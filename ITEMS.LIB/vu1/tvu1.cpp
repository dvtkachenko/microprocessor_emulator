# ifndef __TVU1_CPP
# define __TVU1_CPP 1

# include "service\service.cpp"
# include "items.lib\TVu1.hpp"
# include "class\TWin_d.cpp"
# include <stdlib.h>
# include <alloc.h>

// // // // // // // // // // // // // // // // // // // // // // // //
//  �������� ���������� ������� ������ TVu1 - ��� �1804��1
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//  ����� Run . ������������ ������������� ������� ��� �1804��1
//              � ���������� ������� �������(������)
//---------------------------------------------------------------------
  void TVu1::Run(void)
    {
      MI = Parameters[0];
      RE = Parameters[1];
      CI = Parameters[2];
      S0 = Parameters[3];
      S1 = Parameters[4];
      QR = Parameters[5];
      D  = Parameters[6];

      if ((MI==2) || (MI==6))  PE=1;  else PE=0;   /*  ������������ ��������  */
      if (MI==2)               ME=0;  else ME=1;   /*    �������� PE � ��     */
      if (MI==0)  CT=0;                            /*  ������������     */
      if (((MI==4) && (CC==1)) || (MI==12))  CT=D; /*    ��������       */
      if ((MI==8) || (MI==9))  CT=(CT-1)&0xF;       /*  �������� ������  */
      if (CT==0)  ZCT=1;   /*  ������������ ��������  */
      else        ZCT=0;   /*      ���� ��������      */
      if (RE==0) RA=D;     /*  ������ ������ � ������� RA  */
      CMK=(Y+CI)&0xF;       /*  ��������� �������� ����������� �� ������ 16  */

      Y=CMK;
	  /*-----------------------------------*/
	  /*  ���������� ��������� ����������  */
	  /*-----------------------------------*/
      switch(MI)
       {
	case 0:         Y=0;
			break;

	case 1:         if (CC==1)
			  {
			    Y=D;
			    STEK[StP]=CMK;
			    StP++;
			  }
			break;

	case 2:case 15: Y=D;
			break;

	case 3:case  6: if (CC==1)
			  Y=D;
			break;

	case 4:         STEK[StP]=CMK;
			  StP++;
			break;

	case 5:         STEK[StP]=CMK;
			StP++;
			if (CC==1)
			 Y=D;
			else
			 Y=RA;
			break;

	case 7:         if (CC==1)
			 Y=D;
			else
			 Y=RA;
			break;

	case 8:       if (ZCT==1)
			 StP--;
			else
			  Y=STEK[StP-1];
			break;

	case 9:         if (ZCT==0)
			  Y=D;
			break;

	case 10:        if (CC==1)
			 {
			  StP--;
			  Y=STEK[StP];
			 }
			break;

	case 11:        if (CC==1)
			 {
			  StP--;
			  Y=D;
			 }
			break;

	case 13:       if (CC==1)
			 StP--;
			else
			  Y=STEK[StP-1];
			break;

       }    /*  ��������� ��������� switch  */

      StP=StP%4;
      Y=(Y | QR);
      Y=Y&0xF;
      return(Y);   /*  ����������� � ������� ������� ������ ��������� ������������  */

		   /*  ��������� ������������ VU1  */
    }

//=====================================================================
//  ��������� �������������
//---------------------------------------------------------------------
  int TVu1::Init(string80 Array[])
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

      return(NO_ERROR);
    }

//=====================================================================
//  �������� � �������������� ���������� � ������ ��1
//---------------------------------------------------------------------
  void TVu1::LoadParam(void)
    {
      byte *_MI ;
      byte *_RE ;
      byte *_CI ;
      byte *_S0 ;
      byte *_S1 ;
      byte *_QR ;
      byte *_D  ;

      MI = StrToUnLong(_AA,0,4);
      RE = StrToUnLong(_AB,0,4);
      CI = *_C;
      S0 = *_PF0;
      S1 = *_PF3;
      QR = *_PQ0;
      D = *_PQ3;
    }

//=====================================================================
//  �������� � �������������� ���������� �� ����� ��1 ��
//  ���������� ����������
//---------------------------------------------------------------------
  void TVu1::StoreParam(void)
    {
      *_PF0 = (byte)PF0;
      *_PF3 = (byte)PF3;
      *_PQ0 = (byte)PQ0;
      *_PQ3 = (byte)PQ3;
      *_F3 = (byte)N;
      *_Z = (byte)Z;
      *_C4 = (byte)C4;
      *_OVR = (byte)V;

      UnLongToBin(DY,_DY,4*SekCount);
      //
    }

//=====================================================================
//  ��������� ������������ ��������� ������� ��������
//---------------------------------------------------------------------
  void TVu1::Show(void)
    {
    }

//=====================================================================
//  �����������
//---------------------------------------------------------------------
  TVu1::TVu1(int Number) : TModelItem(Number)
    {
      SetNumParameters(NUM_PARAM_VU1);
    }

//=====================================================================
//  ����������
//---------------------------------------------------------------------
  TVu1::~TVu1()
    {
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  ����� �������� ���������� ������� ������ TVu1
// // // // // // // // // // // // // // // // // // // // // // // //

# endif