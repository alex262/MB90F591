#ifndef __KCU__
#define __KCU__

#include "global.h"

#ifdef 	PLATA_KCU
#define DEVICE_TYPE 3
#define NAME_MODUL "KCU"

extern void (*INIT_BLOK)(void);		//Указатель на функции инициализации блока
extern void (*DRIVER_BLOK)(void);	//Указатель на функции драйвера блока
extern WORD (*STATE_BLOCK);			//Уазатель на поле Info блока

#define PG_F1	PDR9_P92
#define PG_F2	PDR9_P93

#define RSRV	1

#define MODE	(((~PDR0)>>4)&0xF)	//Состояние переключателей
#define ADDR	(PDR2&0x1F)			//Состояние переключателей

#define REG		(PDR1&0x80)			//Состояние переключателей

#define LEDR 	PDR1_P11
#define LEDG 	PDR1_P10
//==============================================================
#define TST24_17		PDR4
#define TST16_9			PDR7
#define TST8_1			PDR8

#define K1_6			(PDR5&0x3f)
#define D_K1_6			DDR5

#define STRB1			PDR6_P63
#define STRB2			PDR6_P62
#define STRB3			PDR6_P61
#define STRB4			PDR6_P60
#define D_STRB1			DDR6_D63
#define D_STRB2			DDR6_D62
#define D_STRB3			DDR6_D61
#define D_STRB4			DDR6_D60

#define TEST1			PDR6_P65
#define TEST2			PDR6_P64
#define D_TEST1			DDR6_D65
#define D_TEST2			DDR6_D64


#define TEST_TR1		PDR6_P66
#define TEST_TR2		PDR6_P67
//==============================================================
typedef union
{
	WORD	word;
	struct
	{
		WORD Addr	:5;	
		WORD Mode	:4;
		WORD F1		:1;
		WORD F2		:1;
		WORD Can1	:1;
		WORD Can2	:1;
		WORD Pwr1	:1;
		WORD Pwr2	:1;
		WORD Res	:1;
	}bits;
}TInfo;

#define REG_CIR_CONTROL		0
#define REG_REL_GR_CONTROL	1

typedef struct
{
	TInfo	Info;	
	BYTE	Regim;
	BYTE	CirControl[3];
	BYTE	CirControlTemp[3];
	BYTE	RelGroup[3];
	WORD    Timer; 
}CKCU;

void DriverKCU();
void InitKCU1C();
extern CKCU Kcu;

#endif
#endif