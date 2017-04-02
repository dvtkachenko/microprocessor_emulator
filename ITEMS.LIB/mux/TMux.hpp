// TMux.hpp  -  ���������� ������ ������������� �������� - �������������� TMux
//              � ���������� �� ������  

# ifndef __TMUX_HPP
# define __TMUX_HPP 1

# include "..\..\main\TModItem.hpp"
# include "vcl\forms.hpp"
# include "MuxForm.h"

# define NUM_I       4
# define NUM_S       2

  class TMux : public TModelItem
    {
      private:
    	//
    	byte *I;             // ������� ������������������ ������� (I0-I3)
    	byte *S;             // ������� ������� ������ ������������������� ����� (s0-s1)
    	byte *Y;             // �������� ������ �������������� (Y)
    	//
    	TMuxForm *MuxForm;
    	//
      public:
    	// �����������
    	TMux(int Number,TComponent *Owner);

    	// ����������
    	virtual ~TMux();

    	// ��������� �������������
    	virtual int Init(string80 Array[]);
    	// ��������� ������������� ������� ������� ���������
    	virtual int InitPin(void);
        // ��������� ��������� � ��������� ���������
    	virtual void Reset(void);

    	// ������������� ������� ��������������
    	// � ���������� ������� �������(������)
    	virtual void Run(void);
    	virtual void Update(void);
    };

# endif  // __TMUX_HPP
