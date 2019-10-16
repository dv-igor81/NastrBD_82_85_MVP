//---------------------------------------------------------------------------
#include <vcl.h>
// ===>> ===>> }{ ===>> ===>>
//    ���������� ��������� #pragma hdrstop ��������� �����������, ���
//    � ������ ����� ������ ����� ���������� ��������� ��������������
//    ���������������� ������������ ������. ������������� ����� ���������
//    #pragma hdrstop ������������ ����� ����� ��������������� ��� ������
//    ���������� ������� ������.
#pragma hdrstop
// <<=== <<=== }{ <<=== <<===
//---------------------------------------------------------------------------
#include <stdio.h>
#include <Inifiles.hpp>
//---------------------------------------------------------------------------
#include "Unit_82_ComPortReadWrite.h"
#include "Unit_82_Priklad_Funk.h"
#include "Unit_82_Form_ARCH.h"
#include "Unit_82_Form_Puasson8BD.h"
#include "Unit_82_Form_Start.h"
#include "Unit_82_Form_Image.h"
#include "Unit_82_Resourse.h"
#include "Unit_82_Form_Spectr.h"
#include "Unit_82_Log.h"
#include "Utilites_For_Edit.h" // EditHelper.ConvertToInt

#ifdef _DIA_OBEDINENIE_
  #include "Unit_FormDispet.h"
#endif
//---------------------------------------------------------------------------
#include "inpout32.h"
#include "Unit_DIA_Global_Funk.h"
//---------------------------------------------------------------------------

// ===>> ===>> }{ ===>> ===>>
//    ����� ��������� ������������� � �������������� ������� � ������
//    �� ������������� � ������ ������, � ����� � ��� �������� �����
//    ����� ��������� #include ����� ����� ����� ������� ����������
//    ������ #pragma package(smart_init). � ��������� ������ ����������
//    ����� ������ ��� �� ����� ���������, �� ����� �� �������
//    ������������ ����������.
#pragma package(smart_init)
// <<=== <<=== }{ <<=== <<===

#pragma link "CSPIN"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
#ifndef _DIA_OBEDINENIE_
  const char * IniFileName = "DIA_BD82.ini";
  AnsiString ProgrammVersion = " v4.xx";
#else
  extern const char * IniFileName;
#endif
bool flagPort = false; // ��������� ����� ������ (true) / ������ (false)
extern getaddrinfo_t * getaddrinfo;
extern freeaddrinfo_t * freeaddrinfo;
HMODULE mod_ws2_32_dll = NULL;
//---------------------------------------------------------------------------
AnsiString FormCaption = "";
AnsiString FormCaption82_84 = "��������� ��82 � ��84";
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::OnWMSysCommand( TMessage& Message )
{
  switch( Message.WParam )
  {
    case SC_MINIMIZE:
         Application->Minimize();
         Message.Result = 0;
         break;
    default :
         DefaultHandler( &Message );
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::updatecom(void)
{
  AnsiString S = "";
  AnsiString Sstr = "";
  int i = 1, j = 0, itInd = 0;
  HANDLE port;

  ComboBox_NomComPort->Clear();
  ComboBox_NomComPort->ItemIndex = 0;
  Button_UpdateComPortsList->Enabled = false;

  SetLastError(0);
  while ( true )
  {
    S = "\\\\.\\COM" + IntToStr(i); // 03.08.2016
    Sstr = "COM" + IntToStr(i);
    //==\\SetLastError(0);
    port = CreateFileA( S.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
      FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
    //tempError = GetLastError();
    //S += " ������ �";
    //S += tempError;
    //MessageBox(NULL, S.c_str(), "TEST COM PORT'S", 0);
    if ( port != INVALID_HANDLE_VALUE )
    {
      ComboBox_NomComPort->Items->Add( Sstr );
      j++;
      CloseHandle(port);
    }
    //if ( i == 32 )
    if ( i == 100 )
    {
      break;
    }
    i++;
  }

  ButtonSearch->Enabled = false;
  Button_OpenBD->Enabled = false;
  Button_WriteToBD->Enabled = false;
  Button_SaveAddr->Enabled = false;
  Button_Start->Enabled = false;

  if( j > 0 ) // ���� ���� ��������� �����
  {
    AnsiString tS, tS2;
    if ( RadioGroup_VyborProtokola->ItemIndex != 0 ) // �������� ModBus
    {
      ButtonSearch->Enabled = true;
      Button_SaveAddr->Enabled = true;
    }
    Button_OpenBD->Enabled = true;
    Button_Start->Enabled = true;

    TIniFile * IniFile = new TIniFile( IniFileName );
    try
    {
      tS = IniFile->ReadString( "Form_82_Start", "SelectedComPort", "COM1" );
      delete IniFile;
    }
    catch (...)
    {
      this->Memo_For_Print_Errors->Lines->Add(Form_82_Start->GetCurrentTime() + "updatecom: ������ ��� ������� ��������� ini-����");
      delete IniFile;
    }
    for (int k = 0; k < j; k++)
    {
      tS2 = ComboBox_NomComPort->Items->Strings[k];
      if (tS == tS2)
      {
        itInd = k;
        break;
      }
    }
    ComboBox_NomComPort->ItemIndex = itInd;
    bFlagDE = true; // ���� ����������� ������ (� ����������� �� �������� ���-������)
  }
  else if (j == 0)
  {
    ComboBox_NomComPort->ItemIndex = -1;
    bFlagDE = false; // ���� ����������� ������ (� ����������� �� �������� ���-������)
  }
  Button_UpdateComPortsList->Enabled = true;
  bFlagChengeKolTik = true; // ����������� ������� ��� �����
  bFlagChengeKolTikSpectr = true; // ����������� ������� ��� �������
}
//---------------------------------------------------------------------------
TForm_82_Start * Form_82_Start;
ComPortReadWrite_t * Cprw;
typedef short (__import TInt32(short PortAddress)); // ������� ������ ��������� (������ �) LPT-�����
typedef void (__import TOut32(short PortAddress, short data));
TInt32 * pInt32 = NULL; // ��������� �� ������� Int32
TOut32 * pOut32 = NULL; // ��������� �� ������� Out32
//---------------------------------------------------------------------------
// ����������
//==\\__fastcall TForm_82_Start::~TForm_82_Start()
//==\\{
//==\\}
//---------------------------------------------------------------------------
// �����������
__fastcall TForm_82_Start::TForm_82_Start(TComponent* Owner)
        : TForm(Owner),
        as_ZvukOnOff ( this, &TForm_82_Start::ZvukOnOff )
{
  ptrUhiI = 0;
  kodUhiI = 0;

  //FormCaption = FormCaption + ProgrammVersion;
  //this->Caption = this->Caption + ProgrammVersion;

  ptrLEDAmp = 0;
  kodLEDAmp = 0;

  bFlagWork = false; // ���� ������ ��������� �������/��������
  FlagWorkCom = false;
  FlagOpros = false; // ���� ��� ��������� ��������� ������ (������� �������/�������)
  f_Inp32 = false; // ���� �������� ������� ������ LPT-����� Inp32
  f_Out32 = false; // ���� �������� ������� ������ � LPT-���� Out32

  MasRez[0] = 0x01;
  MasRez[1] = 0x02;
  MasRez[2] = 0x04;
  MasRez[3] = 0x08;
  MasRez[4] = 0x10;
  MasRez[5] = 0x20;
  MasRez[6] = 0x40;
  MasRez[7] = 0x80;

  AddrLPTPort = 888; // ����� LPT-�����
  CisloItera = 30; // ���������� ���������� ��� �������� ������� ��
  bFlagPotok = false; // = false - �� � ������, = true - � ������
  bFlagRezPotok = false; // = false - �� ����������� ��������� � ������
  bFlagButton_ReadFromBD = false;
  FlagDebug = 1;
  //FlagDebug = 0;
  fLagZapEEPROM = true; // = false - ������ � ������ ����������
  BitBtn_ARCH->Enabled = false;
  BitBtn_Uch_sv->Enabled = false;
  
  CreateFormFlag_BD82 = false; // false - ����� �� ������������ ���
  bFlagKnopkaZapis = false;
  // ===>> 28.02.2015
  tochnost_DNU = 3;
  tochnost_DVU = 3;
  //===
  CheckBox_Diskr->Checked = true;
  CheckBox_Diskr->Enabled = false;
  CheckBox_Diskr->Visible = false;
  //===
  bFlag_Button_WriteToBD = true;
  bFlagDE = true; // ���� ����������� ������ (� ����������� �� �������� ���-������)
  // <<=== 28.02.2015
  // ������ �� ����������� ������� "FormShow"
  this->Prot = new RSProtokol_t; // ������� � "����" ��������� ������� ���������

  Prot->ev_ZvukOnOff += as_ZvukOnOff;

  // ������ �� ����������� ������� "FormShow"
  Cprw = new ComPortReadWrite_t(true); // true - �� ��������� ����� ��� ��������� ������
  // ������ �� ����������� ������� "FormShow"
  Cprw->FreeOnTerminate = true; // false - �� ������������ ����� ����������

  // ����� ����� � ������, �� �� ������ � ���� ����������
  // ���� ���� ��������������� � false
  // ����� �������� ������ (��� ���� ��������� ��� ������ �� ����������) - � true.
  // ������������ ��� ����������� � ���,
  // ��� ������ ���������� �� �������������
  // ��� ������� ����������������� ����� � �����.
  bf_Zabyvchivosti = false;
  bfZvukOn = false;
  bfZvukOff = false;

  /*DWORD style;
  style = GetWindowLong(this->Handle, GWL_EXSTYLE);
  style |= WS_EX_APPWINDOW;
  SetWindowLong(this->Handle,GWL_EXSTYLE, style);*/
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  if ( FlagOpros == true )
  {
    Button_OpenBDClick( NULL ); // ������� ���-����
  }
  if( Cprw != NULL )
  {
    Cprw->Terminate();
    Cprw->Resume(); // ������������ �����
    Cprw = NULL;
  }

  //==\\if( Prot != NULL )
  //==\\{
  //==\\  delete Prot;
  //==\\  Prot = NULL;
  //==\\}
  
  if ( dllInstanse != NULL )
  {
    FreeLibrary( dllInstanse );
    dllInstanse = NULL;    
  }
  TIniFile * IniFile = new TIniFile(IniFileName);
  try
  {
    IniFile->WriteInteger( "Form_82_Start", "FormStartWidth", Form_82_Start->Width );
    IniFile->WriteInteger( "Form_82_Start", "FormStartHeight", Form_82_Start->Height );
    IniFile->WriteInteger( "Form_82_Start", "FormStartLeft", Form_82_Start->Left );
    IniFile->WriteInteger( "Form_82_Start", "FormStartTop", Form_82_Start->Top );
    IniFile->WriteInteger( "Form_82_Start", "FormStartActivePageIndex", ActivePageIndex );
    IniFile->WriteString( "Form_82_Start", "SelectedComPort", Form_82_Start->ComboBox_NomComPort->Text );
    IniFile->WriteInteger( "Form_82_Start", "FormStartLptPortAddr", StrToInt( Form_82_Start->SpinEditLptAddr->Text ) );
    IniFile->WriteInteger( "Form_82_Start_Spectr", "KolTik_Spektr", Form_82_Spectr_BD84->SpinEdit_TimeSpektr->Value );

    IniFile->WriteInteger( "Form_82_Start", "FormStartProtModBus", this->RadioGroup_VyborProtokola->ItemIndex );
    IniFile->WriteInteger( "Form_82_Start", "FormStartProtModBusAddr", this->SpinEdit_AddrBD->Value);

    if ( RadioGroup_VyborProtokola->ItemIndex == 2 ) // ModBus TCP
    {
      IniFile->WriteString( "Form_82_Start", "IpAddrModBusTcp", Edit_IPAddr->Text );
      IniFile->WriteString( "Form_82_Start", "TcpPortModBusTcp", Edit_IPPort->Text );
    }
    else if ( RadioGroup_VyborProtokola->ItemIndex == 3 ) // ModBus RTU (TCP/IP)
    {
      IniFile->WriteString( "Form_82_Start", "IpAddrModBusRtuIp", Edit_IPAddr->Text );
      IniFile->WriteString( "Form_82_Start", "TcpPortModBusRtuIp", Edit_IPPort->Text );
    }

    delete IniFile;
  }
  catch(...) // ����� ����������
  {
    delete IniFile;
  }

#ifdef _DIA_OBEDINENIE_
  CreateFormFlag_BD82 = false;
  FormDispet->Show();
  ComboBox_NomComPort->Clear();
  Memo_For_Print_Errors->Clear();
  RadioGroup_Povtor->ItemIndex = -1;
  RadioGroup_VyborProtokola->ItemIndex = -1;    
#endif
}
//---------------------------------------------------------------------------
AnsiString TForm_82_Start::GetCurrentTime()
{
    TDateTime dateTime;
    AnsiString textTime = dateTime.CurrentTime();
    textTime += " ";
    return textTime;
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Timer1Timer(TObject *Sender)
{
  int i;
  int Flag;
  char text[100];

  if (bFlagWork == true)
  {
    return;
  }
  if ( bFlagButton_OpenBD_msek == true )
  {
    if ( Timer1->Interval != TimerInterval )
    {
      Timer1->Interval = TimerInterval;
    }
    DecodeTime( Time(), Hour2, Min2, Sec2, MSec2 );
    varTime2 = (Hour2 * (60 * 60) + Min2 * (60) + Sec2) * 1000 + MSec2;
    // ===
    if ( varTime2 - varTime1 >= SpinEdit_Sek->Value * 1000 )
    {
      Timer1->Enabled = false;
      sprintf(Str_err, "������ %d ������", (varTime2 - varTime1)/1000);
      Memo_For_Print_Errors->Lines->Add( GetCurrentTime() + Str_err );
      Button_OpenBD_msek->Caption = "������� ��";
      bFlagButton_OpenBD_msek = false; // ���� ��� ����������� ��������� ������ OpenBD
      Timer1->Enabled = false;
      SpinEdit_AddrBD->Enabled = true;
      Button_Start->Enabled = true;
      ComboBox_NomComPort->Enabled = true;
      RadioGroup_VyborProtokola->Enabled = true;
      Button_OpenBD->Enabled = true;
      // ===
      Button_WriteToBD->Enabled = bFlag_Button_WriteToBD;
      Button_UpdateComPortsList->Enabled = true;
      RSDisConnect(); // ������� ����
      // ===
      for ( i = 0; i < Prot->MaxIndexArrTime; i++ )
      {
        Hour = Prot->ArrTime[i].Hour;
        Min = Prot->ArrTime[i].Min;
        Sec = Prot->ArrTime[i].Sec;
        MSec = Prot->ArrTime[i].MSec;
        PSW_bit0 = Prot->ArrTime[i].PSW_b0;
        PSW_bit1 = Prot->ArrTime[i].PSW_b1;

        sprintf(Str_err, "count = %d; flagFirst = %d; flagSecond = %d",
            Prot->ArrTime[i].count, Prot->ArrTime[i].flagFirst,
            Prot->ArrTime[i].flagSecond);
        Memo_For_Print_Errors->Lines->Add( GetCurrentTime() + Str_err );
        if ( i > 0 )
        {
          int VarTnev;
          int VarTold;
          VarTnev = ( Prot->ArrTime[i].Hour * (60 * 60) +
              Prot->ArrTime[i].Min * 60 + Prot->ArrTime[i].Sec ) * 1000 +
              Prot->ArrTime[i].MSec;
          VarTold = ( Prot->ArrTime[i-1].Hour * (60 * 60) +
              Prot->ArrTime[i-1].Min * 60 + Prot->ArrTime[i-1].Sec ) * 1000 +
              Prot->ArrTime[i-1].MSec;
          sprintf(Str_err, "�%d: %d:%d:%d.%d; ��� 0 = %d; ��� 1 = %d, D = %d",
              i+1, Hour, Min, Sec, MSec, PSW_bit0,
              PSW_bit1, VarTnev - VarTold);
          Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + Str_err);
          if (VarTnev - VarTold > 200)
          {
            Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + " > 200");
          }
          if ( VarTnev - VarTold < 100 )
          {
            Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + " < 150");
          }
        }
      }
      sprintf(Str_err, "���������� ��������� ��������� ����� = %d", Prot->N1);
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + Str_err);
      return;
    } // end if (varTime2 - varTime1 >= SpinEdit_Sek->Value)
  }
  if ( FlagAutoOpros == true ) // ���� ��� ����������� ��������� ������ Start
  {
    if (Timer1->Interval != TimerInterval)
    {
      Timer1->Interval = TimerInterval;
    }
    if (FlagAutoTimer == 1) // ���� ��������� � �������� ���������� ��
    {
      Flag = 0; //
      for ( i = 0; i < 8; i++ )
      {
        if ( ArrBD[i] == 1 )
        {
          Flag = 1;
          ArrBD[i] = 0;
          ptrBD = i; // ��������� �� ��
          break;
        }
      }
      if ( Flag == 0 ) // ��� �� ����������������
      {
        if ( bFlagPovtora == false )
        { // = false - ��������� 1 ���, = true - ��������� ���������
          // ���� ��� ��������� ��������� ������ (������� start/stop)
          FlagAutoOpros = false;
          CheckBox_Vybor_BD08->Enabled = true;
          CheckBox_Vybor_BD07->Enabled = true;
          CheckBox_Vybor_BD06->Enabled = true;
          CheckBox_Vybor_BD05->Enabled = true;
          CheckBox_Vybor_BD04->Enabled = true;
          CheckBox_Vybor_BD03->Enabled = true;
          CheckBox_Vybor_BD02->Enabled = true;
          CheckBox_Vybor_BD01->Enabled = true;
          Button_OpenBD->Enabled = true;
          ComboBox_NomBD->Enabled = true;
          ComboBox_NomComPort->Enabled = true;
          Button_Start->Caption = "Start";
          SpinEdit_AddrBD->Enabled = true;
          RadioGroup_VyborProtokola->Enabled = true;
          Timer1->Enabled = false;

          // ===
          Button_WriteToBD->Enabled = bFlag_Button_WriteToBD;
          Button_UpdateComPortsList->Enabled = true;
          Button_OpenBD_msek->Enabled = true;
          Button_ARCH->Enabled = true;
          Button_Puason->Enabled = true;
          Button_Imp2sek->Enabled = true;
          RadioGroup_Povtor->Enabled = true;
          CheckBox_All->Enabled = true;
          if (f_Out32 == true)
          {
            pOut32( AddrLPTPort, (short)(-1) );
          }
          RSDisConnect(); // ������� ����
          return; // ��������� ����� ���������������
        }
        for ( i = 0; i < 8; i++ )
        {
          ArrBD[i] = ArrBD_loop[i];
          StringGrid1->Cells[1][i+1] = "";
          StringGrid1->Cells[2][i+1] = "";
        }
        FlagAutoTimer = 1; // ����, ����������� � �������
        return;
      }
      FlagAutoTimer = 0;
    } // end if (FlagAutoTimer == 1)
    // ==>> ==>> ==>>
    AutoTimer++;
    if ( AutoTimer == 1 )
    {
      if ( f_Out32 == true )
      {
        pOut32( AddrLPTPort, (short)(ptrBD) );
      }
    }
    if ( FlagDebug > 1 )
    {
      sprintf( text, "AutoTimer = %d; ptrBD = %d", AutoTimer, ptrBD );
      Memo_For_Print_Errors->Lines->Add( GetCurrentTime() + text );
    }
    if ( AutoTimer == CisloItera ) // CisloItera - ���������� ���������� ��� �������� ������� ��
    {
      FlagAutoTimer = 1; // ��������� ��
      AutoTimer = 0;
      Prot->Reset(); // ������������� � ����� ������ �� ���������� ��
    }
  } // end if (FlagAutoOpros == true)
  //   ===>>
  Cprw->Resume(); // ������������ �����
  //   <<===
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_StartClick(TObject *Sender)
{
  int i;
  int Flag;
  
  Cprw->flagSostoyaniya = 1;
  for ( i = 0; i < 8; i++ )
  {
    StringGrid1->Cells[1][i+1] = "";
    StringGrid1->Cells[2][i+1] = "";
  }
  ComboBox_NomBD->ItemIndex = 0;
  if ( FlagAutoOpros == false ) //���� ��� ����������� ��������� ������ OpenBD
  {
    ArrBD[8-1] = (unsigned char)CheckBox_Vybor_BD08->Checked;
    ArrBD[7-1] = (unsigned char)CheckBox_Vybor_BD07->Checked;
    ArrBD[6-1] = (unsigned char)CheckBox_Vybor_BD06->Checked;
    ArrBD[5-1] = (unsigned char)CheckBox_Vybor_BD05->Checked;
    ArrBD[4-1] = (unsigned char)CheckBox_Vybor_BD04->Checked;
    ArrBD[3-1] = (unsigned char)CheckBox_Vybor_BD03->Checked;
    ArrBD[2-1] = (unsigned char)CheckBox_Vybor_BD02->Checked;
    ArrBD[1-1] = (unsigned char)CheckBox_Vybor_BD01->Checked;
    for ( i = 0; i < 8; i++ )
    {
      ArrBD_loop[i] = ArrBD[i];
    }
    Flag = 0;
    for ( i = 0; i < 8; i++ )
    {
      if ( ArrBD[i] == 1 )
      {
        Flag = 1;
      }
    }
    if ( Flag == 0 )
    {
      if ( FlagDebug > 0 )
      {
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "�� ������� �� ������ ��");
        ShowMessage("�� ������� �� ������ ��");
      }
      return; // ��� �� ������ ���������� ��
    }
    ErrorCode = RSConnect( ComboBox_NomComPort->Text.c_str() ); // ������� ����
    if ( ErrorCode == 0 ) // ���� ���� �������� ��� ��� ��� ������
    {
      //Prot->AddrBD = StrToInt(SpinEdit_AddrBD->Text);
      Button_Start->Caption = "Stop";
      FlagAutoOpros = true;
      CheckBox_Vybor_BD08->Enabled = false;
      CheckBox_Vybor_BD07->Enabled = false;
      CheckBox_Vybor_BD06->Enabled = false;
      CheckBox_Vybor_BD05->Enabled = false;
      CheckBox_Vybor_BD04->Enabled = false;
      CheckBox_Vybor_BD03->Enabled = false;
      CheckBox_Vybor_BD02->Enabled = false;
      CheckBox_Vybor_BD01->Enabled = false;
      Button_OpenBD->Enabled = false;
      ComboBox_NomBD->Enabled = false;
      ComboBox_NomComPort->Enabled = false;
      SpinEdit_AddrBD->Enabled = false;
      RadioGroup_VyborProtokola->Enabled = false;
      // ===
      Button_WriteToBD->Enabled = false;
      Button_UpdateComPortsList->Enabled = false;
      Button_OpenBD_msek->Enabled = false;
      Button_ARCH->Enabled = false;
      Button_Puason->Enabled = false;
      Button_Imp2sek->Enabled = false;
      RadioGroup_Povtor->Enabled = false;
      CheckBox_All->Enabled = false;      

      FlagAutoTimer = 1; // ����, ����������� � �������
      AutoTimer = 0; // ���������, ����������� � �������
      Timer1->Interval = TimerInterval;
      Timer1->Enabled = true;
      if ( f_Out32 == true )
      {
        pOut32( AddrLPTPort, (short)(-1) ); // ��������� ��� ��
      }
    }
    else // if RSConnect(Prot) != 0
    {
      if ( FlagDebug > 0 )
      {
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ �������� �����");
        ShowMessage("������ �������� �����");
      }
      RSDisConnect(); // ������� ���-����, ���� �� ��� ������
      ClearEdit_1();
      return;
    }
  }
  else // if (FlagAutoOpros == true)
  {
    FlagAutoOpros = false;
    CheckBox_Vybor_BD08->Enabled = true;
    CheckBox_Vybor_BD07->Enabled = true;
    CheckBox_Vybor_BD06->Enabled = true;
    CheckBox_Vybor_BD05->Enabled = true;
    CheckBox_Vybor_BD04->Enabled = true;
    CheckBox_Vybor_BD03->Enabled = true;
    CheckBox_Vybor_BD02->Enabled = true;
    CheckBox_Vybor_BD01->Enabled = true;
    Button_OpenBD->Enabled = true;
    ComboBox_NomBD->Enabled = true;
    ComboBox_NomComPort->Enabled = true;
    RadioGroup_VyborProtokola->Enabled = true;
    Button_Start->Caption = "Start";
    SpinEdit_AddrBD->Enabled = true;
    Timer1->Enabled = false;
    // ===
    Button_WriteToBD->Enabled = bFlag_Button_WriteToBD;
    Button_UpdateComPortsList->Enabled = true;
    Button_OpenBD_msek->Enabled = true;
    Button_ARCH->Enabled = true;
    Button_Puason->Enabled = true;
    Button_Imp2sek->Enabled = true;
    RadioGroup_Povtor->Enabled = true;
    CheckBox_All->Enabled = true;

    ErrorCode = Prot->RSDisConnect(); // ������� ����
    if ( ErrorCode == 0 )
    {
      if ( FlagDebug > 0 )
      {
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "���� ������");
      }
    }
    if ( f_Out32 == true )
    {
      pOut32( AddrLPTPort, (short)(-1) ); // ��������� ��� ��
    }
  }       
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Timer2Timer(TObject *Sender)
{
  short shVar;
  Timer2->Enabled = false;

  switch ( iFlagTimer2 )
  {
  case 1:
    shVar = static_cast<short>( ComboBox_NomBD->ItemIndex - 1 );
    if ( f_Out32 == true )
    {
      pOut32( AddrLPTPort, shVar );
    }
    else
    {
      if ( FlagDebug > 0 )
      {
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������: ������� Out32 �� ������� (timer2)");
      }
    }
    break;
  case 2:
    PageControl_ModBus_Settings->ActivePageIndex = iAP;
    break;
  }
  iFlagTimer2 = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::RadioGroup_VyborProtokolaClick(
      TObject *Sender)
{
  flagModbusProtokol = RadioGroup_VyborProtokola->ItemIndex;
  if ( RadioGroup_VyborProtokola->ItemIndex == 0 ) // ������ ��������: "9 ������"
  {
    ComPort_Or_TcpIp(true);

    Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ��������: \"9 ������\"");
    Panel_MoxaSettingsDisplay->Caption = "���� \"MOXA\", �� \"RealCOM\"";

    ButtonSearch->Enabled = false;
    Button_SaveAddr->Enabled = false;
    SpinEdit_AddrBD->Text = "63";
    //CheckBox_Proshivka->Enabled = false;
    // ���������� ������������� (������ �� ����������� �������),
    // ������� ����� �������, ����� �������� ���� �� �������
    Prot->KolVoPodinterval = 5;

    // 14.10.2014 <<===
    // 28.02.2015 ===>>
    CheckBox_speed->Enabled = true;
    //!CheckBox_TCP->Enabled = false;
    Cprw->SetTcpFlag( false );
    // 28.02.2015 <<===
  }
  if ( RadioGroup_VyborProtokola->ItemIndex == 1 || // ModBus RTU
       RadioGroup_VyborProtokola->ItemIndex == 2 || // ModBus TCP
       RadioGroup_VyborProtokola->ItemIndex == 3 ) // ModBus RTU (TCP/IP)
  {
    Prot->KolVoPodinterval = 4;
    // 28.02.2015 ===>>
    CheckBox_speed->Enabled = false;
    //CheckBox_TCP->Enabled = true;
    // 28.02.2015 <<===

    if ( RadioGroup_VyborProtokola->ItemIndex == 1 ) // ModBus RTU
    {
      ComPort_Or_TcpIp(true);

      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ��������: \"ModBus RTU\"");
      Panel_MoxaSettingsDisplay->Caption = "���� \"MOXA\", �� \"RealCOM\"";

      Cprw->SetTcpFlag( false );
    }
    if ( RadioGroup_VyborProtokola->ItemIndex == 2 ) // ModBus TCP
    {
      ComPort_Or_TcpIp(false);

      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ��������: \"ModBus TCP\"");
      if (Prot->newProsivka == true)
      {
        Panel_MoxaSettingsDisplay->Caption = "\"MOXA\" �� ���'� ��� ����������� ����� (230 400 ���/�.)";
      }
      else
      {
        Panel_MoxaSettingsDisplay->Caption = "\"MOXA\" �� ���'� ��� ����������� ����� (57 600 ���/�.)";
      }
      Cprw->SetTcpFlag( true );
      CheckBox_Enabled_Write_TCP->Checked = false;
    }
    if ( RadioGroup_VyborProtokola->ItemIndex == 3 ) // ModBus RTU (TCP/IP)
    {
      ComPort_Or_TcpIp(false);

      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ��������: \"ModBus RTU (TCP/IP)\"");
      if (Prot->newProsivka == true)
      {
        Panel_MoxaSettingsDisplay->Caption = "\"MOXA\" ������ ���� \"TCP Server\" (230 400 ���/�.)";
      }
      else
      {
        Panel_MoxaSettingsDisplay->Caption = "\"MOXA\" ������ ���� \"TCP Server\" (57 600 ���/�.)";
      }

      Cprw->SetTcpFlag( true );
    }

    ButtonSearch->Enabled = bFlagDE;
    Button_SaveAddr->Enabled = bFlagDE;
    
    SpinEdit_AddrBD->Text = Value_Addr_BD;
    // ���������� ������������� (������ �� ����������� �������),
    // ������� ����� �������, ����� �������� ���� �� �������

    // 14.10.2014 ===>>
    //CheckBox_TCP->Enabled = true;
  }

  Prot->flagModbusProtokol = flagModbusProtokol;
  Prot->flagSpeed = CheckBox_speed->Checked;
  Prot->Data.count = 0;

  if ( bFlagWyborProtokola == false )
  {
    return; // �� ����� ��������� � ��������� ��� ����
  }
  ErrorCode = Prot->RSDisConnect(); // ������� ���-����, ���� �� ������
  if ( ErrorCode == 0 )
  {
    if (FlagDebug > 0)
    {
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "���� ������");
    }
  }       
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::RadioGroup_PovtorClick(TObject *Sender)
{
  if ( RadioGroup_Povtor->ItemIndex == 0 )
  {
    bFlagPovtora = false; // = false - ��������� 1 ���, = true - ��������� ���������
    Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "��������� 1 ���");
  }
  if (RadioGroup_Povtor->ItemIndex == 1)
  {
    bFlagPovtora = true;
    Memo_For_Print_Errors->Lines->Add( GetCurrentTime() + "��������� � �����" );
  }        
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::CheckBox_AllClick(TObject *Sender)
{
  if ( CheckBox_All->Checked == true )
  {
    CheckBox_Vybor_BD01->Checked = true;
    CheckBox_Vybor_BD02->Checked = true;
    CheckBox_Vybor_BD03->Checked = true;
    CheckBox_Vybor_BD04->Checked = true;
    CheckBox_Vybor_BD05->Checked = true;
    CheckBox_Vybor_BD06->Checked = true;
    CheckBox_Vybor_BD07->Checked = true;
    CheckBox_Vybor_BD08->Checked = true;
  }
  else
  {
    CheckBox_Vybor_BD01->Checked = false;
    CheckBox_Vybor_BD02->Checked = false;
    CheckBox_Vybor_BD03->Checked = false;
    CheckBox_Vybor_BD04->Checked = false;
    CheckBox_Vybor_BD05->Checked = false;
    CheckBox_Vybor_BD06->Checked = false;
    CheckBox_Vybor_BD07->Checked = false;
    CheckBox_Vybor_BD08->Checked = false;
  }       
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_OpenBD_msekClick(TObject *Sender)
{
  DecodeTime( Time(), Hour1, Min1, Sec1, MSec1 );
  varTime1 = (Hour1 * (60 * 60) + Min1 * (60) + Sec1) * 1000 + MSec1;
  if ( bFlagButton_OpenBD_msek == false ) //���� ��� ����������� ��������� ������ OpenBD_msek
  {
    ErrorCode = RSConnect( ComboBox_NomComPort->Text.c_str() );
    if ( ErrorCode == 0 ) // ���� ���� �������� ��� ��� ��� ������
    {
      Prot->AddrBD = StrToInt( SpinEdit_AddrBD->Text );
      Button_OpenBD_msek->Caption = "��������";
      SpinEdit_AddrBD->Enabled = false;
      Button_Start->Enabled = false;
      ComboBox_NomComPort->Enabled = false;
      RadioGroup_VyborProtokola->Enabled = false;
      Button_OpenBD->Enabled = false;
      bFlagButton_OpenBD_msek = true;
      // ===
      Button_WriteToBD->Enabled = false;
      Button_UpdateComPortsList->Enabled = false;
      Timer1->Interval = TimerInterval; // 150 ��
      Timer1->Enabled = true;
    }
    else
    {
      RSDisConnect(); // ������� ���-����, ���� �� ��� ������
      ClearEdit_1();
      ClearEdit_2();
      return;
    }
  }
  else // if (bFlagButton_OpenBD_msek == true)
  {
    Button_OpenBD_msek->Caption = "������� ��";
    bFlagButton_OpenBD_msek = false; // ���� ��� ����������� ��������� ������ OpenBD
    Timer1->Enabled = false;
    SpinEdit_AddrBD->Enabled = true;
    Button_Start->Enabled = true;
    ComboBox_NomComPort->Enabled = true;
    RadioGroup_VyborProtokola->Enabled = true;
    Button_OpenBD->Enabled = true;
    // ===
    Button_WriteToBD->Enabled = bFlag_Button_WriteToBD;
    Button_UpdateComPortsList->Enabled = true;
    RSDisConnect(); // ������� ����
  }       
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_WriteToBDClick(TObject *Sender)
{
  Cprw->flagSostoyaniya = 3;
  bFlagKnopkaZapis = true;
  bFlagChengeKolTik = true;
  bFlagChengeKolTikSpectr = true;
}
//---------------------------------------------------------------------------
//--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->--->---
// ���������� ����, � ������ �������� ���������� ������
// ��� ������, ��� ��������� �������� �������� ������ (������� � �������)
//int dia_atof( float * fVar, char * chStr );
//---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---<---
void __fastcall TForm_82_Start::Edit_2_Col3_Row4Change(TObject *Sender)
{
  int iTmp;
  float flTmp;
  if (RadioGroup_KOD->ItemIndex == 0)
  {
    return;
  }
  if ( ( Edit_2_Col3_Row4->Text.Length() != 0 ) && ( bFlagButton_ReadFromBD == false ) )
  {
    iTmp = dia_atof( &flTmp, Edit_2_Col3_Row4->Text.c_str() );
    if ( iTmp != 0 )
    {
      Edit_2_Col2_Row4->Text = "";
      Edit_2_Col3_Row4->Color = clRed;
      return;
    }
    Prot->Data.dbDNUZ = flTmp; // ���������� float � double
    Edit_2_Col2_Row4->Text =
      IntToStr((int)(CheckBox_Diskr->Checked ?
      dnu2code1(Prot->Data.dbDNUZ) : dnu2code0(Prot->Data.dbDNUZ) ));
    if ( Edit_2_Col3_Row4->Color != clWindow )
    {
      Edit_2_Col3_Row4->Color = clWindow;
    }
  }
  if ( Edit_2_Col3_Row4->Text.Length() == 0 )
  {
    Edit_2_Col2_Row4->Text = "";
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Edit_2_Col3_Row5Change(TObject *Sender)
{
  int iTmp;
  float flTmp;
  if (RadioGroup_KOD->ItemIndex == 0)
  {
    return;
  }
  if ( ( Edit_2_Col3_Row5->Text.Length() != 0 ) && ( bFlagButton_ReadFromBD == false ) )
  {
    iTmp = dia_atof( &flTmp, Edit_2_Col3_Row5->Text.c_str() );
    if ( iTmp != 0 )
    {
      Edit_2_Col2_Row5->Text = "";
      Edit_2_Col3_Row5->Color = clRed;
      return;
    }
    Prot->Data.dbDVUZ = flTmp; // ���������� float � double
    Edit_2_Col2_Row5->Text =
      IntToStr((int)(CheckBox_Diskr->Checked ?
      dnu2code1(Prot->Data.dbDVUZ) : dnu2code0(Prot->Data.dbDVUZ) ));
    if ( Edit_2_Col3_Row5->Color != clWindow )
    {
      Edit_2_Col3_Row5->Color = clWindow;
    }
  }
  if ( Edit_2_Col3_Row5->Text.Length() == 0 )
  {
    Edit_2_Col2_Row5->Text = "";
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::RadioGroup_KODClick(TObject *Sender)
{
  // ����� ����� ��� - 0, �������� - 1 (��������� ���������� ��)
  if (RadioGroup_KOD->ItemIndex == 0)
  {
    Edit_2_Col2_Row4->Color = clWindow;
    Edit_2_Col2_Row4->ReadOnly = false;
    Edit_2_Col3_Row4->Color = clMoneyGreen;
    Edit_2_Col3_Row4->ReadOnly = true;
    Edit_2_Col2_Row5->Color = clWindow;
    Edit_2_Col2_Row5->ReadOnly = false;
    Edit_2_Col3_Row5->Color = clMoneyGreen;
    Edit_2_Col3_Row5->ReadOnly = true;
    //==\\Edit_2_Col2_Row12->Color = clWindow;
    //==\\==Edit_2_Col2_Row12->ReadOnly = false;
    //==\\==Edit_2_Col3_Row12->Color = clMoneyGreen;
    Edit_2_Col3_Row12->ReadOnly = true;
    //==\\Edit_2_Col2_Row13->Color = clWindow;
    //==\\Edit_2_Col2_Row13->ReadOnly = false;
    //==\\Edit_2_Col3_Row13->Color = clMoneyGreen;
    Edit_2_Col3_Row13->ReadOnly = true;

    clWin_Edit_2_Col2_Row4 = clWindow;
    clWin_Edit_2_Col3_Row4 = clMoneyGreen;
    clWin_Edit_2_Col2_Row5 = clWindow;
    clWin_Edit_2_Col3_Row5 = clMoneyGreen;

    clWin_Edit_2_Col2_Row12 = clWindow;
    clWin_Edit_2_Col3_Row12 = clMoneyGreen;
    clWin_Edit_2_Col2_Row13 = clWindow;
    clWin_Edit_2_Col3_Row13 = clMoneyGreen;
  }
  if (RadioGroup_KOD->ItemIndex == 1)
  {
    Edit_2_Col3_Row4->Color = clWindow;
    Edit_2_Col3_Row4->ReadOnly = false;
    Edit_2_Col2_Row4->Color = clMoneyGreen;
    Edit_2_Col2_Row4->ReadOnly = true;
    Edit_2_Col3_Row5->Color = clWindow;
    Edit_2_Col3_Row5->ReadOnly = false;
    Edit_2_Col2_Row5->Color = clMoneyGreen;
    Edit_2_Col2_Row5->ReadOnly = true;
    Edit_2_Col3_Row12->Color = clWindow;
    Edit_2_Col3_Row12->ReadOnly = false;
    //==\\Edit_2_Col2_Row12->Color = clMoneyGreen;
    //==\\Edit_2_Col2_Row12->ReadOnly = true;
    Edit_2_Col3_Row13->Color = clWindow;
    Edit_2_Col3_Row13->ReadOnly = false;
    //==\\Edit_2_Col2_Row13->Color = clMoneyGreen;
    //==\\Edit_2_Col2_Row13->ReadOnly = true;

    clWin_Edit_2_Col3_Row4 = clWindow;
    clWin_Edit_2_Col2_Row4 = clMoneyGreen;
    clWin_Edit_2_Col3_Row5 = clWindow;
    clWin_Edit_2_Col2_Row5 = clMoneyGreen;

    clWin_Edit_2_Col3_Row12 = clWindow;
    clWin_Edit_2_Col2_Row12 = clMoneyGreen;
    clWin_Edit_2_Col3_Row13 = clWindow;
    clWin_Edit_2_Col2_Row13 = clMoneyGreen;
  }       
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Edit_2_Col2_Row4Change(TObject *Sender)
{ // �������� ��� ��������*
  unsigned long ulTemp;
  double dbTemp;
  char chText[16];
  if ( RadioGroup_KOD->ItemIndex == 1 ) // ��������
  {
    return;
  }
  try // ���
  {
    if ( Edit_2_Col2_Row4->Text.Length() != 0 )
    {
      ulTemp = StrToInt( Edit_2_Col2_Row4->Text ); // �������� ������������ � EEPROM
      dbTemp = CheckBox_Diskr->Checked ? code2dnu1( ulTemp ) : code2dnu0( ulTemp );
      sprintf ( chText, "%.*f", tochnost_DNU, dbTemp  );
      for ( int i = 0; chText[i] != 0; i++ )
      {
        if ( chText[i] == '.' )
        {
          chText[i] = ',';
        }
      }
      Edit_2_Col3_Row4->Text = chText;
    }
    if ( Edit_2_Col2_Row4->Text.Length() == 0 )
    {
      Edit_2_Col3_Row4->Text = "";
    }
    if ( Edit_2_Col2_Row4->Color != clWindow )
    {
      Edit_2_Col2_Row4->Color = clWindow;
    }
  }
  catch (EConvertError*)
  {
    Edit_2_Col3_Row4->Text = "";
    Edit_2_Col2_Row4->Color = clRed;
  }      
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Edit_2_Col2_Row5Change(TObject *Sender)
{ // �������� ��� ��������*
  unsigned long ulTemp;
  double dbTemp;
  char chText[16];
  if ( RadioGroup_KOD->ItemIndex == 1 )
  {
    return;
  }
  try
  {
    if ( Edit_2_Col2_Row5->Text.Length() != 0 )
    {
      ulTemp = StrToInt( Edit_2_Col2_Row5->Text ); // �������� ������������ � EEPROM
      dbTemp = CheckBox_Diskr->Checked ? code2dvu1( ulTemp ) : code2dvu0( ulTemp );
      sprintf ( chText, "%.*f", tochnost_DVU, dbTemp  );
      for ( int i = 0; chText[i] != 0; i++ )
      {
        if ( chText[i] == '.' )
        {
          chText[i] = ',';
        }
      }
      Edit_2_Col3_Row5->Text = chText;
    }
    if ( Edit_2_Col2_Row5->Text.Length() == 0 )
    {
      Edit_2_Col3_Row5->Text = "";
    }
    if ( Edit_2_Col2_Row5->Color != clWindow )
    {
      Edit_2_Col2_Row5->Color = clWindow;
    }
  }
  catch (EConvertError*)
  {
    Edit_2_Col3_Row5->Text = "";
    Edit_2_Col2_Row5->Color = clRed;
  }       
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Edit_2_Col3_Row12Change(TObject *Sender)
{
  int iTmp;
  float flTmp;
  if (RadioGroup_KOD->ItemIndex == 0)
  {
    return;
  }
  // 28.09.2015
  if ( (Edit_2_Col3_Row12->Text.Length() != 0) && (bFlagButton_ReadFromBD == false) )
  {
    iTmp = dia_atof( &flTmp, Edit_2_Col3_Row12->Text.c_str() );
    if ( iTmp != 0 )
    {
    //==\\  Edit_2_Col2_Row12->Text = "";
    //==\\  Edit_2_Col3_Row12->Color = clRed;
      return;
    }
    Prot->Data.dbm_ulU0Z = flTmp;
    Prot->Data.m_iU0 = static_cast<int>(Prot->Data.dbm_ulU0Z + 0.5);
    if ( Edit_2_Col3_Row12->Color != clWindow )
    {
      Edit_2_Col3_Row12->Color = clWindow;
    }
    //==\\Edit_2_Col2_Row12->Text = IntToStr(Prot->Data.m_iU0);
  }
  //==\\if ( Edit_2_Col3_Row12->Text.Length() == 0 )
  //==\\{
  //==\\  Edit_2_Col2_Row12->Text = "";
  //==\\}
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Edit_2_Col3_Row13Change(TObject *Sender)
{
  int iTmp;
  float flTmp;
  if (RadioGroup_KOD->ItemIndex == 0)
  {
    return;
  }
  // 28.09.2015
  if ( (Edit_2_Col3_Row13->Text.Length() != 0) && (bFlagButton_ReadFromBD == false) )
  {
    iTmp = dia_atof( &flTmp, Edit_2_Col3_Row13->Text.c_str() );
    if ( iTmp != 0 )
    {
      //==\\Edit_2_Col2_Row13->Text = "";
      //==\\Edit_2_Col3_Row13->Color = clRed;
      return;
    }
    Prot->Data.dbm_ulUZ = flTmp;
    Prot->Data.m_iU = static_cast<int>(Prot->Data.dbm_ulUZ + 0.5);
    if ( Edit_2_Col3_Row13->Color != clWindow )
    {
      Edit_2_Col3_Row13->Color = clWindow;
    }
    //==\\Edit_2_Col2_Row13->Text = IntToStr(Prot->Data.m_iU);
  }
  if ( Edit_2_Col3_Row13->Text.Length() == 0 )
  {
    //==\\Edit_2_Col2_Row13->Text = "";
  }
}
//---------------------------------------------------------------------------
/*
void __fastcall TForm_82_Start::Edit_2_Col2_Row12Change(TObject *Sender)
{
  if (RadioGroup_KOD->ItemIndex == 1)
  {
    return;
  }
  try
  {
    if (Edit_2_Col2_Row12->Text.Length() != 0)
    {
      Prot->Data.m_iU0 = StrToInt(Edit_2_Col2_Row12->Text);
      Prot->Data.dbm_ulU0Z = static_cast<float>(Prot->Data.m_iU0);
      Edit_2_Col3_Row12->Text = FloatToStr(Prot->Data.dbm_ulU0Z);
    }
    if (Edit_2_Col2_Row12->Text.Length() == 0)
    {
      Edit_2_Col3_Row12->Text = "";
    }
    if ( Edit_2_Col2_Row12->Color != clWindow )
    {
      Edit_2_Col2_Row12->Color = clWindow;
    }
  }
  catch (EConvertError*)
  {
    Edit_2_Col3_Row12->Text = "";
    Edit_2_Col2_Row12->Color = clRed;
  }
}
*/
//---------------------------------------------------------------------------
/*
void __fastcall TForm_82_Start::Edit_2_Col2_Row13Change(TObject *Sender)
{
  if (RadioGroup_KOD->ItemIndex == 1)
  {
    return;
  }
  try
  {
    if ( Edit_2_Col2_Row13->Text.Length() != 0 )
    {
      Prot->Data.m_iU = StrToInt(Edit_2_Col2_Row13->Text);
      Prot->Data.dbm_ulUZ = static_cast<float>(Prot->Data.m_iU);
      Edit_2_Col3_Row13->Text = FloatToStr(Prot->Data.dbm_ulUZ);
    }
    if ( Edit_2_Col2_Row13->Text.Length() == 0 )
    {
      Edit_2_Col3_Row13->Text = "";
    }
    if ( Edit_2_Col2_Row13->Color != clWindow )
    {
      Edit_2_Col2_Row13->Color = clWindow;
    }
  }
  catch (EConvertError*)
  {
    Edit_2_Col3_Row13->Text = "";
    Edit_2_Col2_Row13->Color = clRed;
  }      
}
*/
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Edit_2_Col2_Row7Change(TObject *Sender)
{
  static UINT auiPwmNom2PwmMin[] =
  {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,               // 00...09
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,               // 10...19
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,               // 20...29
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,               // 30...39
    0, 0, 0, 0, 0, 8, 8, 8, 8, 8,               // 40...49
    8, 8, 8, 8, 8, 8, 8, 9, 9, 9,               // 50...59
    10, 10, 10, 11, 11, 11, 12, 12, 13, 13,     // 60...69
    13, 14, 14, 15, 15, 16, 16, 17, 17, 18,     // 70...79
    18, 18, 19, 19, 20, 20, 21, 21, 22, 22,     // 80...89
    23, 24, 24, 24, 25, 25, 26, 26, 27, 28,     // 90...99
    29,                                         // 100..
  };
  if ( Edit_2_Col2_Row7->Text.Length() != 0 )
  {
    try
    {
      int uhi = StrToInt(Edit_2_Col2_Row7->Text); // ������������ ���'� ��������
      if (uhi < 45)
      {
        Edit_2_Col2_Row9->Text = "800"; // ������ ��� �����������
        return;
      }
      if (uhi > 100)
      {
        Edit_2_Col2_Row9->Text = "2900"; // ������ ��� �����������
        return;
      }
      Edit_2_Col2_Row9->Text = IntToStr((int)auiPwmNom2PwmMin[uhi] * 100); // ������ ��� �����������
    }
    catch (EConvertError*)
    {
      Edit_2_Col2_Row9->Text = "";
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_Clear_Memo_ScanClick(TObject *Sender)
{
  Memo_SkanBD->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::CheckBox_DiskrClick(TObject *Sender)
{
  int DNU, DVU;
  try
  {
    Edit_2_Col3_Row4->OnChange = NULL;
    if ( Edit_2_Col2_Row4->Text.Length() != 0 )
    {
      DNU = StrToInt(Edit_2_Col2_Row4->Text);
      Edit_2_Col3_Row4->Text =
          FloatToStrF(CheckBox_Diskr->Checked ?
          code2dnu1(DNU) : code2dnu0(DNU), ffGeneral, 2 /* ��������. ����� */, 8 );
    }
  }
  catch (EConvertError*)
  {
    Edit_2_Col3_Row4->Text = "";
  }
  Edit_2_Col3_Row4->OnChange = Edit_2_Col3_Row4Change;
  try
  {
    Edit_2_Col3_Row5->OnChange = NULL;
    if ( Edit_2_Col2_Row5->Text.Length() != 0 )
    {
      DVU = StrToInt(Edit_2_Col2_Row5->Text);
      Edit_2_Col3_Row5->Text = 
          FloatToStrF(CheckBox_Diskr->Checked ?
          code2dnu1(DVU) : code2dnu0(DVU), ffGeneral, 2 /* ��������. ����� */, 8 );
    }
  }
  catch (EConvertError*)
  {
    Edit_2_Col3_Row5->Text = "";
  }
  Edit_2_Col3_Row5->OnChange = Edit_2_Col3_Row5Change;     
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_2_Col4_Row4_5Click(TObject *Sender)
{
  if ( RadioGroup_KOD->ItemIndex == 0 ) // ���
  {
    Edit_2_Col2_Row4->Text = IntToStr( iVar_Edit_2_Col2_Row4 /*115*/ ); // iVar_Edit_2_Col2_Row4
    Edit_2_Col2_Row5->Text = IntToStr( iVar_Edit_2_Col2_Row5 /*687*/ ); // iVar_Edit_2_Col2_Row5
  }
  else if ( RadioGroup_KOD->ItemIndex == 1 )
  {
    // fVar_Edit_2_Col3_Row4
    Edit_2_Col3_Row4->Text = FloatToStrF( fVar_Edit_2_Col3_Row4 /*0.154*/, ffGeneral, tochnost_DNU /* �������� */, 8 /* ����� ���� */ );
    // fVar_Edit_2_Col3_Row5
    Edit_2_Col3_Row5->Text = FloatToStrF( fVar_Edit_2_Col3_Row5 /*0.922*/, ffGeneral, tochnost_DVU /* �������� */, 8 /* ����� ���� */ );
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_2_Col4_Row6_10Click(TObject *Sender)
{
  Edit_2_Col2_Row6->Text = IntToStr( iVar_Edit_2_Col2_Row6 /*3000*/); // iVar_Edit_2_Col2_Row6
  Edit_2_Col2_Row7->Text = IntToStr( iVar_Edit_2_Col2_Row7 /*90*/); // iVar_Edit_2_Col2_Row7
  Edit_2_Col2_Row8->Text = IntToStr( iVar_Edit_2_Col2_Row8 /*2600*/); // iVar_Edit_2_Col2_Row8
  Edit_2_Col2_Row9->Text = IntToStr( iVar_Edit_2_Col2_Row9 /*2300*/); // iVar_Edit_2_Col2_Row9
  //Edit_2_Col2_Row10->Text = IntToStr( iVar_Edit_2_Col2_Row10 /*225*/); // iVar_Edit_2_Col2_Row10
}
//---------------------------------------------------------------------------
bool TForm_82_Start::AutoPodborProverka()
{
  bool bFlagError;
  bFlagError = false;
  try
  {
    if ( Edit_2_Col3_Row13->Text.Length() != 0 )
    {
      m_fltU_temp = StrToFloat( Edit_2_Col3_Row13->Text ); // ���������� �����������*
      m_iU_temp = U2Code( m_fltU_temp );
    }
    else
    {
      bFlagError = true; // ������
    }
    if ( Edit_2_Col3_Row12->Text.Length() != 0 )
    {
      m_fltU0_temp = StrToFloat( Edit_2_Col3_Row12->Text ); // ���������� ��� ������� ������������ ���
      m_iU0_temp = U2Code( m_fltU0_temp );
    }
    else
    {
      bFlagError = true;
    }
  }
  catch (EConvertError*)
  {
    bFlagError = true;
  }
  if (bFlagError == true) // ������
  {
    AutoPodborEnd();  
  }
  return !bFlagError;
}
//---------------------------------------------------------------------------
void TForm_82_Start::AutoPodborStart()
{
  Prot->CheckBox_auto_Checked = true;
  // ��������� ����������� ������� �� ������� ��������
  if (
      CheckBox_auto->Checked == true &&
      CheckBox_auto_0_81->Checked == false)
  {
    AutoPodbor_1_Un_2_U81 = 1;
    CheckBox_auto_0_81->Enabled = false;
  }
  if (
      CheckBox_auto->Checked == false &&
      CheckBox_auto_0_81->Checked == true)
  {
    AutoPodbor_1_Un_2_U81 = 2;
    CheckBox_auto->Enabled = false;
  }
  if (
      (CheckBox_auto->Checked == false &&
      CheckBox_auto_0_81->Checked == false) ||
      (CheckBox_auto->Checked == true &&
      CheckBox_auto_0_81->Checked == true)
      )
  {
    // ��������� ��������!!!
    AutoPodbor_1_Un_2_U81 = 3;
  }
  Prot->AutoPodbor_1_Un_2_U81 = this->AutoPodbor_1_Un_2_U81;
  GroupBox_ARCH->Enabled = false;
  Prot->Data.m_fltU = m_fltU_temp;
  Prot->Data.m_iU = m_iU_temp;
  Prot->Data.m_fltU0 = m_fltU0_temp;
  Prot->Data.m_iU0 = m_iU0_temp;
  Prot->auto_State_Flag = 50; // ����� �������������
  Prot->Data.period = Prot->Data.SIM4; // ����� � ���� ��������, ��� ����
  Prot->Data.dlitelnost = Prot->Data.SIM3; // ����� � ���� ��������, ������� ������ ����� ��������... ��� �� �� ���! � ���� ��� ����!
  Prot->Data.KolPopytok = 0; // ���������� ������� 29.09.2015

  // �������� ��� (��� ����� ����������), ���� ���!
  // ������ "Avto" ������� ��������� ���� ��� ���������� ���
  // � ��� ������ � ������ "Avto" �������� �������� ���!!!
}
//---------------------------------------------------------------------------
void TForm_82_Start::AutoPodborEnd()
{
  Prot->CheckBox_auto_Checked = false;
  CheckBox_auto->Checked = false;
  CheckBox_auto_0_81->Checked = false;  
  GroupBox_ARCH->Enabled = true;
  // �������� ����������� ������� �� ������� ��������
  if (AutoPodbor_1_Un_2_U81 == 1) // ������ Un ���������
  {
    CheckBox_auto_0_81->Enabled = true;
  }
  if (AutoPodbor_1_Un_2_U81 == 2) // ������ U81 ���������
  {
    CheckBox_auto->Enabled = true; 
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::CheckBox_autoClick(TObject *Sender)
{
  if ( CheckBox_auto->Checked == true )
  {
    if (!AutoPodborProverka())
    {
      return;
    }
    AutoPodborStart();
  }
  else //==\\ if (CheckBox_auto->Checked == false)
  {
    AutoPodborEnd();
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::CheckBox_DAutoClick(TObject *Sender)
{
  Prot->CheckBox_DAuto_Checked = this->CheckBox_DAuto->Checked; // = true, ���� ������ CheckBox_DAuto ����������

  if (CheckBox_DAuto->Checked == true)
  {
    try
    {
      if (Edit_2_Col3_Row4->Text.Length() != 0)
      {
        Prot->Data.m_fltDac0 = StrToFloat(Edit_2_Col3_Row4->Text);
      }
      Prot->Data.m_iDac0 = Prot->Data.m_fltDac0 / (CheckBox_Diskr->Checked ? 2 * 0.00061 : 0.00061);
      if (Edit_2_Col3_Row5->Text.Length() != 0)
      {
        Prot->Data.m_fltDac1 = StrToFloat(Edit_2_Col3_Row5->Text);
      }
      Prot->Data.m_iDac1 = Prot->Data.m_fltDac1 / (CheckBox_Diskr->Checked ? 2 * 0.00061 : 0.00061);
    }
    catch (EConvertError*)
    {
      Prot->Data.m_fltDac0 = 0;
      Prot->Data.m_iDac0 = 0;
      Prot->Data.m_fltDac1 = 0;
      Prot->Data.m_iDac1 = 0;
      CheckBox_DAuto->Checked = false;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_Clear_Memo_ErrClick(TObject *Sender)
{
  Memo_For_Print_Errors->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::ButtonSearchClick(TObject *Sender)
{
  Cprw->flagSostoyaniya = 2;
  varFrom = StrToInt(SpinEdit_Begin->Text); // varFrom <= varTo
  varTo = StrToInt(SpinEdit_End->Text);
  if ( varFrom > varTo )
  {
    int varSwap;
    // �������� �������� ����������
    varSwap = varFrom;
    varFrom = varTo;
    varTo = varSwap;
    
    SpinEdit_Begin->Value = varFrom;
    SpinEdit_End->Value = varTo;
  }
  if ( FlagButtonSearch == false ) // ���� ��� ����������� ��������� ������ ButtonSearch
  { // ������ �� ������, ������ �
    int var;
    ErrorCode = RSConnect( ComboBox_NomComPort->Text.c_str() ); // ������� ����
    if ( ErrorCode == 0 ) // ���� ���� �������� ��� ��� ��� ������
    {
      FlagButtonSearch = true;
      ButtonSearch->Caption = "����������";
      Button_OpenBD->Enabled = false; // ��������� ������� ������ "�������"
      Button_SaveAddr->Enabled = false; // ��������� ������� ������ "�������� �����"
      RadioGroup_VyborProtokola->Enabled = false; // ��������� ����� ���������
      Button_UpdateComPortsList->Enabled = false; // ��������� ���������� ���-������
      ComboBox_NomComPort->Enabled = false; // ��������� ����� ���-�����

      Button_ARCH->Enabled = false; // ��������� ���
      Button_Puason->Enabled = false; // ��������� �������
      ComboBox_NomBD->Enabled = false; //==\\ 24.01.2016

      //if ( RadioGroup_VyborProtokola->ItemIndex == 1 ) // ������ �������� ModBus
      //{
      //  CheckBox_TCP->Enabled = false;
      //}
    }
    else
    {
      return;
    }
    // ===
    Cprw->Resume(); // ������������ �����
    // ===
  }
  else if ( FlagButtonSearch == true )
  { // ������ ������, "������" �
    FlagButtonSearch = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_UpdateComPortsListClick(
      TObject *Sender)
{
  Button_OpenBD->Enabled = false;
  updatecom();
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_SaveAddrClick(TObject *Sender)
{
  int rc;
  int AddrBD;
  uint16_t AddrReg[1];
  char CArr[100];

  AddrBD = StrToInt( SpinEdit_AddrBD->Text ); // ������ ����� ��
  AddrReg[0] = StrToInt( SpinEdit_ForSaveAddr->Text ); // ����� ����� ��

  ErrorCode = RSConnect( ComboBox_NomComPort->Text.c_str() ); // ������� ����
  if ( ErrorCode == 0 ) // ���� ���� �������� ��� ��� ��� ������
  {
    rc = Prot->write_registers
    (
      AddrBD,
      51, // ����� ��������
      1, // ����� ���������
      AddrReg // ������ ���������
    );
    if (rc < 0)
    {
      //sprintf(CArr, "������ ���������� ������ � ������� write_registers:");
      Memo_SkanBD->Lines->Add("������ ���������� ������ � ������� write_registers:"/*CArr*/);
      if ( rc == -2 )
      {
        sprintf(CArr, "���-�� �������� ���� %d �� ������������� ���������� %d.",
            Prot->err, Prot->MB_length_to_read);
        Memo_SkanBD->Lines->Add(CArr);
      }
      if ( rc == -4 )
      {
        Memo_SkanBD->Lines->Add("������ ������ � EEPROM");
      }
    }
    else
    {
      sprintf(CArr, "����� �� ������ � {%.2d} �� {%.2d}", AddrBD, AddrReg[0]);
      Memo_SkanBD->Lines->Add(CArr);
    }
    RSDisConnect(); // ������� COM-����
  }
  else
  {
    Memo_SkanBD->Lines->Add("������ �������� �����!");
  }    
}
//---------------------------------------------------------------------------
// ������� ����� ������: "���������� � ��"
void __fastcall TForm_82_Start::ClearEdit_1(void)
{
  Edit_Col2_Row4->Clear();
  Edit_Col2_Row5->Clear();
  Edit_Col2_Row6->Clear();
  Edit_Col2_Row7->Clear();
  Edit_Col2_Row8->Clear();
  Edit_Col2_Row9->Clear();
  Edit_Col2_Row10->Clear();
  Edit_Col2_Row11->Clear();
  Edit_Col2_Row12->Clear();
  Edit_Col3_Row2->Clear();
  Edit_Col3_Row3->Clear();
  Edit_Col3_Row4->Clear();
  Edit_Col3_Row5->Clear();
  Edit_Col3_Row6->Clear();
  Edit_Col3_Row7->Clear();
  Edit_Col3_Row8->Clear();
  Edit_Col3_Row9->Clear();
  Edit_Col3_Row11->Clear();
  Edit_Col3_Row12->Clear();
  Edit_Col3_Row13->Clear();
  Edit_Col3_Row14->Clear();
  Edit_Ver01->Clear();
  Edit_Ver02->Clear();
  Edit_Ver03->Clear();
  Edit_Ver04->Clear();
  Edit_SSP_bin->Clear();
  Edit_SSP_hex->Clear();
  Edit_KolTik->Clear();
  StatusBar1->Panels->Items[0]->Text = "";
  StatusBar1->Panels->Items[1]->Text = "";
  StatusBar1->Panels->Items[2]->Text = "";
}
//---------------------------------------------------------------------------
// ������� ����� ������: "��������� ���������� ��"
void __fastcall TForm_82_Start::ClearEdit_2(void)
{
  Edit_2_Col3_Row2->Clear();
  Edit_2_Col3_Row3->Clear();
  Edit_2_Col2_Row4->Clear();
  Edit_2_Col3_Row4->Clear();
  Edit_2_Col2_Row5->Clear();
  Edit_2_Col3_Row5->Clear();
  Edit_2_Col2_Row6->Clear();
  Edit_2_Col2_Row7->Clear();
  Edit_2_Col2_Row8->Clear();
  Edit_2_Col2_Row9->Clear();
  Edit_2_Col2_Row10->Clear();
  Edit_2_Col3_Row11->Clear();
  //==\\Edit_2_Col2_Row12->Clear();
  Edit_2_Col3_Row12->Clear();
  //==\\Edit_2_Col2_Row13->Clear();
  Edit_2_Col3_Row13->Clear();
  Edit_2_Col2_4_Row_14->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::ComboBox_NomBDChange(TObject *Sender)
{
  short ii;
  if ( f_Out32 == true )
  {
    ii = ComboBox_NomBD->ItemIndex - 1;
    pOut32( AddrLPTPort, ii );
  }
  else
  {
    if (FlagDebug > 0)
    {
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������: ������� Out32 �� �������");
    }
  }
  Prot->Reset();
}
//---------------------------------------------------------------------------
// �������������� �������� ����������� �� ���� � ������� �������
//float __fastcall TForm_82_Start::TConvert(int Temper)
//{
//  float g_fltTSlope;
//  float g_fltTOffset;
//  float g_Temper;
//
//  if (Prot->Data.Ver_HEX != 0)
//  {
//    if (Prot->Data.Ver_HEX != 400)
//    {
//      g_fltTSlope = -0.3389;
//      g_fltTOffset = 378.95;
//    }
//    else
//    {
//      g_fltTSlope = -0.714;
//      g_fltTOffset = 486.4;
//    }
//    g_Temper = g_fltTSlope * (float)Temper + g_fltTOffset;
//  }
//  else
//  {
//    g_Temper = 0;
//  }
//  return g_Temper;
//}
//---------------------------------------------------------------------------
unsigned int __fastcall TForm_82_Start::U2Code(double var)
{
  double temp;
  if ( Prot->Data.Ver_HEX != 400 )
  {
    temp = var * 4096 / 2.5 * 0.001;
  }
  else
  {
    temp = var * 4096 / 4.5 * 0.001;
  }
  return static_cast<int>(temp + 0.5);
}
//---------------------------------------------------------------------------
// �������������� ���������� (����������� �� 50-�� ���������) �� ���� � ������
double __fastcall TForm_82_Start::Code2U(int var)
{
  if ( Prot->Data.Ver_HEX != 400 )
  {
    return var * 2.5 / 4096 * 1000;
  }
  else
  {
    return var * 4.5 / 4096 * 1000;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Printing( void )
{
  if ( FlagAutoOpros == true ) // ���� ������ ������ "Start"
  {
    static char str[100];
    sprintf( str, "�� � %d", ptrBD + 1 );

    Memo_For_Print_Errors->Lines->Add( GetCurrentTime() + str );
    ErrorCode = Prot->ReturnVar;    
    if ( ( ErrorCode == 0 ) && ( ErorAuto == false ) )
    {
      if ( Prot->Data.flagFirst == 0 ) // ���� ��� � ���� �������
      {
        StringGrid1->Cells[2][ptrBD+1] = "OK";      
        StringGrid1->Cells[1][ptrBD+1] = IntToStr( (int)Prot->Data.TSchet );
      }
      if ( AutoTimer == CisloItera - 1 )
      {
        StringGrid1->Cells[2][ptrBD+1] = "OK";
        StringGrid1->Cells[1][ptrBD+1] = IntToStr( (int)Prot->Data.TSchet );
      }
    }
    if ( ( ErrorCode != 0 ) && ( AutoTimer == CisloItera/2 - 2 ) ) // ���� ������ ��������� �����, � ���������� ������ �����
    {
      ErorAuto = true; // ���������� ���� ������
      //StringGrid1->Cells[1][ptrBD+1] = "---------";
      //StringGrid1->Cells[2][ptrBD+1] = "- Error -";
    }
    if ( (AutoTimer == CisloItera/2 - 1) && (ErorAuto == true) )
    {
      ErorAuto = false; // ��� ���������� ����� ������ ����� ����� �� ����
      StringGrid1->Cells[1][ptrBD+1] = "---------";
      StringGrid1->Cells[2][ptrBD+1] = "- Error -";
    }
  }
}
//---------------------------------------------------------------------------
int __fastcall TForm_82_Start::OprosBD(void)
{
  if (bFlagWork == true)
  {
    if (FlagDebug > 0)
    {
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������: ������� OprosBD ��� ��������");
    }
    return -1;
  }
  //===
  bFlagWork = true;
  ErrorCode = Prot->ReturnVar;
  //===
  if ( ErrorCode != -1 )
  {
    if ( bFlagChengeKolTik == true )
    {
      bFlagChengeKolTik = false;
      Edit_KolTik->Text = IntToStr((int)Prot->Data.KolTik); // GetTimeInterval, ��
    }
    //=====================================================================
    if ( Prot->Data.flagFirst == 0 )
    {
      if ( FlagDebug > 1 )
      {
        sprintf(Str_err, "�������������� �����: %d", (int)IndAdr);
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + Str_err);
      }
      Edit_Col3_Row2->Text = IntToStr( Prot->Data.IndAdr );
      if ( FlagDebug > 1 )
      {
        sprintf(Str_err, "��������� �����: %d", (int)Prot->Data.IndAdr);
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + Str_err);
      }
      Edit_Col3_Row3->Text = IntToStr( Prot->Data.GrAdr );
      if ( FlagDebug > 1 )
      {
        sprintf(Str_err, "����������� ���: %d", Prot->Data.Temper);
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + Str_err);
      }
      Edit_Col2_Row4->Text = IntToStr((int)Prot->Data.Temper);
      if ( FlagDebug > 1 )
      {
        sprintf(Str_err, "����������� ����.: %.2f", Prot->Data.flTemper);
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + Str_err);
      }
      Edit_Col3_Row4->Text = FormatFloat("0.00", Prot->Data.flTemper);
      if ( FlagDebug > 1 )
      {
        sprintf(Str_err, "���������� ��� (���): %d", Prot->Data.DNU);
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + Str_err);
        sprintf(Str_err, "���������� ��� [�]: %.4f", Prot->Data.dbDNU);
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + Str_err);
      }
      Edit_Col2_Row5->Text = IntToStr((int)Prot->Data.DNU);
      if ( FlagDebug > 1 )
      {
        sprintf(Str_err, "���������� ��� (���): %d", Prot->Data.DVU);
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + Str_err);
        sprintf(Str_err, "���������� ��� [�]: %.4f", Prot->Data.dbDVU);
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + Str_err);
      }
      Edit_Col3_Row5->Text = FormatFloat("0.000", Prot->Data.dbDNU);
      //===
      Edit_Col2_Row6->Text = IntToStr((int)Prot->Data.DVU);
      Edit_Col3_Row6->Text = FormatFloat("0.000", Prot->Data.dbDVU);
      //===
      Edit_Col2_Row7->Text = IntToStr((int)Prot->Data.UhiIsr);
      if (FlagDebug > 1)
      {
        sprintf(Str_err, "���������� ������� ������� (��50) [�]: %.02f", Prot->Data.dbUhiIsr);
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + Str_err);
      }
      Edit_Col3_Row7->Text = FormatFloat("0.0", Prot->Data.dbUhiIsr);
      if ( FlagDebug > 1 )
      {
        sprintf(Str_err, "������������ �������� ��� (���): %d", Prot->Data.SIM3);
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + Str_err);
        sprintf(Str_err, "���������� ������� ������� (��50) (���): %d", Prot->Data.UhiIsr);
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + Str_err);
      }
      Edit_Col2_Row8->Text = IntToStr((int)Prot->Data.SIM3);
      if ( FlagDebug > 1 )
      {
        sprintf(Str_err, "������������ �������� ��� [���.]: %.2f", Prot->Data.dbSIM3);
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + Str_err);
      }
      Edit_Col3_Row8->Text = FormatFloat("0.00", Prot->Data.dbSIM3);
      if ( FlagDebug > 1 )
      {
        sprintf(Str_err, "������ ��� ���������� (���): %d", Prot->Data.SIM4);
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + Str_err);
      }
      Edit_Col2_Row9->Text = IntToStr((int)Prot->Data.SIM4);
      if (FlagDebug > 1)
      {
        sprintf(Str_err, "������ ��� ����������  [���.]: %.2f", Prot->Data.dbSIM4);
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + Str_err);
      }
      Edit_Col3_Row9->Text = FormatFloat("0.00", Prot->Data.dbSIM4);
      if ( FlagDebug > 1 )
      {
        sprintf(Str_err, "��� ���������� ������������ (���): %d", Prot->Data.SIM2);
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + Str_err);
      }
      Edit_Col2_Row10->Text = IntToStr((int)Prot->Data.SIM2);
      if ( FlagDebug > 1 )
      {
        sprintf(Str_err, "������ ���������� (������ = 5) (���): %d", Prot->Data.Ampl);
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + Str_err);
      }
      Edit_Col2_Row11->Text = IntToStr((int)Prot->Data.Ampl);
      if (FlagDebug > 1)
      {
        sprintf(Str_err, "������ ���������� (������ = 5) [�]: %.2f", Prot->Data.dbAmpl);
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + Str_err);
      }
      Edit_Col3_Row11->Text = FormatFloat("0.00", Prot->Data.dbAmpl);
      if (FlagDebug > 1)
      {
        sprintf(Str_err, "�������. ������ ���������� (��50) (���): %d", Prot->Data.LEDAmpRcp);
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + Str_err);
      }
      Edit_Col2_Row12->Text = IntToStr((int)Prot->Data.LEDAmpRcp);
      if (FlagDebug > 1)
      {
        sprintf(Str_err, "�������. ������ ���������� (��50) [�]: %.2f", Prot->Data.dbLEDAmpRcp);
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + Str_err);
      }
      Edit_Col3_Row12->Text = FormatFloat("0.00", Prot->Data.dbLEDAmpRcp);
      // ������� ���� �� 0.2 ���
      if (FlagDebug > 1)
      {
        sprintf(Str_err, "���� � ��: %d", Prot->Data.CountImp);
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + Str_err);
      }
      if (Prot->Data.flagFirst == 0)
      {
        Edit_Col3_Row13->Text = IntToStr((int)Prot->Data.TSchet);
      }

      // ===>> ===>> ===>> 15.10.2019 ===>> ===>> ===>>

      if ( Prot->Data.DoseSupport == IsSupport )
      {
        const int txtSize = 100;
        char text[txtSize];
        double dblDose = static_cast<double>(Prot->Data.Dose);
        dblDose /= 100;
        sprintf(text, "%0.3f", dblDose);
        for (int i = 0; i < txtSize; i++)
        {
          if (text[i] == '.')
          {
            text[i] = ',';          
          }
        }
        Edit_Col3_Row14->Text = text;
      }

      // <<=== <<=== <<=== 15.10.2019 <<=== <<=== <<===

      if (Prot->ErrorCode != 0 && Prot->ErrorCode != 38) // 38 - �� ����� ���� �����
      {
        Prot->NullsToStr_err(); //
        sprintf(Str_err, "ErrorCode: %d (%s)", Prot->ErrorCode, Prot->Str_err);
        Memo_For_Print_Errors->Lines->Add( GetCurrentTime() + Str_err );
      } // END: if ( Prot->Data.flagFirst == 0 )
      if (flagModbusProtokol != 0) // �� "9-�� ������"
      {
        char chString[100];
        sprintf(chString, "����� �� ������� �� [���.]: %d", Prot->Data.TimeZapuskBD);
        StatusBar1->Panels->Items[1]->Text = chString;
      }
    } // END: if ( Prot->Data.flagFirst == 0 )
    ///==========================================================================
    Str_hex = "";
    for(int k = 0; k < 8; k++)
    {
      if( Prot->Data.PSW & MasRez[7-k] )
      {
        Str_hex = Str_hex + "1";
      }
      else
      {
        Str_hex = Str_hex + "0";
      }
    }
    Edit_SSP_bin->Text = Str_hex;
    Edit_SSP_hex->Text = "0x" + IntToHex(Prot->Data.PSW, 2);
    if ( Prot->Data.PSW & MasRez[7] )
    {
      this->Panel_bit7->Color = clGreen;
      this->Panel_bit7_2->Color = clGreen;
    }
    else
    {
      this->Panel_bit7->Color = clRed;
      this->Panel_bit7_2->Color = clRed;
    }
  }
  // ===
  else if ( Prot->ErrorCode != 38 )
  {
    ClearEdit_1(); // �������� ��� ���� �� �����
    ClearEdit_2();
    if (FlagDebug > 0)
    {
      sprintf(Str_err, "ErrorCode: %d (%s)", Prot->ErrorCode, Prot->Str_err);
      Memo_For_Print_Errors->Lines->Add( GetCurrentTime() + Str_err );
      //Memo_For_Print_Errors->Lines->Add( IntToStr(Prot->ErrorCode) + " ���� ��� ������ 10.03.2014" );
    }
  }
  if ( FlagDebug > 0 )
  {
    if(Prot->ErrorCode == 39) // 39 - ����������� ���� ���������� ����� ����� 1-�� ������ ������
    {
      Prot->ErrorCode = 0;
      //!Memo_For_Print_Errors->Lines->Add(Prot->Str_err);
      sprintf(Str_err, "ErrorCode: %d (%s)", Prot->ErrorCode, Prot->Str_err);
      Memo_For_Print_Errors->Lines->Add( GetCurrentTime() + Str_err );
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "����������� ���� ���������� ����� ����� 1-�� ������ ������");
    }
  }
  if ( Prot->auto_State_Flag == -1 )
  {
    char chText[50];
    sprintf( chText, "���������� ������� �������. �� (%d)", Prot->Data.KolPopytok );  // Data.KolPopytok
    Memo_For_Print_Errors->Lines->Add( GetCurrentTime() + chText );
    Prot->auto_State_Flag = 0;
  }
  if ( Prot->auto_State_Flag == 100 )
  {
    Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "���������� ������� �������. �������");
    Prot->auto_State_Flag = 0;
  }
  if ( (Prot->auto_State_Flag != -1) && (Prot->auto_State_Flag != 100) )
  {
    StatusBar1->Panels->Items[2]->Text = "";
  }
  //===>
  if ( Prot->Data.bFlagCount == true )
  {
    Edit_3_Col3_Row1->Text = FormatFloat("0.00", Prot->Data.Sred); // �������� ���� �� 1 ��� �� �����
    Edit_3_Col3_Row2->Text = IntToStr(Prot->Data.SumSchet);
    Edit_3_Col3_Row3->Text = IntToStr(Prot->Data.TimeTSchet_dia);
  }
  //<<===
  if (Prot->Data.bFlagCount == false)
  {
    Button_Sum_Schet->Caption = "�����";
    Button_Set_Reset->Enabled = true;
    CSpinEdit_time_izm->Enabled = true;
  }
  if ( Prot->Data.count == 0 )
  {
    Button_Sum_Schet->Enabled = true; // ����� ������ ������ �����������, ���� cout �� ������ ����� ����
  }
  bFlagWork = false;
  return ErrorCode; // ��� ������ ������
}
//---------------------------------------------------------------------------
int __fastcall TForm_82_Start::RSConnect( const char * device )
{
  Prot->AddrBD = StrToInt(SpinEdit_AddrBD->Text);
  //if ( this->CheckBox_Proshivka->Checked == true ) // ��� �� 84 (��� ModBus �������� 230 400)
  //{
  //  Prot->newProsivka = true;
  //}
  //else // ��� �� 82 (��� ModBus �������� 57 600)
  //{
  //  Prot->newProsivka = false; //
  //}
  if ( Cprw->GetTcpFlag() == true )
  {
    try
    {
      Prot->Data.IP_Port = StrToInt( Edit_IPPort->Text );
    }
    catch ( ... )
    {
      Prot->Data.IP_Port = 502;
    }
    Prot->Data.Addr_BD_TCP = SpinEdit_AddrBD->Value;
    strcpy ( Prot->Data.IP_Addr, Edit_IPAddr->Text.c_str() );
  }
  this->ErrorCode = Prot->RSConnect( ComboBox_NomComPort->Text.c_str() );
  if ( this->ErrorCode == 0 || this->ErrorCode == 2 ) // ���� ���� �������� ��� ��� ��� ������
  {
    if (FlagDebug > 0)
    {
      if (this->ErrorCode == 0)
      {
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "���� ������� ������");
      }
      if (this->ErrorCode == 2)
      {
        this->ErrorCode = 0;
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "���� ��� ��� ������");
      }
    }
    CheckBox_DAuto->Checked = false;
    CheckBox_auto->Checked = false;
    CheckBox_auto_0_81->Checked = false;
    //==\\CheckBox_Proshivka->Enabled = false;
  }
  else // if ErrorCode != 0
  {
    if (FlagDebug > 0)
    {
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ �������� �����: ");
      //Memo_For_Print_Errors->Lines->Add(Prot->Str_err);
    }
    Prot->RSDisConnect(); // ������� ���-����, ���� �� ��� ������
    ClearEdit_1();
    ClearEdit_2();
  }
  return this->ErrorCode;
}
//---------------------------------------------------------------------------
int __fastcall TForm_82_Start::RSDisConnect(void)
{
  ErrorCode = Prot->RSDisConnect(); // ������� ����
  if (ErrorCode == 0)
  {
    if(FlagDebug > 0)
    {
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "���� ������");
      //flagPort = false; // ���� ������
      //flagPort = false; // ���� ������          
    }
  }
  if ( RadioGroup_VyborProtokola->ItemIndex == 1 )
  {
    //==\\CheckBox_Proshivka->Enabled = true; // ������ �������� ������ �� �������� ModBus
    //CheckBox_TCP->Enabled = true;
  }
  CheckBox_DAuto->Checked = false;
  CheckBox_auto->Checked = false;
  CheckBox_auto_0_81->Checked = false;
  return ErrorCode;
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::RSDisConnect2(void)
{
  ErrorCode = Prot->RSDisConnect(); // ������� ����
  if (ErrorCode == 0)
  {
    if(FlagDebug > 0)
    {
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "���� ������");
      flagPort = false; // ���� ������      
    }
  }
  if ( RadioGroup_VyborProtokola->ItemIndex == 1 )
  {
    //==\\CheckBox_Proshivka->Enabled = true; // ������ �������� ������ �� �������� ModBus
    //CheckBox_TCP->Enabled = true;
  }
  CheckBox_DAuto->Checked = false;
  CheckBox_auto->Checked = false;
  CheckBox_auto_0_81->Checked = false;
}
//---------------------------------------------------------------------------
void TForm_82_Start::ZamenaTochky( char * chS )
{
  for ( int i = 0; (chS[i] != 0) && (i < 10); i++ )
  {
    if ( chS[i] == '.' )
    {
      chS[i] = ',';
    }
  }
}
//---------------------------------------------------------------------------
int __fastcall TForm_82_Start::OprosBD_2(void)
{
  double dbTemp;
  char chText[16];

  if ( bFlagWork == true )
  {
    if (FlagDebug > 0)
    {
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������: ������� OprosBD ��� ��������");
    }
    return -1;
  }
  // ===>>
  bFlagWork = true;

  // ����� ����� � ������, �� �� ������ � ���� ����������
  // ���� ���� ��������������� � false
  // ����� �������� ������ (��� ���� ��������� ��� ������ �� ����������) - � true.
  // ������������ ��� ����������� � ���,
  // ��� ������ ���������� �� �������������
  // ��� ������� ����������������� ����� � �����.
  bf_Zabyvchivosti = false;

  Prot->Data.flagSetTimeInterval = false; // ��� ��������� ���� SetTimeInterval(8)
  Prot->Data.flagGetTimeInterval = false; // ��� ��������� ���� SetTimeInterval(8)
  Prot->Data.flagSecond = 1; // ��� ��������� ���� SetTimeInterval(8)
  ErrorCode = Prot->OprosBD_2();
  // <<===
  if ( ErrorCode != -1 )
  {
    if ( Prot->Data.Ver_HEX != 400 )
    {
      //this->Button_2_Col4_Row4_5->Enabled = true;
      //this->Button_2_Col4_Row6_10->Enabled = true;

      iVar_Edit_2_Col2_Row4 = 115;
      iVar_Edit_2_Col2_Row5 = 687;
      fVar_Edit_2_Col3_Row4 = 0.154;
      fVar_Edit_2_Col3_Row5 = 0.922;

      iVar_Edit_2_Col2_Row6 = 3000;
      iVar_Edit_2_Col2_Row7 = 90;
      iVar_Edit_2_Col2_Row8 = 2600;
      iVar_Edit_2_Col2_Row9 = 2300;
      iVar_Edit_2_Col2_Row10 = 225;
    }
    if ( Prot->Data.Ver_HEX == 400 )
    {
      Form_82_Spectr_BD84->Button_Spectr->Enabled = true;
    }

    CheckBox_speed->Checked = false;
    CheckBox_speed->Checked = true;
    Edit_Ver01->Text = Prot->Data.Ver[3];
    Edit_Ver02->Text = Prot->Data.Ver[2];
    Edit_Ver03->Text = Prot->Data.Ver[1];
    Edit_Ver04->Text = Prot->Data.Ver[0];
    if ( FlagDebug > 1 )
    {
      sprintf( Str_err, "������ = %s", Prot->Data.Ver );
      Memo_For_Print_Errors->Lines->Add( GetCurrentTime() + Str_err );
    }
    Edit_2_Col3_Row2->Text = IntToStr((int)Prot->Data.IndAdrZ);
    Edit_2_Col3_Row3->Text = IntToStr((int)Prot->Data.GrpAdrZ);
    Edit_2_Col2_Row4->Text = IntToStr((int)Prot->Data.DNUZ);
    Edit_2_Col2_Row5->Text = IntToStr((int)Prot->Data.DVUZ);

    dbTemp = CheckBox_Diskr->Checked ? code2dnu1( Prot->Data.DNUZ ) : code2dnu0( Prot->Data.DNUZ );
    sprintf ( chText, "%.*f", tochnost_DNU, dbTemp );
    ZamenaTochky( chText ); // ����� � ������ �������� ������� ( ����� ��� �-��� StrToFloat() )
    Edit_2_Col3_Row4->Text = chText;

    dbTemp = CheckBox_Diskr->Checked ? code2dvu1( Prot->Data.DVUZ ) : code2dvu0( Prot->Data.DVUZ );
    sprintf ( chText, "%.*f", tochnost_DVU, dbTemp );
    ZamenaTochky( chText ); // ����� � ������ �������� ������� ( ����� ��� �-��� StrToFloat() )
    Edit_2_Col3_Row5->Text = chText;

    Edit_2_Col2_Row6->Text = IntToStr((int)Prot->Data.LEDAmpZ);
    Edit_2_Col2_Row7->Text = IntToStr((int)Prot->Data.UhiZ);
    Edit_2_Col2_Row8->Text = IntToStr((int)Prot->Data.SIMstartZ);
    Edit_2_Col2_Row9->Text = IntToStr((int)Prot->Data.SIMminZ);
    Edit_2_Col2_Row10->Text = IntToStr((int)Prot->Data.LedZadZ);

    sprintf( chText, "%0.6d", Prot->Data.m_ulSerialNumberZ );
    Edit_2_Col3_Row11->Text = chText;
    // �������� ��������� 2-� �����, (���-�� ��� � 2-� �������������) �� ������ �� ������ ��, � ������ �������� !!
    Edit_2_Col3_Row12->Text = IntToStr((int)Prot->Data.m_ulU0Z); //==\\ �������� � �� ��� ���������� �������� �� ��!!
    Edit_2_Col3_Row13->Text = IntToStr((int)Prot->Data.m_ulUZ); //==\\ �������� � �� ��� ���������� �������� �� ��!!
    Edit_2_Col2_4_Row_14->Text = Prot->Data.m_strStickyNote;
    if ( Prot->flagARCH == 1 )
    {
      RadioButton_ARCH3->Checked = true;
    }
    else if ( Prot->flagARCH == 2 )
    {
      RadioButton_ARCH2->Checked = true;
    }
    else if ( Prot->flagARCH == 3 )
    {
      RadioButton_ARCH1->Checked = true;
    }
    //===//
    if ( Prot->flagUchSv == 1 )
    {
      CheckBox_Diod->Checked = true;
    }
    else if ( Prot->flagUchSv == 2 )
    {
      CheckBox_Diod->Checked = false;
    }
  }
  //==\\ ��� �������������� ������ ������ � ����!!!  
  Button_SaveToFile->Enabled = true;
  bFlagWork = false;
  return ErrorCode; // ��� ������ ������
}
//---------------------------------------------------------------------------
unsigned int __fastcall TForm_82_Start::dnu2code0( double var )
{
  //==\\unsigned int temp;
  double temp; //==\\ 22.06.2015
  if ( Prot->Data.Ver_HEX != 400 )
  {
    temp = ( var / 2.5 * 4096 ) / 1.1;
  }
  else
  {
    temp = ( var / 4.5 * 4096 ) / 1.1;
  }
  return static_cast<int>(temp + 0.5); // ����������;
}
//---------------------------------------------------------------------------
unsigned int __fastcall TForm_82_Start::dvu2code0( double var )
{
  //==\\unsigned int temp;
  double temp; //==\\ 22.06.2015
  if ( Prot->Data.Ver_HEX != 400 )
  {
    temp = ( var / 2.5 * 4096 ) / 1.1;
  }
  else
  {
    temp = ( var / 4.5 * 4096 ) / 1.1;
  }
  return static_cast<int>(temp + 0.5); // ����������
}
//---------------------------------------------------------------------------
unsigned int __fastcall TForm_82_Start::dnu2code1( double var )
{
  //==\\ unsigned int temp;
  double temp; //==\\ 22.06.2015
  if ( Prot->Data.Ver_HEX != 400 )
  {
    temp = ( var / 5.0 * 4096 ) / 1.1;
  }
  else
  {
    temp = ( var / 4.5 * 4096 ) / 1.1;
  }
  return static_cast<int>(temp + 0.5); // ����������
}
//---------------------------------------------------------------------------
unsigned int __fastcall TForm_82_Start::dvu2code1( double var )
{
  //==\\/*unsigned int*/float temp;
  double temp; //==\\ 22.06.2015
  if ( Prot->Data.Ver_HEX != 400 )
  {
    temp = (var / 5.0 * 4096) / 1.1;
  }
  else
  {
    temp = (var / 4.5 * 4096) / 1.1;
  }
  return static_cast<int>(temp + 0.5); // ����������
}
//---------------------------------------------------------------------------
double __fastcall TForm_82_Start::code2dnu0( int var )
{
  if ( Prot->Data.Ver_HEX != 400 )
  {
    return ( var * 2.5 / 4096 ) * 1.1;
  }
  else
  {
    return ( var * 4.5 / 4096 ) * 1.1;
  }
}
//---------------------------------------------------------------------------
double __fastcall TForm_82_Start::code2dvu0( int var )
{
  if ( Prot->Data.Ver_HEX != 400 )
  {
    return ( var * 2.5 / 4096 ) * 1.1;
  }
  else
  {
    return ( var * 4.5 / 4096 ) * 1.1;
  }
}
//---------------------------------------------------------------------------
double __fastcall TForm_82_Start::code2dnu1(int var)
{
  if ( Prot->Data.Ver_HEX != 400 )
  {
    return ( var * 5.0 / 4096 ) * 1.1;
  }
  else
  {
    return ( var * 4.5 / 4096 ) * 1.1;
  }
}
//---------------------------------------------------------------------------
double __fastcall TForm_82_Start::code2dvu1(int var)
{
  if ( Prot->Data.Ver_HEX != 400 )
  {
    return ( var * 5.0 / 4096 ) * 1.1;
  }
  else
  {
    return ( var * 4.5 / 4096 ) * 1.1;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::ZapEEPROM(void)
{
  unsigned int temp;

  if ( !bFlagKnopkaZapis )
  {
    ShowMessage("�������� ����� �� RS485");
    return;
  }
  else
  {
    bFlagKnopkaZapis = false;
  }
  bool flagUspeshnoyZapisi = true; // ���� ������ ������ ��� ������ - true
  bool flagUspeshnogoSravneniya = true; // ���� ������ ������ ��� ����������� - true
  bool flagUspeshnogoChteniya = true; // ���� ������ ������ ��� ������ - true
  bool flagErr; // true - ���� ������ ��� ������, ������ ��� �����������

  bool flagIzmeneniy = false; // ���� ������ ���� �������� - true
  Button_WriteToBD->Enabled = false;
  try // �������������� ����� ��
  {
    temp = StrToInt( Edit_2_Col3_Row2->Text );
    if ( Edit_2_Col3_Row2->Color != clWindow )
    {
      Edit_2_Col3_Row2->Color = clWindow;
    }
  }
  catch (EConvertError*)
  {
    Edit_2_Col3_Row2->Color = clRed;
    Button_WriteToBD->Enabled = bFlag_Button_WriteToBD;
    return;
  }
  if (temp != Prot->Data.IndAdrZ)
  {
    flagIzmeneniy = true;
    if ( Prot->SetIndAdr( temp ) == -1 )
    {
      ShowMessage("������ ������: �������������� ����� ��");
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: �������������� ����� ��");
      Edit_2_Col3_Row2->Text = IntToStr( Prot->Data.IndAdrZ );
      flagUspeshnoyZapisi = false;
    }
    else
    {
      Prot->Data.IndAdrZ = temp;
      if ( Prot->GetIndAdr( (unsigned char *)&temp ) != -1 )
      {
        if ( Prot->Data.IndAdrZ != temp )
        {
          // ������� ��������� ��������, ����� ��� ���������
          // ������� ������ ���������� ��������� �� ������
          Prot->Data.IndAdrZ = temp;
          ShowMessage("������ EEPROM: �������������� ����� ��");
          Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ EEPROM: �������������� ����� ��");
          Edit_2_Col3_Row2->Text = IntToStr( temp );
          flagUspeshnogoSravneniya = false;
        }
      }
      else
      {
        ShowMessage("������ ������: �������������� ����� ��");
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: �������������� ����� ��");
        flagUspeshnogoChteniya = false;
      }
    }
  }
  try // ��������� ����� ��
  {
    temp = StrToInt(Edit_2_Col3_Row3->Text);
    if (Edit_2_Col3_Row3->Color != clWindow)
    {
      Edit_2_Col3_Row3->Color = clWindow;
    }
  }
  catch (EConvertError*)
  {
    Edit_2_Col3_Row3->Color = clRed;
    Button_WriteToBD->Enabled = bFlag_Button_WriteToBD;
    return;
  }
  if (temp != Prot->Data.GrpAdrZ)
  {
    flagIzmeneniy = true;
    if ( Prot->SetGrpAdr( temp ) == -1 )
    {
      ShowMessage("������ ������: ��������� ����� ��");
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: ��������� ����� ��");
      Edit_2_Col3_Row3->Text = IntToStr( Prot->Data.GrpAdrZ );
      flagUspeshnoyZapisi = false;
    }
    else
    {
      Prot->Data.GrpAdrZ = temp;
      if ( Prot->GetGrpAdr( (unsigned char *)&temp ) != -1 )
      {
        if ( Prot->Data.GrpAdrZ != temp )
        {
          // ������� ��������� ��������, ����� ��� ���������
          // ������� ������ ���������� ��������� �� ������
          Prot->Data.GrpAdrZ = temp;
          ShowMessage("������ EEPROM: ��������� ����� ��");
          Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ EEPROM: ��������� ����� ��");
          Edit_2_Col3_Row3->Text = IntToStr( temp );
          flagUspeshnogoSravneniya = false;
        }
      }
      else
      {
        ShowMessage("������ ������: ��������� ����� ��");
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: ��������� ����� ��");
        flagUspeshnogoChteniya = false;
      }
    }
  }
  try // �������� ��� ��������
  {
    temp = StrToInt(Edit_2_Col2_Row4->Text);
    // ���� ����� ���� ������ ���� (� ����������� �� ��������)
    Edit_2_Col2_Row4->Color = clWin_Edit_2_Col2_Row4;
  }
  catch (EConvertError*)
  {
    Edit_2_Col2_Row4->Color = clRed;
    Button_WriteToBD->Enabled = bFlag_Button_WriteToBD;
    return;
  }
  if (temp != Prot->Data.DNUZ)
  {
    flagIzmeneniy = true;
    if ( Prot->SetDNU( temp ) == -1 )
    {
      ShowMessage("������ ������: ������������� ������� ������");
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: ������������� ������� ������");
      Edit_2_Col2_Row4->Text = IntToStr( Prot->Data.DNUZ );
      flagUspeshnoyZapisi = false;
    }
    else
    {
      Prot->Data.DNUZ = temp;
      if ( Prot->ReadFlashInvert( 0, (unsigned long*)&temp ) != -1 )
      {
        temp &= 0x0000FFFF;
        if ( Prot->Data.DNUZ != temp )
        {
          // ������� ��������� ��������, ����� ��� ���������
          // ������� ������ ���������� ��������� �� ������
          Prot->Data.DNUZ = temp;
          ShowMessage("������ EEPROM: ������������� ������� ������");
          Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ EEPROM: ������������� ������� ������");
          Edit_2_Col2_Row4->Text = IntToStr( temp );
          flagUspeshnogoSravneniya = false;
        }
      }
      else
      {
        ShowMessage("������ ������: ������������� ������� ������");
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: ������������� ������� ������");
        flagUspeshnogoChteniya = false;
      }
    }
  }
  try // �������� ��� ��������
  {
    temp = StrToInt(Edit_2_Col2_Row5->Text);
    Edit_2_Col2_Row5->Color = clWin_Edit_2_Col2_Row5;
  }
  catch (EConvertError*)
  {
    Edit_2_Col2_Row5->Color = clRed;
    Button_WriteToBD->Enabled = bFlag_Button_WriteToBD;
    return;
  }
  if (temp > 4095) 
  {
    Edit_2_Col2_Row5->Text = "4095";
    temp = StrToInt(Edit_2_Col2_Row5->Text); // ����� �� ����� ��������� ���������� (���� �����)
    Edit_2_Col3_Row5->Text =
        FloatToStrF(CheckBox_Diskr->Checked ? code2dvu1(temp) :
        code2dvu0(temp), ffGeneral, 2 /* ������� ����� */, 8);
  }
  if (temp != Prot->Data.DVUZ)
  {
    flagIzmeneniy = true;
    if ( Prot->SetDVU( temp ) == -1 )
    {
      ShowMessage("������ ������: ������������� �������� ������");
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: ������������� �������� ������");
      Edit_2_Col2_Row5->Text = IntToStr( Prot->Data.DVUZ );
      flagUspeshnoyZapisi = false;
    }
    else
    {
      Prot->Data.DVUZ = temp;
      if ( Prot->ReadFlashInvert( 1, (unsigned long*)&temp ) != -1 )
      {
        temp &= 0x0000FFFF;
        if ( Prot->Data.DVUZ != temp )
        {
          // ������� ��������� ��������, ����� ��� ���������
          // ������� ������ ���������� ��������� �� ������        
          Prot->Data.DVUZ = temp;
          ShowMessage("������ EEPROM: ������������� �������� ������");
          Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ EEPROM: ������������� �������� ������");
          Edit_2_Col2_Row5->Text = IntToStr( temp );
          flagUspeshnogoSravneniya = false;
        }
      }
      else
      {
        ShowMessage("������ ������: DVUZ");
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: ������������� �������� ������");
        flagUspeshnogoChteniya = false;
      }
    }
  }
  try // ��� ���������� ��������
  {
    temp = StrToInt(Edit_2_Col2_Row6->Text);
    if (Edit_2_Col2_Row6->Color != clWindow)
    {
      Edit_2_Col2_Row6->Color = clWindow;
    }
  }
  catch (EConvertError*)
  {
    Edit_2_Col2_Row6->Color = clRed;
    Button_WriteToBD->Enabled = bFlag_Button_WriteToBD;
    return;
  }
  if (temp != Prot->Data.LEDAmpZ)
  {
    flagIzmeneniy = true;
    if ( Prot->SetLEDAmp( temp ) == -1 )
    {
      ShowMessage("������ ������: ��� ���������� ��������");
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: ��� ���������� ��������");
      Edit_2_Col2_Row6->Text = IntToStr( Prot->Data.LEDAmpZ );
      flagUspeshnoyZapisi = false;
    }
    else
    {
      Prot->Data.LEDAmpZ = temp;
      if ( Prot->ReadFlashInvert( 2, (unsigned long*)&temp ) != -1 )
      {
        temp &= 0x0000FFFF;
        if ( Prot->Data.LEDAmpZ != temp )
        {
          // ������� ��������� ��������, ����� ��� ���������
          // ������� ������ ���������� ��������� �� ������
          Prot->Data.LEDAmpZ = temp;
          ShowMessage("������ EEPROM: ��� ���������� ��������");
          Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ EEPROM: ��� ���������� ��������");
          Edit_2_Col2_Row6->Text = IntToStr( temp );
          flagUspeshnogoSravneniya = false;
        }
      }
      else
      {
        ShowMessage("������ ������: ��� ���������� ��������");
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: ��� ���������� ��������");
        flagUspeshnogoChteniya = false;
      }
    }
  }
  try // ������������ ���� ��������
  {
    temp = StrToInt(Edit_2_Col2_Row7->Text);
    if (Edit_2_Col2_Row7->Color != clWindow)
    {
      Edit_2_Col2_Row7->Color = clWindow;
    }
  }
  catch (EConvertError*)
  {
    Edit_2_Col2_Row7->Color = clRed;
    Button_WriteToBD->Enabled = bFlag_Button_WriteToBD;
    return;
  }
  if (temp != Prot->Data.UhiZ)
  {
    flagIzmeneniy = true;
    if ( Prot->SetUhi( temp ) == -1 )
    {
      ShowMessage("������ ������: ������������ ���� ��������");
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: ������������ ���� ��������");
      Edit_2_Col2_Row7->Text = IntToStr( Prot->Data.UhiZ );
      flagUspeshnoyZapisi = false;
    }
    else
    {
      Prot->Data.UhiZ = temp;
      if ( Prot->ReadFlashInvert( 3, (unsigned long*)&temp ) != -1 )
      {
        temp &= 0x0000FFFF;
        if ( Prot->Data.UhiZ != temp )
        {
          // ������� ��������� ��������, ����� ��� ���������
          // ������� ������ ���������� ��������� �� ������
          Prot->Data.UhiZ = temp;
          ShowMessage("������ EEPROM: ������������ ���� ��������");
          Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ EEPROM: ������������ ���� ��������");
          Edit_2_Col2_Row7->Text = IntToStr( temp );
          flagUspeshnogoSravneniya = false;
        }
      }
      else
      {
        ShowMessage("������ ������: ������������ ���� ��������");
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: ������������ ���� ��������");
        flagUspeshnogoChteniya = false;
      }
    }
  }
  try // ������ ��� ���������
  {
    temp = StrToInt(Edit_2_Col2_Row8->Text);
    if (Edit_2_Col2_Row8->Color != clWindow)
    {
      Edit_2_Col2_Row8->Color = clWindow;
    }
  }
  catch (EConvertError*)
  {
    Edit_2_Col2_Row8->Color = clRed;
    Button_WriteToBD->Enabled = bFlag_Button_WriteToBD;
    return;
  }
  if (temp != Prot->Data.SIMstartZ)
  {
    flagIzmeneniy = true;
    if ( Prot->SetUhi2( temp ) == -1 )
    {
      ShowMessage("������ ������: ������ ��� ���������");
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: ������ ��� ���������");
      Edit_2_Col2_Row8->Text = IntToStr( Prot->Data.SIMstartZ );
      flagUspeshnoyZapisi = false;
    }
    else
    {
      Prot->Data.SIMstartZ = temp;
      if ( Prot->ReadFlashInvert( 7, (unsigned long*)&temp ) != -1 )
      {
        temp &= 0x0000FFFF;
        if ( Prot->Data.SIMstartZ != temp )
        {
          // ������� ��������� ��������, ����� ��� ���������
          // ������� ������ ���������� ��������� �� ������
          Prot->Data.SIMstartZ = temp;
          ShowMessage("������ EEPROM: ������ ��� ���������");
          Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ EEPROM: ������ ��� ���������");
          Edit_2_Col2_Row8->Text = IntToStr( temp );
          flagUspeshnogoSravneniya = false;
        }
      }
      else
      {
        ShowMessage("������ ������: ������ ��� ���������");
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: ������ ��� ���������");
        flagUspeshnogoChteniya = false;
      }
    }
  }
  try //  ������ ��� �����������
  {
    temp = StrToInt(Edit_2_Col2_Row9->Text);
    if (Edit_2_Col2_Row9->Color != clWindow)
    {
      Edit_2_Col2_Row9->Color = clWindow;
    }
  }
  catch (EConvertError*)
  {
    Edit_2_Col2_Row9->Color = clRed;
    Button_WriteToBD->Enabled = bFlag_Button_WriteToBD;
    return;
  }
  if (temp < 670) // ������ ��� �����������
  {
    Edit_2_Col2_Row9->Text = "670";
    temp = StrToInt(Edit_2_Col2_Row9->Text); // ����� �� ����� ��������� ���������� (���� �����)
  }
  if (temp != Prot->Data.SIMminZ)
  {
    flagIzmeneniy = true;
    if ( Prot->WriteFlashInvert( 9, temp ) == -1 )
    {
      ShowMessage("������ ������: ������ ��� �����������");
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: ������ ��� �����������");
      Edit_2_Col2_Row9->Text = IntToStr( Prot->Data.SIMminZ );
      flagUspeshnoyZapisi = false;
    }
    else
    {
      Prot->Data.SIMminZ = temp;
      if ( Prot->ReadFlashInvert( 9, (unsigned long*)&temp ) != -1 )
      {
        temp &= 0x0000FFFF;
        if ( Prot->Data.SIMminZ != temp )
        {
          // ������� ��������� ��������, ����� ��� ���������
          // ������� ������ ���������� ��������� �� ������
          Prot->Data.SIMminZ = temp;
          ShowMessage("������ EEPROM: ������ ��� �����������");
          Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ EEPROM: ������ ��� �����������");
          Edit_2_Col2_Row9->Text = IntToStr( temp );
          flagUspeshnogoSravneniya = false;
        }
      }
      else
      {
        ShowMessage("������ ������: ������ ��� �����������");
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: ������ ��� �����������");
        flagUspeshnogoChteniya = false;
      }
    }
  }
  try // �������� ������ ����������
  {
    temp = StrToInt(Edit_2_Col2_Row10->Text);
    if (Edit_2_Col2_Row10->Color != clWindow)
    {
      Edit_2_Col2_Row10->Color = clWindow;
    }
  }
  catch (EConvertError*)
  {
    Edit_2_Col2_Row10->Color = clRed;
    Button_WriteToBD->Enabled = bFlag_Button_WriteToBD;
    return;
  }
  if (temp > 255) // �������� ������ ����������
  {
    Edit_2_Col2_Row10->Text = "255";
    temp = StrToInt(Edit_2_Col2_Row10->Text); // ����� �� ����� ��������� ���������� (���� �����)
  }
  if (temp != Prot->Data.LedZadZ)
  {
    flagIzmeneniy = true;
    if ( Prot->SetLEDOtkl( temp ) == -1 )
    {
      ShowMessage("������ ������: �������� ������ ����������");
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: �������� ������ ����������");
      Edit_2_Col2_Row10->Text = IntToStr( Prot->Data.LedZadZ );
      flagUspeshnoyZapisi = false;
    }
    else
    {
      Prot->Data.LedZadZ = temp;
      if ( Prot->ReadFlash(0x2B, (unsigned long*)&temp ) != -1 )
      {
        temp &= 0x000000FF;
        if ( Prot->Data.LedZadZ != temp )
        {
          // ������� ��������� ��������, ����� ��� ���������
          // ������� ������ ���������� ��������� �� ������
          Prot->Data.LedZadZ = temp;
          ShowMessage("������ EEPROM: �������� ������ ����������");
          Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ EEPROM: �������� ������ ����������");
          Edit_2_Col2_Row10->Text = IntToStr( temp );
          flagUspeshnogoSravneniya = false;
        }
      }
      else
      {
        ShowMessage("������ ������: �������� ������ ����������");
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: �������� ������ ����������");
        flagUspeshnogoChteniya = false;
      }
    }
  }
  try // �������� �����
  {
    temp = StrToInt(Edit_2_Col3_Row11->Text);
    if (Edit_2_Col3_Row11->Color != clWindow)
    {
      Edit_2_Col3_Row11->Color = clWindow;
    }
  }
  catch (EConvertError*)
  {
    Edit_2_Col3_Row11->Color = clRed;
    Button_WriteToBD->Enabled = bFlag_Button_WriteToBD;
    return;
  }
  if (temp != Prot->Data.m_ulSerialNumberZ)
  {
    flagIzmeneniy = true;
    if (Prot->SetSerialNumber(temp) == -1)
    {
      ShowMessage("������ ������: �������� �����");
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: �������� �����");
      Edit_2_Col3_Row11->Text = IntToStr( Prot->Data.m_ulSerialNumberZ );
      flagUspeshnoyZapisi = false;
    }
    else
    {
      Prot->Data.m_ulSerialNumberZ = temp;
      if ( Prot->ReadFlashInvert( 10, (unsigned long*)&temp ) != -1 )
      {
        temp &= 0xFFFFFFFF;
        if ( Prot->Data.m_ulSerialNumberZ != temp )
        {
          // ������� ��������� ��������, ����� ��� ���������
          // ������� ������ ���������� ��������� �� ������        
          Prot->Data.m_ulSerialNumberZ = temp;
          ShowMessage("������ EEPROM: �������� �����");
          Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ EEPROM: �������� �����");
          Edit_2_Col3_Row11->Text = IntToStr( temp );
          flagUspeshnogoSravneniya = false;
        }
      }
      else
      {
        ShowMessage("������ ������: �������� �����");
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: �������� �����");
        flagUspeshnogoChteniya = false;
      }
    }
  }
  try // ���������� ��� ������� ������������ ���
  {
    float fTmp;
    //==\\temp = StrToInt(Edit_2_Col2_Row12->Text);
    fTmp = StrToFloat(Edit_2_Col3_Row12->Text);
    temp = static_cast<int>(fTmp + 0.5);
    //==\\Edit_2_Col2_Row12->Color = clWin_Edit_2_Col2_Row12;
    Edit_2_Col3_Row12->Color = clWin_Edit_2_Col3_Row12;
  }
  catch (EConvertError*)
  {
    //==\\Edit_2_Col2_Row12->Color = clRed;
    Button_WriteToBD->Enabled = bFlag_Button_WriteToBD;
    return;
  }
  if (temp != Prot->Data.m_ulU0Z)
  //if ( temp != static_cast<int>(Prot->Data.dbm_ulU0Z) )
  {
    flagIzmeneniy = true;
    if (Prot->SetU0(temp) == -1)
    {
      ShowMessage("������ ������: ����. ��� ������� ����. ���");
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: ����. ��� ������� ����. ���");
      Edit_2_Col3_Row12->Text = IntToStr( Prot->Data.m_ulU0Z );
      flagUspeshnoyZapisi = false;
    }
    else
    {
      Prot->Data.m_ulU0Z = temp;
      if ( Prot->ReadFlashInvert( 11, (unsigned long*)&temp ) != -1 )
      {
        temp &= 0xFFFFFFFF;
        if ( Prot->Data.m_ulU0Z != temp )
        {
          // ������� ��������� ��������, ����� ��� ���������
          // ������� ������ ���������� ��������� �� ������        
          Prot->Data.m_ulU0Z = temp;
          ShowMessage("������ EEPROM: ����. ��� ������� ����. ���");
          Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ EEPROM: ����. ��� ������� ����. ���");
          Edit_2_Col3_Row12->Text = IntToStr( temp );
          flagUspeshnogoSravneniya = false;
        }
      }
      else
      {
        ShowMessage("������ ������: ����. ��� ������� ����. ���");
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: ����. ��� ������� ����. ���");
        flagUspeshnogoChteniya = false;
      }
    }
  }
  try // ����. ���.*
  {
    float fTmp;
    //==\\fTmp = StrToInt(Edit_2_Col2_Row13->Text);
    fTmp = StrToFloat(Edit_2_Col3_Row13->Text);
    temp = static_cast<int>(fTmp + 0.5);
    //==\\Edit_2_Col2_Row13->Color = clWin_Edit_2_Col2_Row13;
    //==\\Edit_2_Col3_Row13->Color = clWin_Edit_2_Col3_Row13;
  }
  catch (EConvertError*)
  {
    //==\\Edit_2_Col2_Row13->Color = clRed;
    Button_WriteToBD->Enabled = bFlag_Button_WriteToBD;
    return;
  }
  if (temp != Prot->Data.m_ulUZ)
  {
    flagIzmeneniy = true;
    //if ( Prot->SetU( temp ) == -1 )
    if ( Prot->WriteFlashInvert(12, temp) == -1 )
    {
      ShowMessage("������ ������: ����. ���.*");
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: ����. ���.*");
      Edit_2_Col3_Row13->Text = IntToStr( Prot->Data.m_ulUZ );
      flagUspeshnoyZapisi = false;
    }
    else
    {
      Prot->Data.m_ulUZ = temp;
      if ( Prot->ReadFlashInvert( 12, (unsigned long*)&temp ) != -1 )
      {
        temp &= 0xFFFFFFFF;
        if ( Prot->Data.m_ulUZ != temp )
        {
          // ������� ��������� ��������, ����� ��� ���������
          // ������� ������ ���������� ��������� �� ������
          Prot->Data.m_ulUZ = temp;
          ShowMessage("������ EEPROM: ����. ���.*");
          Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ EEPROM: ����. ���.*");
          Edit_2_Col3_Row13->Text = IntToStr( temp );
          flagUspeshnogoSravneniya = false;
        }
      }
      else
      {
        ShowMessage("������ ������: ����. ���.*");
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: ����. ���.*");
        flagUspeshnogoChteniya = false;
      }
    }
  }
  //===>>
  strcpy( Prot->Data.m_strStickyNote_temp, AnsiString(Edit_2_Col2_4_Row_14->Text).c_str() );
  if ( strcmp( Prot->Data.m_strStickyNote_temp, Prot->Data.m_strStickyNote ) != 0 ) // ���� ������ ����������
  {
    flagIzmeneniy = true;
    if( Prot->SetStickyNote( Prot->Data.m_strStickyNote_temp ) == -1 )
    {
      ShowMessage("������ ������: �������. �������� (0...23)");
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: �������. �������� (0...23)");
      Edit_2_Col2_4_Row_14->Text = Prot->Data.m_strStickyNote;
      flagUspeshnoyZapisi = false;
    }
    else
    {
      strcpy( Prot->Data.m_strStickyNote, Prot->Data.m_strStickyNote_temp );
      if ( Prot->GetStickyNote( Prot->Data.m_strStickyNote_temp ) == 0 )
      {
        if ( strcmp( Prot->Data.m_strStickyNote_temp, Prot->Data.m_strStickyNote ) != 0 )
        {
          // ������� ��������� ��������, ����� ��� ���������
          // ������� ������ ���������� ��������� �� ������
          strcpy( Prot->Data.m_strStickyNote, Prot->Data.m_strStickyNote_temp );
          ShowMessage("������ EEPROM: �������. �������� (0...23)");
          Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ EEPROM: �������. �������� (0...23)");
          Edit_2_Col2_4_Row_14->Text = Prot->Data.m_strStickyNote_temp;
          flagUspeshnogoSravneniya = false;
        }
      }
      else
      {
        ShowMessage("������ ������: �������. �������� (0...23)");
        Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������: �������. �������� (0...23)");
        flagUspeshnogoChteniya = false;
      }
    }
  }
  // flagErr --- true = ���� ������ ��� ������, ������ ��� �����������
  //=============================================================================================
  char LDImp;
  if(CheckBox_Diod->Checked == true)
  {
    temp = 1;
    LDImp = 1;
  }
  else
  {
    temp = 2;
    LDImp = 0;
  }
  if(temp != (unsigned int)(Prot->flagUchSv))
  {
    flagIzmeneniy = true;
    if(Prot->IncFreqLEDImp(LDImp) == -1) // temp = 1 - �������� �������� ����������, 0 - ����.
    {
      ShowMessage("������ ������� \"IncFreqLEDImp\" (�������� ����������)");
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������� \"IncFreqLEDImp\" (�������� ����������)");
      InterfaceUchSvet(Prot->flagARCH); // ������� ������� ���
      flagUspeshnoyZapisi = false;
    }
    else
    {
      Prot->flagUchSv = temp;
      // ���������, ���� �� ������� - ���� ������ ��������
      // ����� ��������, ���� �� �������� - ���� ��������� ��������
    }
  }
  //=============================================================================================
  char SCVar;
  char ACVar;
  if (RadioButton_ARCH1->Checked == true) // ��� �����������
  {
    temp = 3;
    SCVar = 0;
    ACVar = 0;
  }
  if (RadioButton_ARCH2->Checked == true) // ��� ������
  {
    temp = 2;
    SCVar = 1;
    ACVar = 0;
  }
  if (RadioButton_ARCH3->Checked == true) // ���������
  {
    temp = 1;
    SCVar = 0;
    ACVar = 1;                                                          //==\\
  }
  if(temp != (unsigned int)(Prot->flagARCH))
  {
    flagIzmeneniy = true;
    if(Prot->SpectrCon(SCVar) == -1)
    {
      ShowMessage("������ ������� \"SpectrCon\" (���)");
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������� \"SpectrCon\" (���)");
      flagUspeshnoyZapisi = false;
    }
    if(Prot->ARCHCon(ACVar) == -1)
    {
      ShowMessage("������ ������� \"ARCHCon\" (���)");
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������� \"ARCHCon\" (���)");
      flagUspeshnoyZapisi = false;
    }
    if (flagUspeshnoyZapisi == true)
    {
      Prot->flagARCH = temp;
      if (RadioButton_ARCH3->Checked == true) // ���������
      {
        if ( (Prot->flagARCH_Off == true) && (FlagOpros == true) ) //==\\
        {                                                          //==\\
          Prot->flagARCH_Off = false;                              //==\\
          Cprw->flagSostoyaniya = 6;  // ��� ������ � EEPROM ���� ���������� ��������� ...
        }
      }
    }
    else
    {
      InterfaceARH(Prot->flagARCH);
    }
  }
  //=============================================================================================
  /*
  // ===>> 2018.01.26
  if (DnuAndDvuMode)
  {
    DnuAndDvuMode = false;
    this->CheckBox_DAuto_Standart->Checked = false;
    this->CheckBox_DAuto_Shirokie->Checked = false;
    this->CheckBox_DAuto_Rengen->Checked = false;
    Button_WriteToBD->Enabled = bFlag_Button_WriteToBD;    
    return;
  }
  // <<=== 2018.01.26
  */

  flagErr = !( flagUspeshnoyZapisi && flagUspeshnogoSravneniya && flagUspeshnogoChteniya );
  // ===
  if ( flagIzmeneniy == false )
  {
    ShowMessage("������ �� ���� ��������, ���������� �� �������������");
    Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ �� ���� ��������, ���������� �� �������������");

    // ����� ����� � ������, �� �� ������ � ���� ����������
    // ���� ���� ��������������� � false
    // ����� �������� ������ (��� ���� ��������� ��� ������ �� ����������) - � true.
    // ������������ ��� ����������� � ���,
    // ��� ������ ���������� �� �������������
    // ��� ������� ����������������� ����� � �����.
    bf_Zabyvchivosti = true;
  }
  else
  if ( flagErr == true )
  {
    if ( flagUspeshnoyZapisi == false )
    {
      ShowMessage("������, ��� ������� �������� ������");
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������, ��� ������� �������� ������");
    }
    if ( flagUspeshnogoSravneniya == false )
    {
      ShowMessage("������ ����������� ������");
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ����������� ������");
    }
    if ( flagUspeshnogoChteniya == false )
    {
      ShowMessage("������, ��� ������� ��������� ������");
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������, ��� ������� ��������� ������");
    }
  }
  else
  {
    ShowMessage("�������� ��������� ���� ���������");
    Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "�������� ��������� ���� ���������");

    // ����� ����� � ������, �� �� ������ � ���� ����������
    // ���� ���� ��������������� � false
    // ����� �������� ������ (��� ���� ��������� ��� ������ �� ����������) - � true.
    // ������������ ��� ����������� � ���,
    // ��� ������ ���������� �� �������������
    // ��� ������� ����������������� ����� � �����.
    bf_Zabyvchivosti = true;
  }
  // ===
  Button_WriteToBD->Enabled = bFlag_Button_WriteToBD;
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::InterfaceUchSvet(int iVar)
{
  Prot->flagUchSv = iVar;
  if ( Prot->flagUchSv == 1 )
  {
    CheckBox_Diod->Checked = true;
  }
  else if ( Prot->flagUchSv == 2 )
  {
    CheckBox_Diod->Checked = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::InterfaceARH(int iVar)
{
  Prot->flagARCH = iVar;
  if ( Prot->flagARCH == 1 )
  {
    RadioButton_ARCH3->Checked = true;
  }
  else if ( Prot->flagARCH == 2 )
  {
    RadioButton_ARCH2->Checked = true;
  }
  else if ( Prot->flagARCH == 3 )
  {
    RadioButton_ARCH1->Checked = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::ZapEEPROM_2(void)
{
  unsigned int temp;
  bool flagUspeshnoyZapisi = true; // ���� ������ ������ ��� ������ - true
  //bool flagIzmeneniy = false; // ���� ������ ���� �������� - false
  try // ��� ���������� ��������
  {
    temp = StrToInt(Edit_2_Col2_Row6->Text);
    if (Edit_2_Col2_Row6->Color != clWindow)
    {
      Edit_2_Col2_Row6->Color = clWindow;
    }
  }
  catch (EConvertError*)
  {
    Edit_2_Col2_Row6->Color = clRed;
  }
  if (Prot->SetLEDAmp(temp) == -1)
  {
    Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������: LEDAmpZ");
    flagUspeshnoyZapisi = false;
  }
  else
  {
    Prot->Data.LEDAmpZ = temp;
  }
  // == 27.06.2014
  try // ������ ��� ���������
  {
    temp = StrToInt(Edit_2_Col2_Row8->Text);
    if (Edit_2_Col2_Row8->Color != clWindow)
    {
      Edit_2_Col2_Row8->Color = clWindow;
    }
  }
  catch (EConvertError*)
  {
    Edit_2_Col2_Row8->Color = clRed;
  }
  if (Prot->SetUhi2(temp) == -1)
  {
    Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������: SIMstartZ");
    flagUspeshnoyZapisi = false;
  }
  else
  {
    Prot->Data.SIMstartZ = temp;
  }
  // ===
  if ( flagUspeshnoyZapisi == false )
  {
    Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������, ��� ������� �������� ������ (ZapEEPROM_2)");
  }
  else
  {
    Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "�������� ��������� ���� ��������� (ZapEEPROM_2)");
  }
  // ===
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_OpenBDClick(TObject *Sender)
{
  Panel_bit7->Color = clRed; // ��������� �������� ����
  Panel_bit7_2->Color = clRed; // ��������� �������� ����
  if ( FlagOpros == false ) // ���� ��� ����������� ��������� ������ OpenBD
  {
    RadioButton_ARCH1->Checked = false;
    RadioButton_ARCH2->Checked = false;
    RadioButton_ARCH3->Checked = false;
    ErrorCode = RSConnect( ComboBox_NomComPort->Text.c_str() );
    if ( ErrorCode == 0 ) // ���� ���� �������� ��� ��� ��� ������
    {
      GroupBox_ComPort->Enabled = false; // 17.07.2017

      bFlagChengeKolTik = true; // ����������� ������� ��� �����
      bFlagChengeKolTikSpectr = true; // ����������� ������� ��� �������
      Prot->AddrBD = StrToInt( SpinEdit_AddrBD->Text );
      Button_OpenBD->Caption = "�������";

      Button_Plus->Enabled = false;
      Button_Minus->Enabled = false;

      SpinEdit_AddrBD->Enabled = false;
      Button_Start->Enabled = false;
      ComboBox_NomComPort->Enabled = false;
      RadioGroup_VyborProtokola->Enabled = false;
      Button_OpenBD_msek->Enabled = false;
      // ===
      Button_WriteToBD->Enabled = bFlag_Button_WriteToBD; // ������ � ��
      Button_UpdateComPortsList->Enabled = false;
      Button_OpenBD_msek->Enabled = false;
      BitBtn_ARCH->Enabled = true;
      BitBtn_Uch_sv->Enabled = true;
      Button_ARCH->Enabled = false;
      Button_Puason->Enabled = false;
      Button_Sum_Schet->Enabled = true;

      ComboBox_NomBD->Enabled = false; //==\\ 24.01.2016


      Button_P3_7_Set->Enabled = false;
      Button_P3_7_Reset->Enabled = false;

      BitBtn_P37SetReset->Enabled = true;
      CheckBox_Enabled_Write_TCP->Enabled = false;
      if ( RadioGroup_VyborProtokola->ItemIndex != 0 ) // ������ �������� ModBus
      {
        ButtonSearch->Enabled = false;
        Button_SaveAddr->Enabled = false;
        GroupBox_SettingsForModbus->Enabled = true;
        Button_ModBus_Write->Enabled = true;
        Button_ModBus_SetDef->Enabled = true;
        //CheckBox_TCP->Enabled = false;
      }
      Cprw->flagSostoyaniya = 9;
      Timer1->Interval = TimerInterval;
      Timer1->Enabled = true;
      FlagOpros = true;
    }
    else
    {
      return;
    }
  }
  else // if (flagOpros == true)
  {
    GroupBox_ComPort->Enabled = true; // 17.07.2017

    FlagOpros = false; // ���� ��� ����������� ��������� ������ OpenBD  
    Button_OpenBD->Caption = "�������";

    Button_Plus->Enabled = true;
    Button_Minus->Enabled = true;

    ClearEdit_1();
    ClearEdit_2();

    Timer1->Enabled = false;
    SpinEdit_AddrBD->Enabled = true;
    Button_Start->Enabled = true;
    ComboBox_NomComPort->Enabled = true;
    RadioGroup_VyborProtokola->Enabled = true;
    Button_OpenBD_msek->Enabled = true;
    // ===
    Button_WriteToBD->Enabled = false; // ������ � ��
    Button_UpdateComPortsList->Enabled = true;
    Button_OpenBD_msek->Enabled = true;
    BitBtn_ARCH->Enabled = false;
    BitBtn_Uch_sv->Enabled = false;
    Button_ARCH->Enabled = true;
    Button_Puason->Enabled = true;    
    Button_Sum_Schet->Enabled = false;
    Button_SaveToFile->Enabled = false; // ��������� ������ ����� � ����

    ComboBox_NomBD->Enabled = true; //==\\ 24.01.2016


    Button_P3_7_Set->Enabled = true;
    Button_P3_7_Reset->Enabled = true;

    BitBtn_P37SetReset->Enabled = false;
    CheckBox_Enabled_Write_TCP->Enabled = true;
    this->ErrorZvyazi();
    
    if ( RadioGroup_VyborProtokola->ItemIndex == 1 || // ������ ��������: "ModBus RTU
         RadioGroup_VyborProtokola->ItemIndex == 2 || // ������ ��������: "ModBus TCP"
         RadioGroup_VyborProtokola->ItemIndex == 3 ) // ������ ��������: "ModBus RTU (TCP/IP)"
    {
      ButtonSearch->Enabled = true;
      //!if ( CheckBox_Enabled_Write_TCP->Checked == true || CheckBox_TCP->Checked == false )
      if ( CheckBox_Enabled_Write_TCP->Checked == true || RadioGroup_VyborProtokola->ItemIndex != 2 )
      {
        Button_SaveAddr->Enabled = true;
      }
      GroupBox_SettingsForModbus->Enabled = false;
      Button_ModBus_Write->Enabled = false;
      Button_ModBus_SetDef->Enabled = false;
      //CheckBox_TCP->Enabled = false;
    }
    RSDisConnect();
    // ===
    Button_Sum_Schet->Caption = "�����";
    Button_Set_Reset->Enabled = true;
    CSpinEdit_time_izm->Enabled = true;
  }        
}
//---------------------------------------------------------------------------
// ������ ����� ������
void __fastcall TForm_82_Start::ErrorZvyazi(void)
{
  this->YpravlenieDostupnostu( false );  
}
//---------------------------------------------------------------------------
// ������ ����� ����, �� ����� ��������������
void __fastcall TForm_82_Start::ErrorZvyaziByla(void)
{
  this->YpravlenieDostupnostu(true);
}
//---------------------------------------------------------------------------
// ���������� ������������ ��������� ��������� ����������
void __fastcall TForm_82_Start::YpravlenieDostupnostu(bool bFlag)
{
  Form_82_Spectr_BD84->Button_Spectr->Enabled = bFlag;
  Form_82_Spectr_BD84->Button_Spectr;

  if ( bFlag == false )
  {
    if ( Form_82_Spectr_BD84->GetStartStopSpectr() == true )
    {
      Form_82_Spectr_BD84->Button_Spectr->Caption = "������ ����� �������"; // "������ (Off)";
      Form_82_Spectr_BD84->Timer_Obnovleniya_Spectra->Enabled = false;
      Prot->OprosSpectra( false, Form_82_Spectr_BD84->SpinEdit_TimeSpektr->Value );
      Form_82_Spectr_BD84->SetStartStopSpectr( false );
    }
  }
}

//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_PuasonClick(TObject *Sender)
{
  FormPuasson8BD->Show();
}
//---------------------------------------------------------------------------
#ifdef _DIA_OBEDINENIE_
#pragma resource "DllInpout32.res"
//  #pragma resource "DIA_NastrBD82_85.res"
#endif  
//---------------------------------------------------------------------------
// �������� ���� �� � ����� "(������� ����):\VNIIA Ppograms\For_MCNP_Files"
// ���� "inpout32.dll", ���� ��� - ������� ��� �� ��������, � ����� ����������
bool __fastcall TForm_82_Start::IzvlechrnieDLL( void )
{
  String sPath;
  String FN1;
  TResourceStream * FileInResource;
  int iErr = 0;
  HINSTANCE dllInstanse = (void*)0;
  char chPath[MAX_PATH];
  String strErrorString;

  GetWindowsDirectory(chPath, MAX_PATH);
  //==\\GetCurrentDir(); //==\\ extern PACKAGE AnsiString __fastcall GetCurrentDir();
  sPath = ExtractFileDrive( chPath ); // C:
  sPath += "\\VNIIA Ppograms\\NastrBD82_85";
  FN1 = sPath + "\\inpout32.dll";
  if ( DirectoryExists( sPath.c_str() ) == false )
  {
    if ( ForceDirectories( sPath.c_str() ) == false )
    {
      // � ������� �� CreateDir ������� ForceDirectories ������ ���
      // ��������� � ���������� ������� ���������, ���� ���� �������������
      // �������� �� ����������
      return false;
    }
  }
  if ( FileExists( FN1 ) == false ) // ������ ����� ���
  {
    SetLastError ( 0 );
    try
    {
      FileInResource = new TResourceStream(0, "inpout32_DLL", RT_RCDATA);
    }
    catch (...)
    {
      iErr = GetLastError();
      strErrorString = "������ " + IntToStr ( iErr );
      strErrorString += ": " + SysErrorMessage( iErr );
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "�� ������� ����� ������ ����� \"inpout32.dll\"");
      Memo_For_Print_Errors->Lines->Add( GetCurrentTime() + strErrorString );
      return false;
    }
    SetLastError ( 0 );
    try
    {
      FileInResource->SaveToFile( FN1 );
      delete FileInResource;
    }
    catch (...)
    {
      iErr = GetLastError();
      strErrorString = "������ " + IntToStr ( iErr );
      strErrorString += ": " + SysErrorMessage( iErr );
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "�� ������� ��������� ���� � ��������: \"" + sPath + "\"");
      Memo_For_Print_Errors->Lines->Add( GetCurrentTime() + strErrorString );
      delete FileInResource;
      return false;
    }
  } // END if ( FileExists( FN1 ) == false ) // ������ ����� ���

  //dllInstanse = LoadLibrary( "c:\\Windows\\System32\\Kernel32.dll" ); // tmp

  dllInstanse = LoadLibrary( FN1.c_str() );
  if ( dllInstanse != NULL )
  {
    pInt32 = (TInt32*)GetProcAddress( dllInstanse, "Inp32" );
    pOut32 = (TOut32*)GetProcAddress( dllInstanse, "Out32" );
    Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "���� \"" +  FN1 + "\" ���������");
  }
  else
  {
    Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������: ���� \"" +  FN1 + "\" �� ���������!");
  }
  //===
  if ( pInt32 != NULL )
  {
    Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������� \"Int32\" �������");
    f_Inp32 = true;
  }
  else
  {
    Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������: ������� \"Int32\" �� �������!");
  }
  //===
  if ( pOut32 != NULL )
  {
    Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������� \"Out32\" �������");
    f_Out32 = true;
  }
  else
  {
    Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������: ������� \"Out32\" �� �������!");
  }
  if ( ( pInt32 != NULL ) && ( pOut32 != NULL ) )
  {
    return true;
  }
  else
  {
    return false;
  }
}
//---------------------------------------------------------------------------
void TForm_82_Start::Bd82Bd84( int BdTip )
{
  Form_82_Start->CheckBox_Proshivka->Checked = /*true*/false;
  Button_Spectr->Enabled = true;
  Button_Spectr->Visible = true;
  FormCaption = FormCaption82_84;
#ifdef _DIA_OBEDINENIE_
  if( FormDispet != 0 )
  {
    ProgrammVersion = FormDispet->GetProgrammVersion();
  }
#endif
  FormCaption = FormCaption + ProgrammVersion;
  Form_82_Start->Caption = FormCaption;    
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::FormShow(TObject *Sender)
{
  int ModBusFlag;
  HINSTANCE dllInstanse;
  HANDLE temping;
  int Inst;
  //==\\bool bFlagDisplay;
  AnsiString tS;
#ifdef _DIA_OBEDINENIE_
  if( FormDispet != 0 )
  {
    FormDispet->DiaGetWinHandle( this->Handle );
  }
#endif
  if ( CreateFormFlag_BD82 == false )
  {
    if ( this->CheckBox_Proshivka->Checked == true ) // ��� �� 84 (��� ModBus �������� 230 400)
    {
      Prot->newProsivka = true;
      this->Button_2_Col4_Row6_10->Enabled = false;
    }
    else // ��� �� 82 (��� ModBus �������� 57 600)
    {
      Prot->newProsivka = false; //
      iVar_Edit_2_Col2_Row6 = 3000;
      iVar_Edit_2_Col2_Row7 = 90;
      iVar_Edit_2_Col2_Row8 = 2600;
      iVar_Edit_2_Col2_Row9 = 2300;
      iVar_Edit_2_Col2_Row10 = 225;      
      this->Button_2_Col4_Row6_10->Enabled = true;
    }

    AnsiString asFullFileName;
    AnsiString asInfo;
    asFullFileName = ParamStr(0); // ������� �������� ��������� ������ (��� �����)
    asInfo = this->Caption.c_str();
    asInfo += "; ";
    asInfo += "<" + asFullFileName + ">";

    WriteLog_DIA( asInfo.c_str() );
    
    pInt32 = NULL;
    pOut32 = NULL;
    StringGrid1->Cells[0][0] = "� ��";
    StringGrid1->Cells[1][0] = "����";
    StringGrid1->Cells[2][0] = "���������";
    StringGrid1->Cells[0][1] = "1";
    StringGrid1->Cells[0][2] = "2";
    StringGrid1->Cells[0][3] = "3";
    StringGrid1->Cells[0][4] = "4";
    StringGrid1->Cells[0][5] = "5";
    StringGrid1->Cells[0][6] = "6";
    StringGrid1->Cells[0][7] = "7";
    StringGrid1->Cells[0][8] = "8";


    IzvlechrnieDLL();
    Cprw = new ComPortReadWrite_t(true); // true - �� ��������� ����� ��� ��������� ������
    Cprw->FreeOnTerminate = true; // false - �� ������������ ����� ����������

    Form_ARCH->Prot = this->Prot;
    Prot->FlagDebug = this->FlagDebug;
    RadioGroup_Povtor->ItemIndex = 0;
    bFlagButton_OpenBD_msek = false; // ��������� ������ OpenBD_msek
    
    // ������� ������ ����� �� INI-�����
    RadioGroup_KOD->ItemIndex = 1;
    TIniFile * IniFile = new TIniFile(IniFileName);
    try
    {
      Form_82_Start->Width = IniFile->ReadInteger( "Form_82_Start", "FormStartWidth", 300 );
      Form_82_Start->Height = IniFile->ReadInteger( "Form_82_Start", "FormStartHeight", 300 );
      Form_82_Start->Left =  IniFile->ReadInteger( "Form_82_Start", "FormStartLeft", 200 );
      Form_82_Start->Top = IniFile->ReadInteger( "Form_82_Start", "FormStartTop", 200 );
      ModBusFlag = IniFile->ReadInteger( "Form_82_Start", "FormStartProtModBus", 1 );
      Value_Addr_BD = IniFile->ReadInteger( "Form_82_Start", "FormStartProtModBusAddr", 247 );
      AddrLPTPort = IniFile->ReadInteger( "Form_82_Start", "FormStartLptPortAddr", 888 );
      ActivePageIndex = IniFile->ReadInteger( "Form_82_Start", "FormStartActivePageIndex", 0 );
      SpinEditLptAddr->Value = AddrLPTPort;
      PageControl_ModBus_Settings->ActivePageIndex = ActivePageIndex;
      tS = IniFile->ReadString( "Form_82_Start", "SelectedComPort", "COM1" );
      Form_82_Spectr_BD84->SpinEdit_TimeSpektr->Value = IniFile->ReadInteger( "Form_82_Start_Spectr", "KolTik_Spektr", 8 );

      ComboBox_NomComPort->Items->Add( tS );
      ComboBox_NomComPort->ItemIndex = 0;

      
      // === 19.04.2018 RadioGroup_VyborProtokola->ItemIndex = ModBusFlag;

      RadioGroup_VyborProtokolaClick( this ); // 18.07.2017�.

      flagModbusProtokol = ModBusFlag; // ����� ��������� "������"
      if ( ModBusFlag == 0 ) // ��������: 9-�� ������
      {
        bFlagWyborProtokola = false; // �� ����� ��������� � ��������� ��� ����
        bFlagWyborProtokola = true; // ��������� � ��������� ��� ����, ��� ��������� �������������
        SpinEdit_AddrBD->Value = 63;
      }
      else // ��������: ���� ModBus RTU, ���� ModBus TCP, ���� ModBus RTU (TCP/IP)
      {
        bFlagWyborProtokola = false; // �� ����� ��������� � ��������� ��� ����
        bFlagWyborProtokola = true; // ��������� � ��������� ��� ����, ��� ��������� �������������
        SpinEdit_AddrBD->Value = Value_Addr_BD;
      }

      textIpAddrModBusTcp = IniFile->ReadString("Form_82_Start", "IpAddrModBusTcp", "192.168.3.4");
      textTcpPortModBusTcp = IniFile->ReadString("Form_82_Start", "TcpPortModBusTcp", "502");
      textIpAddrModBusRtuIp = IniFile->ReadString("Form_82_Start", "IpAddrModBusRtuIp", "192.168.127.254");
      textTcpPortModBusRtuIp = IniFile->ReadString("Form_82_Start", "TcpPortModBusRtuIp", "4001");

      RadioGroup_VyborProtokola->ItemIndex = ModBusFlag; // === 19.04.2018

      delete IniFile;
    }
    catch(...) // ����� ����������
    {
      delete IniFile;
    }
    Button_Sum_Schet->Enabled = false;
  } // if ( CreateFormFlag_BD82 == false )
  iFlagTimer2 = 1;
  Timer2->Enabled = true;
  CreateFormFlag_BD82 = true;
  DnuAndDvuMode = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::ButtonSetLptAddrClick(TObject *Sender)
{
  AddrLPTPort = static_cast<unsigned short>(StrToInt(SpinEditLptAddr->Text));
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::PageControl_ModBus_SettingsChange(TObject *Sender)
{
  ActivePageIndex = PageControl_ModBus_Settings->ActivePageIndex;
  if ( ActivePageIndex == 1) // ������� ������� "��������� ModBus" (����� ��������� ���������)
  {
    //StatusBar1->Panels->Items[2]->Text = "������� ������� \"��������� ModBus\"";
    if ( (FlagOpros == true) && (flagModbusProtokol != 0) ) // ���� ��� ����������� ��������� ������ OpenBD
    {
      Cprw->flagSostoyaniya = 4;
      StatusBar1->Panels->Items[2]->Text = "������� ������� \"��������� ModBus\"";
    }
  }
  else
  {
    //StatusBar1->Panels->Items[2]->Text = "";
    Edit_3_01->Text = "";
    Edit_3_02->Text = "";
    Edit_3_03->Text = "";
    Edit_3_04->Text = "";
    Edit_3_05->Text = "";
    Edit_3_06->Text = "";
    Edit_3_07->Text = "";
    Edit_3_08->Text = "";
    Edit_3_09->Text = "";
    Edit_3_10->Text = "";
    Edit_3_11->Text = "";
    Edit_3_12->Text = "";
    Edit_3_13->Text = "";
    Edit_3_14->Text = "";
    Edit_3_15->Text = "";
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::ReadFromBDModbus(void)
{
  Prot->ReadFromBDModbus_BD82();
  ErrorCode = Prot->ReturnVar;

  if ( Prot->ReturnVar != -1 )
  {
    Edit_3_01->Text = IntToStr(Prot->Edit_3_01); // ����� �����
    Edit_3_02->Text = IntToStr(Prot->Edit_3_02); // ����������
    Edit_3_03->Text = IntToStr(Prot->Edit_3_03); // ����������� ����
    Edit_3_04->Text = IntToStr(Prot->Edit_3_04); // ������������ ����
    Edit_3_05->Text = IntToStr(Prot->Edit_3_05); // ������� ����������
    Edit_3_06->Text = IntToStr(Prot->Edit_3_06); // ���-�� ����������
    Edit_3_07->Text = IntToStr(Prot->Edit_3_07); // ���-�� ������� �����
    Edit_3_08->Text = IntToStr(Prot->Edit_3_08); // ������� ������� 1
    Edit_3_09->Text = IntToStr(Prot->Edit_3_09); // ������� ������� 2
    Edit_3_10->Text = IntToStr(Prot->Edit_3_10); // ������� ������� 3
    Edit_3_11->Text = IntToStr(Prot->Edit_3_11); // ���, ��
    Edit_3_12->Text = IntToStr(Prot->Edit_3_12); // ����. ������������ ����, ��
    Edit_3_13->Text = IntToStr(Prot->Edit_3_13); // ����. ������� �������, �
    Edit_3_14->Text = IntToStr(Prot->Edit_3_14); // ����. ������� �����, �
    Edit_3_15->Text = IntToStr(Prot->Edit_3_15); // ���������� ���, ���. / �
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::WriteToBDModBus(void)
{
  //bool errConv; // ���� ������ ����������
  int errConv; // ���� ������ ����������
  
  unsigned int Edit_t3_01;
  unsigned int Edit_t3_02;
  unsigned int Edit_t3_03;
  unsigned int Edit_t3_04;
  unsigned int Edit_t3_05;
  unsigned int Edit_t3_06;
  unsigned int Edit_t3_07;
  unsigned int Edit_t3_08;
  unsigned int Edit_t3_09;
  unsigned int Edit_t3_10;
  unsigned int Edit_t3_11;
  unsigned int Edit_t3_12;
  unsigned int Edit_t3_13;
  unsigned int Edit_t3_14;
  unsigned int Edit_t3_15;
  //==// 10.02.2016 DIA ===>>
  //unsigned int Edit_t2_Col2_Row5_DVU;
  //==// 10.02.2016 DIA <<===

  errConv = 0; // ��� ���� ������ �����������  

  Edit_t3_01 = EditHelper::ConvertToInt(Edit_3_01, 0, errConv);
  Edit_t3_02 = EditHelper::ConvertToInt(Edit_3_02, 0, errConv);
  Edit_t3_03 = EditHelper::ConvertToInt(Edit_3_03, 0, errConv);
  Edit_t3_04 = EditHelper::ConvertToInt(Edit_3_04, 0, errConv);
  Edit_t3_05 = EditHelper::ConvertToInt(Edit_3_05, 0, errConv);
  Edit_t3_06 = EditHelper::ConvertToInt(Edit_3_06, 0, errConv);
  Edit_t3_07 = EditHelper::ConvertToInt(Edit_3_07, 0, errConv);
  Edit_t3_08 = EditHelper::ConvertToInt(Edit_3_08, 0, errConv);
  Edit_t3_09 = EditHelper::ConvertToInt(Edit_3_09, 0, errConv);
  Edit_t3_10 = EditHelper::ConvertToInt(Edit_3_10, 0, errConv);
  Edit_t3_11 = EditHelper::ConvertToInt(Edit_3_11, 0, errConv);
  Edit_t3_12 = EditHelper::ConvertToInt(Edit_3_12, 0, errConv);
  Edit_t3_13 = EditHelper::ConvertToInt(Edit_3_13, 0, errConv);
  Edit_t3_14 = EditHelper::ConvertToInt(Edit_3_14, 0, errConv);
  Edit_t3_15 = EditHelper::ConvertToInt(Edit_3_15, 0, errConv);
  //==// 10.02.2016 DIA ===>>
  //Edit_t2_Col2_Row5_DVU = EditHelper::ConvertToInt(Edit_2_Col2_Row5, 0, errConv);
  //==// 10.02.2016 DIA <<===

  if ( errConv == 0 ) // ��� ������ �����������
  {
    Prot->Edit_3_01 = Edit_t3_01; // ����� �����
    Prot->Edit_3_02 = Edit_t3_02; // ����������
    Prot->Edit_3_03 = Edit_t3_03; // ����������� ����
    Prot->Edit_3_04 = Edit_t3_04; // ������������ ����
    Prot->Edit_3_05 = Edit_t3_05; // ������� ����������
    Prot->Edit_3_06 = Edit_t3_06; // ���-�� ����������
    Prot->Edit_3_07 = Edit_t3_07; // ���-�� ������� �����
    Prot->Edit_3_08 = Edit_t3_08; // ������� ������� 1
    Prot->Edit_3_09 = Edit_t3_09; // ������� ������� 2
    Prot->Edit_3_10 = Edit_t3_10; // ������� ������� 3
    Prot->Edit_3_11 = Edit_t3_11; // ���, ��
    Prot->Edit_3_12 = Edit_t3_12; // ����. ������������ ����, ��
    Prot->Edit_3_13 = Edit_t3_13; // ����. ������� �������, ��
    Prot->Edit_3_14 = Edit_t3_14; // ����. ������� �����
    Prot->Edit_3_15 = Edit_t3_15; // ���������� ���, ���. / �
    //Prot->SetDVU(Edit_t2_Col2_Row5_DVU); // ���

    Prot->WriteToBDModBus_BD82();
    ErrorCode = Prot->ReturnVar;
    if (ErrorCode != -1)
    {
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������� ������������ ��������� ModBus");
    }
    else
    {
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������ ������ ���������� ModBus");
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_ModBus_WriteClick(TObject *Sender)
{
  Cprw->flagSostoyaniya = 5;
  Edit_2_Col2_Row5->Text = "4095";
  Edit_2_Col3_Row5->Text = "5,499";
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_ModBus_SetDefClick(TObject *Sender)
{
  Edit_3_02->Text = "250"; // ���������� [��.]
  Edit_3_03->Text = "10"; // ����������� ����
  Edit_3_04->Text = "1000"; // ������������ ����
  Edit_3_05->Text = "10000"; // ������� ����������
  Edit_3_06->Text = "8"; // ���-�� ����������
  Edit_3_07->Text = "4"; // ���-�� �������� �����
  Edit_3_08->Text = "80"; // ������� ������� 1 * 10
  Edit_3_09->Text = "800"; // ������� ������� 2 * 10
  Edit_3_10->Text = "8000"; // ������� ������� 3 * 10
  Edit_3_11->Text = "100"; // ��� [�.]
  Edit_3_12->Text = "1000"; // ����. ������������ ���� [��.]
  Edit_3_13->Text = "7"; // ����. ������� ������� [�.]
  Edit_3_14->Text = "7"; // ����. ������� ����� [�.]
  Edit_3_15->Text = "0"; // ���������� ��� [��� / �.]

  //==\\Edit_2_Col3_Row4->Text = "0,154"; // �������� ��� ��������*
  //==\\Edit_2_Col3_Row5->Text = "2,500"; // �������� ��� ��������*
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::RadioButton_ARCH1Click(TObject *Sender)
{
  //if ( FlagOpros == true )
  {
    Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "��� �����������");
    RadioButton_ARCH1->Color = clLime;
    RadioButton_ARCH2->Color = clBtnFace;
    RadioButton_ARCH3->Color = clBtnFace;
  }
  CheckBox_auto->Enabled = false;
  CheckBox_auto_0_81->Enabled = false;  
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::RadioButton_ARCH2Click(TObject *Sender)
{
  //if ( FlagOpros == true )
  {
    Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "��� ������");
    RadioButton_ARCH1->Color = clBtnFace;
    RadioButton_ARCH2->Color = clYellow;
    RadioButton_ARCH3->Color = clBtnFace;
  }
  CheckBox_auto->Enabled = false;
  CheckBox_auto_0_81->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::RadioButton_ARCH3Click(TObject *Sender)
{
  //if ( FlagOpros == true )
  {
    Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "��� ���������");
    RadioButton_ARCH1->Color = clBtnFace;
    RadioButton_ARCH2->Color = clBtnFace;
    RadioButton_ARCH3->Color = clRed;
  }
  CheckBox_auto->Enabled = true;
  CheckBox_auto_0_81->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::CheckBox_DiodClick(TObject *Sender)
{
  //if ( FlagOpros == true )
  {
    if ( CheckBox_Diod->Checked == true )
    {
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "�������� �������� ����������");
      CheckBox_Diod->Color = clRed;
    }
    else
    {
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "��������� ��. ��.");
      CheckBox_Diod->Color = clBtnFace;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_ARCHClick(TObject *Sender)
{
  Form_ARCH->Prot = this->Prot;
  Form_ARCH->Show();        
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_Sum_SchetClick(TObject *Sender)
{
  if ( Prot->Data.bFlagCount == true )
  {
    Prot->Data.bFlagCount = false;
    Button_Sum_Schet->Caption = "�����";
    Button_Set_Reset->Enabled = true;
    CSpinEdit_time_izm->Enabled = true;
    Button_Sum_Schet->Enabled = false; // ����� ������ ������ �����������, ���� cout �� ������ ����� ����
  }
  else if ( Prot->Data.bFlagCount == false )
  {
    Prot->Data.bFlagCount = true;
    Button_Sum_Schet->Caption = "����";
    Button_Set_Reset->Enabled = false;
    CSpinEdit_time_izm->Enabled = false;
    //Prot->Data.count = 0;
    Prot->Data.SumSchet = 0;
    //Prot->Data.TSchet = 0;
    Prot->Data.Sred = 0;
    Prot->Data.TimeTSchet_dia = 0;
    Prot->Data.T_Limit = CSpinEdit_time_izm->Value; // StrToInt( Edit_time_izm->Text );
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_Set_ResetClick(TObject *Sender)
{
  //Prot->Data.TSchet = 0;
  //Prot->Data.count = 0;
  Prot->Data.SumSchet = 0;
  Edit_3_Col3_Row1->Text = "0";
  Edit_3_Col3_Row2->Text = "0"; // ��������� ���� �� ����� ���������
  Edit_3_Col3_Row3->Text = "0";
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_Out32Click(TObject *Sender)
{
  short ii;
  ii = ComboBox_NomBD->ItemIndex - 1;
  if (f_Out32 == true)
  {
    //===>> Temp
    //==\\char chStr[200];
    //==\\sprintf(chStr, "AddrLPTPort = %d, ii = %d", AddrLPTPort, ii);
    //==\\MessageBox( NULL, chStr, "����", 0 );
    //<<=== Temp
    pOut32( AddrLPTPort, ii );
  }
  else
  {
    if (FlagDebug > 0)
    {
      Memo_For_Print_Errors->Lines->Add(GetCurrentTime() + "������: ������� Out32 �� �������");
    }
  }
}
//---------------------------------------------------------------------------
// ===>> 17.07.2017
void __fastcall TForm_82_Start::ComPort_Or_TcpIp(bool comPortEnabled)
{
  CheckBox_Enabled_Write_TCP->Checked = false;
  if ( comPortEnabled == true )
  {
    Edit_IPAddr->Enabled = false;
    Edit_IPAddr->Visible = false;
    Edit_IPPort->Enabled = false;
    Edit_IPPort->Visible = false;
    ComboBox_NomComPort->Enabled = true;
    ComboBox_NomComPort->Visible = true;
    Button_UpdateComPortsList->Enabled = true;
    Button_UpdateComPortsList->Visible = true;
    Label_NomComPort->Caption = "� COM-�����";
    Label_UpdateComPorts->Caption = "COM-�����";
    Button_OpenBD->Enabled = bFlagDE; // ���� ����������� ������ (� ����������� �� �������� ���-������)
    ButtonSearch->Enabled = bFlagDE; // ���� ����������� ������ (� ����������� �� �������� ���-������)
    EnabledWriteForTCP( true );
    GroupBox_ComPort->Caption = " ����� ����� ";
    Cprw->SetTcpFlag( false );
    Edit_IPAddr->Text = "";
    Edit_IPPort->Text = "";
  }
  else
  {
    Edit_IPAddr->Enabled = true;
    Edit_IPAddr->Visible = true;
    Edit_IPPort->Enabled = true;
    Edit_IPPort->Visible = true;
    ComboBox_NomComPort->Enabled = false;
    ComboBox_NomComPort->Visible = false;
    Button_UpdateComPortsList->Enabled = false;
    Button_UpdateComPortsList->Visible = false;
    Label_NomComPort->Caption = "IP �����";
    Label_UpdateComPorts->Caption = "TCP ����";
    Button_OpenBD->Enabled = true;
    ButtonSearch->Enabled = true;
    Button_SaveAddr->Enabled = true;
    if ( RadioGroup_VyborProtokola->ItemIndex == 2 ) // ��������: ModBus TCP
    {
      EnabledWriteForTCP( false );
      Edit_IPAddr->Text = textIpAddrModBusTcp; // "192.168.3.4"
      Edit_IPPort->Text = textTcpPortModBusTcp; // "502"
    }
    if ( RadioGroup_VyborProtokola->ItemIndex == 3 ) // ��������: ModBus RTU (TCP/IP)
    {
      EnabledWriteForTCP( true );
      Edit_IPAddr->Text = textIpAddrModBusRtuIp; // "192.168.127.254"
      Edit_IPPort->Text = textTcpPortModBusRtuIp; // "4001" 
    }
    GroupBox_ComPort->Caption = " TCP / IP ";
    if ( RadioGroup_VyborProtokola->ItemIndex == 2 || // ��������: ModBus TCP
         RadioGroup_VyborProtokola->ItemIndex == 3 ) // ��������: ModBus RTU (TCP/IP)
    {
      Cprw->SetTcpFlag( true );
    }
  }
}
// <<===  17.07.2017
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::EnabledWriteForTCP( bool Enab )
{ // ���������/��������� ������ � �� � ���������� ModBus TCP
  // ������� ��� ����, ����� �������� � ����� ���� �� �� ������������
  bFlag_Button_WriteToBD = Enab;
  if ( Enab == false )
  {
    //!if ( CheckBox_TCP->Checked == true )//==\\
    if ( RadioGroup_VyborProtokola->ItemIndex == 2 ) // ������ ��������: "ModBus TCP"
    {
      Button_WriteToBD->Enabled = false;
      Button_SaveAddr->Enabled = false;
    }
  }
  else
  {
    //!if ( CheckBox_TCP->Checked == false )
    if ( RadioGroup_VyborProtokola->ItemIndex != 2 ) // ������ ��������: �� "ModBus TCP"
    {
      Button_SaveAddr->Enabled = bFlagDE; // ���� ����������� ������ (� ����������� �� �������� ���-������)
    }
    else
    {
      Button_SaveAddr->Enabled = Enab;
    }
    if ( FlagOpros == true )
    {
      Button_WriteToBD->Enabled = Enab;
    }
  }

  Button_ARCH->Enabled = Enab;
  Button_Puason->Enabled = Enab;
  CheckBox_auto->Enabled = Enab;
  CheckBox_auto_0_81->Enabled = Enab;
  CheckBox_Diod->Enabled = Enab;
  CheckBox_DAuto->Enabled = Enab;
  GroupBox_ARCH->Enabled = Enab;
  RadioButton_ARCH1->Enabled = Enab;
  RadioButton_ARCH2->Enabled = Enab;
  RadioButton_ARCH3->Enabled = Enab;
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_Imp2sekClick(TObject *Sender)
{
  int ProtivOshibkiVypolneniya; // ��������� ������ ��� ��� ��� ����������
  int ProtivOshibkiVypolneniya_2; // ������������� ������ ���������� ���� �������
  if ( (f_Out32 == true) && (f_Inp32 == true) )
  {
    Button_Imp2sek->Enabled = false;
    Button_Imp2sek->Caption = "------";
    try
    {
      StateLPT = pInt32( AddrLPTPort ); // ������� ������ ��������� (������ �) LPT-�����
    }
    catch(...)
    {
    }
    StateLPT |= (1 << 4);
    

    bFlagImp2sek = true; // true - ������ ������ Button_Imp2sek
    bFlagStart = true;
    // ��������� ��������� ������� 3
    TimeInterv = Timer3->Interval;
    bfTimeOnOff = Timer3->Enabled;
    // �������� ������ 3
    Timer3->Interval = 30;
    Timer3->Enabled = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::CheckBox_speedClick(TObject *Sender)
{
  if ( CheckBox_speed->Checked == true )
  {
    Prot->flagSpeed = true;
  }
  else
  {
    Prot->flagSpeed = false;  
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::CheckBox_Enabled_Write_TCPClick(
      TObject *Sender)
{
  if ( CheckBox_Enabled_Write_TCP->Checked == false )
  {
    if ( this->RadioGroup_VyborProtokola->ItemIndex == 1 ) // MobBus
    {
      //if ( CheckBox_TCP->Checked == true )
      if ( RadioGroup_VyborProtokola->ItemIndex == 2 ) // ������ ��������: "ModBus TCP"
      {
        EnabledWriteForTCP( false );
      }
    }
  }
  else
  {
    EnabledWriteForTCP( true );
  }
}
//---------------------------------------------------------------------------
void PressKey( int Key )
{
  // �������� ������� ������� Key
  keybd_event( Key, 0, 0, 0 );
}
//---------------------------------------------------------------------------
void ReleaseKey( int Key )
{
  // �������� ���������� ������� Key
  keybd_event( Key, 0, KEYEVENTF_KEYUP, 0 );
}
//---------------------------------------------------------------------------
void ClickKey( int Key )
{
  // �������� ������ �� ������� Key
  keybd_event( Key, 0, 0, 0 );
  keybd_event( Key, 0, KEYEVENTF_KEYUP, 0 );
}
//---------------------------------------------------------------------------
/*
void TForm_82_Spectr_BD84::DrawPlus
(
    Graphics::TBitmap * BitmapVar, // ������ ������������� BitmapConst
    Graphics::TBitmap * BitmapConst // �� ����������
)
{
  BitBlt
  (
    BitmapVar->Canvas->Handle, // ������ ������������� BitmapConst
    0, 0, Panel_Graph->Width,
    Panel_Graph->Height,
    BitmapConst->Canvas->Handle, // �� ����������
    0, 0,
    SRCAND
  ); // �������� ������� �������
}
*//*
//---------------------------------------------------------------------------
void TForm_82_Start::PressKey( int Key )
{
  // �������� ������� ������� Key
  keybd_event( Key, 0, 0, 0 );
}
//---------------------------------------------------------------------------
void TForm_82_Start::ReleaseKey( int Key )
{
  // �������� ���������� ������� Key
  keybd_event( Key, 0, KEYEVENTF_KEYUP, 0 );
}
//---------------------------------------------------------------------------
void TForm_82_Start::ClickKey( int Key )
{
  // �������� ������ �� ������� Key
  keybd_event( Key, 0, 0, 0 );
  keybd_event( Key, 0, KEYEVENTF_KEYUP, 0 );
}
*/
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_SaveToFileClick(TObject *Sender)
{
  char chS[255];
  //char chTmp[55];
  if ( SaveDialog1->Execute() )
  {
    Memo_SaveLogToFile->Clear();  
    sprintf( chS, "=== ���������� � �� ===" );
    Memo_SaveLogToFile->Lines->Add( chS );

    //fsprintf( chTmp, "%s", "���������� � ��" );
    sprintf( chS, "    �������������� ����� ��: %d", Prot->Data.IndAdr );
    Memo_SaveLogToFile->Lines->Add( chS );
    sprintf( chS, "    ����������� ����������: ��� - %d; �������� - %0.02f [������� �������]", Prot->Data.Temper, Prot->Data.flTemper );
    Memo_SaveLogToFile->Lines->Add( chS );
    sprintf( chS, "    �������� ��� ����������: ��� - %d; �������� - %0.03f [�.]", Prot->Data.DNU, Prot->Data.dbDNU );
    Memo_SaveLogToFile->Lines->Add( chS );
    sprintf( chS, "    �������� ��� ����������: ��� - %d; �������� - %0.03f [�.]", Prot->Data.DVU, Prot->Data.dbDVU );
    Memo_SaveLogToFile->Lines->Add( chS );
    sprintf( chS, "    ���������� ������� ������� (�� 50): ��� - %d; �������� - %0.2f [�.]", Prot->Data.UhiIsr, Prot->Data.dbUhiIsr );
    Memo_SaveLogToFile->Lines->Add( chS );
    sprintf( chS, "    ������������ �������� ���: ��� - %d; �������� - %0.02f [���.]", Prot->Data.SIM3, Prot->Data.dbSIM3 );
    Memo_SaveLogToFile->Lines->Add( chS );
    sprintf( chS, "    ������ ��� ����������: ��� - %d; �������� - %0.02f [���.]", Prot->Data.SIM4, Prot->Data.dbSIM4 );
    Memo_SaveLogToFile->Lines->Add( chS );
    sprintf( chS, "    ��� ���������� ������������: ��� - %d [��.]", Prot->Data.SIM2 );
    Memo_SaveLogToFile->Lines->Add( chS );
    sprintf( chS, "    ������ ���������� (������ = 5): ��� - %d; �������� - %0.02f [�.]", Prot->Data.Ampl, Prot->Data.dbAmpl );
    Memo_SaveLogToFile->Lines->Add( chS );
    sprintf( chS, "    �������. ������ ���������� (�� 50): ��� - %d; �������� - %0.02f [�.]", Prot->Data.LEDAmpRcp, Prot->Data.dbLEDAmpRcp );
    Memo_SaveLogToFile->Lines->Add( chS );
    sprintf( chS, "    ���� � �� �� 1 ���.: %d [���./���.]", Prot->Data.TSchet );
    Memo_SaveLogToFile->Lines->Add( chS );

    sprintf( chS, "=== ��������� ���������� �� ===" );
    Memo_SaveLogToFile->Lines->Add( chS );
    sprintf( chS, "    �������� ��� ��������*: ��� - %d; �������� - %0.03f [�.]", Prot->Data.DNUZ, Prot->Data.dbDNUZ );
    Memo_SaveLogToFile->Lines->Add( chS );
    sprintf( chS, "    �������� ��� ��������*: ��� - %d; �������� - %0.03f [�.]", Prot->Data.DVUZ, Prot->Data.dbDVUZ );
    Memo_SaveLogToFile->Lines->Add( chS );
    sprintf( chS, "    ��� ���������� ��������: %d [��.]", Prot->Data.LEDAmpZ );
    Memo_SaveLogToFile->Lines->Add( chS );
    sprintf( chS, "    ������������ ���� ��������: %d [��.]", Prot->Data.UhiZ );
    Memo_SaveLogToFile->Lines->Add( chS );
    sprintf( chS, "    ������ ��� ���������: %d [��.]", Prot->Data.SIMstartZ );
    Memo_SaveLogToFile->Lines->Add( chS );
    sprintf( chS, "    ������ ��� �����������: %d [��.]", Prot->Data.SIMminZ );
    Memo_SaveLogToFile->Lines->Add( chS );
    sprintf( chS, "    �������� ������ ����������: %d [��.]", Prot->Data.LedZadZ );
    Memo_SaveLogToFile->Lines->Add( chS );
    sprintf( chS, "    �������� �����: %0.6d [��.]", Prot->Data.m_ulSerialNumberZ );
    Memo_SaveLogToFile->Lines->Add( chS );
    sprintf( chS, "    ����. ��� ������� ����. ���: ��� - %d;  �������� - %0.02f", Prot->Data.m_ulU0Z, Prot->Data.dbm_ulU0Z );
    Memo_SaveLogToFile->Lines->Add( chS );
    sprintf( chS, "    ����. ���.*: ��� - %d;  �������� - %0.02f", Prot->Data.m_ulUZ, Prot->Data.dbm_ulUZ );
    Memo_SaveLogToFile->Lines->Add( chS );
    sprintf( chS, "    ������. �������� (0...31): %s", Prot->Data.m_strStickyNote );
    Memo_SaveLogToFile->Lines->Add( chS );
    sprintf( chS, "=== ������ ��������: %s ===", Prot->Data.Ver );
    Memo_SaveLogToFile->Lines->Add( chS );

    if (flagModbusProtokol != 0) // �������� �� "9-�� ������"
    {
      if ( Prot->Data.TimeZapuskBD >= 60 )
      {
        sprintf( chS, "=== ����� �� ������� ��: %d [���.] ===", Prot->Data.TimeZapuskBD );
      }
      else
      {
        sprintf( chS, "!!! ����� �� ������� ��: %d < 60 [���.], �� �� ����� �� ����� !!!!!!!!!!!!!!!!!!!!!!!!", Prot->Data.TimeZapuskBD );
      }
      Memo_SaveLogToFile->Lines->Add( chS );
    }
    //==\\RichEdit_SaveLogToFile->Lines->SaveToFile( SaveDialog1->FileName );
    Memo_SaveLogToFile->Lines->SaveToFile( SaveDialog1->FileName );
  }
}
//---------------------------------------------------------------------------
bool VersiaPoForZvukOn(char VERSIA[5])
{
  int ver;
  //if ( VERSIA[1] == '.' ) // 5.11
  //{
  //  ver = (VERSIA[0] - '0') * 100; // ������� ����
  //  ver += (VERSIA[2] - '0') * 10; // ������� ����
  //  ver += (VERSIA[3] - '0');
  //}
  if ( VERSIA[0] == '8' )
  {
    return true;
  }
  if ( VERSIA[0] == '5' )
  {
    ver = (VERSIA[0] - '0') * 100; // ������� ����
    ver += (VERSIA[2] - '0') * 10; // ������� ����
    ver += (VERSIA[3] - '0');
    if ( ver == 511 )
    {
      return true;
    }
  }
  return false;
}
//---------------------------------------------------------------------------
// �������� ����
void __fastcall TForm_82_Start::ZvukOn(void)
{
  ErrorCode = Prot->GetVersia(Prot->Data.Ver);
  if ( ErrorCode == 0 ) // ���� ������ �����������
  {
    //if ( Prot->Data.Ver[0] == '8' )
    if ( VersiaPoForZvukOn ( Prot->Data.Ver ) )
    {
      Prot->Set_P37(); // ���������� P3.7
    }
    else
    {
      //==\\ShowMessage( "������ ������� ����������� � ��������� v8.xx" );
    }
  }
  else
  {
    //==\\ShowMessage( "�� ������� ��������� ������ ��������" );
  }
}
//---------------------------------------------------------------------------
// ��������� ����
void __fastcall TForm_82_Start::ZvukOff(void)
{
  ErrorCode = Prot->GetVersia(Prot->Data.Ver);
  if ( ErrorCode == 0 ) // ���� ������ �����������
  {
    //if ( Prot->Data.Ver[0] == '8' )
    if ( VersiaPoForZvukOn ( Prot->Data.Ver ) )
    {
      Prot->Reset_P37(); // �������� P3.7
    }
    else
    {
      //==\\ShowMessage( "������ ������� ����������� � ��������� v8.xx" );
    }
  }
  else
  {
    //==\\ShowMessage( "�� ������� ��������� ������ ��������" );
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_P3_7_SetClick(TObject *Sender)
{
  ErrorCode = RSConnect( ComboBox_NomComPort->Text.c_str() );
  if ( ErrorCode == 0 ) // ���� ���� �������� ��� ��� ��� ������
  {
    ErrorCode = Prot->GetVersia(Prot->Data.Ver);
    if ( ErrorCode == 0 ) // ���� ������ �����������
    {
      if ( Prot->Data.Ver[0] == '8' )
      {
        Prot->Set_P37(); // ���������� P3.7
      }
      else
      {
        ShowMessage( "������ ������� ����������� � ��������� v8.xx" );
      }
    }
    else
    {
      ShowMessage( "�� ������� ��������� ������ ��������" );
    }
  }
  else
  {
    ShowMessage( "�� ������� ������� ���-����" );
  }
  RSDisConnect();
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_P3_7_ResetClick(TObject *Sender)
{
  ErrorCode = RSConnect( ComboBox_NomComPort->Text.c_str() );
  if ( ErrorCode == 0 ) // ���� ���� �������� ��� ��� ��� ������
  {
    ErrorCode = Prot->GetVersia(Prot->Data.Ver);
    if ( ErrorCode == 0 ) // ���� ������ �����������
    {
      if ( Prot->Data.Ver[0] == '8' )
      {
        Prot->Reset_P37(); // �������� P3.7
      }
      else
      {
        ShowMessage( "������ ������� ����������� � ��������� v8.xx" );
      }
    }
    else
    {
      ShowMessage( "�� ������� ��������� ������ ��������" );
    }
  }
  else
  {
    ShowMessage( "�� ������� ������� ���-����" );
  }
  RSDisConnect();
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_P37SetResetMouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
  //==\\Button_P3_7_Set->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm_82_Start::Button_P37SetResetMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  //==\\Button_P3_7_Reset->Click();        
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_SpectrClick(TObject *Sender)
{
  RadioGroup_VyborProtokola->Enabled = false;
  flagModbusProtokol = RadioGroup_VyborProtokola->ItemIndex;
  Prot->flagModbusProtokol = flagModbusProtokol;
  Form_82_Spectr_BD84->SpinEdit_TimeSpektrChange( NULL );
  Form_82_Spectr_BD84->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_ImageClick(TObject *Sender)
{
  AnsiString asPathDir, asPathFile;


  try
  {
    BMCopy = new Graphics::TBitmap;
    BMCopy->Width = Form_82_Start->ClientWidth;
    BMCopy->Height = Form_82_Start->ClientHeight;
  }
  catch ( ... )
  {
    ShowMessage("new Graphics::TBitmap!");
    CheckBox_Image->Checked = false;
  }
  //
  try
  {
    jpg = new TJPEGImage;
  }
  catch ( ... )
  {
    ShowMessage("new TJPEGImage!");
    CheckBox_Image->Checked = false;
  }
  iAP = PageControl_ModBus_Settings->ActivePageIndex; // �������� ������� ( 0 ... 3 )
  PageControl_ModBus_Settings->ActivePageIndex = 0;
  Sleep( 300 ); //==\\
  try
  {
    BitBlt
      (
        BMCopy->Canvas->Handle,
        0, 0, Form_82_Start->ClientWidth,
        Form_82_Start->ClientHeight,
        NULL,
        0, 0,
        WHITENESS
      ); // �������� ������� �������

    BitBlt
      (
        BMCopy->Canvas->Handle, // ������ ������������� BitmapConst
        0, 0, Form_82_Start->ClientWidth,
        Form_82_Start->ClientHeight,
        Form_82_Start->Canvas->Handle, // �� ����������
        0, 0,
        SRCAND
      ); // ����������� ������� �������
  }
  catch ( ... )
  {
    ShowMessage("������ ����������� ������!");
  }
  jpg->Grayscale = !this->CheckBox_Image->Checked; //==\\ ������� ������?
  jpg->Assign( BMCopy );
  jpg->CompressionQuality = 60; // ������� ������
  jpg->Compress();
  bool bfErrorDir;
  bfErrorDir = false;
  asPathDir = GetCurrentDir(); // ������� ����������
  asPathDir += "\\�������� ������ �� ����� (screenshot)";
  asPathFile = "��";
  if ( Edit_StantsiyaMetro->Text.Length() > 0 )
  {
    if ( Edit_StantsiyaMetro->Text != Edit_2_Col2_4_Row_14->Text )
    {
      ShowMessage("��������, ����� ���� \"�������� ������� �������������\" �� ����� � ���� \"�������. �������� (0 ... 31)\"!");
    }
    else  if ( bf_Zabyvchivosti == false )
      {
        // ����� ����� � ������, �� �� ������ � ���� ����������
        // ���� ���� ��������������� � false
        // ����� �������� ������ (��� ���� ��������� ��� ������ �� ����������) - � true.
        // ������������ ��� ����������� � ���,
        // ��� ������ ���������� �� �������������
        // ��� ������� ����������������� ����� � �����.
        ShowMessage("��������, ����� ���� \"�������. �������� (0 ... 31)\" �� ����� � ������ ��!");
      }

    asPathDir += "\\";
    asPathDir += Edit_StantsiyaMetro->Text;
  }

  if ( SpinEdit_AddrBD->Text.Length() > 0 )
  {
    asPathFile += "_";
    asPathFile += SpinEdit_AddrBD->Text;
  }

  if ( DirectoryExists( asPathDir.c_str() ) == false )
  {
    if ( ForceDirectories( asPathDir.c_str() ) == false )
    {
      // � ������� �� CreateDir ������� ForceDirectories ������ ���
      // ��������� � ���������� ������� ���������, ���� ���� �������������
      // �������� �� ����������
      //==\\return false;
      bfErrorDir = true;
      ShowMessage("������, �� ���� ������� ������� (�����)!");
    }
  }

  if ( bfErrorDir == false )
  {
    asPathDir += "\\";
    asPathFile = asPathDir + asPathFile;
    asPathFile += ".jpg";
    //==\\jpg->SaveToFile( "Foto.jpg" );
    jpg->SaveToFile( asPathFile.c_str() ); //==\\
    //==\\BMCopy->SaveToFile( "Foto.bmp" );
  }
  try
  {
    delete BMCopy;
  }
  catch ( ... )
  {
    ShowMessage("delete BMCopy!");
    //==\\CheckBox_Image->Checked = false;
  }
  //
  try
  {
    delete jpg;
  }
  catch ( ... )
  {
    ShowMessage("delete jpg!");
    //==\\CheckBox_Image->Checked = false;
  }
  //Form_Image->Show();
  //==\\CheckBox_Image->Checked = false;

  iFlagTimer2 = 2;
  Timer2->Interval = 300;
  Timer2->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm_82_Start::Button_ToCommentClick(TObject *Sender)
{
  Edit_2_Col2_4_Row_14->Text = Edit_StantsiyaMetro->Text;        
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::BitBtn_P37SetResetMouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
  BitBtn_P37SetReset->Font->Color = clRed;
  bfZvukOn = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::BitBtn_P37SetResetMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  BitBtn_P37SetReset->Font->Color = clWindowText;
  bfZvukOff = true;
}
//---------------------------------------------------------------------------
void TForm_82_Start::ZvukOnOff()
{
    if ( bfZvukOn == true )
    {
        bfZvukOn = false;
        ZvukOn();
    }
    if ( bfZvukOff == true )
    {
        bfZvukOff = false;
        ZvukOff();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Timer3Timer(TObject *Sender)
{
  if (bFlagImp2sek == true)
  {
    if (bFlagStart == true)
    {
      Timer3->Interval = 2000; // 2 ���.
      bFlagStart = false;
      try
      {
        pOut32( AddrLPTPort, StateLPT );
      }
      catch(...)
      {
      }
    }
    else
    {
      //StateLPT = pInt32( AddrLPTPort );
      StateLPT &= ~(1 << 4);

      Button_Imp2sek->Caption = "���. (2 ���.)";
      Button_Imp2sek->Enabled = true;
      try
      {
        pOut32( AddrLPTPort, StateLPT );
      }
      catch(...)
      {
      }
      // ������������ ��������� �������
      Timer3->Interval = TimeInterv; //==\\
      Timer3->Enabled = bfTimeOnOff; //==\\
      bFlagImp2sek = false;
    }
    return;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm_82_Start::Button_PlusClick(TObject *Sender)
{
  if(SpinEdit_AddrBD->Value < SpinEdit_AddrBD->MaxValue)
  {
    SpinEdit_AddrBD->Value++;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Button_MinusClick(TObject *Sender)
{
  if(SpinEdit_AddrBD->Value > SpinEdit_AddrBD->MinValue)
  {
    SpinEdit_AddrBD->Value--;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::CheckBox_auto_0_81Click(TObject *Sender)
{
  if (CheckBox_auto_0_81->Checked == true)
  {
    if (!AutoPodborProverka())
    {
      return;
    }
    AutoPodborStart();
  }
  else //==\\ if (CheckBox_auto_0_81->Checked == false)
  {
    AutoPodborEnd();
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::CheckBox_DAuto_StandartClick(
      TObject *Sender)
{
  if(CheckBox_DAuto_Standart->Checked)
  {
    CheckBox_DAuto_Shirokie->Enabled = false;
    CheckBox_DAuto_Shirokie->Checked = false;
    //
    CheckBox_DAuto_Rengen->Enabled = false;
    CheckBox_DAuto_Rengen->Checked = false;
    SetDnuAndDvuStart(1); // ��������
  }
  else
  {
    CheckBox_DAuto_Shirokie->Enabled = true;
    CheckBox_DAuto_Rengen->Enabled = true;
    SetDnuAndDvuEnd();
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::CheckBox_DAuto_ShirokieClick(
      TObject *Sender)
{
  if(CheckBox_DAuto_Shirokie->Checked)
  {
    CheckBox_DAuto_Standart->Enabled = false;
    CheckBox_DAuto_Standart->Checked = false;
    //
    CheckBox_DAuto_Rengen->Enabled = false;
    CheckBox_DAuto_Rengen->Checked = false;
    SetDnuAndDvuStart(2); // �������
  }
  else
  {
    CheckBox_DAuto_Standart->Enabled = true;
    CheckBox_DAuto_Rengen->Enabled = true;
    SetDnuAndDvuEnd();
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::CheckBox_DAuto_RengenClick(TObject *Sender)
{
  if(CheckBox_DAuto_Rengen->Checked)
  {
    CheckBox_DAuto_Standart->Enabled = false;
    CheckBox_DAuto_Standart->Checked = false;
    //
    CheckBox_DAuto_Shirokie->Enabled = false;
    CheckBox_DAuto_Shirokie->Checked = false;
    SetDnuAndDvuStart(3); // ������
  }
  else
  {
    CheckBox_DAuto_Standart->Enabled = true;
    CheckBox_DAuto_Shirokie->Enabled = true;
    SetDnuAndDvuEnd();
  }
}
//---------------------------------------------------------------------------
// ���������� ��������� ��� � ��� (1 - ��������, 2 - �������, 3 - ������)
void TForm_82_Start::SetDnuAndDvuStart(int mode)
{
  int DnuKod;
  int DvuKod;
  double DnuValue;
  double DvuValue;
  DnuAndDvuMode = true;
  if (mode == 1) // ��������
  {
    DnuKod = 115;
    DvuKod = 687;
    DnuValue = 0.154;
    DvuValue = 0.922;
    Prot->Set_CheckBox_DAuto_Checked(
        false, // ��� - ����������
        false); // ��� - ����������
  }
  else if (mode == 2) // �������
  {
    Prot->Set_CheckBox_DAuto_Checked(
        false, // ��� - ����������
        true); // ��� - ��� �����������
    DnuKod = 115;
    DvuKod = 2047;
    DnuValue = 0.154;
    DvuValue = 2.74;
  }
  else if (mode == 3) // ������
  {
    Prot->Set_CheckBox_DAuto_Checked(
        false, // ��� - ����������
        true); // ��� - ��� �����������
    DnuKod = 298;
    DvuKod = 2047;
    DnuValue = 0.400;
    DvuValue = 2.74;
  }
  else
  {
    DnuAndDvuMode = false;
    return; // ����������� ���� �� �������: 1, 2 ��� 3
  }
  if ( RadioGroup_KOD->ItemIndex == 0 ) // ���
  {
    Edit_2_Col2_Row4->Text = IntToStr( DnuKod );
    if ( mode == 1 )
    {
      Edit_2_Col2_Row5->Text = IntToStr( DvuKod );
    }
  }
  else if ( RadioGroup_KOD->ItemIndex == 1 )
  {
    Edit_2_Col3_Row4->Text = FloatToStrF( DnuValue, ffGeneral, tochnost_DNU /* �������� */, 8 /* ����� ���� */ );
    if ( mode == 1 )
    {
      Edit_2_Col3_Row5->Text = FloatToStrF( DvuValue, ffGeneral, tochnost_DVU /* �������� */, 8 /* ����� ���� */ );
    }
  }
  //Button_WriteToBDClick( (void*)0 );
  CheckBox_DAuto->Checked = true;
}
//---------------------------------------------------------------------------
// ��������� ��������� ��� � ��� (����� ���� ������������� �������, ���� ����������� �� �����)
void TForm_82_Start::SetDnuAndDvuEnd()
{
  CheckBox_DAuto->Checked = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Start::Edit_2_Col2_4_Row_14Change(TObject *Sender)
{
  AnsiString asMax24 = Edit_2_Col2_4_Row_14->Text;
  int len = asMax24.Length();
  if (len > 24)
  {
    Edit_2_Col2_4_Row_14->Text = asMax24.SubString(1, 24);
  }
}
//---------------------------------------------------------------------------

