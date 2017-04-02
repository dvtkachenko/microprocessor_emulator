unit About;

interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, ExtCtrls, StdCtrls, Buttons;

type
  TAboutForm = class(TForm)
    AboutPanel: TPanel;
    EmuLabel: TLabel;
    NameLabel: TLabel;
    OkBitBtn: TBitBtn;
    VersionLabel: TLabel;
    Image1: TImage;
    EvmLabel: TLabel;
    procedure OkBitBtnClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  AboutForm: TAboutForm;
  { ����� ���������� �������� �� ��������� ������ }
implementation

{$R *.DFM}

procedure TAboutForm.OkBitBtnClick(Sender: TObject);
{ Ok - ������� }
begin
  Close;
end;

end.
