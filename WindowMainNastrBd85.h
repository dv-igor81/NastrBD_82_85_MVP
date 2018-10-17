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
//---------------------------------------------------------------------------
class TWindowMainBd85 : public TForm, public IWindowMainBd85
{
__published:	// IDE-managed Components
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
    ActionSelf<>* GetSelfShow();
    ActionEvent<>* GetEventFormShow();
    ActionEvent<>* GetEventFormClose();

    HelperConnectFourBdProt* GetConnectFourBdProt();
};
//---------------------------------------------------------------------------
#endif
