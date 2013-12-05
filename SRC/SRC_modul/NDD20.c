#include "mb90590.h"
#include "Ndd20.h"

#ifdef PLATA_NDD20

CNDD20 Ndd;


void 	(*INIT_BLOK)(void)	= InitNDD20;
void 	(*DRIVER_BLOK)(void)= Driver_NDD20;
WORD 	(*STATE_BLOCK) 		= &Ndd.Info.word;

WORD	StartTimeOut=60000;

BYTE Convert_n(BYTE n);
void UpdateDataNDD(void);

void InitNDD20()
{
	BYTE i;
	
	SET_DIN1_TEST0;
	SET_DIN2_TEST0;
	
	DDR0=0x00;
	DDR1=0x03;
	DDR2=0x00;
	DDR4=0x0F;
	DDR5=0xFF;
	DDR6=0x0F;
	DDR7=0x00;
	DDR8=0xFF;
	DDR9=0x00;
	//------------------
	LEDR=1;
	LEDG=1;
	//------------------
	DESELECT_STRB;
	//------------------
	for(i=0;i<2;i++)
	{
		Ndd.state[i]	=0;
		Ndd.tmp_state[i]=0;
		Ndd.valid[i]	=0;
		Ndd.tmp_valid[i]=0;
		Ndd.test[i]		=0;
		Ndd.tmp_test[i]	=0;
	}
	Ndd.Info.word	=0;
	Ndd.St1			=1;
	Ndd.PowerNew	=0;
	Ndd.PowerOld	=1;
	Ndd.Timer1		=0;
	Ndd.Timer2		=0;
	Ndd.CurStep		=0;
	Ndd.CurBunk		=0;
	ADDR_NODE		=ADDR;
	Ndd.Info.bits.Addr=ADDR;
}
//===================================================================
void Driver_NDD20()
{
	BYTE i;
	i=ADDR;	
	Ndd.Info.bits.Addr	=i;
	if(i!=ADDR_NODE)
	{
		setState(Initialisation);
		ADDR_NODE			=ADDR;
	}
//	__DI();
	Ndd.Info.bits.Mode		=MODE;
	Ndd.Info.bits.F1		=PG_F1;
	Ndd.Info.bits.F2		=PG_F2;
	
//	TST1 = Ndd.T_1;
//	TST2 = Ndd.T_2;
//	TST3 = Ndd.T_3;
//	TST4 = Ndd.T_4;
	
	if(Ndd.PowerNew !=	Ndd.PowerOld)
	{
		Ndd.PowerOld = Ndd.PowerNew;
		Ndd.St1			=1;
		Ndd.Timer1		=0;
		Ndd.Timer2		=0;
		Ndd.CurStep		=0;
		Ndd.CurBunk		=0;
		Ndd.tmp_state[i]=0;
		Ndd.tmp_valid[i]=0;
		Ndd.tmp_test[i]	=0;
	}
	UpdateDataNDD();
//	__EI();
}
//===============================================================================
void UpdateDataNDD(void)
{
	BYTE i;
	TIN	in;
	if(Ndd.PowerOld == 1)
	{
		S_ON;
		switch (Ndd.St1)
		{
			case 1:		//читаем по STRB1
			{
				SELECT_STRB1;
				if(Ndd.Timer1>5)
				{
					in.byte = Convert_n(IN1);
					for(i=0;i>2; i++)
					{
						Ndd.tmp_state[i]=0;
						Ndd.tmp_valid[i]=0;
					}
					//-----------------------------------------------
					if(in.bits.I12<2)	Ndd.tmp_valid[0] |=0x01;
					else
						if(in.bits.I12==2)	Ndd.tmp_state[0] |=0x01; 
					//-----------------------------------------------
					if(in.bits.I34<2)	Ndd.tmp_valid[0] |=0x02;
					else
						if(in.bits.I34==2)	Ndd.tmp_state[0] |=0x02; 
					//-----------------------------------------------
					if(in.bits.I56<2)	Ndd.tmp_valid[0] |=0x04;
					else
						if(in.bits.I56==2)	Ndd.tmp_state[0] |=0x04; 
					//-----------------------------------------------
					if(in.bits.I78<2)	Ndd.tmp_valid[0] |=0x08;
					else
						if(in.bits.I78==2)	Ndd.tmp_state[0] |=0x08; 
					//-----------------------------------------------
					Ndd.Timer1=0;
					Ndd.St1 = 2;
				}
			}
			break;
			case 2:		//читаем по STRB2
			{
				SELECT_STRB2;
				if(Ndd.Timer1>5)
				{
					in.byte = Convert_n(IN1);
					//-----------------------------------------------
					if(in.bits.I12<2)	Ndd.tmp_valid[0] |=0x10;
					else
						if(in.bits.I12==2)	Ndd.tmp_state[0] |=0x10; 
					//-----------------------------------------------
					if(in.bits.I34<2)	Ndd.tmp_valid[0] |=0x20;
					else
						if(in.bits.I34==2)	Ndd.tmp_state[0] |=0x20; 
					//-----------------------------------------------
					if(in.bits.I56<2)	Ndd.tmp_valid[0] |=0x40;
					else
						if(in.bits.I56==2)	Ndd.tmp_state[0] |=0x40; 
					//-----------------------------------------------
					if(in.bits.I78<2)	Ndd.tmp_valid[0] |=0x80;
					else
						if(in.bits.I78==2)	Ndd.tmp_state[0] |=0x80; 
					//-----------------------------------------------
					
					Ndd.Timer1=0;
					Ndd.St1 = 3;
				}
			}
			break;
			case 3:		//читаем по STRB3
			{
				SELECT_STRB3;
				if(Ndd.Timer1>5)
				{
					in.byte = Convert_n(IN1);
					//-----------------------------------------------
					if(in.bits.I12<2)	Ndd.tmp_valid[1] |=0x01;
					else
						if(in.bits.I12==2)	Ndd.tmp_state[1] |=0x01; 
					//-----------------------------------------------
					if(in.bits.I34<2)	Ndd.tmp_valid[1] |=0x02;
					else
						if(in.bits.I34==2)	Ndd.tmp_state[1] |=0x02; 
					//-----------------------------------------------
					if(in.bits.I56<2)	Ndd.tmp_valid[1] |=0x04;
					else
						if(in.bits.I56==2)	Ndd.tmp_state[1] |=0x04; 
					//-----------------------------------------------
					if(in.bits.I78<2)	Ndd.tmp_valid[1] |=0x08;
					else
						if(in.bits.I78==2)	Ndd.tmp_state[1] |=0x08; 
					//-----------------------------------------------
					
					Ndd.Timer1=0;
					Ndd.St1 = 4;
				}
			}
			break;
			case 4:		//читаем по STRB4
			{
				SELECT_STRB4;
				if(Ndd.Timer1>5)
				{
					in.byte = Convert_n(IN1);
					//-----------------------------------------------
					if(in.bits.I12<2)	Ndd.tmp_valid[1] |=0x10;
					else
						if(in.bits.I12==2)	Ndd.tmp_state[1] |=0x10; 
					//-----------------------------------------------
					if(in.bits.I34<2)	Ndd.tmp_valid[1] |=0x20;
					else
						if(in.bits.I34==2)	Ndd.tmp_state[1] |=0x20; 
					//-----------------------------------------------
					if(in.bits.I56<2)	Ndd.tmp_valid[1] |=0x40;
					else
						if(in.bits.I56==2)	Ndd.tmp_state[1] |=0x40; 
					//-----------------------------------------------
					if(in.bits.I78<2)	Ndd.tmp_valid[1] |=0x80;
					else
						if(in.bits.I78==2)	Ndd.tmp_state[1] |=0x80; 
					//-----------------------------------------------
					for(i=0;i>2; i++)
					{
						Ndd.state[i]=Ndd.tmp_state[i];
						Ndd.valid[i]=Ndd.tmp_valid[i];
					}
					Ndd.Timer1=0;
					Ndd.St1 = 1;
				}
			}
			break;
			default:
				Ndd.St1 = 1;
		}
	}else
	{
		S_OFF;
		switch (Ndd.St1)
		{
			//====================================================================
			// “естируем на обрыв=================================================
			//====================================================================
			case 1:
			{
				SET_DIN1_TEST0;
				//SET_DIN1_TEST0;
				SELECT_STRB1;
				if(Ndd.Timer1>5)
				{
					in.byte = Convert_n(IN1);
					Ndd.IN_1 = in.byte;
					
					Ndd.tmp_test[0]=0;
					Ndd.tmp_test[1]=0;
				
					//-----------------------------------------------
					if(in.bits.I12!=1)	Ndd.tmp_test[0] |=0x01;
					if(in.bits.I34!=1)	Ndd.tmp_test[0] |=0x02;
					if(in.bits.I56!=1)	Ndd.tmp_test[0] |=0x04;
					if(in.bits.I78!=1)	Ndd.tmp_test[0] |=0x08;
					//-----------------------------------------------
					
					Ndd.Timer1=0;
					Ndd.St1 = 2;
				}
			}
			break;
			case 2:
			{
				SELECT_STRB2;
				if(Ndd.Timer1>5)
				{
					in.byte = Convert_n(IN1);
					Ndd.IN_2 = in.byte;
					//-----------------------------------------------
					if(in.bits.I12!=1)	Ndd.tmp_test[0] |=0x10;
					if(in.bits.I34!=1)	Ndd.tmp_test[0] |=0x20;
					if(in.bits.I56!=1)	Ndd.tmp_test[0] |=0x40;
					if(in.bits.I78!=1)	Ndd.tmp_test[0] |=0x80;
					//-----------------------------------------------
					
					Ndd.Timer1=0;
					Ndd.St1 = 3;
				}
			}
			break;
			//-------------------------------------------------------
			case 3:
			{
				SET_DIN2_TEST0;
				//SET_DIN2_TEST0;
				SELECT_STRB3;
				if(Ndd.Timer1>5)
				{
					in.byte = Convert_n(IN1);
					Ndd.IN_3 = in.byte;
					//-----------------------------------------------
					if(in.bits.I12!=1)	Ndd.tmp_test[1] |=0x01;
					if(in.bits.I34!=1)	Ndd.tmp_test[1] |=0x02;
					if(in.bits.I56!=1)	Ndd.tmp_test[1] |=0x04;
					if(in.bits.I78!=1)	Ndd.tmp_test[1] |=0x08;
					//-----------------------------------------------
					
					Ndd.Timer1=0;
					Ndd.St1 = 4;
				}
			}
			break;
			case 4:
			{
				SELECT_STRB4;
				if(Ndd.Timer1>5)
				{
					in.byte = Convert_n(IN1);
					Ndd.IN_4 = in.byte;
					//-----------------------------------------------
					if(in.bits.I12!=1)	Ndd.tmp_test[1] |=0x10;
					if(in.bits.I34!=1)	Ndd.tmp_test[1] |=0x20;
					if(in.bits.I56!=1)	Ndd.tmp_test[1] |=0x40;
					if(in.bits.I78!=1)	Ndd.tmp_test[1] |=0x80;
					//-----------------------------------------------
					
					Ndd.Timer1=0;
					Ndd.St1 = 5;
					//Ndd.St1 = 13;
				}
			}
			break;
			//*************************************************************************
			//--------------------------------------------------
			// имитаци€ датчика 10 кќм
			//--------------------------------------------------
			case 5:
			{
				SET_DIN1_TEST_10kOm;
				SELECT_STRB1;
				if(Ndd.Timer1>5)
				{
					in.byte = Convert_n(IN1);
					
					//-----------------------------------------------
					if(in.bits.I12!=3)	Ndd.tmp_test[0] |=0x01;
					if(in.bits.I34!=3)	Ndd.tmp_test[0] |=0x02;
					if(in.bits.I56!=3)	Ndd.tmp_test[0] |=0x04;
					if(in.bits.I78!=3)	Ndd.tmp_test[0] |=0x08;
					//-----------------------------------------------
					
					Ndd.Timer1=0;
					Ndd.St1 = 6;
				}
			}
			break;
			case 6:
			{
				SELECT_STRB2;
				if(Ndd.Timer1>5)
				{
					in.byte = Convert_n(IN1);
					
					//-----------------------------------------------
					if(in.bits.I12!=3)	Ndd.tmp_test[0] |=0x10;
					if(in.bits.I34!=3)	Ndd.tmp_test[0] |=0x20;
					if(in.bits.I56!=3)	Ndd.tmp_test[0] |=0x40;
					if(in.bits.I78!=3)	Ndd.tmp_test[0] |=0x80;
					//-----------------------------------------------
					
					Ndd.Timer1=0;
					Ndd.St1 = 7;
				}
			}
			break;
			//--------------------------------------------------
			case 7:
			{
				SET_DIN2_TEST_10kOm;
				SELECT_STRB3;
				if(Ndd.Timer1>5)
				{
					in.byte = Convert_n(IN1);
					
					//-----------------------------------------------
					if(in.bits.I12!=3)	Ndd.tmp_test[1] |=0x01;
					if(in.bits.I34!=3)	Ndd.tmp_test[1] |=0x02;
					if(in.bits.I56!=3)	Ndd.tmp_test[1] |=0x04;
					if(in.bits.I78!=3)	Ndd.tmp_test[1] |=0x08;
					//-----------------------------------------------
					
					Ndd.Timer1=0;
					Ndd.St1 = 8;
				}
			}
			break;
			case 8:
			{
				SELECT_STRB4;
				if(Ndd.Timer1>5)
				{
					in.byte = Convert_n(IN1);
					
					//-----------------------------------------------
					if(in.bits.I12!=3)	Ndd.tmp_test[1] |=0x10;
					if(in.bits.I34!=3)	Ndd.tmp_test[1] |=0x20;
					if(in.bits.I56!=3)	Ndd.tmp_test[1] |=0x40;
					if(in.bits.I78!=3)	Ndd.tmp_test[1] |=0x80;
					//-----------------------------------------------
					
					Ndd.Timer1=0;
					Ndd.St1 = 9;
				}
			}
			//********************************************************************
			// »митаци€ замкнутого состо€ни€
			case 9:
			{
				SET_DIN1_TEST1;
				SELECT_STRB1;
				if(Ndd.Timer1>5)
				{
					in.byte = Convert_n(IN1);
					
					//-----------------------------------------------
					if(in.bits.I12!=2)	Ndd.tmp_test[0] |=0x01;
					if(in.bits.I34!=2)	Ndd.tmp_test[0] |=0x02;
					if(in.bits.I56!=2)	Ndd.tmp_test[0] |=0x04;
					if(in.bits.I78!=2)	Ndd.tmp_test[0] |=0x08;
					//-----------------------------------------------
					
					Ndd.Timer1=0;
					Ndd.St1 = 10;
				}
			}
			break;
			case 10:
			{
				SELECT_STRB2;
				if(Ndd.Timer1>5)
				{
					in.byte = Convert_n(IN1);
					
					//-----------------------------------------------
					if(in.bits.I12!=2)	Ndd.tmp_test[0] |=0x10;
					if(in.bits.I34!=2)	Ndd.tmp_test[0] |=0x20;
					if(in.bits.I56!=2)	Ndd.tmp_test[0] |=0x40;
					if(in.bits.I78!=2)	Ndd.tmp_test[0] |=0x80;
					//-----------------------------------------------
					Ndd.Timer1=0;
					Ndd.St1 = 11;
				}
			}
			break;
			case 11:
			{
				SET_DIN2_TEST1;
				SELECT_STRB3;
				if(Ndd.Timer1>5)
				{
					in.byte = Convert_n(IN1);
					
					//-----------------------------------------------
					if(in.bits.I12!=2)	Ndd.tmp_test[1] |=0x01;
					if(in.bits.I34!=2)	Ndd.tmp_test[1] |=0x02;
					if(in.bits.I56!=2)	Ndd.tmp_test[1] |=0x04;
					if(in.bits.I78!=2)	Ndd.tmp_test[1] |=0x08;
					//-----------------------------------------------
					Ndd.Timer1=0;
					Ndd.St1 = 12;
				}
			}
			break;
			case 12:
			{
				SELECT_STRB4;
				if(Ndd.Timer1>5)
				{
					in.byte = Convert_n(IN1);
					
					//-----------------------------------------------
					if(in.bits.I12!=2)	Ndd.tmp_test[1] |=0x10;
					if(in.bits.I34!=2)	Ndd.tmp_test[1] |=0x20;
					if(in.bits.I56!=2)	Ndd.tmp_test[1] |=0x40;
					if(in.bits.I78!=2)	Ndd.tmp_test[1] |=0x80;
					//-----------------------------------------------
					Ndd.test[0]=Ndd.tmp_test[0];
					Ndd.test[1]=Ndd.tmp_test[1];
				
					Ndd.Timer1=0;
					Ndd.St1 = 13;
				}
			}
			case 13:
			{
				if(Ndd.Timer2>StartTimeOut)
				{
					Ndd.Timer2=0;
					Ndd.St1 = 1;
				}
			}
			break;
			//****************************************************************
			default:
				Ndd.St1 = 1;
		}
	}
}
//======================================================================
BYTE Convert_n(BYTE n)
{
	BYTE i,s=0;
	for(i=0;i<8;i++)
	{
		s|=digit(n,i)<<(7-i);
	}
	return s;
}
//======================================================================
#endif