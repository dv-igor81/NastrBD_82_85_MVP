//---------------------------------------------------------------------------
#ifndef ConnectBdProtH
#define ConnectBdProtH
//---------------------------------------------------------------------------
#include "HelperConnectFourBdProt.h"
#include "Protokol_t.h"
#include "IAllProtokolS.h"
#include "ITask.h"
//---------------------------------------------------------------------------
class ConnectBdProt{
public:
    ConnectBdProt(
        HelperConnectFourBdProt* bdProt,
        IAllProtokolS * allProtokol,
        ITask * task);
private:
    enum { ipAddrSize = 16, tcpPortSize = 6 };
    // ModBus TCP
    char strIpAddr_TCP[ipAddrSize];
    char strTcpPort_TCP[tcpPortSize];
    // ModBus RTU (TCP/IP)
    char strIpAddr_RTU_IP[ipAddrSize];
    char strTcpPort_RTU_IP[tcpPortSize];

    HelperConnectFourBdProt* _bdProt;
    ActionSelf<Protokol> as_protocolChanged;
    void ProtocolChanged(Protokol protocolName);

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

    ActionEvent<bool> ev_comPortOrTcpIp;
    ActionEvent<const char*> ev_labelHint;
    ActionEvent<Protokol> ev_setProtokolName;
    ActionEvent<const char*, const char*> ev_setEndPoint;
    ActionEvent<const char*, const char*> ev_addComPortName;

    void SettingsChengeProtokol(Protokol protokolName, bool fromPresenter);

    IAllProtokolS * _allProtokol;
    ITask * _task;

    void UpdateNumberOfComPortS();

    ActionSelf<> as_UpdateComPotrsAsynk;
    void UpdateComPotrsAsynk();
};
//---------------------------------------------------------------------------
#endif
