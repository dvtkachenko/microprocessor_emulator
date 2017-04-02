//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Vu4Form.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MODEL"
#pragma link "model"
#pragma resource "*.dfm"
TVu4Form *Vu4Form;
//---------------------------------------------------------------------------
__fastcall TVu4Form::TVu4Form(TComponent* Owner)
    : TModelForm(Owner)
{
}
//---------------------------------------------------------------------------
