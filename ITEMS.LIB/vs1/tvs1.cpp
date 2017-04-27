# ifndef __TVS1_CPP
# define __TVS1_CPP 1

# include "..\..\service\service.h"
# include "TVs1.hpp"
# include <vcl\dstring.h>
# include <stdlib.h>
# include <alloc.h>
# include <mem.h>

# define NUM_PARAM_VS1    1 // число параметров инициализации БИС К1804ВС1
// 1 - кол-во секций

// // // // // // // // // // // // // // // // // // // // // // // //
//  Описание прототипов методов класса TVs1 - БИС К1804ВС1
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//  Загрузка и преобразование параметров с входов ВС1
//---------------------------------------------------------------------
  void TVs1::LoadParam(void)
    {
      char buf[40];
      int Bits = SekCount<<2;
/*
      if(CheckUndefLevel(_AA,4))
        throw UndefLevelError();
      if(CheckUndefLevel(_KO,3))
        throw UndefLevelError();
      if(CheckUndefLevel(_KI,3))
        throw UndefLevelError();
      if(CheckUndefLevel(_AB,4))
        throw UndefLevelError();
      if(CheckUndefLevel(_OP,3))
        throw UndefLevelError();
      if(CheckUndefLevel(_C0,1))
        throw UndefLevelError();
      if(CheckUndefLevel(_PF0,1))
        throw UndefLevelError();
      if(CheckUndefLevel(_PF3,1))
        throw UndefLevelError();
      if(CheckUndefLevel(_PQ0,1))
        throw UndefLevelError();
      if(CheckUndefLevel(_PQ3,1))
        throw UndefLevelError();
      if(CheckUndefLevel(_OE,1))
        throw UndefLevelError();
      if(CheckUndefLevel(_DA,Bits))
        throw UndefLevelError();
*/
      if ((*_PF0 & RECEIVE) && ((*_PF0 & 0x0F)!= HZ))
        PF0 = (dword)ConvertLevel(_PF0);
      if ((*_PF3 & RECEIVE) && ((*_PF3 & 0x0F)!= HZ))
        PF3 = (dword)ConvertLevel(_PF3);
      if ((*_PQ0 & RECEIVE) && ((*_PQ0 & 0x0F)!= HZ))
        PQ0 = (dword)ConvertLevel(_PQ0);
      if ((*_PQ3 & RECEIVE) && ((*_PQ3 & 0x0F)!= HZ))
        PQ3 = (dword)ConvertLevel(_PQ3);

      CLK = (dword)ConvertLevel(_CLK);
      C0  = (dword)ConvertLevel(_C0);  //  входной перенос в АЛУ
   	  OE  = (dword)ConvertLevel(_OE);  //  сигнал разрешения Y-выходов
      //
      memcpy(buf,_AA,4);
      StrRev(buf,4);
      AA = StrToUnLong((char*)buf,0,4); // сигналы адреса A для выбора из регистров
      //
      memcpy(buf,_AB,4);
      StrRev(buf,4);
      AB = StrToUnLong((char*)buf,0,4); // сигналы адреса B для выбора из регистров
      //
      memcpy(buf,_KO,3);
      StrRev(buf,3);
      KO = StrToUnLong((char*)buf,0,3); //  MI(I6-I8)
      //  код приемника результата операции
      //
      memcpy(buf,_KI,3);
      StrRev(buf,3);
      KI = StrToUnLong((char*)buf,0,3); //  MI(I0-I2)
      //  код источника операнда
      //
      memcpy(buf,_OP,3);
      StrRev(buf,3);
      OP = StrToUnLong((char*)buf,0,3); //  MI(I3-I5)
      //  код операции
      //
      memcpy(buf,_DA,Bits);
      StrRev(buf,Bits);
      DA = StrToUnLong((char*)buf,0,Bits); //  входная шина данных
    }

//=====================================================================
//  Выгрузка и преобразование параметров на входы ВС1 из
//  внутренних переменных
//---------------------------------------------------------------------
  void TVs1::StoreParam(void)
    {
      char buf[40];
      int i,Bits = SekCount<<2;

      if (OE == HI_LEVEL)
    	{
    	  for(i=0;i<Bits;i++)
    	    _Y[i] = (byte)(HZ | (_Y[i] & 0xF0));
    	}
      else
    	{
          UnLongToBin(DY,(char*)buf,Bits);
          StrRev(buf,Bits);
  	      for(i=0;i<Bits;i++)
       		_Y[i] = (byte)(buf[i] | (_Y[i] & 0xF0));
    	}
      // если вывод не в состоянии HZ и не явл-ся приемником то ...
      if ((!(*_PF0 & RECEIVE)) && ((*_PF0 & 0x0F)!= HZ))
        *_PF0 = (byte)(PF0 | (*_PF0 & 0xF0));
      if ((!(*_PF3 & RECEIVE)) && ((*_PF3 & 0x0F)!= HZ))
        *_PF3 = (byte)(PF3 | (*_PF3 & 0xF0));
      if ((!(*_PQ0 & RECEIVE)) && ((*_PQ0 & 0x0F)!= HZ))
        *_PQ0 = (byte)(PF0 | (*_PQ0 & 0xF0));
      if ((!(*_PQ3 & RECEIVE)) && ((*_PQ3 & 0x0F)!= HZ))
        *_PQ3 = (byte)(PF0 | (*_PQ3 & 0xF0));

      *_F3 = (byte)(N | (*_F3 & 0xF0));
      *_Z = (byte)(Z | (*_Z & 0xF0));
      *_C4 = (byte)(C4 | (*_C4 & 0xF0));
      *_OVR = (byte)(V | (*_OVR & 0xF0));
      //
    }

//=====================================================================
//  Метод Run . Осуществляет моделирование функций БИС К1804ВС1
//              в дискретные моменты времени(кванты)
//---------------------------------------------------------------------
  void TVs1::Run(void)
    {
      unsigned RazrCount=SekCount<<2;
      unsigned long R=0,S=0;
      unsigned long RLow,RHi=0,SLow,SHi=0,FLow,FHi=0;
      unsigned long Mask=0;

      try
        {
          LoadParam();
        }
      catch(UndefLevelError e)
        {
          return;
        }

      CurLevelClk = CLK;
      //--------------------------------------------------
      // Данное условие предназначено для моделирования работы
      // тактируемых(RgA,RgB) блоков ВC1.
      // Регистры RgA и RgB при CLK = HI_LEVEL пропускают на свои выходы
      // информацию из RON. При CLK = LOW_LEVEL сохраняет то состояние
      // которое было на входах в момент перехода из HI_LEVEL в LOW_LEVEL
      //--------------------------------------------------
      if (CurLevelClk == HI_LEVEL)
        {
          RgA = RON[AA];
          RgB = RON[AB];
        }

      //--------------------------------------------------
      // Данное условие предназначено для моделирования работы
      // тактируемых(RON) блоков ВC1.
      // Регистры RON при CLK = LOW_LEVEL пропускают на свои выходы
      // информацию поступающую из сдвигателя. При CLK = HI_LEVEL
      // сохраняет то состояние
      // которое было на входах в момент перехода из LOW_LEVEL в HI_LEVEL
      //--------------------------------------------------
      if (CurLevelClk == LOW_LEVEL)
        {
  	      /*----------------------------------------*/
          /* выбор источника для приемника RON[AB]  */
	      /*----------------------------------------*/

          Mask = 0xFFFFFFFF >> (32-RazrCount);
          switch (KO)
         	{
    	      case  2: case 3: RON[AB]=F;
    	    		   break;
        	  case  4: case 5: PF0=F&1;
        			   RON[AB]=((F>>1) | (PF3<<(16+RazrCount-16-1)))&Mask;
        			   break;
        	  case  6: case 7: RON[AB]=((F<<1) | PF0)&Mask;
        	}
        }

      //--------------------------------------------------
      // Данное условие предназначено для моделирования работы
      // тактируемого(RQ) блока ВC1.
      //--------------------------------------------------
      if ((PrevLevelClk == LOW_LEVEL) && (CurLevelClk == HI_LEVEL))
	  // моделирование процессов происходящих по приходу тактового
	  // импульса(RQ)
        {
	      /*-----------------------------------*/
	      /* выбор источника для приемника RQ  */
	      /*-----------------------------------*/
          Mask = 0xFFFFFFFF >> (32-RazrCount);
          switch (KO)
        	{
        	  case 0: RQ=F; break;
        	  case 4: PQ0=RQ & 1; RQ=((RQ>>1) | (PQ3<<(16+RazrCount-16-1)))&Mask; break;
        	  case 6: PQ3=(RQ>>(RazrCount-1)); RQ=((RQ<<1) | PQ0)&Mask;
        	}
        }

     //-----------------------------------------------------
     // ниже производится моделирование работы КЛС ВС1,
     // т.е. не тактируемых схем
     //-----------------------------------------------------

	   /*-----------------------------*/
	   /* выбор источника операнда R  */
	   /*-----------------------------*/

      switch (KI)
    	{
    	  case 0: case 1:         R=RgA; break;
    	  case 2: case 3: case 4: R=0; break;
    	  case 5: case 6: case 7: R=DA;
    	}

	   /*-----------------------------*/
	   /* выбор источника операнда S  */
	   /*-----------------------------*/
      switch (KI)
    	{
    	  case 0: case 2: case 6: S=RQ; break;
    	  case 1: case 3:         S=RgB; break;
    	  case 4: case 5:         S=RgA; break;
    	  case 7:                 S=0;
    	}

      if (SekCount<=4)
    	{
    	  RLow=R & 0x0000FFFF;   /* младшие разряды R  */
    	  SLow=S & 0x0000FFFF;   /* младшие разряды S  */
    	  Mask=0x0000FFFF>>(16-RazrCount);
    	  RLow&=Mask;
    	  if (RLow&(0x1<<(16+RazrCount-16-1)))
//	  if (RLow&(0x1<<(RazrCount-1)))
    	    RLow|=(unsigned long)(0x80000000>>(32-RazrCount-1));
    	  RHi=0;
    	  SLow&=Mask;
    	  if (SLow&(0x1<<(16+RazrCount-16-1)))
//	  if (SLow&(0x1<<(RazrCount-1)))
    	    SLow|=(unsigned long)(0x80000000>>(32-RazrCount-1));
    	  SHi=0;
    	}
      else
    	{
    	  RLow=R & 0x0000FFFF;   /* младшие разряды R  */
    	  SLow=S & 0x0000FFFF;   /* младшие разряды S  */
    	  RHi=R >> 16 ;    /* старшие разряды R  */
    	  SHi=S >> 16 ;    /* старшие разряды S  */
    	  Mask=0x0000FFFF>>(32-RazrCount);
    	  RHi&=Mask;
    	  if (RHi&(0x1<<(RazrCount-17)))
//	  if (RHi&(0x1<<(RazrCount-17)))
    	    RHi|=(unsigned long)(0x80000000>>(32-RazrCount+15));
    	  SHi&=Mask;
    	  if (SHi&(0x1<<(RazrCount-17)))
//	  if (SHi&(0x1<<(RazrCount-17)))
    	    SHi|=(unsigned long)(0x80000000>>(32-RazrCount+15));
    	}

	    /*-------------------------------*/
	    /* выполнение заданной операции  */
	    /*-------------------------------*/
      switch (OP)
    	{
    	  case 1: if (SekCount<=4)
    		    {
    		      Mask=0x0001FFFF>>(16-RazrCount);
    		      RLow=((~RLow) & Mask );
    		      break;
    		    }
    		  else
    		    {
    		      RLow=((~RLow) & 0X1FFFF);
    		      Mask=0x0001FFFF>>(32-RazrCount);
    		      RHi=(~RHi) & Mask;
    		      break;
    		    }

    	  case 2: if (SekCount<=4)
    		    {
    		      Mask=0x0001FFFF>>(16-RazrCount);
    		      SLow=((~SLow) & Mask );
    		      break;
    		    }
    		  else
    		    {
    		      SLow=((~SLow) & 0XFFFF);
    		      Mask=0x0001FFFF>>(32-RazrCount);
    		      SHi=(~SHi) & Mask;
    		      break;
    		    }

    	  case 3: F=R | S; break;
    	  case 4: F=R & S; break;
    	  case 5: F=(~R) & S; break;
    	  case 6: F=R ^ S; break;
    	  case 7: F=~(R ^ S);
    	}
      if (OP < 3)
    	{
    	  FLow = RLow + SLow + C0;
    	  if(SekCount>4)
    	    {
    	      C4 = (FLow>>16)&1;
    	      FHi= RHi + SHi + C4 ;   // ( (FLow & 0x0003FFFF) >> 16 );
    	      FLow &= 0xFFFF;
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

      if ( F==0 )
       Z=1;
      else
       Z=0;

      // формирование спадающих разрядов при выполнении операций сдвига
      switch (KO)
    	{
    	  case  4: case 5: PF0=F&1;
                           *_PF0 = (byte)((*_PF0 & 0xF0) & (~RECEIVE));
                           *_PF3 = (byte)(RECEIVE | (*_PF3 & 0xF0));
                           break;
    	  case  6: case 7: PF3=(F>>(RazrCount-1));
                           *_PF3 = (byte)((*_PF3 & 0xF0) & (~RECEIVE));
                           *_PF0 = (byte)(RECEIVE | (*_PF0 & 0xF0));
                           break;
                  default: if (*_PF0 & CONNECT) *_PF0 = HZ | CONNECT;
                           else *_PF0 = HZ;
                           if (*_PF3 & CONNECT) *_PF3 = HZ | CONNECT;
                           else *_PF3 = HZ;
    	}

      switch (KO)
    	{
    	  case 4: PQ0=RQ & 1;
                  *_PQ0 = (byte)((*_PQ0 & 0xF0) & (~RECEIVE));
                  *_PQ3 = (byte)(RECEIVE | (*_PQ3 & 0xF0));
                  break;
    	  case 6: PQ3=(RQ>>(RazrCount-1));
                  *_PQ3 = (byte)((*_PQ3 & 0xF0) & (~RECEIVE));
                  *_PQ0 = (byte)(RECEIVE | (*_PQ0 & 0xF0));
                  break;
         default: if (*_PQ0 & CONNECT) *_PQ0 = HZ | CONNECT;
                  else *_PQ0 = HZ;
                  if (*_PQ3 & CONNECT) *_PQ3 = HZ | CONNECT;
                  else *_PQ3 = HZ;
    	}

      if (KO==2)
       DY=RgA;
      else
       DY=F;

      PrevLevelClk = CurLevelClk;
      // формируем значения на выходах ВС1
      StoreParam();
    }

//=====================================================================
//  Процедура инициализации
//---------------------------------------------------------------------
  int TVs1::Init(string80 Array[])
    {
      SekCount = (byte) atoi (Array[0]);
      if ((SekCount < 1) && (SekCount > 8))
    	{
    	  Error = MY_ERROR;
    	  return(MY_ERROR);
    	}

      if ((Parameters = (byte *)malloc(ALL_PIN_VS1 + 8*SekCount - 8))==NULL)
    	{
    	  Error = MY_ERROR;
    	  return(MY_ERROR);
    	}

      memset((void*)Parameters,0,ALL_PIN_VS1 + 8*SekCount - 8);

      PrevLevelClk = UNDEF_LEVEL;
      CurLevelClk = UNDEF_LEVEL;

      _AA = &Parameters[0];     // 0 байт - старший разряд AA
      _KO = &Parameters[4];     // 4 байт - I6,5 байт - I8,6 байт - I7
      _PF3 = &Parameters[7];
      _PF0 = &Parameters[8];
      _Z  = &Parameters[9];
      _KI = &Parameters[10];    // 10 байт - I0,11 байт - I1,12 байт - I2
      _CLK = &Parameters[13];
      _PQ3 = &Parameters[14];
      _AB  = &Parameters[15];   // 15 байт - младший разряд AB
      _PQ0 = &Parameters[19];
      _OP  = &Parameters[20];   // 20 байт - I3,21 байт - I4,
					            // 22 байт - I5
      _C0 = &Parameters[23];
      _F3 = &Parameters[24];
      _C4 = &Parameters[25];
      _OVR = &Parameters[26];
      _OE = &Parameters[27];
      _Y = &Parameters[28];    // меньший номер вывода соотв.
					                      // младшему разряду DY
      _DA  = &Parameters[28+4*SekCount];  // шина данных разрядностью 4*SekCount
			                              // меньший номер вывода - старший разряд DA
      Reset();

      return(MY_NO_ERROR);
    }

//=====================================================================
//  Процедура инициализации выводов моделей элементов
//---------------------------------------------------------------------
  int TVs1::InitPin(void)
    {
      int Bits = SekCount<<2;
      int i;

      *_PF3 = (byte)(HZ | (*_PF3 & 0xF0));
      *_PF0 = (byte)(HZ | (*_PF0 & 0xF0));
      *_PQ3 = (byte)(HZ | (*_PQ3 & 0xF0));
      *_PQ0 = (byte)(HZ | (*_PQ0 & 0xF0));

      if (*_OE & CONNECT) *_OE = (byte)(UNDEF_LEVEL | RECEIVE | (*_OE & 0xF0));
      else *_OE = HI_LEVEL | RECEIVE;

      if (*_C0 & CONNECT) *_C0 = (byte)(UNDEF_LEVEL | RECEIVE | (*_C0 & 0xF0));
      else *_C0 = HI_LEVEL | RECEIVE;

      if (*_CLK & CONNECT) *_CLK = (byte)(UNDEF_LEVEL | RECEIVE | (*_CLK & 0xF0));
      else *_CLK = HI_LEVEL | RECEIVE;

      *_F3 = (byte)(UNDEF_LEVEL | (*_F3 & 0xF0));
      *_Z = (byte)(UNDEF_LEVEL | (*_Z & 0xF0));
      *_C4 = (byte)(UNDEF_LEVEL | (*_C4 & 0xF0));
      *_OVR = (byte)(UNDEF_LEVEL | (*_OVR & 0xF0));

      for(i=0;i<4;i++)
        {
          if (_AA[i] & CONNECT)  _AA[i] = (byte)(UNDEF_LEVEL | RECEIVE | (_AA[i] & 0xF0));
          else _AA[i] = HI_LEVEL | RECEIVE;
        }
      for(i=0;i<4;i++)
        {
          if (_AB[i] & CONNECT)  _AB[i] = (byte)(UNDEF_LEVEL | RECEIVE | (_AB[i] & 0xF0));
          else _AB[i] = HI_LEVEL | RECEIVE;
        }
      for(i=0;i<3;i++)
        {
          if (_KO[i] & CONNECT)  _KO[i] = (byte)(UNDEF_LEVEL | RECEIVE | (_KO[i] & 0xF0));
          else _KO[i] = HI_LEVEL | RECEIVE;
        }
      for(i=0;i<3;i++)
        {
          if (_KI[i] & CONNECT)  _KI[i] = (byte)(UNDEF_LEVEL | RECEIVE | (_KI[i] & 0xF0));
          else _KI[i] = HI_LEVEL | RECEIVE;
        }
      for(i=0;i<3;i++)
        {
          if (_OP[i] & CONNECT)  _OP[i] = (byte)(UNDEF_LEVEL | RECEIVE | (_OP[i] & 0xF0));
          else _OP[i] = HI_LEVEL | RECEIVE;
        }
      for(i=0;i<Bits;i++)
        {
          if (_DA[i] & CONNECT)  _DA[i] = (byte)(UNDEF_LEVEL | RECEIVE | (_DA[i] & 0xF0));
          else _DA[i] = HI_LEVEL | RECEIVE;
        }
      for(i=0;i<Bits;i++) _Y[i] = (byte)(UNDEF_LEVEL | (_Y[i] & 0xF0));

      return(MY_NO_ERROR);
    }

//=====================================================================
//  Процедура приведения моделируемого элемента в исходное состояние 
//---------------------------------------------------------------------
  void TVs1::Reset(void)
    {
      AnsiString symb = "*";
      int i;

      for(i=0;i<16;i++) RON[i] = 0;
      RgA = 0;
      RgB = 0;
      RQ = 0;
      V = 0;
      C4 = 0;
      N = 0;
      Z = 0;;
      DY = 0;
      AA = 0;
      AB = 0;
      C0 = 0;
      PF0 = 0;
      PF3 = 0;
      PQ0 = 0;
      PQ3 = 0;
	  KO = 0;   //  код приемника результата операции
      OP = 0;   //  код операции
      KI = 0;   //  код источника операнда
      DA = 0;
      PrevLevelClk = UNDEF_LEVEL;
      CurLevelClk = UNDEF_LEVEL;
      InitPin();
      Update();
    }

//=====================================================================
//  Процедура визуализации состояния выводов элемента
//---------------------------------------------------------------------
  void TVs1::Update(void)
    {
      int Bits = SekCount<<2;
      char buf[40]; // размер buf должен быть > 32
      char symb[3];
      char *ptr;
      AnsiString temp,sym = "*";
      temp = "0123456789"; // данная строка необходима для резервирования места
                           // под 10 символов

      LevelToString((char)(*_PF0 & 0x0F),symb);
      ptr = temp.c_str();
      strcpy(ptr,symb);
      Vs1Form->PF0Label->Caption = temp;
      //
      LevelToString((char)(*_PF3 & 0x0F),symb);
      strcpy(ptr,symb);
      Vs1Form->PF3Label->Caption = temp;
      //
      LevelToString((char)(*_PQ0 & 0x0F),symb);
      strcpy(ptr,symb);
      Vs1Form->PQ0Label->Caption = temp;
      //
      LevelToString((char)(*_PQ3 & 0x0F),symb);
      strcpy(ptr,symb);
      Vs1Form->PQ3Label->Caption = temp;
      //
      LevelToString((char)(*_CLK & 0x0F),symb);
      strcpy(ptr,symb);
      Vs1Form->CLKLabel->Caption = temp;
      //
      LevelToString((char)(*_C0 & 0x0F),symb);
      strcpy(ptr,symb);
      Vs1Form->C0Label->Caption = temp;
      //
      LevelToString((char)(*_OE & 0x0F),symb);
      strcpy(ptr,symb);
      Vs1Form->OELabel->Caption = temp;
      //
      LevelToString((char)(*_Z & 0x0F),symb);
      strcpy(ptr,symb);
      Vs1Form->ZLabel->Caption = temp;
      //
      LevelToString((char)(*_F3 & 0x0F),symb);
      strcpy(ptr,symb);
      Vs1Form->F3Label->Caption = temp;
      //
      LevelToString((char)(*_C4 & 0x0F),symb);
      strcpy(ptr,symb);
      Vs1Form->C4Label->Caption = temp;
      //
      LevelToString((char)(*_OVR & 0x0F),symb);
      strcpy(ptr,symb);
      Vs1Form->OVRLabel->Caption = temp;
      //
      if(CheckUndefLevel(_AA,4))
        {
          Vs1Form->AALabel->Caption = "*";
        }
      else
        {
          memcpy(buf,_AA,4);
          StrRev(buf,4);
          AA = StrToUnLong((char*)buf,0,4);
          ultoa(AA,ptr,16);
          strupr(ptr);
          Vs1Form->AALabel->Caption = temp;
        }
      //
      if(CheckUndefLevel(_AB,4))
        {
          Vs1Form->ABLabel->Caption = "*";
        }
      else
        {
          memcpy(buf,_AB,4);
          StrRev(buf,4);
          AB = StrToUnLong((char*)buf,0,4);
          ultoa(AB,ptr,16);
          strupr(ptr);
          Vs1Form->ABLabel->Caption = temp;
        }
      //
      if(CheckUndefLevel(_KO,3))
        {
          Vs1Form->KOLabel->Caption = "*";
        }
      else
        {
          memcpy(buf,_KO,3);
          StrRev(buf,3);
          KO = StrToUnLong((char*)buf,0,3);
          ultoa(KO,ptr,16);
          strupr(ptr);
          Vs1Form->KOLabel->Caption = temp;
        }
      //
      if(CheckUndefLevel(_KI,3))
        {
          Vs1Form->KILabel->Caption = "*";
        }
      else
        {
          memcpy(buf,_KI,3);
          StrRev(buf,3);
          KI = StrToUnLong((char*)buf,0,3);
          ultoa(KI,ptr,16);
          strupr(ptr);
          Vs1Form->KILabel->Caption = temp;
        }
      //
      if(CheckUndefLevel(_OP,3))
        {
          Vs1Form->OPLabel->Caption = "*";
        }
      else
        {
          memcpy(buf,_OP,3);
          StrRev(buf,3);
          OP = StrToUnLong((char*)buf,0,3);
          ultoa(OP,ptr,16);
          strupr(ptr);
          Vs1Form->OPLabel->Caption = temp;
        }

      if(CheckUndefLevel(_DA,Bits))
        {
          Vs1Form->DALabel->Caption = '*';
          for(int i=0;i<SekCount-1;i++)
            Vs1Form->DALabel->Caption = Vs1Form->DALabel->Caption + sym;
        }
      else
        {
          memcpy(buf,_DA,Bits);
          StrRev(buf,Bits);
          DA = StrToUnLong((char*)buf,0,Bits);
          ultoa(DA,ptr,16);
          CompleteString(ptr,'0',SekCount);
          strupr(ptr);
          Vs1Form->DALabel->Caption = temp;
        }
      //
      if(CheckUndefLevel(_Y,Bits))
        {
          Vs1Form->YLabel->Caption = '*';
          for(int i=0;i<SekCount-1;i++)
            Vs1Form->YLabel->Caption = Vs1Form->YLabel->Caption + sym;
        }
      else
        {
          ultoa(DY,ptr,16);
          CompleteString(ptr,'0',SekCount);
          strupr(ptr);
          Vs1Form->YLabel->Caption = temp;
        }
      //
      ultoa(RON[0],ptr,16);
      CompleteString(ptr,'0',SekCount);
      strupr(ptr);
      Vs1Form->R0Label->Caption = temp;
      //
      ultoa(RON[1],ptr,16);
      CompleteString(ptr,'0',SekCount);
      strupr(ptr);
      Vs1Form->R1Label->Caption = temp;
      //
      ultoa(RON[2],ptr,16);
      CompleteString(ptr,'0',SekCount);
      strupr(ptr);
      Vs1Form->R2Label->Caption = temp;
      //
      ultoa(RON[3],ptr,16);
      CompleteString(ptr,'0',SekCount);
      strupr(ptr);
      Vs1Form->R3Label->Caption = temp;
      //
      ultoa(RON[4],ptr,16);
      CompleteString(ptr,'0',SekCount);
      strupr(ptr);
      Vs1Form->R4Label->Caption = temp;
      //
      ultoa(RON[5],ptr,16);
      CompleteString(ptr,'0',SekCount);
      strupr(ptr);
      Vs1Form->R5Label->Caption = temp;
      //
      ultoa(RON[6],ptr,16);
      CompleteString(ptr,'0',SekCount);
      strupr(ptr);
      Vs1Form->R6Label->Caption = temp;
      //
      ultoa(RON[7],ptr,16);
      CompleteString(ptr,'0',SekCount);
      strupr(ptr);
      Vs1Form->R7Label->Caption = temp;
      //
      ultoa(RON[8],ptr,16);
      CompleteString(ptr,'0',SekCount);
      strupr(ptr);
      Vs1Form->R8Label->Caption = temp;
      //
      ultoa(RON[9],ptr,16);
      CompleteString(ptr,'0',SekCount);
      strupr(ptr);
      Vs1Form->R9Label->Caption = temp;
      //
      ultoa(RON[10],ptr,16);
      CompleteString(ptr,'0',SekCount);
      strupr(ptr);
      Vs1Form->R10Label->Caption = temp;
      //
      ultoa(RON[11],ptr,16);
      CompleteString(ptr,'0',SekCount);
      strupr(ptr);
      Vs1Form->R11Label->Caption = temp;
      //
      ultoa(RON[12],ptr,16);
      CompleteString(ptr,'0',SekCount);
      strupr(ptr);
      Vs1Form->R12Label->Caption = temp;
      //
      ultoa(RON[13],ptr,16);
      CompleteString(ptr,'0',SekCount);
      strupr(ptr);
      Vs1Form->R13Label->Caption = temp;
      //
      ultoa(RON[14],ptr,16);
      CompleteString(ptr,'0',SekCount);
      strupr(ptr);
      Vs1Form->R14Label->Caption = temp;
      //
      ultoa(RON[15],ptr,16);
      CompleteString(ptr,'0',SekCount);
      strupr(ptr);
      Vs1Form->R15Label->Caption = temp;
      //
      ultoa(RQ,ptr,16);
      CompleteString(ptr,'0',SekCount);
      strupr(ptr);
      Vs1Form->RQLabel->Caption = temp;
      //
      ultoa(RgA,ptr,16);
      CompleteString(ptr,'0',SekCount);
      strupr(ptr);
      Vs1Form->RgALabel->Caption = temp;
      //
      ultoa(RgB,ptr,16);
      CompleteString(ptr,'0',SekCount);
      strupr(ptr);
      Vs1Form->RgBLabel->Caption = temp;
    }

//=====================================================================
//  Конструктор
//---------------------------------------------------------------------
  TVs1::TVs1(int Number,TComponent *Owner) : TModelItem(Number)
    {
      AnsiString temp(Number);

      SetNumParameters(NUM_PARAM_VS1);
      Vs1Form = new TVs1Form(Owner);
      ModelForm = Vs1Form;
      Vs1Form->Caption = "БИС К1804ВС1   D" + temp;
    }

//=====================================================================
//  Деструктор
//---------------------------------------------------------------------
  TVs1::~TVs1()
    {
      if (Vs1Form != NULL)
        {
	      delete Vs1Form;
	    }
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  Конец описания прототипов методов класса TVs1
// // // // // // // // // // // // // // // // // // // // // // // //
# endif
