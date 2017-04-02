//---------------------------------------------------------------------------
#ifndef threadH
#define threadH
//---------------------------------------------------------------------------
#include <Classes.hpp>

#define CREATE_ZAST      true
#define DESTROY_ZAST     false

//---------------------------------------------------------------------------
class TZastavkaFhread : public TThread
{
private:
protected:
    void __fastcall Execute();
public:
    int Create;
    __fastcall TZastavkaFhread(bool CreateSuspended);
    void __fastcall CreateDestroy(void);
};

extern TZastavkaFhread *ZastavkaFhread;
//---------------------------------------------------------------------------
#endif
