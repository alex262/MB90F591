#ifndef __NDD20P__
#define __NDD20P__
#include "appli.h"
#include "global.h"

#ifdef PLATA_NDD20P

#define NAME_MODUL "NDD20P"
#define DEVICE_TYPE 1


extern void (*INIT_BLOK)(void);
extern void (*DRIVER_BLOK)(void);
extern WORD *STATE_BLOCK;			//”азатель на поле Info блока




#define IN1		PDR7	//0 - нали ие сигнала
#define IN2		PDR4



//=======================================================================
#define TST1	PDR6_P63  // 0 -  итаем состо ние входов 1 - тест 0
#define TST2	PDR6_P60
#define PWR1	PDR6_P62  // 0 - тест 1; 1 сото ние входов либо тест 0
#define PWR2	PDR6_P61

#define SET_DIN0_TEST0	PWR1=1; TST1=1;
#define SET_DIN0_TEST1	PWR1=0; TST1=0;
#define SET_DIN0_READ	PWR1=1; TST1=0;

#define SET_DIN1_TEST0	PWR2=1; TST2=1;
#define SET_DIN1_TEST1	PWR2=0; TST2=0;
#define SET_DIN1_READ	PWR2=1; TST2=0;
//==========================================================================




#define LEDR 	PDR1_P11
#define LEDG 	PDR1_P10

#define MODE	(((~PDR0)>>4)&0xF)	// осто ние перекл  ателей
#define ADDR	(PDR2&0x1F)		// осто ние перекл  ателей
#define RSRV	PDR1_P17

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
	BYTE	PowerNew;
	BYTE	PowerOld;
	BYTE	test[2];
	BYTE	tmp_test[2];
	BYTE	state[2];
	
	DWORD 	Timer1_1; // 1 - 0.5 ms
	WORD 	Timer1_2;
	DWORD 	Timer2_1;
	WORD 	Timer2_2;
	
	TInfo	Info;
	BYTE 	St1;
	BYTE 	St2;
}CNDD20P;

void InitNDD20P();
void Driver_NDD20P();



extern CNDD20P Ndd;






void Test1_DIN0();
void Test0_DIN0();
void Read_DIN0();
void Test1_DIN1();
void Test0_DIN1();
void Read_DIN1();
void UpdateDataNDD(void);



#endif
#endif
