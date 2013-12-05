/*********************************************************                   
 *                                                       *
 *             Master/slave CANopen Library              *
 *                                                       *
 
 *********************************************************
           File : candriver.h
 *-------------------------------------------------------*
 * For Microcontroler Motorola MC9S12  (HCS12)           *      
 *                                                       *
 *********************************************************/


#ifndef __CANDRIVER__
#define __CANDRIVER__

//#include DEBUG_CAN

#include "can.h"
#include "objdictdef.h"


/*
The CAN message received are stored in a fifo stack
We consider one stack for all the 5 can devices. It is a choice !
*/

#define BOX_FOR_RCV_MSG  15

/* Be free to change this value */
#define MAX_STACK_MSG_RCV  20
#define MAX_STACK_MSG_SEND 20
/* Number of incomings and outcomings CAN Line. The layer CanOpen must be
used only for ONE line CAN. But you may used one or more CAN drivers, without
a CanOpen layer.
Only 2 lines are implemented. If more lines are needed, copy void __attribute__((interrupt)) can0HdlRcv (void) to void __attribute__((interrupt)) canXHdlRcv (void) and make 
changes : [0] to [x], CAN0 to CANX, etc
*/
#define NB_LINE_CAN 2

/* Whose hardware HCS12 CAN block is used for CanOpen ? Chose between CAN0, ..., CAN4
If you use CANOPEN_LINE_NUMBER_USED = CANI, the value of NB_LINE_CAN must be
more or equal to I + 1
Value other than CAN0 not tested, but should work fine.
 */
#define CANOPEN_LINE_NUMBER_USED CAN0

/* Stack of received messages 
MSG received on CAN0 module is stored in stackMsgRcv[0], etc
*/
//extern volatile Message stackMsgRcv[NB_LINE_CAN][MAX_STACK_MSG_RCV];


/* Copy from the stack of the message to treat */
extern Message msgRcv;

/* used to chose the function to lounch on receiving a msg,
according to the cobId
*/
extern proceed_info proceed_infos[];
extern UNS8 Num_Proc_Max;
/* To move on the stack of messages 
 */
typedef struct {
  UNS8 w ; /* received */
  UNS8 r ; /* To transmit */
} t_pointerStack;


/* Pointer for write or read a message in/from the reception stack */
//extern volatile t_pointerStack ptrMsgRcv[NB_LINE_CAN];

void canRcvHardMB90591 (UNS8 nCan,UNS8 box);






#endif /*__CANDRIVER__*/

