#include "mb90590.h"
#include "sio.h"
#include "AVV2_C.h"
#include "slugebn.h"
#include "timer.h"
#include "appli.h"
#include "flash.h"

#ifdef PLATA_AVV2C

CAVV2 Avv;


void 	(*INIT_BLOK)(void)=InitAVV2C;
void 	(*DRIVER_BLOK)(void)=DriverAVV;
WORD	(*STATE_BLOCK) 		= &Avv.Info.word;

//========================================================================================
					 //ch1   ch2  ch3  ch4	DAC  GND	
const BYTE SelektCH[]={0x48,0x58,0x68,0x78,0x38,0x08};
//========================================================================================
#define chCH1 0
#define chCH2 1
#define chCH3 2
#define chCH4 3
#define chDAC 4
#define chGND 5
//========================================================================================
#define 	NUM_POINT_FILTER 20
long int 	MEMORY[COUNT_CH][NUM_POINT_FILTER];
#define 	ADDR_COEFF	0xFB0000
CTARIR		Tarir_new;
//========================================================================================
WORD TIME_TEM=CICKL_OPROS_TEM/TIMER_RESOLUTION_MS;
WORD TIME_5S=5000/TIMER_RESOLUTION_MS;
WORD TIME_3S=3000/TIMER_RESOLUTION_MS;
WORD TIME_1_5S=1500/TIMER_RESOLUTION_MS;
WORD TIME_1S=1000/TIMER_RESOLUTION_MS;
WORD TIME_10MS=10/TIMER_RESOLUTION_MS;
WORD TIME_5MS=5/TIMER_RESOLUTION_MS;
WORD TIME_1MS=1/TIMER_RESOLUTION_MS;
//========================================================================================
void MeasureCH(BYTE Ch);
void MeasureCH_Regim(BYTE Ch,BYTE Regim);
void UpdateDataADC(void);
void MeasureCH_Tarr(BYTE Ch, BYTE Regim);
//=========================================================================================
//#define SEL_CH(n)  PDR6=SelektCH[n];
//void SelektChanel(BYTE n)	//Подключение соответствующего канала
//{
//	PDR6=SelektCH[n];
//}
#define SelektChanel(n)  PDR6=SelektCH[n];
//=========================================================================================
void SetupPPG()
{
	PPGC0=0;
	PPG01=0x0;
	
	PRLL1=2;
	PRLH1=2;
	
	PPGC1_PE10=1;
	PPGC1_PEN1=1;
}
//=========================================================================================
void InitAVV2C()
{
	BYTE i,j;
	__far WORD *p1,*p2;
	
	DDR0=0x00;
	DDR1=0x03;
	DDR2=0x01;
	DDR4=0x00;
	DDR5=0x3c;
	DDR6=0x78;
	DDR7=0x00;
	DDR8=0x00;
	DDR9=0x00;
	InitSIO(SIO_2MHz);
	
	CSDAC	=1;
	CSADC	=1;
	EN		=1;
	BND		=1;
	
	A0	=0;
	A1	=0;
	A2	=0;
	EN	=1;
	Avv.Info.bits.Addr	=1;
	ADDR_NODE			=1;
	Avv.Status			=0;
	Avv.fNewDAC			=0.0;
	Avv.fDAC			=0.5;
	Avv.workRegim_AVV	=1;
	Avv.newRegim_AVV	=0;
	Avv.RegimWork		=0;
	LEDR				=1;
	LEDG				=1;
	Avv.Coeff.K=1;
	Avv.Coeff.Ofs=0;
	//-------------
	Avv.WriteCoeffFlash=0;
	p2=(__far WORD *)(ADDR_COEFF);
	p1=(__far WORD *)(&Tarir_new);
	
	if((p2[0]==0xFFFF) && (p2[1]==0xFFFF))
	{
		for(i=0;i<COUNT_CH_REGIM;i++)
		{
			for(j=0;j<COUNT_CH;j++)
			{
				Tarir_new.ADC_New[i][j].K	=1;//0.00000149;//1;
				Tarir_new.ADC_New[i][j].Ofs	=0;
				clrwdt;
			}
		}
		Tarir_new.ADC_New[0][0].Ofs	=0;//0.000236268;
		Tarir_new.ADC_New[0][1].Ofs	=0;//-0.00003208;
		Tarir_new.ADC_New[0][2].Ofs	=0;//0.000284639;
		Tarir_new.ADC_New[0][3].Ofs	=0;//0.000133843;

		
		Tarir_new.DAC_New.K		=1;
		Tarir_new.DAC_New.Ofs	=0;
		
		WriteFlashBuff(p1,ADDR_COEFF,COUNT_CH*COUNT_CH_REGIM*4+4*2, 1);
		puts("Reset Tarir. coefficient.\n\r#");
	}
	for(i=0;i<(COUNT_CH*COUNT_CH_REGIM*4+4*2);i++)
	{
		p1[i]=p2[i];
		clrwdt;
	}
//--------------------------------------------	
	//ENIR = 0x04;	// Disable Interrupts
	//ELVR = 0x30;	// Set Level Detect
	//EIRR = 0x00;	// Clear Interrupt bits
	//ENIR = 0x04;	// Enable Ext Int 0 and 1

//--------------------------------------------
	SetupPPG();
}
//=========================================================================================
//Запись физической величины в ЦАП
void WriteDAC_U(float data)
{
	WORD cod;
	Avv.fDAC=data;
	
	data=Tarir_new.DAC_New.K*data+Tarir_new.DAC_New.Ofs;
	
	if(data>=0)
	{
		cod=data;
		cod|=0x8000;
		if(data>32767)cod=0xFFFF;
	}else
	{
		data*=-1;
		cod=data;
		cod=(~cod)&0x7FFF;
		if(data<-32767)cod=0;
	}
	
	SES 		= 0;
	CSDAC=0;
	SDR=(BYTE)(cod>>8);
	start_sio();
	SDR=(BYTE)(cod);
	start_sio();
	stop_sio();
	CSDAC=1;
	SES 		= 1;
}
//=========================================================================================
//Преобразование кода АЦП в значение
float ConvertADC_COD_TO_FLOAT(DWORD data)
{
	float fl;
	if((data&0x800000)==0)
	{
		return data;
	}else
	{
		fl=(float)((~data)&0x7FFFFF);
		fl*=-1;
		return fl;
	}
}
//=========================================================================================
//Чтение кода с АЦП
DWORD ReadADC_COD()
{
	BYTE i;
	DWORD cod=0,d;
	
	CSADC=0;
	SDR=0x1;
	start_sio();
	SDR=0;
	
	for(i=0;i<20;i++);
	
	for(i=0;i<3;i++)
	{
		start_sio();
		d=SDR;
		cod|=d<<(8*(2-i));
	}
	
	stop_sio();
	CSADC=1;
	return cod;
}
//=========================================================================================
void WriteConfigADC(BYTE st,BYTE N,BYTE R)
{
	BYTE n,r;
	if(st==0)
	{
		return;
	}else
	{
		r=N;
		n=R;
	}
	if(r<13)
	{
		r|=0x50;
		CSADC=0;
		SDR=r;
		start_sio();
		SDR=0;
		start_sio();
		SDR=n;
		start_sio();
		stop_sio();
		CSADC=1;
		return;
	}
	if(r==0xFF)
	{
		CSADC=0;
		SDR=n;
		start_sio();
		SDR=0;
		stop_sio();
		CSADC=1;
		return;
	}
	if(r==15)
	{
		BND=n&1;
		return;
	}
	
}
//=========================================================================================
//Калибровка нуля
void CalibrationADC_0()
{
	float fCod;
	BYTE  i=0;
	DWORD dwCod;
	DWORD OCR;
	
	SelektChanel(chGND);
	//=========================
	OCR=0xFF;
	WriteConfigADC(1,7,0xFF);
	WriteConfigADC(1,8,0);
	WriteConfigADC(1,9,0);
	
	WriteConfigADC(1,10,0x59);
	WriteConfigADC(1,11,0x55);
	WriteConfigADC(1,12,0x55);
	//========================
//	Avv.Timer=0;
//	while(Avv.Timer<TIME_5MS);
//	WriteConfigADC(1,0xFF,SYSOCAL);
	while(1)
	{
		if(i==NUM_POINT_FILTER)
		{
			Avv.Timer=0;
			fCod=0;
			for(i=0;i<NUM_POINT_FILTER;i++)
			{
				fCod+=MEMORY[chGND][i];
			}
			fCod=fCod/NUM_POINT_FILTER;
			if((fCod<=150) && (fCod>=(-150)))
			{
				break;
			}
			OCR+=(fCod/1.4);
			
			WriteConfigADC(1,7,OCR&0xff);
			WriteConfigADC(1,8,((OCR&0xff00)>>8));
			WriteConfigADC(1,9,((OCR&0xff0000)>>16));
			i=0;
		}	
		clrwdt;
		if(DRDY==0)
		{
			dwCod=ReadADC_COD();
			fCod=ConvertADC_COD_TO_FLOAT(dwCod);
			MEMORY[chGND][i++]=fCod;	
		}
	}
}
//=========================================================================================
// Выставляем режим измерения АЦП (каждый режим свой диапазон по максимальному и минимальному
// значению)
float SetRegim(BYTE Regim)
{
	float Ur;
	BYTE i;
	Avv.Timer=0;
	while(Avv.Timer<TIME_5MS);
	if(Regim==1 || Regim==0)
	{
			BND=1;
			WriteConfigADC(1,0,0x00);
			Ur=10;
	}else
	{
		if(Regim>9) Regim=9;
		BND=0;
		WriteConfigADC(1,0,(Regim-2)&0x7);
		Ur=1.0;
		if(Regim>2)
		{
			for(i=0;i<(Regim-2);i++)
				Ur=Ur/2;
		}
	}
	return Ur; 
}
//=============================================================================================

//=========================================================================================
void ControlKoeff()
{
	BYTE i;
	__far WORD   *p1,*p2;
	WORD d1,d2;

	if(Avv.WriteCoeffFlash==1)
	{
		Avv.WriteCoeffFlash=0;
		p2=(__far WORD *)(ADDR_COEFF);
		p1=(__far WORD *)(&Tarir_new);
	
		for(i=0;i<(COUNT_CH*COUNT_CH_REGIM*4+4*2);i++)
		{
			//__DI();
			d1=p1[i];
			d2=p2[i];
			d1^=d2;
			//__EI();
			if(d1)
			{
				puts("Start write new tarirov.\n\r#");
				WriteFlashBuff(p1,ADDR_COEFF,COUNT_CH*COUNT_CH_REGIM*4+4*2, 1);
				puts("Successfully write!\n\r#");
				return;
			}
			clrwdt;
		}
	}
}
//=========================================================================================
void DriverAVV()
{
//	BYTE r;
	
	Avv.Info.bits.Mode	=MODE;
	Avv.Info.bits.F1	=PG_F1;
	//-----------------------------------------
	if(Avv.RegimWork == 0)
	{
		//Контроль изменения тарировок и записи их во FLASH
		ControlKoeff();
		//-----------------------------------------
		//Измерение температуры
		//if(Avv.TimerTem>=TIME_TEM)
		//{
		//	tem(&Avv.Temperature);
		//	Avv.TimerTem=0;
		//}
		//----------------------------------------
		//Запись пришедших изменений конфигурации
		//WriteConfigADC(0,0,0);
		//----------------------------------------
		//Запись новых данных в ЦАП
		if(Avv.fNewDAC!=Avv.fDAC)
		{
			Avv.fDAC=Avv.fNewDAC;
			WriteDAC_U(Avv.fDAC);
		}
	}
	//==========================================
	if((Avv.workRegim_AVV!=Avv.newRegim_AVV)||(Avv.Status==0))
	{
		Avv.workRegim_AVV=Avv.newRegim_AVV;
		//----------------------------------------------------
		if(Avv.workRegim_AVV<10)
			MeasureCH_Tarr(0, Avv.workRegim_AVV);
		else
			MeasureCH_Tarr(0, 0);
		//----------------------------------------------------
	}
	UpdateDataADC();
	Avv.Status=4;
	//==========================================
}
//=========================================================================================
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
void UpdateDataADC(void)
{
	float fCod;
	DWORD dwCod;
	float Um;
	BYTE i,j, Num;

	if(Avv.RegimWork == 0)
		Num = COUNT_CH;
	else Num = COUNT_CH-2;
	
	//Num = 1;
	
	for(j=Num;j>0;j--)
	{ 
		SelektChanel(j-1);
		//for( i=0;i<50;i++) wait1mks();
		
		while(DRDY!=1)clrwdt;
		while(DRDY!=0)clrwdt;
		
	//	while(DRDY!=1)clrwdt;
	//	while(DRDY!=0)clrwdt;
		
	//	while(DRDY!=1)clrwdt;
	//	while(DRDY!=0)clrwdt;
	
		dwCod=ReadADC_COD();
		//=============================================================
		//fCod=ConvertADC_COD_TO_FLOAT(dwCod);
		if((dwCod&0x800000)==0)
		{
			fCod = dwCod;
		}else
		{
			fCod=(float)((~dwCod)&0x7FFFFF);
			fCod*=-1;
		}
		//=============================================================
		if(Avv.workRegim_AVV < 2) i=0;
		else i=1;
			Um=Tarir_new.ADC_New[i][j-1].K*fCod+Tarir_new.ADC_New[i][j-1].Ofs;	

		Avv.fADC[j-1]=(float)Um;
		clrwdt;
	}
}
//=========================================================================================
// Измерение напряжение при уже известных тарировочных коэффициентах
void MeasureCH_Tarr(BYTE Ch, BYTE Regim)
{
	Avv.Status=0;
	//==========================
	WriteConfigADC(1,0xFF,SYSRESET);
	CalibrationADC_0();
	Avv.Status=1;
	//==========================
	SelektChanel(Ch);
	SetRegim(Regim);
	//===========================
}
//==================================================================================================

WORD CountInp	=0;
WORD CRC_IN		=0;
BYTE Status		=0;
CTARIR	Tarir_com;
const BYTE pas[5]={2,6,2,1,9};

void GetAndWriteTarirov(BYTE in)
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
			count =sizeof(Tarir_new);
			pData =(BYTE *)&Tarir_new;
			
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
			
			CountInp = 0;
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
			count =sizeof(Tarir_new);
			count = count/8;
			
			Putch((BYTE)(count&0xFF));
			
			CountInp = 0;
			Status 	= 0;
			return;
		}
	}
	if(Status == 2)
	{
		count =sizeof(Tarir_com);
		pData =(BYTE *)&Tarir_com;
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
				pSrc =(BYTE *)&Tarir_new;	
				for(i=0;i<count;i++)
				{
					pSrc[i] = pData[i];
					clrwdt;
				}
				Avv.WriteCoeffFlash=1;
				
			};
			Status 	= 0;
			CountInp= 0;
		}
	}
}

/*
//Чтение всех регистров АЦП
void~ReadAllRegister()
{
	BYTE i;
	CSADC=0;
	SDR=0x10;
	start_sio();
	SDR=0xD;
	start_sio();
	SDR=0;
	for(i=0; i<20;i++);
	for(i=0;i<13;i++)
	{
		start_sio();
		Avv.RegRead[i]=SDR;
	}
	stop_sio();
	CSADC=1;
}
//=========================================================================================
//Запись кода в ЦАП
void~WriteDAC(WORD data)
{
	SES 		= 0;
	CSDAC=0;
	SDR=(BYTE)(data>>8);
	start_sio();
	SDR=(BYTE)(data);
	start_sio();
	stop_sio();
	CSDAC=1;
	SES 		= 1;
}
//========================================================================================
//=========================================================================================
// Расчёт коэффициетов АЦП для определённого режима
void~CalcCoeff(BYTE Regim)
{
	float Ur;
	BYTE i=0;
	float fCod;
	long int  Cod1,Cod2;
	BYTE Count=0;
//	DWORD aCod;
//	WORD Cod;
	//------------------------------
//	WriteConfigADC(1,0xFF,SYSRESET);
	Avv.Timer=0;
	while(Avv.Timer<TIME_5MS);
	//----------------
	Ur=SetRegim(Regim);
	CalibrationADC_0();
	SelektChanel(chDAC);
	//SysGainCalibration(Regim);
	//----------------
	WriteDAC_U(0.6*Ur);//+Ur*0.6
	//================
	Avv.Timer=0;
	while(Avv.Timer<TIME_1MS);
	Avv.Timer=0;
	while(1)
	{
		if(i==NUM_POINT_FILTER)
		{
			fCod=0;
			for(i=0;i<NUM_POINT_FILTER;i++)
			{
				fCod+=MEMORY[chDAC][i];
			}
			Cod1=fCod/NUM_POINT_FILTER;
			break;
		}
		clrwdt;
		if(DRDY==0)
		{
			fCod=ConvertADC_COD_TO_FLOAT(ReadADC_COD());
			MEMORY[chDAC][i++]=fCod;	
		}		
	}
	//--------------------------------
	WriteDAC_U(-Ur*0.6);//+Ur*0.6
	Avv.Timer=0;
	Count=0;
	while(Avv.Timer<TIME_1MS);
	Avv.Timer=0;
	i=0;
	while(1)
	{
		if(i==NUM_POINT_FILTER)
		{
			fCod=0;
			for(i=0;i<NUM_POINT_FILTER;i++)
			{
				fCod+=MEMORY[chDAC][i];
			}
			Cod2=fCod/NUM_POINT_FILTER;
			break;
		}
		clrwdt;
		if(DRDY==0)
		{
			fCod=ConvertADC_COD_TO_FLOAT(ReadADC_COD());
			MEMORY[chDAC][i++]=fCod;	
		}
	}
	//-------------------------------------------------------------------------------------
	__DI();
	Avv.Coeff.K=(-2*Ur*0.6)/(Cod2-Cod1);
	Avv.Coeff.Ofs=Ur*0.6+(Cod1*2*0.6*Ur)/(Cod2-Cod1);
	__EI();
}
//Измерение напряжения в конкретном канале с подбором нужного диапазона измерения
void~MeasureCH(BYTE Ch)
{
	float fCod;
	float Um;
	BYTE Regim,i=0;
	Avv.Status=0;
	//==========================
	WriteConfigADC(1,0xFF,SYSRESET);
	CalcCoeff(1);
	
	Avv.Status=1;
	//==========================
	SelektChanel(Ch);
	Avv.Timer=0;
	while(Avv.Timer<TIME_1MS);
	while(1)
	{
		if(i==NUM_POINT_FILTER)
		{	
			fCod=0;
			for(i=0;i<NUM_POINT_FILTER;i++)
			{
				fCod+=MEMORY[Ch][i];
			}
			fCod=fCod/NUM_POINT_FILTER;
			break;
		}
		clrwdt;
		if(DRDY==0)
		{
			fCod=ConvertADC_COD_TO_FLOAT(ReadADC_COD());
			MEMORY[Ch][i++]=fCod;	
		}
	}
	Avv.Status=2;
	//Um=Avv.Coeff.Mul*Avv.workADC+Avv.Coeff.Offset;
	Um=Avv.Coeff.K*fCod+Avv.Coeff.Ofs;
	Um=Um/5+Um;
	//================================================
	Regim=SelecktRegim(Um);	
	if(Regim!=1) CalcCoeff(Regim);
	Avv.Status=3;
	Avv.Timer=0;
	SelektChanel(Ch);
	//================================================
	Avv.Timer=0;
	while(Avv.Timer<TIME_1_5S)
	{
		clrwdt;
		UpdateDataADC();
	}
	//================================================
	Avv.Status=4;
}

// Измерение напряжения в конкретном канале с заданным диапазоном измерения
void~MeasureCH_Regim(BYTE Ch,BYTE Regim)
{
//	float fCod;
	Avv.Status=0;
	//==========================
	WriteConfigADC(1,0xFF,SYSRESET);
	CalcCoeff(Regim);
	Avv.Status=1;
	Avv.Timer=0;
	SelektChanel(Ch);
	//================================================
	Avv.Timer=0;
	while(Avv.Timer<TIME_1_5S)
	{
		clrwdt;
		UpdateDataADC();
	}
	//================================================
	Avv.Status=4;
}
// Авто калибровка коэффициетов АЦП с заданием конкретногот диапазона измерения
float~SysGainCalibration(BYTE Regim)
{
	float Ur;
//	float fCod;
//	WORD Cod;
	BYTE i;
	SelektChanel(chDAC);
	Avv.Timer=0;
	while(Avv.Timer<TIME_5MS);
	if(Regim==1 || Regim==0)
	{
			BND=1;
			WriteConfigADC(1,0,0x00);
			Ur=10;
	}else
	{
		BND=0;
		WriteConfigADC(1,0,(Regim-2)&0x7);
		Ur=1.4;
		if(Regim>2)
		{
			for(i=0;i<(Regim-2);i++)
				Ur=Ur/2;
		}
	}
	return Ur; 
}
// определение режима измерения для заданного значения напряжения
BYTE~SelecktRegim(float U)
{
	if(U<0) U*=-1;
	if(U>1.4) 						return 1;
	if(U>0.7 		&& U<=1.4) 		return 2;
	if(U>0.35 		&& U<=0.7) 		return 3;
	if(U>0.175 		&& U<=0.35) 	return 4;
	if(U>0.0875		&& U<=0.175) 	return 5;
	if(U>0.04375 	&& U<=0.0875) 	return 6;
	if(U>0.021875 	&& U<=0.04375) 	return 7;
	if(U>0.0109375 	&& U<=0.021875)	return 8;
	if(U<=0.0109375)				return 9;
}
*/
#endif
