//---------------------------------------------------------------------------
#ifndef IterDataNewBd85H
#define IterDataNewBd85H
//---------------------------------------------------------------------------
class IterDataNewBd85
{
public:
    IterDataNewBd85(
        unsigned char indAddr // Индивидуальный адрес
        , unsigned char groupAddr // Групповой адрес
        , unsigned short temperature // Температура МК (КОД)
        , unsigned short dnu
        , unsigned short voltageHi
        , unsigned short widthPwm
        , unsigned short periodPwm
        , unsigned int scaling
    );
    IterDataNewBd85();

    const char* GetIndAddr();
    const char* GetGroupAddr();
    const char* GetTemperatureCode();
    const char* GetTemperatureValue();
    const char* GetDnuCode();
    const char* GetDnuValue();
    const char* GetVoltageHiCode();
    const char* GetVoltageHiValue();
    const char* GetWidthPwmCode();
    const char* GetWidthPwmValue();
    const char* GetPeriodPwmCode();
    const char* GetPeriodPwmValue();
    const char* GetScaling();
private:
    enum { indAddrSize = 4
        , uShortTextSize = 6 // 5 цифр и завершающий ноль
        , floatTextSize = 10
    };
    char _indAddr[indAddrSize];
    char _groupAddr[indAddrSize];
    char _temperatureCode[uShortTextSize];
    char _temperatureValue[floatTextSize];
    char _dnuCode[uShortTextSize];
    char _dnuValue[floatTextSize];
    char _voltageHiCode[uShortTextSize];
    char _voltageHiValue[floatTextSize];
    char _widthPwmCode[uShortTextSize];
    char _widthPwmValue[floatTextSize];
    char _periodPwmCode[uShortTextSize];
    char _periodPwmValue[floatTextSize];
    char _scaling[uShortTextSize];
};
//---------------------------------------------------------------------------
#endif
