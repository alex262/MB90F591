#ifndef _KVV__
#define __KVV__

#include "appli.h"
#include "global.h"

#ifdef PLATA_KVV

#define NAME_MODUL "KVVC"
#define DEVICE_TYPE 7



extern void (*INIT_BLOK)(void);
extern void (*DRIVER_BLOK)(void);

//NDD16
#define TST2	PDR6_P60
#define TST1	PDR6_P63
#define PWR1	PDR6_P62
#define PWR2	PDR6_P61

#define G1		PDR6_P66
#define G2		PDR6_P65
//end NDD16

#define LEDR 	PDR1_P11
#define LEDG 	PDR1_P10
#define E1 	PDR9_P92
#define E2 	PDR9_P95
#define RESIRQ 	PDR9_P90

#define MODE	((PDR0>>4)& 0xF) //Состояние переключателей
#define ADDR	(PDR2&0x1F)		

#define WRP5 {if((Kvv.DD & j) == 0) PDR5= 4; else {if ((Kvv.M24 & j) != 0)\
	PDR5=1; else {if ((Kvv.M5 & j) != 0) PDR5= 2; else PDR5= 3;}}}//M5==1

#define WRP78 if (i < 8){PDR8=~k; __wait_nop();PDR8=0xff;} else\
  {PDR7=~k;__wait_nop();PDR7=0xff;PDR5=0;}
	

#define  READC	ADCS1_STRT =1;PDR5_P53=0; while(ADCS1_INT==0)\
	{__wait_nop();}PDR5_P53=1; ADCS1_INT =0;

#define MAX24 0x3ff
#define MAX5 0xff
#define MIN24 0x2ff
#define MIN5 0xf0
typedef union
{
	WORD	word;
	struct
	{
		WORD Addr	:5;	
		WORD Mode	:4;
		WORD Can1	:1;
		WORD Can2	:1;
		WORD MisMaska	:1;
		WORD MisTMax	:1;
		WORD MisE1	:1;
		WORD Mis5B	:1;
		WORD Mis24B	:1;
	}bits;
}TInfo;
//
typedef union
{
	BYTE	byte;
	struct
	{
		BYTE WrBeg	:1;	
		BYTE Wr		:1;	
		BYTE Delay	:1;	
		BYTE Rezerv	:5;	
	}bits;
}TInfoWr;

typedef struct
{
//new protokol
//for write
	TInfoWr	InfoWr;
//for Begin Wr
	WORD	M24In;	
	WORD	M5In;	
	WORD	M5RIn;	
	WORD	VU24In;	
	WORD	NU24In;	
	WORD	VU240In;	
	WORD	VU5In;	
	WORD	NU5In;	
	WORD	VU50In;	
//for Wr
	BYTE	DDIn[2];	
	BYTE	OIIn[2];	//1-out, 0-in	
//for  DELAY
	BYTE	DelayIn[7];	
//for Rd
	WORD	AnData[20];
	BYTE	DDate[2];
	BYTE	DMis[2];
//internal
	WORD	M24;	
	WORD	M5;	
	WORD	M5R;	
	WORD	VU24;	
	WORD	NU24;	
	WORD	VU240;	
	WORD	VU5;	
	WORD	NU5;	
	WORD	VU50;	
	WORD	JobCo;	
	WORD	DD;	
	WORD	DDPre;	
	WORD	OI;	//1-out, 0-in	
	WORD	OIPre;	//1-out, 0-in	

// end new protokol


//for write -PDO RECEIVE	
	BYTE 	AdDelayIn;  //0-3b - adres in,4-6b - line signal,7b=1-is delay
//for read	
//	BYTE 	MisTst;  //0b-mis 24b,1b-5b,3b-0b,4b-E1
	WORD 	Delay;   //time of delay
//interl use
	BYTE 	AdDelay;  //0-3b - adres in,4-6b - line signal,7b=1-is delay
	WORD 	Tmax;	
	BYTE	Param[16];  //3 bit=1-out, 0-2bit уровень сигн.
	BYTE	ParamPre[16];	//3 bit=1-out, 0-2bit уровень сигн.
	BYTE 	Timer;
	WORD 	Timer2;
	TInfo	Info;
	BYTE 	St;
	WORD	DiData;
	WORD	Mistake;
}CKVV_C;

void InitKVVC();
void DriverKVVC();
BYTE Change(BYTE num, BYTE *mas1, BYTE *mas2);
void SetRd();
void Read();
BYTE RangeOld(void);

//new prot
void BeginWr();
void WrOut();   //write byte
void SetWr();
void Compare();
void ReadOne(BYTE chanel);
BYTE Range(void);
void ReadTst();  //*

extern CKVV_C Kvv;

#endif
#endif