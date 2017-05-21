/*
 ***************************************************************************
 * Ralink Tech Inc.
 * 4F, No. 2 Technology 5th Rd.
 * Science-based Industrial Park
 * Hsin-chu, Taiwan, R.O.C.
 *
 * (c) Copyright 2002-2006, Ralink Technology, Inc.
 *
 * All rights reserved.	Ralink's source	code is	an unpublished work	and	the
 * use of a	copyright notice does not imply	otherwise. This	source code
 * contains	confidential trade secret material of Ralink Tech. Any attemp
 * or participation	in deciphering,	decoding, reverse engineering or in	any
 * way altering	the	source code	is stricitly prohibited, unless	the	prior
 * written consent of Ralink Technology, Inc. is obtained.
 ***************************************************************************/

/****************************************************************************
	Abstract:

***************************************************************************/

#ifndef __WNM_H__
#define __WNM_H__


#ifdef DOT11V_WNM_SUPPORT
#include "rtmp_type.h"
#include "wnm_cmm.h"

#ifdef CONFIG_AP_SUPPORT
#define IS_BSS_TRANSIT_MANMT_SUPPORT(_P, _I) \
	((_P)->ApCfg.MBSSID[(_I)].WnmCfg.bDot11vWNM_BSSEnable == TRUE)

#define IS_WNMDMS_SUPPORT(_P, _I) \
	((_P)->ApCfg.MBSSID[(_I)].WnmCfg.bDot11vWNM_DMSEnable == TRUE)


#define IS_WNMFMS_SUPPORT(_P, _I) \
	((_P)->ApCfg.MBSSID[(_I)].WnmCfg.bDot11vWNM_FMSEnable == TRUE)

#define IS_WNMSleepMode_SUPPORT(_P, _I) \
	((_P)->ApCfg.MBSSID[(_I)].WnmCfg.bDot11vWNM_SleepModeEnable == TRUE)

#define IS_WNMTFS_SUPPORT(_P, _I) \
	((_P)->ApCfg.MBSSID[(_I)].WnmCfg.bDot11vWNM_TFSEnable == TRUE)


#endif /* CONFIG_AP_SUPPORT */


#ifdef CONFIG_STA_SUPPORT

#define IS_BSS_TRANSIT_MANMT_SUPPORT(_P) \
	((_P)->StaCfg.WnmCfg.bDot11vWNM_BSSEnable == TRUE)

#define IS_WNMDMS_SUPPORT(_P) \
	((_P)->StaCfg.WnmCfg.bDot11vWNM_DMSEnable == TRUE)

#define IS_WNMFMS_SUPPORT(_P) \
	((_P)->StaCfg.WnmCfg.bDot11vWNM_FMSEnable == TRUE)

#define IS_WNMSleepMode_SUPPORT(_P) \
	((_P)->StaCfg.WnmCfg.bDot11vWNM_SleepModeEnable == TRUE)

#define IS_WNMTFS_SUPPORT(_P) \
	((_P)->StaCfg.WnmCfg.bDot11vWNM_TFSEnable == TRUE)


#endif /* CONFIG_STA_SUPPORT */


#define WNM_MEM_COPY(__Dst, __Src, __Len)	memcpy(__Dst, __Src, __Len)
#define WNMR_ARG_ATOI(__pArgv)				simple_strtol((PSTRING) __pArgv, 0, 10)
#define WNMR_ARG_ATOH(__Buf, __Hex)			AtoH((PSTRING) __Buf, __Hex, 1)



VOID WNMAPBTMStateMachineInit(
    IN  PRTMP_ADAPTER   pAd, 
    IN  STATE_MACHINE *Sm, 
    OUT STATE_MACHINE_FUNC Trans[]);


VOID WNMSTABTMStateMachineInit(
    IN  PRTMP_ADAPTER   pAd, 
    IN  STATE_MACHINE *Sm, 
    OUT STATE_MACHINE_FUNC Trans[]);


/*
========================================================================
Routine Description:

Arguments:

Return Value:

Note:

========================================================================
*/
VOID WNM_Action(
	IN PRTMP_ADAPTER pAd, 
	IN MLME_QUEUE_ELEM *Elem);


/*
	==========================================================================
	Description:
		
	Parametrs:
	
	Return	: None.
	==========================================================================
 */
void WNM_ReadParametersFromFile(
	IN PRTMP_ADAPTER pAd,
	PSTRING tmpbuf,
	PSTRING buffer);


#ifdef CONFIG_AP_SUPPORT

BOOLEAN DeleteDMSEntry(
    IN  PRTMP_ADAPTER	pAd,
    IN  MAC_TABLE_ENTRY *pEntry);

VOID FMSTable_Release(
	IN PRTMP_ADAPTER pAd);

VOID DMSTable_Release(
	IN PRTMP_ADAPTER pAd);

BOOLEAN DeleteTFSID(
    IN  PRTMP_ADAPTER	pAd,
    IN  MAC_TABLE_ENTRY *pEntry);


NDIS_STATUS DMSPktInfoQuery(
	IN PRTMP_ADAPTER pAd,
	IN PUCHAR pSrcBufVA,
	IN PNDIS_PACKET pPacket,
	IN UCHAR apidx,
	IN UCHAR QueIdx,
	IN UINT8 UserPriority);

NDIS_STATUS FMSPktInfoQuery(
	IN PRTMP_ADAPTER pAd,
	IN PUCHAR pSrcBufVA,
	IN PNDIS_PACKET pPacket,
	IN UCHAR apidx,
	IN UCHAR QueIdx,
	IN UINT8 UserPriority);

NDIS_STATUS TFSPktInfoQuery(
	IN PRTMP_ADAPTER pAd,
	IN PUCHAR pSrcBufVA,
	IN PNDIS_PACKET pPacket,
	IN UCHAR apidx,
	IN UCHAR QueIdx,
	IN UINT8 UserPriority);

/* */
/*
	==========================================================================
	Description:
		
	Parametrs:
	
	Return	: None.
	==========================================================================
 */
#if 0
INT     Set_WnmMaxIdlePeriod_Proc(
        IN      PRTMP_ADAPTER   pAd,
        IN      PSTRING                 arg);
#endif
INT	Set_WNMTransMantREQ_Proc(
	IN	PRTMP_ADAPTER	pAd, 
	IN	PSTRING			arg);

INT Set_APWNMDMSShow_Proc(
	IN	PRTMP_ADAPTER	pAd, 
	IN	PSTRING			arg);

/*
	==========================================================================
	Description:
		Insert WNM Max Idle Capabilitys IE into frame.
		
	Parametrs:
		1. frame buffer pointer.
		2. frame length.
	
	Return	: None.
	==========================================================================
 */
VOID WNM_InsertMaxIdleCapIE(
	IN PRTMP_ADAPTER pAd,
	IN UCHAR aoidx,
	OUT PUCHAR pFrameBuf,
	OUT PULONG pFrameLen);

VOID WNM_InsertFMSDescripotr(
	IN PRTMP_ADAPTER pAd,
	OUT PUCHAR pFrameBuf,
	OUT PULONG pFrameLen,
	IN UINT8 ElementID,
	IN UINT8 Length,
	IN UINT8 NumOfFMSCs);

VOID WNM_InsertFMSStSubEelment(
	IN PRTMP_ADAPTER pAd,
	OUT PUCHAR pFrameBuf,
	OUT PULONG pFrameLen,
	IN WNM_FMS_STATUS_SUBELMENT FMSSubElement);

VOID InsertFMSRspSubElement(
	IN PRTMP_ADAPTER pAd,
	OUT PUCHAR pFrameBuf,
	OUT PULONG pFrameLen,
	IN WNM_FMS_RESPONSE_ELEMENT FMSReqElement);
#endif /* CONFIG_AP_SUPPORT */
VOID WNM_Init(IN PRTMP_ADAPTER pAd);

VOID IS_WNM_DMS(
	IN PRTMP_ADAPTER pAd, 
	IN PNDIS_PACKET pRxPacket, 
	IN PHEADER_802_11 pHeader);

VOID InsertDMSReqElement(
	IN PRTMP_ADAPTER pAd,
	OUT PUCHAR pFrameBuf,
	OUT PULONG pFrameLen,
	IN WNM_DMS_REQUEST_ELEMENT DMSReqElement);


VOID WNM_InsertDMS(
	IN PRTMP_ADAPTER pAd,
	OUT PUCHAR pFrameBuf,
	OUT PULONG pFrameLen,
	IN UINT8 Len,
	IN UCHAR DMSID,
	IN WNM_TCLAS wmn_tclas,
	IN ULONG IpAddr);

VOID WNM_InsertFMSReqSubEelment(
	IN PRTMP_ADAPTER pAd,
	OUT PUCHAR pFrameBuf,
	OUT PULONG pFrameLen,
	IN WNM_FMS_SUBELEMENT FMSSubElement,
	IN WNM_TCLAS wmn_tclas,
	IN ULONG IpAddr);

VOID InsertFMSReqElement(
	IN PRTMP_ADAPTER pAd,
	OUT PUCHAR pFrameBuf,
	OUT PULONG pFrameLen,
	IN WNM_FMS_REQUEST_ELEMENT FMSReqElement);

VOID WNM_InsertTFSReqSubEelment(
	IN PRTMP_ADAPTER pAd,
	OUT PUCHAR pFrameBuf,
	OUT PULONG pFrameLen,
	IN WNM_TFS_SUBELEMENT TFSSubElement,
	IN WNM_TCLAS wmn_tclas,
	IN ULONG IpAddr);


VOID InsertTFSReqElement(
	IN PRTMP_ADAPTER pAd,
	OUT PUCHAR pFrameBuf,
	OUT PULONG pFrameLen,
	IN WNM_TFS_REQUEST_ELEMENT FMSReqElement);


VOID WNM_InsertSleepModeEelment(
	IN PRTMP_ADAPTER pAd,
	OUT PUCHAR pFrameBuf,
	OUT PULONG pFrameLen,
	IN WNM_SLEEP_MODE_ELEMENT Sleep_Mode_Elmt);
	
VOID InsertRequestTyppe(
	IN PRTMP_ADAPTER pAd,
	OUT PUCHAR pFrameBuf,
	OUT PULONG pFrameLen,
	IN UCHAR RequestTyppe);


BOOLEAN RxDMSHandle(
	IN PRTMP_ADAPTER	pAd,
	IN PNDIS_PACKET		pPkt);

#endif /* DOT11V_WNM_SUPPORT */

#endif /* __WNM_H__ */







