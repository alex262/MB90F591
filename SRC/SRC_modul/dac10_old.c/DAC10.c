#include "mb90590.h"
#include "sio.h"
#include "DAC10.h"
#include "appli.h"
#include "timer.h"
#include "flash.h"
#include "i2c.h"

#ifdef PLATA_DAC10

const char SoftwareVer[20] = { __TIME__" " __DATE__}; 


#define ADDR_COEFF	0xFD0000
//==============================================================================
//Максимальное значение которое можно записать в ЦАП 
//Минимальное значение которое можно записать в ЦАП    

#ifdef PLATA_DAC10_ROKOT
	const static float	MinValueDac[COUNT_DOUT_CH] = {4.0,   4.0,  4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	const static float	MaxValueDac[COUNT_DOUT_CH] = {20.0, 20.0, 20.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0};
#endif
#ifdef PLATA_DAC10_ZENIT
	const static float	MinValueDac[COUNT_DOUT_CH] = {0.0,   0.0,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	const static float	MaxValueDac[COUNT_DOUT_CH] = {5.0,   5.0,  5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0};
#endif
//==============================================================================

CDAC10 Dac10;
TSendPak1 SendPak1;
TSendPak2 SendPak2;

WORD	(*STATE_BLOCK) 		= &Dac10.Info.word;
void	(*INIT_BLOK)(void)	= InitDAC10;
void 	(*DRIVER_BLOK)(void)= DriverDAC10;

WORD TIME_WAIT_SELECT_MASTER = 30/TIMER_RESOLUTION_MS;				// Время задержки перед выставлением статуса мастер
WORD TIME_WAIT_SELECT_MASTER_IF_ERROR = 3000/TIMER_RESOLUTION_MS;	// Время задержки перед выставлением статуса мастер при наличии ощибок и отсутствия другого мастера на шине
float	dERR_DAC_mA = 0.05;											//Погрешность измерения ЦАП ->АЦП

TARIROV_K	TarrRAM_DAC[COUNT_DAC_CH];	// Тарировки ЦАПа скопированные в RAM  
//TARIROV_K	TarrRAM_ADC[COUNT_ADC_CH];	// Тарировки АЦП  скопированные в RAM  

TPAK_SPI_RM		pak_spi_rm;
TPAK_SPI_ADC	pak_spi_adc;
TPAK_SPI_DAC	pak_spi_dac;
BYTE	Spi_Buf_In[20];
BYTE	Spi_Buf_Out[20];

WORD Wait5ms = 5/TIMER_RESOLUTION_MS;
WORD Wait1ms = 1/TIMER_RESOLUTION_MS;

WORD PeriodDout	= 2/TIMER_RESOLUTION_MS;

WORD PeriodOprosDin		= 25/TIMER_RESOLUTION_MS;
WORD PeriodOprosAin		= 20/TIMER_RESOLUTION_MS;
WORD PeriodOprosTemp	= 1000/TIMER_RESOLUTION_MS;

//==============================================================================
void Operate_Max1329_DAC_Write(BYTE Num, BYTE ch, WORD data);
void Operate_Max1329_ADC_Convert(BYTE Num, BYTE Mux, BYTE Gain, BYTE Bip);
void Operate_Max1329_RegMode(BYTE Num, BYTE RW, BYTE Adr, BYTE Count);
WORD Operate_Max1329_DAC_Read(BYTE Num, BYTE ch);
void Operate_Max1329_Reset(BYTE Num);
void Operate_Max1329_RegMode_Mask(WORD Mask, BYTE Adr, BYTE Count);// только запись
void Operate_Max1329_DAC_Write_Mask(WORD Mask, BYTE ch, WORD data);

void SelectAll_DAC(void);
void UnSelectAll_DAC(void);
void SelectSPI_DAC(BYTE ch);
void SelectMask_DAC(WORD Mask);
void SelectMasterDAC(void);
//------------------------------------------------------------------------------
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

void WaitConvert(void)
{
	BYTE i;
	for(i=0;i<5;i++)
		PDR6_P60 = ~PDR6_P60;
}
//------------------------------------------------------------------------------
void InitDAC10(void)
{
	BYTE i;
//	__far WORD *p1,*p2;
	
	//---------------------

	DDR0=0x00;
	DDR1=0x03;
	DDR2=0x00;
	DDR3=0x9A;
	DDR4=0x1F;
	DDR5=0xFF;
	DDR6=0x00;
	DDR7=0xCF;
	DDR8=0xFF;
	DDR9=0x05;
	//---------------------
	SDA_TRIS = 1;
	SCL	= 1;
	SDA	= 1;

	//---------------------
	InitSIO(SIO_2MHz);
	//SetInvertSIO(1);

	Dac10.Info.word=0;
	Dac10.Info.bits.Addr=ADDR;
	ADDR_NODE			=ADDR;
	
	LEDR=1;
	LEDG=1;

		
	Dac10.SendFlagUart=0;
	Dac10.WriteCoeffFlash=0;
	
	HighDensByteRead(0, &i);
	
	if(i == 0xFF)
	{
		for(i=0;i<COUNT_DAC_CH;i++)
		{
			TarrRAM_DAC[i].k	= 1.0;
			TarrRAM_DAC[i].ofs	= 0;
		}
		HighDensPageWrite(0, (BYTE *)&TarrRAM_DAC[0],128);
	}else
	{
		HighDensSequentialRead(0, (BYTE *)&TarrRAM_DAC[0],sizeof(TARIROV_K)*COUNT_DAC_CH);
	}
	
	
	for(i=0;i<COUNT_DAC_CH;i++)
	{
		Dac10.fDAC_New[i]	=0;
		Dac10.fDAC_Set[i]	=0;
	}
	
	for(i=0;i<COUNT_ADC_CH;i++)
	{
		Dac10.fADC[i]		=0;
	}
	for(i=0;i<COUNT_DIN_CH;i++)
	{
		Dac10.DIN[i]		=0;
	}
	for(i=0;i<COUNT_DOUT_CH;i++)
	{
		Dac10.DOUT_New[i]	=0;
		Dac10.DOUT_Set[i]	=1;
	}
	Dac10.TimerDin = 0;
	Dac10.EnOutDac = 0;
	Dac10.setEnOutDac = 0;
	//=============================================================
	PWR_DAC_1_6		=PWR_DAC_ON; //Запитывем ЦАПы
	PWR_DAC_7_12	=PWR_DAC_ON;
	
	// Задержка для вкл питания
	Dac10.Timer=0;
	while(Dac10.Timer<Wait5ms);

	// Reset всех ЦАПов
	Operate_Max1329_Reset(0xFF);
	
	Dac10.Timer=0;
	while(Dac10.Timer<Wait5ms);

	// CP/VM 
	Spi_Buf_Out[0]=0x00;
	Operate_Max1329_RegMode(0xFF, WRITE_MODE_SPI, 0xE,1);

	// инициализируем выходы
	Spi_Buf_Out[0]=0xff;
	Spi_Buf_Out[1]=0xff;
	Operate_Max1329_RegMode(0xFF, WRITE_MODE_SPI, 0x12,2);
	
	// инициализируем входы
	Spi_Buf_Out[0]=0x00;
	Spi_Buf_Out[1]=0x00;
	Operate_Max1329_RegMode(0xFF, WRITE_MODE_SPI, 0x10,2);
	
	
	// инициализируем АЦП
	Spi_Buf_Out[0]=0x17;
	//Spi_Buf_Out[0]=0x17;
	//Spi_Buf_Out[0]=0x97;
	Operate_Max1329_RegMode(0xFF, WRITE_MODE_SPI, 0x0,1);
	//Spi_Buf_Out[0]=0x40;
	Spi_Buf_Out[0]=0x00;
	Operate_Max1329_RegMode(0xFF, WRITE_MODE_SPI, 0x1,1);
	
	//Operate_Max1329_ADC_Convert(0xFF, 0x08, 0, 0);
	
	
	// инициализируем ЦАП 
	Spi_Buf_Out[0] = 0x42;		
	Operate_Max1329_RegMode(0xFF, WRITE_MODE_SPI, 0x0F,1);
	
	Spi_Buf_Out[0] = 0x5F;		
	Operate_Max1329_RegMode(0xFF, WRITE_MODE_SPI, 0x7,1);
	

	Operate_Max1329_DAC_Write(0xFF, 0, (MAX_COD_DAC/2));
	Operate_Max1329_DAC_Write(0xFF, 1, (MAX_COD_DAC/2));

	Spi_Buf_Out[0]=3;
	Operate_Max1329_RegMode_Mask(0xFFF, 0x13,1);
	
	Dac10.Master	=false;
	Dac10.StatusMaster = 0;
	Dac10.TarrStatus=true;
	if((TarrRAM_DAC[0].k==1.0)&&(TarrRAM_DAC[0].ofs==0))
		Dac10.TarrStatus		=false;
//	if((TarrRAM_ADC[0].k==1.0)&&(TarrRAM_ADC[0].ofs==0))
//		Dac10.TarrStatus		=false;
		
	Dac10.HiLoDec	= false;
	Dac10.HiLo		= 0;
	Dac10.DiagRele	= 0;
	Dac10.ErrorSet	= false;
	Dac10.TimerMasterError=0;
	Dac10.wOldError = 0;
}
//========================================================================
int ConvertADCtoINT(WORD d)
{
	int c;
	if((d&0x800)==0)
	{
		c = d; 
		return c;
	}else
	{
		c=(int)((~d+1)&0xEFF);
		c*=-1;
		return c;
	}
}
//========================================================================

// Выбор SPI 
void SelectMask_DAC(WORD Mask)
{
	if(Mask&0x0001) CS1 = CS_ON;
	if(Mask&0x0002) CS2 = CS_ON;
	if(Mask&0x0004) CS3 = CS_ON;
	if(Mask&0x0008) CS4 = CS_ON;
	if(Mask&0x0010) CS5 = CS_ON;
	if(Mask&0x0020) CS6 = CS_ON;
	if(Mask&0x0040) CS7 = CS_ON;
	if(Mask&0x0080) CS8 = CS_ON;
	if(Mask&0x0100) CS9 = CS_ON;
	if(Mask&0x0200) CS10 = CS_ON;
	if(Mask&0x0400) CS11 = CS_ON;
	if(Mask&0x0800) CS12 = CS_ON;
}

void SelectAll_DAC(void)
{
	CS1 = CS_ON;
	CS2 = CS_ON;
	CS3 = CS_ON;
	CS4 = CS_ON;
	CS5 = CS_ON;
	CS6 = CS_ON;
	CS7 = CS_ON;
	CS8 = CS_ON;
	CS9 = CS_ON;
	CS10 = CS_ON;
	CS11 = CS_ON;
	CS12 = CS_ON;
}
void UnSelectAll_DAC(void)
{
	CS1 = CS_OFF;
	CS2 = CS_OFF;
	CS3 = CS_OFF;
	CS4 = CS_OFF;
	CS5 = CS_OFF;
	CS6 = CS_OFF;
	CS7 = CS_OFF;
	CS8 = CS_OFF;
	CS9 = CS_OFF;
	CS10 = CS_OFF;
	CS11 = CS_OFF;
	CS12 = CS_OFF;
}
void SelectSPI_DAC(BYTE ch)
{
	if(ch>(COUNT_DAC_CH-1)) return;

	UnSelectAll_DAC();
	
	if(ch<6)
		SELECT_DAC(ch);
	else
		SELECT_DAC(ch+2);
		
	switch(ch)
	{ 
		case 0: 
			CS1 = CS_ON;
			break;
		case 1: 
			CS2 = CS_ON;
			break;
		case 2: 
			CS3 = CS_ON;
			break;
		case 3: 
			CS4 = CS_ON;
			break;
		case 4: 
			CS5 = CS_ON;
			break;
		case 5: 
			CS6 = CS_ON;
			break;
		case 6: 
			CS7 = CS_ON;
			break;
		case 7: 
			CS8 = CS_ON;
			break;
		case 8: 
			CS9 = CS_ON;
			break;
		case 9: 
			CS10 = CS_ON;
			break;
		case 10: 
			CS11 = CS_ON;
			break;
		case 11: 
			CS12 = CS_ON;
			break;
	}
}
//========================================================================
//Масштабирование записываемого значения запись в ЦАП     --
//==========================================================
void WriteNormalDataDac(BYTE ch, float data)
{
	float res;
	WORD out;

	if(ch>(COUNT_DAC_CH-1)) return;

	res=TarrRAM_DAC[ch].k*data+TarrRAM_DAC[ch].ofs;

	if(res>MAX_COD_DAC) res=(float)MAX_COD_DAC;
	if(res<MIN_COD_DAC) res=(float)MIN_COD_DAC;

	out=(WORD)res;
	Operate_Max1329_DAC_Write(ch, 1,out);
}
//===================================================================================
// Контроль за изменением тарировок, запись во FLASH по команде
//=============================================================================
void ControlKoeff()
{
	//__far WORD   *p1,*p2;

	if(Dac10.WriteCoeffFlash==1)
	{
		Dac10.WriteCoeffFlash=0;
		
/*		p2=(__far WORD *)(ADDR_COEFF);
		p1=(__far WORD *)(&TarrRAM_DAC);
	
		puts("Start write new tarirov for DAC.\n\r#");
		WriteFlashBuff(p1,ADDR_COEFF,COUNT_DAC_CH*4,1);
		
		p1=(__far WORD *)(&TarrRAM_ADC);
		puts("Start write new tarirov for ADC.\n\r#");
		WriteFlashBuff(p1,(ADDR_COEFF+COUNT_DAC_CH*8),COUNT_ADC_CH*4,0);
*/
		HighDensPageWrite(0, (BYTE *)&TarrRAM_DAC[0],128);
		
		puts("Successfully write!\n\r#");
	}
}
//=========================================================================
BYTE NumSt=0;

void DriverDAC10(void)
{
	BYTE	i, bData;
	WORD	wData;//, tmp;
	//int		iData;
	float	fData;
	//-------------------------------------
	#ifdef READ_TEMP
	if(Dac10.TimerTem>=TIME_TEM)
	{
		Dac10.TimerTem=0;
	}
	#endif
	//-------------------------------------
	ControlKoeff();
	//-------------------------------------
	#ifndef CASH_PDO_DATA
	__DI();
	#endif
	Dac10.Info.bits.ErrSet = Dac10.ErrorSet;
	i=ADDR;	
	Dac10.Info.bits.Addr	=i;
	if(i!=ADDR_NODE)
	{
		setState(Initialisation);
		ADDR_NODE			=ADDR;
	}
	Dac10.Info.bits.Mode	=MODE;
	Dac10.Info.bits.F1	=0;
	Dac10.Info.bits.F2	=0;
	#ifndef CASH_PDO_DATA
	__EI();
	#endif
	
	Dac10.AddData = DAC_STATUS_NEIGHBOUR|(DAC_ADD_ADDR<<8);

	//----------------------------------------------
	if(Dac10.TarrStatus==true)
		SelectMasterDAC();
	//--------------------------------------------------
	// Проверка записанного значения в ЦАП с помощью АЦП
	#ifndef CASH_PDO_DATA
	__DI();
	#endif
	
	/*if(Dac10.TimerErrDac>=80)
	{
		Dac10.TimerErrDac=80;
		for(i=0;i<COUNT_DAC_CH;i++)
		{
			if((Dac10.fDAC_Set[i]>(Dac10.fADC[i]+dERR_DAC_mA)) || 
				(Dac10.fDAC_Set[i]<(Dac10.fADC[i]-dERR_DAC_mA)))
			{
				Dac10.wError|=1<<i;
			}else
			{
				Dac10.wError&=(WORD)(~(1<<i));
			}
		}	
	}*/
	//----------------------------------------------
	if(Dac10.TimerDout >= PeriodDout)
	{
		Dac10.TimerDout = 0;
		Dac10.HiLoDec = true;
		Dac10.HiLo = ~Dac10.HiLo;
	}
	//=======================================================================================
	// Запись дискретных выходов
	// выбор режима работы цап по току или напряжению
	// коммутация на выход
	// коммутируем только если мы мастер
	//=======================================================================================
	
	//if(Dac10.wError != 0)
	if(Dac10.wOldError != Dac10.wError)
	{
		Dac10.TimerMasterError = 0;
		Dac10.ErrorSet = true;
	}
	wData = Dac10.EnOutDac&(~Dac10.wError);
	if((Dac10.Master == true)||(Dac10.TarrStatus==false))
	{
		if((wData/*Dac10.EnOutDac*/ != 0)&&(Dac10.HiLoDec == true))
		{
			if(Dac10.HiLo == 0)
				Spi_Buf_Out[0]=7;
			else
				Spi_Buf_Out[0]=3;
				
			Operate_Max1329_RegMode_Mask(wData/*Dac10.EnOutDac*/, 0x13,1);
		}
	}
	Dac10.HiLoDec = false;

	Operate_Max1329_DAC_Write_Mask((~Dac10.EnOutDac), 1, (MAX_COD_DAC/2));

	//----------------------------------------------
	for(i=0;i<COUNT_MAX1329;i++)
	{
		//=============================
		// Запись в ЦАП по изменениям
		//=============================
		if(Dac10.fDAC_New[i] != Dac10.fDAC_Set[i])
		{
			
			if(Dac10.TarrStatus == false)
			{
				Dac10.fDAC_Set[i] = Dac10.fDAC_New[i];
				WriteNormalDataDac(i, Dac10.fDAC_Set[i]);
			}else
			{
				//if((Dac10.EnOutDac&(((WORD)1)<<i)) != 0)
				{
					fData = Dac10.fDAC_New[i];
						
					if(fData>MaxValueDac[i])	fData = MaxValueDac[i];
					if(fData<MinValueDac[i])	fData = MinValueDac[i];
					if(fData != Dac10.fDAC_Set[i])
					{
						Dac10.fDAC_Set[i] = fData;
						WriteNormalDataDac(i, fData);
					}
				}	
			}
		}else
		{
			if(((Dac10.EnOutDac^Dac10.setEnOutDac)&(((WORD)1)<<i)) != 0)
			{
				WriteNormalDataDac(i, Dac10.fDAC_Set[i]);
			}	
		}
		//=============================================================================================
		// Опрашиваем дискретные входы
		//=============================================================================================
		if(Dac10.TimerDin >= PeriodOprosDin)
		{
			Operate_Max1329_RegMode(i, READ_MODE_SPI, 0x11,1);
			bData = Spi_Buf_In[0]&0x0F;
			Dac10.DIN[i] = bData;
			
			if((bData&8) == 0) SETBIT(Dac10.DiagRele,i);
			else CLEARBIT(Dac10.DiagRele,i);
			
			//if((bData&5) == 5) CLEARBIT(Dac10.wError,i);
			//else SETBIT(Dac10.wError,i);
			if((bData&5) != 5) SETBIT(Dac10.wError,i);
			
			
			
			if(i == (COUNT_MAX1329-1))
				Dac10.TimerDin = 0;
		}
		//===================================================
		// Опрашиваем АЦП 
		//===================================================
		/*Operate_Max1329_RegMode(i, READ_MODE_SPI, 2,2);
		tmp		= Spi_Buf_In[0];
		wData	= (tmp<<4)&0x0FF0;
		wData	|= (Spi_Buf_In[1]>>4)&0xF;
			
		iData = wData&0xFFF;
		
		Dac10.fADC[i] = TarrRAM_ADC[i].k*(float)iData + TarrRAM_ADC[i].ofs;
				
		Operate_Max1329_ADC_Convert(i, 0, 0, 0);*/
		//===================================================
		// Опрашиваем температурные датчики
		/*if(Dac10.TimerTemp >= PeriodOprosTemp)
		{
			
			Operate_Max1329_RegMode(i,READ_MODE_SPI, 2,2);
			
			tmp		= Spi_Buf_In[0];
			wData	= (tmp<<4)&0x0FF0;
			wData	|= (Spi_Buf_In[1]>>4)&0xF;
			
			iData = ConvertADCtoINT(wData);
			
			Dac10.Temperature[i] = iData*0.125;
			
			//Operate_Max1329_ADC_Convert(i,0x8, 0, 0);
			
			if(i == (COUNT_MAX1329-1))
				Dac10.TimerTemp = 0;
		}*/
	}
	
	
	// -------------------------------------------------------------------------
	GetPak_Uart(0);
	if(Dac10.SendFlagUart==1)
	{
		Dac10.SendFlagUart=0;

		
		for(i=0;i<COUNT_DIN_CH;i++)
		{
			SendPak1.DIN[i]	=Dac10.DIN[i];
		}
		for(i=0;i<COUNT_DOUT_CH;i++)
		{
			SendPak1.DOUT[i]	=Dac10.DOUT_Set[i];
		}
		for(i=0;i<COUNT_DAC_CH;i++)
		{
			SendPak1.fStateDAC[i]   = Dac10.fDAC_Set[i];	
			//SendPak1.fStateDAC[i]   = Dac10.wDAC_Set[i];
		}
		for(i=0;i<COUNT_ADC_CH;i++)
		{
			SendPak1.fStateADC[i]   = Dac10.fADC[i];	
		}
		for(i=0;i<COUNT_MAX1329;i++)
			SendPak1.Temperature[i]   = Dac10.Temperature[i];
		
		for(i=0;i<10;i++)
			SendPak1.Temp[i] = Dac10.Temp[i];
		
		Send_Pkt(0,(BYTE *)(&SendPak1),sizeof(TSendPak1),1,1);
	}
	if(Dac10.SendFlagUart==2)
	{
		Dac10.SendFlagUart=0;
		for(i=0;i<COUNT_DAC_CH;i++)
		{
			SendPak2.tTarDAC[i].k   = TarrRAM_DAC[i].k;
			SendPak2.tTarDAC[i].ofs = TarrRAM_DAC[i].ofs;
		}
		for(i=0;i<COUNT_ADC_CH;i++)
		{
			SendPak2.tTarADC[i].k   = 1;//TarrRAM_ADC[i].k;
			SendPak2.tTarADC[i].ofs = 0;//TarrRAM_ADC[i].ofs;
		}
		Send_Pkt(0,(BYTE *)(&SendPak2),sizeof(TSendPak2),1,2);
	}
}
//========================================================================
//========================================================================
void Operate_Max1329_DAC_Write(BYTE Num, BYTE ch, WORD data)
{
	if(Num == 0xFF) SelectAll_DAC();
	else SelectSPI_DAC(Num);
	__DI();
					
	pak_spi_dac.bits.ch 	= ch;
	pak_spi_dac.bits.d1 	= 1;
	pak_spi_dac.bits.start	= 0;
	pak_spi_dac.bits.dac 	= data;
	pak_spi_dac.bits.rw 	= WRITE_MODE_SPI;
	Send_SIO(pak_spi_dac.data[1]);
	Send_SIO(pak_spi_dac.data[0]);
	stop_sio();
	__EI();
	UnSelectAll_DAC();
}
void Operate_Max1329_DAC_Write_Mask(WORD Mask, BYTE ch, WORD data)
{

	SelectMask_DAC(Mask);
	__DI();
					
	pak_spi_dac.bits.ch 	= ch;
	pak_spi_dac.bits.d1 	= 1;
	pak_spi_dac.bits.start	= 0;
	pak_spi_dac.bits.dac 	= data;
	pak_spi_dac.bits.rw 	= WRITE_MODE_SPI;
	Send_SIO(pak_spi_dac.data[1]);
	Send_SIO(pak_spi_dac.data[0]);
	stop_sio();
	__EI();
	UnSelectAll_DAC();
}
WORD Operate_Max1329_DAC_Read(BYTE Num, BYTE ch)
{
	WORD d;
	
	if(Num == 0xFF) SelectAll_DAC();
	else SelectSPI_DAC(Num);
	__DI();
	
	pak_spi_dac.bits.ch 	= ch;
	pak_spi_dac.bits.d1 	= 1;
	pak_spi_dac.bits.start	= 0;
	pak_spi_dac.bits.dac 	= 0;
	pak_spi_dac.bits.rw 	= READ_MODE_SPI;
	d=Send_SIO(pak_spi_dac.data[1]);
	d = (d&0xF)<<8;
	d |= Send_SIO(pak_spi_dac.data[0]);
	stop_sio();
	__EI();
	UnSelectAll_DAC();
}


void Operate_Max1329_ADC_Convert(BYTE Num, BYTE Mux, BYTE Gain, BYTE Bip)
{
	if(Num == 0xFF) SelectAll_DAC();
	else SelectSPI_DAC(Num);
	__DI();
	
	pak_spi_adc.bits.Mux	= Mux;
	pak_spi_adc.bits.Gain	= Gain;
	pak_spi_adc.bits.Bip	= Bip;
	pak_spi_adc.bits.start	= 1;
	
	Send_SIO(pak_spi_adc.data);
	stop_sio();
	__EI();
	UnSelectAll_DAC();
}

void Operate_Max1329_RegMode(BYTE Num, BYTE RW, BYTE Adr, BYTE Count)
{
	BYTE i;
	
	if(Num == 0xFF) SelectAll_DAC();
	else SelectSPI_DAC(Num);
	__DI();
	
	pak_spi_rm.data = 0;
	pak_spi_rm.bits.RW	= RW;
	pak_spi_rm.bits.adr	= Adr;
	Send_SIO(pak_spi_rm.data);
		
	if(RW == READ_MODE_SPI)
	{
		for(i=0;i<Count;i++)
			Spi_Buf_In[i] = Send_SIO(0);
		stop_sio();
	}else
	{
		for(i=0;i<Count;i++)
			Send_SIO(Spi_Buf_Out[i]);
		stop_sio();
	}
	__EI();
	UnSelectAll_DAC();
}
void Operate_Max1329_RegMode_Mask(WORD Mask, BYTE Adr, BYTE Count)// только запись
{
	BYTE i;
	
	SelectMask_DAC(Mask);
	
	__DI();
	
	pak_spi_rm.data = 0;
	pak_spi_rm.bits.RW	= WRITE_MODE_SPI;;
	pak_spi_rm.bits.adr	= Adr;
	Send_SIO(pak_spi_rm.data);
		
		for(i=0;i<Count;i++)
			Send_SIO(Spi_Buf_Out[i]);
		stop_sio();
	
	__EI();
	UnSelectAll_DAC();
}
void Operate_Max1329_Reset(BYTE Num)
{
	if(Num == 0xFF) SelectAll_DAC();
	else SelectSPI_DAC(Num);
	__DI();
	
	pak_spi_rm.data = 0;
	pak_spi_rm.bits.RW	= WRITE_MODE_SPI;
	pak_spi_rm.bits.adr	= 0x1F;
	Send_SIO(pak_spi_rm.data);
		
	Send_SIO(0xFF);
	stop_sio();
	__EI();
	UnSelectAll_DAC();
}

//========================================================================
// Процедура по выбору мастера из 3х ЦАПов
void SelectMasterDAC(void)
{
	//-------------------------------------------------
	// Проверяем есть ли в данный момент мастер на шине
	if(DAC_STATUS_NEIGHBOUR != 3)
	{
		// Мастер на шине уже есть выходим из процедуры определения мастера
		Dac10.Master=false;
		DAC_MASTER_SET_OFF;
		Dac10.TimerMasterError = 0;
		return;
	}
	// Если хотя бы по одному выходу есть проблемы, с выдачей команд, то данный цап не может быть мастером
	if(Dac10.ErrorSet == true)	
	{
		if(Dac10.TimerMasterError<TIME_WAIT_SELECT_MASTER_IF_ERROR)// скорее всего есть ошибки по и в других канала поэтом выбираем хотябы одного мастера
		{
			Dac10.wOldError = Dac10.wError;
			Dac10.Master=false;
			DAC_MASTER_SET_OFF;	
			return;	
		}
		Dac10.TimerMasterError = TIME_WAIT_SELECT_MASTER_IF_ERROR+1;
		
	}
	//-------------------------------------------------
	// Если нет связи с УСО выходим 
	if((program.TimerCan0>=TIME_OUT_CAN)&&(program.TimerCan1>=TIME_OUT_CAN))
	{
		Dac10.Master=false;
		DAC_MASTER_SET_OFF;
		return;
	}
	//-------------------------------------------------
	// Если блок не проинициализирован УСО выходим 
	if(getState() != Operational)
	{
		Dac10.Master=false;
		DAC_MASTER_SET_OFF;
		return;
	}
	//-------------------------------------------------
	// Если данный блок уже является мастером то выходим из процедуры выявления мастера
	if(Dac10.Master == true)
	{
		return;
	}
	//-----------------------------------------------------------------
	// БЛОК НЕ ЯВЛЯЕТСЯ МАСТЕРОМ, И В ДАННЫЙ МОМЕНТ НА ШИНЕ НЕТ МАСТЕРА
	//-----------------------------------------------------------------
	if(Dac10.StatusMaster == 0)
	{
		DAC_MASTER_SET_ON;
		Dac10.TimerMaster=0;
		Dac10.StatusMaster = 1;
		return;	
	}
	if(Dac10.StatusMaster == 1)
	{
		if(Dac10.TimerMaster<TIME_WAIT_SELECT_MASTER)
		{	// выжидаем реакции соседей
			return;
		}
		//==============================
		// Блок можем стать мастером
		Dac10.Master = true;
		Dac10.StatusMaster = 0;
		return;	
	}
	//-----------------------------------------------------------------
}
//========================================================================

#endif