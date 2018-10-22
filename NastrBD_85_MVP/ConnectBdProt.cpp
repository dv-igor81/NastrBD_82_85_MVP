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
    ITask * task)  :
        as_protocolChanged(this, &ConnectBdProt::ProtocolChanged)
        , as_comPortsChange(this, &ConnectBdProt::ComPortsChange)
        , as_windowShow(this, &ConnectBdProt::WindowShow)
        , as_changeIpAddr(this, &ConnectBdProt::ChangeIpAddr)
        , as_changeTcpPort(this, &ConnectBdProt::ChangeTcpPort)
        , as_updateNumberOfComPorts(this, &ConnectBdProt::UpdateNumberOfComPorts)
        , as_startStopClick(this, &ConnectBdProt::StartStopClick)
        , as_UpdateComPotrsAsynk(this, &ConnectBdProt::UpdateComPotrsAsynk)
        , as_UpdateComPortsInfo(this, &ConnectBdProt::UpdateComPortsInfo)
{
    _bdProt = bdProt;
    _allProtokol = allProtokol;
    _task = task;
    
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
}
//---------------------------------------------------------------------------
void ConnectBdProt::ProtocolChanged(Protokol protocolName)
{
    SettingsChengeProtokol(protocolName, false); // false - не из ini-файла
}
//---------------------------------------------------------------------------
void ConnectBdProt::ComPortsChange(const char* cpName)
{
    TextHelper::CopyText(comPortName, cpName, comPortNameSize);
}
//---------------------------------------------------------------------------
void ConnectBdProt::SettingsChengeProtokol(Protokol protokolName, bool fromPresenter)
{
    bool isComPortProt;
    bool flagError = false;
    char * hintText;
    switch (protokolName)
    {
    case Protokol_t::NineBit: // 9-ти битный
        isComPortProt = true;
        hintText = "RS-232";
        break;
    case Protokol_t::ModBus_RTU: // ModBus RTU
        isComPortProt = true;
        hintText = "RS-232";
        break;
    case Protokol_t::ModBus_TCP: // ModBus TCP
        isComPortProt = false;
        ev_setEndPoint("192.168.3.4", "502");
        hintText = "АРМ МЕТРО";
        break;
    case Protokol_t::ModBus_RTU_IP: // ModBus RTU (TCP/IP)
        isComPortProt = false;
        ev_setEndPoint("192.168.127.254", "4001");
        hintText = "АРМ ВНИИА";
        break;
    case Protokol_t::NeVybran:
        hintText = "Error";
        flagError = true; // Ошибка!!!
        break;
    }
    ev_comPortOrTcpIp(isComPortProt);
    ev_labelHint(hintText);
    _protokolName = Protokol_t::NeVybran; // Протокол не выбран
    if (fromPresenter && !flagError)
    {
        ev_setProtokolName(protokolName);
        _protokolName = protokolName;
    }
}
//---------------------------------------------------------------------------
void ConnectBdProt::WindowShow()
{
    SettingsChengeProtokol(Protokol_t::NineBit, true);
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
}
//---------------------------------------------------------------------------
void ConnectBdProt::ChangeTcpPort(const char* textTcpPort)
{
}
//---------------------------------------------------------------------------
void ConnectBdProt::StartStopClick()
{
    Connect();
}
//---------------------------------------------------------------------------
void ConnectBdProt::Connect()
{
    HelperNumberTextBtn* addrBdHelper = _bdProt->GetHelperNumberAddrBd();
    addrBdHelper->SetNumber(); // Отобразить номер на форме
    int addrBd = addrBdHelper->GetNumber(); // Получить номер
    _allProtokol->SetProtokol( _protokolName );  //_protokolName
    switch ( _protokolName )
    {
    case Protokol_t::NineBit: // 9-ти битный
    case Protokol_t::ModBus_RTU: // ModBus RTU
        _allProtokol->SetComPortName( comPortName );
        break;
    case Protokol_t::ModBus_TCP: // ModBus TCP
    case Protokol_t::ModBus_RTU_IP: // ModBus RTU (TCP/IP)
        break;
    case Protokol_t::NeVybran:
        break;
    }

}
