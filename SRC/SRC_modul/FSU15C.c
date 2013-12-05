#include "mb90590.h"
#include "fsu15c.h"
#include "appli.h"
		
#ifdef PLATA_FSU15_C

CFSU15_C Fsu15;
void 	(*INIT_BLOK)(void)=InitFSU15C;
void 	(*DRIVER_BLOK)(void)=DriverFSU15_C;
WORD	(*STATE_BLOCK) 		= &Fsu15.Info.word;

void InitFSU15C()
{	
//	Fsu15.Temp=0;
//	Fsu15.Temp=PDR6;
//	Fsu15.Temp=Fsu15.Temp<<8;
//	Fsu15.Temp|=PDR7;
	
	DDR0=0x00;
	DDR1=0x03;
	DDR2=0x00;
	DDR4=0x00;
	DDR5=0x00;
	DDR6=0x3f;
	DDR7=0x3f;
	DDR8=0x00;
	DDR9=0x00;
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
			
	//------------------
	LEDR=1;
	LEDG=1;
	//------------------
	INIT_BLOK=InitFSU15C;	

	//------------------
	Fsu15.Test			=0;
	Fsu15.State			=0;
	Fsu15.Prin			=0;
	
	Fsu15.Info.bits.Addr=ADDR;
	ADDR_NODE	        =ADDR;
	//Reset_S();
}

//====================================================================
void WriteOutput()
{
	WORD d;
	if(Fsu15.State!=Fsu15.Prin)
	{
		Fsu15.State=Fsu15.Prin;
		d=Fsu15.State;
		S1=digit(d,0);
		S2=digit(d,1);
		S3=digit(d,2);
		S4=digit(d,3);
		S5=digit(d,4);
		S6=digit(d,5);
		S7=digit(d,6);
		S8=digit(d,7);
		S9=digit(d,8);
		S10=digit(d,9);
		S11=digit(d,10);
		S12=digit(d,11);
	}
}
//================================================
void ReadTest()
{
	Fsu15.Test=K1_6;
	Fsu15.Test|=K7_12<<6;
}
//================================================
void DriverFSU15_C()
{
	BYTE i;
	__DI();
	i=ADDR;	
	Fsu15.Info.bits.Addr	=i;
	if(i!=ADDR_NODE)
	{
		setState(Initialisation);
		ADDR_NODE			=ADDR;
	}
	Fsu15.Info.bits.Mode=MODE;
	Fsu15.Info.bits.F1=PG_F1;
	#ifdef PLATA_FSU15
		Fsu15.Info.bits.F2=PG_F2;
	#endif

	WriteOutput();
	ReadTest();
	__EI();
	
}


#endif