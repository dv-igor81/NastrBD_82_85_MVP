//---------------------------------------------------------------------------
#pragma hdrstop
#include <stdio.h>
#include "PresenterWindowMainBd85.h"
#include "TextHelper.h"
#include "ConvertHelper.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
PresenterWindowMainBd85::PresenterWindowMainBd85(
    IWindowMainBd85 * view,
    IFormDispetView * viewDispet,
    IAllProtokolS * allProtokol,
    ITask * task) :
        as_FormClose(this, &PresenterWindowMainBd85::FormClose)
        , as_OprosStart(this, &PresenterWindowMainBd85::OprosStart)
        , as_OprosStartInvoke(this, &PresenterWindowMainBd85::OprosStartInvoke)
        , as_OprosIter(this, &PresenterWindowMainBd85::OprosIter)
        , as_OprosIterInvoke(this, &PresenterWindowMainBd85::OprosIterInvoke)
        , as_OprosEnd(this, &PresenterWindowMainBd85::OprosEnd)
        , as_OprosEndInvoke(this, &PresenterWindowMainBd85::OprosEndInvoke)
        , as_SetConnectionState(this, &PresenterWindowMainBd85::SetConnectionState)
        , as_StartStopScaling(this, &PresenterWindowMainBd85::StartStopScaling)
        , as_ScalingOprosWorkInvoke(this, &PresenterWindowMainBd85::ScalingOprosWorkInvoke)
        , as_ClearScalingSumm(this, &PresenterWindowMainBd85::ClearScalingSumm)
        , as_WriteToEeprom(this, &PresenterWindowMainBd85::WriteToEeprom)
        , as_TextIndAddrZadChange(this, &PresenterWindowMainBd85::TextIndAddrZadChange)
        , as_TextGroupAdrZadChange(this, &PresenterWindowMainBd85::TextGroupAdrZadChange)
        , as_TextDnuZadCodeChange(this, &PresenterWindowMainBd85::TextDnuZadCodeChange)
        , as_TextVoltageHiZadChange(this, &PresenterWindowMainBd85::TextVoltageHiZadChange)
        , as_TextWidthPwmZadChange(this, &PresenterWindowMainBd85::TextWidthPwmZadChange)
        , as_TextOffsetPwmZadChange(this, &PresenterWindowMainBd85::TextOffsetPwmZadChange)
        , as_TextPeriodPwmZadChange(this, &PresenterWindowMainBd85::TextPeriodPwmZadChange)
        , as_RadioButtonArchOnClick(this, &PresenterWindowMainBd85::RadioButtonArchOnClick)
        , as_RadioButtonArchOffClick(this, &PresenterWindowMainBd85::RadioButtonArchOffClick)
        , as_DisplayChangeEepromData(this, &PresenterWindowMainBd85::DisplayChangeEepromData)
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
    ev_Show += _view->GetSelfShow();
    *_view->GetEventFormClose() += as_FormClose;
    *_view->GetEventButtonStartStopScalingClick() += as_StartStopScaling;
    
    _connectBdProt = new ConnectBdProt(
        _view->GetConnectFourBdProt(), _allProtokol, _task );

    *_connectBdProt->GetEventSetConnectionState() += as_SetConnectionState;
    ev_DisplayStartData += _view->GetSelfDisplayStartData();
    *_allProtokol->GetEventErrorCountIncrement() += _view->GetSelfDisplayErrors();
    ev_DisplayIterData += _view->GetSelfDisplayIterData();
    ev_ScalingOpros += _view->GetSelfDisplayScalingData();
    _view->GetEventButtonClearScalingClick() += as_ClearScalingSumm;

    //===>> ������ � EEPROM
    _view->GetEventButtonWriteToEepromClick() += as_WriteToEeprom;
    _view->GetEventTextIndAddrZadChange() += as_TextIndAddrZadChange;
    _view->GetEventTextGroupAdrZadChange() += as_TextGroupAdrZadChange;
    _view->GetEventTextVoltageHiZadChange() += as_TextVoltageHiZadChange;
    _view->GetEventTextDnuZadCodeChange() += as_TextDnuZadCodeChange;
    _view->GetEventTextWidthPwmZadChange() += as_TextWidthPwmZadChange;
    _view->GetEventTextOffsetPwmZadChange() += as_TextOffsetPwmZadChange;
    _view->GetEventTextPeriodPwmZadChange() += as_TextPeriodPwmZadChange;
    _view->GetEventRadioButtonArchOnClick() += as_RadioButtonArchOnClick;
    _view->GetEventRadioButtonArchOffClick() += as_RadioButtonArchOffClick;
    ev_DisplayNotSaveChanges += _view->GetSelfDisplayNotSaveChanges();
    //<<=== ������ � EEPROM

    _mbParam = new ModBusParamBd85( allProtokol, _view->GetModBusEventContainer(), task );

    _view->SetVerPoText( _viewDispet->GetProgrammVersion() ); // ������ ��������� � ��������� �����
    ev_Show(); // �������� �����
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
void PresenterWindowMainBd85::ConnectIsGood() // ���������� (�� ��� ����� ��� TCP/IP) ������ ������
{
    _connectBdProt->SetActionOprosStart( & as_OprosStart );
    _connectBdProt->SetActionOprosIter( & as_OprosIter );
    _connectBdProt->SetActionOprosEnd( & as_OprosEnd );
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
        if ( InitMkInBd() ) // ������������� �� � �� (�������� ������ �����, ������ ������ = 8)
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
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::OprosStartInvoke()
{
    _textChangeIgnore = true; // ������������ ��������� �� ���
    ev_DisplayStartData( _startData );
    _textChangeIgnore = false; // �� ������������ ��������� �� ���
    delete _startData; // ���������� ������
    _startData = 0;
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::OprosIter()
{
    Sleep(10);
    if ( _allProtokol->GetSsp( & _ssp ) == false )
    {
        return;
    }
    _bfArch = SspToFlagArch( _ssp );
    if ( (_ssp & 0x01) != 0x01 ) // ���� ���������� ����� �� �������
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
    if ( _allProtokol->GetScaling( & _scaling ) == false )
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

    _mbParam->ActionIfEvent();

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
        _currTimeScaling = 0; // ������� ����� ������ �����
        _scalingCounterSumm = 0; // ��������� ���� �� ����� ������
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
    _bfClearScaling = true;
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
bool PresenterWindowMainBd85::InitMkInBd()
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
    return true;
}
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
    _indAddrZadChange = _indAddrZad;
    _groupAddrZadChange = _groupAddrZad;
    _dnuZadChange = _dnuZad;
    _voltageHiZadChange = _voltageHiZad;
    _widthPwmZadChange = _widthPwmZad;
    _offsetPwmZadChange = _offsetPwmZad;
    _periodPwmZadChange = _periodPwmZad;
    _bfArchChange = _bfArch;
    _bfEepromFirstCopy = false;    
}
//---------------------------------------------------------------------------
bool PresenterWindowMainBd85::ReadEEProm()
{
    if ( _readParamIndex == 0 )
    {
        if ( _allProtokol->GetVersia( _verPo ) == false )
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
        if ( _allProtokol->GetIndAdrZ( & _indAddrZad ) == false )
        {
            return false;
        }
        _readParamIndex++;
    }
    if ( _isConnected == false )
    {
        return false; // ������� ����� �� ������� ReadEEProm()
    }    
    if ( _readParamIndex == 2 )
    {
        if ( _allProtokol->GetGroupAdrZ( & _groupAddrZad ) == false )
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
        if ( _allProtokol->GetDnuZ( & _dnuZad ) == false )
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
        if ( _allProtokol->GetVoltageHiZ_Bd85( & _voltageHiZad ) == false )
        {
            return false;
        }
        _readParamIndex++;
    }
    if ( _isConnected == false )
    {
        return false; // ������� ����� �� ������� ReadEEProm()
    }
    if ( _readParamIndex == 5 )
    {
        if ( _allProtokol->GetWidthPwmZ_Bd85( & _widthPwmZad ) == false )
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
        if ( _allProtokol->GetOffsetPwmZ_Bd85( & _offsetPwmZad ) == false )
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
        if ( _allProtokol->GetPeriodPwmZ_Bd85( & _periodPwmZad ) == false )
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
        _bfArch = SspToFlagArch( _ssp );
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
    DisplayChangeEepromDataInvoke();

    _startData = new StartDataNewBd85(
        _verPo // ������ ��������
        , _indAddrZad // �������������� ����� ��������
        , _groupAddrZad // ��������� ����� ��������
        , _dnuZad // ��� �������� ���
        , _voltageHiZad // ���������� ������� �������� ���
        , _widthPwmZad // ������������ ��� ��������
        , _offsetPwmZad //  �������� ��� ��������
        , _periodPwmZad // ������ ��� ��������
        , _bfArch // ���� ��� 
        );
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
void PresenterWindowMainBd85::TextIndAddrZadChange(const char* text)
{
    _indAddrZadChange = TextHelper::ConvertTextToNumber(
        text, _indAddrZad, 0, 247);
    DisplayChangeEepromData();
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::TextGroupAdrZadChange(const char* text)
{
    _groupAddrZadChange = TextHelper::ConvertTextToNumber(
        text, _groupAddrZad, 0, 247);
    DisplayChangeEepromData();
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::TextDnuZadCodeChange(const char* text)
{
    _dnuZadChange = TextHelper::ConvertTextToNumber(
        text, _dnuZad, 0, 4095);
    DisplayChangeEepromData();
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::TextVoltageHiZadChange(const char* text)
{
    double voltageHiZadChangeValue = TextHelper::ConvertTextToDouble(
        text,
        ConvertHelper::VoltageHiCodeToValue( _voltageHiZad ));
    _voltageHiZadChange = ConvertHelper::VoltageHiValueToCode( voltageHiZadChangeValue );
    DisplayChangeEepromData();
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::TextWidthPwmZadChange(const char* text)
{
    _widthPwmZadChange = TextHelper::ConvertTextToNumber(
        text, _widthPwmZad, 0, 4095);
    DisplayChangeEepromData();
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::TextOffsetPwmZadChange(const char* text)
{
    _offsetPwmZadChange = TextHelper::ConvertTextToNumber(
        text, _offsetPwmZad, 0, 4095);
    DisplayChangeEepromData();
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::TextPeriodPwmZadChange(const char* text)
{
    _periodPwmZadChange = TextHelper::ConvertTextToNumber(
        text, _periodPwmZad, 0, 4095);
    DisplayChangeEepromData();
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::RadioButtonArchOnClick(bool onClick)
{
    if ( onClick )
    {
        _bfArchChange = -1; // -1 --- false (0 --- null)
        DisplayChangeEepromData();
    }
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::RadioButtonArchOffClick(bool offClick)
{
    if ( offClick )
    {
        _bfArchChange = 1; // 1 --- true (0 --- null)
        DisplayChangeEepromData();
    }
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::DisplayChangeEepromDataInvoke()
{
    _task->BeginInvoke( & as_DisplayChangeEepromData );
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::DisplayChangeEepromData()
{
    if ( _textChangeIgnore )
    { // ��� ��������� ������� ����������, � �� ������������� (����� ���)
      // ������� ���������� ��� �������
        return;
    }
    _bfChangeEepromCurr = ChangeEepromData();
    if ( _bfChangeEepromOld != _bfChangeEepromCurr )
    {
        ev_DisplayNotSaveChanges( _bfChangeEepromCurr );
        _bfChangeEepromOld = _bfChangeEepromCurr;
    }
}
//---------------------------------------------------------------------------
bool PresenterWindowMainBd85::ChangeEepromData()
{ // ���� ���� ��������� ����-�� ������ ��������� - ��������� ����
    bool flagChenge = false;
    flagChenge |= NotEqual( _indAddrZad, _indAddrZadChange );
    flagChenge |= NotEqual( _groupAddrZad, _groupAddrZadChange );
    flagChenge |= NotEqual( _dnuZad, _dnuZadChange );
    flagChenge |= NotEqual( _voltageHiZad, _voltageHiZadChange );
    flagChenge |= NotEqual( _widthPwmZad, _widthPwmZadChange );
    flagChenge |= NotEqual( _offsetPwmZad, _offsetPwmZadChange );
    flagChenge |= NotEqual( _periodPwmZad, _periodPwmZadChange );
    flagChenge |= NotEqual( _bfArch, _bfArchChange );
    return flagChenge;
}
//---------------------------------------------------------------------------
bool PresenterWindowMainBd85::NotEqual(int var1, int var2)
{
    if ( var1 == var2 )
    {
        return false;
    }
    return true;
}
//---------------------------------------------------------------------------
bool PresenterWindowMainBd85::WriteEEProm()
{ // ���� ���� ������ ���� �� � ����� ���������� - ������ ���� �� ���� �������
    bool flag = true;
    if ( NotEqual( _indAddrZad, _indAddrZadChange ) )
    {
        flag &= _allProtokol->SetIndAdrZ( (unsigned char) _indAddrZadChange );
    }
    if ( NotEqual( _groupAddrZad, _groupAddrZadChange ) )
    {
        flag &= _allProtokol->SetGroupAdrZ( (unsigned char) _groupAddrZadChange );
    }
    if ( NotEqual( _dnuZad, _dnuZadChange ) )
    {
        flag &= _allProtokol->SetDnuZ( (unsigned short) _dnuZadChange );
    }
    if ( NotEqual( _voltageHiZad, _voltageHiZadChange ) )
    {
        flag &= _allProtokol->SetVoltageHiZ_Bd85( (unsigned short) _voltageHiZadChange );
    }
    if ( NotEqual( _widthPwmZad, _widthPwmZadChange ) )
    {
        flag &= _allProtokol->SetWidthPwmZ_Bd85( (unsigned short) _widthPwmZadChange );
    }
    if ( NotEqual( _offsetPwmZad, _offsetPwmZadChange ) )
    {
        flag &= _allProtokol->SetOffsetPwmZ_Bd85( (unsigned short) _offsetPwmZadChange );
    }
    if ( NotEqual( _periodPwmZad, _periodPwmZadChange ) )
    {
        flag &= _allProtokol->SetPeriodPwmZ_Bd85( (unsigned short) _periodPwmZadChange );
    }
    if ( NotEqual( _bfArch, _bfArchChange ) )
    {
        unsigned char archChange;
        if ( _bfArchChange == -1 )
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

