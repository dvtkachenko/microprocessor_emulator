// TMux.hpp  -  Объявление класса моделируемого элемента - мультиплексора TMux
//              с инвертором на выходе  

# ifndef __TMUX_HPP
# define __TMUX_HPP 1

# include "..\..\main\TModItem.hpp"
# include "vcl\forms.hpp"
# include "MuxForm.h"

# define NUM_I       4
# define NUM_S       2

  class TMux : public TModelItem
    {
      private:
    	//
    	byte *I;             // входные мультиплексируемые сигналы (I0-I3)
    	byte *S;             // входные сигналы адреса мультиплексируемого входа (s0-s1)
    	byte *Y;             // выходной сигнал мультиплексора (Y)
    	//
    	TMuxForm *MuxForm;
    	//
      public:
    	// Конструктор
    	TMux(int Number,TComponent *Owner);

    	// Деструктор
    	virtual ~TMux();

    	// Процедура инициализации
    	virtual int Init(string80 Array[]);
    	// Процедура инициализации выводов моделей элементов
    	virtual int InitPin(void);
        // процедура установки в начальное состояние
    	virtual void Reset(void);

    	// Моделирование функций мультиплексора
    	// в дискретные моменты времени(кванты)
    	virtual void Run(void);
    	virtual void Update(void);
    };

# endif  // __TMUX_HPP
