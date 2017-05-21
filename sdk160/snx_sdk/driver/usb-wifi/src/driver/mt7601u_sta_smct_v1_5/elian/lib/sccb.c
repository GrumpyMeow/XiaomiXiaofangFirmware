
#include "sccb.h"
#include "plat.h"
#include "../os/linux/osal.h"

#define MSC_ENABLE_RX_BIT  ((unsigned int)0x1<<31) //BIT(31)

#define sccb_rx_enabled()		(ctrl_data.flag&(MSC_ENABLE_RX_BIT))

struct sccb_ctrl_data {
	unsigned int flag;
	sc_input_func input_func;
	sc_sw_filter filter_func;
} ctrl_data;

int sccb_enable_input()
{
	ctrl_data.flag |= MSC_ENABLE_RX_BIT;
	return 0;	
}

int sccb_disable_input()
{
	ctrl_data.flag &= ~MSC_ENABLE_RX_BIT;
	return 0;
}

int sccb_init(sc_input_func input_func, sc_sw_filter filter_func)
{
	ctrl_data.input_func = input_func;
	ctrl_data.filter_func = filter_func;
	ctrl_data.flag = 0x00000000;
	return 0;
}

int sccb_deinit()
{
	ctrl_data.input_func = NULL;
	ctrl_data.filter_func = NULL;
	ctrl_data.flag = 0x00000000;
	return 0;
}

int sccb_set_monitor_chan(struct chan_info *chl_info, void *priv)
{
	return sc_plt_set_monitor_chan(chl_info, priv);
}

int sccb_enter_monitor_mode(struct monitor_info *info, void *priv)
{
	return sc_plt_enter_monitor_mode(info, priv);
}

int sccb_leave_monitor_mode(void *priv)
{
	return sc_plt_leave_monitor_mode(priv);
}

int sccb_rx(char *data, unsigned int data_len)
{
	char *p= NULL;
	int len;

	if (!sccb_rx_enabled()) {
		return -1;
	}

	if (ctrl_data.input_func == NULL) {
		return -2;
	}

	p = data;
	len = data_len;

	if (ctrl_data.filter_func != NULL) {
		if (ctrl_data.filter_func(p, len)) {
			return -3;
		}
	}

	if (ctrl_data.input_func != NULL) {
		return ctrl_data.input_func(p, len);
	}	
	return -4;
}

