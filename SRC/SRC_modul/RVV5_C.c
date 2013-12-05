#include "mb90590.h"
#include "RVV5_C.h"
#include "appli.h"
#include "timer.h"

#ifdef PLATA_RVV5C

void 	(*INIT_BLOK)(void)	=InitRVV5C;
void 	(*DRIVER_BLOK)(void)=DriverRVV;
WORD 	(*STATE_BLOCK) 		= &Rvv.Info.word;

CRVV5 Rvv;

WORD TIME_1MS=1/TIMER_RESOLUTION_MS;

			//  0 1 2 3 4 5 6 7	
BYTE BL_SH[17]={0,0,1,0,2,0,0,0,
//				8 9 10111213141516
				3,0,0,0,0,0,0,0,4};
				
void WriteBlock(BYTE n,BYTE data);
BYTE ReadBlock(BYTE n);
void WriteBlockNotSelect(BYTE data);
BYTE ReadBlockNotSelect();

//===========================================================================
void UN_SELEKT_BL()
{
	PDR6=PDR6|0x7F;
	PDR8=0x0F;
	Rvv.Sel7 = 0;
}
void SELEKT_BL_7()
{
	PDR6_P66 = 0;
	Rvv.Sel7 = 1;
}
void UNSELEKT_BL_7()
{
	PDR6_P66 = 1;
	Rvv.Sel7 = 0;
}
void SELEKT_BL(BYTE N)
{
	if(N>COUNT_BLOCK)
		return;
	UNSELEKT_BL_7();
	if(N<7)
	{
		PDR8=0x0F;
		PDR6=(~(1<<N))&0x7F;
		return;
	}
	if(N>6)
	{
		PDR6=PDR6|0x7F;
		PDR8=(~(1<<(N-7)))&0xF;
	}
}
//===========================================================================

void InitRVV5C()
{
//	BYTE i;
	
	//-----------
	RCLK=0;
	UN_SELEKT_BL();
	DATA_0_3_W=0;
	RW_R=tREAD;
	//-----------
	
	DDR0=0xC0;
	DDR1=0x00;
	DDR2=0x00;
//	DDR3=0x10;
	DDR4=0x00;
	DDR5=0x0F;
	DDR6=0xFF;
	DDR7=0x01;
	DDR8=0x0f;
	DDR9=0x01;
	
	Rvv.newDn	=0xE;
	Rvv.Error	=0;
	Rvv.SelektBl=0;
	
	Rvv.Info.bits.Addr	=2;
	ADDR_NODE			=2;
	LEDR=1;
	LEDG=1;
//--------------------------------------------
	//for(i=0;i<7;i++)
	//{
	//	SELEKT_BL(i);
		//WriteBlockNotSelect(0);
	//	ReadBlockNotSelect();
	//}
	UN_SELEKT_BL();
}
//===================================================================================
void WriteBlockNotSelect(BYTE data)
{
	//SELEKT_BL(n);
	selWRITE_DATA;
	DATA_0_3_W=data&0xF;
	RW_R=tWRITE;
	RCLK=1;
	RCLK=0;
	Rvv.Timer=0;
	while(Rvv.Timer<TIME_1MS)clrwdt;
}
void WriteBlock(BYTE n,BYTE data)
{
	SELEKT_BL(n);
	selWRITE_DATA;
	DATA_0_3_W=data&0xF;
	RW_R=tWRITE;
	RCLK=1;
	RCLK=0;
    UN_SELEKT_BL();
    Rvv.Timer=0;
	while(Rvv.Timer<TIME_1MS)clrwdt;
}
//===================================================================================
BYTE ReadBlock(BYTE n)
{
	BYTE data;
	SELEKT_BL(n);
	selREAD_DATA;
	RW_R=tREAD;
	RCLK=1;
	RCLK=0;
	data=DATA_0_3_R;
	UN_SELEKT_BL();
	return data;
}
//===================================================================================
BYTE ReadBlockNotSelect()
{
	//SELEKT_BL(n);
	selREAD_DATA;
	RW_R=tREAD;
	RCLK=1;
	RCLK=0;
	return DATA_0_3_R;
}
//===================================================================================
void SelektCH(BYTE nBl,BYTE nCH)
{
	SELEKT_BL(nBl);
	selWRITE_DATA;
	DATA_0_3_W=nCH&0xF;
	RW_R=tWRITE;
	RCLK=1;
	RCLK=0;
}
//===================================================================================
void SelektCH_Input()
{
	//if(Rvv.NewCH_select.word == Rvv.CH_select.word)
	//	return;
	if(Rvv.Sel7 != 0) return;
	
	Rvv.CH_select.word = Rvv.NewCH_select.word; 
	
	
	if(Rvv.CH_select.bits.Nb == 0)
	{
		UN_SELEKT_BL();
		Rvv.SelektBl=0;
	}else
	{
		// =======================================
		// вход с 1 - 48 общий 3-10
		if(Rvv.CH_select.bits.Nb<8)
		{
			Rvv.SelektBl=Rvv.CH_select.bits.Nb;
	
			SELEKT_BL(Rvv.CH_select.bits.Nb-1);
		
			if(Rvv.CH_select.bits.Nch == 0)
				Rvv.SetData=8;
			else
				Rvv.SetData=Rvv.CH_select.bits.Nch-1;
			selWRITE_DATA;
			DATA_0_3_W=Rvv.SetData&0xF;
			RW_R=tWRITE;
			RCLK=1;
			RCLK=0;
			Rvv.Timer=0;
			while(Rvv.Timer<TIME_1MS) clrwdt;
			ReadBlockNotSelect();
			return;
		}
		// =======================================
		// РКС2   
		if(Rvv.CH_select.bits.Nb == 8)
		{
			//if(Rvv.curRKS2 == (Rvv.CH_select.bits.Nch&0xFF))
			//	return;
			Rvv.curRKS2 = Rvv.CH_select.bits.Nch&0xFF;	
			SELEKT_BL(Rvv.CH_select.bits.Nb-1);
			
			Rvv.SelektBl=Rvv.CH_select.bits.Nb;
			Rvv.SetData=Rvv.CH_select.bits.Nch;
			selWRITE_DATA;
			DATA_0_3_W=Rvv.CH_select.bits.Nch&0xF;
			RW_R=tWRITE;
			RCLK=1;
			RCLK=0;
			Rvv.Timer=0;
			while(Rvv.Timer<TIME_1MS) clrwdt;
			ReadBlockNotSelect();
		}
	}
}
//===================================================================================
void SetErrorBlok()
{
	WriteBlockNotSelect(8);
	ReadBlockNotSelect();
}
//===================================================================================
void ControlSetCh()
{
	BYTE data;
	
	if(Rvv.SelektBl==0) return;
	if(Rvv.Sel7 != 0) return;
	data=ReadBlockNotSelect(Rvv.SelektBl-1);
	Rvv.ReadData = data;
	if (Rvv.SetData!=data)
	{
		Rvv.Error|=1<<(Rvv.SelektBl+1);
		if(Rvv.SelektBl != 8)
			SetErrorBlok();
	}else
		Rvv.Error&=~(1<<(Rvv.SelektBl+1));
}
//===================================================================================
void DriverRVV()
{
	__DI();
	Rvv.Error&=~(1<<1);	//Комплектность 
	Rvv.Error|=RIN2<<1;
	__EI();
	
	if(Rvv.NewSel7 != Rvv.Sel7)
	{
		Rvv.Sel7 = Rvv.NewSel7;
		if(Rvv.Sel7 == 0)
			UNSELEKT_BL_7();
		else
			SELEKT_BL_7();
	}
	//============================================================================
	// DN
	if(Rvv.newDn!=Rvv.Dn)
	{
		Rvv.Dn=Rvv.newDn;
		WriteBlock(9,Rvv.Dn);
		WriteBlock(10,Rvv.Dn>>4);
		if((ReadBlock(9)!=(Rvv.Dn&0xF)) && ((ReadBlock(10)!=((Rvv.Dn>>4)&0xF))))
		{
			Rvv.Error|=0x1;
			WriteBlock(10,0x8|(Rvv.Dn>>4));
		}
		else Rvv.Error&=0xFFFE;
	}
	//============================================================================
	// Выбор конкретного входа  
	SelektCH_Input();
	ControlSetCh();
	//============================================================================
//	if(Rvv.SelektBl!=0)
//	{
//		Rvv.Read=ReadBlockNotSelect(BL_SH[Rvv.SelektBl]);
//	}
	//__EI();
}


#endif

