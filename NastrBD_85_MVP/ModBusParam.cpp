//---------------------------------------------------------------------------
#pragma hdrstop
#include "ModBusParam.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
ModBusParam::ModBusParam(
    IAllProtokolS * protokol,
    ModBusEventContainer * container)
{
    _protokol = protokol;
    _container = container;
    Create(); // Создать объект
}
//---------------------------------------------------------------------------
ModBusParam::~ModBusParam()
{
    Destroy(); // Разрушить объект
}
//---------------------------------------------------------------------------
//ModBusParam::_numberOfBdDefault = ; // Номер блока
//---------------------------------------------------------------------------
void ModBusParam::Create() // Создать объект
{
    // 1) Номер блока
    as_MbParamNumberOfBdChange = new ActionSelf<const char*>(this, &ModBusParam::MbParamNumberOfBdChange);
    _container->ev_NumberOfBdChange += as_MbParamNumberOfBdChange;
    // 2) Экспозиция, мс
    as_MbParamExpositionChange = new ActionSelf<const char*>(this, &ModBusParam::MbParamExpositionChange);
    _container->ev_ExpositionChange += as_MbParamExpositionChange;
    // 3) Минимальный счёт
    as_MbParamMinimumCountChange = new ActionSelf<const char*>(this, &ModBusParam::MbParamMinimumCountChange);
    _container->ev_MinimumCountChange += as_MbParamMinimumCountChange;
    // 4) Максимальный счёт
    as_MbParamMaximumCountChange = new ActionSelf<const char*>(this, &ModBusParam::MbParamMaximumCountChange);
    _container->ev_MaximumCountChange += as_MbParamMaximumCountChange;
    // 5) Уровень перегрузки
    as_MbParamLevelOfOverloadChange = new ActionSelf<const char*>(this, &ModBusParam::MbParamLevelOfOverloadChange);
    _container->ev_LevelOfOverloadChange += as_MbParamLevelOfOverloadChange;
    // 6) Кол-во интервалов
    as_MbParamQuantityOfIntervalChange = new ActionSelf<const char*>(this, &ModBusParam::MbParamQuantityOfIntervalChange);
    _container->ev_QuantityOfIntervalChange += as_MbParamQuantityOfIntervalChange;
    // 7) Кол-во взгляда после
    as_MbParamQuantityOfLookChange = new ActionSelf<const char*>(this, &ModBusParam::MbParamQuantityOfLookChange);
    _container->ev_QuantityOfLookChange += as_MbParamQuantityOfLookChange;
    // 8) Уровень тревоги 1 * 10
    as_MbParamLevelOfAlarm1Change = new ActionSelf<const char*>(this, &ModBusParam::MbParamLevelOfAlarm1Change);
    _container->ev_LevelOfAlarm_1Change += as_MbParamLevelOfAlarm1Change;
    // 9) Уровень тревоги 2 * 10
    as_MbParamLevelOfAlarm2Change = new ActionSelf<const char*>(this, &ModBusParam::MbParamLevelOfAlarm2Change);
    _container->ev_LevelOfAlarm_2Change += as_MbParamLevelOfAlarm2Change;
    // 10) Уровень тревоги 3 * 30
    as_MbParamLevelOfAlarm3Change = new ActionSelf<const char*>(this, &ModBusParam::MbParamLevelOfAlarm3Change);
    _container->ev_LevelOfAlarm_3Change += as_MbParamLevelOfAlarm3Change;
    // 11) Фон, с
    as_MbParamPhonChange = new ActionSelf<const char*>(this, &ModBusParam::MbParamPhonChange);
    _container->ev_PhonChange += as_MbParamPhonChange;
    // 12) Длит. подинтервала фона, мс
    as_MbParamDurationOfPhonChange = new ActionSelf<const char*>(this, &ModBusParam::MbParamDurationOfPhonChange);
    _container->ev_DurationOfPhonChange += as_MbParamDurationOfPhonChange;
    // 13) Длит. сигнала тревоги, с
    as_MbParamDurationOfAlarmChange = new ActionSelf<const char*>(this, &ModBusParam::MbParamDurationOfAlarmChange);
    _container->ev_DurationOfAlarmChange += as_MbParamDurationOfAlarmChange;
    // 14) Длит. сигнала видео
    as_MbParamDurationOfVideoChange = new ActionSelf<const char*>(this, &ModBusParam::MbParamDurationOfVideoChange);
    _container->ev_DurationOfVideoChange += as_MbParamDurationOfVideoChange;
    // 15) По умолчанию
    as_ButtonModBusSetDefClick = new ActionSelf<>(this, &ModBusParam::ButtonModBusSetDefClick);
    _container->ev_SetDefClick += as_ButtonModBusSetDefClick;
    // 16) Запись
    as_ButtonModBusWriteClick = new ActionSelf<>(this, &ModBusParam::ButtonModBusWriteClick);
    _container->ev_WriteClick += as_ButtonModBusWriteClick;
}
//---------------------------------------------------------------------------
void ModBusParam::Destroy() // Разрушить объект
{
    delete as_MbParamNumberOfBdChange; // 1) Номер блока
    delete as_MbParamExpositionChange; // 2) Экспозиция, мс
    delete as_MbParamMinimumCountChange; // 3) Минимальный счёт
    delete as_MbParamMaximumCountChange; // 4) Максимальный счёт
    delete as_MbParamLevelOfOverloadChange; // 5) Уровень перегрузки
    delete as_MbParamQuantityOfIntervalChange; // 6) Кол-во интервалов
    delete as_MbParamQuantityOfLookChange; // 7) Кол-во взгляда после
    delete as_MbParamLevelOfAlarm1Change; // 8) Уровень тревоги 1 * 10
    delete as_MbParamLevelOfAlarm2Change; // 9) Уровень тревоги 2 * 10
    delete as_MbParamLevelOfAlarm3Change; // 10) Уровень тревоги 3 * 30
    delete as_MbParamPhonChange; // 11) Фон, с
    delete as_MbParamDurationOfPhonChange; // 12) Длит. подинтервала фона, мс
    delete as_MbParamDurationOfAlarmChange; // 13) Длит. сигнала тревоги, с
    delete as_MbParamDurationOfVideoChange; // 14) Длит. сигнала видео
    delete as_ButtonModBusSetDefClick; // 15) По умолчанию
    delete as_ButtonModBusWriteClick; // 16) Запись
}
//---------------------------------------------------------------------------
//_numberOfBdDefault
//---------------------------------------------------------------------------
//void ModBusParam::SetNumberOfBd( unsigned short numberOfBd )
//{
//    return & _numberOfBd;
///}
//---------------------------------------------------------------------------
//unsigned short ModBusParam::GetNumberOfBd() // Номер блока
//{
//    return _numberOfBd;
//}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void ModBusParam::MbParamNumberOfBdChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamExpositionChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamMinimumCountChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamMaximumCountChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamLevelOfOverloadChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamQuantityOfIntervalChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamQuantityOfLookChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamLevelOfAlarm1Change(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamLevelOfAlarm2Change(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamLevelOfAlarm3Change(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamPhonChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamDurationOfPhonChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamDurationOfAlarmChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamDurationOfVideoChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::ButtonModBusSetDefClick()
{
}
//---------------------------------------------------------------------------
void ModBusParam::ButtonModBusWriteClick()
{
}
//---------------------------------------------------------------------------
