//   SIO
#include "mb90590.h"
#include "global.h"
#include "sio.h"

#include INCLUDE_H

//Инициализация интерфейса последовательного В/В
void InitSIO(BYTE speed)
{
	SMCS_STOP 	= 1;		    /* stop it             				*/
	SMCS_SIE 	= 0;			/* disable interrupt   				*/
	SMCS_MODE 	= 0;   		   	/* start condition MODE 1 by R/W 	*/
	SMCS_BDS 	= 1;		    /* MSB first           				*/
	
	//---SPEED----------------------------------------------------
	CDCR 		= 0xFC;			/* prescaler divider 4 SCLK=1MHz*/
	switch (speed)
	{
		case SIO_2MHz:
		{
			SMCS_SMD0 	= 0;	   		/* 2 MHz */
			SMCS_SMD1 	= 0;
			SMCS_SMD2 	= 0;
		}break;
		case SIO_1MHz:
		{
			SMCS_SMD0 	= 1;	   		/* 1 MHz */
			SMCS_SMD1 	= 0;
			SMCS_SMD2 	= 0;
		}break;
		case SIO_250KHz:
		{
			SMCS_SMD0 	= 0;	   		/* 250 KHz */
			SMCS_SMD1 	= 1;
			SMCS_SMD2 	= 0;
		}break;
		case SIO_125KHz:
		{
			SMCS_SMD0 	= 1;	   		/* 125 KHz */
			SMCS_SMD1 	= 1;
			SMCS_SMD2 	= 0;
		}
		default:
		{
			SMCS_SMD0 	= 1;	   		/* 1 MHz */
			SMCS_SMD1 	= 0;
			SMCS_SMD2 	= 0;
		}	
	}
	//------------------------------------------------------------
	SMCS_SOE 	= 1;			/* serial data output  */
	SMCS_SCOE 	= 1;			/* serial clock output */
								/* 0: general purpose I/O or ext. CLK 	*/
								/* 1: int. CLK 				            */
	SMCS_STRT 	= 0;			/* eneble, if started by data*/
	
	
	
	#ifdef	PLATA_AVV2C
		SES 		= 1; //Avv
	#else
		SES 		= 0; 
	#endif
}
//Старт передачи по SIO
void start_sio(void)
{
	SMCS_STOP = 0;
	SMCS_STRT = 1;
	while(SMCS_BUSY == 1);	/* wait until transmit is complete */
}
//Стоп передачи по SIO
void stop_sio(void)
{
	SMCS_STOP = 1;
	SMCS_STRT = 0;
	SMCS_BUSY = 0;
}
//-------------------------------------------------------------------
//Отправка байта, возвращает принятый байт 
BYTE Send_SIO(BYTE data)
{
	SDR=data;
	SMCS_STOP = 0;
	SMCS_STRT = 1;
	while(SMCS_BUSY == 1);	/* wait until transmit is complete */
	return SDR;
}
//-------------------------------------------------------------------
//-----------------------------------
// Invert - 0 - клоки не инвертированы 1 - инверитровать
void SetInvertSIO(BYTE Invert)
{
	Invert &= 1;
	SES = Invert; 
}
//-----------------------------------
// MSB first bit
void SetMSBFirstSIO(void)
{
	SMCS_STOP 	= 1;		    /* stop it             				*/
	SMCS_BDS 	= 1;		    /* MSB first           				*/
}
// LSB first bit
void SetLSBFirstSIO(void)
{
	SMCS_STOP 	= 1;		    /* stop it             				*/
	SMCS_BDS 	= 0;		    /* LSB first           				*/
}
