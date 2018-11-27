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
    Create(); // Создать объект
}
//---------------------------------------------------------------------------
ModBusParamBd85::~ModBusParamBd85()
{
    Destroy(); // Разрушить объект
}
//---------------------------------------------------------------------------
const unsigned short ModBusParamBd85::_numberOfBdMemoryAddr = 10; // 1) Номер блока
const unsigned short ModBusParamBd85::_expositionMemoryAddr = 0x300+2; // 2) Экспозиция, мс
const unsigned short ModBusParamBd85::_minimumCountMemoryAddr = 0x300+3; // 3) Минимальный счёт
const unsigned short ModBusParamBd85::_maximumCountMemoryAddr = 0x300+4; // 4) Максимальный счёт
const unsigned short ModBusParamBd85::_levelOfOverloadMemoryAddr = 0x300+5; // 5) Уровень перегрузки
const unsigned short ModBusParamBd85::_quantityOfIntervalMemoryAddr = 0x300+6; // 6) Кол-во интервалов
const unsigned short ModBusParamBd85::_quantityOfLookMemoryAddr = 0x300+7;// 7) Кол-во взгляда после
const unsigned short ModBusParamBd85::_levelOfAlarm1MemoryAddr = 0x300+8; // 8) Уровень тревоги 1 * 10
const unsigned short ModBusParamBd85::_levelOfAlarm2MemoryAddr = 0x300+9; // 9) Уровень тревоги 2 * 10
const unsigned short ModBusParamBd85::_levelOfAlarm3MemoryAddr = 0x300+10; // 10) Уровень тревоги 3 * 30
const unsigned short ModBusParamBd85::_phonMemoryAddr = 0x300+11; // 11) Фон, с
const unsigned short ModBusParamBd85::_durationOfPhonMemoryAddr = 18; // 12) Длит. подинтервала фона, мс (8 - для БД82)
const unsigned short ModBusParamBd85::_durationOfAlarmMemoryAddr = 0x300 + 12; // 13) Длит. сигнала тревоги, с
const unsigned short ModBusParamBd85::_durationOfVideoMemoryAddr = 0x300 + 13; // 14) Длит. сигнала видео
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void ModBusParamBd85::Create() // Создать объект
{
    // 1) Номер блока
    as_MbParamNumberOfBdChange =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamNumberOfBdChange);
    _container->ev_NumberOfBdChange += as_MbParamNumberOfBdChange;
    // 2) Экспозиция, мс
    as_MbParamExpositionChange =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamExpositionChange);
    _container->ev_ExpositionChange += as_MbParamExpositionChange;
    // 3) Минимальный счёт
    as_MbParamMinimumCountChange =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamMinimumCountChange);
    _container->ev_MinimumCountChange += as_MbParamMinimumCountChange;
    // 4) Максимальный счёт
    as_MbParamMaximumCountChange =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamMaximumCountChange);
    _container->ev_MaximumCountChange += as_MbParamMaximumCountChange;
    // 5) Уровень перегрузки
    as_MbParamLevelOfOverloadChange =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamLevelOfOverloadChange);
    _container->ev_LevelOfOverloadChange += as_MbParamLevelOfOverloadChange;
    // 6) Кол-во интервалов
    as_MbParamQuantityOfIntervalChange =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamQuantityOfIntervalChange);
    _container->ev_QuantityOfIntervalChange += as_MbParamQuantityOfIntervalChange;
    // 7) Кол-во взгляда после
    as_MbParamQuantityOfLookChange =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamQuantityOfLookChange);
    _container->ev_QuantityOfLookChange += as_MbParamQuantityOfLookChange;
    // 8) Уровень тревоги 1 * 10
    as_MbParamLevelOfAlarm1Change =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamLevelOfAlarm1Change);
    _container->ev_LevelOfAlarm_1Change += as_MbParamLevelOfAlarm1Change;
    // 9) Уровень тревоги 2 * 10
    as_MbParamLevelOfAlarm2Change =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamLevelOfAlarm2Change);
    _container->ev_LevelOfAlarm_2Change += as_MbParamLevelOfAlarm2Change;
    // 10) Уровень тревоги 3 * 30
    as_MbParamLevelOfAlarm3Change =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamLevelOfAlarm3Change);
    _container->ev_LevelOfAlarm_3Change += as_MbParamLevelOfAlarm3Change;
    // 11) Фон, с
    as_MbParamPhonChange =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamPhonChange);
    _container->ev_PhonChange += as_MbParamPhonChange;
    // 12) Длит. подинтервала фона, мс
    as_MbParamDurationOfPhonChange =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamDurationOfPhonChange);
    _container->ev_DurationOfPhonChange += as_MbParamDurationOfPhonChange;
    // 13) Длит. сигнала тревоги, с
    as_MbParamDurationOfAlarmChange =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamDurationOfAlarmChange);
    _container->ev_DurationOfAlarmChange += as_MbParamDurationOfAlarmChange;
    // 14) Длит. сигнала видео
    as_MbParamDurationOfVideoChange =
        new ActionSelf<const char*>(this,
            &ModBusParamBd85::MbParamDurationOfVideoChange);
    _container->ev_DurationOfVideoChange += as_MbParamDurationOfVideoChange;
    // 15) По умолчанию
    as_ButtonModBusSetDefClick =
        new ActionSelf<>(this,
            &ModBusParamBd85::ButtonModBusSetDefClick);
    _container->ev_SetDefClick += as_ButtonModBusSetDefClick;
    // 16) Запись
    as_ButtonModBusWriteClick =
        new ActionSelf<>(this,
            &ModBusParamBd85::ButtonModBusWriteClick);
    _container->ev_WriteClick += as_ButtonModBusWriteClick;
    // 17) Перешли на другую вкладку
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
    // 22) Отобразить сами данные
    as_DisplayReadReg = new ActionSelf<ModBusTextDataBd85**>(this, &ModBusParamBd85::DisplayReadReg);
    // === === === === === === === === === ===
    // 23) Отобразить состояние данных (изменены или нет)
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
void ModBusParamBd85::Destroy() // Разрушить объект
{
    delete as_MbParamNumberOfBdChange; // 1) Номер блока
    delete as_MbParamExpositionChange; // 2) Экспозиция, мс
    delete as_MbParamMinimumCountChange; // 3) Минимальный счёт
    delete as_MbParamMaximumCountChange; // 4) Максимальный счёт
    delete as_MbParamLevelOfOverloadChange; // 5) Уровень перегрузки
    delete as_MbParamQuantityOfIntervalChange; // 6) Кол-во интервалов
    delete as_MbParamQuantityOfLookChange; // 7) Кол-во взгляда после
    delete as_MbParamLevelOfAlarm1Change; // 8) Уровень тревоги 1 * 10
    delete as_MbParamLevelOfAlarm2Change; // 9) Уровень тревоги 2 * 10
    delete as_MbParamLevelOfAlarm3Change; // 10) Уровень тревоги 3 * 30
    delete as_MbParamPhonChange; // 11) Фон, с
    delete as_MbParamDurationOfPhonChange; // 12) Длит. подинтервала фона, мс
    delete as_MbParamDurationOfAlarmChange; // 13) Длит. сигнала тревоги, с
    delete as_MbParamDurationOfVideoChange; // 14) Длит. сигнала видео
    delete as_ButtonModBusSetDefClick; // 15) По умолчанию
    delete as_ButtonModBusWriteClick; // 16) Запись
    delete as_ActivePageIndexChange; // 17) Перешли на другую вкладку
    delete as_WrapReadFlashInvert; // 18) Делегат-обёртка для ReadFlashInvert
    delete as_WrapReadFlash2;  // 19) Делегат-обёртка для ReadFlash2
    delete as_WrapWriteFlashInvert; // 20) Делегат-обёртка для WriteFlashInvert
    delete as_WrapWriteFlash2; // 21) Делегат-обёртка для WriteFlash2
    delete as_DisplayReadReg; // 22) Делегат для вызова в главном потоке
    delete as_DisplayNotSaveChanges; // 23) Делегат для вызова в главном потоке
}
//---------------------------------------------------------------------------
void ModBusParamBd85::ActionIfEventIter() // Действие, если событие
{
    ReadRegIfNeed(); // Прочитать регистры, если нужно
    WriteRegIfNeed(); // Записать регистры, если нужно    
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
        _bfChangeEepromOld = !_bfChangeEepromCurr; // Вызвать функцию в ГИПе ОБЯЗАТЕЛЬНО
        _textData = 0;
        break;
    }
}
//---------------------------------------------------------------------------
bool ModBusParamBd85::ChangeEepromData()
{  // Если есть изменения хотя-бы одного параметра - изменения есть
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
    //paramModBus[0] = & data.NumberOfBd; // 1) Номер блока
    paramModBus[1] = & data.Exposition; // 2) Экспозиция, мс
    paramModBus[2] = & data.MinimumCount; // 3) Минимальный счёт
    paramModBus[3] = & data.MaximumCount; // 4) Максимальный счёт
    paramModBus[4] = & data.LevelOfOverload; // 5) Уровень перегрузки
    paramModBus[5] = & data.QuantityOfInterval; // 6) Кол-во интервалов
    paramModBus[6] = & data.QuantityOfLook; // 7) Кол-во взгляда после
    paramModBus[7] = & data.LevelOfAlarm1; // 8) Уровень тревоги 1 * 10
    paramModBus[8] = & data.LevelOfAlarm2; // 9) Уровень тревоги 2 * 10
    paramModBus[9] = & data.LevelOfAlarm3; // 10) Уровень тревоги 3 * 10
    paramModBus[10] = & data.Phon; // 11) Фон, с
    paramModBus[11] = & data.DurationOfPhon; // 12) Длит. подинтервала фона, мс
    paramModBus[12] = & data.DurationOfAlarm; // 13) Длит. сигнала тревоги, с
    paramModBus[13] = & data.DurationOfVideo; // 14) Длит. сигнала видео
}
//---------------------------------------------------------------------------
void ModBusParamBd85::InitReadDelegate()
{
    //ReadRegCurrent[0] = as_WrapReadFlashInvert; // 1) Номер блока
    ReadRegCurrent[1] = as_WrapReadFlash2; // 2) Экспозиция, мс
    ReadRegCurrent[2] = as_WrapReadFlash2; // 3) Минимальный счёт
    ReadRegCurrent[3] = as_WrapReadFlash2; // 4) Максимальный счёт
    ReadRegCurrent[4] = as_WrapReadFlash2; // 5) Уровень перегрузки
    ReadRegCurrent[5] = as_WrapReadFlash2; // 6) Кол-во интервалов
    ReadRegCurrent[6] = as_WrapReadFlash2; // 7) Кол-во взгляда после
    ReadRegCurrent[7] = as_WrapReadFlash2; // 8) Уровень тревоги 1 * 10
    ReadRegCurrent[8] = as_WrapReadFlash2; // 9) Уровень тревоги 2 * 10
    ReadRegCurrent[9] = as_WrapReadFlash2; // 10) Уровень тревоги 3 * 10
    ReadRegCurrent[10] = as_WrapReadFlash2; // 11) Фон, с
    ReadRegCurrent[11] = as_WrapReadFlashInvert; // 12) Длит. подинтервала фона, мс
    ReadRegCurrent[12] = as_WrapReadFlash2; // 13) Длит. сигнала тревоги, с
    ReadRegCurrent[13] = as_WrapReadFlash2; // 14) Длит. сигнала видео
}
//---------------------------------------------------------------------------
void ModBusParamBd85::InitWriteDelegate()
{
    WriteRegCurrent[0] = as_WrapWriteFlashInvert; // 1) Номер блока
    WriteRegCurrent[1] = as_WrapWriteFlash2; // 2) Экспозиция, мс
    WriteRegCurrent[2] = as_WrapWriteFlash2; // 3) Минимальный счёт
    WriteRegCurrent[3] = as_WrapWriteFlash2; // 4) Максимальный счёт
    WriteRegCurrent[4] = as_WrapWriteFlash2; // 5) Уровень перегрузки
    WriteRegCurrent[5] = as_WrapWriteFlash2; // 6) Кол-во интервалов
    WriteRegCurrent[6] = as_WrapWriteFlash2; // 7) Кол-во взгляда после
    WriteRegCurrent[7] = as_WrapWriteFlash2; // 8) Уровень тревоги 1 * 10
    WriteRegCurrent[8] = as_WrapWriteFlash2; // 9) Уровень тревоги 2 * 10
    WriteRegCurrent[9] = as_WrapWriteFlash2; // 10) Уровень тревоги 3 * 10
    WriteRegCurrent[10] = as_WrapWriteFlash2; // 11) Фон, с
    WriteRegCurrent[11] = as_WrapWriteFlashInvert; // 12) Длит. подинтервала фона, мс
    WriteRegCurrent[12] = as_WrapWriteFlash2; // 13) Длит. сигнала тревоги, с
    WriteRegCurrent[13] = as_WrapWriteFlash2; // 14) Длит. сигнала видео
}
//---------------------------------------------------------------------------
void ModBusParamBd85::ReadRegIfNeed()
{
    if ( _bfNeedReadReg )
    {
        _bfNeedReadReg = false;
        ActionStart();
        if ( _textData == 0 ) // Основной поток  успел отобразить данные
        {
            _textData = new ModBusTextDataBd85( & _modBusSaved );
            DisplayChange(
                true, // true - обновить текстовые данные
                true,  // true - функция запущена во вторичном потоке
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
        DisplayChange( false, true, data ); // true - функция вызвана во вторичном потоке
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
    for ( int i = 1; i < regCount; i++ ) // regCount данных записываем
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
    for ( int i = 1; i < regCount; i++ ) // regCount данных считываем
    {
      (*ReadRegCurrent[i])( _addrRegModBus[i], _paramModBusRead[i], &ReturnVar );
      _bfErrorReadReg == ( _bfErrorReadReg || ReturnVar );
    }
}
//---------------------------------------------------------------------------
void ModBusParamBd85::DisplayReadReg( ModBusTextDataBd85 ** data )
{
    _textChangeIgnore = true; // Игнорировать изменения из ГИП
    _view->DisplayModBusParamData( *data );
    _textChangeIgnore = false; // Не игнорировать изменения из ГИП    
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
        & changeArg, // [OUT] Изменённое значение параметра
        & prevArg, // [IN/OUT] Предыдущее значение параметра
        & update,
        0, max );
    *change = ( changeArg & 0xFFFF );
    *prev = ( prevArg & 0xFFFF );
    ModBusTextDataBd85 * data = new ModBusTextDataBd85( & _modBusChange );
    DisplayChange( update, false, data ); // false - функция вызвана в основном потоке
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
        & changeArg, // [OUT] Изменённое значение параметра
        & prevArg, // [IN/OUT] Предыдущее значение параметра
        & update,
        0, max );
    *change = ( changeArg & 0xFFFFFF );
    *prev = ( prevArg & 0xFFFFFF );
    ModBusTextDataBd85 * data = new ModBusTextDataBd85( & _modBusChange );
    DisplayChange( update, false, data ); // false - функция вызвана в основном потоке
}
//---------------------------------------------------------------------------
void ModBusParamBd85::DisplayChange(
    bool updataText, // true - обновить текстовые данные
    bool inSecondThread,
    ModBusTextDataBd85 *& data ) // true - функция запущена во вторичном потоке
{
    if ( _textChangeIgnore )
    { // Эти изменения внесены программно, а не пользователем (через ГИП)
      // поэтому игнорируем это событие
        return;
    }
    _bfChangeEepromCurr = ChangeEepromData(); // Есть ли изменения хотя-бы одного параметра?
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
    DisplayChange( true, false, data ); // true - нужно обновить данные, false - функция вызвана в основном потоке    
}
//---------------------------------------------------------------------------
void ModBusParamBd85::ButtonModBusWriteClick()
{
    _bfNeedWriteReg = true; // Записать значения регистров
}
//---------------------------------------------------------------------------
void ModBusParamBd85::ActivePageIndexChange(int api)
{
    ModBusTextDataBd85 * data;
    switch ( api )
    {
    case 0: // Основная вкладка
        data = new ModBusTextDataBd85();
        DisplayReadReg( & data );
        break;
    case 1: // Вкладка: "Параметры ModBus"
        _bfNeedReadReg = true; // Прочитать значения регистров
        break;
    }
}
//---------------------------------------------------------------------------
