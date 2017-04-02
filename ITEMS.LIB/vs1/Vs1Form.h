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
class TVs1Form : public TModelForm
{
__published:	// IDE-managed Components
    TPanel *VuPanel;
    TBevel *INBevel;
    TBevel *RegBevel;
    TBevel *OutBevel;
    TLabel *INLabel;
    TLabel *RegLabel;
    TLabel *OutLabel;
    TLabel *AANameLabel;
    TLabel *KONameLabel;
    TLabel *PF3NameLabel;
    TLabel *PF0NameLabel;
    TLabel *KINameLabel;
    TLabel *CLKNameLabel;
    TLabel *PQ3NameLabel;
    TLabel *DANameLabel;
    TLabel *AALabel;
    TLabel *KOLabel;
    TLabel *PF3Label;
    TLabel *PF0Label;
    TLabel *KILabel;
    TLabel *CLKLabel;
    TLabel *PQ3Label;
    TLabel *DALabel;
    TLabel *R0NameLabel;
    TLabel *R1NameLabel;
    TLabel *R2NameLabel;
    TLabel *R3NameLabel;
    TLabel *R4NameLabel;
    TLabel *R0Label;
    TLabel *ZNameLabel;
    TLabel *F3NameLabel;
    TLabel *C4NameLabel;
    TLabel *OVRNameLabel;
    TLabel *YHeaderLabel;
    TLabel *ZLabel;
    TLabel *F3Label;
    TLabel *C4Label;
    TLabel *OVRLabel;
    TLabel *YLabel;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *ABNameLabel;
    TLabel *ABLabel;
    TLabel *PQ0NameLabel;
    TLabel *PQ0Label;
    TLabel *OBNameLabel;
    TLabel *OPLabel;
    TLabel *Label9;
    TLabel *Label10;
    TLabel *C0NameLabel;
    TLabel *C0Label;
    TLabel *OPNameLabel;
    TLabel *OELabel;
    TLabel *R1Label;
    TLabel *R2Label;
    TLabel *R3Label;
    TLabel *R4Label;
    TLabel *R5NameLabel;
    TLabel *R5Label;
    TLabel *R6NameLabel;
    TLabel *R6Label;
    TLabel *R7NameLabel;
    TLabel *R7Label;
    TLabel *R8NameLabel;
    TLabel *R8Label;
    TLabel *R9NameLabel;
    TLabel *R9Label;
    TLabel *R10NameLabel;
    TLabel *R10Label;
    TLabel *R11NameLabel;
    TLabel *R11Label;
    TLabel *R12NameLabel;
    TLabel *R12Label;
    TLabel *R13NameLabel;
    TLabel *R13Label;
    TLabel *R14NameLabel;
    TLabel *R14Label;
    TLabel *R15NameLabel;
    TLabel *R15Label;
    TLabel *RgANameLabel;
    TLabel *RgALabel;
    TLabel *RgBNameLabel;
    TLabel *RgBLabel;
    TLabel *RQNameLabel;
    TLabel *RQLabel;
    void __fastcall R0LabelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TVs1Form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TVs1Form *Vs1Form;
//---------------------------------------------------------------------------
#endif
