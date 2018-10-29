//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include <math.h>
#include <stdio.h>
#include <Inifiles.hpp>
//---------------------------------------------------------------------------
#include "Unit_82_Form_Puasson.h"
#include "Unit_82_Form_Start.h"
#include "Unit_82_Priklad_Funk.h"

#ifdef _DIA_OBEDINENIE_
  #include "Unit_FormDispet.h"
#endif
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm_Puasson *Form_Puasson;
//---------------------------------------------------------------------------
bool Work = false;
bool WorkCancel = false;
extern const char * IniFileName;
extern bool flagPort;
//---------------------------------------------------------------------------
#define NMAS 300000
float SredMas[NMAS];
//---------------------------------------------------------------------------
__fastcall TForm_Puasson::TForm_Puasson(TComponent* Owner)
        : TForm(Owner)
{
  put = "C:\\TCPM\\BD82";
  // DataArray = 0; // пока не выделена память под массив
  MaxZn = 0; // максимальное значение
  MaxPoisson = 0; // позиция максимального значения
  Dig << ' ' << ',' << '+' << '-' << '.'
      << '0' << '1' << '2' << '3' << '4'
      << '5' << '6' << '7' << '8' << '9'
      << 'E' << 'e'; // Заполнение множества
  // Получим размер формы из INI-файла
  TIniFile * IniFile = new TIniFile(IniFileName);
  try
  {
    this->Width = IniFile->ReadInteger("Form Puasson Settings", "FormPuassonWidth", 537);
    this->Height = IniFile->ReadInteger("Form Puasson Settings", "FormPuassonHeight", 372);
    this->Left =  IniFile->ReadInteger("Form Puasson Settings", "FormPuassonLeft", 100);
    this->Top = IniFile->ReadInteger("Form Puasson Settings", "FormPuassonTop", 100);
    this->Edit_fileName->Text = IniFile->ReadString("Form Puasson Settings", "FormPuassonEdit_fileName", "poissonBD82.txt");
    this->SpinEdit_kolichestvo->Text = IniFile->ReadString("Form Puasson Settings", "FormPuassonSpinEdit_kolichestvo", "300000");
    delete IniFile;
  }
  catch(...)
  {
    delete IniFile;
  }
  Button_stop->Enabled = false;
  FlagWork = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm_Puasson::FormShow(TObject *Sender)
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
void __fastcall TForm_Puasson::FormHide(TObject *Sender)
{
  Form_82_Start->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Puasson::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Work = false;
  Form_82_Start->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Puasson::Button_startClick(TObject *Sender)
{
  bool uspeh; // флаг успешного завершения испытания == true
  uspeh = true;
  // Кнопка "Начали"
  Button_stop->Enabled = true;
  Button_exit->Enabled = false;
  Form_Graph->CheckBox_logariphm->Checked = false; // масштаб линейный

  for ( int j = 1; j <= SpinEdit_kolichestvo->Text.Length(); j++ )
  {
    if( !Dig.Contains(SpinEdit_kolichestvo->Text[j]) )
    {
      Application->MessageBox("Вы ввели не цифровые символы",
          "Кол-во испытаний", MB_ICONSTOP);
      Button_stop->Enabled = false;
      Button_exit->Enabled = true;      
      return;
    }
  } // end for

  str = SpinEdit_kolichestvo->Text;
  if ( str.AnsiPos(".") || str.AnsiPos(",") || str.AnsiPos("E") || str.AnsiPos("e") )
  {
    Application->MessageBox("Число должно быть целым",
        "Кол-во испытаний", MB_ICONSTOP);
    Button_stop->Enabled = false;
    Button_exit->Enabled = true;
    return;
  }  

  Kisp = StrToInt(str); //Количество испытаний
  if ( Kisp > NMAS )
  {
    Application->MessageBox("Число должно быть <= 300 000",
        "Кол-во испытаний", MB_ICONSTOP);
    Button_stop->Enabled = false;
    Button_exit->Enabled = true;      
    return;
  }
  CreateDir(put);
  filename = AnsiString(put) + AnsiString("\\") + AnsiString(Edit_fileName->Text);
  if ( FileExists(filename) )
  {
    AnsiString filename2 = "Файл " + filename + " уже существует";
    if ( Application->MessageBox ( filename2.c_str(), "Перезаписать?", MB_YESNO) != IDYES )
    {
      Button_stop->Enabled = false;
      Button_exit->Enabled = true;
      return;
    }
  }
  Work = true;
  WorkCancel = true;
  FlagWork = true;
  StatusBar->Panels->Items[0]->Text = "Номер испытания";
  Button_start->Enabled = false;
  //******************************************************************************
  Nisp = 1;
  DWORD error;
  AnsiString StrError;
  long time1, time2;
  unsigned char ShetGotov;
  unsigned int Shet;

  // Открыть ком порт

  if ( Form_82_Start->RSConnect( Form_82_Start->ComboBox_NomComPort->Text.c_str() ) != 0 )
  {
    // Сообщение об ошибке
    Button_stop->Enabled = false;
    Button_exit->Enabled = true;
    Application->MessageBox("Испытание ПРЕРВАННО из-за ошибки открытия COM-порта", "Внимание!", MB_ICONINFORMATION);
    return;
  }

  for ( ; ; )
  {
    do // до тех пор пока не будет установлен флаг ГОТОВНОСТИ СЧЕТА
    {
      //err = Prot->GetSSP(PSW) //GetSSP(&MainForm->PSW); // опрашиваем слово состояние программы БД
      if ( Prot->GetSSP(&PSW) != 0)
      {
        Application->MessageBox("Испытание ПРЕРВАННО из-за ошибки связи, при попытке прочитать PSW", "Внимание!", MB_ICONINFORMATION);
        uspeh = false; // Не выводить сообщение об успешном завершении испытания
        goto exit_metka;
      }
    } while ( ( PSW & 0x01 ) != 0x01 ); // end do ... while

    if ( Prot->GetCountImp(&Shet) != 0 )
    {
      Application->MessageBox("Испытание ПРЕРВАННО из-за ошибки связи, при попытке прочитать СЧЁТ", "Внимание!", MB_ICONINFORMATION);
      uspeh = false; // Не выводить сообщение об успешном завершении испытания
      goto exit_metka;
    }

    this->StatusBar->Panels->Items[1]->Text = IntToStr(Nisp);
    Application->ProcessMessages();
    SredMas[Nisp-1] = Shet;

    Edit_Znachenie->Text = IntToStr((int)SredMas[Nisp-1]);
    Application->ProcessMessages(); // интенсивность 1
    if( Nisp > 2 )
    {
      Sum = 0;
      for ( int k = 0; k < Nisp; k++ )
      {
        Sum = Sum + SredMas[k];
      }
      Sum = Sum / Nisp; // среднее значение
      Disp = 0;
      for ( int k = 0; k < Nisp; k++ )
      {
        Disp = Disp + (SredMas[k] - Sum) * (SredMas[k]-Sum);
      }
      Disp = Disp / (Nisp-1);
      if ( Sum != 0 )
      {
        Krit = ( Disp - Sum ) / Sum; // Критерий Морозова
      }

      Edit_Srednee->Text = FormatFloat("0.00", Sum);
      Application->ProcessMessages();

      Edit_dispersiya->Text = FormatFloat("0.00", Disp);
      Application->ProcessMessages();

      Edit_koeph->Text = FormatFloat("0.00", Krit);
      Application->ProcessMessages();
    } // end if ( Nisp > 2 )

    if ( Nisp == Kisp )
    {
      break;
    }
    Nisp++;    
    Application->ProcessMessages();
    if( !WorkCancel )
    {
      break;
    }
  }
exit_metka:

  if ( Form_82_Start->RSDisConnect() != 0 )
  {
    // Сообщение об ошибке
    Button_stop->Enabled = false;
    Button_exit->Enabled = true;
    Application->MessageBox("Ошибки закрытия COM-порта", "Внимание!", MB_ICONINFORMATION);
  }
  Work = false;
  FlagWork = false; // false - Строить график из файла, true - из буфера
  Application->ProcessMessages();
  Zapis(); // результаты испытания - в файл
  Application->ProcessMessages();
  Button_start->Enabled = true;
  Application->ProcessMessages();
  StatusBar->Panels->Items[0]->Text = "";
  Application->ProcessMessages();
  StatusBar->Panels->Items[1]->Text = "";
  Application->ProcessMessages();
  if ( uspeh == true )
  {
    Application->MessageBox("Испытание закончено", "Внимание!", MB_ICONINFORMATION);
  }
  Button_stop->Enabled = false;
  Button_exit->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm_Puasson::Button_exitClick(TObject *Sender)
{
  // Выход (закрытие формы)
  StatusBar->Panels->Items[0]->Text = "";
  StatusBar->Panels->Items[1]->Text = "";
  Button_exit->Enabled = true;

  // Запишем размер формы в INI-файл
  TIniFile * IniFile = new TIniFile(IniFileName);
  try
  {
    IniFile->WriteInteger("Form Puasson Settings", "FormPuassonWidth", this->Width);
    IniFile->WriteInteger("Form Puasson Settings", "FormPuassonHeight", this->Height);
    IniFile->WriteInteger("Form Puasson Settings", "FormPuassonLeft", this->Left);
    IniFile->WriteInteger("Form Puasson Settings", "FormPuassonTop", this->Top);
    IniFile->WriteString("Form Puasson Settings", "FormPuassonEdit_fileName", this->Edit_fileName->Text);
    IniFile->WriteString("Form Puasson Settings", "FormPuassonSpinEdit_kolichestvo", this->SpinEdit_kolichestvo->Text);
    delete IniFile;
  }
  catch(...)
  {
    delete IniFile;
  }
  WorkCancel = false;
  if ( KodVxod )
  {
    Work = false;
    flagPort = false;
  }
  Form_82_Start->Show();
  Form_Puasson->Hide();
  Form_Graph->Hide();        
}
//---------------------------------------------------------------------------

void __fastcall TForm_Puasson::Button_graphClick(TObject *Sender)
{
  Kisp = StrToInt( SpinEdit_kolichestvo->Text );
  if ( FlagWork == false )
  {
    Graph(); // График из файла
  }
  else
  {
    GraphWork(); // График из буфера
  }
}
//---------------------------------------------------------------------------
void TForm_Puasson::GraphWork( void )
{
  for (int i = 0; i < Nisp; i++)
  {
    DataArray[i] = SredMas[i];
  }
  PostrGraf();
}
//---------------------------------------------------------------------------
void TForm_Puasson::Graph()
{
  // Просмотр графика (данные из файла)
  const int MAX = 80;
  char buffer[MAX];


  int Int_3_Arr[3]; // Int_3_Arr[0] - признак функции, если 1, то счёт прочитан, 0 - нет
  // Int_3_Arr[1] - счёт, Int_3_Arr[2] - слово состояния

  AnsiString str_report;
  filename = put + AnsiString("\\") + AnsiString(Edit_fileName->Text);
  Kisp = StrToInt ( SpinEdit_kolichestvo->Text );
  if ( FileExists( filename ) == false )
  {
    str_report = "Файл \"" + filename + "\" не существует. Выход из функции...";
    Form_82_Start->Memo_For_Print_Errors->Lines->Add(str_report);
    return;
  }
  else
  {
    str_report = "Файл \"" + filename + "\" найден";
    Form_82_Start->Memo_For_Print_Errors->Lines->Add(str_report);
  }
  ////////////////////////////////////////////////////////////////////////
  std::fstream fs;
  fs.open(filename.c_str(), std::ios::in);
  if ( fs == 0 )
  {
    str_report = "Файл \"" + filename + "\" не открывается. Выход из функции...";
    Form_82_Start->Memo_For_Print_Errors->Lines->Add(str_report);
    return;
  }
  else
  {
    str_report = "Файл \"" + filename + "\" успешно открыт";
    Form_82_Start->Memo_For_Print_Errors->Lines->Add(str_report);
  }
  count = 0;
  Err_Svyaz = 0;
  while ( !fs.eof() ) // цикл до EOF
  {
    fs.getline(buffer, MAX); // читать строку текста
    // обработка прочитанной строки
    ReadSchetaFromBuffer(buffer, MAX, Int_3_Arr);
    if ( (Int_3_Arr[1-1] == 1) || (Int_3_Arr[1-1] == 2) )
    {
      if (count != 0 && count < 300000) // 300 000 - максимальный размер массива
      {
        DataArray[count-1] = Int_3_Arr[2-1];
      }
      count++;
    }
    if ( Int_3_Arr[1-1] == 3 )
    {
      Err_Svyaz++;
    }
  }

  Nisp = count - 1; // первая строка не считывается, в ней количество измерений
  if ( Nisp < Kisp ) // В файле меньше точек, чем указано в окне ввода
  {
    Kisp = Nisp;
    SpinEdit_kolichestvo->Text = IntToStr(Kisp);
  }
  Label_Chislo_Izmereniy->Caption = AnsiString("Количество измерений в файле = ") + IntToStr(Nisp);

  fs.close();
  PostrGraf();
}
//---------------------------------------------------------------------------
void TForm_Puasson::PostrGraf()
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

  // Обработаем данные Kisp - количество снятых точек
  unsigned long SumZn = 0;
  for ( int i = 0; i < Nisp; i++ )
  {
    SumZn = SumZn + DataArray[i]; //сумма полученного ряда
  }
  if ( SumZn == 0 ) 
  {
    Form_82_Start->Memo_For_Print_Errors->Lines->Add("Внимание на файл: все значения нулевые");
    return;
  }
  //среднее значение(середина распределения гистограммы)
  float SredneeZn = static_cast<float>( SumZn ) / static_cast<float>( Nisp );
  // Подготовим данные для вывода
  for ( int i = 0; i < 10000; i++)
  {
    Spec[i] = 0;
  }
  for ( int i = 0; i < Nisp; i++)
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
  for ( int k = 0; k < Nisp; k++ )
  {
    Di += (DataArray[k] - SredneeZn) * (DataArray[k] - SredneeZn);
  }
  if ( Nisp > 1 )
  {
    Di /= ( Nisp - 1 );
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
    yy[i] = poisson(i, SredneeZn + 1.96 * Di / sqrt(/*Kisp*/Nisp));
    Spec_Gays[i] = Gays(i, Di, SredneeZn);
    y[i] *= Nisp;
    yy[i] *= Nisp;
    Spec_Gays[i] *= Nisp;
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
  for ( int i = 0; i < Nisp; i++ )
  {
    if ( DataArray[i] > MaxZn2 )
    {
      MaxZn2 = DataArray[i];
    }
  }
  MinZn2 = MaxZn2;
  for ( int i = 0; i < Nisp; i++ )
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
  SumKolLog = static_cast<float>(Nisp) / 1000.0 * 999.0; //Количество допустимых ложных срабатываний
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
  for ( int i = 0; i < Nisp; i++ )
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
  Form_Graph->Series1->Clear();
  Form_Graph->Series2->Clear();
  Form_Graph->Series3->Clear();
  Form_Graph->Series4->Clear();
  Form_Graph->Series5->Clear();
  Form_Graph->Series6->Clear();

  // Линейный масштаб
  Form_Graph->Chart_Puasson_lin->BottomAxis->Minimum = 0;
  Form_Graph->Chart_Puasson_lin->BottomAxis->Maximum = MaxZn2 + pow(10, por2);
  Form_Graph->Chart_Puasson_lin->BottomAxis->Minimum = MinZn2;

  Form_Graph->Chart_Puasson_lin->LeftAxis->Minimum = 0;
  MaxZn = 0;
  for ( int i = 0; i < 10000; i++ )
  {
    if ( Spec[i] > MaxZn )
    {
      MaxZn = Spec[i];
    }
  }
  Form_Graph->Chart_Puasson_lin->LeftAxis->Maximum = MaxZn + pow(10, por);

  // Логарифмический масштаб по оси Y
  Form_Graph->Chart_Puasson_log->BottomAxis->Minimum = 0;
  Form_Graph->Chart_Puasson_log->BottomAxis->Maximum = MaxZn2 + pow(10, por2);
  Form_Graph->Chart_Puasson_log->BottomAxis->Minimum = MinZn2;

  Form_Graph->Chart_Puasson_log->LeftAxis->Minimum = 0;
  if ( MaxZn <= 100000 )
  {
    Form_Graph->Chart_Puasson_log->LeftAxis->Maximum = 100000;
  }
  if ( MaxZn <= 10000 )
  {
    Form_Graph->Chart_Puasson_log->LeftAxis->Maximum = 10000;
  }
  if ( MaxZn <= 1000 )
  {
    Form_Graph->Chart_Puasson_log->LeftAxis->Maximum = 1000;
  }
  if ( MaxZn <= 100 )
  {
    Form_Graph->Chart_Puasson_log->LeftAxis->Maximum = 100;
  }
  if ( MaxZn <= 10 )
  {
    Form_Graph->Chart_Puasson_log->LeftAxis->Maximum = 10;
  }
  if ( Form_Graph->RadioButton_Puasson->Checked ) // Пуассон
  {
    if ( Form_Graph->CheckBox_logariphm->Checked ) // Логарифмический масштаб
    {
      Form_Graph->Chart_Puasson_log->Visible = true;
      Form_Graph->Chart_Puasson_lin->Visible = true;
      Form_Graph->Series4->Clear();
      Form_Graph->Series5->Clear();
      Form_Graph->Series6->Clear();
      Form_Graph->Chart_Puasson_log->Title->Text->Clear();
      Form_Graph->Chart_Puasson_log->Title->Text->Add("Распределение по Пуассону (логарифмический масштаб)");
      for ( int i = 0; i < MaxPoisson-100; i++ )
      {
        Form_Graph->Series4->AddXY(i, y[i], "", clRed); // Распределение Пуассона
      }
      for ( int i = 0; i < MaxPoisson-100; i++ )
      {
        Form_Graph->Series5->AddXY(i, Spec[i], "", clBlack); // строим гистограмму
      }
      for ( int i = 0; i < MaxPoisson-100; i++ )
      {
        Form_Graph->Series6->AddXY(i, yy[i], "", clGreen); // строим гистограмму
      }
    }
    else if ( !Form_Graph->CheckBox_logariphm->Checked ) // Линейный масштаб
    {
      Form_Graph->Chart_Puasson_log->Visible = false;
      Form_Graph->Chart_Puasson_lin->Visible = true;
      Form_Graph->Chart_Puasson_lin->Title->Text->Clear();
      Form_Graph->Chart_Puasson_lin->Title->Text->Add("Распределение по Пуассону (линейный масштаб)");
      Form_Graph->Series1->Clear();
      Form_Graph->Series2->Clear();
      Form_Graph->Series3->Clear();
      for ( int i = 0; i < MaxPoisson-100; i++ )
      {
        Form_Graph->Series1->AddXY(i, y[i], "", clRed); // Распределение Пуассона
      }
      for ( int i = 0; i < MaxPoisson-100; i++ )
      {
        Form_Graph->Series2->AddXY(i, Spec[i], "", clBlack); // строим гистограмму
      }
      for ( int i = 0; i < MaxPoisson-100; i++ )
      {
        Form_Graph->Series3->AddXY(i, yy[i], "", clGreen);
      }
    }
  }
  else if ( Form_Graph->RadioButton_inTime->Checked ) // Построим график - изменение от времени
  {
    if ( Form_Graph->CheckBox_logariphm->Checked ) // Логарифмический масштаб
    {
      Form_Graph->Chart_Puasson_log->Visible = true;
      Form_Graph->Chart_Puasson_lin->Visible = true;
      Form_Graph->Series4->Clear();
      Form_Graph->Series5->Clear();
      Form_Graph->Series6->Clear();
      Form_Graph->Chart_Puasson_log->Title->Text->Clear();
      Form_Graph->Chart_Puasson_log->Title->Text->Add("График счёта от времени (логарифмический масштаб)");
      Form_Graph->Chart_Puasson_log->BottomAxis->Minimum = 0;
      Form_Graph->Chart_Puasson_log->BottomAxis->Maximum = Nisp;
      Form_Graph->Chart_Puasson_log->LeftAxis->Minimum = 0;
      unsigned int MaxZn3 = 0;
      for ( int i = 0; i < Nisp; i++ )
      {
        if ( DataArray[i] > MaxZn3 )
        {
          MaxZn3 = DataArray[i];
        }
      }
      if ( MaxZn3 <= 100000 )
      {
        Form_Graph->Chart_Puasson_log->LeftAxis->Maximum = 100000;
      }
      if ( MaxZn3 <= 10000 )
      {
        Form_Graph->Chart_Puasson_log->LeftAxis->Maximum = 10000;
      }
      if ( MaxZn3 <= 1000 )
      {
        Form_Graph->Chart_Puasson_log->LeftAxis->Maximum = 1000;
      }
      if ( MaxZn3 <= 100 )
      {
        Form_Graph->Chart_Puasson_log->LeftAxis->Maximum = 100;
      }
      if ( MaxZn3 <= 10 )
      {
        Form_Graph->Chart_Puasson_log->LeftAxis->Maximum = 10;
      }
      for ( int i = 0; i < Nisp; i++ )
      {
        Form_Graph->Series4->AddXY(i, DataArray[i], "", clBlack );
      }
    }
    else if ( !Form_Graph->CheckBox_logariphm->Checked ) // Линейный масштаб
    {
      Form_Graph->Chart_Puasson_log->Visible = false;
      Form_Graph->Chart_Puasson_lin->Visible = true;
      Form_Graph->Series1->Clear();
      Form_Graph->Series2->Clear();
      Form_Graph->Series3->Clear();
      Form_Graph->Chart_Puasson_lin->Title->Text->Clear();
      Form_Graph->Chart_Puasson_lin->Title->Text->Add("График счёта от времени (линейный масштаб)");
      Form_Graph->Chart_Puasson_lin->BottomAxis->Minimum = 0;
      Form_Graph->Chart_Puasson_lin->BottomAxis->Maximum = Nisp;
      Form_Graph->Chart_Puasson_lin->LeftAxis->Minimum = 0;
      unsigned int MaxZn3 = 0;
      for ( int i = 0; i < Nisp; i++ )
      {
        if ( DataArray[i] > MaxZn3 )
        {
          MaxZn3 = DataArray[i];
        }
      }
      Form_Graph->Chart_Puasson_lin->LeftAxis->Maximum = MaxZn3 + 10;
      for ( int i = 0; i < Nisp; i++ )
      {
        Form_Graph->Series1->AddXY(i, DataArray[i], "", clBlack);
      }
    }
  }
  else if ( Form_Graph->RadioButton_Gays->Checked ) // "Нормальное" распределение
  {
    if ( Form_Graph->CheckBox_logariphm->Checked ) // Логарифмический масштаб
    {
      Form_Graph->Chart_Puasson_log->Visible = true;
      Form_Graph->Chart_Puasson_lin->Visible = true;
      Form_Graph->Series4->Clear();
      Form_Graph->Series5->Clear();
      Form_Graph->Series6->Clear();
      Form_Graph->Chart_Puasson_log->Title->Text->Clear();
      Form_Graph->Chart_Puasson_log->Title->Text->Add("Распределение по Гаусу (логарифмический масштаб)");
      for ( int i = 0; i < MaxPoisson; i++ )
      {
        Form_Graph->Series4->AddXY(i, Spec_Gays[i], "", clRed); // Распределение Гауса
      }
      for ( int i = 0; i < MaxPoisson; i++ )
      {
        Form_Graph->Series5->AddXY(i, Spec[i], "", clBlack); // строим гистограмму
      }
    }
    else if ( !Form_Graph->CheckBox_logariphm->Checked ) // Линейный масштаб
    {
      Form_Graph->Chart_Puasson_log->Visible = false;
      Form_Graph->Chart_Puasson_lin->Visible = true;
      Form_Graph->Chart_Puasson_lin->Title->Text->Clear();
      Form_Graph->Chart_Puasson_lin->Title->Text->Add("Распределение по Гаусу (линейный масштаб)");
      Form_Graph->Series1->Clear();
      Form_Graph->Series2->Clear();
      Form_Graph->Series3->Clear();
      for ( int i = 0; i < MaxPoisson; i++ )
      {
        Form_Graph->Series1->AddXY(i, Spec_Gays[i], "", clRed); // Распределение Гауса
      }
      for ( int i = 0; i < MaxPoisson; i++ )
      {
        Form_Graph->Series2->AddXY(i, Spec[i], "", clBlack); // строим гистограмму
      }
    }
  }
  str = AnsiString("Среднее значение = ") + FormatFloat("0.00", SredneeZn);
  Form_Graph->Label_srednee->Caption = str;
  str = AnsiString("Значение порога = ") + FormatFloat("0.00", PorogZn);
  Form_Graph->Label_znachPoroga->Caption = str;
  str = AnsiString("Вероятность ложных срабатываний*Е-3 = ") +
  FormatFloat("0.0000", static_cast<float>(KolLog)/static_cast<float>(/*Kisp*/Nisp));
  Form_Graph->Label_verLoSrab->Caption = str;
  str = AnsiString("Количество измерений = ") + IntToStr(/*Kisp*/Nisp);
  Form_Graph->Label_kolichIzmereniy->Caption = str;

  str = AnsiString("Дисперсия = ") + FormatFloat("0.00", Di);
  Form_Graph->Label_Dispersiya->Caption = str;
  str = AnsiString("Коэф. Морозова = ") + FormatFloat("0.0000", Kr);
  Form_Graph->Label_koefMorozova->Caption = str;
  str = AnsiString("Ошибок связи = ") + IntToStr(Err_Svyaz);
  Form_Graph->Label_Error_Svyazi->Caption = str;

  Form_Graph->Show();
}
//---------------------------------------------------------------------------
double TForm_Puasson::poisson(int x, float Srednee)
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
double TForm_Puasson::Gays(int x, float Disper, float Srednee)
{
  double K1;
  const double Pi = 3.1415926535;
  K1 = 1 / sqrt ( Disper * 2 * Pi );
  return K1 * exp ( -1 * ((x - Srednee) * (x - Srednee)) /(2 * Disper) );
}
//---------------------------------------------------------------------------
void TForm_Puasson::Zapis()
{
  if ( Nisp == 0 )
  {
    return;
  }
  filename = AnsiString(put) + AnsiString("\\") + AnsiString(Edit_fileName->Text);
  FILE * filW; // для чтения
  filW = fopen( filename.c_str(), "wt" );
  if ( filW == NULL )
  {
    AnsiString filename2 = "Файл " + filename + " не открылся благополучно";
    Application->MessageBox( filename2.c_str(), "Ошибка ", MB_ICONSTOP);
    return;
  }

  fprintf( filW, "   %i\n", Nisp/*-1*/);
  for ( int j = 0; j < Nisp /*- 1*/; j++ )
  {
    fprintf ( filW, "%9.0f ", SredMas[j] );
    fprintf ( filW, "\n" );
  }
  fclose( filW );
}


void __fastcall TForm_Puasson::Button_stopClick(TObject *Sender)
{ // СТОП
  WorkCancel = false;
  FlagWork = false;
  Application->ProcessMessages();
  Zapis(); // результаты испытания - в файл
  Application->ProcessMessages();
  Button_start->Enabled = true;
  Button_exit->Enabled = true;
  Button_stop->Enabled = false;
  StatusBar->Panels->Items[0]->Text = " ";
  StatusBar->Panels->Items[1]->Text = " ";
}
//---------------------------------------------------------------------------

