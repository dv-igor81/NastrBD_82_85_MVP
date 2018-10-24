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
        , const char* dnuZad
        , const char* dnuValueZad
    );
    StartDataNewBd85();        
    const char* GetVerPo();
    const char* GetIndAddrZad();
    const char* GetDnuZad();
    const char* GetDnuValueZad();    
private:
    enum { verPoSize = 5
        , indAddrZadSize = 4
        , uShortTextSize = 6 // 5 цифр и завершающий ноль
        , floatTextSize = 10        
    };
    char _verPo[verPoSize];
    char _indAddrZad[indAddrZadSize];
    char _dnuZad[uShortTextSize];
    char _dnuValueZad[floatTextSize];
};
//---------------------------------------------------------------------------
#endif
