//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "PzuForm.h"
#include "..\..\service\service.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MODEL"
#pragma link "model"
#pragma resource "*.dfm"
TPzuForm *PzuForm;
//---------------------------------------------------------------------------
__fastcall TPzuForm::TPzuForm(TComponent* Owner)
    : TModelForm(Owner)
{
}

//=====================================================================
//  Процедура визуализации содержимого памяти ПЗУ
//---------------------------------------------------------------------
void __fastcall TPzuForm::ShowAdrLabel(void)
    {
      char *ptr;
      AnsiString temp;
      // данная строка необходима для резервирования места
      // под 10 символов
      temp = "0123456789";

      ptr = temp.c_str();
      //
      ultoa(TopAddress,ptr,16);
      CompleteString(ptr,'0',3);
      strupr(ptr);
      Adr0Label->Caption = temp;
      //
      ultoa(TopAddress+1,ptr,16);
      CompleteString(ptr,'0',3);
      strupr(ptr);
      Adr1Label->Caption = temp;
      //
      ultoa(TopAddress+2,ptr,16);
      CompleteString(ptr,'0',3);
      strupr(ptr);
      Adr2Label->Caption = temp;
      //
      ultoa(TopAddress+3,ptr,16);
      CompleteString(ptr,'0',3);
      strupr(ptr);
      Adr3Label->Caption = temp;
      //
      ultoa(TopAddress+4,ptr,16);
      CompleteString(ptr,'0',3);
      strupr(ptr);
      Adr4Label->Caption = temp;
      //
      ultoa(TopAddress+5,ptr,16);
      CompleteString(ptr,'0',3);
      strupr(ptr);
      Adr5Label->Caption = temp;
      //
      ultoa(TopAddress+6,ptr,16);
      CompleteString(ptr,'0',3);
      strupr(ptr);
      Adr6Label->Caption = temp;
      //
      ultoa(TopAddress+7,ptr,16);
      CompleteString(ptr,'0',3);
      strupr(ptr);
      Adr7Label->Caption = temp;
      //
      ultoa(TopAddress+8,ptr,16);
      CompleteString(ptr,'0',3);
      strupr(ptr);
      Adr8Label->Caption = temp;
      //
      ultoa(TopAddress+9,ptr,16);
      CompleteString(ptr,'0',3);
      strupr(ptr);
      Adr9Label->Caption = temp;
      //
      ultoa(TopAddress+10,ptr,16);
      CompleteString(ptr,'0',3);
      strupr(ptr);
      Adr10Label->Caption = temp;
    }

//=====================================================================
//  Процедура обновления содержимого памяти ПЗУ на экране
//---------------------------------------------------------------------
  void __fastcall TPzuForm::ShowMemory()
    {
      char *ptr;
      byte MemString[255];
      AnsiString temp;
      // данная строка необходима для резервирования места
      // под 60 символов
      temp = "012345678901234567890123456789012345678901234567890123456789";
      //
      ptr = temp.c_str();

      Memory[TopAddress]->Read(MemString);
      BinToHex((char*)MemString,WordLength,ptr);
      Mem0Label->Caption = temp;
      //
      Memory[TopAddress+1]->Read(MemString);
      BinToHex((char*)MemString,WordLength,ptr);
      Mem1Label->Caption = temp;
      //
      Memory[TopAddress+2]->Read(MemString);
      BinToHex((char*)MemString,WordLength,ptr);
      Mem2Label->Caption = temp;
      //
      Memory[TopAddress+3]->Read(MemString);
      BinToHex((char*)MemString,WordLength,ptr);
      Mem3Label->Caption = temp;
      //
      Memory[TopAddress+4]->Read(MemString);
      BinToHex((char*)MemString,WordLength,ptr);
      Mem4Label->Caption = temp;
      //
      Memory[TopAddress+5]->Read(MemString);
      BinToHex((char*)MemString,WordLength,ptr);
      Mem5Label->Caption = temp;
      //
      Memory[TopAddress+6]->Read(MemString);
      BinToHex((char*)MemString,WordLength,ptr);
      Mem6Label->Caption = temp;
      //
      Memory[TopAddress+7]->Read(MemString);
      BinToHex((char*)MemString,WordLength,ptr);
      Mem7Label->Caption = temp;
      //
      Memory[TopAddress+8]->Read(MemString);
      BinToHex((char*)MemString,WordLength,ptr);
      Mem8Label->Caption = temp;
      //
      Memory[TopAddress+9]->Read(MemString);
      BinToHex((char*)MemString,WordLength,ptr);
      Mem9Label->Caption = temp;
      //
      Memory[TopAddress+10]->Read(MemString);
      BinToHex((char*)MemString,WordLength,ptr);
      Mem10Label->Caption = temp;
    }


//---------------------------------------------------------------------------

void __fastcall TPzuForm::MemScrollBarChange(TObject *Sender)
{
  TopAddress = MemScrollBar->Position;
  ShowAdrLabel();
  ShowMemory();
}

//=====================================================================
//  Процедура чтения содержимого памяти ПЗУ из файла
//---------------------------------------------------------------------
  void __fastcall TPzuForm::ReadMemFromFile(char *FileName)
    {
      FILE *fp;

//      int Error;
      int i,Address;
      byte buf[129+40];

//      Error = MY_NO_ERROR;

      memset(buf,0,129+40);
      fp = fopen(FileName,"rt");
      if (fp == NULL)
    	{
//	      Error = MY_ERROR;
    	  return;
    	}
      //
      Address = 0;
      while((fgets((char*)buf,WordLength+40,fp) != NULL) && (Address != MemSize))
    	{
    	  for(i=0;i<WordLength;i++)
            {
              if ((buf[i] == '0') || (buf[i] == '1'))
                buf[i] -= (byte)0x30;
              else
                buf[i] = 0;
            }
    	  Memory[Address]->Write(buf);
    	  Address++;
    	}
      //
      fclose(fp);
    }

//---------------------------------------------------------------------------


void __fastcall TPzuForm::LoadItemClick(TObject *Sender)
{
  if (MemLoadOpenDialog->Execute())
    {
      ReadMemFromFile(MemLoadOpenDialog->FileName.c_str());
      ShowAdrLabel();
      ShowMemory();
    }
}
//---------------------------------------------------------------------------

