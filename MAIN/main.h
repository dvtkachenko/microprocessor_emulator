//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu;
    TOpenDialog *SchemeOpenDialog;
    TMenuItem *TuneItem;
    TMenuItem *WorkItem;
    TMenuItem *HelpItem;
    TMenuItem *ExitItem;
    TMenuItem *TuneLoadScheme;
    TMenuItem *WorkStepTrace;
    TMenuItem *WorkFullRun;
    TMenuItem *TuneEmpty;
    TMenuItem *WorkTaktLevel;
    TMenuItem *WorkMikroTaktLevel;
    TMenuItem *WorkKvantLevel;
    TMenuItem *HelpAbout;
    TMenuItem *WindowItem;
    TMenuItem *WindowCloseAll;
    TMenuItem *WindowShowAll;
    TMenuItem *N1;
    TMenuItem *TuneResetScheme;
    void __fastcall HelpAboutClick(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall ExitItemClick(TObject *Sender);
    void __fastcall TuneLoadSchemeClick(TObject *Sender);
    void __fastcall WorkKvantLevelClick(TObject *Sender);
    void __fastcall WorkMikroTaktLevelClick(TObject *Sender);
    void __fastcall WorkTaktLevelClick(TObject *Sender);
    void __fastcall WorkStepTraceClick(TObject *Sender);
    void __fastcall WorkFullRunClick(TObject *Sender);
    void __fastcall WindowCloseAllClick(TObject *Sender);
    
    void __fastcall WindowShowAllClick(TObject *Sender);
    
    void __fastcall TuneResetSchemeClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
      char PathToProgram[MAX_PATH];
    __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
