#ifndef __test__
#define __test__
#include "global.h"
#ifdef CAN_OPEN_ENABLE
	#include "appli.h"
#endif


#ifdef PLATA_TEST
#define NAME_MODUL "TEST"
#define DEVICE_TYPE 1


extern void (*INIT_BLOK)(void);
extern void (*DRIVER_BLOK)(void);
extern WORD *STATE_BLOCK;			//Уа атель на поле Info блока


#define LEDR 	PDR1_P11
#define LEDG 	PDR1_P10

#define MODE	(((~PDR0)>>4)&0xF)	//Состояние переключателей
#define ADDR	(PDR2&0x1F)		//Состояние переключателей
#define RSRV	PDR1_P17

typedef struct
{
	WORD	word;
	BYTE	pr;
	BYTE	set;
	float	f_data[25];
	WORD	w_data[25];
	BYTE	b_data[25];
}CTest;

void InitTest();
void Driver_Test();

extern CTest Test;

#endif
#endif