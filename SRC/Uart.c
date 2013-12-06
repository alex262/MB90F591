#include "mb90590.h"
#include "sio.h"
#include "global.h" 
#include "Uart.h"
#include INCLUDE_H
								
BYTE nOurID = 0;	//НАШ ID
void GetPak_Uart(BYTE ch);
/*=====================================================================*/
                      /* initialize UART 0 */
/*=====================================================================*/

void InitUART_0(void)
{
    URD0 = 0x0C;            /*  0010 1100   set baud rate */ //    7c
                            //19230/38460
    UMC0 = 0x19;            /* 00011001  select Mode1, 8 Data bits  
                            select asynchr. Start/Stop transfer 
                             Enable Uart0 outputs                 */
    USR0_RIE  =1;           /*Разрешить прерывание на приём информации */
}
/*---------------------------- initialize UART 1-------------------------- */
void InitUART_1(void)
{
    URD1 = 0x7C;          /*  01111100   set baud rate */     
                          /* Baud rate to 115000 */ 
    UMC1 = 0x19;          // 00011001  select Mode1, 8 Data bits 
                         // select asynchr. Start/Stop transfer 
    USR1_RIE  =1;        /*Разрешить прерывание на приём информации */
}
/*---------------------------- initialize UART 2-------------------------- */
void InitUART_2(void)
{
    URD2 = 0x7C;          /*  01111100   set baud rate */     
                          /*Baud rate to 115000 */
    UMC2 = 0x19;          // 00011001  select Mode1, 8 Data bits 
                          //select asynchr. Start/Stop transfer 
    USR2_RIE  =1;        //Разрешить прерывание на приём информации 
}
//--------------------------------------------------------------------------------
void InitUART(void) 
{
    
    InitUART_0();
//  InitUART_1();
//  InitUART_2();
}
/* -----------------Загрузка символа в выходной буфер UART0-------------------*/

void Putch_N (BYTE N, BYTE ch)           /* sends a char */
{
    if(N==0)
    {
    	while (USR0_TDRE == 0); 
    	UODR0 = ch;                         /* put ch into buffer           */
    }
    if(N==1)
    {
    	while (USR1_TDRE == 0); 
    	UODR1 = ch;                         /* put ch into buffer           */
    }
    if(N==2)
    {
    	while (USR2_TDRE == 0); 
    	UODR2 = ch;                         /* put ch into buffer           */
    }
}

void Putch (unsigned char ch)           /* sends a char */
{
    while (USR0_TDRE == 0); 
    UODR0 = ch;                         /* put ch into buffer           */
}

/*--------------Посимвольная отправка в выходной буфер UART0---------------*/

void puts (unsigned char *Name2)    /* Puts a String to UART */ 
{
 char c;
 int i,len; 
 
  len = strlen(Name2);
    
 for (i=0; i<len; i++)              /* go through string */ 
  { 
    c=(Name2[i]);                   /* pick char */ 
    Putch (c);                      /* send it out */
  } 
}
/* -----------------Загрузка символа в выходной буфер UART1-------------------*/

void Putch1 (unsigned char ch)         /* sends a char */
{
    while (USR1_TDRE==0);   /* wait for transmit buffer empty   */
    UODR1 = ch;             /* put ch into buffer           */
}

/*--------------Посимвольная отправка в выходной буфер UART1---------------*/

void puts1 (unsigned char *Name2)   /* Puts a String to UART */ 
{
 char c;
 int i,len; 
 
  len = strlen(Name2);
    
 for (i=0; i<len; i++)  /* go through string */ 
  { 
    c=(Name2[i]);           /* pick char */ 
    Putch1 (c);         /* send it out */
  } 
}
/* -----------------Загрузка символа в выходной буфер UART2-------------------*/

void Putch2 (unsigned char ch)         /* sends a char */
{
    while (USR2_TDRE==0);   /* wait for transmit buffer empty   */
    UODR2 = ch;             /* put ch into buffer           */

}

/*--------------Посимвольная отправка в выходной буфер UART0---------------*/

void puts2 (unsigned char *Name2)   /* Puts a String to UART */ 
{
 char c;
 int i,len; 
 
  len = strlen(Name2);
    
 for (i=0; i<len; i++)  /* go through string */ 
  { 
    c=(Name2[i]);       /* pick char */ 
    Putch2 (c);         /* send it out */
  } 
}
//--------------------------------------------------------------------------------
/*=====================================================================*/
/*------------------ПРЕРЫВАНИЯ----------------------------------------- 
/*=====================================================================*/
/*------------------Приём символа по прерыванию-UART0----------------------*/
__interrupt void Getch0 (void)  /* interrupt function */
{ 
    unsigned char ch,ch_in; 
    
    if (USR0_ORFE||USR0_PE)     /* overrun error        */
    {
        ch = UIDR0;             /* reset error flags        */
        UMC0_RFC=0; 
    }
    else
    {
        ch_in = UIDR0;          /* Приём символа            */
        //Terminal(ch_in);
        #ifdef	PLATA_DAC9
        	if(program.N[0]<(BUFFER_LEN_UART-1))
				program.Pack_IN_[0][program.N[0]++]=ch_in;
			//GetPak_Uart(0);
        #endif
        #ifdef	PLATA_ADC
        	
        	if(program.N[0]<(BUFFER_LEN_UART-1))
				program.Pack_IN_[0][program.N[0]++]=ch_in;
        	//GetAndWriteTarirov(ch_in);
        #endif
        #ifdef	PLATA_AVV2C
        	GetAndWriteTarirov(ch_in);
        #endif
        #ifdef	PLATA_TEST
        	Test.pr = ch_in;
        #endif
		#ifdef	PLATA_DAC10
        	if(program.N[0]<(BUFFER_LEN_UART-1))
				program.Pack_IN_[0][program.N[0]++]=ch_in;
			//GetPak_Uart(0);
        #endif
        
    }
}
/*-----------------------------------------------------------------*/
/*---------------Приём символа по прерыванию--UART1----------------*/
__interrupt void Getch1 (void)  /* interrupt function */ 
{ 
    unsigned char ch,ch_in; 
    
    if (USR1_ORFE||USR1_PE)     /* overrun error        */
    {
        ch = UIDR1;             /* reset error flags        */
        UMC1_RFC=0; 
    }
    else
    {
        ch_in = UIDR1;          /* Приём символа            */
    }
}
/*==================================================================*/
/*------------------Приём символа по прерыванию----UART2------------*/
__interrupt void Getch2 (void)  /* interrupt function */
{ 
    unsigned char ch,ch_in; 
    
    if (USR2_ORFE||USR0_PE)     /* overrun error        */
    {
        ch = UIDR2;             /* reset error flags        */
        UMC2_RFC=0; 
    }
    else
    {
        ch_in = UIDR2;          /* Приём символа            */
    }
}/*==================================================================*/ 
// Подсчёт CRC
/*WORD CRC(BYTE *sBuf,WORD nLen )
{
	WORD nCRC = 0;
	WORD i;

	for( i = 0; i < nLen; i++ )
		nCRC += sBuf[i];
	return nCRC;
}*/
//=======================================================================
void Send_Pkt(BYTE nCH,BYTE *sDataBuf,WORD nLen,BYTE nReceiver,BYTE nCodOp)
{
	WORD nCRC,i;
	
	nCRC=nReceiver+(BYTE)((nLen)&0x00FF)+(BYTE)(((nLen)&0xFF00)>>8);
	nCRC+=nCodOp+nOurID+1;
	
	Putch_N(nCH,0x81);				//				[0]
	Putch_N(nCH,nReceiver);			//Кому			[1]
	Putch_N(nCH,nOurID);			//Наш адрес		[2]
	Putch_N(nCH,(BYTE)((nLen+1)&0x00FF));	//		[3]          
	Putch_N(nCH,(BYTE)(((nLen+1)&0xFF00)>>8));//	[4]   
    Putch_N(nCH,nCodOp);					//		[5]	

	for(i=0;i<nLen; i++)
	{
		Putch_N(nCH,sDataBuf[i]);			//		[6]
		clrwdt;
	}
	nCRC += CRC(sDataBuf,nLen);

	Putch_N(nCH,(BYTE)(nCRC&0x00FF));         	//	[nLen+6]
	Putch_N(nCH,(BYTE)((nCRC&0xFF00)>>8));  	//	[nLen+7]
	Putch_N(nCH,0x81);							//	[nLen+8]
	Putch_N(nCH,0x0);							//	[nLen+9]
}

//----------------------------
//Драйвер Uart1 Uart2
void GetPak_Uart(BYTE ch)
{
	//unsigned long time,tmp1;
	#ifdef PLATA_ADC
	TSendPakTar	*ptrSendPakTar;
	#endif
	#ifdef PLATA_ADC8
	TSendPakTar	*ptrSendPakTar;
	#endif
	unsigned int crc_p,i,j,crc,nDataLen,nLen;
	unsigned char *ptr, k;//,tmp,n;
	//------------------------------Обрабатываются входящие пакеты------------------------	
	//-----------------------Тестовый(Работает нормально----------------------------------
	if(COUNT_UART_BUF == 0) return;
	if(ch>(COUNT_UART_BUF-1)) return;
	i=0;
	if(program.N[ch]>4)
	{
		while(i<=program.N[ch])
		{
		//	clr_wdt;
			if((program.Pack_IN_[ch][i]==0x81))// && (program.Pack_IN_[i+1]!=0))
			//Ишем начало пакета
			{
				//Putch_N(0,0x30);
				//-Перетаскиваем 81 к начaлу буфера
				__DI();
				program.N[ch]-= i;
				memmove(program.Pack_IN_[ch],program.Pack_IN_[ch]+i,program.N[ch]);
				__EI();
				i=0;
				if(program.N[ch]<(5)) break;
				//Putch_N(0,0x31);
				
				//если длина ещё непришла выход
				nDataLen=program.Pack_IN_[ch][3]+(unsigned int)(program.Pack_IN_[ch][4]<<8);
				nLen=nDataLen+9;
				if(nLen<Max_In_Pak)
				//Слишком большая длина пакета
				{
					//Putch_N(0,0x32);
					if(nLen>(BUFFER_LEN_UART-1))	//Если пакет не помещяется в оставшейся чачти буфера
					{							//перетаскиваем пакет к началу
						program.N[ch]= 0;
						break;
					}
					//Putch_N(0,0x33);
					
					if(nLen>(program.N[ch])) break;
					//Putch_N(0,0x34);
					//Если пришёл ещё не весь пакет выходим
					if(program.Pack_IN_[ch][nLen-2]==0x81 && program.Pack_IN_[ch][nLen-1]==0x0)
					//Ищем конец пакета
					{
						//Putch_N(0,0x35);
						if(CRC(program.Pack_IN_[ch]+1,nLen-5)==Calc(program.Pack_IN_[ch][nLen-3],program.Pack_IN_[ch][nLen-4]))
						//Проверяем контрольную сумму
						{
							//Putch_N(0,0x36);
							//Проверяем код операции
							switch(program.Pack_IN_[ch][5])
							{
								//=======================================================================================
								//=======================================================================================
								#ifdef PLATA_ADC8
								case 0x01://--------------------------
								{	// Чтение тарировок
									SendTarADC8();
									//Перетаскиваем оставшиеся данные к началу буфера
									program.N[ch]-= nLen;
									memmove(program.Pack_IN_[ch],program.Pack_IN_[ch]+nLen,BUFFER_LEN_UART-nLen);
									break;
								}
								case 0x02://--------------------------
								{	// Запись тарировок
									
									ptrSendPakTar = (TSendPakTar *)(&program.Pack_IN_[ch][6]);
									if(ptrSendPakTar->wCountTar<=COUNT_ADC_CH)
									{
										for(j=0; j<ptrSendPakTar->wCountTar; j++)
										{	
											k_new[j].K   = ptrSendPakTar->tTar[j].K;
											k_new[j].Ofs = ptrSendPakTar->tTar[j].Ofs;
										}
									}
									Adc.WriteCoeffFlash = 1;
									//Перетаскиваем оставшиеся данные к началу буфера
									program.N[ch]-= nLen;
									memmove(program.Pack_IN_[ch],program.Pack_IN_[ch]+nLen,BUFFER_LEN_UART-nLen);
									break;
								}
								
								#endif
								//=======================================================================================
								#ifdef PLATA_ADC
								case 0x01://--------------------------
								{	// Чтение тарировок
									//Putch_N(0,0x37);
									SendTarADC6();
									//Перетаскиваем оставшиеся данные к началу буфера
									program.N[ch]-= nLen;
									memmove(program.Pack_IN_[ch],program.Pack_IN_[ch]+nLen,BUFFER_LEN_UART-nLen);
									break;
								}
								case 0x02://--------------------------
								{	// Запись тарировок
									//Putch_N(0,0x37);
									
									ptrSendPakTar = (TSendPakTar *)(&program.Pack_IN_[ch][6]);
									if(ptrSendPakTar->wCountTar<=COUNT_TAR_COEFF)
									{
										for(j=0; j<ptrSendPakTar->wCountTar; j++)
										{	
											k_33_new[j].K   = ptrSendPakTar->tTar[j].K;
											k_33_new[j].Ofs = ptrSendPakTar->tTar[j].Ofs;
										}
									}
									Adc.WriteCoeffFlash = 1;
									//Перетаскиваем оставшиеся данные к началу буфера
									program.N[ch]-= nLen;
									memmove(program.Pack_IN_[ch],program.Pack_IN_[ch]+nLen,BUFFER_LEN_UART-nLen);
									break;
								}
								
								#endif
								//=======================================================================================
								//=======================================================================================
								//=======================================================================================
								#ifdef PLATA_DAC9
								case 0x01://--------------------------
								{	// Запись в ЦАП	
									//Putch_N(0,0x36);
									__DI();
									Dac9.SelDAC_CH = program.Pack_IN_[ch][6];
									Dac9.SelDAC_CH += (WORD)(program.Pack_IN_[ch][7]<<8);
									
									for(k=0;k<COUNT_DAC_CH; k++)
									{
										ptr = (BYTE *)&Dac9.fDAC_New[k];
										ptr[0] = program.Pack_IN_[ch][10+k*4];
										ptr[1] = program.Pack_IN_[ch][11+k*4];
										ptr[2] = program.Pack_IN_[ch][12+k*4];
										ptr[3] = program.Pack_IN_[ch][13+k*4];
									}
									//Перетаскиваем оставшиеся данные к началу буфера
									program.N[ch]-= nLen;
									memmove(program.Pack_IN_[ch],program.Pack_IN_[ch]+nLen,BUFFER_LEN_UART-nLen);
									__EI();
									break;
								}
								case 0x02://--------------------------
								{	// Запись тарировок АЦП	
									//Putch_N(0,0x37);
						
									__DI();
									ptr = (BYTE *)&TarrRAM_ADC[0];
									for(k=0;k<COUNT_ADC_CH*8; k++)
									{
										ptr[k] = program.Pack_IN_[ch][6+k];
									}
									ptr = (BYTE *)&TarrRAM_DAC[0];
									j=COUNT_ADC_CH*8;
									for(k=0;k<COUNT_DAC_CH*8; k++)
									{
										ptr[k] = program.Pack_IN_[ch][6+k+j];
									}
									
									Dac9.WriteCoeffFlash=1;
									//Перетаскиваем оставшиеся данные к началу буфера
									program.N[ch]-= nLen;
									memmove(program.Pack_IN_[ch],program.Pack_IN_[ch]+nLen,BUFFER_LEN_UART-nLen);
									__EI();
									break;
								}
								case 0x03:
								{
									//Putch_N(0,0x38);
						
									Dac9.SendFlagUart=1;
									
									break;
								}
								#endif
								//=======================================================================================
								//=======================================================================================
								//=======================================================================================
								#ifdef PLATA_DAC10
								case 0x01://--------------------------
								{	// Запись в ЦАП	
									//Putch_N(0,0x36);
									__DI();
									
									k = program.Pack_IN_[ch][6];
									Dac10.EnOutDac	=Dac10.EnOutDac&(~(((WORD)(1))<<k))|(((program.Pack_IN_[ch][7])&1)<<k);
									Dac10.DOUT_New[k] = program.Pack_IN_[ch][7];
									Dac10.SPDT2_New[0] = program.Pack_IN_[ch][8];
									ptr = (BYTE *)&Dac10.fDAC_New[k];
										
									ptr[0] = program.Pack_IN_[ch][10];
									ptr[1] = program.Pack_IN_[ch][11];
									ptr[2] = program.Pack_IN_[ch][12];
									ptr[3] = program.Pack_IN_[ch][13];
									
									//Перетаскиваем оставшиеся данные к началу буфера
									program.N[ch]-= nLen;
									memmove(program.Pack_IN_[ch],program.Pack_IN_[ch]+nLen,BUFFER_LEN_UART-nLen);
									__EI();
									break;
								}
								case 0x02://--------------------------
								{	// Запись тарировок АЦП	ЦАП 
									//Putch_N(0,0x37);
									__DI();
									ptr = (BYTE *)&TarrRAM_DAC[0];
									for(k=0;k<COUNT_DAC_CH*8; k++)
									{
										ptr[k] = program.Pack_IN_[ch][6+k];
									}
									Dac10.WriteCoeffFlash=1;
									//Перетаскиваем оставшиеся данные к началу буфера
									program.N[ch]-= nLen;
									memmove(program.Pack_IN_[ch],program.Pack_IN_[ch]+nLen,BUFFER_LEN_UART-nLen);
									__EI();
									break;
								}
								case 0x03:
								{
									Dac10.SendFlagUart=1;
									break;
								}
								case 0x04:
								{
									Dac10.SendFlagUart=2;
									break;
								}
								#endif
								//=======================================================================================
								//=======================================================================================
								//=======================================================================================
								default:	//пришёл неизвестный идентификатор
								{
									__DI();
									program.N[ch]-= nLen;
									memmove(program.Pack_IN_[ch],program.Pack_IN_[ch]+nLen,BUFFER_LEN_UART-nLen);
									__EI();
									break;
								}
							}
						//-----------------------------------------------------------
						}else
						//Контрольная сумма не совпадает
						{
						//	Putch_N(0,0x33);
						
							__DI();
							memmove(program.Pack_IN_[ch],program.Pack_IN_[ch]+nLen, program.N[ch]-(nLen));
							program.N[ch] -= nLen;
							__EI();
							break;
						}
					}else
					//Нашли не начало пакета
					{
						//Putch_N(0,0x31);
						
						__DI();
						memmove(program.Pack_IN_[ch], program.Pack_IN_[ch]+1, program.N[ch]);
						program.N[ch] -= 1;
						__EI();
						break;
					}
				}else 
				{//Пришла слишком большая длина пакет затираем символ 0x81
					//Putch_N(0,0x32);
						
					__DI();
					memmove(program.Pack_IN_[ch], program.Pack_IN_[ch]+1, program.N[ch]);
					program.N[ch] -= 1;
					__EI();
					break;
				}
			}
			i++;
			if((program.N[ch]>=(BUFFER_LEN_UART-2)) && (i>=(BUFFER_LEN_UART-1)))
				program.N[ch]=0;
		}
	}
}