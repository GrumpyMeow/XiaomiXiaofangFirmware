/*
 ***************************************************************************
 * Ralink Tech Inc.
 * 4F, No. 2 Technology 5th Rd.
 * Science-based Industrial Park
 * Hsin-chu, Taiwan, R.O.C.
 *
 * (c) Copyright 2002-2004, Ralink Technology, Inc.
 *
 * All rights reserved. Ralink's source code is an unpublished work and the
 * use of a copyright notice does not imply otherwise. This source code
 * contains confidential trade secret material of Ralink Tech. Any attemp
 * or participation in deciphering, decoding, reverse engineering or in any
 * way altering the source code is stricitly prohibited, unless the prior
 * written consent of Ralink Technology, Inc. is obtained.
 ***************************************************************************

	Module Name:
	rtmp_init.c

	Abstract:
	Miniport generic portion header file

	Revision History:
	Who         When          What
	--------    ----------    ----------------------------------------------
*/
#include	"rt_config.h"
#ifdef DOT11R_FT_SUPPORT
#include	"ft.h"
#endif /* DOT11R_FT_SUPPORT */

#ifdef OS_ABL_FUNC_SUPPORT
/* Os utility link: printk, scanf */
RTMP_OS_ABL_OPS RaOsOps, *pRaOsOps = &RaOsOps;
#endif /* OS_ABL_FUNC_SUPPORT */

#ifdef RELEASE_EXCLUDE

/* RT3090A's default internal LNA gain*/

#endif /* RELEASE_EXCLUDE */
#define RT3090A_DEFAULT_INTERNAL_LNA_GAIN	0x0A
UCHAR NUM_BIT8[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
#if 0
ULONG BIT32[] = {0x00000001, 0x00000002, 0x00000004, 0x00000008,
					0x00000010, 0x00000020, 0x00000040, 0x00000080,
					0x00000100, 0x00000200, 0x00000400, 0x00000800,
					0x00001000, 0x00002000, 0x00004000, 0x00008000,
					0x00010000, 0x00020000, 0x00040000, 0x00080000,
					0x00100000, 0x00200000, 0x00400000, 0x00800000,
					0x01000000, 0x02000000, 0x04000000, 0x08000000,
					0x10000000, 0x20000000, 0x40000000, 0x80000000};
#endif
#ifdef DBG
char*   CipherName[] = {"none","wep64","wep128","TKIP","AES","CKIP64","CKIP128","CKIP152","SMS4"};
#endif


/* 
	ASIC register initialization sets
*/
RTMP_REG_PAIR MACRegTable[] = {
#ifndef MT7601
#if defined(HW_BEACON_OFFSET) && (HW_BEACON_OFFSET == 0x200)
	{BCN_OFFSET0,			0xf8f0e8e0}, /* 0x3800(e0), 0x3A00(e8), 0x3C00(f0), 0x3E00(f8), 512B for each beacon */
	{BCN_OFFSET1,			0x6f77d0c8}, /* 0x3200(c8), 0x3400(d0), 0x1DC0(77), 0x1BC0(6f), 512B for each beacon */
#elif defined(HW_BEACON_OFFSET) && (HW_BEACON_OFFSET == 0x100)
	{BCN_OFFSET0,			0xece8e4e0}, /* 0x3800, 0x3A00, 0x3C00, 0x3E00, 512B for each beacon */
	{BCN_OFFSET1,			0xfcf8f4f0}, /* 0x3800, 0x3A00, 0x3C00, 0x3E00, 512B for each beacon */
#endif /* HW_BEACON_OFFSET */
#endif /* MT7601 */

	{LEGACY_BASIC_RATE,		0x0000013f}, /*  Basic rate set bitmap*/
	{HT_BASIC_RATE,		0x00008003}, /* Basic HT rate set , 20M, MCS=3, MM. Format is the same as in TXWI.*/
	{MAC_SYS_CTRL,		0x00}, /* 0x1004, , default Disable RX*/
	{RX_FILTR_CFG,		0x17f97}, /*0x1400  , RX filter control,  */
	{BKOFF_SLOT_CFG,	0x209}, /* default set short slot time, CC_DELAY_TIME should be 2	 */
	/*{TX_SW_CFG0,		0x40a06},  Gary,2006-08-23 */
	{TX_SW_CFG0,		0x0}, 		/* Gary,2008-05-21 for CWC test */
	{TX_SW_CFG1,		0x80606}, /* Gary,2006-08-23 */
	{TX_LINK_CFG,		0x1020},		/* Gary,2006-08-23 */
	/*{TX_TIMEOUT_CFG,	0x00182090},	 CCK has some problem. So increase timieout value. 2006-10-09 MArvek RT*/
	{TX_TIMEOUT_CFG,	0x000a2090},	/* CCK has some problem. So increase timieout value. 2006-10-09 MArvek RT , Modify for 2860E ,2007-08-01*/
	{MAX_LEN_CFG,		MAX_AGGREGATION_SIZE | 0x00001000},	/* 0x3018, MAX frame length. Max PSDU = 16kbytes.*/
#ifndef MT7601
	{LED_CFG,		0x7f031e46}, /* Gary, 2006-08-23*/
#endif /* MT7601 */

#ifdef RLT_MAC

#ifdef MT7601
	{TX_MAX_PCNT,		0x1fbf1f1f},
	{RX_MAX_PCNT,		0x9f},
#else
	{TX_MAX_PCNT,		0xbfbf3f1f},
	{RX_MAX_PCNT,		0x9f},
#endif

// TODO: shiang-6590, need set this in FPGA mode
#ifdef RTMP_MAC_USB
#if 0
#ifdef FPGA_MODE
	{0x120c, 			0},	/* aux_clk_en, because FPGA don't have aux_clk(clock switch), but real chip will need this! */
#endif /* FPGA_MODE */
#endif
#endif /* RTMP_MAC_USB */
#else
#ifdef INF_AMAZON_SE
	{PBF_MAX_PCNT,			0x1F3F6F6F}, 	/*iverson modify for usb issue, 2008/09/19*/
											/* 6F + 6F < total page count FE*/
											/* so that RX doesn't occupy TX's buffer space when WMM congestion.*/
#else
	{PBF_MAX_PCNT,			0x1F3FBF9F}, 	/*0x1F3f7f9f},		Jan, 2006/04/20*/
#endif /* INF_AMAZON_SE */
#endif /* RLT_MAC */

	/*{TX_RTY_CFG,			0x6bb80408},	 Jan, 2006/11/16*/
/* WMM_ACM_SUPPORT*/
/*	{TX_RTY_CFG,			0x6bb80101},	 sample*/
	{TX_RTY_CFG,			0x47d01f0f},	/* Jan, 2006/11/16, Set TxWI->ACK =0 in Probe Rsp Modify for 2860E ,2007-08-03*/
	
	{AUTO_RSP_CFG,			0x00000013},	/* Initial Auto_Responder, because QA will turn off Auto-Responder*/
	{CCK_PROT_CFG,			0x05740003 /*0x01740003*/},	/* Initial Auto_Responder, because QA will turn off Auto-Responder. And RTS threshold is enabled. */
	{OFDM_PROT_CFG,			0x05740003 /*0x01740003*/},	/* Initial Auto_Responder, because QA will turn off Auto-Responder. And RTS threshold is enabled. */
#ifdef RTMP_MAC_USB
#ifndef MT7601
	{PBF_CFG, 				0xf40006}, 		/* Only enable Queue 2*/
	{WPDMA_GLO_CFG,			0x00000030},		// MT7601U not support WPDMA
#endif /* MT7601 */
	{MM40_PROT_CFG,			0x3F44084},		/* Initial Auto_Responder, because QA will turn off Auto-Responder*/
#endif /* RTMP_MAC_USB */
	{GF20_PROT_CFG,			0x01744004},    /* set 19:18 --> Short NAV for MIMO PS*/
	{GF40_PROT_CFG,			0x03F44084},    
	{MM20_PROT_CFG,			0x01744004},    
#ifdef RTMP_MAC_PCI
	{MM40_PROT_CFG,			0x03F54084},	
#endif /* RTMP_MAC_PCI */
	{TXOP_CTRL_CFG,			0x0000583f, /*0x0000243f*/ /*0x000024bf*/},	/*Extension channel backoff.*/
	{TX_RTS_CFG,			0x01092b20},		// enable RTS fall back

	{EXP_ACK_TIME,			0x002400ca},	/* default value */
#if 0
#ifdef WIFI_TEST
	{EXP_ACK_TIME,			0x002400ca},	/* default value */
#else
	{EXP_ACK_TIME,			0x005400ca},	 /* suggested by Gray @ 20070323 for 11n intel-sta throughput */
#endif  /* WIFI_TEST */
#ifdef CONFIG_AP_SUPPORT
	{TBTT_SYNC_CFG,			0x00422000},	 /* TBTT_ADJUST(7:0) == 0	*/
	{TBTT_SYNC_CFG,			0x00012000},	 /* TBTT_ADJUST(7:0) == 0	*/
#endif /* CONFIG_AP_SUPPORT */
#endif
	{TXOP_HLDR_ET, 			0x00000002},

	/* Jerry comments 2008/01/16: we use SIFS = 10us in CCK defaultly, but it seems that 10us
		is too small for INTEL 2200bg card, so in MBSS mode, the delta time between beacon0
		and beacon1 is SIFS (10us), so if INTEL 2200bg card connects to BSS0, the ping
		will always lost. So we change the SIFS of CCK from 10us to 16us. */
	{XIFS_TIME_CFG,			0x33a41010},
#if defined(RT65xx) || defined(MT7601)
	{PWR_PIN_CFG,			0x00000000},
#else
	{PWR_PIN_CFG,			0x00000003},	/* patch for 2880-E*/
#endif /* defined(RT65xx) || defined(MT7601) */
};

#ifdef CONFIG_AP_SUPPORT
RTMP_REG_PAIR	APMACRegTable[] =	{
	{WMM_AIFSN_CFG,		0x00001173},
	{WMM_CWMIN_CFG,	0x00002344},
	{WMM_CWMAX_CFG,	0x000034a6},
	{WMM_TXOP0_CFG,		0x00100020},
	{WMM_TXOP1_CFG,		0x002F0038},
	{TBTT_SYNC_CFG,		0x00012000},
#ifdef STREAM_MODE_SUPPORT
	{TX_CHAIN_ADDR0_L,	0xFFFFFFFF},	/* Broadcast frames are in stream mode*/
	{TX_CHAIN_ADDR0_H,	0x3FFFF},
#endif /* STREAM_MODE_SUPPORT */
};
#endif /* CONFIG_AP_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
RTMP_REG_PAIR	STAMACRegTable[] =	{
	{WMM_AIFSN_CFG,		0x00002273},
	{WMM_CWMIN_CFG,	0x00002344},
	{WMM_CWMAX_CFG,	0x000034aa},
};
#endif /* CONFIG_STA_SUPPORT */


#define	NUM_MAC_REG_PARMS		(sizeof(MACRegTable) / sizeof(RTMP_REG_PAIR))
#ifdef CONFIG_AP_SUPPORT
#define	NUM_AP_MAC_REG_PARMS	(sizeof(APMACRegTable) / sizeof(RTMP_REG_PAIR))
#endif /* CONFIG_AP_SUPPORT */
#ifdef CONFIG_STA_SUPPORT
#define	NUM_STA_MAC_REG_PARMS	(sizeof(STAMACRegTable) / sizeof(RTMP_REG_PAIR))
#endif /* CONFIG_STA_SUPPORT */


/*
	Use the global variable is not a good solution.
	But we can not put it to pAd and use the lock in pAd of RALINK_TIMER_STRUCT;
	Or when the structure is cleared, we maybe get NULL for pAd and can not lock.
	Maybe we can put pAd in RTMPSetTimer/ RTMPModTimer/ RTMPCancelTimer.
*/
NDIS_SPIN_LOCK TimerSemLock;


/*
	========================================================================
	
	Routine Description:
		Allocate RTMP_ADAPTER data block and do some initialization

	Arguments:
		Adapter		Pointer to our adapter

	Return Value:
		NDIS_STATUS_SUCCESS
		NDIS_STATUS_FAILURE

	IRQL = PASSIVE_LEVEL

	Note:
	
	========================================================================
*/
NDIS_STATUS	RTMPAllocAdapterBlock(
	IN  PVOID	handle,
	OUT	VOID	**ppAdapter)
{
	PRTMP_ADAPTER	pAd = NULL;
	NDIS_STATUS		Status;
	INT 			index;
	UCHAR			*pBeaconBuf = NULL;


#ifdef OS_ABL_FUNC_SUPPORT
	/* must put the function before any print message */
	/* init OS utilities provided from UTIL module */
	RtmpOsOpsInit(&RaOsOps);
#endif /* OS_ABL_FUNC_SUPPORT */

	DBGPRINT(RT_DEBUG_TRACE, ("--> RTMPAllocAdapterBlock\n"));

	/* init UTIL module */
	RtmpUtilInit();

	*ppAdapter = NULL;

	do
	{
		/* Allocate RTMP_ADAPTER memory block*/
/*		pBeaconBuf = kmalloc(MAX_BEACON_SIZE, MEM_ALLOC_FLAG);*/
		os_alloc_mem(NULL, (UCHAR **)&pBeaconBuf, MAX_BEACON_SIZE);
		if (pBeaconBuf == NULL)
		{
			Status = NDIS_STATUS_FAILURE;
			DBGPRINT_ERR(("Failed to allocate memory - BeaconBuf!\n"));
			break;
		}
		NdisZeroMemory(pBeaconBuf, MAX_BEACON_SIZE);

		Status = AdapterBlockAllocateMemory(handle, (PVOID *)&pAd, sizeof(RTMP_ADAPTER));
		if (Status != NDIS_STATUS_SUCCESS)
		{
			DBGPRINT_ERR(("Failed to allocate memory - ADAPTER\n"));
			break;
		}
		else
		{
			/* init resource list (must be after pAd allocation) */
			initList(&pAd->RscTimerMemList);
			initList(&pAd->RscTaskMemList);
			initList(&pAd->RscLockMemList);
			initList(&pAd->RscTaskletMemList);
			initList(&pAd->RscSemMemList);
			initList(&pAd->RscAtomicMemList);

			initList(&pAd->RscTimerCreateList);

			pAd->OS_Cookie = handle;
#ifdef WORKQUEUE_BH
			((POS_COOKIE)(handle))->pAd_va = pAd;
#endif /* WORKQUEUE_BH */
		}
		pAd->BeaconBuf = pBeaconBuf;
		DBGPRINT(RT_DEBUG_OFF, ("\n\n=== pAd = %p, size = %d ===\n\n", pAd, (UINT32)sizeof(RTMP_ADAPTER)));

		if (RtmpOsStatsAlloc(&pAd->stats, &pAd->iw_stats) == FALSE)
		{
			Status = NDIS_STATUS_FAILURE;
			break;
		}

		/* Init spin locks*/
		NdisAllocateSpinLock(pAd, &pAd->MgmtRingLock);
#ifdef RTMP_MAC_PCI
		NdisAllocateSpinLock(pAd, &pAd->RxRingLock);
#if defined(RT3090) || defined(RT3592) || defined(RT3390) || defined(RT3593) || defined(RT5390) || defined(RT5392) || defined(RT5592)
#ifdef CONFIG_STA_SUPPORT
	NdisAllocateSpinLock(pAd, &pAd->McuCmdLock);
#endif /* CONFIG_STA_SUPPORT */
#endif /* defined(RT3090) || defined(RT3592) || defined(RT3390) || defined(RT3593) || defined(RT5390) || defined(RT5392) */
#endif /* RTMP_MAC_PCI */

#if defined(RT3290) || defined(RT65xx) || defined(MT7601)
#ifdef RTMP_MAC_PCI
		NdisAllocateSpinLock(pAd, &pAd->WlanEnLock);
#endif
#endif /* defined(RT3290) || defined(RT65xx) || defined(MT7601) */

		for (index =0 ; index < NUM_OF_TX_RING; index++)
		{
			NdisAllocateSpinLock(pAd, &pAd->TxSwQueueLock[index]);
			NdisAllocateSpinLock(pAd, &pAd->DeQueueLock[index]);
			pAd->DeQueueRunning[index] = FALSE;
		}

#ifdef RESOURCE_PRE_ALLOC
		/* 
			move this function from rt28xx_init() to here. now this function only allocate memory and
			leave the initialization job to RTMPInitTxRxRingMemory() which called in rt28xx_init().
		*/
		Status = RTMPAllocTxRxRingMemory(pAd);
		if (Status != NDIS_STATUS_SUCCESS)
		{
			DBGPRINT_ERR(("Failed to allocate memory - TxRxRing\n"));
			break;
		}
#endif /* RESOURCE_PRE_ALLOC */

		NdisAllocateSpinLock(pAd, &pAd->irq_lock);

#ifdef RTMP_MAC_PCI
		NdisAllocateSpinLock(pAd, &pAd->LockInterrupt);
#endif /* RTMP_MAC_PCI */

		NdisAllocateSpinLock(pAd, &TimerSemLock);

#ifdef SPECIFIC_BCN_BUF_SUPPORT
#ifdef RTMP_MAC_PCI
		NdisAllocateSpinLock(pAd, &pAd->ShrMemLock);
#endif /* RTMP_MAC_PCI */
#ifdef RTMP_MAC_USB
		RTMP_SEM_EVENT_INIT(&pAd->ShrMemSemaphore, &pAd->RscSemMemList);
#endif /* RTMP_MAC_USB */
#endif /* SPECIFIC_BCN_BUF_SUPPORT */

#ifdef WMM_ACM_SUPPORT
		NdisAllocateSpinLock(pAd, &pAd->AcmTspecSemLock);
		NdisAllocateSpinLock(pAd, &pAd->AcmTspecIrqLock);
#endif /* WMM_ACM_SUPPORT */

#ifdef RALINK_ATE
#ifdef RTMP_MAC_USB
		RTMP_OS_ATMOIC_INIT(&pAd->BulkOutRemained, &pAd->RscAtomicMemList);
		RTMP_OS_ATMOIC_INIT(&pAd->BulkInRemained, &pAd->RscAtomicMemList);
#endif /* RTMP_MAC_USB */
#endif /* RALINK_ATE */

#ifdef CONFIG_AP_SUPPORT
#ifdef UAPSD_SUPPORT
/*        UAPSD_Init(pAd);  move to rt28xx_init*/
#endif /* UAPSD_SUPPORT */
#endif /* CONFIG_AP_SUPPORT */

		/* assign function pointers*/
#ifdef MAT_SUPPORT
		/* init function pointers, used in OS_ABL */
/*		RTMP_MATOpsInit(pAd);  move to rt28xx_init*/
#endif /* MAT_SUPPORT */
	} while (FALSE);

	if ((Status != NDIS_STATUS_SUCCESS) && (pBeaconBuf))
/*		kfree(pBeaconBuf);*/
		os_free_mem(NULL, pBeaconBuf);

	if ((Status != NDIS_STATUS_SUCCESS) && (pAd != NULL))
	{
		if (pAd->stats != NULL)
			os_free_mem(NULL, pAd->stats);

		if (pAd->iw_stats != NULL)
			os_free_mem(NULL, pAd->iw_stats);
	}

	if (pAd != NULL) /* compile warning: avoid use NULL pointer when pAd == NULL */
		*ppAdapter = (VOID *)pAd;

#ifdef RELEASE_EXCLUDE
#ifdef CONFIG_AP_SUPPORT
#ifdef RTMP_MAC_PCI
{
	/* purpose: Used to monitor the data size in pAd */
	UINT32 Size;

	DBGPRINT(RT_DEBUG_TRACE, ("size> pAd = \t\t%d bytes\n\n", sizeof(*pAd)));

	DBGPRINT(RT_DEBUG_TRACE, ("size> pAd->ApCfg = \t%d bytes\n", sizeof(pAd->ApCfg)));

	DBGPRINT(RT_DEBUG_TRACE, ("size> pAd->TxRing = \t%d bytes\n", sizeof(pAd->TxRing)));
	DBGPRINT(RT_DEBUG_TRACE, ("size> pAd->RxRing = \t%d bytes\n", sizeof(pAd->RxRing)));
	DBGPRINT(RT_DEBUG_TRACE, ("size> pAd->MgmtRing = \t%d bytes\n", sizeof(pAd->MgmtRing)));
	DBGPRINT(RT_DEBUG_TRACE, ("size> pAd->CommonCfg = \t%d bytes\n", sizeof(pAd->CommonCfg)));
	DBGPRINT(RT_DEBUG_TRACE, ("size> pAd->Mlme = \t%d bytes\n", sizeof(pAd->Mlme)));
	DBGPRINT(RT_DEBUG_TRACE, ("size> pAd->MlmeAux = \t%d bytes\n", sizeof(pAd->MlmeAux)));
	DBGPRINT(RT_DEBUG_TRACE, ("size> pAd->MacTab = \t%d bytes\n", sizeof(pAd->MacTab)));

	Size = sizeof(pAd->ApCfg) + sizeof(pAd->TxRing) +
			sizeof(pAd->RxRing) + sizeof(pAd->MgmtRing) +
			sizeof(pAd->CommonCfg) + sizeof(pAd->Mlme) +
			sizeof(pAd->MlmeAux) + sizeof(pAd->MacTab);

#ifdef DOT11_N_SUPPORT
	DBGPRINT(RT_DEBUG_TRACE, ("size> pAd->BATable = \t%d bytes\n", sizeof(pAd->BATable)));
	Size += sizeof(pAd->BATable);
#endif /* DOT11_N_SUPPORT */

	DBGPRINT(RT_DEBUG_TRACE, ("size> pAd->Counter** = \t%d bytes\n",
			sizeof(pAd->Counters8023) + sizeof(pAd->WlanCounters) +
			sizeof(pAd->RalinkCounters) + /* sizeof(pAd->DrsCounters) */+
			sizeof(pAd->PrivateInfo)));
	Size += sizeof(pAd->Counters8023) + sizeof(pAd->WlanCounters) +
			sizeof(pAd->RalinkCounters) + /* sizeof(pAd->DrsCounters) */ +
			sizeof(pAd->PrivateInfo);
#if defined (AP_SCAN_SUPPORT) || defined (CONFIG_STA_SUPPORT)
	DBGPRINT(RT_DEBUG_TRACE, ("size> pAd->ScanTab = \t%d bytes\n", sizeof(pAd->ScanTab)));
	Size += sizeof(pAd->ScanTab);
#endif
	DBGPRINT(RT_DEBUG_TRACE, ("\nsize> Total = \t\t%d bytes, Others = %d bytes\n\n",
			Size, sizeof(*pAd)-Size));
}
#endif /* RTMP_MAC_PCI */
#endif /* CONFIG_AP_SUPPORT */
#endif /* RELEASE_EXCLUDE */

	/*
		Init ProbeRespIE Table
	*/
	for (index = 0; index < MAX_LEN_OF_BSS_TABLE; index++) 
	{
		if (os_alloc_mem(pAd,&pAd->ProbeRespIE[index].pIe, MAX_VIE_LEN) == NDIS_STATUS_SUCCESS)
			RTMPZeroMemory(pAd->ProbeRespIE[index].pIe, MAX_VIE_LEN);
		else
			pAd->ProbeRespIE[index].pIe = NULL;
	}	

	DBGPRINT_S(Status, ("<-- RTMPAllocAdapterBlock, Status=%x\n", Status));
	return Status;
}


/*
	========================================================================
	
	Routine Description:
		Read initial parameters from EEPROM
		
	Arguments:
		Adapter						Pointer to our adapter

	Return Value:
		None

	IRQL = PASSIVE_LEVEL

	Note:
		
	========================================================================
*/
VOID NICReadEEPROMParameters(RTMP_ADAPTER *pAd, PSTRING mac_addr)
{
	USHORT i, value, value2;
	EEPROM_TX_PWR_STRUC Power;
	EEPROM_VERSION_STRUC Version;
	EEPROM_ANTENNA_STRUC Antenna;
	EEPROM_NIC_CONFIG2_STRUC NicConfig2;
	USHORT  Addr01,Addr23,Addr45 ;
	MAC_DW0_STRUC csr2;
	MAC_DW1_STRUC csr3;


	DBGPRINT(RT_DEBUG_TRACE, ("--> NICReadEEPROMParameters\n"));	

#ifdef RT3290
	if (IS_RT3290(pAd))
		RT3290_eeprom_access_grant(pAd, TRUE);
#endif /* RT3290 */

	if (pAd->chipOps.eeinit)
	{
		pAd->chipOps.eeinit(pAd);
#ifdef RTMP_EFUSE_SUPPORT
#ifdef RALINK_ATE
		if(!pAd->bFroceEEPROMBuffer && pAd->bEEPROMFile)
		{
			DBGPRINT(RT_DEBUG_OFF, ("--> NICReadEEPROMParameters::(Efuse)Load to EEPROM Buffer Mode\n"));	
			eFuseLoadEEPROM(pAd);
		}
#endif /* RALINK_ATE */
#endif /* RTMP_EFUSE_SUPPORT */
	}

	/* Read MAC setting from EEPROM and record as permanent MAC address */
	DBGPRINT(RT_DEBUG_TRACE, ("Initialize MAC Address from E2PROM \n"));

	RT28xx_EEPROM_READ16(pAd, 0x04, Addr01);
	RT28xx_EEPROM_READ16(pAd, 0x06, Addr23);
	RT28xx_EEPROM_READ16(pAd, 0x08, Addr45);

	pAd->PermanentAddress[0] = (UCHAR)(Addr01 & 0xff);
	pAd->PermanentAddress[1] = (UCHAR)(Addr01 >> 8);
	pAd->PermanentAddress[2] = (UCHAR)(Addr23 & 0xff);
	pAd->PermanentAddress[3] = (UCHAR)(Addr23 >> 8);
	pAd->PermanentAddress[4] = (UCHAR)(Addr45 & 0xff);
	pAd->PermanentAddress[5] = (UCHAR)(Addr45 >> 8);

	/*more conveninet to test mbssid, so ap's bssid &0xf1*/
	if (pAd->PermanentAddress[0] == 0xff)
		pAd->PermanentAddress[0] = RandomByte(pAd)&0xf8;
			
	DBGPRINT(RT_DEBUG_TRACE, ("E2PROM MAC: =%02x:%02x:%02x:%02x:%02x:%02x\n",
								PRINT_MAC(pAd->PermanentAddress)));

	/* Assign the actually working MAC Address */
	if (pAd->bLocalAdminMAC)
	{		
		DBGPRINT(RT_DEBUG_TRACE, ("Use the MAC address what is assigned from Configuration file(.dat). \n"));
	}
	else if (mac_addr && 
			 strlen((PSTRING)mac_addr) == 17 &&
			 (strcmp(mac_addr, "00:00:00:00:00:00") != 0))
	{
		INT j;
		PSTRING	macptr;

		macptr = (PSTRING) mac_addr;
		for (j=0; j<MAC_ADDR_LEN; j++)
		{
			AtoH(macptr, &pAd->CurrentAddress[j], 1);
			macptr=macptr+3;
		}	
		
		DBGPRINT(RT_DEBUG_TRACE, ("Use the MAC address what is assigned from Moudle Parameter. \n"));
	}
	else
	{
		COPY_MAC_ADDR(pAd->CurrentAddress, pAd->PermanentAddress);
		DBGPRINT(RT_DEBUG_TRACE, ("Use the MAC address what is assigned from EEPROM. \n"));
	}

	/* Set the current MAC to ASIC */	
	csr2.field.Byte0 = pAd->CurrentAddress[0];
	csr2.field.Byte1 = pAd->CurrentAddress[1];
	csr2.field.Byte2 = pAd->CurrentAddress[2];
	csr2.field.Byte3 = pAd->CurrentAddress[3];
	RTMP_IO_WRITE32(pAd, MAC_ADDR_DW0, csr2.word);
	csr3.word = 0;
	csr3.field.Byte4 = pAd->CurrentAddress[4];
#ifdef P2P_SUPPORT
#ifdef P2P_ODD_MAC_ADJUST
	if ((pAd->CurrentAddress[5] & 0x01) == 0x01)
	{
		csr3.field.Byte5 = pAd->CurrentAddress[5] - 1;
		/* p2p supporting need to use 2 mac addresses. And regarding the p2p odd mac adjust rule.
		** sta's mac should be E2P mac and p2p's mac should be "E2P mac -1" if original mac is odd value.
		** so in order to let MAC chip be able to recv pakcet from 2 those mac address,
		** MAC_ADDR should be original mac - 1.
		**
		** ex. E2P mac is 00:0c:43:00:00:03.
		** in the case, STA MAC will be 00:0c:43:00:03 and p2p MAC will be 00:0c:43:00:00:02
		** then the MAC_ADDR of MAC should be 00:0c:43:00:00:02
		** so need to set 2 MAC support for the case.
		*/
		RTMP_IO_WRITE32(pAd, MAC_BSSID_DW1, (1<<16));
	}
	else
#endif /* P2P_ODD_MAC_ADJUST */
#endif /* P2P_SUPPORT */
	{
		csr3.field.Byte5 = pAd->CurrentAddress[5];
		csr3.field.U2MeMask = 0xff;
	}
	RTMP_IO_WRITE32(pAd, MAC_ADDR_DW1, csr3.word);

#ifdef HDR_TRANS_SUPPORT
	RTMP_IO_WRITE32(pAd, HT_MAC_ADDR_DW0, csr2.word);
	csr3.word &= 0xff00ffff;
	csr3.word |= 0x00410000;				// HW test code
	RTMP_IO_WRITE32(pAd, HT_MAC_ADDR_DW1, csr3.word);
#endif /* HDR_TRANS_SUPPORT */

	DBGPRINT_RAW(RT_DEBUG_TRACE,("Current MAC: =%02x:%02x:%02x:%02x:%02x:%02x\n",
					PRINT_MAC(pAd->CurrentAddress)));

	/* if E2PROM version mismatch with driver's expectation, then skip*/
	/* all subsequent E2RPOM retieval and set a system error bit to notify GUI*/
	RT28xx_EEPROM_READ16(pAd, EEPROM_VERSION_OFFSET, Version.word);
	pAd->EepromVersion = Version.field.Version + Version.field.FaeReleaseNumber * 256;
	DBGPRINT(RT_DEBUG_TRACE, ("E2PROM: Version = %d, FAE release #%d\n", Version.field.Version, Version.field.FaeReleaseNumber));

#ifdef MT7601
	if ( IS_MT7601(pAd) )
	{
		if (Version.field.Version > MT7601_VALID_EEPROM_VERSION)
		{
			DBGPRINT_ERR(("MT7601 E2PROM: WRONG VERSION 0x%x, should be %d\n",Version.field.Version, MT7601_VALID_EEPROM_VERSION));
		}

	}
	else
#endif /* MT7601 */
	if (Version.field.Version > VALID_EEPROM_VERSION)
	{
		DBGPRINT_ERR(("E2PROM: WRONG VERSION 0x%x, should be %d\n",Version.field.Version, VALID_EEPROM_VERSION));
#if 0
		pAd->SystemErrorBitmap |= 0x00000001;

		/* hard-code default value when no proper E2PROM installed*/
		pAd->bAutoTxAgcA = FALSE;
		pAd->bAutoTxAgcG = FALSE;

		/* Default the channel power*/
		for (i = 0; i < MAX_NUM_OF_CHANNELS; i++)
			pAd->TxPower[i].Power = DEFAULT_RF_TX_POWER;

		/* Default the channel power*/
		for (i = 0; i < MAX_NUM_OF_11JCHANNELS; i++)
			pAd->TxPower11J[i].Power = DEFAULT_RF_TX_POWER;

		for(i = 0; i < NUM_EEPROM_BBP_PARMS; i++)
			pAd->EEPROMDefaultValue[i] = 0xffff;
		return;
#endif            
	}

	/* Read BBP default value from EEPROM and store to array(EEPROMDefaultValue) in pAd*/
	RT28xx_EEPROM_READ16(pAd, EEPROM_NIC1_OFFSET, value);
	pAd->EEPROMDefaultValue[EEPROM_NIC_CFG1_OFFSET] = value;

	RT28xx_EEPROM_READ16(pAd, EEPROM_NIC2_OFFSET, value);
	pAd->EEPROMDefaultValue[EEPROM_NIC_CFG2_OFFSET] = value;

	/* if not return early. cause fail at emulation.*/
	/* Init the channel number for TX channel power*/
#ifdef RT3883
	if (IS_RT3883(pAd))
		RTMPRT3883ReadChannelPwr(pAd);
	else
#endif /* RT3883 */
#ifdef RT2883
	if (IS_RT2883(pAd))
		RTMPRT2883ReadChannelPwr(pAd);
	else
#endif /* RT2883 */
#ifdef RT8592
	if (IS_RT8592(pAd))
		RT85592_ReadChannelPwr(pAd);
	else
#endif /* RT8592 */
#ifdef RT65xx
	if (IS_RT6590(pAd))
		RT6590_ReadChannelPwr(pAd);
	else
#endif /* RT65xx */
#ifdef MT7601
	if (IS_MT7601(pAd))
		MT7601_ReadChannelPwr(pAd);
	else
#endif /* MT7601 */
		RTMPReadChannelPwr(pAd);

#ifdef RT3593
	if (IS_RT3593(pAd))
	{
		RT3593_EEPROM_COUNTRY_REGION_READ(pAd);
	}
	else
#endif /* RT3593 */
	{
		RT28xx_EEPROM_READ16(pAd, EEPROM_COUNTRY_REGION, value);	/* Country Region*/
		pAd->EEPROMDefaultValue[EEPROM_COUNTRY_REG_OFFSET] = value;
	}

#if defined(BT_COEXISTENCE_SUPPORT) || defined(RT3290)
	RT28xx_EEPROM_READ16(pAd, EEPROM_NIC3_OFFSET, value);
	pAd->EEPROMDefaultValue[EEPROM_NIC_CFG3_OFFSET] = value;
	pAd->NicConfig3.word = pAd->EEPROMDefaultValue[EEPROM_NIC_CFG3_OFFSET];
#endif /* defined(BT_COEXISTENCE_SUPPORT) || defined(RT3290) */

// TODO: check this after receive TC6008 EEPROM format
#if !defined(RT65xx) && !defined(MT7601) 
	for(i = 0; i < 8; i++)
	{
		RT28xx_EEPROM_READ16(pAd, EEPROM_BBP_BASE_OFFSET + i*2, value);
		pAd->EEPROMDefaultValue[i+EEPROM_BBP_ARRAY_OFFSET] = value;
	}
#endif /* !defined(RT65xx) && !defined(MT7601) */

	/* We have to parse NIC configuration 0 at here.*/
	/* If TSSI did not have preloaded value, it should reset the TxAutoAgc to false*/
	/* Therefore, we have to read TxAutoAgc control beforehand.*/
	/* Read Tx AGC control bit*/
	Antenna.word = pAd->EEPROMDefaultValue[EEPROM_NIC_CFG1_OFFSET];

#ifdef RT65xx
	if (IS_RT8592(pAd)) {
		DBGPRINT(RT_DEBUG_OFF, ("RT85592: Antenna.RfIcType=%d, TxPath=%d, RxPath=%d\n",
					Antenna.field.RfIcType, Antenna.field.TxPath, Antenna.field.RxPath));
		// TODO: fix me!!
		Antenna.word = 0;
		Antenna.field.BoardType = 0;
		Antenna.field.RfIcType = 0xf;
		Antenna.field.TxPath = 2;
		Antenna.field.RxPath = 2;
	}
	else if (IS_RT65XX(pAd)) {
		// TODO: shiang-6590, now we force the ant as 1*1, remove it after EEPROM is ready!
		Antenna.word = 0;
		Antenna.field.BoardType = 0;
		Antenna.field.RfIcType = 0xf;
		Antenna.field.TxPath = 1;
		Antenna.field.RxPath = 1;
	}
#endif /* RT65xx */

	/* must be put here, because RTMP_CHIP_ANTENNA_INFO_DEFAULT_RESET() will clear *
	 * EPROM 0x34~3 */
#ifdef TXRX_SW_ANTDIV_SUPPORT
	/* EEPROM 0x34[15:12] = 0xF is invalid, 0x2~0x3 is TX/RX SW AntDiv */
	if (((Antenna.word & 0xFF00) != 0xFF00) && (Antenna.word & 0x2000))  
	{																	  
		pAd->chipCap.bTxRxSwAntDiv = TRUE;		/* for GPIO switch */
		DBGPRINT(RT_DEBUG_OFF, ("\x1b[mAntenna word %X/%d, AntDiv %d\x1b[m\n", 
					Antenna.word, Antenna.field.BoardType, pAd->NicConfig2.field.AntDiversity));
	}
#endif /* TXRX_SW_ANTDIV_SUPPORT */

#ifdef RT3593
	if (IS_RT3593(pAd))
	{
		RT3593_CONFIG_SET_BY_ANTENNA(pAd);
	}
#endif /* RT3593 */

	// TODO: shiang, why we only check oxff00??
	if ((Antenna.word & 0xFF00) == 0xFF00)
/*	if (Antenna.word == 0xFFFF)*/
		RTMP_CHIP_ANTENNA_INFO_DEFAULT_RESET(pAd, &Antenna);

	/* Choose the desired Tx&Rx stream.*/
	if ((pAd->CommonCfg.TxStream == 0) || (pAd->CommonCfg.TxStream > Antenna.field.TxPath))
		pAd->CommonCfg.TxStream = Antenna.field.TxPath;

	if ((pAd->CommonCfg.RxStream == 0) || (pAd->CommonCfg.RxStream > Antenna.field.RxPath))
	{
		pAd->CommonCfg.RxStream = Antenna.field.RxPath;

		if ((pAd->MACVersion != RALINK_3883_VERSION) &&
			(pAd->MACVersion != RALINK_2883_VERSION) &&
#ifdef RT3593
			(!RT3593_MAC_VERSION_CHECK(pAd->MACVersion)) &&
#endif /* RT3593 */
			(pAd->CommonCfg.RxStream > 2))
		{
			/* only 2 Rx streams for RT2860 series*/
			pAd->CommonCfg.RxStream = 2;
		}
	}

	/* EEPROM offset 0x36 - NIC Configuration 1 */
	NicConfig2.word = pAd->EEPROMDefaultValue[EEPROM_NIC_CFG2_OFFSET];

#ifdef WSC_INCLUDED
	/* WSC hardware push button function 0811 */
	//if ((pAd->MACVersion == 0x28600100) || (pAd->MACVersion == 0x28700100))
		WSC_HDR_BTN_MR_HDR_SUPPORT_SET(pAd, NicConfig2.field.EnableWPSPBC);
#endif /* WSC_INCLUDED */

#ifdef CONFIG_AP_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_AP(pAd)
	{
		if (NicConfig2.word == 0xffff)
			NicConfig2.word = 0;
	}
#endif /* CONFIG_AP_SUPPORT */	

#ifdef CONFIG_STA_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	{
		if ((NicConfig2.word & 0x00ff) == 0xff)
			NicConfig2.word &= 0xff00;

		if ((NicConfig2.word >> 8) == 0xff)
			NicConfig2.word &= 0x00ff;
	}
#endif /* CONFIG_STA_SUPPORT */

	if (NicConfig2.field.DynamicTxAgcControl == 1)
		pAd->bAutoTxAgcA = pAd->bAutoTxAgcG = TRUE;
	else
		pAd->bAutoTxAgcA = pAd->bAutoTxAgcG = FALSE;
	
	
	/* Save value for future using */
	pAd->NicConfig2.word = NicConfig2.word;
	
	DBGPRINT_RAW(RT_DEBUG_TRACE, ("NICReadEEPROMParameters: RxPath = %d, TxPath = %d\n", Antenna.field.RxPath, Antenna.field.TxPath));

	/* Save the antenna for future use*/
	pAd->Antenna.word = Antenna.word;

	/* Set the RfICType here, then we can initialize RFIC related operation callbacks*/
	pAd->Mlme.RealRxPath = (UCHAR) Antenna.field.RxPath;

	pAd->RfIcType = (UCHAR) Antenna.field.RfIcType;

#ifdef RT65xx
	// TODO: shiang-6590, currently we don't have eeprom value, so directly force to set it as 0xff
	if (IS_RT8592(pAd)) {
		pAd->Mlme.RealRxPath = 2;
		pAd->RfIcType = RFIC_UNKNOWN;
	}
	else	 if (IS_RT65XX(pAd)) {
		pAd->Mlme.RealRxPath = 1;
		pAd->RfIcType = RFIC_UNKNOWN;
	}
#endif /* RT65xx */

	/* check if the chip supports 5G band */
	if (WMODE_CAP_5G(pAd->CommonCfg.PhyMode))
	{
		if (!RFIC_IS_5G_BAND(pAd))
		{
			DBGPRINT_RAW(RT_DEBUG_ERROR,
						("%s():Err! chip not support 5G band %d!\n",
						__FUNCTION__, pAd->RfIcType));
#ifdef DOT11_N_SUPPORT
			/* change to bgn mode */
			Set_WirelessMode_Proc(pAd, "9");
#else
			/* change to bg mode */
			Set_WirelessMode_Proc(pAd, "0");
#endif /* DOT11_N_SUPPORT */
			pAd->RFICType = RFIC_24GHZ;
		}
		pAd->RFICType = RFIC_24GHZ | RFIC_5GHZ;
	}
	else
		pAd->RFICType = RFIC_24GHZ;

	RTMP_NET_DEV_NICKNAME_INIT(pAd);

#ifdef RT65xx
	if (IS_RT6590(pAd))
	{
		; // TODO: wait TC6008 EEPROM format
	}
	else
#endif /* RT65xx */
#ifdef MT7601
	if (IS_MT7601(pAd))
	{
		; // move to MT7601_InitDesiredTSSITable
	}
	else
#endif /* MT7601 */
	/* Read TSSI reference and TSSI boundary for temperature compensation. This is ugly*/
	/* 0. 11b/g*/
	{
		/* these are tempature reference value (0x00 ~ 0xFE)
		   ex: 0x00 0x15 0x25 0x45 0x88 0xA0 0xB5 0xD0 0xF0
		   TssiPlusBoundaryG [4] [3] [2] [1] [0] (smaller) +
		   TssiMinusBoundaryG[0] [1] [2] [3] [4] (larger) */
#ifdef RT3593
		if (IS_RT3593(pAd))
		{
			RT3593_EEPROM_TSSI_24G_READ(pAd);
		}
		else
#endif /* RT3593 */
		{
			RT28xx_EEPROM_READ16(pAd, EEPROM_G_TSSI_BOUND1, Power.word);
			pAd->TssiMinusBoundaryG[4] = Power.field.Byte0;
			pAd->TssiMinusBoundaryG[3] = Power.field.Byte1;
			RT28xx_EEPROM_READ16(pAd, EEPROM_G_TSSI_BOUND2, Power.word);
			pAd->TssiMinusBoundaryG[2] = Power.field.Byte0;
			pAd->TssiMinusBoundaryG[1] = Power.field.Byte1;
			RT28xx_EEPROM_READ16(pAd, EEPROM_G_TSSI_BOUND3, Power.word);
			pAd->TssiRefG   = Power.field.Byte0; /* reference value [0] */
			pAd->TssiPlusBoundaryG[1] = Power.field.Byte1;
			RT28xx_EEPROM_READ16(pAd, EEPROM_G_TSSI_BOUND4, Power.word);
			pAd->TssiPlusBoundaryG[2] = Power.field.Byte0;
			pAd->TssiPlusBoundaryG[3] = Power.field.Byte1;
			RT28xx_EEPROM_READ16(pAd, EEPROM_G_TSSI_BOUND5, Power.word);
			pAd->TssiPlusBoundaryG[4] = Power.field.Byte0;
			pAd->TxAgcStepG = Power.field.Byte1;    
			pAd->TxAgcCompensateG = 0;
			pAd->TssiMinusBoundaryG[0] = pAd->TssiRefG;
			pAd->TssiPlusBoundaryG[0]  = pAd->TssiRefG;

			/* Disable TxAgc if the based value is not right*/
			if (pAd->TssiRefG == 0xff)
				pAd->bAutoTxAgcG = FALSE;
		}

		DBGPRINT(RT_DEBUG_TRACE,("E2PROM: G Tssi[-4 .. +4] = %d %d %d %d - %d -%d %d %d %d, step=%d, tuning=%d\n",
			pAd->TssiMinusBoundaryG[4], pAd->TssiMinusBoundaryG[3], pAd->TssiMinusBoundaryG[2], pAd->TssiMinusBoundaryG[1],
			pAd->TssiRefG,
			pAd->TssiPlusBoundaryG[1], pAd->TssiPlusBoundaryG[2], pAd->TssiPlusBoundaryG[3], pAd->TssiPlusBoundaryG[4],
			pAd->TxAgcStepG, pAd->bAutoTxAgcG));
	}	

#ifdef RT65xx
	if (IS_RT6590(pAd))
	{
		; // TODO: wait TC6008 EEPROM format
	}
	else
#endif /* RT65xx */
#ifdef MT7601
	if (IS_MT7601(pAd))
	{
		; // MT7601 not support A Band
	}
	else
#endif /* MT7601 */
	/* 1. 11a*/
	{
#ifdef RT3593
		if (IS_RT3593(pAd))
		{
			RT3593_EEPROM_TSSI_5G_READ(pAd);
		}
		else
#endif /* RT3593 */
		{
			RT28xx_EEPROM_READ16(pAd, EEPROM_A_TSSI_BOUND1, Power.word);
			pAd->TssiMinusBoundaryA[4] = Power.field.Byte0;
			pAd->TssiMinusBoundaryA[3] = Power.field.Byte1;
			RT28xx_EEPROM_READ16(pAd, EEPROM_A_TSSI_BOUND2, Power.word);
			pAd->TssiMinusBoundaryA[2] = Power.field.Byte0;
			pAd->TssiMinusBoundaryA[1] = Power.field.Byte1;
			RT28xx_EEPROM_READ16(pAd, EEPROM_A_TSSI_BOUND3, Power.word);
			pAd->TssiRefA = Power.field.Byte0;
			pAd->TssiPlusBoundaryA[1] = Power.field.Byte1;
			RT28xx_EEPROM_READ16(pAd, EEPROM_A_TSSI_BOUND4, Power.word);
			pAd->TssiPlusBoundaryA[2] = Power.field.Byte0;
			pAd->TssiPlusBoundaryA[3] = Power.field.Byte1;
			RT28xx_EEPROM_READ16(pAd, EEPROM_A_TSSI_BOUND5, Power.word);
			pAd->TssiPlusBoundaryA[4] = Power.field.Byte0;
			pAd->TxAgcStepA = Power.field.Byte1;    
			pAd->TxAgcCompensateA = 0;
			pAd->TssiMinusBoundaryA[0] = pAd->TssiRefA;
			pAd->TssiPlusBoundaryA[0]  = pAd->TssiRefA;

			/* Disable TxAgc if the based value is not right*/
			if (pAd->TssiRefA == 0xff)
				pAd->bAutoTxAgcA = FALSE;
		}

		DBGPRINT(RT_DEBUG_TRACE,("E2PROM: A Tssi[-4 .. +4] = %d %d %d %d - %d -%d %d %d %d, step=%d, tuning=%d\n",
			pAd->TssiMinusBoundaryA[4], pAd->TssiMinusBoundaryA[3], pAd->TssiMinusBoundaryA[2], pAd->TssiMinusBoundaryA[1],
			pAd->TssiRefA,
			pAd->TssiPlusBoundaryA[1], pAd->TssiPlusBoundaryA[2], pAd->TssiPlusBoundaryA[3], pAd->TssiPlusBoundaryA[4],
			pAd->TxAgcStepA, pAd->bAutoTxAgcA));
	}	
	pAd->BbpRssiToDbmDelta = 0x0;
	
	/* Read frequency offset setting for RF*/
#ifdef RT3593
	if (IS_RT3593(pAd))
		RT28xx_EEPROM_READ16(pAd, EEPROM_EXT_FREQUENCY_OFFSET, value);
	else
#endif /* RT3593 */
		RT28xx_EEPROM_READ16(pAd, EEPROM_FREQ_OFFSET, value);

	if ((value & 0x00FF) != 0x00FF)
		pAd->RfFreqOffset = (ULONG) (value & 0x00FF);
	else
		pAd->RfFreqOffset = 0;
	
#ifdef MT7601
	if ( IS_MT7601(pAd) )
	{
		RT28xx_EEPROM_READ16(pAd, EEPROM_FREQ_OFFSET_COMPERSATION, value);
		value = (value >> 8) & 0xFF;
		if ( value != 0xFF )
		{
			if ( value & 0x80 )
				pAd->RfFreqOffset -= (value & 0x7F);
			else
				pAd->RfFreqOffset += value;
		}
		
	}
#endif /* MT7601 */
	
#ifdef RTMP_RBUS_SUPPORT
	if (pAd->infType == RTMP_DEV_INF_RBUS)
	{
		if (pAd->RfFreqDelta & 0x10)
		{
			pAd->RfFreqOffset = (pAd->RfFreqOffset >= pAd->RfFreqDelta)? (pAd->RfFreqOffset - (pAd->RfFreqDelta & 0xf)) : 0;
		}
		else
		{
			pAd->RfFreqOffset = ((pAd->RfFreqOffset + pAd->RfFreqDelta) < 0x40)? (pAd->RfFreqOffset + (pAd->RfFreqDelta & 0xf)) : 0x3f;
		}
	}
#endif /* RTMP_RBUS_SUPPORT */

	DBGPRINT(RT_DEBUG_TRACE, ("E2PROM: RF FreqOffset=0x%lx \n", pAd->RfFreqOffset));

#if 0
	// 40M BW in 2.4GHz band (37h)
	if ( pAd->NicConfig2.field.BW40MAvailForG )
	{
		pAd->CommonCfg.RegTransmitSetting.field.BW  = BW_20;
		DBGPRINT(RT_DEBUG_TRACE, ("E2PROM: BW_20\n"));
	}
#endif
	/*CountryRegion byte offset (38h)*/
#ifdef RT3883
	if (IS_RT3883(pAd))
	{
		value = pAd->EEPROMDefaultValue[EEPROM_COUNTRY_REG_OFFSET] & 0x00FF;		// 2.4G band
		value2 = pAd->EEPROMDefaultValue[EEPROM_COUNTRY_REG_OFFSET] >> 8;	// 5G band
	}
	else
#endif // RT3883 //
	{
		value = pAd->EEPROMDefaultValue[EEPROM_COUNTRY_REG_OFFSET] >> 8;		/* 2.4G band*/
		value2 = pAd->EEPROMDefaultValue[EEPROM_COUNTRY_REG_OFFSET] & 0x00FF;	/* 5G band*/
	}
	
	if ((value <= REGION_MAXIMUM_BG_BAND) || (value == REGION_32_BG_BAND) || (value == REGION_33_BG_BAND))
	{
		pAd->CommonCfg.CountryRegion = ((UCHAR) value) | 0x80;
#ifdef P2P_SUPPORT
#ifdef P2P_CHANNEL_LIST_SEPARATE
		pAd->P2pCfg.CountryRegion = pAd->CommonCfg.CountryRegion;
		DBGPRINT(RT_DEBUG_ERROR, ("%s::(CountryRegion=%d)\n", __FUNCTION__, pAd->P2pCfg.CountryRegion));
#endif /* P2P_CHANNEL_LIST_SEPARATE */
#endif /* P2P_SUPPORT */
	}

	if (value2 <= REGION_MAXIMUM_A_BAND)
	{
		pAd->CommonCfg.CountryRegionForABand = ((UCHAR) value2) | 0x80;
#ifdef P2P_SUPPORT
#ifdef P2P_CHANNEL_LIST_SEPARATE
		pAd->P2pCfg.CountryRegionForABand = pAd->CommonCfg.CountryRegionForABand;
DBGPRINT(RT_DEBUG_ERROR, ("%s::(CountryRegionForABand=%d)\n", __FUNCTION__, pAd->P2pCfg.CountryRegionForABand));
#endif /* P2P_CHANNEL_LIST_SEPARATE */
#endif /* P2P_SUPPORT */
	}
	
	/* Get RSSI Offset on EEPROM 0x9Ah & 0x9Ch.*/
	/* The valid value are (-10 ~ 10) */
	/* */
#ifdef RT3593
	if (IS_RT3593(pAd))
	{
		RT3593_EEPROM_RSSI01_OFFSET_24G_READ(pAd);
	}
	else
#endif /* RT3593 */
#if 0 //def RT65xx
	if (IS_RT6590(pAd))
	{
		; // TODO: wait TC6008 EEPROM format
	}
	else
#endif /* RT65xx */
	{
		RT28xx_EEPROM_READ16(pAd, EEPROM_RSSI_BG_OFFSET, value);
		pAd->BGRssiOffset[0] = value & 0x00ff;
		pAd->BGRssiOffset[1] = (value >> 8);
	}

#ifdef RT3593
	if (IS_RT3593(pAd))
	{
		RT3593_EEPROM_RSSI2_OFFSET_ALNAGAIN1_24G_READ(pAd);
	}
	else
#endif /* RT3593 */
#if 0 //def RT65xx
	if (IS_RT6590(pAd))
	{
		; // TODO: wait TC6008 EEPROM format
	}
	else
#endif /* RT65xx */
#ifdef MT7601
	if (IS_MT7601(pAd))
	{
		; // MT7601 not support BGRssiOffset[2]
	}
	else
#endif /* MT7601 */
	{
		RT28xx_EEPROM_READ16(pAd, EEPROM_RSSI_BG_OFFSET+2, value);
/*		if (IS_RT2860(pAd))  RT2860 supports 3 Rx and the 2.4 GHz RSSI #2 offset is in the EEPROM 0x48*/
			pAd->BGRssiOffset[2] = value & 0x00ff;
		pAd->ALNAGain1 = (value >> 8);
	}

#ifdef RT3593
	if (IS_RT3593(pAd))
	{
		RT3593_EEPROM_BLNA_ALNA_GAIN0_24G_READ(pAd);
	}
	else
#endif /* RT3593 */
#ifdef RT65xx
	if (IS_RT6590(pAd))
	{
		/*
			MT7650 E1 doesn't support external LNA.
			2012/04/12
		*/
		; // TODO: wait TC6008 EEPROM format
	}
	else
#endif /* RT65xx */
	{
		RT28xx_EEPROM_READ16(pAd, EEPROM_LNA_OFFSET, value);
		pAd->BLNAGain = value & 0x00ff;
		pAd->ALNAGain0 = (value >> 8);
	}
	
#ifdef RT3090
#ifdef RELEASE_EXCLUDE
/* Because only RT3090A has internal LNA,*/
/*and its default value of  RT3090A's internal LNA gain is 0x0A*/
#endif /* RELEASE_EXCLUDE */
	/* RT3090A's internal LNA gain is 0x0A RT3090A's internal LNA gain is 0x0A*/
	if (IS_RT3090A(pAd))
	{
		pAd->BLNAGain = RT3090A_DEFAULT_INTERNAL_LNA_GAIN;
	}
#endif /* RT3090 */

#ifdef RT3593
	if (IS_RT3593(pAd))
	{
		RT3593_EEPROM_RSSI01_OFFSET_5G_READ(pAd);
	}
	else
#endif /* RT3593 */
#if 0 //def RT65xx
	if (IS_RT6590(pAd))
	{
		; // TODO: wait TC6008 EEPROM format
	}
	else
#endif /* RT65xx */
#ifdef MT7601
	if (IS_MT7601(pAd))
	{
		;	// MT7601 not support A Band
	}
	else
#endif /* MT7601 */
	{
		RT28xx_EEPROM_READ16(pAd, EEPROM_RSSI_A_OFFSET, value);
		pAd->ARssiOffset[0] = value & 0x00ff;
		pAd->ARssiOffset[1] = (value >> 8);
	}

#ifdef RT3593
	if (IS_RT3593(pAd))
	{
		RT3593_EEPROM_RSSI2_OFFSET_ALNAGAIN2_5G_READ(pAd);
	}
	else
#endif /* RT3593 */
#if 0 //def RT65xx
	if (IS_RT6590(pAd))
	{
		; // TODO: wait TC6008 EEPROM format
	}
	else
#endif /* RT65xx */
#ifdef MT7601
	if (IS_MT7601(pAd))
	{
		;	// MT7601 not support A Band
	}
	else
#endif /* MT7601 */
	{
		RT28xx_EEPROM_READ16(pAd, (EEPROM_RSSI_A_OFFSET+2), value);
		pAd->ARssiOffset[2] = value & 0x00ff;
		pAd->ALNAGain2 = (value >> 8);
	}

#if defined(RT2883) || defined(RT3883)
	if (IS_RT2883(pAd) || IS_RT3883(pAd))
	{
		RT28xx_EEPROM_READ16(pAd, EEPROM_LNA_OFFSET2, value);
		pAd->ALNAGain1 = value & 0x00ff;
		pAd->ALNAGain2 = (value >> 8);
	}
#endif /* defined(RT2883) || defined(RT3883) */

	if (((UCHAR)pAd->ALNAGain1 == 0xFF) || (pAd->ALNAGain1 == 0x00))
		pAd->ALNAGain1 = pAd->ALNAGain0;
	if (((UCHAR)pAd->ALNAGain2 == 0xFF) || (pAd->ALNAGain2 == 0x00))
		pAd->ALNAGain2 = pAd->ALNAGain0;

	/* Validate 11a/b/g RSSI 0/1/2 offset.*/
	for (i =0 ; i < 3; i++)
	{
		if ((pAd->BGRssiOffset[i] < -10) || (pAd->BGRssiOffset[i] > 10))
			pAd->BGRssiOffset[i] = 0;

		if ((pAd->ARssiOffset[i] < -10) || (pAd->ARssiOffset[i] > 10))
			pAd->ARssiOffset[i] = 0;
	}

#ifdef RT30xx
	
	/* Get TX mixer gain setting*/
	/* 0xff are invalid value*/
	/* Note: RT30xX default value is 0x00 and will program to RF_R17 only when this value is not zero.*/
	/*       RT359X default value is 0x02*/
	
	if (IS_RT30xx(pAd) || IS_RT3572(pAd)  || IS_RT3593(pAd)  
		|| IS_RT5390(pAd) || IS_RT5392(pAd) || IS_RT5592(pAd)
		|| IS_RT3290(pAd) || IS_RT65XX(pAd) || IS_MT7601(pAd))
	{
		RT28xx_EEPROM_READ16(pAd, EEPROM_TXMIXER_GAIN_2_4G, value);
		pAd->TxMixerGain24G = 0;
		value &= 0x00ff;
		if (value != 0xff)
		{
			value &= 0x07;
			pAd->TxMixerGain24G = (UCHAR)value;
		}

#ifdef RT3593
		if (IS_RT3593(pAd))
		{
			pAd->TxMixerGain24G = 0;
			pAd->TxMixerGain5G = 0;
		}
#endif /* RT3593 */
	}
#endif /* RT30xx */
#ifdef RT35xx
	/* EEPROM setting of TxMixer for 3572*/
	if (IS_RT3572(pAd))
	{
		RT28xx_EEPROM_READ16(pAd, EEPROM_TXMIXER_GAIN_5G, value);
		pAd->TxMixerGain5G = 0;
		value &= 0x00ff;
		if (value != 0xff)
		{
			value &= 0x07;
			pAd->TxMixerGain5G = (UCHAR)value;
		}
	}
#endif /* RT35xx */
	
#ifdef LED_CONTROL_SUPPORT
	/* LED Setting */
	RTMPGetLEDSetting(pAd);
#endif /* LED_CONTROL_SUPPORT */
		
		RTMPReadTxPwrPerRate(pAd);

#ifdef SINGLE_SKU
#ifdef RT3593
	if (IS_RT3593(pAd))
	{
		RT28xx_EEPROM_READ16(pAd, EEPROM_EXT_MAX_TX_POWER_OVER_2DOT4G_AND_5G, pAd->CommonCfg.DefineMaxTxPwr);
	}
	else
#endif /* RT3593 */
	{
		RT28xx_EEPROM_READ16(pAd, EEPROM_DEFINE_MAX_TXPWR, pAd->CommonCfg.DefineMaxTxPwr);
	}

	/*
		Some dongle has old EEPROM value, use ModuleTxpower for saving correct value fo DefineMaxTxPwr.
		ModuleTxpower will override DefineMaxTxPwr (value from EEPROM) if ModuleTxpower is not zero.
	*/
	if (pAd->CommonCfg.ModuleTxpower > 0) 
		pAd->CommonCfg.DefineMaxTxPwr = pAd->CommonCfg.ModuleTxpower;

	DBGPRINT(RT_DEBUG_TRACE, ("TX Power set for SINGLE SKU MODE is : 0x%04x \n", pAd->CommonCfg.DefineMaxTxPwr));
	
	pAd->CommonCfg.bSKUMode = FALSE;
	if ((pAd->CommonCfg.DefineMaxTxPwr & 0xFF) <= 0x50)
	{
		if (IS_RT3883(pAd))
			pAd->CommonCfg.bSKUMode = TRUE;
		else if ((pAd->CommonCfg.AntGain > 0) && (pAd->CommonCfg.BandedgeDelta >= 0))
			pAd->CommonCfg.bSKUMode = TRUE;
	}
	DBGPRINT(RT_DEBUG_TRACE, ("Single SKU Mode is %s\n", 
				pAd->CommonCfg.bSKUMode ? "Enable" : "Disable"));
#endif /* SINGLE_SKU */

#ifdef SINGLE_SKU_V2
	InitSkuRateDiffTable(pAd);
#endif /* SINGLE_SKU_V2 */

#ifdef RT30xx
#ifdef RTMP_EFUSE_SUPPORT
	RtmpEfuseSupportCheck(pAd);
#endif /* RTMP_EFUSE_SUPPORT */
#endif /* RT30xx */

#ifdef RTMP_INTERNAL_TX_ALC
#ifdef RT65xx
	if (IS_RT6590(pAd))
	{
		; // TODO: wait TC6008 EEPROM format
	}
	else
#endif /* RT65xx */
	{
		/*
			Internal Tx ALC support is starting from RT3370 / RT3390, which combine PA / LNA in single chip.
			The old chipset don't have this, add new feature flag RTMP_INTERNAL_TX_ALC.
		*/
		RT28xx_EEPROM_READ16(pAd, EEPROM_NIC2_OFFSET, value);
		if (value == 0xFFFF) /*EEPROM is empty*/
		   	pAd->TxPowerCtrl.bInternalTxALC = FALSE;
		else if (value & 1<<13) 
		   	pAd->TxPowerCtrl.bInternalTxALC = TRUE;
		else 
		   	pAd->TxPowerCtrl.bInternalTxALC = FALSE;

	}
	DBGPRINT(RT_DEBUG_TRACE, ("TXALC> bInternalTxALC = %d\n", pAd->TxPowerCtrl.bInternalTxALC));
#endif /* RTMP_INTERNAL_TX_ALC */


#ifdef IQ_CAL_SUPPORT
#ifdef RT8592
	if (IS_RT65XX(pAd))
		ReadIQCompensationConfiguraiton(pAd);
	else
#endif /* RT8592 */
		GetIQCalibration(pAd);
#endif /* IQ_CAL_SUPPORT */

#ifdef RT3290
	if (IS_RT3290(pAd))
		RT3290_eeprom_access_grant(pAd, FALSE);
#endif /* RT3290 */

	DBGPRINT(RT_DEBUG_TRACE, ("%s: pAd->Antenna.field.BoardType = %d, IS_MINI_CARD(pAd) = %d, IS_RT5390U(pAd) = %d\n", 
		__FUNCTION__,
		pAd->Antenna.field.BoardType,
		IS_MINI_CARD(pAd),
		IS_RT5390U(pAd)));

	DBGPRINT(RT_DEBUG_TRACE, ("<-- NICReadEEPROMParameters\n"));
}


/*
	========================================================================
	
	Routine Description:
		Set default value from EEPROM
		
	Arguments:
		Adapter						Pointer to our adapter

	Return Value:
		None

	IRQL = PASSIVE_LEVEL
	
	Note:
		
	========================================================================
*/
VOID	NICInitAsicFromEEPROM(
	IN	PRTMP_ADAPTER	pAd)
{
#ifdef CONFIG_STA_SUPPORT
	UINT32 data = 0;
#endif /* CONFIG_STA_SUPPORT */
	USHORT i;
#ifdef RALINK_ATE
	USHORT value;
#endif /* RALINK_ATE */
	EEPROM_NIC_CONFIG2_STRUC NicConfig2;
#ifdef RT30xx
	UCHAR bbpreg = 0;
#endif /* RT30xx */
	
	DBGPRINT(RT_DEBUG_TRACE, ("--> NICInitAsicFromEEPROM\n"));

#if !defined(RT65xx) && !defined(MT7601)
	for(i = EEPROM_BBP_ARRAY_OFFSET; i < NUM_EEPROM_BBP_PARMS; i++)
	{
		UCHAR BbpRegIdx, BbpValue;
	
		if ((pAd->EEPROMDefaultValue[i] != 0xFFFF) && (pAd->EEPROMDefaultValue[i] != 0))
		{
			BbpRegIdx = (UCHAR)(pAd->EEPROMDefaultValue[i] >> 8);
			BbpValue  = (UCHAR)(pAd->EEPROMDefaultValue[i] & 0xff);
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BbpRegIdx, BbpValue);
		}
	}
#endif /* #if !defined(RT65xx) && !defined(MT7601) */

	NicConfig2.word = pAd->NicConfig2.word;

	/* finally set primary ant */
	AntCfgInit(pAd);

	RTMP_CHIP_ASIC_INIT_TEMPERATURE_COMPENSATION(pAd);

	if (pAd->chipOps.AsicRfInit)
		pAd->chipOps.AsicRfInit(pAd);

#ifdef ANT_DIVERSITY_SUPPORT
	if ((pAd->CommonCfg.bHWRxAntDiversity) && (pAd->CommonCfg.RxAntDiversityCfg == ANT_HW_DIVERSITY_ENABLE) &&
			(pAd->chipOps.HwAntEnable))
		pAd->chipOps.HwAntEnable(pAd);
#endif

#ifdef CONFIG_STA_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	{
#ifdef RTMP_MAC_PCI
		/* Read Hardware controlled Radio state enable bit*/
		if (NicConfig2.field.HardwareRadioControl == 1)
		{
			BOOLEAN radioOff = FALSE;
			pAd->StaCfg.bHardwareRadio = TRUE;

#ifdef RT3290
			if (IS_RT3290(pAd))
			{
				// Read GPIO pin0 as Hardware controlled radio state
				RTMP_IO_FORCE_READ32(pAd, WLAN_FUN_CTRL, &data);
				if ((data & 0x100) == 0)
					radioOff = TRUE;
			}
			else
#endif /* RT3290 */
			{
				/* Read GPIO pin2 as Hardware controlled radio state*/
				RTMP_IO_READ32(pAd, GPIO_CTRL_CFG, &data);
				if ((data & 0x04) == 0)
					radioOff = TRUE;
			}

			if (radioOff)
			{
				pAd->StaCfg.bHwRadio = FALSE;
				pAd->StaCfg.bRadio = FALSE;
/*				RTMP_IO_WRITE32(pAd, PWR_PIN_CFG, 0x00001818);*/
				RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_RADIO_OFF);
			}
		}
		else
#endif /* RTMP_MAC_PCI */		
			pAd->StaCfg.bHardwareRadio = FALSE;

#ifdef LED_CONTROL_SUPPORT
		if (pAd->StaCfg.bRadio == FALSE)
		{
			RTMPSetLED(pAd, LED_RADIO_OFF);
		}
		else
		{
			RTMPSetLED(pAd, LED_RADIO_ON);
		}
#endif /* LED_CONTROL_SUPPORT */

#ifdef RTMP_MAC_PCI
		if (pAd->StaCfg.bRadio == TRUE)
		{
			AsicSendCommandToMcu(pAd, 0x30, PowerRadioOffCID, 0xff, 0x02, FALSE);
			AsicCheckCommanOk(pAd, PowerRadioOffCID);

			/*AsicSendCommandToMcu(pAd, 0x30, 0xff, 0xff, 0x02, FALSE);*/
			AsicSendCommandToMcu(pAd, 0x31, PowerWakeCID, 0x00, 0x00, FALSE);
			/* 2-1. wait command ok.*/
			AsicCheckCommanOk(pAd, PowerWakeCID);
		}
#endif /* RTMP_MAC_PCI */		
	}
#ifdef PCIE_PS_SUPPORT
#if defined(RT3090) || defined(RT3592) || defined(RT3390) || defined(RT3593) || defined(RT5390) || defined(RT5392) || defined(RT5592) || defined(RT3290)
		if (IS_RT3090(pAd)|| IS_RT3572(pAd) || IS_RT3390(pAd) 
			|| IS_RT3593(pAd) || IS_RT5390(pAd) || IS_RT5392(pAd)
			|| IS_RT5592(pAd) || IS_RT3290(pAd))
		{
			RTMP_CHIP_OP *pChipOps = &pAd->chipOps;
			if (pChipOps->AsicReverseRfFromSleepMode)
				pChipOps->AsicReverseRfFromSleepMode(pAd, TRUE);
		}
		/* 3090 MCU Wakeup command needs more time to be stable. */
		/* Before stable, don't issue other MCU command to prevent from firmware error.*/
		if ((((IS_RT3090(pAd)|| IS_RT3572(pAd) ||IS_RT3390(pAd) 
			|| IS_RT3593(pAd) || IS_RT5390(pAd) || IS_RT5392(pAd)) 
			  && IS_VERSION_AFTER_F(pAd)) || IS_RT5592(pAd) || IS_RT3290(pAd))
			&& (pAd->StaCfg.PSControl.field.rt30xxPowerMode == 3) 
			&& (pAd->StaCfg.PSControl.field.EnableNewPS == TRUE))
		{
			DBGPRINT(RT_DEBUG_TRACE,("%s::%d,release Mcu Lock\n",__FUNCTION__,__LINE__));
			RTMP_SEM_LOCK(&pAd->McuCmdLock);
			pAd->brt30xxBanMcuCmd = FALSE;
			RTMP_SEM_UNLOCK(&pAd->McuCmdLock);
		}
#endif /* defined(RT3090) || defined(RT3592) || defined(RT3390) || defined(RT3593) || defined(RT5390) || defined(RT5392) */
#endif /* PCIE_PS_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */
#ifdef RTMP_MAC_USB
		if (IS_RT30xx(pAd)|| IS_RT3572(pAd))
		{
			RTMP_CHIP_OP *pChipOps = &pAd->chipOps;
			if (pChipOps->AsicReverseRfFromSleepMode)
				pChipOps->AsicReverseRfFromSleepMode(pAd, TRUE);
		}
#endif /* RTMP_MAC_USB */
	/* Turn off patching for cardbus controller*/
	if (NicConfig2.field.CardbusAcceleration == 1)
	{
/*		pAd->bTest1 = TRUE;*/
	}

	if (NicConfig2.field.DynamicTxAgcControl == 1)
		pAd->bAutoTxAgcA = pAd->bAutoTxAgcG = TRUE;
	else
		pAd->bAutoTxAgcA = pAd->bAutoTxAgcG = FALSE;

#ifdef RTMP_INTERNAL_TX_ALC
	/*
	    Internal Tx ALC support is starting from RT3370 / RT3390, which combine PA / LNA in single chip.
	    The old chipset don't have this, add new feature flag RTMP_INTERNAL_TX_ALC.
	 */

	/* Internal Tx ALC */
	if (((NicConfig2.field.DynamicTxAgcControl == 1) && 
            (NicConfig2.field.bInternalTxALC == 1)) ||
            ((!IS_RT3390(pAd)) && (!IS_RT3350(pAd)) &&
            (!IS_RT3352(pAd)) && (!IS_RT5350(pAd)) && (!IS_RT5390(pAd)) && (!IS_RT3290(pAd)) && (!IS_MT7601(pAd))))
	{
		/*
			If both DynamicTxAgcControl and bInternalTxALC are enabled,
			it is a wrong configuration.
			If the chipset does not support Internal TX ALC, we shall disable it.
		*/
			pAd->TxPowerCtrl.bInternalTxALC = FALSE;
	}
	else
	{
		if (NicConfig2.field.bInternalTxALC == 1)
		{
			pAd->TxPowerCtrl.bInternalTxALC = TRUE;
		}
		else
		{
			pAd->TxPowerCtrl.bInternalTxALC = FALSE;
		}
	}

	
	/* Old 5390 NIC always disables the internal ALC */
	
	if (pAd->MACVersion == 0x53900501)
	{
		pAd->TxPowerCtrl.bInternalTxALC = FALSE;
	}

	DBGPRINT(RT_DEBUG_TRACE, ("%s: pAd->TxPowerCtrl.bInternalTxALC = %d\n", 
		__FUNCTION__, 
		pAd->TxPowerCtrl.bInternalTxALC));
#endif /* RTMP_INTERNAL_TX_ALC */

#ifdef RALINK_ATE
	RT28xx_EEPROM_READ16(pAd, EEPROM_TSSI_GAIN_AND_ATTENUATION, value);
	value = (value & 0x00FF);	
	
	if (IS_RT5390(pAd))
	{
		pAd->TssiGain = 0x02;	 /* RT5390 uses 2 as TSSI gain/attenuation default value */
	}
	else
	{
		pAd->TssiGain = 0x03; /* RT5392 uses 3 as TSSI gain/attenuation default value */
	}	
	
	if ((value != 0x00) && (value != 0xFF))
	{
		pAd->TssiGain =  (UCHAR) (value & 0x000F);
	}
	
	DBGPRINT(RT_DEBUG_TRACE, ("%s: EEPROM_TSSI_GAIN_AND_ATTENUATION = 0x%X, pAd->TssiGain=0x%x\n", 
				__FUNCTION__, 
				value, 
				pAd->TssiGain));
#endif // RALINK_ATE //

	rtmp_bbp_set_rxpath(pAd, pAd->Antenna.field.RxPath);
	
#ifdef CONFIG_STA_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	{
		/* Handle the difference when 1T*/
#ifdef RT3883
		if (IS_RT3883(pAd))
			rtmp_bbp_set_txdac(pAd, pAd->Antenna.field.TxPath-1);
		else
#endif /* RT3883 */
#ifdef RT3593
		if (IS_RT3593(pAd))
			rtmp_bbp_set_txdac(pAd, pAd->Antenna.field.TxPath-1);
		else
#endif /* RT3593 */
		{
			if(pAd->Antenna.field.TxPath == 1)
				rtmp_bbp_set_txdac(pAd, 0);
			else
				rtmp_bbp_set_txdac(pAd, 2);
		}

		DBGPRINT(RT_DEBUG_TRACE, ("Use Hw Radio Control Pin=%d; if used Pin=%d;\n", 
					pAd->StaCfg.bHardwareRadio, pAd->StaCfg.bHardwareRadio));
	}
#endif /* CONFIG_STA_SUPPORT */

	RTMP_EEPROM_ASIC_INIT(pAd);

#ifdef RT30xx
	/* Initialize RT3070 serial MAC registers which is different from RT2870 serial*/
	if (IS_RT3090(pAd) || IS_RT3390(pAd) || IS_RT3593(pAd) || IS_RT5390(pAd) || IS_RT5392(pAd))
	{
		/* enable DC filter*/
		if ((pAd->MACVersion & 0xffff) >= 0x0211)
		{
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R103, 0xc0);
		}

		/* improve power consumption in RT3071 Ver.E */
		if (((pAd->MACVersion & 0xffff) >= 0x0211) && !IS_RT3593(pAd))
		{
			RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R31, &bbpreg);
			bbpreg &= (~0x3);
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R31, bbpreg);
		}


		RTMP_IO_WRITE32(pAd, TX_SW_CFG1, 0);
		
		/* RT3071 version E has fixed this issue*/
		if ((pAd->MACVersion & 0xffff) < 0x0211)
		{
			if (pAd->NicConfig2.field.DACTestBit == 1)
			{
				RTMP_IO_WRITE32(pAd, TX_SW_CFG2, 0x2C);	/* To fix throughput drop drastically*/
			}
			else
			{
				RTMP_IO_WRITE32(pAd, TX_SW_CFG2, 0x0F);	/* To fix throughput drop drastically*/
			}
		}
		else
		{
			RTMP_IO_WRITE32(pAd, TX_SW_CFG2, 0x0);
		}
	}
	else if (IS_RT3070(pAd))
	{
		if ((pAd->MACVersion & 0xffff) >= 0x0201)
		{
			/* enable DC filter*/
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R103, 0xc0);
			
			/* improve power consumption in RT3070 Ver.F*/
			RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R31, &bbpreg);
			bbpreg &= (~0x3);
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R31, bbpreg);
		}
		/*
		     RT3070(E) Version[0200]
		     RT3070(F) Version[0201]
		 */
		if (((pAd->MACVersion & 0xffff) < 0x0201))
		{
			RTMP_IO_WRITE32(pAd, TX_SW_CFG1, 0);
			RTMP_IO_WRITE32(pAd, TX_SW_CFG2, 0x2C);	/* To fix throughput drop drastically*/
		}
		else
		{
			RTMP_IO_WRITE32(pAd, TX_SW_CFG2, 0);
		}
	}
	else if (IS_RT3071(pAd) || IS_RT3572(pAd))
	{
		RTMP_IO_WRITE32(pAd, TX_SW_CFG1, 0);
		if (((pAd->MACVersion & 0xffff) < 0x0211))
		{
			if (pAd->NicConfig2.field.DACTestBit == 1)
			{
				RTMP_IO_WRITE32(pAd, TX_SW_CFG2, 0x1F); /* To fix throughput drop drastically*/
			}
			else
			{
				RTMP_IO_WRITE32(pAd, TX_SW_CFG2, 0x0F); /* To fix throughput drop drastically*/
			}
		}
		else
		{
			RTMP_IO_WRITE32(pAd, TX_SW_CFG2, 0x0);
		}
	}

	/* update registers from EEPROM for RT3071 or later(3572/3562/3592).*/
	if (IS_RT3090(pAd) || IS_RT3572(pAd) || IS_RT3390(pAd))
	{
		UCHAR RegIdx, RegValue;
		USHORT value;

		/* after RT3071, write BBP from EEPROM 0xF0 to 0x102*/
		for (i = 0xF0; i <= 0x102; i = i+2)
		{
			value = 0xFFFF;
			RT28xx_EEPROM_READ16(pAd, i, value);
			if ((value != 0xFFFF) && (value != 0))
			{
				RegIdx = (UCHAR)(value >> 8);
				RegValue  = (UCHAR)(value & 0xff);
				RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, RegIdx, RegValue);
				DBGPRINT(RT_DEBUG_TRACE, ("Update BBP Registers from EEPROM(0x%0x), BBP(0x%x) = 0x%x\n", i, RegIdx, RegValue));
			}
		}

		/* after RT3071, write RF from EEPROM 0x104 to 0x116*/
		for (i = 0x104; i <= 0x116; i = i+2)
		{
			value = 0xFFFF;
			RT28xx_EEPROM_READ16(pAd, i, value);
			if ((value != 0xFFFF) && (value != 0))
			{
				RegIdx = (UCHAR)(value >> 8);
				RegValue  = (UCHAR)(value & 0xff);
				RT30xxWriteRFRegister(pAd, RegIdx, RegValue);
				DBGPRINT(RT_DEBUG_TRACE, ("Update RF Registers from EEPROM0x%x), BBP(0x%x) = 0x%x\n", i, RegIdx, RegValue));
			}
		}
	}
#endif /* RT30xx */

#ifdef CONFIG_STA_SUPPORT
#ifdef RTMP_FREQ_CALIBRATION_SUPPORT
		/*
			Only for RT3593, RT5390 (Maybe add other chip in the future)
			Sometimes the frequency will be shift, we need to adjust it.
		*/
		if (pAd->StaCfg.AdaptiveFreq == TRUE) /*Todo: iwpriv and profile support.*/
		pAd->FreqCalibrationCtrl.bEnableFrequencyCalibration = TRUE;

		DBGPRINT(RT_DEBUG_TRACE, ("%s: pAd->FreqCalibrationCtrl.bEnableFrequencyCalibration = %d\n", 
			__FUNCTION__, 
			pAd->FreqCalibrationCtrl.bEnableFrequencyCalibration));

#endif /* RTMP_FREQ_CALIBRATION_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */
	DBGPRINT(RT_DEBUG_TRACE, ("TxPath = %d, RxPath = %d, RFIC=%d\n", 
				pAd->Antenna.field.TxPath, pAd->Antenna.field.RxPath, pAd->RfIcType));
	DBGPRINT(RT_DEBUG_TRACE, ("<-- NICInitAsicFromEEPROM\n"));
}


#ifdef DBG
VOID dump_pdma_reg(RTMP_ADAPTER *pAd)
{
	

}
#endif /* DBG */


#ifdef RTMP_MAC_PCI
#ifdef RLT_MAC
VOID AsicInitTxRxRing(RTMP_ADAPTER *pAd)
{
	DELAY_INT_CFG_STRUC IntCfg;
	WPDMA_GLO_CFG_STRUC GloCfg;
	UINT32 addr;
	INT i, offset;
	
	/*
		Write Tx Ring base address registers 
		
		The Tx Ring arrangement:
		RingIdx	SwRingIdx	AsicPriority	WMM QID
		0 		TxSw0		L			QID_AC_BE
		1		TxSw1		L			QID_AC_BK
		2		TxSw2		L			QID_AC_VI
		3		TxSw3		L			QID_AC_VO

		4		CTRL		M			-
		5		MGMT		H			-

		6		-			L			QID_AC_BE
		7		-			L			QID_AC_BK
		8		-			L			QID_AC_VI
		9		-			L			QID_AC_VO

		Ring 0~3 for TxChannel 0
		Ring 6~9 for TxChannel 1
	*/
#if 0
	for (i = 0 ; i < 4; i++)
#else
	for (i=0; i<NUM_OF_TX_RING; i++)
#endif
	{
		offset = i * 0x10;
		addr = RTMP_GetPhysicalAddressLow(pAd->TxRing[i].Cell[0].AllocPa);
		RTMP_IO_WRITE32(pAd, TX_RING_BASE + offset, addr);
		RTMP_IO_WRITE32(pAd, TX_RING_CNT + offset, TX_RING_SIZE);
		pAd->TxRing[i].TxSwFreeIdx = 0;
		pAd->TxRing[i].TxCpuIdx = 0;
		RTMP_IO_WRITE32(pAd, (TX_RING_CIDX + offset), pAd->TxRing[i].TxCpuIdx);
		DBGPRINT(RT_DEBUG_TRACE, ("-->TX_RING_%d: Base=0x%x, Cnt=%d!\n",
					i, addr, TX_RING_SIZE));
	}


	/* init MGMT ring index pointer */
	addr = RTMP_GetPhysicalAddressLow(pAd->MgmtRing.Cell[0].AllocPa);
	RTMP_IO_WRITE32(pAd, TX_MGMT_BASE, addr);
	RTMP_IO_WRITE32(pAd, TX_MGMT_CNT, MGMT_RING_SIZE);
	pAd->MgmtRing.TxSwFreeIdx = 0;
	pAd->MgmtRing.TxCpuIdx = 0;
	RTMP_IO_WRITE32(pAd, TX_MGMT_CIDX,  pAd->MgmtRing.TxCpuIdx);
	DBGPRINT(RT_DEBUG_TRACE, ("-->TX_RING_MGMT: Base=0x%x, Cnt=%d!\n",
					addr, TX_RING_SIZE));


	/* Init RX Ring index pointer */
	addr = RTMP_GetPhysicalAddressLow(pAd->RxRing.Cell[0].AllocPa);
	RTMP_IO_WRITE32(pAd, RX_RING_BASE, addr);
	RTMP_IO_WRITE32(pAd, RX_RING_CNT, RX_RING_SIZE);
	pAd->RxRing.RxSwReadIdx = 0;
	pAd->RxRing.RxCpuIdx = RX_RING_SIZE - 1;
	DBGPRINT(RT_DEBUG_TRACE, ("-->RX_RING: Base=0x%x, Cnt=%d\n", addr, RX_RING_SIZE));
	for(i = 0; i < RX_RING_NUM; i++)
	{
		RTMP_IO_WRITE32(pAd, RX_RING_CIDX + i * 0x10, pAd->RxRing.RxCpuIdx);
	}

	/*
		Reset DMA Index
	*/
	RTMP_IO_WRITE32(pAd, WPDMA_RST_IDX, 0xFFFFFFFF);

	/* Set DMA global configuration except TX_DMA_EN and RX_DMA_EN bits */
	AsicWaitPDMAIdle(pAd, 100, 1000);
	RTMP_IO_READ32(pAd, WPDMA_GLO_CFG, &GloCfg.word);
	GloCfg.word &= 0xff0;
	GloCfg.field.EnTXWriteBackDDONE = 1;
	RTMP_IO_WRITE32(pAd, WPDMA_GLO_CFG, GloCfg.word);

	IntCfg.word = 0;
	RTMP_IO_WRITE32(pAd, DELAY_INT_CFG, IntCfg.word);
}
#else
VOID AsicInitTxRxRing(RTMP_ADAPTER *pAd)
{
	DELAY_INT_CFG_STRUC IntCfg;
	WPDMA_GLO_CFG_STRUC GloCfg;
	UINT32 Value;
	INT i;
	

	/* Write AC_BK base address register */
	Value = RTMP_GetPhysicalAddressLow(pAd->TxRing[QID_AC_BK].Cell[0].AllocPa);
	RTMP_IO_WRITE32(pAd, TX_BASE_PTR1, Value);
	DBGPRINT(RT_DEBUG_TRACE, ("--> TX_BASE_PTR1 : 0x%x\n", Value));

	/* Write AC_BE base address register */
	Value = RTMP_GetPhysicalAddressLow(pAd->TxRing[QID_AC_BE].Cell[0].AllocPa);
	RTMP_IO_WRITE32(pAd, TX_BASE_PTR0, Value);
	DBGPRINT(RT_DEBUG_TRACE, ("-->TX_BASE_PTR0: 0x%x\n", Value));

	/* Write AC_VI base address register */
	Value = RTMP_GetPhysicalAddressLow(pAd->TxRing[QID_AC_VI].Cell[0].AllocPa);
	RTMP_IO_WRITE32(pAd, TX_BASE_PTR2, Value);
	DBGPRINT(RT_DEBUG_TRACE, ("-->TX_BASE_PTR2: 0x%x\n", Value));

	/* Write AC_VO base address register */
	Value = RTMP_GetPhysicalAddressLow(pAd->TxRing[QID_AC_VO].Cell[0].AllocPa);	
	RTMP_IO_WRITE32(pAd, TX_BASE_PTR3, Value);
	DBGPRINT(RT_DEBUG_TRACE, ("-->TX_BASE_PTR3: 0x%x\n", Value));

	/* Write HCCA base address register */
	Value = RTMP_GetPhysicalAddressLow(pAd->TxRing[QID_HCCA].Cell[0].AllocPa);
	RTMP_IO_WRITE32(pAd, TX_BASE_PTR4, Value);
	DBGPRINT(RT_DEBUG_TRACE, ("-->TX_BASE_PTR4: 0x%x\n", Value));

	/* Write MGMT_BASE_CSR register */
	Value = RTMP_GetPhysicalAddressLow(pAd->MgmtRing.Cell[0].AllocPa);
	RTMP_IO_WRITE32(pAd, TX_BASE_PTR5, Value);
	DBGPRINT(RT_DEBUG_TRACE, ("-->TX_BASE_PTR5: 0x%x\n", Value));

	/* Write RX_BASE_CSR register */
	Value = RTMP_GetPhysicalAddressLow(pAd->RxRing.Cell[0].AllocPa);
	RTMP_IO_WRITE32(pAd, RX_BASE_PTR, Value);
	DBGPRINT(RT_DEBUG_TRACE, ("-->RX_BASE_PTR: 0x%x\n", Value));

	/* Init RX Ring index pointer */
	pAd->RxRing.RxSwReadIdx = 0;
	pAd->RxRing.RxCpuIdx = RX_RING_SIZE-1;
	RTMP_IO_WRITE32(pAd, RX_CRX_IDX, pAd->RxRing.RxCpuIdx);
	
	/* Init TX rings index pointer */
	for (i=0; i<NUM_OF_TX_RING; i++)
	{
		pAd->TxRing[i].TxSwFreeIdx = 0;
		pAd->TxRing[i].TxCpuIdx = 0;
		RTMP_IO_WRITE32(pAd, (TX_CTX_IDX0 + i * 0x10) ,  pAd->TxRing[i].TxCpuIdx);
	}

	/* init MGMT ring index pointer */
	pAd->MgmtRing.TxSwFreeIdx = 0;
	pAd->MgmtRing.TxCpuIdx = 0;
	RTMP_IO_WRITE32(pAd, TX_MGMTCTX_IDX,  pAd->MgmtRing.TxCpuIdx);

	
	/* set each Ring's SIZE  into ASIC. Descriptor Size is fixed by design */
	

	/* Write TX_RING_CSR0 register */
	Value = TX_RING_SIZE;
	RTMP_IO_WRITE32(pAd, TX_MAX_CNT0, Value);
	RTMP_IO_WRITE32(pAd, TX_MAX_CNT1, Value);
	RTMP_IO_WRITE32(pAd, TX_MAX_CNT2, Value);
	RTMP_IO_WRITE32(pAd, TX_MAX_CNT3, Value);
	RTMP_IO_WRITE32(pAd, TX_MAX_CNT4, Value);
	Value = MGMT_RING_SIZE;
	RTMP_IO_WRITE32(pAd, TX_MGMTMAX_CNT, Value);

	/* Write RX_RING_CSR register */
	Value = RX_RING_SIZE;
	RTMP_IO_WRITE32(pAd, RX_MAX_CNT, Value);

	/* Set DMA global configuration except TX_DMA_EN and RX_DMA_EN bits */
	AsicWaitPDMAIdle(pAd, 100, 1000);
	RTMP_IO_READ32(pAd, WPDMA_GLO_CFG, &GloCfg.word);
	GloCfg.word &= 0xff0;
	GloCfg.field.EnTXWriteBackDDONE = 1;
	RTMP_IO_WRITE32(pAd, WPDMA_GLO_CFG, GloCfg.word);
	
	IntCfg.word = 0;
	RTMP_IO_WRITE32(pAd, DELAY_INT_CFG, IntCfg.word);
}
#endif /* RLT_MAC */
#endif /* RTMP_MAC_PCI */


VOID AsicInitBcnBuf(IN RTMP_ADAPTER *pAd)
{
	int idx;
	RTMP_CHIP_CAP *pChipCap = &pAd->chipCap;
	
	
	for (idx = 0; idx < pChipCap->BcnMaxHwNum; idx++)
		pAd->BeaconOffset[idx] = pChipCap->BcnBase[idx];

	DBGPRINT(RT_DEBUG_TRACE, ("< Beacon Information: >\n"));
	DBGPRINT(RT_DEBUG_TRACE, ("\tFlgIsSupSpecBcnBuf = %s\n", pChipCap->FlgIsSupSpecBcnBuf ? "TRUE" : "FALSE"));
	DBGPRINT(RT_DEBUG_TRACE, ("\tBcnMaxHwNum = %d\n", pChipCap->BcnMaxHwNum));
	DBGPRINT(RT_DEBUG_TRACE, ("\tBcnMaxNum = %d\n", pChipCap->BcnMaxNum));
	DBGPRINT(RT_DEBUG_TRACE, ("\tBcnMaxHwSize = 0x%x\n", pChipCap->BcnMaxHwSize));
	DBGPRINT(RT_DEBUG_TRACE, ("\tWcidHwRsvNum = %d\n", pChipCap->WcidHwRsvNum));
	for (idx = 0; idx < pChipCap->BcnMaxHwNum; idx++) {
		DBGPRINT(RT_DEBUG_TRACE, ("\t\tBcnBase[%d] = 0x%x, pAd->BeaconOffset[%d]=0x%x\n",
					idx, pChipCap->BcnBase[idx], idx, pAd->BeaconOffset[idx]));
	}

#ifdef SPECIFIC_BCN_BUF_SUPPORT
	if (pAd->chipCap.FlgIsSupSpecBcnBuf == TRUE)
	{
		RTMP_REG_PAIR BcnSpecMACRegTable[] = {
			/* 	
				That means all beacon's size are 512 bytes 
				and their starting address are "0x4000, 0x4200, 0x4400, 0x4600, ....." 
				in the second(higher) 8KB shared memory . 

				The formula is : 0x4000 + BCNx_OFFSET*64
					ex : the address of BSS0 = 0x4000 + 0x00 * 64 = 0x4000
						 the address of BSS1 = 0x4000 + 0x08 * 64 = 0x4200
			*/
			{BCN_OFFSET0,			0x18100800}, 
			{BCN_OFFSET1,			0x38302820}, 
			{BCN_OFFSET2,			0x58504840}, 
			{BCN_OFFSET3,			0x78706860}, 
		};

		/* re-set beacon offset */
		for(idx = 0; idx < (sizeof(BcnSpecMACRegTable) / sizeof(RTMP_REG_PAIR)); idx++)
		{
			RTMP_IO_WRITE32(pAd, (USHORT)BcnSpecMACRegTable[idx].Register, 
									BcnSpecMACRegTable[idx].Value);
		}
	}
#endif /* SPECIFIC_BCN_BUF_SUPPORT */

#ifdef RLT_MAC
	{
#ifdef RELEASE_EXCLUDE
		/*
			If the bit 7 of each beacon offset is set as 0, the BCN_BASE = 0xc000
			If the bit 7 of each beacon offset is set as 1, the BCN_BASE = 0x8000

			i.e., formula to calculate the beacon offset are:
						
			if you want use share memory in range 0xA000 ~ 0xbFFF
			    formula:
				Beacon Buf Address = 0x8000 + BCN_OFFSET * 64
					if BSS0 = 0xba00
					 offset = (BSS0 - 0x8000) / 64 = 0xE8
			if you want use share memory in range 0xC000 ~ 0xFFFF
			    formula:
				Beacon Buf Address = 0xC000 + BCN_OFFSET * 64
					if BSS0 = 0xC200,
					 offset = (BSS0 - 0xc000) / 64 = 0x08
		*/
#endif /* RELEASE_EXCLUDE */
		RTMP_REG_PAIR bcn_mac_reg_tb[] = {
			{BCN_OFFSET0, 0x18100800},
			{BCN_OFFSET1, 0x38302820},
			{BCN_OFFSET2, 0x58504840},
			{BCN_OFFSET3, 0x78706860},
		};
		for (idx = 0; idx < 4; idx ++)
		{
			RTMP_IO_WRITE32(pAd, (USHORT)bcn_mac_reg_tb[idx].Register, 
									bcn_mac_reg_tb[idx].Value);
		}
	}
#endif /* RLT_MAC */

}


/*
	========================================================================
	
	Routine Description:
		Initialize NIC hardware

	Arguments:
		Adapter						Pointer to our adapter

	Return Value:
		None

	IRQL = PASSIVE_LEVEL

	Note:
		
	========================================================================
*/
NDIS_STATUS	NICInitializeAdapter(
	IN	PRTMP_ADAPTER	pAd,
	IN   BOOLEAN    bHardReset)
{
	NDIS_STATUS     Status = NDIS_STATUS_SUCCESS;
	WPDMA_GLO_CFG_STRUC	GloCfg;
	ULONG j=0;


	DBGPRINT(RT_DEBUG_TRACE, ("--> NICInitializeAdapter\n"));
	
	/* Set DMA global configuration except TX_DMA_EN and RX_DMA_EN bits */
retry:

	if (AsicWaitPDMAIdle(pAd, 100, 1000) != TRUE) {
		if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))
			return NDIS_STATUS_FAILURE;
	}

#ifdef RTMP_MAC_PCI
	RTMP_IO_READ32(pAd, WPDMA_GLO_CFG, &GloCfg.word);
	GloCfg.word &= 0xff0;
	GloCfg.field.EnTXWriteBackDDONE = 1;
	RTMP_IO_WRITE32(pAd, WPDMA_GLO_CFG, GloCfg.word);
	DBGPRINT(RT_DEBUG_TRACE, ("<== DMA offset 0x208 = 0x%x\n", GloCfg.word));
#endif /* RTMP_MAC_PCI */
	
#ifdef RTMP_MAC_PCI
	/* pbf hardware reset, asic simulation sequence put this ahead before loading firmware */
	RTMP_IO_WRITE32(pAd, WPDMA_RST_IDX, 0x1003f);	/* 0x10000 for reset rx, 0x3f resets all 6 tx rings.*/
#ifdef RT8592
	// TODO: shiang-6590, sync with windows, why 85592 don't need this???
	if (!IS_RT65XX(pAd))
#endif /* RT8592 */
	{
		RTMP_IO_WRITE32(pAd, PBF_SYS_CTRL, 0xe1f);
		RTMP_IO_WRITE32(pAd, PBF_SYS_CTRL, 0xe00);
	}
#endif /* RTMP_MAC_PCI */

	/* Initialze ASIC for TX & Rx operation*/
	if (NICInitializeAsic(pAd , bHardReset) != NDIS_STATUS_SUCCESS)
	{
		if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))
			return NDIS_STATUS_FAILURE;

		if (pAd->chipOps.loadFirmware)
		{
			if (j++ == 0)
			{
				NICLoadFirmware(pAd);
				goto retry;
			}
		}
		return NDIS_STATUS_FAILURE;
	}

#if defined(CONFIG_CSO_SUPPORT) || defined(CONFIG_TSO_SUPPORT)
	// TODO: shiang-6590, we need configure TSO before can do tx/rx
	rlt_net_acc_init(pAd);
#endif /* CONFIG_CSO_SUPPORT */

#ifdef RTMP_MAC_PCI
	/* write all shared Ring's base address into ASIC*/
	AsicInitTxRxRing(pAd);
#endif /* RTMP_MAC_PCI */

#ifdef MT7601
#ifdef ED_MONITOR
	// TODO: for certification only!
#if 0
	if (IS_MT7601(pAd)) {
		MT7601_set_ed_cca(pAd, TRUE);
	}
#endif
#endif /* ED_MONITOR */
#endif /* MT7601 */
	DBGPRINT(RT_DEBUG_TRACE, ("<-- NICInitializeAdapter\n"));
	return Status;
}

/*
	========================================================================
	
	Routine Description:
		Initialize ASIC

	Arguments:
		Adapter						Pointer to our adapter

	Return Value:
		None

	IRQL = PASSIVE_LEVEL

	Note:
		
	========================================================================
*/
NDIS_STATUS	NICInitializeAsic(
	IN	PRTMP_ADAPTER	pAd,
	IN  BOOLEAN		bHardReset)
{
	ULONG			Index = 0;
	UINT32			MACValue = 0;
#ifdef RTMP_MAC_USB
	UINT32			Counter = 0;
	USB_DMA_CFG_STRUC UsbCfg;
#endif /* RTMP_MAC_USB */
	USHORT			KeyIdx;

#ifdef RLT_MAC
	RTMP_CHIP_CAP *pChipCap = &pAd->chipCap;
#endif

	DBGPRINT(RT_DEBUG_TRACE, ("--> NICInitializeAsic\n"));

#ifdef RTMP_MAC_PCI
#ifdef RT8592
	// TODO:shiang-6590, why we don't need to change PWR_PIN_CFG as 1 here? Windows did it!!
	if (IS_RT8592(pAd)) {
		RTMP_IO_WRITE32(pAd, PWR_PIN_CFG, 0x1);
	}
	else
#endif /* RT8592 */
#ifdef RT65xx
	if (IS_RT6590(pAd))
	{
		/*
			PWR_PIN_CFG[2:0]: obsolete, no function
			Don't need to change PWR_PIN_CFG here.
		*/
		;
	}
	else
#endif /* RT65xx */
#ifdef MT7601
	if (IS_MT7601(pAd))
	{
		/*
			PWR_PIN_CFG[2:0]: obsolete, no function
			Don't need to change PWR_PIN_CFG here.
		*/
		;
	}
	else
#endif /* MT7601 */
	{
		RTMP_IO_WRITE32(pAd, PWR_PIN_CFG, 0x3);	/* To fix driver disable/enable hang issue when radio off*/
	}

	if (bHardReset == TRUE)
	{
		RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, 0x3);

#ifdef RT3593
		if (IS_RT3593(pAd))
		{
			/* SNR mapping */
			RT3593_SNR_MAPPING_INIT(pAd);
		}
#endif /* RT3593 */
	}
	else
		RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, 0x1);

	RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, 0x0);
	/* Initialize MAC register to default value*/
	for (Index = 0; Index < NUM_MAC_REG_PARMS; Index++)
	{
#ifdef RT30xx
		if ((MACRegTable[Index].Register == TX_SW_CFG0) &&
			(IS_RT3090(pAd) || IS_RT3390(pAd)))
		{
			MACRegTable[Index].Value = 0x00000400;
		}
#endif /* RT30xx */

#ifdef RT8592
		if ((MACRegTable[Index].Register == PWR_PIN_CFG) && (IS_RT8592(pAd)))
			MACRegTable[Index].Value = 0x1;
#endif /* RT8592 */

#ifdef RT65xx
		if ((MACRegTable[Index].Register == PWR_PIN_CFG) && (IS_RT6590(pAd)))
			MACRegTable[Index].Value = 0x00;
#endif /* RT65xx */

#ifdef MT7601
		if ((MACRegTable[Index].Register == PWR_PIN_CFG) && (IS_MT7601(pAd)))
			MACRegTable[Index].Value = 0x00;
#endif /* MT7601 */

		RTMP_IO_WRITE32(pAd,
			MACRegTable[Index].Register,
			MACRegTable[Index].Value);
	}

#ifdef CONFIG_AP_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_AP(pAd)
	{
		for (Index = 0; Index < NUM_AP_MAC_REG_PARMS; Index++)
		{
			RTMP_IO_WRITE32(pAd,
				APMACRegTable[Index].Register,
				APMACRegTable[Index].Value);
		}
	}
#endif /* CONFIG_AP_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	{
		for (Index = 0; Index < NUM_STA_MAC_REG_PARMS; Index++)
		{
			RTMP_IO_WRITE32(pAd,
				STAMACRegTable[Index].Register,
				STAMACRegTable[Index].Value);
		}
	}
#endif /* CONFIG_STA_SUPPORT */
#endif /* RTMP_MAC_PCI */

#ifdef RTMP_PCI_SUPPORT
	pAd->CommonCfg.bPCIeBus = FALSE; /* PCI bus*/

	if ((pAd->infType == RTMP_DEV_INF_PCI || 
		pAd->infType == RTMP_DEV_INF_PCIE)
#ifdef RT3290
		&& (!IS_RT3290(pAd))
#endif /* RT3290 */
#ifdef RT65xx
		&& (!(IS_RT65XX(pAd)))
#endif /* RT65xx */
#ifdef MT7601
		&& (!(IS_MT7601(pAd)))
#endif /* MT7601 */
	)
	{
#ifdef RTMP_MAC
		// TODO: shiang-6590, how about 6590 for US_CYC_CNT register?
		UINT32 Value;

		/* PCI and PCIe have different value in US_CYC_CNT*/
		RTMP_IO_READ32(pAd, PCI_CFG, &Value);
		if ((Value & 0x10000) == 0)
		{
			US_CYC_CNT_STRUC USCycCnt;
			UINT32 Value;

			RTMP_IO_READ32(pAd, US_CYC_CNT, &Value);
			USCycCnt.word = Value;
			USCycCnt.field.UsCycCnt = 0x7D;
			RTMP_IO_WRITE32(pAd, US_CYC_CNT, USCycCnt.word);
			
			pAd->CommonCfg.bPCIeBus = TRUE;
			
			DBGPRINT(RT_DEBUG_TRACE, ("NICInitializeAsic::act as PCIe driver \n"));
		}
		else
		{
			DBGPRINT(RT_DEBUG_TRACE, ("NICInitializeAsic::act as PCI driver \n"));
		}
#endif /* RTMP_MAC */
	}
	DBGPRINT(RT_DEBUG_TRACE, ("%s: pAd->CommonCfg.bPCIeBus = %d\n", 
		__FUNCTION__, pAd->CommonCfg.bPCIeBus));
#endif /* RTMP_PCI_SUPPORT */

#ifdef RTMP_MAC_USB
	/* Make sure MAC gets ready after NICLoadFirmware().*/
	
	Index = 0;
	
	/*To avoid hang-on issue when interface up in kernel 2.4, */
	/*we use a local variable "MacCsr0" instead of using "pAd->MACVersion" directly.*/
	if (WaitForAsicReady(pAd) != TRUE)
			return NDIS_STATUS_FAILURE;

	// TODO: shiang, how about the value setting of pAd->MACVersion?? Original it assigned here

	DBGPRINT(RT_DEBUG_TRACE, ("%s():MACVersion[Ver:Rev=0x%08x]\n",
			__FUNCTION__, pAd->MACVersion));


	if ( !IS_MT7601(pAd) )
	{
	/* turn on bit13 (set to zero) after rt2860D. This is to solve high-current issue.*/
	RTMP_IO_READ32(pAd, PBF_SYS_CTRL, &MACValue);
	MACValue &= (~0x2000);
	RTMP_IO_WRITE32(pAd, PBF_SYS_CTRL, MACValue);
	}

	RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, 0x3);
	RTMP_IO_WRITE32(pAd, USB_DMA_CFG, 0x0);

#ifdef RTMP_MAC
	RTUSBVenderReset(pAd);
#endif
#ifdef RELEASE_EXCLUDE
	/* 
		Patch on 2009/12/10 for resolving RT3070 unable to connect with AP issue.
		Add delay in base band reset time due to platform depending issue.
	*/
#endif /* RELEASE_EXCLUDE */
	RTMPusecDelay(1000); 
	RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, 0x0);
#endif /* RTMP_MAC_USB */

#ifdef RTMP_MAC_USB
	UsbCfg.word = 0;
	
	/* USB1.1 do not use bulk in aggregation */
	if (pAd->BulkInMaxPacketSize == 512)
		UsbCfg.field.RxBulkAggEn = 1;

	/* for last packet, PBF might use more than limited, so minus 2 to prevent from error */
		UsbCfg.field.RxBulkAggLmt = (MAX_RXBULK_SIZE /1024)-3;
#ifdef DPA_T
	UsbCfg.field.RxBulkAggTOut = 0xFF;
#else
	UsbCfg.field.RxBulkAggTOut = 0x80; 
#endif

	UsbCfg.field.RxBulkEn = 1;
	UsbCfg.field.TxBulkEn = 1;
	
	RTMP_IO_WRITE32(pAd, USB_DMA_CFG, UsbCfg.word);

#ifdef MT7601
	if ( IS_MT7601(pAd) )
	{
		UsbCfg.field.UDMA_RX_WL_DROP = 1;
		RTMP_IO_WRITE32(pAd, USB_DMA_CFG, UsbCfg.word);
	
		UsbCfg.field.UDMA_RX_WL_DROP = 0;
		RTMP_IO_WRITE32(pAd, USB_DMA_CFG, UsbCfg.word);

	}
	
#endif /* MT7601 */

#ifdef RLT_MAC
	/* Select Q2 to receive command response */
	RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_MCU_SEND_IN_BAND_CMD);
	AndesFunSetOP(pAd, Q_SELECT, pChipCap->CmdRspRxRing);
	RTUSBBulkCmdRspEventReceive(pAd);

	RTUSBBulkReceive(pAd);
#endif /* RLT_MAC */
#endif /* RTMP_MAC_USB */

#if defined(RTMP_MAC_USB) && defined(RLT_MAC)

	AndesRandomWritePair(pAd, MACRegTable, NUM_MAC_REG_PARMS);
#else

	/* Initialize MAC register to default value*/
	for(Index=0; Index<NUM_MAC_REG_PARMS; Index++)
	{
#ifdef RT30xx
		if ((MACRegTable[Index].Register == TX_SW_CFG0) &&
			(IS_RT3070(pAd) || IS_RT3071(pAd) || IS_RT3390(pAd)))
		{
			MACRegTable[Index].Value = 0x00000400;
		}
#endif /* RT30xx */
		RTMP_IO_WRITE32(pAd, (USHORT)MACRegTable[Index].Register, MACRegTable[Index].Value);
	}
#endif /* defined(RTMP_MAC_USB) && defined(RLT_MAC) */

	AsicInitBcnBuf(pAd);

	/* re-set specific MAC registers for individual chip */
	if (pAd->chipOps.AsicMacInit != NULL)
		pAd->chipOps.AsicMacInit(pAd);

	
	/* Before program BBP, we need to wait BBP/RF get wake up.*/
	Index = 0;
	do
	{
		RTMP_IO_READ32(pAd, MAC_STATUS_CFG, &MACValue);

		if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST))			
			return NDIS_STATUS_FAILURE;

		if ((MACValue & 0x03) == 0)	/* if BB.RF is stable*/
			break;
		
		DBGPRINT(RT_DEBUG_TRACE, ("Check MAC_STATUS_CFG  = Busy = %x\n", MACValue));
		RTMPusecDelay(1000);
	} while (Index++ < 100);

#ifdef RTMP_MAC_PCI
	/* The commands to firmware should be after these commands, these commands will init firmware*/
	/* PCI and USB are not the same because PCI driver needs to wait for PCI bus ready*/
	RTMP_IO_WRITE32(pAd, H2M_BBP_AGENT, 0);	/* initialize BBP R/W access agent*/
	RTMP_IO_WRITE32(pAd, H2M_MAILBOX_CSR, 0);
#ifdef RELEASE_EXCLUDE
	/* 2008/11/28: KH add to fix the dead rf frequency offset bug. */
#endif /* RELEASE_EXCLUDE */
	AsicSendCommandToMcu(pAd, 0x72, 0, 0, 0, FALSE);
#endif /* RTMP_MAC_PCI */

#ifdef RTMP_MAC_USB
	if ( !IS_MT7601(pAd) )
	{
	/* The commands to firmware should be after these commands, these commands will init firmware*/
	/* PCI and USB are not the same because PCI driver needs to wait for PCI bus ready*/
		RTUSBWriteMACRegister(pAd, H2M_BBP_AGENT, 0, FALSE); /* initialize BBP R/W access agent. */
		RTUSBWriteMACRegister(pAd,H2M_MAILBOX_CSR,0, FALSE);
		RTUSBWriteMACRegister(pAd, H2M_INT_SRC, 0, FALSE);
		AsicSendCommandToMcu(pAd, 0x72, 0x00, 0x00, 0x00, FALSE); /* reset rf by MCU supported by new firmware */
	}
#endif /* RTMP_MAC_USB */

	/* Wait to be stable.*/
	RTMPusecDelay(1000);
	pAd->LastMCUCmd = 0x72;

	NICInitBBP(pAd);
	
#ifdef RTMP_MAC_PCI
	/* TODO: check MACVersion, currently, rbus-based chip use this.*/
	if (pAd->MACVersion == 0x28720200)
	{
		/*UCHAR value;*/
		UINT32 value2;

		/*disable MLD by Bruce 20080704*/
		/*BBP_IO_READ8_BY_REG_ID(pAd, BBP_R105, &value);*/
		/*BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R105, value | 4);*/
	
		/*Maximum PSDU length from 16K to 32K bytes	*/
		RTMP_IO_READ32(pAd, MAX_LEN_CFG, &value2);
		value2 &= ~(0x3<<12);
		value2 |= (0x2<<12);
		RTMP_IO_WRITE32(pAd, MAX_LEN_CFG, value2);
	}
#endif /* RTMP_MAC_PCI */

	if ((IS_RT3883(pAd)) || IS_RT65XX(pAd) || IS_MT7601(pAd) ||
#ifdef RT3593
		RT3593_MAC_VERSION_CHECK(pAd->MACVersion) ||
#endif /* RT3593 */
		((pAd->MACVersion >= RALINK_2880E_VERSION) &&
		(pAd->MACVersion < RALINK_3070_VERSION))) /* 3*3*/
	{
		/* enlarge MAX_LEN_CFG*/
		UINT32 csr;
		RTMP_IO_READ32(pAd, MAX_LEN_CFG, &csr);
#if defined(RT2883) || defined(RT3883) || defined(RT3593) || defined(RT65xx) || defined(MT7601)
		if (IS_RT2883(pAd) || IS_RT3883(pAd) || IS_RT3593(pAd) || IS_RT65XX(pAd) || IS_MT7601(pAd)) 
		{
			csr |= 0x3fff;
		}
		else
#endif /* defined(RT2883) || defined(RT3883) || defined(RT3593) */
		{
			csr &= 0xFFF;
			csr |= 0x2000;
		}
		RTMP_IO_WRITE32(pAd, MAX_LEN_CFG, csr);
	}

#ifdef RTMP_MAC_USB
#ifdef RLT_MAC
	{
	UINT32 MACValue[128 * 2];

	for (Index = 0; Index < 128 * 2; Index+=2)
	{
		MACValue[Index] = 0xffffffff;
		MACValue[Index + 1] = 0x00ffffff;
	}

	AndesBurstWrite(pAd, MAC_WCID_BASE, MACValue, 128 * 2);

#if 0 //def MT7601
	for (Index = 0; Index < 128 * 2; Index+=2)
	{
		MACValue[Index] = 0x8183;
		MACValue[Index + 1] = 0x0;
	}

	BurstWrite(pAd, 0x1c00, MACValue, 128 * 2);
#endif /* MT7601 */
	}
#else
	{
	UCHAR	MAC_Value[]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0,0};

	/*Initialize WCID table*/
	for(Index =0 ;Index < 254;Index++)
	{
		RTUSBMultiWrite(pAd, (USHORT)(MAC_WCID_BASE + Index * 8), MAC_Value, 8, FALSE);
	}
	}

#endif /* RLT_MAC */
#endif /* RTMP_MAC_USB */

#ifdef CONFIG_STA_SUPPORT
	/* Add radio off control*/
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	{
		if (pAd->StaCfg.bRadio == FALSE)
		{
/*			RTMP_IO_WRITE32(pAd, PWR_PIN_CFG, 0x00001818);*/
			RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_RADIO_OFF);
			DBGPRINT(RT_DEBUG_TRACE, ("Set Radio Off\n"));
		}
	}
#endif /* CONFIG_STA_SUPPORT */	

	/* Clear raw counters*/
	NicResetRawCounters(pAd);
	
	/* ASIC will keep garbage value after boot*/
	/* Clear all shared key table when initial*/
	/* This routine can be ignored in radio-ON/OFF operation. */
	if (bHardReset)
	{
#if defined(RTMP_MAC_USB) && defined(RLT_MAC)
		{
			UINT32 MACValue[4];

			for (Index = 0; Index < 4; Index++)
				MACValue[Index] = 0;

			AndesBurstWrite(pAd, SHARED_KEY_MODE_BASE, MACValue, 4);
		}

		/* Clear all pairwise key table when initial*/
		{
			UINT32 MACValue[256];

			for (Index = 0; Index < 256; Index++)
				MACValue[Index] = 1;

			AndesBurstWrite(pAd, MAC_WCID_ATTRIBUTE_BASE, MACValue, 256);
		}
#else

		printk("SHARED_KEY_MODE_BASE = %x\n", SHARED_KEY_MODE_BASE);
		printk("MAC_WCID_ATTRIBUTE_BASE = %x\n", MAC_WCID_ATTRIBUTE_BASE);
		for (KeyIdx = 0; KeyIdx < 4; KeyIdx++)
		{
			RTMP_IO_WRITE32(pAd, SHARED_KEY_MODE_BASE + 4*KeyIdx, 0);
		}

		/* Clear all pairwise key table when initial*/
		for (KeyIdx = 0; KeyIdx < 256; KeyIdx++)
		{
			RTMP_IO_WRITE32(pAd, MAC_WCID_ATTRIBUTE_BASE + (KeyIdx * HW_WCID_ATTRI_SIZE), 1);
		}
#endif /* defined(RTMP_MAC_USB) && defined(RLT_MAC) */
	}

	/* assert HOST ready bit*/
/*  RTMP_IO_WRITE32(pAd, MAC_CSR1, 0x0);  2004-09-14 asked by Mark*/
/*  RTMP_IO_WRITE32(pAd, MAC_CSR1, 0x4);*/

	/* It isn't necessary to clear this space when not hard reset. */
	if (bHardReset == TRUE)
	{
		/* clear all on-chip BEACON frame space */
#ifdef CONFIG_AP_SUPPORT
		INT	i, apidx;
		for (apidx = 0; apidx < HW_BEACON_MAX_COUNT(pAd); apidx++)
		{
			if (pAd->BeaconOffset[apidx] > 0) {
				// TODO: shiang-6590, if we didn't define MBSS_SUPPORT, the pAd->BeaconOffset[x] may set as 0 when chipCap.BcnMaxHwNum != HW_BEACON_MAX_COUNT
				for (i = 0; i < HW_BEACON_OFFSET; i+=4)
					RTMP_CHIP_UPDATE_BEACON(pAd, pAd->BeaconOffset[apidx] + i, 0x00, 4); 
			}
#ifdef RTMP_MAC_USB
			IF_DEV_CONFIG_OPMODE_ON_AP(pAd)
			{
				if (pAd->CommonCfg.pBeaconSync)
					pAd->CommonCfg.pBeaconSync->BeaconBitMap &= (~(BEACON_BITMAP_MASK & (1 << apidx)));
			}
#endif /* RTMP_MAC_USB */
		}
#endif /* CONFIG_AP_SUPPORT */
	}
	
#ifdef RTMP_MAC_USB
	AsicDisableSync(pAd);

	/* Clear raw counters*/
	NicResetRawCounters(pAd);

	/* Default PCI clock cycle per ms is different as default setting, which is based on PCI.*/
	RTMP_IO_READ32(pAd, USB_CYC_CFG, &Counter);
	Counter&=0xffffff00;
	Counter|=0x000001e;
	RTMP_IO_WRITE32(pAd, USB_CYC_CFG, Counter);
#endif /* RTMP_MAC_USB */

#ifdef CONFIG_STA_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	{
		/* for rt2860E and after, init TXOP_CTRL_CFG with 0x583f. This is for extension channel overlapping IOT.*/
		if ((pAd->MACVersion&0xffff) != 0x0101)
			RTMP_IO_WRITE32(pAd, TXOP_CTRL_CFG, 0x583f);
	}
#endif /* CONFIG_STA_SUPPORT */

#ifdef RT3290
	if (IS_RT3290(pAd))
	{
		UINT32 coex_val;
		//halt wlan tx when bt_rx_busy asserted
		RTMP_IO_READ32(pAd, COEXCFG2, &coex_val);
		coex_val |= 0x100;
		RTMP_IO_WRITE32(pAd, COEXCFG2, coex_val);
	}
#endif /* RT3290 */

	DBGPRINT(RT_DEBUG_TRACE, ("<-- NICInitializeAsic\n"));
	return NDIS_STATUS_SUCCESS;
}

#if 0
/*
	========================================================================
	
	Routine Description:
		Reset NIC Asics

	Arguments:
		Adapter						Pointer to our adapter

	Return Value:
		None

	IRQL = PASSIVE_LEVEL

	Note:
		Reset NIC to initial state AS IS system boot up time.
		
	========================================================================
*/
VOID	NICIssueReset(
	IN	PRTMP_ADAPTER	pAd)
{
	UINT32	Value = 0;
	DBGPRINT(RT_DEBUG_TRACE, ("--> NICIssueReset\n"));

	/* Abort Tx, prevent ASIC from writing to Host memory*/
	/*RTMP_IO_WRITE32(pAd, TX_CNTL_CSR, 0x001f0000);*/
	
	/* Disable Rx, register value supposed will remain after reset*/
	RTMP_IO_READ32(pAd, MAC_SYS_CTRL, &Value);
	Value &= (0xfffffff3);
	RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, Value);

	/* Issue reset and clear from reset state*/
	RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, 0x03); /* 2004-09-17 change from 0x01*/
	RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, 0x00);

	DBGPRINT(RT_DEBUG_TRACE, ("<-- NICIssueReset\n"));
}

/*
	========================================================================
	
	Routine Description:
		Check ASIC registers and find any reason the system might hang

	Arguments:
		Adapter						Pointer to our adapter

	Return Value:
		None

	IRQL = DISPATCH_LEVEL
	
	========================================================================
*/
BOOLEAN	NICCheckForHang(
	IN	PRTMP_ADAPTER	pAd)
{
	return (FALSE);
}
		
/*
	========================================================================
	
	Routine Description:
		Read the following from the registry
		1. All the parameters
		2. NetworkAddres

	Arguments:
		Adapter						Pointer to our adapter
		WrapperConfigurationContext	For use by NdisOpenConfiguration

	Return Value:
		NDIS_STATUS_SUCCESS
		NDIS_STATUS_FAILURE
		NDIS_STATUS_RESOURCES

	IRQL = PASSIVE_LEVEL

	Note:
	
	========================================================================
*/
NDIS_STATUS	NICReadRegParameters(
	IN	PRTMP_ADAPTER		pAd,
	IN	NDIS_HANDLE			WrapperConfigurationContext
	)
{
	NDIS_STATUS						Status = NDIS_STATUS_SUCCESS;
	DBGPRINT_S(Status, ("<-- NICReadRegParameters, Status=%x\n", Status));
	return Status;
}
#endif /* Unused */

#ifdef RTMP_RBUS_SUPPORT
/*
	========================================================================
	
	Routine Description:
		Reset NIC from error

	Arguments:
		Adapter						Pointer to our adapter

	Return Value:
		None

	IRQL = PASSIVE_LEVEL

	Note:
		Reset NIC from error state
		
	========================================================================
*/
VOID NICResetFromError(
	IN PRTMP_ADAPTER pAd)
{
	UCHAR rf_channel;
		
	/* Reset BBP (according to alex, reset ASIC will force reset BBP*/
	/* Therefore, skip the reset BBP*/
	/* RTMP_IO_WRITE32(pAd, MAC_CSR1, 0x2);*/
		
	RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, 0x1);
	/* Remove ASIC from reset state*/
	RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, 0x0);

	NICInitializeAdapter(pAd, FALSE);
	NICInitAsicFromEEPROM(pAd);

	IF_DEV_CONFIG_OPMODE_ON_AP(pAd)
	{
		AsicBBPAdjust(pAd);
	}

#ifdef CONFIG_STA_SUPPORT	
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	{
		AsicStaBbpTuning(pAd);
	}
#endif /* CONFIG_STA_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	{
		if (INFRA_ON(pAd) && (pAd->CommonCfg.CentralChannel != pAd->CommonCfg.Channel) 
			&& (pAd->MlmeAux.HtCapability.HtCapInfo.ChannelWidth == BW_40))
			rf_channel = pAd->CommonCfg.CentralChannel;
		else
			rf_channel = pAd->CommonCfg.Channel;
	}
#endif /* CONFIG_STA_SUPPORT */
#ifdef CONFIG_AP_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_AP(pAd)
	{
		rf_channel = pAd->CommonCfg.CentralChannel;
	}
#endif /* CONFIG_AP_SUPPORT */

#if defined(CONFIG_AP_SUPPORT) || defined(CONFIG_STA_SUPPORT)
	AsicSwitchChannel(pAd, rf_channel, FALSE);
	AsicLockChannel(pAd, rf_channel);
#endif /* defined(CONFIG_AP_SUPPORT) || defined(CONFIG_STA_SUPPORT) */
}
#endif /* RTMP_RBUS_SUPPORT */


#ifdef CONFIG_AP_SUPPORT
#ifdef RTMP_MAC_PCI
/*
	========================================================================
	
	Routine Description:
		In the case, Client may be silent left without sending DeAuth or DeAssoc.
		AP'll continue retry packets for the client since AP doesn't know the STA
		is gone. To Minimum affection of exist traffic is disable retransmition for
		all those packet relative to the STA.
		So decide to change ack required setting of all packet in TX ring
		to "no ACK" requirement for specific Client.

	Arguments:
		Adapter						Pointer to our adapter

	Return Value:
		None

	IRQL = DISPATCH_LEVEL
	
	========================================================================
*/
static VOID ClearTxRingClientAck(
	IN PRTMP_ADAPTER pAd,
	IN MAC_TABLE_ENTRY *pEntry)

{
	INT index;
	USHORT TxIdx;
	PRTMP_TX_RING pTxRing;
	PTXD_STRUC pTxD;
	TXWI_STRUC *pTxWI;
#ifdef RT_BIG_ENDIAN
	PTXD_STRUC	pDestTxD;
	TXD_STRUC	TxD;
	TXWI_STRUC *pDestTxWI;
	TXWI_STRUC	TxWI;
#endif /* RT_BIG_ENDIAN */
	UINT8 TXWISize;

	if (!pAd || !pEntry)
		return;

	TXWISize = pAd->chipCap.TXWISize;

	for (index = 3; index >= 0; index--)
	{
		pTxRing = &pAd->TxRing[index];
		for (TxIdx = 0; TxIdx < TX_RING_SIZE; TxIdx++)
		{
#ifdef RT_BIG_ENDIAN
			pDestTxD = (PTXD_STRUC) pTxRing->Cell[TxIdx].AllocVa;
			TxD = *pDestTxD;
			pTxD = &TxD;
			RTMPDescriptorEndianChange((PUCHAR)pTxD, TYPE_TXD);
#else
			pTxD = (PTXD_STRUC) pTxRing->Cell[TxIdx].AllocVa;
#endif /* RT_BIG_ENDIAN */

			if (!pTxD->DMADONE)
			{
#ifdef RT_BIG_ENDIAN
				pDestTxWI = (TXWI_STRUC *) pTxRing->Cell[TxIdx].DmaBuf.AllocVa;
				NdisMoveMemory((PUCHAR)&TxWI, (PUCHAR)pDestTxWI, TXWISize);
				pTxWI = &TxWI;
				RTMPWIEndianChange(pAd, (PUCHAR)pTxWI, TYPE_TXWI);
#else
				 pTxWI = (TXWI_STRUC *)pTxRing->Cell[TxIdx].DmaBuf.AllocVa;
#endif /* RT_BIG_ENDIAN */

				if (pTxWI->TxWIWirelessCliID == pEntry->Aid)
#ifdef RLT_MAC
					pTxWI->TXWI_N.ACK = FALSE;
#else
					pTxWI->TXWI_O.ACK = FALSE;
#endif /* RLT_MAC */


#ifdef RT_BIG_ENDIAN
				RTMPWIEndianChange(pAd, (PUCHAR)pTxWI, TYPE_TXWI);
				NdisMoveMemory((PUCHAR)pDestTxWI, (PUCHAR)pTxWI, TXWISize);
#endif /* RT_BIG_ENDIAN */
			}
		}
	}
}
#endif /* RTMP_MAC_PCI */
#endif /* CONFIG_AP_SUPPORT */

VOID NICUpdateFifoStaCounters(
	IN PRTMP_ADAPTER pAd)
{
	TX_STA_FIFO_STRUC	StaFifo;
	MAC_TABLE_ENTRY		*pEntry = NULL;
	UINT32				i = 0;
	UCHAR				pid = 0, wcid = 0;
	INT32				reTry;
	UCHAR				succMCS;
#ifdef SMART_ANTENNA
#ifdef RTMP_MAC_PCI
	BOOLEAN				bSATunning = FALSE;
#endif /* RTMP_MAC_PCI */
	RTMP_SA_TRAINING_PARAM *pTrainEntry = NULL;
	BOOLEAN bSADbgOn = FALSE;
#endif /* SMART_ANTENNA */

#ifdef RALINK_ATE		
	/* Nothing to do in ATE mode */
	if (ATE_ON(pAd))
		return;
#endif /* RALINK_ATE */

#ifdef RTMP_MAC_USB
#ifdef CONFIG_STA_SUPPORT
	if(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_IDLE_RADIO_OFF))
		return;
#endif /* CONFIG_STA_SUPPORT */
#endif /* RTMP_MAC_USB */


#ifdef RT65xx
	// TODO: shiang-6590, for 8592 now we have tx-status report packet from hardware!!
	if (IS_RT65XX(pAd))
		return;
#endif /* RT65xx */

#ifdef SMART_ANTENNA
	if (RTMP_SA_WORK_ON(pAd))
	{
		pTrainEntry = &pAd->pSAParam->trainEntry[0];
		pEntry = pTrainEntry->pMacEntry;
		if (pEntry && IS_ENTRY_CLIENT(pEntry))
		{
			bSATunning = TRUE;
			if (pAd->smartAntDbgOn)
				bSADbgOn = TRUE;
		}
	}
#endif /* SMART_ANTENNA */

		do
		{
			RTMP_IO_READ32(pAd, TX_STA_FIFO, &StaFifo.word);

			if (StaFifo.field.bValid == 0)
				break;
		
			wcid = (UCHAR)StaFifo.field.wcid;

#ifdef DBG_CTRL_SUPPORT
#ifdef INCLUDE_DEBUG_QUEUE
		if (pAd->CommonCfg.DebugFlags & DBF_DBQ_TXFIFO) {
			dbQueueEnqueue(0x73, (UCHAR *)(&StaFifo.word));
		}
#endif /* INCLUDE_DEBUG_QUEUE */
#endif /* DBG_CTRL_SUPPORT */

		/* ignore NoACK and MGMT frame use 0xFF as WCID */
			if ((StaFifo.field.TxAckRequired == 0) || (wcid >= MAX_LEN_OF_MAC_TABLE))
			{
				i++;
				continue;
			}

			/* PID store Tx MCS Rate */
			pid = (UCHAR)StaFifo.field.PidType;

			pEntry = &pAd->MacTab.Content[wcid];

			pEntry->DebugFIFOCount++;

#ifdef SMART_ANTENNA
			if ((pEntry->HTPhyMode.field.MCS == 0) && (pid == 15))
			{
				pid = 0;
				if ((StaFifo.field.SuccessRate & 0x7F)!= 0)
				{
					DBGPRINT(RT_DEBUG_ERROR, ("%s():SucMCS(%d) != TxMCS(%d)\n", 
								__FUNCTION__, StaFifo.field.SuccessRate & 0x7F, pid));
					continue;
				}
			}
#endif /* SMART_ANTENNA */

#ifdef DOT11_N_SUPPORT
#ifdef TXBF_SUPPORT
			/* Update BF statistics*/
			if (pAd->chipCap.FlgHwTxBfCap)
			{
				int succMCS = (StaFifo.field.SuccessRate & 0x7F);
				int origMCS = pid;

				if (succMCS==32)
					origMCS = 32;
#ifdef DOT11N_SS3_SUPPORT
				if (succMCS>origMCS && pEntry->HTCapability.MCSSet[2]==0xff)
					origMCS += 16;
#endif /* DOT11N_SS3_SUPPORT */

				if (succMCS>origMCS)
					origMCS = succMCS+1;

				/* MCS16 falls back to MCS8*/
				if (origMCS>=16 && succMCS<=8)
					succMCS += 8;

				/* MCS8 falls back to 0 */
				if (origMCS >= 8 && succMCS == 0)
					succMCS += 7;

				reTry = origMCS-succMCS;

				if (StaFifo.field.eTxBF) {
					if (StaFifo.field.TxSuccess)
						pEntry->TxBFCounters.ETxSuccessCount++;
					else
						pEntry->TxBFCounters.ETxFailCount++;
					pEntry->TxBFCounters.ETxRetryCount += reTry;
				}
				else if (StaFifo.field.iTxBF) {
					if (StaFifo.field.TxSuccess)
						pEntry->TxBFCounters.ITxSuccessCount++;
					else
						pEntry->TxBFCounters.ITxFailCount++;
					pEntry->TxBFCounters.ITxRetryCount += reTry;
				}
				else {
					if (StaFifo.field.TxSuccess)
						pEntry->TxBFCounters.TxSuccessCount++;
					else
						pEntry->TxBFCounters.TxFailCount++;
					pEntry->TxBFCounters.TxRetryCount += reTry;
				}
			}
#endif /* TXBF_SUPPORT */
#endif /* DOT11_N_SUPPORT */

#ifdef UAPSD_SUPPORT
			UAPSD_SP_AUE_Handle(pAd, pEntry, StaFifo.field.TxSuccess);
#endif /* UAPSD_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
			if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_BSS_SCAN_IN_PROGRESS))
				continue;
#endif /* CONFIG_STA_SUPPORT */

			if (!StaFifo.field.TxSuccess)
			{
				pEntry->FIFOCount++;
				pEntry->OneSecTxFailCount++;
#ifdef SMART_ANTENNA
				if (bSATunning)
					pEntry->saLstTxFailCnt++;
#endif /* SMART_ANTENNA */
									
				if (pEntry->FIFOCount >= 1)
				{			
					DBGPRINT(RT_DEBUG_TRACE, ("#"));
#if 0
					SendRefreshBAR(pAd, pEntry);
					pEntry->NoBADataCountDown = 64;
#else
#ifdef DOT11_N_SUPPORT
					pEntry->NoBADataCountDown = 64;
#endif /* DOT11_N_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
#ifdef DOT11Z_TDLS_SUPPORT
					IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
					{
						if(IS_ENTRY_TDLS(pEntry))
						{
							pEntry->TdlsTxFailCount++;
							if (pEntry->TdlsTxFailCount >= 15)
							{
								DBGPRINT(RT_DEBUG_OFF, ("TDLS: TxFail >= 15 LinkTearDown !!!\n"));
								TDLS_TearDownPeerLink(pAd, pEntry->Addr, FALSE);
							}
						}
					}
#endif /* DOT11Z_TDLS_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */

					/* Update the continuous transmission counter.*/
					pEntry->ContinueTxFailCnt++;

					if(pEntry->PsMode == PWR_ACTIVE)
					{
#ifdef DOT11_N_SUPPORT					
						int tid;
						for (tid=0; tid<NUM_OF_TID; tid++)
							BAOriSessionTearDown(pAd, pEntry->Aid,  tid, FALSE, FALSE);
#endif /* DOT11_N_SUPPORT */

#ifdef WDS_SUPPORT
						/* fix WDS Jam issue*/
						if(IS_ENTRY_WDS(pEntry)
							&& (pEntry->LockEntryTx == FALSE)
							&& (pEntry->ContinueTxFailCnt >= pAd->ApCfg.EntryLifeCheck))
						{ 
							DBGPRINT(RT_DEBUG_TRACE, ("Entry %02x:%02x:%02x:%02x:%02x:%02x Blocked!! (Fail Cnt = %d)\n",
								PRINT_MAC(pEntry->Addr), pEntry->ContinueTxFailCnt ));

							pEntry->LockEntryTx = TRUE;
						}
#endif /* WDS_SUPPORT */
					}
#endif
				}
#ifdef CONFIG_AP_SUPPORT
#ifdef RTMP_MAC_PCI
			/* if Tx fail >= 20, then clear TXWI ack in Tx Ring*/
			if (pEntry->ContinueTxFailCnt >= pAd->ApCfg.EntryLifeCheck)
				ClearTxRingClientAck(pAd, pEntry);	
#endif /* RTMP_MAC_PCI */				
#endif /* CONFIG_AP_SUPPORT */
			}
			else
			{
#ifdef DOT11_N_SUPPORT
				if ((pEntry->PsMode != PWR_SAVE) && (pEntry->NoBADataCountDown > 0))
				{
					pEntry->NoBADataCountDown--;
					if (pEntry->NoBADataCountDown==0)
					{
						DBGPRINT(RT_DEBUG_TRACE, ("@\n"));
					}
				}
#endif /* DOT11_N_SUPPORT */
				pEntry->FIFOCount = 0;
				pEntry->OneSecTxNoRetryOkCount++;

#ifdef SMART_ANTENNA
				if (bSATunning)
					pEntry->saLstTxNoRtyCnt++;
#endif /* SMART_ANTEENA */

				/* update NoDataIdleCount when sucessful send packet to STA.*/
				pEntry->NoDataIdleCount = 0;
				pEntry->ContinueTxFailCnt = 0;
#ifdef WDS_SUPPORT
				pEntry->LockEntryTx = FALSE;
#endif /* WDS_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
#ifdef DOT11Z_TDLS_SUPPORT
				IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
				{
					if(IS_ENTRY_TDLS(pEntry))
						pEntry->TdlsTxFailCount = 0;
				}
#endif /* DOT11Z_TDLS_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */
			}

			succMCS = StaFifo.field.SuccessRate & 0x7F;
#ifdef DOT11N_SS3_SUPPORT
			if (pEntry->HTCapability.MCSSet[2] == 0xff)
			{
				if (succMCS > pid)
					pid = pid + 16;
			}
#endif /* DOT11N_SS3_SUPPORT */

			if (StaFifo.field.TxSuccess)
			{
				pEntry->TXMCSExpected[pid]++;
				if (pid == succMCS)
					pEntry->TXMCSSuccessful[pid]++;
				else 
					pEntry->TXMCSAutoFallBack[pid][succMCS]++;
			}
			else
			{
				pEntry->TXMCSFailed[pid]++;
			}

#ifdef DOT11N_SS3_SUPPORT
			if (pid >= 16 && succMCS <= 8)
				succMCS += (2 - (succMCS >> 3)) * 7;
#endif /* DOT11N_SS3_SUPPORT */

			reTry = pid - succMCS;

			if (reTry > 0)
			{
				/* MCS8 falls back to 0 */
				if (pid>=8 && succMCS==0)
					reTry -= 7;
				else if ((pid >= 12) && succMCS <=7)
					reTry -= 4;

				pEntry->OneSecTxRetryOkCount += reTry;
#ifdef SMART_ANTENNA
				if (bSATunning)
					pEntry->saLstTxRtyCnt += reTry;
#endif /* SMART_ANTENNA */
			}
#ifdef RELEASE_EXCLUDE
			else if (reTry < 0)
			{
				DBGPRINT(RT_DEBUG_INFO, ("(%d): reTry %d , (TxMCS = %d, SuccessRate = %d)\n", 
				wcid, reTry, pid, StaFifo.field.SuccessRate & 0x7F));
			}
#endif /* RELEASE_EXCLUDE */

			i++;	/* ASIC store 16 stack*/
		} while ( i < (TX_RING_SIZE<<1) );

#if 0
#ifdef SMART_ANTENNA
	if ((bSATunning == TRUE)&& (bSADbgOn == TRUE) && (pEntry != NULL))
	{
		printk("%d,%d,%d\n", pEntry->saLstTxNoRtyCnt,pEntry->saLstTxRtyCnt,pEntry->saLstTxFailCnt);
	}
#endif /* SMART_ANTENNA */
#endif
}


#ifdef FIFO_EXT_SUPPORT
BOOLEAN NicGetMacFifoTxCnt(
	IN RTMP_ADAPTER *pAd,
	IN MAC_TABLE_ENTRY *pEntry)
{
	if (pEntry->Aid >= 1 && pEntry->Aid <= 8)
	{
		WCID_TX_CNT_STRUC wcidTxCnt;
		UINT32 regAddr;
		
		regAddr = WCID_TX_CNT_0 + (pEntry->Aid - 1) * 4;
		RTMP_IO_READ32(pAd, regAddr, &wcidTxCnt.word);

		pEntry->fifoTxSucCnt += wcidTxCnt.field.succCnt;
		pEntry->fifoTxRtyCnt += wcidTxCnt.field.reTryCnt;
#ifdef SMART_ANTENNA
		pEntry->hwTxSucCnt += wcidTxCnt.field.succCnt;
		pEntry->hwTxRtyCnt += wcidTxCnt.field.reTryCnt;
#endif /* SMART_ANTENNA */
	}

	return TRUE;
}


VOID AsicFifoExtSet(IN RTMP_ADAPTER *pAd)
{
	if (pAd->chipCap.FlgHwFifoExtCap)
	{
		RTMP_IO_WRITE32(pAd, WCID_MAPPING_0, 0x04030201);
		RTMP_IO_WRITE32(pAd, WCID_MAPPING_1, 0x08070605);
	}
}


VOID AsicFifoExtEntryClean(
	IN RTMP_ADAPTER * pAd, 
	IN MAC_TABLE_ENTRY *pEntry)
{
	WCID_TX_CNT_STRUC wcidTxCnt;
	UINT32 regAddr;
			
	if (pAd->chipCap.FlgHwFifoExtCap)
	{
		/* We clean the fifo info when MCS is 0 and Aid is from 1~8 */
		if (pEntry->Aid >=1  && pEntry->Aid <= 8)
		{		
			regAddr = WCID_TX_CNT_0 + (pEntry->Aid - 1) * 4;
			RTMP_IO_READ32(pAd, regAddr, &wcidTxCnt.word);
		}
	}
}
#endif /* FIFO_EXT_SUPPORT */


/*
	========================================================================
	
	Routine Description:
		Read Tx statistic raw counters from hardware registers and record to
		related software variables for later on query

	Arguments:
		pAd					Pointer to our adapter
		pStaTxCnt0			Pointer to record "TX_STA_CNT0" (0x170c)
		pStaTxCnt1			Pointer to record "TX_STA_CNT1" (0x1710)

	Return Value:
		None

	========================================================================
*/
VOID NicGetTxRawCounters(
	IN RTMP_ADAPTER *pAd,
	IN TX_STA_CNT0_STRUC *pStaTxCnt0,
	IN TX_STA_CNT1_STRUC *pStaTxCnt1)
{
#ifdef SMART_ANTENNA
#ifdef SA_LUMP_SUM
	/* 
		TODO: Currently, SA didn't take care about USB interface, 
				we need to reconsider it when support for USB!
	*/
	RTMP_SA_TRAINING_PARAM *pTrainEntry = NULL;
	MAC_TABLE_ENTRY *pEntry = NULL;
	BOOLEAN bLocked = FALSE;
	unsigned long irqFlag;

	if (RTMP_SA_WORK_ON(pAd))
	{
		if (!in_interrupt())
		{
			RTMP_IRQ_LOCK(&pAd->smartAntLock, irqFlag);
			bLocked = TRUE;
		}
		pTrainEntry = &pAd->pSAParam->trainEntry[0];
		pEntry = pTrainEntry->pMacEntry;
	}
#endif /* SA_LUMP_SUM */
#endif /* SMART_ANTENNA */

	RTMP_IO_READ32(pAd, TX_STA_CNT0, &pStaTxCnt0->word);
	RTMP_IO_READ32(pAd, TX_STA_CNT1, &pStaTxCnt1->word);

	pAd->bUpdateBcnCntDone = TRUE;	/* not appear in Rory's code */
	pAd->RalinkCounters.OneSecBeaconSentCnt += pStaTxCnt0->field.TxBeaconCount;
	pAd->RalinkCounters.OneSecTxRetryOkCount += pStaTxCnt1->field.TxRetransmit;
	pAd->RalinkCounters.OneSecTxNoRetryOkCount += pStaTxCnt1->field.TxSuccess;
	pAd->RalinkCounters.OneSecTxFailCount += pStaTxCnt0->field.TxFailCount;

#ifdef STATS_COUNT_SUPPORT
	pAd->WlanCounters.TransmittedFragmentCount.u.LowPart += pStaTxCnt1->field.TxSuccess;
	pAd->WlanCounters.RetryCount.u.LowPart += pStaTxCnt1->field.TxRetransmit;
	pAd->WlanCounters.FailedCount.u.LowPart += pStaTxCnt0->field.TxFailCount;
#endif /* STATS_COUNT_SUPPORT */

#ifdef SMART_ANTENNA
#ifdef SA_LUMP_SUM
	if (pEntry && IS_ENTRY_CLIENT(pEntry))
	{	
		pTrainEntry->sumTxRtyCnt += pStaTxCnt1->field.TxRetransmit;
		pTrainEntry->sumTxFailCnt += pStaTxCnt0->field.TxFailCount;
		pTrainEntry->sumTxCnt += (pStaTxCnt1->field.TxRetransmit + 
									pStaTxCnt1->field.TxSuccess + 
									pStaTxCnt0->field.TxFailCount);
}

	if (bLocked)
		RTMP_IRQ_UNLOCK(&pAd->smartAntLock, irqFlag);
#endif /* SA_LUMP_SUM */
#endif /* SMART_ANTENNA */

}


/*
	========================================================================
	
	Routine Description:
		Clean all Tx/Rx statistic raw counters from hardware registers

	Arguments:
		pAd					Pointer to our adapter

	Return Value:
		None

	========================================================================
*/
VOID NicResetRawCounters(RTMP_ADAPTER *pAd)
{
	UINT32 Counter;
	
	RTMP_IO_READ32(pAd, RX_STA_CNT0, &Counter);
	RTMP_IO_READ32(pAd, RX_STA_CNT1, &Counter);
	RTMP_IO_READ32(pAd, RX_STA_CNT2, &Counter);
	RTMP_IO_READ32(pAd, TX_STA_CNT0, &Counter);
	RTMP_IO_READ32(pAd, TX_STA_CNT1, &Counter);
	RTMP_IO_READ32(pAd, TX_STA_CNT2, &Counter);
}


/*
	========================================================================
	
	Routine Description:
		Read statistical counters from hardware registers and record them
		in software variables for later on query

	Arguments:
		pAd					Pointer to our adapter

	Return Value:
		None

	IRQL = DISPATCH_LEVEL
	
	========================================================================
*/
VOID NICUpdateRawCounters(
	IN PRTMP_ADAPTER pAd)
{
	UINT32	OldValue;/*, Value2;*/
	/*ULONG	PageSum, OneSecTransmitCount;*/
	/*ULONG	TxErrorRatio, Retry, Fail;*/
	RX_STA_CNT0_STRUC	 RxStaCnt0;
	RX_STA_CNT1_STRUC   RxStaCnt1;
	RX_STA_CNT2_STRUC   RxStaCnt2;
	TX_STA_CNT0_STRUC 	 TxStaCnt0;
	TX_STA_CNT1_STRUC	 StaTx1;
	TX_STA_CNT2_STRUC	 StaTx2;
#ifdef STATS_COUNT_SUPPORT
	TX_NAG_AGG_CNT_STRUC	TxAggCnt;
	TX_AGG_CNT0_STRUC	TxAggCnt0;
	TX_AGG_CNT1_STRUC	TxAggCnt1;
	TX_AGG_CNT2_STRUC	TxAggCnt2;
	TX_AGG_CNT3_STRUC	TxAggCnt3;
	TX_AGG_CNT4_STRUC	TxAggCnt4;
	TX_AGG_CNT5_STRUC	TxAggCnt5;
	TX_AGG_CNT6_STRUC	TxAggCnt6;
	TX_AGG_CNT7_STRUC	TxAggCnt7;
#endif /* STATS_COUNT_SUPPORT */
	COUNTER_RALINK		*pRalinkCounters;


	pRalinkCounters = &pAd->RalinkCounters;
#if 0	
/*==================================================================*/
/*Read PBF for emulation debug.*/
	RTMP_IO_READ32(pAd, PBF_DBG, &OldValue);
	RTMP_IO_READ32(pAd, TXRXQ_PCNT, &Value2);
	PageSum = (OldValue&0xff);
	PageSum += ((Value2&0xff));
	PageSum += ((Value2&0xff00)>>8);
	PageSum += ((Value2&0xff0000)>>16);
	PageSum += ((Value2&0xff000000)>>24);
	
/*==================================================================*/
#endif
#ifdef RTMP_MAC_USB
#ifdef STATS_COUNT_SUPPORT
	if(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_IDLE_RADIO_OFF))
		return;

	if(RTMP_TEST_FLAG(pAd, fRTMP_PS_MCU_SLEEP))
		return;
#endif /* STATS_COUNT_SUPPORT */
#endif /* RTMP_MAC_USB */


#if 1
	RTMP_IO_READ32(pAd, RX_STA_CNT0, &RxStaCnt0.word);
	RTMP_IO_READ32(pAd, RX_STA_CNT2, &RxStaCnt2.word);
#else
	{
		RTMP_REG_PAIR RxStaCnt[] = {
			{RX_STA_CNT0,			0x0}, 
			{RX_STA_CNT2,			0x0}, 
		};
		AndesRandomRead(pAd, RxStaCnt, 2);
		RxStaCnt0.word = RxStaCnt[0].Value;
		RxStaCnt2.word = RxStaCnt[1].Value;
		//printk("RxStaCnt0.word = %x\n", RxStaCnt0.word);
		//printk("RxStaCnt2.word = %x\n", RxStaCnt2.word);
	}
#endif

#ifdef CONFIG_AP_SUPPORT
#ifdef CARRIER_DETECTION_SUPPORT
	if ((pAd->CommonCfg.CarrierDetect.Enable == FALSE) || (pAd->OpMode == OPMODE_STA))
#endif /* CARRIER_DETECTION_SUPPORT */
#endif /* CONFIG_AP_SUPPORT */
	{
#ifdef MICROWAVE_OVEN_SUPPORT
	    /* Update RX PLCP error counter*/
	    pAd->PrivateInfo.PhyRxErrCnt += NICSumPLCPErrCnt(pAd); /* get PLCP error count per sec */
		/* Update False CCA counter*/
		pAd->RalinkCounters.OneSecFalseCCACnt += NICSumFalseCCACnt(pAd); /* get FalseCCA count per sec */
		pAd->RalinkCounters.FalseCCACnt += pAd->RalinkCounters.OneSecFalseCCACnt;
#else
		RTMP_IO_READ32(pAd, RX_STA_CNT1, &RxStaCnt1.word);
	    /* Update RX PLCP error counter*/
	    pAd->PrivateInfo.PhyRxErrCnt += RxStaCnt1.field.PlcpErr;
		/* Update False CCA counter*/
		//pAd->RalinkCounters.OneSecFalseCCACnt += RxStaCnt1.field.FalseCca;
		pAd->RalinkCounters.OneSecFalseCCACnt = RxStaCnt1.field.FalseCca;
		pAd->RalinkCounters.FalseCCACnt += RxStaCnt1.field.FalseCca;
		
#endif /* MICROWAVE_OVEN_SUPPORT */

#ifdef ED_MONITOR
		if (pAd->ed_chk /*&& pAd->ed_timer_inited == TRUE*/) //no timer now, and the data may not correct before.
			pAd->false_cca_stat[pAd->ed_stat_lidx] += RxStaCnt1.field.FalseCca;
#endif /* ED_MONITOR */

	}

#ifdef STATS_COUNT_SUPPORT
	/* Update FCS counters*/
	OldValue= pAd->WlanCounters.FCSErrorCount.u.LowPart;
	pAd->WlanCounters.FCSErrorCount.u.LowPart += (RxStaCnt0.field.CrcErr); /* >> 7);*/
	if (pAd->WlanCounters.FCSErrorCount.u.LowPart < OldValue)
		pAd->WlanCounters.FCSErrorCount.u.HighPart++;
#endif /* STATS_COUNT_SUPPORT */

	/* Add FCS error count to private counters*/
	pRalinkCounters->OneSecRxFcsErrCnt += RxStaCnt0.field.CrcErr;
	OldValue = pRalinkCounters->RealFcsErrCount.u.LowPart;
	pRalinkCounters->RealFcsErrCount.u.LowPart += RxStaCnt0.field.CrcErr;
	if (pRalinkCounters->RealFcsErrCount.u.LowPart < OldValue)
		pRalinkCounters->RealFcsErrCount.u.HighPart++;

	/* Update Duplicate Rcv check*/
	pRalinkCounters->DuplicateRcv += RxStaCnt2.field.RxDupliCount;
#ifdef STATS_COUNT_SUPPORT
	pAd->WlanCounters.FrameDuplicateCount.u.LowPart += RxStaCnt2.field.RxDupliCount;
#endif /* STATS_COUNT_SUPPORT */
	/* Update RX Overflow counter*/
	pAd->Counters8023.RxNoBuffer += (RxStaCnt2.field.RxFifoOverflowCount);
	
	/*pAd->RalinkCounters.RxCount = 0;*/
#ifdef RTMP_MAC_USB
	if (pRalinkCounters->RxCount != pAd->watchDogRxCnt)
	{
		pAd->watchDogRxCnt = pRalinkCounters->RxCount;
		pAd->watchDogRxOverFlowCnt = 0;
	}
	else
	{
		if (RxStaCnt2.field.RxFifoOverflowCount)
			pAd->watchDogRxOverFlowCnt++;
		else
			pAd->watchDogRxOverFlowCnt = 0;
	}
#endif /* RTMP_MAC_USB */

	
	/*if (!OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_TX_RATE_SWITCH_ENABLED) || */
	/*	(OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_TX_RATE_SWITCH_ENABLED) && (pAd->MacTab.Size != 1)))*/
	if (!pAd->bUpdateBcnCntDone)
	{
		/* Update BEACON sent count*/
		NicGetTxRawCounters(pAd, &TxStaCnt0, &StaTx1);
		RTMP_IO_READ32(pAd, TX_STA_CNT2, &StaTx2.word);
	}

#if 0	
	Retry = StaTx1.field.TxRetransmit;
	Fail = TxStaCnt0.field.TxFailCount;
	TxErrorRatio = 0;
	OneSecTransmitCount = pAd->WlanCounters.TransmittedFragmentCount.u.LowPart- pAd->WlanCounters.LastTransmittedFragmentCount.u.LowPart;
	if ((OneSecTransmitCount+Retry + Fail) > 0)
		TxErrorRatio = (( Retry + Fail) *100) / (OneSecTransmitCount+Retry + Fail);

	if ((OneSecTransmitCount+Retry + Fail) > 0)
		TxErrorRatio = (( Retry + Fail) *100) / (OneSecTransmitCount+Retry + Fail);
	DBGPRINT(RT_DEBUG_INFO, ("TX ERROR Rate = %ld %%, Retry = %ld, Fail = %ld, Total = %ld  \n",TxErrorRatio, Retry, Fail, (OneSecTransmitCount+Retry + Fail)));
	pAd->WlanCounters.LastTransmittedFragmentCount.u.LowPart = pAd->WlanCounters.TransmittedFragmentCount.u.LowPart;
#endif

	/*if (pAd->bStaFifoTest == TRUE)*/
#ifdef STATS_COUNT_SUPPORT
	{
#if 1
		RTMP_IO_READ32(pAd, TX_AGG_CNT, &TxAggCnt.word);
	RTMP_IO_READ32(pAd, TX_AGG_CNT0, &TxAggCnt0.word);
	RTMP_IO_READ32(pAd, TX_AGG_CNT1, &TxAggCnt1.word);
	RTMP_IO_READ32(pAd, TX_AGG_CNT2, &TxAggCnt2.word);
	RTMP_IO_READ32(pAd, TX_AGG_CNT3, &TxAggCnt3.word);
		RTMP_IO_READ32(pAd, TX_AGG_CNT4, &TxAggCnt4.word);
		RTMP_IO_READ32(pAd, TX_AGG_CNT5, &TxAggCnt5.word);
		RTMP_IO_READ32(pAd, TX_AGG_CNT6, &TxAggCnt6.word);
		RTMP_IO_READ32(pAd, TX_AGG_CNT7, &TxAggCnt7.word);
#else
		RTMP_REG_PAIR TxStaCnt[] = {
			{TX_AGG_CNT,			0x0}, 
			{TX_AGG_CNT0,			0x0}, 
			{TX_AGG_CNT1,			0x0}, 
			{TX_AGG_CNT2,			0x0}, 
			{TX_AGG_CNT3,			0x0}, 
			{TX_AGG_CNT4,			0x0}, 
			{TX_AGG_CNT5,			0x0}, 
			{TX_AGG_CNT6,			0x0}, 
			{TX_AGG_CNT7,			0x0}, 
		};
		AndesRandomRead(pAd, TxStaCnt, 9);
		TxAggCnt.word = TxStaCnt[0].Value;
		TxAggCnt0.word = TxStaCnt[1].Value;
		TxAggCnt1.word = TxStaCnt[2].Value;
		TxAggCnt2.word = TxStaCnt[3].Value;
		TxAggCnt3.word = TxStaCnt[4].Value;
		TxAggCnt4.word = TxStaCnt[5].Value;
		TxAggCnt5.word = TxStaCnt[6].Value;
		TxAggCnt6.word = TxStaCnt[7].Value;
		TxAggCnt7.word = TxStaCnt[8].Value;
#endif
		pRalinkCounters->TxAggCount += TxAggCnt.field.AggTxCount;
		pRalinkCounters->TxNonAggCount += TxAggCnt.field.NonAggTxCount;
		pRalinkCounters->TxAgg1MPDUCount += TxAggCnt0.field.AggSize1Count;
		pRalinkCounters->TxAgg2MPDUCount += TxAggCnt0.field.AggSize2Count;
		
		pRalinkCounters->TxAgg3MPDUCount += TxAggCnt1.field.AggSize3Count;
		pRalinkCounters->TxAgg4MPDUCount += TxAggCnt1.field.AggSize4Count;
		pRalinkCounters->TxAgg5MPDUCount += TxAggCnt2.field.AggSize5Count;
		pRalinkCounters->TxAgg6MPDUCount += TxAggCnt2.field.AggSize6Count;
	
		pRalinkCounters->TxAgg7MPDUCount += TxAggCnt3.field.AggSize7Count;
		pRalinkCounters->TxAgg8MPDUCount += TxAggCnt3.field.AggSize8Count;
		pRalinkCounters->TxAgg9MPDUCount += TxAggCnt4.field.AggSize9Count;
		pRalinkCounters->TxAgg10MPDUCount += TxAggCnt4.field.AggSize10Count;

		pRalinkCounters->TxAgg11MPDUCount += TxAggCnt5.field.AggSize11Count;
		pRalinkCounters->TxAgg12MPDUCount += TxAggCnt5.field.AggSize12Count;
		pRalinkCounters->TxAgg13MPDUCount += TxAggCnt6.field.AggSize13Count;
		pRalinkCounters->TxAgg14MPDUCount += TxAggCnt6.field.AggSize14Count;

		pRalinkCounters->TxAgg15MPDUCount += TxAggCnt7.field.AggSize15Count;
		pRalinkCounters->TxAgg16MPDUCount += TxAggCnt7.field.AggSize16Count;

		/* Calculate the transmitted A-MPDU count*/
		pRalinkCounters->TransmittedAMPDUCount.u.LowPart += TxAggCnt0.field.AggSize1Count;
		pRalinkCounters->TransmittedAMPDUCount.u.LowPart += (TxAggCnt0.field.AggSize2Count >> 1);

		pRalinkCounters->TransmittedAMPDUCount.u.LowPart += (TxAggCnt1.field.AggSize3Count / 3);
		pRalinkCounters->TransmittedAMPDUCount.u.LowPart += (TxAggCnt1.field.AggSize4Count >> 2);

		pRalinkCounters->TransmittedAMPDUCount.u.LowPart += (TxAggCnt2.field.AggSize5Count / 5);
		pRalinkCounters->TransmittedAMPDUCount.u.LowPart += (TxAggCnt2.field.AggSize6Count / 6);

		pRalinkCounters->TransmittedAMPDUCount.u.LowPart += (TxAggCnt3.field.AggSize7Count / 7);
		pRalinkCounters->TransmittedAMPDUCount.u.LowPart += (TxAggCnt3.field.AggSize8Count >> 3);

		pRalinkCounters->TransmittedAMPDUCount.u.LowPart += (TxAggCnt4.field.AggSize9Count / 9);
		pRalinkCounters->TransmittedAMPDUCount.u.LowPart += (TxAggCnt4.field.AggSize10Count / 10);

		pRalinkCounters->TransmittedAMPDUCount.u.LowPart += (TxAggCnt5.field.AggSize11Count / 11);
		pRalinkCounters->TransmittedAMPDUCount.u.LowPart += (TxAggCnt5.field.AggSize12Count / 12);

		pRalinkCounters->TransmittedAMPDUCount.u.LowPart += (TxAggCnt6.field.AggSize13Count / 13);
		pRalinkCounters->TransmittedAMPDUCount.u.LowPart += (TxAggCnt6.field.AggSize14Count / 14);

		pRalinkCounters->TransmittedAMPDUCount.u.LowPart += (TxAggCnt7.field.AggSize15Count / 15);
		pRalinkCounters->TransmittedAMPDUCount.u.LowPart += (TxAggCnt7.field.AggSize16Count >> 4);	
	}
#endif /* STATS_COUNT_SUPPORT */			

#ifdef DBG_DIAGNOSE
	{
		RtmpDiagStruct	*pDiag;
		UCHAR			ArrayCurIdx, i;
		
		pDiag = &pAd->DiagStruct;
		ArrayCurIdx = pDiag->ArrayCurIdx;
		
		if (pDiag->inited == 0)
		{
			NdisZeroMemory(pDiag, sizeof(struct _RtmpDiagStrcut_));
			pDiag->ArrayStartIdx = pDiag->ArrayCurIdx = 0;
			pDiag->inited = 1;
		}
		else
		{
			/* Tx*/
			pDiag->TxFailCnt[ArrayCurIdx] = TxStaCnt0.field.TxFailCount;
			pDiag->TxAggCnt[ArrayCurIdx] = TxAggCnt.field.AggTxCount;
			pDiag->TxNonAggCnt[ArrayCurIdx] = TxAggCnt.field.NonAggTxCount;

			pDiag->TxAMPDUCnt[ArrayCurIdx][0] = TxAggCnt0.field.AggSize1Count;
			pDiag->TxAMPDUCnt[ArrayCurIdx][1] = TxAggCnt0.field.AggSize2Count;
			pDiag->TxAMPDUCnt[ArrayCurIdx][2] = TxAggCnt1.field.AggSize3Count;
			pDiag->TxAMPDUCnt[ArrayCurIdx][3] = TxAggCnt1.field.AggSize4Count;
			pDiag->TxAMPDUCnt[ArrayCurIdx][4] = TxAggCnt2.field.AggSize5Count;
			pDiag->TxAMPDUCnt[ArrayCurIdx][5] = TxAggCnt2.field.AggSize6Count;
			pDiag->TxAMPDUCnt[ArrayCurIdx][6] = TxAggCnt3.field.AggSize7Count;
			pDiag->TxAMPDUCnt[ArrayCurIdx][7] = TxAggCnt3.field.AggSize8Count;
			pDiag->TxAMPDUCnt[ArrayCurIdx][8] = TxAggCnt4.field.AggSize9Count;
			pDiag->TxAMPDUCnt[ArrayCurIdx][9] = TxAggCnt4.field.AggSize10Count;
			pDiag->TxAMPDUCnt[ArrayCurIdx][10] = TxAggCnt5.field.AggSize11Count;
			pDiag->TxAMPDUCnt[ArrayCurIdx][11] = TxAggCnt5.field.AggSize12Count;
			pDiag->TxAMPDUCnt[ArrayCurIdx][12] = TxAggCnt6.field.AggSize13Count;
			pDiag->TxAMPDUCnt[ArrayCurIdx][13] = TxAggCnt6.field.AggSize14Count;
			pDiag->TxAMPDUCnt[ArrayCurIdx][14] = TxAggCnt7.field.AggSize15Count;
			pDiag->TxAMPDUCnt[ArrayCurIdx][15] = TxAggCnt7.field.AggSize16Count;

			pDiag->RxCrcErrCnt[ArrayCurIdx] = RxStaCnt0.field.CrcErr;
			
			INC_RING_INDEX(pDiag->ArrayCurIdx,  DIAGNOSE_TIME);
			ArrayCurIdx = pDiag->ArrayCurIdx;
			for (i =0; i < 9; i++)
			{
				pDiag->TxDescCnt[ArrayCurIdx][i]= 0;
				pDiag->TxSWQueCnt[ArrayCurIdx][i] =0;
				pDiag->TxMcsCnt[ArrayCurIdx][i] = 0;
				pDiag->RxMcsCnt[ArrayCurIdx][i] = 0;
			}
			pDiag->TxDataCnt[ArrayCurIdx] = 0;
			pDiag->TxFailCnt[ArrayCurIdx] = 0;
			pDiag->RxDataCnt[ArrayCurIdx] = 0;
			pDiag->RxCrcErrCnt[ArrayCurIdx]  = 0;
/*			for (i = 9; i < 16; i++)*/
			for (i = 9; i < 24; i++) /* 3*3*/
			{
				pDiag->TxDescCnt[ArrayCurIdx][i] = 0;
				pDiag->TxMcsCnt[ArrayCurIdx][i] = 0;
				pDiag->RxMcsCnt[ArrayCurIdx][i] = 0;
}

			if (pDiag->ArrayCurIdx == pDiag->ArrayStartIdx)
				INC_RING_INDEX(pDiag->ArrayStartIdx,  DIAGNOSE_TIME);
		}
		
	}
#endif /* DBG_DIAGNOSE */


}

NDIS_STATUS NICLoadFirmware(
	IN PRTMP_ADAPTER pAd)
{
#ifdef RELEASE_EXCLUDE
	/*
		8051 Firmware -
			1. For PCI:
		        (1) Write SYS_CTRL bit16(HST_PM_SEL) to 1
		        (2) Write 8051 firmware to RAM.
		        (3) Write SYS_CTRL to 0.
		        (4) Write SYS_CTRL bit0(MCU_RESET) to 1 to do MCU HW reset.

			2. For USB:
		        (1)Get current firmware operation mode via VendorRequest(0x1, 0x11) command.
		        (2) Write SYS_CTRL bit7(MCU_READY) to 0.
		        (3) Write SYS_CTRL bit0(MCU_RESET) to 1 to do MCU reset to run 8051 on ROM.
		        (4) Check MCU ready via SYS_CTRL bit7(MCU_READY).
		        (5) Write 8051 firmware to RAM.
		        (6) Write MAC 0x7014 to 0xffffffff.
		        (7) Write MAC 0x701c to 0xffffffff.
		        (8) Change 8051 from ROM to RAM site via VendorRequest(0x01, 0x8) command.
	*/
#endif /* RELEASE_EXCLUDE */
	NDIS_STATUS	 status = NDIS_STATUS_SUCCESS;

	if (pAd->chipOps.loadFirmware)
		status = pAd->chipOps.loadFirmware(pAd);
	return status;
}


/*
	========================================================================
	
	Routine Description:
		erase 8051 firmware image in MAC ASIC

	Arguments:
		Adapter						Pointer to our adapter

	IRQL = PASSIVE_LEVEL
		
	========================================================================
*/
VOID NICEraseFirmware(
	IN PRTMP_ADAPTER pAd)
{
	if (pAd->chipOps.eraseFirmware)
		pAd->chipOps.eraseFirmware(pAd);
	
}


/*
	========================================================================
	
	Routine Description:
		Compare two memory block

	Arguments:
		pSrc1		Pointer to first memory address
		pSrc2		Pointer to second memory address
		
	Return Value:
		0:			memory is equal
		1:			pSrc1 memory is larger
		2:			pSrc2 memory is larger

	IRQL = DISPATCH_LEVEL
	
	Note:
		
	========================================================================
*/
ULONG	RTMPCompareMemory(
	IN	PVOID	pSrc1,
	IN	PVOID	pSrc2,
	IN	ULONG	Length)
{
	PUCHAR	pMem1;
	PUCHAR	pMem2;
	ULONG	Index = 0;

	pMem1 = (PUCHAR) pSrc1;
	pMem2 = (PUCHAR) pSrc2;

	for (Index = 0; Index < Length; Index++)
	{
		if (pMem1[Index] > pMem2[Index])
			return (1);
		else if (pMem1[Index] < pMem2[Index])
			return (2);
	}

	/* Equal*/
	return (0);
}


/*
	========================================================================
	
	Routine Description:
		Zero out memory block

	Arguments:
		pSrc1		Pointer to memory address
		Length		Size

	Return Value:
		None
		
	IRQL = PASSIVE_LEVEL
	IRQL = DISPATCH_LEVEL
	
	Note:
		
	========================================================================
*/
VOID	RTMPZeroMemory(
	IN	PVOID	pSrc,
	IN	ULONG	Length)
{
	PUCHAR	pMem;
	ULONG	Index = 0;

	pMem = (PUCHAR) pSrc;

	for (Index = 0; Index < Length; Index++)
	{
		pMem[Index] = 0x00;
	}
}


/*
	========================================================================
	
	Routine Description:
		Copy data from memory block 1 to memory block 2

	Arguments:
		pDest		Pointer to destination memory address
		pSrc		Pointer to source memory address
		Length		Copy size
		
	Return Value:
		None

	IRQL = PASSIVE_LEVEL
	IRQL = DISPATCH_LEVEL
	
	Note:
		
	========================================================================
*/
VOID RTMPMoveMemory(
	OUT	PVOID	pDest,
	IN	PVOID	pSrc,
	IN	ULONG	Length)
{
	PUCHAR	pMem1;
	PUCHAR	pMem2;
	UINT	Index;

	ASSERT((Length==0) || (pDest && pSrc));

	pMem1 = (PUCHAR) pDest;
	pMem2 = (PUCHAR) pSrc;

	for (Index = 0; Index < Length; Index++)
	{
		pMem1[Index] = pMem2[Index];
	}
}

VOID UserCfgExit(
	IN RTMP_ADAPTER *pAd)
{
#ifdef DOT11_N_SUPPORT
	BATableExit(pAd);
#endif /* DOT11_N_SUPPORT */

#ifdef WFA_WFD_SUPPORT
	pAd->WfdIeInBeaconLen = 0;
	if (pAd->pWfdIeInBeacon)
	{
		os_free_mem(NULL, pAd->pWfdIeInBeacon);
		pAd->pWfdIeInBeacon = NULL;
	}
	pAd->WfdIeInProbeReqLen= 0;
	if (pAd->pWfdIeInProbeReq)
	{
		os_free_mem(NULL, pAd->pWfdIeInProbeReq);
		pAd->pWfdIeInProbeReq = NULL;
	}
	pAd->WfdIeInProbeRspLen= 0;	
	if (pAd->pWfdIeInProbeRsp)
	{
		os_free_mem(NULL, pAd->pWfdIeInProbeRsp);
		pAd->pWfdIeInProbeRsp = NULL;
	}
	pAd->WfdIeInActionPktLen = 0;
	if (pAd->pWfdIeInActionPkt)
	{
		os_free_mem(NULL, pAd->pWfdIeInActionPkt);
		pAd->pWfdIeInActionPkt = NULL;
	}
	pAd->WfdIeInAssocReqLen= 0;
	if (pAd->pWfdIeInAssocReq)
	{
		os_free_mem(NULL, pAd->pWfdIeInAssocReq);
		pAd->pWfdIeInAssocReq = NULL;
	}
	pAd->WfdIeInAssocRspLen= 0;
	if (pAd->pWfdIeInAssocRsp)
	{
		os_free_mem(NULL, pAd->pWfdIeInAssocRsp);
		pAd->pWfdIeInAssocRsp = NULL;
	}
#endif /* WFA_WFD_SUPPORT */

	NdisFreeSpinLock(&pAd->MacTabLock);
}

/*
	========================================================================
	
	Routine Description:
		Initialize port configuration structure

	Arguments:
		Adapter						Pointer to our adapter

	Return Value:
		None

	IRQL = PASSIVE_LEVEL

	Note:
		
	========================================================================
*/
VOID UserCfgInit(RTMP_ADAPTER *pAd)
{
	UINT i;
#ifdef CONFIG_AP_SUPPORT
	UINT j;
#endif /* CONFIG_AP_SUPPORT */
/*	EDCA_PARM DefaultEdcaParm;*/
    UINT key_index, bss_index;
	UINT8 TXWISize = pAd->chipCap.TXWISize;

	DBGPRINT(RT_DEBUG_TRACE, ("--> UserCfgInit\n"));    
	 
	pAd->IndicateMediaState = NdisMediaStateDisconnected; 
	
	/*  part I. intialize common configuration*/
	pAd->CommonCfg.BasicRateBitmap = 0xF;
	pAd->CommonCfg.BasicRateBitmapOld = 0xF;
#ifdef CONFIG_MULTI_CHANNEL
	pAd->Multi_Channel_Enable = FALSE;
#endif /* CONFIG_MULTI_CHANNEL */

#ifdef RTMP_MAC_USB
	pAd->BulkOutReq = 0;
	
	pAd->BulkOutComplete = 0;
	pAd->BulkOutCompleteOther = 0;
	pAd->BulkOutCompleteCancel = 0;
	pAd->BulkInReq = 0;
	pAd->BulkInComplete = 0;
	pAd->BulkInCompleteFail = 0;

	/*pAd->QuickTimerP = 100;*/
	/*pAd->TurnAggrBulkInCount = 0;*/
	pAd->bUsbTxBulkAggre = 0;

#ifdef LED_CONTROL_SUPPORT
	/* init as unsed value to ensure driver will set to MCU once.*/
	pAd->LedCntl.LedIndicatorStrength = 0xFF;
#endif /* LED_CONTROL_SUPPORT */

	pAd->CommonCfg.MaxPktOneTxBulk = 2;
	pAd->CommonCfg.TxBulkFactor = 1;
	pAd->CommonCfg.RxBulkFactor =1;

	pAd->CommonCfg.TxPower = 100; /*mW*/

	NdisZeroMemory(&pAd->CommonCfg.IOTestParm, sizeof(pAd->CommonCfg.IOTestParm));
#ifdef CONFIG_STA_SUPPORT
	pAd->CountDowntoPsm = 0;
	pAd->StaCfg.Connectinfoflag = FALSE;
#endif /* CONFIG_STA_SUPPORT */

#endif /* RTMP_MAC_USB */

	for(key_index=0; key_index<SHARE_KEY_NUM; key_index++)
	{
		for(bss_index = 0; bss_index < MAX_MBSSID_NUM(pAd) + MAX_P2P_NUM; bss_index++)
		{
			pAd->SharedKey[bss_index][key_index].KeyLen = 0;
			pAd->SharedKey[bss_index][key_index].CipherAlg = CIPHER_NONE;
		}
	}

	pAd->bLocalAdminMAC = FALSE;
	pAd->EepromAccess = FALSE;
	
	pAd->Antenna.word = 0; 
	pAd->CommonCfg.BBPCurrentBW = BW_20;

#ifdef RTMP_MAC_PCI
#ifdef LED_CONTROL_SUPPORT
	pAd->LedCntl.LedIndicatorStrength = 0;
#endif /* LED_CONTROL_SUPPORT */
#ifdef CONFIG_STA_SUPPORT
	pAd->RLnkCtrlOffset = 0;
	pAd->HostLnkCtrlOffset = 0;
#endif /* CONFIG_STA_SUPPORT */
#endif /* RTMP_MAC_PCI */

	pAd->bAutoTxAgcA = FALSE;			/* Default is OFF*/
	pAd->bAutoTxAgcG = FALSE;			/* Default is OFF*/
	
#if defined(RTMP_INTERNAL_TX_ALC) || defined(RTMP_TEMPERATURE_COMPENSATION)
	pAd->TxPowerCtrl.bInternalTxALC = FALSE; /* Off by default */
	pAd->TxPowerCtrl.idxTxPowerTable = 0;
	pAd->TxPowerCtrl.idxTxPowerTable2 = 0;
#ifdef RTMP_TEMPERATURE_COMPENSATION
	pAd->TxPowerCtrl.LookupTableIndex = 0;
#endif /* RTMP_TEMPERATURE_COMPENSATION */
#endif /* RTMP_INTERNAL_TX_ALC || RTMP_TEMPERATURE_COMPENSATION */

	pAd->RfIcType = RFIC_2820;

	/* Init timer for reset complete event*/
	pAd->CommonCfg.CentralChannel = 1;
	pAd->bForcePrintTX = FALSE;
	pAd->bForcePrintRX = FALSE;
	pAd->bStaFifoTest = FALSE;
	pAd->bProtectionTest = FALSE;
	pAd->bHCCATest = FALSE;
	pAd->bGenOneHCCA = FALSE;
	pAd->CommonCfg.Dsifs = 10;      /* in units of usec */
	pAd->CommonCfg.TxPower = 100; /* mW*/
	pAd->CommonCfg.TxPowerPercentage = 0xffffffff; /* AUTO*/
	pAd->CommonCfg.TxPowerDefault = 0xffffffff; /* AUTO*/
	pAd->CommonCfg.TxPreamble = Rt802_11PreambleAuto; /* use Long preamble on TX by defaut*/
	pAd->CommonCfg.bUseZeroToDisableFragment = FALSE;
	pAd->CommonCfg.RtsThreshold = 2347;
	pAd->CommonCfg.FragmentThreshold = 2346;
	pAd->CommonCfg.UseBGProtection = 0;    /* 0: AUTO*/
	pAd->CommonCfg.bEnableTxBurst = TRUE; /* 0;    	*/
	pAd->CommonCfg.PhyMode = 0xff;     /* unknown*/
	pAd->CommonCfg.SavedPhyMode = pAd->CommonCfg.PhyMode;
	
#ifdef RT3052
#ifdef RELEASE_EXCLUDE
/*
  CID and CN(chip name) is used to check the chip version of 2880 for SoC
*/
#endif /* RELEASE_EXCLUDE */
#ifdef RTMP_RBUS_SUPPORT
	if (pAd->infType == RTMP_DEV_INF_RBUS)
	{
		RTMP_SYS_IO_READ32(0xb000000c, &pAd->CommonCfg.CID);
		RTMP_SYS_IO_READ32(0xb0000000, &pAd->CommonCfg.CN);
	}
#endif /* RTMP_RBUS_SUPPORT */
#endif /* RT3052 */

#ifdef CONFIG_AP_SUPPORT
#ifdef RT2880
	RTMP_SYS_IO_READ32(0xa030000c, &pAd->CommonCfg.CID);
#endif
#endif /* CONFIG_AP_SUPPORT */

#ifdef CARRIER_DETECTION_SUPPORT
	pAd->CommonCfg.CarrierDetect.delta = CARRIER_DETECT_DELTA;
	pAd->CommonCfg.CarrierDetect.div_flag = CARRIER_DETECT_DIV_FLAG;
	pAd->CommonCfg.CarrierDetect.criteria = CARRIER_DETECT_CRITIRIA;
	pAd->CommonCfg.CarrierDetect.threshold = CARRIER_DETECT_THRESHOLD;
	pAd->CommonCfg.CarrierDetect.recheck1 = CARRIER_DETECT_RECHECK_TIME;
	pAd->CommonCfg.CarrierDetect.CarrierGoneThreshold = CARRIER_GONE_TRESHOLD;
	pAd->CommonCfg.CarrierDetect.VGA_Mask = CARRIER_DETECT_DEFAULT_MASK;
	pAd->CommonCfg.CarrierDetect.Packet_End_Mask = CARRIER_DETECT_DEFAULT_MASK;
	pAd->CommonCfg.CarrierDetect.Rx_PE_Mask = CARRIER_DETECT_DEFAULT_MASK;
#endif /* CARRIER_DETECTION_SUPPORT */

#ifdef DFS_SUPPORT
	pAd->CommonCfg.RadarDetect.bDfsInit = FALSE;
#endif /* DFS_SUPPORT */

	pAd->Dot11_H.ChMovingTime = 65;

#ifdef UAPSD_SUPPORT
#ifdef CONFIG_AP_SUPPORT
{
	UINT32 IdMbss;

	for(IdMbss=0; IdMbss<HW_BEACON_MAX_NUM; IdMbss++)
		UAPSD_INFO_INIT(&pAd->ApCfg.MBSSID[IdMbss].UapsdInfo);
}
#endif /* CONFIG_AP_SUPPORT */
#ifdef CONFIG_STA_SUPPORT
	pAd->StaCfg.UapsdInfo.bAPSDCapable = FALSE;
#endif /* CONFIG_STA_SUPPORT */
#endif /* UAPSD_SUPPORT */
	pAd->CommonCfg.bNeedSendTriggerFrame = FALSE;
	pAd->CommonCfg.TriggerTimerCount = 0;
	pAd->CommonCfg.bAPSDForcePowerSave = FALSE;
	/*pAd->CommonCfg.bCountryFlag = FALSE;*/
	pAd->CommonCfg.TxStream = 0;
	pAd->CommonCfg.RxStream = 0;

	NdisZeroMemory(&pAd->BeaconTxWI, TXWISize);

#ifdef DOT11_N_SUPPORT
	NdisZeroMemory(&pAd->CommonCfg.HtCapability, sizeof(pAd->CommonCfg.HtCapability));
	pAd->HTCEnable = FALSE;
	pAd->bBroadComHT = FALSE;
	pAd->CommonCfg.bRdg = FALSE;
	
#ifdef DOT11N_DRAFT3
	pAd->CommonCfg.Dot11OBssScanPassiveDwell = dot11OBSSScanPassiveDwell;	/* Unit : TU. 5~1000*/
	pAd->CommonCfg.Dot11OBssScanActiveDwell = dot11OBSSScanActiveDwell;	/* Unit : TU. 10~1000*/
	pAd->CommonCfg.Dot11BssWidthTriggerScanInt = dot11BSSWidthTriggerScanInterval;	/* Unit : Second	*/
	pAd->CommonCfg.Dot11OBssScanPassiveTotalPerChannel = dot11OBSSScanPassiveTotalPerChannel;	/* Unit : TU. 200~10000*/
	pAd->CommonCfg.Dot11OBssScanActiveTotalPerChannel = dot11OBSSScanActiveTotalPerChannel;	/* Unit : TU. 20~10000*/
	pAd->CommonCfg.Dot11BssWidthChanTranDelayFactor = dot11BSSWidthChannelTransactionDelayFactor;
	pAd->CommonCfg.Dot11OBssScanActivityThre = dot11BSSScanActivityThreshold;	/* Unit : percentage*/
	pAd->CommonCfg.Dot11BssWidthChanTranDelay = (pAd->CommonCfg.Dot11BssWidthTriggerScanInt * pAd->CommonCfg.Dot11BssWidthChanTranDelayFactor);

	pAd->CommonCfg.bBssCoexEnable = TRUE; /* by default, we enable this feature, you can disable it via the profile or ioctl command*/
	pAd->CommonCfg.BssCoexApCntThr = 0;
	pAd->CommonCfg.Bss2040NeedFallBack = 0;
#endif  /* DOT11N_DRAFT3 */

	NdisZeroMemory(&pAd->CommonCfg.AddHTInfo, sizeof(pAd->CommonCfg.AddHTInfo));
	pAd->CommonCfg.BACapability.field.MMPSmode = MMPS_ENABLE;
	pAd->CommonCfg.BACapability.field.MpduDensity = 0;
	pAd->CommonCfg.BACapability.field.Policy = IMMED_BA;
	pAd->CommonCfg.BACapability.field.RxBAWinLimit = 64; /*32;*/
	pAd->CommonCfg.BACapability.field.TxBAWinLimit = 64; /*32;*/
	DBGPRINT(RT_DEBUG_TRACE, ("--> UserCfgInit. BACapability = 0x%x\n", pAd->CommonCfg.BACapability.word));    

	pAd->CommonCfg.BACapability.field.AutoBA = FALSE;	
	BATableInit(pAd, &pAd->BATable);

	pAd->CommonCfg.bExtChannelSwitchAnnouncement = 1;
	pAd->CommonCfg.bHTProtect = 1;
	pAd->CommonCfg.bMIMOPSEnable = TRUE;
#ifdef GREENAP_SUPPORT
	pAd->ApCfg.bGreenAPEnable=FALSE;
	pAd->ApCfg.bGreenAPActive = FALSE;
	pAd->ApCfg.GreenAPLevel= GREENAP_WITHOUT_ANY_STAS_CONNECT;
#endif /* GREENAP_SUPPORT */
	pAd->CommonCfg.bBADecline = FALSE;
	pAd->CommonCfg.bDisableReordering = FALSE;

	if (pAd->MACVersion == 0x28720200)
		pAd->CommonCfg.TxBASize = 13; /*by Jerry recommend*/
	else
		pAd->CommonCfg.TxBASize = 7;

	pAd->CommonCfg.REGBACapability.word = pAd->CommonCfg.BACapability.word;
#endif /* DOT11_N_SUPPORT */

	/*pAd->CommonCfg.HTPhyMode.field.BW = BW_20;*/
	/*pAd->CommonCfg.HTPhyMode.field.MCS = MCS_AUTO;*/
	/*pAd->CommonCfg.HTPhyMode.field.ShortGI = GI_800;*/
	/*pAd->CommonCfg.HTPhyMode.field.STBC = STBC_NONE;*/
	pAd->CommonCfg.TxRate = RATE_6;
	
	pAd->CommonCfg.MlmeTransmit.field.MCS = MCS_RATE_6;
	pAd->CommonCfg.MlmeTransmit.field.BW = BW_20;
	pAd->CommonCfg.MlmeTransmit.field.MODE = MODE_OFDM;

	pAd->CommonCfg.BeaconPeriod = 100;     /* in mSec*/

#ifdef STREAM_MODE_SUPPORT
	if (pAd->chipCap.FlgHwStreamMode)
	{
		pAd->CommonCfg.StreamMode = 3;
		pAd->CommonCfg.StreamModeMCS = 0x0B0B;
	}
#endif /* STREAM_MODE_SUPPORT */

#ifdef TXBF_SUPPORT
	pAd->CommonCfg.ETxBfNoncompress = 0;
	pAd->CommonCfg.ETxBfIncapable = 0;
#endif /* TXBF_SUPPORT */

#ifdef NEW_RATE_ADAPT_SUPPORT
	pAd->CommonCfg.lowTrafficThrd = 2;
	pAd->CommonCfg.TrainUpRule = 2; // 1;
	pAd->CommonCfg.TrainUpRuleRSSI = -70; // 0;
	pAd->CommonCfg.TrainUpLowThrd = 90;
	pAd->CommonCfg.TrainUpHighThrd = 110;
#endif /* NEW_RATE_ADAPT_SUPPORT */

#if defined(RT2883) || defined(RT3883)
	if (IS_RT2883(pAd) || IS_RT3883(pAd))
	{
#ifdef PRE_ANT_SWITCH
		pAd->CommonCfg.PreAntSwitch = 1;
		pAd->CommonCfg.PreAntSwitchRSSI = -76;
		pAd->CommonCfg.PreAntSwitchTimeout = 0;
#endif /* PRE_ANT_SWITCH */
		pAd->CommonCfg.PhyRateLimit = 0;
		pAd->CommonCfg.FixedRate = -1;		// Disable
	}
#endif // defined (RT2883) || defined (RT3883) //


#ifdef CFO_TRACK
#ifdef RT3883
	if (IS_RT3883(pAd))
		pAd->CommonCfg.CFOTrack = 8;		// No tracking
#endif /* RT3883 */
#endif /* CFO_TRACK */

#ifdef DBG_CTRL_SUPPORT
	pAd->CommonCfg.DebugFlags = 0;
#endif /* DBG_CTRL_SUPPORT */

#ifdef WAPI_SUPPORT
	pAd->CommonCfg.wapi_usk_rekey_method = REKEY_METHOD_DISABLE;
	pAd->CommonCfg.wapi_msk_rekey_method = REKEY_METHOD_DISABLE;
	pAd->CommonCfg.wapi_msk_rekey_cnt = 0;
#endif /* WAPI_SUPPORT */

#ifdef MCAST_RATE_SPECIFIC
	pAd->CommonCfg.MCastPhyMode.word
	= pAd->MacTab.Content[MCAST_WCID].HTPhyMode.word;
#endif /* MCAST_RATE_SPECIFIC */

	/* WFA policy - disallow TH rate in WEP or TKIP cipher */
	pAd->CommonCfg.HT_DisallowTKIP = TRUE;

	/* Frequency for rate adaptation */
	pAd->ra_interval = DEF_RA_TIME_INTRVAL;
	pAd->ra_fast_interval = DEF_QUICK_RA_TIME_INTERVAL;

#ifdef AGS_SUPPORT
	if (pAd->rateAlg == RATE_ALG_AGS)
		pAd->ra_fast_interval = AGS_QUICK_RA_TIME_INTERVAL;
#endif /* AGS_SUPPORT */

	/* Tx Sw queue length setting */
	pAd->TxSwQMaxLen = MAX_PACKETS_IN_QUEUE;
	
	pAd->CommonCfg.bRalinkBurstMode = FALSE;

#ifdef CONFIG_STA_SUPPORT
	/* part II. intialize STA specific configuration*/
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	{
		RX_FILTER_SET_FLAG(pAd, fRX_FILTER_ACCEPT_DIRECT);
		RX_FILTER_CLEAR_FLAG(pAd, fRX_FILTER_ACCEPT_MULTICAST);
		RX_FILTER_SET_FLAG(pAd, fRX_FILTER_ACCEPT_BROADCAST);
		RX_FILTER_SET_FLAG(pAd, fRX_FILTER_ACCEPT_ALL_MULTICAST);

		pAd->StaCfg.Psm = PWR_ACTIVE;

		pAd->StaCfg.PairCipher = Ndis802_11EncryptionDisabled;
		pAd->StaCfg.GroupCipher = Ndis802_11EncryptionDisabled;
		pAd->StaCfg.bMixCipher = FALSE;	
		pAd->StaCfg.DefaultKeyId = 0;

		/* 802.1x port control*/
		pAd->StaCfg.PrivacyFilter = Ndis802_11PrivFilter8021xWEP;
		pAd->StaCfg.PortSecured = WPA_802_1X_PORT_NOT_SECURED;
		pAd->StaCfg.LastMicErrorTime = 0;
		pAd->StaCfg.MicErrCnt        = 0;
		pAd->StaCfg.bBlockAssoc      = FALSE;
		pAd->StaCfg.WpaState         = SS_NOTUSE;

		pAd->CommonCfg.NdisRadioStateOff = FALSE;		/* New to support microsoft disable radio with OID command*/

		pAd->StaCfg.RssiTrigger = 0;
		NdisZeroMemory(&pAd->StaCfg.RssiSample, sizeof(RSSI_SAMPLE));
		pAd->StaCfg.RssiTriggerMode = RSSI_TRIGGERED_UPON_BELOW_THRESHOLD;
		pAd->StaCfg.AtimWin = 0;
		pAd->StaCfg.DefaultListenCount = 3;/*default listen count;*/
#ifdef DOT11Z_TDLS_SUPPORT
		pAd->StaCfg.DefaultListenCount = 1;
#endif /* DOT11Z_TDLS_SUPPORT */
		pAd->StaCfg.BssType = BSS_INFRA;  /* BSS_INFRA or BSS_ADHOC or BSS_MONITOR*/
		pAd->StaCfg.bSkipAutoScanConn = FALSE;
		OPSTATUS_CLEAR_FLAG(pAd, fOP_STATUS_DOZE);
		OPSTATUS_CLEAR_FLAG(pAd, fOP_STATUS_WAKEUP_NOW);

		pAd->StaCfg.bAutoTxRateSwitch = TRUE;
		pAd->StaCfg.DesiredTransmitSetting.field.MCS = MCS_AUTO;
		pAd->StaCfg.bAutoConnectIfNoSSID = FALSE;
#ifdef RTMP_FREQ_CALIBRATION_SUPPORT
		pAd->StaCfg.AdaptiveFreq = TRUE; /* Todo: iwpriv and profile support. */
#endif /* RTMP_FREQ_CALIBRATION_SUPPORT */
	}

#ifdef EXT_BUILD_CHANNEL_LIST
	pAd->StaCfg.IEEE80211dClientMode = Rt802_11_D_None;
#endif /* EXT_BUILD_CHANNEL_LIST */

#ifdef RELEASE_EXCLUDE
/*
	3090F could not execute any MCU commands after executing SLEEP comands exceptiong
	RADIO_OFF and WakeUp or the chips will crash. Therefore, We use brt30xxBanMcuCmd to block MCU commands.
*/
#endif /* RELEASE_EXCLUDE */
#ifdef RTMP_MAC_PCI

	pAd->brt30xxBanMcuCmd = FALSE;
	pAd->StaCfg.PSControl.field.EnableNewPS=FALSE;

#ifdef PCIE_PS_SUPPORT
	pAd->StaCfg.PSControl.field.EnableNewPS=TRUE;
	pAd->b3090ESpecialChip = FALSE;
	/*The value of PowerMode could be 1 or 3. Level 3 could save more power than Level 1. */
	pAd->StaCfg.PSControl.field.rt30xxPowerMode=3;
	pAd->StaCfg.PSControl.field.rt30xxForceASPMTest=0;
	pAd->StaCfg.PSControl.field.rt30xxFollowHostASPM=1;

	if (IS_SUPPORT_PCIE_PS_L3(pAd))
	{
		pAd->chipCap.HW_PCIE_PS_L3_ENABLE=TRUE;
		DBGPRINT(RT_DEBUG_TRACE, ("Support PCIe PS3 \n"));
	}
#endif /* PCIE_PS_SUPPORT */
#endif /* RTMP_MAC_PCI */
#endif /* CONFIG_STA_SUPPORT */

	/* global variables mXXXX used in MAC protocol state machines*/
	OPSTATUS_SET_FLAG(pAd, fOP_STATUS_RECEIVE_DTIM);
	OPSTATUS_CLEAR_FLAG(pAd, fOP_STATUS_ADHOC_ON);
	OPSTATUS_CLEAR_FLAG(pAd, fOP_STATUS_INFRA_ON);

	/* PHY specification*/
	pAd->CommonCfg.PhyMode = (WMODE_B | WMODE_G);		/* default PHY mode*/
	OPSTATUS_CLEAR_FLAG(pAd, fOP_STATUS_SHORT_PREAMBLE_INUSED);  /* CCK use LONG preamble*/

#ifdef CONFIG_STA_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	{
		/* user desired power mode*/
		pAd->StaCfg.WindowsPowerMode = Ndis802_11PowerModeCAM;
		pAd->StaCfg.WindowsBatteryPowerMode = Ndis802_11PowerModeCAM;
		pAd->StaCfg.bWindowsACCAMEnable = FALSE;

		pAd->StaCfg.bHwRadio  = TRUE; /* Default Hardware Radio status is On*/
		pAd->StaCfg.bSwRadio  = TRUE; /* Default Software Radio status is On*/
		pAd->StaCfg.bRadio    = TRUE; /* bHwRadio && bSwRadio*/
		pAd->StaCfg.bHardwareRadio = FALSE;		/* Default is OFF*/
		pAd->StaCfg.bShowHiddenSSID = FALSE;		/* Default no show*/

		/* Nitro mode control*/
#ifdef NATIVE_WPA_SUPPLICANT_SUPPORT
		pAd->StaCfg.bAutoReconnect = FALSE;
#else
		pAd->StaCfg.bAutoReconnect = TRUE;
#endif /* NATIVE_WPA_SUPPLICANT_SUPPORT */

		pAd->StaCfg.LastScanTime = 0;
		
		NdisZeroMemory(pAd->nickname, IW_ESSID_MAX_SIZE+1);
#ifdef PROFILE_STORE
		pAd->bWriteDat = FALSE;
#endif /* PROFILE_STORE */
#ifdef WPA_SUPPLICANT_SUPPORT
		pAd->StaCfg.IEEE8021X = FALSE;
		pAd->StaCfg.IEEE8021x_required_keys = FALSE;
		pAd->StaCfg.WpaSupplicantUP = WPA_SUPPLICANT_DISABLE;
		pAd->StaCfg.bRSN_IE_FromWpaSupplicant = FALSE;
#ifdef NATIVE_WPA_SUPPLICANT_SUPPORT
		pAd->StaCfg.WpaSupplicantUP = WPA_SUPPLICANT_ENABLE;
#ifdef PROFILE_STORE
		pAd->bWriteDat = TRUE;
#endif /* PROFILE_STORE */
#endif /* NATIVE_WPA_SUPPLICANT_SUPPORT */
		pAd->StaCfg.bLostAp = FALSE;
		pAd->StaCfg.pWpsProbeReqIe = NULL;
		pAd->StaCfg.WpsProbeReqIeLen = 0;
		pAd->StaCfg.pWpaAssocIe = NULL;
		pAd->StaCfg.WpaAssocIeLen = 0;
		pAd->StaCfg.WpaSupplicantScanCount = 0;
#endif /* WPA_SUPPLICANT_SUPPORT */

#ifdef WSC_STA_SUPPORT
		{
			INT					idx;
			PWSC_CTRL 			pWscControl;
#ifdef STA_EASY_CONFIG_SETUP
			PEASY_CONFIG_INFO	pEasyConfig;
#endif /* STA_EASY_CONFIG_SETUP */
#ifdef WSC_V2_SUPPORT
			PWSC_V2_INFO	pWscV2Info;
#endif /* WSC_V2_SUPPORT */

			/*
				WscControl cannot be zero here, because WscControl timers are initial in MLME Initialize 
				and MLME Initialize is called before UserCfgInit.

			*/
			pWscControl = &pAd->StaCfg.WscControl;
			pWscControl->WscConfMode = WSC_DISABLE;
			pWscControl->WscMode = WSC_PIN_MODE;
			pWscControl->WscConfStatus = WSC_SCSTATE_UNCONFIGURED;
#ifdef WSC_V2_SUPPORT
			pWscControl->WscConfigMethods= 0x238C;
#else
			pWscControl->WscConfigMethods= 0x008C;
#endif /* WSC_V2_SUPPORT */
#ifdef P2P_SUPPORT
			pWscControl->WscConfigMethods |= 0x0100;
#endif /* P2P_SUPPORT */
			pWscControl->WscState = WSC_STATE_OFF;
			pWscControl->WscStatus = STATUS_WSC_NOTUSED;
			pWscControl->WscPinCode = 0;
			pWscControl->WscLastPinFromEnrollee = 0;
			pWscControl->WscEnrollee4digitPinCode = FALSE;
			pWscControl->WscEnrolleePinCode = 0;
			pWscControl->WscSelReg = 0;
			NdisZeroMemory(&pAd->StaCfg.WscControl.RegData, sizeof(WSC_REG_DATA));
			NdisZeroMemory(&pWscControl->WscProfile, sizeof(WSC_PROFILE));
			pWscControl->WscUseUPnP = 0;
			pWscControl->WscEnAssociateIE = TRUE;
			pWscControl->WscEnProbeReqIE = TRUE;
			pWscControl->RegData.ReComputePke = 1;
			pWscControl->lastId = 1;
			pWscControl->EntryIfIdx = BSS0;
			pWscControl->pAd = pAd;
#ifdef DPA_T
			pWscControl->WscDriverAutoConnect = 0x00;	// 2009-11-14 changed.
#else /* DPA_T */
			pWscControl->WscDriverAutoConnect = 0x02;
#endif /* !DPA_T */
			pAd->WriteWscCfgToDatFile = 0xFF;
			pWscControl->WscRejectSamePinFromEnrollee = FALSE;
			pWscControl->WpsApBand = PREFERRED_WPS_AP_PHY_TYPE_AUTO_SELECTION;
			pWscControl->bCheckMultiByte = FALSE;
			pWscControl->bWscAutoTigeer = FALSE;
			/* Enrollee Nonce, first generate and save to Wsc Control Block*/
			for (idx = 0; idx < 16; idx++)
			{
				pWscControl->RegData.SelfNonce[idx] = RandomByte(pAd);
			}
			pWscControl->WscRxBufLen = 0;
			pWscControl->pWscRxBuf = NULL;
			os_alloc_mem(pAd, &pWscControl->pWscRxBuf, MGMT_DMA_BUFFER_SIZE);
			if (pWscControl->pWscRxBuf)
				NdisZeroMemory(pWscControl->pWscRxBuf, MGMT_DMA_BUFFER_SIZE);
			pWscControl->WscTxBufLen = 0;
			pWscControl->pWscTxBuf = NULL;
			os_alloc_mem(pAd, &pWscControl->pWscTxBuf, MGMT_DMA_BUFFER_SIZE);
			if (pWscControl->pWscTxBuf)
				NdisZeroMemory(pWscControl->pWscTxBuf, MGMT_DMA_BUFFER_SIZE);
			pWscControl->bWscFragment = FALSE;
			pWscControl->WscFragSize = 128;
			initList(&pWscControl->WscPeerList);
			NdisAllocateSpinLock(pAd, &pWscControl->WscPeerListSemLock);
#ifdef STA_EASY_CONFIG_SETUP
			pEasyConfig = &pAd->StaCfg.EasyConfigInfo;
			AutoProvisionGenWpsPTK(pAd, BSS0);
			pEasyConfig->ModuleType = MODULE_UNKNOW;
			pEasyConfig->bRaAutoWpsAp = FALSE;
			pEasyConfig->bDoAutoWps = FALSE;
			pEasyConfig->RssiThreshold = -50;
			pEasyConfig->bEnable = TRUE;
			pEasyConfig->bChangeMode = FALSE;
#ifdef WAC_SUPPORT
			pEasyConfig->bEnableWAC = TRUE;
			pEasyConfig->DoAutoWAC = 0xFF;
			pEasyConfig->pVendorInfoForProbeReq = NULL;
#endif /* WAC_SUPPORT */
#endif /* STA_EASY_CONFIG_SETUP */

#ifdef WSC_V2_SUPPORT
			pWscV2Info = &pWscControl->WscV2Info;
			pWscV2Info->bWpsEnable = TRUE;
			pWscV2Info->ExtraTlv.TlvLen = 0;
			pWscV2Info->ExtraTlv.TlvTag = 0;
			pWscV2Info->ExtraTlv.pTlvData = NULL;
			pWscV2Info->ExtraTlv.TlvType = TLV_ASCII;
			pWscV2Info->bEnableWpsV2 = TRUE;
			pWscV2Info->bForceSetAP = FALSE;
#endif /* WSC_V2_SUPPORT */

#ifdef DPA_T
			for (idx = 0; idx < 8; idx++)
			{
				pWscControl->WpsVendorExt[idx].Length = 0;
				pWscControl->WpsVendorExt[idx].pData = NULL;
			}
			pAd->StaCfg.bPriorityCtrl = FALSE;
			pAd->StaCfg.WscPbcExtraScanCount = 0;
#endif /* DPA_T */
		}
#ifdef IWSC_SUPPORT
		IWSC_Init(pAd);
#endif /* IWSC_SUPPORT */
#endif /* WSC_STA_SUPPORT */
		NdisZeroMemory(pAd->StaCfg.ReplayCounter, 8);

#ifdef DOT11R_FT_SUPPORT
		NdisZeroMemory(&pAd->StaCfg.Dot11RCommInfo, sizeof(DOT11R_CMN_STRUC));
#endif /* DOT11R_FT_SUPPORT */

		pAd->StaCfg.bAutoConnectByBssid = FALSE;
		pAd->StaCfg.BeaconLostTime = BEACON_LOST_TIME;
		NdisZeroMemory(pAd->StaCfg.WpaPassPhrase, 64);    
		pAd->StaCfg.WpaPassPhraseLen = 0;
		pAd->StaCfg.bAutoRoaming = FALSE;
		pAd->StaCfg.bForceTxBurst = FALSE;
		pAd->StaCfg.bNotFirstScan = FALSE;
		pAd->StaCfg.bImprovedScan = FALSE;
#ifdef DOT11_N_SUPPORT
		pAd->StaCfg.bAdhocN = TRUE;
#endif /* DOT11_N_SUPPORT */
		pAd->StaCfg.bFastConnect = FALSE;
		pAd->StaCfg.bAdhocCreator = FALSE;
#ifdef WIDI_SUPPORT
		pAd->StaCfg.bWIDI = TRUE;
		pAd->MlmeAux.OldChannel = 0;
#ifdef WFA_WFD_SUPPORT
		pAd->pWfdIeInBeacon = NULL;
		pAd->WfdIeInBeaconLen = 0;
		pAd->pWfdIeInProbeReq = NULL;
		pAd->WfdIeInProbeReqLen = 0;
		pAd->pWfdIeInProbeRsp = NULL;
		pAd->WfdIeInProbeRspLen = 0;
		pAd->pWfdIeInActionPkt = NULL;
		pAd->WfdIeInActionPktLen = 0;		

		pAd->pWfdIeInAssocReq = NULL;
		pAd->WfdIeInAssocReqLen = 0;
		pAd->pWfdIeInAssocRsp = NULL;
		pAd->WfdIeInAssocRspLen = 0;
		pAd->EnterpriseEnabled = 0;
		pAd->ToggleEnabled = 0;
#endif /* WFA_WFD_SUPPORT */
#endif /* WIDI_SUPPORT */
	}
#endif /* CONFIG_STA_SUPPORT */

	/* Default for extra information is not valid*/
	pAd->ExtraInfo = EXTRA_INFO_CLEAR;
	
	/* Default Config change flag*/
	pAd->bConfigChanged = FALSE;

	/* */
	/* part III. AP configurations*/
	
#ifdef CONFIG_AP_SUPPORT
#ifndef P2P_APCLI_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_AP(pAd)
#endif /* P2P_APCLI_SUPPORT */
	{
		/* Set MBSS Default Configurations*/
		pAd->ApCfg.BssidNum = MAX_MBSSID_NUM(pAd);
		for(j = BSS0; j < pAd->ApCfg.BssidNum; j++)
		{
			pAd->ApCfg.MBSSID[j].AuthMode = Ndis802_11AuthModeOpen;
			pAd->ApCfg.MBSSID[j].WepStatus = Ndis802_11EncryptionDisabled;
			pAd->ApCfg.MBSSID[j].GroupKeyWepStatus = Ndis802_11EncryptionDisabled;
			pAd->ApCfg.MBSSID[j].DefaultKeyId = 0;
			pAd->ApCfg.MBSSID[j].WpaMixPairCipher = MIX_CIPHER_NOTUSE;
			pAd->ApCfg.MBSSID[j].RekeyCountDown = 0;	/* it's used for WPA rekey */

#ifdef DOT1X_SUPPORT
			pAd->ApCfg.MBSSID[j].IEEE8021X = FALSE;
			pAd->ApCfg.MBSSID[j].PreAuth = FALSE;

			/* PMK cache setting*/
			pAd->ApCfg.MBSSID[j].PMKCachePeriod = (10 * 60 * OS_HZ); /* unit : tick(default: 10 minute)*/
			NdisZeroMemory(&pAd->ApCfg.MBSSID[j].PMKIDCache, sizeof(NDIS_AP_802_11_PMKID));

			/* dot1x related per BSS */
			pAd->ApCfg.MBSSID[j].radius_srv_num = 0;
			pAd->ApCfg.MBSSID[j].NasIdLen = 0;
#endif /* DOT1X_SUPPORT */

			/* VLAN related */
        		pAd->ApCfg.MBSSID[j].VLAN_VID = 0;

			/* Default MCS as AUTO*/
			pAd->ApCfg.MBSSID[j].bAutoTxRateSwitch = TRUE;
			pAd->ApCfg.MBSSID[j].DesiredTransmitSetting.field.MCS = MCS_AUTO;

			/* Default is zero. It means no limit.*/
			pAd->ApCfg.MBSSID[j].MaxStaNum = 0;
			pAd->ApCfg.MBSSID[j].StaCount = 0;
			
#ifdef WSC_AP_SUPPORT
			pAd->ApCfg.MBSSID[j].WscSecurityMode = 0xff;
			{
				PWSC_CTRL pWscControl;
				INT idx;
#ifdef WSC_V2_SUPPORT
				PWSC_V2_INFO	pWscV2Info;
#endif /* WSC_V2_SUPPORT */
				/*
					WscControl cannot be zero here, because WscControl timers are initial in MLME Initialize 
					and MLME Initialize is called before UserCfgInit.

				*/
				pWscControl = &pAd->ApCfg.MBSSID[j].WscControl;
				NdisZeroMemory(&pWscControl->RegData, sizeof(WSC_REG_DATA));
				NdisZeroMemory(&pAd->CommonCfg.WscStaPbcProbeInfo, sizeof(WSC_STA_PBC_PROBE_INFO));
				pWscControl->WscMode = 1;
				pWscControl->WscConfStatus = 1;
#ifdef WSC_V2_SUPPORT
				pWscControl->WscConfigMethods= 0x238C;
#else
				pWscControl->WscConfigMethods= 0x0084;
#endif /* WSC_V2_SUPPORT */
#ifdef P2P_SUPPORT
				pWscControl->WscConfigMethods |= 0x0108;
#endif /* P2P_SUPPORT */
				pWscControl->RegData.ReComputePke = 1;
				pWscControl->lastId = 1;
				/* pWscControl->EntryIfIdx = (MIN_NET_DEVICE_FOR_MBSSID | j); */
				pWscControl->pAd = pAd;
				pWscControl->WscRejectSamePinFromEnrollee = FALSE;
				pAd->CommonCfg.WscPBCOverlap = FALSE;
#ifdef P2P_SUPPORT
				/*
					Set defaule value of WscConfMode to be (WSC_REGISTRAR | WSC_ENROLLEE) for WiFi P2P.
				*/
				pWscControl->WscConfMode = (WSC_REGISTRAR | WSC_ENROLLEE);
#else /* P2P_SUPPORT */
				pWscControl->WscConfMode = 0;
#endif /* !P2P_SUPPORT */
				pWscControl->WscStatus = 0;
				pWscControl->WscState = 0;
				pWscControl->WscPinCode = 0;
				pWscControl->WscLastPinFromEnrollee = 0;
				pWscControl->WscEnrollee4digitPinCode = FALSE;
				pWscControl->WscEnrolleePinCode = 0;
				pWscControl->WscSelReg = 0;
				pWscControl->WscUseUPnP = 0;
				pWscControl->bWCNTest = FALSE;
				pWscControl->WscKeyASCII = 0; /* default, 0 (64 Hex) */
				
				/*
					Enrollee 192 random bytes for DH key generation
				*/
				for (idx = 0; idx < 192; idx++)
					pWscControl->RegData.EnrolleeRandom[idx] = RandomByte(pAd);

				/* Enrollee Nonce, first generate and save to Wsc Control Block*/
				for (idx = 0; idx < 16; idx++)
				{
					pWscControl->RegData.SelfNonce[idx] = RandomByte(pAd);
				}
				NdisZeroMemory(&pWscControl->WscDefaultSsid, sizeof(NDIS_802_11_SSID));
				NdisZeroMemory(&pWscControl->Wsc_Uuid_Str[0], UUID_LEN_STR);
				NdisZeroMemory(&pWscControl->Wsc_Uuid_E[0], UUID_LEN_HEX);
				pWscControl->bCheckMultiByte = FALSE;
				pWscControl->bWscAutoTigeer = FALSE;
				pWscControl->bWscFragment = FALSE;
				pWscControl->WscFragSize = 128;
				pWscControl->WscRxBufLen = 0;
				pWscControl->pWscRxBuf = NULL;
				os_alloc_mem(pAd, &pWscControl->pWscRxBuf, MGMT_DMA_BUFFER_SIZE);
				if (pWscControl->pWscRxBuf)
					NdisZeroMemory(pWscControl->pWscRxBuf, MGMT_DMA_BUFFER_SIZE);
				pWscControl->WscTxBufLen = 0;
				pWscControl->pWscTxBuf = NULL;
				os_alloc_mem(pAd, &pWscControl->pWscTxBuf, MGMT_DMA_BUFFER_SIZE);
				if (pWscControl->pWscTxBuf)
					NdisZeroMemory(pWscControl->pWscTxBuf, MGMT_DMA_BUFFER_SIZE);
				initList(&pWscControl->WscPeerList);
				NdisAllocateSpinLock(pAd, &pWscControl->WscPeerListSemLock);
				pWscControl->PinAttackCount = 0;
				pWscControl->bSetupLock = FALSE;
#ifdef WSC_V2_SUPPORT
				pWscV2Info = &pWscControl->WscV2Info;
				pWscV2Info->bWpsEnable = TRUE;
				pWscV2Info->ExtraTlv.TlvLen = 0;
				pWscV2Info->ExtraTlv.TlvTag = 0;
				pWscV2Info->ExtraTlv.pTlvData = NULL;
				pWscV2Info->ExtraTlv.TlvType = TLV_ASCII;
				pWscV2Info->bEnableWpsV2 = TRUE;
				pWscControl->SetupLockTime = WSC_WPS_AP_SETUP_LOCK_TIME;
				pWscControl->MaxPinAttack = WSC_WPS_AP_MAX_PIN_ATTACK;
#endif /* WSC_V2_SUPPORT */

			}
#endif /* WSC_AP_SUPPORT */

#ifdef EASY_CONFIG_SETUP
			AutoProvisionGenWpsPTK(pAd, j);
			pAd->ApCfg.MBSSID[j].EasyConfigInfo.RssiThreshold = -50;
			pAd->ApCfg.MBSSID[j].EasyConfigInfo.bEnable = TRUE;
			NdisZeroMemory(pAd->ApCfg.MBSSID[j].EasyConfigInfo.WpsPinCode, MAC_ADDR_LEN);
#endif /* EASY_CONFIG_SETUP */
#ifdef WAC_SUPPORT
			pAd->ApCfg.MBSSID[j].EasyConfigInfo.bEnableWAC = TRUE;
			initList(&pAd->ApCfg.MBSSID[j].EasyConfigInfo.WAC_PeerList);
			NdisAllocateSpinLock(pAd, &pAd->ApCfg.MBSSID[j].EasyConfigInfo.WAC_PeerListSemLock);
#ifdef WAC_QOS_PRIORITY
			initList(&pAd->ApCfg.MBSSID[j].EasyConfigInfo.WAC_ForcePriorityList);
			NdisAllocateSpinLock(pAd, &pAd->ApCfg.MBSSID[j].EasyConfigInfo.WAC_ForcePriorityListSemLock);
#endif /* WAC_QOS_PRIORITY */
			pAd->ApCfg.MBSSID[j].EasyConfigInfo.pVendorInfoForBeacon = NULL;
			pAd->ApCfg.MBSSID[j].EasyConfigInfo.pVendorInfoForProbeRsp = NULL;
#endif /* WAC_SUPPORT */

			for(i = 0; i < WLAN_MAX_NUM_OF_TIM; i++)
	        		pAd->ApCfg.MBSSID[j].TimBitmaps[i] = 0;
		}
		pAd->ApCfg.DtimCount  = 0;
		pAd->ApCfg.DtimPeriod = DEFAULT_DTIM_PERIOD;

		pAd->ApCfg.ErpIeContent = 0;

		pAd->ApCfg.StaIdleTimeout = MAC_TABLE_AGEOUT_TIME;

#ifdef IDS_SUPPORT
		/* Default disable IDS threshold and reset all IDS counters*/
		pAd->ApCfg.IdsEnable = FALSE;
		pAd->ApCfg.AuthFloodThreshold = 0;
		pAd->ApCfg.AssocReqFloodThreshold = 0;
		pAd->ApCfg.ReassocReqFloodThreshold = 0;
		pAd->ApCfg.ProbeReqFloodThreshold = 0;
		pAd->ApCfg.DisassocFloodThreshold = 0;
		pAd->ApCfg.DeauthFloodThreshold = 0;
		pAd->ApCfg.EapReqFloodThreshold = 0;
		RTMPClearAllIdsCounter(pAd);
#endif /* IDS_SUPPORT */

#ifdef WDS_SUPPORT
		APWdsInitialize(pAd);
#endif /* WDS_SUPPORT*/

#ifdef WSC_INCLUDED
		pAd->WriteWscCfgToDatFile = 0xFF;
		pAd->WriteWscCfgToAr9DatFile = FALSE;
#ifdef CONFIG_AP_SUPPORT
#ifdef RTMP_RBUS_SUPPORT
#ifdef __ECOS
		pAd->bWscDriverAutoUpdateCfg = TRUE;
#else
		pAd->bWscDriverAutoUpdateCfg = FALSE;
#endif /* __ECOS */
#else
		pAd->bWscDriverAutoUpdateCfg = TRUE;
#endif
#endif /* CONFIG_AP_SUPPORT */
#endif /* WSC_INCLUDED */

#ifdef APCLI_SUPPORT
		pAd->ApCfg.FlgApCliIsUapsdInfoUpdated = FALSE;

		for(j = 0; j < MAX_APCLI_NUM; j++) 
		{
			pAd->ApCfg.ApCliTab[j].AuthMode = Ndis802_11AuthModeOpen;
			pAd->ApCfg.ApCliTab[j].WepStatus = Ndis802_11WEPDisabled;
			pAd->ApCfg.ApCliTab[j].bAutoTxRateSwitch = TRUE;
			pAd->ApCfg.ApCliTab[j].DesiredTransmitSetting.field.MCS = MCS_AUTO;
			pAd->ApCfg.ApCliTab[j].UapsdInfo.bAPSDCapable = FALSE;

#ifdef APCLI_WPA_SUPPLICANT_SUPPORT
			pAd->ApCfg.ApCliTab[j].IEEE8021X=FALSE;
			pAd->ApCfg.ApCliTab[j].IEEE8021x_required_keys=FALSE;
			pAd->ApCfg.ApCliTab[j].bRSN_IE_FromWpaSupplicant=FALSE;
			pAd->ApCfg.ApCliTab[j].bLostAp=FALSE;
			pAd->ApCfg.ApCliTab[j].bScanReqIsFromWebUI=FALSE;
			pAd->ApCfg.ApCliTab[j].bConfigChanged=FALSE;
			pAd->ApCfg.ApCliTab[j].DesireSharedKeyId=0;
			pAd->ApCfg.ApCliTab[j].WpaSupplicantUP=WPA_SUPPLICANT_DISABLE;
			pAd->ApCfg.ApCliTab[j].WpaSupplicantScanCount=0;
			pAd->ApCfg.ApCliTab[j].pWpsProbeReqIe=NULL;
			pAd->ApCfg.ApCliTab[j].WpsProbeReqIeLen=0;
			pAd->ApCfg.ApCliTab[j].pWpaAssocIe=NULL;
			pAd->ApCfg.ApCliTab[j].WpaAssocIeLen=0;
			pAd->ApCfg.ApCliTab[j].SavedPMKNum=0;
			RTMPZeroMemory(pAd->ApCfg.ApCliTab[j].SavedPMK, (PMKID_NO * sizeof(BSSID_INFO)));
#endif/*APCLI_WPA_SUPPLICANT_SUPPORT*/

		}
#endif /* APCLI_SUPPORT */
		pAd->ApCfg.EntryClientCount = 0;
	}
#endif /* CONFIG_AP_SUPPORT */

#ifdef ETH_CONVERT_SUPPORT
	if (pAd->OpMode == OPMODE_STA)
	{
		NdisZeroMemory(pAd->EthConvert.EthCloneMac, MAC_ADDR_LEN);
		pAd->EthConvert.ECMode = ETH_CONVERT_MODE_DISABLE;
		pAd->EthConvert.CloneMacVaild = FALSE;
		/*pAd->EthConvert.nodeCount = 0;*/
		NdisZeroMemory(pAd->EthConvert.SSIDStr, MAX_LEN_OF_SSID);
		pAd->EthConvert.SSIDStrLen = 0;
		pAd->EthConvert.macAutoLearn = FALSE;
	}
#endif /* ETH_CONVERT_SUPPORT */

#ifdef IP_ASSEMBLY
	if (pAd->OpMode == OPMODE_STA)
	{
		pAd->StaCfg.bFragFlag = TRUE;
	}
#endif /* IP_ASSEMBLY */
	
	/* part IV. others*/
	
	/* dynamic BBP R66:sensibity tuning to overcome background noise*/
	pAd->BbpTuning.bEnable                = TRUE;  
	pAd->BbpTuning.FalseCcaLowerThreshold = 100;
	pAd->BbpTuning.FalseCcaUpperThreshold = 512;
	pAd->BbpTuning.R66Delta               = 4;
	pAd->Mlme.bEnableAutoAntennaCheck = TRUE;
	
	
	/* Also initial R66CurrentValue, RTUSBResumeMsduTransmission might use this value.*/
	/* if not initial this value, the default value will be 0.*/
	
	pAd->BbpTuning.R66CurrentValue = 0x38;

	pAd->Bbp94 = BBPR94_DEFAULT;
	pAd->BbpForCCK = FALSE;
	
	/* Default is FALSE for test bit 1*/
	/*pAd->bTest1 = FALSE;*/
	
	/* initialize MAC table and allocate spin lock*/
	NdisZeroMemory(&pAd->MacTab, sizeof(MAC_TABLE));
	InitializeQueueHeader(&pAd->MacTab.McastPsQueue);
	NdisAllocateSpinLock(pAd, &pAd->MacTabLock);

	/*RTMPInitTimer(pAd, &pAd->RECBATimer, RECBATimerTimeout, pAd, TRUE);*/
	/*RTMPSetTimer(&pAd->RECBATimer, REORDER_EXEC_INTV);*/

#ifdef MESH_SUPPORT
	pAd->MeshTab.AuthMode = Ndis802_11AuthModeOpen;	
	pAd->MeshTab.WepStatus = Ndis802_11EncryptionDisabled;
	pAd->MeshTab.DefaultKeyId = 0;
#endif /* MESH_SUPPORT */

	pAd->CommonCfg.bWiFiTest = FALSE;
#ifdef RTMP_MAC_PCI
    pAd->bPCIclkOff = FALSE;
#endif /* RTMP_MAC_PCI */

#ifdef CONFIG_AP_SUPPORT
	pAd->ApCfg.EntryLifeCheck = MAC_ENTRY_LIFE_CHECK_CNT;

#ifdef DOT11R_FT_SUPPORT
	FT_CfgInitial(pAd);
#endif /* DOT11R_FT_SUPPORT */
#endif /* CONFIG_AP_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
#ifdef PCIE_PS_SUPPORT
	RTMP_SET_PSFLAG(pAd, fRTMP_PS_CAN_GO_SLEEP);
#endif /* PCIE_PS_SUPPORT */
#ifdef DOT11Z_TDLS_SUPPORT
		pAd->StaCfg.TdlsInfo.bTDLSCapable = FALSE;
		pAd->StaCfg.TdlsInfo.TdlsChSwitchSupp = TRUE;
		pAd->StaCfg.TdlsInfo.TdlsPsmSupp = FALSE;
		pAd->StaCfg.TdlsInfo.TdlsKeyLifeTime = TDLS_LEY_LIFETIME;
#ifdef TDLS_AUTOLINK_SUPPORT
		initList(&pAd->StaCfg.TdlsInfo.TdlsDiscovPeerList);
		NdisAllocateSpinLock(&pAd->StaCfg.TdlsInfo.TdlsDiscovPeerListSemLock);
		initList(&pAd->StaCfg.TdlsInfo.TdlsBlackList);
		NdisAllocateSpinLock(&pAd->StaCfg.TdlsInfo.TdlsBlackListSemLock);

		pAd->StaCfg.TdlsInfo.TdlsAutoSetupRssiThreshold = TDLS_AUTO_SETUP_RSSI_THRESHOLD;
		pAd->StaCfg.TdlsInfo.TdlsAutoTeardownRssiThreshold = TDLS_AUTO_TEARDOWN_RSSI_THRESHOLD;
		pAd->StaCfg.TdlsInfo.TdlsRssiMeasurementPeriod = TDLS_RSSI_MEASUREMENT_PERIOD;
		pAd->StaCfg.TdlsInfo.TdlsDisabledPeriodByTeardown = TDLS_DISABLE_PERIOD_BY_TEARDOWN;
		pAd->StaCfg.TdlsInfo.TdlsAutoDiscoveryPeriod = TDLS_AUTO_DISCOVERY_PERIOD;
#endif /* TDLS_AUTOLINK_SUPPORT */
#endif /* DOT11Z_TDLS_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */

	pAd->RxAnt.Pair1PrimaryRxAnt = 0;
	pAd->RxAnt.Pair1SecondaryRxAnt = 1;

		pAd->RxAnt.EvaluatePeriod = 0;
		pAd->RxAnt.RcvPktNumWhenEvaluate = 0;
#ifdef CONFIG_STA_SUPPORT
		pAd->RxAnt.Pair1AvgRssi[0] = pAd->RxAnt.Pair1AvgRssi[1] = 0;
#endif /* CONFIG_STA_SUPPORT */
#ifdef CONFIG_AP_SUPPORT
		pAd->RxAnt.Pair1AvgRssiGroup1[0] = pAd->RxAnt.Pair1AvgRssiGroup1[1] = 0;
		pAd->RxAnt.Pair1AvgRssiGroup2[0] = pAd->RxAnt.Pair1AvgRssiGroup2[1] = 0;
#endif /* CONFIG_AP_SUPPORT */

#ifdef ANT_DIVERSITY_SUPPORT
	pAd->CommonCfg.RxAntDiversityCfg = ANT_DIVERSITY_DEFAULT;
	pAd->CommonCfg.bSWRxAntDiversity = FALSE;
	pAd->CommonCfg.bHWRxAntDiversity = FALSE;
	pAd->CommonCfg.nAntEval_Threshold = -55; /* dBm */
	pAd->CommonCfg.nAntMiss_Threshold = 7;	/* RX antenna mismatch threshold */
	pAd->CommonCfg.nAntMiss_Cnt = 0;		/* RX antenna mismatch count */
	pAd->CommonCfg.bAntEvalEnable = FALSE;
	pAd->CommonCfg.nAntChk_Period = 4; /* 4 sec */
#endif /* ANT_DIVERSITY_SUPPORT */

#ifdef TXRX_SW_ANTDIV_SUPPORT
		pAd->chipCap.bTxRxSwAntDiv = FALSE;
#endif /* TXRX_SW_ANTDIV_SUPPORT */

#if 0
#ifdef CONFIG_STA_SUPPORT
RTMP_SET_PSFLAG(pAd, fRTMP_PS_CAN_GO_SLEEP);
#endif /* CONFIG_STA_SUPPORT */
#endif

#if defined(AP_SCAN_SUPPORT) || defined(CONFIG_STA_SUPPORT)
	for (i = 0; i < MAX_LEN_OF_BSS_TABLE; i++) 
	{
		PBSS_ENTRY	pBssEntry = &pAd->ScanTab.BssEntry[i];
		
		if (pAd->ProbeRespIE[i].pIe)
			pBssEntry->pVarIeFromProbRsp = pAd->ProbeRespIE[i].pIe;
		else
			pBssEntry->pVarIeFromProbRsp = NULL;
	}
#endif /* defined(AP_SCAN_SUPPORT) || defined(CONFIG_STA_SUPPORT) */

#ifdef HW_COEXISTENCE_SUPPORT
	pAd->bHWCoexistenceInit = FALSE;
	pAd->bWiMaxCoexistenceOn = FALSE;
#endif /* HW_COEXISTENCE_SUPPORT */
#ifdef BT_COEXISTENCE_SUPPORT
	MiscUserCfgInit(pAd);
#endif /* BT_COEXISTENCE_SUPPORT */

#ifdef WSC_INCLUDED
	NdisZeroMemory(&pAd->CommonCfg.WscStaPbcProbeInfo, sizeof(WSC_STA_PBC_PROBE_INFO));
	pAd->CommonCfg.WscPBCOverlap = FALSE;
#endif /* WSC_INCLUDED */

#ifdef RT3593
	if (IS_RT3593(pAd))
	{
		RTMP_FREQ_CAL_DISABLE(pAd); /* Off by default*/
	}
#endif /* RT3593 */

#ifdef P2P_SUPPORT
	P2pCfgInit(pAd);
#endif /* P2P_SUPPORT */

#ifdef WFD_SUPPORT
	WfdCfgInit(pAd);
#endif /* WFD_SUPPORT */

#ifdef RT3883
	if (IS_RT3883(pAd))
		pAd->FlgCWC = 0;
#endif /* RT3883 */

#if (defined(WOW_SUPPORT) && defined(RTMP_MAC_USB)) || defined(NEW_WOW_SUPPORT)
	pAd->WOW_Cfg.bEnable = FALSE;	
	pAd->WOW_Cfg.bWOWFirmware = FALSE;	/* load normal firmware */
	pAd->WOW_Cfg.bInBand = TRUE;		/* use in-band signal */
	pAd->WOW_Cfg.nSelectedGPIO = 1;
	pAd->WOW_Cfg.nDelay = 3; /* (3+1)*3 = 12 sec */
	pAd->WOW_Cfg.nHoldTime = 1; /* 1*10 = 10 ms */
	DBGPRINT(RT_DEBUG_OFF, ("WOW Enable %d, WOWFirmware %d\n", pAd->WOW_Cfg.bEnable, pAd->WOW_Cfg.bWOWFirmware));
#endif /* (defined(WOW_SUPPORT) && defined(RTMP_MAC_USB)) || defined(NEW_WOW_SUPPORT) */

	/* 802.11H and DFS related params*/
	pAd->Dot11_H.CSCount = 0;
	pAd->Dot11_H.CSPeriod = 10;
	pAd->Dot11_H.RDMode = RD_NORMAL_MODE;
	pAd->Dot11_H.bDFSIndoor = 1;

#if defined(RT5370) || defined(RT5372) || defined(RT5390) || defined(RT5392)
pAd->BbpResetFlag = 0;
pAd->BbpResetFlagCount = 0;
pAd->BbpResetFlagCountVale = 20;
#endif

#ifdef FPGA_MODE
	pAd->fpga_on = 0x0;
	pAd->tx_kick_cnt = 0;
	pAd->data_phy = 0;
	pAd->data_mcs = 0;
	pAd->data_bw = 0;
	pAd->data_gi = 0;
#endif /* FPGA_MODE */

#ifdef MICROWAVE_OVEN_SUPPORT
	if (pAd->OpMode == OPMODE_AP)
		pAd->CommonCfg.MO_Cfg.bEnable = TRUE;
	else
		pAd->CommonCfg.MO_Cfg.bEnable = FALSE;
	pAd->CommonCfg.MO_Cfg.nFalseCCATh = MO_FALSE_CCA_TH;
#endif /* MICROWAVE_OVEN_SUPPORT */

#ifdef ED_MONITOR
	pAd->ed_chk = FALSE; //let country region to turn on

#ifdef CONFIG_AP_SUPPORT
	pAd->ed_sta_threshold = 1;
	pAd->ed_ap_threshold = 1;
#endif /* CONFIG_AP_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
	pAd->ed_ap_scaned = 5;
	pAd->ed_current_ch_aps = 1;
	pAd->ed_rssi_threshold = -80; //tmp set
#endif /* CONFIG_STA_SUPPORT */

	pAd->ed_chk_period = 100;
	pAd->ed_threshold = 90;
	pAd->false_cca_threshold = 180;
	pAd->ed_block_tx_threshold = 2;
#endif /* ED_MONITOR */

	DBGPRINT(RT_DEBUG_TRACE, ("<-- UserCfgInit\n"));
}

/* IRQL = PASSIVE_LEVEL*/
UCHAR BtoH(STRING ch)
{
	if (ch >= '0' && ch <= '9') return (ch - '0');        /* Handle numerals*/
	if (ch >= 'A' && ch <= 'F') return (ch - 'A' + 0xA);  /* Handle capitol hex digits*/
	if (ch >= 'a' && ch <= 'f') return (ch - 'a' + 0xA);  /* Handle small hex digits*/
	return(255);
}


/*  FUNCTION: AtoH(char *, UCHAR *, int)*/

/*  PURPOSE:  Converts ascii string to network order hex*/

/*  PARAMETERS:*/
/*    src    - pointer to input ascii string*/
/*    dest   - pointer to output hex*/
/*    destlen - size of dest*/

/*  COMMENTS:*/

/*    2 ascii bytes make a hex byte so must put 1st ascii byte of pair*/
/*    into upper nibble and 2nd ascii byte of pair into lower nibble.*/

/* IRQL = PASSIVE_LEVEL*/

void AtoH(PSTRING src, PUCHAR dest, int destlen)
{
	PSTRING srcptr;
	PUCHAR destTemp;

	srcptr = src;	
	destTemp = (PUCHAR) dest; 

	while(destlen--)
	{
		*destTemp = BtoH(*srcptr++) << 4;    /* Put 1st ascii byte in upper nibble.*/
		*destTemp += BtoH(*srcptr++);      /* Add 2nd ascii byte to above.*/
		destTemp++;
	}
}


/*
========================================================================
Routine Description:
	Add a timer to the timer list.

Arguments:
	pAd				- WLAN control block pointer
	pRsc			- the OS resource

Return Value:
	None

Note:
========================================================================
*/
VOID	RTMP_TimerListAdd(
	IN	PRTMP_ADAPTER			pAd,
	IN	VOID					*pRsc)
{
	LIST_HEADER *pRscList = &pAd->RscTimerCreateList;
	LIST_RESOURCE_OBJ_ENTRY *pObj;


	/* try to find old entry */
	pObj = (LIST_RESOURCE_OBJ_ENTRY *)(pRscList->pHead);
	while(1)
	{
		if (pObj == NULL)
			break;
		if ((ULONG)(pObj->pRscObj) == (ULONG)pRsc)
			return; /* exists */
		pObj = pObj->pNext;
	}

	/* allocate a timer record entry */
	os_alloc_mem(NULL, (UCHAR **)&(pObj), sizeof(LIST_RESOURCE_OBJ_ENTRY));
	if (pObj == NULL)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("%s: alloc timer obj fail!\n", __FUNCTION__));
		return;
	}
	else
	{
		pObj->pRscObj = pRsc;
		insertTailList(pRscList, (LIST_ENTRY *)pObj);
		DBGPRINT(RT_DEBUG_ERROR, ("%s: add timer obj %lx!\n", __FUNCTION__, (ULONG)pRsc));
	}
}


/*
========================================================================
Routine Description:
	Cancel all timers in the timer list.

Arguments:
	pAd				- WLAN control block pointer

Return Value:
	None

Note:
========================================================================
*/
VOID	RTMP_TimerListRelease(
	IN	PRTMP_ADAPTER			pAd)
{
	LIST_HEADER *pRscList = &pAd->RscTimerCreateList;
	LIST_RESOURCE_OBJ_ENTRY *pObj, *pObjOld;
	BOOLEAN Cancel;


	/* try to find old entry */
	pObj = (LIST_RESOURCE_OBJ_ENTRY *)(pRscList->pHead);
	while(1)
	{
		if (pObj == NULL)
			break;
		DBGPRINT(RT_DEBUG_TRACE, ("%s: Cancel timer obj %lx!\n", __FUNCTION__, (ULONG)(pObj->pRscObj)));
		RTMPReleaseTimer(pObj->pRscObj, &Cancel);
		pObjOld = pObj;
		pObj = pObj->pNext;
		os_free_mem(NULL, pObjOld);
	}

	/* reset TimerList */
	initList(&pAd->RscTimerCreateList);
}


VOID RTMP_AllTimerListRelease(RTMP_ADAPTER *pAd)
{
   LIST_HEADER *pRscList = &pAd->RscTimerCreateList;
   LIST_RESOURCE_OBJ_ENTRY *pObj, *pObjOld;
   BOOLEAN Cancel;

   /* try to find old entry */
   pObj = (LIST_RESOURCE_OBJ_ENTRY *)(pRscList->pHead);
   while(1)
   {
           if (pObj == NULL)
                   break;
           DBGPRINT(RT_DEBUG_TRACE, ("%s: Cancel timer obj %lx!\n", __FUNCTION__, (ULONG)(pObj->pRscObj)));
           pObjOld = pObj;
           pObj = pObj->pNext;
           RTMPReleaseTimer(pObjOld->pRscObj, &Cancel);
           os_free_mem(NULL, pObjOld);
   }

   /* reset TimerList */
   initList(&pAd->RscTimerCreateList);
}


/*
	========================================================================
	
	Routine Description:
		Init timer objects

	Arguments:
		pAd			Pointer to our adapter
		pTimer				Timer structure
		pTimerFunc			Function to execute when timer expired
		Repeat				Ture for period timer

	Return Value:
		None

	Note:
		
	========================================================================
*/
VOID	RTMPInitTimer(
	IN	PRTMP_ADAPTER			pAd,
	IN	PRALINK_TIMER_STRUCT	pTimer,
	IN	PVOID					pTimerFunc,
	IN	PVOID					pData,
	IN	BOOLEAN					Repeat)
{
	RTMP_SEM_LOCK(&TimerSemLock);

	RTMP_TimerListAdd(pAd, pTimer);

	
	/* Set Valid to TRUE for later used.*/
	/* It will crash if we cancel a timer or set a timer */
	/* that we haven't initialize before.*/
	/* */
	pTimer->Valid      = TRUE;
	
	pTimer->PeriodicType = Repeat;
	pTimer->State      = FALSE;
	pTimer->cookie = (ULONG) pData;
	pTimer->pAd = pAd;

	RTMP_OS_Init_Timer(pAd, &pTimer->TimerObj,	pTimerFunc, (PVOID) pTimer, &pAd->RscTimerMemList);	
	DBGPRINT(RT_DEBUG_TRACE,("%s: %lx\n",__FUNCTION__, (ULONG)pTimer));

	RTMP_SEM_UNLOCK(&TimerSemLock);
}


/*
	========================================================================
	
	Routine Description:
		Init timer objects

	Arguments:
		pTimer				Timer structure
		Value				Timer value in milliseconds

	Return Value:
		None

	Note:
		To use this routine, must call RTMPInitTimer before.
		
	========================================================================
*/
VOID	RTMPSetTimer(
	IN	PRALINK_TIMER_STRUCT	pTimer,
	IN	ULONG					Value)
{
	RTMP_SEM_LOCK(&TimerSemLock);

	if (pTimer->Valid)
	{
		RTMP_ADAPTER *pAd;
		
		pAd = (RTMP_ADAPTER *)pTimer->pAd;
		if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_HALT_IN_PROGRESS | fRTMP_ADAPTER_NIC_NOT_EXIST))
		{
			DBGPRINT_ERR(("RTMPSetTimer failed, Halt in Progress!\n"));
			RTMP_SEM_UNLOCK(&TimerSemLock);
			return;
		}
		
		pTimer->TimerValue = Value;
		pTimer->State      = FALSE;
		if (pTimer->PeriodicType == TRUE)
		{
			pTimer->Repeat = TRUE;
			RTMP_SetPeriodicTimer(&pTimer->TimerObj, Value);
		}
		else
		{
			pTimer->Repeat = FALSE;
			RTMP_OS_Add_Timer(&pTimer->TimerObj, Value);
		}

		DBGPRINT(RT_DEBUG_INFO,("%s: %lx\n",__FUNCTION__, (ULONG)pTimer));
	}
	else
	{
		DBGPRINT_ERR(("RTMPSetTimer failed, Timer hasn't been initialize!\n"));
	}
	RTMP_SEM_UNLOCK(&TimerSemLock);
}


/*
	========================================================================
	
	Routine Description:
		Init timer objects

	Arguments:
		pTimer				Timer structure
		Value				Timer value in milliseconds

	Return Value:
		None

	Note:
		To use this routine, must call RTMPInitTimer before.
		
	========================================================================
*/
VOID	RTMPModTimer(
	IN	PRALINK_TIMER_STRUCT	pTimer,
	IN	ULONG					Value)
{
	BOOLEAN	Cancel;


	RTMP_SEM_LOCK(&TimerSemLock);

	if (pTimer->Valid)
	{
		pTimer->TimerValue = Value;
		pTimer->State      = FALSE;
		if (pTimer->PeriodicType == TRUE)
		{
			RTMP_SEM_UNLOCK(&TimerSemLock);
			RTMPCancelTimer(pTimer, &Cancel);
			RTMPSetTimer(pTimer, Value);
		}
		else
		{
			RTMP_OS_Mod_Timer(&pTimer->TimerObj, Value);
			RTMP_SEM_UNLOCK(&TimerSemLock);
		}
		DBGPRINT(RT_DEBUG_TRACE,("%s: %lx\n",__FUNCTION__, (ULONG)pTimer));
	}
	else
	{
		DBGPRINT_ERR(("RTMPModTimer failed, Timer hasn't been initialize!\n"));
		RTMP_SEM_UNLOCK(&TimerSemLock);
	}
}


/*
	========================================================================
	
	Routine Description:
		Cancel timer objects

	Arguments:
		Adapter						Pointer to our adapter

	Return Value:
		None

	IRQL = PASSIVE_LEVEL
	IRQL = DISPATCH_LEVEL
	
	Note:
		1.) To use this routine, must call RTMPInitTimer before.
		2.) Reset NIC to initial state AS IS system boot up time.
		
	========================================================================
*/
VOID	RTMPCancelTimer(
	IN	PRALINK_TIMER_STRUCT	pTimer,
	OUT	BOOLEAN					*pCancelled)
{
	RTMP_SEM_LOCK(&TimerSemLock);

	if (pTimer->Valid)
	{
		if (pTimer->State == FALSE)
			pTimer->Repeat = FALSE;
		
		RTMP_OS_Del_Timer(&pTimer->TimerObj, pCancelled);
		
		if (*pCancelled == TRUE)
			pTimer->State = TRUE;

#ifdef RTMP_TIMER_TASK_SUPPORT
		/* We need to go-through the TimerQ to findout this timer handler and remove it if */
		/*		it's still waiting for execution.*/
		RtmpTimerQRemove(pTimer->pAd, pTimer);
#endif /* RTMP_TIMER_TASK_SUPPORT */

		DBGPRINT(RT_DEBUG_INFO,("%s: %lx\n",__FUNCTION__, (ULONG)pTimer));
	}
	else
	{
		DBGPRINT(RT_DEBUG_INFO,("RTMPCancelTimer failed, Timer hasn't been initialize!\n"));
	}

	RTMP_SEM_UNLOCK(&TimerSemLock);
}


VOID	RTMPReleaseTimer(
	IN	PRALINK_TIMER_STRUCT	pTimer,
	OUT	BOOLEAN					*pCancelled)
{
	RTMP_SEM_LOCK(&TimerSemLock);

	if (pTimer->Valid)
	{
		if (pTimer->State == FALSE)
			pTimer->Repeat = FALSE;
		
		RTMP_OS_Del_Timer(&pTimer->TimerObj, pCancelled);
		
		if (*pCancelled == TRUE)
			pTimer->State = TRUE;

#ifdef RTMP_TIMER_TASK_SUPPORT
		/* We need to go-through the TimerQ to findout this timer handler and remove it if */
		/*		it's still waiting for execution.*/
		RtmpTimerQRemove(pTimer->pAd, pTimer);
#endif /* RTMP_TIMER_TASK_SUPPORT */

		/* release timer */
		RTMP_OS_Release_Timer(&pTimer->TimerObj);

		pTimer->Valid = FALSE;

		DBGPRINT(RT_DEBUG_INFO,("%s: %lx\n",__FUNCTION__, (ULONG)pTimer));
	}
	else
	{
		DBGPRINT(RT_DEBUG_INFO,("RTMPReleasefailed, Timer hasn't been initialize!\n"));
	}

	RTMP_SEM_UNLOCK(&TimerSemLock);
}


/*
	========================================================================
	
	Routine Description:
		Enable RX 

	Arguments:
		pAd						Pointer to our adapter

	Return Value:
		None

	IRQL <= DISPATCH_LEVEL
	
	Note:
		Before Enable RX, make sure you have enabled Interrupt.
	========================================================================
*/
VOID RTMPEnableRxTx(
	IN PRTMP_ADAPTER	pAd)
{
	UINT32 rx_filter_flag;

	DBGPRINT(RT_DEBUG_TRACE, ("==> RTMPEnableRxTx\n"));

	RT28XXDMAEnable(pAd);

	/* enable RX of MAC block*/
	if (pAd->OpMode == OPMODE_AP)
	{
		rx_filter_flag = APNORMAL;

#ifdef CONFIG_AP_SUPPORT
#ifdef IDS_SUPPORT
		IF_DEV_CONFIG_OPMODE_ON_AP(pAd)
		{
			if (pAd->ApCfg.IdsEnable)
				rx_filter_flag &= (~0x4);	/* Don't drop those not-U2M frames*/
		}
#endif /* IDS_SUPPORT */			
#endif /* CONFIG_AP_SUPPORT */

		RTMP_IO_WRITE32(pAd, RX_FILTR_CFG, rx_filter_flag);     /* enable RX of DMA block*/
	}
#ifdef CONFIG_STA_SUPPORT
	else
	{
#ifdef XLINK_SUPPORT
		if (pAd->StaCfg.PSPXlink)
			rx_filter_flag = PSPXLINK;
		else
#endif /* XLINK_SUPPORT */	
			rx_filter_flag = STANORMAL;     /* Staion not drop control frame will fail WiFi Certification.*/
		RTMP_IO_WRITE32(pAd, RX_FILTR_CFG, rx_filter_flag);
	}
#endif /* CONFIG_STA_SUPPORT */
	
#ifdef HW_COEXISTENCE_SUPPORT
#if defined(RT35xx) || defined (RT5390)
#ifdef HW_COEXISTENCE_SUPPORT

	if (pAd->bHWCoexistenceInit&& (!IS_RT5390BC8(pAd)) && (!IS_RT3592BC8(pAd)))
#endif /* HW_COEXISTENCE_SUPPORT */
#endif /* RT35xx || RT5390 */
	{
#ifdef BT_COEXISTENCE_SUPPORT
		if(IS_ENABLE_BT_WIFI_ACTIVE_PULL_HIGH_BY_TIMER(pAd) && (pAd->BT_BC_PERMIT_RXWIFI_ACTIVE==TRUE))
		{
			RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, 0x224c);
		}
		if (IS_ENABLE_WIFI_ACTIVE_PULL_LOW_BY_FORCE(pAd))
		{
			RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, WLAN_WIFI_ACT_PULL_LOW);
		}
		else
#endif /* BT_COEXISTENCE_SUPPORT */
		{
			RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, WLAN_WIFI_ACT_PULL_HIGH);
		}
	}
	else
#endif /* HW_COEXISTENCE_SUPPORT */
	{
		RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, 0xc);
//+++Add by shiang for debug for pbf_loopback
			//RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, 0x2c);
//---Add by shiang for debug
//+++Add by shiang for debug invalid RxWI->WCID 
#ifdef RT8592
#if 0
		if (IS_RT8592(pAd))
		{	// enable ts in RxWI->RSSI fields
			RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, 0x8c);
		}
#endif
#endif /* RT8592 */
//---Add by shiang for  debug invalid RxWI->WCID 
	}

	DBGPRINT(RT_DEBUG_TRACE, ("<== RTMPEnableRxTx\n"));	
}


void CfgInitHook(PRTMP_ADAPTER pAd)
{
	/*pAd->bBroadComHT = TRUE;*/
}


static INT RtmpChipOpsRegister(
	IN RTMP_ADAPTER *pAd,
	IN INT			infType)
{
	RTMP_CHIP_OP	*pChipOps = &pAd->chipOps;
	int status;
	
	memset(pChipOps, 0, sizeof(RTMP_CHIP_OP));

	RtmpChipOpsHook(pAd);

	/* MCU related */
	ChipOpsMCUHook(pAd, pAd->chipCap.MCUType);

	/* set eeprom related hook functions */
	status = RtmpChipOpsEepromHook(pAd, infType);

	return status;
}


#ifdef RTMP_MAC_USB
BOOLEAN PairEP(RTMP_ADAPTER *pAd, UINT8 EP, UINT8 Index, UINT8 InOut)
{
	RTMP_CHIP_CAP *pChipCap = &pAd->chipCap;

	if (Index == 0 && InOut == 0)
	{
		pChipCap->CommandBulkOutAddr = EP;
		DBGPRINT(RT_DEBUG_OFF, ("Endpoint(%x) is for In-band Command\n", EP));
		return TRUE;
	}
	
	if (Index > 0 && Index < 5 && InOut == 0)
	{
		pChipCap->WMM0ACBulkOutAddr[Index - 1] = EP; 
		DBGPRINT(RT_DEBUG_OFF, ("Endpoint(%x) is for WMM0 AC%d\n", EP, Index - 1));
		return TRUE;
	}
	
	if (Index == 5 && InOut == 0)
	{
		pChipCap->WMM1ACBulkOutAddr = EP;
		DBGPRINT(RT_DEBUG_OFF, ("Endpoint(%x) is for WMM1 AC0\n", EP));
		return TRUE;
	}

	if (Index == 0 && InOut == 1)
	{
		pChipCap->DataBulkInAddr = EP;
		DBGPRINT(RT_DEBUG_OFF, ("Endpoint(%x) is for Data-In\n", EP));
		return TRUE;
	}


	if (Index == 1 && InOut == 1)
	{
		pChipCap->CommandRspBulkInAddr = EP;
		DBGPRINT(RT_DEBUG_OFF, ("Endpoint(%x) is for Command Rsp\n", EP));
		return TRUE;
	}
				
	return FALSE;
}
#endif /* RTMP_MAC_USB */


INT RtmpRaDevCtrlInit(VOID *pAdSrc, RTMP_INF_TYPE infType)
{
	RTMP_ADAPTER *pAd = (PRTMP_ADAPTER)pAdSrc;
	UINT8 i;

	/* Assign the interface type. We need use it when do register/EEPROM access.*/
	pAd->infType = infType;

#ifdef CONFIG_STA_SUPPORT
	pAd->OpMode = OPMODE_STA;
	DBGPRINT(RT_DEBUG_TRACE, ("STA Driver version-%s\n", STA_DRIVER_VERSION));
#endif /* CONFIG_STA_SUPPORT */

#ifdef CONFIG_AP_SUPPORT
	pAd->OpMode = OPMODE_AP;
	DBGPRINT(RT_DEBUG_TRACE, ("AP Driver version-%s\n", AP_DRIVER_VERSION));
#endif /* CONFIG_AP_SUPPORT */

#ifdef P2P_SUPPORT
	pAd->OpMode = OPMODE_STA;
#endif /* P2P_SUPPORT */

#ifdef RTMP_MAC_USB
	RTMP_SEM_EVENT_INIT(&(pAd->UsbVendorReq_semaphore), &pAd->RscSemMemList);
	RTMP_SEM_EVENT_INIT(&(pAd->reg_atomic), &pAd->RscSemMemList);
	RTMP_SEM_EVENT_INIT(&(pAd->hw_atomic), &pAd->RscSemMemList);
	os_alloc_mem(pAd, (PUCHAR *)&pAd->UsbVendorReqBuf, MAX_PARAM_BUFFER_SIZE - 1);
	if (pAd->UsbVendorReqBuf == NULL)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("Allocate vendor request temp buffer failed!\n"));
		return FALSE;
	}


#endif /* RTMP_MAC_USB */

	RtmpChipOpsRegister(pAd, infType);

#ifdef RTMP_MAC_USB
	for (i = 0; i < 6; i++)
	{
		if (!PairEP(pAd, pAd->BulkOutEpAddr[i], i, 0))
			DBGPRINT(RT_DEBUG_ERROR, ("Invalid bulk out ep(%x)\n", pAd->BulkOutEpAddr[i]));
	}

	for (i = 0; i < 2; i++)
	{
		if (!PairEP(pAd, pAd->BulkInEpAddr[i], i, 1))
			DBGPRINT(RT_DEBUG_ERROR, ("Invalid bulk in ep(%x)\n", pAd->BulkInEpAddr[i]));
	}

#endif

#ifdef MULTIPLE_CARD_SUPPORT
{
	extern BOOLEAN RTMP_CardInfoRead(PRTMP_ADAPTER pAd);

	/* find its profile path*/
	pAd->MC_RowID = -1; /* use default profile path*/
	RTMP_CardInfoRead(pAd);

	if (pAd->MC_RowID == -1)
#ifdef CONFIG_AP_SUPPORT
		strcpy(pAd->MC_FileName, AP_PROFILE_PATH);
#endif /* CONFIG_AP_SUPPORT */
#ifdef CONFIG_STA_SUPPORT
		strcpy(pAd->MC_FileName, STA_PROFILE_PATH);
#endif /* CONFIG_STA_SUPPORT */

	DBGPRINT(RT_DEBUG_TRACE, ("MC> ROW = %d, PATH = %s\n", pAd->MC_RowID, pAd->MC_FileName));
}
#endif /* MULTIPLE_CARD_SUPPORT */

#if defined(CONFIG_CSO_SUPPORT) || defined(CONFIG_RX_CSO_SUPPORT)
	if (pAd->chipCap.asic_caps | fASIC_CAP_CSO)
		RTMP_SET_MORE_FLAG(pAd, fASIC_CAP_CSO);
#endif /* defined(CONFIG_CSO_SUPPORT) || defined(CONFIG_RX_CSO_SUPPORT) */
#ifdef CONFIG_TSO_SUPPORT
	if (pAd->chipCap.asic_caps | fASIC_CAP_TSO)
		RTMP_SET_MORE_FLAG(pAd, fASIC_CAP_TSO);
#endif /* CONFIG_TSO_SUPPORT */
	return 0;
}


BOOLEAN RtmpRaDevCtrlExit(IN VOID *pAdSrc)
{
	PRTMP_ADAPTER	pAd = (PRTMP_ADAPTER)pAdSrc;
	INT index;
	
#ifdef MULTIPLE_CARD_SUPPORT
extern UINT8  MC_CardUsed[MAX_NUM_OF_MULTIPLE_CARD];

	if ((pAd->MC_RowID >= 0) && (pAd->MC_RowID <= MAX_NUM_OF_MULTIPLE_CARD))
		MC_CardUsed[pAd->MC_RowID] = 0; /* not clear MAC address*/
#endif /* MULTIPLE_CARD_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
#ifdef CREDENTIAL_STORE
		NdisFreeSpinLock(&pAd->StaCtIf.Lock);
#endif /* CREDENTIAL_STORE */
#endif /* CONFIG_STA_SUPPORT */



#ifdef RTMP_MAC_USB
	RTMP_SEM_EVENT_DESTORY(&(pAd->UsbVendorReq_semaphore));
	RTMP_SEM_EVENT_DESTORY(&(pAd->reg_atomic));
	RTMP_SEM_EVENT_DESTORY(&(pAd->hw_atomic));

#ifdef SPECIFIC_BCN_BUF_SUPPORT
	RTMP_SEM_EVENT_DESTORY(&pAd->ShrMemSemaphore);
#endif /* SPECIFIC_BCN_BUF_SUPPORT */

	if (pAd->UsbVendorReqBuf)
		os_free_mem(pAd, pAd->UsbVendorReqBuf);
#endif /* RTMP_MAC_USB */

	/*
		Free ProbeRespIE Table
	*/
	for (index = 0; index < MAX_LEN_OF_BSS_TABLE; index++) 
	{
		if (pAd->ProbeRespIE[index].pIe)
			os_free_mem(pAd, pAd->ProbeRespIE[index].pIe);
	}

#ifdef RESOURCE_PRE_ALLOC
	RTMPFreeTxRxRingMemory(pAd);
#endif /* RESOURCE_PRE_ALLOC */

#ifdef RT65xx
	if (IS_RT6590(pAd) && (pAd->WlanFunCtrl.field.WLAN_EN == 1))
	{	
		ral_wlan_chip_onoff(pAd, FALSE, FALSE);
	}
#endif /* RT65xx */

#ifdef MT7601
	if (IS_MT7601(pAd) && (pAd->WlanFunCtrl.field.WLAN_EN == 1) )
	{	
		MT7601_WLAN_ChipOnOff(pAd, FALSE, FALSE);
	}
#endif /* MT7601 */

	RTMPFreeAdapter(pAd);

	return TRUE;
}


#ifdef CONFIG_AP_SUPPORT
#ifdef DOT11_N_SUPPORT
#ifdef DOT11N_DRAFT3
VOID RTMP_11N_D3_TimerInit(
	IN PRTMP_ADAPTER pAd)
{
	RTMPInitTimer(pAd, &pAd->CommonCfg.Bss2040CoexistTimer, GET_TIMER_FUNCTION(Bss2040CoexistTimeOut), pAd, FALSE);
}
#endif /* DOT11N_DRAFT3 */
#endif /* DOT11_N_SUPPORT */
#endif /* CONFIG_AP_SUPPORT */


#ifdef VENDOR_FEATURE3_SUPPORT
VOID RTMP_IO_WRITE32(
	PRTMP_ADAPTER pAd,
	UINT32 Offset,
	UINT32 Value)
{
	_RTMP_IO_WRITE32(pAd, Offset, Value);
}

VOID RTMP_BBP_IO_READ8_BY_REG_ID(
	PRTMP_ADAPTER pAd,
	UINT32 Offset,
	UINT8 *pValue)
{
#ifdef RT8592
	if (IS_RT8592(pAd))
		return;
#endif /* RT8592 */

#ifdef RT65xx
	if (IS_RT65XX(pAd))
		return;
#endif /* RT65xx */

#ifdef MT7601
	if (IS_MT7601(pAd))
		return;
#endif /* MT7601 */
	_RTMP_BBP_IO_READ8_BY_REG_ID(pAd, Offset, pValue);
}

VOID RTMP_BBP_IO_READ8(
	PRTMP_ADAPTER pAd,
	UCHAR Offset,
	UINT8 *pValue,
	BOOLEAN FlgValidMCR)
{
#ifdef RT8592
	if (IS_RT8592(pAd))
		return;
#endif /* RT8592 */

#ifdef RT65xx
	if (IS_RT65XX(pAd))
		return;
#endif /* RT65xx */

#ifdef MT7601
	if (IS_MT7601(pAd))
		return;
#endif /* MT7601 */

	_RTMP_BBP_IO_READ8(pAd, Offset, pValue, FlgValidMCR);
}

VOID RTMP_BBP_IO_WRITE8_BY_REG_ID(
	PRTMP_ADAPTER pAd,
	UINT32 Offset,
	UINT8 Value)
{
#ifdef RT8592
	if (IS_RT8592(pAd))
		return;
#endif /* RT8592 */

#ifdef RT65xx
	if (IS_RT65XX(pAd))
		return;
#endif /* RT65xx */

#ifdef MT7601
	if (IS_MT7601(pAd))
		return;
#endif /* MT7601 */

	_RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, Offset, Value);
}

VOID RTMP_BBP_IO_WRITE8(
	PRTMP_ADAPTER pAd,
	UCHAR Offset,
	UINT8 Value,
	BOOLEAN FlgValidMCR)
{
#ifdef RT8592
	if (IS_RT8592(pAd))
		return;
#endif /* RT8592 */

#ifdef RT65xx
	if (IS_RT65XX(pAd))
		return;
#endif /* RT65xx */

#ifdef MT7601
	if (IS_MT7601(pAd))
		return;
#endif /* MT7601 */

	_RTMP_BBP_IO_WRITE8(pAd, Offset, Value, FlgValidMCR);
}
#endif /* VENDOR_FEATURE3_SUPPORT */


#ifdef RTMP_MAC_PCI
VOID CMDHandler(                                                                                                                                                
    IN PRTMP_ADAPTER pAd)                                                                                                                                       
{                                                                                                                                                               
	PCmdQElmt		cmdqelmt;                                                                                                                                       
	PUCHAR			pData;                                                                                                                                          
	NDIS_STATUS		NdisStatus = NDIS_STATUS_SUCCESS;                                                                                                               
/*	ULONG			Now = 0;*/
/*	NTSTATUS		ntStatus;*/
/*	unsigned long	IrqFlags;*/
	
	while (pAd && pAd->CmdQ.size > 0)	
	{                                                                                                                                                           
		NdisStatus = NDIS_STATUS_SUCCESS;
		                                                                                                                      
		NdisAcquireSpinLock(&pAd->CmdQLock);
		RTThreadDequeueCmd(&pAd->CmdQ, &cmdqelmt);
		NdisReleaseSpinLock(&pAd->CmdQLock);
		                                                                                                        
		if (cmdqelmt == NULL)                                                                                                                                   
			break; 
			                                                                                                                                             
		pData = cmdqelmt->buffer;                                      
#ifdef RELEASE_EXCLUDE
		DBGPRINT_RAW(RT_DEBUG_INFO, ("Cmd = %x\n", cmdqelmt->command));
#endif /* RELEASE_EXCLUDE */
		                                                                                         
		if(!(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST) || RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_HALT_IN_PROGRESS)))
		{
			switch (cmdqelmt->command)
			{
#ifdef CONFIG_AP_SUPPORT
				case CMDTHREAD_CHAN_RESCAN:
					DBGPRINT(RT_DEBUG_TRACE, ("cmd> Re-scan channel! \n"));

					pAd->CommonCfg.Channel = AP_AUTO_CH_SEL(pAd, ChannelAlgCCA);

#ifdef DOT11_N_SUPPORT
					/* If WMODE_CAP_N(phymode) and BW=40 check extension channel, after select channel  */
					N_ChannelCheck(pAd);
#endif /* DOT11_N_SUPPORT */

					DBGPRINT(RT_DEBUG_TRACE, ("cmd> Switch to %d! \n", pAd->CommonCfg.Channel));
					APStop(pAd);
					APStartUp(pAd);

#ifdef AP_QLOAD_SUPPORT
					QBSS_LoadAlarmResume(pAd);
#endif /* AP_QLOAD_SUPPORT */
					break;
#endif /* CONFIG_AP_SUPPORT */

				case CMDTHREAD_REG_HINT:
#ifdef LINUX
#ifdef RT_CFG80211_SUPPORT
					RT_CFG80211_CRDA_REG_HINT(pAd, pData, cmdqelmt->bufferlength);
#endif /* RT_CFG80211_SUPPORT */
#endif /* LINUX */
					break;

				case CMDTHREAD_REG_HINT_11D:
#ifdef LINUX
#ifdef RT_CFG80211_SUPPORT
					RT_CFG80211_CRDA_REG_HINT11D(pAd, pData, cmdqelmt->bufferlength);
#endif /* RT_CFG80211_SUPPORT */
#endif /* LINUX */
					break;

				case CMDTHREAD_SCAN_END:
#ifdef LINUX
#ifdef RT_CFG80211_SUPPORT
					RT_CFG80211_SCAN_END(pAd, FALSE);
#endif /* RT_CFG80211_SUPPORT */
#endif /* LINUX */
					break;

				case CMDTHREAD_CONNECT_RESULT_INFORM:
#ifdef LINUX
#ifdef RT_CFG80211_SUPPORT
					RT_CFG80211_CONN_RESULT_INFORM(pAd,
												pAd->MlmeAux.Bssid,
												pData, cmdqelmt->bufferlength,
												pData, cmdqelmt->bufferlength,
												1);
#endif /* RT_CFG80211_SUPPORT */
#endif /* LINUX */
					break;

				default:
					DBGPRINT(RT_DEBUG_ERROR, ("--> Control Thread !! ERROR !! Unknown(cmdqelmt->command=0x%x) !! \n", cmdqelmt->command));
					break;
			}
		}

		if (cmdqelmt->CmdFromNdis == TRUE)
		{
			if (cmdqelmt->buffer != NULL)
				os_free_mem(pAd, cmdqelmt->buffer);
			os_free_mem(pAd, cmdqelmt);
		}
		else
		{
			if ((cmdqelmt->buffer != NULL) && (cmdqelmt->bufferlength != 0))
				os_free_mem(pAd, cmdqelmt->buffer);
			os_free_mem(pAd, cmdqelmt);
		}
	}	/* end of while */
}
#endif /* RTMP_MAC_PCI */

VOID AntCfgInit(
IN  PRTMP_ADAPTER   pAd)
{
#ifdef RELEASE_EXCLUDE
	/* Because profile is read before efuse, so if profile didn't set up ant, it needs to set by efuse's setting. */
#endif

#ifdef ANT_DIVERSITY_SUPPORT
	DBGPRINT(RT_DEBUG_OFF, ("%s: RxAntDiversityCfg %d\n", __FUNCTION__, pAd->CommonCfg.RxAntDiversityCfg));

	/* determine EEPORM Ant Diversity Bit */
	if ((pAd->NicConfig2.word & 0x1800) == 0x800)
	{
		pAd->CommonCfg.bSWRxAntDiversity = TRUE;
		if (pAd->chipCap.FlgIsHwAntennaDiversitySup)
			pAd->CommonCfg.bHWRxAntDiversity = TRUE;
	}
#endif	/* ANT_DIVERSITY_SUPPORT */
	
#ifdef TXRX_SW_ANTDIV_SUPPORT
	/* EEPROM 0x34[15:12] = 0xF is invalid, 0x2~0x3 is TX/RX SW AntDiv */
	DBGPRINT(RT_DEBUG_OFF, ("%s: bTxRxSwAntDiv %d\n", __FUNCTION__, pAd->chipCap.bTxRxSwAntDiv));
	if (pAd->chipCap.bTxRxSwAntDiv)  
	{																	  
#ifdef ANT_DIVERSITY_SUPPORT
		/* if PPAD and TXRX AntDiv are both on, only enable PPAD */
		if ((pAd->CommonCfg.bHWRxAntDiversity) && (pAd->chipCap.FlgIsHwAntennaDiversitySup))
			pAd->chipCap.bTxRxSwAntDiv = FALSE;		/* for GPIO switch */
		else
			pAd->CommonCfg.bSWRxAntDiversity = TRUE; /* for sw diversity capability */
#endif /* ANT_DIVERSITY_SUPPORT */
		DBGPRINT(RT_DEBUG_OFF, ("Antenna word %X/%d, AntDiv %d\n", 
					pAd->Antenna.word, pAd->Antenna.field.BoardType, pAd->NicConfig2.field.AntDiversity));
	}
#endif /* TXRX_SW_ANTDIV_SUPPORT */

#ifdef ANT_DIVERSITY_SUPPORT
	/* Because profile read before EEPROM, so profile can not determine what kind od diversity enable, */
	/* so postpone to select SW/HW Diversity, HW has the higher priority */
	if (pAd->CommonCfg.RxAntDiversityCfg == ANT_DIVERSITY_ENABLE)
	{
		if (pAd->CommonCfg.bHWRxAntDiversity)	/* EEPROM setting */
			pAd->CommonCfg.RxAntDiversityCfg = ANT_HW_DIVERSITY_ENABLE;	/* profile, ioctl setting */
		else if (pAd->CommonCfg.bSWRxAntDiversity)	/* EEPROM setting */
			pAd->CommonCfg.RxAntDiversityCfg = ANT_SW_DIVERSITY_ENABLE;	/* profile, ioctl setting */
		else
			pAd->CommonCfg.RxAntDiversityCfg = ANT_DIVERSITY_DEFAULT; /* by EEPROM */
	}

	
	if (pAd->CommonCfg.RxAntDiversityCfg == ANT_DIVERSITY_DEFAULT)
#endif
	{
		if (pAd->NicConfig2.field.AntOpt== 1) /* ant selected by efuse */
		{	
			if (pAd->NicConfig2.field.AntDiversity == 0) /* main */
			{
				pAd->RxAnt.Pair1PrimaryRxAnt = 0;
				pAd->RxAnt.Pair1SecondaryRxAnt = 1;
			}
			else/* aux */
			{
				pAd->RxAnt.Pair1PrimaryRxAnt = 1;
				pAd->RxAnt.Pair1SecondaryRxAnt = 0;
			}
		}
		else if (pAd->NicConfig2.field.AntDiversity == 0) /* Ant div off: default ant is main */
		{
			pAd->RxAnt.Pair1PrimaryRxAnt = 0;
			pAd->RxAnt.Pair1SecondaryRxAnt = 1;
		}
		else if (pAd->NicConfig2.field.AntDiversity == 1)/* Ant div on */
#ifdef ANT_DIVERSITY_SUPPORT
			if (pAd->chipCap.FlgIsHwAntennaDiversitySup)
				pAd->CommonCfg.RxAntDiversityCfg = ANT_HW_DIVERSITY_ENABLE; 
#else
		{/* eeprom on, but sw ant div support is not enabled: default ant is main */
			pAd->RxAnt.Pair1PrimaryRxAnt = 0;
			pAd->RxAnt.Pair1SecondaryRxAnt = 1;
		}
#endif
	}

	DBGPRINT(RT_DEBUG_OFF, ("%s: primary/secondary ant %d/%d\n", 
					__FUNCTION__,
					pAd->RxAnt.Pair1PrimaryRxAnt,
					pAd->RxAnt.Pair1SecondaryRxAnt));
#ifdef ANT_DIVERSITY_SUPPORT
	DBGPRINT(RT_DEBUG_OFF, ("%s: RxAntDiv %d/%d\n", 
					__FUNCTION__,
					pAd->CommonCfg.bSWRxAntDiversity,
					pAd->CommonCfg.bHWRxAntDiversity));
#endif
}

#ifdef MICROWAVE_OVEN_SUPPORT
VOID NICUpdateRxStatusCnt1(
IN  PRTMP_ADAPTER   pAd,
IN  UCHAR	Idx)
{
	RX_STA_CNT1_STRUC   RxStaCnt1;

	RTMP_IO_READ32(pAd, RX_STA_CNT1, &RxStaCnt1.word);

	if (Idx < MLME_TASK_EXEC_MULTIPLE)
	{
		pAd->RalinkCounters.FalseCCACnt_100MS[Idx] = RxStaCnt1.field.FalseCca;
		pAd->RalinkCounters.PLCPErrCnt_100MS[Idx] = RxStaCnt1.field.PlcpErr;
	}
}

UINT32 NICSumFalseCCACnt(
IN  PRTMP_ADAPTER   pAd)
{
	UCHAR Idx;
	UINT32 FalseCCACnt = 0;

	for (Idx = 0; Idx < MLME_TASK_EXEC_MULTIPLE; Idx++)
		FalseCCACnt += pAd->RalinkCounters.FalseCCACnt_100MS[Idx];

	return FalseCCACnt;
}

UINT32 NICSumPLCPErrCnt(
IN  PRTMP_ADAPTER   pAd)
{
	UCHAR Idx;
	UINT32 PLCPErrCnt = 0;

	for (Idx = 0; Idx < MLME_TASK_EXEC_MULTIPLE; Idx++)
		PLCPErrCnt += pAd->RalinkCounters.PLCPErrCnt_100MS[Idx];

	return PLCPErrCnt;
}
#endif /* MICROWAVE_OVEN_SUPPORT */

