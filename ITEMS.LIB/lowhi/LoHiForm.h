//---------------------------------------------------------------------------
#ifndef LoHiFormH
#define LoHiFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MODEL.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TConstForm : public TModelForm
{
__published:	// IDE-managed Components
    TPanel *ConstPanel;
    TLabel *LowHeaderLabel;
    TLabel *HiHeaderLabel;
    TLabel *LowLabel;
    TLabel *HiLabel;
private:	// User declarations
public:		// User declarations
    __fastcall TConstForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TConstForm *ConstForm;
//---------------------------------------------------------------------------
#endif
