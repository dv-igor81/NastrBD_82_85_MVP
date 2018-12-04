//---------------------------------------------------------------------------
#pragma hdrstop
#include "ModelSaveParamBd85.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
ModelSaveParamBd85::ModelSaveParamBd85(
    IAllProtokolS * allProtokol,
    ViewModelSaveParamBd85 * vmSaveParam,
    ConnectBdProt * connectBdProt)
{
    _allProtokol = allProtokol;
    _vmSaveParam = vmSaveParam;
    _connectBdProt = connectBdProt;
    _isWork = false;
    m_nT = 0;
    m_nN = 0;
    m_nZ = 0;
    ClearParam();
    CreateActions(); // Создать делегаты
    *_allProtokol->GetEventErrorCountIncrement() += as_DisplayErrors;
}
//---------------------------------------------------------------------------
ModelSaveParamBd85::~ModelSaveParamBd85()
{
    DestroyActions(); // Освободить память, от делегатов
}
//---------------------------------------------------------------------------
bool ModelSaveParamBd85::StartStopWork()
{
    if ( _isWork == false )
    {
        StartWork();
    }
    else
    {
        StopWork();    
    }
    return _isWork;
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::CreateActions() // Создать делегаты
{
    as_OprosIter = new ActionSelf<>(this, &ModelSaveParamBd85::OprosIter);
    as_DisplayErrors = new ActionSelf<const char*>(this, &ModelSaveParamBd85::DisplayErrors);
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::DestroyActions() // Освободить память, от делегатов
{
    delete as_OprosIter;
    delete as_DisplayErrors;
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::OprosIter()
{
    Sleep(5);
    if ( _allProtokol->GetSsp( & _ssp ) == false )
    {
        return;
    }
    if ( (_ssp & 0x01) != 0x01 ) // Флаг готовности счёта НЕ получен
    {
        return;
    }
    if ( _allProtokol->GetScaling( & _scaling ) == false )
    {
        return;
    }
    Calculate();
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::DisplayErrors(const char * text)
{
    _vmSaveParam->DisplayErrorsInvoke( text );
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::StartWork()
{
    if ( GetSummTime() <= 0 )
    {
        return;
    }
    ClearParam();
    _vmSaveParam->DisplayCurrTimeInvoke( _currTimeScaling );       
    _connectBdProt->SetActionOprosIter( as_OprosIter );
    switch ( _allProtokol->GetProtokolName() )
    {
    case ProtokolName_t::NineBit: // 9-ти битный
        _intervalQuantity = 5; // Количество подинтервалов в секунде
        break;
    case ProtokolName_t::ModBus_RTU: // ModBus RTU
    case ProtokolName_t::ModBus_TCP: // ModBus TCP
    case ProtokolName_t::ModBus_RTU_IP: // ModBus RTU (TCP/IP)
        _intervalQuantity = 4; // Количество подинтервалов в секунде
        break;
    }
    _isWork = true;
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::StopWork()
{
    _connectBdProt->SetActionOprosIter( 0 );
    _isWork = false;    
}
//---------------------------------------------------------------------------
unsigned int ModelSaveParamBd85::GetSummTime()
{
    unsigned int summTime = m_nT * m_nN + m_nZ * 60 * (m_nN - 1);
    return summTime;
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::ClearParam()
{
    _scaling = 0; // Счёт за подинтервал (200 мс для 9-битного, 250 для ModBus)
    _intervalQuantity = 0; // Количество подинтервалов, для интервала (секунды) (4 либо 5)
    _intervalCounter = 0; // Счётчик подинтервалов (0,1,2,3 или 0,1,2,3,4)
    _scalingCounterTmp = 0; // Для секундного счёта
    _scalingCounter = 0; // Для секундного счёта
    _currTimeScaling = 0; // Текущее время
    _scalingSumm = 0; // Счёт за время измерения
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::Calculate()
{
    _intervalCounter++; // Счетчик подинтервалов
    _scalingCounterTmp += _scaling; // _scalingCounter - Счетчик секундного счёта
    if ( _intervalCounter % _intervalQuantity == 0 )
    { // Прошла ещё 1 секунда
        _scalingCounter = _scalingCounterTmp;
        _scalingCounterTmp = 0;
        _intervalCounter = 0; // Счетчик подинтервалов
        if ( IsDelayTime() == false )
        {
            _scalingSumm += _scalingCounter;
        }
        _currTimeScaling++;
        _vmSaveParam->DisplayCurrTimeInvoke( _currTimeScaling );
        if ( _currTimeScaling >= GetSummTime() )
        {
            _vmSaveParam->ButtonOkClickInvoke(); // Прервать измерения
            _vmSaveParam->DisplayInfoInvoke(""); // Очистить поле с информацией
            _vmSaveParam->DisplayMiddleScalingInvoke(""); // Очистить поле "Ср. счёт с БД за 1 сек."
            _vmSaveParam->DisplayTotalScalingInvoke(""); // Очистить поле "Суммарный счёт за время измерения"
            WriteToFile();
            _scalingSumm = 0;
            return;
        }
        DisplayInfo();
        if ( EndOfMetering() == true )
        {
            WriteToFile();
            _scalingSumm = 0;
        }
    }
}
//---------------------------------------------------------------------------
bool ModelSaveParamBd85::IsDelayTime() // Время задержки сейчас?
{
    unsigned int remainder = _currTimeScaling % ( m_nT + 60 * m_nZ );
    if ( remainder >= m_nT )
    { // Идёт пауза, а не измерение
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
unsigned int ModelSaveParamBd85::NumberOfMetering()
{
    unsigned int quotient = _currTimeScaling / ( m_nT + 60 * m_nZ );
    return quotient + 1;
}
//---------------------------------------------------------------------------
unsigned int ModelSaveParamBd85::TimeOfMetering()
{ // Время для текущего измерения (или задержки)
    unsigned int time;
    unsigned int remainder = _currTimeScaling % ( m_nT + 60 * m_nZ );
    if ( remainder >= m_nT )
    {  // Идёт пауза, а не измерение
        time = remainder - m_nT;
    }
    else
    { // Идёт измерение, а не пауза
        time = remainder;
    }
    return time;
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::WriteToFile()
{

}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::DisplayInfo()
{
    char * str;
    char text1[50];
    char text2[12];
    char text3[12];
    if ( IsDelayTime() )
    {
        str = "Пауза";
    }
    else
    {
        str = "Измер.";
    }
    int q = NumberOfMetering(); // номер измерения
    int t = TimeOfMetering(); // Време для текущего измерения или паузы 
    sprintf( text1, "%s № %d (%d сек.)", str, q, t );
    _vmSaveParam->DisplayInfoInvoke( text1 );


    double dblScalingSumm = _scalingSumm;
    if ( EndOfMetering() == true )
    {
        dblScalingSumm /= m_nT;
        sprintf( text2, "%0.2f", dblScalingSumm ); // Средний счёт за 1 сек.
        sprintf( text3, "%d", _scalingSumm ); // Суммарный счёт за время измерения
        _vmSaveParam->DisplayMiddleScalingInvoke( text2 );
        _vmSaveParam->DisplayTotalScalingInvoke( text3 );
    }
    if ( IsDelayTime() == false ) // Время измерения (а не паузы)
    {
        unsigned int timeMet = TimeOfMetering();
        if ( timeMet != 0 )
        {
            dblScalingSumm /= timeMet;
            sprintf( text2, "%0.2f", dblScalingSumm ); // Средний счёт за 1 сек.
            sprintf( text3, "%d", _scalingSumm ); // Суммарный счёт за время измерения
            _vmSaveParam->DisplayMiddleScalingInvoke( text2 );
            _vmSaveParam->DisplayTotalScalingInvoke( text3 );
        }
    }
}
//---------------------------------------------------------------------------
bool ModelSaveParamBd85::EndOfMetering()
{
    unsigned int remainder = _currTimeScaling % ( m_nT + 60 * m_nZ );
    if ( ( remainder == 0 && m_nZ == 0 ) || ( remainder == m_nT && m_nZ != 0 ) )
    { // Завершилось измерение
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------




