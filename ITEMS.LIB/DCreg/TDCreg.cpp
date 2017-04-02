# include "TDCreg.hpp"
# include "..\..\service\service.h"
# include <vcl\dstring.h>
# include <stdlib.h>
# include <alloc.h>
# include <mem.h>

# define NUM_PARAM_REG 1 // ����� ���������� ������������� ��������
// 1 - ���-�� �������� � ��������

// ��������� ������� �������� ���������:
//   - ������� ���������� ��� D - �����;   (1 ... n)
//   - ����� C - ���� ;                    (n+1)
//   - ����� NonR - ���� ;                 (n+2)
//   - ����� ��� Q - ������ ;              (n+3 ... n+n+4)
//           ��� n - ���������� �������� � ��������.
// ����� ��������� ���������� ��� �������� ��������� ���� ������� ��������

// // // // // // // // // // // // // // // // // // // // // // // //
//  �������� ���������� ������� ������ TDCreg - DC-��������
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//  ����� Run . ������������ ������������� ������� �������� �� D-���������
//              � ���������� ������� �������(������)
//---------------------------------------------------------------------
  void TDCreg::Run(void)
    {
      byte i;

   	  CurLevelClk = (byte)(*C & 0x0F);
      for(i=0;i<CountElem;i++)
    	{
    	  if ((*NonR & 0x0F) == LOW_LEVEL)
    	    {
    	      Q[i] = (byte)(LOW_LEVEL | (Q[i] & 0xF0));
    	    }

    	  if ((*NonR & 0x0F) == HI_LEVEL)
    	    {
    	      if ((PrevLevelClk == LOW_LEVEL) && (CurLevelClk == HI_LEVEL))
    	    	{
                  Q[i] = (byte)((D[i] & 0x0F) | (Q[i] & 0xF0));
        		}
    	    }
    	} // end of for
   	  //
   	  PrevLevelClk = CurLevelClk;
    }

//=====================================================================
//  ��������� �������������
//---------------------------------------------------------------------
  int TDCreg::Init(string80 Array[])
    {
      CountElem = (byte) atoi (Array[0]);
      if (CountElem == 0)
    	{
    	  Error = MY_ERROR;
    	  return(MY_ERROR);
    	}

      if ((Parameters = (byte *)malloc((CountElem << 1) + 2))==NULL)
    	{
    	  Error = MY_ERROR;
    	  return(MY_ERROR);
    	}

      memset(Parameters,0,((CountElem << 1) + 2));

      PrevLevelClk = UNDEF_LEVEL;
	  CurLevelClk = UNDEF_LEVEL;

      D = &Parameters[0];
      C = &Parameters[CountElem];
      NonR = &Parameters[CountElem+1];
      Q = &Parameters[CountElem+2];

      return(MY_NO_ERROR);
    }

//=====================================================================
//  ��������� ������������� ������� ������� ���������
//---------------------------------------------------------------------
  int TDCreg::InitPin(void)
    {
      int i;

      if (*C & CONNECT) *C = (byte)(UNDEF_LEVEL | RECEIVE | (*C & 0xF0));
      else *C = (HI_LEVEL | RECEIVE);

      if (*NonR & CONNECT) *NonR = (byte)(UNDEF_LEVEL | RECEIVE | (*NonR & 0xF0));
      else *NonR = (HI_LEVEL | RECEIVE);

      for(i=0;i<CountElem;i++)
        {
          if (D[i] & CONNECT)  D[i] = (byte)(UNDEF_LEVEL | RECEIVE | (D[i] & 0xF0));
          else D[i] = (HI_LEVEL | RECEIVE);
        }

      for(i=0;i<CountElem;i++) Q[i] = (byte)(UNDEF_LEVEL | (Q[i] & 0xF0));

      return(MY_NO_ERROR);
    }

//=====================================================================
//  ��������� ��������� � ��������� ���������
//---------------------------------------------------------------------
  void TDCreg::Reset()
    {
      PrevLevelClk = UNDEF_LEVEL;
	  CurLevelClk = UNDEF_LEVEL;
      InitPin();
      Update();
      //
    }

//=====================================================================
//  ��������� ���������� ����������� �����
//---------------------------------------------------------------------
  void TDCreg::Update(void)
    {
      byte RegString[255];
      char symb[3];
      AnsiString temp;
      // ������ ������ ���������� ��� �������������� �����
      // ��� 60 ��������
      temp = "012345678901234567890123456789012345678901234567890123456789";
      //
      LevelToString((char)(*NonR & 0x0F),symb);
      strcpy(temp.c_str(),symb);
      DCregForm->RLabel->Caption = temp;
      //
      LevelToString((char)(*C & 0x0F),symb);
      strcpy(temp.c_str(),symb);
      DCregForm->ClkLabel->Caption = temp;
      //
      memcpy(RegString,D,CountElem);
      BinToHex((char*)RegString,CountElem,temp.c_str());
      DCregForm->DLabel->Caption = temp;
      //
      memcpy(RegString,Q,CountElem);
      BinToHex((char*)RegString,CountElem,temp.c_str());
      DCregForm->QLabel->Caption = temp;
    }

//=====================================================================
//  �����������
//---------------------------------------------------------------------
  TDCreg::TDCreg(int Number,TComponent *Owner) : TModelItem(Number)
    {
      AnsiString temp(Number);

      DCregForm = new TDCregForm(Owner);
      ModelForm = DCregForm;
      DCregForm->Caption = "DC �������  D" + temp;
      SetNumParameters(NUM_PARAM_REG);

      D = NULL;
      C = NULL;
      NonR = NULL;
      Q = NULL;
    }

//=====================================================================
//  ����������
//---------------------------------------------------------------------
  TDCreg::~TDCreg()
    {
      if (DCregForm != NULL)
    	{
    	  delete DCregForm;
    	}
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  ����� �������� ���������� ������� ������ TDCreg
// // // // // // // // // // // // // // // // // // // // // // // //

