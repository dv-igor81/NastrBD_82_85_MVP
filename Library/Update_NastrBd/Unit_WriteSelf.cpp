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
// �����������
TWriteSelf::TWriteSelf() :
    _fileBufSelf ( "DIAVNIIA" )  // ����
    ,_fileBufUpdate ( "DIAVNIIA" )  // ����
    ,_flagDeystviya ( 0 )
    ,_bfDebuf( 1 )
    ,_bfReady( false ) // ���� ���������� (��� ������ ��������) 
{
}
//---------------------------------------------------------------------------
// ����������
TWriteSelf::~TWriteSelf()
{
}
//---------------------------------------------------------------------------
// ��� �: 1 - ��, 2 - ��, 3 - ��, 4 - ���� �� ������ (������ ������)
// �� - ��������� ���������, ����������� �������������, ������ � ��������� ������������� ���������
// �� - ������������� ���������, ����������� ��������� ����������, ������ � ��������� ������������� ���������
// �� - ������������� ���������, ����������� ������������� ����������, ������ �� ������ � �� ���������
int TWriteSelf::WhoAmI() // ��������� ���� � ������
{
    fileName = ParamStr( 0 ); // ��� �������� �����
    return WhoAmFile( fileName, _fileBufSelf );
}
//---------------------------------------------------------------------------
int TWriteSelf::WhoAmFile(
  AnsiString fileNameLocal,
  TFileBuffer & fileBufLocal)
{
    if ( fileBufLocal.ReadFileToSelf( fileNameLocal.c_str() ) != 0 ) // ��������� ���� � ������
    {
      return -1; // ������ ������
    }

    if ( fileBufLocal.CheckKey() )
    {
        Mess( "TWriteSelf::WhoAmI(): ���� ������", 2 );
        // �������� �� ������� ��������� ������������� ����������
        if ( fileBufLocal.Intermediate() ) // Intermediate program
        {
            Mess( "TWriteSelf::WhoAmI(): �� - ������������� ���������", 2 );
            InfofillName = fileBufLocal.GetInfofillName();
            return 2; // �� - ������������� ���������
        }
        else
        { // ��������� �� �������� �������������
          // ���� ���� "������������� ���������" ������, ������,
          // ������� ��������� - "������������� ���������". ����� - "��������� ���������"
            if ( FileExists( GetNewFileName() ) )
            {
                Mess( "TWriteSelf::WhoAmI(): �� - ������������� ���������", 2 );
                return 3; // �� - ������������� ���������
            }
            else
            {
                Mess( "TWriteSelf::WhoAmI(): �� - ��������� ���������", 2 );
                return 1; // �� - ��������� ���������
            }
        }
    }
    else
    {
        Mess( "TWriteSelf::WhoAmI(): ���� �� ������", 2 );
        return 4; // ���� �� ������ (������ ������)
    }
}
//---------------------------------------------------------------------------
// ����� ���������
int TWriteSelf::StartProgramm()
{
    int deystvie = WhoAmI();

    switch ( deystvie )
    {
    case 1: // 1 - ��
        _flagDeystviya = 1;
        break;
    case 2: // 2 - ��
        _flagDeystviya = 2;
        break;
    case 3: // 3 - ��
        _flagDeystviya = 3;
        break;
    case 4: // 4 - ���� �� ������ (������ ������)
        _flagDeystviya = 4;
        break;
    default: // ������������� ��������
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
    Mess( "TWriteSelf::WhoAmI(): ��� ���� �� ��������", 1 );
    return -1;
  }
//===========================================================================
  int curVerPo = 12; // v4.29.1 (12)
//===========================================================================  
  int verPo = _fileBufSelf.GetPoVersiya();
  if (verPo != curVerPo)
  {
     Mess( "TWriteSelf::WhoAmI(): ���������� ������", 1 );
    _fileBufSelf.SetPoVersiya(curVerPo); // ������ ���������
    return 2;
  }
  errCod = _fileBufUpdate.ReadFileToSelf( remoteFileNameFake.c_str() );
  if ( errCod != 0 )
  {
    //Mess( "��������� ���� �� �������� (�������� �������� fileserver ����������)", 1 );
    errCod = _fileBufUpdate.ReadFileToSelf( remFileName.c_str() );
    if (errCod != 0)
    {
      //Mess( "��������� ���� �� �������� (�������� fileserver ����������)", 1 );
      return 3; // �� ����� �����������
    }
  }
  if ( _fileBufUpdate.CheckKey() == false )
  {
    Mess( "_fileBufUpdate.CheckKey() == false", 1 );
  }
  int NewVersion = _fileBufUpdate.GetPoVersiya();
  if ( NewVersion == -1 )
  {
    //Mess( "TWriteSelf::WhoAmI(): ������ - NewVersion == -1", 2 );
    return 1; // ���� �����������
  }
  if ( NewVersion > curVerPo )
  {
    //sprintf(msfFormated,
    //  "TWriteSelf::WhoAmI(): ������ - NewVersion (%d) > curVerPo (%d)",
    //  NewVersion, curVerPo);
    //Mess( msfFormated, 2 );
    return 1; // ���� �����������
  }
  //sprintf(msfFormated,
  //  "TWriteSelf::WhoAmI(): NewVersion  = %d END curVerPo = %d",
  //  NewVersion, curVerPo);
  //Mess( msfFormated, 2 );
  return 0; // �� ����� �����������
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
// �������� ����
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
  case 1: // 1 - ��
    // ������� ���� ������������� ���������
    fileBufLocal.SsdYesPp( fileName.c_str() ); // ��� �������� ������� ��
    //
    size1 = sizeof ( TSsd );
    fileBufLocal.CopyIsKeyFindRevers ( size1 ); // �������� � ���� ��� ������ ���������

    newFileName = GetNewFileName();
    fileBufLocal.WriteFileFromSelf( newFileName.c_str() ); // �������� ������������� ����
    break;
  case 2: // 2 - ��
    // ������� ���� ������������� ���������
    fileBufLocal.SsdNoPp(); // ��� �������� ������� ��
    // "����������������" ���, ���� ��������� �����, ���� �������� ��� ���������
    fileBufLocal.SsdIncrement(); // ��� ���������������� ��������

    size1 = sizeof ( TSsd );
    fileBufLocal.CopyIsKeyFindRevers ( size1 ); // �������� � ���� ��� ������ ���������

    fileBufLocal.WriteFileFromSelf( InfofillName.c_str() ); // �������� ���� ������������� ���������
    break;
  //case 3: // 3 - ��
  //  // ������ ��������� �� �����
  //  break;
  case 4: // 4 - ���� �� ������ (������ ������)
    // ������� ���� ������������� ���������
    fileBufLocal.StartSsdInit( fileName.c_str() ); // ������������������� ���
    newFileName = GetNewFileName();
    fileBufLocal.WriteSelfSsd( newFileName.c_str() ); // �������� ������������� ����
    break;
  }
}
//---------------------------------------------------------------------------
void TWriteSelf::MyWinExec()
{
  AnsiString fName;
  switch ( _flagDeystviya )
  {
  case 1: // 1 - ��
  case 4: // 4 - ���� �� ������ (������ ������)
    fName = GetNewFileName();
    break;
  case 2: // 2 - ��
    fName = InfofillName;
    break;
  }
  int Code = WinExec( fName.c_str(), SW_RESTORE );
  if ( Code < 32 ) // ���� ������� ����������� �������, �������� ������������� �������� - ������ ��� 31.
  {
    int ErrCode = GetLastError();
    if ( ErrCode != 0 )
    {
      Mess( "MyWinExec(): Error", 1 );
    }
  }
}
//---------------------------------------------------------------------------
// ���������� ���� ���������� (��� ������ ��������)
void TWriteSelf::SetReady()
{
  _bfReady = true;
}
//---------------------------------------------------------------------------
// ���� ������� �� ����� ��������
bool TWriteSelf::Reset()
{
  return Reset(_fileBufSelf);
}
//---------------------------------------------------------------------------
// �������� ������� �������� ���������
bool TWriteSelf::Reset(TFileBuffer & fileBufLocal)
{
  if ( ! _bfReady )
  {
    return false; // ��������
  }

  // ������� ���� ������������� ���������
  fileBufLocal.SsdYesPp( fileName.c_str() ); // ��� �������� ������� ��
  fileBufLocal.SsdReset(); // ��� ������� �� ����� ��������

  int size1 = sizeof ( TSsd );
  fileBufLocal.CopyIsKeyFindRevers ( size1 ); // �������� � ���� ��� ������ ���������

  AnsiString newFileName = GetNewFileName();
  fileBufLocal.WriteFileFromSelf( newFileName.c_str() ); // �������� ������������� ����

  _flagDeystviya = 1; // 1 - ��
  return true; // ������
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
