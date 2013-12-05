#ifndef __NDD__
#define __NDD__
#include "appli.h"
#include "global.h"

#ifdef PLATA_NDD21
#define NAME_MODUL "NDD21"
#define DEVICE_TYPE 1


extern void (*INIT_BLOK)(void);
extern void (*DRIVER_BLOK)(void);
extern WORD *STATE_BLOCK;			//Уа атель на поле Info блока


#define IN1		PDR8
#define IN2		PDR7


#define PG_F1	PDR9_P92
#define PG_F2	PDR9_P93


#define TST1	PDR6_P60
#define TST2	PDR6_P61
#define TST3	PDR6_P62
#define TST4	PDR6_P63

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
		WORD PWRDin	:1; // опрашиваем входы или нет
		WORD TestRun:1;	//Выполнялся ли тест 
		WORD TestRes:1;	//Результат тестировани 
	}bits;
}TInfo;
typedef struct
{
	BYTE	test[2];	// 0 - испаравен 1 - неисправен
	BYTE	tmp_test[2];
	BYTE	test_0;	// Завершилось ли проведение теста по конкретной половине 
	BYTE	test_1; 
	
	BYTE	state[2];
//	BYTE	drebezg[2];
	BYTE	pr_data[2];
	BYTE	counters[2][8];
	BYTE	counters_dr[2][8];
	BYTE 	Timer;
	BYTE 	Timer2;
	TInfo	Info;
	BYTE 	St1;
	BYTE 	St2;
//	WORD	TimerTest;	// Если в течение определённого времени ошибки не появлялись то снимаем ранее выставленные флаги ошибок 
	BYTE	stOff;		// 0 - отключаем входы, 1 - входы опрашиваются
	
}CNDD21;

BYTE Convert_n(BYTE n);
void InitNDD21();
void Read_DIN();
void Driver_NDD21();
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

extern CNDD21	Ndd;
extern WORD		TIME_CONTROL_TEST;

#endif
#endif