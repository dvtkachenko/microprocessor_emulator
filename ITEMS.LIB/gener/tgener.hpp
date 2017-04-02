 // TGener.hpp  -  Объявление класса моделируемого элемента - генератора
 //                синхроимпульсов TGenerator

# ifndef __TGENERATOR_HPP
# define __TGENERATOR_HPP 1

# include "..\..\main\TModItem.hpp"
# include "GenForm.h"
# include "vcl\forms.hpp"

// Микротакт - промежуток времени между двумя переходами  ( 1-0 и 0-1 )
// \______/~~~~~~
//    МТ1     МТ2   рис 1
//
// /~~~~~~\______
//    МТ1     МТ2   рис 2
// В зависимости от стартового уровня StarlLevel моделируется
//   либо рис 1 (StarlLevel = 1) ,
//   либо рис 2 (StarlLevel = 0) .

  class TGenerator : public TModelItem
    {
      private:

        dword CLKLenght;       // продолжительность тактового импульса
                               // в квантах
        byte  StartLevel;      // начальное значение тактового импульса
        dword MT1_Lenght;      // продолжительность первого микротакта
                               // в квантах
    	dword StartDelayLenght;// время , в течение которого в начале
			       // работы генератора выдается StartLevel

    	byte *Clk;             // выходной прямой сигнал генератора
        byte *NonClk;          // выходной инверсный сигнал генератора

        dword TotalTakt;       // счетчик тактов
    	dword InternalCounter; // внутритактовой счетчик квантов
    	dword FullTime;        // полное время работы генератора
    	//
    	TGeneratorForm *GeneratorForm;
    	//
      public:
        // Конструктор
    	TGenerator(int Number,TComponent *Owner);

        // Деструктор
        virtual ~TGenerator();

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

# endif  // __TGENERATOR_HPP
