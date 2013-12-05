#include "mb90590.h"
#include "Ndd20P.h"

#ifdef PLATA_NDD20P

CNDD20P Ndd;

void 	(*INIT_BLOK)(void)	= InitNDD20P;
void 	(*DRIVER_BLOK)(void)= Driver_NDD20P;
WORD 	(*STATE_BLOCK) 		= &Ndd.Info.word;

void InitNDD20P()
{
	BYTE i;
	
	SET_DIN0_TEST1;
	SET_DIN1_TEST1;
	
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
	for(i=0;i<2;i++)
	{
		Ndd.test[i]=0;
		Ndd.state[i]=0;
	}
	Ndd.Info.word=0;
	Ndd.St1=1;
	Ndd.St2=0;
	Ndd.PowerNew=0;
	Ndd.PowerOld=1;
	Ndd.Timer1_1=0;
	Ndd.Timer1_2=0;
	Ndd.Timer2_1=0;
	Ndd.Timer2_2=0;
	ADDR_NODE		  =ADDR;
	Ndd.Info.bits.Addr=ADDR;
}
//===================================================================
void Driver_NDD20P()
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
	}
	//UpdateDataNDD();
	__EI();
	
}
//======================================================================
void UpdateDataNDD(void)
{
	if(Ndd.PowerOld == 1)
	{
		if(Ndd.Timer1_1>=120000)
		{
			Ndd.Timer1_2=0;
			Ndd.Timer1_1=0;
			SET_DIN0_TEST1;
			Ndd.St1=3;
		}
		if(Ndd.Timer2_1>=120000)
		{
			Ndd.Timer2_2=0;
			Ndd.Timer2_1=0;
			SET_DIN1_TEST1;
			Ndd.St2=3;
		}
		switch (Ndd.St1)
		{
			case 1:Read_DIN0();
				   break;
			case 2:Test0_DIN0();
				   break;
			case 3:Test1_DIN0();
				   break;
		}
		switch (Ndd.St2)
		{
			case 1:Read_DIN1();
				   break;
			case 2:Test0_DIN1();
				   break;
			case 3:Test1_DIN1();
				   break;	
		}
	}else
	{
		PWR1=0;
		PWR2=0;
		TST1=0;
		TST2=0;
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
//===================================================================
void Test1_DIN0()
{
	if(Ndd.Timer1_2>19)
	{
		Ndd.Timer1_2=0;
		Ndd.test[0]=~Convert_n(IN1);
		Ndd.St1=1;
		SET_DIN0_READ;
		
	} 
}
void Test0_DIN0()
{
	if(Ndd.Timer1_2>2)
	{
		Ndd.Timer1_2=0;
		Ndd.test[0]|=Convert_n(IN1);
		Ndd.St1=1;
		SET_DIN0_READ;
	}
}
void Read_DIN0()
{
	if(Ndd.Timer1_2>2)
	{
		Ndd.state[0]=~Convert_n(IN1);
	}
	if(Ndd.Timer1_2>=200)	//100ms
	{
		Ndd.St1=2;
		Ndd.Timer1_2=0;
		SET_DIN0_TEST0;
	}
	if(Ndd.St2==0)
	{
			Ndd.St2=1;
			SET_DIN1_READ;
	}
}
//$$$$$$$$$$$$$$$$$$$$$$
void Test1_DIN1()
{
	if(Ndd.Timer2_2>19)
	{
		Ndd.Timer2_2=0;
		Ndd.test[1]=~Convert_n(IN2);
		Ndd.St2=1;
		SET_DIN1_READ;
	}
}
void Test0_DIN1()
{
	if(Ndd.Timer2_2>2)
	{
		Ndd.Timer2_2=0;
		Ndd.test[1]|=Convert_n(IN2);
		Ndd.St2=1;
		SET_DIN1_READ;
	}
}
void Read_DIN1()
{
	if(Ndd.Timer2_2>2)
	{
		Ndd.state[1]=~Convert_n(IN2);
	}
	if(Ndd.Timer2_2>=200) 	//100ms
	{
		Ndd.St2=2;
		Ndd.Timer2_2=0;
		SET_DIN1_TEST0;
	}
}
//-------------------------------------------------------------------
#endif
