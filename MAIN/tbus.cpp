# include "TBus.hpp"
# include <alloc.h>


// // // // // // // // // // // // // // // // // // // // // // // //
//  �������� ���������� ������� ������ TBus
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//  ����� Transmit ������������ ��������������� �������
//  � ����� � ����� ����, �� �� ������ ����� ������ ��������� ��������
//  � ��������� ���� LevelChangeFlag, ������� ��������� ��
//  ��������� ��������� ���� � ������� ��������� ��������
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
//  �����������
//---------------------------------------------------------------------
  TBus::TBus()
    {
      PtrBusLinks = NULL;
    }

//=====================================================================
//  ����� Init.
//  ModelItems - ��������� �� ������� ���� ������������ ���������
//  �����.
//  ModelWires - ��������� �� ������� ���� ������ �������������
//  �������� ���� �����-����� ����.
//  ������ ��������� ����������� ������������ �����.
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
      // �������� � ������������� ������� ����� ����
      // ��������� ������� ��� ���������� ���� ��������
      // ������ ModelItems � ModelWires.
      // ��������� ������� �������� :
      // ������ ���������� �� ������� ������ TLink,
      // ����� ����� � ���� TotalLinks
      // --------------

      // �������� ������ ���������� ������� ����� ����
      ModelWires->GoTop();
      while(ModelWires->GetItem((void **)&Link) != MY_ERROR)
    	{
    	  BusLineNumbers.AddUniqueItem(0,4,(void *)&Link->BusLineNumber);
    	  if (ModelWires->Skip() == MY_ERROR) break;
    	}

      // ������� ���-�� ����� ����
      TotalLinks = BusLineNumbers.GetCounterItems();

      // ��������� ������ ��� ������ ���������� �� ������� ������ TLink
      PtrBusLinks = (TLink **)malloc(TotalLinks*(sizeof(TLink *)));
      if (PtrBusLinks == NULL)
    	{
          Error = MY_ERROR;
    	  return;
    	}

      // ���������������� �������� � ������������� ������� ����� ����
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
//  ����������
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
//  ����� �������� ���������� ������� ������ TBus
// // // // // // // // // // // // // // // // // // // // // // // //

