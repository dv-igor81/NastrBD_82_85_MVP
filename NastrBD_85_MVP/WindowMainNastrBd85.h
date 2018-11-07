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
#include "ProtokolName_t.h"
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
        TGroupBox *GroupBox_Scaling;
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
        TPanel *Panel_PeriodPwmZad_0;
        TEdit *Edit_PeriodPwmZad;
        TPanel *Panel_PeriodPwmZad_2;
        TEdit *Edit_PeriodPwmZad_3;
        TButton *button_WriteToEeprom;
        TButton *btnDefaults;
        TButton *btnPwmAuto;
        TPanel *Panel_rate_Description;
        TPanel *Panel_rate_Code;
        TPanel *Panel_rate_Value;
        TPanel *Panel_rate_Unit;
        TPanel *Panel_IndAddr_0;
        TPanel *Panel_IndAddr_1;
        TEdit *Edit_IndAddr;
        TPanel *Panel_IndAddr_3;
        TPanel *Panel_GroupAdr_0;
        TPanel *Panel_GroupAdr_1;
        TEdit *Edit_GroupAdr;
        TPanel *Panel_GroupAdr_3;
        TPanel *Panel_Temperature_0;
        TEdit *Edit_Temperature_Code;
        TEdit *Edit_Temperature_Value;
        TEdit *Edit_Temperature_3;
        TPanel *Panel_DNU_0;
        TEdit *Edit_DNU_Code;
        TEdit *Edit_DNU_Value;
        TEdit *Edit_DNU_3;
        TPanel *Panel_VoltageHi_0;
        TEdit *Edit_VoltageHi_Code;
        TEdit *Edit_VoltageHi_Value;
        TEdit *Edit_VoltageHi_3;
        TPanel *Panel_WidthPwm_0;
        TEdit *Edit_WidthPwm_Code;
        TEdit *Edit_WidthPwm_Value;
        TEdit *Edit_WidthPwm_3;
        TPanel *Panel_PeriodPwm_0;
        TEdit *Edit_PeriodPwm_Code;
        TEdit *Edit_PeriodPwm_Value;
        TEdit *Edit_PeriodPwm_3;
        TPanel *Panel_ErrorConnectCount;
        TEdit *Edit_ErrorConnectCount;
        TGroupBox *GroupBox_ReverseLink;
        TRadioButton *radioButton_ArchOn;
        TRadioButton *radioButton_ArchOff;
        TLabel *Label_TimeMetering;
        TEdit *Edit_TimeMeteringLimit;
        TPanel *Panel_MiddleSecondScaling_0;
        TPanel *Panel_MiddleSecondScaling_1;
        TEdit *Edit_MiddleSecondScaling;
        TEdit *Edit_MiddleSecondScaling_3;
        TPanel *Panel_TotalScaling_0;
        TPanel *Panel_TotalScaling_1;
        TEdit *Edit_TotalScaling;
        TEdit *Edit_TotalScaling_3;
        TPanel *Panel_TimeScaling_0;
        TPanel *Panel_TimeScaling_1;
        TEdit *Edit_TimeScaling;
        TEdit *Edit_TimeScaling_3;
        TButton *button_ClearScaling;
        TButton *button_StartStopScaling;
        TButton *button_SaveToFile;
        TLabel *Label_VerPo;
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
        TPanel *Panel_Scaling_0;
        TPanel *Panel_Scaling_1;
        TEdit *Edit_Scaling;
        TEdit *Edit_Scaling_3;
        TLabel *Label_ChangeEEPROM;
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
        void __fastcall button_StartStopScalingClick(TObject *Sender);
        void __fastcall button_ClearScalingClick(TObject *Sender);
        void __fastcall Edit_IndAddrZadChange(TObject *Sender);
        void __fastcall Edit_GroupAdrZadChange(TObject *Sender);
        void __fastcall Edit_DnuZad_CodeChange(TObject *Sender);
        void __fastcall Edit_WidthPwmZadChange(TObject *Sender);
        void __fastcall Edit_OffsetPwmZadChange(TObject *Sender);
        void __fastcall Edit_PeriodPwmZadChange(TObject *Sender);
        void __fastcall comboBox_VoltageHiZad_ValueChange(TObject *Sender);
        void __fastcall radioButton_ArchOnClick(TObject *Sender);
        void __fastcall radioButton_ArchOffClick(TObject *Sender);
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

    ActionSelf<ProtokolName> as_setProtokolName;
    void SetProtokolName(ProtokolName protokolName);

    ActionSelf<const char*, const char*> as_setEndPoint;
    void SetEndPoint(const char* textIpAddr, const char* textTcpPort);

    ActionSelf<ConnectionStateInfo> as_SetConnectionState; // Отобразить изменения о состоянии соединения в ГИП
    void SetConnectionState(ConnectionStateInfo state);
    void ControlsAvailability(bool isEnabled);
    void ControlsAvailabilityInvert(bool isEnabled);


    ActionSelf<StartDataNewBd85*> as_DisplayStartData;
    void DisplayStartData( StartDataNewBd85* data );

    ActionSelf<IterDataNewBd85*> as_DisplayIterData;
    void DisplayIterData( IterDataNewBd85* data );

    ActionSelf<ScalingDataNewBd85*> as_DisplayScalingData;
    void DisplayScalingData( ScalingDataNewBd85* data );

    ActionSelf<const char*> as_DisplayCountConnectError;
    void DisplayCountConnectError(const char* text);

    ActionSelf<bool> as_DisplayNotSaveChanges;
    void DisplayNotSaveChanges(bool);

    ActionEvent<const char*> ev_textBox_AddrBd_Change;
    ActionEvent<> ev_button_AddrBd_DecClick;
    ActionEvent<> ev_button_AddrBd_IncClick;
    ActionEvent<> ev_button_StartStopClick;
    ActionEvent<ProtokolName> ev_comboBox_ProtocolChange;
    ActionEvent<const char*> ev_comboBox_ComPortsChange;
    ActionEvent<> ev_windowShow;
    ActionEvent<> ev_windowClose;
    ActionEvent<const char*> ev_textBox_IP_AddrChange;
    ActionEvent<const char*> ev_textBox_TCP_PortChange;
    ActionEvent<> ev_button_UpdateNumberOfComPortSClick;

    HelperNumberTextBtn addrBdHelper;
    HelperConnectFourBdProt bdProtHelper;

    ActionEvent<const char*> ev_button_StartStopScalingClick;
    ActionEvent<> ev_button_ClearScalingClick;
    //===>> Запись в EEPROM
    ActionEvent<> ev_button_WriteToEepromClick;
    ActionEvent<const char*> ev_Text_IndAddrZadChange;
    ActionEvent<const char*> ev_Text_GroupAdrZadChange;
    ActionEvent<const char*> ev_Text_DnuZadCodeChange;
    ActionEvent<const char*> ev_Text_VoltageHiZadChange;
    ActionEvent<const char*> ev_Text_WidthPwmZadChange;
    ActionEvent<const char*> ev_Text_OffsetPwmZadChange;
    ActionEvent<const char*> ev_Text_PeriodPwmZadChange;
    ActionEvent<bool> ev_radioButton_ArchOnClick;
    ActionEvent<bool> ev_radioButton_ArchOffClick;
    //<<=== Запись в EEPROM

public:		// User declarations
        __fastcall TWindowMainBd85(TComponent* Owner);

    void Destroy();
            
    ActionSelf<>* GetSelfShow();
    ActionEvent<>* GetEventFormShow();
    ActionEvent<>* GetEventFormClose();
    ActionSelf<StartDataNewBd85*>* GetSelfDisplayStartData();
    ActionSelf<const char*>* GetSelfDisplayErrors();
    ActionSelf<IterDataNewBd85*>& GetSelfDisplayIterData();
    HelperConnectFourBdProt* GetConnectFourBdProt();

    ActionEvent<const char*>* GetEventButtonStartStopScalingClick();
    ActionSelf<ScalingDataNewBd85*>& GetSelfDisplayScalingData();
    ActionEvent<>& GetEventButtonClearScalingClick();

    //===>> Запись в EEPROM
    ActionEvent<>& GetEventButtonWriteToEepromClick();
    ActionEvent<const char*>& GetEventTextIndAddrZadChange();
    ActionEvent<const char*>& GetEventTextGroupAdrZadChange();
    ActionEvent<const char*>& GetEventTextDnuZadCodeChange();
    ActionEvent<const char*>& GetEventTextVoltageHiZadChange();
    ActionEvent<const char*>& GetEventTextWidthPwmZadChange();
    ActionEvent<const char*>& GetEventTextOffsetPwmZadChange();
    ActionEvent<const char*>& GetEventTextPeriodPwmZadChange();
    ActionEvent<bool>& GetEventRadioButtonArchOnClick();
    ActionEvent<bool>& GetEventRadioButtonArchOffClick();
    ActionSelf<bool>& GetSelfDisplayNotSaveChanges();
    //<<=== Запись в EEPROM
};
//---------------------------------------------------------------------------
#endif
