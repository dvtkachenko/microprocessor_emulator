//---------------------------------------------------------------------------
#ifndef modelH
#define modelH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TModelForm : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
    __fastcall TModelForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TModelForm *ModelForm;
//---------------------------------------------------------------------------
#endif
 