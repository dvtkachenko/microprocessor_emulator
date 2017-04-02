# include "TQueue.hpp"
# include <alloc.h>
# include <mem.h>

// // // // // // // // // // // // // // // // // // // // // // // //
//  Описание прототипов методов класса TQueue - связного списка типа
//  очередь для  хранения данных произвольной длины
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//  Метод AddItem . Осуществляет добавление элемента в конец списка
//---------------------------------------------------------------------
  int TQueue::AddItem(void *_Info)
    {
      QueueItem *Buf;

      if (First == NULL)
        {
          First = (QueueItem *)malloc(sizeof(QueueItem));
          if (First == NULL) return(MY_ERROR);

          First->Info = (void *)malloc(InfoSize);
          if (First->Info == NULL)
            {
              free(First);
              First = NULL;
              return(MY_ERROR);
            }
	  _fmemcpy((void *)First->Info,(void *)_Info,InfoSize);
          First->Next = NULL;
          Last = First;
          Current = First;
          ElementCounter ++;
        }
      else
        {
          Buf = (QueueItem *)malloc(sizeof(QueueItem));
          if (Buf == NULL) return(MY_ERROR);

          Buf->Info = (void *)malloc(InfoSize);
          if (Buf->Info == NULL)
            {
              free(Buf);
              return(MY_ERROR);
            }
          memcpy(Buf->Info,_Info,InfoSize);
          Buf->Next = NULL;
          Last->Next = Buf;
          Last = Buf;
          ElementCounter ++;
        }
      return(MY_NO_ERROR);
    }

//=====================================================================
//  Обеспечивает добавление в очередь только не повторяющихся эл-тов
//     где Offset - смещение сравниваемого эл-та в поле Info (в байтах)
//         Type   - длина сравниваемого поля в байтах
//         _Info  - указатель на добавляемый элемент
//---------------------------------------------------------------------
  int TQueue::AddUniqueItem(int Offset,int Type,void *_Info)
    {
      QueueItem *OldCurrent = Current;
      void *Item,*__Info;

      GoTop();
      __Info = (byte *)_Info + Offset;
      while(GetItem((void **)&Item) != MY_ERROR)
        {
          Item = (byte *)Item + Offset;
	  if (!(memcmp(Item,__Info,Type)))
            {
              Current = OldCurrent;
              return(MY_ERROR);
            }
          if (Skip() == MY_ERROR) break;
        }

      Current = OldCurrent;
      return(AddItem(_Info));
    }

//=====================================================================
//  Метод DeleteItem . Осуществляет удаление текущего элемента из списка
//---------------------------------------------------------------------
  int TQueue::DeleteItem(void)
    {
      QueueItem *Buf;

      if (First == NULL) return(MY_ERROR);

      if (First == Current)
        {
          Buf = First;
          First = First->Next;
          if (First == NULL) Last = NULL;
          Current = First;
          free(Buf->Info);
          free(Buf);
          ElementCounter --;
        }
      else
        {
          Buf = First;
          while(Buf->Next != Current)
            {
              Buf = Buf->Next;
            }
          Buf->Next = Current->Next;
          free(Current->Info);
          free(Current);
          if (Buf->Next == NULL)
            {
              Current = Buf;
              Last = Buf;
            }
          else
            Current = Buf->Next;
          ElementCounter --;
        }
      return(MY_NO_ERROR);
    }

//=====================================================================
//  Метод DestroyQueue . Осуществляет уничтожение списка
//---------------------------------------------------------------------
  void TQueue::DestroyQueue(void)
    {
      if (First == NULL) return;

      Current = First;
      while(DeleteItem() != MY_ERROR);
      ElementCounter = 0;
    }

//=====================================================================
//  Метод Skip . Осуществляет переход к следующему элементу списка
//---------------------------------------------------------------------
  int TQueue::Skip(void)
    {
      if (Current->Next == NULL)
        return(MY_ERROR);
      Current = Current->Next;
      return(MY_NO_ERROR);
    }

//=====================================================================
//  Метод GoTo . Осуществляет переход к указанному элементу списка
//---------------------------------------------------------------------
  void TQueue::GoTo(QueueItem *Item)
    {
      Current = Item;
    }

//=====================================================================
//  Метод GoTop . Осуществляет переход к первому элементу списка
//---------------------------------------------------------------------
  void TQueue::GoTop(void)
    {
      Current = First;
    }

//=====================================================================
//  Метод GetItem . Возвращает адрес информационной области текущего
//                  элемента списка
//---------------------------------------------------------------------
  int TQueue::GetItem(void **Item)
    {
      if (First == NULL)
        return(MY_ERROR);

      *Item = Current->Info;
      return(MY_NO_ERROR);
    }

//=====================================================================
//  Метод GetNumItem . Возвращает адрес текущего
//                  элемента списка
//---------------------------------------------------------------------
  int TQueue::GetNumItem(QueueItem **Item)
    {
      if (First == NULL)
	return(MY_ERROR);

      *Item = Current;
      return(MY_NO_ERROR);
    }

//=====================================================================
//  Метод GetCounter . Возвращает кол-во элементов списка
//---------------------------------------------------------------------
  int TQueue::GetCounterItems(void)
    {
      return(ElementCounter);
    }

//=====================================================================
//  Конструкторы
//---------------------------------------------------------------------
  TQueue::TQueue(int StructSize)
    {
      ElementCounter = 0;
      InfoSize = StructSize;
      First = NULL;
      Last = NULL;
      Current = NULL;
    }

  TQueue::TQueue(void)
    {
      ElementCounter = 0;
      InfoSize = 2;
      First = NULL;
      Last = NULL;
      Current = NULL;
    }

//=====================================================================
//  Деструктор
//---------------------------------------------------------------------
  TQueue::~TQueue()
    {
      DestroyQueue();
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  Конец описания прототипов методов класса TQueue
// // // // // // // // // // // // // // // // // // // // // // // //

