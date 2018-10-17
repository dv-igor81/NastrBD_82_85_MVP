//---------------------------------------------------------------------------
#pragma hdrstop
#include "ConnectBdProt.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
ConnectBdProt::ConnectBdProt(HelperConnectFourBdProt* bdProt)  :
    as_protocolChanged(this, &ConnectBdProt::ProtocolChanged)
    , as_windowShow(this, &ConnectBdProt::WindowShow)
    , as_changeIpAddr(this, &ConnectBdProt::ChangeIpAddr)
    , as_changeTcpPort(this, &ConnectBdProt::ChangeTcpPort)
    , as_updateNumberOfComPorts(this, &ConnectBdProt::UpdateNumberOfComPorts)
    , as_startStopClick(this, &ConnectBdProt::StartStopClick)
{
    _bdProt = bdProt;
    *_bdProt->GetEventProtocolChange() += as_protocolChanged;
    ev_comPortOrTcpIp += _bdProt->GetSelfComPortOrTcpIp();
    ev_labelHint += _bdProt->GetSelfLabelHintSetText();
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
    SettingsChengeProtokol(protocolName, false); // false - ÌÂ ËÁ ini-Ù‡ÈÎ‡
}
//---------------------------------------------------------------------------
void ConnectBdProt::SettingsChengeProtokol(Protokol protokolName, bool fromPresenter)
{
    bool isComPortProt;
    bool flagError = false;
    char * hintText;
    switch (protokolName)
    {
    case Protokol_t::NineBit: // 9-ÚË ·ËÚÌ˚È
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
        hintText = "¿–Ã Ã≈“–Œ";
        break;
    case Protokol_t::ModBus_RTU_IP: // ModBus RTU (TCP/IP)
        isComPortProt = false;
        ev_setEndPoint("192.168.127.254", "4001");
        hintText = "¿–Ã ¬Õ»»¿";
        break;
    case Protokol_t::NeVybran:
        hintText = "Error";
        flagError = true; // Œ¯Ë·Í‡!!!
        break;
    }

    ev_comPortOrTcpIp(isComPortProt);
    ev_labelHint(hintText);
    if (fromPresenter && !flagError)
    {
      ev_setProtokolName(protokolName);
    }
}
//---------------------------------------------------------------------------
void ConnectBdProt::WindowShow()
{
    SettingsChengeProtokol(Protokol_t::NineBit, true);
    ev_addComPortName("COM1", "1");
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
void ConnectBdProt::UpdateNumberOfComPorts()
{
}
//---------------------------------------------------------------------------
void ConnectBdProt::StartStopClick()
{
}
//---------------------------------------------------------------------------
