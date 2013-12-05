/*********************************************************                   
 *             Master/slave CANopen Library              *
 *********************************************************
 *                 canOpenDriver.h                       *
 *********************************************************
*/

#ifndef __canOpenDriver_h__
#define __canOpenDriver_h__
#include "can.h"
void FastRcvMsg(BYTE nCan,BYTE box);
/** Called when a message is received by the application from the board
 * bus_id is hardware dependant
 * return 0xFF if error (unknown message received, 
 * else return proceed_infos[fc].process_function(bus_id,&m)
 * i.e return the result of the function Proceed_xxx called
 * Return 0 if no new message.*/

UNS8 receiveMsgHandler (UNS8 bus_id);

/** Used by the application which indicates that
 * its receives a message, *m, from the board
 * Return 0 if new message, other if no new message.*/

BYTE f_can_receive(BYTE nCan ,Message *m );

/** Used by the application to transmit a message, *m, to the board
 * Return undefined today. */

BYTE f_can_send(BYTE nCan ,Message *m );

void SendFifoCanMsg(UNS8 nCAN);

#endif // __canOpenDriver_h__
