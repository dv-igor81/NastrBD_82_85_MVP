//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.h> // exp()
#include <iostream>
#include <fstream>
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma hdrstop
#include "Unit_82_Form_Graph.h"
#include "Unit_82_Form_Start.h"
#include "Unit_82_Priklad_Funk.h"

#ifdef _DIA_OBEDINENIE_
  #include "Unit_FormDispet.h"
#endif
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_Graph *Form_Graph;
//---------------------------------------------------------------------------
__fastcall TForm_Graph::TForm_Graph(TComponent* Owner)
        : TForm(Owner)
{
  bFlagWork = false; // ���� ������ ��������� �������/��������
}
//---------------------------------------------------------------------------
void TForm_Graph::PostrGrafAll( void )
{
  this->bFlagWork = this->ptrForm8BD->bFlagWork;
  if ( this->bFlagWork == false )
  {
    this->GraphFromFile(); // ������ �� �����
  }
  else
  {
    this->GrafFromBufer(); // ������ �� ������
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_Graph::CheckBox_logariphmClick(TObject *Sender)
{
  PostrGrafAll();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Graph::RadioButton_PuassonClick(TObject *Sender)
{
  PostrGrafAll();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Graph::RadioButton_inTimeClick(TObject *Sender)
{
  PostrGrafAll();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Graph::RadioButton_GaysClick(TObject *Sender)
{
  PostrGrafAll();
}
//---------------------------------------------------------------------------
bool TForm_Graph::DiaFindFile ( AnsiString * filename )
{ // �������-��������
  int SerNum, AddrBD;
  bool bTemp;
  char chFileName[250];

  if ( ptrForm8BD->Edit_ArrSerNum[siFlagGraph - 1]->Text.Length() == 0 )
  {
    ptrForm8BD->Panel_Display_Arr[siFlagGraph - 1]->Caption = "������: �� ������ �������� ����� ��!";
    return false;
  }
  try
  {
    SerNum = StrToInt( ptrForm8BD->Edit_ArrSerNum[siFlagGraph - 1]->Text );
  }
  catch ( ... )
  {
    ptrForm8BD->Panel_Display_Arr[siFlagGraph - 1]->Caption = "������: �������� ����� �� ����� �����������!";
    return false;
  }
  if ( SerNum < 0 || SerNum >999999 )
  {
    ptrForm8BD->Panel_Display_Arr[siFlagGraph - 1]->Caption = "������: �������� ����� �� ��� ���������!";
    return false;
  }
  //===
  AddrBD = ptrForm8BD->SpinEdit_AddrBDArr[siFlagGraph - 1]->Value;
  sprintf( chFileName, "SN_%.06d_Addr_%.02d.txt", SerNum, AddrBD );
  bTemp = FileExists( chFileName );
  if ( bTemp == true )
  {
    *filename = chFileName;
    ptrForm8BD->Panel_Display_Arr[siFlagGraph - 1]->Caption = "";
    return true;
  }
  else
  {
    sprintf( chFileName, "SerNum_%0.6d.txt", SerNum );
    bTemp = FileExists( chFileName );
    if ( bTemp == true )
    {
      *filename = chFileName;
      ptrForm8BD->Panel_Display_Arr[siFlagGraph - 1]->Caption = "";
      return true;
    }
    else
    {
      *filename = "NULL";
      ptrForm8BD->Panel_Display_Arr[siFlagGraph - 1]->Caption = "������: �� ������ ���������� ���� �����!";
      return false;
    }
  }
}
//---------------------------------------------------------------------------
void TForm_Graph::GraphFromFile( void )
{
  // �������� ������� (������ �� �����)
  const int MAX = 80;
  char buffer[MAX];

  int Int_3_Arr[3]; // Int_3_Arr[0] - ������� �������, ���� 1, �� ���� ��������, 0 - ���
  // Int_3_Arr[1] - ����, Int_3_Arr[2] - ����� ���������
  this->Timer_ForGraphUpdate->Enabled = false; // �� ��������� �������

  AnsiString str_report;
  if ( DiaFindFile ( & filename ) == false )
  {
    str_report = "���� \"" + filename + "\" �� ����������. ����� �� �������...";
    Form_82_Start->Memo_For_Print_Errors->Lines->Add( Form_82_Start->GetCurrentTime() + str_report );
    Kisp = 0;
    sprintf(chFileName, "��� ����� =");
    Label_srednee->Caption = "������� �������� =";
    Label_znachPoroga->Caption = "�������� ������ =";
    Label_verLoSrab->Caption = "������. ������ ������. * �-3 =";
    Label_kolichIzmereniy->Caption = "���-�� ����� (������) � ����� =";
    Label_Dispersiya->Caption = "��������� =";
    Label_koefMorozova->Caption = "����. �������� =";
    Label_Error_Svyazi->Caption = "������ ����� =";
  }
  else
  {
    str_report = "���� \"" + filename + "\" ������";
    Form_82_Start->Memo_For_Print_Errors->Lines->Add( Form_82_Start->GetCurrentTime() + str_report );
    Kisp = FormPuasson8BD->SpinEdit_Time->Value * 1000;
    sprintf(chFileName, "��� ����� = %s", filename.c_str());
    ////////////////////////////////////////////////////////////////////////
    std::fstream fs;
    fs.open(filename.c_str(), std::ios::in);
    if ( fs == 0 )
    {
      str_report = "���� \"" + filename + "\" �� �����������. ����� �� �������...";
      Form_82_Start->Memo_For_Print_Errors->Lines->Add( Form_82_Start->GetCurrentTime() + str_report );
      return;
    }
    else
    {
      str_report = "���� \"" + filename + "\" ������� ������";
      Form_82_Start->Memo_For_Print_Errors->Lines->Add(Form_82_Start->GetCurrentTime() + str_report);
    }
    countIndex = 0;
    Err_Svyaz = 0;
    while ( !fs.eof() ) // ���� �� EOF
    {
      fs.getline(buffer, MAX); // ������ ������ ������
      // ��������� ����������� ������
      ReadSchetaFromBuffer(buffer, MAX, Int_3_Arr);
      if ( (Int_3_Arr[1-1] == 1) || (Int_3_Arr[1-1] == 2) )
      {
        if ( (countIndex != 0) && (countIndex < 300000) ) // 300 000 - ������������ ������ �������
        {
          DataArray[countIndex-1] = Int_3_Arr[2-1];
        }
        countIndex++;
      }
      else if ( Int_3_Arr[1-1] == 3 )
      {
        Err_Svyaz++;
      }
    }
    //==\\Nisp = countIndex - 1; // ������ ������ �� �����������, � ��� ���������� ���������
    Nisp = countIndex;
    if ( Nisp < Kisp ) // � ����� ������ �����, ��� ������� � ���� �����
    {
      Kisp = Nisp;
    }
    else if ( Nisp > Kisp ) // � ����� ������ �����, ��� ������� � ���� �����
    {
      //Nisp = Kisp;
    }
    fs.close();
  }
  Label_FileName->Caption = chFileName;  
  PostrGraf();  
}
//---------------------------------------------------------------------------
void TForm_Graph::GrafFromBufer( void )
{
  int k; // ���������� ��������� (� ����� �������) ������ ��� ������� �� (� �������)
  int indArr;
  sprintf(chFileName, "��� ����� =");
  indArr = this->siFlagGraph-1;
  k = this->ptrForm8BD->indexSM[indArr]; // ���������� ���������
  for (int i = 0; i < k; i++)
  {
    DataArray[i] = this->ptrForm8BD->SredMas[indArr][i];
  }
  Kisp = Nisp = k;
  PostrGraf();
}
//---------------------------------------------------------------------------
double TForm_Graph::poisson(int x, float Srednee)
{
  long double b;
  long double f = 0;
  if ( x == 0 )
  {
    return exp(static_cast<double>(-1 * Srednee));
  }
  for ( int i = 1; i <= x; i++ )
  {
    f += log(static_cast<double>(i)); // log(i) - ����������� ��������
  }
  b = exp(-1 * Srednee + x * log(Srednee) - f);
  return b;
}
//---------------------------------------------------------------------------
double TForm_Graph::Gays(int x, float Disper, float Srednee)
{
  double K1;
  const double Pi = 3.1415926535;
  if ( Disper != 0 )
  {
    K1 = 1 / sqrt ( Disper * 2 * Pi );
    return K1 * exp ( -1 * ((x - Srednee) * (x - Srednee)) /(2 * Disper) );
  }
  else
  {
    return 0;
  }
}
//---------------------------------------------------------------------------
void TForm_Graph::PostrGraf( void )
{
  float Di; // ���������
  float Kr; // �������� ��������
  float PorogZn; // �����
  float SumKolLog; // ���������� ���������� ������ ������������
  float Sum;
  unsigned int KolLog = 0;
  int por = 0; // ������� �����
  int por2 = 0; // ������� ������������� �����
  int por3 = 0; // ������� ������������ �����
  AnsiString str;

  // ���������� ������ Kisp - ���������� ������ �����
  unsigned long SumZn = 0;
  for ( int i = 0; i < Kisp; i++ )
  {
    SumZn = SumZn + DataArray[i]; //����� ����������� ����
  }
  if ( SumZn == 0 ) 
  {
    Form_82_Start->Memo_For_Print_Errors->Lines->Add(Form_82_Start->GetCurrentTime() + "�������� �� ����: ��� �������� �������");
    // ������� �� ������
    this->Series1->Clear();
    this->Series2->Clear();
    this->Series3->Clear();
    this->Series4->Clear();
    this->Series5->Clear();
    this->Series6->Clear();
    return;
  }
  //������� ��������(�������� ������������� �����������)
  float SredneeZn = static_cast<float>(SumZn) / static_cast<float>( Kisp );
  // ���������� ������ ��� ������
  for ( int i = 0; i < 10000; i++)
  {
    Spec[i] = 0;
  }
  for ( int i = 0; i < Kisp; i++)
  {
    if( static_cast<int>(DataArray[i]) < 10000 )
    {
      Spec[static_cast<int>(DataArray[i])]++;
    }
  }
  MaxZn = 0; // ������������ ��������
  MaxPoisson = 0; // ������� ������������� ��������
  for ( int i = 0; i < 10000; i++)
  {
    if ( Spec[i] > MaxZn )
    {
      MaxZn = Spec[i];
    }
  }
  for ( int i = 0; i < 10000; i++ )
  {
    if ( Spec[i] > 0 )
    {
      MaxPoisson = i;
    }
  }
  if ( MaxPoisson < 9800 )
  {
    MaxPoisson += 200;
  }
  Di = 0;
  for ( int k = 0; k < Kisp; k++ )
  {
    Di += (DataArray[k] - SredneeZn) * (DataArray[k] - SredneeZn);
  }
  if ( Kisp > 1 )
  {
    Di /= ( Kisp - 1 );
  }
  else
  {
    Di = 0;
  }
  Kr = (Di - SredneeZn) / SredneeZn;
  // ������� ������������� ��������

  for ( int i = 0; i < MaxPoisson; i++ )
  {
    y[i] = poisson(i, SredneeZn);
    yy[i] = poisson(i, SredneeZn + 1.96 * Di / sqrt( Kisp ));
    Spec_Gays[i] = Gays(i, Di, SredneeZn);
    y[i] *= Kisp;
    yy[i] *= Kisp;
    Spec_Gays[i] *= Kisp;
  }
  MaxZn = 0;
  for ( int i = 0; i < MaxPoisson; i++ )
  {
    if ( y[i] > MaxZn )
    {
      MaxZn = y[i];
    }
  }
  MaxZn2 = 0;
  for ( int i = 0; i < Kisp; i++ )
  {
    if ( DataArray[i] > MaxZn2 )
    {
      MaxZn2 = DataArray[i];
    }
  }
  MinZn2 = MaxZn2;
  for ( int i = 0; i < Kisp; i++ )
  {
    if ( DataArray[i] < MinZn2 )
    {
      MinZn2 = DataArray[i];
    }
  }
  // ���������� �����
  PorogZn = MaxZn2;
  Sum = 0;
  int i;
  // �������� �� ���� � �������������
  SumKolLog = static_cast<float>( Kisp ) / 1000.0 * 999.0; //���������� ���������� ������ ������������
  float Ymin, Ymax;
  for ( i = 0; i < MaxPoisson; i++ )
  {
    if ( i >= 130 ) // �����
    {
      Ymin = y[i-1];
      Ymax = y[i];
      if ( Ymax > Ymin )
      {
        Sum += (Ymin + 0.5*(Ymax-Ymin));
      }
      else
      {
        Sum += (Ymax + 0.5*(Ymin-Ymax));
      }
    }
    else // �������
    {
      Sum += y[i];
    }
    if ( Sum >= SumKolLog )
    {
      break;
    }
  }
  PorogZn = i + 1;
  KolLog = 0;
  for ( int i = 0; i < Kisp; i++ )
  {
    if ( DataArray[i] > (unsigned int)(int)(PorogZn) )
    {
      KolLog++;
    }
  }
  por = 0; // ������� �����
  float temp = MaxZn;
  while (temp >= 10)
  {
    por++;
    temp /= 10.0;
  }
  if ( por > 1 )
  {
    por--;
  }
  por2 = 0;
  temp = MaxZn2;
  while (temp >= 10)
  {
    por2++;
    temp /= 10.0;
  }
  por3 = 0;
  temp = MinZn2;
  while (temp >= 10)
  {
    por3++;
    temp /= 10.0;
  }
  if (MinZn2 > pow(10, por3))
  {
    MinZn2 -= pow(10, por3);
  }
  // ������� �� ������
  this->Series1->Clear();
  this->Series2->Clear();
  this->Series3->Clear();
  this->Series4->Clear();
  this->Series5->Clear();
  this->Series6->Clear();

  // �������� �������
  this->Chart_Puasson_lin->BottomAxis->Minimum = 0;
  this->Chart_Puasson_lin->BottomAxis->Maximum = MaxZn2 + pow(10, por2);
  this->Chart_Puasson_lin->BottomAxis->Minimum = MinZn2;
  this->Chart_Puasson_lin->LeftAxis->Minimum = 0;
  MaxZn = 0;
  for ( int i = 0; i < 10000; i++ )
  {
    if ( Spec[i] > MaxZn )
    {
      MaxZn = Spec[i];
    }
  }
  this->Chart_Puasson_lin->LeftAxis->Maximum = MaxZn + pow(10, por);
  // ��������������� ������� �� ��� Y
  this->Chart_Puasson_log->BottomAxis->Minimum = 0;
  this->Chart_Puasson_log->BottomAxis->Maximum = MaxZn2 + pow(10, por2);
  this->Chart_Puasson_log->BottomAxis->Minimum = MinZn2;
  this->Chart_Puasson_log->LeftAxis->Minimum = 0;
  if ( MaxZn <= 100000 )
  {
    this->Chart_Puasson_log->LeftAxis->Maximum = 100000;
  }
  if ( MaxZn <= 10000 )
  {
    this->Chart_Puasson_log->LeftAxis->Maximum = 10000;
  }
  if ( MaxZn <= 1000 )
  {
    this->Chart_Puasson_log->LeftAxis->Maximum = 1000;
  }
  if ( MaxZn <= 100 )
  {
    this->Chart_Puasson_log->LeftAxis->Maximum = 100;
  }
  if ( MaxZn <= 10 )
  {
    this->Chart_Puasson_log->LeftAxis->Maximum = 10;
  }
  if ( this->RadioButton_Puasson->Checked ) // �������
  {
    if ( this->CheckBox_logariphm->Checked ) // ��������������� �������
    {
      this->Chart_Puasson_log->Visible = true;
      this->Chart_Puasson_lin->Visible = true;
      this->Series4->Clear();
      this->Series5->Clear();
      this->Series6->Clear();
      this->Chart_Puasson_log->Title->Text->Clear();
      this->Chart_Puasson_log->Title->Text->Add("������������� �� �������� (��������������� �������)");
      for ( int i = 0; i < MaxPoisson-100; i++ )
      {
        this->Series4->AddXY(i, y[i], "", clRed); // ������������� ��������
      }
      for ( int i = 0; i < MaxPoisson-100; i++ )
      {
        this->Series5->AddXY(i, Spec[i], "", clBlack); // ������ �����������
      }
      for ( int i = 0; i < MaxPoisson-100; i++ )
      {
        this->Series6->AddXY(i, yy[i], "", clGreen); // ������ �����������
      }
    }
    else if ( this->CheckBox_logariphm->Checked == false ) // �������� �������
    {
      this->Chart_Puasson_log->Visible = false;
      this->Chart_Puasson_lin->Visible = true;
      this->Chart_Puasson_lin->Title->Text->Clear();
      this->Chart_Puasson_lin->Title->Text->Add("������������� �� �������� (�������� �������)");
      this->Series1->Clear();
      this->Series2->Clear();
      this->Series3->Clear();
      for ( int i = 0; i < MaxPoisson-100; i++ )
      {
        this->Series1->AddXY(i, y[i], "", clRed); // ������������� ��������
      }
      for ( int i = 0; i < MaxPoisson-100; i++ )
      {
        this->Series2->AddXY(i, Spec[i], "", clBlack); // ������ �����������
      }
      for ( int i = 0; i < MaxPoisson-100; i++ )
      {
        this->Series3->AddXY(i, yy[i], "", clGreen);
      }
    }
  }
  else if ( this->RadioButton_inTime->Checked == true ) // �������� ������ - ��������� �� �������
  {
    if ( this->CheckBox_logariphm->Checked ) // ��������������� �������
    {
      this->Chart_Puasson_log->Visible = true;
      this->Chart_Puasson_lin->Visible = true;
      this->Series4->Clear();
      this->Series5->Clear();
      this->Series6->Clear();
      this->Chart_Puasson_log->Title->Text->Clear();
      this->Chart_Puasson_log->Title->Text->Add("������ ����� �� ������� (��������������� �������)");
      this->Chart_Puasson_log->BottomAxis->Minimum = 0;
      this->Chart_Puasson_log->BottomAxis->Maximum = Kisp;
      this->Chart_Puasson_log->LeftAxis->Minimum = 0;
      unsigned int MaxZn3 = 0;
      for ( int i = 0; i < Kisp; i++ )
      {
        if ( DataArray[i] > MaxZn3 )
        {
          MaxZn3 = DataArray[i];
        }
      }
      if ( MaxZn3 <= 100000 )
      {
        this->Chart_Puasson_log->LeftAxis->Maximum = 100000;
      }
      if ( MaxZn3 <= 10000 )
      {
        this->Chart_Puasson_log->LeftAxis->Maximum = 10000;
      }
      if ( MaxZn3 <= 1000 )
      {
        this->Chart_Puasson_log->LeftAxis->Maximum = 1000;
      }
      if ( MaxZn3 <= 100 )
      {
        this->Chart_Puasson_log->LeftAxis->Maximum = 100;
      }
      if ( MaxZn3 <= 10 )
      {
        this->Chart_Puasson_log->LeftAxis->Maximum = 10;
      }
      for ( int i = 0; i < Kisp; i++ )
      {
        this->Series4->AddXY(i, DataArray[i], "", clBlack );
      }
    }
    else if ( this->CheckBox_logariphm->Checked == 0 ) // �������� �������
    {
      this->Chart_Puasson_log->Visible = false;
      this->Chart_Puasson_lin->Visible = true;
      this->Series1->Clear();
      this->Series2->Clear();
      this->Series3->Clear();
      this->Chart_Puasson_lin->Title->Text->Clear();
      this->Chart_Puasson_lin->Title->Text->Add("������ ����� �� ������� (�������� �������)");
      this->Chart_Puasson_lin->BottomAxis->Minimum = 0;
      this->Chart_Puasson_lin->BottomAxis->Maximum = Kisp;
      this->Chart_Puasson_lin->LeftAxis->Minimum = 0;
      unsigned int MaxZn3 = 0;
      for ( int i = 0; i < Kisp; i++ )
      {
        if ( DataArray[i] > MaxZn3 )
        {
          MaxZn3 = DataArray[i];
        }
      }
      this->Chart_Puasson_lin->LeftAxis->Maximum = MaxZn3 + 10;
      for ( int i = 0; i < Kisp; i++ )
      {
        this->Series1->AddXY(i, DataArray[i], "", clBlack);
      }
    }
  }
  else if ( this->RadioButton_Gays->Checked ) // "����������" �������������
  {
    if ( this->CheckBox_logariphm->Checked ) // ��������������� �������
    {
      this->Chart_Puasson_log->Visible = true;
      this->Chart_Puasson_lin->Visible = true;
      this->Series4->Clear();
      this->Series5->Clear();
      this->Series6->Clear();
      this->Chart_Puasson_log->Title->Text->Clear();
      this->Chart_Puasson_log->Title->Text->Add("������������� �� ����� (��������������� �������)");
      for ( int i = 0; i < MaxPoisson; i++ )
      {
        this->Series4->AddXY(i, Spec_Gays[i], "", clRed); // ������������� �����
      }
      for ( int i = 0; i < MaxPoisson; i++ )
      {
        this->Series5->AddXY(i, Spec[i], "", clBlack); // ������ �����������
      }
    }
    else if ( this->CheckBox_logariphm->Checked == false ) // �������� �������
    {
      this->Chart_Puasson_log->Visible = false;
      this->Chart_Puasson_lin->Visible = true;
      this->Chart_Puasson_lin->Title->Text->Clear();
      this->Chart_Puasson_lin->Title->Text->Add("������������� �� ����� (�������� �������)");
      this->Series1->Clear();
      this->Series2->Clear();
      this->Series3->Clear();
      for ( int i = 0; i < MaxPoisson; i++ )
      {
        this->Series1->AddXY(i, Spec_Gays[i], "", clRed); // ������������� �����
      }
      for ( int i = 0; i < MaxPoisson; i++ )
      {
        this->Series2->AddXY(i, Spec[i], "", clBlack); // ������ �����������
      }
    }
  }
  str = AnsiString("������� �������� = ") + FormatFloat("0.00", SredneeZn);
  this->Label_srednee->Caption = str;
  str = AnsiString("�������� ������ = ") + FormatFloat("0.00", PorogZn);
  this->Label_znachPoroga->Caption = str;
  str = AnsiString("������. ������ ������. * �-3 = ") +
  FormatFloat("0.0000", static_cast<float>(KolLog)/static_cast<float>( Kisp ));
  this->Label_verLoSrab->Caption = str;
  str = AnsiString("���-�� ����� (������) � ����� = ") + IntToStr( Nisp );
  this->Label_kolichIzmereniy->Caption = str;
  str = AnsiString("��������� = ") + FormatFloat("0.00", Di);
  this->Label_Dispersiya->Caption = str;
  str = AnsiString("����. �������� = ") + FormatFloat("0.0000", Kr);
  this->Label_koefMorozova->Caption = str;
  str = AnsiString("������ ����� = ") + IntToStr(Err_Svyaz);
  this->Label_Error_Svyazi->Caption = str;
  this->Label_FileName->Caption = chFileName;
}
//---------------------------------------------------------------------------
void __fastcall TForm_Graph::Button_UpdateGraphClick(TObject *Sender)
{
  PostrGrafAll();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Graph::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  bFlagOtkrytoyFormy = false; // = true --- ����� �������, ����� ����� ��������� ������
}
//---------------------------------------------------------------------------
void __fastcall TForm_Graph::FormShow(TObject *Sender)
{
#ifdef _DIA_OBEDINENIE_
  if( FormDispet != 0 )
  {
    FormDispet->DiaGetWinHandle( this->Handle );  
  }
#endif  
  bFlagOtkrytoyFormy = true; // = true --- ����� �������, ����� ����� ��������� ������
}
//---------------------------------------------------------------------------
void __fastcall TForm_Graph::Timer_ForGraphUpdateTimer(TObject *Sender)
{
  if ( this->bFlagOtkrytoyFormy == true )
  {
    this->PostrGrafAll();
  }
}
//---------------------------------------------------------------------------
