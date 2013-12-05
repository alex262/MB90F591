#include "mb90590.h"
#include "RVV6.h"
#include "appli.h"
#include "timer.h"

#ifdef PLATA_RVV6

void 	(*INIT_BLOK)(void)	=InitRVV;
void 	(*DRIVER_BLOK)(void)=DriverRVV;
WORD 	(*STATE_BLOCK) 		= &Rvv.Info.word;

CRVV6 Rvv;

WORD TIME_1MS=1/TIMER_RESOLUTION_MS;
WORD TIME_5MS=5/TIMER_RESOLUTION_MS;
WORD TIME_10MS=10/TIMER_RESOLUTION_MS;

//===========================================================================
void UN_SELEKT_BL(void);
//===========================================================================
void WaitMS(BYTE ms)
{
	WORD t;
	t=ms/TIMER_RESOLUTION_MS;
	Rvv.Timer=0;
	while(Rvv.Timer<t)clrwdt;
}

void CLOCK_CLK(void)
{
	RCLK=0; 
	RCLK=1; 
	WaitMS(1);
	RCLK=0;
}
// Инициализируем 
void InitRVV()
{
	BYTE i, j;
	
	//-----------
	RCLK=0;
	UN_SELEKT_BL();
	DATA_0_3_W(0);
	RW_R=tREAD;
	//-----------
	
	DDR0=0xC0;
	DDR1=0x00;
	DDR2=0x00;
//	DDR3=0x10;
	DDR4=0x00;
	DDR5=0x00;
	DDR6=0xFF;
	DDR7=0xF1;
	DDR8=0xFF;
	DDR9=0x01;
	RCLK=0;
	//-----------------------------------------------
	for(i=0;i<COUNT_BLOCK; i++)
	{
		for(j=0;j<2; j++)
		{
			Rvv.Block[i].New[j]=0;
			Rvv.Block[i].Old[j]=0xAA;
			Rvv.Block[i].Select[j]=UNSELECT_BLOCK;
		}
		Rvv.Block[i].Error=0;
	}
	Rvv.Block[BLOCK_DN_NUM].New[0]=0xE;
	
	Rvv.EnableChange	= 0;
	Rvv.NewEnableChange	= 0x5A;
	Rvv.Error		 	= 0;
	//-----------------------------------------------
	Rvv.Info.bits.Addr	=2;
	ADDR_NODE			=2;
	LEDR=1;
	LEDG=1;
}
//===================================================================================
//===========================================================================
// Снимаем выбор со всех блоков
void UN_SELEKT_BL()
{
	RSE1=UNSELECT_BLOCK;
	RSE2=UNSELECT_BLOCK;
	RSE3=UNSELECT_BLOCK;
	RSE4=UNSELECT_BLOCK;
	RSE5=UNSELECT_BLOCK;
	RSE6=UNSELECT_BLOCK;
	RSE7=UNSELECT_BLOCK;
	RSE8=UNSELECT_BLOCK;
	RSE9=UNSELECT_BLOCK;
	RSE10=UNSELECT_BLOCK;
	RSE11=UNSELECT_BLOCK;
	RSE12=UNSELECT_BLOCK;
	RSE13=UNSELECT_BLOCK;
	RSE14=UNSELECT_BLOCK;
	RSE15=UNSELECT_BLOCK;
	RSE16=UNSELECT_BLOCK;
	RSE17=UNSELECT_BLOCK;
	RSE18=UNSELECT_BLOCK;
	RSE19=UNSELECT_BLOCK;
}
//---------------------------------------------------
// Выставляем выбор для конкретного блока
void SET_SELEKT_STATUS(BYTE N, BYTE St1, BYTE St2)
{
	if(N>(COUNT_BLOCK-1)) return;
	
	St1&=1;
	St2&=1;
	Rvv.Block[N].Select[0] = St1;
	Rvv.Block[N].Select[1] = St2;
	
	switch(N)
	{
		case 0:
		{
			RSE1 = St1;
			RSE2 = St2;
		}break;
		case 1:
		{
			RSE3 = St1;
			RSE4 = St2;
		}break;
		case 2:
		{
			RSE5 = St1;
			RSE6 = St2;
		}break;
		case 3:
		{
			RSE7 = St1;
			RSE8 = St2;
		}break;
		case 4:
		{
			RSE9 = St1;
			RSE10 = St2;
		}break;
		case 5:
		{
			RSE11 = St1;
			RSE12 = St2;
		}break;
		case 6:
		{
			RSE13 = St1;
			RSE14 = St2;
		}break;
		case 7:
		{
			RSE15 = St1;
			RSE16 = St2;
		}break;
		case 8:
		{
			RSE17 = St1;
			RSE18 = St2;
		}break;
	} 
}
//===========================================================================
//---------------------------------------------------
// Ставим выбор для конкретного блока первой его половины, но отметку о выборе не ставим
void SetSel0Path_WithoutMark(BYTE N, BYTE St1)
{
	if(N>(COUNT_BLOCK-1)) return;
	
	St1&=1;
	switch(N)
	{
		case 0:
		{
			RSE1 = St1;
		}break;
		case 1:
		{
			RSE3 = St1;
		}break;
		case 2:
		{
			RSE5 = St1;
		}break;
		case 3:
		{
			RSE7 = St1;
		}break;
		case 4:
		{
			RSE9 = St1;
		}break;
		case 5:
		{
			RSE11 = St1;
		}break;
		case 6:
		{
			RSE13 = St1;
		}break;
		case 7:
		{
			RSE15 = St1;
		}break;
		case 8:
		{
			RSE17 = St1;
		}break;
	} 
}
//---------------------------------------------------
// Ставим выбор для конкретного блока второй его половины, но отметку о выборе не ставим
void SetSel1Path_WithoutMark(BYTE N, BYTE St2)
{
	if(N>(COUNT_BLOCK-1)) return;
	
	St2&=1;
	switch(N)
	{
		case 0:
		{
			RSE2 = St2;
		}break;
		case 1:
		{
			RSE4 = St2;
		}break;
		case 2:
		{
			RSE6 = St2;
		}break;
		case 3:
		{
			RSE8 = St2;
		}break;
		case 4:
		{
			RSE10 = St2;
		}break;
		case 5:
		{
			RSE12 = St2;
		}break;
		case 6:
		{
			RSE14 = St2;
		}break;
		case 7:
		{
			RSE16 = St2;
		}break;
		case 8:
		{
			RSE18 = St2;
		}break;
	} 
}
//===========================================================================

// Выбираем все выбранные блоки
void SET_ALL_SELEKT_STATUS(void)
{
	RSE1 = Rvv.Block[0].Select[0];
	RSE2 = Rvv.Block[0].Select[1];
	RSE3 = Rvv.Block[1].Select[0];
	RSE4 = Rvv.Block[1].Select[1];
	RSE5 = Rvv.Block[2].Select[0];
	RSE6 = Rvv.Block[2].Select[1];
	RSE7 = Rvv.Block[3].Select[0];
	RSE8 = Rvv.Block[3].Select[1];
	RSE9 = Rvv.Block[4].Select[0];
	RSE10= Rvv.Block[4].Select[1];
	RSE11= Rvv.Block[5].Select[0];
	RSE12= Rvv.Block[5].Select[1];
	RSE13= Rvv.Block[6].Select[0];
	RSE14= Rvv.Block[6].Select[1];
	RSE15= Rvv.Block[7].Select[0];
	RSE16= Rvv.Block[7].Select[1];
	RSE17= Rvv.Block[8].Select[0];
	RSE18= Rvv.Block[8].Select[1];
}
//===================================================================================
//===================================================================================
//===================================================================================
void SetErrorBlok()
{

}
//===================================================================================
void WriteBlockNotSelect(BYTE data)
{
	selWRITE_DATA;
	DATA_0_3_W(data);
	RW_R=tWRITE;
	WaitMS(1);
	CLOCK_CLK();
	Rvv.Timer=0;
	while(Rvv.Timer<TIME_5MS)clrwdt;
}
//===================================================================================
BYTE ReadBlockNotSelect()
{
	BYTE b;
	selREAD_DATA;
	RW_R=tREAD;
	WaitMS(1);
	CLOCK_CLK();
	b=DATA_0_3_R;
	WaitMS(1);
	RW_R=tWRITE;
	selWRITE_DATA;
	return b;
}
//===================================================================================
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void DriverRVV()
{
	BYTE	flag, i, j, ret;
	//DWORD k;
	//__DI();
	//Rvv.Error&=~7;	//Комплектность 
	Rvv.Error=RIN;
	//============================================================================
	if(Rvv.EnableChange != Rvv.NewEnableChange)	// разрешено переключить реле
	{
		//=====================================
		// Сначала проверяем необходимо ли что то записывать
		flag = 0;
		for(i=0;i<COUNT_BLOCK; i++)
		{
			for(j=0;j<2; j++)
			{
				if(Rvv.Block[i].New[j] != Rvv.Block[i].Old[j])
					flag = 1;
			}
		}
		if(Rvv.SelectBlockNew!=Rvv.SelectBlockOld)
			flag = 1;
		//---------------------------------------
		// Переходим к записи данных при необходимости
		if(flag == 1)
		{
			Rvv.SelectBlockOld = Rvv.SelectBlockNew;
			
			UN_SELEKT_BL();	// Снимаем выбор со всех блоков
			WaitMS(10);
			
			//-------------------------------------------
			// Запись нужно начинать с блока ДН
			for(i=COUNT_BLOCK; i>0; i--)
			{
				for(j=0;j<2; j++)
				{
					//----------------------------------------------
					//Выставляем Select для блока при неообходимости
					ret = (Rvv.SelectBlockOld>>(2*(i-1)+j))&1;
					if(ret == 1)
						Rvv.Block[i-1].Select[j] = SELECT_BLOCK;
					if(ret == 0)
						Rvv.Block[i-1].Select[j] = UNSELECT_BLOCK;
					//----------------------------------------------
					if(Rvv.Block[i-1].New[j] != Rvv.Block[i-1].Old[j])
					{
						Rvv.Block[i-1].Old[j] = Rvv.Block[i-1].New[j];
						//====================================================
						// Выставляем выбор для конкретной половины блока если необходимо записать новые данные
						if(j==0)
							SetSel0Path_WithoutMark(i-1,SELECT_BLOCK);
						if(j==1)
							SetSel1Path_WithoutMark(i-1,SELECT_BLOCK);
						WaitMS(5);
						// Записываем данные
						WriteBlockNotSelect(Rvv.Block[i-1].Old[j]);
						// Проверяем чтением записаныые данные
						ret = ReadBlockNotSelect();
						Rvv.Block[i-1].Read[j]=ret;
						// 0 бит неисправность первой половины блока; 1 - второй
						if(ret !=Rvv.Block[i-1].Old[j])
							Rvv.Block[i-1].Error |= 1<<j;
						else
							Rvv.Block[i-1].Error &= ~(1<<j);
						WaitMS(5);
						// Снимаем выбор
						if(j==0)
							SetSel0Path_WithoutMark(i-1,UNSELECT_BLOCK);
						if(j==1)
							SetSel1Path_WithoutMark(i-1,UNSELECT_BLOCK);
						WaitMS(10);
						
					}
				}
			}
			SET_ALL_SELEKT_STATUS(); // Ставим выбор всем блокам которым он был выставлен или которым нужно выставить
		}
		//=====================================
		Rvv.EnableChange = Rvv.NewEnableChange;	// Сбрасываем флаг
	}
	//__EI();
	//-----------------------------------------------------------
	// Читаем подключённые блоки и сверяем с тем что записали 
	// вслучае несовпадения зажигаем неисправность
/*	for(i=0; i<COUNT_BLOCK; i++)
	{
		for(j=0;j<2; j++)
		{
			if(Rvv.Block[i].Select[j] == SELECT_BLOCK)
			{
				// Проверяем чтением записаныые данные
				ret = ReadBlockNotSelect();
				// 0 бит неисправность первой половины блока; 1 - второй
				if(ret !=Rvv.Block[i-1].Old[j])
					Rvv.Block[i].Error |= 1<<j;
				else
					Rvv.Block[i].Error &= ~(1<<j);
				// Снимаем выбор
			}
		}
	}*/
	//============================================================================
	
}


#endif

