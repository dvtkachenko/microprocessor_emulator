//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "GoiForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MODEL"
#pragma resource "*.dfm"
TGoiForm *GoiForm;
//---------------------------------------------------------------------------
__fastcall TGoiForm::TGoiForm(TComponent* Owner)
    : TModelForm(Owner)
{
}
//---------------------------------------------------------------------------
