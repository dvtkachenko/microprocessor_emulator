# include "TRun.hpp"
# include "TScheme.hpp"
# include <alloc.h>


TRun *RunScheme;

// // // // // // // // // // // // // // // // // // // // // // // //
//  Описание прототипов методов класса TKvantLevel
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//  Метод Run моделирует работу схемы в течение одного кванта
//---------------------------------------------------------------------
  void __fastcall TKvantLevel::Run(void)
    {
      typedef unsigned char param[40]; //  for debug

      TModelItem *Item;
      TModelItem **_Item;
      tagMSG lpMSG;
      byte *ptr;

      Scheme->GenerQueue->GoTop();
      while(Scheme->GenerQueue->GetItem((void **)&_Item) != MY_ERROR)
    	{
    	  Item = *_Item;
    	  Item->Run();
    	  if (Item->NumberElement == Scheme->NumPrimaryGenerator)
    	    {
    	      ptr = Item->GetParamPtr();
    	      // запоминаем значение прямого выхода основного генератора
    	      Scheme->PrimaryGenLevel = ptr[0];
    	    }

    	  if (Scheme->GenerQueue->Skip() == MY_ERROR) break;
    	} // end of while(Scheme->GenerQueue->GetItem((void **)&_Item) != ERROR)
      //
      Scheme->Bus->Transmit();
      //
      while(Scheme->Bus->LevelChangeFlag)
    	{
    	  Scheme->ItemsQueue->GoTop();
    	  while(Scheme->ItemsQueue->GetItem((void **)&_Item) != MY_ERROR)
    	    {
	          Item = *_Item;
    	      Item->Run();
    	      if (Scheme->ItemsQueue->Skip() == MY_ERROR) break;
    	    }
          Scheme->Bus->Transmit();
          //---------------------------------------
          if(PeekMessage(&lpMSG,NULL,0,0,PM_REMOVE))
            {
              if(lpMSG.wParam == VK_ESCAPE)
                {
                  throw "Моделирование прервано";
                }
            }
          //------------------------------------

    	} // end of while(Scheme->Bus->LevelChangeFlag)
      //
      Scheme->AbsoluteTime++;
    }

//=====================================================================
//  Устанавливает указатель на моделируемую схему
//---------------------------------------------------------------------
  void TKvantLevel::SetScheme(TScheme *SchemePtr)
    {
      Scheme = SchemePtr ;
    }

//=====================================================================
//  Конструктор
//---------------------------------------------------------------------
  TKvantLevel::TKvantLevel()
    {
    }

//=====================================================================
//  Деструктор
//---------------------------------------------------------------------
  TKvantLevel::~TKvantLevel(void)
    {
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  Конец описания прототипов методов класса TKvantLevel
// // // // // // // // // // // // // // // // // // // // // // // //


//**************************************************************************

// // // // // // // // // // // // // // // // // // // // // // // //
//  Описание прототипов методов класса TMikroTaktLevel
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//
//---------------------------------------------------------------------
  void __fastcall TMikroTaktLevel::Run(void)
    {
	  Prev = Scheme->PrimaryGenLevel;
	  Cur  = Prev;
	  do
	    {
	      TKvantLevel::Run();
	      Cur = Scheme->PrimaryGenLevel;
	    }
	  while(Prev == Cur);
    }

//=====================================================================
//  Конструктор
//---------------------------------------------------------------------
  TMikroTaktLevel::TMikroTaktLevel() : TKvantLevel()
    {
    }

//=====================================================================
//  Деструктор
//---------------------------------------------------------------------
  TMikroTaktLevel::~TMikroTaktLevel(void)
    {
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  Конец описания прототипов методов класса TMikroTaktLevel
// // // // // // // // // // // // // // // // // // // // // // // //


//**************************************************************************

// // // // // // // // // // // // // // // // // // // // // // // //
//  Описание прототипов методов класса TTaktLevel
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//
//---------------------------------------------------------------------
  void __fastcall TTaktLevel::Run(void)
    {
	  TMikroTaktLevel::Run();
	  TMikroTaktLevel::Run();
    }

//=====================================================================
//  Конструктор
//---------------------------------------------------------------------
  TTaktLevel::TTaktLevel()
    {
    }

//=====================================================================
//  Деструктор
//---------------------------------------------------------------------
  TTaktLevel::~TTaktLevel(void)
    {
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  Конец описания прототипов методов класса TTaktLevel
// // // // // // // // // // // // // // // // // // // // // // // //


//**************************************************************************

// // // // // // // // // // // // // // // // // // // // // // // //
//  Описание прототипов методов класса TRun
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//
//---------------------------------------------------------------------
  void __fastcall TRun::Run(void) throw(const char*)
    {
      if(Scheme == NULL) throw "TRun::Run - не найдена моделируемая схема";

      if(TKvantLevel::TraceFlag)
        {
          TKvantLevel::Run();
        }

      if(TMikroTaktLevel::TraceFlag)
        {
          TMikroTaktLevel::Run();
        }

      if(TTaktLevel::TraceFlag)
        {
          TTaktLevel::Run();
        }

    }

//=====================================================================
//  Данная процедура устанавливает уровень выполнения
//---------------------------------------------------------------------
  void TRun::SetTraceLevel(int NumLevel)
    {
      TKvantLevel::TraceFlag = FALSE;
      TMikroTaktLevel::TraceFlag = FALSE;
      TTaktLevel::TraceFlag = FALSE;

      switch(NumLevel)
    	{
	  case KVANT_LEVEL :     TKvantLevel::TraceFlag = TRUE;
				 break;
	  case MIKROTAKT_LEVEL : TMikroTaktLevel::TraceFlag = TRUE;
				 break;
	  case TAKT_LEVEL :      TTaktLevel::TraceFlag = TRUE;
				 break;
    	}
    }

//=====================================================================
//  Данная процедура устанавливает уровень выполнения
//---------------------------------------------------------------------
  int TRun::GetTraceLevel(void)
    {
      int TraceLevel=0;

      if(TKvantLevel::TraceFlag) TraceLevel = KVANT_LEVEL;
      if(TMikroTaktLevel::TraceFlag) TraceLevel = MIKROTAKT_LEVEL;
      if(TTaktLevel::TraceFlag) TraceLevel = TAKT_LEVEL;

      return TraceLevel;
    }

//=====================================================================
//  Устанавливает указатель на моделируемую схему
//---------------------------------------------------------------------
  void TRun::SetScheme(TScheme *SchemePtr)
    {
      TModelItem **Item;

      TKvantLevel::SetScheme(SchemePtr);

      Scheme->GenerQueue->GoTop();
      // проверяем наличие генераторов в моделируемой схеме
      if(Scheme->GenerQueue->GetItem((void **)&Item) == MY_ERROR)
	    {
          TMikroTaktLevel::Enable = false;
          TTaktLevel::Enable = false;
          TRun::Enable = false;
        }
      else
        {
          TMikroTaktLevel::Enable = true;
          TTaktLevel::Enable = true;
          TRun::Enable = true;
        }
    }
//=====================================================================
//  Конструктор
//---------------------------------------------------------------------
  TRun::TRun()
    {
      Scheme = NULL;
      TKvantLevel::TraceFlag = TRUE;
      TMikroTaktLevel::TraceFlag = FALSE;
      TTaktLevel::TraceFlag = FALSE;
    }

//=====================================================================
//  Деструктор
//---------------------------------------------------------------------
  TRun::~TRun(void)
    {
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  Конец описания прототипов методов класса TRun
// // // // // // // // // // // // // // // // // // // // // // // //


