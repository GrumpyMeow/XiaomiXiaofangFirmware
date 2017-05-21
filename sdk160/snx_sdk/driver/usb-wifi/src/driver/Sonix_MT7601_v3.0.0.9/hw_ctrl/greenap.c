/*

*/

#include "rt_config.h"


#ifdef GREENAP_SUPPORT
#ifdef RT305x
extern REG_PAIR   RT305x_RFRegTable[];
#endif /* RT305x */
static VOID EnableAPMIMOPSv2(
	IN PRTMP_ADAPTER		pAd,
	IN BOOLEAN				ReduceCorePower)
{
	UCHAR	BBPR3 = 0,BBPR1 = 0;
	UINT32 	macdata=0;

	/* enable MMPS BBP control register*/
	RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R3, &BBPR3);
	BBPR3 |= 0x04;
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R3, BBPR3);

	/* enable MMPS MAC control register*/
	RTMP_IO_READ32(pAd, 0x1210, &macdata);
	macdata |= 0x09;
	RTMP_IO_WRITE32(pAd, 0x1210, macdata);
		
	DBGPRINT(RT_DEBUG_INFO, ("EnableAPMIMOPSNew, 30xx changes the # of antenna to 1\n"));
}

static VOID DisableAPMIMOPSv2(
	IN PRTMP_ADAPTER		pAd)
{
	UCHAR	BBPR3=0,BBPR1=0;
	UINT32 	macdata=0;
	
	RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R3, &BBPR3);
	BBPR3 &= ~(0x04);
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R3, BBPR3);

	/* enable MMPS MAC control register*/
	RTMP_IO_READ32(pAd, 0x1210, &macdata);
	macdata &= ~(0x09);
	RTMP_IO_WRITE32(pAd, 0x1210, macdata);
		
	DBGPRINT(RT_DEBUG_INFO, ("DisableAPMIMOPSNew, 30xx reserve only one antenna\n"));
}

static VOID EnableAPMIMOPSv1(
	IN PRTMP_ADAPTER		pAd,
	IN BOOLEAN				ReduceCorePower)
{
	UCHAR	BBPR3 = 0,BBPR1 = 0;
	ULONG	TxPinCfg = 0x00050F0A;/*Gary 2007/08/09 0x050A0A*/
	UCHAR	BBPR4=0;
	UCHAR	CentralChannel;


#ifdef RT305x
	UCHAR 	RFValue=0;
		
	RT30xxReadRFRegister(pAd, RF_R01, &RFValue);
	RFValue &= 0x03;	//clear bit[7~2]
	RFValue |= 0x3C; // default 2Tx 2Rx
	// turn off tx1
	RFValue &= ~(0x1 << 5);
	// turn off rx1
	RFValue &= ~(0x1 << 4);
	// Turn off unused PA or LNA when only 1T or 1R
#endif /* RT305x */

	if(pAd->CommonCfg.Channel>14)
		TxPinCfg=0x00050F05;
		
	TxPinCfg &= 0xFFFFFFF3;
	TxPinCfg &= 0xFFFFF3FF;
	pAd->ApCfg.bGreenAPActive=TRUE;

	CentralChannel = pAd->CommonCfg.CentralChannel;
	DBGPRINT(RT_DEBUG_INFO, ("Run with BW_20\n"));
	pAd->CommonCfg.CentralChannel = pAd->CommonCfg.Channel;
	CentralChannel = pAd->CommonCfg.Channel;

	/* Set BBP registers to BW20 */
	rtmp_bbp_set_bw(pAd, BW_20);

	/* RF Bandwidth related registers would be set in AsicSwitchChannel() */
	if (pAd->Antenna.field.RxPath>1||pAd->Antenna.field.TxPath>1)
	{
		/*TX Stream*/
		rtmp_bbp_set_txdac(pAd, 0);
		
		/*Rx Stream*/
		rtmp_bbp_set_rxpath(pAd, 1);
		
	RTMP_IO_WRITE32(pAd, TX_PIN_CFG, TxPinCfg);

#ifdef RT305x
	RT30xxWriteRFRegister(pAd, RF_R01, RFValue);
#endif /* RT305x */
	}
	AsicSwitchChannel(pAd, CentralChannel, FALSE);

	DBGPRINT(RT_DEBUG_INFO, ("EnableAPMIMOPS, 305x/28xx changes the # of antenna to 1\n"));
}


static VOID DisableAPMIMOPSv1(
	IN PRTMP_ADAPTER		pAd)
{
	UCHAR	BBPR3=0,BBPR1=0;
	ULONG	TxPinCfg = 0x00050F0A;/*Gary 2007/08/09 0x050A0A*/

	UCHAR	CentralChannel;
	UINT32	Value=0;


#ifdef RT305x
	UCHAR 	RFValue=0;

	RT30xxReadRFRegister(pAd, RF_R01, &RFValue);
	RFValue &= 0x03;	//clear bit[7~2]
	RFValue |= 0x3C; // default 2Tx 2Rx
#endif /* RT305x */

	if(pAd->CommonCfg.Channel>14)
		TxPinCfg=0x00050F05;
	/* Turn off unused PA or LNA when only 1T or 1R*/
	if (pAd->Antenna.field.TxPath == 1)
		TxPinCfg &= 0xFFFFFFF3;
	if (pAd->Antenna.field.RxPath == 1)
		TxPinCfg &= 0xFFFFF3FF;

	pAd->ApCfg.bGreenAPActive=FALSE;

	if ((pAd->CommonCfg.HtCapability.HtCapInfo.ChannelWidth == BW_40) && (pAd->CommonCfg.Channel != 14))
	{
		INT ext_ch = EXTCHA_NONE;

		DBGPRINT(RT_DEBUG_INFO, ("Run with BW_40\n"));
		/* Set CentralChannel to work for BW40 */
		if (pAd->CommonCfg.RegTransmitSetting.field.EXTCHA == EXTCHA_ABOVE)
		{
			pAd->CommonCfg.CentralChannel = pAd->CommonCfg.Channel + 2;
			ext_ch = EXTCHA_ABOVE;
		}
		else if ((pAd->CommonCfg.Channel > 2) && (pAd->CommonCfg.RegTransmitSetting.field.EXTCHA == EXTCHA_BELOW)) 
		{
			pAd->CommonCfg.CentralChannel = pAd->CommonCfg.Channel - 2;
			ext_ch = EXTCHA_BELOW;
		}
		CentralChannel = pAd->CommonCfg.CentralChannel;

		AsicSetChannel(pAd, CentralChannel, BW_40, ext_ch, FALSE);
	}

	/*Tx Stream*/
	if (WMODE_CAP_N(pAd->CommonCfg.PhyMode) && (pAd->Antenna.field.TxPath == 2))
		rtmp_bbp_set_txdac(pAd, 2);
	else
		rtmp_bbp_set_txdac(pAd, 0);

	/*Rx Stream*/
	rtmp_bbp_set_rxpath(pAd, pAd->Antenna.field.RxPath);

	RTMP_IO_WRITE32(pAd, TX_PIN_CFG, TxPinCfg);

#ifdef RT305x
	RT30xxWriteRFRegister(pAd, RF_R01, RFValue);
#endif /* RT305x */

	DBGPRINT(RT_DEBUG_INFO, ("DisableAPMIMOPS, 305x/28xx reserve only one antenna\n"));
}
#endif /* GREENAP_SUPPORT */

