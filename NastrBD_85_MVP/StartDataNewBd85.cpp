//---------------------------------------------------------------------------
#pragma hdrstop
#include <stdio.h>
#include "StartDataNewBd85.h"
#include "TextHelper.h"
#include "ConvertHelper.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
StartDataNewBd85::StartDataNewBd85( EepromBd85Settings * data )
{
    InsteadOfConstructor(); // Вместо конструктора

    TextHelper::CopyText( _verPo, data->VerPo, verPoSize );
    sprintf( _indAddrZad, "%d", data->IndAddrZad );
    sprintf( _groupAddrZad, "%d", data->GroupAddrZad );
    _dnuZad = data->DnuZad;
    _voltageHiZad = data->VoltageHiZad;
    sprintf( _widthPwmZad, "%d", data->WidthPwmZad );
    sprintf( _offsetPwmZad, "%d", data->OffsetPwmZad );
    sprintf( _periodPwmZad, "%d", data->PeriodPwmZad );
    _flagArch = data->FlagArch;
}
//---------------------------------------------------------------------------
StartDataNewBd85::StartDataNewBd85()
{
    InsteadOfConstructor(); // Вместо конструктора
}
//---------------------------------------------------------------------------
void StartDataNewBd85::InsteadOfConstructor() // Вместо конструктора
{
    // Заполнить все символы строки нулями
    TextHelper::SetCharInText(_verPo, 0, verPoSize);
    TextHelper::SetCharInText(_indAddrZad, 0, indAddrZadSize);
    TextHelper::SetCharInText(_groupAddrZad, 0, indAddrZadSize);
    _dnuZad = -1;
    _voltageHiZad = -1;
    TextHelper::SetCharInText(_widthPwmZad, 0, uShortTextSize);
    TextHelper::SetCharInText(_offsetPwmZad, 0, uShortTextSize);
    TextHelper::SetCharInText(_periodPwmZad, 0, uShortTextSize);
    _flagArch = 0;
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
int StartDataNewBd85::GetDnuZad()
{
    return _dnuZad;
}
//---------------------------------------------------------------------------
int StartDataNewBd85::GetVoltageHiZad()
{
    return _voltageHiZad;
}
//---------------------------------------------------------------------------
const char* StartDataNewBd85::GetWidthPwmZad()
{
    return _widthPwmZad;
}
//---------------------------------------------------------------------------
const char* StartDataNewBd85::GetOffsetPwmZad()
{
    return _offsetPwmZad;
}
//---------------------------------------------------------------------------
const char* StartDataNewBd85::GetPeriodPwmZad()
{
    return _periodPwmZad;
}
//---------------------------------------------------------------------------
int StartDataNewBd85::GetFlagArch()
{
    return _flagArch;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
