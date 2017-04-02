 // TQueue.hpp  -  ���������� ������ - ������� ������ ���� ������� ���
 //                �������� ������ ������������ �����

# ifndef __TQUEUE_HPP
# define __TQUEUE_HPP 1

# include "..\main\const.hpp"

// ��������� ��� �������� ������������ �������� ������
typedef struct QueueItem
  {
    void *Info;
    QueueItem *Next;
  } QueueItem;

  // ���������� �����
  class TQueue
    {
      private:
        int ElementCounter;       //  ������� ��������� ������
        int InfoSize;             //  ������ �������������� ������� � ������
        QueueItem *First;         //  ��������� �� ������ ������� ������
        QueueItem *Last;          //  ��������� �� ��������� ������� ������
        QueueItem *Current;       //  ��������� �� ������� ������� ������
        //  ����������� ������
        void DestroyQueue(void);

      public:
        // ������������
        TQueue(int StructSize);
        TQueue(void);

        // ����������
        ~TQueue(void);

        // ���������� �������� � ����� ������
        int AddItem(void *_Info);

        // ���������� � ������� ������ �� ������������� ��-���
    	int AddUniqueItem(int Offset,int Type,void *_Info);

        // �������� �������� ��������
        int DeleteItem(void);

        // ������� � ���������� �������� ������
        int Skip(void);

    	// ������� � ���������� �������� ������
    	void GoTo(QueueItem *Item);

    	// ������� � ������� �������� ������
        void GoTop(void);

        // ���������� ����� �������������� ������� �������� �������� ������
        int GetItem(void **Item);

	// ���������� ����� �������� �������� ������
	int GetNumItem(QueueItem **Item);

	// ���������� ���-�� ��������� ������
	int GetCounterItems(void);

    };

# endif  // __TQUEUE_HPP
