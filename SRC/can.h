#ifndef __CAN
#define __CAN
#include "global.h"
#include "applicfg.h"
//------------------------- зарегистрированные скорости CAN -----------------------------------
#define BIT_TIMING_10	0x7FFF
#define BIT_TIMING_20	0x7FDF
#define BIT_TIMING_62	0x498F
#define BIT_TIMING_125	0x4987
#define BIT_TIMING_250	0x4983
#define BIT_TIMING_500	0x4981
#define BIT_TIMING_800	0x5CC0
#define BIT_TIMING_1000	0x4980

#define CAN_10 		0
#define CAN_20 		1
#define CAN_62 		2
#define CAN_125 	3
#define CAN_250		4
#define CAN_500		5
#define CAN_800		6
#define CAN_1000	7
//------------------------------- Порты CAN контроллера -----------------------------------
#define CAN0_DRX	DDR9_D91		 // CAN0 RX
#define CAN0_TX		PDR9_P90		 // CAN0 TX
#define CAN0_DTX	DDR9_D90		 // CAN0 TX

#define CAN1_DRX	DDR1_D14		 // CAN1 RX
#define CAN1_TX		PDR1_P15		 // CAN1 TX
#define CAN1_DTX	DDR1_D15		 // CAN1 TX


#define CSRHALT		0x0081			 // служебные CAN флаги
#define CSRRUN		0x0084 			 // служебные CAN флаги
#define CSROFF		0x0001			 // служебные CAN флаги
//------------------------------------------------------------------------------------------
//------------------------------- Типы масок идентификаторов ----------------------------------
#define MASK_COMPARE		0x0			// побитное сравнение
#define MASK_IGNORE			0x1			// не сравнивать
#define MASK_ACCEPT1		0x2			// использовать маску 1
#define MASK_ACCEPT2		0x3			// использовать маску 2

//------------------------------- Типы сообщений --------------------------
#define CANMSG_MINE			0x0			// индивидуальное сообщение
#define CANMSG_BROADCAST	0x1			// широковещательное сообщение
//------------------------------ Типы ящиков --------------------------------------
#define MSGBOX_RX			0x0			// Ящик для приема сообщений
#define MSGBOX_TX			0x1			// ящик для отправки сообщений
#define MSGBOX_RF			0x2			// ящик для приема удаленных фреймов
#define CANMSG_TRANSMIT		0x5			// сообщение на передачу

#define DIR_RX				0x0			// ящик приемник
#define DIR_TX				0x1			// ящик передатчик

//#define CAN_BUFF_SIZE		1






// конвертирование реального идентификатора в идентификатор контроллера
#define SET_ID(id) ( (((unsigned int)id<<13) & 0x0000E000) | (((unsigned int)id >> 3) & 0x000000FF) )

//#define GET_ID(id) ( (((unsigned int)id<<3) & 0x7f1) | (((unsigned int)id >> 5) & 0x00000007) )
#define GET_ID_0(box) (IDR0_ID0_2(box)|((unsigned int)IDR0_ID3_10(box)<<3))
#define GET_ID_1(box) (IDR1_ID0_2(box)|((unsigned int)IDR1_ID3_10(box)<<3))

#define SET_MASK_10(id) AMRX10_13_20=(unsigned long)id<<5;\
						AMRX10_21_28=(unsigned long)id>>3;\
						AMRX10_5_12 =0;\
						AMRX10_0_4=0;

						//AMRX10_0_4  =(unsigned long)id;\
						//AMRX10_13_20=(unsigned long)id>>13;\
						//AMRX10_5_12 =(unsigned long)id>>5;\
						//AMRX10_21_28=(unsigned long)id>>21;

#define SET_MASK_11(id) AMRX11_13_20=(unsigned long)id<<5;\
						AMRX11_21_28=(unsigned long)id>>3;\
						AMRX11_5_12 =0;\
						AMRX11_0_4=0;

						
						//AMRX11_0_4  =(unsigned long)id;\
						//AMRX11_13_20=(unsigned long)id>>13;\
						//AMRX11_5_12 =(unsigned long)id>>5;\
						//AMRX11_21_28=(unsigned long)id>>21;

#define SET_MASK_00(id) AMRX00_13_20=(unsigned long)id<<5;\
						AMRX00_21_28=(unsigned long)id>>3;\
						AMRX00_5_12 =0;\
						AMRX00_0_4=0;

						//AMRX00_0_4  =(unsigned long)id;\
						//AMRX00_13_20=(unsigned long)id>>13;\
						//AMRX00_5_12 =(unsigned long)id>>5;\
						//AMRX00_21_28=(unsigned long)id>>21;

#define SET_MASK_01(id) AMRX01_13_20=(unsigned long)id<<5;\
						AMRX01_21_28=(unsigned long)id>>3;\
						AMRX11_5_12 =0;\
						AMRX11_0_4=0;

						//AMRX01_0_4  =(unsigned long)id;\
						//AMRX01_13_20=(unsigned long)id>>13;\
						//AMRX01_5_12 =(unsigned long)id>>5;\
						//AMRX01_21_28=(unsigned long)id>>21;

extern unsigned char bytes2word[];
// копирование буферов пословно
#define word_copy(_dst,_src,_count) wrdcpyNN((unsigned short *)_dst, (unsigned short *)_src, bytes2word[_count])




typedef struct
{
	unsigned int id;
	unsigned char box;
	unsigned char dlc;
	unsigned char *msg;
	
}TSendMsgInfo;

typedef struct 
{
  WORD w; // 32 bits
} SHORT_CAN;

/** Can message structure */
struct s_Message  
{
  UNS32 cob_id;	// l'ID du mesg
  UNS8 rtr;				// remote transmission request. 0 if not rtr, 
                        // 1 for a rtr message
  UNS8 len;				// message length (0 to 8)
  UNS8 data[8];  		// data 
};
typedef struct s_Message Message;


BYTE can_transmit_0(TSendMsgInfo *pSendMsgInfo);
BYTE can_transmit_1(TSendMsgInfo *pSendMsgInfo);
BYTE GetCan0Data (BYTE  box, BYTE *BufPtr);
BYTE GetCan1Data (BYTE  box, BYTE *BufPtr);
extern unsigned short BitMasks[16];
extern unsigned short BitMasksInv[16];
extern unsigned char box_type[2][16];
//extern TCAN_BUFF Can_Buff[2];
#endif