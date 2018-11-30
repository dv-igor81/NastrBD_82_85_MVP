//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "WindowSaveParamNastrBd85.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TWindowSaveParamBd85::TWindowSaveParamBd85(TComponent* Owner)
        : TForm(Owner)
{
    this->Position = poScreenCenter;
}
//---------------------------------------------------------------------------
void __fastcall TWindowSaveParamBd85::OnWMSysCommand( TMessage& Message )
{
  switch( Message.WParam )
  {
    case SC_MINIMIZE:
         Application->Minimize();
         Message.Result = 0;
         break;
    default :
         DefaultHandler( &Message );
  }
}
//---------------------------------------------------------------------------
void TWindowSaveParamBd85::SetVerPoText(const char * text)
{
    AnsiString textPoVer = Caption;
    textPoVer += text;
    this->Caption = textPoVer;
}
//---------------------------------------------------------------------------
void TWindowSaveParamBd85::SetFileName(const char * fileName)
{
    this->Edit_FileName->Text = fileName;
}
//---------------------------------------------------------------------------
void TWindowSaveParamBd85::SetFileNameEnabled(bool enabled)
{
    this->Edit_FileName->Enabled = enabled;
}
//---------------------------------------------------------------------------
void TWindowSaveParamBd85::SetFileHeader(const char * fileHeader)
{
    this->Edit_FileHeader->Text = fileHeader;
}
//---------------------------------------------------------------------------
void TWindowSaveParamBd85::SetFileHeaderEnabled(bool enabled)
{
    this->Edit_FileHeader->Enabled = enabled;
}
//---------------------------------------------------------------------------
void TWindowSaveParamBd85::SetTimeText(const char * text)
{
    this->Edit_Time->Text = text;
}
//---------------------------------------------------------------------------
void TWindowSaveParamBd85::SetTimeEnabled(bool enabled)
{
    this->Edit_Time->Enabled = enabled;
}
//---------------------------------------------------------------------------
void TWindowSaveParamBd85::SetNumberText(const char * text)
{
    this->Edit_Number->Text = text;
}
//---------------------------------------------------------------------------
void TWindowSaveParamBd85::SetNumberEnabled(bool enabled)
{
    this->Edit_Number->Enabled = enabled;
}
//---------------------------------------------------------------------------
void TWindowSaveParamBd85::SetDelayText(const char * text)
{
    this->Edit_Delay->Text = text;
}
//---------------------------------------------------------------------------
void TWindowSaveParamBd85::SetDelayEnabled(bool enabled)
{
    this->Edit_Delay->Enabled = enabled;
}
//---------------------------------------------------------------------------
void TWindowSaveParamBd85::WrapShow()
{
    this->Show();
}
//---------------------------------------------------------------------------
void TWindowSaveParamBd85::Destroy()
{
    delete this;
}
//---------------------------------------------------------------------------
void __fastcall TWindowSaveParamBd85::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    ev_FormClose();
}
//---------------------------------------------------------------------------
ActionEvent<>& TWindowSaveParamBd85::EventFormClose()
{
    return ev_FormClose;
}
//---------------------------------------------------------------------------
void __fastcall TWindowSaveParamBd85::Edit_FileNameChange(TObject *Sender)
{
    ev_EditFileNameChange( Edit_FileName->Text.c_str() );
}
//---------------------------------------------------------------------------
ActionEvent<const char*>& TWindowSaveParamBd85::EventEditFileNameChange()
{
    return ev_EditFileNameChange;
}
//---------------------------------------------------------------------------
void __fastcall TWindowSaveParamBd85::Edit_FileHeaderChange(
      TObject *Sender)
{
    ev_EditFileHeaderChange( Edit_FileHeader->Text.c_str() );
}
//---------------------------------------------------------------------------
ActionEvent<const char*>& TWindowSaveParamBd85::EventEditFileHeaderChange()
{
    return ev_EditFileHeaderChange;
}
//---------------------------------------------------------------------------
void __fastcall TWindowSaveParamBd85::Edit_TimeChange(TObject *Sender)
{
    ev_EditTimeChange( Edit_Time->Text.c_str() );
}
//---------------------------------------------------------------------------
ActionEvent<const char*>& TWindowSaveParamBd85::EventEditTimeChange()
{
    return ev_EditTimeChange;
}
//---------------------------------------------------------------------------
void __fastcall TWindowSaveParamBd85::Edit_NumberChange(TObject *Sender)
{
    ev_EditNumberChange( Edit_Number->Text.c_str() );
}
//---------------------------------------------------------------------------
ActionEvent<const char*>& TWindowSaveParamBd85::EventEditNumberChange()
{
    return ev_EditNumberChange; 
}
//---------------------------------------------------------------------------
void __fastcall TWindowSaveParamBd85::Edit_DelayChange(TObject *Sender)
{
    ev_EditDelayChange( Edit_Delay->Text.c_str() );
}
//---------------------------------------------------------------------------
ActionEvent<const char*>& TWindowSaveParamBd85::EventEditDelayChange()
{
    return ev_EditDelayChange;
}
//---------------------------------------------------------------------------
