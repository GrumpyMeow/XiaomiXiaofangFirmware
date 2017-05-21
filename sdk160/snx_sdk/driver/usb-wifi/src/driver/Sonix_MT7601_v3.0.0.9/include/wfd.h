/*
	Module Name:
	wfd.h
	
	Revision History:
	Who 			When			What
	--------		----------		----------------------------------------------
	
*/


#ifndef	__WFD_H__
#define	__WFD_H__

#ifdef WFD_SUPPORT

#include "rtmp_type.h"

INT Set_WfdEnable_Proc(
    IN  PRTMP_ADAPTER		pAd, 
    IN  PSTRING			arg);

#ifdef RT_CFG80211_SUPPORT
INT Set_WfdInsertIe_Proc
(
	IN	PRTMP_ADAPTER		pAd, 
	IN	PSTRING 		arg);
#endif /* RT_CFG80211_SUPPORT */

INT Set_WfdDeviceType_Proc(
    IN  PRTMP_ADAPTER		pAd, 
    IN  PSTRING			arg);

INT Set_WfdCouple_Proc(
    IN  PRTMP_ADAPTER		pAd, 
    IN  PSTRING			arg);

INT Set_WfdSessionAvailable_Proc(
    IN  PRTMP_ADAPTER		pAd, 
    IN  PSTRING			arg);

INT Set_WfdCP_Proc(
    IN  PRTMP_ADAPTER		pAd, 
    IN  PSTRING			arg);

INT	Set_WfdRtspPort_Proc(
    IN  PRTMP_ADAPTER		pAd, 
    IN  PSTRING			arg);

INT	Set_WfdMaxThroughput_Proc(
    IN  PRTMP_ADAPTER		pAd, 
    IN  PSTRING			arg);

INT Set_WfdLocalIp_Proc(
    IN  PRTMP_ADAPTER		pAd, 
    IN  PSTRING			arg);

INT Set_PeerRtspPort_Proc(
    IN  PRTMP_ADAPTER		pAd, 
    IN  PSTRING			arg);

VOID WfdMakeWfdIE(
	IN	PRTMP_ADAPTER	pAd,
	IN 	ULONG			WfdIeBitmap,
	OUT	PUCHAR			pOutBuf,
	OUT	PULONG			pIeLen);

ULONG InsertWfdSubelmtTlv(
	IN PRTMP_ADAPTER 	pAd,
	IN UCHAR			SubId,
	IN PUCHAR			pInBuffer,
	IN PUCHAR			pOutBuffer,
	IN UINT				Action);

VOID WfdParseSubElmt(
	IN PRTMP_ADAPTER 	pAd, 
	IN PWFD_ENTRY_INFO	pWfdEntryInfo,
	IN VOID 				*Msg, 
	IN ULONG 			MsgLen);

VOID WfdCfgInit(
	IN PRTMP_ADAPTER pAd);

#endif /* WFD_SUPPORT */
#endif /* __WFD_H__ */

