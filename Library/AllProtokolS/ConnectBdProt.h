//---------------------------------------------------------------------------
#ifndef ConnectBdProtH
#define ConnectBdProtH
//---------------------------------------------------------------------------
#include "HelperConnectFourBdProt.h"
#include "ProtokolName_t.h"
#include "ConnectionStateInfo_t.h"
#include "IAllProtokolS.h"
#include "ITask.h"
#include "TaskWithParam.h"
//---------------------------------------------------------------------------
class ConnectBdProt{
public:
    ConnectBdProt(
        HelperConnectFourBdProt* bdProt,
        IAllProtokolS * allProtokol,
        TaskWithParam * task);

    IAllProtokolS * _allProtokol;
    TaskWithParam * _task;
    int _addrBd;

    void SetActionOprosStart( ActionSelf<>* action );
    void SetActionOprosIter( ActionSelf<>* action );
    void SetActionOprosEnd( ActionSelf<>* action );
    ActionEvent<ConnectionStateInfo>* GetEventSetConnectionState();
    void Disconnect(); // Публичный, чтобы дать возможность презентеру разорвать соединение
private:
    enum { ipAddrSize = 16, tcpPortSize = 6, comPortNameSize = 7 };   //enum { comPortCount = 100, comPortNameSize = 7 };
    // ModBus TCP
    char strIpAddr_TCP[ipAddrSize];
    char strTcpPort_TCP[tcpPortSize];
    // ModBus RTU (TCP/IP)
    char strIpAddr_RTU_IP[ipAddrSize];
    char strTcpPort_RTU_IP[tcpPortSize];
    // Com-Port Name
    char comPortName[comPortNameSize];

    HelperConnectFourBdProt* _bdProt;

    ActionSelf<ProtokolName> as_protocolChanged;
    void ProtocolChanged(ProtokolName protocolName);

    ActionSelf<const char*> as_comPortsChange;
    void ComPortsChange(const char* comPortName);

    ActionSelf<> as_windowShow;
    void WindowShow();

    ActionSelf<const char*> as_changeIpAddr;
    void ChangeIpAddr(const char* textIpAddr);

    ActionSelf<const char*> as_changeTcpPort;
    void ChangeTcpPort(const char* textTcpPort);

    ActionSelf<> as_updateNumberOfComPorts;
    void UpdateNumberOfComPorts();

    ActionSelf<> as_startStopClick;
    void StartStopClick();

    ActionSelf<> as_UpdateComPortsInfo;
    void UpdateComPortsInfo();

    ActionSelf<> as_UpdateComPotrsAsynk;
    void UpdateComPotrsAsynk();

    ActionSelf<> as_ConnectionAsynk;
    void ConnectionAsynk();

    ActionSelf<> as_SetControlStateInvoke;
    void SetControlStateInvoke();

    ActionEvent<bool> ev_comPortOrTcpIp;
    ActionEvent<const char*> ev_labelHint;

    ActionEvent<> ev_clearAllComPortName;
    ActionEvent<bool> ev_setEnabledUpdateComPorts;

    ActionEvent<ProtokolName> ev_setProtokolName;
    ActionEvent<const char*, const char*> ev_setEndPoint;
    ActionEvent<const char*, const char*> ev_addComPortName;
    ActionEvent<ConnectionStateInfo> ev_SetConnectionState;

    ActionSelf<>* as_OprosStart;
    ActionSelf<>* as_OprosIter;
    ActionSelf<>* as_OprosEnd;

    ActionSelf<int> as_SetAddrBdNumber;
    void SetAddrBdNumber(int addrBd);

    void SettingsChengeProtokol(ProtokolName pName, bool fromPresenter);
    void WorkInLoop();

    ProtokolName _protokolName;
    void Connect();
    void SetTcpPort(const char* textTcpPort, int defTcpPort);
    void SetControlFromConnectionState(ConnectionStateInfo state);
    bool _isConnected;
    bool _bfOprosInLoop;
    ConnectionStateInfo _state;

    HelperNumberTextBtn* _addrBdHelper;

    int* _addrBdPtr;
    int _addrBd_NineBit;
    int _addrBd_ModBus_RTU;
    int _addrBd_ModBus_TCP;
    int _addrBd_ModBus_RTU_IP;
};
//---------------------------------------------------------------------------
#endif
