# ifndef __LEVCONV_HPP
# define __LEVCONV_HPP 1

# include "..\..\main\const.hpp"

extern void __fastcall LevelToString(char Level,char *string);

//---------------------------------------------------------------
//  ����������� �������� ����� , �������� � ���� ����������
//  ������ ,� ����� ���� unsigned long . ��� ���� ���������������
//  Str[0] - ������� ������.
//---------------------------------------------------------------
extern dword __fastcall StrToUnLong(char *Str,int Place,int Len);

//---------------------------------------------------------------
//  ����������� ����� ���� unsigned long , � �������� ������ ���
//  ���� ��� �������������� ������.
//  ��� ���� ���������������  Str[0] - ������� ������.
//---------------------------------------------------------------
extern void __fastcall UnLongToBin(dword Value,char *Str,int BitCount);

//---------------------------------------------------------------
//  ������ ������� �������� � ������ �� ��������
//---------------------------------------------------------------
extern void __fastcall StrRev(char *Str,int Len);

//---------------------------------------------------------------
//  ��������� ������� � ������ �������� ��������������� ������
//---------------------------------------------------------------
extern bool __fastcall CheckUndefLevel(byte *Str,int Len);

//---------------------------------------------------------------
//  ����������� ������ ������������ ����������� HI_LEVEL � LOW_LEVEL
//  � ����� 1 � 0 ��������������. ������ �������� ���������� � ���������
//  ���������� ��� ����������� �� ���������� ������.
//---------------------------------------------------------------
byte _fastcall ConvertLevel(byte *Str);

//---------------------------------------------------------------
// ��������� ������ �������� �������� �� size �����
//---------------------------------------------------------------
void __fastcall CompleteString(char *src,char symb,int size);

//---------------------------------------------------------------
//  ����������� �������� ������ � ��������� ������ ��������� ���� 0->"0"
//---------------------------------------------------------------
void __fastcall BinNumToBinSymb(char *Str,int Len);

//---------------------------------------------------------------
//  ����������� �������� ������ � ��������� �����������������
//---------------------------------------------------------------
 void __fastcall BinToHex(char *BinString,int LenBin,char *HexString);

 # endif