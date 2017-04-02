// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'About.pas' rev: 3.00

#ifndef AboutHPP
#define AboutHPP
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

namespace About
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TAboutForm;
class PASCALIMPLEMENTATION TAboutForm : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Extctrls::TPanel* AboutPanel;
	Stdctrls::TLabel* EmuLabel;
	Stdctrls::TLabel* NameLabel;
	Buttons::TBitBtn* OkBitBtn;
	Stdctrls::TLabel* VersionLabel;
	Extctrls::TImage* Image1;
	Stdctrls::TLabel* EvmLabel;
	void __fastcall OkBitBtnClick(System::TObject* Sender);
public:
	/* TCustomForm.Create */ __fastcall virtual TAboutForm(Classes::TComponent* AOwner) : Forms::TForm(
		AOwner) { }
	/* TCustomForm.CreateNew */ __fastcall TAboutForm(Classes::TComponent* AOwner, int Dummy) : Forms::
		TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ __fastcall virtual ~TAboutForm(void) { }
	
public:
	/* TWinControl.CreateParented */ __fastcall TAboutForm(HWND ParentWindow) : Forms::TForm(ParentWindow
		) { }
	
};

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TAboutForm* AboutForm;

}	/* namespace About */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace About;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// About
