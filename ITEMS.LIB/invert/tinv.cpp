# ifndef __TINV_CPP
# define __TINV_CPP 1

# include "service\service.cpp"
# include "items.lib\TInv.hpp"
# include "class\TWin_d.cpp"
# include <stdlib.h>
# include <alloc.h>

# define NUM_PARAM_INV 1 // число параметров инициализации инвертора
// 1 - кол-во элементов в пакете

// // // // // // // // // // // // // // // // // // // // // // // //
//  Описание прототипов методов класса TInvertor - инвертора
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//  Метод Run . Осуществляет моделирование функций инвертора
//              в дискретные моменты времени(кванты)
//---------------------------------------------------------------------
  void TInvertor::Run(void)
    {
      byte i;
      for(i=0;i<CountElem;i++)
	switch(In[i] & 0x0F)
          {
//            case HI_TO_LOW    : Out[i] = LOW_TO_HI  ;break;
//            case LOW_TO_HI    : Out[i] = HI_TO_LOW  ;break;
            case LOW_LEVEL    : Out[i] = HI_LEVEL   ;break;
            case HI_LEVEL     : Out[i] = LOW_LEVEL  ;break;
            case HZ           : Out[i] = LOW_LEVEL  ;break;
            case UNDEF_LEVEL  : Out[i] = UNDEF_LEVEL;break;
            default           : Out[i] = UNDEF_LEVEL;
          }
    }

//=====================================================================
//  Процедура инициализации
//---------------------------------------------------------------------
  int TInvertor::Init(string80 Array[])
    {
      byte i;
      CountElem = (byte) atoi (Array[0]);
      if (CountElem == 0)
        {
          Error = ERROR;
          return(ERROR);
        }

      if ((Parameters = (byte *)malloc(CountElem << 1))==NULL)
        {
          Error = ERROR;
          return(ERROR);
	}
      In = &Parameters[0];
      Out = &Parameters[CountElem];

      for(i=0;i<CountElem;i++) In[i]  = (RECEIVE | UNDEF_LEVEL);
      for(i=0;i<CountElem;i++) Out[i] = UNDEF_LEVEL;

      return(NO_ERROR);
    }

//=====================================================================
//  Процедура визуализации состояния выводов элемента
//---------------------------------------------------------------------
  void TInvertor::Show(void)
    {
      int i;
      char symb[3];

      for(i=0;i<CountElem;i++)
	{
	  LevelToString(In[i] & 0x0F,symb);
	  Invertor->wprint(1,8+i*9,symb);
	}

      for(i=0;i<CountElem;i++)
	{
	  LevelToString(Out[i] & 0x0F,symb);
	  Invertor->wprint(2,8+i*9,symb);
	}

    }

//=====================================================================
//  Конструктор
//---------------------------------------------------------------------
  TInvertor::TInvertor(int Number) : TModelItem(Number)
    {
      char Header[20],str[5];

      strcpy(Header," Инвертор D");
      itoa(Number,str,10);
      strcat(Header,str);

      Invertor = new TWindow(0x1A,Header);
      if (Invertor == NULL)
	{
	  Error = ERROR;
	}
      else
	{
	  Invertor->wopen(2,30,5,68,SINGLE_LINE);
	}
      Invertor->wprint(1,2," In0=     In1=     In2=     In3=   ");
      Invertor->wprint(2,2,"Out0=    Out1=    Out2=    Out3=   ");
      Invertor->SetSymbColor(0x0F);

      SetNumParameters(NUM_PARAM_INV);
      Out = NULL;
      In  = NULL;
    }

//=====================================================================
//  Деструктор
//---------------------------------------------------------------------
  TInvertor::~TInvertor()
    {
      if (Invertor != NULL)
	{
	  Invertor->wclose();
	  delete Invertor;
	}
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  Конец описания прототипов методов класса TInvertor 
// // // // // // // // // // // // // // // // // // // // // // // //
# endif
