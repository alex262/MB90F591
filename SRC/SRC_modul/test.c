#include "mb90590.h"
#include "test.h"
#include "can.h"


#ifdef PLATA_TEST
 
CTest Test;

void 	(*INIT_BLOK)(void)=InitTest;
void 	(*DRIVER_BLOK)(void)=Driver_Test;
WORD 	(*STATE_BLOCK) 		= &Test.word;

Message msg_tst;
Message msg_tst2;
Message msg_rcv;
Message msg_rcv2;

void InitTest()
{
	BYTE i;

	DDR0=0x00;
	DDR1=0x73;
	DDR2=0x00;
	DDR4=0x00;
	DDR5=0x00;
	DDR6=0x00;
	DDR7=0x00;
	DDR8=0x00;
	DDR9=0x00;
	//------------------
	LEDR=1;
	LEDG=1;
	//------------------
	#ifdef CAN_OPEN_ENABLE
		ADDR_NODE		  =30;//ADDR;
	#endif
	
	for(i=0;i<25;i++)
	{
		Test.w_data[i]=i;
		Test.f_data[i]=i;
		Test.b_data[i]=i;
	}
	
	/*msg_tst.cob_id=0;
	msg_tst.rtr=0;
	msg_tst.len=8;
	msg_tst2.cob_id=0x3FF;
	msg_tst2.rtr=0;
	msg_tst2.len=8;
	
	for(i=0;i<30;i++)
	{
		msg_tst.data[i]=0;
		msg_tst2.data[i]=0xff;
	}*/
}
//===================================================================
WORD nn=0;
BYTE FLAG_OBMEN=0;
void Driver_Test()
{
	BYTE i, flg;
	
	//__DI();
	//receiveMsgHandler(0);
	//__EI();
	//__DI();
	//receiveMsgHandler(1);
	//__EI();
	
/*	for(i=0;i<25;i++)
	{
		Test.w_data[i]=i;
		Test.b_data[i]=i;
		Test.f_data[i]=i;
	}
	if(f_can_receive(0,&msg_rcv) == 0)
	{
		flg=0;
		if(msg_rcv.cob_id==0x123) flg++;
		if(msg_rcv.len==7) flg++;
		for(i=0;i<7;i++)
			if(msg_rcv.data[i]==0x55) flg++;
		for(i=0;i<7;i++)
			if(msg_rcv.data[i]==0xAA) flg=flg+2;
		
		if(flg == 9)
		{
			FLAG_OBMEN = 1;
		}
		
		if(flg == 14)
		{
			FLAG_OBMEN = 0;
		}
		
		if(FLAG_OBMEN != 0)
			f_can_send(0 , &msg_rcv);
		
	}
	if(f_can_receive(1,&msg_rcv2) == 0)
	{
		flg=0;
		if(msg_rcv.cob_id==0x123) flg++;
		if(msg_rcv.len==7) flg++;
		for(i=0;i<7;i++)
			if(msg_rcv.data[i]==0x55) flg++;
		for(i=0;i<7;i++)
			if(msg_rcv.data[i]==0xAA) flg=flg+2;
		
		if(flg == 9)
			FLAG_OBMEN = 1;
		
		if(flg == 14)
			FLAG_OBMEN = 0;

		if(FLAG_OBMEN != 0)
			f_can_send(1 , &msg_rcv2);
	}*/
	/*
	//return;
	nn++;
	//if(nn<10) return;
	nn=0;
	msg_tst.rtr=0;
	msg_tst.len=8;
	msg_tst2.rtr=0;
	msg_tst2.len=8;
	
	//if(Test.pr == 0x31)
	{
		Test.pr = 0;
	if(f_can_send(0 , &msg_tst ) == 0)
	{
		msg_tst.cob_id++;
		msg_tst.cob_id &=0x3FF;
		msg_tst.data[0]++;
		
		if(msg_tst.data[0]==0)
		{
			msg_tst.data[1]++;
			if(msg_tst.data[1]==0)
			{
				msg_tst.data[2]++;
				if(msg_tst.data[2]==0)
				{
					msg_tst.data[3]++;
					if(msg_tst.data[3]==0)
					{
						msg_tst.data[4]++;
						if(msg_tst.data[4]==0)
						{
							msg_tst.data[5]++;
							if(msg_tst.data[5]==0)
							{
								msg_tst.data[6]++;
								if(msg_tst.data[6]==0)
								{
									msg_tst.data[7]++;
								}
							}
						}
					}
				}
			}
		}
	}
	}
	//if(Test.pr == 0x32)
	{
		Test.pr = 0;
	if(f_can_send(1 , &msg_tst2 ) == 0)
	{
		msg_tst2.cob_id++;
		msg_tst2.cob_id &=0x3FF;
		msg_tst2.data[0]++;
		if(msg_tst2.data[0]==0)
		{
			msg_tst2.data[1]++;
			if(msg_tst2.data[1]==0)
			{
				msg_tst2.data[2]++;
				if(msg_tst2.data[2]==0)
				{
					msg_tst2.data[3]++;
					if(msg_tst2.data[3]==0)
					{
						msg_tst2.data[4]++;
						if(msg_tst2.data[4]==0)
						{
							msg_tst2.data[5]++;
							if(msg_tst2.data[5]==0)
							{
								msg_tst2.data[6]++;
								if(msg_tst2.data[6]==0)
								{
									msg_tst2.data[7]++;
								}
							}
						}
					}
				}
			}
		}
	}
}*/
}
//-------------------------------------------------------------------
#endif
