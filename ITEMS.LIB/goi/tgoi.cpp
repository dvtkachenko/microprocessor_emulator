
# include "TGoi.hpp"
# include <vcl\dstring.h>
# include "..\..\service\service.h"
# include <stdlib.h>
# include <string.h>

# define NUM_PARAM_GOI 3 // ����� ���������� ������������� ����������
// 1 - ��������� ������� �� ������ ���������� ��������
// 2 - ����� ������ ���������� �������� �� ������� �������
// 3 - ����� ��������

// // // // // // // // // // // // // // // // // // // // // // // //
//  �������� ���������� ������� ������ TGoi - ���������� ���������
//  ���������
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//  ����� Run . ������������ ������������� ������� ����������
//              � ���������� ������� �������(������)
//---------------------------------------------------------------------
  void TGoi::Run(void)
    {

      if (((FullTime+1) < StartDelayLenght) || ((FullTime+1) >= StartDelayLenght + CLKLenght))
    	{
    	  if (StartLevel == HI_LEVEL)
    	    {
    	      *Clk = HI_LEVEL;
    	    }
    	  else
    	    {
    	      *Clk = LOW_LEVEL;
    	    }
    	}
      else
    	{
   	      if (StartLevel == LOW_LEVEL)
       		{
       		  *Clk = HI_LEVEL;
       		}
   	      else
   	    	{
   	    	  *Clk = LOW_LEVEL;
   	    	}
   	    }

      FullTime++;
      // �������� ������������ FullTime
      if (FullTime == 0)
    	{
    	  StartDelayLenght = 0;
    	}
    }

//=====================================================================
//  ��������� ������������ ��������� ������� ����������
//---------------------------------------------------------------------
  void TGoi::Update(void)
    {
      char symb[3];
      AnsiString temp;

      temp = "0123456789"; // ������ ������ ���������� ��� �������������� �����
                           // ��� 10 ��������

      LevelToString((char)(*Clk & 0x0F),symb);
      strcpy(temp.c_str(),symb);
      GoiForm->Out1Label->Caption = temp;
      //
      ultoa(FullTime,temp.c_str(),10);
      GoiForm->KvantCountLabel->Caption = temp;
      //
      ultoa(CLKLenght,temp.c_str(),10);
      GoiForm->LenClkLabel->Caption = temp;
      //
      ultoa(StartDelayLenght,temp.c_str(),10);
      GoiForm->StartLabel->Caption = temp;
    }

//=====================================================================
//  ��������� �������������
//---------------------------------------------------------------------
  int TGoi::Init(string80 Array[])
    {
      StartLevel = (byte)  atoi (Array[0]);
      StartDelayLenght = (dword) atol (Array[1]);
      CLKLenght  = (dword) atol (Array[2]);
      //
      return(MY_NO_ERROR);
    }

//=====================================================================
//  ��������� ������������� ������� ������� ���������
//---------------------------------------------------------------------
  int TGoi::InitPin(void)
    {
      if(StartLevel == LOW_LEVEL) *Clk = (byte)((*Clk & 0xF0) | LOW_LEVEL);
      if(StartLevel == HI_LEVEL) *Clk = (byte)((*Clk & 0xF0) | HI_LEVEL);
      //
      return(MY_NO_ERROR);
    }

//=====================================================================
//  ��������� ��������� � ��������� ���������
//---------------------------------------------------------------------
  void TGoi::Reset()
    {
      FullTime = 0;
      InitPin();
      Update();
      //
    }

//=====================================================================
//  �����������
//---------------------------------------------------------------------
  TGoi::TGoi(int Number,TComponent *Owner) : TModelItem(Number)
    {
      AnsiString temp(Number);

      if ((Parameters = (byte *)malloc(2))==NULL)
    	Error = MY_ERROR;

      SetNumParameters(NUM_PARAM_GOI);
      GoiForm = new TGoiForm(Owner);
      ModelForm = GoiForm;
      GoiForm->Caption = "���  D" + temp;
      FullTime = 0;
      Clk = &Parameters[0];
    }

//=====================================================================
//  ����������
//---------------------------------------------------------------------
  TGoi::~TGoi()
    {
      if (GoiForm != NULL)
        {
	      delete GoiForm;
	    }
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  ����� �������� ���������� ������� ������ TGoi ���������� ���������
//  ���������
// // // // // // // // // // // // // // // // // // // // // // // //

