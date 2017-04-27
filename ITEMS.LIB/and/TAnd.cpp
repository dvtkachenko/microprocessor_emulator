# include "TAnd.hpp"
# include <vcl\dstring.h>
# include "..\..\service\service.h"
# include <stdlib.h>
# include <alloc.h>

// Нумерация выводов ЛЭ "И" следующая:
//   - сначала нумеруются все I - входы;    I0,I1,I2,I3 (1 ... 4)
//   - далее Y - выход ;                    Y    (5)
// Такая нумерация необходима для линейной адресации всех выводов ЛЭ "И"

// // // // // // // // // // // // // // // // // // // // // // // //
//  Описание прототипов методов класса TAnd - ЛЭ "И"
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//  Метод Run . Осуществляет моделирование функций ЛЭ "И" 
//              в дискретные моменты времени(кванты)
//---------------------------------------------------------------------
  void TAnd::Run(void)
    {
      byte buf;
      bool LowFlag = false;

      // смотрим имеется ли хотя бы на одном входе низкий уровень
      for(int i=0;i<NUM_I;i++)
        {
          if((I[i] & 0x0F) == LOW_LEVEL)
            {
              LowFlag = true;
              break;
            }
        }

      if(!LowFlag)
        {
          buf = HI_LEVEL;
          for(int i=0;i<NUM_I;i++)
            {
              if((I[i] & 0x0F) == UNDEF_LEVEL)
                {
                  buf = UNDEF_LEVEL;
                  break;
                }
            }
        }
      else
        {
          buf = LOW_LEVEL;
        }

      *Y = (byte)((*Y & 0xF0) | buf);
    }

//=====================================================================
//  Процедура инициализации
//---------------------------------------------------------------------
  int TAnd::Init(string80 Array[])
    {
      if ((Parameters = (byte *)malloc(NUM_I + 1))==NULL)
    	{
    	  Error = MY_ERROR;
    	  return(MY_ERROR);
    	}

      memset((void*)Parameters,0,NUM_I + 1);

      I = &Parameters[0];
      Y = &Parameters[NUM_I];

      return(MY_NO_ERROR);
    }

//=====================================================================
//  Процедура инициализации моделей выводов элементов
//---------------------------------------------------------------------
  int TAnd::InitPin(void)
    {
      int i;

      for(i=0;i<NUM_I;i++)
        {
         // если вход находится в подвешенном состоянии,
         // то устанавливаем на нем HI_LEVEL
         if (I[i] & CONNECT)
           I[i] = (RECEIVE | UNDEF_LEVEL | CONNECT);
         else
           I[i] = HI_LEVEL | RECEIVE;
        }

      *Y = (byte)(UNDEF_LEVEL | (*Y & 0xF0));

      return(MY_NO_ERROR);
    }

//=====================================================================
//  Процедура установки в начальное состояние
//---------------------------------------------------------------------
  void TAnd::Reset()
    {
      InitPin();
      Update();
    }

//=====================================================================
//  Процедура обновления окна состояния выводов элемента
//---------------------------------------------------------------------
  void TAnd::Update(void)
    {
      char symb[3];
      AnsiString temp;

      temp = "0123456789"; // данная строка необходима для резервирования места
                           // под 10 символов
      LevelToString((char)(I[0] & 0x0F),symb);
      strcpy(temp.c_str(),symb);
      AndForm->I0Label->Caption = temp;
      //
      LevelToString((char)(I[1] & 0x0F),symb);
      strcpy(temp.c_str(),symb);
      AndForm->I1Label->Caption = temp;
      //
      LevelToString((char)(I[2] & 0x0F),symb);
      strcpy(temp.c_str(),symb);
      AndForm->I2Label->Caption = temp;
      //
      LevelToString((char)(I[3] & 0x0F),symb);
      strcpy(temp.c_str(),symb);
      AndForm->I3Label->Caption = temp;
      //
      LevelToString((char)(*Y & 0x0F),symb);
      strcpy(temp.c_str(),symb);
      AndForm->YLabel->Caption = temp;
    }

//=====================================================================
//  Конструктор
//---------------------------------------------------------------------
  TAnd::TAnd(int Number,TComponent *Owner) : TModelItem(Number)
    {
      AnsiString temp(Number);

      AndForm = new TAndForm(Owner);
      ModelForm = AndForm;
      AndForm->Caption = "ЛЭ 'AND' D" + temp;
      I = NULL;
      Y = NULL;
    }

//=====================================================================
//  Деструктор
//---------------------------------------------------------------------
  TAnd::~TAnd()
    {
      if (AndForm != NULL)
        {
	      delete AndForm;
	    }
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  Конец описания прототипов методов класса TAnd
// // // // // // // // // // // // // // // // // // // // // // // //

