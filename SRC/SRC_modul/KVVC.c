#include "mb90590.h"
#include "KVVC.h"

#ifdef PLATA_KVV
#include "filter.h"

CKVV_C Kvv;

void 	(*INIT_BLOK)(void)=InitKVVC;
void 	(*DRIVER_BLOK)(void)=DriverKVVC;

//===============
void InitKVVC(void)
{
	BYTE	i,k;

	DDR0=0x00;
	DDR1=0x03;
	DDR2=0x0;
	DDR4=0x1f;	//adres for read, out  prover bloka
	DDR5=0x0f;
	DDR6=0x00;	//ad
	DDR7=0xff;	//LE15-LE8
	DDR8=0xff;	//LE7-LE0
	DDR9=0x21;	//E1,E2

	PDR4=0x00;
	PDR5=0x00;
	PDR7=0xff;
	PDR8=0xff;
	PDR9=0x0;  //E2=0 OUT - LOW
	RESIRQ=1;
//ADC
	ADER=0x1f;
	ADCS0=0x00;	//SINGLE MODE
	ADCS1=0x00;
	ADCR1=0x0;
	RESIRQ=1;

	LEDR=1;
	LEDG=1;
//------------------
	Kvv.Info.word=0;
	Kvv.Info.bits.Addr=ADDR;
	ADDR_NODE	=ADDR;

	
	Kvv.St=1;
	Kvv.Delay=0;
	Kvv.DDate[0]=0;
	Kvv.DDate[1]=0;
	Kvv.DMis[0]=0;
	Kvv.DMis[1]=0;
	for (i=0;i<20;i++)
	  {
	    Kvv.AnData[i]=0;	
	  }
	Kvv.DD=0;  
	Kvv.DDPre=0;  
	Kvv.OI=0;  
	Kvv.OIPre=0;

//out is 	
	 PDR5= 0;
	 k=0x80;
	for (i=0;i<16;i++)
	{
	  if (i==8)
	    k=0x80;	
		WRP78
		k = k >> 1;
	}  
}

//==============
void DriverKVVC()
{
	BYTE i;
	WORD dan;
	__DI();
	i = ADDR;
	Kvv.Info.bits.Addr	=i;
	if(i!=ADDR_NODE)
	{
		setState(Initialisation);
		ADDR_NODE  =ADDR;
	
	}
	Kvv.Info.bits.Addr	=ADDR;
	Kvv.Info.bits.Mode	=MODE;

/*	    if (E1 == 0)
	     { 
	     	Kvv.Info.bits.MisE1 =0; //reset mistake of E1
		ClearError(ind_ERROR);
	     }	
	    else
	    	{
	    	 Kvv.Info.bits.MisE1=1; //set mistake of E1
		 SetError(ind_ERROR);
	        }
	    if ((Kvv.Info.bits.MisPw == 0) & (Kvv.Info.bits.MisE1 == 0))
	      {	    
		switch (Kvv.St)
		    {
			case 1:BeginWr();	
				   break;
			case 2:SetWr();	
				   break;
				
			case 3:SetRd();
				   break;
	        }
/*	      } 
	    else
	    {
	    	Kvv.DMis[0]=0xff;
	    	Kvv.DMis[1]=0xff;
	    }   
*/	
PDR5_P53=1;
	    ReadTst();  	
PDR5_P53=0;
	BeginWr();
	SetWr();
PDR5_P53=1;
//	SetRd();
PDR5_P53=1;
	ReadOne(15);
__EI();
}
//==========
//for test
void ReadTst()
{
	ADCS0=9;	//24B
 	READC
 	 Kvv.AnData[16]=0x3ff & ADCR; 
	ADCS0=0x12;	//5B
 	READC
 	 Kvv.AnData[17]=0x3ff & ADCR; 

 	 if (( Kvv.AnData[16] > MAX5) || ( Kvv.AnData[16] < MIN5))
 	{  Kvv.Info.bits.Mis5B=1;
	}   
 	 else
 	{   Kvv.Info.bits.Mis5B=0;
 	}
 	 if (( Kvv.AnData[17] > MAX24) || ( Kvv.AnData[17] < MIN24))
 	{  Kvv.Info.bits.Mis24B =1;
	}   
 	 else
 	{   Kvv.Info.bits.Mis24B=0;
 	}
}
//==========
void SetWr(void)
	{//1
 if (Kvv.Timer>0)
	  {//2
		Kvv.DD = (WORD)Kvv.DDIn[0] | ((WORD)Kvv.DDIn[1] << 8);
		Kvv.OI = (WORD)Kvv.OIIn[0] | ((WORD)Kvv.OIIn[1] << 8);
	        E2=1;
	        WrOut();
	        if ((Kvv.AdDelayIn & 0x80) ==0)
	        {
	          Kvv.Info.bits.MisTMax=0;
	          Kvv.Delay=0;	
	          Kvv.AdDelay=0;
	        }
	        else
	        {
	        Kvv.AdDelay = Kvv.AdDelayIn; 	
	        Kvv.Timer2 = 0;
	        }
//	        Kvv.Timer = 0;
	        Kvv.St = 3;
	   }//2
	}//1
//=========================
void WrOut()   //write byte
	{//1
	 BYTE k,i;
	 WORD j;
 	   j = 1;
	   k=0x80;
	   for (i=0;i<16;i++)
	    {//2
	    if (i==8)
	    k=0x80;	
		if ((Kvv.JobCo & j) != 0)  //in/out in job
		  {//3
		    if ((Kvv.OI & j) != 0)  //out or in
	    		{//4
		         if ((Kvv.OIPre & j) != 0)  //out in pre
	    		  {//41
	    	           if ((Kvv.DDPre & j)!=(Kvv.DD & j))  //was change?
			       {//5
			        WRP5
			        WRP78
			      }//5
			    }//41
			  else
			   {
				WRP5
			    WRP78
			  }
			}//4
			else
			{//6
		     if ( (Kvv.OIPre & j) != 0)  //out in pre?
			  {//9
			    PDR5= 0;
			    WRP78
			  }//9
		   }//6	
	     }//3
		k = k >> 1;
		j = j << 1;	
	    }//2
	 Kvv.DDPre = Kvv.DD;
	 Kvv.OIPre = Kvv.OI;
}//1
//==========
void ReadOne(BYTE chanel)
{
	     if ((chanel & 8)==0)
		  PDR4=chanel | 8;
		 else
		  PDR4=chanel & 0xf7 | 0x10;

		  READC
	 	  Kvv.AnData[chanel]=0x3ff & ADCR; //adc
	      PDR4=0;
}
//==========
void BeginWr()
{
	 if (Kvv.Timer>0)
	 {//1
	   if (Kvv.InfoWr.bits.WrBeg == 1)
	   {//2
//mistake in maska
	     if ((Kvv.M24In & Kvv.M5In | Kvv.M5RIn & Kvv.M5In|Kvv.M24In & Kvv.M5RIn) == 0)
		{//3
		  Kvv.Info.bits.MisMaska = 0;

  		  Kvv.M24 = Kvv.M24In;  
		  Kvv.M5 = Kvv.M5In;   
		  Kvv.M5R = Kvv.M5RIn;		  
		  Kvv.VU24 = Kvv.VU24In; 
		  Kvv.NU24 = Kvv.NU24In;
  		  Kvv.VU240 = Kvv.VU240In;
		  Kvv.VU5 = Kvv.VU5In; 
		  Kvv.NU5 = Kvv.NU5In;
  		  Kvv.VU50 = Kvv.VU50In;

		  Kvv.JobCo = Kvv.M24 | Kvv.M5 | Kvv.M5R;
		  Kvv.St = 2;
		}//3
		else
		{
			 Kvv.Info.bits.MisMaska = 1;
	     }	
	   }//2
	   else
	   Kvv.St=2;	
	 }//1
}
//=========================
void SetRd (void)
	{
	  if (Kvv.Timer >0)
	  {//2
		ADCS0=0x1b;	//I job
 		READC
 		Kvv.AnData[18]=0x3ff & ADCR; 
		ADCS0=0x24;	//voltmetr
	 	READC
	 	Kvv.AnData[19]=0x3ff & ADCR; 

	    Read();
	    Compare();
/*	     if ((Kvv.AdDelay & 0x80) ==1)
	     {//3
	      if (Kvv.Timer2< Kvv.Tmax)
	      {//4
	      	if (Range())
	      	 {//5
	      	   Kvv.Delay = Kvv.Timer2;
	      	   Kvv.St = 1;	
	           Kvv.Timer = 0;
	      	 }//5
	      } //4
	      else
	      { //6
	        //write mistake
	           Kvv.Info.bits.MisTMax=1;	
	      	   Kvv.St = 1;	
	           Kvv.Timer = 0;
	      }	//6
	     }//3
	     else
	     { //7
*/	      	   Kvv.St = 1;	
//	           Kvv.Timer = 0;
//	     }	//7
	  }//2
	}     
//==========
BYTE Change(BYTE num, BYTE* mas1, BYTE* mas2)
	{
	 BYTE i; 
	 for (i=0;i<num;i++)
	 {
	  if ((mas1[i]) != (mas2[i]))
	  return 1;	
	 }
	 return 0;
	}
//===============
BYTE Range(void)
	{
	  BYTE job, adres;
	  job = Kvv.DelayIn[0] & 0xf;
	  adres = Kvv.DelayIn[0] >> 4;
	  switch(job)
	  {//2
	    case 1:	//+
	    if (((Kvv.M24 >> adres) & 0xfffe) ==1)
	     return( (Kvv.AnData[adres] >= Kvv.NU24) && (Kvv.AnData[adres] <= Kvv.VU24));
	    else
	     return( (Kvv.AnData[adres] >= Kvv.NU5) && (Kvv.AnData[adres] <= Kvv.VU5));

	    case 2:	//-
	    if (((Kvv.M24 >> adres) & 0xfffe) ==1)
	     return(Kvv.AnData[adres] <= Kvv.VU240);
	     else	
	     return(Kvv.AnData[adres] <= Kvv.VU50);

	    case 3:	//n 
	     if( (Kvv.AnData[adres] > Kvv.NU5) && (Kvv.AnData[adres] < Kvv.VU5))
	     return (1);
	     else	
	     return (0);
	    case 4:	//0
	     if(Kvv.AnData[adres] < Kvv.VU50)
	     return (1);
	     else	
	     return (0);
	  }//2	
	}
//===============
void Read(void)
{
	BYTE i,j;
	j=1;
	for (i=0;i<16;i++)
	    {//4
//	     if ((Kvv.JobCo & j)==1) //
//	      	{//5
	      	 if ((i & 8)==0)
		       PDR4=i | 8;
		    else
		      PDR4=0x10 | i & 0xf7;
			  READC	
 	      	  Kvv.AnData[i]=0x3ff & ADCR; //adc
//		}//5
//		else
//		Kvv.AnData[i]=0; //adc
	 }//4
	     PDR4=0;
}
//=================
void Compare(void)
{//1
	BYTE i;
	WORD fil24, fil5;
	fil24=Kvv.M24;
	fil5=Kvv.M5 | Kvv.M5R;
	 for(i=0;i<16;i++)
	  {//2
	    if (fil24 & 1)	//24v
	     {//3
	     	if ((Kvv.AnData[i] <= Kvv.VU24) && (Kvv.AnData[i] >= Kvv.NU24))
	     	{//31
	     	  Kvv.DiData |= 1<< i;	
	     	  Kvv.Mistake &= ~(1<< i);	
	     	}//31
	     	else
	     	{//4
	         if (Kvv.AnData[i] < Kvv.VU240)
	     	  {//41
	     	    Kvv.DiData &= ~(1<< i);	
	     	    Kvv.Mistake &= ~(1<< i);	
	     	  }//41
	         else
		  {	         
	      	   Kvv.DiData |= 1<< i;		//wr mistake
	      	   Kvv.Mistake |= 1<< i;
	      	  }
	      	 } //4 	
	     }//3
	     else
	      {//5
	       if (fil5 & 1)	//5v and 5rv
	      	{//6
	     	if ((Kvv.AnData[i] <= Kvv.VU5) && (Kvv.AnData[i] >= Kvv.NU5))
	     	{//7
	     	  Kvv.DiData |= 1<< i;	
	     	  Kvv.Mistake &= ~(1<< i);	
	     	}//7
	     	else
	     	{//8
	     	  if (Kvv.AnData[i] < Kvv.VU50)
	     	  {//81
	     	    Kvv.DiData &= ~(1<< i);	
	     	    Kvv.Mistake &= ~(1<< i);	
	     	  }//81
	         else
	      	   Kvv.DiData |= 1<< i;	//wr mistake
	      	   Kvv.Mistake |= 1<< i;
	      	}//8
	      }//6
	        else
	         {//9
	     	   Kvv.DiData &= ~(1<< i);	
	      	   Kvv.Mistake |= 1<< i;
	      	  }//9 
	     }//5
	 fil24 = fil24 >>1;
	 fil5 = fil5 >>1;
	}//2
	Kvv.DDate[0] = (BYTE)Kvv.DiData; 
	Kvv.DDate[1] = (BYTE)(Kvv.DiData >> 8); 
	Kvv.DMis[0] = (BYTE)Kvv.Mistake; 
	Kvv.DMis[1] = (BYTE)(Kvv.Mistake >> 8); 	
	}//1
//=================

/*
//init for NDD16
	DDR0=0x00;
	DDR1=0x03;
	DDR2=0x00;
	DDR4=0x00;
	DDR5=0x00;
	DDR6=0x6F;
	DDR7=0x00;
	DDR8=0x00;
	DDR9=0x00;
	//------------------
	LEDR=1;
	LEDG=1;
	//------------------
	//    þ             
	PWR1=0;
	PWR2=0;
	//------------------
	//    þ                  
	TST1=1;
	TST2=1;
	//------------------
	//    þ         û
	G1=0;
	G2=0;
	//------------------
	Kvv.Info.word=0;
	Kvv.Info.bits.Addr=ADDR;
	ADDR_NODE		  =ADDR;
//end of init NDD16	
//===============
void Read(void)
{
	BYTE i;
	for (i=0;i<16;i++)
	    {//4
	     if ((Kvv.Param[i] & 0x8)==0) //rd only in
	      	{//5
	      	 if ((i & 8)==0)
		  PDR2=(i | 8);
		 else
		  PDR2=i | 0x10;
		  ADCS1_STRT =1;
 	     	  while(ADCS1_INT==0)
 	      		{
 	   __wait_nop();
 	      		} 
 	      	  Kvv.AnData[i]=0x3ff & (WORD)ADCR0; //adc
 	          ADCS1_INT =0;
		}//5
	     }//4
	     PDR2=0;
	}
//=================
*/
//===============
BYTE RangeOld(void)
	{
	  BYTE level, adres;
	  level = Kvv.AdDelay >> 4;
	  adres = Kvv.AdDelay & 0xf;
	  switch(level)
	  {//2
	    case 1:	//24B
	     if( (Kvv.AnData[adres] > Kvv.NU24) && (Kvv.AnData[adres] < Kvv.VU24))
	     return (1);
	     else	
	     return (0);
	    case 2:	//5B
	     if( (Kvv.AnData[adres] > Kvv.NU5) && (Kvv.AnData[adres] < Kvv.VU5))
	     return (1);
	     else	
	     return (0);
	    case 3:	//5B WIHT R
	     if( (Kvv.AnData[adres] > Kvv.NU5) && (Kvv.AnData[adres] < Kvv.VU5))
	     return (1);
	     else	
	     return (0);
	    case 4:	//0
	     if(Kvv.AnData[adres] < Kvv.VU50)
	     return (1);
	     else	
	     return (0);
	  }//2	
	}

 #endif