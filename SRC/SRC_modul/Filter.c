#include "global.h"
#include "Ndd16c.h"
#ifdef PLATA_NDD
//---------------------------------------------------------------------------------------------------------
// ��������� ���������� �������� ������ DIn
// ���������� ��� ������� ������ ���
//addr		- ����� ������
//inputs	- ��������� ��������� ���
//time		- ����� ���������� ��������
void debounce_Din(unsigned char addr, unsigned char inputs, unsigned short time)
{
	unsigned char i;									// �������
	unsigned char ch_cnt;								// ����������� ������ � �������
	unsigned char pr,tmp,bit;							// ��������� ����������

__DI();

	pr=Ndd.pr_data[addr];
	
	tmp = inputs ^ pr;									// � tmp - ��������� �� ������
	if (time==0) time=1;
	for (i=0;i<8;i++)
	{
		bit = 1<<i;										// ����������� �������� �����
		if (tmp & bit)
		{												// ��������� ����� ���������� - ����� ��������
			Ndd.counters[addr][i]=0;
			Ndd.counters_dr[addr][i]++;	
			if(Ndd.counters_dr[addr][i]>=time)			//������� ������ �� ��������������� � ���������� ���������
			{
				Ndd.counters_dr[addr][i]=time;
				Ndd.drebezg[addr]&=~bit;				//
				Ndd.drebezg[addr]|=bit;					//������ ������� � �������� �������
			}
			else	Ndd.drebezg[addr]&=~bit;
		} 
		else
		 {												// ��������� ����� �� ���������� - ���������
			Ndd.counters_dr[addr][i]=0;
			Ndd.counters[addr][i]++;					// ��������
			if (Ndd.counters[addr][i]>=time-1)
			{											// ��������� ����� ������������
				Ndd.state[addr]&=~bit;					// ������ ��������� �����
				Ndd.state[addr]|=(inputs & bit);
				Ndd.counters[addr][i]--;				// ��������� ��������
			}
		}
	}
	Ndd.pr_data[addr] = inputs;							// ���������� ������� �������� ��� ����������
__EI();
}
#endif