/****************************************************************************
 * Ralink Tech Inc.
 * Taiwan, R.O.C.
 *
 * (c) Copyright 2002, Ralink Technology, Inc.
 *
 * All rights reserved. Ralink's source code is an unpublished work and the
 * use of a copyright notice does not imply otherwise. This source code
 * contains confidential trade secret material of Ralink Tech. Any attemp
 * or participation in deciphering, decoding, reverse engineering or in any
 * way altering the source code is stricitly prohibited, unless the prior
 * written consent of Ralink Technology, Inc. is obtained.
 ***************************************************************************

    Module Name:
	ap_ioctl.c

    Abstract:
    IOCTL related subroutines

    Revision History:
    Who          When          What
    --------    ----------      ------------------------------------------
*/

#include "rt_config.h"

INT rt28xx_ap_ioctl(
	IN	PNET_DEV	net_dev, 
	IN	INT			cmd, 
	IN	caddr_t		pData)
{
	RTMP_ADAPTER	*pAd = NULL;
	INT				retVal = 0;
	INT 				index = 0;
	POS_COOKIE		pObj;
	UCHAR			apidx=0;
	UINT32          subcmd;
	struct iwreq	*wrqin = (struct iwreq *)pData;
	RTMP_IOCTL_INPUT_STRUCT rt_wrq, *wrq = &rt_wrq;
	INT			Status = NDIS_STATUS_SUCCESS;
	UINT32			org_len;

	if (net_dev == NULL)
		return (EINVAL);
		
	pAd = RTMP_OS_NETDEV_GET_PRIV(net_dev);
	if (pAd == NULL)
	{
		/* if 1st open fail, pAd will be free; So the net_dev->priv will be NULL in 2rd open */
		return (EINVAL);
	}

	NdisZeroMemory(&rt_wrq, sizeof(struct __RTMP_IOCTL_INPUT_STRUCT));
	wrq->u.data.pointer = wrqin->u.data.pointer;
	wrq->u.data.length = wrqin->u.data.length;
	wrq->u.data.flags = wrqin->u.data.flags;
	org_len = wrq->u.data.length;

	pObj = (POS_COOKIE) pAd->OS_Cookie;

    /* determine this ioctl command is comming from which interface. */
    if (strcmp(net_dev->dev_name,"ra0") == 0)
    {
		pObj->ioctl_if_type = INT_MAIN;
       	pObj->ioctl_if = MAIN_MBSSID;
    }
    else if ((strcmp(net_dev->dev_name,"ra1") == 0) ||
		   (strcmp(net_dev->dev_name,"ra2") == 0) ||
		   (strcmp(net_dev->dev_name,"ra3") == 0) ||
		   (strcmp(net_dev->dev_name,"ra4") == 0) ||
		   (strcmp(net_dev->dev_name,"ra5") == 0) ||
		   (strcmp(net_dev->dev_name,"ra6") == 0) ||
		   (strcmp(net_dev->dev_name,"ra7") == 0)
		)
    {
		pObj->ioctl_if_type = INT_MBSSID;
		if (strcmp(net_dev->dev_name, pAd->net_dev->dev_name) != 0)
    	{
	        for (index = 1; index < pAd->ApCfg.BssidNum; index++)
	    	{
	    	    if (pAd->ApCfg.MBSSID[index].MSSIDDev == net_dev)
	    	    {
	    	        pObj->ioctl_if = index;
	    	        break;
	    	    }
	    	}

	        /* Interface not found! */
	        if(index == pAd->ApCfg.BssidNum)
	            return -ENETDOWN;
	    }
	    else    /* ioctl command from I/F(ra0) */
	    {
			GET_PAD_FROM_NET_DEV(pAd, net_dev);	
    	    pObj->ioctl_if = MAIN_MBSSID;
	    }
        MBSS_MR_APIDX_SANITY_CHECK(pAd, pObj->ioctl_if);
        apidx = pObj->ioctl_if;
    }
#ifdef WDS_SUPPORT
	else if ((strcmp(net_dev->dev_name,"wds0") == 0))
	{
		pObj->ioctl_if_type = INT_WDS;
		for(index = 0; index < MAX_WDS_ENTRY; index++)
		{
			if (pAd->WdsTab.WdsEntry[index].dev == net_dev)
			{
				pObj->ioctl_if = index;

#ifdef RELASE_EXCLUDE
				DBGPRINT(RT_DEBUG_INFO, ("rt28xx_ioctl I/F(wds%d): cmd = 0x%08x\n", pObj->ioctl_if, cmd));
#endif /* RELASE_EXCLUDE */
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
	else if ((strcmp(net_dev->dev_name,"apcli0") == 0))
	{
		pObj->ioctl_if_type = INT_APCLI;
		for (index = 0; index < MAX_APCLI_NUM; index++)
		{
			if (pAd->ApCfg.ApCliTab[index].dev == net_dev)
			{
				pObj->ioctl_if = index;

#ifdef RELASE_EXCLUDE
				DBGPRINT(RT_DEBUG_INFO, ("rt28xx_ioctl I/F(apcli%d): cmd = 0x%08x\n", pObj->ioctl_if, cmd));
#endif /* RELASE_EXCLUDE */
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
	else if ((strcmp(net_dev->dev_name,"mesh0") == 0))
	{
		pObj->ioctl_if_type = INT_MESH;
		pObj->ioctl_if = 0;
	}
#endif /* MESH_SUPPORT */
    else
    {
    	return -EOPNOTSUPP;
    }

	switch(cmd)
	{
#ifdef RALINK_ATE
#ifdef RALINK_QA
		case RTPRIV_IOCTL_ATE:
			{	
				RtmpDoAte(pAd, wrq, wrqin->ifr_name);
			}
			break;
#endif /* RALINK_QA */ 
#endif /* RALINK_ATE */

		case RT_PRIV_IOCTL:
		case RT_PRIV_IOCTL_EXT:	
			subcmd = wrqin->u.data.flags;
			Status = RTMP_AP_IoctlHandle(pAd, wrq, CMD_RT_PRIV_IOCTL, subcmd, NULL, 0);
			break;
		
		case RTPRIV_IOCTL_SET:
			{	
				retVal = RTMPAPPrivIoctlSet(pAd, wrq);
			}
			break;
		    
		case RTPRIV_IOCTL_SHOW:
			{
				retVal = RTMPAPPrivIoctlShow(pAd, wrq);
			}
			break;		    

		case RTPRIV_IOCTL_GET_MAC_TABLE:
			RTMP_AP_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_GET_MAC_TABLE, 0, NULL, 0);
		    break;

		case RTPRIV_IOCTL_GSITESURVEY:
			Status = RTMP_AP_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_GSITESURVEY, 0, NULL, 0);
			break;

		case RTPRIV_IOCTL_STATISTICS:
			RTMP_AP_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_STATISTICS, 0, NULL, 0);
			break;

#ifdef DOT1X_SUPPORT
		case RTPRIV_IOCTL_RADIUS_DATA:
		    RTMPIoctlRadiusData(pAd, wrq);
		    break;

		case RTPRIV_IOCTL_ADD_WPA_KEY:
		    RTMPIoctlAddWPAKey(pAd, wrq);
		    break;

		case RTPRIV_IOCTL_ADD_PMKID_CACHE:
		    RTMPIoctlAddPMKIDCache(pAd, wrq);
			break;

		case RTPRIV_IOCTL_STATIC_WEP_COPY:
		    RTMPIoctlStaticWepCopy(pAd, wrq);
			break;
#endif /* DOT1X_SUPPORT */

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
			break;

#ifdef DBG
		case RTPRIV_IOCTL_BBP:
			{                
				RTMP_AP_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_BBP, 0, NULL, 0);
			}
			break;
			
		case RTPRIV_IOCTL_MAC:
			{
				RTMP_AP_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_MAC, 0, NULL, 0);
			}
			break;

		case RTPRIV_IOCTL_E2P:
			{
				RTMP_AP_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_E2P, 0, NULL, 0);
			}
			break;
#ifdef RTMP_RF_RW_SUPPORT
		case RTPRIV_IOCTL_RF:
			{
				RTMP_AP_IoctlHandle(pAd, wrq, CMD_RTPRIV_IOCTL_RF, 0, NULL, 0);
			}
			break;
#endif /* RTMP_RF_RW_SUPPORT */
#endif /* DBG */

#ifdef WSC_INCLUDED
		case RTPRIV_IOCTL_WSC_CALLBACK:
			{
				POS_COOKIE pObj;

				pObj = (POS_COOKIE)pAd->OS_Cookie;
				pObj->WscMsgCallBack = wrq->u.data.pointer;
                                if (pObj->WscMsgCallBack)
                                        DBGPRINT(RT_DEBUG_ERROR, ("Set pObj->WscMsgCallBack 0x%x\n", pObj->WscMsgCallBack));
                                else {
                                        retVal = EINVAL;
                                        DBGPRINT(RT_DEBUG_ERROR, ("Set pObj->WscMsgCallBack is NULL\n"));
                                }
			}
			break;
						
#endif /* WSC_INCLUDED */
		default:
			DBGPRINT(RT_DEBUG_ERROR, ("rt28xx_ap_ioctl():Not supported ioctl cmd:0x%x!\n", cmd));
			retVal = EINVAL;
			break;
	}

        /*
                If wrq length is modified, we reset the lenght of origin wrq;
    	
                Or we can not modify it because the address of wrq->u.data.length
                maybe same as other union field, ex: iw_range, etc.

                if the length is not changed but we change it, the value for other
                union will also be changed, this is not correct.
        */
        if (wrq->u.data.length != org_len)
                wrqin->u.data.length = wrq->u.data.length;

	return retVal;
}

