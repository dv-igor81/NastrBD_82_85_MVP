//---------------------------------------------------------------------------
#ifndef ModBusTextDataBd85H
#define ModBusTextDataBd85H
//---------------------------------------------------------------------------
#include "IModBusParamDataBd85.h"
//---------------------------------------------------------------------------
class ModBusTextDataBd85
{
public:
    ModBusTextDataBd85(IModBusParamDataBd85 * param);

    const char* GetNumberOfBd(); // 1) ����� �����
    const char* GetExposition(); // 2) ����������, ��
    const char* GetMinimumCount(); // 3) ����������� ����
    const char* GetMaximumCount(); // 4) ������������ ����
    const char* GetLevelOfOverload(); // 5) ������� ����������
    const char* GetQuantityOfInterval(); // 6) ���-�� ����������
    const char* GetQuantityOfLook(); // 7) ���-�� ������� �����
    const char* GetLevelOfAlarm1(); // 8) ������� ������� 1 * 10
    const char* GetLevelOfAlarm2(); // 9) ������� ������� 2 * 10
    const char* GetLevelOfAlarm3(); // 10) ������� ������� 3 * 10
    const char* GetPhon(); // 11) ���, �
    const char* GetDurationOfPhon(); // 12) ����. ������������ ����, ��
    const char* GetDurationOfAlarm(); // 13) ����. ������� �������, �
    const char* GetDurationOfVideo(); // 14) ����. ������� �����
private:
    enum { uLongTextSize = 11 }; // 10 ���� � ����������� ����
    char _numberOfBd[uLongTextSize]; // 1) ����� �����
    char _exposition[uLongTextSize]; // 2) ����������, ��
    char _minimumCount[uLongTextSize]; // 3) ����������� ����
    char _maximumCount[uLongTextSize]; // 4) ������������ ����
    char _levelOfOverload[uLongTextSize]; // 5) ������� ����������
    char _quantityOfInterval[uLongTextSize]; // 6) ���-�� ����������
    char _quantityOfLook[uLongTextSize]; // 7) ���-�� ������� �����
    char _levelOfAlarm1[uLongTextSize]; // 8) ������� ������� 1 * 10
    char _levelOfAlarm2[uLongTextSize]; // 9) ������� ������� 2 * 10
    char _levelOfAlarm3[uLongTextSize]; // 10) ������� ������� 3 * 10
    char _phon[uLongTextSize]; // 11) ���, �
    char _durationOfPhon[uLongTextSize]; // 12) ����. ������������ ����, ��
    char _durationOfAlarm[uLongTextSize]; // 13) ����. ������� �������, �
    char _durationOfVideo[uLongTextSize]; // 14) ����. ������� �����
};
//---------------------------------------------------------------------------
#endif
