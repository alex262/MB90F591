#include "mb90590.h"
#include "sio.h"
#include "ADC5_C.h"
#include "appli.h"
#include "timer.h"
#include "flash.h"

#ifdef PLATA_ADC

const char SoftwareVer[20] = { __TIME__" " __DATE__}; 

CADC5 Adc;

void 	(*INIT_BLOK)(void)	= InitADC5C;
void 	(*DRIVER_BLOK)(void)= DriverADC5;
WORD 	(*STATE_BLOCK) 		= &Adc.Info.word;

#define ADDR_COEFF	0xFD0000

//=========================================================================
//#pragma segment CONST=KOEFF,attr=CONST,locate=0xfd0000
//const TARITOV_K k_={1,0};
//=========================================================================
//#define MEMORY_POINT	10
//BYTE StartPoint=0;
//BYTE CountPoint=0;
//float MEMORY_ADC[32][MEMORY_POINT];
//=========================================================================
//#pragma segment DATA=ram2 
BYTE ChADC[33]={0x80,0x81,0x82,0x83,0x84,0x85,0x86,
			  0x40,0x41,0x42,0x43,0x44,0x45,0x46,
			  0x20,0x21,0x22,0x23,0x24,0x25,0x26,
			  0x10,0x11,0x12,0x13,0x14,0x15,0x16,
			  0x87,0x47,0x27,0x17,0};
//==========================================================================
float TEST_VALUE_DAC[COUNT_TEST_VALUE] = {-10.1, -9.1, -8.1, -7.1, -6.1 , -5.1, -4.1, -3.1, -2.1, -1.1
										 , -0.1,  1.1,  2.1,  3.1,  4.1,  5.1,  6.1,   7.1,  8.1,  9.1};
//==========================================================================
//#pragma segment DATA=ram1
TARIROV_K k_33_new[COUNT_TAR_COEFF];
			  
#define SEL_CH(n) rSEL_CH=ChADC[n];	
//void UpdateF(int x);
//void UpdateDataCH(BYTE ch,float data);

WORD TIME_TEM=CICKL_OPROS_TEM/TIMER_RESOLUTION_MS;
//---------------------------------------------------------------------------
void InitADC5C()
{
	BYTE i;
	__far WORD *p1,*p2;
	DDR0=0x00;
	DDR1=0x2F;
	DDR2=0x00;
	DDR4=0x43;//xCB;
	DDR5=0x1C;
	DDR6=0xF7;
	DDR7=0x60;
	DDR8=0x00;
	DDR9=0x01;
	
	//InitSIO(SIO_2MHz);
	//InitSIO(SIO_250KHz);
	
	SES = 1;
	
	NCS	=1;
	A0	=1;
	A1	=1;
	A2	=1;
	EN0	=0;
	EN1	=0;
	EN2	=0;
	EN3	=0;
	Adc.Timer=0;
	Adc.Info.word=0;
	Adc.Info.bits.Addr	=ADDR;
	ADDR_NODE		  	=ADDR;
	SC0 =0;
	SC1 =0;
	NCNVRT=1;
	
	LEDR=1;
	LEDG=1;
//--------------------------------------------	
	ENIR = 0x00;	// Disable Interrupts
	ELVR = 0xFFFF;	// Set Level Detect
	EIRR = 0x00;	// Clear Interrupt bits
//	ENIR = 0x04;	// Enable Ext Int 0 and 1
//--------------------------------------------
	//GetAndWriteTarirov(0);
		
	Adc.StRead=0;
	Adc.WriteCoeffFlash=0;
	Adc.EnableTest=TRUE;
	Adc.CurTest = 0;
	Adc.DAC		= 0;
	Adc.newDAC	= TEST_VALUE_DAC[Adc.CurTest];
	Adc.ErrADC	= 0;
	Adc.TimerTest=0;
	Adc.Reg		= 0;
	
	for(i=0;i<4;i++)
	{  
		Adc.Err[i]   =0;
		Adc.CountErr[i]   =0;
	}
	
	p2=(__far WORD *)(ADDR_COEFF);
	p1=(__far WORD *)(&k_33_new);
	
	if((p2[0]==0xFFFF) && (p2[1]==0xFFFF))
	{
		for(i=0;i<COUNT_TAR_COEFF;i++)
		{
			k_33_new[i].K=1;
			k_33_new[i].Ofs=0;
		}
		WriteFlashBuff(p1,ADDR_COEFF,COUNT_TAR_COEFF*4,1);
		puts("Reset Tarir. coefficient.\n\r#");
	}
	for(i=0;i<COUNT_TAR_COEFF*4;i++)
	{
		p1[i]=read_word(ADDR_COEFF+i*2);
		clrwdt;
	}
	for(i=0;i<33;i++)
	{
		Adc.fADC[i]=0;
	}
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
void wait5mks()
{
	wait1mks();
	wait1mks();
	wait1mks();
	wait1mks();
	wait1mks();
}
//============================================================================
//=============================================================================
void SelectChannel(BYTE n)
{
	SEL_CH((n)&0xF);
	SEL_CH((n)&0xF);
	SEL_CH(n);
}
/*void DeSelectChannel(BYTE n)
{
	SEL_CH(n&0xF);
}*/
//-----------------------------------------------------------------------------
BYTE ReadAdcManual(WORD * cAdc)
{
	WORD data=0,bit;
	BYTE i;
	
	__DI();
	SIO_SCLK = 0;
	CONVERT_ADC;
	wait1mks();
	Adc.Timer = 0;
	__EI();
	while(BUSY == 1)
	{
		if(Adc.Timer>1) 
		{
			return 0;
		}
	}
	__DI();
	for(i=0;i<16;i++)
	{
		SIO_SCLK = 1;
		wait1mks();
		
		bit = SIO_SDATA&1;
		if((i==0)||(i==1))
		{
			if(bit	== 1) 
			{
				__EI();
				return 0;
			}
		}else
		{
			if(bit)	data |= (bit)<<(15-i);
		}
		SIO_SCLK = 0;
		wait1mks();
	}
	__EI();
	*cAdc = data;
	return 1;
}
//=============================================================================
void WriteDAC(float data)
{
	WORD w_data;
	data=k_33_new[32].K*data+k_33_new[32].Ofs;
	
	if(data>=0)
	{
		w_data=data;
		w_data|=0x8000;
		if(data>32767)w_data=0xFFFF;
	}else
	{
		data*=-1;
		w_data=data;
		w_data=(~w_data)&0x7FFF;
		if(data<-32767)w_data=0;
	}
	__DI();
	InitSIO(SIO_2MHz);
	SES=0;
	NCS=0;
	SDR=(BYTE)(w_data>>8);
	start_sio();
	SDR=(BYTE)(w_data);
	start_sio();
	stop_sio();

//	WRITE_SIO((BYTE)(data));
//	WRITE_SIO((BYTE)(data>>8));
	NCS=1;
	SES=1;
	SMCS= 0x0200;
	
	__EI();
}
//=============================================================================

WORD ReadADC()
{
	WORD d;
	start_sio();
	d=SDR;
	d=(WORD)(d<<8);
	start_sio();
	d|=SDR;
	stop_sio();
	return d;
}

//------------------------------------------------------------------------------
int ConvertADCtoINT(WORD d)
{
	int c;
	if((d&0x2000)==0)
	{
		c = d&0x1FFF;
		return c;
	}else
	{
		c=(int)((~d+1)&0x1FFF);
		c*=-1;
		return c;
	}
}
//=============================================================================
void StartReadADC()
{
	if (Adc.StRead==0)
	{
		SelectChannel(0);
		Adc.StRead=1;
		CONVERT_ADC;
	}
}

//=============================================================================
//
void ReadAdcInt()
{
	int cod;
	WORD data;
	TARIROV_K *pT;
	
	__EI();
	
	if(Adc.Reg==0)
	{
		Adc.Reg=1;
		CONVERT_ADC;
		return;
	}
	if(Adc.Reg==1)
	{
		
		data = ReadADC();
		if((data&0xC000) == 0)
		{
			cod=ConvertADCtoINT(data);
			
			pT=&k_33_new[Adc.StRead];
			Adc.fADC[Adc.StRead]=cod*pT->K+pT->Ofs;
		}
		Adc.StRead++;
		if(Adc.StRead>32) Adc.StRead=0;
		SelectChannel(Adc.StRead);
		Adc.Reg=0;
	}
}
void ReadAllAdc(void)
{
	int cod;
	WORD data;
	TARIROV_K *pT;
	
	if((Adc.Reg==0)&&(Adc.Timer>1))
	{
		Adc.Reg=1;
	}
	if(Adc.Reg==1)
	{
		data = 0;
		if(ReadAdcManual(&data) == 1)
		{
			cod=ConvertADCtoINT(data);
			
			pT=&k_33_new[Adc.StRead];
			Adc.fADC[Adc.StRead]=cod*pT->K+pT->Ofs;
		}
		Adc.StRead++;
		if(Adc.StRead>32) Adc.StRead=0;
		SelectChannel(Adc.StRead);
		Adc.Reg=0;
		Adc.Timer = 0;
	}
}

//=============================================================================
void TestDAC_ADC()
{
	BYTE i=0;
	int cod;
	
	if(Adc.Info.bits.Mode<5)
		i=Adc.Info.bits.Mode+27;
	if(Adc.Info.bits.Mode==5 || Adc.Info.bits.Mode==6)
		i=Adc.Info.bits.Mode-5;
	if(Adc.Info.bits.Mode==7 || Adc.Info.bits.Mode==8)
		i=Adc.Info.bits.Mode;
	if(Adc.Info.bits.Mode==9 || Adc.Info.bits.Mode==10)
		i=Adc.Info.bits.Mode+5;
	if(Adc.Info.bits.Mode==11 || Adc.Info.bits.Mode==12)
		i=Adc.Info.bits.Mode+10;

	SelectChannel(i);
	CONVERT_ADC;
	while(BUSY==1);
	cod=ConvertADCtoINT(ReadADC());
	Adc.fADC[i]=cod*0.001221001221;
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
		p1=(__far WORD *)(&k_33_new);
	
		//for(i=0;i<COUNT_TAR_COEFF*4;i++)
		{
			//#ifndef CASH_PDO_DATA
			//__DI();
			//#endif
			//d1=p1[i];
			//d2=p2[i];
			//d1^=d2;
			//#ifndef CASH_PDO_DATA
			//__EI();
			//#endif
			//if(d1)
			{
				//puts("Start write new tarirov.\n\r#");
				WriteFlashBuff(p1,ADDR_COEFF,COUNT_TAR_COEFF*4,1);
				//puts("Successfully write!\n\r#");
				return;
			}
			//clrwdt;
		}
	}
}
//=============================================================================
void DriverADC5()
{
	BYTE i;
	float rA,minA,maxA;



	ControlKoeff();
	i=ADDR;	
	Adc.Info.bits.Addr	=i;
	if(i!=ADDR_NODE)
	{
		setState(Initialisation);
		ADDR_NODE			=ADDR;
	}
	Adc.Info.bits.Mode	=MODE;
	Adc.Info.bits.F1	=PG_F1;
	Adc.Info.bits.F2	=PG_F2;
	
	//if(Adc.Info.bits.F2==1 || Adc.Info.bits.F1==1)//ADC5
	//if(Adc.Info.bits.F2==0 || Adc.Info.bits.F1==1)	//ADC6
	//	SetError(ind_PWRAT);
	//else
	//	ClearError(ind_PWRAT);
	//==================================================
	ReadAllAdc();
	//==================================================
	if((Adc.newDAC!=Adc.DAC)&&(Adc.Reg == 0))
	{
		__DI();
		Adc.DAC=Adc.newDAC;
		WriteDAC(Adc.DAC);
		__EI();
	}
	//==================================================
	if((Adc.EnableTest == TRUE)&&(Adc.Reg == 0))
	{
		__DI();
		if(TEST_VALUE_DAC[Adc.CurTest] != Adc.DAC)	// 
		{
			Adc.EnableTest = FALSE;
		}else
		{
			if(Adc.TimerTest>1000)
			{
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!}
				Adc.TimerTest=0;
				
				maxA=TEST_VALUE_DAC[Adc.CurTest]+POGRESHNOST_DAC;
				minA=TEST_VALUE_DAC[Adc.CurTest]-POGRESHNOST_DAC;
				
				rA=Adc.fADC[28];
				if((rA>maxA)||(rA<minA))
					Adc.Err[0]++;
					
				rA=Adc.fADC[29];
				if((rA>maxA)||(rA<minA))
					Adc.Err[1]++;

				rA=Adc.fADC[30];
				if((rA>maxA)||(rA<minA))
					Adc.Err[2]++;
				
				rA=Adc.fADC[31];
				if((rA>maxA)||(rA<minA))
					Adc.Err[3]++;
				//=======================================
				Adc.CurTest++;
				if(Adc.CurTest>=COUNT_TEST_VALUE)
				{
					Adc.CurTest=0;
					for(i=0;i<4;i++)
					{
						if(Adc.Err[i]>0)
						{
							if(Adc.CountErr[i]<(COUNT_CICKLE_S_ERROR+COUNT_CICKLE_S_ERROR))
								Adc.CountErr[i]++;
						}else
							if(Adc.CountErr[i]>0) Adc.CountErr[i]--;
						if(Adc.CountErr[i]>=COUNT_CICKLE_S_ERROR)
						{
							Adc.ErrADC|=1<<i;
						}else
						{
							Adc.ErrADC&=(BYTE)(~(1<<i));
						}
						Adc.Err[i]=0;
						if(Adc.ErrADC!=0) SetError(ind_ERROR);
						else ClearError(ind_ERROR);
					}
				}
				Adc.newDAC=TEST_VALUE_DAC[Adc.CurTest];
				Adc.DAC=Adc.newDAC;
				WriteDAC(Adc.DAC);
				//=======================================
				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!}
			}
		}
		__EI();
	}
	//==================================================
//	if(Adc.TimerTem>=TIME_TEM)
//	{
//		tem(&Adc.Temp);
//		Adc.TimerTem=0;
//	}
	GetPak_Uart(0);
}
void DriverADC5_rgd()
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
	
	//ReadAdcInt_();

	GetPak_Uart(0);
}

//===================================================================
// Посылаем тарировки по UART
//	DWORD	wCountTar;					// Количество тарировок
//	TARIROV_K	tTar[COUNT_TAR_COEFF];	// Тарировки ЦАПа
//}TSendPakTar; 

TSendPakTar SendPakTar;
void SendTarADC6(void)
{
	BYTE i;
	SendPakTar.wCountTar = COUNT_TAR_COEFF;
	
	for(i=0; i<COUNT_TAR_COEFF; i++)
	{
		SendPakTar.tTar[i].K = k_33_new[i].K;
		SendPakTar.tTar[i].Ofs = k_33_new[i].Ofs;
	}
	Send_Pkt(0,(BYTE *)(&SendPakTar),sizeof(TSendPakTar),1,1);
}

//====================================================
/*WORD CountInp	=0;
WORD CRC_IN		=0;
BYTE Status		=0;
TARITOV_K k_33_com[COUNT_TAR_COEFF];
const BYTE pas[5]={2,6,2,1,9};

void~GetAndWriteTarirov(BYTE in)
{
	WORD count,i;
	BYTE *pData, *pSrc;
	WORD crc=0;
	
	if(Status == 0)
	{
		if(in == pas[CountInp]) CountInp++;
		else CountInp=0;
		if(CountInp == 5) 
		{
			Status = 1;	
			CountInp = 0;
		}
		return;
	}
	if(Status == 1)
	{
		if(in == 0x72)	//Чтение
		{
			count =sizeof(k_33_new);
			pData =(BYTE *)&k_33_new;
			
			Putch((BYTE)(count&0xFF));crc+=count&0xFF;
			Putch((BYTE)(count>>8));  crc+=count>>8;
			for(i=0;i<count;i++)
			{
				Putch(pData[i]);
				crc+=pData[i];
				clrwdt;
			}
			Putch((BYTE)(crc&0xFF));
			Putch((BYTE)(crc>>8));
			
			Status 	= 0;
			return;
		}
		if(in == 0x77)	//Запись
		{
			Status = 2;
			CountInp= 0;

			return;
		}
		if(in == 0x71) //Чтение количества тарировок
		{
			count =sizeof(k_33_new);
			count = count/8;
			
			Putch((BYTE)(count&0xFF));
			
			CountInp = 0;
			Status 	= 0;
			return;
		}
	}
	if(Status == 2)
	{
		count =sizeof(k_33_com);
		pData =(BYTE *)&k_33_com;
		if(CountInp<count)
		{
			pData[CountInp]=in;
		}
		if(CountInp == count) CRC_IN=in;
		if(CountInp == (count+1)) CRC_IN|=(WORD)(in<<8);
		
		CountInp++;
			
		if(CountInp == (count+2))
		{
			for(i=0;i<count;i++)
			{
				crc+=pData[i];
				clrwdt;
			}
			if(crc == CRC_IN)
			{
				Putch(0xAA);
				Putch(0x55);
				Putch(0xAA);
				Putch(0x55);
				pSrc =(BYTE *)&k_33_new;	
				for(i=0;i<count;i++)
				{
					pSrc[i] = pData[i];
					clrwdt;
				}
				Adc.WriteCoeffFlash=1;
				
			}else Putch(1);
			Status 	= 0;
			CountInp= 0;
		}
	}
}
/*void~ReadAllChanel()
{
	BYTE i,j;
	int cod;
	for(i=0;i<32;i++)
	{
		SelectChannel(i);
		for (j=0;j<240;j++)
		{
			wait1mks();
			wait1mks();
			clrwdt;
		}
		CONVERT_ADC;
		DeSelectChannel(i);
		
		cod=ConvertADCtoINT(ReadADC());
		
		#ifndef CASH_PDO_DATA
		__DI();
		#endif
		Adc.fADC[i]=cod*k_33_new[i].K+k_33_new[i].Ofs;
		#ifndef CASH_PDO_DATA
		__EI();
		#endif
	}
}
*/
/*
//=============================================================================
//#pragma register(2)
//__nosavereg 
__interrupt void~INT2(void)
{ 
	int cod;
	BYTE i;
	TARIROV_K *pT;
	
	#ifndef CASH_PDO_DATA
	__DI();
	#endif
	clrwdt;
	if((EIRR&0x04)==0) 
	{
		EIRR = 0x00;
		#ifndef CASH_PDO_DATA
		__EI();
		#endif
		return;
	}
	EIRR = 0x00;
	
	if (Adc.StRead>32)
	{
		Adc.StRead=0;
		#ifndef CASH_PDO_DATA
		__EI();
		#endif
	 	return;
	}
	cod=ConvertADCtoINT(ReadADC());
	i=Adc.StRead-1;
	pT=&k_33_new[i];
	
	Adc.fADC[i]=cod*pT->K+pT->Ofs;
	SelectChannel(Adc.StRead);
	
	if(Adc.StRead>31) 
	{
		Adc.StRead=0;
	 	rSEL_CH=0x07;
	}
	CONVERT_ADC;
	Adc.StRead++;
	#ifndef CASH_PDO_DATA
	__EI();
	#endif
	
}
//#pragma noregister
//========================================
void~UpdateDataCH(BYTE ch,float data)
{
	BYTE i;
	float w=0;
		
	MEMORY_ADC[ch][StartPoint]=data;
	if(ch==31)
	{
		StartPoint++;
		if(StartPoint==MEMORY_POINT)
			StartPoint=0;
	}
	for(i=0;i<MEMORY_POINT;i++)
	{
		w+=MEMORY_ADC[ch][i];	
	}
	w=w/MEMORY_POINT;
	Adc.fADC[ch]=w;
}*/
/*

	int cod;
	BYTE i;
	TARIROV_K *pT;
	
	__EI();
	
	if(Adc.Reg==0)
	{
		Adc.Reg=1;
		CONVERT_ADC;
		return;
	}
	if(Adc.Reg==1)
	{
		
		cod=ConvertADCtoINT(ReadADC());

		pT=&k_33_new[Adc.StRead];
		Adc.fADC[5+Adc.StRead]=cod*pT->K+pT->Ofs;
				
		if(cod>AdcBufMax[Adc.StRead])
			AdcBufMax[Adc.StRead] = cod;
		if(cod<AdcBufMin[Adc.StRead])
			AdcBufMin[Adc.StRead] = cod;
		
		if(curTick>=COUNT_TICK_BUF)
		{
			curTick = 0;
			for(i=0;i<5;i++)
			{
				pT=&k_33_new[i];
					
					
				cod = (AdcBufMax[i]-AdcBufMin[i])/2;
				Adc.fADC[i]=cod*pT->K+pT->Ofs;
				AdcBufMax[i] = -32000;
				AdcBufMin[i] = 32000;
			}
		}
		Adc.StRead++;
		curTick++;
		if(Adc.StRead>4) Adc.StRead=0;
		SelectChannel(Adc.StRead);
		Adc.Reg=0;
	}
*/
/*int AdcBufMax[5] = {-10000,-10000,-10000,-10000,-10000};
int AdcBufMin[5] = {10000,10000,10000,10000,10000};
#define COUNT_TICK_BUF	1000	//0.5s	 
WORD curTick=0;
void ReadAdcInt_()
{
	int cod;
	BYTE j;
	WORD i;
	TARIROV_K *pT;
	
	__EI();
	
	
	curTick++;

	for(j=0;j<5;j++)
	{
		CONVERT_ADC;
		for(i=0;i<20;i++)
			wait1mks();
		cod=ConvertADCtoINT(ReadADC());

		if(cod>AdcBufMax[j])
			AdcBufMax[j] = cod;
		if(cod<AdcBufMin[j])
			AdcBufMin[j] = cod;

		SelectChannel(j+1);
		for(i=0;i<1000;i++)
			wait1mks();
		
	}
	SelectChannel(0);
	
	if(curTick>=COUNT_TICK_BUF)
	{
		curTick = 0;
		for(i=0;i<5;i++)
		{
			pT=&k_33_new[i];
				
			Adc.fADC[5+i]=cod*pT->K+pT->Ofs;
				
			cod = (AdcBufMax[i]-AdcBufMin[i])/2;
			Adc.fADC[i]=cod*pT->K+pT->Ofs;
			AdcBufMax[i] = -32000;
			AdcBufMin[i] = 32000;
		}
	}
}*/

#endif