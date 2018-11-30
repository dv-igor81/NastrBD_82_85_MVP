//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "WindowMainNastrBd85.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TWindowMainBd85::TWindowMainBd85(TComponent* Owner)
        : TForm(Owner)
        , as_textBox_AddrBd_SetText(this, &TWindowMainBd85::TextBox_AddrBd_SetText)
        , as_setComPortProtEnabled(this, &TWindowMainBd85::SetComPortProtEnabled)
        , as_label_HintSetText(this, &TWindowMainBd85::HintSetText)
        , as_clearAllComPortName(this, &TWindowMainBd85::ClearAllComPortName)
        , as_setEnabledUpdateComPorts(this, &TWindowMainBd85::SetEnabledUpdateComPorts)
        , as_addComPortName(this, &TWindowMainBd85::AddComPortName)
        , as_setProtokolName(this, &TWindowMainBd85::SetProtokolName)
        , as_setEndPoint(this, &TWindowMainBd85::SetEndPoint)
        , as_SetConnectionState(this, &TWindowMainBd85::SetConnectionState)
        , as_DisplayStartData(this, &TWindowMainBd85::DisplayStartData)
        , as_DisplayCountConnectError(this, &TWindowMainBd85::DisplayCountConnectError)
        , as_DisplayIterData(this, &TWindowMainBd85::DisplayIterData)
        , as_DisplayScalingData(this, &TWindowMainBd85::DisplayScalingData)
        , as_DisplayNotSaveChanges(this, &TWindowMainBd85::DisplayNotSaveChanges)

        ,addrBdHelper(
            &as_textBox_AddrBd_SetText, // Изменяю текст программно
            &ev_textBox_AddrBd_Change, // Текст изменился из ГИП
            &ev_button_AddrBd_DecClick,
            &ev_button_AddrBd_IncClick,
            1, 1, 247) // default, minimum, maximum

        ,bdProtHelper(
            &ev_comboBox_ProtocolChange, // Протокол меняется из ГИП
            &ev_comboBox_ComPortsChange, // Меняется номер ком-порта из ГИП
            &as_setComPortProtEnabled, // Меняется вид программно: ком-порт или TCP/IP
            &as_label_HintSetText, // Текст подсказки установить
            &as_clearAllComPortName, // Очистить список найденых ком-портов
            &as_setEnabledUpdateComPorts, // Установить доступность обновления ком-портов
            &as_addComPortName, // Добавить имя ком-порта в список доступных ком-портов
            &as_setProtokolName, // Установить имя протокола
            &as_setEndPoint, // Установить IP-адрес и TCP-порт
            &ev_textBox_IP_AddrChange, // Текст ip-адреса изменился из ГИП
            &ev_textBox_TCP_PortChange, // Текст tcp-порта изменился из ГИП
            &ev_button_UpdateNumberOfComPortSClick, // Просьба обновить список доступных ком-портов
            &ev_button_StartStopClick, // Запустить/Остановить обмен данными с БД
            &as_SetConnectionState,
            &addrBdHelper)
{
    InitComponrnts();
}
//---------------------------------------------------------------------------
void TWindowMainBd85::Destroy()
{
    delete this;
}
//---------------------------------------------------------------------------
void TWindowMainBd85::SetVerPoText(const char * text)
{
    AnsiString textPoVer = Caption;
    textPoVer += text;
    Caption = textPoVer;
}
//---------------------------------------------------------------------------
void TWindowMainBd85::WrapShow()
{
    this->Show();
}
//---------------------------------------------------------------------------
void TWindowMainBd85::WrapHide()
{
    this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::OnWMSysCommand( TMessage& Message )
{
  // Сохранить описатель окна, пославшего запрос
  //HWND hWndSecond = (HWND)Message.WParam;
  switch( Message.WParam )
  {
    case SC_MINIMIZE:
         Application->Minimize();
         Message.Result = 0;
         break;
    default :
         DefaultHandler( &Message );
  }
}
//---------------------------------------------------------------------------
void TWindowMainBd85::InitComponrnts()
{
    comboBox_Protocol->Style = csDropDownList; // Недоступно для редактирования
    comboBox_Protocol->Items->Add("9-ти битный");
    comboBox_Protocol->Items->Add("ModBus RTU");
    comboBox_Protocol->Items->Add("ModBus TCP");
    comboBox_Protocol->Items->Add("ModBus RTU (TCP/IP)");
    comboBox_Protocol->ItemIndex = 0;
    comboBox_Protocol->Text = "ModBus RTU (TCP/IP)";
    comboBox_ComPorts->Style = csDropDownList; // Недоступно для редактирования
}
//---------------------------------------------------------------------------
ActionEvent<>* TWindowMainBd85::GetEventFormClose()
{
    return &ev_windowClose;
}
//---------------------------------------------------------------------------
HelperConnectFourBdProt* TWindowMainBd85::GetConnectFourBdProt()
{
    return &bdProtHelper;
}
//---------------------------------------------------------------------------
void TWindowMainBd85::TextBox_AddrBd_SetText(const char* text)
{
    textBox_AddrBd->Text = text;
}
//---------------------------------------------------------------------------
void TWindowMainBd85::SetComPortProtEnabled(bool comPortEnable)
{
    groupBox_ComPort->Enabled = comPortEnable;
    groupBox_ComPort->Visible = comPortEnable;
    groupBox_TcpIp->Enabled = !comPortEnable;
    groupBox_TcpIp->Visible = !comPortEnable;
}
//---------------------------------------------------------------------------
void TWindowMainBd85::HintSetText(const char* text)
{
    label_Hint->Caption = text;
}
//---------------------------------------------------------------------------
void TWindowMainBd85::ClearAllComPortName()
{
    comboBox_ComPorts->Items->Clear();
    label_ComPortsCount->Text = "";
}
//---------------------------------------------------------------------------
void TWindowMainBd85::SetEnabledUpdateComPorts(bool enabled)
{
    button_UpdateNumberOfComPortS->Enabled = enabled;
    comboBox_ComPorts->Enabled = enabled;
    button_StartStop->Enabled = enabled;
    comboBox_Protocol->Enabled = enabled;
}
//---------------------------------------------------------------------------
void TWindowMainBd85::AddComPortName(
    const char* comPortName,
    const char* comPortCount)
{
    comboBox_ComPorts->Items->Add(comPortName);
    label_ComPortsCount->Text = comPortCount;
    comboBox_ComPorts->ItemIndex = 0;
    ev_comboBox_ComPortsChange( comboBox_ComPorts->Text.c_str() );
}
//---------------------------------------------------------------------------
void TWindowMainBd85::SetProtokolName(ProtokolName protokolName)
{
    comboBox_Protocol->ItemIndex = (int)protokolName;
    switch (protokolName)
    {
    case ProtokolName_t::NineBit: // 9-ти битный
        TabSheet_ModBusParam->TabVisible = false;
        break;
    case ProtokolName_t::ModBus_RTU: // ModBus RTU
        TabSheet_ModBusParam->TabVisible = true;
        break;
    case ProtokolName_t::ModBus_TCP: // ModBus TCP
        TabSheet_ModBusParam->TabVisible = true;
        break;
    case ProtokolName_t::ModBus_RTU_IP: // ModBus RTU (TCP/IP)
        TabSheet_ModBusParam->TabVisible = true;
        break;
    }
}
//---------------------------------------------------------------------------
void TWindowMainBd85::SetEndPoint(
    const char* textIpAddr,
    const char* textTcpPort)
{
    textBox_IP_Addr->Text = textIpAddr;
    textBox_TCP_Port->Text = textTcpPort;
}
//---------------------------------------------------------------------------
void TWindowMainBd85::SetConnectionState(ConnectionStateInfo state)
{
    switch (state)
    {
    case ConnectionStateInfo_t::WaitConnect:
        button_StartStop->Caption = "Стартую";
        button_StartStop->Enabled = false;
        ControlsAvailability(false);
        ControlsAvailabilityInvert(false);
        break;
    case ConnectionStateInfo_t::IsConnected:
        button_StartStop->Caption = "Прервать";
        button_StartStop->Enabled = true;
        ControlsAvailability(false);
        ControlsAvailabilityInvert(true);
        break;
    case ConnectionStateInfo_t::WaitLoopExit:
        button_StartStop->Caption = "Завершаю";
        button_StartStop->Enabled = false;
        ControlsAvailability(false);
        ControlsAvailabilityInvert(false);
        break;
    case ConnectionStateInfo_t::IsDisconnect:
        button_StartStop->Caption = "Начать";
        button_StartStop->Enabled = true;
        ControlsAvailability(true);
        ControlsAvailabilityInvert(false);
        break;
    }
}
//---------------------------------------------------------------------------
void TWindowMainBd85::ControlsAvailability(bool isEnabled)
{
    comboBox_Protocol->Enabled = isEnabled;
    comboBox_ComPorts->Enabled = isEnabled;
    button_UpdateNumberOfComPortS->Enabled = isEnabled;
    textBox_IP_Addr->Enabled = isEnabled;
    textBox_TCP_Port->Enabled = isEnabled;
    textBox_AddrBd->Enabled = isEnabled;
    button_AddrBd_Dec->Enabled = isEnabled;
    button_AddrBd_Inc->Enabled = isEnabled;
}
//---------------------------------------------------------------------------
void TWindowMainBd85::ControlsAvailabilityInvert(bool isEnabled)
{
    button_WriteToEeprom->Enabled = isEnabled;
    
    Edit_IndAddrZad->ReadOnly = !isEnabled;
    Edit_GroupAdrZad->ReadOnly = !isEnabled;
    Edit_DnuZad_Code->ReadOnly = !isEnabled;
    //comboBox_VoltageHiZad_Value->Style = csDropDownList;
    comboBox_VoltageHiZad_Value->Enabled = isEnabled;
    Edit_WidthPwmZad->ReadOnly = !isEnabled;
    Edit_OffsetPwmZad->ReadOnly = !isEnabled;
    Edit_PeriodPwmZad->ReadOnly = !isEnabled;
    //===>> Параметры ModBus
    Edit_NumberOfBd->ReadOnly = !isEnabled; // 1)
    Edit_Exposition->ReadOnly = !isEnabled; // 2)
    Edit_MinimumCount->ReadOnly = !isEnabled; // 3)
    Edit_MaximumCount->ReadOnly = !isEnabled; // 4)
    Edit_LevelOfOverload->ReadOnly = !isEnabled; // 5)
    Edit_QuantityOfInterval->ReadOnly = !isEnabled; // 6)
    Edit_QuantityOfLook->ReadOnly = !isEnabled; // 7)
    Edit_LevelOfAlarm_1->ReadOnly = !isEnabled; // 8)
    Edit_LevelOfAlarm_2->ReadOnly = !isEnabled; // 9)
    Edit_LevelOfAlarm_3->ReadOnly = !isEnabled; // 10)
    Edit_Phon->ReadOnly = !isEnabled; // 11)
    Edit_DurationOfPhon->ReadOnly = !isEnabled; // 12)
    Edit_DurationOfAlarm->ReadOnly = !isEnabled; // 13
    Edit_DurationOfVideo->ReadOnly = !isEnabled; // 14
    Button_ModBus_SetDef->Enabled = isEnabled;
    Button_ModBus_Write->Enabled = isEnabled;
    //<<=== Параметры ModBus
    button_StartStopScaling->Enabled = isEnabled;
    GroupBox_ReverseLink->Enabled = isEnabled;
    BitBtn_ArchOnOffDisplay->Enabled = isEnabled;
    button_FromFile->Enabled = isEnabled;
}
//---------------------------------------------------------------------------
void TWindowMainBd85::DisplayStartData( StartDataNewBd85* data )
{
    const char * verPo = data->GetVerPo();
    Edit_VerPo0->Text = verPo[0];
    Edit_VerPo1->Text = verPo[1];
    Edit_VerPo2->Text = verPo[2];
    Edit_VerPo3->Text = verPo[3];
    Edit_IndAddrZad->Text = data->GetIndAddrZad();
    Edit_GroupAdrZad->Text = data->GetGroupAddrZad();
    Edit_DnuZad_Code->Text = data->GetDnuZad();
    Edit_DnuZad_Value->Text = data->GetDnuValueZad();
    Edit_VoltageHiZad_Code->Text = data->GetVoltageHiZad();
    comboBox_VoltageHiZad_Value->Text = data->GetVoltageHiValueZad();
    Edit_WidthPwmZad->Text = data->GetWidthPwmZad();
    Edit_OffsetPwmZad->Text = data->GetOffsetPwmZad();
    Edit_PeriodPwmZad->Text = data->GetPeriodPwmZad();
    switch ( data->GetFlagArch() )
    {
    case -1:
        radioButton_ArchOn->Checked = true;
        BitBtn_ArchOnOffDisplay->Kind = bkRetry;
        BitBtn_ArchOnOffDisplay->Caption = "Включена";
        BitBtn_ArchOnOffDisplay->Font->Color = clGreen;
        break;
    case 1:
        radioButton_ArchOff->Checked = true;
        BitBtn_ArchOnOffDisplay->Kind = bkNo;
        BitBtn_ArchOnOffDisplay->Caption = "Отключена";
        BitBtn_ArchOnOffDisplay->Font->Color = clRed;
        break;
    case 0:
        radioButton_ArchOn->Checked = false;
        radioButton_ArchOff->Checked = false;
        BitBtn_ArchOnOffDisplay->Kind = bkCustom;
        BitBtn_ArchOnOffDisplay->Caption = "";
        break;
    }
}
//---------------------------------------------------------------------------
void TWindowMainBd85::DisplayIterData( IterDataNewBd85* data )
{
    Edit_IndAddr->Text = data->GetIndAddr();
    Edit_GroupAdr->Text = data->GetGroupAddr();
    Edit_Temperature_Code->Text = data->GetTemperatureCode();
    Edit_Temperature_Value->Text = data->GetTemperatureValue();
    Edit_DNU_Code->Text = data->GetDnuCode();
    Edit_DNU_Value->Text = data->GetDnuValue();
    Edit_VoltageHi_Code->Text = data->GetVoltageHiCode();
    Edit_VoltageHi_Value->Text = data->GetVoltageHiValue();
    Edit_WidthPwm_Code->Text = data->GetWidthPwmCode();
    Edit_WidthPwm_Value->Text = data->GetWidthPwmValue();
    Edit_PeriodPwm_Code->Text = data->GetPeriodPwmCode();
    Edit_PeriodPwm_Value->Text = data->GetPeriodPwmValue();
    AnsiString text = data->GetScaling();
    if ( text != "..." )// ...
    {
        Edit_Scaling->Text = data->GetScaling();
    }
}
//---------------------------------------------------------------------------
void TWindowMainBd85::DisplayScalingData( ScalingDataNewBd85* data )
{
    if ( data->GetStartWorkScalingSumm() ) // Начать работу
    {
        button_ClearScaling->Enabled = true;
        Edit_TimeMeteringLimit->Enabled = false;
        button_StartStopScaling->Caption = "Стоп";
        Edit_TimeMeteringLimit->Text = data->GetTimeMeteringLimit();
    }
    if ( data->GetWorkScalingSumm() == false ) // Завершить работу
    {
        button_ClearScaling->Enabled = false;
        Edit_TimeMeteringLimit->Enabled = true;
        button_StartStopScaling->Caption = "Старт";
        Edit_TimeMeteringLimit->Enabled = true;
    }
    Edit_TimeScaling->Text = data->GetTimeScaling(); // Текущее время набора среднего счёта
    Edit_TotalScaling->Text = data->GetTotalScaling(); // Суммарный счёт (Интеграл)
    Edit_MiddleSecondScaling->Text = data->GetMiddleScaling(); // Средний счёт за секунду
}
//---------------------------------------------------------------------------
void TWindowMainBd85::DisplayModBusParamData( ModBusTextDataBd85 * data )
{
    Edit_NumberOfBd->Text = data->GetNumberOfBd();
    Edit_Exposition->Text = data->GetExposition();
    Edit_MinimumCount->Text = data->GetMinimumCount();
    Edit_MaximumCount->Text = data->GetMaximumCount();
    Edit_LevelOfOverload->Text = data->GetLevelOfOverload();
    Edit_QuantityOfInterval->Text = data->GetQuantityOfInterval();
    Edit_QuantityOfLook->Text = data->GetQuantityOfLook();
    Edit_LevelOfAlarm_1->Text = data->GetLevelOfAlarm1();
    Edit_LevelOfAlarm_2->Text = data->GetLevelOfAlarm2();
    Edit_LevelOfAlarm_3->Text = data->GetLevelOfAlarm3();
    Edit_Phon->Text = data->GetPhon();
    Edit_DurationOfPhon->Text = data->GetDurationOfPhon();
    Edit_DurationOfAlarm->Text = data->GetDurationOfAlarm();
    Edit_DurationOfVideo->Text = data->GetDurationOfVideo();
}    
//---------------------------------------------------------------------------
void TWindowMainBd85::DisplayCountConnectError(const char* text)
{
    Edit_ErrorConnectCount->Text = text;
}
//---------------------------------------------------------------------------
ActionSelf<StartDataNewBd85*>* TWindowMainBd85::GetSelfDisplayStartData()
{
    return & as_DisplayStartData; // Отобразить данные считанные при старте опроса
}
//---------------------------------------------------------------------------
ActionSelf<IterDataNewBd85*>& TWindowMainBd85::GetSelfDisplayIterData()
{
    return as_DisplayIterData;
}
//---------------------------------------------------------------------------
ActionSelf<const char*>* TWindowMainBd85::GetSelfDisplayErrors()
{
    return & as_DisplayCountConnectError; 
}
//---------------------------------------------------------------------------
ActionEvent<const char*>* TWindowMainBd85::GetEventButtonStartStopScalingClick()
{
    return & ev_button_StartStopScalingClick;
}
//---------------------------------------------------------------------------
ActionSelf<ScalingDataNewBd85*>& TWindowMainBd85::GetSelfDisplayScalingData()
{
    return as_DisplayScalingData;
}
//---------------------------------------------------------------------------
ActionEvent<>& TWindowMainBd85::GetEventButtonClearScalingClick()
{
    return ev_button_ClearScalingClick;
}
//---------------------------------------------------------------------------
ActionEvent<>& TWindowMainBd85::GetEventButtonWriteToEepromClick()
{
    return ev_button_WriteToEepromClick;
}
//---------------------------------------------------------------------------
ActionEvent<const char*>& TWindowMainBd85::GetEventTextIndAddrZadChange()
{
    return ev_Text_IndAddrZadChange;
}
//---------------------------------------------------------------------------
ActionEvent<const char*>& TWindowMainBd85::GetEventTextGroupAdrZadChange()
{
    return ev_Text_GroupAdrZadChange;
}
//---------------------------------------------------------------------------
ActionEvent<const char*>& TWindowMainBd85::GetEventTextDnuZadCodeChange()
{
    return ev_Text_DnuZadCodeChange;
}
//---------------------------------------------------------------------------
ActionEvent<const char*>& TWindowMainBd85::GetEventTextVoltageHiZadChange()
{
    return ev_Text_VoltageHiZadChange;
}
//---------------------------------------------------------------------------
ActionEvent<const char*>& TWindowMainBd85::GetEventTextWidthPwmZadChange()
{
    return ev_Text_WidthPwmZadChange;
}
//---------------------------------------------------------------------------
ActionEvent<const char*>& TWindowMainBd85::GetEventTextOffsetPwmZadChange()
{
    return ev_Text_OffsetPwmZadChange;
}
//---------------------------------------------------------------------------
ActionEvent<const char*>& TWindowMainBd85::GetEventTextPeriodPwmZadChange()
{
    return ev_Text_PeriodPwmZadChange;
}
//---------------------------------------------------------------------------
ActionEvent<bool>& TWindowMainBd85::GetEventRadioButtonArchOnClick()
{
    return ev_radioButton_ArchOnClick;
}
//---------------------------------------------------------------------------
ActionEvent<bool>& TWindowMainBd85::GetEventRadioButtonArchOffClick()
{
    return ev_radioButton_ArchOffClick;
}
//---------------------------------------------------------------------------
void TWindowMainBd85::DisplayNotSaveChanges( bool display )
{
    Label_ChangeEEPROM->Visible = display;
}
//---------------------------------------------------------------------------
ActionSelf<bool>& TWindowMainBd85::GetSelfDisplayNotSaveChanges()
{
    return as_DisplayNotSaveChanges;
}
//---------------------------------------------------------------------------
void TWindowMainBd85::DisplayModBusNotSaveChanges( bool display )
{ // Отобразить не сохраненные изменения
    Label_ChangeModBusEEPROM->Visible = display;
}
//---------------------------------------------------------------------------
ActionEvent<>& TWindowMainBd85::GetEventButtonFromFileClick()
{
    return ev_button_FromFileClick;
}
//---------------------------------------------------------------------------
ActionEvent<>& TWindowMainBd85::GetEventButtonSaveToFileClick()
{
    return ev_button_SaveToFileClick;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::button_StartStopClick(TObject *Sender)
{
    ev_button_StartStopClick();
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::button_AddrBd_DecClick(TObject *Sender)
{
    ev_button_AddrBd_DecClick();
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::button_AddrBd_IncClick(TObject *Sender)
{
    ev_button_AddrBd_IncClick();
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::textBox_AddrBdChange(TObject *Sender)
{
    ev_textBox_AddrBd_Change( textBox_AddrBd->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::comboBox_ProtocolChange(TObject *Sender)
{
    ev_comboBox_ProtocolChange( (ProtokolName)comboBox_Protocol->ItemIndex );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    ev_windowClose();
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::textBox_IP_AddrChange(TObject *Sender)
{
    ev_textBox_IP_AddrChange( textBox_IP_Addr->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::textBox_TCP_PortChange(TObject *Sender)
{
    ev_textBox_TCP_PortChange( textBox_TCP_Port->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::button_UpdateNumberOfComPortSClick(
      TObject *Sender)
{
    ev_button_UpdateNumberOfComPortSClick();
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::comboBox_ComPortsChange(TObject *Sender)
{
    ev_comboBox_ComPortsChange( comboBox_ComPorts->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::button_StartStopScalingClick(
      TObject *Sender)
{
    ev_button_StartStopScalingClick( Edit_TimeMeteringLimit->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::button_ClearScalingClick(TObject *Sender)
{
    ev_button_ClearScalingClick();
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::button_WriteToEepromClick(TObject *Sender)
{
    ev_button_WriteToEepromClick();
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::Edit_IndAddrZadChange(TObject *Sender)
{
    ev_Text_IndAddrZadChange( Edit_IndAddrZad->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::Edit_GroupAdrZadChange(TObject *Sender)
{
    ev_Text_GroupAdrZadChange( Edit_GroupAdrZad->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::Edit_DnuZad_CodeChange(TObject *Sender)
{
    ev_Text_DnuZadCodeChange( Edit_DnuZad_Code->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::comboBox_VoltageHiZad_ValueChange(
      TObject *Sender)
{
    ev_Text_VoltageHiZadChange( comboBox_VoltageHiZad_Value->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::Edit_WidthPwmZadChange(TObject *Sender)
{
    ev_Text_WidthPwmZadChange( Edit_WidthPwmZad->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::Edit_OffsetPwmZadChange(TObject *Sender)
{
    ev_Text_OffsetPwmZadChange( Edit_OffsetPwmZad->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::Edit_PeriodPwmZadChange(TObject *Sender)
{
    ev_Text_PeriodPwmZadChange( Edit_PeriodPwmZad->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::radioButton_ArchOnClick(TObject *Sender)
{
    ev_radioButton_ArchOnClick( radioButton_ArchOn->Checked );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::radioButton_ArchOffClick(TObject *Sender)
{
    ev_radioButton_ArchOffClick( radioButton_ArchOff->Checked );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::Edit_NumberOfBdChange(TObject *Sender)
{ // Номер блока
    mbContainer.ev_NumberOfBdChange( Edit_NumberOfBd->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::Edit_ExpositionChange(TObject *Sender)
{ // Экспозиция, мс
    mbContainer.ev_ExpositionChange( Edit_Exposition->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::Edit_MinimumCountChange(TObject *Sender)
{ // Минимальный счёт
    mbContainer.ev_MinimumCountChange( Edit_MinimumCount->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::Edit_MaximumCountChange(TObject *Sender)
{ // Максимальный счёт
    mbContainer.ev_MaximumCountChange( Edit_MaximumCount->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::Edit_LevelOfOverloadChange(
      TObject *Sender)
{ // Уровень перегрузки
    mbContainer.ev_LevelOfOverloadChange( Edit_LevelOfOverload->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::Edit_QuantityOfIntervalChange(
      TObject *Sender)
{ // Кол-во интервалов
    mbContainer.ev_QuantityOfIntervalChange( Edit_QuantityOfInterval->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::Edit_QuantityOfLookChange(TObject *Sender)
{ // Кол-во взгляда после
    mbContainer.ev_QuantityOfLookChange( Edit_QuantityOfLook->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::Edit_LevelOfAlarm_1Change(TObject *Sender)
{ // Уровень тревоги 1 * 10
    mbContainer.ev_LevelOfAlarm_1Change( Edit_LevelOfAlarm_1->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::Edit_LevelOfAlarm_2Change(TObject *Sender)
{ // Уровень тревоги 2 * 10
    mbContainer.ev_LevelOfAlarm_2Change( Edit_LevelOfAlarm_2->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::Edit_LevelOfAlarm_3Change(TObject *Sender)
{ // Уровень тревоги 3 * 10
    mbContainer.ev_LevelOfAlarm_3Change( Edit_LevelOfAlarm_3->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::Edit_PhonChange(TObject *Sender)
{ // Фон, с
    mbContainer.ev_PhonChange( Edit_Phon->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::Edit_DurationOfPhonChange(TObject *Sender)
{ // Длит. подинтервала фона, мс
    mbContainer.ev_DurationOfPhonChange( Edit_DurationOfPhon->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::Edit_DurationOfAlarmChange(
      TObject *Sender)
{ // Длит. сигнала тревоги
    mbContainer.ev_DurationOfAlarmChange( Edit_DurationOfAlarm->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::Edit_DurationOfVideoChange(
      TObject *Sender)
{ // Длит. сигнала видео
    mbContainer.ev_DurationOfVideoChange( Edit_DurationOfVideo->Text.c_str() );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::Button_ModBus_SetDefClick(TObject *Sender)
{ // По умолчанию
    mbContainer.ev_SetDefClick();
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::Button_ModBus_WriteClick(TObject *Sender)
{ // Запись
    mbContainer.ev_WriteClick();
}
//---------------------------------------------------------------------------
ModBusEventContainerBd85 * TWindowMainBd85::GetModBusEventContainer()
{
    return & mbContainer;
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::PageControl_WindowBd85Change(
      TObject *Sender)
{
    mbContainer.ev_ActivePageIndex( PageControl_WindowBd85->ActivePageIndex );
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::button_FromFileClick(TObject *Sender)
{
    ev_button_FromFileClick();
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::button_SaveToFileClick(TObject *Sender)
{
    ev_button_SaveToFileClick();
}
//---------------------------------------------------------------------------

