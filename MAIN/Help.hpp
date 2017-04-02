// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Help.pas' rev: 3.00

#ifndef HelpHPP
#define HelpHPP
#include <ComCtrls.hpp>
#include <Tabnotbk.hpp>
#include <Tabs.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
#include <Dialogs.hpp>
#include <Forms.hpp>
#include <Controls.hpp>
#include <Graphics.hpp>
#include <Classes.hpp>
#include <Messages.hpp>
#include <Windows.hpp>
#include <SysUtils.hpp>
#include <SysInit.hpp>
#include <System.hpp>

//-- user supplied -----------------------------------------------------------

namespace Help
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS THelpForm;
class PASCALIMPLEMENTATION THelpForm : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Tabnotbk::TTabbedNotebook* HelpNotebook;
	Stdctrls::TListBox* WorkList;
	Stdctrls::TListBox* VozmList;
	Stdctrls::TListBox* MppList;
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall HelpNotebookChange(System::TObject* Sender, int NewTab, bool &AllowChange);
	void __fastcall FormKeyPress(System::TObject* Sender, char &Key);
	
public:
	bool HelpExistFlag;
public:
	/* TCustomForm.Create */ __fastcall virtual THelpForm(Classes::TComponent* AOwner) : Forms::TForm(AOwner
		) { }
	/* TCustomForm.CreateNew */ __fastcall THelpForm(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(
		AOwner, Dummy) { }
	/* TCustomForm.Destroy */ __fastcall virtual ~THelpForm(void) { }
	
public:
	/* TWinControl.CreateParented */ __fastcall THelpForm(HWND ParentWindow) : Forms::TForm(ParentWindow
		) { }
	
};

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE THelpForm* HelpForm;

}	/* namespace Help */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Help;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// Help
