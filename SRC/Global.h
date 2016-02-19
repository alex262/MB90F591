//--------------------------------
#ifndef __GLOBAL__
#define __GLOBAL__
#include "stdlib.h"
#include "mb90590.h"
//--------------------------------
//����������� ������ TX PDO ��� 
//��������� �������� ��� ������� �������
#define	CASH_PDO_DATA
//--------------------------------
//�������� ������ �� ��������� CanOpen
#define CAN_OPEN_ENABLE
//--------------------------------
//�������� ���� ��  ���������  ����������
//#define	PLATA_NDD	//19 16 18 17
//#define	PLATA_FSU	//fsu 14 20 16 18 26
//#define	PLATA_ADC
//#define	PLATA_AVV2C
//#define	PLATA_KCU 
//#define	PLATA_RVV3C
//#define	PLATA_FSU15_C	//21
//#define	PLATA_FSU19		//23
//#define	PLATA_FSU22
//#define	PLATA_DAC9
//#define 	PLATA_FSU22C
//#define	PLATA_NDD20P
//#define	PLATA_RVV5C
//#define	PLATA_NDD20P1
//#define	PLATA_NDD20
//#define	PLATA_TEST
//#define	PLATA_RVV6
#define	PLATA_NDD21
//#define	PLATA_DAC10
//#define	PLATA_ADC8
//#define PLATA_FSU28

//================================
// �  ������ ����   ��������� 
// ������ ���� header
#ifdef	PLATA_NDD
	#define	INCLUDE_H	"NDD16C.h"
#endif
#ifdef	PLATA_FSU
	#define	INCLUDE_H	"fsu.h"
#endif
#ifdef	PLATA_ADC
	//--------------------------------
	#define BUFFER_LEN_UART		280		//������ ������� �����
	#define Max_In_Pak 			270		//���c�������  ����� ��������� ������
	#define COUNT_UART_BUF		1		// ��������� ������
	#define	INCLUDE_H	"adc5_c.h"
#endif
#ifdef	PLATA_AVV2C
	#define	INCLUDE_H	"avv2_c.h"
#endif
#ifdef	PLATA_KCU
	#define	INCLUDE_H	"kcu1_c.h"
#endif
#ifdef	PLATA_RVV3C
	#define	INCLUDE_H	"rvv3_c.h"
#endif
#ifdef	PLATA_FSU15_C
	#define	INCLUDE_H	"fsu15c.h"
#endif
#ifdef	PLATA_FSU19
	#define	INCLUDE_H	"fsu19.h"
#endif
#ifdef	PLATA_FSU22
	#define	INCLUDE_H	"fsu22.h"
#endif
#ifdef	PLATA_DAC9
	//--------------------------------
	#define BUFFER_LEN_UART		265		//������ ������� �����
	#define Max_In_Pak 			254		//���c�������  ����� ��������� ������
	#define COUNT_UART_BUF		1		// ��������� ������
	#define	INCLUDE_H	"dac9.h"
#endif
#ifdef	PLATA_FSU22C
	#define	INCLUDE_H	"FSU22C.h"
#endif
#ifdef	PLATA_NDD20P
	#define	INCLUDE_H	"NDD20P.h"
#endif
#ifdef	PLATA_RVV5C
	#define	INCLUDE_H	"RVV5_C.h"
#endif
#ifdef	PLATA_NDD20P1
	#define	INCLUDE_H	"NDD20P1.h"
#endif
#ifdef	PLATA_NDD20
	#define	INCLUDE_H	"NDD20.h"
#endif
#ifdef	PLATA_TEST
	#define	INCLUDE_H	"test.h"
#endif
#ifdef	PLATA_RVV6
	#define	INCLUDE_H	"RVV6.h"
#endif
#ifdef	PLATA_NDD21
	#define	INCLUDE_H	"NDD21.h"
#endif
#ifdef	PLATA_DAC10
	#define	INCLUDE_H	"dac10.h"
	//--------------------------------
	#define BUFFER_LEN_UART		120				//������ ������� �����
	#define Max_In_Pak 			110				//���c�������  ����� ��������� ������
	#define COUNT_UART_BUF		1				// ��������� ������
#endif
#ifdef	PLATA_ADC8
	#define	INCLUDE_H	"ADC8.h"
#endif
#ifdef	PLATA_FSU28
	#define	INCLUDE_H	"FSU28.h"
#endif

//--------------------------------
#ifndef	BUFFER_LEN_UART
	#define BUFFER_LEN_UART		120				//������ ������� �����
#endif
#ifndef	Max_In_Pak
	#define Max_In_Pak 			110				//���c�������  ����� ��������� ������
#endif
#ifndef	COUNT_UART_BUF
	#define COUNT_UART_BUF		1				// ��������� ������
#endif

//--------------------------------
// ��������
#ifdef	PLATA_FSU
	#define SPEED_CAN_0	CAN_1000
	#define SPEED_CAN_1	CAN_1000
#endif
//--------------------------------

#ifdef	PLATA_TEST
	#define SPEED_CAN_0	CAN_1000
	#define SPEED_CAN_1	CAN_1000
#endif

#ifdef PLATA_FSU19
	#define SPEED_CAN_0	0
	#define SPEED_CAN_1	CAN_1000
#endif
#ifdef PLATA_AVV2C
	#define SPEED_CAN_0	CAN_1000
	#define SPEED_CAN_1	0
#endif
#ifdef PLATA_RVV3C
	#define SPEED_CAN_0	CAN_1000
	#define SPEED_CAN_1	0
#endif
#ifdef PLATA_RVV5C
	#define SPEED_CAN_0	CAN_1000
	#define SPEED_CAN_1	0
#endif
#ifdef PLATA_RVV6
	#define SPEED_CAN_0	CAN_1000
	#define SPEED_CAN_1	0
#endif
//---------------------------------------
#ifndef SPEED_CAN_0
	#define	SPEED_CAN_0	CAN_1000
#endif
#ifndef SPEED_CAN_1
	#define	SPEED_CAN_1	CAN_1000
#endif
//--------------------------------
typedef unsigned char		BYTE;
typedef unsigned short		WORD;
typedef unsigned long		DWORD;
//--------------------------------
#define TRUE	1
#define FALSE	0
#define true	1
#define false	0
//--------------------------------
// System Timer
// Period timer 2 uc
#define		RELOAD_VALUE_0			500
//#define		RELOAD_VALUE_1			5000

#define  	TIMER_RESOLUTION_MS		1
#define 	TIMER_RESOLUTION_US 	1000
//--------------------------------
#define BLINK_LED		(100/TIMER_RESOLUTION_MS)
#define TIME_OUT_CAN	(2000/TIMER_RESOLUTION_MS)	

//--------------------------------
//	�������� 
#define	ind_WORK		0		//!���� �������� ���������, ��� ������ ��  ���
//#define	ind_PWRAT		1		//���� ��� ���� ����� ������  
#define	ind_COM1		2		// ��������  ��������  �� ������ ������  � ��
#define	ind_ERROR		3		//������,  ���������  ��  ����������� ���� ������, ���� ��  �  ���������������� �����   ������������ ���. ���������� 
#define	ind_COMA		4		//! ��������  ��������  �� � �� �������  � ��
#define	ind_TEST		5		//���� ������� �� ������: �� ���������, ������� �� �����
#define	ind_FATERR		6		//����������� ��� �������  ������, �� ���� ��  �  ����������� ������ �����.
#define	ind_RESET		7		//���� � ������ ���������������  

#define	Err_CAN1		1		//
#define	Err_CAN2		2		//

//-------------------------------------------
//STATE BLOCK
#define	ST_Addr	0x001F	
#define	ST_Mode	0x01E0
#define	ST_F1	0x0200
#define	ST_F2	0x0400
#define	ST_Can1	0x0800
#define	ST_Can2	0x1000
#define	ST_Pwr1	0x2000
#define	ST_Pwr2	0x4000
#define	ST_Res	0x8000


// Interface I2C for temperature sensor
#ifdef PLATA_DAC9
	#define SDA_0 DDR5_D57=1;DDR5_D56=1;	// Set SDA line active (0, output)
	#define SDA_1 DDR5_D57=0;DDR5_D56=1;	// Set SDA line passive(1, input)
	#define SCL_0 PDR5_P57=0;PDR5_P56=0;	// Set SCL line active (0, output)
	#define SCL_1 PDR5_P57=0;PDR5_P56=1;	// Set SCL line active (1, output)
	#define I2C_SDA	PDR5_P57
	#define I2C_SCL	PDR5_P56
#else
	#define SDA_0 DDR5_D53=1;DDR5_D54=1;	// Set SDA line active (0, output)
	#define SDA_1 DDR5_D53=0;DDR5_D54=1;	// Set SDA line passive(1, input)
	#define SCL_0 PDR5_P53=0;PDR5_P54=0;	// Set SCL line active (0, output)
	#define SCL_1 PDR5_P53=0;PDR5_P54=1;	// Set SCL line active (1, output)
	#define I2C_SDA	PDR5_P53
	#define I2C_SCL	PDR5_P54
#endif


//================================

#define SETBIT(ADDRESS,BIT) 	((ADDRESS) |= (1<<(BIT)))	//Set BIT in ADDRESS 
#define CLEARBIT(ADDRESS,BIT)  	((ADDRESS) &= ~(1<<(BIT)))	//Clear BIT in ADDRESS
#define digit(DATA,BIT)			((DATA&(1<<BIT)) ? 1 : 0)	//������  �� �������� BIT -�� ���� �� � �� �� DATA
#define MAX(a,b)				(a>b ? a : b)

#define VER_PROT 		0x0030							//��� �  ��������� ��

#define clrwdt 			WDTC_WTE=0			//���c��� WatchDog
#define clr_wdt 		program.watch_dog=0	//���c��� ������������ WatchDog
#define RESET 			LPMCR_RST=0			//������������ ����������������

#define RST_UNKNOWN		0x0			// ����� ��� ������� ������������
#define RST_POWERON		0x1			//������� �������
#define RST_STANDBY		0x2			//���������� ���� �����
#define RST_WATCHDOG	0x3			//�������� ��������  ��������
#define RST_RSTPIN		0x4			//�� �������� � �������
#define RST_RSTBIT		0x5			//RST bit

#define SPI_MISO 		PDR4_P45
#define SPI_SCK  		PDR4_P46
#define SPI_MOSI 		PDR4_P47

#define READY	0x4			//����� ���������������  
//#define INIT	0x1
//#define TEST	0x2
//#define PAUSE	0x3
#define ERROR	0x0			// ��� - �����������
	
typedef struct
{
	DWORD 	ms1counter;				//���� �������   ������
	DWORD 	current_time;			//������� ����  �  �������
	BYTE 	Device_ReStart;			//������� �������� �� ����������������
	BYTE 	watch_dog;
	BYTE	REGIM;
	WORD	Error;
	WORD	TimerCan0;
	WORD	TimerCan1;
	BYTE	ErrorCAN;
	WORD	COUNT;
	
	unsigned char Pack_IN_[COUNT_UART_BUF][BUFFER_LEN_UART];	//����  �  ����� �� UART1
	unsigned int  N[COUNT_UART_BUF];						// ���� ����������  ������ � ������ UART1
}TProgram;

//------------------------------------------------------------------
void SetError(BYTE Error);
void ClearError(BYTE Error);
BYTE GetError();
void Indicate(WORD *pCount, WORD BLINK);

extern TProgram program;

#endif
