
#ifndef __MSC_PLAT_H__
#define __MSC_PLAT_H__

#include "sccb.h"
#include "../msc/msc.h"

int sc_plt_enter_monitor_mode(struct monitor_info *info, void *priv);
int sc_plt_leave_monitor_mode(void *priv);
int sc_plt_set_monitor_chan(struct chan_info *info, void *priv);
char *sc_plt_get_la(void *priv);
void sc_plt_aes128_decrypt(unsigned char *,unsigned int, unsigned char *, 
				unsigned int, unsigned char *, unsigned int *);
void sc_plt_add_timer(struct etimer *);
int sc_plt_del_timer(struct etimer *);
#endif
