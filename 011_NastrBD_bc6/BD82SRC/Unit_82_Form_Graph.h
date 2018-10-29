//---------------------------------------------------------------------------

#ifndef Unit_82_Form_GraphH
#define Unit_82_Form_GraphH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
//---------------------------------------------------------------------------
#include "Unit_82_Form_Puasson8BD.h"
//---------------------------------------------------------------------------
class TForm_Graph : public TForm
{
__published:	// IDE-managed Components

  TChart * Chart_Puasson_lin;
  TChart * Chart_Puasson_log;

  TLineSeries * Series1;
  TBarSeries * Series2;
  TLineSeries * Series3;
  TLineSeries * Series4;
  TBarSeries * Series5;
  TLineSeries * Series6;

  TCheckBox * CheckBox_logariphm;
  TPanel * Panel_InfoMain;
  TLabel * Label_srednee;
  TLabel * Label_verLoSrab;
  TLabel * Label_Error_Svyazi;
  TPanel * Panel_Vybora;
  TRadioButton * RadioButton_Puasson;
  TRadioButton * RadioButton_inTime;
  TRadioButton * RadioButton_Gays;
  TPanel * Panel_InfoDop;
  TLabel * Label_koefMorozova;
  TLabel * Label_znachPoroga;
  TLabel * Label_kolichIzmereniy;
  TLabel * Label_Dispersiya;
  TTimer * Timer_ForGraphUpdate;
  TLabel * Label_FileName;
  void __fastcall RadioButton_PuassonClick(TObject *Sender);
  void __fastcall CheckBox_logariphmClick(TObject *Sender);
  void __fastcall RadioButton_GaysClick(TObject *Sender);
  void __fastcall RadioButton_inTimeClick(TObject *Sender);
  void __fastcall Button_UpdateGraphClick(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall FormShow(TObject *Sender);
        void __fastcall Timer_ForGraphUpdateTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TForm_Graph(TComponent * Owner);
  int Kisp; // ���������� ��������� (���� �������� �� ���� ����� FormPuasson8BD->SpinEdit_Time->Value * 1000)
  int Nisp; // ���������� ��������� (���� �������� ��������� ����� � �����, ��� ������)
  bool bFlagWork;

  char chFileName[250];
  AnsiString filename;

  int countIndex; // �������
  int Err_Svyaz; // ������ ����� (������� � ���� "-1")

  int MaxPoisson; // ������� ������������� ��������  
  unsigned int MaxZn; // ������������ ��������
  unsigned int MinZn; // ����������� ��������  
  unsigned int MaxZn2; // ������������ �������� 2
  unsigned int MinZn2; // ����������� �������� 2

  unsigned int DataArray[300000];
  double y[300000];
  double yy[300000];
  double Spec_Gays[300000];
  unsigned int Spec[10000]; // ������ ��� �������

  bool DiaFindFile ( AnsiString * filename ); // false - �� ������ ���� filename
  void GraphFromFile( void );
  void PostrGraf( void ); // ������ ���������� ��������
  void PostrGrafAll( void ); // ��� �������� �� ���������� ��������, ������� ����� ��������� (����/�����)
  void GrafFromBufer( void );
  double poisson(int x, float Srednee);
  double Gays(int x, float Disper, float Srednee);

  int siFlagGraph;
  TFormPuasson8BD * ptrForm8BD;
  bool bFlagOtkrytoyFormy;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Graph *Form_Graph;
//---------------------------------------------------------------------------
#endif
