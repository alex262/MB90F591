#include "mb90590.h"
#include "fsu28.h"
#include "appli.h"
#include "timer.h"


		
#ifdef PLATA_FSU28

const char SoftwareVer[20] = { __TIME__" " __DATE__}; 

void 	(*INIT_BLOK)(void)	=InitFSU28;
void 	(*DRIVER_BLOK)(void)=Driver_FSU28;
WORD	(*STATE_BLOCK)		= &Fsu.Info.word;

CFSU28 Fsu;
//==================================================================
static TYPE_DATA_TIMER TimerStartBlock = 1000/TIMER_RESOLUTION_MS;
static BYTE stStartBlock = FALSE;
//==================================================================
BYTE Convert_f(BYTE n)
{
	BYTE i,s=0;
	for(i=0;i<3;i++)
	{
		s|=digit(n,i)<<(2-i);
	}
	return s;
}
//==================================================================
BYTE Convert_n(BYTE n)
{
	BYTE i,s=0;
	for(i=0;i<8;i++)
	{
		s|=digit(n,i)<<(7-i);
	}
	return s;
}
void InitFSU28()
{	
	add_timer(&TimerStartBlock);
		//------------------
	//Отключение тестирования
	STRB1=1;
	STRB2=1;
	STRB3=1;
	STRB4=1;
	//------------------
	S_1=0;	
	S_2=0;
	S_3=0;
	//------------------
	
	DDR0=0x00;
	DDR1=0x03;
	DDR2=0x00;
	DDR4=0xFF;
	DDR5=0x00;
	DDR6=0xFF;
	DDR7=0xFF;
	DDR8=0xFF;
	DDR9=0x00;
		
	//------------------
	LEDR=1;
	LEDG=1;
	//------------------
	Fsu.Test	= 0;
	Fsu.State	= 0;	
	Fsu.Prin	= 0;
	
	Fsu.Info.word=0;
	Fsu.Info.bits.Addr=ADDR;
	ADDR_NODE		  =ADDR;

}
//=============================================================================
//=============================================================================
void Driver_FSU28()
{
	BYTE i;
	DWORD tmp;
	
	//------------------------------------------------
	// обновление адреса блока
	if(stStartBlock == FALSE)
	{
		if(getTime(&TimerStartBlock))	// если адрес изменился в течение первой секнды то переинициализируем блок
		{
			i=ADDR;	
			Fsu.Info.bits.Addr	=i;
			if(i!=ADDR_NODE)
			{
				setState(Initialisation);
				ADDR_NODE			=ADDR;
			}
		}else
		{ 
			del_timer(&TimerStartBlock);
			stStartBlock = TRUE;
		}
	}
	//----------------------------------------------------	
	Fsu.Info.bits.Mode=MODE;
	Fsu.Info.bits.F1=PG_F1;
	Fsu.Info.bits.F2=PG_F1;
	//**************************************************
	if(Fsu.Prin!=Fsu.State)	//Устанавливаем новые команды
	{
		Fsu.State=Fsu.Prin;
		tmp=Fsu.State;
		
		
		S_1=Convert_n((BYTE)(tmp));
		S_2=Convert_n((BYTE)(tmp>>8));
		S_3=Convert_n((BYTE)(tmp>>16));
		
	}
	TestOutput();	
}
//=============================================================================
void Sleep_1_5mk()
{
	volatile BYTE i=20;
	while(i!=0)	i--;
}
//=============================================================================
void TestOutput()
{
	DWORD t=0, test;
	
	STRB1=0;
	Sleep_1_5mk();
	test=K1_6;
	STRB1=1;
	
	STRB2=0;
	Sleep_1_5mk();
	t=K1_6;
	test|=(DWORD)(t<<6);
	STRB2=1;
	
	STRB3=0;
	Sleep_1_5mk();
	t=K1_6;
	test|=(DWORD)(t<<12);
	STRB3=1;
	
	STRB4=0;
	Sleep_1_5mk();
	t=K1_6;
	test|=(DWORD)(t<<18);
	STRB4=1;
	test =~ test; //Зенит
	Fsu.Test=test^RELE_TIP;	 
}

#endif