
#ifndef __MSC_H__
#define __MSC_H__

#include "core.h"

#define MSC_RESULT_BUFFER_SIZE 256
typedef void (*msc_evt_cb)(unsigned int eid);

struct msc_param {
	msc_evt_cb evt_cb;
	int chl_num;
	unsigned char *chls;
	unsigned char *key;
	void *reserved;
};

struct msc_result {
	unsigned char auth_mode;
	unsigned char cust_data_len;
	char ssid[33];
	char pwd[65];
	char user[65];
	char cust_data[256];
};

int msc_start(struct msc_param *p, void *priv);
void msc_stop(void *pirv);
int msc_reset(void);
int msc_get_result(struct msc_result *result);
int msc_cmd_handler(char *cmd, int len, char *result_str, void *priv);

#endif

