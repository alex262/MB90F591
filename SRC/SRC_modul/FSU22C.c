#include "mb90590.h"
#include "fsu22C.h"
#include "appli.h"
		
#ifdef PLATA_FSU22C

void	(*INIT_BLOK)(void)	=InitFSU22C;
void	(*DRIVER_BLOK)(void)=Driver_FSU22C;
WORD	(*STATE_BLOCK)		=&Fsu22C.Info.word;

CFSU22_C Fsu22C;

void Reset_S();
void TestOutput();


void Sleep_1_5mk()
{
	BYTE i=10;
	while(i!=0)	i--;
}
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
void InitFSU22C()
{	
	BYTE i;
	//------------------
	//Откл чаем реле
	//------------------
	PR1=1;
	PR2=1;
	PS1=0;
	PS2=0;
	
	DDR0=0x00;
	DDR1=0x03;
	DDR2=0x00;
	DDR4=0x00;
	DDR5=0x00;
	DDR6=0xFF;
	DDR7=0xFF;
	DDR8=0xFF;
	DDR9=0x00;
		
	//------------------
	LEDR=1;
	LEDG=1;
	//------------------
	Reset_S();
	//Откл чение тестировани 
	//------------------
	//------------------
	Fsu22C.Timer_Test		=0;
	for(i=0;i<2;i++)
	{
		Fsu22C.Test[i]		=0;
		Fsu22C.State[i]		=0x5A;
		Fsu22C.Prin[i]		=0x00;
	}
	Fsu22C.State_NECHET	=0;
	Fsu22C.State_CHET	=0;
	Fsu22C.Prin_NECHET	=0;
	Fsu22C.Prin_CHET	=0;
	Fsu22C.St			=0;
	
	Fsu22C.Info.word	 =0;
	Fsu22C.Info.bits.Addr=ADDR;
	ADDR_NODE		  	 =ADDR;
	
	//Reset_S();
}
//=============================================================================
void Update_Data_BD_DOUT()
{
	BYTE i=0;
	BYTE state;
	
	switch (Fsu22C.St)
	{
		case 0:
		{
			TestOutput();
			__DI();
			if((Fsu22C.Prin[0]!=Fsu22C.State[0]) ||(Fsu22C.Prin[1]!=Fsu22C.State[1]))
			{
				Fsu22C.State[0]=Fsu22C.Prin[0];
				Fsu22C.State[1]=Fsu22C.Prin[1];
				
				state=Fsu22C.State[0];
				Fsu22C.Prin_NECHET=0;
				Fsu22C.Prin_CHET=0;
				for(i=0;i<4;i++)
				{
					Fsu22C.Prin_NECHET	|=digit(state,i*2+1)<<i;
					Fsu22C.Prin_CHET	|=digit(state,i*2)<<i;
				}
				state=Fsu22C.State[1];
				
				for(i=0;i<2;i++)
				{
					Fsu22C.Prin_NECHET	|=digit(state,i*2+1)<<(i+4);
					Fsu22C.Prin_CHET	|=digit(state,i*2)<<(i+4);
				}
				
				Fsu22C.State_CHET=Fsu22C.Prin_NECHET;
				Fsu22C.State_NECHET=Fsu22C.Prin_CHET;
				Fsu22C.St=1;
			}
			__EI();
		}break;
		case 1:
		{
			DOUT_ON(NE_CHET);
			Fsu22C.St=2;
		}break;
		case 2:
		{
			if(Fsu22C.Timer>5)
			{
				Reset_Set(NE_CHET);
				DOUT_ON(CHET);
				Fsu22C.St=3;
			}
		}break;
		case 3:
		{
			if(Fsu22C.Timer>5)
			{
				Reset_Set(CHET);
				DOUT_OFF(NE_CHET);
				Fsu22C.St=4;
			}
		}break;
		case 4:
		{
			if(Fsu22C.Timer>5)
			{
				Reset_Set(NE_CHET);
				DOUT_OFF(CHET);
				Fsu22C.St=5;
			}
		}break;
		case 5:
		{
			if(Fsu22C.Timer>5)
			{
				Reset_Set(CHET);
				Fsu22C.St=0;
			}
		}break;
		default:Fsu22C.St=0;
	}
}
//=============================================================================
void Driver_FSU22C()
{
	BYTE i;
	__DI();
	
	i=ADDR;	
	Fsu22C.Info.bits.Addr	=i;
	if(i!=ADDR_NODE)
	{
		setState(Initialisation);
		ADDR_NODE			=ADDR;
	}
	Fsu22C.Info.bits.Mode=MODE;
	//**************************************************
	Fsu22C.Info.bits.F1=PG_F;
	__EI();

	Update_Data_BD_DOUT();

	//**************************************************
	
}
//=============================================================================
void DOUT_OFF(BYTE Type)
{
	BYTE State;
	
	if(Type==NE_CHET)
	{
		State=Fsu22C.State_NECHET;
	}else
		{
			State=Fsu22C.State_CHET;
		}
	//------------------------------------
	//	Замыкаем  нужные реле
	//------------------------------------
	if(digit(State,0)==0)
	{
		S1=1;
		S2=1;
	}
	if(digit(State,1)==0)
	{
		S3=1;
		S4=1;
	}
	if(digit(State,2)==0)
	{
		S5=1;
		S6=1;
	}
	if(digit(State,3)==0)
	{
		S7=1;
		S8=1;
	}
	if(digit(State,4)==0)
	{
		S9=1;
		S10=1;
	}
	if(digit(State,5)==0)
	{
		S11=1;
		S12=1;
	}
	//------------------
	// Записываем данные
	//------------------
	if(Type==NE_CHET)
	{
		PS1=0;
		PR1=0;
	}else
		{
			PS2=0;
			PR2=0;
		}
	Fsu22C.Timer=0;
}
void DOUT_ON(BYTE Type)
{
	BYTE State;
	
	if(Type==NE_CHET)
	{
		State=Fsu22C.State_NECHET;
	}else
		{
			State=Fsu22C.State_CHET;
		}
	//------------------------------------
	//	Размыкаем  нужные реле
	//------------------------------------
	if(digit(State,0)==1)
	{
		S1=0;
		S2=0;
	}
	if(digit(State,1)==1)
	{
		S3=0;
		S4=0;
	}
	if(digit(State,2)==1)
	{
		S5=0;
		S6=0;
	}
	if(digit(State,3)==1)
	{
		S7=0;
		S8=0;
	}
	if(digit(State,4)==1)
	{
		S9=0;
		S10=0;
	}
	if(digit(State,5)==1)
	{
		S11=0;
		S12=0;
	}
	//------------------
	// Записываем данные
	//------------------
	if(Type==NE_CHET)
	{
		PS1=1;
		PR1=1;
	}else
		{
			PS2=1;
			PR2=1;
		}
	Fsu22C.Timer=0;
}
void Reset_Set(BYTE Type)
{
	if(Type==NE_CHET)
	{
		PS1=0;
		PR1=1;
	}else
		{
			PS2=0;
			PR2=1;
		}
	//-----------------
	Reset_S();
	Fsu22C.Timer=0;
}

void Reset_S()
{
	S1=1;
	S2=0;

	S3=1;
	S4=0;

	S5=1;
	S6=0;

	S7=1;
	S8=0;

	S9=1;
	S10=0;

	S11=1;
	S12=0;
}

//--------------------------------------------------------------------

void TestOutput()
{
	__DI();
	Fsu22C.Test[0]=K1|(K2<<1)|(K3<<2)|(K4<<3)|(K5<<4)|(K6<<5)|(K7<<6)|(K8<<7);
	Fsu22C.Test[1]=K9|(K10<<1)|(K11<<2)|(K12<<3);
	Fsu22C.Test[0]=~Fsu22C.Test[0];
	Fsu22C.Test[1]=(~Fsu22C.Test[1])&0xF;
	__EI();
	
}

#endif