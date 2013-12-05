#include "global.h"
#include "Ndd16c.h"
#ifdef PLATA_NDD
//---------------------------------------------------------------------------------------------------------
// Процедура подавление дребезга входов DIn
// Вызывается для каждого модуля НДД
//addr		- адрес модуля
//inputs	- считанное состояние НДД
//time		- Время подавления дребезга
void debounce_Din(unsigned char addr, unsigned char inputs, unsigned short time)
{
	unsigned char i;									// счетчик
	unsigned char ch_cnt;								// колличество входов у данного
	unsigned char pr,tmp,bit;							// временные переменные

__DI();

	pr=Ndd.pr_data[addr];
	
	tmp = inputs ^ pr;									// в tmp - изменения на входах
	if (time==0) time=1;
	for (i=0;i<8;i++)
	{
		bit = 1<<i;										// определение текущего входа
		if (tmp & bit)
		{												// состояние входа изменилось - сброс счетчика
			Ndd.counters[addr][i]=0;
			Ndd.counters_dr[addr][i]++;	
			if(Ndd.counters_dr[addr][i]>=time)			//Входной сигнал не устанавливается в устойчивое состояние
			{
				Ndd.counters_dr[addr][i]=time;
				Ndd.drebezg[addr]&=~bit;				//
				Ndd.drebezg[addr]|=bit;					//Запись сигнала у которого дребезг
			}
			else	Ndd.drebezg[addr]&=~bit;
		} 
		else
		 {												// состояние входа не изменилось - инкремент
			Ndd.counters_dr[addr][i]=0;
			Ndd.counters[addr][i]++;					// счетчика
			if (Ndd.counters[addr][i]>=time-1)
			{											// состояние входа установилось
				Ndd.state[addr]&=~bit;					// запись состояния входа
				Ndd.state[addr]|=(inputs & bit);
				Ndd.counters[addr][i]--;				// декремент счетчика
			}
		}
	}
	Ndd.pr_data[addr] = inputs;							// сохранение текущих значений как предыдущих
__EI();
}
#endif