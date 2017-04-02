 // TGoi.hpp  -  ���������� ������ ������������� �������� - ���������� ���������
 //              ��������� TGoi

# ifndef __TGOI_HPP
# define __TGOI_HPP 1

# include "..\..\main\TModItem.hpp"
# include "GoiForm.h"
# include "vcl\forms.hpp"

// ��������� ������� - ���������� ������� ����� ����� ����������  ( 1-0 � 0-1 )
// ~~~~\______/~~~~
//       ��� 1
//
// ____/~~~~~~\___
//       ��� 2
// � ����������� �� ���������� ������ StarlLevel ������������
//   ���� ��� 1 (StarlLevel = 1) ,
//   ���� ��� 2 (StarlLevel = 0) .

  class TGoi : public TModelItem
    {
      private:

        dword CLKLenght;       // ����������������� ���������� ��������
                               // � �������
        byte  StartLevel;      // ��������� �������� �� ������ ���������� ��������
                               // � �������
    	dword StartDelayLenght;// ����� , � ������� �������� � ������
			                   // ������ ���������� �������� StartLevel

    	byte *Clk;             // �������� ������ ������ ����������

    	dword FullTime;        // ������ ����� ������ ����������
    	//
    	TGoiForm *GoiForm;
    	//
      public:
        // �����������
    	TGoi(int Number,TComponent *Owner);

        // ����������
        virtual ~TGoi();

        // ��������� �������������
        virtual int Init(string80 Array[]);
        // ��������� ������������� ������� ������� ���������
        virtual int InitPin(void);
        // ��������� ��������� � ��������� ���������
    	virtual void Reset(void);

        // ������������� ������� ����������
        // � ���������� ������� �������(������)
        virtual void Run(void);
    	//
    	virtual void Update(void);
    };

# endif  // __TGOI_HPP
