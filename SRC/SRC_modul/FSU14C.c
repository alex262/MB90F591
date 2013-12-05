#include "mb90590.h"
#include "fsu.h"
#include "appli.h"
#include "timer.h"


/*DWORD MAS[24]={	0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080,
		0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000,
		0x010000,0x020000,0x040000,0x080000,0x100000,0x200000,0x400000,0x800000};*/
		
#ifdef PLATA_FSU

const char SoftwareVer[20] = { __TIME__" " __DATE__}; 

void 	(*INIT_BLOK)(void)=InitFSU14C;
void 	(*DRIVER_BLOK)(void)=Driver_FSU14_C;
WORD	(*STATE_BLOCK) 		= &Fsu.Info.word;

CFSU14_C Fsu;

WORD TimeOutSetData = 5/TIMER_RESOLUTION_MS;

void Sleep_1_5mk()
{
	volatile BYTE i=20;
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
void InitFSU14C()
{	
	//------------------
	//Отключаем реле
	//------------------
	PR1=1;
	PR2=1;
	PS1=0;
	PS2=0;
	//------------------
	//Отключение тестирования
	STRB1=1;
	STRB2=1;
	STRB3=1;
	STRB4=1;
	//------------------
	Reset_S();
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
	Fsu.Timer_Test		=0;
	Fsu.Test			=0;
	Fsu.State			=0x5a;
	Fsu.Prin			=0x5a;
	Fsu.State_NECHET	=0;
	Fsu.State_CHET		=0;
	Fsu.Prin_NECHET		=0;
	Fsu.Prin_CHET		=0;
	Fsu.St				=0;
	
	Fsu.Info.word=0;
	Fsu.Info.bits.Addr=ADDR;
	ADDR_NODE		  =ADDR;

	
	//DOUT_ON(NE_CHET);
	//DOUT_ON(CHET);
	//Reset_S();
}
//=============================================================================
void Update_Data_BD_DOUT()
{
	BYTE i=0;
//	DWORD *pDW;
	DWORD state,chet=0,nechet=0;
	
	//===================================
	//Fsu.Prin=RESERV;
	//===================================
	switch (Fsu.St)
	{
		case 0:
		{
			TestOutput();
			if(Fsu.Prin!=Fsu.State)
			{
				Fsu.State=Fsu.Prin;
				state=Fsu.State;
				Fsu.Prin_NECHET=0;
				Fsu.Prin_CHET=0;
				for(i=0;i<12;i++)
				{
					if(i<4)
					{
						Fsu.Prin_NECHET	|=digit(state,i*2+1)<<i;
						Fsu.Prin_CHET	|=digit(state,i*2)<<i;
					}
					if(i>3 && i<8)
					{
						if(i==4)
							state=state>>8;
						Fsu.Prin_NECHET	|=digit(state,(i-4)*2+1)<<i;
						Fsu.Prin_CHET	|=digit(state,(i-4)*2)<<i;
					}
					if(i>7)
					{
						if(i==8)
							state=state>>8;
						Fsu.Prin_NECHET	|=digit(state,(i-8)*2+1)<<i;
						Fsu.Prin_CHET	|=digit(state,(i-8)*2)<<i;
					}
				}
				Fsu.State_CHET=Fsu.Prin_NECHET;
				Fsu.State_NECHET=Fsu.Prin_CHET;
				Fsu.St=1;
			}
		}break;
		case 1:
		{
			if(Fsu.Timer>TimeOutSetData)
			{
				DOUT_ON(NE_CHET);
				Fsu.St=2;
			}
		}break;
		case 2:
		{
			if(Fsu.Timer>TimeOutSetData)
			{
				Reset_Set(NE_CHET);
				DOUT_ON(CHET);
				Fsu.St=3;
			}
		}break;
		case 3:
		{
			if(Fsu.Timer>TimeOutSetData)
			{
				Reset_Set(CHET);
				DOUT_OFF(NE_CHET);
				Fsu.St=4;
			}
		}break;
		case 4:
		{
			if(Fsu.Timer>TimeOutSetData)
			{
				Reset_Set(NE_CHET);
				DOUT_OFF(CHET);
				Fsu.St=5;
			}
		}break;
		case 5:
		{
			if(Fsu.Timer>TimeOutSetData)
			{
				Reset_Set(CHET);
				Fsu.St=0;
			}
		}break;
	}
}
WORD TimeOut3s = 3000/TIMER_RESOLUTION_MS;
WORD TimeOutOn = 50/TIMER_RESOLUTION_MS;
WORD TimeOutOn2 = 50/TIMER_RESOLUTION_MS;
BYTE St2=0;
void Update_Data_BD_DOUT_Test()
{
	BYTE i=0;
	
	switch (St2)
	{
		case 0:
		{
			if(((Fsu.Prin>>8)&0xFF) != 0)
			{
				TimeOutOn2 = ((Fsu.Prin>>8)&0xFF)*2;
				St2=1;
			}	
		}break;
		case 1:
		{			// разомкнули
			S13 = 1;
			S14 = 1;
				
			PR2= 0;
			PS2= 0;
			
			St2=2;
			Fsu.Timer2 = 0;
		}break;
		case 2:
		{
			if(Fsu.Timer2>TimeOutSetData) // ждём коммутации
			{
				PR2= 1;
				PS2= 0;
				S13 = 1;
				S14 = 0;
				
				St2=3;
				Fsu.Timer2 = 0;
			}
		}break;
		case 3:
		{
			if(Fsu.Timer2 > TimeOutOn2) // Таймаут
			{
				// замкнули
				S13 = 0;
				S14 = 0;
				PR2= 1;
				PS2= 1;
				
				Fsu.Timer2 = 0;
				St2=4;
			}
		}break;
		case 4:
		{
			if(Fsu.Timer2>TimeOutSetData)
			{
				PR2= 1;
				PS2= 0;
				S13 = 1;
				S14 = 0;
				St2=5;
				Fsu.Timer2 = 0;
			}
		}break;
		case 5:
		{
			if(Fsu.Timer2>TimeOut3s)
			{
				St2=0;
			}
		}break;
	}
	//-----------------------------------------------------
	switch (Fsu.St)
	{
		case 0:
		{
			if((Fsu.Prin&0xFF) != 0)
			{
				TimeOutOn = ((Fsu.Prin&0xFF)*2);
				Fsu.St=1;
			}
		}break;
		case 1:
		{			// Замкнули
			S13 = 0;
			S14 = 0;
			PR1= 1;
			PS1= 1;
			
			Fsu.St=2;
			Fsu.Timer = 0;
		}break;
		case 2:
		{
			if(Fsu.Timer>TimeOutSetData) // ждём коммутации
			{
				PR1= 1;
				PS1= 0;
				S13 = 1;
				S14 = 0;
				
				Fsu.St=3;
				Fsu.Timer = 0;
			}
		}break;
		case 3:
		{
			if(Fsu.Timer > TimeOutOn) // Таймаут
			{
				S13 = 1;	// размыкаем
				S14 = 1;
				
				PR1= 0;
				PS1= 0;
				Fsu.Timer = 0;
				Fsu.St=4;
			}
		}break;
		case 4:
		{
			if(Fsu.Timer>TimeOutSetData)
			{
				PR1= 1;
				PS1= 0;
				S13 = 1;
				S14 = 0;
				Fsu.St=5;
				Fsu.Timer = 0;
			}
		}break;
		case 5:
		{
			if(Fsu.Timer>TimeOut3s)
			{
				Fsu.St=0;
			}
		}break;
	}

}

//=============================================================================
void Driver_FSU14_C()
{
	BYTE i;
	//__DI();
//	DWORD	tmp;
	
	i=ADDR;	
	Fsu.Info.bits.Addr	=i;
	//if(i!=ADDR_NODE)
	//{
	//	setState(Initialisation);
	//	ADDR_NODE			=ADDR;
	//}
	Fsu.Info.bits.Mode=MODE;
	Fsu.Info.bits.F1=PG_F1;
	Fsu.Info.bits.F2=PG_F2;
	
	//**************************************************
	#ifdef FSU14_C

	//Update_Data_BD_DOUT_Test();
	Update_Data_BD_DOUT();

	#endif
	//**************************************************
	#ifdef FSU16_K
	
	if(Fsu.Prin!=Fsu.State)	//Устанавливаем новые команды
	{
		//__DI();
		Fsu.State=Fsu.Prin;
		tmp=Fsu.State;
		S_1=Convert_n((BYTE)(tmp));
		S_2=Convert_n((BYTE)(tmp>>8));
		S_3=Convert_n((BYTE)(tmp>>16));
		//__EI();
	}
	TestOutput();	
	#endif
	//**************************************************
}
//=============================================================================
void DOUT_OFF(BYTE Type)
{
	WORD State;
	
	if(Type==NE_CHET)
	{
		State=Fsu.State_NECHET;
	}else
		{
			State=Fsu.State_CHET;
		}
	//------------------------------------
	//	Размыкаем  нужные реле
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
	if(digit(State,6)==0)
	{
		S13=1;
		S14=1;
	}
	if(digit(State,7)==0)
	{
		S15=1;
		S16=1;
	}
	if(digit(State,8)==0)
	{
		S17=1;
		S18=1;
	}
	if(digit(State,9)==0)
	{
		S19=1;
		S20=1;
	}
	if(digit(State,10)==0)
	{
		S21=1;
		S22=1;
	}
	if(digit(State,11)==0)
	{
		S23=1;
		S24=1;
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
	//------------------
	//	Задержка 2.5 мс
	//------------------
	Fsu.Timer=0;
//	while(Fsu.Timer<4);
	//-----------------
	//Снимаем управляющее воздействие
//	Reset_Set(Type);
	//-----------------
}
void DOUT_ON(BYTE Type)
{
	WORD State;
	
	if(Type==NE_CHET)
	{
		State=Fsu.State_NECHET;
	}else
		{
			State=Fsu.State_CHET;
		}
	//------------------------------------
	//	Замыкаем нужные реле
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
	if(digit(State,6)==1)
	{
		S13=0;
		S14=0;
	}
	if(digit(State,7)==1)
	{
		S15=0;
		S16=0;
	}
	if(digit(State,8)==1)
	{
		S17=0;
		S18=0;
	}
	if(digit(State,9)==1)
	{
		S19=0;
		S20=0;
	}
	if(digit(State,10)==1)
	{
		S21=0;
		S22=0;
	}
	if(digit(State,11)==1)
	{
		S23=0;
		S24=0;
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
	//------------------
	//	Задержка 2.5 мс
	//------------------
	Fsu.Timer=0;
//	while(Fsu.Timer<4);
	//-----------------
	//Снимаем управляющее воздействие
//	Reset_Set(Type);
	//-----------------
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
	Fsu.Timer=0;
}

void Reset_S()
{
#ifdef FSU14_C	
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

	S13=1;
	S14=0;

	S15=1;
	S16=0;

	S17=1;
	S18=0;

	S19=1;
	S20=0;

	S21=1;
	S22=0;

	S23=1;
	S24=0;
#endif
#ifdef FSU16_K
	S_1=0;	
	S_2=0;
	S_3=0;
#endif
}

//--------------------------------------------------------------------

void TestOutput()
{
	DWORD t=0;
	
	STRB1=0;
	Sleep_1_5mk();
	Fsu.Test=K1_6;
	STRB1=1;
	
	STRB2=0;
	Sleep_1_5mk();
	t=K1_6;
	Fsu.Test|=(DWORD)(t<<6);
	STRB2=1;
	
	STRB3=0;
	Sleep_1_5mk();
	t=K1_6;
	Fsu.Test|=(DWORD)(t<<12);
	STRB3=1;
	
	STRB4=0;
	Sleep_1_5mk();
	t=K1_6;
	Fsu.Test|=(DWORD)(t<<18);
	STRB4=1;
	Fsu.Test=~Fsu.Test;	//Зенит 
	//Fsu.Test=Fsu.Test;	//Гвиана 
	
	
}

#endif