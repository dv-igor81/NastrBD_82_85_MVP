//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Window_UpdateThis.h"
//---------------------------------------------------------------------------
#include "Unit_FormDispet.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TWindow_Updater *Window_Updater;
//---------------------------------------------------------------------------
__fastcall TWindow_Updater::TWindow_Updater(TComponent* Owner)
        : TForm(Owner)
        ,_bfDebuf( 1 )
{
}
//---------------------------------------------------------------------------
void TWindow_Updater::Step_01()
{
    this->Timer->Enabled = false;
    int deystvie = _writeSelf.StartProgramm(); // ��������� ������ ����
    AnsiString localFileName = ParamStr( 0 ); // ��� �������� �����
    AnsiString remoteFileName =
      "\\\\fileserver\\Change\\Podr-56\\�������� ����� ������������� (DIA)\\Updater\\NastrBD\\NastrBD_82_85.exe";
    AnsiString remoteFileNameFake = "C:\\Updater\\NastrBD\\NastrBD_82_85.exe";

    int test;
    switch ( deystvie )
    {
    case 1: // 1 - ��
        this->Panel_Display->Caption = "�������� ����������";
        this->Label_Display->Caption = "��������� ���������";
        test = _writeSelf.ReadUpdatedProg(localFileName, remoteFileName, remoteFileNameFake);
        if ( test == 1 ) // ���� ����������
        {
          _writeSelf.UpdatedWriteFile(); // ������� ������������� ���� �� ������������
          this->Timer->Enabled = true;
          this->Timer->Interval = 1000;
        }
        else if (test == 2) // ���������� ������
        {
          _writeSelf.MyWriteFile(); // ������� ������������� ���� �� ����
          this->Timer->Enabled = true;
          this->Timer->Interval = 1000;
        }
        else if (test == 3)
        {
          this->Panel_Display->Caption = "fileserver ����������, ���� ��������� ���� �������";
          this->Label_Display->Caption = "fileserver ����������, ���� ��������� ���� �������";
          Label_Count->Caption = _writeSelf.AnalisFile(); // ������ � ��������
          Label_VersiyaPo->Caption = _writeSelf.AnalisFileVerPo(); // ������ ��
          // �������� ��� �����, ���������� �������� �����
          // ...
          this->Timer->Enabled = true;
          this->Timer->Interval = 2000;
          _step = 3;
        }
        else if (test == 0) // ��� ����� � ����������
        {
          // ��� ���������� - ��� ����� ��������� ������������� ����
          this->Panel_Display->Caption = "����������� ��������� ������";
          this->Label_Display->Caption = "����������� ��������� ������";
          Label_Count->Caption = _writeSelf.AnalisFile(); // ������ � ��������
          Label_VersiyaPo->Caption = _writeSelf.AnalisFileVerPo(); // ������ ��
          // �������� ��� �����, ���������� �������� �����
          // ...
          this->Timer->Enabled = true;
          this->Timer->Interval = 2000;
          _step = 3;
        }
        // ===>> ������� ����� ���������
        //Visible = false;
        //Application->ShowMainForm = false;
        // <<=== ������� ����� ���������
        break;
    case 2: // 2 - ��
        this->Label_Display->Caption = "===}{===";
        _bfTimerFirst = true; // ��������� ���������� ��������� ��������� (������ ��� �� ������)
        // ===>> ������� ����� ���������
        Visible = false;
        Application->ShowMainForm = false;
        // <<=== ������� ����� ���������
        this->Timer->Enabled = true;
        this->Timer->Interval = 1000;
        break;
    case 3: // 3 - ��
        this->Panel_Display->Caption = "���������� ������� ���������";
        this->Label_Display->Caption = "������������� ���������";
        _bfTimerFirst = true; // ��������� ���������� ������������� ��������� (������ ��� �� ������)
        this->Timer->Enabled = true;
        this->Timer->Interval = 1000;
        //_step = 3;
        break;
    case 4: // 4 - ���� �� ������ (������ ������)
        this->Panel_Display->Caption = "������ ������: ��������� ������ ��� �� ��������";
        this->Label_Display->Caption = "������ ������";
        _writeSelf.MyWriteFile(); // ������� ������������� ����
        this->Timer->Enabled = true;
        this->Timer->Interval = 1000;
        break;
    }
}
//---------------------------------------------------------------------------
void TWindow_Updater::Step_02()
{
    int deystv = _writeSelf.GetFlag();
    if ( deystv == 0 )
    {
        return;
    }
    this->Timer->Enabled = false;
    switch ( deystv )
    {
    case 1: // 1 - ��
    case 4: // 4 - ���� �� ������ (������ ������)
        _writeSelf.MyWinExec(); // ��������� ������������� ���������
        Close(); // ��������� ����������
        break;
    case 2: // 2 - ��
        if ( this->_bfTimerFirst == true )
        {
            // ������������ ��������� ���������, �������������
            _writeSelf.MyWriteFile(); // ������� ���� ������������� ���������
            // ���������, ���� ������ ���������
            this->_bfTimerFirst = false;
            this->Timer->Enabled = true;
        }
        else
        {
            _writeSelf.MyWinExec(); // ��������� ������������� ���������
            Close(); // ��������� ����������
        }
        break;
    case 3: // 3 - ��
        SetLastError( 0 );
        if ( DeleteFile( _writeSelf.GetNewFileName() ) == 0 ) // ������
        {
            int errCod = GetLastError();
            AnsiString errStr = "DeleteFile: ";
            errStr += SysErrorMessage( errCod );
            Mess( errStr, 1 );
        }
        else
        {
            Mess( "DeleteFile: OK", 2 );

        }
        this->Panel_Display->Caption = "}���������� ������� ���������{";
        this->Label_Display->Caption = "�������� �� ��";
        Label_Count->Caption = _writeSelf.AnalisFile(); // ������ � ��������
        Label_VersiyaPo->Caption = _writeSelf.AnalisFileVerPo(); // ������ ��
        _writeSelf.SetReady(); // ���������� ���� ���������� (��� ������ ��������)
        this->Timer->Enabled = true;
        this->Timer->Interval = 1000;
        _step = 3;        
        break;
    }
}
//---------------------------------------------------------------------------
void TWindow_Updater::Step_03()
{
  this->Timer->Enabled = false;
  this->Hide();
  FormDispet->Show();
}
//---------------------------------------------------------------------------
// ��������� �������� �� ����-�������?
bool TWindow_Updater::ProgramStartFromFileServer()
{
  AnsiString localFileName = ParamStr( 0 ); // ��� �������� �����
  if ( FileExists("DebugDiaMess_VNIIA.txt" ) )
  {
    Application->MessageBox(
          localFileName.c_str(),
          "NastrBD82_85.exe",
          MB_ICONSTOP);
  }
  //localFileName = localFileName.LowerCase(); // � ������� ��������
  localFileName = localFileName.UpperCase(); // � �������� ��������
  if (
    localFileName.Pos("\\\\FILESERVER\\") == 1 || // � ���������������� �����
    localFileName.Pos("\\\\IGOR81-PC\\") == 1 ) // ����� ����������� �� ���� �����
  {
    return true; // ��, ������� ����� ����������� ������ '\\fileserver\'
  }
  AnsiString bukvaDiska = localFileName.SubString(0, 1);
  char Drives[255];
  PChar P;
  AnsiString AllBukvDiskov; // ��� ����� ������ (����� �������)
  if ( GetLogicalDriveStrings( 256, Drives ) > 256 )
  {
    return false; // �������, ��� ���� �� �������, �.�. ������
  }
  AllBukvDiskov = "";
  P = Drives;
  while ( *P != 0 )
  {
    if ( GetDriveType( P ) != DRIVE_REMOTE ) // ���� �� �������� ������� (������� �� ������ ������)
    { // ������, ��� ������ ������� ����� � ���� ������ � ��� �����������!!!
      AllBukvDiskov += AnsiString( P );
    }
    P += 4; // � ��������� ����� �����
  }
  AllBukvDiskov = AllBukvDiskov.UpperCase(); // � �������� ��������
  if ( AllBukvDiskov.Pos(bukvaDiska) == 0 )
  {
    return true; // ������� ����
  }
  return false;
}
//---------------------------------------------------------------------------
void __fastcall TWindow_Updater::FormCreate(TObject *Sender)
{
  if ( ProgramStartFromFileServer() )
  {
    Application->ShowMainForm = false; // ������ ����� (�������� Visible ������ ���� ����������� � false - � ���������, � �� ���������� �����)
    //ShowMessage( "��� ��������� ������� ���������, ���������� � � ���� �� ����. ������ �� fileserver ��������." );
    Application->MessageBox(
          "��� ��������� ������� ���������, ���������� � � ���� �� ����. ������ �� fileserver ��������.",
          "NastrBD82_85.exe",
          MB_ICONSTOP);
    _step = 4;
  }
  else if ( FileExists("NoUpdate.txt") )
  {
    _step = 3; // �� ��������� ����������
  }
  else
  {
    _step = 1;
  }
  this->Timer->Enabled = true;
  this->Timer->Interval = 100;
}
//---------------------------------------------------------------------------
void __fastcall TWindow_Updater::TimerTimer(TObject *Sender)
{
    if (_step == 1)
    {
        _step = 2;
        Step_01();
    }
    else if (_step == 2)
    {
        Step_02();
    }
    else if (_step == 3)
    {
        Step_03(); // ��������� ���������
    }
    else if (_step == 4)
    {
        Close();
    }    
}
//---------------------------------------------------------------------------
void TWindow_Updater::Mess( AnsiString text, int Level )
{
  if ( _bfDebuf >= Level )
  {
    ShowMessage( text );
  }
}
//---------------------------------------------------------------------------
void __fastcall TWindow_Updater::Button_ResetClick(TObject *Sender)
{
    // ���� ������� �� ����� ��������
    if ( ! _writeSelf.Reset() ) // ������ ��� _writeSelf.GetFlag() == 3 ( �� )
    {
        return; // �� ����� �������� ��������
    }
    // ������� ������������� ����
    _bfTimerFirst = true; // ������ ��������� ������� ��� ���� (������ ����� ������ ������)
    Timer->Enabled = true;  
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

