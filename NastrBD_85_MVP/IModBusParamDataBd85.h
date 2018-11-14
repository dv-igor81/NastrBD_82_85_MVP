//---------------------------------------------------------------------------
#ifndef IModBusParamDataBd85H
#define IModBusParamDataBd85H
//---------------------------------------------------------------------------
class IModBusParamDataBd85
{
public:
    virtual unsigned long GetNumberOfBd() = 0; // 1) Номер блока
    virtual unsigned long GetExposition() = 0; // 2) Экспозиция, мс
    virtual unsigned long GetMinimumCount() = 0; // 3) Минимальный счёт
    virtual unsigned long GetMaximumCount() = 0; // 4) Максимальный счёт
    virtual unsigned long GetLevelOfOverload() = 0; // 5) Уровень перегрузки
    virtual unsigned long GetQuantityOfInterval() = 0; // 6) Кол-во интервалов
    virtual unsigned long GetQuantityOfLook() = 0; // 7) Кол-во взгляда после
    virtual unsigned long GetLevelOfAlarm1() = 0; // 8) Уровень тревоги 1 * 10
    virtual unsigned long GetLevelOfAlarm2() = 0; // 9) Уровень тревоги 2 * 10
    virtual unsigned long GetLevelOfAlarm3() = 0; // 10) Уровень тревоги 3 * 10
    virtual unsigned long GetPhon() = 0; // 11) Фон, с
    virtual unsigned long GetDurationOfPhon() = 0; // 12) Длит. подинтервала фона, мс
    virtual unsigned long GetDurationOfAlarm() = 0; // 13) Длит. сигнала тревоги, с
    virtual unsigned long GetDurationOfVideo() = 0; // 14) Длит. сигнала видео
};
//---------------------------------------------------------------------------
#endif
