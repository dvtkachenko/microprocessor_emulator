# ifndef __TPzu_CPP
# define __TPzu_CPP 1

# include "TPzu.hpp"
# include "..\..\service\service.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <mem.h>
# include <alloc.h>

# define NUM_PARAM_PZU  2   // ����� ���������� ������������� ���
// 1 - ����������� �������������� ���� (8-128) ���
// 2 - ����� ������  �� 16 �� 1024 ����  (16,32,64,128,256,512,1024)

// ��������� ������� ��� ���������:
//   - ������� ���������� ��� �������� �����;   (1 ... Na)
//   - ����� ���� �� RE - ����������� ��������������� ������; (Na+1)
//   - ����� ��� �������������� ������ ;        (Na+2 ... Nq)
//    ��� Na - ���-�� �������� ������ (������� �� ������ ���):
//        Nq - ���-�� �������� ��������������� �����;

// ����� ��������� ���������� ��� �������� ��������� ���� ������� ���

// // // // // // // // // // // // // // // // // // // // // // // //
//  �������� ���������� ������� ������ TPzu - ���
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//  ����� Run . ������������ ������������� ������� ���
//              � ���������� ������� �������(������)
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
//  ��������� �������������
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
//  ��������� ������������� ������� ������� ���������
//---------------------------------------------------------------------
  int TPzu::InitPin(void)
    {
      for(int i=0;i<AddressSize;i++)
        {
          // ���� ���� ��������� � ����������� ���������,
          // �� ������������� �� ��� HI_LEVEL
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
//  ��������� ��������� � ��������� ���������
//---------------------------------------------------------------------
  void TPzu::Reset()
    {
      for(int i=0;i<MemSize;i++) Memory[i]->Clear();
      InitPin();
      //
    }

//=====================================================================
//  ��������� ���������� ����������� ����� PzuForm �� ������
//---------------------------------------------------------------------
  void TPzu::Update(void)
    {
      char *ptr;
      byte MemString[255];
      char symb[3];
      AnsiString temp;
      // ������ ������ ���������� ��� �������������� �����
      // ��� 60 ��������
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
//  �����������
//---------------------------------------------------------------------
  TPzu::TPzu(int Number,TComponent *Owner) : TModelItem(Number)
    {
      AnsiString temp(Number);

      SetNumParameters(NUM_PARAM_PZU);
      PzuForm = new TPzuForm(Owner);
      ModelForm = PzuForm;
      PzuForm->Caption = " ���  D" + temp;
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
//  ����������
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
//  ����� �������� ���������� ������� ������ TPzu
// // // // // // // // // // // // // // // // // // // // // // // //

// // // // // // // // // // // // // // // // // // // // // // // //
//  �������� ���������� ������� ������ TWord - ������������
//  ���� ����� ������
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//  ��������� ��������� ����� ������
//---------------------------------------------------------------------
  void TWord::Clear()
    {
      memset((void *)Word,0x00,WordLength);
    }

//=====================================================================
//  ��������� ������ ����� �� ������
//---------------------------------------------------------------------
  void TWord::Read(byte *ptr)
    {
      memcpy(ptr,Word,WordLength);
    }

//=====================================================================
//  ��������� ������ ����� � ������
//---------------------------------------------------------------------
  void TWord::Write(byte *ptr)
    {
      memcpy(Word,ptr,WordLength);
    }

//=====================================================================
//  �����������
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
//  ����������
//---------------------------------------------------------------------
  TWord::~TWord()
    {
      if (Word != NULL)
    	{
	      delete Word;
    	}
    }



// // // // // // // // // // // // // // // // // // // // // // // //
//  ����� �������� ���������� ������� ������ TWord
// // // // // // // // // // // // // // // // // // // // // // // //

# endif

