//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit_Thread_ComPort.h"
#include "Unit_Form_Start.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------
//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ComPortReadWrite_t::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
__fastcall ComPortReadWrite_t::ComPortReadWrite_t(bool CreateSuspended)
        : TThread(CreateSuspended)
{
  Ptr_ComPort = 0;
  Prot = new RSProtokol_t();
  for ( int i = 0; i < 16; i++ )
  {
    MasBD_ModBus[i] = false;
    MasBD_9bit[i] = false;
  }
  flagEnableResume = true; // Resume доступно
  Length_BD = Size_BD;
  ByloSkanirovanie = false; // false - не было сканирования доступных КОМ-портов
}
//---------------------------------------------------------------------------
void __fastcall ComPortReadWrite_t::Execute()
{
  while ( Terminated == false )
  {
    flagEnableResume = false;
    switch ( flagZadachi )
    {
    case ZD_Opros_Portov:
      SkanComPort();
      //Form_Start->flagZadachi_FS = ZD_Opros_9Bit; // Сканировать "9 битные" БД
      break;
    case ZD_Opros_9Bit:
      SkanBD9Bit();
      //Form_Start->flagZadachi_FS = ZD_ReadBDParam_9Bit; // Читать параметры из БД "9 битный" протокол
      break;
    case ZD_Opros_ModBusRTU:
      break;
    case ZD_ReadBDParam_9Bit:
      ReadBD9Bit();
      Form_Start->flagZadachi_FS = ZD_Start; // Кнопка "Старт/Стоп" не нажималась ещё или в положение "Старт"
      break;
    } // END: switch ( flagZadachi )

    ClearText();
    flagEnableResume = true;
    Suspend(); // Приостановить поток
  } // END: while ( Terminated == false )
  //---- Place thread code here ----
}
//---------------------------------------------------------------------------
void __fastcall ComPortReadWrite_t::Printing()
{
  if ( Form_Start->Button_Start_Stop->Caption == "Прервать" )
  {
    Form_Start->Panel_Display->Caption = StrDisplay;
  }
}
//---------------------------------------------------------------------------
void __fastcall ComPortReadWrite_t::SetString(String Str)
{
  StrDisplay = Str;
}
//---------------------------------------------------------------------------
void ComPortReadWrite_t::SkanComPort()
{
  int i;
  int j;
  Form_Start->flagZadachi_FS = ZD_Prostoy;
  SetString("Поиск КОМ-портов");
  Synchronize( Printing );
  Count = DIA_UpdateCom( KomPorts );
  Form_Start->flagZadachi_FS = ZD_Opros_9Bit;
}
//---------------------------------------------------------------------------
void ComPortReadWrite_t::ClearText()
{
  SetString("");
  Synchronize( Printing );
}
//---------------------------------------------------------------------------
void ComPortReadWrite_t::Display (String Str)
{
  SetString( Str );
  Synchronize( Printing );
}
//---------------------------------------------------------------------------
// Просканировать 16 БД
void ComPortReadWrite_t::SkanBD9Bit()
{
  int ErrorCod;
  unsigned char AddrBD;
  String strBDAddr;
  bool * bArr = MasBD_9bit;

  Form_Start->flagZadachi_FS = ZD_Prostoy; // Ожидание задачи

  Prot->flagModbusProtokol = false;
  ErrorCod = Prot->RSConnect( ComPortName.c_str() );
  if ( ErrorCod == -1 )
  {
    if ( ByloSkanirovanie == true )
    {
      Display("Доступный КОМ-порт не найден!"); // Завершение работы
      Form_Start->flagZadachi_FS = ZD_Start;
      return;
    }
    else
    {
      Form_Start->flagZadachi_FS = ZD_Opros_Portov; // Сканирование КОМ-портов
      return;
    }
  }

  for ( int i = 0; i < 16; i++ )
  {
    Prot->AddrBD = i;
    strBDAddr = "Адрес БД (9 бит): " + IntToStr( i );
    Display( strBDAddr );
    Prot->flagFirstAddr = true;
    ErrorCod = Prot->GetIndAdr( & AddrBD );
    Sleep( 500 );
    bArr[i] = false;
    if ( ErrorCod == 0 )
    {
      if ( i == AddrBD )
      {
        bArr[i] = true;
      }
    }
  }
  Prot->RSDisConnect();
  Form_Start->flagZadachi_FS = ZD_ReadBDParam_9Bit;
}
//---------------------------------------------------------------------------
int ComPortReadWrite_t::GetNextCom()
{
  int CP = -1;
  int i;
  int j;

  if ( Count > 0 )
  {
    for ( i = Ptr_ComPort + 1, j = 0; j < 32; j++, i++ )
    {
      if ( KomPorts[i] == true )
      {
        Ptr_ComPort = i;
        CP = i + 1;
        break;
      }
    }
  }
  return CP;
}
//---------------------------------------------------------------------------
int ComPortReadWrite_t::ReadBD9Bit()
{
  int RetVal;
  Prot->flagModbusProtokol = false;
  Prot->RSConnect( ComPortName.c_str() );
  for ( int i = 0; i < Size_BD; i++ )
  {
    if ( MasBD_9bit[i] == false )
    {
      continue;
    }
    Prot->flagFirstAddr = true;
    Prot->AddrBD = i;
    RetVal = Prot->ReadBD( & Data9Bit[i] );
  }
  Prot->RSDisConnect();
  return RetVal;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
