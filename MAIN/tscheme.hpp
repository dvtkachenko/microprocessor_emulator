 // TScheme.hpp  -  Объявление класса - создателя схемы
 //   Входные параметры для конструктора:
 //     - имя файла схемы;
 //   Выходные параметры :
 //     - указатели на очереди , содержащие объекты класса TModelItem:
 //       - очередь генераторов;
 //       - очередь остальных элементов;
 //     - указатель на инициализированную шину.

# ifndef __TSCHEME_HPP
# define __TSCHEME_HPP 1

# include "const.hpp"
# include "TBus.hpp"
# include "TTrans.hpp"
# include "..\service\TQueue.hpp"
# include <stdio.h>

# define  ERROR_INIT_BUS  50


  // собственно класс
  class TScheme : private TTranslator
    {
      private:

      public:
    	//
    	TQueue *ItemsQueue;    // указатель на очередь моделей
    			       // генераторов ItemsQueue;

    	TQueue *GenerQueue;    // указатель на очередь
    			       // моделируемых элементов GenerQueue;

    	int NumPrimaryGenerator;  // номер генератора , относительно
    			       // тактов которого выполняется моделирование
    			       // схемы

    	byte PrimaryGenLevel;   // выход прямого сигнала генератора ,
    			       // относительно тактов которого
    			       // выполняется моделирование схемы

    	TBus *Bus;             // указатель на объект класса TBus ,
    			       // моделирующий шину схемы.

        dword AbsoluteTime; // абсолютное время моделирования схемы в квантах

    	int Error;      // указывает на ошибку при инициализации
			// (напр. мало памяти)
    	int ErrorCode;  // указывает на тип ошибки, если она была

        void Raise(void) throw(const char*);
    	// данный метод устанавливает номер генератора, относительно
    	// которого выполняется моделирование схемы
    	void SetPrimaryGenerator(int NumGenerator);

    	// Рабочие методы
    	void Create(void);
    	void Show(void);
    	void Update(void);
        void Reset(void);
        void SetWindowStateToMinimized(int NumModel);
        void SetWindowStateToNormal(int NumModel);

    	// Конструктор
    	TScheme(const char *FileName);

    	// Деструктор
    	~TScheme(void);
    };

  extern TScheme *Scheme;

# endif  // __TSCHEME_HPP
