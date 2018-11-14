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
    Create(); // ������� ������
}
//---------------------------------------------------------------------------
ModBusParamBd85::~ModBusParamBd85()
{
    Destroy(); // ��������� ������
}
//---------------------------------------------------------------------------
const unsigned short ModBusParamBd85::_expositionDefault = 250; // 2) ����������, ��
const unsigned short ModBusParamBd85::_minimumCountDefault = 10; // 3) ����������� ����                                                                                                 1
const unsigned short ModBusParamBd85::_maximumCountDefault = 1000; // 4) ������������ ����
const unsigned short ModBusParamBd85::_levelOfOverloadDefault = 10000; // 5) ������� ����������
const unsigned short ModBusParamBd85::_quantityOfIntervalDefault = 8; // 6) ���-�� ����������
const unsigned short ModBusParamBd85::_quantityOfLookDefault = 4;// 7) ���-�� ������� �����
const unsigned short ModBusParamBd85::_levelOfAlarm1Default = 80; // 8) ������� ������� 1 * 10
const unsigned short ModBusParamBd85::_levelOfAlarm2Default = 800; // 9) ������� ������� 2 * 10
const unsigned short ModBusParamBd85::_levelOfAlarm3Default = 8000; // 10) ������� ������� 3 * 30
const unsigned short ModBusParamBd85::_phonDefault = 100; // 11) ���, �
const unsigned short ModBusParamBd85::_durationOfPhonDefault = 1000; // 12) ����. ������������ ����, ��
const unsigned short ModBusParamBd85::_durationOfAlarmDefault = 7; // 13) ����. ������� �������, �
const unsigned short ModBusParamBd85::_durationOfVideoDefault = 7; // 14) ����. ������� �����
//---------------------------------------------------------------------------
const unsigned short ModBusParamBd85::_numberOfBdMemoryAddr = 10; // 1) ����� �����
const unsigned short ModBusParamBd85::_expositionMemoryAddr = 0x300+2; // 2) ����������, ��
const unsigned short ModBusParamBd85::_minimumCountMemoryAddr = 0x300+3; // 3) ����������� ����
const unsigned short ModBusParamBd85::_maximumCountMemoryAddr = 0x300+4; // 4) ������������ ����
const unsigned short ModBusParamBd85::_levelOfOverloadMemoryAddr = 0x300+5; // 5) ������� ����������
const unsigned short ModBusParamBd85::_quantityOfIntervalMemoryAddr = 0x300+6; // 6) ���-�� ����������
const unsigned short ModBusParamBd85::_quantityOfLookMemoryAddr = 0x300+7;// 7) ���-�� ������� �����
const unsigned short ModBusParamBd85::_levelOfAlarm1MemoryAddr = 0x300+8; // 8) ������� ������� 1 * 10
const unsigned short ModBusParamBd85::_levelOfAlarm2MemoryAddr = 0x300+9; // 9) ������� ������� 2 * 10
const unsigned short ModBusParamBd85::_levelOfAlarm3MemoryAddr = 0x300+10; // 10) ������� ������� 3 * 30
const unsigned short ModBusParamBd85::_phonMemoryAddr = 0x300+11; // 11) ���, �
const unsigned short ModBusParamBd85::_durationOfPhonMemoryAddr = 18; // 12) ����. ������������ ����, ��
const unsigned short ModBusParamBd85::_durationOfAlarmMemoryAddr = 0x300 + 12; // 13) ����. ������� �������, �
const unsigned short ModBusParamBd85::_durationOfVideoMemoryAddr = 0x300 + 13; // 14) ����. ������� �����
//---------------------------------------------------------------------------
void ModBusParamBd85::Create() // ������� ������
{
    // 1) ����� �����
    as_MbParamNumberOfBdChange =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamNumberOfBdChange);
    _container->ev_NumberOfBdChange += as_MbParamNumberOfBdChange;
    // 2) ����������, ��
    as_MbParamExpositionChange =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamExpositionChange);
    _container->ev_ExpositionChange += as_MbParamExpositionChange;
    // 3) ����������� ����
    as_MbParamMinimumCountChange =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamMinimumCountChange);
    _container->ev_MinimumCountChange += as_MbParamMinimumCountChange;
    // 4) ������������ ����
    as_MbParamMaximumCountChange =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamMaximumCountChange);
    _container->ev_MaximumCountChange += as_MbParamMaximumCountChange;
    // 5) ������� ����������
    as_MbParamLevelOfOverloadChange =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamLevelOfOverloadChange);
    _container->ev_LevelOfOverloadChange += as_MbParamLevelOfOverloadChange;
    // 6) ���-�� ����������
    as_MbParamQuantityOfIntervalChange =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamQuantityOfIntervalChange);
    _container->ev_QuantityOfIntervalChange += as_MbParamQuantityOfIntervalChange;
    // 7) ���-�� ������� �����
    as_MbParamQuantityOfLookChange =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamQuantityOfLookChange);
    _container->ev_QuantityOfLookChange += as_MbParamQuantityOfLookChange;
    // 8) ������� ������� 1 * 10
    as_MbParamLevelOfAlarm1Change =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamLevelOfAlarm1Change);
    _container->ev_LevelOfAlarm_1Change += as_MbParamLevelOfAlarm1Change;
    // 9) ������� ������� 2 * 10
    as_MbParamLevelOfAlarm2Change =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamLevelOfAlarm2Change);
    _container->ev_LevelOfAlarm_2Change += as_MbParamLevelOfAlarm2Change;
    // 10) ������� ������� 3 * 30
    as_MbParamLevelOfAlarm3Change =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamLevelOfAlarm3Change);
    _container->ev_LevelOfAlarm_3Change += as_MbParamLevelOfAlarm3Change;
    // 11) ���, �
    as_MbParamPhonChange =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamPhonChange);
    _container->ev_PhonChange += as_MbParamPhonChange;
    // 12) ����. ������������ ����, ��
    as_MbParamDurationOfPhonChange =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamDurationOfPhonChange);
    _container->ev_DurationOfPhonChange += as_MbParamDurationOfPhonChange;
    // 13) ����. ������� �������, �
    as_MbParamDurationOfAlarmChange =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamDurationOfAlarmChange);
    _container->ev_DurationOfAlarmChange += as_MbParamDurationOfAlarmChange;
    // 14) ����. ������� �����
    as_MbParamDurationOfVideoChange =
        new ActionSelf<const char*>(this, &ModBusParamBd85::MbParamDurationOfVideoChange);
    _container->ev_DurationOfVideoChange += as_MbParamDurationOfVideoChange;
    // 15) �� ���������
    as_ButtonModBusSetDefClick =
        new ActionSelf<>(this, &ModBusParamBd85::ButtonModBusSetDefClick);
    _container->ev_SetDefClick += as_ButtonModBusSetDefClick;
    // 16) ������
    as_ButtonModBusWriteClick =
        new ActionSelf<>(this, &ModBusParamBd85::ButtonModBusWriteClick);
    _container->ev_WriteClick += as_ButtonModBusWriteClick;
}
//---------------------------------------------------------------------------
void ModBusParamBd85::Destroy() // ��������� ������
{
    delete as_MbParamNumberOfBdChange; // 1) ����� �����
    delete as_MbParamExpositionChange; // 2) ����������, ��
    delete as_MbParamMinimumCountChange; // 3) ����������� ����
    delete as_MbParamMaximumCountChange; // 4) ������������ ����
    delete as_MbParamLevelOfOverloadChange; // 5) ������� ����������
    delete as_MbParamQuantityOfIntervalChange; // 6) ���-�� ����������
    delete as_MbParamQuantityOfLookChange; // 7) ���-�� ������� �����
    delete as_MbParamLevelOfAlarm1Change; // 8) ������� ������� 1 * 10
    delete as_MbParamLevelOfAlarm2Change; // 9) ������� ������� 2 * 10
    delete as_MbParamLevelOfAlarm3Change; // 10) ������� ������� 3 * 30
    delete as_MbParamPhonChange; // 11) ���, �
    delete as_MbParamDurationOfPhonChange; // 12) ����. ������������ ����, ��
    delete as_MbParamDurationOfAlarmChange; // 13) ����. ������� �������, �
    delete as_MbParamDurationOfVideoChange; // 14) ����. ������� �����
    delete as_ButtonModBusSetDefClick; // 15) �� ���������
    delete as_ButtonModBusWriteClick; // 16) ������
}
//---------------------------------------------------------------------------
void ModBusParamBd85::ActionIfEvent() // ��������, ���� �������
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
