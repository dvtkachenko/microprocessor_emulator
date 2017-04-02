//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "MuxForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MODEL"
#pragma link "model"
#pragma resource "*.dfm"
TMuxForm *MuxForm;
//---------------------------------------------------------------------------
__fastcall TMuxForm::TMuxForm(TComponent* Owner)
    : TModelForm(Owner)
{
}
//---------------------------------------------------------------------------
