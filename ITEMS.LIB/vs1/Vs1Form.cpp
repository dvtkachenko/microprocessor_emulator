//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Vs1Form.h"
//#include "Mem_edit.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "MODEL"
#pragma link "model"
#pragma resource "*.dfm"
TVs1Form *Vs1Form;
//---------------------------------------------------------------------------
__fastcall TVs1Form::TVs1Form(TComponent* Owner)
    : TModelForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TVs1Form::R0LabelClick(TObject *Sender)
{
  //
//  InitMem_EditForChip(R0NameLabel,R0Label,RON);
}
//---------------------------------------------------------------------------

