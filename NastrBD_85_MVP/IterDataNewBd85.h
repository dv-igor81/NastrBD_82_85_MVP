//---------------------------------------------------------------------------
#ifndef IterDataNewBd85H
#define IterDataNewBd85H
//---------------------------------------------------------------------------
class IterDataNewBd85
{
public:
    IterDataNewBd85(
        unsigned char indAddr // �������������� �����
        , unsigned char groupAddr // ��������� �����
        , unsigned short temperature // ����������� �� (���)
        , unsigned short dnu
        , unsigned short voltageHi
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
private:
    enum { indAddrSize = 4
        , uShortTextSize = 6 // 5 ���� � ����������� ����
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
};
//---------------------------------------------------------------------------
#endif
