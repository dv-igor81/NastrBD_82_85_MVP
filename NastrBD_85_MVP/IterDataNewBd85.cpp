//---------------------------------------------------------------------------
#pragma hdrstop
#include <stdio.h>
#include "IterDataNewBd85.h"
#include "TextHelper.h"
#include "ConvertHelper.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
IterDataNewBd85::IterDataNewBd85(
    unsigned char indAddr // �������������� �����
    , unsigned char groupAddr // ��������� �����
    , unsigned short temperature // ����������� �� (���)
    , unsigned short dnu
    , unsigned short voltageHi
)
{
    sprintf(_indAddr, "%d", indAddr);
    sprintf(_groupAddr, "%d", groupAddr);
    sprintf(_temperatureCode, "%d", temperature);
    double temperVal = ConvertHelper::TemperatureCodeToValue(temperature);
    sprintf(_temperatureValue, "%0.2f", temperVal);
    sprintf(_dnuCode, "%d", dnu );
    double dnuVal = ConvertHelper::CodeToValue(dnu);
    sprintf(_dnuValue, "%0.3f", dnuVal );
    sprintf(_voltageHiCode, "%d", voltageHi );
    double voltageHiVal = ConvertHelper::VoltageHiCodeToValue(voltageHi);
    sprintf(_voltageHiValue, "%0.1f", voltageHiVal );
}
//---------------------------------------------------------------------------
IterDataNewBd85::IterDataNewBd85()
{
    TextHelper::SetCharInText(_indAddr, 0, indAddrSize);
    TextHelper::SetCharInText(_groupAddr, 0, indAddrSize);
    TextHelper::SetCharInText(_temperatureCode, 0, uShortTextSize);
    TextHelper::SetCharInText(_temperatureValue, 0, floatTextSize);
    TextHelper::SetCharInText(_dnuCode, 0, uShortTextSize);
    TextHelper::SetCharInText(_dnuValue, 0, floatTextSize);
    TextHelper::SetCharInText(_voltageHiCode, 0, uShortTextSize);
    TextHelper::SetCharInText(_voltageHiValue, 0, floatTextSize);
}
//---------------------------------------------------------------------------
const char* IterDataNewBd85::GetIndAddr()
{
    return _indAddr;
}
//---------------------------------------------------------------------------
const char* IterDataNewBd85::GetGroupAddr()
{
    return _groupAddr;
}
//---------------------------------------------------------------------------
const char* IterDataNewBd85::GetTemperatureCode()
{
    return _temperatureCode;
}
//---------------------------------------------------------------------------
const char* IterDataNewBd85::GetTemperatureValue()
{
    return _temperatureValue;
}
//---------------------------------------------------------------------------
const char* IterDataNewBd85::GetDnuCode()
{
    return _dnuCode;
}
//---------------------------------------------------------------------------
const char* IterDataNewBd85::GetDnuValue()
{
    return _dnuValue;
}
//---------------------------------------------------------------------------
const char* IterDataNewBd85::GetVoltageHiCode()
{
    return _voltageHiCode;
}
//---------------------------------------------------------------------------
const char* IterDataNewBd85::GetVoltageHiValue()
{
    return _voltageHiValue;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
