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

    ActionSelf<> as_OprosStart;
    void OprosStart();

    ActionSelf<> as_OprosStartInvoke;
    void OprosStartInvoke();

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

    //===>> ������ � EEPROM

    ActionSelf<> as_WriteToEeprom;
    void WriteToEeprom();

    ActionSelf<const char*> as_TextIndAddrZadChange;
    void TextIndAddrZadChange(const char* text);

    ActionSelf<const char*> as_TextGroupAdrZadChange;
    void TextGroupAdrZadChange(const char* text);

    ActionSelf<const char*> as_TextDnuZadCodeChange;
    void TextDnuZadCodeChange(const char* text);

    ActionSelf<const char*> as_TextVoltageHiZadChange;
    void TextVoltageHiZadChange(const char* text);

    ActionSelf<const char*> as_TextWidthPwmZadChange;
    void TextWidthPwmZadChange(const char* text);

    ActionSelf<const char*> as_TextOffsetPwmZadChange;
    void TextOffsetPwmZadChange(const char* text);

    ActionSelf<const char*> as_TextPeriodPwmZadChange;
    void TextPeriodPwmZadChange(const char* text);

    ActionSelf<bool> as_RadioButtonArchOnClick;
    void RadioButtonArchOnClick(bool onClick);

    ActionSelf<bool> as_RadioButtonArchOffClick;
    void RadioButtonArchOffClick(bool offClick);

    //<<=== ������ � EEPROM

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
    ActionEvent<bool> ev_DisplayNotSaveChanges;

    bool InitMkInBd();
    bool _isConnected;
    bool ReadEEProm();

    int _readParamIndex;
    enum { verPoSize = 5 };
    //===>> ������, ��������� �� EEPROM �� � ��
    char _verPo[5];
    unsigned char _indAddrZad;
    unsigned char _groupAddrZad;
    unsigned short _dnuZad;
    unsigned short _voltageHiZad;
    unsigned short _widthPwmZad;
    unsigned short _offsetPwmZad;
    unsigned short _periodPwmZad;
    int _bfArch; // ���� ��� (1 --- true, -1 --- false)
    //===
    int _indAddrZadChange;
    int _groupAddrZadChange;
    int _dnuZadChange;
    int _voltageHiZadChange;
    int _widthPwmZadChange;
    int _offsetPwmZadChange;
    int _periodPwmZadChange;
    int _bfArchChange; // ���� ��� (1 --- true, -1 --- false)


    void DisplayChangeEepromDataInvoke();

    ActionSelf<> as_DisplayChangeEepromData;
    void DisplayChangeEepromData();
    //bool _isTextChange;
    bool _textChangeIgnore;

    bool ChangeEepromData(); // true - ��������� ������� � ���, �� �� �������� � EEPROM
    bool NotEqual(int var1, int var2);
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
    int SspToFlagArch(unsigned char ssp); // 1 --- true, -1 --- false

    bool _bfChangeEepromCurr;
    bool _bfChangeEepromOld;
    bool WriteEEProm();
    void FirstCopyEEprom();
    bool _bfEepromFirstCopy;
    bool _flagWriteToEeprom; // true - ��� ������ � EEPROM
};
//---------------------------------------------------------------------------
#endif
