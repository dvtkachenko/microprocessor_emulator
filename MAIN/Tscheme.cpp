# include "TScheme.hpp"
# include "TBus.hpp"
# include "TTrans.hpp"
# include "ListForm.h"


//  ���������� ��������� �� ������ ������ TScheme
 TScheme *Scheme;

// // // // // // // // // // // // // // // // // // // // // // // //
//  �������� ���������� ������� ������ TScheme
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
// ���������� ���������� � ������������ � ����� ������ � ErrorCode
//---------------------------------------------------------------------
  void TScheme::Raise(void) throw(const char *)
    {
      switch (ErrorCode)
        {
          case FILE_NAME_ERROR : throw "������ � ����� �����";
          case OUT_OF_MEMORY : throw "������������ ������";
          case INVALID_END_OF_FILE : throw "�������� ���������� � ����� �����";
          case INVALID_HEADER_STRING : throw "�������� ������������ ������";
          case LOGIC_ERROR : throw "���������� ������";
          case ERROR_LOADING_DLL : throw "������ �������� DLL";
          case ERROR_READING_ITEMS_LIB :
                throw "������ ������ ����� ���������� ���������";
          case ERROR_INIT_BUS : throw "������ ��� ������������� ���� �����";

          default : throw "������ ��� �������� ������������ �����";
        }
    }

//=====================================================================
// ����� Create ������������ �������� �����.
// � ���������� ������ ����� ������ ������� ���������� ������� � ���-
// ��������������� ����.
//---------------------------------------------------------------------

  void TScheme::Create(void)
    {
      TQueue ModelItems(sizeof(ModelItemParameters));
      TQueue ModelWires(sizeof(ModelLinkParameters));
      ModelItemParameters ModelItem;
      TModelItem *Item;
      TModelItem **_Item;
      //
      Error = GetError();
      ErrorCode = GetErrorCode();
      if (Error == MY_ERROR) Raise();
      //
      Translate(GenerQueue,ItemsQueue,&ModelWires);
      Error = GetError();
      ErrorCode = GetErrorCode();
      if (Error == MY_ERROR) Raise();
      //
      GenerQueue->GoTop();
      int i=0;  // for debug
      while(GenerQueue->GetItem((void **)&_Item) != MY_ERROR)
    	{
    	  Item = *_Item;
    	  ModelItem.ModelItemNumber = Item->NumberElement;
    	  ModelItem.Parameters = Item->GetParamPtr();
    	  ModelItems.AddItem((void *)&ModelItem);
    	  if (GenerQueue->Skip() == MY_ERROR) break;
    	}

      ItemsQueue->GoTop();
      while(ItemsQueue->GetItem((void **)&_Item) != MY_ERROR)
    	{
    	  Item = *_Item;
    	  ModelItem.ModelItemNumber = Item->NumberElement;
    	  ModelItem.Parameters = Item->GetParamPtr();
    	  ModelItems.AddItem((void *)&ModelItem);
    	  if (ItemsQueue->Skip() == MY_ERROR) break;
    	}                                           //   *ModelParam[i]
      //
      Bus->Init(&ModelItems,&ModelWires);
      //
      if (Bus->Error == MY_ERROR)
    	{
    	  Error = MY_ERROR;
    	  ErrorCode = ERROR_INIT_BUS;
          throw "������ ������������� ����";
    	}
      // ���������� ������������� ������� ������� ���������
      // �� ���������� ����������� ����� ������������� ����
      // ��� ��� �� ����� ������������� ���� ������������ ����������
      // ������� ������������ ���������(����� ������������ ���������������� ����)
      // � ��� ���������� ��� � ���� ���� ��� ���
      GenerQueue->GoTop();
      while(GenerQueue->GetItem((void **)&_Item) != MY_ERROR)
    	{
    	  Item = *_Item;
          Item->InitPin();
    	  if (GenerQueue->Skip() == MY_ERROR) break;
    	}

      ItemsQueue->GoTop();
      while(ItemsQueue->GetItem((void **)&_Item) != MY_ERROR)
    	{
    	  Item = *_Item;
          Item->InitPin();
    	  if (ItemsQueue->Skip() == MY_ERROR) break;
    	}
      //
    }

//=====================================================================
//  ���������� ��������� ��������� ���� ���� Visible ����������������
//  �������� ���������� � TRUE
//---------------------------------------------------------------------
  void TScheme::Show(void)
    {
      TModelItem *Item;
      TModelItem **_Item;
      QueueItem *CurrentItem;
      // ������ ������ ���������� ��� �������������� �����
      // ��� 10 ��������
      AnsiString temp = "0123456789";


      GenerQueue->GetNumItem(&CurrentItem);
      GenerQueue->GoTop();
      while(GenerQueue->GetItem((void **)&_Item) != MY_ERROR)
    	{
    	  Item = *_Item;
    	  Item->Show();

    	  if (GenerQueue->Skip() == MY_ERROR) break;
    	}
      GenerQueue->GoTo(CurrentItem);

      ItemsQueue->GetNumItem(&CurrentItem);
      ItemsQueue->GoTop();
      while(ItemsQueue->GetItem((void **)&_Item) != MY_ERROR)
    	{
    	  Item = *_Item;
    	  Item->Show();

    	  if (ItemsQueue->Skip() == MY_ERROR) break;
    	}
      ItemsQueue->GoTo(CurrentItem);
      // ������� �������� ������� �������������  
      ultoa(AbsoluteTime,temp.c_str(),10);
      ListModelForm->AbsoluteTimeLabel->Caption = temp;
    }

//=====================================================================
//  ��������� ���������� ���� ������������ ���������
//---------------------------------------------------------------------
  void TScheme::Update(void)
    {
      TModelItem *Item;
      TModelItem **_Item;
      QueueItem *CurrentItem;
      // ������ ������ ���������� ��� �������������� �����
      // ��� 10 ��������
      AnsiString temp = "0123456789";

      GenerQueue->GetNumItem(&CurrentItem);
      GenerQueue->GoTop();
      while(GenerQueue->GetItem((void **)&_Item) != MY_ERROR)
    	{
    	  Item = *_Item;
    	  Item->Update();

    	  if (GenerQueue->Skip() == MY_ERROR) break;
    	}
      GenerQueue->GoTo(CurrentItem);
      ItemsQueue->GetNumItem(&CurrentItem);
      ItemsQueue->GoTop();
      while(ItemsQueue->GetItem((void **)&_Item) != MY_ERROR)
    	{
    	  Item = *_Item;
    	  Item->Update();

    	  if (ItemsQueue->Skip() == MY_ERROR) break;
    	}
      ItemsQueue->GoTo(CurrentItem);
      // ������� �������� ������� �������������
      ultoa(AbsoluteTime,temp.c_str(),10);
      ListModelForm->AbsoluteTimeLabel->Caption = temp;
    }

//=====================================================================
//  ������������� ������������ ����� � ��������� ���������
//---------------------------------------------------------------------
  void TScheme::Reset(void)
    {
      TModelItem *Item;
      TModelItem **_Item;
      QueueItem *CurrentItem;
      // ������ ������ ���������� ��� �������������� �����
      // ��� 10 ��������
      AnsiString temp = "0123456789";

      GenerQueue->GetNumItem(&CurrentItem);
      GenerQueue->GoTop();
      while(GenerQueue->GetItem((void **)&_Item) != MY_ERROR)
    	{
    	  Item = *_Item;
    	  Item->Reset();

    	  if (GenerQueue->Skip() == MY_ERROR) break;
    	}
      GenerQueue->GoTo(CurrentItem);
      ItemsQueue->GetNumItem(&CurrentItem);
      ItemsQueue->GoTop();
      while(ItemsQueue->GetItem((void **)&_Item) != MY_ERROR)
    	{
    	  Item = *_Item;
    	  Item->Reset();

    	  if (ItemsQueue->Skip() == MY_ERROR) break;
    	}
      ItemsQueue->GoTo(CurrentItem);
      AbsoluteTime = 0;
    }

//=====================================================================
//  ������������� WindowState ���� ������������ ���������
//---------------------------------------------------------------------
  void TScheme::SetWindowStateToMinimized(int NumModel)
    {
      TModelItem *Item;
      TModelItem **_Item;
      QueueItem *CurrentItem;

      GenerQueue->GetNumItem(&CurrentItem);
      GenerQueue->GoTop();
      while(GenerQueue->GetItem((void **)&_Item) != MY_ERROR)
    	{
    	  Item = *_Item;
          if(Item->NumberElement == NumModel)
            {
    	      Item->SetToMinimized();
            }

    	  if (GenerQueue->Skip() == MY_ERROR) break;
    	}
      GenerQueue->GoTo(CurrentItem);

      ItemsQueue->GetNumItem(&CurrentItem);
      ItemsQueue->GoTop();
      while(ItemsQueue->GetItem((void **)&_Item) != MY_ERROR)
    	{
    	  Item = *_Item;
          if(Item->NumberElement == NumModel)
            {
    	      Item->SetToMinimized();
            }

    	  if (ItemsQueue->Skip() == MY_ERROR) break;
    	}
      ItemsQueue->GoTo(CurrentItem);
    }

//=====================================================================
//  ������������� WindowState ���� ������������ ���������
//---------------------------------------------------------------------
  void TScheme::SetWindowStateToNormal(int NumModel)
    {
      TModelItem *Item;
      TModelItem **_Item;
      QueueItem *CurrentItem;

      GenerQueue->GetNumItem(&CurrentItem);
      GenerQueue->GoTop();
      while(GenerQueue->GetItem((void **)&_Item) != MY_ERROR)
    	{
    	  Item = *_Item;
          if(Item->NumberElement == NumModel)
            {
    	      Item->SetToNormal();
            }

    	  if (GenerQueue->Skip() == MY_ERROR) break;
    	}
      GenerQueue->GoTo(CurrentItem);

      ItemsQueue->GetNumItem(&CurrentItem);
      ItemsQueue->GoTop();
      while(ItemsQueue->GetItem((void **)&_Item) != MY_ERROR)
    	{
    	  Item = *_Item;
          if(Item->NumberElement == NumModel)
            {
    	      Item->SetToNormal();
            }

    	  if (ItemsQueue->Skip() == MY_ERROR) break;
    	}
      ItemsQueue->GoTo(CurrentItem);
    }

//=====================================================================
// ������������� ����� ��������� ����������
//---------------------------------------------------------------------
  void TScheme::SetPrimaryGenerator(int NumGenerator)
    {
      NumPrimaryGenerator = NumGenerator;
    }

//=====================================================================
//  �����������
//---------------------------------------------------------------------
  TScheme::TScheme(const char *FileName) : TTranslator(FileName)
    {
      // ������� �������������������� ������� ��������� � ����
      GenerQueue = new TQueue(sizeof(TModelItem *));
      ItemsQueue = new TQueue(sizeof(TModelItem *));
      Bus = new TBus;
      AbsoluteTime = 0;
      SetPrimaryGenerator(1);

      if ((GenerQueue == NULL) || (ItemsQueue == NULL) || (Bus == NULL))
    	{
    	  Error = MY_ERROR;
    	  return;
    	}
    }

//=====================================================================
//  ����������
//---------------------------------------------------------------------
  TScheme::~TScheme(void)
    {
      TModelItem *Item;
      TModelItem **_Item;

      if (GenerQueue != NULL)
    	{
    	  GenerQueue->GoTop();
    	  while(GenerQueue->GetItem((void **)&_Item) != MY_ERROR)
	         {
	           Item = *_Item;
    	       delete Item;

    	       if (GenerQueue->Skip() == MY_ERROR) break;
    	     }

    	  delete GenerQueue ;
    	  GenerQueue = NULL;
    	}

      if (ItemsQueue != NULL)
    	{
	  ItemsQueue->GoTop();
	  while(ItemsQueue->GetItem((void **)&_Item) != MY_ERROR)
	    {
	      Item = *_Item;
	      delete Item;

	      if (ItemsQueue->Skip() == MY_ERROR) break;
	    }

    	  delete ItemsQueue ;
    	  ItemsQueue = NULL;
    	}

      if (Bus != NULL)
    	{
    	  delete Bus ;
    	  Bus = NULL;
    	}
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  ����� �������� ���������� ������� ������ TScheme
// // // // // // // // // // // // // // // // // // // // // // // //


