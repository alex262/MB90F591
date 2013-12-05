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

	    .PROGRAM WRDCPY
    	.TITLE   WRDCPY
    	;.REG_PASS
		
ffpar1	.EQU	H'6		; first parameter, skip return address
ffpar2	.EQU	H'A		; second parameter, skip destination address
ffpar3	.EQU	H'E		; third parameter, skip source address

ffbnk1	.EQU	H'8		; bank of first address parameter
ffbnk2	.EQU	H'C		; bank of second address parameter
ffbnk3	.EQU	H'10	; bank of third address parameter

nfpar1	.EQU	H'6		; first parameter, skip return address
nfpar2	.EQU	H'8		; second parameter, skip destination address
nfpar3	.EQU	H'C		; third parameter, skip source address

nfbnk2	.EQU	H'A		; bank of second address parameter
nfbnk3	.EQU	H'E 	; bank of third address parameter

nnpar1	.EQU	H'6		; first parameter, skip return address
nnpar2	.EQU	H'8		; second parameter, skip destination address
nnpar3	.EQU	H'A		; third parameter, skip source address


   		.SECTION	CODE_WRDCPY, CODE, ALIGN=2
		.EXPORT 	_wrdcpyNN, _wrdcpyNF
_wrdcpyNN:
		LINK	#0		; DTB is bank of CAN and stack

		MOVW	RW4,RW0			;save RW0
		MOVW	RW0,@RW3+nnpar3	; ctr
		MOVW	A,@RW3+nnpar1	; offset of destination
		MOVW	A,@RW3+nnpar2	; offset of source
		MOVSWI	DTB,DTB		; 

		MOVW	RW0,RW4		; restore RW0
		SWAPW				; destination offset + ctr

		UNLINK
		RETP

_wrdcpyNF:
		LINK	#0		; DTB is bank of CAN and stack

		MOVW	RW4,RW0			;save RW0
		MOVW	RW5,RW2			;save RW2
		MOVW	RW0,@RW3+nfpar3	; ctr
		MOV		A,@RW3+nfbnk2	; source bank
		MOV		ADB,A

		MOVW	A,@RW3+nfpar1	; offset of destination
		MOVW	A,@RW3+nfpar2	; offset of source
		MOVSWI	DTB,ADB			; 

		MOVW	RW0,RW4		; restore RW0
		MOVW	RW2,RW5		; restore RW2
		SWAPW				; destination offset + ctr

		UNLINK
		RETP

		.END
