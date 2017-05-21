/*
    Module Name:
    ap_apcli.c

    Abstract:
    Support AP-Client function.

    Note:
    1. Call RT28xx_ApCli_Init() in init function and
       call RT28xx_ApCli_Remove() in close function

    2. MAC of ApCli-interface is initialized in RT28xx_ApCli_Init()

    3. ApCli index (0) of different rx packet is got in
       APHandleRxDoneInterrupt() by using FromWhichBSSID = pEntry->apidx;
       Or FromWhichBSSID = BSS0;

    4. ApCli index (0) of different tx packet is assigned in
       MBSS_VirtualIF_PacketSend() by using RTMP_SET_PACKET_NET_DEVICE_MBSSID()
    5. ApCli index (0) of different interface is got in APHardTransmit() by using
       RTMP_GET_PACKET_IF()

    6. ApCli index (0) of IOCTL command is put in pAd->OS_Cookie->ioctl_if

    8. The number of ApCli only can be 1

	9. apcli convert engine subroutines, we should just take care data packet.
    Revision History:
    Who             When            What
    --------------  ----------      ----------------------------------------------
    Shiang, Fonchi  02-13-2007      created
*/
#define RTMP_MODULE_OS

#ifdef APCLI_SUPPORT

/*#include "rt_config.h" */
#include "rtmp_comm.h"
#include "rt_os_util.h"
#include "rt_os_net.h"


/*
========================================================================
Routine Description:
    Init AP-Client function.

Arguments:
    pAd            points to our adapter
    main_dev_p      points to the main BSS network interface

Return Value:
    None

Note:
	1. Only create and initialize virtual network interfaces.
	2. No main network interface here.
========================================================================
*/
VOID RT28xx_ApCli_Init(
	IN VOID 				*pAd,
	IN PNET_DEV				main_dev_p)
{
#if 0 /* os abl move */
#define APCLI_MAX_DEV_NUM	32
	PNET_DEV	new_dev_p;
/*	VIRTUAL_ADAPTER *apcli_pAd; */
	INT apcli_index;
	RTMP_OS_NETDEV_OP_HOOK	netDevOpHook;
	APCLI_STRUCT	*pApCliEntry;
	
	/* sanity check to avoid redundant virtual interfaces are created */
	if (pAd->flg_apcli_init != FALSE)
		return;

#ifdef RELEASE_EXCLUDE
	DBGPRINT(RT_DEBUG_INFO, ("%s --->\n", __FUNCTION__));
#endif /* RELEASE_EXCLUDE */

	/* init */
	for(apcli_index = 0; apcli_index < MAX_APCLI_NUM; apcli_index++)
		pAd->ApCfg.ApCliTab[apcli_index].dev = NULL;

	/* create virtual network interface */
	for(apcli_index = 0; apcli_index < MAX_APCLI_NUM; apcli_index++)
	{
		new_dev_p = RtmpOSNetDevCreate(pAd, INT_APCLI, apcli_index, sizeof(PRTMP_ADAPTER), INF_APCLI_DEV_NAME);
		RTMP_OS_NETDEV_SET_PRIV(new_dev_p, pAd);

		pApCliEntry = &pAd->ApCfg.ApCliTab[apcli_index];
		/* init MAC address of virtual network interface */
		COPY_MAC_ADDR(pApCliEntry->CurrentAddress, pAd->CurrentAddress);

#ifdef NEW_MBSSID_MODE
		if (pAd->ApCfg.BssidNum > 0 || MAX_MESH_NUM > 0) 
		{
			/* 	
				Refer to HW definition - 
					Bit1 of MAC address Byte0 is local administration bit 
					and should be set to 1 in extended multiple BSSIDs'
					Bit3~ of MAC address Byte0 is extended multiple BSSID index.
			 */ 
			pApCliEntry->CurrentAddress[0] += 2; 	
			pApCliEntry->CurrentAddress[0] += (((pAd->ApCfg.BssidNum + MAX_MESH_NUM) - 1) << 2);
		}
#else
		pApCliEntry->CurrentAddress[ETH_LENGTH_OF_ADDRESS - 1] =
			(pApCliEntry->CurrentAddress[ETH_LENGTH_OF_ADDRESS - 1] + pAd->ApCfg.BssidNum + MAX_MESH_NUM) & 0xFF;
#endif /* NEW_MBSSID_MODE */

		/* init operation functions */
		NdisZeroMemory(&netDevOpHook, sizeof(RTMP_OS_NETDEV_OP_HOOK));
		netDevOpHook.open = ApCli_VirtualIF_Open;
		netDevOpHook.stop = ApCli_VirtualIF_Close;
		netDevOpHook.xmit = ApCli_VirtualIF_PacketSend;
		netDevOpHook.ioctl = ApCli_VirtualIF_Ioctl;
		netDevOpHook.priv_flags = INT_APCLI; /* we are virtual interface */
		netDevOpHook.needProtcted = TRUE;
		NdisMoveMemory(&netDevOpHook.devAddr[0], &pApCliEntry->CurrentAddress[0], MAC_ADDR_LEN);
		
		/* register this device to OS */
		RtmpOSNetDevAttach(new_dev_p, &netDevOpHook);

		/* backup our virtual network interface */
		pApCliEntry->dev = new_dev_p;
        
#ifdef WSC_AP_SUPPORT
		pApCliEntry->WscControl.pAd = pAd;        
		NdisZeroMemory(pApCliEntry->WscControl.EntryAddr, MAC_ADDR_LEN);
		pApCliEntry->WscControl.WscConfigMethods= 0x008C;
		WscGenerateUUID(pAd, &pApCliEntry->WscControl.Wsc_Uuid_E[0], &pApCliEntry->WscControl.Wsc_Uuid_Str[0], 0, FALSE);
		WscInit(pAd, TRUE, apcli_index);
#endif /* WSC_AP_SUPPORT */
	} /* End of for */

	pAd->flg_apcli_init = TRUE;

#ifdef RELEASE_EXCLUDE
	DBGPRINT(RT_DEBUG_INFO, ("%s <---\n", __FUNCTION__));
#endif /* RELEASE_EXCLUDE */
#endif /* 0 */

	RTMP_OS_NETDEV_OP_HOOK	netDevOpHook;

	/* init operation functions */
	NdisZeroMemory(&netDevOpHook, sizeof(RTMP_OS_NETDEV_OP_HOOK));
	netDevOpHook.open = ApCli_VirtualIF_Open;
	netDevOpHook.stop = ApCli_VirtualIF_Close;
	netDevOpHook.xmit = ApCli_VirtualIF_PacketSend;
	netDevOpHook.ioctl = ApCli_VirtualIF_Ioctl;
	RTMP_AP_IoctlHandle(pAd, NULL, CMD_RTPRIV_IOCTL_APC_INIT,
						0, &netDevOpHook, 0);
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
INT ApCli_VirtualIF_Open(
	IN PNET_DEV		dev_p)
{
/*	UCHAR ifIndex; */
	VOID *pAd;

	pAd = RTMP_OS_NETDEV_GET_PRIV(dev_p);
	ASSERT(pAd);

	DBGPRINT(RT_DEBUG_TRACE, ("%s: ===> %s\n", __FUNCTION__, RTMP_OS_NETDEV_GET_DEVNAME(dev_p)));

	if (VIRTUAL_IF_UP(pAd) != 0)
		return -1;

	/* increase MODULE use count */
	RT_MOD_INC_USE_COUNT();

#if 0 /* os abl move */
	for (ifIndex = 0; ifIndex < MAX_APCLI_NUM; ifIndex++)
	{
		if (pAd->ApCfg.ApCliTab[ifIndex].dev == dev_p)
		{
			RTMP_OS_NETDEV_START_QUEUE(dev_p);
			ApCliIfUp(pAd);
		}
	}
#endif /* 0 */

	RTMP_AP_IoctlHandle(pAd, NULL, CMD_RTPRIV_IOCTL_APC_OPEN, 0, dev_p, 0);

	return 0;
} /* End of ApCli_VirtualIF_Open */


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
INT ApCli_VirtualIF_Close(
	IN	PNET_DEV	dev_p)
{
/*	UCHAR ifIndex; */
	VOID *pAd;

	pAd = RTMP_OS_NETDEV_GET_PRIV(dev_p);
	ASSERT(pAd);

	DBGPRINT(RT_DEBUG_TRACE, ("%s: ===> %s\n", __FUNCTION__, RTMP_OS_NETDEV_GET_DEVNAME(dev_p)));

#if 0 /* os abl move */
	for (ifIndex = 0; ifIndex < MAX_APCLI_NUM; ifIndex++)
	{
		if (pAd->ApCfg.ApCliTab[ifIndex].dev == dev_p)
		{
			RTMP_OS_NETDEV_STOP_QUEUE(dev_p);
			
			/* send disconnect-req to sta State Machine. */
			if (pAd->ApCfg.ApCliTab[ifIndex].Enable)
			{
				MlmeEnqueue(pAd, APCLI_CTRL_STATE_MACHINE, APCLI_CTRL_DISCONNECT_REQ, 0, NULL, ifIndex);
				RTMP_MLME_HANDLER(pAd);
				DBGPRINT(RT_DEBUG_TRACE, ("(%s) ApCli interface[%d] startdown.\n", __FUNCTION__, ifIndex));
			}
			break;
		}
	}
#endif /* 0 */

	RTMP_AP_IoctlHandle(pAd, NULL, CMD_RTPRIV_IOCTL_APC_CLOSE, 0, dev_p, 0);

	VIRTUAL_IF_DOWN(pAd);

	RT_MOD_DEC_USE_COUNT();

	return 0;
} /* End of ApCli_VirtualIF_Close */


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
INT ApCli_VirtualIF_PacketSend(
	IN PNDIS_PACKET 	pPktSrc, 
	IN PNET_DEV			pDev)
{
#if 0 /* os abl move */
	RTMP_ADAPTER *pAd;
	PAPCLI_STRUCT pApCli;
	INT apcliIndex;

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

	if (!(RTMP_OS_NETDEV_STATE_RUNNING(dev_p)))
	{
		/* the interface is down */
		RELEASE_NDIS_PACKET(pAd, skb_p, NDIS_STATUS_FAILURE);
		return 0;
	}


	pApCli = (PAPCLI_STRUCT)&pAd->ApCfg.ApCliTab;

	for(apcliIndex = 0; apcliIndex < MAX_APCLI_NUM; apcliIndex++)
	{
		if (pApCli[apcliIndex].Valid != TRUE)
			continue;

		/* find the device in our ApCli list */
		if (pApCli[apcliIndex].dev == dev_p)
		{
			/* ya! find it */
			pAd->RalinkCounters.PendingNdisPacketCount ++;
			RTMP_SET_PACKET_SOURCE(skb_p, PKTSRC_NDIS);
			RTMP_SET_PACKET_MOREDATA(skb_p, FALSE);
			RTMP_SET_PACKET_NET_DEVICE_APCLI(skb_p, apcliIndex);
			SET_OS_PKT_NETDEV(skb_p, pAd->net_dev);

#ifdef RELEASE_EXCLUDE
			if (!(*(GET_OS_PKT_DATAPTR(RTPKT_TO_OSPKT(skb_p))) & 0x01))
			{
				DBGPRINT(RT_DEBUG_INFO, ("%s - unicast packet to (apcli%d)\n", 
							__FUNCTION__, apcliIndex));
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
#endif /* 0 */

	MEM_DBG_PKT_ALLOC_INC(pPktSrc);

	if(!(RTMP_OS_NETDEV_STATE_RUNNING(pDev)))
	{
		/* the interface is down */
		RELEASE_NDIS_PACKET(NULL, pPktSrc, NDIS_STATUS_FAILURE);
		return 0;
	} /* End of if */

	return APC_PacketSend(pPktSrc, pDev, rt28xx_packet_xmit);
} /* End of ApCli_VirtualIF_PacketSend */


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
INT ApCli_VirtualIF_Ioctl(
	IN PNET_DEV				dev_p, 
	IN OUT VOID 			*rq_p, 
	IN INT 					cmd)
{
	VOID *pAd;

	pAd = RTMP_OS_NETDEV_GET_PRIV(dev_p);
	ASSERT(pAd);

/*	if (!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_INTERRUPT_IN_USE)) */
	if (RTMP_DRIVER_IOCTL_SANITY_CHECK(pAd, NULL) != NDIS_STATUS_SUCCESS)
		return -ENETDOWN;

	/* do real IOCTL */
	return (rt28xx_ioctl(dev_p, rq_p, cmd));
} /* End of ApCli_VirtualIF_Ioctl */


/*
========================================================================
Routine Description:
    Remove ApCli-BSS network interface.

Arguments:
    pAd            points to our adapter

Return Value:
    None

Note:
========================================================================
*/
VOID RT28xx_ApCli_Remove(
	IN VOID *pAd)
{
/*	UINT index; */

#ifdef RELEASE_EXCLUDE
	DBGPRINT(RT_DEBUG_INFO, ("%s --->\n", __FUNCTION__));
#endif /* RELEASE_EXCLUDE */

	RTMP_AP_IoctlHandle(pAd, NULL, CMD_RTPRIV_IOCTL_APC_REMOVE, 0, NULL, 0);

#if 0 /* os abl move */
	for(index = 0; index < MAX_APCLI_NUM; index++)
	{
		if (pAd->ApCfg.ApCliTab[index].dev)
		{
			RtmpOSNetDevDetach(pAd->ApCfg.ApCliTab[index].dev);

			RtmpOSNetDevFree(pAd->ApCfg.ApCliTab[index].dev);

			/* Clear it as NULL to prevent latter access error. */
			pAd->flg_apcli_init = FALSE;
			pAd->ApCfg.ApCliTab[index].dev = NULL;
		}
	}
#endif /* 0 */

#ifdef RELEASE_EXCLUDE
	DBGPRINT(RT_DEBUG_INFO, ("%s <---\n", __FUNCTION__));
#endif /* RELEASE_EXCLUDE */
}

#endif /* APCLI_SUPPORT */
