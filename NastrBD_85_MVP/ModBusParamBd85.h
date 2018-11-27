//---------------------------------------------------------------------------
#ifndef ModBusParamBd85H
#define ModBusParamBd85H
//---------------------------------------------------------------------------
#include "IAllProtokolS.h"
#include "ModBusEventContainerBd85.h"
#include "ITask.h"
#include "TaskWithParam.h"
#include "ModBusTextDataBd85.h"
#include "IWindowMainBd85.h"
#include "EepromModBusBd85Settings.h"
//---------------------------------------------------------------------------
class ModBusParamBd85
{
public:
    ModBusParamBd85(
        IAllProtokolS * protokol,
        IWindowMainBd85 * view,
        TaskWithParam * task);

    ~ModBusParamBd85();
private:
    IAllProtokolS * _protokol;
    ModBusEventContainerBd85 * _container;
    TaskWithParam * _task;
    IWindowMainBd85 * _view;

public:
    void ActionIfEventIter(); // Действие, если событие
    void ActionStart(); // Действие, при старте
    EepromModBusBd85Settings _modBusSaved; // Сохранённое в EEPROM состояние
    EepromModBusBd85Settings _modBusChange; // Текущее изменённое состояние
    EepromModBusBd85Settings _modBusPrev; // Предидущее изменённое состояние

private:
    enum { regCount = 14 };

    ModBusTextDataBd85 * _textData;
    //===>> Отобразить данные
    void DisplayReadReg( ModBusTextDataBd85 ** data );
    ActionSelf<ModBusTextDataBd85**>* as_DisplayReadReg;
    //<<=== Отобразить данные
    //===>> Отобразить состояние данных (изменены или нет)
    void DisplayNotSaveChanges( bool display );
    ActionSelf<bool>* as_DisplayNotSaveChanges;
    //<<=== Отобразить состояние данных (изменены или нет)

    void DisplayChange(
        bool updataText, // true - обновить текстовые данные
        bool inSecondThread, // true - функция запущена во вторичном потоке
        ModBusTextDataBd85 *& data );

private:
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
    unsigned short * _paramModBusRead[regCount]; // Массив указателей
    unsigned short * _paramModBusWrite[regCount]; // Массив указателей

    //  Массив указателей на "делегаты"
    ActionSelf<unsigned short, unsigned short*, bool *>* ReadRegCurrent[regCount];

    //  Массив указателей на "делегаты"
    ActionSelf<unsigned short, unsigned short, bool *>* WriteRegCurrent[regCount];
    
    bool _bfNeedReadReg;
    void ReadRegIfNeed();
    bool _bfNeedWriteReg;
    void WriteRegIfNeed();
    void ReadReg();
    void WriteReg();
    bool _bfErrorReadReg;
    bool _bfErrorWriteReg;
    bool _textChangeIgnore;
private:
    //===>> Параметры ModBus
    void Create(); // Создать объект
    void Destroy(); // Разрушить объект
    void InitAddrRegModBus();
    void InitParamModBus();
    void Binding(
        unsigned short ** paramModBus,
        EepromModBusBd85Settings & data);
    void InitReadDelegate();
    void InitWriteDelegate();

    void ToNumber(
        const char * text,
        unsigned short * change,
        unsigned short * prev,
        int max);

    void ToNumber(
        const char * text,
        unsigned long * change,
        unsigned long * prev,
        int max);

    bool _bfChangeOld;
    bool _bfChangeCurr;

    bool _bfChangeEepromCurr;
    bool _bfChangeEepromOld;
    bool ChangeEepromData();


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
    ActionSelf<unsigned short, unsigned short*, bool*>* as_WrapReadFlashInvert;
    void WrapReadFlashInvert(
        unsigned short memoryAddr,
        unsigned short * data,
        bool * flagResult);

    ActionSelf<unsigned short, unsigned short*, bool*>* as_WrapReadFlash2;
    void WrapReadFlash2(
        unsigned short memoryAddr,
        unsigned short * data,
        bool * flagResult);

    ActionSelf<unsigned short, unsigned short, bool*>* as_WrapWriteFlashInvert;
    void WrapWriteFlashInvert(
        unsigned short memoryAddr,
        unsigned short data,
        bool * flagResult);

    ActionSelf<unsigned short, unsigned short, bool*>* as_WrapWriteFlash2;
    void WrapWriteFlash2(
        unsigned short memoryAddr,
        unsigned short data,
        bool * flagResult);
    //===>> Функции чтения и записи регистров

};
//---------------------------------------------------------------------------
#endif
