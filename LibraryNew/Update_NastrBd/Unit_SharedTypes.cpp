//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
#include <vcl.h>
//---------------------------------------------------------------------------
#include "Unit_SharedTypes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void MyStrCopy(
    char * strTo,
    const char * strFrom,
    int maxLength
)
{
  for ( int i = 0; i < maxLength; i++ )
  {
    strTo[i] = strFrom[i];
    if ( strTo[i] == 0 )
    {
      break;
    }
  }
}
//---------------------------------------------------------------------------
void SetNull(
    char * strTo,
    int Count
)
{
  for ( int i = 0; i < Count; i++ )
  {
    strTo[i] = 0;
  }
}
//---------------------------------------------------------------------------
// Конструктор
TFileBuffer::TFileBuffer(const char * key) :
    _key( key )
    ,_btArrPtr(0)
    ,_length(0)
    ,_bfDebuf( 1 )
{
}
//---------------------------------------------------------------------------
// Деструктор
TFileBuffer::~TFileBuffer()
{
    if ( _btArrPtr != 0 )
    {
        delete [] _btArrPtr;
    }
}
//---------------------------------------------------------------------------
// Прочитать содержимое файла в себя
int TFileBuffer::ReadFileToSelf( char * fileName )
{
  unsigned long BytesForRead = 0; // Количество байт, которое нужно прочитать
  unsigned long ReadBytes = 0; // Количество реально прочитанных байт
  int errCode;

  // Прочитать себя
  HANDLE hRead = CreateFile (
      fileName, // lpFileName ("LPT1")
      GENERIC_READ, // dwDesiredAccess
      
      //0, // dwShareMode (0 - совместный доступ невозможен)
      FILE_SHARE_READ, // dwShareMode (0 - совместный доступ невозможен)
      // 0 - порождает ошибки неверного дескриптора

      NULL, // lpSecurityAttributes (0 - дескриптор не может быть унаследован процессами - потомками)
      OPEN_EXISTING,  // dwCreationDisposition (Открыть файл)
      NULL, // dwFlagsAndAttributes (0)
      0  // hTemplateFile (IntPtr.Zero)
  );

  SetLastError( 0 );

  // Узнать размер файла
  BytesForRead = SetFilePointer ( // Установить позицию в конец файла, перед чтением
      hRead, // Дескриптор ресурса (файла)
      0, // Чичло байт, на которое требуется переместить курсор
      NULL,
      FILE_END // Сдвиг относительно конца
  );

  errCode = GetLastError();
  if (errCode != 0)
  {
    AnsiString str = "ReadSelf: конец файла. ";
    str += SysErrorMessage( errCode );
    ErrorMess( str.c_str(), 2 );
  }

  if ( this->_btArrPtr != 0 )
  {
    delete [] this->_btArrPtr;
  }

  // Выделить память для чтения
  this->_btArrPtr = new unsigned char [BytesForRead];

  // Подготовиться к чтению
  ReadBytes = SetFilePointer ( // Установить позицию в начало файла, перед чтением
      hRead, // Дескриптор файла
      0, // Чичло байт, на которое требуется переместить курсор
      NULL,
      FILE_BEGIN // Сдвиг относительно начала
  );

  ReadFile (
      hRead, // Дескриптор файла
      this->_btArrPtr, //
      BytesForRead, // Количество байт, которое нужно прочитать
      & ReadBytes, // Количество прочитанных байт
      NULL // OVERLAPPED, м.б. равнв нулю, при синхронном чтении
  );
  
  this->_length = ReadBytes;

  if ( BytesForRead != ReadBytes )
  {
    AnsiString str = "Ошибка чтения: прочитанно ";
    str += IntToStr ( ReadBytes );
    str += " вместо ";
    str += IntToStr ( BytesForRead );
    ErrorMess( str.c_str(), 2 );
    CloseHandle( hRead );
    return -1;
  }
  CloseHandle( hRead );
  return 0;
}
//---------------------------------------------------------------------------
// Записать своё содержимое в файл
void TFileBuffer::WriteFileFromSelf( char * fileName )
{
  unsigned long BytesForWrite = 0; // Количество байт, которое нужно ззаписать
  unsigned long WriteBytes = 0; // Количество реально записанных байт

  HANDLE hWrite = CreateFile (
        fileName, // lpFileName ("LPT1")
        GENERIC_WRITE, // dwDesiredAccess
        0, // dwShareMode (0 - совместный доступ невозможен)
        NULL, // lpSecurityAttributes (0 - дескриптор не может быть унаследован процессами - потомками)
        CREATE_ALWAYS,  // dwCreationDisposition (Создать новый файл, переписать, если существует)
        NULL, // dwFlagsAndAttributes (0)
        0 // hTemplateFile (IntPtr.Zero)
  );

  // Записать основное тело файла
  BytesForWrite = this->_length;

  WriteFile (
      hWrite, // Дескриптор файла
      this->_btArrPtr, //
      BytesForWrite, // Количество байт, которое нужно записать
      & WriteBytes, // Количество записанных байт
      NULL // OVERLAPPED, м.б. равнв нулю, при синхронной записии
  );
  
  if ( BytesForWrite != WriteBytes )
  {
    AnsiString str = "Ошибка записи (WriteSelf): записано ";
    str += IntToStr ( WriteBytes );
    str += " вместо ";
    str += IntToStr ( BytesForWrite );
    ErrorMess( str.c_str(), 2 );
    CloseHandle( hWrite );
    return;
  }
  CloseHandle( hWrite );
}
//---------------------------------------------------------------------------
// Записать своё содержимое и ССД (специальную структуру данных) в файл
void TFileBuffer::WriteSelfSsd( char * fileName )
{
  unsigned long BytesForWrite = 0; // Количество байт, которое нужно ззаписать
  unsigned long WriteBytes = 0; // Количество реально записанных байт

  HANDLE hWrite = CreateFile (
        fileName, // lpFileName ("LPT1")
        GENERIC_WRITE, // dwDesiredAccess
        0, // dwShareMode (0 - совместный доступ невозможен)
        NULL, // lpSecurityAttributes (0 - дескриптор не может быть унаследован процессами - потомками)
        CREATE_ALWAYS,  // dwCreationDisposition (Создать новый файл, переписать, если существует)
        NULL, // dwFlagsAndAttributes (0)
        0 // hTemplateFile (IntPtr.Zero)
  );

  // Записать основное тело файла
  BytesForWrite = this->_length;

  WriteFile (
      hWrite, // Дескриптор файла
      this->_btArrPtr, //
      BytesForWrite, // Количество байт, которое нужно записать
      & WriteBytes, // Количество записанных байт
      NULL // OVERLAPPED, м.б. равнв нулю, при синхронной записии
  );
  if ( BytesForWrite != WriteBytes )
  {
    AnsiString str = "Ошибка записи (WriteSelfSsd - _btArrPtr): записано ";
    str += IntToStr ( WriteBytes );
    str += " вместо ";
    str += IntToStr ( BytesForWrite );
    ErrorMess( str.c_str(), 2 );

    CloseHandle( hWrite );
    return;
  }
  // Запись Ssd, которая должна быть проинициализированна
  BytesForWrite = sizeof ( TSsd );
  WriteFile (
      hWrite, // Дескриптор файла
      _ssd.BtArr, //
      BytesForWrite, // Количество байт, которое нужно записать
      & WriteBytes, // Количество записанных байт
      NULL // OVERLAPPED, м.б. равнв нулю, при синхронной записии
  );
  if ( BytesForWrite != WriteBytes )
  {
    AnsiString str = "Ошибка записи (WriteSelfSsd - _ssd): записано ";
    str += IntToStr ( WriteBytes );
    str += " вместо ";
    str += IntToStr ( BytesForWrite );
    ErrorMess( str.c_str(), 2 );
  }
  CloseHandle( hWrite );
}
//---------------------------------------------------------------------------
// Начальная инициализация специальной структуры данных
void TFileBuffer::StartSsdInit( char * fileName )
{
  int size = sizeof ( TSsd );
  // Инициализировать нулями
  SetNull( _ssd.BtArr, size );
  // Записываем ключ
  MyStrCopy ( _ssd.Info.key, this->_key, __kei_length__ );
  // Записываем имя файла
  MyStrCopy ( _ssd.Info.fileName, fileName, 256 );
  _ssd.Info.count = 0;
  _ssd.Info.Size.Lint = size;
  _ssd.Info.flags[0] = 0x55; // Признак промежуточной программы
}
//---------------------------------------------------------------------------
// Изменить признак промежуточной програмы: это НЕ ПП
void TFileBuffer::SsdNoPp()
{
  _ssd.Info.flags[0] = 0xAA; // Признак промежуточной программы
}
//---------------------------------------------------------------------------
// Изменить признак промежуточной програмы: это ПП
void TFileBuffer::SsdYesPp( char * fileName )
{
  // Записываем имя файла
  MyStrCopy ( _ssd.Info.fileName, fileName, 256 );
  _ssd.Info.flags[0] = 0x55; // Признак промежуточной программы
}
//---------------------------------------------------------------------------
// "Инкрементировать" ССД, либо выполнить сброс, либо оставить без изменения
void TFileBuffer::SsdIncrement()
{
  if ( _ssd.Info.flags[1] == 1 )
  {
    _ssd.Info.flags[1] = 2; // Оставить без изменений
    return;
  }
  if ( _ssd.Info.flags[1] == 2 )
  {
    _ssd.Info.flags[1] = 0; // Сбросить
    _ssd.Info.count = 0;
  }
  _ssd.Info.count++; // Инкрементировать
}
//---------------------------------------------------------------------------
int TFileBuffer::GetCount()
{
  return _ssd.Info.count;
}
//---------------------------------------------------------------------------
long TFileBuffer::GetPoVersiya()
{
  return _ssd.Info.poVersiya;
}
//---------------------------------------------------------------------------
void TFileBuffer::SetPoVersiya(long poVers)
{
  _ssd.Info.poVersiya = poVers;
}
//---------------------------------------------------------------------------
void TFileBuffer::SsdReset()
{
  _ssd.Info.flags[1] = 1;
}
//---------------------------------------------------------------------------
// Проверить ключ специальной структуры данных (ССД).
bool TFileBuffer::CheckKey()
{
  int keyLength = __kei_length__;
  for ( int i = 0, j = _length - keyLength; i < keyLength; i++, j++ )
  {
    if ( _btArrPtr[j] != _key[i] )
    {
      ErrorMess( "CheckKey(): ошибка при сравнении ключа", 2 );
      return false;
    }
  }
  // Ключ найден
  int size1 = sizeof ( TSsd );
  CopyIsKeyFind ( // Получить все данные структуры
      size1 );
  int size2 = _ssd.Info.Size.Lint;
  if ( size1 != size2 )
  {
    ErrorMess( "CheckKey(): ошибка в размере слушебного блока данных", 2 );
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------
// Является ли текущая программа промежуточной
bool TFileBuffer::Intermediate()
{
    if ( _ssd.Info.flags[0] == 0x55 )
    {
        return true;
    }
    if ( _ssd.Info.flags[0] == 0xAA )
    {
        return false;
    }
    ErrorMess( "TFileBuffer::Intermediate(): Недопустимое значение", 1 );
    return false;
}
//---------------------------------------------------------------------------
// Установить ключ специальной структуры данных (ССД), и некоторую другую информацию
void TFileBuffer::SetKey()
{
    // зарезервировано на будущее 
}
//---------------------------------------------------------------------------
// Если ключ модификации файла найден, копируем служебные данные из
// файла в специальную структуру данных
void TFileBuffer::CopyIsKeyFind(
    int btArrLength )
{
    for ( int i = 0, j = _length - btArrLength; i < btArrLength; i++, j++ )
    {
        _ssd.BtArr[i] = _btArrPtr[j];
    }
}
//---------------------------------------------------------------------------
// Если ключ модификации файла найден, копируем служебные данные из
// специальной структуры данных в файл
void TFileBuffer::CopyIsKeyFindRevers(
    int btArrLength )
{
  for ( int i = 0, j = /*fileArrLength*/_length - btArrLength; i < btArrLength; i++, j++ )
  {
    _btArrPtr[j] = _ssd.BtArr[i];
  }
}
//---------------------------------------------------------------------------
char * TFileBuffer::GetInfofillName()
{
  return _ssd.Info.fileName;
}
//---------------------------------------------------------------------------
// Сообщить об ошибке
void TFileBuffer::ErrorMess( char * text, int Level )
{
    // зарезервировано на будущее
  if ( _bfDebuf >= Level )
  {
    ShowMessage( text );
  }
}
//---------------------------------------------------------------------------
