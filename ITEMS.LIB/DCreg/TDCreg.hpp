 // TDCreg.hpp  -  Объявление класса моделируемого элемента - регистра
 //                TDCreg на DC-триггерах

# ifndef __TDCREG_HPP
# define __TDCREG_HPP 1

# include "vcl\forms.hpp"
# include "RegForm.h"
# include "..\..\main\TModItem.hpp"

  class TDCreg : public TModelItem
    {
      private:
    	//
    	byte *D;             // входные сигналы регистра (D)
    	byte *C;             // входные сигналы регистра (C)
    	byte *NonR;          // установочный вход регистра (не R)
    	byte *Q;             // выходные сигналы регистра (Q)
    	byte CountElem;      // кол-во разрядов в регистре
    	//
    	byte PrevLevelClk;   // содержит предыдущий уровень тактового
    			             // импульса

    	byte CurLevelClk;    // содержит текущий уровень тактового
    			             // импульса
      public:

        TDCregForm *DCregForm;
    	// Конструктор
    	TDCreg(int Number,TComponent *Owner);

    	// Деструктор
    	virtual ~TDCreg();

    	// Процедура инициализации
    	virtual int Init(string80 Array[]);
    	// Процедура инициализации моделей выводов элементов
    	virtual int InitPin(void);
        // процедура установки в начальное состояние
    	virtual void Reset(void);

    	// Моделирование функций регистра
    	// в дискретные моменты времени(кванты)
    	virtual void Run(void);
    	virtual void Update(void);
    };

# endif  // __TDCREG_HPP
