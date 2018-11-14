//---------------------------------------------------------------------------
#ifndef ModBusEventContainerH
#define ModBusEventContainerH
//---------------------------------------------------------------------------
#include "ActionEvent.h"
using namespace smartevents;
//---------------------------------------------------------------------------
class ModBusEventContainer
{
public:
    //===>> ��������� ModBus
    ActionEvent<const char*> ev_NumberOfBdChange; // ����� �����
    ActionEvent<const char*> ev_ExpositionChange; // ����������, ��
    ActionEvent<const char*> ev_MinimumCountChange; // ����������� ����
    ActionEvent<const char*> ev_MaximumCountChange; // ������������ ����
    ActionEvent<const char*> ev_LevelOfOverloadChange; // ������� ����������
    ActionEvent<const char*> ev_QuantityOfIntervalChange; // ���-�� ����������
    ActionEvent<const char*> ev_QuantityOfLookChange; // ���-�� ������� �����
    ActionEvent<const char*> ev_LevelOfAlarm_1Change; // ������� ������� 1 * 10
    ActionEvent<const char*> ev_LevelOfAlarm_2Change; // ������� ������� 2 * 10
    ActionEvent<const char*> ev_LevelOfAlarm_3Change; // ������� ������� 3 * 10
    ActionEvent<const char*> ev_PhonChange; // ���, �
    ActionEvent<const char*> ev_DurationOfPhonChange; // ����. ������������ ����, ��
    ActionEvent<const char*> ev_DurationOfAlarmChange; // ����. ������� �������
    ActionEvent<const char*> ev_DurationOfVideoChange; // ����. ������� �����
    ActionEvent<> ev_SetDefClick; // �� ���������
    ActionEvent<> ev_WriteClick; // ������
    //<<=== ��������� ModBus
};
//---------------------------------------------------------------------------
#endif