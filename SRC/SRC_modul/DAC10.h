#ifndef __DAC10__
#define __DAC10__

#include "global.h"

#ifdef PLATA_DAC10

#include "timer.h"

extern const char SoftwareVer[20]; 
//---------------------------------------------------------------------
//#define PLATA_DAC10_ZENIT
#define PLATA_DAC10_ROKOT

#define DEVICE_TYPE 8

#ifdef PLATA_DAC10_ZENIT
	#define NAME_MODUL "DAC10"
#endif
#ifdef PLATA_DAC10_ROKOT
	#define NAME_MODUL "DAC10-NR"
#endif
//---------------------------------------------------------------------


extern void (*INIT_BLOK)(void);		//Указатель на функции инициализации блока
extern void (*DRIVER_BLOK)(void);	//Указатель на функции драйвера блока
extern WORD *STATE_BLOCK;			//Уазатель на поле Info блока


//=====DAC=======================
#define MAX_COD_DAC		0xFFF	//Максимальное значение которое можно записать в ЦАП
#define MIN_COD_DAC		0		//Минимальное значение которое можно записать в ЦАП    



#define CS1		PDR8_P83	// Выбор SPI для соответствующего канала ЦАП
#define CS2		PDR8_P82
#define CS3		PDR8_P81
#define CS4		PDR8_P80
#define CS5		PDR7_P77
#define CS6		PDR7_P76
#define CS7		PDR4_P44
#define CS8		PDR4_P43
#define CS9		PDR4_P42
#define CS10	PDR4_P41
#define CS11	PDR4_P40
#define CS12	PDR3_P37

#define CS_ON	0
#define CS_OFF	1

#define SELECT_DAC(x)	PDR5=(PDR5&0xC0)|x // выбор ЦАПа

#define READ_MODE_SPI	1 
#define WRITE_MODE_SPI	0 


#define PWR_DAC_ON	1	// Питание ЦАП
#define PWR_DAC_OFF	0

#define PWR_DAC_1_6		PDR8_P86
#define PWR_DAC_7_12	PDR8_P85
//=====================================================
#define DAC_MASTER_SET_ON		PDR5_P56=0;	PDR5_P57=0;
#define DAC_MASTER_SET_OFF		PDR5_P56=1;	PDR5_P57=1;
#define DAC_STATUS_NEIGHBOUR	((PDR6>>4)&3)	//1- сосед выставил что он не мастер, 0 - сосед выставил что он мастер 
#define DAC_ADD_ADDR 			((PDR6>>6)&3)
//=====================================================
//=====================================================

#define MODE	(((~PDR0)>>4)&0xF)	//Состояние переключателей
#define ADDR	(PDR2&0x1F)			//Состояние переключателей

#define LEDR 	PDR1_P11
#define LEDG 	PDR1_P10


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
		WORD ErrSet	:1;
		WORD Resrv	:2;
	}bits;
}TInfo;

typedef struct
{
	float k;
	float ofs;
}TARIROV_K;

#define COUNT_DAC_CH	12
#define COUNT_ADC_CH	12
#define COUNT_DIN_CH	12
#define COUNT_DOUT_CH	12

#define COUNT_MAX1329	12

typedef struct
{
	TInfo	Info;	
	
	TYPE_DATA_TIMER	Timer;
	TYPE_DATA_TIMER	TimerDout;
	TYPE_DATA_TIMER	TimerDin;
	TYPE_DATA_TIMER	TimerAin;
	TYPE_DATA_TIMER	TimerTemp;
	TYPE_DATA_TIMER	TimerErrDac;
	
	BYTE	StRead;
	WORD	SelDAC_CH;
	WORD	SelDAC_CH_cur;
	WORD	wError;
	WORD	wOldError;				// старые ошибки
	WORD	EnOutDac;				// исп первые 12 бит, 1 - выход цапа коммутируется
	//WORD	setEnOutDac;			//что скомутировано в данный момент
	
	
	float	fDAC_New[COUNT_DAC_CH];
	float	fDAC_Set[COUNT_DAC_CH];
	WORD	wDAC_Set[COUNT_DAC_CH];
	float	fADC[COUNT_ADC_CH];
	float	Temperature[COUNT_MAX1329];
	BYTE	SPDT2_New[COUNT_DAC_CH];
	BYTE	SPDT2_Set[COUNT_DAC_CH];
	BYTE	DIN[COUNT_DIN_CH];
	BYTE	DOUT_New[COUNT_DOUT_CH];
	BYTE	DOUT_Set[COUNT_DOUT_CH];
	BYTE	HiLo;	// выдача меанднра для выдачи ЦАП
	BYTE	HiLoDec;// HiLo изменился 
	
	WORD	DiagRele;	// диагностика состояния реле
	
	BYTE	Temp[10];
	
		
	BYTE	WriteCoeffFlash;		//1-Записать данные во флеш память
	BYTE	SendFlagUart;

	BYTE	Master;					//Является ли данный ЦАП мастером
	WORD	TimerMaster;			//Таймер для выбора мастера
	WORD	TimerMasterError;		//Таймер для выбора мастера
	
	BYTE	StatusMaster;			//Статус выбора
	BYTE	TarrStatus;				//Оттарирован блок или нет, если не оттарирован то можно выставить мастера
	
	WORD	AddData;
	BYTE	ErrorSet;				// 1- били ошибки при включении реле больше не пытаемся стать мастером

}CDAC10;
//==============================================================
//формат выходного пакета для SPI для ЦАПа
typedef union
{
    BYTE    data;
    struct  
    {
        BYTE   adr		:5;
        BYTE   RW		:1;
        BYTE   start1	:1;
        BYTE   start0	:1;
    }bits;
}TPAK_SPI_RM;
typedef union
{
    BYTE    data;
    struct  
    {
        BYTE   Bip		:1;
        BYTE   Gain		:2;
        BYTE   Mux		:4;
        BYTE   start	:1;
    }bits;
}TPAK_SPI_ADC;
typedef union
{
    BYTE    data[2];
    struct  
    {
        WORD   dac		:12;
        WORD   ch		:1;
        WORD   rw		:1;
        WORD   d1		:1;
        WORD   start	:1;
    }bits;
}TPAK_SPI_DAC;
//==============================================================
typedef struct
{
	BYTE	DIN[COUNT_DIN_CH];			// Дискретные входы
	BYTE	DOUT[COUNT_DOUT_CH];		// Дискретные выходы
	BYTE	Temp[12];
	float	fStateDAC[COUNT_DAC_CH];	// Значения выдаваемые ЦАПом
	float	fStateADC[COUNT_ADC_CH];	// Значения читаемые АЦП
	float	Temperature[COUNT_MAX1329];	// Температура
}TSendPak1;
typedef struct
{
	TARIROV_K	tTarDAC[COUNT_DAC_CH];	// Тарировки ЦАПа
	TARIROV_K	tTarADC[COUNT_ADC_CH];	// Тарировки АЦП
}TSendPak2;

extern CDAC10 Dac10;

extern TARIROV_K	TarrRAM_DAC[COUNT_DAC_CH];	// Тарировки ЦАПа скопированные в RAM  
//extern TARIROV_K	TarrRAM_ADC[COUNT_ADC_CH];	// Тарировки АЦП скопированные в RAM  

extern TSendPak1 SendPak1;
extern TSendPak2 SendPak2;

//=================================================================
void InitDAC10(void);
void DriverDAC10(void);

#endif
#endif