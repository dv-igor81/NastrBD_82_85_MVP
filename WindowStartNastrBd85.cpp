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
        : TForm(Owner), viewLoader(this)
{
}
//---------------------------------------------------------------------------
void __fastcall TWindowStart::Button_StartClick(TObject *Sender)
{
    viewLoader.LoadWindowMain();
}
//---------------------------------------------------------------------------

