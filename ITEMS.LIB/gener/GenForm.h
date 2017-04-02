//---------------------------------------------------------------------------
#ifndef GenFormH
#define GenFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MODEL.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGeneratorForm : public TModelForm
{
__published:	// IDE-managed Components
    TLabel *TaktLabel;
    TLabel *MikroTaktLabel;
    TLabel *NonTaktLabel;
    TLabel *SizeT1NameLabel;
    TLabel *SizeT2NameLabel;
    TLabel *KvantCountNameLabel;
    TLabel *KvantCountLabel;
    TLabel *SizeT1Label;
    TLabel *SizeT2Label;
    TLabel *NameOut1Label;
    TLabel *NameOut2Label;
    TLabel *Out2Label;
    TLabel *Out1Label;
    TBevel *PropetyBevel;
    TLabel *StartNameLabel;
    TLabel *StartLabel;
    TLabel *TotalTaktNameLabel;
    TLabel *TotalTaktLabel;
private:	// User declarations
public:		// User declarations
    __fastcall TGeneratorForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGeneratorForm *GeneratorForm;
//---------------------------------------------------------------------------
#endif
