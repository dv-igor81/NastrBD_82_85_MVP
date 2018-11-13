//---------------------------------------------------------------------------
#ifndef ModBusParamH
#define ModBusParamH
//---------------------------------------------------------------------------
#include "IAllProtokolS.h"
#include "ModBusEventContainer.h"
//---------------------------------------------------------------------------
class ModBusParam {
public:
    ModBusParam(
        IAllProtokolS * protokol,
        ModBusEventContainer * container);
    ~ModBusParam();    
    //void SetNumberOfBd( unsigned short numberOfBd );
    //unsigned short GetNumberOfBd(); // Номер блока
private:
    void SetAnyParam();
    unsigned short _numberOfBd; // Номер блока
    /*unsigned short _ // Экспозиция, мс
    unsigned short _ // Минимальный счёт
    unsigned short _ // Максимальный счёт
    unsigned short _ // Уровень перегрузки
    unsigned short _ // Кол-во интервалов
    unsigned short _ // Кол-во взгляда после
    unsigned short _ // Уровень тревоги 1 * 10
    unsigned short _ // Уровень тревоги 2 * 10
    unsigned short _ // Уровень тревоги 3 * 30
    unsigned short _ // Фон, с
    unsigned short _ // Длит. подинтервала фона, мс
    unsigned short _ // Длит. сигнала тревоги, с
    unsigned short _ // Длит. сигнала видео
    */
private:
    //static const unsigned short _numberOfBdDefault; // Номер блока
private:
    IAllProtokolS * _protokol;
    ModBusEventContainer * _container;
    //===>> Параметры ModBus
    void Create(); // Создать объект
    void Destroy(); // Разрушить объект

    ActionSelf<const char*>* as_MbParamNumberOfBdChange;
    void MbParamNumberOfBdChange(const char* text);

    ActionSelf<const char*>* as_MbParamExpositionChange;
    void MbParamExpositionChange(const char* text);

    ActionSelf<const char*>* as_MbParamMinimumCountChange;
    void MbParamMinimumCountChange(const char* text);

    ActionSelf<const char*>* as_MbParamMaximumCountChange;
    void MbParamMaximumCountChange(const char* text);

    ActionSelf<const char*>* as_MbParamLevelOfOverloadChange;
    void MbParamLevelOfOverloadChange(const char* text);

    ActionSelf<const char*>* as_MbParamQuantityOfIntervalChange;
    void MbParamQuantityOfIntervalChange(const char* text);

    ActionSelf<const char*>* as_MbParamQuantityOfLookChange;
    void MbParamQuantityOfLookChange(const char* text);

    ActionSelf<const char*>* as_MbParamLevelOfAlarm1Change;
    void MbParamLevelOfAlarm1Change(const char* text);

    ActionSelf<const char*>* as_MbParamLevelOfAlarm2Change;
    void MbParamLevelOfAlarm2Change(const char* text);

    ActionSelf<const char*>* as_MbParamLevelOfAlarm3Change;
    void MbParamLevelOfAlarm3Change(const char* text);

    ActionSelf<const char*>* as_MbParamPhonChange;
    void MbParamPhonChange(const char* text);

    ActionSelf<const char*>* as_MbParamDurationOfPhonChange;
    void MbParamDurationOfPhonChange(const char* text);

    ActionSelf<const char*>* as_MbParamDurationOfAlarmChange;
    void MbParamDurationOfAlarmChange(const char* text);

    ActionSelf<const char*>* as_MbParamDurationOfVideoChange;
    void MbParamDurationOfVideoChange(const char* text);

    ActionSelf<>* as_ButtonModBusSetDefClick;
    void ButtonModBusSetDefClick();

    ActionSelf<>* as_ButtonModBusWriteClick;
    void ButtonModBusWriteClick();
    //<<=== Параметры ModBus
};
//---------------------------------------------------------------------------
#endif
