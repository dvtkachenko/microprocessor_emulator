# ifndef __TTrig_DC_CPP
# define __TTrig_DC_CPP 1

# include "items.lib\TTrig_DC.hpp"
# include "service\service.cpp"
# include <stdlib.h>
# include <alloc.h>

# define NUM_PARAM_REG 1 // ����� ���������� ������������� ��������
// 1 - ���-�� ��������� � ��������

// ��������� ������� �������� ���������:
//   - ������� ���������� ��� D - �����;   (1 ... n)
//   - ����� ��� C - ����� ;               (n+1 ... 2*n)
//   - ����� ��� NonR - ����� ;            (2*n+1 ... 3*n)
//   - ����� ��� Q - ������ ;              (3*n+1 ... 4*n)
//   - ����� ��� NonQ - ������ ;           (4*n+1 ... 5*n)
//           ��� n - ����������  DC- ��������� � ������.
// ����� ��������� ���������� ��� �������� ��������� ���� ������� ��������

// // // // // // // // // // // // // // // // // // // // // // // //
//  �������� ���������� ������� ������ TTrigger_DC - DC-��������
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//  ����� Run . ������������ ������������� ������� �������� �� D-���������
//              � ���������� ������� �������(������)
//---------------------------------------------------------------------
  void TTrigger_DC::Run(void)
    {
      byte i;

      for(i=0;i<CountElem;i++)
	{
	  CurLevelClk[i] = (C[i] & 0x0F);

	  if ((NonR[i] & 0x0F) == LOW_LEVEL)
	    {
	      Q[i] = LOW_LEVEL ;
	      NonQ[i] = HI_LEVEL ;
	    }

	  if ((NonR[i] & 0x0F) == HI_LEVEL)
	    {
	      if ((PrevLevelClk[i] == LOW_LEVEL) &&
		  (CurLevelClk[i] == HI_LEVEL))
		{
		  if ((D[i] & 0x0F) == LOW_LEVEL)
		    {
		      Q[i] = LOW_LEVEL ;
		      NonQ[i] = HI_LEVEL ;
		    }

		  if ((D[i] & 0x0F) == HI_LEVEL)
		    {
		      Q[i] = HI_LEVEL ;
		      NonQ[i] = LOW_LEVEL ;
		    }

		  if ((D[i] & 0x0F) == UNDEF_LEVEL)
		    {
		      Q[i] = UNDEF_LEVEL ;
		      NonQ[i] = UNDEF_LEVEL ;
		    }
		}
	    }
	  //
	  PrevLevelClk[i] = CurLevelClk[i];

	} // end of for
    }

//=====================================================================
//  ��������� �������������
//---------------------------------------------------------------------
  int TTrigger_DC::Init(string80 Array[])
    {
      byte i;
      CountElem = (byte) atoi (Array[0]);
      if (CountElem == 0)
	{
	  Error = ERROR;
	  return(ERROR);
	}

      if ((Parameters = (byte *)malloc((CountElem << 2) + CountElem))==NULL)
	{
	  Error = ERROR;
	  return(ERROR);
	}

      if ((PrevLevelClk = (byte *)malloc(CountElem)) == NULL)
	{
	  Error = ERROR;
	  return(ERROR);
	}
      else
	{
	  for(i=0;i<CountElem;i++) PrevLevelClk[i] = UNDEF_LEVEL;
	}

      if ((CurLevelClk = (byte *)malloc(CountElem)) == NULL)
	{
	  Error = ERROR;
	  return(ERROR);
	}
      else
	{
	  for(i=0;i<CountElem;i++) CurLevelClk[i] = UNDEF_LEVEL;
	}

      D = &Parameters[0];
      C = &Parameters[CountElem];
      NonR = &Parameters[2*CountElem];
      Q = &Parameters[3*CountElem];
      NonQ = &Parameters[4*CountElem];

      for(i=0;i<CountElem;i++) D[i]  = (RECEIVE | UNDEF_LEVEL);
      for(i=0;i<CountElem;i++) C[i]  = (RECEIVE | UNDEF_LEVEL);
      for(i=0;i<CountElem;i++) NonR[i]  = (RECEIVE | UNDEF_LEVEL);
      for(i=0;i<CountElem;i++) Q[i] = UNDEF_LEVEL;
      for(i=0;i<CountElem;i++) NonQ[i] = UNDEF_LEVEL;

      return(NO_ERROR);
    }

//=====================================================================
//  ��������� ������������ ��������� ������� ��������
//---------------------------------------------------------------------
  void TTrigger_DC::Show(void)
    {
    }

//=====================================================================
//  �����������
//---------------------------------------------------------------------
  TTrigger_DC::TTrigger_DC(int Number) : TModelItem(Number)
    {
      SetNumParameters(NUM_PARAM_REG);
      D = NULL;
      C = NULL;
      NonR = NULL;
      Q = NULL;
      NonQ = NULL;
    }

//=====================================================================
//  ����������
//---------------------------------------------------------------------
  TTrigger_DC::~TTrigger_DC()
    {
      if (PrevLevelClk != NULL)
	{
	  free(PrevLevelClk);
	}

      if (CurLevelClk != NULL)
	{
	  free(CurLevelClk);
	}

    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  ����� �������� ���������� ������� ������ TTrigger_DC
// // // // // // // // // // // // // // // // // // // // // // // //

# endif
