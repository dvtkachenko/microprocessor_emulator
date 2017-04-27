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
//  Преобразует двоичное число , заданное в виде символьной
//  строки ,в число типа unsigned long . При этом подразумевается
//  Str[0] - старший разряд.
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
//  Преобразует число типа unsigned long , в двоичную строку где
//  один бит представляется байтом.
//  При этом подразумевается  Str[0] - старший разряд.
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
//  Проверяет наличие в строке символов неопределенного уровня
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
//  Преобразует уровни определенные константами HI_LEVEL и LOW_LEVEL
//  в числа 1 и 0 соответственно. Данная операция необходима в некоторых
//  процедурах для обеспечения их корректной работы.
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
//  Меняет порядок символов в строке на обратный
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
//  Преобразует двоичную строку в текстовую строку двоичного вида 0->"0"
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
//  Преобразует двоичную строку в текстовую шестнадцатеричную
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
// Дополнить строку заданным символов до size длины
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



