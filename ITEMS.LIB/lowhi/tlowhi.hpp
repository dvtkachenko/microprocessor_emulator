 // TLowHi.hpp  -  ���������� ������ TConstant ������������� ��������.
 //                ������������  ������������� ������� ������� � �������� ������.

# ifndef __TCONSTANT_HPP
# define __TCONSTANT_HPP 1

# include "..\..\main\TModItem.hpp"
# include "LoHiForm.h"

  class TConstant : public TModelItem
    {
      private:
        byte *Low;      // �������� ������ ������� ������
        byte *Hi;       // �������� ������ �������� ������

      public:
        TConstForm *ConstForm;

        // �����������
    	TConstant(int Number,TComponent *Owner);
        // ����������
        ~TConstant();

        // ��������� �������������
        virtual int Init(string80 Array[]);
        // ��������� ������������� ������� ������� ���������
        virtual int InitPin(void);
        // ��������� ��������� � ��������� ���������
    	virtual void Reset(void);

        // ������������� ������� ������� � �������� ������
        // � ���������� ������� �������(������)
        virtual void Run(void);
    };

# endif  // __TCONSTANT_HPP
