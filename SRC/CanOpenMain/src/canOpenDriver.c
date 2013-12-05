/*********************************************************                   
 *                                                       *
 *             Master/slave CANopen Library              *
 *                                                       *
 *********************************************************
           File : canOpenDriver.c
 *********************************************************/

//#define  DEBUG_CAN  
//#define DEBUG_WAR_CONSOLE_ON 
//#define DEBUG_ERR_CONSOLE_ON 

#include <stddef.h> /* for NULL */
#include <mb90590.h> /* for NULL */

#include <applicfg.h> 
#include <candriver.h>
//#include <interrupt.h"

#include <canOpenDriver.h>
#include <can.h>
#include <objdictdef.h>
#include <timer.h> 

volatile static Message 		stackMsgSend[NB_LINE_CAN][MAX_STACK_MSG_SEND]; 
volatile static t_pointerStack 	ptrMsgSend[NB_LINE_CAN];
 
volatile static Message 		stackMsgRcv[NB_LINE_CAN][MAX_STACK_MSG_RCV]; 
volatile static t_pointerStack 	ptrMsgRcv[NB_LINE_CAN];
/* Copy from the stack of the message to treat */
//static Message msgRcv; 

/***************************************************************************/
/* receiveMsgHandler : call the receive function 
 and call the implied process function
 Parameters : the function used to receive can messages. 
 Function used only when platform is Linux or hcs12*/
UNS8 receiveMsgHandler(UNS8 nCAN)
{ 
	Message m;
  	UNS8 fc;	       //the function code
  	while(!(f_can_receive(nCAN, &m)))
  	{
    	fc = GET_FUNCTION_CODE(m);//(m->cob_id >> 7);//
    	
    	if(fc>Num_Proc_Max) return 0xFF;
    	if(proceed_infos[fc].process_function!=NULL) 
		{
      		proceed_infos[fc].process_function(nCAN,&m);
    	}
  	}
  	return 0;   
}
/**************************************************************************/
UNS8 f_can_receive(UNS8 nCAN, Message *m)
{ 
	Message *pM;
	UNS8 i, j;
	
	if(nCAN>1) return 0xFF;
	j=nCAN;	
	/* See if a message is pending in the stack */
	if (ptrMsgRcv[j].r == ptrMsgRcv[j].w)
		return 0xFF; // No new message
	
	/* Increment the reading pointer of the stack */
	if (ptrMsgRcv[j].r == (MAX_STACK_MSG_RCV - 1)) 
		ptrMsgRcv[j].r = 0;
	else
		ptrMsgRcv[j].r ++;
	
	/* Store the message from the stack*/
	pM = (Message *)&stackMsgRcv[j][ptrMsgRcv[j].r];
	m->cob_id = pM->cob_id;
	m->len 	= pM->len;
	m->rtr 	= pM->rtr;
	for (i = 0 ; i < pM->len ; i++)
		m->data[i] = pM->data[i];
	return 0;
}

void canRcvHardMB90591 (UNS8 nCan,UNS8 box)
{ 
	UNS8 NewPtrW, i; 
	Message *pM;

	if(nCan>1)return;
  
	/* We are obliged to save the message while the interruption is pending */
	/* Increment the writing stack pointer before writing the msg */
	if (ptrMsgRcv[nCan].w == (MAX_STACK_MSG_RCV - 1)) 
		NewPtrW = 0;
	else
		NewPtrW = ptrMsgRcv[nCan].w + 1;

	if (NewPtrW == ptrMsgRcv[nCan].r) 
	{
		
		puts("RF/n/r");
		/* The stack is full. The last msg received before this one is lost */
		MSG_WAR(0X1620, "Stack for received msg is full", 0);
	}
	else
		ptrMsgRcv[nCan].w = NewPtrW;

	/* Store the message */
	if(nCan==0)
	{
		pM = (Message *)&stackMsgRcv[0][ptrMsgRcv[0].w];
		pM->cob_id = GET_ID_0(box);//GET_ID(IDR0(box));
		pM->len = DLCR0(box);
		pM->rtr = (RRTRR0>>box)&1;
		if(pM->rtr == 0)
		{
			pM->len	= DLCR0(box);
			for(i=0;i<pM->len;i++)	
				pM->data[i]=DTR0_BYTE(box, i);
		}else pM->len=0;
		//word_copy(pM->data,DTR0_WPTR(box),DLCR0(box));
	}
	if(nCan==1)
	{
		pM = (Message *)&stackMsgRcv[1][ptrMsgRcv[1].w];
		pM->cob_id = GET_ID_1(box);//GET_ID(IDR1(box));
		pM->len = DLCR1(box);
		pM->rtr = (RRTRR1>>box)&1;
		if(pM->rtr == 0)
		{
			pM->len	= DLCR1(box);
			for(i=0;i<pM->len;i++)	
				pM->data[i]=DTR1_BYTE(box, i);
		}else pM->len=0;

		//word_copy(pM->data,DTR1_WPTR(box),DLCR1(box));
	}
}
//--------------
/*void FastRcvMsg(BYTE nCan,BYTE box)
{
	Message m;
  	UNS8 fc;	       //the function code
  	
  	if(nCan>1)return;
  	
  	if(nCan==0)
  	{
  		m.cob_id = GET_ID_0(box);
  		m.len = DLCR0(box);
  		m.rtr = (RRTRR0>>box)&1;
  		word_copy(m.data,DTR0_WPTR(box),m.len);
  	}else
  	{
  		m.cob_id = GET_ID_1(box);
  		m.len = DLCR1(box);
  		m.rtr = (RRTRR1>>box)&1;
  		word_copy(m.data,DTR1_WPTR(box),m.len);
  	}
  	  	
  	fc = GET_FUNCTION_CODE(m);
    if(fc>Num_Proc_Max) return;
    if(proceed_infos[fc].process_function!=NULL) 
	{
    	proceed_infos[fc].process_function(nCan,&m);
   	}
}*/
BYTE f_can_send(BYTE nCan ,Message *m )
{
	UNS16 mask, inv_mask;
	Message *pM;
	//BYTE state=0;
	BYTE box;
	UNS8 NewPtrW; 

	if(nCan==1)
	{
		for(box=BOX_FOR_RCV_MSG;box<16;box++)
		{
			mask = BitMasks[box];
			inv_mask = ~mask;
			if((TREQR1&mask)!=0) continue;
			BVALR1 		&= inv_mask;					// о клю   и	ик 
			TRTRR1		&= inv_mask;
			IDRX1(box) 	= SET_ID(m->cob_id);			//	и  и	ифик  ор    ик	
			DLCR1(box) 	= m->len;						//	и   ли	ы соо	 и 
			
			//TRTRR1		|=m->rtr>0 ? mask:0;
										
			word_copy(DTR1_WPTR(box),m->data,m->len);	// ко иро   и  соо    и	

			BVALR1 |= mask;								//  клю	  и    ик 
			TREQR1 |= mask;								//  с	о к	рос	  р	
			return 0;
		}
	}
	if(nCan==0)
	{
		for(box=BOX_FOR_RCV_MSG;box<16;box++)
		{
			mask = BitMasks[box];
			inv_mask = ~mask;
			if((TREQR0&mask)!=0) continue;
			BVALR0 		&= inv_mask;					// о клю   и	ик 
			TRTRR0		&= inv_mask;
			IDRX0(box) 	= SET_ID(m->cob_id);			//	и  и	ифик  ор    ик	
			DLCR0(box) 	= m->len;						//	и   ли	ы соо	 и 
			//TRTRR0		|=m->rtr>0 ? mask:0;
											
			word_copy(DTR0_WPTR(box),m->data,m->len);	// ко иро   и  соо    и	
	
			BVALR0 |= mask;								//  клю	  и    ик 
			TREQR0 |= mask;								//  с	о к	рос	  р	
			return 0;
		}
	}
	//if(state==0)
	{
  		//puts("S/n/r");
  		if(nCan>1)return 1;
  
   		if (ptrMsgSend[nCan].w == (MAX_STACK_MSG_SEND - 1)) 
    		NewPtrW = 0;
  		else
    		NewPtrW = ptrMsgSend[nCan].w + 1;
  		
  		if (NewPtrW == ptrMsgSend[nCan].r) 
  		{
    		MSG_WAR(0X1620, "Stack for sending msg is full", 0);
    		return 1;
  		}
  		else
    		ptrMsgSend[nCan].w = NewPtrW;
  		
  		pM = (Message *)&stackMsgSend[nCan][ptrMsgSend[nCan].w];
  		pM->cob_id 		= m->cob_id;
  		pM->len 		= m->len;
  		pM->rtr 		= m->rtr;
  		for( box=0;box<m->len;box++)
  		{
  			pM->data[box]=m->data[box];
  		}
  	}
	return 0;
}

void SendFifoCanMsg(UNS8 nCAN)
{ 
  Message *pM;
  UNS8 i;

  if(nCAN>1) return;
  
  /* See if a message is pending in the stack */
  if (ptrMsgSend[nCAN].r == ptrMsgSend[nCAN].w)  return; // No new message

  /* Increment the reading pointer of the stack */
  if (ptrMsgSend[nCAN].r == (MAX_STACK_MSG_SEND - 1)) 
     ptrMsgSend[nCAN].r = 0;
  else
    ptrMsgSend[nCAN].r++;

  /* Store the message from the stack*/
  pM = (Message *)&stackMsgSend[nCAN][ptrMsgSend[nCAN].r];
  
  f_can_send(nCAN ,pM);
}