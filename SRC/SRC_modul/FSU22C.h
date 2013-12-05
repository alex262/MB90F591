#ifndef __FSU22C__
#define __FSU22C__

#include "global.h"

#ifdef PLATA_FSU22C

#define NAME_MODUL "FSU22-C"

#define DEVICE_TYPE 2


extern void (*INIT_BLOK)(void);
extern void (*DRIVER_BLOK)(void);
extern WORD *STATE_BLOCK;			//Lазатель на поле Info блока

#define RSRV	PDR1_P17

#define	NE_CHET	0x1
#define	CHET	0x2

#define PR1		PDR8_P84
#define PR2		PDR8_P85
#define PS1		PDR8_P86
#define PS2		PDR8_P87


#define S1		PDR7_P77
#define S2		PDR7_P76
#define S3		PDR7_P75
#define S4		PDR7_P74
#define S5		PDR7_P73
#define S6		PDR7_P72
#define S7		PDR7_P71
#define S8		PDR7_P70

#define S9		PDR6_P67
#define S10		PDR6_P66
#define S11		PDR6_P65
#define S12		PDR6_P64

#define K1_4	(PDR5&0xF)
#define K5_12	PDR4

#define K1		PDR5_P53
#define K2		PDR5_P52
#define K3		PDR5_P51
#define K4		PDR5_P50

#define K5		PDR4_P47
#define K6		PDR4_P46
#define K7		PDR4_P45
#define K8		PDR4_P44
#define K9		PDR4_P43
#define K10		PDR4_P42
#define K11		PDR4_P41
#define K12		PDR4_P40

#define LEDR 	PDR1_P11
#define LEDG 	PDR1_P10

#define MODE	(((~PDR0)>>4)&0xF)		//Tостояние перекл_чателей
#define ADDR	(PDR2&0x1F)			//Tостояние перекл_чателей


#define PG_F	PDR9_P92
//#define PG_F2	PDR9_P93

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
	BYTE	Test[2];
	BYTE	State[2];
	BYTE	Prin[2];
	
	BYTE	State_NECHET;
	BYTE	State_CHET;
	BYTE	Prin_NECHET;
	BYTE	Prin_CHET;
	
	WORD	Timer_Test;
	BYTE	Timer;
	TInfo	Info;
	BYTE	St;
}CFSU22_C;

void InitFSU22C();
void Driver_FSU22C();
void DOUT_ON(BYTE Type);
void DOUT_OFF(BYTE Type);
void Reset_Set(BYTE Type);



extern CFSU22_C Fsu22C;

#endif
#endif