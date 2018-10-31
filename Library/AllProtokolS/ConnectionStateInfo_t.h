//---------------------------------------------------------------------------
#ifndef ConnectionStateInfo_tH
#define ConnectionStateInfo_tH
//---------------------------------------------------------------------------
namespace ConnectionStateInfo_t
{
    enum ConnectionStateInfo_t
    {
        // Ожидание установления соединения.
        // Состояние используется для предотвращения
        // повторной попытки соединения во время ожидания.
        WaitConnect = 0,

        // Соединение установлено
        IsConnected = 1,

        // Ожидание завершения цикла опроса
        WaitLoopExit = 2,

        // Соединение не установлено
        IsDisconnect = 3
    };
}
typedef ConnectionStateInfo_t::ConnectionStateInfo_t ConnectionStateInfo;
//---------------------------------------------------------------------------
#endif
