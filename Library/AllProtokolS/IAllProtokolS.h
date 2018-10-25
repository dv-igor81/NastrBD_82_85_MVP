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
    virtual bool GetVersia(char * versia) = 0; // Считать версию программы БД
    virtual bool GetSsp(unsigned char * ssp) = 0; // Считать слово состояния программы БД
    virtual bool GetTimeInterval(unsigned char * timeInt) = 0; // Получить константу, которая определяет интервал набора счёта
    virtual bool SetTimeInterval(unsigned char timeInt) = 0; // Установить константу, которая определяет интервал набора счёта
    virtual bool GetIndAdrZ(unsigned char * indAdrZ) = 0; // Считать индивидуальный адрес БД заданный
    virtual bool GetGroupAdrZ(unsigned char * groupAdrZ) = 0; // Считать групповой адрес БД заданный
    virtual bool GetDnuZ(unsigned short * dnuZ) = 0; // Считать значение ДНУ заданное
    virtual bool GetVoltageHiZ_Bd85(unsigned short * voltageHiZ) = 0; // Считать напряжение высокое заданное
    virtual bool GetWidthPwmZ_Bd85(unsigned short * widthPwmZ) = 0; // Считать длительность ШИМ заданная
};
//---------------------------------------------------------------------------
#endif
