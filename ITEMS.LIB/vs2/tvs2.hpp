 // TVs2.hpp  -  Объявление класса TVs2 моделируемого элемента - БИС К1804ВС2

# ifndef __TVS2_HPP
# define __TVS2_HPP 1

# include "main\TModItem.hpp"
# include "class\TWin_d.hpp"

# define ALL_PIN_VS2      48

  class TVs2 : public TModelItem
    {
      private:
	//
	byte *_PQ0;
	byte *_EA;
	byte *_DA ;
	byte *_KO ;
	byte *_C0 ;
	byte *_C4 ;
	byte *_OVR;
	byte *_F3 ;
	byte *_OEY;
	byte *_DY ;
	byte *_PF0;
	byte *_PF3;
	byte *_Z  ;
	byte *_DB ;
	byte *_AA ;
	byte *_OEB;
	byte *_OP ;
	byte *_WE ;
	byte *_IEN;
	byte *_LSS;
	byte *_MSSW;
	byte *_I0 ;
	byte *_CLK;
	byte *_AB ;
	byte *_PQ3;
	//
	unsigned long RON[16];
	unsigned long RQ;
	unsigned long V,C4,N,Z;
	unsigned long DY;
	//
	unsigned long AA  ;
	unsigned long AB  ;
	unsigned long C0  ;
	unsigned long PF0 ;
	unsigned long PF3 ;
	unsigned long PQ0 ;
	unsigned long PQ3 ;
	unsigned long KO  ;
	unsigned long OP  ;
	unsigned long EA  ;
	unsigned long I0  ;
	unsigned long OEB ;
	unsigned long IEN ;
	unsigned long DA  ;
	unsigned long DB  ;
	//
	int SekCount;
	//
	void SLL(unsigned long *F,unsigned long *PF3,unsigned long *PF0,unsigned long *DY,unsigned SekCount);
	void SLA(unsigned long *F,unsigned long *PF3,unsigned long *PF0,unsigned long *DY,unsigned SekCount);
	void SRA(unsigned long *F,unsigned long *PF3,unsigned long *PF0,unsigned long *DY,unsigned SekCount);
	void SRL(unsigned long *F,unsigned long *PF3,unsigned long *PF0,unsigned long *DY,unsigned SekCount);
	void SLO(unsigned long RLow,unsigned long SLow,unsigned long *FLow,unsigned long RHi,unsigned long SHi,unsigned long *FHi,unsigned long C0,unsigned SekCount);

      public:
        // Конструктор
	TVs2(int Number);

	// Деструктор
	~TVs2();

        // Процедура инициализации
        virtual int Init(string80 Array[]);

	// Моделирование функций БИС К1804ВС2
        // в дискретные моменты времени(кванты)
	void LoadParam(void);
	void StoreParam(void);
	virtual void Run(void);
	virtual void Show(void);
    };

# endif  // __TVS2_HPP
