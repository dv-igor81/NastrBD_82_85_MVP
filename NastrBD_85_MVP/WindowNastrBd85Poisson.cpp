//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "WindowNastrBd85Poisson.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TWindowBd85Poisson::TWindowBd85Poisson(TComponent* Owner)
        : TForm(Owner)
{
    Initialization();
}
//---------------------------------------------------------------------------
void TWindowBd85Poisson::Initialization()
{
    //_viewModel = 0;
    this->Position = poScreenCenter;
}
//---------------------------------------------------------------------------
void __fastcall TWindowBd85Poisson::OnWMSysCommand( TMessage& Message )
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
void TWindowBd85Poisson::SetViewModel( IViewModelBd85Poisson * viewModel )
{
    _viewModel = viewModel;
}
//---------------------------------------------------------------------------
void TWindowBd85Poisson::SetVerPoText(const char * text)
{
    AnsiString textPoVer = Caption;
    textPoVer += text;
    this->Caption = textPoVer;
}
//---------------------------------------------------------------------------
void __fastcall TWindowBd85Poisson::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    _viewModel->FormClose();        
}
//---------------------------------------------------------------------------
void TWindowBd85Poisson::WrapShow()
{
    this->Show();
}
//---------------------------------------------------------------------------
void TWindowBd85Poisson::WrapClose()
{
    this->Close();
}
//---------------------------------------------------------------------------
void TWindowBd85Poisson::Destroy()
{
    delete this;
}
//---------------------------------------------------------------------------
