#include "mb90590.h"
#include "Ndd20P1.h"

#ifdef PLATA_NDD20P1

CNDD20P1 Ndd;

void	(*INIT_BLOK)(void)	= InitNDD20P1;
void	(*DRIVER_BLOK)(void)= Driver_NDD20P1;
WORD	(*STATE_BLOCK) 		= &Ndd.Info.word;

WORD	StartTimeOut=5000;//30000;
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
	for(i=0;i<4;i++)
	{
		Ndd.St1[i]			=1;
		Ndd.Timer2[i]		=0;
		Ndd.CurStep[i]		=0;
		Ndd.Test0_Req[i]	=0;
		Ndd.Test0_Run[i]	=0;
		Ndd.Test_Bunk[i]	=0;
	}
	Ndd.Test0_Last	=0;
	Ndd.Info.word	=0;
	Ndd.PowerNew	=0;
	Ndd.PowerOld	=1;
	ADDR_NODE		=ADDR;
	Ndd.Info.bits.Addr=ADDR;
}
//===================================================================
void SetOn(BYTE n)
{
	switch(n)
	{
		case 0: S1_4_ON;
				break;
		case 1: S5_8_ON;
				break;
		case 2: S9_12_ON;
				break;
		case 3: S13_16_ON;
				break;
	}
}
void SetOff(BYTE n)
{
	switch(n)
	{
		case 0: S1_4_OFF;
				break;
		case 1: S5_8_OFF;
				break;
		case 2: S9_12_OFF;
				break;
		case 3: S13_16_OFF;
				break;
	}
}
//===================================================================


void SetRegim(BYTE n, BYTE Regim)
{
	if(n>3) return;
	if(Regim>REGIM_MAX) return;
	
	if(Regim == REGIM_WORK)
	{
		switch(n)
		{
			case 0:SET_DIN1_READ; break;
			case 1:SET_DIN2_READ; break;
			case 2:SET_DIN3_READ; break;
			case 3:SET_DIN4_READ; break;
		}
		return;
	}
	if(Regim == REGIM_TEST_1)
	{
		switch(n)
		{
			case 0:SET_DIN1_TEST1; break;
			case 1:SET_DIN2_TEST1; break;
			case 2:SET_DIN3_TEST1; break;
			case 3:SET_DIN4_TEST1; break;
		}
		return;
	}
	if(Regim == REGIM_TEST_0)
	{
		switch(n)
		{
			case 0:SET_DIN1_TEST0; break;
			case 1:SET_DIN2_TEST0; break;
			case 2:SET_DIN3_TEST0; break;
			case 3:SET_DIN4_TEST0; break;
		}
		return;
	}
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
		for(i=0;i<4;i++)
		{
			if(digit(Ndd.PowerOld,i) != digit(Ndd.PowerNew,i))
			{
				Ndd.St1[i]		=1;
				Ndd.Timer2[i]	=0;
				Ndd.CurStep[i]	=0;
			}
		}
		Ndd.PowerOld = Ndd.PowerNew;
	}
	//=========================================
	for(i=0;i<4;i++)
		UpdateDataSector(i);
	//=========================================
	__EI();
}
//======================================================================
BYTE GetDataBunk(BYTE n)
{
	switch(n)
	{
		case 0: return (Convert_n(IN1)&0x0F);
		case 1: return (Convert_n(IN1)&0xF0);
		case 2: return (Convert_n(IN2)&0x0F);	
		case 3: return (Convert_n(IN2)&0xF0);
	}
}
void GetDataInput(BYTE n)
{
	BYTE tmp;
	switch(n)
	{
		case 0: 
			{
				tmp = Ndd.state[0]&0xF0;
				tmp |= 0xF & (~Convert_n(IN1));
				Ndd.state[0] = tmp;
			}break;
		case 1: 
			{
				tmp = Ndd.state[0]&0x0F;
				tmp |= 0xF0 & (~Convert_n(IN1));
				Ndd.state[0] = tmp;
			}break;
		case 2: 
			{
				tmp = Ndd.state[1]&0xF0;
				tmp |= 0xF & (~Convert_n(IN2));
				Ndd.state[1] = tmp;
			}break;
		case 3: 
			{
				tmp = Ndd.state[1]&0x0F;
				tmp |= 0xF0 & (~Convert_n(IN2));
				Ndd.state[1] = tmp;
			}break;
	}
}
//===============================================================================
void SetValidForCurBunk(BYTE n, BYTE Valid)
{
	BYTE d;
	
	switch(n)
	{ 
		case 0:
		{
			d=Ndd.test[0]&0xF0;
			Valid&=0xF;
			Ndd.test[0]=d|Valid;
		}break;
		case 1:
		{
			d=Ndd.test[0]&0x0F;
			Valid&=0xF0;
			Ndd.test[0]=d|Valid;
		}break;
		case 2:
		{
			d=Ndd.test[1]&0xF0;
			Valid&=0xF;
			Ndd.test[1]=d|Valid;
		}break;
		case 3:
		{
			d=Ndd.test[1]&0x0F;
			Valid&=0xF0;
			Ndd.test[1]=d|Valid;
		}break;
	}
}
// Анализируем данные по тестированию реле
void AnalizeTestData(BYTE n)
{
	BYTE i,j,err,ReadOR, ofs;
	
	if(n>3) return;
	
	ReadOR = Ndd.Read[n][0]|Ndd.Read[n][1];
	ReadOR |=Ndd.Read[n][2];
	ReadOR = ~ReadOR;	// 0 -исправно	
	
	err=0;
	if(ReadOR!=0)	// тест на ноль возможен только по тем входам где цепь разомкнута
	{ 
		if((n==1)||(n==3)) ofs = 4;
		else ofs = 0;
			
		for(i=0;i<4;i++)
		{
			j =	digit(Ndd.TestR[n][0],i+ofs);
			j +=digit(Ndd.TestR[n][1],i+ofs);
			j +=digit(Ndd.TestR[n][2],i+ofs);
			if(j<2)
				err|=1<<(i+ofs);
		}
	}
	SetValidForCurBunk(n,ReadOR & err);
}
//===============================================================================
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
BYTE	ReqwestTest0(BYTE n)	// запрашиваем проведение теста 0, 1 = разрешен
{
	BYTE i, j;
	
	if(Ndd.Test0_Last>3) 
		Ndd.Test0_Last = 0;
	if (n>3)
		return 0;
	
	Ndd.Test0_Run[n]	=0;	// нами тест точно не проводится
	Ndd.Test0_Req[n]	=1; //выставляем запрос что мы хотим провести тест
	j	= 0;
	for(i=0;i<4;i++)
	{
		j += Ndd.Test0_Run[i];
	}
	
	if(j > 0) // тест уже кем то запущен
		return 0;

	// тест ни кем не выполняется узнаем кто последний выполнил тест				
	j=Ndd.Test0_Last+1;	
	for(i=0;i<4;i++)
	{
		if(j>3) j=0;
		if(Ndd.Test0_Req[j]	== 1)	// следующий может провести тест
		{
			if(j == n)	
				break; 	//мы являемся следующими
			else
				return 0;	// мы являемся следующим кто может провести тест
		}
		j++;
	}
	
	Ndd.Test0_Run[n]	=1;
	Ndd.Test0_Req[n]	=0;
	
	return 1;
}
const MASK_FF[4]	= {0xF0,0x0F,0xF0,0x0F};
const MASK_FF_INV[4]= {0x0F,0xF0,0x0F,0xF0};
void UpdateDataSector(BYTE n)
{
	BYTE in;
	
	if(n>3) return;
	
	if(digit(Ndd.PowerOld,n) == 1)	// рабочий режим
	{
		SetOn(n);
		switch (Ndd.St1[n])
		{
			case 1:		//читаем все
			{
				SetRegim(n, REGIM_WORK);
				
				if(Ndd.Timer2[n]>10) 
				{
					GetDataInput(n);
					Ndd.Timer2[n] = 0;
					Ndd.Read[n][Ndd.CurStep[n]]=~GetDataBunk(n);
					Ndd.St1[n]=2;
				}
			}
			break;
			case 2:		// провереям можно ли в данный момент провести тест 0
			{
				if(ReqwestTest0(n) == 1)
				{
					Ndd.St1[n]=3;
					Ndd.Timer2[n] = 0;
				}
			}break;
			case 3:		//читаем тест 0
			{
				Ndd.Test0_Last = n;	// мы в последними выполнили тест 0
				SetRegim(n, REGIM_TEST_0);
				if(Ndd.Timer2[n]>10) 
				{
					Ndd.Timer2[n] = 0;
					Ndd.TestR[n][Ndd.CurStep[n]]=GetDataBunk(n);
					Ndd.CurStep[n]++;
					if(Ndd.CurStep[n]>2)
					{
						Ndd.CurStep[n]=0;
						AnalizeTestData(n);
					}
					Ndd.St1[n]=1;
					SetRegim(n, REGIM_WORK);
					Ndd.Test0_Run[n]	=0;
				}
			}
			break;
			default:
				Ndd.St1[n] = 1;
		}
	}else	// тестовый режим
	{
		SetOff(n);
		switch (Ndd.St1[n])
		{
			case 1:	// ждем когда можно будет провести тест 0
			{
				if(Ndd.Timer2[n]>StartTimeOut)
				{
					StartTimeOut = 10;
					Ndd.Timer2[n] = 11;
				}else break;
				
				if(ReqwestTest0(n) == 1)
				{
					Ndd.St1[n]=2;
					Ndd.Timer2[n] = 0;
				}
			}break;
			case 2:	// тест 0
			{
				SetRegim(n, REGIM_TEST_0);	// test 0 
				if(Ndd.Timer2[n]>StartTimeOut) 
				{
					StartTimeOut=10;
					//============================
					//in = GetDataBunk(n);
					
					//if(n<2) tmp = Ndd.test[0] & MASK_FF[n];
					//else	tmp = Ndd.test[1] & MASK_FF[n];
					
					Ndd.Test_Bunk[n] = GetDataBunk(n);
					
					//if(n<2)	Ndd.tmp_test[0] = tmp;
					//else	Ndd.tmp_test[1] = tmp;
					//============================
					Ndd.Timer2[n] = 0;
					Ndd.St1[n] = 3;
					SetRegim(n, REGIM_TEST_1);	// test 1 
					Ndd.Test0_Run[n]	=0;
				}		
			}
			break;
			case 3:
			{
				SetRegim(n, REGIM_TEST_1); // test 1 
				if(Ndd.Timer2[n]>10) 
				{
					//==============================
					in = GetDataBunk(n);
					
					//if(n<2)	tmp = Ndd.tmp_test[0] & MASK_FF[n];
					//else	tmp = Ndd.tmp_test[1] & MASK_FF[n];
					//if(n<2)	tmp = Ndd.tmp_test[0];
					//else	tmp = Ndd.tmp_test[1];
					
					Ndd.Test_Bunk[n] |=  ((~in) & MASK_FF_INV[n]);
					
					if(n<2)	Ndd.test[0] = (Ndd.test[0]&MASK_FF[n]) | Ndd.Test_Bunk[n];
					else	Ndd.test[1] = (Ndd.test[1]&MASK_FF[n]) | Ndd.Test_Bunk[n];
					//==============================
					Ndd.Timer2[n] 	= 0;
					Ndd.St1[n] 		= 4;
				}
			}
			break;
			//-------------------------------------------------------
			case 4:
			{
				SetRegim(n, REGIM_WORK);
				if(Ndd.Timer2[n]>5000/*60000*/) 
				{
					Ndd.Timer2[n] = 0;
					Ndd.St1[n] = 1;
				}
			}
			break;
			default:
				Ndd.St1[n] = 1;
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
/*
void~UpdateDataNDD(void)
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
*/
#endif
