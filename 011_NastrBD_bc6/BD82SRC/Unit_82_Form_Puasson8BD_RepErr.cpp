//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Unit_82_Form_Puasson8BD_RepErr.h"

#ifdef _DIA_OBEDINENIE_
  #include "Unit_FormDispet.h"
#endif
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPuasson8BDPepErr * FormPuasson8BDPepErr;
//---------------------------------------------------------------------------
__fastcall TFormPuasson8BDPepErr::TFormPuasson8BDPepErr(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormPuasson8BDPepErr::Button_ClearClick(TObject *Sender)
{
  Memo_main->Clear();        
}
//---------------------------------------------------------------------------
void __fastcall TFormPuasson8BDPepErr::FormShow(TObject *Sender)
{
#ifdef _DIA_OBEDINENIE_
  if( FormDispet != 0 )
  {
    FormDispet->DiaGetWinHandle( this->Handle );  
  }
#endif
}
//---------------------------------------------------------------------------

