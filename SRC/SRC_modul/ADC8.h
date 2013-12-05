#ifndef __ADC8__
#define __ADC8__

#include "global.h"
#include "timer.h"

#ifdef PLATA_ADC8

#define DEVICE_TYPE 4

#define NAME_MODUL "ADC8"

extern void (*INIT_BLOK)(void);		//Указатель на функции инициализации блока
extern void (*DRIVER_BLOK)(void);	//Указатель на функции драйвера блока
extern WORD *STATE_BLOCK;			//Уазатель на поле Info блока

#define MODE	(((~PDR0)>>4)&0xF)	//Состояние переключателей
#define ADDR	(PDR2&0x1F)			//Состояние переключателей


#define CS1_8	PDR7
#define CS9_16	PDR6
#define CS17_24	PDR5

#define SDA_A_1	PDR3_P37
#define SCL_A_1	PDR4_P40
#define D_SDA_1	DDR3_D37
#define D_SCL_1	DDR4_D40

#define SDA_A_2	PDR4_P44
#define SCL_A_2	PDR4_P43
#define D_SDA_2	DDR4_D44
#define D_SCL_2	DDR4_D43
//----------------------------

#define _CS1_D	DDR3_D37
#define _CS2_D	DDR4_D44
#define _CS1	PDR3_P37
#define _CS2	PDR4_P44

#define _DATA1	PDR7
#define _DATA2	PDR6
#define _DATA3	PDR5

#define D_DATA1	DDR7
#define D_DATA2	DDR6
#define D_DATA3	DDR5


//----------------------------
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
		WORD Resrv	:3;
	}bits;
}TInfo;

typedef struct
{
	float K;
	float Ofs;
}TARIROV_K;

#define COUNT_ADC_CH	24	


typedef struct
{
	TInfo	Info;	

	float   fADC[COUNT_ADC_CH];

	BYTE	WriteCoeffFlash;		//1-Записать данные во флеш память
	
	TYPE_DATA_TIMER TimerWait;		//ожидаем преобразования всех АЦП
}CADC8;


//-------------------------------------------------------------------------------
typedef struct
{
	DWORD	wCountTar;					// Количество тарировок
	TARIROV_K	tTar[COUNT_ADC_CH];	// Тарировки ЦАПа
}TSendPakTar;



extern TARIROV_K k_new[COUNT_ADC_CH];
extern CADC8 Adc;

//=================================================================
void InitADC8();
void DriverADC8();
void SendTarADC8(void);
//=================================================================


#endif
#endif