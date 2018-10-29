//---------------------------------------------------------------------------
#ifndef Unit_82_Form_StartH
#define Unit_82_Form_StartH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CSPIN.h"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
//#include "Unit_82_RSProtokol.h"
#include "RSProtokol.h"
#include "Protokol_t.h"
//---------------------------------------------------------------------------
// DIA INC
#include <Clipbrd.hpp>
#include <axctrls.hpp>
#include <Jpeg.hpp>
#include <ScktComp.hpp>
#include <Dialogs.hpp>

class TForm_82_Start : public TForm
{
  private:
    void __fastcall OnWMSysCommand( TMessage& aMsg );
  public:
    BEGIN_MESSAGE_MAP
      MESSAGE_HANDLER( WM_SYSCOMMAND, TMessage, OnWMSysCommand );
    END_MESSAGE_MAP( TComponent )

__published:	// IDE-managed Components
        TPageControl *PageControl_ModBus_Settings;
        TTabSheet *TabSheet_Main;
        TScrollBox *ScrollBox_Tab1_Scrolling;
        TTabSheet *TabSheet_SetSettings;
        TTabSheet *TabSheet_Reports;
        TScrollBox *ScrollBox_Tab2_Scrolling;
        TScrollBox *ScrollBox_Tab4_Scrolling;
        TButton *Button_Clear_Memo_Err;
        TGroupBox *GroupBox_For_Prints_Errors;
        TMemo *Memo_For_Print_Errors;
        TGroupBox *GroupBox_InfoFromBD_Display;
        TPanel *Panel_Col1_Row1;
        TPanel *Panel_Col2_Row1;
        TPanel *Panel_Col3_Row1;
        TPanel *Panel_Col4_Row1;
        TPanel *Panel_Col4_Row2;
        TPanel *Panel_Col1_Row2;
        TPanel *Panel_Col4_Row3;
        TPanel *Panel_Col2_Row3;
        TPanel *Panel_Col1_Row3;
        TPanel *Panel_Col1_Row4;
        TPanel *Panel_Col1_Row5;
        TPanel *Panel_Col1_Row6;
        TPanel *Panel_Col1_Row7;
        TPanel *Panel_Col1_Row9;
        TPanel *Panel_Col3_Row10;
        TPanel *Panel_Col1_Row10;
        TPanel *Panel_Col1_Row11;
        TPanel *Panel_Col1_Row12;
        TPanel *Panel_Col2_Row13;
        TPanel *Panel_Col1_Row13;
        TPanel *Panel_Col1_Row8;
        TEdit *Edit_Col2_Row4;
        TEdit *Edit_Col2_Row5;
        TEdit *Edit_Col2_Row6;
        TEdit *Edit_Col2_Row7;
        TEdit *Edit_Col2_Row8;
        TEdit *Edit_Col2_Row9;
        TEdit *Edit_Col2_Row10;
        TEdit *Edit_Col2_Row11;
        TEdit *Edit_Col2_Row12;
        TEdit *Edit_Col3_Row2;
        TEdit *Edit_Col3_Row4;
        TEdit *Edit_Col3_Row5;
        TEdit *Edit_Col3_Row6;
        TEdit *Edit_Col3_Row7;
        TEdit *Edit_Col3_Row8;
        TEdit *Edit_Col3_Row9;
        TEdit *Edit_Col3_Row11;
        TEdit *Edit_Col3_Row12;
        TEdit *Edit_Col3_Row13;
        TEdit *Edit_Col4_Row4;
        TEdit *Edit_Col4_Row5;
        TEdit *Edit_Col4_Row6;
        TEdit *Edit_Col4_Row7;
        TEdit *Edit_Col4_Row8;
        TEdit *Edit_Col4_Row9;
        TEdit *Edit_Col4_Row10;
        TEdit *Edit_Col4_Row11;
        TEdit *Edit_Col4_Row12;
        TEdit *Edit_Col4_Row13;
        TPanel *Panel_Col2_Row2;
        TGroupBox *GroupBox_WriteSettings;
        TPanel *Panel_2_Col1_Row1;
        TPanel *Panel_2_Col2_Row1;
        TPanel *Panel_2_Col3_Row1;
        TPanel *Panel_2_Col4_Row1;
        TPanel *Panel_2_Col4_Row2;
        TPanel *Panel_2_Col1_Row2;
        TPanel *Panel_2_Col4_Row3;
        TPanel *Panel_2_Col2_Row3;
        TPanel *Panel_2_Col1_Row3;
        TPanel *Panel_2_Col1_Row4;
        TPanel *Panel_2_Col1_Row5;
        TPanel *Panel_2_Col1_Row6;
        TPanel *Panel_2_Col1_Row7;
        TPanel *Panel_2_Col1_Row9;
        TPanel *Panel_2_Col3_Row10;
        TPanel *Panel_2_Col1_Row10;
        TPanel *Panel_2_Col1_Row11;
        TPanel *Panel_2_Col1_Row12;
        TPanel *Panel_2_Col1_Row13;
        TPanel *Panel_2_Col1_Row8;
        TEdit *Edit_2_Col2_Row4;
        TEdit *Edit_2_Col2_Row5;
        TEdit *Edit_2_Col2_Row6;
        TEdit *Edit_2_Col2_Row7;
        TEdit *Edit_2_Col2_Row8;
        TEdit *Edit_2_Col2_Row9;
        TEdit *Edit_2_Col2_Row10;
        TEdit *Edit_2_Col3_Row2;
        TEdit *Edit_2_Col3_Row3;
        TEdit *Edit_2_Col3_Row4;
        TEdit *Edit_2_Col3_Row5;
        TEdit *Edit_2_Col3_Row11;
        TEdit *Edit_2_Col3_Row12;
        TEdit *Edit_2_Col3_Row13;
        TEdit *Edit_2_Col4_Row6;
        TEdit *Edit_2_Col4_Row7;
        TEdit *Edit_2_Col4_Row8;
        TEdit *Edit_2_Col4_Row9;
        TEdit *Edit_2_Col4_Row10;
        TEdit *Edit_2_Col4_Row12;
        TEdit *Edit_2_Col4_Row13;
        TPanel *Panel_2_Col2_Row2;
        TEdit *Edit_2_Col2_4_Row_14;
        TPanel *Panel_2_Col1_Row14;
        TPanel *Panel_2_Col3_Row9;
        TPanel *Panel_2_Col3_Row8;
        TPanel *Panel_2_Col3_Row7;
        TPanel *Panel_2_Col3_Row6;
        TPanel *Panel_2_Col4_Row11;
        TPanel *Panel_2_Col2_Row11;
        TButton *Button_2_Col4_Row6_10;
        TGroupBox *GroupBox_ReadSettings;
        TLabel *LabelAddtFrom;
        TLabel *LabelAddrTo;
        TButton *ButtonSearch;
        TMemo *Memo_SkanBD;
        TButton *Button_Clear_Memo_Scan;
        TButton *Button_SaveAddr;
        TGroupBox *GroupBox_ARCH;
        TRadioButton *RadioButton_ARCH1;
        TRadioButton *RadioButton_ARCH2;
        TRadioButton *RadioButton_ARCH3;
        TCheckBox *CheckBox_Diod;
        TGroupBox *GroupBox_InfoFromBD_Ver;
        TLabel *Label_VerProshivki;
        TEdit *Edit_Ver04;
        TEdit *Edit_Ver03;
        TEdit *Edit_Ver02;
        TEdit *Edit_Ver01;
        TGroupBox *GroupBox_InfoFromBD_SetParam;
        TLabel *Label_AddrBD;
        TCheckBox *CheckBox_Diskr;
        TCSpinEdit *SpinEdit_ForSaveAddr;
        TCSpinEdit *SpinEdit_AddrBD;
        TCSpinEdit *SpinEdit_Begin;
        TCSpinEdit *SpinEdit_End;
        TStringGrid *StringGrid1;
        TCheckBox *CheckBox_Proshivka;
        TGroupBox *GroupBox_InfoFromBD_AutoTesting;
        TLabel *Label_BD01;
        TLabel *Label_BD02;
        TLabel *Label_BD03;
        TLabel *Label_BD04;
        TLabel *Label_BD05;
        TLabel *Label_BD06;
        TLabel *Label_BD07;
        TLabel *Label_BD08;
        TButton *Button_Start;
        TCheckBox *CheckBox_Vybor_BD01;
        TCheckBox *CheckBox_Vybor_BD02;
        TCheckBox *CheckBox_Vybor_BD03;
        TCheckBox *CheckBox_Vybor_BD04;
        TCheckBox *CheckBox_Vybor_BD08;
        TCheckBox *CheckBox_Vybor_BD07;
        TCheckBox *CheckBox_Vybor_BD06;
        TCheckBox *CheckBox_Vybor_BD05;
        TRadioGroup *RadioGroup_Povtor;
        TCheckBox *CheckBox_All;
        TButton *Button_Imp2sek;
        TStatusBar *StatusBar1;
        TTimer *Timer1;
        TTimer *Timer2;
        TButton *Button_OpenBD_msek;
        TLabel *Label_sek;
        TCSpinEdit *SpinEdit_Sek;
        TCSpinEdit *SpinEditLptAddr;
        TLabel *LabelLptAddr;
        TButton *ButtonSetLptAddr;
        TTabSheet *TabSheet_Modbus;
        TScrollBox *ScrollBox_Tab3_Scrolling;
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
        TEdit *Edit_3_15;        

        TButton *Button_ModBus_Write;
        TButton *Button_ModBus_SetDef;
        TButton *Button_OpenBD;
        TCheckBox *CheckBox_auto;
        TCheckBox *CheckBox_DAuto;
        TEdit *Edit_Col3_Row3;
        TRadioGroup *RadioGroup_KOD;
        TButton *Button_ARCH;
        TButton *Button_Puason;
        TButton *Button_WriteToBD;
        TComboBox *ComboBox_NomBD;
        TLabel *Label_NomBD;
        TLabel *Label_bit7;
        TPanel *Panel_bit7;
        TPanel *Panel_bit7_2;
        TLabel *Label_bit7_2;
        TEdit *Edit_SSP_bin;
        TEdit *Edit_SSP_hex;
        TLabel *Label_SSP;
        TRadioGroup *RadioGroup_VyborProtokola;
        TGroupBox *GroupBox_ComPort;
        TLabel *Label_NomComPort;
        TLabel *Label_UpdateComPorts;
        TButton *Button_UpdateComPortsList;
        TComboBox *ComboBox_NomComPort;
        TButton *Button_Out32;
        TButton *Button_Inp32;
        TEdit *Edit_IPAddr;
        TEdit *Edit_IPPort;
        TLabel *Label_Imp2sek;
        TLabel *Label_Start;
        TGroupBox *GroupBox_For_Metro;
        TCheckBox *CheckBox_Enabled_Write_TCP;
        TCheckBox *CheckBox_Image;
        TSaveDialog *SaveDialog1;
        TRichEdit *RichEdit_SaveLogToFile;
        TMemo *Memo_SaveLogToFile;
        TButton *Button_Spectr;
        TButton *Button_Image;
        TEdit *Edit_StantsiyaMetro;
        TLabel *Label_StantsiyaMetro;
        TButton *Button_ToComment;

        TLabel *Label_3_15;
        TBitBtn *BitBtn_ARCH;
        TLabel *Label_arch;
        TLabel *Label_uch_sv;
        TBitBtn *BitBtn_Uch_sv;
        TButton *Button_P3_7_Set;
        TButton *Button_P3_7_Reset;
        TGroupBox *GroupBox_TCP;
        TCheckBox *CheckBox_speed;
        TButton *Button_SaveToFile;
        TGroupBox *GroupBox_UsredSchet;
        TLabel *Label_time_izm;
        TLabel *Label_time_izm_2;
        TButton *Button_Set_Reset;
        TPanel *Panel_3_Col1_Row1;
        TPanel *Panel_3_Col2_Row3;
        TEdit *Edit_3_Col3_Row2;
        TEdit *Edit_3_Col4_Row1;
        TPanel *Panel_3_Col1_Row2;
        TPanel *Panel_3_Col2_Row2;
        TEdit *Edit_3_Col3_Row1;
        TEdit *Edit_3_Col4_Row2;
        TPanel *Panel_3_Col1_Row3;
        TPanel *Panel_3_Col2_Row1;
        TEdit *Edit_3_Col3_Row3;
        TEdit *Edit_3_Col4_Row3;
        TButton *Button_Sum_Schet;
        TCSpinEdit *CSpinEdit_time_izm;
        TEdit *Edit_KolTik;
        TLabel *Label_KolTik;
        TBitBtn *BitBtn_P37SetReset;
        TButton *Button_P37SetReset;
        TTimer *Timer3;
        TButton *Button_Plus;
        TButton *Button_Minus;
        TPanel *Panel_2_Col2_Row12;
        TPanel *Panel_2_Col2_Row13;
        TCheckBox *CheckBox_auto_0_81;
        TPanel *Panel_MoxaSettingsDisplay;
        TCheckBox *CheckBox_DAuto_Standart;
        TCheckBox *CheckBox_DAuto_Shirokie;
        TCheckBox *CheckBox_DAuto_Rengen;


        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ComboBox_NomBDChange(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Button_StartClick(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
        void __fastcall RadioGroup_VyborProtokolaClick(TObject *Sender);
        void __fastcall RadioGroup_PovtorClick(TObject *Sender);
        void __fastcall CheckBox_AllClick(TObject *Sender);
        void __fastcall Button_OpenBD_msekClick(TObject *Sender);
        void __fastcall Button_WriteToBDClick(TObject *Sender);
        void __fastcall Edit_2_Col3_Row4Change(TObject *Sender);
        void __fastcall Edit_2_Col3_Row5Change(TObject *Sender);
        void __fastcall RadioGroup_KODClick(TObject *Sender);
        void __fastcall Edit_2_Col2_Row4Change(TObject *Sender);
        void __fastcall Edit_2_Col2_Row5Change(TObject *Sender);
        void __fastcall Edit_2_Col3_Row12Change(TObject *Sender);
        void __fastcall Edit_2_Col3_Row13Change(TObject *Sender);
        //==\\void __fastcall Edit_2_Col2_Row12Change(TObject *Sender);
        //==\\void __fastcall Edit_2_Col2_Row13Change(TObject *Sender);
        void __fastcall Edit_2_Col2_Row7Change(TObject *Sender);
        void __fastcall Button_Clear_Memo_ScanClick(TObject *Sender);
        void __fastcall CheckBox_DiskrClick(TObject *Sender);
        void __fastcall Button_2_Col4_Row4_5Click(TObject *Sender);
        void __fastcall Button_2_Col4_Row6_10Click(TObject *Sender);
        void __fastcall CheckBox_autoClick(TObject *Sender);
        void __fastcall CheckBox_DAutoClick(TObject *Sender);
        void __fastcall Button_Clear_Memo_ErrClick(TObject *Sender);
        void __fastcall ButtonSearchClick(TObject *Sender);
        void __fastcall Button_UpdateComPortsListClick(TObject *Sender);
        void __fastcall Button_SaveAddrClick(TObject *Sender);
        void __fastcall Button_OpenBDClick(TObject *Sender);
        void __fastcall Button_PuasonClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ButtonSetLptAddrClick(TObject *Sender);
        void __fastcall PageControl_ModBus_SettingsChange(TObject *Sender);
        void __fastcall Button_ModBus_WriteClick(TObject *Sender);
        void __fastcall Button_ModBus_SetDefClick(TObject *Sender);
        void __fastcall RadioButton_ARCH1Click(TObject *Sender);
        void __fastcall RadioButton_ARCH2Click(TObject *Sender);
        void __fastcall RadioButton_ARCH3Click(TObject *Sender);
        void __fastcall CheckBox_DiodClick(TObject *Sender);
        void __fastcall Button_ARCHClick(TObject *Sender);
        void __fastcall Button_Sum_SchetClick(TObject *Sender);
        void __fastcall Button_Set_ResetClick(TObject *Sender);
        void __fastcall Button_Out32Click(TObject *Sender);

        //!void __fastcall CheckBox_TCPClick(TObject *Sender);
        void __fastcall ComPort_Or_TcpIp(bool comPortEnabled);

        void __fastcall Button_Imp2sekClick(TObject *Sender);
        void __fastcall CheckBox_speedClick(TObject *Sender);
        void __fastcall CheckBox_Enabled_Write_TCPClick(TObject *Sender);
        void __fastcall Button_SaveToFileClick(TObject *Sender);
        void __fastcall Button_P3_7_SetClick(TObject *Sender);
        void __fastcall Button_P3_7_ResetClick(TObject *Sender);
        void __fastcall Button_P37SetResetMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Button_P37SetResetMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Button_SpectrClick(TObject *Sender);
        void __fastcall Button_ImageClick(TObject *Sender);
        void __fastcall Button_ToCommentClick(TObject *Sender);
        void __fastcall BitBtn_P37SetResetMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall BitBtn_P37SetResetMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Timer3Timer(TObject *Sender);
        void __fastcall Button_PlusClick(TObject *Sender);
        void __fastcall Button_MinusClick(TObject *Sender);
        void __fastcall CheckBox_auto_0_81Click(TObject *Sender);
        void __fastcall CheckBox_DAuto_StandartClick(TObject *Sender);
        void __fastcall CheckBox_DAuto_ShirokieClick(TObject *Sender);
        void __fastcall CheckBox_DAuto_RengenClick(TObject *Sender);
        void __fastcall Edit_2_Col2_4_Row_14Change(TObject *Sender);
private:	// User declarations
  Protokol prtotType;
  int AutoPodbor_1_Un_2_U81;
  float m_fltU_temp;
  unsigned int m_iU_temp;
  float m_fltU0_temp;
  unsigned int m_iU0_temp;
  bool AutoPodborProverka();
  void AutoPodborStart();
  void AutoPodborEnd();

  // ���������� ��������� ��� � ��� (1 - ��������, 2 - �������, 3 - ������)
  void SetDnuAndDvuStart(int);

  //////////////////////////////////////////////////
  /// 0 - ������ ��� � ��� �� ������������
  /// 1 - �������� (��� - 0,154; ��� - 0,922)
  /// 2 - �������  (��� - 0,154; ��� - 5,499)
  /// 3 - ������   (��� - 0,400; ��� - 5,499)
  //////////////////////////////////////////////////
  bool DnuAndDvuMode;


  // ��������� ��������� ��� � ��� (����� ���� ������������� �������, ���� ����������� �� �����)
  void SetDnuAndDvuEnd();

  enum DIA_CONST { TimerInterval = 30 };

  bool bFlagKnopkaZapis;
  bool bFlagDE; // ���� ����������� ������ (� ����������� �� �������� ���-������)
  unsigned char IndAdr; // �������������� ����� ����-��
  unsigned char GrAdr; // �������������� ����� ����-��
  unsigned int Temper; // ����������� ���
  float flTemper; // �����������, ������� �������
  unsigned int DNU; // ���������� �� ������ �������������� ������� ������ ���
  double dbDNU; // ���������� �� ������ �������������� ������� ������ [�]
  unsigned int DVU; // ���������� �� ������ �������������� �������� ������ ���
  double dbDVU; // ���������� �� ������ �������������� �������� ������ [�]
  int UhiI, UhiIsr, sumUhiI[50], kodUhiI, ptrUhiI; // UhiI - ���������� ������� �����. (��50) ���
  double dbUhiIsr; // ���������� ������� �����. (��50) [�]
  unsigned int SIM3; // ������������ �������� ��� (���)
  double dbSIM3; // ������������ �������� ��� [���.]
  unsigned int SIM4; // ������ ��� ���������� (���)
  double dbSIM4; // ������ ��� ���������� [���.]
  unsigned int SIM2; // ��� ���������� ������������ (���)
  unsigned int Ampl; // ������ ���������� (������ = 5) (���)
  double dbAmpl; // ������ ���������� (������ = 5) [�]
  int LEDAmpI, LEDAmpR, LEDAmpRcp, LEDAmp[50], kodLEDAmp, ptrLEDAmp;
  double dbLEDAmpRcp;
  unsigned int flagFirst;  // ���� ���������� ������ (�������� ������� 1)
  unsigned int flagSecond; // ���� ���������� ������ (�������� ������� 1)
  unsigned char MasRez[8];// = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
  int ptrBD;
  bool ErorAuto;

  String Str_hex;

  char Str_err[250]; // ���� ���������� ��������������� ��������� �� ������

  bool f_Inp32;
  bool f_Out32;
  unsigned short AddrLPTPort;
  //==\\int AddrLPTPort;

  int FlagDebug; // ���� �������

  bool FlagAutoOpros; // ���� ��� ��������� ��������� ������ (������� start/stop)
  bool bFlagWork; // ���� ������ ��������� �������/��������
  bool bFlagWyborProtokola;
  bool bFlagPovtora; // = false - ��������� 1 ���, = true - ��������� ���������

  int FlagAutoTimer; // ����, ����������� � �������
  int AutoTimer; // ���������, ����������� � �������
  int CisloItera; // ���������� ���������� ��� �������� ������� ��

  HINSTANCE dllInstanse;
  unsigned char ArrBD[8]; // ��� ������������� 8-�� ��
  unsigned char ArrBD_loop[8]; // ��� ������������� 8-�� �� � "�����������" �����


  int FlagFuncInPotok; //
  bool bFlagButton_ReadFromBD; // false - ������ �� ������, true - ������

  unsigned int __fastcall dnu2code0(double var);
  unsigned int __fastcall dnu2code1(double var);
  unsigned int __fastcall dvu2code0(double var);
  unsigned int __fastcall dvu2code1(double var);

  unsigned int __fastcall U2Code(double var);
  double __fastcall Code2U(int var);
  
  double __fastcall code2dnu0(int var);
  double __fastcall code2dvu0(int var);
  double __fastcall code2dnu1(int var);
  double __fastcall code2dvu1(int var);

  bool bFlag_Button_WriteToBD;
  void __fastcall EnabledWriteForTCP( bool En ); // ���������/��������� ������ � �� � ���������� ModBus TCP

  void __fastcall updatecom(void);

  bool fLagZapEEPROM; // = false - ������ � ������ ����������

  WORD Hour, Min, Sec, MSec;
  WORD Hour1, Min1, Sec1, MSec1;
  WORD Hour2, Min2, Sec2, MSec2;
  int varTime1;
  int varTime2;
  int PSW_bit0;
  int PSW_bit1;
  bool bFlagButton_OpenBD_msek;
  // 22.05.2014
  int Value_Addr_BD;
  TColor clWin_Edit_2_Col2_Row4;
  TColor clWin_Edit_2_Col3_Row4;
  TColor clWin_Edit_2_Col2_Row5;
  TColor clWin_Edit_2_Col3_Row5;

  TColor clWin_Edit_2_Col2_Row12;
  TColor clWin_Edit_2_Col3_Row12;
  TColor clWin_Edit_2_Col2_Row13;
  TColor clWin_Edit_2_Col3_Row13;

  bool CreateFormFlag_BD82; // false - ����� �� ������������ ���
  int ActivePageIndex; // ������ �������
  int iFlagTimer2;
  int iAP; // �������� ������� ( 0 ... 3 )

  // ����� ����� � ������, �� �� ������ � ���� ����������
  // ���� ���� ��������������� � false
  // ����� �������� ������ (��� ���� ��������� ��� ������ �� ����������) - � true.
  // ������������ ��� ����������� � ���,
  // ��� ������ ���������� �� �������������
  // ��� ������� ����������������� ����� � �����.
  bool bf_Zabyvchivosti;


  //==\\void PressKey( int Key );
  //==\\void ReleaseKey( int Key );
  //==\\void ClickKey( int Key );
  

  Graphics::TBitmap * BMCopy;
  TJPEGImage * jpg;
  void ZamenaTochky( char * chS ); // ����� � ������ �������� ������� ( ����� ��� �-��� StrToFloat() )

  //==\\int ADCdata[1024]; // ������
  int ADCdata[512]; //==\\ ������

  // �������� ���� �� � ����� "(������� ����):\VNIIA Ppograms\For_MCNP_Files"
  // ���� "inpout32.dll", ���� ��� - ������� ��� �� ��������, � ����� ����������
  bool __fastcall IzvlechrnieDLL( void );
  void __fastcall YpravlenieDostupnostu(bool bFlag);

  void __fastcall InterfaceUchSvet(int iVar);
  void __fastcall InterfaceARH(int iVar);
public:		// User declarations
  //bool bFlagChengeKolTik; // ����������� ������� ��� �����
  bool bFlagChengeKolTikSpectr; // ����������� ������� ��� �������
  bool FlagOpros; // ���� ��� ��������� ��������� ������ (������� �������/�������)
  bool FlagWorkCom; // ���� ������ � Com-������
  RSProtokol_t * Prot;
  int ErrorCode;

  bool bFlagPotok; // = false - ��������� ������ � ������
  bool bFlagRezPotok; // = false - �� ����������� ��������� � ������
  bool bFlagImp2sek;
  bool bFlagStart; // = true - ������ "���. (2 ���)" ������ ������, false - ������ �� ����� 2 ���. � ������� �������
  short StateLPT;

  int varFrom;
  int varTo;
  char CArr[100]; // ������ ������ � Memo

  // ===>> 17.07.2017
  //!bool flagModbusProtokol; // ���� ��������� false - "������", true - ModBusRTU (���� � ������ RSProtokol_t)
  int flagModbusProtokol; //! // ���� ��������� (���� � ������ RSProtokol_t)
  // 0 - "9-�� ������"
  // 1 - ModBus RTU
  // 2 - ModBus TCP
  // 3 - ModBus RTU (TCP/IP)
  // <<=== 17.07.2017

  void __fastcall ClearEdit_1(void);
  void __fastcall ClearEdit_2(void);
  void Bd82Bd84( int BdTip84 );  
  //==\\float __fastcall TConvert(int Temper);

  //===
  int __fastcall OprosBD(void); // -1 - ������ �����, 0 - ����� ��������
  int __fastcall OprosBD_2(void);
  void __fastcall Printing(void);
  // ===
  int __fastcall RSDisConnect(void);
  void __fastcall RSDisConnect2(void);  
  // ===
  bool FlagButtonSearch;


  // �����������
  __fastcall TForm_82_Start(TComponent* Owner);
  // ����������
  //==\\__fastcall ~TForm_82_Start();


  void __fastcall ZapEEPROM(void);
  void __fastcall ZapEEPROM_2(void);
  void __fastcall ReadFromBDModbus(void);
  void __fastcall WriteToBDModBus(void);
  int __fastcall RSConnect(const char * device);
  // ===>> 28.02.2015
  int tochnost_DNU;
  int tochnost_DVU;
  //int Vybor_TCP;  
  // <<=== 28.02.2015

  void __fastcall ErrorZvyazi(void);
  void __fastcall ErrorZvyaziByla(void);

  int iVar_Edit_2_Col2_Row4;
  int iVar_Edit_2_Col2_Row5;

  double fVar_Edit_2_Col3_Row4;
  double fVar_Edit_2_Col3_Row5;

  int iVar_Edit_2_Col2_Row6;
  int iVar_Edit_2_Col2_Row7;
  int iVar_Edit_2_Col2_Row8;
  int iVar_Edit_2_Col2_Row9;
  int iVar_Edit_2_Col2_Row10;

  void __fastcall ZvukOn(void);
  void __fastcall ZvukOff(void);
  bool bfZvukOn;
  bool bfZvukOff;

  // ��� ����������� ��������� �������
  int TimeInterv;
  bool bfTimeOnOff;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_82_Start * Form_82_Start;
//---------------------------------------------------------------------------
#endif
