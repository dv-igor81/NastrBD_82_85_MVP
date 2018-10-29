//---------------------------------------------------------------------------
#ifndef Unit_Form_Puasson8BDH
#define Unit_Form_Puasson8BDH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
class TFormPuasson8BD : public TForm
{
__published:	// IDE-managed Components

  TCheckBox * CheckBox_AddrBD1;
  TCheckBox * CheckBox_AddrBD2;
  TCheckBox * CheckBox_AddrBD3;
  TCheckBox * CheckBox_AddrBD4;
  TCheckBox * CheckBox_AddrBD5;
  TCheckBox * CheckBox_AddrBD6;
  TCheckBox * CheckBox_AddrBD7;
  TCheckBox * CheckBox_AddrBD8;

  TEdit * Edit_SN1;
  TEdit * Edit_SN2;
  TEdit * Edit_SN3;
  TEdit * Edit_SN4;
  TEdit * Edit_SN5;
  TEdit * Edit_SN6;
  TEdit * Edit_SN7;
  TEdit * Edit_SN8;

  TPanel * Panel_Display_BD1;
  TPanel * Panel_Display_BD2;
  TPanel * Panel_Display_BD3;
  TPanel * Panel_Display_BD4;
  TPanel * Panel_Display_BD5;
  TPanel * Panel_Display_BD6;
  TPanel * Panel_Display_BD7;
  TPanel * Panel_Display_BD8;

  TCSpinEdit * SpinEdit_AddrBD1;
  TCSpinEdit * SpinEdit_AddrBD2;
  TCSpinEdit * SpinEdit_AddrBD3;
  TCSpinEdit * SpinEdit_AddrBD4;
  TCSpinEdit * SpinEdit_AddrBD5;
  TCSpinEdit * SpinEdit_AddrBD6;
  TCSpinEdit * SpinEdit_AddrBD7;
  TCSpinEdit * SpinEdit_AddrBD8;

  TCSpinEdit * SpinEdit_Time;

  TScrollBox * ScrollBoxMain;
  TGroupBox * GroupBoxMain;

  TLabel * Label_sernum;
  TLabel * Label_addr_BD;
  TLabel * Label_Time;
  TLabel * Label_info;
  TPanel * Panel_Info;

  TButton * Button_Start;
  TButton * Button_detail;
  TButton * Button_ReadLogs;
  TButton * Button_Stop;

  TCSpinEdit * SpinEdit_readTimeout;
  TLabel * Label_readTimeout;
  TCheckBox * CheckBox_Err;
  TCheckBox * CheckBox_AllBD;
  TLabel * Label_Time_Diapazon;
  TButton * Button_Exit;

  TButton * Button_Graph_01;
  TButton * Button_Graph_02;
  TButton * Button_Graph_03;
  TButton * Button_Graph_04;
  TButton * Button_Graph_05;
  TButton * Button_Graph_06;
  TButton * Button_Graph_07;
  TButton * Button_Graph_08;
  TButton * Button_Graph;

  TEdit * Edit_SchetSek01;
  TEdit * Edit_SchetSek02;
  TEdit * Edit_SchetSek03;
  TEdit * Edit_SchetSek04;
  TEdit * Edit_SchetSek05;
  TEdit * Edit_SchetSek06;
  TEdit * Edit_SchetSek07;
  TEdit * Edit_SchetSek08;

  TEdit * Edit_PNSch01;
  TEdit * Edit_PNSch02;
  TEdit * Edit_PNSch03;
  TEdit * Edit_PNSch04;
  TEdit * Edit_PNSch05;
  TEdit * Edit_PNSch06;
  TEdit * Edit_PNSch07;
  TEdit * Edit_PNSch08;

  TEdit * Edit_KvoIsp01;
  TEdit * Edit_KvoIsp02;
  TEdit * Edit_KvoIsp03;
  TEdit * Edit_KvoIsp04;
  TEdit * Edit_KvoIsp05;
  TEdit * Edit_KvoIsp06;
  TEdit * Edit_KvoIsp07;
  TEdit * Edit_KvoIsp08;

  TLabel * Label_KvoIsp01;
  TLabel * Label_KvoIsp02;
  TLabel * Label_KvoIsp03;
  TLabel * Label_KvoIsp04;
  TLabel * Label_KvoIsp05;
  TLabel * Label_KvoIsp06;
  TLabel * Label_KvoIsp07;
  TLabel * Label_KvoIsp08;

  TLabel * Label_SchetSek01;
  TLabel * Label_SchetSek02;
  TLabel * Label_SchetSek03;
  TLabel * Label_SchetSek04;
  TLabel * Label_SchetSek05;
  TLabel * Label_SchetSek06;
  TLabel * Label_SchetSek07;
  TLabel * Label_SchetSek08;


  TLabel * Label_PNSch01;
  TLabel * Label_PNSch02;
  TLabel * Label_PNSch03;
  TLabel * Label_PNSch04;
  TLabel * Label_PNSch05;
  TLabel * Label_PNSch06;
  TLabel * Label_PNSch07;
  TLabel * Label_PNSch08;

  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall Button_StartClick(TObject *Sender);
  void __fastcall Button_StopClick(TObject *Sender);
  void __fastcall Button_detailClick(TObject *Sender);
  void __fastcall CheckBox_AllBDClick(TObject *Sender);
  void __fastcall Button_ExitClick(TObject *Sender);
  void __fastcall Button_Graph_01Click(TObject *Sender);
  void __fastcall Button_Graph_02Click(TObject *Sender);
  void __fastcall Button_Graph_03Click(TObject *Sender);
  void __fastcall Button_Graph_04Click(TObject *Sender);
  void __fastcall Button_Graph_05Click(TObject *Sender);
  void __fastcall Button_Graph_06Click(TObject *Sender);
  void __fastcall Button_Graph_07Click(TObject *Sender);
  void __fastcall Button_Graph_08Click(TObject *Sender);
  void __fastcall Button_GraphClick(TObject *Sender);
        
private:	// User declarations

  char chLogFileName[8 /* ���������� ����� */][/*16*/26 /* ����� ������ */]; // ����� ������-�����
  int handle [ 8 ]; // ����������� ������ (����� ���������� <io.h>)
  char shFileString[16]; // ������ ��� ������ � ����

  void GetAddrBDArr( void );
  int MinSchet(int * ArrSchet);
  void PostroitGrafik(void);    

public:		// User declarations
  int DIA_Interval; // ��������, ��� ���������� ��������
  unsigned char AddrBDArr[8]; // 248 - ���� �������������� �� ������������, 1...247 - ����� ��
  //===>> (24.10.2014)
  unsigned char IndexArr[8]; // ��������� ��� ������ (�������� ������� AddrBDArr, ������� ��), ������� ������ ������������
  unsigned char pInd; // "���������" (������) ������� IndexArr (��������� �� ��� ����, ����� ��������� �������� ��� ����� �������)
  unsigned char maxInd; // ������� �� ������� �������������.
  //<<=== (24.10.2014)
  unsigned long SerialNumArr[8]; // �������� ������ ��

  bool bFlag8BD_PSW; // true - ���� �� 8-�� ������ ������� ������� (���� ���� ���������� �����)
  bool bFlagSetTimeInterval[8]; // false - �� ����������� ������� SetTimeInterval(8) ��� ��
  bool bFlagGetSerialNum[8]; // false - �� ����������� ������� ReadFlashInvert(10, &SerialNumArr[i]) ��� ��
  bool bFlagDisplaySN[8]; // false - �� ������������ �������� ������
  bool bFlagOprosBD8; // false - ��� �� ���� �� ���������� ������� OprosBD8Arr
  bool bFlagDisplayArr[8]; // false = ������ �� �������

  float SredMas[8][300000]; // ������, ��� ����������� ������ �� 8-�� ��
  int indexSM[8]; // �������� ��������, ��� ���������� ������� ������� SredMas
  
  bool bFlagDisplay; // false = �� ���������� ���������� ��������
  bool bFlagDisplay_temp;
  int siFlagGraph;
  bool bFlagWork;

  unsigned int ErrorCodBD[8]; // ��� ������

  unsigned int KolErrors[8]; // ���������� ������
  unsigned int KolErrorsPodryad; // ���������� ������ ������

  unsigned int PrizNesnChet[8]; // ���������� ��������� ��������� �����
  unsigned int Chet[8]; // ������� ����
  signed int PSW[8]; // ������� ����� ��������� (-1 - ������)

  unsigned int ChetNakapl[8]; // �������� ���� �� ������� ����������� ��� ������ ����� �������������� �����
  unsigned int ChetZaSekundu[8]; // �������� ���� �� �������
  unsigned char KolVoChet[8]; // ���������� ���������� � �� ������ (������� ��� �������� ���� � ��)

  unsigned int dTSum; // �������� �������, �� ������� ������������ ��������� �����
  unsigned int dTmaxSum; // �������� dTSum

  unsigned int dTPeriod; // �������� �������, ����� ������� ������������ ��������� �����
  unsigned int dTmaxPeriod; // �������� dTSum

  unsigned int dTBD[8];
  unsigned int dTmaxBD[8];

  int TimeBD[8];
  int MinTimeBD;

  TPanel * Panel_Display_Arr[8];
  TEdit * Edit_ArrSerNum[8];
  TCSpinEdit * SpinEdit_AddrBDArr[8];
  TCheckBox * CheckBox_AddrBDArr[8];
  TButton * Button_GraphArr[8];

  TEdit * Edit_SchetSekArr[8];
  TEdit * Edit_PNSchArr[8];
  TEdit * Edit_KvoIspArr[8];

  __fastcall TFormPuasson8BD(TComponent* Owner);
  void __fastcall Display( void );
  void __fastcall TimerOn( void );
  void __fastcall TimerOff( void );

  void __fastcall FileArrayInit( int IndexArr  );
  void __fastcall FileWriteData( int IndexArr );  
  void __fastcall FileWriteError( int IndexArr );
  void UpdateGraph( int NomerBD ); // ��������� ������� (0 <= NomerBD < 8) 

};
//---------------------------------------------------------------------------
extern PACKAGE TFormPuasson8BD * FormPuasson8BD;
//---------------------------------------------------------------------------
#endif
