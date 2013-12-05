#ifndef __RVV6__
#define __RVV6__

#include "global.h"

#ifdef PLATA_RVV6

#define DEVICE_TYPE 3
#define NAME_MODUL "RVV6"

extern void (*INIT_BLOK)(void);
extern void (*DRIVER_BLOK)(void);
extern WORD *STATE_BLOCK;			//Уазатель на поле Info блока

#define MODE	((~PDR1)&0xF)	//Состояние переключателей

#define LEDR 	PDR0_P07
#define LEDG 	PDR0_P06

//#define RSRV	PDR0_P04
//==============================================================
#define BLOCK_DN_NUM	8
#define COUNT_RK3_BLOCK 7

//==============================================================
#define DATA_0_3_R			(PDR5&0xF)
#define DATA_0_3_W(x)		PDR5=x&0xF;

#define RIN0			PDR5_P54
#define RIN1			PDR5_P55
#define RIN2			PDR5_P56

#define RIN				((PDR5>>4)&7)



#define selREAD_DATA	DDR5=0;
#define selWRITE_DATA	DDR5=0xF;

#define COUNT_BLOCK		9

#define SELECT_BLOCK	0
#define UNSELECT_BLOCK	1


#define RW_R			PDR6_P67
#define tREAD			0
#define tWRITE			1

#define RCLK			PDR7_P70
//#define CLOCK_CLK		RCLK=0; RCLK=1; RCLK=0;

//========================================
#define RSE1			PDR6_P60
#define RSE2			PDR6_P61
#define RSE3			PDR6_P62
#define RSE4			PDR6_P63
#define RSE5			PDR6_P64
#define RSE6			PDR6_P65
#define RSE7			PDR6_P66
#define RSE8			PDR7_P74
#define RSE9			PDR7_P75
#define RSE10			PDR7_P76
#define RSE11			PDR7_P77
#define RSE12			PDR8_P80
#define RSE13			PDR8_P81
#define RSE14			PDR8_P82
#define RSE15			PDR8_P83
#define RSE16			PDR8_P84
#define RSE17			PDR8_P85
#define RSE18			PDR8_P86
#define RSE19			PDR8_P87



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

typedef struct
{
	BYTE	New[2];		// Записываемые данные в блок
	BYTE	Old[2];		// Записанные данные в блок
	BYTE	Read[2];	//
	BYTE	Select[2];	//	SELECT_BLOCK, UNSELECT_BLOCK 
	BYTE	Error;		// 0 бит - неисправность первой половины блока; 1 - второй
}TBlock;



typedef struct
{
	TInfo	Info;	
	WORD	Error;			// 0 - бит комплектность
	TBlock	Block[COUNT_BLOCK];
	BYTE	NewEnableChange;//если  EnableChange не равно NewEnableChange  
	BYTE	EnableChange;	//вносим изменения
							//после того как блок отработал изменения он сам выставляет 0
							//и ждёт следующей команды на разрешение переключения реле
	WORD	Timer;
	DWORD	SelectBlockNew;	// Обмен с УСО 0 бит первая половина 1 блока он же РК3-1 согласно схемы, 1 бит второя половина
	DWORD	SelectBlockOld;
	
}CRVV6;

extern CRVV6 Rvv;
void DriverRVV();
void InitRVV();


#endif
#endif