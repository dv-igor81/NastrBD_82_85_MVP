//---------------------------------------------------------------------------
#include <vcl.h>
#include <Inifiles.hpp>
#include <stdio.h>
#pragma hdrstop
#include "Unit_FormDispet.h"
#include "Unit_82_Form_Start.h"
#include "Unit_Form_VersionInfo.h"
#include "Unit_82_Log.h"
#include "Window_UpdateThis.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormDispet *FormDispet;
const char * IniFileName = "DIA_VNIIA_NASTR_BD8285";
//---------------------------------------------------------------------------
const char * TFormDispet::GetProgrammVersion()
{
  return ProgrammVersion.c_str();
}
//---------------------------------------------------------------------------
void TFormDispet::WrapShow()
{
  this->Show();
}
//---------------------------------------------------------------------------
__fastcall TFormDispet::TFormDispet(TComponent* Owner)
        : TForm(Owner),
        szAppName( "NastrBD82_85" )
        , viewLoader ( this, this )        
{
  DiaGetWinHandle( Handle );
  uiFlagApp = 0;

  ProgrammVersion = " v4.29.5";
  AnsiString FormCaption = "��������� ��: 82, 84, 85";  

  this->Caption = FormCaption;
  this->Caption = this->Caption + ProgrammVersion;
  this->RadioButton_BD82_84->Checked = true;
}
//---------------------------------------------------------------------------
/*void __fastcall TFormDispet::OnWMSysCommand( TMessage& Message )
{
  // ��������� ��������� ����, ���������� ������
  hWndSecond = (HWND)Message.WParam;
  switch( Message.WParam )
  {
    case SC_MINIMIZE:
         Application->Minimize();
         Message.Result = 0;
         break;
    default :
         DefaultHandler( &Message );
  }
}*/
//---------------------------------------------------------------------------
void __fastcall TFormDispet::funkZapros( TMessage & Message )
{
  // ��������� ��������� ����, ���������� ������
  hWndSecond = (HWND)Message.WParam;
  aApp = GlobalAddAtom( szAppName );
  if ( Message.LParamLo == aApp )
  {
    // ����, ���������� ������, ������� ��������� ������ ����
    SendMessage( hWndSecond, WM_DIA_OTVET, (WPARAM)hWndFirst, (LPARAM)0 );
  }
  else
  {
    GlobalDeleteAtom( aApp );
  }
}
//---------------------------------------------------------------------------
int __fastcall TFormDispet::DiaGetWinHandle( HWND hWnd ) // �������� ��������� ����
{
  this->hWndFirst = hWnd;
  return 0; // ��� ������
}
//---------------------------------------------------------------------------
void __fastcall TFormDispet::funkOtvet( TMessage & Message )
{
  // ��������� ��������� ����, ���������� �����
  hWndSecond = (HWND)Message.WParam;
  GlobalDeleteAtom( aApp );
  uiFlagApp = 1;
}
//---------------------------------------------------------------------------
void __fastcall TFormDispet::Button_InitiateClick(TObject *Sender)
{
  bool bFlagVybor;
  if (
        (RadioButton_BD82_84->Checked == true) ||
        (RadioButton_BD85New->Checked == true)
     )
  { // ������ ���� ���� �����
    Hide();
  }
  else
  {
    iPanelLeft = Panel_MessageBox->Left;
    iPanelTop = Panel_MessageBox->Top;
    iPanelHeight = Panel_MessageBox->Height;
    iPanelWidth = Panel_MessageBox->Width;
    Panel_MessageBox->Align = alClient;
    Panel_MessageBox->Enabled = true;
    Panel_MessageBox->Visible = true;
    Timer_Dispet->Interval = 1000; // 1 ���
    Timer_Dispet->Enabled = true;
    iFlagTimer = 1;
  }

  if ( RadioButton_BD82_84->Checked )
  {
    Form_82_Start->Bd82Bd84( 84 );    
    Form_82_Start->Show();   //ShowModal
  }
  else if ( RadioButton_BD85New->Checked )
  {
    viewLoader.LoadWindowBd85Main();
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormDispet::FormCreate(TObject *Sender)
{
  Panel_MessageBox->Enabled = false;
  Panel_MessageBox->Visible = false;
  TIniFile * IniFile = new TIniFile( IniFileName );
  try
  {
    this->Left = IniFile->ReadInteger( "DIA_Form_Dispet", "Form Left", 0 );
    this->Top = IniFile->ReadInteger( "DIA_Form_Dispet", "Form Top", 0 );
    this->iFlagVyborFormy = IniFile->ReadInteger( "DIA_Form_Dispet", "Form FlagVyborFormy", 0 );
    switch ( iFlagVyborFormy )
    {
    case 1:
      RadioButton_BD82_84->Checked = true;
      break;
    case 2:
      RadioButton_BD85New->Checked = true;
      break;
    }
    delete IniFile;
  }
  catch (...)
  {
    delete IniFile;
    ShowMessage( "TFormDispet::FormCreate ����������" );
  }

  HWND WinHandle;
  WinHandle = hWndFirst;

  /*aApp = GlobalAddAtom( szAppName );
  while ( WinHandle != 0 )
  {
    if ( WinHandle != hWndFirst )
    {
      SendMessage
      (
        WinHandle,
        WM_DIA_ZAPROS,
        (WPARAM)hWndFirst,
        (LPARAM)MAKELPARAM( aApp, 0 )
      );
    }
    WinHandle = GetWindow( WinHandle, GW_HWNDNEXT );
  }
  GlobalDeleteAtom( aApp );   */


  if ( uiFlagApp == 0 )
  {
    ; // ��� 1-�� ��������� ���������� (�� �������� ���������-�����)
  }
  else if ( uiFlagApp == 1 )
  {  // ��� �� 1-�� ��������� ���������� (�������� ���������-�����)
    //ShowMessage( "���������� ��� ��������!" );
    sprintf( szCaptionMess, "%s", szAppName );
    sprintf( szTextMess, "���������� \"%s\" ��� ��������!", szAppName );
    MessageBox( hWndFirst, szTextMess, szCaptionMess, MB_OK );

    SetForegroundWindow( hWndSecond ); // �������� ����� �����
    ShowWindow( hWndSecond, SW_SHOWDEFAULT );
    Application->Terminate();
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormDispet::Timer_DispetTimer(TObject *Sender)
{
  switch ( iFlagTimer )
  {
  case 1:
    Panel_MessageBox->Enabled = false;
    Panel_MessageBox->Visible = false;
    Panel_MessageBox->Align = alNone;
    Panel_MessageBox->Left = iPanelLeft;
    Panel_MessageBox->Top = iPanelTop;
    Panel_MessageBox->Height = iPanelHeight;
    Panel_MessageBox->Width = iPanelWidth;
    break;
  default:
    break;
  }
  Timer_Dispet->Enabled = false;  
  iFlagTimer = 0;
}
//---------------------------------------------------------------------------
void __fastcall TFormDispet::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  TIniFile * IniFile = new TIniFile( IniFileName );
  try
  {
    IniFile->WriteInteger( "DIA_Form_Dispet", "Form Left", this->Left );
    IniFile->WriteInteger( "DIA_Form_Dispet", "Form Top", this->Top );
    if ( RadioButton_BD82_84->Checked == true )
    {
      iFlagVyborFormy = 5;
    }
    if ( RadioButton_BD85New->Checked == true )
    {
      iFlagVyborFormy = 2;
    }
    IniFile->WriteInteger( "DIA_Form_Dispet", "Form FlagVyborFormy", iFlagVyborFormy );

    delete IniFile;    
  }
  catch (...)
  {
    delete IniFile;
    ShowMessage( "TFormDispet::FormClose ����������" );
  }
  Window_Updater->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormDispet::Button_IzmeneniyaClick(TObject *Sender)
{
  Form_VersionInfo->Show();
}
//---------------------------------------------------------------------------
void __fastcall TFormDispet::FormShow(TObject *Sender)
{
  DiaGetWinHandle( this->Handle );
}
//---------------------------------------------------------------------------



