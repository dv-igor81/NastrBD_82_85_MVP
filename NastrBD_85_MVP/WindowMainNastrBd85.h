//---------------------------------------------------------------------------
#ifndef WindowMainNastrBd85H
#define WindowMainNastrBd85H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
#include "ProtokolName_t.h"
#include "ConnectionStateInfo_t.h"
#include "IWindowMainBd85.h"
#include "ICodeValueTextBoxNumber.h"
//---------------------------------------------------------------------------
class TWindowMainBd85 : public TForm, public IWindowMainBd85
{
__published:	// IDE-managed Components
        TPageControl *PageControl_WindowBd85;
        TTabSheet *TabSheet_MainParam;
        TTabSheet *TabSheet_ModBusParam;
        TGroupBox *GroupBox_Rate;
        TGroupBox *GroupBox_EEPROM;
        TScrollBox *ScrollBox_MainParam;
        TPanel *Panel_IndAddrZad_0;
        TPanel *Panel_IndAddrZad_1;
        TEdit *Edit_IndAddrZad;
        TPanel *Panel_indAddrZad_3;
        TPanel *Panel_GroupAdrZad_0;
        TPanel *Panel_GroupAdrZad_1;
        TEdit *Edit_GroupAdrZad;
        TPanel *Panel_GroupAdrZad_3;
        TEdit *Edit_DnuZad_Code;
        TEdit *Edit_VoltageHiZad_Code;
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
        TButton *button_FromFile;
        TButton *button_Poisson;
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
        TEdit *Edit_DNU_Code;
        TEdit *Edit_VoltageHi_Code;
        TPanel *Panel_WidthPwm_0;
        TEdit *Edit_WidthPwm_Code;
        TEdit *Edit_WidthPwm_Value;
        TEdit *Edit_WidthPwm_3;
        TPanel *Panel_PeriodPwm_0;
        TEdit *Edit_PeriodPwm_Code;
        TEdit *Edit_PeriodPwm_Value;
        TEdit *Edit_PeriodPwm_3;
        TScrollBox *ScrollBox_SettingsForModBus;
        TGroupBox *GroupBox_SettingsForModbus;
        TLabel *Label_NumberOfBd;
        TLabel *Label_Exposition;
        TLabel *Label_MinimumCount;
        TLabel *Label_MaximumCount;
        TLabel *Label_LevelOfOverload;
        TLabel *Label_QuantityOfInterval;
        TLabel *Label_QuantityOfLook;
        TLabel *Label_LevelOfAlarm_1;
        TLabel *Label_LevelOfAlarm_2;
        TLabel *Label_LevelOfAlarm_3;
        TLabel *Label_Phon;
        TLabel *Label_DurationOfPhon;
        TLabel *Label_DurationOfAlarm;
        TLabel *Label_DurationOfVideo;
        TEdit *Edit_NumberOfBd;
        TEdit *Edit_Exposition;
        TEdit *Edit_MinimumCount;
        TEdit *Edit_MaximumCount;
        TEdit *Edit_LevelOfOverload;
        TEdit *Edit_QuantityOfInterval;
        TEdit *Edit_QuantityOfLook;
        TEdit *Edit_LevelOfAlarm_1;
        TEdit *Edit_LevelOfAlarm_2;
        TEdit *Edit_LevelOfAlarm_3;
        TEdit *Edit_Phon;
        TEdit *Edit_DurationOfPhon;
        TEdit *Edit_DurationOfAlarm;
        TEdit *Edit_DurationOfVideo;
        TButton *Button_ModBus_Write;
        TButton *Button_ModBus_SetDef;
        TPanel *Panel_Scaling_1;
        TLabel *Label_ChangeEEPROM;
        TLabel *Label_ChangeModBusEEPROM;
        TGroupBox *GroupBox_Automatic;
        TButton *Button_Shift05a;
        TButton *Button_chm18;
        //TScrollBox *ScrollBox_HideFewControls;
        TPanel *panel_Connect;
        TPanel *panel_comPort_TcpIp;
        TGroupBox *groupBox_ComPort;
        TLabel *label_ComPortS;
        TComboBox *comboBox_ComPorts;
        TButton *button_UpdateNumberOfComPortS;
        TEdit *label_ComPortsCount;
        TButton *button_StartStop;
        TPanel *label_Hint;
        TComboBox *comboBox_Protocol;
        TLabel *label_Protocol;
        TGroupBox *groupBox_TcpIp;
        TLabel *label_IP_Addr;
        TLabel *label_TCP_Port;
        TEdit *textBox_IP_Addr;
        TEdit *textBox_TCP_Port;
        TPanel *panel_helperNumTxtBtn;
        TLabel *label_AddrBd;
        TEdit *textBox_AddrBd;
        TButton *button_AddrBd_Dec;
        TButton *button_AddrBd_Inc;
        TGroupBox *GroupBox_VerPo;
        TPanel *Panel_ErrorConnectCount;
        TEdit *Edit_ErrorConnectCount;
        TGroupBox *GroupBox_ReverseLink;
        TRadioButton *radioButton_ArchOn;
        TRadioButton *radioButton_ArchOff;
        TBitBtn *BitBtn_ArchOnOffDisplay;
        TEdit *Edit_VerPo0;
        TEdit *Edit_VerPo1;
        TEdit *Edit_VerPo2;
        TEdit *Edit_VerPo3;
        TLabel *Label_VerPo;
        TPanel *Panel_EEPROM_Description;
        TPanel *Panel_EEPROM_Value;
        TPanel *Panel_EEPROM_Unit;
        TPanel *Panel_EEPROM_Code;
        TPanel *Panel_DnuZad_0;
        TPanel *Panel_VoltageHiZad_0;
        TMaskEdit *Edit_DnuZad_Value;
        TComboBox *comboBox_VoltageHiZad_Value;
        TEdit *Edit_DnuZad_3;
        TEdit *Edit_VoltageHiZad_3;
        TEdit *Edit_Scaling;
        TPanel *Panel_Scaling_0;
        TEdit *Edit_Scaling_3;
        TGroupBox *GroupBox_Scaling;
        TLabel *Label_TimeMetering;
        TEdit *Edit_TimeMeteringLimit;
        TPanel *Panel_MiddleSecondScaling_0;
        TEdit *Edit_MiddleSecondScaling;
        TEdit *Edit_MiddleSecondScaling_3;
        TPanel *Panel_TotalScaling_0;
        TEdit *Edit_TotalScaling;
        TEdit *Edit_TotalScaling_3;
        TPanel *Panel_TimeScaling_0;
        TEdit *Edit_TimeScaling;
        TEdit *Edit_TimeScaling_3;
        TButton *button_ClearScaling;
        TButton *button_StartStopScaling;
        TButton *button_SaveToFile;
        TButton *button_WriteToEeprom;
        TPanel *Panel_DNU_0;
        TEdit *Edit_DNU_Value;
        TEdit *Edit_DNU_3;
        TPanel *Panel_VoltageHi_0;
        TEdit *Edit_VoltageHi_Value;
        TEdit *Edit_VoltageHi_3;
        TTimer *Timer_DisplayErrors;
        void __fastcall button_StartStopClick(TObject *Sender);
        void __fastcall button_AddrBd_DecClick(TObject *Sender);
        void __fastcall button_AddrBd_IncClick(TObject *Sender);
        void __fastcall textBox_AddrBdChange(TObject *Sender);
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
        void __fastcall Edit_NumberOfBdChange(TObject *Sender);
        void __fastcall Edit_ExpositionChange(TObject *Sender);
        void __fastcall Edit_MinimumCountChange(TObject *Sender);
        void __fastcall Edit_LevelOfOverloadChange(TObject *Sender);
        void __fastcall Edit_QuantityOfIntervalChange(TObject *Sender);
        void __fastcall Edit_QuantityOfLookChange(TObject *Sender);
        void __fastcall Edit_LevelOfAlarm_1Change(TObject *Sender);
        void __fastcall Edit_LevelOfAlarm_2Change(TObject *Sender);
        void __fastcall Edit_LevelOfAlarm_3Change(TObject *Sender);
        void __fastcall Edit_PhonChange(TObject *Sender);
        void __fastcall Edit_DurationOfPhonChange(TObject *Sender);
        void __fastcall Edit_DurationOfAlarmChange(TObject *Sender);
        void __fastcall Edit_DurationOfVideoChange(TObject *Sender);
        void __fastcall Button_ModBus_SetDefClick(TObject *Sender);
        void __fastcall Button_ModBus_WriteClick(TObject *Sender);
        void __fastcall Edit_MaximumCountChange(TObject *Sender);
        void __fastcall PageControl_WindowBd85Change(TObject *Sender);
        void __fastcall button_FromFileClick(TObject *Sender);
        void __fastcall button_SaveToFileClick(TObject *Sender);
        void __fastcall button_PoissonClick(TObject *Sender);
        void __fastcall Button_chm18Click(TObject *Sender);
        void __fastcall Button_Shift05aClick(TObject *Sender);
        void __fastcall Edit_DnuZad_ValueChange(TObject *Sender);
        void __fastcall Edit_VoltageHiZad_CodeChange(TObject *Sender);
        void __fastcall Timer_DisplayErrorsTimer(TObject *Sender);
public:
    BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER( WM_SYSCOMMAND, TMessage, OnWMSysCommand );
    END_MESSAGE_MAP( TComponent )

    void __fastcall OnWMSysCommand( TMessage& Message );
private:	// User declarations
    void InitComponrnts();
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


    ActionEvent<int> ev_Text_DnuZadCodeChange;
    ActionEvent<const char*> ev_Text_DnuZadChange;

    ActionEvent<int> ev_Text_VoltageHiZadChange;
    ActionEvent<const char*> ev_Text_WidthPwmZadChange;
    ActionEvent<const char*> ev_Text_OffsetPwmZadChange;
    ActionEvent<const char*> ev_Text_PeriodPwmZadChange;
    ActionEvent<bool> ev_radioButton_ArchOnClick;
    ActionEvent<bool> ev_radioButton_ArchOffClick;
    //<<=== Запись в EEPROM

    //===>> Параметры ModBus
    ModBusEventContainerBd85 mbContainer;
    //<<=== Параметры ModBus

    //===>> Параметры из файла
    ActionEvent<> ev_button_FromFileClick;
    //<<=== Параметры из файла

    ActionEvent<> ev_button_SaveToFileClick;
    ActionEvent<> ev_button_PoissonClick;

    // Включить на время внимание к ошибкам
    void ErrorAttention();
    int _errAttenState; // Начальное состояние внимания к ошибкам связи
    int _errorAttentionCount; // Счетчик циклов состояний веимания к ошибкам
    const int _errorAttentionCountMax;
    bool _errAttenDisplay;

public:		// User declarations
        __fastcall TWindowMainBd85(TComponent* Owner);

    //===>> Вместо GetSelf
    void SetVerPoText(const char * text);
    void WrapShow();
    void WrapHide();
    //<<=== Вместо GetSelf

    void Destroy();
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
    ActionEvent<int>& GetEventTextDnuZadCodeChange();
    ActionEvent<const char*>& GetEventTextDnuZadChange();
    ActionEvent<int>& GetEventTextVoltageHiZadChange();
    ActionEvent<const char*>& GetEventTextWidthPwmZadChange();
    ActionEvent<const char*>& GetEventTextOffsetPwmZadChange();
    ActionEvent<const char*>& GetEventTextPeriodPwmZadChange();
    ActionEvent<bool>& GetEventRadioButtonArchOnClick();
    ActionEvent<bool>& GetEventRadioButtonArchOffClick();
    ActionSelf<bool>& GetSelfDisplayNotSaveChanges();
    //<<=== Запись в EEPROM

    //===>> Параметры ModBus
    ModBusEventContainerBd85 * GetModBusEventContainer();
    void DisplayModBusParamData( ModBusTextDataBd85 * data );
    void DisplayModBusNotSaveChanges( bool display ); // true --- отобразить несохраненные изменения
    //<<=== Параметры ModBus

    //===>> Параметры из файла
    ActionEvent<>& GetEventButtonFromFileClick();
    //<<=== Параметры из файла

    ActionEvent<>& GetEventButtonSaveToFileClick();
    ActionEvent<>& GetEventButtonPoissonClick();

    ICodeValueTextBoxNumber * _tbnDnuZad;
    // asp - Action Self Pointer
    ActionSelf<const char*> * asp_SetTextCodeDnuZad;
    ActionSelf<const char*> * asp_SetTextValueDnuZad;
    ActionSelf<int> * asp_SetCursorCodeDnuZad;
    ActionSelf<int> * asp_SetCursorValueDnuZad;

    void CreateAsp();
    void DestroyAsp();
    
    void SetTextCodeDnuZad(const char * txt);
    void SetTextValueDnuZad(const char * txt);
    void SetCursorCodeDnuZad(int pos);
    void SetCursorValueDnuZad(int pos);

    bool _notSetDnu;

    ICodeValueTextBoxNumber * _tbnVoltageHiZad;
    ActionSelf<const char*> * asp_SetTextCodeVoltageHiZad;
    ActionSelf<const char*> * asp_SetTextValueVoltageHiZad;
    ActionSelf<int> * asp_SetCursorCodeVoltageHiZad;
    ActionSelf<int> * asp_SetCursorValueVoltageHiZad;

    void SetTextCodeVoltageHiZad(const char * txt);
    void SetTextValueVoltageHiZad(const char * txt);
    void SetCursorCodeVoltageHiZad(int pos);
    void SetCursorValueVoltageHiZad(int pos);
    bool _notSetVoltageHi;
};
//---------------------------------------------------------------------------
#endif
