#ifdef DOT11V_WNM_SUPPORT
#include "rt_config.h"

#define ISWNM_MULTICAST_MAC_ADDR(Addr)			((((Addr[0]) & 0x01) == 0x01) && ((Addr[0]) != 0xff))
#define ISWNM_BROADCAST_MAC_ADDR(Addr)			((((Addr[0]) & 0xff) == 0xff))
#define WNM_SHOW_IP_HTONL(__IP)	\
	(htonl(__IP) >> 24) & 0xFF,		\
	(htonl(__IP) >> 16) & 0xFF,		\
	(htonl(__IP) >> 8) & 0xFF,		\
	(htonl(__IP) & 0xFF)

#ifdef CONFIG_STA_SUPPORT
static  WNM_DMS_DESCRIPTOR	DMS_Dscptor[WNMMAX_TCLAS];
static UINT32 gWNMDMS_ID;
static WNM_TCLAS gWNMCMD_TCLAS_Group[WNMMAX_TCLAS];
#endif /* CONFIG_STA_SUPPORT */


#ifdef CONFIG_STA_SUPPORT
#define WNMR_ARG_ATOI(__pArgv)				simple_strtol((PSTRING) __pArgv, 0, 10)
#define WNMR_ARG_ATOH(__Buf, __Hex)			AtoH((PSTRING) __Buf, __Hex, 1)
#endif /* CONFIG_STA_SUPPORT */



VOID InsertRequestTyppe(
	IN PRTMP_ADAPTER pAd,
	OUT PUCHAR pFrameBuf,
	OUT PULONG pFrameLen,
	IN UCHAR RequestTyppe)
{
	ULONG TempLen;
	MakeOutgoingFrame(pFrameBuf,	&TempLen,
					1,				&RequestTyppe,
					END_OF_ARGS);

	*pFrameLen = *pFrameLen + TempLen;

	return;
}


VOID WNM_Action(
	IN PRTMP_ADAPTER pAd, 
	IN MLME_QUEUE_ELEM *Elem) 
{
	UCHAR	Action = Elem->Msg[LENGTH_802_11+1];

	switch(Action)
	{


		case WNM_ACTION_BSS_TRANS_MANG_QUERY:
#ifdef CONFIG_AP_SUPPORT
			APPeerWNMBTMQueryAction(pAd,Elem);
#endif /* CONFIG_AP_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
			MlmeWNMBTMQueryAction(pAd,Elem);
#endif /* CONFIG_STA_SUPPORT */
				break;

		case WNM_ACTION_BSS_TRANS_MANG_REQUEST:

#ifdef CONFIG_AP_SUPPORT
			APPeerWNMBTMQueryAction(pAd,Elem);
#endif /* CONFIG_AP_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
			PeerWNMBTMReqAction(pAd,Elem);
#endif /* CONFIG_STA_SUPPORT */
				break;

		case WNM_ACTION_BSS_TRANS_MANG_RESPONSE:
#ifdef CONFIG_AP_SUPPORT
			APPeerWNMBTMRspAction(pAd,Elem);
#endif /* CONFIG_AP_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
#endif /* CONFIG_STA_SUPPORT */
				break;


		case WNM_ACTION_DMS_REQUEST:

#ifdef CONFIG_AP_SUPPORT
				APPeerWNMDMSReqAction(pAd,Elem);
#endif /* CONFIG_AP_SUPPORT */
				break;

		case WNM_ACTION_DMS_RESPONSE:
#ifdef CONFIG_STA_SUPPORT
				MlmeWNMDMSRspAction(pAd,Elem);
#endif /* CONFIG_STA_SUPPORT */
				break;


		default:
			DBGPRINT(RT_DEBUG_TRACE, ("%s: unknow action type (%d).\n",__FUNCTION__, Action));
			break;
	}

}

void WNM_ReadParametersFromFile(
	IN PRTMP_ADAPTER pAd,
	PSTRING tmpbuf,
	PSTRING buffer)
{
#ifdef CONFIG_AP_SUPPORT
/*	UCHAR WnmMaxIdlePeriod; */
	PSTRING					macptr;							
	INT loop;
#endif /* CONFIG_AP_SUPPORT */
#ifdef CONFIG_AP_SUPPORT
#if 0
	int i;
		if(RTMPGetKeyParameter("WnmMaxIdlePeriod", tmpbuf, 32, buffer, TRUE))
		{
			for (i = 0, macptr = rstrtok(tmpbuf,";"); macptr; macptr = rstrtok(NULL,";"), i++)
		    {
				int apidx = i;

				if (i >= pAd->ApCfg.BssidNum)
					break;

				WnmMaxIdlePeriod = simple_strtol(macptr, 0, 10);
				if((WnmMaxIdlePeriod > 0) && (WnmMaxIdlePeriod < 65535))
					pAd->ApCfg.MBSSID[apidx].WnmMaxIdlePeriod = WnmMaxIdlePeriod;
				else
					pAd->ApCfg.MBSSID[apidx].WnmMaxIdlePeriod = 0;
				
				DBGPRINT(RT_DEBUG_TRACE, (" I/F(ra%d) WnmMaxIdlePeriod=%d   (1~65535)\n", i, pAd->ApCfg.MBSSID[apidx].WnmMaxIdlePeriod));
			}
		}
#endif
#endif /* CONFIG_AP_SUPPORT */

	/* WNMBSSEnable */
	if (RTMPGetKeyParameter("WNMBSSEnable", tmpbuf, 255, buffer, TRUE))
	{
#ifdef CONFIG_AP_SUPPORT
		for (loop=0, macptr = rstrtok(tmpbuf,";");
				(macptr && loop < MAX_MBSSID_NUM(pAd));
					macptr = rstrtok(NULL,";"), loop++)
		{
			LONG Enable;
			Enable = simple_strtol(macptr, 0, 10);
			pAd->ApCfg.MBSSID[loop].WnmCfg.bDot11vWNM_BSSEnable =
				(Enable > 0) ? TRUE : FALSE;
			DBGPRINT(RT_DEBUG_TRACE, ("%s::(bDot11vWNM_BSSEnable[%d]=%d)\n",
				__FUNCTION__, loop,
				pAd->ApCfg.MBSSID[loop].WnmCfg.bDot11vWNM_BSSEnable));
		}
#endif /* CONFIG_AP_SUPPORT */
#ifdef CONFIG_STA_SUPPORT
			LONG Enable;
			Enable = simple_strtol(tmpbuf, 0, 10);
			pAd->StaCfg.WnmCfg.bDot11vWNM_BSSEnable =
				(Enable > 0) ? TRUE : FALSE;
			DBGPRINT(RT_DEBUG_TRACE, ("%s::(bDot11vWNM_BSSEnable=%d)\n",
				__FUNCTION__,
				pAd->StaCfg.WnmCfg.bDot11vWNM_BSSEnable));

#endif /* CONFIG_STA_SUPPORT */
	}
	else 
	{
#ifdef CONFIG_AP_SUPPORT
		for (loop = 0; loop < MAX_MBSSID_NUM(pAd); loop++)
			pAd->ApCfg.MBSSID[loop].WnmCfg.bDot11vWNM_BSSEnable = FALSE;
#endif /* CONFIG_AP_SUPPORT */
#ifdef CONFIG_STA_SUPPORT
		pAd->StaCfg.WnmCfg.bDot11vWNM_BSSEnable = FALSE;
#endif /* CONFIG_STA_SUPPORT */
	}



	/* WNMDMSEnable */
	if (RTMPGetKeyParameter("WNMDMSEnable", tmpbuf, 255, buffer, TRUE))
	{
#ifdef CONFIG_AP_SUPPORT
		for (loop=0, macptr = rstrtok(tmpbuf,";");
				(macptr && loop < MAX_MBSSID_NUM(pAd));
					macptr = rstrtok(NULL,";"), loop++)
		{
			LONG Enable;
			Enable = simple_strtol(macptr, 0, 10);
			pAd->ApCfg.MBSSID[loop].WnmCfg.bDot11vWNM_DMSEnable =
				(Enable > 0) ? TRUE : FALSE;
			DBGPRINT(RT_DEBUG_TRACE, ("%s::(bDot11vWNM_DMSEnable[%d]=%d)\n",
				__FUNCTION__, loop,
				pAd->ApCfg.MBSSID[loop].WnmCfg.bDot11vWNM_DMSEnable));
		}
#endif /* CONFIG_AP_SUPPORT */
#ifdef CONFIG_STA_SUPPORT
			LONG Enable;
			Enable = simple_strtol(tmpbuf, 0, 10);
			pAd->StaCfg.WnmCfg.bDot11vWNM_DMSEnable =
				(Enable > 0) ? TRUE : FALSE;
			DBGPRINT(RT_DEBUG_TRACE, ("%s::(bDot11vWNM_DMSEnable=%d)\n",
				__FUNCTION__,
				pAd->StaCfg.WnmCfg.bDot11vWNM_DMSEnable));

#endif /* CONFIG_STA_SUPPORT */
	}
	else 
	{
#ifdef CONFIG_AP_SUPPORT
		for (loop = 0; loop < MAX_MBSSID_NUM(pAd); loop++)
			pAd->ApCfg.MBSSID[loop].WnmCfg.bDot11vWNM_DMSEnable = FALSE;
#endif /* CONFIG_AP_SUPPORT */
#ifdef CONFIG_STA_SUPPORT
		pAd->StaCfg.WnmCfg.bDot11vWNM_DMSEnable = FALSE;
#endif /* CONFIG_STA_SUPPORT */
	}

	return;
}




#ifdef CONFIG_AP_SUPPORT
VOID TimetoSendDisassoc(
    IN PVOID SystemSpecific1, 
    IN PVOID FunctionContext, 
    IN PVOID SystemSpecific2, 
    IN PVOID SystemSpecific3);

BUILD_TIMER_FUNCTION(TimetoSendDisassoc);

VOID InsertKeydata(
	IN PRTMP_ADAPTER pAd,
	OUT PUCHAR pFrameBuf,
	OUT PULONG pFrameLen,
	IN UINT16 Keydata)
{
	ULONG TempLen;
	MakeOutgoingFrame(pFrameBuf,	&TempLen,
					2,				&Keydata,
					END_OF_ARGS);

	*pFrameLen = *pFrameLen + TempLen;

	return;
}

BOOLEAN DeleteDMSEntry(
    IN  PRTMP_ADAPTER	pAd,
    IN  MAC_TABLE_ENTRY *pEntry)
{

	PDMS_ENTRY pDMSEntry,pDMSEntrytmp;
	PDMSID_TABLE	pDMS_Table2,pDMS_Table2tmp;
	pDMSEntry = (PDMS_ENTRY) pAd->DMSEntryList.pHead;

		while(pDMSEntry != NULL)
		{
			 pDMSEntrytmp = pDMSEntry->pNext;
			if( pDMSEntry->pEntry == pEntry)
			{
				pDMS_Table2 = (PDMSID_TABLE) pDMSEntry->DMSIDList.pHead;
			
				while(pDMS_Table2 != NULL)
				{
					pDMS_Table2tmp = pDMS_Table2->pNext;
					os_free_mem(pAd, pDMS_Table2);
					delEntryList(&pDMSEntry->DMSIDList, (PLIST_ENTRY)pDMS_Table2);
 					pAd->ApCfg.MBSSID[pEntry->apidx].totalDMScount--; 
					if(getListSize(&pDMSEntry->DMSIDList) == 0)
					{
						os_free_mem(pAd, pDMSEntry);
						delEntryList(&pAd->DMSEntryList, (PLIST_ENTRY)pDMSEntry);					
						break;
					}
					pDMS_Table2 = pDMS_Table2tmp;
				}
			  }
			  pDMSEntry = pDMSEntrytmp;
		}	

	return TRUE;
}

VOID DMSTable_Release(
	IN PRTMP_ADAPTER pAd)
{
	PDMS_ENTRY pDMSEntry = NULL, pDMSEntrytmp;
	PDMSID_TABLE	pDMS_Table2 = NULL, pDMS_Table2tmp;
	pDMSEntry = (PDMS_ENTRY) pAd->DMSEntryList.pHead;
	while(pDMSEntry != NULL)
	{
		pDMS_Table2 = (PDMSID_TABLE) pDMSEntry->DMSIDList.pHead;				
		while(pDMS_Table2 != NULL)
		{
			pDMS_Table2tmp = pDMS_Table2->pNext;
			delEntryList(&pDMSEntry->DMSIDList, (PLIST_ENTRY)pDMS_Table2);
			os_free_mem(pAd, pDMS_Table2);
			pDMS_Table2 = pDMS_Table2tmp;
		}
		pDMSEntrytmp = pDMSEntry->pNext;
		delEntryList(&pAd->DMSEntryList, (PLIST_ENTRY)pDMSEntry);
		os_free_mem(pAd, pDMSEntry);
		pDMSEntry = pDMSEntrytmp;
	}	
}



NDIS_STATUS DMSPktInfoQuery(
	IN PRTMP_ADAPTER pAd,
	IN PUCHAR pSrcBufVA,
	IN PNDIS_PACKET pPacket,
	IN UCHAR apidx,
	IN UCHAR QueIdx,
	IN UINT8 UserPriority)

{
	PNDIS_PACKET pSkbClone = NULL;
	UINT32	DestIP;
	unsigned long IrqFlags;
	PDMS_ENTRY pDMSEntry;
	PDMSID_TABLE	pDMS_Table2;
	BOOLEAN FindDMS = FALSE;

	pDMSEntry = (PDMS_ENTRY) pAd->DMSEntryList.pHead;

	if (ISWNM_BROADCAST_MAC_ADDR(pSrcBufVA) || ISWNM_MULTICAST_MAC_ADDR(pSrcBufVA))
	{
		NdisMoveMemory(&DestIP, &pSrcBufVA[30], 4);/* point to Destination of Ip address of IP header. */

		while(pDMSEntry != NULL)
		{
			pDMSEntry->pEntry->Beclone = FALSE;
			pDMS_Table2 = (PDMSID_TABLE) pDMSEntry->DMSIDList.pHead;
			while(pDMS_Table2 != NULL)
			{
				if(pDMS_Table2->DMSID_DestIP == DestIP)
				{
					FindDMS = TRUE;
				}
				pDMS_Table2 = pDMS_Table2->pNext;
			}
			if(FindDMS ==  TRUE)
			{
				pSkbClone = skb_clone(RTPKT_TO_OSPKT(pPacket), MEM_ALLOC_FLAG);

				if(pSkbClone)
				{
					pDMSEntry->pEntry->Beclone = TRUE;
					RTMP_SET_PACKET_WCID(pSkbClone, (UCHAR)pDMSEntry->pEntry->Aid);
					/* Pkt type must set to PKTSRC_NDIS. */
					/* It cause of the deason that APHardTransmit() */
					/* doesn't handle PKTSRC_DRIVER pkt type in version 1.3.0.0. */
					RTMP_SET_PACKET_SOURCE(pSkbClone, PKTSRC_NDIS);
					
				/* insert the pkt to TxSwQueue. */
					if (pAd->TxSwQueue[QueIdx].Number >= pAd->TxSwQMaxLen)
					{
#ifdef BLOCK_NET_IF
						StopNetIfQueue(pAd, QueIdx, pSkbClone);
#endif /* BLOCK_NET_IF */
						RELEASE_NDIS_PACKET(pAd, pSkbClone, NDIS_STATUS_FAILURE);
						return NDIS_STATUS_FAILURE;
					}
					else
					{
						RTMP_IRQ_LOCK(&pAd->irq_lock, IrqFlags);
						InsertTailQueueAc(pAd, pDMSEntry->pEntry, &pAd->TxSwQueue[QueIdx], PACKET_TO_QUEUE_ENTRY(pSkbClone));
						RTMP_IRQ_UNLOCK(&pAd->irq_lock, IrqFlags);
						return NDIS_STATUS_SUCCESS;
					}
				}

		}


			pDMSEntry = pDMSEntry->pNext;
		}	
		
		}
			
	return NDIS_STATUS_SUCCESS;
}

BOOLEAN PeerWNMDMSReqSanity( 
    IN PRTMP_ADAPTER pAd, 
    IN VOID *Msg, 
    IN ULONG MsgLen,
    OUT PUCHAR pDA,
    OUT PUCHAR DialogToken, 
    OUT PUCHAR RequestTyppe,
    OUT PUCHAR DMSID,
    OUT PUINT32 IPdest)	
{
    CHAR            *Ptr;
    PFRAME_802_11	Fr = (PFRAME_802_11)Msg;

    /* get DA from payload and advance the pointer */
    NdisMoveMemory(pDA, (PCHAR)Fr->Hdr.Addr2, MAC_ADDR_LEN);

    Ptr = (PCHAR)Fr->Octet;
	/* offset to destination MAC address (Category and Action field) */
    Ptr += 2;

    /* get DialogToken */
    NdisMoveMemory(DialogToken, Ptr, 1);
    Ptr += 1;

/* element && length */
	Ptr +=2;

    /* get RequestTyppe */
    NdisMoveMemory(RequestTyppe, Ptr, 1);

    Ptr += 1;

    /* get DMSID */
    NdisMoveMemory(DMSID, Ptr, 1);
    Ptr +=1;

    Ptr +=1; /*DMS length*/	
    Ptr +=2; /*TCLAS elelemy ID length*/	
    Ptr +=8; 
	/*   UCHAR  UserPriority  
	       UCHAR   ClassifierType 
	       UCHAR  ClassifierMask           
	      UCHAR   Version;
            UINT32  IpSource;
            UINT32  IpDest;
            UINT16  PortSource;
            UINT16  PortDest;
            UCHAR   DSCP;
            UCHAR   Protocol;*/

     NdisMoveMemory(IPdest, Ptr, 4);
    return TRUE;
}


/*
========================================================================
Routine Description: handlerDMS Request and  Send DMS Resopns action

Arguments:

Return Value:

Note:

========================================================================
*/

VOID APPeerWNMDMSReqAction(
    IN PRTMP_ADAPTER pAd, 
    IN MLME_QUEUE_ELEM *Elem) 
{
	UCHAR				DA[MAC_ADDR_LEN];
	PUCHAR          pOutBuffer = NULL;
	NDIS_STATUS     NStatus;
	ULONG           FrameLen;
	UCHAR DialogToke;
	UCHAR DMSID;
	UCHAR RequestTyppe;
	UINT32 IPdest;
 	PMAC_TABLE_ENTRY	 pSAEntry = NULL;
	WNM_DMS_RESPONSE_FRAME	DMSRspFrame;
	WNM_DMS_RESPONSE_ELEMENT  DMSRspElement;
	UCHAR						DMSState = 0;

	BOOLEAN	newDMSEntry = TRUE;
	BOOLEAN	newDMSID = TRUE;

	PDMS_ENTRY pDMSEntry = NULL;
	PDMSID_TABLE	pDMS_Table2 = NULL;
	pDMSEntry = (PDMS_ENTRY) pAd->DMSEntryList.pHead;

	if (!PeerWNMDMSReqSanity(pAd, Elem->Msg, Elem->MsgLen, DA, &DialogToke, 
		&RequestTyppe,&DMSID ,&IPdest))
	{
        	return;
	}
	printk("DialogToke %d RequestTyppe %d DMSID %d  IPdest %d %d %d %d  \n \n"
		,DialogToke,RequestTyppe, DMSID,WNM_SHOW_IP_HTONL(IPdest));


	pSAEntry = MacTableLookup(pAd, DA);
	

	if(!pSAEntry)
		return;
	if(pSAEntry->bDMSSTASupport != TRUE)
	{
		printk("pSAEntry->bDMSSTASupport not support or ap not enable WNMDMS \n");
		return;
	}

	if(RequestTyppe == 0)/*add DMSID TCLAS*/
	{

	

		/* total count 15 */
		if (pAd->ApCfg.MBSSID[pSAEntry->apidx].DMSEntrycount >= 10)
		{
			printk("  total DMSID  count is 10 , reject   \n");
			DMSState = WNM_STATUS_OVERRIDDEN_DUE_TO_LACK_RESOURCES;
			goto done;
		}
		if(getListSize(&pAd->DMSEntryList) == 0)
		{
				newDMSEntry = TRUE;
				printk("  newDMSEntry = TRUE   \n");
		}
		else
		{
				
			while(pDMSEntry != NULL)
			{
				if( pDMSEntry->pEntry->Aid ==  pSAEntry->Aid) 
				{	
					newDMSEntry = FALSE;
						break;
				}
				pDMSEntry = pDMSEntry->pNext;			
			}
		}

		if(newDMSEntry)
		{	
				
			while(pDMSEntry != NULL)
			{
				pDMSEntry = pDMSEntry->pNext;			
			}
		
/*			pDMSEntry = kmalloc(sizeof(DMS_ENTRY), GFP_ATOMIC); */
			os_alloc_mem(NULL, (UCHAR **)&pDMSEntry, sizeof(DMS_ENTRY));
			initList(&pDMSEntry->DMSIDList);
			pDMSEntry->pEntry = pSAEntry;
			pDMS_Table2 = (PDMSID_TABLE) pDMSEntry->DMSIDList.pHead;

/*			pDMS_Table2 = kmalloc(sizeof(DMSID_TABLE), GFP_ATOMIC); */
			os_alloc_mem(NULL, (UCHAR **)&pDMS_Table2, sizeof(DMSID_TABLE));
			pDMS_Table2->DMSIDs = DMSID;				
			pDMS_Table2->DMSID_DestIP = IPdest;
			insertTailList(&pDMSEntry->DMSIDList  , (PLIST_ENTRY)pDMS_Table2);
			insertTailList(&pAd->DMSEntryList, (PLIST_ENTRY)pDMSEntry);
			pAd->ApCfg.MBSSID[pSAEntry->apidx].totalDMScount++; 
			DMSState = WNM_STATUS_ACCEPT;
		
			goto done;
		}
		else /* this is not new entry , but i maby new DMSID*/
		{
	
		      pDMS_Table2 = (PDMSID_TABLE) pDMSEntry->DMSIDList.pHead;
			
			if(getListSize(&pDMSEntry->DMSIDList) == 0)
			{
				newDMSID = TRUE;	
			}
			else
			{
				while(pDMS_Table2 !=NULL)
				{
					if( pDMS_Table2->DMSIDs ==  DMSID) 
					{
						newDMSID = FALSE;
						break;
					}
					pDMS_Table2 = pDMS_Table2->pNext;
				}
			}
				
			if(newDMSID)
			{			
/*				pDMS_Table2 = kmalloc(sizeof(DMSID_TABLE), GFP_ATOMIC); */
				os_alloc_mem(NULL, (UCHAR **)&pDMS_Table2, sizeof(DMSID_TABLE));
				pDMS_Table2->DMSIDs = DMSID;				
				pDMS_Table2->DMSID_DestIP = IPdest;
				insertTailList(&pDMSEntry->DMSIDList  , (PLIST_ENTRY)pDMS_Table2);
				pAd->ApCfg.MBSSID[pSAEntry->apidx].totalDMScount++; 
				DMSState = WNM_STATUS_ACCEPT;
			}
			else
			{ /*this entry and this dmsid is exist*/
				printk("this entry and this dmsid is exist");
				DMSState = WNM_STATUS_DENIED_FROMAT_ERROR;
				goto done;				
			}
		}
	
	}
	else if(RequestTyppe == 1)/*remove DMSID TCLAS*/
	{
		if(getListSize(&pAd->DMSEntryList) == 0)
		{
			printk("no any entry \n");
			DMSState = WNM_STATUS_DENIED_FROMAT_ERROR;
			goto done;	
		}
		
		while(pDMSEntry != NULL)
		{
			/*find entry*/
			if(getListSize(&pDMSEntry->DMSIDList) == 0)
			{
				printk("no any DMSID \n");
				DMSState = WNM_STATUS_DENIED_FROMAT_ERROR;
				goto done;	
			}
			else
			{
				pDMS_Table2 = (PDMSID_TABLE) pDMSEntry->DMSIDList.pHead;			
				while(pDMS_Table2 != NULL)
				{
					if( pDMS_Table2->DMSIDs == DMSID) 
					{
						printk("free DMSID  \n");
						os_free_mem(pAd, pDMS_Table2);
						delEntryList(&pDMSEntry->DMSIDList, (PLIST_ENTRY)pDMS_Table2);
						DMSState = WNM_STATUS_ACCEPT;
						pAd->ApCfg.MBSSID[pSAEntry->apidx].totalDMScount--; 
						if(getListSize(&pDMSEntry->DMSIDList) == 0)
						{
							os_free_mem(pAd, pDMSEntry);
							delEntryList(&pAd->DMSEntryList, (PLIST_ENTRY)pDMSEntry);					
						}

						goto done;
					}
					pDMS_Table2 = pDMS_Table2->pNext;
				}
	

			}
				pDMSEntry = pDMSEntry->pNext;
		}

	}
	
done:
	NStatus = MlmeAllocateMemory(pAd, &pOutBuffer);	 /*Get an unused nonpaged memory */
	if (NStatus != NDIS_STATUS_SUCCESS)
	{
		DBGPRINT(RT_DEBUG_ERROR,(" MlmeWNMDMSREQAction() allocate memory failed \n"));
		return;
	}


	DMSRspFrame.Category = WNM_CATEGORY;
	DMSRspFrame.Action = WNM_ACTION_DMS_RESPONSE;
	DMSRspFrame.DialogToken = DialogToke;
	DMSRspElement.ElementId = WNM_INF_ELE_DMS_RESPONSE;
	DMSRspElement.Length =2 ;
	ActHeaderInit(pAd, &DMSRspFrame.Hdr, DA, pAd->ApCfg.MBSSID[pSAEntry->apidx].Bssid, pAd->ApCfg.MBSSID[pSAEntry->apidx].Bssid);

	MakeOutgoingFrame(pOutBuffer,               &FrameLen,
					  sizeof(WNM_DMS_RESPONSE_FRAME),      &DMSRspFrame,
					   sizeof(WNM_DMS_RESPONSE_ELEMENT),	 &DMSRspElement,				
					  1								,	 &DMSID,
					  1								,	 &DMSState,
					  END_OF_ARGS);
	MiniportMMRequest(pAd, QID_AC_BE, pOutBuffer, FrameLen);
	MlmeFreeMemory(pAd, pOutBuffer);
	DBGPRINT(RT_DEBUG_TRACE,("WNM- APPeerWNMDMSReqAction()  \n"));

 
}



BOOLEAN PeerWNMBTMQuerySanity(
    IN PRTMP_ADAPTER pAd, 
    IN VOID *Msg, 
    IN ULONG MsgLen,
    OUT PUCHAR pDA,
    OUT PUCHAR DialogToken, 
    OUT PUCHAR QueryReason,
    OUT PUCHAR IsAPSend)	
{
	CHAR            *Ptr;
    	PFRAME_802_11	Fr = (PFRAME_802_11)Msg;

  
    /* get DA from payload and advance the pointer */
    NdisMoveMemory(pDA, (PCHAR)Fr->Hdr.Addr2, MAC_ADDR_LEN);

    Ptr = (PCHAR)Fr->Octet;
	/* offset to destination MAC address (Category and Action field) */
    Ptr += 2;

    /* get DialogToken */
    NdisMoveMemory(DialogToken, Ptr, 1);
    Ptr += 1;

    /* get QueryReason */
    NdisMoveMemory(QueryReason, Ptr, 1);

   if	(*QueryReason > 100)
   {
		*QueryReason = *QueryReason - 100;
		*IsAPSend = TRUE;
   }
   else
   		*IsAPSend = FALSE;	
   
    return TRUE;
}


BOOLEAN PeerWNMBTMRSPSanity(
    IN PRTMP_ADAPTER pAd, 
    IN VOID *Msg, 
    IN ULONG MsgLen,
    OUT PUCHAR pDA,
    OUT PUCHAR DialogToken, 
    OUT PUCHAR Statuscode,
    OUT PUCHAR BSSTerminationDelay)	
{
	CHAR            *Ptr;
    	PFRAME_802_11	Fr = (PFRAME_802_11)Msg;

    /* get DA from payload and advance the pointer */
    NdisMoveMemory(pDA, (PCHAR)Fr->Hdr.Addr2, MAC_ADDR_LEN);

    Ptr = (PCHAR)Fr->Octet;
	/* offset to destination MAC address (Category and Action field) */
    Ptr += 2;
  
    /* get DialogToken */
    NdisMoveMemory(DialogToken, Ptr, 1);
    Ptr += 1;

    /* get Statuscode */
    NdisMoveMemory(Statuscode, Ptr, 1);

    Ptr += 1;
   /* get BSSTerminationDelay */
    NdisMoveMemory(BSSTerminationDelay, Ptr, 1);
   
    return TRUE;
}


/*
========================================================================
Routine Description: Handler  BSS Transition Manganment QUERY
				  and send   BSS Transition Manganment REQUEST	

Arguments:

Return Value:

Note:

========================================================================
*/
VOID APPeerWNMBTMQueryAction(
    IN PRTMP_ADAPTER pAd, 
    IN MLME_QUEUE_ELEM *Elem) 
{

	UCHAR				DA[MAC_ADDR_LEN];
	WNM_BSS_TRANSITION_REQUEST_FRAME BssTrREQFrame;
	PUCHAR          pOutBuffer = NULL;
	NDIS_STATUS     NStatus;
	ULONG           FrameLen;
	UCHAR   QueryReason;
	UCHAR 	DialogToken;
	PMAC_TABLE_ENTRY	 pSAEntry;
	UCHAR	IsAPSend;
	/* frame sanity check */


	if (!PeerWNMBTMQuerySanity(pAd, Elem->Msg, Elem->MsgLen, DA,
							&DialogToken, &QueryReason, &IsAPSend))
	{
        return;
	}

	pSAEntry = MacTableLookup(pAd, DA);

	if(!pSAEntry){
		return;
	}

	if(pSAEntry->bBSSMantSTASupport != TRUE)
	{
		DBGPRINT(RT_DEBUG_ERROR,(" STA or AP do not support BSS M \n"));
		return;
	}

	NStatus = MlmeAllocateMemory(pAd, &pOutBuffer);	 /*Get an unused nonpaged memory */
	if (NStatus != NDIS_STATUS_SUCCESS)
	{
		DBGPRINT(RT_DEBUG_ERROR,(" APPeerWNMBTMQueryAction() allocate memory failed \n"));
		return;
	}



	ActHeaderInit(pAd, &BssTrREQFrame.Hdr, DA, pAd->ApCfg.MBSSID[pSAEntry->apidx].Bssid, pAd->ApCfg.MBSSID[pSAEntry->apidx].Bssid);


	BssTrREQFrame.Category = WNM_CATEGORY;
	BssTrREQFrame.Action = WNM_ACTION_BSS_TRANS_MANG_REQUEST;	

	if(IsAPSend) 
		BssTrREQFrame.DialogToken = RandomByte(pAd); 
	else 
		BssTrREQFrame.DialogToken = DialogToken;	
 
	pSAEntry->BTMQueryDialogToken = BssTrREQFrame.DialogToken;

      switch (QueryReason)
      	{
		case 	UNSPECIFIED:
		case 	EXCESSIVE_FRAME_LOSS_RATES_AND_POOR_CONDITIONS:
		case 	EXCESSIVE_DELAY_FOR_CURRENT_TRAFFIC_STREAMS:
		case	INSUFFICIENT_QOS_CAPCAITY_FOR_CURRENT_TRAFFIC_STREAMS:
		case	FIRST_ASSOCIATION_RO_ESS:

				BssTrREQFrame.RequestMode.PreferredCandidateList = 0;
				BssTrREQFrame.RequestMode.Abridged = 0;
				BssTrREQFrame.RequestMode.DisassociationImminent = 0;
				BssTrREQFrame.RequestMode.BSSTerminationIncluded = 0;
				BssTrREQFrame.DisassociationTimer = 0;
				BssTrREQFrame.ValidityInterval = 0;
				break;
		case	LOAD_BALANCING	:

				BssTrREQFrame.RequestMode.PreferredCandidateList = 0;
				BssTrREQFrame.RequestMode.Abridged = 0;
				BssTrREQFrame.RequestMode.DisassociationImminent = 0;
				BssTrREQFrame.RequestMode.BSSTerminationIncluded = 1;
				BssTrREQFrame.DisassociationTimer = 0;
				BssTrREQFrame.ValidityInterval = 0;
				pSAEntry->BSSTerminationIncluded = TRUE;
				break;
		case	BETTER_AP_FOUND:

				BssTrREQFrame.RequestMode.PreferredCandidateList = 0;
				BssTrREQFrame.RequestMode.Abridged = 0;
				BssTrREQFrame.RequestMode.DisassociationImminent = 1;
				BssTrREQFrame.RequestMode.BSSTerminationIncluded = 0;
				BssTrREQFrame.DisassociationTimer = 0;
				BssTrREQFrame.ValidityInterval = 0;
				pSAEntry->DisassociationImminent = TRUE;

				break;				
		case	DEAUTHENTICATED_OR_DISACCOCIATES_FROM_THE_PERVIOUS_AP:	
		case 	AP_FAILED_IEEE_8021X_EAP_AUTHENTICATION	:
		case 	AP_FAILED_4WAY_HANDSHAKE:
		case 	REVEIVED_TOO_MANY_REPLAY_COUNTER_FAILURES:
		case 	RECEIVED_TOO_MANY_DATA_MIC_FAILURES:
		case 	EXCEEDED_MAXIMUM_NUMBER_OF_RETRANSMISSIONS:
		case 	RECEIVED_TOO_MANY_BROADCAST_DISASSOCIATIONS:
		case 	RECEIVED_TOO_MANY_BROCADCAST_DEAUTHEHTICATIONS:
		case 	PREVIOUS_TRANSITION_FAILD:
		case 	LOW_RSSI:

				BssTrREQFrame.RequestMode.PreferredCandidateList = 0;
				BssTrREQFrame.RequestMode.Abridged = 0;
				BssTrREQFrame.RequestMode.DisassociationImminent = 0;
				BssTrREQFrame.RequestMode.BSSTerminationIncluded = 0;
				BssTrREQFrame.DisassociationTimer = 0;
				BssTrREQFrame.ValidityInterval = 0;

			break;
		
		default:
			DBGPRINT(RT_DEBUG_ERROR,("APPeerWNMBTMQueryAction unknow QueryReason \n"));

				break;
			
      	}

	MakeOutgoingFrame(pOutBuffer,               &FrameLen,
					  sizeof(WNM_BSS_TRANSITION_QUERY_FRAME),      &BssTrREQFrame,
					  END_OF_ARGS);
	MiniportMMRequest(pAd, QID_AC_BE, pOutBuffer, FrameLen);
	MlmeFreeMemory(pAd, pOutBuffer);
	DBGPRINT(RT_DEBUG_TRACE,("WNM- APPeerWNMBTMQueryAction  \n"));

}




/*
========================================================================
Routine Description: Handler  BSS Transition Manganment RESPONSE
			

Arguments:

Return Value:

Note:

========================================================================
*/


VOID APPeerWNMBTMRspAction(
    IN PRTMP_ADAPTER pAd, 
    IN MLME_QUEUE_ELEM *Elem) 
{

	UCHAR				DA[MAC_ADDR_LEN];
	UCHAR 	DialogToken;
	UCHAR	Statuscode;
	UCHAR	BSSTerminationDelay;
	PMAC_TABLE_ENTRY	pSAEntry;

	if (!PeerWNMBTMRSPSanity(pAd, Elem->Msg, Elem->MsgLen, DA,
							&DialogToken, &Statuscode, &BSSTerminationDelay))
	{
        return;
	}

	pSAEntry = MacTableLookup(pAd, DA);

	if(!pSAEntry){
		return;
	}

	if(pSAEntry->bBSSMantSTASupport != TRUE)
	{
		DBGPRINT(RT_DEBUG_ERROR,("STA do not support BSS M T or do not enable WNMBSSEnable  \n"));
		return;
	}


	if(!(pSAEntry->BTMQueryDialogToken == DialogToken))
	{
		DBGPRINT(RT_DEBUG_ERROR,("APPeerWNMBTMRspAction  DialogToken error\n"));
		return;
	}

	if(pSAEntry->DisassociationImminent == TRUE )
	{
		PUCHAR      pOutBuffer = NULL;
		NDIS_STATUS NStatus;
		ULONG       FrameLen = 0;
		HEADER_802_11 DisassocHdr;
		USHORT      Reason;
		pSAEntry->DisassociationImminent = FALSE;
		/*  send out a DISASSOC request frame */
		NStatus = MlmeAllocateMemory(pAd, &pOutBuffer);
		Reason = REASON_DISASSOC_DUE_TO_BSS_TRANSITION_MANAGEMENT;
		DBGPRINT(RT_DEBUG_WARN, ("Send DISASSOC - Reason = %d frame  TO %x %x %x %x %x %x \n",Reason,pSAEntry->Addr[0],
								pSAEntry->Addr[1],pSAEntry->Addr[2],pSAEntry->Addr[3],pSAEntry->Addr[4],pSAEntry->Addr[5]));
		MgtMacHeaderInit(pAd, &DisassocHdr, SUBTYPE_DISASSOC, 0, pSAEntry->Addr, 
#ifdef P2P_SUPPORT
							pAd->ApCfg.MBSSID[pSAEntry->apidx].Bssid,
#endif /* P2P_SUPPORT */
							pAd->ApCfg.MBSSID[pSAEntry->apidx].Bssid);				
	    	MakeOutgoingFrame(pOutBuffer,            &FrameLen, 
		   	  	                sizeof(HEADER_802_11), &DisassocHdr, 
		   	      		          2,                     &Reason, 
		    	             	    END_OF_ARGS);				
		 MiniportMMRequest(pAd, 0, pOutBuffer, FrameLen);
		 MlmeFreeMemory(pAd, pOutBuffer);
		 MacTableDeleteEntry(pAd, pSAEntry->Aid, pSAEntry->Addr);

	}

	if (pSAEntry->BSSTerminationIncluded == TRUE)
	{
		pSAEntry->BSSTerminationIncluded = FALSE;
		RTMPInitTimer(pAd, &pSAEntry->DisassocTimer, GET_TIMER_FUNCTION(TimetoSendDisassoc), pSAEntry, FALSE);
		RTMPSetTimer(&pSAEntry->DisassocTimer, 3000);

	}

}


VOID TimetoSendDisassoc(
    IN PVOID SystemSpecific1, 
    IN PVOID FunctionContext, 
    IN PVOID SystemSpecific2, 
    IN PVOID SystemSpecific3) 
{
	MAC_TABLE_ENTRY *pEntry = (MAC_TABLE_ENTRY *)FunctionContext;
	PRTMP_ADAPTER   pAd;
	PUCHAR      pOutBuffer = NULL;
	NDIS_STATUS NStatus;
	ULONG       FrameLen = 0;
	HEADER_802_11 DisassocHdr;
	USHORT      Reason;
	
	if (pEntry == NULL)
		return;

	pAd = pEntry->pAd;

	/*  send out a DISASSOC request frame */
	NStatus = MlmeAllocateMemory(pAd, &pOutBuffer);
	Reason = REASON_DISASSOC_DUE_TO_BSS_TRANSITION_MANAGEMENT;
	DBGPRINT(RT_DEBUG_WARN, ("Send DISASSOC - Reason = %d frame  TO %x %x %x %x %x %x \n",Reason,pEntry->Addr[0],
							pEntry->Addr[1],pEntry->Addr[2],pEntry->Addr[3],pEntry->Addr[4],pEntry->Addr[5]));
	MgtMacHeaderInit(pAd, &DisassocHdr, SUBTYPE_DISASSOC, 0, pEntry->Addr, 
#ifdef P2P_SUPPORT
						pAd->ApCfg.MBSSID[pEntry->apidx].Bssid,
#endif /* P2P_SUPPORT */
						pAd->ApCfg.MBSSID[pEntry->apidx].Bssid);				
	MakeOutgoingFrame(pOutBuffer,            &FrameLen, 
		  	                sizeof(HEADER_802_11), &DisassocHdr, 
		   	      	          2,                     &Reason, 
		    	            	    END_OF_ARGS);				
	 MiniportMMRequest(pAd, 0, pOutBuffer, FrameLen);
	 MlmeFreeMemory(pAd, pOutBuffer);

	MacTableDeleteEntry(pAd, pEntry->Aid, pEntry->Addr);

}


INT	Set_APWNMDMSShow_Proc(
	IN	PRTMP_ADAPTER	pAd, 
	IN	PSTRING			arg)
{
	INT   success = FALSE;
	UCHAR   Show;
	
	PDMS_ENTRY pDMSEntry = NULL;
	PDMSID_TABLE	pDMS_Table2 = NULL;

	pDMSEntry = (PDMS_ENTRY) pAd->DMSEntryList.pHead;
	Show = (USHORT) simple_strtol(arg, 0, 10);

	if(Show == 1)
	{		
		success = TRUE;
	}
	else
	{
		DBGPRINT(RT_DEBUG_ERROR, ("Set_MlmeWNMDMSShow_Proc=1  =>  you type %d    \n",Show));
		success = FALSE;
	}

	
	if(success == TRUE)
	{
		while(pDMSEntry != NULL)
		{		
				printk(" pSAEntry->Addr %02x:%02x:%02x:%02x:%02x:%02x \n",
				pDMSEntry->pEntry->Addr[0],pDMSEntry->pEntry->Addr[1],
				pDMSEntry->pEntry->Addr[2],pDMSEntry->pEntry->Addr[3],
				pDMSEntry->pEntry->Addr[4],pDMSEntry->pEntry->Addr[5]);
				pDMS_Table2 = (PDMSID_TABLE) pDMSEntry->DMSIDList.pHead;
				while(pDMS_Table2 != NULL)
				{
					printk("pSAEntry->DMSID %d pSAEntry->DMSID_DestIP %d %d %d %d \n",
					pDMS_Table2->DMSIDs,
					WNM_SHOW_IP_HTONL(pDMS_Table2->DMSID_DestIP));				
					pDMS_Table2 = pDMS_Table2->pNext;
				}
				pDMSEntry = pDMSEntry->pNext;
			}	
			
		}
	return success;

}


INT	Set_WNMTransMantREQ_Proc(
	IN	PRTMP_ADAPTER	pAd, 
	IN	PSTRING			arg)
{

	WNM_BSS_TRANSITION_QUERY_FRAME	BssTrQFrame;
    	UCHAR	mac[MAC_ADDR_LEN];
	UCHAR	QueryReason;
	PSTRING token;
	STRING sepValue[] = ":", DASH = '-';
	INT i;

  
    if(strlen(arg) < 17)  /*Mac address acceptable format 01:02:03:04:05:06 length 17 plus the "-" and QueryReason value in decimal format. */
    	{
		printk(" < 17 ");
		return FALSE;
    	}
	token = strchr(arg, DASH);
	if ((token != NULL) && (strlen(token)>1))
	{
		QueryReason = (USHORT) simple_strtol((token+1), 0, 10);


		*token = '\0';
		for (i = 0, token = rstrtok(arg, &sepValue[0]); token; token = rstrtok(NULL, &sepValue[0]), i++)
		{
			if((strlen(token) != 2) || (!isxdigit(*token)) || (!isxdigit(*(token+1))))
				return FALSE;
			AtoH(token, (&mac[i]), 1);
		}
		if(i != 6)
			return FALSE;

	    DBGPRINT(RT_DEBUG_OFF, ("\n%02x:%02x:%02x:%02x:%02x:%02x-%d", mac[0], mac[1],
	           mac[2], mac[3], mac[4], mac[5], QueryReason));


		for(i=0;  i < MAC_ADDR_LEN; i++)
			BssTrQFrame.Hdr.Addr2[i] = mac[i];

		BssTrQFrame.Category = WNM_CATEGORY;
		BssTrQFrame.Action = WNM_ACTION_BSS_TRANS_MANG_QUERY;	
		BssTrQFrame.BSSTransitionQueryReason = QueryReason + 100;
		MlmeEnqueue(pAd, ACTION_STATE_MACHINE, WNM_CATEGORY_BSS_TRANSITION, sizeof(BssTrQFrame), &BssTrQFrame,0);
	 
		return TRUE;
	}

	return FALSE;

	

}



/* 
    ==========================================================================
    Description:
        Set Wnm MaxIdle Period
    Return:
        TRUE if all parameters are OK, FALSE otherwise
    ==========================================================================
*/
#if 0
INT	Set_WnmMaxIdlePeriod_Proc(
	IN	PRTMP_ADAPTER	pAd, 
	IN	PSTRING			arg)
{
	USHORT WnmMaxIdlePeriod;
	INT   success = FALSE;
	POS_COOKIE pObj = (POS_COOKIE) pAd->OS_Cookie;
	UCHAR		apidx = pObj->ioctl_if;

	WnmMaxIdlePeriod = (USHORT) simple_strtol(arg, 0, 10);
	if((WnmMaxIdlePeriod > 0) && (WnmMaxIdlePeriod < 65535))
	{		
		pAd->ApCfg.MBSSID[apidx].WnmMaxIdlePeriod = WnmMaxIdlePeriod;
		success = TRUE;		
	}
	else
		success = FALSE;

	DBGPRINT(RT_DEBUG_TRACE, ("Set_WnmMaxIdlePeriod_Proc::(WnmMaxIdlePeriod=%d)\n", pAd->ApCfg.MBSSID[apidx].WnmMaxIdlePeriod));

	return success;
}
#endif


#endif /* CONFIG_AP_SUPPORT */


/* STA STA STA STA STA STA STA STA STA STA STA STA STA STA STA STA STA STA STA*/




#ifdef CONFIG_STA_SUPPORT
void WNM_Init(IN PRTMP_ADAPTER pAd)
{
	gWNMDMS_ID = 0 ;

}
void IS_WNM_DMS(
	IN PRTMP_ADAPTER pAd, 
	IN PNDIS_PACKET pRxPacket, 
	IN PHEADER_802_11 pHeader)
{
	if (ISWNM_BROADCAST_MAC_ADDR(pHeader->Addr1) 
		|| ISWNM_MULTICAST_MAC_ADDR(pHeader->Addr1))
	{
	/*	printk("set b or m \n"); */
		RTMP_SET_WNM_DMS(pRxPacket, 1);
	}

}
BOOLEAN RxDMSHandle(
	IN PRTMP_ADAPTER	pAd,
	IN PNDIS_PACKET		pPkt)
{
	unsigned char *pt;
	int i;
	UINT32	IP;
	pt = GET_OS_PKT_DATAPTR(pPkt);   
	
   if(pAd->StaCfg.bDMSSetUp == TRUE)
   {
		/*get dest ip address*/
		NdisMoveMemory(&IP, &pt[30], 4);
  
		for(i=0; i < gWNMDMS_ID; i++)
		{
			if( (gWNMCMD_TCLAS_Group[i].Clasifier.IPv4.IpDest == IP) &&  (RTMP_GET_WNM_DMS(pPkt) ))
                   {
				RELEASE_NDIS_PACKET(pAd, pPkt, NDIS_STATUS_FAILURE);
				return (NDIS_STATUS_FAILURE);
			 }
		}
   }

	return (NDIS_STATUS_SUCCESS);
}


BOOLEAN PeerWNMDMSRSPSanity(
    IN PRTMP_ADAPTER pAd, 
    IN VOID *Msg, 
    IN ULONG MsgLen,
    OUT PUCHAR DialogToken, 
    OUT PUCHAR DMSID,
    OUT PUCHAR DMSState)	
{
    CHAR            *Ptr;
    PFRAME_802_11	Fr = (PFRAME_802_11)Msg;

    Ptr = (PCHAR)Fr->Octet;
	/* offset to destination MAC address (Category and Action field) */
    Ptr += 2;
      /* get DialogToken */
    NdisMoveMemory(DialogToken, Ptr, 1);
    Ptr += 1;

/* element ID Length */
    Ptr +=2;	

    /* get Statuscode */
    NdisMoveMemory(DMSID, Ptr, 1);
    Ptr += 1;
   /* get BSSTerminationDelay */
    NdisMoveMemory(DMSState, Ptr, 1);
   
    return TRUE;
}



/*
========================================================================
Routine Description: handler DMS Response 

Arguments:

Return Value:

Note:

========================================================================
*/

VOID MlmeWNMDMSRspAction(
    IN PRTMP_ADAPTER pAd, 
    IN MLME_QUEUE_ELEM *Elem) 
{

	UCHAR DialogToke;
	UCHAR DMSID;
	UCHAR						DMSStatue = 0;
 	UINT8 gWNMDMScount;
	BOOLEAN remove = FALSE;

	if (!PeerWNMDMSRSPSanity(pAd, Elem->Msg, Elem->MsgLen
							, &DialogToke, &DMSID, &DMSStatue))
	{
        return;
	}

	printk(" DialogToke %d   DMSID %d   DMSStatue %d  \n",DialogToke,DMSID,DMSStatue);

	if(DialogToke != pAd->StaCfg.DMSREQDialogToken)
	{
		DBGPRINT(RT_DEBUG_ERROR,("MlmeWNMDMSRspAction  DialogToken error\n"));
		return;
	}

	for(gWNMDMScount=0; gWNMDMScount < gWNMDMS_ID; gWNMDMScount++)
	{			
		if(DMS_Dscptor[gWNMDMScount].DMSID == DMSID)
		{
				remove = TRUE;
				break;
		}
	}

	if(DMSStatue == WNM_STATUS_ACCEPT)
	{
		if(remove)
		{
			for(gWNMDMScount; gWNMDMScount < gWNMDMS_ID; gWNMDMScount++)
			{			
				DMS_Dscptor[gWNMDMScount].DMSID = DMS_Dscptor[gWNMDMScount+1].DMSID;				
				gWNMCMD_TCLAS_Group[gWNMDMScount].Clasifier.IPv4.IpDest = gWNMCMD_TCLAS_Group[gWNMDMScount+1].Clasifier.IPv4.IpDest;

			}
			gWNMDMS_ID--;
		}
		else
			gWNMDMS_ID++;

	}
	else if(DMSStatue == WNM_STATUS_ACCEPT_TIM)
	{
		if(remove)
{
			for(gWNMDMScount; gWNMDMScount < gWNMDMS_ID; gWNMDMScount++)
			{			
				DMS_Dscptor[gWNMDMScount].DMSID = DMS_Dscptor[gWNMDMScount+1].DMSID;				
				gWNMCMD_TCLAS_Group[gWNMDMScount].Clasifier.IPv4.IpDest = gWNMCMD_TCLAS_Group[gWNMDMScount+1].Clasifier.IPv4.IpDest;	
			}
			gWNMDMS_ID--;
		}		
                else
			gWNMDMS_ID++;
	}
	else if(DMSStatue == WNM_STATUS_DENIED_FROMAT_ERROR)
	{
		/*not success so delete the ID*/

	}
	else if(DMSStatue == WNM_STATUS_OVERRIDDEN_DUE_TO_REQUEST_INTERVAL_TOO_LONG)
	{
		/*not success so delete the ID*/

	}
	else if(DMSStatue == WNM_STATUS_OVERRIDDEN_DUE_TO_LACK_RESOURCES)
	{
		/*not success so delete the ID*/
	
	}


	if(gWNMDMS_ID > 0)		
		pAd->StaCfg.bDMSSetUp = TRUE;

	
}


BOOLEAN PeerWNMBTMREQSanity(
    IN PRTMP_ADAPTER pAd, 
    IN VOID *Msg, 
    IN ULONG MsgLen,
    OUT PWNM_BSS_TRANSITION_REQUEST_FRAME BssTrREQFrame)	
{

    	PWNM_BSS_TRANSITION_REQUEST_FRAME	Fr = (PWNM_BSS_TRANSITION_REQUEST_FRAME)Msg;
  
       NdisMoveMemory(BssTrREQFrame, (PCHAR)Fr, sizeof(WNM_BSS_TRANSITION_REQUEST_FRAME));

  
    return TRUE;
}


/*
========================================================================
Routine Description: Send BSS Transition Manganment QUERY

Arguments:

Return Value:

Note:

========================================================================
*/

VOID MlmeWNMBTMQueryAction(
    IN PRTMP_ADAPTER pAd, 
    IN MLME_QUEUE_ELEM *Elem) 
{

	PUCHAR          pOutBuffer = NULL;
	NDIS_STATUS     NStatus;
	UCHAR   QueryReason;
	WNM_BSS_TRANSITION_QUERY_FRAME	BssTrQFrame;
	ULONG           FrameLen;

	PWNM_BSS_TRANSITION_QUERY_FRAME	Fr = (PWNM_BSS_TRANSITION_QUERY_FRAME )Elem->Msg;

	QueryReason = Fr->BSSTransitionQueryReason;

	NStatus = MlmeAllocateMemory(pAd, &pOutBuffer);	 /*Get an unused nonpaged memory */
	if (NStatus != NDIS_STATUS_SUCCESS)
	{
		DBGPRINT(RT_DEBUG_ERROR,(" MlmeWNMBTMQueryAction() allocate memory failed \n"));
		return;
	}

		ActHeaderInit(pAd, &BssTrQFrame.Hdr, pAd->CommonCfg.Bssid, pAd->CurrentAddress, pAd->CommonCfg.Bssid);

	BssTrQFrame.Category = WNM_CATEGORY;
	BssTrQFrame.Action = WNM_ACTION_BSS_TRANS_MANG_QUERY;	
	BssTrQFrame.DialogToken = RandomByte(pAd);


	BssTrQFrame.BSSTransitionQueryReason = QueryReason;

	pAd->StaCfg.BTMQuerySend = TRUE;
	pAd->StaCfg.BTMQueryDialogToken = BssTrQFrame.DialogToken;

	MakeOutgoingFrame(pOutBuffer,               &FrameLen,
					  sizeof(WNM_BSS_TRANSITION_QUERY_FRAME),      &BssTrQFrame,
					  END_OF_ARGS);
	MiniportMMRequest(pAd, QID_AC_BE, pOutBuffer, FrameLen);
	MlmeFreeMemory(pAd, pOutBuffer);
	DBGPRINT(RT_DEBUG_TRACE,("WNM- SendBSSMangtQueryAction( %d )  \n",QueryReason));
 
}



/*
========================================================================
Routine Description: Handler  BSS Transition Manganment REQUEST
				  and send   BSS Transition Manganment RESPONSE	

Arguments:

Return Value:

Note:

========================================================================
*/

VOID PeerWNMBTMReqAction(
    IN PRTMP_ADAPTER pAd, 
    IN MLME_QUEUE_ELEM *Elem) 
{

	UCHAR				DA[MAC_ADDR_LEN];
	WNM_BSS_TRANSITION_RESPONSE_FRAME BssTrRSPFrame;
	WNM_BSS_TRANSITION_REQUEST_FRAME BssTrREQFrame;
	PUCHAR          pOutBuffer = NULL;
	NDIS_STATUS     NStatus;
	ULONG           FrameLen;
	PMAC_TABLE_ENTRY	 pSAEntry;

	if(pAd->StaCfg.bBSSMantAPSupport != TRUE)
	{
		DBGPRINT(RT_DEBUG_ERROR,("AP not support WNM BSS T M  or not enable WNMBSSenable \n"));
		return;
	}

	if (!PeerWNMBTMREQSanity(pAd, Elem->Msg, Elem->MsgLen, &BssTrREQFrame))
	{
       	return;
	}

	pSAEntry = MacTableLookup(pAd, DA);
	NStatus = MlmeAllocateMemory(pAd, &pOutBuffer);	 /*Get an unused nonpaged memory */
	if (NStatus != NDIS_STATUS_SUCCESS)
	{
		DBGPRINT(RT_DEBUG_ERROR,(" PeerWNMBTMReqAction() allocate memory failed \n"));
		return;
	}

	ActHeaderInit(pAd, &BssTrRSPFrame.Hdr, pAd->CommonCfg.Bssid, pAd->CurrentAddress, pAd->CommonCfg.Bssid);

	BssTrRSPFrame.Category = WNM_CATEGORY;
	BssTrRSPFrame.Action = WNM_ACTION_BSS_TRANS_MANG_RESPONSE;	

	
	if(pAd->StaCfg.BTMQuerySend == TRUE)
	{
		pAd->StaCfg.BTMQuerySend = FALSE;
		if(BssTrREQFrame.DialogToken != pAd->StaCfg.BTMQueryDialogToken)
		{
		printk(" error  DialogToken return \n");
		return;
		}
	}
	BssTrRSPFrame.DialogToken = BssTrREQFrame.DialogToken;
	BssTrRSPFrame.Statuscode = 0;
	BssTrRSPFrame.BSSTerminationDelay = 0;

	MakeOutgoingFrame(pOutBuffer,               &FrameLen,
					  sizeof(WNM_BSS_TRANSITION_RESPONSE_FRAME),      &BssTrRSPFrame,
					  END_OF_ARGS);
	MiniportMMRequest(pAd, QID_AC_BE, pOutBuffer, FrameLen);
	MlmeFreeMemory(pAd, pOutBuffer);
	DBGPRINT(RT_DEBUG_TRACE,("WNM- PeerWNMBTMReqAction  \n"));



}


INT	Set_MlmeWNMDMSShow_Proc(
	IN	PRTMP_ADAPTER	pAd, 
	IN	PSTRING			arg)
{
	INT   success = FALSE;
	UCHAR   Show;
	INT	gWNMDMScount;
	Show = (USHORT) simple_strtol(arg, 0, 10);

	if(pAd->StaCfg.bDMSAPSupport != TRUE)
	{
		DBGPRINT(RT_DEBUG_ERROR,("AP not support WNM DMS or not enable WNMDMS \n"));
		return FALSE;
	}



	if(Show == 1)
	{		
		success = TRUE;
	}
	else
	{
		DBGPRINT(RT_DEBUG_ERROR, ("Set_MlmeWNMDMSShow_Proc=1  =>  you type %d    \n",Show));
		success = FALSE;
	}

	
	if(success == TRUE)
	{
		
		for(gWNMDMScount=0; gWNMDMScount < gWNMDMS_ID; gWNMDMScount++)
		{
			printk("gWNMDMS_ID %d   DMS_Dscptor.DMSID %d   ip- %d %d %d %d  \n",
			gWNMDMScount,
			DMS_Dscptor[gWNMDMScount].DMSID,
			WNM_SHOW_IP_HTONL(gWNMCMD_TCLAS_Group[gWNMDMScount].Clasifier.IPv4.IpDest)  );
	
		}
	}
	return success;
}




INT	Set_MlmeWNMDMSReq_Proc(
	IN	PRTMP_ADAPTER	pAd, 
	IN	PSTRING			arg)
{
 	
	WNM_DMS_REQUEST_FRAME 	DMSREQFrame;
	WNM_DMS_REQUEST_ELEMENT 	DMSReqElement;
	UCHAR DialogToken = RandomByte(pAd);

	UCHAR	RequestTyppe, DMSnum, DMSnumCount;
	HEADER_802_11 ActHdr;
	PUCHAR pOutBuffer = NULL;
	NDIS_STATUS NStatus;
	ULONG FrameLen; 
	UINT8 beremove=0;
	UINT8 TotalLen;
	WNM_TCLAS				wnm_tclas;
	ULONG IpAddr32;
	ULONG pOutBufferTmp;
	PSTRING thisChar;
	PSTRING value;
	int i;
	UCHAR IpAddr[gWNMDMS_ID][4];

	if(pAd->StaCfg.bDMSAPSupport != TRUE)
	{
		DBGPRINT(RT_DEBUG_ERROR,("AP not support WNM DMS or not enable WNMDMS \n"));
		return FALSE;
	}

	RequestTyppe = (USHORT) simple_strtol(arg, 0, 10);

	printk("RequestTyppe %d \n",RequestTyppe);

	arg += 2; /* RequestTyppe */

	DMSnum = (USHORT) simple_strtol(arg, 0, 10);

	printk("DMSnum %d \n",DMSnum);

	arg += 2; /* DMSnum  */

	NStatus = MlmeAllocateMemory(pAd, (PVOID)&pOutBuffer);  /*Get an unused nonpaged memory */
	if(NStatus != NDIS_STATUS_SUCCESS)
	{
		DBGPRINT(RT_DEBUG_TRACE, ("%s() allocate memory failed \n", __FUNCTION__));
		return FALSE;
	}

	/* build action frame header. */
	MgtMacHeaderInit(pAd, &ActHdr, SUBTYPE_ACTION, 0, pAd->CommonCfg.Bssid,
#ifdef P2P_SUPPORT
						pAd->CommonCfg.Bssid,
#endif /* P2P_SUPPORT */
						pAd->CommonCfg.Bssid);

	NdisMoveMemory(pOutBuffer, (PCHAR)&ActHdr, sizeof(HEADER_802_11));
	FrameLen = sizeof(HEADER_802_11);

	InsertActField(pAd, (pOutBuffer + FrameLen), &FrameLen,
		WNM_CATEGORY, WNM_ACTION_DMS_REQUEST);

		printk("DialogToken %d \n",DialogToken);
	InsertDialogToken(pAd, (pOutBuffer + FrameLen), &FrameLen, DialogToken);
	pAd->StaCfg.DMSREQDialogToken = DialogToken;

/*Draf 6.0 change DMS request format */
/*DMS Request element format*/
/*Because lenth is total all DMS elements => one or more DMSDescripotr , put at end*/
/**skip Element ID   
	Length ,   
	Request Type */
	pOutBufferTmp = FrameLen;
	FrameLen += 3;


/*	DMSREQFrame.RequestTyppe = RequestTyppe; */
/*	InsertRequestTyppe(pAd, (pOutBuffer + FrameLen), &FrameLen, RequestTyppe); */


	
	switch(RequestTyppe)
	{

		case DMS_REQUEST_TYPE_ADD: 
		case DMS_REQUEST_TYPE_REMOVE:

			for(DMSnumCount = 0 ; DMSnumCount < DMSnum ; DMSnumCount ++)
			{
				if(RequestTyppe == DMS_REQUEST_TYPE_ADD)
				{
					if(gWNMDMS_ID > 5)
					{
						printk("out of DMS number \n");
						return FALSE;
					}
				}
				if(RequestTyppe == DMS_REQUEST_TYPE_REMOVE)
				{
					if(gWNMDMS_ID == 0)
					{
						printk("no DMSID to remove \n");
						return FALSE;
					}
				}

				DMS_Dscptor[gWNMDMS_ID].DMSID = (USHORT) simple_strtol(arg, 0, 10);
				printk("DMS_Dscptor.DMSID  %d \n",DMS_Dscptor[gWNMDMS_ID].DMSID);
				/*chech  is it a duplicate  DMSID*/
				for(i=0; i< gWNMDMS_ID; i++)
				{
					if(DMS_Dscptor[gWNMDMS_ID].DMSID == DMS_Dscptor[i].DMSID )
					{
						beremove = 1;
						if(RequestTyppe == DMS_REQUEST_TYPE_ADD)
						{
							printk("DMS_REQUEST_TYPE_ADD this DMSID is exist \n");
							return FALSE;
						}
					}
				}

				if((beremove != 1) && (RequestTyppe == DMS_REQUEST_TYPE_REMOVE))	
				{
							printk("DMS_REQUEST_TYPE_REMOVE no this DMSID \n");
							return FALSE;
				}
				arg += 2;
		
				while ((thisChar = strsep((char **)&arg, "-")) != NULL)
				{

					for (i=0, value = rstrtok(thisChar,"."); value; value = rstrtok(NULL,".")) 
					{
						if((strlen(value) > 0) && (strlen(value) <= 3)) 
						{
							int ii;
							for(ii=0; ii<strlen(value); ii++)
								if (!isxdigit(*(value + ii))){
									printk("@\n");
									return FALSE;
								}
							}
						else{
							printk("$\n");
							return FALSE;  /*Invalid */
						}

					IpAddr[gWNMDMS_ID][i] = (UCHAR)simple_strtol(value, NULL, 10);
					i++;
				}
				if(i != 4){
					printk("&\n");
					return FALSE;  /*Invalid */
				}
/*
				printk("IpAddr[0] %d IpAddr[1] %d IpAddr[2] %d IpAddr[3] %d  \n"
				,IpAddr[gWNMDMS_ID][0],IpAddr[gWNMDMS_ID][1],
				IpAddr[gWNMDMS_ID][2],IpAddr[gWNMDMS_ID][3]);
*/			
				(IpAddr32 ) = ((ULONG) IpAddr[gWNMDMS_ID][3] << 24) | 
							((ULONG) IpAddr[gWNMDMS_ID][2] << 16) | 
							((ULONG) IpAddr[gWNMDMS_ID][1] << 8) | 
							((ULONG) IpAddr[gWNMDMS_ID][0]);
				gWNMCMD_TCLAS_Group[gWNMDMS_ID].Clasifier.IPv4.IpDest = IpAddr32;	
/*1 Request Type 2 TCAL header */
				TotalLen = 1  + 2 + WNM_TCLAS_TYPE_IP_V4_LEN;			
				WNM_InsertDMS(pAd, (pOutBuffer + FrameLen), &FrameLen,
				(WNM_TCLAS_TYPE_IP_V4_LEN+2),  DMS_Dscptor[gWNMDMS_ID].DMSID,
				wnm_tclas, IpAddr32);
	
				break;
				}

			}/*for(DMSnumCount = 0 ; DMSnumCount < DMSnum ; DMSnumCount ++)*/


/*DMS Request element  format*/
/* 	Element ID   
	Length ,   
	Request Type  */

	DMSReqElement.ElementId = WNM_INF_ELE_DMS_REQUEST ;
	DMSReqElement.Length = TotalLen;;
	printk("tatal length %d \n",TotalLen);
	DMSReqElement.RequestType = RequestTyppe;
	InsertDMSReqElement(pAd, (pOutBuffer + pOutBufferTmp),
		&FrameLen,DMSReqElement);



	
			MiniportMMRequest(pAd, QID_AC_BE, pOutBuffer, FrameLen);

			if (pOutBuffer)
				MlmeFreeMemory(pAd, pOutBuffer);
			
			break;


		case DMS_REQUEST_TYPE_CHANGE:

			break;

		default: /* error command type */
			DBGPRINT(RT_DEBUG_ERROR,("WNM-  error RequestTyppe  \n"));

			return -EINVAL; /* input error */
	} /* End of switch */


	return TRUE;

}


INT	Set_WNMTransMantQuery_Proc(
	IN	PRTMP_ADAPTER	pAd, 
	IN	PSTRING			arg)
{
	INT   success = FALSE;
	UCHAR   QueryReason;
	WNM_BSS_TRANSITION_QUERY_FRAME	BssTrQFrame;

	if(pAd->StaCfg.bBSSMantAPSupport != TRUE)
	{
		DBGPRINT(RT_DEBUG_ERROR,("AP not support WNM BSS or not enable WNM BSS \n"));
		return FALSE;
	}



	QueryReason = (UCHAR) simple_strtol(arg, 0, 10);
	if((QueryReason < 17) && (QueryReason > 0 ))
	{		
		success = TRUE;
	}
	else
	{
		DBGPRINT(RT_DEBUG_ERROR, ("bad QueryReason number  %d   ==> 0 ~ 16 \n",QueryReason));
		success = FALSE;
	}

	if(pAd->StaCfg.bBSSMantAPSupport != TRUE)
	{
		DBGPRINT(RT_DEBUG_ERROR,("AP not support WNM BSS  or STA not enable WNM BSS T M\n"));
		success = FALSE;
	}

	if(success == TRUE)
	{

	ActHeaderInit(pAd, &BssTrQFrame.Hdr, pAd->CommonCfg.Bssid, pAd->CurrentAddress, pAd->CommonCfg.Bssid);

	BssTrQFrame.Category = WNM_CATEGORY;
	BssTrQFrame.Action = WNM_ACTION_BSS_TRANS_MANG_QUERY;	
	BssTrQFrame.BSSTransitionQueryReason = QueryReason;

		MlmeEnqueue(pAd, ACTION_STATE_MACHINE, WNM_CATEGORY_BSS_TRANSITION,sizeof(BssTrQFrame), &BssTrQFrame,0);
/*		printk("iverson  MlmeEnqueue WNM_STATE_MACHINE  MT2_MLME_WNM_BTM_QUERY %d \n",QueryReason); */
	}

	DBGPRINT(RT_DEBUG_TRACE, ("Set_WNMTransMantQuery_Proc::(QueryReason=%d)\n", QueryReason));

	return success;

}


#endif /* CONFIG_STA_SUPPORT */

#endif /* DOT11V_WNM_SUPPORT */

