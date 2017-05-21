
#include "plat.h"
#include "../os/linux/osal.h"

#include "rtmp_comm.h"
#include "rt_os_util.h"
#include "rt_os_net.h"
#include "rt_config.h"
static unsigned int g_iftype = 0;
static struct timer_list rst_timer;

int sc_plt_set_monitor_chan(struct chan_info *info, void *priv)
{
	CFG80211_CB *p80211CB = NULL;
	CMD_RTPRIV_IOCTL_80211_CHAN ChanInfo;
	PRTMP_ADAPTER pAd = (PRTMP_ADAPTER)priv;

	MSC_DBG("[MSC] set chl, chan_id:%d, width:%d, chan_flags:0x%x\n",
		 info->chan_id, info->width, info->flags );

	memset(&ChanInfo, 0, sizeof(ChanInfo));
	ChanInfo.ChanId = info->chan_id;

	RTMP_DRIVER_80211_CB_GET(pAd, &p80211CB);
	if (p80211CB == NULL) {
		return -1;
	}

	ChanInfo.MonFilterFlag = 0x17f93;//0x17f93 is a RX filter   //0x17f13-->won't drop duplicate frame
	ChanInfo.IfType = RT_CMD_80211_IFTYPE_MONITOR;

	if(info->width == MSC_CHAN_WIDTH_20_NOHT) {
		ChanInfo.ChanType = RT_CMD_80211_CHANTYPE_NOHT;
	} else if (info->width == MSC_CHAN_WIDTH_20) {
		ChanInfo.ChanType = RT_CMD_80211_CHANTYPE_HT20;
	} else if (info->width == MSC_CHAN_WIDTH_40_PLUS) {
		ChanInfo.ChanType = RT_CMD_80211_CHANTYPE_HT40PLUS;
	} else if (info->width == MSC_CHAN_WIDTH_40_MINUS) {
		ChanInfo.ChanType = RT_CMD_80211_CHANTYPE_HT40MINUS;
	} else {
		ChanInfo.ChanType = RT_CMD_80211_CHANTYPE_NOHT;
	}

	/* set channel */
	RTMP_DRIVER_80211_CHAN_SET(pAd, &ChanInfo);
	//PRTMP_ADAPTER pAd = (PRTMP_ADAPTER)priv;
	//AsicSwitchChannel(pAd, info->chan_id, FALSE);
 
	return 0;
}

int sc_plt_enter_monitor_mode(struct monitor_info *info, void *priv)
{
	PRTMP_ADAPTER pAd = (PRTMP_ADAPTER)priv;
	unsigned int filter = 0;

	MSC_DBG("[MSC] enter monitor mode: filter:0x%x, chan_id:%d, width:%d, chan_flags:0x%x, monitor_priv=%p, priv=%p\n",
			info->filter, info->chl_info.chan_id, info->chl_info.width,
			info->chl_info.flags, info->priv, priv);

	filter |= 0x07;

	/* 1.Save current state info. */
	g_iftype = pAd->net_dev->ieee80211_ptr->iftype;
	MSC_DBG("[MSC] old iftype: 0x%x\n", g_iftype);

	/* 2.Switch to monitor mode. */
	CFG80211DRV_OpsChgVirtualInf(pAd, &filter, RT_CMD_80211_IFTYPE_MONITOR);

	sc_plt_set_monitor_chan(&info->chl_info, priv);

	return 0;
}

int sc_plt_leave_monitor_mode(void *priv)
{
	PRTMP_ADAPTER pAd = (PRTMP_ADAPTER)priv;
	unsigned int filter = 0;
	
	MSC_DBG("[MSC] leave monitor mode.\n");
	CFG80211DRV_OpsChgVirtualInf(pAd, &filter, g_iftype);
	return 0;
}

char *sc_plt_get_la(void *priv)
{
	PRTMP_ADAPTER pAd = (PRTMP_ADAPTER)priv;
	MSC_DBG("[MSC] get local address %p : %x:%x:%x:%x:%x:%x\n",
		priv, pAd->CurrentAddress[0]&0xff, pAd->CurrentAddress[1]&0xff, pAd->CurrentAddress[2]&0xff, 
		pAd->CurrentAddress[3]&0xff, pAd->CurrentAddress[4]&0xff, pAd->CurrentAddress[5]&0xff);
	return (char*)pAd->CurrentAddress;
}

void sc_plt_aes128_decrypt(unsigned char *cipher_blk, unsigned int cipher_blk_size, 
				unsigned char *key, unsigned int key_len, 
				unsigned char *plain_blk, unsigned int *plain_blk_size)
{
	return RT_AES_Decrypt(cipher_blk, cipher_blk_size, key, key_len, plain_blk, plain_blk_size);
}

void sc_plt_add_timer(struct etimer *p)
{
	init_timer(&rst_timer);
	rst_timer.expires = jiffies + p->expires * HZ;
	rst_timer.data = p->data;
	rst_timer.function = p->func;
	return add_timer(&rst_timer);	
}

int sc_plt_del_timer(struct etimer *p)
{
	return del_timer(&rst_timer);
}

