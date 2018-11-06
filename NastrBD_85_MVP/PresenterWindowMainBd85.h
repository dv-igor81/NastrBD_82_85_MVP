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

    void ConnectIsGood(); // ���������� (�� ��� ����� ��� TCP/IP) ������ ������

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

    ActionSelf<const char*> as_StartStopScaling;
    void StartStopScaling(const char* timeMeteringLimit);

    void ScalingOprosWork();
    ActionSelf<> as_ScalingOprosWorkInvoke;
    void ScalingOprosWorkInvoke();

    ActionSelf<> as_ClearScalingSumm;
    void ClearScalingSumm();

    ActionEvent<> ev_Show;
    bool _isViewLoaded;

    IAllProtokolS * _allProtokol;
    ITask * _task;

    ActionEvent<StartDataNewBd85*> ev_DisplayStartData;
    StartDataNewBd85* _startData;

    ActionEvent<IterDataNewBd85*> ev_DisplayIterData;
    IterDataNewBd85* _iterData;

    ActionEvent<ScalingDataNewBd85*> ev_ScalingOpros;
    ScalingDataNewBd85* _scalingData;

    ActionEvent<> ev_ShowDispetWindow;

    bool InitMkInBd();
    bool _isConnected;
    bool ReadEEProm();

    int _readParamIndex;
    enum { verPoSize = 5 };
    //===>> ������, ��������� �� EEPROM �� � ��
    char _verPo[5];
    char _indAddrZad;
    char _groupAddrZad;
    unsigned short _dnuZad;
    unsigned short _voltageHiZad;
    unsigned short _widthPwmZad;
    unsigned short _offsetPwmZ;
    unsigned short _periodPwmZ;
    //<<=== ������, ��������� �� EEPROM �� � ��
    
    //===>> ������ ������ ��
    unsigned char _ssp;
    unsigned char _indAddr;
    unsigned char _groupAddr;
    unsigned short _temperature;
    unsigned short _dnu;
    unsigned short _voltageHi;
    unsigned short _widthPwm;
    unsigned short _periodPwm;
    unsigned short _scaling;
    //<<=== ������ ������ ��
    unsigned int ScalingSummator(unsigned short scaling);
    unsigned int _intervalQuantity; // ���������� ������������� � �������
    unsigned int _intervalCounter; // ������� �������������
    unsigned int _scalingCounter; // ������� ���������� �����

    bool _isScalingWork; // �������� �� ������ �������� ����� �� ������������ ������������� ��������
    bool _isExitScalingWork; // ������, �� ���������� ������� �������� �����

    int _timeLimitScaling; // �����, �������� �������������, ��� ������ �������� ���������� �����
    int _currTimeScaling; // ������� ����� ������ �������� �����
    unsigned int _scalingCounterTmp; // ��������� ���� �� �������
    double _scalingCounterSumm; // ��������� ���� �� ����� ������

    bool _bfClearScaling; // ���� ������� �� ����� �����

    //* KodRS = * KodRS & 0x10;/
    int _bfARCH; // ���� ��� (1 --- true, -1 --- false)

    int SspToFlagArch(unsigned char ssp); // 1 --- true, -1 --- false
};
//---------------------------------------------------------------------------
#endif
