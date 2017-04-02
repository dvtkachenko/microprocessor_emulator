# include "TAndNo.hpp"
# include <vcl\dstring.h>
# include "..\..\service\service.h"
# include <stdlib.h>
# include <alloc.h>

// ��������� ������� �� "�-��" ���������:
//   - ������� ���������� ��� I - �����;    I0,I1,I2,I3 (1 ... 4)
//   - ����� NonY - ����� ;                    Y    (5)
// ����� ��������� ���������� ��� �������� ��������� ���� ������� �� "�"

// // // // // // // // // // // // // // // // // // // // // // // //
//  �������� ���������� ������� ������ TAnd - �� "�-��"
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//  ����� Run . ������������ ������������� ������� �� "�-��"
//              � ���������� ������� �������(������)
//---------------------------------------------------------------------
  void TAndNo::Run(void)
    {
      byte buf;
      bool LowFlag = false;

      // ������� ������� �� ���� �� �� ����� ����� ������ �������
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

      if (buf != UNDEF_LEVEL)
        {
          if (buf == LOW_LEVEL) buf = HI_LEVEL;
          else buf = LOW_LEVEL;
        }

      *NonY = (byte)((*NonY & 0xF0) | buf);
    }

//=====================================================================
//  ��������� �������������
//---------------------------------------------------------------------
  int TAndNo::Init(string80 Array[])
    {
      if ((Parameters = (byte *)malloc(NUM_I + 1))==NULL)
    	{
    	  Error = MY_ERROR;
    	  return(MY_ERROR);
    	}

      memset((void*)Parameters,0,NUM_I + 1);

      I = &Parameters[0];
      NonY = &Parameters[NUM_I];

      return(MY_NO_ERROR);
    }

//=====================================================================
//  ��������� ������������� ������� ������� ���������
//---------------------------------------------------------------------
  int TAndNo::InitPin(void)
    {
      int i;

      for(i=0;i<NUM_I;i++)
        {
         // ���� ���� ��������� � ����������� ���������,
         // �� ������������� �� ��� HI_LEVEL
         if (I[i] & CONNECT)
           I[i] = (RECEIVE | UNDEF_LEVEL | CONNECT);
         else
           I[i] = HI_LEVEL | RECEIVE;
        }

      *NonY = (byte)(UNDEF_LEVEL | (*NonY & 0xF0));

      return(MY_NO_ERROR);
    }

//=====================================================================
//  ��������� ��������� � ��������� ���������
//---------------------------------------------------------------------
  void TAndNo::Reset()
    {
      InitPin();
      Update();
    }

//=====================================================================
//  ��������� ���������� ���� ��������� ������� ��������
//---------------------------------------------------------------------
  void TAndNo::Update(void)
    {
      char symb[3];
      AnsiString temp;

      temp = "0123456789"; // ������ ������ ���������� ��� �������������� �����
                           // ��� 10 ��������
      LevelToString((char)(I[0] & 0x0F),symb);
      strcpy(temp.c_str(),symb);
      AndNoForm->I0Label->Caption = temp;
      //
      LevelToString((char)(I[1] & 0x0F),symb);
      strcpy(temp.c_str(),symb);
      AndNoForm->I1Label->Caption = temp;
      //
      LevelToString((char)(I[2] & 0x0F),symb);
      strcpy(temp.c_str(),symb);
      AndNoForm->I2Label->Caption = temp;
      //
      LevelToString((char)(I[3] & 0x0F),symb);
      strcpy(temp.c_str(),symb);
      AndNoForm->I3Label->Caption = temp;
      //
      LevelToString((char)(*NonY & 0x0F),symb);
      strcpy(temp.c_str(),symb);
      AndNoForm->YLabel->Caption = temp;
    }

//=====================================================================
//  �����������
//---------------------------------------------------------------------
  TAndNo::TAndNo(int Number,TComponent *Owner) : TModelItem(Number)
    {
      AnsiString temp(Number);

      AndNoForm = new TAndNoForm(Owner);
      ModelForm = AndNoForm;
      AndNoForm->Caption = "�� '�-��' D" + temp;
      I = NULL;
      NonY = NULL;
    }

//=====================================================================
//  ����������
//---------------------------------------------------------------------
  TAndNo::~TAndNo()
    {
      if (AndNoForm != NULL)
        {
	      delete AndNoForm;
	    }
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  ����� �������� ���������� ������� ������ TAndNo
// // // // // // // // // // // // // // // // // // // // // // // //

