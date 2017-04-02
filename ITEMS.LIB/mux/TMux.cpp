# include "TMux.hpp"
# include <vcl\dstring.h>
# include "..\..\service\service.h"
# include <stdlib.h>
# include <alloc.h>

// ��������� ������� �������������� ���������:
//   - ������� ���������� ��� I - �����;    I0,I1,I2,I3 (1 ... 4)
//   - ����� ��� S - ����� ;                S0,S1 (5 ... 6) S0 - ������� ������
//   - ����� ��� NonY - ������ ;            NonY    (7)
// ����� ��������� ���������� ��� �������� ��������� ���� ������� ��������

// // // // // // // // // // // // // // // // // // // // // // // //
//  �������� ���������� ������� ������ TMux - ��������������
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//  ����� Run . ������������ ������������� ������� �������������� � ����������
//              � ���������� ������� �������(������)
//---------------------------------------------------------------------
  void TMux::Run(void)
    {
      byte buf[NUM_S + 1];
      dword Address;

      if (CheckUndefLevel(S,NUM_S)) return;

      // ��������� ����� ������������������� �����
      memcpy(buf,S,NUM_S);
      StrRev((char*)buf,NUM_S);
      Address = StrToUnLong((char*)buf,0,NUM_S);
      // ��������� �������� ��������
      *Y = (byte)((*Y & 0xF0) | (I[Address] & 0x0F));

      // ... � ����������� ���
      if ((*Y & 0x0F) != UNDEF_LEVEL)
        {
          if ((*Y & 0x0F) == HI_LEVEL) *Y = (byte)(LOW_LEVEL | (*Y & 0xF0));
                                      // ���������� � ������� ����� �����
          else *Y = (byte)(HI_LEVEL | (*Y & 0xF0));
                    // ���������� � ������� ����� �����
        }
    }

//=====================================================================
//  ��������� �������������
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
//  ��������� ������������� ������� ������� ���������
//---------------------------------------------------------------------
  int TMux::InitPin(void)
    {
      int i;

      for(i=0;i<NUM_I;i++)
        {
         // ���� ���� ��������� � ����������� ���������,
         // �� ������������� �� ��� HI_LEVEL
         if (I[i] & CONNECT)
           I[i] = (RECEIVE | UNDEF_LEVEL | CONNECT);
         else
           I[i] = (HI_LEVEL | RECEIVE);
        }
      for(i=0;i<NUM_S;i++)
        {
         // ���� ���� ��������� � ����������� ���������,
         // �� ������������� �� ��� HI_LEVEL
         if (S[i] & CONNECT)
           S[i] = (RECEIVE | UNDEF_LEVEL | CONNECT);
         else
           S[i] = (HI_LEVEL | RECEIVE | CONNECT);
        }

      *Y = (byte)(UNDEF_LEVEL | (*Y & 0xF0));

      return(MY_NO_ERROR);
    }

//=====================================================================
//  ��������� ��������� � ��������� ���������
//---------------------------------------------------------------------
  void TMux::Reset()
    {
      InitPin();
      Update();
      //
    }

//=====================================================================
//  ��������� ���������� ���� ��������� ������� ��������
//---------------------------------------------------------------------
  void TMux::Update(void)
    {
      char symb[3];
      AnsiString temp;

      temp = "0123456789"; // ������ ������ ���������� ��� �������������� �����
                           // ��� 10 ��������
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
//  �����������
//---------------------------------------------------------------------
  TMux::TMux(int Number,TComponent *Owner) : TModelItem(Number)
    {
      AnsiString temp(Number);

      MuxForm = new TMuxForm(Owner);
      ModelForm = MuxForm;
      MuxForm->Caption = "������������� D" + temp;
      I = NULL;
      S = NULL;
      Y = NULL;
    }

//=====================================================================
//  ����������
//---------------------------------------------------------------------
  TMux::~TMux()
    {
      if (MuxForm != NULL)
        {
	      delete MuxForm;
	    }
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  ����� �������� ���������� ������� ������ TMux
// // // // // // // // // // // // // // // // // // // // // // // //

