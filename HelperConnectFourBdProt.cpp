//---------------------------------------------------------------------------
#pragma hdrstop
#include "HelperConnectFourBdProt.h"
#include "Protokol_t.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
HelperConnectFourBdProt::HelperConnectFourBdProt(
    ActionEvent<Protokol>* ev_protocolChange, // �������� �������� �� ���
    ActionSelf<bool>* as_comPortOrTcpIp, // �������� ��� ����������: ���-���� ��� TCP/IP
    ActionSelf<const char*>* as_labelHint, // ����� ���������
    ActionSelf<const char*, const char*>* as_addComPortName, // �������� ��� ���-�����
    ActionEvent<>* ev_windowShow, // ������� �������� ����
    ActionSelf<Protokol>* as_setProtokolName, // ���������� ��� ���������
    ActionSelf<const char*, const char*>* as_setEndPoint, // ���������� IP-����� � TCP-����
    ActionEvent<const char*>* ev_textBox_IP_AddrChange, // ����� ip-������ ��������� �� ���
    ActionEvent<const char*>*  ev_textBox_TCP_PortChange, // ����� tcp-����� ��������� �� ���
    ActionEvent<>* ev_button_UpdateNumberOfComPortSClick, // �������� ������ ���-������
    ActionEvent<>* ev_button_StartStopClick, // ���������/���������� ����� ������� � ��
    HelperNumberTextBtn* addrBd)
{
    _ev_protocolChange = ev_protocolChange; // �������� �������� �� ���
    _as_comPortOrTcpIp = as_comPortOrTcpIp; // ������� ��� ����������: ���-���� ��� TCP/IP
    _as_labelHint = as_labelHint;
    _as_addComPortName = as_addComPortName;
    _ev_windowShow = ev_windowShow;
    _as_setProtokolName = as_setProtokolName;
    _as_setEndPoint = as_setEndPoint;
    _ev_textBox_IP_AddrChange = ev_textBox_IP_AddrChange;
    _ev_textBox_TCP_PortChange = ev_textBox_TCP_PortChange;
    _ev_button_UpdateNumberOfComPortSClick = ev_button_UpdateNumberOfComPortSClick;
    _ev_button_StartStopClick = ev_button_StartStopClick;
    _addrBd = addrBd;
}
//---------------------------------------------------------------------------
ActionEvent<Protokol>* HelperConnectFourBdProt::GetEventProtocolChange()
{
    return _ev_protocolChange;
}
//---------------------------------------------------------------------------
ActionSelf<bool>* HelperConnectFourBdProt::GetSelfComPortOrTcpIp()
{
    return _as_comPortOrTcpIp;
}
//---------------------------------------------------------------------------
ActionSelf<const char*>* HelperConnectFourBdProt::GetSelfLabelHintSetText()
{
    return _as_labelHint;
}
//---------------------------------------------------------------------------
ActionSelf<const char*, const char*>* HelperConnectFourBdProt::GetSelfAddComPortName()
{
    return _as_addComPortName;
}
//---------------------------------------------------------------------------
ActionEvent<>* HelperConnectFourBdProt::GetEventWindowShow()
{
    return _ev_windowShow;
}
//---------------------------------------------------------------------------
ActionSelf<Protokol>* HelperConnectFourBdProt::GetSelfSetProtokolName()
{
    return _as_setProtokolName;
}
//---------------------------------------------------------------------------
ActionSelf<const char*, const char*>* HelperConnectFourBdProt::GetSelfSetEndPoint()
{
    return _as_setEndPoint;
}
//---------------------------------------------------------------------------
ActionEvent<const char*>* HelperConnectFourBdProt::GetEventIpAddrChange()
{
    return _ev_textBox_IP_AddrChange;
}
//---------------------------------------------------------------------------
ActionEvent<const char*>* HelperConnectFourBdProt::GetEventTcpPortChange()
{
    return _ev_textBox_TCP_PortChange;
}
//---------------------------------------------------------------------------
ActionEvent<>* HelperConnectFourBdProt::GetEventUpdateNumberOfComPorts()
{
    return _ev_button_UpdateNumberOfComPortSClick;
}
//---------------------------------------------------------------------------
ActionEvent<>* HelperConnectFourBdProt::GetEventStartStopClick()
{
    return _ev_button_StartStopClick;
}
//---------------------------------------------------------------------------
HelperNumberTextBtn* HelperConnectFourBdProt::GetHelperNumberAddrBd()
{
    return _addrBd;
}
