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
  bFlagWork = false; // Флаг режима измерения включён/выключен
}
//---------------------------------------------------------------------------
void TForm_Graph::PostrGrafAll( void )
{
  this->bFlagWork = this->ptrForm8BD->bFlagWork;
  if ( this->bFlagWork == false )
  {
    this->GraphFromFile(); // График из файла
  }
  else
  {
    this->GrafFromBufer(); // График из буфера
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
{ // Функция-заглушка
  int SerNum, AddrBD;
  bool bTemp;
  char chFileName[250];

  if ( ptrForm8BD->Edit_ArrSerNum[siFlagGraph - 1]->Text.Length() == 0 )
  {
    ptrForm8BD->Panel_Display_Arr[siFlagGraph - 1]->Caption = "Ошибка: не найден серийный номер БД!";
    return false;
  }
  try
  {
    SerNum = StrToInt( ptrForm8BD->Edit_ArrSerNum[siFlagGraph - 1]->Text );
  }
  catch ( ... )
  {
    ptrForm8BD->Panel_Display_Arr[siFlagGraph - 1]->Caption = "Ошибка: серийный номер БД введён неправильно!";
    return false;
  }
  if ( SerNum < 0 || SerNum >999999 )
  {
    ptrForm8BD->Panel_Display_Arr[siFlagGraph - 1]->Caption = "Ошибка: серийный номер БД вне диапазона!";
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
      ptrForm8BD->Panel_Display_Arr[siFlagGraph - 1]->Caption = "Ошибка: не найден подходящий файл логов!";
      return false;
    }
  }
}
//---------------------------------------------------------------------------
void TForm_Graph::GraphFromFile( void )
{
  // Просмотр графика (данные из файла)
  const int MAX = 80;
  char buffer[MAX];

  int Int_3_Arr[3]; // Int_3_Arr[0] - признак функции, если 1, то счёт прочитан, 0 - нет
  // Int_3_Arr[1] - счёт, Int_3_Arr[2] - слово состояния
  this->Timer_ForGraphUpdate->Enabled = false; // Не обновляет графики

  AnsiString str_report;
  if ( DiaFindFile ( & filename ) == false )
  {
    str_report = "Файл \"" + filename + "\" не существует. Выход из функции...";
    Form_82_Start->Memo_For_Print_Errors->Lines->Add( Form_82_Start->GetCurrentTime() + str_report );
    Kisp = 0;
    sprintf(chFileName, "Имя файла =");
    Label_srednee->Caption = "Среднее значение =";
    Label_znachPoroga->Caption = "Значение порога =";
    Label_verLoSrab->Caption = "Вероят. ложных срабат. * Е-3 =";
    Label_kolichIzmereniy->Caption = "Кол-во строк (счетов) в файле =";
    Label_Dispersiya->Caption = "Дисперсия =";
    Label_koefMorozova->Caption = "Коэф. Морозова =";
    Label_Error_Svyazi->Caption = "Ошибок связи =";
  }
  else
  {
    str_report = "Файл \"" + filename + "\" найден";
    Form_82_Start->Memo_For_Print_Errors->Lines->Add( Form_82_Start->GetCurrentTime() + str_report );
    Kisp = FormPuasson8BD->SpinEdit_Time->Value * 1000;
    sprintf(chFileName, "Имя файла = %s", filename.c_str());
    ////////////////////////////////////////////////////////////////////////
    std::fstream fs;
    fs.open(filename.c_str(), std::ios::in);
    if ( fs == 0 )
    {
      str_report = "Файл \"" + filename + "\" не открывается. Выход из функции...";
      Form_82_Start->Memo_For_Print_Errors->Lines->Add( Form_82_Start->GetCurrentTime() + str_report );
      return;
    }
    else
    {
      str_report = "Файл \"" + filename + "\" успешно открыт";
      Form_82_Start->Memo_For_Print_Errors->Lines->Add(Form_82_Start->GetCurrentTime() + str_report);
    }
    countIndex = 0;
    Err_Svyaz = 0;
    while ( !fs.eof() ) // цикл до EOF
    {
      fs.getline(buffer, MAX); // читать строку текста
      // обработка прочитанной строки
      ReadSchetaFromBuffer(buffer, MAX, Int_3_Arr);
      if ( (Int_3_Arr[1-1] == 1) || (Int_3_Arr[1-1] == 2) )
      {
        if ( (countIndex != 0) && (countIndex < 300000) ) // 300 000 - максимальный размер массива
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
    //==\\Nisp = countIndex - 1; // первая строка не считывается, в ней количество измерений
    Nisp = countIndex;
    if ( Nisp < Kisp ) // В файле меньше точек, чем указано в окне ввода
    {
      Kisp = Nisp;
    }
    else if ( Nisp > Kisp ) // В файле больше точек, чем указано в окне ввода
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
  int k; // Количество измереных (к этому времени) счетов для данного БД (и графика)
  int indArr;
  sprintf(chFileName, "Имя файла =");
  indArr = this->siFlagGraph-1;
  k = this->ptrForm8BD->indexSM[indArr]; // Количество измерений
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
    f += log(static_cast<double>(i)); // log(i) - натуральный логарифм
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
  float Di; // Дисперсия
  float Kr; // Критерий Морозова
  float PorogZn; // Порог
  float SumKolLog; // Количество допустимых ложных срабатываний
  float Sum;
  unsigned int KolLog = 0;
  int por = 0; // порядок числа
  int por2 = 0; // порядок максимального числа
  int por3 = 0; // порядок минимального числа
  AnsiString str;

  // Обработаем данные Kisp - количество снятых точек
  unsigned long SumZn = 0;
  for ( int i = 0; i < Kisp; i++ )
  {
    SumZn = SumZn + DataArray[i]; //сумма полученного ряда
  }
  if ( SumZn == 0 ) 
  {
    Form_82_Start->Memo_For_Print_Errors->Lines->Add(Form_82_Start->GetCurrentTime() + "Внимание на файл: все значения нулевые");
    // Выведем на график
    this->Series1->Clear();
    this->Series2->Clear();
    this->Series3->Clear();
    this->Series4->Clear();
    this->Series5->Clear();
    this->Series6->Clear();
    return;
  }
  //среднее значение(середина распределения гистограммы)
  float SredneeZn = static_cast<float>(SumZn) / static_cast<float>( Kisp );
  // Подготовим данные для вывода
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
  MaxZn = 0; // максимальное значение
  MaxPoisson = 0; // позиция максимального значения
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
  // Получим распределения Пуассона

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
  // рассчитаем порог
  PorogZn = MaxZn2;
  Sum = 0;
  int i;
  // движемся от нуля к бесконечности
  SumKolLog = static_cast<float>( Kisp ) / 1000.0 * 999.0; //Количество допустимых ложных срабатываний
  float Ymin, Ymax;
  for ( i = 0; i < MaxPoisson; i++ )
  {
    if ( i >= 130 ) // Гаусс
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
    else // Пуассон
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
  por = 0; // порядок числа
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
  // Выведем на график
  this->Series1->Clear();
  this->Series2->Clear();
  this->Series3->Clear();
  this->Series4->Clear();
  this->Series5->Clear();
  this->Series6->Clear();

  // Линейный масштаб
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
  // Логарифмический масштаб по оси Y
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
  if ( this->RadioButton_Puasson->Checked ) // Пуассон
  {
    if ( this->CheckBox_logariphm->Checked ) // Логарифмический масштаб
    {
      this->Chart_Puasson_log->Visible = true;
      this->Chart_Puasson_lin->Visible = true;
      this->Series4->Clear();
      this->Series5->Clear();
      this->Series6->Clear();
      this->Chart_Puasson_log->Title->Text->Clear();
      this->Chart_Puasson_log->Title->Text->Add("Распределение по Пуассону (логарифмический масштаб)");
      for ( int i = 0; i < MaxPoisson-100; i++ )
      {
        this->Series4->AddXY(i, y[i], "", clRed); // Распределение Пуассона
      }
      for ( int i = 0; i < MaxPoisson-100; i++ )
      {
        this->Series5->AddXY(i, Spec[i], "", clBlack); // строим гистограмму
      }
      for ( int i = 0; i < MaxPoisson-100; i++ )
      {
        this->Series6->AddXY(i, yy[i], "", clGreen); // строим гистограмму
      }
    }
    else if ( this->CheckBox_logariphm->Checked == false ) // Линейный масштаб
    {
      this->Chart_Puasson_log->Visible = false;
      this->Chart_Puasson_lin->Visible = true;
      this->Chart_Puasson_lin->Title->Text->Clear();
      this->Chart_Puasson_lin->Title->Text->Add("Распределение по Пуассону (линейный масштаб)");
      this->Series1->Clear();
      this->Series2->Clear();
      this->Series3->Clear();
      for ( int i = 0; i < MaxPoisson-100; i++ )
      {
        this->Series1->AddXY(i, y[i], "", clRed); // Распределение Пуассона
      }
      for ( int i = 0; i < MaxPoisson-100; i++ )
      {
        this->Series2->AddXY(i, Spec[i], "", clBlack); // строим гистограмму
      }
      for ( int i = 0; i < MaxPoisson-100; i++ )
      {
        this->Series3->AddXY(i, yy[i], "", clGreen);
      }
    }
  }
  else if ( this->RadioButton_inTime->Checked == true ) // Построим график - изменение от времени
  {
    if ( this->CheckBox_logariphm->Checked ) // Логарифмический масштаб
    {
      this->Chart_Puasson_log->Visible = true;
      this->Chart_Puasson_lin->Visible = true;
      this->Series4->Clear();
      this->Series5->Clear();
      this->Series6->Clear();
      this->Chart_Puasson_log->Title->Text->Clear();
      this->Chart_Puasson_log->Title->Text->Add("График счёта от времени (логарифмический масштаб)");
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
    else if ( this->CheckBox_logariphm->Checked == 0 ) // Линейный масштаб
    {
      this->Chart_Puasson_log->Visible = false;
      this->Chart_Puasson_lin->Visible = true;
      this->Series1->Clear();
      this->Series2->Clear();
      this->Series3->Clear();
      this->Chart_Puasson_lin->Title->Text->Clear();
      this->Chart_Puasson_lin->Title->Text->Add("График счёта от времени (линейный масштаб)");
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
  else if ( this->RadioButton_Gays->Checked ) // "Нормальное" распределение
  {
    if ( this->CheckBox_logariphm->Checked ) // Логарифмический масштаб
    {
      this->Chart_Puasson_log->Visible = true;
      this->Chart_Puasson_lin->Visible = true;
      this->Series4->Clear();
      this->Series5->Clear();
      this->Series6->Clear();
      this->Chart_Puasson_log->Title->Text->Clear();
      this->Chart_Puasson_log->Title->Text->Add("Распределение по Гаусу (логарифмический масштаб)");
      for ( int i = 0; i < MaxPoisson; i++ )
      {
        this->Series4->AddXY(i, Spec_Gays[i], "", clRed); // Распределение Гауса
      }
      for ( int i = 0; i < MaxPoisson; i++ )
      {
        this->Series5->AddXY(i, Spec[i], "", clBlack); // строим гистограмму
      }
    }
    else if ( this->CheckBox_logariphm->Checked == false ) // Линейный масштаб
    {
      this->Chart_Puasson_log->Visible = false;
      this->Chart_Puasson_lin->Visible = true;
      this->Chart_Puasson_lin->Title->Text->Clear();
      this->Chart_Puasson_lin->Title->Text->Add("Распределение по Гаусу (линейный масштаб)");
      this->Series1->Clear();
      this->Series2->Clear();
      this->Series3->Clear();
      for ( int i = 0; i < MaxPoisson; i++ )
      {
        this->Series1->AddXY(i, Spec_Gays[i], "", clRed); // Распределение Гауса
      }
      for ( int i = 0; i < MaxPoisson; i++ )
      {
        this->Series2->AddXY(i, Spec[i], "", clBlack); // строим гистограмму
      }
    }
  }
  str = AnsiString("Среднее значение = ") + FormatFloat("0.00", SredneeZn);
  this->Label_srednee->Caption = str;
  str = AnsiString("Значение порога = ") + FormatFloat("0.00", PorogZn);
  this->Label_znachPoroga->Caption = str;
  str = AnsiString("Вероят. ложных срабат. * Е-3 = ") +
  FormatFloat("0.0000", static_cast<float>(KolLog)/static_cast<float>( Kisp ));
  this->Label_verLoSrab->Caption = str;
  str = AnsiString("Кол-во строк (счетов) в файле = ") + IntToStr( Nisp );
  this->Label_kolichIzmereniy->Caption = str;
  str = AnsiString("Дисперсия = ") + FormatFloat("0.00", Di);
  this->Label_Dispersiya->Caption = str;
  str = AnsiString("Коэф. Морозова = ") + FormatFloat("0.0000", Kr);
  this->Label_koefMorozova->Caption = str;
  str = AnsiString("Ошибок связи = ") + IntToStr(Err_Svyaz);
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
  bFlagOtkrytoyFormy = false; // = true --- Форма открыта, имеет смысл обновлять график
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
  bFlagOtkrytoyFormy = true; // = true --- Форма открыта, имеет смысл обновлять график
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
