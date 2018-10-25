//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "WindowMainNastrBd85.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
//TWindowMainBd85 *WindowMainBd85;
//---------------------------------------------------------------------------
__fastcall TWindowMainBd85::TWindowMainBd85(TComponent* Owner)
        : TForm(Owner)
        , as_wrapShow(this, &TWindowMainBd85::WrapShow)
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
            &ev_windowShow, // Событие показать окно
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
ActionSelf<>* TWindowMainBd85::GetSelfShow()
{
    return &as_wrapShow;
}
//---------------------------------------------------------------------------
void TWindowMainBd85::WrapShow()
{
    Show();
}
//---------------------------------------------------------------------------
ActionEvent<>* TWindowMainBd85::GetEventFormShow()
{
    return &ev_windowShow;
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
void TWindowMainBd85::SetProtokolName(Protokol protokolName)
{
    comboBox_Protocol->ItemIndex = (int)protokolName;
    switch (protokolName)
    {
    case Protokol_t::NineBit: // 9-ти битный
        TabSheet_ModBusParam->TabVisible = false;
        break;
    case Protokol_t::ModBus_RTU: // ModBus RTU
        TabSheet_ModBusParam->TabVisible = true;
        break;
    case Protokol_t::ModBus_TCP: // ModBus TCP
        TabSheet_ModBusParam->TabVisible = true;
        break;
    case Protokol_t::ModBus_RTU_IP: // ModBus RTU (TCP/IP)
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
    Edit_WidthPwm->Text = data->GetWidthPwmZad();

    delete data; // Освободить память
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
ActionSelf<const char*>* TWindowMainBd85::GetSelfDisplayErrors()
{
    return & as_DisplayCountConnectError; 
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
void __fastcall TWindowMainBd85::FormShow(TObject *Sender)
{
    ev_windowShow();
}
//---------------------------------------------------------------------------
void __fastcall TWindowMainBd85::comboBox_ProtocolChange(TObject *Sender)
{
    ev_comboBox_ProtocolChange( (Protokol)comboBox_Protocol->ItemIndex );
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
void __fastcall TWindowMainBd85::button_WriteToEepromClick(TObject *Sender)
{
    ev_button_WriteToEepromClick();
}
//---------------------------------------------------------------------------

