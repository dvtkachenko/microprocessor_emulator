 // TTranslator.hpp  -  Объявление класса - транслятора схемы
 //   Входные параметры :
 //     - имя файла схемы
 //   Выходные параметры :
 //     - очереди указателей на объекты класса TModelItem:
 //       - очередь генераторов
 //       - очередь остальных элементов
 //     - очередь элементов типа ModelLinkParameters
 //       (отдельные связи типа "вывод элемента - линия шины")

# ifndef __TTRANS_HPP
# define __TTRANS_HPP 1

# include "const.hpp"
# include "..\service\TQueue.hpp"
# include "TModItem.hpp"
# include <stdio.h>
# include <windows.h>
# include <vcl\forms.hpp>

# define BUFFER_SIZE       4096
# define NAME_ELEMENT_LENGHT  10

# define STRING_CONTINUE   0x5C    //  '\'

# define NOTUSED_PARTITION  0
# define ELEMENTS_PARTITION 1
# define WIRES_PARTITION    2

# define EMPTY_STRING       1
# define NOT_EMPTY_STRING   0

//# define LINK_STRING        1
//# define ELEMENT_STRING     2

# define FILE_NAME_ERROR           1
# define OUT_OF_MEMORY             2
# define INVALID_END_OF_FILE       3
# define INVALID_HEADER_STRING     4
# define LOGIC_ERROR               5

# define ERROR_LOADING_DLL         6
# define ERROR_READING_ITEMS_LIB   7

  typedef BOOL (WINAPI *PROCPTR) (TModelItem**,int,TComponent *);

  typedef struct DescribeElement
    {
      char NameElement[NAME_ELEMENT_LENGHT+1];
      char NameDLL[9];
    } DescribeElement;

  // собственно класс
  class TTranslator
    {
      private:
        // очередь имен элементов и соответствующих им библиотек DLL
        TQueue *QueueDescribe;
        // очередь содержащая ID всех загруженных DLL
        TQueue *QueueDLL;

        char PathToDLL[MAX_PATH];
	    char *FileNameBuffer;
	    char *BufferString;
	    int Flag;
     	FILE *FileHandle;
    	//
    	int EmptyString(char *string); // возвращает EMPTY_STRING если строка
				       // не содержит ничего кроме пробелов
				       // и ENTER
    	//
        bool FindDLL(char *NameModel,char *FileNameDLL);
        bool LoadDLL(char *FileNameDLL,TModelItem **Model,int NumberElement);
        void FreeAllDLL(void);
        void ReadItemsLib(void); // читаем файл описания библиотеки элементов
    	void ReadOneSchemeComponent(void);
    	void MakeOneBusLink(TQueue *WiresQueue);
    	void MakeOneElement(TQueue *GenerQueue,TQueue *ItemsQueue);
    	int Error;      // указывает на ошибку при инициализации
			// (напр. мало памяти)
    	int ErrorCode;  // указывает на тип ошибки, если она была

      public:
    	//
    	int GetError() { return Error; };
    	int GetErrorCode() { return ErrorCode; };
    	// Рабочий метод
    	// Указатели на выходные очереди передаются из верхних уровней программы
    	void Translate(TQueue *GenerQueue,TQueue *ItemsQueue,TQueue *WiresQueue);

     	// Конструктор
    	TTranslator(const char *FileName);

    	// Деструктор
    	~TTranslator(void);
    };

# endif  // __TTRANS_HPP
