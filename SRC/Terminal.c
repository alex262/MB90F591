#include "mb90590.h"
#include "math.h"
#include "global.h"
#include "can.h"
#include "flash.h"

#pragma section CODE=TERMINAL, attr=CODE,locate=0xF90000
#pragma section FAR_CODE=TERMINAL, attr=CODE,locate=0xF90000

//-----------

//-----------

const unsigned char 
ver_pr[30]="Верси  про и ки    - ",
e[7]="\n\r#",
s[3]="||",
bad_passw[36]="#Invalid password !!!\n\r#password: ",
ok[12]="#Ok !!!\n\r",
bad_command[36]="Command is not found. See Help\n\r#",
exit_[11]="Goodby\n\r",
help[43]="           ПЕРЕЧЕ   Д С УП  Х    А Д\n\r#",
h_exit[35]="   exit -  ыход по ь о  те   \n\r#",
h_test[47]="   test - состо ние подк ю ённых моду ей\n\r#",
h_ver_prot[52]="   ver_prot -  ерси  про и ки микроконтро  ер \n\r#",
h_set_password[133]="   set password <xxx> <yyy> - уст н   и  ет но ый п ро ь\n\r               ххх - ст рый п ро ь\n\r               ууу - но ый п ро ь\n\r#",
h_read[217]="   read <addr> [count] - ком нд   ы одит содержимое п м ти\n\r               addr -  дрес с которого н  ин ют  ы одитс  д нные(HEX)\n\r               count - ко и ест о  ы одимых б йт(DEC) (необ   те ьный п р метр)\n\r#",
h_write[90]="   write <addr> <data> [data] ... - ком нд    писы  ет д нные н  ин   с  дрес  addr\n\r#",
h_getconf[48]="   getconf - теку    конфигур ци  моду ей\n\r#",
h_getdin[63]="   getdin  - состо ние  сех  х/ ых,   т кже их    идность\n\r#",
//ok_pas[45]="New password is successfully installed\n\r#",
h_errors[71]="   errors - состо ние  к ф  и р с иреннн   информ ци  о пит нии \n\r#",
h_time[50]="   time -  рем  н р ботки  к ф    секунд х \n\r#",
h_temp[37]="   temp - темпер тур     к фу \n\r#",
h_buf1[79]="   get_buf_1(2) -  ы од тс  д нные н ход  иес   о  ходном буфере UART1(2)\n\r#",
h_can0[37]="   can0 - осно ные регистры CAN0\n\r#",
h_can1[37]="   can1 - осно ные регистры CAN1\n\r#",
h_box_can0[40]="   box_can0 - буффур сооб ений CAN0\n\r#",
h_box_can1[40]="   box_can1 - буффур сооб ений CAN1\n\r#",
//bad_passw_st[27]="Invalid old password\n\r#",
//bad_par_set[28]="Invalid set parameter\n\r#",
modul[15]=" Module №", 
t_n[13]=" - NDD-1A", t_f[80]=" - FSU-1A", 
t_e[39]=" - Unknown type or module is absent",
welcome[]=   "-------------------Welcome to Fujitsu microcontroller----------------\n\r#password: "
;




void InitFlash(void)
{
	buffer_pr.password[0]=0x32;buffer_pr.password[1]=0x36;buffer_pr.password[2]=0x32;
}
//------преобр  о  ние HEX    ис  
unsigned long hextoB(unsigned char *s, unsigned char col) 
{
    unsigned char  b;
    unsigned long res = 0;
    //int ctr = 6;
    while(col--) {
        if ((b = *s++) >= '0' && b <= '9')
            b -= '0';
        else if ((b &= 0xDF) >= 'A' && b <= 'F')
            b -= ('A'- 0xA);
        else
            return 0;
        res <<= 4; res |= b;
    }
    return res;
}

void __far Terminal (unsigned char ch_in)
{
unsigned char t,i,*a;
unsigned long col,i_col,addres;
//int temp;
WORD __far *addr;
unsigned int p, j;
unsigned char tmp[50];
//WORD Index;
//BYTE SubIndex;
unsigned long ERR;
//Message m;

buffer_pr.timer=0;
if(buffer_pr.entry==0) 
{
	puts(welcome);
	buffer_pr.entry=1;
}
else 

	if(buffer_pr.entry!=2) 
	{
		if(buffer_pr.flag==1)	{buffer_pr.flag=2; Putch(0x0A);}	//принн  и сим о  0х0А(Enter)
		if(ch_in==0x0D) {buffer_pr.flag=1;Putch(0x0D);}			//принн  и сим о  0х0D(Enter)
		else
		{
			if(buffer_pr.flag==0)
			{
				buffer_pr.command[buffer_pr.n]=ch_in;
				if(buffer_pr.n<10)
					buffer_pr.n++;
				else return;
				Putch(0x2A);
			}
			if(buffer_pr.flag==2)
			{
				//buffer_pr.entry=2; //бе  про ерки п ро  
				//-------------
				buffer_pr.flag=0;
				buffer_pr.n=0;
				if(strcmp(buffer_pr.command,buffer_pr.password)==0) 
					{
						buffer_pr.entry=2;
						puts(ok);Putch(0x23);
					}
				else puts(bad_passw);
				for(i=0;i<10;i++) buffer_pr.command[i]=0;
			}
		}
	}
	//----------------- бр ботк    одимых ком нд-----------------------------------
	else
	{
		if(buffer_pr.flag==1)				//принн  и сим о  0х0А(Enter)
		{
			buffer_pr.flag_pr=0xFF;
			buffer_pr.flag=0; 
			Putch(0x0A);
			Putch(0x23);
		}
		if(ch_in==0x0D) {buffer_pr.flag=1;Putch(0x0D);}	//принн  и сим о  0х0D(Enter)
		else
		{
			if(buffer_pr.flag_pr==0) buffer_pr.flag_pr=1;
			
			if((buffer_pr.flag==0)&&(buffer_pr.flag_pr==5))
			{
				if(ch_in==0x20) {Putch(0x20);buffer_pr.flag_pr=6;buffer_pr.n=0; goto end;}
				buffer_pr.par4[buffer_pr.n]=ch_in;
				if(buffer_pr.n<10)
					buffer_pr.n++;
				else return;
				if (strcmp(buffer_pr.par1,"password")==0) Putch(0x2A);
				else Putch(ch_in);
			}
			if((buffer_pr.flag==0)&&(buffer_pr.flag_pr==4))
			{
				if(ch_in==0x20) {Putch(0x20);buffer_pr.flag_pr=5;buffer_pr.n=0; goto end;}
				buffer_pr.par3[buffer_pr.n]=ch_in;
				if(buffer_pr.n<10)
					buffer_pr.n++;
				else return;
				if (strcmp(buffer_pr.par1,"password")==0) Putch(0x2A);
				else Putch(ch_in);
			}
			if((buffer_pr.flag==0)&&(buffer_pr.flag_pr==3))
			{
				
				if(ch_in==0x20) {Putch(0x20);buffer_pr.flag_pr=4;buffer_pr.n=0; goto end;}
				buffer_pr.par2[buffer_pr.n]=ch_in;
				if(buffer_pr.n<10)
					buffer_pr.n++;
				else return;
				if (strcmp(buffer_pr.par1,"password")==0) Putch(0x2A);
				else Putch(ch_in);
			}
			if((buffer_pr.flag==0)&&(buffer_pr.flag_pr==2))
			{
				if(ch_in==0x20) {Putch(0x20);buffer_pr.flag_pr=3;buffer_pr.n=0; goto end;}
				buffer_pr.par1[buffer_pr.n]=ch_in;
				if(buffer_pr.n<10)
					buffer_pr.n++;
				else return;
				Putch(ch_in);
			}
			if((buffer_pr.flag==0)&&(buffer_pr.flag_pr==1))
			{
				if(ch_in==0x20) {Putch(0x20);buffer_pr.flag_pr=2;buffer_pr.n=0; goto end;}
				buffer_pr.command[buffer_pr.n]=ch_in;
				if(buffer_pr.n<10)
					buffer_pr.n++;
				else return;
				Putch(ch_in);
			}
		}
		if(buffer_pr.flag_pr==0xFF)
		{
			buffer_pr.flag_pr=0;
			//------------- бр ботк  ком нды----------------
			if (strcmp(buffer_pr.command,"exit")==0)
			{
				buffer_pr.entry=0;
				puts(exit_);
				goto com_yes;
			}
			if (strcmp(buffer_pr.command,"help")==0)
			{
				if(buffer_pr.par1[0]==0)
				{
					puts(help); puts(h_exit); puts(h_test); puts(h_ver_prot); 
					clrwdt;
					puts(h_set_password); puts(h_read); puts(h_write); puts(h_getconf);
					clrwdt;
					puts(h_getdin);puts(h_errors);puts(h_time);puts(h_temp);
					clrwdt;
					puts(h_buf1);puts(h_can0); puts(h_can1); puts(h_box_can0); puts(h_box_can1);
				}else
					{
						if (strcmp(buffer_pr.par1,"set")==0)
						{if (strcmp(buffer_pr.par2,"password")==0) puts(h_set_password);}
						if (strcmp(buffer_pr.par1,"exit")==0) puts(h_exit);
						if (strcmp(buffer_pr.par1,"read")==0) puts(h_read);
						if (strcmp(buffer_pr.par1,"write")==0) puts(h_write);
						if (strcmp(buffer_pr.par1,"getconf")==0) puts(h_getconf);
						if (strcmp(buffer_pr.par1,"getdin")==0) puts(h_getdin);
						if (strcmp(buffer_pr.par1,"ver_prot")==0) puts(h_ver_prot);
						if (strcmp(buffer_pr.par1,"errors")==0) puts(h_errors);
						if (strcmp(buffer_pr.par1,"time")==0) puts(h_time);
						if (strcmp(buffer_pr.par1,"temp")==0) puts(h_temp);
						if (strcmp(buffer_pr.par1,"get_buf_1")==0) puts(h_buf1);
					}
				goto com_yes;
			}
			if (strcmp(buffer_pr.command,"read")==0)
			{
				if(buffer_pr.par2[0]==0) col=1;
				else
					{
						if(buffer_pr.par2[1]==0) col=(buffer_pr.par2[0]-0x30);
						else
						{
							if(buffer_pr.par2[2]==0) col=(buffer_pr.par2[0]-0x30)*10+buffer_pr.par2[1]-0x30;
							else
							{
								col=(unsigned long)(buffer_pr.par2[0]-0x30)*100+(buffer_pr.par2[1]-0x30)*10+buffer_pr.par2[2]-0x30;
							}
						}
					}
				t=0;
				for(i=0;i<6;i++)
				{
					if(buffer_pr.par1[i]!=0) t++;
				}
				addres=hextoB(buffer_pr.par1,t);
				put_24bit_value(addres);Putch(0x3A);Putch(0x20);
				t=0;
				for(i_col=0;i_col<col;i_col++)
				{
					t++;
					//program.watch_dog=0;
					put_8bit_value(read_byte(addres));
					Putch(0x20);
					if(t==8){Putch(0x7C);Putch(0x20);}
					addres++;
					if(t==16)
					{
						Putch(0x20);
						addres-=16;
						for(i=0;i<16;i++)
						{
							Putch(read_byte(addres));
							addres++;
						}
						//--------------------------
						puts(e);
						put_24bit_value(addres);
						Putch(0x3A);
						Putch(0x20);
						t=0;
					}
				}
				puts(e);
				goto com_yes;
			}
			if (strcmp(buffer_pr.command,"write")==0)
			{
				t=0;
				for(i=0;i<6;i++)
				{
					if(buffer_pr.par1[i]!=0) t++;
				}
				addres=hextoB(buffer_pr.par1,t);
				addr = (WORD __far *)addres;	
				t=0;
				for(i=0;i<10;i++)
				{
					if(buffer_pr.par2[i]!=0) t++;
				}
				a= &buffer_pr.par2[0];
				if((addres>=0xF90000)&&(addres<=0xFFFFFF))
				{
					p=hextoB(a,4);
					i=(unsigned char)p;
					p=p>>8;
					p|=(unsigned int)(i<<8);
					__DI();
					i=Flash_write(addr,p);
					__EI();
					if(i==1) puts("Successfully recorded\n\r#");
					else puts("Not written\n\r#");
				}
				else
				{
					if((addres>=0)&&(addres<0xF90000))
					{
						while(t>0)
						{
							p=hextoB(a,4);
							i=(unsigned char)p;
							p=p>>8;
							p|=(unsigned int)(i<<8);
							*addr=(WORD)p;
							t-=4;
							a+=4;
							addr++;
						}
						puts("Successfully recorded\n\r#");
					}
					else puts("Address is incorrect!!!\n\r#");
				}
				goto com_yes;
			}
			if (strcmp(buffer_pr.command,"erase")==0)
			{
				__DI();
				//FL_SectorErase(0xFB0000);
				Flash_sector_erase((volatile __far WORD *)0xFB0000);
				__EI();
				goto com_yes;
			}
			//-------------------Пок  ы  ет содержимое осно ных регистро  CAN0--------------------------
			if (strcmp(buffer_pr.command,"1")==0)
			{
				puts("Состо ние CAN0\n\r\n\r");
				puts("      CSR0        |       RTEC0       |       IDER0       |        RCR0       |\n\r");
				
				p=CSR0;
				putBIN_int(p);puts(" | ");
				p=RTEC0;
				clrwdt;
				putBIN_int(p);puts(" | ");
				p=IDER0;
				clrwdt;
				putBIN_int(p);puts(" | ");
				p=RCR0;
				putBIN_int(p);puts(" |\n\r");
				clrwdt;
				puts("      TCR0        |       BVALR0      |       BTR0        |      TIER0        |\n\r");
				p=TCR0;
				putBIN_int(p);puts(" | ");
				p=BVALR0;
				clrwdt;
				putBIN_int(p);puts(" | ");
				p=BTR0;
				putBIN_int(p);puts(" | ");
				clrwdt;
				p=TIER0;
				putBIN_int(p);puts(" |\n\r");
				
				puts("      RIER0       |       TREQR0      |       LEIR0       |        RRTRR0     |\n\r");
				p=RIER0; 
				putBIN_int(p);puts(" | ");
				p=TREQR0;
				clrwdt;
				putBIN_int(p);puts(" |      ");
				p=LEIR0;
				putBIN((unsigned char)p);puts("     | ");
				p=RRTRR0;
				clrwdt;
				putBIN_int(p);puts(" |\n\r");
				puts("      TRTRR0      |        ROVRR0     |       AMSR0       |        AMR00      |\n\r");
				p=TRTRR0;
				putBIN_int(p);puts(" | ");
				p=ROVRR0;
				putBIN_int(p);puts(" |     ");
				ERR=AMSR0;
				sprintf(tmp,"0x%02X%02X %02X%02X",read_byte(0x1c13),read_byte(0x1c12),read_byte(0x1c11),read_byte(0x1c10));
				puts(tmp);
				
				puts("   |    ");
				ERR=AMR00;
				sprintf(tmp,"0x%02X%02X %02X%02X",read_byte(0x1c14),read_byte(0x1c15),read_byte(0x1c16),read_byte(0x1c17));
				puts(tmp);//PrHexD(AMR00);
				puts("\n\r");
				
				goto com_yes;
			}
			//-------------------Пок  ы  ет содержимое осно ных регистро  CAN1--------------------------
			if (strcmp(buffer_pr.command,"2")==0)
			{
				puts("Состо ние CAN1\n\r\n\r");
				puts("      CSR1        |       RTEC1       |       IDER1       |        RCR1       |\n\r");
				p=CSR1;
				putBIN_int(p);puts(" | ");
				p=RTEC1;
				clrwdt;
				putBIN_int(p);puts(" | ");
				p=IDER1;
				putBIN_int(p);puts(" | ");
				p=RCR1;
				putBIN_int(p);puts(" |\n\r");
				puts("      TCR1        |       BVALR1      |       BTR1        |      TIER1        |\n\r");
				p=TCR1;
				clrwdt;
				putBIN_int(p);puts(" | ");
				p=BVALR1;
				putBIN_int(p);puts(" | ");
				p=BTR1;
				putBIN_int(p);puts(" | ");
				p=TIER1;
				putBIN_int(p);puts(" |\n\r");
				puts("      RIER1       |       TREQR1      |       LEIR1       |        RRTRR1     |\n\r");
				p=RIER1; 
				putBIN_int(p);puts(" | ");
				p=TREQR1;
				clrwdt;
				putBIN_int(p);puts(" |      ");
				p=LEIR1;
				putBIN((unsigned char)p);puts("     | ");
				p=RRTRR1;
				clrwdt;
				putBIN_int(p);puts(" |\n\r");
				puts("      TRTRR1      |        ROVRR1     |       AMSR1       |         AMR10\n\r");
				p=TRTRR1;
				putBIN_int(p);puts(" | ");
				p=ROVRR1;
				putBIN_int(p);puts(" |    ");
				ERR=AMSR1;
				sprintf(tmp,"0x%02X%02X %02X%02X",read_byte(0x1d13),read_byte(0x1d12),read_byte(0x1d11),read_byte(0x1d10));
				puts(tmp);
				
				puts("    | ");
				ERR=AMR10;
				sprintf(tmp,"0x%02X%02X %02X%02X",read_byte(0x1d14),read_byte(0x1d15),read_byte(0x1d16),read_byte(0x1d17));
				puts(tmp);
				puts("\n\r");
				
				goto com_yes;
			}
			//------------------------------------------------
		
			//---------------Пок  ы  ет содержимое MsgBox CAN0----------------
			if (strcmp(buffer_pr.command,"3")==0)
			{
				puts("\n\r| box |       IDR0        |       DLC0        |           DTR            |\n\r");
				for(i=0;i<16;i++)
				{
					clrwdt;
					puts("| ");putD(i);
					if(box_type[0][i]==CANMSG_TRANSMIT) puts(" TX ");
					if(box_type[0][i]==CANMSG_MINE) puts(" RX ");
					p=IDR0_ID0_2(i)|(IDR0_ID3_10(i)<<3); 
					puts(" | ");/*putBIN_int(p)*/put_8bit_value(p>>8);put_8bit_value(p);puts(" | ");
					p=DLCR0(i)&0xF;
					/*putBIN_int(p)*/put_8bit_value(p);puts(" | ");
					put_8bit_value(read_byte(0x1a80+i*8));puts(" ");put_8bit_value(read_byte(0x1a81+i*8));puts(" ");
					put_8bit_value(read_byte(0x1a82+i*8));puts(" ");put_8bit_value(read_byte(0x1a83+i*8));puts(" ");
					put_8bit_value(read_byte(0x1a84+i*8));puts(" ");put_8bit_value(read_byte(0x1a85+i*8));puts(" ");
					put_8bit_value(read_byte(0x1a86+i*8));puts(" ");put_8bit_value(read_byte(0x1a87+i*8));puts(" \n\r");
				}
				puts("\n\r#");
				goto com_yes;
			}
			//---------------Пок  ы  ет содержимое MsgBox CAN1---------------------------------
			if (strcmp(buffer_pr.command,"4")==0)
			{
				puts("\n\r| box |       IDR1        |       DLC1        |           DTR1           |\n\r");
				for(i=0;i<16;i++)
				{
					clrwdt;
					puts("| ");putD(i);//puts(" |");
					if(box_type[1][i]==CANMSG_TRANSMIT) puts(" TX ");
					if(box_type[1][i]==CANMSG_MINE) puts(" RX ");
					p=IDR1_ID0_2(i)|(IDR1_ID3_10(i)<<3); 
					puts(" | ");/*putBIN_int(p)*/put_8bit_value(p>>8);put_8bit_value(p);puts(" | ");
					p=DLCR1(i)&0xF;
					/*putBIN_int(p)*/put_8bit_value(p);puts(" | ");
					put_8bit_value(read_byte(0x1b80+i*8));puts(" ");put_8bit_value(read_byte(0x1b81+i*8));puts(" ");
					put_8bit_value(read_byte(0x1b82+i*8));puts(" ");put_8bit_value(read_byte(0x1b83+i*8));puts(" ");
					put_8bit_value(read_byte(0x1b84+i*8));puts(" ");put_8bit_value(read_byte(0x1b85+i*8));puts(" ");
					put_8bit_value(read_byte(0x1b86+i*8));puts(" ");put_8bit_value(read_byte(0x1b87+i*8));puts(" \n\r");
				}
				puts("\n\r#");
				goto com_yes;
			}
			//=====================================================
			if (strcmp(buffer_pr.command,"get_buf_0")==0)
			{
				puts("//============BUFFER RX UART0===============//\n\r");
				puts("Count byte: ");
				__DI();
				p=program.N[0];
				putD(p);
				puts("\n\r");
				puts("Data ,h   : ");
				for(j=0;j<p;j++)
				{
					clrwdt;
					PrHexB(program.Pack_IN_[0][j]);
				}
				__EI();
				puts("\n\r#");
				goto com_yes;
			}

			
			//----------------------------------------------
			/*if (strcmp(buffer_pr.command,"1")==0)
			{
				m.rtr=1;
				m.cob_id=1;
				m.len=0;
				f_can_send(1 ,&m );
				puts("\n\r#");
				goto com_yes;
			}
			if (strcmp(buffer_pr.command,"0")==0)
			{
				m.rtr=1;
				m.cob_id=2;
				m.len=0;
				f_can_send(0 ,&m );
				puts("\n\r#");
				goto com_yes;
			}
			*/
			//--------В еден  неи  естн   ком нд -----------
			puts(bad_command);
			//----------------------------------------------
com_yes:	buffer_pr.n=0;
			for(i=0;i<10;i++) 
			{
				buffer_pr.command[i]=0;
				buffer_pr.par1[i]=0;
				buffer_pr.par2[i]=0;
				buffer_pr.par3[i]=0;
				buffer_pr.par4[i]=0;
			}
		}
	}
//----------------------------------------------------------------------------------		
end:;
}

//----------------------------------------------------------------------------------

