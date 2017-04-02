//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "thread.h"
#include "zast.hpp"
#pragma package(smart_init)

TZastavkaFhread *ZastavkaFhread;

//---------------------------------------------------------------------------
//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TZastavkaFhread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
__fastcall TZastavkaFhread::TZastavkaFhread(bool CreateSuspended)
    : TThread(CreateSuspended)
{
}

//---------------------------------------------------------------------------
void __fastcall TZastavkaFhread::CreateDestroy(void)
{
  if(Create)
    {
      ZastForm = new TZastForm((TComponent *)Application->Owner);
      ZastForm->Show();
      ZastForm->Update();
    }
  else
    {
      ZastForm->Hide();
      delete ZastForm;
    }
}

//---------------------------------------------------------------------------
void __fastcall TZastavkaFhread::Execute()
{
  //---- Place thread code here ----

  // Задержка для демонстрации заставки
  unsigned long CurTime,Delay;

  Create = CREATE_ZAST;
  Synchronize((TThreadMethod)&CreateDestroy);
  //
  CurTime = GetTickCount()/1000;
  Delay = 3; // Время задержки в секундах
  while ((GetTickCount()/1000)<(CurTime+Delay));
  //
  Create = DESTROY_ZAST;
  Synchronize((TThreadMethod)&CreateDestroy);
  Terminate();
}
//---------------------------------------------------------------------------
