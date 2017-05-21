/****************************************************************************
 * Ralink Tech Inc.
 * Taiwan, R.O.C.
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
	rt_ecos.c

    Abstract:
    Common functions for eCos Platform
 
    Revision History:
    Who          When          What
    --------    ----------      ------------------------------------------
*/

#include "rt_config.h"

#ifdef BRANCH_ADV
#include <eventlog.h>
#endif /* BRANCH_ADV */

ULONG RTDebugLevel = RT_DEBUG_ERROR;
ULONG RTDebugFunc = 0;

/*UCHAR   RALINK_OUI[]  = {0x00, 0x0c, 0x43}; */
#ifdef BRANCH_ADV
UCHAR   DbgBuffer[2048];
#define is_digit(c) ((c >= '0') && (c <= '9'))

#ifdef VENDOR_FEATURE4_SUPPORT
ULONG	OS_NumOfMemAlloc = 0, OS_NumOfMemFree = 0;
#endif /* VENDOR_FEATURE4_SUPPORT */
#ifdef VENDOR_FEATURE2_SUPPORT
ULONG	OS_NumOfPktAlloc = 0, OS_NumOfPktFree = 0;
#endif /* VENDOR_FEATURE2_SUPPORT */

static int
_cvt(unsigned long long val, char *buf, long radix, char *digits)
{
    char temp[80];
    char *cp = temp;
    int length = 0;

    if (val == 0) {
        /* Special case */
        *cp++ = '0';
    } else {
        while (val) {
            *cp++ = digits[val % radix];
            val /= radix;
        }
    }
    while (cp != temp) {
        *buf++ = *--cp;
        length++;
    }
    *buf = '\0';
    return (length);
}

static cyg_bool diag_check_string( const char *str )
{
    cyg_bool result = true;
    const char *s;

    if( str == NULL ) return false;
    
    for( s = str ; result && *s ; s++ )
    {
        char c = *s;

        /* Check for a reasonable length string. */
        
        if( s-str > 2048 ) result = false;

        /* We only really support CR, NL, tab and backspace at present.
	 * If we want to use other special chars, this test will
         * have to be expanded.  */

        if( c == '\n' || c == '\r' || c == '\b' || c == '\t' || c == '\033' )
            continue;

        /* Check for printable chars. This assumes ASCII */
        
        if( c < ' ' || c > '~' )
            result = false;

    }

    return result;
}

static int _vprintf(char *DbgBuffer, const char *fmt, va_list ap)
{
    char buf[sizeof(long long)*8];
    char c, sign, *cp=buf;
    int left_prec, right_prec, zero_fill, pad, pad_on_right, 
        i, islong, islonglong;
    long long val = 0;
    int res = 0, length = 0;

    if (!diag_check_string(fmt)) {
        diag_write_string("<Bad format string: ");
        diag_write_hex((cyg_uint32)fmt);
        diag_write_string(" :");
        for( i = 0; i < 8; i++ ) {
            diag_write_char(' ');
            val = va_arg(ap, unsigned long);
            diag_write_hex(val);
        }
        diag_write_string(">\n");
        return 0;
    }
    while ((c = *fmt++) != '\0') {
        if (c == '%') {
            c = *fmt++;
            left_prec = right_prec = pad_on_right = islong = islonglong = 0;
            if (c == '-') {
                c = *fmt++;
                pad_on_right++;
            }
            if (c == '0') {
                zero_fill = true;
                c = *fmt++;
            } else {
                zero_fill = false;
            }
            while (is_digit(c)) {
                left_prec = (left_prec * 10) + (c - '0');
                c = *fmt++;
            }
            if (c == '.') {
                c = *fmt++;
                zero_fill++;
                while (is_digit(c)) {
                    right_prec = (right_prec * 10) + (c - '0');
                    c = *fmt++;
                }
            } else {
                right_prec = left_prec;
            }
            sign = '\0';
            if (c == 'l') {
                /* 'long' qualifier */
                c = *fmt++;
		islong = 1;
                if (c == 'l') {
                    /* long long qualifier */
                    c = *fmt++;
                    islonglong = 1;
                }
            }
            if (c == 'z') {
                c = *fmt++;
		islong = sizeof(size_t) == sizeof(long);
            }
            /* Fetch value [numeric descriptors only] */
            switch (c) {
            case 'p':
		islong = 1;
            case 'd':
            case 'D':
            case 'x':
            case 'X':
            case 'u':
            case 'U':
            case 'b':
            case 'B':
                if (islonglong) {
                    val = va_arg(ap, long long);
	        } else if (islong) {
                    val = (long long)va_arg(ap, long);
		} else{
                    val = (long long)va_arg(ap, int);
                }
                if ((c == 'd') || (c == 'D')) {
                    if (val < 0) {
                        sign = '-';
                        val = -val;
                    }
                } else {
                    /* Mask to unsigned, sized quantity */
                    if (islong) {
                        val &= ((long long)1 << (sizeof(long) * 8)) - 1;
                    } else if (!islonglong) { /* no need to mask longlong */
                        val &= ((long long)1 << (sizeof(int) * 8)) - 1;
                    }
                }
                break;
            default:
                break;
            }
            /* Process output */
            switch (c) {
            case 'p':  /* Pointer */
                DbgBuffer[res] = '0';
                DbgBuffer[res+1] = 'x';
                zero_fill = true;
                left_prec = sizeof(unsigned long)*2;
                res += 2;  /* Account for "0x" leadin */
            case 'd':
            case 'D':
            case 'u':
            case 'U':
            case 'x':
            case 'X':
                switch (c) {
                case 'd':
                case 'D':
                case 'u':
                case 'U':
                    length = _cvt(val, buf, 10, (char *)"0123456789");
                    break;
                case 'p':
                case 'x':
                    length = _cvt(val, buf, 16, (char *)"0123456789abcdef");
                    break;
                case 'X':
                    length = _cvt(val, buf, 16, (char *)"0123456789ABCDEF");
                    break;
                }
                cp = buf;
                break;
            case 's':
            case 'S':
                cp = va_arg(ap, char *);
                if (cp == NULL) 
                    cp = (char *)"<null>";
                else if (!diag_check_string(cp)) {
                    diag_write_string("<Not a string: 0x");
                    diag_write_hex((cyg_uint32)cp);
                    cp = (char *)">";
                }
                length = 0;
                while (cp[length] != '\0') length++;
                break;
            case 'c':
            case 'C':
                c = va_arg(ap, int /*char*/);
                DbgBuffer[res] = c;
                res++;
                continue;
            case 'b':
            case 'B':
                length = left_prec;
                if (left_prec == 0) {
                    if (islonglong)
                        length = sizeof(long long)*8;
                    else if (islong)
                        length = sizeof(long)*8;
                    else
                        length = sizeof(int)*8;
                }
                for (i = 0;  i < length-1;  i++) {
                    buf[i] = ((val & ((long long)1<<i)) ? '1' : '.');
                }
                cp = buf;
                break;
            case '%':
                DbgBuffer[res] = '%';
                res++;
                continue;
            default:
                DbgBuffer[res] = '%';
                DbgBuffer[res+1] = c;
                res += 2;
                continue;
            }
            pad = left_prec - length;
            if (sign != '\0') {
                pad--;
            }
            if (zero_fill) {
                c = '0';
                if (sign != '\0') {
                    DbgBuffer[res] = sign;
                    res++;
                    sign = '\0';
                }
            } else {
                c = ' ';
            }
            if (!pad_on_right) {
                while (pad-- > 0) {
                    DbgBuffer[res] = c;
                    res++;
                }
            }
            if (sign != '\0') {
                DbgBuffer[res] = sign;
                res++;
            }
            while (length-- > 0) {
                c = *cp++;
                DbgBuffer[res] = c;
                res++;
            }
            if (pad_on_right) {
                while (pad-- > 0) {
                    DbgBuffer[res] = ' ';
                    res++;
                }
            }
        } else {
            DbgBuffer[res] = c;
            res++;
        }
    }
    return (res);
}

int printUI(const char *fmt, ...)
{
    int ret = 0;
    va_list ap;

    va_start(ap, fmt);
    ret = _vprintf(DbgBuffer, fmt, ap);
    va_end(ap);
    DbgBuffer[ret] = '\0';
    if (ret > 0)
        SysLog(LOG_USER|LOG_INFO|LOGM_WLAN, DbgBuffer);	
    return (ret);
}
#endif /* BRANCH_ADV */

/*
	This function copy from target/usr/src/libdl/strsep.c
*/
char *strsep(register char **stringp, register const char *delim)
{
	register char *s;
	register const char *spanp;
	register int c, sc;
	char *tok;

	if ((s = *stringp) == NULL)
		return (NULL);
	for (tok = s;;) {
		c = *s++;
		spanp = delim;
		do {
			if ((sc = *spanp++) == c) {
				if (c == 0)
					s = NULL;
				else
					s[-1] = 0;
				*stringp = s;
				return (tok);
			}
		} while (sc != 0);
	}
	/* NOTREACHED */
}


unsigned long simple_strtoul(const char *cp,char **endp,unsigned int base)
{
        unsigned long result = 0,value;

        if (!base) {
                base = 10;
                if (*cp == '0') {
                        base = 8;
                        cp++;
                        if ((*cp == 'x') && isxdigit(cp[1])) {
                                cp++;
                                base = 16;
                        }
                }
        }
        while (isxdigit(*cp) &&
               (value = isdigit(*cp) ? *cp-'0' : toupper(*cp)-'A'+10) < base) {
                result = result*base + value;
                cp++;
        }
        if (endp)
                *endp = (char *)cp;
        return result;
}

long simple_strtol(const char *cp,char **endp,unsigned int base)
{
        if(*cp=='-')
                return -simple_strtoul(cp+1,endp,base);
        return simple_strtoul(cp,endp,base);
}
void hex_dump(char *str, unsigned char *pSrcBufVA, unsigned int SrcBufLen)
{
	unsigned char *pt;
	int x;

	if (RTDebugLevel < RT_DEBUG_TRACE)
		return;
	
	pt = pSrcBufVA;
	printf("%s: %p, len = %d\n",str,  pSrcBufVA, SrcBufLen);
	for (x=0; x<SrcBufLen; x++)
	{
		if (x % 16 == 0) 
			printf("0x%04x : ", x);
		printf("%02x ", ((unsigned char)pt[x]));
		if (x%16 == 15) printf("\n");
	}
    printf("\n");
}


#ifdef DBG
void dump_RxDesc(PRXD_STRUC pRxDesc)
{
	printf("Dump RxDesc = 0x%x!\n", (INT32) pRxDesc);
	hex_dump("RxDescRawData", (PUCHAR)pRxDesc, sizeof(RXD_STRUC));
	
	/* Word 0 */
	printf("\tSDP0=0x%x!\n", pRxDesc->SDP0);

	/*Word 1 */
	printf("\tSDL1=0x%x!\n", pRxDesc->SDL1);
	printf("\tSDL0=0x%x!\n", pRxDesc->SDL0);
	printf("\tLS0=0x%x!\n", pRxDesc->LS0);
	printf("\tDDONE=0x%x!\n", pRxDesc->DDONE);

	/* Word 2 */
	printf("\tSDP1=0x%x!\n", pRxDesc->SDP1);

	/* Word 3 */
	printf("\tBA=0x%x!\n", pRxDesc->BA);
	printf("\tDATA=0x%x!\n", pRxDesc->DATA);
	printf("\tNULLDATA=0x%x!\n", pRxDesc->NULLDATA);
	printf("\tFRAG=0x%x!\n", pRxDesc->FRAG);
	printf("\tU2M=0x%x!\n", pRxDesc->U2M);			    /* 1: this RX frame is unicast to me */
	printf("\tMcast=0x%x!\n", pRxDesc->Mcast);			/* 1: this is a multicast frame */
	printf("\tBcast=0x%x!\n", pRxDesc->Bcast);			/* 1: this is a broadcast frame */
	printf("\tMyBss=0x%x!\n", pRxDesc->MyBss);			/* 1: this frame belongs to the same BSSID */
	printf("\tCrc=0x%x!\n", pRxDesc->Crc);				/* 1: CRC error */
	printf("\tCipherErr=0x%x!\n", pRxDesc->CipherErr);	/* 0: decryption okay, 1:ICV error, 2:MIC error, 3:KEY not valid */
	printf("\tAMSDU=0x%x!\n", pRxDesc->AMSDU);	    	/* rx with 802.3 header, not 802.11 header. */
	printf("\tHTC=0x%x!\n", pRxDesc->HTC);
	printf("\tRSSI=0x%x!\n", pRxDesc->RSSI);
	printf("\tL2PAD=0x%x!\n", pRxDesc->L2PAD);
	printf("\tAMPDU=0x%x!\n", pRxDesc->AMPDU);
	printf("\tDecrypted=0x%x!\n", pRxDesc->Decrypted);	/* this frame is being decrypted. */
}

	
void dump_RxWI(RXWI_STRUC *pRxWI)
{
	printf("Dump RxWI = 0x%x!\n", (INT32) pRxWI);
	hex_dump("RxWIRawData", (PUCHAR)pRxWI, sizeof(RXWI_STRUC));
	
	/* word 0 */
	printf("\tWirelessCliID=%d!\n", pRxWI->RxWIWirelessCliID);
	printf("\tKeyIndex=%d!\n", pRxWI->RxWIKeyIndex);
	printf("\tBSSID=%d!\n", pRxWI->BSSID);
	printf("\tUDF=%d!\n", pRxWI->UDF);
	printf("\tTID=%d!\n", pRxWI->RxWITID);

	/* word 1 */
	printf("\tFRAG=%d!\n", pRxWI->FRAG);
	printf("\tSEQUENCE=%d!\n", pRxWI->SEQUENCE);
	printf("\tMCS=%d!\n", pRxWI->RxWIMCS);
	printf("\tBW=%d!\n", pRxWI->RxWIBW);
	printf("\tShortGI=%d!\n", pRxWI->RxWISGI);
	printf("\tSTBC=%d!\n", pRxWI->RxWISTBC);
	printf("\tPHYMODE=%d!\n", pRxWI->RxWIPhyMode);

	/* word 2 */
	printf("\tRSSI0=%d!\n", pRxWI->RxWIRSSI0);
	printf("\tRSSI1=%d!\n", pRxWI->RxWIRSSI1);
	printf("\tRSSI2=%d!\n", pRxWI->RxWIRSSI2);

	/* word 3 */
	printf("\tSNR0=%d!\n", pRxWI->RxWISNR0);
	printf("\tSNR1=%d!\n", pRxWI->RxWISNR1);
}
#endif /* DBG */


/***********************************************************************************
 *
 *	Definition of timer and time related functions
 * ***********************************************************************************/ 
/* timeout -- ms */
VOID RTMP_SetPeriodicTimer(
	IN	NDIS_MINIPORT_TIMER *pTimer, 
	IN	unsigned long timeout)
{
	if (pTimer->sys_clk)
	{
		timeout = (timeout * OS_HZ) / 1000;
		cyg_alarm_initialize(pTimer->alarm_hdl, cyg_current_time() + timeout, timeout);
	} else {
		DBGPRINT(RT_DEBUG_ERROR, ("RTMP_SetPeriodicTimer: Timer is not initial!\n"));
	}
}

VOID RTMP_OS_Init_Timer(
	IN	VOID 					*pReserved,
	IN	NDIS_MINIPORT_TIMER		*pTimer, 
	IN	TIMER_FUNCTION			function,
	IN	PVOID					data,
	IN	LIST_HEADER				*pTimerList)
{
    pTimer->sys_clk = cyg_real_time_clock();
	if (pTimer->sys_clk)
	{	
		cyg_clock_to_counter(pTimer->sys_clk, &pTimer->counter_hdl);
		pTimer->data = data;
		cyg_alarm_create(pTimer->counter_hdl,
			function,
 			(cyg_addrword_t) pTimer->data,
			&pTimer->alarm_hdl,
			&pTimer->alarm_obj);        
	}
	else
	{
		PRALINK_TIMER_STRUCT	pTimer;

		pTimer = (PRALINK_TIMER_STRUCT)data;
		pTimer->Valid = FALSE;
		DBGPRINT(RT_DEBUG_ERROR, ("init_Timer failed!\n"));
	}
}

VOID RTMP_OS_Add_Timer(
	IN	NDIS_MINIPORT_TIMER		*pTimer,
	IN	unsigned long timeout)
{
	if (pTimer->sys_clk)
	{
	    cyg_alarm_disable(pTimer->alarm_hdl);
		timeout = (timeout * OS_HZ)  / 1000;
        if (timeout > 0)
		cyg_alarm_initialize(pTimer->alarm_hdl, cyg_current_time() + timeout, 0);
	} else {
		DBGPRINT(RT_DEBUG_ERROR, ("RTMP_OS_Add_Timer: Timer is not initial!\n"));
	}
}

VOID RTMP_OS_Mod_Timer(
	IN	NDIS_MINIPORT_TIMER		*pTimer,
	IN	unsigned long timeout)
{
    if (pTimer->sys_clk)
	{
	    cyg_alarm_disable(pTimer->alarm_hdl);
		timeout = (timeout * OS_HZ) / 1000;
        if (timeout > 0)
            cyg_alarm_initialize(pTimer->alarm_hdl, cyg_current_time() + timeout, 0);
	} else {
		DBGPRINT(RT_DEBUG_ERROR, ("RTMP_OS_Mod_Timer: Timer is not initial!\n"));
    }
}

VOID RTMP_OS_Del_Timer(
	IN	NDIS_MINIPORT_TIMER		*pTimer,
	OUT	BOOLEAN					*pCancelled)
{
    if (pTimer->sys_clk)
	{
	    cyg_alarm_disable(pTimer->alarm_hdl);
		*pCancelled = TRUE;
	} else {
		DBGPRINT(RT_DEBUG_ERROR, ("CancelTimer failed!\n"));
		*pCancelled = FALSE;
    }
}

VOID RTMP_OS_Release_Timer(
	IN	NDIS_MINIPORT_TIMER		*pTimer)
{
}

/* Unify all delay routine by using udelay */
VOID RTMPusecDelay(
	IN	ULONG	usec)
{
    CYGACC_CALL_IF_DELAY_US((UINT32)usec);
}

VOID RtmpOsMsDelay(
	IN	ULONG	msec)
{
	mdelay(msec);
}

void RTMP_GetCurrentSystemTime(LARGE_INTEGER *NowTime)
{
	NowTime->u.HighPart = 0;
	time((time_t *)&NowTime->u.LowPart);
}


/*******************************************************************************

	Flash Read/Write related functions.
	
 *******************************************************************************/
#ifdef RTMP_RBUS_SUPPORT
#ifndef CONFIG_RALINK_FLASH_API
void RtmpFlashWrite(UCHAR *p, ULONG offset, ULONG size)
{
	cyg_flashaddr_t err_addr;
	cyg_flashaddr_t addr = (cyg_flashaddr_t)offset;
	int status;
	
	status = cyg_flash_erase (addr, size, &err_addr);
	if (status != CYG_FLASH_ERR_OK) 
		DBGPRINT(RT_DEBUG_ERROR, ("Flash erase error : %s\n", cyg_flash_errmsg (status)));

	status = cyg_flash_program(addr, p, size, &err_addr);	
	if (status != CYG_FLASH_ERR_OK)
		DBGPRINT(RT_DEBUG_ERROR, ("FlashWrite error : %s\n", cyg_flash_errmsg (status)));
}


void RtmpFlashRead(UCHAR *p, ULONG a, ULONG b)
{
	cyg_flashaddr_t err_addr;
	cyg_flashaddr_t flsbase = (cyg_flashaddr_t)a;
	size_t len = (size_t)b;
	void *rambase = (void *)p;
	int status;
	
	status = cyg_flash_read(flsbase, rambase, len, &err_addr);
	if (status != CYG_FLASH_ERR_OK)
		DBGPRINT(RT_DEBUG_ERROR, ("FlashRead error : %s\n", cyg_flash_errmsg (status)));

}
#endif /* CONFIG_RALINK_FLASH_API */
#endif /* RTMP_RBUS_SUPPORT */


/*******************************************************************************

	Normal memory allocation related functions.
	
 *******************************************************************************/
NDIS_STATUS os_alloc_mem(
	IN	VOID *pAd,
	OUT	UCHAR **mem,
	IN	ULONG  size)
{	
	*mem = (PUCHAR) kmalloc(size, 0);
	if (*mem)
		return (NDIS_STATUS_SUCCESS);
	else
	{
		DBGPRINT(RT_DEBUG_TRACE, ("malloc failed size = %d\n", (INT) size));
		return (NDIS_STATUS_FAILURE);
	}
}

NDIS_STATUS os_alloc_mem_suspend(
	IN	VOID					*pReserved,
	OUT	UCHAR					**mem,
	IN	ULONG					size)
{
	return os_alloc_mem(pReserved, mem, size);
}


/* pAd MUST allow to be NULL */
NDIS_STATUS os_free_mem(
	IN	VOID *pAd,
	IN	PVOID mem)
{
	
	ASSERT(mem);
	kfree(mem);
	return (NDIS_STATUS_SUCCESS);
}


/*******************************************************************************

	Device IRQ related functions.
	
 *******************************************************************************/
int RtmpOSIRQRequest(IN PNET_DEV pNetDev)
{
	return 0; 
}

int RtmpOSIRQRelease(
	IN	PNET_DEV				pNetDev,
	IN	UINT32					infType,
	IN	PPCI_DEV				pci_dev,
	IN	BOOLEAN					*pHaveMsi)
{
	return 0;
}


/*******************************************************************************

	File open/close related functions.
	
 *******************************************************************************/
/*EddyTODO */
RTMP_OS_FD RtmpOSFileOpen(char *pPath,  int flag, int mode)
{
    return -1;
/*	return open(pPath, flag, mode); */
}

int RtmpOSFileClose(RTMP_OS_FD osfd)
{
    return -1;
/*	return close(osfd); */
}

void RtmpOSFileSeek(RTMP_OS_FD osfd, int offset)
{
/*	lseek(osfd, offset, SEEK_SET); */
}

int RtmpOSFileRead(RTMP_OS_FD osfd, char *pDataPtr, int readLen)
{
    return -1;
/*	return read(osfd, pDataPtr, readLen); */
}

int RtmpOSFileWrite(RTMP_OS_FD osfd, char *pDataPtr, int writeLen)
{
    return -1;
/*	return write(osfd, pDataPtr, writeLen); */
}

void RtmpOSFSInfoChange(RTMP_OS_FS_INFO *pOSFSInfo, BOOLEAN bSet)
{
	return;
}


/*******************************************************************************

	Task create/management/kill related functions.
	
 *******************************************************************************/
#ifndef NET_TASK_PRIORITY
#define NET_TASK_PRIORITY       4
#endif
NDIS_STATUS RtmpOSTaskAttach(
	IN RTMP_OS_TASK *pTask,
	IN RTMP_OS_TASK_CALLBACK fn, 
	IN ULONG arg)
{
	NDIS_STATUS status;

    cyg_thread_create(NET_TASK_PRIORITY, (FUNCPTR)fn, (cyg_addrword_t) arg,
		    pTask->taskName, (void *) pTask->stack, sizeof(pTask->stack),
		    &pTask->threadID, &pTask->thread_obj);
	if (pTask->threadID == NULL) 
	{
		DBGPRINT(RT_DEBUG_ERROR, ("Attach task(%s) failed!\n", pTask->taskName));
		pTask->taskPID = -1;
		status = NDIS_STATUS_FAILURE;
	}
	else {
		status = NDIS_STATUS_SUCCESS;
		
		pTask->taskComplete.done = 0;
		cyg_semaphore_init(&pTask->taskComplete.wait, 0);
		
		cyg_thread_resume(pTask->threadID);        
    }
	
	return status;
}

NDIS_STATUS RtmpOSTaskInit(
	IN RTMP_OS_TASK *pTask,
	PSTRING			 pTaskName,
	VOID			 *pPriv,
	LIST_HEADER				*pTaskList,
	LIST_HEADER				*pSemList)
{
	int len;
	
	ASSERT(pTask);

	NdisZeroMemory((PUCHAR)(pTask), sizeof(RTMP_OS_TASK));

	len = strlen(pTaskName);
	len = len > (RTMP_OS_TASK_NAME_LEN -1) ? (RTMP_OS_TASK_NAME_LEN-1) : len;
	NdisMoveMemory(&pTask->taskName[0], pTaskName, strlen(pTaskName)); 
	
	RTMP_SEM_EVENT_INIT_LOCKED(&(pTask->taskSema), NULL);

	pTask->priv = pPriv;
	
	return NDIS_STATUS_SUCCESS;
}

INT RtmpOSTaskNotifyToExit(
	IN RTMP_OS_TASK *pTask)
{
	pTask->taskComplete.done = 1;
	cyg_semaphore_post(&pTask->taskComplete.wait);
	return 0;
}

void RtmpOSTaskCustomize(
	IN RTMP_OS_TASK *pTask)
{
	return;
}

NDIS_STATUS RtmpOSTaskKill(
	IN RTMP_OS_TASK *pTask)
{
	UINT retVal;
	int cnt = 0;
	
	pTask->task_killed = 1;
	RTMP_SEM_EVENT_UP(&pTask->taskSema);
	retVal = cyg_thread_delete(pTask->threadID);

	do
	{
		cyg_semaphore_trywait(&pTask->taskComplete.wait);
		
		if (pTask->taskComplete.done == 1)
			break;
		else
		{
			cyg_thread_info info;
			cyg_uint16 id;
			cyg_bool_t rt;
			int state = -1;

			id = cyg_thread_get_id(pTask->threadID);
			rt = cyg_thread_get_info(pTask->threadID, id, &info);
			if (rt == 1)
				state = info.state;
			DBGPRINT(RT_DEBUG_ERROR, ("Killed task(%s) donebit=%d, status=%d, round=%d!\n",
				pTask->taskName, pTask->taskComplete.done, state, cnt)); 
			cyg_thread_yield();
		}
		cnt++;
	}while(cnt< 1000);
	
	if (retVal == 0)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("Kill task(%s) failed!\n", pTask->taskName)); 
		return NDIS_STATUS_FAILURE;
	}	
	else
	{
	       pTask->task_killed = 0;
		DBGPRINT(RT_DEBUG_ERROR, ("Kill task(%s) succeed!\n", pTask->taskName)); 
	return NDIS_STATUS_SUCCESS;
}
}

/* IRQL = DISPATCH_LEVEL */
/* NOTE: we do have an assumption here, that Byte0 and Byte1 always reasid at the same */
/*			 scatter gather buffer */
NDIS_STATUS Sniff2BytesFromNdisBuffer(
	IN	PNDIS_BUFFER	pFirstBuffer,
	IN	UCHAR			DesiredOffset,
	OUT PUCHAR			pByte0,
	OUT PUCHAR			pByte1)
{
    *pByte0 = *(PUCHAR)(pFirstBuffer + DesiredOffset);
    *pByte1 = *(PUCHAR)(pFirstBuffer + DesiredOffset + 1);

	return NDIS_STATUS_SUCCESS;
}


/* */
/* change OS packet DataPtr and DataLen */
/* */
void  update_os_packet_info(
	IN	PRTMP_ADAPTER	pAd, 
	IN	RX_BLK			*pRxBlk,
	IN  UCHAR			FromWhichBSSID)
{
    PECOS_PKT_BUFFER pkt;
	PNET_DEV	pNetDev;

	ASSERT(pRxBlk->pRxPacket);
	pkt = RTPKT_TO_OSPKT(pRxBlk->pRxPacket);

	pNetDev = get_netdev_from_bssid(pAd, FromWhichBSSID);
	SET_OS_PKT_NETDEV(pkt, pNetDev);

	SET_OS_PKT_DATAPTR(pkt, pRxBlk->pData);
	SET_OS_PKT_LEN(pkt, pRxBlk->DataSize);
}

void wlan_802_11_to_802_3_packet(
	IN	PNET_DEV				pNetDev,
	IN	UCHAR					OpMode,
	IN	USHORT					VLAN_VID,
	IN	USHORT					VLAN_Priority,
	IN	PNDIS_PACKET			pRxPacket,
	IN	UCHAR					*pData,
	IN	ULONG					DataSize,
	IN	PUCHAR					pHeader802_3,
	IN  UCHAR					FromWhichBSSID,
	IN	UCHAR					*TPID)
{
    PECOS_PKT_BUFFER pkt;

	ASSERT(pRxPacket);
	ASSERT(pHeader802_3);

	pkt = RTPKT_TO_OSPKT(pRxPacket);

	SET_OS_PKT_NETDEV(pkt, pNetDev);
	SET_OS_PKT_DATAPTR(pkt, pData);
	SET_OS_PKT_LEN(pkt, DataSize);

	/* */
	/* copy 802.3 header */
	/* */
	/* */
#ifdef CONFIG_AP_SUPPORT
	RT_CONFIG_IF_OPMODE_ON_AP(OpMode)
	{
		/* maybe insert VLAN tag to the received packet */
		UCHAR VLAN_Size = 0;
		UCHAR *data_p;

		/* VLAN related */
		if (VLAN_VID != 0)
			VLAN_Size = LENGTH_802_1Q;

		data_p = skb_push(pkt, LENGTH_802_3+VLAN_Size);

		VLAN_8023_Header_Copy(VLAN_VID, VLAN_Priority,
								pHeader802_3, LENGTH_802_3,
								data_p, FromWhichBSSID, TPID);
	}
#endif /* CONFIG_AP_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
	RT_CONFIG_IF_OPMODE_ON_STA(OpMode)
		NdisMoveMemory(skb_push(pkt, LENGTH_802_3), pHeader802_3, LENGTH_802_3);
#endif /* CONFIG_STA_SUPPORT */
}

static VOID RTMP_NetPktInput(
	IN PNDIS_PACKET pPacket)
{
	PRTMP_ADAPTER       pAd = NULL;
    PNET_DEV            pNetDev = NULL;
    PECOS_PKT_BUFFER    pBuffer = NULL;
	struct ifnet        *ifp = NULL;
    struct mbuf         *pMBuf = NULL;
    struct ether_header *eh = NULL;
 
	pNetDev = GET_OS_PKT_NETDEV(pPacket);
    if (GET_OS_PKT_TOTAL_LEN(pPacket) < LENGTH_802_3) {
        DBGPRINT(RT_DEBUG_ERROR, ("%s: packet size %lu < LENGTH_802_3\n", __FUNCTION__, GET_OS_PKT_TOTAL_LEN(pPacket)));
        return;
    }

	pAd = (PRTMP_ADAPTER)GET_OS_PKT_NETDEV(pPacket)->driver_private;
	ifp = &pNetDev->sc_arpcom.ac_if;
    pBuffer = (PECOS_PKT_BUFFER) pPacket;

    pMBuf = pBuffer->pDataMBuf;
    ifp->if_ipackets++;
    pMBuf->m_pkthdr.rcvif = ifp;
        pMBuf->m_data = pBuffer->pDataPtr;
    eh = (struct ether_hdr *) pMBuf->m_data;
    pMBuf->m_data += sizeof(struct ether_header);
    pMBuf->m_pkthdr.len = pBuffer->pktLen - sizeof(struct ether_header);
    pMBuf->m_len = pMBuf->m_pkthdr.len;

    /* Push data into protocol stacks */
    ether_input(ifp, eh, pMBuf);
	MEM_DBG_PKT_FREE_INC(pAd);
    pBuffer->pDataMBuf = NULL;
    RTMPFreeNdisPacket(pAd, pPacket);
}
 
void announce_802_3_packet(
        IN VOID *pAdSrc,
        IN PNDIS_PACKET	pPacket,
        IN UCHAR OpMode)
{
	PRTMP_ADAPTER	pAd = (PRTMP_ADAPTER)pAdSrc;

	pAd = pAd; /* avoid compile warning */

#ifdef CONFIG_AP_SUPPORT
#ifdef APCLI_SUPPORT
	PNET_DEV		pNetDev = GET_OS_PKT_NETDEV(pPacket);

	IF_DEV_CONFIG_OPMODE_ON_AP(pAd)
	{
		if (MATPktRxNeedConvert(pAd, pNetDev))
			MATEngineRxHandle(pAd, pPacket, 0);
	}
#endif /* APCLI_SUPPORT */
#endif /* CONFIG_AP_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
#ifdef ETH_CONVERT_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	{
		if (pAd->EthConvert.ECMode & ETH_CONVERT_MODE_DONGLE)
			MATEngineRxHandle(pAd, pPacket, 0);
	}
#endif /* ETH_CONVERT_SUPPORT */
#endif /* CONFIG_STA_SUPPORT */

	RTMP_NetPktInput(pPacket);
}


VOID IAPP_L2_UpdatePostCtrl(
	IN PRTMP_ADAPTER	pAd,
    IN UINT8 *mac_p,
    IN INT  bssid)
{
#ifdef CONFIG_BRIDGE
	PNET_DEV pNetDev = get_netdev_from_bssid(pAd, bssid);
	struct bridge_softc *sc;
	struct ifnet        *ifp = NULL;
	struct ether_addr   ea;
 
   	ifp = &pNetDev->sc_arpcom.ac_if;
   	if ((ifp != NULL) && (ifp->if_bridge))
    {
        sc = (struct bridge_softc *)ifp->if_bridge; 
        memcpy(&ea, mac_p, MAC_ADDR_LEN);
        bridge_rtdaddr(sc, &ea);
    }
#endif
}


#ifdef CONFIG_AP_SUPPORT
#ifdef DOT1X_SUPPORT
/*
 ========================================================================
 Routine Description:
    Send Leyer 2 Frame to notify 802.1x daemon. This is a internal command

 Arguments:

 Return Value:
    TRUE - send successfully
    FAIL - send fail

 Note:
 ========================================================================
*/
BOOLEAN Dot1xInternalCmdAction(
    IN  PRTMP_ADAPTER	pAd,
    IN  MAC_TABLE_ENTRY *pEntry,
    IN	UINT8			cmd,
	IN	UINT8			*EAPOL) /* OS_ABL_SUPPORT */
{
	INT				apidx = MAIN_MBSSID;
	UCHAR 			Header802_3[14];
	UCHAR 			RalinkIe[9] = {221, 7, 0x00, 0x0c, 0x43, 0x00, 0x00, 0x00, 0x00};
	UCHAR			s_addr[MAC_ADDR_LEN];
    PNDIS_PACKET	pPacket;
    NDIS_STATUS  	Status = NDIS_STATUS_SUCCESS;
	
	INT size = sizeof(Header802_3) + sizeof(RalinkIe);

	DBGPRINT(RT_DEBUG_OFF, ("%s\n", __FUNCTION__));
    Status = RTMPAllocateNdisPacket(pAd, &pPacket, NULL, 0, NULL, size+2);
    if (Status != NDIS_STATUS_SUCCESS)
    {
        DBGPRINT(RT_DEBUG_ERROR, ("%s (error:: can't allocate NDIS PACKET)\n", __FUNCTION__));
        return FALSE;
    }
	
	if (pEntry)
	{
		apidx = pEntry->apidx;
		NdisMoveMemory(s_addr, pEntry->Addr, MAC_ADDR_LEN);
	}
	else
	{
		/* Fake a Source Address for transmission */
		NdisMoveMemory(s_addr, pAd->ApCfg.MBSSID[apidx].Bssid, MAC_ADDR_LENGTH);
		s_addr[0] |= 0x80;
	}

	MAKE_802_3_HEADER(Header802_3, 
					  pAd->ApCfg.MBSSID[apidx].Bssid, 
					  s_addr, EAPOL);
	
	SET_OS_PKT_NETDEV(pPacket, get_netdev_from_bssid(pAd, apidx));

	skb_reserve(GET_OS_PKT_TYPE(pPacket), 2);	/* 16 byte align the IP header */
	NdisMoveMemory(GET_OS_PKT_DATAPTR(pPacket), Header802_3, LENGTH_802_3);

	/* Prepare internal command */
	RalinkIe[5] = cmd;
	NdisMoveMemory(GET_OS_PKT_DATAPTR(pPacket) + LENGTH_802_3, RalinkIe, sizeof(RalinkIe));

	skb_put(GET_OS_PKT_TYPE(pPacket), size);

	DBGPRINT(RT_DEBUG_TRACE, ("%s : cmd(%d)\n", __FUNCTION__, cmd));

	announce_802_3_packet(pAd, pPacket, OPMODE_AP);

	return TRUE;
}

/*
 ========================================================================
 Routine Description:
    Send Leyer 2 Frame to trigger 802.1x EAP state machine.

 Arguments:

 Return Value:
    TRUE - send successfully
    FAIL - send fail

 Note:
 ========================================================================
*/
BOOLEAN Dot1xEapTriggerAction(
    IN  PRTMP_ADAPTER	pAd,
    IN  MAC_TABLE_ENTRY *pEntry,
	IN	UINT8			*EAPOL) /* OS_ABL_SUPPORT */
{
	INT				apidx = MAIN_MBSSID;
	UCHAR 			Header802_3[14];
	UCHAR 			eapol_start_1x_hdr[4] = {0x01, 0x01, 0x00, 0x00};

    if((pEntry->AuthMode == Ndis802_11AuthModeWPA) || (pEntry->AuthMode == Ndis802_11AuthModeWPA2) || (pAd->ApCfg.MBSSID[apidx].IEEE8021X == TRUE))
	{
        PNDIS_PACKET	pPacket;
        NDIS_STATUS  	Status = NDIS_STATUS_SUCCESS;
        INT size = sizeof(Header802_3) + sizeof(eapol_start_1x_hdr);

        Status = RTMPAllocateNdisPacket(pAd, &pPacket, NULL, 0, NULL, size+2);
        if (Status != NDIS_STATUS_SUCCESS)
        {
            DBGPRINT(RT_DEBUG_ERROR, ("%s (error:: can't allocate NDIS PACKET)\n", __FUNCTION__));
            return FALSE;
        }

		apidx = pEntry->apidx;
		MAKE_802_3_HEADER(Header802_3, pAd->ApCfg.MBSSID[apidx].Bssid, pEntry->Addr, EAPOL);

		MEM_DBG_PKT_ALLOC_INC(pAd);
	   	GET_OS_PKT_NETDEV(pPacket) = get_netdev_from_bssid(pAd, apidx);

		skb_reserve(GET_OS_PKT_TYPE(pPacket), 2);	/* 16 byte align the IP header */
		NdisMoveMemory(GET_OS_PKT_DATAPTR(pPacket), Header802_3, LENGTH_802_3);
		NdisMoveMemory(GET_OS_PKT_DATAPTR(pPacket) + LENGTH_802_3, eapol_start_1x_hdr, sizeof(eapol_start_1x_hdr));

 		skb_put(GET_OS_PKT_TYPE(pPacket), size);

		DBGPRINT(RT_DEBUG_TRACE, ("Notify 8021.x daemon to trigger EAP-SM for this sta(%02x:%02x:%02x:%02x:%02x:%02x)\n", PRINT_MAC(pEntry->Addr)));

	    announce_802_3_packet(pAd, pPacket, OPMODE_AP);

	}

	return TRUE;
}
#endif /* DOT1X_SUPPORT */
#endif /* CONFIG_AP_SUPPORT */


#ifdef SYSTEM_LOG_SUPPORT
/* for wireless system event message */
char const *pWirelessSysEventText[IW_SYS_EVENT_TYPE_NUM] = {    
	/* system status event */
    "had associated successfully",							/* IW_ASSOC_EVENT_FLAG */
    "had disassociated",									/* IW_DISASSOC_EVENT_FLAG */
    "had deauthenticated",									/* IW_DEAUTH_EVENT_FLAG */
    "had been aged-out and disassociated",					/* IW_AGEOUT_EVENT_FLAG */
    "occurred CounterMeasures attack",						/* IW_COUNTER_MEASURES_EVENT_FLAG */	
    "occurred replay counter different in Key Handshaking",	/* IW_REPLAY_COUNTER_DIFF_EVENT_FLAG */
    "occurred RSNIE different in Key Handshaking",			/* IW_RSNIE_DIFF_EVENT_FLAG */
    "occurred MIC different in Key Handshaking",			/* IW_MIC_DIFF_EVENT_FLAG */
    "occurred ICV error in RX",								/* IW_ICV_ERROR_EVENT_FLAG */
    "occurred MIC error in RX",								/* IW_MIC_ERROR_EVENT_FLAG */
	"Group Key Handshaking timeout",						/* IW_GROUP_HS_TIMEOUT_EVENT_FLAG */ 
	"Pairwise Key Handshaking timeout",						/* IW_PAIRWISE_HS_TIMEOUT_EVENT_FLAG */ 
	"RSN IE sanity check failure",							/* IW_RSNIE_SANITY_FAIL_EVENT_FLAG */ 
	"set key done in WPA/WPAPSK",							/* IW_SET_KEY_DONE_WPA1_EVENT_FLAG */ 
	"set key done in WPA2/WPA2PSK",                         /* IW_SET_KEY_DONE_WPA2_EVENT_FLAG */ 
	"connects with our wireless client",                    /* IW_STA_LINKUP_EVENT_FLAG */ 
	"disconnects with our wireless client",                 /* IW_STA_LINKDOWN_EVENT_FLAG */
	"scan completed",										/* IW_SCAN_COMPLETED_EVENT_FLAG */
	"scan terminate!! Busy!! Enqueue fail!!",				/* IW_SCAN_ENQUEUE_FAIL_EVENT_FLAG */
	"channel switch to ",									/* IW_CHANNEL_CHANGE_EVENT_FLAG */
	"wireless mode is not support",							/* IW_STA_MODE_EVENT_FLAG */
	"blacklisted in MAC filter list",						/* IW_MAC_FILTER_LIST_EVENT_FLAG */
	"Authentication rejected because of challenge failure",	/* IW_AUTH_REJECT_CHALLENGE_FAILURE */
	"Scanning",												/* IW_SCANNING_EVENT_FLAG */
	"Start a new IBSS",										/* IW_START_IBSS_FLAG */
	"Join the IBSS",										/* IW_JOIN_IBSS_FLAG */
	};

#ifdef IDS_SUPPORT
/* for wireless IDS_spoof_attack event message */
char const *pWirelessSpoofEventText[IW_SPOOF_EVENT_TYPE_NUM] = {   	
    "detected conflict SSID",								/* IW_CONFLICT_SSID_EVENT_FLAG */
    "detected spoofed association response",				/* IW_SPOOF_ASSOC_RESP_EVENT_FLAG */
    "detected spoofed reassociation responses",				/* IW_SPOOF_REASSOC_RESP_EVENT_FLAG */
    "detected spoofed probe response",						/* IW_SPOOF_PROBE_RESP_EVENT_FLAG */
    "detected spoofed beacon",								/* IW_SPOOF_BEACON_EVENT_FLAG */
    "detected spoofed disassociation",						/* IW_SPOOF_DISASSOC_EVENT_FLAG */
    "detected spoofed authentication",						/* IW_SPOOF_AUTH_EVENT_FLAG */
    "detected spoofed deauthentication",					/* IW_SPOOF_DEAUTH_EVENT_FLAG */
    "detected spoofed unknown management frame",			/* IW_SPOOF_UNKNOWN_MGMT_EVENT_FLAG */
	"detected replay attack"								/* IW_REPLAY_ATTACK_EVENT_FLAG */	
	};

/* for wireless IDS_flooding_attack event message */
char const *pWirelessFloodEventText[IW_FLOOD_EVENT_TYPE_NUM] = {   	
	"detected authentication flooding",						/* IW_FLOOD_AUTH_EVENT_FLAG */
    "detected association request flooding",				/* IW_FLOOD_ASSOC_REQ_EVENT_FLAG */
    "detected reassociation request flooding",				/* IW_FLOOD_REASSOC_REQ_EVENT_FLAG */
    "detected probe request flooding",						/* IW_FLOOD_PROBE_REQ_EVENT_FLAG */
    "detected disassociation flooding",						/* IW_FLOOD_DISASSOC_EVENT_FLAG */
    "detected deauthentication flooding",					/* IW_FLOOD_DEAUTH_EVENT_FLAG */
    "detected 802.1x eap-request flooding"					/* IW_FLOOD_EAP_REQ_EVENT_FLAG */	
	};
#endif /* IDS_SUPPORT */

#ifdef WSC_INCLUDED
/* for WSC wireless event message */
char const *pWirelessWscEventText[IW_WSC_EVENT_TYPE_NUM] = {   	
	"PBC Session Overlap",									/* IW_WSC_PBC_SESSION_OVERLAP */
	"This WPS Registrar supports PBC",						/* IW_WSC_REGISTRAR_SUPPORT_PBC */
	"This WPS Registrar supports PIN",						/* IW_WSC_REGISTRAR_SUPPORT_PIN */
	"WPS status success",									/* IW_WSC_STATUS_SUCCESS */
	"WPS status fail",										/* IW_WSC_STATUS_FAIL */
	"WPS 2 mins time out!",									/* IW_WSC_2MINS_TIMEOUT */
	"WPS Send EAPOL_Start!",								/* IW_WSC_SEND_EAPOL_START */
	"WPS Send WscStart!",									/* IW_WSC_SEND_WSC_START */
	"WPS Send M1!",											/* IW_WSC_SEND_M1 */
	"WPS Send M2!",											/* IW_WSC_SEND_M2 */
	"WPS Send M3!",											/* IW_WSC_SEND_M3 */
	"WPS Send M4!",											/* IW_WSC_SEND_M4 */
	"WPS Send M5!",											/* IW_WSC_SEND_M5 */
	"WPS Send M6!",											/* IW_WSC_SEND_M6 */
	"WPS Send M7!",											/* IW_WSC_SEND_M7 */
	"WPS Send M8!",											/* IW_WSC_SEND_M8 */
	"WPS Send WscDone!",									/* IW_WSC_SEND_DONE */
	"WPS Send WscAck!",										/* IW_WSC_SEND_ACK */
	"WPS Send WscNack!",									/* IW_WSC_SEND_NACK */
	"WPS Receive WscStart!",								/* IW_WSC_RECEIVE_WSC_START */
	"WPS Receive M1!",										/* IW_WSC_RECEIVE_M1 */
	"WPS Receive M2!",										/* IW_WSC_RECEIVE_M2 */
	"WPS Receive M3!",										/* IW_WSC_RECEIVE_M3 */
	"WPS Receive M4!",										/* IW_WSC_RECEIVE_M4 */
	"WPS Receive M5!",										/* IW_WSC_RECEIVE_M5 */
	"WPS Receive M6!",										/* IW_WSC_RECEIVE_M6 */
	"WPS Receive M7!",										/* IW_WSC_RECEIVE_M7 */
	"WPS Receive M8!",										/* IW_WSC_RECEIVE_M8 */
	"WPS Receive WscDone!",									/* IW_WSC_RECEIVE_DONE */
	"WPS Receive WscAck!",									/* IW_WSC_RECEIVE_ACK */
	"WPS Receive WscNack!",									/* IW_WSC_RECEIVE_NACK */
	"Not only one candidate found"							/* IW_WSC_MANY_CANDIDATE */
	};
#endif /* WSC_INCLUDED */
/*
	========================================================================
	
	Routine Description:
		Send log message through wireless event

	========================================================================
*/
VOID RtmpDrvSendWirelessEvent(
	IN	VOID					*pAdSrc,
	IN	USHORT					Event_flag,
	IN	PUCHAR 					pAddr,
	IN  UCHAR					BssIdx,
	IN	CHAR					Rssi)
{
	PRTMP_ADAPTER pAd = (PRTMP_ADAPTER)pAdSrc;
	PSTRING	pBuf = NULL, pBufPtr = NULL;
	USHORT	event, type, BufLen;	
	UCHAR	event_table_len = 0;

	type = Event_flag & 0xFF00;	
	event = Event_flag & 0x00FF;

	switch (type)
	{
		case IW_SYS_EVENT_FLAG_START:
			event_table_len = IW_SYS_EVENT_TYPE_NUM;
			break;
#ifdef IDS_SUPPORT
		case IW_SPOOF_EVENT_FLAG_START:
			event_table_len = IW_SPOOF_EVENT_TYPE_NUM;
			break;

		case IW_FLOOD_EVENT_FLAG_START:
			event_table_len = IW_FLOOD_EVENT_TYPE_NUM;
			break;
#endif /* IDS_SUPPORT */ 			
#ifdef WSC_INCLUDED
		case IW_WSC_EVENT_FLAG_START:
			event_table_len = IW_WSC_EVENT_TYPE_NUM;
			break;
#endif /* WSC_INCLUDED */
	}
	
	if (event_table_len == 0)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("%s : The type(%0x02x) is not valid.\n", __FUNCTION__, type));			       		       		
		return;
	}
	
	if (event >= event_table_len)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("%s : The event(%0x02x) is not valid.\n", __FUNCTION__, event));			       		       		
		return;
	}	
 
	/*Allocate memory and copy the msg. */
	if((pBuf = kmalloc(IW_CUSTOM_MAX_LEN, GFP_ATOMIC)) != NULL)
	{
		/*Prepare the payload */
		memset(pBuf, 0, IW_CUSTOM_MAX_LEN);

		pBufPtr = pBuf;		

		if (pAddr)
			pBufPtr += sprintf(pBufPtr, "STA(%02x:%02x:%02x:%02x:%02x:%02x) ", PRINT_MAC(pAddr));				
		else if (BssIdx < MAX_MBSSID_NUM(pAd))
			pBufPtr += sprintf(pBufPtr, "BSS(ra%d) ", BssIdx);
		else
			pBufPtr += sprintf(pBufPtr, " ");

		if (type == IW_SYS_EVENT_FLAG_START)
        {
			pBufPtr += sprintf(pBufPtr, "%s", pWirelessSysEventText[event]);
		    
            if (Event_flag == IW_CHANNEL_CHANGE_EVENT_FLAG)
		  	{
			 	pBufPtr += sprintf(pBufPtr, "%3d", Rssi);
			}			
		}
#ifdef IDS_SUPPORT		
		else if (type == IW_SPOOF_EVENT_FLAG_START)
			pBufPtr += sprintf(pBufPtr, "%s (RSSI=%d)", pWirelessSpoofEventText[event], Rssi);
		else if (type == IW_FLOOD_EVENT_FLAG_START)
			pBufPtr += sprintf(pBufPtr, "%s", pWirelessFloodEventText[event]);
#endif /* IDS_SUPPORT */		
#ifdef WSC_INCLUDED
		else if (type == IW_WSC_EVENT_FLAG_START)
			pBufPtr += sprintf(pBufPtr, "%s", pWirelessWscEventText[event]);
#endif /* WSC_INCLUDED */
		else
			pBufPtr += sprintf(pBufPtr, "%s", "unknown event");
		
		pBufPtr[pBufPtr - pBuf] = '\0';
		BufLen = pBufPtr - pBuf;
		
		RtmpOSWrielessEventSend(pAd->net_dev, IWEVCUSTOM, Event_flag, NULL, (PUCHAR)pBuf, BufLen);
		/*DBGPRINT(RT_DEBUG_TRACE, ("%s : %s\n", __FUNCTION__, pBuf)); */
	
		kfree(pBuf);
	}
	else
		DBGPRINT(RT_DEBUG_ERROR, ("%s : Can't allocate memory for wireless event.\n", __FUNCTION__));			       		       				
}
#endif /* SYSTEM_LOG_SUPPORT */

static UINT32 RtmpOSWirelessEventTranslate(
	IN UINT32		eventType)
{
	switch(eventType)
	{
		case RT_WLAN_EVENT_CUSTOM:
		case IWEVCUSTOM:
			eventType = IWEVCUSTOM;
			break;

		default:
			printk("Unknown event: %x\n", eventType);
			break;
	}

	return eventType;
}

int RtmpOSWrielessEventSend(
	IN PNET_DEV		pNetDev,
	IN UINT32		eventType,
	IN INT			flags,
	IN PUCHAR		pSrcMac,
	IN PUCHAR		pData,
	IN UINT32		dataLen)
{
	RTMP_ADAPTER *pAd = pNetDev->driver_private;

	/* translate event type */
	eventType = RtmpOSWirelessEventTranslate(eventType);

#ifdef BRANCH_ADV
        if ((pData!= NULL) 
                && (dataLen > 0) 
                && (flags != RT_WSC_UPNP_EVENT_FLAG)) {
	        SysLog(LOG_USER|LOG_INFO|LOGM_WLAN, pData);	
        }
#endif /* BRANCH_ADV */
    
	if (eventType == IWEVCUSTOM)
	{
		POS_COOKIE  pObj;
		pObj = (POS_COOKIE)pAd->OS_Cookie;
		switch(flags)
		{
#ifdef WSC_AP_SUPPORT
			case RT_WSC_UPNP_EVENT_FLAG:
				if (pObj->WscMsgCallBack)
				{
					DBGPRINT(RT_DEBUG_WARN, ("%s(RT_WSC_UPNP_EVENT_FLAG)\n", __FUNCTION__));
					pObj->WscMsgCallBack(pData, dataLen);
				}
				break;
#endif /* WSC_AP_SUPPORT */
			default:
				break;
		}
	}
	return 0;
}

void RTMP_IndicateMediaState(	
	IN	PRTMP_ADAPTER		pAd,
	IN  NDIS_MEDIA_STATE	media_state)
{


}

extern INT wscNLSockRecv(char *pData, UINT32 dataLen);

/*EddyTODO */
/*
  *	Assign the network dev name for created Ralink WiFi interface.
  */
static int RtmpOSNetDevRequestName(
	IN RTMP_ADAPTER *pAd, 
	IN PSTRING pPrefixStr, 
	IN INT	devIdx,
	OUT INT	*avilNum)
{
    DBGPRINT(RT_DEBUG_ERROR, ("%s: Eddy Notice\n", __FUNCTION__));
    return 0;
}


void RtmpOSNetDevClose(
	IN PNET_DEV pNetDev)
{
}


void RtmpOSNetDevFree(PNET_DEV pNetDev)
{
}

int RtmpOSNetDevAddrSet(
	IN UCHAR					OpMode,
	IN PNET_DEV 				pNetDev,
	IN PUCHAR					pMacAddr,
	IN PUCHAR					dev_name)
{
    if (NULL != pMacAddr)
        bcopy(pMacAddr, &pNetDev->sc_arpcom.ac_enaddr, MAC_ADDR_LEN);

	return 0;
}

/*EddyTODO */
void RtmpOSNetDevDetach(
	IN PNET_DEV pNetDev)
{
    DBGPRINT(RT_DEBUG_ERROR, ("%s: Eddy Notice\n", __FUNCTION__));
}

int RtmpOSNetDevAttach(
	IN UCHAR					OpMode,
	IN PNET_DEV					pNetDev, 
	IN RTMP_OS_NETDEV_OP_HOOK	*pDevOpHook)
{
	RtmpOSNetDevAddrSet(OpMode, pNetDev, &pDevOpHook->devAddr[0], NULL);
	return NDIS_STATUS_SUCCESS;
}


VOID	RTMPFreeAdapter(
	IN	VOID		*pAdSrc)
{
	PRTMP_ADAPTER pAd = (PRTMP_ADAPTER)pAdSrc;
	POS_COOKIE os_cookie;
	
	os_cookie=(POS_COOKIE)pAd->OS_Cookie;
	kfree(pAd);
	kfree(os_cookie);
}


/*
	VxWorks sepecific functions for creations of EndDevice and realted procedures.
*/
int RtmpENDDevInitStrParse(char *initString, RTMP_VX_INIT_STRING *pInitToken)
{
	int count = 0;
	char     *tok, *pPtr = NULL; 
	int 		*pTokenValue = NULL;
	

	/*
		initString format:
			phyNum:devNum:infType:irqNum:devType:privSize:devName
	*/
	tok = strtok_r(initString, ":", &pPtr);
	pTokenValue = (int *)pInitToken;
	while(tok)
	{
		printf("tok=%s! count=%d!\n", tok, count);
		if (count == 7)
			memcpy(pInitToken->devName, tok, strlen(tok));
		else
			*(pTokenValue + count) = atoi(tok);
		tok = strtok_r (NULL, ":", &pPtr);
		count++;
	}

	printf("count=%d!\n", count);
	if (count != 8)
		return NDIS_STATUS_FAILURE;

	printf("The initString info:\n");
	printf("\tphyNum=%d!\n", pInitToken->phyNum);
	printf("\tdevNum=%d!\n", pInitToken->devNum);
	printf("\tinfType=%d!\n", pInitToken->infType);
	printf("\tirqNum=%d!\n", pInitToken->irqNum);
	printf("\tdevType=%d!\n", pInitToken->devType);
	printf("\tprivSize=%d!\n", pInitToken->privSize);
	printf("\tcsrAddr=0x%x!\n", pInitToken->csrAddr);
	printf("\tdevName=%s!\n", pInitToken->devName);
	
	return NDIS_STATUS_SUCCESS;
}

#define END_OBJ VOID    
END_OBJ *RtmpVirtualENDDevCreate(
	IN char *initString, 
	IN void *pBSP)
{
    DBGPRINT(RT_DEBUG_ERROR, ("%s: Eddy Notice\n", __FUNCTION__));
    return NULL;
}


#ifdef MESH_SUPPORT
END_OBJ *RtmpMeshENDDevLoad(
	IN char *initString, 
	IN void *pBSP)
{

	ASSERT(initString);
	
	/*  First pass, we just return the device name for function "muxDevLoad()" to check if the device exists */
	if (initString[0] == '\0') {
		bcopy(INF_MESH_DEV_NAME, initString, strlen(INF_MESH_DEV_NAME));
		printf("%s():Into phase 1, return initSting=%s!\n", __FUNCTION__, initString);
		return NULL;
	}

	/*   Now we are phase 2, now do END_OBJ related initialization */
	return RtmpVirtualENDDevCreate(initString, pBSP);
	
}
#endif /* MESH_SUPPORT */


#ifdef CONFIG_AP_SUPPORT
#ifdef APCLI_SUPPORT
END_OBJ *RtmpApCliENDDevLoad(
	IN char *initString, 
	IN void *pBSP)
{

	ASSERT(initString);
	
	/*  First pass, we just return the device name for function "muxDevLoad()" to check if the device exists */
	if (initString[0] == '\0') {
		bcopy(INF_APCLI_DEV_NAME, initString, strlen(INF_APCLI_DEV_NAME));
		printf("%s():Into phase 1, return initSting=%s!\n", __FUNCTION__, initString);
		return NULL;
	}

	/*   Now we are phase 2, now do END_OBJ related initialization */
	return RtmpVirtualENDDevCreate(initString, pBSP);
}
#endif /* APCLI_SUPPORT */


#ifdef WDS_SUPPORT
END_OBJ *RtmpWDSENDDevLoad(
	IN char *initString, 
	IN void *pBSP)
{
	ASSERT(initString);
	
	/*  First pass, we just return the device name for function "muxDevLoad()" to check if the device exists */
	if (initString[0] == '\0') {
		bcopy(INF_WDS_DEV_NAME, initString, strlen(INF_WDS_DEV_NAME));
		printf("%s():Into phase 1, return initSting=%s!\n", __FUNCTION__, initString);
		return NULL;
	}

	/*   Now we are phase 2, now do END_OBJ related initialization */
	return RtmpVirtualENDDevCreate(initString, pBSP);
}
#endif /* WDS_SUPPORT */


#ifdef MBSS_SUPPORT
END_OBJ *RtmpMBSSENDDevLoad(
	IN char *pInitString, 
	IN void *pBSP)
{	
	ASSERT(pInitString);
	
	/*  First pass, we just return the device name for function "muxDevLoad()" to check if the device exists */
	if (pInitString[0] == '\0') {
		bcopy(INF_MAIN_DEV_NAME, pInitString, strlen(INF_MAIN_DEV_NAME));
		DBGPRINT(RT_DEBUG_TRACE, ("%s():Into phase 1, return pInitString=%s!\n", __FUNCTION__, pInitString));
		return NULL;
	}

	/*   Now we are phase 2, now do END_OBJ related initialization */
	return RtmpVirtualENDDevCreate(pInitString, pBSP);
}
#endif /* MBSS_SUPPORT */
#endif /* CONFIG_AP_SUPPORT */


PNET_DEV RtmpOSNetDevCreate(
	IN INT32					MC_RowID,
	IN UINT32					*pIoctlIF,
	IN INT 						devType,
	IN INT						devNum,
	IN INT						privMemSize,
	IN PSTRING					pNamePrefix)
{
    cyg_netdevtab_entry_t *pNetdevEntry;
    struct eth_drv_sc *sc;
	char				devName[IFNAMSIZ];

    sprintf(devName, "%s%d", pNamePrefix, devNum);
    for (pNetdevEntry = &__NETDEVTAB__[0]; pNetdevEntry != &__NETDEVTAB_END__; pNetdevEntry++)
    {
        sc = (struct eth_drv_sc *)pNetdevEntry->device_instance;
        if (strcmp(sc->dev_name, devName) == 0)
            return sc;
	}
		return NULL;
}

PNET_DEV get_netdev_from_bssid(
	IN	PRTMP_ADAPTER	pAd,
	IN	UCHAR			FromWhichBSSID)
{
	PNET_DEV dev_p = NULL;
	
#ifdef MESH_SUPPORT
	if(FromWhichBSSID >= MIN_NET_DEVICE_FOR_MESH)
	{
		dev_p = pAd->MeshTab.dev;
	} 
	else
#endif /* MESH_SUPPORT */
#ifdef CONFIG_AP_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_AP(pAd)
	{
		UCHAR infRealIdx;

		infRealIdx = FromWhichBSSID & (NET_DEVICE_REAL_IDX_MASK);
#ifdef APCLI_SUPPORT
		if(FromWhichBSSID >= MIN_NET_DEVICE_FOR_APCLI)
		{
			dev_p = (infRealIdx > MAX_APCLI_NUM ? NULL : pAd->ApCfg.ApCliTab[infRealIdx].dev);
		} 
		else
#endif /* APCLI_SUPPORT */
#ifdef WDS_SUPPORT
		if(FromWhichBSSID >= MIN_NET_DEVICE_FOR_WDS)
		{
			dev_p = ((infRealIdx > MAX_WDS_ENTRY) ? NULL : pAd->WdsTab.WdsEntry[infRealIdx].dev);
		}
		else
#endif /* WDS_SUPPORT */
		{
			if (FromWhichBSSID >= pAd->ApCfg.BssidNum)
	    		{
				DBGPRINT(RT_DEBUG_ERROR, ("%s: fatal error ssid > ssid num!\n", __FUNCTION__));
				dev_p = pAd->net_dev;
	    		}

	    		if (FromWhichBSSID == BSS0)
				dev_p = pAd->net_dev;
	    		else
	    		{
	    	    		dev_p = pAd->ApCfg.MBSSID[FromWhichBSSID].MSSIDDev;
	    		}
		}
	}
#endif /* CONFIG_AP_SUPPORT */

#ifdef CONFIG_STA_SUPPORT
	IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
	{
		dev_p = pAd->net_dev;
	}
#endif /* CONFIG_STA_SUPPORT */

	ASSERT(dev_p);
	return dev_p; /* return one of MBSS */    
}

#ifdef CONFIG_AP_SUPPORT
UCHAR VLAN_8023_Header_Copy(
	IN	USHORT					VLAN_VID,
	IN	USHORT					VLAN_Priority,
	IN	PUCHAR					pHeader802_3,
	IN	UINT            		HdrLen,
	OUT PUCHAR					pData,
	IN	UCHAR					FromWhichBSSID,
	IN	UCHAR					*TPID)
{
	UINT16 TCI;
	UCHAR VLAN_Size = 0;


	if (VLAN_VID != 0)
	{
		/* need to insert VLAN tag */
		VLAN_Size = LENGTH_802_1Q;

		/* make up TCI field */
		TCI = (VLAN_VID & 0x0fff) | ((VLAN_Priority & 0x7)<<13);

#ifndef RT_BIG_ENDIAN
		TCI = SWAP16(TCI);
#endif /* RT_BIG_ENDIAN */

		/* copy dst + src MAC (12B) */
		memcpy(pData, pHeader802_3, LENGTH_802_3_NO_TYPE);

		/* copy VLAN tag (4B) */
		/* do NOT use memcpy to speed up */
		*(UINT16 *)(pData+LENGTH_802_3_NO_TYPE) = *(UINT16 *)TPID;
		*(UINT16 *)(pData+LENGTH_802_3_NO_TYPE+2) = TCI;

		/* copy type/len (2B) */
		*(UINT16 *)(pData+LENGTH_802_3_NO_TYPE+LENGTH_802_1Q) = \
				*(UINT16 *)&pHeader802_3[LENGTH_802_3-LENGTH_802_3_TYPE];

		/* copy tail if exist */
		if (HdrLen > LENGTH_802_3)
		{
			memcpy(pData+LENGTH_802_3+LENGTH_802_1Q,
					pHeader802_3+LENGTH_802_3,
					HdrLen - LENGTH_802_3);
		}
	}
	else
	{
		/* no VLAN tag is needed to insert */
		memcpy(pData, pHeader802_3, HdrLen);
	}

	return VLAN_Size;
}
#endif /* CONFIG_AP_SUPPORT */


#ifdef IAPP_SUPPORT
/* Layer 2 Update frame to switch/bridge */
/* For any Layer2 devices, e.g., bridges, switches and other APs, the frame
   can update their forwarding tables with the correct port to reach the new
   location of the STA */
typedef struct GNU_PACKED _RT_IAPP_L2_UPDATE_FRAME {

    UCHAR   DA[ETH_ALEN]; /* broadcast MAC address */
    UCHAR   SA[ETH_ALEN]; /* the MAC address of the STA that has just associated or reassociated */
    USHORT  Len;          /* 8 octets */
    UCHAR   DSAP;         /* null */
    UCHAR   SSAP;         /* null */
    UCHAR   Control;      /* reference to IEEE Std 802.2 */
    UCHAR   XIDInfo[3];   /* reference to IEEE Std 802.2 */
} RT_IAPP_L2_UPDATE_FRAME, *PRT_IAPP_L2_UPDATE_FRAME;

PNDIS_PACKET RtmpOsPktIappMakeUp(
	IN	PNET_DEV				pNetDev,
	IN	UINT8					*pMac)
{
	RTMP_ADAPTER *pAd = pNetDev->driver_private;
	RT_IAPP_L2_UPDATE_FRAME  frame_body;
	INT size = sizeof(RT_IAPP_L2_UPDATE_FRAME);
	PNDIS_PACKET	pNetBuf;


	pNetBuf = RtmpOSNetPktAlloc(pAd, size);
	if (!pNetBuf)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("Error! Can't allocate a skb.\n"));
		return NULL;
	}
	
	/* init the update frame body */
	NdisZeroMemory(&frame_body, size);

	memset(frame_body.DA, 0xFF, ETH_ALEN);
	memcpy(frame_body.SA, pMac, ETH_ALEN);

	frame_body.Len      = OS_HTONS(ETH_ALEN);
	frame_body.DSAP     = 0;
	frame_body.SSAP     = 0x01;
	frame_body.Control  = 0xAF;

	frame_body.XIDInfo[0] = 0x81;
	frame_body.XIDInfo[1] = 1;
	frame_body.XIDInfo[2] = 1 << 1;

	SET_OS_PKT_NETDEV(pNetBuf, pNetDev);
    skb_reserve(pNetBuf, 2);
    memcpy(skb_put(pNetBuf, size), &frame_body, size);
	return pNetBuf;
}
#endif /* IAPP_SUPPORT */


VOID RtmpOsPktInit(
	IN	PNDIS_PACKET		pNetPkt,
	IN	PNET_DEV			pNetDev,
	IN	UCHAR				*pData,
	IN	USHORT				DataSize)
{
	PNDIS_PACKET	pRxPkt;


	pRxPkt = RTPKT_TO_OSPKT(pNetPkt);

	SET_OS_PKT_NETDEV(pRxPkt, pNetDev);
	SET_OS_PKT_DATAPTR(pRxPkt, pData);
	SET_OS_PKT_LEN(pRxPkt, DataSize);
	SET_OS_PKT_DATATAIL(pRxPkt, pData, DataSize);
}

VOID RtmpUtilInit(VOID)
{
}


BOOLEAN RtmpOsStatsAlloc(
	IN	VOID					**ppStats,
	IN	VOID					**ppIwStats)
{
	return TRUE;
}


BOOLEAN RtmpOSTaskWait(
	IN	VOID					*pReserved,
	IN	RTMP_OS_TASK			*pTaskOrg,
	IN	INT32					*pStatus)
{
	RTMP_SEM_EVENT_WAIT(&(pTaskOrg->taskSema), *pStatus);
	if (*pStatus == 0)
		return TRUE;
	return FALSE;
}


BOOLEAN RTMPL2FrameTxAction(
	IN  VOID				*pCtrlBkPtr,
	IN	PNET_DEV			pNetDev,
	IN	RTMP_CB_8023_PACKET_ANNOUNCE _announce_802_3_packet,
	IN	UCHAR				apidx,
	IN	PUCHAR				pData,
	IN	UINT32				data_len,
	IN	UCHAR			OpMode)
{
	PNDIS_PACKET	pPacket;
	NDIS_STATUS  	Status = NDIS_STATUS_SUCCESS;

	Status = RTMPAllocateNdisPacket(pCtrlBkPtr, &pPacket, NULL, 0, NULL, data_len+2);
	if (Status != NDIS_STATUS_SUCCESS)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("%s (error:: can't allocate NDIS PACKET)\n", __FUNCTION__));
		return FALSE;
	}

	MEM_DBG_PKT_ALLOC_INC(pAd);
   	SET_OS_PKT_NETDEV(pPacket, pNetDev); /*get_netdev_from_bssid(pAd, apidx)); */

	skb_reserve(GET_OS_PKT_TYPE(pPacket), 2);	/* 16 byte align the IP header */
	NdisMoveMemory(GET_OS_PKT_DATAPTR(pPacket), pData, data_len);

	skb_put(GET_OS_PKT_TYPE(pPacket), data_len);

/*	DBGPRINT(RT_DEBUG_TRACE, ("Notify 8021.x daemon to trigger EAP-SM for this sta(%02x:%02x:%02x:%02x:%02x:%02x)\n", PRINT_MAC(pEntry->Addr))); */

	_announce_802_3_packet(pCtrlBkPtr, pPacket, OpMode);
	return TRUE;
}

INT RTMP_AP_IoctlPrepare(
	IN	RTMP_ADAPTER			*pAd,
	IN	VOID					*pCB)
{
	return 0;
}

VOID RtmpOsTaskPidInit(
	IN	RTMP_OS_PID				*pPid)
{
	*pPid = THREAD_PID_INIT_VALUE;
}

VOID RtmpOsTaskWakeUp(
	IN	RTMP_OS_TASK			*pTask)
{
#ifdef KTHREAD_SUPPORT
	WAKE_UP(pTask);
#else
	RTMP_SEM_EVENT_UP(&pTask->taskSema);
#endif
}

VOID RtmpOsSendWirelessEvent(
	IN	VOID			*pAd,
	IN	USHORT			Event_flag,
	IN	PUCHAR 			pAddr,
	IN	UCHAR			BssIdx,
	IN	CHAR			Rssi,
	IN	RTMP_OS_SEND_WLAN_EVENT		pFunc)
{
	pFunc(pAd, Event_flag, pAddr, BssIdx, Rssi);
}


/*
========================================================================
Routine Description:
	Enable or disable wireless event sent.

Arguments:
	pReserved		- Reserved
	FlgIsWEntSup	- TRUE or FALSE

Return Value:
	None

Note:
========================================================================
*/
VOID RtmpOsWlanEventSet(
	IN	VOID					*pReserved,
	IN	BOOLEAN					*pCfgWEnt,
	IN	BOOLEAN					FlgIsWEntSup)
{
	*pCfgWEnt = FlgIsWEntSup;
}


#ifdef WDS_SUPPORT
VOID AP_WDS_KeyNameMakeUp(
	IN	STRING						*pKey,
	IN	UINT32						KeyMaxSize,
	IN	INT							KeyId)
{
	sprintf(pKey, "Wds%dKey", KeyId+1);
}


NET_DEV_STATS *RT28xx_get_wds_ether_stats(
    IN PNET_DEV *net_dev)
{
    return NULL;
}
#endif /* WDS_SUPPORT */


#ifdef CONFIG_AP_SUPPORT
VOID AP_E2PROM_IOCTL_PostCtrl(
	IN	RTMP_IOCTL_INPUT_STRUCT	*wrq,
	IN	PSTRING					msg)
{
	DBGPRINT(RT_DEBUG_OFF, ("%s\n", msg));	
}
#endif /* CONFIG_AP_SUPPORT */


/*
========================================================================
Routine Description:
	Wake up the command thread.

Arguments:
	pAd				- WLAN control block pointer

Return Value:
	None

Note:
========================================================================
*/
VOID RtmpOsCmdUp(
	IN RTMP_OS_TASK			*pCmdQTask)
{
#ifdef KTHREAD_SUPPORT
	do{
		OS_TASK	*pTask = RTMP_OS_TASK_GET(pCmdQTask);
		{
			pTask->kthread_running = TRUE;
	        wake_up(&pTask->kthread_q);
		}
	}while(0);
#else
	do{
		OS_TASK	*pTask = RTMP_OS_TASK_GET(pCmdQTask);
		CHECK_PID_LEGALITY(pTask->taskPID)
		{
			RTMP_SEM_EVENT_UP(&(pTask->taskSema));
		}
	}while(0);
#endif /* KTHREAD_SUPPORT */
}
