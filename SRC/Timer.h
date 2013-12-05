#ifndef __TIMERMB
#define __TIMERMB
#include "global.h"




#define COUNT_USER_TIMERS	6
#define TYPE_DATA_TIMER		WORD

typedef struct
{
	BYTE count;
	TYPE_DATA_TIMER * timers[COUNT_USER_TIMERS];
}TSystemTimers;

void add_timer(TYPE_DATA_TIMER * tmr);
void del_timer(TYPE_DATA_TIMER * tmr);
TYPE_DATA_TIMER getTime(TYPE_DATA_TIMER * time );
void setTime( TYPE_DATA_TIMER * time, TYPE_DATA_TIMER value );


//#define  	TIMER_RESOLUTION_MS_2	10
//#define 	TIMER_RESOLUTION_US_2 	10000


void SetupTime(void);
void InitFreeRunTimer(void);
void InitInputCapture(void);
__interrupt void ReloadTimer0(void);
__interrupt void ReloadTimer1(void); 



WORD getTime16 (WORD* time);
DWORD getTime32 (DWORD* time);

/** This function sets the correct value of the actual time. If the time
 *  would be written without this function, its possible to set the wrong time,
 *  because the interrupt service routine could be executed during writing
 *  this value.\n
 *  This function calls itself (recursive) if it seams that the ISR was called
 *  during setting the time.
 *  \param time The pointer to the variable thats points to the time that
 *              should be set in the program
 *  \param value The time that should be set.
 */
/** I am not sure that these functions are usefull (FD Nov 2004)*/

void setTime16 (WORD* time, WORD value);
void setTime32 (DWORD* time, DWORD value);

#endif
