 // TQueue.hpp  -  ќбъ€вление класса - свзного списка типа очередь дл€
 //                хранени€ данных произвольной длины

# ifndef __TQUEUE_HPP
# define __TQUEUE_HPP 1

# include "..\main\const.hpp"

// структура дл€ описани€ абстрактного элемента списка
typedef struct QueueItem
  {
    void *Info;
    QueueItem *Next;
  } QueueItem;

  // собственно класс
  class TQueue
    {
      private:
        int ElementCounter;       //  счетчик элементов списка
        int InfoSize;             //  размер информационной области в байтах
        QueueItem *First;         //  указатель на первый элемент списка
        QueueItem *Last;          //  указатель на последний элемент списка
        QueueItem *Current;       //  указатель на текущий элемент списка
        //  уничтожение списка
        void DestroyQueue(void);

      public:
        //  онструкторы
        TQueue(int StructSize);
        TQueue(void);

        // ƒеструктор
        ~TQueue(void);

        // добавление элемента в конец списка
        int AddItem(void *_Info);

        // добавление в очередь только не повтор€ющихс€ эл-тов
    	int AddUniqueItem(int Offset,int Type,void *_Info);

        // удаление текущего элемента
        int DeleteItem(void);

        // переход к следующему элементу списка
        int Skip(void);

    	// переход к указанному элементу списка
    	void GoTo(QueueItem *Item);

    	// переход к первому элементу списка
        void GoTop(void);

        // возвращает адрес информационной области текущего элемента списка
        int GetItem(void **Item);

	// возвращает адрес текущего элемента списка
	int GetNumItem(QueueItem **Item);

	// возвращает кол-во элементов списка
	int GetCounterItems(void);

    };

# endif  // __TQUEUE_HPP
