 // TGener.hpp  -  ���������� ������ ������������� �������� - ����������
 //                ��������������� TGenerator

# ifndef __TGENERATOR_HPP
# define __TGENERATOR_HPP 1

# include "..\..\main\TModItem.hpp"
# include "GenForm.h"
# include "vcl\forms.hpp"

// ��������� - ���������� ������� ����� ����� ����������  ( 1-0 � 0-1 )
// \______/~~~~~~
//    ��1     ��2   ��� 1
//
// /~~~~~~\______
//    ��1     ��2   ��� 2
// � ����������� �� ���������� ������ StarlLevel ������������
//   ���� ��� 1 (StarlLevel = 1) ,
//   ���� ��� 2 (StarlLevel = 0) .

  class TGenerator : public TModelItem
    {
      private:

        dword CLKLenght;       // ����������������� ��������� ��������
                               // � �������
        byte  StartLevel;      // ��������� �������� ��������� ��������
        dword MT1_Lenght;      // ����������������� ������� ����������
                               // � �������
    	dword StartDelayLenght;// ����� , � ������� �������� � ������
			       // ������ ���������� �������� StartLevel

    	byte *Clk;             // �������� ������ ������ ����������
        byte *NonClk;          // �������� ��������� ������ ����������

        dword TotalTakt;       // ������� ������
    	dword InternalCounter; // �������������� ������� �������
    	dword FullTime;        // ������ ����� ������ ����������
    	//
    	TGeneratorForm *GeneratorForm;
    	//
      public:
        // �����������
    	TGenerator(int Number,TComponent *Owner);

        // ����������
        virtual ~TGenerator();

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

# endif  // __TGENERATOR_HPP
