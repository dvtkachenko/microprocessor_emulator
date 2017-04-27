unit Mem_edit;

interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, ExtCtrls, StdCtrls, Des, Buttons, Mask;

type
  TMem_EditForm = class(TForm)
    OkButtonEditMem: TButton;
    CancelButtonEditMem: TButton;
    MaskEditMem: TEdit;
    MemoryEditLabel: TLabel;
    procedure OkButtonEditMemClick(Sender: TObject);
    procedure CancelButtonEditMemClick(Sender: TObject);
    procedure FormKeyPress(Sender: TObject; var Key: Char);
    procedure FormCloseQuery(Sender: TObject; var CanClose: Boolean);
    procedure FormShow(Sender: TObject);
    procedure InitMem_EditForChip(Var InLabel,NameLabel:TLabel;
                                 Var OutRezult:LongInt;MaxValue:LongInt);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Mem_EditForm: TMem_EditForm;
  Buffer:string;  { буфер исходной строки }

implementation

{$R *.DFM}

procedure TMem_EditForm.FormShow(Sender: TObject);
{ Копирование исходной строки в буфер для возможного восстановления }
begin
  Buffer:=MaskEditMem.Text;
end;

procedure TMem_EditForm.OkButtonEditMemClick(Sender: TObject);
{ Окончание редактирования }
begin
  Close;
end;

procedure TMem_EditForm.CancelButtonEditMemClick(Sender: TObject);
{ Копирование исходной строки из буфера для отмены редактирования }
begin
  MaskEditMem.Text:=Buffer;
  Close;
end;

procedure TMem_EditForm.FormKeyPress(Sender: TObject; var Key: Char);
{ Настройка редактора на пропуск только 16-ричных чисел }
begin
  Key:=UpCase(Key);
  if not(Key in ['0'..'9','A'..'F'])and(Key>=#32) then
    Key:=#0
  else
    if Key=#13 then
      Close;
end;

procedure TMem_EditForm.FormCloseQuery(Sender: TObject;var CanClose: Boolean);
{ Проверка корректности введенных данных }
begin
  if length(MaskEditMem.Text)<MaskEditMem.MaxLength then
    begin
      MessageDlg('Недостаточная длина редактируемого поля',mtError,[mbOk],0);
      CanClose:=False;
    end;
end;

procedure TMem_EditForm.InitMem_EditForChip(Var InLabel,NameLabel:TLabel;
                                 Var OutRezult:LongInt;MaxValue:LongInt);
{ Настройка универсального редактора для редактирования содержимого  }
{ регистров микропроцессора }
Var  ErrorCode:Integer;
     BufOut:LongInt;
begin
  MemoryEditLabel.Caption:='Содержимое регистра '+
                            NameLabel.Caption;
  MaskEditMem.Text:= InLabel.Caption;
  MaskEditMem.MaxLength:=Length(InLabel.Caption);
  {  Проверка корректности ввода данных }
  repeat
    ShowModal;
    BufOut:=HexToLong(MaskEditMem.Text,ErrorCode);
    if not((BufOut<=MaxValue)or(MaxValue=0)) then
      MessageDlg('Недопустимое значение редактируемого поля',mtError,[mbOk],0);
  Until (BufOut<=MaxValue)or(MaxValue=0);
  { Загрузка измененных значений }
  InLabel.Caption:=MaskEditMem.Text;
  OutRezult:=HexToLong(InLabel.Caption,ErrorCode);
end;


end.
