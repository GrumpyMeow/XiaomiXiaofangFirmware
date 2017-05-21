/*
 * BCM43XX Sonics SiliconBackplane PCMCIA core hardware definitions.
 *
 * Copyright (C) 2013, Broadcom Corporation. All Rights Reserved.
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * $Id: sbpcmcia.h 381094 2013-01-25 04:45:06Z $
 */

#ifndef	_SBPCMCIA_H
#define	_SBPCMCIA_H




#define	PCMCIA_FCR		(0x700 / 2)

#define	FCR0_OFF		0
#define	FCR1_OFF		(0x40 / 2)
#define	FCR2_OFF		(0x80 / 2)
#define	FCR3_OFF		(0xc0 / 2)

#define	PCMCIA_FCR0		(0x700 / 2)
#define	PCMCIA_FCR1		(0x740 / 2)
#define	PCMCIA_FCR2		(0x780 / 2)
#define	PCMCIA_FCR3		(0x7c0 / 2)



#define	PCMCIA_COR		0

#define	COR_RST			0x80
#define	COR_LEV			0x40
#define	COR_IRQEN		0x04
#define	COR_BLREN		0x01
#define	COR_FUNEN		0x01


#define	PCICIA_FCSR		(2 / 2)
#define	PCICIA_PRR		(4 / 2)
#define	PCICIA_SCR		(6 / 2)
#define	PCICIA_ESR		(8 / 2)


#define PCM_MEMOFF		0x0000
#define F0_MEMOFF		0x1000
#define F1_MEMOFF		0x2000
#define F2_MEMOFF		0x3000
#define F3_MEMOFF		0x4000


#define MEM_ADDR0		(0x728 / 2)
#define MEM_ADDR1		(0x72a / 2)
#define MEM_ADDR2		(0x72c / 2)


#define PCMCIA_ADDR0		(0x072e / 2)
#define PCMCIA_ADDR1		(0x0730 / 2)
#define PCMCIA_ADDR2		(0x0732 / 2)

#define MEM_SEG			(0x0734 / 2)
#define SROM_CS			(0x0736 / 2)
#define SROM_DATAL		(0x0738 / 2)
#define SROM_DATAH		(0x073a / 2)
#define SROM_ADDRL		(0x073c / 2)
#define SROM_ADDRH		(0x073e / 2)
#define	SROM_INFO2		(0x0772 / 2)	
#define	SROM_INFO		(0x07be / 2)	


#define SROM_IDLE		0
#define SROM_WRITE		1
#define SROM_READ		2
#define SROM_WEN		4
#define SROM_WDS		7
#define SROM_DONE		8


#define	SRI_SZ_MASK		0x03
#define	SRI_BLANK		0x04
#define	SRI_OTP			0x80

#if !defined(LINUX_POSTMOGRIFY_REMOVAL)



#define	CIS_SIZE		PCMCIA_FCR


#define CIS_TUPLE_LEN_MAX	0xff



#define CISTPL_NULL			0x00
#define	CISTPL_VERS_1		0x15		
#define	CISTPL_MANFID		0x20		
#define CISTPL_FUNCID		0x21		
#define	CISTPL_FUNCE		0x22		
#define	CISTPL_CFTABLE		0x1b		
#define	CISTPL_END		0xff		


#define CISTPL_FID_SDIO		0x0c		


#define	LAN_TECH		1		
#define	LAN_SPEED		2		
#define	LAN_MEDIA		3		
#define	LAN_NID			4		
#define	LAN_CONN		5		



#define CFTABLE_REGWIN_2K	0x08		
#define CFTABLE_REGWIN_4K	0x10		
#define CFTABLE_REGWIN_8K	0x20		



#define	CISTPL_BRCM_HNBU	0x80



#define HNBU_SROMREV		0x00	
#define HNBU_CHIPID		0x01	
#define HNBU_BOARDREV		0x02	
#define HNBU_PAPARMS		0x03	
#define HNBU_OEM		0x04	
#define HNBU_CC			0x05	
#define	HNBU_AA			0x06	
#define	HNBU_AG			0x07	
#define HNBU_BOARDFLAGS		0x08	
#define HNBU_LEDS		0x09	
#define HNBU_CCODE		0x0a	
#define HNBU_CCKPO		0x0b	
#define HNBU_OFDMPO		0x0c	
#define HNBU_GPIOTIMER		0x0d	
#define HNBU_PAPARMS5G		0x0e	
#define HNBU_ANT5G		0x0f	
#define HNBU_RDLID		0x10	
#define HNBU_RSSISMBXA2G	0x11	
#define HNBU_RSSISMBXA5G	0x12	
#define HNBU_XTALFREQ		0x13	
#define HNBU_TRI2G		0x14	
#define HNBU_TRI5G		0x15	
#define HNBU_RXPO2G		0x16	
#define HNBU_RXPO5G		0x17	
#define HNBU_BOARDNUM		0x18	
#define HNBU_MACADDR		0x19	
#define HNBU_RDLSN		0x1a	
#define HNBU_BOARDTYPE		0x1b	
#define HNBU_LEDDC		0x1c	
#define HNBU_HNBUCIS		0x1d	
#define HNBU_PAPARMS_SSLPNPHY	0x1e	
#define HNBU_RSSISMBXA2G_SSLPNPHY 0x1f 
#define HNBU_RDLRNDIS		0x20	
#define HNBU_CHAINSWITCH	0x21	
#define HNBU_REGREV		0x22	
#define HNBU_FEM		0x23	
#define HNBU_PAPARMS_C0		0x24	
#define HNBU_PAPARMS_C1		0x25	
#define HNBU_PAPARMS_C2		0x26	
#define HNBU_PAPARMS_C3		0x27	
#define HNBU_PO_CCKOFDM		0x28	
#define HNBU_PO_MCS2G		0x29	
#define HNBU_PO_MCS5GM		0x2a	
#define HNBU_PO_MCS5GLH		0x2b	
#define HNBU_PO_CDD		0x2c	
#define HNBU_PO_STBC		0x2d	
#define HNBU_PO_40M		0x2e	
#define HNBU_PO_40MDUP		0x2f	

#define HNBU_RDLRWU		0x30	
#define HNBU_WPS		0x31	
#define HNBU_USBFS		0x32	
#define HNBU_BRMIN		0x33	
#define HNBU_BRMAX		0x34	
#define HNBU_PATCH		0x35	
#define HNBU_CCKFILTTYPE	0x36	
#define HNBU_OFDMPO5G		0x37	
#define HNBU_ELNA2G             0x38
#define HNBU_ELNA5G             0x39
#define HNBU_TEMPTHRESH 0x3A 
#define HNBU_UUID 0x3B 

#define HNBU_USBEPNUM		0x40	


#define HNBU_CCKBW202GPO       0x41    

#define HNBU_LEGOFDMBW202GPO    0x42    

#define HNBU_LEGOFDMBW205GPO   0x43    

#define HNBU_MCS2GPO    0x44    
#define HNBU_MCS5GLPO    0x45    
#define HNBU_MCS5GMPO    0x46    
#define HNBU_MCS5GHPO    0x47    
#define HNBU_MCS32PO	0x48	
#define HNBU_LEG40DUPPO	0x49 

#define HNBU_PMUREGS	0x4a 

#define HNBU_PATCH2		0x4b	

#define HNBU_USBRDY		0x4c	

#define HNBU_USBREGS	0x4d	

#define HNBU_BLDR_TIMEOUT	0x4e	
#define HNBU_USBFLAGS		0x4f
#define HNBU_PATCH_AUTOINC	0x50
#define HNBU_MDIO_REGLIST	0x51
#define HNBU_MDIOEX_REGLIST	0x52

#define HNBU_UMANFID		0x53
#define HNBU_PUBKEY		0x54	
#define HNBU_WOWLGPIO 		0x55 	
#define HNBU_MUXENAB            0x56    
#define HNBU_GCI_CCR		0x57	

#define HNBU_FEM_CFG		0x58	
#define HNBU_ACPA_C0		0x59	
#define HNBU_ACPA_C1		0x5a	
#define HNBU_ACPA_C2		0x5b	
#define HNBU_MEAS_PWR		0x5c
#define HNBU_PDOFF		0x5d
#define HNBU_ACPPR_2GPO		0x5e	
#define HNBU_ACPPR_5GPO		0x5f	
#define HNBU_ACPPR_SBPO		0x60	
#define HNBU_NOISELVL		0x61
#define HNBU_RXGAIN_ERR		0x62
#define HNBU_AGBGA		0x63
#define HNBU_USBDESC_COMPOSITE	0x64    
#define HNBU_PATCH_AUTOINC8	0x65	
#define HNBU_PATCH8		0x66	
#define HNBU_ACRXGAINS_C0	0x67	
#define HNBU_ACRXGAINS_C1	0x68	
#define HNBU_ACRXGAINS_C2	0x69	
#define HNBU_TXDUTY		0x6a	
#define HNBU_USBUTMI_CTL        0x6b    
#define HNBU_PDOFF_2G		0x6c
#define HNBU_USBSSPHY_UTMI_CTL0 0x6d    
#define HNBU_USBSSPHY_UTMI_CTL1 0x6e    
#define HNBU_USBSSPHY_UTMI_CTL2 0x6f    
#define HNBU_USBSSPHY_SLEEP0    0x70    
#define HNBU_USBSSPHY_SLEEP1    0x71    
#define HNBU_USBSSPHY_SLEEP2    0x72    
#define HNBU_USBSSPHY_SLEEP3    0x73    
#define HNBU_USBSSPHY_MDIO		0x74	
#define HNBU_USB30PHY_NOSS		0x75	
#define HNBU_USB30PHY_NODIS		0x76	

#define HNBU_SROM3SWRGN		0x80	
#define HNBU_RESERVED		0x81	
#define HNBU_CUSTOM1		0x82	
#define HNBU_CUSTOM2		0x83	
#define HNBU_ACPAPARAM		0x84	
#define HNBU_ACPA_CCK		0x86	
#define HNBU_ACPA_40		0x87	
#define HNBU_ACPA_80		0x88	
#define HNBU_ACPA_4080		0x89	


#endif 


#define SBTML_INT_ACK		0x40000		
#define SBTML_INT_EN		0x20000		


#define SBTMH_INT_STATUS	0x40000		

#endif	
