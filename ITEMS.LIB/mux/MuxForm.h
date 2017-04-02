//---------------------------------------------------------------------------
#ifndef MuxFormH
#define MuxFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MODEL.h"
#include <ExtCtrls.hpp>
#include "model.h"
//---------------------------------------------------------------------------
class TMuxForm : public TModelForm
{
__published:	// IDE-managed Components
    TPanel *MuxPanel;
    TBevel *InBevel;
    TBevel *OutBevel;
    TLabel *InHeaderLabel;
    TLabel *OutHeaderLabel;
    TLabel *YHeaderLabel;
    TLabel *YLabel;
    TLabel *I0HeaderLabel;
    TLabel *I1HeaderLabel;
    TLabel *I2HeaderLabel;
    TLabel *I3HeaderLabel;
    TLabel *I0Label;
    TLabel *I1Label;
    TLabel *I2Label;
    TLabel *I3Label;
    TLabel *S1HeaderLabel;
    TLabel *S0HeaderLabel;
    TLabel *S1Label;
    TLabel *S0Label;
private:	// User declarations
public:		// User declarations
    __fastcall TMuxForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMuxForm *MuxForm;
//---------------------------------------------------------------------------
#endif
