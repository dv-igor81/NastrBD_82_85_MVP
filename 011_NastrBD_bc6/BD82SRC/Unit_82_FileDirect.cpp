//---------------------------------------------------------------------------
// Запись в файл - типа прямого доступа
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
FileDirect::FileDirect() // конструктор
{
  ;
}
//---------------------------------------------------------------------------
//Количество строк в запрашиваемом списке строк
int FileDirect::ReadCount(const AnsiString FileName)
{
  if ( FileExists( FileName ) ) // если такой файл существует
  {
    TStringList * strList = new TStringList;
    strList->LoadFromFile( FileName );
    int n = strList->Count; // количество строк в списке
    delete strList;
    return n;
  }
  else // если файл не существует
  {
    AnsiString filename = "Файл " + FileName + " не существует";
    Application->MessageBox( filename.c_str(), "Внимание", MB_ICONSTOP );
    return 0;
  }
}
//---------------------------------------------------------------------------
// Чтение из файла всего списка строк
int FileDirect::ReadStr(const AnsiString FileName, AnsiString * MasStr)
{
  if ( FileExists( FileName ) ) // если такой файл существует
  {
    TStringList * strList = new TStringList;
    strList->LoadFromFile( FileName );
    int n = strList->Count; // количество строк в списке
    for ( int i = 0; i < n; i++ )
    {
      MasStr[i] = strList->Strings[i];
    }
    delete strList;
    return n;
  }
  else // если файл не существует
  {
    AnsiString filename = "Файл " + FileName + " не существует";
    Application->MessageBox(filename.c_str(),"Внимание",MB_ICONSTOP);
    return 0;
  }
}
//---------------------------------------------------------------------------
// Чтение из файла значения по Name (Name = Значение) - возвращает значение
AnsiString FileDirect::ReadString(const AnsiString FileName,
    AnsiString Name,
    AnsiString Default
    )
{
  if ( FileExists( FileName ) ) // если такой файл существует
  {
    AnsiString Value;
    TStringList * strList = new TStringList;
    strList->LoadFromFile( FileName );
    //==\\int n = strList->Count; // количество строк в списке
    Value = strList->Values[Name]; // Получим значение по имени
    delete strList;

    if ( Value == "" )
    {
      Value = Default;
    }
    return Value;
  }
  else // если файл не существует
  {
    return Default;
  }
}
//---------------------------------------------------------------------------
//Запись в файл значения по Name( Name=Значение)
void FileDirect::WriteString(const AnsiString FileName,
    AnsiString Name,
    AnsiString Value
    )
{
  Value = Name + "=" + Value;
  TStringList * strList = new TStringList;
  if ( FileExists( FileName ) ) // если такой файл существует
  {
    AnsiString str2;
    strList->Sorted = false;
    strList->LoadFromFile( FileName );
    strList->SaveToFile( FileName + "~" );
    int n = strList->Count; // количество строк в списке
    int nom = -1;
    for ( int i = 0; i < n; i++ )
    {
      str2 = strList->Names[i];
      if ( str2 == Name )
      {
        nom = i; // индекс строки с заданным номером
        break;
      }
    }
    if ( nom >= 0 ) // нашли, что искали
    {
      strList->Delete(nom);
      strList->Insert(nom, Value); // Заменили на новое
    }
    else
    {
      strList->Add(Value); // не нашли - добавили в конец списка
    }
  }
  else // если файл не существовал
  {
    strList->Add(Value); // не нашли - добавили в конец списка
  }
  strList->CaseSensitive = true; // чувствительность к регистру при сортировке
  // strList->Sorted = true; // отсортируем по алфавиту перед записью в файл
  strList->SaveToFile(FileName);
  delete strList;
}
//---------------------------------------------------------------------------
// Чтение из файла значения по Name (Name = Значение) - возвращает значение
bool FileDirect::ReadBool(const AnsiString FileName,
    AnsiString Name,
    bool Default
    )
{
  if ( FileExists( FileName ) ) // если такой файл существует
  {
    AnsiString Value;
    TStringList * strList = new TStringList;
    strList->LoadFromFile(FileName);
    //==\\int n = strList->Count; // количество строк в списке
    Value = strList->Values[Name]; // получим значение по имени
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
  else // если файл не существует
  {
    return Default;
  }
}
//---------------------------------------------------------------------------
// Запись в файл значения по Name (Name = Значение)
void FileDirect::WriteBool(const AnsiString FileName,
    AnsiString Name,
    bool boolValue
    )
{
  AnsiString Value;
  if ( boolValue )
  {
    Value = "1"; // переводим в AnsiString
  }
  else
  {
    Value = "0";
  }
  Value = Name + "=" + Value;
  TStringList * strList = new TStringList;

  if ( FileExists( FileName ) ) // если такой файл существует
  {
    AnsiString str2;
    strList->Sorted = false;
    strList->LoadFromFile(FileName);
    strList->SaveToFile( FileName + "~" );
    int n = strList->Count; // количество строк в списке
    int nom = -1;
    for ( int i = 0; i < n; i++ )
    {
      str2 = strList->Names[i];
      if ( str2 == Name )
      {
        nom = i; // индекс строки с заданным номером
        break;
      }
    }
    if ( nom >= 0 ) // нашли, что искали
    {
      strList->Delete(nom);
      strList->Insert(nom, Value); // заменили на новое
    }
    else
    {
      strList->Add(Value); // не нашли - добавили в конец списка
    }
  }
  else // если файл не существовал
  {
    strList->Add(Value); // не нашли - добавили в конец списка
  }
  strList->CaseSensitive = true; // чувствительность к регистру при сортировке
  // strList->Sorted = true; // отсортируем по алфавиту перед записью в файл
  strList->SaveToFile(FileName);
  delete strList;
}
//---------------------------------------------------------------------------
// Чтение из файла значения по Name (Name = Значение) - возвращает значение
int FileDirect::ReadInteger(const AnsiString FileName,
    AnsiString Name,
    int Default
    )
{
  if ( FileExists( FileName ) ) // если такой файл существует
  {
    AnsiString Value;
    TStringList * strList = new TStringList;
    strList->LoadFromFile(FileName);
    //==\\int n = strList->Count; // количество строк в списке
    Value = strList->Values[Name]; // Получим значение по имени
    delete strList;
    if ( Value == "" )
    {
      return Default;
    }
    return Value.ToIntDef(0);
  }
  else // если файл не существует
  {
    return Default;
  }
}
//---------------------------------------------------------------------------
// Запись в файл значения по Name (Name = Значение)
void FileDirect::WriteInteger(const AnsiString FileName,
    AnsiString Name,
    int intValue
    )
{
  AnsiString Value;
  Value = IntToStr(intValue); // переводим в AnsiString
  Value = Name + "=" + Value;
  TStringList * strList = new TStringList;
  if ( FileExists( FileName ) ) // если такой файл существует
  {
    AnsiString str2;
    strList->Sorted = false;
    strList->LoadFromFile(FileName);
    strList->SaveToFile( FileName + "~" );
    int n = strList->Count; // количество строк в списке
    int nom = -1;
    for ( int i = 0; i < n; i++ )
    {
      str2 = strList->Names[i];
      if ( str2 == Name )
      {
        nom = i; // индекс строки с заданным номером
        break;
      }
    }
    if ( nom >= 0 ) // нашли, что искали
    {
      strList->Delete(nom);
      strList->Insert(nom, Value); // Заменили на новое
    }
    else
    {
      strList->Add(Value); // не нашли - добавили в конец списка}
    }
  }
  else // если файл не существовал
  {
    strList->Add(Value); // не нашли - добавили в конец списка
  }
  strList->CaseSensitive = true; // чувствительность к регистру при сортировке
  // strList->Sorted = true; // отсортируем по алфавиту перед записью в файл
  strList->SaveToFile(FileName);
  delete strList;
}
//---------------------------------------------------------------------------
// Чтение из файла значения по Name (Name = Значение) - возвращает значение
unsigned long  FileDirect::ReadUnsignedLong(const AnsiString FileName,
    AnsiString Name,
    unsigned long Default
    )
{
  if ( FileExists( FileName ) ) // если такой файл существует
  {
    AnsiString Value;
    TStringList * strList = new TStringList;
    strList->LoadFromFile(FileName);
    //==\\int n = strList->Count; // количество строк в списке
    Value = strList->Values[Name]; // Получим значение по имени
    delete strList;
    if ( Value == "" )
    {
      return Default;
    }
    // return Value.ToIntDef(0);
    return atol(Value.c_str());
  }
  else // если файл не существует
  {
    return Default;
  }
}
//---------------------------------------------------------------------------
// Запись в файл значения по Name (Name = Значение)
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
  if ( FileExists( FileName ) ) // если такой файл существует
  {
    AnsiString str2;
    strList->Sorted = false;
    strList->LoadFromFile(FileName);
    strList->SaveToFile( FileName + "~" );
    int n = strList->Count; // количество строк в списке
    int nom = -1;
    for ( int i = 0; i < n; i++ )
    {
      str2 = strList->Names[i];
      if ( str2 == Name )
      {
        nom = i; // индекс строки с заданным номером
        break;
      }
    }
    if ( nom >= 0) // нашли, что искали
    {
      strList->Delete(nom);
      strList->Insert(nom, Value); // Заменили на новое
    }
    else
    {
      strList->Add(Value);// не нашли - добавили в конец списка
    }
  }
  else // если файл не существовал
  {
    strList->Add(Value); // не нашли - добавили в конец списка
  }
  strList->CaseSensitive = true; // чувствительность к регистру при сортировке
  // strList->Sorted = true; // отсортируем по алфавиту перед записью в файл
  strList->SaveToFile(FileName);
  delete strList;
}
//---------------------------------------------------------------------------
// Чтение из файла значения по Name (Name = Значение) - возвращает значение
float FileDirect::ReadFloat(const AnsiString FileName,
    AnsiString Name,
    float Default
    )
{
  if ( FileExists( FileName ) ) // если такой файл существует
  {
    AnsiString Value;
    TStringList * strList = new TStringList;
    strList->LoadFromFile(FileName);
    //==\\int n = strList->Count; // количество строк в списке
    Value = strList->Values[Name]; // Получим значение по имени
    delete strList;
    if ( Value == "" )
    {
      return Default;
    }
    return Value.ToDouble();
  }
  else // если файл не существует
  {
    return Default;
  }
}
//---------------------------------------------------------------------------
// Запись в файл значения по Name (Name = Значение)
void  FileDirect::WriteFloat(const AnsiString FileName,
    AnsiString Name,
    float floatValue
    )
{
  AnsiString Value;
  Value = FormatFloat("0.000", floatValue); // переводим в AnsiString
  if ( fabs(floatValue) < 0.01 )
  {
    Value = FloatToStrF(floatValue, ffExponent, 5, 10); // научный формат
  }
  Value = Name + "=" + Value;
  TStringList * strList = new TStringList;
  if ( FileExists( FileName ) ) // если такой файл существует
  {
    AnsiString str2;
    strList->Sorted = false;
    strList->LoadFromFile(FileName);
    strList->SaveToFile( FileName + "~" );
    int n = strList->Count; // количество строк в списке
    int nom = -1;
    for ( int i = 0; i < n; i++ )
    {
      str2 = strList->Names[i];
      if ( str2 == Name )
      {
        nom = i; // индекс строки с заданным номером
        break;
      }
    }
    if ( nom >= 0 ) // нашли, что искали
    {
      strList->Delete(nom);
      strList->Insert(nom, Value); // Заменили на новое
    }
    else
    {
      strList->Add(Value); // не нашли - добавили в конец списка
    }
  }
  else // если файл не существовал
  {
    strList->Add(Value); // не нашли - добавили в конец списка
  }
  strList->CaseSensitive = true; // чувствительность к регистру при сортировке
  // strList->Sorted = true; // отсортируем по алфавиту перед записью в файл
  strList->SaveToFile(FileName);
  delete strList;
}
//---------------------------------------------------------------------------
// Почистим файл - сделаем его пустым
void  FileDirect::ClearFile(const AnsiString FileName)
{
  if ( FileExists( FileName ) ) // если такой файл существует
  {
    TStringList * strList = new TStringList;
    strList->LoadFromFile(FileName);
    strList->Clear(); // очистили список
    strList->SaveToFile(FileName); // записали пустоту в файл
    delete strList;
  }
  else // если файл не существует
  {
    AnsiString filename = "Файл " + FileName + " не существует";
    Application->MessageBox(filename.c_str(), "Внимание", MB_ICONSTOP);
  }
}
//---------------------------------------------------------------------------
void  FileDirect::ClearString(const AnsiString FileName,
    AnsiString Name
    )
{
  TStringList * strList = new TStringList;
  if ( FileExists( FileName ) ) // если такой файл существует
  {
    AnsiString str2;
    strList->Sorted = false;
    strList->LoadFromFile(FileName);
    strList->SaveToFile( FileName + "~" );
    int n = strList->Count; // количество строк в списке
    int nom = -1;
    for ( int i = 0; i < n; i++ )
    {
      str2 = strList->Names[i];
      if ( str2 == Name )
      {
        nom = i; // индекс строки с заданным номером
        break;
      }
    }
    if ( nom >= 0 ) // нашли, что искали
    {
      strList->Delete(nom);
    }
  }
  else // если файл не существовал
  {
    delete strList;
    return;
  }
  strList->CaseSensitive = true; // чувствительность к регистру при сортировке
  // strList->Sorted = true; // отсортируем по алфавиту перед записью в файл
  strList->SaveToFile(FileName);
  delete strList;
}
//---------------------------------------------------------------------------
FileDirect::~FileDirect() // деструктор
{
  ;
}
//---------------------------------------------------------------------------
/*
ПРИМЕРЫ
//создадим новый файл и поместим туда информацию

fD.WriteString("c:\\filestr2.txt","Имя1","Лена1");//заменить, или добавить
fD.WriteString("c:\\filestr2.txt","Имя2","Лена2");//заменить, или добавить
fD.WriteString("c:\\filestr2.txt","Имя4","Лена4");//заменить, или добавить
fD.WriteString("c:\\filestr2.txt","Имя3","Лена3");//заменить, или добавить

//fD.WriteBool("c:\\filestr.txt","Bool",false);//заменить, или добавить
//fD.WriteInteger("c:\\filestr.txt","Integer",-35);//заменить, или добавить
//fD.WriteFloat("c:\\filestr.txt","Float",-2.35);//заменить, или добавить

//ск. строк в файле ? Если нет файла - сообщение и n=0
int n=fD.ReadCount("c:\\filestr.txt");
AnsiString MasStr[100];
//считаем весь файл(n2-количество строк)  Если нет файла - сообщение и n2=0
int n2=fD.ReadStr("c:\\filestr.txt",MasStr);

//Перезапишем или добавим
fD.WriteString("c:\\filestr.txt","Имя1","Лена2");//заменить, или добавить
fD.WriteString("c:\\filestr.txt","Имя0","Света2");

//Считаем значение по имени
AnsiString str=fD.ReadString("c:\\filestr.txt","Имя10","Cdtnbr");//Если нет файла - сообщение и str=NULL
bool b=fD.ReadBool("c:\\filestr.txt","Bool",true);//Если нет файла - сообщение и b=false
int i=fD.ReadInteger("c:\\filestr.txt","Integer",33);//Если нет файла - сообщение и i=0
float f=fD.ReadFloat("c:\\filestr.txt","Float",10.56);//Если нет файла - сообщение и f=0

//сделаем файл пустым
fD.ClearFile("c:\\filestr.txt");
*/
