//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "RegForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MODEL"
#pragma resource "*.dfm"
TDCregForm *DCregForm;
//---------------------------------------------------------------------------
__fastcall TDCregForm::TDCregForm(TComponent* Owner)
    : TModelForm(Owner)
{
}
//---------------------------------------------------------------------------
