/*----------------------------------------------------------------------*/
 // MAIN.C
/*----------------------------------------------------------------------*/
#include "mb90590.h"
#include "Reginit.h"
#include "global.h"
#include "can.h"
#include "timer.h"
#ifdef CAN_OPEN_ENABLE
	#include "objacces.h"
	#include "init.h"
#endif

#include INCLUDE_H


#define _NUM_ISD 2		//   и  ст   исп  ь   мых         EIIOS
//   тср      хр    г  т  м р  - 0.5 с  
void setup_watchdog()
{
	WDTC_WT |= 3;
	clrwdt;
}

//  пр д    и  при и ы п р   п с   пр гр ммы
void get_resetsource()
{
	unsigned char rst,ret;
	rst = WDTC;
	if (rst & 0x80)	ret = RST_POWERON;
	else
		if (rst & 0x40) ret = RST_STANDBY;
		else
			if (rst & 0x20) ret = RST_WATCHDOG;
			else
				if (rst & 0x10) ret = RST_RSTPIN;
				else
					if (rst & 0x08) ret = RST_RSTBIT;
					else ret=RST_UNKNOWN;
	program.Device_ReStart=ret;
}
//---------------------------------------------------------------------------------------------------------
void main(void)
{
	#ifdef CASH_PDO_DATA
	BYTE i;
	#endif
	//	#pragma asm
//		callp 0x100
//	#pragma endasm
	pwreset();								//»иициали аци  регистр  
	InitUART();								/*»нициали аци  UART 0,1,2*/
	SetupTime();							//ReloadTimer0(100 мс)	TimeBaseTimer (4.096 мс)
	get_resetsource();						//ќпределение при ины пер апуска
	InitIrqLevels();  						//»нициали аци  прерываний ми р    тр    р 
	__set_il(7);							/*  пр д   ютс   с   р   и */
	__EI();					    			/* ра решаютс  прерывани  */
	//puts("Reset\n\r");
	InitFlash();
	setup_watchdog();
	
	if(INIT_BLOK!=NULL)
		INIT_BLOK();
	#ifdef CAN_OPEN_ENABLE
		setState(Initialisation);
	#else
		SetupCAN(SPEED_CAN_0, SPEED_CAN_1);
	#endif
	while(1)
	{
		clrwdt;	
		//========================================
		#ifdef CAN_OPEN_ENABLE
			DriverCanOpen();
			#ifdef CASH_PDO_DATA
				for(i=0;i<18;i++) buildPDO_CASH(0x1800+i);
			#endif
		#endif
		//========================================
		if(DRIVER_BLOK!=NULL)
			DRIVER_BLOK();
		//========================================
	}
}
