
# include "TGener.hpp"
# include <vcl\dstring.h>
# include "..\..\service\service.h"
# include <stdlib.h>
# include <string.h>

# define NUM_PARAM_GENER 4 // ����� ���������� ������������� ����������
// 1 - ��������� �������
// 2 - ����� �����
// 3 - ����� 1-�� ����������
// 4 - ����� ������ ������ �� ������� �������
//     ������ �������� ��������� ��� ���� ����� ����� ���� ����������� �����
//     �������� ��������� ������������ ���� �����

// // // // // // // // // // // // // // // // // // // // // // // //
//  �������� ���������� ������� ������ TGenerator - ����������
//  ���������������
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//  ����� Run . ������������ ������������� ������� ����������
//              � ���������� ������� �������(������)
//---------------------------------------------------------------------
  void TGenerator::Run(void)
    {

      if ((FullTime+1) < StartDelayLenght)
    	{
    	  if (StartLevel == HI_LEVEL)
    	    {
    	      *Clk = HI_LEVEL;
    	      *NonClk = LOW_LEVEL;
    	    }
    	  else
    	    {
    	      *NonClk = HI_LEVEL;
    	      *Clk = LOW_LEVEL;
    	    }
    	}
      else
    	{
    	  if (InternalCounter == 0) TotalTakt++;

	  if ((InternalCounter >= 0 ) && ( InternalCounter < MT1_Lenght ))
	    {
	      if (StartLevel == LOW_LEVEL)
	    	{
	    	  *Clk = HI_LEVEL;
	    	  *NonClk = LOW_LEVEL;
	    	}
	      else
	    	{
	    	  *NonClk = HI_LEVEL;
	    	  *Clk = LOW_LEVEL;
	    	}
	    }

	  if ((InternalCounter >= MT1_Lenght) && (InternalCounter < CLKLenght))
	    {
	      if (StartLevel == LOW_LEVEL)
	    	{
		      *NonClk = HI_LEVEL;
	    	  *Clk = LOW_LEVEL;
	    	}
	      else
	    	{
	    	  *Clk = HI_LEVEL;
	    	  *NonClk = LOW_LEVEL;
	    	}
        }

    	  if (InternalCounter == CLKLenght-1)
    	    InternalCounter = 0;
    	  else
	        InternalCounter++;

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
  void TGenerator::Update(void)
    {
      char symb[3];
      char *ptr;
      AnsiString temp;

      LevelToString((char)(*Clk & 0x0F),symb);
      temp = "0123456789"; // ������ ������ ���������� ��� �������������� �����
                           // ��� 10 ��������
      ptr = temp.c_str();
      strcpy(ptr,symb);
      GeneratorForm->Out1Label->Caption = temp;
      //
      LevelToString((char)(*NonClk & 0x0F),symb);
      strcpy(ptr,symb);
      GeneratorForm->Out2Label->Caption = temp;
      //
      ultoa(FullTime,ptr,10);
      GeneratorForm->KvantCountLabel->Caption = temp;
      //
      ultoa(MT1_Lenght,ptr,10);
      GeneratorForm->SizeT1Label->Caption = temp;
      //
      ultoa(CLKLenght - MT1_Lenght,ptr,10);
      GeneratorForm->SizeT2Label->Caption = temp;
      //
      ultoa(StartDelayLenght,ptr,10);
      GeneratorForm->StartLabel->Caption = temp;
      //
      ultoa(TotalTakt,ptr,10);
      GeneratorForm->TotalTaktLabel->Caption = temp;
    }

//=====================================================================
//  ��������� �������������
//---------------------------------------------------------------------
  int TGenerator::Init(string80 Array[])
    {
      StartLevel = (byte)  atoi (Array[0]);
      CLKLenght  = (dword) atol (Array[1]);
      MT1_Lenght = (dword) atol (Array[2]);
      StartDelayLenght = (dword) atol (Array[3]);
      //
      return(MY_NO_ERROR);
    }

//=====================================================================
//  ��������� �������������
//---------------------------------------------------------------------
  int TGenerator::InitPin(void)
    {
      if(StartLevel == LOW_LEVEL)
        {
          *Clk = (byte)(LOW_LEVEL | (*Clk & 0xF0));
          *NonClk = (byte)(HI_LEVEL | (*NonClk & 0xF0));
        }

      if(StartLevel == HI_LEVEL)
        {
          *Clk = (byte)(HI_LEVEL | (*Clk & 0xF0));
          *NonClk = (byte)(LOW_LEVEL | (*NonClk & 0xF0));
        }
      //
      return(MY_NO_ERROR);
    }

//=====================================================================
//  ��������� ��������� � ��������� ���������
//---------------------------------------------------------------------
  void TGenerator::Reset()
    {
      FullTime = 0;
      TotalTakt = 0;
      InternalCounter = 0;
      InitPin();
      Update();
      //
    }

//=====================================================================
//  �����������
//---------------------------------------------------------------------
  TGenerator::TGenerator(int Number,TComponent *Owner) : TModelItem(Number)
    {
      AnsiString temp(Number);
      
      if ((Parameters = (byte *)malloc(2))==NULL)
    	Error = MY_ERROR;

      SetNumParameters(NUM_PARAM_GENER);
      GeneratorForm = new TGeneratorForm(Owner);
      ModelForm = GeneratorForm;
      GeneratorForm->Caption = "��������� ��������� D" + temp;
      FullTime = 0;
      TotalTakt = 0;
      InternalCounter = 0;
      Clk = &Parameters[0];
      NonClk = &Parameters[1];
    }

//=====================================================================
//  ����������
//---------------------------------------------------------------------
  TGenerator::~TGenerator()
    {
      if (GeneratorForm != NULL)
        {
	      delete GeneratorForm;
	    }
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  ����� �������� ���������� ������� ������ TGenerator ����������
//  ���������������
// // // // // // // // // // // // // // // // // // // // // // // //

