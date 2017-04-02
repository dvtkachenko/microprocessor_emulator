# ifndef __TPzu_CPP
# define __TPzu_CPP 1

# include "TPzu.hpp"
# include "..\..\service\service.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <mem.h>
# include <alloc.h>

# define NUM_PARAM_PZU  2   // число параметров инициализации ПЗУ
// 1 - разрядность информационных слов (8-128) бит
// 2 - объем памяти  от 16 до 1024 слов  (16,32,64,128,256,512,1024)

// Нумерация выводов ПЗУ следующая:
//   - сначала нумеруются все адресные входы;   (1 ... Na)
//   - далее вход не RE - управляющий преобразованием адреса; (Na+1)
//   - далее все информационные выходы ;        (Na+2 ... Nq)
//    где Na - кол-во адресных входов (зависит от объема ПЗУ):
//        Nq - кол-во разрядов информационного слова;

// Такая нумерация необходима для линейной адресации всех выводов ПЗУ

// // // // // // // // // // // // // // // // // // // // // // // //
//  Описание прототипов методов класса TPzu - ПЗУ
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//  Метод Run . Осуществляет моделирование функций ПЗУ
//              в дискретные моменты времени(кванты)
//---------------------------------------------------------------------
  void TPzu::Run(void)
    {
      byte i;
      int Address;
      char buf[11];

      if (((*NonRE) & 0x0F) == LOW_LEVEL)
    	{
          for(i=0;i<WordLength;i++)
            {
              Q[i] = (byte)(HI_LEVEL | (Q[i] & 0xF0));
            }
//    	  memset((void *)Q,HI_LEVEL | CONNECT),WordLength);
    	}

      if (((*NonRE) & 0x0F) == HI_LEVEL)
    	{
    	  memcpy(buf,A,AddressSize);
    	  for(i=0;i<AddressSize;i++)
    	    {
    	      buf[i] &= 0x0F;
    	      if (buf[i] == UNDEF_LEVEL)
                {
                  for(i=0;i<WordLength;i++)
                    {
                      Q[i] = (byte)(UNDEF_LEVEL | (Q[i] & 0xF0));
                    }
                  return;
                }
    	    }

    	  StrRev(buf,AddressSize);
    	  Address = (int)StrToUnLong(buf,0,AddressSize);
    	  Memory[Address]->Read(Q);
          PzuForm->CurrentAddress = Address;
    	}
    }

//=====================================================================
//  Процедура инициализации
//---------------------------------------------------------------------
  int TPzu::Init(string80 Array[])
    {
      int i;
      //
      WordLength = atoi (Array[0]);
      if ((WordLength < 8) || (WordLength > 128))
    	{
    	  Error = MY_ERROR;
    	  return MY_ERROR;
    	}

      MemSize = atoi (Array[1]);
      if ((MemSize < 16) || (MemSize > 1024))
    	{
    	  Error = MY_ERROR;
    	  return MY_ERROR;
    	}

      PzuForm->MemScrollBar->Max = MemSize - 11;

      AddressSize = (int)ceil(log(MemSize)/log(2));

      Memory = (TWord **)malloc(MemSize*sizeof(TWord *));
      if (Memory == NULL)
    	{
	      Error = MY_ERROR;
    	  return(MY_ERROR);
    	}

      PzuForm->Memory = Memory;
      PzuForm->WordLength = WordLength;
      PzuForm->MemSize = MemSize;

      for(i=0;i<MemSize;i++)
    	{
    	  Memory[i] = new TWord(WordLength);
    	  if (Memory[i] == NULL)
    	    {
    	      for(int j=0;j<i;j++)
    	    	{
    	    	  delete Memory[j];
    	    	}
    	      free (Memory);
    	      Error = MY_ERROR;
    	      return MY_ERROR;
    	    }
    	  //
    	  Memory[i]->Clear();
	    }

      A = &Parameters[0];
      NonRE = &Parameters[AddressSize];
      Q = &Parameters[AddressSize+1];

      return(MY_NO_ERROR);
    }

//=====================================================================
//  Процедура инициализации моделей выводов элементов
//---------------------------------------------------------------------
  int TPzu::InitPin(void)
    {
      for(int i=0;i<AddressSize;i++)
        {
          // если вход находится в подвешенном состоянии,
          // то устанавливаем на нем HI_LEVEL
          if (A[i] & CONNECT)
            A[i] = (RECEIVE | UNDEF_LEVEL | CONNECT);
          else
            A[i] = (byte)(HI_LEVEL | (A[i] & 0xF0));
        }

      if (*NonRE & CONNECT) *NonRE = (RECEIVE | UNDEF_LEVEL | CONNECT);
      else *NonRE = (byte)(HI_LEVEL | (*NonRE & 0xF0));

      for(int i=0;i<WordLength;i++) Q[i] = (byte)(UNDEF_LEVEL | (Q[i] & 0xF0));
      //
      PzuForm->Update();
      return(MY_NO_ERROR);
    }
//=====================================================================
//  Процедура установки в начальное состояние
//---------------------------------------------------------------------
  void TPzu::Reset()
    {
      for(int i=0;i<MemSize;i++) Memory[i]->Clear();
      InitPin();
      //
    }

//=====================================================================
//  Процедура обновления содержимого формы PzuForm на экране
//---------------------------------------------------------------------
  void TPzu::Update(void)
    {
      char *ptr;
      byte MemString[255];
      char symb[3];
      AnsiString temp;
      // данная строка необходима для резервирования места
      // под 60 символов
      temp = "012345678901234567890123456789012345678901234567890123456789";
      //
      ptr = temp.c_str();

      memcpy(ptr,A,AddressSize);
      StrRev(ptr,AddressSize);
      BinNumToBinSymb(ptr,AddressSize);
      PzuForm->InAdrLabel->Caption = temp;
      //
      LevelToString((char)(*NonRE & 0x0F),symb);
      strcpy(ptr,symb);
      PzuForm->RELabel->Caption = temp;
      //
      memcpy(MemString,Q,WordLength);
      BinToHex((char*)MemString,WordLength,ptr);
      PzuForm->OutDataLabel->Caption = temp;

      PzuForm->ShowAdrLabel();
      PzuForm->ShowMemory();
      //
    }

//=====================================================================
//  Конструктор
//---------------------------------------------------------------------
  TPzu::TPzu(int Number,TComponent *Owner) : TModelItem(Number)
    {
      AnsiString temp(Number);

      SetNumParameters(NUM_PARAM_PZU);
      PzuForm = new TPzuForm(Owner);
      ModelForm = PzuForm;
      PzuForm->Caption = " ПЗУ  D" + temp;
      PzuForm->CurrentAddress = 0;
      PzuForm->TopAddress = 0;
      PzuForm->UndefAddressFlag = true;
      if ((Parameters = (byte *)malloc(MAX_PIN_NUM))==NULL)
    	{
    	  Error = MY_ERROR;
    	}

      memset((void*)Parameters,0,MAX_PIN_NUM);
    }

//=====================================================================
//  Деструктор
//---------------------------------------------------------------------
  TPzu::~TPzu()
    {
      if (Memory != NULL)
       {
	    delete Memory;
	   }

      if (PzuForm != NULL)
       {
	    delete PzuForm;
	   }
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  Конец описания прототипов методов класса TPzu
// // // // // // // // // // // // // // // // // // // // // // // //

// // // // // // // // // // // // // // // // // // // // // // // //
//  Описание прототипов методов класса TWord - реализующего
//  одно слово памяти
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//  процедура обнуления слова памяти
//---------------------------------------------------------------------
  void TWord::Clear()
    {
      memset((void *)Word,0x00,WordLength);
    }

//=====================================================================
//  процедура чтения слова из памяти
//---------------------------------------------------------------------
  void TWord::Read(byte *ptr)
    {
      memcpy(ptr,Word,WordLength);
    }

//=====================================================================
//  процедура записи слова в память
//---------------------------------------------------------------------
  void TWord::Write(byte *ptr)
    {
      memcpy(Word,ptr,WordLength);
    }

//=====================================================================
//  Конструктор
//---------------------------------------------------------------------
  TWord::TWord(int Length)
    {
      Error = MY_NO_ERROR;

      WordLength = Length;
      Word = (byte *)malloc(WordLength+1);

      if (Word == NULL)
    	Error = MY_ERROR;
      else
    	Clear();
    }

//=====================================================================
//  Деструктор
//---------------------------------------------------------------------
  TWord::~TWord()
    {
      if (Word != NULL)
    	{
	      delete Word;
    	}
    }



// // // // // // // // // // // // // // // // // // // // // // // //
//  Конец описания прототипов методов класса TWord
// // // // // // // // // // // // // // // // // // // // // // // //

# endif

