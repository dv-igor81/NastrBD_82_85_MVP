//---------------------------------------------------------------------------
#ifndef IAllProtokolSH
#define IAllProtokolSH
//---------------------------------------------------------------------------
#include "Protokol_t.h"
//---------------------------------------------------------------------------
#include "ActionEvent.h"
using namespace smartevents;
//---------------------------------------------------------------------------
class IAllProtokolS
{
public:
    virtual ~IAllProtokolS(){};

    virtual ActionEvent<const char*>* GetEventErrorCountIncrement() = 0;

    virtual void UpdateComPotrs() = 0;
    virtual bool NextComPortIndex(int * comPortIndex) = 0;

    virtual void SetProtokol(Protokol protokolName) = 0;
    virtual void SetComPortName(const char* comPortName) = 0;
    virtual void SetIpAddr(const char* ipAddr) = 0;
    virtual void SetTcpPort(int tcpPort) = 0;
    virtual void SetBdAddr(int addrBd) = 0;
    virtual bool Open() = 0;
    virtual void Close() = 0;
    virtual bool GetVersia(char * versia) = 0; // ������� ������ ��������� ��
    virtual bool GetSsp(unsigned char * ssp) = 0; // ������� ����� ��������� ��������� ��
    virtual bool GetTimeInterval(unsigned char * timeInt) = 0; // �������� ���������, ������� ���������� �������� ������ �����
    virtual bool SetTimeInterval(unsigned char timeInt) = 0; // ���������� ���������, ������� ���������� �������� ������ �����
    virtual bool GetIndAdrZ(unsigned char * indAdrZ) = 0; // ������� �������������� ����� �� ��������
    virtual bool GetGroupAdrZ(unsigned char * groupAdrZ) = 0; // ������� ��������� ����� �� ��������
    virtual bool GetDnuZ(unsigned short * dnuZ) = 0; // ������� �������� ��� ��������
    virtual bool GetVoltageHiZ_Bd85(unsigned short * voltageHiZ) = 0; // ������� ���������� ������� ��������
    virtual bool GetWidthPwmZ_Bd85(unsigned short * widthPwmZ) = 0; // ������� ������������ ��� ��������
};
//---------------------------------------------------------------------------
#endif
