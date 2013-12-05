#ifndef __RVV5C__
#define __RVV5C__

#include "global.h"

#ifdef PLATA_RVV5C

#define DEVICE_TYPE 3
#define NAME_MODUL "RVV5-C"

extern void (*INIT_BLOK)(void);
extern void (*DRIVER_BLOK)(void);
extern WORD *STATE_BLOCK;			//Уазатель на поле Info блока

#define MODE	((~PDR1)&0xF)	//Состояние переключателей

#define LEDR 	PDR0_P07
#define LEDG 	PDR0_P06

//#define RSRV	PDR0_P04
//==============================================================
#define DATA_0_3_R		(PDR5&0xF)
#define DATA_0_3_W		PDR5

#define RIN0			PDR5_P54
#define RIN1			PDR5_P55
#define RIN2			PDR5_P56



#define selREAD_DATA	DDR5=0;
#define selWRITE_DATA	DDR5=0xF;

#define COUNT_BLOCK		10

//#define SELEKT_BL(n)	PDR6=(~(1<<n))&0x7F;
//#define UN_SELEKT_BL	PDR6=0x7F;

#define RW_R			PDR6_P67
#define tREAD			0
#define tWRITE			1

#define RCLK			PDR7_P70
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
		WORD Res	:3;
	}bits;
}TInfo;

typedef union
{
	BYTE	byte;
	struct
	{
		BYTE read	:4;	
		BYTE write	:4;	
	}bits;
}TRK;
typedef union
{
	WORD	word;
	struct
	{
		WORD read	:6;	
		WORD write	:6;
		WORD error	:1;
		WORD res	:3;	
	}bits;
}TDN;

typedef union
{
	WORD	word;
	struct
	{
		WORD Nch	:8;	// 0 выбор блока без комутации для РКС1 1-48,  1-10	
		WORD Nb		:4; // 0 не выбираем блок 1-6 РКС1,  7 РКС1-7 
	}bits;				// 8 - РКС2	
}TCH;


typedef struct
{
	TInfo	Info;	

	TCH		CH_select;	// коммутация входов	
	TCH		NewCH_select;	// коммутация входов	
	
	BYTE 	NewSel7;	//Выбор 7 блока 0 - выбор 1 - нет	
	BYTE 	Sel7;		//Выбор 7 блока 0 - выбор 1 - нет	
	
	BYTE	curRKS2;
	//BYTE	newRKS2;	//
	
	BYTE	Dn;			//Значение записанное в ДН
	BYTE	newDn;		//Новое Значение для записи в ДН

	WORD 	Error;		// Ошибки блоков 0 - ДН, 1 - комплектность, 2-8 РКС1 9 - РКС2
	
	BYTE 	SelektBl;	// Выбранный блок

	BYTE 	SetData;	// записанные данные в РКС1
	BYTE 	ReadData;	// записанные данные в РКС1
	
	WORD	Timer;
}CRVV5;

extern CRVV5 Rvv;
void DriverRVV();
void InitRVV5C();


#endif
#endif