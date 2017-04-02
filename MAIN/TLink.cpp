# include "TLink.hpp"
# include <alloc.h>

// // // // // // // // // // // // // // // // // // // // // // // //
//  Описание прототипов методов класса TLink
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//  Метод Transmit обеспечивает распространение сигнала
//  с входа в линию шины , и на ее выходы
//---------------------------------------------------------------------
  void TLink::Transmit(void)
    {
      int i,CountWorkingOut=0;
      byte Level = UNDEF_LEVEL,buf;


      for(i=0;i<NumWires;i++)
    	{
    	  buf = (byte)*LinkPtr[i];
    	  if ((!(buf & RECEIVE)) && ((buf & 0x0F) != HZ))
    	    {
    	      Level = (byte)(buf & 0x0F);
    	      CountWorkingOut++;
    	    }
    	}

      if (CountWorkingOut > 1) Level = UNDEF_LEVEL | CONNECT;

      for(i=0;i<NumWires;i++)
    	{
    	  if ((byte)*LinkPtr[i] & RECEIVE)
    	    (byte)*LinkPtr[i] = (byte)(Level | RECEIVE | CONNECT);
    	}

      CurrentLevel = Level;

      if (PreviousLevel != CurrentLevel)
    	{
    	  LevelChangeFlag = TRUE;
    	}
      else
    	{
    	  LevelChangeFlag = FALSE;
    	}

      PreviousLevel = CurrentLevel;
    }

//=====================================================================
//  Процедура инициализации
//---------------------------------------------------------------------
  void TLink::Init(byte **LinksPtr)
    {
      int i;

      for(i=0;i<NumWires;i++)
        {
    	  LinkPtr[i] = LinksPtr[i];
          *LinkPtr[i] = CONNECT;
        }
    }

//=====================================================================
//  Конструктор
//---------------------------------------------------------------------
  TLink::TLink(int _NumWires)
    {
      Error = MY_NO_ERROR;

//      int size = sizeof(LinkPtr); // for debug
      if((LinkPtr = (byte **)malloc(_NumWires*sizeof(LinkPtr))) == NULL)
    	Error =  MY_ERROR;

      PreviousLevel = UNDEF_LEVEL;
      NumWires = _NumWires;
    }

//=====================================================================
//  Деструктор
//---------------------------------------------------------------------
  TLink::~TLink()
    {
      free(LinkPtr);
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  Конец описания прототипов методов класса TLink
// // // // // // // // // // // // // // // // // // // // // // // //


