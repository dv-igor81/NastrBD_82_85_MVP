//---------------------------------------------------------------------------
#pragma hdrstop
#include <stdio.h>
#include "PresenterWindowMainBd85.h"
#include "TextHelper.h"
#include "ConvertHelper.h"
#include "FileDirectExtensive.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma comment(lib, "TextBoxNumber.lib")
#pragma comment(lib, "SmartEventsMin.lib")
//---------------------------------------------------------------------------
PresenterWindowMainBd85::PresenterWindowMainBd85(
    IWindowMainBd85 * view,
    IFormDispetView * viewDispet,
    IAllProtokolS * allProtokol,
    TaskWithParam * task,
    IWindowLoader * loader) :
        _iniFileName( "BD85.dat" )
        , as_FormClose(this, &PresenterWindowMainBd85::FormClose)
        , as_OprosStart(this, &PresenterWindowMainBd85::OprosStart)
        , as_OprosStartInvoke(this, &PresenterWindowMainBd85::OprosStartInvoke)
        , as_OprosIter(this, &PresenterWindowMainBd85::OprosIter)
        , as_OprosIterInvoke(this, &PresenterWindowMainBd85::OprosIterInvoke)
        , as_OprosEnd(this, &PresenterWindowMainBd85::OprosEnd)
        , as_OprosEndInvoke(this, &PresenterWindowMainBd85::OprosEndInvoke)
        , as_SetConnectionState(this, &PresenterWindowMainBd85::SetConnectionState)
        //===>> ��������� ���������� ������� 03.12.2018
        , as_DisplayErrors(this, &PresenterWindowMainBd85::DisplayErrors)
        //<<===  ��������� ���������� ������� 03.12.2018
        , as_StartStopScaling(this, &PresenterWindowMainBd85::StartStopScaling)
        , as_ScalingOprosWorkInvoke(this, &PresenterWindowMainBd85::ScalingOprosWorkInvoke)
        , as_ClearScalingSumm(this, &PresenterWindowMainBd85::ClearScalingSumm)
        , as_WriteToEeprom(this, &PresenterWindowMainBd85::WriteToEeprom)
        , as_TextIndAddrZadChange(this, &PresenterWindowMainBd85::TextIndAddrZadChange)
        , as_TextGroupAdrZadChange(this, &PresenterWindowMainBd85::TextGroupAdrZadChange)
        , as_TextDnuZadCodeChange(this, &PresenterWindowMainBd85::TextDnuZadCodeChange)
        , as_TextDnuZadChange(this, &PresenterWindowMainBd85::TextDnuZadChange)
        , as_TextVoltageHiZadChange(this, &PresenterWindowMainBd85::TextVoltageHiZadChange)
        , as_TextWidthPwmZadChange(this, &PresenterWindowMainBd85::TextWidthPwmZadChange)
        , as_TextOffsetPwmZadChange(this, &PresenterWindowMainBd85::TextOffsetPwmZadChange)
        , as_TextPeriodPwmZadChange(this, &PresenterWindowMainBd85::TextPeriodPwmZadChange)
        , as_RadioButtonArchOnClick(this, &PresenterWindowMainBd85::RadioButtonArchOnClick)
        , as_RadioButtonArchOffClick(this, &PresenterWindowMainBd85::RadioButtonArchOffClick)
        , as_DisplayChangeEepromData(this, &PresenterWindowMainBd85::DisplayChangeEepromData)
        , as_FromFileBd85Settings(this, &PresenterWindowMainBd85::FromFileBd85Settings)
        , as_SaveToLogFile(this, &PresenterWindowMainBd85::SaveToLogFile)
        , as_Poisson(this, &PresenterWindowMainBd85::Poisson)
        , _omissionMax(100)
        //===
{
    _startData = 0;
    _iterData = 0;
    //===
    _isConnected = false; // �� ������������ � �� (����� ���-���� ���� �� TCP/IP)
    _isViewLoaded = true; // �������� ���� (���) ���������
    //===
    _view = view;
    _viewDispet = viewDispet;
    //===
    _allProtokol = allProtokol;
    _task = task;
    *_view->GetEventFormClose() += as_FormClose;
    *_view->GetEventButtonStartStopScalingClick() += as_StartStopScaling;
    
    _connectBdProt = new ConnectBdProt(
        _view->GetConnectFourBdProt(), _allProtokol, _task );

    *_connectBdProt->GetEventSetConnectionState() += as_SetConnectionState;
    ev_DisplayStartData += _view->GetSelfDisplayStartData();
    //===>> ��������� ���������� ������� 03.12.2018
    *_allProtokol->GetEventErrorCountIncrement() += as_DisplayErrors;
    //<<===  ��������� ���������� ������� 03.12.2018

    ev_DisplayIterData += _view->GetSelfDisplayIterData();
    ev_ScalingOpros += _view->GetSelfDisplayScalingData();
    _view->GetEventButtonClearScalingClick() += as_ClearScalingSumm;
    //===>> ������ � EEPROM
    _view->GetEventButtonWriteToEepromClick() += as_WriteToEeprom;
    _view->GetEventTextIndAddrZadChange() += as_TextIndAddrZadChange;
    _view->GetEventTextGroupAdrZadChange() += as_TextGroupAdrZadChange;
    _view->GetEventTextVoltageHiZadChange() += as_TextVoltageHiZadChange;
    _view->GetEventTextDnuZadCodeChange() += as_TextDnuZadCodeChange;
    _view->GetEventTextDnuZadChange() += as_TextDnuZadChange;
    _view->GetEventTextDnuZadChange() += as_TextDnuZadChange;
    _view->GetEventTextWidthPwmZadChange() += as_TextWidthPwmZadChange;
    _view->GetEventTextOffsetPwmZadChange() += as_TextOffsetPwmZadChange;
    _view->GetEventTextPeriodPwmZadChange() += as_TextPeriodPwmZadChange;
    _view->GetEventRadioButtonArchOnClick() += as_RadioButtonArchOnClick;
    _view->GetEventRadioButtonArchOffClick() += as_RadioButtonArchOffClick;
    ev_DisplayNotSaveChanges += _view->GetSelfDisplayNotSaveChanges();
    //<<=== ������ � EEPROM

    _mbParam = new ModBusParamBd85( allProtokol, view, task );

    _view->GetEventButtonFromFileClick() += as_FromFileBd85Settings;
    _view->GetEventButtonSaveToFileClick() += as_SaveToLogFile;

    _view->GetEventButtonPoissonClick() += as_Poisson;

    _view->SetVerPoText( _viewDispet->GetProgrammVersion() ); // ������ ��������� � ��������� �����
    _loader = loader;

    _view->WrapShow(); // �������� �����
}
//---------------------------------------------------------------------------
PresenterWindowMainBd85::~PresenterWindowMainBd85()
{
    delete _mbParam;
    _view->Destroy();
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::FormClose()
{
    _connectBdProt->Disconnect();
    _isViewLoaded = false;
    _viewDispet->WrapShow(); // �������� ����� ����������
}
//---------------------------------------------------------------------------
bool PresenterWindowMainBd85::IsViewLoaded()
{
    return _isViewLoaded;
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::ViewFilialClose() // ��������� �������� �����
{
    ConnectIsGood();
    _view->WrapShow();
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::ConnectIsGood() // ���������� (�� ��� ����� ��� TCP/IP) ������ ������
{
    _connectBdProt->SetActionOprosStart( & as_OprosStart );
    _connectBdProt->SetActionOprosIter( & as_OprosIter );
    _connectBdProt->SetActionOprosEnd( & as_OprosEnd );
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::DisplayErrors(const char * text)
{
    _task->BeginInvoke<const char*>(_view->GetSelfDisplayErrors(), text);
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::OprosStart()
{
    _startData = new StartDataNewBd85();
    OprosStartInvoke();
    _iterData = new IterDataNewBd85();
    OprosIterInvoke();

    while ( _isConnected )
    {
        if ( _allProtokol->InitMkInBd() ) // ������������� �� � �� (�������� ������ �����, ������ ������ = 8)
        {
            break;
        }
    }
    _readParamIndex = 0;
    while ( _isConnected )
    {
        if ( ReadEEProm() )
        {
            break; // ������� �������� �� ������ �� � ��
        }
    }
    _mbParam->ActionStart();
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::OprosStartInvoke()
{
    OprosStartNotInvoke( _startData );
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::OprosStartNotInvoke(StartDataNewBd85 *& data)
{
    _textChangeIgnore = true; // ������������ ��������� �� ���
    ev_DisplayStartData( data );
    _textChangeIgnore = false; // �� ������������ ��������� �� ���
    delete _startData; // ���������� ������
    _startData = 0;
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::OprosIter()
{
    Sleep(5);
    if ( _allProtokol->GetSsp( & _ssp ) == false )
    {
        return;
    }
    if ( (_ssp & 0x01) != 0x01 ) // ���� ���������� ����� �� �������
    {
        _omission++;
        if ( _omission > _omissionMax )
        {
            if ( _allProtokol->InitMkInBd() == false )
            {
                return;
            }
            else
            {
                _omission = 0;
            }
        }
        else
        {
            return;
        }
    }
    _omission = 0;
    if ( _allProtokol->GetScaling( & _scaling ) == false )
    {
        return;
    }    
    if ( _allProtokol->GetIndAdr( & _indAddr ) == false )
    {
        return;
    }
    if ( _allProtokol->GetGrpAdr( & _groupAddr ) == false )
    {
        return;
    }
    if ( _allProtokol->GetTemperature( & _temperature ) == false )
    {
        return;
    }
    if ( _allProtokol->GetDNU( & _dnu ) == false )
    {
        return;
    }
    if ( _allProtokol->GetVoltageHi( & _voltageHi ) == false )
    {
        return;
    }
    if ( _allProtokol->GetWidthPwm( & _widthPwm ) == false )
    {
        return;
    }
    if ( _allProtokol->GetPeriodPwm( & _periodPwm ) == false )
    {
        return;
    }

    if ( _flagWriteToEeprom ) // true - ��� ������ � EEPROM
    {
        _flagWriteToEeprom = false;
        bool flag = WriteEEProm();
        _readParamIndex = 0;
        flag &= ReadEEProm();
    }
    if ( _iterData != 0 ) // �������� ����� �� ����� ���������� ������
    {
        return;
    }
    _iterData = new IterDataNewBd85(
        _indAddr // �������������� �����
        , _groupAddr // ��������� �����
        , _temperature // ����������� �� (���)
        , _dnu
        , _voltageHi
        , _widthPwm
        , _periodPwm
        , ScalingSummator(_scaling)
    );
    _task->BeginInvoke( & as_OprosIterInvoke );
    //===>>
    _mbParam->ActionIfEventIter();
    //<<===
}
//---------------------------------------------------------------------------
unsigned int PresenterWindowMainBd85::ScalingSummator(unsigned short scaling)
{
    _intervalCounter++; // ������� �������������
    _scalingCounter += scaling; // _scalingCounter - ������� ���������� �����
    if ( _intervalCounter % _intervalQuantity == 0 ) // _intervalQuantity - ���������� ������������� � �������
    {
        _scalingCounterTmp = _scalingCounter;
        _scalingCounter = 0; // _scalingCounter - ������� ���������� �����
        _intervalCounter = 0; // ������� �������������

        if ( _isScalingWork )
        {
            ScalingOprosWork();
        }

        return _scalingCounterTmp; // ������� ��������� ����
    }
    return 0xFFFFFFFF; // ������� ����, ��� ���� �� �����
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::OprosIterInvoke()
{
    ev_DisplayIterData( _iterData );
    delete _iterData;
    _iterData = 0;
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::StartStopScaling(const char* timeMeteringLimit)
{
    if(_isScalingWork) // ���� ����� �����
    {
        _isExitScalingWork = true; // ������, �� ���������� ������� �������� �����
    }
    else
    {
        _isExitScalingWork = false;
        _timeLimitScaling = TextHelper::ConvertTextToNumber(
            timeMeteringLimit, // �����
            60); // 60 ������ �� ���������
        //_currTimeScaling = 0; // ������� ����� ������ �����
        //_scalingCounterSumm = 0; // ��������� ���� �� ����� ������
        _bfClearScaling = false;

        // ��������� ������ �����, ��������� ���� ����, �������� ����
        _scalingData = new ScalingDataNewBd85( _timeLimitScaling );
        ev_ScalingOpros( _scalingData );
        delete _scalingData;
        _scalingData = 0;
        if ( _timeLimitScaling > 0 )
        {
            _isScalingWork = true;
        }
    }
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::ScalingOprosWork()
{
    int stubExit = _timeLimitScaling;
    if (_bfClearScaling)
    {
        _bfClearScaling = false;
        _currTimeScaling = 0;
        _scalingCounterSumm = 0;
    }
    if ( _isExitScalingWork ) // ��������� ������ �������� �����
    {
        _isScalingWork = false;
    }
    else
    { // ����������� ������� ����
        _currTimeScaling++;
        _scalingCounterSumm += _scalingCounterTmp;
        if ( _currTimeScaling >= _timeLimitScaling )
        {
            _isScalingWork = false; // ��������� ������ �������� �����
        }
    }
    if ( _isScalingWork == false )
    {
        stubExit = -1; // ��������� ���������� ������� �������� �����
    }

    if ( _scalingData != 0 ) // �������� ����� �� ����� ���������� ������
    {
        return;
    }

    _scalingData = new ScalingDataNewBd85(
        stubExit
        , _currTimeScaling // ������� ����� ������ �����
        , _scalingCounterSumm // ��������� ����
    );

    _task->BeginInvoke( & as_ScalingOprosWorkInvoke );
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::ScalingOprosWorkInvoke()
{
    ev_ScalingOpros( _scalingData );
    delete _scalingData;
    _scalingData = 0;
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::ClearScalingSumm()
{
    if( _isScalingWork ) // ���� ����� �����
    {
        _bfClearScaling = true;
    }
    else
    {
        _currTimeScaling = 0; // ������� ����� ������ �����
        _scalingCounterSumm = 0; // ��������� ���� �� ����� ������
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::OprosEnd()
{
    Sleep(10);
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::OprosEndInvoke()
{
}
//---------------------------------------------------------------------------
/*bool PresenterWindowMainBd85::InitMkInBd()
{
    unsigned char timeInterval = 0;
    const unsigned char defaultTimeInterval = 8;
    if ( _allProtokol->GetTimeInterval( & timeInterval ) == false )
    {
        return false;
    }
    if ( timeInterval != defaultTimeInterval )
    {
        if ( _allProtokol->SetTimeInterval( defaultTimeInterval ) == false )
        {
            return false;
        }
        if ( _allProtokol->GetTimeInterval( & timeInterval ) == false )
        {
            return false;
        }
        if ( timeInterval != defaultTimeInterval )
        {
            return false;
        }
    }
    _omission = 0;
    return true;
} */
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::SetConnectionState( ConnectionStateInfo state )
{
    switch (state)
    {
    case ConnectionStateInfo_t::WaitConnect:
        break;
    case ConnectionStateInfo_t::IsConnected:
        ConnectIsGood();
        _isConnected = true;
        switch ( _allProtokol->GetProtokolName() )
        {
        case ProtokolName_t::NineBit: // 9-�� ������
            _intervalQuantity = 5; // ���������� ������������� � �������
            break;
        case ProtokolName_t::ModBus_RTU: // ModBus RTU
        case ProtokolName_t::ModBus_TCP: // ModBus TCP
        case ProtokolName_t::ModBus_RTU_IP: // ModBus RTU (TCP/IP)
            _intervalQuantity = 4; // ���������� ������������� � �������
            break;
        }
        _intervalCounter = 0; // ������� �������������
        _scalingCounter = 0; // ������� ���������� �����
        _isScalingWork = false; // �� �������� ����� ����� �� ������������ ������������� ��������
        _bfEepromFirstCopy = true; // ������ ����������� ����������
        _flagWriteToEeprom = false; // true - ��� ������ � EEPROM
        break;
    case ConnectionStateInfo_t::WaitLoopExit:
        _isConnected = false;
        _isExitScalingWork = true; // ������, �� ���������� ������� �������� �����
        ScalingOprosWork(); // ���������� ���������� ���������� ������� �������� �����
        break;
    case ConnectionStateInfo_t::IsDisconnect:
        break;
    }
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::FirstCopyEEprom()
{
    if ( _bfEepromFirstCopy == false )
    {
        return;
    }
    _eepromChange.Copy( _eepromSaved );
    _eepromPrev.Copy(_eepromChange);
}
//---------------------------------------------------------------------------
bool PresenterWindowMainBd85::ReadEEProm()
{
    if ( _readParamIndex == 0 )
    {
        if ( _allProtokol->GetVersia( _eepromSaved.VerPo ) == false )
        {
            return false;
        }
        _readParamIndex++;
    }
    if ( _isConnected == false )
    {
        return false; // ������� ����� �� ������� ReadEEProm()
    }
    if ( _readParamIndex == 1 )
    {
        if(_eepromSaved.VerPo[0] == '6') // ver = 6.xx
        {
            if ( _allProtokol->GetIndAdrZ/*_Bd85*/( & _eepromSaved.IndAddrZad ) == false )
            {
                return false;
            }
        }
        else
        {
            if ( _allProtokol->GetIndAdrZ( & _eepromSaved.IndAddrZad ) == false )
            {
                return false;
            }
        }
        _readParamIndex++;
    }
    if ( _isConnected == false )
    {
        return false; // ������� ����� �� ������� ReadEEProm()
    }    
    if ( _readParamIndex == 2 )
    {
        if ( _allProtokol->GetGroupAdrZ( & _eepromSaved.GroupAddrZad ) == false )
        {
            return false;
        }
        _readParamIndex++;
    }
    if ( _isConnected == false )
    {
        return false; // ������� ����� �� ������� ReadEEProm()
    }
    if ( _readParamIndex == 3 )
    {
        if ( _allProtokol->GetDnuZ( & _eepromSaved.DnuZad ) == false )
        {
            return false;
        }
        _readParamIndex++;
    }
    if ( _isConnected == false )
    {
        return false; // ������� ����� �� ������� ReadEEProm()
    }
    if ( _readParamIndex == 4 )
    {
        if ( _allProtokol->GetVoltageHiZ_Bd85( & _eepromSaved.VoltageHiZad ) == false )
        {
            return false;
        }
        _eepromSaved.VoltageHiZadValue = TextHelper::Rounding(
            ConvertHelper::VoltageHiCodeToValue( _eepromSaved.VoltageHiZad ),
            2 ); // ��������� 2 ����� ����� �������
        _readParamIndex++;
    }
    if ( _isConnected == false )
    {
        return false; // ������� ����� �� ������� ReadEEProm()
    }
    if ( _readParamIndex == 5 )
    {
        if ( _allProtokol->GetWidthPwmZ_Bd85( & _eepromSaved.WidthPwmZad ) == false )
        {
            return false;
        }
        _readParamIndex++;
    }
    if ( _isConnected == false )
    {
        return false; // ������� ����� �� ������� ReadEEProm()
    }
    if ( _readParamIndex == 6 )
    {
        if ( _allProtokol->GetOffsetPwmZ_Bd85( & _eepromSaved.OffsetPwmZad ) == false )
        {
            return false;
        }
        _readParamIndex++;
    }
    if ( _isConnected == false )
    {
        return false; // ������� ����� �� ������� ReadEEProm()
    }
    if ( _readParamIndex == 7 )
    {
        if ( _allProtokol->GetPeriodPwmZ_Bd85( & _eepromSaved.PeriodPwmZad ) == false )
        {
            return false;
        }
        _readParamIndex++;
    }
    if ( _isConnected == false )
    {
        return false; // ������� ����� �� ������� ReadEEProm()
    }
    if ( _readParamIndex == 8 )
    {
        if ( _allProtokol->GetSsp( & _ssp ) == false )
        {
            return false;
        }
        _eepromSaved.FlagArch = SspToFlagArch( _ssp );
        _readParamIndex++;
    }
    if ( _isConnected == false )
    {
        return false; // ������� ����� �� ������� ReadEEProm()
    }
    if ( _startData != 0 )
    {
        return false; // �������� ����� �� ����� ���������� ������
    }
    FirstCopyEEprom();
    _bfChangeEepromCurr = ChangeEepromData();
    _bfChangeEepromOld = !_bfChangeEepromCurr; // ������� ������� � ���� �����������
    WrapDisplayChangeEepromDataInvoke( true );

    _startData = new StartDataNewBd85( & _eepromSaved );
    _task->BeginInvoke( & as_OprosStartInvoke );
    return true;
}
//---------------------------------------------------------------------------
int PresenterWindowMainBd85::SspToFlagArch(unsigned char ssp)
{
    if ( (ssp & 0x10) != 0 )
    {
        return 1;
    }
    return -1;
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::WriteToEeprom()
{
    _flagWriteToEeprom = true;
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::ToNumber(
    const char * text,
    unsigned char * change,
    unsigned char * prev,
    int max)
{
    bool update;
    int changeArg;
    int prevArg = *prev;
    TextHelper::ConvertTextToNumber( text,
        & changeArg, // [OUT] ��������� �������� ���������
        & prevArg, // [IN/OUT] ���������� �������� ���������
        & update,
        0, max );
    *change = ( changeArg & 0xFF );
    *prev = ( prevArg & 0xFF );
    DisplayChangeEepromData( update );
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::ToNumber(
    const char * text,
    unsigned short * change,
    unsigned short * prev,
    int max)
{
    bool update;
    int changeArg;
    int prevArg = *prev;
    TextHelper::ConvertTextToNumber( text,
        & changeArg, // [OUT] ��������� �������� ���������
        & prevArg, // [IN/OUT] ���������� �������� ���������
        & update, // [OUT] true - �������� ��������� ����
        0, max );
    *change = ( changeArg & 0xFFFF );
    *prev = ( prevArg & 0xFFFF );
    DisplayChangeEepromData( update );
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::ToNumber(
    unsigned short * change, // [IN/OUT]
    unsigned short * prev, // [IN/OUT]
    bool update,
    int max)
{
    int changeArg = *change;
    int prevArg = *prev;
    TextHelper::CheckNumber(
        & changeArg, // [IN/OUT] ��������� �������� ���������
        & prevArg, // [IN/OUT] ���������� �������� ���������
        & update, // [IN/OUT]
        0, max);
    *change = ( changeArg & 0xFFFF );
    *prev = ( prevArg & 0xFFFF );
    DisplayChangeEepromData( update );
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::TextIndAddrZadChange(const char* text)
{
    ToNumber( text, & _eepromChange.IndAddrZad, & _eepromPrev.IndAddrZad, 247 );
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::TextGroupAdrZadChange(const char* text)
{
    ToNumber( text, & _eepromChange.GroupAddrZad, & _eepromPrev.GroupAddrZad, 247 );
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::TextDnuZadCodeChange(int code)
{
    AnsiString text = IntToStr(code);
    ToNumber( text.c_str(), & _eepromChange.DnuZad, & _eepromPrev.DnuZad, 4095 );
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::TextDnuZadChange(const char* text)
{
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::TextVoltageHiZadChange(int code)
{
    AnsiString text = IntToStr(code);
    ToNumber( text.c_str(), & _eepromChange.VoltageHiZad, & _eepromPrev.VoltageHiZad, 4095 );
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::TextWidthPwmZadChange(const char* text)
{
    ToNumber( text, & _eepromChange.WidthPwmZad, & _eepromPrev.WidthPwmZad, 4095 );
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::TextOffsetPwmZadChange(const char* text)
{
    ToNumber( text, & _eepromChange.OffsetPwmZad, & _eepromPrev.OffsetPwmZad, 4095 );
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::TextPeriodPwmZadChange(const char* text)
{
    ToNumber( text, & _eepromChange.PeriodPwmZad, & _eepromPrev.PeriodPwmZad, 4095 );
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::RadioButtonArchOnClick(bool onClick)
{
    if ( onClick )
    {
        _eepromChange.FlagArch = -1; // -1 --- false, 1 --- true, 0 --- null
        DisplayChangeEepromData( false );
    }
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::RadioButtonArchOffClick(bool offClick)
{
    if ( offClick )
    {
        _eepromChange.FlagArch = 1; // -1 --- false, 1 --- true, 0 --- null
        DisplayChangeEepromData( false );
    }
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::WrapDisplayChangeEepromDataInvoke(bool updateText)
{
    _task->BeginInvoke( & as_DisplayChangeEepromData, updateText );
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::DisplayChangeEepromData( bool updataText )
{
    if ( _textChangeIgnore )
    { // ��� ��������� ������� ����������, � �� ������������� (����� ���)
      // ������� ���������� ��� �������
        return;
    }
    _bfChangeEepromCurr = ChangeEepromData(); // ���� �� ��������� ����-�� ������ ���������?
    if ( _bfChangeEepromOld != _bfChangeEepromCurr )
    {
        _bfChangeEepromOld = _bfChangeEepromCurr;
        ev_DisplayNotSaveChanges( _bfChangeEepromCurr );
    }
    if ( updataText )
    {
        StartDataNewBd85 * data = new StartDataNewBd85( & _eepromChange );
        OprosStartNotInvoke( data );
    }
}
//---------------------------------------------------------------------------
bool PresenterWindowMainBd85::ChangeEepromData()
{ // ���� ���� ��������� ����-�� ������ ��������� - ��������� ����
    return _eepromChange.NotEqual( _eepromSaved );
}
//---------------------------------------------------------------------------
bool PresenterWindowMainBd85::WriteEEProm()
{ // ���� ���� ������ ���� �� � ����� ���������� - ������ ���� �� ���� �������
    bool flag = true;
    if ( _eepromSaved.IndAddrZad != _eepromChange.IndAddrZad )
    {
        flag &= _allProtokol->SetIndAdrZ( _eepromChange.IndAddrZad );
    }
    if ( _eepromSaved.GroupAddrZad != _eepromChange.GroupAddrZad )
    {
        flag &= _allProtokol->SetGroupAdrZ( _eepromChange.GroupAddrZad );
    }
    if ( _eepromSaved.DnuZad != _eepromChange.DnuZad )
    {
        flag &= _allProtokol->SetDnuZ( _eepromChange.DnuZad );
    }
    if ( _eepromSaved.VoltageHiZad != _eepromChange.VoltageHiZad )
    {
        flag &= _allProtokol->SetVoltageHiZ_Bd85( _eepromChange.VoltageHiZad );
    }
    if ( _eepromSaved.WidthPwmZad != _eepromChange.WidthPwmZad )
    {
        flag &= _allProtokol->SetWidthPwmZ_Bd85( _eepromChange.WidthPwmZad );
    }
    if ( _eepromSaved.OffsetPwmZad != _eepromChange.OffsetPwmZad )
    {
        flag &= _allProtokol->SetOffsetPwmZ_Bd85( _eepromChange.OffsetPwmZad );
    }
    if ( _eepromSaved.PeriodPwmZad != _eepromChange.PeriodPwmZad )
    {
        flag &= _allProtokol->SetPeriodPwmZ_Bd85( _eepromChange.PeriodPwmZad );
    }
    if ( _eepromSaved.FlagArch != _eepromChange.FlagArch )
    {
        unsigned char archChange;
        if ( _eepromChange.FlagArch == -1 )
        {
            archChange = 0;
        }
        else
        {
            archChange = 1;
        }
        flag &= _allProtokol->SetArch( archChange );
    }
    return flag;
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::FromFileBd85Settings()
{
    FileDirectExtensive fromIni;
    bool flagArch;
    unsigned short voltageHiZadValue;
    unsigned short voltageHiZad;
    bool bfError = false;

    fromIni.LoadFromFile( _iniFileName.c_str() );
    const unsigned char Addr = 0;
    const unsigned char AddrG = 0;
    const unsigned short DNU = 950;
    const unsigned short UHI = 1230;
    const unsigned short PwmPulseLength = 40;
    const unsigned short PwmOffset = 525;
    const unsigned short PwmCycleTime = 2500;
    const bool Feedback = false;

    fromIni.ReadByte( & _eepromChange.IndAddrZad, "Addr", 0, Addr, 255, & bfError ); // "Addr" - ������������� �� ������� ��������
    fromIni.ReadByte( & _eepromChange.GroupAddrZad, "AddrG", 0, AddrG, 255, & bfError ); // "AddrG" - ������������� �� ������� ��������
    fromIni.ReadWord( & _eepromChange.DnuZad, "DNU", 0, DNU, 0xFFFF, & bfError ); // "DNU" - ������������� �� ������� ��������
    fromIni.ReadWord( & voltageHiZadValue, "UHI", 0, UHI, 0xFFFF, & bfError ); // "UHI" - ������������� �� ������� ��������
    _eepromChange.VoltageHiZad = ConvertHelper::VoltageHiValueToCode( voltageHiZadValue );
    fromIni.ReadWord( & _eepromChange.WidthPwmZad, "PwmPulseLength", 0, PwmPulseLength, 0xFFFF, & bfError ); // "PwmPulseLength" - ������������� �� ������� ��������
    fromIni.ReadWord( & _eepromChange.OffsetPwmZad, "PwmOffset", 0, 525, 0xFFFF, & bfError ); // "PwmOffset" - ������������� �� ������� ��������
    fromIni.ReadWord( & _eepromChange.PeriodPwmZad, "PwmCycleTime", 0, 2500, 0xFFFF, & bfError ); // "PwmCycleTime" - ������������� �� ������� ��������
    fromIni.ReadBool( & flagArch, "Feedback", Feedback, & bfError ); // "Feedback" - ������������� �� ������� ��������
    flagArch ^= 1;
    if ( flagArch )
    {
        _eepromChange.FlagArch = 1; // -1 --- false, 1 --- true, 0 --- null
    }
    else
    {
        _eepromChange.FlagArch = -1; // -1 --- false, 1 --- true, 0 --- null
    }
    _eepromPrev.Copy( _eepromChange );
    DisplayChangeEepromData( true );

    if ( fromIni.DiaFileExists() == false || bfError == true )
    { // ���� �� ������, ���� ���� �� ���������� �� ��������
        fromIni.WriteInteger( Addr, "Addr" ); // "Addr" - ������������� �� ������� ��������
        fromIni.WriteInteger( AddrG, "AddrG" ); // "AddrG" - ������������� �� ������� ��������
        fromIni.WriteInteger( DNU, "DNU" ); // "DNU" - ������������� �� ������� ��������
        fromIni.WriteInteger( UHI, "UHI" ); // "UHI" - ������������� �� ������� ��������
        fromIni.WriteInteger( PwmPulseLength, "PwmPulseLength" ); // "PwmPulseLength" - ������������� �� ������� ��������
        fromIni.WriteInteger( PwmOffset, "PwmOffset" ); // "PwmOffset" - ������������� �� ������� ��������
        fromIni.WriteInteger( PwmCycleTime, "PwmCycleTime" ); // "PwmCycleTime" - ������������� �� ������� ��������
        fromIni.WriteInteger( Feedback, "Feedback" ); //  "Feedback" - ������������� �� ������� ��������
        fromIni.SaveToFile( _iniFileName.c_str() );
    }
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::HideSelf()
{
    _view->WrapHide(); // ������ ����
    _connectBdProt->SetActionOprosStart( 0 );
    _connectBdProt->SetActionOprosIter( 0 );
    _connectBdProt->SetActionOprosEnd( 0 );
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::SaveToLogFile()
{
    HideSelf();
    _loader->LoadWindowBd85SaveParam( this, _connectBdProt ); // ��������� ����� ���� "Bd85SaveParam"
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::Poisson()
{
    HideSelf();
    _loader->LoadWindowBd85Poisson( this, _connectBdProt ); // ��������� ����� ���� "Bd85Poisson"
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

