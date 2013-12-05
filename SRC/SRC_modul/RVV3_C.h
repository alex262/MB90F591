#ifndef __RVV__
#define __RVV__

#include "global.h"

#ifdef PLATA_RVV3C
#define DEVICE_TYPE 3
#define NAME_MODUL "RVV3"

extern void (*INIT_BLOK)(void);
extern void (*DRIVER_BLOK)(void);
extern WORD *STATE_BLOCK;			//Уазатель на поле Info блока

#define MODE	((~PDR1)&0xF)	//Состояние переключателей

#define LEDR 	PDR0_P07
#define LEDG 	PDR0_P06

#define RSRV	PDR0_P04
//==============================================================
#define DATA_0_3_R		(PDR5&0xF)
#define DATA_0_3_W		PDR5

#define RIN0			PDR5_P54
#define RIN1			PDR5_P55
#define RIN2			PDR5_P56



#define selREAD_DATA	DDR5=0;
#define selWRITE_DATA	DDR5=0xF;

#define SELEKT_BL(n)	PDR6=(~(1<<n))&0x7F;
#define UN_SELEKT_BL	PDR6=0x7F;

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


typedef struct
{
	TInfo	Info;	
	BYTE	Regim;
	BYTE	Dn;
	BYTE	newDn;
	BYTE 	Error;
	BYTE 	SelektBl;
	BYTE 	SetData;
	
	BYTE	Write;
	BYTE	WriteNew;
	BYTE	Read;
	BYTE 	nCH;
	WORD	Timer;
}CRVV2;

extern CRVV2 Rvv;
void DriverRVV();
void InitRVV3C();


#endif
#endif