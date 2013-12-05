#ifndef __DS401_h
#define __DS401_h
#include "OD.h"
//--------------------------------
#define NUMBER_DOUT_8		3
#define NUMBER_DIN_8		4
//----------0x1000----------------
#define	DS401_PROFILE 	401
#define DIN				0x00010000	
#define DOUT		  	0x00020000	
#define AIN				0x00040000
#define AOUT		  	0x00080000		
//-----------------------------------------------------------------------------
//					DOUT
//-----------------------------------------------------------------------------
//	0x6200 Записываемые данные 

typedef struct
{
	Unsigned8 	NumberEntry;
	Unsigned8	Data[NUMBER_DOUT_8];
}WRITE_DATA_DOUT;
//--------------------------------
//--------------------------------
//	0x6202 Полярность выходов 
typedef struct
{
	Unsigned8 	NumberEntry;
	Unsigned8	Data[NUMBER_DOUT_8];
}POLARITY_DOUT;
//--------------------------------
//--------------------------------
//	0x6206 Режим ошибки  
typedef struct
{
	Unsigned8 	NumberEntry;
	Unsigned8	Data[NUMBER_DOUT_8];
}ERROR_MODE_DOUT;
//--------------------------------
//--------------------------------
//	0x6207 Значение выходов  при ошибке   
typedef struct
{
	Unsigned8 	NumberEntry;
	Unsigned8	Data[NUMBER_DOUT_8];
}ERROR_VALUE_DOUT;
//--------------------------------
//--------------------------------
//	0x6208 Фильтр выходов   
typedef struct
{
	Unsigned8 	NumberEntry;
	Unsigned8	Data[NUMBER_DOUT_8];
}FILTER_DOUT;
//--------------------------------
//--------------------------------
//	0x6209 Обратная связь   
typedef struct
{
	Unsigned8 	NumberEntry;
	Unsigned8	Data[NUMBER_DOUT_8];
}TEST_DOUT;
//--------------------------------
//-------------------------------------------------------------------
//-----------------------------------------------------------------------------
//					DIN
//-----------------------------------------------------------------------------
//	0x6000 Состояние входов
typedef struct
{
	Unsigned8 	NumberEntry;
	Unsigned8	Data[NUMBER_DIN_8];
}READ_DATA_DIN;
//--------------------------------
//	0x6002 Полярность входов
typedef struct
{
	Unsigned8 	NumberEntry;
	Unsigned8	Data[NUMBER_DIN_8];
}POLARITY_DIN;
//--------------------------------
//	0x6003 Фильтр входов
typedef struct
{
	Unsigned8 	NumberEntry;
	Unsigned8	Data[NUMBER_DIN_8];
}FILTER_DIN;
//--------------------------------
//	0x6009 Тест входов
typedef struct 
{
	Unsigned8 	NumberEntry;
	Unsigned8	Data[NUMBER_DIN_8];
}TEST_DIN;
//--------------------------------




//extern	WRITE_DATA_DOUT	__far	Write_Data_Dout;
//extern 	POLARITY_DOUT	__far	Polarity_Dout;

//extern	READ_DATA_DIN	__far	Read_Data_Din;
//extern	POLARITY_DIN	__far	Polarity_Din;
//extern	FILTER_DIN		__far	Filter_Din;
//extern	TEST_DIN		__far	Test_Din;
#endif 
