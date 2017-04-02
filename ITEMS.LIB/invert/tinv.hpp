 // TInv.hpp  -  Объявление класса моделируемого элемента - инвертора
 //            TInvertor

# ifndef __TINVERTOR_HPP
# define __TINVERTOR_HPP 1

# include "main\TModItem.hpp"
# include "class\TWin_d.hpp"

  class TInvertor : public TModelItem
    {
      private:

	byte *Out;       // выходные сигналы инверторов
	byte *In;        // входные сигналы инверторов
	byte CountElem;  // кол-во элементов в пакете
	//
	TWindow *Invertor;
	//
      public:
        // Конструктор
	TInvertor(int Number);

        // Деструктор
        ~TInvertor();

        // Процедура инициализации
        virtual int Init(string80 Array[]);

        // Моделирование функций инвертора
        // в дискретные моменты времени(кванты)
        virtual void Run(void);
	virtual void Show(void);
    };

# endif  // __TINVERTOR_HPP
