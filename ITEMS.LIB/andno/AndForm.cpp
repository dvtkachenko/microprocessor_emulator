//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AndForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MODEL"
#pragma link "model"
#pragma resource "*.dfm"
TAndNoForm *AndNoForm;
//---------------------------------------------------------------------------
__fastcall TAndNoForm::TAndNoForm(TComponent* Owner)
    : TModelForm(Owner)
{
}
//---------------------------------------------------------------------------
