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
// �����������
TFileBuffer::TFileBuffer(const char * key) :
    _key( key )
    ,_btArrPtr(0)
    ,_length(0)
    ,_bfDebuf( 1 )
{
}
//---------------------------------------------------------------------------
// ����������
TFileBuffer::~TFileBuffer()
{
    if ( _btArrPtr != 0 )
    {
        delete [] _btArrPtr;
    }
}
//---------------------------------------------------------------------------
// ��������� ���������� ����� � ����
int TFileBuffer::ReadFileToSelf( char * fileName )
{
  unsigned long BytesForRead = 0; // ���������� ����, ������� ����� ���������
  unsigned long ReadBytes = 0; // ���������� ������� ����������� ����
  int errCode;

  // ��������� ����
  HANDLE hRead = CreateFile (
      fileName, // lpFileName ("LPT1")
      GENERIC_READ, // dwDesiredAccess
      
      //0, // dwShareMode (0 - ���������� ������ ����������)
      FILE_SHARE_READ, // dwShareMode (0 - ���������� ������ ����������)
      // 0 - ��������� ������ ��������� �����������

      NULL, // lpSecurityAttributes (0 - ���������� �� ����� ���� ����������� ���������� - ���������)
      OPEN_EXISTING,  // dwCreationDisposition (������� ����)
      NULL, // dwFlagsAndAttributes (0)
      0  // hTemplateFile (IntPtr.Zero)
  );

  SetLastError( 0 );

  // ������ ������ �����
  BytesForRead = SetFilePointer ( // ���������� ������� � ����� �����, ����� �������
      hRead, // ���������� ������� (�����)
      0, // ����� ����, �� ������� ��������� ����������� ������
      NULL,
      FILE_END // ����� ������������ �����
  );

  errCode = GetLastError();
  if (errCode != 0)
  {
    AnsiString str = "ReadSelf: ����� �����. ";
    str += SysErrorMessage( errCode );
    ErrorMess( str.c_str(), 2 );
  }

  if ( this->_btArrPtr != 0 )
  {
    delete [] this->_btArrPtr;
  }

  // �������� ������ ��� ������
  this->_btArrPtr = new unsigned char [BytesForRead];

  // ������������� � ������
  ReadBytes = SetFilePointer ( // ���������� ������� � ������ �����, ����� �������
      hRead, // ���������� �����
      0, // ����� ����, �� ������� ��������� ����������� ������
      NULL,
      FILE_BEGIN // ����� ������������ ������
  );

  ReadFile (
      hRead, // ���������� �����
      this->_btArrPtr, //
      BytesForRead, // ���������� ����, ������� ����� ���������
      & ReadBytes, // ���������� ����������� ����
      NULL // OVERLAPPED, �.�. ����� ����, ��� ���������� ������
  );
  
  this->_length = ReadBytes;

  if ( BytesForRead != ReadBytes )
  {
    AnsiString str = "������ ������: ���������� ";
    str += IntToStr ( ReadBytes );
    str += " ������ ";
    str += IntToStr ( BytesForRead );
    ErrorMess( str.c_str(), 2 );
    CloseHandle( hRead );
    return -1;
  }
  CloseHandle( hRead );
  return 0;
}
//---------------------------------------------------------------------------
// �������� ��� ���������� � ����
void TFileBuffer::WriteFileFromSelf( char * fileName )
{
  unsigned long BytesForWrite = 0; // ���������� ����, ������� ����� ���������
  unsigned long WriteBytes = 0; // ���������� ������� ���������� ����

  HANDLE hWrite = CreateFile (
        fileName, // lpFileName ("LPT1")
        GENERIC_WRITE, // dwDesiredAccess
        0, // dwShareMode (0 - ���������� ������ ����������)
        NULL, // lpSecurityAttributes (0 - ���������� �� ����� ���� ����������� ���������� - ���������)
        CREATE_ALWAYS,  // dwCreationDisposition (������� ����� ����, ����������, ���� ����������)
        NULL, // dwFlagsAndAttributes (0)
        0 // hTemplateFile (IntPtr.Zero)
  );

  // �������� �������� ���� �����
  BytesForWrite = this->_length;

  WriteFile (
      hWrite, // ���������� �����
      this->_btArrPtr, //
      BytesForWrite, // ���������� ����, ������� ����� ��������
      & WriteBytes, // ���������� ���������� ����
      NULL // OVERLAPPED, �.�. ����� ����, ��� ���������� �������
  );
  
  if ( BytesForWrite != WriteBytes )
  {
    AnsiString str = "������ ������ (WriteSelf): �������� ";
    str += IntToStr ( WriteBytes );
    str += " ������ ";
    str += IntToStr ( BytesForWrite );
    ErrorMess( str.c_str(), 2 );
    CloseHandle( hWrite );
    return;
  }
  CloseHandle( hWrite );
}
//---------------------------------------------------------------------------
// �������� ��� ���������� � ��� (����������� ��������� ������) � ����
void TFileBuffer::WriteSelfSsd( char * fileName )
{
  unsigned long BytesForWrite = 0; // ���������� ����, ������� ����� ���������
  unsigned long WriteBytes = 0; // ���������� ������� ���������� ����

  HANDLE hWrite = CreateFile (
        fileName, // lpFileName ("LPT1")
        GENERIC_WRITE, // dwDesiredAccess
        0, // dwShareMode (0 - ���������� ������ ����������)
        NULL, // lpSecurityAttributes (0 - ���������� �� ����� ���� ����������� ���������� - ���������)
        CREATE_ALWAYS,  // dwCreationDisposition (������� ����� ����, ����������, ���� ����������)
        NULL, // dwFlagsAndAttributes (0)
        0 // hTemplateFile (IntPtr.Zero)
  );

  // �������� �������� ���� �����
  BytesForWrite = this->_length;

  WriteFile (
      hWrite, // ���������� �����
      this->_btArrPtr, //
      BytesForWrite, // ���������� ����, ������� ����� ��������
      & WriteBytes, // ���������� ���������� ����
      NULL // OVERLAPPED, �.�. ����� ����, ��� ���������� �������
  );
  if ( BytesForWrite != WriteBytes )
  {
    AnsiString str = "������ ������ (WriteSelfSsd - _btArrPtr): �������� ";
    str += IntToStr ( WriteBytes );
    str += " ������ ";
    str += IntToStr ( BytesForWrite );
    ErrorMess( str.c_str(), 2 );

    CloseHandle( hWrite );
    return;
  }
  // ������ Ssd, ������� ������ ���� ��������������������
  BytesForWrite = sizeof ( TSsd );
  WriteFile (
      hWrite, // ���������� �����
      _ssd.BtArr, //
      BytesForWrite, // ���������� ����, ������� ����� ��������
      & WriteBytes, // ���������� ���������� ����
      NULL // OVERLAPPED, �.�. ����� ����, ��� ���������� �������
  );
  if ( BytesForWrite != WriteBytes )
  {
    AnsiString str = "������ ������ (WriteSelfSsd - _ssd): �������� ";
    str += IntToStr ( WriteBytes );
    str += " ������ ";
    str += IntToStr ( BytesForWrite );
    ErrorMess( str.c_str(), 2 );
  }
  CloseHandle( hWrite );
}
//---------------------------------------------------------------------------
// ��������� ������������� ����������� ��������� ������
void TFileBuffer::StartSsdInit( char * fileName )
{
  int size = sizeof ( TSsd );
  // ���������������� ������
  SetNull( _ssd.BtArr, size );
  // ���������� ����
  MyStrCopy ( _ssd.Info.key, this->_key, __kei_length__ );
  // ���������� ��� �����
  MyStrCopy ( _ssd.Info.fileName, fileName, 256 );
  _ssd.Info.count = 0;
  _ssd.Info.Size.Lint = size;
  _ssd.Info.flags[0] = 0x55; // ������� ������������� ���������
}
//---------------------------------------------------------------------------
// �������� ������� ������������� ��������: ��� �� ��
void TFileBuffer::SsdNoPp()
{
  _ssd.Info.flags[0] = 0xAA; // ������� ������������� ���������
}
//---------------------------------------------------------------------------
// �������� ������� ������������� ��������: ��� ��
void TFileBuffer::SsdYesPp( char * fileName )
{
  // ���������� ��� �����
  MyStrCopy ( _ssd.Info.fileName, fileName, 256 );
  _ssd.Info.flags[0] = 0x55; // ������� ������������� ���������
}
//---------------------------------------------------------------------------
// "����������������" ���, ���� ��������� �����, ���� �������� ��� ���������
void TFileBuffer::SsdIncrement()
{
  if ( _ssd.Info.flags[1] == 1 )
  {
    _ssd.Info.flags[1] = 2; // �������� ��� ���������
    return;
  }
  if ( _ssd.Info.flags[1] == 2 )
  {
    _ssd.Info.flags[1] = 0; // ��������
    _ssd.Info.count = 0;
  }
  _ssd.Info.count++; // ����������������
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
// ��������� ���� ����������� ��������� ������ (���).
bool TFileBuffer::CheckKey()
{
  int keyLength = __kei_length__;
  for ( int i = 0, j = _length - keyLength; i < keyLength; i++, j++ )
  {
    if ( _btArrPtr[j] != _key[i] )
    {
      ErrorMess( "CheckKey(): ������ ��� ��������� �����", 2 );
      return false;
    }
  }
  // ���� ������
  int size1 = sizeof ( TSsd );
  CopyIsKeyFind ( // �������� ��� ������ ���������
      size1 );
  int size2 = _ssd.Info.Size.Lint;
  if ( size1 != size2 )
  {
    ErrorMess( "CheckKey(): ������ � ������� ���������� ����� ������", 2 );
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------
// �������� �� ������� ��������� �������������
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
    ErrorMess( "TFileBuffer::Intermediate(): ������������ ��������", 1 );
    return false;
}
//---------------------------------------------------------------------------
// ���������� ���� ����������� ��������� ������ (���), � ��������� ������ ����������
void TFileBuffer::SetKey()
{
    // ��������������� �� ������� 
}
//---------------------------------------------------------------------------
// ���� ���� ����������� ����� ������, �������� ��������� ������ ��
// ����� � ����������� ��������� ������
void TFileBuffer::CopyIsKeyFind(
    int btArrLength )
{
    for ( int i = 0, j = _length - btArrLength; i < btArrLength; i++, j++ )
    {
        _ssd.BtArr[i] = _btArrPtr[j];
    }
}
//---------------------------------------------------------------------------
// ���� ���� ����������� ����� ������, �������� ��������� ������ ��
// ����������� ��������� ������ � ����
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
// �������� �� ������
void TFileBuffer::ErrorMess( char * text, int Level )
{
    // ��������������� �� �������
  if ( _bfDebuf >= Level )
  {
    ShowMessage( text );
  }
}
//---------------------------------------------------------------------------
