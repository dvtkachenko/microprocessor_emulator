# ifndef __TTRANS_CPP
# define __TTRANS_CPP 1

# include "TTrans.hpp"
# include "ListForm.h"
# include "main.h"
# include <string.h>
# include <dir.h>
# include <io.h>
# include <stdlib.h>

// // // // // // // // // // // // // // // // // // // // // // // //
//  Описание прототипов методов класса TTranslator
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//  Ищем содержится ли указываемое имя моделируемого эл-та в библиотеке
//  эл-тов.Если да , то извлекаем соответствующее имя модуля DLL,
//  моделирующего работу данного элемента.
//---------------------------------------------------------------------
  bool TTranslator::FindDLL(char *NameModel,char *FileNameDLL)
    {
      DescribeElement *Item;
      bool Find = false;

      QueueDescribe->GoTop();
      while(QueueDescribe->GetItem((void **)&Item) != MY_ERROR)
    	{
          // сравниваем извлеченное имя эл-та с NameModel
	      if(!(strcmp(Item->NameElement,NameModel)))
            {
              Find = true;
              strcpy(FileNameDLL,Item->NameDLL);
            }
    	  if (QueueDescribe->Skip() == MY_ERROR) break;
    	}

      return Find;
    }

//=====================================================================
//  Загружаем модуль DLL, моделирующий работу элемента
//
//---------------------------------------------------------------------
  bool TTranslator::LoadDLL(char *FileNameDLL,TModelItem **Model,int NumberElement)
    {
      HANDLE hLib;
      PROCPTR CreateModel;
      char PathToFile[MAXPATH];

      strcpy(PathToFile,PathToDLL);
      strcat(PathToFile,FileNameDLL);
      hLib = LoadLibrary(PathToFile);
      if (hLib == NULL)
        {
          throw "Ошибка при загрузке DLL";
        }
      CreateModel = (PROCPTR)GetProcAddress(hLib,"_CreateModel");
  	  CreateModel(Model,NumberElement,Application);
      QueueDLL->AddItem(&hLib);

      return true; 
    }

//=====================================================================
//
//
//---------------------------------------------------------------------
  void TTranslator::FreeAllDLL(void)
    {
      HANDLE *Item;

      QueueDLL->GoTop();
      while(QueueDLL->GetItem((void **)&Item) != MY_ERROR)
    	{
	      FreeLibrary(*Item);
	      if (QueueDLL->Skip() == MY_ERROR) break;
    	}
    }

//=====================================================================
//
//
//---------------------------------------------------------------------
  void TTranslator::ReadItemsLib(void)
    {
      DescribeElement Describe;
      FILE *flib;
      char FileLibName[MAXPATH];
      char BufStr[256];
      char *ptr;

      // копируем из PathToProgram путь к исполняемому файлу 
      strcpy(PathToDLL,MainForm->PathToProgram);
      strcat(PathToDLL,"\\items.dll\\"); // в PathTo,содержится полный путь к DLL
      strcpy(FileLibName,PathToDLL);
      strcat(FileLibName,"items.lib");
      flib = fopen(FileLibName,"r");
      if(flib == NULL)
        {
          Error = MY_ERROR;
          ErrorCode = ERROR_READING_ITEMS_LIB;
          return;
        }

      while(fgets(BufStr,256,flib) != NULL)
    	{
          if ((EmptyString(BufStr) == NOT_EMPTY_STRING) && (BufStr[0] != '/'))
	        {
              // извлекаем имя элемента
              ptr = strtok(BufStr,"\n- ");
              strcpy(Describe.NameElement,ptr);
              // извлекаем имя библиотеки DLL
              ptr = strtok(NULL,"\n- ");
              if(ptr == NULL)
                {
                  Error = MY_ERROR;
                  ErrorCode = ERROR_READING_ITEMS_LIB;
                  fclose(flib);
                  return;
                }
              strcpy(Describe.NameDLL,ptr);
              // заносим в очередь имя эл-та и имя файла DLL
              QueueDescribe->AddItem(&Describe);
	        }
    	}
      //
//      if(!(eof()))
//        {
//          Error = MY_ERROR;
//          ErrorCode = ERROR_READING_ITEMS_LIB;
//        }
      //
      fclose(flib);
    }

//=====================================================================
// возвращает EMPTY_STRING если строка не содержит ничего кроме пробелов
// и ENTER
//---------------------------------------------------------------------
  int TTranslator::EmptyString(char *string)
    {
      int i=0;

      while(string[i] != '\x0')
    	{
    	  if ((string[i] != 0x20) && (string[i] != 0x0A))
    	    {
    	      return(NOT_EMPTY_STRING);
    	    }
    	  i++;
    	}
      return(EMPTY_STRING);
    }

//=====================================================================
// Данный метод осуществляет чтение строки, описывающей компонент
// схемы из файла схемы.
// Возвращает тип считанной строки (LINK_STRING или ELEMENT_STRING)>
//---------------------------------------------------------------------
  void TTranslator::ReadOneSchemeComponent(void)
    {
      char Buf[BUFFER_SIZE >> 2];
      char Buf1[BUFFER_SIZE >> 2];
      char *ptr;

      while(1)
	{
	  if (fgets(Buf,BUFFER_SIZE >> 2,FileHandle) == NULL)
	    {
	      Flag = EOF;
	      return;
	    }

	  strupr(Buf);
	  if (EmptyString(Buf) == EMPTY_STRING) continue;
	  if ((Buf[0]=='/') && (Buf[1]=='/')) continue;

	  if ((ptr=strchr(Buf,'>')) != 0)
	    {
	      strcpy(Buf1,Buf);
	      ptr = Buf1;
	      if (Buf1[0] != '>')
		{
		  ptr = strtok(Buf1,">");
		  if (EmptyString(ptr) == NOT_EMPTY_STRING)
		    {
		      Error = MY_ERROR;
		      ErrorCode = INVALID_HEADER_STRING;
		      Flag = NOTUSED_PARTITION;
		      return;
		    }
		}
	      if ((strstr(Buf,"ELEMENTS\n")==0) && (strstr(Buf,"ELEMENTS ")==0))
		{
		  if ((strstr(Buf,"WIRES\n")==0) && (strstr(Buf,"WIRES ")==0))
		    {
		      Error = MY_ERROR;
		      ErrorCode = INVALID_HEADER_STRING;
		      Flag = NOTUSED_PARTITION;
		      return;
		    }
		  else
		    {
		      Flag = WIRES_PARTITION;
		      continue;
		    }
		}
	      else
		{
		  Flag = ELEMENTS_PARTITION;
		  continue;
		}
	    }
	  //
	  strcpy(BufferString,Buf);
	  while (strrchr(Buf,STRING_CONTINUE) != NULL)
	    {
	      if (fgets(Buf,BUFFER_SIZE >> 2,FileHandle) == NULL)
		{
		  Error = MY_ERROR;
		  ErrorCode = INVALID_END_OF_FILE;
		  Flag = NOTUSED_PARTITION;
		  return;
		}
	      else
		{
		  if (EmptyString(Buf) == EMPTY_STRING)
		    {
		      Buf[0] = STRING_CONTINUE;
		      continue;
		    }
		  else
		    {
		      strcat(BufferString,Buf);
		      continue;
		    }
		}
	    }
	  if (strrchr(Buf,STRING_CONTINUE) == NULL) break;
	}
    }

//=====================================================================
// Данный метод осуществляет :
//    - синтаксический разбор строки описывающей моделируемый элемент;
//    - создание в памяти модели данного элемента;
//    - добавление указателя на объект модели в соответсвующую очередь.
//---------------------------------------------------------------------
  void TTranslator::MakeOneElement(TQueue *GenerQueue,TQueue *ItemsQueue)
    {
      TModelItem *ModelPtr;
      int NumberElement;
      char NameElement[NAME_ELEMENT_LENGHT + 1];
      char NameElementForList[5 + NAME_ELEMENT_LENGHT + 1];
      char NameDLL[8+1];
      string80 Parameters[20];
      int CountParameters=0;
      char Buf[BUFFER_SIZE];
      char *ptr;
      // данная строка необходима для резервирования места
      // под 10 символов
      AnsiString temp = "01234567890123456789";
      //
      ModelPtr = NULL;
      strcpy(Buf,BufferString);
      // выделяем из строки номер элемента
      ptr = strtok(Buf,"\\\n:, ");
      // формируем имя эл-та для занесения его в список эл-тов
      strcpy(NameElementForList,ptr);
      NumberElement = atoi(ptr + 1);
      // выделяем из строки имя элемента
      ptr = strtok(NULL,"\\\n:, ");
      strcpy(NameElement,ptr);
      // добавляем пробел после "Dnn"
      strcat(NameElementForList," ");
      // формируем имя эл-та для занесения его в список эл-тов
      strcat(NameElementForList,NameElement);
      //
      while((ptr = strtok(NULL,"\\\n:, ")) != NULL)
    	{
	      strcpy(Parameters[CountParameters],ptr);
	      CountParameters++;
    	}
      //---------------------------------------------------------------
      // нижеприведенный код анализирует имя элемента и производит
      // создание соответствующего объекта класса
      //---------------------------------------------------------------

      if ((strcmp(NameElement,"GENERATOR") == 0) ||
          (strcmp(NameElement,"GOI") == 0))
    	{
          if (FindDLL(NameElement,NameDLL))
            {
              LoadDLL(NameDLL,&ModelPtr,NumberElement);
  	          GenerQueue->AddItem((void *)&ModelPtr);
              strcpy(temp.c_str(),NameElementForList);
              ListModelForm->ModelCheckListBox->Items->Add(temp);
            }
    	}
      else
    	{
          if (FindDLL(NameElement,NameDLL))
            {
              LoadDLL(NameDLL,&ModelPtr,NumberElement);
        	  // заносим указатель на объект моделируемого эл-та в очередь
        	  ItemsQueue->AddItem((void *)&ModelPtr);
              strcpy(temp.c_str(),NameElementForList);
              ListModelForm->ModelCheckListBox->Items->Add(temp);
            }
	    }

      // производим инициализацию модели элемента путем передачи массива
      // параметров
      if (ModelPtr != NULL)
    	{
    	  ModelPtr->Init(Parameters);
    	}
      else
    	{
    	  Error = MY_ERROR;
    	  ErrorCode = LOGIC_ERROR;
    	}
      //---------------------------------------------------------------
    }

//=====================================================================
// Данный метод осуществляет :
//    - синтаксический разбор строки описывающей линию шины;
//    - добавление параметров линии в очередь связей схемы WiresQueue.
//---------------------------------------------------------------------
  void TTranslator::MakeOneBusLink(TQueue *WiresQueue)
    {
      TQueue LexemQueue(32);
      ModelLinkParameters ModelLine;
      //
      char Buf[BUFFER_SIZE];
//      char BufLexem[32];
      char *Lexem,*SubLexem;
      int FirstLinkNumber;
      int LastLinkNumber;
      int FirstPinNumber;
      int LastPinNumber;

      strcpy(Buf,BufferString);
      // выделяем из строки номер линии шины
      Lexem = strtok(Buf,"\\\n:, ");
      if (strchr(Lexem,'-')==NULL)
	{
	  ModelLine.BusLineNumber = atoi(Lexem+1);
	  // выделяем из строки точки подключения
	  while((Lexem = strtok(NULL,"\\\n:, ")) != NULL)
	    {
	      LexemQueue.AddItem((void *)Lexem);
	    }
	  //
	  LexemQueue.GoTop();
	  while(LexemQueue.GetItem((void**)&Lexem)!=MY_ERROR)
	    {
	      SubLexem = strtok(Lexem,".-");
	      ModelLine.ModelItemNumber = atoi(Lexem+1);
	      SubLexem = strtok(NULL,".-");
	      FirstPinNumber = atoi(SubLexem);
	      SubLexem = strtok(NULL,".-");
	      if(SubLexem != NULL)
		{
		  LastPinNumber = atoi(SubLexem);
		}
	      else
		{
		  LastPinNumber = FirstPinNumber;
		}
	      //
	      for(int i=FirstPinNumber;i<=LastPinNumber;i++)
		{
		  ModelLine.PinNumber = i;
		  WiresQueue->AddItem((void *)&ModelLine);
		}
	      //
	      if(LexemQueue.Skip() == MY_ERROR) break;
	    }
	}
      else
	{
	  LexemQueue.AddItem((void *)Lexem);
	  Lexem = strtok(NULL,"\\\n:, ");
	  LexemQueue.AddItem((void *)Lexem);
	  //
	  LexemQueue.GoTop();
	  LexemQueue.GetItem((void **)&Lexem);
	  SubLexem = strtok(Lexem,"-");
	  FirstLinkNumber = atoi(SubLexem + 1);
	  SubLexem = strtok(NULL,"-");
	  LastLinkNumber = atoi(SubLexem);
	  //
	  LexemQueue.Skip();
	  LexemQueue.GetItem((void **)&Lexem);
	  SubLexem = strtok(Lexem,".-");
	  ModelLine.ModelItemNumber = atoi(SubLexem+1);
	  SubLexem = strtok(NULL,".-");
	  FirstPinNumber = atoi(SubLexem);
	  SubLexem = strtok(NULL,".-");
	  LastPinNumber = atoi(SubLexem);
	  if ((LastLinkNumber - FirstLinkNumber) != (LastPinNumber - FirstPinNumber))
	    {
	      Error = MY_ERROR;
	      ErrorCode = LOGIC_ERROR;
	      return;
	    }
	  //
	  for(int i=FirstPinNumber,j=FirstLinkNumber;i<=LastPinNumber;i++,j++)
	    {
	      ModelLine.PinNumber = i;
	      ModelLine.BusLineNumber = j;
	      WiresQueue->AddItem((void *)&ModelLine);
	    }
	}
      //---------------------------------------------------------------
    }

//=====================================================================
// Метод Translate осуществляет разбор файла схемы по компонентам
//---------------------------------------------------------------------
  void TTranslator::Translate(TQueue *GenerQueue,TQueue *ItemsQueue,TQueue *WiresQueue)
    {
      if(Error == MY_ERROR) return;
      ReadItemsLib();
      if(Error == MY_ERROR) return;

      do
    	{
	      ReadOneSchemeComponent();
	      switch (Flag)
	        {
	          case ELEMENTS_PARTITION:
		       MakeOneElement(GenerQueue,ItemsQueue);
		       break;
	          case WIRES_PARTITION:
		       MakeOneBusLink(WiresQueue);
		       break;
	        }
          if (Error == MY_ERROR) break;
    	}
      while(Flag != EOF);
    }

//=====================================================================
//  Конструктор
//---------------------------------------------------------------------

  TTranslator::TTranslator(const char *FileName)
    {
      Error = MY_NO_ERROR;
      ErrorCode = MY_NO_ERROR;
      Flag = NOTUSED_PARTITION;
      FileNameBuffer = (char *)malloc(strlen(FileName)+1);
      if(FileNameBuffer == NULL)
    	{
	     Error = MY_ERROR;
	     ErrorCode = OUT_OF_MEMORY;
	     return;
    	}
         strcpy(FileNameBuffer,FileName);

         BufferString = (char *)malloc(BUFFER_SIZE);
      if(BufferString == NULL)
    	{
	      Error = MY_ERROR;
	      ErrorCode = OUT_OF_MEMORY;
	      return;
    	}

      FileHandle = fopen(FileName,"rt");
      if(FileHandle == NULL)
    	{
	      Error = MY_ERROR;
	      ErrorCode = FILE_NAME_ERROR;
	      return;
    	}

      QueueDescribe = new TQueue(sizeof(DescribeElement));
      if(QueueDescribe == NULL)
    	{
	     Error = MY_ERROR;
	     ErrorCode = OUT_OF_MEMORY;
	     return;
    	}

      QueueDLL = new TQueue(sizeof(HANDLE));
      if(QueueDLL == NULL)
    	{
	     Error = MY_ERROR;
	     ErrorCode = OUT_OF_MEMORY;
	     return;
    	}
    }

//=====================================================================
//  Деструктор
//---------------------------------------------------------------------
  TTranslator::~TTranslator(void)
    {
      FreeAllDLL();
      if(FileNameBuffer != NULL) free(FileNameBuffer);
      if(BufferString != NULL) free(BufferString);
      if(FileHandle != NULL) fclose(FileHandle);
      if(QueueDescribe != NULL) delete QueueDescribe;
      if(QueueDLL != NULL) delete QueueDLL;
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  Конец описания прототипов методов класса TTranslator
// // // // // // // // // // // // // // // // // // // // // // // //

# endif  // __TTRANS_CPP
