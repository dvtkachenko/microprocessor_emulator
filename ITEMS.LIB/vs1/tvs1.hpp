 // TVs1.hpp  -  Объявление класса TVs1 моделируемого элемента - БИС К1804ВС1

# ifndef __TVS1_HPP
# define __TVS1_HPP 1

# include "..\..\main\TModItem.hpp"
# include "Vs1Form.h"
# include "vcl\forms.hpp"

# define ALL_PIN_VS1      40

/*    |-----------|------------|
      |Имя вывода |Номер вывода|
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
      | Y(n*4-0)  |     29     |  где n - количество секций
      |_DA(n*4-0)_|___29-n*4___|
*/
// в данной модели пока (!) не предусмотрена реакция на неопределенные
// состояния на входах

  class TVs1 : public TModelItem
    {
      private:
    	// указатели на соответствующие модели выводов
    	byte *_AA ;  //  сигналы адреса A для выбора из регистров
    	byte *_KO ;  //  MI(I6-I8)
    	byte *_PF3;
    	byte *_PF0;
    	byte *_Z  ;  //  признак нуля на всех выходах АЛУ
    	byte *_KI ;  //  MI(I0-I2)
    	byte *_CLK;
    	byte *_PQ3;
    	byte *_AB ;  //  сигналы адреса B для выбора из регистров
    	byte *_PQ0;

    	byte *_OP ;  //  MI(I3-I5)
    	byte *_C0 ;  //  входной перенос в АЛУ
    	byte *_F3 ;  //  старший (знаковый) разряд АЛУ
    	byte *_C4 ;  //  выход переноса из АЛУ
    	byte *_OVR;  //  сигнал переполнения (V)
    	byte *_OE ;  //  сигнал разрешения Y-выходов
    	byte *_Y ;   //  трехстабильная шина Y
    	byte *_DA ;  //  входная шина данных
    	// модели внутренних регистров
    	// все регистры ВС1 построены на DC-триггерах,
    	// которые срабатывают по положительному фронту
    	// тактового импульса (LOW_LEVEL -> HI_LEVEL)
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
	    dword KO ;   //  код приемника результата операции
    	dword OP ;   //  код операции
    	dword KI ;   //  код источника операнда
    	dword DA ;
    	//
    	int SekCount;
        //
    	dword PrevLevelClk;  // содержит предыдущие уровни тактовых
             			     // импульсов

    	dword CurLevelClk;   // содержит текущие уровни тактовых
    			     // импульсов

        TVs1Form *Vs1Form;

      public:
        // Конструктор
    	TVs1(int Number,TComponent *Owner);

        // Деструктор
    	virtual ~TVs1();

        // Процедура инициализации
        virtual int Init(string80 Array[]);
    	// Процедура инициализации выводов моделей элементов  
    	virtual int InitPin(void);
    	// Процедура приведения моделируемого элемента в исходное состояние
    	virtual void Reset(void);

    	// Моделирование функций БИС К1804ВС1
        // в дискретные моменты времени(кванты)
    	void LoadParam(void);
    	void StoreParam(void);
    	virtual void Run(void);
    	virtual void Update(void);
    };

# endif  // __TVS1_HPP
