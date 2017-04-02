 // TVs1.hpp  -  ���������� ������ TVs1 ������������� �������� - ��� �1804��1

# ifndef __TVS1_HPP
# define __TVS1_HPP 1

# include "..\..\main\TModItem.hpp"
# include "Vs1Form.h"
# include "vcl\forms.hpp"

# define ALL_PIN_VS1      40

/*    |-----------|------------|
      |��� ������ |����� ������|
      |-----------|------------|
      |   AA      |    1-4     |
      |  KO(I6-I8)|    5-7     |
      |   PF3     |     8      |
      |   PF0     |     9      |
      |    Z      |     10     |
      |  KI(I0-I2)|   11-13    |
      |   CLK     |     14     |
      |   PQ3     |     15     |
      |   AB      |   16-19    |
      |   PQ0     |     20     |
      |  OP(I3-I5)|   21-23    |
      |   C0      |     24     |
      |   F3      |     25     |
      |   C4      |     26     |
      |   OVR     |     27     |
      |   OE      |     28     |
      | Y(n*4-0)  |     29     |  ��� n - ���������� ������
      |_DA(n*4-0)_|___29-n*4___|
*/
// � ������ ������ ���� (!) �� ������������� ������� �� ��������������
// ��������� �� ������

  class TVs1 : public TModelItem
    {
      private:
    	// ��������� �� ��������������� ������ �������
    	byte *_AA ;  //  ������� ������ A ��� ������ �� ���������
    	byte *_KO ;  //  MI(I6-I8)
    	byte *_PF3;
    	byte *_PF0;
    	byte *_Z  ;  //  ������� ���� �� ���� ������� ���
    	byte *_KI ;  //  MI(I0-I2)
    	byte *_CLK;
    	byte *_PQ3;
    	byte *_AB ;  //  ������� ������ B ��� ������ �� ���������
    	byte *_PQ0;

    	byte *_OP ;  //  MI(I3-I5)
    	byte *_C0 ;  //  ������� ������� � ���
    	byte *_F3 ;  //  ������� (��������) ������ ���
    	byte *_C4 ;  //  ����� �������� �� ���
    	byte *_OVR;  //  ������ ������������ (V)
    	byte *_OE ;  //  ������ ���������� Y-�������
    	byte *_Y ;   //  �������������� ���� Y
    	byte *_DA ;  //  ������� ���� ������
    	// ������ ���������� ���������
    	// ��� �������� ��1 ��������� �� DC-���������,
    	// ������� ����������� �� �������������� ������
    	// ��������� �������� (LOW_LEVEL -> HI_LEVEL)
    	dword RON[16];
        dword RgA,RgB,F;
    	dword RQ;

        dword CLK,OE;
    	dword V,C4,N,Z;
    	dword DY;

    	dword AA ;
    	dword AB ;
    	dword C0 ;
    	dword PF0;
    	dword PF3;
    	dword PQ0;
    	dword PQ3;
	    dword KO ;   //  ��� ��������� ���������� ��������
    	dword OP ;   //  ��� ��������
    	dword KI ;   //  ��� ��������� ��������
    	dword DA ;
    	//
    	int SekCount;
        //
    	dword PrevLevelClk;  // �������� ���������� ������ ��������
             			     // ���������

    	dword CurLevelClk;   // �������� ������� ������ ��������
    			     // ���������

        TVs1Form *Vs1Form;

      public:
        // �����������
    	TVs1(int Number,TComponent *Owner);

        // ����������
    	virtual ~TVs1();

        // ��������� �������������
        virtual int Init(string80 Array[]);
    	// ��������� ������������� ������� ������� ���������  
    	virtual int InitPin(void);
    	// ��������� ���������� ������������� �������� � �������� ���������
    	virtual void Reset(void);

    	// ������������� ������� ��� �1804��1
        // � ���������� ������� �������(������)
    	void LoadParam(void);
    	void StoreParam(void);
    	virtual void Run(void);
    	virtual void Update(void);
    };

# endif  // __TVS1_HPP
