//---------------------------------------------------------------------------
#pragma hdrstop
#include <stdio.h>
#include "PresenterWindowMainBd85.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
PresenterWindowMainBd85::PresenterWindowMainBd85(
    IWindowMainBd85 * view,
    IAllProtokolS * allProtokol,
    ITask * task) :
        as_FormClose(this, &PresenterWindowMainBd85::FormClose)
        , as_OprosStar(this, &PresenterWindowMainBd85::OprosStar)
        , as_OprosStarInvoke(this, &PresenterWindowMainBd85::OprosStarInvoke)
        , as_OprosIter(this, &PresenterWindowMainBd85::OprosIter)
        , as_OprosIterInvoke(this, &PresenterWindowMainBd85::OprosIterInvoke)
        , as_OprosEnd(this, &PresenterWindowMainBd85::OprosEnd)
        , as_OprosEndInvoke(this, &PresenterWindowMainBd85::OprosEndInvoke)
        , as_SetConnectionState(this, &PresenterWindowMainBd85::SetConnectionState)
{
    _isConnected = false; // Не подключились к БД (через ком-порт либо по TCP/IP)
    _isViewLoaded = true; // основное окно (вид) загружено
    _view = view;
    _allProtokol = allProtokol;
    _task = task;

    ev_Show += _view->GetSelfShow();
    *_view->GetEventFormClose() += as_FormClose;
    _connectBdProt = new ConnectBdProt(
        _view->GetConnectFourBdProt(), _allProtokol, _task );
    ev_Show(); // Прказать форму
    *_connectBdProt->GetEventSetConnectionState() += as_SetConnectionState;

    ev_DisplayStartData += _view->GetSelfDisplayStartData();
    *_allProtokol->GetEventErrorCountIncrement() += _view->GetSelfDisplayErrors();
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
    _data = new StartDataNewBd85();
    ev_DisplayStartData( _data );

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
    ev_DisplayStartData( _data );
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::OprosIter()
{
    Sleep(10);
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::OprosIterInvoke()
{
}
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
        break;
    case ConnectionStateInfo_t::WaitLoopExit:
        _isConnected = false;    
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

    _data = new StartDataNewBd85(
        _verPo // Версия прошивки
        , _indAddrZad // Индивидуальный адрес заданный
        , _groupAddrZad // Групповой адрес заданный
        , _dnuZad // ДНУ заданное КОД
        , _voltageHiZad // Напряжение высокое заданное КОД
        , _widthPwmZad // Длительность ШИМ заданная
        );
    _task->BeginInvoke( & as_OprosStarInvoke );
    return true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
