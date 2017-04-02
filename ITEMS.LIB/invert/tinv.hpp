 // TInv.hpp  -  ���������� ������ ������������� �������� - ���������
 //            TInvertor

# ifndef __TINVERTOR_HPP
# define __TINVERTOR_HPP 1

# include "main\TModItem.hpp"
# include "class\TWin_d.hpp"

  class TInvertor : public TModelItem
    {
      private:

	byte *Out;       // �������� ������� ����������
	byte *In;        // ������� ������� ����������
	byte CountElem;  // ���-�� ��������� � ������
	//
	TWindow *Invertor;
	//
      public:
        // �����������
	TInvertor(int Number);

        // ����������
        ~TInvertor();

        // ��������� �������������
        virtual int Init(string80 Array[]);

        // ������������� ������� ���������
        // � ���������� ������� �������(������)
        virtual void Run(void);
	virtual void Show(void);
    };

# endif  // __TINVERTOR_HPP
