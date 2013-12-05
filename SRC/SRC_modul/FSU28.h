#ifndef __FSU28__
#define __FSU28__

#include "global.h"

#ifdef PLATA_FSU28


extern const char SoftwareVer[20]; 
//-----------------------------------------------------------------------------------------------
//#define FSU28_0
//#define FSU28_1
//#define FSU28_2
#define FSU28_3

#ifdef FSU28_0
	#define NAME_MODUL "FSU28-0"
	#define	RELE_TIP	0xF00000	//тип реле 0-нормально разомкнутое; 1-нормально замкнутое
#endif	
#ifdef FSU28_1
	#define NAME_MODUL "FSU28-1"
	#define	RELE_TIP	0xF80000	//тип реле 0-нормально разомкнутое; 1-нормально замкнутое
#endif	
#ifdef FSU28_2
	#define NAME_MODUL "FSU28-2"
	#define	RELE_TIP	0x000000	//тип реле 0-нормально разомкнутое; 1-нормально замкнутое
#endif	
#ifdef FSU28_3
	#define NAME_MODUL "FSU28-3"
	#define	RELE_TIP	0xFE0000	//тип реле 0-нормально разомкнутое; 1-нормально замкнутое
#endif	

//-----------------------------------------------------------------------------------------------
#define DEVICE_TYPE 2


extern void (*INIT_BLOK)(void);
extern void (*DRIVER_BLOK)(void);
extern WORD *STATE_BLOCK;

#define RSRV	PDR1_P17

#define S_1		PDR7
#define S_2		PDR6
#define S_3		PDR4

#define S1		PDR7_P77	//FSU 18 1 - замкнуто 0 - разомкнуто
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

#define K1		PDR5_P50	//FSU 18 0 - замкнуто 1 - разомкнуто
#define K2		PDR5_P51
#define K3		PDR5_P52
#define K4		PDR5_P53
#define K5		PDR5_P54
#define K6		PDR5_P55

#define K1_6	(PDR5&0x3F)

#define STRB1	PDR8_P80
#define STRB2	PDR8_P81
#define STRB3	PDR8_P82
#define STRB4	PDR8_P83

#define LEDR 	PDR1_P11
#define LEDG 	PDR1_P10

#define MODE	(((~PDR0)>>4)&0xF)		
#define ADDR	(PDR2&0x1F)			


#define PG_F1	PDR9_P92

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
	
	TInfo  	Info;
}CFSU28;

void InitFSU28();
void Driver_FSU28();
void TestOutput();

BYTE Convert_f(BYTE n);
extern CFSU28 Fsu;

#endif
#endif