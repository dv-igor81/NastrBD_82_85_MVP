//---------------------------------------------------------------------------
#ifndef WindowMainNastrBd85H
#define WindowMainNastrBd85H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "Protokol_t.h"
#include "ConnectionStateInfo_t.h"
#include "IWindowMainBd85.h"
#include <ComCtrls.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TWindowMainBd85 : public TForm, public IWindowMainBd85
{
__published:	// IDE-managed Components
        TPageControl *PageControl_WindowBd85;
        TTabSheet *TabSheet_MainParam;
        TTabSheet *TabSheet_ModBusParam;
        TPanel *panel_Connect;
        TLabel *label_Protocol;
        TComboBox *comboBox_Protocol;
        TPanel *panel_helperNumTxtBtn;
        TLabel *label_AddrBd;
        TEdit *textBox_AddrBd;
        TButton *button_AddrBd_Dec;
        TButton *button_AddrBd_Inc;
        TPanel *panel_comPort_TcpIp;
        TGroupBox *groupBox_ComPort;
        TLabel *label_ComPortS;
        TComboBox *comboBox_ComPorts;
        TButton *button_UpdateNumberOfComPortS;
        TEdit *label_ComPortsCount;
        TGroupBox *groupBox_TcpIp;
        TLabel *label_IP_Addr;
        TLabel *label_TCP_Port;
        TEdit *textBox_IP_Addr;
        TEdit *textBox_TCP_Port;
        TButton *button_StartStop;
        TPanel *label_Hint;
        TGroupBox *GroupBox_Rate;
        TGroupBox *GroupBox2;
        TGroupBox *GroupBox_EEPROM;
        TGroupBox *GroupBox_VerPo;
        TEdit *Edit_VerPo0;
        TEdit *Edit_VerPo1;
        TEdit *Edit_VerPo2;
        TEdit *Edit_VerPo3;
        TScrollBox *ScrollBox_MainParam;
        TPanel *Panel_EEPROM_Description;
        TPanel *Panel_EEPROM_Code;
        TPanel *Panel_EEPROM_Value;
        TPanel *Panel_EEPROM_Unit;
        TPanel *Panel_IndAddrZad_0;
        TPanel *Panel_IndAddrZad_1;
        TEdit *Edit_IndAddrZad;
        TPanel *Panel_indAddrZad_3;
        TPanel *Panel_GroupAdrZad_0;
        TPanel *Panel_GroupAdrZad_1;
        TEdit *Edit_GroupAdrZad;
        TPanel *Panel_GroupAdrZad_3;
        TPanel *Panel_DnuZad_0;
        TEdit *Edit_DnuZad_Code;
        TMaskEdit *Edit_DnuZad_Value;
        TEdit *Edit_DnuZad_3;
        TPanel *Panel_VoltageHiZad_0;
        TEdit *Edit_VoltageHiZad_Code;
        TComboBox *comboBox_VoltageHiZad_Value;
        TEdit *Edit_VoltageHiZad_3;
        TPanel *Panel_WidthPwmZad_0;
        TEdit *Edit_WidthPwmZad;
        TPanel *Panel_WidthPwmZad_2;
        TEdit *Edit_WidthPwmZad_3;
        TPanel *Panel_OffsetPwmZad_0;
        TEdit *Edit_OffsetPwmZad;
        TPanel *Panel_OffsetPwmZad_2;
        TEdit *Edit_OffsetPwmZad_3;
        TPanel *Panel2;
        TEdit *Edit16;
        TPanel *Panel6;
        TEdit *Edit17;
        TPanel *Panel16;
        TPanel *Panel18;
        TEdit *Edit22;
        TEdit *Edit15;
        TButton *button_WriteToEeprom;
        TButton *btnDefaults;
        TButton *btnPwmAuto;
        TPanel *Panel_rate_Description;
        TPanel *Panel_rate_Code;
        TPanel *Panel_rate_Value;
        TPanel *Panel_rate_Unit;
        TPanel *IndAdrPanel;
        TPanel *EmptyPanel01;
        TEdit *IndAdrEdit;
        TPanel *EmptyPanel07;
        TPanel *GrpAdrPanel;
        TPanel *EmptyPanel02;
        TEdit *GrpAdrEdit;
        TPanel *EmptyPanel08;
        TPanel *TprPanel;
        TEdit *TprCodeEdit;
        TEdit *TprEdit;
        TEdit *TprUnitEdit;
        TPanel *DNUIPanel;
        TEdit *DNUICodeEdit;
        TEdit *Edit4;
        TEdit *DNUIUnitEdit;
        TPanel *UhiIPanel;
        TEdit *UhiICodeEdit;
        TEdit *Edit14;
        TEdit *UhiIUnitEdit;
        TPanel *Panel1;
        TEdit *Edit5;
        TEdit *Edit20;
        TEdit *Edit2;
        TPanel *Panel15;
        TEdit *Edit10;
        TEdit *Edit21;
        TEdit *Edit9;
        TPanel *Panel_ErrorConnectCount;
        TEdit *Edit_ErrorConnectCount;
        TGroupBox *GroupBox_ReverseLink;
        TRadioButton *RS1;
        TRadioButton *RS3;
        TLabel *Label3;
        TEdit *T_LimitEdit;
        TPanel *Count1Panel;
        TPanel *EmptyPanel04;
        TEdit *Count1Edit;
        TEdit *Count1UnitEdit;
        TPanel *SumCountPanel;
        TPanel *EmptyPanel05;
        TEdit *SumCountEdit;
        TEdit *SumCountUnitEdit;
        TPanel *TCountPanel;
        TPanel *EmptyPanel06;
        TEdit *TCountEdit;
        TEdit *TCountUnitEdit;
        TButton *SetResetButton;
        TButton *StartCountButton;
        TButton *btnSaveParam;
        TLabel *Label6;
        TButton *Button5;
        TScrollBox *ScrollBox_SettingsForModBus;
        TGroupBox *GroupBox_SettingsForModbus;
        TLabel *Label_3_01;
        TLabel *Label_3_02;
        TLabel *Label_3_03;
        TLabel *Label_3_04;
        TLabel *Label_3_05;
        TLabel *Label_3_06;
        TLabel *Label_3_07;
        TLabel *Label_3_08;
        TLabel *Label_3_09;
        TLabel *Label_3_10;
        TLabel *Label_3_11;
        TLabel *Label_3_12;
        TLabel *Label_3_13;
        TLabel *Label_3_14;
        TEdit *Edit_3_01;
        TEdit *Edit_3_02;
        TEdit *Edit_3_03;
        TEdit *Edit_3_04;
        TEdit *Edit_3_05;
        TEdit *Edit_3_06;
        TEdit *Edit_3_07;
        TEdit *Edit_3_08;
        TEdit *Edit_3_09;
        TEdit *Edit_3_10;
        TEdit *Edit_3_11;
        TEdit *Edit_3_12;
        TEdit *Edit_3_13;
        TEdit *Edit_3_14;
        TButton *Button_ModBus_Write;
        TButton *Button_ModBus_SetDef;
        void __fastcall button_StartStopClick(TObject *Sender);
        void __fastcall button_AddrBd_DecClick(TObject *Sender);
        void __fastcall button_AddrBd_IncClick(TObject *Sender);
        void __fastcall textBox_AddrBdChange(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall comboBox_ProtocolChange(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall textBox_IP_AddrChange(TObject *Sender);
        void __fastcall textBox_TCP_PortChange(TObject *Sender);
        void __fastcall button_UpdateNumberOfComPortSClick(
          TObject *Sender);
        void __fastcall comboBox_ComPortsChange(TObject *Sender);
        void __fastcall button_WriteToEepromClick(TObject *Sender);
private:	// User declarations
    void InitComponrnts();
     
    ActionSelf<> as_wrapShow;
    void WrapShow();

    ActionSelf<const char*> as_textBox_AddrBd_SetText;
    void TextBox_AddrBd_SetText(const char* text);

    ActionSelf<bool> as_setComPortProtEnabled;
    void SetComPortProtEnabled(bool comPortEnable);

    ActionSelf<const char*> as_label_HintSetText;
    void HintSetText(const char* text);

    ActionSelf<> as_clearAllComPortName;
    void ClearAllComPortName();

    ActionSelf<bool> as_setEnabledUpdateComPorts;
    void SetEnabledUpdateComPorts(bool enabled);

    ActionSelf<const char*, const char*> as_addComPortName;
    void AddComPortName(const char* comPortName, const char* comPortCount);

    ActionSelf<Protokol> as_setProtokolName;
    void SetProtokolName(Protokol protokolName);

    ActionSelf<const char*, const char*> as_setEndPoint;
    void SetEndPoint(const char* textIpAddr, const char* textTcpPort);

    ActionSelf<ConnectionStateInfo> as_SetConnectionState; // Отобразить изменения о состоянии соединения в ГИП
    void SetConnectionState(ConnectionStateInfo state);
    void ControlsAvailability(bool isEnabled);
    void ControlsAvailabilityInvert(bool isEnabled);


    ActionSelf<StartDataNewBd85*> as_DisplayStartData;
    void DisplayStartData( StartDataNewBd85* data );

    ActionSelf<const char*> as_DisplayCountConnectError;
    void DisplayCountConnectError(const char* text);

    ActionEvent<const char*> ev_textBox_AddrBd_Change;
    ActionEvent<> ev_button_AddrBd_DecClick;
    ActionEvent<> ev_button_AddrBd_IncClick;
    ActionEvent<> ev_button_StartStopClick;
    ActionEvent<Protokol> ev_comboBox_ProtocolChange;
    ActionEvent<const char*> ev_comboBox_ComPortsChange;
    ActionEvent<> ev_windowShow;
    ActionEvent<> ev_windowClose;
    ActionEvent<const char*> ev_textBox_IP_AddrChange;
    ActionEvent<const char*> ev_textBox_TCP_PortChange;
    ActionEvent<> ev_button_UpdateNumberOfComPortSClick;
    ActionEvent<> ev_button_WriteToEepromClick;

    HelperNumberTextBtn addrBdHelper;
    HelperConnectFourBdProt bdProtHelper;

public:		// User declarations
        __fastcall TWindowMainBd85(TComponent* Owner);

    void Destroy();
            
    ActionSelf<>* GetSelfShow();
    ActionEvent<>* GetEventFormShow();
    ActionEvent<>* GetEventFormClose();
    ActionSelf<StartDataNewBd85*>* GetSelfDisplayStartData();
    ActionSelf<const char*>* GetSelfDisplayErrors();

    HelperConnectFourBdProt* GetConnectFourBdProt();
};
//---------------------------------------------------------------------------
#endif
