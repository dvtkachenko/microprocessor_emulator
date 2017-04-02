unit Des;
interface

uses SysUtils;

Function HexToLong(S:string;Var ErrorCode:integer):LongInt;

implementation

function HexToLong(S:string;Var ErrorCode:integer):LongInt;
{ ѕреобразование из 16-ричной строки в число }
Var Ves,OutSum,i,Buf:LongInt;
begin
  Ves:=1;
  OutSum:=0;
  ErrorCode:=0;
  Buf:=0;
  for i:=Length(S) downto 1 do
    begin
      if S[i] in ['A'..'F'] then
        case S[i] of
          'A': Buf:=10;
          'B': Buf:=11;
          'C': Buf:=12;
          'D': Buf:=13;
          'E': Buf:=14;
          'F': Buf:=15;
        end
      else
        begin
          if S[i] in ['0'..'9'] then
            Val(S[i],Buf,ErrorCode)
          else
            begin
              ErrorCode:=1;
              Exit;
            end;
        end;
      OutSum:=OutSum+Buf*Ves;
      Ves:=Ves*16;
    end;
  HexToLong:=OutSum;
end; {  онец преобразовани€ из 16-ричной строки в число }

END.

