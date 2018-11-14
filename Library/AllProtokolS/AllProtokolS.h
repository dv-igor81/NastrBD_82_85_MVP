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

    void SetProtokolName(ProtokolName protokolName);
    ProtokolName GetProtokolName();

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
    bool SetIndAdrZ(unsigned char indAdrZ);

    bool GetGroupAdrZ(unsigned char * groupAdrZ);
    bool SetGroupAdrZ(unsigned char groupAdrZ);

    bool GetDnuZ(unsigned short * dnuZ);
    bool SetDnuZ(unsigned short dnuZ);

    bool GetVoltageHiZ_Bd85(unsigned short * voltageHiZ);
    bool SetVoltageHiZ_Bd85(unsigned short voltageHiZ);

    bool GetWidthPwmZ_Bd85(unsigned short * widthPwmZ);
    bool SetWidthPwmZ_Bd85(unsigned short widthPwmZ);

    bool GetOffsetPwmZ_Bd85(unsigned short * offsetPwmZ);
    bool SetOffsetPwmZ_Bd85(unsigned short offsetPwmZ);

    bool GetPeriodPwmZ_Bd85(unsigned short * periodPwmZ);
    bool SetPeriodPwmZ_Bd85(unsigned short periodPwmZ);

    bool SetArch(unsigned char Arch);
    //===
    bool GetIndAdr(unsigned char * indAdr);
    bool GetGrpAdr(unsigned char * groupAdr);
    bool GetTemperature(unsigned short * temper);
    bool GetDNU(unsigned short * dnu);
    bool GetDVU(unsigned short * dvu);
    bool GetVoltageHi(unsigned short * voltageHi);
    bool GetWidthPwm(unsigned short * widthPwm);
    bool GetPeriodPwm(unsigned short * periodPwm);
    bool GetScaling(unsigned short * scaling);

    ActionEvent<const char*>* GetEventErrorCountIncrement();

    bool ReadFlashInvert(
        unsigned int memoryAddr,
        unsigned long * data);

    bool ReadFlash(
        unsigned int memoryAddr,
        unsigned long * data);
        
    bool ReadFlash2(
        unsigned int memoryAddr,
        unsigned long * data);

    bool WriteFlashInvert(
        unsigned int memoryAddr,
        unsigned long data);

    bool WriteFlash(
        unsigned int memoryAddr,
        unsigned long data);

    bool WriteFlash2(
        unsigned int memoryAddr,
        unsigned long data);

private:
    enum { comPortCount = 100, ipAddrSize = 16, comPortNameSize = 7 };
    bool findComPorts[comPortCount];
    char comPortName[comPortNameSize];
    RSProtokol_t * protokol;
    int comPortPtr;
    bool _flagError;
    ProtokolName _protokolName;

    bool ErrorChecked(int nullValue);
    int ErrorCount;
    ActionEvent<const char*> ev_ErrorCountIncrement;
};
//---------------------------------------------------------------------------
#endif
