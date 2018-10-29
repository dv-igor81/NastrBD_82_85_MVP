//---------------------------------------------------------------------------
// ������ � ���� - ���� ������� �������
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Unit_82_FileDirect.h"
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <string.h>
#include <math.h>
#include <stdio.h>
//---------------------------------------------------------------------------
FileDirect::FileDirect() // �����������
{
  ;
}
//---------------------------------------------------------------------------
//���������� ����� � ������������� ������ �����
int FileDirect::ReadCount(const AnsiString FileName)
{
  if ( FileExists( FileName ) ) // ���� ����� ���� ����������
  {
    TStringList * strList = new TStringList;
    strList->LoadFromFile( FileName );
    int n = strList->Count; // ���������� ����� � ������
    delete strList;
    return n;
  }
  else // ���� ���� �� ����������
  {
    AnsiString filename = "���� " + FileName + " �� ����������";
    Application->MessageBox( filename.c_str(), "��������", MB_ICONSTOP );
    return 0;
  }
}
//---------------------------------------------------------------------------
// ������ �� ����� ����� ������ �����
int FileDirect::ReadStr(const AnsiString FileName, AnsiString * MasStr)
{
  if ( FileExists( FileName ) ) // ���� ����� ���� ����������
  {
    TStringList * strList = new TStringList;
    strList->LoadFromFile( FileName );
    int n = strList->Count; // ���������� ����� � ������
    for ( int i = 0; i < n; i++ )
    {
      MasStr[i] = strList->Strings[i];
    }
    delete strList;
    return n;
  }
  else // ���� ���� �� ����������
  {
    AnsiString filename = "���� " + FileName + " �� ����������";
    Application->MessageBox(filename.c_str(),"��������",MB_ICONSTOP);
    return 0;
  }
}
//---------------------------------------------------------------------------
// ������ �� ����� �������� �� Name (Name = ��������) - ���������� ��������
AnsiString FileDirect::ReadString(const AnsiString FileName,
    AnsiString Name,
    AnsiString Default
    )
{
  if ( FileExists( FileName ) ) // ���� ����� ���� ����������
  {
    AnsiString Value;
    TStringList * strList = new TStringList;
    strList->LoadFromFile( FileName );
    //==\\int n = strList->Count; // ���������� ����� � ������
    Value = strList->Values[Name]; // ������� �������� �� �����
    delete strList;

    if ( Value == "" )
    {
      Value = Default;
    }
    return Value;
  }
  else // ���� ���� �� ����������
  {
    return Default;
  }
}
//---------------------------------------------------------------------------
//������ � ���� �������� �� Name( Name=��������)
void FileDirect::WriteString(const AnsiString FileName,
    AnsiString Name,
    AnsiString Value
    )
{
  Value = Name + "=" + Value;
  TStringList * strList = new TStringList;
  if ( FileExists( FileName ) ) // ���� ����� ���� ����������
  {
    AnsiString str2;
    strList->Sorted = false;
    strList->LoadFromFile( FileName );
    strList->SaveToFile( FileName + "~" );
    int n = strList->Count; // ���������� ����� � ������
    int nom = -1;
    for ( int i = 0; i < n; i++ )
    {
      str2 = strList->Names[i];
      if ( str2 == Name )
      {
        nom = i; // ������ ������ � �������� �������
        break;
      }
    }
    if ( nom >= 0 ) // �����, ��� ������
    {
      strList->Delete(nom);
      strList->Insert(nom, Value); // �������� �� �����
    }
    else
    {
      strList->Add(Value); // �� ����� - �������� � ����� ������
    }
  }
  else // ���� ���� �� �����������
  {
    strList->Add(Value); // �� ����� - �������� � ����� ������
  }
  strList->CaseSensitive = true; // ���������������� � �������� ��� ����������
  // strList->Sorted = true; // ����������� �� �������� ����� ������� � ����
  strList->SaveToFile(FileName);
  delete strList;
}
//---------------------------------------------------------------------------
// ������ �� ����� �������� �� Name (Name = ��������) - ���������� ��������
bool FileDirect::ReadBool(const AnsiString FileName,
    AnsiString Name,
    bool Default
    )
{
  if ( FileExists( FileName ) ) // ���� ����� ���� ����������
  {
    AnsiString Value;
    TStringList * strList = new TStringList;
    strList->LoadFromFile(FileName);
    //==\\int n = strList->Count; // ���������� ����� � ������
    Value = strList->Values[Name]; // ������� �������� �� �����
    delete strList;
    if ( Value == "" )
    {
      return Default;
    }
    if ( Value == "1" )
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else // ���� ���� �� ����������
  {
    return Default;
  }
}
//---------------------------------------------------------------------------
// ������ � ���� �������� �� Name (Name = ��������)
void FileDirect::WriteBool(const AnsiString FileName,
    AnsiString Name,
    bool boolValue
    )
{
  AnsiString Value;
  if ( boolValue )
  {
    Value = "1"; // ��������� � AnsiString
  }
  else
  {
    Value = "0";
  }
  Value = Name + "=" + Value;
  TStringList * strList = new TStringList;

  if ( FileExists( FileName ) ) // ���� ����� ���� ����������
  {
    AnsiString str2;
    strList->Sorted = false;
    strList->LoadFromFile(FileName);
    strList->SaveToFile( FileName + "~" );
    int n = strList->Count; // ���������� ����� � ������
    int nom = -1;
    for ( int i = 0; i < n; i++ )
    {
      str2 = strList->Names[i];
      if ( str2 == Name )
      {
        nom = i; // ������ ������ � �������� �������
        break;
      }
    }
    if ( nom >= 0 ) // �����, ��� ������
    {
      strList->Delete(nom);
      strList->Insert(nom, Value); // �������� �� �����
    }
    else
    {
      strList->Add(Value); // �� ����� - �������� � ����� ������
    }
  }
  else // ���� ���� �� �����������
  {
    strList->Add(Value); // �� ����� - �������� � ����� ������
  }
  strList->CaseSensitive = true; // ���������������� � �������� ��� ����������
  // strList->Sorted = true; // ����������� �� �������� ����� ������� � ����
  strList->SaveToFile(FileName);
  delete strList;
}
//---------------------------------------------------------------------------
// ������ �� ����� �������� �� Name (Name = ��������) - ���������� ��������
int FileDirect::ReadInteger(const AnsiString FileName,
    AnsiString Name,
    int Default
    )
{
  if ( FileExists( FileName ) ) // ���� ����� ���� ����������
  {
    AnsiString Value;
    TStringList * strList = new TStringList;
    strList->LoadFromFile(FileName);
    //==\\int n = strList->Count; // ���������� ����� � ������
    Value = strList->Values[Name]; // ������� �������� �� �����
    delete strList;
    if ( Value == "" )
    {
      return Default;
    }
    return Value.ToIntDef(0);
  }
  else // ���� ���� �� ����������
  {
    return Default;
  }
}
//---------------------------------------------------------------------------
// ������ � ���� �������� �� Name (Name = ��������)
void FileDirect::WriteInteger(const AnsiString FileName,
    AnsiString Name,
    int intValue
    )
{
  AnsiString Value;
  Value = IntToStr(intValue); // ��������� � AnsiString
  Value = Name + "=" + Value;
  TStringList * strList = new TStringList;
  if ( FileExists( FileName ) ) // ���� ����� ���� ����������
  {
    AnsiString str2;
    strList->Sorted = false;
    strList->LoadFromFile(FileName);
    strList->SaveToFile( FileName + "~" );
    int n = strList->Count; // ���������� ����� � ������
    int nom = -1;
    for ( int i = 0; i < n; i++ )
    {
      str2 = strList->Names[i];
      if ( str2 == Name )
      {
        nom = i; // ������ ������ � �������� �������
        break;
      }
    }
    if ( nom >= 0 ) // �����, ��� ������
    {
      strList->Delete(nom);
      strList->Insert(nom, Value); // �������� �� �����
    }
    else
    {
      strList->Add(Value); // �� ����� - �������� � ����� ������}
    }
  }
  else // ���� ���� �� �����������
  {
    strList->Add(Value); // �� ����� - �������� � ����� ������
  }
  strList->CaseSensitive = true; // ���������������� � �������� ��� ����������
  // strList->Sorted = true; // ����������� �� �������� ����� ������� � ����
  strList->SaveToFile(FileName);
  delete strList;
}
//---------------------------------------------------------------------------
// ������ �� ����� �������� �� Name (Name = ��������) - ���������� ��������
unsigned long  FileDirect::ReadUnsignedLong(const AnsiString FileName,
    AnsiString Name,
    unsigned long Default
    )
{
  if ( FileExists( FileName ) ) // ���� ����� ���� ����������
  {
    AnsiString Value;
    TStringList * strList = new TStringList;
    strList->LoadFromFile(FileName);
    //==\\int n = strList->Count; // ���������� ����� � ������
    Value = strList->Values[Name]; // ������� �������� �� �����
    delete strList;
    if ( Value == "" )
    {
      return Default;
    }
    // return Value.ToIntDef(0);
    return atol(Value.c_str());
  }
  else // ���� ���� �� ����������
  {
    return Default;
  }
}
//---------------------------------------------------------------------------
// ������ � ���� �������� �� Name (Name = ��������)
void FileDirect::WriteUnsignedLong(const AnsiString FileName,
    AnsiString Name,
    unsigned long intValue
    )
{
  AnsiString Value;
  char buf[12];
  sprintf(buf, "%11u", intValue);
  // Value = (AnsiString)buf;
  Value = IntToStr(intValue);
  Value = Name + "=" + Value;
  TStringList * strList = new TStringList;
  if ( FileExists( FileName ) ) // ���� ����� ���� ����������
  {
    AnsiString str2;
    strList->Sorted = false;
    strList->LoadFromFile(FileName);
    strList->SaveToFile( FileName + "~" );
    int n = strList->Count; // ���������� ����� � ������
    int nom = -1;
    for ( int i = 0; i < n; i++ )
    {
      str2 = strList->Names[i];
      if ( str2 == Name )
      {
        nom = i; // ������ ������ � �������� �������
        break;
      }
    }
    if ( nom >= 0) // �����, ��� ������
    {
      strList->Delete(nom);
      strList->Insert(nom, Value); // �������� �� �����
    }
    else
    {
      strList->Add(Value);// �� ����� - �������� � ����� ������
    }
  }
  else // ���� ���� �� �����������
  {
    strList->Add(Value); // �� ����� - �������� � ����� ������
  }
  strList->CaseSensitive = true; // ���������������� � �������� ��� ����������
  // strList->Sorted = true; // ����������� �� �������� ����� ������� � ����
  strList->SaveToFile(FileName);
  delete strList;
}
//---------------------------------------------------------------------------
// ������ �� ����� �������� �� Name (Name = ��������) - ���������� ��������
float FileDirect::ReadFloat(const AnsiString FileName,
    AnsiString Name,
    float Default
    )
{
  if ( FileExists( FileName ) ) // ���� ����� ���� ����������
  {
    AnsiString Value;
    TStringList * strList = new TStringList;
    strList->LoadFromFile(FileName);
    //==\\int n = strList->Count; // ���������� ����� � ������
    Value = strList->Values[Name]; // ������� �������� �� �����
    delete strList;
    if ( Value == "" )
    {
      return Default;
    }
    return Value.ToDouble();
  }
  else // ���� ���� �� ����������
  {
    return Default;
  }
}
//---------------------------------------------------------------------------
// ������ � ���� �������� �� Name (Name = ��������)
void  FileDirect::WriteFloat(const AnsiString FileName,
    AnsiString Name,
    float floatValue
    )
{
  AnsiString Value;
  Value = FormatFloat("0.000", floatValue); // ��������� � AnsiString
  if ( fabs(floatValue) < 0.01 )
  {
    Value = FloatToStrF(floatValue, ffExponent, 5, 10); // ������� ������
  }
  Value = Name + "=" + Value;
  TStringList * strList = new TStringList;
  if ( FileExists( FileName ) ) // ���� ����� ���� ����������
  {
    AnsiString str2;
    strList->Sorted = false;
    strList->LoadFromFile(FileName);
    strList->SaveToFile( FileName + "~" );
    int n = strList->Count; // ���������� ����� � ������
    int nom = -1;
    for ( int i = 0; i < n; i++ )
    {
      str2 = strList->Names[i];
      if ( str2 == Name )
      {
        nom = i; // ������ ������ � �������� �������
        break;
      }
    }
    if ( nom >= 0 ) // �����, ��� ������
    {
      strList->Delete(nom);
      strList->Insert(nom, Value); // �������� �� �����
    }
    else
    {
      strList->Add(Value); // �� ����� - �������� � ����� ������
    }
  }
  else // ���� ���� �� �����������
  {
    strList->Add(Value); // �� ����� - �������� � ����� ������
  }
  strList->CaseSensitive = true; // ���������������� � �������� ��� ����������
  // strList->Sorted = true; // ����������� �� �������� ����� ������� � ����
  strList->SaveToFile(FileName);
  delete strList;
}
//---------------------------------------------------------------------------
// �������� ���� - ������� ��� ������
void  FileDirect::ClearFile(const AnsiString FileName)
{
  if ( FileExists( FileName ) ) // ���� ����� ���� ����������
  {
    TStringList * strList = new TStringList;
    strList->LoadFromFile(FileName);
    strList->Clear(); // �������� ������
    strList->SaveToFile(FileName); // �������� ������� � ����
    delete strList;
  }
  else // ���� ���� �� ����������
  {
    AnsiString filename = "���� " + FileName + " �� ����������";
    Application->MessageBox(filename.c_str(), "��������", MB_ICONSTOP);
  }
}
//---------------------------------------------------------------------------
void  FileDirect::ClearString(const AnsiString FileName,
    AnsiString Name
    )
{
  TStringList * strList = new TStringList;
  if ( FileExists( FileName ) ) // ���� ����� ���� ����������
  {
    AnsiString str2;
    strList->Sorted = false;
    strList->LoadFromFile(FileName);
    strList->SaveToFile( FileName + "~" );
    int n = strList->Count; // ���������� ����� � ������
    int nom = -1;
    for ( int i = 0; i < n; i++ )
    {
      str2 = strList->Names[i];
      if ( str2 == Name )
      {
        nom = i; // ������ ������ � �������� �������
        break;
      }
    }
    if ( nom >= 0 ) // �����, ��� ������
    {
      strList->Delete(nom);
    }
  }
  else // ���� ���� �� �����������
  {
    delete strList;
    return;
  }
  strList->CaseSensitive = true; // ���������������� � �������� ��� ����������
  // strList->Sorted = true; // ����������� �� �������� ����� ������� � ����
  strList->SaveToFile(FileName);
  delete strList;
}
//---------------------------------------------------------------------------
FileDirect::~FileDirect() // ����������
{
  ;
}
//---------------------------------------------------------------------------
/*
�������
//�������� ����� ���� � �������� ���� ����������

fD.WriteString("c:\\filestr2.txt","���1","����1");//��������, ��� ��������
fD.WriteString("c:\\filestr2.txt","���2","����2");//��������, ��� ��������
fD.WriteString("c:\\filestr2.txt","���4","����4");//��������, ��� ��������
fD.WriteString("c:\\filestr2.txt","���3","����3");//��������, ��� ��������

//fD.WriteBool("c:\\filestr.txt","Bool",false);//��������, ��� ��������
//fD.WriteInteger("c:\\filestr.txt","Integer",-35);//��������, ��� ��������
//fD.WriteFloat("c:\\filestr.txt","Float",-2.35);//��������, ��� ��������

//��. ����� � ����� ? ���� ��� ����� - ��������� � n=0
int n=fD.ReadCount("c:\\filestr.txt");
AnsiString MasStr[100];
//������� ���� ����(n2-���������� �����)  ���� ��� ����� - ��������� � n2=0
int n2=fD.ReadStr("c:\\filestr.txt",MasStr);

//����������� ��� �������
fD.WriteString("c:\\filestr.txt","���1","����2");//��������, ��� ��������
fD.WriteString("c:\\filestr.txt","���0","�����2");

//������� �������� �� �����
AnsiString str=fD.ReadString("c:\\filestr.txt","���10","Cdtnbr");//���� ��� ����� - ��������� � str=NULL
bool b=fD.ReadBool("c:\\filestr.txt","Bool",true);//���� ��� ����� - ��������� � b=false
int i=fD.ReadInteger("c:\\filestr.txt","Integer",33);//���� ��� ����� - ��������� � i=0
float f=fD.ReadFloat("c:\\filestr.txt","Float",10.56);//���� ��� ����� - ��������� � f=0

//������� ���� ������
fD.ClearFile("c:\\filestr.txt");
*/
