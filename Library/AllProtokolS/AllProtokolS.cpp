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
void AllProtokolS::UpdateComPotrs()
{
    AnsiString comPortName;
    comPortPtr = 1;
    protokol->flagModbusProtokol = 0; // 9-ти битный
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
void AllProtokolS::SetProtokol(Protokol protokolName)
{
    _protokolName = protokolName;
    switch ( protokolName )
    {
    case Protokol_t::NineBit: // 9-ти битный
        protokol->flagModbusProtokol = 0;
        break;
    case Protokol_t::ModBus_RTU: // ModBus RTU
        protokol->flagModbusProtokol = 1;
        break;
    case Protokol_t::ModBus_TCP: // ModBus TCP
        protokol->flagModbusProtokol = 2;
        break;
    case Protokol_t::ModBus_RTU_IP: // ModBus RTU (TCP/IP)
        protokol->flagModbusProtokol = 3;
        break;
    case Protokol_t::NeVybran:
        protokol->flagModbusProtokol = -1;
        break;
    }
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
    case Protokol_t::NineBit: // 9-ти битный
    case Protokol_t::ModBus_RTU: // ModBus RTU
        protokol->AddrBD = addrBd;
        break;
    case Protokol_t::ModBus_TCP: // ModBus TCP
    case Protokol_t::ModBus_RTU_IP: // ModBus RTU (TCP/IP)
        protokol->Data.Addr_BD_TCP = addrBd;
        break;
    case Protokol_t::NeVybran:
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
    int errorCode = protokol->RSConnect( comPortName );
    if ( errorCode != 0 )
    {
        return false;
    }
    return true;
}
//---------------------------------------------------------------------------
void AllProtokolS::Close()
{
    protokol->RSDisConnect();
}
//---------------------------------------------------------------------------
int AllProtokolS::GetVersia(char * versia)
{
    return protokol->GetVersia( versia );
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
