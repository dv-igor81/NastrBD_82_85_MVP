//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include <stdio.h>
//---------------------------------------------------------------------------
#include "ModBusTextDataBd85.h"
#include "TextHelper.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
ModBusTextDataBd85::ModBusTextDataBd85()
{
    InsteadOfConstructor(); // ������ ������������
}
//---------------------------------------------------------------------------
ModBusTextDataBd85::ModBusTextDataBd85(
    EepromModBusBd85Settings * param)
{
    InsteadOfConstructor(); // ������ ������������
    sprintf( _numberOfBd, "%d", param->NumberOfBd );
    sprintf( _exposition, "%d", param->Exposition );
    sprintf( _minimumCount, "%d", param->MinimumCount );
    sprintf( _maximumCount, "%d", param->MaximumCount );
    sprintf( _levelOfOverload, "%d", param->LevelOfOverload );
    sprintf( _quantityOfInterval, "%d", param->QuantityOfInterval );
    sprintf( _quantityOfLook, "%d", param->QuantityOfLook );
    sprintf( _levelOfAlarm1, "%d", param->LevelOfAlarm1 );
    sprintf( _levelOfAlarm2, "%d", param->LevelOfAlarm2 );
    sprintf( _levelOfAlarm3, "%d", param->LevelOfAlarm3 );
    sprintf( _phon, "%d", param->Phon );
    sprintf( _durationOfPhon, "%d", param->DurationOfPhon );
    sprintf( _durationOfAlarm, "%d", param->DurationOfAlarm );
    sprintf( _durationOfVideo, "%d", param->DurationOfVideo );
}
//---------------------------------------------------------------------------
void ModBusTextDataBd85::InsteadOfConstructor() // ������ ������������
{
    // ��������� ��� ������� ������ ������
    TextHelper::SetCharInText(_numberOfBd, 0, uLongTextSize);
    TextHelper::SetCharInText(_exposition, 0, uLongTextSize);
    TextHelper::SetCharInText(_minimumCount, 0, uLongTextSize);
    TextHelper::SetCharInText(_maximumCount, 0, uLongTextSize);
    TextHelper::SetCharInText(_levelOfOverload, 0, uLongTextSize);
    TextHelper::SetCharInText(_quantityOfInterval, 0, uLongTextSize);
    TextHelper::SetCharInText(_quantityOfLook, 0, uLongTextSize);
    TextHelper::SetCharInText(_levelOfAlarm1, 0, uLongTextSize);
    TextHelper::SetCharInText(_levelOfAlarm2, 0, uLongTextSize);
    TextHelper::SetCharInText(_levelOfAlarm3, 0, uLongTextSize);
    TextHelper::SetCharInText(_phon, 0, uLongTextSize);
    TextHelper::SetCharInText(_durationOfPhon, 0, uLongTextSize);
    TextHelper::SetCharInText(_durationOfAlarm, 0, uLongTextSize);
    TextHelper::SetCharInText(_durationOfVideo, 0, uLongTextSize);                                                    
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetNumberOfBd() // 1) ����� �����
{
    return _numberOfBd;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetExposition() // 2) ����������, ��
{
    return _exposition;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetMinimumCount() // 3) ����������� ����
{
    return _minimumCount;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetMaximumCount() // 4) ������������ ����
{
    return _maximumCount;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetLevelOfOverload() // 5) ������� ����������
{
    return _levelOfOverload;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetQuantityOfInterval() // 6) ���-�� ����������
{
    return _quantityOfInterval;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetQuantityOfLook() // 7) ���-�� ������� �����
{
    return _quantityOfLook;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetLevelOfAlarm1() // 8) ������� ������� 1 * 10
{
    return _levelOfAlarm1;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetLevelOfAlarm2() // 9) ������� ������� 2 * 10
{
    return _levelOfAlarm2;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetLevelOfAlarm3() // 10) ������� ������� 3 * 10
{
    return _levelOfAlarm3;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetPhon() // 11) ���, �
{
    return _phon;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetDurationOfPhon() // 12) ����. ������������ ����, ��
{
    return _durationOfPhon;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetDurationOfAlarm() // 13) ����. ������� �������, �
{
    return _durationOfAlarm;
}
//---------------------------------------------------------------------------
const char* ModBusTextDataBd85::GetDurationOfVideo() // 14) ����. ������� �����
{
    return _durationOfVideo;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
