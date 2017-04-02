//---------------------------------------------------------------------------
#ifndef EntFormH
#define EntFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TEnterForm : public TForm
{
__published:	// IDE-managed Components
    TLabel *HeaderLabel;
    TEdit *EditBox;
    TButton *OkButton;
    TButton *CancelButton;
    TLabel *TKLabel;
    void __fastcall EditBoxKeyPress(TObject *Sender, char &Key);
    
    
private:	// User declarations
public:		// User declarations
    __fastcall TEnterForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEnterForm *EnterForm;
//---------------------------------------------------------------------------
#endif
