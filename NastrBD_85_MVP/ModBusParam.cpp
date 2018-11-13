//---------------------------------------------------------------------------
#pragma hdrstop
#include "ModBusParam.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
ModBusParam::ModBusParam(
    IAllProtokolS * protokol,
    ModBusEventContainer * container)
{
    _protokol = protokol;
    _container = container;
    Create(); // ������� ������
}
//---------------------------------------------------------------------------
ModBusParam::~ModBusParam()
{
    Destroy(); // ��������� ������
}
//---------------------------------------------------------------------------
//ModBusParam::_numberOfBdDefault = ; // ����� �����
//---------------------------------------------------------------------------
void ModBusParam::Create() // ������� ������
{
    // 1) ����� �����
    as_MbParamNumberOfBdChange = new ActionSelf<const char*>(this, &ModBusParam::MbParamNumberOfBdChange);
    _container->ev_NumberOfBdChange += as_MbParamNumberOfBdChange;
    // 2) ����������, ��
    as_MbParamExpositionChange = new ActionSelf<const char*>(this, &ModBusParam::MbParamExpositionChange);
    _container->ev_ExpositionChange += as_MbParamExpositionChange;
    // 3) ����������� ����
    as_MbParamMinimumCountChange = new ActionSelf<const char*>(this, &ModBusParam::MbParamMinimumCountChange);
    _container->ev_MinimumCountChange += as_MbParamMinimumCountChange;
    // 4) ������������ ����
    as_MbParamMaximumCountChange = new ActionSelf<const char*>(this, &ModBusParam::MbParamMaximumCountChange);
    _container->ev_MaximumCountChange += as_MbParamMaximumCountChange;
    // 5) ������� ����������
    as_MbParamLevelOfOverloadChange = new ActionSelf<const char*>(this, &ModBusParam::MbParamLevelOfOverloadChange);
    _container->ev_LevelOfOverloadChange += as_MbParamLevelOfOverloadChange;
    // 6) ���-�� ����������
    as_MbParamQuantityOfIntervalChange = new ActionSelf<const char*>(this, &ModBusParam::MbParamQuantityOfIntervalChange);
    _container->ev_QuantityOfIntervalChange += as_MbParamQuantityOfIntervalChange;
    // 7) ���-�� ������� �����
    as_MbParamQuantityOfLookChange = new ActionSelf<const char*>(this, &ModBusParam::MbParamQuantityOfLookChange);
    _container->ev_QuantityOfLookChange += as_MbParamQuantityOfLookChange;
    // 8) ������� ������� 1 * 10
    as_MbParamLevelOfAlarm1Change = new ActionSelf<const char*>(this, &ModBusParam::MbParamLevelOfAlarm1Change);
    _container->ev_LevelOfAlarm_1Change += as_MbParamLevelOfAlarm1Change;
    // 9) ������� ������� 2 * 10
    as_MbParamLevelOfAlarm2Change = new ActionSelf<const char*>(this, &ModBusParam::MbParamLevelOfAlarm2Change);
    _container->ev_LevelOfAlarm_2Change += as_MbParamLevelOfAlarm2Change;
    // 10) ������� ������� 3 * 30
    as_MbParamLevelOfAlarm3Change = new ActionSelf<const char*>(this, &ModBusParam::MbParamLevelOfAlarm3Change);
    _container->ev_LevelOfAlarm_3Change += as_MbParamLevelOfAlarm3Change;
    // 11) ���, �
    as_MbParamPhonChange = new ActionSelf<const char*>(this, &ModBusParam::MbParamPhonChange);
    _container->ev_PhonChange += as_MbParamPhonChange;
    // 12) ����. ������������ ����, ��
    as_MbParamDurationOfPhonChange = new ActionSelf<const char*>(this, &ModBusParam::MbParamDurationOfPhonChange);
    _container->ev_DurationOfPhonChange += as_MbParamDurationOfPhonChange;
    // 13) ����. ������� �������, �
    as_MbParamDurationOfAlarmChange = new ActionSelf<const char*>(this, &ModBusParam::MbParamDurationOfAlarmChange);
    _container->ev_DurationOfAlarmChange += as_MbParamDurationOfAlarmChange;
    // 14) ����. ������� �����
    as_MbParamDurationOfVideoChange = new ActionSelf<const char*>(this, &ModBusParam::MbParamDurationOfVideoChange);
    _container->ev_DurationOfVideoChange += as_MbParamDurationOfVideoChange;
    // 15) �� ���������
    as_ButtonModBusSetDefClick = new ActionSelf<>(this, &ModBusParam::ButtonModBusSetDefClick);
    _container->ev_SetDefClick += as_ButtonModBusSetDefClick;
    // 16) ������
    as_ButtonModBusWriteClick = new ActionSelf<>(this, &ModBusParam::ButtonModBusWriteClick);
    _container->ev_WriteClick += as_ButtonModBusWriteClick;
}
//---------------------------------------------------------------------------
void ModBusParam::Destroy() // ��������� ������
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
//_numberOfBdDefault
//---------------------------------------------------------------------------
//void ModBusParam::SetNumberOfBd( unsigned short numberOfBd )
//{
//    return & _numberOfBd;
///}
//---------------------------------------------------------------------------
//unsigned short ModBusParam::GetNumberOfBd() // ����� �����
//{
//    return _numberOfBd;
//}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void ModBusParam::MbParamNumberOfBdChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamExpositionChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamMinimumCountChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamMaximumCountChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamLevelOfOverloadChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamQuantityOfIntervalChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamQuantityOfLookChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamLevelOfAlarm1Change(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamLevelOfAlarm2Change(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamLevelOfAlarm3Change(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamPhonChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamDurationOfPhonChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamDurationOfAlarmChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::MbParamDurationOfVideoChange(const char* text)
{
}
//---------------------------------------------------------------------------
void ModBusParam::ButtonModBusSetDefClick()
{
}
//---------------------------------------------------------------------------
void ModBusParam::ButtonModBusWriteClick()
{
}
//---------------------------------------------------------------------------
