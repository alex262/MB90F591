#include "mb90590.h"
#include "global.h"

#pragma section CODE=UTIL, attr=CODE,locate=0xF99000
#pragma section FAR_CODE=UTIL, attr=CODE,locate=0xF99000
//-----------------------------------------------------------------------------------
unsigned int Calc(unsigned char H,unsigned char L)
{
	unsigned int   N = 0;
	N = (H << 8) + L;
	return N;
}
unsigned int CRC( BYTE *sBuf, WORD nLen )
{
	WORD i,CRC = 0;

	for(i = 0; i < nLen; i++ )
	{
		CRC += sBuf[i];
	}
	return CRC;
}

void PrHexB(BYTE Dat)
{
	BYTE i, Nib;
	for (i=0;i<2;i++) 
	{
		Nib = Dat >> 4;
		Dat = Dat << 4;
		if (Nib < 10) Nib += '0';
		else Nib += ('A'-10);
		Putch(Nib);
	}
}
void PrHexW(WORD Dat)
{
	BYTE i, Nib;
	for (i=0;i<4;i++) 
	{
		Nib = Dat >> 12;
		Dat = Dat << 4;
		if (Nib < 10) Nib += '0';
		else Nib += ('A'-10);
		Putch(Nib);
	}
}
void PrHexD(unsigned long Dat)
{
	BYTE i, Nib;
	unsigned long TDat;
	for (i=0;i<8;i++) 
	{
		Nib = (TDat = Dat >> 28);
		Dat = Dat << 4;
		Nib &= 0x0F;
		if (Nib < 10) Nib += '0';
		else Nib += ('A'-10);
		Putch(Nib);
	}
}
void PrHexAd(DWORD Dat)
{
	BYTE i, Nib;
	DWORD TDat;
	for (i=0;i<6;i++) {
		Nib = (TDat = Dat >> 20);
		Dat = Dat << 4;
		Nib &= 0x0F;
		if (Nib < 10) Nib += '0';
		else Nib += ('A'-10);
		Putch(Nib);
	}
}
BYTE HexToBinD(BYTE __far *pStr, DWORD *pDat)
{
	BYTE Ch, ix, OkF;
	DWORD TDat;
	ix = 0;
	TDat = 0;
	OkF = 1;
	while (Ch=pStr[ix++]) 
	{
		Ch = toupper(Ch);
		TDat = TDat << 4;
		if (Ch >= 'A') Ch -= ('A'-10);
		else Ch -= '0';
		if (Ch < 16) TDat |= Ch; 
		else OkF = 0; 
	}
	if (OkF) *pDat = TDat;
	return OkF;
}
/*------------------------------------------------*/
//-------------------------------------------
unsigned char *ctobits (unsigned char *str,unsigned char x)
{
int ctr = 8;
//char *old = str;
    do {
        *str = (x & 0x80)? '1' : '0';
    } while (str++, x <<= 1, --ctr);
    *str = '\0';
    return (str);
}
//преобразование HEX в числа
/*unsigned long hextoB1(unsigned char *s, unsigned char col) 
{
    unsigned char  b;
    unsigned long res = 0;
    //int ctr = 6;
    while(col--) {
        if ((b = *s++) >= '0' && b <= '9')
            b -= '0';
        else if ((b &= 0xDF) >= 'A' && b <= 'F')
            b -= ('A'- 0xA);
        else
            return 0;
        res <<= 4; res |= b;
    }
    return res;
}*/
/******************************************************************
* CAUTION: val must be between 0 and F.
*******************************************************************/
void put_4bit_value(BYTE val) {
	if(val <= 9)
		Putch((char)('0' + val));
	else
		Putch((char)('A' - 10 + val));
}
/******************************************************************
* CAUTION: val must be between 00 and FF.
*******************************************************************/
void put_8bit_value(BYTE val) 
{
	put_4bit_value(val >> 4);
	put_4bit_value(val & 0x0f);
}

/******************************************************************
* CAUTION: val must be between 000000 and FFFFFF.
*******************************************************************/
void put_24bit_value(long val) {
	put_8bit_value((int)(val >> 16));
	put_8bit_value((int)((val >> 8) & 0xff));
	put_8bit_value((int)(val & 0xff));
}




void putD(unsigned char p)
{
	unsigned char s1,s10,s100;
	
	s1=s10=s100=0x30;
	
	if(p>=100)
	{
		s100=0x30+p/100;
		p=p%100;
		s1 =0x30+p%10;
		s10=0x30+p/10;
	}
	else
	{
		if(p>=10)
		{
		s1 =0x30+p%10;
		s10=0x30+p/10;
		}
		else
		{
			s1=0x30+p;
		}
	}
	
	Putch(s100);Putch(s10);Putch(s1);
}



void putBIN(unsigned char p)	//Auaia ?enea(1 aaeo) a aeia?iii aeaa a NII1
{
unsigned char n,bit;
	
	for (n=8;n>0;n--){
				bit = (unsigned char)1<<(n-1);	//ii?aaaeaiea oaeouaai aeoa
				if (p & bit)					//anee 1
				{
					Putch(0x31);
				}
				else Putch(0x30);
	}
}
void putBIN_int(unsigned int p)					//Auaia ?enea(2 aaeoa) a aeia?iii aeaa a NII1
{
unsigned char n;
unsigned int bit;
	
	for (n=16;n>0;n--)
	{
		if(n==8) Putch(0x20);
		bit = (unsigned int)1<<(n-1);	//ii?aaaeaiea oaeouaai aeoa
		if (p & bit)				//anee 1
			Putch(0x31);
		else Putch(0x30);
	}

}
void putBIN_lword(unsigned long p)					//Auaia ?enea(2 aaeoa) a aeia?iii aeaa a NII1
{
unsigned char n;
unsigned long bit;
	
	for (n=32;n>0;n--){
				bit = (unsigned long)1<<(n-1);	//ii?aaaeaiea oaeouaai aeoa
				if (p & bit)				//anee 1
				{
					Putch(0x31);
				}
				else Putch(0x30);
	}

}


