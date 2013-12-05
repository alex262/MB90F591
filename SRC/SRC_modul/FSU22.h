#ifndef __FSU22__
#define __FSU22__

#include "global.h"

#ifdef PLATA_FSU22

#define NAME_MODUL "FSU22"

#define DEVICE_TYPE 2


extern void (*INIT_BLOK)(void);
extern void (*DRIVER_BLOK)(void);
extern WORD *STATE_BLOCK;			//Уазатель на поле Info блока
#define RSRV	PDR1_P17


#define S_1		PDR7
#define S_2		PDR6

#define S1		PDR7_P77
#define S2		PDR7_P76
#define S3		PDR7_P75
#define S4		PDR7_P74
#define S5		PDR7_P73
#define S6		PDR7_P72

#define S7		PDR6_P67
#define S8		PDR6_P66
#define S9		PDR6_P65
#define S10		PDR6_P64
#define S11		PDR6_P63
#define S12		PDR6_P62

#define K1		PDR5_P50
#define K2		PDR5_P51
#define K3		PDR5_P52
#define K4		PDR5_P53
#define K5		PDR5_P54
#define K6		PDR5_P55

#define STRB1	PDR8_P80
#define STRB2	PDR8_P81
#define STRB3	PDR8_P82
#define STRB4	PDR8_P83

#define D_STRB1	DDR8_D80
#define D_STRB2	DDR8_D81
#define D_STRB3	DDR8_D82
#define D_STRB4	DDR8_D83

#define K1_6	(PDR5&0x3F)

#define LEDR 	PDR1_P11
#define LEDG 	PDR1_P10

#define MODE	(((~PDR0)>>4)&0xF)		//Состояние переключателей
#define ADDR	(PDR2&0x1F)			//Состояние переключателей


#define PG_F1	PDR9_P92

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

typedef union
{
	BYTE	byte[2];
	WORD	word;
	struct
	{
		WORD O1		:1;	
		WORD O2		:1;
		WORD O3		:1;
		WORD O4		:1;
		WORD O5		:1;
		WORD O6		:1;
		WORD O7		:1;
		WORD O8		:1;
		WORD O9		:1;
		WORD O10	:1;
		WORD O11	:1;
		WORD O12	:1;
		WORD rsv	:4;
	}bits;
}TDout;


typedef struct
{
	TDout	Test;
	TDout	State;
	TDout	Prin;
	
	WORD 	Timer_Test;
	BYTE 	Timer;
	TInfo  	Info;
}CFSU22;

extern CFSU22 Fsu22; 


void InitFSU22();
void Driver_FSU22();

#endif
#endif