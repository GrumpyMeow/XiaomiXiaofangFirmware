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
	rt5390.c

	Abstract:
	Specific funcitons and variables for RT3090

	Revision History:
	Who         When          What
	--------    ----------    ----------------------------------------------
*/



#include "rt_config.h"


#ifndef RTMP_RF_RW_SUPPORT
#error "You Should Enable compile flag RTMP_RF_RW_SUPPORT for this chip"
#endif /* RTMP_RF_RW_SUPPORT */
#ifdef RTMP_FLASH_SUPPORT
UCHAR RT5390_EeBuffer[EEPROM_SIZE] = { 
0x90, 0x53, 0x02, 0x01, 0x00, 0x0c, 0x43, 0x30, 0x92, 0x00, 0x92, 0x30, 0x14, 0x18, 0x01, 0x80, 
0x00, 0x00, 0x92, 0x30, 0x14, 0x18, 0x00, 0x00, 0x01, 0x00, 0x6a, 0xff, 0x13, 0x02, 0xff, 0xff, 
0xff, 0xff, 0xc1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0x8e, 0x75, 0x01, 0x43, 0x22, 0x08, 0x27, 0x00, 0xff, 0xff, 0x16, 0x01, 0xff, 0xff, 0xd9, 0xfa, 
0xcc, 0x88, 0xff, 0xff, 0x0a, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 
0xff, 0xff, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 
0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x1d, 0x1a, 
0x15, 0x11, 0x0f, 0x0d, 0x0a, 0x07, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x88, 0x88, 
0xcc, 0xcc, 0xaa, 0x88, 0xcc, 0xcc, 0xaa, 0x88, 0xcc, 0xcc, 0xaa, 0x88, 0xcc, 0xcc, 0xaa, 0x88, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, };
#endif /* RTMP_FLASH_SUPPORT */

REG_PAIR RF5390RegTable[] = 
{
/*	{RF_R00,		0x20}, //Read only */
	{RF_R01,		0x0F}, 
	{RF_R02,		0x80}, 
	{RF_R03,		0x88}, /* vcocal_double_step */ 
/*	{RF_R04,		0x51}, // Read only */
	{RF_R05,		0x10}, 
	{RF_R06,		0xA0}, 
	{RF_R07,		0x00}, 
/*	{RF_R08,		0xF1}, // By channel plan */
/*	{RF_R09,		0x02}, // By channel plan */

	{RF_R10,		0x53},
	{RF_R11,		0x4A},
	{RF_R12,		0x46},
	{RF_R13,		0x9F},
	{RF_R14,		0x00}, 
	{RF_R15,		0x00}, 
	{RF_R16,		0x00}, 
/*	{RF_R17,		0x00}, // Bit 7=0, and based on the frequency offset in the EEPROM */
	{RF_R18,		0x03}, 
	{RF_R19,		0x00}, /* Spare */

	{RF_R20,		0x00}, 
	{RF_R21,		0x00}, /* Spare */
	{RF_R22,		0x20},	
	{RF_R23,		0x00}, /* Spare */
	{RF_R24,		0x00}, /* Spare */
	{RF_R25,		0xC0}, 
	{RF_R26,		0x00}, /* Spare */
	{RF_R27,		0x09}, 
	{RF_R28,		0x00}, 
	{RF_R29,		0x10}, 

	{RF_R30,		0x10},
	{RF_R31,		0x80}, 
	{RF_R32,		0x80}, 
	{RF_R33,		0x00}, /* Spare */
	{RF_R34,		0x07}, 
	{RF_R35,		0x12}, 
	{RF_R36,		0x00}, 
	{RF_R37,		0x08}, 
	{RF_R38,		0x85}, 
	{RF_R39,		0x1B}, 

	{RF_R40,		0x0B}, 
	{RF_R41,		0xBB}, 
	{RF_R42,		0xD2}, 
	{RF_R43,		0x9A}, 
	{RF_R44,		0x0E},
	{RF_R45,		0xA2}, 
	{RF_R46,		0x7B}, 
	{RF_R47,		0x00}, 
	{RF_R48,		0x10}, 
	{RF_R49,		0x94},

/*	{RF_R50,		0x00}, // NC */
/*	{RF_R51,		0x00}, // NC */
 	{RF_R52,		0x38}, 
	{RF_R53,		0x84}, /* RT5370 only. RT5390, RT5370F and RT5390F will re-write to 0x00 */
	{RF_R54,		0x78},
	{RF_R55,		0x44}, /* Changed by channel */
	{RF_R56,		0x22}, 
	{RF_R57,		0x80},
	{RF_R58,		0x7F}, 
	{RF_R59,		0x8F}, /* Changed by channel */

	{RF_R60,		0x45}, 
	{RF_R61,		0xDD},
	{RF_R62,		0x00}, /* Spare */
	{RF_R63,		0x00}, /* Spare */
};

#define NUM_RF_5390_REG_PARMS (sizeof(RF5390RegTable) / sizeof(REG_PAIR))

/* 5390U (5370 using PCIe interface) */

REG_PAIR RF5390URegTable[] = 
{
/*	{RF_R00,		0x20}, // Read only */
	{RF_R01,		0x0F}, 
	{RF_R02,		0x80}, 
	{RF_R03,		0x88}, /* vcocal_double_step */
/*	{RF_R04,		0x51}, // Read only */
	{RF_R05,		0x10}, 
	{RF_R06,		0xE0}, 
	{RF_R07,		0x00}, 
/*	{RF_R08,		0xF1}, // By channel plan */
/*	{RF_R09,		0x02}, // By channel plan */
	{RF_R10,		0x53},
	{RF_R11,		0x4A},
	{RF_R12,		0x46},
	{RF_R13,		0x9F},
	{RF_R14,		0x00}, 
	{RF_R15,		0x00}, 
	{RF_R16,		0x00}, 
/*	{RF_R17,		0x00}, // Based on the frequency offset in the EEPROM */
	{RF_R18,		0x03}, 
	{RF_R19,		0x00}, /* Spare */
	{RF_R20,		0x00}, 
	{RF_R21,		0x00}, /* Spare */
	{RF_R22,		0x20},	
	{RF_R23,		0x00}, /* Spare */
	{RF_R24,		0x00}, /* Spare */
	{RF_R25,		0x80}, 
	{RF_R26,		0x00}, /* Spare */
	{RF_R27,		0x09}, 
	{RF_R28,		0x00}, 
	{RF_R29,		0x10}, 
	{RF_R30,		0x10},
	{RF_R31,		0x80}, 
	{RF_R32,		0x80}, 
	{RF_R33,		0x00}, /* Spare */
	{RF_R34,		0x07}, 
	{RF_R35,		0x12}, 
	{RF_R36,		0x00}, 
	{RF_R37,		0x08}, 
	{RF_R38,		0x85}, 
	{RF_R39,		0x1B}, 
	{RF_R40,		0x0B}, 
	{RF_R41,		0xBB}, 
	{RF_R42,		0xD2}, 
	{RF_R43,		0x9A}, 
	{RF_R44,		0x0E},
	{RF_R45,		0xA2}, 
	{RF_R46,		0x73}, 
	{RF_R47,		0x00}, 
	{RF_R48,		0x10}, 
	{RF_R49,		0x94},
/*	{RF_R50,		0x00}, // NC */
/*	{RF_R51,		0x00}, // NC */
	{RF_R52,		0x38}, 
	{RF_R53,		0x00},
	{RF_R54,		0x78},
	{RF_R55,		0x23},
	{RF_R56,		0x22}, 
	{RF_R57,		0x80},
	{RF_R58,		0x7F}, 
	{RF_R59,		0x07}, 
	{RF_R60,		0x45}, 
	{RF_R61,		0xD1}, 
	{RF_R62,		0x00}, /* Spare */
	{RF_R63,		0x00}, /* Spare */
};

#define NUM_RF_5390U_REG_PARMS (sizeof(RF5390URegTable) / sizeof(REG_PAIR))

REG_PAIR RF5392RegTable[] = 
{
/*	{RF_R00,		0x20}, // Read only */
	{RF_R01,		0x17},
	{RF_R02,		0x80},
	{RF_R03,		0x88}, /* vcocal_double_step */
/*	{RF_R04,		0x51}, // Read only */
	{RF_R05,		0x10},
	{RF_R06,		0xE0}, /* 20101018 update */
	{RF_R07,		0x00}, 
/*	{RF_R08,		0xF1}, // By channel plan */
/*	{RF_R09,		0x02}, // By channel plan */
	{RF_R10,		0x53},
	{RF_R11,		0x4A},
	{RF_R12,		0x46},
	{RF_R13,		0x9F},
	{RF_R14,		0x00}, 
	{RF_R15,		0x00}, 
	{RF_R16,		0x00}, 
/*	{RF_R17,		0x00}, // Based on the frequency offset in the EEPROM */
	{RF_R18,		0x03}, 
	{RF_R19,		0x4D}, /* Spare */
	{RF_R20,		0x00}, 
	{RF_R21,		0x8D}, /* Spare 20101018 update. */
	{RF_R22,		0x20},	
	{RF_R23,		0x0B}, /* Spare 20101018 update. */
	{RF_R24,		0x44}, /* Spare */
	{RF_R25,		0x80}, /* 20101018 update. */
	{RF_R26,		0x82}, /* Spare */
	{RF_R27,		0x09}, 
	{RF_R28,		0x00}, 
	{RF_R29,		0x10}, 
	{RF_R30,		0x10},
	{RF_R31,		0x80}, 
	{RF_R32,		0x20}, 
	{RF_R33,		0xC0}, /* Spare */
	{RF_R34,		0x07}, 
	{RF_R35,		0x12}, 
	{RF_R36,		0x00}, 
	{RF_R37,		0x08}, 
	{RF_R38,		0x89}, /* 20101118 update. */
	{RF_R39,		0x1B}, 
	{RF_R40,		0x0F}, /* 20101118 update. */
	{RF_R41,		0xBB}, 
	{RF_R42,		0xD5}, /* 20101018 update. */
	{RF_R43,		0x9B}, /* 20101018 update. */
	{RF_R44,		0x0E},
	{RF_R45,		0xA2}, 
	{RF_R46,		0x73}, 
	{RF_R47,		0x0C}, 
	{RF_R48,		0x10}, 
	{RF_R49,		0x94},
	{RF_R50,		0x94}, /* 5392_todo */
	{RF_R51,		0x3A}, /* 20101018 update */
	{RF_R52,		0x48}, /* 20101018 update. */
	{RF_R53,		0x44}, /* 20101018 update. */
	{RF_R54,		0x38},
	{RF_R55,		0x43},
	{RF_R56,		0xA1}, /* 20101018 update. */
	{RF_R57,		0x00}, /* 20101018 update.*/
	{RF_R58,		0x39}, 
	{RF_R59,		0x07}, /* 20101018 update. */
	{RF_R60,		0x45}, /* 20101018 update.*/
	{RF_R61,		0x91}, /* 20101018 update. */
	{RF_R62,		0x39}, /* Spare */
	{RF_R63,		0x07}, /* Spare */
};

#define NUM_RF_5392_REG_PARMS (sizeof(RF5392RegTable) / sizeof(REG_PAIR))

#if 0
REG_PAIR   RT5390_BBPRegTable[] = {
	{BBP_R65,		0x2C},		/* fix rssi issue */
	{BBP_R66,		0x38},	/* Also set this default value to pAd->BbpTuning.R66CurrentValue at initial */
	{BBP_R69,		0x12},
	{BBP_R70,		0xa},	/* BBP_R70 will change to 0x8 in ApStartUp and LinkUp for rt2860C, otherwise value is 0xa */
	{BBP_R73,		0x10},
	{BBP_R81,		0x37},
	{BBP_R82,		0x62},
	{BBP_R83,		0x6A},
	{BBP_R84,		0x99},	/* 0x19 is for rt2860E and after. This is for extension channel overlapping IOT. 0x99 is for rt2860D and before */
	{BBP_R86,		0x00},	/* middle range issue, Rory @2008-01-28 	*/
	{BBP_R91,		0x04},	/* middle range issue, Rory @2008-01-28 */
	{BBP_R92,		0x00},	/* middle range issue, Rory @2008-01-28 */
	{BBP_R103,		0x00}, 	/* near range high-power issue, requested from Gary @2008-0528 */
#ifdef RTMP_RBUS_SUPPORT
	{BBP_R105,		0x01},/*kurtis:0x01 ori  0x05 is for rt2860E to turn on FEQ control. It is safe for rt2860D and before, because Bit 7:2 are reserved in rt2860D and before. */
#else
	{BBP_R105,		0x05},	/* 0x05 is for rt2860E to turn on FEQ control. It is safe for rt2860D and before, because Bit 7:2 are reserved in rt2860D and before. */
#endif /* RTMP_RBUS_SUPPORT */
#ifdef DOT11_N_SUPPORT
	{BBP_R106,		0x35},	/* Optimizing the Short GI sampling request from Gray @2009-0409 */
#endif /* DOT11_N_SUPPORT */
};

UCHAR RT5390_NUM_BBP_REG_PARMS = (sizeof(RT5390_BBPRegTable) / sizeof(REG_PAIR));
#endif

RTMP_REG_PAIR	RT5390_MACRegTable[] =	{
	{TX_SW_CFG0,		0x404},   // 2010-07-20
};

UCHAR RT5390_NUM_MAC_REG_PARMS = (sizeof(RT5390_MACRegTable) / sizeof(RTMP_REG_PAIR));

#if defined(RTMP_INTERNAL_TX_ALC) || defined(RTMP_TEMPERATURE_COMPENSATION) 

/* The Tx power tuning entry */
TX_POWER_TUNING_ENTRY_STRUCT RT5390_TxPowerTuningTable[] = 
{
/*	idxTxPowerTable			Tx power control over RF	Tx power control over MAC */
/*	(zero-based array)			{ RF R49[5:0]: Tx0 ALC},	{MAC 0x1314~0x1324} */
/*     0       */				{0x00,					-15}, 
/*     1       */ 				{0x01,					-15}, 
/*     2       */ 				{0x00,					-14}, 
/*     3       */ 				{0x01,					-14}, 
/*     4       */ 				{0x00,					-13}, 
/*     5       */				{0x01,					-13}, 
/*     6       */ 				{0x00,					-12}, 
/*     7       */ 				{0x01,					-12}, 
/*     8       */ 				{0x00,					-11}, 
/*     9       */ 				{0x01,					-11}, 
/*     10     */ 				{0x00,					-10}, 
/*     11     */ 				{0x01,					-10}, 
/*     12     */ 				{0x00,					-9}, 
/*     13     */ 				{0x01,					-9}, 
/*     14     */ 				{0x00,					-8}, 
/*     15     */ 				{0x01,					-8}, 
/*     16     */ 				{0x00,					-7}, 
/*     17     */ 				{0x01,					-7}, 
/*     18     */ 				{0x00,					-6}, 
/*     19     */ 				{0x01,					-6}, 
/*     20     */ 				{0x00,					-5}, 
/*     21     */ 				{0x01,					-5}, 
/*     22     */ 				{0x00,					-4}, 
/*     23     */ 				{0x01,					-4}, 
/*     24     */ 				{0x00,					-3}, 
/*     25     */ 				{0x01,					-3}, 
/*     26     */ 				{0x00,					-2}, 
/*     27     */ 				{0x01,					-2}, 
/*     28     */ 				{0x00,					-1}, 
/*     29     */ 				{0x01,					-1}, 
/*     30     */ 				{0x00,					0}, 
/*     31     */ 				{0x01,					0}, 
/*     32     */ 				{0x02,					0}, 
/*     33     */ 				{0x03,					0}, 
/*     34     */ 				{0x04,					0}, 
/*     35     */ 				{0x05,					0}, 
/*     36     */ 				{0x06,					0}, 
/*     37     */ 				{0x07,					0}, 
/*     38     */ 				{0x08,					0}, 
/*     39     */ 				{0x09,					0}, 
/*     40     */ 				{0x0A,					0}, 
/*     41     */ 				{0x0B,					0}, 
/*     42     */ 				{0x0C,					0}, 
/*     43     */ 				{0x0D,					0}, 
/*     44     */ 				{0x0E,					0}, 
/*     45     */ 				{0x0F,					0}, 
/*     46     */ 				{0x10,					0}, 
/*     47     */ 				{0x11,					0}, 
/*     48     */ 				{0x12,					0}, 
/*     49     */ 				{0x13,					0}, 
/*     50     */ 				{0x14,					0}, 
/*     51     */ 				{0x15,					0}, 
/*     52     */ 				{0x16,					0}, 
/*     53     */ 				{0x17,					0}, 
/*     54     */ 				{0x18,					0}, 
/*     55     */ 				{0x19,					0}, 
/*     56     */ 				{0x1A,					0}, 
/*     57     */ 				{0x1B,					0}, 
/*     58     */ 				{0x1C,					0}, 
/*     59     */ 				{0x1D,					0}, 
/*     60     */ 				{0x1E,					0}, 
/*     61     */ 				{0x1F,					0}, 
/*     62     */                         	{0x20,                              	0}, 
/*     63     */                          	{0x21,                             	0}, 
/*     64     */                          	{0x22,                             	0}, 
/*     65     */                          	{0x23,                            	0}, 
/*     66     */                          	{0x24,                            	0}, 
/*     67     */                         	{0x25,                            	0}, 
/*     68     */                          	{0x26,                            	0}, 
/*     69     */                         	{0x27,                            	0}, 
/*     70     */                         	{0x27-1,                         	1}, 
/*     71     */                          	{0x27,                            	1}, 
/*     72     */                          	{0x27-1,                         	2}, 
/*     73     */                      	{0x27,                             	2}, 
/*     74     */                        	{0x27-1,                          	3}, 
/*     75     */                     	{0x27,                             	3}, 
/*     76     */                     	{0x27-1,                        	4}, 
/*     77     */                      	{0x27,                           	4}, 
/*     78     */                      	{0x27-1,                          	5}, 
/*     79     */                       	{0x27,                              	5}, 
/*     80     */                      	{0x27-1,                          	6}, 
/*     81     */                       	{0x27,                            	6}, 
/*     82     */                       	{0x27-1,                        	7}, 
/*     83     */                       	{0x27,                            	7}, 
/*     84     */                      	{0x27-1,                         	8}, 
/*     85     */                      	{0x27,                            	8}, 
/*     86     */                      	{0x27-1,                         	9}, 
/*     87     */                       	{0x27,                            	9}, 
/*     88     */                       	{0x27-1,                         	10}, 
/*     89     */                       	{0x27,                            	10}, 
/*     90     */                       	{0x27-1,                         	11}, 
/*     91     */                       	{0x27,                            	11}, 
/*     92     */                       	{0x27-1,                         	12}, 
/*     93     */                       	{0x27,                           	12}, 
/*     94     */                      	{0x27-1,                        	13}, 
/*     95     */                       	{0x27,                            	13}, 
/*     96     */                       	{0x27-1,                         	14}, 
/*     97     */                       	{0x27,                            	14}, 
/*     98     */                       	{0x27-1,                        	15}, 
/*     99     */                       	{0x27,                            	15}, 
};

#ifdef RTMP_INTERNAL_TX_ALC

ULONG TssiRatioTable[][2] = 
	{
/*	{numerator,	denominator}	Power delta (dBm)	Ratio	Index */
	{955,		10000}, 		/* -12			0.0955	0 */
	{1161, 		10000},		/* -11			0.1161	1 */
	{1413,		10000}, 		/* -10			0.1413	2 */
	{1718,		10000},		/* -9			0.1718	3 */
	{2089, 		10000},		/* -8			0.2089	4 */
	{2541, 		10000}, 		/* -7 			0.2541	5 */
	{3090, 		10000}, 		/* -6 			0.3090	6 */
	{3758, 		10000}, 		/* -5 			0.3758	7 */
	{4571, 		10000}, 		/* -4 			0.4571	8 */
	{5559, 		10000}, 		/* -3 			0.5559	9 */
	{6761, 		10000}, 		/* -2 			0.6761	10 */
	{8222, 		10000}, 		/* -1 			0.8222	11 */
	{1, 				1}, 		/* 0	 			1		12 */
	{12162, 		10000}, 		/* 1				1.2162	13 */
	{14791, 		10000}, 		/* 2				1.4791	14 */
	{17989, 		10000}, 		/* 3				1.7989	15 */
	{21878, 		10000}, 		/* 4				2.1878	16 */
	{26607, 		10000}, 		/* 5				2.6607	17 */
	{32359, 		10000}, 		/* 6				3.2359	18 */
	{39355, 		10000}, 		/* 7				3.9355	19 */
	{47863, 		10000}, 		/* 8				4.7863	20 */
	{58210, 		10000}, 		/* 9				5.8210	21 */
	{70795, 		10000}, 		/* 10			7.0795	22 */
	{86099, 		10000}, 		/* 11			8.6099	23 */
	{104713, 	10000}, 		/* 12			10.4713	24 */
};

/* The desired TSSI over CCK (with extended TSSI information) */
CHAR RT5390_desiredTSSIOverCCKExt[NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET + 1][4];

/* The desired TSSI over OFDM (with extended TSSI information) */
CHAR RT5390_desiredTSSIOverOFDMExt[NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET + 1][8];

/* The desired TSSI over HT (with extended TSSI information) */
CHAR RT5390_desiredTSSIOverHTExt[NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET + 1][8];

/* The desired TSSI over HT40 (with extended TSSI information) */
CHAR RT5390_desiredTSSIOverHT40Ext[NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET + 1][8];

/* The desired TSSI over HT using STBC (with extended TSSI information) */
CHAR RT5390_desiredTSSIOverHTUsingSTBCExt[NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET + 1][8];

#endif /* RTMP_INTERNAL_TX_ALC */
#endif /* RTMP_INTERNAL_TX_ALC || RTMP_TEMPERATURE_COMPENSATION */

/*
========================================================================
Routine Description:
	Initialize RT5390.

Arguments:
	pAd					- WLAN control block pointer

Return Value:
	None

Note:
========================================================================
*/
VOID RT5390_Init(
	IN PRTMP_ADAPTER		pAd)
{
	RTMP_CHIP_OP *pChipOps = &pAd->chipOps;
	RTMP_CHIP_CAP *pChipCap = &pAd->chipCap;

	/* pAd->RfIcType = RFIC_3320; */

	/* init capability */
	pChipCap->MaxNumOfRfId = 63;
	pChipCap->MaxNumOfBbpId = 255;

	if (IS_RT5390(pAd))
		pChipCap->pRFRegTable = RF5390RegTable;
	else if (IS_RT5392(pAd))
		pChipCap->pRFRegTable = RF5392RegTable;
		
	pChipCap->pBBPRegTable = NULL; /* The same with BBPRegTable */
	pChipCap->bbpRegTbSize = 0;
	pChipCap->SnrFormula = SNR_FORMULA3;
	pChipCap->TXWISize = 16;
	pChipCap->RXWISize = 16;
#ifdef RTMP_FLASH_SUPPORT
	pChipCap->eebuf = RT5390_EeBuffer;
#endif /* RTMP_FLASH_SUPPORT */
	pChipOps->AsicRfInit = NICInitRT5390RFRegisters;
	pChipOps->AsicHaltAction = RT5390HaltAction;
	pChipOps->AsicRfTurnOff = RT5390LoadRFSleepModeSetup;
	pChipOps->AsicReverseRfFromSleepMode = RT5390ReverseRFSleepModeSetup;
	pChipCap->FlgIsHwWapiSup = TRUE;
	pChipCap->FlgIsVcoReCalMode = VCO_CAL_MODE_2;

	pChipCap->phy_caps = fPHY_CAP_24G;
	pChipCap->phy_caps |= fPHY_CAP_HT;

	if (IS_RT5370G(pAd) || IS_RT5390R(pAd))
	{
		DBGPRINT(RT_DEBUG_OFF, ("\x1b[31m%s: FlgIsHwAntennaDiversitySup --> True\x1b[m\n", __FUNCTION__));
		pChipCap->FlgIsHwAntennaDiversitySup = TRUE; 
	}
	else
		pChipCap->FlgIsHwAntennaDiversitySup = FALSE; 

#ifdef NEW_MBSSID_MODE
	pChipCap->MBSSIDMode = MBSSID_MODE1;
#else
	pChipCap->MBSSIDMode = MBSSID_MODE0;
#endif /* NEW_MBSSID_MODE */

#ifdef DOT11W_PMF_SUPPORT
        pChipCap->FlgPMFEncrtptMode = PMF_ENCRYPT_MODE_1;
#endif /* DOT11W_PMF_SUPPORT */

	/* Init operator */
	pChipOps->AsicBbpInit = NICInitRT5390BbpRegisters;
	pChipOps->AsicMacInit = NICInitRT5390MacRegisters;
	pChipOps->RxSensitivityTuning = RT5390_RxSensitivityTuning;
#ifdef CONFIG_STA_SUPPORT
	pChipOps->ChipAGCAdjust = RT5390_ChipAGCAdjust;
#endif /* CONFIG_STA_SUPPORT */
	pChipOps->ChipBBPAdjust = RT5390_ChipBBPAdjust;
	pChipOps->ChipSwitchChannel = RT5390_ChipSwitchChannel;
	pChipOps->ChipAGCInit = RT5390_ChipAGCInit;
	pChipOps->AsicGetTxPowerOffset = AsicGetTxPowerOffset;

#ifdef RTMP_INTERNAL_TX_ALC
	if (IS_RT5390(pAd))
	{
		pChipCap->TxAlcTxPowerUpperBound_2G = 69;
		pChipCap->TxPowerTuningTable_2G = RT5390_TxPowerTuningTable;
		pChipOps->InitDesiredTSSITable = RT5390_InitDesiredTSSITable;
		pChipOps->AsicTxAlcGetAutoAgcOffset = RT5390_AsicTxAlcGetAutoAgcOffset;
	}

#ifdef TSSI_ANTENNA_VARIATION
#ifdef RELEASE_EXCLUDE
	/* 
		TSSI readout value will depend on well output matching. 
		When antenna matching is poor, the TSSI reading will be incorrect. 
		The outcome is the power compensation will be compensated incorrectly, 
		and cause EVM out of calibrate range, and make throughput drop.
	*/
#endif /* RELEASE_EXCLUDE */
	pChipCap->bLimitPowerRange = TRUE;
#else
	pChipCap->bLimitPowerRange = FALSE;
#endif /* TSSI_ANTENNA_VARIATION */
#endif /* RTMP_INTERNAL_TX_ALC */

#ifdef RTMP_TEMPERATURE_COMPENSATION
	if (IS_RT5392(pAd))
	{
		pChipCap->bTempCompTxALC = TRUE;
		pChipCap->TxAlcTxPowerUpperBound_2G = 69;
		pChipCap->TxPowerTuningTable_2G = RT5390_TxPowerTuningTable;
#ifdef RELEASE_EXCLUDE
		/* 
		    Since RT5392 has a temperature sense resistor to do temperature compensation, 
		    don't need to do TSSI/TSSI-Extended calibration
		*/
#endif /* RELEASE_EXCLUDE */		
		pChipOps->AsicTxAlcGetAutoAgcOffset = AsicGetAutoAgcOffsetForTemperatureSensor;
		pChipOps->ATEReadExternalTSSI = RT5392_ATEReadExternalTSSI;	
	}
#endif /* RTMP_TEMPERATURE_COMPENSATION */

	/* 5390/92 have other MAC registers to extra compensate Tx power for OFDM 54, HT MCS 7 and STBC MCS 7 */
	pChipOps->AsicExtraPowerOverMAC = RT539x_AsicExtraPowerOverMAC;

#ifdef IQ_CAL_SUPPORT
	if (IS_RT5390(pAd))
		pChipOps->ChipIQCalibration = IQCalibrationViaBBPAccessSpace;
	else if (IS_RT5392(pAd))
		pChipOps->ChipIQCalibration = IQCalibration;
#endif /* IQ_CAL_SUPPORT */

#ifdef RTMP_FREQ_CALIBRATION_SUPPORT
#ifdef CONFIG_STA_SUPPORT
	pChipCap->FreqCalibrationSupport = TRUE;
	pChipCap->FreqCalInitMode = FREQ_CAL_INIT_MODE2;
	pChipCap->FreqCalMode = FREQ_CAL_MODE1;
	pChipCap->RxWIFrqOffset = RXWI_FRQ_OFFSET_FIELD1;
#endif /* CONFIG_STA_SUPPORT */
#endif /* RTMP_FREQ_CALIBRATION_SUPPORT */

	if (IS_RT5390(pAd))/* 1T1R only */
	{
		pChipOps->SetRxAnt = RT5390SetRxAnt;
#ifdef ANT_DIVERSITY_SUPPORT
		pChipOps->HwAntEnable = HWAntennaDiversityEnable;
#endif /* ANT_DIVERSITY_SUPPORT */
#ifdef TXRX_SW_ANTDIV_SUPPORT
		pChipCap->bTxRxSwAntDiv = FALSE;
#endif /* TXRX_SW_ANTDIV_SUPPORT */

		pAd->Mlme.bEnableAutoAntennaCheck = FALSE;	
	}
	
#ifdef CARRIER_DETECTION_SUPPORT
	pAd->chipCap.carrier_func = TONE_RADAR_V2;
	pChipOps->ToneRadarProgram = ToneRadarProgram_v2;
#endif /* CARRIER_DETECTION_SUPPORT */

	if (IS_RT5392(pAd))
		pChipOps->AsicResetBbpAgent = RT5392_AsicResetBBPAgent;
	
	RtmpChipBcnSpecInit(pAd);
	
	pChipCap->MCUType = M8051;

#if defined(WOW_SUPPORT) && defined(RTMP_MAC_USB)
	pChipOps->AsicWOWEnable = RT28xxUsbAsicWOWEnable;
	pChipOps->AsicWOWDisable = RT28xxUsbAsicWOWDisable;
#endif /* defined(WOW_SUPPORT) && defined(RTMP_MAC_USB) */
}

VOID NICInitRT5390RFRegisters(IN PRTMP_ADAPTER pAd)
{
	INT 		i;
	ULONG	data;
	UCHAR	RfReg = 0;
	
	/* Init RF calibration */
	/* Driver should toggle RF R30 bit7 before init RF registers */
	RT30xxReadRFRegister(pAd, RF_R02, (PUCHAR)&RfReg);
	RfReg = ((RfReg & ~0x80) | 0x80); /* rescal_en (initiate calbration) */
	RT30xxWriteRFRegister(pAd, RF_R02, (UCHAR)RfReg);
		
	RTMPusecDelay(1000);
		
	RfReg = ((RfReg & ~0x80) | 0x00); /* rescal_en (initiate calbration) */
	RT30xxWriteRFRegister(pAd, RF_R02, (UCHAR)RfReg);

	DBGPRINT(RT_DEBUG_TRACE, ("%s: Initialize the RF registers to the default values", __FUNCTION__));
		
	/* Initialize RF register to default value */
	if (IS_RT5392(pAd))
	{
		/* Initialize RF register to default value */
		for (i = 0; i < NUM_RF_5392_REG_PARMS; i++)
		{
			if (IS_RT5392C(pAd))
			{
#ifdef RTMP_MAC_USB /* For >= RT5372C */
			if (RF5392RegTable[i].Register == RF_R23)
			{
					RF5392RegTable[i].Value = 0x0F;
			}
			else if (RF5392RegTable[i].Register == RF_R24)
			{
					RF5392RegTable[i].Value = 0x3E;
			}
			else if (RF5392RegTable[i].Register == RF_R51)
			{
					RF5392RegTable[i].Value = 0x32;
			}
			else if (RF5392RegTable[i].Register == RF_R53)
			{
					RF5392RegTable[i].Value = 0x22;
			}
			else if (RF5392RegTable[i].Register == RF_R56)
			{
					RF5392RegTable[i].Value = 0xC1;
			}
			else if (RF5392RegTable[i].Register == RF_R59)
			{
					RF5392RegTable[i].Value = 0x0F;
			}
#endif /* RTMP_MAC_USB */
#ifdef RTMP_MAC_PCI /* For >= RT5392C */
				if (RF5392RegTable[i].Register == RF_R23)
 			{
				RF5392RegTable[i].Value = 0x0B;
			}
				else if (RF5392RegTable[i].Register == RF_R51)
			{
				RF5392RegTable[i].Value = 0x3A;
			}
				else if (RF5392RegTable[i].Register == RF_R53)
			{
				RF5392RegTable[i].Value = 0x44;
			}
				else if (RF5392RegTable[i].Register == RF_R59)
			{
				RF5392RegTable[i].Value = 0x07;
			}
#endif /* RTMP_MAC_PCI */
			}	
			RT30xxWriteRFRegister(pAd, RF5392RegTable[i].Register, RF5392RegTable[i].Value);
		}
	}
	else if (IS_RT5390U(pAd))
	{
		DBGPRINT(RT_DEBUG_TRACE, ("%s: Initialize the RF registers to the default values (5390U)", __FUNCTION__));

		/* Initialize RF register to default value */
		for (i = 0; i < NUM_RF_5390U_REG_PARMS; i++)
		{	
			RT30xxWriteRFRegister(pAd, RF5390URegTable[i].Register, RF5390URegTable[i].Value);
		}
	}
	else if (IS_RT5390(pAd) && !IS_MINI_CARD(pAd))
	{
		/* Initialize RF register to default value */
		for (i = 0; i < NUM_RF_5390_REG_PARMS; i++)
		{
#ifdef RTMP_MAC_PCI /* For RT5390 */
			if ((IS_RT5390F(pAd) || IS_RT5390H(pAd)) && (RF5390RegTable[i].Register == RF_R06)) /* >= RT5390F */
			{
				RF5390RegTable[i].Value = 0xE0;
			}
			else if ((IS_RT5390F(pAd) || IS_RT5390H(pAd)) && (RF5390RegTable[i].Register == RF_R25)) /* >= RT5390F */
			{
				RF5390RegTable[i].Value = 0x80;
			}
			else if ((IS_RT5390F(pAd) || IS_RT5390H(pAd)) && (RF5390RegTable[i].Register == RF_R46)) /* >= RT5390F */
			{
				RF5390RegTable[i].Value = 0x73;
			}
			else if ((IS_RT5390F(pAd) || IS_RT5390H(pAd)) && (RF5390RegTable[i].Register == RF_R53)) /* >= RT5390F */
			{
				RF5390RegTable[i].Value = 0x00;
			}
			else if ((IS_RT5390F(pAd) || IS_RT5390H(pAd)) && (RF5390RegTable[i].Register == RF_R61)) /* >= RT5390F */
			{
				RF5390RegTable[i].Value = 0xD1;
			}
#endif /* RTMP_MAC_PCI */
#ifdef RTMP_MAC_USB /* For RT5370 */
			if (IS_RT5390F(pAd) && (RF5390RegTable[i].Register == RF_R06)) /* >= RT5390F */
			{
				RF5390RegTable[i].Value = 0xE0;
			}
			else if (IS_RT5390F(pAd) && (RF5390RegTable[i].Register == RF_R25)) /* >= RT5390F */
			{
				RF5390RegTable[i].Value = 0x80;
			}
			else if (IS_RT5390F(pAd) && (RF5390RegTable[i].Register == RF_R46)) /* >= RT5390F */
			{
				RF5390RegTable[i].Value = 0x73;
			}
			else if (IS_RT5390F(pAd) && (RF5390RegTable[i].Register == RF_R53)) /* >= RT5390F */
			{
				RF5390RegTable[i].Value = 0x00;
			}
			else if (IS_RT5390F(pAd) && (RF5390RegTable[i].Register == RF_R56)) /* >= RT5390F */
			{
				RF5390RegTable[i].Value = 0x42;
			}
			else if (IS_RT5390F(pAd) && (RF5390RegTable[i].Register == RF_R61)) /* >= RT5390F */
			{
				RF5390RegTable[i].Value = 0xD1;
			}
#endif /* RTMP_MAC_USB */
			RT30xxWriteRFRegister(pAd, RF5390RegTable[i].Register, RF5390RegTable[i].Value);
		}
	}

	/* 
		Where to add the following codes?
		RT5390BC8, Disable RF_R40 bit[6] to save power consumption
	*/
	if (pAd->NicConfig2.field.CoexBit == TRUE)
	{
		RT30xxReadRFRegister(pAd, RF_R40, (PUCHAR)&RfReg);
		RfReg &= (~0x40);
		RT30xxWriteRFRegister(pAd, RF_R40, (UCHAR)RfReg);
	}

	/* Give bbp filter initial value   Moved here from RTMPFilterCalibration( ) */
	pAd->Mlme.CaliBW20RfR24 = 0x1F;
	pAd->Mlme.CaliBW40RfR24 = 0x2F; /* Bit[5] must be 1 for BW 40 */
	/* For RF filter Calibration */
	/* RTMPFilterCalibration(pAd); */

	/* Initialize RF R27 register, set RF R27 must be behind RTMPFilterCalibration() */
	if ((pAd->MACVersion & 0xffff) < 0x0211)
		RT30xxWriteRFRegister(pAd, RF_R27, 0x3);

	/* set led open drain enable */
	RTMP_IO_READ32(pAd, OPT_14, &data);
	data |= 0x01;
	RTMP_IO_WRITE32(pAd, OPT_14, data);

	RTMP_IO_WRITE32(pAd, TX_SW_CFG1, 0);
	RTMP_IO_WRITE32(pAd, TX_SW_CFG2, 0x0);
 
#ifdef BT_COEXISTENCE_SUPPORT	
	if (IS_RT5390BC8(pAd))/* default is main */
	{
		pAd->RxAnt.Pair1PrimaryRxAnt = 0;
		pAd->RxAnt.Pair1SecondaryRxAnt = 1;
	}				
#endif	

	/* set default antenna as main */
	if (IS_RT5390(pAd)) /* IT1R Only */
		AsicSetRxAnt(pAd, pAd->RxAnt.Pair1PrimaryRxAnt);
	
	/* patch RSSI inaccurate issue, due to design change */
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R79, 0x13);
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R80, 0x05);
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R81, 0x33);

	/* enable DC filter */
	if ((pAd->MACVersion & 0xffff) >= 0x0211)
	{
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R103, 0xc0);
	}
	/*
		From RT3071 Power Sequence v1.1 document, the Normal Operation Setting Registers as follow :
	 	BBP_R138 / RF_R1 / RF_R15 / RF_R17 / RF_R20 / RF_R21.
		add by johnli, RF power sequence setup, load RF normal operation-mode setup 
	*/
	RT5390LoadRFNormalModeSetup(pAd);
	
	/* adjust some BBP register contents */
	/* also can put these BBP registers to pBBPRegTable */
	
#if 0 /* Move to chipOps.AsicBbpInit hook function (NICInitRT5390BbpRegisters) */
	RT5390_PostBBPInitialization(pAd);
#endif 
	
}


/*
	Antenna divesity use GPIO3 and EESK pin for control
	Antenna and EEPROM access are both using EESK pin,
	Therefor we should avoid accessing EESK at the same time
	Then restore antenna after EEPROM access
	The original name of this function is AsicSetRxAnt(), now changes to this.
*/
VOID RT5390SetRxAnt(
	IN PRTMP_ADAPTER	pAd,
	IN UCHAR			Ant)
{
	if ((RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_RESET_IN_PROGRESS))	||
		(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_HALT_IN_PROGRESS))	||
		(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_RADIO_OFF)) ||
		(RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST)))
	{
		return;
	}

	if (IS_RT5390(pAd)
#ifdef BT_COEXISTENCE_SUPPORT	
		&& (!IS_RT5390BC8(pAd))
#endif /* BT_COEXISTENCE_SUPPORT */
		)
	{
		UCHAR BbpValue = 0;

#ifdef TXRX_SW_ANTDIV_SUPPORT
        /* EEPROM 34h bit 13 = 1, support SW antenna diverity TX/RX boundle switch */

        if (pAd->chipCap.bTxRxSwAntDiv) /* Mini card with TX/RX Diversity (RT5390U) & USB with TX/RX Diversity (RT5370) */
        {
			UINT32 Value;

            RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R152, &BbpValue);
            BbpValue = (BbpValue  | 0x80); /* MSB =1 , TX/RX is the same path */
            RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R152, BbpValue);


            if (Ant == 0) /* 0: Main antenna */
            {
                RTMP_IO_READ32(pAd, GPIO_CTRL_CFG, &Value);
                DBGPRINT(RT_DEBUG_ERROR, ("AsicSetRxTxAnt, before switch to main antenna(%X)\n", Value));
                Value &= ~(0x04000808); /* GPIO3 = 0, GIPO10 = 1 */
                Value |= (0x00040000);
                RTMP_IO_WRITE32(pAd, GPIO_CTRL_CFG, Value);
                DBGPRINT(RT_DEBUG_ERROR, ("AsicSetRxTxAnt, after switch to main antenna(%X)\n", Value));
            }
            else if (Ant == 1) /* 1: Aux. antenna */
            {
                RTMP_IO_READ32(pAd, GPIO_CTRL_CFG, &Value);
                DBGPRINT(RT_DEBUG_ERROR, ("AsicSetRxTxAnt, before switch to aux antenna(%X)\n", Value));
                Value &= ~(0x04040800); /* GPIO3 = 1, GIPO10 = 0 */
                Value |= (0x8);
                RTMP_IO_WRITE32(pAd, GPIO_CTRL_CFG, Value);
                DBGPRINT(RT_DEBUG_ERROR, ("AsicSetRxTxAnt, after switch to aux antenna(%X)\n", Value));
            }
        }else
#endif  /* TXRX_SW_ANTDIV_SUPPORT */

		if (pAd->chipCap.FlgIsHwAntennaDiversitySup) /* PPAD support */
		{
    		/* For PPAD Debug, BBP R153[7] = 1 --> Main Ant, R153[7] = 0 --> Aux Ant */
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R150, 0x00); /* Disable ANTSW_OFDM */		
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R151, 0x00); /* Disable ANTSW_CCK	*/		
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R154, 0x00); /* Clear R154[4], Rx Ant is not bound to the previous rx packet selected Ant */
			if (Ant == 0)
			{
				RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R152, 0x80); /* Main Ant */			
				DBGPRINT(RT_DEBUG_TRACE, ("\x1b[31m%s: rt5370G/rt5390R --> switch to main\x1b[m\n", __FUNCTION__));
			}
			else
			{
				RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R152, 0x00); /* Aux Ant */				
				DBGPRINT(RT_DEBUG_TRACE, ("\x1b[31m%s: rt5370G/rt5390R --> switch to aux\x1b[m\n", __FUNCTION__));
			}
			
			
		}	
		else
		{
			if (Ant == 0) /* 0: Main antenna */
			{
				RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R152, &BbpValue);
				BbpValue = ((BbpValue & ~0x80) | (0x80));
				RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R152, BbpValue);

				DBGPRINT(RT_DEBUG_OFF, ("AsicSetRxAnt, switch to main antenna\n"));
			}
			else /* 1: Aux. antenna */
			{
				RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R152, &BbpValue);
				BbpValue = ((BbpValue & ~0x80) | (0x00));
				RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R152, BbpValue);

				DBGPRINT(RT_DEBUG_OFF, ("AsicSetRxAnt, switch to aux. antenna\n"));
			}	
		}
	}
#ifdef RTMP_MAC_PCI
#ifdef BT_COEXISTENCE_SUPPORT
	else if (IS_RT5390BC8(pAd))
	{
		UINT32 Value;
		
		/* the antenna selection is through firmware and MAC register(GPIO3) */
		if (Ant == 0)
		{
			/*
				Main antenna
				E2PROM_CSR only in PCI bus Reg., USB Bus need MCU commad to control the EESK pin.
			*/

			RTMP_IO_READ32(pAd, GPIO_CTRL_CFG, &Value);
			Value &= ~(0x0808);
			Value |= 0x08;
					
			/*
				RT5390 Use GPIO6 and GPIO3 to control antenna diversity
				Also make sure GPIO_SWITCH(Function) MAC 0x05DC Bit[6] been enabled.
				Here we use GPIO6 instead of EESK.
			 */				

			Value &= ~(0x4040);
			RTMP_IO_READ32(pAd, GPIO_CTRL_CFG, &Value);
			Value &= ~(0x0808);
			RTMP_IO_WRITE32(pAd, GPIO_CTRL_CFG, Value);
			DBGPRINT_RAW(RT_DEBUG_TRACE, ("AsicSetRxAnt, switch to main antenna\n"));
		}
		else
		{
			/*
				Aux antenna
				E2PROM_CSR only in PCI bus Reg., USB Bus need MCU commad to control the EESK pin.
			*/
			
			RTMP_IO_READ32(pAd, GPIO_CTRL_CFG, &Value);
			Value &= ~(0x0808);
			
			/*
				RT5390 Use GPIO6 and GPIO3 to control antenna diversity
				Also make sure GPIO_SWITCH(Function) MAC 0x05DC Bit[6] been enabled.
				Here we use GPIO6 instead of EESK.
			*/
			
			Value &= ~(0x4040);
			Value |= 0x40;
			RTMP_IO_READ32(pAd, GPIO_CTRL_CFG, &Value);
			Value &= ~(0x0808);
			Value |= 0x08;
			RTMP_IO_WRITE32(pAd, GPIO_CTRL_CFG, Value);
			DBGPRINT_RAW(RT_DEBUG_TRACE, ("AsicSetRxAnt, switch to aux antenna\n"));
		}
	}
#endif /* BT_COEXISTENCE_SUPPORT */
#endif /* RTMP_MAC_PCI */
}

/*
	add by johnli, RF power sequence setup

	==========================================================================
	Description:

	Load RF normal operation-mode setup
	
	==========================================================================
 */
VOID RT5390LoadRFNormalModeSetup(
	IN PRTMP_ADAPTER 	pAd)
{
	UCHAR RFValue, bbpreg = 0;

	/* improve power consumption */
	RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R138, &bbpreg);
	
	if (pAd->Antenna.field.TxPath == 1)
	{
		/* turn off tx DAC_1 */
		bbpreg = (bbpreg | 0x20);
	}
	
	if (pAd->Antenna.field.RxPath == 1)
	{
		/* turn off tx ADC_1 */
		bbpreg &= (~0x2);
	}
	
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R138, bbpreg);
	
	RT30xxReadRFRegister(pAd, RF_R38, (PUCHAR)&RFValue);
	RFValue = ((RFValue & ~0x20) | 0x00); /* rx_lo1_en (enable RX LO1, 0: LO1 follows TR switch) */
	RT30xxWriteRFRegister(pAd, RF_R38, (UCHAR)RFValue);

	RT30xxReadRFRegister(pAd, RF_R39, (PUCHAR)&RFValue);
	RFValue = ((RFValue & ~0x80) | 0x00); /* rx_lo2_en (enable RX LO2, 0: LO2 follows TR switch) */
	RT30xxWriteRFRegister(pAd, RF_R39, (UCHAR)RFValue);

	/* Avoid data lost and CRC error */
	
	RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R4, &bbpreg);
	bbpreg = ((bbpreg & ~0x40) | 0x40); /* MAC interface control (MAC_IF_80M, 1: 80 MHz) */
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R4, bbpreg);

	RT30xxReadRFRegister(pAd, RF_R30, (PUCHAR)&RFValue);
	RFValue = ((RFValue & ~0x18) | 0x10); /* rxvcm (Rx BB filter VCM) */
	RT30xxWriteRFRegister(pAd, RF_R30, (UCHAR)RFValue);
}

/*
	==========================================================================
	Description:

	Load RF sleep-mode setup
	
	==========================================================================
 */
VOID RT5390LoadRFSleepModeSetup(
	IN PRTMP_ADAPTER 	pAd)
{
	UINT32 MACValue;
	UCHAR	rfreg;
		
	RT30xxReadRFRegister(pAd, RF_R01, &rfreg);
	rfreg = ((rfreg & ~0x01) | 0x00); /* vco_en */
	RT30xxWriteRFRegister(pAd, RF_R01, rfreg);

	RT30xxReadRFRegister(pAd, RF_R06, &rfreg);
	rfreg = ((rfreg & ~0xC0) | 0x00); /* vco_ic (VCO bias current control, 00: off) */
	RT30xxWriteRFRegister(pAd, RF_R06, rfreg);

	RT30xxReadRFRegister(pAd, RF_R22, &rfreg);
	rfreg = ((rfreg & ~0xE0) | 0x00); /* cp_ic (reference current control, 000: 0.25 mA) */
	RT30xxWriteRFRegister(pAd, RF_R22, rfreg);

	RT30xxReadRFRegister(pAd, RF_R42, &rfreg);
	rfreg = ((rfreg & ~0x40) | 0x00); /* rx_ctb_en */
	RT30xxWriteRFRegister(pAd, RF_R42, rfreg);

	RT30xxReadRFRegister(pAd, RF_R20, &rfreg);
	rfreg = ((rfreg & ~0x77) | 0x77); /* ldo_pll_vc and ldo_rf_vc (111: -0.15) */
	RT30xxWriteRFRegister(pAd, RF_R20, rfreg);
		
	/* Don't touch LDO_CFG0 for 3090F & 3593, possibly the board is single power scheme */
#if 0
	RTMP_IO_READ32(pAd, LDO_CFG0, &MACValue);
	MACValue |= 0x1D000000;
	RTMP_IO_WRITE32(pAd, LDO_CFG0, MACValue);
#endif
}

VOID RT5390HaltAction(
	IN PRTMP_ADAPTER 	pAd)
{
	UINT32 TxPinCfg = 0x00050F0F;
	
	/* Turn off LNA_PE or TRSW_POL */
	
	if ((IS_RT5390(pAd) || IS_RT5392(pAd))
#ifdef RTMP_EFUSE_SUPPORT
		&& (pAd->bUseEfuse)
#endif /* RTMP_EFUSE_SUPPORT */
		)
	{
		TxPinCfg &= 0xFFFBF0F0; /* bit18 off */
	}
	else
	{
		TxPinCfg &= 0xFFFFF0F0;
	}

	RTMP_IO_WRITE32(pAd, TX_PIN_CFG, TxPinCfg);   
}

/*
	==========================================================================
	Description:

	Reverse RF sleep-mode setup
	
	==========================================================================
 */
VOID RT5390ReverseRFSleepModeSetup(
	IN PRTMP_ADAPTER 	pAd,
	IN BOOLEAN			FlgIsInitState)
{
	UINT32 MACValue;
	UCHAR rfreg;

	RT30xxReadRFRegister(pAd, RF_R01, &rfreg);
	if (IS_RT5392(pAd))
	{
		rfreg = ((rfreg & ~0x3F) | 0x3F);
	}
	else
	{
		rfreg = ((rfreg & ~0x0F) | 0x0F); /* Enable rf_block_en, pll_en, rx0_en and tx0_en */
	}
	RT30xxWriteRFRegister(pAd, RF_R01, rfreg);
	
	RT30xxReadRFRegister(pAd, RF_R06, &rfreg);
	if (IS_RT5390F(pAd) || IS_RT5392C(pAd))
	{
		rfreg = ((rfreg & ~0xC0) | 0xC0); /* vco_ic (VCO bias current control, 11: high) */
	}
	else
	{
		rfreg = ((rfreg & ~0xC0) | 0x80); /* vco_ic (VCO bias current control, 10: mid.) */
	}
	RT30xxWriteRFRegister(pAd, RF_R06, rfreg);

	RT30xxReadRFRegister(pAd, RF_R02, &rfreg);
	rfreg = ((rfreg & ~0x80) | 0x80); /* rescal_en (initiate calibration) */
	RT30xxWriteRFRegister(pAd, RF_R02, rfreg);

	RT30xxReadRFRegister(pAd, RF_R22, &rfreg);
	rfreg = ((rfreg & ~0xE0) | 0x20); /* cp_ic (reference current control, 001: 0.33 mA) */
	RT30xxWriteRFRegister(pAd, RF_R22, rfreg);

	RT30xxReadRFRegister(pAd, RF_R42, &rfreg);
	rfreg = ((rfreg & ~0x40) | 0x40); /* rx_ctb_en */
	RT30xxWriteRFRegister(pAd, RF_R42, rfreg);
	
	RT30xxReadRFRegister(pAd, RF_R20, &rfreg);
	rfreg = ((rfreg & ~0x77) | 0x00); /* ldo_rf_vc and ldo_pll_vc ( 111: +0.15) */
	RT30xxWriteRFRegister(pAd, RF_R20, rfreg);
	
	RT30xxReadRFRegister(pAd, RF_R03, &rfreg);
	rfreg = ((rfreg & ~0x80) | 0x80); /* vcocal_en (initiate VCO calibration (reset after completion)) */
	RT30xxWriteRFRegister(pAd, RF_R03, rfreg);
#if 0
	/* RT3071 version E has fixed this issue */
	if ((pAd->NicConfig2.field.DACTestBit == 1) && ((pAd->MACVersion & 0xffff) < 0x0211))
	{
		/* patch tx EVM issue temporarily */
		RTMP_IO_READ32(pAd, LDO_CFG0, &MACValue);
		MACValue = ((MACValue & 0xE0FFFFFF) | 0x0D000000);
		RTMP_IO_WRITE32(pAd, LDO_CFG0, MACValue);
	}
#endif
}

VOID RT5390_RxSensitivityTuning(
	IN PRTMP_ADAPTER		pAd)
{
}

/*
========================================================================
Routine Description:
	Initialize specific MAC registers.

Arguments:
	pAd					- WLAN control block pointer

Return Value:
	None

Note:
========================================================================
*/
VOID NICInitRT5390MacRegisters(
	IN	PRTMP_ADAPTER 		pAd)
{
	UINT32 IdReg;

	for (IdReg=0; IdReg<RT5390_NUM_MAC_REG_PARMS; IdReg++)
	{
		RTMP_IO_WRITE32(pAd, RT5390_MACRegTable[IdReg].Register, RT5390_MACRegTable[IdReg].Value);
	}
}

/*
========================================================================
Routine Description:
	Initialize specific BBP registers.

Arguments:
	pAd					- WLAN control block pointer

Return Value:
	None

Note:
========================================================================
*/
VOID NICInitRT5390BbpRegisters(
	IN	PRTMP_ADAPTER 		pAd)
{
	UCHAR BbpReg = 0;
	BBP_R105_STRUC BBPR105 = { { 0 } };
	
	DBGPRINT(RT_DEBUG_TRACE, ("--> %s\n", __FUNCTION__));
	
	/*  The channel estimation updates based on remodulation of L-SIG and HT-SIG symbols. */
	
	RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R105, &BBPR105.byte);
	
	/* Apply Maximum Likelihood Detection (MLD) for 2 stream case (reserved field if single RX) */
	
	if (pAd->Antenna.field.RxPath == 1) /* Single RX */
		BBPR105.field.MLDFor2Stream = 0;
	else
		BBPR105.field.MLDFor2Stream = 1;
	
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R105, BBPR105.byte);

	DBGPRINT(RT_DEBUG_TRACE, ("%s: BBP_R105: BBPR105.field.EnableSIGRemodulation = %d, BBPR105.field.MLDFor2Stream = %d\n", 
		__FUNCTION__, 
		BBPR105.field.EnableSIGRemodulation, 
		BBPR105.field.MLDFor2Stream));

#if 0 /* Sync windows driver */
	/* Use 5 bit ADC for Acquisition: bit <7:6>=11 */
	RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R3, &BbpReg);
	BbpReg = (BbpReg | 0xc0);
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R3, BbpReg);
#endif	

	/* Avoid data lost and CRC error */		
	RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R4, &BbpReg);
	BbpReg = ((BbpReg & ~0x40) | 0x40); /* MAC interface control (MAC_IF_80M, 1: 80 MHz) */
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R4, BbpReg);
	
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R31, 0x08); /* ADC/DAC contro */
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R68, 0x0B); /* Rx AGC energy lower bound in log2 */
	
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R70, 0x0A); /* Rx AGC SQ CCK Xcorr threshold */
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R73, 0x13); /* Rx AGC SQ ACorr threshold */
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R75, 0x46); /* Rx high power VGA offset for LNA offset */
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R76, 0x28); /* Rx medium power VGA offset for LNA offset */
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R77, 0x59); /* Rx high/medium power threshold in log2 */
	
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R82, 0x62); /* Rx AGC LNA select threshold in log2 */
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R83, 0x7A); /* Rx AGC LNA MM select threshold in log2 */
		
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R84, 0x9A); /* Rx AGC VGA/LNA delay */
	
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R86, 0x38); /* Rx AGC high gain threshold in dB */

	if (IS_RT5392(pAd))
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R88, 0x90); /* Request by Gary 2011/11/23 */

	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R91, 0x04); /* Guard interval delay counter for 20M band */
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R92, 0x02); /* Guard interval delay counter for 40M band */

	if (IS_RT5392(pAd))
	{
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R95, 0x9A); /* CCK MRC decode */
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R98, 0x12); /* TX CCK higher gain */ 
	}

	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R103, 0xC0); /* Rx - 11b adaptive equalizer gear down control and signal energy average period */
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R104, 0x92); /* SIGN detection threshold/GF CDD control */
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R105, 0x3C); /* FEQ control */

	if (IS_RT5392(pAd))
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R106, 0x12); /* GI remover. For RX peak throughput enhancement. 2011/11/23 */
	else			
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R106, 0x03); /* GI remover */

	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R128, 0x12); /* R/W remodulation control */
	
	if (IS_RT5392(pAd))
	{
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R134, 0xD0); /* TX CCK higher gain */
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R135, 0xF6); /* TX CCK higher gain */ 
	}

#ifdef RT5390
#ifdef BT_COEXISTENCE_SUPPORT	
		if (IS_RT5390BC8(pAd)) /* 5390BC8 */
		{
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R75, 0x52); /* Rx high power VGA offset for LNA offset */
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R76, 0x34); /* Rx medium power VGA offset for LNA offset */
		}
		else
#endif /* BT_COEXISTENCE_SUPPORT */
		{
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R75, 0x4E); /* Rx high power VGA offset for LNA offset */
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R76, 0x30); /* Rx medium power VGA offset for LNA offset */
		}
#endif /* RT5390 */

#ifdef RT5390
#ifdef BT_COEXISTENCE_SUPPORT	
	if (IS_RT5390BC8(pAd))
	{
		RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R152, &BbpReg);
		BbpReg = ((BbpReg & ~0x80) | (0x80)); /* Main antenna */
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R152, BbpReg);

		DBGPRINT(RT_DEBUG_TRACE, ("%s: 5390BC8: Select the main antenna\n", __FUNCTION__));
	}
	else
#endif /* BT_COEXISTENCE_SUPPORT */
#endif /* RT5390 */	
	{
		if (pAd->NicConfig2.field.AntOpt == 1)
		{
			if (pAd->NicConfig2.field.AntDiversity == 0) /* 0: Main antenna */
			{
				RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R152, &BbpReg);
				BbpReg = ((BbpReg & ~0x80) | (0x80));
				RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R152, BbpReg);

				DBGPRINT(RT_DEBUG_TRACE, ("%s, switch to main antenna\n", __FUNCTION__));
			}
			else /* 1: Aux. antenna */
			{
				RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R152, &BbpReg);
				BbpReg = ((BbpReg & ~0x80) | (0x00));
				RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R152, BbpReg);

				DBGPRINT(RT_DEBUG_TRACE, ("%s, switch to aux. antenna\n", __FUNCTION__));
			}
		}
		else if (pAd->NicConfig2.field.AntDiversity == 0) /* Diversity is Off, set to Main Antenna as default */
		{
			RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R152, &BbpReg);
			BbpReg = ((BbpReg & ~0x80) | (0x80));
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R152, BbpReg);

			DBGPRINT(RT_DEBUG_TRACE, ("%s, switch to main antenna as default ...... 3\n", __FUNCTION__));
		}
	}

	if (IS_RT5390(pAd))
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R154, 0x0); /* Disable HW Antenna Diversity (5390/5370 only) */
	
	DBGPRINT(RT_DEBUG_TRACE, ("<-- %s\n", __FUNCTION__));
}

#ifdef CONFIG_STA_SUPPORT
/*
	==========================================================================
	Description:
		dynamic tune BBP R66 to find a balance between sensibility and 
		noise isolation

	IRQL = DISPATCH_LEVEL

	==========================================================================
 */
UCHAR RT5390_ChipAGCAdjust(
	IN PRTMP_ADAPTER		pAd,
	IN CHAR					Rssi,
	IN UCHAR				OrigR66Value)
{
	UCHAR R66 = OrigR66Value; /* R66UpperBound = 0x30, R66LowerBound = 0x30; */
	
	if (pAd->LatchRfRegs.Channel <= 14) /* BG band */
	{	
		R66 = 0x1C + 2*GET_LNA_GAIN(pAd);
		
		if (Rssi > RSSI_FOR_MID_LOW_SENSIBILITY)
			R66 += 0x20;
		
		if (OrigR66Value != R66)
		{
			rtmp_bbp_set_agc(pAd, R66, RX_CHAIN_ALL);
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R83, 0x4A);
		}
	}
	
	return R66;
}
#endif /* CONFIG_STA_SUPPORT */

VOID RT5390_ChipBBPAdjust(RTMP_ADAPTER *pAd)
{
	UINT32 Value;
	UCHAR rf_bw, bbp_val;
	INT ext_ch;


#ifdef DOT11_N_SUPPORT
	if (get_ht_cent_ch(pAd, &rf_bw, &ext_ch) == FALSE)
#endif /* DOT11_N_SUPPORT */
	{
		rf_bw = BW_20;
		ext_ch = EXTCHA_NONE;
		pAd->CommonCfg.CentralChannel = pAd->CommonCfg.Channel;
	}

	rtmp_bbp_set_bw(pAd, rf_bw);

	/*  TX/RX : control channel setting */ 
	rtmp_mac_set_ctrlch(pAd, ext_ch);
	rtmp_bbp_set_ctrlch(pAd, ext_ch);
	
	/* request by Gary 20070208 for middle and long range A/G Band */
#ifdef DOT11_N_SUPPORT
	if (rf_bw == BW_40)
		bbp_val = (pAd->CommonCfg.Channel > 14) ? 0x48 : 0x38;
	else
#endif /* DOT11_N_SUPPORT */
		bbp_val = (pAd->CommonCfg.Channel > 14) ? 0x40 : 0x38;
	rtmp_bbp_set_agc(pAd, bbp_val, RX_CHAIN_ALL);

	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R69, 0x12);
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R70, 0x0A);
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R73, 0x10);

#ifdef DOT11_N_SUPPORT
DBGPRINT(RT_DEBUG_TRACE, ("ApStartUp : 20MHz, ChannelWidth=%d, Channel=%d, ExtChanOffset=%d(%d) \n",
	pAd->CommonCfg.HtCapability.HtCapInfo.ChannelWidth, 
	pAd->CommonCfg.Channel, 
	pAd->CommonCfg.RegTransmitSetting.field.EXTCHA,
	pAd->CommonCfg.AddHTInfo.AddHtInfo.ExtChanOffset));
#endif /* DOT11_N_SUPPORT */

	/* request by Gary 20070208 for middle and long range G band */
	if (pAd->CommonCfg.Channel > 14)
		bbp_val = 0x1D;
	else
		bbp_val = 0x2D;
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R62, bbp_val);
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R63, bbp_val);
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R64, bbp_val);
	/* RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R86, bbp_val); */

}

VOID RT5390_ChipSwitchChannel(
	IN PRTMP_ADAPTER 		pAd,
	IN UCHAR				Channel,
	IN BOOLEAN				bScan) 
{
	CHAR    	TxPwer = 0, TxPwer2 = DEFAULT_RF_TX_POWER;
#ifdef DOT11N_SS3_SUPPORT
	CHAR    	TxPwer3 = 0;
#endif /* DOT11N_SS3_SUPPORT */
	UINT32 	Value = 0;
	UCHAR	index;
	UCHAR 	RFValue = 0;
	UCHAR 	TxRxh20M = 0;
	UCHAR 	PreRFValue = 0;
	UCHAR 	Tx0FinePowerCtrl = 0, Tx1FinePowerCtrl = 0;
	
#ifdef CONFIG_AP_SUPPORT
#ifdef AP_QLOAD_SUPPORT
	/* clear all statistics count for QBSS Load */
	QBSS_LoadStatusClear(pAd);
#endif /* AP_QLOAD_SUPPORT */
#endif /* CONFIG_AP_SUPPORT */

	/*
		Search Tx power value.
		We can't use ChannelList to search channel, since some central channl's txpowr doesn't list 
		in ChannelList, so use TxPower array instead.
	*/
	for (index = 0; index < MAX_NUM_OF_CHANNELS; index++)
	{
		if (Channel == pAd->TxPower[index].Channel)
		{
			TxPwer = pAd->TxPower[index].Power;
			TxPwer2 = pAd->TxPower[index].Power2;

			Tx0FinePowerCtrl = pAd->TxPower[index].Tx0FinePowerCtrl;
			Tx1FinePowerCtrl = pAd->TxPower[index].Tx1FinePowerCtrl;

			break;
		}
	}

	if (index == MAX_NUM_OF_CHANNELS)
	{
		DBGPRINT(RT_DEBUG_ERROR, ("%s(): Can't find the Channel#%d \n", __FUNCTION__, Channel));
	}
	
	for (index = 0; index < NUM_OF_3020_CHNL; index++)
	{
		if (Channel == FreqItems3020[index].Channel)
		{
#if 0 /* Based on windows driver */	
			/* Set the BBP Tx fine power control in 0.1dB step */
			
			BbpR109.field.Tx0PowerCtrl = Tx0FinePowerCtrl;
			BbpR109.field.Tx1PowerCtrl = 0;
			
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R109, BbpR109.byte);
#endif /* 0 */
			/* Programming channel parameters */
			RT30xxWriteRFRegister(pAd, RF_R08, FreqItems3020[index].N); /* N */
			RT30xxWriteRFRegister(pAd, RF_R09, (FreqItems3020[index].K & 0x0F)); /* K, N<11:8> is set to zero */

			RT30xxReadRFRegister(pAd, RF_R11, (PUCHAR)&RFValue);
			RFValue = ((RFValue & ~0x03) | (FreqItems3020[index].R & 0x03)); /* R */
			RT30xxWriteRFRegister(pAd, RF_R11, (UCHAR)RFValue);

			RT30xxReadRFRegister(pAd, RF_R49, (PUCHAR)&RFValue);
			RFValue = ((RFValue & ~0x3F) | (TxPwer & 0x3F)); /* tx0_alc */
			if ((RFValue & 0x3F) > 0x27) /* The valid range of the RF R49 (<5:0>tx0_alc<5:0>) is 0x00~0x27 */
			{
				RFValue = ((RFValue & ~0x3F) | 0x27);
			}
			RT30xxWriteRFRegister(pAd, RF_R49, (UCHAR)RFValue);

			if (IS_RT5392(pAd))
			{
				RT30xxReadRFRegister(pAd, RF_R50, &RFValue);
				RFValue = ((RFValue & ~0x3F) | (TxPwer2 & 0x3F)); /* tx0_alc */
				if ((RFValue & 0x3F) > 0x27) /* The valid range of the RF R49 (<5:0>tx0_alc<5:0>) is 0x00~0x27 */
				{
					RFValue = ((RFValue & ~0x3F) | 0x27);
				}
				RT30xxWriteRFRegister(pAd, RF_R50, RFValue);
			}

			RT30xxReadRFRegister(pAd, RF_R01, (PUCHAR)&RFValue);
			if (IS_RT5392(pAd))
			{
				RFValue = ((RFValue & ~0x3F) | 0x3F);
			}
			else
			{
				RFValue = ((RFValue & ~0x0F) | 0x0F); /* Enable rf_block_en, pll_en, rx0_en and tx0_en */
			}
			RT30xxWriteRFRegister(pAd, RF_R01, (UCHAR)RFValue);

			RT30xxReadRFRegister(pAd, RF_R02, (PUCHAR)&RFValue);
			RFValue |= 0x80;
			RT30xxWriteRFRegister(pAd, RF_R02, (UCHAR)RFValue);
			RTMPusecDelay(1000);
			RFValue &= 0x7F;
			RT30xxWriteRFRegister(pAd, RF_R02, (UCHAR)RFValue);   
							
#ifdef CONFIG_STA_SUPPORT
#ifdef RTMP_FREQ_CALIBRATION_SUPPORT
			if (pAd->FreqCalibrationCtrl.bEnableFrequencyCalibration == TRUE)
			{
			     	if (INFRA_ON(pAd)) /* Update the frequency offset from the adaptive frequency offset */
				{
					RT30xxReadRFRegister(pAd, RF_R17, (PUCHAR)&RFValue);
					PreRFValue = RFValue;
					/* xo_code (C1 value control) - Crystal calibration */
					RFValue = ((RFValue & ~0x7F) | (pAd->FreqCalibrationCtrl.AdaptiveFreqOffset & 0x7F)); 
					RFValue = min((INT)RFValue, 0x5F);
					if (PreRFValue != RFValue)
					{
						AsicSendCommandToMcu(pAd, 0x74, 0xff, RFValue, PreRFValue, FALSE);
					}
				}
				else /* Update the frequency offset from EEPROM */
				{
					RT30xxReadRFRegister(pAd, RF_R17, (PUCHAR)&RFValue);
					PreRFValue = RFValue;
					/* xo_code (C1 value control) - Crystal calibration */
					RFValue = ((RFValue & ~0x7F) | (pAd->RfFreqOffset & 0x7F)); 
					RFValue = min((INT)RFValue, 0x5F);
					if (PreRFValue != RFValue)
					{
						AsicSendCommandToMcu(pAd, 0x74, 0xff, RFValue, PreRFValue, FALSE);
					}
				}
			}
			else
#endif /* RTMP_FREQ_CALIBRATION_SUPPORT */					
#endif /* CONFIG_STA_SUPPORT */					
			{
				RT30xxReadRFRegister(pAd, RF_R17, (PUCHAR)&RFValue);
				PreRFValue = RFValue;
				/* xo_code (C1 value control) - Crystal calibration */
				RFValue = ((RFValue & ~0x7F) | (pAd->RfFreqOffset & 0x7F)); 
				RFValue = min((INT)RFValue, 0x5F);
				if (PreRFValue != RFValue)
				{
					AsicSendCommandToMcu(pAd, 0x74, 0xff, RFValue, PreRFValue, FALSE);
				}
			}

			if ((!bScan) && (pAd->CommonCfg.BBPCurrentBW == BW_40)) /* BW 40 */
			{
				TxRxh20M = ((pAd->Mlme.CaliBW40RfR24 & 0x20) >> 5); /* Tx/Rx h20M */
			}
			else /* BW 20 */
			{
				TxRxh20M = ((pAd->Mlme.CaliBW20RfR24 & 0x20) >> 5); /* Tx/Rx h20M */
			}
#ifdef BT_COEXISTENCE_SUPPORT				
			if (IS_RT5390BC8(pAd))
			{
				if (IS_RT5390F(pAd)) /* >= RT5390F */
				{
					if ((Channel >= 1) && (Channel <= 3))
					{
						RT30xxWriteRFRegister(pAd, RF_R55, 0x83);
					}
					else if ((Channel >= 4) && (Channel <= 5))
					{
						RT30xxWriteRFRegister(pAd, RF_R55, 0x73);
					}
					else if (Channel == 6)
					{
						RT30xxWriteRFRegister(pAd, RF_R55, 0x63);
					}
					else if ((Channel >= 7) && (Channel <= 9))
					{
						RT30xxWriteRFRegister(pAd, RF_R55, 0x53);
					}
					else if ((Channel >= 10) && (Channel <= 14))
					{
						RT30xxWriteRFRegister(pAd, RF_R55, 0x43);
					}
					
					if ((Channel >= 1) && (Channel <= 5))
					{
						RT30xxWriteRFRegister(pAd, RF_R59, 0x0E); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
					}
					else if (Channel == 6)
					{
						RT30xxWriteRFRegister(pAd, RF_R59, 0x0B); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
					}
					else if (Channel == 7)
					{
						RT30xxWriteRFRegister(pAd, RF_R59, 0x0A); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
					}
					else if (Channel == 8)
					{
						RT30xxWriteRFRegister(pAd, RF_R59, 0x09); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
					}
					else if ((Channel >= 9) && (Channel <= 14))
					{
						RT30xxWriteRFRegister(pAd, RF_R59, 0x07); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
					}
				}
				else
				{
					RT30xxWriteRFRegister(pAd, RF_R55, 0x44);
					
					if ((Channel >= 1) && (Channel <= 7))
					{
						RT30xxWriteRFRegister(pAd, RF_R59, 0x8B); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
					}
					else if (Channel == 8)
					{
						RT30xxWriteRFRegister(pAd, RF_R59, 0x8A); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
					}
					else if (Channel == 9)
					{
						RT30xxWriteRFRegister(pAd, RF_R59, 0x89); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
					}
					else if ((Channel >= 10) && (Channel <= 11))
					{
						RT30xxWriteRFRegister(pAd, RF_R59, 0x88); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
					}
					else if (Channel == 12)
					{
						RT30xxWriteRFRegister(pAd, RF_R59, 0x86); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
					}
					else if (Channel == 13)
					{
						RT30xxWriteRFRegister(pAd, RF_R59, 0x85); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
					}	
					else if (Channel == 14)
					{
						RT30xxWriteRFRegister(pAd, RF_R59, 0x84); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
					}
				}
			}
			else
#endif /* BT_COEXISTENCE_SUPPORT */
#ifdef RTMP_MAC_USB
			if (IS_RT5392(pAd)) /* RT5372 */
			{
				if (IS_RT5392C(pAd)) /* >= RT5372C */
				{
					if ((Channel >= 1) && (Channel <= 4)) /* channel 1~4 */
					{
						RT30xxWriteRFRegister(pAd, RF_R23, 0x0F);
					}
					else if ((Channel >= 5) && (Channel <= 7)) /* channel 5~7 */
					{
						RT30xxWriteRFRegister(pAd, RF_R23, 0x0E);
					}
					else if ((Channel >= 8) && (Channel <= 14)) /* channel 8~14 */
					{
						RT30xxWriteRFRegister(pAd, RF_R23, 0x0D);
					}
					
					if ((Channel >= 1) && (Channel <= 4)) /* channel 1~4 */
					{
						RT30xxWriteRFRegister(pAd, RF_R59, 0x0C);
					}
					else if (Channel == 5) /* channel 5 */
					{
						RT30xxWriteRFRegister(pAd, RF_R59, 0x0B);
					}
					else if ((Channel >= 6) && (Channel <= 7)) /* channel 6~7 */
					{
						RT30xxWriteRFRegister(pAd, RF_R59, 0x0A);
					}
					else if ((Channel >= 8) && (Channel <= 10)) /* channel 8~10 */
					{
						RT30xxWriteRFRegister(pAd, RF_R59, 0x09);
					}
					else if ((Channel >= 11) && (Channel <= 14)) /* channel 11~14 */
					{
						RT30xxWriteRFRegister(pAd, RF_R59, 0x08);
					}
				}
				else 
				{
					if ((Channel >= 1) && (Channel <= 11)) /* channel 1~11 */
					{
						RT30xxWriteRFRegister(pAd, RF_R59, 0x0F);
					}
					else if ((Channel >= 12) && (Channel <= 14)) /* channel 12~14 */
					{
						RT30xxWriteRFRegister(pAd, RF_R59, 0x0B);
					}
				}
			}
			else if (IS_RT5390U(pAd))
			{
				if ((Channel >= 1) && (Channel <= 4))
				{
					RT30xxWriteRFRegister(pAd, RF_R55, 0x23); /* txvga_cc and pa1_cc_cck */
				}
				else if ((Channel >= 5) && (Channel <= 6))
				{
					RT30xxWriteRFRegister(pAd, RF_R55, 0x13); /* txvga_cc and pa1_cc_cck */
				}
				else if ((Channel >= 7) && (Channel <= 14))
				{
					RT30xxWriteRFRegister(pAd, RF_R55, 0x03); /* txvga_cc and pa1_cc_cck */
				}			

				if ((Channel >= 1) && (Channel <= 10))
				{
					RT30xxWriteRFRegister(pAd, RF_R59, 0x07); /* pa2_cc_ofdm and pa1_cc_ofdm */
				}
				else if (Channel == 11)
				{
					RT30xxWriteRFRegister(pAd, RF_R59, 0x06); /* pa2_cc_ofdm and pa1_cc_ofdm */
				}
				else if (Channel == 12)
				{
					RT30xxWriteRFRegister(pAd, RF_R59, 0x05); /* pa2_cc_ofdm and pa1_cc_ofdm */
				}
				else if ((Channel >= 13) && (Channel <= 14))
				{
					RT30xxWriteRFRegister(pAd, RF_R59, 0x04); /* pa2_cc_ofdm and pa1_cc_ofdm */
				}
			}
			else if (IS_RT5390F(pAd) && !IS_MINI_CARD(pAd)) /* For RT5370F support */
			{
				if ((Channel >= 1) && (Channel <= 11))
				{
					RT30xxWriteRFRegister(pAd, RF_R55, 0x43); /* txvga_cc and pa1_cc_cck */
				}
				else if ((Channel >= 12) && (Channel <= 14))
				{
					RT30xxWriteRFRegister(pAd, RF_R55, 0x23); /* txvga_cc and pa1_cc_cck */
				}

				if ((Channel >= 1) && (Channel <= 11))
				{
					RT30xxWriteRFRegister(pAd, RF_R59, 0x0F); /* pa2_cc_ofdm and pa1_cc_ofdm */
				}
				else if (Channel == 12)
				{
					RT30xxWriteRFRegister(pAd, RF_R59, 0x0D); /* pa2_cc_ofdm and pa1_cc_ofdm */
				}
				else if ((Channel >= 13) && (Channel <= 14))
				{
					RT30xxWriteRFRegister(pAd, RF_R59, 0x0B); /* pa2_cc_ofdm and pa1_cc_ofdms */
				}
			}
			else
#endif /* RTMP_MAC_USB */
#ifdef RTMP_MAC_PCI 
			if (IS_RT5392(pAd)) /* RT5392 */
			{
			}
			else if (IS_RT5390H(pAd)) /* RT5390H */
			{
				if ((Channel >= 1) && (Channel <= 4))
				{
					RT30xxWriteRFRegister(pAd, RF_R55, 0x23);
				}
				else if ((Channel >= 5) && (Channel <= 6))
				{
					RT30xxWriteRFRegister(pAd, RF_R55, 0x13);	
				}	
				else if ((Channel >= 7) && (Channel <= 14))
				{
					RT30xxWriteRFRegister(pAd, RF_R55, 0x03);							
				}
			
				if ((Channel >= 1) && (Channel <= 3))
				{							
					RT30xxWriteRFRegister(pAd, RF_R59, 0x0F); 
				}
				else if ((Channel >= 4) && (Channel <= 5))
				{							
					RT30xxWriteRFRegister(pAd, RF_R59, 0x0E); 
				}
				else if (Channel == 6)
				{							
					RT30xxWriteRFRegister(pAd, RF_R59, 0x0C); 
				}
				else if (Channel == 7)
				{							
					RT30xxWriteRFRegister(pAd, RF_R59, 0x0B);
				}
				else if ((Channel >= 8) && (Channel <= 11))
				{							
					RT30xxWriteRFRegister(pAd, RF_R59, 0x09); 
				}
				else if ((Channel >= 12) && (Channel <= 13))
				{							
					RT30xxWriteRFRegister(pAd, RF_R59, 0x08);
				}
				else if (Channel == 14)
				{							
					RT30xxWriteRFRegister(pAd, RF_R59, 0x06);
				}
			}
			else if (IS_RT5390F(pAd)) /* >= RT5390F */
			{
				if ((Channel >= 1) && (Channel <= 4))
				{
					RT30xxWriteRFRegister(pAd, RF_R55, 0x23);
				}
				else if ((Channel >= 5) && (Channel <= 6))
				{
					RT30xxWriteRFRegister(pAd, RF_R55, 0x13);	
				}	
				else if ((Channel >= 7) && (Channel <= 14))
				{
					RT30xxWriteRFRegister(pAd, RF_R55, 0x03);							
				}
									
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
			}
			else if (IS_RT5390(pAd)) /* Only for RT5390 */
			{
				if ((Channel >= 1) && (Channel <= 4))
				{
					RT30xxWriteRFRegister(pAd, RF_R55, 0x73);
				}
				else if ((Channel >= 5) && (Channel <= 6))
				{
					RT30xxWriteRFRegister(pAd, RF_R55, 0x63);	
				}	
				else if ((Channel >= 7) && (Channel <= 10))
				{
					RT30xxWriteRFRegister(pAd, RF_R55, 0x53);							
				}
				else if ((Channel >= 11) && (Channel <= 14))
				{
					RT30xxWriteRFRegister(pAd, RF_R55, 0x43);							
				}

				if (Channel == 1)
				{							
					RT30xxWriteRFRegister(pAd, RF_R59, 0x0C); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
				}
				else if (Channel == 2)
				{							
					RT30xxWriteRFRegister(pAd, RF_R59, 0x0B); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
				}
				else if (Channel == 3)
				{							
					RT30xxWriteRFRegister(pAd, RF_R59, 0x0A); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
				}
				else if ((Channel >= 4) && (Channel <=6))
				{							
					RT30xxWriteRFRegister(pAd, RF_R59, 0x09); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
				}					
				else if ((Channel >= 7) && (Channel <=12))
				{							
					RT30xxWriteRFRegister(pAd, RF_R59, 0x08); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
				}	
				else if (Channel == 13)
				{							
					RT30xxWriteRFRegister(pAd, RF_R59, 0x07); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
				}
				else if (Channel == 14)
				{							
					RT30xxWriteRFRegister(pAd, RF_R59, 0x06); /* pa2_cc_ofdm<3:0> (PA2 Cascode Bias OFDM mode) */
				}
			}
#endif /* RTMP_MAC_PCI */

#ifdef RTMP_TEMPERATURE_COMPENSATION
			if (pAd->chipCap.bTempCompTxALC)
			{
				/*  Set RF_R27 */
				RT30xxReadRFRegister(pAd, RF_R27, &RFValue);

				/* Set [3:0] to TssiGain */
				RFValue = (RFValue & 0xf0);
				RFValue = (RFValue | pAd->TxPowerCtrl.TssiGain[IEEE80211_BAND_2G]);

				RT30xxWriteRFRegister(pAd, RF_R27, RFValue);
			}
#endif /* RTMP_TEMPERATURE_COMPENSATION */

#ifdef RELEASE_EXCLUDE
			/*
				Before Read RF_R30, we must clear the RFValue or the value will be incorrect.
				For example, in 53xx we always get 0x30 but the original correct value is 0x10. 
			*/
#endif /* RELEASE_EXCLUDE */
			RFValue=0;
			RT30xxReadRFRegister(pAd, RF_R30, (PUCHAR)&RFValue);
			RFValue = ((RFValue & ~0x06) | (TxRxh20M << 1) | (TxRxh20M << 2)); /* tx_h20M and rx_h20M */
			RT30xxWriteRFRegister(pAd, RF_R30, (UCHAR)RFValue);

			RT30xxReadRFRegister(pAd, RF_R30, (PUCHAR)&RFValue);
			RFValue = ((RFValue & ~0x18) | 0x10); /* rxvcm (Rx BB filter VCM) */
			RT30xxWriteRFRegister(pAd, RF_R30, (UCHAR)RFValue);

			RT30xxReadRFRegister(pAd, RF_R03, (PUCHAR)&RFValue);
			/* vcocal_en (initiate VCO calibration (reset after completion)) - It should be at the end of RF configuration. */
			RFValue = ((RFValue & ~0x80) | 0x80);
			RT30xxWriteRFRegister(pAd, RF_R03, (UCHAR)RFValue);					
			pAd->LatchRfRegs.Channel = Channel; /* Channel latch */

			DBGPRINT(RT_DEBUG_TRACE, ("%s: 5390: SwitchChannel#%d(RF=%d, Pwr0=%d, Pwr1=%d, %dT), N=0x%02X, K=0x%02X, R=0x%02X\n",
				__FUNCTION__, 
				Channel, 
				pAd->RfIcType, 
				TxPwer, 
				TxPwer2, 
				pAd->Antenna.field.TxPath, 
				FreqItems3020[index].N, 
				FreqItems3020[index].K, 
				FreqItems3020[index].R));

			break;
		}
	}

	/* Change BBP setting during siwtch from a->g, g->a */
	if (Channel <= 14)
	{
		ULONG	TxPinCfg = 0x00050F0A; /* Gary 2007/08/09 0x050A0A */

		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R62, (0x37 - GET_LNA_GAIN(pAd)));
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R63, (0x37 - GET_LNA_GAIN(pAd)));
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R64, (0x37 - GET_LNA_GAIN(pAd)));

		/* Rx High power VGA offset for LNA select */
		if (pAd->NicConfig2.field.ExternalLNAForG)
		{
#ifdef RTMP_MAC_USB
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R75, 0x52);
#else
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R75, 0x46);
#endif /* RTMP_MAC_USB */
		}
		else
		{
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R75, 0x50);
		}

		/* 5G band selection PIN, bit1 and bit2 are complement */
		RTMP_IO_READ32(pAd, TX_BAND_CFG, &Value);
		Value &= (~0x6);
		Value |= (0x04);
		RTMP_IO_WRITE32(pAd, TX_BAND_CFG, Value);

		/* Turn off unused PA or LNA when only 1T or 1R */
		if (pAd->Antenna.field.TxPath == 1)
		{
			TxPinCfg &= 0xFFFFFFF3;
		}
		
		if (pAd->Antenna.field.RxPath == 1)
		{
			TxPinCfg &= 0xFFFFF3FF;
		}
			
		RTMP_IO_WRITE32(pAd, TX_PIN_CFG, TxPinCfg);

		/* PCIe PHY Transmit attenuation adjustment */
		if (IS_PCIE_INF(pAd))
		{
			INTERNAL_1_STRUCT Internal_1 = { { 0 } };

			RTMP_IO_READ32(pAd, INTERNAL_1, &Internal_1.word);
#ifdef RELEASE_EXCLUDE
			/* 
				Explanation for #14 channel interference 
				
				RF(2.5GHz)

				---------

				Internal

				125Mhz/32Khz(PCIe power-saving)

				---------

				PCIe PHY(2.5Ghz for spec 1.x)


				All Ralink¡¦s PCIe devices have two external phy interfaces. One is RF which works in 2.5GHz in B/G 

				Modes and the other is PCIe Phy which creates p2p Lane with PCIe bus and works in 2.5GHz based on PCIe spec 1.x.


				When the channel is set to channel #14 under 20 MHz bandwidth, the maximum frequency is 

				equal to 2496 [2412(channel 1 central channel)+12*5( the space between channel 1 and 13)+

				12(the space between channel 13 and 14)=2484(the central channel of channel 14)+

				12MHz (bandwidth/2)]. The frequency is closed to 2.5GHz and bandwidth 40 MHz is closer.


				Because the Tx signal of PCIe PHY will feed back to RF PHY, if the frequency of the feed-back 

				signals from PCIe is closed to current working channel of RF PHY, the feed-back signal will be 

				mixed with the Rx signal of RF and interfere in the Rx of RF. 


				To solve this problem, we must degrade the power of PCIe Tx when devices switch to channel #14. 
			*/ 
#endif /* RELEASE_EXCLUDE */

			if (Channel == 14) /* Channel #14 */
			{
				Internal_1.field.PCIE_PHY_TX_ATTEN_EN = 1; /* Enable PCIe PHY Tx attenuation */
				Internal_1.field.PCIE_PHY_TX_ATTEN_VALUE = 4; /* 9/16 full drive level */
			}
			else /* Channel #1~#13 */
			{
				Internal_1.field.PCIE_PHY_TX_ATTEN_EN = 0; /* Disable PCIe PHY Tx attenuation */
				Internal_1.field.PCIE_PHY_TX_ATTEN_VALUE = 0; /* n/a */
			}

			RTMP_IO_WRITE32(pAd, INTERNAL_1, Internal_1.word);
		}

		rtmp_bbp_set_filter_coefficient_ctrl(pAd, Channel);
	}
	else
	{
		ULONG	TxPinCfg = 0x00050F05; /* Gary 2007/8/9 0x050505 */
		UINT8	bbpValue;
		
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R62, (0x37 - GET_LNA_GAIN(pAd)));
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R63, (0x37 - GET_LNA_GAIN(pAd)));
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R64, (0x37 - GET_LNA_GAIN(pAd)));

		/* Set the BBP_R82 value here */
		bbpValue = 0xF2;
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R82, bbpValue);

		/* Rx High power VGA offset for LNA select */
		if (pAd->NicConfig2.field.ExternalLNAForA)
		{
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R75, 0x46);
		}
		else
		{
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R75, 0x50);
		}

		/* 5G band selection PIN, bit1 and bit2 are complement */
		RTMP_IO_READ32(pAd, TX_BAND_CFG, &Value);
		Value &= (~0x6);
		Value |= (0x02);
		RTMP_IO_WRITE32(pAd, TX_BAND_CFG, Value);

		/* Turn off unused PA or LNA when only 1T or 1R */
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
	
#ifdef IQ_CAL_SUPPORT
	/* IQ Calibration */
	RTMP_CHIP_IQ_CAL(pAd, Channel);
#endif /* IQ_CAL_SUPPORT */

	/*
		On 11A, We should delay and wait RF/BBP to be stable
		and the appropriate time should be 1000 micro seconds 
		2005/06/05 - On 11G, We also need this delay time. Otherwise it's difficult to pass the WHQL.
	*/
	RTMPusecDelay(1000);  
}

#if 0 /* Move to chipOps.AsicBbpInit hook function (NICInitRT5390BbpRegisters) */
/*
 Post-process the BBP registers based on the chip model

 Parameters
	pAd: The adapter data structure

 Return Value
	None
*/
 VOID RT5390_PostBBPInitialization(
	IN PRTMP_ADAPTER pAd)
{
	UCHAR BbpReg = 0;
	BBP_R105_STRUC BBPR105 = { { 0 } };
/*	BBP_R106_STRUC BBPR106 = { { 0 } }; */
	
	DBGPRINT(RT_DEBUG_TRACE, ("--> %s\n", __FUNCTION__));

	
	/*  The channel estimation updates based on remodulation of L-SIG and HT-SIG symbols. */
	
	RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R105, &BBPR105.byte);
	
	 /* Apply Maximum Likelihood Detection (MLD) for 2 stream case (reserved field if single RX) */
	
	{
	if (pAd->Antenna.field.RxPath == 1) /* Single RX */
	{
		BBPR105.field.MLDFor2Stream = 0;
	}
	else
	{
		BBPR105.field.MLDFor2Stream = 1;
	}
	}
	RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R105, BBPR105.byte);

	DBGPRINT(RT_DEBUG_TRACE, ("%s: BBP_R105: BBPR105.field.EnableSIGRemodulation = %d, BBPR105.field.MLDFor2Stream = %d\n", 
		__FUNCTION__, 
		BBPR105.field.EnableSIGRemodulation, 
		BBPR105.field.MLDFor2Stream));

	{
#if 0	/* Sync windows driver */
		/* Use 5 bit ADC for Acquisition: bit <7:6>=11 */
		RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R3, &BbpReg);
		BbpReg = (BbpReg | 0xc0);
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R3, BbpReg);
#endif		
		/*   Avoid data lost and CRC error */		
		
		RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R4, &BbpReg);
		BbpReg = ((BbpReg & ~0x40) | 0x40); /* MAC interface control (MAC_IF_80M, 1: 80 MHz) */
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R4, BbpReg);
		
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R68, 0x0B); /* Rx AGC energy lower bound in log2 */
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R77, 0x59); /* Rx high/medium power threshold in log2 */
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R82, 0x62); /* Rx AGC LNA select threshold in log2 */
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R83, 0x7A); /* Rx AGC LNA MM select threshold in log2 */
		
		if (IS_RT5392(pAd))
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R84, 0x9A); /* Rx AGC VGA/LNA delay */
		else
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R84, 0x19); /* Rx AGC VGA/LNA delay */
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R86, 0x38); /* Rx AGC high gain threshold in dB */
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R91, 0x04); /* Guard interval delay counter for 20M band */
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R92, 0x02); /* Guard interval delay counter for 40M band */

		if (IS_RT5392(pAd))
		{
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R95, 0x9A); /* CCK MRC decode */
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R98, 0x12); /* TX CCK higher gain */ 
		}

		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R103, 0xC0); /* Rx - 11b adaptive equalizer gear down control and signal energy average period */
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R104, 0x92); /* SIGN detection threshold/GF CDD control */
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R105, 0x3C); /* FEQ control */
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R128, 0x12); /* R/W remodulation control */

		if (IS_RT5392(pAd))
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R106, 0x05); /* GI remover */
		else			
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R106, 0x03); /* GI remover */

		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R31, 0x08); /* ADC/DAC contro */
		
		if (IS_RT5392(pAd))
		{
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R134, 0xD0); /* TX CCK higher gain */
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R135, 0xF6); /* TX CCK higher gain */ 
		}
		
#ifdef RT5390
#ifdef BT_COEXISTENCE_SUPPORT	
		if (IS_RT5390BC8(pAd)) /* 5390BC8 */
		{
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R75, 0x52); /* Rx high power VGA offset for LNA offset */
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R76, 0x34); /* Rx medium power VGA offset for LNA offset */
		}
		else
#endif /* BT_COEXISTENCE_SUPPORT */
		{
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R75, 0x4E); /* Rx high power VGA offset for LNA offset */
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R76, 0x30); /* Rx medium power VGA offset for LNA offset */
		}
#endif /* RT5390 */

		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R75, 0x46); /* Rx high power VGA offset for LNA offset */
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R76, 0x28); /* Rx medium power VGA offset for LNA offset */
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R70, 0x0A); /* Rx AGC SQ CCK Xcorr threshold */
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R73, 0x13); /* Rx AGC SQ ACorr threshold */

	}
#ifdef RT5390
#ifdef BT_COEXISTENCE_SUPPORT	
	if (IS_RT5390BC8(pAd))
	{
		RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R152, &BbpReg);
		BbpReg = ((BbpReg & ~0x80) | (0x80)); /* Main antenna */
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R152, BbpReg);

		DBGPRINT(RT_DEBUG_TRACE, ("%s: 5390BC8: Select the main antenna\n", __FUNCTION__));
	}
	else
#endif /* BT_COEXISTENCE_SUPPORT */
#endif /* RT5390 */	
	{
			if (pAd->NicConfig2.field.AntOpt == 1)
			{
				if (pAd->NicConfig2.field.AntDiversity == 0) // 0: Main antenna
				{
					RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R152, &BbpReg);
					BbpReg = ((BbpReg & ~0x80) | (0x80));
					RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R152, BbpReg);

					DBGPRINT(RT_DEBUG_TRACE, ("%s, switch to main antenna\n", __FUNCTION__));
				}
				else // 1: Aux. antenna
				{
					RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R152, &BbpReg);
					BbpReg = ((BbpReg & ~0x80) | (0x00));
					RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R152, BbpReg);
	
					DBGPRINT(RT_DEBUG_TRACE, ("%s, switch to aux. antenna\n", __FUNCTION__));
				}
			}
			else if (pAd->NicConfig2.field.AntDiversity == 0)	// Diversity is Off, set to Main Antenna as default
			{
					RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R152, &BbpReg);
					BbpReg = ((BbpReg & ~0x80) | (0x80));
					RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R152, BbpReg);
	
					DBGPRINT(RT_DEBUG_TRACE, ("%s, switch to main antenna as default ...... 3\n", __FUNCTION__));
			}
		}
	DBGPRINT(RT_DEBUG_TRACE, ("<-- %s\n", __FUNCTION__));
}
#endif 

VOID RT539x_AsicExtraPowerOverMAC(
	IN	PRTMP_ADAPTER 		pAd)
{
	ULONG	ExtraPwrOverMAC = 0;
	ULONG	ExtraPwrOverTxPwrCfg7 = 0, ExtraPwrOverTxPwrCfg8 = 0, ExtraPwrOverTxPwrCfg9 = 0;

	/* For OFDM_54 and HT_MCS_7, extra fill the corresponding register value into MAC 0x13D4 */
	RTMP_IO_READ32(pAd, 0x1318, &ExtraPwrOverMAC);  
	ExtraPwrOverTxPwrCfg7 |= (ExtraPwrOverMAC & 0x0000FF00) >> 8; /* Get Tx power for OFDM 54 */
	RTMP_IO_READ32(pAd, 0x131C, &ExtraPwrOverMAC);  
	ExtraPwrOverTxPwrCfg7 |= (ExtraPwrOverMAC & 0x0000FF00) << 8; /* Get Tx power for HT MCS 7 */			
	RTMP_IO_WRITE32(pAd, TX_PWR_CFG_7, ExtraPwrOverTxPwrCfg7);

	/* For STBC_MCS_7, extra fill the corresponding register value into MAC 0x13DC */
	RTMP_IO_READ32(pAd, 0x1324, &ExtraPwrOverMAC);  
	ExtraPwrOverTxPwrCfg9 |= (ExtraPwrOverMAC & 0x0000FF00) >> 8; /* Get Tx power for STBC MCS 7 */
	RTMP_IO_WRITE32(pAd, TX_PWR_CFG_9, ExtraPwrOverTxPwrCfg9);

	if (IS_RT5392(pAd))
	{	
		/*  For HT_MCS_15, extra fill the corresponding register value into MAC 0x13DC */
		RTMP_IO_READ32(pAd, 0x1320, &ExtraPwrOverMAC);  
		ExtraPwrOverTxPwrCfg8 |= (ExtraPwrOverMAC & 0x0000FF00) >> 8; /* Get Tx power for HT MCS 15 */
		RTMP_IO_WRITE32(pAd, TX_PWR_CFG_8, ExtraPwrOverTxPwrCfg8);
		
		DBGPRINT(RT_DEBUG_TRACE, ("Offset =0x13D8, TxPwr = 0x%08X, ", (UINT)ExtraPwrOverTxPwrCfg8));
	}
	
	DBGPRINT(RT_DEBUG_TRACE, ("Offset = 0x13D4, TxPwr = 0x%08X, Offset = 0x13DC, TxPwr = 0x%08X\n", 
		(UINT)ExtraPwrOverTxPwrCfg7, 
		(UINT)ExtraPwrOverTxPwrCfg9));
}

#ifdef RTMP_INTERNAL_TX_ALC
VOID RT5390_InitDesiredTSSITable(
	IN PRTMP_ADAPTER			pAd)
{
	INT			i = 0;
	CHAR 		DesiredTssi = 0;
	CHAR 		BWPowerDelta = 0;
	UCHAR 		ch = 0;
	UCHAR 		index = 0;
	UCHAR 		BbpR47 = 0;
	UCHAR 		RFValue = 0;
	UCHAR 		TSSIBase = 0; /* The TSSI over OFDM 54Mbps */
	USHORT 		Value = 0;
	USHORT 		TxPower = 0, TxPowerOFDM54 = 0;
	BOOLEAN 	bExtendedTssiMode = FALSE;
	EEPROM_TX_PWR_OFFSET_STRUC TxPwrOffset = {{0}};

	if (pAd->TxPowerCtrl.bInternalTxALC == FALSE)
	{
		return;
	}

	DBGPRINT(RT_DEBUG_TRACE, ("---> %s\n", __FUNCTION__));

	if (IS_RT5390(pAd))
	{
		RT28xx_EEPROM_READ16(pAd, EEPROM_TXPOWER_DELTA, Value);
		
		if ((Value & 0xFF) == 0xFF) /* 20M/40M BW Power Delta for 2.4GHz band */
		{
			DBGPRINT(RT_DEBUG_TRACE, ("%s: Don't considerate 20M/40M BW Delta Power since EEPROM is not calibrated.\n", __FUNCTION__));
		}
		else
		{
			if ((Value & 0xC0) == 0xC0)
			{
				BWPowerDelta += (Value & 0x3F); /* increase 40M BW Tx power with the delta value */
			}
			else if ((Value & 0xC0) == 0x80)
			{
				BWPowerDelta -= (Value & 0x3F); /* decrease 40M BW Tx power with the delta value */
			}
			else
				DBGPRINT(RT_DEBUG_TRACE, ("%s: 20/40M BW Delta Power is not enabled, Value = 0x%X\n", __FUNCTION__, Value));
		}
		
		RT28xx_EEPROM_READ16(pAd, EEPROM_TSSI_OVER_OFDM_54, Value);

		TSSIBase = (Value & 0x007F); /* range: bit6~bit0 */	

		RT28xx_EEPROM_READ16(pAd, (EEPROM_TSSI_STEP_OVER_2DOT4G - 1), Value);
		if (((Value >> 8) & 0x80) == 0x80) /* Enable the extended TSSI mode */
		{
			bExtendedTssiMode = TRUE;
		}
		else
		{
			bExtendedTssiMode = FALSE;
		}

		if (bExtendedTssiMode == TRUE) /* Tx power offset for the extended TSSI mode */
		{
			pAd->TxPowerCtrl.bExtendedTssiMode = TRUE;

			/* Get the per-channel Tx power offset */
			
			RT28xx_EEPROM_READ16(pAd, (EEPROM_TX_POWER_OFFSET_OVER_CH_1 - 1), TxPwrOffset.word);
			pAd->TxPowerCtrl.PerChTxPwrOffset[1] = (TxPwrOffset.field.Byte1 & 0x0F); /* Tx power offset over channel 1 */
			pAd->TxPowerCtrl.PerChTxPwrOffset[2] = (((TxPwrOffset.field.Byte1 & 0xF0) >> 4) & 0x0F); /* Tx power offset over channel 2 */

			RT28xx_EEPROM_READ16(pAd, EEPROM_TX_POWER_OFFSET_OVER_CH_3, TxPwrOffset.word);
			pAd->TxPowerCtrl.PerChTxPwrOffset[3] = (TxPwrOffset.field.Byte0 & 0x0F); /* Tx power offset over channel 3 */
			pAd->TxPowerCtrl.PerChTxPwrOffset[4] = (((TxPwrOffset.field.Byte0 & 0xF0) >> 4) & 0x0F); /* Tx power offset over channel 4 */
			pAd->TxPowerCtrl.PerChTxPwrOffset[5] = (TxPwrOffset.field.Byte1 & 0x0F); /* Tx power offset over channel 5 */
			pAd->TxPowerCtrl.PerChTxPwrOffset[6] = (((TxPwrOffset.field.Byte1 & 0xF0) >> 4) & 0x0F); /* Tx power offset over channel 6 */

			RT28xx_EEPROM_READ16(pAd, EEPROM_TX_POWER_OFFSET_OVER_CH_7, TxPwrOffset.word);
			pAd->TxPowerCtrl.PerChTxPwrOffset[7] = (TxPwrOffset.field.Byte0 & 0x0F); /* Tx power offset over channel 7 */
			pAd->TxPowerCtrl.PerChTxPwrOffset[8] = (((TxPwrOffset.field.Byte0 & 0xF0) >> 4) & 0x0F); /* Tx power offset over channel 8 */
			pAd->TxPowerCtrl.PerChTxPwrOffset[9] = (TxPwrOffset.field.Byte1 & 0x0F); /* Tx power offset over channel 9 */
			pAd->TxPowerCtrl.PerChTxPwrOffset[10] = (((TxPwrOffset.field.Byte1 & 0xF0) >> 4) & 0x0F); /* Tx power offset over channel 10 */

			RT28xx_EEPROM_READ16(pAd, EEPROM_TX_POWER_OFFSET_OVER_CH_11, TxPwrOffset.word);
			pAd->TxPowerCtrl.PerChTxPwrOffset[11] = (TxPwrOffset.field.Byte0 & 0x0F); /* Tx power offset over channel 11 */
			pAd->TxPowerCtrl.PerChTxPwrOffset[12] = (((TxPwrOffset.field.Byte0 & 0xF0) >> 4) & 0x0F); /* Tx power offset over channel 12 */
			pAd->TxPowerCtrl.PerChTxPwrOffset[13] = (TxPwrOffset.field.Byte1 & 0x0F); /* Tx power offset over channel 13 */
			pAd->TxPowerCtrl.PerChTxPwrOffset[14] = (((TxPwrOffset.field.Byte1 & 0xF0) >> 4) & 0x0F); /* Tx power offset over channel 14 */

			/* 4-bit representation ==> 8-bit representation (2's complement) */
			
			for (i = 1; i <= NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET; i++)
			{
				if ((pAd->TxPowerCtrl.PerChTxPwrOffset[i] & 0x08) == 0x00) /* Positive number */
				{
					pAd->TxPowerCtrl.PerChTxPwrOffset[i] = (pAd->TxPowerCtrl.PerChTxPwrOffset[i] & ~0xF8);
				}
				else /* 0x08: Negative number */
				{
					pAd->TxPowerCtrl.PerChTxPwrOffset[i] = (pAd->TxPowerCtrl.PerChTxPwrOffset[i] | 0xF0);
				}
			}

			DBGPRINT(RT_DEBUG_TRACE, ("%s: TxPwrOffset[1] = %d, TxPwrOffset[2] = %d, TxPwrOffset[3] = %d, TxPwrOffset[4] = %d\n", 
				__FUNCTION__, 
				pAd->TxPowerCtrl.PerChTxPwrOffset[1], 
				pAd->TxPowerCtrl.PerChTxPwrOffset[2], 
				pAd->TxPowerCtrl.PerChTxPwrOffset[3], 
				pAd->TxPowerCtrl.PerChTxPwrOffset[4]));
			DBGPRINT(RT_DEBUG_TRACE, ("%s: TxPwrOffset[5] = %d, TxPwrOffset[6] = %d, TxPwrOffset[7] = %d, TxPwrOffset[8] = %d\n", 
				__FUNCTION__, 
				pAd->TxPowerCtrl.PerChTxPwrOffset[5], 
				pAd->TxPowerCtrl.PerChTxPwrOffset[6], 
				pAd->TxPowerCtrl.PerChTxPwrOffset[7], 
				pAd->TxPowerCtrl.PerChTxPwrOffset[8]));
			DBGPRINT(RT_DEBUG_TRACE, ("%s: TxPwrOffset[9] = %d, TxPwrOffset[10] = %d, TxPwrOffset[11] = %d, TxPwrOffset[12] = %d\n", 
				__FUNCTION__, 
				pAd->TxPowerCtrl.PerChTxPwrOffset[9], 
				pAd->TxPowerCtrl.PerChTxPwrOffset[10], 
				pAd->TxPowerCtrl.PerChTxPwrOffset[11], 
				pAd->TxPowerCtrl.PerChTxPwrOffset[12]));
			DBGPRINT(RT_DEBUG_TRACE, ("%s: TxPwrOffset[13] = %d, TxPwrOffset[14] = %d\n", 
				__FUNCTION__, 
				pAd->TxPowerCtrl.PerChTxPwrOffset[13], 
				pAd->TxPowerCtrl.PerChTxPwrOffset[14]));
		}
		else
		{
			pAd->TxPowerCtrl.bExtendedTssiMode = FALSE;
			RTMPZeroMemory(pAd->TxPowerCtrl.PerChTxPwrOffset, sizeof (pAd->TxPowerCtrl.PerChTxPwrOffset));
		}
		
		RT28xx_EEPROM_READ16(pAd, (EEPROM_OFDM_MCS6_MCS7 - 1), Value);
		TxPowerOFDM54 = (0x000F & (Value >> 8));

		DBGPRINT(RT_DEBUG_TRACE, ("%s: TSSIBase = 0x%X, TxPowerOFDM54 = 0x%X, , bExtendedTssiMode = %d\n", 
			__FUNCTION__, 
			TSSIBase, 
			TxPowerOFDM54,
			pAd->TxPowerCtrl.bExtendedTssiMode));

		/* The desired TSSI over CCK */

		DBGPRINT(RT_DEBUG_TRACE, ("%s: ------------------------------------------------------\n", __FUNCTION__));
		DBGPRINT(RT_DEBUG_TRACE, ("%s: The desired TSSI over CCK\n", __FUNCTION__));
		RT28xx_EEPROM_READ16(pAd, EEPROM_CCK_MCS0_MCS1, Value);
		TxPower = (Value & 0x000F);
		DBGPRINT(RT_DEBUG_TRACE, ("%s: eFuse 0xDE = 0x%X\n", __FUNCTION__, TxPower));

		for (ch = 1; ch <= NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET; ch++)
		{
			index = GET_TSSI_RATE_TABLE_INDEX(TxPower - TxPowerOFDM54 + 3 + pAd->TxPowerCtrl.PerChTxPwrOffset[ch] + TSSI_RATIO_TABLE_OFFSET);
			DesiredTssi = (SHORT)Rounding(pAd, (TSSIBase * TssiRatioTable[index][0] / TssiRatioTable[index][1]), (TSSIBase * TssiRatioTable[index][0] % TssiRatioTable[index][1]), TssiRatioTable[index][1]);
			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, index = %d, DesiredTssi = 0x%02X\n", __FUNCTION__, ch, index, DesiredTssi));
			
			/* Boundary verification: the desired TSSI value */
			
			if (DesiredTssi < 0x00)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));

				DesiredTssi = 0x00;
			}
			else if (DesiredTssi > 0x7C)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));

				DesiredTssi = 0x7C;
			}

			RT5390_desiredTSSIOverCCKExt[ch][MCS_0] = (CHAR)DesiredTssi;
			RT5390_desiredTSSIOverCCKExt[ch][MCS_1] = (CHAR)DesiredTssi;
		}
		
		RT28xx_EEPROM_READ16(pAd, (EEPROM_CCK_MCS2_MCS3 - 1), Value);
		TxPower = ((Value >> 8) & 0x000F);
		DBGPRINT(RT_DEBUG_TRACE, ("%s: eFuse 0xDF = 0x%X\n", __FUNCTION__, TxPower));		

		for (ch = 1; ch <= NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET; ch++)
		{
			index = GET_TSSI_RATE_TABLE_INDEX(TxPower - TxPowerOFDM54 + 3 + pAd->TxPowerCtrl.PerChTxPwrOffset[ch] + TSSI_RATIO_TABLE_OFFSET);
			DesiredTssi = (SHORT)Rounding(pAd, (TSSIBase * TssiRatioTable[index][0] / TssiRatioTable[index][1]), (TSSIBase * TssiRatioTable[index][0] % TssiRatioTable[index][1]), TssiRatioTable[index][1]);
			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, index = %d, DesiredTssi = 0x%02X\n", __FUNCTION__, ch, index, DesiredTssi));

			/* Boundary verification: the desired TSSI value */
			
			if (DesiredTssi < 0x00)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));
				
				DesiredTssi = 0x00;
			}
			else if (DesiredTssi > 0x7C)			
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));
				
				DesiredTssi = 0x7C;
			}

			RT5390_desiredTSSIOverCCKExt[ch][MCS_2] = (CHAR)DesiredTssi;
			RT5390_desiredTSSIOverCCKExt[ch][MCS_3] = (CHAR)DesiredTssi;
		}

		for (ch = 1; ch <= NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET; ch++)
		{
			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, RT5390_desiredTSSIOverCCK[%d][0] = %d, RT5390_desiredTSSIOverCCK[%d][1] = %d, RT5390_desiredTSSIOverCCK[%d][2] = %d, RT5390_desiredTSSIOverCCK[%d][3] = %d\n", 
				__FUNCTION__, 
				ch, 
				ch, 
				RT5390_desiredTSSIOverCCKExt[ch][0], 
				ch, 
				RT5390_desiredTSSIOverCCKExt[ch][1], 
				ch, 
				RT5390_desiredTSSIOverCCKExt[ch][2], 
				ch, 
				RT5390_desiredTSSIOverCCKExt[ch][3]));
		}
		
		/* The desired TSSI over OFDM */

		DBGPRINT(RT_DEBUG_TRACE, ("%s: ------------------------------------------------------\n", __FUNCTION__));
		DBGPRINT(RT_DEBUG_TRACE, ("%s: The desired TSSI over OFDM\n", __FUNCTION__));	
		RT28xx_EEPROM_READ16(pAd, EEPROM_OFDM_MCS0_MCS1, Value);
		TxPower = (Value & 0x000F);
		DBGPRINT(RT_DEBUG_TRACE, ("%s: eFuse 0xE0 = 0x%X\n", __FUNCTION__, TxPower));

		for (ch = 1; ch <= NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET; ch++)
		{
			index = GET_TSSI_RATE_TABLE_INDEX(TxPower - TxPowerOFDM54 + pAd->TxPowerCtrl.PerChTxPwrOffset[ch] + TSSI_RATIO_TABLE_OFFSET);
			DesiredTssi = (SHORT)Rounding(pAd, (TSSIBase * TssiRatioTable[index][0] / TssiRatioTable[index][1]), (TSSIBase * TssiRatioTable[index][0] % TssiRatioTable[index][1]), TssiRatioTable[index][1]);
			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, index = %d, DesiredTssi = 0x%02X\n", __FUNCTION__, ch, index, DesiredTssi));

			/* Boundary verification: the desired TSSI value */
			
			if (DesiredTssi < 0x00)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));
				
				DesiredTssi = 0x00;
			}
			else if (DesiredTssi > 0x7C)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));

				DesiredTssi = 0x7C;
			}

			RT5390_desiredTSSIOverOFDMExt[ch][MCS_0] = (CHAR)DesiredTssi;
			RT5390_desiredTSSIOverOFDMExt[ch][MCS_1] = (CHAR)DesiredTssi;
		}

		RT28xx_EEPROM_READ16(pAd, (EEPROM_OFDM_MCS2_MCS3 - 1), Value);
		TxPower = ((Value >> 8) & 0x000F);
		DBGPRINT(RT_DEBUG_TRACE, ("%s: eFuse 0xE1 = 0x%X\n", __FUNCTION__, TxPower));

		for (ch = 1; ch <= NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET; ch++)
		{
			index = GET_TSSI_RATE_TABLE_INDEX(TxPower - TxPowerOFDM54 + pAd->TxPowerCtrl.PerChTxPwrOffset[ch] + TSSI_RATIO_TABLE_OFFSET);
			DesiredTssi = (SHORT)Rounding(pAd, (TSSIBase * TssiRatioTable[index][0] / TssiRatioTable[index][1]), (TSSIBase * TssiRatioTable[index][0] % TssiRatioTable[index][1]), TssiRatioTable[index][1]);
			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, index = %d, DesiredTssi = 0x%02X\n", __FUNCTION__, ch, index, DesiredTssi));

			/* Boundary verification: the desired TSSI value */
			
			if (DesiredTssi < 0x00)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));
				
				DesiredTssi = 0x00;
			}
			else if (DesiredTssi > 0x7C)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));

				DesiredTssi = 0x7C;
			}

			RT5390_desiredTSSIOverOFDMExt[ch][MCS_2] = (CHAR)DesiredTssi;
			RT5390_desiredTSSIOverOFDMExt[ch][MCS_3] = (CHAR)DesiredTssi;
		}
		
		RT28xx_EEPROM_READ16(pAd, EEPROM_OFDM_MCS4_MCS5, Value);
		TxPower = (Value & 0x000F);
		DBGPRINT(RT_DEBUG_TRACE, ("%s: eFuse 0xE2 = 0x%X\n", __FUNCTION__, TxPower));

		for (ch = 1; ch <= NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET; ch++)
		{
			index = GET_TSSI_RATE_TABLE_INDEX(TxPower - TxPowerOFDM54 + pAd->TxPowerCtrl.PerChTxPwrOffset[ch] + TSSI_RATIO_TABLE_OFFSET);
			DesiredTssi = (SHORT)Rounding(pAd, (TSSIBase * TssiRatioTable[index][0] / TssiRatioTable[index][1]), (TSSIBase * TssiRatioTable[index][0] % TssiRatioTable[index][1]), TssiRatioTable[index][1]);
			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, index = %d, DesiredTssi = 0x%02X\n", __FUNCTION__, ch, index, DesiredTssi));

			/* Boundary verification: the desired TSSI value */
			
			if (DesiredTssi < 0x00)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));
				
				DesiredTssi = 0x00;
			}
			else if (DesiredTssi > 0x7C)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));

				DesiredTssi = 0x7C;
			}

			RT5390_desiredTSSIOverOFDMExt[ch][MCS_4] = (CHAR)DesiredTssi;
			RT5390_desiredTSSIOverOFDMExt[ch][MCS_5] = (CHAR)DesiredTssi;

			index = GET_TSSI_RATE_TABLE_INDEX(pAd->TxPowerCtrl.PerChTxPwrOffset[ch] + TSSI_RATIO_TABLE_OFFSET);
			DesiredTssi = (SHORT)Rounding(pAd, (TSSIBase * TssiRatioTable[index][0] / TssiRatioTable[index][1]), (TSSIBase * TssiRatioTable[index][0] % TssiRatioTable[index][1]), TssiRatioTable[index][1]);
			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, index = %d, DesiredTssi = 0x%02X\n", __FUNCTION__, ch, index, DesiredTssi));
			
			/* Boundary verification: the desired TSSI value */
			
			if (DesiredTssi < 0x00)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));
				
				DesiredTssi = 0x00;
			}
			else if (DesiredTssi > 0x7C)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));

				DesiredTssi = 0x7C;
			}

			RT5390_desiredTSSIOverOFDMExt[ch][MCS_6] = (CHAR)DesiredTssi;
			RT5390_desiredTSSIOverOFDMExt[ch][MCS_7] =(CHAR) DesiredTssi;
		}
		
		for (ch = 1; ch <= NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET; ch++)
		{
			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, desiredTSSIOverOFDM[%d][0] = %d, desiredTSSIOverOFDM[%d][1] = %d, desiredTSSIOverOFDM[%d][2] = %d, desiredTSSIOverOFDM[%d][3] = %d\n", 
				__FUNCTION__, 
				ch, 
				ch, 
				RT5390_desiredTSSIOverOFDMExt[ch][0], 
				ch, 
				RT5390_desiredTSSIOverOFDMExt[ch][1], 
				ch, 
				RT5390_desiredTSSIOverOFDMExt[ch][2], 
				ch, 
				RT5390_desiredTSSIOverOFDMExt[ch][3]));
			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, desiredTSSIOverOFDM[%d][4] = %d, desiredTSSIOverOFDM[%d][5] = %d, desiredTSSIOverOFDM[[%d]6] = %d, desiredTSSIOverOFDM[%d][7] = %d\n", 
				__FUNCTION__, 
				ch, 
				ch, 
				RT5390_desiredTSSIOverOFDMExt[ch][4], 
				ch, 
				RT5390_desiredTSSIOverOFDMExt[ch][5], 
				ch, 
				RT5390_desiredTSSIOverOFDMExt[ch][6], 
				ch, 
				RT5390_desiredTSSIOverOFDMExt[ch][7]));
		}

		/* The desired TSSI over HT */

		DBGPRINT(RT_DEBUG_TRACE, ("%s: ------------------------------------------------------\n", __FUNCTION__));
		DBGPRINT(RT_DEBUG_TRACE, ("%s: The desired TSSI over HT\n", __FUNCTION__));		
		RT28xx_EEPROM_READ16(pAd, EEPROM_HT_MCS0_MCS1, Value);
		TxPower = (Value & 0x000F);
		DBGPRINT(RT_DEBUG_TRACE, ("%s: eFuse 0xE4 = 0x%X\n", __FUNCTION__, TxPower));

		for (ch = 1; ch <= NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET; ch++)
		{
			index = GET_TSSI_RATE_TABLE_INDEX(TxPower - TxPowerOFDM54 + pAd->TxPowerCtrl.PerChTxPwrOffset[ch] + TSSI_RATIO_TABLE_OFFSET + BWPowerDelta);
			DesiredTssi = (SHORT)Rounding(pAd, (TSSIBase * TssiRatioTable[index][0] / TssiRatioTable[index][1]), (TSSIBase * TssiRatioTable[index][0] % TssiRatioTable[index][1]), TssiRatioTable[index][1]);
			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, index = %d, DesiredTssi = 0x%02X\n", __FUNCTION__, ch, index, DesiredTssi));
			
			/* Boundary verification: the desired TSSI value */
		
			if (DesiredTssi < 0x00)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));
				
				DesiredTssi = 0x00;
			}
			else if (DesiredTssi > 0x7C)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));

				DesiredTssi = 0x7C;
			}
			
			RT5390_desiredTSSIOverHTExt[ch][MCS_0] = (CHAR)DesiredTssi;
			RT5390_desiredTSSIOverHTExt[ch][MCS_1] = (CHAR)DesiredTssi;
		}
		
		RT28xx_EEPROM_READ16(pAd, (EEPROM_HT_MCS2_MCS3 - 1), Value);
		TxPower = ((Value >> 8) & 0x000F);
		DBGPRINT(RT_DEBUG_TRACE, ("%s: eFuse 0xE5 = 0x%X\n", __FUNCTION__, TxPower));

		for (ch = 1; ch <= NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET; ch++)
		{
			index = GET_TSSI_RATE_TABLE_INDEX(TxPower - TxPowerOFDM54 + pAd->TxPowerCtrl.PerChTxPwrOffset[ch] + TSSI_RATIO_TABLE_OFFSET + BWPowerDelta);
			DesiredTssi = (SHORT)Rounding(pAd, (TSSIBase * TssiRatioTable[index][0] / TssiRatioTable[index][1]), (TSSIBase * TssiRatioTable[index][0] % TssiRatioTable[index][1]), TssiRatioTable[index][1]);
			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, index = %d, DesiredTssi = 0x%02X\n", __FUNCTION__, ch, index, DesiredTssi));
			
			/* Boundary verification: the desired TSSI value */
			
			if (DesiredTssi < 0x00)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));
				
				DesiredTssi = 0x00;
			}
			else if (DesiredTssi > 0x7C)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));

				DesiredTssi = 0x7C;
			}
			
			RT5390_desiredTSSIOverHTExt[ch][MCS_2] = (CHAR)DesiredTssi;
			RT5390_desiredTSSIOverHTExt[ch][MCS_3] = (CHAR)DesiredTssi;
		}

		RT28xx_EEPROM_READ16(pAd, EEPROM_HT_MCS4_MCS5, Value);
		TxPower = (Value & 0x000F);
		DBGPRINT(RT_DEBUG_TRACE, ("%s: eFuse 0xE6 = 0x%X\n", __FUNCTION__, TxPower));
		
		for (ch = 1; ch <= NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET; ch++)
		{
			index = GET_TSSI_RATE_TABLE_INDEX(TxPower - TxPowerOFDM54 + pAd->TxPowerCtrl.PerChTxPwrOffset[ch] + TSSI_RATIO_TABLE_OFFSET + BWPowerDelta);
			DesiredTssi = (SHORT)Rounding(pAd, (TSSIBase * TssiRatioTable[index][0] / TssiRatioTable[index][1]), (TSSIBase * TssiRatioTable[index][0] % TssiRatioTable[index][1]), TssiRatioTable[index][1]);
			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, index = %d, DesiredTssi = 0x%02X\n", __FUNCTION__, ch, index, DesiredTssi));

			/* Boundary verification: the desired TSSI value */
			
			if (DesiredTssi < 0x00)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));
				
				DesiredTssi = 0x00;
			}
			else if (DesiredTssi > 0x7C)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));

				DesiredTssi = 0x7C;
			}
			
			RT5390_desiredTSSIOverHTExt[ch][MCS_4] = (CHAR)DesiredTssi;
			RT5390_desiredTSSIOverHTExt[ch][MCS_5] = (CHAR)DesiredTssi;
		}

		RT28xx_EEPROM_READ16(pAd, (EEPROM_HT_MCS6_MCS7 - 1), Value);
		TxPower = ((Value >> 8) & 0x000F);
		DBGPRINT(RT_DEBUG_TRACE, ("%s: eFuse 0xE7 = 0x%X\n", __FUNCTION__, TxPower));

		for (ch = 1; ch <= NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET; ch++)
		{
			index = GET_TSSI_RATE_TABLE_INDEX(TxPower - TxPowerOFDM54 + pAd->TxPowerCtrl.PerChTxPwrOffset[ch] + TSSI_RATIO_TABLE_OFFSET + BWPowerDelta);
			DesiredTssi = (SHORT)Rounding(pAd, (TSSIBase * TssiRatioTable[index][0] / TssiRatioTable[index][1]), (TSSIBase * TssiRatioTable[index][0] % TssiRatioTable[index][1]), TssiRatioTable[index][1]);
			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, index = %d, DesiredTssi = 0x%02X\n", __FUNCTION__, ch, index, DesiredTssi));

			/* Boundary verification: the desired TSSI value */
			
			if (DesiredTssi < 0x00)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));
				
				DesiredTssi = 0x00;
			}
			else if (DesiredTssi > 0x7C)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));

				DesiredTssi = 0x7C;
			}
			
			RT5390_desiredTSSIOverHTExt[ch][MCS_6] = (CHAR)DesiredTssi;
			RT5390_desiredTSSIOverHTExt[ch][MCS_7] = (CHAR)DesiredTssi;
		}
		
		for (ch = 1; ch <= NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET; ch++)
		{
			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, desiredTSSIOverHT[%d][0] = %d, desiredTSSIOverHT[%d][1] = %d, desiredTSSIOverHT[%d][2] = %d, desiredTSSIOverHT[%d][3] = %d\n", 
				__FUNCTION__, 
				ch, 
				ch, 
				RT5390_desiredTSSIOverHTExt[ch][0], 
				ch, 
				RT5390_desiredTSSIOverHTExt[ch][1], 
				ch, 
				RT5390_desiredTSSIOverHTExt[ch][2], 
				ch, 
				RT5390_desiredTSSIOverHTExt[ch][3]));
			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, desiredTSSIOverHT[%d][4] = %d, desiredTSSIOverHT[%d][5] = %d, desiredTSSIOverHT[%d][6] = %d, desiredTSSIOverHT[%d][7] = %d\n", 
				__FUNCTION__, 
				ch, 
				ch, 
				RT5390_desiredTSSIOverHTExt[ch][4], 
				ch, 
				RT5390_desiredTSSIOverHTExt[ch][5], 
				ch, 
				RT5390_desiredTSSIOverHTExt[ch][6], 
				ch, 
				RT5390_desiredTSSIOverHTExt[ch][7]));
		}

		/* Calcuate the desired TSSI over HT for MCS 5, 6 and 7 in BW40 */
		
		DBGPRINT(RT_DEBUG_TRACE, ("%s: Calculate the desired TSSI over HT for MCS 5, 6 and 7 in BW40\n", __FUNCTION__));
		RT28xx_EEPROM_READ16(pAd, EEPROM_HT_MCS4_MCS5, Value);
		TxPower = (Value & 0x000F);
		DBGPRINT(RT_DEBUG_TRACE, ("%s: eFuse 0xE6 = 0x%X\n", __FUNCTION__, TxPower));
		
		for (ch = 1; ch <= NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET; ch++)
		{
			index = GET_TSSI_RATE_TABLE_INDEX(TxPower - TxPowerOFDM54 + pAd->TxPowerCtrl.PerChTxPwrOffset[ch] - 1 + TSSI_RATIO_TABLE_OFFSET);
			DesiredTssi = (SHORT)Rounding(pAd, (TSSIBase * TssiRatioTable[index][0] / TssiRatioTable[index][1]), (TSSIBase * TssiRatioTable[index][0] % TssiRatioTable[index][1]), TssiRatioTable[index][1]);
			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, index = %d, DesiredTssi = 0x%02X\n", __FUNCTION__, ch, index, DesiredTssi));

			/* Boundary verification: the desired TSSI value */

			if (DesiredTssi < 0x00)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));
				
				DesiredTssi = 0x00;
			}
			else if (DesiredTssi > 0x7C)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));

				DesiredTssi = 0x7C;
			}
			
			RT5390_desiredTSSIOverHT40Ext[ch][MCS_5] = (CHAR)DesiredTssi;
		}
		
		RT28xx_EEPROM_READ16(pAd, (EEPROM_HT_MCS6_MCS7 - 1), Value);
		TxPower = ((Value >> 8) & 0x000F);
		DBGPRINT(RT_DEBUG_TRACE, ("%s: eFuse 0xE7 = 0x%X\n", __FUNCTION__, TxPower));
		
		for (ch = 1; ch <= NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET; ch++)
		{
			index = GET_TSSI_RATE_TABLE_INDEX(TxPower - TxPowerOFDM54 + pAd->TxPowerCtrl.PerChTxPwrOffset[ch] - 1 + TSSI_RATIO_TABLE_OFFSET + BWPowerDelta);
			DesiredTssi = (SHORT)Rounding(pAd, (TSSIBase * TssiRatioTable[index][0] / TssiRatioTable[index][1]), (TSSIBase * TssiRatioTable[index][0] % TssiRatioTable[index][1]), TssiRatioTable[index][1]);
			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, index = %d, DesiredTssi = 0x%02X\n", __FUNCTION__, ch, index, DesiredTssi));

			/* Boundary verification: the desired TSSI value */

			if (DesiredTssi < 0x00)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));
				
				DesiredTssi = 0x00;
			}
			else if (DesiredTssi > 0x7C)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));

				DesiredTssi = 0x7C;
			}

			RT5390_desiredTSSIOverHT40Ext[ch][MCS_6] = (CHAR)DesiredTssi;
			RT5390_desiredTSSIOverHT40Ext[ch][MCS_7] = (CHAR)DesiredTssi;
		}

		for (ch = 1; ch <= NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET; ch++)
		{
			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, desiredTSSIOverHT40[%d][0] = %d, desiredTSSIOverHT40[%d][1] = %d, desiredTSSIOverHT40[%d][2] = %d, desiredTSSIOverHT40[%d][3] = %d\n", 
				__FUNCTION__, 
				ch, 
				ch, 
				RT5390_desiredTSSIOverHT40Ext[ch][0], 
				ch, 
				RT5390_desiredTSSIOverHT40Ext[ch][1], 
				ch, 
				RT5390_desiredTSSIOverHT40Ext[ch][2], 
				ch, 
				RT5390_desiredTSSIOverHT40Ext[ch][3]));
			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, desiredTSSIOverHT40[%d][4] = %d, desiredTSSIOverHT40[%d][5] = %d, desiredTSSIOverHT40[%d][6] = %d, desiredTSSIOverHT40[%d][7] = %d\n", 
				__FUNCTION__, 
				ch, 
				ch, 
				RT5390_desiredTSSIOverHT40Ext[ch][4], 
				ch, 
				RT5390_desiredTSSIOverHT40Ext[ch][5], 
				ch, 
				RT5390_desiredTSSIOverHT40Ext[ch][6], 
				ch, 
				RT5390_desiredTSSIOverHT40Ext[ch][7]));
		}
		
		/* The desired TSSI over HT using STBC */

		DBGPRINT(RT_DEBUG_TRACE, ("%s: ------------------------------------------------------\n", __FUNCTION__));
		DBGPRINT(RT_DEBUG_TRACE, ("%s: The desired TSSI over HT using STBC\n", __FUNCTION__));
		RT28xx_EEPROM_READ16(pAd, EEPROM_HT_USING_STBC_MCS0_MCS1, Value);
		TxPower = (Value & 0x000F);
		DBGPRINT(RT_DEBUG_TRACE, ("%s: eFuse 0xEC = 0x%X\n", __FUNCTION__, TxPower));

		for (ch = 1; ch <= NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET; ch++)
		{
			index = GET_TSSI_RATE_TABLE_INDEX(TxPower - TxPowerOFDM54 + pAd->TxPowerCtrl.PerChTxPwrOffset[ch] + TSSI_RATIO_TABLE_OFFSET);
			DesiredTssi = (SHORT)Rounding(pAd, (TSSIBase * TssiRatioTable[index][0] / TssiRatioTable[index][1]), (TSSIBase * TssiRatioTable[index][0] % TssiRatioTable[index][1]), TssiRatioTable[index][1]);
			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, index = %d, DesiredTssi = 0x%02X\n", __FUNCTION__, ch, index, DesiredTssi));
			
			/* Boundary verification: the desired TSSI value */
			
			if (DesiredTssi < 0x00)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));
				
				DesiredTssi = 0x00;
			}
			else if (DesiredTssi > 0x7C)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));

				DesiredTssi = 0x7C;
			}
			
			RT5390_desiredTSSIOverHTUsingSTBCExt[ch][MCS_0] = (CHAR)DesiredTssi;
			RT5390_desiredTSSIOverHTUsingSTBCExt[ch][MCS_1] = (CHAR)DesiredTssi;
		}

		RT28xx_EEPROM_READ16(pAd, (EEPROM_HT_USING_STBC_MCS2_MCS3 - 1), Value);
		TxPower = ((Value >> 8) & 0x000F);
		DBGPRINT(RT_DEBUG_TRACE, ("%s: eFuse 0xED = 0x%X\n", __FUNCTION__, TxPower));

		for (ch = 1; ch <= NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET; ch++)
		{
			index = GET_TSSI_RATE_TABLE_INDEX(TxPower - TxPowerOFDM54 + pAd->TxPowerCtrl.PerChTxPwrOffset[ch] + TSSI_RATIO_TABLE_OFFSET);
			DesiredTssi = (SHORT)Rounding(pAd, (TSSIBase * TssiRatioTable[index][0] / TssiRatioTable[index][1]), (TSSIBase * TssiRatioTable[index][0] % TssiRatioTable[index][1]), TssiRatioTable[index][1]);
			DBGPRINT(RT_DEBUG_TRACE, ("%s:ch = %d, index = %d, DesiredTssi = 0x%02X\n", __FUNCTION__, ch, index, DesiredTssi));

			/* Boundary verification: the desired TSSI value */
			
			if (DesiredTssi < 0x00)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));
				
				DesiredTssi = 0x00;
			}
			else if (DesiredTssi > 0x7C)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));

				DesiredTssi = 0x7C;
			}
			
			RT5390_desiredTSSIOverHTUsingSTBCExt[ch][MCS_2] = (CHAR)DesiredTssi;
			RT5390_desiredTSSIOverHTUsingSTBCExt[ch][MCS_3] = (CHAR)DesiredTssi;
		}

		RT28xx_EEPROM_READ16(pAd, EEPROM_HT_USING_STBC_MCS4_MCS5, Value);
		TxPower = (Value & 0x000F);
		DBGPRINT(RT_DEBUG_TRACE, ("%s: eFuse 0xEE = 0x%X\n", __FUNCTION__, TxPower));

		for (ch = 1; ch <= NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET; ch++)
		{
			index = GET_TSSI_RATE_TABLE_INDEX(TxPower - TxPowerOFDM54 + pAd->TxPowerCtrl.PerChTxPwrOffset[ch] + TSSI_RATIO_TABLE_OFFSET);
			DesiredTssi = (SHORT)Rounding(pAd, (TSSIBase * TssiRatioTable[index][0] / TssiRatioTable[index][1]), (TSSIBase * TssiRatioTable[index][0] % TssiRatioTable[index][1]), TssiRatioTable[index][1]);
			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, index = %d, DesiredTssi = 0x%02X\n", __FUNCTION__, ch, index, DesiredTssi));

			/* Boundary verification: the desired TSSI value */
			
			if (DesiredTssi < 0x00)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));
				
				DesiredTssi = 0x00;
			}
			else if (DesiredTssi > 0x7C)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));

				DesiredTssi = 0x7C;
			}
			
			RT5390_desiredTSSIOverHTUsingSTBCExt[ch][MCS_4] = (CHAR)DesiredTssi;
			RT5390_desiredTSSIOverHTUsingSTBCExt[ch][MCS_5] = (CHAR)DesiredTssi;
		}

		RT28xx_EEPROM_READ16(pAd, (EEPROM_HT_USING_STBC_MCS6_MCS7 - 1), Value);
		TxPower = ((Value >> 8) & 0x000F);
		DBGPRINT(RT_DEBUG_TRACE, ("%s: eFuse 0xEF = 0x%X\n", __FUNCTION__, TxPower));

		for (ch = 1; ch <= NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET; ch++)
		{
			index = GET_TSSI_RATE_TABLE_INDEX(TxPower - TxPowerOFDM54 + pAd->TxPowerCtrl.PerChTxPwrOffset[ch] + TSSI_RATIO_TABLE_OFFSET);
			DesiredTssi = (SHORT)Rounding(pAd, (TSSIBase * TssiRatioTable[index][0] / TssiRatioTable[index][1]), (TSSIBase * TssiRatioTable[index][0] % TssiRatioTable[index][1]), TssiRatioTable[index][1]);
			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, index = %d, DesiredTssi = 0x%02X\n", __FUNCTION__, ch, index, DesiredTssi));

			/* Boundary verification: the desired TSSI value */
			
			if (DesiredTssi < 0x00)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));
				
				DesiredTssi = 0x00;
			}
			else if (DesiredTssi > 0x7C)
			{
				DBGPRINT(RT_DEBUG_TRACE, ("%s: Out of range, DesiredTssi = 0x%02X\n", 
					__FUNCTION__, 
					DesiredTssi));

				DesiredTssi = 0x7C;
			}
			
			RT5390_desiredTSSIOverHTUsingSTBCExt[ch][MCS_6] = (CHAR)DesiredTssi;
			RT5390_desiredTSSIOverHTUsingSTBCExt[ch][MCS_7] = (CHAR)DesiredTssi;
		}
		
		for (ch = 1; ch <= NUM_OF_CH_FOR_PER_CH_TX_PWR_OFFSET; ch++)
		{
			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, desiredTSSIOverHTUsingSTBC[%d][0] = %d, desiredTSSIOverHTUsingSTBC[%d][1] = %d, desiredTSSIOverHTUsingSTBC[%d][2] = %d, desiredTSSIOverHTUsingSTBC[%d][3] = %d\n", 
				__FUNCTION__, 
				ch, 
				ch, 
				RT5390_desiredTSSIOverHTUsingSTBCExt[ch][0], 
				ch, 
				RT5390_desiredTSSIOverHTUsingSTBCExt[ch][1], 
				ch, 
				RT5390_desiredTSSIOverHTUsingSTBCExt[ch][2], 
				ch, 
				RT5390_desiredTSSIOverHTUsingSTBCExt[ch][3]));
			
			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, desiredTSSIOverHTUsingSTBC[%d][4] = %d, desiredTSSIOverHTUsingSTBC[%d][5] = %d, desiredTSSIOverHTUsingSTBC[%d][6] = %d, desiredTSSIOverHTUsingSTBC[%d][7] = %d\n", 
				__FUNCTION__, 
				ch, 
				ch, 
				RT5390_desiredTSSIOverHTUsingSTBCExt[ch][4], 
				ch, 
				RT5390_desiredTSSIOverHTUsingSTBCExt[ch][5], 
				ch, 
				RT5390_desiredTSSIOverHTUsingSTBCExt[ch][6], 
				ch, 
				RT5390_desiredTSSIOverHTUsingSTBCExt[ch][7]));
		}

		/* 5390 RF TSSI configuraiton */
		
		RT30xxReadRFRegister(pAd, RF_R28, (PUCHAR)(&RFValue));
		RFValue = 0;
		RT30xxWriteRFRegister(pAd, RF_R28, RFValue);

		RT30xxReadRFRegister(pAd, RF_R29, (PUCHAR)(&RFValue));
		RFValue = ((RFValue & ~0x03) | 0x00);
		RT30xxWriteRFRegister(pAd, RF_R29, RFValue);

		RT30xxReadRFRegister(pAd, RF_R27, (PUCHAR)(&RFValue));
		RFValue = (RFValue & ~0xFC); /* [7:4] = 0, [3:2] = 0 */
		RFValue = (RFValue | 0x03); /* [1:0] = 0x03 (tssi_gain = 12dB) */
		RT30xxWriteRFRegister(pAd, RF_R27, RFValue);
		
		RT28xx_EEPROM_READ16(pAd, EEPROM_TSSI_GAIN_AND_ATTENUATION,Value);
		Value = (Value & 0x00FF);
		DBGPRINT(RT_DEBUG_TRACE, ("%s: EEPROM_TSSI_GAIN_AND_ATTENUATION = 0x%X\n", 
			__FUNCTION__, 
			Value));

		if ((Value != 0x00) && (Value != 0xFF))
		{
			RT30xxReadRFRegister(pAd, RF_R27, (PUCHAR)(&RFValue));
			Value = (Value & 0x000F);
			RFValue = ((RFValue & 0xF0) | Value); /* [3:0] = (tssi_gain and tssi_atten) */
			RT30xxWriteRFRegister(pAd, RF_R27, RFValue);
		}
		
		/* 5390 BBP TSSI configuration */
		
		RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R47, &BbpR47);
		BbpR47 = ((BbpR47 & ~0x80) | 0x80); /* ADC6 on */
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R47, BbpR47);
		
		RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R47, &BbpR47);
		BbpR47 = ((BbpR47 & ~0x18) | 0x10); /* TSSI_MODE (new averaged TSSI mode for 3290/5390) */
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R47, BbpR47);

		RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R47, &BbpR47);
		BbpR47 = ((BbpR47 & ~0x07) | 0x04); /* TSSI_REPORT_SEL (TSSI INFO 0 - TSSI) and enable TSSI INFO udpate */
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R47, BbpR47);	
	}
	
	DBGPRINT(RT_DEBUG_TRACE, ("<--- %s\n", __FUNCTION__));
}

VOID RT5390_AsicTxAlcGetAutoAgcOffset(
	IN PRTMP_ADAPTER 			pAd,
	IN PCHAR					pDeltaPwr,
	IN PCHAR					pTotalDeltaPwr,
	IN PCHAR					pAgcCompensate,
	IN PCHAR 					pDeltaPowerByBbpR1)
{
	const TX_POWER_TUNING_ENTRY_STRUCT *TxPowerTuningTable = pAd->chipCap.TxPowerTuningTable_2G;
	PTX_POWER_TUNING_ENTRY_STRUCT pTxPowerTuningEntry = NULL;
	UCHAR 			RFValue = 0;
	CHAR 			desiredTssi = 0;
	CHAR 			currentTssi = 0;
	CHAR 			TotalDeltaPower = 0; 
	CHAR			TuningTableIndex = 0;
	CHAR			TX0_DAC = 0;
	RTMP_CHIP_CAP 	*pChipCap = &pAd->chipCap;
	
	/* Locate the Internal Tx ALC tuning entry */
	if ((pAd->TxPowerCtrl.bInternalTxALC == TRUE) && (IS_RT5390(pAd)))
	{
		if ((pAd->Mlme.OneSecPeriodicRound % 4 == 0) && (*pDeltaPowerByBbpR1 == 0))
		{
			if (GetDesiredTssiAndCurrentTssi(pAd, &desiredTssi, &currentTssi) == FALSE)
			{
				DBGPRINT(RT_DEBUG_ERROR, ("%s: Incorrect desired TSSI or current TSSI\n", __FUNCTION__));
				
				/* Tx power adjustment over RF */
				RT30xxReadRFRegister(pAd, RF_R49, (PUCHAR)(&RFValue));
				RFValue = ((RFValue & ~0x3F) | pAd->TxPowerCtrl.RF_TX_ALC);
				if ((RFValue & 0x3F) > 0x27) /* The valid range of the RF R49 (<5:0>tx0_alc<5:0>) is 0x00~0x27 */
				{
					RFValue = ((RFValue & ~0x3F) | 0x27);
				}
				RT30xxWriteRFRegister(pAd, RF_R49, (UCHAR)(RFValue));

				/* Tx power adjustment over MAC */
				TotalDeltaPower += pAd->TxPowerCtrl.MAC_PowerDelta;
			}
			else
			{
#ifdef DOT11_N_SUPPORT				
				TX0_DAC = pAd->TxPower[pAd->CommonCfg.CentralChannel-1].Power;
#else
				TX0_DAC = pAd->TxPower[pAd->CommonCfg.Channel-1].Power;
#endif /* DOT11_N_SUPPORT */

				if (pChipCap->bLimitPowerRange == FALSE)
				{
				if (desiredTssi > currentTssi)
				{
					pAd->TxPowerCtrl.idxTxPowerTable++;
				}

				if (desiredTssi < currentTssi)
				{
					pAd->TxPowerCtrl.idxTxPowerTable--;
					}				
				}
				else /* Enable the limit power compensation range */
				{
					if ((desiredTssi > currentTssi) && (pAd->TxPowerCtrl.idxTxPowerTable < 4))
				{
						pAd->TxPowerCtrl.idxTxPowerTable++;
				}

					if (desiredTssi < currentTssi) /* No compensation limitation on negative side */
				{
						pAd->TxPowerCtrl.idxTxPowerTable--;
					}

					DBGPRINT(RT_DEBUG_TRACE, ("Tssi antenna variation: idxTxPowerTable=%d\n", pAd->TxPowerCtrl.idxTxPowerTable));
				}
				
				TuningTableIndex = pAd->TxPowerCtrl.idxTxPowerTable + TX0_DAC;

				TuningTableIndex = (TuningTableIndex < LOWERBOUND_TX_POWER_TUNING_ENTRY) ? 
									LOWERBOUND_TX_POWER_TUNING_ENTRY : TuningTableIndex;
				TuningTableIndex = (TuningTableIndex > UPPERBOUND_TX_POWER_TUNING_ENTRY(pAd)) ? 
									UPPERBOUND_TX_POWER_TUNING_ENTRY(pAd) : TuningTableIndex;	

				/* Valide pAd->TxPowerCtrl.idxTxPowerTable: -30 ~ 69 */
				pTxPowerTuningEntry = &TxPowerTuningTable[TuningTableIndex + TX_POWER_TUNING_ENTRY_OFFSET ];

				pAd->TxPowerCtrl.RF_TX_ALC = pTxPowerTuningEntry->RF_TX_ALC;
				pAd->TxPowerCtrl.MAC_PowerDelta = pTxPowerTuningEntry->MAC_PowerDelta;

				/* Tx power adjustment over RF */
				RT30xxReadRFRegister(pAd, RF_R49, (PUCHAR)(&RFValue));
				RFValue = ((RFValue & ~0x3F) | pAd->TxPowerCtrl.RF_TX_ALC);
				if ((RFValue & 0x3F) > 0x27) /* The valid range of the RF R49 (<5:0>tx0_alc<5:0>) is 0x00~0x1F */
				{
					RFValue = ((RFValue & ~0x3F) | 0x27);
				}
				RT30xxWriteRFRegister(pAd, RF_R49, (UCHAR)(RFValue));

				/* Tx power adjustment over MAC */
				TotalDeltaPower += pAd->TxPowerCtrl.MAC_PowerDelta;

				DBGPRINT(RT_DEBUG_TRACE, ("%s: desiredTSSI = %d, currentTSSI = %d, idxTxPowerTable = %d, TuningTableIndex = %d, {RF_TX_ALC = 0x%X, MAC_PowerDelta = %d}\n", 
					__FUNCTION__, 
					desiredTssi, 
					currentTssi, 
					pAd->TxPowerCtrl.idxTxPowerTable, 
					TuningTableIndex,
					pTxPowerTuningEntry->RF_TX_ALC, 
					pTxPowerTuningEntry->MAC_PowerDelta));
			}
		}
		else
		{
			/* Tx power adjustment over RF */
			RT30xxReadRFRegister(pAd, RF_R49, (PUCHAR)(&RFValue));
			RFValue = ((RFValue & ~0x3F) | pAd->TxPowerCtrl.RF_TX_ALC);
			if ((RFValue & 0x3F) > 0x27) /* The valid range of the RF R49 (<5:0>tx0_alc<5:0>) is 0x00~0x1F */
			{
				RFValue = ((RFValue & ~0x3F) | 0x27);
			}
			RT30xxWriteRFRegister(pAd, RF_R49, (UCHAR)(RFValue));

			/* Tx power adjustment over MAC */
			TotalDeltaPower += pAd->TxPowerCtrl.MAC_PowerDelta;
		}
	}

	*pTotalDeltaPwr = TotalDeltaPower;
}

/*
   Rounding to integer
   e.g., +16.9 ~= 17 and -16.9 ~= -17

   Parameters
	  pAd: The adapter data structure
	  Integer: Integer part
	  Fraction: Fraction part
	  DenominatorOfTssiRatio: The denominator of the TSSI ratio

    Return Value:
	  Rounding result
*/
LONG Rounding(
	IN PRTMP_ADAPTER 			pAd, 
	IN LONG 						Integer, 
	IN LONG 						Fraction, 
	IN LONG 						DenominatorOfTssiRatio)
{
	LONG temp = 0;

	DBGPRINT(RT_DEBUG_INFO, ("%s: Integer = %d, Fraction = %d, DenominatorOfTssiRatio = %d\n", 
		__FUNCTION__, 
		(INT)Integer, 
		(INT)Fraction, 
		(INT)DenominatorOfTssiRatio));

	if (Fraction >= 0)
	{
		if (Fraction < (DenominatorOfTssiRatio / 10))
		{
			return Integer; /* e.g., 32.08059 ~= 32 */
		}
	}
	else
	{
		if (-Fraction < (DenominatorOfTssiRatio / 10))
		{
			return Integer; /* e.g., -32.08059 ~= -32 */
		}
	}

	if (Integer >= 0)
	{
		if (Fraction == 0)
		{
			return Integer;
		}
		else
		{
			do {
/*
 Coverity found the condition (Fration ==0) will not be executed, after line 3378.
*/
#if 0
				if (Fraction == 0)
				{
					break;
				}
				else
#endif
				{
					temp = Fraction / 10;
					if (temp == 0)
					{
						break;
					}
					else
					{
						Fraction = temp;
					}
				}
			} while (1);

			DBGPRINT(RT_DEBUG_INFO, ("%s: [+] temp = %d, Fraction = %d\n", __FUNCTION__, (INT)temp, (INT)Fraction));

			if (Fraction >= 5)
			{
				return (Integer + 1);
			}
			else
			{
				return Integer;
			}
		}
	}
	else
	{
		if (Fraction == 0)
		{
			return Integer;
		}
		else
		{
			do {
				if (Fraction == 0)
				{
					break;
				}
				else
				{
					temp = Fraction / 10;
					if (temp == 0)
					{
						break;
					}
					else
					{
						Fraction = temp;
					}
				}
			} while (1);

			DBGPRINT(RT_DEBUG_INFO, ("%s: [-] temp = %d, Fraction = %d\n", __FUNCTION__, (INT)temp, (INT)Fraction));

			if (Fraction <= -5)
			{
				return (Integer - 1);
			}
			else
			{
				return Integer;
			}
		}
	}
}

/*
   Get the desired TSSI based on the latest packet

   Parameters
	  pAd: The adapter data structure
	  pDesiredTssi: The desired TSSI
	  pCurrentTssi: The current TSSI/
	
   Return Value:
	  Success or failure
*/
BOOLEAN GetDesiredTssiAndCurrentTssi(
	IN 		PRTMP_ADAPTER 		pAd, 
	IN OUT 	PCHAR 				pDesiredTssi, 
	IN OUT 	PCHAR 				pCurrentTssi)
{
	UCHAR BbpR47 = 0;
	UCHAR RateInfo = 0;
	CCK_TSSI_INFO cckTssiInfo = {{0}};
	OFDM_TSSI_INFO ofdmTssiInfo = {{0}};
	HT_TSSI_INFO htTssiInfo = {
			.PartA.value= 0,
			.PartB.value = 0,
		};

	UCHAR ch=0;

	DBGPRINT(RT_DEBUG_INFO, ("---> %s\n", __FUNCTION__));

	if (IS_RT5390(pAd))
	{
		RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R47, &BbpR47);
		if ((BbpR47 & 0x04) == 0x04) /* The TSSI INFO is not ready. */
		{
			DBGPRINT(RT_DEBUG_ERROR, ("%s: BBP TSSI INFO is not ready. (BbpR47 = 0x%X)\n", __FUNCTION__, BbpR47));

			return FALSE;
		}
		
		/* Get TSSI */
		
		RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R49, (PUCHAR)(pCurrentTssi));

		if ((*pCurrentTssi < 0) || (*pCurrentTssi > 0x7C))
		{
			DBGPRINT(RT_DEBUG_ERROR, ("%s: Out of range, *pCurrentTssi = %d\n", __FUNCTION__, *pCurrentTssi));
			
			*pCurrentTssi = 0;
		}

		DBGPRINT(RT_DEBUG_TRACE, ("%s: *pCurrentTssi = %d\n", __FUNCTION__, *pCurrentTssi));
		
		/* Get packet information */
		
		RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R47, &BbpR47);
		BbpR47 = ((BbpR47 & ~0x03) | 0x01); /* TSSI_REPORT_SEL (TSSI INFO 1 - Packet infomation) */
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R47, BbpR47);

		RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R49, (PUCHAR)(&RateInfo));

		if ((RateInfo & 0x03) == MODE_CCK) /* CCK */
		{
			cckTssiInfo.value = RateInfo;

			DBGPRINT(RT_DEBUG_TRACE, ("%s: CCK, cckTssiInfo.field.Rate = %d\n", 
				__FUNCTION__, 
				cckTssiInfo.field.Rate));

			DBGPRINT(RT_DEBUG_INFO, ("%s: RateInfo = 0x%X\n", __FUNCTION__, RateInfo));

			if (((cckTssiInfo.field.Rate >= 4) && (cckTssiInfo.field.Rate <= 7)) || 
			      (cckTssiInfo.field.Rate > 11)) /* boundary verification */
			{
				DBGPRINT(RT_DEBUG_ERROR, ("%s: incorrect MCS: cckTssiInfo.field.Rate = %d\n", 
					__FUNCTION__, 
					cckTssiInfo.field.Rate));
				
				return FALSE;
			}

			/* Data rate mapping for short/long preamble over CCK */
			if (cckTssiInfo.field.Rate == 8)
			{
				cckTssiInfo.field.Rate = 0; /* Short preamble CCK 1Mbps => Long preamble CCK 1Mbps */
			}
			else if (cckTssiInfo.field.Rate == 9)
			{
				cckTssiInfo.field.Rate = 1; /* Short preamble CCK 2Mbps => Long preamble CCK 2Mbps */
			}
			else if (cckTssiInfo.field.Rate == 10)
			{
				cckTssiInfo.field.Rate = 2; /* Short preamble CCK 5.5Mbps => Long preamble CCK 5.5Mbps */
			}
			else if (cckTssiInfo.field.Rate == 11)
			{
				cckTssiInfo.field.Rate = 3; /* Short preamble CCK 11Mbps => Long preamble CCK 11Mbps */
			}

			if ((pAd->CommonCfg.CentralChannel >= 1) && (pAd->CommonCfg.CentralChannel <= 14))
			{
				ch = pAd->CommonCfg.CentralChannel;
			}
			else
			{
				ch = 1;

				DBGPRINT(RT_DEBUG_ERROR, ("%s: Incorrect channel #%d\n", __FUNCTION__, pAd->CommonCfg.CentralChannel));
			}
		
			*pDesiredTssi = RT5390_desiredTSSIOverCCKExt[ch][cckTssiInfo.field.Rate];

			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, *pDesiredTssi = %d\n", __FUNCTION__, ch, *pDesiredTssi));

		}
		else if ((RateInfo & 0x03) == MODE_OFDM) /* OFDM */
		{
			ofdmTssiInfo.value = RateInfo;
			
			/* BBP OFDM rate format ==> MAC OFDM rate format */
			
			switch (ofdmTssiInfo.field.Rate)
			{
				case 0x0B: /* 6 Mbits/s */
				{
					ofdmTssiInfo.field.Rate = MCS_0;
				}
				break;

				case 0x0F: /* 9 Mbits/s */
				{
					ofdmTssiInfo.field.Rate = MCS_1;
				}
				break;

				case 0x0A: /* 12 Mbits/s */
				{
					ofdmTssiInfo.field.Rate = MCS_2;
				}
				break;

				case 0x0E: /* 18  Mbits/s */
				{
					ofdmTssiInfo.field.Rate = MCS_3;
				}
				break;

				case 0x09: /* 24  Mbits/s */
				{
					ofdmTssiInfo.field.Rate = MCS_4;
				}
				break;

				case 0x0D: /* 36  Mbits/s */
				{
					ofdmTssiInfo.field.Rate = MCS_5;
				}
				break;

				case 0x08: /* 48  Mbits/s */
				{
					ofdmTssiInfo.field.Rate = MCS_6;
				}
				break;

				case 0x0C: /* 54  Mbits/s */
				{
					ofdmTssiInfo.field.Rate = MCS_7;
				}
				break;

				default: 
				{
					DBGPRINT(RT_DEBUG_ERROR, ("%s: Incorrect OFDM rate = 0x%X\n", __FUNCTION__, ofdmTssiInfo.field.Rate));
					
					return FALSE;
				}
				break;
			}

			DBGPRINT(RT_DEBUG_TRACE, ("%s: OFDM, ofdmTssiInfo.field.Rate = %d\n", 
				__FUNCTION__, 
				ofdmTssiInfo.field.Rate));

			if ((ofdmTssiInfo.field.Rate < 0) || (ofdmTssiInfo.field.Rate > 7)) /* boundary verification */
			{
				DBGPRINT(RT_DEBUG_ERROR, ("%s: incorrect MCS: ofdmTssiInfo.field.Rate = %d\n", 
					__FUNCTION__, 
					ofdmTssiInfo.field.Rate));

				return FALSE;
			}

			if ((pAd->CommonCfg.CentralChannel >= 1) && (pAd->CommonCfg.CentralChannel <= 14))
			{
				ch = pAd->CommonCfg.CentralChannel;
			}
			else
			{
				ch = 1;

				DBGPRINT(RT_DEBUG_ERROR, ("%s: Incorrect channel #%d\n", __FUNCTION__, pAd->CommonCfg.CentralChannel));
			}

			*pDesiredTssi = RT5390_desiredTSSIOverOFDMExt[ch][ofdmTssiInfo.field.Rate];

			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, *pDesiredTssi = %d\n", __FUNCTION__, ch, *pDesiredTssi));
			
			DBGPRINT(RT_DEBUG_INFO, ("%s: RateInfo = 0x%X\n", __FUNCTION__, RateInfo));
		}
		else /* Mixed mode or green-field mode */
		{
			htTssiInfo.PartA.value = RateInfo;
			DBGPRINT(RT_DEBUG_INFO, ("%s: RateInfo = 0x%X\n", __FUNCTION__, RateInfo));

			RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R47, &BbpR47);
			BbpR47 = ((BbpR47 & ~0x03) | 0x02); /* TSSI_REPORT_SEL (TSSI INFO 2 - Packet infomation) */
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R47, 0x92);
			RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R49, (PUCHAR)(&RateInfo));

			htTssiInfo.PartB.value = RateInfo;
			DBGPRINT(RT_DEBUG_INFO, ("%s: RateInfo = 0x%X\n", __FUNCTION__, RateInfo));

			DBGPRINT(RT_DEBUG_TRACE, ("%s: HT, htTssiInfo.PartA.field.STBC = %d, htTssiInfo.PartB.field.MCS = %d\n", 
				__FUNCTION__, 
				htTssiInfo.PartA.field.STBC, 
				htTssiInfo.PartB.field.MCS));

			if ((htTssiInfo.PartB.field.MCS < 0) || (htTssiInfo.PartB.field.MCS > 7)) /* boundary verification */
			{
				DBGPRINT(RT_DEBUG_ERROR, ("%s: incorrect MCS: htTssiInfo.PartB.field.MCS = %d\n", 
					__FUNCTION__, 
					htTssiInfo.PartB.field.MCS));

				return FALSE;
			}

			if ((pAd->CommonCfg.CentralChannel >= 1) && (pAd->CommonCfg.CentralChannel <= 14))
			{
				ch = pAd->CommonCfg.CentralChannel;
			}
			else
			{
				ch = 1;

				DBGPRINT(RT_DEBUG_ERROR, ("%s: Incorrect channel #%d\n", __FUNCTION__, pAd->CommonCfg.CentralChannel));
			}

			if (htTssiInfo.PartA.field.STBC == 0)
			{
				if ((htTssiInfo.PartB.field.BW == BW_40) && 
				     ((htTssiInfo.PartB.field.MCS == MCS_5) || (htTssiInfo.PartB.field.MCS == MCS_6) || (htTssiInfo.PartB.field.MCS == MCS_7)))
				{
					*pDesiredTssi = RT5390_desiredTSSIOverHT40Ext[ch][htTssiInfo.PartB.field.MCS];
				}
				else
				{
					*pDesiredTssi = RT5390_desiredTSSIOverHTExt[ch][htTssiInfo.PartB.field.MCS];
				}
			}
			else
			{
				*pDesiredTssi = RT5390_desiredTSSIOverHTUsingSTBCExt[ch][htTssiInfo.PartB.field.MCS];
			}

			DBGPRINT(RT_DEBUG_TRACE, ("%s: ch = %d, *pDesiredTssi = %d\n", __FUNCTION__, ch, *pDesiredTssi));			
		}	

		if (*pDesiredTssi < 0x00)
		{
			*pDesiredTssi = 0x00;
		}	
		else if (*pDesiredTssi > 0x7C)
		{
			*pDesiredTssi = 0x7C;
		}

		RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R47, &BbpR47);
		BbpR47 = ((BbpR47 & ~0x07) | 0x04); /* TSSI_REPORT_SEL (TSSI INFO 0 - TSSI) and enable TSSI INFO udpate */
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R47, BbpR47);
	}

	DBGPRINT(RT_DEBUG_INFO, ("<--- %s\n", __FUNCTION__));

	return TRUE;
}

#if 0
#ifdef RALINK_ATE
INT RT5390_ATETssiCalibration(
	IN	PRTMP_ADAPTER		pAd,
	IN	PSTRING				arg)
{    
	UCHAR inputDAC;
	UINT 		i = 0;
	UCHAR		BbpData = 0, RFValue, OrgBbp47Value; /*, ChannelPower; */
	USHORT		EEPData = 0;
	UCHAR 		BSSID_ADDR[MAC_ADDR_LEN] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
	BBP_R47_STRUC	BBPR47;
	
	inputDAC = simple_strtol(arg, 0, 10);

	if (!IS_RT5390(pAd) || !(pAd->TxPowerCtrl.bInternalTxALC))                          
	{
		DBGPRINT(RT_DEBUG_TRACE, ("Not support TSSI calibration since not 5390 chip or EEPROM not set!!!\n"));
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
#endif /* RTMP_EFUSE_SUPPORT */
	else
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

INT RT5390_ATETssiCalibrationExtend(
	IN	PRTMP_ADAPTER		pAd,
	IN	PSTRING				arg)
{  
	UCHAR inputData;
	
	inputData = simple_strtol(arg, 0, 10);
	
	if (!(IS_RT5390(pAd) && (pAd->TxPowerCtrl.bInternalTxALC) && (pAd->TxPowerCtrl.bExtendedTssiMode)))			
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
#endif /* RALINK_ATE */
#endif
#endif /* RTMP_INTERNAL_TX_ALC */

#ifdef RTMP_TEMPERATURE_COMPENSATION
INT RT5392_ATEReadExternalTSSI(
	IN	PRTMP_ADAPTER		pAd,
	IN	PSTRING				arg)
{
	UCHAR	inputData = 0, RFValue = 0, BbpData = 0;
	USHORT	EEPData;
	
	inputData = simple_strtol(arg, 0, 10);
	
	RT28xx_EEPROM_READ16(pAd, EEPROM_NIC2_OFFSET, EEPData);

	if (!(IS_RT5392(pAd) && ((EEPData & 0x02) != 0)))			
	{
		DBGPRINT(RT_DEBUG_TRACE, ("Not support TSSI calibration since not 5392 chip or EEPROM not set!!!\n"));
		return FALSE;
	}
	else
	{	
		/* BBP R47[7]=1 : ADC 6 on */
		RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R47, &BbpData);
		BbpData |= 0x80;
		RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R47, BbpData);

		/* RF R27[7:6]=0x1 : Adc_insel 01:Temp */	
		/* Write RF R27[3:0]=EEPROM 0x76 bit[3:0] */
		RT30xxReadRFRegister(pAd, RF_R27, &RFValue);	
		RFValue &= ~0xC0;
		RFValue |= 0x40;
		RFValue = ((RFValue & 0xF0) | pAd->TssiGain); /* [3:0] = (tssi_gain and tssi_atten) */
		RT30xxWriteRFRegister(pAd, RF_R27, RFValue);			

		/* Wait 1ms. */					
		RTMPusecDelay(1000);

		/* Read BBP R49 reading as return value. */
		DBGPRINT(RT_DEBUG_TRACE, ("Read  BBP_R49\n")); 
		RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R49, &BbpData);
		DBGPRINT(RT_DEBUG_TRACE, ("BBP R49=0x%x\n", BbpData));

		RT28xx_EEPROM_READ16(pAd, EEPROM_TSSI_STEP_OVER_2DOT4G, EEPData);
		EEPData &= 0xff00;
		EEPData |= BbpData;
			
#ifdef RTMP_EFUSE_SUPPORT
		if (pAd->bUseEfuse)
		{
			if (pAd->bFroceEEPROMBuffer)
				NdisMoveMemory(&(pAd->EEPROMImage[EEPROM_TSSI_STEP_OVER_2DOT4G]), (PUSHORT)(&EEPData) ,2);
			else
			    	eFuseWrite(pAd, EEPROM_TSSI_STEP_OVER_2DOT4G, (PUSHORT)(&EEPData), 2);
		}
		else
#endif /* RTMP_EFUSE_SUPPORT */
		{
			RT28xx_EEPROM_WRITE16(pAd, EEPROM_TSSI_STEP_OVER_2DOT4G, EEPData);
			RTMPusecDelay(10);
		}   

		/* RF R27[7:6]=0x0 */
		RT30xxReadRFRegister(pAd, RF_R27, &RFValue);	
		RFValue &= ~0xC0;
		RT30xxWriteRFRegister(pAd, RF_R27, RFValue);		
	}

	return TRUE;
}
#endif /* RTMP_TEMPERATURE_COMPENSATION */

VOID RT5390_ChipAGCInit(
	IN PRTMP_ADAPTER		pAd,
	IN UCHAR				BandWidth)
{
	UCHAR R66 = 0x30;
	CHAR lan_gain = GET_LNA_GAIN(pAd);
	
	if (pAd->LatchRfRegs.Channel <= 14) /* BG band */
	{	
		/* Gary was verified Amazon AP and find that RT307x has BBP_R66 invalid default value */
		
		R66 = 0x1C + 2 * lan_gain;
		
		rtmp_bbp_set_agc(pAd, R66, RX_CHAIN_ALL);
		
		/*20100902 update for Rx Sensitive*/
		if (IS_RT5392(pAd))
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R135 ,0xF6);
	}
	else /*A band */
	{	
		if (BandWidth == BW_20)
			R66 = (UCHAR)(0x32 + (lan_gain * 5) / 3);
#ifdef DOT11_N_SUPPORT
		else
			R66 = (UCHAR)(0x3A + (lan_gain * 5) / 3);
#endif /* DOT11_N_SUPPORT */

		rtmp_bbp_set_agc(pAd, R66, RX_CHAIN_ALL);
	}

#ifdef RELEASE_EXCLUDE
	DBGPRINT(RT_DEBUG_INFO, ("%s():Ch=%d, BandWidth=%d, LNA_GAIN=0x%x, set R66 as 0x%x\n", 
		__FUNCTION__, pAd->LatchRfRegs.Channel, BandWidth, GET_LNA_GAIN(pAd), R66));
#endif /* RELEASE_EXCLUDE */
}

VOID RT5392_AsicRecalBbpAgent(
	IN PRTMP_ADAPTER		pAd)	
{	
	ULONG 	loop = 0;
	UINT8 	BBPValue = 0;
	UINT32 	MacValue = 0;
		
	/* step 1: disable PA. */
	RTMP_IO_READ32(pAd, 0x1328, &MacValue);
	RTMP_IO_WRITE32(pAd, 0x1328, (MacValue & 0xfffff0f0));

	/* step 2: re-calibarate BBP IQ. */
	BBP_IO_WRITE8_BY_REG_ID(pAd,158,0x00);
	BBP_IO_WRITE8_BY_REG_ID(pAd,159,0x80);

	/* step3: check re-calibarate BBP IQ done. */
	do
	{
		BBP_IO_READ8_BY_REG_ID(pAd,159,&BBPValue);
		RTMPusecDelay(5);
	} while ((BBPValue != 0) && (loop++ <= 100));
		
	if (loop == 101)
		DBGPRINT(RT_DEBUG_OFF, ("BBP re-calibaration fail! \n"));
#ifdef IQ_CAL_SUPPORT
	else
	{
		/* IQ Calibration */
		RTMP_CHIP_IQ_CAL(pAd, pAd->CommonCfg.Channel);
	}
#endif /* IQ_CAL_SUPPORT */

	/* step4: enable PA. */
	RTMP_IO_READ32(pAd, 0x1328, &MacValue);
	RTMP_IO_WRITE32(pAd, 0x1328, (MacValue | 0x00050f0f));	
}


VOID NICStoreBBPValue(
	IN PRTMP_ADAPTER pAd,
	IN REG_PAIR *RegPair)
{
	UCHAR BBPIndex = 0, BBPValue = 0;
	INT32 i = 0;
	/* BBP R1 ~ R4 */
	for (BBPIndex = BBP_R1; BBPIndex <= BBP_R4; BBPIndex++)
	{
		RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBPIndex, &BBPValue);
		RegPair[i].Register = BBPIndex;
		RegPair[i].Value = BBPValue;
		i++;
	}
	/* BBP R31 */
	BBPIndex = BBP_R31;
	RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBPIndex, &BBPValue);
	RegPair[i].Register = BBPIndex;
	RegPair[i].Value = BBPValue;
	i++;	

	/* BBP R53 */
	BBPIndex = BBP_R53;
	RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBPIndex, &BBPValue);
	RegPair[i].Register = BBPIndex;
	RegPair[i].Value = BBPValue;
	i++;	


	/* BBP R62~R92 */
	for (BBPIndex = BBP_R62; BBPIndex <= BBP_R92; BBPIndex++)
	{
		RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBPIndex, &BBPValue);	
		RegPair[i].Register = BBPIndex;	
		RegPair[i].Value = BBPValue;
		i++;	
	}

	/* BBP R98 */
	BBPIndex = BBP_R98;
	RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBPIndex, &BBPValue);
	RegPair[i].Register = BBPIndex;
	RegPair[i].Value = BBPValue;
	i++;	

	
	/* BBP R103~R106 */
	for (BBPIndex = BBP_R103; BBPIndex <= BBP_R106; BBPIndex++)
	{
		RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBPIndex, &BBPValue);
		RegPair[i].Register = BBPIndex;
		RegPair[i].Value = BBPValue;
		i++;
	}

	/* BBP R128 */
	BBPIndex = BBP_R128;
	RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBPIndex, &BBPValue);
	RegPair[i].Register = BBPIndex;
	RegPair[i].Value = BBPValue;
	i++;	

	/* BBP R134 */
	BBPIndex = BBP_R134;
	RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBPIndex, &BBPValue);
	RegPair[i].Register = BBPIndex;
	RegPair[i].Value = BBPValue;
	i++;	

	/* BBP R135 */
	BBPIndex = BBP_R135;
	RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBPIndex, &BBPValue);
	RegPair[i].Register = BBPIndex;
	RegPair[i].Value = BBPValue;
	i++;	

	/* BBP R152 */
	BBPIndex = BBP_R152;	
	RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBPIndex, &BBPValue);	
	RegPair[i].Register = BBPIndex;	
	RegPair[i].Value = BBPValue;
}

VOID NICRestoreBBPValue(
	IN PRTMP_ADAPTER pAd,
	IN REG_PAIR *RegPair)
{
	INT32 i;

	for (i = 0; i < 10; i++)
	{
		if (RegPair[i].Register)
		{
			DBGPRINT(RT_DEBUG_TRACE,
				("i = %d, BBPIndex = %d, BBPValue = 0x%x\n",	
					i, RegPair[i].Register, RegPair[i].Value));
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, RegPair[i].Register,
					RegPair[i].Value);
		}
	}
			DBGPRINT(RT_DEBUG_TRACE,
				("10 BBPIndex = %d, BBPValue = 0x%x\n",RegPair[10].Register, RegPair[10].Value));

	rtmp_bbp_set_agc(pAd, RegPair[10].Value, RX_CHAIN_ALL);

	for (i = 11; i < BBP_RECORD_NUM; i++)
	{
		if (RegPair[i].Register)
		{
			DBGPRINT(RT_DEBUG_TRACE,
				("i = %d, BBPIndex = %d, BBPValue = 0x%x\n",	
					i, RegPair[i].Register, RegPair[i].Value));
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, RegPair[i].Register,
					RegPair[i].Value);
		}
	}


}


VOID RT5392_AsicResetBBPAgent(
IN PRTMP_ADAPTER pAd)
{

	DBGPRINT(RT_DEBUG_ERROR, ("Reset BBP Agent busy bit.!! \n"));
#if 1

	NICStoreBBPValue(pAd, pAd->BBPResetCtl.BBPRegDB);
	RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, 0xe);
	RTMPusecDelay(50);
	RTMP_IO_WRITE32(pAd, MAC_SYS_CTRL, 0xc);
	RTMPusecDelay(50);
	NICRestoreBBPValue(pAd, pAd->BBPResetCtl.BBPRegDB);

#else
	{
		RTMP_IO_READ32(pAd, H2M_BBP_AGENT, &BbpCsr.word);
		BbpCsr.field.Busy = 0;
		RTMP_IO_WRITE32(pAd, H2M_BBP_AGENT, BbpCsr.word);
	}
#endif

}

