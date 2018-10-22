//---------------------------------------------------------------------------
#ifndef AllProtokolSH
#define AllProtokolSH
//---------------------------------------------------------------------------
#include "IAllProtokolS.h"
#include "RSProtokol.h"
//---------------------------------------------------------------------------
class AllProtokolS : public IAllProtokolS
{
public:
    AllProtokolS();
    ~AllProtokolS();
    void UpdateComPotrs();
    bool NextComPortIndex(int * comPortIndex);

    void SetProtokol(Protokol protokolName);
    void SetComPortName(const char* cpName);
    void SetIpAddr(const char* ipAddr);
private:
    enum { comPortCount = 100, ipAddrSize = 16, comPortNameSize = 7 };
    bool findComPorts[comPortCount];
    char comPortName[comPortNameSize];
    RSProtokol_t * protokol;
    int comPortPtr;


};
//---------------------------------------------------------------------------
#endif
