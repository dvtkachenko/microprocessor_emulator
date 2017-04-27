// TAndNo.hpp  -  Объявление класса моделируемого элемента - ЛЭ "И-НЕ"

# ifndef __TAND_HPP
# define __TAND_HPP 1

# include "..\..\main\TModItem.hpp"
# include "vcl\forms.hpp"
# include "AndForm.h"

# define NUM_I       4

  class TAndNo : public TModelItem
    {
      private:
    	//
    	byte *I;        // входные сигналы (I0-I3)
    	byte *NonY;        // выходной сигнал ЛЭ "И-НЕ" (Y)
    	//
    	TAndNoForm *AndNoForm;
    	//
      public:
    	// Конструктор
    	TAndNo(int Number,TComponent *Owner);

    	// Деструктор
    	virtual ~TAndNo();

    	// Процедура инициализации
    	virtual int Init(string80 Array[]);
    	// Процедура инициализации моделей выводов элементов
    	virtual int InitPin(void);
        // процедура установки в начальное состояние
    	virtual void Reset(void);

    	// Моделирование функций ЛЭ "И-НЕ"
    	// в дискретные моменты времени(кванты)
    	virtual void Run(void);
    	virtual void Update(void);
    };

# endif  // __TAND_HPP
