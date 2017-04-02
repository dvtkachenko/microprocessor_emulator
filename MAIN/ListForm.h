//---------------------------------------------------------------------------
#ifndef ListFormH
#define ListFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <checklst.hpp>
//---------------------------------------------------------------------------
class TListModelForm : public TForm
{
__published:	// IDE-managed Components
    TPanel *ListItemPanel;
    TPanel *TimePanel;
    TCheckListBox *ModelCheckListBox;
    TLabel *HeaderAbsoluteTimeLabel;
    TLabel *AbsoluteTimeLabel;
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    
    void __fastcall ModelCheckListBoxClickCheck(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TListModelForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TListModelForm *ListModelForm;
//---------------------------------------------------------------------------
#endif
