//---------------------------------------------------------------------------
#ifndef ConnectBdProtH
#define ConnectBdProtH
//---------------------------------------------------------------------------
#include "HelperConnectFourBdProt.h"
#include "Protokol_t.h"
//---------------------------------------------------------------------------
class ConnectBdProt{
public:
    ConnectBdProt(HelperConnectFourBdProt* bdProt);
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
};
//---------------------------------------------------------------------------
#endif
