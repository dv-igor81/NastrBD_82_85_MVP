//---------------------------------------------------------------------------
#ifndef StartDataNewBd85H
#define StartDataNewBd85H
//---------------------------------------------------------------------------
#include "EepromBd85Settings.h"
//---------------------------------------------------------------------------
class StartDataNewBd85
{
public:
    StartDataNewBd85( EepromBd85Settings * data );
    StartDataNewBd85();
    void InsteadOfConstructor(); // ������ ������������

    const char* GetVerPo();
    const char* GetIndAddrZad();
    const char* GetGroupAddrZad();
    const char* GetDnuZad();
    const char* GetDnuValueZad();
    const char* GetVoltageHiZad();
    const char* GetVoltageHiValueZad();
    const char* GetWidthPwmZad();
    const char* GetOffsetPwmZad();
    const char* GetPeriodPwmZad();
    int GetFlagArch();
private:
    enum { verPoSize = 5
        , indAddrZadSize = 4
        , uShortTextSize = 6 // 5 ���� � ����������� ����
        , floatTextSize = 10        
    };
    char _verPo[verPoSize];
    char _indAddrZad[indAddrZadSize];
    char _groupAddrZad[indAddrZadSize];
    char _dnuZad[uShortTextSize];
    char _dnuValueZad[floatTextSize];
    char _voltageHiZad[uShortTextSize];
    char _voltageHiValueZad[floatTextSize];
    char _widthPwmZad[uShortTextSize]; // ������������ ��� ��������
    char _offsetPwmZad[uShortTextSize]; // �������� ��� ��������
    char _periodPwmZad[uShortTextSize]; // ������ ��� ��������
    int _flagArch; // ���� ���   (-1 - false, 0 - ������ �� ������, 1 - true)
};
//---------------------------------------------------------------------------
#endif
