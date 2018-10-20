//---------------------------------------------------------------------------
#ifndef Protokol_tH
#define Protokol_tH
namespace Protokol_t
{
    enum Protokol_t
    {
        NineBit = 0, // 9-������
        ModBus_RTU = 1, // ModBus RTU
        ModBus_TCP = 2, // ModBus TCP
        ModBus_RTU_IP = 3, // ModBus RTU (TCP/IP)
        NeVybran = 4 // �������� �� ������
    };
}
typedef Protokol_t::Protokol_t Protokol;
//---------------------------------------------------------------------------
#endif
