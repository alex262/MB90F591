#ifndef __FSU19__
#define __FSU19__

#include "global.h"

#ifdef PLATA_FSU19

#define NAME_MODUL "FSU23"

#define DEVICE_TYPE 2



extern void (*INIT_BLOK)(void);
extern void (*DRIVER_BLOK)(void);
extern WORD *STATE_BLOCK;			//Уазатель на поле Info блока

#define S_1		PDR7
#define S_2		PDR6
#define S_3		PDR5
#define S_4		PDR4

#define RSRV	1

#define LEDR 	PDR1_P11
#define LEDG 	PDR1_P10

#define MODE	(((~PDR0)>>4)&0xF)	//Состояние переключателей
#define ADDR	(PDR2&0x1F)			//Состояние переключателей


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
	BYTE	State[4];
	BYTE	Prin[4];
	
	TInfo  	Info;

}CFSU19;

void InitFSU19();
void Driver_FSU19();

extern CFSU19 Fsu;

#endif
#endif