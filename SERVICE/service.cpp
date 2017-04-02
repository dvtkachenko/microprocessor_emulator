# include "..\..\main\const.hpp"
# include <string.h>
# include <stdlib.h>

/////////////////////////////////////////////////////////////////

void __fastcall LevelToString(char Level,char *string)
    {
      string[1] = 0;
      switch(Level & 0x0F)
    	{
    	  case  LOW_LEVEL   : string[0] = '0' ;break;
    	  case	HI_LEVEL    : string[0] = '1' ;break;
    	  case	HZ          : string[0] = 'Z';
    			      string[1] =  0 ;break;

    	  case	UNDEF_LEVEL : string[0] = '*';break;
    	}
    }

//---------------------------------------------------------------
//  ����������� �������� ����� , �������� � ���� ����������
//  ������ ,� ����� ���� unsigned long . ��� ���� ���������������
//  Str[0] - ������� ������.
//---------------------------------------------------------------
dword __fastcall StrToUnLong(char *Str,int Place,int Len)
    {
      int Ves=1,OutSum=0,i;

      for (i=Place+Len-1;i>=Place;i--)
    	{
    	  if ((Str[i] & 0x0F) == HI_LEVEL) OutSum = OutSum + Ves;

    	  if (i != Place) Ves = Ves*2;
    	}

      return OutSum;
    }

//---------------------------------------------------------------
//  ����������� ����� ���� unsigned long , � �������� ������ ���
//  ���� ��� �������������� ������.
//  ��� ���� ���������������  Str[0] - ������� ������.
//---------------------------------------------------------------
void __fastcall UnLongToBin(dword Value,char *Str,int BitCount)
    {
      dword Mask = 0x00000001;
      int i;

      for(i=BitCount-1;i>=0;i--)
    	{
    	  if (Value & Mask)
    	    {
    	      Str[i] = 1;       //  Str[i] = HI_LEVEL
    	    }
    	  else
    	    {
    	      Str[i] = 0;       //  Str[i] = LOW_LEVEL
    	    }

          Value = Value >> 1;
    	}
    }

//---------------------------------------------------------------
//  ��������� ������� � ������ �������� ��������������� ������
//---------------------------------------------------------------
bool __fastcall CheckUndefLevel(byte *Str,int Len)
    {
      byte i;
      bool result=false;

      for(i=0;i<Len;i++)
    	{
    	  if ((Str[i]& 0x0F) == UNDEF_LEVEL) result = true;
    	}
      return result;
    }

//---------------------------------------------------------------
//  ����������� ������ ������������ ����������� HI_LEVEL � LOW_LEVEL
//  � ����� 1 � 0 ��������������. ������ �������� ���������� � ���������
//  ���������� ��� ����������� �� ���������� ������.
//---------------------------------------------------------------
byte __fastcall ConvertLevel(byte *Str)
    {
      byte result=0;

      if((*Str & 0x0F)== LOW_LEVEL)
    	result = 0;
      else
    	result = 1;

      return result;
    }

//---------------------------------------------------------------
//  ������ ������� �������� � ������ �� ��������
//---------------------------------------------------------------
void __fastcall StrRev(char *Str,int Len)
    {
      int i;

      for(i=0;i<Len;i++) Str[i] += (char)0x30;
      //
      Str[i] = 0;
      strrev(Str);
      //
      for(i=0;i<Len;i++) Str[i] -= (char)0x30;
    }

//---------------------------------------------------------------
//  ����������� �������� ������ � ��������� ������ ��������� ���� 0->"0"
//---------------------------------------------------------------
void __fastcall BinNumToBinSymb(char *Str,int Len)
    {
      byte i;
      char symb[3];
      for(i=0;i<Len;i++)
    	{
    	  LevelToString(Str[i],symb);
    	  Str[i] = symb[0];
    	}
      Str[i] = 0;
    }

//---------------------------------------------------------------
//  ����������� �������� ������ � ��������� �����������������
//---------------------------------------------------------------
 void __fastcall BinToHex(char *BinString,int LenBin,char *HexString)
   {
     char BufString[255],buf[3];
     int i,n;

     memcpy(BufString,BinString,LenBin);
     n = LenBin%4;
     for(i=0;i<n;i++) BufString[LenBin++] = 0;

     n = LenBin/4;
     if(CheckUndefLevel((byte*)BinString,LenBin))
       {
         memset(HexString,'*',n);
         HexString[n] = 0;
         return;
       }

     for(i=0;i<n;i++)
       {
         ultoa(StrToUnLong(BufString,i<<2,4),buf,16);
         HexString[i] = buf[0];
       }
     HexString[i] = 0;
     strupr(HexString);
   }

//---------------------------------------------------------------
// ��������� ������ �������� �������� �� size �����
//---------------------------------------------------------------
void __fastcall CompleteString(char *src,char symb,int size)
    {
      int len;
      char buf[2];

      buf[0] = symb;
      buf[1] = 0;

      len = (int)strlen(src);
      if (len < size)
    	{
    	  len = size - len;
    	  strrev(src);
    	  for(int i=0;i<len;i++)
    	    strcat(src,buf);
    	  strrev(src);
    	}
    }



