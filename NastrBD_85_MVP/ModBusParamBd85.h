//---------------------------------------------------------------------------
#ifndef ModBusParamBd85H
#define ModBusParamBd85H
//---------------------------------------------------------------------------
#include "IAllProtokolS.h"
#include "ModBusEventContainer.h"
#include "ITask.h"
//---------------------------------------------------------------------------
class ModBusParamBd85 {
public:
    ModBusParamBd85(
        IAllProtokolS * protokol,
        ModBusEventContainer * container,
        ITask * task);
    ~ModBusParamBd85();
    void ActionIfEvent(); // Действие, если событие
private:
    void SetAnyParam();
    unsigned short _numberOfBd; // 1) Номер блока
    unsigned short _exposition; // 2) Экспозиция, мс
    unsigned short _minimumCount; // 3) Минимальный счёт
    unsigned short _maximumCount; // 4) Максимальный счёт
    unsigned short _levelOfOverload; // 5) Уровень перегрузки
    unsigned short _quantityOfInterval; // 6) Кол-во интервалов
    unsigned short _quantityOfLook; // 7) Кол-во взгляда после
    unsigned short _levelOfAlarm1; // 8) Уровень тревоги 1 * 10
    unsigned short _levelOfAlarm2; // 9) Уровень тревоги 2 * 10
    unsigned short _levelOfAlarm3; // 10) Уровень тревоги 3 * 30
    unsigned short _phon; // 11) Фон, с
    unsigned short _durationOfPhon; // 12) Длит. подинтервала фона, мс
    unsigned short _durationOfAlarm; // 13) Длит. сигнала тревоги, с
    unsigned short _durationOfVideo; // 14) Длит. сигнала видео

private:
    static const unsigned short _expositionDefault; // 2) Экспозиция, мс
    static const unsigned short _minimumCountDefault; // 3) Минимальный счёт
    static const unsigned short _maximumCountDefault; // 4) Максимальный счёт
    static const unsigned short _levelOfOverloadDefault; // 5) Уровень перегрузки
    static const unsigned short _quantityOfIntervalDefault; // 6) Кол-во интервалов
    static const unsigned short _quantityOfLookDefault;// 7) Кол-во взгляда после
    static const unsigned short _levelOfAlarm1Default; // 8) Уровень тревоги 1 * 10
    static const unsigned short _levelOfAlarm2Default; // 9) Уровень тревоги 2 * 10
    static const unsigned short _levelOfAlarm3Default; // 10) Уровень тревоги 3 * 30
    static const unsigned short _phonDefault; // 11) Фон, с
    static const unsigned short _durationOfPhonDefault; // 12) Длит. подинтервала фона, мс
    static const unsigned short _durationOfAlarmDefault; // 13) Длит. сигнала тревоги, с
    static const unsigned short _durationOfVideoDefault; // 14) Длит. сигнала видео

    static const unsigned short _numberOfBdMemoryAddr; // 1) Номер блока
    static const unsigned short _expositionMemoryAddr; // 2) Экспозиция, мс
    static const unsigned short _minimumCountMemoryAddr; // 3) Минимальный счёт
    static const unsigned short _maximumCountMemoryAddr; // 4) Максимальный счёт
    static const unsigned short _levelOfOverloadMemoryAddr; // 5) Уровень перегрузки
    static const unsigned short _quantityOfIntervalMemoryAddr; // 6) Кол-во интервалов
    static const unsigned short _quantityOfLookMemoryAddr;// 7) Кол-во взгляда после
    static const unsigned short _levelOfAlarm1MemoryAddr; // 8) Уровень тревоги 1 * 10
    static const unsigned short _levelOfAlarm2MemoryAddr; // 9) Уровень тревоги 2 * 10
    static const unsigned short _levelOfAlarm3MemoryAddr; // 10) Уровень тревоги 3 * 30
    static const unsigned short _phonMemoryAddr; // 11) Фон, с
    static const unsigned short _durationOfPhonMemoryAddr; // 12) Длит. подинтервала фона, мс
    static const unsigned short _durationOfAlarmMemoryAddr; // 13) Длит. сигнала тревоги, с
    static const unsigned short _durationOfVideoMemoryAddr; // 14) Длит. сигнала видео

    unsigned short _addrRegModBus[14];
private:
    IAllProtokolS * _protokol;
    ModBusEventContainer * _container;
    ITask * _task;
    //===>> Параметры ModBus
    void Create(); // Создать объект
    void Destroy(); // Разрушить объект
    void InitAddrRegModBus();

    // 1) Номер блока
    ActionSelf<const char*>* as_MbParamNumberOfBdChange;
    void MbParamNumberOfBdChange(const char* text);
    // 2) Экспозиция, мс
    ActionSelf<const char*>* as_MbParamExpositionChange;
    void MbParamExpositionChange(const char* text);
    // 3) Минимальный счёт
    ActionSelf<const char*>* as_MbParamMinimumCountChange;
    void MbParamMinimumCountChange(const char* text);
    // 4) Максимальный счёт
    ActionSelf<const char*>* as_MbParamMaximumCountChange;
    void MbParamMaximumCountChange(const char* text);
    // 5) Уровень перегрузки
    ActionSelf<const char*>* as_MbParamLevelOfOverloadChange;
    void MbParamLevelOfOverloadChange(const char* text);
    // 6) Кол-во интервалов
    ActionSelf<const char*>* as_MbParamQuantityOfIntervalChange;
    void MbParamQuantityOfIntervalChange(const char* text);
    // 7) Кол-во взгляда после
    ActionSelf<const char*>* as_MbParamQuantityOfLookChange;
    void MbParamQuantityOfLookChange(const char* text);
    // 8) Уровень тревоги 1 * 10
    ActionSelf<const char*>* as_MbParamLevelOfAlarm1Change;
    void MbParamLevelOfAlarm1Change(const char* text);
    // 9) Уровень тревоги 2 * 10
    ActionSelf<const char*>* as_MbParamLevelOfAlarm2Change;
    void MbParamLevelOfAlarm2Change(const char* text);
    // 10) Уровень тревоги 3 * 30
    ActionSelf<const char*>* as_MbParamLevelOfAlarm3Change;
    void MbParamLevelOfAlarm3Change(const char* text);
    // 11) Фон, с
    ActionSelf<const char*>* as_MbParamPhonChange;
    void MbParamPhonChange(const char* text);
    // 12) Длит. подинтервала фона, мс
    ActionSelf<const char*>* as_MbParamDurationOfPhonChange;
    void MbParamDurationOfPhonChange(const char* text);
    // 13) Длит. сигнала тревоги, с
    ActionSelf<const char*>* as_MbParamDurationOfAlarmChange;
    void MbParamDurationOfAlarmChange(const char* text);
    // 14) Длит. сигнала видео
    ActionSelf<const char*>* as_MbParamDurationOfVideoChange;
    void MbParamDurationOfVideoChange(const char* text);
    // По умолчанию
    ActionSelf<>* as_ButtonModBusSetDefClick;
    void ButtonModBusSetDefClick();
    // Запись
    ActionSelf<>* as_ButtonModBusWriteClick;
    void ButtonModBusWriteClick();
    //<<=== Параметры ModBus
};
//---------------------------------------------------------------------------
#endif
