// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Mem_edit.pas' rev: 3.00

#ifndef Mem_editHPP
#define Mem_editHPP
#include <Mask.hpp>
#include <Buttons.hpp>
#include "Des.hpp"
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

namespace Mem_edit
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TMem_EditForm;
class PASCALIMPLEMENTATION TMem_EditForm : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TButton* OkButtonEditMem;
	Stdctrls::TButton* CancelButtonEditMem;
	Stdctrls::TEdit* MaskEditMem;
	Stdctrls::TLabel* MemoryEditLabel;
	void __fastcall OkButtonEditMemClick(System::TObject* Sender);
	void __fastcall CancelButtonEditMemClick(System::TObject* Sender);
	void __fastcall FormKeyPress(System::TObject* Sender, char &Key);
	void __fastcall FormCloseQuery(System::TObject* Sender, bool &CanClose);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall InitMem_EditForChip(Stdctrls::TLabel* &InLabel, Stdctrls::TLabel* &NameLabel, int &
		OutRezult, int MaxValue);
public:
	/* TCustomForm.Create */ __fastcall virtual TMem_EditForm(Classes::TComponent* AOwner) : Forms::TForm(
		AOwner) { }
	/* TCustomForm.CreateNew */ __fastcall TMem_EditForm(Classes::TComponent* AOwner, int Dummy) : Forms::
		TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ __fastcall virtual ~TMem_EditForm(void) { }
	
public:
	/* TWinControl.CreateParented */ __fastcall TMem_EditForm(HWND ParentWindow) : Forms::TForm(ParentWindow
		) { }
	
};

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TMem_EditForm* Mem_EditForm;
extern PACKAGE System::AnsiString Buffer;

}	/* namespace Mem_edit */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Mem_edit;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// Mem_edit
