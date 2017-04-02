# ifndef __TVU4_CPP
# define __TVU4_CPP 1

# include "TVu4.hpp"
# include "..\..\service\service.h"
# include <vcl\dstring.h>
# include <stdlib.h>
# include <alloc.h>
# include <mem.h>

// // // // // // // // // // // // // // // // // // // // // // // //
//  �������� ���������� ������� ������ TVu4 - ��� �1804��4
// // // // // // // // // // // // // // // // // // // // // // // //

//=====================================================================
//  �������� � �������������� ���������� � ������ ��4
//---------------------------------------------------------------------
  void TVu4::LoadParam(void)
    {
      char buf[ADDRESS_LEN+1];

/*      if(CheckUndefLevel(_RLD,1))
        throw UndefLevelError();
      if(CheckUndefLevel(_CC,1))
        throw UndefLevelError();
      if(CheckUndefLevel(_CCE,1))
        throw UndefLevelError();
      if(CheckUndefLevel(_CCE,1))
        throw UndefLevelError();
      if(CheckUndefLevel(_OE,1))
        throw UndefLevelError();
      if(CheckUndefLevel(_CI,1))
        throw UndefLevelError();
//      if(CheckUndefLevel(_CLK,1))
//        throw UndefLevelError();
*/
      if(CheckUndefLevel(_MI,INSTRUCTION_LEN))
        throw UndefLevelError();
//      if(CheckUndefLevel(_D,ADDRESS_LEN))
//        throw UndefLevelError();

      RLD = (dword)ConvertLevel(_RLD);
      CC = (dword)ConvertLevel(_CC);
      CCE = (dword)ConvertLevel(_CCE);
      OE = (dword)ConvertLevel(_OE);
      CI = (dword)ConvertLevel(_CI);
      CLK = (dword)ConvertLevel(_CLK);

      memcpy(buf,_MI,INSTRUCTION_LEN);
      StrRev(buf,INSTRUCTION_LEN);
      MI = StrToUnLong((char*)buf,0,INSTRUCTION_LEN);
      //
      memcpy(buf,_D,ADDRESS_LEN);
      StrRev(buf,ADDRESS_LEN);
      D = StrToUnLong((char*)buf,0,ADDRESS_LEN);
      //
    }

//=====================================================================
//  �������� � �������������� ���������� �� ����� ��4 ��
//  ���������� ����������
//---------------------------------------------------------------------
  void TVu4::StoreParam(void)
    {
      char buf[ADDRESS_LEN+1];
      int i;

      if (OE == HI_LEVEL)
    	{
    	  for(i=0;i<ADDRESS_LEN;i++)
    	    _Y[i] = (byte)(HZ | (_Y[i] & 0xF0));
    	}

      if (OE == LOW_LEVEL)
    	{
    	  if (((MI==8) || (MI==10) || (MI==13) || (MI==15)) &&
    	      (StP == 0))
    	    // � ��������� ������ �� ����� ��� StP=0 ���� Y=UNDEF_LEVEL
    	    {
    	      for(i=0;i<ADDRESS_LEN;i++)
         		_Y[i] = (byte)(UNDEF_LEVEL | (_Y[i] & 0xF0));
    	    }
    	  else
            {
              UnLongToBin(Y,(char*)buf,ADDRESS_LEN);
              StrRev(buf,ADDRESS_LEN);
    	      for(i=0;i<ADDRESS_LEN;i++)
         		_Y[i] = (byte)(buf[i] | (_Y[i] & 0xF0));
            }
    	}
      //
      *_FL = (byte)(FL | (*_FL & 0xF0));
      *_ME = (byte)(ME | (*_ME & 0xF0));
      *_PE = (byte)(PE | (*_PE & 0xF0));
      *_VE = (byte)(VE | (*_VE & 0xF0));
    }

//=====================================================================
//  ����� Run . ������������ ������������� ������� ��� �1804��4
//              � ���������� ������� �������(������)
//---------------------------------------------------------------------
  void TVu4::Run(void)
    {
      try
        {
          LoadParam();
        }
      catch(UndefLevelError e)
        {
          return;
        }

      if (CC == HI_LEVEL) CC = LOW_LEVEL;
      else CC = HI_LEVEL;

      if ((CCE==HI_LEVEL) || (CC == HI_LEVEL)) CC=HI_LEVEL; // ������� ���������

      if ((MI==2) || (MI==6)) PE=1; else PE=0;    /*  ������������  */
      if (MI==2) ME=0; else ME=1;                 /*    ��������    */
      if (MI==6) VE=0; else VE=1;                 /*    PE,ME,VE    */

      CurLevelClk = CLK;
      //--------------------------------------------------
      // ������ ������� ������������� ��� ������������� ������
      // �����������(RA,StP,STEK,CMK) � �������������(���) ������ ��4.
      // ��� �������� ,��� ���� ��� ���������� ��������� ������ CLK
      // ��� ��4 ��� ����� ����������� , ���������� � ������������
      // � �������� ���������.
      //--------------------------------------------------
      if ((PrevLevelClk == LOW_LEVEL) && (CurLevelClk == HI_LEVEL))
	  // ������������� ��������� ������������ �� ������� ���������
	  // ��������(RA,StP,STEK,CMK)
	{
	  if (((MI==4) && (CC==HI_LEVEL)) || (MI==12) || (RLD==0)) RA=D; /*  ������������ ��������  */
	  if (((MI==8) || (MI==9) || (MI==15)) && (RA!=0)) RA=(RA-1) & 0x0FFF; /*  ��������/��������    */

	  CMK=(Y+CI)&0x0FFF;  /* ��������� �������� ����������� �� ������ 4096 */

	  Y=CMK;
	  /*-----------------------------------*/
	  /*  ���������� ��������� ����������  */
	  /*-----------------------------------*/
	  switch(MI)
	   {
	    case  0: Y=0;
		     StP=0;
		     break;

	    case  1: if (CC==HI_LEVEL)
		      {
		       Y=D;
		       STEK[StP]=CMK;
		       StP++;
		      }
		     break;

	    case  2: Y=D;
		     break;

	    case  3: if (CC==HI_LEVEL)
		         Y=D;
		         break;
	    case  6: if (CC==HI_LEVEL)
		      Y=D;
		     break;

	    case  4: STEK[StP]=CMK;
		     StP++;
		     break;

	    case  5: STEK[StP]=CMK;
		     StP++;
		     if (CC==HI_LEVEL)
		      Y=D;
		     else
		      Y=RA;
		     break;

	    case  7: if (CC==HI_LEVEL)
		      Y=D;
		     else
		      Y=RA;
		     break;

	    case  8: if (RA!=0)
		      Y=STEK[StP-1];
		     else
		      StP--;
		     break;

	    case  9: if (RA!=0)
		      Y=D;
		     break;

	    case 10: if (CC==HI_LEVEL)
		      {
		       StP--;
		       Y=STEK[StP];
		      }
		     break;

	    case 11: if (CC==HI_LEVEL)
		      {
		       StP--;
		       Y=D;
		      }
		     break;

	    case 13: if (CC==HI_LEVEL)
		      StP--;
		     else
		      Y=STEK[StP-1];
		     break;

	    case 15: if (CC==LOW_LEVEL)
		      {
		       if (RA==0)
			{
			 Y=D;
			 StP--;
			}
		       else
			Y=STEK[StP-1];
		      }
		     else StP--;

	   }   /*  ��������� ��������� switch  */

	  if (StP>3)
	    {
	     FL=1;   /*  ������������ �������� ���������� �����  */
	     StP=3;
	    }
	}

      else
	 // ������������� ��������� ������������ ��� ���������� ���������
	 // ��������
	{
	  Y=CMK;
	  /*-----------------------------------*/
	  /*  ���������� ��������� ����������  */
	  /*-----------------------------------*/
	  switch(MI)
	   {
	    case  0: Y=0;
		     break;

	    case  1: if (CC==HI_LEVEL)
		      {
		       Y=D;
		      }
		     break;

	    case  2: Y=D;
		     break;

	    case  3: if (CC==HI_LEVEL)
		         Y=D;
		         break;
	    case  6: if (CC==HI_LEVEL)
		         Y=D;
		         break;

	    case  5: if (CC==HI_LEVEL)
		      Y=D;
		     else
		      Y=RA;
		     break;

	    case  7: if (CC==HI_LEVEL)
		      Y=D;
		     else
		      Y=RA;
		     break;

	    case  8: if (RA!=0)
		      Y=STEK[StP-1];
		     break;

	    case  9: if (RA!=0)
		      Y=D;
		     break;

	    case 10: if (CC==HI_LEVEL)
		      {
		       Y=STEK[StP];
		      }
		     break;

	    case 11: if (CC==HI_LEVEL)
		      {
		       Y=D;
		      }
		     break;

	    case 13: if (CC == LOW_LEVEL)
		      Y=STEK[StP-1];
		     break;

	    case 15: if (CC==LOW_LEVEL)
		      {
		       if (RA==0)
			{
			 Y=D;
			}
		       else
			Y=STEK[StP-1];
		      }

	   }   /*  ��������� ��������� switch  */

	  if (StP>3)
	    {
	     FL=1;   /*  ������������ �������� ���������� �����  */
	    }

	}

      Y=Y&0x0FFF; /*  ����������� � ������� ������� ������ ��������� ������������  */
      PrevLevelClk = CurLevelClk;

      StoreParam();
      //
    } /*  ��������� ������������ VU4  */

//=====================================================================
//  ��������� �������������
//---------------------------------------------------------------------
  int TVu4::Init(string80 Array[])
    {
      Y = 0;
      RA = 0;
      CMK = 0;
      StP = 0;
      STEK[0] = 0;
      STEK[1] = 0;
      STEK[2] = 0;
      STEK[3] = 0;
      STEK[4] = 0;

      PrevLevelClk = UNDEF_LEVEL;
      CurLevelClk = UNDEF_LEVEL;

      _RLD = &Parameters[0];
      _CC = &Parameters[1];
      _CCE = &Parameters[2];
      _PE = &Parameters[3];
      _ME = &Parameters[4];
      _VE = &Parameters[5];
      _FL = &Parameters[6];
      _OE = &Parameters[7];
      _CI = &Parameters[8];
      _CLK = &Parameters[9];
      _MI = &Parameters[10];
      _D = &Parameters[14];
      _Y = &Parameters[26];
      //
      return(MY_NO_ERROR);
    }

//=====================================================================
//  ��������� ������������� ������� ������� ���������
//---------------------------------------------------------------------
  int TVu4::InitPin(void)
    {
      int i;

      if (*_RLD & CONNECT) *_RLD = (byte)(UNDEF_LEVEL | RECEIVE | (*_RLD & 0xF0));
      else *_RLD = HI_LEVEL | RECEIVE;

      if (*_CC & CONNECT) *_CC = (byte)(UNDEF_LEVEL | RECEIVE | (*_CC & 0xF0));
      else *_CC = HI_LEVEL | RECEIVE;

      if (*_CCE & CONNECT) *_CCE = (byte)(UNDEF_LEVEL | RECEIVE | (*_CCE & 0xF0));
      else *_CCE = HI_LEVEL | RECEIVE;

      *_PE = (byte)(UNDEF_LEVEL | (*_PE & 0xF0));
      *_ME = (byte)(UNDEF_LEVEL | (*_ME & 0xF0));
      *_VE = (byte)(UNDEF_LEVEL | (*_VE & 0xF0));
      *_FL = (byte)(UNDEF_LEVEL | (*_FL & 0xF0));

      if (*_OE & CONNECT) *_OE = (byte)(UNDEF_LEVEL | RECEIVE | (*_OE & 0xF0));
      else *_OE = HI_LEVEL | RECEIVE;

      if (*_CI & CONNECT) *_CI = (byte)(UNDEF_LEVEL | RECEIVE | (*_CI & 0xF0));
      else *_CI = HI_LEVEL | RECEIVE;

      if (*_CLK & CONNECT) *_CLK = (byte)(UNDEF_LEVEL | RECEIVE | (*_CLK & 0xF0));
      else *_CLK = HI_LEVEL | RECEIVE;

      for(i=0;i<INSTRUCTION_LEN;i++)
        {
          if (_MI[i] & CONNECT)  _MI[i] = (byte)(UNDEF_LEVEL | RECEIVE | (_MI[i] & 0xF0));
          else _MI[i] = HI_LEVEL | RECEIVE;
        }
      for(i=0;i<ADDRESS_LEN;i++)
        {
          if (_D[i] & CONNECT)  _D[i] = (byte)(UNDEF_LEVEL | RECEIVE | (_D[i] & 0xF0));
          else _D[i] = HI_LEVEL | RECEIVE;
        }
      for(i=0;i<ADDRESS_LEN;i++) _Y[i] = (byte)(UNDEF_LEVEL | (_Y[i] & 0xF0));

      return(MY_NO_ERROR);
    }

//=====================================================================
//  ��������� ��������� � ��������� ���������
//---------------------------------------------------------------------
  void TVu4::Reset()
    {
      Y = 0;
      RA = 0;
      CMK = 0;
      StP = 0;
      STEK[0] = 0;
      STEK[1] = 0;
      STEK[2] = 0;
      STEK[3] = 0;
      STEK[4] = 0;

      PrevLevelClk = UNDEF_LEVEL;
      CurLevelClk = UNDEF_LEVEL;

      InitPin();
      Update();
      //
    }

//=====================================================================
//  ��������� ������������ ��������� ������� ��������
//---------------------------------------------------------------------
  void TVu4::Update(void)
    {
      char buf[ADDRESS_LEN+1];
      char symb[3];
      char *ptr;
      AnsiString temp;

      LevelToString((char)(*_RLD & 0x0F),symb);
      temp = "0123456789"; // ������ ������ ���������� ��� �������������� �����
                           // ��� 10 ��������
      ptr = temp.c_str();
      strcpy(ptr,symb);
      Vu4Form->RLDLabel->Caption = temp;
      //
      LevelToString((char)(*_CC & 0x0F),symb);
      strcpy(ptr,symb);
      Vu4Form->CCLabel->Caption = temp;
      //
      LevelToString((char)(*_CCE & 0x0F),symb);
      strcpy(ptr,symb);
      Vu4Form->CCELabel->Caption = temp;
      //
      LevelToString((char)(*_OE & 0x0F),symb);
      strcpy(ptr,symb);
      Vu4Form->OELabel->Caption = temp;
      //
      LevelToString((char)(*_CI & 0x0F),symb);
      strcpy(ptr,symb);
      Vu4Form->CILabel->Caption = temp;
      //
      LevelToString((char)(*_CLK & 0x0F),symb);
      strcpy(ptr,symb);
      Vu4Form->CLKLabel->Caption = temp;
      //
      LevelToString((char)(*_PE & 0x0F),symb);
      strcpy(ptr,symb);
      Vu4Form->PELabel->Caption = temp;
      //
      LevelToString((char)(*_ME & 0x0F),symb);
      strcpy(ptr,symb);
      Vu4Form->MELabel->Caption = temp;
      //
      LevelToString((char)(*_VE & 0x0F),symb);
      strcpy(ptr,symb);
      Vu4Form->VELabel->Caption = temp;
      //
      LevelToString((char)(*_FL & 0x0F),symb);
      strcpy(ptr,symb);
      Vu4Form->FLLabel->Caption = temp;
      //
      if(CheckUndefLevel(_MI,INSTRUCTION_LEN))
        {
          Vu4Form->MILabel->Caption = "*";
        }
      else
        {
          memcpy(buf,_MI,INSTRUCTION_LEN);
          StrRev(buf,INSTRUCTION_LEN);
          MI = StrToUnLong((char*)buf,0,INSTRUCTION_LEN);
          ultoa(MI,ptr,16);
//          CompleteString(ptr,'0',3);
          strupr(ptr);
          Vu4Form->MILabel->Caption = temp;
        }

      if(CheckUndefLevel(_D,ADDRESS_LEN))
        {
          Vu4Form->DLabel->Caption = "***";
        }
      else
        {
          memcpy(buf,_D,ADDRESS_LEN);
          StrRev(buf,ADDRESS_LEN);
          D = StrToUnLong((char*)buf,0,ADDRESS_LEN);
          ultoa(D,ptr,16);
          CompleteString(ptr,'0',3);
          strupr(ptr);
          Vu4Form->DLabel->Caption = temp;
        }
      //
      if(CheckUndefLevel(_Y,ADDRESS_LEN))
        {
          Vu4Form->YLabel->Caption = "***";
        }
      else
        {
          ultoa(Y,ptr,16);
          CompleteString(ptr,'0',3);
          strupr(ptr);
          Vu4Form->YLabel->Caption = temp;
        }
      //
      ultoa(RA,ptr,16);
      CompleteString(ptr,'0',3);
      strupr(ptr);
      Vu4Form->RALabel->Caption = temp;
      //
      ultoa(CMK,ptr,16);
      CompleteString(ptr,'0',3);
      strupr(ptr);
      Vu4Form->CMKLabel->Caption = temp;
      //
      ultoa(StP,ptr,16);
      Vu4Form->SPLabel->Caption = temp;
      //
      ultoa(STEK[0],ptr,16);
      CompleteString(ptr,'0',3);
      strupr(ptr);
      Vu4Form->Stack0Label->Caption = temp;
      //
      ultoa(STEK[1],ptr,16);
      CompleteString(ptr,'0',3);
      strupr(ptr);
      Vu4Form->Stack1Label->Caption = temp;
      //
      ultoa(STEK[2],ptr,16);
      CompleteString(ptr,'0',3);
      strupr(ptr);
      Vu4Form->Stack2Label->Caption = temp;
      //
      ultoa(STEK[3],ptr,16);
      CompleteString(ptr,'0',3);
      strupr(ptr);
      Vu4Form->Stack3Label->Caption = temp;
      //
      ultoa(STEK[4],ptr,16);
      CompleteString(ptr,'0',3);
      strupr(ptr);
      Vu4Form->Stack4Label->Caption = temp;
    }

//=====================================================================
//  �����������
//---------------------------------------------------------------------
  TVu4::TVu4(int Number,TComponent *Owner) : TModelItem(Number)
    {
      AnsiString temp(Number);

      Vu4Form = new TVu4Form(Owner);
      ModelForm = Vu4Form;
      Vu4Form->Caption = "��� �1804��4   D" + temp;
      if ((Parameters = (byte *)malloc(ALL_PIN_VU4))==NULL)
    	{
    	  Error = MY_ERROR;
    	}
      memset((void*)Parameters,0,ALL_PIN_VU4);
    }

//=====================================================================
//  ����������
//---------------------------------------------------------------------
  TVu4::~TVu4()
    {
      if (Vu4Form != NULL)
        {
	      delete Vu4Form;
	    }
    }

// // // // // // // // // // // // // // // // // // // // // // // //
//  ����� �������� ���������� ������� ������ TVu4
// // // // // // // // // // // // // // // // // // // // // // // //

# endif
