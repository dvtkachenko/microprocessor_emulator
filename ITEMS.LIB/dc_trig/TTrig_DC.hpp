 // TTrig_DC.hpp  -  Объявление класса моделируемого элемента - регистра
 //                  TTrigger_DC на DC-триггерах

# ifndef __TTRIGGER_DC_HPP
# define __TTRIGGER_DC_HPP 1

# include "main\TModItem.hpp"

  class TTrigger_DC : public TModelItem
    {
      private:
	//
	byte *D;             // входные сигналы триггеров (D)
	byte *C;             // входные сигналы триггеров (C)
	byte *NonR;          // установочный вход триггеров (не R)
	byte *Q;             // выходные сигналы триггеров (Q)
	byte *NonQ;          // выходные сигналы триггеров (не Q)
	byte CountElem;      // кол-во элементов в пакете
	//
	byte *PrevLevelClk;  // содержит предыдущие уровни тактовых
			     // импульсов

	byte *CurLevelClk;   // содержит текущие уровни тактовых
			     // импульсов

      public:
	// Конструктор
	TTrigger_DC(int Number);

	// Деструктор
	virtual ~TTrigger_DC();

	// Процедура инициализации
	virtual int Init(string80 Array[]);

	// Моделирование функций инвертора
	// в дискретные моменты времени(кванты)
	virtual void Run(void);
	virtual void Show(void);
    };

# endif  // __TTRIGGER_DC_HPP
