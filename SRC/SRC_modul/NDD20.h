#ifndef __NDD20__
#define __NDD20__
#include "appli.h"
#include "global.h"

#ifdef PLATA_NDD20

#define NAME_MODUL "NDD20"
#define DEVICE_TYPE 1


extern void (*INIT_BLOK)(void);
extern void (*DRIVER_BLOK)(void);
extern WORD *STATE_BLOCK;


#define PG_F1	PDR9_P92	//0 - OK 
#define PG_F2	PDR9_P93	//1 - Bad


#define IN1		PDR7	

#define S1		PDR8	// 1 вкл 0 выкл  
#define S2		PDR5

#define S_OFF	S1=0;	 S2=0;
#define S_ON	S1=0xFF; S2=0xFF;

//=======================================================================
#define STRB1 	PDR4_P40  // 0 - работа 1 - выкл
#define STRB2 	PDR4_P41  // 0 - работа 1 - выкл
#define STRB3 	PDR4_P42  // 0 - работа 1 - выкл
#define STRB4 	PDR4_P43  // 0 - работа 1 - выкл

#define SELECT_STRB1 	STRB1=0; STRB2=1; STRB3=1; STRB4=1;
#define SELECT_STRB2 	STRB1=1; STRB2=0; STRB3=1; STRB4=1;
#define SELECT_STRB3 	STRB1=1; STRB2=1; STRB3=0; STRB4=1;
#define SELECT_STRB4 	STRB1=1; STRB2=1; STRB3=1; STRB4=0;

#define DESELECT_STRB	STRB1=1;STRB2=1;STRB3=1;STRB4=1;




#define TST1	PDR6_P60  // имеет значение только когда реле разомкнуты
#define TST2	PDR6_P61  // 1-2 - 	00 »митаци€ разрыва	
						  //		10 »митаци€ разрыва	
#define TST3	PDR6_P62  // 		10 »митаци€ датчика в состо€нии 10 кќм 	
#define TST4	PDR6_P63  //		11 »митаци€ замкнутого состо€ни€		

#define PWR1	PDR1_P12  // 0 - вкл  1 - выкл


#define SET_DIN1_TEST0		TST1=0;	TST2=0;		// имитаци€ разрыва
#define SET_DIN1_TEST1		TST1=1;	TST2=1;		// имитаци€ замкнутого состо€ни€
#define SET_DIN1_TEST_10kOm	TST1=0;	TST2=1;		// имитаци€ состо€ни€ 10 кќм

#define SET_DIN2_TEST0		TST3=0;	TST4=0;
#define SET_DIN2_TEST1		TST3=1;	TST4=1;
#define SET_DIN2_TEST_10kOm	TST3=0;	TST4=1;
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

typedef union
{
	BYTE	byte;
	struct
	{
		BYTE I12	:2;	
		BYTE I34	:2;
		BYTE I56	:2;
		BYTE I78	:2;
	}bits;
}TIN;

typedef struct
{
	BYTE	PowerNew;	// —осто€ние реле 1 - вкл 0 - выкл
	BYTE	PowerOld;

	BYTE	state[2];	// 0 - 10 кќм 	1 - «амкнуто
	BYTE	tmp_state[2];
	BYTE	valid[2];	// 0 - исправно 1 - обрыв/неисправность блока
	BYTE	tmp_valid[2];
	BYTE	test[2];	// 0 - »справно 1 - неисправно
	BYTE	tmp_test[2];
	
	WORD 	Timer1; // 1 - 0.5 ms
	DWORD 	Timer2;
	
	TInfo	Info;
	
	BYTE 	St1;
	BYTE	Read[3];
	BYTE	TestR[3];
	BYTE	CurStep;
	BYTE	CurBunk;
	
	BYTE	T_1;
	BYTE	T_2;
	BYTE	T_3;
	BYTE	T_4;
	
	BYTE	IN_1;
	BYTE	IN_2;
	BYTE	IN_3;
	BYTE	IN_4;
	
	
	
}CNDD20;

void InitNDD20();
void Driver_NDD20();

extern CNDD20 Ndd;


#endif
#endif
