//---------------------------------------------------------------------------
#ifndef HelperConnectFourBdProtH
#define HelperConnectFourBdProtH
//---------------------------------------------------------------------------
#include "ActionEvent.h"
using namespace smartevents;
//---------------------------------------------------------------------------
#include "HelperNumberTextBtn.h"
#include "ProtokolName_t.h"
#include "ConnectionStateInfo_t.h"
//---------------------------------------------------------------------------
class HelperConnectFourBdProt
{
public:
    HelperConnectFourBdProt(
        ActionEvent<ProtokolName>* ev_protocolChange, // Протокол меняется из ГИП
        ActionEvent<const char*>* ev_comboBox_ComPortsChange, // Меняется номер ком-порта из ГИП
        ActionSelf<bool>* as_comPortOrTcpIp, // Изменяю вид программно: ком-порт или TCP/IP
        ActionSelf<const char*>* as_labelHint, // Текст подсказки
        ActionSelf<>* as_clearAllComPortName,  // Очистить список найденых ком-портов
        ActionSelf<bool>* as_setEnabledUpdateComPorts, // Установить доступность обновления ком-портов
        ActionSelf<const char*, const char*>* as_addComPortName, // Добавить имя ком-порта
        ActionSelf<ProtokolName>* as_setProtokolName, // Установить имя протокола
        ActionSelf<const char*, const char*>* as_setEndPoint, // Установить IP-адрес и TCP-порт
        ActionEvent<const char*>* ev_textBox_IP_AddrChange, // Текст ip-адреса изменился из ГИП
        ActionEvent<const char*>* ev_textBox_TCP_PortChange, // Текст tcp-порта изменился из ГИП
        ActionEvent<>* ev_button_UpdateNumberOfComPortSClick, // Обновите список ком-портов
        ActionEvent<>* ev_button_StartStopClick, // Запустить/Остановить обмен данными с БД
        ActionSelf<ConnectionStateInfo>* as_SetConnectionState, // Отобразить изменения о состоянии соединения в ГИП
        HelperNumberTextBtn* addrBd);
private:
    ActionSelf<bool>* _as_comPortOrTcpIp; // Изменяю вид программно: ком-порт или TCP/IP
    ActionSelf<const char*>* _as_labelHint; // Добавить подсказку

    ActionSelf<>* _as_clearAllComPortName;  // Очистить список найденых ком-портов
    ActionSelf<bool>* _as_setEnabledUpdateComPorts; // Установить доступность обновления ком-портов

    ActionSelf<const char*, const char*>* _as_addComPortName; // Добавить имя ком-порта
    ActionSelf<ProtokolName>* _as_setProtokolName;
    ActionSelf<const char*, const char*>* _as_setEndPoint;

    ActionEvent<ProtokolName>* _ev_protocolChange; // Протокол меняется из ГИП
    ActionEvent<const char*>* _ev_comboBox_ComPortsChange; // Меняется номер ком-порта из ГИП
    ActionEvent<const char*>* _ev_textBox_IP_AddrChange;  // Текст ip-адреса изменился из ГИП
    ActionEvent<const char*>* _ev_textBox_TCP_PortChange; // Текст tcp-порта изменился из ГИП
    ActionEvent<>* _ev_button_UpdateNumberOfComPortSClick; // Обновите список ком-портов
    ActionEvent<>* _ev_button_StartStopClick; // Запустить/Остановить обмен данными с БД
    ActionSelf<ConnectionStateInfo>* _as_SetConnectionState; // Отобразить изменения в ГИП
    HelperNumberTextBtn* _addrBd;
public:

    ActionSelf<bool>* GetSelfComPortOrTcpIp();
    ActionSelf<const char*>* GetSelfLabelHintSetText();

    ActionSelf<>* GetSelfClearAllComPortName();  // Очистить список найденых ком-портов
    ActionSelf<bool>* GetSelfSetEnabledUpdateComPorts(); // Установить доступность обновления ком-портов

    ActionSelf<const char*, const char*>* GetSelfAddComPortName();
    ActionSelf<ProtokolName>* GetSelfSetProtokolName();
    ActionSelf<const char*, const char*>* GetSelfSetEndPoint();
    ActionSelf<ConnectionStateInfo>* GetSelfSetConnectionState(); // Отобразить изменения о состоянии соединения в ГИП

    ActionEvent<ProtokolName>* GetEventProtocolChange();
    ActionEvent<const char*>* GetEventComPortsChange();
    ActionEvent<const char*>* GetEventIpAddrChange(); // Текст ip-адреса изменился из ГИП
    ActionEvent<const char*>* GetEventTcpPortChange(); // Текст tcp-порта изменился из ГИП
    ActionEvent<>* GetEventUpdateNumberOfComPorts(); // Обновите список ком-портов
    ActionEvent<>* GetEventStartStopClick(); // Запустить/Остановить обмен данными с БД
    HelperNumberTextBtn* GetHelperNumberAddrBd();
};
//---------------------------------------------------------------------------
#endif
