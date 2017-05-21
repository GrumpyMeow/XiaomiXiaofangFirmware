/*

*/

#include "rt_config.h"


#define MDSM_NORMAL_TX_POWER							0x00
#define MDSM_DROP_TX_POWER_BY_6dBm						0x01
#define MDSM_DROP_TX_POWER_BY_12dBm					0x02
#define MDSM_ADD_TX_POWER_BY_6dBm						0x03
#define MDSM_BBP_R1_STATIC_TX_POWER_CONTROL_MASK		0x03

VOID AsicGetTxPowerOffset(RTMP_ADAPTER *pAd, ULONG *TxPwr)
{
	CONFIGURATION_OF_TX_POWER_CONTROL_OVER_MAC CfgOfTxPwrCtrlOverMAC;
	DBGPRINT(RT_DEBUG_INFO, ("-->AsicGetTxPowerOffset\n"));

	NdisZeroMemory(&CfgOfTxPwrCtrlOverMAC, sizeof(CfgOfTxPwrCtrlOverMAC));

	CfgOfTxPwrCtrlOverMAC.NumOfEntries = 5; /* MAC 0x1314, 0x1318, 0x131C, 0x1320 and 1324 */

#ifdef DOT11_VHT_AC
	if (pAd->CommonCfg.BBPCurrentBW == BW_80 &&
		pAd->CommonCfg.Channel > 14)
	{
		CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].MACRegisterOffset = TX_PWR_CFG_0;
		CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].RegisterValue = pAd->Tx80MPwrCfgABand[0];
		CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].MACRegisterOffset = TX_PWR_CFG_1;
		CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].RegisterValue = pAd->Tx80MPwrCfgABand[1];
		CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].MACRegisterOffset = TX_PWR_CFG_2;
		CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].RegisterValue = pAd->Tx80MPwrCfgABand[2];
		CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].MACRegisterOffset = TX_PWR_CFG_3;
		CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].RegisterValue = pAd->Tx80MPwrCfgABand[3];
		CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].MACRegisterOffset = TX_PWR_CFG_4;
		CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].RegisterValue = pAd->Tx80MPwrCfgABand[4];
	}
	else
#endif /* DOT11_VHT_AC */
	if (pAd->CommonCfg.BBPCurrentBW == BW_40)
	{
		if (pAd->CommonCfg.CentralChannel > 14)
		{
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].MACRegisterOffset = TX_PWR_CFG_0;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].RegisterValue = pAd->Tx40MPwrCfgABand[0];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].MACRegisterOffset = TX_PWR_CFG_1;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].RegisterValue = pAd->Tx40MPwrCfgABand[1];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].MACRegisterOffset = TX_PWR_CFG_2;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].RegisterValue = pAd->Tx40MPwrCfgABand[2];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].MACRegisterOffset = TX_PWR_CFG_3;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].RegisterValue = pAd->Tx40MPwrCfgABand[3];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].MACRegisterOffset = TX_PWR_CFG_4;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].RegisterValue = pAd->Tx40MPwrCfgABand[4];
		}
		else
		{
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].MACRegisterOffset = TX_PWR_CFG_0;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].RegisterValue = pAd->Tx40MPwrCfgGBand[0];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].MACRegisterOffset = TX_PWR_CFG_1;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].RegisterValue = pAd->Tx40MPwrCfgGBand[1];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].MACRegisterOffset = TX_PWR_CFG_2;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].RegisterValue = pAd->Tx40MPwrCfgGBand[2];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].MACRegisterOffset = TX_PWR_CFG_3;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].RegisterValue = pAd->Tx40MPwrCfgGBand[3];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].MACRegisterOffset = TX_PWR_CFG_4;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].RegisterValue = pAd->Tx40MPwrCfgGBand[4];
		}
	}
	else
	{
		if (pAd->CommonCfg.CentralChannel > 14)
		{
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].MACRegisterOffset = TX_PWR_CFG_0;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].RegisterValue = pAd->Tx20MPwrCfgABand[0];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].MACRegisterOffset = TX_PWR_CFG_1;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].RegisterValue = pAd->Tx20MPwrCfgABand[1];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].MACRegisterOffset = TX_PWR_CFG_2;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].RegisterValue = pAd->Tx20MPwrCfgABand[2];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].MACRegisterOffset = TX_PWR_CFG_3;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].RegisterValue = pAd->Tx20MPwrCfgABand[3];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].MACRegisterOffset = TX_PWR_CFG_4;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].RegisterValue = pAd->Tx20MPwrCfgABand[4];
		}
		else
		{
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].MACRegisterOffset = TX_PWR_CFG_0;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].RegisterValue = pAd->Tx20MPwrCfgGBand[0];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].MACRegisterOffset = TX_PWR_CFG_1;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[1].RegisterValue = pAd->Tx20MPwrCfgGBand[1];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].MACRegisterOffset = TX_PWR_CFG_2;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[2].RegisterValue = pAd->Tx20MPwrCfgGBand[2];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].MACRegisterOffset = TX_PWR_CFG_3;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[3].RegisterValue = pAd->Tx20MPwrCfgGBand[3];
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].MACRegisterOffset = TX_PWR_CFG_4;
			CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[4].RegisterValue = pAd->Tx20MPwrCfgGBand[4];
		}
	}

	NdisCopyMemory(TxPwr, (UCHAR *)&CfgOfTxPwrCtrlOverMAC, sizeof(CfgOfTxPwrCtrlOverMAC));

	DBGPRINT(RT_DEBUG_INFO, ("<--AsicGetTxPowerOffset\n"));
}


VOID AsicGetAutoAgcOffsetForExternalTxAlc(
	IN PRTMP_ADAPTER 			pAd,
	IN PCHAR 					pDeltaPwr,
	IN PCHAR 					pTotalDeltaPwr,
	IN PCHAR 					pAgcCompensate,
	IN PCHAR 					pDeltaPowerByBbpR1)
{
	BBP_R49_STRUC	BbpR49;
	BOOLEAN			bAutoTxAgc = FALSE;
	UCHAR			TssiRef, *pTssiMinusBoundary, *pTssiPlusBoundary, TxAgcStep, idx;
	PCHAR			pTxAgcCompensate = NULL;
	CHAR    			DeltaPwr = 0;

	DBGPRINT(RT_DEBUG_INFO, ("-->%s\n", __FUNCTION__));

	BbpR49.byte = 0;

	/* TX power compensation for temperature variation based on TSSI. Try every 4 second */
	if (pAd->Mlme.OneSecPeriodicRound % 4 == 0)
	{
		if (pAd->CommonCfg.Channel <= 14)
		{
			/* bg channel */
			bAutoTxAgc = pAd->bAutoTxAgcG;
			TssiRef = pAd->TssiRefG;
			pTssiMinusBoundary = &pAd->TssiMinusBoundaryG[0];
			pTssiPlusBoundary = &pAd->TssiPlusBoundaryG[0];
			TxAgcStep = pAd->TxAgcStepG;
			pTxAgcCompensate = &pAd->TxAgcCompensateG;
		}
		else
		{
			/* a channel */
			bAutoTxAgc = pAd->bAutoTxAgcA;
			TssiRef = pAd->TssiRefA;
			pTssiMinusBoundary = &pAd->TssiMinusBoundaryA[0];
			pTssiPlusBoundary = &pAd->TssiPlusBoundaryA[0];
			TxAgcStep = pAd->TxAgcStepA;
			pTxAgcCompensate = &pAd->TxAgcCompensateA;
		}

		if (bAutoTxAgc)
		{
			RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R49, &BbpR49.byte);

			/* TSSI representation */
			if (IS_RT3071(pAd) || IS_RT3390(pAd) || IS_RT3090A(pAd) || IS_RT3572(pAd)) /* 5-bits */
			{
				BbpR49.byte = (BbpR49.byte & 0x1F);
			}
				
			/* (p) TssiPlusBoundaryG[0] = 0 = (m) TssiMinusBoundaryG[0] */
			/* compensate: +4     +3   +2   +1    0   -1   -2   -3   -4 * steps */
			/* step value is defined in pAd->TxAgcStepG for tx power value */

			/* [4]+1+[4]   p4     p3   p2   p1   o1   m1   m2   m3   m4 */
			/* ex:         0x00 0x15 0x25 0x45 0x88 0xA0 0xB5 0xD0 0xF0
			    above value are examined in mass factory production */
			/*             [4]    [3]  [2]  [1]  [0]  [1]  [2]  [3]  [4] */

			/* plus (+) is 0x00 ~ 0x45, minus (-) is 0xa0 ~ 0xf0 */
			/* if value is between p1 ~ o1 or o1 ~ s1, no need to adjust tx power */
			/* if value is 0xa5, tx power will be -= TxAgcStep*(2-1) */

			if (BbpR49.byte > pTssiMinusBoundary[1])
			{
				/* Reading is larger than the reference value */
				/* Check for how large we need to decrease the Tx power */
				for (idx = 1; idx < 5; idx++)
				{
					if (BbpR49.byte <= pTssiMinusBoundary[idx])  /* Found the range */
						break;
				}
				/* The index is the step we should decrease, idx = 0 means there is nothing to compensate */
#ifdef RT3883
				if (IS_RT3883(pAd))
				{
					if ((idx == 5) && ((BbpR49.byte) >  pTssiMinusBoundary[4] + 8))
						idx += 1;
				}
#endif /* RT3883 */

				*pTxAgcCompensate = -(TxAgcStep * (idx-1));			
				DeltaPwr += (*pTxAgcCompensate);
				DBGPRINT(RT_DEBUG_TRACE, ("-- Tx Power, BBP R49=%x, TssiRef=%x, TxAgcStep=%x, step = -%d\n",
					                BbpR49.byte, TssiRef, TxAgcStep, idx-1));                    
			}
			else if (BbpR49.byte < pTssiPlusBoundary[1])
			{
				/* Reading is smaller than the reference value */
				/* Check for how large we need to increase the Tx power */
				for (idx = 1; idx < 5; idx++)
				{
					if (BbpR49.byte >= pTssiPlusBoundary[idx])   /* Found the range*/
						break;
				}
#ifdef RT3883
				if (IS_RT3883(pAd) && (idx == 5))
				{
					if ((BbpR49.byte) <  (pTssiPlusBoundary[4] - 16))
						idx += 2;
					else if ((BbpR49.byte) <  (pTssiPlusBoundary[4] - 8))
						idx += 1;
				}
#endif /* RT3883 */

				/* The index is the step we should increase, idx = 0 means there is nothing to compensate */
				*pTxAgcCompensate = TxAgcStep * (idx-1);
				DeltaPwr += (*pTxAgcCompensate);
				DBGPRINT(RT_DEBUG_TRACE, ("++ Tx Power, BBP R49=%x, TssiRef=%x, TxAgcStep=%x, step = +%d\n",
				                	BbpR49.byte, TssiRef, TxAgcStep, idx-1));
			}
			else
			{
				*pTxAgcCompensate = 0;
				DBGPRINT(RT_DEBUG_TRACE, ("   Tx Power, BBP R49=%x, TssiRef=%x, TxAgcStep=%x, step = +%d\n",
				                	BbpR49.byte, TssiRef, TxAgcStep, 0));
			}
		}
	}
	else
	{
		if (pAd->CommonCfg.Channel <= 14)
		{
			bAutoTxAgc = pAd->bAutoTxAgcG;
			pTxAgcCompensate = &pAd->TxAgcCompensateG;
		}
		else
		{
			bAutoTxAgc = pAd->bAutoTxAgcA;
			pTxAgcCompensate = &pAd->TxAgcCompensateA;
		}

		if (bAutoTxAgc)
			DeltaPwr += (*pTxAgcCompensate);
	}

#ifdef RT3883
	if (IS_RT3883(pAd) && (pAd->bTxPwrRangeExt))
		DeltaPwr -= 2;
#endif /* RT3883 */

	*pDeltaPwr = DeltaPwr;
	*pAgcCompensate = *pTxAgcCompensate;

	DBGPRINT(RT_DEBUG_INFO, ("<--%s\n", __FUNCTION__));
}


/*
	==========================================================================
	Description:
		Gives CCK TX rate 2 more dB TX power.
		This routine works only in LINK UP in INFRASTRUCTURE mode.

		calculate desired Tx power in RF R3.Tx0~5,	should consider -
		0. if current radio is a noisy environment (pAd->DrsCounters.fNoisyEnvironment)
		1. TxPowerPercentage
		2. auto calibration based on TSSI feedback
		3. extra 2 db for CCK
		4. -10 db upon very-short distance (AvgRSSI >= -40db) to AP

	NOTE: Since this routine requires the value of (pAd->DrsCounters.fNoisyEnvironment),
		it should be called AFTER MlmeDynamicTxRatSwitching()
	==========================================================================
 */

VOID AsicAdjustTxPower(
	IN PRTMP_ADAPTER pAd) 
{
	INT			i, j;
	CHAR 		Value;
	CHAR		Rssi = -127;
	CHAR		DeltaPwr = 0;
	CHAR		TxAgcCompensate = 0;
	CHAR		DeltaPowerByBbpR1 = 0; 
	CHAR		TotalDeltaPower = 0; /* (non-positive number) including the transmit power controlled by the MAC and the BBP R1 */
	CONFIGURATION_OF_TX_POWER_CONTROL_OVER_MAC CfgOfTxPwrCtrlOverMAC = {0};	
#ifdef SINGLE_SKU
	CHAR		TotalDeltaPowerOri = 0;
	UCHAR		SingleSKUBbpR1Offset = 0;
	ULONG		SingleSKUTotalDeltaPwr[MAX_TXPOWER_ARRAY_SIZE] = {0};
#endif /* SINGLE_SKU */

#ifdef RELEASE_EXCLUDE
	DBGPRINT(RT_DEBUG_INFO,("-->%s\n", __FUNCTION__));
#endif /* RELEASE_EXCLUDE */

#ifdef CONFIG_STA_SUPPORT
	if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_IDLE_RADIO_OFF))
		return;

	if (OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_DOZE) || 
#ifdef RTMP_MAC_PCI
		(pAd->bPCIclkOff == TRUE) || RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_IDLE_RADIO_OFF) ||
#endif /* RTMP_MAC_PCI */
		RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_BSS_SCAN_IN_PROGRESS))
		return;

	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	{
		if(INFRA_ON(pAd))
		{
			Rssi = RTMPMaxRssi(pAd, 
						   pAd->StaCfg.RssiSample.AvgRssi0, 
						   pAd->StaCfg.RssiSample.AvgRssi1, 
						   pAd->StaCfg.RssiSample.AvgRssi2);
		}
	}
#endif /* CONFIG_STA_SUPPORT */

	/* Get Tx rate offset table which from EEPROM 0xDEh ~ 0xEFh */
	RTMP_CHIP_ASIC_TX_POWER_OFFSET_GET(pAd, (PULONG)&CfgOfTxPwrCtrlOverMAC);
	/* Get temperature compensation delta power value */
	RTMP_CHIP_ASIC_AUTO_AGC_OFFSET_GET(
		pAd, &DeltaPwr, &TotalDeltaPower, &TxAgcCompensate, &DeltaPowerByBbpR1);

	DBGPRINT(RT_DEBUG_INFO, ("%s: DeltaPwr=%d, TotalDeltaPower=%d, TxAgcCompensate=%d, DeltaPowerByBbpR1=%d\n",
			__FUNCTION__,
			DeltaPwr,
			TotalDeltaPower,
			TxAgcCompensate,
			DeltaPowerByBbpR1));
		
	/* Get delta power based on the percentage specified from UI */
	//AsicPercentageDeltaPower(pAd, Rssi, &DeltaPwr,&DeltaPowerByBbpR1);
#ifdef BT_COEXISTENCE_SUPPORT
	TxPowerDown(pAd, Rssi, &DeltaPowerByBbpR1, &DeltaPwr);
#endif /* BT_COEXISTENCE_SUPPORT */

	/* The transmit power controlled by the BBP */
	TotalDeltaPower += DeltaPowerByBbpR1; 
	/* The transmit power controlled by the MAC */
	TotalDeltaPower += DeltaPwr; 	

#ifdef SINGLE_SKU
	if (pAd->CommonCfg.bSKUMode == TRUE)
	{
		/* Re calculate delta power while enabling Single SKU */
		GetSingleSkuDeltaPower(pAd, &TotalDeltaPower, (PULONG)&SingleSKUTotalDeltaPwr, &SingleSKUBbpR1Offset);
	
		TotalDeltaPowerOri = TotalDeltaPower;
	}
	else
#endif /* SINGLE_SKU */
	{
		AsicCompensatePowerViaBBP(pAd, &TotalDeltaPower);
	}			

#ifdef MT7601
	if ( IS_MT7601(pAd) )
		return;
#endif /* MT7601 */

	/* Power will be updated each 4 sec. */
	if (pAd->Mlme.OneSecPeriodicRound % 4 == 0)
	{
/*****************************************************************************/
		/* Set new Tx power for different Tx rates */
		for (i=0; i < CfgOfTxPwrCtrlOverMAC.NumOfEntries; i++)
		{
			TX_POWER_CONTROL_OVER_MAC_ENTRY *pTxPwrEntry;
			ULONG reg_val;

			pTxPwrEntry = &CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[i];
			reg_val = pTxPwrEntry->RegisterValue;
			if (reg_val != 0xffffffff)
			{	
				for (j=0; j<8; j++)
				{
					CHAR _upbound, _lowbound, t_pwr;
					BOOLEAN _bValid;

					_lowbound = 0;
					_bValid = TRUE;
											
					Value = (CHAR)((reg_val >> j*4) & 0x0F);
#ifdef SINGLE_SKU
					if (pAd->CommonCfg.bSKUMode == TRUE)
					{
						TotalDeltaPower = SingleSKUBbpR1Offset + TotalDeltaPowerOri - (CHAR)((SingleSKUTotalDeltaPwr[i] >> j*4) & 0x0F);	

						DBGPRINT(RT_DEBUG_INFO, ("%s: BbpR1Offset(%d) + TX ALC(%d) - SingleSKU[%d/%d](%d) = TotalDeltaPower(%d)\n",
							__FUNCTION__, SingleSKUBbpR1Offset,
							TotalDeltaPowerOri, i, j,
							(CHAR)((SingleSKUTotalDeltaPwr[i] >> j*4) & 0x0F),
							TotalDeltaPower));
					}
#endif /* SINGLE_SKU */

#if defined(RTMP_INTERNAL_TX_ALC) || defined(RTMP_TEMPERATURE_COMPENSATION)
					/* The upper bounds of MAC 0x1314 ~ 0x1324 are variable */
					if ((pAd->TxPowerCtrl.bInternalTxALC == TRUE)^(pAd->chipCap.bTempCompTxALC == TRUE))
					{
						switch (0x1314 + (i * 4))
						{
							case 0x1314: 
								_upbound = 0xe;
							break;

							case 0x1318: 
								_upbound = (j <= 3) ? 0xc : 0xe;
							break;

							case 0x131C: 
								_upbound = ((j == 0) || (j == 2) || (j == 3)) ? 0xc : 0xe;
							break;

							case 0x1320: 
								_upbound = (j == 1) ? 0xe : 0xc;
							break;

							case 0x1324: 
								_upbound = 0xc;
							break;

							default: 
							{
								/* do nothing */
								_bValid = FALSE;
								DBGPRINT(RT_DEBUG_ERROR, ("%s: Unknown register = 0x%x\n", __FUNCTION__, (0x1314 + (i * 4))));
							}
							break;
						}
					}
					else
#endif /* RTMP_INTERNAL_TX_ALC || RTMP_TEMPERATURE_COMPENSATION */
						_upbound = 0xc;

					if (_bValid)
					{
						t_pwr = Value + TotalDeltaPower;
						if (t_pwr < _lowbound)
							Value = _lowbound;
						else if (t_pwr > _upbound)
							Value = _upbound;
						else
							Value = t_pwr;
					}

					/* Fill new value into the corresponding MAC offset */
					reg_val  = (reg_val & ~(0x0000000F << j*4)) | (Value << j*4);
				}

				pTxPwrEntry->RegisterValue = reg_val;
				RTMP_IO_WRITE32(pAd, pTxPwrEntry->MACRegisterOffset, pTxPwrEntry->RegisterValue);

#ifdef RELEASE_EXCLUDE
				DBGPRINT(RT_DEBUG_INFO, ("%s: After compensation, Offset = 0x%04X, RegisterValue = 0x%08lX\n",
					__FUNCTION__, pTxPwrEntry->MACRegisterOffset, pTxPwrEntry->RegisterValue));
#endif /* RELEASE_EXCLUDE */
			}
		}
		
		/* Extra set MAC registers to compensate Tx power if any */
		RTMP_CHIP_ASIC_EXTRA_POWER_OVER_MAC(pAd);
	}

#ifdef RELEASE_EXCLUDE
	DBGPRINT(RT_DEBUG_INFO, ("<--%s\n", __FUNCTION__));
#endif /* RELEASE_EXCLUDE */
}


#ifdef SINGLE_SKU
VOID GetSingleSkuDeltaPower(
	IN 		PRTMP_ADAPTER 	pAd,
	IN 		PCHAR 			pTotalDeltaPower,
	INOUT 	PULONG			pSingleSKUTotalDeltaPwr,
	INOUT  	PUCHAR              	pSingleSKUBbpR1Offset) 
{
	INT		i, j;
	CHAR	Value;
	CHAR 	MinValue = 127;
	UCHAR	BbpR1 = 0;
	UCHAR  	TxPwrInEEPROM = 0xFF, CountryTxPwr = 0xFF, criterion;
	UCHAR   	AdjustMaxTxPwr[(MAX_TX_PWR_CONTROL_OVER_MAC_REGISTERS * 8)]; 
	CONFIGURATION_OF_TX_POWER_CONTROL_OVER_MAC CfgOfTxPwrCtrlOverMAC = {0};
	
	/* Get TX rate offset table which from EEPROM 0xDEh ~ 0xEFh */
	RTMP_CHIP_ASIC_TX_POWER_OFFSET_GET(pAd, (PULONG)&CfgOfTxPwrCtrlOverMAC);
		
	/* Handle regulatory max. TX power constraint */
	if (pAd->CommonCfg.Channel > 14) 
	{
		TxPwrInEEPROM = ((pAd->CommonCfg.DefineMaxTxPwr & 0xFF00) >> 8); /* 5G band */
	}
	else 
	{
		TxPwrInEEPROM = (pAd->CommonCfg.DefineMaxTxPwr & 0x00FF); /* 2.4G band */
	}

	CountryTxPwr = GetCuntryMaxTxPwr(pAd, pAd->CommonCfg.Channel); 

	/* Use OFDM 6M as the criterion */
	criterion = (UCHAR)((CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[0].RegisterValue & 0x000F0000) >> 16);

	DBGPRINT(RT_DEBUG_TRACE, ("%s: criterion=%d, TxPwrInEEPROM=%d, CountryTxPwr=%d\n", 
		__FUNCTION__, criterion, TxPwrInEEPROM, CountryTxPwr));

	/* Adjust max. TX power according to the relationship of TX power in EEPROM */
	for (i=0; i<CfgOfTxPwrCtrlOverMAC.NumOfEntries; i++)
	{
		if (i == 0)
		{
			for (j=0; j<8; j++)
			{
				Value = (CHAR)((CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[i].RegisterValue >> j*4) & 0x0F); 

				if (j < 4)
				{
					AdjustMaxTxPwr[i*8+j] = TxPwrInEEPROM + (Value - criterion) + 4; /* CCK has 4dBm larger than OFDM */
				}
				else
				{
					AdjustMaxTxPwr[i*8+j] = TxPwrInEEPROM + (Value - criterion);
				}

				DBGPRINT(RT_DEBUG_TRACE, ("%s: offset = 0x%04X, i/j=%d/%d, (Default)Value=%d, %d\n", 
					__FUNCTION__,
					CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[i].MACRegisterOffset,
					i, 
					j, 
					Value, 
					AdjustMaxTxPwr[i*8+j]));
			}
		}
		else
		{
			for (j=0; j<8; j++)
			{
				Value = (CHAR)((CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[i].RegisterValue >> j*4) & 0x0F);

				AdjustMaxTxPwr[i*8+j] = TxPwrInEEPROM + (Value - criterion);

				DBGPRINT(RT_DEBUG_TRACE, ("%s: offset = 0x%04X, i/j=%d/%d, (Default)Value=%d, %d\n", 
					__FUNCTION__,
					CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[i].MACRegisterOffset, 
					i, 
					j, 
					Value, 
					AdjustMaxTxPwr[i*8+j]));
			}
		}
	}

	/* Adjust TX power according to the relationship */
	for (i=0; i<CfgOfTxPwrCtrlOverMAC.NumOfEntries; i++)
	{
		if (CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[i].RegisterValue != 0xffffffff)
		{
			for (j=0; j<8; j++)
			{
				Value = (CHAR)((CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[i].RegisterValue >> j*4) & 0x0F);

				/* The TX power is larger than the regulatory, the power should be restrained */
				if (AdjustMaxTxPwr[i*8+j] > CountryTxPwr)
				{
					Value = (AdjustMaxTxPwr[i*8+j] - CountryTxPwr);
					
					if (Value > 0xF)
					{
						/* The output power is larger than Country Regulatory over 15dBm, the origianl design has overflow case */
						DBGPRINT(RT_DEBUG_ERROR,("%s: Value overflow - %d\n", __FUNCTION__, Value));
					}
					
					*(pSingleSKUTotalDeltaPwr+i) = (*(pSingleSKUTotalDeltaPwr+i) & ~(0x0000000F << j*4)) | (Value << j*4);

					DBGPRINT(RT_DEBUG_TRACE, ("%s: offset = 0x%04X, i/j=%d/%d, (Exceed)Value=%d, %d\n", 
						__FUNCTION__,
						CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[i].MACRegisterOffset, 
						i, 
						j, 
						Value, 
						AdjustMaxTxPwr[i*8+j]));
				}
				else
				{
					DBGPRINT(RT_DEBUG_TRACE, ("%s: offset = 0x%04X, i/j=%d/%d, Value=%d, %d, no change\n",
						__FUNCTION__,
						CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[i].MACRegisterOffset, 
						i, 
						j, 
						Value, 
						AdjustMaxTxPwr[i*8+j]));
				}
			}
		}
	}

	/* Calculate the min. TX power */
	for(i=0; i<CfgOfTxPwrCtrlOverMAC.NumOfEntries; i++)
	{
		if (CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[i].RegisterValue != 0xffffffff)
		{
			for (j=0; j<8; j++)
			{
				CHAR PwrChange;
				/* 
				   After Single SKU, each data rate offset power value is saved in TotalDeltaPwr[].
				   PwrChange will add SingleSKUDeltaPwr and TotalDeltaPwr[] for each data rate to calculate
				   the final adjust output power value which is saved in MAC Reg. and BBP_R1.
				*/
				
				/*   
				   Value / TxPwr[] is get from eeprom 0xDEh ~ 0xEFh and increase or decrease the  
				   20/40 Bandwidth Delta Value in eeprom 0x50h. 
				*/
				Value = (CHAR)((CfgOfTxPwrCtrlOverMAC.TxPwrCtrlOverMAC[i].RegisterValue >> j*4) & 0x0F); /* 0 ~ 15 */

				/* Fix the corner case of Single SKU read eeprom offset 0xF0h ~ 0xFEh which for BBP Instruction configuration */
				if (Value == 0xF)
					continue;

				/* Value_offset is current Pwr comapre with Country Regulation and need adjust delta value */
				PwrChange = (CHAR)((*(pSingleSKUTotalDeltaPwr+i) >> j*4) & 0x0F); /* 0 ~ 15 */
				PwrChange -= *pTotalDeltaPower;

				Value -= PwrChange;
				
				if (MinValue > Value)
					MinValue = Value;				
			}
		}
	}

	RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R1, &BbpR1);
	/* Depend on the min. TX power to adjust and prevent the value of MAC_TX_PWR_CFG less than 0 */
	if ((MinValue < 0) && (MinValue >= -6))
	{
		BbpR1 |= MDSM_DROP_TX_POWER_BY_6dBm;
		*pSingleSKUBbpR1Offset = 6;
	}
	else if ((MinValue < -6)&&(MinValue >= -12))
	{
		BbpR1 |= MDSM_DROP_TX_POWER_BY_12dBm;
		*pSingleSKUBbpR1Offset = 12;
	}
	else if (MinValue < -12)
	{
		DBGPRINT(RT_DEBUG_WARN, ("%s: ASIC limit..\n", __FUNCTION__));
		BbpR1 |= MDSM_DROP_TX_POWER_BY_12dBm;
		*pSingleSKUBbpR1Offset = 12;
	}

	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R1, BbpR1);

	DBGPRINT(RT_DEBUG_TRACE, ("%s: <After BBP R1> TotalDeltaPower = %d dBm, BbpR1 = 0x%02X \n", __FUNCTION__, *pTotalDeltaPower, BbpR1));
}
#endif /* SINGLE_SKU */


VOID AsicPercentageDeltaPower(
	IN 		PRTMP_ADAPTER 		pAd,
	IN		CHAR				Rssi,
	INOUT	PCHAR				pDeltaPwr,
	INOUT	PCHAR				pDeltaPowerByBbpR1) 
{
	/* 
		Calculate delta power based on the percentage specified from UI.
		E2PROM setting is calibrated for maximum TX power (i.e. 100%).
		We lower TX power here according to the percentage specified from UI.
	*/
	
	if (pAd->CommonCfg.TxPowerPercentage >= 100) /* AUTO TX POWER control */
	{
#ifdef CONFIG_STA_SUPPORT
		if ((pAd->OpMode == OPMODE_STA)
#ifdef P2P_SUPPORT
			&& (!P2P_GO_ON(pAd))
#endif /* P2P_SUPPORT */
		)
		{
			/* To patch high power issue with some APs, like Belkin N1.*/
			if (Rssi > -35)
			{
				*pDeltaPwr -= 12;
			}
			else if (Rssi > -40)
			{
				*pDeltaPwr -= 6;
			}
			else
				;
		}
#endif /* CONFIG_STA_SUPPORT */
	}
	else if (pAd->CommonCfg.TxPowerPercentage > 90) /* 91 ~ 100% & AUTO, treat as 100% in terms of mW */
		;
	else if (pAd->CommonCfg.TxPowerPercentage > 60) /* 61 ~ 90%, treat as 75% in terms of mW		 DeltaPwr -= 1; */
	{
		*pDeltaPwr -= 1;
	}
	else if (pAd->CommonCfg.TxPowerPercentage > 30) /* 31 ~ 60%, treat as 50% in terms of mW		 DeltaPwr -= 3; */
	{
		*pDeltaPwr -= 3;
	}
	else if (pAd->CommonCfg.TxPowerPercentage > 15) /* 16 ~ 30%, treat as 25% in terms of mW		 DeltaPwr -= 6; */
	{
		*pDeltaPowerByBbpR1 -= 6; /* -6 dBm */
	}
	else if (pAd->CommonCfg.TxPowerPercentage > 9) /* 10 ~ 15%, treat as 12.5% in terms of mW		 DeltaPwr -= 9; */
	{
		*pDeltaPowerByBbpR1 -= 6; /* -6 dBm */
		*pDeltaPwr -= 3;
	}
	else /* 0 ~ 9 %, treat as MIN(~3%) in terms of mW		 DeltaPwr -= 12; */
	{
		*pDeltaPowerByBbpR1 -= 12; /* -12 dBm */
	}
}


VOID AsicCompensatePowerViaBBP(
	IN 		PRTMP_ADAPTER 		pAd,
	INOUT	PCHAR				pTotalDeltaPower) 
{
	UCHAR mdsm_drop_pwr;
	
	DBGPRINT(RT_DEBUG_INFO, ("%s: <Before BBP R1> TotalDeltaPower = %d dBm\n", __FUNCTION__, *pTotalDeltaPower));

#ifdef MT7601
	if (IS_MT7601(pAd))
	{
#ifdef RELEASE_EXCLUDE
		/* 
			MT7601 not suggest modify BBP_R1 directly.
			Use MAC 0x13B0 and 0x13B4, the TX power is handled by MAC.
		*/
#endif /* RELEASE_EXCLUDE */
		return;
	}
#endif /* MT7601 */

	if (*pTotalDeltaPower <= -12)
	{
		*pTotalDeltaPower += 12;
		mdsm_drop_pwr = MDSM_DROP_TX_POWER_BY_12dBm;

		DBGPRINT(RT_DEBUG_INFO, ("%s: Drop the transmit power by 12 dBm (BBP R1)\n", __FUNCTION__));
	}
	else if ((*pTotalDeltaPower <= -6) && (*pTotalDeltaPower > -12))
	{
		*pTotalDeltaPower += 6;
		mdsm_drop_pwr = MDSM_DROP_TX_POWER_BY_6dBm;

		DBGPRINT(RT_DEBUG_INFO, ("%s: Drop the transmit power by 6 dBm (BBP R1)\n", __FUNCTION__));
	}
	else
	{
		/* Control the the transmit power by using the MAC only */
		mdsm_drop_pwr = MDSM_NORMAL_TX_POWER;
	}

#ifdef RT65xx
	if (IS_RT65XX(pAd))
	{
		UINT32 bbp_val = 0;

		RTMP_BBP_IO_READ32(pAd, TXBE_R4, &bbp_val);
		bbp_val &= (~0x3);
		bbp_val |= mdsm_drop_pwr;
		RTMP_BBP_IO_WRITE32(pAd, TXBE_R4, bbp_val);
		DBGPRINT(RT_DEBUG_INFO, ("%s: <After TXBE_R4> TotalDeltaPower = %d dBm, TXBE_R4 = 0x%0x\n", __FUNCTION__, *pTotalDeltaPower, bbp_val));
	}
	else
#endif /* RT65xx */
	{
		UCHAR	BbpR1 = 0;
	
		/* The BBP R1 controls the transmit power for all rates */
		RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R1, &BbpR1);
		BbpR1 &= ~MDSM_BBP_R1_STATIC_TX_POWER_CONTROL_MASK;	
		BbpR1 |= mdsm_drop_pwr;
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R1, BbpR1);
		
		DBGPRINT(RT_DEBUG_INFO, ("%s: <After BBP R1> TotalDeltaPower = %d dBm, BbpR1 = 0x%02X \n", __FUNCTION__, *pTotalDeltaPower, BbpR1));
	}
}


/*
	========================================================================
	
	Routine Description:
		Read initial Tx power per MCS and BW from EEPROM
		
	Arguments:
		Adapter						Pointer to our adapter

	Return Value:
		None

	IRQL = PASSIVE_LEVEL

	Note:
		
	========================================================================
*/
VOID RTMPReadTxPwrPerRate(RTMP_ADAPTER *pAd)
{
	ULONG		data, Adata, Gdata;
	USHORT		i, value, value2;
	USHORT		value_1, value_2, value_3, value_4;
	INT			Apwrdelta, Gpwrdelta;
	UCHAR		t1,t2,t3,t4;
	BOOLEAN		bApwrdeltaMinus = TRUE, bGpwrdeltaMinus = TRUE;


#ifdef RT3883
	if (IS_RT3883(pAd)) {
		RTMPRT3883ReadTxPwrPerRate(pAd);
		return;
	}
#endif /* RT3883 */

#ifdef RT2883
	if (IS_RT2883(pAd) && (pAd->RfIcType == RFIC_2853)) {
		RTMPRT2883ReadTxPwrPerRate(pAd);
		return;
	}
#endif /* RT2883 */

#ifdef RT8592
	if (IS_RT8592(pAd)) {
		RT85592ReadTxPwrPerRate(pAd);
		return;
	}
#endif /* RT8592 */

#ifdef RT65xx
	if (IS_RT6590(pAd)) {
		RT6590ReadTxPwrPerRate(pAd);
		return;
	}
#endif /* RT65xx */

#ifdef RT3593
	if (IS_RT3593(pAd))
	{
		RTMPReadTxPwrPerRateExt(pAd);
		return;
	}
#endif /* RT3593 */

#ifdef MT7601
	if (IS_MT7601(pAd)) {
		MT7601_ReadTxPwrPerRate(pAd);
		return;
	}
#endif /* MT7601 */

	/* For default one, go here!! */
	{	
		
		/* Get power delta for 20MHz and 40MHz.*/
		DBGPRINT(RT_DEBUG_TRACE, ("Txpower per Rate\n"));
		RT28xx_EEPROM_READ16(pAd, EEPROM_TXPOWER_DELTA, value2);
		Apwrdelta = 0;
		Gpwrdelta = 0;

		if ((value2 & 0xff) != 0xff)
		{
			if ((value2 & 0x80))
				Gpwrdelta = (value2&0xf);
			
			if ((value2 & 0x40))
				bGpwrdeltaMinus = FALSE;
			else
				bGpwrdeltaMinus = TRUE;
		}
		if ((value2 & 0xff00) != 0xff00)
		{
			if ((value2 & 0x8000))
				Apwrdelta = ((value2&0xf00)>>8);

			if ((value2 & 0x4000))
				bApwrdeltaMinus = FALSE;
			else
				bApwrdeltaMinus = TRUE;
		}	
		DBGPRINT(RT_DEBUG_TRACE, ("Gpwrdelta = %x, Apwrdelta = %x .\n", Gpwrdelta, Apwrdelta));

		
		/* Get Txpower per MCS for 20MHz in 2.4G.*/
		
		for (i=0; i<5; i++)
		{
			RT28xx_EEPROM_READ16(pAd, EEPROM_TXPOWER_BYRATE_20MHZ_2_4G + i*4, value);
			data = value;

			/* use value_1 ~ value_4 for code size reduce */
			value_1 = value&0xf;
			value_2 = (value&0xf0)>>4;
			value_3 = (value&0xf00)>>8;
			value_4 = (value&0xf000)>>12;

			if (bApwrdeltaMinus == FALSE)
			{
				t1 = value_1+(Apwrdelta);
				if (t1 > 0xf)
					t1 = 0xf;
				t2 = value_2+(Apwrdelta);
				if (t2 > 0xf)
					t2 = 0xf;
				t3 = value_3+(Apwrdelta);
				if (t3 > 0xf)
					t3 = 0xf;
				t4 = value_4+(Apwrdelta);
				if (t4 > 0xf)
					t4 = 0xf;
			}
			else
			{
				if (value_1 > Apwrdelta)
					t1 = value_1-(Apwrdelta);
				else
					t1 = 0;
				if (value_2 > Apwrdelta)
					t2 = value_2-(Apwrdelta);
				else
					t2 = 0;
				if (value_3 > Apwrdelta)
					t3 = value_3-(Apwrdelta);
				else
					t3 = 0;
				if (value_4 > Apwrdelta)
					t4 = value_4-(Apwrdelta);
				else
					t4 = 0;
			}				
			Adata = t1 + (t2<<4) + (t3<<8) + (t4<<12);
			if (bGpwrdeltaMinus == FALSE)
			{
				t1 = value_1+(Gpwrdelta);
				if (t1 > 0xf)
					t1 = 0xf;
				t2 = value_2+(Gpwrdelta);
				if (t2 > 0xf)
					t2 = 0xf;
				t3 = value_3+(Gpwrdelta);
				if (t3 > 0xf)
					t3 = 0xf;
				t4 = value_4+(Gpwrdelta);
				if (t4 > 0xf)
					t4 = 0xf;
			}
			else
			{
				if (value_1 > Gpwrdelta)
					t1 = value_1-(Gpwrdelta);
				else
					t1 = 0;
				if (value_2 > Gpwrdelta)
					t2 = value_2-(Gpwrdelta);
				else
					t2 = 0;
				if (value_3 > Gpwrdelta)
					t3 = value_3-(Gpwrdelta);
				else
					t3 = 0;
				if (value_4 > Gpwrdelta)
					t4 = value_4-(Gpwrdelta);
				else
					t4 = 0;
			}				
			Gdata = t1 + (t2<<4) + (t3<<8) + (t4<<12);
			
			RT28xx_EEPROM_READ16(pAd, EEPROM_TXPOWER_BYRATE_20MHZ_2_4G + i*4 + 2, value);

			/* use value_1 ~ value_4 for code size reduce */
			value_1 = value&0xf;
			value_2 = (value&0xf0)>>4;
			value_3 = (value&0xf00)>>8;
			value_4 = (value&0xf000)>>12;

			if (bApwrdeltaMinus == FALSE)
			{
				t1 = value_1+(Apwrdelta);
				if (t1 > 0xf)
					t1 = 0xf;
				t2 = value_2+(Apwrdelta);
				if (t2 > 0xf)
					t2 = 0xf;
				t3 = value_3+(Apwrdelta);
				if (t3 > 0xf)
					t3 = 0xf;
				t4 = value_4+(Apwrdelta);
				if (t4 > 0xf)
					t4 = 0xf;
			}
			else
			{
				if (value_1 > Apwrdelta)
					t1 = value_1-(Apwrdelta);
				else
					t1 = 0;
				if (value_2 > Apwrdelta)
					t2 = value_2-(Apwrdelta);
				else
					t2 = 0;
				if (value_3 > Apwrdelta)
					t3 = value_3-(Apwrdelta);
				else
					t3 = 0;
				if (value_4 > Apwrdelta)
					t4 = value_4-(Apwrdelta);
				else
					t4 = 0;
			}				
			Adata |= ((t1<<16) + (t2<<20) + (t3<<24) + (t4<<28));
			if (bGpwrdeltaMinus == FALSE)
			{
				t1 = value_1+(Gpwrdelta);
				if (t1 > 0xf)
					t1 = 0xf;
				t2 = value_2+(Gpwrdelta);
				if (t2 > 0xf)
					t2 = 0xf;
				t3 = value_3+(Gpwrdelta);
				if (t3 > 0xf)
					t3 = 0xf;
				t4 = value_4+(Gpwrdelta);
				if (t4 > 0xf)
					t4 = 0xf;
			}
			else
			{
				if (value_1 > Gpwrdelta)
					t1 = value_1-(Gpwrdelta);
				else
					t1 = 0;
				if (value_2 > Gpwrdelta)
					t2 = value_2-(Gpwrdelta);
				else
					t2 = 0;
				if (value_3 > Gpwrdelta)
					t3 = value_3-(Gpwrdelta);
				else
					t3 = 0;
				if (value_4 > Gpwrdelta)
					t4 = value_4-(Gpwrdelta);
				else
					t4 = 0;
			}				
			Gdata |= ((t1<<16) + (t2<<20) + (t3<<24) + (t4<<28));
			data |= (value<<16);

			/* For 20M/40M Power Delta issue */		
			pAd->Tx20MPwrCfgABand[i] = data;
			pAd->Tx20MPwrCfgGBand[i] = data;
			pAd->Tx40MPwrCfgABand[i] = Adata;
			pAd->Tx40MPwrCfgGBand[i] = Gdata;
			
			if (data != 0xffffffff)
				RTMP_IO_WRITE32(pAd, TX_PWR_CFG_0 + i*4, data);
			DBGPRINT_RAW(RT_DEBUG_TRACE, ("20MHz BW, 2.4G band-%lx,  Adata = %lx,  Gdata = %lx \n", data, Adata, Gdata));
		}
	}

	/* Extra set MAC registers to compensate Tx power if any */
	RTMP_CHIP_ASIC_EXTRA_POWER_OVER_MAC(pAd);

}


/*
	========================================================================
	
	Routine Description:
		Read initial channel power parameters from EEPROM
		
	Arguments:
		Adapter						Pointer to our adapter

	Return Value:
		None

	IRQL = PASSIVE_LEVEL

	Note:
		
	========================================================================
*/
VOID RTMPReadChannelPwr(RTMP_ADAPTER *pAd)
{
	UINT32					i, choffset;
	EEPROM_TX_PWR_STRUC	    Power;
	EEPROM_TX_PWR_STRUC	    Power2;
#if (defined(RT30xx) && defined(RTMP_MAC_PCI)) || defined(RT3593)
	UCHAR Tx0ALC = 0, Tx1ALC = 0, Tx0FinePowerCtrl = 0, Tx1FinePowerCtrl = 0;
#endif /* (defined(RT30xx) && defined(RTMP_MAC_PCI)) || defined(RT3593) */
#ifdef RT3593
	EEPROM_TX_PWR_STRUC	    Power3;
/*	UCHAR Tx0ALC = 0, Tx1ALC = 0, Tx2ALC = 0, Tx0FinePowerCtrl = 0, Tx1FinePowerCtrl = 0, Tx2FinePowerCtrl = 0*/;
	UCHAR  Tx2ALC = 0, Tx2FinePowerCtrl = 0;
	
	EEPROM_ANTENNA_STRUC NICConfig0 = {{ 0 }};

	RT28xx_EEPROM_READ16(pAd, EEPROM_NIC1_OFFSET, NICConfig0.word);

	DBGPRINT(RT_DEBUG_TRACE, ("%s: NICConfig0.field.TxPath = %d, NICConfig0.field.RxPath = %d\n", 
		__FUNCTION__, 
		NICConfig0.field.TxPath, 
		NICConfig0.field.RxPath));
#endif /* RT3593 */

	/* Read Tx power value for all channels*/
	/* Value from 1 - 0x7f. Default value is 24.*/
	/* Power value : 2.4G 0x00 (0) ~ 0x1F (31)*/
	/*             : 5.5G 0xF9 (-7) ~ 0x0F (15)*/

	/* 0. 11b/g, ch1 - ch 14*/
	for (i = 0; i < 7; i++)
	{
#ifdef RT30xx
#ifdef RTMP_MAC_PCI
		/* Tx power control over RF R12, RF R13 and BBP R109*/
		if ((IS_RT3090A(pAd) || IS_RT3390(pAd)) && pAd->infType==RTMP_DEV_INF_PCIE)
		{
			RT28xx_EEPROM_READ16(pAd, EEPROM_G_TX_PWR_OFFSET + i * 2, Power.word);
			RT28xx_EEPROM_READ16(pAd, EEPROM_G_TX2_PWR_OFFSET + i * 2, Power2.word);
			pAd->TxPower[i * 2].Channel = i * 2 + 1;
			pAd->TxPower[i * 2 + 1].Channel = i * 2 + 2;

			
			/* Tx0 power control*/
			
			Tx0ALC = GET_TX_ALC_BIT_MASK & Power.field.Byte0;
			Tx0FinePowerCtrl = ((GET_TX_FINE_POWER_CTRL_BIT_MASK & Power.field.Byte0) >> NUMBER_OF_BITS_FOR_TX_ALC);

			if (IS_RT3390(pAd))
			{
				pAd->TxPower[i * 2].Power = Power.field.Byte0;
			}
			else
			{
				if (Tx0ALC > 31)
				{
					pAd->TxPower[i * 2].Power = DEFAULT_RF_TX_POWER;
				}
				else
				{
					pAd->TxPower[i * 2].Power = Tx0ALC;
				}
			}	

			if (Tx0FinePowerCtrl > 4)
			{
				pAd->TxPower[i * 2].Tx0FinePowerCtrl = DEFAULT_BBP_TX_FINE_POWER_CTRL;
			}
			else
			{
				pAd->TxPower[i * 2].Tx0FinePowerCtrl = Tx0FinePowerCtrl;
			}

			Tx0ALC = GET_TX_ALC_BIT_MASK & Power.field.Byte1;
			Tx0FinePowerCtrl = ((GET_TX_FINE_POWER_CTRL_BIT_MASK & Power.field.Byte1) >> NUMBER_OF_BITS_FOR_TX_ALC);

			if (IS_RT3390(pAd))
			{
				pAd->TxPower[i * 2 + 1].Power = Power.field.Byte1;
			}
			else
			{
			if (Tx0ALC > 31)
			{
				pAd->TxPower[i * 2 + 1].Power = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2 + 1].Power = Tx0ALC;
			}
			}

			if (Tx0FinePowerCtrl > 4)
			{
				pAd->TxPower[i * 2 + 1].Tx0FinePowerCtrl = DEFAULT_BBP_TX_FINE_POWER_CTRL;
			}
			else
			{
				pAd->TxPower[i * 2 + 1].Tx0FinePowerCtrl = Tx0FinePowerCtrl;
			}

			
			/* Tx1 power control*/
			
			if (pAd->Antenna.field.TxPath >= 2)
			{
				Tx1ALC = GET_TX_ALC_BIT_MASK & Power2.field.Byte0;
				Tx1FinePowerCtrl = ((GET_TX_FINE_POWER_CTRL_BIT_MASK & Power2.field.Byte0) >> NUMBER_OF_BITS_FOR_TX_ALC);

				if (Tx1ALC > 31)
				{
					pAd->TxPower[i * 2].Power2 = DEFAULT_RF_TX_POWER;
				}
				else
				{
					pAd->TxPower[i * 2].Power2 = Tx1ALC;
				}

				if (Tx1FinePowerCtrl > 4)
				{
					pAd->TxPower[i * 2].Tx1FinePowerCtrl = DEFAULT_BBP_TX_FINE_POWER_CTRL;
				}
				else
				{
					pAd->TxPower[i * 2].Tx1FinePowerCtrl = Tx1FinePowerCtrl;
				}

				Tx1ALC = GET_TX_ALC_BIT_MASK & Power2.field.Byte1;
				Tx1FinePowerCtrl = ((GET_TX_FINE_POWER_CTRL_BIT_MASK & Power2.field.Byte1) >> NUMBER_OF_BITS_FOR_TX_ALC);

				if (Tx1ALC > 31)
				{
					pAd->TxPower[i * 2 + 1].Power2 = DEFAULT_RF_TX_POWER;
				}
				else
				{
					pAd->TxPower[i * 2 + 1].Power2 = Tx1ALC;
				}

				if (Tx1FinePowerCtrl > 4)
				{
					pAd->TxPower[i * 2 + 1].Tx1FinePowerCtrl = DEFAULT_BBP_TX_FINE_POWER_CTRL;
				}
				else
				{
					pAd->TxPower[i * 2 + 1].Tx1FinePowerCtrl = Tx1FinePowerCtrl;
				}
			}

			DBGPRINT(RT_DEBUG_TRACE, ("%s: pAd->TxPower[%d].Power = 0x%02X, pAd->TxPower[%d].Tx0FinePowerCtrl = 0x%02X, pAd->TxPower[%d].Power = 0x%02X, pAd->TxPower[%d].Tx0FinePowerCtrl = 0x%02X, pAd->TxPower[%d].Power2 = 0x%02X, pAd->TxPower[%d].Tx1FinePowerCtrl = 0x%02X, pAd->TxPower[%d].Power2 = 0x%02X, pAd->TxPower[%d].Tx1FinePowerCtrl = 0x%02X, \n", 
				__FUNCTION__, 
				i * 2, 
				pAd->TxPower[i * 2].Power, 
				i * 2, 
				pAd->TxPower[i * 2].Tx0FinePowerCtrl, 
				i * 2 + 1, 
				pAd->TxPower[i * 2 + 1].Power, 
				i * 2 + 1, 
				pAd->TxPower[i * 2 + 1].Tx0FinePowerCtrl, 
				i * 2, 
				pAd->TxPower[i * 2].Power2, 
				i * 2, 
				pAd->TxPower[i * 2].Tx1FinePowerCtrl, 
				i * 2 + 1, 
				pAd->TxPower[i * 2 + 1].Power2, 
				i * 2 + 1, 
				pAd->TxPower[i * 2 + 1].Tx1FinePowerCtrl));
		}
		else /* Tx power control over RF R12 and RF R13*/
#endif /* RTMP_MAC_PCI */
#if defined(RT5370) || defined(RT5372) || defined(RT5390) || defined(RT5392) || defined(RT5592) || defined(RT3290) || defined(RT65xx)
		if (IS_RT5390(pAd) || IS_RT5392(pAd) || IS_RT5592(pAd) || IS_RT3290(pAd) || IS_RT65XX(pAd) )
		{
			 RT28xx_EEPROM_READ16(pAd, EEPROM_G_TX_PWR_OFFSET + i * 2,Power.word);
			if (IS_RT5392(pAd) || IS_RT5592(pAd))
			{
				RT28xx_EEPROM_READ16(pAd, EEPROM_G_TX2_PWR_OFFSET + i * 2,Power2.word);
			}
			pAd->TxPower[i * 2].Channel = i * 2 + 1;
			pAd->TxPower[i * 2 + 1].Channel = i * 2 + 2;
	
			if ((Power.field.Byte0 > 0x27) || (Power.field.Byte0 < 0))
			{
				pAd->TxPower[i * 2].Power = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2].Power = Power.field.Byte0;
			}
	
			if ((Power.field.Byte1 > 0x27) || (Power.field.Byte1 < 0))
			{
				pAd->TxPower[i * 2 + 1].Power = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2 + 1].Power = Power.field.Byte1;
			}
	
			if (IS_RT5392(pAd) || IS_RT5592(pAd))
			{
				if ((Power2.field.Byte0 > 0x27) || (Power2.field.Byte0 < 0))
				{
					pAd->TxPower[i * 2].Power2 = DEFAULT_RF_TX_POWER;
				}
				else
				{
					pAd->TxPower[i * 2].Power2 = Power2.field.Byte0;
				}
		
				if ((Power2.field.Byte1 > 0x27) || (Power2.field.Byte1 < 0))
				{
					pAd->TxPower[i * 2 + 1].Power2 = DEFAULT_RF_TX_POWER;
				}
				else
				{
					pAd->TxPower[i * 2 + 1].Power2 = Power2.field.Byte1;
				}
			}
			
			DBGPRINT(RT_DEBUG_TRACE, ("%s: TxPower[%d].Power = 0x%02X, TxPower[%d].Power = 0x%02X\n", 
				__FUNCTION__, 
				i * 2, 
				pAd->TxPower[i * 2].Power, 
				i * 2 + 1, 
				pAd->TxPower[i * 2 + 1].Power));
			
			if (IS_RT5392(pAd) || IS_RT5592(pAd))
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: TxPower[%d].Power2 = 0x%02X, TxPower[%d].Power2 = 0x%02X\n", 
					__FUNCTION__, 
					i * 2, 
					pAd->TxPower[i * 2].Power2, 
					i * 2 + 1, 
					pAd->TxPower[i * 2 + 1].Power2));
			}
		}
		else
#endif /* defined(RT5370) || defined(RT5372) || defined(RT5390) || defined(RT5392) || defined(RT5592) || defined(RT65xx) */
#endif /* RT30xx */

#ifdef RT3593
		if (IS_RT3593(pAd))
		{
			if (NICConfig0.field.TxPath == 3)
			{
				RT28xx_EEPROM_READ16(pAd, (EEPROM_EXT_TX0_OVER_2DOT4G + (i * 2)), Power.word);
				RT28xx_EEPROM_READ16(pAd, (EEPROM_EXT_TX1_OVER_2DOT4G + (i * 2)), Power2.word);
				RT28xx_EEPROM_READ16(pAd, (EEPROM_EXT_TX2_OVER_2DOT4G + (i * 2)), Power3.word);
			}
			else
			{
				RT28xx_EEPROM_READ16(pAd, (EEPROM_G_TX_PWR_OFFSET + i * 2), Power.word);
				RT28xx_EEPROM_READ16(pAd, (EEPROM_G_TX2_PWR_OFFSET + i * 2), Power2.word);
			}
			
			pAd->TxPower[i * 2].Channel = i * 2 + 1;
			pAd->TxPower[i * 2 + 1].Channel = i * 2 + 2;

			
			/* Tx0 power control*/
			
			Tx0ALC = GET_TX_ALC_BIT_MASK & Power.field.Byte0;
			Tx0FinePowerCtrl = ((GET_TX_FINE_POWER_CTRL_BIT_MASK & Power.field.Byte0) >> NUMBER_OF_BITS_FOR_TX_ALC);

			if (Tx0ALC > 31)
			{
				pAd->TxPower[i * 2].Power = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2].Power = Tx0ALC;
			}

			if (Tx0FinePowerCtrl > 4)
			{
				pAd->TxPower[i * 2].Tx0FinePowerCtrl = DEFAULT_BBP_TX_FINE_POWER_CTRL;
			}
			else
			{
				pAd->TxPower[i * 2].Tx0FinePowerCtrl = Tx0FinePowerCtrl;
			}

			Tx0ALC = GET_TX_ALC_BIT_MASK & Power.field.Byte1;
			Tx0FinePowerCtrl = ((GET_TX_FINE_POWER_CTRL_BIT_MASK & Power.field.Byte1) >> NUMBER_OF_BITS_FOR_TX_ALC);

			if (Tx0ALC > 31)
			{
				pAd->TxPower[i * 2 + 1].Power = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2 + 1].Power = Tx0ALC;
			}

			if (Tx0FinePowerCtrl > 4)
			{
				pAd->TxPower[i * 2 + 1].Tx0FinePowerCtrl = DEFAULT_BBP_TX_FINE_POWER_CTRL;
			}
			else
			{
				pAd->TxPower[i * 2 + 1].Tx0FinePowerCtrl = Tx0FinePowerCtrl;
			}

			
			/* Tx1 power control*/
			
			if (NICConfig0.field.TxPath >= 2)
			{
				Tx1ALC = GET_TX_ALC_BIT_MASK & Power2.field.Byte0;
				Tx1FinePowerCtrl = ((GET_TX_FINE_POWER_CTRL_BIT_MASK & Power2.field.Byte0) >> NUMBER_OF_BITS_FOR_TX_ALC);

				if (Tx1ALC > 31)
				{
					pAd->TxPower[i * 2].Power2 = DEFAULT_RF_TX_POWER;
				}
				else
				{
					pAd->TxPower[i * 2].Power2 = Tx1ALC;
				}

				if (Tx1FinePowerCtrl > 4)
				{
					pAd->TxPower[i * 2].Tx1FinePowerCtrl = DEFAULT_BBP_TX_FINE_POWER_CTRL;
				}
				else
				{
					pAd->TxPower[i * 2].Tx1FinePowerCtrl = Tx1FinePowerCtrl;
				}

				Tx1ALC = GET_TX_ALC_BIT_MASK & Power2.field.Byte1;
				Tx1FinePowerCtrl = ((GET_TX_FINE_POWER_CTRL_BIT_MASK & Power2.field.Byte1) >> NUMBER_OF_BITS_FOR_TX_ALC);

				if (Tx1ALC > 31)
				{
					pAd->TxPower[i * 2 + 1].Power2 = DEFAULT_RF_TX_POWER;
				}
				else
				{
					pAd->TxPower[i * 2 + 1].Power2 = Tx1ALC;
				}

				if (Tx1FinePowerCtrl > 4)
				{
					pAd->TxPower[i * 2 + 1].Tx1FinePowerCtrl = DEFAULT_BBP_TX_FINE_POWER_CTRL;
				}
				else
				{
					pAd->TxPower[i * 2 + 1].Tx1FinePowerCtrl = Tx1FinePowerCtrl;
				}
			}

			DBGPRINT(RT_DEBUG_TRACE, ("%s: pAd->TxPower[%d].Power = 0x%02X, pAd->TxPower[%d].Tx0FinePowerCtrl = 0x%02X, pAd->TxPower[%d].Power = 0x%02X, pAd->TxPower[%d].Tx0FinePowerCtrl = 0x%02X, pAd->TxPower[%d].Power2 = 0x%02X, pAd->TxPower[%d].Tx1FinePowerCtrl = 0x%02X, pAd->TxPower[%d].Power2 = 0x%02X, pAd->TxPower[%d].Tx1FinePowerCtrl = 0x%02X, \n", 
				__FUNCTION__, 
				i * 2, 
				pAd->TxPower[i * 2].Power, 
				i * 2, 
				pAd->TxPower[i * 2].Tx0FinePowerCtrl, 
				i * 2 + 1, 
				pAd->TxPower[i * 2 + 1].Power, 
				i * 2 + 1, 
				pAd->TxPower[i * 2 + 1].Tx0FinePowerCtrl, 
				i * 2, 
				pAd->TxPower[i * 2].Power2, 
				i * 2, 
				pAd->TxPower[i * 2].Tx1FinePowerCtrl, 
				i * 2 + 1, 
				pAd->TxPower[i * 2 + 1].Power2, 
				i * 2 + 1, 
				pAd->TxPower[i * 2 + 1].Tx1FinePowerCtrl));

			
			/* Tx2 power control*/
			
			if (NICConfig0.field.TxPath == 3)
			{
				Tx2ALC = GET_TX_ALC_BIT_MASK & Power3.field.Byte0;
				Tx2FinePowerCtrl = ((GET_TX_FINE_POWER_CTRL_BIT_MASK & Power3.field.Byte0) >> NUMBER_OF_BITS_FOR_TX_ALC);

				if (Tx2ALC > 31)
				{
					pAd->TxPower[i * 2].Power3 = DEFAULT_RF_TX_POWER;
				}
				else
				{
					pAd->TxPower[i * 2].Power3 = Tx2ALC;
				}

				if (Tx2FinePowerCtrl > 4)
				{
					pAd->TxPower[i * 2].Tx2FinePowerCtrl = DEFAULT_BBP_TX_FINE_POWER_CTRL;
				}
				else
				{
					pAd->TxPower[i * 2].Tx2FinePowerCtrl = Tx2FinePowerCtrl;
				}

				Tx2ALC = GET_TX_ALC_BIT_MASK & Power3.field.Byte1;
				Tx2FinePowerCtrl = ((GET_TX_FINE_POWER_CTRL_BIT_MASK & Power3.field.Byte1) >> NUMBER_OF_BITS_FOR_TX_ALC);

				if (Tx2ALC > 31)
				{
					pAd->TxPower[i * 2 + 1].Power3 = DEFAULT_RF_TX_POWER;
				}
				else
				{
					pAd->TxPower[i * 2 + 1].Power3 = Tx2ALC;
				}

				if (Tx2FinePowerCtrl > 4)
				{
					pAd->TxPower[i * 2 + 1].Tx2FinePowerCtrl = DEFAULT_BBP_TX_FINE_POWER_CTRL;
				}
				else
				{
					pAd->TxPower[i * 2 + 1].Tx2FinePowerCtrl = Tx2FinePowerCtrl;
				}

				DBGPRINT(RT_DEBUG_TRACE, ("%s: pAd->TxPower[%d].Power3 = 0x%02X, pAd->TxPower[%d].Tx2FinePowerCtrl = 0x%02X, pAd->TxPower[%d].Power3 = 0x%02X, pAd->TxPower[%d].Tx2FinePowerCtrl = 0x%02X\n", 
					__FUNCTION__, 
					i * 2, 
					pAd->TxPower[i * 2].Power3, 
					i * 2, 
					pAd->TxPower[i * 2].Tx2FinePowerCtrl, 
					i * 2 + 1, 
					pAd->TxPower[i * 2 + 1].Power3, 
					i * 2 + 1, 
					pAd->TxPower[i * 2 + 1].Tx2FinePowerCtrl));
			}
		}
		else /* Tx power control over RF R12 and RF R13*/
#endif /* RT3593 */
		{ /* Default routine. RT3070 and RT3370 run here. */
			RT28xx_EEPROM_READ16(pAd, EEPROM_G_TX_PWR_OFFSET + i * 2, Power.word);
			RT28xx_EEPROM_READ16(pAd, EEPROM_G_TX2_PWR_OFFSET + i * 2, Power2.word);
			pAd->TxPower[i * 2].Channel = i * 2 + 1;
			pAd->TxPower[i * 2 + 1].Channel = i * 2 + 2;

			pAd->TxPower[i * 2].Power = Power.field.Byte0;
			if(!IS_RT3390(pAd))  // 3370 has different Tx power range
			{
			if ((Power.field.Byte0 > 31) || (Power.field.Byte0 < 0))
				pAd->TxPower[i * 2].Power = DEFAULT_RF_TX_POWER;
			}				

			pAd->TxPower[i * 2 + 1].Power = Power.field.Byte1;
			if(!IS_RT3390(pAd)) // 3370 has different Tx power range
			{
			if ((Power.field.Byte1 > 31) || (Power.field.Byte1 < 0))
				pAd->TxPower[i * 2 + 1].Power = DEFAULT_RF_TX_POWER;
			}				

			if ((Power2.field.Byte0 > 31) || (Power2.field.Byte0 < 0))
				pAd->TxPower[i * 2].Power2 = DEFAULT_RF_TX_POWER;
			else
				pAd->TxPower[i * 2].Power2 = Power2.field.Byte0;

			if ((Power2.field.Byte1 > 31) || (Power2.field.Byte1 < 0))
				pAd->TxPower[i * 2 + 1].Power2 = DEFAULT_RF_TX_POWER;
			else
				pAd->TxPower[i * 2 + 1].Power2 = Power2.field.Byte1;
		}
	}
	
#ifdef RT5592
	if (IS_RT5592(pAd))
	{
		/* 1. U-NII lower/middle band: 36, 38, 40; 44, 46, 48; 52, 54, 56; 60, 62, 64 (including central frequency in BW 40MHz)*/
		/* 1.1 Fill up channel*/
		choffset = 14;
		for (i = 0; i < 4; i++)
		{
			pAd->TxPower[3 * i + choffset + 0].Channel	= 36 + i * 8 + 0;
			pAd->TxPower[3 * i + choffset + 0].Power	= DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 0].Power2	= DEFAULT_RF_TX_POWER;

			pAd->TxPower[3 * i + choffset + 1].Channel	= 36 + i * 8 + 2;
			pAd->TxPower[3 * i + choffset + 1].Power	= DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 1].Power2	= DEFAULT_RF_TX_POWER;

			pAd->TxPower[3 * i + choffset + 2].Channel	= 36 + i * 8 + 4;
			pAd->TxPower[3 * i + choffset + 2].Power	= DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 2].Power2	= DEFAULT_RF_TX_POWER;
		}

		/* 1.2 Fill up power*/
		for (i = 0; i < 6; i++)
		{
			RT28xx_EEPROM_READ16(pAd, EEPROM_A_TX_PWR_OFFSET + i * 2, Power.word);
			RT28xx_EEPROM_READ16(pAd, EEPROM_A_TX2_PWR_OFFSET + i * 2, Power2.word);
			printk("Power = %x\n", Power.word);
			printk("Power2 = %x\n", Power2.word);			

			if ((Power.field.Byte0 < 0x2B) && (Power.field.Byte0 >= 0))
				pAd->TxPower[i * 2 + choffset + 0].Power = Power.field.Byte0;

			if ((Power.field.Byte1 < 0x2B) && (Power.field.Byte1 >= 0))
				pAd->TxPower[i * 2 + choffset + 1].Power = Power.field.Byte1;			

			if ((Power2.field.Byte0 < 0x2B) && (Power2.field.Byte0 >= 0))
				pAd->TxPower[i * 2 + choffset + 0].Power2 = Power2.field.Byte0;

			if ((Power2.field.Byte1 < 0x2B) && (Power2.field.Byte1 >= 0))
				pAd->TxPower[i * 2 + choffset + 1].Power2 = Power2.field.Byte1;			
		}

		/* 2. HipperLAN 2 100, 102 ,104; 108, 110, 112; 116, 118, 120; 124, 126, 128; 132, 134, 136; 140 (including central frequency in BW 40MHz)*/
		/* 2.1 Fill up channel*/
		choffset = 14 + 12;
		for (i = 0; i < 5; i++)
		{
			pAd->TxPower[3 * i + choffset + 0].Channel	= 100 + i * 8 + 0;
			pAd->TxPower[3 * i + choffset + 0].Power	= DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 0].Power2	= DEFAULT_RF_TX_POWER;

			pAd->TxPower[3 * i + choffset + 1].Channel	= 100 + i * 8 + 2;
			pAd->TxPower[3 * i + choffset + 1].Power	= DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 1].Power2	= DEFAULT_RF_TX_POWER;

			pAd->TxPower[3 * i + choffset + 2].Channel	= 100 + i * 8 + 4;
			pAd->TxPower[3 * i + choffset + 2].Power	= DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 2].Power2	= DEFAULT_RF_TX_POWER;
		}

		pAd->TxPower[3 * 5 + choffset + 0].Channel		= 140;
		pAd->TxPower[3 * 5 + choffset + 0].Power		= DEFAULT_RF_TX_POWER;
		pAd->TxPower[3 * 5 + choffset + 0].Power2		= DEFAULT_RF_TX_POWER;

		/* 2.2 Fill up power*/
		for (i = 0; i < 8; i++)
		{
			RT28xx_EEPROM_READ16(pAd, EEPROM_A_TX_PWR_OFFSET + (choffset - 14) + i * 2, Power.word);
			RT28xx_EEPROM_READ16(pAd, EEPROM_A_TX2_PWR_OFFSET + (choffset - 14) + i * 2, Power2.word);

			if ((Power.field.Byte0 < 0X2b) && (Power.field.Byte0 >= 0))
				pAd->TxPower[i * 2 + choffset + 0].Power = Power.field.Byte0;

			if ((Power.field.Byte1 < 0X2B) && (Power.field.Byte1 >= 0))
				pAd->TxPower[i * 2 + choffset + 1].Power = Power.field.Byte1;			

			if ((Power2.field.Byte0 < 0X2B) && (Power2.field.Byte0 >= 0))
				pAd->TxPower[i * 2 + choffset + 0].Power2 = Power2.field.Byte0;

			if ((Power2.field.Byte1 < 0X2B) && (Power2.field.Byte1 >= 0))
				pAd->TxPower[i * 2 + choffset + 1].Power2 = Power2.field.Byte1;			
		}

		/* 3. U-NII upper band: 149, 151, 153; 157, 159, 161; 165, 167, 169; 171, 173 (including central frequency in BW 40MHz)*/
		/* 3.1 Fill up channel*/
		choffset = 14 + 12 + 16;
		/*for (i = 0; i < 2; i++)*/
		for (i = 0; i < 3; i++)
		{
			pAd->TxPower[3 * i + choffset + 0].Channel	= 149 + i * 8 + 0;
			pAd->TxPower[3 * i + choffset + 0].Power	= DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 0].Power2	= DEFAULT_RF_TX_POWER;

			pAd->TxPower[3 * i + choffset + 1].Channel	= 149 + i * 8 + 2;
			pAd->TxPower[3 * i + choffset + 1].Power	= DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 1].Power2	= DEFAULT_RF_TX_POWER;

			pAd->TxPower[3 * i + choffset + 2].Channel	= 149 + i * 8 + 4;
			pAd->TxPower[3 * i + choffset + 2].Power	= DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 2].Power2	= DEFAULT_RF_TX_POWER;
		}

#if 0
		pAd->TxPower[3 * 2 + choffset + 0].Channel		= 165;
		pAd->TxPower[3 * 2 + choffset + 0].Power		= DEFAULT_RF_TX_POWER;
		pAd->TxPower[3 * 2 + choffset + 0].Power2		= DEFAULT_RF_TX_POWER;
#endif
		pAd->TxPower[3 * 3 + choffset + 0].Channel		= 171;
		pAd->TxPower[3 * 3 + choffset + 0].Power		= DEFAULT_RF_TX_POWER;
		pAd->TxPower[3 * 3 + choffset + 0].Power2		= DEFAULT_RF_TX_POWER;
		pAd->TxPower[3 * 3 + choffset + 1].Channel		= 173;
		pAd->TxPower[3 * 3 + choffset + 1].Power		= DEFAULT_RF_TX_POWER;
		pAd->TxPower[3 * 3 + choffset + 1].Power2		= DEFAULT_RF_TX_POWER;

		/* 3.2 Fill up power*/
		/*for (i = 0; i < 4; i++)*/
		for (i = 0; i < 6; i++)
		{
			RT28xx_EEPROM_READ16(pAd, EEPROM_A_TX_PWR_OFFSET + (choffset - 14) + i * 2, Power.word);
			RT28xx_EEPROM_READ16(pAd, EEPROM_A_TX2_PWR_OFFSET + (choffset - 14) + i * 2, Power2.word);

			if ((Power.field.Byte0 < 0x2B) && (Power.field.Byte0 >= 0))
				pAd->TxPower[i * 2 + choffset + 0].Power = Power.field.Byte0;

			if ((Power.field.Byte1 < 0x2b) && (Power.field.Byte1 >= 0))
				pAd->TxPower[i * 2 + choffset + 1].Power = Power.field.Byte1;			

			if ((Power2.field.Byte0 < 0x2b) && (Power2.field.Byte0 >= 0))
				pAd->TxPower[i * 2 + choffset + 0].Power2 = Power2.field.Byte0;

			if ((Power2.field.Byte1 < 0x2b) && (Power2.field.Byte1 >= 0))
				pAd->TxPower[i * 2 + choffset + 1].Power2 = Power2.field.Byte1;
		}
		/* 4. Print and Debug*/
		/*choffset = 14 + 12 + 16 + 7;*/
		choffset = 14 + 12 + 16 + 11;
		for (i = 0; i < choffset; i++)
		{
			DBGPRINT(RT_DEBUG_TRACE, ("E2PROM: TxPower[%03d], Channel = %d, Power = %d, Power2 = %d\n", i, pAd->TxPower[i].Channel, pAd->TxPower[i].Power, pAd->TxPower[i].Power2 ));
		}
	}

#endif /* RT5592 */

#ifdef RT3593
	//
	// 5GHz Tx power for 3593
	//
	if (IS_RT3593(pAd))
	{
		// 1. U-NII lower/middle band: 36, 38, 40; 44, 46, 48; 52, 54, 56; 60, 62, 64 (including central frequency in BW 40MHz)
		// 1.1 Fill up channel
		choffset = 14;
		for (i = 0; i < 4; i++)
		{
			pAd->TxPower[3 * i + choffset + 0].Channel  = 36 + i * 8 + 0;
			pAd->TxPower[3 * i + choffset + 0].Power     = DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 0].Power2   = DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 0].Power3	= DEFAULT_RF_TX_POWER;

			pAd->TxPower[3 * i + choffset + 1].Channel  = 36 + i * 8 + 2;
			pAd->TxPower[3 * i + choffset + 1].Power     = DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 1].Power2   = DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 1].Power3	= DEFAULT_RF_TX_POWER;

			pAd->TxPower[3 * i + choffset + 2].Channel  = 36 + i * 8 + 4;
			pAd->TxPower[3 * i + choffset + 2].Power     = DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 2].Power2   = DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 2].Power3	= DEFAULT_RF_TX_POWER;
		}

		// 1.2 Fill up power
		for (i = 0; i < 6; i++)
		{
			RT28xx_EEPROM_READ16(pAd, (EEPROM_EXT_TX0_OVER_5G + i * 2), Power.word);
			RT28xx_EEPROM_READ16(pAd, (EEPROM_EXT_TX1_OVER_5G + i * 2), Power2.word);
			RT28xx_EEPROM_READ16(pAd, (EEPROM_EXT_TX2_OVER_5G + i * 2), Power3.word);

			Tx0ALC = GET_TX_ALC_BIT_MASK & Power.field.Byte0;
			if (Tx0ALC > 31)
			{
				pAd->TxPower[i * 2 + choffset + 0].Power = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2 + choffset + 0].Power = Tx0ALC;
			}

			Tx0ALC = GET_TX_ALC_BIT_MASK & Power.field.Byte1;
			if (Tx0ALC > 31)
			{
				pAd->TxPower[i * 2 + choffset + 1].Power = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2 + choffset + 1].Power = Tx0ALC;
			}

			Tx1ALC = GET_TX_ALC_BIT_MASK & Power2.field.Byte0;
			if (Tx1ALC > 31)
			{
				pAd->TxPower[i * 2 + choffset + 0].Power2 = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2 + choffset + 0].Power2 = Tx1ALC;
			}

			Tx1ALC = GET_TX_ALC_BIT_MASK & Power2.field.Byte1;
			if (Tx1ALC > 31)
			{
				pAd->TxPower[i * 2 + choffset + 1].Power2 = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2 + choffset + 1].Power2 = Tx1ALC;
			}

			Tx2ALC = GET_TX_ALC_BIT_MASK & Power3.field.Byte0;
			if (Tx2ALC > 31)
			{
				pAd->TxPower[i * 2 + choffset + 0].Power3 = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2 + choffset + 0].Power3 = Tx2ALC;
			}

			Tx2ALC = GET_TX_ALC_BIT_MASK & Power3.field.Byte1;
			if (Tx2ALC > 31)
			{
				pAd->TxPower[i * 2 + choffset + 1].Power3 = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2 + choffset + 1].Power3 = Tx2ALC;
			}
		}

		// 2. HipperLAN 2 100, 102 ,104; 108, 110, 112; 116, 118, 120; 124, 126, 128; 132, 134, 136; 140 (including central frequency in BW 40MHz)
		// 2.1 Fill up channel
		choffset = 14 + 12;
		for (i = 0; i < 5; i++)
		{
			pAd->TxPower[3 * i + choffset + 0].Channel  = 100 + i * 8 + 0;
			pAd->TxPower[3 * i + choffset + 0].Power     = DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 0].Power2   = DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 0].Power3	= DEFAULT_RF_TX_POWER;

			pAd->TxPower[3 * i + choffset + 1].Channel  = 100 + i * 8 + 2;
			pAd->TxPower[3 * i + choffset + 1].Power     = DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 1].Power2   = DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 1].Power3	= DEFAULT_RF_TX_POWER;

			pAd->TxPower[3 * i + choffset + 2].Channel  = 100 + i * 8 + 4;
			pAd->TxPower[3 * i + choffset + 2].Power     = DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 2].Power2   = DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 2].Power3	= DEFAULT_RF_TX_POWER;
		}
		
		pAd->TxPower[3 * 5 + choffset + 0].Channel         = 140;
		pAd->TxPower[3 * 5 + choffset + 0].Power            = DEFAULT_RF_TX_POWER;
		pAd->TxPower[3 * 5 + choffset + 0].Power2          = DEFAULT_RF_TX_POWER;
		pAd->TxPower[3 * 5 + choffset + 0].Power3		= DEFAULT_RF_TX_POWER;

		// 2.2 Fill up power
		for (i = 0; i < 8; i++)
		{
			RT28xx_EEPROM_READ16(pAd, (EEPROM_EXT_TX0_OVER_5G + (choffset - 14) + i * 2), Power.word);
			RT28xx_EEPROM_READ16(pAd, (EEPROM_EXT_TX1_OVER_5G + (choffset - 14) + i * 2), Power2.word);
			RT28xx_EEPROM_READ16(pAd, (EEPROM_EXT_TX2_OVER_5G + (choffset - 14) + i * 2), Power3.word);

			Tx0ALC = GET_TX_ALC_BIT_MASK & Power.field.Byte0;
			if (Tx0ALC > 31)
			{
				pAd->TxPower[i * 2 + choffset + 0].Power = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2 + choffset + 0].Power = Tx0ALC;
			}

			Tx0ALC = GET_TX_ALC_BIT_MASK & Power.field.Byte1;
			if (Tx0ALC > 31)
			{
				pAd->TxPower[i * 2 + choffset + 1].Power = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2 + choffset + 1].Power = Tx0ALC;
			}

			Tx1ALC = GET_TX_ALC_BIT_MASK & Power2.field.Byte0;
			if (Tx1ALC > 31)
			{
				pAd->TxPower[i * 2 + choffset + 0].Power2 = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2 + choffset + 0].Power2 = Tx1ALC;
			}

			Tx1ALC = GET_TX_ALC_BIT_MASK & Power2.field.Byte1;
			if (Tx1ALC > 31)
			{
				pAd->TxPower[i * 2 + choffset + 1].Power2 = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2 + choffset + 1].Power2 = Tx1ALC;
			}

			Tx2ALC = GET_TX_ALC_BIT_MASK & Power3.field.Byte0;
			if (Tx2ALC > 31)
			{
				pAd->TxPower[i * 2 + choffset + 0].Power3 = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2 + choffset + 0].Power3 = Tx2ALC;
			}

			Tx2ALC = GET_TX_ALC_BIT_MASK & Power3.field.Byte1;
			if (Tx2ALC > 31)
			{
				pAd->TxPower[i * 2 + choffset + 1].Power3 = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2 + choffset + 1].Power3 = Tx2ALC;
			}
		}

		// 3. U-NII upper band: 149, 151, 153; 157, 159, 161; 165; 167; 169; 171; 173 (including central frequency in BW 40MHz)
		// 3.1 Fill up channel
		choffset = 14 + 12 + 16;
		for (i = 0; i < 3; i++)
		{
			pAd->TxPower[3 * i + choffset + 0].Channel  = 149 + i * 8 + 0;
			pAd->TxPower[3 * i + choffset + 0].Power     = DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 0].Power2   = DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 0].Power3	= DEFAULT_RF_TX_POWER;

			pAd->TxPower[3 * i + choffset + 1].Channel  = 149 + i * 8 + 2;
			pAd->TxPower[3 * i + choffset + 1].Power     = DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 1].Power2   = DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 1].Power3	= DEFAULT_RF_TX_POWER;

			pAd->TxPower[3 * i + choffset + 2].Channel  = 149 + i * 8 + 4;
			pAd->TxPower[3 * i + choffset + 2].Power     = DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 2].Power2   = DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 2].Power3	= DEFAULT_RF_TX_POWER;
		}
		
		pAd->TxPower[3 * 3 + choffset + 0].Channel         = 171;
		pAd->TxPower[3 * 3 + choffset + 0].Power            = DEFAULT_RF_TX_POWER;
		pAd->TxPower[3 * 3 + choffset + 0].Power2          = DEFAULT_RF_TX_POWER;
		pAd->TxPower[3 * 3 + choffset + 0].Power3		= DEFAULT_RF_TX_POWER;

		pAd->TxPower[3 * 3 + choffset + 1].Channel		= 173;
		pAd->TxPower[3 * 3 + choffset + 1].Power		= DEFAULT_RF_TX_POWER;
		pAd->TxPower[3 * 3 + choffset + 1].Power2		= DEFAULT_RF_TX_POWER;
		pAd->TxPower[3 * 3 + choffset + 1].Power3		= DEFAULT_RF_TX_POWER;

		// 3.2 Fill up power
		for (i = 0; i < 6; i++)
		{
			RT28xx_EEPROM_READ16(pAd, (EEPROM_EXT_TX0_OVER_5G + (choffset - 14) + i * 2), Power.word);
			RT28xx_EEPROM_READ16(pAd, (EEPROM_EXT_TX1_OVER_5G + (choffset - 14) + i * 2), Power2.word);
			RT28xx_EEPROM_READ16(pAd, (EEPROM_EXT_TX2_OVER_5G + (choffset - 14) + i * 2), Power3.word);

			Tx0ALC = GET_TX_ALC_BIT_MASK & Power.field.Byte0;
			if (Tx0ALC > 31)
			{
				pAd->TxPower[i * 2 + choffset + 0].Power = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2 + choffset + 0].Power = Tx0ALC;
			}

			Tx0ALC = GET_TX_ALC_BIT_MASK & Power.field.Byte1;
			if (Tx0ALC > 31)
			{
				pAd->TxPower[i * 2 + choffset + 1].Power = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2 + choffset + 1].Power = Tx0ALC;
			}

			Tx1ALC = GET_TX_ALC_BIT_MASK & Power2.field.Byte0;
			if (Tx1ALC > 31)
			{
				pAd->TxPower[i * 2 + choffset + 0].Power2 = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2 + choffset + 0].Power2 = Tx1ALC;
			}

			Tx1ALC = GET_TX_ALC_BIT_MASK & Power2.field.Byte1;
			if (Tx1ALC > 31)
			{
				pAd->TxPower[i * 2 + choffset + 1].Power2 = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2 + choffset + 1].Power2 = Tx1ALC;
			}

			Tx2ALC = GET_TX_ALC_BIT_MASK & Power3.field.Byte0;
			if (Tx2ALC > 31)
			{
				pAd->TxPower[i * 2 + choffset + 0].Power3 = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2 + choffset + 0].Power3 = Tx2ALC;
			}

			Tx2ALC = GET_TX_ALC_BIT_MASK & Power3.field.Byte1;
			if (Tx2ALC > 31)
			{
				pAd->TxPower[i * 2 + choffset + 1].Power3 = DEFAULT_RF_TX_POWER;
			}
			else
			{
				pAd->TxPower[i * 2 + choffset + 1].Power3 = Tx2ALC;
			}
		}
	}
	else
#endif /* RT3593 */
	{
		if (IS_RT5592(pAd))
			return;
		
		/* 1. U-NII lower/middle band: 36, 38, 40; 44, 46, 48; 52, 54, 56; 60, 62, 64 (including central frequency in BW 40MHz)*/
		/* 1.1 Fill up channel*/
		choffset = 14;
		for (i = 0; i < 4; i++)
		{
			pAd->TxPower[3 * i + choffset + 0].Channel	= 36 + i * 8 + 0;
			pAd->TxPower[3 * i + choffset + 0].Power	= DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 0].Power2	= DEFAULT_RF_TX_POWER;

			pAd->TxPower[3 * i + choffset + 1].Channel	= 36 + i * 8 + 2;
			pAd->TxPower[3 * i + choffset + 1].Power	= DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 1].Power2	= DEFAULT_RF_TX_POWER;

			pAd->TxPower[3 * i + choffset + 2].Channel	= 36 + i * 8 + 4;
			pAd->TxPower[3 * i + choffset + 2].Power	= DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 2].Power2	= DEFAULT_RF_TX_POWER;
		}

		/* 1.2 Fill up power*/
		for (i = 0; i < 6; i++)
		{
			RT28xx_EEPROM_READ16(pAd, EEPROM_A_TX_PWR_OFFSET + i * 2, Power.word);
			RT28xx_EEPROM_READ16(pAd, EEPROM_A_TX2_PWR_OFFSET + i * 2, Power2.word);

			if ((Power.field.Byte0 < 16) && (Power.field.Byte0 >= -7))
				pAd->TxPower[i * 2 + choffset + 0].Power = Power.field.Byte0;

			if ((Power.field.Byte1 < 16) && (Power.field.Byte1 >= -7))
				pAd->TxPower[i * 2 + choffset + 1].Power = Power.field.Byte1;			

			if ((Power2.field.Byte0 < 16) && (Power2.field.Byte0 >= -7))
				pAd->TxPower[i * 2 + choffset + 0].Power2 = Power2.field.Byte0;

			if ((Power2.field.Byte1 < 16) && (Power2.field.Byte1 >= -7))
				pAd->TxPower[i * 2 + choffset + 1].Power2 = Power2.field.Byte1;			
		}
		
		/* 2. HipperLAN 2 100, 102 ,104; 108, 110, 112; 116, 118, 120; 124, 126, 128; 132, 134, 136; 140 (including central frequency in BW 40MHz)*/
		/* 2.1 Fill up channel*/
		choffset = 14 + 12;
		for (i = 0; i < 5; i++)
		{
			pAd->TxPower[3 * i + choffset + 0].Channel	= 100 + i * 8 + 0;
			pAd->TxPower[3 * i + choffset + 0].Power	= DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 0].Power2	= DEFAULT_RF_TX_POWER;

			pAd->TxPower[3 * i + choffset + 1].Channel	= 100 + i * 8 + 2;
			pAd->TxPower[3 * i + choffset + 1].Power	= DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 1].Power2	= DEFAULT_RF_TX_POWER;

			pAd->TxPower[3 * i + choffset + 2].Channel	= 100 + i * 8 + 4;
			pAd->TxPower[3 * i + choffset + 2].Power	= DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 2].Power2	= DEFAULT_RF_TX_POWER;
		}
		pAd->TxPower[3 * 5 + choffset + 0].Channel		= 140;
		pAd->TxPower[3 * 5 + choffset + 0].Power		= DEFAULT_RF_TX_POWER;
		pAd->TxPower[3 * 5 + choffset + 0].Power2		= DEFAULT_RF_TX_POWER;

		/* 2.2 Fill up power*/
		for (i = 0; i < 8; i++)
		{
			RT28xx_EEPROM_READ16(pAd, EEPROM_A_TX_PWR_OFFSET + (choffset - 14) + i * 2, Power.word);
			RT28xx_EEPROM_READ16(pAd, EEPROM_A_TX2_PWR_OFFSET + (choffset - 14) + i * 2, Power2.word);

			if ((Power.field.Byte0 < 16) && (Power.field.Byte0 >= -7))
				pAd->TxPower[i * 2 + choffset + 0].Power = Power.field.Byte0;

			if ((Power.field.Byte1 < 16) && (Power.field.Byte1 >= -7))
				pAd->TxPower[i * 2 + choffset + 1].Power = Power.field.Byte1;			

			if ((Power2.field.Byte0 < 16) && (Power2.field.Byte0 >= -7))
				pAd->TxPower[i * 2 + choffset + 0].Power2 = Power2.field.Byte0;

			if ((Power2.field.Byte1 < 16) && (Power2.field.Byte1 >= -7))
				pAd->TxPower[i * 2 + choffset + 1].Power2 = Power2.field.Byte1;			
		}

		/* 3. U-NII upper band: 149, 151, 153; 157, 159, 161; 165, 167, 169; 171, 173 (including central frequency in BW 40MHz)*/
		/* 3.1 Fill up channel*/
		choffset = 14 + 12 + 16;
		/*for (i = 0; i < 2; i++)*/
		for (i = 0; i < 3; i++)
		{
			pAd->TxPower[3 * i + choffset + 0].Channel	= 149 + i * 8 + 0;
			pAd->TxPower[3 * i + choffset + 0].Power	= DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 0].Power2	= DEFAULT_RF_TX_POWER;

			pAd->TxPower[3 * i + choffset + 1].Channel	= 149 + i * 8 + 2;
			pAd->TxPower[3 * i + choffset + 1].Power	= DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 1].Power2	= DEFAULT_RF_TX_POWER;

			pAd->TxPower[3 * i + choffset + 2].Channel	= 149 + i * 8 + 4;
			pAd->TxPower[3 * i + choffset + 2].Power	= DEFAULT_RF_TX_POWER;
			pAd->TxPower[3 * i + choffset + 2].Power2	= DEFAULT_RF_TX_POWER;
		}
#if 0
		pAd->TxPower[3 * 2 + choffset + 0].Channel		= 165;
		pAd->TxPower[3 * 2 + choffset + 0].Power		= DEFAULT_RF_TX_POWER;
		pAd->TxPower[3 * 2 + choffset + 0].Power2		= DEFAULT_RF_TX_POWER;
#endif
		pAd->TxPower[3 * 3 + choffset + 0].Channel		= 171;
		pAd->TxPower[3 * 3 + choffset + 0].Power		= DEFAULT_RF_TX_POWER;
		pAd->TxPower[3 * 3 + choffset + 0].Power2		= DEFAULT_RF_TX_POWER;

		pAd->TxPower[3 * 3 + choffset + 1].Channel		= 173;
		pAd->TxPower[3 * 3 + choffset + 1].Power		= DEFAULT_RF_TX_POWER;
		pAd->TxPower[3 * 3 + choffset + 1].Power2		= DEFAULT_RF_TX_POWER;

		/* 3.2 Fill up power*/
		/*for (i = 0; i < 4; i++)*/
		for (i = 0; i < 6; i++)
		{
			RT28xx_EEPROM_READ16(pAd, EEPROM_A_TX_PWR_OFFSET + (choffset - 14) + i * 2, Power.word);
			RT28xx_EEPROM_READ16(pAd, EEPROM_A_TX2_PWR_OFFSET + (choffset - 14) + i * 2, Power2.word);

			if ((Power.field.Byte0 < 16) && (Power.field.Byte0 >= -7))
				pAd->TxPower[i * 2 + choffset + 0].Power = Power.field.Byte0;

			if ((Power.field.Byte1 < 16) && (Power.field.Byte1 >= -7))
				pAd->TxPower[i * 2 + choffset + 1].Power = Power.field.Byte1;			

			if ((Power2.field.Byte0 < 16) && (Power2.field.Byte0 >= -7))
				pAd->TxPower[i * 2 + choffset + 0].Power2 = Power2.field.Byte0;

			if ((Power2.field.Byte1 < 16) && (Power2.field.Byte1 >= -7))
				pAd->TxPower[i * 2 + choffset + 1].Power2 = Power2.field.Byte1;			
		}
	}


	/* 4. Print and Debug*/
	/*choffset = 14 + 12 + 16 + 7;*/
	choffset = 14 + 12 + 16 + 11;
#ifdef RELEASE_EXCLUDE
	for (i = 0; i < choffset; i++)
	{
		DBGPRINT(RT_DEBUG_INFO, ("E2PROM: TxPower[%03d], Channel = %d, Power = %d, Power2 = %d\n", i, pAd->TxPower[i].Channel, pAd->TxPower[i].Power, pAd->TxPower[i].Power2 ));
	}
#endif /* RELEASE_EXCLUDE */
	

#if 0
	/* Init the 802.11j channel number for TX channel power*/
	/* 0. 20MHz */
	for (i = 0; i < 3; i++)
	{
		pAd->TxPower11J[i].Channel = 8 + i * 4;
		pAd->TxPower11J[i].BW = BW_20;
	}
	
	for (i = 0; i < 4; i++)
	{
		pAd->TxPower11J[i + 3].Channel = 34 + i * 4;
		pAd->TxPower11J[i + 3].BW = BW_20;
	}

	for (i = 0; i < 4; i++)
	{
		pAd->TxPower11J[i + 7].Channel = 184 + i * 4;
		pAd->TxPower11J[i + 7].BW = BW_20;
	}

	/* 0. 10MHz */
	for (i = 0; i < 2; i++)
	{
		pAd->TxPower11J[i + 11].Channel = 7 + i;
		pAd->TxPower11J[i + 11].BW = BW_10;
	}
	pAd->TxPower11J[13].Channel = 11;
	pAd->TxPower11J[13].BW = BW_10;
	
	for (i = 0; i < 3; i++)
	{
		pAd->TxPower11J[i + 14].Channel = 183 + i;
		pAd->TxPower11J[i + 14].BW= BW_10;
	}

	for (i = 0; i < 3; i++)
	{
		pAd->TxPower11J[i + 17].Channel = 187 + i;
		pAd->TxPower11J[i + 17].BW = BW_10;
	}
	for (i = 0; i < 10; i++)
	{
		RT28xx_EEPROM_READ16(pAd, EEPROM_Japan_TX_PWR_OFFSET + i * 2, Power.word);
		RT28xx_EEPROM_READ16(pAd, EEPROM_Japan_TX2_PWR_OFFSET + i * 2, Power2.word);

		if ((Power.field.Byte0 < 36) && (Power.field.Byte0 > -6))
			pAd->TxPower11J[i * 2].Power = Power.field.Byte0;

		if ((Power.field.Byte1 < 36) && (Power.field.Byte1 > -6))
			pAd->TxPower11J[i * 2 + 1].Power = Power.field.Byte1;			

		if ((Power2.field.Byte0 < 36) && (Power2.field.Byte0 > -6))
			pAd->TxPower11J[i * 2].Power2 = Power2.field.Byte0;

		if ((Power2.field.Byte1 < 36) && (Power2.field.Byte1 > -6))
			pAd->TxPower11J[i * 2 + 1].Power2 = Power2.field.Byte1;			
	}
#endif
}

