unit Exit_que;

interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, ExtCtrls, StdCtrls, Buttons;

type
  TExit_queForm = class(TForm)
    ExitLabel1: TLabel;
    ExitImage: TImage;
    NameLabel: TLabel;
    YesButton: TBitBtn;
    NoButton: TBitBtn;
    procedure YesButtonClick(Sender: TObject);
    procedure NoButtonClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
  private
    { Private declarations }
  public
    CloseFlag:Boolean;
    NameClose1:string;
    NameClose2:string;
    { Public declarations }
  end;

var
  Exit_queForm: TExit_queForm;

implementation

{$R *.DFM}

procedure TExit_queForm.FormShow(Sender: TObject);
{ Формирование сообщений запроса }
begin
  ExitLabel1.Caption:=NameClose1;
  NameLabel .Caption:=NameClose2;
end;

procedure TExit_queForm.YesButtonClick(Sender: TObject);
{ Разрешение закрытия окна }
begin
  CloseFlag:=True;
  Close;
end;

procedure TExit_queForm.NoButtonClick(Sender: TObject);
{ Запрещение закрытия окна }
begin
  CloseFlag:=False;
  Close;
end;

end.
