//---------------------------------------------------------------------------
#ifndef IAllProtokolSH
#define IAllProtokolSH
//---------------------------------------------------------------------------
#include "ProtokolName_t.h"
//---------------------------------------------------------------------------
#include "ActionEvent.h"
using namespace smarteventsMin;
//---------------------------------------------------------------------------
class IAllProtokolS
{
public:
    virtual ~IAllProtokolS(){};

    virtual ActionEvent<const char*>* GetEventErrorCountIncrement() = 0;

    virtual void UpdateComPotrs() = 0;
    virtual bool NextComPortIndex(int * comPortIndex) = 0;

    virtual void SetProtokolName(ProtokolName protokolName) = 0;
    virtual ProtokolName GetProtokolName() = 0;
    
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
    virtual bool SetIndAdrZ(unsigned char indAdrZ) = 0; // Прочитать индивидуальный адрес БД заданный

    virtual bool GetGroupAdrZ(unsigned char * groupAdrZ) = 0; // Считать групповой адрес БД заданный
    virtual bool SetGroupAdrZ(unsigned char groupAdrZ) = 0; // Прочитать групповой адрес БД заданный

    virtual bool GetDnuZ(unsigned short * dnuZ) = 0; // Считать значение ДНУ заданное
    virtual bool SetDnuZ(unsigned short dnuZ) = 0; // Прочитать значение ДНУ заданное

    virtual bool GetVoltageHiZ_Bd85(unsigned short * voltageHiZ) = 0; // Считать напряжение высокое заданное
    virtual bool SetVoltageHiZ_Bd85(unsigned short voltageHiZ) = 0; // Прочитать напряжение высокое заданное

    virtual bool GetWidthPwmZ_Bd85(unsigned short * widthPwmZ) = 0; // Считать длительность ШИМ заданная
    virtual bool SetWidthPwmZ_Bd85(unsigned short widthPwmZ) = 0; // Прочитать длительность ШИМ заданная

    virtual bool GetOffsetPwmZ_Bd85(unsigned short * offsetPwmZ) = 0; // Считать смешение ШИМ заданное
    virtual bool SetOffsetPwmZ_Bd85(unsigned short offsetPwmZ) = 0; // Прочитать смешение ШИМ заданное

    virtual bool GetPeriodPwmZ_Bd85(unsigned short * periodPwmZ) = 0; // Считать период ШИМ заданный
    virtual bool SetPeriodPwmZ_Bd85(unsigned short periodPwmZ) = 0; // Прочитать  период ШИМ заданный

    virtual bool SetArch(unsigned char Arch) = 0;

    virtual bool GetIndAdr(unsigned char * indAdr) = 0; // Считать индивидуальный адрес БД
    virtual bool GetGrpAdr(unsigned char * groupAdr) = 0; // Считать групповой адрес БД
    virtual bool GetTemperature(unsigned short * temper) = 0; // Получить температуру МК (КК 0x08)
    virtual bool GetDNU(unsigned short * dnu) = 0; // Получить ДНУ измеренное (КК 0x17)
    virtual bool GetDVU(unsigned short * dvu) = 0; // Получить ДВУ измеренное (КК 0x18)
    virtual bool GetVoltageHi(unsigned short * voltageHi) = 0; // Получить напряжение высокое (КК 0x07)
    virtual bool GetWidthPwm(unsigned short * widthPwm) = 0; // Получить длительность ШИМ (КК 0x1C, 3)
    virtual bool GetPeriodPwm(unsigned short * periodPwm) = 0; // Получить период ШИМ (КК 0x1C, 4)
    virtual bool GetScaling(unsigned short * scaling) = 0; // Получить счёт импульсов


    virtual bool ReadFlashInvert(
        unsigned int memoryAddr,
        unsigned long * data) = 0;

    //virtual bool ReadFlash(
    //    unsigned int memoryAddr,
    //    unsigned long * data) = 0;

    virtual bool ReadFlash2(
        unsigned int memoryAddr,
        unsigned long * data) = 0;

    virtual bool WriteFlashInvert(
        unsigned int memoryAddr,
        unsigned long data) = 0;

    //virtual bool WriteFlash(
    //    unsigned int memoryAddr,
    //    unsigned long data) = 0;

    virtual bool WriteFlash2(
        unsigned int memoryAddr,
        unsigned long data) = 0;

    virtual bool InitMkInBd() = 0; // Инициализация МК в БД (интервал набота счета, задать колтик = 8)
};
//---------------------------------------------------------------------------
#endif
