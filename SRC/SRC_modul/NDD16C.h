#ifndef __NDD__
#define __NDD__
#include "appli.h"
#include "global.h"
#include "timer.h"

#ifdef PLATA_NDD
//#define NAME_MODUL "NDD18"
//#define NAME_MODUL "NDD16"
//#define NAME_MODUL "NDD17"
#define NAME_MODUL "NDD19"
#define DEVICE_TYPE 1
//#define NDD18_CV
#define NDD16_C					//19, 
//#define NDD17_K


extern const char SoftwareVer[20]; 

extern void (*INIT_BLOK)(void);
extern void (*DRIVER_BLOK)(void);
extern WORD *STATE_BLOCK;			//Уа атель на поле Info блока


#define IN1		PDR8
#define IN2		PDR7
#define IN3		PDR5
#define IN4		PDR4


#define PG_F1	PDR9_P92
#define PG_F2	PDR9_P93
#define PWR		PDR9_P94


#define TST1	PDR6_P63
#define TST2	PDR6_P60
#define PWR1	PDR6_P62
#define PWR2	PDR6_P61

#define G1		PDR6_P66
#define G2		PDR6_P65

#define LEDR 	PDR1_P11
#define LEDG 	PDR1_P10

#define MODE	(((~PDR0)>>4)&0xF)	//Состояние переключателей
#define ADDR	(PDR2&0x1F)		//Состояние переключателей
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
		WORD PWRDin	:1;
		WORD TestRun:1;	//Выполнялся ли тест 
		WORD TestRes:1;	//Результат тестировани 
	}bits;
}TInfo;
typedef struct
{
	BYTE	test[4];		// 0 - испаравен 1 - неисправен
	BYTE	tmp_test[4];
	BYTE	test_0;	// Завершилось ли проведение теста по конкретной половине
	BYTE	test_1; 
	
	BYTE	state[4];
	BYTE	drebezg[4];
	BYTE	pr_data[4];
	BYTE	counters[4][8];
	BYTE	counters_dr[4][8];
	BYTE 	Timer;
	BYTE 	Timer2;
	TInfo	Info;
	BYTE 	St1;
	BYTE 	St2;
	BYTE	Start;
	
	WORD	TimerTest;	// Если в течение определённого времени ошибки не появлялись то снимаем ранее выставленные флаги ошибок 
	TYPE_DATA_TIMER	TimerNdd;
}CNDD16_C;

BYTE Convert_n(BYTE n);
void InitNDD16C();
void Read_DIN();
void Driver_NDD16_C();
void Test_DIN();

//--------------------
void Test1_DIN0();
void Test0_DIN0();
void Read_DIN0();

void Test1_DIN1();
void Test0_DIN1();
void Read_DIN1();
//--------------------


BYTE Convert_a(BYTE n);

extern CNDD16_C	Ndd;
extern WORD		TIME_CONTROL_TEST;

#endif
#endif