 // TScheme.hpp  -  ���������� ������ - ��������� �����
 //   ������� ��������� ��� ������������:
 //     - ��� ����� �����;
 //   �������� ��������� :
 //     - ��������� �� ������� , ���������� ������� ������ TModelItem:
 //       - ������� �����������;
 //       - ������� ��������� ���������;
 //     - ��������� �� ������������������ ����.

# ifndef __TSCHEME_HPP
# define __TSCHEME_HPP 1

# include "const.hpp"
# include "TBus.hpp"
# include "TTrans.hpp"
# include "..\service\TQueue.hpp"
# include <stdio.h>

# define  ERROR_INIT_BUS  50


  // ���������� �����
  class TScheme : private TTranslator
    {
      private:

      public:
    	//
    	TQueue *ItemsQueue;    // ��������� �� ������� �������
    			       // ����������� ItemsQueue;

    	TQueue *GenerQueue;    // ��������� �� �������
    			       // ������������ ��������� GenerQueue;

    	int NumPrimaryGenerator;  // ����� ���������� , ������������
    			       // ������ �������� ����������� �������������
    			       // �����

    	byte PrimaryGenLevel;   // ����� ������� ������� ���������� ,
    			       // ������������ ������ ��������
    			       // ����������� ������������� �����

    	TBus *Bus;             // ��������� �� ������ ������ TBus ,
    			       // ������������ ���� �����.

        dword AbsoluteTime; // ���������� ����� ������������� ����� � �������

    	int Error;      // ��������� �� ������ ��� �������������
			// (����. ���� ������)
    	int ErrorCode;  // ��������� �� ��� ������, ���� ��� ����

        void Raise(void) throw(const char*);
    	// ������ ����� ������������� ����� ����������, ������������
    	// �������� ����������� ������������� �����
    	void SetPrimaryGenerator(int NumGenerator);

    	// ������� ������
    	void Create(void);
    	void Show(void);
    	void Update(void);
        void Reset(void);
        void SetWindowStateToMinimized(int NumModel);
        void SetWindowStateToNormal(int NumModel);

    	// �����������
    	TScheme(const char *FileName);

    	// ����������
    	~TScheme(void);
    };

  extern TScheme *Scheme;

# endif  // __TSCHEME_HPP
