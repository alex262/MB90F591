#ifndef __FSU__
#define __FSU__

#include "global.h"



#ifdef PLATA_FSU

extern const char SoftwareVer[20]; 

#define FSU14_C
//#define NAME_MODUL "FSU26"
#define NAME_MODUL "FSU20"
//#define NAME_MODUL "FSU14"

//#define FSU16_K
//#define NAME_MODUL "FSU16"
//#define NAME_MODUL "FSU18"

#define DEVICE_TYPE 2


extern void (*INIT_BLOK)(void);
extern void (*DRIVER_BLOK)(void);
extern WORD *STATE_BLOCK;

#define RSRV	PDR1_P17

#define	NE_CHET	0x1
#define	CHET	0x2

#define PR1		PDR8_P84
#define PR2		PDR8_P85
#define PS1		PDR8_P86
#define PS2		PDR8_P87


#define S_1		PDR7
#define S_2		PDR6
#define S_3		PDR4

#define S1		PDR7_P77	//FSU 18 1 - çàìêíóòî 0 - ðàçîìêíóòî
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
#define S13		PDR6_P63 
#define S14		PDR6_P62 
#define S15		PDR6_P61  
#define S16		PDR6_P60 

#define S17		PDR4_P47
#define S18		PDR4_P46
#define S19		PDR4_P45
#define S20		PDR4_P44
#define S21		PDR4_P43
#define S22		PDR4_P42
#define S23		PDR4_P41
#define S24		PDR4_P40

#define K1		PDR5_P50	//FSU 18 0 - çàìêíóòî 1 - ðàçîìêíóòî
#define K2		PDR5_P51
#define K3		PDR5_P52
#define K4		PDR5_P53
#define K5		PDR5_P54
#define K6		PDR5_P55

#define K1_6	(PDR5&0x3F)

#define RESERV   PDR1_P17

#define STRB1	PDR8_P80
#define STRB2	PDR8_P81
#define STRB3	PDR8_P82
#define STRB4	PDR8_P83

#define LEDR 	PDR1_P11
#define LEDG 	PDR1_P10

#define MODE	(((~PDR0)>>4)&0xF)		//T®áâ®ï­¨¥ ¯¥à¥ª«_ç â¥«¥©
#define ADDR	(PDR2&0x1F)			//T®áâ®ï­¨¥ ¯¥à¥ª«_ç â¥«¥©


#define PG_F1	PDR9_P92
#define PG_F2	PDR9_P93

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
	DWORD	Test;
	DWORD	State;
	DWORD	Prin;
	
	WORD	State_NECHET;
	WORD	State_CHET;
	WORD	Prin_NECHET;
	WORD	Prin_CHET;
	
	WORD 	Timer_Test;
	WORD 	Timer;
	WORD 	Timer2;
	TInfo  	Info;
	BYTE 	St;
}CFSU14_C;

void Reset_S();
void Reset_Set(BYTE Type);
void Test_FSU();
void InitFSU14C();
void Update_DOUT(BYTE Type);
void Update_Data_BD_DOUT();
void Driver_FSU14_C();
void TestOutput();
void TestOutput_1(BYTE i);
void DOUT_OFF(BYTE Type);
void DOUT_ON(BYTE Type);

BYTE Convert_f(BYTE n);
extern CFSU14_C Fsu;

#endif
#endif