/*
 ***************************************************************************
 * Ralink Tech Inc.
 * 4F, No. 2 Technology 5th Rd.
 * Science-based Industrial Park
 * Hsin-chu, Taiwan, R.O.C.
 *
 * (c) Copyright 2002-2011, Ralink Technology, Inc.
 *
 * All rights reserved. Ralink's source code is an unpublished work and the
 * use of a copyright notice does not imply otherwise. This source code
 * contains confidential trade secret material of Ralink Tech. Any attemp
 * or participation in deciphering, decoding, reverse engineering or in any
 * way altering the source code is stricitly prohibited, unless the prior
 * written consent of Ralink Technology, Inc. is obtained.
 ***************************************************************************

	Module Name:
	rt5592_ate.c

	Abstract:
	Specific ATE funcitons and variables for RT5572/RT5592

	Revision History:
	Who         When          What
	--------    ----------    ----------------------------------------------
*/

#if defined(RT5370) || defined(RT5372) || defined(RT5390) || defined(RT5392)

#include "rt_config.h"

#ifndef RTMP_RF_RW_SUPPORT
#error "You Should Enable compile flag RTMP_RF_RW_SUPPORT for this chip"
#endif /* RTMP_RF_RW_SUPPORT */

extern UCHAR RTATEGetTssiByChannel(PRTMP_ADAPTER pAd, UCHAR Channel);
extern CHAR GetPowerDeltaFromTssiRatio(CHAR TssiOfChannel, CHAR TssiBase);
CHAR RTATEInsertTssi(UCHAR InChannel, UCHAR Channel0, UCHAR Channel1,CHAR Tssi0, CHAR Tssi1);


/* Vx = V0 + t(V1 - V0) ? f(x), where t = (x-x0) / (x1 - x0) */
CHAR RTATEInsertTssi(UCHAR InChannel, UCHAR Channel0, UCHAR Channel1,CHAR Tssi0, CHAR Tssi1)
{
	CHAR	InTssi, TssiDelta, ChannelDelta, InChannelDelta;
	
	ChannelDelta = Channel1 - Channel0;
	InChannelDelta = InChannel - Channel0;
	TssiDelta = Tssi1 - Tssi0;

	/* channel delta should not be 0 */
	if (ChannelDelta == 0)
		InTssi = Tssi0;

	DBGPRINT(RT_DEBUG_WARN, ("--->RTATEInsertTssi\n")); 	
	
	if ((TssiDelta > 0) && (((InChannelDelta * TssiDelta * 10) / ChannelDelta) % 10 >= 5))
	{
		InTssi = Tssi0 + ((InChannelDelta * TssiDelta) / ChannelDelta);
		InTssi += 1;
	}
	else	if ((TssiDelta < 0) && (((InChannelDelta * TssiDelta * 10) / ChannelDelta) % 10 <= -5))
	{
		InTssi = Tssi0 + ((InChannelDelta * TssiDelta) / ChannelDelta);
		InTssi -= 1;
	}
	else
	{
		InTssi = Tssi0 + ((InChannelDelta * TssiDelta) / ChannelDelta);	
	}	

	DBGPRINT(RT_DEBUG_WARN, ("<---RTATEInsertTssi\n")); 		
	
	return InTssi;
}

UCHAR RTATEGetTssiByChannel(PRTMP_ADAPTER pAd, UCHAR Channel)
{
	UINT	i = 0;
	UCHAR	BbpData =0;
	UCHAR	ChannelPower;
	UCHAR 	BSSID_ADDR[MAC_ADDR_LEN] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
	USHORT	EEPData;
	BBP_R47_STRUC BBPR47;

	RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R47, &BBPR47.byte);
	BBPR47.field.Adc6On = 1;
	BBPR47.field.TssiMode = 0x02;
	BBPR47.field.TssiUpdateReq = 1;
	BBPR47.field.TssiReportSel = 0;							
	DBGPRINT(RT_DEBUG_WARN, ("Write BBP R47 = 0x%x\n", BBPR47.byte));
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R47, BBPR47.byte);
		
	/* start TX at 54Mbps */
	NdisZeroMemory(&pAd->ate, sizeof(ATE_INFO));
	pAd->ate.TxCount = 100;
	pAd->ate.TxLength = 1024;
	pAd->ate.Channel = Channel;
	COPY_MAC_ADDR(pAd->ate.Addr1, BROADCAST_ADDR);
	COPY_MAC_ADDR(pAd->ate.Addr2, pAd->PermanentAddress);                                                     
	COPY_MAC_ADDR(pAd->ate.Addr3, BSSID_ADDR);    		

	Set_ATE_TX_MODE_Proc(pAd, "1");		/* MODE_OFDM */
	Set_ATE_TX_MCS_Proc(pAd, "7");		/* 54Mbps */
	Set_ATE_TX_BW_Proc(pAd, "0");		/* 20MHz */
		
	/* read calibrated channel power value from EEPROM */
	RT28xx_EEPROM_READ16(pAd, EEPROM_G_TX_PWR_OFFSET+Channel-1, ChannelPower);
	pAd->ate.TxPower0 = (UCHAR)(ChannelPower & 0xff);
	DBGPRINT(RT_DEBUG_TRACE, ("Channel %d, Calibrated Tx.Power0= 0x%x\n", Channel, pAd->ate.TxPower0));
	
	/* read frequency offset from EEPROM */                        
	RT28xx_EEPROM_READ16(pAd, EEPROM_FREQ_OFFSET, EEPData);
	pAd->ate.RFFreqOffset = (UCHAR)(EEPData & 0xff);
		
	Set_ATE_Proc(pAd, "TXFRAME"); 
	RTMPusecDelay(200000);

	while (i < 500)
	{
		RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R47, &BbpData);

		if ((BbpData & 0x04) == 0)
			break;

		RTMPusecDelay(2);
		i++;	
	}

	if (i >= 500)
		DBGPRINT(RT_DEBUG_WARN, ("TSSI status not ready!!! (i=%d)\n", i));

	/* read BBP R49[6:0] and write to EEPROM 0x6E */
	DBGPRINT(RT_DEBUG_WARN, ("Read  BBP_R49\n")); 
	RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R49, &BbpData);
	DBGPRINT(RT_DEBUG_WARN, ("BBP R49 = 0x%x\n", BbpData)); 
	BbpData &= 0x7f;

	/* the upper boundary of 0x6E (TSSI base) is 0x7C */
	if (BbpData > 0x7C)
		BbpData = 0;

	/* back to ATE IDLE state */
	Set_ATE_Proc(pAd, "ATESTART");

	return BbpData;	
}

/* Get the power delta bound */
#define GET_TSSI_RATE_TABLE_INDEX(x) (((x) > UPPER_POWER_DELTA_INDEX) ? (UPPER_POWER_DELTA_INDEX) : (((x) < LOWER_POWER_DELTA_INDEX) ? (LOWER_POWER_DELTA_INDEX) : ((x))))

CHAR GetPowerDeltaFromTssiRatio(CHAR TssiOfChannel, CHAR TssiBase)
{
	LONG	TssiRatio, TssiDelta, MinTssiDelta;
	CHAR	i, PowerDeltaStatIndex, PowerDeltaEndIndex, MinTssiDeltaIndex;	
	CHAR	PowerDelta;
	extern ULONG TssiRatioTable[][2];

	// TODO: If 0 is a valid value for TSSI base
	if (TssiBase == 0)
		return 0;
	
	TssiRatio = TssiOfChannel * TssiRatioTable[0][1] / TssiBase;

	DBGPRINT(RT_DEBUG_WARN, ("TssiOfChannel = %d, TssiBase = %d, TssiRatio = %ld\n", TssiOfChannel,  TssiBase, TssiRatio));

	PowerDeltaStatIndex = 4;
	PowerDeltaEndIndex = 19;

	MinTssiDeltaIndex= PowerDeltaStatIndex;
	MinTssiDelta = TssiRatio - TssiRatioTable[MinTssiDeltaIndex][0];
	
	if (MinTssiDelta < 0)
		MinTssiDelta = -MinTssiDelta;

	for (i = PowerDeltaStatIndex+1; i <= PowerDeltaEndIndex; i++)
	{
		TssiDelta = TssiRatio -TssiRatioTable[i][0];
		
		if (TssiDelta < 0)
		{
			TssiDelta = -TssiDelta;
		}

		if (TssiDelta < MinTssiDelta)
		{
			MinTssiDelta = TssiDelta;
			MinTssiDeltaIndex = i;
		}
	}

	PowerDelta = MinTssiDeltaIndex - TSSI_RATIO_TABLE_OFFSET;

	DBGPRINT(RT_DEBUG_WARN, ("MinTssiDeltaIndex = %d, MinTssiDelta = %ld, PowerDelta = %d\n", MinTssiDeltaIndex,  MinTssiDelta, PowerDelta));
	
	return (PowerDelta);
}


/* both for RT5370 and RT5372 and RT5390 and RT5392*/
VOID RT5390ATEAsicSwitchChannel(
    IN PRTMP_ADAPTER pAd)
{
	UINT32 Value = 0;
	CHAR TxPwer = 0, TxPwer2 = 0;
	UCHAR index = 0, BbpValue = 0, Channel = 0;
#ifdef RTMP_RF_RW_SUPPORT
	/* added to prevent RF register reading error */
	UCHAR RFValue = 0;
#endif /* RTMP_RF_RW_SUPPORT */

#ifdef DOT11N_SS3_SUPPORT
	CHAR TxPwer3 = 0;
#endif /* DOT11N_SS3_SUPPORT */

	UCHAR TxRxh20M=0;
	UCHAR PreRFValue = 0;

#ifdef RALINK_QA
	/* for QA mode, TX power values are passed from UI */
	if ((pAd->ate.bQATxStart == TRUE) || (pAd->ate.bQARxStart == TRUE))
	{
		if (pAd->ate.Channel != pAd->LatchRfRegs.Channel)			
		{
			pAd->ate.Channel = pAd->LatchRfRegs.Channel;
		}
		return;
	}
	else
#endif /* RALINK_QA */
	Channel = pAd->ate.Channel;

	/* fill Tx power value */
	TxPwer = pAd->ate.TxPower0;
	TxPwer2 = pAd->ate.TxPower1;
#ifdef DOT11N_SS3_SUPPORT
	TxPwer3 = pAd->ate.TxPower2;
#endif /* DOT11N_SS3_SUPPORT */

	if (IS_RT5390(pAd))
	{	
		for (index = 0; index < NUM_OF_3020_CHNL; index++)
		{

			if (Channel == FreqItems3020[index].Channel)
			{
				/*
				    Set the BBP Tx fine power control in 0.1dB step				
				    Programming channel parameters
				*/
				ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R08, FreqItems3020[index].N); /* N */
				ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R09, (FreqItems3020[index].K & 0x0F)); /* K, N<11:8> is set to zero */

				ATE_RF_IO_READ8_BY_REG_ID(pAd, RF_R11, (PUCHAR)&RFValue);
				RFValue = ((RFValue & ~0x03) | (FreqItems3020[index].R & 0x03)); /* R */
				ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R11, (UCHAR)RFValue);

				ATE_RF_IO_READ8_BY_REG_ID(pAd, RF_R49, (PUCHAR)&RFValue);
				RFValue = ((RFValue & ~0x3F) | (TxPwer & 0x3F)); /* tx0_alc */
				ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R49, (UCHAR)RFValue);

				if (IS_RT5392(pAd))
				{
					ATE_RF_IO_READ8_BY_REG_ID(pAd, RF_R50, &RFValue);
					RFValue = ((RFValue & ~0x3F) | (TxPwer2 & 0x3F)); /* tx0_alc */
					ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R50, RFValue);
				}

				/* zero patch based on windows driver */
				ATE_RF_IO_READ8_BY_REG_ID(pAd, RF_R01, &RFValue);
				if (IS_RT5392(pAd))
				{
					RFValue = ((RFValue & ~0x3F) | 0x3F);
				}
				else
				{
					RFValue = ((RFValue & ~0x0F) | 0x0F); /* Enable rf_block_en, pll_en, rx0_en and tx0_en */
				}	
				ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R01, RFValue);

				ATE_RF_IO_READ8_BY_REG_ID(pAd, RF_R02, (PUCHAR)&RFValue);
                                RFValue |= 0x80;
                                ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R02, (UCHAR)RFValue);
                                RTMPusecDelay(1000);
                                RFValue &= 0x7F;
                                ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R02, (UCHAR)RFValue);   
				{
					/* Zero patch based on windows driver */
					if (IS_RT5392(pAd))
					{
						ATEAsicSetTxRxPath(pAd);
					}/**/
					
					ATE_RF_IO_READ8_BY_REG_ID(pAd, RF_R17, (PUCHAR)&RFValue);
					PreRFValue = RFValue;
					RFValue = ((RFValue & 0x80) | (pAd->ate.RFFreqOffset & 0x7F)); /* xo_code (C1 value control) - Crystal calibration */
					RFValue = min((INT)RFValue, 0x5F);
					if (PreRFValue != RFValue)
					{
						AsicSendCommandToMcu(pAd, 0x74, 0xff, RFValue, PreRFValue, FALSE);
					}

					/* Zero patch based on windows driver */
					if(pAd->ate.TxWI.TxWIPHYMODE == MODE_CCK)
					{
						ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R32, 0xC0);

						if (IS_RT5390F(pAd)) /* >= RT5390F */
						{
							ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R55, 0x46);
						}
						else if (IS_RT5392C(pAd))
							ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R55, 0x47);
					}
					else
					{
						ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R32, 0x20);

						if (IS_RT5390F(pAd) || IS_RT5392C(pAd)) /* >= RT5390F */
						{
							ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R55, 0x43);
						}
					}

					if (pAd->ate.TxWI.TxWIBW == BW_20) /* BW 20 */
					{
						/* write BBP R4 value 0x40 */
						ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R4, 0x40);
					}
					else
					{
						/* write BBP R4 value 0x50 */
						ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R4, 0x50);

					}/**/
				}

				if (  (pAd->ate.TxWI.TxWIBW /*CommonCfg.BBPCurrentBW*/ == BW_40)) /* BW 40 */
				{
					TxRxh20M = ((pAd->Mlme.CaliBW40RfR24 & 0x20) >> 5); /* Tx/Rx h20M */
				}
				else /* BW 20 */
				{
					TxRxh20M = ((pAd->Mlme.CaliBW20RfR24 & 0x20) >> 5); /* Tx/Rx h20M */
				}
#ifdef HW_COEXISTENCE_SUPPORT				
				if (IS_RT5390BC8(pAd))
				{
					if (IS_RT5390F(pAd)) /* >= RT5390F */
					{
						if ((Channel >= 1) && (Channel <= 5))
						{
							ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R59, 0x0E); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
						}
						else if (Channel == 6)
						{
							ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R59, 0x0B); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
						}
						else if (Channel == 7)
						{
							ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R59, 0x0A); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
						}
						else if (Channel == 8)
						{
							ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R59, 0x09); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
						}
						else if ((Channel >= 9) && (Channel <= 14))
						{
							ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R59, 0x07); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
						}
						else
						{
							/* Do nothing */
						}
					}
					else
					{
						if ((Channel >= 1) && (Channel <= 7))
						{
							ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R59, 0x8B); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
						}
						else if (Channel == 8)
						{
							ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R59, 0x8A); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
						}
						else if (Channel == 9)
						{
							ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R59, 0x89); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
						}
						else if ((Channel >= 10) && (Channel <= 11))
						{
							ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R59, 0x88); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
						}
						else if (Channel == 12)
						{
							ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R59, 0x86); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
						}
						else if (Channel == 13)
						{
							ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R59, 0x85); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
						}	
						else if (Channel == 14)
						{
							RT30xxWriteRFRegister(pAd, RF_R59, 0x84); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
						}
						else
						{
							/* Do nothing */
						}
					}
				}
				else
#endif /* HW_COEXISTENCE_SUPPORT */

				if (IS_RT5392(pAd))
				{
					/* do nothing */
				}
				else if (IS_RT5390F(pAd)) /* >= RT5390F */
				{
						if ((Channel >= 1) && (Channel <=10))
						{							
							RT30xxWriteRFRegister(pAd, RF_R59, 0x07); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
						}
						
						else if (Channel == 11)
						{							
							RT30xxWriteRFRegister(pAd, RF_R59, 0x06); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
						}
						else if (Channel == 12)
						{							
							RT30xxWriteRFRegister(pAd, RF_R59, 0x05); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
						}
						else if ((Channel >= 13) && (Channel <=14))
						{							
							RT30xxWriteRFRegister(pAd, RF_R59, 0x04); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
						}
						else
						{
							/* Do nothing */
						}
				}
				else if (IS_RT5390(pAd))
				{
					if ((Channel >= 1) && (Channel <= 7))
					{
						ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R59, 0x8F); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
					}
					else if (Channel == 8)
					{
						ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R59, 0x8D); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
					}
					else if (Channel == 9)
					{
						ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R59, 0x8A); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
					}
					else if ((Channel >= 10) && (Channel <= 11))
					{
						ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R59, 0x88); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
					}
					else if ((Channel >= 12) && (Channel <= 13))
					{
						ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R59, 0x87); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
					}
					else if (Channel == 14)
					{
						ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R59, 0x86); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
					}
					else
					{
						/* Do nothing */
					}
				}

				ATE_RF_IO_READ8_BY_REG_ID(pAd, RF_R30, (PUCHAR)&RFValue);
				RFValue = ((RFValue & ~0x06) | (TxRxh20M << 1) | (TxRxh20M << 2)); /* tx_h20M and rx_h20M */
				ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R30, (UCHAR)RFValue);

				ATE_RF_IO_READ8_BY_REG_ID(pAd, RF_R30, (PUCHAR)&RFValue);
				RFValue = ((RFValue & ~0x18) | 0x10); /* rxvcm (Rx BB filter VCM) */
				ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R30, (UCHAR)RFValue);

				ATE_RF_IO_READ8_BY_REG_ID(pAd, RF_R03, (PUCHAR)&RFValue);
				/* vcocal_en (initiate VCO calibration (reset after completion)) - It should be at the end of RF configuration.*/
				RFValue = ((RFValue & ~0x80) | 0x80); 
				ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R03, (UCHAR)RFValue);					

				DBGPRINT(RT_DEBUG_TRACE, ("%s: 5390: SwitchChannel#%d(RF=%d, Pwr0=%d, Pwr1=%d, %dT), N=0x%02X, K=0x%02X, R=0x%02X\n",
					__FUNCTION__, 
					Channel, 
					pAd->RfIcType, 
					TxPwer, 
					TxPwer2, 
					pAd->ate.TxAntennaSel, 
					FreqItems3020[index].N, 
					FreqItems3020[index].K, 
					FreqItems3020[index].R));

				break;
			}
		}
	}

	/* Change BBP setting during switch from a->g, g->a */
	if (Channel <= 14)
	{
		UINT32 TxPinCfg = 0x00050F0A;/* 2007.10.09 by Brian : 0x0005050A ==> 0x00050F0A */

		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R62, (0x37 - GET_LNA_GAIN(pAd)));
		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R63, (0x37 - GET_LNA_GAIN(pAd)));
		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R64, (0x37 - GET_LNA_GAIN(pAd)));
		/* According the Rory's suggestion to solve the middle range issue. */
		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R86, 0);	
		

		/* Rx High power VGA offset for LNA select */
		if (pAd->NicConfig2.field.ExternalLNAForG)
		{
			ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R82, 0x62);
			ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R75, 0x46);
		}
		else
		{
			ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R82, 0x84);
			ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R75, 0x50);
		}


		/* 2.4 G band selection PIN */
		RTMP_IO_READ32(pAd, TX_BAND_CFG, &Value);
		Value &= (~0x6);
		Value |= (0x04);
		RTMP_IO_WRITE32(pAd, TX_BAND_CFG, Value);


			/* Turn off unused PA or LNA when only 1T or 1R. */
			if (pAd->Antenna.field.TxPath == 1)
			{
				TxPinCfg &= 0xFFFFFFF3;
			}
			if (pAd->Antenna.field.RxPath == 1)
			{
				TxPinCfg &= 0xFFFFF3FF;
			}

			/* calibration power unbalance issues */
			if (pAd->Antenna.field.TxPath == 2)
			{
				if (pAd->ate.TxAntennaSel == 1)
				{
					TxPinCfg &= 0xFFFFFFF7;
				}
				else if (pAd->ate.TxAntennaSel == 2)
				{
					TxPinCfg &= 0xFFFFFFFD;
				}
			}
		
		RTMP_IO_WRITE32(pAd, TX_PIN_CFG, TxPinCfg);

	}
	/* channel > 14 */
	else
	{
	    UINT32	TxPinCfg = 0x00050F05;/* 2007.10.09 by Brian : 0x00050505 ==> 0x00050F05 */
		
		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R62, (0x37 - GET_LNA_GAIN(pAd)));
		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R63, (0x37 - GET_LNA_GAIN(pAd)));
		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R64, (0x37 - GET_LNA_GAIN(pAd)));
		/* According the Rory's suggestion to solve the middle range issue. */
		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R86, 0);        

		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R82, 0xF2);

		/* Rx High power VGA offset for LNA select */
		if (pAd->NicConfig2.field.ExternalLNAForA)
		{
			ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R75, 0x46);
		}
		else
		{
			ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R75, 0x50);
		}

		ATE_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R91, &BbpValue);
		ASSERT((BbpValue == 0x04));

		/* 5 G band selection PIN, bit1 and bit2 are complement */
		RTMP_IO_READ32(pAd, TX_BAND_CFG, &Value);
		Value &= (~0x6);
		Value |= (0x02);
		RTMP_IO_WRITE32(pAd, TX_BAND_CFG, Value);

		/* Turn off unused PA or LNA when only 1T or 1R. */
		if (pAd->Antenna.field.TxPath == 1)
		{
			TxPinCfg &= 0xFFFFFFF3;
		}

		if (pAd->Antenna.field.RxPath == 1)
		{
			TxPinCfg &= 0xFFFFF3FF;
		}

		RTMP_IO_WRITE32(pAd, TX_PIN_CFG, TxPinCfg);
	}


#if 0
	/* R66 should be set according to Channel. */
	if (Channel <= 14)
	{	
		/* BG band */
			R66 = 0x2E + GET_LNA_GAIN(pAd);

		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R66, R66);
	}
	else
	{	
		/* A band, BW == 20 */
		if (pAd->ate.TxWI.BW == BW_20)
		{
			R66 = (UCHAR)(0x32 + (GET_LNA_GAIN(pAd)*5)/3);


    		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R66, R66);
		}
		else
		{
			/* A band, BW == 40 */
			R66 = (UCHAR)(0x3A + (GET_LNA_GAIN(pAd)*5)/3);

			ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R66, R66);
		}
	}
#endif
/* here change to 	ATE_CHIP_RX_VGA_GAIN_INIT hook*/
	ATE_CHIP_RX_VGA_GAIN_INIT(pAd);

#ifdef RELEASE_EXCLUDE
	/*
		On 11A, We should delay and wait RF/BBP to be stable
		and the appropriate time should be 1000 micro seconds. 

		2005/06/05 - On 11G, We also need this delay time.
		Otherwise it's difficult to pass the WHQL.
	*/
#endif /* RELEASE_EXCLUDE */
	RtmpOsMsDelay(1);  

#ifndef RTMP_RF_RW_SUPPORT
	if (Channel > 14)
	{
		/* When 5.5GHz band the LSB of TxPwr will be used to reduced 7dB or not. */
		DBGPRINT(RT_DEBUG_TRACE, ("SwitchChannel#%d(RF=%d, %dT) to , R1=0x%08x, R2=0x%08x, R3=0x%08x, R4=0x%08x\n",
								  Channel, 
								  pAd->RfIcType, 
								  pAd->Antenna.field.TxPath,
								  pAd->LatchRfRegs.R1, 
								  pAd->LatchRfRegs.R2, 
								  pAd->LatchRfRegs.R3, 
								  pAd->LatchRfRegs.R4));
	}
	else
	{
		DBGPRINT(RT_DEBUG_TRACE, ("SwitchChannel#%d(RF=%d, Pwr0=%u, Pwr1=%u, %dT) to , R1=0x%08x, R2=0x%08x, R3=0x%08x, R4=0x%08x\n",
								  Channel, 
								  pAd->RfIcType, 
								  (R3 & 0x00003e00) >> 9,
								  (R4 & 0x000007c0) >> 6,
								  pAd->Antenna.field.TxPath,
								  pAd->LatchRfRegs.R1, 
								  pAd->LatchRfRegs.R2, 
								  pAd->LatchRfRegs.R3, 
								  pAd->LatchRfRegs.R4));
    }
#endif /* !RTMP_RF_RW_SUPPORT */
}


/* both for RT5370 and RT5372 and RT5390 and RT5392*/
INT RT5390ATETxPwrHandler(
	IN PRTMP_ADAPTER pAd,
	IN char index)
{
	ULONG R;
	CHAR TxPower = 0;
	UCHAR Bbp94 = 0;
	BOOLEAN bPowerReduce = FALSE;
#ifdef RTMP_RF_RW_SUPPORT
	UCHAR RFValue = 0;
#endif /* RTMP_RF_RW_SUPPORT */

#ifdef RALINK_QA
	if ((pAd->ate.bQATxStart == TRUE) || (pAd->ate.bQARxStart == TRUE))
	{
		/* 
			When QA is used for Tx, pAd->ate.TxPower0/1 and real tx power
			are not synchronized.
		*/
		return 0;
	}
	else
#endif /* RALINK_QA */

	if (index == 0)
	{
		TxPower = pAd->ate.TxPower0;
	}
	else if (index == 1)
	{
		TxPower = pAd->ate.TxPower1;
	}
#ifdef DOT11N_SS3_SUPPORT
	else if (index == 2)
	{
		if (IS_RT2883(pAd) || IS_RT3883(pAd) )
			TxPower = pAd->ate.TxPower2;
		else
		{ 	
			DBGPRINT(RT_DEBUG_ERROR, ("Only TxPower0 and TxPower1 are adjustable !\n"));
			DBGPRINT(RT_DEBUG_ERROR, ("TxPower%d is out of range !\n", index));	
		}	
	}
#endif /* DOT11N_SS3_SUPPORT */
	else
	{
#ifdef DOT11N_SS3_SUPPORT
		DBGPRINT(RT_DEBUG_ERROR, ("Only TxPower0, TxPower1, and TxPower2 are adjustable !\n"));
#else
		DBGPRINT(RT_DEBUG_ERROR, ("Only TxPower0 and TxPower1 are adjustable !\n"));
#endif /* DOT11N_SS3_SUPPORT */
		DBGPRINT(RT_DEBUG_ERROR, ("TxPower%d is out of range !\n", index));
	}

#ifdef RTMP_RF_RW_SUPPORT
		if (IS_RT5390(pAd))
		{
				UCHAR ANT_POWER_INDEX=RF_R49+index;
				ATE_RF_IO_READ8_BY_REG_ID(pAd, ANT_POWER_INDEX, (PUCHAR)&RFValue);
				RFValue = ((RFValue & ~0x3F) | (TxPower & 0x3F)); /* tx0_alc */
				ATE_RF_IO_WRITE8_BY_REG_ID(pAd, ANT_POWER_INDEX, (UCHAR)RFValue);
				if (!IS_RT5392(pAd))	
					ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R53, 0x04);
		}
#endif /* RTMP_RF_RW_SUPPORT */
	{
		if (pAd->ate.Channel <= 14)
		{
			if (TxPower > 31)
			{
				/* R3, R4 can't large than 31 (0x24), 31 ~ 36 used by BBP 94 */
				R = 31;
				if (TxPower <= 36)
					Bbp94 = BBPR94_DEFAULT + (UCHAR)(TxPower - 31);		
			}
			else if (TxPower < 0)
			{
				/* R3, R4 can't less than 0, -1 ~ -6 used by BBP 94 */
				R = 0;
				if (TxPower >= -6)
					Bbp94 = BBPR94_DEFAULT + TxPower;
			}
			else
			{  
				/* 0 ~ 31 */
				R = (ULONG) TxPower;
				Bbp94 = BBPR94_DEFAULT;
			}

			DBGPRINT(RT_DEBUG_TRACE, ("%s (TxPower=%d, R=%ld, BBP_R94=%d)\n", __FUNCTION__, TxPower, R, Bbp94));
		}
		else /* 5.5 GHz */
		{
			if (TxPower > 15)
			{
				/* R3, R4 can't large than 15 (0x0F) */
				R = 15;
			}
			else if (TxPower < 0)
			{
				/* R3, R4 can't less than 0 */
				/* -1 ~ -7 */
				ASSERT((TxPower >= -7));
				R = (ULONG)(TxPower + 7);
				bPowerReduce = TRUE;
			}
			else
			{  
				/* 0 ~ 15 */
				R = (ULONG) TxPower;
			}

			DBGPRINT(RT_DEBUG_TRACE, ("%s (TxPower=%d, R=%lu)\n", __FUNCTION__, TxPower, R));
		}

		if (pAd->ate.Channel <= 14)
		{
			if (index == 0)
			{
				/* shift TX power control to correct RF(R3) register bit position */
				R = R << 9;		
				R |= (pAd->LatchRfRegs.R3 & 0xffffc1ff);
				pAd->LatchRfRegs.R3 = R;
			}
			else
			{
				/* shift TX power control to correct RF(R4) register bit position */
				R = R << 6;		
				R |= (pAd->LatchRfRegs.R4 & 0xfffff83f);
				pAd->LatchRfRegs.R4 = R;
			}
		}
		else /* 5.5GHz */
		{
			if (bPowerReduce == FALSE)
			{
				if (index == 0)
				{
					/* shift TX power control to correct RF(R3) register bit position */
					R = (R << 10) | (1 << 9);		
					R |= (pAd->LatchRfRegs.R3 & 0xffffc1ff);
					pAd->LatchRfRegs.R3 = R;
				}
				else
				{
					/* shift TX power control to correct RF(R4) register bit position */
					R = (R << 7) | (1 << 6);		
					R |= (pAd->LatchRfRegs.R4 & 0xfffff83f);
					pAd->LatchRfRegs.R4 = R;
				}
			}
			else
			{
				if (index == 0)
				{
					/* shift TX power control to correct RF(R3) register bit position */
					R = (R << 10);		
					R |= (pAd->LatchRfRegs.R3 & 0xffffc1ff);

					/* Clear bit 9 of R3 to reduce 7dB. */ 
					pAd->LatchRfRegs.R3 = (R & (~(1 << 9)));
				}
				else
				{
					/* shift TX power control to correct RF(R4) register bit position */
					R = (R << 7);		
					R |= (pAd->LatchRfRegs.R4 & 0xfffff83f);

					/* Clear bit 6 of R4 to reduce 7dB. */ 
					pAd->LatchRfRegs.R4 = (R & (~(1 << 6)));
				}
			}
		}
		RtmpRfIoWrite(pAd);
	}

	return 0;
}	


/* both for RT5370 and RT5372 and RT5390 and RT5392*/
VOID RT5390ATERxVGAInit(
	IN PRTMP_ADAPTER		pAd)
{
	PATE_INFO pATEInfo = &(pAd->ate);
	UCHAR R66 = 0x30;
	CHAR LNAGain = GET_LNA_GAIN(pAd);
	
	/* R66 should be set according to Channel. */
	if (pATEInfo->Channel <= 14)
	{	
			R66 = 0x2E + LNAGain;
	}
	else
	{	
			/* A band, BW == 20 */
		if (pATEInfo->TxWI.BW == BW_20)
		{
			R66 = (UCHAR)(0x32 + (LNAGain*5)/3);
		}
		else
		{
			/* A band, BW == 40 */
			R66 = (UCHAR)(0x3A + (LNAGain*5)/3);
		}
	}

	ATEBBPWriteWithRxChain(pAd, BBP_R66, R66, RX_CHAIN_ALL);


	return;
}

INT RT5390_ATETssiCalibration(
	IN	PRTMP_ADAPTER		pAd,
	IN	PSTRING				arg)
{    
	UCHAR inputDAC;
	UINT 		i = 0;
	UCHAR		BbpData = 0, RFValue, OrgBbp47Value;
	USHORT		EEPData;
	UCHAR 		BSSID_ADDR[MAC_ADDR_LEN] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
	BBP_R47_STRUC	BBPR47;
	
	inputDAC = simple_strtol(arg, 0, 10);

	if (!IS_RT5390(pAd) || !(pAd->TxPowerCtrl.bInternalTxALC))                          
	{
		DBGPRINT(RT_DEBUG_TRACE, ("Not support TSSI calibration since not 5390 chip or EEPROM not set!!!\n"));
		return FALSE;
	}
	else if (IS_RT5392(pAd))
	{
		DBGPRINT(RT_DEBUG_WARN, ("Not support TSSI calibration since not 5390 chip or EEPROM not set!!!\n"));
		return FALSE;
	}

	

	/* Set RF R27[3:0] TSSI gain */		
	RT30xxReadRFRegister(pAd, RF_R27, (PUCHAR)(&RFValue));			
	RFValue = ((RFValue & 0xF0) | pAd->TssiGain); /* [3:0] = (tssi_gain and tssi_atten) */
	RT30xxWriteRFRegister(pAd, RF_R27, RFValue);	

	/* Set RF R28 bit[7:6] = 00 */
	RT30xxReadRFRegister(pAd, RF_R28, &RFValue);
	/* RF28Value = RFValue; */
	RFValue &= (~0xC0); 
	RT30xxWriteRFRegister(pAd, RF_R28, RFValue);

	/* set BBP R47[7] = 1(ADC6 ON), R47[4:3] = 0x2(new average TSSI mode), R47[2] = 1(TSSI_UPDATE_REQ), R49[1:0] = 0(TSSI info 0 - TSSI) */
	RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R47, &BBPR47.byte);
	OrgBbp47Value = BBPR47.byte;
	BBPR47.field.Adc6On = 1;
	BBPR47.field.TssiMode = 0x02;
	BBPR47.field.TssiUpdateReq = 1;
	BBPR47.field.TssiReportSel = 0;							
	DBGPRINT(RT_DEBUG_TRACE, ("Write BBP R47 = 0x%x\n", BBPR47.byte));
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R47, BBPR47.byte);		

	/* start TX at 54Mbps, we use channel and power value passed from upper layer program */
	NdisZeroMemory(&pAd->ate, sizeof(struct _ATE_INFO));
	pAd->ate.TxCount = 100;
	pAd->ate.TxLength = 1024;
	 pAd->ate.Channel = 1;
	COPY_MAC_ADDR(pAd->ate.Addr1, BROADCAST_ADDR);
	COPY_MAC_ADDR(pAd->ate.Addr2, pAd->PermanentAddress);                                                     
	COPY_MAC_ADDR(pAd->ate.Addr3, BSSID_ADDR);    

	Set_ATE_TX_MODE_Proc(pAd, "1");		/* MODE_OFDM */
	Set_ATE_TX_MCS_Proc(pAd, "7");		/* 54Mbps */
	Set_ATE_TX_BW_Proc(pAd, "0");		/* 20MHz */
			
	/* set power value calibrated DAC */		
	pAd->ate.TxPower0 = inputDAC;
     	DBGPRINT(RT_DEBUG_TRACE, ("(Calibrated) Tx.Power0= 0x%x\n", pAd->ate.TxPower0));
		 
	/* read frequency offset from EEPROM */                       
	RT28xx_EEPROM_READ16(pAd, EEPROM_FREQ_OFFSET, EEPData);
	pAd->ate.RFFreqOffset = (UCHAR) (EEPData & 0xff);
		
	Set_ATE_Proc(pAd, "TXFRAME"); 
	RTMPusecDelay(200000);

	while (i < 500)
	{
		RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R47, &BbpData);

		if ((BbpData & 0x04) == 0)
			break;

		RTMPusecDelay(2);
		i++;	
	}

	if (i >= 500)
	{
		DBGPRINT(RT_DEBUG_TRACE, ("TSSI status not ready!!! (i=%d)\n", i));
		return FALSE;
	}	

	/* read BBP R49[6:0] and write to EEPROM 0x6E */
	DBGPRINT(RT_DEBUG_TRACE, ("Read  BBP_R49\n")); 
	RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R49, &BbpData);
	DBGPRINT(RT_DEBUG_TRACE, ("BBP R49 = 0x%x\n", BbpData)); 
	BbpData &= 0x7f;

	/* the upper boundary of 0x6E (TSSI base) is 0x7C */
	if (BbpData > 0x7C)
		BbpData = 0;

	RT28xx_EEPROM_READ16(pAd, EEPROM_TSSI_OVER_OFDM_54, EEPData);
	EEPData &= 0xff00;
	EEPData |= BbpData;
	DBGPRINT(RT_DEBUG_TRACE, ("Write  E2P 0x6e: 0x%x\n", EEPData)); 		
	
#ifdef RTMP_EFUSE_SUPPORT
	if (pAd->bUseEfuse)
	{
		if (pAd->bFroceEEPROMBuffer)
			NdisMoveMemory(&(pAd->EEPROMImage[EEPROM_TSSI_OVER_OFDM_54]), (PUCHAR)(&EEPData) ,2);
		else
			eFuseWrite(pAd, EEPROM_TSSI_OVER_OFDM_54, (PUSHORT)(&EEPData), 2);
	}
	else
#endif /* RTMP_EFUSE_SUPPORT */
	{
		RT28xx_EEPROM_WRITE16(pAd, EEPROM_TSSI_OVER_OFDM_54, EEPData);
		RTMPusecDelay(10);
	}    

	/* restore RF R27 and R28, BBP R47 */
	/* RT30xxWriteRFRegister(pAd, RF_R27, RF27Value); */				
	/* RT30xxWriteRFRegister(pAd, RF_R28, RF28Value); */
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R47, OrgBbp47Value);

	Set_ATE_Proc(pAd, "ATESTART");

	return TRUE;
}


INT RT5390ATETssiCalibrationExtend(
	IN	PRTMP_ADAPTER	pAd,
	IN	PSTRING			arg)
{  
	UCHAR inputData;
	
	inputData = simple_strtol(arg, 0, 10);
	
	if (!(IS_RT5390(pAd) && (pAd->TxPowerCtrl.bInternalTxALC) && (pAd->TxPowerCtrl.bExtendedTssiMode)))			
	{
		DBGPRINT(RT_DEBUG_WARN, ("Not support TSSI calibration since not 5390 chip or EEPROM not set!!!\n"));
		return FALSE;
	}	
	else if (IS_RT5392(pAd))
	{
		DBGPRINT(RT_DEBUG_WARN, ("Not support TSSI calibration since not 5390 chip or EEPROM not set!!!\n"));
		return FALSE;
	}
	else
	{				
		UCHAR	RFValue;
		CHAR	TssiRefPerChannel[14+1], PowerDeltaPerChannel[14+1], TssiBase;
		USHORT	EEPData;
		UCHAR	CurrentChannel;

		/* step 0: set init register values for TSSI calibration */
		/* Set RF R27[3:2] = 00, R27[1:0] = 11 */
		RT30xxReadRFRegister(pAd, RF_R27, &RFValue);
		/* RF27Value = RFValue; */
		/* RFValue &= (~0x0F); */
		/* RFValue |= 0x02; */ 
		RFValue = ((RFValue & 0xF0) | pAd->TssiGain); /* [3:0] = (tssi_gain and tssi_atten) */
		RT30xxWriteRFRegister(pAd, RF_R27, RFValue);

		/* Set RF R28 bit[7:6] = 00 */
		RT30xxReadRFRegister(pAd, RF_R28, &RFValue);
		/* RF28Value = RFValue; */
		RFValue &= (~0xC0); 
		RT30xxWriteRFRegister(pAd, RF_R28, RFValue);

		/* step 1: get channel 7 TSSI as reference value */
		CurrentChannel = 7;
		TssiRefPerChannel[CurrentChannel] = RTATEGetTssiByChannel(pAd, CurrentChannel);
		TssiBase = TssiRefPerChannel[CurrentChannel];
		PowerDeltaPerChannel[CurrentChannel] = GetPowerDeltaFromTssiRatio(TssiRefPerChannel[CurrentChannel], TssiBase);

		/* Save TSSI ref base to EEPROM 0x6E */
		RT28xx_EEPROM_READ16(pAd, EEPROM_TSSI_OVER_OFDM_54, EEPData);
		EEPData &= 0xff00;
		EEPData |= TssiBase;
		DBGPRINT(RT_DEBUG_WARN, ("Write  E2P 0x6E: 0x%x\n", EEPData)); 				
		RT28xx_EEPROM_WRITE16(pAd, EEPROM_TSSI_OVER_OFDM_54, EEPData);
		RTMPusecDelay(10); /* delay for twp(MAX)=10ms */
		
		/* step 2: get channel 1 and 13 TSSI values */
		/* start TX at 54Mbps */
		CurrentChannel = 1;
		TssiRefPerChannel[CurrentChannel] = RTATEGetTssiByChannel(pAd, CurrentChannel);
		PowerDeltaPerChannel[CurrentChannel] = GetPowerDeltaFromTssiRatio(TssiRefPerChannel[CurrentChannel], TssiBase);

		/* start TX at 54Mbps */
		CurrentChannel = 13;
		TssiRefPerChannel[CurrentChannel] = RTATEGetTssiByChannel(pAd, CurrentChannel);
		PowerDeltaPerChannel[CurrentChannel] = GetPowerDeltaFromTssiRatio(TssiRefPerChannel[CurrentChannel], TssiBase);

		/* step 3: insert the power table */
		/* insert channel 2 to 6 TSSI values */
		/*
			for(CurrentChannel = 2; CurrentChannel <7; CurrentChannel++)
				TssiRefPerChannel[CurrentChannel] = RTATEInsertTssi(CurrentChannel, 1, 7, TssiRefPerChannel[1], TssiRefPerChannel[7]);
		*/
		for (CurrentChannel = 2; CurrentChannel < 7; CurrentChannel++)
			PowerDeltaPerChannel[CurrentChannel] = RTATEInsertTssi(CurrentChannel, 1, 7, PowerDeltaPerChannel[1], PowerDeltaPerChannel[7]);

		/* insert channel 8 to 12 TSSI values */
		/*
			for(CurrentChannel = 8; CurrentChannel < 13; CurrentChannel++)
				TssiRefPerChannel[CurrentChannel] = RTATEInsertTssi(CurrentChannel, 7, 13, TssiRefPerChannel[7], TssiRefPerChannel[13]);
		*/
		for (CurrentChannel = 8; CurrentChannel < 13; CurrentChannel++)
			PowerDeltaPerChannel[CurrentChannel] = RTATEInsertTssi(CurrentChannel, 7, 13, PowerDeltaPerChannel[7], PowerDeltaPerChannel[13]);


		/* channel 14 TSSI equals channel 13 TSSI */
		/* TssiRefPerChannel[14] = TssiRefPerChannel[13]; */
		PowerDeltaPerChannel[14] = PowerDeltaPerChannel[13];

		for (CurrentChannel = 1; CurrentChannel <= 14; CurrentChannel++)
		{
			DBGPRINT(RT_DEBUG_WARN, ("Channel %d, PowerDeltaPerChannel= 0x%x\n", CurrentChannel, PowerDeltaPerChannel[CurrentChannel]));
		
			/* PowerDeltaPerChannel[CurrentChannel] = GetPowerDeltaFromTssiRatio(TssiRefPerChannel[CurrentChannel], TssiBase); */

			/* boundary check */
			if (PowerDeltaPerChannel[CurrentChannel] > 7)
				PowerDeltaPerChannel[CurrentChannel] = 7;
			if (PowerDeltaPerChannel[CurrentChannel] < -8)
				PowerDeltaPerChannel[CurrentChannel] = -8;

			/* eeprom only use 4 bit for TSSI delta */
			PowerDeltaPerChannel[CurrentChannel] &= 0x0f;
			DBGPRINT(RT_DEBUG_WARN, ("Channel = %d, PowerDeltaPerChannel=0x%x\n", CurrentChannel, PowerDeltaPerChannel[CurrentChannel]));	
		}
	

		/* step 4: store TSSI delta values to EEPROM 0x6f - 0x75 */
		RT28xx_EEPROM_READ16(pAd, EEPROM_TX_POWER_OFFSET_OVER_CH_1-1, EEPData);
		EEPData &= 0x00ff;
		EEPData |= (PowerDeltaPerChannel[1] << 8) | (PowerDeltaPerChannel[2] << 12);
		RT28xx_EEPROM_WRITE16(pAd, EEPROM_TX_POWER_OFFSET_OVER_CH_1-1, EEPData);
		
		for (CurrentChannel = 3; CurrentChannel <= 14; CurrentChannel += 4)
		{
			/* EEPData = ( TssiDeltaPerChannel[CurrentChannel+2]  << 12) |(  TssiDeltaPerChannel[CurrentChannel+1]  << 8); */
			/* DBGPRINT(RT_DEBUG_TRACE, ("CurrentChannel=%d, TssiDeltaPerChannel[CurrentChannel+2] = 0x%x, EEPData=0x%x\n", CurrentChannel, TssiDeltaPerChannel[CurrentChannel+2], EEPData)); */
			EEPData = (PowerDeltaPerChannel[CurrentChannel + 3] << 12) | (PowerDeltaPerChannel[CurrentChannel + 2] << 8) | 
				(PowerDeltaPerChannel[CurrentChannel + 1] << 4) | PowerDeltaPerChannel[CurrentChannel];
			RT28xx_EEPROM_WRITE16(pAd, (EEPROM_TX_POWER_OFFSET_OVER_CH_3 + ((CurrentChannel - 3) / 2)), EEPData);
			/* DBGPRINT(RT_DEBUG_TRACE, ("offset=0x%x, EEPData = 0x%x\n", (EEPROM_TSSI_DELTA_CH3_CH4 +((CurrentChannel-3)/2)),EEPData));	*/
		}
						
		/* restore RF R27 and R28, BBP R47 */
		/* RT30xxWriteRFRegister(pAd, RF_R27, RF27Value); */				
		/* RT30xxWriteRFRegister(pAd, RF_R28, RF28Value); */

		Set_ATE_Proc(pAd, "ATESTART");
	}

	return TRUE;
}





/* 
==========================================================================
    Description:
        Set  RT5370 and RT5372 and RT5390 and RT5392  ATE RF BW
        
    Return:
        TRUE if all parameters are OK, FALSE otherwise
==========================================================================
*/
INT	RT5390_Set_ATE_TX_BW_Proc(
	IN	PRTMP_ADAPTER	pAd, 
	IN	PSTRING			arg)
{
	INT powerIndex;
	UCHAR value = 0;
	UCHAR BBPCurrentBW;
	
	BBPCurrentBW = simple_strtol(arg, 0, 10);

	if ((BBPCurrentBW == 0))
	{
		pAd->ate.TxWI.TxWIBW = BW_20;
	}
	else
	{
		pAd->ate.TxWI.TxWIBW = BW_40;
 	}

	if ((pAd->ate.TxWI.TxWIPHYMODE == MODE_CCK) && (pAd->ate.TxWI.TxWIBW == BW_40))
	{
		DBGPRINT(RT_DEBUG_ERROR, ("Set_ATE_TX_BW_Proc!! Warning!! CCK only supports 20MHZ!!\nBandwidth switch to 20\n"));
		pAd->ate.TxWI.TxWIBW = BW_20;
	}

	if (pAd->ate.TxWI.TxWIBW == BW_20)
	{
		if (pAd->ate.Channel <= 14)
		{
			/* BW=20;G band */
 			for (powerIndex=0; powerIndex<MAX_TXPOWER_ARRAY_SIZE; powerIndex++)
 			{
				if (pAd->Tx20MPwrCfgGBand[powerIndex] == 0xffffffff)
					continue;
				RTMP_IO_WRITE32(pAd, TX_PWR_CFG_0 + powerIndex*4, pAd->Tx20MPwrCfgGBand[powerIndex]);	
				RtmpOsMsDelay(5);				
			}
		}
		else
		{
			/* BW=20;A band */
 			for (powerIndex=0; powerIndex<MAX_TXPOWER_ARRAY_SIZE; powerIndex++)
 			{
				if (pAd->Tx20MPwrCfgABand[powerIndex] == 0xffffffff)
					continue;
				RTMP_IO_WRITE32(pAd, TX_PWR_CFG_0 + powerIndex*4, pAd->Tx20MPwrCfgABand[powerIndex]);
 				RtmpOsMsDelay(5);				
 			}
		}

		/* BW=20 */
		{
		/* Set BBP R4 bit[4:3]=0:0 */
 		ATE_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R4, &value);
 		value &= (~0x18);
 		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R4, value);
		}


		/* Set BBP R66=0x3C */
		value = 0x3C;
		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R66, value);

		if (IS_RT5390(pAd))
		{
			ATE_RF_IO_READ8_BY_REG_ID(pAd, RF_R30, &value);
			value &= ~(0x06); // 20MBW Bit[2:1]=0,0
			ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R30, value);
		}		

		/* set BW = 20 MHz */
		{
			pAd->LatchRfRegs.R4 &= ~0x00200000;
			RtmpRfIoWrite(pAd);
		}
		/* BW = 20 MHz */
		{
			/* Set BBP R68=0x0B to improve Rx sensitivity. */
			value = 0x0B;
			ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R68, value);
			/* Set BBP R69=0x16 */
			if ( IS_RT5390(pAd))
				value = 0x12;
			else
				value = 0x16;
	 		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R69, value);
			/* Set BBP R70=0x08 */
			if ( IS_RT5390(pAd))
				value = 0x0A;
			else
				value = 0x08;
	 		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R70, value);
			/* Set BBP R73=0x11 */
		        if ( IS_RT5390(pAd))
			    value = 0x13;
		        else
			    value = 0x11;

	 		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R73, value);
		}

#ifdef RELEASE_EXCLUDE
	    /*
			If Channel=14, Bandwidth=20M and Mode=CCK, Set BBP R4 bit5=1
			(to set Japan filter coefficients).
			This segment of code will only works when ATETXMODE and ATECHANNEL
			were set to MODE_CCK and 14 respectively before ATETXBW is set to 0.
	    */
#endif /* RELEASE_EXCLUDE */
		/* Please don't move this block backward. */
		/* BBP_R4 should be overwritten for every chip if the condition matched. */
		if (pAd->ate.Channel == 14)
		{
			INT TxMode = pAd->ate.TxWI.TxWIPHYMODE;

			if (TxMode == MODE_CCK)
			{
				/* when Channel==14 && Mode==CCK && BandWidth==20M, BBP R4 bit5=1 */
 				ATE_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R4, &value);
				value |= 0x20; /* set bit5=1 */
 				ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R4, value);				
			}
		}
	}
	/* If bandwidth = 40M, set RF Reg4 bit 21 = 0. */
	else if (pAd->ate.TxWI.TxWIBW == BW_40)
	{
		if (pAd->ate.Channel <= 14)
		{
			/* BW=40;G band */
			for (powerIndex=0; powerIndex<MAX_TXPOWER_ARRAY_SIZE; powerIndex++)
			{
				if (pAd->Tx40MPwrCfgGBand[powerIndex] == 0xffffffff)
					continue;
				RTMP_IO_WRITE32(pAd, TX_PWR_CFG_0 + powerIndex*4, pAd->Tx40MPwrCfgGBand[powerIndex]);	
				RtmpOsMsDelay(5);				
			}
		}
		else
		{
			/* BW=40;A band */
			for (powerIndex=0; powerIndex<MAX_TXPOWER_ARRAY_SIZE; powerIndex++)
			{
				if (pAd->Tx40MPwrCfgABand[powerIndex] == 0xffffffff)
					continue;
				RTMP_IO_WRITE32(pAd, TX_PWR_CFG_0 + powerIndex*4, pAd->Tx40MPwrCfgABand[powerIndex]);	
				RtmpOsMsDelay(5);				
			}		

			if ((pAd->ate.TxWI.TxWIPHYMODE >= 2) && (pAd->ate.TxWI.TxWIMCS == 7))
			{
    				value = 0x28;
    				ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R67, value);
			}
		}

		{
			/* Set BBP R4 bit[4:3]=1:0 */
			ATE_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R4, &value);
			value &= (~0x18);
			value |= 0x10;
			ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R4, value);
		}

		/* Set BBP R66=0x3C */
		value = 0x3C;
		ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R66, value);

		/* set BW = 40 MHz */
		{
		pAd->LatchRfRegs.R4 |= 0x00200000;
		RtmpRfIoWrite(pAd);
		}
		/* BW = 40 MHz */
		{
			/* Set BBP R68=0x0C to improve Rx sensitivity. */
			value = 0x0C;
			ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R68, value);
			/* Set BBP R69=0x1A */
			value = 0x1A;
			ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R69, value);
			/* Set BBP R70=0x0A */
			value = 0x0A;
			ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R70, value);
			/* Set BBP R73=0x16 */
		        if (IS_RT5390(pAd))
			    value = 0x13;
		        else
			    value = 0x16;
			ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R73, value);
		}
	}

	DBGPRINT(RT_DEBUG_TRACE, ("Set_ATE_TX_BW_Proc (BBPCurrentBW = %d)\n", pAd->ate.TxWI.BW));
	DBGPRINT(RT_DEBUG_TRACE, ("Ralink: Set_ATE_TX_BW_Proc Success\n"));

#ifdef CONFIG_AP_SUPPORT
#ifdef GEMTEK_ATE
	DBGPRINT(RT_DEBUG_OFF,  (KERN_EMERG "Gemtek:Success\n"));
#endif /* GEMTEK_ATE */
#endif /* CONFIG_AP_SUPPORT */
	
	return TRUE;
}	


VOID RT5390ATEAsicSetTxRxPath(
    IN PRTMP_ADAPTER pAd)
{
	UCHAR	RFValue = 0, BbpValue = 0;

	if (IS_RT5392(pAd))
	{
		RFValue = 0x03;

		/* Set TX path, pAd->TxAntennaSel : 0 -> All, 1 -> TX0, 2 -> TX1 */
		switch(pAd->Antenna.field.TxPath)
		{
			case 2:
				switch (pAd->ate.TxAntennaSel)
				{
					case 1:
						/* set BBP R1, bit 4:3 = 00 */
						ATE_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R1, &BbpValue);
						BbpValue &= 0xE7;		/* 11100111B */
						ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R1, BbpValue);

						/* set RF R1, bit 7:5:3 = 001  */					
						RFValue &=  ~TXPowerEnMask;
						RFValue = RFValue | 0x08;
						break;
					case 2:	
						/* set BBP R1, bit 4:3 = 01 */
						ATE_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R1, &BbpValue);
						BbpValue &= 0xE7;	
						BbpValue |= 0x08;
						ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R1, BbpValue);

						/* set RF R1, bit 7:5:3 = 010 */					
						RFValue &=  ~TXPowerEnMask;
						RFValue = RFValue | 0x20;
						break;
					default:		
						/* set BBP R1, bit 4:3 = 10 */
						ATE_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R1, &BbpValue);
						BbpValue &= 0xE7;
						BbpValue |= 0x10;
						ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R1, BbpValue);

						/* set RF R1, bit 7:5:3 = 011 */
						RFValue &=  ~TXPowerEnMask;
						RFValue = RFValue | 0x28;
					break;						
			}
			break;

		default:
				/* set RF R1, bit 7:5:3 = 011 */
				RFValue &=  ~TXPowerEnMask;
				RFValue = RFValue | 0x28;
				break;
		}


		/* Set RX path, pAd->RxAntennaSel : 0 -> All, 1 -> RX0, 2 -> RX1, 3 -> RX2 */
		switch (pAd->Antenna.field.RxPath)
		{
			case 3:
				switch (pAd->ate.RxAntennaSel)
				{
					case 1:
						/* set BBP R3, bit 4:3:1:0 = 0000 */							
						ATE_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R3, &BbpValue);
						BbpValue &= 0xE4;
						BbpValue |= 0x00;
						ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R3, BbpValue);

						/* set RF R1, bit 6:4:2 = 110 */
						ATE_RF_IO_READ8_BY_REG_ID(pAd, RF_R01, &RFValue);
						RFValue = RFValue & 0xAB;
						RFValue = RFValue | 0x50;
						ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R01, RFValue);
						break;
					case 2:
						/* set BBP R3, bit 4:3:1:0 = 0001	 */							
						ATE_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R3, &BbpValue);
						BbpValue &= 0xE4;
						BbpValue |= 0x01;
						ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R3, BbpValue);									

						/* set RF R1, bit 6:4:2 = 101 */
						ATE_RF_IO_READ8_BY_REG_ID(pAd, RF_R01, &RFValue);
						RFValue = RFValue & 0xAB;
						RFValue = RFValue | 0x44;
						ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R01, RFValue);
						break;
					case 3:	
						/* set BBP R3, bit 4:3:1:0 = 0002 */								
						ATE_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R3, &BbpValue);
						BbpValue &= 0xE4;
						BbpValue |= 0x02;
						ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R3, BbpValue);

						/* set RF R1, bit 6:4:2 = 011 */
						ATE_RF_IO_READ8_BY_REG_ID(pAd, RF_R01, &RFValue);
						RFValue = RFValue & 0xAB;
						RFValue = RFValue | 0x14;
						ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R01, RFValue);
						break;								
					default:	
						/* set BBP R3, bit 4:3:1:0 = 1000 */
						ATE_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R3, &BbpValue);
						BbpValue &= 0xE4;
						BbpValue |= 0x10;
						ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R3, BbpValue);								

						/* set RF R1, bit 6:4:2 = 000 */
						/* RT30xxReadRFRegister(pAd, RF_R01, (PUCHAR)&Value); */
						/* Value = Value & 0xAB; */
						/* RT30xxWriteRFRegister(pAd, RF_R01, (UCHAR)Value); */
						break;
				}
				break;

			case 2:						
			switch (pAd->ate.RxAntennaSel)
			{
					case 1:	
						/* set BBP R3, bit 4:3:1:0 = 0000 */
						ATE_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R3, &BbpValue);
						BbpValue &= 0xE4;
						BbpValue |= 0x00;
						ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R3, BbpValue);								

						/* set RF R1, bit 6:4:2 = 001 */				
						RFValue &=  ~RXPowerEnMask;
						RFValue |=  0x04;
						break;
					case 2:								
						/* set BBP R3, bit 4:3:1:0 = 0001 */
						ATE_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R3, &BbpValue);
						BbpValue &= 0xE4;
						BbpValue |= 0x01;
						ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R3, BbpValue);

						/* set RF R1, bit 6:4:2 = 010 */
						RFValue &=  ~RXPowerEnMask;
						RFValue |= 0x10;
						break;							
				default:
						/* set BBP R3, bit 4:3:1:0 = 0100 */		
						ATE_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R3, &BbpValue);
						BbpValue &= 0xE4;
						BbpValue |= 0x08;
						ATE_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R3, BbpValue);								

						/* set RF R1, bit 6:4:2 = 011 */
						RFValue &=  ~RXPowerEnMask;
						RFValue |= 0x14;
					break;
			}
			break;		

			default:
				/* set RF R1, bit 6:4:2 = 011 */
				RFValue &=  ~RXPowerEnMask;
				RFValue |= 0x14;			
				break;		
	}

		ATE_RF_IO_WRITE8_BY_REG_ID(pAd, RF_R01, RFValue);
	}

}


/* 
==========================================================================
    Description:
        Set RT5370 and RT5372 and RT5390 and RT5392   ATE RF central frequency offset
        
    Return:
        TRUE if all parameters are OK, FALSE otherwise
==========================================================================
*/
INT	RT5390_Set_ATE_TX_FREQ_OFFSET_Proc(
	IN	PRTMP_ADAPTER	pAd, 
	IN	PSTRING			arg)
{
	UCHAR RFFreqOffset = 0;
	ULONG R4 = 0;
#ifdef RTMP_RF_RW_SUPPORT
	UCHAR RFValue = 0;
#endif /* RTMP_RF_RW_SUPPORT */
	UCHAR PreRFValue = 0;
	RFFreqOffset = simple_strtol(arg, 0, 10);

#ifdef RTMP_RF_RW_SUPPORT
	/* RT35xx ATE will reuse this code segment. */
	/* 2008/08/06: KH modified the limit of offset value from 64 to 96(0x5F + 0x01) */
	if (RFFreqOffset >= 96)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("Set_ATE_TX_FREQOFFSET_Proc::Out of range(0 ~ 95).\n"));
		return FALSE;
	}
#else
	if (RFFreqOffset >= 64)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("Set_ATE_TX_FREQOFFSET_Proc::Out of range(0 ~ 63).\n"));
		return FALSE;
	}
#endif /* RTMP_RF_RW_SUPPORT */

	pAd->ate.RFFreqOffset = RFFreqOffset;

#ifdef RTMP_RF_RW_SUPPORT
	if ( IS_RT5390(pAd))
	{
		ATE_RF_IO_READ8_BY_REG_ID(pAd, RF_R17, (PUCHAR)&RFValue);
		PreRFValue = RFValue;
		RFValue = ((RFValue & 0x80) | (pAd->ate.RFFreqOffset & 0x7F)); // xo_code (C1 value control) - Crystal calibration
		RFValue = min((INT)RFValue, 0x5F);
		if (PreRFValue != RFValue)
		{
			AsicSendCommandToMcu(pAd, 0x74, 0xff, RFValue, PreRFValue, FALSE);
		}
	}
	else
#endif /* RTMP_RF_RW_SUPPORT */
	{
		/* RT28xx */
		/* shift TX power control to correct RF register bit position */
		R4 = pAd->ate.RFFreqOffset << 15;		
		R4 |= (pAd->LatchRfRegs.R4 & ((~0x001f8000)));
		pAd->LatchRfRegs.R4 = R4;
		
		RtmpRfIoWrite(pAd);
	}
		
	DBGPRINT(RT_DEBUG_TRACE, ("Set_ATE_TX_FREQOFFSET_Proc (RFFreqOffset = %d)\n", pAd->ate.RFFreqOffset));
	DBGPRINT(RT_DEBUG_TRACE, ("Ralink: Set_ATE_TX_FREQOFFSET_Proc Success\n"));

#ifdef CONFIG_AP_SUPPORT
#ifdef GEMTEK_ATE
	DBGPRINT(RT_DEBUG_OFF, (KERN_EMERG "Gemtek:Success\n"));
#endif /* GEMTEK_ATE */
#endif /* CONFIG_AP_SUPPORT */
	
	return TRUE;
}



struct _ATE_CHIP_STRUCT RALINK5390 =
{
	/* functions */
	.ChannelSwitch = RT5390ATEAsicSwitchChannel,
	.TxPwrHandler = RT5390ATETxPwrHandler,
	.AsicExtraPowerOverMAC = DefaultATEAsicExtraPowerOverMAC,
//	if (IS_RT5392(pAd))
//	{
//why not have ATETssiCalibration ???
//		pChipOps->ATETssiCalibration = NULL,
//		.ExtendedTssiCalibration = NULL,
//	}
//	else
//	{
//why not have ATETssiCalibration ???
//		RT5390_ATETssiCalibration,
		.TssiCalibration = RT5390_ATETssiCalibration,
		.ExtendedTssiCalibration = RT5390ATETssiCalibrationExtend,
//	}	
	.RxVGAInit = RT5390ATERxVGAInit,
	.AsicSetTxRxPath = RT5390ATEAsicSetTxRxPath,	
	.Set_BW_Proc = RT5390_Set_ATE_TX_BW_Proc,
	.Set_FREQ_OFFSET_Proc = RT5390_Set_ATE_TX_FREQ_OFFSET_Proc,
	.maxTxPwrCnt = 5,
	.bBBPStoreTXCARR = TRUE,
	.bBBPStoreTXCARRSUPP = TRUE,	
	.bBBPStoreTXCONT = TRUE,
	.bBBPLoadATESTOP = TRUE,/* ralink debug */
};


#endif /* defined(RT5370) || defined(RT5372) || defined(RT5390) || defined(RT5392) */

