//---------------------------------------------------------------------------
#pragma hdrstop
#include "FileDirectExtensive.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
class FileDirectExtensive::impl
{
public:
    TStringList * StrList;
};
//---------------------------------------------------------------------------
FileDirectExtensive::FileDirectExtensive()
{
    pImpl = new impl();
    pImpl->StrList = new TStringList();
    pImpl->StrList->Sorted = false;
    _fileIsReading = false;
}
//---------------------------------------------------------------------------
FileDirectExtensive::~FileDirectExtensive()
{
    if (pImpl != 0)
    {
        if ( pImpl->StrList != 0 )
        {
            delete pImpl->StrList;
        }
        delete pImpl;
    }
}
//---------------------------------------------------------------------------
bool FileDirectExtensive::LoadFromFile( const char * fileName )
{
    if ( CheckFileName( fileName ) == false )
    {
        _fileIsReading = false;    
        return false;
    }
    pImpl->StrList->LoadFromFile( fileName );
    _fileIsReading = true;
    return true;   
}
//---------------------------------------------------------------------------
bool FileDirectExtensive::SaveToFile( const char * fileName )
{
    //if ( CheckFileName( fileName ) == false )
    //{
    //    return false;
    //}
    pImpl->StrList->SaveToFile( fileName );
    return true;     
}
//---------------------------------------------------------------------------
bool FileDirectExtensive::DiaFileExists()
{
    return _fileIsReading;
}
//---------------------------------------------------------------------------
void FileDirectExtensive::ReadInteger (
    int * retVal, // [OUT]
    const char * paramName, // [IN]
    int min, int def, int max, // [IN]
    bool * flagError ) // [IN/OUT]
{
    if ( _fileIsReading == false )
    {
        *retVal = def;
        return;
    }
    AnsiString value = pImpl->StrList->Values[paramName]; // ������� �������� �� �����
    if ( value == "" )
    {
        *retVal = def;
        *flagError = true;
        return;
    }
    int x = value.ToIntDef( def );
    if ( x < min )
    {
        *flagError = true;
        x = min;
    }
    if ( x > max )
    {
        *flagError = true;
        x = max;
    }
    *retVal = x;
}
//---------------------------------------------------------------------------
void FileDirectExtensive::WriteInteger (
    int value, // [IN]
    const char * paramName) // [IN]
{
    int n = pImpl->StrList->Count; // ���������� ����� � ������
    int findNom = - 1;
    AnsiString find;
    AnsiString name = paramName;
    AnsiString text;
    text += paramName;
    text += "=";
    text += IntToStr( value ); // ��������� � AnsiString

    for ( int i = 0; i < n; i++ )
    {
        find = pImpl->StrList->Names[i];
        if ( find == name )
        {
            findNom = i; // ������ ������ � �������� �������
            break;
        }
    }
    if ( findNom >= 0 ) // �����, ��� ������
    {
        pImpl->StrList->Delete( findNom );
        pImpl->StrList->Insert( findNom, text ); // �������� �� �����
    }
    else
    {
        pImpl->StrList->Add( text );
    }
}
//---------------------------------------------------------------------------
void FileDirectExtensive::ReadByte (
    unsigned char * retVal, // [OUT]
    const char * paramName, // [IN]
    unsigned char min, unsigned char def, unsigned char max, // [IN]
    bool * flagError) // [IN/OUT]
{
    if ( _fileIsReading == false )
    {
        *retVal = def;
        return;
    }
    AnsiString value = pImpl->StrList->Values[paramName]; // ������� �������� �� �����
    if ( value == "" )
    {
        *retVal = def;
        *flagError = true;
        return;
    }
    int x = value.ToIntDef( def );
    if ( x < min )
    {
        *flagError = true;
        x = min;
    }
    if ( x > max )
    {
        *flagError = true;
        x = max;
    }
    *retVal = x;
}
//---------------------------------------------------------------------------
void FileDirectExtensive::ReadWord (
    unsigned short * retVal, // [OUT]
    const char * paramName, // [IN]
    unsigned short min, unsigned short def, unsigned short max, // [IN]
    bool * flagError) // [IN/OUT]
{
    if ( _fileIsReading == false )
    {
        *retVal = def;
        return;
    }
    AnsiString value = pImpl->StrList->Values[paramName]; // ������� �������� �� �����
    if ( value == "" )
    {
        *retVal = def;
        *flagError = true;
        return;
    }
    int x = value.ToIntDef( def );
    if ( x < min )
    {
        *flagError = true;
        x = min;
    }
    if ( x > max )
    {
        *flagError = true;
        x = max;
    }
    *retVal = x;
}
//---------------------------------------------------------------------------
void FileDirectExtensive::ReadBool(
    bool * retVal, // [OUT]
    const char * paramName, // [IN]
    bool def, // [IN]
    bool * flagError ) // [IN/OUT]
{
    if ( _fileIsReading == false )
    {
        *retVal = def;
        return;
    }
    AnsiString value = pImpl->StrList->Values[paramName]; // ������� �������� �� �����
    if ( value == "" )
    {
        *retVal = def;
        *flagError = true;
        return;
    }
    if ( value == "1" )
    {
        *retVal = true;
    }
    else
    {
        *retVal = false;
    }
}
//---------------------------------------------------------------------------
void FileDirectExtensive::WriteBool(
    bool value, // [IN]
    const char * paramName ) // [IN]
{
    int n = pImpl->StrList->Count; // ���������� ����� � ������
    int findNom = - 1;
    AnsiString find;
    AnsiString name = paramName;
    AnsiString text; // ��������� � AnsiString
    text = name;
    text += "=";
    if ( value )
    {
        text += "1";
    }
    else
    {
        text += "0";
    }
    for ( int i = 0; i < n; i++ )
    {
        find = pImpl->StrList->Names[i];
        if ( find == name )
        {
            findNom = i; // ������ ������ � �������� �������
            break;
        }
    }
    if ( findNom >= 0 ) // �����, ��� ������
    {
        pImpl->StrList->Delete( findNom );
        pImpl->StrList->Insert( findNom, text ); // �������� �� �����
    }
    else
    {
        pImpl->StrList->Add( text );
    }
}
//---------------------------------------------------------------------------
bool FileDirectExtensive::CheckFileName( const char * fileName )
{
    if ( FileExists( fileName ) == false )
    { // ���� ������ ����� �� ����������
        AnsiString fullFileName = ParamStr( 0 ); // ��� ����� (������ �������� ��������� ������)
        fullFileName = ExtractFileDir( fullFileName ); // �������, � ������� ��������� ����
        fullFileName += "\\";
        fullFileName += fileName;
        if ( FileExists( fullFileName ) == false )
        {  // ���� ������ ����� �� ����������
            return false; // �������� � �������
        }
    }
    return true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
