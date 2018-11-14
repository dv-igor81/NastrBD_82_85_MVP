//---------------------------------------------------------------------------
#ifndef IModBusParamDataBd85H
#define IModBusParamDataBd85H
//---------------------------------------------------------------------------
class IModBusParamDataBd85
{
public:
    virtual unsigned long GetNumberOfBd() = 0; // 1) ����� �����
    virtual unsigned long GetExposition() = 0; // 2) ����������, ��
    virtual unsigned long GetMinimumCount() = 0; // 3) ����������� ����
    virtual unsigned long GetMaximumCount() = 0; // 4) ������������ ����
    virtual unsigned long GetLevelOfOverload() = 0; // 5) ������� ����������
    virtual unsigned long GetQuantityOfInterval() = 0; // 6) ���-�� ����������
    virtual unsigned long GetQuantityOfLook() = 0; // 7) ���-�� ������� �����
    virtual unsigned long GetLevelOfAlarm1() = 0; // 8) ������� ������� 1 * 10
    virtual unsigned long GetLevelOfAlarm2() = 0; // 9) ������� ������� 2 * 10
    virtual unsigned long GetLevelOfAlarm3() = 0; // 10) ������� ������� 3 * 10
    virtual unsigned long GetPhon() = 0; // 11) ���, �
    virtual unsigned long GetDurationOfPhon() = 0; // 12) ����. ������������ ����, ��
    virtual unsigned long GetDurationOfAlarm() = 0; // 13) ����. ������� �������, �
    virtual unsigned long GetDurationOfVideo() = 0; // 14) ����. ������� �����
};
//---------------------------------------------------------------------------
#endif
