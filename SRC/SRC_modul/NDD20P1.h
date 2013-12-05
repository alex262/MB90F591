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




#define IN1		PDR7	//0 - замкнуто 1 - разомкнуто
#define IN2		PDR4

#define S1		PDR8	// 1 вкл 0 выкл  
#define S2		PDR5

#define S1_4_ON		S1 = S1|0x0F;	
#define S5_8_ON		S1 = S1|0xF0;	
#define S9_12_ON	S2 = S2|0x0F;	
#define S13_16_ON	S2 = S2|0xF0;	

#define S1_4_OFF	S1 = S1&0xF0;	
#define S5_8_OFF	S1 = S1&0x0F;	
#define S9_12_OFF	S2 = S2&0xF0;	
#define S13_16_OFF	S2 = S2&0x0F;	

#define S_OFF	S1=0;S2=0;
#define S_ON	S1=0xFF;S2=0xFF;

//=======================================================================
//  РАБОЧИЙ РЕЖИМ 
//  тест нуля возможен только при разомкнутой входной цепи
//  цепь разомкнута - TST = 1 IN = 1
//  ------------------------------------------------------
//  ТЕСТОВЫЙ РЕЖИМ
//  TST = 1 IN = 0
//  TST = 0 IN = 1

#define REGIM_TEST_1 0
#define REGIM_TEST_0 1
#define REGIM_WORK 	 2
#define REGIM_MAX 	 2


#define TST1	PDR6_P60  // 0 -тест 1, рабочий режим; 1 - тест 0
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
	
	//DWORD 	Timer1; // 1 - 0.5 ms
	WORD 	Timer2[4];
	BYTE 	St1[4];
	BYTE	CurStep[4];
	BYTE	Read[4][3];
	BYTE	TestR[4][3];
	
	BYTE	Test_Bunk[4];	// результаты теста для соответствующего банка
	BYTE	Test0_Req[4];	//1 - данная подгруппа запрашивает разрешение на проведение теста  0
	BYTE	Test0_Run[4];	//1 - данная подгруппа проводит тест  0
	BYTE	Test0_Last;		// 0-3 - тот кто последний выполнил тест
	TInfo	Info;
	
//	BYTE	CurBunk;
	
	
}CNDD20P1;

void InitNDD20P1();
void Driver_NDD20P1();



extern CNDD20P1 Ndd;

void UpdateDataSector(BYTE n);

//void UpdateDataNDD(void);



#endif
#endif
