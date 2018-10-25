//---------------------------------------------------------------------------
#ifndef IterDataNewBd85H
#define IterDataNewBd85H
//---------------------------------------------------------------------------
class IterDataNewBd85
{
public:
    IterDataNewBd85(
        unsigned char indAddr
    );
    IterDataNewBd85();

    const char* GetIndAddr();
private:
    enum { indAddrSize = 4
        , uShortTextSize = 6 // 5 цифр и завершающий ноль
        , floatTextSize = 10        
    };
    char _indAddr[indAddrSize];
};
//---------------------------------------------------------------------------
#endif
