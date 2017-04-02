 // TPzu.hpp  -  Объявление класса TPzu моделируемого элемента -
 //		 микросхемы ПЗУ

# ifndef __TPZU_HPP
# define __TPZU_HPP 1

# include "tword.hpp"
# include "..\..\main\TModItem.hpp"
# include "PzuForm.h"

# define VISIBLE_MEM_STRING    11
# define MAX_PIN_NUM           150    //  максимально возможное число выводов

//////////////////////////////////////////////////////////////////////

  class TPzu : public TModelItem
    {
      private:
    	//
    	byte *A;         // входная шина адреса
    	byte *Q;         // выходная шина данных
    	byte *NonRE;     // сигнал разрешения работы (не RE)

      public:
    	//
        TPzuForm *PzuForm;
        //
    	int WordLength;    // разрядность информационных слов
    	int MemSize;       // размер памяти - слов
    	int AddressSize;   // разрядность шины адреса

    	TWord **Memory;

    	// Конструктор
    	TPzu(int Number,TComponent *Owner);

    	// Деструктор
    	virtual ~TPzu();

    	// Процедура инициализации
    	virtual int Init(string80 Array[]);
    	// Процедура инициализации моделей выводов элементов
    	virtual int InitPin(void);
        // процедура установки в начальное состояние
    	virtual void Reset(void);

    	// Моделирование функций ПЗУ
    	// в дискретные моменты времени(кванты)
    	virtual void Run(void);
    	virtual void Update(void);
    };

 //---------------------------------------------------------------------------

# endif  // __TPZU_HPP
