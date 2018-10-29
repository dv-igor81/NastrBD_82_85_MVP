//---------------------------------------------------------------------------
//#pragma hdrstop
#include "Utilites_For_Edit.h"
//---------------------------------------------------------------------------
//#pragma package(smart_init)
//---------------------------------------------------------------------------
EditHelper::EditHelper()
{
} 
//---------------------------------------------------------------------------
EditHelper::~EditHelper()
{
}
//---------------------------------------------------------------------------
int EditHelper::ConvertToInt(
  TEdit * edit,
  int min,
  int max,
  int & errorCode)
{
  bool errConv; // флаг ошибки коментария
  int editValue;
  errConv = false; // Нет пока ошибок конвертации

  edit->Color = clWindow;

  try // Номер блока
  {
    if (edit->Text.Length() != 0)
    {
      editValue = StrToInt(edit->Text);
    }
  }
  catch ( EConvertError* )
  {
    errConv = true; // Ошибка конвертации
  }
  if ( ((min <= editValue) && (editValue <= max)) == false )
  {
    errConv = true; // Ошибка конвертации
  }
  if (errConv)
  {
    edit->Color = clRed;
    errorCode = -1;
  }
  return editValue;
}
//---------------------------------------------------------------------------
int EditHelper::ConvertToInt(
  TEdit * edit,
  int min,
  int & errorCode)
{
  bool errConv; // флаг ошибки коментария
  int editValue;
  errConv = false; // Нет пока ошибок конвертации

  edit->Color = clWindow;

  try // Номер блока
  {
    if (edit->Text.Length() != 0)
    {
      editValue = StrToInt(edit->Text);
    }
  }
  catch ( EConvertError* )
  {
    errConv = true; // Ошибка конвертации
  }
  if ( min > editValue )
  {
    errConv = true; // Ошибка конвертации
  }
  if (errConv)
  {
    edit->Color = clRed;
    errorCode = -1;
  }
  return editValue;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------




