/*********************************************************                   
 *                                                       *
 *             Master/slave CANopen Library              *
 *                                                       *

 *********************************************************
           File : appli.c
 *-------------------------------------------------------*
 * This is where you put your code                       *      
 *                                                       *
 *********************************************************/

#define PDO_ERROR /* To send in a PDO an error, in all situation */


/* Comment when the code is debugged */
//#define DEBUG_CAN
//#define DEBUG_WAR_CONSOLE_ON
//#define DEBUG_ERR_CONSOLE_ON
/* end Comment when the code is debugged */

#include <stddef.h> /* for NULL */
#include "mb90590.h"
//#include "candriver.h"
#include "applicfg.h"
#include "objacces.h"
#include "def.h"
#include "sdo.h"
#include "pdo.h"
#include "canOpenDriver.h"
#include "objdictdef.h"
#include "lifegrd.h"
#include "timer.h"
#include "nmtSlave.h" 
#include "init.h" 
#include "sync.h"
#include "appli.h"

#include "global.h"
#include INCLUDE_H


// MB90 configuration
// -----------------------------------------------------


// Required definition variables
// -----------------------------
// The variables that you should define for debugging.
// They are used by the macro MSG_ERR and MSG_WAR in applicfg.h
// if the node is a slave, they can be mapped in the object dictionnary.
// if not null, allow the printing of message to the console
// Could be managed by PDO

//UNS8 printMsgErrToConsole = 1;
//UNS8 printMsgWarToConsole = 1;



/*************************User's variables declaration**************************/
char B_Out[100];

UNS16 softCount = 0;
UNS8 lastMinute = 0;
UNS8 lastSecond = 0;
UNS8 sendingError = 0;
e_nodeState lastState = Unknown_state;
//------------------------------------------------------------------------------
UNS8	ADDR_NODE=1;

//------------------------------------------------------------------------------
extern UNS8 seconds;		// Mapped at index 0x2000, subindex 0x1
extern UNS8 minutes;		// Mapped at index 0x2000, subindex 0x2
extern UNS8 hours;			// Mapped at index 0x2000, subindex 0x3
extern UNS16 day;			// Mapped at index 0x2000, subindex 0x4
//extern UNS32 canopenErrNB;	// Mapped at index 0x6000, subindex 0x0
//extern UNS32 canopenErrVAL;	// Mapped at index 0x6001, subindex 0x0
//------------------------------------------------------------------------------


// Incrementation of the date, every second
void incDate(void)
{
  if (seconds == 59) 
  {
    seconds = 0;
    if (minutes == 59) 
    {
      minutes = 0;
      if (hours == 23) 
      {
		hours = 0;
		day++;
      } 
      else
		hours++;
    }
    else 
      minutes++;
  }
  else
  {
    seconds++;

	}
}



/*********************************************************************/
void heartbeatError( UNS8 heartbeatID )
{
  MSG_ERR(0x1F00, "HeartBeat not received from node : ", heartbeatID);
}


/*********************************************************************/
void initialisation( void )
{ 
	MSG_WAR(0X3F05, "I am in INITIALISATION mode ", 0);
	/* Defining the node Id */
	setNodeId(ADDR_NODE);
	//------------------------
	MSG_WAR(0x3F06, "My node ID is : ", getNodeId()); 
	initCANopenMain();    //initialisation du canopen 
	heartbeatInit();      //initialisation du lifeguarding
	
	SetupCAN(SPEED_CAN_0,SPEED_CAN_1);	//initialisation du bus Can
}


/*********************************************************************/
void preOperational(void)
{
  // Test if the heartBeat have been received. Send headbeat
 // heartbeatMGR();
  // Read message
  //receiveMsgHandler(0);
}


/********************************************************************/
void operational( void )
{ 
  	// Test if the heartBeat have been received. Send headbeat
  	//heartbeatMGR();
 
  
}

/*****************************************************************************/
void stopped( void )
{
  //heartbeatMGR();
  // Read message
  //receiveMsgHandler(0);
}


/*****************************************************************************/

/********************************* MAIN ***************************************/

void DriverCanOpen()
{
	//if(NUMB_CAN == 2)
	if((SPEED_CAN_0!=0)&&(SPEED_CAN_1!=0))
	{
		if((program.TimerCan0>=TIME_OUT_CAN) && (program.TimerCan1>=TIME_OUT_CAN))
			SetError(ind_COMA);
		if((program.TimerCan0<TIME_OUT_CAN) && (program.TimerCan1<TIME_OUT_CAN))
			ClearError(ind_COM1);
		if((program.TimerCan0<TIME_OUT_CAN) && (program.TimerCan1>=TIME_OUT_CAN))
			SetError(ind_COM1);
		if((program.TimerCan0>=TIME_OUT_CAN) && (program.TimerCan1<TIME_OUT_CAN))
			SetError(ind_COM1);
			
		if(program.TimerCan0>=TIME_OUT_CAN)	
		{
			program.ErrorCAN|=Err_CAN1;
			(*STATE_BLOCK)|=ST_Can1; 
		}
		if(program.TimerCan1>=TIME_OUT_CAN)	
		{
			program.ErrorCAN|=Err_CAN2;
			(*STATE_BLOCK)|=ST_Can2; 
		}
	}else
	{
		if(SPEED_CAN_1 != 0)
		{
			if(program.TimerCan1>=TIME_OUT_CAN)
				SetError(ind_COMA);
			program.ErrorCAN&=(~Err_CAN1);
		}//===========================================================================	
		if(SPEED_CAN_0 != 0)
		{
			if(program.TimerCan0>=TIME_OUT_CAN)
				SetError(ind_COMA);
			program.ErrorCAN&=(~Err_CAN1);
		}//===========================================================================	
	}
  // CanOpen slave state machine         
  // ------------------------------------
    
  //while(1) 
  { // slave's state machine 
  //  receiveMsgHandler(0);	
//	receiveMsgHandler(1);
    switch( getState() ) 
    {				
    	case Initialisation:
      		if (lastState != getState()) 
      		{
				//initLeds();
				MSG_WAR(0X3F10, "Entering in INITIALISATION mode ", 0);
				SetError(ind_TEST);
      		}
      		initialisation();
      		// change automatically into pre_operational state  
      		lastState = Initialisation;
      		setState(Pre_operational);
      		break;
					
    	case Pre_operational:
      		if (lastState != getState()) 
      		{
				MSG_WAR(0X3F11, "Entering in PRE_OPERATIONAL mode ", 0);
				SetError(ind_TEST);
      		}
      		preOperational();
      		//if (lastState == Initialisation)
			//slaveSendBootUp(0);
      		lastState = Pre_operational;
      		
      		break;
		case Operational:
      		if (lastState != getState()) 
      		{
				MSG_WAR(0X3F12, "Entering in OPERATIONAL mode ", 0);
      			ClearError(ind_TEST);
      		}
      		operational();    
      		lastState = Operational;	
      		break;
	  		
    	case Stopped:
      		if (lastState != getState()) 
      		{
				MSG_WAR(0X3F13, "Entering in  STOPPED mode", 0);
      			SetError(ind_TEST);
      		}
      		stopped();
      		lastState = Stopped;
      		break;
   	}//end switch case	
  }
}
