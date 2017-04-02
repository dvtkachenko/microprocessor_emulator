# ifndef __TVS2_CPP
# define __TVS2_CPP 1

# include "service\service.cpp"
# include "items.lib\TVs2.hpp"
# include "class\TWin_d.cpp"
# include <stdlib.h>
# include <alloc.h>

# define NUM_PARAM_VS2    1 // число параметров инициализации БИС К1804ВС2
// 1 - кол-во секций

// // // // // // // // // // // // // // // // // // // // // // // //
//  Описание прототипов методов класса TVs2 - БИС К1804ВС2
// // // // // // // // // // // // // // // // // // // // // // // //

//////////////////////////////////////////////////////////////////////////////

/////      СЕРВИСНАЯ ФУНКЦИЯ ВС2                 ////////

  void TVs2::SLL(unsigned long *F,unsigned long *PF3,unsigned long *PF0,unsigned long *DY,unsigned SekCount)
   {
     unsigned RazrCount=SekCount<<2;
     unsigned long Mask= 0xFFFFFFFF >> (32-RazrCount);

     *PF3=(*F>>(RazrCount-1));
     *DY=((*F<<1) | *PF0)&Mask;
   }

/////      СЕРВИСНАЯ ФУНКЦИЯ ВС2                 ////////

  void TVs2::SLA(unsigned long *F,unsigned long *PF3,unsigned long *PF0,unsigned long *DY,unsigned SekCount)
   {
     unsigned RazrCount=SekCount<<2;
     unsigned long Mask= 0x80000000 >> (32-RazrCount);
     unsigned long Sign=0;

     *PF3=(*F>>(RazrCount-2))&1;
     Sign=*F&Mask;
     Mask= 0x7FFFFFFF >> (32-RazrCount);
     *DY=(((*F<<1) | *PF0)&Mask) | Sign;
   }

/////      СЕРВИСНАЯ ФУНКЦИЯ ВС2                 ////////

  void TVs2::SRA(unsigned long *F,unsigned long *PF3,unsigned long *PF0,unsigned long *DY,unsigned SekCount)
   {
     unsigned RazrCount=SekCount<<2;
     unsigned long Mask= 0x80000000 >> (32-RazrCount);
     unsigned long Sign=0;

     *PF0=*F&1;
     Sign=*F&Mask;
     Mask= 0x3FFFFFFF >> (32-RazrCount);
     *DY= ((*F>>1)&Mask) | (*PF3<<(16+RazrCount-16-2)) | Sign;
   }

/////      СЕРВИСНАЯ ФУНКЦИЯ ВС2                 ////////

  void TVs2::SRL(unsigned long *F,unsigned long *PF3,unsigned long *PF0,unsigned long *DY,unsigned SekCount)
   {
     unsigned RazrCount=SekCount<<2;
     unsigned long Mask= 0xFFFFFFFF >> (32-RazrCount);

     *PF0= *F&1;
     *DY=((*F>>1) | *PF3<<(16+RazrCount-16-1))&Mask;
   }

/////      СЕРВИСНАЯ ФУНКЦИЯ ВС2                 ////////

  void TVs2::SLO(unsigned long RLow,unsigned long SLow,unsigned long *FLow,unsigned long RHi,unsigned long SHi,unsigned long *FHi,unsigned long C0,unsigned SekCount)
   {
     unsigned long C4=0;
     *FLow = RLow + SLow + C0;
     if(SekCount>4)
       {
	  C4 = (*FLow>>16)&1;
	  *FHi= RHi + SHi + C4 ;
	  *FLow &= 0xFFFF;
       }
      else
	  *FHi=0;
   }

//=====================================================================
//  Загрузка и преобразование параметров с входов ВС2
//---------------------------------------------------------------------
  void TVs2::LoadParam(void)
    {

      AA = StrToUnLong(_AA,0,4);
      AB = StrToUnLong(_AB,0,4);
      C0  = *_C0;
      PF0 = *_PF0;
      PF3 = *_PF3;
      PQ0 = *_PQ0;
      PQ3 = *_PQ3;
      KO  = StrToUnLong(_KO,0,3);   //  код приемника результата операции
      OP  = StrToUnLong(_OP,0,4);   //  код операции
      EA  = *_EA;
      I0  = *_I0;
      OEB = *_OEB;
      IEN = *_IEN;
      DA = StrToUnLong(_DA,0,4*SekCount);
      DB = StrToUnLong(_DB,0,4*SekCount);
      //
    }

//=====================================================================
//  Выгрузка и преобразование параметров на входы ВС2 из
//  внутренних переменных
//---------------------------------------------------------------------
  void TVs2::StoreParam(void)
    {

      *_PF0 = (byte)PF0;
      *_PF3 = (byte)PF3;
      *_PQ0 = (byte)PQ0;
      *_PQ3 = (byte)PQ3;
      *_F3 = (byte)N;
      *_Z = (byte)Z;
      *_C4 = (byte)C4;
      *_OVR = (byte)V;

      UnLongToBin(DY,_DY,4*SekCount);
      //
    }

//=====================================================================
//  Метод Run . Осуществляет моделирование функций БИС К1804ВС2
//              в дискретные моменты времени(кванты)
//---------------------------------------------------------------------
  void TVs2::Run(void)
    {

      unsigned RazrCount=SekCount<<2;
      unsigned long R=0,S=0,F=0,w;
      unsigned long RLow,RHi=0,SLow,SHi=0,FLow,FHi=0,sdq;
      unsigned long Mask=0;

	    /*------------------------------*/
	    /*  выбор источников операндов  */
	    /*------------------------------*/
      if (EA==1) R=DA; else R=RON[AA];
      if (I0==1) S=RQ; else if (OEB==1) S=DB;
			    else S=RON[AB];

      if (SekCount<=4)
	{
	  RLow=R & 0x0000FFFF;   /* младшие разряды R  */
	  SLow=S & 0x0000FFFF;   /* младшие разряды S  */
	  Mask=0x0000FFFF>>(16-RazrCount);
	  RLow&=Mask;
	  if (RLow&(0x1<<16+RazrCount-16-1))
	    RLow|=0x80000000>>(32-RazrCount-1);
	  RHi=0;
	  SLow&=Mask;
	  if (SLow&(0x1<<16+RazrCount-16-1))
	    SLow|=0x80000000>>(32-RazrCount-1);
	  SHi=0;
	}
      else
	{
	  RLow=R & 0x0000FFFF;   /* младшие разряды R  */
	  SLow=S & 0x0000FFFF;   /* младшие разряды S  */
	  RHi=R >> 16 ;    /* старшие разряды R  */
	  SHi=S >> 16 ;    /* старшие разряды R  */
	  Mask=0x0000FFFF>>(32-RazrCount);
	  RHi&=Mask;
	  if (RHi&(0x1<<RazrCount-17))
	    RHi|=0x80000000>>(32-RazrCount+15);
	  SHi&=Mask;
	  if (SHi&(0x1<<RazrCount-17))
	    SHi|=0x80000000>>(32-RazrCount+15);
	}


	  /*----------------------------------*/
	  /*  выбор стандартной функции  АЛУ  */
	  /*----------------------------------*/
      if ((OP!=0)||(I0!=0))
       {
	switch (OP)
	{
	 case 0 :FHi=0X1FFFF;FLow=0XFFFF;break;
	 case 1 :
		  if (SekCount<=4)
		     {
		       Mask=0x0001FFFF>>(16-RazrCount);
		       RLow=((~RLow) & Mask );
		     }
		   else
		     {
		       RLow=((~RLow) & 0X1FFFF);
		       Mask=0x0001FFFF>>(32-RazrCount);
		       RHi=(~RHi) & Mask;
		     }
		  SLO(RLow,SLow,&FLow,RHi,SHi,&FHi,C0,SekCount);
		  break;

	 case 2 :
		  if (SekCount<=4)
		    {
		      Mask=0x0001FFFF>>(16-RazrCount);
		      SLow=((~SLow) & Mask );
		    }
		  else
		    {
		      SLow=((~SLow) & 0XFFFF);
		      Mask=0x0001FFFF>>(32-RazrCount);
		      SHi=(~SHi) & Mask;
		    }
		  SLO(RLow,SLow,&FLow,RHi,SHi,&FHi,C0,SekCount);
		  break;

	 case 3 :
		  SLO(RLow,SLow,&FLow,RHi,SHi,&FHi,C0,SekCount);
		  break;

	 case 4 :
		  RLow=RHi=0;
		  SLO(RLow,SLow,&FLow,RHi,SHi,&FHi,C0,SekCount);
		  break;

	 case 5 :
		  RLow=RHi=0;
		  if (SekCount<=4)
		    {
		      Mask=0x0001FFFF>>(16-RazrCount);
		      SLow=((~SLow) & Mask );
		    }
		  else
		    {
		      SLow=((~SLow) & 0XFFFF);
		      Mask=0x0001FFFF>>(32-RazrCount);
		      SHi=(~SHi) & Mask;
		    }
		  SLO(RLow,SLow,&FLow,RHi,SHi,&FHi,C0,SekCount);
		  break;

	 case 6 :
		  SLow=SHi=0;
		  SLO(RLow,SLow,&FLow,RHi,SHi,&FHi,C0,SekCount);
		  break;

	 case 7 :
		  SLow=SHi=0;
		  if (SekCount<=4)
		     {
		       Mask=0x0001FFFF>>(16-RazrCount);
		       RLow=((~RLow) & Mask );
		     }
		   else
		     {
		       RLow=((~RLow) & 0X1FFFF);
		       Mask=0x0001FFFF>>(32-RazrCount);
		       RHi=(~RHi) & Mask;
		     }
		  SLO(RLow,SLow,&FLow,RHi,SHi,&FHi,C0,SekCount);
		  break;

	 case 8 : FLow=F=FHi=0;break;
	 case 9 : F=(~R) & S;break;
	 case 10: F=(~(R ^ S));break;
	 case 11: F=R^S;break;
	 case 12: F=R & S;break;
	 case 13: F=(~(R|S));break;
	 case 14: F=(~(R & S));break;
	 case 15: F=R | S;
	}  /*  окончание выполнения стандартной функции АЛУ  */

      if ((OP < 8) && (OP>0))
	{
	  SLO(RLow,SLow,&FLow,RHi,SHi,&FHi,C0,SekCount);
	  if(SekCount>4)
	    {
	      Mask = 0xFFFF>>(32-RazrCount);
	      C4 = (((RHi&Mask)+(SHi&Mask)+C4)>>(RazrCount-16))&1;
	      V = ((FHi>>(RazrCount-17))^(FHi>>(RazrCount-16)))&1 ;
	    }
	  else
	    {
	      Mask = 0xFFFF>>(16-RazrCount);
	      C4 = (((RLow&Mask)+(SLow&Mask)+C0)>>(RazrCount))&1;
	      V = ((FLow>>(RazrCount))^(FLow>>(RazrCount-1)))&1 ;
	    }
	  F=(FHi<<16) | FLow ;
	}
      else V = C4 = 0 ;
      Mask = 0xFFFFFFFF >> (32-RazrCount);
      F &= Mask;
      N = F >> (RazrCount-1);

	   /*--------------------------------------------*/
	   /*  выбор приемников для стандартных функций  */
	   /*--------------------------------------------*/
       switch(KO)
	{
	 case  0: SRA(&F,&PF3,&PF0,&DY,SekCount);
		  sdq=RQ;w=0;break;

	 case  1: SRL(&F,&PF3,&PF0,&DY,SekCount);
		  sdq=RQ;w=0;break;

	 case  2: SRA(&F,&PF3,&PF0,&DY,SekCount);
		  SRL(&RQ,&PQ3,&PQ0,&sdq,SekCount);
		  w=0;break;

	 case  3: SRL(&F,&PF3,&PF0,&DY,SekCount);
		  SRL(&RQ,&PQ3,&PQ0,&sdq,SekCount);
		  w=0;break;

	 case  4: DY=F;sdq=RQ;w=0;break;

	 case  5: DY=F;
		  SRL(&RQ,&PQ3,&PQ0,&sdq,SekCount);
		  w=1;break;

	 case  6: DY=sdq=F;w=0;break;

	 case  7: DY=sdq=F;w=1;break;

	 case  8: SLA(&F,&PF3,&PF0,&DY,SekCount);
		  sdq=RQ;w=0;break;

	 case  9: SLL(&F,&PF3,&PF0,&DY,SekCount);
		  sdq=RQ;w=0;break;

	 case 10: SLL(&RQ,&PQ3,&PQ0,&sdq,SekCount);
		  SLA(&F,&PF3,&PF0,&DY,SekCount);
		  w=0;break;

	 case 11: SLL(&RQ,&PQ3,&PQ0,&sdq,SekCount);
		  SLL(&F,&PF3,&PF0,&DY,SekCount);
		  w=0;break;

	 case 12: DY=F;sdq=RQ;w=1;break;

	 case 13: DY=F;
		  SLL(&RQ,&PQ3,&PQ0,&sdq,SekCount);
		  w=1;break;

	 case 14: DY=PF0*Mask;sdq=RQ;w=0;

	 case 15: DY=F;sdq=RQ;w=0;break;

	}  /*  окончание выбора приёмников для стандартных функций  */

	if (DY==0) Z=1;    /*  формирование  */
	else Z=0;           /*   признака Z   */

       }   /*  окончание работы со стандартными функциями  */


	       /*---------------------------*/
	       /*  специальные функции АЛУ  */
	       /*---------------------------*/
      else
       { switch(KO)
	{
	 case  0: Z=RQ & 1;
		  if(Z==0) RLow=RHi=0;
		  SLO(RLow,SLow,&FLow,RHi,SHi,&FHi,C0,SekCount);
		  if(SekCount>4)
		    {
		      Mask = 0xFFFF>>(32-RazrCount);
		      C4 = (((RHi&Mask)+(SHi&Mask)+C4)>>(RazrCount-16))&1;
		      V = ((FHi>>(RazrCount-17))^(FHi>>(RazrCount-16)))&1 ;
		    }
		  else
		    {
		      Mask = 0xFFFF>>(16-RazrCount);
		      C4 = (((RLow&Mask)+(SLow&Mask)+C0)>>(RazrCount))&1;
		      V = ((FLow>>(RazrCount))^(FLow>>(RazrCount-1)))&1 ;
		    }
		  F=(FHi<<16) | FLow ;
		  Mask = 0xFFFFFFFF >> (32-RazrCount);
		  F &= Mask;
		  N = F >> (RazrCount-1);
		  SRL(&F,&C0,&PF0,&DY,SekCount);
		  SRL(&RQ,&PF0,&PQ0,&sdq,SekCount);
		  break;

	 case  2: Z=RQ & 1;
		  if(Z==0) RLow=RHi=0;
		  SLO(RLow,SLow,&FLow,RHi,SHi,&FHi,C0,SekCount);
		  if(SekCount>4)
		    {
		      Mask = 0xFFFF>>(32-RazrCount);
		      C4 = (((RHi&Mask)+(SHi&Mask)+C4)>>(RazrCount-16))&1;
		      V = ((FHi>>(RazrCount-17))^(FHi>>(RazrCount-16)))&1 ;
		    }
		  else
		    {
		      Mask = 0xFFFF>>(16-RazrCount);
		      C4 = (((RLow&Mask)+(SLow&Mask)+C0)>>(RazrCount))&1;
		      V = ((FLow>>(RazrCount))^(FLow>>(RazrCount-1)))&1 ;
		    }
		  F=(FHi<<16) | FLow ;
		  Mask = 0xFFFFFFFF >> (32-RazrCount);
		  F &= Mask;
		  N = F >> (RazrCount-1);
		  PF3=N^V;
		  SRL(&F,&PF3,&PF0,&DY,SekCount);
		  SRL(&RQ,&PF0,&PQ0,&sdq,SekCount);
		  break;

	 case  4: RHi=0;RLow=1;
		  SLO(RLow,SLow,&FLow,RHi,SHi,&FHi,C0,SekCount);
		  if(SekCount>4)
		    {
		      Mask = 0xFFFF>>(32-RazrCount);
		      C4 = (((RHi&Mask)+(SHi&Mask)+C4)>>(RazrCount-16))&1;
		      V = ((FHi>>(RazrCount-17))^(FHi>>(RazrCount-16)))&1 ;
		    }
		  else
		    {
		      Mask = 0xFFFF>>(16-RazrCount);
		      C4 = (((RLow&Mask)+(SLow&Mask)+C0)>>(RazrCount))&1;
		      V = ((FLow>>(RazrCount))^(FLow>>(RazrCount-1)))&1 ;
		    }
		  F=(FHi<<16) | FLow ;
		  Mask = 0xFFFFFFFF >> (32-RazrCount);
		  F &= Mask;
		  N = F >> (RazrCount-1);
		  if (F==0) Z=1;
		   else Z=0;
		  DY=F;sdq=RQ;
		  break;

	 case  5: Z=N=S >> (RazrCount-1); RLow=RHi=0;
		  V=0;
		  if (Z==1)
		   {
		     if (SekCount<=4)
		       {
			 Mask=0x0001FFFF>>(16-RazrCount);
			 SLow=((~SLow) & Mask );
		       }
		     else
		       {
			 SLow=((~SLow) & 0XFFFF);
			 Mask=0x0001FFFF>>(32-RazrCount);
			 SHi=(~SHi) & Mask;
		       }
		   }
		  SLO(RLow,SLow,&FLow,RHi,SHi,&FHi,Z,SekCount);
		  if(Z==1)
		   {
		     if (SekCount<=4)
		       {
			 FLow|=0xC0000000>>(32-RazrCount-1);
			 FHi=0;
		       }
		     else
			 FHi|=0xC0000000>>(32-RazrCount+15);
		   }
		  F=(FHi<<16) | FLow ;
		  Mask = 0xFFFFFFFF >> (32-RazrCount);
		  F &= Mask;
		  if(SekCount>4)
		    {
		      Mask = 0xFFFF>>(32-RazrCount);
		      C4 = (((RHi&Mask)+(SHi&Mask)+C4)>>(RazrCount-16))&1;
		    }
		  else
		    {
		      Mask = 0xFFFF>>(16-RazrCount);
		      C4 = (((RLow&Mask)+(SLow&Mask)+C0)>>(RazrCount))&1;
		    }
		  DY=F;
		  sdq=RQ;
		  break;

	 case  6:
		  Z=RQ & 1;
		  if (Z==1)
		   {
		     if (SekCount<=4)
		       {
			 Mask=0x0001FFFF>>(16-RazrCount);
			 RLow=((~RLow) & Mask );
		       }
		     else
		       {
			 RLow=((~RLow) & 0XFFFF);
			 Mask=0x0001FFFF>>(32-RazrCount);
			 RHi=(~RHi) & Mask;
		       }
		   }
		  else
		   RLow=RHi=0;
		  SLO(RLow,SLow,&FLow,RHi,SHi,&FHi,C0,SekCount);
		  if(SekCount>4)
		    {
		      Mask = 0xFFFF>>(32-RazrCount);
		      C4 = (((RHi&Mask)+(SHi&Mask)+C4)>>(RazrCount-16))&1;
		      V = ((FHi>>(RazrCount-17))^(FHi>>(RazrCount-16)))&1 ;
		    }
		  else
		    {
		      Mask = 0xFFFF>>(16-RazrCount);
		      C4 = (((RLow&Mask)+(SLow&Mask)+C0)>>(RazrCount))&1;
		      V = ((FLow>>(RazrCount))^(FLow>>(RazrCount-1)))&1 ;
		    }
		  F=(FHi<<16) | FLow ;
		  Mask = 0xFFFFFFFF >> (32-RazrCount);
		  F &= Mask;
		  N = F >> (RazrCount-1);
		  PF3=N^V;
		  SRL(&F,&PF3,&PF0,&DY,SekCount);
		  SRL(&RQ,&PF0,&PQ0,&sdq,SekCount);
		  break;

	 case  8:
		  C4 = ((RQ>>(RazrCount-1))^(RQ>>(RazrCount-2)))&1 ;
		  V = ((RQ>>(RazrCount-2))^(RQ>>(RazrCount-3)))&1 ;
		  if (RQ==0)
		   Z=1;
		  else
		   Z=0;
		  RLow=RHi=0;
		  SLO(RLow,SLow,&FLow,RHi,SHi,&FHi,C0,SekCount);
		  F=(FHi<<16) | FLow ;
		  Mask = 0xFFFFFFFF >> (32-RazrCount);
		  F &= Mask;
		  N = F >> (RazrCount-1);
		  DY=F;
		  if ((Z==0)&&(C4==0))
		   sdq=(RQ<<1);
		  else
		   sdq=RQ;
		  break;

	 case 10: if (RQ|S==0)
		   Z=1;
		  else
		   Z=0;
		  RLow=RHi=0;
		  SLO(RLow,SLow,&FLow,RHi,SHi,&FHi,C0,SekCount);
		  if(SekCount>4)
		    {
		      Mask = 0xFFFF>>(32-RazrCount);
		      C4 = (((RHi&Mask)+(SHi&Mask)+C4)>>(RazrCount-16))&1;
		      V = ((FHi>>(RazrCount-17))^(FHi>>(RazrCount-16)))&1 ;
		    }
		  else
		    {
		      Mask = 0xFFFF>>(16-RazrCount);
		      C4 = (((RLow&Mask)+(SLow&Mask)+C0)>>(RazrCount))&1;
		      V = ((FLow>>(RazrCount))^(FLow>>(RazrCount-1)))&1 ;
		    }
		  F=(FHi<<16) | FLow ;
		  Mask = 0xFFFFFFFF >> (32-RazrCount);
		  F &= Mask;
		  N = F >> (RazrCount-1);
		  if ((Z==0)&&(C4==0))
		   {
		    Mask=0;
		    SLL(&RQ,&PQ3,&Mask,&sdq,SekCount);
		    SLL(&F,&PF3,&PQ3,&DY,SekCount);
		   }
		  else
		   {
		    sdq=RQ;
		    DY=F;
		   }
		  break;

	 case 12:
		  Z=(~(F^R)) >> (RazrCount-1);
		  if (Z==1)
		   {
		     if (SekCount<=4)
		       {
			 Mask=0x0001FFFF>>(16-RazrCount);
			 RLow=((~RLow) & Mask );
		       }
		     else
		       {
			 RLow=((~RLow) & 0XFFFF);
			 Mask=0x0001FFFF>>(32-RazrCount);
			 RHi=(~RHi) & Mask;
		       }
		   }
		  SLO(RLow,SLow,&FLow,RHi,SHi,&FHi,Z,SekCount);
		  if(SekCount>4)
		    {
		      Mask = 0xFFFF>>(32-RazrCount);
		      C4 = (((RHi&Mask)+(SHi&Mask)+C4)>>(RazrCount-16))&1;
		      V = ((FHi>>(RazrCount-17))^(FHi>>(RazrCount-16)))&1 ;
		    }
		  else
		    {
		      Mask = 0xFFFF>>(16-RazrCount);
		      C4 = (((RLow&Mask)+(SLow&Mask)+C0)>>(RazrCount))&1;
		      V = ((FLow>>(RazrCount))^(FLow>>(RazrCount-1)))&1 ;
		    }
		  F=(FHi<<16) | FLow ;
		  Mask = 0xFFFFFFFF >> (32-RazrCount);
		  F &= Mask;
		  N = F >> (RazrCount-1);
		  Mask=(~(F^R)) >> (RazrCount-1);
		  SLL(&RQ,&PF0,&Mask,&sdq,SekCount);
		  SLL(&F,&PF3,&PF0,&DY,SekCount);
		  break;

	 case 14:
		  Z=(~(F^R)) >> (RazrCount-1);
		  if (Z==1)
		   {
		     if (SekCount<=4)
		       {
			 Mask=0x0001FFFF>>(16-RazrCount);
			 RLow=((~RLow) & Mask );
		       }
		     else
		       {
			 RLow=((~RLow) & 0XFFFF);
			 Mask=0x0001FFFF>>(32-RazrCount);
			 RHi=(~RHi) & Mask;
		       }
		   }
		  SLO(RLow,SLow,&FLow,RHi,SHi,&FHi,Z,SekCount);
		  if(SekCount>4)
		    {
		      Mask = 0xFFFF>>(32-RazrCount);
		      C4 = (((RHi&Mask)+(SHi&Mask)+C4)>>(RazrCount-16))&1;
		      V = ((FHi>>(RazrCount-17))^(FHi>>(RazrCount-16)))&1 ;
		    }
		  else
		    {
		      Mask = 0xFFFF>>(16-RazrCount);
		      C4 = (((RLow&Mask)+(SLow&Mask)+C0)>>(RazrCount))&1;
		      V = ((FLow>>(RazrCount))^(FLow>>(RazrCount-1)))&1 ;
		    }
		  F=(FHi<<16) | FLow ;
		  Mask = 0xFFFFFFFF >> (32-RazrCount);
		  F &= Mask;
		  N = F >> (RazrCount-1);
		  PQ0=1;
		  SLL(&RQ,&PF0,&PQ0,&sdq,SekCount);
		  DY=F;
	}
       w=0;
      }    /*  окончание выполнения специальной функции  */

     if (IEN==0)                /*  запись в     */
      {
       RQ=sdq;                  /*  регистры     */
       if (w==0)
	RON[AB]=DY;   /*  RQ и RON[AB] */
      }
    }  // end of Run()

//=====================================================================
//  Процедура инициализации
//---------------------------------------------------------------------
  int TVs2::Init(string80 Array[])
    {
      byte i;
      SekCount = (byte) atoi (Array[0]);
      if (SekCount == 0)
	{
	  Error = ERROR;
	  return(ERROR);
	}

      if ((Parameters = (byte *)malloc(ALL_PIN_VS2 + 12*SekCount - 12))==NULL)
	{
	  Error = ERROR;
	  return(ERROR);
	}

      _PQ0 = &Parameters[0];
      _EA  = &Parameters[1];
      _DA  = &Parameters[2];
      _KO  = &Parameters[2+4*SekCount]  ;
      _C0  = &Parameters[3+4*SekCount]  ;
      _C4  = &Parameters[4+4*SekCount]  ;
      _OVR = &Parameters[5+4*SekCount]  ;
      _F3  = &Parameters[7+4*SekCount]  ;
      _OEY = &Parameters[8+4*SekCount]  ;
      _DY  = &Parameters[9+4*SekCount]  ;
      _PF0 = &Parameters[9+8*SekCount]  ;
      _PF3 = &Parameters[10+8*SekCount] ;
      _Z   = &Parameters[11+8*SekCount] ;
      _DB  = &Parameters[12+8*SekCount] ;
      _AA  = &Parameters[12+12*SekCount];
      _OEB = &Parameters[13+12*SekCount];
      _OP  = &Parameters[14+12*SekCount];
      _WE  = &Parameters[18+12*SekCount];
      _IEN = &Parameters[19+12*SekCount];
      _LSS = &Parameters[20+12*SekCount];
      _MSSW= &Parameters[21+12*SekCount];
      _I0  = &Parameters[22+12*SekCount];
      _CLK = &Parameters[24+12*SekCount];
      _AB  = &Parameters[25+12*SekCount];
      _PQ3 = &Parameters[26+12*SekCount];

      return(NO_ERROR);
    }

//=====================================================================
//  Процедура визуализации состояния выводов элемента
//---------------------------------------------------------------------
  void TVs2::Show(void)
    {
    }

//=====================================================================
//  Конструктор
//---------------------------------------------------------------------
  TVs2::TVs2(int Number) : TModelItem(Number)
    {
      SetNumParameters(NUM_PARAM_VS2);
    }

//=====================================================================
//  Деструктор
//---------------------------------------------------------------------
  TVs2::~TVs2()
    {
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  Конец описания прототипов методов класса TVs2
// // // // // // // // // // // // // // // // // // // // // // // //
# endif
