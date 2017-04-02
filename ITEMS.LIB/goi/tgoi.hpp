 // TGoi.hpp  -  Объявление класса моделируемого элемента - генератора одиночных
 //              импульсов TGoi

# ifndef __TGOI_HPP
# define __TGOI_HPP 1

# include "..\..\main\TModItem.hpp"
# include "GoiForm.h"
# include "vcl\forms.hpp"

// Одиночный импульс - промежуток времени между двумя переходами  ( 1-0 и 0-1 )
// ~~~~\______/~~~~
//       рис 1
//
// ____/~~~~~~\___
//       рис 2
// В зависимости от стартового уровня StarlLevel моделируется
//   либо рис 1 (StarlLevel = 1) ,
//   либо рис 2 (StarlLevel = 0) .

  class TGoi : public TModelItem
    {
      private:

        dword CLKLenght;       // продолжительность одиночного импульса
                               // в квантах
        byte  StartLevel;      // начальное значение до выдачи одиночного импульса
                               // в квантах
    	dword StartDelayLenght;// время , в течение которого в начале
			                   // работы генератора выдается StartLevel

    	byte *Clk;             // выходной прямой сигнал генератора

    	dword FullTime;        // полное время работы генератора
    	//
    	TGoiForm *GoiForm;
    	//
      public:
        // Конструктор
    	TGoi(int Number,TComponent *Owner);

        // Деструктор
        virtual ~TGoi();

        // Процедура инициализации
        virtual int Init(string80 Array[]);
        // Процедура инициализации моделей выводов элементов
        virtual int InitPin(void);
        // процедура установки в начальное состояние
    	virtual void Reset(void);

        // Моделирование функций генератора
        // в дискретные моменты времени(кванты)
        virtual void Run(void);
    	//
    	virtual void Update(void);
    };

# endif  // __TGOI_HPP
