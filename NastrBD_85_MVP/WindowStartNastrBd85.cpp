//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "WindowStartNastrBd85.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TWindowStart *WindowStart;
//---------------------------------------------------------------------------
__fastcall TWindowStart::TWindowStart(TComponent* Owner)
        : TForm(Owner), viewLoader(this, this)
{
    ProgrammVersion = " v4.29.1";
    SetVerPoText( ProgrammVersion.c_str() );
}
//---------------------------------------------------------------------------
void TWindowStart::SetVerPoText(const char * text)
{
    AnsiString textPoVer = Caption;
    textPoVer += text;
    Caption = textPoVer;
}
//---------------------------------------------------------------------------
void __fastcall TWindowStart::Button_StartClick(TObject *Sender)
{
    viewLoader.LoadWindowBd85Main();
    Hide();
}
//---------------------------------------------------------------------------
void __fastcall TWindowStart::FormCloseQuery(TObject *Sender,
      bool &CanClose)
{
    //bool tmp = CanClose;
    //CanClose = false;
}
//---------------------------------------------------------------------------
const char * TWindowStart::GetProgrammVersion()
{
    return ProgrammVersion.c_str();
}
//---------------------------------------------------------------------------
void TWindowStart::WrapShow()
{
    Show();
}
//---------------------------------------------------------------------------

