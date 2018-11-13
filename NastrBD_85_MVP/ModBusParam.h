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
    //unsigned short GetNumberOfBd(); // ����� �����
private:
    void SetAnyParam();
    unsigned short _numberOfBd; // ����� �����
    /*unsigned short _ // ����������, ��
    unsigned short _ // ����������� ����
    unsigned short _ // ������������ ����
    unsigned short _ // ������� ����������
    unsigned short _ // ���-�� ����������
    unsigned short _ // ���-�� ������� �����
    unsigned short _ // ������� ������� 1 * 10
    unsigned short _ // ������� ������� 2 * 10
    unsigned short _ // ������� ������� 3 * 30
    unsigned short _ // ���, �
    unsigned short _ // ����. ������������ ����, ��
    unsigned short _ // ����. ������� �������, �
    unsigned short _ // ����. ������� �����
    */
private:
    //static const unsigned short _numberOfBdDefault; // ����� �����
private:
    IAllProtokolS * _protokol;
    ModBusEventContainer * _container;
    //===>> ��������� ModBus
    void Create(); // ������� ������
    void Destroy(); // ��������� ������

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
    //<<=== ��������� ModBus
};
//---------------------------------------------------------------------------
#endif
