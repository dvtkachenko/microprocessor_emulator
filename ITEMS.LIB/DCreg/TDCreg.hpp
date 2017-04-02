 // TDCreg.hpp  -  ���������� ������ ������������� �������� - ��������
 //                TDCreg �� DC-���������

# ifndef __TDCREG_HPP
# define __TDCREG_HPP 1

# include "vcl\forms.hpp"
# include "RegForm.h"
# include "..\..\main\TModItem.hpp"

  class TDCreg : public TModelItem
    {
      private:
    	//
    	byte *D;             // ������� ������� �������� (D)
    	byte *C;             // ������� ������� �������� (C)
    	byte *NonR;          // ������������ ���� �������� (�� R)
    	byte *Q;             // �������� ������� �������� (Q)
    	byte CountElem;      // ���-�� �������� � ��������
    	//
    	byte PrevLevelClk;   // �������� ���������� ������� ���������
    			             // ��������

    	byte CurLevelClk;    // �������� ������� ������� ���������
    			             // ��������
      public:

        TDCregForm *DCregForm;
    	// �����������
    	TDCreg(int Number,TComponent *Owner);

    	// ����������
    	virtual ~TDCreg();

    	// ��������� �������������
    	virtual int Init(string80 Array[]);
    	// ��������� ������������� ������� ������� ���������
    	virtual int InitPin(void);
        // ��������� ��������� � ��������� ���������
    	virtual void Reset(void);

    	// ������������� ������� ��������
    	// � ���������� ������� �������(������)
    	virtual void Run(void);
    	virtual void Update(void);
    };

# endif  // __TDCREG_HPP
