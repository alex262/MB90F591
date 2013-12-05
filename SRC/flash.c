#include "mb90590.h"
#include "flash.h"
#include "global.h"

#pragma section CODE=RAMCODE, attr=CODE
#pragma section FAR_CODE=RAMCODE, attr=CODE



#define DQ7 0x0080							/* data polling flag */
#define DQ5 0x0020	

#define seq_AAAA ((__far volatile unsigned int*)0xFBAAAA)	/* sequence address */
#define seq_5554 ((__far volatile unsigned int*)0xFB5554)	

#define AutoSelCmd 0x9090
#define ProgramCmd 0xA0A0
#define SecEraCmd1 0x8080
#define SecEraCmd2 0x3030
#define ChpEraCmd2 0x1010
#define LoAdr5555 0xAAAA /* Address 5555 is AAAA physically ! */
#define LoAdrAAAA 0x5554 /* Address AAAA is 5554 physically ! */
#define LoAdrxx00 0x0000 /* Address xx00 is xx00 physically ! */
#define LoAdrxx01 0x0002 /* Address xx01 is xx02 physically ! */
#define LoAdrxx02 0x0004
//-------------------
__far BYTE Flash_write(volatile __far WORD *start1_adr,volatile WORD wdata)
{
	BYTE flag = 0;
	/* start write sequence */
	FMCS_WE = 1;
	
	*seq_AAAA = 0x00AA;	/* sends the command to the pointed address */
	*seq_5554 = 0x0055;
	*seq_AAAA = 0x00A0;
	*start1_adr = wdata;		/* send data to the pointed address */
	while(flag == 0)
	{
		if((*start1_adr & DQ7) == (wdata & DQ7))
		{
			flag = 1;
		}
		if((*start1_adr & DQ5) == DQ5)
			if((*start1_adr & DQ7) == (wdata & DQ7))
			{
				flag = 1;
			}
			else
			{
				flag = 2;
			}
	}
	FMCS_WE = 0;			/* reset write enable flag */
	return(flag);
}

//---------------------------------------------------------------------------------------------------------
// Процедера стирания сектора ППЗУ
// вход: sector_addr - стартовый адрес сектора
// выход: TRUE - все нормально, иначе FALSE
//WORD FL_SectorErase(DWORD FAdr)
//{
/*	WORD __far *pAAAA; // some Pointers to Flash Memory 
	WORD __far *p5555; // some Pointers to Flash Memory 
	WORD __far *pAdr;
	WORD TDat,TDat2;
	FMCS_WE = 1;
	pAdr = (WORD __far*) FAdr;
	p5555 = (WORD __far*) (( FAdr & 0xFFFE0000) | LoAdr5555);
	pAAAA = (WORD __far*) (( FAdr & 0xFFFE0000) | LoAdrAAAA);
	*p5555 = 0xAAAA; 		// Data = AA 
	*pAAAA = 0x5555; 		// Data = 55 
	*p5555 = SecEraCmd1; 	// Erase Command 1 
	*p5555 = 0xAAAA; 		// Data = AA 
	*pAAAA = 0x5555; 		// Data = 55 
	*pAdr = SecEraCmd2; 	// Erase Command 2 
	TDat = *pAdr; 			// poll bit 
	do {
		TDat2 = *pAdr; 		// poll bit 
		if ((TDat&0x0070)==(TDat2&0x0070)) {FMCS_WE = 0;return 1;}	// if finished OK 
		else if ((TDat&0x0028)==0x0028) {FMCS_WE = 0; return 0;} 	// else if failure 
		TDat=TDat2;
	} while (1);
	*/
/*	WORD __far *pAAAA; 
	WORD __far *p5555; 
	WORD __far *pAdr;
	WORD TDat;
	pAdr = (WORD __far*) FAdr;
	p5555 = (WORD __far*) (( FAdr & 0xFFFE0000) | LoAdr5555);
	pAAAA = (WORD __far*) (( FAdr & 0xFFFE0000) | LoAdrAAAA);
	*p5555 = 0xAAAA; 	
	*pAAAA = 0x5555; 	
	*p5555 = SecEraCmd1;
	*p5555 = 0xAAAA; 	
	*pAAAA = 0x5555; 	
	*pAdr = SecEraCmd2; 
	do {
		TDat = *pAdr; 	
		if (TDat&0x0080) return 1; 
		else if ((TDat&0x0028)==0x0028) return 0; 
	} while (1);
	*/
//}
/*-------- ----------------------------------------*/
/* checks if a sector is empty (every byte = FF) */
/*------------------------------------------------*/
WORD FL_CheckEmpty(DWORD FAdr,WORD SecWordLen)
{
	WORD __far *pAdr;
	WORD ix, Flag, Dat;
	pAdr = (WORD __far*) FAdr;
	Flag = 1;
	for (ix=0;ix<SecWordLen;ix++) 
	{
		if ((Dat=*pAdr++)!=0xFFFF) Flag = 0; 
	}
	return Flag;
}
//=========================================================================================================
__near BYTE Flash_sector_erase( volatile __far WORD *sector_adr)
{
	BYTE flag = 0;
	int size;
	size = sizeof(sector_adr);
	/* start with chip erase sequence */
	FMCS_WE = 1;
	*seq_AAAA = 0x00AA;	/* sends the command to the pointed address */
	*seq_5554 = 0x0055;
	*seq_AAAA = 0x0080;
	*seq_AAAA = 0x00AA;
	*seq_5554 = 0x0055;
	*sector_adr = 0x0030;
	
	while(flag == 0)
	{
		clrwdt;
		if((*sector_adr & DQ7) == DQ7)	/* Toggle bit */
		{
			flag = 1;		/* successful erased */
		}
		if((*sector_adr & DQ5) == DQ5)	/* time out */
			if((*sector_adr & DQ7) == DQ7)
			{
				flag = 1;	/* successful erased */
			}
			else
			{
				flag = 2;	/* timeout error */
			}
	}
	FMCS_WE = 0;
	return(flag);
}

//==========================================================================================================
//#ifdef PLATA_ADC
//#pragma segment FAR_CODE=FLASHCODE, attr=CODE		// ROM location

//#endif
void WriteFlashBuff(volatile __far WORD *start1_adr,DWORD addr,int count,BYTE Erase)
{
	int i;
	__DI();
	if (Erase == 1)
		Flash_sector_erase((volatile __far WORD *)addr);
	for(i=0;i<count;i++)
	{
		clrwdt;
		Flash_write((volatile __far WORD *)(addr+2*i),start1_adr[i]);
	}
	__EI();
}