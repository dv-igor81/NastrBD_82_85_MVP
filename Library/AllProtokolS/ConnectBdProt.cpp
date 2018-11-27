//---------------------------------------------------------------------------
#pragma hdrstop
#include "ConnectBdProt.h"
//---------------------------------------------------------------------------
#include <dstring.h>
#include "TextHelper.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
ConnectBdProt::ConnectBdProt(
    HelperConnectFourBdProt * bdProt,
    IAllProtokolS * allProtokol,
    TaskWithParam * task)  :
        as_protocolChanged(this, &ConnectBdProt::ProtocolChanged)
        , as_comPortsChange(this, &ConnectBdProt::ComPortsChange)
        , as_windowShow(this, &ConnectBdProt::WindowShow)
        , as_changeIpAddr(this, &ConnectBdProt::ChangeIpAddr)
        , as_changeTcpPort(this, &ConnectBdProt::ChangeTcpPort)
        , as_updateNumberOfComPorts(this, &ConnectBdProt::UpdateNumberOfComPorts)
        , as_startStopClick(this, &ConnectBdProt::StartStopClick)
        , as_UpdateComPotrsAsynk(this, &ConnectBdProt::UpdateComPotrsAsynk)
        , as_UpdateComPortsInfo(this, &ConnectBdProt::UpdateComPortsInfo)
        , as_ConnectionAsynk(this, &ConnectBdProt::ConnectionAsynk)
        , as_SetControlStateInvoke(this, &ConnectBdProt::SetControlStateInvoke)
        , as_SetAddrBdNumber(this, &ConnectBdProt::SetAddrBdNumber)
{
    _bdProt = bdProt;
    _allProtokol = allProtokol;
    _task = task;
    _isConnected = false;
    _bfOprosInLoop = false;
    as_OprosStart = 0;
    as_OprosIter = 0;
    as_OprosEnd = 0;
    _addrBdPtr = 0;


    _addrBdHelper = _bdProt->GetHelperNumberAddrBd();
    _addrBd_NineBit = 63;
    _addrBd_ModBus_RTU = 247;
    _addrBd_ModBus_TCP = 247;
    _addrBd_ModBus_RTU_IP = 247;

    *_addrBdHelper->GetEventSetNumber() += as_SetAddrBdNumber;


    *_bdProt->GetEventProtocolChange() += as_protocolChanged;
    *_bdProt->GetEventComPortsChange() += as_comPortsChange;

    ev_comPortOrTcpIp += _bdProt->GetSelfComPortOrTcpIp();
    ev_labelHint += _bdProt->GetSelfLabelHintSetText();

    ev_clearAllComPortName += _bdProt->GetSelfClearAllComPortName();
    ev_setEnabledUpdateComPorts += _bdProt->GetSelfSetEnabledUpdateComPorts();

    *_bdProt->GetEventWindowShow() += as_windowShow;
    ev_setProtokolName += _bdProt->GetSelfSetProtokolName();
    ev_setEndPoint += _bdProt->GetSelfSetEndPoint();
    *_bdProt->GetEventIpAddrChange() += as_changeIpAddr;
    *_bdProt->GetEventTcpPortChange() += as_changeTcpPort;
    ev_addComPortName += _bdProt->GetSelfAddComPortName();
    *_bdProt->GetEventUpdateNumberOfComPorts() += as_updateNumberOfComPorts;
    *_bdProt->GetEventStartStopClick() += as_startStopClick;
    ev_SetConnectionState += _bdProt->GetSelfSetConnectionState();
}
//---------------------------------------------------------------------------
void ConnectBdProt::ProtocolChanged(ProtokolName protocolName)
{
    SettingsChengeProtokol(protocolName, false); // false - не из ini-файла
}
//---------------------------------------------------------------------------
void ConnectBdProt::ComPortsChange(const char* cpName)
{
    TextHelper::CopyText(comPortName, cpName, comPortNameSize);
}
//---------------------------------------------------------------------------
void ConnectBdProt::SettingsChengeProtokol(ProtokolName protokolName, bool fromPresenter)
{
    bool isComPortProt;
    bool flagError = false;
    char * hintText;
    _protokolName = protokolName;
    switch (protokolName)
    {
    case ProtokolName_t::NineBit: // 9-ти битный
        isComPortProt = true;
        hintText = "RS-232";
        _addrBdPtr = & _addrBd_NineBit;
        break;
    case ProtokolName_t::ModBus_RTU: // ModBus RTU
        isComPortProt = true;
        hintText = "RS-232";
        _addrBdPtr = & _addrBd_ModBus_RTU;
        break;
    case ProtokolName_t::ModBus_TCP: // ModBus TCP
        isComPortProt = false;
        ev_setEndPoint(strIpAddr_TCP, strTcpPort_TCP);
        hintText = "АРМ МЕТРО";
        _addrBdPtr = & _addrBd_ModBus_TCP;
        break;
    case ProtokolName_t::ModBus_RTU_IP: // ModBus RTU (TCP/IP)
        isComPortProt = false;
        ev_setEndPoint(strIpAddr_RTU_IP, strTcpPort_RTU_IP);
        hintText = "АРМ ВНИИА";
        _addrBdPtr = & _addrBd_ModBus_RTU_IP;
        break;
    case ProtokolName_t::NeVybran:
        hintText = "Error";
        flagError = true; // Ошибка!!!
        break;
    }
    ev_comPortOrTcpIp(isComPortProt);
    ev_labelHint(hintText);
    _addrBdHelper->SetNumber( *_addrBdPtr ); // Отобразить адрес БД на форме
    if ( !flagError )
    {
        ev_setProtokolName(protokolName);
    }
}
//---------------------------------------------------------------------------
void ConnectBdProt::WindowShow()
{
    TextHelper::CopyText(strIpAddr_TCP, "192.168.3.4", ipAddrSize);
    TextHelper::CopyText(strIpAddr_RTU_IP, "192.168.127.254", ipAddrSize);
    TextHelper::CopyText(strTcpPort_TCP, "502", tcpPortSize);
    TextHelper::CopyText(strTcpPort_RTU_IP, "4001", tcpPortSize);
    SettingsChengeProtokol(ProtokolName_t::NineBit, true);
    SetControlFromConnectionState(ConnectionStateInfo_t::IsDisconnect);
    UpdateNumberOfComPorts();
}
//---------------------------------------------------------------------------
void ConnectBdProt::UpdateNumberOfComPorts()
{
    ev_clearAllComPortName(); // Очистить список ком портов
    ev_setEnabledUpdateComPorts(false); // Сделать на форме недоступной кнопку обновления ком-порта
    _task->RunAsynk( & as_UpdateComPotrsAsynk );
}
//---------------------------------------------------------------------------
void ConnectBdProt::UpdateComPotrsAsynk()
{
    _allProtokol->UpdateComPotrs();
    _task->BeginInvoke( & as_UpdateComPortsInfo );
}
//---------------------------------------------------------------------------
void ConnectBdProt::UpdateComPortsInfo()
{
    int comPortIndex;
    int comPortCount = 0;
    AnsiString comPortName;
    while ( _allProtokol->NextComPortIndex( & comPortIndex ) )
    {
        comPortName = "COM" + IntToStr( comPortIndex );
        comPortCount++;
        AnsiString count = IntToStr( comPortCount );
        ev_addComPortName( comPortName.c_str(), count.c_str() );
    }
    ev_setEnabledUpdateComPorts(true); // Сделать на форме доступной кнопку обновления ком-порта
}
//---------------------------------------------------------------------------
void ConnectBdProt::ChangeIpAddr(const char* textIpAddr)
{
    switch (_protokolName)
    {
    case ProtokolName_t::ModBus_TCP: // ModBus TCP
        TextHelper::CopyText(strIpAddr_TCP, textIpAddr, ipAddrSize);
        break;
    case ProtokolName_t::ModBus_RTU_IP: // ModBus RTU (TCP/IP)
        TextHelper::CopyText(strIpAddr_RTU_IP, textIpAddr, ipAddrSize);
        break;
    }
}
//---------------------------------------------------------------------------
void ConnectBdProt::ChangeTcpPort(const char* textTcpPort)
{
    switch (_protokolName)
    {
    case ProtokolName_t::ModBus_TCP: // ModBus TCP
        TextHelper::CopyText(strTcpPort_TCP, textTcpPort, tcpPortSize);
        break;
    case ProtokolName_t::ModBus_RTU_IP: // ModBus RTU (TCP/IP)
        TextHelper::CopyText(strTcpPort_RTU_IP, textTcpPort, tcpPortSize);
        break;
    }
}
//---------------------------------------------------------------------------
void ConnectBdProt::StartStopClick()
{
    if ( _isConnected == false )
    {
        // Заблокировать элементы управления, и ожидать соединения
        SetControlFromConnectionState(ConnectionStateInfo_t::WaitConnect);
        _addrBdHelper->SetNumber(); // Отобразить адрес БД на форме
        _addrBd = _addrBdHelper->GetNumber(); // Получить номер
        _task->RunAsynk( & as_ConnectionAsynk );
    }
    else
    {
        Disconnect();
    }
}
//---------------------------------------------------------------------------
void ConnectBdProt::ConnectionAsynk()
{
    Connect();
}
//---------------------------------------------------------------------------
void ConnectBdProt::Connect()
{
    _allProtokol->SetProtokolName( _protokolName );  //_protokolName
    switch ( _protokolName )
    {
    case ProtokolName_t::NineBit: // 9-ти битный
    case ProtokolName_t::ModBus_RTU: // ModBus RTU
        _allProtokol->SetComPortName( comPortName );
        break;
    case ProtokolName_t::ModBus_TCP: // ModBus TCP
        _allProtokol->SetIpAddr( strIpAddr_TCP );
        SetTcpPort( strTcpPort_TCP, 502 );
        break;
    case ProtokolName_t::ModBus_RTU_IP: // ModBus RTU (TCP/IP)
        _allProtokol->SetIpAddr( strIpAddr_RTU_IP );
        SetTcpPort( strTcpPort_RTU_IP, 4001 );
        break;
    case ProtokolName_t::NeVybran:
        break;
    }
    //SetResponseTimeout(_timeOut); // Ждать ответа timeOut мс
    //SetDelayTimeout(3);
    //SetKolVoPopytok(1); // Количество попыток обмена, прежде чем выдать ошибку
    _allProtokol->SetBdAddr( _addrBd );
    _isConnected = _allProtokol->Open();
    Sleep( 500 );
    if ( _isConnected )
    {
        _bfOprosInLoop = true;
        _state = ConnectionStateInfo_t::IsConnected;
        //ev_ConnectIsGood();
        _task->BeginInvoke( & as_SetControlStateInvoke );
        WorkInLoop();
        _allProtokol->Close();
        _isConnected = false;
    }
    _state = ConnectionStateInfo_t::IsDisconnect;
    _task->BeginInvoke( & as_SetControlStateInvoke );
}
//---------------------------------------------------------------------------
void ConnectBdProt::Disconnect()
{
    _bfOprosInLoop = false;
    _state = ConnectionStateInfo_t::WaitLoopExit;
    _task->BeginInvoke( & as_SetControlStateInvoke ); // Ждать выход из петли    
}
//---------------------------------------------------------------------------
void ConnectBdProt::WorkInLoop()
{
    if ( as_OprosStart != 0 )
    {
        (*as_OprosStart)();
    }
    while ( _bfOprosInLoop && (as_OprosIter != 0) )
    {
        (*as_OprosIter)();
    }
    if ( as_OprosEnd != 0 )
    {
        (*as_OprosEnd)();
    }
    Sleep( 500 );
}
//---------------------------------------------------------------------------
void ConnectBdProt::SetTcpPort(const char* textTcpPort, int defTcpPort)
{
    int tcpPort;
    try
    {
        tcpPort = StrToInt( textTcpPort );
    }
    catch ( ... )
    {
        tcpPort = defTcpPort;
    }
    _allProtokol->SetTcpPort( tcpPort );
}
//---------------------------------------------------------------------------
void ConnectBdProt::SetControlFromConnectionState(ConnectionStateInfo state)
{
    ev_SetConnectionState(state);
}
//---------------------------------------------------------------------------
void ConnectBdProt::SetControlStateInvoke()
{
    SetControlFromConnectionState( _state );
}
//---------------------------------------------------------------------------
void ConnectBdProt::SetActionOprosStart( ActionSelf<>* action )
{
    as_OprosStart = action;
}
//---------------------------------------------------------------------------
void ConnectBdProt::SetActionOprosIter( ActionSelf<>* action )
{
    as_OprosIter = action;
}
//---------------------------------------------------------------------------
void ConnectBdProt::SetActionOprosEnd( ActionSelf<>* action )
{
    as_OprosEnd = action;
}
//---------------------------------------------------------------------------
void ConnectBdProt::SetAddrBdNumber(int addrBd)
{
    if ( _addrBdPtr != 0 )
    {
        *_addrBdPtr = addrBd;
    }
}
//---------------------------------------------------------------------------
ActionEvent<ConnectionStateInfo>* ConnectBdProt::GetEventSetConnectionState()
{
    return & ev_SetConnectionState;
}
//---------------------------------------------------------------------------
