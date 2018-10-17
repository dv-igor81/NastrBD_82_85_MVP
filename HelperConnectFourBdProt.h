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
        ActionEvent<Protokol>* ev_protocolChange, // �������� �������� �� ���
        ActionSelf<bool>* as_comPortOrTcpIp, // ������� ��� ����������: ���-���� ��� TCP/IP
        ActionSelf<const char*>* as_labelHint, // ����� ���������
        ActionSelf<const char*, const char*>* as_addComPortName, // �������� ��� ���-�����
        ActionEvent<>* ev_windowShow, // ������� �������� ����
        ActionSelf<Protokol>* as_setProtokolName, // ���������� ��� ���������
        ActionSelf<const char*, const char*>* as_setEndPoint, // ���������� IP-����� � TCP-����
        ActionEvent<const char*>* ev_textBox_IP_AddrChange, // ����� ip-������ ��������� �� ���
        ActionEvent<const char*>* ev_textBox_TCP_PortChange, // ����� tcp-����� ��������� �� ���
        ActionEvent<>* ev_button_UpdateNumberOfComPortSClick, // �������� ������ ���-������
        ActionEvent<>* ev_button_StartStopClick, // ���������/���������� ����� ������� � ��
        HelperNumberTextBtn* addrBd);
private:
    ActionSelf<bool>* _as_comPortOrTcpIp; // ������� ��� ����������: ���-���� ��� TCP/IP
    ActionSelf<const char*>* _as_labelHint; // �������� ���������
    ActionSelf<const char*, const char*>* _as_addComPortName; // �������� ��� ���-�����
    ActionSelf<Protokol>* _as_setProtokolName;
    ActionSelf<const char*, const char*>* _as_setEndPoint;

    ActionEvent<>* _ev_windowShow;
    ActionEvent<Protokol>* _ev_protocolChange; // �������� �������� �� ���
    ActionEvent<const char*>* _ev_textBox_IP_AddrChange;  // ����� ip-������ ��������� �� ���
    ActionEvent<const char*>* _ev_textBox_TCP_PortChange; // ����� tcp-����� ��������� �� ���
    ActionEvent<>* _ev_button_UpdateNumberOfComPortSClick; // �������� ������ ���-������
    ActionEvent<>* _ev_button_StartStopClick; // ���������/���������� ����� ������� � ��

    HelperNumberTextBtn* _addrBd;
public:
    ActionEvent<Protokol>* GetEventProtocolChange();
    ActionSelf<bool>* GetSelfComPortOrTcpIp();
    ActionSelf<const char*>* GetSelfLabelHintSetText();
    ActionSelf<const char*, const char*>* GetSelfAddComPortName();
    ActionEvent<>* GetEventWindowShow();
    ActionSelf<Protokol>* GetSelfSetProtokolName();
    ActionSelf<const char*, const char*>* GetSelfSetEndPoint();
    ActionEvent<const char*>* GetEventIpAddrChange(); // ����� ip-������ ��������� �� ���
    ActionEvent<const char*>* GetEventTcpPortChange(); // ����� tcp-����� ��������� �� ���
    ActionEvent<>* GetEventUpdateNumberOfComPorts(); // �������� ������ ���-������
    ActionEvent<>* GetEventStartStopClick(); // ���������/���������� ����� ������� � ��
};
//---------------------------------------------------------------------------
#endif
