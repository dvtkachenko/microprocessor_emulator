# include "TQueue.hpp"
# include <alloc.h>
# include <mem.h>

// // // // // // // // // // // // // // // // // // // // // // // //
//  �������� ���������� ������� ������ TQueue - �������� ������ ����
//  ������� ���  �������� ������ ������������ �����
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//  ����� AddItem . ������������ ���������� �������� � ����� ������
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
//  ������������ ���������� � ������� ������ �� ������������� ��-���
//     ��� Offset - �������� ������������� ��-�� � ���� Info (� ������)
//         Type   - ����� ������������� ���� � ������
//         _Info  - ��������� �� ����������� �������
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
//  ����� DeleteItem . ������������ �������� �������� �������� �� ������
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
//  ����� DestroyQueue . ������������ ����������� ������
//---------------------------------------------------------------------
  void TQueue::DestroyQueue(void)
    {
      if (First == NULL) return;

      Current = First;
      while(DeleteItem() != MY_ERROR);
      ElementCounter = 0;
    }

//=====================================================================
//  ����� Skip . ������������ ������� � ���������� �������� ������
//---------------------------------------------------------------------
  int TQueue::Skip(void)
    {
      if (Current->Next == NULL)
        return(MY_ERROR);
      Current = Current->Next;
      return(MY_NO_ERROR);
    }

//=====================================================================
//  ����� GoTo . ������������ ������� � ���������� �������� ������
//---------------------------------------------------------------------
  void TQueue::GoTo(QueueItem *Item)
    {
      Current = Item;
    }

//=====================================================================
//  ����� GoTop . ������������ ������� � ������� �������� ������
//---------------------------------------------------------------------
  void TQueue::GoTop(void)
    {
      Current = First;
    }

//=====================================================================
//  ����� GetItem . ���������� ����� �������������� ������� ��������
//                  �������� ������
//---------------------------------------------------------------------
  int TQueue::GetItem(void **Item)
    {
      if (First == NULL)
        return(MY_ERROR);

      *Item = Current->Info;
      return(MY_NO_ERROR);
    }

//=====================================================================
//  ����� GetNumItem . ���������� ����� ��������
//                  �������� ������
//---------------------------------------------------------------------
  int TQueue::GetNumItem(QueueItem **Item)
    {
      if (First == NULL)
	return(MY_ERROR);

      *Item = Current;
      return(MY_NO_ERROR);
    }

//=====================================================================
//  ����� GetCounter . ���������� ���-�� ��������� ������
//---------------------------------------------------------------------
  int TQueue::GetCounterItems(void)
    {
      return(ElementCounter);
    }

//=====================================================================
//  ������������
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
//  ����������
//---------------------------------------------------------------------
  TQueue::~TQueue()
    {
      DestroyQueue();
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  ����� �������� ���������� ������� ������ TQueue
// // // // // // // // // // // // // // // // // // // // // // // //

