//---------------------------------------------------------------------------
#pragma hdrstop
#include "AllProtokolS.h"
#include "TextHelper.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
AllProtokolS::AllProtokolS()
{
    protokol = new RSProtokol_t();
    comPortPtr = comPortCount;
    _flagError = false;
}
//---------------------------------------------------------------------------
AllProtokolS::~AllProtokolS()
{
    delete protokol;
}
//---------------------------------------------------------------------------
ProtokolName AllProtokolS::GetProtokolName()
{
    return _protokolName;
}
//---------------------------------------------------------------------------
void AllProtokolS::SetProtokolName(ProtokolName protokolName)
{
    _protokolName = protokolName;
    switch ( protokolName )
    {
    case ProtokolName_t::NineBit: // 9-�� ������
        protokol->flagModbusProtokol = 0;
        break;
    case ProtokolName_t::ModBus_RTU: // ModBus RTU
        protokol->flagModbusProtokol = 1;
        break;
    case ProtokolName_t::ModBus_TCP: // ModBus TCP
        protokol->flagModbusProtokol = 2;
        break;
    case ProtokolName_t::ModBus_RTU_IP: // ModBus RTU (TCP/IP)
        protokol->flagModbusProtokol = 3;
        break;
    case ProtokolName_t::NeVybran:
        protokol->flagModbusProtokol = -1;
        break;
    }
}
//---------------------------------------------------------------------------
void AllProtokolS::UpdateComPotrs()
{
    AnsiString comPortName;
    comPortPtr = 1;
    protokol->flagModbusProtokol = 0; // 9-�� ������
    while ( comPortPtr <= comPortCount )
    {
        comPortName = "\\\\.\\COM" + IntToStr( comPortPtr );
        int errorCode = protokol->RSConnect( comPortName.c_str() );
        findComPorts[comPortPtr - 1] = false;
        if ( errorCode == 0 )
        {
           protokol->RSDisConnect();
           findComPorts[comPortPtr - 1] = true;
        }
        comPortPtr++;
    }
    comPortPtr = 0;
}
//---------------------------------------------------------------------------
bool AllProtokolS::NextComPortIndex(int * comPortIndex)
{
    while ( comPortPtr < comPortCount )
    {
        if ( findComPorts[comPortPtr] )
        {
            *comPortIndex = comPortPtr + 1;
            comPortPtr++;
            return true;
        }
        comPortPtr++;
    }
    return false;
}
//---------------------------------------------------------------------------
void AllProtokolS::SetComPortName(const char* cpName)
{
    TextHelper::CopyText(comPortName, cpName, comPortNameSize);
}
//---------------------------------------------------------------------------
void AllProtokolS::SetIpAddr(const char* ipAddr)
{
    TextHelper::CopyText(protokol->Data.IP_Addr, ipAddr, ipAddrSize);
}
//---------------------------------------------------------------------------
void AllProtokolS::SetTcpPort(int tcpPort)
{
    protokol->Data.IP_Port = tcpPort;
}
//---------------------------------------------------------------------------
void AllProtokolS::SetBdAddr(int addrBd)
{
    switch ( _protokolName )
    {
    case ProtokolName_t::NineBit: // 9-�� ������
    case ProtokolName_t::ModBus_RTU: // ModBus RTU
        protokol->AddrBD = addrBd;
        break;
    case ProtokolName_t::ModBus_TCP: // ModBus TCP
    case ProtokolName_t::ModBus_RTU_IP: // ModBus RTU (TCP/IP)
        protokol->Data.Addr_BD_TCP = addrBd;
        break;
    case ProtokolName_t::NeVybran:
        _flagError = true;
        break;
    }
}
//---------------------------------------------------------------------------
bool AllProtokolS::Open()
{
    if (_flagError == true)
    {
        _flagError = false;
        return false;
    }
    protokol->flagSpeed = true;
    int errorCode = protokol->RSConnect( comPortName );
    if ( errorCode != 0 )
    {
        return false;
    }
    ErrorCount = 0;
    ev_ErrorCountIncrement( "0" );
    return true;
}
//---------------------------------------------------------------------------
void AllProtokolS::Close()
{
    protokol->RSDisConnect();
}
//---------------------------------------------------------------------------
bool AllProtokolS::ErrorChecked(int nullValue)
{
    if ( nullValue != 0 )
    {
        ev_ErrorCountIncrement( IntToStr(++ErrorCount).c_str() );
        return false;
    }
    return true;
}
//---------------------------------------------------------------------------
ActionEvent<const char*>* AllProtokolS::GetEventErrorCountIncrement()
{
    return & ev_ErrorCountIncrement;
}
//---------------------------------------------------------------------------
bool AllProtokolS::GetVersia(char * versia)
{
    return ErrorChecked( protokol->GetVersia( versia ) );
}
//---------------------------------------------------------------------------
bool AllProtokolS::GetSsp(unsigned char * ssp)
{
    return ErrorChecked( protokol->GetSSP( ssp ) );
}
//---------------------------------------------------------------------------
bool AllProtokolS::GetTimeInterval(unsigned char * timeInt)
{
    return ErrorChecked( protokol->GetTimeInterval( timeInt ) );
}
//---------------------------------------------------------------------------
bool AllProtokolS::SetTimeInterval(unsigned char timeInt)
{
    return ErrorChecked( protokol->SetTimeInterval( timeInt ) );
}
//---------------------------------------------------------------------------
bool AllProtokolS::GetIndAdrZ(unsigned char * indAdrZ)
{
    int result = -1;
    unsigned long data;
    switch ( _protokolName )
    {
    case ProtokolName_t::NineBit: // 9-�� ������
        result = protokol->ReadFlashInvert( 0x04, & data );
        break;
    case ProtokolName_t::ModBus_RTU: // ModBus RTU
    case ProtokolName_t::ModBus_TCP: // ModBus TCP
    case ProtokolName_t::ModBus_RTU_IP: // ModBus RTU (TCP/IP)
        result = protokol->ReadFlash2( 0x300+1, & data );
        break;
    }
    *indAdrZ = (data & 0xFF);
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::SetIndAdrZ(unsigned char indAdrZ)
{
    int result = -1;
    result = protokol->SetIndAdr( indAdrZ );
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::GetGroupAdrZ(unsigned char * groupAdrZ)
{
    int result;
    unsigned long data;
    result = protokol->ReadFlashInvert( 0x05, & data );
    *groupAdrZ = (data & 0xFF);
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::SetGroupAdrZ(unsigned char groupAdrZ)
{
    int result = -1;
    result = protokol->SetGrpAdr( groupAdrZ );
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::GetDnuZ(unsigned short * dnuZ)
{
    int result;
    unsigned long data;
    result = protokol->ReadFlashInvert( 0, & data );
    *dnuZ = (data & 0xFFFF);
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::SetDnuZ(unsigned short dnuZ)
{
    int result = -1;
    result = protokol->SetDNU( dnuZ );
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::GetVoltageHiZ_Bd85(unsigned short * voltageHiZ)
{
    int result;
    unsigned long data;
    result = protokol->ReadFlashInvert( 0x03, & data );
    *voltageHiZ = (data & 0xFFFF);
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::SetVoltageHiZ_Bd85(unsigned short voltageHiZ)
{
    int result;
    result = protokol->SetUhi( voltageHiZ );
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::GetWidthPwmZ_Bd85(unsigned short * widthPwmZ)
{
    int result;
    unsigned long data;
    result = protokol->ReadFlashInvert( 0x08, & data );
    *widthPwmZ = (data & 0xFFFF);
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::SetWidthPwmZ_Bd85(unsigned short widthPwmZ)
{
    int result;
    result = protokol->SetLEDOtkl( widthPwmZ );
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::GetOffsetPwmZ_Bd85(unsigned short * offsetPwmZ)
{
    int result;
    unsigned long data;
    result = protokol->ReadFlashInvert( 0x09, & data );
    *offsetPwmZ = (data & 0xFFFF);
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::SetOffsetPwmZ_Bd85(unsigned short offsetPwmZ)
{
    int result;
    result = protokol->SetLEDAmp( offsetPwmZ );
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::GetPeriodPwmZ_Bd85(unsigned short * periodPwmZ)
{
    int result;
    unsigned long data;
    result = protokol->ReadFlashInvert( 0x07, & data );
    *periodPwmZ = (data & 0xFFFF);
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::SetPeriodPwmZ_Bd85(unsigned short periodPwmZ)
{
    int result;
    result = protokol->SetUhi2( periodPwmZ );
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::GetIndAdr(unsigned char * indAdr)
{
    return ErrorChecked( protokol->GetIndAdr( indAdr ) );
}
//---------------------------------------------------------------------------
bool AllProtokolS::GetGrpAdr(unsigned char * groupAdr)
{
    return ErrorChecked( protokol->GetGrpAdr( groupAdr ) );
}
//---------------------------------------------------------------------------
bool AllProtokolS::GetTemperature(unsigned short * temper)
{
    unsigned int data;
    int result = protokol->GetTemp( & data );
    *temper = (data & 0xFFFF);
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::GetDNU(unsigned short * dnu)
{
    unsigned int data;
    int result = protokol->GetDNU( & data );
    *dnu = (data & 0xFFFF);
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::GetDVU(unsigned short * dvu)
{
    unsigned int data;
    int result = protokol->GetDVU( & data );
    *dvu = (data & 0xFFFF);
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::GetVoltageHi(unsigned short * voltageHi)
{
    unsigned int data;
    int result = protokol->GetUhi( & data );
    *voltageHi = (data & 0xFFFF);
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::GetWidthPwm(unsigned short * widthPwm)
{
    unsigned int data;
    int result = protokol->GetSIM3( & data );
    *widthPwm = (data & 0xFFFF);
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::GetPeriodPwm(unsigned short * periodPwm)
{
    unsigned int data;
    int result = protokol->GetSIM4( & data );
    *periodPwm = (data & 0xFFFF);
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::GetScaling(unsigned short * scaling)
{
    unsigned int data;
    int result = protokol->GetCountImp( & data );
    *scaling = (data & 0xFFFF);
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::SetArch(unsigned char Arch)
{
    int result = protokol->ARCHCon( Arch );
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::ReadFlashInvert(
    unsigned int memoryAddr,
    unsigned long * data)
{
    int result = protokol->ReadFlashInvert(memoryAddr, data);
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::ReadFlash(
    unsigned int memoryAddr,
    unsigned long * data)
{
    int result = protokol->ReadFlash(memoryAddr, data);
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::ReadFlash2(
    unsigned int memoryAddr,
    unsigned long * data)
{
    int result = protokol->ReadFlash2(memoryAddr, data);
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::WriteFlashInvert(
    unsigned int memoryAddr,
    unsigned long data)
{
    int result = protokol->WriteFlashInvert(memoryAddr, data);
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::WriteFlash(
    unsigned int memoryAddr,
    unsigned long data)
{
    int result = protokol->WriteFlash(memoryAddr, data);
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
bool AllProtokolS::WriteFlash2(
    unsigned int memoryAddr,
    unsigned long data)
{
    int result = protokol->WriteFlash2(memoryAddr, data);
    return ErrorChecked( result );
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
