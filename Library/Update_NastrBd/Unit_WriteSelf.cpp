//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Unit_WriteSelf.h"
//---------------------------------------------------------------------------
#include <vcl.h>
//---------------------------------------------------------------------------
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Конструктор
TWriteSelf::TWriteSelf() :
    _fileBufSelf ( "DIAVNIIA" )  // Ключ
    ,_fileBufUpdate ( "DIAVNIIA" )  // Ключ
    ,_flagDeystviya ( 0 )
    ,_bfDebuf( 1 )
    ,_bfReady( false ) // флаг готовности (для сброса счётчика) 
{
}
//---------------------------------------------------------------------------
// Деструктор
TWriteSelf::~TWriteSelf()
{
}
//---------------------------------------------------------------------------
// Кто я: 1 - НП, 2 - ПП, 3 - ОП, 4 - ключ не найден (первый запуск)
// НП - Начальная программа, запускается пользователем, создаёт и запускает Промежуточную программу
// ПП - Промежуточная программа, запускается Начальной программой, создаёт и запускает Окончательную программу
// ОП - Окончательная программа, запускается Промежуточной программой, ничего не создаёт и не запускает
int TWriteSelf::WhoAmI() // Прочитать себя в буффер
{
    fileName = ParamStr( 0 ); // Имя текущего файла
    return WhoAmFile( fileName, _fileBufSelf );
}
//---------------------------------------------------------------------------
int TWriteSelf::WhoAmFile(
  AnsiString fileNameLocal,
  TFileBuffer & fileBufLocal)
{
    if ( fileBufLocal.ReadFileToSelf( fileNameLocal.c_str() ) != 0 ) // Прочитать файл в буффер
    {
      return -1; // Ошибка чтения
    }

    if ( fileBufLocal.CheckKey() )
    {
        Mess( "TWriteSelf::WhoAmI(): Ключ найден", 2 );
        // Является ли текущая программа Промежуточной программой
        if ( fileBufLocal.Intermediate() ) // Intermediate program
        {
            Mess( "TWriteSelf::WhoAmI(): ПП - Промежуточная программа", 2 );
            InfofillName = fileBufLocal.GetInfofillName();
            return 2; // ПП - Промежуточная программа
        }
        else
        { // Программа не является промежуточной
          // Если файл "Промежуточная программа" найден, значит,
          // текущая программа - "Окончательная программа". Иначе - "Начальная программа"
            if ( FileExists( GetNewFileName() ) )
            {
                Mess( "TWriteSelf::WhoAmI(): ОП - Окончательная программа", 2 );
                return 3; // ОП - Окончательная программа
            }
            else
            {
                Mess( "TWriteSelf::WhoAmI(): НП - Начальная программа", 2 );
                return 1; // НП - Начальная программа
            }
        }
    }
    else
    {
        Mess( "TWriteSelf::WhoAmI(): Ключ НЕ найден", 2 );
        return 4; // ключ не найден (первый запуск)
    }
}
//---------------------------------------------------------------------------
// Старт программы
int TWriteSelf::StartProgramm()
{
    int deystvie = WhoAmI();

    switch ( deystvie )
    {
    case 1: // 1 - НП
        _flagDeystviya = 1;
        break;
    case 2: // 2 - ПП
        _flagDeystviya = 2;
        break;
    case 3: // 3 - ОП
        _flagDeystviya = 3;
        break;
    case 4: // 4 - ключ не найден (первый запуск)
        _flagDeystviya = 4;
        break;
    default: // Неопределённое значение
       _flagDeystviya = -1;
       break;
    }
    return _flagDeystviya;
}
//---------------------------------------------------------------------------
int TWriteSelf::ReadUpdatedProg(
  AnsiString locFileName,
  AnsiString remFileName,
  AnsiString remoteFileNameFake)
{
  int errCod = _fileBufSelf.ReadFileToSelf( locFileName.c_str() );
  if ( errCod != 0 )
  {
    Mess( "TWriteSelf::WhoAmI(): Сам себя не прочитал", 1 );
    return -1;
  }
//===========================================================================
  int curVerPo = 12; // v4.29.1 (12)
//===========================================================================  
  int verPo = _fileBufSelf.GetPoVersiya();
  if (verPo != curVerPo)
  {
     Mess( "TWriteSelf::WhoAmI(): Перезапишу версию", 1 );
    _fileBufSelf.SetPoVersiya(curVerPo); // Версия программы
    return 2;
  }
  errCod = _fileBufUpdate.ReadFileToSelf( remoteFileNameFake.c_str() );
  if ( errCod != 0 )
  {
    //Mess( "Удаленный файл не прочитан (возможно фейковый fileserver недоступен)", 1 );
    errCod = _fileBufUpdate.ReadFileToSelf( remFileName.c_str() );
    if (errCod != 0)
    {
      //Mess( "Удаленный файл не прочитан (возможно fileserver недоступен)", 1 );
      return 3; // Не нужно обновляться
    }
  }
  if ( _fileBufUpdate.CheckKey() == false )
  {
    Mess( "_fileBufUpdate.CheckKey() == false", 1 );
  }
  int NewVersion = _fileBufUpdate.GetPoVersiya();
  if ( NewVersion == -1 )
  {
    //Mess( "TWriteSelf::WhoAmI(): Обнови - NewVersion == -1", 2 );
    return 1; // Надо обновляться
  }
  if ( NewVersion > curVerPo )
  {
    //sprintf(msfFormated,
    //  "TWriteSelf::WhoAmI(): Обнови - NewVersion (%d) > curVerPo (%d)",
    //  NewVersion, curVerPo);
    //Mess( msfFormated, 2 );
    return 1; // Надо обновляться
  }
  //sprintf(msfFormated,
  //  "TWriteSelf::WhoAmI(): NewVersion  = %d END curVerPo = %d",
  //  NewVersion, curVerPo);
  //Mess( msfFormated, 2 );
  return 0; // Не нужно обновляться
}
//---------------------------------------------------------------------------
void TWriteSelf::Mess( char * text, int Level )
{
  if ( _bfDebuf >= Level )
  {
    ShowMessage( text );
  }
}
//---------------------------------------------------------------------------
// Записать файл
void TWriteSelf::MyWriteFile()
{
  MyWriteFile(_fileBufSelf);
}
//---------------------------------------------------------------------------
void TWriteSelf::UpdatedWriteFile()
{
  MyWriteFile(_fileBufUpdate);
}
//---------------------------------------------------------------------------
void TWriteSelf::MyWriteFile(TFileBuffer & fileBufLocal)
{
  AnsiString newFileName;
  int size1;
  switch ( _flagDeystviya )
  {
  case 1: // 1 - НП
    // Создать файл промежуточной программы
    fileBufLocal.SsdYesPp( fileName.c_str() ); // ССД изменить признак ПП
    //
    size1 = sizeof ( TSsd );
    fileBufLocal.CopyIsKeyFindRevers ( size1 ); // Записать в файл все данные структуры

    newFileName = GetNewFileName();
    fileBufLocal.WriteFileFromSelf( newFileName.c_str() ); // Записать промежуточный файл
    break;
  case 2: // 2 - ПП
    // Создать файл окончательной программы
    fileBufLocal.SsdNoPp(); // ССД изменить признак ПП
    // "Инкрементировать" ССД, либо выполнить сброс, либо оставить без изменения
    fileBufLocal.SsdIncrement(); // ССД инкрементировать счётчики

    size1 = sizeof ( TSsd );
    fileBufLocal.CopyIsKeyFindRevers ( size1 ); // Записать в файл все данные структуры

    fileBufLocal.WriteFileFromSelf( InfofillName.c_str() ); // Записать файл окончательной программы
    break;
  //case 3: // 3 - ОП
  //  // Ничего создавать не нужно
  //  break;
  case 4: // 4 - ключ не найден (первый запуск)
    // Создать файл промежуточной программы
    fileBufLocal.StartSsdInit( fileName.c_str() ); // Проинициализировать ССД
    newFileName = GetNewFileName();
    fileBufLocal.WriteSelfSsd( newFileName.c_str() ); // Записать промежуточный файл
    break;
  }
}
//---------------------------------------------------------------------------
void TWriteSelf::MyWinExec()
{
  AnsiString fName;
  switch ( _flagDeystviya )
  {
  case 1: // 1 - НП
  case 4: // 4 - ключ не найден (первый запуск)
    fName = GetNewFileName();
    break;
  case 2: // 2 - ПП
    fName = InfofillName;
    break;
  }
  int Code = WinExec( fName.c_str(), SW_RESTORE );
  if ( Code < 32 ) // Если функция завершается успешно, величина возвращаемого значения - больше чем 31.
  {
    int ErrCode = GetLastError();
    if ( ErrCode != 0 )
    {
      Mess( "MyWinExec(): Error", 1 );
    }
  }
}
//---------------------------------------------------------------------------
// Установить флаг готовности (для сброса счётчика)
void TWriteSelf::SetReady()
{
  _bfReady = true;
}
//---------------------------------------------------------------------------
// Дать команду на сброс счётчика
bool TWriteSelf::Reset()
{
  return Reset(_fileBufSelf);
}
//---------------------------------------------------------------------------
// Сбросить счетчик запусков программы
bool TWriteSelf::Reset(TFileBuffer & fileBufLocal)
{
  if ( ! _bfReady )
  {
    return false; // Неготово
  }

  // Создать файл промежуточной программы
  fileBufLocal.SsdYesPp( fileName.c_str() ); // ССД изменить признак ПП
  fileBufLocal.SsdReset(); // ССД команда на сброс счётчика

  int size1 = sizeof ( TSsd );
  fileBufLocal.CopyIsKeyFindRevers ( size1 ); // Записать в файл все данные структуры

  AnsiString newFileName = GetNewFileName();
  fileBufLocal.WriteFileFromSelf( newFileName.c_str() ); // Записать промежуточный файл

  _flagDeystviya = 1; // 1 - НП
  return true; // Готово
}
//---------------------------------------------------------------------------
AnsiString TWriteSelf::AnalisFile()
{
  return IntToStr ( _fileBufSelf.GetCount() );
}
//---------------------------------------------------------------------------
AnsiString TWriteSelf::AnalisFileVerPo()
{
  return IntToStr ( _fileBufSelf.GetPoVersiya() );
}
//---------------------------------------------------------------------------
AnsiString TWriteSelf::GetNewFileName()
{
  return this->fileName + ".exe";
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
