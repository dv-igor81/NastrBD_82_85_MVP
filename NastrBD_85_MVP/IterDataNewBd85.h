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
    );
    IterDataNewBd85();

    const char* GetIndAddr();
    const char* GetGroupAddr();
    const char* GetTemperatureCode();
    const char* GetTemperatureValue();
private:
    enum { indAddrSize = 4
        , uShortTextSize = 6 // 5 ���� � ����������� ����
        , floatTextSize = 10
    };
    char _indAddr[indAddrSize];
    char _groupAddr[indAddrSize];
    char _temperatureCode[uShortTextSize];
    char _temperatureValue[floatTextSize];
};
//---------------------------------------------------------------------------
#endif
