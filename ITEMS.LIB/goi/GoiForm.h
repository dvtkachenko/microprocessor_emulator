//---------------------------------------------------------------------------
#ifndef _GoiFormH
#define _GoiFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MODEL.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGoiForm : public TModelForm
{
__published:	// IDE-managed Components
    TLabel *TaktLabel;
    TLabel *LenClkNameLabel;
    TLabel *KvantCountNameLabel;
    TLabel *KvantCountLabel;
    TLabel *LenClkLabel;
    TLabel *NameOut1Label;
    TLabel *Out1Label;
    TBevel *PropetyBevel;
    TLabel *StartNameLabel;
    TLabel *StartLabel;
private:	// User declarations
public:		// User declarations
    __fastcall TGoiForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGoiForm *GoiForm;
//---------------------------------------------------------------------------
#endif
