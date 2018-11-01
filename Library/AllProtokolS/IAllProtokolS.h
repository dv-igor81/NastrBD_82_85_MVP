//---------------------------------------------------------------------------
#ifndef IAllProtokolSH
#define IAllProtokolSH
//---------------------------------------------------------------------------
#include "ProtokolName_t.h"
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

    virtual void SetProtokol(ProtokolName protokolName) = 0;
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
    virtual bool GetOffsetPwmZ_Bd85(unsigned short * offsetPwmZ) = 0; // ������� �������� ��� ��������
    virtual bool GetPeriodPwmZ_Bd85(unsigned short * periodPwmZ) = 0; // ������� ������ ��� ��������

    virtual bool GetIndAdr(unsigned char * indAdr) = 0; // ������� �������������� ����� ��
    virtual bool GetGrpAdr(unsigned char * groupAdr) = 0; // ������� ��������� ����� ��
    virtual bool GetTemperature(unsigned short * temper) = 0; // �������� ����������� �� (�� 0x08)
    virtual bool GetDNU(unsigned short * dnu) = 0; // �������� ��� ���������� (�� 0x17)
    virtual bool GetDVU(unsigned short * dvu) = 0; // �������� ��� ���������� (�� 0x18)
    virtual bool GetVoltageHi(unsigned short * voltageHi) = 0; // �������� ���������� ������� (�� 0x07)
    virtual bool GetWidthPwm(unsigned short * widthPwm) = 0; // �������� ������������ ��� (�� 0x1C, 3)
    virtual bool GetPeriodPwm(unsigned short * periodPwm) = 0; // �������� ������ ��� (�� 0x1C, 4)
    virtual bool GetScaling(unsigned short * scaling) = 0; // �������� ���� ���������
};
//---------------------------------------------------------------------------
#endif
