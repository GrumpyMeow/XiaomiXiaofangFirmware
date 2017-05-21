#ifndef __MSC_LIB_H__
#define __MSC_LIB_H__

//#define BIT(n) (1UL << (n%(8*sizeof(unsigned long))))

#define ERR_NOTSUPPORT		-1
#define ERR_TIMEDOUT		-2
#define ERR_INVALIDPARAM	-3

//#define MSC_DROP_DATA BIT(0)
//#define MSC_DROP_MGMT BIT(1)
//#define MSC_DROP_MULTICAST BIT(2)
//#define MSC_DROP_BROADCAST BIT(3)
#if 0 
enum sc_ctrl_id {
	MSC_CTRLID_ENABLE_MONITOR_MODE = 0x00,
	MSC_CTRLID_DISABLE_MONITOR_MODE,
	MSC_CTRLID_GET_MODE,
	MSC_CTRLID_SET_CHANNEL,
	MSC_CTRLID_GET_CHANNEL,
	MSC_CTRLID_SET_FILTER,
	MSC_CTRLID_GET_FILTER,
	MSC_CTRLID_USE_ELIAN,
	MSC_CTRLID_MAX
};
enum msc_band {
	MSC_BAND_2GHZ,
	MSC_BAND_5GHZ,
	MSC_BAND_60GHZ,
	MSC_BAND_NUM
};
#endif

enum msc_chan_width {
	MSC_CHAN_WIDTH_20_NOHT,
	MSC_CHAN_WIDTH_20,
	MSC_CHAN_WIDTH_40_PLUS,
	MSC_CHAN_WIDTH_80,
	MSC_CHAN_WIDTH_80P80,
	MSC_CHAN_WIDTH_160,
	MSC_CHAN_WIDTH_5,
	MSC_CHAN_WIDTH_10,
	MSC_CHAN_WIDTH_40_MINUS,
};

enum msc_iftype {
	MSC_IFTYPE_UNSPECIFIED,
	MSC_IFTYPE_ADHOC,
	MSC_IFTYPE_STATION,
	MSC_IFTYPE_AP,
	MSC_IFTYPE_AP_VLAN,
	MSC_IFTYPE_WDS,
	MSC_IFTYPE_MONITOR,
	MSC_IFTYPE_MESH_POINT,
	MSC_IFTYPE_P2P_CLIENT,
	MSC_IFTYPE_P2P_GO,
	MSC_IFTYPE_P2P_DEVICE,

	MSC_IFTYPE_IFTYPES,
};

struct chan_info {
	int chan_id;
	enum msc_chan_width width;
	unsigned int flags;
};

struct monitor_info {
	//enum msc_iftype iftype;
	unsigned int filter;
	struct chan_info chl_info;
	void *priv;
};

typedef int (*sc_input_func) (char *, int);
typedef int (*sc_sw_filter) (char *, int);

int sccb_init(sc_input_func input_func, sc_sw_filter filter_func);
int sccb_deinit(void);
int sccb_enter_monitor_mode(struct monitor_info *info, void *priv);
int sccb_leave_monitor_mode(void *priv);
int sccb_set_monitor_chan(struct chan_info *chl_info, void *priv);
int sccb_rx(char *data, unsigned int data_len);
int sccb_enable_input(void);
int sccb_disable_input(void);
#endif

