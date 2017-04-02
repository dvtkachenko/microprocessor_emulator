//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AndForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MODEL"
#pragma link "model"
#pragma resource "*.dfm"
TAndForm *AndForm;
//---------------------------------------------------------------------------
__fastcall TAndForm::TAndForm(TComponent* Owner)
    : TModelForm(Owner)
{
}
//---------------------------------------------------------------------------
