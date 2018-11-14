//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include <stdio.h>
//---------------------------------------------------------------------------
#include "ModBusTextDataBd85.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
ModBusTextDataBd85::ModBusTextDataBd85(IModBusParamDataBd85 * param)
{
    sprintf(_numberOfBd, "%d", param->GetNumberOfBd());
    sprintf(_exposition, "%d", param->GetExposition());
    sprintf(_minimumCount, "%d", param->GetMinimumCount());
    sprintf(_maximumCount, "%d", param->GetMaximumCount());
    sprintf(_levelOfOverload, "%d", param->GetLevelOfOverload());
    sprintf(_quantityOfInterval, "%d", param->GetQuantityOfInterval());
    sprintf(_quantityOfLook, "%d", param->GetQuantityOfLook());
    sprintf(_levelOfAlarm1, "%d", param->GetLevelOfAlarm1());
    sprintf(_levelOfAlarm2, "%d", param->GetLevelOfAlarm2());
    sprintf(_levelOfAlarm3, "%d", param->GetLevelOfAlarm3());
    sprintf(_phon, "%d", param->GetPhon());
    sprintf(_durationOfPhon, "%d", param->GetDurationOfPhon());
    sprintf(_durationOfAlarm, "%d", param->GetDurationOfAlarm());
    sprintf(_durationOfVideo, "%d", param->GetDurationOfVideo());
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetNumberOfBd() // 1) Номер блока
{
    return _numberOfBd;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetExposition() // 2) Экспозиция, мс
{
    return _exposition;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetMinimumCount() // 3) Минимальный счёт
{
    return _minimumCount;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetMaximumCount() // 4) Максимальный счёт
{
    return _maximumCount;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetLevelOfOverload() // 5) Уровень перегрузки
{
    return _levelOfOverload;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetQuantityOfInterval() // 6) Кол-во интервалов
{
    return _quantityOfInterval;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetQuantityOfLook() // 7) Кол-во взгляда после
{
    return _quantityOfLook;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetLevelOfAlarm1() // 8) Уровень тревоги 1 * 10
{
    return _levelOfAlarm1;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetLevelOfAlarm2() // 9) Уровень тревоги 2 * 10
{
    return _levelOfAlarm2;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetLevelOfAlarm3() // 10) Уровень тревоги 3 * 10
{
    return _levelOfAlarm3;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetPhon() // 11) Фон, с
{
    return _phon;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetDurationOfPhon() // 12) Длит. подинтервала фона, мс
{
    return _durationOfPhon;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetDurationOfAlarm() // 13) Длит. сигнала тревоги, с
{
    return _durationOfAlarm;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetDurationOfVideo() // 14) Длит. сигнала видео
{
    return _durationOfVideo;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
