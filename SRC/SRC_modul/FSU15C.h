#ifndef __FSU15C__
#define __FSU15C__

#include "global.h"

#ifdef PLATA_FSU15_C

//#define PLATA_FSU15
#define PLATA_FSU21

#ifdef PLATA_FSU15
	#define NAME_MODUL "FSU15"
#endif
#ifdef PLATA_FSU21
	#define NAME_MODUL "FSU21"
#endif

#define DEVICE_TYPE 2

extern void (*INIT_BLOK)(void);
extern void (*DRIVER_BLOK)(void);
extern WORD *STATE_BLOCK;					//Уазатель на поле Info блока

#define S1		PDR7_P75
#define S2		PDR7_P74
#define S3		PDR7_P73
#define S4		PDR7_P72
#define S5		PDR7_P71
#define S6		PDR7_P70
#define S7		PDR6_P65
#define S8		PDR6_P64

#define S9		PDR6_P63
#define S10		PDR6_P62
#define S11		PDR6_P61
#define S12		PDR6_P60

#define K1_6	(PDR8&0x3F)
#define K7_12	(PDR4&0x3F)

#define LEDR 	PDR1_P11
#define LEDG 	PDR1_P10

#define MODE	(((~PDR0)>>4)&0xF)	//Состояние переключателей
#define ADDR	(PDR2&0x1F)			//Состояние переключателей


#define PG_F1	PDR9_P92
#define PG_F2	PDR9_P93

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
		WORD Resrv	:3;
	}bits;
}TInfo;


typedef struct
{
	WORD	Test;
	WORD	State;
	WORD	Prin;
	
	TInfo  	Info;
	
	//WORD	Temp;
}CFSU15_C;

extern CFSU15_C Fsu15;


void InitFSU15C(void);
void DriverFSU15_C();

#endif
#endif