//---------------------------------------------------------------------------
#include <vcl.h>
#include "Zast.hpp"
#include "Black.hpp"
#include "tscheme.hpp"
#include "thread.h"
#include "trun.hpp"
#include "ListForm.h"
#pragma hdrstop
USERES("emulator.res");
USEFORM("MAIN\main.cpp", MainForm);
USEFORMNS("MAIN\About.pas", About, AboutForm);
USEFORMNS("MAIN\Zast.pas", Zast, ZastForm);
USEFORMNS("MAIN\Exit_que.pas", Exit_que, Exit_queForm);
USEFORMNS("MAIN\Help.pas", Help, HelpForm);
USEUNIT("MAIN\TLink.cpp");
USEUNIT("MAIN\tbus.cpp");
USEUNIT("MAIN\Ttrans.cpp");
USEUNIT("MAIN\Tscheme.cpp");
USEUNIT("MAIN\Trun.cpp");
USEFORM("SERVICE\EntForm.cpp", EnterForm);
USEUNIT("MAIN\thread.cpp");
USEUNIT("service\TQueue.cpp");
USEFORM("MAIN\ListForm.cpp", ListModelForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

    try
    {
      try
       {
        ZastavkaFhread = new TZastavkaFhread(false);
        Application->Initialize();
        Application->Title = "Эмулятор ЭВМ";
        Application->CreateForm(__classid(TMainForm), &MainForm);
        Application->CreateForm(__classid(TAboutForm), &AboutForm);
        Application->CreateForm(__classid(TExit_queForm), &Exit_queForm);
        Application->CreateForm(__classid(THelpForm), &HelpForm);
        Application->CreateForm(__classid(TEnterForm), &EnterForm);
        RunScheme = NULL;
        Scheme = NULL;
        ListModelForm = NULL;
//        RunScheme = new TRun();
        //
        Application->Run();
       }
       __finally
       {
        delete ZastavkaFhread;
        if(RunScheme != NULL) delete RunScheme;
        if(Scheme != NULL) delete Scheme;
        if(ListModelForm != NULL) delete ListModelForm;
       }

    }

    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
