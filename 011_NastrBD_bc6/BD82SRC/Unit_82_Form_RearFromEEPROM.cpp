//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Unit_82_Form_RearFromEEPROM.h"

#ifdef _DIA_OBEDINENIE_
  #include "Unit_FormDispet.h"
#endif
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_RearFromEEPROM *Form_RearFromEEPROM;
//---------------------------------------------------------------------------
__fastcall TForm_RearFromEEPROM::TForm_RearFromEEPROM(TComponent* Owner)
        : TForm(Owner)
{
  StringGrid_large->Cells[0][0] = "БАНК" ;
  StringGrid_large->Cells[1][0] = "1(Ток светод.)";
  StringGrid_large->Cells[2][0] = "2(Ток светод.)";
  StringGrid_large->Cells[3][0] = "3(Ток светод.)";
  StringGrid_large->Cells[4][0] = "4(Ток светод.)";
  for ( int i = 0; i < 64; i++ )
  {
    StringGrid_large->Cells[0][i+1] = "0x" + IntToHex((i+48), 2);
  }
  StringGrid_small->Cells[0][0] = "БАНК";
  StringGrid_small->Cells[1][0] = "K1(Температура)";
  StringGrid_small->Cells[2][0] = "A1(Температура)";
  StringGrid_small->Cells[3][0] = "K2(Ток светод.)";
  StringGrid_small->Cells[4][0] = "A2(Ток светод.)";
  StringGrid_small->Cells[0][1] = "2C-2F";
}
//---------------------------------------------------------------------------
void __fastcall TForm_RearFromEEPROM::FormShow(TObject *Sender)
{
#ifdef _DIA_OBEDINENIE_
  if( FormDispet != 0 )
  {
    FormDispet->DiaGetWinHandle( this->Handle );
  }
#endif
}
//---------------------------------------------------------------------------

