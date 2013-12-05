#ifndef __AVV2C__
#define __AVV2C__

#include "global.h"

#ifdef PLATA_AVV2C

#define PLATA_AVV2_M1

#define DEVICE_TYPE 4

#define NAME_MODUL "AVV2"

extern void (*INIT_BLOK)(void);
extern void (*DRIVER_BLOK)(void);
extern WORD *STATE_BLOCK;


#define PG_F1	PDR9_P92

#define RSRV	PDR1_P17

#define DRDY	PDR9_P93	//Готовность данных 0

#define FADC	PDR5_P50
#define CSADC	PDR5_P52
#define CSDAC	PDR5_P55

#define BND		PDR2_P20	//Включение выключение делителя диапазона

#define A0_2	((PDR6>>4)&7)
#define A0		PDR6_P64
#define A1		PDR6_P65
#define A2		PDR6_P66

#define EN		PDR6_P63

#define MODE	(((~PDR0)>>4)&0xF)	//Состояние переключателей
#define M0		PDR0_P04
#define M1		PDR0_P05
#define M2		PDR0_P06
#define M3		PDR0_P07

#define LEDR 	PDR1_P11
#define LEDG 	PDR1_P10
//===========================
#define SELFCAL 	0xF0
#define SELFOCAL	0xF1
#define SELFGCAL	0xF2
#define SYSOCAL 	0xF3
#define SYSGCAL 	0xF4
#define SYSRESET 	0xFE
//===========================
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
	float K;
	float Ofs;
}TTarirCoef;

#define CICKL_OPROS_TEM	100	//Цикл опроса температурного датчика в ms

#define COUNT_CH_REGIM	2
#define COUNT_CH		6

typedef struct
{
	TInfo	Info;	
	//WORD 	Temperature;	//Температура 
	WORD	TimerTem;		//Таймер для измерения температуры
	//BYTE	RegRead[16];	//Значения регистров АЦП
	//WORD	ConfigADC;
	
	float	fDAC;			//Значение записываемое в ЦАП
	float	fNewDAC;		//Новое значение записываемое в ЦАП
	
	WORD 		Timer;		//Таймер	
	TTarirCoef 	Coeff;		//Тарировочные коэффициенты расчитанные самим блоком
	float  		fADC[COUNT_CH];	//Значение напряжения в вольтах на выбранном в данный момент входе
	//==================
	BYTE	WriteCoeffFlash;
	BYTE    Status;			//Статус проведения измерения 4- данные готовы к использованию
	BYTE 	workRegim_AVV;	//Установленный в данный момент диапазон измерения 
	BYTE 	newRegim_AVV;	//Новый диапазон измерения
	//==================
	BYTE	RegimWork;		// Режим работы АВВ : 0 - тарировка; 1 - рабочий
}CAVV2;



typedef struct
{
	TTarirCoef 	ADC_New[COUNT_CH_REGIM][COUNT_CH];
	TTarirCoef	DAC_New;	
}CTARIR;

void InitAVV2C();
void DriverAVV();

extern CAVV2 	Avv;
extern CTARIR	Tarir_new;

#endif
#endif