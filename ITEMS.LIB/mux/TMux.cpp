# include "TMux.hpp"
# include <vcl\dstring.h>
# include "..\..\service\service.h"
# include <stdlib.h>
# include <alloc.h>

// Нумерация выводов мультиплексора следующая:
//   - сначала нумеруются все I - входы;    I0,I1,I2,I3 (1 ... 4)
//   - далее все S - входы ;                S0,S1 (5 ... 6) S0 - младший разряд
//   - далее все NonY - выходы ;            NonY    (7)
// Такая нумерация необходима для линейной адресации всех выводов регистра

// // // // // // // // // // // // // // // // // // // // // // // //
//  Описание прототипов методов класса TMux - мультиплексора
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//  Метод Run . Осуществляет моделирование функций мультиплексора с инвертором
//              в дискретные моменты времени(кванты)
//---------------------------------------------------------------------
  void TMux::Run(void)
    {
      byte buf[NUM_S + 1];
      dword Address;

      if (CheckUndefLevel(S,NUM_S)) return;

      // формируем адрес мультиплексируемого входа
      memcpy(buf,S,NUM_S);
      StrRev((char*)buf,NUM_S);
      Address = StrToUnLong((char*)buf,0,NUM_S);
      // формируем выходное значение
      *Y = (byte)((*Y & 0xF0) | (I[Address] & 0x0F));

      // ... и инвертируем его
      if ((*Y & 0x0F) != UNDEF_LEVEL)
        {
          if ((*Y & 0x0F) == HI_LEVEL) *Y = (byte)(LOW_LEVEL | (*Y & 0xF0));
                                      // записываем в младшую часть байта
          else *Y = (byte)(HI_LEVEL | (*Y & 0xF0));
                    // записываем в младшую часть байта
        }
    }

//=====================================================================
//  Процедура инициализации
//---------------------------------------------------------------------
  int TMux::Init(string80 Array[])
    {
      if ((Parameters = (byte *)malloc(NUM_I + NUM_S + 1))==NULL)
    	{
    	  Error = MY_ERROR;
    	  return(MY_ERROR);
    	}

      memset((void*)Parameters,0,NUM_I + NUM_S + 1);

      I = &Parameters[0];
      S = &Parameters[NUM_I];
      Y = &Parameters[NUM_I + NUM_S];

      return(MY_NO_ERROR);
    }

//=====================================================================
//  Процедура инициализации выводов моделей элементов
//---------------------------------------------------------------------
  int TMux::InitPin(void)
    {
      int i;

      for(i=0;i<NUM_I;i++)
        {
         // если вход находится в подвешенном состоянии,
         // то устанавливаем на нем HI_LEVEL
         if (I[i] & CONNECT)
           I[i] = (RECEIVE | UNDEF_LEVEL | CONNECT);
         else
           I[i] = (HI_LEVEL | RECEIVE);
        }
      for(i=0;i<NUM_S;i++)
        {
         // если вход находится в подвешенном состоянии,
         // то устанавливаем на нем HI_LEVEL
         if (S[i] & CONNECT)
           S[i] = (RECEIVE | UNDEF_LEVEL | CONNECT);
         else
           S[i] = (HI_LEVEL | RECEIVE | CONNECT);
        }

      *Y = (byte)(UNDEF_LEVEL | (*Y & 0xF0));

      return(MY_NO_ERROR);
    }

//=====================================================================
//  Процедура установки в начальное состояние
//---------------------------------------------------------------------
  void TMux::Reset()
    {
      InitPin();
      Update();
      //
    }

//=====================================================================
//  Процедура обновления окна состояния выводов элемента
//---------------------------------------------------------------------
  void TMux::Update(void)
    {
      char symb[3];
      AnsiString temp;

      temp = "0123456789"; // данная строка необходима для резервирования места
                           // под 10 символов
      LevelToString((char)(I[0] & 0x0F),symb);
      strcpy(temp.c_str(),symb);
      MuxForm->I0Label->Caption = temp;
      //
      LevelToString((char)(I[1] & 0x0F),symb);
      strcpy(temp.c_str(),symb);
      MuxForm->I1Label->Caption = temp;
      //
      LevelToString((char)(I[2] & 0x0F),symb);
      strcpy(temp.c_str(),symb);
      MuxForm->I2Label->Caption = temp;
      //
      LevelToString((char)(I[3] & 0x0F),symb);
      strcpy(temp.c_str(),symb);
      MuxForm->I3Label->Caption = temp;
      //
      LevelToString((char)(S[0] & 0x0F),symb);
      strcpy(temp.c_str(),symb);
      MuxForm->S0Label->Caption = temp;
      //
      LevelToString((char)(S[1] & 0x0F),symb);
      strcpy(temp.c_str(),symb);
      MuxForm->S1Label->Caption = temp;
      //
      LevelToString((char)(*Y & 0x0F),symb);
      strcpy(temp.c_str(),symb);
      MuxForm->YLabel->Caption = temp;
    }

//=====================================================================
//  Конструктор
//---------------------------------------------------------------------
  TMux::TMux(int Number,TComponent *Owner) : TModelItem(Number)
    {
      AnsiString temp(Number);

      MuxForm = new TMuxForm(Owner);
      ModelForm = MuxForm;
      MuxForm->Caption = "Мультиплексор D" + temp;
      I = NULL;
      S = NULL;
      Y = NULL;
    }

//=====================================================================
//  Деструктор
//---------------------------------------------------------------------
  TMux::~TMux()
    {
      if (MuxForm != NULL)
        {
	      delete MuxForm;
	    }
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  Конец описания прототипов методов класса TMux
// // // // // // // // // // // // // // // // // // // // // // // //

