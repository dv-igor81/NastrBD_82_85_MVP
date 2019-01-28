//---------------------------------------------------------------------------
#ifndef ModBusEventContainerBd85H
#define ModBusEventContainerBd85H
//---------------------------------------------------------------------------
#include "ActionEvent.h"
using namespace smarteventsMin;
//---------------------------------------------------------------------------
class ModBusEventContainerBd85
{
public:
    //===>> Параметры ModBus
    ActionEvent<const char*> ev_NumberOfBdChange; // Номер блока
    ActionEvent<const char*> ev_ExpositionChange; // Экспозиция, мс
    ActionEvent<const char*> ev_MinimumCountChange; // Минимальный счёт
    ActionEvent<const char*> ev_MaximumCountChange; // Максимальный счёт
    ActionEvent<const char*> ev_LevelOfOverloadChange; // Уровень перегрузки
    ActionEvent<const char*> ev_QuantityOfIntervalChange; // Кол-во интервалов
    ActionEvent<const char*> ev_QuantityOfLookChange; // Кол-во взгляда после
    ActionEvent<const char*> ev_LevelOfAlarm_1Change; // Уровень тревоги 1 * 10
    ActionEvent<const char*> ev_LevelOfAlarm_2Change; // Уровень тревоги 2 * 10
    ActionEvent<const char*> ev_LevelOfAlarm_3Change; // Уровень тревоги 3 * 10
    ActionEvent<const char*> ev_PhonChange; // Фон, с
    ActionEvent<const char*> ev_DurationOfPhonChange; // Длит. подинтервала фона, мс
    ActionEvent<const char*> ev_DurationOfAlarmChange; // Длит. сигнала тревоги
    ActionEvent<const char*> ev_DurationOfVideoChange; // Длит. сигнала видео
    //<<=== Параметры ModBus
    ActionEvent<> ev_SetDefClick; // По умолчанию
    ActionEvent<> ev_WriteClick; // Запись
    ActionEvent<int> ev_ActivePageIndex; // Перешли на другую вкладку
};
//---------------------------------------------------------------------------
#endif
