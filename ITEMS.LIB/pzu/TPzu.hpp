 // TPzu.hpp  -  ���������� ������ TPzu ������������� �������� -
 //		 ���������� ���

# ifndef __TPZU_HPP
# define __TPZU_HPP 1

# include "tword.hpp"
# include "..\..\main\TModItem.hpp"
# include "PzuForm.h"

# define VISIBLE_MEM_STRING    11
# define MAX_PIN_NUM           150    //  ����������� ��������� ����� �������

//////////////////////////////////////////////////////////////////////

  class TPzu : public TModelItem
    {
      private:
    	//
    	byte *A;         // ������� ���� ������
    	byte *Q;         // �������� ���� ������
    	byte *NonRE;     // ������ ���������� ������ (�� RE)

      public:
    	//
        TPzuForm *PzuForm;
        //
    	int WordLength;    // ����������� �������������� ����
    	int MemSize;       // ������ ������ - ����
    	int AddressSize;   // ����������� ���� ������

    	TWord **Memory;

    	// �����������
    	TPzu(int Number,TComponent *Owner);

    	// ����������
    	virtual ~TPzu();

    	// ��������� �������������
    	virtual int Init(string80 Array[]);
    	// ��������� ������������� ������� ������� ���������
    	virtual int InitPin(void);
        // ��������� ��������� � ��������� ���������
    	virtual void Reset(void);

    	// ������������� ������� ���
    	// � ���������� ������� �������(������)
    	virtual void Run(void);
    	virtual void Update(void);
    };

 //---------------------------------------------------------------------------

# endif  // __TPZU_HPP
