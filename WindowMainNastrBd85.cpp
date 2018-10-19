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
        , as_wrapShow(this, &TWindowMainBd85::WrapShow)
        , as_textBox_AddrBd_SetText(this, &TWindowMainBd85::TextBox_AddrBd_SetText)
        , as_setComPortProtEnabled(this, &TWindowMainBd85::SetComPortProtEnabled)
        , as_label_HintSetText(this, &TWindowMainBd85::HintSetText)
        , as_addComPortName(this, &TWindowMainBd85::AddComPortName)
        , as_setProtokolName(this, &TWindowMainBd85::SetProtokolName)
        , as_setEndPoint(this, &TWindowMainBd85::SetEndPoint)

        ,addrBdHelper(
            &as_textBox_AddrBd_SetText, // Изменяю текст программно
            &ev_textBox_AddrBd_Change, // Текст изменился из ГИП
            &ev_button_AddrBd_DecClick,
            &ev_button_AddrBd_IncClick,
            1, 1, 247) // default, minimum, maximum

        ,bdProtHelper(
            &ev_comboBox_ProtocolChange, // Протокол меняется из ГИП
            &as_setComPortProtEnabled, // Меняется вид программно: ком-порт или TCP/IP
            &as_label_HintSetText, // Текст подсказки установить
            &as_addComPortName, // Добавить имя ком-порта в список доступных ком-портов
            &ev_windowShow, // Событие показать окно
            &as_setProtokolName, // Установить имя протокола
            &as_setEndPoint, // Установить IP-адрес и TCP-порт
            &ev_textBox_IP_AddrChange, // Текст ip-адреса изменился из ГИП
            &ev_textBox_TCP_PortChange, // Текст tcp-порта изменился из ГИП
            &ev_button_UpdateNumberOfComPortSClick, // Просьба обновить список доступных ком-портов
            &ev_button_StartStopClick, // Запустить/Остановить обмен данными с БД
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
void TWindowMainBd85::AddComPortName(
    const char* comPortName,
    const char* comPortCount)
{
    comboBox_ComPorts->Items->Add(comPortName);
    label_ComPortsCount->Text = comPortCount;
    comboBox_ComPorts->ItemIndex = 0;
}
//---------------------------------------------------------------------------
void TWindowMainBd85::SetProtokolName(Protokol protokolName)
{
    comboBox_Protocol->ItemIndex = (int)protokolName;
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

