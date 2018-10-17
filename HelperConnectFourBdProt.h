//---------------------------------------------------------------------------
#ifndef HelperConnectFourBdProtH
#define HelperConnectFourBdProtH
//---------------------------------------------------------------------------
#include "ActionEvent.h"
using namespace smartevents;
//---------------------------------------------------------------------------
#include "HelperNumberTextBtn.h"
#include "Protokol_t.h"
//---------------------------------------------------------------------------
class HelperConnectFourBdProt
{
public:
    HelperConnectFourBdProt(
        ActionEvent<Protokol>* ev_protocolChange, // Протокол меняется из ГИП
        ActionSelf<bool>* as_comPortOrTcpIp, // Изменяю вид программно: ком-порт или TCP/IP
        ActionSelf<const char*>* as_labelHint, // Текст подсказки
        ActionSelf<const char*, const char*>* as_addComPortName, // Добавить имя ком-порта
        ActionEvent<>* ev_windowShow, // Событие показать окно
        ActionSelf<Protokol>* as_setProtokolName, // Установить имя протокола
        ActionSelf<const char*, const char*>* as_setEndPoint, // Установить IP-адрес и TCP-порт
        ActionEvent<const char*>* ev_textBox_IP_AddrChange, // Текст ip-адреса изменился из ГИП
        ActionEvent<const char*>* ev_textBox_TCP_PortChange, // Текст tcp-порта изменился из ГИП
        ActionEvent<>* ev_button_UpdateNumberOfComPortSClick, // Обновите список ком-портов
        ActionEvent<>* ev_button_StartStopClick, // Запустить/Остановить обмен данными с БД
        HelperNumberTextBtn* addrBd);
private:
    ActionSelf<bool>* _as_comPortOrTcpIp; // Изменяю вид программно: ком-порт или TCP/IP
    ActionSelf<const char*>* _as_labelHint; // Добавить подсказку
    ActionSelf<const char*, const char*>* _as_addComPortName; // Добавить имя ком-порта
    ActionSelf<Protokol>* _as_setProtokolName;
    ActionSelf<const char*, const char*>* _as_setEndPoint;

    ActionEvent<>* _ev_windowShow;
    ActionEvent<Protokol>* _ev_protocolChange; // Протокол меняется из ГИП
    ActionEvent<const char*>* _ev_textBox_IP_AddrChange;  // Текст ip-адреса изменился из ГИП
    ActionEvent<const char*>* _ev_textBox_TCP_PortChange; // Текст tcp-порта изменился из ГИП
    ActionEvent<>* _ev_button_UpdateNumberOfComPortSClick; // Обновите список ком-портов
    ActionEvent<>* _ev_button_StartStopClick; // Запустить/Остановить обмен данными с БД

    HelperNumberTextBtn* _addrBd;
public:
    ActionEvent<Protokol>* GetEventProtocolChange();
    ActionSelf<bool>* GetSelfComPortOrTcpIp();
    ActionSelf<const char*>* GetSelfLabelHintSetText();
    ActionSelf<const char*, const char*>* GetSelfAddComPortName();
    ActionEvent<>* GetEventWindowShow();
    ActionSelf<Protokol>* GetSelfSetProtokolName();
    ActionSelf<const char*, const char*>* GetSelfSetEndPoint();
    ActionEvent<const char*>* GetEventIpAddrChange(); // Текст ip-адреса изменился из ГИП
    ActionEvent<const char*>* GetEventTcpPortChange(); // Текст tcp-порта изменился из ГИП
    ActionEvent<>* GetEventUpdateNumberOfComPorts(); // Обновите список ком-портов
    ActionEvent<>* GetEventStartStopClick(); // Запустить/Остановить обмен данными с БД
};
//---------------------------------------------------------------------------
#endif
