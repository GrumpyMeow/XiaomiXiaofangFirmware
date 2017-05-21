#ifndef __DOT11V_WNM_H__
#define __DOT11V_WNM_H__

#ifdef DOT11V_WNM_SUPPORT
#include "rtmp_type.h"

/* wireless network management category */

#define WNM_CATEGORY								18


#define WNM_TCLAS_TYPE_ETHERNET_LEN 	17
#define WNM_TCLAS_TYPE_IP_V4_LEN		18
#define WNM_TCLAS_TYPE_8021DQ_LEN		5

#define 	WNMMAX_DMSID		5
#define	WNMMAX_TCLAS		5
/* wnm Information Element IDs. */


/*#define WNM_INF_ELE_ID_OFFSET								100 */
#define WNM_INF_ELE_EVENT_REQUEST_ID						78
#define WNM_INF_ELE_EVENT_REPORT_ID						79
#define WNM_INF_ELE_DIAGNOSTIC_REQUEST_ID				80
#define WNM_INF_ELE_DIAGNOSTIC_REPORT_ID					81
#define WNM_INF_ELE_LOCATION_PARAMETERS_ID				82
#define WNM_INF_ELE_NON_TRAN_BSSID_CAP_ID				83
#define WNM_INF_ELE_SSID_LIST_ID							84
#define WNM_INF_ELE_MUTI_BSSID_INDEX_ID					85
#define WNM_INF_ELE_FMS_DESCRIPTOR_ID					86
#define WNM_INF_ELE_FMS_REQUEST_ID						87
#define WNM_INF_ELE_FMS_RESPONSE_ID						88
#define WNM_INF_ELE_QOS_TRAFF_CAP_ID						89
#define WNM_INF_ELE_BSS_MAX_IDLE_PERIOD_ID				90
#define WNM_INF_ELE_TFS_REQUEST_ID						91
#define WNM_INF_ELE_TFS_RESPONSE_ID						92
#define WNM_INF_ELE_WNM_SLEEP_MODE_ID					93
#define WNM_INF_ELE_TIM_BCAST_REQUEST_ID					94
#define WNM_INF_ELE_TIM_BACST_RESPONSE_ID				95
#define WNM_INF_ELE_COLLOCATED_INTERF_REPORT_ID			96
#define WNM_INF_ELE_CHANNEL_USAGE_ID						97
#define WNM_INF_ELE_TIME_ZONE								98
#define WNM_INF_ELE_DMS_REQUEST							99
#define WNM_INF_ELE_DMS_RESPONSE							100


/* wnm action field values */


#define WNM_ACTION_EVENT_REQUEST									0
#define WNM_ACTION_EVENT_REPORT									1
#define WNM_ACTION_DIAGNOSTIC_REQUEST							2
#define WNM_ACTION_DIAGNOSTIC_REPORT								3
#define WNM_ACTION_LOCATION_CONF_REQUEST						4
#define WNM_ACTION_LOCATION_CONF_REPORT							5
#define WNM_ACTION_BSS_TRANS_MANG_QUERY						6
#define WNM_ACTION_BSS_TRANS_MANG_REQUEST						7
#define WNM_ACTION_BSS_TRANS_MANG_RESPONSE						8
#define WNM_ACTION_FMS_REQUEST									9
#define WNM_ACTION_FMS_RESPONSE									10
#define WNM_ACTION_COLLOCATED_INTERF_REQUEST					11
#define WNM_ACTION_COLLOCATED_INTERF_RESPONSE					12
#define WNM_ACTION_TFS_REQUEST									13
#define WNM_ACTION_TFS_RESPONSE									14
#define WNM_ACTION_TFS_NOTIFY										15
#define WNM_ACTION_WNM_SLEEP_MODE_REQUEST						16
#define WNM_ACTION_WNM_SLEEP_MODE_RESPONSE					17
#define WNM_ACTION_TIM_BCAST_REQUEST							18
#define WNM_ACTION_TIM_BACST_RESPONSE							19
#define WNM_ACTION_TIM												20
#define WNM_ACTION_QOS_TRAFF_CAP_UPDATE						21
#define WNM_ACTION_TIMING_MEASUREMENT							22
#define WNM_ACTION_DMS_REQUEST									23
#define WNM_ACTION_DMS_RESPONSE									24



/*Neighbor Report elememt*/

#define BSS_TRANSITION_CANDIDATE_PEFERENCE					3
#define BSS_TERMINATION_DURATION								4



/*  Status field values */
#define WNM_STATUS_ACCEPT													0
#define WNM_STATUS_ACCEPT_TIM												1
#define WNM_STATUS_DENIED_FROMAT_ERROR									2
#define WNM_STATUS_OVERRIDDEN_DUE_TO_REQUEST_INTERVAL_TOO_LONG		3
#define WNM_STATUS_OVERRIDDEN_DUE_TO_LACK_RESOURCES					4

/*wnm sleep mode response status */
#define ENTER_EXIT_WNM_SLEEP_MODE_ACCEPT					0
#define EXIT_WNM_SLEEP_MODE_ACCEPT_GTK_UPDATE				1
#define WNM_SLEEP_MODE_DENY1									2
#define WNM_SLEEP_MODE_DENY2									3
#define WNM_SLEEP_MODE_DENY3									4
#define WNM_SLEEP_MODE_DENY4									5

typedef struct  GNU_PACKED  _WNM_IDLE_OPTION
{	
	UCHAR pkar:1;
	UCHAR Reserv:7;
} WNM_IDLE_OPTION;	


typedef struct GNU_PACKED _WNM_BSS_MAX_IDLE_PERIOD_ELEMENT
{
/*	UCHAR 	ElementID; */
/*	UCHAR 	Length; */
	UINT16 	MaxIdlePeriod;
	WNM_IDLE_OPTION	IdleOptions;

} WNM_BSS_MAX_IDLE_PERIOD_ELEMENT, *PWNM_BSS_MAX_IDLE_PERIOD_ELEMENT;

/* wnm sleep mode action type */
#define WNM_ENTER_SLEEP_MODE			0
#define WNM_EXIT_SLEEP_MODE			1

typedef struct GNU_PACKED _WNM_SLEEP_MODE_ELEMENT
{

	UCHAR 	ElementID;
	UCHAR 	Length;
	UCHAR 	Actiontype;
	UCHAR 	WNMSleepModeRespStatus;
	UCHAR	WNMSleepInterval;

} WNM_SLEEP_MODE_ELEMENT, *PWNM_SLEEP_MODE_ELEMENT;


typedef struct GNU_PACKED _WNM_TFS_REQUEST_ELEMENT
{
	UCHAR 	ElementID;
	UCHAR 	Length;
	UCHAR 	TFSID;
	UCHAR 	TFSActionCode;
/*one or more TFS Request subelements*/
	UCHAR	TFSReqSubelement[0];
} WNM_TFS_REQUEST_ELEMENT, *PWNM_TFS_REQUEST_ELEMENT;

typedef struct GNU_PACKED _WNM_TFS_STATUS_SUBELEMENT
{
	UCHAR 	SubElementID;
	UCHAR 	Length;
	UCHAR 	TFSRespStatus;
	UCHAR	TFSID;
} WNM_TFS_STATUS_SUBELEMENT, *P_WNM_TFS_STATUS_SUBELEMENT;




typedef struct GNU_PACKED _WNM_TFS_RESPONSE_ELEMENT
{
	UCHAR 	ElementID;
	UCHAR 	Length;

	UCHAR 	TFSActionCode;
/*one or more TFS Request subelements*/
	UCHAR	TFSReqSubelement[0];
} WNM_TFS_RESPONSE_ELEMENT, *PWNM_TFS_RESPONSE_ELEMENT;




typedef struct _WNM_TCLAS
{

    UCHAR  UserPriority;				/* user priority */

#define WNM_TCLAS_TYPE_ETHERNET			0
#define WNM_TCLAS_TYPE_IP_V4				1
#define WNM_TCLAS_TYPE_8021DQ			2
#define WNM_TCLAS_TYPE_FITER_OFFSET				3
#define WNM_TCLAS_TYPE_IP_AND_HIGHERLAYER_PAR			4


#define WNM_TCLAS_TYPE_MAX				WNM_TCLAS_TYPE_IP_AND_HIGHERLAYER_PAR

#define WNM_TCLAS_TYPE_ETHERNET_LEN 	17
#define WNM_TCLAS_TYPE_IP_V4_LEN		18
#define WNM_TCLAS_TYPE_8021DQ_LEN		5

#define WNM_TCLAS_TYPE_WME_ETHERNET_LEN	(17+6) /* 6 is OUI header length */
#define WNM_TCLAS_TYPE_WME_IP_V4_LEN	(18+6) /* 6 is OUI header length */
#define WNM_TCLAS_TYPE_WME_8021DQ_LEN	(5+6)  /* 6 is OUI header length */
    UCHAR  ClassifierType;

    UCHAR  ClassifierMask;				/* maximum 8 fields mapping */

    union
    {
        struct
        {
            UCHAR   AddrSrc[6];		/* source MAC address */
            UCHAR   AddrDst[6];		/* destination MAC address */
            UINT16  Type;				/* type/length */
            UCHAR   Reserved[28];
        } __attribute__ ((packed)) Ethernet;

        struct
        {
            UCHAR   Version;
            UINT32  IpSource;
            UINT32  IpDest;
            UINT16  PortSource;
            UINT16  PortDest;
            UCHAR   DSCP;
            UCHAR   Protocol;
            UCHAR   Reserved[27];
        } __attribute__ ((packed)) IPv4;

        struct
        {
            UINT16  TagType;			/* VLAN tag (2B) */
            UCHAR   Reserved[40];
        } __attribute__ ((packed)) IEEE8021Q;
    } Clasifier;
} __attribute__ ((packed)) WNM_TCLAS;



typedef struct _TCLAS_PROCESSING_ELEMRNT {

	UCHAR ElementId;
	UCHAR Length;

#define ACM_TCLAS_PROCESSING_ALL		0
#define ACM_TCLAS_PROCESSING_ONE		1
	UCHAR Processing;
} __attribute__ ((packed)) TCLAS_PROCESSING_ELEMRNT;


typedef struct GNU_PACKED _TCLAS_ELEMENT
{
	UCHAR 	ElementID;
	UCHAR 	Length;
	WNM_TCLAS Tclas;
	
} TCLAS_ELEMENT, *PTCLAS_ELEMENT;


typedef struct GNU_PACKED _WNM_TFS_SUBELEMENT
{
	UCHAR 	SubElementID;
	UCHAR 	Length;
/*one or more TCLAS_ELEMENT*/
/*	TCLAS_ELEMENT	TCLASElement;*/
	UCHAR	TCLASElement[0];
	TCLAS_PROCESSING_ELEMRNT	TCLASProcessingElement;

} WNM_TFS_SUBELEMENT, *PWNM_TFS_SUBELEMENT;


typedef struct _WNM_SLEEP_MODE_REQ_FRAME
{

	UCHAR 	Category;
	UCHAR 	Action;
	UCHAR 	DialogToken;
	WNM_SLEEP_MODE_ELEMENT 	WNMSleepModeElement;
/*one or more TFS Request elements*/
/*	WNM_TFS_REQUEST_ELEMENT	TFSRequestElements;*/
	UCHAR	TFSreqelement[0];
} GNU_PACKED WNM_SLEEP_MODE_REQ_FRAME;


#define	WNM_SLEEP_MODE_SUBLEMENT_GTK	0
#define	WNM_SLEEP_MODE_SUBLEMENT_IGTK	1


typedef struct GNU_PACKED _WNM_SLEEP_MODE_GTK_SUBELEMENT
{
	UCHAR 	SubElementID;
	UCHAR 	Length;
	UINT16	KeyInfo;
	UCHAR	KeyLength;
	UCHAR 	rsc[8];
	PUCHAR	*Key;
} WNM_SLEEP_MODE_GTK_SUBELEMENT, *PWNM_SLEEP_MODE_GTK_SUBELEMENT;


typedef struct GNU_PACKED _WNM_SLEEP_MODE_IGTK_SUBELEMENT
{
	UCHAR 	SubElementID;
	UCHAR 	Length;
	UINT16	KeyID;
	UCHAR	PN[6];
	UCHAR 	Key[16];
} WNM_SLEEP_MODE_IGTK_SUBELEMENT, *PWNM_SLEEP_MODE_IGTK_SUBELEMENT;




typedef struct _WNM_SLEEP_MODE_RESP_FRAME
{

	UCHAR 	Category;
	UCHAR 	Action;
	UCHAR 	DialogToken;
	UINT16	KeyDateLenght;
	PUCHAR  *KeyData;
	WNM_SLEEP_MODE_ELEMENT 	WNMSleepModeElement;
/*one or more TFS Request elements*/
/*	WNM_TFS_REQUEST_ELEMENT	TFSRequestElements;*/
	UCHAR	TFSreqelement[0];
} GNU_PACKED WNM_SLEEP_MODE_RESP_FRAME;



#define	UNSPECIFIED													0
#define	EXCESSIVE_FRAME_LOSS_RATES_AND_POOR_CONDITIONS			1
#define	EXCESSIVE_DELAY_FOR_CURRENT_TRAFFIC_STREAMS				2
#define	INSUFFICIENT_QOS_CAPCAITY_FOR_CURRENT_TRAFFIC_STREAMS	3
#define	FIRST_ASSOCIATION_RO_ESS										4
#define	LOAD_BALANCING												5
#define	BETTER_AP_FOUND												6
#define	DEAUTHENTICATED_OR_DISACCOCIATES_FROM_THE_PERVIOUS_AP	7	
#define	AP_FAILED_IEEE_8021X_EAP_AUTHENTICATION						8
#define	AP_FAILED_4WAY_HANDSHAKE									9
#define	REVEIVED_TOO_MANY_REPLAY_COUNTER_FAILURES					10
#define	RECEIVED_TOO_MANY_DATA_MIC_FAILURES						11
#define	EXCEEDED_MAXIMUM_NUMBER_OF_RETRANSMISSIONS				12
#define	RECEIVED_TOO_MANY_BROADCAST_DISASSOCIATIONS				13
#define	RECEIVED_TOO_MANY_BROCADCAST_DEAUTHEHTICATIONS			14
#define	PREVIOUS_TRANSITION_FAILD										15
#define	LOW_RSSI														16

typedef struct _WNM_BSS_TRANSITION_QUERY_FRAME
{
	HEADER_802_11   Hdr;
	UCHAR 	Category;
	UCHAR 	Action;
	UCHAR 	DialogToken;
	UCHAR	BSSTransitionQueryReason;
} GNU_PACKED WNM_BSS_TRANSITION_QUERY_FRAME, *PWNM_BSS_TRANSITION_QUERY_FRAME;


typedef struct  GNU_PACKED  _WNM_BSS_REQUEST_MODE
{	
	UCHAR	PreferredCandidateList:1;
	UCHAR	Abridged:1;
	UCHAR	DisassociationImminent:1;
	UCHAR	BSSTerminationIncluded:1;
	UCHAR	reserve:4;
} WNM_BSS_REQUEST_MODE, *PWNM_BSS_REQUEST_MODE;	


typedef struct GNU_PACKED _WNM_NEIGHBOR_BSSTCP_ELEMENT
{
	UCHAR ElementId;
	UCHAR Length;	
	UCHAR Preference;
} WNM_NEIGHBOR_BSSTCP_ELEMENT, *RWNM_NEIGHBOR_BSSTCP_ELEMENT;

typedef struct GNU_PACKED _WNM_NEIGHBOR_BSSTD_ELEMENT
{
	UCHAR ElementId;
	UCHAR Length;	
	UCHAR BssTTSF[8];
	UINT16 Duration;
} WNM_NEIGHBOR_BSSTD_ELEMENT, *RWNM_NEIGHBOR_BSSTD_ELEMENT;


typedef struct _WNM_BSS_TRANSITION_REQUEST_FRAME
{
	HEADER_802_11   Hdr;
	UCHAR 	Category;
	UCHAR 	Action;
	UCHAR 	DialogToken;
	WNM_BSS_REQUEST_MODE	RequestMode;
	UCHAR	DisassociationTimer;
	UCHAR	ValidityInterval;
/*	UCHAR	BSS TerminationDuration;*/
/*	 BSSTransitionCandidateListListEntries;*/
	UCHAR	BssTCLEntry[0];

} GNU_PACKED WNM_BSS_TRANSITION_REQUEST_FRAME, *PWNM_BSS_TRANSITION_REQUEST_FRAME;


typedef struct _WNM_BSS_TRANSITION_RESPONSE_FRAME
{
	HEADER_802_11   Hdr;
	UCHAR 	Category;
	UCHAR 	Action;
	UCHAR 	DialogToken;
	UCHAR	Statuscode;
	UCHAR	BSSTerminationDelay;
/*	UCHAR	TargetBSSID*/
} GNU_PACKED WNM_BSS_TRANSITION_RESPONSE_FRAME;


typedef struct GNU_PACKED  _WNM_DMS_DESCRIPTOR
{
	UCHAR 	DMSID;
	UCHAR 	Length;
/*zero or more TCLAS_ELEMENT*/
/*	TCLAS_ELEMENT	TCLASElement;*/
	UCHAR	TCLASElement[0];
	TCLAS_PROCESSING_ELEMRNT	TCLASProcessingElement;
} WNM_DMS_DESCRIPTOR, *PWNM_DMS_DESCRIPTOR;

#define	DMS_REQUEST_TYPE_ADD		0
#define	DMS_REQUEST_TYPE_REMOVE		1
#define	DMS_REQUEST_TYPE_CHANGE		2

typedef struct _WNM_DMS_REQUEST_ELEMENT
{
	UCHAR 	ElementId;
	UCHAR 	Length;
	UCHAR 	RequestType;
/*one or more one or more DMS Status*/
	UCHAR	DMSDescriptorList[0];
} GNU_PACKED WNM_DMS_REQUEST_ELEMENT, *PWNM_DMS_REQUEST_ELEMENT;



typedef struct _WNM_DMS_REQUEST_FRAME
{
	UCHAR 	Category;
	UCHAR 	Action;
	UCHAR 	DialogToken;

/*	UCHAR	RequestTyppe; */
/*one or more one or more DMS Descriptors*/
	UCHAR	DMSReqelements[0];

} GNU_PACKED WNM_DMS_REQUEST_FRAME, *PWNM_DMS_REQUEST_FRAME;


typedef struct _WNM_DMS_STATUS
{
	UCHAR 	DMSID;
	UCHAR 	Status;
} GNU_PACKED WNM_DMS_STATUS, *PWNM_DMS_STATUS;



typedef struct _WNM_DMS_RESPONSE_ELEMENT
{
	UCHAR 	ElementId;
	UCHAR 	Length;
/*	UCHAR 	RequestType; */
/*one or more one or more DMS Status*/
/*	UCHAR	DMSDescriptorList[0]; */
} GNU_PACKED WNM_DMS_RESPONSE_ELEMENT, *PWNM_DMS_RESPONSE_ELEMENT;



typedef struct _WNM_DMS_RESPONSE_FRAME
{
	HEADER_802_11   Hdr;
	UCHAR 	Category;
	UCHAR 	Action;
	UCHAR 	DialogToken;
/*one or more one or more DMS Status*/
/*	UCHAR	DMSStatusList[0]; */

} GNU_PACKED WNM_DMS_RESPONSE_FRAME, *PWNM_DMS_RESPONSE_FRAME;


#define	FMS_STATUS_SUBELEMENT			1
#define	VENDOR_SPECIFIC_SUBELEMENT 		221



typedef struct _WNM_FMS_DESCRIPTOR
{
	UCHAR 	ElementID;
	UCHAR 	Length;
	UCHAR 	NumOfFMSCs;;
/* zero  or more FMS Counters*/
	UCHAR	FMSCounters[0];
/* zero  one or more FMSIDs*/
	UCHAR	FMSIDs[0];

} GNU_PACKED WNM_FMS_DESCRIPTOR, *PWNM_FMS_DESCRIPTOR;


typedef struct GNU_PACKED _FMS_IDENTIFICATION_FIELD_FORMAT{
	ULONG	MCSSelector:3;
	ULONG	RateType:2;
	ULONG	rsv1:3;
	ULONG	MCSIndex:8;
	ULONG	Rate:16;
}FMS_IDENTIFICATION_FIELD_FORMAT, *PFMS_IDENTIFICATION_FIELD_FORMAT;


typedef struct _WNM_FMS_SUBELEMENT
{
	UCHAR 	SubelementID;
	UCHAR 	Length;
	UCHAR 	DeliveryInterval;
	UCHAR	MaxDeliveryInterval;
/*draf 6.0 change*/
/*	UINT16	MulticastRate; */
	FMS_IDENTIFICATION_FIELD_FORMAT Identifiction_field;
/*one or more TCLAS_ELEMENT*/
/*	TCLAS_ELEMENT	TCLASElement;*/
/*	UCHAR	TCLASElement[0]; */
/*	TCLAS_PROCESSING_ELEMRNT	TCLASProcessingElement; */
} GNU_PACKED WNM_FMS_SUBELEMENT, *PWNM_FMS_SUBELEMENT;


typedef struct _WNM_FMS_REQUEST_ELEMENT
{
	UCHAR 	ElementId;
	UCHAR 	Length;
	UCHAR 	FMSToken;
/*one or more one or more DMS Status*/
	UCHAR	FMSRequestSubelements[0];
} GNU_PACKED WNM_FMS_REQUEST_ELEMENT, *PWNM_FMS_REQUEST_ELEMENT;


typedef struct _WNM_FMS_REQUEST_FRAME
{
	UCHAR 	Category;
	UCHAR 	Action;
	UCHAR 	DialogToken;
	WNM_FMS_REQUEST_ELEMENT	FMS_Request_Element;

} GNU_PACKED WNM_FMS_REQUEST_FRAME, *PWNM_FMS_REQUEST_FRAME;

/* fms and tfs element status definition */
#define FMS_TFS_ELEM_STATUS_ACCEPT		0
#define FMS_TFS_ELEM_STATUS_DENY1			1
#define FMS_TFS_ELEM_STATUS_DENY2			2	
#define FMS_TFS_ELEM_STATUS_DENY3			3
#define FMS_TFS_ELEM_STATUS_DENY4			4
#define FMS_TFS_ELEM_STATUS_DENY5			5
#define FMS_TFS_ELEM_STATUS_OVERRIDE1	6
#define FMS_TFS_ELEM_STATUS_OVERRIDE2	7
#define FMS_TFS_ELEM_STATUS_OVERRIDE3	8
#define FMS_TFS_ELEM_STATUS_OVERRIDE4	9
#define FMS_TFS_ELEM_STATUS_TERMINATE1	10
#define FMS_TFS_ELEM_STATUS_TERMINATE2	11
#define FMS_TFS_ELEM_STATUS_TERMINATE3	12
#define FMS_TFS_ELEM_STATUS_OVERRIDE5	13

typedef struct GNU_PACKED _FMS_COUNTER{
#ifdef RT_BIG_ENDIAN
	UCHAR	FMSCounterID:3;
	UCHAR	CurrentCount:5;
#else
	UCHAR	CurrentCount:5;
	UCHAR	FMSCounterID:3;
#endif /* RT_BIG_ENDIAN */
}FMS_COUNTER, *PFMS_COUNTER;

typedef struct _WNM_FMS_STATUS_SUBELMENT
{
	UCHAR 	SubelementID;
	UCHAR 	Length;
	UCHAR 	ElementStatus;
	UCHAR	DeliveryInterval;
	UCHAR	MaxDeliveryInterval;
	UCHAR	FMSID;
	FMS_COUNTER	FMSCounter;
/*	UINT16	MulticastRate; */
	FMS_IDENTIFICATION_FIELD_FORMAT Identifiction_field;
	UCHAR	MulticastAddress[MAC_ADDR_LEN];
} GNU_PACKED WNM_FMS_STATUS_SUBELMENT, *PWNM_FMS_STATUS_SUBELMENT;






typedef struct _WNM_FMS_RESPONSE_ELEMENT
{
	UCHAR 	ElementId;
	UCHAR 	Length;
	UCHAR 	FMSToken;
/*one or more one or more Status Subelements*/
	UCHAR	StatusSubelements[0];	
} GNU_PACKED WNM_FMS_RESPONSE_ELEMENT, *PWNM_FMS_RESPONSE_ELEMENT;


typedef struct _WNM_FMS_RESPONSE_FRAME
{
	UCHAR 	Category;
	UCHAR 	Action;
	UCHAR 	DialogToken;
	WNM_FMS_RESPONSE_ELEMENT	FMS_Response_Element;

} GNU_PACKED WNM_FMS_RESPONSE_FRAME, *PWNM_FMS_RESPONSE_FRAME;





/* bss status code definitions */

#define BSS_STATUS_CODE_ACCEPT								0
#define BSS_STATUS_CODE_REJECT_1								1
#define BSS_STATUS_CODE_REJECT_2								2
#define BSS_STATUS_CODE_REJECT_3								3
#define BSS_STATUS_CODE_REJECT_4								4
#define BSS_STATUS_CODE_BSS_TERMINATION_DELAY_REQUESTED	0









#endif /* DOT11V_WNM_SUPPORT */

#endif /* __DOT11V_WNM_H__ */

