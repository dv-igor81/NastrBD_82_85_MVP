//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "Unit_82_ComPortReadWrite.h"
#include "Unit_82_Form_Start.h"
#include "Unit_82_Form_Puasson8BD.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
//extern RSProtokol_t * Prot;
//---------------------------------------------------------------------------
__fastcall ComPortReadWrite_t::ComPortReadWrite_t(bool CreateSuspended)
    : TThread(CreateSuspended)
{
  this->Prot = Form_82_Start->Prot;
  bflag_pred_err = false; // ��� �������� �������, ������ ����� ��� �� ����
  //Prot->flagTCP = false;
}
//---------------------------------------------------------------------------
void __fastcall ComPortReadWrite_t::Printing()
{
  if ( this->flagSostoyaniya == 9 )
  {
    Form_82_Start->OprosBD_2();  
    this->flagSostoyaniya = 1;
  }
  if ( ( bflag_tek_err == true ) && ( bflag_pred_err == false ) ) // ������ ����� ���������
  {
    //!Prot->Reset();
    Form_82_Start->CheckBox_speed->Checked = false; // ��� ��������� ������
    Form_82_Start->ErrorZvyazi();
  }
  if ( ( bflag_pred_err == true ) && ( bflag_tek_err == false ) ) // ���� ����� ���� ����� ����, �� ����� �������������, ��� ����� ���������
  {
    Prot->Data.flagGetVersion = false; // ������ ��������� ������  
    Form_82_Start->OprosBD_2();
    Prot->Data.flagSetTimeInterval = false; // ������ ���������� ������� (KolTick)
    Prot->Data.flagGetTimeInterval = false; // ������ ��������� ��������� ��������
  }
  if ( this->flagSostoyaniya == 1 )
  {
    if ( Form_82_Start->FlagOpros == true ) // ���� ��� ����������� ��������� ������ OpenBD
    {
      Form_82_Start->OprosBD();
    }
    Form_82_Start->Printing();
  }
  else if ( this->flagSostoyaniya == 3 )
  {
    Form_82_Start->ZapEEPROM();
    this->flagSostoyaniya = 1;
  }
}
//---------------------------------------------------------------------------
void ComPortReadWrite_t::swap(int & varTo, int & varFrom)
{
  int tmp = varTo;
  varTo = varFrom;
  varFrom = tmp;
}
//---------------------------------------------------------------------------
void ComPortReadWrite_t::FindBdByNom(int nom)
{
  unsigned short RegArray[32]; // �������� ��
  int rc;
  rc = Prot->read_registers(nom, 0, 1, RegArray);
  Sleep(8); // ��������� 8 ����.
  if ( rc != 1 )
  {
    sprintf(CArr, "������ ����� � �� � %d", nom);
    Synchronize( &PrintingNot );
  }
  else
  {
    if (RegArray[0] == 0x4D41)
    {
      sprintf(CArr, "�� � <%d> ������", nom);
      this->N++; // ��� ������ ��������� "������ �������������� �� ����������"
      this->AddrBD = nom;
      Synchronize( &PrintingYes );
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall ComPortReadWrite_t::Execute()
{
  while ( Terminated == false )
  {
    if ( this->flagSostoyaniya == 1 ||
         this->flagSostoyaniya == 3 ||
         this->flagSostoyaniya == 9 )
    {
      Prot->ReturnVar = Prot->OprosBD();
      if ( Prot->ReturnVar != -1 )
      {
        bflag_tek_err = false; // ��� ������ �����
      }
      else if ( Prot->ReturnVar == -1 )
      {
        bflag_tek_err = true; // ������ �����
      }
      Synchronize( &Printing ); // ������ �� ����� � ����� �������!
      bflag_pred_err = bflag_tek_err;
    }
    else if ( this->flagSostoyaniya == 2 ) // ����� ���������� (������ ��� ModBus)
    {
      int flagPotoka;
      int i;
      varFrom = Form_82_Start->varFrom;
      varTo = Form_82_Start->varTo;
      flagPotoka = Form_82_Start->FlagButtonSearch;
      this->N = 0;
      if ( varTo > varFrom )
      {
        swap(varTo, varFrom);
      }
      FindBdByNom(247);
      for ( i = varTo; (i <= varFrom) && (flagPotoka == true); i++ )
      {
        flagPotoka = Form_82_Start->FlagButtonSearch;
        FindBdByNom(i);
      }
      Synchronize( &PrintingEnd );
    }
    else if ( this->flagSostoyaniya == 4 ) //
    {
      Form_82_Start->ReadFromBDModbus(); // ������� ������ ���������� ModBus
      this->flagSostoyaniya = 1;
    }
    else if ( this->flagSostoyaniya == 5 ) //
    {
      Form_82_Start->WriteToBDModBus(); // ������� ������ ���������� ModBus
      this->flagSostoyaniya = 1;
    }
    else if ( this->flagSostoyaniya == 6 ) // ������ � EEPROM
    { // "��� ���������� ��������" � "������ ��� ���������"
      Form_82_Start->ZapEEPROM_2();
      this->flagSostoyaniya = 1;
    }
    else if ( this->flagSostoyaniya == 7 )
    {
      Synchronize( & FormPuasson8BD->TimerOff ); // ��������� ������
      Prot->NullsToStr_err();
      //Prot->OprosBD8Arr();
      Synchronize( & FormPuasson8BD->TimerOn ); // �������� ������      
      Synchronize( & FormPuasson8BD->Display );
    }
    else if ( this->flagSostoyaniya == 8 )
    {
      Synchronize( & FormPuasson8BD->TimerOff ); // ��������� ������
      Synchronize( & Form_82_Start->RSDisConnect2 ); // ������� ���-����
      Prot->ReadTimeout = 100;
      Prot->WriteTimeout = 100;
    }
    else if ( this->flagSostoyaniya == 10 ) // ����� �������
    {
      //Prot->OprosBDSpektr(); // ���� �� �����������, �.�. ����� �� ��������������� this->flagSostoyaniya = 10
    }
    Suspend(); // ������������� �����
  }
}
//---------------------------------------------------------------------------
void __fastcall ComPortReadWrite_t::PrintingNoConnect()
{
  Form_82_Start->StatusBar1->Panels->Items[1]->Text = "��� ����������";
}
//---------------------------------------------------------------------------
void __fastcall ComPortReadWrite_t::PrintingNot()
{
  Form_82_Start->StatusBar1->Panels->Items[0]->Text = CArr;
}
//---------------------------------------------------------------------------
void __fastcall ComPortReadWrite_t::PrintingYes()
{
  Form_82_Start->Memo_SkanBD->Lines->Add(CArr);
}
//---------------------------------------------------------------------------
void __fastcall ComPortReadWrite_t::PrintingEnd()
{
  if (this->N != 0)
  {
    Form_82_Start->SpinEdit_AddrBD->Text = IntToStr(this->AddrBD);
    sprintf(CArr, "������� %d ��", this->N);
    Form_82_Start->Memo_SkanBD->Lines->Add(CArr);
  }
  else
  {
    Form_82_Start->Memo_SkanBD->Lines->Add("������ �������������� �� ����������");
  }
  Form_82_Start->StatusBar1->Panels->Items[0]->Text = "";
  Form_82_Start->ButtonSearch->Caption = "������";
  Form_82_Start->Button_OpenBD->Enabled = true; // ��������� ������� ������ "�������"
  Form_82_Start->RadioGroup_VyborProtokola->Enabled = true; // ��������� ����� ���������
  Form_82_Start->Button_UpdateComPortsList->Enabled = true; // ��������� ���������� ���-������
  Form_82_Start->ComboBox_NomComPort->Enabled = true; // ��������� ����� ���-�����
  Form_82_Start->Button_ARCH->Enabled = true; // ��������� ���
  Form_82_Start->Button_Puason->Enabled = true; // ��������� �������
  Form_82_Start->Button_SaveAddr->Enabled = true; // ��������� ������� ������ "�������� �����"
  Form_82_Start->ComboBox_NomBD->Enabled = true; //==\\ 24.01.2016


  Form_82_Start->Button_P3_7_Set->Enabled = true;
  Form_82_Start->Button_P3_7_Reset->Enabled = true;

  Form_82_Start->FlagButtonSearch = false;
  Form_82_Start->RSDisConnect();
}
//---------------------------------------------------------------------------
void __fastcall ComPortReadWrite_t::SetTcpFlag( bool flag )
{
  this->Prot->flagTCP = flag;
}
//---------------------------------------------------------------------------
bool __fastcall ComPortReadWrite_t::GetTcpFlag( void )
{
  return this->Prot->flagTCP;
}
