#include "mb90590.h"
#include "KCU1_C.h"
#include "slugebn.h"
#include "timer.h"
#include "appli.h"

#ifdef PLATA_KCU
void 	(*INIT_BLOK)(void)	=InitKCU1C;
void 	(*DRIVER_BLOK)(void)=DriverKCU;

CKCU Kcu;

WORD (*STATE_BLOCK) = &Kcu.Info.word;

BYTE Start=0;

void InitKCU1C()
{
	DDR0=0x00;
	DDR1=0x23;
	DDR2=0x00;
//	DDR3=0x10;
	DDR4=0x00;
	DDR5=0x00;
	DDR6=0x3F;
	DDR7=0x00;
	DDR8=0x00;
	DDR9=0x01;
	
	//-----------
	STRB1=1;		
	STRB2=1;		
	STRB3=1;		
	STRB4=1;	
	D_STRB1=0;
	D_STRB2=0;
	D_STRB3=0;
	D_STRB4=0;
	
	TEST1=1;		
	TEST2=1;	
	D_TEST1=0;
	D_TEST2=0;		
	//-----------
	ADDR_NODE			=ADDR;
	Kcu.Info.bits.Addr	=ADDR;
	Kcu.Regim			=REG_CIR_CONTROL;
	
	LEDR=1;
	LEDG=1;
//--------------------------------------------	
	//ENIR = 0x04;	// Disable Interrupts
	//ELVR = 0x30;	// Set Level Detect
	//EIRR = 0x00;	// Clear Interrupt bits
	//ENIR = 0x04;	// Enable Ext Int 0 and 1
//--------------------------------------------
}
//====================================================================
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
void wait1_5mks()
{
	DWORD i=40;
	while(i!=0)	i--;
}
void wait_ms(WORD ms)
{
	WORD t=ms/TIMER_RESOLUTION_MS;
	Kcu.Timer=0;
	while(Kcu.Timer <= t) clrwdt;
}
void ControlCir()
{
	BYTE d;
	BYTE tmp;
	
	D_TEST1=0;
	D_TEST2=0;
	TEST1=1;
	TEST2=1;
	//================
	wait_ms(1);
	STRB1=0;
	D_STRB1=1;
	wait1_5mks();
	d=K1_6;
	Kcu.CirControlTemp[0]= d&0x3f;
	//D_STRB1=0;
	STRB1=1;
	//-----------------
	wait_ms(1);
	STRB2=0;
	D_STRB2=1;
	wait1_5mks();
	d=K1_6;
	tmp = (d<<6)&0xC0;
	Kcu.CirControlTemp[0]|=tmp;
	Kcu.CirControlTemp[1]=(d>>2)&0x0F;
	//D_STRB2=0;
	STRB2=1;
	//-----------------
	wait_ms(1);
	STRB3=0;
	D_STRB3=1;
	wait1_5mks();
	d=K1_6;
	tmp = (d<<4)&0xF0;
	Kcu.CirControlTemp[1]|= tmp;
	Kcu.CirControlTemp[2]=(d>>4)&0x03;
	//D_STRB3=0;
	STRB3=1;
	//-----------------
	wait_ms(1);
	STRB4=0;
	D_STRB4=1;
	wait1_5mks();
	d=K1_6;
	tmp = (d<<2)&0xFC;
	Kcu.CirControlTemp[2]|= tmp;
	//D_STRB4=0;
	STRB4=1;
	//-----------------
	__DI();
	Kcu.CirControl[0]=Kcu.CirControlTemp[0];
	Kcu.CirControl[1]=Kcu.CirControlTemp[1];
	Kcu.CirControl[2]=Kcu.CirControlTemp[2];
	__EI();
}
//====================================================================
BYTE Convert_8(BYTE n)
{
	BYTE i,s=0;
	for(i=0;i<8;i++)
	{
		s|=digit(n,i)<<(7-i);
	}
	return s;
}
void ControlRelGroup()
{
	BYTE d[3];
	//===============
	D_TEST1=1;
	TEST1=0;
	
	Kcu.Info.bits.Pwr1=~TEST_TR1;
	if(Start==0) wait_ms(1000);
	
	D_TEST2=1;
	TEST2=0;
	Start=0xFF;
	
	Kcu.Info.bits.Pwr2=~TEST_TR2;
	
	d[0]=TST8_1;
	d[1]=TST16_9;
	d[2]=TST24_17;
	
	d[0]=Convert_8(d[0]);
	d[1]=Convert_8(d[1]);
	d[2]=Convert_8(d[2]);

	__DI();
	Kcu.RelGroup[0]=d[0];
	Kcu.RelGroup[1]=d[1];
	Kcu.RelGroup[2]=d[2];
	__EI();
}
//====================================================================
void DriverKCU()
{
	BYTE i;
	__DI();
	i=ADDR;	
	Kcu.Info.bits.Addr	=i;
	if(i!=ADDR_NODE)
	{
		setState(Initialisation);
		ADDR_NODE			=ADDR;
	}
	Kcu.Info.bits.Mode	=MODE;
	Kcu.Info.bits.F1	=PG_F1;
	Kcu.Info.bits.F2	=PG_F2;
	__EI();
	
//	if(Kcu.Info.bits.F2==1 || Kcu.Info.bits.F1==1)
//		SetError(ind_PWRAT);
//	else
//		ClearError(ind_PWRAT);
	
	if(Kcu.Regim==REG_CIR_CONTROL)
	{
		ControlCir();
		Start=0;
	}
	if(Kcu.Regim==REG_REL_GR_CONTROL)	
	{
		ControlRelGroup();
	}
}
//====================================================================

#endif;