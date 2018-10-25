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
    void SetTcpPort(int tcpPort);
    void SetBdAddr(int addrBd);
    bool Open();
    void Close();
    bool GetVersia(char * versia);
    bool GetSsp(unsigned char * ssp);
    bool GetTimeInterval(unsigned char * timeInt);
    bool SetTimeInterval(unsigned char timeInt);
    bool GetIndAdrZ(unsigned char * indAdrZ);
    bool GetGroupAdrZ(unsigned char * groupAdrZ);
    bool GetDnuZ(unsigned short * dnuZ);
    bool GetVoltageHiZ_Bd85(unsigned short * voltageHiZ);
    bool GetWidthPwmZ_Bd85(unsigned short * widthPwmZ);
    bool GetOffsetPwmZ_Bd85(unsigned short * offsetPwmZ);

    ActionEvent<const char*>* GetEventErrorCountIncrement();

private:
    enum { comPortCount = 100, ipAddrSize = 16, comPortNameSize = 7 };
    bool findComPorts[comPortCount];
    char comPortName[comPortNameSize];
    RSProtokol_t * protokol;
    int comPortPtr;
    bool _flagError;
    Protokol _protokolName;

    bool ErrorChecked(int nullValue);
    int ErrorCount;
    ActionEvent<const char*> ev_ErrorCountIncrement;
};
//---------------------------------------------------------------------------
#endif
