 // TLowHi.hpp  -  Объявление класса TConstant моделируемого элемента.
 //                Обеспечивает  моделирование сигнала низкого и высокого уровня.

# ifndef __TCONSTANT_HPP
# define __TCONSTANT_HPP 1

# include "..\..\main\TModItem.hpp"
# include "LoHiForm.h"

  class TConstant : public TModelItem
    {
      private:
        byte *Low;      // выходной сигнал низкого уровня
        byte *Hi;       // выходной сигнал высокого уровня

      public:
        TConstForm *ConstForm;

        // Конструктор
    	TConstant(int Number,TComponent *Owner);
        // Деструктор
        ~TConstant();

        // Процедура инициализации
        virtual int Init(string80 Array[]);
        // Процедура инициализации моделей выводов элементов
        virtual int InitPin(void);
        // процедура установки в начальное состояние
    	virtual void Reset(void);

        // Моделирование сигнала низкого и высокого уровня
        // в дискретные моменты времени(кванты)
        virtual void Run(void);
    };

# endif  // __TCONSTANT_HPP
