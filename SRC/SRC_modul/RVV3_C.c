#include "mb90590.h"
#include "RVV3_C.h"
#include "appli.h"
#include "timer.h"

#ifdef PLATA_RVV3C
void 	(*INIT_BLOK)(void)	=InitRVV3C;
void 	(*DRIVER_BLOK)(void)=DriverRVV;
WORD 	(*STATE_BLOCK) 		= &Rvv.Info.word;

CRVV2 Rvv;

WORD TIME_1MS=1/TIMER_RESOLUTION_MS;

			//  0 1 2 3 4 5 6 7	
BYTE BL_SH[17]={0,0,1,0,2,0,0,0,
//				8 9 10111213141516
				3,0,0,0,0,0,0,0,4};
				
void WriteBlock(BYTE n,BYTE data);
BYTE ReadBlock(BYTE n);
void WriteBlockNotSelect(BYTE n,BYTE data);
BYTE ReadBlockNotSelect(BYTE n);

//===========================================================================

void InitRVV3C()
{
	BYTE i;
	
	DDR0=0xC0;
	DDR1=0x00;
	DDR2=0x00;
//	DDR3=0x10;
	DDR4=0x00;
	DDR5=0x0F;
	DDR6=0xFF;
	DDR7=0x01;
	DDR8=0x00;
	DDR9=0x01;
	
	Rvv.newDn	=0xE;
	Rvv.Error	=0;
	Rvv.SelektBl=0;
	//-----------
	RCLK=0;
	UN_SELEKT_BL;
	DATA_0_3_W=0;
	//-----------
	Rvv.Info.bits.Addr	=2;
	ADDR_NODE			=2;
	LEDR=1;
	LEDG=1;
//--------------------------------------------	
	//ENIR = 0x04;	// Disable Interrupts
	//ELVR = 0x30;	// Set Level Detect
	//EIRR = 0x00;	// Clear Interrupt bits
	//ENIR = 0x04;	// Enable Ext Int 0 and 1
//--------------------------------------------
	for(i=0;i<5;i++)
	{
		SELEKT_BL(i);
		WriteBlockNotSelect(i,0);
		ReadBlockNotSelect(i);
	}
	UN_SELEKT_BL;
}
//===================================================================================
void WriteBlockNotSelect(BYTE n,BYTE data)
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
    UN_SELEKT_BL;
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
	UN_SELEKT_BL;
	return data;
}
//===================================================================================
BYTE ReadBlockNotSelect(BYTE n)
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
void SelektCH_Input(BYTE Nch)
{
	Rvv.SelektBl=0;
	if(Nch==0)
	{
		UN_SELEKT_BL;
	}else
	{
		if(Nch>45) return;
		if(Nch<9)			//1 blok
		{
			//if ((Rvv.Error&0x1)!=0)return;
			SELEKT_BL(0);
			Nch-=1;
			Rvv.SelektBl=1;
		}
		if(Nch>8 && Nch<17)	//2 blok
		{
			//if ((Rvv.Error&0x2)!=0)return;
			SELEKT_BL(1);
			Nch-=9;
			Rvv.SelektBl=2;
		}
		if(Nch>16 && Nch<25)//3 blok	
		{
			//if ((Rvv.Error&0x4)!=0)return;
			SELEKT_BL(2);
			Nch-=17;
			Rvv.SelektBl=4;
		}
		if(Nch>24 && Nch<33)//4 blok	
		{
			//if ((Rvv.Error&0x8)!=0)return;
			SELEKT_BL(3);
			Nch-=25;
			Rvv.SelektBl=8;
		}
		if(Nch>32 && Nch<41)//5 blok
		{
			//if ((Rvv.Error&0x10)!=0)return;
			SELEKT_BL(4);
			Nch-=33;
			Rvv.SelektBl=0x10;
		}
		
		if(Nch==41)
		{
			SELEKT_BL(0);
			Nch=8;
			Rvv.SelektBl=1;
		}
		if(Nch==42)
		{
			SELEKT_BL(1);
			Nch=8;
			Rvv.SelektBl=2;
		}
		if(Nch==43)
		{
			SELEKT_BL(2);
			Nch=8;
			Rvv.SelektBl=4;
		}
		if(Nch==44)
		{
			SELEKT_BL(3);
			Nch=8;
			Rvv.SelektBl=8;
		}
		if(Nch==45)
		{
			SELEKT_BL(4);
			Nch=8;
			Rvv.SelektBl=0x10;
		}
		//if(Nch<8)
		Rvv.SetData=Nch;
		{
			selWRITE_DATA;
			DATA_0_3_W=Nch&0xF;
			RW_R=tWRITE;
			RCLK=1;
			RCLK=0;
		}
		Rvv.Timer=0;
		while(Rvv.Timer<TIME_1MS) clrwdt;
		ReadBlockNotSelect(Nch);
	}
}
//===================================================================================
void SetErrorBlok(BYTE Num)
{
	if(Num<5)
	{
		//WriteBlock(Num,8);
		WriteBlockNotSelect(Num,8);
		ReadBlockNotSelect(Num);
	}
}
//===================================================================================
void ControlSetCh()
{
	BYTE data;
	if(Rvv.SelektBl==0) return;
	data=ReadBlockNotSelect(BL_SH[Rvv.SelektBl]);
	if (Rvv.SetData!=data)
	{
		if((Rvv.Error&(Rvv.SelektBl<<1))==0)
		{
			Rvv.Error|=(Rvv.SelektBl<<1);
			SetErrorBlok(BL_SH[Rvv.SelektBl]);
		}
	}else
		Rvv.Error&=(~(Rvv.SelektBl<<1));
}
//===================================================================================
void DriverRVV()
{
	__DI();
	Rvv.Error&=0x7F;
	Rvv.Error|=RIN2<<7;
	__EI();
	if(Rvv.newDn!=Rvv.Dn)
	{
		Rvv.Dn=Rvv.newDn;
		WriteBlock(5,Rvv.Dn);
		WriteBlock(6,Rvv.Dn>>4);
		if((ReadBlock(5)!=(Rvv.Dn&0xF)) && ((ReadBlock(6)!=((Rvv.Dn>>4)&0xF))))
		{
			Rvv.Error|=0x1;
			WriteBlock(6,0x8|(Rvv.Dn>>4));
		}
		else Rvv.Error&=0xFE;
	}
	
	SelektCH_Input(Rvv.nCH);
	ControlSetCh();
	
	if(Rvv.SelektBl!=0)
	//	if (Rvv.Write!=Rvv.WriteNew)
	{
//		WriteBlockNotSelect(Rvv.nCH,Rvv.WriteNew);
		Rvv.Read=ReadBlockNotSelect(BL_SH[Rvv.SelektBl]);
//		Rvv.Write=Rvv.WriteNew;
	}
	
	//__EI();
}


#endif

