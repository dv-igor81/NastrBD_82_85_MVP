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
        ITask * task);

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

    StartDataNewBd85* _data;

    bool InitMkInBd();
    bool _isConnected;
    bool ReadEEProm();
    double CodeToValue(unsigned short code);
    unsigned short ValueToCode(double value);

    double VoltageHiCodeToValue(unsigned short code);
    unsigned short VoltageHiValueToCode(double value);

    int _readParamIndex;
        enum { verPoSize = 5
        , indAddrZadSize = 4
        , uShortTextSize = 6 // 5 цифр и завершающий ноль
        , floatTextSize = 10
    };
    //===>> Данные, считанные из EEPROM МК в БД
    char _verPo[verPoSize];
    char _indAddrZad[indAddrZadSize];
    char _dnuZad[uShortTextSize];
    char _dnuValueZad[floatTextSize];
    char _voltageHiZad[uShortTextSize];
    char _voltageHiValueZad[floatTextSize];
    //<<=== Данные, считанные из EEPROM МК в БД
};
//---------------------------------------------------------------------------
#endif
