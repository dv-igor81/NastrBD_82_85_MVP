//---------------------------------------------------------------------------
#ifndef StartDataNewBd85H
#define StartDataNewBd85H
//---------------------------------------------------------------------------
class StartDataNewBd85
{
public:
    StartDataNewBd85(
        const char* verPo
        , unsigned char indAddrZad
        , unsigned char groupAddrZad
        , unsigned short dnuZad
        , unsigned short voltageHiZad
        , unsigned short widthPwmZad // Длительность ШИМ заданная
    );
    StartDataNewBd85();        
    const char* GetVerPo();
    const char* GetIndAddrZad();
    const char* GetGroupAddrZad();
    const char* GetDnuZad();
    const char* GetDnuValueZad();
    const char* GetVoltageHiZad();
    const char* GetVoltageHiValueZad();
    const char* GetWidthPwmZad();
private:
    enum { verPoSize = 5
        , indAddrZadSize = 4
        , uShortTextSize = 6 // 5 цифр и завершающий ноль
        , floatTextSize = 10        
    };
    char _verPo[verPoSize];
    char _indAddrZad[indAddrZadSize];
    char _groupAddrZad[indAddrZadSize];
    char _dnuZad[uShortTextSize];
    char _dnuValueZad[floatTextSize];
    char _voltageHiZad[uShortTextSize];
    char _voltageHiValueZad[floatTextSize];
    char _widthPwmZad[uShortTextSize]; // Длительность ШИМ заданная
};
//---------------------------------------------------------------------------
#endif
