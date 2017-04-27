//---------------------------------------------------------------------------
#ifndef PzuFormH
#define PzuFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "MODEL.h"
#include "tword.hpp"
#include <ExtCtrls.hpp>
#include "model.h"
#include <Dialogs.hpp>
#include <Menus.hpp>

//---------------------------------------------------------------------------
class TPzuForm : public TModelForm
{
__published:	// IDE-managed Components
    TPanel *PzuPanel;
    TBevel *InBevel;
    TBevel *MemBevel;
    TLabel *InLabel;
    TLabel *MemLabel;
    TLabel *Adr0Label;
    TLabel *Adr1Label;
    TLabel *Adr2Label;
    TLabel *Adr3Label;
    TLabel *Adr4Label;
    TLabel *Adr5Label;
    TLabel *Adr6Label;
    TLabel *Adr7Label;
    TLabel *Adr8Label;
    TLabel *Adr9Label;
    TLabel *Adr10Label;
    TLabel *AdrHeaderLabel;
    TLabel *InAdrHeaderLabel;
    TLabel *InAdrLabel;
    TLabel *InREHeaderLabel;
    TLabel *RELabel;
    TLabel *Mem0Label;
    TScrollBar *MemScrollBar;
    TLabel *OutHeaderLabel;
    TBevel *Bevel1;
    TLabel *OutDataLabel;
    TLabel *Mem1Label;
    TLabel *Mem2Label;
    TLabel *Mem3Label;
    TLabel *Mem4Label;
    TLabel *Mem5Label;
    TLabel *Mem6Label;
    TLabel *Mem7Label;
    TLabel *Mem8Label;
    TLabel *Mem9Label;
    TLabel *Mem10Label;
    TOpenDialog *MemLoadOpenDialog;
    TPopupMenu *PzuPopupMenu;
    TMenuItem *LoadItem;
    void __fastcall MemScrollBarChange(TObject *Sender);
    
    void __fastcall LoadItemClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    //
    TWord **Memory;
    int WordLength;
    int MemSize;

    int CurrentAddress;   // адрес текущей строки памяти
    int TopAddress;       // адрес верхней видимой в окне строки памяти
    bool UndefAddressFlag;
    //
    void __fastcall ShowAdrLabel(void);
    void __fastcall ShowMemory(void);
    void __fastcall ReadMemFromFile(char *FileName);
    __fastcall TPzuForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPzuForm *PzuForm;
//---------------------------------------------------------------------------
#endif
