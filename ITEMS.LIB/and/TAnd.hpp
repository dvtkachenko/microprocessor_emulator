// TAnd.hpp  -  Объявление класса моделируемого элемента - ЛЭ "И"

# ifndef __TAND_HPP
# define __TAND_HPP 1

# include "..\..\main\TModItem.hpp"
# include "vcl\forms.hpp"
# include "AndForm.h"

# define NUM_I       4

  class TAnd : public TModelItem
    {
      private:
    	//
    	byte *I;        // входные сигналы (I0-I3)
    	byte *Y;        // выходной сигнал ЛЭ "И" (Y)
    	//
    	TAndForm *AndForm;
    	//
      public:
    	// Конструктор
    	TAnd(int Number,TComponent *Owner);

    	// Деструктор
    	virtual ~TAnd();

    	// Процедура инициализации
    	virtual int Init(string80 Array[]);
    	// Процедура инициализации моделей выводов элементов
    	virtual int InitPin(void);
        // процедура установки в начальное состояние
    	virtual void Reset(void);

    	// Моделирование функций ЛЭ "И"
    	// в дискретные моменты времени(кванты)
    	virtual void Run(void);
    	virtual void Update(void);
    };

# endif  // __TAND_HPP
