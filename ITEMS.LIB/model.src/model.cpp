//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "model.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TModelForm *ModelForm;
//---------------------------------------------------------------------------
__fastcall TModelForm::TModelForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
 