
/*
 ***************************************************************************
 * Ralink Tech Inc.
 * 4F, No. 2 Technology 5th Rd.
 * Science-based Industrial Park
 * Hsin-chu, Taiwan, R.O.C.
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
    ap_wds.c

    Abstract:
    Support WDS function.

    Revision History:
    Who       When            What
    ------    ----------      ----------------------------------------------
    Fonchi    02-13-2007      created
*/
#define RTMP_MODULE_OS

#ifdef WDS_SUPPORT

/*#include "rt_config.h" */
#include "rtmp_comm.h"
#include "rt_os_util.h"
#include "rt_os_net.h"

NET_DEV_STATS *RT28xx_get_wds_ether_stats(
    IN  PNET_DEV net_dev);


/* Register WDS interface */
VOID RT28xx_WDS_Init(
	IN VOID				*pAd,
	IN PNET_DEV			net_dev)
{
#if 0 /* os abl move */
	INT index;
	PNET_DEV pWdsNetDev;
	RTMP_OS_NETDEV_OP_HOOK netDevOpHook;
	
	/* sanity check to avoid redundant virtual interfaces are created */
	if (pAd->flg_wds_init != FALSE)
		return;

	for(index = 0; index < MAX_WDS_ENTRY; index++)
	{
		pWdsNetDev = RtmpOSNetDevCreate(pAd, INT_WDS, index, sizeof(PRTMP_ADAPTER), INF_WDS_DEV_NAME);
		if (pWdsNetDev == NULL)
		{
			/* allocation fail, exit */
			DBGPRINT(RT_DEBUG_ERROR, ("Allocate network device fail (WDS)...\n"));
			break;
		}
		else
		{
			PMAC_TABLE_ENTRY pWdsEntry;
			pWdsEntry = &pAd->MacTab.Content[pAd->WdsTab.WdsEntry[index].MacTabMatchWCID];
			DBGPRINT(RT_DEBUG_TRACE, ("The new WDS interface MAC = %02X:%02X:%02X:%02X:%02X:%02X\n", 
					PRINT_MAC(pWdsEntry->Addr)));
		}

		NdisZeroMemory(&pAd->WdsTab.WdsEntry[index].WdsCounter, sizeof(WDS_COUNTER));
		RTMP_OS_NETDEV_SET_PRIV(pWdsNetDev, pAd);
		pAd->WdsTab.WdsEntry[index].PhyMode = 0xff;
		pAd->WdsTab.WdsEntry[index].dev = pWdsNetDev;
		NdisZeroMemory((PUCHAR)&netDevOpHook, sizeof(RTMP_OS_NETDEV_OP_HOOK));
		netDevOpHook.open = WdsVirtualIF_open;
		netDevOpHook.stop = WdsVirtualIF_close;
		netDevOpHook.xmit = WdsVirtualIFSendPackets;
		netDevOpHook.ioctl = WdsVirtualIF_ioctl;
		netDevOpHook.priv_flags = INT_WDS; /* we are virtual interface */
		netDevOpHook.needProtcted = TRUE;
		netDevOpHook.get_stats = RT28xx_get_wds_ether_stats;
		NdisMoveMemory(&netDevOpHook.devAddr[0], RTMP_OS_NETDEV_GET_PHYADDR(net_dev), MAC_ADDR_LEN);
		DBGPRINT(RT_DEBUG_TRACE, ("The new WDS interface MAC = %02X:%02X:%02X:%02X:%02X:%02X\n", 
					PRINT_MAC(netDevOpHook.devAddr)));

		/* Register this device */
		RtmpOSNetDevAttach(pWdsNetDev, &netDevOpHook);

		pAd->WdsTab.WdsEntry[index].PhyMode = 0xff;
		pAd->WdsTab.WdsEntry[index].dev = pWdsNetDev;
	}

	pAd->flg_wds_init = TRUE;
#endif /* 0 */

	RTMP_OS_NETDEV_OP_HOOK	netDevOpHook;

	NdisZeroMemory((PUCHAR)&netDevOpHook, sizeof(RTMP_OS_NETDEV_OP_HOOK));
	netDevOpHook.open = WdsVirtualIF_open;
	netDevOpHook.stop = WdsVirtualIF_close;
	netDevOpHook.xmit = WdsVirtualIFSendPackets;
	netDevOpHook.ioctl = WdsVirtualIF_ioctl;
	netDevOpHook.get_stats = RT28xx_get_wds_ether_stats;
	NdisMoveMemory(&netDevOpHook.devAddr[0], RTMP_OS_NETDEV_GET_PHYADDR(net_dev), MAC_ADDR_LEN);
	DBGPRINT(RT_DEBUG_TRACE, ("The new WDS interface MAC = %02X:%02X:%02X:%02X:%02X:%02X\n", 
				PRINT_MAC(netDevOpHook.devAddr)));

	RTMP_AP_IoctlHandle(pAd, NULL, CMD_RTPRIV_IOCTL_WDS_INIT,
						0, &netDevOpHook, 0);
	
}


INT WdsVirtualIFSendPackets(
	IN PNDIS_PACKET			pPktSrc, 
	IN PNET_DEV				pDev)
{
#if 0 /* os abl move */
	UCHAR i;
	RTMP_ADAPTER *pAd;
	PNDIS_PACKET pPacket = (PNDIS_PACKET) pSkb;

	pAd = (PRTMP_ADAPTER) RTMP_OS_NETDEV_GET_PRIV(dev);

#ifdef RELEASE_EXCLUDE
	DBGPRINT(RT_DEBUG_INFO, ("%s --->\n", __FUNCTION__));
#endif /* RELEASE_EXCLUDE */

#ifdef RALINK_ATE
	if (ATE_ON(pAd))
	{
		RELEASE_NDIS_PACKET(pAd, pPacket, NDIS_STATUS_FAILURE);
		return 0;
	}
#endif /* RALINK_ATE */

	if ((RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_BSS_SCAN_IN_PROGRESS)) ||
		(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_RADIO_OFF))          ||
		(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_RESET_IN_PROGRESS)))
	{
		RELEASE_NDIS_PACKET(pAd, pPacket, NDIS_STATUS_FAILURE);
		return 0;
	}
	
	if (!(RTMP_OS_NETDEV_STATE_RUNNING(dev)))
	{
		RELEASE_NDIS_PACKET(pAd, pPacket, NDIS_STATUS_FAILURE);
		return 0;
	}

	for (i = 0; i < MAX_WDS_ENTRY; i++)
	{
		if (ValidWdsEntry(pAd, i) && (pAd->WdsTab.WdsEntry[i].dev == dev))
		{
			RTMP_SET_PACKET_NET_DEVICE_WDS(pSkb, i);
			SET_OS_PKT_NETDEV(pSkb, pAd->net_dev);

#ifdef RELEASE_EXCLUDE
			DBGPRINT(RT_DEBUG_INFO, ("VirtualIFSendPackets(WDS) - packet to (%d)\n", i));
#endif /* RELEASE_EXCLUDE */
			return rt28xx_packet_xmit(pSkb);
		}
	}

	
	RELEASE_NDIS_PACKET(pAd, pPacket, NDIS_STATUS_FAILURE);
#ifdef RELEASE_EXCLUDE
	DBGPRINT(RT_DEBUG_INFO, ("VirtualIFSendPackets - needn't to send or net_device not exist.\n"));
	DBGPRINT(RT_DEBUG_INFO, ("%s <---\n", __FUNCTION__));
#endif /* RELEASE_EXCLUDE */
	return 0;
#endif /* 0 */

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

	return WDS_PacketSend(pPktSrc, pDev, rt28xx_packet_xmit);
}


INT WdsVirtualIF_open(
	IN	PNET_DEV dev)
{
	VOID			*pAd;
#ifdef RTL865X_SOC
	INT				index;
	unsigned int 	linkid;
#endif

	DBGPRINT(RT_DEBUG_TRACE, ("%s: ===> VirtualIF_open\n", RTMP_OS_NETDEV_GET_DEVNAME(dev)));


	pAd = RTMP_OS_NETDEV_GET_PRIV(dev);
	if (VIRTUAL_IF_UP(pAd) != 0)
		return -1;

	/* increase MODULE use count */
	RT_MOD_INC_USE_COUNT();
	
	RTMP_OS_NETDEV_START_QUEUE(dev);
	return 0;
}


INT WdsVirtualIF_close(
	IN PNET_DEV dev)
{
	VOID		*pAd;

	DBGPRINT(RT_DEBUG_TRACE, ("%s: ===> VirtualIF_close\n", RTMP_OS_NETDEV_GET_DEVNAME(dev)));


	pAd = RTMP_OS_NETDEV_GET_PRIV(dev);

	//RTMP_OS_NETDEV_CARRIER_OFF(dev);
	RTMP_OS_NETDEV_STOP_QUEUE(dev);
	
	VIRTUAL_IF_DOWN(pAd);

	RT_MOD_DEC_USE_COUNT();

	return 0;
}


INT WdsVirtualIF_ioctl(
	IN PNET_DEV net_dev, 
	IN OUT VOID *rq, 
	IN INT cmd)
{
	VOID *pAd = RTMP_OS_NETDEV_GET_PRIV(net_dev); /*RTMP_OS_NETDEV_GET_PRIV(pVirtualAd->RtmpDev); */
	
/*	if(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_INTERRUPT_IN_USE)) */
	if (RTMP_DRIVER_IOCTL_SANITY_CHECK(pAd, NULL) != NDIS_STATUS_SUCCESS)
	{
		DBGPRINT(RT_DEBUG_TRACE, ("VirtualIF_ioctl(%s)::Network is down!\n", RTMP_OS_NETDEV_GET_DEVNAME(net_dev)));
		return -ENETDOWN;
	}

	return rt28xx_ioctl(net_dev, rq, cmd);
}


VOID RT28xx_WDS_Remove(
	IN VOID				*pAd)
{
#if 0 /* os abl move */
	PRTMP_ADAPTER pAd = (PRTMP_ADAPTER)pAdSrc;
	UINT index;

	for(index = 0; index < MAX_WDS_ENTRY; index++)
	{
		if (pAd->WdsTab.WdsEntry[index].dev)
	    {
			RtmpOSNetDevDetach(pAd->WdsTab.WdsEntry[index].dev);
			RtmpOSNetDevFree(pAd->WdsTab.WdsEntry[index].dev);

			/* Clear it as NULL to prevent latter access error. */
			pAd->WdsTab.WdsEntry[index].dev = NULL;
		}
	}
#endif /* 0 */

	RTMP_AP_IoctlHandle(pAd, NULL, CMD_RTPRIV_IOCTL_WDS_REMOVE, 0, NULL, 0);
}

#endif /* WDS_SUPPORT */
