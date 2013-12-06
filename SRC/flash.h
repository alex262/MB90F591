#ifndef _FLASH_H
#define _FLASH_H

#include "global.h"



#define LINE_BUFFER_SIZE 0x100

#define read_byte(adr) ((int)*(unsigned char __far*)(adr))
#define read_word(adr) (*(unsigned int __far*)(adr))
#define read_long(adr) (*(unsigned long __far*)(adr))


#define BEL     0x07            /* special symbol for BELL */
#define BS      0x08            /* special symbol for BACKSPACE */
#define TAB    	0x09  			/* special symbol for TAB(ulator) */
#define ESC     0x1B            /* special symbol for ESCAPE */
#define CR      0x0D            /* special symbol for RETURN */
#define LF      0x0A            /* special symbol for LINEFEED */
#define DEL     0x7F            /* special symbol for DELETE */





void put_4bit_value(int);
void put_8bit_value(int);
void put_24bit_value(long);

//__far void read_flash(__far unsigned char *_addr, unsigned char *_dst, int _cnt); 
//void WriteFlashBuff(volatile __far WORD *start1_adr,DWORD addr,int count);
void WriteFlashBuff(volatile __far WORD *start1_adr,DWORD addr,int count,BYTE Erase);


typedef struct{
	unsigned long timer;		//������� ����������� ������� �������� �����������
	unsigned char entry;		//��������� ���� � ������� ��� ��� (1 - ���� ��������� �� ������ �� �����
								// 2 - ������ �����)
	unsigned char password[5];	//������
	unsigned char command[10];	//����������� �������� �������
	unsigned char par1[10];		//������ �������� ��������� �� ��������
	unsigned char par2[10];		//������ �������� ��������� �� ��������
	unsigned char par3[10];		//������ �������� ��������� �� ��������
	unsigned char par4[10];		//�������� �������� ��������� �� ��������
	unsigned char flag_pr;		//0 - ������ �� �����������; 1 - �������; 
								//2 - ����������� 1 ��������; 3 - ����������� 2 �������� 0xFF - ���� ����� �����
	unsigned char n;		//����� ������������ ����� � ������������������
	unsigned char flag;		//

}TBuffer_pr;					//����� ����� Uart0

extern TBuffer_pr buffer_pr;
/*
void put_4bit_value(int val);
void put_8bit_value(int val); 
void put_24bit_value(long val);
void putD(unsigned char p);
void putBIN(unsigned char p);
void putBIN_int(unsigned int p);
void putBIN_lword(unsigned long p);
*/


#endif


