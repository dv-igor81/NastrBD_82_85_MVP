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
  bool errConv; // ���� ������ ����������
  int editValue;
  errConv = false; // ��� ���� ������ �����������

  edit->Color = clWindow;

  try // ����� �����
  {
    if (edit->Text.Length() != 0)
    {
      editValue = StrToInt(edit->Text);
    }
  }
  catch ( EConvertError* )
  {
    errConv = true; // ������ �����������
  }
  if ( ((min <= editValue) && (editValue <= max)) == false )
  {
    errConv = true; // ������ �����������
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
  bool errConv; // ���� ������ ����������
  int editValue;
  errConv = false; // ��� ���� ������ �����������

  edit->Color = clWindow;

  try // ����� �����
  {
    if (edit->Text.Length() != 0)
    {
      editValue = StrToInt(edit->Text);
    }
  }
  catch ( EConvertError* )
  {
    errConv = true; // ������ �����������
  }
  if ( min > editValue )
  {
    errConv = true; // ������ �����������
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




