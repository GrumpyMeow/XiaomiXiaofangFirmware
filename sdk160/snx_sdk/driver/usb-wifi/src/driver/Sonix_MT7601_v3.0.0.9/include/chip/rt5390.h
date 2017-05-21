/****************************************************************************
 * Ralink Tech Inc.
 * 4F, No. 2 Technology 5th Rd.
 * Science-based Industrial Park
 * Hsin-chu, Taiwan, R.O.C.
 * (c) Copyright 2002, Ralink Technology, Inc.
 *
 * All rights reserved. Ralink's source code is an unpublished work and the
 * use of a copyright notice does not imply otherwise. This source code
 * contains confidential trade secret material of Ralink Tech. Any attemp
 * or participation in deciphering, decoding, reverse engineering or in any
 * way altering the source code is stricitly prohibited, unless the prior
 * written consent of Ralink Technology, Inc. is obtained.
 ****************************************************************************

    Module Name:
	rt5390.h
 
    Abstract:
 
    Revision History:
    Who          When          What
    ---------    ----------    ----------------------------------------------
 */

#ifndef __RT5390_H__
#define __RT5390_H__

#if defined(RT5370) || defined(RT5372) || defined(RT5390) || defined(RT5392)

#if 0
#ifndef RTMP_PCI_SUPPORT
#error "For RT5390, you should define the compile flag -DRTMP_PCI_SUPPORT"
#endif

#ifndef RTMP_MAC_PCI
#error "For RT5390, you should define the compile flag -DRTMP_MAC_PCI"
#endif
#endif

#ifndef RTMP_RF_RW_SUPPORT
#error "For RT5390, you should define the compile flag -DRTMP_RF_RW_SUPPORT"
#endif

#ifndef RT30xx
#error "For RT5390, you should define the compile flag -DRT30xx"
#endif

#ifdef CONFIG_STA_SUPPORT
#if defined(RT5390) || defined(RT5392)
#define PCIE_PS_SUPPORT
#endif /* defined(RT5390) || defined(RT5392) */
#endif /* CONFIG_STA_SUPPORT */
extern REG_PAIR RF5390RegTable[];
extern UCHAR NUM_RF_5390_REG_PARMS;
#if 0
#define RTMP_RF33_SHARED_MEM_SELECT(__pAd)							\
{																	\
	if (IS_RT5390(__pAd))											\
	{																\
		PBF_SYS_CTRL_STRUC __PbfSysCtrl = {{0}};					\
		RTMP_IO_READ32(__pAd, PBF_SYS_CTRL, &__PbfSysCtrl.word);	\
		__PbfSysCtrl.field.SHR_MSEL = 1;							\
		RTMP_IO_WRITE32(__pAd, PBF_SYS_CTRL, __PbfSysCtrl.word);	\
	}																\
}

#define RTMP_RF33_SHARED_MEM_DESELECT(__pAd)						\
{																	\
	if (IS_RT5390(__pAd))						\
	{																\
		PBF_SYS_CTRL_STRUC __PbfSysCtrl = {{0}};					\
		RTMP_IO_WRITE32(__pAd, BCN_OFFSET0, 0x18100800); /* 0x0000(00), 0x0200(08), 0x0400(10), 0x0600(18), 512B for each beacon */ \
		RTMP_IO_WRITE32(__pAd, BCN_OFFSET1, 0x38302820); /* 0x0800(20), 0x0A00(28), 0x0C00(30), 0x0E00(38), 512B for each beacon */ \
		RTMP_IO_READ32(__pAd, PBF_SYS_CTRL, &__PbfSysCtrl.word);		\
		__PbfSysCtrl.field.SHR_MSEL = 0;							\
		RTMP_IO_WRITE32(__pAd, PBF_SYS_CTRL, __PbfSysCtrl.word);		\
	}																\
}
//
// The trigger point of the high/low frequency
//
#define HIGH_FREQUENCY_TRIGGER_POINT_OFDM		20
#define LOW_FREQUENCY_TRIGGER_POINT_OFDM		-20
#define HIGH_FREQUENCY_TRIGGER_POINT_CCK		4
#define LOW_FREQUENCY_TRIGGER_POINT_CCK		-4

//
// The trigger point of decreasng/increasing the frequency offset
//
#define DECREASE_FREQUENCY_OFFSET_OFDM			10
#define INCREASE_FREQUENCY_OFFSET_OFDM			-10
#define DECREASE_FREQUENCY_OFFSET_CCK			2
#define INCREASE_FREQUENCY_OFFSET_CCK			-2

//
// Invalid frequency offset
//
#define INVALID_FREQUENCY_OFFSET			-128

//
// Frequency calibration period
//
#define FREQUENCY_CALIBRATION_PERIOD		100
//
// The frequency calibration control
//
typedef struct _FREQUENCY_CALIBRATION_CONTROL
{
	BOOLEAN bEnableFrequencyCalibration; // Enable the frequency calibration algorithm

	BOOLEAN bSkipFirstFrequencyCalibration; // Avoid calibrating frequency at the time the STA is just link-up

	BOOLEAN bApproachFrequency; // Approach the frequency

	CHAR AdaptiveFreqOffset; // Adaptive frequency offset
	CHAR LatestFreqOffsetOverBeacon; // Latest frequency offset from the beacon

	UCHAR BeaconPhyMode; // Beacon's PHY mode
} FREQUENCY_CALIBRATION_CONTROL, *PFREQUENCY_CALIBRATION_CONTROL;

//
// Invalid frequency offset
//
#define INVALID_FREQUENCY_OFFSET			-128

//
// The upperbound/lowerbound of the frequency offset
//
#define UPPERBOUND_OF_FREQUENCY_OFFSET		127
#define LOWERBOUND_OF_FREQUENCY_OFFSET	-127

//
// The trigger point of decreasng/increasing the frequency offset
//
#define DECREASE_FREQUENCY_OFFSET			3
#define INCREASE_FREQUENCY_OFFSET			-3

//
// Frequency calibration period
//
#define FREQUENCY_CALIBRATION_PERIOD		10
#endif

#ifdef CONFIG_STA_SUPPORT
#ifdef RTMP_MAC_PCI
#define PCIE_PS_SUPPORT
#endif // RTMP_MAC_PCI //
#endif // CONFIG_STA_SUPPORT //

#ifdef RTMP_FLASH_SUPPORT
#define EEPROM_DEFAULT_FILE_PATH                     "etc_ro/Wireless/RT2860AP/RT3092_PCIe_LNA_2T2R_ALC_V1_2.bin"
#define RF_OFFSET					0x48000
#endif // RTMP_FLASH_SUPPORT //
#if 0
#include "chip/mac_pci.h"
//nclude "chip/rt30xx.h"
#include "chip/rt33xx.h"
#endif 
#include "chip/rt30xx.h"

/* Device ID & Vendor ID, these values should match EEPROM value */

#define NIC5390_PCIe_DEVICE_ID	0x5390
#define NIC539F_PCIe_DEVICE_ID 	0x539F
#define NIC5392_PCIe_DEVICE_ID 	0x5392
#define NIC5360_PCI_DEVICE_ID   	0x5360
#define NIC5362_PCI_DEVICE_ID	0x5362

VOID RT5390HaltAction(
	IN struct _RTMP_ADAPTER			*pAd);


/* add by johnli, RF power sequence setup */
VOID RT5390LoadRFNormalModeSetup(
	IN struct _RTMP_ADAPTER			*pAd);

VOID RT5390LoadRFSleepModeSetup(
	IN struct _RTMP_ADAPTER			*pAd);

VOID RT5390ReverseRFSleepModeSetup(
	IN struct _RTMP_ADAPTER			*pAd,
	IN BOOLEAN			FlgIsInitState);
/* end johnli */


VOID RT5390_Init(
	IN struct _RTMP_ADAPTER			*pAd);

VOID NICInitRT5390BbpRegisters(
	IN struct _RTMP_ADAPTER		*pAd);

VOID NICInitRT5390MacRegisters(
	IN struct _RTMP_ADAPTER		*pAd);


VOID NICRestoreBBPValue(
	IN struct _RTMP_ADAPTER			*pAd,
	IN REG_PAIR *RegPair);


VOID RT5390_RxSensitivityTuning(
	IN struct _RTMP_ADAPTER		*pAd);

UCHAR RT5390_ChipAGCAdjust(
	IN struct _RTMP_ADAPTER		*pAd,
	IN CHAR						Rssi,
	IN UCHAR					OrigR66Value);

VOID RT5390_ChipBBPAdjust(
	IN struct _RTMP_ADAPTER		*pAd);

VOID RT5390_ChipSwitchChannel(
	IN struct _RTMP_ADAPTER 	*pAd,
	IN UCHAR					Channel,
	IN BOOLEAN					bScan);

VOID RT539x_AsicExtraPowerOverMAC(
	IN struct _RTMP_ADAPTER 	*pAd);

#ifdef RTMP_INTERNAL_TX_ALC

VOID RT5390_InitDesiredTSSITable(
	IN struct _RTMP_ADAPTER		*pAd);

INT RT5390_ATETssiCalibration(
	IN struct _RTMP_ADAPTER		*pAd,
	IN PSTRING					arg);

INT RT5390_ATETssiCalibrationExtend(
	IN struct _RTMP_ADAPTER		*pAd,
	IN PSTRING					arg);

VOID RT5390_AsicTxAlcGetAutoAgcOffset(
	IN struct _RTMP_ADAPTER		*pAd,
	IN PCHAR					pDeltaPwr,
	IN PCHAR					pTotalDeltaPwr,
	IN PCHAR					pAgcCompensate,
	IN PCHAR 					pDeltaPowerByBbpR1);

LONG Rounding(
	IN struct _RTMP_ADAPTER		*pAd,
	IN LONG Integer, 
	IN LONG Fraction, 
	IN LONG DenominatorOfTssiRatio);

BOOLEAN GetDesiredTssiAndCurrentTssi(
	IN 		struct _RTMP_ADAPTER		*pAd,
	IN OUT 	PCHAR 					pDesiredTssi, 
	IN OUT 	PCHAR 					pCurrentTssi);

#endif /* RTMP_INTERNAL_TX_ALC */

#ifdef RTMP_TEMPERATURE_COMPENSATION
INT RT5392_ATEReadExternalTSSI(
	IN struct _RTMP_ADAPTER		*pAd,
	IN PSTRING					arg);
#endif /* RTMP_TEMPERATURE_COMPENSATION */

VOID RT5390_ChipAGCInit(
	IN struct _RTMP_ADAPTER		*pAd,
	IN UCHAR					BandWidth);

VOID RT5392_AsicRecalBbpAgent(
	IN struct _RTMP_ADAPTER		*pAd);	

VOID RT5392_AsicResetBBPAgent(
	IN struct _RTMP_ADAPTER		*pAd);	


#endif /* defined(RT5370) || defined(RT5372) || defined(RT5390) || defined(RT5392) */

#endif /* __RT5390_H__ */
