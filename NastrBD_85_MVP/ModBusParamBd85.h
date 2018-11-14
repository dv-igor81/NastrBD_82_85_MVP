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
    void ActionIfEvent(); // ��������, ���� �������

    unsigned long GetNumberOfBd(); // 1) ����� �����
    unsigned long GetExposition(); // 2) ����������, ��
    unsigned long GetMinimumCount(); // 3) ����������� ����
    unsigned long GetMaximumCount(); // 4) ������������ ����
    unsigned long GetLevelOfOverload(); // 5) ������� ����������
    unsigned long GetQuantityOfInterval(); // 6) ���-�� ����������
    unsigned long GetQuantityOfLook(); // 7) ���-�� ������� �����
    unsigned long GetLevelOfAlarm1(); // 8) ������� ������� 1 * 10
    unsigned long GetLevelOfAlarm2(); // 9) ������� ������� 2 * 10
    unsigned long GetLevelOfAlarm3(); // 10) ������� ������� 3 * 10
    unsigned long GetPhon(); // 11) ���, �
    unsigned long GetDurationOfPhon(); // 12) ����. ������������ ����, ��
    unsigned long GetDurationOfAlarm(); // 13) ����. ������� �������, �
    unsigned long GetDurationOfVideo(); // 14) ����. ������� �����
private:
    enum { regCount = 14 };

    unsigned long _numberOfBd; // 1) ����� �����
    unsigned long _exposition; // 2) ����������, ��
    unsigned long _minimumCount; // 3) ����������� ����
    unsigned long _maximumCount; // 4) ������������ ����
    unsigned long _levelOfOverload; // 5) ������� ����������
    unsigned long _quantityOfInterval; // 6) ���-�� ����������
    unsigned long _quantityOfLook; // 7) ���-�� ������� �����
    unsigned long _levelOfAlarm1; // 8) ������� ������� 1 * 10
    unsigned long _levelOfAlarm2; // 9) ������� ������� 2 * 10
    unsigned long _levelOfAlarm3; // 10) ������� ������� 3 * 10
    unsigned long _phon; // 11) ���, �
    unsigned long _durationOfPhon; // 12) ����. ������������ ����, ��
    unsigned long _durationOfAlarm; // 13) ����. ������� �������, �
    unsigned long _durationOfVideo; // 14) ����. ������� �����

private:
    static const unsigned short _expositionDefault; // 2) ����������, ��
    static const unsigned short _minimumCountDefault; // 3) ����������� ����
    static const unsigned short _maximumCountDefault; // 4) ������������ ����
    static const unsigned short _levelOfOverloadDefault; // 5) ������� ����������
    static const unsigned short _quantityOfIntervalDefault; // 6) ���-�� ����������
    static const unsigned short _quantityOfLookDefault;// 7) ���-�� ������� �����
    static const unsigned short _levelOfAlarm1Default; // 8) ������� ������� 1 * 10
    static const unsigned short _levelOfAlarm2Default; // 9) ������� ������� 2 * 10
    static const unsigned short _levelOfAlarm3Default; // 10) ������� ������� 3 * 10
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
    static const unsigned short _levelOfAlarm3MemoryAddr; // 10) ������� ������� 3 * 10
    static const unsigned short _phonMemoryAddr; // 11) ���, �
    static const unsigned short _durationOfPhonMemoryAddr; // 12) ����. ������������ ����, ��
    static const unsigned short _durationOfAlarmMemoryAddr; // 13) ����. ������� �������, �
    static const unsigned short _durationOfVideoMemoryAddr; // 14) ����. ������� �����

    unsigned short _addrRegModBus[regCount];
    unsigned long * _paramModBus[regCount]; // ������ ����������

    //  ������ ���������� �� "��������"
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
    //===>> ��������� ModBus
    void Create(); // ������� ������
    void Destroy(); // ��������� ������
    void InitAddrRegModBus();
    void InitParamModBus();
    void InitReadDelegate();

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
    // 10) ������� ������� 3 * 10
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
    //<<=== ��������� ModBus

    // �� ���������
    ActionSelf<>* as_ButtonModBusSetDefClick;
    void ButtonModBusSetDefClick();
    // ������
    ActionSelf<>* as_ButtonModBusWriteClick;
    void ButtonModBusWriteClick();
    // ������� �� ������ �������
    ActionSelf<int>* as_ActivePageIndexChange;
    void ActivePageIndexChange(int api);

    //<<=== ������� ������ � ������ ���������
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
    //===>> ������� ������ � ������ ���������

};
//---------------------------------------------------------------------------
#endif
