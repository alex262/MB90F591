#include "mb90590.h"

//---------------------------------------------------------------------------------------------------------
// Инициализация системных регистров (установка значений по умолчанию)
void pwreset()
{
//	PDR0 = 0x00;
//	PDR1 = 0xF0;
//	PDR2 = 0x00;
	PDR3 = 0x00;
//	PDR4 = 0x00;
//	PDR5 = 0x00;
//	PDR6 = 0x0F;
//	PDR7 = 0x08;
//	PDR8 = 0x00;
//	PDR9 = 0x3F;

//	DDR0=0xC0;
//	DDR1=0xEF;
//	DDR2=0x4F;
	DDR3=0x1A;
//	DDR4=0xC6;
//	DDR5=0xFF;
//	DDR6=0xFF;
//	DDR7=0xFB;
//	DDR8=0x80;
//	DDR9=0x21;

	ADER=0;
	UMC0 = 0x04; 		// Serial Mode Control Register 
	USR0 = 0x10; 		// Status Register
	URD0 = 0x00; 		// Rate and Data Register
	
	UMC1 = 0x04; 		// Serial Mode Control Register 
	USR1 = 0x10; 		// Status Register
	URD1 = 0x00; 		// Rate and Data Register
	
	UMC2 = 0x04; 		// Serial Mode Control Register 
	USR2 = 0x10; 		// Status Register
	URD2 = 0x00; 		// Rate and Data Register

	CDCR = 0x08;
	SMCS  = 0x0200; 		// Serial Mode Control
	//SMCS  = 0x02;		// Serial Mode Control
	SES   = 0x00;		// Edge Selector
	ENIR  = 0x00; 		// External Interrupt Enable
	ELVR  = 0x0000; 		// External Interrupt Level
	//ELVR  = 0x00; 		// External Interrupt Level
	ADCS0 = 0x00; 		// A/D Control Status 0
	ADCS1 = 0x00; 		// A/D Control Status 1
	ADCR1 = 0x08; 		// A/D Data 1
	
	PPGC0 = 0x01; 		// PPG0 operation mode control register
	PPGC1 = 0x01; 		// PPG1 operation mode control register
	PPG01 = 0x00; 		// PPG0 and PPG1 clock select register
	PPGC2 = 0x01; 		// PPG2 operation mode control register
	PPGC3 = 0x01; 		// PPG3 operation mode control register
	PPG23 = 0x00; 		// PPG2 and PPG3 clock select register
	PPGC4 = 0x01; 		// PPG4 operation mode control register
	PPGC5 = 0x01; 		// PPG5 operation mode control register
	PPG45 = 0x00; 		// PPG4 and PPG5 clock select register
	PPGC6 = 0x01; 		// PPG6 operation mode control register
	PPGC7 = 0x01; 		// PPG7 operation mode control register
	PPG67 = 0x00; 		// PPG6 and PPG7 clock select register
	PPGC8 = 0x01; 		// PPG8 operation mode control register
	PPGC9 = 0x01; 		// PPG9 operation mode control register
	PPG89 = 0x00; 		// PPG8 and PPG9 clock select register
	PPGCA = 0x01; 		// PPGA operation mode control register
	PPGCB = 0x01; 		// PPGB operation mode control register
	PPGAB = 0x00; 		// PPGA and PPGB clock select register
	
	TMCSR0 = 0x0000;		// Timer Control Status 0
	
	TMCSR1 = 0x0000;		// Timer Control Status 1
	
	OCS0 = 0x00;		// Output Compare Control Status 0
	OCS1 = 0x00;		// Output Compare Control Status 1
	OCS2 = 0x00;		// Output Compare Control Status 2
	OCS3 = 0x00;		// Output Compare Control Status 3
	OCS4 = 0x00;		// Output Compare Control Status 4
	OCS5 = 0x00;		// Output Compare Control Status 5
	
	ICS01 = 0x00;		// Input Capture Control Status 0/1
	ICS23 = 0x00;		// Input Capture Control Status 2/3
	ICS45 = 0x00;
	
	PWC0 = 0x00;		// PWM Control 0
	PWC1 = 0x00;		// PWM Control 1
	PWC2 = 0x00;		// PWM Control 2
	PWC3 = 0x00;		// PWM Control 3
	
	TCDT = 0x00;		// Timer Data
	TCCS = 0x00;		// Timer Control
	ROMM  = 0x01;		// ROM Mirror
	PWS10 = 0x00;		// PWM1 Select 0
	PWS20 = 0x00;		// PWM2 Select 0
	PWS11 = 0x00;		// PWM1 Select 1
	PWS21 = 0x00;		// PWM2 Select 1
	PWS12 = 0x00;		// PWM1 Select 2
	PWS22 = 0x00;		// PWM2 Select 2
	PWS13 = 0x00;		// PWM1 Select 3
	PWS23 = 0x00;		// PWM2 Select 3
	PACSR = 0x00;		// ROM Correction Control Status
	DIRR = 0x00;		// Delayed Interrupt/release
	LPMCR = 0x18;		// Low-power Mode
	//WDTC = 0x07;		// Watchdog Control
	TBTC = 0x84;		// Time Base Timer Control
	
	ICR00 = 0x07;		// Interrupt control register 00
	ICR01 = 0x07;		// Interrupt control register 01
	ICR02 = 0x07;		// Interrupt control register 02
	ICR03 = 0x07;		// Interrupt control register 03
	ICR04 = 0x07;		// Interrupt control register 04
	ICR05 = 0x07;		// Interrupt control register 05
	ICR06 = 0x07;		// Interrupt control register 06
	ICR07 = 0x07;		// Interrupt control register 07
	ICR08 = 0x07;		// Interrupt control register 08
	ICR09 = 0x07;		// Interrupt control register 09
	ICR10 = 0x07;		// Interrupt control register 10
	ICR11 = 0x07;		// Interrupt control register 11
	ICR12 = 0x07;		// Interrupt control register 12
	ICR13 = 0x07;		// Interrupt control register 13
	ICR14 = 0x07;		// Interrupt control register 14
	ICR15 = 0x07;		// Interrupt control register 15
}
