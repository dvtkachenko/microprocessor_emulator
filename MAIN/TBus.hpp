 // TBus.hpp - ќбъ¤вление класса TBus, реализующего системную шину
 //            схемы (шина в схеме может быть только одна)

# ifndef __TBUS_HPP
# define __TBUS_HPP 1

# include "const.hpp"
# include "TLink.hpp"
# include "..\service\TQueue.hpp"

typedef struct ItemLinks
  {
    // кол-во св¤зей элемента
    int TotalLinks;
    // массив номеров линий шины, присоединенных к элементу
    int *NumLinks[];
  } ItemLinks;

// // // // // // // // // // // // // // // // // // // // // // // //

  class TBus
    {
      private:
	// число линий шины
	int  TotalLinks;
	// массив указателей на линии шины
	TLink **PtrBusLinks;

      public:

	int Error;      // указывает на ошибку при инициализации
			// (напр. мало пам¤ти)

	int LevelChangeFlag;  // флаг устанавливаетс¤ в 1, если предыдущее
			      // состо¤ние  шины не равно текущему

	void Init(TQueue *ModelItems,TQueue *ModelWires);
	TBus();
	~TBus(void);
	void Transmit(void);

    } ;

# endif  // __TBUS_HPP
