 // TTrig_DC.hpp  -  ���������� ������ ������������� �������� - ��������
 //                  TTrigger_DC �� DC-���������

# ifndef __TTRIGGER_DC_HPP
# define __TTRIGGER_DC_HPP 1

# include "main\TModItem.hpp"

  class TTrigger_DC : public TModelItem
    {
      private:
	//
	byte *D;             // ������� ������� ��������� (D)
	byte *C;             // ������� ������� ��������� (C)
	byte *NonR;          // ������������ ���� ��������� (�� R)
	byte *Q;             // �������� ������� ��������� (Q)
	byte *NonQ;          // �������� ������� ��������� (�� Q)
	byte CountElem;      // ���-�� ��������� � ������
	//
	byte *PrevLevelClk;  // �������� ���������� ������ ��������
			     // ���������

	byte *CurLevelClk;   // �������� ������� ������ ��������
			     // ���������

      public:
	// �����������
	TTrigger_DC(int Number);

	// ����������
	virtual ~TTrigger_DC();

	// ��������� �������������
	virtual int Init(string80 Array[]);

	// ������������� ������� ���������
	// � ���������� ������� �������(������)
	virtual void Run(void);
	virtual void Show(void);
    };

# endif  // __TTRIGGER_DC_HPP
