
#include "../os/linux/osal.h"
#include "../lib/sccb.h"
#include "msc.h"
#include "../lib/plat.h"
#include "rtmp_comm.h"
#include "rt_os_util.h"
#include "rt_os_net.h"
#include "rt_config.h"


static unsigned char msc_listen_chls[] = {1, 6, 11, 2, 5, 7, 1, 6, 11, 10, 12, 3, 1, 6, 11, 8, 13, 4, 9};
#if 0
struct chan_info msc_listen_chls[] = {
	{1, 	MSC_CHAN_WIDTH_40_PLUS, 0},
	{6, 	MSC_CHAN_WIDTH_40_PLUS, 0},
	{6, 	MSC_CHAN_WIDTH_40_MINUS, 0},
	{11, 	MSC_CHAN_WIDTH_40_MINUS, 0},
	{2, 	MSC_CHAN_WIDTH_40_PLUS, 0},
	{5, 	MSC_CHAN_WIDTH_40_PLUS, 0},
	{5, 	MSC_CHAN_WIDTH_40_MINUS, 0},
	{7, 	MSC_CHAN_WIDTH_40_PLUS, 0},
	{7, 	MSC_CHAN_WIDTH_40_MINUS, 0},
	{1, 	MSC_CHAN_WIDTH_40_PLUS, 0},
	{6, 	MSC_CHAN_WIDTH_40_PLUS, 0},
	{6, 	MSC_CHAN_WIDTH_40_MINUS, 0},
	{11, 	MSC_CHAN_WIDTH_40_MINUS, 0},
	{10, 	MSC_CHAN_WIDTH_40_MINUS, 0},
	{12, 	MSC_CHAN_WIDTH_40_MINUS, 0},
	{3, 	MSC_CHAN_WIDTH_40_PLUS, 0},
	{1, 	MSC_CHAN_WIDTH_40_PLUS, 0},
	{6, 	MSC_CHAN_WIDTH_40_PLUS, 0},
	{6, 	MSC_CHAN_WIDTH_40_MINUS, 0},
	{11, 	MSC_CHAN_WIDTH_40_MINUS, 0},
	{8, 	MSC_CHAN_WIDTH_40_MINUS, 0},
	{13, 	MSC_CHAN_WIDTH_40_MINUS, 0},
	{4, 	MSC_CHAN_WIDTH_40_PLUS, 0},
	{9, 	MSC_CHAN_WIDTH_40_MINUS, 0},
};
#endif
#define MSC_CHANNEL_DWELL_TIME 400 //ms in unit
/* On linux OS, timer handler is running in INTR context.
   It can't call any function which may cause sleep. we have
   to handle this case carefully.
*/

//TODO: thread or timer? which one is better.
#define MSC_CHANNEL_SWITCH_USE_THREAD 1

struct msc_contex {
	/* event call back, when received ssid&pwd,
	 this function will be call with parameter
	 struct msc_param. */
	msc_evt_cb evt_cb;
#if MSC_CHANNEL_SWITCH_USE_THREAD
	osal_thread chl_thread;
	int chl_thread_running;
	bool is_thread_run_to_end;
#else
	osal_timer timer;
#endif
	unsigned int chl_num;
	unsigned char *channel;
	struct monitor_info m_info;
	spinlock_t lock;
	int cur_chl;

#define MSC_STATE_STARTED 1
#define MSC_STATE_STOPED 0
	int state;
	void *priv;
} msc_ctx;

static void msc_core_evt_cbk(enum eevent_id eid);
#if MSC_CHANNEL_SWITCH_USE_THREAD
static int chl_switch_thread(void *data);
#else
static void timeout_handler(unsigned long data);
#endif
static int msc_init(struct msc_param *param, void *priv);

int msc_get_current_channel_info(void)
{
	int cur_chl = 0;
	PRTMP_ADAPTER pAd = (PRTMP_ADAPTER)(msc_ctx.priv);
	cur_chl = pAd->CommonCfg.Channel;
	MSC_INFO("[MSC] current channel = %d\n",cur_chl);
	return cur_chl;
}


static void msc_core_evt_cbk(enum eevent_id eid) 
{
	osal_lock(&msc_ctx.lock);
	switch(eid) {
	case EVT_ID_SYNCSUC:
		if (msc_ctx.chl_num > 1) {
#if MSC_CHANNEL_SWITCH_USE_THREAD
			/*We don't used osal_thread_stop because this function
			  may cause sleep on linux(kthread_stop), and we this runtine
			  may be called from intr context.*/
			msc_ctx.cur_chl = msc_get_current_channel_info();
			msc_ctx.chl_thread_running = 0;
			MSC_INFO("[MSC]stop chl_switch thread.\n");
			//osal_thread_stop(&msc_ctx.chl_thread);
#else
			osal_timer_stop(&msc_ctx.timer);
#endif
		}
		break;
	case EVT_ID_INFOGET:
		sccb_disable_input();
		if (msc_ctx.evt_cb)
			msc_ctx.evt_cb(eid);
		break;
	case EVT_ID_TIMEOUT:
		MSC_INFO("[MSC]receive pkt timeout.\n");
#if 0		
		msc_stop(msc_ctx.priv);
		msc_msleep(1000);
		
		para.chls = NULL;
		para.chl_num = 0;
		msc_start(&para, msc_ctx.priv);
#endif		
		break;
	default:
		break;
	}
	osal_unlock(&msc_ctx.lock);
	return;
}

#if MSC_CHANNEL_SWITCH_USE_THREAD
static int chl_switch_thread(void *data)
{
	int idx = 0;
	struct chan_info chl_info;
	chl_info.chan_id = 0;
	chl_info.flags = 0x0;
	chl_info.width = MSC_CHAN_WIDTH_40_PLUS;

	//while(!osal_thread_should_stop(&msc_ctx.chl_thread)) {
	while(1) {//msc_ctx.chl_thread_running) {
		osal_msleep(MSC_CHANNEL_DWELL_TIME);
		osal_lock(&msc_ctx.lock);
		if(!msc_ctx.chl_thread_running)
		{
			osal_unlock(&msc_ctx.lock);
			break;
		}
		msc_ctx.is_thread_run_to_end = 0;
		chl_info.chan_id = msc_ctx.channel[(idx++)%msc_ctx.chl_num];
		if (chl_info.chan_id >= 8  && chl_info.chan_id <= 14) {
			chl_info.width = MSC_CHAN_WIDTH_40_MINUS;
		} else {
			chl_info.width = MSC_CHAN_WIDTH_40_PLUS;
		}
		chl_info.flags = 0x0;
		sccb_set_monitor_chan(&chl_info, msc_ctx.priv);
		msc_ctx.is_thread_run_to_end = 1;
		osal_unlock(&msc_ctx.lock);
		}
	if ((msc_ctx.cur_chl != chl_info.chan_id) && (chl_info.chan_id != 0) &&  (msc_ctx.cur_chl != 0))
	{
		osal_msleep(100);
		chl_info.chan_id = msc_ctx.cur_chl;
		if (chl_info.chan_id >= 8  && chl_info.chan_id <= 14) {
			chl_info.width = MSC_CHAN_WIDTH_40_MINUS;
		} else {
			chl_info.width = MSC_CHAN_WIDTH_40_PLUS;
		}
		chl_info.flags = 0x0;
		sccb_set_monitor_chan(&chl_info, msc_ctx.priv);
		MSC_INFO("[MSC] chl_info.chan_id = %d\n",chl_info.chan_id);
	}
	
	return 0;
}
#else
static void timeout_handler(unsigned long data)
{
	static int idx = 0;
	struct chan_info chl_info;

	osal_lock(&msc_ctx.lock);
	chl_info.chan_id = msc_ctx.channel[(idx++)%msc_ctx.chl_id];
	if (chl_info.chan_id >= 8  && chl_info.chan_id <= 14) {
		chl_info.width = MSC_CHAN_WIDTH_40_MINUS;
	} else {
		chl_info.width = MSC_CHAN_WIDTH_40_PLUS;
	}
	chl_info.flags = 0x0;
	sccb_set_monitor_chan(&chl_info, msc_ctx.priv);

	osal_timer_modify(&msc_ctx.timer, 1000);
	osal_unlock(&msc_ctx.lock);
	return;
}
#endif

struct efunc_table f_tbl = {
	.report_evt = msc_core_evt_cbk,
	.start_timer = sc_plt_add_timer,
	.stop_timer = sc_plt_del_timer,
	.aes128_decrypt = sc_plt_aes128_decrypt,
};

static int msc_init(struct msc_param *param, void *priv)
{
	int ret = 0;

	
	osal_memset(&msc_ctx, 0, sizeof(msc_ctx));

	osal_lock_init(&msc_ctx.lock);
	msc_ctx.evt_cb = param->evt_cb;

	MSC_INFO("[MSC] Driver v 1.0.0\n");
	if (param->chl_num == 0) {
		msc_ctx.channel = msc_listen_chls;
		msc_ctx.chl_num = sizeof(msc_listen_chls);
	} else {
		msc_ctx.channel = param->chls;
		msc_ctx.chl_num = param->chl_num;
	}

	ret = elian_init(sc_plt_get_la(priv), &f_tbl, param->key);
	if (ret) {
		MSC_WARN("[MSC] Get sc fsm init failed.\n");
		//Add error handler.
	}

#if MSC_CHANNEL_SWITCH_USE_THREAD
	msc_ctx.chl_thread.thread_func = chl_switch_thread;
	msc_ctx.chl_thread.data = NULL;
	strcpy(msc_ctx.chl_thread.name, "chl_switch");
	osal_thread_create(&msc_ctx.chl_thread);
#else
	msc_ctx.timer.timeoutHandler = timeout_handler;
	osal_timer_create(&msc_ctx.timer);
#endif
	return ret;
}

int msc_start(struct msc_param *param, void *priv)
{
	int ret = 0;

	if(msc_ctx.state == MSC_STATE_STARTED)
		return 0;

	msc_init(param, priv);

	sccb_init(elian_input, NULL);

	msc_ctx.m_info.filter = 0x00000000;
	msc_ctx.m_info.priv = NULL;
	msc_ctx.m_info.chl_info.chan_id = msc_ctx.channel[0];
	if (msc_ctx.m_info.chl_info.chan_id >= 8  && msc_ctx.m_info.chl_info.chan_id <= 14) {
		msc_ctx.m_info.chl_info.width = MSC_CHAN_WIDTH_40_MINUS;
	} else {
		msc_ctx.m_info.chl_info.width = MSC_CHAN_WIDTH_40_PLUS;
	}
	msc_ctx.m_info.chl_info.flags = 0x0;
	msc_ctx.chl_thread_running = 1;
	msc_ctx.is_thread_run_to_end = 1;
	msc_ctx.cur_chl = 0;
	msc_ctx.priv = priv;
	/* Config to monitor mode. */
	sccb_enter_monitor_mode(&msc_ctx.m_info, priv);

	sccb_enable_input();

	if (msc_ctx.chl_num > 1) {
#if MSC_CHANNEL_SWITCH_USE_THREAD
		osal_thread_run(&msc_ctx.chl_thread);
#else
		osal_timer_start(&msc_ctx.timer, 1000);
#endif
	}

	msc_ctx.state = MSC_STATE_STARTED;
	return ret;
}

void msc_stop(void *priv)
{
	unsigned int count=0;
	bool timeout = 0;

	if (msc_ctx.state == MSC_STATE_STOPED)
		return;
	
	osal_lock(&msc_ctx.lock);
	if (msc_ctx.chl_num > 1) {
#if MSC_CHANNEL_SWITCH_USE_THREAD
		/* Avoid INTR context. */
		//osal_thread_stop(&msc_ctx.chl_thread);
		msc_ctx.chl_thread_running = 0;
#else
		osal_timer_stop(&msc_ctx.timer);
#endif
	}
	elian_stop();
	sccb_disable_input();

	/*there is a problem if chl_switch_thread haven't finish "sccb_set_monitor_chan()" function.
	so we use a flag "msc_ctx.is_thread_run_to_end" to avoid that case*/
	while(msc_ctx.is_thread_run_to_end == 0) 
	{	
		MSC_INFO("chl_switch thread not finished, waiting 50ms!\n");
		osal_msleep(50);
		if(count++ >= 40)
		{
			timeout=1;
			break;
		}
	}

	if(timeout)
	{
		MSC_WARN("msc_stop failed (timeout)!\n");
		return;
	}
	
	sccb_leave_monitor_mode(priv);

	msc_ctx.state = MSC_STATE_STOPED;
	osal_unlock(&msc_ctx.lock);
	return;
}

int msc_get_result(struct msc_result *result)
{
	char buffer[MSC_RESULT_BUFFER_SIZE] = {0};
	int len;

	len = MSC_RESULT_BUFFER_SIZE;
	elian_get(TYPE_ID_AM, buffer, &len);
	/* TODO:shoule add error handling. */
	memcpy((char *)&(result->auth_mode), buffer, len);

	len = MSC_RESULT_BUFFER_SIZE;
	memset(buffer, 0, sizeof(buffer));
	elian_get(TYPE_ID_SSID, buffer, &len);
	memcpy(result->ssid, buffer, len);

	len = MSC_RESULT_BUFFER_SIZE;
	memset(buffer, 0, sizeof(buffer));
	elian_get(TYPE_ID_PWD, buffer, &len);
	memcpy(result->pwd, buffer, len);

	len = MSC_RESULT_BUFFER_SIZE;
	memset(buffer, 0, sizeof(buffer));
	elian_get(TYPE_ID_USER, buffer, &len);
	memcpy(result->user, buffer, len);

	len = MSC_RESULT_BUFFER_SIZE;
	memset(buffer, 0, sizeof(buffer));
	elian_get(TYPE_ID_CUST, buffer, &len);
	memcpy(result->cust_data, buffer, len);
	result->cust_data_len = len;

	return 0;
}

int msc_reset()
{
	sccb_disable_input();
	elian_reset();
	sccb_enable_input();

	return 0;
}

int msc_set_chl(struct chan_info *chl, void *priv)
{
	if(msc_ctx.state == MSC_STATE_STOPED)
		return -1;

	sccb_set_monitor_chan(chl, priv);
	return 0;
}

int msc_cmd_handler(char *cmd, int len, char *result_str, void *priv)
{
	char *p = cmd;
	struct msc_param para = {0};
	struct msc_result result ={0};
	struct chan_info chl_info;
	int chl;
	char result_str_temp[500];

	if (cmd == NULL || result_str == NULL || priv == NULL)
		return -1;

	MSC_INFO("[MSC] msc_cmd_handler %s %d\n", cmd, len);
	if(osal_strncmp(p, "start", 5) == 0) {
		if(len>6) { //+1 for "enter"
			p = osal_strstr(p, "ch=");
			if(p == NULL){
				osal_strcpy(result_str, "Format: elian start ch=6");
				return -2;
			}
			chl = (int)osal_strtol(p+3, NULL, 10);
			para.chls = (char *)&chl;
			MSC_INFO("[MSC] msc_cmd_handler %s %d\n", p, chl);
			para.chl_num = 1;
		} else {
			para.chls = NULL;
			para.chl_num = 0;
		}
		msc_start(&para, priv);
		osal_strcpy(result_str, "ok");
	} else if(osal_strcmp(p, "stop") == 0) {
		msc_stop(priv);	
		osal_strcpy(result_str, "ok");
	} else if (osal_strcmp(p, "clear") == 0) {
		msc_reset();	
		osal_strcpy(result_str, "ok");
	} else if (osal_strcmp(p, "result") == 0){
		msc_get_result(&result);
		MSC_INFO("[MSC] AM=%d, ssid=%s, pwd=%s, user=%s, cust_data_len=%d, cust_data=%s,\n",
				result.auth_mode, result.ssid, result.pwd, 
				result.user, result.cust_data_len, result.cust_data);
		sprintf(result_str_temp, "AM=%d, ssid=%s, pwd=%s, user=%s, cust_data_len=%d, cust_data=%s,\n",
				result.auth_mode, result.ssid, result.pwd, 
				result.user, result.cust_data_len, result.cust_data);
		if(osal_strlen(result_str_temp) >= MSC_RESULT_BUFFER_SIZE)
		{
			printk("Max result len is 128, Current len is [%d] \n", osal_strlen(result_str_temp));
		}
		else
		{
			osal_memcpy(result_str, result_str_temp, osal_strlen(result_str_temp));
		}
	} else if (osal_strncmp(p, "set_ch=", 7) == 0) {

		chl = (int)osal_strtol(p+7, NULL, 10);
		chl_info.chan_id = chl;

	 	if(osal_strstr(p, "bw=20")) {
			chl_info.width = MSC_CHAN_WIDTH_20;
		} else if (osal_strstr(p, "bw=40h")) {
			chl_info.width = MSC_CHAN_WIDTH_40_PLUS;
		} else if (osal_strstr(p, "bw=40l")) {
			chl_info.width = MSC_CHAN_WIDTH_40_MINUS;
		} else {
			if (chl_info.chan_id >= 8  && chl_info.chan_id <= 14) {
				chl_info.width = MSC_CHAN_WIDTH_40_MINUS;
			} else {
				chl_info.width = MSC_CHAN_WIDTH_40_PLUS;
			}
		}
		chl_info.flags = 0x0;
		if (msc_set_chl(&chl_info, priv)) {
			osal_strcpy(result_str, "call start CMD first.");
		} else {
			osal_strcpy(result_str, "ok");
		}
	} else {
		osal_strcpy(result_str, "unknown CMD.");
	}
	return 0;
}

