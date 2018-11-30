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
        ActionEvent<ProtokolName>* ev_protocolChange, // �������� �������� �� ���
        ActionEvent<const char*>* ev_comboBox_ComPortsChange, // �������� ����� ���-����� �� ���
        ActionSelf<bool>* as_comPortOrTcpIp, // ������� ��� ����������: ���-���� ��� TCP/IP
        ActionSelf<const char*>* as_labelHint, // ����� ���������
        ActionSelf<>* as_clearAllComPortName,  // �������� ������ �������� ���-������
        ActionSelf<bool>* as_setEnabledUpdateComPorts, // ���������� ����������� ���������� ���-������
        ActionSelf<const char*, const char*>* as_addComPortName, // �������� ��� ���-�����
        ActionSelf<ProtokolName>* as_setProtokolName, // ���������� ��� ���������
        ActionSelf<const char*, const char*>* as_setEndPoint, // ���������� IP-����� � TCP-����
        ActionEvent<const char*>* ev_textBox_IP_AddrChange, // ����� ip-������ ��������� �� ���
        ActionEvent<const char*>* ev_textBox_TCP_PortChange, // ����� tcp-����� ��������� �� ���
        ActionEvent<>* ev_button_UpdateNumberOfComPortSClick, // �������� ������ ���-������
        ActionEvent<>* ev_button_StartStopClick, // ���������/���������� ����� ������� � ��
        ActionSelf<ConnectionStateInfo>* as_SetConnectionState, // ���������� ��������� � ��������� ���������� � ���
        HelperNumberTextBtn* addrBd);
private:
    ActionSelf<bool>* _as_comPortOrTcpIp; // ������� ��� ����������: ���-���� ��� TCP/IP
    ActionSelf<const char*>* _as_labelHint; // �������� ���������

    ActionSelf<>* _as_clearAllComPortName;  // �������� ������ �������� ���-������
    ActionSelf<bool>* _as_setEnabledUpdateComPorts; // ���������� ����������� ���������� ���-������

    ActionSelf<const char*, const char*>* _as_addComPortName; // �������� ��� ���-�����
    ActionSelf<ProtokolName>* _as_setProtokolName;
    ActionSelf<const char*, const char*>* _as_setEndPoint;

    ActionEvent<ProtokolName>* _ev_protocolChange; // �������� �������� �� ���
    ActionEvent<const char*>* _ev_comboBox_ComPortsChange; // �������� ����� ���-����� �� ���
    ActionEvent<const char*>* _ev_textBox_IP_AddrChange;  // ����� ip-������ ��������� �� ���
    ActionEvent<const char*>* _ev_textBox_TCP_PortChange; // ����� tcp-����� ��������� �� ���
    ActionEvent<>* _ev_button_UpdateNumberOfComPortSClick; // �������� ������ ���-������
    ActionEvent<>* _ev_button_StartStopClick; // ���������/���������� ����� ������� � ��
    ActionSelf<ConnectionStateInfo>* _as_SetConnectionState; // ���������� ��������� � ���
    HelperNumberTextBtn* _addrBd;
public:

    ActionSelf<bool>* GetSelfComPortOrTcpIp();
    ActionSelf<const char*>* GetSelfLabelHintSetText();

    ActionSelf<>* GetSelfClearAllComPortName();  // �������� ������ �������� ���-������
    ActionSelf<bool>* GetSelfSetEnabledUpdateComPorts(); // ���������� ����������� ���������� ���-������

    ActionSelf<const char*, const char*>* GetSelfAddComPortName();
    ActionSelf<ProtokolName>* GetSelfSetProtokolName();
    ActionSelf<const char*, const char*>* GetSelfSetEndPoint();
    ActionSelf<ConnectionStateInfo>* GetSelfSetConnectionState(); // ���������� ��������� � ��������� ���������� � ���

    ActionEvent<ProtokolName>* GetEventProtocolChange();
    ActionEvent<const char*>* GetEventComPortsChange();
    ActionEvent<const char*>* GetEventIpAddrChange(); // ����� ip-������ ��������� �� ���
    ActionEvent<const char*>* GetEventTcpPortChange(); // ����� tcp-����� ��������� �� ���
    ActionEvent<>* GetEventUpdateNumberOfComPorts(); // �������� ������ ���-������
    ActionEvent<>* GetEventStartStopClick(); // ���������/���������� ����� ������� � ��
    HelperNumberTextBtn* GetHelperNumberAddrBd();
};
//---------------------------------------------------------------------------
#endif
