/****************************************************************************

    Module Name:
	rtmp_comm.h

	Abstract:
	All common definitions and macros for UTIL/DRIVER/NETIF.

    Revision History:
    Who          When          What
    ---------    ----------    ----------------------------------------------

***************************************************************************/  
    
#ifndef __RT_COMM_H__
#define __RT_COMM_H__
    
#define VENDOR_FEATURE1_SUPPORT
/*#define VENDOR_FEATURE3_SUPPORT */
    
#ifdef RELEASE_EXCLUDE
#define VENDOR_FEATURE2_SUPPORT
#define VENDOR_FEATURE4_SUPPORT
#endif	/* RELEASE_EXCLUDE */
    
/*#define MONITOR_FLAG_11N_SNIFFER_SUPPORT */
    
#ifdef CONFIG_STA_SUPPORT
/*#define AGS_SUPPORT */
#endif	/* CONFIG_STA_SUPPORT */
    
#ifdef VENDOR_FEATURE3_SUPPORT 
#ifdef DOT1X_SUPPORT
#undef DOT1X_SUPPORT
#endif	/* DOT1X_SUPPORT */
#ifdef SYSTEM_LOG_SUPPORT
#undef SYSTEM_LOG_SUPPORT
#endif	/* SYSTEM_LOG_SUPPORT */
#ifdef LED_CONTROL_SUPPORT
#undef LED_CONTROL_SUPPORT
#endif	/* LED_CONTROL_SUPPORT */
#ifdef WSC_LED_SUPPORT
#undef WSC_LED_SUPPORT
#endif	/* WSC_LED_SUPPORT */
#endif /* VENDOR_FEATURE3_SUPPORT */
    
#ifdef RELEASE_EXCLUDE
/*
	Key function explanation as below:

	VENDOR_FEATURE1_SUPPORT:

	1. Purpose:
		Improve the driver throughput.

	2. Improvment:
		a. Support temp TXWI & TXD buffer for each station.
			But you need use extra memory to do buffer, MAX_LEN_OF_MAC_TABLE * 128B

		b. Decrease the use times for NICUpdateFifoStaCounters()

	3. Note:
		Not put to config.mk to avoid to confuse our customers.

	VENDOR_FEATURE2_SUPPORT:

	1. Purpose:
		Add memory debug related parameters in pkt allocation/free.

	VENDOR_FEATURE3_SUPPORT:

	1. Purpose:
		Reduce code size but throughput will be impacted.

	2.	Note:
		 a. Some festures will be removed.
				DOT1X_SUPPORT
				SYSTEM_LOG_SUPPORT		
				LED_CONTROL_SUPPORT & WSC_LED_SUPPORT

	VENDOR_FEATURE4_SUPPORT:

	1. Purpose:
		Add memory debug related parameters in mem allocation/free.

*/ 
#endif	/* RELEASE_EXCLUDE */
    
#ifdef CONFIG_AP_SUPPORT
    
#ifndef VENDOR_FEATURE3_SUPPORT
#define AP_QLOAD_SUPPORT
#endif /* VENDOR_FEATURE3_SUPPORT */
    
#endif	/* CONFIG_AP_SUPPORT */
    

/* ======================== Before include files ============================ */ 
/*
	14 channels @2.4G +  12@UNII(lower/middle) + 16@HiperLAN2 + 11@UNII(upper) + 0 @Japan + 1 as NULL termination
	Refer to CH_HZ_ID_MAP[] in rt_channel.c

*/
#ifdef DOT11_VHT_AC
#define MAX_NUM_OF_CHS             		(54 + 5)	/* 5 channels for central channel of VHT 80MHz */
#else
#define MAX_NUM_OF_CHS             		54
#endif /* DOT11_VHT_AC*/
/* 14 channels @2.4G +  12@UNII + 4 @MMAC + 11 @HiperLAN2 + 7 @Japan + 1 as NULL termination */
#define MAX_NUM_OF_CHANNELS             MAX_NUM_OF_CHS


#include "rtmp_type.h"
#include "rtmp_os.h"
#include "link_list.h"
#include "rtmp_cmd.h"
#include "iface/iface_util.h"
    



/* ======================== Debug =========================================== */ 
/* */
/*  Debug information verbosity: lower values indicate higher urgency */
/* */
#define RT_DEBUG_OFF        0
#define RT_DEBUG_ERROR      1
#define RT_DEBUG_WARN       2
#define RT_DEBUG_TRACE      3
#define RT_DEBUG_INFO       4
#define RT_DEBUG_LOUD       5
    
typedef enum{
	DBG_FUNC_RA = 0x100,	/* debug flag for rate adaptation */
	DBG_FUNC_SA = 0x200,	/* debug flag for smart antenna */
}RT_DEBUG_FUNC;


/* ======================== Definition ====================================== */ 
#ifndef TRUE
#define TRUE						1
#endif
#ifndef FALSE
#define FALSE						0
#endif
    
/* definition of pAd->OpMode */
#define OPMODE_STA                  0
#define OPMODE_AP                   1
#define OPMODE_APSTA				2       /* as AP and STA at the same time */
#if 0
#define OPMODE_L3_BRG               2       // as AP and STA at the same time
#endif
    
#define MAIN_MBSSID                 0
#define FIRST_MBSSID                1
    
/* Endian byte swapping codes */
#define SWAP16(x) \
    ((UINT16) (\
	       (((UINT16) (x) & (UINT16) 0x00ffU) << 8) | \
	       (((UINT16) (x) & (UINT16) 0xff00U) >> 8))) 
 
#define SWAP32(x) \
    ((UINT32) (\
	       (((UINT32) (x) & (UINT32) 0x000000ffUL) << 24) | \
	       (((UINT32) (x) & (UINT32) 0x0000ff00UL) << 8) | \
	       (((UINT32) (x) & (UINT32) 0x00ff0000UL) >> 8) | \
	       (((UINT32) (x) & (UINT32) 0xff000000UL) >> 24))) 

#define SWAP64(x) \
    ((UINT64)( \
    (UINT64)(((UINT64)(x) & (UINT64) 0x00000000000000ffULL) << 56) | \
    (UINT64)(((UINT64)(x) & (UINT64) 0x000000000000ff00ULL) << 40) | \
    (UINT64)(((UINT64)(x) & (UINT64) 0x0000000000ff0000ULL) << 24) | \
    (UINT64)(((UINT64)(x) & (UINT64) 0x00000000ff000000ULL) <<  8) | \
    (UINT64)(((UINT64)(x) & (UINT64) 0x000000ff00000000ULL) >>  8) | \
    (UINT64)(((UINT64)(x) & (UINT64) 0x0000ff0000000000ULL) >> 24) | \
    (UINT64)(((UINT64)(x) & (UINT64) 0x00ff000000000000ULL) >> 40) | \
    (UINT64)(((UINT64)(x) & (UINT64) 0xff00000000000000ULL) >> 56) ))
 
#ifdef RT_BIG_ENDIAN

#define cpu2le64(x) SWAP64((x))
#define le2cpu64(x) SWAP64((x))
#define cpu2le32(x) SWAP32((x))
#define le2cpu32(x) SWAP32((x))
#define cpu2le16(x) SWAP16((x))
#define le2cpu16(x) SWAP16((x))
#define cpu2be64(x) ((UINT64)(x))
#define be2cpu64(x) ((UINT64)(x))
#define cpu2be32(x) ((UINT32)(x))
#define be2cpu32(x) ((UINT32)(x))
#define cpu2be16(x) ((UINT16)(x))
#define be2cpu16(x) ((UINT16)(x))
    
#else /* Little_Endian */
    
#define cpu2le64(x) ((UINT64)(x))
#define le2cpu64(x) ((UINT64)(x))
#define cpu2le32(x) ((UINT32)(x))
#define le2cpu32(x) ((UINT32)(x))
#define cpu2le16(x) ((UINT16)(x))
#define le2cpu16(x) ((UINT16)(x))
#define cpu2be64(x) SWAP64((x))
#define be2cpu64(x) SWAP64((x))
#define cpu2be32(x) SWAP32((x))
#define be2cpu32(x) SWAP32((x))
#define cpu2be16(x) SWAP16((x))
#define be2cpu16(x) SWAP16((x))
    
#endif /* RT_BIG_ENDIAN */
    

#define MAX_CUSTOM_LEN 128 
    
/* */
/* IEEE 802.11 Structures and definitions */
/* */
#define MAX_TX_POWER_LEVEL              100   /* mW */
#define MAX_RSSI_TRIGGER                -10    /* dBm */
#define MIN_RSSI_TRIGGER                -200   /* dBm */
#define MAX_FRAG_THRESHOLD              2346  /* byte count */
#define MIN_FRAG_THRESHOLD              256   /* byte count */
#define MAX_RTS_THRESHOLD               2347  /* byte count */

typedef enum _NDIS_802_11_NETWORK_INFRASTRUCTURE 
 { 
Ndis802_11IBSS, 
Ndis802_11Infrastructure, 
Ndis802_11AutoUnknown, 
Ndis802_11Monitor, 
Ndis802_11InfrastructureMax	/* Not a real value, defined as upper bound */
} NDIS_802_11_NETWORK_INFRASTRUCTURE, *PNDIS_802_11_NETWORK_INFRASTRUCTURE;




/* ======================== Memory ========================================== */ 
#ifdef VENDOR_FEATURE2_SUPPORT

extern ULONG OS_NumOfPktAlloc, OS_NumOfPktFree;

#define MEM_DBG_PKT_ALLOC_INC(__pPacket)	OS_NumOfPktAlloc ++;
#define MEM_DBG_PKT_FREE_INC(__pPacket)		OS_NumOfPktFree ++;
#else
#define MEM_DBG_PKT_ALLOC_INC(__pPacket)
#define MEM_DBG_PKT_FREE_INC(__pPacket)
#endif /* VENDOR_FEATURE2_SUPPORT */
    
/* value domain of 802.11 header FC.Tyte, which is b3..b2 of the 1st-byte of MAC header */
#define BTYPE_MGMT                  0
#define BTYPE_CNTL                  1
#define BTYPE_DATA                  2
    
/* All PHY rate summary in TXD */
/* Preamble MODE in TxD */
#define MODE_CCK	0
#define MODE_OFDM   1
#ifdef DOT11_N_SUPPORT
#define MODE_HTMIX	2
#define MODE_HTGREENFIELD	3
#endif /* DOT11_N_SUPPORT */
#define MODE_VHT	4

#ifdef NO_CONSISTENT_MEM_SUPPORT
/* current support RXD_SIZE = 16B and cache line = 16 or 32B */
#define RTMP_DCACHE_FLUSH(__AddrStart, __Size)							\
		RtmpOsDCacheFlush((ULONG)(__AddrStart), (ULONG)(__Size))
#else
#define RTMP_DCACHE_FLUSH(__AddrStart, __Size)
#endif /* NO_CONSISTENT_MEM_SUPPORT */


/* ======================== Interface ======================================= */
typedef enum _RTMP_INF_TYPE_
{	
	RTMP_DEV_INF_UNKNOWN = 0,
	RTMP_DEV_INF_PCI = 1,
	RTMP_DEV_INF_USB = 2,
	RTMP_DEV_INF_RBUS = 4,
	RTMP_DEV_INF_PCIE = 5,
}RTMP_INF_TYPE;

#if defined(CONFIG_AP_SUPPORT) && defined(CONFIG_STA_SUPPORT)
#define IF_DEV_CONFIG_OPMODE_ON_AP(_pAd)		if(_pAd->OpMode == OPMODE_AP)
#define IF_DEV_CONFIG_OPMODE_ON_STA(_pAd)		if(_pAd->OpMode == OPMODE_STA)
#define RT_CONFIG_IF_OPMODE_ON_AP(__OpMode)		if (__OpMode == OPMODE_AP)
#define RT_CONFIG_IF_OPMODE_ON_STA(__OpMode)	if (__OpMode == OPMODE_STA)
#else
#define IF_DEV_CONFIG_OPMODE_ON_AP(_pAd)
#define IF_DEV_CONFIG_OPMODE_ON_STA(_pAd)
#define RT_CONFIG_IF_OPMODE_ON_AP(__OpMode)
#define RT_CONFIG_IF_OPMODE_ON_STA(__OpMode)
#endif

/* associated with device interface */
typedef struct _DEV_PRIV_INFO {
	VOID			*pPriv; /* pAd */
	UINT32			priv_flags;
} DEV_PRIV_INFO;



    
/***********************************************************************************
 * IOCTL related definitions and data structures.
 **********************************************************************************/
typedef struct __RTMP_IOCTL_INPUT_STRUCT
{
	union
	{
		CHAR *name;
		struct
		{
			CHAR *pointer;
			UINT16 length;
			UINT16 flags;
		} data;
	} u;
} RTMP_IOCTL_INPUT_STRUCT;


#define RT_CMD_STATUS_TRANSLATE(__Status)				\
	{													\
		if (__Status == RTMP_IO_EINVAL)					\
			__Status = -EINVAL;							\
		else if (__Status == RTMP_IO_EOPNOTSUPP)		\
			__Status = -EOPNOTSUPP;						\
		else if (__Status == RTMP_IO_EFAULT)			\
			__Status = -EFAULT;							\
		else if (__Status == RTMP_IO_E2BIG)				\
			__Status = -E2BIG;							\
		else if (__Status == RTMP_IO_ENOMEM)			\
			__Status = -ENOMEM;							\
		else if (__Status == RTMP_IO_EAGAIN)			\
			__Status = -EAGAIN;							\
		else if (__Status == RTMP_IO_ENOTCONN)			\
			__Status = -ENOTCONN;						\
	}




/* ======================== Timer =========================================== */
typedef struct _LIST_RESOURCE_OBJ_ENTRY
{
	struct _LIST_RESOURCE_OBJ_ENTRY *pNext;
	VOID *pRscObj;
} LIST_RESOURCE_OBJ_ENTRY, *PLIST_RESOURCE_OBJ_ENTRY;




/* ======================== IC =========================================== */
#define RFIC_24GHZ		0x01
#define RFIC_5GHZ		0x02




/* ======================== CFG80211 ======================================== */ 
#define RT_CFG80211_DEBUG /* debug use */

#ifdef RT_CFG80211_DEBUG
#define CFG80211DBG(__Flg, __pMsg)		DBGPRINT(__Flg, __pMsg)
#else
#define CFG80211DBG(__Flg, __pMsg)
#endif /* RT_CFG80211_DEBUG */

/* 1 ~ 14 */
#define CFG80211_NUM_OF_CHAN_2GHZ			14

/* 36 ~ 64, 100 ~ 136, 140 ~ 161 */
#define CFG80211_NUM_OF_CHAN_5GHZ			\
							(sizeof(Cfg80211_Chan)-CFG80211_NUM_OF_CHAN_2GHZ)




/* ======================== Packet ========================================== */ 
#define LENGTH_802_11               24
#define LENGTH_802_11_AND_H         30
#define LENGTH_802_11_CRC_H         34
#define LENGTH_802_11_CRC           28
#define LENGTH_802_11_WITH_ADDR4    30
#define LENGTH_802_3                14
#define LENGTH_802_3_TYPE           2
#define LENGTH_802_1_H              8
#define LENGTH_EAPOL_H              4
#define LENGTH_WMMQOS_H				2
#define LENGTH_CRC                  4
#define MAX_SEQ_NUMBER              0x0fff
#define LENGTH_802_3_NO_TYPE		12
#define LENGTH_802_1Q				4 /* VLAN related */


#ifdef TX_PKT_SG
#ifndef MAX_SKB_FRAGS 
#define MAX_SKB_FRAGS (65536/(1UL << 12) + 2)
#endif
typedef struct _PTK_SG_T{
	VOID *data;
	INT len;
}PKT_SG_T;
#endif /* TX_PKT_SG */
/*
	Packet information for NdisQueryPacket
*/
typedef struct  _PACKET_INFO    {
	UINT PhysicalBufferCount;    /* Physical breaks of buffer descripor chained */
	UINT BufferCount;           /* Number of Buffer descriptor chained */
	UINT TotalPacketLength ;     /* Self explained */
	PNDIS_BUFFER pFirstBuffer;   /* Pointer to first buffer descriptor */
#ifdef TX_PKT_SG
	PKT_SG_T sg_list[MAX_SKB_FRAGS];
#endif /* TX_PKT_SG */
} PACKET_INFO, *PPACKET_INFO;


#define MAC_ADDR_LEN                    6
    
/* 2-byte Frame control field */
    typedef struct GNU_PACKED {
	
#ifdef RT_BIG_ENDIAN
	USHORT Order:1;		/* Strict order expected */
	USHORT Wep:1;		/* Wep data */
	USHORT MoreData:1;	/* More data bit */
	USHORT PwrMgmt:1;	/* Power management bit */
	USHORT Retry:1;		/* Retry status bit */
	USHORT MoreFrag:1;	/* More fragment bit */
	USHORT FrDs:1;		/* From DS indication */
	USHORT ToDs:1;		/* To DS indication */
	USHORT SubType:4;	/* MSDU subtype */
	USHORT Type:2;		/* MSDU type */
	USHORT Ver:2;		/* Protocol version */
#else
        USHORT Ver:2;		/* Protocol version */
	USHORT Type:2;		/* MSDU type */
	USHORT SubType:4;	/* MSDU subtype */
	USHORT ToDs:1;		/* To DS indication */
	USHORT FrDs:1;		/* From DS indication */
	USHORT MoreFrag:1;	/* More fragment bit */
	USHORT Retry:1;		/* Retry status bit */
	USHORT PwrMgmt:1;	/* Power management bit */
	USHORT MoreData:1;	/* More data bit */
	USHORT Wep:1;		/* Wep data */
	USHORT Order:1;		/* Strict order expected */
#endif	/* !RT_BIG_ENDIAN */
} FRAME_CONTROL, *PFRAME_CONTROL;


typedef struct GNU_PACKED _HEADER_802_11 {
        FRAME_CONTROL   FC;
        USHORT          Duration;
        UCHAR           Addr1[MAC_ADDR_LEN];
        UCHAR           Addr2[MAC_ADDR_LEN];
	UCHAR			Addr3[MAC_ADDR_LEN];
#ifdef RT_BIG_ENDIAN
	USHORT			Sequence:12;
	USHORT			Frag:4;
#else
	USHORT			Frag:4;
	USHORT			Sequence:12;
#endif /* !RT_BIG_ENDIAN */
	UCHAR			Octet[0];
}	HEADER_802_11, *PHEADER_802_11;

enum {
	DIDmsg_lnxind_wlansniffrm		= 0x00000044,
	DIDmsg_lnxind_wlansniffrm_hosttime	= 0x00010044,
	DIDmsg_lnxind_wlansniffrm_mactime	= 0x00020044,
	DIDmsg_lnxind_wlansniffrm_channel	= 0x00030044,
	DIDmsg_lnxind_wlansniffrm_rssi		= 0x00040044,
	DIDmsg_lnxind_wlansniffrm_sq		= 0x00050044,
	DIDmsg_lnxind_wlansniffrm_signal	= 0x00060044,
	DIDmsg_lnxind_wlansniffrm_noise		= 0x00070044,
	DIDmsg_lnxind_wlansniffrm_rate		= 0x00080044,
	DIDmsg_lnxind_wlansniffrm_istx		= 0x00090044,
	DIDmsg_lnxind_wlansniffrm_frmlen	= 0x000A0044
};
enum { 
P80211ENUM_msgitem_status_no_value = 0x00 
};

enum { 
P80211ENUM_truth_false = 0x00, 
P80211ENUM_truth_true = 0x01 
};


/* Definition from madwifi */
typedef struct {
        UINT32 did;
        UINT16 status;
        UINT16 len;
        UINT32 data;
} p80211item_uint32_t;

typedef struct {
        UINT32 msgcode;
        UINT32 msglen;
#define WLAN_DEVNAMELEN_MAX 16
        UINT8 devname[WLAN_DEVNAMELEN_MAX];
        p80211item_uint32_t hosttime;
        p80211item_uint32_t mactime;
        p80211item_uint32_t channel;
        p80211item_uint32_t rssi;
        p80211item_uint32_t sq;
        p80211item_uint32_t signal;
        p80211item_uint32_t noise;
        p80211item_uint32_t rate;
        p80211item_uint32_t istx;
        p80211item_uint32_t frmlen;
} wlan_ng_prism2_header;

#ifdef MONITOR_FLAG_11N_SNIFFER_SUPPORT
/*
	Note: 2009/11/10
	Used in WiFi Sigma Test Engine RT3593 (replace RT2883).
*/

#if 0
    From modified wireshark source code:
	2,   4,   11,  22,  12,  18,  24,  36, 48,   72,  96, 108, 109, 110,  111, 112,
	13,  26,  39,  52,  78, 104, 117, 130, 26,   52,  78, 104, 156, 208,  234, 260, /* long GI */
	27,  54,  81, 108, 162, 216, 243, 270, 54,  108, 162, 216, 324, 432,  486, 540,
	14,  29,  43,  57,  87, 115, 130, 144, 29,   59,  87, 115, 173, 230,  260, 288, /* short GI */
	30,  60,  90, 120, 180, 240, 270, 300, 60,  120, 180, 240, 360, 480,  540, 600,
	39,  78, 117, 156, 234, 312, 351, 390, 52,  104, 156, 208, 312, 416,  486, 520,
	81, 162, 243, 324, 486, 648, 729, 810, 108, 216, 324, 432, 648, 864,  972, 1080,
	43,  87, 130, 173, 260, 347, 391, 433, 58,  116, 173, 231, 347, 462,  520, 578,
	90, 180, 270, 360, 540 ,720, 810, 900, 120, 240, 360, 480, 720, 960, 1080, 1200,
	64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,   78, 79,
	80
#endif
#ifdef RT_BIG_ENDIAN
typedef struct _ETHEREAL_RADIO {
        UCHAR Flag_80211n;
        UCHAR signal_level; /* dBm */
        UCHAR data_rate; /* rate index */
        UCHAR channel; /* Channel number */
} ETHEREAL_RADIO, *PETHEREAL_RADIO;
#else
typedef struct _ETHEREAL_RADIO {
        UCHAR channel; /* Channel number */
        UCHAR data_rate; /* rate index */
        UCHAR signal_level; /* dBm */
        UCHAR Flag_80211n;      
} ETHEREAL_RADIO, *PETHEREAL_RADIO;
#endif

#define WIRESHARK_11N_FLAG_3x3             	0x01
#define WIRESHARK_11N_FLAG_GF              	0x02
#define WIRESHARK_11N_FLAG_AMPDU     	 	0x04
#define WIRESHARK_11N_FLAG_STBC          	0x08
#define WIRESHARK_11N_FLAG_SGI             	0x10
#define WIRESHARK_11N_FLAG_BW20U      		0x20
#define WIRESHARK_11N_FLAG_BW20D      		0x40
#define WIRESHARK_11N_FLAG_BW40             0x80
#endif /* MONITOR_FLAG_11N_SNIFFER_SUPPORT */
    
#ifdef WIDI_SUPPORT
#define 	ETH_P_WIDI_NOTIF	0x888F
#endif /* WIDI_SUPPORT */

#ifdef DPA_S
#define 	ETH_P_DPA_S_NOTIF	0x5572
#endif /* DPA_S */

/* structure to store channel TX power */
typedef struct _CHANNEL_TX_POWER {
	USHORT RemainingTimeForUse;	/*unit: sec */
	UCHAR Channel;
#ifdef DOT11N_DRAFT3
	BOOLEAN bEffectedChannel;	/* For BW 40 operating in 2.4GHz , the "effected channel" is the channel that is covered in 40Mhz. */
#endif /* DOT11N_DRAFT3 */
	CHAR Power;
	CHAR Power2;
#ifdef DOT11N_SS3_SUPPORT
	CHAR Power3;
#endif /* DOT11N_SS3_SUPPORT */
	UCHAR MaxTxPwr;
	UCHAR DfsReq;
	UCHAR RegulatoryDomain;

/*
	Channel property:
 
	CHANNEL_DISABLED: The channel is disabled.
	CHANNEL_PASSIVE_SCAN: Only passive scanning is allowed.
	CHANNEL_NO_IBSS: IBSS is not allowed.
	CHANNEL_RADAR: Radar detection is required.
	CHANNEL_NO_FAT_ABOVE: Extension channel above this channel is not allowed.
	CHANNEL_NO_FAT_BELOW: Extension channel below this channel is not allowed.
	CHANNEL_40M_CAP: 40 BW channel group
 */
#define CHANNEL_DEFAULT_PROP	0x00
#define CHANNEL_DISABLED		0x01	/* no use */
#define CHANNEL_PASSIVE_SCAN	0x02
#define CHANNEL_NO_IBSS			0x04
#define CHANNEL_RADAR			0x08
#define CHANNEL_NO_FAT_ABOVE	0x10
#define CHANNEL_NO_FAT_BELOW	0x20
#define CHANNEL_40M_CAP			0x40

	UCHAR Flags;

#ifdef RT30xx
	UCHAR Tx0FinePowerCtrl;	/* Tx0 fine power control in 0.1dB step */
	UCHAR Tx1FinePowerCtrl;	/* Tx1 fine power control in 0.1dB step */
	UCHAR Tx2FinePowerCtrl;	/* Tx2 fine power control in 0.1dB step */
#endif /* RT30xx */
} CHANNEL_TX_POWER, *PCHANNEL_TX_POWER;

#endif /* __RT_COMM_H__ */

