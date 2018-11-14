//---------------------------------------------------------------------------
#ifndef ModBusParamBd85H
#define ModBusParamBd85H
//---------------------------------------------------------------------------
#include "IAllProtokolS.h"
#include "ModBusEventContainerBd85.h"
#include "ITask.h"
#include "IModBusParamDataBd85.h"
#include "ModBusTextDataBd85.h"
#include "IWindowMainBd85.h"
//---------------------------------------------------------------------------
class ModBusParamBd85 : public IModBusParamDataBd85
{
public:
    ModBusParamBd85(
        IAllProtokolS * protokol,
        IWindowMainBd85 * view,
        ITask * task);
    ~ModBusParamBd85();
    void ActionIfEvent(); // Действие, если событие

    unsigned long GetNumberOfBd(); // 1) Номер блока
    unsigned long GetExposition(); // 2) Экспозиция, мс
    unsigned long GetMinimumCount(); // 3) Минимальный счёт
    unsigned long GetMaximumCount(); // 4) Максимальный счёт
    unsigned long GetLevelOfOverload(); // 5) Уровень перегрузки
    unsigned long GetQuantityOfInterval(); // 6) Кол-во интервалов
    unsigned long GetQuantityOfLook(); // 7) Кол-во взгляда после
    unsigned long GetLevelOfAlarm1(); // 8) Уровень тревоги 1 * 10
    unsigned long GetLevelOfAlarm2(); // 9) Уровень тревоги 2 * 10
    unsigned long GetLevelOfAlarm3(); // 10) Уровень тревоги 3 * 10
    unsigned long GetPhon(); // 11) Фон, с
    unsigned long GetDurationOfPhon(); // 12) Длит. подинтервала фона, мс
    unsigned long GetDurationOfAlarm(); // 13) Длит. сигнала тревоги, с
    unsigned long GetDurationOfVideo(); // 14) Длит. сигнала видео
private:
    enum { regCount = 14 };

    unsigned long _numberOfBd; // 1) Номер блока
    unsigned long _exposition; // 2) Экспозиция, мс
    unsigned long _minimumCount; // 3) Минимальный счёт
    unsigned long _maximumCount; // 4) Максимальный счёт
    unsigned long _levelOfOverload; // 5) Уровень перегрузки
    unsigned long _quantityOfInterval; // 6) Кол-во интервалов
    unsigned long _quantityOfLook; // 7) Кол-во взгляда после
    unsigned long _levelOfAlarm1; // 8) Уровень тревоги 1 * 10
    unsigned long _levelOfAlarm2; // 9) Уровень тревоги 2 * 10
    unsigned long _levelOfAlarm3; // 10) Уровень тревоги 3 * 10
    unsigned long _phon; // 11) Фон, с
    unsigned long _durationOfPhon; // 12) Длит. подинтервала фона, мс
    unsigned long _durationOfAlarm; // 13) Длит. сигнала тревоги, с
    unsigned long _durationOfVideo; // 14) Длит. сигнала видео

private:
    static const unsigned short _expositionDefault; // 2) Экспозиция, мс
    static const unsigned short _minimumCountDefault; // 3) Минимальный счёт
    static const unsigned short _maximumCountDefault; // 4) Максимальный счёт
    static const unsigned short _levelOfOverloadDefault; // 5) Уровень перегрузки
    static const unsigned short _quantityOfIntervalDefault; // 6) Кол-во интервалов
    static const unsigned short _quantityOfLookDefault;// 7) Кол-во взгляда после
    static const unsigned short _levelOfAlarm1Default; // 8) Уровень тревоги 1 * 10
    static const unsigned short _levelOfAlarm2Default; // 9) Уровень тревоги 2 * 10
    static const unsigned short _levelOfAlarm3Default; // 10) Уровень тревоги 3 * 10
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
    static const unsigned short _levelOfAlarm3MemoryAddr; // 10) Уровень тревоги 3 * 10
    static const unsigned short _phonMemoryAddr; // 11) Фон, с
    static const unsigned short _durationOfPhonMemoryAddr; // 12) Длит. подинтервала фона, мс
    static const unsigned short _durationOfAlarmMemoryAddr; // 13) Длит. сигнала тревоги, с
    static const unsigned short _durationOfVideoMemoryAddr; // 14) Длит. сигнала видео

    unsigned short _addrRegModBus[regCount];
    unsigned long * _paramModBus[regCount]; // Массив указателей

    //  Массив указателей на "делегаты"
    ActionSelf<unsigned short, unsigned long*, bool *>* ReadRegCurrent[regCount];
    
    bool _bfNeedReadReg;
    void ReadRegIfNeed();
    bool _bfNeedWriteReg;
    void WriteRegIfNeed();
    void ReadReg();


    void DisplayReadReg();
    ModBusTextDataBd85* _textData;
    ActionEvent<ModBusTextDataBd85*> ev_DisplayReadReg;
    ActionSelf<>* as_DisplayReadReg;

    bool _bfErrorReadReg;
private:
    IAllProtokolS * _protokol;
    ModBusEventContainerBd85 * _container;
    ITask * _task;
    IWindowMainBd85 * _view;
    //===>> Параметры ModBus
    void Create(); // Создать объект
    void Destroy(); // Разрушить объект
    void InitAddrRegModBus();
    void InitParamModBus();
    void InitReadDelegate();

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
    // 10) Уровень тревоги 3 * 10
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
    //<<=== Параметры ModBus

    // По умолчанию
    ActionSelf<>* as_ButtonModBusSetDefClick;
    void ButtonModBusSetDefClick();
    // Запись
    ActionSelf<>* as_ButtonModBusWriteClick;
    void ButtonModBusWriteClick();
    // Перешли на другую вкладку
    ActionSelf<int>* as_ActivePageIndexChange;
    void ActivePageIndexChange(int api);

    //<<=== Функции чтения и записи регистров
    ActionSelf<unsigned short, unsigned long*, bool*>* as_WrapReadFlashInvert;
    void WrapReadFlashInvert(
        unsigned short memoryAddr,
        unsigned long * data,
        bool * flagResult);

    ActionSelf<unsigned short, unsigned long*, bool*>* as_WrapReadFlash2;
    void WrapReadFlash2(
        unsigned short memoryAddr,
        unsigned long * data,
        bool * flagResult);

    ActionSelf<unsigned short, unsigned long, bool*>* as_WrapWriteFlashInvert;
    void WrapWriteFlashInvert(
        unsigned short memoryAddr,
        unsigned long data,
        bool * flagResult);

    ActionSelf<unsigned short, unsigned long, bool*>* as_WrapWriteFlash2;
    void WrapWriteFlash2(
        unsigned short memoryAddr,
        unsigned long data,
        bool * flagResult);
    //===>> Функции чтения и записи регистров

};
//---------------------------------------------------------------------------
#endif
