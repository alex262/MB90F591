#include "mb90590.h"
#include "flash.h"
#include "global.h"

#pragma section CODE=FLASH_PROG, attr=CODE, locate=0xFA0100
#pragma section FAR_CODE=FLASH_PROG, attr=CODE, locate=0xFA0100

#define COUNT_BANK	6	// ���������� �������� 
DWORD 	BANK_ADDR[COUNT_BANK]	= {0xF90000,0xFA0000,0xFB0000,0xFD0000,0xFE0000,0xFF0000};	// ������ ��������
BYTE	BANK_PROG =	1;	// ������ � ������� ��������� ��������� ���������� ��������

//=============================================================================================================
// ������� FLASH ������ ���������������� �� ���������� ������� ��� ��������� ��������� ���������� ��
void EraseFlash(viod)
{
	BYTE i;
	
	for(i=0;i<COUNT_BANK; i++)
	{
		if(i != BANK_PROG)
			Flash_sector_erase((volatile __far WORD *)BANK_ADDR[i]);
	}
}
//=============================================================================================================

