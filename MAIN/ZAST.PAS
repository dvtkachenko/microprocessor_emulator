unit Zast;
{ ‘орма с заставкой программы }
interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, ExtCtrls, StdCtrls;

type
  TZastForm = class(TForm)
    ZastBevel: TBevel;
    ZastPanel: TPanel;
    ZastImage: TImage;
    ZastLabel1: TLabel;
    ZastLabel2: TLabel;
    ZastLabel3: TLabel;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  ZastForm: TZastForm;

implementation

{$R *.DFM}

end.
