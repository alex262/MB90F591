#include "mb90590.h"
#include "timer.h"
#include "global.h"
#include "applicfg.h"
#include "def.h"
#include "objdictdef.h"
#include "lifegrd.h"
#include "sync.h"

#include INCLUDE_H

TSystemTimers SystemTimers;

void InitTimerService(void);
void TimerService(void);

void timerInterrupt( UNS8 unused);
extern UNS16 softCount;

void SetupTime(void)
{ 
	InitTimerService();

//    TBTC_TBIE=1;
//	TBTC_TBC1=1;
//	TBTC_TBC0=0;

    /* initialise reload timer 0 */
    TMRLR0 = RELOAD_VALUE_0;    /* set reload value*/
    TMCSR0 = 0x81B;      		/* prescaler 2us at 16 MHz */
	program.ms1counter=0;
	
//	TMRLR1 = RELOAD_VALUE_1;    /* set reload value*/
 //   TMCSR1 = 0x81B;      		/* prescaler 2us at 16 MHz */
}
// р рывани  Reload Timer 1 
__interrupt void ReloadTimer1(void) 
{
	__DI();	
	TMCSR1_UF = 0;       			/* reset underflow interrupt request flag */
	//receiveMsgHandler(0);	
	//receiveMsgHandler(1);
	__EI();	
}
// р рывани  Reload Timer 0 
__interrupt void ReloadTimer0(void) 
{   
	BYTE i;
	TMCSR0_UF = 0;       			/* reset underflow interrupt request flag */
//	timerInterrupt(1);
//	if(program.watch_dog>254) RESET;	//~1с
//		else program.watch_dog++;


	TimerService();// декрементирование пользовательских таймеров	
	
	//===========================================================================
	if(program.TimerCan0<TIME_OUT_CAN)	//(ok)
	{
		program.TimerCan0++;
		ClearError(ind_COMA);
		program.ErrorCAN&=(~Err_CAN1);
		(*STATE_BLOCK)&=~ST_Can1; 
	}
	if(program.TimerCan1<TIME_OUT_CAN)//(ok)
	{
		program.TimerCan1++;
		ClearError(ind_COMA);
		program.ErrorCAN&=(~Err_CAN2);
		(*STATE_BLOCK)&=~ST_Can2; 
	}
	program.COUNT++;
	Indicate(&program.COUNT,BLINK_LED/*200*/); //ok
	//===========================================================================
	//#ifdef PLATA_FSU22
	//	Fsu22.Timer++;
	//#endif
	//===========================================================================
	#ifdef PLATA_FSU22C
		Fsu22C.Timer++;			//not
	#endif
	//===========================================================================
	#ifdef PLATA_FSU
		//Fsu.Timer_Test++;
		Fsu.Timer++;	//ok
		Fsu.Timer2++;	//ok
	#endif
	//===========================================================================
	#ifdef PLATA_NDD
		Ndd.Timer++;	//not
		Ndd.Timer2++;	//not
		Ndd.TimerTest++;//ok
	#endif
	//===========================================================================
	#ifdef PLATA_ADC
		//Adc.TimerTem++;
		Adc.TimerTest++;	//not
		Adc.Timer++;
		//ReadAdcInt();
	#endif
	//===========================================================================
	#ifdef PLATA_DAC9
		Dac9.TimerErrDac++;	//not
		Dac9.TimerMaster++;
		#ifdef READ_TEMP
			Dac9.TimerTem++;	
		#endif
		ReadAdcInt();
		//SelectMasterDAC();
	#endif
	//===========================================================================
	#ifdef PLATA_AVV2C
		Avv.TimerTem++;
		Avv.Timer++;
	#endif
	#ifdef PLATA_RVV3C
		Rvv.Timer++;
	#endif
	//===========================================================================
	#ifdef PLATA_KVV
		Kvv.Timer++;
		Kvv.Timer2++;
	#endif
	#ifdef PLATA_KCU
		Kcu.Timer++;	//ok
	#endif
	//===========================================================================
	#ifdef PLATA_NDD20P1
//		Ndd.Timer1++;
		for(i=0;i<4;i++)
			Ndd.Timer2[i]++;
	#endif
	#ifdef PLATA_NDD20
		Ndd.Timer1++;
		Ndd.Timer2++;
	#endif
	//===========================================================================
	#ifdef PLATA_RVV5C
		Rvv.Timer++;
	#endif
	//===========================================================================
	#ifdef PLATA_RVV6
		Rvv.Timer++;
	#endif
	//===========================================================================
	#ifdef PLATA_NDD21
		Ndd.Timer++;
		Ndd.Timer2++;
	#endif
	//===========================================================================
	#ifdef PLATA_DAC10
		Dac10.Timer++;
		Dac10.TimerDin++;
		//Dac10.TimerAin++;
		Dac10.TimerTemp++;
		Dac10.TimerDout++;
		//Dac10.TimerErrDac++;
		Dac10.TimerMaster++;
		Dac10.TimerMasterError++;
	#endif
//===========================================================================
}
// р рывани  от базово о та м ра
__interrupt void TimeBaseTimer(void)// 4.096 мс
{
	TBTC_TBR=0;						//сброс с Єт ика
//------------------WatchDog----------------------------------------
//	if(program.watch_dog>122) RESET;	//~1с
//		else program.watch_dog++;
//------------------------------------------------------------------
//------------------------------------------------------------------
	program.ms1counter++;			// в ли  ни  милис к ндно о с  т ика(244*4.096=999.424; 
   									//о ибка за с к нд  составл  т 0.058%
}
//=====================================================
void timerInterrupt( UNS8 unused)
{
	UNS8 i;
	for( i=0; i < NB_OF_HEARTBEAT_PRODUCERS; i++ )
	{
		// this increaes the time var. +1 means +1ms
		if( heartBeatTable[i].should_time > 0 )  
		{
			heartBeatTable[i].time += TIMER_RESOLUTION_MS;
		}
	}
	// increase time of "our" heartbeat...
	//if( ourHeartBeatValues.ourShouldTime > 0 )
    	ourHeartBeatValues.ourTime += TIMER_RESOLUTION_MS;
//	if (SyncValues.ourShouldTime > 0 )
		SyncValues.ourTime += TIMER_RESOLUTION_US ;
}
//=====================================================
UNS16 getTime16( UNS16* time )
{
	UNS16 wReturnValue;
	UNS16 wTestTime;

	wReturnValue = *time;
	wTestTime = *time;
	if( wTestTime != wReturnValue )
	{
		// maybe an overflow occured. call this function again (recursive)
		wReturnValue = getTime16( time );
	}
	return wReturnValue;
}
//=====================================================
UNS32 getTime32( UNS32* time )
{
	UNS32 wReturnValue;
	UNS32 wTestTime;

	wReturnValue = *time;
	wTestTime = *time;
	if( wTestTime != wReturnValue )
	{
		// maybe an overflow occured. call this function again (recursive)
		wReturnValue = getTime32 ( time );
	}
	return wReturnValue;
}
//=====================================================
void setTime16( UNS16* time, UNS16 value )
{
	*time = value;
	if( *time != value )
	{ 
		// it seems that the irq-serviceroutine was called during setting the
		// value, so try again
		setTime16( time, value );
	}
}
//=====================================================
void setTime32( UNS32* time, UNS32 value )
{
	*time = value;
	if( *time != value )
	{ 
		// it seems that the irq-serviceroutine was called during setting the
		// value, so try again
		setTime32( time, value );
	}
}


//=============================================================================================================
TYPE_DATA_TIMER getTime(TYPE_DATA_TIMER * time )
{
	TYPE_DATA_TIMER wReturnValue;
	TYPE_DATA_TIMER wTestTime;

	wReturnValue = *time;
	wTestTime = *time;
	if( wTestTime != wReturnValue )
	{
		// maybe an overflow occured. call this function again (recursive)
		wReturnValue = getTime ( time );
	}
	return wReturnValue;
}
//=====================================================
void setTime( TYPE_DATA_TIMER * time, TYPE_DATA_TIMER value )
{
	*time = value;
	if( *time != value )
	{ 
		// it seems that the irq-serviceroutine was called during setting the
		// value, so try again
		setTime( time, value );
	}
}
//=============================================================================================================

void InitTimerService(void)
{
	BYTE cnt;

	SystemTimers.count = 0;
	cnt = COUNT_USER_TIMERS;
	
	while (cnt--)
	{				
		SystemTimers.timers[cnt] = 0;
	}
}
//регистраци€ пользовательского таймера в системе
//¬ход: указатель на таймер usrtmr
//
void add_timer(TYPE_DATA_TIMER * tmr)
{
	BYTE cnt;
	cnt = COUNT_USER_TIMERS;
	while (cnt--)
	{															//данный таймер уже зарегистрирован
	  if (SystemTimers.timers[cnt]==tmr) return;				//выход
	}
	  
	cnt = COUNT_USER_TIMERS;
	while (cnt--)
	{									
		if (SystemTimers.timers[cnt]==0) //место свободно
		{
			__DI();
			SystemTimers.timers[cnt] = tmr;
			SystemTimers.count++;  
			__EI();
			return;
	  	}
	}
}
//удаление таймера 
void del_timer(TYPE_DATA_TIMER * tmr)
{
	BYTE cnt;
	cnt = COUNT_USER_TIMERS;
	while (cnt--)
	{				
		if (SystemTimers.timers[cnt]==tmr) // таймер найден
		{
			__DI();
			SystemTimers.timers[cnt] = 0;
			SystemTimers.count--;  
			__EI();
			return;	
		}
	}
}
void TimerService(void)
{
	BYTE i;
	
	for (i=0; i<COUNT_USER_TIMERS; i++)	// декрементирование пользовательских таймеров	
	{
		if (SystemTimers.timers[i] != 0) 
		{
			if (*(SystemTimers.timers[i])>0) 
				(*(SystemTimers.timers[i]))--;
		}
	}
}
//=============================================================================================================
