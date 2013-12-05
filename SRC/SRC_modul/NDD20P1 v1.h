#ifndef __NDD20P1__
#define __NDD20P1__
#include "appli.h"
#include "global.h"

#ifdef PLATA_NDD20P1

#define NAME_MODUL "NDD20P"
#define DEVICE_TYPE 1


extern void (*INIT_BLOK)(void);
extern void (*DRIVER_BLOK)(void);
extern WORD *STATE_BLOCK;




#define IN1		PDR7	//0 - замкнуто                 
#define IN2		PDR4

#define S1		PDR8	// 1 вкл 0 выкл  
#define S2		PDR5

#define S_OFF	PDR5=0;PDR8=0;
#define S_ON	PDR5=0xFF;PDR8=0xFF;

//=======================================================================
#define TST1	PDR6_P60  // 0 -                         ,      0; 1 -      1
#define TST2	PDR6_P61
#define TST3	PDR6_P62
#define TST4	PDR6_P63

#define PWR1	PDR1_P12  // 0 - вкл  1 - выкл
#define PWR_ON	PWR1=0;
#define PWR_OFF	PWR1=1;

#define SET_DIN1_TEST0	TST1=1;
#define SET_DIN1_TEST1	TST1=0;
#define SET_DIN1_READ	TST1=0;

#define SET_DIN2_TEST0	TST2=1;
#define SET_DIN2_TEST1	TST2=0;
#define SET_DIN2_READ	TST2=0;

#define SET_DIN3_TEST0	TST3=1;
#define SET_DIN3_TEST1	TST3=0;
#define SET_DIN3_READ	TST3=0;

#define SET_DIN4_TEST0	TST4=1;
#define SET_DIN4_TEST1	TST4=0;
#define SET_DIN4_READ	TST4=0;

//==========================================================================

#define LEDR 	PDR1_P11
#define LEDG 	PDR1_P10

#define MODE	(((~PDR0)>>4)&0xF)	//                        
#define ADDR	(PDR2&0x1F)		//                        
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
	BYTE	test[2];	// 0-Исправно 1 - неисправно
	BYTE	tmp_test[2];
	BYTE	state[2];
	
	DWORD 	Timer1; // 1 - 0.5 ms
	WORD 	Timer2;
	
	TInfo	Info;
	BYTE 	St1;
	BYTE	Read[3];
	BYTE	TestR[3];
	BYTE	CurStep;
	BYTE	CurBunk;
	
	
}CNDD20P1;

void InitNDD20P1();
void Driver_NDD20P1();



extern CNDD20P1 Ndd;

void Test1_DIN0();
void Test0_DIN0();
void Read_DIN0();
void Test1_DIN1();
void Test0_DIN1();
void Read_DIN1();
void UpdateDataNDD(void);



#endif
#endif
