/*******************************************************************
 *
 *    DESCRIPTION:	Word Copy Functions 
 *                  (for CAN messagebuffer access)
 *
 *    AUTHOR:       Fujitsu Mikroelektronik GmbH, HL98
 *
 *    HISTORY:		V1.0  original version 
 *    23.02.99      V2.0  assembly and C-language splittet   
 *
 *******************************************************************/

#ifndef __WRDCPY_H
#define __WRDCPY_H

/*
 ** wrdcpyNN, wrdcpyNF
 *
 *  PARAMETERS: dest: address of destination buffer
 *              src : address of source data
 *              num : number of words to be copied
 *
 *  DESCRIPTION:
 *   This functions tranfers data from dest to src. Only word accesses
 *   are used for writing. This is necessary for the CAN message buffers.
 *   These buffers do not allow byte access for writing. Therefore, this
 *   function (or similar) has to be used.
 *
 *   wrdcpyNN: Both dest and src are 16Bit addresses. Intended for pro-
 *   grams, which are copying data from bank0 to CAN-message buffer.
 *
 *   wrdcpyNF: dest is a 16Bit address. src is a 24Bit address. Intended
 *   for programs, which are copying data from bank other than bank0 to CAN-
 *   message buffer.
 *
 *  RETURNS: a pointer to the next address after the copied destination area
 *
 */

unsigned int __near * __far wrdcpyNN(unsigned short __near* dest,
                                     const unsigned short __near* src, 
                                     unsigned int num);

unsigned int __near * __far wrdcpyNF(unsigned short __near* dest, 
                                     const unsigned short __far * src, 
                                     unsigned int num);

#endif /* __WRDCPY_H */
