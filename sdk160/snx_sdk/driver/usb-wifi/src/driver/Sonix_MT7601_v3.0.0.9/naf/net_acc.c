/*
	Network Acceleration related function
*/

#include "rt_config.h"


#if defined(CONFIG_CSO_SUPPORT) || defined(CONFIG_TSO_SUPPORT)
VOID dump_tsoinfo(TSO_INFO *tinfo)
{
	DBGPRINT(RT_DEBUG_OFF, ("TSO_INFO:\n"));
	hex_dump("\traw data", (UCHAR *)tinfo, sizeof(TSO_INFO));	
	DBGPRINT(RT_DEBUG_OFF, ("\ttcp=%d\n", tinfo->tcp));
	DBGPRINT(RT_DEBUG_OFF, ("\ttups=%d\n", tinfo->tups));
	DBGPRINT(RT_DEBUG_OFF, ("\tips=%d\n", tinfo->ips));
	DBGPRINT(RT_DEBUG_OFF, ("\tmss=%d\n", tinfo->mss));
}

#ifdef CONFIG_TSO_SUPPORT
INT rlt_tso_info_write(RTMP_ADAPTER *pAd, TSO_INFO *tinfo, TX_BLK *pTxBlk, int hdr_len)
{
	ULONG offset = GET_OS_PKT_DATAPTR(pTxBlk->pPacket) - pTxBlk->pSrcBufData + hdr_len;
	
	tinfo->ips = pTxBlk->tso_info.ips + offset;
	tinfo->tups = pTxBlk->tso_info.tups;
	tinfo->tcp = pTxBlk->tso_info.tcp;
	tinfo->mss = pTxBlk->tso_info.mss;

	if (pTxBlk->naf_type & NAF_TYPE_TSO)
		dump_tsoinfo(tinfo);
	return TRUE;
}
#endif /* CONFIG_TSO_SUPPORT */

INT rlt_net_acc_exit(RTMP_ADAPTER *pAd)
{

	return TRUE;
}


INT rlt_net_acc_init(RTMP_ADAPTER *pAd)
{
	UINT32 val;

#ifdef RT5592
	if (IS_ASIC_CAP(pAd, fASIC_CAP_CSO))
		rtmp_cso_enable(pAd);
#endif /* RT5592 */

#ifdef RT65xx
	//RTMP_IO_READ32(pAd, FCE_L2_STUFF, &val);
	val = 0x3ff023b;
	if (IS_ASIC_CAP(pAd, fASIC_CAP_CSO | fASIC_CAP_TSO))
		val |= 0x8; /* enable TSO_INFO field removal operation for FCE */
	else
		val &= (~0x8);
	RTMP_IO_WRITE32(pAd, FCE_L2_STUFF, val);

	if (IS_ASIC_CAP(pAd, fASIC_CAP_TSO)) {
		RTMP_IO_WRITE32(pAd, TSO_CTRL, 0x50050);
	} else {
		RTMP_IO_WRITE32(pAd, TSO_CTRL, 0);
	}
	
	if (IS_ASIC_CAP(pAd, fASIC_CAP_CSO)) {
		RTMP_IO_WRITE32(pAd, FCE_CSO, 0x3ff);
	}
#endif /* RT65xx */

	return TRUE;
}
#endif /* defined(CONFIG_CSO_SUPPORT) || defined(CONFIG_TSO_SUPPORT) */

