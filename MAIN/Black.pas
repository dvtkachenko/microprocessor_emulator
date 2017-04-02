unit Black;

interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs;

type
  TBlackForm = class(TForm)
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  BlackForm: TBlackForm;
  { Форма создает темно - синий фон для работы программы }
implementation

{$R *.DFM}

end.
