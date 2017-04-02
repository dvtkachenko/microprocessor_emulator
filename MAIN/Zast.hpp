// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Zast.pas' rev: 3.00

#ifndef ZastHPP
#define ZastHPP
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

namespace Zast
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TZastForm;
class PASCALIMPLEMENTATION TZastForm : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Extctrls::TBevel* ZastBevel;
	Extctrls::TPanel* ZastPanel;
	Extctrls::TImage* ZastImage;
	Stdctrls::TLabel* ZastLabel1;
	Stdctrls::TLabel* ZastLabel2;
	Stdctrls::TLabel* ZastLabel3;
public:
	/* TCustomForm.Create */ __fastcall virtual TZastForm(Classes::TComponent* AOwner) : Forms::TForm(AOwner
		) { }
	/* TCustomForm.CreateNew */ __fastcall TZastForm(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(
		AOwner, Dummy) { }
	/* TCustomForm.Destroy */ __fastcall virtual ~TZastForm(void) { }
	
public:
	/* TWinControl.CreateParented */ __fastcall TZastForm(HWND ParentWindow) : Forms::TForm(ParentWindow
		) { }
	
};

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TZastForm* ZastForm;

}	/* namespace Zast */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Zast;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// Zast
