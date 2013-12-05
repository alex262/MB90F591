#include "mb90590.h"
#include "global.h"
#include "flash.h"

#include INCLUDE_H

//#pragma section CODE=PROGR_DATA, attr=DATA,locate=0xF90000
//#pragma section FAR_CODE=PROGR_DATA, attr=DATA,locate=0xF90000



TProgram program;
TBuffer_pr buffer_pr;




void SetError(BYTE Error)
{
	SETBIT(program.Error,Error);
}
void ClearError(BYTE Error)
{
	CLEARBIT(program.Error,Error);
}
BYTE GetError()
{
	BYTE i;
	
	for(i=0;i<16;i++)
	{
		if(digit(program.Error,15-i)==1)
			return (15-i);
	}
	return 0;
}

void Indicate(WORD *pCount, WORD BLINK)
{
	if ((*pCount) < BLINK ) return;
	switch (GetError())
	{
		case ind_WORK:
			LEDR=1;
			LEDG=1;	
			break;
		case ind_COMA:
			LEDR=0;
			if((*pCount)>=BLINK)
			{
				(*pCount)=0;
				LEDG=~LEDG;
			}
			break;
		case ind_COM1:
			if((*pCount)>=BLINK)
			{
				(*pCount)=0;
				LEDG=~LEDG;
				LEDR=~LEDR;
			}
			break;
		case ind_FATERR:
			LEDG=0;
			if((*pCount)>=BLINK)
			{
				(*pCount)=0;
				LEDR=~LEDR;
			}
			break;
		case ind_RESET:
			LEDG=0;
			LEDR=0;
			break;
		case ind_TEST:
			LEDR=1;
			if((*pCount)>=BLINK)
			{
				(*pCount)=0;
				LEDG=~LEDG;
			}
			break;
		case ind_ERROR:
			LEDG=1;
			if((*pCount)>=BLINK)
			{
				(*pCount)=0;
				LEDR=~LEDR;
			}
			break;
/*		case ind_PWRAT:
			LEDG=1;
			LEDR=0;
			break;*/
	}	
}