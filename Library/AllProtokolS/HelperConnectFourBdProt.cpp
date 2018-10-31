//---------------------------------------------------------------------------
#pragma hdrstop
#include "HelperConnectFourBdProt.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
HelperConnectFourBdProt::HelperConnectFourBdProt(
    ActionEvent<ProtokolName>* ev_protocolChange, // Протокол меняется из ГИП
    ActionEvent<const char*>* ev_comboBox_ComPortsChange, // Меняется номер ком-порта из ГИП
    ActionSelf<bool>* as_comPortOrTcpIp, // Меняется вид программно: ком-порт или TCP/IP
    ActionSelf<const char*>* as_labelHint, // Текст подсказки
    ActionSelf<>* as_clearAllComPortName,  // Очистить список найденых ком-портов
    ActionSelf<bool>* as_setEnabledUpdateComPorts, // Установить доступность обновления ком-портов
    ActionSelf<const char*, const char*>* as_addComPortName, // Добавить имя ком-порта
    ActionEvent<>* ev_windowShow, // Событие показать окно
    ActionSelf<ProtokolName>* as_setProtokolName, // Установить имя протокола
    ActionSelf<const char*, const char*>* as_setEndPoint, // Установить IP-адрес и TCP-порт
    ActionEvent<const char*>* ev_textBox_IP_AddrChange, // Текст ip-адреса изменился из ГИП
    ActionEvent<const char*>*  ev_textBox_TCP_PortChange, // Текст tcp-порта изменился из ГИП
    ActionEvent<>* ev_button_UpdateNumberOfComPortSClick, // Обновите список ком-портов
    ActionEvent<>* ev_button_StartStopClick, // Запустить/Остановить обмен данными с БД
    ActionSelf<ConnectionStateInfo>* as_SetConnectionState, // Отобразить изменения о состоянии соединения в ГИП
    HelperNumberTextBtn* addrBd)
{
    _ev_protocolChange = ev_protocolChange; // Протокол меняется из ГИП
    _ev_comboBox_ComPortsChange = ev_comboBox_ComPortsChange; // Меняется номер ком-порта из ГИП
    _as_comPortOrTcpIp = as_comPortOrTcpIp; // Изменяю вид программно: ком-порт или TCP/IP
    _as_labelHint = as_labelHint;

    _as_clearAllComPortName = as_clearAllComPortName;
    _as_setEnabledUpdateComPorts = as_setEnabledUpdateComPorts;

    _as_addComPortName = as_addComPortName;
    _ev_windowShow = ev_windowShow;
    _as_setProtokolName = as_setProtokolName;
    _as_setEndPoint = as_setEndPoint;
    _ev_textBox_IP_AddrChange = ev_textBox_IP_AddrChange;
    _ev_textBox_TCP_PortChange = ev_textBox_TCP_PortChange;
    _ev_button_UpdateNumberOfComPortSClick = ev_button_UpdateNumberOfComPortSClick;
    _ev_button_StartStopClick = ev_button_StartStopClick;
    _as_SetConnectionState = as_SetConnectionState;
    _addrBd = addrBd;
}
//---------------------------------------------------------------------------
ActionEvent<ProtokolName>* HelperConnectFourBdProt::GetEventProtocolChange()
{
    return _ev_protocolChange;
}
//---------------------------------------------------------------------------
ActionEvent<const char*>* HelperConnectFourBdProt::GetEventComPortsChange()
{
    return _ev_comboBox_ComPortsChange;
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
ActionSelf<ProtokolName>* HelperConnectFourBdProt::GetSelfSetProtokolName()
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
//---------------------------------------------------------------------------
ActionSelf<>* HelperConnectFourBdProt::GetSelfClearAllComPortName()
{
    return _as_clearAllComPortName;
}
//---------------------------------------------------------------------------
ActionSelf<bool>* HelperConnectFourBdProt::GetSelfSetEnabledUpdateComPorts()
{
    return _as_setEnabledUpdateComPorts;
}
//---------------------------------------------------------------------------
ActionSelf<ConnectionStateInfo>* HelperConnectFourBdProt::GetSelfSetConnectionState()
{
    return _as_SetConnectionState;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
