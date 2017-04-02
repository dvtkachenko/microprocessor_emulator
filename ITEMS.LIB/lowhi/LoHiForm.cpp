//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "LoHiForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MODEL"
#pragma resource "*.dfm"
TConstForm *ConstForm;
//---------------------------------------------------------------------------
__fastcall TConstForm::TConstForm(TComponent* Owner)
    : TModelForm(Owner)
{
}
//---------------------------------------------------------------------------
