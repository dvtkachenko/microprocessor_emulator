 // TVu4.hpp  -  Объявление класса TVu4 моделируемого элемента - БИС К1804ВУ4

# ifndef __TVU4_HPP
# define __TVU4_HPP 1

# include "..\..\main\TModItem.hpp"
# include "Vu4Form.h"
# include "vcl\forms.hpp"

# define ADDRESS_LEN      12
# define INSTRUCTION_LEN   4
# define ALL_PIN_VU4      38

/*    |-----------|------------|
      |Имя вывода |Номер вывода|
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
// в данной модели пока (!) не предусмотрена реакция на неопределенные
// состояния на входах

  class TVu4 : public TModelItem
    {
      private:
    	// модели внутренних регистров
    	// все регистры ВУ4 построены на DC-триггерах,
    	// которые срабатывают по положительному фронту
    	// тактового импульса (LOW_LEVEL -> HI_LEVEL)
    	dword RA,CMK,StP,STEK[5];

    	// модели выводов
    	dword ME,PE,VE,RLD;
    	dword FL,CC,CCE,OE,CI;
    	dword Y ;   // код на выводах Y0-Y11
    	dword MI ;  // код на выводах I0-I3
    	dword D  ;  // код на выводах D0-D11
    	dword CLK;  // вход тактовых импульсов

    	// указатели на соответствующие модели выводов
    	byte *_ME,*_PE,*_VE,*_RLD;
    	byte *_FL,*_CC,*_CCE,*_OE,*_CI;
    	byte *_Y ;   // код на выводах Y0-Y11
    	byte *_MI ;  // код на выводах I0-I3
    	byte *_D  ;  // код на выводах D0-D11
    	byte *_CLK;  // вход тактовых импульсов

    	dword PrevLevelClk;  // содержит предыдущие уровни тактовых
			     // импульсов

    	dword CurLevelClk;   // содержит текущие уровни тактовых
    			     // импульсов

        TVu4Form *Vu4Form;

      public:
    	// Конструктор
    	TVu4(int Number,TComponent *Owner);

    	// Деструктор
    	virtual ~TVu4();

    	// Процедура инициализации
    	virtual int Init(string80 Array[]);
    	// Процедура инициализации выводов моделей элементов  
    	virtual int InitPin(void);
        // процедура установки в начальное состояние
    	virtual void Reset(void);

    	// Моделирование функций БИС К1804ВУ4
    	// в дискретные моменты времени(кванты)
    	void LoadParam(void);
    	void StoreParam(void);
    	virtual void Run(void);
    	virtual void Update(void);
    };

# endif  // __TVU4_HPP
