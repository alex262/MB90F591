#include "mb90590.h"
#include "sio.h"
#include "DAC9.h"
#include "appli.h"
#include "timer.h"
#include "flash.h"

#ifdef PLATA_DAC9

const char SoftwareVer[20] = { __TIME__" " __DATE__}; 


#define ADDR_COEFF	0xFD0000

WORD TIME_TEM=CICKL_OPROS_TEM/TIMER_RESOLUTION_MS;
WORD TIME_WAIT_SELECT_MASTER = 30/TIMER_RESOLUTION_MS;	// Время задержки перед выставлением статуса мастер
//==============================================================================
CDAC9 Dac9;
TSendPak SendPak;

float	dERR_DAC_V=dERR_DAC_V_STEP;		//Погрешность измерения АЦП	= dERR_DAC_V_STEP*MODE(состояние переключателя) 

WORD	(*STATE_BLOCK) 		= &Dac9.Info.word;
void	(*INIT_BLOK)(void)	= InitDAC9;
void 	(*DRIVER_BLOK)(void)= DriverDAC9;

TARIROV_K	TarrRAM_DAC[COUNT_DAC_CH];	// Тарировки ЦАПа скопированные в RAM  
TARIROV_K	TarrRAM_ADC[COUNT_ADC_CH];	// Тарировки АЦП  скопированные в RAM  

const BYTE 		DAC_CH[COUNT_DAC_CH] = {23,22,21,9,11,7,6,15,13,8 ,5 ,4 ,3 ,2}; 	 //Соответствие каналов выходам ЦАПа
const BYTE 		ADC_CH[COUNT_ADC_CH] = {0 ,1 ,2 ,3,4 ,5,6,8 ,9 ,10,11,12,13,14,7,15};//Соответствие каналов входe АЦП

TPAK_SPI    pak_spi;
//TPAK_SPI  tmp_pak_spi;
//==============================================================================
void SelectDAC_CH(WORD ch);
void WriteControlRegisterDAC(WORD RG);
void WriteDac(BYTE nCH,WORD data);
//==============================================================================
//------------------------------------------------------------------------------
void InitDAC9(void)
{
	BYTE i;
	__far WORD *p1,*p2;
	
	//---------------------
	DAC_MASTER_SET_OFF;
	//---------------------
	
	DDR0=0x00;
	DDR1=0xE0;//20
	DDR2=0x00;
	
	DDR4=0x1F;
	DDR5=0x10;
	DDR6=0x37;
	DDR7=0xFF;
	DDR8=0xFF;
	DDR9=0x01;
	//---------------------
	//DAC_MASTER_SET_OFF;
	Dac9.StatusMaster = 0;
	TIME_WAIT_SELECT_MASTER = TIME_WAIT_SELECT_MASTER*(DAC_ADD_ADDR+1);
	//---------------------
	InitSIO(SIO_2MHz);
	SES 		= 1; //Avv
	
	A0	=1;
	A1	=1;
	A2	=1;
	EN1	=0;
	EN2	=0;
	Dac9.Info.word=0;
	Dac9.Info.bits.Addr	=ADDR;
	ADDR_NODE		  	=ADDR;
	Dac9.Master			=FALSE;
	Dac9.TarrStatus		=true;
	Dac9.wError			=0;
	CONVN_ADC=1;
	LOAD_DAC =1;
	SYNC_DAC =1;
	
	LEDR=1;
	LEDG=1;

		
	Dac9.StRead=0;
	Dac9.SendFlagUart=0;
	Dac9.WriteCoeffFlash=0;
	
	p2=(__far WORD *)(ADDR_COEFF);
	p1=(__far WORD *)(&TarrRAM_DAC);
	
	if((p2[0]==0xFFFF) && (p2[1]==0xFFFF))
	{
		for(i=0;i<COUNT_DAC_CH;i++)
		{
			TarrRAM_DAC[i].k=1.0;
			TarrRAM_DAC[i].ofs=0;
		}
		puts("Start write Tarir. coefficient. in FLASH\n\r#");
		WriteFlashBuff(p1,ADDR_COEFF,COUNT_DAC_CH*4,1);
		
		p1=(__far WORD *)(&TarrRAM_ADC);
		for(i=0;i<COUNT_ADC_CH;i++)
		{
			TarrRAM_ADC[i].k=1.0;
			TarrRAM_ADC[i].ofs=0;
		}
		WriteFlashBuff(p1,(ADDR_COEFF+COUNT_DAC_CH*8),COUNT_ADC_CH*4,0);
		
		puts("Reset Tarir. coefficient.\n\r#");
	}
	
	p1=(__far WORD *)(&TarrRAM_DAC);
	for(i=0;i<COUNT_DAC_CH*4;i++)
	{
		p1[i]=read_word(ADDR_COEFF+i*2);
		clrwdt;
	}
	
	p1=(__far WORD *)(&TarrRAM_ADC);
	for(i=0;i<COUNT_ADC_CH*4;i++)
	{
		p1[i]=read_word(COUNT_DAC_CH*8+ADDR_COEFF+i*2);
		clrwdt;
	}
	if((TarrRAM_DAC[0].k==1.0)&&(TarrRAM_DAC[0].ofs==0))
		Dac9.TarrStatus		=false;
	if((TarrRAM_ADC[0].k==1.0)&&(TarrRAM_ADC[0].ofs==0))
		Dac9.TarrStatus		=false;
	
	for(i=0;i<COUNT_DAC_CH;i++)
	{
		Dac9.fDAC_New[i]	=0;
		Dac9.fDAC_Cur[i]	=0;
	}
	
	for(i=0;i<COUNT_ADC_CH;i++)
	{
		Dac9.fADC[i]		=0;
//		Dac9.fErrADC[i]		=0;
	}
	//=============================================================
	Dac9.SelDAC_CH = 0;
	Dac9.SelDAC_CH_cur = 0;
	SelectDAC_CH(Dac9.SelDAC_CH);
	//-------------------------------------------------------------
    //Включаем питание выходных каскадов ЦАПа
    WriteControlRegisterDAC(0xD00);    //Выставляем опорное напряжение
	//-------------------------------------------------------------
	//dERR_DAC_V=1.0;//dERR_DAC_V_STEP*MODE;	//Допустимая погрешность ЦАП относительно АЦП
}
//========================================================================
// Выбор каналов ЦАПа 0 бит - 1:вкл 0:выкл
void SelectDAC_CH(WORD ch)
{
	if(ch == 0) 
	{
		OFF_ALL_DAC;
		return;
	}
	if((ch&0x3FFF) == 0x3FFF) 
	{
		ON_ALL_DAC;
		return;
	}
	
	K1 = ch & 1;
	K2 = (ch>>1) & 1;
	K3 = (ch>>2) & 1;
	K4 = (ch>>3) & 1;
	K5 = (ch>>4) & 1;
	K6 = (ch>>5) & 1;
	K7 = (ch>>6) & 1;
	K8 = (ch>>7) & 1;
	K9 = (ch>>8) & 1;
	K10= (ch>>9) & 1;
	K11= (ch>>10)& 1;
	K12= (ch>>11)& 1;
	K13= (ch>>12)& 1;
	K14= (ch>>13)& 1;
}
//================================================
//Посылыаем SPI пакет ЦПАу
void WritePakSpiDAC(void)
{
    SELECT_WORK_SPI(SEL_DAC);
    
    SYNC_DAC=0;
    SDR=pak_spi.data[2];
	start_sio();
    SDR=pak_spi.data[1];
	start_sio();
	SDR=pak_spi.data[0];
	start_sio();
    stop_sio();
    SYNC_DAC=1;
}
//=========================================
//Производим запись в контрольный регистр ЦАП 
void WriteControlRegisterDAC(WORD RG)
{
    RG&=0xFFF;
    
    pak_spi.data[0]=0;
    pak_spi.data[1]=0;
    pak_spi.data[2]=0;
    
    pak_spi.bits.DB =RG;
    pak_spi.bits.A  =0xC;
    WritePakSpiDAC();
}
//============================================
//Запись кода в выходной регистр ЦАП 0-31
void WriteDac(BYTE nCH,WORD data)
{
    if(nCH>31) return;
    
    pak_spi.data[0]=0;
    pak_spi.data[1]=0;
    pak_spi.data[2]=0;
    
    pak_spi.bits.DB =data;
    pak_spi.bits.A  =nCH;
    pak_spi.bits.REG =3;
    
    WritePakSpiDAC();
}
//==========================================================
//Масштабирование записываемого значения запись в ЦАП     --
void WriteNormalDataDac(BYTE ch, float data)
{
    float res;
    WORD out;
    
    if(ch>(COUNT_DAC_CH-1)) return;

	res=TarrRAM_DAC[ch].k*data+TarrRAM_DAC[ch].ofs;
        
    if(res>MAX_COD_DAC) res=(float)MAX_COD_DAC;
    if(res<MIN_COD_DAC) res=(float)MIN_COD_DAC;
        
    out=(WORD)res;
        
    WriteDac(DAC_CH[ch],out);
	LOAD_DAC_RUN;
}
//===================================================================================
// Подключение канала к АЦП
void SelectCH_ADC(BYTE CH)
{
	BYTE ch;
	if(CH>(COUNT_ADC_CH-1)) return;
	
	if(CH<8)
	{
		EN2=ADC_OFF;
		EN1=ADC_ON;
		ADC_A(CH);
	}else
	{
		ch=CH-8;
		EN1=ADC_OFF;
		EN2=ADC_ON;
		
		ADC_A(ch);
	}
}
//================================
WORD ReadADC()
{
	WORD d;
	SELECT_WORK_SPI(SEL_ADC);
	start_sio();
	d=SDR;
	d=(WORD)(d<<8);
	start_sio();
	d|=SDR;
	stop_sio();
	return d;
}
//================================
int ConvertADCtoINT(WORD d)
{
	int c;
	if((d&0x2000)==0)
	{
		c = d; 
		return c;
	}else
	{
		c=(int)((~d+1)&0x1FFF);
		c*=-1;
		return c;
	}
}
//================================
void StartReadADC()
{
	if (Dac9.StRead==0)
	{
		SelectCH_ADC(0);
		Dac9.StRead=1;
		CONVERT_ADC;
	}
}
//================================
BYTE Reg=0;
void ReadAdcInt()
{
	int cod;//, ch;
	TARIROV_K *pT;
	
	
	if(Reg==0)
	{
		Reg=1;
		CONVERT_ADC;
		return;
	}
	if(Reg==1)
	{
		if(BUSY_ADC == 1) return;
		Reg=0;
		
		cod=ConvertADCtoINT(ReadADC());
		
		#ifndef CASH_PDO_DATA
		__DI();
		#endif
		//ch = ADC_CH[Dac9.StRead];
		pT=&TarrRAM_ADC[Dac9.StRead];
		Dac9.fADC[Dac9.StRead]=cod*pT->k+pT->ofs;
		
		#ifndef CASH_PDO_DATA
		__EI();
		#endif
	
		Dac9.StRead++;
		if(Dac9.StRead>=COUNT_ADC_CH) Dac9.StRead=0;
		SelectCH_ADC(ADC_CH[Dac9.StRead]);
	}
}
//=============================================================================
// Контроль за изменением тарировок, запись во FLASH по команде
void ControlKoeff()
{
//	BYTE i;
	__far WORD   *p1,*p2;
	//WORD d1;//,d2;

	if(Dac9.WriteCoeffFlash==1)
	{
		Dac9.WriteCoeffFlash=0;
		
		p2=(__far WORD *)(ADDR_COEFF);
		p1=(__far WORD *)(&TarrRAM_DAC);
	
		puts("Start write new tarirov for DAC.\n\r#");
		WriteFlashBuff(p1,ADDR_COEFF,COUNT_DAC_CH*4,1);
		
		p1=(__far WORD *)(&TarrRAM_ADC);
		puts("Start write new tarirov for ADC.\n\r#");
		WriteFlashBuff(p1,(ADDR_COEFF+COUNT_DAC_CH*8),COUNT_ADC_CH*4,0);
		
		puts("Successfully write!\n\r#");
	}
}
//=========================================================================
void DriverDAC9(void)
{
	BYTE i;
	float fData;
//	WORD Temp;
	//-------------------------------------
	#ifdef READ_TEMP
	if(Dac9.TimerTem>=TIME_TEM)
	{
		tem(&Temp);
		if((Temp&0x200) != 0) // Отрицательная температура
		{
			Dac9.Temp=((float)Temp-512)/4;	
		}
		else
		{
			Dac9.Temp=(float)Temp/4;	
		}
		Dac9.TimerTem=0;
	}
	#endif
	ControlKoeff();
	//-------------------------------------
	
	#ifndef CASH_PDO_DATA
	__DI();
	#endif
	i=ADDR;	
	Dac9.Info.bits.Addr	=i;
	if(i!=ADDR_NODE)
	{
		setState(Initialisation);
		ADDR_NODE			=ADDR;
	}
	Dac9.Info.bits.Mode	=MODE;
	Dac9.Info.bits.F1	=0;
	Dac9.Info.bits.F2	=0;
	#ifndef CASH_PDO_DATA
	__EI();
	#endif
	//-------------------------------------
	// Проверка записанного значения в ЦАП с помощью АЦП
	#ifndef CASH_PDO_DATA
	__DI();
	#endif
	if(Dac9.TimerErrDac>=80)
	{
		Dac9.TimerErrDac=80;
		for(i=0;i<COUNT_DAC_CH;i++)
    	{
    		if((Dac9.fDAC_Cur[i]>(Dac9.fADC[i]+dERR_DAC_V)) || 
    	   	   (Dac9.fDAC_Cur[i]<(Dac9.fADC[i]-dERR_DAC_V)))
        	{
        		Dac9.wError|=1<<i;
//        		Dac9.fErrADC[i] = Dac9.fADC[i];
       		}else
       		{
       			Dac9.wError&=(WORD)(~(1<<i));
       		}
   		}	
	}
	// Запись в ЦАП по изменениям
	for(i=0;i<COUNT_DAC_CH;i++)
    {
    	if(Dac9.fDAC_New[i] != Dac9.fDAC_Cur[i])
        {
        	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			// Временно введено для Зенита
			//fData = Dac9.fDAC_New[i];
			//if(fData>2.5) fData = 2.5;
			//if(fData<0.0) fData = 0.0;
			//if(Dac9.fDAC_Cur[i] == fData)
			//	continue;
			//Dac9.fDAC_New[i] = fData;
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        	Dac9.TimerErrDac=0;
        	Dac9.fDAC_Cur[i]=Dac9.fDAC_New[i];
            __DI();
	        WriteNormalDataDac(i, Dac9.fDAC_Cur[i]);
       	}
   	}
   	//=================================================================================================
	//=================================================================================================
	// Реле замыкается только после того как выберется мастер в тройке ЦАПов, если мастер ещё не выбран
	if((Dac9.Master == true)||(Dac9.TarrStatus==false))
	{
		DAC_MASTER_SET_ON;
		if(Dac9.SelDAC_CH_cur != Dac9.SelDAC_CH)
		{
			SelectDAC_CH(Dac9.SelDAC_CH);
			Dac9.SelDAC_CH_cur = Dac9.SelDAC_CH;
		}
	}else
	{
		OFF_ALL_DAC;			// отключаем все реле
		Dac9.SelDAC_CH_cur = 0;
	}
	if(Dac9.TarrStatus==true)
		SelectMasterDAC();
	//=================================================================================================
	//=================================================================================================
	__EI();
	//-------------------------------------
	GetPak_Uart(0);
	if(Dac9.SendFlagUart==1)
	{
		Dac9.SendFlagUart=0;

		SendPak.wSelectDAC = Dac9.SelDAC_CH;
		for(i=0;i<COUNT_DAC_CH;i++)
		{
			SendPak.fStateDAC[i]   = Dac9.fDAC_New[i];	
			SendPak.tTarDAC[i].k   = TarrRAM_DAC[i].k;
			SendPak.tTarDAC[i].ofs = TarrRAM_DAC[i].ofs;
		}
		for(i=0;i<COUNT_ADC_CH;i++)
		{
			SendPak.fStateADC[i]   = Dac9.fADC[i];	
//			SendPak.fStateADC[i]   = Dac9.fErrADC[i];	
			SendPak.tTarADC[i].k   = TarrRAM_ADC[i].k;
			SendPak.tTarADC[i].ofs = TarrRAM_ADC[i].ofs;
		}
		Send_Pkt(0,(BYTE *)(&SendPak),124+240,1,1);
	}
}
//========================================================================
// Процедура по выбору мастера из 3х ЦАПов
void SelectMasterDAC(void)
{
	//-------------------------------------------------
	// Проверяем есть ли в данный момент мастер на шине
	//Dac9.wError = DAC_STATUS_NEIGHBOUR;
	//Dac9.wError |= Dac9.Master<<8;
	//Dac9.wError |= DAC_ADD_ADDR<<12;
	
	if(DAC_STATUS_NEIGHBOUR != 3)
	{
		// Мастер на шине уже есть выходим из процедуры определения мастера
		Dac9.Master=false;
		DAC_MASTER_SET_OFF;
		return;
	}
	// Если хотя бы по одному выходу есть проблемы, с выдачей команд, то данный цап не может быть мастером
	if(Dac9.wError!=0)	
	{
		Dac9.Master=false;
		DAC_MASTER_SET_OFF;		
		return;
	}
	//-------------------------------------------------
	// Если нет связи с УСО выходим 
	if((program.TimerCan0>=TIME_OUT_CAN)&&(program.TimerCan1>=TIME_OUT_CAN))
	{
		Dac9.Master=false;
		DAC_MASTER_SET_OFF;
		return;
	}
	//-------------------------------------------------
	// Если блок не проинициализирован УСО выходим 
	if(getState() != Operational)
	{
		Dac9.Master=false;
		DAC_MASTER_SET_OFF;
		return;
	}
	//-------------------------------------------------
	// Если данный блок уже является мастером то выходим из процедуры выявления мастера
	if(Dac9.Master == true)
		return;
	//-----------------------------------------------------------------
	// БЛОК НЕ ЯВЛЯЕТСЯ МАСТЕРОМ, И В ДАННЫЙ МОМЕНТ НА ШИНЕ НЕТ МАСТЕРА
	//-----------------------------------------------------------------
	if(Dac9.StatusMaster == 0)
	{
		DAC_MASTER_SET_ON;
		Dac9.TimerMaster=0;
		Dac9.StatusMaster = 1;
		return;	
	}
	if(Dac9.StatusMaster == 1)
	{
		if(Dac9.TimerMaster<TIME_WAIT_SELECT_MASTER)
		{	// выжидаем реакции соседей
			return;
		}
		//==============================
		// Блок можем стать мастером
		Dac9.Master = true;
		Dac9.StatusMaster = 0;
		return;	
	}
	//-----------------------------------------------------------------
}
//========================================================================

#endif