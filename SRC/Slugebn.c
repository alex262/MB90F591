#include "mb90590.h"

#include "slugebn.h"


// Init. I2C interface line
//	SDA: Dir = 0(in),  Port = 1;
//	SCL: Dir = 1(out), Port = 1;

void clok (void)
{
	unsigned char i;
	for (i=0;i<1;i++);
}

// Writing to the Address Pointer Register to Select
// a Data Register for a Subsequent Read Operation
void chek_tem (void)
{
	unsigned char i;
//Стартовый бит
	SDA_0; clok (); SCL_0;
// Frame 1 - Serial bus address byte
	SDA_1; clok (); SCL_1; SCL_0; //1001---0	(1)
	SDA_0; clok (); SCL_1; SCL_0; //			(2)
	SDA_0; clok (); SCL_1; SCL_0; //			(3)
	SDA_1; clok (); SCL_1; SCL_0; //			(4)
	SDA_0; clok (); SCL_1; SCL_0; //			(5)
	SDA_0; clok (); SCL_1; SCL_0; //			(6)
	SDA_1; clok (); SCL_1; SCL_0; //			(7)
	SDA_0; clok (); SCL_1; SCL_0; //			(8)R/W(0-W,1-R)
// Test Ack. by AD7416
	SDA_1; SCL_1; clok ();		  //			(9)
	
//	if (PDR7 && 0x04) ; //return 1;
	SDA_0;
	SCL_0;//clok ();

// Frame 2 - Address pointer register byte
	//SDA_0;
	for (i=0;i<8;i++)
	{
		SCL_1;clok (); SCL_0; //Посылаем указатель адреса регистра значения температуры
	}
// Test Ack. by AD7416
	SDA_1;
	SCL_1;									//			(9)
	clok ();
//	if (PDR7 && 0x04) ; //return 2;
	SCL_0;
	clok ();
//Стоп бит
	SDA_0; SCL_1;clok (); SDA_1;clok (); 
}

// Reading Two Bytes of Data from the Temperature Value Register
void tem(WORD *data)
{
	unsigned int t=0,b=0;
	unsigned char i;
	
	chek_tem();				//Передача адреса регистра температуры
//Стартовый бит
	SDA_0; SCL_0;clok ();
// Frame 1 - Serial bus address byte
	SDA_1; clok (); SCL_1; SCL_0; //1001---0	(1)
	SDA_0; clok (); SCL_1; SCL_0; //			(2)
	SDA_0; clok (); SCL_1; SCL_0; //			(3)
	SDA_1; clok (); SCL_1; SCL_0; //			(4)
	SDA_0; clok (); SCL_1; SCL_0; //			(5)
	SDA_0; clok (); SCL_1; SCL_0; //			(6)
	SDA_1; clok (); SCL_1; SCL_0; //			(7)
	SDA_1; clok (); SCL_1; SCL_0; //			(8)R/W(0-W,1-R)
// Test Ack. by AD7416
	SDA_1;
	SCL_1;							//			(9)
	clok ();
	if (I2C_SDA) ; //return 1;	// exit if no ack
	SCL_0;
// Frame 2 - MOST SIGNIFICANT DATA BYTE FROM AD7416 (D15...D8)
	SDA_1;
	for (i=0; i<8; i++)
	{
		SCL_1; clok ();
		b=((b<<1)&0xFFFE)|(I2C_SDA ? 1:0);
		SCL_0;		// (1)...(8)
	}
// Ack. by Master
	SDA_0;
	SCL_1; clok (); SCL_0;	// (9)
// Frame 3 - LEAST SIGNIFICANT DATA BYTE FROM AD7416 (D7...D0)
	SDA_1;
	for (i=0; i<8; i++)
	{
		SCL_1; clok ();
		b=((b<<1)&0xFFFE)|(I2C_SDA ? 1:0);
		SCL_0;		// (1)...(8)
	}
// Ack. by Master
	SDA_0;
	SCL_1; SCL_0;	// (9)
// Stop-bit
	SCL_1;
	SDA_1;
	b=(b&0xFFC0)>>6;
	*data=b;
	//program.tem_s=b>>8;			//Запись значения температуры
	//program.tem_m=b;
}
