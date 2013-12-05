#ifndef __ADC__
#define __ADC__

#include "global.h"

#ifdef PLATA_ADC
#define DEVICE_TYPE 4
//#define NAME_MODUL "ADC5-C"
#define NAME_MODUL "ADC6"

extern const char SoftwareVer[20]; 


extern void (*INIT_BLOK)(void);		//Указатель на функции инициализации блока
extern void (*DRIVER_BLOK)(void);	//Указатель на функции драйвера блока
extern WORD *STATE_BLOCK;			//Уазатель на поле Info блока

#define PG_F1	PDR9_P92
#define PG_F2	PDR9_P93

#define BUSY	PDR9_P94
#define NCNVRT	PDR1_P12

#define SIO_SCLK	PDR4_P46
#define SIO_SDATA	PDR4_P45


#define CONVERT_ADC NCNVRT=0;NCNVRT=1;	

#define RSRV	PDR1_P17

#define NCS		PDR5_P52
#define SDA		PDR5_P53
#define SCL		PDR5_P54

#define A0		PDR6_P60
#define A1		PDR6_P61
#define A2		PDR6_P62

#define EN0		PDR6_P64
#define EN1		PDR6_P65
#define EN2		PDR6_P66
#define EN3		PDR6_P67

#define rSEL_CH	PDR6

#define SC0		PDR4_P40
#define SC1		PDR4_P41


#define MODE	(((~PDR0)>>4)&0xF)	//Состояние переключателей
#define ADDR	(PDR2&0x1F)		//Состояние переключателей

#define LEDR 	PDR1_P11
#define LEDG 	PDR1_P10



void InitADC5C();

/*__nosavereg*/ __interrupt void INT2(void);


typedef union
{
	WORD	word;
	struct
	{
		WORD Addr	:5;	
		WORD Mode	:4;	//Тест DAC->ADC
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
}TARIROV_K;

#define CICKL_OPROS_TEM			100	//ms
#define COUNT_TAR_COEFF			33	
#define COUNT_TEST_VALUE 		20		// Количество тестовых значений	
#define POGRESHNOST_DAC			0.2		// Допустимая погрешность ЦАПа
#define COUNT_CICKLE_S_ERROR	2		// Допустимое количество циклов с ошибкой пока не зажигаем неисправность


typedef struct
{
	float 	DAC;
	float 	newDAC;
	TInfo	Info;	
	WORD 	Temp;
	WORD	TimerTem;
	WORD	Timer;
	BYTE	StRead;
	float   fADC[33];

	BYTE	WriteCoeffFlash;		//1-Записать данные во флеш память
	
	BYTE	EnableTest;				// Разрешение тестирования ЦАП->АЦП
	BYTE	CurTest;				// 
	BYTE	ErrADC;					// 0 бит 1-7 каналы; 1 бит 8-14 каналы; 2 бит 15-21 каналы; 3 бит 22-28 каналы;
	BYTE	CountErr[4];			// счётчики циклов с ошибками подряд
	BYTE	Err[4];					// счётчики ошибок по мультиплексорам
	WORD	TimerTest;
	BYTE	Reg;
	
}CADC5;


//-------------------------------------------------------------------------------
typedef struct
{
	DWORD	wCountTar;					// Количество тарировок
	TARIROV_K	tTar[COUNT_TAR_COEFF];	// Тарировки ЦАПа
}TSendPakTar;



extern TARIROV_K k_33_new[COUNT_TAR_COEFF];
extern CADC5 Adc;

//=================================================================

//void GetAndWriteTarirov(BYTE in);
void DriverADC5();
void SendTarADC6(void);
void DriverADC5_rgd();
//=================================================================


#endif
#endif