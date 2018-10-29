//---------------------------------------------------------------------------
#ifndef PresenterWindowMainBd85H
#define PresenterWindowMainBd85H
//---------------------------------------------------------------------------
#include "IWindowMainBd85.h"
#include "ConnectBdProt.h"
#include "IAllProtokolS.h"
#include "ITask.h"
//---------------------------------------------------------------------------
class PresenterWindowMainBd85
{
public:
    PresenterWindowMainBd85(
        IWindowMainBd85 * view,
        IAllProtokolS * allProtokol,
        ITask * task,
        ActionSelf<> & as_ShowDispetWindow);
    ~PresenterWindowMainBd85();
    bool IsViewLoaded();
private:
    IWindowMainBd85 * _view;
    ConnectBdProt* _connectBdProt;

    ActionSelf<> as_FormClose;
    void FormClose();

    void ConnectIsGood(); // Соединение (по ком порту или TCP/IP) прошло удачно

    ActionSelf<> as_OprosStar;
    void OprosStar();

    ActionSelf<> as_OprosStarInvoke;
    void OprosStarInvoke();

    ActionSelf<> as_OprosIter;
    void OprosIter();

    ActionSelf<> as_OprosIterInvoke;
    void OprosIterInvoke();

    ActionSelf<> as_OprosEnd;
    void OprosEnd();

    ActionSelf<> as_OprosEndInvoke;
    void OprosEndInvoke();

    ActionSelf<ConnectionStateInfo> as_SetConnectionState;
    void SetConnectionState( ConnectionStateInfo state );

    ActionEvent<> ev_Show;
    bool _isViewLoaded;

    IAllProtokolS * _allProtokol;
    ITask * _task;

    ActionEvent<StartDataNewBd85*> ev_DisplayStartData;
    StartDataNewBd85* _startData;

    ActionEvent<IterDataNewBd85*> ev_DisplayIterData;
    IterDataNewBd85* _iterData;

    ActionEvent<> ev_ShowDispetWindow;

    bool InitMkInBd();
    bool _isConnected;
    bool ReadEEProm();

    int _readParamIndex;
    enum { verPoSize = 5 };
    //===>> Данные, считанные из EEPROM МК в БД
    char _verPo[5];
    char _indAddrZad;
    char _groupAddrZad;
    unsigned short _dnuZad;
    unsigned short _voltageHiZad;
    unsigned short _widthPwmZad;
    unsigned short _offsetPwmZ;
    unsigned short _periodPwmZ;
    //<<=== Данные, считанные из EEPROM МК в БД

    unsigned char _ssp;
    unsigned char _indAddr;
};
//---------------------------------------------------------------------------
#endif
