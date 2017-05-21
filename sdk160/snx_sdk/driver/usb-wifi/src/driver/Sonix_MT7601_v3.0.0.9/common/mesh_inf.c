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
 ***************************************************************************

	Module Name:
	mesh.c

	Abstract:

	Revision History:
	Who			When			What
	--------	----------		----------------------------------------------
	Fonchi		2007-06-25      For mesh (802.11s) support.
*/
#define RTMP_MODULE_OS

#ifdef MESH_SUPPORT


/*#include "rt_config.h" */
/*#include "mesh_sanity.h" */
#include "rtmp_comm.h"
#include "rt_os_util.h"
#include "rt_os_net.h"

/*static VOID MeshCfgInit( */
/*	IN PRTMP_ADAPTER pAd, */
/*	IN PSTRING		 pHostName); */


/*
========================================================================
Routine Description:
    Init Mesh function.

Arguments:
    ad_p            points to our adapter
    main_dev_p      points to the main BSS network interface

Return Value:
    None

Note:
	1. Only create and initialize virtual network interfaces.
	2. No main network interface here.
========================================================================
*/
VOID RTMP_Mesh_Init(
	IN VOID 				*pAd,
	IN PNET_DEV				main_dev_p,
	IN PSTRING				pHostName)
{
	RTMP_OS_NETDEV_OP_HOOK	netDevOpHook;
	ULONG OpMode;


	/* init operation functions */
	NdisZeroMemory((PUCHAR)&netDevOpHook, sizeof(RTMP_OS_NETDEV_OP_HOOK));
	netDevOpHook.open = Mesh_VirtualIF_Open;
	netDevOpHook.stop = Mesh_VirtualIF_Close;
	netDevOpHook.xmit = Mesh_VirtualIF_PacketSend;
	netDevOpHook.ioctl = Mesh_VirtualIF_Ioctl;	

	/* init operation functions */
	RTMP_DRIVER_OP_MODE_GET(pAd, &OpMode);

#ifdef CONFIG_STA_SUPPORT
#if WIRELESS_EXT >= 12
	if (OpMode == OPMODE_STA)
	{
		netDevOpHook.iw_handler = (void *)&rt28xx_iw_handler_def;
	}
#endif /*WIRELESS_EXT >= 12 */
#endif /* CONFIG_STA_SUPPORT */

#ifdef CONFIG_APSTA_MIXED_SUPPORT
#if WIRELESS_EXT >= 12
	if (OpMode == OPMODE_AP)
	{
		netDevOpHook.iw_handler = &rt28xx_ap_iw_handler_def;
	}
#endif /*WIRELESS_EXT >= 12 */
#endif /* CONFIG_APSTA_MIXED_SUPPORT */

	RTMP_COM_IoctlHandle(pAd, NULL, CMD_RTPRIV_IOCTL_MESH_INIT,
						0, &netDevOpHook, 0);

#if 0 /* os abl move */
#define MESH_MAX_DEV_NUM	32
	PNET_DEV	new_dev_p;
	RTMP_OS_NETDEV_OP_HOOK	netDevOpHook;
	
	/* sanity check to avoid redundant virtual interfaces are created */
	if (pAd->flg_mesh_init != FALSE)
		return;

#ifdef RELEASE_EXCLUDE
	DBGPRINT(RT_DEBUG_INFO, ("%s --->\n", __FUNCTION__));
#endif /* RELEASE_EXCLUDE */

	/* init */
	pAd->MeshTab.dev = NULL;
 
	/* create virtual network interface */
	do {
		new_dev_p = RtmpOSNetDevCreate(pAd, INT_MESH, 0, sizeof(PRTMP_ADAPTER), INF_MESH_DEV_NAME);
		if (new_dev_p == NULL)
		{
			/* allocation fail, exit */
			DBGPRINT(RT_DEBUG_ERROR, ("Allocate network device fail (MESH)...\n"));
			break;
		}

		RTMP_OS_NETDEV_SET_PRIV(new_dev_p, pAd);

		/* init MAC address of virtual network interface */
		COPY_MAC_ADDR(pAd->MeshTab.CurrentAddress, pAd->CurrentAddress);
#ifdef CONFIG_AP_SUPPORT
#ifdef NEW_MBSSID_MODE
		if (pAd->ApCfg.BssidNum > 0) 
		{
			/* 	
				Refer to HW definition - 
					Bit1 of MAC address Byte0 is local administration bit 
					and should be set to 1 in extended multiple BSSIDs'
					Bit3~ of MAC address Byte0 is extended multiple BSSID index.
			 */ 
			pAd->MeshTab.CurrentAddress[0] += 2; 	
			pAd->MeshTab.CurrentAddress[0] += ((pAd->ApCfg.BssidNum - 1) << 2);
		}
#else
		pAd->MeshTab.CurrentAddress[ETH_LENGTH_OF_ADDRESS - 1] =
			(pAd->MeshTab.CurrentAddress[ETH_LENGTH_OF_ADDRESS - 1] + pAd->ApCfg.BssidNum) & 0xFF;
#endif /* NEW_MBSSID_MODE */
#endif /* CONFIG_AP_SUPPORT */

		/* init operation functions */
		NdisZeroMemory((PUCHAR)&netDevOpHook, sizeof(RTMP_OS_NETDEV_OP_HOOK));
		netDevOpHook.open = Mesh_VirtualIF_Open;
		netDevOpHook.stop = Mesh_VirtualIF_Close;
		netDevOpHook.xmit = Mesh_VirtualIF_PacketSend;
		netDevOpHook.ioctl = Mesh_VirtualIF_Ioctl;	
		netDevOpHook.priv_flags = INT_MESH; /* we are virtual interface */
		netDevOpHook.needProtcted = TRUE;

#ifdef CONFIG_STA_SUPPORT
#if WIRELESS_EXT >= 12
		if (pAd->OpMode == OPMODE_STA)
		{
			netDevOpHook.iw_handler = (void *)&rt28xx_iw_handler_def;
		}
#endif /*WIRELESS_EXT >= 12 */
#endif /* CONFIG_STA_SUPPORT */

#ifdef CONFIG_APSTA_MIXED_SUPPORT
#if WIRELESS_EXT >= 12
		if (pAd->OpMode == OPMODE_AP)
		{
			netDevOpHook.iw_handler = &rt28xx_ap_iw_handler_def;
		}
#endif /*WIRELESS_EXT >= 12 */
#endif /* CONFIG_APSTA_MIXED_SUPPORT */

		NdisMoveMemory(&netDevOpHook.devAddr[0], &pAd->MeshTab.CurrentAddress[0], MAC_ADDR_LEN);
		
		/* register this device to OS */
		RtmpOSNetDevAttach(new_dev_p, &netDevOpHook);

		/* backup our virtual network interface */
       	 pAd->MeshTab.dev = new_dev_p;
	} while(FALSE);

	/* Initialize Mesh configuration */
	/*MeshCfgInit(pAd, pHostName); */

	/* initialize Mesh Tables and allocate spin locks */
	NdisAllocateSpinLock(pAd, &pAd->MeshTabLock);

	NeighborTableInit(pAd);
	BMPktSigTabInit(pAd);
	MultipathPoolInit(pAd);

	MeshRoutingTable_Init(pAd);
	MeshEntryTable_Init(pAd);
	MeshProxyEntryTable_Init(pAd);

#ifdef CONFIG_STA_SUPPORT
#ifdef RTMP_MAC_USB
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	{
		MeshTimerInit(pAd);
/*		RTMPInitTimer(pAd, &pAd->CommonCfg.BeaconUpdateTimer, GET_TIMER_FUNCTION(BeaconUpdateExec), pAd, TRUE); */

		RTUSBBssBeaconInit(pAd);
	}
#endif /* RTMP_MAC_USB */
#endif /* CONFIG_STA_SUPPORT */

	pAd->flg_mesh_init = TRUE;
#endif /* 0 */

#ifdef RELEASE_EXCLUDE
	DBGPRINT(RT_DEBUG_INFO, ("%s <---\n", __FUNCTION__));
#endif /* RELEASE_EXCLUDE */
	
}


/*
========================================================================
Routine Description:
    Open a virtual network interface.

Arguments:
    pDev           which WLAN network interface

Return Value:
    0: open successfully
    otherwise: open fail

Note:
========================================================================
*/
INT Mesh_VirtualIF_Open(
	IN PNET_DEV		pDev)
{
	VOID *pAd;

	pAd = RTMP_OS_NETDEV_GET_PRIV(pDev);
	ASSERT(pAd);

	DBGPRINT(RT_DEBUG_TRACE, ("%s: ===> %s\n", __FUNCTION__, RTMP_OS_NETDEV_GET_DEVNAME(pDev)));
	

	if (RTMP_COM_IoctlHandle(pAd, NULL, CMD_RTPRIV_IOCTL_MESH_OPEN_PRE, 0,
							pDev, 0) != NDIS_STATUS_SUCCESS)
		return -1;

	if (VIRTUAL_IF_UP(pAd) != 0)
		return -1;

	/* increase MODULE use count */
	RT_MOD_INC_USE_COUNT();

	RTMP_OS_NETDEV_START_QUEUE(pDev);

	if (RTMP_COM_IoctlHandle(pAd, NULL, CMD_RTPRIV_IOCTL_MESH_OPEN_POST, 0,
							pDev, 0) != NDIS_STATUS_SUCCESS)
		return -1;

#if 0 /* os abl move */
	if (ADHOC_ON(pAd))
		return -1;

	pAd->MeshTab.bBcnSntReq = TRUE;

	if (VIRTUAL_IF_UP(pAd) != 0)
		return -1;

	/* increase MODULE use count */
	RT_MOD_INC_USE_COUNT();

	RTMP_OS_NETDEV_START_QUEUE(dev_p);
	
	/* Statup Mesh Protocol Stack. */
	MeshUp(pAd);

#ifdef CONFIG_STA_SUPPORT
	AsicSetPreTbttInt(pAd, TRUE);
	AsicEnableMESHSync(pAd);
#endif /* CONFIG_STA_SUPPORT */
#endif /* 0 */

	DBGPRINT(RT_DEBUG_TRACE, ("%s: <=== %s\n", __FUNCTION__, RTMP_OS_NETDEV_GET_DEVNAME(pDev)));

	return 0;
}


/*
========================================================================
Routine Description:
    Close a virtual network interface.

Arguments:
    dev_p           which WLAN network interface

Return Value:
    0: close successfully
    otherwise: close fail

Note:
========================================================================
*/
INT Mesh_VirtualIF_Close(
	IN	PNET_DEV	pDev)
{
	VOID *pAd;

	pAd = RTMP_OS_NETDEV_GET_PRIV(pDev);
	ASSERT(pAd);

	DBGPRINT(RT_DEBUG_TRACE, ("%s: ===> %s\n", __FUNCTION__, RTMP_OS_NETDEV_GET_DEVNAME(pDev)));
	

	/* stop mesh. */
	RTMP_OS_NETDEV_STOP_QUEUE(pDev);

	RTMP_COM_IoctlHandle(pAd, NULL, CMD_RTPRIV_IOCTL_MESH_CLOSE, 0, pDev, 0);

#if 0 /* os abl move */
	MeshDown(pAd, TRUE);

	pAd->MeshTab.bBcnSntReq = FALSE;

#ifdef CONFIG_STA_SUPPORT
	{
		UINT32 Value;
		/* Disable pre-tbtt interrupt */
		RTMP_IO_READ32(pAd, INT_TIMER_EN, &Value);
		Value &=0xe;
		RTMP_IO_WRITE32(pAd, INT_TIMER_EN, Value);
	}

	/*update beacon Sync */
	/*if rausb0 is up => stop beacon */
	/*if rausb0 is down => we will call AsicDisableSync() in usb_rtusb_close_device() */
	if (INFRA_ON(pAd))
		AsicEnableBssSync(pAd);
	else if (ADHOC_ON(pAd))
		AsicEnableIbssSync(pAd);
	else
		AsicDisableSync(pAd);
#endif /* CONFIG_STA_SUPPORT */

	pAd->MeshTab.bBcnSntReq = FALSE;

#ifdef CONFIG_AP_SUPPORT
	APMakeAllBssBeacon(pAd);
	APUpdateAllBeaconFrame(pAd);
#endif /* CONFIG_AP_SUPPORT */
#endif /* 0 */

	VIRTUAL_IF_DOWN(pAd);

	RT_MOD_DEC_USE_COUNT();

	return 0;
} 


/*
========================================================================
Routine Description:
    Send a packet to WLAN.

Arguments:
    skb_p           points to our adapter
    dev_p           which WLAN network interface

Return Value:
    0: transmit successfully
    otherwise: transmit fail

Note:
========================================================================
*/
INT Mesh_VirtualIF_PacketSend(
	IN PNDIS_PACKET 	pPktSrc, 
	IN PNET_DEV			pDev)
{
#ifdef RELEASE_EXCLUDE
	DBGPRINT(RT_DEBUG_INFO, ("%s --->\n", __FUNCTION__));
#endif /* RELEASE_EXCLUDE */

	MEM_DBG_PKT_ALLOC_INC(pPktSrc);

	if(!(RTMP_OS_NETDEV_STATE_RUNNING(pDev)))
	{
		/* the interface is down */
		RELEASE_NDIS_PACKET(NULL, pPktSrc, NDIS_STATUS_FAILURE);
		return 0;
	}

	return MESH_PacketSend(pPktSrc, pDev, rt28xx_packet_xmit);


#if 0 /* os abl move */
	PRTMP_ADAPTER pAd;
	PMESH_STRUCT pMesh;

#ifdef RELEASE_EXCLUDE
	DBGPRINT(RT_DEBUG_INFO, ("%s --->\n", __FUNCTION__));
#endif /* RELEASE_EXCLUDE */
	

	pAd = RTMP_OS_NETDEV_GET_PRIV(dev_p);
	ASSERT(pAd);

#ifdef RALINK_ATE
	if (ATE_ON(pAd))
	{
		RELEASE_NDIS_PACKET(pAd, skb_p, NDIS_STATUS_FAILURE);
		return 0;
	}
#endif /* RALINK_ATE */
	if ((RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_BSS_SCAN_IN_PROGRESS)) ||
		(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_RADIO_OFF))          ||
		(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_RESET_IN_PROGRESS)))
	{
		/* wlan is scanning/disabled/reset */
		RELEASE_NDIS_PACKET(pAd, skb_p, NDIS_STATUS_FAILURE);
		return 0;
	}

	if(!(RTMP_OS_NETDEV_STATE_RUNNING(dev_p)))
	{
		/* the interface is down */
		RELEASE_NDIS_PACKET(pAd, skb_p, NDIS_STATUS_FAILURE);
		return 0;
	}

	pMesh = (PMESH_STRUCT)&pAd->MeshTab;
	do
	{
		if (MeshValid(pMesh) != TRUE)
			break;
		/* find the device in our Mesh list */
		if (pMesh->dev == dev_p)
		{
			/* ya! find it */
			pAd->RalinkCounters.PendingNdisPacketCount ++;
			RTMP_SET_PACKET_SOURCE(skb_p, PKTSRC_NDIS);
			RTMP_SET_PACKET_MOREDATA(skb_p, FALSE);
			RTMP_SET_PACKET_NET_DEVICE_MESH(skb_p, 0);
			SET_OS_PKT_NETDEV(skb_p, pAd->net_dev);
#ifdef RELEASE_EXCLUDE			
			if (!(*(GET_OS_PKT_DATAPTR(skb_p)) & 0x01))
			{
				DBGPRINT(RT_DEBUG_INFO,
							("%s(Mesh) - unicast packet to "
							"(Mesh0)\n", __FUNCTION__));
			}
 #endif /* RELEASE_EXCLUDE */


			/* transmit the packet */
			return rt28xx_packet_xmit(RTPKT_TO_OSPKT(skb_p));
		}
    } while(FALSE);


	/* can not find the BSS so discard the packet */
#ifdef RELEASE_EXCLUDE
	DBGPRINT(RT_DEBUG_INFO,
				("%s - needn't to send or net device not exist.\n", __FUNCTION__));
	DBGPRINT(RT_DEBUG_INFO, ("%s <---\n", __FUNCTION__));
#endif /* RELEASE_EXCLUDE */

	RELEASE_NDIS_PACKET(pAd, skb_p, NDIS_STATUS_FAILURE);

	return 0;
#endif /* 0 */
}


/*
========================================================================
Routine Description:
    IOCTL to WLAN.

Arguments:
    dev_p           which WLAN network interface
    rq_p            command information
    cmd             command ID

Return Value:
    0: IOCTL successfully
    otherwise: IOCTL fail

Note:
    SIOCETHTOOL     8946    New drivers use this ETHTOOL interface to
                            report link failure activity.
========================================================================
*/
INT Mesh_VirtualIF_Ioctl(
	IN PNET_DEV				dev_p, 
	IN OUT VOID 			*rq_p, 
	IN INT 					cmd)
{
	return rt28xx_ioctl(dev_p, rq_p, cmd);
}


#if 0 /* os abl move to common/mesh.c */
VOID MeshCfgInit(
	IN PRTMP_ADAPTER pAd,
	IN PSTRING		 pHostName)
{
	INT	i;

	/* default configuration of Mesh. */
	pAd->MeshTab.OpMode = MESH_MP;

#ifdef CONFIG_AP_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_AP(pAd)
		pAd->MeshTab.OpMode |= MESH_AP;
#endif /* CONFIG_AP_SUPPORT */

	pAd->MeshTab.PathProtocolId = MESH_HWMP;
	pAd->MeshTab.PathMetricId = MESH_AIRTIME;
	pAd->MeshTab.ContgesionCtrlId = NULL_PROTOCOL;
	pAd->MeshTab.TTL = MESH_TTL;
	pAd->MeshTab.MeshMaxTxRate = 0;
	pAd->MeshTab.MeshMultiCastAgeOut = MULTIPATH_AGEOUT;
	pAd->MeshTab.UCGEnable = FALSE;
	pAd->MeshTab.MeshCapability.field.Forwarding = 1;
	if (pAd->MeshTab.MeshIdLen == 0)
	{
		pAd->MeshTab.MeshIdLen = strlen(DEFAULT_MESH_ID);
		NdisMoveMemory(pAd->MeshTab.MeshId, DEFAULT_MESH_ID, pAd->MeshTab.MeshIdLen);
	}

	/* initialize state */
	pAd->MeshTab.EasyMeshSecurity = TRUE;	/* Default is TRUE for CMPC */
	pAd->MeshTab.bInitialMsaDone = FALSE;
	pAd->MeshTab.bKeyholderDone  = FALSE;
	pAd->MeshTab.bConnectedToMKD = FALSE;
	pAd->MeshTab.MeshOnly = FALSE;

	pAd->MeshTab.bAutoTxRateSwitch = TRUE;
	pAd->MeshTab.DesiredTransmitSetting.field.MCS = MCS_AUTO;

	for (i = 0; i < MAX_MESH_LINKS; i++)
		NdisZeroMemory(&pAd->MeshTab.MeshLink[i].Entry, sizeof(MESH_LINK_ENTRY));

	if (strlen(pHostName) > 0)
	{
		if (strlen(pHostName) < MAX_HOST_NAME_LEN)
			strcpy((PSTRING) pAd->MeshTab.HostName, pHostName);
		else
			strncpy((PSTRING) pAd->MeshTab.HostName, pHostName, MAX_HOST_NAME_LEN-1);
	}
	else
		strcpy((PSTRING) pAd->MeshTab.HostName, DEFAULT_MESH_HOST_NAME);

}
#endif /* 0 */

#ifdef LINUX
#if (WIRELESS_EXT >= 12)
struct iw_statistics *Mesh_VirtualIF_get_wireless_stats(
	IN  struct net_device *net_dev);
#endif
#endif /* LINUX */


VOID RTMP_Mesh_Remove(
	IN VOID 			*pAd)
{
#ifdef RELEASE_EXCLUDE
	DBGPRINT(RT_DEBUG_INFO, ("%s --->\n", __FUNCTION__));
#endif /* RELEASE_EXCLUDE */

	RTMP_COM_IoctlHandle(pAd, NULL, CMD_RTPRIV_IOCTL_MESH_REMOVE, 0, NULL, 0);

#ifdef RELEASE_EXCLUDE
	DBGPRINT(RT_DEBUG_INFO, ("%s <---\n", __FUNCTION__));
#endif /* RELEASE_EXCLUDE */
}


#endif /* MESH_SUPPORT */
