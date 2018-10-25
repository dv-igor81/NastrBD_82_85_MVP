//---------------------------------------------------------------------------
#pragma hdrstop
#include "StartDataNewBd85.h"
#include "TextHelper.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
StartDataNewBd85::StartDataNewBd85(
    const char* verPo
        , const char* indAddrZad
        , const char* dnuZad
        , const char* dnuValueZad
        , const char* voltageHiZad
        , const char* voltageHiValueZad
    )
{
    TextHelper::CopyText(_verPo, verPo, verPoSize);
    TextHelper::CopyText(_indAddrZad, indAddrZad, indAddrZadSize);
    TextHelper::CopyText(_dnuZad, dnuZad, uShortTextSize);
    TextHelper::CopyText(_dnuValueZad, dnuValueZad, floatTextSize);
    TextHelper::CopyText(_voltageHiZad, voltageHiZad, uShortTextSize);
    TextHelper::CopyText(_voltageHiValueZad, voltageHiValueZad, floatTextSize);
}
//---------------------------------------------------------------------------
StartDataNewBd85::StartDataNewBd85()
{
    TextHelper::SpaseText(_verPo, verPoSize);  // Заполнить все символы строки пробелами
    TextHelper::SpaseText(_indAddrZad, indAddrZadSize);
    TextHelper::SpaseText(_dnuZad, uShortTextSize);
    TextHelper::SpaseText(_dnuValueZad, floatTextSize);
    TextHelper::SpaseText(_voltageHiZad, uShortTextSize);
    TextHelper::SpaseText(_voltageHiValueZad, floatTextSize);
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
