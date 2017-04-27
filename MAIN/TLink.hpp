 // TLink.hpp - ќбъ¤вление класса TLink, реализующего одну линию
 //             шины схемы (шина в схеме может быть только одна)

# ifndef __TLINK_HPP
# define __TLINK_HPP 1

# include "const.hpp"

// // // // // // // // // // // // // // // // // // // // // // // //

  class TLink
    {
      private:

	byte **LinkPtr; //  указатель на массив проводов присоединенных
                        //  к линии шины
        int NumWires;   //  кол-во проводов присоединенных к линии шины

	byte PreviousLevel;  // предыдущее состо¤ние линии
	byte CurrentLevel;   // текущее состо¤ние линии

      public:
        int Error;      // указывает на ошибку при инициализации
                        // (напр. мало пам¤ти)

	int LevelChangeFlag;  // флаг устанавливаетс¤ в 1, если предыдущее
			      // состо¤ние линии шины не равно текущему

    	TLink(int _NumWires);
        ~TLink();

        //  процедура Init выполн¤ет инициализацию линии
        void Init(byte **LinksPtr);

        //  процедура Transmit обеспечивает распространение сигнала
        //  с входа в линию шины , на ее выходы
        void Transmit(void);

    } ;

# endif  // __TLINK_HPP
