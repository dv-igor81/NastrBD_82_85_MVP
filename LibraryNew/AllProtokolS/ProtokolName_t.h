//---------------------------------------------------------------------------
#ifndef ProtokolName_tH
#define ProtokolName_tH
//---------------------------------------------------------------------------
namespace ProtokolName_t
{
    enum ProtokolName_t
    {
        NineBit = 0, // 9-битный
        ModBus_RTU = 1, // ModBus RTU
        ModBus_TCP = 2, // ModBus TCP
        ModBus_RTU_IP = 3, // ModBus RTU (TCP/IP)
        NeVybran = 4 // Протокол не выбран
    };
}
typedef ProtokolName_t::ProtokolName_t ProtokolName;
//---------------------------------------------------------------------------
#endif
