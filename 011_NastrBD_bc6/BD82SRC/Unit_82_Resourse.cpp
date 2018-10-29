//---------------------------------------------------------------------------
//#pragma hdrstop
#include "Unit_82_Resourse.h"
//---------------------------------------------------------------------------
//#pragma package(smart_init)
#pragma resource "DllInpout32.res"

TResourceStream * DllResStream;
TFileStream * DllFileStream;
//TMemoryStream * DllMemStream;

void DiaFunktionRes( )
{
  if ( FileExists( "inpout32.dll" ) == false ) // ������ ����� ���
  {
    SetLastError( 0 );
    try
    {
      DllResStream = new TResourceStream( 0, "inpout32_DLL", RT_RCDATA ); // ��������� ���������� dll � �����
    }
    catch ( ... )
    {
      Application->MessageBoxA(SysErrorMessage( GetLastError() ).c_str(), "������", MB_ICONSTOP);
    }
    SetLastError( 0 );
    try
    {
      DllFileStream  = new TFileStream( "inpout32.dll", fmCreate );
    }
    catch ( ... )
    {
      Application->MessageBoxA(SysErrorMessage( GetLastError() ).c_str(), "������", MB_ICONSTOP);
    }
    SetLastError( 0 );
    //==\\DllFileStream  = new TFileStream( "inpout32.dll", fmOpenRead | fmShareDenyWrite );
    try
    {
      DllResStream->SaveToStream( DllFileStream );
    }
    catch ( ... )
    {
      Application->MessageBoxA(SysErrorMessage( GetLastError() ).c_str(), "������", MB_ICONSTOP);
    }
    DllFileStream->Free();
    DllResStream->Free();
  }
}