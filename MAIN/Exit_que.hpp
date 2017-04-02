// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Exit_que.pas' rev: 3.00

#ifndef Exit_queHPP
#define Exit_queHPP
#include <Buttons.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>
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

namespace Exit_que
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TExit_queForm;
class PASCALIMPLEMENTATION TExit_queForm : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TLabel* ExitLabel1;
	Extctrls::TImage* ExitImage;
	Stdctrls::TLabel* NameLabel;
	Buttons::TBitBtn* YesButton;
	Buttons::TBitBtn* NoButton;
	void __fastcall YesButtonClick(System::TObject* Sender);
	void __fastcall NoButtonClick(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	
public:
	bool CloseFlag;
	System::AnsiString NameClose1;
	System::AnsiString NameClose2;
public:
	/* TCustomForm.Create */ __fastcall virtual TExit_queForm(Classes::TComponent* AOwner) : Forms::TForm(
		AOwner) { }
	/* TCustomForm.CreateNew */ __fastcall TExit_queForm(Classes::TComponent* AOwner, int Dummy) : Forms::
		TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ __fastcall virtual ~TExit_queForm(void) { }
	
public:
	/* TWinControl.CreateParented */ __fastcall TExit_queForm(HWND ParentWindow) : Forms::TForm(ParentWindow
		) { }
	
};

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TExit_queForm* Exit_queForm;

}	/* namespace Exit_que */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Exit_que;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// Exit_que
