//---------------------------------------------------------------------------
#ifndef IWindowMainBd85H
#define IWindowMainBd85H
//---------------------------------------------------------------------------
#include "ActionEvent.h"
using namespace smartevents;
//---------------------------------------------------------------------------
#include "HelperConnectFourBdProt.h"
#include "StartDataNewBd85.h"
#include "IterDataNewBd85.h"
#include "ScalingDataNewBd85.h"
//---------------------------------------------------------------------------
class IWindowMainBd85
{
public:
    //===>> Вместо GetSelf
    virtual void SetVerPoText(const char * text) = 0;
    //<<=== Вместо GetSelf

    virtual void Destroy() = 0;
    virtual ActionSelf<>* GetSelfShow() = 0;
    virtual ActionEvent<>* GetEventFormShow() = 0;
    virtual ActionEvent<>* GetEventFormClose() = 0;
    virtual ActionSelf<StartDataNewBd85*>* GetSelfDisplayStartData() = 0;
    virtual ActionSelf<IterDataNewBd85*>& GetSelfDisplayIterData() = 0;
    virtual ActionSelf<const char*>* GetSelfDisplayErrors() = 0;
    virtual HelperConnectFourBdProt* GetConnectFourBdProt() = 0;
    virtual ActionEvent<const char*>* GetEventButtonStartStopScalingClick() = 0;
    virtual ActionSelf<ScalingDataNewBd85*>& GetSelfDisplayScalingData() = 0;
    virtual ActionEvent<>& GetEventButtonClearScalingClick() = 0;

    //===>> Запись в EEPROM
    virtual ActionEvent<>& GetEventButtonWriteToEepromClick() = 0;
    virtual ActionEvent<const char*>& GetEventTextIndAddrZadChange() = 0;
    virtual ActionEvent<const char*>& GetEventTextGroupAdrZadChange() = 0;
    virtual ActionEvent<const char*>& GetEventTextDnuZadCodeChange() = 0;
    virtual ActionEvent<const char*>& GetEventTextVoltageHiZadChange() = 0;
    virtual ActionEvent<const char*>& GetEventTextWidthPwmZadChange() = 0;
    virtual ActionEvent<const char*>& GetEventTextOffsetPwmZadChange() = 0;
    virtual ActionEvent<const char*>& GetEventTextPeriodPwmZadChange() = 0;
    virtual ActionEvent<bool>& GetEventRadioButtonArchOnClick() = 0;
    virtual ActionEvent<bool>& GetEventRadioButtonArchOffClick() = 0;
    virtual ActionSelf<bool>& GetSelfDisplayNotSaveChanges() = 0;
    //<<=== Запись в EEPROM

    //===>> Параметры ModBus
    virtual ActionEvent<const char*>& GetEventMbParamNumberOfBdChange() = 0;
    virtual ActionEvent<const char*>& GetEventMbParamExpositionChange() = 0;
    virtual ActionEvent<const char*>& GetEventMbParamMinimumCountChange() = 0;
    virtual ActionEvent<const char*>& GetEventMbParamMaximumCountChange() = 0;
    virtual ActionEvent<const char*>& GetEventMbParamLevelOfOverloadChange() = 0;
    virtual ActionEvent<const char*>& GetEventMbParamQuantityOfIntervalChange() = 0;
    virtual ActionEvent<const char*>& GetEventMbParamQuantityOfLookChange() = 0;
    virtual ActionEvent<const char*>& GetEventMbParamLevelOfAlarm1Change() = 0;
    virtual ActionEvent<const char*>& GetEventMbParamLevelOfAlarm2Change() = 0;
    virtual ActionEvent<const char*>& GetEventMbParamLevelOfAlarm3Change() = 0;
    virtual ActionEvent<const char*>& GetEventMbParamPhonChange() = 0;
    virtual ActionEvent<const char*>& GetEventMbParamDurationOfPhonChange() = 0;
    virtual ActionEvent<const char*>& GetEventMbParamDurationOfAlarmChange() = 0;
    virtual ActionEvent<const char*>& GetEventMbParamDurationOfVideoChange() = 0;
    virtual ActionEvent<>& GetEventButtonModBusSetDefClick() = 0;
    virtual ActionEvent<>& GetEventButtonModBusWriteClick() = 0;
    //<<=== Параметры ModBus
};
//---------------------------------------------------------------------------
#endif
