//---------------------------------------------------------------------------
#pragma hdrstop
#include <stdio.h>
#include "StartDataNewBd85.h"
#include "TextHelper.h"
#include "ConvertHelper.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
StartDataNewBd85::StartDataNewBd85(
        const char* verPo
        , unsigned char indAddrZad
        , unsigned char groupAddrZad
        , unsigned short dnuZad
        , unsigned short voltageHiZad
        , unsigned short widthPwmZad // Длительность ШИМ заданная
        , unsigned short offsetPwmZ // Смешение ШИМ заданное
    )
{
    TextHelper::CopyText(_verPo, verPo, verPoSize);
    sprintf(_indAddrZad, "%d", indAddrZad);
    sprintf(_groupAddrZad, "%d", groupAddrZad);

    double dnuValueZad = ConvertHelper::CodeToValue( dnuZad );
    sprintf(_dnuZad, "%d", dnuZad);
    sprintf(_dnuValueZad, "%0.3f", dnuValueZad);
    double voltageValueZad = ConvertHelper::VoltageHiCodeToValue(voltageHiZad);
    sprintf(_voltageHiZad, "%d", voltageHiZad);
    sprintf(_voltageHiValueZad, "%0.2f", voltageValueZad);
    sprintf(_widthPwmZad, "%d", widthPwmZad);
    sprintf(_offsetPwmZ, "%d", offsetPwmZ);
}
//---------------------------------------------------------------------------
StartDataNewBd85::StartDataNewBd85()
{
    TextHelper::SetCharInText(_verPo, 0, verPoSize);  // Заполнить все символы строки пробелами
    TextHelper::SetCharInText(_indAddrZad, 0, indAddrZadSize);
    TextHelper::SetCharInText(_groupAddrZad, 0, indAddrZadSize);
    TextHelper::SetCharInText(_dnuZad, 0, uShortTextSize);
    TextHelper::SetCharInText(_dnuValueZad, 0, floatTextSize);
    TextHelper::SetCharInText(_voltageHiZad, 0, uShortTextSize);
    TextHelper::SetCharInText(_voltageHiValueZad, 0, floatTextSize);
    TextHelper::SetCharInText(_widthPwmZad, 0, uShortTextSize);
    TextHelper::SetCharInText(_offsetPwmZ, 0, uShortTextSize);
}
//---------------------------------------------------------------------------
const char* StartDataNewBd85::GetVerPo()
{
    return _verPo;
}
//---------------------------------------------------------------------------
const char* StartDataNewBd85::GetIndAddrZad()
{
    return _indAddrZad;
}
//---------------------------------------------------------------------------
const char* StartDataNewBd85::GetGroupAddrZad()
{
    return _groupAddrZad;
}
//---------------------------------------------------------------------------
const char* StartDataNewBd85::GetDnuZad()
{
    return _dnuZad;
}
//---------------------------------------------------------------------------
const char* StartDataNewBd85::GetDnuValueZad()
{
    return _dnuValueZad;
}
//---------------------------------------------------------------------------
const char* StartDataNewBd85::GetVoltageHiZad()
{
    return _voltageHiZad;
}
//---------------------------------------------------------------------------
const char* StartDataNewBd85::GetVoltageHiValueZad()
{
    return _voltageHiValueZad;
}
//---------------------------------------------------------------------------
const char* StartDataNewBd85::GetWidthPwmZad()
{
    return _widthPwmZad;
}
//---------------------------------------------------------------------------
const char* StartDataNewBd85::GetOffsetPwmZad()
{
    return _offsetPwmZ;
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
