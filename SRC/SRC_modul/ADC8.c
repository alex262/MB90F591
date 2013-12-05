#include "mb90590.h"
#include "ADC8.h"
#include "appli.h"
#include "timer.h"
#include "flash.h"

#ifdef PLATA_ADC8

CADC8 Adc;

#define ADDR_COEFF	0xFD0000

void 	(*INIT_BLOK)(void)	= InitADC8;
void 	(*DRIVER_BLOK)(void)= DriverADC8;
WORD 	(*STATE_BLOCK) 		= &Adc.Info.word;

//=========================================================================
#define ADC_WAIT_CONVERT (300/TIMER_RESOLUTION_MS)
TARIROV_K k_new[COUNT_ADC_CH];
			  
//WORD TIME_TEM=CICKL_OPROS_TEM/TIMER_RESOLUTION_MS;

//---------------------------------------------------------------------------
void InitADC8()
{
	BYTE i;
	__far WORD *p1,*p2;

	DDR0=0x00;
	DDR1=0x2F;
	DDR2=0x00;
	DDR4=0xFF;
	//DDR5=0xFF;
	//DDR6=0xFF;
	//DDR7=0xFF;
	DDR5=0x0;
	DDR6=0x0;
	DDR7=0x0;
	
	DDR8=0x00;
	DDR9=0x01;
	
	Adc.Info.word=0;
	Adc.Info.bits.Addr	=ADDR;
	ADDR_NODE		  	=ADDR;
	
	LEDR=1;
	LEDG=1;
		
	Adc.WriteCoeffFlash=0;
	
	p2=(__far WORD *)(ADDR_COEFF);
	p1=(__far WORD *)(&k_new);
	
	if((p2[0]==0xFFFF) && (p2[1]==0xFFFF))
	{
		for(i=0;i<COUNT_ADC_CH;i++)
		{
			k_new[i].K=1.0;
			k_new[i].Ofs=0;
		}
		WriteFlashBuff(p1,ADDR_COEFF,COUNT_ADC_CH*4,1);
		puts("Reset Tarir. coefficient.\n\r#");
	}
	for(i=0;i<COUNT_ADC_CH*4;i++)
	{
		p1[i]=read_word(ADDR_COEFF+i*2);
		clrwdt;
	}
	for(i=0;i<COUNT_ADC_CH;i++)
	{
		Adc.fADC[i]=0;
	}
	
	Adc.TimerWait = ADC_WAIT_CONVERT;
	add_timer(&Adc.TimerWait);

	
}
//=============================================================================
void SelectChannel(BYTE n)
{
	if(n<8)
	{
		CS9_16  = 0xFF;
		CS17_24 = 0xFF;
		CS1_8 = (~(0x80>>n));
		return;
	}	
	if((n>7)&&(n<16))
	{
		CS1_8	= 0xFF;
		CS17_24	= 0xFF;
		CS9_16 = (~(0x80>>(n-8)));
		return;
	}
	if((n>15)&&(n<24))
	{
		CS1_8	= 0xFF;
		CS9_16	= 0xFF;
		CS17_24 = (~(0x80>>(n-16)));
		return;
	}
}
//=============================================================================
void DeSelectAllChannel(void)
{
	CS1_8	= 0xFF;
	CS9_16	= 0xFF;
	CS17_24 = 0xFF;
}
//=============================================================================
void wait1mks()
{
	__wait_nop();
	__wait_nop();
	__wait_nop();
	__wait_nop();
	__wait_nop();
	__wait_nop();
	__wait_nop();
	__wait_nop();
	__wait_nop();
	__wait_nop();
	__wait_nop();
}
//=============================================================================

void ReadADC(void)
{
	BYTE i, j, sig;
	WORD d, bit;
	
	D_SDA_1	= 0;
	D_SCL_1	= 1;
	D_SDA_2	= 0;
	D_SCL_2	= 1;
	SCL_A_1 = 0;
	SCL_A_2 = 0;
				
	for(i=0; i<COUNT_ADC_CH; i++)
	{
		__DI();
		SelectChannel(i);
			
		if(i<12)
		{
			if(SDA_A_1 == 0)	// конверсия завершена
			{
				SCL_A_1 = 1;
				wait1mks();		// EOC
				SCL_A_1 = 0;
				wait1mks();
				
				SCL_A_1 = 1;
				wait1mks();		
				if(SDA_A_1 != 0) continue;// "0"
				SCL_A_1 = 0;
				wait1mks();
				
				SCL_A_1 = 1;
				wait1mks();		
				sig = SDA_A_1;// "SIG"
				SCL_A_1 = 0;
				wait1mks();
				
				d = 0;
				for(j=0; j<16; j++)
				{
					SCL_A_1 = 1;
					wait1mks();		
					bit = SDA_A_1;
					d |= (bit)<<(15-j); 
					SCL_A_1 = 0;
					wait1mks();		
				}
				
				if(sig == 0)
				{
					d = ~d;
					Adc.fADC[i] = d;
					Adc.fADC[i] = Adc.fADC[i]*(-1);
				}else
				{
					Adc.fADC[i] = d;
				}	
				Adc.fADC[i] = Adc.fADC[i]*k_new[i].K + k_new[i].Ofs;
			}
		}else
		{
			if(SDA_A_2 == 0)	// конверсия завершена
			{
				SCL_A_2 = 1;
				wait1mks();		// EOC
				SCL_A_2 = 0;
				wait1mks();
				
				SCL_A_2 = 1;
				wait1mks();		
				if(SDA_A_2 != 0) continue;// "0"
				SCL_A_2 = 0;
				wait1mks();
				
				SCL_A_2 = 1;
				wait1mks();		
				sig = SDA_A_2;// "SIG"
				SCL_A_2 = 0;
				wait1mks();
				
				d = 0;
				for(j=0; j<16; j++)
				{
					SCL_A_2 = 1;
					wait1mks();		
					bit = SDA_A_2;
					d |= (bit)<<(15-j); 
					SCL_A_2 = 0;
					wait1mks();		
				}
				if(sig == 0)
				{
					d = ~d;
					Adc.fADC[i] = d;
					Adc.fADC[i] = Adc.fADC[i]*(-1);
				}else
				{
					Adc.fADC[i] = d;
				}	
				Adc.fADC[i] = Adc.fADC[i]*k_new[i].K + k_new[i].Ofs;
			}
		}
		__EI();
	}
	__EI();
	DeSelectAllChannel();
}

BYTE ST_READ[3];
BYTE SIG[3];
BYTE NUL_BIT[3];
WORD DataAdc[COUNT_ADC_CH];
unsigned char tmp[50];	
void ReadADC_New(void)
{
	BYTE i, j,st = 0;
	BYTE d[3];	
	
	
	_CS1_D = 1;
	_CS2_D = 1;
	
	D_DATA1= 0x00;
	D_DATA2= 0x00;
	D_DATA3= 0x00;
	
	D_SCL_1	= 1;
	D_SCL_2	= 1;
	SCL_A_1= 0;
	SCL_A_2= 0;
	
	_CS1 = 0;	
	_CS2 = 0;
	
	if((_DATA1 == 0)&&(_DATA2 == 0)&&(_DATA3 == 0)) // конверсия завершена по всем АЦП
	{
		st = 1;
		ST_READ[0] = 0;
		ST_READ[1] = 0;
		ST_READ[2] = 0;
	}else 
	{
		if(getTime(&Adc.TimerWait) == 0) // таймаут закончен
		{
			st = 1;	
			ST_READ[0] = _DATA1;
			ST_READ[1] = _DATA2;
			ST_READ[2] = _DATA3;
		}
	}
	
	if( st == 1)	// опрашиваем те входы где данные готовы
	{	
		for(i=0; i<COUNT_ADC_CH; i++)
			DataAdc[i] = 0;
		
		SCL_A_1 = 1;
		SCL_A_2 = 1;
		wait1mks();		// EOC
		SCL_A_1 = 0;
		SCL_A_2 = 0;
		wait1mks();
				
		SCL_A_1 = 1;
		SCL_A_2 = 1;
		wait1mks();		
		NUL_BIT[0] = _DATA1;// "0"
		NUL_BIT[1] = _DATA2;// "0"
		NUL_BIT[2] = _DATA3;// "0"
		SCL_A_1 = 0;
		SCL_A_2 = 0;
		wait1mks();
				
		SCL_A_1 = 1;
		SCL_A_2 = 1;
		wait1mks();		
		SIG[0] = _DATA1;// "SIG"
		SIG[1] = _DATA2;// "SIG"
		SIG[2] = _DATA3;// "SIG"
		SCL_A_1 = 0;
		SCL_A_2 = 0;
		wait1mks();
		//--------------------------------------	

		for(i=0; i<16; i++)
		{
			SCL_A_1 = 1;
			SCL_A_2 = 1;
			wait1mks();		
			d[0] = _DATA1;
			d[1] = _DATA2;
			d[2] = _DATA3;
			
			for(j=0; j<COUNT_ADC_CH; j++)
			{
				if(j<8)
				{
					DataAdc[j] |=digit(d[0],(7-j))<<(15-i); 
				}	
				if((j>7)&&(j<16))
				{
					DataAdc[j] |=digit(d[1],(15-j))<<(15-i); 
				}
				if((j>15)&&(j<24))
				{
					DataAdc[j] |=digit(d[2],(23-j))<<(15-i); 
				}			
			}
			SCL_A_1 = 0;
			SCL_A_2 = 0;
			wait1mks();		
		}
		//---------------------
	/*	
		puts("ch1 - sig ");
		putD(digit(SIG[0],7));
		puts(" data ");
		put_24bit_value(DataAdc[0]);
		puts(" || ");
		puts("ch2 - sig ");
		putD(digit(SIG[1],3));
		puts(" data ");
		put_24bit_value(DataAdc[12]);
		puts("\n\r");
		*/
		for(j=0; j<COUNT_ADC_CH; j++)
		{
			DataAdc[j] = DataAdc[j]&0xFFFF;
			if(j<8)
			{
				if(digit(ST_READ[0],(7-j)) == 1) 
				{
					Adc.fADC[j] = 1000;
					continue;
				}
				if(digit(NUL_BIT[0],(7-j)) == 1) 
				{
					Adc.fADC[j] = 1000;
					continue;
				}
				if(digit(SIG[0],(7-j)) == 0)
				{
					DataAdc[j] = ~DataAdc[j] ;
					Adc.fADC[j] = DataAdc[j];
					Adc.fADC[j] = Adc.fADC[j]*(-1);
				}else
				{
					Adc.fADC[j] = DataAdc[j];
				}
			}	
			if((j>7)&&(j<16))
			{
				if(digit(ST_READ[1],(15-j)) == 1) 
				{
					Adc.fADC[j] = 1000;
					continue;
				}
				if(digit(NUL_BIT[1],(15-j)) == 1)
				{
					Adc.fADC[j] = 1000;
					continue;
				}
				
				if(digit(SIG[1],(15-j)) == 0)
				{
					DataAdc[j] = ~DataAdc[j] ;
					Adc.fADC[j] = DataAdc[j];
					Adc.fADC[j] = Adc.fADC[j]*(-1);
				}else
				{
					Adc.fADC[j] = DataAdc[j];
				}
			}
			if((j>15)&&(j<24))
			{
				if(digit(ST_READ[0],(23-j)) == 1) 
				{
					Adc.fADC[j] = 1000;
					continue;
				}
				if(digit(NUL_BIT[2],(23-j)) == 1)
				{
					Adc.fADC[j] = 1000;
					continue;
				}
				if(digit(SIG[2],(23-j)) == 0)
				{
					DataAdc[j] = ~DataAdc[j] ;
					Adc.fADC[j] = DataAdc[j];
					Adc.fADC[j] = Adc.fADC[j]*(-1);
				}else
				{
					Adc.fADC[j] = DataAdc[j];
				}
			}			
			
			Adc.fADC[j] = Adc.fADC[j]*k_new[j].K + k_new[j].Ofs;
		}
		//---------------------------------------
		setTime(&Adc.TimerWait, ADC_WAIT_CONVERT);
	}
	_CS1 = 1;	
	_CS2 = 1;	
}
//------------------------------------------------------------------------------
int ConvertADCtoINT(WORD d)
{
	int c;
	if((d&0x2000)==0)
	{
		return d;
	}else
	{
		c=(int)((~d+1)&0x1FFF);
		c*=-1;
		return c;
	}
}
//=============================================================================
void ControlKoeff()
{
//	BYTE i;
	__far WORD   *p1,*p2;
	//WORD d1,d2;

	if(Adc.WriteCoeffFlash==1)
	{
		Adc.WriteCoeffFlash=0;
		p2=(__far WORD *)(ADDR_COEFF);
		p1=(__far WORD *)(&k_new);
	
		WriteFlashBuff(p1,ADDR_COEFF,COUNT_ADC_CH*4,1);
	}
}
//=============================================================================
void DriverADC8()
{
	BYTE i;

	ControlKoeff();
	i=ADDR;	
	Adc.Info.bits.Addr	=i;
	if(i!=ADDR_NODE)
	{
		setState(Initialisation);
		ADDR_NODE			=ADDR;
	}
	Adc.Info.bits.Mode	=MODE;

	//ReadADC();
	ReadADC_New();
	
	GetPak_Uart(0);
}

//===================================================================
// Посылаем тарировки по UART
//	DWORD	wCountTar;					// Количество тарировок
//	TARIROV_K	tTar[COUNT_TAR_COEFF];	// Тарировки ЦАПа
//}TSendPakTar; 

TSendPakTar SendPakTar;
void SendTarADC8(void)
{
	BYTE i;
	SendPakTar.wCountTar = COUNT_ADC_CH;
	
	for(i=0; i<COUNT_ADC_CH; i++)
	{
		SendPakTar.tTar[i].K = k_new[i].K;
		SendPakTar.tTar[i].Ofs = k_new[i].Ofs;
	}
	Send_Pkt(0,(BYTE *)(&SendPakTar),sizeof(TSendPakTar),1,1);
}


#endif