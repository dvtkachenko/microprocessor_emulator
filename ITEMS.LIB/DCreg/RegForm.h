//---------------------------------------------------------------------------
#ifndef RegFormH
#define RegFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MODEL.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TDCregForm : public TModelForm
{
__published:	// IDE-managed Components
    TPanel *DCregPanel;
    TBevel *INBevel;
    TBevel *OutBevel;
    TLabel *InRHeaderLabel;
    TLabel *RLabel;
    TLabel *InClkHeaderLabel;
    TLabel *ClkLabel;
    TLabel *InDHeaderLabel;
    TLabel *DLabel;
    TLabel *Label3;
    TLabel *OutHeaderLabel;
    TLabel *QHeaderLabel;
    TLabel *QLabel;
private:	// User declarations
public:		// User declarations
    __fastcall TDCregForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDCregForm *DCregForm;
//---------------------------------------------------------------------------
#endif
