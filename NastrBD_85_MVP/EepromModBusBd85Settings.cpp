//---------------------------------------------------------------------------
#pragma hdrstop
#include "EepromModBusBd85Settings.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
 // 2) Экспозиция, мс
const unsigned short EepromModBusBd85Settings::ExpositionDefault = 250;
 // 3) Минимальный счёт
const unsigned short EepromModBusBd85Settings::MinimumCountDefault = 10;
// 4) Максимальный счёт                                                                                               1
const unsigned short EepromModBusBd85Settings::MaximumCountDefault = 1000;
 // 5) Уровень перегрузки
const unsigned short EepromModBusBd85Settings::LevelOfOverloadDefault = 10000;
// 6) Кол-во интервалов
const unsigned short EepromModBusBd85Settings::QuantityOfIntervalDefault = 8;
// 7) Кол-во взгляда после
const unsigned short EepromModBusBd85Settings::QuantityOfLookDefault = 4;
// 8) Уровень тревоги 1 * 10
const unsigned short EepromModBusBd85Settings::LevelOfAlarm1Default = 80;
// 9) Уровень тревоги 2 * 10
const unsigned short EepromModBusBd85Settings::LevelOfAlarm2Default = 800;
 // 10) Уровень тревоги 3 * 30
const unsigned short EepromModBusBd85Settings::LevelOfAlarm3Default = 8000;
// 11) Фон, с
const unsigned short EepromModBusBd85Settings::PhonDefault = 100;
 // 12) Длит. подинтервала фона, мс
const unsigned short EepromModBusBd85Settings::DurationOfPhonDefault = 1000;
// 13) Длит. сигнала тревоги, с
const unsigned short EepromModBusBd85Settings::DurationOfAlarmDefault = 7;
 // 14) Длит. сигнала видео
const unsigned short EepromModBusBd85Settings::DurationOfVideoDefault = 7;
//---------------------------------------------------------------------------
void EepromModBusBd85Settings::Copy( EepromModBusBd85Settings & data )
{
    NumberOfBd = data.NumberOfBd; // 1) Номер БД
    Exposition = data.Exposition; // 2) Экспозиция, мс
    MinimumCount = data.MinimumCount; // 3) Минимальный счёт
    MaximumCount = data.MaximumCount; // 4) Максимальный счёт
    LevelOfOverload = data.LevelOfOverload; // 5) Уровень перегрузки
    QuantityOfInterval = data.QuantityOfInterval; // 6) Кол-во интервалов
    QuantityOfLook = data.QuantityOfLook; // 7) Кол-во взгляда после
    LevelOfAlarm1 = data.LevelOfAlarm1; // 8) Уровень тревоги 1 * 10
    LevelOfAlarm2 = data.LevelOfAlarm2; // 9) Уровень тревоги 2 * 10
    LevelOfAlarm3 = data.LevelOfAlarm3; // 10) Уровень тревоги 3 * 10
    Phon = data.Phon; // 11) Фон, с
    DurationOfPhon = data.DurationOfPhon; // 12) Длит. подинтервала фона, мс
    DurationOfAlarm = data.DurationOfAlarm; // 13) Длит. сигнала тревоги, с
    DurationOfVideo = data.DurationOfVideo; // 14) Длит. сигнала видео, с
}
//---------------------------------------------------------------------------
bool EepromModBusBd85Settings::NotEqual( EepromModBusBd85Settings & data )
{
    bool flagEqual = true;
    // Отметить, если два поля не эквивалентны
    MarkIfNotEqual( flagEqual, NumberOfBd, data.NumberOfBd ); // 1) Номер БД
    MarkIfNotEqual( flagEqual, Exposition, data.Exposition ); // 2) Экспозиция, мс
    MarkIfNotEqual( flagEqual, MinimumCount, data.MinimumCount ); // 3) Минимальный счёт
    MarkIfNotEqual( flagEqual, MaximumCount, data.MaximumCount ); // 4) Максимальный счёт
    MarkIfNotEqual( flagEqual, LevelOfOverload, data.LevelOfOverload ); // 5) Уровень перегрузки
    MarkIfNotEqual( flagEqual, QuantityOfInterval, data.QuantityOfInterval ); // 6) Кол-во интервалов
    MarkIfNotEqual( flagEqual, QuantityOfLook, data.QuantityOfLook ); // 7) Кол-во взгляда после
    MarkIfNotEqual( flagEqual, LevelOfAlarm1, data.LevelOfAlarm1 ); // 8) Уровень тревоги 1 * 10
    MarkIfNotEqual( flagEqual, LevelOfAlarm2, data.LevelOfAlarm2 ); // 9) Уровень тревоги 2 * 10
    MarkIfNotEqual( flagEqual, LevelOfAlarm3, data.LevelOfAlarm3 ); // 10) Уровень тревоги 3 * 10
    MarkIfNotEqual( flagEqual, Phon, data.Phon ); // 11) Фон, с
    MarkIfNotEqual( flagEqual, DurationOfPhon, data.DurationOfPhon ); // 12) Длит. подинтервала фона, мс
    MarkIfNotEqual( flagEqual, DurationOfAlarm, data.DurationOfAlarm ); // 13) Длит. сигнала тревоги, с
    MarkIfNotEqual( flagEqual, DurationOfVideo, data.DurationOfVideo ); // 14) Длит. сигнала видео, с
    return !flagEqual;
}
//---------------------------------------------------------------------------
void EepromModBusBd85Settings::MarkIfNotEqual( bool & flagEqual, int arg1, int arg2  )
{
    flagEqual = flagEqual && ( arg1 == arg2 );
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
