//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "EntForm.h"
#include "stdlib.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEnterForm *EnterForm;
//---------------------------------------------------------------------------
__fastcall TEnterForm::TEnterForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TEnterForm::EditBoxKeyPress(TObject *Sender, char &Key)
{
//  if(Key == 0x13)
  if((Key < 0x30) || (Key > 0x39))
    {
      Key = 0x00;
    }
}
//---------------------------------------------------------------------------

