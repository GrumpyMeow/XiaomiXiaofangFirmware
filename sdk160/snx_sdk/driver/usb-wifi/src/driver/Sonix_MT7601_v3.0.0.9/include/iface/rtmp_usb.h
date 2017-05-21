#ifndef __RTMP_USB_H__
#define __RTMP_USB_H__

#include "rtusb_io.h"

extern UCHAR EpToQueue[6];

#ifdef DPA_T
#define RXBULKAGGRE_SIZE			5
#else /* DPA_T */
#define RXBULKAGGRE_SIZE			12
#endif /* !DPA_T */
#define MAX_TXBULK_LIMIT			(LOCAL_TXBUF_SIZE*(BULKAGGRE_SIZE-1))
#define MAX_TXBULK_SIZE			(LOCAL_TXBUF_SIZE*BULKAGGRE_SIZE)
#define MAX_RXBULK_SIZE			(LOCAL_TXBUF_SIZE*RXBULKAGGRE_SIZE)
#define MAX_MLME_HANDLER_MEMORY 20
#define CMD_RSP_BULK_SIZE	1024

#ifdef USB_BULK_BUF_ALIGMENT
#ifdef CONFIG_MSTARTV_CUS_SUPPORT
#define ALIGMENT_BULKAGGRE_SIZE	4/* org=14,must >=  4*/
#else
#define ALIGMENT_BULKAGGRE_SIZE	14/* must >=  4*/
#endif


#define MAX_ALIGMENT_TXBULK_SIZE			(LOCAL_TXBUF_SIZE*ALIGMENT_BULKAGGRE_SIZE)
//#define BULKOUT_SIZE	0x00006000
#define BULKOUT_SIZE	(LOCAL_TXBUF_SIZE * (ALIGMENT_BULKAGGRE_SIZE -2))

#endif /* USB_BULK_BUF_ALIGMENT */

/*Power saving */
#define PowerWakeCID		3
#define CID0MASK		0x000000ff
#define CID1MASK		0x0000ff00
#define CID2MASK		0x00ff0000
#define CID3MASK		0xff000000


/* Flags for Bulkflags control for bulk out data */
/* */
#define	fRTUSB_BULK_OUT_DATA_NULL			0x00000001
#define	fRTUSB_BULK_OUT_RTS					0x00000002
#define	fRTUSB_BULK_OUT_MLME				0x00000004

#define	fRTUSB_BULK_OUT_PSPOLL				0x00000010
#define	fRTUSB_BULK_OUT_DATA_FRAG			0x00000020
#define	fRTUSB_BULK_OUT_DATA_FRAG_2			0x00000040
#define	fRTUSB_BULK_OUT_DATA_FRAG_3			0x00000080
#define	fRTUSB_BULK_OUT_DATA_FRAG_4			0x00000100

#define	fRTUSB_BULK_OUT_DATA_NORMAL			0x00010000
#define	fRTUSB_BULK_OUT_DATA_NORMAL_2		0x00020000
#define	fRTUSB_BULK_OUT_DATA_NORMAL_3		0x00040000
#define	fRTUSB_BULK_OUT_DATA_NORMAL_4		0x00080000

#define   fRTUSB_BULK_OUT_DATA_HCCA				0x00100000
#define fRTUSB_BULK_OUT_DATA_NULL_HCCA			0x00400000
#define fRTUSB_BULK_OUT_MLME_HCCA				0x00800000


/* TODO:move to ./ate/include/iface/ate_usb.h */
#ifdef RALINK_ATE
#define	fRTUSB_BULK_OUT_DATA_ATE			0x00100000
#endif /* RALINK_ATE */


#define FREE_HTTX_RING(_pCookie, _pipeId, _txContext)			\
{										\
	if ((_txContext)->ENextBulkOutPosition == (_txContext)->CurWritePosition)	\
	{																	\
		(_txContext)->bRingEmpty = TRUE;			\
	}																	\
	/*NdisInterlockedDecrement(&(_p)->TxCount); */\
}

#define NT_SUCCESS(status)			(((status) >=0) ? (TRUE):(FALSE))


#if 0
/* */
/* NdisMCancelTimer just canced the timer and not mean release the timer. */
/* And don't set the "Valid" to False. So that we can use this timer again. */
/* NOTE: now we didn't implement this feature!!! */
/* */
#define NdisMCancelTimer		RTMPCancelTimer
#define PMDL		PVOID
/*#define NdisMSendComplete			RTMP_SendComplete */

#endif

#if 0 /* os abl move to include/iface/iface_util.h */
#define USBD_TRANSFER_DIRECTION_OUT		0
#define USBD_TRANSFER_DIRECTION_IN		0
#define USBD_SHORT_TRANSFER_OK			0
#define PURB			purbb_t
#endif /* 0 */

#define PIRP		PVOID
/*#define NDIS_OID	UINT */
#ifndef USB_ST_NOERROR
#define USB_ST_NOERROR     0
#endif

#ifdef THREADX
#undef  USB_ST_NOERROR
#define USB_ST_NOERROR		DC_URB_COMPLETE
#endif /* THREADX */

/* vendor-specific control operations */
#define CONTROL_TIMEOUT_JIFFIES ( (300 * OS_HZ) / 1000)
/*#define UNLINK_TIMEOUT_MS		3 // os abl move */

#if 0 /* os abl move to include/iface/iface_util.h */
#ifdef KTHREAD_SUPPORT
#define RTUSBMlmeUp(pAd) \
	do{								    \
		RTMP_OS_TASK	*_pTask = &((pAd)->mlmeTask);\
		if (_pTask->kthread_task) \
        { \
			_pTask->kthread_running = TRUE; \
	        wake_up(&_pTask->kthread_q); \
		} \
	}while(0)
#else
#define RTUSBMlmeUp(pAd)	        \
	do{								    \
		RTMP_OS_TASK	*_pTask = &((pAd)->mlmeTask);\
		CHECK_PID_LEGALITY(_pTask->taskPID)		    \
		{ \
			RTMP_SEM_EVENT_UP(&(_pTask->taskSema)); \
		}	\
	}while(0)
#endif


#ifdef KTHREAD_SUPPORT
#define RTUSBCMDUp(pAd) \
	do{	\
		RTMP_OS_TASK	*_pTask = &((pAd)->cmdQTask);	\
		{ \
			_pTask->kthread_running = TRUE; \
	        wake_up(&_pTask->kthread_q); \
		} \
	}while(0)

#else
#define RTUSBCMDUp(pAd)	                \
	do{									    \
		RTMP_OS_TASK	*_pTask = &((pAd)->cmdQTask);	\
		CHECK_PID_LEGALITY(_pTask->taskPID)	    \
		{	\
			RTMP_SEM_EVENT_UP(&(_pTask->taskSema)); \
		}	\
	}while(0)
#endif
#endif /* 0 */

#define DEVICE_VENDOR_REQUEST_OUT       0x40
#define DEVICE_VENDOR_REQUEST_IN        0xc0
/*#define INTERFACE_VENDOR_REQUEST_OUT    0x41 */
/*#define INTERFACE_VENDOR_REQUEST_IN     0xc1 */
#define BULKOUT_MGMT_RESET_FLAG		0x80

#define RTUSB_SET_BULK_FLAG(_M, _F)	((_M)->BulkFlags |= (_F))
#define RTUSB_CLEAR_BULK_FLAG(_M, _F)	((_M)->BulkFlags &= ~(_F))
#define RTUSB_TEST_BULK_FLAG(_M, _F)	(((_M)->BulkFlags & (_F)) != 0)

#endif /* __RTMP_USB_H__ */
