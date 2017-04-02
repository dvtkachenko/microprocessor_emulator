# include "TRun.hpp"
# include "TScheme.hpp"
# include <alloc.h>


TRun *RunScheme;

// // // // // // // // // // // // // // // // // // // // // // // //
//  �������� ���������� ������� ������ TKvantLevel
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//  ����� Run ���������� ������ ����� � ������� ������ ������
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
    	      // ���������� �������� ������� ������ ��������� ����������
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
                  throw "������������� ��������";
                }
            }
          //------------------------------------

    	} // end of while(Scheme->Bus->LevelChangeFlag)
      //
      Scheme->AbsoluteTime++;
    }

//=====================================================================
//  ������������� ��������� �� ������������ �����
//---------------------------------------------------------------------
  void TKvantLevel::SetScheme(TScheme *SchemePtr)
    {
      Scheme = SchemePtr ;
    }

//=====================================================================
//  �����������
//---------------------------------------------------------------------
  TKvantLevel::TKvantLevel()
    {
    }

//=====================================================================
//  ����������
//---------------------------------------------------------------------
  TKvantLevel::~TKvantLevel(void)
    {
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  ����� �������� ���������� ������� ������ TKvantLevel
// // // // // // // // // // // // // // // // // // // // // // // //


//**************************************************************************

// // // // // // // // // // // // // // // // // // // // // // // //
//  �������� ���������� ������� ������ TMikroTaktLevel
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
//  �����������
//---------------------------------------------------------------------
  TMikroTaktLevel::TMikroTaktLevel() : TKvantLevel()
    {
    }

//=====================================================================
//  ����������
//---------------------------------------------------------------------
  TMikroTaktLevel::~TMikroTaktLevel(void)
    {
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  ����� �������� ���������� ������� ������ TMikroTaktLevel
// // // // // // // // // // // // // // // // // // // // // // // //


//**************************************************************************

// // // // // // // // // // // // // // // // // // // // // // // //
//  �������� ���������� ������� ������ TTaktLevel
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
//  �����������
//---------------------------------------------------------------------
  TTaktLevel::TTaktLevel()
    {
    }

//=====================================================================
//  ����������
//---------------------------------------------------------------------
  TTaktLevel::~TTaktLevel(void)
    {
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  ����� �������� ���������� ������� ������ TTaktLevel
// // // // // // // // // // // // // // // // // // // // // // // //


//**************************************************************************

// // // // // // // // // // // // // // // // // // // // // // // //
//  �������� ���������� ������� ������ TRun
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//
//---------------------------------------------------------------------
  void __fastcall TRun::Run(void) throw(const char*)
    {
      if(Scheme == NULL) throw "TRun::Run - �� ������� ������������ �����";

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
//  ������ ��������� ������������� ������� ����������
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
//  ������ ��������� ������������� ������� ����������
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
//  ������������� ��������� �� ������������ �����
//---------------------------------------------------------------------
  void TRun::SetScheme(TScheme *SchemePtr)
    {
      TModelItem **Item;

      TKvantLevel::SetScheme(SchemePtr);

      Scheme->GenerQueue->GoTop();
      // ��������� ������� ����������� � ������������ �����
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
//  �����������
//---------------------------------------------------------------------
  TRun::TRun()
    {
      Scheme = NULL;
      TKvantLevel::TraceFlag = TRUE;
      TMikroTaktLevel::TraceFlag = FALSE;
      TTaktLevel::TraceFlag = FALSE;
    }

//=====================================================================
//  ����������
//---------------------------------------------------------------------
  TRun::~TRun(void)
    {
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  ����� �������� ���������� ������� ������ TRun
// // // // // // // // // // // // // // // // // // // // // // // //


