/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
;                                                                     
;                     Software License Agreement                      
;                                                                     
;     ©2007 Microchip Technology Inc
;     Mirochip Technology Inc. ("Microchip") licenses this software to 
;     you solely for the use with Microchip Products. The software is
;     owned by Microchip and is protected under applicable copyright
;     laws. All rights reserved.
;
;     SOFTWARE IS PROVIDED "AS IS." MICROCHIP EXPRESSLY DISCLAIMS ANY
;     WARRANTY OF ANY KIND, WHETHER EXPRESS OR IMPLIED, INCLUDING BUT NOT
;     LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
;     PARTICULAR PURPOSE, OR NON-INFRINGEMENT. IN NO EVENT SHALL MICROCHIP
;     BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL
;     DAMAGES, LOST PROFITS OR LOST DATA, HARM TO YOUR EQUIPMENT, COST OF
;     PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
;     BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
;     ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER SIMILAR COSTS.
;     
;                                                                
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
;	Filename:			    i2c.h            
;	Date:				    February 21, 2007          
;	File Version:		  	1.0                             
;	Assembled using:		MPLAB IDE 7.51.00.0               
; 	Author:		  	    	Martin Bowman              
;	Company:			    Microchip Technology, Inc.
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


//These are the definitions for the I2C pins that are used for Bit-Bang 
//communications.  These can be changed in the final Application.
#define SCL			PDR9_P92	//I2C Clock PORTG pin 2
#define SDA			PDR9_P93	//I2C Data 
#define	SDA_TRIS	DDR9_D93	//SDA Tris bit


#define     CONTROLBYTE 0xA0	// Control byte
#define     ACKBIT      0x00	// ACK bit
#define     NAKBIT      0x80	// NAK bit

/** E X T E R N A L   V A R I A B L E S ***************************/

void bstart(void);                      // Start condition
void bstop(void);                       // Stop condition
BYTE byte_out(BYTE);  // Byte output
BYTE byte_in(BYTE);   // Byte input
void bit_out(BYTE data);
void bit_in(BYTE *data);
BYTE byte_out(BYTE data);
BYTE byte_in(BYTE ack);
void LowDensByteWrite(WORD address, BYTE data);
void HighDensByteWrite(WORD address, BYTE data);
void LowDensPageWrite(WORD address, BYTE *data, BYTE numbytes);
void HighDensPageWrite(WORD address, BYTE *data, BYTE numbytes);
void LowDensByteRead(WORD address, BYTE *data);
void HighDensByteRead(WORD address, BYTE *data);
void LowDensSequentialRead(WORD address, BYTE *data, WORD numbytes);
void HighDensSequentialRead(WORD address, BYTE *data, WORD numbytes);
void ACK_Poll(void);                    // Acknowledge polling
