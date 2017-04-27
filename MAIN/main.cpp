//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "exit_que.hpp"
#include "about.hpp"
#include "tscheme.hpp"
#include "trun.hpp"
#include "EntForm.h"
#include "ListForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
  getcwd(PathToProgram,MAXPATH);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::HelpAboutClick(TObject *Sender)
{
  AboutForm->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  Exit_queForm->NameClose1 = "Вы действительно хотите закрыть";
  Exit_queForm->NameClose2 = " Программу-эмулятор";
  Exit_queForm->ShowModal();
  CanClose = Exit_queForm->CloseFlag;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ExitItemClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TuneLoadSchemeClick(TObject *Sender)
{
  if(SchemeOpenDialog->Execute())
    {
        try
          {
            if(Scheme != NULL) delete Scheme;
            if(RunScheme != NULL) delete RunScheme;
            if(ListModelForm != NULL) delete ListModelForm;
            //
            RunScheme = new TRun();
            Scheme = new TScheme(SchemeOpenDialog->FileName.c_str());
            ListModelForm = new TListModelForm(Application);
            Scheme->Create();
            RunScheme->SetScheme(Scheme);
            //
            ListModelForm->Show();
            WindowCloseAllClick(Sender);
            Scheme->Show();
            //
            WorkTaktLevel->Checked = false;
            WorkMikroTaktLevel->Checked = false;
            WorkKvantLevel->Checked = true;
            RunScheme->SetTraceLevel(KVANT_LEVEL);
          }
        catch(const char *exception)
          {
            if(Scheme != NULL) delete Scheme;
            MessageDlg(exception, mtError,TMsgDlgButtons() << mbOK , 0);
            throw exception;
          }

        WorkItem->Enabled = true;  
        TuneResetScheme->Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::WorkKvantLevelClick(TObject *Sender)
{
  RunScheme->SetTraceLevel(KVANT_LEVEL);
  WorkKvantLevel->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::WorkMikroTaktLevelClick(TObject *Sender)
{
  RunScheme->SetTraceLevel(MIKROTAKT_LEVEL);
  WorkMikroTaktLevel->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::WorkTaktLevelClick(TObject *Sender)
{
  RunScheme->SetTraceLevel(TAKT_LEVEL);
  WorkTaktLevel->Checked = true;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::WorkStepTraceClick(TObject *Sender)
{
  RunScheme->Run();
  Scheme->Update();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::WorkFullRunClick(TObject *Sender)
{
  tagMSG lpMSG;
  long i,Len;

  switch(RunScheme->GetTraceLevel())
    {
      case KVANT_LEVEL : EnterForm->TKLabel->Caption = "(в квантах)";break;
      case MIKROTAKT_LEVEL : EnterForm->TKLabel->Caption = "(в микротактах)";break;
      case TAKT_LEVEL : EnterForm->TKLabel->Caption = "(в тактах)";break;
    }

  if(EnterForm->ShowModal() == mrOk)
    {
      Len = atol(EnterForm->EditBox->Text.c_str());

      try
        {
          for(i=0;i<Len;i++)
            {
              if(PeekMessage(&lpMSG,NULL,0,0,PM_REMOVE))
                {
                  if(lpMSG.wParam == VK_ESCAPE)
                    {
                      throw "Моделирование прервано";
                    }
                }
              RunScheme->Run();
            }
        }
      catch(const char *message)
        {
          Scheme->Update();
          MessageDlg("Моделирование было прервано"
                     " по желанию пользователя", mtInformation,
                       TMsgDlgButtons() << mbOK , 0);
        }
    }
  Scheme->Update();
//  MessageDlg("Моделирование завершено", mtConfirmation,
//             TMsgDlgButtons() << mbOK , 0);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::WindowCloseAllClick(TObject *Sender)
{
  for(int i = 0; i < MDIChildCount; i++)
    {
      MDIChildren[i]->Enabled = false;
      MDIChildren[i]->WindowState = wsMinimized;
    }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::WindowShowAllClick(TObject *Sender)
{
  for(int i = 0; i < MDIChildCount; i++)
    {
      MDIChildren[i]->Enabled = true;
      MDIChildren[i]->WindowState = wsNormal;
    }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::TuneResetSchemeClick(TObject *Sender)
{
  Exit_queForm->NameClose1 = "Вы действительно хотите установить";
  Exit_queForm->NameClose2 = " моделируемую схему в начальное состояние";
  Exit_queForm->ShowModal();
  if (Exit_queForm->CloseFlag)
    {
      Scheme->Reset();
      Scheme->Update();
    }  
}
//---------------------------------------------------------------------------

