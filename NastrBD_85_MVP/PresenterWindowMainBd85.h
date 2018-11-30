//---------------------------------------------------------------------------
#ifndef PresenterWindowMainBd85H
#define PresenterWindowMainBd85H
//---------------------------------------------------------------------------
#include "IWindowMainBd85.h"
#include "IFormDispetView.h"
#include "ConnectBdProt.h"
#include "IAllProtokolS.h"
#include "ITask.h"
#include "TaskWithParam.h"
#include "ModBusParamBd85.h"
#include "EepromBd85Settings.h"
#include "IWindowLoader.h"
//---------------------------------------------------------------------------
class PresenterWindowMainBd85
{
public:
    PresenterWindowMainBd85(
        IWindowMainBd85 * view,
        IFormDispetView * viewDispet,
        IAllProtokolS * allProtokol,
        TaskWithParam * task,
        IWindowLoader * loader);
    ~PresenterWindowMainBd85();
    bool IsViewLoaded();
private:
    IWindowMainBd85 * _view;
    IFormDispetView * _viewDispet;
    ConnectBdProt* _connectBdProt;
    IAllProtokolS * _allProtokol;
    TaskWithParam * _task;
    IWindowLoader * _loader;

    ActionSelf<> as_FormClose;
    void FormClose();

    void ConnectIsGood(); // ���������� (�� ��� ����� ��� TCP/IP) ������ ������

    ActionSelf<> as_OprosStart;
    void OprosStart();

    ActionSelf<> as_OprosStartInvoke;
    void OprosStartInvoke();
    void OprosStartNotInvoke(StartDataNewBd85 *& data);

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

    ActionSelf<> as_FromFileBd85Settings;
    void FromFileBd85Settings();

    ActionSelf<> as_SaveToLogFile;
    void SaveToLogFile();

    bool _isViewLoaded;

    ActionEvent<StartDataNewBd85*> ev_DisplayStartData;
    StartDataNewBd85* _startData;


    ActionEvent<IterDataNewBd85*> ev_DisplayIterData;
    IterDataNewBd85* _iterData;

    ActionEvent<ScalingDataNewBd85*> ev_ScalingOpros;
    ScalingDataNewBd85* _scalingData;

    ActionEvent<bool> ev_DisplayNotSaveChanges;

    bool InitMkInBd();
    bool _isConnected;
    bool ReadEEProm();

    int _readParamIndex;
    enum { verPoSize = 5 };
    //===>> ������, ��������� �� EEPROM �� � ��
    EepromBd85Settings _eepromSaved; // ���������� � EEPROM ���������
    EepromBd85Settings _eepromChange; // ������� ��������� ���������
    EepromBd85Settings _eepromPrev; // ���������� ��������� ���������

    void WrapDisplayChangeEepromDataInvoke( bool updateText );
    ActionSelf<bool> as_DisplayChangeEepromData;
    void DisplayChangeEepromData( bool updateText );


    bool _textChangeIgnore;
    bool ChangeEepromData(); // true - ��������� ������� � ���, �� �� �������� � EEPROM
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

    void ToNumber(
        const char * text,
        unsigned char * change,
        unsigned char * prev,
        int max);

    void ToNumber(
        const char * text,
        unsigned short * change,
        unsigned short * prev,
        int max);

    void ToNumber(
        unsigned short * change, // [IN/OUT]
        unsigned short * prev,
        bool update, // true �������� ��������� ����
        int max);

    ModBusParamBd85 * _mbParam;
    const AnsiString _iniFileName;
};
//---------------------------------------------------------------------------
#endif
