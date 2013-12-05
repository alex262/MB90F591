#ifndef __ADC__
#define __ADC__

#include "global.h"

#ifdef PLATA_DAC9

#define DEVICE_TYPE 8
#define NAME_MODUL "DAC9"


extern void (*INIT_BLOK)(void);		//Указатель на функции инициализации блока
extern void (*DRIVER_BLOK)(void);	//Указатель на функции драйвера блока
extern WORD *STATE_BLOCK;			//Уазатель на поле Info блока

//=====ADC=======================
#define A0		PDR6_P60
#define A1		PDR6_P61
#define A2		PDR6_P62
#define EN1		PDR6_P64
#define EN2		PDR6_P65
#define ADC_ON	1
#define ADC_OFF	0
#define ADC_A(n)		PDR6=(PDR6&0x30)|(n&7);

#define CONVN_ADC		PDR4_P44
#define CONVERT_ADC 	CONVN_ADC=0;CONVN_ADC=1;	
#define BUSY_ADC 		PDR5_P53
//===============================
// Выбираем с кем будем работать АЦП или ЦАП
#define SELECT_WORK_SPI(n)	PDR4_P43=n;	//ADN
#define SEL_ADC		1
#define SEL_DAC		0
//=====DAC=======================
#define MAX_COD_DAC     0xFFF   //Максимальное значение которое можно записать в ЦАП
#define MIN_COD_DAC     0       //Минимальное значение которое можно записать в ЦАП    

// Комутация аналоговых выходов
#define OFF_ALL_DAC	PDR7=0x00;PDR8=PDR8&0xC0;
#define ON_ALL_DAC	PDR7=0xFF;PDR8=PDR8|0x3F;
#define SELECT_ALL_DAC	0x3FFF

#define K1	PDR8_P85
#define K2	PDR8_P84
#define K3	PDR8_P83
#define K4	PDR8_P82
#define K5	PDR8_P81
#define K6	PDR8_P80
#define K7	PDR7_P77
#define K8	PDR7_P76
#define K9	PDR7_P75
#define K10	PDR7_P74
#define K11	PDR7_P73
#define K12	PDR7_P72
#define K13	PDR7_P71
#define K14	PDR7_P70

#define DAC_ON	1
#define DAC_OFF	0

#define BUSY_DAC 		PDR5_P54
#define LOAD_DAC 		PDR4_P42	//Запись данных в ЦАП
#define SYNC_DAC 		PDR4_P41	//Выбор ЦАП
#define CLRN_DAC 		PDR4_P40

#define LOAD_DAC_RUN	LOAD_DAC=0;LOAD_DAC=1;	//Запись данных в ЦАП

//===============================



#define MODE	(((~PDR0)>>4)&0xF)	//Состояние переключателей
#define ADDR	(PDR2&0x1F)		//Состояние переключателей

#define LEDR 	PDR8_P86
#define LEDG 	PDR8_P87


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
	float k;
	float ofs;
}TARIROV_K;

#define CICKL_OPROS_TEM	500	//ms
#define COUNT_DAC_CH	14
#define COUNT_ADC_CH	16
#define dERR_DAC_V		0.1
typedef struct
{
	TInfo	Info;	
	WORD	TimerTem;
	WORD	TimerErrDac;
	
	BYTE	StRead;
	WORD	SelDAC_CH;
	WORD	SelDAC_CH_cur;
	float   fDAC_New[COUNT_DAC_CH];
	float   fDAC_Cur[COUNT_DAC_CH];
	float   fADC[COUNT_ADC_CH];
//	float   fErrADC[COUNT_ADC_CH];
	
	WORD	wError;					// Исправность ЦАП сравнивается выданное значение со считанным АЦП 
									// погрешность в вольтах dERR_DAC_V
	float	Temp;					// Температура
	BYTE	WriteCoeffFlash;		//1-Записать данные во флеш память
	BYTE	SendFlagUart;
}CDAC9;
//==============================================================
//формат выходного пакета для SPI для ЦАПа
typedef union
{
    BYTE    data[3];
    struct  
    {
        DWORD   tmp :2;
        DWORD   DB  :12;
        DWORD   REG :2;
        DWORD   A   :5;
        DWORD   zero:1;
        DWORD   RW  :1;
        DWORD   AB  :1;    
    }bits;
}TPAK_SPI;
typedef struct
{
	DWORD	wSelectDAC;					// Показываются подключенные к выходу канала ЦАПа
	float	fStateDAC[COUNT_DAC_CH];	// Значения выдаваемые ЦАПом
	float	fStateADC[COUNT_ADC_CH];	// Значения читаемые АЦП
	TARIROV_K	tTarDAC[COUNT_DAC_CH];	// Тарировки ЦАПа
	TARIROV_K	tTarADC[COUNT_ADC_CH];	// Тарировки АЦП
}TSendPak;

extern CDAC9 Dac9;
extern TARIROV_K	TarrRAM_DAC[COUNT_DAC_CH];	// Тарировки ЦАПа скопированные в RAM  
extern TARIROV_K	TarrRAM_ADC[COUNT_ADC_CH];	// Тарировки АЦП скопированные в RAM  
extern TSendPak SendPak;

//=================================================================
void InitDAC9(void);
void DriverDAC9(void);

#endif
#endif