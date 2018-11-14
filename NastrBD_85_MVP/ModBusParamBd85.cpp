//---------------------------------------------------------------------------
#pragma hdrstop
#include "ModBusParamBd85.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
ModBusParamBd85::ModBusParamBd85(
    IAllProtokolS * protokol,
    ModBusEventContainer * container,
    ITask * task)
{
    _protokol = protokol;
    _container = container;
    _task = task;
    Create(); // Создать объект
}
//---------------------------------------------------------------------------
ModBusParamBd85::~ModBusParamBd85()
{
    Destroy(); // Разрушить объект
}
//---------------------------------------------------------------------------
const unsigned short ModBusParamBd85::_expositionDefault = 250; // 2) Экспозиция, мс
const unsigned short ModBusParamBd85::_minimumCountDefault = 10; // 3) Минимальный счёт                                                                                                 1
const unsigned short ModBusParamBd85::_maximumCountDefault = 1000; // 4) Максимальный счёт
const unsigned short ModBusParamBd85::_levelOfOverloadDefault = 10000; // 5) Уровень перегрузки
const unsigned short ModBusParamBd85::_quantityOfIntervalDefault = 8; // 6) Кол-во интервалов
const unsigned short ModBusParamBd85::_quantityOfLookDefault = 4;// 7) Кол-во взгляда после
const unsigned short ModBusParamBd85::_levelOfAlarm1Default = 80; // 8) Уровень тревоги 1 * 10
const unsigned short ModBusParamBd85::_levelOfAlarm2Default = 800; // 9) Уровень тревоги 2 * 10
const unsigned short ModBusParamBd85::_levelOfAlarm3Default = 8000; // 10) Уровень тревоги 3 * 30
const unsigned short ModBusParamBd85::_phonDefault = 100; // 11) Фон, с
const unsigned short ModBusParamBd85::_durationOfPhonDefault = 1000; // 12) Длит. подинтервала фона, мс
const unsigned short ModBusParamBd85::_durationOfAlarmDefault = 7; // 13) Длит. сигнала тревоги, с
const unsigned short ModBusParamBd85::_durationOfVideoDefault = 7; // 14) Длит. сигнала видео
//---------------------------------------------------------------------------
const unsigned short ModBusParamBd85::_numberOfBdMemoryAddr = 10; // 1) Номер блока
const unsigned short ModBusParamBd85::_expositionMemoryAddr = 0x300+2; // 2) Экспозиция, мс
const unsigned short ModBusParamBd85::_minimumCountMemoryAddr = 0x300+3; // 3) Минимальный счёт
const unsigned short ModBusParamBd85::_maximumCountMemoryAddr = 0x300+4; // 4) Максимальный счёт
const unsigned short ModBusParamBd85::_levelOfOverloadMemoryAddr = 0x300+5; // 5) Уровень перегрузки
const unsigned short ModBusParamBd85::_quantityOfIntervalMemoryAddr = 0x300+6; // 6) Кол-во интервалов
const unsigned short ModBusParamBd85::_quantityOfLookMemoryAddr = 0x300+7;// 7) Кол-во взгляда после
const unsigned short ModBusParamBd85::_levelOfAlarm1MemoryAddr = 0x300+8; // 8) Уровень тревоги 1 * 10
const unsigned short ModBusParamBd85::_levelOfAlarm2MemoryAddr = 0x300+9; // 9) Уровень тревоги 2 * 10
const unsigned short ModBusParamBd85::_levelOfAlarm3MemoryAddr = 0x300+10; // 10) Уровень тревоги 3 * 30
const unsigned short ModBusParamBd85::_phonMemoryAddr = 0x300+11; // 11) Фон, с
const unsigned short ModBusParamBd85::_durationOfPhonMemoryAddr = 18; // 12) Длит. подинтервала фона, мс
const unsigned short ModBusParamBd85::_durationOfAlarmMemoryAddr = 0x300 + 12; // 13) Длит. сигнала тревоги, с
const unsigned short ModBusParamBd85::_durationOfVideoMemoryAddr = 0x300 + 13; // 14) Длит. сигнала видео
//---------------------------------------------------------------------------
void ModBusParamBd85::Create() // Создать объект
{
    // 1) Номер блока
    as_MbParamNumberOfBdChange =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamNumberOfBdChange);
    _container->ev_NumberOfBdChange += as_MbParamNumberOfBdChange;
    // 2) Экспозиция, мс
    as_MbParamExpositionChange =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamExpositionChange);
    _container->ev_ExpositionChange += as_MbParamExpositionChange;
    // 3) Минимальный счёт
    as_MbParamMinimumCountChange =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamMinimumCountChange);
    _container->ev_MinimumCountChange += as_MbParamMinimumCountChange;
    // 4) Максимальный счёт
    as_MbParamMaximumCountChange =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamMaximumCountChange);
    _container->ev_MaximumCountChange += as_MbParamMaximumCountChange;
    // 5) Уровень перегрузки
    as_MbParamLevelOfOverloadChange =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamLevelOfOverloadChange);
    _container->ev_LevelOfOverloadChange += as_MbParamLevelOfOverloadChange;
    // 6) Кол-во интервалов
    as_MbParamQuantityOfIntervalChange =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamQuantityOfIntervalChange);
    _container->ev_QuantityOfIntervalChange += as_MbParamQuantityOfIntervalChange;
    // 7) Кол-во взгляда после
    as_MbParamQuantityOfLookChange =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamQuantityOfLookChange);
    _container->ev_QuantityOfLookChange += as_MbParamQuantityOfLookChange;
    // 8) Уровень тревоги 1 * 10
    as_MbParamLevelOfAlarm1Change =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamLevelOfAlarm1Change);
    _container->ev_LevelOfAlarm_1Change += as_MbParamLevelOfAlarm1Change;
    // 9) Уровень тревоги 2 * 10
    as_MbParamLevelOfAlarm2Change =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamLevelOfAlarm2Change);
    _container->ev_LevelOfAlarm_2Change += as_MbParamLevelOfAlarm2Change;
    // 10) Уровень тревоги 3 * 30
    as_MbParamLevelOfAlarm3Change =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamLevelOfAlarm3Change);
    _container->ev_LevelOfAlarm_3Change += as_MbParamLevelOfAlarm3Change;
    // 11) Фон, с
    as_MbParamPhonChange =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamPhonChange);
    _container->ev_PhonChange += as_MbParamPhonChange;
    // 12) Длит. подинтервала фона, мс
    as_MbParamDurationOfPhonChange =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamDurationOfPhonChange);
    _container->ev_DurationOfPhonChange += as_MbParamDurationOfPhonChange;
    // 13) Длит. сигнала тревоги, с
    as_MbParamDurationOfAlarmChange =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamDurationOfAlarmChange);
    _container->ev_DurationOfAlarmChange += as_MbParamDurationOfAlarmChange;
    // 14) Длит. сигнала видео
    as_MbParamDurationOfVideoChange =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamDurationOfVideoChange);
    _container->ev_DurationOfVideoChange += as_MbParamDurationOfVideoChange;
    // 15) По умолчанию
    as_ButtonModBusSetDefClick =
        new ActionSelf<>(this, &ModBusParamBd85::ButtonModBusSetDefClick);
    _container->ev_SetDefClick += as_ButtonModBusSetDefClick;
    // 16) Запись
    as_ButtonModBusWriteClick =
        new ActionSelf<>(this, &ModBusParamBd85::ButtonModBusWriteClick);
    _container->ev_WriteClick += as_ButtonModBusWriteClick;
}
//---------------------------------------------------------------------------
void ModBusParamBd85::Destroy() // Разрушить объект
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
void ModBusParamBd85::ActionIfEvent() // Действие, если событие
{
}
//---------------------------------------------------------------------------
void ModBusParamBd85::InitAddrRegModBus()
{
    _addrRegModBus[0] = _numberOfBdMemoryAddr;
    _addrRegModBus[1] = _expositionMemoryAddr;
    _addrRegModBus[2] = _minimumCountMemoryAddr;
    _addrRegModBus[3] = _maximumCountMemoryAddr;
    _addrRegModBus[4] = _levelOfOverloadMemoryAddr;
    _addrRegModBus[5] = _quantityOfIntervalMemoryAddr;
    _addrRegModBus[6] = _quantityOfLookMemoryAddr;
    _addrRegModBus[7] = _levelOfAlarm1MemoryAddr;
    _addrRegModBus[8] = _levelOfAlarm2MemoryAddr;
    _addrRegModBus[9] = _levelOfAlarm3MemoryAddr;
    _addrRegModBus[10] = _phonMemoryAddr;
    _addrRegModBus[11] = _durationOfPhonMemoryAddr;
    _addrRegModBus[12] = _durationOfAlarmMemoryAddr;
    _addrRegModBus[13] = _durationOfVideoMemoryAddr;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamNumberOfBdChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamExpositionChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamMinimumCountChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamMaximumCountChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamLevelOfOverloadChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamQuantityOfIntervalChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamQuantityOfLookChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamLevelOfAlarm1Change(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamLevelOfAlarm2Change(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamLevelOfAlarm3Change(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamPhonChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamDurationOfPhonChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamDurationOfAlarmChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamDurationOfVideoChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParamBd85::ButtonModBusSetDefClick()
{
}
//---------------------------------------------------------------------------
void ModBusParamBd85::ButtonModBusWriteClick()
{
}
//---------------------------------------------------------------------------
