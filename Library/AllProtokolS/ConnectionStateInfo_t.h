//---------------------------------------------------------------------------
#ifndef ConnectionStateInfo_tH
#define ConnectionStateInfo_tH
//---------------------------------------------------------------------------
namespace ConnectionStateInfo_t
{
    enum ConnectionStateInfo_t
    {
        // �������� ������������ ����������.
        // ��������� ������������ ��� ��������������
        // ��������� ������� ���������� �� ����� ��������.
        WaitConnect = 0,

        // ���������� �����������
        IsConnected = 1,

        // �������� ���������� ����� ������
        WaitLoopExit = 2,

        // ���������� �� �����������
        IsDisconnect = 3
    };
}
typedef ConnectionStateInfo_t::ConnectionStateInfo_t ConnectionStateInfo;
//---------------------------------------------------------------------------
#endif
