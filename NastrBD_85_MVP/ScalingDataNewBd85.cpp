//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include <stdio.h>
#include "ScalingDataNewBd85.h"
#include "TextHelper.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
ScalingDataNewBd85::ScalingDataNewBd85( int timeLimitScaling )
{
    TextHelper::SetCharInText(_currTimeScaling, 0, uShortTextSize);
    if ( timeLimitScaling > 0 )
    {
        _isWorkScalingSumm = true;
        _isStartWork = true;
        sprintf(_timeLimitScaling, "%d", timeLimitScaling);
    }
    else
    {
        _isWorkScalingSumm = false; // Завершение расчёта среднего счёта
        TextHelper::SetCharInText(_timeLimitScaling, 0, uShortTextSize);
    }
    TextHelper::SetCharInText(_currTimeScaling, 0, uShortTextSize);
    TextHelper::SetCharInText(_scalingCounterSumm, 0, floatTextSize);
    TextHelper::SetCharInText(_middleScaling, 0, floatTextSize);
}
//---------------------------------------------------------------------------
ScalingDataNewBd85::ScalingDataNewBd85(
    int timeLimitScaling
    , int currTimeScaling
    , double scalingCounterSumm
)
{
    _isStartWork = false; // Очередная итерация, а не начало работы
    if ( timeLimitScaling > 0 )
    {
        _isWorkScalingSumm = true;
    }
    else
    {
        _isWorkScalingSumm = false; // Завершение расчёта среднего счёта
    }
    sprintf(_currTimeScaling, "%d", currTimeScaling);
    sprintf(_scalingCounterSumm, "%0.0f", scalingCounterSumm);
    sprintf(_middleScaling, "%0.2f", scalingCounterSumm / currTimeScaling);
}
//---------------------------------------------------------------------------
bool ScalingDataNewBd85::GetWorkScalingSumm() // false - Завершить работу
{
    return _isWorkScalingSumm;
}
//---------------------------------------------------------------------------
bool ScalingDataNewBd85::GetStartWorkScalingSumm() // true - Начать работу
{
    return _isStartWork;
}
//---------------------------------------------------------------------------
const char* ScalingDataNewBd85::GetTimeMeteringLimit()
{
    return _timeLimitScaling;
}
//---------------------------------------------------------------------------
const char* ScalingDataNewBd85::GetTimeScaling()
{
    return _currTimeScaling;
}
//---------------------------------------------------------------------------
const char* ScalingDataNewBd85::GetTotalScaling()
{
    return _scalingCounterSumm;
}
//---------------------------------------------------------------------------
const char* ScalingDataNewBd85::GetMiddleScaling()
{
    return _middleScaling;
}
//---------------------------------------------------------------------------

