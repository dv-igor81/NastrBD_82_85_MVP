//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "WindowStart.h"
#include "WindowSecond.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    TForm2 * win = new TForm2(this);
    win->Show();      
}
//---------------------------------------------------------------------------
