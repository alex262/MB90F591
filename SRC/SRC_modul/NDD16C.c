#include "mb90590.h"
#include "Ndd16c.h"

#ifdef PLATA_NDD

#include "filter.h"
#include "timer.h"

const char SoftwareVer[20] = { __TIME__" " __DATE__}; 
 

CNDD16_C Ndd;


void	(*INIT_BLOK)(void)=InitNDD16C;
void	(*DRIVER_BLOK)(void)=Driver_NDD16_C;
WORD	(*STATE_BLOCK) 		= &Ndd.Info.word;

WORD	TIME_CONTROL_TEST=10000/TIMER_RESOLUTION_MS;
WORD	TIME_NAKOPL = 40/TIMER_RESOLUTION_MS;

TYPE_DATA_TIMER TimerStart=1000;
//WORD	COUNTER_DIN[2][32];
//-------------------------------------------------------------------------
BYTE	ModePr;
void InitNDD16C()
{
	BYTE i, j;

	DDR0=0x00;
	DDR1=0x73;
	DDR2=0x00;
	DDR4=0x00;
	DDR5=0x00;
	DDR6=0x6F;
	DDR7=0x00;
	DDR8=0x00;
	DDR9=0x00;
	//------------------
	LEDR=1;
	LEDG=1;
	//------------------
	//Отключение питания
	PWR1=1;
	PWR2=1;
	//------------------
	//Отключение тестирования
	TST1=0;
	TST2=0;
	//------------------
	//Отключаем Входы
	G1=0;
	G2=0;
	//------------------
//	n = ADDR;
//	n = (n & 0xF)|((n<<4)&0xF0);
	for(i=0;i<4;i++)
	{
		Ndd.test[i]=0;
		Ndd.state[i]=0;
		Ndd.pr_data[i]=0;
	}
	Ndd.test_0 = 0;
	Ndd.test_1 = 0;
	Ndd.Info.word=0;
	Ndd.St1=1;
	Ndd.St2=3;
	ADDR_NODE		  =ADDR;
	Ndd.Info.bits.Addr=ADDR;
	Ndd.Start=0;
	Ndd.Timer=0;

	//Ndd.TimerNdd=TIME_NAKOPL;
	//add_timer(&Ndd.TimerNdd);
	/*for(i=0;i<2;i++)
		for(j=0;j<32;j++)
			COUNTER_DIN[i][j]=0;*/

	//add_timer(&TimerStart);
	ModePr = MODE;
}
//===================================================================
BYTE	StDin[4];
DWORD	dwData;
void Driver_NDD16_C()
{
	BYTE i;
	WORD w;
	Ndd.Info.bits.Addr	=i;
	//if(getTime(&TimerStart)>0)
	{
		i=ADDR;	
		if(i!=ADDR_NODE)
		{
			setState(Initialisation);
			ADDR_NODE			=ADDR;
		}
	}
	/*else
	{
		del_timer(&TimerStart);
		i=ADDR;	
		if(i!=ADDR_NODE)
		{
			setODentry(0x100B, 0, &i, 1, 0);
		}
	
	}*/
	Ndd.Info.bits.Mode		=MODE;
//===================================================================
#ifdef	NDD17_K
	Ndd.Info.bits.PWRDin=~PWR;
	//==================================
	if(Ndd.Start == 0)
	{
		Ndd.Timer=0;
		Ndd.Start=1;
	}
	if(Ndd.Start == 1)
	{
		i=ADDR;
		//puts("A=");putD(i);puts("\n\r");
		if((i<17)||(i==25)||(i>29))
		{
			Ndd.Start=2;
			Ndd.Timer=0;
			return;
		}
		if((i==17)||(i==26))
		{
			if(Ndd.Timer>5)
			{
				Ndd.Start=2;
				Ndd.Timer=0;
				return;
			}
		}
		if((i==18)||(i==27))
		{
			if(Ndd.Timer>11)
			{
				Ndd.Start=2;
				Ndd.Timer=0;
				return;
			}
		}
		if((i==19)||(i==28))
		{
			if(Ndd.Timer>17)
			{
				Ndd.Start=2;
				Ndd.Timer=0;
				return;
			}
		}
		if((i==20)||(i==29))
		{
			if(Ndd.Timer>23)
			{
				Ndd.Start=2;
				Ndd.Timer=0;
				return;
			}
		}
	}
	//==================================
	if(PWR == 0 )
	{
		switch (Ndd.St1)
		{
			case 1:	//Test1 1 gruppy
			{
				if(Ndd.Timer >25)
				{
					Ndd.tmp_test[0]=~IN1;
					Ndd.tmp_test[1]=~IN2;
					TST1=0;
					PWR1=0;
					Ndd.St1=2;
					Ndd.Timer=0;
				}
			}break;	
			
			case 2:	//Test0 1 gruppy
			{
				if(Ndd.Timer >0)
				{
					Ndd.tmp_test[0]|=IN1;
					Ndd.tmp_test[1]|=IN2;
					TST1=0;
					PWR1=1;
					Ndd.St1=3;
					Ndd.Timer=0;
				}
			}break;	
			case 3:	//WORK 1 gruppy
			{
				if(Ndd.Timer >0)
				{
					Ndd.state[0]=Convert_n(IN1);
					Ndd.state[1]=Convert_n(IN2);
					TST1=1;
					PWR1=1;
					TST2=1;
					PWR2=1;
					Ndd.St1=4;
					Ndd.Timer=0;
				}
			}break;	
			
			
			case 4:	//Test1 2 gruppy
			{
				if(Ndd.Timer >0)
				{
					Ndd.tmp_test[2]=~IN3;
					Ndd.tmp_test[3]=~IN4;
					TST2=0;
					PWR2=0;
					Ndd.St1=5;
					Ndd.Timer=0;
				}
			}break;	
			
			case 5:	//Test0 2 gruppy
			{
				if(Ndd.Timer >0)
				{
					Ndd.tmp_test[2]|=IN3;
					Ndd.tmp_test[3]|=IN4;
					Ndd.test[0] = Ndd.tmp_test[0];
					Ndd.test[1] = Ndd.tmp_test[1];
					Ndd.test[2] = Ndd.tmp_test[2];
					Ndd.test[3] = Ndd.tmp_test[3];
					TST2=0;
					PWR2=1;
					Ndd.St1=6;
					Ndd.Timer=0;
				}
			}break;	
			case 6:	//WORK 1 gruppy
			{
				if(Ndd.Timer >0)
				{
					Ndd.state[2]=Convert_n(IN3);
					Ndd.state[3]=Convert_n(IN4);
					TST1=1;
					PWR1=1;
					TST2=1;
					PWR2=1;
					Ndd.St1=1;
					Ndd.Timer=0;
				}
			}break;	
			default:Ndd.St1=1;
		}
	}else
	{
		PWR1=1;
		PWR2=1;
		//------------------
		//Отключение тестирования
		TST1=1;
		TST2=1;
		Ndd.test[0]=0xFF;
		Ndd.test[1]=0xFF;
		Ndd.test[2]=0xFF;
		Ndd.test[3]=0xFF;
	}
#endif 
//===================================================================
#ifdef	NDD18_CV
	Ndd.Info.bits.F1	=PG_F1;
	Ndd.Info.bits.F2	=PG_F2;

	debounce_Din(0,Convert_n(IN1),5);
	debounce_Din(1,Convert_n(IN2),5);
	debounce_Din(2,Convert_n(IN3),5);
	debounce_Din(3,Convert_n(IN4),5);
#endif 
//===================================================================
#ifdef	NDD16_C
//	Ndd.Info.bits.F1	=PG_F1;
//	Ndd.Info.bits.F2	=PG_F2;
	
	if(PWR==0)
	{
		//======================================================
		//if(ModePr == 0)
		{
			switch (Ndd.St1)
			{
				case 1:Test1_DIN0();
					   break;
				case 2:Read_DIN0();
					   break;
				case 3:Test0_DIN0();
					   break;
			}
			switch (Ndd.St2)
			{
				case 1:Test1_DIN1();
					   break;
				case 2:Read_DIN1();
					   break;	
				case 3:Test0_DIN1();
					   break;	
			}
			if((Ndd.test_0 != 0)&&(Ndd.test_1 != 0))
			{
				Ndd.Info.bits.TestRun = 1;	// Тест проводился 
				w=0;
				for(i=0;i<4;i++)
					w+=Ndd.test[i];
				if(w!=0) Ndd.Info.bits.TestRes = 0;
				else Ndd.Info.bits.TestRes = 1;
			}
			if(PWR!=0)
			{
				for(i=0;i<4;i++)
					Ndd.test[i]=0xFF;
			}
		}
		/*if(ModePr == 1)
		{
			G1 = 1;
			G2 = 1;
			for(i=0;i<4;i++) Ndd.test[i]=0;
					
			StDin[0]=Convert_n(IN1);
			StDin[1]=Convert_n(IN2);
			StDin[2]=Convert_n(IN3);
			StDin[3]=Convert_n(IN4);
			dwData = StDin[0];
			dwData |= ((DWORD)StDin[1])<<8;
			dwData |= ((DWORD)StDin[2])<<16;
			dwData |= ((DWORD)StDin[3])<<24;
			
			for(i=0;i<32;i++)
			{
				if(digit(dwData, i) == 0) COUNTER_DIN[0][i]++;
				else	COUNTER_DIN[1][i]++;
			}
			if(getTime(&Ndd.TimerNdd) == 0)
			{
				setTime(&Ndd.TimerNdd, TIME_NAKOPL);
			
				dwData = 0;
				for(i=0;i<32;i++)
				{
					if(COUNTER_DIN[1][i]>COUNTER_DIN[0][i])	SETBIT(dwData,i);

					COUNTER_DIN[0][i] = 0;
					COUNTER_DIN[1][i] = 0;
				}
				Ndd.state[0] = (BYTE)dwData;
				Ndd.state[1] = (BYTE)(dwData>>8);
				Ndd.state[2] = (BYTE)(dwData>>16);
				Ndd.state[3] = (BYTE)(dwData>>24);
			}	
		}
		if(ModePr == 2)
		{
			G1 = 1;
			G2 = 1;
			for(i=0;i<4;i++) Ndd.test[i]=0;
			
			StDin[0]=Convert_n(IN1);
			StDin[1]=Convert_n(IN2);
			StDin[2]=Convert_n(IN3);
			StDin[3]=Convert_n(IN4);
			
			dwData = StDin[0]&0xFF;
			dwData |= (((DWORD)StDin[1])<<8)&0x0000FF00;
			dwData |= (((DWORD)StDin[2])<<16)&0x00FF0000;
			dwData |= (((DWORD)StDin[3])<<24)&0xFF000000;
			
			for(i=0;i<32;i++)
			{
				if(digit(dwData, i) != 0) COUNTER_DIN[1][i]=1;
			}
			if(getTime(&Ndd.TimerNdd) == 0)
			{
				setTime(&Ndd.TimerNdd, TIME_NAKOPL);
			
				dwData = 0;
				for(i=0;i<32;i++)
				{
					if(COUNTER_DIN[1][i] != 0)	SETBIT(dwData,i);
					
					COUNTER_DIN[1][i] = 0;
				}
				Ndd.state[0] = (BYTE)dwData;
				dwData = dwData>>8;
				Ndd.state[1] = (BYTE)(dwData);
				dwData = dwData>>8;
				Ndd.state[2] = (BYTE)(dwData);
				dwData = dwData>>8;
				Ndd.state[3] = (BYTE)(dwData);
			}	
		}*/
		//======================================================
		Ndd.Info.bits.PWRDin=~PWR;
	}else
	{
		Ndd.TimerTest=TIME_CONTROL_TEST;
		for(i=0;i<4;i++)
			Ndd.test[i]=0xFF;
		Ndd.Info.bits.PWRDin=~PWR;
		Ndd.St1=1;
		Ndd.St2=3;
	}
//===================================================================
#endif
	//__EI();
}
BYTE Convert_n(BYTE n)
{
	BYTE i;
	BYTE s=0;
	for(i=0;i<8;i++)
	{
		s|=digit(n,i)<<(7-i);
	}
	return s;
}
BYTE Convert_a(BYTE n)
{
	BYTE i,s=0;
	for(i=0;i<3;i++)
	{
		s|=digit(n,i)<<(2-i);
	}
	return s;
}
//===================================================================
//Ndd.TimerTest
//TIME_CONTROL_TEST
void Test1_DIN0()
{
//	BYTE t;
	if(Ndd.Timer>1)
	{
		Ndd.Timer=0;
		
		Ndd.tmp_test[0]=Convert_n(IN1);
		Ndd.tmp_test[1]=Convert_n(IN2);
		Ndd.St1=2;
	
		PWR1=1;
		TST1=0;
		G1=1;
	}
}
void Test0_DIN0()
{
	if(Ndd.Timer>16)
	{
		Ndd.Timer=0;
		
		Ndd.tmp_test[0]|=~Convert_n(IN1);
		Ndd.tmp_test[1]|=~Convert_n(IN2);
		Ndd.test[0] = Ndd.tmp_test[0];
		Ndd.test[1] = Ndd.tmp_test[1];
		Ndd.test_0 = 1;
		Ndd.St1=1;
		
		PWR1=1;
		TST1=1;
		G1=0;
	}
}
void Read_DIN0()
{
	if(Ndd.Timer>2)
	{
		Ndd.Timer=0;
		Ndd.state[1]=Convert_n(IN2);
		Ndd.state[0]=Convert_n(IN1);
		//debounce_Din(0,Convert_n(IN1),5);
		//debounce_Din(1,Convert_n(IN2),5);

		Ndd.St1=3;
		
		PWR1=0;
		TST1=1;
		G1=0;
	}
}
//$$$$$$$$$$$$$$$$$$$$$$
void Test1_DIN1()
{
	if(Ndd.Timer2>1)
	{
		Ndd.Timer2=0;
		
		Ndd.tmp_test[2]|=Convert_n(IN3);
		Ndd.tmp_test[3]|=Convert_n(IN4);
		Ndd.test[2] = Ndd.tmp_test[2];
		Ndd.test[3] = Ndd.tmp_test[3];
		Ndd.test_1 = 1;
		
		Ndd.St2=2;
		PWR2=1;
		TST2=0;
		G2=1;
	}
}
void Test0_DIN1()
{
	if(Ndd.Timer2>16)
	{
		Ndd.Timer2=0;

		Ndd.tmp_test[2]=~Convert_n(IN3);
		Ndd.tmp_test[3]=~Convert_n(IN4);
		
		Ndd.St2=1;
		
		PWR2=1;
		TST2=1;
		G2=0;
	}
}
void Read_DIN1()
{
	if(Ndd.Timer2>2)
	{
		Ndd.Timer2=0;
		Ndd.state[2]=Convert_n(IN3);
		Ndd.state[3]=Convert_n(IN4);
		//debounce_Din(2,Convert_n(IN3),5);
		//debounce_Din(3,Convert_n(IN4),5);

		Ndd.St2=3;
		
		PWR2=0;
		TST2=1;
		G2=0;
	}
}
//-------------------------------------------------------------------
#endif
