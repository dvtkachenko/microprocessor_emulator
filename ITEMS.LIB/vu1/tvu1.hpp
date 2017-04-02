 // TVu1.hpp  -  ���������� ������ TVu1 ������������� �������� - ��� �1804��1

# ifndef __TVU1_HPP
# define __TVU1_HPP 1

# include "main\TModItem.hpp"
# include "class\TWin_d.hpp"

  class TVu1 : public TModelItem
    {
      private:
	//
	byte *_MI ;
	byte *_RE ;
	byte *_CI ;
	byte *_S0 ;
	byte *_S1 ;
	byte *_QR ;
	byte *_D  ;

	byte *_CC;
	byte *_Y;
	//
	unsigned long CT,ME,PE,VE,ZCT;
	unsigned long RA,CMK,StP,STEK[5];
	unsigned long FL;
	unsigned long Y;

	unsigned long MI ;
	unsigned long RE ;
	unsigned long CI ;
	unsigned long S0 ;
	unsigned long S1 ;
	unsigned long QR ;
	unsigned long D  ;

	unsigned CC;
	unsigned Y;

      public:
        // �����������
	TVu1(int Number);

	// ����������
	virtual ~TVu1();

        // ��������� �������������
        virtual int Init(string80 Array[]);

	// ������������� ������� ��� �1804��1
        // � ���������� ������� �������(������)
	void LoadParam();
	void StoreParam();
	virtual void Run(void);
	virtual void Show(void);
    };

# endif  // __TVU1_HPP
