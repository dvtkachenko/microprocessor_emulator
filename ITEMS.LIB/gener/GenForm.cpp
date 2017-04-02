//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "GenForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MODEL"
#pragma resource "*.dfm"
TGeneratorForm *GeneratorForm;
//---------------------------------------------------------------------------
__fastcall TGeneratorForm::TGeneratorForm(TComponent* Owner)
    : TModelForm(Owner)
{
}
//---------------------------------------------------------------------------
