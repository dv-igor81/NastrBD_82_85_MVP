#include <vcl.h>
#pragma hdrstop
#include "Unit_82_Form_Start.h"
#include "Unit_82_Form_ARCH.h"
#include "Unit_82_Priklad_Funk.h"
#include "Unit_82_FileDirect.h"
#include "Unit_82_Form_RearFromEEPROM.h"
#include "Unit_82_Form_LoadParam.h"
//#include "Unit_82_RSProtokol.h"
#include "RSProtokol.h"
//---------------------------------------------------------------------------
#ifdef _DIA_OBEDINENIE_
  #include "Unit_FormDispet.h"
#endif
//---------------------------------------------------------------------------
#include <Inifiles.hpp>
#include <list.h>
#include <math.h>
// pow()
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
#define KOL_ZN 19
//#define KOL_ZN 255
//---------------------------------------------------------------------------
TForm_ARCH * Form_ARCH;
extern bool flagPort; // ��������� ����� ������ (true)/������ (false)
//---------------------------------------------------------------------------
extern const char * IniFileName;
int UgolTangens;
int del; // ���������� �����������
unsigned char kol_zn = KOL_ZN;
unsigned char MasT[KOL_ZN];
unsigned char MasS[KOL_ZN];
int Temp[KOL_ZN];
int Sveto[KOL_ZN];
AnsiString TempKamera[KOL_ZN];

Set<char, '0', '9'> Dig;
bool FlagGrafikKnopka = false;

int T_MAX = 0;
int T_MIN;
int SVETO_MAX = 0;
int SVETO_MIN;
//---------------------------------------------------------------------------
unsigned int YMAX = 255;
AnsiString filename;
FileDirect fD;
//---------------------------------------------------------------------------
__fastcall TForm_ARCH::TForm_ARCH(TComponent* Owner)
        : TForm(Owner)
{
  Edit_KolVoPoints->Text = "0";
  err = 0;
  VisEdit();
  FlagGrafik = false;
  Dig << '0' << '1' << '2' << '3' << '4'
      << '5' << '6' << '7' << '8' << '9'; // ���������� ���������
  FlagFile = false;
  FlagEEPROM = false;
  FlagGrafik = false;

  TIniFile * IniFile = new TIniFile(IniFileName);
  try
  {
    m_strLogFileName = IniFile->ReadString("Form ARCH Settings", "LogFileName", "NastrBD.log");
    delete IniFile;
  }
  catch (...)
  {
    delete IniFile;
    ShowMessage("�������� ���������� ��� ������ �������� *.ini");    
  }
  /*DWORD style;
  style = GetWindowLong(this->Handle, GWL_EXSTYLE);
  style |= WS_EX_APPWINDOW;
  SetWindowLong(this->Handle,GWL_EXSTYLE, style);*/
}
//---------------------------------------------------------------------------
void __fastcall TForm_ARCH::FormHide(TObject *Sender)
{
  Form_82_Start->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm_ARCH::FormShow(TObject *Sender)
{
#ifdef _DIA_OBEDINENIE_
  if( FormDispet != 0 )
  {
    FormDispet->DiaGetWinHandle( this->Handle );  
  }
#endif  
  Form_82_Start->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm_ARCH::UpDown_KolVoPointsClick(TObject *Sender,
      TUDBtnType Button)
{
  VisEdit();
}
//---------------------------------------------------------------------------
void __fastcall TForm_ARCH::VisEdit(void)
{
  Edit_temperKam_01->Visible = false;
  Edit_kodTemper_01->Visible = false;
  Edit_kodSvd_01->Visible = false;
  Edit_temperKam_02->Visible = false;
  Edit_kodTemper_02->Visible = false;
  Edit_kodSvd_02->Visible = false;
  Edit_temperKam_03->Visible = false;
  Edit_kodTemper_03->Visible = false;
  Edit_kodSvd_03->Visible = false;
  Edit_temperKam_04->Visible = false;
  Edit_kodTemper_04->Visible = false;
  Edit_kodSvd_04->Visible = false;
  Edit_temperKam_05->Visible = false;
  Edit_kodTemper_05->Visible = false;
  Edit_kodSvd_05->Visible = false;
  Edit_temperKam_06->Visible = false;
  Edit_kodTemper_06->Visible = false;
  Edit_kodSvd_06->Visible = false;
  Edit_temperKam_07->Visible = false;
  Edit_kodTemper_07->Visible = false;
  Edit_kodSvd_07->Visible = false;
  Edit_temperKam_08->Visible = false;
  Edit_kodTemper_08->Visible = false;
  Edit_kodSvd_08->Visible = false;
  Edit_temperKam_09->Visible = false;
  Edit_kodTemper_09->Visible = false;
  Edit_kodSvd_09->Visible = false;
  Edit_temperKam_10->Visible = false;
  Edit_kodTemper_10->Visible = false;
  Edit_kodSvd_10->Visible = false;
  Edit_temperKam_11->Visible = false;
  Edit_kodTemper_11->Visible = false;
  Edit_kodSvd_11->Visible = false;
  Edit_temperKam_12->Visible = false;
  Edit_kodTemper_12->Visible = false;
  Edit_kodSvd_12->Visible = false;
  Edit_temperKam_13->Visible = false;
  Edit_kodTemper_13->Visible = false;
  Edit_kodSvd_13->Visible = false;
  Edit_temperKam_14->Visible = false;
  Edit_kodTemper_14->Visible = false;
  Edit_kodSvd_14->Visible = false;
  Edit_temperKam_15->Visible = false;
  Edit_kodTemper_15->Visible = false;
  Edit_kodSvd_15->Visible = false;
  Edit_temperKam_16->Visible = false;
  Edit_kodTemper_16->Visible = false;
  Edit_kodSvd_16->Visible = false;
  Edit_temperKam_17->Visible = false;
  Edit_kodTemper_17->Visible = false;
  Edit_kodSvd_17->Visible = false;
  Edit_temperKam_18->Visible = false;
  Edit_kodTemper_18->Visible = false;
  Edit_kodSvd_18->Visible = false;
  Edit_temperKam_19->Visible = false;
  Edit_kodTemper_19->Visible = false;
  Edit_kodSvd_19->Visible = false;
  for ( int i = 0; i < this->UpDown_KolVoPoints->Position+1; i++ )
  {
    switch ( i )
    {
    case 1:
      Edit_temperKam_01->Visible = true;
      Edit_kodTemper_01->Visible = true;
      Edit_kodSvd_01->Visible = true;
      break;
    case 2:
      Edit_temperKam_02->Visible = true;
      Edit_kodTemper_02->Visible = true;
      Edit_kodSvd_02->Visible = true;
      break;
    case 3:
      Edit_temperKam_03->Visible = true;
      Edit_kodTemper_03->Visible = true;
      Edit_kodSvd_03->Visible = true;
      break;
    case 4:
      Edit_temperKam_04->Visible = true;
      Edit_kodTemper_04->Visible = true;
      Edit_kodSvd_04->Visible = true;
      break;
    case 5:
      Edit_temperKam_05->Visible = true;
      Edit_kodTemper_05->Visible = true;
      Edit_kodSvd_05->Visible = true;
      break;
    case 6:
      Edit_temperKam_06->Visible = true;
      Edit_kodTemper_06->Visible = true;
      Edit_kodSvd_06->Visible = true;
      break;
    case 7:
      Edit_temperKam_07->Visible = true;
      Edit_kodTemper_07->Visible = true;
      Edit_kodSvd_07->Visible = true;
      break;
    case 8:
      Edit_temperKam_08->Visible = true;
      Edit_kodTemper_08->Visible = true;
      Edit_kodSvd_08->Visible = true;
      break;
    case 9:
      Edit_temperKam_09->Visible = true;
      Edit_kodTemper_09->Visible = true;
      Edit_kodSvd_09->Visible = true;
      break;
    case 10:
      Edit_temperKam_10->Visible = true;
      Edit_kodTemper_10->Visible = true;
      Edit_kodSvd_10->Visible = true;
      break;
    case 11:
      Edit_temperKam_11->Visible = true;
      Edit_kodTemper_11->Visible = true;
      Edit_kodSvd_11->Visible = true;
      break;
    case 12:
      Edit_temperKam_12->Visible = true;
      Edit_kodTemper_12->Visible = true;
      Edit_kodSvd_12->Visible = true;
      break;
    case 13:
      Edit_temperKam_13->Visible = true;
      Edit_kodTemper_13->Visible = true;
      Edit_kodSvd_13->Visible = true;
      break;
    case 14:
      Edit_temperKam_14->Visible = true;
      Edit_kodTemper_14->Visible = true;
      Edit_kodSvd_14->Visible = true;
      break;
    case 15:
      Edit_temperKam_15->Visible = true;
      Edit_kodTemper_15->Visible = true;
      Edit_kodSvd_15->Visible = true;
      break;
    case 16:
      Edit_temperKam_16->Visible = true;
      Edit_kodTemper_16->Visible = true;
      Edit_kodSvd_16->Visible = true;
      break;
    case 17:
      Edit_temperKam_17->Visible = true;
      Edit_kodTemper_17->Visible = true;
      Edit_kodSvd_17->Visible = true;
      break;
    case 18:
      Edit_temperKam_18->Visible = true;
      Edit_kodTemper_18->Visible = true;
      Edit_kodSvd_18->Visible = true;
      break;
    case 19:
      Edit_temperKam_19->Visible = true;
      Edit_kodTemper_19->Visible = true;
      Edit_kodSvd_19->Visible = true;
      break;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_ARCH::Grafik(void)
{
  // 1-������ ������; 2-������ ������; 3-��� �������
  if ( FlagGrafik )
  {
    IshDan(); // ���� �������� ����� � ������
    if ( err )
    {
      return;
    }
    Interpol(); // ������������
    if ( (T_MIN == 0) && (T_MAX == 0) )
    {
      return;
    }
    for ( int i = 0; i < 256; i++ )
    {
      if ( MasSveto[i] < 0 )
      {
        MasSveto[i] = 0;
        if ( MasSveto[i] > 255 )
        {
          MasSveto[i] = 255;
        }
      }
    } // end for ( int i = 0; i < 256; i++ )
  } // end if ( FlagGrafik )
  Series1->Clear();
  Series2->Clear();
  Series3->Clear();
  Series4->Clear();

  Chart_Main->BottomAxis->Minimum = 0;
  Chart_Main->BottomAxis->Maximum = 255;
  Chart_Main->LeftAxis->Minimum = 0;
  Chart_Main->LeftAxis->Maximum = 280;
  if ( RadioButton_Grafik2->Checked )
  {
    for ( int i = 0; i < 256; i++ )
    {
      Series1->AddXY(i, MasSveto[i]," ",clRed);
    }
    for ( int i = 0; i < 256; i++ )
    {
      Series3->AddXY(i, 255," ",clBlue);
    }
    for ( int i = 0; i < 256; i++ )
    {
      Series4->AddXY(i, 0, " ", clBlue);
    }
    for ( int i = 0; i < 250; i = i + 10)
    {
      Series2->AddXY(i, MasSveto[i], " ", clBlack);
    }
  } // end if ( RadioButton_Grafik2->Checked )
  if ( RadioButton_Grafik1->Checked )
  {
    Chart_Main->BottomAxis->Minimum = 0;
    Chart_Main->BottomAxis->Maximum = 100;
    int MaxX, MinX;
    if ( k1 != 0 )
    {
      MaxX = (255.0 - (-1 * A1)) / k1;
    }
    else
    {
      MaxX = 255.0;
    }
    if ( k1 != 0 )
    {
      MinX = (0.0 - (-1 * A1)) / k1;
    }
    else
    {
      MinX = 0.0;
    }
    Chart_Main->BottomAxis->Maximum = MaxX;
    Chart_Main->BottomAxis->Minimum = MinX;
    int MaxY = 0;
    for ( int i = 0; i < 256; i++ )
    {
      if ( MasSveto[i] > MaxY )
      {
        MaxY = MasSveto[i];
      }
    }
    int MinY = MaxY;
    Chart_Main->LeftAxis->Maximum = (1.0 / k2) * (MaxY + A2) + 10;
    for (int i = 0; i < 256; i++ )
    {
      if ( MasSveto[i] < MinY)
      {
        MinY = MasSveto[i];
      }
    }
    Chart_Main->LeftAxis->Minimum = (1.0 / k2) * (MinY + A2) - 10;
    int j = 0;
    float x = 0;
    for ( int i = 0; i < 256; i++ )
    {
      j++;
      if ( k1 != 0 )
      {
        x = ((float)i - (-1 * A1)) / k1;
      }
      else
      {
        x = (float)i;
      }
      Series1->AddXY(x, (1.0 / k2) * (MasSveto[i] + A2), " ", clRed);
      Series3->AddXY(x, (1.0 / k2) * (255 + A2), " ", clBlue);
      Series4->AddXY(x, (1.0 / k2) * (0 + A2), " ", clBlue);
      if ( j == 10 )
      {
        j = 0;
        Series2->AddXY(x, (1.0 / k2) * (MasSveto[i] + A2), " ", clBlack);
      }
    }
  } // end if ( RadioButton_Grafik1->Checked )
}
//---------------------------------------------------------------------------
void __fastcall TForm_ARCH::Matr(int Nmatr) // ������� ������� �������� ��������� ������� ������
{
  float mn, V;
  for ( int k = 0; k < Nmatr - 1; k++ )
  {
    if ( Mas[k][k] == 0 ) // ���� ������������ ������� ����� ����
    {
      // ���� ������ � ��������� � �-��� ������� �� ������ ����
      for ( int i = k + 1; i < Nmatr; i++ )
      {
        if ( Mas[i][k] != 0 )
        { // ������ ������� ������-i (��� �� ������� ������� � �-��� �������)
          // � �-������ � Mas[][] � B[]
          for (int j = 0; j < Nmatr; j++ )
          {
            V = Mas[k][j];
            Mas[k][j] = Mas[i][j];
            Mas[i][j] = V;
          } // for j
          V = B[k];
          B[k] = B[i];
          B[i] = V;
          break;
        } // if ( Mas[i][k] != 0 )
      } // for i
    } // if ( Mas[k][k] == 0 )
    // ����� ��� ������� k-��� ������ Mas[][] � B[] �� ������������ �������
    mn = Mas[k][k];
    for ( int i = 0; i < Nmatr; i++ )
    {
      if ( Mas[k][i] != 0 )
      {
        Mas[k][i] = Mas[k][i] / mn;
      }
    }
    B[k] /= mn;
    // �������� �� ��������� ��������� k-���, ���������� �� ������� �-�������
    for ( int m = k + 1; m < Nmatr; m++ )
    {
      mn = Mas[m][k];
      for ( int j = k; j < Nmatr; j++ ) // j=0
      {
        Mas[m][j] = Mas[m][j] - Mas[k][j] * mn;
      } // for j
      B[m] = B[m] - B[k] * mn;
    } // for m
  } // for k
  // �������� ����������� �������
  Xx[Nmatr-1] = B[Nmatr-1] / Mas[Nmatr-1][Nmatr-1];

  // �������� ���
  // X[3] = B[4];
  // X[2] = B[3] - Mas[2][3] * X[3];
  // X[1] = B[2] - Mas[1][3] * X[3] - Mas[1][2] * X[2];
  // X[0] = B[1] - Mas[0][3] * X[3] - Mas[0][2] * X[2] - Mas[0][1] * X[1];
  for ( int k = Nmatr - 2; k >= 0; k-- )
  {
    Xx[k] = B[k];
    for ( int i = Nmatr - 1; i > k; i--)
    {
      Xx[k] = Xx[k] - Xx[i] * Mas[k][i];
    } // for i
  } // for k
  // int x = Xx[0];
  // x = Xx[3] * 255 * 255 + Xx[4] * 255 + Xx[5];
  // x = Xx[0];
}
//---------------------------------------------------------------------------
void __fastcall TForm_ARCH::FormCreate(TObject *Sender)
{
  TIniFile * IniFile = new TIniFile(IniFileName);
  try
  {
    Form_ARCH->Width = IniFile->ReadInteger( "Form ARCH Settings", "FormARCHWidth", Form_ARCH->Width );
    Form_ARCH->Height = IniFile->ReadInteger( "Form ARCH Settings", "FormARCHHeight", Form_ARCH->Height );
    Form_ARCH->Left =  IniFile->ReadInteger( "Form ARCH Settings", "FormARCHLeft", Form_ARCH->Left );
    Form_ARCH->Top = IniFile->ReadInteger( "Form ARCH Settings", "FormARCHTop", Form_ARCH->Top );
    //
    Form_ARCH->Edit_WriteFileStr->Text =
      IniFile->ReadString( "Form ARCH Settings", "Form_ARCH_Edit_WriteFileStr_Text", Form_ARCH->Edit_WriteFileStr->Text );
    Form_ARCH->Edit_ReadFileStr->Text =
      IniFile->ReadString( "Form ARCH Settings", "Form_ARCH_Edit_ReadFileStr_Text", Form_ARCH->Edit_ReadFileStr->Text );
    delete IniFile;
  }
  catch(...) // ����� ����������
  {
    delete IniFile;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_ARCH::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  TIniFile * IniFile = new TIniFile(IniFileName);
  try
  {
    IniFile->WriteInteger( "Form ARCH Settings", "FormARCHWidth", Form_ARCH->Width );
    IniFile->WriteInteger( "Form ARCH Settings", "FormARCHHeight", Form_ARCH->Height );
    IniFile->WriteInteger( "Form ARCH Settings", "FormARCHLeft", Form_ARCH->Left );
    IniFile->WriteInteger( "Form ARCH Settings", "FormARCHTop", Form_ARCH->Top );
    //
    IniFile->WriteString( "Form ARCH Settings", "Form_ARCH_Edit_WriteFileStr_Text", Form_ARCH->Edit_WriteFileStr->Text );
    IniFile->WriteString( "Form ARCH Settings", "Form_ARCH_Edit_ReadFileStr_Text", Form_ARCH->Edit_ReadFileStr->Text );
    delete IniFile;
  }
  catch(...) // ����� ����������
  {
    delete IniFile;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_ARCH::Button_WriteFileStrClick(TObject *Sender)
{
  // ������� ����������� ����
  AnsiString filename = Edit_WriteFileStr->Text;
  AnsiString put = ExtractFileDir(filename);
  OpenDialog_forWrite->InitialDir = put;
  if ( OpenDialog_forWrite->Execute() )
  {
    filename = OpenDialog_forWrite->FileName;
    Edit_WriteFileStr->Text = filename;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_ARCH::Button_ReadFileStrClick(TObject *Sender)
{
  // ������� ����������� ����
  AnsiString filename = Edit_ReadFileStr->Text;
  AnsiString put = ExtractFileDir(filename);
  OpenDialog_forRead->InitialDir = put;
  if ( OpenDialog_forRead->Execute() )
  {
    filename = OpenDialog_forRead->FileName;
    Edit_ReadFileStr->Text = filename;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_ARCH::Button_ProsmGrafikaClick(TObject *Sender)
{
  FlagGrafikKnopka = true; // false
  FlagFile = false; // false
  FlagEEPROM = false; // false
  FlagGrafik = true; // false
  Grafik();
  FlagGrafikKnopka = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm_ARCH::IshDan(void)
{
  err = 0;
  // ���� �������� �����
  UgolTangens = StrToInt( Edit_tangens->Text );
  // ���� ������ � ������ � �� ��������
  kol_zn = UpDown_KolVoPoints->Position;
  for ( int i = 0; i < kol_zn; i++ )
  {
    MasT[i] = 0;
    MasS[i] = 0;
    Temp[i] = 0;
    Sveto[i] = 0;
  }
  for ( int i = 0; i < kol_zn; i++ )
  {
    switch ( i )
    {
    case 0:
      if ( Edit_kodTemper_01->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 1, ������� 2", MB_ICONSTOP);
        return;
      }
      if ( Edit_kodSvd_01->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 1, ������� 3", MB_ICONSTOP);
        return;        
      }
      for ( int j = 1; j <= Edit_kodTemper_01->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodTemper_01->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 1, ������� 2", MB_ICONSTOP );
          return;
        }
      }
      for ( int j = 1; j <= Edit_kodSvd_01->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodSvd_01->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 1, ������� 3", MB_ICONSTOP );
          return;
        }
      }
      Temp[i] = StrToInt( Edit_kodTemper_01->Text );
      Sveto[i] = StrToInt( Edit_kodSvd_01->Text );
      TempKamera[i] = Edit_temperKam_01->Text;
      break;
      // end case
    case 1:
      if ( Edit_kodTemper_02->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 2, ������� 2", MB_ICONSTOP);
        return;
      }
      if ( Edit_kodSvd_02->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 2, ������� 3", MB_ICONSTOP);
        return;
      }
      for ( int j = 1; j <= Edit_kodTemper_02->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodTemper_02->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 2, ������� 2", MB_ICONSTOP );
          return;
        }
      }
      for ( int j = 1; j <= Edit_kodSvd_02->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodSvd_02->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 2, ������� 3", MB_ICONSTOP );
          return;
        }
      }
      Temp[i] = StrToInt( Edit_kodTemper_02->Text );
      Sveto[i] = StrToInt( Edit_kodSvd_02->Text );
      TempKamera[i] = Edit_temperKam_02->Text;
      break;
      // end case
    case 2:
      if ( Edit_kodTemper_03->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 3, ������� 2", MB_ICONSTOP);
        return;
      }
      if ( Edit_kodSvd_03->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 3, ������� 3", MB_ICONSTOP);
        return;
      }
      for ( int j = 1; j <= Edit_kodTemper_03->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodTemper_03->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 3, ������� 2", MB_ICONSTOP );
          return;
        }
      }
      for ( int j = 1; j <= Edit_kodSvd_03->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodSvd_03->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 3, ������� 3", MB_ICONSTOP );
          return;
        }
      }
      Temp[i] = StrToInt( Edit_kodTemper_03->Text );
      Sveto[i] = StrToInt( Edit_kodSvd_03->Text );
      TempKamera[i] = Edit_temperKam_03->Text;
      break;
      // end case
    case 3:
      if ( Edit_kodTemper_04->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 4, ������� 2", MB_ICONSTOP);
        return;
      }
      if ( Edit_kodSvd_04->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 4, ������� 3", MB_ICONSTOP);
        return;
      }
      for ( int j = 1; j <= Edit_kodTemper_04->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodTemper_04->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 4, ������� 2", MB_ICONSTOP );
          return;
        }
      }
      for ( int j = 1; j <= Edit_kodSvd_04->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodSvd_04->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 4, ������� 3", MB_ICONSTOP );
          return;
        }
      }
      Temp[i] = StrToInt( Edit_kodTemper_04->Text );
      Sveto[i] = StrToInt( Edit_kodSvd_04->Text );
      TempKamera[i] = Edit_temperKam_04->Text;
      break;
      // end case
    case 4:
      if ( Edit_kodTemper_05->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 5, ������� 2", MB_ICONSTOP);
        return;
      }
      if ( Edit_kodSvd_05->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 5, ������� 3", MB_ICONSTOP);
        return;
      }
      for ( int j = 1; j <= Edit_kodTemper_05->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodTemper_05->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 5, ������� 2", MB_ICONSTOP );
          return;
        }
      }
      for ( int j = 1; j <= Edit_kodSvd_05->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodSvd_05->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 5, ������� 3", MB_ICONSTOP );
          return;
        }
      }
      Temp[i] = StrToInt( Edit_kodTemper_05->Text );
      Sveto[i] = StrToInt( Edit_kodSvd_05->Text );
      TempKamera[i] = Edit_temperKam_05->Text;
      break;
      // end case
    case 5:
      if ( Edit_kodTemper_06->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 6, ������� 2", MB_ICONSTOP);
        return;
      }
      if ( Edit_kodSvd_06->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 6, ������� 3", MB_ICONSTOP);
        return;
      }
      for ( int j = 1; j <= Edit_kodTemper_06->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodTemper_06->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 6, ������� 2", MB_ICONSTOP );
          return;
        }
      }
      for ( int j = 1; j <= Edit_kodSvd_06->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodSvd_06->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 6, ������� 3", MB_ICONSTOP );
          return;
        }
      }
      Temp[i] = StrToInt( Edit_kodTemper_06->Text );
      Sveto[i] = StrToInt( Edit_kodSvd_06->Text );
      TempKamera[i] = Edit_temperKam_06->Text;
      break;
      // end case
    case 6:
      if ( Edit_kodTemper_07->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 7, ������� 2", MB_ICONSTOP);
        return;
      }
      if ( Edit_kodSvd_07->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 7, ������� 3", MB_ICONSTOP);
        return;
      }
      for ( int j = 1; j <= Edit_kodTemper_07->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodTemper_07->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 7, ������� 2", MB_ICONSTOP );
          return;
        }
      }
      for ( int j = 1; j <= Edit_kodSvd_07->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodSvd_07->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 7, ������� 3", MB_ICONSTOP );
          return;
        }
      }
      Temp[i] = StrToInt( Edit_kodTemper_07->Text );
      Sveto[i] = StrToInt( Edit_kodSvd_07->Text );
      TempKamera[i] = Edit_temperKam_07->Text;
      break;
      // end case
    case 7:
      if ( Edit_kodTemper_08->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 8, ������� 2", MB_ICONSTOP);
        return;
      }
      if ( Edit_kodSvd_08->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 8, ������� 3", MB_ICONSTOP);
        return;
      }
      for ( int j = 1; j <= Edit_kodTemper_08->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodTemper_08->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 8, ������� 2", MB_ICONSTOP );
          return;
        }
      }
      for ( int j = 1; j <= Edit_kodSvd_08->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodSvd_08->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 8, ������� 3", MB_ICONSTOP );
          return;
        }
      }
      Temp[i] = StrToInt( Edit_kodTemper_08->Text );
      Sveto[i] = StrToInt( Edit_kodSvd_08->Text );
      TempKamera[i] = Edit_temperKam_08->Text;
      break;
      // end case
    case 8:
      if ( Edit_kodTemper_09->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 9, ������� 2", MB_ICONSTOP);
        return;
      }
      if ( Edit_kodSvd_09->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 9, ������� 3", MB_ICONSTOP);
        return;
      }
      for ( int j = 1; j <= Edit_kodTemper_09->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodTemper_09->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 9, ������� 2", MB_ICONSTOP );
          return;
        }
      }
      for ( int j = 1; j <= Edit_kodSvd_09->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodSvd_09->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 9, ������� 3", MB_ICONSTOP );
          return;
        }
      }
      Temp[i] = StrToInt( Edit_kodTemper_09->Text );
      Sveto[i] = StrToInt( Edit_kodSvd_09->Text );
      TempKamera[i] = Edit_temperKam_09->Text;
      break;
      // end case
    case 9:
      if ( Edit_kodTemper_10->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 10, ������� 2", MB_ICONSTOP);
        return;
      }
      if ( Edit_kodSvd_10->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 10, ������� 3", MB_ICONSTOP);
        return;
      }
      for ( int j = 1; j <= Edit_kodTemper_10->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodTemper_10->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 10, ������� 2", MB_ICONSTOP );
          return;
        }
      }
      for ( int j = 1; j <= Edit_kodSvd_10->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodSvd_10->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 10, ������� 3", MB_ICONSTOP );
          return;
        }
      }
      Temp[i] = StrToInt( Edit_kodTemper_10->Text );
      Sveto[i] = StrToInt( Edit_kodSvd_10->Text );
      TempKamera[i] = Edit_temperKam_10->Text;
      break;
      // end case
    case 10:
      if ( Edit_kodTemper_11->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 11, ������� 2", MB_ICONSTOP);
        return;
      }
      if ( Edit_kodSvd_11->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 11, ������� 3", MB_ICONSTOP);
        return;
      }
      for ( int j = 1; j <= Edit_kodTemper_11->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodTemper_11->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 11, ������� 2", MB_ICONSTOP );
          return;
        }
      }
      for ( int j = 1; j <= Edit_kodSvd_11->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodSvd_11->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 11, ������� 3", MB_ICONSTOP );
          return;
        }
      }
      Temp[i] = StrToInt( Edit_kodTemper_11->Text );
      Sveto[i] = StrToInt( Edit_kodSvd_11->Text );
      TempKamera[i] = Edit_temperKam_11->Text;
      break;
      // end case
    case 11:
      if ( Edit_kodTemper_12->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 12, ������� 2", MB_ICONSTOP);
        return;
      }
      if ( Edit_kodSvd_12->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 12, ������� 3", MB_ICONSTOP);
        return;
      }
      for ( int j = 1; j <= Edit_kodTemper_12->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodTemper_12->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 12, ������� 2", MB_ICONSTOP );
          return;
        }
      }
      for ( int j = 1; j <= Edit_kodSvd_12->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodSvd_12->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 12, ������� 3", MB_ICONSTOP );
          return;
        }
      }
      Temp[i] = StrToInt( Edit_kodTemper_12->Text );
      Sveto[i] = StrToInt( Edit_kodSvd_12->Text );
      TempKamera[i] = Edit_temperKam_12->Text;
      break;
      // end case
    case 12:
      if ( Edit_kodTemper_13->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 13, ������� 2", MB_ICONSTOP);
        return;
      }
      if ( Edit_kodSvd_13->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 13, ������� 3", MB_ICONSTOP);
        return;
      }
      for ( int j = 1; j <= Edit_kodTemper_13->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodTemper_13->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 13, ������� 2", MB_ICONSTOP );
          return;
        }
      }
      for ( int j = 1; j <= Edit_kodSvd_13->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodSvd_13->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 13, ������� 3", MB_ICONSTOP );
          return;
        }
      }
      Temp[i] = StrToInt( Edit_kodTemper_13->Text );
      Sveto[i] = StrToInt( Edit_kodSvd_13->Text );
      TempKamera[i] = Edit_temperKam_13->Text;
      break;
      // end case
    case 13:
      if ( Edit_kodTemper_14->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 14, ������� 2", MB_ICONSTOP);
        return;
      }
      if ( Edit_kodSvd_14->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 14, ������� 3", MB_ICONSTOP);
        return;
      }
      for ( int j = 1; j <= Edit_kodTemper_14->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodTemper_14->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 14, ������� 2", MB_ICONSTOP );
          return;
        }
      }
      for ( int j = 1; j <= Edit_kodSvd_14->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodSvd_14->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 14, ������� 3", MB_ICONSTOP );
          return;
        }
      }
      Temp[i] = StrToInt( Edit_kodTemper_14->Text );
      Sveto[i] = StrToInt( Edit_kodSvd_14->Text );
      TempKamera[i] = Edit_temperKam_14->Text;
      break;
      // end case
    case 14:
      if ( Edit_kodTemper_15->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 15, ������� 2", MB_ICONSTOP);
        return;
      }
      if ( Edit_kodSvd_15->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 15, ������� 3", MB_ICONSTOP);
        return;
      }
      for ( int j = 1; j <= Edit_kodTemper_15->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodTemper_15->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 15, ������� 2", MB_ICONSTOP );
          return;
        }
      }
      for ( int j = 1; j <= Edit_kodSvd_15->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodSvd_15->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 15, ������� 3", MB_ICONSTOP );
          return;
        }
      }
      Temp[i] = StrToInt( Edit_kodTemper_15->Text );
      Sveto[i] = StrToInt( Edit_kodSvd_15->Text );
      TempKamera[i] = Edit_temperKam_15->Text;
      break;
      // end case
    case 15:
      if ( Edit_kodTemper_16->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 16, ������� 2", MB_ICONSTOP);
        return;
      }
      if ( Edit_kodSvd_16->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 16, ������� 3", MB_ICONSTOP);
        return;
      }
      for ( int j = 1; j <= Edit_kodTemper_16->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodTemper_16->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 16, ������� 2", MB_ICONSTOP );
          return;
        }
      }
      for ( int j = 1; j <= Edit_kodSvd_16->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodSvd_16->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 16, ������� 3", MB_ICONSTOP );
          return;
        }
      }
      Temp[i] = StrToInt( Edit_kodTemper_16->Text );
      Sveto[i] = StrToInt( Edit_kodSvd_16->Text );
      TempKamera[i] = Edit_temperKam_16->Text;
      break;
      // end case
    case 16:
      if ( Edit_kodTemper_17->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 17, ������� 2", MB_ICONSTOP);
        return;
      }
      if ( Edit_kodSvd_17->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 17, ������� 3", MB_ICONSTOP);
        return;
      }
      for ( int j = 1; j <= Edit_kodTemper_17->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodTemper_17->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 17, ������� 2", MB_ICONSTOP );
          return;
        }
      }
      for ( int j = 1; j <= Edit_kodSvd_17->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodSvd_17->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 17, ������� 3", MB_ICONSTOP );
          return;
        }
      }
      Temp[i] = StrToInt( Edit_kodTemper_17->Text );
      Sveto[i] = StrToInt( Edit_kodSvd_17->Text );
      TempKamera[i] = Edit_temperKam_17->Text;
      break;
      // end case
    case 17:
      if ( Edit_kodTemper_18->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 18, ������� 2", MB_ICONSTOP);
        return;
      }
      if ( Edit_kodSvd_18->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 18, ������� 3", MB_ICONSTOP);
        return;
      }
      for ( int j = 1; j <= Edit_kodTemper_18->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodTemper_18->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 18, ������� 2", MB_ICONSTOP );
          return;
        }
      }
      for ( int j = 1; j <= Edit_kodSvd_18->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodSvd_18->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 18, ������� 3", MB_ICONSTOP );
          return;
        }
      }
      Temp[i] = StrToInt( Edit_kodTemper_18->Text );
      Sveto[i] = StrToInt( Edit_kodSvd_18->Text );
      TempKamera[i] = Edit_temperKam_18->Text;
      break;
      // end case
    case 18:
      if ( Edit_kodTemper_19->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 19, ������� 2", MB_ICONSTOP);
        return;
      }
      if ( Edit_kodSvd_19->Text == "" )
      {
        err = 1;
        Application->MessageBoxA("�� �� ����� ������", "������ 19, ������� 3", MB_ICONSTOP);
        return;
      }
      for ( int j = 1; j <= Edit_kodTemper_19->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodTemper_19->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 19, ������� 2", MB_ICONSTOP );
          return;
        }
      }
      for ( int j = 1; j <= Edit_kodSvd_19->Text.Length(); j++ )
      {
        if ( !Dig.Contains( Edit_kodSvd_19->Text[j] ) )
        {
          err = 1;
          Application->MessageBoxA("�� ����� �� �������� �������", "������ 19, ������� 3", MB_ICONSTOP );
          return;
        }
      }
      Temp[i] = StrToInt( Edit_kodTemper_19->Text );
      Sveto[i] = StrToInt( Edit_kodSvd_19->Text );
      TempKamera[i] = Edit_temperKam_19->Text;
      break;
      // end case
    } // end switch ( i )
  } // end for ( int i = 0; i < kol_zn; i++ )
  del = Temp[1] - Temp[0]; // del < 0 - �������� ����������� �������
  for ( int i = 2; i < kol_zn; i++ )
  {
    if ( (del < 0) && (Temp[i-1] < Temp[i]) )
    {
      err = 1;
      Application->MessageBox("������ ����� ������ �� �����������!",
          "�������� ������ �������", MB_ICONSTOP);
      return;
    }
    if ( (del > 0) && (Temp[i-1] > Temp[i]) )
    {
      err = 1;
      Application->MessageBox("������ ����� ������ �� �����������!",
          "�������� ������ ����������", MB_ICONSTOP);
      return;
    }
  }
}
//---------------------------------------------------------------------------
void _fastcall TForm_ARCH::Interpol(void)
{
  // ������� ������������
  T_MIN = T_MAX = SVETO_MIN = SVETO_MAX = 0;
  for ( int i = 0; i < kol_zn; i++ )
  {
    if ( Temp[i] > T_MAX )
    {
      T_MAX = Temp[i];
    }
    if ( Sveto[i] > SVETO_MAX )
    {
      SVETO_MAX = Sveto[i];
    }
  }
  T_MIN = T_MAX;
  SVETO_MIN = SVETO_MAX;
  for ( int i = 0; i < kol_zn; i++ )
  {
    if ( Temp[i] < T_MIN )
    {
      T_MIN = Temp[i];
    }
    if ( Sveto[i] < SVETO_MIN )
    {
      SVETO_MIN = Sveto[i];
    }
  }
  if ( (T_MIN == 0) && (T_MAX == 0) )
  {
    Application->MessageBox("��������� �� �������� ������\n ���-�� ����� ��� ������� N < 2",
        "��������",MB_ICONSTOP);
    return;
  }
  if( SVETO_MIN != SVETO_MAX )
  {
    A1 = 255.0 * T_MIN / ((float)(T_MAX - T_MIN));
    k1 = 255.0 / ((float)(T_MAX - T_MIN));
    A2 = (float)YMAX * SVETO_MIN / ((float)(SVETO_MAX - SVETO_MIN));
    k2 = (float)YMAX / ((float)(SVETO_MAX - SVETO_MIN));
  }
  else
  {
    A1 = -1.0;
    k1 = 0;
    A2 = 0;
    k2 = 128.0 / (float)SVETO_MIN;
    for ( int i = 0; i < 256; i++ )
    {
      MasSveto[i] = 128; //������ �����
    }
    return;
  }
  // ������������
  // ���������� ������������� �������� 0-255 � MasT[] � MasS[]
  for ( int i = 0; i < kol_zn; i++ )
  {
    MasT[i] = Temp[i] * k1 - A1;
    if ( Temp[i] == T_MAX )
    {
      MasT[i] = 255;
    }
    if ( Temp[i] == T_MIN )
    {
      MasT[i] = 0;
    }
    MasS[i] = Sveto[i] * k2 - A2;
    if ( Sveto[i] == SVETO_MAX )
    {
      MasS[i] = YMAX;
    }
    if ( Sveto[i] == SVETO_MIN )
    {
      MasS[i] = 0;
    }
  }
  for ( int i = 0; i < 256; i++ )
  {
    MasSveto[i] = 0;
  }
  for ( int i = 0; i < 72; i++ )
  {
    Xx[i] = 0;
    B[i] = 0;
    for ( int j = 0; j < 72; j++ )
    {
      Mas[i][j] = 0;
    }
  }
  // �������������
  // 1) ��������
  if ( RadioButton_Interpol_01->Checked )
  {
    float L[19], M[19]; // �������������� ������� (MasT ���� ��� �� � ����)
    if ( del > 0 )
    {
      for ( int i = 0; i < kol_zn; i++ )
      {
        L[i] = MasT[kol_zn-i-1];
        M[i] = MasS[kol_zn-i-1];
      }
      for ( int i = 0; i < kol_zn; i++ )
      {
        MasT[i] = L[i];
        MasS[i] = M[i];
      }
    }
    unsigned char x1, x2, y1, y2, interval;
    for ( int i = kol_zn - 1; i > 0; i-- )
    {
      x1 = MasT[i];
      x2 = MasT[i-1];
      y1 = MasS[i];
      y2 = MasS[i-1];
      interval = x2 - x1;
      for ( int j = 0; j < interval; j++ )
      {
        if ( (x2 != x1) && (y2 > y1) )
        {
          MasSveto[x1+j] = y1 + (y2 - y1) * j / (x2 - x1);
        }
        if ( (x2 != x1) && (y1 > y2) )
        {
          MasSveto[x1+j] = y2 + (y1 - y2) * (x2 - x1 - j) / (x2 - x1);
        }
        if ( y1 == y2 )
        {
          MasSveto[x1+j] = y1;
        }
      } // for(j)
    } // for(i)
    MasSveto[0] = MasS[kol_zn-1];
    MasSveto[255] = MasS[0];
  } // end if ( RadioButton_Interpol_01->Checked )
  // 2) �� ������� ��������
  if ( RadioButton_Interpol_02->Checked )
  {
    float PRx;
    for ( int k = 0; k < 256; k++ )
    {
      MasSveto[k] = 0;
      for ( int i = 0; i < kol_zn; i++ )
      {
        PRx = 1;
        for ( int j = 0; j < kol_zn; j++ )
        if ( i != j )
        {
          PRx *= ((float)(k - MasT[j])) / ((float)(MasT[i] - MasT[j]));
        }
        MasSveto[k] += (int)((float)MasS[i] * PRx);
      }
    }
  } // end if ( RadioButton_Interpol_02->Checked )
  // 3) ������ 2-�� �������
  if ( RadioButton_Interpol_03->Checked )
  {
    float L[19], M[19]; // �������������� ������� (MasT ���� ��� � ����)
    if ( del < 0 )
    {
      for ( int i = 0; i < kol_zn; i++ )
      {
        L[i] = MasT[kol_zn-i-1];
        M[i] = MasS[kol_zn-i-1];
      }
      for ( int i = 0; i < kol_zn; i++ )
      {
        MasT[i] = L[i];
        MasS[i] = M[i];
      }
    }
    Nmatr = (kol_zn - 1) * (2 + 1); // 2 - ��� 2 �������
    // ��������� �������
    // �) B[Nmatr] - ��������� ����� {y0,y1,y1,y2,y2,...,y(n-1),y(n-1),y(n)} n - ��������� �����
    B[0] = MasS[0];
    B[2*(kol_zn-1)-1] = MasS[kol_zn-1];
    int j = 1;
    for ( int i = 1; i < 2*(kol_zn-1)-1; i = i + 2 )
    {
      B[i] = MasS[j];
      B[i+1] = MasS[j++];
    }
    // �) Mas[Nmatr][Nmatr]
    // ������� �����
    int N = (kol_zn - 1) * 2;
    j = 0;
    int k = 0;
    for ( int i = 0; i < N; i = i + 2 )
    {
      Mas[i][0+k] = pow(MasT[j], 2);
      Mas[i][1+k] = MasT[j];
      Mas[i][2+k] = 1;
      Mas[i+1][0+k] = pow(MasT[j+1], 2);
      Mas[i+1][1+k] = MasT[j+1];
      Mas[i+1][2+k] = 1;
      j++;
      k = k + 3;
    }
    // ������������� ����������� � ������
    j = 1;
    k = 0;
    for ( int i = N; i < Nmatr - 1; i++ )
    {
      Mas[i][0+k] = MasT[j] * 2;
      Mas[i][1+k] = 1;
      Mas[i][3+k] = -2 * MasT[j];
      Mas[i][4+k] = -1;
      j++;
      k = k + 3;
    }
    // ��������� ������� (����������� �� ������ ����� ����)
    Mas[Nmatr-1][0] = 2 * MasT[0];
    Mas[Nmatr-1][1] = 1;
    B[Nmatr-1] = UgolTangens; //3; //������� ���� ������� �����������  !!!!! ����� ������ ��� �������� �����!!!!!!!!!!!!!!!!!!!
    // Mas[Nmatr-1][Nmatr-3] = -2*MasT[kol_zn-1];
    // Mas[Nmatr-1][Nmatr-2] = -1;
    // Mas[Nmatr-1][Nmatr-1] = 0;
    // ������ ������� �� Nmatr �������� ���������
    Matr(Nmatr); // ����� ������ � ������� �������� ��������
    if( (int)Xx[2] != MasS[0] )
    {
      Application->MessageBox("������ �������!", "������-2", MB_ICONSTOP);
      return;
    }
    // ��������� ���������� ������������
    // Koef[18][5];
    j = 0;
    for ( int i = 0; i < kol_zn; i++ )
    {
      for ( int k = 0; k < 3; k++ ) // 3-��� 2�������
      {
        Koef[i][k] = Xx[j++];
      } // i-����� ������� �-����� ������������(0-��� x~2,1-��� x ,2-��������� ����)
    }
    // ��������� ������
    int i = 0;
    for ( int xx = 0; xx < 256; xx++ )
    {
      if ( xx > MasT[i+1] )
      {
        i++;
      }
      MasSveto[xx] = Koef[i][0] * pow(xx, 2) + Koef[i][1] * xx + Koef[i][2];
    }
    int x = x;
  } // end if ( RadioButton_Interpol_03->Checked )
  // 4) ������ 3-�� �������
  if ( RadioButton_Interpol_04->Checked )
  {
    float L[19], M[19]; // �������������� ������� (MasT ���� ��� � ����)
    if ( del < 0 )
    {
      for ( int i = 0; i <kol_zn; i++ )
      {
        L[i] = MasT[kol_zn-i-1];
        M[i] = MasS[kol_zn-i-1];
      }
      for ( int i = 0; i < kol_zn; i++ )
      {
        MasT[i] = L[i];
        MasS[i] = M[i];
      }
    }
    Nmatr = (kol_zn - 1) * (3 + 1); // 3-��� 3 �������
    // ��������� �������
    // �) B[Nmatr] - ��������� ����� {y0,y1,y1,y2,y2,...,y(n-1),y(n-1),y(n)} n - ��������� �����
    B[0] = MasS[0];
    B[2*(kol_zn-1)-1] = MasS[kol_zn-1];
    int j = 1;
    for ( int i = 1; i < 2 * (kol_zn - 1) - 1; i = i + 2 )
    {
      B[i] = MasS[j];
      B[i+1] = MasS[j++];
    }
    // �) Mas[Nmatr][Nmatr]
    // ������� �����
    int N = (kol_zn - 1) * 2;
    j = 0;
    int k = 0;
    for ( int i = 0; i < N; i = i + 2 )
    {
      Mas[i][0+k] = pow(MasT[j], 3);
      Mas[i][1+k] = pow(MasT[j], 2);
      Mas[i][2+k] = MasT[j];
      Mas[i][3+k] = 1;

      Mas[i+1][0+k] = pow(MasT[j+1], 3);
      Mas[i+1][1+k] = pow(MasT[j+1], 2);
      Mas[i+1][2+k] = MasT[j+1];
      Mas[i+1][3+k] = 1;
      j++;
      k = k + 4;
    }
    // ������������� ������ ����������� � ������
    j = 1;
    k = 0;
    int N1 = kol_zn - 2;
    for ( int i = N; i < N + N1; i++ )
    {
      Mas[i][0+k] = 3 * pow(MasT[j], 2);
      Mas[i][1+k] = 2 * MasT[j];
      Mas[i][2+k] = 1;
      Mas[i][4+k] = -3 * pow(MasT[j], 2);
      Mas[i][5+k] = -2 * MasT[j];
      Mas[i][6+k] = -1;
      j++;
      k = k + 4;
    }
    // ������������� ������ ����������� � ������
    j = 1; k = 0;
    for ( int i = N + N1; i < Nmatr - 2; i++ )
    {
      Mas[i][0+k] = 6 * MasT[j];
      Mas[i][1+k] = 2;
      Mas[i][4+k] = -6 * MasT[j];
      Mas[i][5+k] = -2;
      j++;
      k = k + 4;
    }
    // ��������� ������� (����������� �� ������ ����� ����
    Mas[Nmatr-2][0] = 3 * pow(MasT[0],2);
    Mas[Nmatr-2][1] = 2 * MasT[0];
    Mas[Nmatr-2][2] = 1;
    // Mas[Nmatr-2][Nmatr-4] = -3 * pow(MasT[kol_zn-1], 2);
    // Mas[Nmatr-2][Nmatr-3] = -2 * MasT[kol_zn-1];
    // Mas[Nmatr-2][Nmatr-2] = -1;
    Mas[Nmatr-1][0] = 6 * MasT[0];
    Mas[Nmatr-1][1] = 2;
    Mas[Nmatr-1][Nmatr-4] = -6 * MasT[kol_zn-1];
    Mas[Nmatr-1][Nmatr-3] = -2;

    B[Nmatr-2] = UgolTangens; // ������� ���� ������� �����������  !!!!! ����� ������ ��� �������� �����!!!!!!!!!!!!!!!!!!!
    B[Nmatr-1] = 0;

    // ������ ������� �� Nmatr �������� ���������
    Matr ( Nmatr ); // ����� ������ � ������� �������� ��������
    if ( (int)Xx[3] != MasS[0])
    {
      Application->MessageBox("������ �������!", "������-3", MB_ICONSTOP);
      return;
    }
    j = 0;
    for ( int i = 0; i < kol_zn; i++ )
    {
      for ( int k = 0; k < 4; k++ ) // 4-��� 3�������
      {
        Koef[i][k] = Xx[j++];
      } // i-����� ������� �-����� ������������(0-��� x~3, 1-��� x~2, 2-��� x, 2-��������� ����)
    }
    // ���������� ������� ������������
    int i = 0;
    for ( int xx = 0; xx < 256; xx++ )
    {
      if ( xx > MasT[i+1] )
      {
        i++;
      }
      MasSveto[xx] = Koef[i][0] * pow(xx, 3) + Koef[i][1] * pow(xx, 2) +
          Koef[i][2] * xx + Koef[i][3];
    }
    int x = x;
  } // end if ( RadioButton_Interpol_04->Checked )
  // 5) ������ 4-�� �������
  if ( RadioButton_Interpol_05->Checked )
  {
    float L[19], M[19]; // �������������� �������(MasT ���� ��� � ����)
    if ( del < 0 )
    {
      for ( int i = 0; i < kol_zn; i++ )
      {
        L[i] = MasT[kol_zn-i-1];
        M[i] = MasS[kol_zn-i-1];
      }
      for ( int i = 0; i < kol_zn; i++ )
      {
        MasT[i] = L[i];
        MasS[i] = M[i];
      }
    }
    Nmatr = (kol_zn - 1) * (4 + 1); // 4-��� 4 �������
    // ��������� �������
    // �) B[Nmatr] - ��������� ����� {y0,y1,y1,y2,y2,...,y(n-1),y(n-1),y(n)} n - ��������� �����
    B[0] = MasS[0];
    B[2*(kol_zn-1)-1] = MasS[kol_zn-1];
    int j = 1;
    for ( int i = 1; i < 2 * (kol_zn - 1) - 1; i = i + 2 )
    {
      B[i] = MasS[j];
      B[i+1] = MasS[j++];
    }
    // �) Mas[Nmatr][Nmatr]
    // ������� �����
    int N =(kol_zn - 1) * 2;
    j = 0;
    int k = 0;
    for ( int i = 0; i < N; i = i + 2 )
    {
      Mas[i][0+k] = pow(MasT[j], 4);
      Mas[i][1+k] = pow(MasT[j], 3);
      Mas[i][2+k] = pow(MasT[j], 2);
      Mas[i][3+k] = MasT[j];
      Mas[i][4+k] = 1;

      Mas[i+1][0+k] = pow(MasT[j+1], 4);
      Mas[i+1][1+k] = pow(MasT[j+1], 3);
      Mas[i+1][2+k] = pow(MasT[j+1], 2);
      Mas[i+1][3+k] = MasT[j+1];
      Mas[i+1][4+k] = 1;
      j++;
      k = k + 5;
    }
    // ������������� ������ ����������� � ������
    j = 1;
    k = 0;
    int N1 = kol_zn - 2;
    for ( int i = N; i < N + N1 ; i++ )
    {
      Mas[i][0+k] = 4 * pow(MasT[j], 3);
      Mas[i][1+k] = 3 * pow(MasT[j], 2);
      Mas[i][2+k] = 2 * MasT[j];
      Mas[i][3+k] = 1;

      Mas[i][5+k] = -4 * pow(MasT[j], 3);
      Mas[i][6+k] = -3 * pow(MasT[j], 2);
      Mas[i][7+k] = -2 * MasT[j];
      Mas[i][8+k] = -1;
      j++;
      k = k + 5;
    }
    // ������������� ������ ����������� � ������
    j = 1;
    k = 0;
    int N2 = N + N1 + N1;
    for ( int i = N + N1; i < N2; i++ )
    {
      Mas[i][0+k] = 12 * pow(MasT[j],2);
      Mas[i][1+k] = 6 * MasT[j];
      Mas[i][2+k] = 2;

      Mas[i][5+k] = -12 * pow(MasT[j], 2);
      Mas[i][6+k] = -6 * MasT[j];
      Mas[i][7+k] = -2;
      j++;
      k = k + 5;
    }
    // ������������� ������� ����������� � ������
    j = 1; k = 0;
    for ( int i = N2; i < Nmatr - 3; i++ )
    {
      Mas[i][0+k] = 24 * MasT[j];
      Mas[i][1+k] = 6;
      Mas[i][5+k] = -24 * MasT[j];
      Mas[i][6+k] = -6;
      j++;
      k = k + 5;
    }
    // ��������� ������� (����������� �� ������ ����� ����)
    Mas[Nmatr-3][0] = 4 * pow(MasT[0], 3);
    Mas[Nmatr-3][1] = 3 * pow(MasT[0], 2);
    Mas[Nmatr-3][2] = 2 * MasT[0];
    Mas[Nmatr-3][3] = 1;
    // Mas[Nmatr-3][Nmatr-5] = -4 * pow(MasT[kol_zn-1], 3);
    // Mas[Nmatr-3][Nmatr-4] = -3 * pow(MasT[kol_zn-1], 2);
    // Mas[Nmatr-3][Nmatr-3] = -2 * MasT[kol_zn-1];
    // Mas[Nmatr-3][Nmatr-2] = -1;

    Mas[Nmatr-2][0] = 12 * pow(MasT[0], 2);
    Mas[Nmatr-2][1] = 6 * MasT[0];
    Mas[Nmatr-2][2] = 2;
    Mas[Nmatr-2][Nmatr-5] = -12 * MasT[kol_zn-1];
    Mas[Nmatr-2][Nmatr-4] = -6 * MasT[kol_zn-1];
    Mas[Nmatr-2][Nmatr-3] = -2;

    Mas[Nmatr-1][0] = 24 * MasT[0];
    Mas[Nmatr-1][1] = 6;
    Mas[Nmatr-1][Nmatr-5] = -24 * MasT[kol_zn-1];
    Mas[Nmatr-1][Nmatr-4] = -6;

    B[Nmatr-3] = UgolTangens; // 5; //������� ���� ������� �����������  !!!!! ����� ������ ��� �������� �����!!!!!!!!!!!!!!!!!!!
    B[Nmatr-2] = 0; //
    B[Nmatr-1] = 0;//

    // ������ ������� �� Nmatr �������� ���������
    Matr(Nmatr); // ����� ������ � ������� �������� ��������
    if ( (int)Xx[4] != MasS[0] )
    {
      Application->MessageBox("������ �������!", "������-4", MB_ICONSTOP);
      return;
    }
    // Koef[18][5];
    j = 0;
    for ( int i = 0; i < kol_zn; i++ )
    {
      for ( int k = 0; k < 5; k++ ) // 5-��� 4 �������
      {
        Koef[i][k] = Xx[j++];
      } // i-����� ������� �-����� ������������(0-��� x~3,1-��� x~2 ,2-��� x,2-��������� ����)
    }
    // ���������� ������� ������������
    int i = 0;
    for ( int xx = 0; xx < 256; xx++ )
    {
      if ( xx > MasT[i+1] )
      {
        i++;
      }
      MasSveto[xx] = Koef[i][0] * pow(xx, 4) + Koef[i][1] * pow(xx, 3)
          + Koef[i][2] * pow(xx, 2) + Koef[i][3] * xx + Koef[i][4];
    }
    int x = x;
  } // end if ( RadioButton_Interpol_05->Checked )
  // 6) �������� ������������� - ���������
  if ( RadioButton_Approks_01->Checked )
  {
    float TX = 0, TY = 0, XX = 0, XY = 0, MX = 0,
          MY = 0, CV = 0, VX = 0, BY = 0, AY = 0;
    for ( int i = 0; i < kol_zn; i++ )
    {
      TX = TX + MasT[i];
      TY = TY + MasS[i];
      XX = XX + MasT[i] * MasT[i];
      XY = XY + MasT[i] * MasS[i];
    }
    MX = TX / (float)kol_zn;
    MY = TY / (float)kol_zn;
    CV = (XY - MX * TY) / (float)(kol_zn - 1);
    VX = (XX - MX * TX) / (float)(kol_zn - 1);
    BY = CV / VX;
    AY = MY - BY * MX;
    // y = AY + BY * x  - ������������� ������
    for ( int i = 0; i < 256; i++ )
    {
      MasSveto[i] = AY + BY * i;
    }
  } // end if ( RadioButton_Approks_01->Checked )
  int DP;
  float EI;
  t_IN_mas X, Y;
  t_OUT_mas MK;
  for ( int i = 0; i < 100; i++ )
  {
    X[i] = Y[i] = MK[i] = 0;
  }
  for ( int i = 0; i < kol_zn; i++ )
  {
    X[i] = MasT[i];
    Y[i] = MasS[i];
  }
  // 7) ������� 2-�� �������
  if ( RadioButton_Approks_02->Checked )
  {
    AprocSP(X, Y, kol_zn, 2, MK, DP, EI);
    for ( int i = 0; i <256; i++ )
    {
      MasSveto[i] = MK[3] * pow(i, 2) + MK[2] * i + MK[1];
    }
  } // end if ( RadioButton_Approks_02->Checked )
  // 8) ������� 3-�� �������
  if ( RadioButton_Approks_03->Checked )
  {
    AprocSP(X, Y, kol_zn, 3, MK, DP, EI);
    for (int i = 0; i < 256; i++ )
    {
      MasSveto[i] = MK[4] * pow(i, 3) + MK[3] * pow(i, 2) + MK[2] * i + MK[1];
    }
  } // end if ( RadioButton_Approks_03->Checked )
  // 9) ������� 4-�� �������
  if ( RadioButton_Approks_04->Checked )
  {
    AprocSP(X, Y, kol_zn, 4, MK, DP, EI);
    for ( int i = 0; i < 256; i++ )
    {
      MasSveto[i] = MK[5] * pow(i, 4) + MK[4] * pow(i, 3) + MK[3] * pow(i, 2)
          + MK[2] * i + MK[1];
    }
  } // end if ( RadioButton_Approks_04->Checked )
}
//---------------------------------------------------------------------------
void __fastcall TForm_ARCH::RadioButton_Grafik2Click(TObject *Sender)
{
  FlagGrafikKnopka = true;
  Grafik();
  FlagGrafikKnopka = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm_ARCH::RadioButton_Grafik1Click(TObject *Sender)
{
  FlagGrafikKnopka = true;
  FlagFile = false;
  FlagEEPROM = false;
  FlagGrafik = true;
  Grafik();
  FlagGrafikKnopka = false;       
}
//---------------------------------------------------------------------------

void __fastcall TForm_ARCH::RadioButton_Interpol_01Click(TObject *Sender)
{
  FlagGrafikKnopka = true;
  FlagFile = false;
  FlagEEPROM = false;
  FlagGrafik = true;
  Grafik();
  FlagGrafikKnopka = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm_ARCH::RadioButton_Interpol_02Click(TObject *Sender)
{
  FlagGrafikKnopka = true;
  FlagFile = false;
  FlagEEPROM = false;
  FlagGrafik = true;
  Grafik();
  FlagGrafikKnopka = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm_ARCH::RadioButton_Interpol_03Click(TObject *Sender)
{
  FlagGrafikKnopka = true;
  FlagFile = false;
  FlagEEPROM = false;
  FlagGrafik = true;
  Grafik();
  FlagGrafikKnopka = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm_ARCH::RadioButton_Interpol_04Click(TObject *Sender)
{
  FlagGrafikKnopka = true;
  FlagFile = false;
  FlagEEPROM = false;
  FlagGrafik = true;
  Grafik();
  FlagGrafikKnopka = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm_ARCH::RadioButton_Interpol_05Click(TObject *Sender)
{
  FlagGrafikKnopka = true;
  FlagFile = false;
  FlagEEPROM = false;
  FlagGrafik = true;
  Grafik();
  FlagGrafikKnopka = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm_ARCH::RadioButton_Approks_01Click(TObject *Sender)
{
  FlagGrafikKnopka = true;
  FlagFile = false;
  FlagEEPROM = false;
  FlagGrafik = true;
  Grafik();
  FlagGrafikKnopka = false;        
}
//---------------------------------------------------------------------------

void __fastcall TForm_ARCH::RadioButton_Approks_02Click(TObject *Sender)
{
  FlagGrafikKnopka = true;
  FlagFile = false;
  FlagEEPROM = false;
  FlagGrafik = true;
  Grafik();
  FlagGrafikKnopka = false;        
}
//---------------------------------------------------------------------------

void __fastcall TForm_ARCH::RadioButton_Approks_03Click(TObject *Sender)
{
  FlagGrafikKnopka = true;
  FlagFile = false;
  FlagEEPROM = false;
  FlagGrafik = true;
  Grafik();
  FlagGrafikKnopka = false;        
}
//---------------------------------------------------------------------------

void __fastcall TForm_ARCH::RadioButton_Approks_04Click(TObject *Sender)
{
  FlagGrafikKnopka = true;
  FlagFile = false;
  FlagEEPROM = false;
  FlagGrafik = true;
  Grafik();
  FlagGrafikKnopka = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm_ARCH::UpDown_tangensClick(TObject *Sender,
      TUDBtnType Button)
{
  if ( RadioButton_Interpol_03->Checked ||
      RadioButton_Interpol_04->Checked ||
      RadioButton_Interpol_05->Checked )
  {
    FlagGrafikKnopka = true;
    FlagFile = false;
    FlagEEPROM = false;
    FlagGrafik = true;
    Grafik();
    FlagGrafikKnopka = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_ARCH::Button_ReadFromFileClick(TObject *Sender)
{
  FlagFile = false;
  FlagEEPROM = false;
  FlagGrafik = false;

  UpDown_KolVoPoints->Position = 0;
  VisEdit();
  filename = Edit_ReadFileStr->Text;

  IndAdrZ = fD.ReadUnsignedLong(filename, "�������������� �����", 0); // +
  Form_RearFromEEPROM->Edit_attr_01->Text = IntToStr(IndAdrZ);
  GrpAdrZ = fD.ReadUnsignedLong(filename, "��������� �����", 0); // +
  Form_RearFromEEPROM->Edit_attr_02->Text = IntToStr(GrpAdrZ);
  DNUZ = fD.ReadUnsignedLong(filename, "���", 0); // +
  Form_RearFromEEPROM->Edit_attr_03->Text = IntToStr(DNUZ);
  DVUZ = fD.ReadUnsignedLong(filename, "���", 0);  // +
  Form_RearFromEEPROM->Edit_attr_04->Text = IntToStr(DVUZ);
  LEDAmpZ = fD.ReadUnsignedLong(filename, "��������� �������� �� ����������", 0); // +
  Form_RearFromEEPROM->Edit_attr_05->Text = IntToStr(LEDAmpZ);
  UhiZ = fD.ReadUnsignedLong(filename, "������������ ��� �����.", 0); // +
  Form_RearFromEEPROM->Edit_attr_06->Text = IntToStr(UhiZ);
  SIMstart = fD.ReadUnsignedLong(filename, "������ ��� ���.", 0); // +
  Form_RearFromEEPROM->Edit_attr_07->Text = IntToStr(SIMstart);
  SIMmax = fD.ReadUnsignedLong(filename, "������ ��� max.",0); // +
  Form_RearFromEEPROM->Edit_attr_08->Text = IntToStr(SIMmax);
  NSveto = fD.ReadUnsignedLong(filename, "�������� ������ ����������", 0);
  Form_RearFromEEPROM->Edit_attr_09->Text = IntToStr(NSveto);
  SSPP = fD.ReadUnsignedLong(filename, "SSP", 0); // +
  Form_RearFromEEPROM->Edit_attr_10->Text = "0x" + IntToHex((BYTE)SSPP, 2);

  // ����� ����� EEPROM ���� � 44-����������
  k1 = fD.ReadFloat(filename, "k1", 0);
  A1 = fD.ReadFloat(filename, "A1", 0);
  k2 = fD.ReadFloat(filename, "k2", 0);
  A2 = fD.ReadFloat(filename, "A2", 0);

  Longk1 = fD.ReadUnsignedLong(filename, "Longk1", 1);
  LongA1 = fD.ReadUnsignedLong(filename, "LongA1", 1);
  Longk2 = fD.ReadUnsignedLong(filename, "Longk2", 1);
  LongA2 = fD.ReadUnsignedLong(filename, "LongA2", 1);

  // ������ ������������� �������� 0-255
  int j = 0;
  for ( int i = 0; i < 64; i++ )
  {
    j++;
    str = "���_" + IntToStr(j-1);
    MasSveto[j-1] = fD.ReadInteger(filename, str, 0);
    j++;
    str = "���_" + IntToStr(j-1);
    MasSveto[j-1] = fD.ReadInteger(filename, str, 0);
    j++;
    str = "���_" + IntToStr(j-1);
    MasSveto[j-1] = fD.ReadInteger(filename, str, 0);
    j++;
    str = "���_" + IntToStr(j-1);
    MasSveto[j-1] = fD.ReadInteger(filename, str, 0);
  }
  Form_RearFromEEPROM->Show();
  Form_RearFromEEPROM->StringGrid_small->Cells[1][1] = FormatFloat("0.000", k1);
  Form_RearFromEEPROM->StringGrid_small->Cells[2][1] = FormatFloat("0.0", A1);
  Form_RearFromEEPROM->StringGrid_small->Cells[3][1] = FormatFloat("0.000", k2);
  Form_RearFromEEPROM->StringGrid_small->Cells[4][1] = FormatFloat("0.0", A2);

  A1 = (-1 * A1);
  if (k2 != 0)
  {
    k2 = (1 / k2);
  }

  AnsiString str;
  j = 0;
  for ( int i = 0; i < 64; i++ )
  {
    for ( int k = 0; k < kol_zn; k++ )
    {
      if ( j == MasT[k] )
      {
        str = "+++";
        break;
      }
      else
      {
        str = "";
      }
    }
    Form_RearFromEEPROM->StringGrid_large->Cells[1][i+1] = IntToStr( MasSveto[j++] ) + str;
    for ( int k = 0; k < kol_zn; k++ )
    {
      if ( j == MasT[k] )
      {
        str = "+++";
        break;
      }
      else
      {
        str = "";
      }
    }
    Form_RearFromEEPROM->StringGrid_large->Cells[2][i+1] = IntToStr( MasSveto[j++] ) + str;
    for ( int k = 0; k < kol_zn; k++ )
    {
      if ( j == MasT[k] )
      {
        str = "+++";
        break;
      }
      else
      {
        str = "";
      }
    }
    Form_RearFromEEPROM->StringGrid_large->Cells[3][i+1] = IntToStr( MasSveto[j++] ) + str;
    for ( int k = 0; k < kol_zn; k++ )
    {
      if ( j == MasT[k] )
      {
        str = "+++";
        break;
      }
      else
      {
        str = "";
      }
    }
    Form_RearFromEEPROM->StringGrid_large->Cells[4][i+1] = IntToStr( MasSveto[j++] ) + str;
  }
  VyvEdit();
  RadioButton_Grafik2->Checked = true;
  Grafik();
  UpDown_KolVoPoints->Position = kol_zn;
  VisEdit();
  FlagFile = true; // ������ ������ �� �����  
}
//---------------------------------------------------------------------------
void __fastcall TForm_ARCH::VyvEdit(void)
{
  AnsiString str1, str2, str3;
  kol_zn = 0;
  for ( int i = 0; i <19 ; i++ )
  {
    str1 = fD.ReadString(filename, IntToStr(i+1) + ".�����������������", " ");
    str2 = fD.ReadString(filename, IntToStr(i+1) + ".��������������", " ");
    str3 = fD.ReadString(filename, IntToStr(i+1) + ".�������������", " ");
    if ( str1 != " " )
    {
      kol_zn++;
      switch ( i )
      {
      case 0:
        Edit_temperKam_01->Text = str1;
        TempKamera[i] = str1;
        Edit_kodTemper_01->Text = str2;
        Temp[i] = StrToInt(str2);
        Edit_kodSvd_01->Text = str3;
        Sveto[i] = StrToInt(str3);
        break;
      case 1:
        Edit_temperKam_02->Text = str1;
        TempKamera[i] = str1;
        Edit_kodTemper_02->Text = str2;
        Temp[i] = StrToInt(str2);
        Edit_kodSvd_02->Text = str3;
        Sveto[i] = StrToInt(str3);
        break;
      case 2:
        Edit_temperKam_03->Text = str1;
        TempKamera[i] = str1;
        Edit_kodTemper_03->Text = str2;
        Temp[i] = StrToInt(str2);
        Edit_kodSvd_03->Text = str3;
        Sveto[i] = StrToInt(str3);
        break;
      case 3:
        Edit_temperKam_04->Text = str1;
        TempKamera[i] = str1;
        Edit_kodTemper_04->Text = str2;
        Temp[i] = StrToInt(str2);
        Edit_kodSvd_04->Text = str3;
        Sveto[i] = StrToInt(str3);
        break;
      case 4:
        Edit_temperKam_05->Text = str1;
        TempKamera[i] = str1;
        Edit_kodTemper_05->Text = str2;
        Temp[i] = StrToInt(str2);
        Edit_kodSvd_05->Text = str3;
        Sveto[i] = StrToInt(str3);
        break;
      case 5:
        Edit_temperKam_06->Text = str1;
        TempKamera[i] = str1;
        Edit_kodTemper_06->Text = str2;
        Temp[i] = StrToInt(str2);
        Edit_kodSvd_06->Text = str3;
        Sveto[i] = StrToInt(str3);
        break;
      case 6:
        Edit_temperKam_07->Text = str1;
        TempKamera[i] = str1;
        Edit_kodTemper_07->Text = str2;
        Temp[i] = StrToInt(str2);
        Edit_kodSvd_07->Text = str3;
        Sveto[i] = StrToInt(str3);
        break;
      case 7:
        Edit_temperKam_08->Text = str1;
        TempKamera[i] = str1;
        Edit_kodTemper_08->Text = str2;
        Temp[i] = StrToInt(str2);
        Edit_kodSvd_08->Text = str3;
        Sveto[i] = StrToInt(str3);
        break;
      case 8:
        Edit_temperKam_09->Text = str1;
        TempKamera[i] = str1;
        Edit_kodTemper_09->Text = str2;
        Temp[i] = StrToInt(str2);
        Edit_kodSvd_09->Text = str3;
        Sveto[i] = StrToInt(str3);
        break;
      case 9:
        Edit_temperKam_10->Text = str1;
        TempKamera[i] = str1;
        Edit_kodTemper_10->Text = str2;
        Temp[i] = StrToInt(str2);
        Edit_kodSvd_10->Text = str3;
        Sveto[i] = StrToInt(str3);
        break;
      case 10:
        Edit_temperKam_11->Text = str1;
        TempKamera[i] = str1;
        Edit_kodTemper_11->Text = str2;
        Temp[i] = StrToInt(str2);
        Edit_kodSvd_11->Text = str3;
        Sveto[i] = StrToInt(str3);
        break;
      case 11:
        Edit_temperKam_12->Text = str1;
        TempKamera[i] = str1;
        Edit_kodTemper_12->Text = str2;
        Temp[i] = StrToInt(str2);
        Edit_kodSvd_12->Text = str3;
        Sveto[i] = StrToInt(str3);
        break;
      case 12:
        Edit_temperKam_13->Text = str1;
        TempKamera[i] = str1;
        Edit_kodTemper_13->Text = str2;
        Temp[i] = StrToInt(str2);
        Edit_kodSvd_13->Text = str3;
        Sveto[i] = StrToInt(str3);
        break;
      case 13:
        Edit_temperKam_14->Text = str1;
        TempKamera[i] = str1;
        Edit_kodTemper_14->Text = str2;
        Temp[i] = StrToInt(str2);
        Edit_kodSvd_14->Text = str3;
        Sveto[i] = StrToInt(str3);
        break;
      case 14:
        Edit_temperKam_15->Text = str1;
        TempKamera[i] = str1;
        Edit_kodTemper_15->Text = str2;
        Temp[i] = StrToInt(str2);
        Edit_kodSvd_15->Text = str3;
        Sveto[i] = StrToInt(str3);
        break;
      case 15:
        Edit_temperKam_16->Text = str1;
        TempKamera[i] = str1;
        Edit_kodTemper_16->Text = str2;
        Temp[i] = StrToInt(str2);
        Edit_kodSvd_16->Text = str3;
        Sveto[i] = StrToInt(str3);
        break;
      case 16:
        Edit_temperKam_17->Text = str1;
        TempKamera[i] = str1;
        Edit_kodTemper_17->Text = str2;
        Temp[i] = StrToInt(str2);
        Edit_kodSvd_17->Text = str3;
        Sveto[i] = StrToInt(str3);
        break;
      case 17:
        Edit_temperKam_18->Text = str1;
        TempKamera[i] = str1;
        Edit_kodTemper_18->Text = str2;
        Temp[i] = StrToInt(str2);
        Edit_kodSvd_18->Text = str3;
        Sveto[i] = StrToInt(str3);
        break;
      case 18:
        Edit_temperKam_19->Text = str1;
        TempKamera[i] = str1;
        Edit_kodTemper_19->Text = str2;
        Temp[i] = StrToInt(str2);
        Edit_kodSvd_19->Text = str3;
        Sveto[i] = StrToInt(str3);
        break;
      } // end switch ( i )
    } // end if ( str1 != " " )
  } // end for ( int i = 0; i <19 ; i++ )
}
//---------------------------------------------------------------------------
void __fastcall TForm_ARCH::Button_ReadFromEEPROMClick(TObject *Sender)
{
  // ������ �� EEPROMa
  union
  {
    float Flo;
    unsigned char Ch[4];
  } uu;
  union
  {
    unsigned long Lon;
    unsigned char Ch[4];
  } uuFL;

  unsigned long temp;

  if ( flagPort == false ) // ���� ������
  {
    ErrorCode = Form_82_Start->RSConnect( Form_82_Start->ComboBox_NomComPort->Text.c_str() ); // ������� ����
    if ( ErrorCode == 0 )
    {
      flagPort = true; // ��������� ����� ������ (true)/������ (false)
    }
    if ( flagPort == false ) // ���� �� �������� ������!
    {
      return;
    }
    KodVxod = true;
  }

  FlagFile = false;
  FlagEEPROM = false;
  FlagGrafik = false;

  Prot->ReadFlashInvert(0, &DNUZ);
  DNUZ = DNUZ & 0x0000FFFF;
  Prot->ReadFlashInvert(1, &DVUZ);
  DVUZ = DVUZ & 0x0000FFFF;
  Prot->ReadFlashInvert(2, &LEDAmpZ);
  LEDAmpZ = LEDAmpZ & 0x0000FFFF;
  Prot->ReadFlashInvert(3, &UhiZ);
  UhiZ = UhiZ & 0x0000FFFF;
  if ( Prot->flagModbusProtokol == 0 ) // ������ "������" ��������
  {
    Prot->ReadFlashInvert(4, &IndAdrZ);
  }
  else // ������ �������� "ModBus RTU", "ModBus TCP" ���� "ModBus RTU (TCP/IP)"
  {
    Prot->ReadFlash2(0x300 + 1, &IndAdrZ);
  }
  IndAdrZ = IndAdrZ & 0x000000FF;
  Prot->ReadFlashInvert(5, &GrpAdrZ);
  GrpAdrZ = GrpAdrZ & 0x000000FF;
  Prot->ReadFlash(6, &SSPP);
  SSPP = SSPP & 0x000000FF;
  Prot->ReadFlashInvert(7, &SIMstart);
  SIMstart = SIMstart & 0x0000FFFF;
  // ReadFlashInvert(8, &DlitPodintFon);
  // DlitPodintFon = DlitPodintFon & 0x0000FFFF;
  Prot->ReadFlashInvert(9, &SIMmax);
  SIMmax = SIMmax & 0x0000FFFF;
  Prot->ReadFlash(0x2B, &temp);
  NSveto = temp & 0x000000FF; // NSveto

  Form_RearFromEEPROM->Edit_attr_01->Text = IntToStr(IndAdrZ);
  Form_RearFromEEPROM->Edit_attr_02->Text = IntToStr(GrpAdrZ);
  Form_RearFromEEPROM->Edit_attr_03->Text = IntToStr(DNUZ);
  Form_RearFromEEPROM->Edit_attr_04->Text = IntToStr(DVUZ);
  Form_RearFromEEPROM->Edit_attr_05->Text = IntToStr(LEDAmpZ);
  Form_RearFromEEPROM->Edit_attr_06->Text = IntToStr(UhiZ);
  Form_RearFromEEPROM->Edit_attr_07->Text = IntToStr(SIMstart);
  Form_RearFromEEPROM->Edit_attr_08->Text = IntToStr(SIMmax);
  Form_RearFromEEPROM->Edit_attr_09->Text = IntToStr(NSveto);
  Form_RearFromEEPROM->Edit_attr_10->Text = "0x" + IntToHex((BYTE)SSPP, 2);


  // if ( !Form1->Privet(AdresBD) )
  //{
  //  return;
  //}
  k1 = A1 = k2 = A2 = 0;


  /**/
  Prot->ReadKoef(
      &k1,
      &Longk1,
      &A1,
      &LongA1,
      &k2,
      &Longk2,
      &A2,
      &LongA2,
      MasSveto    
    );
  /**/
  Form_RearFromEEPROM->Show();
  Form_RearFromEEPROM->StringGrid_small->Cells[1][1] = FormatFloat("0.000", k1);
  Form_RearFromEEPROM->StringGrid_small->Cells[2][1] = FormatFloat("0.0", A1);
  Form_RearFromEEPROM->StringGrid_small->Cells[3][1] = FormatFloat("0.000", k2);
  Form_RearFromEEPROM->StringGrid_small->Cells[4][1] = FormatFloat("0.0", A2);

  A1 = (-1 * A1);
  if ( k2 != 0)
  {
    k2 = (1 / k2);
  }
  AnsiString str;
  int j = 0;
  for ( int i = 0; i < 64; i++ )
  {
    for ( int k = 0; k < kol_zn; k++ )
    {
      if ( j == MasT[k] )
      {
        str = "+++";
        break;
      }
      else
      {
        str = "";
      }
    }
    Form_RearFromEEPROM->StringGrid_large->Cells[1][i+1] = IntToStr(MasSveto[j++]) + str;
    for ( int k = 0; k < kol_zn; k++ )
    {
      if ( j == MasT[k] )
      {
        str = "+++";
        break;
      }
      else
      {
        str = "";
      }
    }
    Form_RearFromEEPROM->StringGrid_large->Cells[2][i+1] = IntToStr( MasSveto[j++] ) + str;
    for ( int k = 0; k < kol_zn; k++ )
    {
      if ( j == MasT[k] )
      {
        str = "+++";
        break;
      }
      else
      {
        str = "";
      }
    }
    Form_RearFromEEPROM->StringGrid_large->Cells[3][i+1] = IntToStr( MasSveto[j++] ) + str;
    for ( int k = 0; k < kol_zn; k++ )
    {
      if ( j == MasT[k] )
      {
        str = "+++";
        break;
      }
      else
      {
        str = "";
      }
    }
    Form_RearFromEEPROM->StringGrid_large->Cells[4][i+1] = IntToStr( MasSveto[j++] ) + str;
    //\\Application->ProcessMessages();
  }
  RadioButton_Grafik2->Checked = true;
  Grafik();
  // ������ �� EEPROM� ��������� �������� ������
  unsigned int adress = 0xB0;
  unsigned char n1;
  Prot->ReadFlash(adress++, &uuFL.Lon);
  kol_zn = uuFL.Ch[0];

  // 03.09.2015 ===>>
  if ( kol_zn > 19 )
  {
    kol_zn = 19; // ������ �� ������������ ��������
  }
  // 03.09.2015 <<===

  for ( int i = 0; i < kol_zn; i++ )
  {
    Prot->ReadFlash( adress++, &uuFL.Lon );
    n1 = uuFL.Ch[0];
    TempKamera[i] = "";
    for ( int k = 0; k < n1; k = k + 4 )
    {
      Prot->ReadFlash(adress++, &uuFL.Lon);
      if ( k < n1 )
      {
        TempKamera[i] = TempKamera[i] + (char)uuFL.Ch[0];
      }
      if ( k + 1 < n1 )
      {
        TempKamera[i] = TempKamera[i] + (char)uuFL.Ch[1];
      }
      if ( k + 2 < n1 )
      {
        TempKamera[i] = TempKamera[i] + (char)uuFL.Ch[2];
      }
      if ( k + 3 < n1 )
      {
        TempKamera[i] = TempKamera[i] + (char)uuFL.Ch[3];
      }
    }
    Prot->ReadFlash( adress++, &uuFL.Lon );
    Temp[i] = uuFL.Ch[1];
    Temp[i] = Temp[i] << 8;
    Temp[i] = Temp[i] + uuFL.Ch[0];

    Sveto[i] = uuFL.Ch[3];
    Sveto[i] = Sveto[i] << 8;
    Sveto[i] = Sveto[i] + uuFL.Ch[2];
  } // end for ( int k = 0; k < n1; k = k + 4 )

  for ( int i = 0; i < kol_zn; i++ )
  {
    switch ( i )
    {
    case 0:
      Edit_temperKam_01->Text = TempKamera[i];
      Edit_kodTemper_01->Text = IntToStr(Temp[i]);
      Edit_kodSvd_01->Text = IntToStr(Sveto[i]);
      break;
    case 1:
      Edit_temperKam_02->Text = TempKamera[i];
      Edit_kodTemper_02->Text = IntToStr(Temp[i]);
      Edit_kodSvd_02->Text = IntToStr(Sveto[i]);
      break;
    case 2:
      Edit_temperKam_03->Text = TempKamera[i];
      Edit_kodTemper_03->Text = IntToStr(Temp[i]);
      Edit_kodSvd_03->Text = IntToStr(Sveto[i]);
      break;
    case 3:
      Edit_temperKam_04->Text = TempKamera[i];
      Edit_kodTemper_04->Text = IntToStr(Temp[i]);
      Edit_kodSvd_04->Text = IntToStr(Sveto[i]);
      break;
    case 4:
      Edit_temperKam_05->Text = TempKamera[i];
      Edit_kodTemper_05->Text = IntToStr(Temp[i]);
      Edit_kodSvd_05->Text = IntToStr(Sveto[i]);
      break;
    case 5:
      Edit_temperKam_06->Text = TempKamera[i];
      Edit_kodTemper_06->Text = IntToStr(Temp[i]);
      Edit_kodSvd_06->Text = IntToStr(Sveto[i]);
      break;
    case 6:
      Edit_temperKam_07->Text = TempKamera[i];
      Edit_kodTemper_07->Text = IntToStr(Temp[i]);
      Edit_kodSvd_07->Text = IntToStr(Sveto[i]);
      break;
    case 7:
      Edit_temperKam_08->Text = TempKamera[i];
      Edit_kodTemper_08->Text = IntToStr(Temp[i]);
      Edit_kodSvd_08->Text = IntToStr(Sveto[i]);
      break;
    case 8:
      Edit_temperKam_09->Text = TempKamera[i];
      Edit_kodTemper_09->Text = IntToStr(Temp[i]);
      Edit_kodSvd_09->Text = IntToStr(Sveto[i]);
      break;
    case 9:
      Edit_temperKam_10->Text = TempKamera[i];
      Edit_kodTemper_10->Text = IntToStr(Temp[i]);
      Edit_kodSvd_10->Text = IntToStr(Sveto[i]);
      break;
    case 10:
      Edit_temperKam_11->Text = TempKamera[i];
      Edit_kodTemper_11->Text = IntToStr(Temp[i]);
      Edit_kodSvd_11->Text = IntToStr(Sveto[i]);
      break;
    case 11:
      Edit_temperKam_12->Text = TempKamera[i];
      Edit_kodTemper_12->Text = IntToStr(Temp[i]);
      Edit_kodSvd_12->Text = IntToStr(Sveto[i]);
      break;
    case 12:
      Edit_temperKam_13->Text = TempKamera[i];
      Edit_kodTemper_13->Text = IntToStr(Temp[i]);
      Edit_kodSvd_13->Text = IntToStr(Sveto[i]);
      break;
    case 13:
      Edit_temperKam_14->Text = TempKamera[i];
      Edit_kodTemper_14->Text = IntToStr(Temp[i]);
      Edit_kodSvd_14->Text = IntToStr(Sveto[i]);
      break;
    case 14:
      Edit_temperKam_15->Text = TempKamera[i];
      Edit_kodTemper_15->Text = IntToStr(Temp[i]);
      Edit_kodSvd_15->Text = IntToStr(Sveto[i]);
      break;
    case 15:
      Edit_temperKam_16->Text = TempKamera[i];
      Edit_kodTemper_16->Text = IntToStr(Temp[i]);
      Edit_kodSvd_16->Text = IntToStr(Sveto[i]);
      break;
    case 16:
      Edit_temperKam_17->Text = TempKamera[i];
      Edit_kodTemper_17->Text = IntToStr(Temp[i]);
      Edit_kodSvd_17->Text = IntToStr(Sveto[i]);
      break;
    case 17:
      Edit_temperKam_18->Text = TempKamera[i];
      Edit_kodTemper_18->Text = IntToStr(Temp[i]);
      Edit_kodSvd_18->Text = IntToStr(Sveto[i]);
      break;
    case 18:
      Edit_temperKam_19->Text = TempKamera[i];
      Edit_kodTemper_19->Text = IntToStr(Temp[i]);
      Edit_kodSvd_19->Text = IntToStr(Sveto[i]);
      break;
    } // end switch ( i )
  } // end for ( int i = 0; i < kol_zn; i++ )
  UpDown_KolVoPoints->Position = kol_zn;
  VisEdit();
  ZapisFile(Edit_WriteFileStr->Text);
  FlagEEPROM = true; // ������ ������ �� �������
  if ( KodVxod )
  {
    flagPort = false; // ��������� ����� ������ (true)/������ (false)
    Form_82_Start->RSDisConnect();
  }
}
//---------------------------------------------------------------------------
void TForm_ARCH::ZapisFile(AnsiString filename)
{
  // filename = FileNameEdit3->Text;
  // filename = FileNameEdit2->Text;
  TDateTime Td( Now() );
  AnsiString stime = Td.TimeString();
  AnsiString sdate = Td.DateString();
  fD.WriteString ( filename, "�������� ������", sdate + "   " + stime);
  AnsiString str = "";

  for ( int i = 0; i < kol_zn; i++ )
  {
    fD.WriteString ( filename, IntToStr(i+1) + ".�����������������", TempKamera[i] );
    fD.WriteString ( filename, IntToStr(i+1) + ".��������������", IntToStr ( Temp[i] ) );
    fD.WriteString ( filename, IntToStr(i+1) + ".�������������", IntToStr ( Sveto[i] ) );
  }
  if ( kol_zn < 19 )
  {
    for ( int i = kol_zn; i <19; i++ )
    {
      fD.ClearString ( filename, IntToStr(i+1) + ".�����������������" );
      fD.ClearString ( filename, IntToStr(i+1) + ".��������������" );
      fD.ClearString ( filename, IntToStr(i+1) + ".�������������" );
    }
  }
  fD.WriteUnsignedLong ( filename, "�������������� �����", IndAdrZ );
  fD.WriteUnsignedLong ( filename, "��������� �����", GrpAdrZ );
  fD.WriteUnsignedLong ( filename, "���", DNUZ );
  fD.WriteUnsignedLong ( filename, "���", DVUZ );
  fD.WriteUnsignedLong ( filename, "��������� �������� �� ����������", LEDAmpZ );
  fD.WriteUnsignedLong ( filename, "������������ ��� �����.", UhiZ );
  fD.WriteUnsignedLong ( filename, "������ ��� ���", SIMstart );
  fD.WriteUnsignedLong ( filename, "������ ��� max", SIMmax );
  fD.WriteUnsignedLong ( filename, "�������� ������ ����������", NSveto );
  fD.WriteUnsignedLong ( filename, "SSP", SSPP );

  fD.WriteFloat ( filename, "k1", k1 );
  fD.WriteFloat ( filename, "A1", A1 );
  fD.WriteFloat ( filename, "k2", k2 );
  fD.WriteFloat ( filename, "A2", A2 );

  fD.WriteUnsignedLong ( filename, "Longk1", Longk1 );
  fD.WriteUnsignedLong ( filename, "LongA1", LongA1 );
  fD.WriteUnsignedLong ( filename, "Longk2", Longk2 );
  fD.WriteUnsignedLong ( filename, "LongA2", LongA2 );

  // ������ ������������� �������� 0 - 255
  int j = 0;
  for ( int i = 0; i < 64; i++ )
  {
    j++;
    str = "���_" + IntToStr(j-1);
    fD.WriteInteger ( filename, str, MasSveto[j-1] );
    j++;
    str = "���_" + IntToStr(j-1);
    fD.WriteInteger ( filename, str, MasSveto[j-1] );
    j++;
    str = "���_" + IntToStr(j-1);
    fD.WriteInteger ( filename, str, MasSveto[j-1] );
    j++;
    str = "���_" + IntToStr(j-1);
    fD.WriteInteger ( filename, str, MasSveto[j-1] );
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_ARCH::Button_WriteToEEPROMClick(TObject *Sender)
{
  if ( !FlagFile && !FlagEEPROM && !FlagGrafik )
  {
    Application->MessageBox("��������� �� �������� ������", "��������", MB_ICONSTOP);
    return;
  }
  if ( Application->MessageBox("���������� ������ � EEPROM BD82", "�� �������?", MB_YESNO) != IDYES )
  {
    return;
  }
  if ( flagPort == false ) // ���� ������
  {
    ErrorCode = Form_82_Start->RSConnect( Form_82_Start->ComboBox_NomComPort->Text.c_str() ); // ������� ����
    if ( ErrorCode == 0 )
    {
      flagPort = true; // ��������� ����� ������ (true)/������ (false)
    }
    if ( flagPort == false ) // ���� �� �������� ������!
    {
      return;
    }
    KodVxod = true;
  }
  Button_WriteToEEPROM->Enabled = false;
  ZapEEPROM();
  ZapisFile( Edit_WriteFileStr->Text );
  Button_WriteToEEPROM->Enabled = true;
  if ( KodVxod )
  {
    flagPort = false; // ��������� ����� ������ (true)/������ (false)
    Form_82_Start->RSDisConnect();
  }  
}
//---------------------------------------------------------------------------
void __fastcall TForm_ARCH::ZapEEPROM(void)
{
  // ������������ ������ � EEPROM
  unsigned long temp = 0;
  unsigned char temp2 = 0;
  // ����� ����� EEPROM ���� � 51-���������� // 44
  union
  {
    float Flo;
    unsigned char Ch[4];
  } uu;
  union
  {
    unsigned long Lon;
    unsigned char Ch[4];
  } uuFL;

  if ( FlagGrafik ) // ���� ������ � �����
  {
    IshDan(); // ���� �������� �����
    if ( err )
    {
      return;
    }
    Interpol();
  }
  // ����� ��������� ������ � ������
  unsigned int adress = 0xB0;
  unsigned char n1;
  uuFL.Ch[0] = kol_zn;
  uuFL.Ch[1] = 0;
  uuFL.Ch[2] = 0;
  uuFL.Ch[3] = 0;
  Prot->WriteFlash ( adress++, uuFL.Lon );
  for ( int i = 0; i < kol_zn; i++ )
  {
    n1 = TempKamera[i].Length();
    uuFL.Ch[0] = n1;
    uuFL.Ch[1] = 0;
    uuFL.Ch[2] = 0;
    uuFL.Ch[3] = 0;
    Prot->WriteFlash ( adress++, uuFL.Lon );
    for ( int k = 0; k < n1; k = k +4)
    {
      if ( k < n1 )
      {
        uuFL.Ch[0] = (unsigned char)TempKamera[i][k+1];
      }

      if ( k + 1 < n1 )
      {
        uuFL.Ch[1] = (unsigned char)TempKamera[i][k+2];
      }
      else
      {
        uuFL.Ch[1] = 0;
      }

      if ( k + 2 < n1 )
      {
        uuFL.Ch[2] = (unsigned char)TempKamera[i][k+3];
      }
      else
      {
        uuFL.Ch[2] = 0;
      }

      if ( k + 3 < n1 )
      {
        uuFL.Ch[3] = (unsigned char)TempKamera[i][k+4];
      }
      else
      {
        uuFL.Ch[3] = 0;
      }
      Prot->WriteFlash ( adress++, uuFL.Lon );
    }
    uuFL.Ch[0] = Temp[i] & 0x00FF;
    uuFL.Ch[1] = Temp[i] >> 8;
    uuFL.Ch[2] = Sveto[i] & 0x00FF;
    uuFL.Ch[3] = Sveto[i] >> 8;
    Prot->WriteFlash ( adress++, uuFL.Lon );
  } // end for ( int i = 0; i < kol_zn; i++ )
  // ��� 04.09.2015 ===>>
  // ��� 24.01.2018 ===>>
  unsigned long U_Nom = 0;
  Prot->ReadFlashInvert( 12, &U_Nom );
  if ( U_Nom == 600 )
  {
    SIMmax -= 1000;  
  }
  // ��� 24.01.2018 <<===
  Prot->WriteFlashInvert ( 9, SIMmax ); //==\\ SIMmax - ������ ��� �����������
  Prot->ReadFlashInvert( 9, &SIMmaxPR ); //==\\
  // ��� 04.09.2015 <<===
  if ( SIMmaxPR != SIMmax )
  {
    Application->MessageBox( "�������� �� ���������� � EEPROM", "������ ��� �����������", MB_ICONINFORMATION );
  }
  if ( !FlagGrafik ) // ���� ������� �� ����� ��� EEPROM�
  {
    // ���������� ��, ��, ���, ��� � �.�.
    Prot->WriteFlashInvert (0, DNUZ );
    Prot->WriteFlashInvert (1, DVUZ );
    Prot->WriteFlashInvert (2, LEDAmpZ );
    Prot->WriteFlashInvert (3, UhiZ );
    Prot->WriteFlashInvert (4, IndAdrZ );
    Prot->WriteFlashInvert (5, GrpAdrZ );
    temp2 = SSPP;
    Prot->WriteFlash ( 6, temp2 );
    Prot->WriteFlashInvert ( 7, SIMstart );
    // WriteFlashInvert(8,DlitPodintFon);
    //==\\Prot->WriteFlashInvert ( 9, SIMmax ); // SIMmax - ������ ��� �����������
    temp = NSveto;
    Prot->WriteFlash ( 0x2B, temp ); // NSveto  -------------------------------------------------------

    // ��������, ��� ��������!!!**********************************************************
    Prot->ReadFlashInvert(0, &DNUZPR);
    DNUZPR = DNUZPR & 0x0000FFFF;
    Prot->ReadFlashInvert(1, &DVUZPR);
    DVUZPR = DVUZPR & 0x0000FFFF;
    Prot->ReadFlashInvert(2, &LEDAmpZPR);
    LEDAmpZPR = LEDAmpZPR & 0x0000FFFF;
    Prot->ReadFlashInvert(3, &UhiZPR);
    UhiZPR = UhiZPR & 0x0000FFFF;
    Prot->ReadFlashInvert(4, &IndAdrZPR);
    IndAdrZPR = IndAdrZPR & 0x000000FF;
    Prot->ReadFlashInvert(5, &GrpAdrZPR);
    GrpAdrZPR = GrpAdrZPR & 0x000000FF;
    Prot->ReadFlash(6, &SSPPPR);
    SSPPPR = SSPPPR & 0x000000FF;
    Prot->ReadFlashInvert(7, &SIMstartPR);
    SIMstartPR = SIMstartPR & 0x0000FFFF;
    //==\\Prot->ReadFlashInvert(9, &SIMmaxPR);
    SIMmaxPR = SIMmaxPR & 0x0000FFFF;
    Prot->ReadFlash(0x2B, &temp);
    NSvetoPR = temp & 0x000000FF; // NSveto

    // �������, ��� ������ �������� � ��� ����������!!********************************
    if ( DNUZPR != DNUZ )
    {
      Application->MessageBox("�������� �� ���������� � EEPROM", "���", MB_ICONINFORMATION);
    }
    if ( DVUZPR != DVUZ )
    {
      Application->MessageBox("�������� �� ���������� � EEPROM", "���", MB_ICONINFORMATION);
    }
    if ( LEDAmpZPR != LEDAmpZ )
    {
      Application->MessageBox("�������� �� ���������� � EEPROM", "��������� �������� �� ����������", MB_ICONINFORMATION);
    }
    if ( UhiZPR != UhiZ )
    {
      Application->MessageBox("�������� �� ���������� � EEPROM", "������� ����������", MB_ICONINFORMATION);
    }
    if ( IndAdrZPR != IndAdrZ )
    {
      Application->MessageBox("�������� �� ���������� � EEPROM", "�������������� �����", MB_ICONINFORMATION);
    }
    if ( GrpAdrZPR != GrpAdrZ )
    {
      Application->MessageBox("�������� �� ���������� � EEPROM", "��������� �����", MB_ICONINFORMATION);
    }
    if ( SSPPPR != SSPP )
    {
      Application->MessageBox("�������� �� ���������� � EEPROM", "SSP", MB_ICONINFORMATION);
    }
    if ( SIMstartPR != SIMstart )
    {
      Application->MessageBox("�������� �� ���������� � EEPROM", "������ ��� ���������", MB_ICONINFORMATION);
    }
    // if ( DlitPodintFonPR != DlitPodintFon )
    //{
    //  Application->MessageBox("�������� �� ���������� � EEPROM", "���������� ������������� ����", MB_ICONINFORMATION);
    //}
    //==\\if ( SIMmaxPR != SIMmax )
    //==\\{
    //==\\  Application->MessageBox("�������� �� ���������� � EEPROM", "������ ��� �����������", MB_ICONINFORMATION);
    //==\\}
    if ( NSvetoPR != NSveto )
    {
      Application->MessageBox("�������� �� ���������� � EEPROM", "�������� ������ ����������", MB_ICONINFORMATION);
    }
  }
  else //==\\ if ( FlagGrafik == true )// ���� ����� ������ � ������� - ��������� ������� �� �������
  {

    Prot->ReadFlashInvert(0, &DNUZ);
    DNUZ = DNUZ & 0x0000FFFF;
    Prot->ReadFlashInvert(1, &DVUZ);
    DVUZ = DVUZ & 0x0000FFFF;
    Prot->ReadFlashInvert(2, &LEDAmpZ);
    LEDAmpZ = LEDAmpZ & 0x0000FFFF;
    Prot->ReadFlashInvert(3, &UhiZ);
    UhiZ = UhiZ & 0x0000FFFF;
    Prot->ReadFlashInvert(4, &IndAdrZ);
    IndAdrZ = IndAdrZ & 0x000000FF;
    Prot->ReadFlashInvert(5, &GrpAdrZ);
    GrpAdrZ = GrpAdrZ & 0x000000FF;
    Prot->ReadFlash(6, &SSPP);
    SSPP = SSPP & 0x000000FF;
    Prot->ReadFlashInvert(7, &SIMstart);
    SIMstart = SIMstart & 0x0000FFFF;
    // ReadFlashInvert(8, &DlitPodintFon);
    // DlitPodintFon = DlitPodintFon & 0x0000FFFF;
    Prot->ReadFlashInvert(9, &SIMmax);
    SIMmax = SIMmax & 0x0000FFFF;
    Prot->ReadFlash(0x2B, &temp);
    NSveto = temp & 0x000000FF; // NSveto
  } // end if ( !FlagGrafik )
  unsigned long Longk1_2, LongA1_2, Longk2_2, LongA2_2;
  A1 = ( -1 * A1 );
  if ( k2 != 0 )
  {
    k2 = ( 1 / k2 );
  }
  Prot->WriteKoef(
    &k1,
    &Longk1,
    &A1,
    &LongA1,
    &k2,
    &Longk2,
    &A2,
    &LongA2,
    MasSveto,
    FlagGrafik
    );
  Application->MessageBox("��������� ������ � EEPROM!", "��������!", MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------
void __fastcall TForm_ARCH::Button_ParamIzFaylaClick(TObject *Sender)
{
  TIniFile * IniFile = new TIniFile(IniFileName);
  try
  {
    m_strLogFileName = IniFile->ReadString( "Form ARCH Settings", "LogFileName", "NastrBD.log" );
    delete IniFile;
  }
  catch (...)
  {
    delete IniFile;
    ShowMessage("�������� ���������� ��� ������ �������� *.ini");    
  }

  Form_LoadParam->Edit_LogFileName->Text = m_strLogFileName;

  if ( mrOk == Form_LoadParam->ShowModal() )
  {
    // Show fields.
    std::list<Param> params;
    Form_LoadParam->GetParams(params);
    SIMmax = Form_LoadParam->DiaShim_Min;

    if ( !params.empty() )
    {
      // Hide fields.
      Edit_temperKam_01->Visible = false;
      Edit_kodTemper_01->Visible = false;
      Edit_kodSvd_01->Visible = false;
      Edit_temperKam_02->Visible = false;
      Edit_kodTemper_02->Visible = false;
      Edit_kodSvd_02->Visible = false;
      Edit_temperKam_03->Visible = false;
      Edit_kodTemper_03->Visible = false;
      Edit_kodSvd_03->Visible = false;
      Edit_temperKam_04->Visible = false;
      Edit_kodTemper_04->Visible = false;
      Edit_kodSvd_04->Visible = false;
      Edit_temperKam_05->Visible = false;
      Edit_kodTemper_05->Visible = false;
      Edit_kodSvd_05->Visible = false;
      Edit_temperKam_06->Visible = false;
      Edit_kodTemper_06->Visible = false;
      Edit_kodSvd_06->Visible = false;
      Edit_temperKam_07->Visible = false;
      Edit_kodTemper_07->Visible = false;
      Edit_kodSvd_07->Visible = false;
      Edit_temperKam_08->Visible = false;
      Edit_kodTemper_08->Visible = false;
      Edit_kodSvd_08->Visible = false;
      Edit_temperKam_09->Visible = false;
      Edit_kodTemper_09->Visible = false;
      Edit_kodSvd_09->Visible = false;
      Edit_temperKam_10->Visible = false;
      Edit_kodTemper_10->Visible = false;
      Edit_kodSvd_10->Visible = false;
      Edit_temperKam_11->Visible = false;
      Edit_kodTemper_11->Visible = false;
      Edit_kodSvd_11->Visible = false;
      Edit_temperKam_12->Visible = false;
      Edit_kodTemper_12->Visible = false;
      Edit_kodSvd_12->Visible = false;
      Edit_temperKam_13->Visible = false;
      Edit_kodTemper_13->Visible = false;
      Edit_kodSvd_13->Visible = false;
      Edit_temperKam_14->Visible = false;
      Edit_kodTemper_14->Visible = false;
      Edit_kodSvd_14->Visible = false;
      Edit_temperKam_15->Visible = false;
      Edit_kodTemper_15->Visible = false;
      Edit_kodSvd_15->Visible = false;
      Edit_temperKam_16->Visible = false;
      Edit_kodTemper_16->Visible = false;
      Edit_kodSvd_16->Visible = false;
      Edit_temperKam_17->Visible = false;
      Edit_kodTemper_17->Visible = false;
      Edit_kodSvd_17->Visible = false;
      Edit_temperKam_18->Visible = false;
      Edit_kodTemper_18->Visible = false;
      Edit_kodSvd_18->Visible = false;
      Edit_temperKam_19->Visible = false;
      Edit_kodTemper_19->Visible = false;
      Edit_kodSvd_19->Visible = false;
      //
      int n = 1;
      int kolvopoints = 0;
      // Sort fields.
      params.sort();
      for ( std::list<Param>::iterator i = params.begin();
          i != params.end(); i++, n++)
      {
        kolvopoints++;
        if ( !i->m_xChecked )
        {
          n--;
          continue;
        }
        switch( n )
        {
        case 1:
          Edit_temperKam_01->Visible = true;
          Edit_temperKam_01->Text = FloatToStrF(i->m_fltTValue, ffFixed , 8, 1);
          Edit_kodTemper_01->Visible = true;
          Edit_kodTemper_01->Text = IntToStr(i->m_nTCode);
          Edit_kodSvd_01->Visible = true;
          Edit_kodSvd_01->Text = IntToStr(i->m_nLedCode);
          break;
        case 2:
          Edit_temperKam_02->Visible = true;
          Edit_temperKam_02->Text = FloatToStrF(i->m_fltTValue, ffFixed , 8, 1);
          Edit_kodTemper_02->Visible = true;
          Edit_kodTemper_02->Text = IntToStr(i->m_nTCode);
          Edit_kodSvd_02->Visible = true;
          Edit_kodSvd_02->Text = IntToStr(i->m_nLedCode);
          break;
        case 3:
          Edit_temperKam_03->Visible = true;
          Edit_temperKam_03->Text = FloatToStrF(i->m_fltTValue, ffFixed , 8, 1);
          Edit_kodTemper_03->Visible = true;
          Edit_kodTemper_03->Text = IntToStr(i->m_nTCode);
          Edit_kodSvd_03->Visible = true;
          Edit_kodSvd_03->Text = IntToStr(i->m_nLedCode);
          break;
        case 4:
          Edit_temperKam_04->Visible = true;
          Edit_temperKam_04->Text = FloatToStrF(i->m_fltTValue, ffFixed , 8, 1);
          Edit_kodTemper_04->Visible = true;
          Edit_kodTemper_04->Text = IntToStr(i->m_nTCode);
          Edit_kodSvd_04->Visible = true;
          Edit_kodSvd_04->Text = IntToStr(i->m_nLedCode);
          break;
        case 5:
          Edit_temperKam_05->Visible = true;
          Edit_temperKam_05->Text = FloatToStrF(i->m_fltTValue, ffFixed , 8, 1);
          Edit_kodTemper_05->Visible = true;
          Edit_kodTemper_05->Text = IntToStr(i->m_nTCode);
          Edit_kodSvd_05->Visible = true;
          Edit_kodSvd_05->Text = IntToStr(i->m_nLedCode);
          break;
        case 6:
          Edit_temperKam_06->Visible = true;
          Edit_temperKam_06->Text = FloatToStrF(i->m_fltTValue, ffFixed , 8, 1);
          Edit_kodTemper_06->Visible = true;
          Edit_kodTemper_06->Text = IntToStr(i->m_nTCode);
          Edit_kodSvd_06->Visible = true;
          Edit_kodSvd_06->Text = IntToStr(i->m_nLedCode);
          break;
        case 7:
          Edit_temperKam_07->Visible = true;
          Edit_temperKam_07->Text = FloatToStrF(i->m_fltTValue, ffFixed , 8, 1);
          Edit_kodTemper_07->Visible = true;
          Edit_kodTemper_07->Text = IntToStr(i->m_nTCode);
          Edit_kodSvd_07->Visible = true;
          Edit_kodSvd_07->Text = IntToStr(i->m_nLedCode);
          break;
        case 8:
          Edit_temperKam_08->Visible = true;
          Edit_temperKam_08->Text = FloatToStrF(i->m_fltTValue, ffFixed , 8, 1);
          Edit_kodTemper_08->Visible = true;
          Edit_kodTemper_08->Text = IntToStr(i->m_nTCode);
          Edit_kodSvd_08->Visible = true;
          Edit_kodSvd_08->Text = IntToStr(i->m_nLedCode);
          break;
        case 9:
          Edit_temperKam_09->Visible = true;
          Edit_temperKam_09->Text = FloatToStrF(i->m_fltTValue, ffFixed , 8, 1);
          Edit_kodTemper_09->Visible = true;
          Edit_kodTemper_09->Text = IntToStr(i->m_nTCode);
          Edit_kodSvd_09->Visible = true;
          Edit_kodSvd_09->Text = IntToStr(i->m_nLedCode);
          break;
        case 10:
          Edit_temperKam_10->Visible = true;
          Edit_temperKam_10->Text = FloatToStrF(i->m_fltTValue, ffFixed , 8, 1);
          Edit_kodTemper_10->Visible = true;
          Edit_kodTemper_10->Text = IntToStr(i->m_nTCode);
          Edit_kodSvd_10->Visible = true;
          Edit_kodSvd_10->Text = IntToStr(i->m_nLedCode);
          break;
        case 11:
          Edit_temperKam_11->Visible = true;
          Edit_temperKam_11->Text = FloatToStrF(i->m_fltTValue, ffFixed , 8, 1);
          Edit_kodTemper_11->Visible = true;
          Edit_kodTemper_11->Text = IntToStr(i->m_nTCode);
          Edit_kodSvd_11->Visible = true;
          Edit_kodSvd_11->Text = IntToStr(i->m_nLedCode);
          break;
        case 12:
          Edit_temperKam_12->Visible = true;
          Edit_temperKam_12->Text = FloatToStrF(i->m_fltTValue, ffFixed , 8, 1);
          Edit_kodTemper_12->Visible = true;
          Edit_kodTemper_12->Text = IntToStr(i->m_nTCode);
          Edit_kodSvd_12->Visible = true;
          Edit_kodSvd_12->Text = IntToStr(i->m_nLedCode);
          break;
        case 13:
          Edit_temperKam_13->Visible = true;
          Edit_temperKam_13->Text = FloatToStrF(i->m_fltTValue, ffFixed , 8, 1);
          Edit_kodTemper_13->Visible = true;
          Edit_kodTemper_13->Text = IntToStr(i->m_nTCode);
          Edit_kodSvd_13->Visible = true;
          Edit_kodSvd_13->Text = IntToStr(i->m_nLedCode);
          break;
        case 14:
          Edit_temperKam_14->Visible = true;
          Edit_temperKam_14->Text = FloatToStrF(i->m_fltTValue, ffFixed , 8, 1);
          Edit_kodTemper_14->Visible = true;
          Edit_kodTemper_14->Text = IntToStr(i->m_nTCode);
          Edit_kodSvd_14->Visible = true;
          Edit_kodSvd_14->Text = IntToStr(i->m_nLedCode);
          break;
        case 15:
          Edit_temperKam_15->Visible = true;
          Edit_temperKam_15->Text = FloatToStrF(i->m_fltTValue, ffFixed , 8, 1);
          Edit_kodTemper_15->Visible = true;
          Edit_kodTemper_15->Text = IntToStr(i->m_nTCode);
          Edit_kodSvd_15->Visible = true;
          Edit_kodSvd_15->Text = IntToStr(i->m_nLedCode);
          break;
        case 16:
          Edit_temperKam_16->Visible = true;
          Edit_temperKam_16->Text = FloatToStrF(i->m_fltTValue, ffFixed , 8, 1);
          Edit_kodTemper_16->Visible = true;
          Edit_kodTemper_16->Text = IntToStr(i->m_nTCode);
          Edit_kodSvd_16->Visible = true;
          Edit_kodSvd_16->Text = IntToStr(i->m_nLedCode);
          break;
        case 17:
          Edit_temperKam_17->Visible = true;
          Edit_temperKam_17->Text = FloatToStrF(i->m_fltTValue, ffFixed , 8, 1);
          Edit_kodTemper_17->Visible = true;
          Edit_kodTemper_17->Text = IntToStr(i->m_nTCode);
          Edit_kodSvd_17->Visible = true;
          Edit_kodSvd_17->Text = IntToStr(i->m_nLedCode);
          break;
        case 18:
          Edit_temperKam_18->Visible = true;
          Edit_temperKam_18->Text = FloatToStrF(i->m_fltTValue, ffFixed , 8, 1);
          Edit_kodTemper_18->Visible = true;
          Edit_kodTemper_18->Text = IntToStr(i->m_nTCode);
          Edit_kodSvd_18->Visible = true;
          Edit_kodSvd_18->Text = IntToStr(i->m_nLedCode);
          break;
        case 19:
          Edit_temperKam_18->Visible = true;
          Edit_temperKam_18->Text = FloatToStrF(i->m_fltTValue, ffFixed , 8, 1);
          Edit_kodTemper_18->Visible = true;
          Edit_kodTemper_18->Text = IntToStr(i->m_nTCode);
          Edit_kodSvd_18->Visible = true;
          Edit_kodSvd_18->Text = IntToStr(i->m_nLedCode);
          break;
        } // end switch( n )
      } // end for ( std::list<Param>::iterator i = params.begin()...
      UpDown_KolVoPoints->Position = kolvopoints;
    } // end if ( !params.empty() )
  } // end if ( mrOk == FrmLoadParam->ShowModal() )
}
//---------------------------------------------------------------------------

