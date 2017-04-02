//---------------------------------------------------------------------------
#ifndef AndFormH
#define AndFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MODEL.h"
#include <ExtCtrls.hpp>
#include "model.h"
//---------------------------------------------------------------------------
class TAndForm : public TModelForm
{
__published:	// IDE-managed Components
    TPanel *MuxPanel;
    TBevel *InBevel;
    TBevel *OutBevel;
    TLabel *InHeaderLabel;
    TLabel *OutHeaderLabel;
    TLabel *YHeaderLabel;
    TLabel *YLabel;
    TLabel *I3HeaderLabel;
    TLabel *I2HeaderLabel;
    TLabel *I1HeaderLabel;
    TLabel *I0HeaderLabel;
    TLabel *I3Label;
    TLabel *I2Label;
    TLabel *I1Label;
    TLabel *I0Label;
private:	// User declarations
public:		// User declarations
    __fastcall TAndForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAndForm *AndForm;
//---------------------------------------------------------------------------
#endif
