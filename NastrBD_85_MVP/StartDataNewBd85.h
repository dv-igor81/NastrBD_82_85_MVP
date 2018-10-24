//---------------------------------------------------------------------------
#ifndef StartDataNewBd85H
#define StartDataNewBd85H
//---------------------------------------------------------------------------
class StartDataNewBd85
{
public:
    StartDataNewBd85(
    const char* verPo
    , const char* indAddrZad
    );
    StartDataNewBd85();        
    const char* GetVerPo();
    const char* GetIndAddrZad();
private:
    enum { verPoSize = 5
        , indAddrZadSize = 4
     };
    char _verPo[verPoSize];
    char _indAddrZad[indAddrZadSize];
};
//---------------------------------------------------------------------------
#endif
