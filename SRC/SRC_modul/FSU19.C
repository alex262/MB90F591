#include "mb90590.h"
#include "fsu19.h"
#include "appli.h"
		
#ifdef PLATA_FSU19

CFSU19 Fsu;

void 	(*INIT_BLOK)(void)=InitFSU19;
void 	(*DRIVER_BLOK)(void)=Driver_FSU19;
WORD (*STATE_BLOCK) = &Fsu.Info.word;




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
void InitFSU19()
{	
	BYTE i;
	
	DDR0=0x00;
	DDR1=0x03;
	DDR2=0x00;
	DDR4=0xFF;
	DDR5=0xFF;
	DDR6=0xFF;
	DDR7=0xFF;
	DDR8=0x00;
	DDR9=0x00;
	
	S_1=0;
	S_2=0;
	S_3=0;
	S_4=0;
		
	//------------------
	LEDR=1;
	LEDG=1;
	//------------------
	//------------------
	for(i=0;i<4;i++)
	{
		Fsu.State[i]=0;
		Fsu.Prin[i]	=0;
	}
	Fsu.Info.word=0;
	Fsu.Info.bits.Addr=ADDR;
	ADDR_NODE		  =ADDR;
}
//=============================================================================
void Driver_FSU19()
{
	BYTE i;
	
	i=ADDR;	
	Fsu.Info.bits.Addr	=i;
	if(i!=ADDR_NODE)
	{
		setState(Initialisation);
		ADDR_NODE			=ADDR;
	}
	Fsu.Info.bits.Mode=MODE;
	
	for(i=0;i<4;i++)
	{
		if(Fsu.Prin[i]!=Fsu.State[i])	//Устанавливаем новые команды
		{
			Fsu.State[i]=Fsu.Prin[i];
			
			if(i==0)
				S_1=Convert_n((BYTE)(Fsu.State[0]));
			if(i==1)
				S_2=Convert_n((BYTE)(Fsu.State[1]));
			if(i==2)
				S_3=Convert_n((BYTE)(Fsu.State[2]));
			if(i==3)
				S_4=Convert_n((BYTE)(Fsu.State[3]));
		}
	}
}
//=============================================================================
#endif