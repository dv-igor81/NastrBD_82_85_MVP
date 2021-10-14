//---------------------------------------------------------------------------
#include <vcl.h>
#include <Inifiles.hpp>
#pragma hdrstop
#include "Unit_Form_VersionInfo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_VersionInfo *Form_VersionInfo;
extern const char * IniFileName;
//---------------------------------------------------------------------------
__fastcall TForm_VersionInfo::TForm_VersionInfo(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_VersionInfo::FormCreate(TObject *Sender)
{
  TIniFile * IniFile = new TIniFile( IniFileName );
  try
  {
    Left = IniFile->ReadInteger( "DIA_Form_Version", "Form_Left_Version", 0 );
    Top = IniFile->ReadInteger( "DIA_Form_Version", "Form_Top_Version", 0 );
    delete IniFile;
  }
  catch (...)
  {
    delete IniFile;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_VersionInfo::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  TIniFile * IniFile = new TIniFile( IniFileName );
  try
  {
    IniFile->WriteInteger( "DIA_Form_Version", "Form_Left_Version", Left );
    IniFile->WriteInteger( "DIA_Form_Version", "Form_Top_Version", Top );
    delete IniFile;
  }
  catch (...)
  {
    delete IniFile;
  }
}
//---------------------------------------------------------------------------






