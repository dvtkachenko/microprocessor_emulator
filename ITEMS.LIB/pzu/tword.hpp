 // TWord.hpp  -  Объявление класса TPzu моделируемого элемента -
 //		 микросхемы ПЗУ

# ifndef __TWORD_HPP
# define __TWORD_HPP 1

# include "..\..\main\TModItem.hpp"

  // класс реализующий одно слово памяти (8 - 128) бит
  class TWord
    {
      private:
	//
	int WordLength;

      public:
	//
	int Error;

	byte *Word;     // слово памяти

	// Конструктор
	TWord(int Length);

	// Деструктор
	~TWord();
	//
	void Clear(void); // процедура обнуляет слово памяти
	void Read(byte *ptr);      // процедура чтения из памяти
	void Write(byte *ptr);     // процедура записи в память

    } ;

 //---------------------------------------------------------------------------

# endif  // __TWORD_HPP
