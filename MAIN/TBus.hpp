 // TBus.hpp - ���������� ������ TBus, ������������ ��������� ����
 //            ����� (���� � ����� ����� ���� ������ ����)

# ifndef __TBUS_HPP
# define __TBUS_HPP 1

# include "const.hpp"
# include "TLink.hpp"
# include "..\service\TQueue.hpp"

typedef struct ItemLinks
  {
    // ���-�� ������ ��������
    int TotalLinks;
    // ������ ������� ����� ����, �������������� � ��������
    int *NumLinks[];
  } ItemLinks;

// // // // // // // // // // // // // // // // // // // // // // // //

  class TBus
    {
      private:
	// ����� ����� ����
	int  TotalLinks;
	// ������ ���������� �� ����� ����
	TLink **PtrBusLinks;

      public:

	int Error;      // ��������� �� ������ ��� �������������
			// (����. ���� ������)

	int LevelChangeFlag;  // ���� ��������������� � 1, ���� ����������
			      // ���������  ���� �� ����� ��������

	void Init(TQueue *ModelItems,TQueue *ModelWires);
	TBus();
	~TBus(void);
	void Transmit(void);

    } ;

# endif  // __TBUS_HPP
