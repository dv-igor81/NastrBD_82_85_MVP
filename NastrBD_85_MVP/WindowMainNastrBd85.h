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
#include "IWindowMainBd85.h"
#include <ComCtrls.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TWindowMainBd85 : public TForm, public IWindowMainBd85
{
__published:	// IDE-managed Components
        TPageControl *PageControl_WindowBd85;
        TTabSheet *TabSheet_Main;
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
        TGroupBox *DataFromDetGroupBox;
        TEdit *IndAdrEdit;
        TPanel *IndAdrPanel;
        TPanel *ParamColPanel;
        TPanel *GrpAdrPanel;
        TPanel *CodeColPanel;
        TEdit *GrpAdrEdit;
        TPanel *TprPanel;
        TPanel *UhiIPanel;
        TPanel *DNUIPanel;
        TEdit *TprCodeEdit;
        TEdit *UhiICodeEdit;
        TEdit *DNUICodeEdit;
        TPanel *ValueCodePanel;
        TEdit *TprEdit;
        TPanel *UnitPanel;
        TEdit *TprUnitEdit;
        TEdit *UhiIUnitEdit;
        TEdit *DNUIUnitEdit;
        TPanel *EmptyPanel01;
        TPanel *EmptyPanel02;
        TPanel *EmptyPanel07;
        TPanel *EmptyPanel08;
        TPanel *Panel1;
        TEdit *Edit2;
        TPanel *Panel15;
        TEdit *Edit9;
        TPanel *Panel16;
        TPanel *Panel18;
        TEdit *Edit15;
        TGroupBox *GroupBox2;
        TLabel *Label3;
        TPanel *SumCountPanel;
        TPanel *TCountPanel;
        TPanel *EmptyPanel05;
        TPanel *EmptyPanel06;
        TEdit *SumCountEdit;
        TEdit *TCountEdit;
        TEdit *SumCountUnitEdit;
        TEdit *TCountUnitEdit;
        TEdit *T_LimitEdit;
        TButton *SetResetButton;
        TButton *StartCountButton;
        TPanel *Count1Panel;
        TPanel *EmptyPanel04;
        TEdit *Count1Edit;
        TEdit *Count1UnitEdit;
        TButton *btnSaveParam;
        TGroupBox *DataForDetBox;
        TMaskEdit *SetDNUEdit;
        TPanel *SetIndAdrPanel;
        TPanel *SetGrpAdrPanel;
        TPanel *SetDNUPanel;
        TPanel *SetUhiPanel;
        TPanel *SetParamColPanel;
        TPanel *SetCodeColPanel;
        TPanel *SetValueColPanel;
        TEdit *SetIndAdrEdit;
        TEdit *SetGrpAdrEdit;
        TEdit *SetDNUCodeEdit;
        TEdit *SetUhiCodeEdit;
        TPanel *EmptyPanel09;
        TPanel *EmptyPanel10;
        TPanel *Panel3;
        TPanel *Panel4;
        TPanel *Panel5;
        TEdit *Edit1;
        TEdit *Edit3;
        TPanel *Panel12;
        TPanel *Panel28;
        TEdit *Edit6;
        TEdit *Edit18;
        TPanel *Panel14;
        TPanel *Panel29;
        TEdit *Edit8;
        TEdit *Edit19;
        TGroupBox *GroupBox_ReverseLink;
        TRadioButton *RS1;
        TRadioButton *RS3;
        TPanel *Panel2;
        TEdit *Edit16;
        TPanel *Panel6;
        TEdit *Edit17;
        TButton *btnDefaults;
        TComboBox *SetUhiEdit;
        TGroupBox *GroupBox_VerPo;
        TLabel *Label6;
        TLabel *Label4;
        TBitBtn *ARCH_Con;
        TEdit *Edit7;
        TEdit *Edit11;
        TEdit *Edit12;
        TEdit *Edit13;
        TButton *Button5;
        TButton *btnPwmAuto;
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
        TEdit *Edit5;
        TEdit *Edit10;
        TEdit *Edit4;
        TEdit *Edit14;
        TEdit *Edit20;
        TEdit *Edit21;
        TEdit *Edit22;
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

    ActionEvent<const char*> ev_textBox_AddrBd_Change;
    ActionEvent<> ev_button_AddrBd_DecClick;
    ActionEvent<> ev_button_AddrBd_IncClick;
    ActionEvent<> ev_button_StartStopClick;
    ActionEvent<Protokol> ev_comboBox_ProtocolChange;
    ActionEvent<> ev_windowShow;
    ActionEvent<> ev_windowClose;
    ActionEvent<const char*> ev_textBox_IP_AddrChange;
    ActionEvent<const char*> ev_textBox_TCP_PortChange;
    ActionEvent<> ev_button_UpdateNumberOfComPortSClick;

    HelperNumberTextBtn addrBdHelper;
    HelperConnectFourBdProt bdProtHelper;

public:		// User declarations
        __fastcall TWindowMainBd85(TComponent* Owner);

    void Destroy();
            
    ActionSelf<>* GetSelfShow();
    ActionEvent<>* GetEventFormShow();
    ActionEvent<>* GetEventFormClose();

    HelperConnectFourBdProt* GetConnectFourBdProt();
};
//---------------------------------------------------------------------------
#endif
