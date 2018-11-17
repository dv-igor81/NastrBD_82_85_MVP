//---------------------------------------------------------------------------
#pragma hdrstop
#include "EepromBd85Settings.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
char EepromBd85Settings::VerPo[5];
//---------------------------------------------------------------------------
EepromBd85Settings::EepromBd85Settings()
{
    for (int i = 0; i < 5; i++)
    {
        VerPo[i] = 0;
    }
}
//---------------------------------------------------------------------------
void EepromBd85Settings::Copy( EepromBd85Settings & data )
{
    IndAddrZad = data.IndAddrZad;
    GroupAddrZad = data.GroupAddrZad;
    DnuZad = data.DnuZad;
    VoltageHiZad = data.VoltageHiZad;
    WidthPwmZad = data.WidthPwmZad;
    OffsetPwmZad = data.OffsetPwmZad;
    PeriodPwmZad = data.PeriodPwmZad;
    FlagArch = data.FlagArch;
    VoltageHiZadValue = data.VoltageHiZadValue;
}
//---------------------------------------------------------------------------
bool EepromBd85Settings::NotEqual( EepromBd85Settings & data )
{
    bool flagEqual = true;
    MarkIfNotEqual( flagEqual, IndAddrZad, data.IndAddrZad ); // Отметить, если два поля не эквивалентны
    MarkIfNotEqual( flagEqual, GroupAddrZad, data.GroupAddrZad );
    MarkIfNotEqual( flagEqual, DnuZad, data.DnuZad );
    MarkIfNotEqual( flagEqual, VoltageHiZad, data.VoltageHiZad );
    MarkIfNotEqual( flagEqual, WidthPwmZad, data.WidthPwmZad );
    MarkIfNotEqual( flagEqual, OffsetPwmZad, data.OffsetPwmZad );
    MarkIfNotEqual( flagEqual, PeriodPwmZad, data.PeriodPwmZad );
    MarkIfNotEqual( flagEqual, FlagArch, data.FlagArch );
    return !flagEqual;
}
//---------------------------------------------------------------------------
void EepromBd85Settings::MarkIfNotEqual( bool & flagEqual, int arg1, int arg2  )
{
    flagEqual = flagEqual && ( arg1 == arg2 );
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

