//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "ModBusParamBd85.h"
#include "TextHelper.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
ModBusParamBd85::ModBusParamBd85(
    IAllProtokolS * protokol,
    IWindowMainBd85 * view,
    TaskWithParam * task)
{
    _protokol = protokol;
    _task = task;
    _view = view;
    _container = _view->GetModBusEventContainer();
    Create(); // ������� ������
}
//---------------------------------------------------------------------------
ModBusParamBd85::~ModBusParamBd85()
{
    Destroy(); // ��������� ������
}
//---------------------------------------------------------------------------
const unsigned short ModBusParamBd85::_numberOfBdMemoryAddr = 10; // 1) ����� �����
const unsigned short ModBusParamBd85::_expositionMemoryAddr = 0x300+2; // 2) ����������, ��
const unsigned short ModBusParamBd85::_minimumCountMemoryAddr = 0x300+3; // 3) ����������� ����
const unsigned short ModBusParamBd85::_maximumCountMemoryAddr = 0x300+4; // 4) ������������ ����
const unsigned short ModBusParamBd85::_levelOfOverloadMemoryAddr = 0x300+5; // 5) ������� ����������
const unsigned short ModBusParamBd85::_quantityOfIntervalMemoryAddr = 0x300+6; // 6) ���-�� ����������
const unsigned short ModBusParamBd85::_quantityOfLookMemoryAddr = 0x300+7;// 7) ���-�� ������� �����
const unsigned short ModBusParamBd85::_levelOfAlarm1MemoryAddr = 0x300+8; // 8) ������� ������� 1 * 10
const unsigned short ModBusParamBd85::_levelOfAlarm2MemoryAddr = 0x300+9; // 9) ������� ������� 2 * 10
const unsigned short ModBusParamBd85::_levelOfAlarm3MemoryAddr = 0x300+10; // 10) ������� ������� 3 * 30
const unsigned short ModBusParamBd85::_phonMemoryAddr = 0x300+11; // 11) ���, �
const unsigned short ModBusParamBd85::_durationOfPhonMemoryAddr = 18; // 12) ����. ������������ ����, �� (8 - ��� ��82)
const unsigned short ModBusParamBd85::_durationOfAlarmMemoryAddr = 0x300 + 12; // 13) ����. ������� �������, �
const unsigned short ModBusParamBd85::_durationOfVideoMemoryAddr = 0x300 + 13; // 14) ����. ������� �����
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void ModBusParamBd85::Create() // ������� ������
{
    // 1) ����� �����
    as_MbParamNumberOfBdChange =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamNumberOfBdChange);
    _container->ev_NumberOfBdChange += as_MbParamNumberOfBdChange;
    // 2) ����������, ��
    as_MbParamExpositionChange =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamExpositionChange);
    _container->ev_ExpositionChange += as_MbParamExpositionChange;
    // 3) ����������� ����
    as_MbParamMinimumCountChange =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamMinimumCountChange);
    _container->ev_MinimumCountChange += as_MbParamMinimumCountChange;
    // 4) ������������ ����
    as_MbParamMaximumCountChange =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamMaximumCountChange);
    _container->ev_MaximumCountChange += as_MbParamMaximumCountChange;
    // 5) ������� ����������
    as_MbParamLevelOfOverloadChange =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamLevelOfOverloadChange);
    _container->ev_LevelOfOverloadChange += as_MbParamLevelOfOverloadChange;
    // 6) ���-�� ����������
    as_MbParamQuantityOfIntervalChange =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamQuantityOfIntervalChange);
    _container->ev_QuantityOfIntervalChange += as_MbParamQuantityOfIntervalChange;
    // 7) ���-�� ������� �����
    as_MbParamQuantityOfLookChange =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamQuantityOfLookChange);
    _container->ev_QuantityOfLookChange += as_MbParamQuantityOfLookChange;
    // 8) ������� ������� 1 * 10
    as_MbParamLevelOfAlarm1Change =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamLevelOfAlarm1Change);
    _container->ev_LevelOfAlarm_1Change += as_MbParamLevelOfAlarm1Change;
    // 9) ������� ������� 2 * 10
    as_MbParamLevelOfAlarm2Change =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamLevelOfAlarm2Change);
    _container->ev_LevelOfAlarm_2Change += as_MbParamLevelOfAlarm2Change;
    // 10) ������� ������� 3 * 30
    as_MbParamLevelOfAlarm3Change =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamLevelOfAlarm3Change);
    _container->ev_LevelOfAlarm_3Change += as_MbParamLevelOfAlarm3Change;
    // 11) ���, �
    as_MbParamPhonChange =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamPhonChange);
    _container->ev_PhonChange += as_MbParamPhonChange;
    // 12) ����. ������������ ����, ��
    as_MbParamDurationOfPhonChange =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamDurationOfPhonChange);
    _container->ev_DurationOfPhonChange += as_MbParamDurationOfPhonChange;
    // 13) ����. ������� �������, �
    as_MbParamDurationOfAlarmChange =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamDurationOfAlarmChange);
    _container->ev_DurationOfAlarmChange += as_MbParamDurationOfAlarmChange;
    // 14) ����. ������� �����
    as_MbParamDurationOfVideoChange =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamDurationOfVideoChange);
    _container->ev_DurationOfVideoChange += as_MbParamDurationOfVideoChange;
    // 15) �� ���������
    as_ButtonModBusSetDefClick =
        new ActionSelf<>(this,
            &ModBusParamBd85::ButtonModBusSetDefClick);
    _container->ev_SetDefClick += as_ButtonModBusSetDefClick;
    // 16) ������
    as_ButtonModBusWriteClick =
        new ActionSelf<>(this,
            &ModBusParamBd85::ButtonModBusWriteClick);
    _container->ev_WriteClick += as_ButtonModBusWriteClick;
    // 17) ������� �� ������ �������
    as_ActivePageIndexChange =
        new ActionSelf<int>(this,
            &ModBusParamBd85::ActivePageIndexChange);
    _container->ev_ActivePageIndex += as_ActivePageIndexChange;
    // === === === === === === === === === ===
    // 18)
    as_WrapReadFlashInvert =
        new ActionSelf<unsigned short, unsigned short*, bool*>(this,
            &ModBusParamBd85::WrapReadFlashInvert);
    // 19)
    as_WrapReadFlash2 =
        new ActionSelf<unsigned short, unsigned short*, bool*>(this,
            &ModBusParamBd85::WrapReadFlash2);
    // 20)
    as_WrapWriteFlashInvert =
        new ActionSelf<unsigned short, unsigned short, bool*>(this,
            &ModBusParamBd85::WrapWriteFlashInvert);
    // 21)
    as_WrapWriteFlash2 =
        new ActionSelf<unsigned short, unsigned short, bool*>(this,
            &ModBusParamBd85::WrapWriteFlash2);
    // === === === === === === === === === ===
    // 22) ���������� ���� ������
    as_DisplayReadReg = new ActionSelf<ModBusTextDataBd85**>(this, &ModBusParamBd85::DisplayReadReg);
    // === === === === === === === === === ===
    // 23) ���������� ��������� ������ (�������� ��� ���)
    as_DisplayNotSaveChanges = new ActionSelf<bool>(this, &ModBusParamBd85::DisplayNotSaveChanges);
    // === === === === === === === === === ===
    InitAddrRegModBus();
    InitParamModBus();
    InitReadDelegate();
    InitWriteDelegate();
    // === === === === === === === === === ===
    _bfNeedReadReg = false;
    _bfNeedWriteReg = false;
    _bfErrorReadReg = false;
    _bfErrorWriteReg = false;
    _textData = 0;
}
//---------------------------------------------------------------------------
void ModBusParamBd85::Destroy() // ��������� ������
{
    delete as_MbParamNumberOfBdChange; // 1) ����� �����
    delete as_MbParamExpositionChange; // 2) ����������, ��
    delete as_MbParamMinimumCountChange; // 3) ����������� ����
    delete as_MbParamMaximumCountChange; // 4) ������������ ����
    delete as_MbParamLevelOfOverloadChange; // 5) ������� ����������
    delete as_MbParamQuantityOfIntervalChange; // 6) ���-�� ����������
    delete as_MbParamQuantityOfLookChange; // 7) ���-�� ������� �����
    delete as_MbParamLevelOfAlarm1Change; // 8) ������� ������� 1 * 10
    delete as_MbParamLevelOfAlarm2Change; // 9) ������� ������� 2 * 10
    delete as_MbParamLevelOfAlarm3Change; // 10) ������� ������� 3 * 30
    delete as_MbParamPhonChange; // 11) ���, �
    delete as_MbParamDurationOfPhonChange; // 12) ����. ������������ ����, ��
    delete as_MbParamDurationOfAlarmChange; // 13) ����. ������� �������, �
    delete as_MbParamDurationOfVideoChange; // 14) ����. ������� �����
    delete as_ButtonModBusSetDefClick; // 15) �� ���������
    delete as_ButtonModBusWriteClick; // 16) ������
    delete as_ActivePageIndexChange; // 17) ������� �� ������ �������
    delete as_WrapReadFlashInvert; // 18) �������-������ ��� ReadFlashInvert
    delete as_WrapReadFlash2;  // 19) �������-������ ��� ReadFlash2
    delete as_WrapWriteFlashInvert; // 20) �������-������ ��� WriteFlashInvert
    delete as_WrapWriteFlash2; // 21) �������-������ ��� WriteFlash2
    delete as_DisplayReadReg; // 22) ������� ��� ������ � ������� ������
    delete as_DisplayNotSaveChanges; // 23) ������� ��� ������ � ������� ������
}
//---------------------------------------------------------------------------
void ModBusParamBd85::ActionIfEventIter() // ��������, ���� �������
{
    ReadRegIfNeed(); // ��������� ��������, ���� �����
    WriteRegIfNeed(); // �������� ��������, ���� �����    
}
//---------------------------------------------------------------------------
void ModBusParamBd85::ActionStart()
{
    switch ( _protokol->GetProtokolName() )
    {
    case ProtokolName_t::ModBus_RTU: // ModBus RTU
    case ProtokolName_t::ModBus_TCP: // ModBus TCP
    case ProtokolName_t::ModBus_RTU_IP: // ModBus RTU (TCP/IP)
        ReadReg();
        _modBusChange.Copy( _modBusSaved );
        _modBusPrev.Copy( _modBusSaved );
        _bfChangeEepromCurr = ChangeEepromData();
        _bfChangeEepromOld = !_bfChangeEepromCurr; // ������� ������� � ���� �����������
        _textData = 0;
        break;
    }
}
//---------------------------------------------------------------------------
bool ModBusParamBd85::ChangeEepromData()
{  // ���� ���� ��������� ����-�� ������ ��������� - ��������� ����
    return _modBusChange.NotEqual( _modBusSaved );
}
//---------------------------------------------------------------------------
void ModBusParamBd85::InitAddrRegModBus()
{
    _addrRegModBus[0] = _numberOfBdMemoryAddr;
    _addrRegModBus[1] = _expositionMemoryAddr;
    _addrRegModBus[2] = _minimumCountMemoryAddr;
    _addrRegModBus[3] = _maximumCountMemoryAddr;
    _addrRegModBus[4] = _levelOfOverloadMemoryAddr;
    _addrRegModBus[5] = _quantityOfIntervalMemoryAddr;
    _addrRegModBus[6] = _quantityOfLookMemoryAddr;
    _addrRegModBus[7] = _levelOfAlarm1MemoryAddr;
    _addrRegModBus[8] = _levelOfAlarm2MemoryAddr;
    _addrRegModBus[9] = _levelOfAlarm3MemoryAddr;
    _addrRegModBus[10] = _phonMemoryAddr;
    _addrRegModBus[11] = _durationOfPhonMemoryAddr;
    _addrRegModBus[12] = _durationOfAlarmMemoryAddr;
    _addrRegModBus[13] = _durationOfVideoMemoryAddr;
}
//---------------------------------------------------------------------------
void ModBusParamBd85::InitParamModBus()
{
    Binding( _paramModBusRead, _modBusSaved );
    Binding( _paramModBusWrite, _modBusChange );
}
//---------------------------------------------------------------------------
void ModBusParamBd85::Binding(
    unsigned short ** paramModBus,
    EepromModBusBd85Settings & data)
{
    //paramModBus[0] = & data.NumberOfBd; // 1) ����� �����
    paramModBus[1] = & data.Exposition; // 2) ����������, ��
    paramModBus[2] = & data.MinimumCount; // 3) ����������� ����
    paramModBus[3] = & data.MaximumCount; // 4) ������������ ����
    paramModBus[4] = & data.LevelOfOverload; // 5) ������� ����������
    paramModBus[5] = & data.QuantityOfInterval; // 6) ���-�� ����������
    paramModBus[6] = & data.QuantityOfLook; // 7) ���-�� ������� �����
    paramModBus[7] = & data.LevelOfAlarm1; // 8) ������� ������� 1 * 10
    paramModBus[8] = & data.LevelOfAlarm2; // 9) ������� ������� 2 * 10
    paramModBus[9] = & data.LevelOfAlarm3; // 10) ������� ������� 3 * 10
    paramModBus[10] = & data.Phon; // 11) ���, �
    paramModBus[11] = & data.DurationOfPhon; // 12) ����. ������������ ����, ��
    paramModBus[12] = & data.DurationOfAlarm; // 13) ����. ������� �������, �
    paramModBus[13] = & data.DurationOfVideo; // 14) ����. ������� �����
}
//---------------------------------------------------------------------------
void ModBusParamBd85::InitReadDelegate()
{
    //ReadRegCurrent[0] = as_WrapReadFlashInvert; // 1) ����� �����
    ReadRegCurrent[1] = as_WrapReadFlash2; // 2) ����������, ��
    ReadRegCurrent[2] = as_WrapReadFlash2; // 3) ����������� ����
    ReadRegCurrent[3] = as_WrapReadFlash2; // 4) ������������ ����
    ReadRegCurrent[4] = as_WrapReadFlash2; // 5) ������� ����������
    ReadRegCurrent[5] = as_WrapReadFlash2; // 6) ���-�� ����������
    ReadRegCurrent[6] = as_WrapReadFlash2; // 7) ���-�� ������� �����
    ReadRegCurrent[7] = as_WrapReadFlash2; // 8) ������� ������� 1 * 10
    ReadRegCurrent[8] = as_WrapReadFlash2; // 9) ������� ������� 2 * 10
    ReadRegCurrent[9] = as_WrapReadFlash2; // 10) ������� ������� 3 * 10
    ReadRegCurrent[10] = as_WrapReadFlash2; // 11) ���, �
    ReadRegCurrent[11] = as_WrapReadFlashInvert; // 12) ����. ������������ ����, ��
    ReadRegCurrent[12] = as_WrapReadFlash2; // 13) ����. ������� �������, �
    ReadRegCurrent[13] = as_WrapReadFlash2; // 14) ����. ������� �����
}
//---------------------------------------------------------------------------
void ModBusParamBd85::InitWriteDelegate()
{
    WriteRegCurrent[0] = as_WrapWriteFlashInvert; // 1) ����� �����
    WriteRegCurrent[1] = as_WrapWriteFlash2; // 2) ����������, ��
    WriteRegCurrent[2] = as_WrapWriteFlash2; // 3) ����������� ����
    WriteRegCurrent[3] = as_WrapWriteFlash2; // 4) ������������ ����
    WriteRegCurrent[4] = as_WrapWriteFlash2; // 5) ������� ����������
    WriteRegCurrent[5] = as_WrapWriteFlash2; // 6) ���-�� ����������
    WriteRegCurrent[6] = as_WrapWriteFlash2; // 7) ���-�� ������� �����
    WriteRegCurrent[7] = as_WrapWriteFlash2; // 8) ������� ������� 1 * 10
    WriteRegCurrent[8] = as_WrapWriteFlash2; // 9) ������� ������� 2 * 10
    WriteRegCurrent[9] = as_WrapWriteFlash2; // 10) ������� ������� 3 * 10
    WriteRegCurrent[10] = as_WrapWriteFlash2; // 11) ���, �
    WriteRegCurrent[11] = as_WrapWriteFlashInvert; // 12) ����. ������������ ����, ��
    WriteRegCurrent[12] = as_WrapWriteFlash2; // 13) ����. ������� �������, �
    WriteRegCurrent[13] = as_WrapWriteFlash2; // 14) ����. ������� �����
}
//---------------------------------------------------------------------------
void ModBusParamBd85::ReadRegIfNeed()
{
    if ( _bfNeedReadReg )
    {
        _bfNeedReadReg = false;
        ActionStart();
        if ( _textData == 0 ) // �������� �����  ����� ���������� ������
        {
            _textData = new ModBusTextDataBd85( & _modBusSaved );
            DisplayChange(
                true, // true - �������� ��������� ������
                true,  // true - ������� �������� �� ��������� ������
                _textData );
        }
    }
}
//---------------------------------------------------------------------------
void ModBusParamBd85::WriteRegIfNeed()
{
    if ( _bfNeedWriteReg )
    {
        WriteReg();
        if ( _bfErrorWriteReg )
        {
            return;
        }
        ReadReg();
        if ( _bfErrorReadReg )
        {
            return;
        }
        if ( _modBusChange.NotEqual( _modBusPrev ) )
        {
            return;
        }
        ModBusTextDataBd85 * data = new ModBusTextDataBd85( & _modBusChange );
        DisplayChange( false, true, data ); // true - ������� ������� �� ��������� ������
        _bfNeedWriteReg = false;
    }
}
//---------------------------------------------------------------------------
void ModBusParamBd85::WriteReg()
{
    bool ReturnVar;
    _bfErrorWriteReg = false;
    ReturnVar = _protokol->WriteFlashInvert( _addrRegModBus[0], _modBusChange.NumberOfBd );
    _bfErrorWriteReg == ( _bfErrorWriteReg || ReturnVar );
    for ( int i = 1; i < regCount; i++ ) // regCount ������ ����������
    {
      (*WriteRegCurrent[i])( _addrRegModBus[i], *_paramModBusWrite[i], &ReturnVar );
      _bfErrorWriteReg == ( _bfErrorWriteReg || ReturnVar );
    }
}
//---------------------------------------------------------------------------
void ModBusParamBd85::ReadReg()
{
    bool ReturnVar;
    _bfErrorReadReg = false;
    ReturnVar = _protokol->ReadFlashInvert( _addrRegModBus[0], & _modBusSaved.NumberOfBd );
    _bfErrorReadReg == ( _bfErrorReadReg || ReturnVar );
    for ( int i = 1; i < regCount; i++ ) // regCount ������ ���������
    {
      (*ReadRegCurrent[i])( _addrRegModBus[i], _paramModBusRead[i], &ReturnVar );
      _bfErrorReadReg == ( _bfErrorReadReg || ReturnVar );
    }
}
//---------------------------------------------------------------------------
void ModBusParamBd85::DisplayReadReg( ModBusTextDataBd85 ** data )
{
    _textChangeIgnore = true; // ������������ ��������� �� ���
    _view->DisplayModBusParamData( *data );
    _textChangeIgnore = false; // �� ������������ ��������� �� ���    
    delete *data;
    *data = 0;
}
//---------------------------------------------------------------------------
void ModBusParamBd85::DisplayNotSaveChanges( bool updataText )
{
    _view->DisplayModBusNotSaveChanges( updataText );
}
//---------------------------------------------------------------------------
void ModBusParamBd85::WrapReadFlashInvert(
    unsigned short memoryAddr,
    unsigned short * data,
    bool * flagError)
{
    unsigned long dataArg;
    *flagError = _protokol->ReadFlashInvert(memoryAddr, & dataArg);
    *data = ( dataArg & 0xFFFF );
}
//---------------------------------------------------------------------------
void ModBusParamBd85::WrapReadFlash2(
    unsigned short memoryAddr, // [IN]
    unsigned short * data, // [OUT]
    bool * flagError)
{
    unsigned long dataArg;
    *flagError = _protokol->ReadFlash2(memoryAddr, & dataArg);
    *data = ( dataArg & 0xFFFF );
}
//---------------------------------------------------------------------------
void ModBusParamBd85::WrapWriteFlashInvert(
    unsigned short memoryAddr,
    unsigned short data,
    bool * flagResult)
{
    *flagResult = _protokol->WriteFlashInvert(memoryAddr, data);
}
//---------------------------------------------------------------------------
void ModBusParamBd85::WrapWriteFlash2(
    unsigned short memoryAddr,
    unsigned short data,
    bool * flagResult)
{
    *flagResult = _protokol->WriteFlash2(memoryAddr, data);
}
//---------------------------------------------------------------------------
void ModBusParamBd85::ToNumber(
    const char * text,
    unsigned short * change,
    unsigned short * prev,
    int max)
{
    bool update;
    int changeArg = *change;
    int prevArg = *prev;
    TextHelper::ConvertTextToNumber( text,
        & changeArg, // [OUT] ��������� �������� ���������
        & prevArg, // [IN/OUT] ���������� �������� ���������
        & update,
        0, max );
    *change = ( changeArg & 0xFFFF );
    *prev = ( prevArg & 0xFFFF );
    ModBusTextDataBd85 * data = new ModBusTextDataBd85( & _modBusChange );
    DisplayChange( update, false, data ); // false - ������� ������� � �������� ������
}
//---------------------------------------------------------------------------
void ModBusParamBd85::ToNumber(
    const char * text,
    unsigned long * change,
    unsigned long * prev,
    int max)
{
    bool update;
    int changeArg = *change;
    int prevArg = *prev;
    TextHelper::ConvertTextToNumber( text,
        & changeArg, // [OUT] ��������� �������� ���������
        & prevArg, // [IN/OUT] ���������� �������� ���������
        & update,
        0, max );
    *change = ( changeArg & 0xFFFFFF );
    *prev = ( prevArg & 0xFFFFFF );
    ModBusTextDataBd85 * data = new ModBusTextDataBd85( & _modBusChange );
    DisplayChange( update, false, data ); // false - ������� ������� � �������� ������
}
//---------------------------------------------------------------------------
void ModBusParamBd85::DisplayChange(
    bool updataText, // true - �������� ��������� ������
    bool inSecondThread,
    ModBusTextDataBd85 *& data ) // true - ������� �������� �� ��������� ������
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
        if ( inSecondThread )
        {
            _task->BeginInvoke( as_DisplayNotSaveChanges, _bfChangeEepromCurr );
        }
        else
        {
            DisplayNotSaveChanges( _bfChangeEepromCurr );
        }
    }
    if ( updataText )
    {
        if ( inSecondThread )
        {
            _task->BeginInvoke(as_DisplayReadReg, & data );
        }
        else
        {
            DisplayReadReg( & data );
        }
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamNumberOfBdChange(const char* text)
{
    ToNumber(text, & _modBusChange.NumberOfBd, & _modBusPrev.NumberOfBd, 0xFFFFFF); // 16777215
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamExpositionChange(const char* text)
{
    ToNumber(text, & _modBusChange.Exposition, & _modBusPrev.Exposition, 0xFFFF);
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamMinimumCountChange(const char* text)
{
    ToNumber(text, & _modBusChange.MinimumCount, & _modBusPrev.MinimumCount, 0xFFFF);
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamMaximumCountChange(const char* text)
{
    ToNumber(text, & _modBusChange.MaximumCount, & _modBusPrev.MaximumCount, 0xFFFF);
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamLevelOfOverloadChange(const char* text)
{
    ToNumber(text, & _modBusChange.LevelOfOverload, & _modBusPrev.LevelOfOverload, 0xFFFF);
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamQuantityOfIntervalChange(const char* text)
{
    ToNumber(text, & _modBusChange.QuantityOfInterval,
        & _modBusPrev.QuantityOfInterval, 0xFFFF);
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamQuantityOfLookChange(const char* text)
{
    ToNumber(text, & _modBusChange.QuantityOfLook, & _modBusPrev.QuantityOfLook, 0xFFFF);
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamLevelOfAlarm1Change(const char* text)
{
    ToNumber(text, & _modBusChange.LevelOfAlarm1, & _modBusPrev.LevelOfAlarm1, 0xFFFF);
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamLevelOfAlarm2Change(const char* text)
{
    ToNumber(text, & _modBusChange.LevelOfAlarm2, & _modBusPrev.LevelOfAlarm2, 0xFFFF);
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamLevelOfAlarm3Change(const char* text)
{
    ToNumber(text, & _modBusChange.LevelOfAlarm3, & _modBusPrev.LevelOfAlarm3, 0xFFFF);
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamPhonChange(const char* text)
{
    ToNumber(text, & _modBusChange.Phon, & _modBusPrev.Phon, 0xFFFF);
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamDurationOfPhonChange(const char* text)
{
    ToNumber(text, & _modBusChange.DurationOfPhon, & _modBusPrev.DurationOfPhon, 0xFFFF);
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamDurationOfAlarmChange(const char* text)
{
    ToNumber(text, & _modBusChange.DurationOfAlarm, & _modBusPrev.DurationOfAlarm, 0xFFFF);
}
//---------------------------------------------------------------------------
void ModBusParamBd85::MbParamDurationOfVideoChange(const char* text)
{
    ToNumber(text, & _modBusChange.DurationOfVideo, & _modBusPrev.DurationOfVideo, 0xFFFF);
}
//---------------------------------------------------------------------------
void ModBusParamBd85::ButtonModBusSetDefClick()
{
    _modBusChange.Default();
    _modBusPrev.Default();
    ModBusTextDataBd85 * data = new ModBusTextDataBd85( & _modBusChange );
    DisplayChange( true, false, data ); // true - ����� �������� ������, false - ������� ������� � �������� ������    
}
//---------------------------------------------------------------------------
void ModBusParamBd85::ButtonModBusWriteClick()
{
    _bfNeedWriteReg = true; // �������� �������� ���������
}
//---------------------------------------------------------------------------
void ModBusParamBd85::ActivePageIndexChange(int api)
{
    ModBusTextDataBd85 * data;
    switch ( api )
    {
    case 0: // �������� �������
        data = new ModBusTextDataBd85();
        DisplayReadReg( & data );
        break;
    case 1: // �������: "��������� ModBus"
        _bfNeedReadReg = true; // ��������� �������� ���������
        break;
    }
}
//---------------------------------------------------------------------------
