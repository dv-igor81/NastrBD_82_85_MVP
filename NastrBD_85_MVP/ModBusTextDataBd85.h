//---------------------------------------------------------------------------
#ifndef ModBusTextDataBd85H
#define ModBusTextDataBd85H
//---------------------------------------------------------------------------
#include "IModBusParamDataBd85.h"
//---------------------------------------------------------------------------
class ModBusTextDataBd85
{
public:
    ModBusTextDataBd85(IModBusParamDataBd85 * param);

    const char* GetNumberOfBd(); // 1) Номер блока
    const char* GetExposition(); // 2) Экспозиция, мс
    const char* GetMinimumCount(); // 3) Минимальный счёт
    const char* GetMaximumCount(); // 4) Максимальный счёт
    const char* GetLevelOfOverload(); // 5) Уровень перегрузки
    const char* GetQuantityOfInterval(); // 6) Кол-во интервалов
    const char* GetQuantityOfLook(); // 7) Кол-во взгляда после
    const char* GetLevelOfAlarm1(); // 8) Уровень тревоги 1 * 10
    const char* GetLevelOfAlarm2(); // 9) Уровень тревоги 2 * 10
    const char* GetLevelOfAlarm3(); // 10) Уровень тревоги 3 * 10
    const char* GetPhon(); // 11) Фон, с
    const char* GetDurationOfPhon(); // 12) Длит. подинтервала фона, мс
    const char* GetDurationOfAlarm(); // 13) Длит. сигнала тревоги, с
    const char* GetDurationOfVideo(); // 14) Длит. сигнала видео
private:
    enum { uLongTextSize = 11 }; // 10 цифр и завершающий ноль
    char _numberOfBd[uLongTextSize]; // 1) Номер блока
    char _exposition[uLongTextSize]; // 2) Экспозиция, мс
    char _minimumCount[uLongTextSize]; // 3) Минимальный счёт
    char _maximumCount[uLongTextSize]; // 4) Максимальный счёт
    char _levelOfOverload[uLongTextSize]; // 5) Уровень перегрузки
    char _quantityOfInterval[uLongTextSize]; // 6) Кол-во интервалов
    char _quantityOfLook[uLongTextSize]; // 7) Кол-во взгляда после
    char _levelOfAlarm1[uLongTextSize]; // 8) Уровень тревоги 1 * 10
    char _levelOfAlarm2[uLongTextSize]; // 9) Уровень тревоги 2 * 10
    char _levelOfAlarm3[uLongTextSize]; // 10) Уровень тревоги 3 * 10
    char _phon[uLongTextSize]; // 11) Фон, с
    char _durationOfPhon[uLongTextSize]; // 12) Длит. подинтервала фона, мс
    char _durationOfAlarm[uLongTextSize]; // 13) Длит. сигнала тревоги, с
    char _durationOfVideo[uLongTextSize]; // 14) Длит. сигнала видео
};
//---------------------------------------------------------------------------
#endif
