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
    void ActionIfEvent(); // ��������, ���� �������
private:
    void SetAnyParam();
    unsigned short _numberOfBd; // 1) ����� �����
    unsigned short _exposition; // 2) ����������, ��
    unsigned short _minimumCount; // 3) ����������� ����
    unsigned short _maximumCount; // 4) ������������ ����
    unsigned short _levelOfOverload; // 5) ������� ����������
    unsigned short _quantityOfInterval; // 6) ���-�� ����������
    unsigned short _quantityOfLook; // 7) ���-�� ������� �����
    unsigned short _levelOfAlarm1; // 8) ������� ������� 1 * 10
    unsigned short _levelOfAlarm2; // 9) ������� ������� 2 * 10
    unsigned short _levelOfAlarm3; // 10) ������� ������� 3 * 30
    unsigned short _phon; // 11) ���, �
    unsigned short _durationOfPhon; // 12) ����. ������������ ����, ��
    unsigned short _durationOfAlarm; // 13) ����. ������� �������, �
    unsigned short _durationOfVideo; // 14) ����. ������� �����

private:
    static const unsigned short _expositionDefault; // 2) ����������, ��
    static const unsigned short _minimumCountDefault; // 3) ����������� ����
    static const unsigned short _maximumCountDefault; // 4) ������������ ����
    static const unsigned short _levelOfOverloadDefault; // 5) ������� ����������
    static const unsigned short _quantityOfIntervalDefault; // 6) ���-�� ����������
    static const unsigned short _quantityOfLookDefault;// 7) ���-�� ������� �����
    static const unsigned short _levelOfAlarm1Default; // 8) ������� ������� 1 * 10
    static const unsigned short _levelOfAlarm2Default; // 9) ������� ������� 2 * 10
    static const unsigned short _levelOfAlarm3Default; // 10) ������� ������� 3 * 30
    static const unsigned short _phonDefault; // 11) ���, �
    static const unsigned short _durationOfPhonDefault; // 12) ����. ������������ ����, ��
    static const unsigned short _durationOfAlarmDefault; // 13) ����. ������� �������, �
    static const unsigned short _durationOfVideoDefault; // 14) ����. ������� �����

    static const unsigned short _numberOfBdMemoryAddr; // 1) ����� �����
    static const unsigned short _expositionMemoryAddr; // 2) ����������, ��
    static const unsigned short _minimumCountMemoryAddr; // 3) ����������� ����
    static const unsigned short _maximumCountMemoryAddr; // 4) ������������ ����
    static const unsigned short _levelOfOverloadMemoryAddr; // 5) ������� ����������
    static const unsigned short _quantityOfIntervalMemoryAddr; // 6) ���-�� ����������
    static const unsigned short _quantityOfLookMemoryAddr;// 7) ���-�� ������� �����
    static const unsigned short _levelOfAlarm1MemoryAddr; // 8) ������� ������� 1 * 10
    static const unsigned short _levelOfAlarm2MemoryAddr; // 9) ������� ������� 2 * 10
    static const unsigned short _levelOfAlarm3MemoryAddr; // 10) ������� ������� 3 * 30
    static const unsigned short _phonMemoryAddr; // 11) ���, �
    static const unsigned short _durationOfPhonMemoryAddr; // 12) ����. ������������ ����, ��
    static const unsigned short _durationOfAlarmMemoryAddr; // 13) ����. ������� �������, �
    static const unsigned short _durationOfVideoMemoryAddr; // 14) ����. ������� �����

    unsigned short _addrRegModBus[14];
private:
    IAllProtokolS * _protokol;
    ModBusEventContainer * _container;
    ITask * _task;
    //===>> ��������� ModBus
    void Create(); // ������� ������
    void Destroy(); // ��������� ������
    void InitAddrRegModBus();

    // 1) ����� �����
    ActionSelf<const char*>* as_MbParamNumberOfBdChange;
    void MbParamNumberOfBdChange(const char* text);
    // 2) ����������, ��
    ActionSelf<const char*>* as_MbParamExpositionChange;
    void MbParamExpositionChange(const char* text);
    // 3) ����������� ����
    ActionSelf<const char*>* as_MbParamMinimumCountChange;
    void MbParamMinimumCountChange(const char* text);
    // 4) ������������ ����
    ActionSelf<const char*>* as_MbParamMaximumCountChange;
    void MbParamMaximumCountChange(const char* text);
    // 5) ������� ����������
    ActionSelf<const char*>* as_MbParamLevelOfOverloadChange;
    void MbParamLevelOfOverloadChange(const char* text);
    // 6) ���-�� ����������
    ActionSelf<const char*>* as_MbParamQuantityOfIntervalChange;
    void MbParamQuantityOfIntervalChange(const char* text);
    // 7) ���-�� ������� �����
    ActionSelf<const char*>* as_MbParamQuantityOfLookChange;
    void MbParamQuantityOfLookChange(const char* text);
    // 8) ������� ������� 1 * 10
    ActionSelf<const char*>* as_MbParamLevelOfAlarm1Change;
    void MbParamLevelOfAlarm1Change(const char* text);
    // 9) ������� ������� 2 * 10
    ActionSelf<const char*>* as_MbParamLevelOfAlarm2Change;
    void MbParamLevelOfAlarm2Change(const char* text);
    // 10) ������� ������� 3 * 30
    ActionSelf<const char*>* as_MbParamLevelOfAlarm3Change;
    void MbParamLevelOfAlarm3Change(const char* text);
    // 11) ���, �
    ActionSelf<const char*>* as_MbParamPhonChange;
    void MbParamPhonChange(const char* text);
    // 12) ����. ������������ ����, ��
    ActionSelf<const char*>* as_MbParamDurationOfPhonChange;
    void MbParamDurationOfPhonChange(const char* text);
    // 13) ����. ������� �������, �
    ActionSelf<const char*>* as_MbParamDurationOfAlarmChange;
    void MbParamDurationOfAlarmChange(const char* text);
    // 14) ����. ������� �����
    ActionSelf<const char*>* as_MbParamDurationOfVideoChange;
    void MbParamDurationOfVideoChange(const char* text);
    // �� ���������
    ActionSelf<>* as_ButtonModBusSetDefClick;
    void ButtonModBusSetDefClick();
    // ������
    ActionSelf<>* as_ButtonModBusWriteClick;
    void ButtonModBusWriteClick();
    //<<=== ��������� ModBus
};
//---------------------------------------------------------------------------
#endif
