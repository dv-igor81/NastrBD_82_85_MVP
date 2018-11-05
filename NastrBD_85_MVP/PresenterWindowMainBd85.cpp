//---------------------------------------------------------------------------
#pragma hdrstop
#include <stdio.h>
#include "PresenterWindowMainBd85.h"
#include "TextHelper.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
PresenterWindowMainBd85::PresenterWindowMainBd85(
    IWindowMainBd85 * view,
    IAllProtokolS * allProtokol,
    ITask * task,
    ActionSelf<> & as_ShowDispetWindow) :
        as_FormClose(this, &PresenterWindowMainBd85::FormClose)
        , as_OprosStar(this, &PresenterWindowMainBd85::OprosStar)
        , as_OprosStarInvoke(this, &PresenterWindowMainBd85::OprosStarInvoke)
        , as_OprosIter(this, &PresenterWindowMainBd85::OprosIter)
        , as_OprosIterInvoke(this, &PresenterWindowMainBd85::OprosIterInvoke)
        , as_OprosEnd(this, &PresenterWindowMainBd85::OprosEnd)
        , as_OprosEndInvoke(this, &PresenterWindowMainBd85::OprosEndInvoke)
        , as_SetConnectionState(this, &PresenterWindowMainBd85::SetConnectionState)
        , as_StartStopScaling(this, &PresenterWindowMainBd85::StartStopScaling)
        , as_ScalingOprosWorkInvoke(this, &PresenterWindowMainBd85::ScalingOprosWorkInvoke)
{
    _startData = 0;
    _iterData = 0;
    //===
    _isConnected = false; // Не подключились к БД (через ком-порт либо по TCP/IP)
    _isViewLoaded = true; // основное окно (вид) загружено
    _view = view;
    _allProtokol = allProtokol;
    _task = task;

    ev_Show += _view->GetSelfShow();
    *_view->GetEventFormClose() += as_FormClose;

    *_view->GetEventButtonStartStopScalingClick() += as_StartStopScaling;

    _connectBdProt = new ConnectBdProt(
        _view->GetConnectFourBdProt(), _allProtokol, _task );
    ev_Show(); // Прказать форму
    *_connectBdProt->GetEventSetConnectionState() += as_SetConnectionState;

    ev_DisplayStartData += _view->GetSelfDisplayStartData();
    *_allProtokol->GetEventErrorCountIncrement() += _view->GetSelfDisplayErrors();
    ev_DisplayIterData += _view->GetSelfDisplayIterData();

    ev_ShowDispetWindow += as_ShowDispetWindow;

    ev_ScalingOpros += _view->GetSelfDisplayScalingData();
}
//---------------------------------------------------------------------------
PresenterWindowMainBd85::~PresenterWindowMainBd85()
{
    _view->Destroy();
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::FormClose()
{
    _connectBdProt->Disconnect();
    _isViewLoaded = false;
    ev_ShowDispetWindow(); // Показать форму диспетчера
}
//---------------------------------------------------------------------------
bool PresenterWindowMainBd85::IsViewLoaded()
{
    return _isViewLoaded;
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::ConnectIsGood() // Соединение (по ком порту или TCP/IP) прошло удачно
{
    _connectBdProt->SetActionOprosStart( & as_OprosStar );
    _connectBdProt->SetActionOprosIter( & as_OprosIter );
    _connectBdProt->SetActionOprosEnd( & as_OprosEnd );
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::OprosStar()
{
    _startData = new StartDataNewBd85();
    ev_DisplayStartData( _startData ); // Очистить все поля
    _iterData = new IterDataNewBd85();
    ev_DisplayIterData( _iterData ); // Очистить все поля
    delete _startData; // Освободить память
    _startData = 0;
    delete _iterData; // Освободить память
    _iterData = 0;    
    while ( _isConnected )
    {
        if ( InitMkInBd() ) // Инициализация МК в БД (интервал набота счета, задать колтик = 8)
        {
            break;
        }
    }
    _readParamIndex = 0;
    while ( _isConnected )
    {
        if ( ReadEEProm() )
        {
            break; // Считать значения из памяти МК в БД
        }
    }
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::OprosStarInvoke()
{
    ev_DisplayStartData( _startData );
    delete _startData; // Освободить память
    _startData = 0;
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::OprosIter()
{
    if ( _allProtokol->GetSsp( & _ssp ) == false )
    {
        Sleep(10);
        return;
    }
    if ( (_ssp & 0x01) != 0x01 ) // Флаг готовности счёта НЕ получен
    {
        return;
    }
    if ( _allProtokol->GetIndAdr( & _indAddr ) == false )
    {
        return;
    }
    if ( _allProtokol->GetGrpAdr( & _groupAddr ) == false )
    {
        return;
    }
    if ( _allProtokol->GetTemperature( & _temperature ) == false )
    {
        return;
    }
    if ( _allProtokol->GetDNU( & _dnu ) == false )
    {
        return;
    }
    if ( _allProtokol->GetVoltageHi( & _voltageHi ) == false )
    {
        return;
    }
    if ( _allProtokol->GetWidthPwm( & _widthPwm ) == false )
    {
        return;
    }
    if ( _allProtokol->GetPeriodPwm( & _periodPwm ) == false )
    {
        return;
    }
    if ( _allProtokol->GetScaling( & _scaling ) == false )
    {
        return;
    }
    if ( _iterData != 0 ) // Основной поток не успел отобразить данные
    {
        return;
    }
    _iterData = new IterDataNewBd85(
        _indAddr // Индивидуальный адрес
        , _groupAddr // Групповой адрес
        , _temperature // Температура МК (КОД)
        , _dnu
        , _voltageHi
        , _widthPwm
        , _periodPwm
        , ScalingSummator(_scaling)
    );
    _task->BeginInvoke( & as_OprosIterInvoke );
}
//---------------------------------------------------------------------------
unsigned int PresenterWindowMainBd85::ScalingSummator(unsigned short scaling)
{
    _intervalCounter++; // Счетчик подинтервалов
    _scalingCounter += scaling; // _scalingCounter - Счетчик секундного счёта
    if ( _intervalCounter % _intervalQuantity == 0 ) // _intervalQuantity - Количество подинтервалов в секунде
    {
        _scalingCounterTmp = _scalingCounter;
        _scalingCounter = 0; // _scalingCounter - Счетчик секундного счёта
        _intervalCounter = 0; // Счетчик подинтервалов

        if ( _isScalingWork )
        {
            ScalingOprosWork();
        }

        return _scalingCounterTmp; // Текущий секундный счёт
    }
    return 0xFFFFFFFF; // Признак того, что счет не готов
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::OprosIterInvoke()
{
    ev_DisplayIterData( _iterData );
    delete _iterData;
    _iterData = 0;
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::StartStopScaling(const char* timeMeteringLimit)
{
    if(_isScalingWork) // Идет набор счета
    {
        _isExitScalingWork = true; // Сигнал, на завершение расчёта среднего счета
    }
    else
    {
        _isExitScalingWork = false;
        _timeLimitScaling = TextHelper::ConvertTextToNumber(
            timeMeteringLimit, // Текст
            60); // 60 секунд по умолчанию
        _currTimeScaling = 0; // Текущее время набора счета
        _scalingCounterSumm = 0; // Суммарный счет за время набора

        // Проверить ошибку ввода, устранить если есть, очистить поля
        _scalingData = new ScalingDataNewBd85( _timeLimitScaling );
        ev_ScalingOpros( _scalingData );
        if ( _timeLimitScaling > 0 )
        {
            _isScalingWork = true;
        }
    }
    delete _scalingData;
    _scalingData = 0;
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::ScalingOprosWork()
{
    int stubExit = _timeLimitScaling;
    if ( _isExitScalingWork ) // Завершить расчёт среднего счёта
    {
        _isScalingWork = false;
    }
    else
    { // Расчитывать средней счет
        _currTimeScaling++;
        _scalingCounterSumm += _scalingCounterTmp;
        if ( _currTimeScaling >= _timeLimitScaling )
        {
            _isScalingWork = false; // Завершить расчёт среднего счёта
        }
    }
    if ( _isScalingWork == false )
    {
        stubExit = -1; // Индикация завершения расчёта среднего счёта
    }
    if ( _scalingData != 0 ) // Основной поток не успел отобразить данные
    {
        return;
    }

    _scalingData = new ScalingDataNewBd85(
        stubExit
        , _currTimeScaling // Текущее время набора счета
        , _scalingCounterSumm
    );

    _task->BeginInvoke( & as_ScalingOprosWorkInvoke );
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::ScalingOprosWorkInvoke()
{
    ev_ScalingOpros( _scalingData );
    delete _scalingData;
    _scalingData = 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::OprosEnd()
{
    Sleep(10);
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::OprosEndInvoke()
{
}
//---------------------------------------------------------------------------
bool PresenterWindowMainBd85::InitMkInBd()
{
    unsigned char timeInterval = 0;
    const unsigned char defaultTimeInterval = 8;
    if ( _allProtokol->GetTimeInterval( & timeInterval ) == false )
    {
        return false;
    }
    if ( timeInterval != defaultTimeInterval )
    {
        if ( _allProtokol->SetTimeInterval( defaultTimeInterval ) == false )
        {
            return false;
        }
        if ( _allProtokol->GetTimeInterval( & timeInterval ) == false )
        {
            return false;
        }
        if ( timeInterval != defaultTimeInterval )
        {
            return false;
        }
    }
    return true;
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::SetConnectionState( ConnectionStateInfo state )
{
    switch (state)
    {
    case ConnectionStateInfo_t::WaitConnect:
        break;
    case ConnectionStateInfo_t::IsConnected:
        ConnectIsGood();
        _isConnected = true;
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
        _intervalCounter = 0; // Счетчик подинтервалов
        _scalingCounter = 0; // Счетчик секундного счёта
        _isScalingWork = false; // Не работает набор счета за определенный пользователем интервал
        break;
    case ConnectionStateInfo_t::WaitLoopExit:
        _isConnected = false;
        _isExitScalingWork = true; // Сигнал, на завершение расчёта среднего счёта
        ScalingOprosWork(); // Отобразить графически завершение расчёта среднего счёта
        break;
    case ConnectionStateInfo_t::IsDisconnect:
        break;
    }
}
//---------------------------------------------------------------------------
bool PresenterWindowMainBd85::ReadEEProm()
{
    if ( _readParamIndex == 0 )
    {
        if ( _allProtokol->GetVersia( _verPo ) == false )
        {
            return false;
        }
        _readParamIndex++;
    }
    if ( _isConnected == false )
    {
        return false;
    }
    if ( _readParamIndex == 1 )
    {
        if ( _allProtokol->GetIndAdrZ( & _indAddrZad ) == false )
        {
            return false;
        }
        _readParamIndex++;
    }
    if ( _readParamIndex == 2 )
    {
        if ( _allProtokol->GetGroupAdrZ( & _groupAddrZad ) == false )
        {
            return false;
        }
        _readParamIndex++;
    }
    if ( _isConnected == false )
    {
        return false;
    }
    if ( _readParamIndex == 3 )
    {
        if ( _allProtokol->GetDnuZ( & _dnuZad ) == false )
        {
            return false;
        }
        _readParamIndex++;
    }
    if ( _isConnected == false )
    {
        return false;
    }
    if ( _readParamIndex == 4 )
    {
        if ( _allProtokol->GetVoltageHiZ_Bd85( & _voltageHiZad ) == false )
        {
            return false;
        }
        _readParamIndex++;
    }
    if ( _isConnected == false )
    {
        return false;
    }
    if ( _readParamIndex == 5 )
    {
        if ( _allProtokol->GetWidthPwmZ_Bd85( & _widthPwmZad ) == false )
        {
            return false;
        }
        _readParamIndex++;
    }
    if ( _isConnected == false )
    {
        return false;
    }
    if ( _readParamIndex == 6 )
    {
        if ( _allProtokol->GetOffsetPwmZ_Bd85( & _offsetPwmZ ) == false )
        {
            return false;
        }
        _readParamIndex++;
    }
    if ( _isConnected == false )
    {
        return false;
    }
    if ( _readParamIndex == 7 )
    {
        if ( _allProtokol->GetPeriodPwmZ_Bd85( & _periodPwmZ ) == false )
        {
            return false;
        }
        _readParamIndex++;
    }
    if ( _startData != 0 )
    {
        return false; // Основной поток не успел отобразить данные
    }
    _startData = new StartDataNewBd85(
        _verPo // Версия прошивки
        , _indAddrZad // Индивидуальный адрес заданный
        , _groupAddrZad // Групповой адрес заданный
        , _dnuZad // ДНУ заданное КОД
        , _voltageHiZad // Напряжение высокое заданное КОД
        , _widthPwmZad // Длительность ШИМ заданная
        , _offsetPwmZ //  Смешение ШИМ заданное
        , _periodPwmZ // Период ШИМ заданный
        );
    _task->BeginInvoke( & as_OprosStarInvoke );
    return true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
