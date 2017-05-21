/*
	Module Name:
	p2p_inf.c

	Abstract:

	Revision History:
	Who			When			What
	--------	----------		----------------------------------------------

*/
#define RTMP_MODULE_OS

#ifdef P2P_SUPPORT

/*#include "rt_config.h" */
/*#include "p2p_inf.h" */
#include "rtmp_comm.h"
#include "rt_os_util.h"
#include "rt_os_net.h"


/*
========================================================================
Routine Description:
    Initialize Multi-BSS function.

Arguments:
    pAd				points to our adapter
    pDevMain		points to the main BSS network interface

Return Value:
    None

Note:
	1. Only create and initialize virtual network interfaces.
	2. No main network interface here.
========================================================================
*/
VOID RTMP_P2P_Init(
	IN VOID 		*pAd,
	IN PNET_DEV		main_dev_p)
{
	/*PNET_DEV pDevNew; */
	/*INT status;*/
	RTMP_OS_NETDEV_OP_HOOK	netDevHook;
	/*APCLI_STRUCT	*pApCliEntry; */
				
#if 0
	/* sanity check to avoid redundant virtual interfaces are created */
	if (pAd->flg_p2p_init != FALSE)
		return;
#endif

	DBGPRINT(RT_DEBUG_TRACE, ("%s --->\n", __FUNCTION__));

#if 0 /* os abl move */
	/* init */
	pAd->ApCfg.MBSSID[MAIN_MBSSID].MSSIDDev = NULL;
	pAd->ApCfg.ApCliTab[MAIN_MBSSID].dev = NULL;
	pApCliEntry = &pAd->ApCfg.ApCliTab[MAIN_MBSSID];

    /* create virtual network interface */
	{
		UINT32 MC_RowID = 0, IoctlIF = 0;
		pDevNew = RtmpOSNetDevCreate(MC_RowID, &IoctlIF, INT_P2P, MAIN_MBSSID, sizeof(PRTMP_ADAPTER), INF_P2P_DEV_NAME);

		if (pDevNew == NULL)
		{
			/* allocation fail, exit */
			DBGPRINT(RT_DEBUG_ERROR, ("Allocate network device fail (MBSS)...\n"));
			return;
		}
		else
		{
			DBGPRINT(RT_DEBUG_TRACE, ("Register P2P IF (%s)\n", RTMP_OS_NETDEV_GET_DEVNAME(pDevNew)));
		}

		RTMP_OS_NETDEV_SET_PRIV(pDevNew, pAd);
#endif
		/* init operation functions and flags */
		NdisZeroMemory(&netDevHook, sizeof(netDevHook));
		netDevHook.open = P2P_VirtualIF_Open;	/* device opem hook point */
		netDevHook.stop = P2P_VirtualIF_Close;	/* device close hook point */
		netDevHook.xmit = P2P_VirtualIF_PacketSend;	/* hard transmit hook point */
		netDevHook.ioctl = P2P_VirtualIF_Ioctl;	/* ioctl hook point */

#if 0 /* os abl move */
		netDevHook.priv_flags = INT_P2P;			/* We are virtual interface */
		netDevHook.needProtcted = TRUE;
#endif /*0*/
#if WIRELESS_EXT >= 12
		netDevHook.iw_handler = (void *)&rt28xx_ap_iw_handler_def;
#endif /* WIRELESS_EXT >= 12 */
		RTMP_COM_IoctlHandle(pAd, NULL, CMD_RTPRIV_IOCTL_P2P_INIT,
							0, &netDevHook, 0);

#if 0 /* os abl move */
		/* Init MAC address of virtual network interface */
		COPY_MAC_ADDR(pAd->P2PCurrentAddress, pAd->CurrentAddress);
#ifdef NEW_MBSSID_MODE
		/* 	
			Refer to HW definition - 
						Bit1 of MAC address Byte0 is local administration bit 
						and should be set to 1 in extended multiple BSSIDs'
						Bit3~ of MAC address Byte0 is extended multiple BSSID index.
		*/
		pAd->P2PCurrentAddress[0] += 2; 
#else
		pAd->P2PCurrentAddress[5] += FIRST_MBSSID;
#endif /* NEW_MBSSID_MODE */

		NdisMoveMemory(&netDevHook.devAddr[0], &pAd->P2PCurrentAddress[0], MAC_ADDR_LEN);
		
		/* backup our virtual network interface */
		pAd->ApCfg.MBSSID[MAIN_MBSSID].MSSIDDev = pDevNew;
		COPY_MAC_ADDR(pAd->ApCfg.MBSSID[MAIN_MBSSID].Bssid, pAd->P2PCurrentAddress);

		pApCliEntry->dev = pDevNew;
		COPY_MAC_ADDR(pApCliEntry->CurrentAddress, pAd->P2PCurrentAddress);

		COPY_MAC_ADDR(pAd->P2pCfg.CurrentAddress, pAd->P2PCurrentAddress);
		pAd->p2p_dev = pDevNew;
		
		/* register this device to OS */
		RtmpOSNetDevAttach(pAd->OpMode, pDevNew, &netDevHook);
	}

	pAd->CommonCfg.BeaconPeriod = 100;
	pAd->ApCfg.DtimPeriod = 1;
	pAd->CommonCfg.DisableOLBCDetect = 0;

	NdisMoveMemory(pAd->ApCfg.MBSSID[MAIN_MBSSID].Ssid, "DIRECT-LINUX-AP", 15);
	pAd->ApCfg.MBSSID[MAIN_MBSSID].SsidLen = 15;
	pAd->ApCfg.MBSSID[MAIN_MBSSID].AuthMode = Ndis802_11AuthModeOpen;
	pAd->ApCfg.MBSSID[MAIN_MBSSID].WepStatus = Ndis802_11EncryptionDisabled;
	pAd->ApCfg.MBSSID[MAIN_MBSSID].DesiredTransmitSetting.field.MCS = pAd->StaCfg.DesiredTransmitSetting.field.MCS;

	if ((pAd->CommonCfg.bWmmCapable) || WMODE_CAP_N(pAd->CommonCfg.PhyMode))
		pAd->ApCfg.MBSSID[MAIN_MBSSID].bWmmCapable = TRUE;

	/*OPSTATUS_CLEAR_FLAG(pAd, fOP_STATUS_P2P_GO); */
	/*OPSTATUS_CLEAR_FLAG(pAd, fOP_STATUS_P2P_CLI); */

	pAd->flg_p2p_init = TRUE;
	pAd->ApCfg.ApCliTab[MAIN_MBSSID].AuthMode = Ndis802_11AuthModeOpen;
	pAd->ApCfg.ApCliTab[MAIN_MBSSID].WepStatus = Ndis802_11WEPDisabled;
	pAd->ApCfg.ApCliTab[MAIN_MBSSID].DesiredTransmitSetting.field.MCS = pAd->StaCfg.DesiredTransmitSetting.field.MCS;
	RTMPSetIndividualHT(pAd, MIN_NET_DEVICE_FOR_APCLI);
	pAd->flg_apcli_init = TRUE;

	pAd->flg_p2p_OpStatusFlags = P2P_DISABLE;
#endif /*0*/
	DBGPRINT(RT_DEBUG_TRACE, ("%s <---\n", __FUNCTION__));

}

/*
========================================================================
Routine Description:
    Open a virtual network interface.

Arguments:
    dev_p           which WLAN network interface

Return Value:
    0: open successfully
    otherwise: open fail

Note:
========================================================================
*/
INT P2P_VirtualIF_Open(
	IN PNET_DEV		dev_p)
{
	VOID *pAd;
	/*PMULTISSID_STRUCT	pMbss; */

	pAd = RTMP_OS_NETDEV_GET_PRIV(dev_p);
	ASSERT(pAd);

	DBGPRINT(RT_DEBUG_TRACE, ("%s: ===> %s\n", __FUNCTION__, RTMP_OS_NETDEV_GET_DEVNAME(dev_p)));

	if (RTMP_COM_IoctlHandle(pAd, NULL, CMD_RTPRIV_IOCTL_P2P_OPEN_PRE, 0,
							dev_p, 0) != NDIS_STATUS_SUCCESS)
		return -1;

	if (VIRTUAL_IF_UP(pAd) != 0)
		return -1;

	/* increase MODULE use count */
	RT_MOD_INC_USE_COUNT();

	RTMP_OS_NETDEV_START_QUEUE(dev_p);

	if (RTMP_COM_IoctlHandle(pAd, NULL, CMD_RTPRIV_IOCTL_P2P_OPEN_POST, 0,
							dev_p, 0) != NDIS_STATUS_SUCCESS)
		return -1;

#if 0 /* os abl move */
	if (ADHOC_ON(pAd))
		return -1;

	pMbss = &pAd->ApCfg.MBSSID[MAIN_MBSSID];
	/* re-copy the MAC to virtual interface to avoid these MAC = all zero,
		when re-open the ra0,
		i.e. ifconfig ra0 down, ifconfig ra0 up, ifconfig ra0 down, ifconfig up ... */

	COPY_MAC_ADDR(pMbss->Bssid, pAd->CurrentAddress);

#ifdef NEW_MBSSID_MODE
	/* 	
		Refer to HW definition - 
					Bit1 of MAC address Byte0 is local administration bit 
					and should be set to 1 in extended multiple BSSIDs'
					Bit3~ of MAC address Byte0 is extended multiple BSSID index.
	*/
	pMbss->Bssid[MAIN_MBSSID] += 2; 	
#else
		pMbss->Bssid[5] += FIRST_MBSSID;
#endif /* NEW_MBSSID_MODE */

	if (pMbss->MSSIDDev != NULL)
	{
		NdisMoveMemory(RTMP_OS_NETDEV_GET_PHYADDR(pMbss->MSSIDDev), 
							pMbss->Bssid,
							MAC_ADDR_LEN);
	}

	pAd->ApCfg.MBSSID[MAIN_MBSSID].bBcnSntReq = FALSE;

	if (VIRTUAL_IF_UP(pAd) != 0)
		return -1;

	/* increase MODULE use count */
	RT_MOD_INC_USE_COUNT();

	RTMP_OS_NETDEV_START_QUEUE(dev_p);

	P2PCfgInit(pAd);
	/*P2P_GoStartUp(pAd, MAIN_MBSSID); */
	/*P2P_CliStartUp(pAd); */

	/* P2P Enable */
	P2pEnable(pAd);

#ifdef WSC_INCLUDED
	WscGenerateUUID(pAd, 
					&pAd->ApCfg.MBSSID[MAIN_MBSSID].WscControl.Wsc_Uuid_E[0], 
					&pAd->ApCfg.MBSSID[MAIN_MBSSID].WscControl.Wsc_Uuid_Str[0], 
					0, 
					FALSE);
	WscGenerateUUID(pAd, 
					&pAd->ApCfg.ApCliTab[MAIN_MBSSID].WscControl.Wsc_Uuid_E[0], 
					&pAd->ApCfg.ApCliTab[MAIN_MBSSID].WscControl.Wsc_Uuid_Str[0], 
					0, 
					FALSE);
	WscInit(pAd, FALSE, MIN_NET_DEVICE_FOR_P2P_GO);
	WscInit(pAd, TRUE, BSS0);
#endif /* WSC_INCLUDED */
#endif /*0*/
	DBGPRINT(RT_DEBUG_TRACE, ("%s: <=== %s\n", __FUNCTION__, RTMP_OS_NETDEV_GET_DEVNAME(dev_p)));

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
INT P2P_VirtualIF_Close(
	IN	PNET_DEV	dev_p)
{
	VOID *pAd;

	pAd = RTMP_OS_NETDEV_GET_PRIV(dev_p);
	ASSERT(pAd);

	DBGPRINT(RT_DEBUG_TRACE, ("%s: ===> %s\n", __FUNCTION__, RTMP_OS_NETDEV_GET_DEVNAME(dev_p)));

	/* stop p2p. */
	RTMP_OS_NETDEV_STOP_QUEUE(dev_p);

	RTMP_COM_IoctlHandle(pAd, NULL, CMD_RTPRIV_IOCTL_P2P_CLOSE, 0, dev_p, 0);

#if 0 /* os abl move */
	if (P2P_CLI_ON(pAd))
		P2P_CliStop(pAd);
	else if (P2P_GO_ON(pAd))
		P2P_GoStop(pAd);

	{
		UINT32 Value;
		/* Disable pre-tbtt interrupt */
		RTMP_IO_READ32(pAd, INT_TIMER_EN, &Value);
		Value &=0xe;
		RTMP_IO_WRITE32(pAd, INT_TIMER_EN, Value);
	}

	/* update beacon Sync */
	/* if rausb0 is up => stop beacon */
	/* if rausb0 is down => we will call AsicDisableSync() in usb_rtusb_close_device() */
	if (INFRA_ON(pAd))
		AsicEnableBssSync(pAd);
	else if (ADHOC_ON(pAd))
		AsicEnableIbssSync(pAd);
	else
		AsicDisableSync(pAd);
#endif /*0*/
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
INT P2P_VirtualIF_PacketSend(
	IN PNDIS_PACKET 	skb_p, 
	IN PNET_DEV			dev_p)
{
	/*PRTMP_ADAPTER pAd; */
	/*PAPCLI_STRUCT pApCli; */

#ifdef RELEASE_EXCLUDE
	DBGPRINT(RT_DEBUG_INFO, ("%s --->\n", __FUNCTION__));
#endif /* RELEASE_EXCLUDE */
	
	MEM_DBG_PKT_ALLOC_INC(skb_p);

	if(!(RTMP_OS_NETDEV_STATE_RUNNING(dev_p)))
	{
		/* the interface is down */
		RELEASE_NDIS_PACKET(NULL, skb_p, NDIS_STATUS_FAILURE);
		return 0;
	}

	return P2P_PacketSend(skb_p, dev_p, rt28xx_packet_xmit);

#if 0 /* os abl move */
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
		/*printk("1. P2P_VirtualIF_PacketSend @@@@@\n"); */
		return 0;
	}

	if(!(RTMP_OS_NETDEV_STATE_RUNNING(dev_p)))
	{
		/* the interface is down */
		RELEASE_NDIS_PACKET(pAd, skb_p, NDIS_STATUS_FAILURE);
		/*printk("2. P2P_VirtualIF_PacketSend @@@@@\n"); */
		return 0;
	}

	if (P2P_CLI_ON(pAd))
	{
		pApCli = (PAPCLI_STRUCT)&pAd->ApCfg.ApCliTab;

		if (pApCli[MAIN_MBSSID].Valid != TRUE)
		{
			RELEASE_NDIS_PACKET(pAd, skb_p, NDIS_STATUS_FAILURE);
			/*printk("3. P2P_VirtualIF_PacketSend @@@@@\n"); */
			return 0;
		}

		/* find the device in our ApCli list */
		if (pApCli[MAIN_MBSSID].dev == dev_p)
		{
			/* ya! find it */
			pAd->RalinkCounters.PendingNdisPacketCount ++;
			NdisZeroMemory((PUCHAR)&(RTPKT_TO_OSPKT(skb_p))->cb[CB_OFF], 15);
			RTMP_SET_PACKET_SOURCE(skb_p, PKTSRC_NDIS);
			RTMP_SET_PACKET_MOREDATA(skb_p, FALSE);
			RTMP_SET_PACKET_NET_DEVICE_APCLI(skb_p, MAIN_MBSSID);
			SET_OS_PKT_NETDEV(skb_p, pAd->net_dev);
			RTMP_SET_PACKET_OPMODE(skb_p, OPMODE_AP);

#ifdef RELEASE_EXCLUDE
			if (!(*(GET_OS_PKT_DATAPTR(RTPKT_TO_OSPKT(skb_p))) & 0x01))
			{
				DBGPRINT(RT_DEBUG_INFO, ("%s - unicast packet to (apcli%d)\n", 
							__FUNCTION__, MAIN_MBSSID));
			}
#endif /* RELEASE_EXCLUDE */

			/* transmit the packet */
			return rt28xx_packet_xmit(RTPKT_TO_OSPKT(skb_p));
		}
	}
	else
	{
		//printk("4. P2P_VirtualIF_PacketSend @@@@@\n");
        /* find the device in our p2p list */
		if (pAd->ApCfg.MBSSID[MAIN_MBSSID].MSSIDDev == dev_p)
		{
			/* ya! find it */
			pAd->RalinkCounters.PendingNdisPacketCount ++;
			NdisZeroMemory((PUCHAR)&(RTPKT_TO_OSPKT(skb_p))->cb[CB_OFF], 15);
			RTMP_SET_PACKET_SOURCE(skb_p, PKTSRC_NDIS);
			RTMP_SET_PACKET_MOREDATA(skb_p, FALSE);
			RTMP_SET_PACKET_NET_DEVICE_P2P(skb_p, MAIN_MBSSID);
			SET_OS_PKT_NETDEV(skb_p, pAd->net_dev);
			RTMP_SET_PACKET_OPMODE(skb_p, OPMODE_AP);

#ifdef RELEASE_EXCLUDE
			if (!(*(GET_OS_PKT_DATAPTR(RTPKT_TO_OSPKT(skb_p))) & 0x01))
			{
				DBGPRINT(RT_DEBUG_INFO, ("%s - unicast packet to (p2p%d)\n", 
							__FUNCTION__, MAIN_MBSSID));
			}
#endif /* RELEASE_EXCLUDE */

			/* transmit the packet */
			return rt28xx_packet_xmit(RTPKT_TO_OSPKT(skb_p));
		}
	}

	RELEASE_NDIS_PACKET(pAd, skb_p, NDIS_STATUS_FAILURE);
#ifdef RELEASE_EXCLUDE
	/* can not find the BSS so discard the packet */
	DBGPRINT(RT_DEBUG_INFO,
				("%s -Don't need to send or netdevice not exist.\n", 
				__FUNCTION__));
	DBGPRINT(RT_DEBUG_INFO, ("%s <---\n", __FUNCTION__));
#endif /* RELEASE_EXCLUDE */

	return 0;
#endif
}


VOID RTMP_P2P_Remove(
	IN VOID 	*pAd)
{
#ifdef RELEASE_EXCLUDE
	DBGPRINT(RT_DEBUG_TRACE, ("%s --->\n", __FUNCTION__));
#endif /* RELEASE_EXCLUDE */

	RTMP_COM_IoctlHandle(pAd, NULL, CMD_RTPRIV_IOCTL_P2P_REMOVE, 0, NULL, 0);

#if 0
	if (pAd->p2p_dev)
	{
		RtmpOSNetDevDetach(pAd->p2p_dev);
		RtmpOSNetDevFree(pAd->p2p_dev);

		/* clear it as NULL to prevent latter access error */
		pAd->p2p_dev = NULL;
		pAd->flg_p2p_init = FALSE;

		pMbss = &pAd->ApCfg.MBSSID[MAIN_MBSSID];
		pMbss->MSSIDDev = NULL;

		pAd->ApCfg.ApCliTab[MAIN_MBSSID].dev = NULL;
		pAd->flg_apcli_init = FALSE;
	}
#endif
		
#ifdef RELEASE_EXCLUDE
	DBGPRINT(RT_DEBUG_TRACE, ("%s <---\n", __FUNCTION__));
#endif /* RELEASE_EXCLUDE */
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
INT P2P_VirtualIF_Ioctl(
	IN PNET_DEV				dev_p, 
	IN OUT VOID 	*rq_p, 
	IN INT 					cmd)
{
/*
	RTMP_ADAPTER *pAd;

	pAd = RTMP_OS_NETDEV_GET_PRIV(dev_p);
	ASSERT(pAd);

	if (!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_INTERRUPT_IN_USE))
		return -ENETDOWN;
*/
		return rt28xx_ioctl(dev_p, rq_p, cmd);

}


#endif /* P2P_SUPPORT */

