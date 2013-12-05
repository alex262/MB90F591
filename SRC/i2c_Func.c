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
;	Filename:			    i2c_Func.c            
;	Date:				    February 21, 2007          
;	File Version:		  	1.0                             
;	Assembled using:		MPLAB IDE 7.51.00.0               
; 	Author:		  	    	Martin Bowman              
;	Company:			    Microchip Technology, Inc.
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "mb90590.h"
#include "global.h"
#include "i2c.h"

/** V A R I A B L E S **********************************************/
BYTE control = CONTROLBYTE;	// Control byte variable

//Function Prototypes
void bit_in(BYTE *data);		//Bit Input function
void bit_out(BYTE data);		//Bit Out function

/********************************************************************
 * Function:        void bstart(void)
 *
 * Description:     This function generates an I2C Start condition.
 *******************************************************************/
void bstart(void)
{
    SDA_TRIS = 0;                   // Ensure SDA is high
    SCL = 1;                        // Ensure SCL is high
	__wait_nop();
    SDA_TRIS = 1;                   // Configure SDA as an output
    SDA = 0;                        // Pull SDA low
	__wait_nop();
    SCL = 0;                        // Pull SCL low
    
} // end bstart(void)

/********************************************************************
 * Function:        void bstop(void)
 *
 * Description:     This function generates an I2C Stop condition.
 *******************************************************************/
void bstop(void)
{
    SCL = 0;                        // Ensure SCL is low
    SDA_TRIS = 1;                   // Configure SDA as an output
    SDA = 0;                        // Ensure SDA low
	__wait_nop();
    SCL = 1;                        // Pull SCL high
	__wait_nop();
    SDA_TRIS = 0;                   // Allow SDA to be pulled high
} // end bstop(void)

/********************************************************************
 * Function:        void bit_out(BYTE data)
 *
 * Description:     This function outputs a bit to the I2C bus.
 *******************************************************************/
void bit_out(BYTE data)
{
	SCL = 0;                        // Ensure SCL is low
	if (data & 0x80)                // Check if next bit is high
	{
		SDA_TRIS = 0;               // Release SDA to be pulled high
		__wait_nop();
		__wait_nop();
    }
    else
    {
        SDA_TRIS = 1;               // Configure SDA as an output
        SDA = 0;                    // Pull SDA low
		__wait_nop();
		__wait_nop();
    }
    SCL = 1;                        // Pull SCL high to clock bit
	__wait_nop();
	__wait_nop();
	__wait_nop();
    SCL = 0;                        // Pull SCL low for next bit
} // end bit_out(BYTE data)

/********************************************************************
 * Function:        void bit_in(BYTE *data)
 *
 * Description:     This function inputs a bit from the I2C bus.
 *******************************************************************/
void bit_in(BYTE *data)
{
    SCL = 0;                        // Ensure SCL is low	
	__wait_nop();
    SDA_TRIS = 0;                   // Configure SDA as an input
	__wait_nop();
    SCL = 1;                        // Bring SCL high to begin transfer
    *data &= 0xFE;                  // Assume next bit is low
    if (SDA)                        // Check if SDA is high
    {
        *data |= 0x01;              // If high, set next bit
    }
	__wait_nop();
    SCL = 0;                        // Bring SCL low again
} // end bit_in(BYTE *data)

/********************************************************************
 * Function:        BYTE byte_out(BYTE data)
 *
 * Description:     This function outputs a byte to the I2C bus.
 *                  It also receives the ACK bit and returns 0 if
 *                  successfully received, or 1 if not.
 *******************************************************************/
BYTE byte_out(BYTE data)
{
    BYTE i;                // Loop counter
    BYTE ack;              // ACK bit

    ack = 0;
    for (i = 0; i < 8; i++)         // Loop through each bit
    {
        bit_out(data);              // Output bit
        data = data << 1;           // Shift left for next bit
    }
    bit_in(&ack);                   // Input ACK bit

    return ack;
} // end byte_out(BYTE data)

/********************************************************************
 * Function:        BYTE byte_in(BYTE ack)
 *
 * Description:     This function inputs a byte from the I2C bus.
 *                  Depending on the value of ack, it will also
 *                  transmit either an ACK or a NAK bit.
 *******************************************************************/
BYTE byte_in(BYTE ack)
{
    BYTE i;                // Loop counter
    BYTE retval;           // Return value

    retval = 0;
    for (i = 0; i < 8; i++)         // Loop through each bit
    {
        retval = retval << 1;       // Shift left for next bit
        bit_in(&retval);            // Input bit
    }
    bit_out(ack);                   // Output ACK/NAK bit

    return retval;
} // end byte_in(void)

/********************************************************************
 * Function:        void LowDensByteWrite(BYTE data)
 *
 * Description:     This function writes a single byte to a
 *                  low-density (<= 16 Kb) serial EEPROM device.
 *
 * Dependencies:    'control' contains the control byte
 *                  'address' contains the address word
 *******************************************************************/
void LowDensByteWrite(WORD address, BYTE data)
{
    BYTE temp_control;     // Temp. variable for control byte

    // Merge block bits with control byte
    temp_control = (control & 0xF1) | ((address >> 7) & 0x0E);

    bstart();                       // Generate Start condition
    byte_out(temp_control);         // Output control byte
    byte_out((BYTE)address);// Output address LSB
    byte_out(data);                 // Output data byte
    bstop();                        // Generate Stop condition
    ACK_Poll();                     // Begin ACK polling
} // end LowDensByteWrite(BYTE data)

/********************************************************************
 * Function:        void HighDensByteWrite(BYTE data)
 *
 * Description:     This function writes a single byte to a
 *                  high-density (>= 32 Kb) serial EEPROM device.
 *
 * Dependencies:    'control' contains the control byte
 *                  'address' contains the address word
 *******************************************************************/
void HighDensByteWrite(WORD address, BYTE data)
{
    bstart();                       // Generate Start condition
    byte_out(control);              // Output control byte
    byte_out((BYTE)(address>>8));// Output address MSB
    byte_out((BYTE)address);// Output address LSB
    byte_out(data);                 // Output data byte
    bstop();                        // Generate Stop condition
    ACK_Poll();                     // Begin ACK polling
} // end HighDensByteWrite(BYTE data)

/********************************************************************
 * Function:        void LowDensPageWrite(BYTE *data,
 *                                        BYTE numbytes)
 *
 * Description:     This function writes multiple bytes to a
 *                  low-density (<= 16 Kb) serial EEPROM device.
 *
 * Dependencies:    'control' contains the control byte
 *                  'address' contains the address word
 *******************************************************************/
void LowDensPageWrite(WORD address, BYTE *data, BYTE numbytes)
{
    BYTE i;                // Loop counter
    BYTE temp_control;     // Temp. variable for control byte

    // Merge block bits with control byte
    temp_control = (control & 0xF1) | ((address >> 7) & 0x0E);

    bstart();                       // Generate Start condition
    byte_out(temp_control);         // Output control byte
    byte_out((BYTE)address);// Output address LSB
    for (i = 0; i < numbytes; i++)  // Loop through data bytes
    {
        byte_out(data[i]);          // Output next data byte
    }
    bstop();                        // Generate Stop condition
    ACK_Poll();                     // Begin ACK polling
} // end LowDensPageWrite(BYTE *data, BYTE numbytes)

/********************************************************************
 * Function:        void HighDensPageWrite(BYTE *data,
 *                                         BYTE numbytes)
 *
 * Description:     This function writes multiple bytes to a
 *                  high-density (>= 32 Kb) serial EEPROM device.
 *
 * Dependencies:    'control' contains the control byte
 *                  'address' contains the address word
 *******************************************************************/
void HighDensPageWrite(WORD address, BYTE *data, BYTE numbytes)
{
    BYTE i;                // Loop counter

    bstart();                       // Generate Start condition
    byte_out(control);              // Output control byte
    byte_out((BYTE)(address>>8));// Output address MSB
    byte_out((BYTE)address);// Output address LSB
    for (i = 0; i < numbytes; i++)  // Loop through data bytes
    {
        byte_out(data[i]);          // Output next data byte
    }
    bstop();                        // Generate Stop condition
    ACK_Poll();                     // Begin ACK polling
} // end HighDensPageWrite(BYTE *data, BYTE numbytes)

/********************************************************************
 * Function:        void LowDensByteRead(BYTE *data)
 *
 * Description:     This function reads a single byte from a
 *                  low-density (<= 16 Kb) serial EEPROM device.
 *
 * Dependencies:    'control' contains the control byte
 *                  'address' contains the address word
 *******************************************************************/
void LowDensByteRead(WORD address, BYTE *data)
{
    BYTE temp_control;     // Temp. variable for control byte

    // Merge block bits with control byte
    temp_control = (control & 0xF1) | ((address >> 7) & 0x0E);

    bstart();                       // Generate Start condition
    byte_out(temp_control);         // Output control byte
    byte_out((BYTE)address);// Output address LSB
    bstart();                       // Generate Start condition
    byte_out(temp_control | 0x01);  // Output control byte
    *data = byte_in(NAKBIT);        // Input data byte
    bstop();                        // Generate Stop condition
} // end LowDensByteRead(BYTE data)

/********************************************************************
 * Function:        void HighDensByteRead(BYTE *data)
 *
 * Description:     This function reads a single byte from a
 *                  high-density (>= 32 Kb) serial EEPROM device.
 *
 * Dependencies:    'control' contains the control byte
 *                  'address' contains the address word
 *******************************************************************/
void HighDensByteRead(WORD address, BYTE *data)
{
    bstart();                       // Generate Start condition
    byte_out(control);              // Output control byte
    byte_out((BYTE)(address>>8));// Output address MSB
    byte_out((BYTE)address);// Output address LSB
    bstart();                       // Generate Start condition
    byte_out(control | 0x01);       // Output control byte
    *data = byte_in(NAKBIT);        // Input data byte
    bstop();                        // Generate Stop condition
} // end HighDensByteRead(BYTE data)

/********************************************************************
 * Function:        void LowDensSequentialRead(BYTE *data,
 *                                             BYTE numbytes)
 *
 * Description:     This function reads multiple bytes from a
 *                  low-density (<= 16 Kb) serial EEPROM device.
 *
 * Dependencies:    'control' contains the control byte
 *                  'address' contains the address word
 *******************************************************************/
void LowDensSequentialRead(WORD address, BYTE *data, WORD numbytes)
{
    WORD i;                 // Loop counter
    BYTE temp_control;     // Temp. variable for control byte

    // Merge block bits with control byte
    temp_control = (control & 0xF1) | ((address >> 7) & 0x0E);

    bstart();                       // Generate Start condition
    byte_out(temp_control);         // Output control byte
    byte_out((BYTE)address);// Output address LSB
    bstart();                       // Generate Start condition
    byte_out(temp_control | 0x01);  // Output control byte
    for (i = 0; i < numbytes; i++)  // Loop through data bytes
    {
        if (i < (numbytes - 1))     // Check if more data will be read
        {
            data[i] = byte_in(ACKBIT); // If not last, input byte & send ACK
        }
        else
        {
            data[i] = byte_in(NAKBIT); // If last byte, input byte & send NAK
        }
    }
    bstop();                        // Generate Stop condition
} // end LowDensSequentialRead(BYTE *data, BYTE numbytes)

/********************************************************************
 * Function:        void HighDensSequentialRead(BYTE *data,
 *                                              BYTE numbytes)
 *
 * Description:     This function reads multiple bytes from a
 *                  high-density (>= 32 Kb) serial EEPROM device.
 *
 * Dependencies:    'control' contains the control byte
 *                  'address' contains the address word
 *******************************************************************/
void HighDensSequentialRead(WORD address, BYTE *data, WORD numbytes)
{
    WORD i;                 // Loop counter

    bstart();                       // Generate Start condition
    byte_out(control);              // Output control byte
    byte_out((BYTE)(address>>8));// Output address MSB
    byte_out((BYTE)address);// Output address LSB
    bstart();                       // Generate Start condition
    byte_out(control | 0x01);       // Output control byte
    for (i = 0; i < numbytes; i++)  // Loop through data bytes
    {
        if (i < (numbytes - 1))     // Check if more data will be read
        {
            data[i] = byte_in(ACKBIT); // If not last, input byte & send ACK
        }
        else
        {
            data[i] = byte_in(NAKBIT); // If last byte, input byte & send NAK
        }
    }
    bstop();                        // Generate Stop condition
} // end HighDensSequentialRead(BYTE *data, BYTE numbytes)

/********************************************************************
 * Function:        void ACK_Poll(void)
 *
 * Description:     This function implements Acknowledge polling.
 *
 * Dependencies:    'control' contains the control byte
 *******************************************************************/
void ACK_Poll(void)
{
    BYTE result;           // Polling result

    result = 1;                     // Initialize result
    do
    {
        bstart();                   // Generate Start condition
        result = byte_out(control); // Output control byte
    } while (result == 1);
    bstop();                        // Generate Stop condition
} // end ACK_Poll(void)
