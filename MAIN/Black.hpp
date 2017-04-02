// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Black.pas' rev: 3.00

#ifndef BlackHPP
#define BlackHPP
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

namespace Black
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TBlackForm;
class PASCALIMPLEMENTATION TBlackForm : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
public:
	/* TCustomForm.Create */ __fastcall virtual TBlackForm(Classes::TComponent* AOwner) : Forms::TForm(
		AOwner) { }
	/* TCustomForm.CreateNew */ __fastcall TBlackForm(Classes::TComponent* AOwner, int Dummy) : Forms::
		TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ __fastcall virtual ~TBlackForm(void) { }
	
public:
	/* TWinControl.CreateParented */ __fastcall TBlackForm(HWND ParentWindow) : Forms::TForm(ParentWindow
		) { }
	
};

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TBlackForm* BlackForm;

}	/* namespace Black */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Black;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// Black
