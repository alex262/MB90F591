#include "isd.h"
#include "mb90590.h"
//Инициализация 1 канала DMA UART0
//COUNT -  количество посылаемых байт
//SDRval - указатель на отправляемый буфер
void EIIOS_Descriptor0(unsigned short COUNT, unsigned char *SDRval)
{
	unsigned long temp = (unsigned char) &SDRval[0]; // get Buffer address 
   	ISD0_ISCS = 0x12;	// set status register
   						// Bit0 : SE  : 0 : no termination by request from resource
   						// Bit1 : DIR : 1 : Buffer -> IO (because we want to send through UART)
   						// Bit2 : BF  : 0 : update Buffer after data transfer (to send whole string)
   						// Bit3 : BW  : 0 : Byte-transfer (UART-Send-register has 8 Bits)
   						// Bit4 : IF  : 1 : I/O register is fixed (use always UART-send-register)
						// Bit7..5			reserved   						
						
    ISD0_BAPL = (unsigned char) &SDRval[0];	// set lower address of buffer
    temp >>= 8;
	ISD0_BAPM = (unsigned int) temp;		// set middle address of buffer
	temp >>= 8;
	ISD0_BAPH = (unsigned int) temp;		// set upper address of buffer
	ISD0_DCT  = COUNT;
	ISD0_IOA = (unsigned int) &UODR0;		// I/O address pointer: use UART1

	ICR06 = 0x0B;		// 8 IRQ Control register "Reload Timer 0"
   						// Bit2..0 	: IL2..0  : 000  : IRQ Priority, valid after EIIOS has finished (ISE = 0)
   						// Bit3 	: ISE 	  :	1    : IRQ serve EIIOS
						// Bit7..4	: ICS3..0 : 0000 : EIIOS Chanel 0 will be used
}

//Инициализация 1 канала DMA UART1
//COUNT -  количество посылаемых байт
//SDRval - указатель на отправляемый буфер
void EIIOS_Descriptor1(unsigned short COUNT, unsigned char *SDRval)
{
	unsigned long temp = (unsigned char) &SDRval[0]; // get Buffer address 
   	ISD1_ISCS = 0x12;	// set status register
   						// Bit0 : SE  : 0 : no termination by request from resource
   						// Bit1 : DIR : 1 : Buffer -> IO (because we want to send through UART)
   						// Bit2 : BF  : 0 : update Buffer after data transfer (to send whole string)
   						// Bit3 : BW  : 0 : Byte-transfer (UART-Send-register has 8 Bits)
   						// Bit4 : IF  : 1 : I/O register is fixed (use always UART-send-register)
						// Bit7..5			reserved   						
						
    ISD1_BAPL = (unsigned char) &SDRval[0];	// set lower address of buffer
    temp >>= 8;
	ISD1_BAPM = (unsigned int) temp;		// set middle address of buffer
	temp >>= 8;
	ISD1_BAPH = (unsigned int) temp;		// set upper address of buffer
	ISD1_DCT  = COUNT;
	ISD1_IOA = (unsigned int) &UODR1;		// I/O address pointer: use UART 0

	ICR06 = 0x1C;		// IRQ Control register "Reload Timer 0"
   						// Bit2..0 	: IL2..0  : 000  : IRQ Priority, valid after EIIOS has finished (ISE = 0)
   						// Bit3 	: ISE 	  :	1    : IRQ serve EIIOS
						// Bit7..4	: ICS3..0 : 0001 : EIIOS Chanel 1 will be used
}
//Инициализация 2 канала DMA UART2
//COUNT -  количество посылаемых байт
//SDRval - указатель на отправляемый буфер
void EIIOS_Descriptor2(unsigned short COUNT, unsigned char *SDRval)
{
	unsigned long temp = (unsigned char) &SDRval[0]; // get Buffer address 
   	ISD2_ISCS = 0x12;	// set status register
   						// Bit0 : SE  : 0 : no termination by request from resource
   						// Bit1 : DIR : 1 : Buffer -> IO (because we want to send through UART)
   						// Bit2 : BF  : 0 : update Buffer after data transfer (to send whole string)
   						// Bit3 : BW  : 0 : Byte-transfer (UART-Send-register has 8 Bits)
   						// Bit4 : IF  : 1 : I/O register is fixed (use always UART-send-register)
						// Bit7..5			reserved   						
						
    ISD2_BAPL = (unsigned char) &SDRval[0];	// set lower address of buffer
    temp >>= 8;
	ISD2_BAPM = (unsigned int) temp;		// set middle address of buffer
	temp >>= 8;
	ISD2_BAPH = (unsigned int) temp;		// set upper address of buffer
	ISD2_DCT  = COUNT;
	ISD2_IOA = (unsigned int) &UODR2;		// I/O address pointer: use UART1

	ICR06 = 0x2A;		// 8 IRQ Control register "Reload Timer 0"
   						// Bit2..0 	: IL2..0  : 000  : IRQ Priority, valid after EIIOS has finished (ISE = 0)
   						// Bit3 	: ISE 	  :	1    : IRQ serve EIIOS
						// Bit7..4	: ICS3..0 : 0002 : EIIOS Chanel 2 will be used
}


