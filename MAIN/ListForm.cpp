//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ListForm.h"
#include "tscheme.hpp"
#include <string.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TListModelForm *ListModelForm;
//---------------------------------------------------------------------------
__fastcall TListModelForm::TListModelForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TListModelForm::FormCloseQuery(TObject *Sender,
      bool &CanClose)
{
  CanClose = false;     
}
//---------------------------------------------------------------------------

void __fastcall TListModelForm::ModelCheckListBoxClickCheck(
      TObject *Sender)
{
  char NumItem[30];
  char *ptr;
  int NumModelItem;
  // получаем строку из списка с номером и именем моделируемого эл-та
  strcpy(NumItem,ModelCheckListBox->Items->Strings[ModelCheckListBox->ItemIndex].c_str());
  ptr = strtok(NumItem," ");
  // извлекаем номер эл-та из строки вида -> "Dnnn"
  NumModelItem = atoi(ptr + 1);
  if(ModelCheckListBox->Checked[ModelCheckListBox->ItemIndex])
    {
      Scheme->SetWindowStateToNormal(NumModelItem);
    }
  else                                    
    {
      Scheme->SetWindowStateToMinimized(NumModelItem);
    }
}
//---------------------------------------------------------------------------

