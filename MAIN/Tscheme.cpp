# include "TScheme.hpp"
# include "TBus.hpp"
# include "TTrans.hpp"
# include "ListForm.h"


//  объявление указателя на объект класса TScheme
 TScheme *Scheme;

// // // // // // // // // // // // // // // // // // // // // // // //
//  Описание прототипов методов класса TScheme
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
// Генерирует исключение в соответствии с кодом ошибки в ErrorCode
//---------------------------------------------------------------------
  void TScheme::Raise(void) throw(const char *)
    {
      switch (ErrorCode)
        {
          case FILE_NAME_ERROR : throw "Ошибка в имени файла";
          case OUT_OF_MEMORY : throw "Недостаточно памяти";
          case INVALID_END_OF_FILE : throw "Неверное завершение в файле схемы";
          case INVALID_HEADER_STRING : throw "Неверная заголовочная строка";
          case LOGIC_ERROR : throw "Логическая ошибка";
          case ERROR_LOADING_DLL : throw "Ошибка загрузки DLL";
          case ERROR_READING_ITEMS_LIB :
                throw "Ошибка чтения файла библиотеки элементов";
          case ERROR_INIT_BUS : throw "Ошибка при инициализации шины схемы";

          default : throw "Ошибка при создании моделируемой схемы";
        }
    }

//=====================================================================
// Метод Create осуществляет создание схемы.
// В результате работы этого метода получим заполненые очереди и ини-
// циализированную шину.
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
          throw "Ошибка инициализации шины";
    	}
      // производим инициализацию моделей выводов элементов
      // ее необходимо производить после инициализации шины
      // так как во время инициализации шины производится оповещение
      // выводов моделируемых элементов(путем установления соответствующего бита)
      // о том подключены они к чему либо или нет
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
//  Показывает состояние элементов если флаг Visible соответствующего
//  элемента установлен в TRUE
//---------------------------------------------------------------------
  void TScheme::Show(void)
    {
      TModelItem *Item;
      TModelItem **_Item;
      QueueItem *CurrentItem;
      // данная строка необходима для резервирования места
      // под 10 символов
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
      // выводим значение времени моделирования  
      ultoa(AbsoluteTime,temp.c_str(),10);
      ListModelForm->AbsoluteTimeLabel->Caption = temp;
    }

//=====================================================================
//  Обновляет содержимое форм моделируемых элементов
//---------------------------------------------------------------------
  void TScheme::Update(void)
    {
      TModelItem *Item;
      TModelItem **_Item;
      QueueItem *CurrentItem;
      // данная строка необходима для резервирования места
      // под 10 символов
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
      // выводим значение времени моделирования
      ultoa(AbsoluteTime,temp.c_str(),10);
      ListModelForm->AbsoluteTimeLabel->Caption = temp;
    }

//=====================================================================
//  устанавливает моделируемую схему в начальное состояние
//---------------------------------------------------------------------
  void TScheme::Reset(void)
    {
      TModelItem *Item;
      TModelItem **_Item;
      QueueItem *CurrentItem;
      // данная строка необходима для резервирования места
      // под 10 символов
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
//  Устанавливает WindowState форм моделируемых элементов
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
//  Устанавливает WindowState форм моделируемых элементов
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
// Устанавливает номер основного генератора
//---------------------------------------------------------------------
  void TScheme::SetPrimaryGenerator(int NumGenerator)
    {
      NumPrimaryGenerator = NumGenerator;
    }

//=====================================================================
//  Конструктор
//---------------------------------------------------------------------
  TScheme::TScheme(const char *FileName) : TTranslator(FileName)
    {
      // Создаем неинициализированные очереди элементов и шину
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
//  Деструктор
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
//  Конец описания прототипов методов класса TScheme
// // // // // // // // // // // // // // // // // // // // // // // //


