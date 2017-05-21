
#include "rt_config.h"

#ifdef FPGA_MODE
struct fpga_cmd{
	PSTRING cmd_id;
	INT (*fpga_func)(RTMP_ADAPTER *pAd, PSTRING arg);
};




#if 0
INT set_phy_rate(RTMP_ADAPTER *pAd, PSTRING arg)
{
	return TRUE;
}


struct fpga_cmd cmd_list[] = 
{
	{"on",						set_fpga_mode}
	{"TxKickCnt",					set_tx_kickcnt},
	{"dataphy",					set_data_phy_mode},
	{"datamcs",					set_data_mcs},
};


INT fpga_cmd_handler(RTMP_ADAPTER *pAd, PSTRING arg)
{


}
#endif
#endif /* FPGA_MODE */

