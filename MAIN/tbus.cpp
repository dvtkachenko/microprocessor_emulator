# include "TBus.hpp"
# include <alloc.h>


// // // // // // // // // // // // // // // // // // // // // // // //
//  Описание прототипов методов класса TBus
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//  Метод Transmit обеспечивает распространение сигнала
//  с входа в линию шины, на ее выходы после работы заданного элемента
//  и формирует флаг LevelChangeFlag, который указывает на
//  изменение состояния шины с момента последней итерации
//---------------------------------------------------------------------
  void TBus::Transmit(void)
    {
      LevelChangeFlag = FALSE;
      for (int i=0;i<TotalLinks;i++)
    	{
    	  PtrBusLinks[i]->Transmit();
    	  LevelChangeFlag |= PtrBusLinks[i]->LevelChangeFlag;
    	}
    }

//=====================================================================
//  Конструктор
//---------------------------------------------------------------------
  TBus::TBus()
    {
      PtrBusLinks = NULL;
    }

//=====================================================================
//  Метод Init.
//  ModelItems - указатель на очередь всех моделируемых элементов
//  схемы.
//  ModelWires - указатель на очередь всех связей моделируемого
//  элемента типа вывод-линия шины.
//  Данные параметры формируются транслятором схемы.
//---------------------------------------------------------------------
  void TBus::Init(TQueue *ModelItems,TQueue *ModelWires)
    {
      ModelItemParameters *Item;
      ModelLinkParameters *Link;
      int *LinkNumber;
      TQueue BusLineNumbers(4);
      byte *LinksPtr[1000];
      int NumWires;
      int i;

      // --------------
      // Создание и инициализация моделей линий шины
      // Исходными данными для построения шины являются
      // списки ModelItems и ModelWires.
      // Выходными данными являются :
      // массив указателей на объекты класса TLink,
      // число линий в шине TotalLinks
      // --------------

      // создание списка уникальных номеров линий шины
      ModelWires->GoTop();
      while(ModelWires->GetItem((void **)&Link) != MY_ERROR)
    	{
    	  BusLineNumbers.AddUniqueItem(0,4,(void *)&Link->BusLineNumber);
    	  if (ModelWires->Skip() == MY_ERROR) break;
    	}

      // подсчет кол-ва линий шины
      TotalLinks = BusLineNumbers.GetCounterItems();

      // выделение памяти под массив указателей на объекты класса TLink
      PtrBusLinks = (TLink **)malloc(TotalLinks*(sizeof(TLink *)));
      if (PtrBusLinks == NULL)
    	{
          Error = MY_ERROR;
    	  return;
    	}

      // непосредственное создание и инициализация моделей линий шины
      BusLineNumbers.GoTop();
      for(i=0;i<TotalLinks;i++)
    	{
    	  BusLineNumbers.GetItem((void **)&LinkNumber);
    	  BusLineNumbers.Skip();
    	  //
    	  NumWires = 0;
    	  ModelWires->GoTop();
    	  while(ModelWires->GetItem((void **)&Link) != MY_ERROR)
    	    {
    	      if (Link->BusLineNumber == *LinkNumber)
    	 	{
		  ModelItems->GoTop();
		  while(ModelItems->GetItem((void **)&Item) != MY_ERROR)
		    {
		      if (Item->ModelItemNumber == Link->ModelItemNumber)
	    		{
    			  LinksPtr[NumWires] = Item->Parameters + Link->PinNumber - 1;
    	 		  NumWires++;
    			  break;
	    		}
		      if (ModelItems->Skip() == MY_ERROR) break;
		    }
		}
	      if (ModelWires->Skip() == MY_ERROR) break;
	    }

	  PtrBusLinks[i] = new TLink(NumWires);
	  if (PtrBusLinks[i] == NULL)
	    {
	      for(int j=0;j<i;j++)
		{
		  delete PtrBusLinks[j];
		}
	      free (PtrBusLinks);
	      Error = MY_ERROR;
	      return;
	    }

	  PtrBusLinks[i]->Init((byte **)&LinksPtr);
    	}
      // --------------
      i=1;
      return;
    }

//=====================================================================
//  Деструктор
//---------------------------------------------------------------------
  TBus::~TBus(void)
    {
      for(int j=0;j<TotalLinks;j++)
	{
	  delete PtrBusLinks[j];
	}
      free (PtrBusLinks);
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  Конец описания прототипов методов класса TBus
// // // // // // // // // // // // // // // // // // // // // // // //

