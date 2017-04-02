//---------------------------------------------------------------------------
#ifndef unnamedH
#define unnamedH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MODEL.h"
#include <ExtCtrls.hpp>
#include "model.h"
//---------------------------------------------------------------------------
class TVu4Form : public TModelForm
{
__published:	// IDE-managed Components
    TPanel *VuPanel;
    TBevel *INBevel;
    TBevel *RegBevel;
    TBevel *OutBevel;
    TLabel *INLabel;
    TLabel *RegLabel;
    TLabel *OutLabel;
    TLabel *RLDHeaderLabel;
    TLabel *CCHeaderLabel;
    TLabel *CCEHeaderLabel;
    TLabel *OEHeaderLabel;
    TLabel *CIHeaderLabel;
    TLabel *CLKHeaderLabel;
    TLabel *MIHeaderLabel;
    TLabel *DHeaderLabel;
    TLabel *RLDLabel;
    TLabel *CCLabel;
    TLabel *CCELabel;
    TLabel *OELabel;
    TLabel *CILabel;
    TLabel *CLKLabel;
    TLabel *MILabel;
    TLabel *DLabel;
    TBevel *StackBevel;
    TLabel *RAHeaderLabel;
    TLabel *CMKHeaderLabel;
    TLabel *StackLabel;
    TLabel *RALabel;
    TLabel *CMKLabel;
    TLabel *SPHeaderLabel;
    TLabel *Stack0HeaderLabel;
    TLabel *Stack1HeaderLabel;
    TLabel *Stack2HeaderLabel;
    TLabel *Stack3HeaderLabel;
    TLabel *Stack4HeaderLabel;
    TLabel *SPLabel;
    TLabel *Stack0Label;
    TLabel *Stack1Label;
    TLabel *Stack2Label;
    TLabel *Stack3Label;
    TLabel *Stack4Label;
    TLabel *PEHeaderLabel;
    TLabel *MEHeaderLabel;
    TLabel *VEHeaderLabel;
    TLabel *FLHeaderLabel;
    TLabel *YHeaderLabel;
    TLabel *PELabel;
    TLabel *MELabel;
    TLabel *VELabel;
    TLabel *FLLabel;
    TLabel *YLabel;
private:	// User declarations
public:		// User declarations
    __fastcall TVu4Form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TVu4Form *Vu4Form;
//---------------------------------------------------------------------------
#endif
