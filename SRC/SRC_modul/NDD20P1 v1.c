#include "mb90590.h"
#include "Ndd20P1.h"

#ifdef PLATA_NDD20P1

CNDD20P1 Ndd;

void	(*INIT_BLOK)(void)	= InitNDD20P1;
void	(*DRIVER_BLOK)(void)= Driver_NDD20P1;
WORD	(*STATE_BLOCK) 		= &Ndd.Info.word;

WORD	StartTimeOut=30000;
BYTE	Convert_n(BYTE n);

void InitNDD20P1()
{
	BYTE i;
	
	SET_DIN1_TEST0;
	SET_DIN2_TEST0;
	SET_DIN3_TEST0;
	SET_DIN4_TEST0;
	
	DDR0=0x00;
	DDR1=0x07;
	DDR2=0x00;
	DDR4=0x00;
	DDR5=0xFF;
	DDR6=0x0F;
	DDR7=0x00;
	DDR8=0xFF;
	DDR9=0x00;
	//------------------
	LEDR=1;
	LEDG=1;
	//------------------
	PWR_ON;
	//------------------
	for(i=0;i<2;i++)
	{
		Ndd.test[i]		=0;
		Ndd.tmp_test[i]	=0;
		Ndd.state[i]	=0;
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
void Driver_NDD20P1()
{
	BYTE i;
	i=ADDR;	
	Ndd.Info.bits.Addr	=i;
	if(i!=ADDR_NODE)
	{
		setState(Initialisation);
		ADDR_NODE			=ADDR;
	}
	__DI();
	Ndd.Info.bits.Mode		=MODE;
	
	if(Ndd.PowerNew !=	Ndd.PowerOld)
	{
		Ndd.PowerOld = Ndd.PowerNew;
		Ndd.St1			=1;
		Ndd.Timer1		=0;
		Ndd.Timer2		=0;
		Ndd.CurStep		=0;
		Ndd.CurBunk		=0;
	}
	UpdateDataNDD();
	__EI();
}
//======================================================================
void SetTest0CurBunk(void)
{
	if(Ndd.CurBunk == 0)
	{
		SET_DIN1_TEST0;
		SET_DIN2_READ;
		SET_DIN3_READ;
		SET_DIN4_READ;
		return;
	}
	if(Ndd.CurBunk == 1)
	{
		SET_DIN1_READ;
		SET_DIN2_TEST0;
		SET_DIN3_READ;
		SET_DIN4_READ;
		return;
	}
	if(Ndd.CurBunk == 2)
	{
		SET_DIN1_READ;
		SET_DIN2_READ;
		SET_DIN3_TEST0;
		SET_DIN4_READ;
		return;
	}
	if(Ndd.CurBunk == 3)
	{
		SET_DIN1_READ;
		SET_DIN2_READ;
		SET_DIN3_READ;
		SET_DIN4_TEST0;
		return;
	}
}
//--------------------------------------------
BYTE GetDataCurBunk(void)
{
	if(Ndd.CurBunk == 0)
	{
		return (Convert_n(IN1)&0x0F);
	}
	if(Ndd.CurBunk == 1)
	{
		return (Convert_n(IN1)&0xF0);
	}
	if(Ndd.CurBunk == 2)
	{
		return (Convert_n(IN2)&0x0F);
	}
	if(Ndd.CurBunk == 3)
	{
		return (Convert_n(IN2)&0xF0);
	}
}
//===============================================================================
void SetValidForCurBunk(BYTE Valid)
{
	BYTE n;
	 
	if(Ndd.CurBunk == 0)
	{
		n=Ndd.test[0]&0xF0;
		Valid&=0xF;
		Ndd.test[0]=n|Valid;
	}
	if(Ndd.CurBunk == 1)
	{
		n=Ndd.test[0]&0x0F;
		Valid&=0xF0;
		Ndd.test[0]=n|Valid;
	}
	if(Ndd.CurBunk == 2)
	{
		n=Ndd.test[1]&0xF0;
		Valid&=0xF;
		Ndd.test[1]=n|Valid;
	}
	if(Ndd.CurBunk == 3)
	{
		n=Ndd.test[1]&0x0F;
		Valid&=0xF0;
		Ndd.test[1]=n|Valid;
	}
}
// Анализируем данные по тестированию реле
void AnalizeTestData(void)
{
	BYTE i,n,err,ReadOR;
	
	ReadOR = Ndd.Read[0]|Ndd.Read[1];
	ReadOR |=Ndd.Read[2];
	ReadOR = ~ReadOR;	// 0 -исправно	
	
	err=0;
	if(ReadOR!=0)
	{ 
		if((Ndd.CurBunk==0)||(Ndd.CurBunk==2))
		{
			for(i=0;i<4;i++)
			{
				n=digit(Ndd.TestR[0],i);
				n+=digit(Ndd.TestR[1],i);
				n+=digit(Ndd.TestR[2],i);
				if(n<2)
					err|=1<<i;
			}
		}else
		{
			for(i=0;i<4;i++)
			{
				n=digit(Ndd.TestR[0],i+4);
				n+=digit(Ndd.TestR[1],i+4);
				n+=digit(Ndd.TestR[2],i+4);
				if(n<2)
					err|=1<<(i+4);
			}
		}
	}
	SetValidForCurBunk(ReadOR & err);
}
//===============================================================================
void UpdateDataNDD(void)
{
	BYTE tmp, in;
	if(Ndd.PowerOld == 1)
	{
		S_ON;
		switch (Ndd.St1)
		{
			case 1:		//читаем все
			{
				SET_DIN1_READ;
				SET_DIN2_READ;
				SET_DIN3_READ;
				SET_DIN4_READ;
				
				if(Ndd.Timer2>10) 
				{
					Ndd.state[0] = ~Convert_n(IN1);
					Ndd.state[1] = ~Convert_n(IN2);
					Ndd.Timer2 = 0;
					Ndd.Read[Ndd.CurStep]=~GetDataCurBunk();
					Ndd.St1=2;
				}
			}
			break;
			case 2:		//читаем тест 0
			{
				SetTest0CurBunk();
				if(Ndd.Timer2>10) 
				{
					Ndd.Timer2 = 0;
					Ndd.TestR[Ndd.CurStep]=GetDataCurBunk();
					Ndd.CurStep++;
					if(Ndd.CurStep>2)
					{
						Ndd.CurStep=0;
						AnalizeTestData();
						Ndd.CurBunk++;
						if(Ndd.CurBunk>3)
							Ndd.CurBunk=0;
					}
					Ndd.St1=1;
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
			case 1:
			{
				SET_DIN1_TEST0;
				SET_DIN2_READ;
				SET_DIN3_READ;
				SET_DIN4_READ;
				if(Ndd.Timer2>StartTimeOut) // test 0 for 1-4
				{
					StartTimeOut=10;
					in = Convert_n(IN1);
					tmp = Ndd.test[0] & 0xF0;
					tmp |= (in & 0xF);
					Ndd.tmp_test[0] = tmp;
					
					Ndd.Timer2 = 0;
					Ndd.St1 = 2;
				}		
			}
			break;
			case 2:
			{
				SET_DIN1_TEST1;
				SET_DIN2_READ;
				SET_DIN3_READ;
				SET_DIN4_READ;
				if(Ndd.Timer2>10) // test 1 for 1-4
				{
					in = Convert_n(IN1);
					
					tmp = Ndd.tmp_test[0] ;//& 0xF0;
					tmp |= ((~in) & 0xF);
					Ndd.test[0] = tmp;
					
					Ndd.Timer2 = 0;
					Ndd.St1 = 3;
				}
			}
			break;
			//-------------------------------------------------------
			case 3:
			{
				SET_DIN1_READ;
				SET_DIN2_TEST0;
				SET_DIN3_READ;
				SET_DIN4_READ;
				if(Ndd.Timer2>10) // test 0 for 5-8
				{
					in = Convert_n(IN1);
					tmp = Ndd.test[0] & 0x0F;
					tmp |= (in & 0xF0);
					Ndd.tmp_test[0] = tmp;
					
					Ndd.Timer2 = 0;
					Ndd.St1 = 4;
				}		
			}
			break;
			case 4:
			{
				SET_DIN1_READ;
				SET_DIN2_TEST1;
				SET_DIN3_READ;
				SET_DIN4_READ;
				if(Ndd.Timer2>10) // test 1 for 5-8
				{
					in = Convert_n(IN1);
					
					tmp = Ndd.tmp_test[0];// & 0x0F;
					tmp |= ((~in) & 0xF0);
					Ndd.test[0] = tmp;
					
					Ndd.Timer2 = 0;
					Ndd.St1 = 5;
				}
			}
			break;
			//--------------------------------------------------
			case 5:
			{
				SET_DIN1_READ;
				SET_DIN2_READ;
				SET_DIN3_TEST0;
				SET_DIN4_READ;
				if(Ndd.Timer2>10) // test 0 for 9-12
				{
				
					in = Convert_n(IN2);
					tmp = Ndd.test[1] & 0xF0;
					tmp |= (in & 0xF);
					Ndd.tmp_test[1] = tmp;
					
					Ndd.Timer2 = 0;
					Ndd.St1 = 6;
				}		
			}
			break;
			case 6:
			{
				SET_DIN1_READ;
				SET_DIN2_READ;
				SET_DIN3_TEST1;
				SET_DIN4_READ;
				if(Ndd.Timer2>10) // test 1 for 9-12
				{
				
					in = Convert_n(IN2);
					tmp = Ndd.tmp_test[1];// & 0xF0;
					tmp |= ((~in) & 0xF);
					Ndd.test[1] = tmp;
					
					Ndd.Timer2 = 0;
					Ndd.St1 = 7;
				}
			}
			break;
			//--------------------------------------------------
			case 7:
			{
				SET_DIN1_READ;
				SET_DIN2_READ;
				SET_DIN3_READ;
				SET_DIN4_TEST0;
				if(Ndd.Timer2>10) // test 0 for 13-16
				{
					
					in = Convert_n(IN2);
					tmp = Ndd.test[1] & 0x0F;
					tmp |= (in & 0xF0);
					Ndd.tmp_test[1] = tmp;
					
					Ndd.Timer2 = 0;
					Ndd.St1 = 8;
				}		
			}
			break;
			case 8:
			{
				SET_DIN1_READ;
				SET_DIN2_READ;
				SET_DIN3_READ;
				SET_DIN4_TEST1;
				if(Ndd.Timer2>10) // test 1 for 13-16
				{
					in = Convert_n(IN2);
					
					tmp = Ndd.tmp_test[1];// & 0x0F;
					tmp |= ((~in) & 0xF0);
					Ndd.test[1] = tmp;
					
					Ndd.Timer2 = 0;
					Ndd.St1 = 9;
				}
			}
			case 9:
			{
				SET_DIN1_READ;
				SET_DIN2_READ;
				SET_DIN3_READ;
				SET_DIN4_READ;
				if(Ndd.Timer2>60000) 
				{
					Ndd.Timer2 = 0;
					Ndd.St1 = 1;
				}
			}
			break;
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
