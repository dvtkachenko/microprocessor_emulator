unit Help;

interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, Menus, ExtCtrls, Tabs, TabNotBk, ComCtrls;

type
  THelpForm = class(TForm)
    HelpNotebook: TTabbedNotebook;
    WorkList: TListBox;
    VozmList: TListBox;
    MppList: TListBox;
    procedure FormCreate(Sender: TObject);
    procedure HelpNotebookChange(Sender: TObject; NewTab: Integer;
      var AllowChange: Boolean);
    procedure FormKeyPress(Sender: TObject; var Key: Char);

  private
    { Private declarations }
  public
    HelpExistFlag:Boolean;
    { Public declarations }
  end;

var
  HelpForm: THelpForm;

implementation

{$R *.DFM}

procedure THelpForm.FormCreate(Sender: TObject);
{ Поиск и загрузка файлов помощи }
{Var SR:TSearchRec;
    H1,H2,H3:Boolean;{ Флаги извещают о присутствии файлов помощи }
begin
  { файл помощи по работе с эмулятором }
 { if FindFirst('ID1\work.txt',$3F,SR)<>0 then
    begin
      MessageDlg('Отсутствует файл помощи по работе с эмулятором',mtInformation,[mbOk],0);
      H1:=False;
    end
  else
    WorkList.Items.LoadFromFIle('ID1\work.txt');
  { файл помощи по возможностям программы }
{  if FindFirst('ID1\vozm.txt',$3F,SR)<>0 then
    begin
      MessageDlg('Отсутствует файл помощи по возможностям программы',mtInformation,[mbOk],0);
      H3:=False;
    end
  else
    VozmList.Items.LoadFromFIle('ID1\vozm.txt');
  { файл помощи по прошивке МПП }
{  if FindFirst('ID1\mpp.txt',$3F,SR)<>0 then
    begin
      MessageDlg('Отсутствует файл помощи по прошивке МПП',mtInformation,[mbOk],0);
      H3:=False;
    end
  else
    MppList.Items.LoadFromFIle('ID1\mpp.txt');}
  { Формирование признака наличия хотя-бы одного файла помощи }
{  HelpExistFlag := H1 or H2 or H3;}
end;

procedure THelpForm.HelpNotebookChange(Sender: TObject; NewTab: Integer;
                                       var AllowChange: Boolean);
{ Проверка нажатия на страницу с именем "Закрыть" }
begin
  if NewTab=3 then
    begin
      AllowChange:=False;
      Close;
    end;
end;

procedure THelpForm.FormKeyPress(Sender: TObject; var Key: Char);
{ Закрывать по Esc }
begin
  if Key=#27 then Close;
end;

end.
