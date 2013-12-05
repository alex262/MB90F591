#include "appli.h"
#include "global.h"
#include "FSU22.h"
		
#ifdef PLATA_FSU22

void 	(*INIT_BLOK)(void)=InitFSU22;
void 	(*DRIVER_BLOK)(void)=Driver_FSU22;
WORD 	(*STATE_BLOCK) = &Fsu22.Info.word;

CFSU22 Fsu22;

void TestOutput();

void Sleep_5ms()
{
	DWORD i=80000;
	while(i!=0)	i--;
}
void Sleep_1_5mk()
{
	DWORD i=10;
	while(i!=0)	i--;
}
//==================================================================
void InitFSU22()
{	
	//------------------
	//Отключаем реле
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
	S1=0;
	S2=0;
	S3=0;
	S4=0;
	S5=0;
	S6=0;
	S7=0;
	S8=0;
	S9=0;
	S10=0;
	S11=0;
	S12=0;
	
	
	D_STRB1 = 0;
	D_STRB2 = 0;
	D_STRB3 = 0;
	D_STRB4 = 0;
	STRB1=1;
	STRB2=1;
	STRB3=1;
	STRB4=1;
	//------------------
	Fsu22.Timer_Test	=0;
	Fsu22.Test.word		=0;
	Fsu22.State.word	=0;
	Fsu22.Prin.word		=0;
	
	Fsu22.Info.word		=0;
	Fsu22.Info.bits.Addr=ADDR;
	ADDR_NODE		  	=ADDR;
}
//=============================================================================

//=============================================================================
void Driver_FSU22()
{
	BYTE i;
	__DI();
	
	i=ADDR;	
	Fsu22.Info.bits.Addr	=i;
	if(i!=ADDR_NODE)
	{
		setState(Initialisation);
		ADDR_NODE			=ADDR;
	}
	Fsu22.Info.bits.Mode=MODE;
	//**************************************************
	Fsu22.Info.bits.F1=PG_F1;
	//**************************************************
	
	if(Fsu22.Prin.word!=Fsu22.State.word)	//Устанавливаем новые команды
	{
		Fsu22.State.word=Fsu22.Prin.word;
		
		S1=Fsu22.State.bits.O1;
		S2=Fsu22.State.bits.O2;
		S3=Fsu22.State.bits.O3;
		S4=Fsu22.State.bits.O4;
		S5=Fsu22.State.bits.O5;
		S6=Fsu22.State.bits.O6;
		
		S7=Fsu22.State.bits.O7;
		S8=Fsu22.State.bits.O8;
		S9=Fsu22.State.bits.O9;
		S10=Fsu22.State.bits.O10;
		S11=Fsu22.State.bits.O11;
		S12=Fsu22.State.bits.O12;
		
		Fsu22.Timer_Test=0;
	}
	__EI();
	//**************************************************
	TestOutput();	
	//**************************************************
}
//=============================================================================
//--------------------------------------------------------------------
void TestOutput()
{
	DWORD t=0;
	
	//if(Fsu22.Timer_Test<10) return;
	
	Fsu22.Timer_Test=10;
	
	STRB1=0;
	D_STRB1=1;
	Sleep_1_5mk();
	__DI();
	Fsu22.Test.bits.O1= ~(K1 | K2);
	Fsu22.Test.bits.O2= ~(K3 | K4);
	Fsu22.Test.bits.O3= ~(K5 | K6);
	__EI();
	D_STRB1=0;
	STRB1=1;
	
	
	STRB2=0;
	D_STRB2=1;
	Sleep_1_5mk();
	__DI();
	Fsu22.Test.bits.O4= ~(K1 | K2);
	Fsu22.Test.bits.O5= ~(K3 | K4);
	Fsu22.Test.bits.O6= ~(K5 | K6);
	__EI();
	D_STRB2=0;
	STRB2=1;
	
	D_STRB3=1;
	STRB3=0;
	Sleep_1_5mk();
	__DI();
	Fsu22.Test.bits.O7= ~(K1 | K2);
	Fsu22.Test.bits.O8= ~(K3 | K4);
	Fsu22.Test.bits.O9= ~(K5 | K6);
	__EI();
	D_STRB3=0;
	STRB3=1;
	
	D_STRB4=1;
	STRB4=0;
	Sleep_1_5mk();
	__DI();
	Fsu22.Test.bits.O10= ~(K1 | K2);
	Fsu22.Test.bits.O11= ~(K3 | K4);
	Fsu22.Test.bits.O12= ~(K5 | K6);
	__EI();
	D_STRB4=0;
	STRB4=1;
}
#endif