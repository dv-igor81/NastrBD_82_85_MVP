//---------------------------------------------------------------------------
#ifndef IAllProtokolSH
#define IAllProtokolSH
//---------------------------------------------------------------------------
#include "Protokol_t.h"
//---------------------------------------------------------------------------
class IAllProtokolS
{
public:
    virtual ~IAllProtokolS(){};
    virtual void UpdateComPotrs() = 0;
    virtual bool NextComPortIndex(int * comPortIndex) = 0;

    virtual void SetProtokol(Protokol protokolName) = 0;
    virtual void SetComPortName(const char* comPortName) = 0;
    virtual void SetIpAddr(const char* ipAddr) = 0;
    virtual void SetTcpPort(int tcpPort) = 0;
    virtual void SetBdAddr(int addrBd) = 0;
    virtual bool Open() = 0;
    virtual void Close() = 0;
};
//---------------------------------------------------------------------------
#endif
