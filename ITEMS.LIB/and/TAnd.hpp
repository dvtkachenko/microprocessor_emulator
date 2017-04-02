// TAnd.hpp  -  ���������� ������ ������������� �������� - �� "�"

# ifndef __TAND_HPP
# define __TAND_HPP 1

# include "..\..\main\TModItem.hpp"
# include "vcl\forms.hpp"
# include "AndForm.h"

# define NUM_I       4

  class TAnd : public TModelItem
    {
      private:
    	//
    	byte *I;        // ������� ������� (I0-I3)
    	byte *Y;        // �������� ������ �� "�" (Y)
    	//
    	TAndForm *AndForm;
    	//
      public:
    	// �����������
    	TAnd(int Number,TComponent *Owner);

    	// ����������
    	virtual ~TAnd();

    	// ��������� �������������
    	virtual int Init(string80 Array[]);
    	// ��������� ������������� ������� ������� ���������
    	virtual int InitPin(void);
        // ��������� ��������� � ��������� ���������
    	virtual void Reset(void);

    	// ������������� ������� �� "�"
    	// � ���������� ������� �������(������)
    	virtual void Run(void);
    	virtual void Update(void);
    };

# endif  // __TAND_HPP
