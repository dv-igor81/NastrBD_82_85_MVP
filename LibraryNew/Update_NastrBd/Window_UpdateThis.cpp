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
    int deystvie = _writeSelf.StartProgramm(); // Прочитать самого себя
    AnsiString localFileName = ParamStr( 0 ); // Имя текущего файла
    AnsiString remoteFileName =
      "\\\\fileserver\\Change\\Podr-56\\Дорофеев Игорь Александрович (DIA)\\Updater\\NastrBD\\NastrBD_82_85.exe";
    AnsiString remoteFileNameFake = "C:\\Updater\\NastrBD\\NastrBD_82_85.exe";

    int test;
    switch ( deystvie )
    {
    case 1: // 1 - НП
        this->Panel_Display->Caption = "Проверка обновления";
        this->Label_Display->Caption = "Начальная программа";
        test = _writeSelf.ReadUpdatedProg(localFileName, remoteFileName, remoteFileNameFake);
        if ( test == 1 ) // Надо обновиться
        {
          _writeSelf.UpdatedWriteFile(); // Создать промежуточный файл из прочитанного
          this->Timer->Enabled = true;
          this->Timer->Interval = 1000;
        }
        else if (test == 2) // Перезапишу версию
        {
          _writeSelf.MyWriteFile(); // Создать промежуточный файл из себя
          this->Timer->Enabled = true;
          this->Timer->Interval = 1000;
        }
        else if (test == 3)
        {
          this->Panel_Display->Caption = "fileserver недоступен, либо программа была удалена";
          this->Label_Display->Caption = "fileserver недоступен, либо программа была удалена";
          Label_Count->Caption = _writeSelf.AnalisFile(); // Данные с счётчика
          Label_VersiyaPo->Caption = _writeSelf.AnalisFileVerPo(); // Версия ПО
          // Скрываем эту форму, показываем основную форму
          // ...
          this->Timer->Enabled = true;
          this->Timer->Interval = 2000;
          _step = 3;
        }
        else if (test == 0) // Нет нужды в обновлении
        {
          // Нет обновления - нет нужды создавать промежуточный файл
          this->Panel_Display->Caption = "Установлена последняя версия";
          this->Label_Display->Caption = "Установлена последняя версия";
          Label_Count->Caption = _writeSelf.AnalisFile(); // Данные с счётчика
          Label_VersiyaPo->Caption = _writeSelf.AnalisFileVerPo(); // Версия ПО
          // Скрываем эту форму, показываем основную форму
          // ...
          this->Timer->Enabled = true;
          this->Timer->Interval = 2000;
          _step = 3;
        }
        // ===>> Сделать форму невидимой
        //Visible = false;
        //Application->ShowMainForm = false;
        // <<=== Сделать форму невидимой
        break;
    case 2: // 2 - ПП
        this->Label_Display->Caption = "===}{===";
        _bfTimerFirst = true; // Дождаться завершения начальной программы (ничего тут не делать)
        // ===>> Сделать форму невидимой
        Visible = false;
        Application->ShowMainForm = false;
        // <<=== Сделать форму невидимой
        this->Timer->Enabled = true;
        this->Timer->Interval = 1000;
        break;
    case 3: // 3 - ОП
        this->Panel_Display->Caption = "Обновление успешно завершено";
        this->Label_Display->Caption = "Окончательная программа";
        _bfTimerFirst = true; // Дождаться завершения промежуточной программы (ничего тут не делать)
        this->Timer->Enabled = true;
        this->Timer->Interval = 1000;
        //_step = 3;
        break;
    case 4: // 4 - ключ не найден (первый запуск)
        this->Panel_Display->Caption = "Первый запуск: системные данные еще не записаны";
        this->Label_Display->Caption = "Первый запуск";
        _writeSelf.MyWriteFile(); // Создать промежуточный файл
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
    case 1: // 1 - НП
    case 4: // 4 - ключ не найден (первый запуск)
        _writeSelf.MyWinExec(); // Запустить промежуточную программу
        Close(); // Завершить выполнение
        break;
    case 2: // 2 - ПП
        if ( this->_bfTimerFirst == true )
        {
            // Перезаписать начальную программу, окончательной
            _writeSelf.MyWriteFile(); // Создать файл окончательной программы
            // подождать, пока данные запишутся
            this->_bfTimerFirst = false;
            this->Timer->Enabled = true;
        }
        else
        {
            _writeSelf.MyWinExec(); // Запустить окончательную программу
            Close(); // Завершить выполнение
        }
        break;
    case 3: // 3 - ОП
        SetLastError( 0 );
        if ( DeleteFile( _writeSelf.GetNewFileName() ) == 0 ) // Ошибка
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
        this->Panel_Display->Caption = "}Обновление успешно завершено{";
        this->Label_Display->Caption = "Удаление ПП ОК";
        Label_Count->Caption = _writeSelf.AnalisFile(); // Данные с счётчика
        Label_VersiyaPo->Caption = _writeSelf.AnalisFileVerPo(); // Версия ПО
        _writeSelf.SetReady(); // Установить флаг готовности (для сброса счётчика)
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
// Программа запущена из файл-сервера?
bool TWindow_Updater::ProgramStartFromFileServer()
{
  AnsiString localFileName = ParamStr( 0 ); // Имя текущего файла
  if ( FileExists("DebugDiaMess_VNIIA.txt" ) )
  {
    Application->MessageBox(
          localFileName.c_str(),
          "NastrBD82_85.exe",
          MB_ICONSTOP);
  }
  //localFileName = localFileName.LowerCase(); // к нижнему регистру
  localFileName = localFileName.UpperCase(); // к ВЕРХНЕМУ регистру
  if (
    localFileName.Pos("\\\\FILESERVER\\") == 1 || // В производственной среде
    localFileName.Pos("\\\\IGOR81-PC\\") == 1 ) // Легче тестировать на своём компе
  {
    return true; // Да, вначеле имени встретилась строка '\\fileserver\'
  }
  AnsiString bukvaDiska = localFileName.SubString(0, 1);
  char Drives[255];
  PChar P;
  AnsiString AllBukvDiskov; // Все буквы дисков (кроме сетевых)
  if ( GetLogicalDriveStrings( 256, Drives ) > 256 )
  {
    return false; // Считаем, что диск не сетевой, т.к. ошибка
  }
  AllBukvDiskov = "";
  P = Drives;
  while ( *P != 0 )
  {
    if ( GetDriveType( P ) != DRIVE_REMOTE ) // Диск не является сетевым (условие на всякий случай)
    { // потому, что обычно сетевые диски в этом списке и так отсутствуют!!!
      AllBukvDiskov += AnsiString( P );
    }
    P += 4; // К следующей букве диска
  }
  AllBukvDiskov = AllBukvDiskov.UpperCase(); // к ВЕРХНЕМУ регистру
  if ( AllBukvDiskov.Pos(bukvaDiska) == 0 )
  {
    return true; // Сетевой диск
  }
  return false;
}
//---------------------------------------------------------------------------
void __fastcall TWindow_Updater::FormCreate(TObject *Sender)
{
  if ( ProgramStartFromFileServer() )
  {
    Application->ShowMainForm = false; // Скрыть форму (свойство Visible должно быть установлено в false - в дизайнере, а не программно здесь)
    //ShowMessage( "Для успешного запуска программы, скопируйте её к себе на диск. Запуск из fileserver запрещен." );
    Application->MessageBox(
          "Для успешного запуска программы, скопируйте её к себе на диск. Запуск из fileserver запрещен.",
          "NastrBD82_85.exe",
          MB_ICONSTOP);
    _step = 4;
  }
  else if ( FileExists("NoUpdate.txt") )
  {
    _step = 3; // Не проверять обновление
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
        Step_03(); // Запустить программу
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
    // Дать команду на сброс счётчика
    if ( ! _writeSelf.Reset() ) // Только для _writeSelf.GetFlag() == 3 ( ОП )
    {
        return; // Не готов сбросить счётчики
    }
    // Записан промежуточный файл
    _bfTimerFirst = true; // Таймер запустить придётся два раза (сейчас будет первый запуск)
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

