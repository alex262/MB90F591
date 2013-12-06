#include "mb90590.h"
#include "wrdcpy.h"
#include "can.h"
#include "flash.h"
#include "candriver.h"

//TCAN_BUFF Can_Buff[2];
#pragma section CODE=CAN, attr=CODE,locate=0xF97000
#pragma section FAR_CODE=CAN, attr=CODE,locate=0xF97000

unsigned char CNTL_OUTBOX;

unsigned short BitMasks[16] = {0x0001, 0x0002, 0x0004,		// ������ ������������ ��� ������� ��������� �����
							   0x0008, 0x0010, 0x0020,		// � ���������� ���� int
							   0x0040, 0x0080, 0x0100,
							   0x0200, 0x0400, 0x0800,
							   0x1000, 0x2000, 0x4000, 0x8000};

unsigned short BitMasksInv[16] = {0xFFFE, 0xFFFD, 0xFFFB,	// ������ ������������ ��� ������� ������� ����� 
								  0xFFF7, 0xFFEF, 0xFFDF,	// � ���������� ���� int
								  0xFFBF, 0xFF7F, 0xFEFF,
								  0xFDFF, 0xFBFF, 0xF7FF,
								  0xEFFF, 0xDFFF, 0xBFFF, 0x7FFF};	

unsigned char bytes2word[] = {0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8, // ������ ������������ � ��������� word_copy
							  9,9,10,10,11,11,12,12,13,13,14,14,
							  15,15,16,16,17,17,18,18,19,19,20,20,
							  21,21,22,22,23,23,24,24,25,25,26,26,27,27,28,28};

unsigned char box_type[2][16];		// ������ ����� ������

//---------------------------------------------------------------------------------------------------------
// ��	� �   �	  � ���	 �   � �   � �	 �� 
//   � : 
//     box -  �� �   ��	
//     masktype	-  �  �	��� (��. � ��  �  Fujitsu)
void set_boxmask_0(unsigned char box, unsigned char masktype)
{
	unsigned char _pos;
	_pos = box*2;
	AMSR0&=~(unsigned long)(0x3<<_pos);
	AMSR0|=(unsigned long)(masktype)<<_pos;	
}
void set_boxmask_1(unsigned char box, unsigned char masktype)
{
	unsigned char _pos;
	_pos = box*2;
	AMSR1&=~(unsigned long)(0x3<<_pos);
	AMSR1|=(unsigned long)(masktype)<<_pos;	
}


//---------------------------------------------------------------------------------------------------------
//  � ��  ����	 �    �� 
//   � :
//		box -  �� �   �� 
//		boxtype	-  �	�� 
//		dir -	 �  �  �    ��	
//		id - �	  ����	�� ���	  � 
//		masktype -  �  � ���
//-------CAN0----------	
void configure_msgbox_0(unsigned char box, unsigned char boxtype, unsigned char	dir, unsigned int id, unsigned char masktype){
	unsigned short bitmask;
	bitmask	= BitMasks[box]; 
	
	IDR0(box) = id;								//  �	� �  �	  ����	��    �� 
	box_type[0][box]	= boxtype;					// � �	 �  �	�     ��    � ���    � �    ���	
	set_boxmask_0(box,masktype);				//  �	� �   �	  � ���	

	switch (dir){
		case MSGBOX_RX:							//    �	 �  �	 ��  -	�� �
			RIER0|=bitmask;						// �  �	   �   � ��   �	     ��	�
			TIER0&=~bitmask;					//    �	   � ��	  �	  �	
			RFWTR0&=~bitmask;					// � ���   �  ���   �	  �   �	    ���� 
			TREQR0&=~bitmask;					// � ��	�     ���	�     
			BVALR0|=bitmask;
		break;
		case MSGBOX_TX:							//    �	�  �	��  -	�     
			TIER0|=bitmask;						// �  �	   �   � ��   �	      �	    
			RIER0&=~bitmask;					//    �	   � ��	  �	 �� �
			RFWTR0&=~bitmask;					// � ���   �  ���   �	  �   �	 ��  ��	
			TREQR0&=~bitmask;					// � ��	�     ���	�     
			BVALR0&=~bitmask;
			if (CNTL_OUTBOX==0xFF) CNTL_OUTBOX=box;	
		break;
		case MSGBOX_RF:							//    �	 �  �	 ��  -	�� �	�   �  ��  �� 
			TIER0|=bitmask;						// �  �	   �   � �    �	      �	    
			RIER0&=~bitmask;					//    �	   � ��	  �	 �� �
			RFWTR0|=bitmask;					//  ���	  �  ���   �	 �   �	��  ��	
			TREQR0|=bitmask;					//  �	� �	���	  �	
			BVALR0|=bitmask;
		break;
	}
}
//-------CAN1----------	
void configure_msgbox_1(unsigned char box, unsigned char boxtype, unsigned char	dir, unsigned int id, unsigned char masktype){
	unsigned short bitmask;	
	bitmask	= BitMasks[box]; 

	IDR1(box) = id;								//  �	� �  �	  ����	��    �� 
	box_type[1][box]	= boxtype;					// � �	 �  �	�     ��    � ���    � �    ���	
	set_boxmask_1(box,masktype);				//  �	� �   �	  � ���	

	switch (dir){
		case MSGBOX_RX:							//    �	 �  �	 ��  -	�� �
			RIER1|=bitmask;						// �  �	   �   � ��   �	     ��	�
			TIER1&=~bitmask;					//    �	   � ��	  �	  �	
			RFWTR1&=~bitmask;					// � ���   �  ���   �	  �   �	    ���� 
			TREQR1&=~bitmask;					// � ��	�     ���	�     
			BVALR1|=bitmask;
		break;
		case MSGBOX_TX:							//    �	�  �	��  -	�     
			TIER1|=bitmask;						// �  �	   �   � ��   �	      �	    
			RIER1&=~bitmask;					//    �	   � ��	  �	 �� �
			RFWTR1&=~bitmask;					// � ���   �  ���   �	  �   �	 ��  ��	
			TREQR1&=~bitmask;					// � ��	�     ���	�     
			BVALR1&=~bitmask;
			if (CNTL_OUTBOX==0xFF) CNTL_OUTBOX=box;	
		break;
		case MSGBOX_RF:							//    �	 �  �	 ��  -	�� �	�   �  ��  �� 
			TIER1|=bitmask;						// �  �	   �   � �    �	      �	    
			RIER1&=~bitmask;					//    �	   � ��	  �	 �� �
			RFWTR1|=bitmask;					//  ���	  �  ���   �	 �   �	��  ��	
			TREQR1|=bitmask;					//  �	� �	���	  �	
			BVALR1|=bitmask;
		break;
	}
}
//---------------------------------------------------------------------------------------------------------
//  ��	  �  � � � ��	�� CAN ��  ����	� 
//-------CAN0----------	
void setup_can0(unsigned char speed)
{
//	unsigned int standart_id;
//	unsigned int broadcast_id;
	BYTE i,msg[8];
	
	if(speed==0) return;
	
    CAN0_DRX = 0;						// �� ��  ����	 �   ��	�    �	/ � �	CAN ��	���� �	
	CAN0_DTX = 1;
	CAN0_TX	= 1;
	CSR0=CSRHALT;						// � ���   �  CAN ��  ���� � 

    while (!CSR0_HALT);					// ���	 �  �	��    

	switch (speed)
	{						//	�  ������ � � �	  
		case 0:	BTR0 = BIT_TIMING_10;break;
		case 1:	BTR0 = BIT_TIMING_20;break;
		case 2:	BTR0 = BIT_TIMING_62;break;
		case 3:	BTR0 = BIT_TIMING_125;break;
		case 4:	BTR0 = BIT_TIMING_250;break;
		case 5:	BTR0 = BIT_TIMING_500;break;
		case 6:	BTR0 = BIT_TIMING_800;break;
		case 7:	BTR0 = BIT_TIMING_1000;break;
		default:return; 
	}
//-------------------------- � ����    ���� ��	�   ����  CAN ---------------------------------	

//	RTEC0_TEC = 0x0;						// � ��� � � ��	  �    �
//	RTEC0_REC = 0x0;						// � ��� � � ��	 �� � 
	IDER0  = 0x0000;							//	�   � �	 �� ���	  ��  �	   ����	 ���  -	11  � 
	RFWTR0 = 0x0000;						// �� ��  ����	 �    ���      �� �    �   �  ��  �� 
	TCANR0 = 0x0000;						// � ��� ��  �	" � �	�  �� �	    � "	
	RCR0   = 0x0000;						// � ��� ��  �	" �� �	   �   "
	TCR0   = 0x0000;						// � ��� ��  �	"  �	      �	   "
	ROVRR0 = 0x0000;						// � ��� ��  �	"  �  ��   �	� � "
	AMSR0  = 0x00000000;					//  � �� � ���	

	SET_MASK_00(0x7E0);		//	�  � ���  �  �	� �   �� �  �	 ����  ��� 
	SET_MASK_01(0);//broadcast_mask();			//	�  � ���  �   �����	 �� �  �    ����  ��� 

	BVALR0 = 0x0000;						// � ���   �   �     ��� 
	TREQR0 = 0x0000;

	// � �	 �  �	�   �  � �   ��	�  �  �����	 �� �  �    ����  ��� 
//	broadcast_id = 101;
//	standart_id = 100;
//---------------------------------------------------------
	
	for(i=0;i<8;i++)
		msg[i]=0xFF;
	for(i=0;i<16;i++)
	{
		word_copy(DTR0_WPTR(i),msg,8);
		IDRX0(i) = SET_ID(0xFFF);				//	�  �	����  ��    ��	
		DLCR0(i) = 0xF;	
		if(i<BOX_FOR_RCV_MSG)
		{
		/*	if(i == 0)
				configure_msgbox_0(0	,	CANMSG_MINE,	MSGBOX_RX	,	(DWORD)SET_ID(NMT<<7)	,	MASK_COMPARE);
			if(i == 1)
				configure_msgbox_0(1	,	CANMSG_MINE,	MSGBOX_RX	,	(DWORD)SET_ID(SYNC<<7)	,	MASK_COMPARE);
			if(i > 1)
				configure_msgbox_0(i	,	CANMSG_MINE,	MSGBOX_RX	,	(DWORD)SET_ID(getNodeId()),	MASK_ACCEPT1);
		*/
			#ifdef CAN_OPEN_ENABLE
				if(i == 0)
					configure_msgbox_0(0	,	CANMSG_MINE,		MSGBOX_RX	,	SET_ID(NMT<<7)	    ,	MASK_COMPARE);
				if(i == 1)
					configure_msgbox_0(1	,	CANMSG_MINE,		MSGBOX_RX	,	SET_ID(SYNC<<7)	,	MASK_COMPARE);
				if(i > 1)
					configure_msgbox_0(i	,	CANMSG_MINE,		MSGBOX_RX	,	SET_ID(getNodeId()),	MASK_ACCEPT1);
			#else
				configure_msgbox_0(i	,	CANMSG_MINE,		MSGBOX_RX	,	(DWORD)0,	MASK_IGNORE);
    		#endif
		}	
		else
		{
			configure_msgbox_0(i	,	CANMSG_TRANSMIT,	MSGBOX_TX	,	(DWORD)0xFFFF			,	MASK_COMPARE);
		}
	}
// ----------------------------	 � ��  ����   �	   ���	----------------------------------------
/*	configure_msgbox_0(0	,	CANMSG_MINE,		MSGBOX_RX	,	(DWORD)SET_ID(NMT<<7)	,	MASK_COMPARE);
	configure_msgbox_0(1	,	CANMSG_MINE,		MSGBOX_RX	,	(DWORD)SET_ID(SYNC<<7)	,	MASK_COMPARE);
	//configure_msgbox_0(2	,	CANMSG_MINE,		MSGBOX_RX	,	(DWORD)SET_ID(TIME_STAMP<<5),MASK_COMPARE);
	
	configure_msgbox_0(2	,	CANMSG_MINE,		MSGBOX_RX	,	(DWORD)SET_ID(getNodeId()),	MASK_ACCEPT1);
	configure_msgbox_0(3	,	CANMSG_MINE,		MSGBOX_RX	,	(DWORD)SET_ID(getNodeId()),	MASK_ACCEPT1);
	configure_msgbox_0(4	,	CANMSG_MINE,		MSGBOX_RX	,	(DWORD)SET_ID(getNodeId()),	MASK_ACCEPT1);
	configure_msgbox_0(5	,	CANMSG_MINE,		MSGBOX_RX	,	(DWORD)SET_ID(getNodeId()),	MASK_ACCEPT1);
	configure_msgbox_0(6	,	CANMSG_MINE,		MSGBOX_RX	,	(DWORD)SET_ID(getNodeId()),	MASK_ACCEPT1);
	configure_msgbox_0(7	,	CANMSG_MINE,		MSGBOX_RX	,	(DWORD)SET_ID(getNodeId()),	MASK_ACCEPT1);
	configure_msgbox_0(8	,	CANMSG_MINE,		MSGBOX_RX	,	(DWORD)SET_ID(getNodeId()),	MASK_ACCEPT1);
	configure_msgbox_0(9	,	CANMSG_MINE,		MSGBOX_RX	,	(DWORD)SET_ID(getNodeId()),	MASK_ACCEPT1);
	
	configure_msgbox_0(10	,	CANMSG_TRANSMIT,	MSGBOX_TX	,	(DWORD)0xFFFF			,	MASK_COMPARE);
	configure_msgbox_0(11	,	CANMSG_TRANSMIT,	MSGBOX_TX	,	(DWORD)0xFFFF			,	MASK_COMPARE);
	configure_msgbox_0(12	,	CANMSG_TRANSMIT,	MSGBOX_TX	,	(DWORD)0xFFFF			,	MASK_COMPARE);
	configure_msgbox_0(13	,	CANMSG_TRANSMIT,	MSGBOX_TX	,	(DWORD)0xFFFF			,	MASK_COMPARE);
	configure_msgbox_0(14	,	CANMSG_TRANSMIT,	MSGBOX_TX	,	(DWORD)0xFFFF			,	MASK_COMPARE);
	configure_msgbox_0(15	,	CANMSG_TRANSMIT,	MSGBOX_TX	,	(DWORD)0xFFFF			,	MASK_COMPARE);
	*/
	CSR0=CSRRUN;									//     �� CAN ��  ���� � 

//	program.can_txtimeout=0;						// � ���  ��� �	   �����     � ��     �		�� � �	 �	
//	program.can_rxtimeout=0;
//	program.can_timeout = 0;
		
	//settings.can_timeout = get_timeout(speed);	// � �	 �  �	 �� � �	   �	     ��	� �   �	    

	while (CSR0_HALT);								// ���	 �   � �  �� � CAN ��  ���� � 
}
//------------CAN1------------
void setup_can1(unsigned char speed){
//	unsigned int standart_id;
//	unsigned int broadcast_id;
	BYTE i,msg[8];
	
	if(speed==0) return;
	
	CAN1_DRX = 0;						// �� ��  ����	 �   ��	�    �	/ � �	CAN ��	���� �	
	CAN1_DTX = 1;
	CAN1_TX	= 1;
	CSR1=CSRHALT;						// � ���   �  CAN ��  ���� � 

    	while (!CSR1_HALT);					// ���	 �  �	��    

	switch (speed)						//	�  ������ � � �	  
	{
		case 0:	BTR1 = BIT_TIMING_10;break;
		case 1:	BTR1 = BIT_TIMING_20;break;
		case 2:	BTR1 = BIT_TIMING_62;break;
		case 3:	BTR1 = BIT_TIMING_125;break;
		case 4:	BTR1 = BIT_TIMING_250;break;
		case 5:	BTR1 = BIT_TIMING_500;break;
		case 6:	BTR1 = BIT_TIMING_800;break;
		case 7:	BTR1 = BIT_TIMING_1000;break;
		default:return;
	}
//-------------------------- � ����    ���� ��	�   ����  CAN ---------------------------------	

//	RTEC1_TEC = 0x0;						// � ��� � � ��	  �    �
//	RTEC1_REC = 0x0;						// � ��� � � ��	 �� � 

    IDER1 = 0x0000;						//	�   � �	 �� ���	  ��  �	   ����	 ���  -	11  � 

	RFWTR1 = 0x0000;						// �� ��  ����	 �    ���      �� �    �   �  ��  �� 
	TCANR1 = 0x0000;						// � ��� ��  �	" � �	�  �� �	    � "	
	RCR1   = 0x0000;						// � ��� ��  �	" �� �	   �   "
	TCR1   = 0x0000;						// � ��� ��  �	"  �	      �	   "
	ROVRR1 = 0x0000;						// � ��� ��  �	"  �  ��   �	� � "
    AMSR1  = 0x00000000;					//  � �� � ���	

    SET_MASK_10(0x7E0);		//	�  � ���  �  �	� �   �� �  �	 ����  ��� 
	SET_MASK_11(0);					//	�  � ���  �   �����	 �� �  �    ����  ��� 

    BVALR1 = 0x0000;						// � ���   �   �     ��� 
	TREQR1 = 0x0000;

	// � �	 �  �	�   �  � �   ��	�  �  �����	 �� �  �    ����  ��� 
//	broadcast_id = 101;
//	standart_id = 100;
	//--------------------------------
	for(i=0;i<8;i++)
		msg[i]=0xFF;
	for(i=0;i<16;i++)
	{
		word_copy(DTR1_WPTR(i),msg,8);
		IDRX1(i) = SET_ID(0xFFF);				//	�  �	����  ��    ��	
		DLCR1(i) = 0xF;
		if(i<BOX_FOR_RCV_MSG)
		{
			/*if(i == 0)
				configure_msgbox_1(0	,	CANMSG_MINE,	MSGBOX_RX	,	(DWORD)SET_ID(NMT<<7)	,	MASK_COMPARE);
			if(i == 1)
				configure_msgbox_1(1	,	CANMSG_MINE,	MSGBOX_RX	,	(DWORD)SET_ID(SYNC<<7)	,	MASK_COMPARE);
			if(i > 1)
				configure_msgbox_1(i	,	CANMSG_MINE,	MSGBOX_RX	,	(DWORD)SET_ID(getNodeId()),	MASK_ACCEPT1);
			*/
			#ifdef CAN_OPEN_ENABLE
				if(i == 0)
					configure_msgbox_1(0	,	CANMSG_MINE,		MSGBOX_RX	,	SET_ID(NMT<<7)	    ,	MASK_COMPARE);
				if(i == 1)
					configure_msgbox_1(1	,	CANMSG_MINE,		MSGBOX_RX	,	SET_ID(SYNC<<7)	,	MASK_COMPARE);
				if(i > 1)
					configure_msgbox_1(i	,	CANMSG_MINE,		MSGBOX_RX	,	SET_ID(getNodeId()),	MASK_ACCEPT1);
			#else
				configure_msgbox_1(i	,	CANMSG_MINE,		MSGBOX_RX	,	(DWORD)0,	MASK_IGNORE);
    		#endif
		}	
		else
		{
			configure_msgbox_1(i	,	CANMSG_TRANSMIT,	MSGBOX_TX	,	(DWORD)0xFFFF			,	MASK_COMPARE);
		}	
	}
// ----------------------------	 � ��  ����   �	   ���	----------------------------------------
/*	configure_msgbox_1(0	,	CANMSG_MINE,		MSGBOX_RX	,	(DWORD)SET_ID(NMT<<7)	,	MASK_COMPARE);
	configure_msgbox_1(1	,	CANMSG_MINE,		MSGBOX_RX	,	(DWORD)SET_ID(SYNC<<7)	,	MASK_COMPARE);
	//configure_msgbox_1(2	,	CANMSG_MINE,		MSGBOX_RX	,	(DWORD)SET_ID(TIME_STAMP<<7),MASK_COMPARE);
	
	configure_msgbox_1(2	,	CANMSG_MINE,		MSGBOX_RX	,	(DWORD)SET_ID(getNodeId()),	MASK_ACCEPT1);
	configure_msgbox_1(3	,	CANMSG_MINE,		MSGBOX_RX	,	(DWORD)SET_ID(getNodeId()),	MASK_ACCEPT1);//MASK_ACCEPT1);
	configure_msgbox_1(4	,	CANMSG_MINE,		MSGBOX_RX	,	(DWORD)SET_ID(getNodeId()),	MASK_ACCEPT1);//MASK_ACCEPT1);
	configure_msgbox_1(5	,	CANMSG_MINE,		MSGBOX_RX	,	(DWORD)SET_ID(getNodeId()),	MASK_ACCEPT1);//MASK_ACCEPT1);
	configure_msgbox_1(6	,	CANMSG_MINE,		MSGBOX_RX	,	(DWORD)SET_ID(getNodeId()),	MASK_ACCEPT1);//MASK_ACCEPT1);
	configure_msgbox_1(7	,	CANMSG_MINE,		MSGBOX_RX	,	(DWORD)SET_ID(getNodeId()),	MASK_ACCEPT1);//MASK_ACCEPT1);
	configure_msgbox_1(8	,	CANMSG_MINE,		MSGBOX_RX	,	(DWORD)SET_ID(getNodeId()),	MASK_ACCEPT1);//MASK_ACCEPT1);
	configure_msgbox_1(9	,	CANMSG_MINE,		MSGBOX_RX	,	(DWORD)SET_ID(getNodeId()),	MASK_ACCEPT1);
	
	configure_msgbox_1(10	,	CANMSG_TRANSMIT,	MSGBOX_TX	,	(DWORD)0xFFFF			,	MASK_COMPARE);
	configure_msgbox_1(11	,	CANMSG_TRANSMIT,	MSGBOX_TX	,	(DWORD)0xFFFF			,	MASK_COMPARE);
	configure_msgbox_1(12	,	CANMSG_TRANSMIT,	MSGBOX_TX	,	(DWORD)0xFFFF,				MASK_COMPARE);
	configure_msgbox_1(13	,	CANMSG_TRANSMIT,	MSGBOX_TX	,	(DWORD)0xFFFF			,	MASK_COMPARE);
	configure_msgbox_1(14	,	CANMSG_TRANSMIT,	MSGBOX_TX	,	(DWORD)0xFFFF			,	MASK_COMPARE);
	configure_msgbox_1(15	,	CANMSG_TRANSMIT,	MSGBOX_TX	,	(DWORD)0xFFFF			,	MASK_COMPARE);
	*/		
	CSR1=CSRRUN;									//     �� CAN ��  ���� � 

//	program.can_txtimeout=0;						// � ���  ��� �	   �����     � ��     �		�� � �	 �	
//	program.can_rxtimeout=0;
//	program.can_timeout = 0;
		
	//settings.can_timeout = get_timeout(speed);	// � �	 �  �	 �� � �	   �	     ��	� �   �	    

	while (CSR1_HALT);								// ���	 �   � �  �� � CAN ��  ���� � 
}
//---------------------------------------------------------------------------------------------------------
void SetupCAN(unsigned char speed_CAN0,unsigned	char speed_CAN1)
{
	setup_can0(speed_CAN0);	
	setup_can1(speed_CAN1);	
}

BYTE GetCan0Data (BYTE	box, BYTE *BufPtr)
{
  	BYTE Len, pos;
    
  	//*BufPtr++ =	
  	Len =	DLCR0(box);
  	for (pos=0; pos<=Len;pos++)
    		*BufPtr++ =	DTR0_BYTE(box, pos);
  	return (Len);	
}

BYTE GetCan1Data (BYTE	box, BYTE *BufPtr)
{
  	BYTE Len, pos;
    
  	//*BufPtr++ =	
  	Len =	DLCR1(box);
  	for (pos=0; pos<=Len;pos++)
    		*BufPtr++ =	DTR1_BYTE(box, pos);
  	return (Len);	
}
//---------------------------------------------------------------------------------------------------------
//   �	    ���	   �   � CAN0
//   � : 
//    box -   ��
//	  id - �    ����  �� ���    � 
//	  dlc -	 ��    ���    �	 (0..8)	
//	  msg -	 �     ��      �� ���	 � 

BYTE can_transmit_0(TSendMsgInfo *pSendMsgInfo)	
{
	unsigned int mask;
	
	mask = BitMasks[pSendMsgInfo->box];
	if((TREQR0&mask)!=0) return 1;
	BVALR0 &= ~mask;						// � ���   �	�� 

	IDRX0(pSendMsgInfo->box) = SET_ID(pSendMsgInfo->id);				//	�  �	����  ��    ��	
	DLCR0(pSendMsgInfo->box) = pSendMsgInfo->dlc;						//	�   ��	� ���	 � 
										
	word_copy(DTR0_WPTR(pSendMsgInfo->box),	pSendMsgInfo->msg, pSendMsgInfo->dlc);	// �� ���   �  ���    �	
	BVALR0 |= mask;							//  ���	  �    �� 
	TREQR0 |= mask;							//  �	� �	���	  �	
	return 0;
//	program.can_txtimeout =	settings.can_timeout;//	    ��	  � �	  �	
}

BYTE can_transmit_1(TSendMsgInfo *pSendMsgInfo)	
{
	unsigned int mask;
	mask = BitMasks[pSendMsgInfo->box];
	
	if((TREQR1&mask)!=0) return 1;
	BVALR1 &= ~mask;						// � ���   �	�� 
	IDRX1(pSendMsgInfo->box) = SET_ID(pSendMsgInfo->id);				//	�  �	����  ��    ��	
	DLCR1(pSendMsgInfo->box) = pSendMsgInfo->dlc;						//	�   ��	� ���	 � 
										
	word_copy(DTR1_WPTR(pSendMsgInfo->box),	pSendMsgInfo->msg, pSendMsgInfo->dlc);	// �� ���   �  ���    �	

	BVALR1 |= mask;							//  ���	  �    �� 
	TREQR1 |= mask;							//  �	� �	���	  �	
	return 0;
//	program.can_txtimeout =	settings.can_timeout;//	    ��	  � �	  �	
}
//---------------------------------------------------------------------------------------------------------
// � �	�  ��  � ��   �	 CAN0 ��  ���� �  -   �		 � 
//
//#pragma register(2)
/*__nosavereg */
__interrupt void onCANTransmit_0(void)
{
	WORD bvalr;							//  � �	       � �	
	WORD tcr;	

	if (CSR0_NT || (RTEC0_TEC>127) || (RTEC0_REC>127)) 
	{																			// �   � �    �	� ��   �  �
		CSR0_NT	= 0;
		if ((CSR0_NS == 3) || (CSR0_NS == 2))
		{																	// ��� �  �  �	� - BUSOFF
			puts("0TReset\n\r");
			CSR0_HALT=1;						// � ���   �  CAN ��  ���� � 
			while (!CSR0_HALT);	
			TREQR0 = 0;
			TCANR0 = 0xFFFF;
			RCR0 = 0;
			TCR0 = 0;
			CSR0=CSRRUN;
			while (CSR0_HALT);	
		}
	}
//	if (TREQR1==0)	
//		program.can_txtimeout =	0; else			//   �	     �	 ���	�      �     - � ���   �     � �     �	  
//		program.can_txtimeout =	settings.can_timeout;
	tcr=TCR0;
	TCR0&=~tcr;
	bvalr=BVALR0;								// � ���   �	���  � �� ���	���   �	   �	 � 
	bvalr&=~tcr;
	BVALR0=bvalr;
__DI();
	SendFifoCanMsg(0);
__EI();
}
//#pragma __nosavereg
__interrupt void onCANTransmit_1(void)
{
	WORD bvalr;							//  � �	       � �	
	WORD tcr;
//	unsigned int trec;	

	if (CSR1_NT || (RTEC1_TEC>127) || (RTEC1_REC>127)) 
	{																			// �   � �    �	� ��   �  �
		CSR1_NT	= 0;
		if ((CSR1_NS == 3) || (CSR1_NS == 2))
		{																	// ��� �  �  �	� - BUSOFF
			puts("1TReset\n\r");
			CSR1_HALT=1;						// � ���   �  CAN ��  ���� � 
			while (!CSR1_HALT);	
			TREQR1 = 0;
			TCANR1 = 0xFFFF;
			RCR1 = 0;
			TCR1 = 0;
			CSR1=CSRRUN;
			while (CSR1_HALT);	
		}
	}
//	if (TREQR1==0)	
//		program.can_txtimeout =	0; else			//   �	     �	 ���	�      �     - � ���   �     � �     �	  
//		program.can_txtimeout =	settings.can_timeout;

	tcr=TCR1;
	TCR1&=~tcr;
	bvalr=BVALR1;								// � ���   �	���  � �� ���	���   �	   �	 � 
	bvalr&=~tcr;
	BVALR1=bvalr;
__DI();
	SendFifoCanMsg(1);
__EI();
}


// � �	�  ��  � ��   �	 �  CAN	��  ���� �  -  �� �	� /���	  � 

__interrupt void onCANReceive_0(void)
{
	unsigned char box;							//  � �	       � �	- �    ��   ���	
//__DI();	
	if (ROVRR0)
	{								//  ���	� ��   �  ��   �    � �	
		ROVRR0 = 0;
		puts("0Rovr\n\r");
	}
	for (box=0; box<BOX_FOR_RCV_MSG; box++)						// � �	 �  �  � � �� �	����  �	  ��	  � ���	   � 
	{
		if (RCR0==0) break;
		if (!(RCR0 & BitMasks[box])) continue;
		//------------------------------------------------------------------------------------------------------
		//FastRcvMsg(0,box);
		canRcvHardMB90591(0,box);
		//------------------------------------------------------------------------------------------------------
		RCR0=BitMasksInv[box];						
		//RRTRR0&=BitMasksInv[box];										
	}	// for
	program.TimerCan0=0;
	//__DI();
	#ifdef CAN_OPEN_ENABLE	
		receiveMsgHandler(0);
	#endif
	//__EI();	
}			// ��	 � �  �	 ��   �	��   �	
 __interrupt void onCANReceive_1(void)
{
	unsigned char box;
//	unsigned char msg[8];
//	unsigned short id;																		//  � �	       � �	- �    ��   ���	
//__DI();
	if (ROVRR1)
	{								//  ���	� ��   �  ��   �    � �	
		ROVRR1 = 0;
		puts("1Rovr\n\r");
	}
	for (box=0; box<BOX_FOR_RCV_MSG; box++)						// � �	 �  �  � � �� �	����  �	  ��	  � ���	   � 
	{
		if (RCR1==0) break;
		if (!(RCR1 & BitMasks[box])) continue;
		//------------------------------------------------------------------------------------------------------
		//FastRcvMsg(1,box);
		canRcvHardMB90591(1,box);		
		//------------------------------------------------------------------------------------------------------
		RCR1=BitMasksInv[box];						
		//RRTRR1&=BitMasksInv[box];			//O � �								
	}	
	program.TimerCan1=0;	
	//__DI();	
	#ifdef CAN_OPEN_ENABLE
		receiveMsgHandler(1);
	#endif
	//__EI();	
	// for
}			// ��	 � �  �	 ��   �	��   �	


//===========================================================================
