/*
    Module Name:
	ap_ioctl.c

    Abstract:
    IOCTL related subroutines

    Revision History:
    Who          When          What
    ---------    ----------    ----------------------------------------------
*/
#define RTMP_MODULE_OS

/*#include "rt_config.h" */
#include "rtmp_comm.h"
#include "rt_os_util.h"
#include "rt_os_net.h"
#include <linux/wireless.h>

struct iw_priv_args ap_privtab[] = {
{ RTPRIV_IOCTL_SET, 
/* 1024 --> 1024 + 512 */
/* larger size specific to allow 64 ACL MAC addresses to be set up all at once. */
  IW_PRIV_TYPE_CHAR | 1536, 0,
  "set"},  
{ RTPRIV_IOCTL_SHOW,
  IW_PRIV_TYPE_CHAR | 1024, 0,
  "show"},
{ RTPRIV_IOCTL_GSITESURVEY,
  IW_PRIV_TYPE_CHAR | 1024, IW_PRIV_TYPE_CHAR | 1024 ,
  "get_site_survey"}, 
#ifdef INF_AR9
  { RTPRIV_IOCTL_GET_AR9_SHOW,
  IW_PRIV_TYPE_CHAR | 1024, IW_PRIV_TYPE_CHAR | 1024 ,
  "ar9_show"}, 
#endif
  { RTPRIV_IOCTL_SET_WSCOOB,
  IW_PRIV_TYPE_CHAR | 1024, IW_PRIV_TYPE_CHAR | 1024 ,
  "set_wsc_oob"}, 
{ RTPRIV_IOCTL_GET_MAC_TABLE,
  IW_PRIV_TYPE_CHAR | 1024, IW_PRIV_TYPE_CHAR | 1024 ,
  "get_mac_table"}, 
{ RTPRIV_IOCTL_E2P,
  IW_PRIV_TYPE_CHAR | 1024, IW_PRIV_TYPE_CHAR | 1024,
  "e2p"},
#ifdef DBG
{ RTPRIV_IOCTL_BBP,
  IW_PRIV_TYPE_CHAR | 1024, IW_PRIV_TYPE_CHAR | 1024,
  "bbp"},
{ RTPRIV_IOCTL_MAC,
  IW_PRIV_TYPE_CHAR | 1024, IW_PRIV_TYPE_CHAR | 1024,
  "mac"},
{ RTPRIV_IOCTL_RF,
  IW_PRIV_TYPE_CHAR | 1024, IW_PRIV_TYPE_CHAR | 1024,
  "rf"},
#endif /* DBG */

#ifdef WSC_AP_SUPPORT
{ RTPRIV_IOCTL_WSC_PROFILE,
  IW_PRIV_TYPE_CHAR | 1024, IW_PRIV_TYPE_CHAR | 1024 ,
  "get_wsc_profile"},
#endif /* WSC_AP_SUPPORT */
{ RTPRIV_IOCTL_QUERY_BATABLE,
  IW_PRIV_TYPE_CHAR | 1024, IW_PRIV_TYPE_CHAR | 1024 ,
  "get_ba_table"},
{ RTPRIV_IOCTL_STATISTICS,
  IW_PRIV_TYPE_CHAR | 1024, IW_PRIV_TYPE_CHAR | 1024,
  "stat"}
};

#if 0
#ifdef ApCli_8021X_SUPPORT
int rt_apcli_ioctl_siwscan(struct net_device *dev,
			struct iw_request_info *info,
			struct iw_point *data, char *extra)
{
	PRTMP_ADAPTER pAd = NULL;
	int Status = NDIS_STATUS_SUCCESS;

	GET_PAD_FROM_NET_DEV(pAd, dev);

	UCHAR ifIndex;
	BOOLEAN apcliEn=FALSE;
	PAPCLI_STRUCT pApCliEntry = NULL;
	PMAC_TABLE_ENTRY pMacEntry = NULL;
	POS_COOKIE	pObj = (POS_COOKIE) pAd->OS_Cookie;

	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;

	ifIndex = pObj->ioctl_if;
	apcliEn = pAd->ApCfg.ApCliTab[ifIndex].Enable;

	if (!apcliEn)
		return FALSE;

	pApCliEntry = &pAd->ApCfg.ApCliTab[ifIndex];
	pMacEntry = &pAd->MacTab.Content[pApCliEntry->MacTabWCID];

	//check if the interface is down
	if(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_INTERRUPT_IN_USE))
	{
		DBGPRINT(RT_DEBUG_TRACE, ("INFO::Network is down!\n"));
		return -ENETDOWN;   
	}


#ifdef MESH_SUPPORT
	if (pAd->MeshTab.MeshOnly == TRUE)
		return Status;
#endif // MESH_SUPPORT //


	if ((pApCliEntry->WpaSupplicantUP & 0x7F) == WPA_SUPPLICANT_ENABLE)
	{
		pApCliEntry->WpaSupplicantScanCount++;
	}

    pApCliEntry->bScanReqIsFromWebUI = TRUE;
	do{


		if (((pApCliEntry->WpaSupplicantUP & 0x7F) == WPA_SUPPLICANT_ENABLE) &&
			(pApCliEntry->WpaSupplicantScanCount > 3))
		{
			DBGPRINT(RT_DEBUG_TRACE, ("!!! WpaSupplicantScanCount > 3\n"));
			Status = NDIS_STATUS_SUCCESS;
			break;
		}


		if ((OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_MEDIA_STATE_CONNECTED)) &&
			((pApCliEntry->AuthMode == Ndis802_11AuthModeWPA) || 
				(pApCliEntry->AuthMode == Ndis802_11AuthModeWPAPSK) ||
				(pApCliEntry->AuthMode == Ndis802_11AuthModeWPA2) ||
				(pApCliEntry->AuthMode == Ndis802_11AuthModeWPA2PSK))
				&&	(pMacEntry->PortSecured == WPA_802_1X_PORT_NOT_SECURED))
		{
			DBGPRINT(RT_DEBUG_TRACE, ("!!! Link UP, Port Not Secured! ignore this set::OID_802_11_BSSID_LIST_SCAN\n"));
			Status = NDIS_STATUS_SUCCESS;
			break;
		}

		ApSiteSurvey(pAd, NULL, SCAN_ACTIVE, TRUE);
	}while(0);
	return NDIS_STATUS_SUCCESS;
}


int rt_apcli_ioctl_siwfreq(struct net_device *dev,
			struct iw_request_info *info,
			struct iw_freq *freq, char *extra)
{
	PRTMP_ADAPTER pAd = NULL;
	int 	chan = -1;

	GET_PAD_FROM_NET_DEV(pAd, dev);
	UCHAR ifIndex;
	BOOLEAN apcliEn=FALSE;
	PAPCLI_STRUCT pApCliEntry = NULL;
	PMAC_TABLE_ENTRY pMacEntry = NULL;
	POS_COOKIE	pObj = (POS_COOKIE) pAd->OS_Cookie;

	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;

	ifIndex = pObj->ioctl_if;
	apcliEn = pAd->ApCfg.ApCliTab[ifIndex].Enable;

	if (!apcliEn)
		return FALSE;

	pApCliEntry = &pAd->ApCfg.ApCliTab[ifIndex];
	pMacEntry = &pAd->MacTab.Content[pApCliEntry->MacTabWCID];


    //check if the interface is down
    if(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_INTERRUPT_IN_USE))
    {
        DBGPRINT(RT_DEBUG_TRACE, ("INFO::Network is down!\n"));
        return -ENETDOWN;   
    }


	if (freq->e > 1)
		return -EINVAL;

	if((freq->e == 0) && (freq->m <= 1000))
		chan = freq->m;	// Setting by channel number 
	else
		MAP_KHZ_TO_CHANNEL_ID( (freq->m /100) , chan); // Setting by frequency - search the table , like 2.412G, 2.422G, 

    if (ChannelSanity(pAd, chan) == TRUE)
    {
	pAd->CommonCfg.Channel = chan;
	DBGPRINT(RT_DEBUG_ERROR, ("==>rt_ioctl_siwfreq::SIOCSIWFREQ[cmd=0x%x] (Channel=%d)\n", SIOCSIWFREQ, pAd->CommonCfg.Channel));
    }
    else
        return -EINVAL;
    
	return 0;
}

int rt_apcli_ioctl_giwfreq(struct net_device *dev,
		   struct iw_request_info *info,
		   struct iw_freq *freq, char *extra)
{
	PRTMP_ADAPTER pAd = NULL;
	UCHAR ch;
	ULONG	m = 2412000;

	GET_PAD_FROM_NET_DEV(pAd, dev);

	if (pAd == NULL)
	{
		/* if 1st open fail, pAd will be free;
		   So the net_dev->priv will be NULL in 2rd open */
		return -ENETDOWN;
	}

	UCHAR ifIndex;
	BOOLEAN apcliEn=FALSE;
	PAPCLI_STRUCT pApCliEntry = NULL;
	PMAC_TABLE_ENTRY pMacEntry = NULL;
	POS_COOKIE	pObj = (POS_COOKIE) pAd->OS_Cookie;

	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;

	ifIndex = pObj->ioctl_if;
	apcliEn = pAd->ApCfg.ApCliTab[ifIndex].Enable;

	if (!apcliEn)
		return FALSE;

	pApCliEntry = &pAd->ApCfg.ApCliTab[ifIndex];
	pMacEntry = &pAd->MacTab.Content[pApCliEntry->MacTabWCID];



	//check if the interface is down
	if(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_INTERRUPT_IN_USE))
	{
		DBGPRINT(RT_DEBUG_TRACE, ("INFO::Network is down!\n"));
		return -ENETDOWN;   
	}
#ifdef MESH_SUPPORT
	if (RT_DEV_PRIV_FLAGS_GET(dev) == INT_MESH)
		ch = pAd->MeshTab.MeshChannel;
	else
#endif // MESH_SUPPORT //
		ch = pAd->CommonCfg.Channel;

	DBGPRINT(RT_DEBUG_TRACE,("==>rt_ioctl_giwfreq  %d\n", ch));

	MAP_CHANNEL_ID_TO_KHZ(ch, m);
	freq->m = m * 100;
	freq->e = 1;
	freq->i = 0;
	
	return 0;
}

int rt_apcli_ioctl_siwmode(struct net_device *dev,
		   struct iw_request_info *info,
		   __u32 *mode, char *extra)
{
	return 0;
}


int rt_apcli_ioctl_giwmode(struct net_device *dev,
		   struct iw_request_info *info,
		   __u32 *mode, char *extra)
{
	PRTMP_ADAPTER pAd = NULL;

	GET_PAD_FROM_NET_DEV(pAd, dev);

	if (pAd == NULL)
	{
		/* if 1st open fail, pAd will be free;
		   So the net_dev->priv will be NULL in 2rd open */
		return -ENETDOWN;
	}

	//check if the interface is down
    if(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_INTERRUPT_IN_USE))
    {
        DBGPRINT(RT_DEBUG_TRACE, ("INFO::Network is down!\n"));
        return -ENETDOWN;   
    }

		*mode = IW_MODE_INFRA;

	DBGPRINT(RT_DEBUG_TRACE, ("==>rt_ioctl_giwmode(mode=%d)\n", *mode));
	return 0;
}

int rt_apcli_ioctl_siwsens(struct net_device *dev,
		   struct iw_request_info *info,
		   char *name, char *extra)
{
	PRTMP_ADAPTER pAd = NULL;

	GET_PAD_FROM_NET_DEV(pAd, dev);

	//check if the interface is down
    	if(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_INTERRUPT_IN_USE))
    	{
        	DBGPRINT(RT_DEBUG_TRACE, ("INFO::Network is down!\n"));
        	return -ENETDOWN;   
    	}

	return 0;
}

int rt_apcli_ioctl_giwsens(struct net_device *dev,
		   struct iw_request_info *info,
		   char *name, char *extra)
{
	return 0;
}

int rt_apcli_ioctl_giwrange(struct net_device *dev,
		   struct iw_request_info *info,
		   struct iw_point *data, char *extra)
{
	PRTMP_ADAPTER pAd = NULL;
	struct iw_range *range = (struct iw_range *) extra;
	u16 val;
	int i;

	GET_PAD_FROM_NET_DEV(pAd, dev);

	if (pAd == NULL)
	{
		/* if 1st open fail, pAd will be free;
		   So the net_dev->priv will be NULL in 2rd open */
		return -ENETDOWN;
	}

#ifndef NATIVE_WPA_SUPPLICANT_SUPPORT
	if(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_INTERRUPT_IN_USE))
	{
    	DBGPRINT(RT_DEBUG_TRACE, ("INFO::Network is down!\n"));
    	return -ENETDOWN;   
	}
#endif // NATIVE_WPA_SUPPLICANT_SUPPORT //

	DBGPRINT(RT_DEBUG_TRACE ,("===>rt_ioctl_giwrange\n"));
	data->length = sizeof(struct iw_range);
	memset(range, 0, sizeof(struct iw_range));

	range->txpower_capa = IW_TXPOW_DBM;

	if (INFRA_ON(pAd)||ADHOC_ON(pAd))
	{
		range->min_pmp = 1 * 1024;
		range->max_pmp = 65535 * 1024;
		range->min_pmt = 1 * 1024;
		range->max_pmt = 1000 * 1024;
		range->pmp_flags = IW_POWER_PERIOD;
		range->pmt_flags = IW_POWER_TIMEOUT;
		range->pm_capa = IW_POWER_PERIOD | IW_POWER_TIMEOUT |
			IW_POWER_UNICAST_R | IW_POWER_ALL_R;
	}

	range->we_version_compiled = WIRELESS_EXT;
	range->we_version_source = 14;

	range->retry_capa = IW_RETRY_LIMIT;
	range->retry_flags = IW_RETRY_LIMIT;
	range->min_retry = 0;
	range->max_retry = 255;

	range->num_channels =  pAd->ChannelListNum;

	val = 0;
	for (i = 1; i <= range->num_channels; i++) 
	{
		u32 m = 2412000;
		range->freq[val].i = pAd->ChannelList[i-1].Channel;
		MAP_CHANNEL_ID_TO_KHZ(pAd->ChannelList[i-1].Channel, m);
		range->freq[val].m = m * 100; /* OS_HZ */
		
		range->freq[val].e = 1;
		val++;
		if (val == IW_MAX_FREQUENCIES)
			break;
	}
	range->num_frequency = val;

	range->max_qual.qual = 100; /* what is correct max? This was not
					* documented exactly. At least
					* 69 has been observed. */
	range->max_qual.level = 0; /* dB */
	range->max_qual.noise = 0; /* dB */

	/* What would be suitable values for "average/typical" qual? */
	range->avg_qual.qual = 20;
	range->avg_qual.level = -60;
	range->avg_qual.noise = -95;
	range->sensitivity = 3;

	range->max_encoding_tokens = NR_WEP_KEYS;
	range->num_encoding_sizes = 2;
	range->encoding_size[0] = 5;
	range->encoding_size[1] = 13;

	range->min_rts = 0;
	range->max_rts = 2347;
	range->min_frag = 256;
	range->max_frag = 2346;

#if WIRELESS_EXT > 17
	/* IW_ENC_CAPA_* bit field */
	range->enc_capa = IW_ENC_CAPA_WPA | IW_ENC_CAPA_WPA2 | 
					IW_ENC_CAPA_CIPHER_TKIP | IW_ENC_CAPA_CIPHER_CCMP;
#endif

	return 0;
}

int rt_apcli_ioctl_siwap(struct net_device *dev,
		      struct iw_request_info *info,
		      struct sockaddr *ap_addr, char *extra)
{
	PRTMP_ADAPTER pAd = NULL;
    	NDIS_802_11_MAC_ADDRESS Bssid;
	UCHAR ifIndex;
	BOOLEAN apcliEn;
	POS_COOKIE pObj;
	PAPCLI_STRUCT pApCliEntry = NULL;


	GET_PAD_FROM_NET_DEV(pAd, dev);
	pObj = (POS_COOKIE) pAd->OS_Cookie;
	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;

	ifIndex = pObj->ioctl_if;
	apcliEn = pAd->ApCfg.ApCliTab[ifIndex].Enable;
	pApCliEntry = &pAd->ApCfg.ApCliTab[ifIndex];


	//check if the interface is down
	if(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_INTERRUPT_IN_USE))
	{
       	DBGPRINT(RT_DEBUG_TRACE, ("INFO::Network is down!\n"));
       	return -ENETDOWN;   
    	}

	if (NdisCmpMemory(ZERO_MAC_ADDR, ap_addr->sa_data, MAC_ADDR_LEN) == 0)
        return 0;

    // tell CNTL state machine to call NdisMSetInformationComplete() after completing
    // this request, because this request is initiated by NDIS.
    pAd->MlmeAux.CurrReqIsFromNdis = FALSE; 
	// Prevent to connect AP again in STAMlmePeriodicExec
	pAd->MlmeAux.AutoReconnectSsidLen= 32;

    memset(Bssid, 0, MAC_ADDR_LEN);
    memcpy(Bssid, ap_addr->sa_data, MAC_ADDR_LEN);

	if (MAC_ADDR_EQUAL(Bssid, ZERO_MAC_ADDR))
	{
		if(apcliEn == TRUE )
		{
			pAd->ApCfg.ApCliTab[ifIndex].Enable = FALSE;
			ApCliIfDown(pAd);
		}
	}
    else
	{
		// bring apcli interface down first
		if(apcliEn == TRUE )
		{
			pAd->ApCfg.ApCliTab[ifIndex].Enable = FALSE;
			ApCliIfDown(pAd);
			Set_ApCli_Bssid_Proc(pAd, Bssid);
		}
	}
    
    DBGPRINT(RT_DEBUG_TRACE, ("APCLI_IOCTL::SIOCSIWAP %02x:%02x:%02x:%02x:%02x:%02x\n",
        Bssid[0], Bssid[1], Bssid[2], Bssid[3], Bssid[4], Bssid[5]));

	return 0;
}

int rt_apcli_ioctl_giwap(struct net_device *dev,
		      struct iw_request_info *info,
		      struct sockaddr *ap_addr, char *extra)
{
	PRTMP_ADAPTER pAd = NULL;
	UCHAR ifIndex;
	BOOLEAN apcliEn;
	POS_COOKIE pObj;
	PAPCLI_STRUCT pApCliEntry = NULL;

	GET_PAD_FROM_NET_DEV(pAd, dev);

	if (pAd == NULL)
	{
		/* if 1st open fail, pAd will be free;
		   So the net_dev->priv will be NULL in 2rd open */
		return -ENETDOWN;
	}

	pObj = (POS_COOKIE) pAd->OS_Cookie;
	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;

	ifIndex = pObj->ioctl_if;
	apcliEn = pAd->ApCfg.ApCliTab[ifIndex].Enable;
	pApCliEntry = &pAd->ApCfg.ApCliTab[ifIndex];
	
	//check if the interface is down
    if(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_INTERRUPT_IN_USE))
    {
        DBGPRINT(RT_DEBUG_TRACE, ("INFO::Network is down!\n"));
        return -ENETDOWN;   
    }

		ap_addr->sa_family = ARPHRD_ETHER;
		memcpy(ap_addr->sa_data, pApCliEntry->CfgApCliBssid, ETH_ALEN);

	return 0;
}

#ifdef SIOCSIWMLME
int rt_apcli_ioctl_siwmlme(struct net_device *dev,
			   struct iw_request_info *info,
			   union iwreq_data *wrqu,
			   char *extra)
{
	PRTMP_ADAPTER   pAd = NULL;
	struct iw_mlme *pMlme = (struct iw_mlme *)wrqu->data.pointer;

	UCHAR ifIndex;
	BOOLEAN apcliEn;
	POS_COOKIE pObj;
	PAPCLI_STRUCT pApCliEntry = NULL;
	PULONG pCurrState;
	MLME_DISASSOC_REQ_STRUCT DisassocReq;
	MLME_DEAUTH_REQ_STRUCT	DeAuthFrame;

	DBGPRINT(RT_DEBUG_TRACE, ("====> %s\n", __FUNCTION__));	
	GET_PAD_FROM_NET_DEV(pAd, dev);

	if (pAd == NULL)
	{
		/* if 1st open fail, pAd will be free;
		   So the net_dev->priv will be NULL in 2rd open */
		return -ENETDOWN;
	}

	pObj = (POS_COOKIE) pAd->OS_Cookie;
	if (pObj->ioctl_if_type != INT_APCLI)
		return FALSE;

	ifIndex = pObj->ioctl_if;
	apcliEn = pAd->ApCfg.ApCliTab[ifIndex].Enable;
	pApCliEntry = &pAd->ApCfg.ApCliTab[ifIndex];
	



	//check if the interface is down
    if(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_INTERRUPT_IN_USE))
    {
       	DBGPRINT(RT_DEBUG_TRACE, ("INFO::Network is down!\n"));
        return -ENETDOWN;
	}

	if (pMlme == NULL)
		return -EINVAL;

	switch(pMlme->cmd)
	{
#ifdef IW_MLME_DEAUTH	
		case IW_MLME_DEAUTH:
			DBGPRINT(RT_DEBUG_TRACE, ("====> %s - IW_MLME_DEAUTH\n", __FUNCTION__));			                
				if (pObj->ioctl_if_type == INT_APCLI)
				{
					ifIndex = pObj->ioctl_if;
					apcliEn = pAd->ApCfg.ApCliTab[ifIndex].Enable;
					pApCliEntry = &pAd->ApCfg.ApCliTab[ifIndex];
					pCurrState = &pAd->ApCfg.ApCliTab[ifIndex].CtrlCurrState;
					if (ifIndex >= MAX_APCLI_NUM)
						return FALSE;

					// Fill in the related information
					DeAuthFrame.Reason = (USHORT)REASON_DEAUTH_STA_LEAVING;
					COPY_MAC_ADDR(DeAuthFrame.Addr, pAd->MlmeAux.Bssid);
					
					MlmeEnqueue(pAd, 
								  APCLI_AUTH_STATE_MACHINE, 
								  APCLI_MT2_MLME_DEAUTH_REQ, 
								  sizeof(MLME_DEAUTH_REQ_STRUCT),
								  &DeAuthFrame, 
								  ifIndex);

					if (pApCliEntry->Valid)
						ApCliLinkDown(pAd, ifIndex);

					// set the apcli interface be invalid.
					pApCliEntry->Valid = FALSE;

					// clear MlmeAux.Ssid and Bssid.
					NdisZeroMemory(pAd->MlmeAux.Bssid, MAC_ADDR_LEN);
					pAd->MlmeAux.SsidLen = 0;
					NdisZeroMemory(pAd->MlmeAux.Ssid, MAX_LEN_OF_SSID);
					pAd->MlmeAux.Rssi = 0;

					*pCurrState = APCLI_CTRL_DISCONNECTED;
				}
			break;
#endif // IW_MLME_DEAUTH //
#ifdef IW_MLME_DISASSOC
		case IW_MLME_DISASSOC:
			DBGPRINT(RT_DEBUG_TRACE, ("====> %s - IW_MLME_DISASSOC\n", __FUNCTION__));
			if (pObj->ioctl_if_type != INT_APCLI)
				return FALSE;

			ifIndex = pObj->ioctl_if;
			apcliEn = pAd->ApCfg.ApCliTab[ifIndex].Enable;
			pApCliEntry = &pAd->ApCfg.ApCliTab[ifIndex];
			pCurrState = &pAd->ApCfg.ApCliTab[ifIndex].CtrlCurrState;


			if (!apcliEn || ifIndex >= MAX_APCLI_NUM)
				return FALSE;
			
			DisassocParmFill(pAd, &DisassocReq, pAd->MlmeAux.Bssid, REASON_DISASSOC_STA_LEAVING);

			MlmeEnqueue(pAd, APCLI_ASSOC_STATE_MACHINE, APCLI_MT2_MLME_DISASSOC_REQ,
					sizeof(MLME_DISASSOC_REQ_STRUCT), &DisassocReq, ifIndex);
	
			if (pApCliEntry->Valid)
				ApCliLinkDown(pAd, ifIndex);

			// set the apcli interface be invalid.
			pApCliEntry->Valid = FALSE;

			// clear MlmeAux.Ssid and Bssid.
			NdisZeroMemory(pAd->MlmeAux.Bssid, MAC_ADDR_LEN);
			pAd->MlmeAux.SsidLen = 0;
			NdisZeroMemory(pAd->MlmeAux.Ssid, MAX_LEN_OF_SSID);
			pAd->MlmeAux.Rssi = 0;

			*pCurrState = APCLI_CTRL_DEASSOC;
			break;
#endif // IW_MLME_DISASSOC //
		default:
			DBGPRINT(RT_DEBUG_TRACE, ("====> %s - Unknow Command\n", __FUNCTION__));
			break;
	}
	
	return 0;
}
#endif // SIOCSIWMLME //


int rt_apcli_ioctl_siwessid(struct net_device *dev,
			 struct iw_request_info *info,
			 struct iw_point *data, char *essid)
{
	PRTMP_ADAPTER pAd = NULL;
	POS_COOKIE		pObj;
	GET_PAD_FROM_NET_DEV(pAd, dev);

	//check if the interface is down
	if(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_INTERRUPT_IN_USE))
	{
	       	DBGPRINT(RT_DEBUG_TRACE, ("INFO::Network is down!\n"));
	       	return -ENETDOWN;   
	}
	
	pObj = (POS_COOKIE) pAd->OS_Cookie;

	if (pAd->ApCfg.ApCliTab[pObj->ioctl_if].Valid == TRUE)
	{
		if (data->flags)
		{
			PSTRING	pSsidString = NULL;

			// Includes null character.
			if (data->length > (IW_ESSID_MAX_SIZE + 1)) 
				return -E2BIG;

			pSsidString = kmalloc(MAX_LEN_OF_SSID+1, MEM_ALLOC_FLAG);
			if (pSsidString)
	        {
				NdisZeroMemory(pSsidString, MAX_LEN_OF_SSID+1);
				NdisMoveMemory(pSsidString, essid, data->length);
				if (Set_ApCli_Ssid_Proc(pAd, pSsidString) == FALSE)
				{
					kfree(pSsidString);
					return -EINVAL;
				}
				kfree(pSsidString);
			}
			else
				return -ENOMEM;
			}
		else
	    {
			// ANY ssid
			if (Set_ApCli_Ssid_Proc(pAd, "") == FALSE)
				return -EINVAL;
	    }
	}
	return 0;
}

int rt_apcli_ioctl_giwessid(struct net_device *dev,
			 struct iw_request_info *info,
			 struct iw_point *data, char *essid)
{
	PRTMP_ADAPTER pAd = NULL;
	POS_COOKIE		pObj;
	GET_PAD_FROM_NET_DEV(pAd, dev);

	//check if the interface is down
	if(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_INTERRUPT_IN_USE))
	{
	       	DBGPRINT(RT_DEBUG_TRACE, ("INFO::Network is down!\n"));
	       	return -ENETDOWN;   
	}
	
	pObj = (POS_COOKIE) pAd->OS_Cookie;

	if (pAd->ApCfg.ApCliTab[pObj->ioctl_if].Valid == TRUE)
	{
		data->flags = 1;	
		data->length = pAd->ApCfg.ApCliTab[pObj->ioctl_if].SsidLen;
		memcpy(essid, pAd->ApCfg.ApCliTab[pObj->ioctl_if].Ssid, pAd->ApCfg.ApCliTab[pObj->ioctl_if].SsidLen);
	}
	return 0;
}

int rt_apcli_ioctl_giwrts(struct net_device *dev,
		       struct iw_request_info *info,
		       struct iw_param *rts, char *extra)
{
	PRTMP_ADAPTER pAd = NULL;

	GET_PAD_FROM_NET_DEV(pAd, dev);

	if (pAd == NULL)
	{
		/* if 1st open fail, pAd will be free;
		   So the net_dev->priv will be NULL in 2rd open */
		return -ENETDOWN;
	}

	//check if the interface is down
    	if(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_INTERRUPT_IN_USE))
    	{
      		DBGPRINT(RT_DEBUG_TRACE, ("INFO::Network is down!\n"));
        	return -ENETDOWN;   
    	}

	rts->value = pAd->CommonCfg.RtsThreshold;
	rts->disabled = (rts->value == MAX_RTS_THRESHOLD);
	rts->fixed = 1;

	return 0;
}

int rt_apcli_ioctl_giwfrag(struct net_device *dev,
			struct iw_request_info *info,
			struct iw_param *frag, char *extra)
{
	PRTMP_ADAPTER pAd = NULL;

	GET_PAD_FROM_NET_DEV(pAd, dev);

	if (pAd == NULL)
	{
		/* if 1st open fail, pAd will be free;
		   So the net_dev->priv will be NULL in 2rd open */
		return -ENETDOWN;
	}

	//check if the interface is down
    	if(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_INTERRUPT_IN_USE))
    	{
      		DBGPRINT(RT_DEBUG_TRACE, ("INFO::Network is down!\n"));
        	return -ENETDOWN;   
    	}
		
	frag->value = pAd->CommonCfg.FragmentThreshold;
	frag->disabled = (frag->value == MAX_FRAG_THRESHOLD);
	frag->fixed = 1;

	return 0;
}


int
rt_apcli_ioctl_giwencode(struct net_device *dev,
			  struct iw_request_info *info,
			  struct iw_point *erq, char *key)
{
	int kid;
	PRTMP_ADAPTER pAd = NULL;
	POS_COOKIE		pObj;

	GET_PAD_FROM_NET_DEV(pAd, dev);

	if (pAd == NULL)
	{
		/* if 1st open fail, pAd will be free;
		   So the net_dev->priv will be NULL in 2rd open */
		return -ENETDOWN;
	}

	if (RT_DEV_PRIV_FLAGS_GET(dev) != INT_APCLI)
	{
		/* if 1st open fail, pAd will be free;
		   So the net_dev->priv will be NULL in 2rd open */
		return -ENETDOWN;
	}
	//check if the interface is down
	if(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_INTERRUPT_IN_USE))
	{
  		DBGPRINT(RT_DEBUG_TRACE, ("INFO::Network is down!\n"));
    		return -ENETDOWN;   
	}
	pObj = (POS_COOKIE) pAd->OS_Cookie;
	kid = erq->flags & IW_ENCODE_INDEX;
	DBGPRINT(RT_DEBUG_TRACE, ("===>rt_apcli_ioctl_giwencode %d\n", erq->flags & IW_ENCODE_INDEX));


	if (pAd->ApCfg.ApCliTab[pObj->ioctl_if].Valid == TRUE)
	{
		if (pAd->ApCfg.ApCliTab[pObj->ioctl_if].WepStatus == Ndis802_11WEPDisabled)
		{
			erq->length = 0;
			erq->flags = IW_ENCODE_DISABLED;
		} 
		else if ((kid > 0) && (kid <=4))
		{

			// copy wep key
			erq->flags = kid ;			/* NB: base 1 */
			if (erq->length > pAd->ApCfg.ApCliTab[pObj->ioctl_if].SharedKey[kid-1].KeyLen)
				erq->length = pAd->ApCfg.ApCliTab[pObj->ioctl_if].SharedKey[kid-1].KeyLen;
			memcpy(key, pAd->ApCfg.ApCliTab[pObj->ioctl_if].SharedKey[kid-1].Key, erq->length);
			//erq->flags |= IW_ENCODE_ENABLED;	/* XXX */
			if (pAd->ApCfg.ApCliTab[pObj->ioctl_if].AuthMode == Ndis802_11AuthModeShared)
				erq->flags |= IW_ENCODE_RESTRICTED;		/* XXX */
			else
				erq->flags |= IW_ENCODE_OPEN;		/* XXX */
			
		}
		else if (kid == 0)
		{
			if (pAd->ApCfg.ApCliTab[pObj->ioctl_if].AuthMode == Ndis802_11AuthModeShared)
				erq->flags |= IW_ENCODE_RESTRICTED;		/* XXX */
			else
				erq->flags |= IW_ENCODE_OPEN;		/* XXX */
			erq->length = pAd->ApCfg.ApCliTab[pObj->ioctl_if].SharedKey[kid-1].KeyLen;
			memcpy(key, pAd->ApCfg.ApCliTab[pObj->ioctl_if].SharedKey[kid-1].Key, erq->length);
			// copy default key ID
			if (pAd->ApCfg.ApCliTab[pObj->ioctl_if].AuthMode == Ndis802_11AuthModeShared)
				erq->flags |= IW_ENCODE_RESTRICTED;		/* XXX */
			else
				erq->flags |= IW_ENCODE_OPEN;		/* XXX */
			erq->flags = pAd->ApCfg.ApCliTab[pObj->ioctl_if].DefaultKeyId + 1;			/* NB: base 1 */
			erq->flags |= IW_ENCODE_ENABLED;	/* XXX */
		}
	}
	return 0;

}


#define MAX_WEP_KEY_SIZE 13
#define MIN_WEP_KEY_SIZE 5
int rt_apcli_ioctl_siwencode(struct net_device *dev,
			  struct iw_request_info *info,
			  struct iw_point *erq, char *extra)
{
	PRTMP_ADAPTER pAd = NULL;
	POS_COOKIE		pObj;
	MAC_TABLE_ENTRY  *pEntry;
	GET_PAD_FROM_NET_DEV(pAd, dev);

	if (pAd == NULL)
	{
		/* if 1st open fail, pAd will be free;
		   So the net_dev->priv will be NULL in 2rd open */
		return -ENETDOWN;
	}

	if (RT_DEV_PRIV_FLAGS_GET(dev) != INT_APCLI)
	{
		/* if 1st open fail, pAd will be free;
		   So the net_dev->priv will be NULL in 2rd open */
		return -ENETDOWN;
	}

	//check if the interface is down
    	if(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_INTERRUPT_IN_USE))
    	{
      		DBGPRINT(RT_DEBUG_TRACE, ("INFO::Network is down!\n"));
        	return -ENETDOWN;   
    	}
		
	pObj = (POS_COOKIE) pAd->OS_Cookie;

	if (pAd->ApCfg.ApCliTab[pObj->ioctl_if].Valid == TRUE)
	{
			if ((erq->length == 0) &&
		        (erq->flags & IW_ENCODE_DISABLED))
			{
				pAd->ApCfg.ApCliTab[pObj->ioctl_if].PairCipher = Ndis802_11WEPDisabled;
				pAd->ApCfg.ApCliTab[pObj->ioctl_if].GroupCipher = Ndis802_11WEPDisabled;
				pAd->ApCfg.ApCliTab[pObj->ioctl_if].WepStatus = Ndis802_11WEPDisabled;
		       	 pAd->ApCfg.ApCliTab[pObj->ioctl_if].AuthMode = Ndis802_11AuthModeOpen;
		        	goto done;
			}
			else if (erq->flags & IW_ENCODE_RESTRICTED || erq->flags & IW_ENCODE_OPEN)
			{
			    //pAd->StaCfg.PortSecured = WPA_802_1X_PORT_SECURED;
				//STA_PORT_SECURED(pAd);

				pEntry = &pAd->MacTab.Content[pAd->ApCfg.ApCliTab[pObj->ioctl_if].MacTabWCID]; 

				if(!IS_ENTRY_APCLI(pEntry))
					return -EINVAL;
				else
				{
					NdisAcquireSpinLock(&pAd->MacTabLock);
					pEntry->PortSecured=WPA_802_1X_PORT_SECURED;
					pEntry->PrivacyFilter=Ndis802_11PrivFilterAcceptAll;
					NdisReleaseSpinLock(&pAd->MacTabLock);
					pAd->ApCfg.ApCliTab[pObj->ioctl_if].PairCipher = Ndis802_11WEPEnabled;
					pAd->ApCfg.ApCliTab[pObj->ioctl_if].GroupCipher = Ndis802_11WEPEnabled;
					pAd->ApCfg.ApCliTab[pObj->ioctl_if].WepStatus = Ndis802_11WEPEnabled;
					if (erq->flags & IW_ENCODE_RESTRICTED)
						pAd->ApCfg.ApCliTab[pObj->ioctl_if].AuthMode = Ndis802_11AuthModeShared;
			    		else
						pAd->ApCfg.ApCliTab[pObj->ioctl_if].AuthMode = Ndis802_11AuthModeOpen;
				}
			}
		    
		    if (erq->length > 0) 
			{
				int keyIdx = (erq->flags & IW_ENCODE_INDEX) - 1;
				/* Check the size of the key */
				if (erq->length > MAX_WEP_KEY_SIZE) 
				{
					return -EINVAL;
				}
				/* Check key index */
				if ((keyIdx < 0) || (keyIdx >= NR_WEP_KEYS))
		        {
		            DBGPRINT(RT_DEBUG_TRACE ,("==>rt_ioctl_siwencode::Wrong keyIdx=%d! Using default key instead (%d)\n", 
		                                        keyIdx, pAd->ApCfg.ApCliTab[pObj->ioctl_if].DefaultKeyId));
		            
		            //Using default key
					keyIdx = pAd->ApCfg.ApCliTab[pObj->ioctl_if].DefaultKeyId;   
		        }
				else
					pAd->ApCfg.ApCliTab[pObj->ioctl_if].DefaultKeyId = keyIdx;

		        NdisZeroMemory(pAd->SharedKey[BSS0][keyIdx].Key,  16);
				
				if (erq->length == MAX_WEP_KEY_SIZE)
		        {      
					pAd->ApCfg.ApCliTab[pObj->ioctl_if].SharedKey[keyIdx].KeyLen = MAX_WEP_KEY_SIZE;
		           		 pAd->ApCfg.ApCliTab[pObj->ioctl_if].SharedKey[keyIdx].CipherAlg = CIPHER_WEP128;
				}
				else if (erq->length == MIN_WEP_KEY_SIZE)
		        {      
		            pAd->ApCfg.ApCliTab[pObj->ioctl_if].SharedKey[keyIdx].KeyLen = MIN_WEP_KEY_SIZE;
		            pAd->ApCfg.ApCliTab[pObj->ioctl_if].SharedKey[keyIdx].CipherAlg = CIPHER_WEP64;
				}
				else
					/* Disable the key */
					pAd->ApCfg.ApCliTab[pObj->ioctl_if].SharedKey[keyIdx].KeyLen = 0;

				/* Check if the key is not marked as invalid */
				if(!(erq->flags & IW_ENCODE_NOKEY)) 
				{
					/* Copy the key in the driver */
					NdisMoveMemory(pAd->ApCfg.ApCliTab[pObj->ioctl_if].SharedKey[keyIdx].Key, extra, erq->length);
		        }
			} 
		    else 
					{
				/* Do we want to just set the transmit key index ? */
				int index = (erq->flags & IW_ENCODE_INDEX) - 1;
				if ((index >= 0) && (index < 4)) 
		        {      
					pAd->ApCfg.ApCliTab[pObj->ioctl_if].DefaultKeyId = index;
		            }
		        else
					/* Don't complain if only change the mode */
				if(!erq->flags & IW_ENCODE_MODE) 
				{
						return -EINVAL;
				}
			}
		}
		
done:
    DBGPRINT(RT_DEBUG_TRACE ,("==>rt_apcli_ioctl_siwencode::erq->flags=%x\n",erq->flags));
	DBGPRINT(RT_DEBUG_TRACE ,("==>rt_apcli_ioctl_siwencode::ApCli(%d) AuthMode=%x\n",pObj->ioctl_if,pAd->ApCfg.ApCliTab[pObj->ioctl_if].AuthMode));
	DBGPRINT(RT_DEBUG_TRACE ,("==>rt_apcli_ioctl_siwencode::ApCli(%d) DefaultKeyId=%x, KeyLen = %d\n",pObj->ioctl_if,pAd->ApCfg.ApCliTab[pObj->ioctl_if].DefaultKeyId , pAd->ApCfg.ApCliTab[pObj->ioctl_if].SharedKey[pAd->ApCfg.ApCliTab[pObj->ioctl_if].DefaultKeyId].KeyLen));
	DBGPRINT(RT_DEBUG_TRACE ,("==>rt_apcli_ioctl_siwencode::ApCli(%d) WepStatus=%x\n",pObj->ioctl_if, pAd->ApCfg.ApCliTab[pObj->ioctl_if].WepStatus));
	return 0;
}

#if 0
int rt_apcli_ioctl_siwap(struct net_device *dev,
		      struct iw_request_info *info,
		      struct sockaddr *ap_addr, char *extra)
{
	PRTMP_ADAPTER pAd = NULL;
    	NDIS_802_11_MAC_ADDRESS Bssid;
	POS_COOKIE		pObj;
	MAC_TABLE_ENTRY  *pEntry;

	GET_PAD_FROM_NET_DEV(pAd, dev);

	if (pAd == NULL)
	{
		/* if 1st open fail, pAd will be free;
		   So the net_dev->priv will be NULL in 2rd open */
		return -ENETDOWN;
	}

	if (RT_DEV_PRIV_FLAGS_GET(dev) != INT_APCLI)
	{
		/* if 1st open fail, pAd will be free;
		   So the net_dev->priv will be NULL in 2rd open */
		return -ENETDOWN;
	}

	//check if the interface is down
	if(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_INTERRUPT_IN_USE))
	{
       	DBGPRINT(RT_DEBUG_TRACE, ("INFO::Network is down!\n"));
       	return -ENETDOWN;   
    	}
	pObj = (POS_COOKIE) pAd->OS_Cookie;

	if (pAd->ApCfg.ApCliTab[pObj->ioctl_if].Valid == TRUE)
	{
			if (pAd->Mlme.CntlMachine.CurrState != CNTL_IDLE)
		    	{
		       	 RTMP_MLME_RESET_STATE_MACHINE(pAd);
		        	DBGPRINT(RT_DEBUG_TRACE, ("!!! MLME busy, reset MLME state machine !!!\n"));
		    	}

			if (NdisCmpMemory(ZERO_MAC_ADDR, ap_addr->sa_data, MAC_ADDR_LEN) == 0)
		        return 0;

		    // tell CNTL state machine to call NdisMSetInformationComplete() after completing
		    // this request, because this request is initiated by NDIS.
		    	//pAd->MlmeAux.CurrReqIsFromNdis = FALSE; 
			// Prevent to connect AP again in STAMlmePeriodicExec
			//pAd->MlmeAux.AutoReconnectSsidLen= 32;

		    memset(Bssid, 0, MAC_ADDR_LEN);
		    memcpy(Bssid, ap_addr->sa_data, MAC_ADDR_LEN);

			if (MAC_ADDR_EQUAL(Bssid, ZERO_MAC_ADDR))
			{
					ApCliLinkDown(pAd, pObj->ioctl_if);	
			}
		    	else
			{
					Set_ApCli_Bssid_Proc(pAd, Bssid);
			}
		    
		    DBGPRINT(RT_DEBUG_TRACE, ("IOCTL::APCLI_SIOCSIWAP %02x:%02x:%02x:%02x:%02x:%02x\n",
		        Bssid[0], Bssid[1], Bssid[2], Bssid[3], Bssid[4], Bssid[5]));
	}
	return 0;
}
#endif
static const iw_handler rt_apcli_handler[] =
{
	(iw_handler) NULL,			            /* SIOCSIWCOMMIT */
	(iw_handler) rt_apcli_ioctl_siwscan,			/* SIOCGIWNAME   */
	(iw_handler) NULL,			            /* SIOCSIWNWID   */
	(iw_handler) NULL,			            /* SIOCGIWNWID   */
	(iw_handler) rt_apcli_ioctl_siwfreq,		    /* SIOCSIWFREQ   */
	(iw_handler) rt_apcli_ioctl_giwfreq,		    /* SIOCGIWFREQ   */
	(iw_handler) NULL,	    /* SIOCSIWMODE   */
	(iw_handler) rt_apcli_ioctl_giwmode,		    /* SIOCGIWMODE   */
	(iw_handler) NULL,		                /* SIOCSIWSENS   */
	(iw_handler) NULL,		                /* SIOCGIWSENS   */
	(iw_handler) NULL /* not used */,		/* SIOCSIWRANGE  */
	(iw_handler) rt_apcli_ioctl_giwrange,		    /* SIOCGIWRANGE  */
	(iw_handler) NULL /* not used */,		/* SIOCSIWPRIV   */
	(iw_handler) NULL /* kernel code */,    /* SIOCGIWPRIV   */
	(iw_handler) NULL /* not used */,		/* SIOCSIWSTATS  */
	(iw_handler) rt28xx_get_wireless_stats /* kernel code */,    /* SIOCGIWSTATS  */
	(iw_handler) NULL,		                /* SIOCSIWSPY    */
	(iw_handler) NULL,		                /* SIOCGIWSPY    */
	(iw_handler) NULL,				        /* SIOCSIWTHRSPY */
	(iw_handler) NULL,				        /* SIOCGIWTHRSPY */
	(iw_handler) rt_apcli_ioctl_siwap,            /* SIOCSIWAP     */
	(iw_handler) rt_apcli_ioctl_giwap,		    /* SIOCGIWAP     */
#ifdef SIOCSIWMLME
	(iw_handler) rt_apcli_ioctl_siwmlme,	        /* SIOCSIWMLME   */
#else
	(iw_handler) NULL,				        /* SIOCSIWMLME */
#endif // SIOCSIWMLME //
	(iw_handler) NULL,		    /* SIOCGIWAPLIST */
#ifdef SIOCGIWSCAN
	(iw_handler) rt_apcli_ioctl_siwscan,		    /* SIOCSIWSCAN   */
	(iw_handler) NULL,		    /* SIOCGIWSCAN   */
#else
	(iw_handler) NULL,				        /* SIOCSIWSCAN   */
	(iw_handler) NULL,				        /* SIOCGIWSCAN   */
#endif /* SIOCGIWSCAN */
	(iw_handler) rt_apcli_ioctl_siwessid,		    /* SIOCSIWESSID  */
	(iw_handler) rt_apcli_ioctl_giwessid,		    /* SIOCGIWESSID  */
	(iw_handler) NULL,		    /* SIOCSIWNICKN  */
	(iw_handler) NULL,		    /* SIOCGIWNICKN  */
	(iw_handler) NULL,				        /* -- hole --    */
	(iw_handler) NULL,				        /* -- hole --    */
	(iw_handler) NULL,          /* SIOCSIWRATE   */
	(iw_handler) NULL,          /* SIOCGIWRATE   */
	(iw_handler) NULL,		    /* SIOCSIWRTS    */
	(iw_handler) rt_apcli_ioctl_giwrts,		    /* SIOCGIWRTS    */
	(iw_handler) NULL,		    /* SIOCSIWFRAG   */
	(iw_handler) rt_apcli_ioctl_giwfrag,		    /* SIOCGIWFRAG   */
	(iw_handler) NULL,		                /* SIOCSIWTXPOW  */
	(iw_handler) NULL,		                /* SIOCGIWTXPOW  */
	(iw_handler) NULL,		                /* SIOCSIWRETRY  */
	(iw_handler) NULL,		                /* SIOCGIWRETRY  */
	(iw_handler) rt_apcli_ioctl_siwencode,		/* SIOCSIWENCODE */
	(iw_handler) rt_apcli_ioctl_giwencode,		/* SIOCGIWENCODE */
	(iw_handler) NULL,		                /* SIOCSIWPOWER  */
	(iw_handler) NULL,		                /* SIOCGIWPOWER  */
	(iw_handler) NULL,						/* -- hole -- */	
	(iw_handler) NULL,						/* -- hole -- */
#if WIRELESS_EXT > 17	
    (iw_handler) NULL,         /* SIOCSIWGENIE  */
	(iw_handler) NULL,         /* SIOCGIWGENIE  */
	(iw_handler) NULL,		    /* SIOCSIWAUTH   */
	(iw_handler) NULL,		    /* SIOCGIWAUTH   */
	(iw_handler) NULL,	    /* SIOCSIWENCODEEXT */
	(iw_handler) NULL,		/* SIOCGIWENCODEEXT */
	(iw_handler) NULL,         /* SIOCSIWPMKSA  */
#endif
};



static const iw_handler rt_apcli_priv_handlers[] = {
	(iw_handler) NULL, /* + 0x00 */
	(iw_handler) NULL, /* + 0x01 */
#ifndef CONFIG_AP_SUPPORT
	(iw_handler) rt_ioctl_setparam, /* + 0x02 */
#else
	(iw_handler) NULL, /* + 0x02 */
#endif // CONFIG_AP_SUPPORT //
#ifdef DBG	
	(iw_handler) NULL, /* + 0x03 */	
#else
	(iw_handler) NULL, /* + 0x03 */
#endif
	(iw_handler) NULL, /* + 0x04 */
	(iw_handler) NULL, /* + 0x05 */
	(iw_handler) NULL, /* + 0x06 */
	(iw_handler) NULL, /* + 0x07 */
	(iw_handler) NULL, /* + 0x08 */
	(iw_handler) NULL, /* + 0x09 */
	(iw_handler) NULL, /* + 0x0A */
	(iw_handler) NULL, /* + 0x0B */
	(iw_handler) NULL, /* + 0x0C */
	(iw_handler) NULL, /* + 0x0D */
	(iw_handler) NULL, /* + 0x0E */
	(iw_handler) NULL, /* + 0x0F */
	(iw_handler) NULL, /* + 0x10 */
	(iw_handler) NULL, /* + 0x11 */
    (iw_handler) NULL, /* + 0x12 */
	(iw_handler) NULL, /* + 0x13 */
#ifdef WSC_STA_SUPPORT	
	(iw_handler) rt_private_set_wsc_u32_item, /* + 0x14 */
#else
    (iw_handler) NULL, /* + 0x14 */
#endif // WSC_STA_SUPPORT //
	(iw_handler) NULL, /* + 0x15 */
#ifdef WSC_STA_SUPPORT	
	(iw_handler) rt_private_set_wsc_string_item, /* + 0x16 */
#else
    (iw_handler) NULL, /* + 0x16 */
#endif // WSC_STA_SUPPORT //
	(iw_handler) NULL, /* + 0x17 */
	(iw_handler) NULL, /* + 0x18 */
};

#endif /*ApCli_8021X_SUPPORT*/
#endif

#ifdef CONFIG_APSTA_MIXED_SUPPORT
const struct iw_handler_def rt28xx_ap_iw_handler_def =
{
#define	N(a)	(sizeof (a) / sizeof (a[0]))
	.private_args	= (struct iw_priv_args *) ap_privtab,
	.num_private_args	= N(ap_privtab),
#if IW_HANDLER_VERSION >= 7
	.get_wireless_stats = rt28xx_get_wireless_stats,
#endif 
};
#endif /* CONFIG_APSTA_MIXED_SUPPORT */


INT rt28xx_ap_ioctl(
	IN	struct net_device	*net_dev, 
	IN	OUT	struct ifreq	*rq, 
	IN	INT					cmd)
{
	VOID			*pAd = NULL;
    struct iwreq	*wrqin = (struct iwreq *) rq;
	RTMP_IOCTL_INPUT_STRUCT rt_wrq, *wrq = &rt_wrq;
    INT				Status = NDIS_STATUS_SUCCESS;
    USHORT			subcmd; /*, index; */
/*	POS_COOKIE		pObj; */
	INT			apidx=0;
	UINT32		org_len;
	RT_CMD_AP_IOCTL_CONFIG IoctlConfig, *pIoctlConfig = &IoctlConfig;

	GET_PAD_FROM_NET_DEV(pAd, net_dev);	
/*	pObj = (POS_COOKIE) pAd->OS_Cookie; */

	if (pAd == NULL)
	{
		/* if 1st open fail, pAd will be free;
		   So the net_dev->priv will be NULL in 2rd open */
		return -ENETDOWN;
	}

	wrq->u.data.pointer = wrqin->u.data.pointer;
	wrq->u.data.length = wrqin->u.data.length;
	org_len = wrq->u.data.length;

	pIoctlConfig->Status = 0;
	pIoctlConfig->net_dev = net_dev;
	pIoctlConfig->priv_flags = RT_DEV_PRIV_FLAGS_GET(net_dev);
	pIoctlConfig->pCmdData = wrqin->u.data.pointer;
	pIoctlConfig->CmdId_RTPRIV_IOCTL_SET = RTPRIV_IOCTL_SET;
	pIoctlConfig->name = net_dev->name;
	pIoctlConfig->apidx = 0;

	if ((cmd != SIOCGIWPRIV) &&
		RTMP_AP_IoctlHandle(pAd, NULL, CMD_RTPRIV_IOCTL_PREPARE, 0,
							pIoctlConfig, 0) != NDIS_STATUS_SUCCESS)
	{
		/* prepare error */
		Status = pIoctlConfig->Status;
		goto LabelExit;
	}

	apidx = pIoctlConfig->apidx;
	
    /*+ patch for SnapGear Request even the interface is down */
    if(cmd== SIOCGIWNAME){
	    DBGPRINT(RT_DEBUG_TRACE, ("IOCTL::SIOCGIWNAME\n"));

	RTMP_COM_IoctlHandle(pAd, NULL, CMD_RTPRIV_IOCTL_SIOCGIWNAME, 0, wrqin->u.name, 0);

#if 0 /* 20090602 */
#ifdef RTMP_MAC_PCI
	    strcpy(wrqin->u.name, "RT2860 SoftAP");
#endif /* RTMP_MAC_PCI */
#ifdef RT35xx
			if (IS_RT3572(pAd))
				strcpy(wrqin->u.name, "RT3572 SoftAP");
			else
#endif /* RT35xx */
	    strcpy(wrqin->u.name, "RT2870 SoftAP");
#endif /* 0 */
	    return Status;
    }/*- patch for SnapGear */

#if 0 /* os abl move */
    if((RT_DEV_PRIV_FLAGS_GET(net_dev) == INT_MAIN) && !RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_INTERRUPT_IN_USE))
    {
#ifdef CONFIG_APSTA_MIXED_SUPPORT
	if (wrqin->u.data.pointer == NULL)
		return Status;

	if (cmd == RTPRIV_IOCTL_SET)
	{
		if (strstr(wrqin->u.data.pointer, "OpMode") == NULL)
			return -ENETDOWN;
	}
	else
#endif /* CONFIG_APSTA_MIXED_SUPPORT */
		return -ENETDOWN;
    }

    /* determine this ioctl command is comming from which interface. */
    if (RT_DEV_PRIV_FLAGS_GET(net_dev) == INT_MAIN)
    {
		pObj->ioctl_if_type = INT_MAIN;
        pObj->ioctl_if = MAIN_MBSSID;
/*        DBGPRINT(RT_DEBUG_INFO, ("rt28xx_ioctl I/F(ra%d)(flags=%d): cmd = 0x%08x\n", pObj->ioctl_if, RT_DEV_PRIV_FLAGS_GET(net_dev), cmd)); */
    }
    else if (RT_DEV_PRIV_FLAGS_GET(net_dev) == INT_MBSSID)
    {
		pObj->ioctl_if_type = INT_MBSSID;
/*    	if (!RTMPEqualMemory(net_dev->name, pAd->net_dev->name, 3))  // for multi-physical card, no MBSSID */
		if (strcmp(net_dev->name, pAd->net_dev->name) != 0) /* sample */
    	{
	        for (index = 1; index < pAd->ApCfg.BssidNum; index++)
	    	{
	    	    if (pAd->ApCfg.MBSSID[index].MSSIDDev == net_dev)
	    	    {
	    	        pObj->ioctl_if = index;
	    	        
/*	    	        DBGPRINT(RT_DEBUG_INFO, ("rt28xx_ioctl I/F(ra%d)(flags=%d): cmd = 0x%08x\n", index, RT_DEV_PRIV_FLAGS_GET(net_dev), cmd)); */
	    	        break;
	    	    }
	    	}
	        /* Interface not found! */
	        if(index == pAd->ApCfg.BssidNum)
	        {
/*	        	DBGPRINT(RT_DEBUG_ERROR, ("rt28xx_ioctl can not find I/F\n")); */
	            return -ENETDOWN;
	        }
	    }
	    else    /* ioctl command from I/F(ra0) */
	    {
			GET_PAD_FROM_NET_DEV(pAd, net_dev);	
    	    pObj->ioctl_if = MAIN_MBSSID;
/*	        DBGPRINT(RT_DEBUG_ERROR, ("rt28xx_ioctl can not find I/F and use default: cmd = 0x%08x\n", cmd)); */
	    }
        MBSS_MR_APIDX_SANITY_CHECK(pAd, pObj->ioctl_if);
        apidx = pObj->ioctl_if;
    }
#ifdef WDS_SUPPORT
	else if (RT_DEV_PRIV_FLAGS_GET(net_dev) == INT_WDS)
	{
		pObj->ioctl_if_type = INT_WDS;
		for(index = 0; index < MAX_WDS_ENTRY; index++)
		{
			if (pAd->WdsTab.WdsEntry[index].dev == net_dev)
			{
				pObj->ioctl_if = index;

#ifdef RELEASE_EXCLUDE
				DBGPRINT(RT_DEBUG_INFO, ("rt28xx_ioctl I/F(wds%d)(flags=%x): cmd = 0x%08x\n", pObj->ioctl_if, RT_DEV_PRIV_FLAGS_GET(net_dev), cmd));
#endif /* RELEASE_EXCLUDE */
				break;
			}
			
			if(index == MAX_WDS_ENTRY)
			{
				DBGPRINT(RT_DEBUG_ERROR, ("rt28xx_ioctl can not find wds I/F\n"));
				return -ENETDOWN;
			}
		}
	}
#endif /* WDS_SUPPORT */
#ifdef APCLI_SUPPORT
	else if (RT_DEV_PRIV_FLAGS_GET(net_dev) == INT_APCLI)
	{
		pObj->ioctl_if_type = INT_APCLI;
		for (index = 0; index < MAX_APCLI_NUM; index++)
		{
			if (pAd->ApCfg.ApCliTab[index].dev == net_dev)
			{
				pObj->ioctl_if = index;

#ifdef RELEASE_EXCLUDE
				DBGPRINT(RT_DEBUG_INFO, ("rt28xx_ioctl I/F(apcli%d)(flags=%x): cmd = 0x%08x\n", pObj->ioctl_if, RT_DEV_PRIV_FLAGS_GET(net_dev), cmd));
#endif /* RELEASE_EXCLUDE */
				break;
			}

			if(index == MAX_APCLI_NUM)
			{
				DBGPRINT(RT_DEBUG_ERROR, ("rt28xx_ioctl can not find Apcli I/F\n"));
				return -ENETDOWN;
			}
		}
		APCLI_MR_APIDX_SANITY_CHECK(pObj->ioctl_if);
	}
#endif /* APCLI_SUPPORT */
#ifdef MESH_SUPPORT
	else if (RT_DEV_PRIV_FLAGS_GET(net_dev) == INT_MESH)
	{
		pObj->ioctl_if_type = INT_MESH;
		pObj->ioctl_if = 0;
	}
#endif /* MESH_SUPPORT */
#ifdef P2P_SUPPORT
	else if (RT_DEV_PRIV_FLAGS_GET(net_dev) == INT_P2P)
	{
		pObj->ioctl_if_type = INT_P2P;
		pObj->ioctl_if = MAIN_MBSSID;
		apidx = MAIN_MBSSID;
	}
#endif /* P2P_SUPPORT */
    else
    {
/*    	DBGPRINT(RT_DEBUG_WARN, ("IOCTL is not supported in WDS interface\n")); */
    	return -EOPNOTSUPP;
    }
#endif /* 0 */

	switch(cmd)
	{
		case RTPRIV_IOCTL_ATE:
			{
				RTMP_COM_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_ATE, 0, wrqin->ifr_name, 0);
			}
			break;

        case SIOCGIFHWADDR:
			DBGPRINT(RT_DEBUG_TRACE, ("IOCTLIOCTLIOCTL::SIOCGIFHWADDR\n"));
			RTMP_AP_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_AP_SIOCGIFHWADDR, 0, NULL, 0);
/*            if (pObj->ioctl_if < MAX_MBSSID_NUM(pAd)) */
/*    			strcpy((PSTRING) wrq->u.name, (PSTRING) pAd->ApCfg.MBSSID[pObj->ioctl_if].Bssid); */
			break;
#if 0
		case SIOCGIWNAME:
			DBGPRINT(RT_DEBUG_TRACE, ("IOCTL::SIOCGIWNAME\n"));
			strcpy(wrqin->u.name, "RTWIFI SoftAP");
			break;
#endif /* 0 */
		case SIOCSIWESSID:  /*Set ESSID */
#if 0
#ifdef APCLI_SUPPORT
#ifdef ApCli_8021X_SUPPORT
			if (RT_DEV_PRIV_FLAGS_GET(net_dev) == INT_APCLI)
			{
        			struct iw_point	*essid=&wrq->u.essid;
        			rt_apcli_ioctl_siwessid(net_dev, NULL, essid, essid->pointer);
			}
			else
				Status = -EOPNOTSUPP;
#else
			Status = -EOPNOTSUPP;
#endif/*ApCli_8021X_SUPPORT*/
#endif/*APCLI_SUPPORT*/
#endif
			break;
		case SIOCGIWESSID:  /*Get ESSID */
			{
				RT_CMD_AP_IOCTL_SSID IoctlSSID, *pIoctlSSID = &IoctlSSID;
				struct iw_point *erq = &wrqin->u.essid;
				PCHAR pSsidStr = NULL;

				erq->flags=1;
              /*erq->length = pAd->ApCfg.MBSSID[pObj->ioctl_if].SsidLen; */

				pIoctlSSID->priv_flags = RT_DEV_PRIV_FLAGS_GET(net_dev);
				pIoctlSSID->apidx = apidx;
				RTMP_AP_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_AP_SIOCGIWESSID, 0, pIoctlSSID, 0);

				pSsidStr = (PCHAR)pIoctlSSID->pSsidStr;
				erq->length = pIoctlSSID->length;

#if 0 /* os abl move */
#ifdef APCLI_SUPPORT
				if (RT_DEV_PRIV_FLAGS_GET(net_dev) == INT_APCLI)
				{
					if (pAd->ApCfg.ApCliTab[pObj->ioctl_if].Valid == TRUE)
					{
						erq->length = pAd->ApCfg.ApCliTab[pObj->ioctl_if].SsidLen;
						pSsidStr = (PCHAR)&pAd->ApCfg.ApCliTab[pObj->ioctl_if].Ssid;
					}
					else {
						erq->length = 0;
						pSsidStr = NULL;
					}
				}
				else
#endif /* APCLI_SUPPORT */
				{
				erq->length = pAd->ApCfg.MBSSID[apidx].SsidLen;
					pSsidStr = (PCHAR)pAd->ApCfg.MBSSID[apidx].Ssid;
				}
#endif /* 0 */

				if((erq->pointer) && (pSsidStr != NULL))
				{
					/*if(copy_to_user(erq->pointer, pAd->ApCfg.MBSSID[pObj->ioctl_if].Ssid, erq->length)) */
					if(copy_to_user(erq->pointer, pSsidStr, erq->length))
					{
						Status = RTMP_IO_EFAULT;
						break;
					}
				}
				DBGPRINT(RT_DEBUG_TRACE, ("IOCTL::SIOCGIWESSID (Len=%d, ssid=%s...)\n", erq->length, (char *)erq->pointer));
			}
			break;
		case SIOCGIWNWID: /* get network id */
		case SIOCSIWNWID: /* set network id (the cell) */
			Status = RTMP_IO_EOPNOTSUPP;
			break;
		case SIOCGIWFREQ: /* get channel/frequency (Hz) */
		{
			ULONG Channel;
			RTMP_DRIVER_CHANNEL_GET(pAd, &Channel);
			wrqin->u.freq.m = Channel; /*pAd->CommonCfg.Channel; */
			wrqin->u.freq.e = 0;
			wrqin->u.freq.i = 0;
		}
			break; 
		case SIOCSIWFREQ: /*set channel/frequency (Hz) */
			Status = RTMP_IO_EOPNOTSUPP;
			break;
		case SIOCGIWNICKN:
		case SIOCSIWNICKN: /*set node name/nickname */
			Status = RTMP_IO_EOPNOTSUPP;
			break;
		case SIOCGIWRATE:  /*get default bit rate (bps) */
            {
				RT_CMD_IOCTL_RATE IoctlRate, *pIoctlRate = &IoctlRate;

				pIoctlRate->priv_flags = RT_DEV_PRIV_FLAGS_GET(net_dev);
				RTMP_DRIVER_BITRATE_GET(pAd, pIoctlRate);

#if 0
                int rate_index = 0;
                INT32 ralinkrate[256] =
					{2,  4, 11, 22, 12, 18,   24,  36, 48, 72, 96, 108, 109, 110, 111, 112,
					13, 26,   39,  52,  78, 104, 117, 130, 26,  52,  78, 104, 156, 208, 234, 260,
					39, 78,  117, 156, 234, 312, 351, 390,
					27, 54,   81, 108, 162, 216, 243, 270, 54, 108, 162, 216, 324, 432, 486, 540,
					81, 162, 243, 324, 486, 648, 729, 810,
					14, 29,   43,  57,  87, 115, 130, 144, 29, 59,   87, 115, 173, 230, 260, 288,
					43, 87,  130, 173, 260, 317, 390, 433,
					30, 60,   90, 120, 180, 240, 270, 300, 60, 120, 180, 240, 360, 480, 540, 600,
					90, 180, 270, 360, 540, 720, 810, 900,
					0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,
					20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,
					40,41,42,43,44,45,46,47}; /* 3*3 */
#endif

#if 0 /* os abl move */
				HTTRANSMIT_SETTING		HtPhyMode;

#ifdef MESH_SUPPORT
				if (RT_DEV_PRIV_FLAGS_GET(net_dev) == INT_MESH)
					HtPhyMode = pAd->MeshTab.HTPhyMode;
				else
#endif /* MESH_SUPPORT */
#ifdef APCLI_SUPPORT
#ifdef P2P_SUPPORT
				if ((RT_DEV_PRIV_FLAGS_GET(net_dev) == INT_P2P) && P2P_CLI_ON(pAd))
#else
				if (RT_DEV_PRIV_FLAGS_GET(net_dev) == INT_APCLI)
#endif /* P2P_SUPPORT */
					HtPhyMode = pAd->ApCfg.ApCliTab[pObj->ioctl_if].HTPhyMode;
				else
#endif /* APCLI_SUPPORT */
#ifdef WDS_SUPPORT
				if (RT_DEV_PRIV_FLAGS_GET(net_dev) == INT_WDS)
					HtPhyMode = pAd->WdsTab.WdsEntry[pObj->ioctl_if].HTPhyMode;
				else
#endif /* WDS_SUPPORT */
					HtPhyMode = pAd->ApCfg.MBSSID[pObj->ioctl_if].HTPhyMode;

#ifdef MBSS_SUPPORT
				/* reset phy mode for MBSS */
				MBSS_PHY_MODE_RESET(pObj->ioctl_if, HtPhyMode);
#endif /* MBSS_SUPPORT */

#if 0
#ifdef DOT11_N_SUPPORT
                if (pHtPhyMode->field.MODE >= MODE_HTMIX)
                {
/*                	rate_index = 16 + ((UCHAR)pHtPhyMode->field.BW *16) + ((UCHAR)pHtPhyMode->field.ShortGI *32) + ((UCHAR)pHtPhyMode->field.MCS); */
                	rate_index = 16 + ((UCHAR)pHtPhyMode->field.BW *24) + ((UCHAR)pHtPhyMode->field.ShortGI *48) + ((UCHAR)pHtPhyMode->field.MCS);
                }
                else 
#endif /* DOT11_N_SUPPORT */
		  if (pHtPhyMode->field.MODE == MODE_OFDM)
                	rate_index = (UCHAR)(pHtPhyMode->field.MCS) + 4;
                else 
                	rate_index = (UCHAR)(pHtPhyMode->field.MCS);

                if (rate_index < 0)
                    rate_index = 0;

                if (rate_index > 255)
                    rate_index = 255;
    
			    wrqin->u.bitrate.value = ralinkrate[rate_index] * 500000;
#else

			RtmpDrvMaxRateGet(pAd, HtPhyMode.field.MODE, HtPhyMode.field.ShortGI,
							HtPhyMode.field.BW, HtPhyMode.field.MCS,
							(UINT32 *)&wrqin->u.bitrate.value);
#endif
#endif /* 0 */
			wrqin->u.bitrate.value = pIoctlRate->BitRate;
			wrqin->u.bitrate.disabled = 0;
            }
			break;
		case SIOCSIWRATE:  /*set default bit rate (bps) */
		case SIOCGIWRTS:  /* get RTS/CTS threshold (bytes) */
		case SIOCSIWRTS:  /*set RTS/CTS threshold (bytes) */
		case SIOCGIWFRAG:  /*get fragmentation thr (bytes) */
		case SIOCSIWFRAG:  /*set fragmentation thr (bytes) */
		case SIOCGIWENCODE:  /*get encoding token & mode */
		case SIOCSIWENCODE:  /*set encoding token & mode */
			Status = RTMP_IO_EOPNOTSUPP;
			break;
		case SIOCGIWAP:  /*get access point MAC addresses */
			{
/*				PCHAR pBssidStr; */

				wrqin->u.ap_addr.sa_family = ARPHRD_ETHER;
				/*memcpy(wrqin->u.ap_addr.sa_data, &pAd->ApCfg.MBSSID[pObj->ioctl_if].Bssid, ETH_ALEN); */

				RTMP_AP_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_AP_SIOCGIWAP, 0,
								wrqin->u.ap_addr.sa_data, RT_DEV_PRIV_FLAGS_GET(net_dev));
#if 0 /* os abl move */
#ifdef APCLI_SUPPORT
				if (RT_DEV_PRIV_FLAGS_GET(net_dev) == INT_APCLI)
				{
					if (pAd->ApCfg.ApCliTab[pObj->ioctl_if].Valid == TRUE)
						pBssidStr = (PCHAR)&APCLI_ROOT_BSSID_GET(pAd, pAd->ApCfg.ApCliTab[pObj->ioctl_if].MacTabWCID);
					else
						pBssidStr = NULL;
				}
				else
#endif /* APCLI_SUPPORT */
#ifdef P2P_SUPPORT
				if ((RT_DEV_PRIV_FLAGS_GET(net_dev) == INT_P2P) && P2P_CLI_ON(pAd))
				{
					if (pAd->ApCfg.ApCliTab[pObj->ioctl_if].Valid == TRUE)
						pBssidStr = (PCHAR)&APCLI_ROOT_BSSID_GET(pAd, pAd->ApCfg.ApCliTab[pObj->ioctl_if].MacTabWCID);
					else
						pBssidStr = NULL;
				}
				else
#endif /* P2P_SUPPORT */
				{
					pBssidStr = (PCHAR) &pAd->ApCfg.MBSSID[pObj->ioctl_if].Bssid[0];
				}

				if (pBssidStr != NULL)
				{
					memcpy(wrqin->u.ap_addr.sa_data, pBssidStr, ETH_ALEN);
					DBGPRINT(RT_DEBUG_TRACE, ("IOCTL::SIOCGIWAP(=%02x:%02x:%02x:%02x:%02x:%02x)\n",
						pBssidStr[0],pBssidStr[1],pBssidStr[2], pBssidStr[3],pBssidStr[4],pBssidStr[5]));
				}
				else
				{
					memset(wrqin->u.ap_addr.sa_data, 0, ETH_ALEN);
				}
#endif /* 0 */
			}
			break;
		case SIOCGIWMODE:  /*get operation mode */
			wrqin->u.mode = IW_MODE_INFRA;   /*SoftAP always on INFRA mode. */
			break;
		case SIOCSIWAP:  /*set access point MAC addresses */
		case SIOCSIWMODE:  /*set operation mode */
		case SIOCGIWSENS:   /*get sensitivity (dBm) */
		case SIOCSIWSENS:	/*set sensitivity (dBm) */
		case SIOCGIWPOWER:  /*get Power Management settings */
		case SIOCSIWPOWER:  /*set Power Management settings */
		case SIOCGIWTXPOW:  /*get transmit power (dBm) */
		case SIOCSIWTXPOW:  /*set transmit power (dBm) */
		/*case SIOCGIWRANGE:	//Get range of parameters */
		case SIOCGIWRETRY:	/*get retry limits and lifetime */
		case SIOCSIWRETRY:	/*set retry limits and lifetime */
			Status = RTMP_IO_EOPNOTSUPP;
			break;
		case SIOCGIWRANGE:	/*Get range of parameters */
		    {
/*				struct iw_range range; */
				struct iw_range *prange = NULL;
				UINT32 len;

				/* allocate memory */
				os_alloc_mem(NULL, (UCHAR **)&prange, sizeof(struct iw_range));
				if (prange == NULL)
				{
					DBGPRINT(RT_DEBUG_ERROR, ("%s: Allocate memory fail!!!\n", __FUNCTION__));
					break;
				}

				memset(prange, 0, sizeof(struct iw_range));
				prange->we_version_compiled = WIRELESS_EXT;
				prange->we_version_source = 14;

				/*
					what is correct max? This was not
					documented exactly. At least
					69 has been observed.
				*/
				prange->max_qual.qual = 100;
				prange->max_qual.level = 0; /* dB */
				prange->max_qual.noise = 0; /* dB */
				len = copy_to_user(wrq->u.data.pointer, prange, sizeof(struct iw_range));
				os_free_mem(NULL, prange);
		    }
		    break;
		    
		case RT_PRIV_IOCTL:
		case RT_PRIV_IOCTL_EXT:
		{
			subcmd = wrqin->u.data.flags;

			Status = RTMP_AP_IoctlHandle(pAd, wrq, CMD_RT_PRIV_IOCTL, subcmd, wrqin->u.data.pointer, 0);
		}
			break;
		
#ifdef HOSTAPD_SUPPORT
		case SIOCSIWGENIE:
			DBGPRINT(RT_DEBUG_TRACE,("ioctl SIOCSIWGENIE apidx=%d\n",apidx));
			DBGPRINT(RT_DEBUG_TRACE,("ioctl SIOCSIWGENIE length=%d, pointer=%x\n", wrqin->u.data.length, wrqin->u.data.pointer));

#if 0 /* os abl move */
			if(wrqin->u.data.length > 20 && MAX_LEN_OF_RSNIE > wrqin->u.data.length && wrqin->u.data.pointer)
			{
				UCHAR RSNIE_Len[2];
				UCHAR RSNIe[2];
				int offset_next_ie=0;

				DBGPRINT(RT_DEBUG_TRACE,("ioctl SIOCSIWGENIE pAd->IoctlIF=%d\n",apidx));

				RSNIe[0]=*(UINT8 *)wrqin->u.data.pointer;
				if(IE_WPA != RSNIe[0] && IE_RSN != RSNIe[0] )
				{
					DBGPRINT(RT_DEBUG_TRACE,("IE %02x != 0x30/0xdd\n",RSNIe[0]));
					Status = -EINVAL;
					break;
				}
				RSNIE_Len[0]=*((UINT8 *)wrqin->u.data.pointer + 1);
				if(wrqin->u.data.length != RSNIE_Len[0]+2)
				{
					DBGPRINT(RT_DEBUG_TRACE,("IE use WPA1 WPA2\n"));
					NdisZeroMemory(pAd->ApCfg.MBSSID[apidx].RSN_IE[1], MAX_LEN_OF_RSNIE);
					RSNIe[1]=*(UINT8 *)wrqin->u.data.pointer;
					RSNIE_Len[1]=*((UINT8 *)wrqin->u.data.pointer + 1);
					DBGPRINT(RT_DEBUG_TRACE,( "IE1 %02x %02x\n",RSNIe[1],RSNIE_Len[1]));
					pAd->ApCfg.MBSSID[apidx].RSNIE_Len[1] = RSNIE_Len[1];
					NdisMoveMemory(pAd->ApCfg.MBSSID[apidx].RSN_IE[1], (UCHAR *)(wrqin->u.data.pointer)+2, RSNIE_Len[1]);
					offset_next_ie=RSNIE_Len[1]+2;
				}
				else
					DBGPRINT(RT_DEBUG_TRACE,("IE use only %02x\n",RSNIe[0]));

				NdisZeroMemory(pAd->ApCfg.MBSSID[apidx].RSN_IE[0], MAX_LEN_OF_RSNIE);
				RSNIe[0]=*(((UINT8 *)wrqin->u.data.pointer)+offset_next_ie);
				RSNIE_Len[0]=*(((UINT8 *)wrqin->u.data.pointer) + offset_next_ie + 1);
				if(IE_WPA != RSNIe[0] && IE_RSN != RSNIe[0] )
				{
					Status = -EINVAL;
					break;
				}
				pAd->ApCfg.MBSSID[apidx].RSNIE_Len[0] = RSNIE_Len[0];
				NdisMoveMemory(pAd->ApCfg.MBSSID[apidx].RSN_IE[0], ((UCHAR *)(wrqin->u.data.pointer))+2+offset_next_ie, RSNIE_Len[0]);
				APMakeAllBssBeacon(pAd);
				APUpdateAllBeaconFrame(pAd);
			}
#endif /* 0 */

			RTMP_AP_IoctlHandle(pAd, wrqin, CMD_RTPRIV_IOCTL_AP_SIOCSIWGENIE, 0, NULL, 0);
			break;
#endif /* HOSTAPD_SUPPORT */

		case SIOCGIWPRIV:
			if (wrqin->u.data.pointer) 
			{
				if ( access_ok(VERIFY_WRITE, wrqin->u.data.pointer, sizeof(ap_privtab)) != TRUE)
					break;
				if ((sizeof(ap_privtab) / sizeof(ap_privtab[0])) <= wrq->u.data.length)
				{
					wrqin->u.data.length = sizeof(ap_privtab) / sizeof(ap_privtab[0]);
					if (copy_to_user(wrqin->u.data.pointer, ap_privtab, sizeof(ap_privtab)))
						Status = RTMP_IO_EFAULT;
				}
				else
					Status = RTMP_IO_E2BIG;
			}
			break;
		case RTPRIV_IOCTL_SET:
			{
				if( access_ok(VERIFY_READ, wrqin->u.data.pointer, wrqin->u.data.length) == TRUE)
					Status = RTMP_AP_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_SET, 0, NULL, 0);
			}
			break;
		    
		case RTPRIV_IOCTL_SHOW:
			{
				if( access_ok(VERIFY_READ, wrqin->u.data.pointer, wrqin->u.data.length) == TRUE)
					Status = RTMP_AP_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_SHOW, 0, NULL, 0);
			}
			break;	
			
#ifdef INF_AR9
#ifdef AR9_MAPI_SUPPORT
		case RTPRIV_IOCTL_GET_AR9_SHOW:
			{
				if( access_ok(VERIFY_READ, wrqin->u.data.pointer, wrqin->u.data.length) == TRUE)
					Status = RTMP_AP_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_GET_AR9_SHOW, 0, NULL, 0);
			}	
		    break;
#endif /*AR9_MAPI_SUPPORT*/
#endif /* INF_AR9 */

#ifdef WSC_AP_SUPPORT
		case RTPRIV_IOCTL_SET_WSCOOB:
			RTMP_AP_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_SET_WSCOOB, 0, NULL, 0);
		    break;
#endif/*WSC_AP_SUPPORT*/

/* modified by Red@Ralink, 2009/09/30 */
		case RTPRIV_IOCTL_GET_MAC_TABLE:
			RTMP_AP_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_GET_MAC_TABLE, 0, NULL, 0);
		    break;

		case RTPRIV_IOCTL_GET_MAC_TABLE_STRUCT:
			RTMP_AP_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_GET_MAC_TABLE_STRUCT, 0, NULL, 0);
			break;
/* end of modification */

#ifdef AP_SCAN_SUPPORT
		case RTPRIV_IOCTL_GSITESURVEY:
			RTMP_AP_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_GSITESURVEY, 0, NULL, 0);
			break;
#endif /* AP_SCAN_SUPPORT */

		case RTPRIV_IOCTL_STATISTICS:
			RTMP_AP_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_STATISTICS, 0, NULL, 0);
			break;

#ifdef WSC_AP_SUPPORT
		case RTPRIV_IOCTL_WSC_PROFILE:
			RTMP_AP_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_WSC_PROFILE, 0, NULL, 0);
		    break;
#endif /* WSC_AP_SUPPORT */
#ifdef DOT11_N_SUPPORT
		case RTPRIV_IOCTL_QUERY_BATABLE:
			RTMP_AP_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_QUERY_BATABLE, 0, NULL, 0);
		    break;
#endif /* DOT11_N_SUPPORT */
		case RTPRIV_IOCTL_E2P:
			RTMP_AP_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_E2P, 0, NULL, 0);
			break;

#ifdef DBG
		case RTPRIV_IOCTL_BBP:
			RTMP_AP_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_BBP, 0, NULL, 0);
			break;
			
		case RTPRIV_IOCTL_MAC:
			RTMP_AP_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_MAC, 0, NULL, 0);
			break;
            
		case RTPRIV_IOCTL_RF:
			RTMP_AP_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_RF, 0, NULL, 0);
			break;
#endif /* DBG */

		default:
/*			DBGPRINT(RT_DEBUG_ERROR, ("IOCTL::unknown IOCTL's cmd = 0x%08x\n", cmd)); */
			Status = RTMP_IO_EOPNOTSUPP;
			break;
	}

LabelExit:
	if (Status != 0)
	{
		RT_CMD_STATUS_TRANSLATE(Status);
	}
	else
	{
		/*
			If wrq length is modified, we reset the lenght of origin wrq;

			Or we can not modify it because the address of wrq->u.data.length
			maybe same as other union field, ex: iw_range, etc.

			if the length is not changed but we change it, the value for other
			union will also be changed, this is not correct.
		*/
		if (wrq->u.data.length != org_len)
			wrqin->u.data.length = wrq->u.data.length;
	}

	return Status;
}
