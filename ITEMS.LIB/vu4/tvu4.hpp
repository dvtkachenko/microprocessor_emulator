 // TVu4.hpp  -  ���������� ������ TVu4 ������������� �������� - ��� �1804��4

# ifndef __TVU4_HPP
# define __TVU4_HPP 1

# include "..\..\main\TModItem.hpp"
# include "Vu4Form.h"
# include "vcl\forms.hpp"

# define ADDRESS_LEN      12
# define INSTRUCTION_LEN   4
# define ALL_PIN_VU4      38

/*    |-----------|------------|
      |��� ������ |����� ������|
      |-----------|------------|
      |   RLD     |     1      |
      |   CC      |     2      |
      |   CCE     |     3      |
      |   PE      |     4      |
      |   ME      |     5      |
      |   VE      |     6      |
      |   FL      |     7      |
      |   OE      |     8      |
      |   CI      |     9      |
      |   CLK     |     10     |
      |   MI(0-3) |    11-14   |
      |   D(0-11) |    15-26   |
      |___Y(0-11)_|____27-38___|
*/
// � ������ ������ ���� (!) �� ������������� ������� �� ��������������
// ��������� �� ������

  class TVu4 : public TModelItem
    {
      private:
    	// ������ ���������� ���������
    	// ��� �������� ��4 ��������� �� DC-���������,
    	// ������� ����������� �� �������������� ������
    	// ��������� �������� (LOW_LEVEL -> HI_LEVEL)
    	dword RA,CMK,StP,STEK[5];

    	// ������ �������
    	dword ME,PE,VE,RLD;
    	dword FL,CC,CCE,OE,CI;
    	dword Y ;   // ��� �� ������� Y0-Y11
    	dword MI ;  // ��� �� ������� I0-I3
    	dword D  ;  // ��� �� ������� D0-D11
    	dword CLK;  // ���� �������� ���������

    	// ��������� �� ��������������� ������ �������
    	byte *_ME,*_PE,*_VE,*_RLD;
    	byte *_FL,*_CC,*_CCE,*_OE,*_CI;
    	byte *_Y ;   // ��� �� ������� Y0-Y11
    	byte *_MI ;  // ��� �� ������� I0-I3
    	byte *_D  ;  // ��� �� ������� D0-D11
    	byte *_CLK;  // ���� �������� ���������

    	dword PrevLevelClk;  // �������� ���������� ������ ��������
			     // ���������

    	dword CurLevelClk;   // �������� ������� ������ ��������
    			     // ���������

        TVu4Form *Vu4Form;

      public:
    	// �����������
    	TVu4(int Number,TComponent *Owner);

    	// ����������
    	virtual ~TVu4();

    	// ��������� �������������
    	virtual int Init(string80 Array[]);
    	// ��������� ������������� ������� ������� ���������  
    	virtual int InitPin(void);
        // ��������� ��������� � ��������� ���������
    	virtual void Reset(void);

    	// ������������� ������� ��� �1804��4
    	// � ���������� ������� �������(������)
    	void LoadParam(void);
    	void StoreParam(void);
    	virtual void Run(void);
    	virtual void Update(void);
    };

# endif  // __TVU4_HPP
