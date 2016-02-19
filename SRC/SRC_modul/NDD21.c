#include "mb90590.h"
#include "Ndd21.h"

#ifdef PLATA_NDD21
#include "filter.h"
#include "timer.h"

 

CNDD21 Ndd;
void 	(*INIT_BLOK)(void)=InitNDD21;
void 	(*DRIVER_BLOK)(void)=Driver_NDD21;
WORD 	(*STATE_BLOCK) 		= &Ndd.Info.word;

const char SoftwareVer[20] = { __TIME__" " __DATE__}; 

WORD 	TIME_CONTROL_TEST=10000/TIMER_RESOLUTION_MS;

void InitNDD21()
{
	BYTE i, j;

	DDR0=0x00;
	DDR1=0x03;
	DDR2=0x00;
	DDR4=0x00;
	DDR5=0x00;
	DDR6=0x0F;
	DDR7=0x00;
	DDR8=0x00;
	DDR9=0x00;
	//------------------
	LEDR=1;
	LEDG=1;
	//------------------
	//------------------
	//Отключение тестирования
	TST1=0;
	TST2=0;
	TST3=0;
	TST4=1;
	//------------------
	for(i=0;i<2;i++)
	{
		Ndd.test[i]		=0;
		Ndd.tmp_test[i]	=0;
		Ndd.state[i]	=0;
		Ndd.state[i]	=0;
		Ndd.pr_data[i]	=0;
		
		for(j=0;j<8;j++)
		{
			Ndd.counters[i][j]		=0;
			Ndd.counters_dr[i][j]	=0;
		}

	}
	Ndd.Info.word=0;
	Ndd.Timer	=0;
	Ndd.Timer2	=0;
	Ndd.St1		=1;
	Ndd.St2		=1;
	Ndd.test_0 = 0;
	Ndd.test_1 = 0;
	Ndd.stOff  = 0;
	
	ADDR_NODE		  =ADDR;
	Ndd.Info.bits.Addr=ADDR;
	Ndd.Timer=0;
}
//===================================================================
void Driver_NDD21()
{
	BYTE i, w;
	i=ADDR;	
	Ndd.Info.bits.Addr	=i;
	if(i!=ADDR_NODE)
	{
		setState(Initialisation);
		ADDR_NODE			=ADDR;
	}
	Ndd.Info.bits.Mode		=MODE;
	
//===================================================================
	/*if((PG_F1==0)&&(PG_F2==1))
		Ndd.Info.bits.F1=0;
	else
		Ndd.Info.bits.F1=1;*/
	Ndd.Info.bits.F1	=0;
	Ndd.Info.bits.F2	=0;
	
	if(Ndd.stOff == 0)
	{
		TST1=1;
		TST2=0;
		TST3=1;
		TST4=0;
		Ndd.test[0] = 0xFF;
		Ndd.test[1] = 0xFF;
		Ndd.St1		=1;
		Ndd.St2		=1;
		Ndd.Info.bits.PWRDin=0;
	}
	else
	{
		//===================================================================
		switch (Ndd.St1)
		{
			case 1:Test0_DIN0();
				   break;
			case 2:Test1_DIN0();
				   break;
			case 3:Read_DIN0();
				   break;
		}
		switch (Ndd.St2)
		{
			case 1:Read_DIN1();
				   break;
			case 2:Test1_DIN1();
				   break;	
			case 3:Test0_DIN1();
				   break;	
		}
		if((Ndd.test_0 == 1)&&(Ndd.test_1 == 1))
		{
			Ndd.Info.bits.PWRDin=1;
			Ndd.Info.bits.TestRun = 1;	// Тест проводился 
			w=0;
			for(i=0;i<2;i++)
				w+=Ndd.test[i];
			if(w!=0) Ndd.Info.bits.TestRes = 0;
			else Ndd.Info.bits.TestRes = 1;
		}
	}
}
//===================================================================
BYTE Convert_n(BYTE n)
{
	BYTE i,s=0;
	for(i=0;i<8;i++)
	{
		s|=digit(n,i)<<(7-i);
	}
	return s;
}
//===================================================================
void Test0_DIN0()
{
	if(Ndd.Timer>11)
	{
		Ndd.tmp_test[0]=~Convert_n(IN1);
		Ndd.St1=2;
		TST1=1;
		TST2=1;
	}
}
void Test1_DIN0()
{
	if(Ndd.Timer>15)
	{
		Ndd.tmp_test[0]|=Convert_n(IN1);
		Ndd.test[0]=Ndd.tmp_test[0];
		Ndd.St1=3;
		Ndd.test_0 = 1;
		TST1=0;
		TST2=1;
	}
}
void Read_DIN0()
{
	if(Ndd.Timer>19)
	{
		Ndd.Timer=0;
		// переделали из-за НДД19, чтобы было одинаково, 0 - сигнал замкнут
		//Ndd.state[0]=~Convert_n(IN1);
		Ndd.state[0]=Convert_n(IN1);
		Ndd.St1=1;
		TST1=0;
		TST2=0;
	}
}
//===================================================================
void Read_DIN1()
{
	if(Ndd.Timer2>3)
	{
		//Ndd.state[1]=~Convert_n(IN2);
		Ndd.state[1]=Convert_n(IN2);
		Ndd.St2=2;
		TST3=1;
		TST4=1;
	}
}
void Test1_DIN1()
{
	if(Ndd.Timer2>7)
	{
		Ndd.tmp_test[1]=Convert_n(IN2);
		Ndd.St2=3;
		TST3=0;
		TST4=0;
	}
}
void Test0_DIN1()
{
	if(Ndd.Timer2>19)
	{
		Ndd.Timer=0;
		Ndd.tmp_test[1]|=(~Convert_n(IN2));
		Ndd.test[1]=Ndd.tmp_test[1];
		Ndd.St2=1;
		Ndd.test_1 = 1;
		TST3=0;
		TST4=1;
	}
}
//-------------------------------------------------------------------
#endif
