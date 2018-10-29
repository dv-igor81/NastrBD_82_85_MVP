//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Unit_82_Form_Puasson8BD.h"
#include "Unit_82_Form_Start.h"
#include "Unit_82_ComPortReadWrite.h"
//#include "Unit_82_RSProtokol.h"
#include "RSProtokol.h"
//---------------------------------------------------------------------------
#include <stdio.h>
#include <io.h> // open()
#include <fcntl.h> // O_CREAT
#include <sys\stat.h> // S_IREAD | S_IWRITE
#include "Unit_82_Form_Puasson8BD_RepErr.h"
#include "Unit_82_Form_Graph.h"

#ifdef _DIA_OBEDINENIE_
  #include "Unit_FormDispet.h"
#endif
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TFormPuasson8BD * FormPuasson8BD;
TForm_Graph * Form_Graph_Arr[8];
extern ComPortReadWrite_t * Cprw;
//---------------------------------------------------------------------------
__fastcall TFormPuasson8BD::TFormPuasson8BD(TComponent* Owner)
        : TForm(Owner)
{
  Panel_Display_Arr[1-1] = Panel_Display_BD1;
  Panel_Display_Arr[2-1] = Panel_Display_BD2;
  Panel_Display_Arr[3-1] = Panel_Display_BD3;
  Panel_Display_Arr[4-1] = Panel_Display_BD4;
  Panel_Display_Arr[5-1] = Panel_Display_BD5;
  Panel_Display_Arr[6-1] = Panel_Display_BD6;
  Panel_Display_Arr[7-1] = Panel_Display_BD7;
  Panel_Display_Arr[8-1] = Panel_Display_BD8;

  Edit_ArrSerNum[1-1] = Edit_SN1;
  Edit_ArrSerNum[2-1] = Edit_SN2;
  Edit_ArrSerNum[3-1] = Edit_SN3;
  Edit_ArrSerNum[4-1] = Edit_SN4;
  Edit_ArrSerNum[5-1] = Edit_SN5;
  Edit_ArrSerNum[6-1] = Edit_SN6;
  Edit_ArrSerNum[7-1] = Edit_SN7;
  Edit_ArrSerNum[8-1] = Edit_SN8;

  SpinEdit_AddrBDArr[1-1] = SpinEdit_AddrBD1;
  SpinEdit_AddrBDArr[2-1] = SpinEdit_AddrBD2;
  SpinEdit_AddrBDArr[3-1] = SpinEdit_AddrBD3;
  SpinEdit_AddrBDArr[4-1] = SpinEdit_AddrBD4;
  SpinEdit_AddrBDArr[5-1] = SpinEdit_AddrBD5;
  SpinEdit_AddrBDArr[6-1] = SpinEdit_AddrBD6;
  SpinEdit_AddrBDArr[7-1] = SpinEdit_AddrBD7;
  SpinEdit_AddrBDArr[8-1] = SpinEdit_AddrBD8;

  CheckBox_AddrBDArr[1-1] = CheckBox_AddrBD1;
  CheckBox_AddrBDArr[2-1] = CheckBox_AddrBD2;
  CheckBox_AddrBDArr[3-1] = CheckBox_AddrBD3;
  CheckBox_AddrBDArr[4-1] = CheckBox_AddrBD4;
  CheckBox_AddrBDArr[5-1] = CheckBox_AddrBD5;
  CheckBox_AddrBDArr[6-1] = CheckBox_AddrBD6;
  CheckBox_AddrBDArr[7-1] = CheckBox_AddrBD7;
  CheckBox_AddrBDArr[8-1] = CheckBox_AddrBD8;

  Button_GraphArr[1-1] = Button_Graph_01;
  Button_GraphArr[2-1] = Button_Graph_02;
  Button_GraphArr[3-1] = Button_Graph_03;
  Button_GraphArr[4-1] = Button_Graph_04;
  Button_GraphArr[5-1] = Button_Graph_05;
  Button_GraphArr[6-1] = Button_Graph_06;
  Button_GraphArr[7-1] = Button_Graph_07;
  Button_GraphArr[8-1] = Button_Graph_08;

  Edit_SchetSekArr[1-1] = Edit_SchetSek01;
  Edit_SchetSekArr[2-1] = Edit_SchetSek02;
  Edit_SchetSekArr[3-1] = Edit_SchetSek03;
  Edit_SchetSekArr[4-1] = Edit_SchetSek04;
  Edit_SchetSekArr[5-1] = Edit_SchetSek05;
  Edit_SchetSekArr[6-1] = Edit_SchetSek06;
  Edit_SchetSekArr[7-1] = Edit_SchetSek07;
  Edit_SchetSekArr[8-1] = Edit_SchetSek08;

  Edit_PNSchArr[1-1] = Edit_PNSch01;
  Edit_PNSchArr[2-1] = Edit_PNSch02;
  Edit_PNSchArr[3-1] = Edit_PNSch03;
  Edit_PNSchArr[4-1] = Edit_PNSch04;
  Edit_PNSchArr[5-1] = Edit_PNSch05;
  Edit_PNSchArr[6-1] = Edit_PNSch06;
  Edit_PNSchArr[7-1] = Edit_PNSch07;
  Edit_PNSchArr[8-1] = Edit_PNSch08;

  Edit_KvoIspArr[1-1] = Edit_KvoIsp01;
  Edit_KvoIspArr[2-1] = Edit_KvoIsp02;
  Edit_KvoIspArr[3-1] = Edit_KvoIsp03;
  Edit_KvoIspArr[4-1] = Edit_KvoIsp04;
  Edit_KvoIspArr[5-1] = Edit_KvoIsp05;
  Edit_KvoIspArr[6-1] = Edit_KvoIsp06;
  Edit_KvoIspArr[7-1] = Edit_KvoIsp07;
  Edit_KvoIspArr[8-1] = Edit_KvoIsp08;

  Button_Stop->Enabled = false;
  CheckBox_Err->Visible = false;
  CheckBox_Err->Enabled = false;

  Button_detail->Visible = false;
  Button_detail->Enabled = false;
  bFlagWork = false;

  for ( int i = 0; i < 8; i++ )
  {
    bFlagSetTimeInterval[i] = false; // false - не выполнялась функция SetTimeInterval(8) для БД
    bFlagGetSerialNum[i] = false; // false - не выполнялась функция ReadFlashInvert(10, &SerialNumArr[i]) для БД
    SerialNumArr[i] = 0; // Серийные номера БД
    Edit_ArrSerNum[i]->Enabled = true;
    Edit_ArrSerNum[i]->ReadOnly = false;
    Form_Graph_Arr[i] = 0; // Не создано ни одной формы графиков
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPuasson8BD::FormShow(TObject *Sender)
{
#ifdef _DIA_OBEDINENIE_
  if( FormDispet != 0 )
  {
    FormDispet->DiaGetWinHandle( this->Handle );  
  }
#endif  
  Form_82_Start->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TFormPuasson8BD::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Form_82_Start->Show();
  FormPuasson8BDPepErr->Close();
}
//---------------------------------------------------------------------------
void TFormPuasson8BD::GetAddrBDArr( void )
{
  maxInd = 0; // Сколько БД выбрано пользователем.
  pInd = 0; // pInd - указывает на первый выбранный пользователем БД
  for ( int i = 0; i < 8; i++ )
  {
    if ( CheckBox_AddrBDArr[i]->Checked == true )
    {
      AddrBDArr[i] = static_cast<unsigned char>( SpinEdit_AddrBDArr[i]->Value );
      IndexArr[maxInd] = i; // Множество тех блоков (индексов массива AddrBDArr, адресов БД), которые выбрал пользователь
      maxInd++; // Сколько БД выбрано пользователем.      
    }
    else
    {
      AddrBDArr[i] = 248; // Блок детектирования не опрашивается
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPuasson8BD::Button_StartClick(TObject *Sender)
{
  int ErrorCode;

  ErrorCode = 0;
  for ( int i = 0; i < 8; i++ )
  {
    if ( CheckBox_AddrBDArr[i]->Checked == true )
    {
      ErrorCode = 1;
      break; // выход из цикла
    }
  }
  if ( ErrorCode == 0 )
  {
    Panel_Info->Caption = "Выберите хотя бы один БД!";
    return;  
  }

  Form_82_Start->Prot->ReadTimeout = SpinEdit_readTimeout->Value;
  ErrorCode = Form_82_Start->RSConnect( Form_82_Start->ComboBox_NomComPort->Text.c_str() ); // Открыть порт
  if ( ErrorCode == 0 ) // Если порт открылся или уже был открыт
  {
    GetAddrBDArr(); // Заполнить массив значениями адресов
    Cprw->flagSostoyaniya = 7;
    Button_Stop->Enabled = true;
    Button_Start->Enabled = false;
    CheckBox_AllBD->Enabled = false;
    SpinEdit_Time->Enabled = false;
    Button_Exit->Enabled = false;

    dTSum = 0;
    dTmaxSum = 0;
    dTPeriod = 0;
    dTmaxPeriod = 0;
    if ( Form_82_Start->Prot->flagModbusProtokol != 0 ) // ModBus RTU, ModBus TCP, ModBus RTU (TCP/IP)
    {
      DIA_Interval = 170 - (20 * maxInd);  // Интервал, для управления таймером
    }
    else
    {
      DIA_Interval = 130 - (15 * maxInd);  // Интервал, для управления таймером    
    }
    Form_82_Start->Timer1->Enabled = true;

    bFlagOprosBD8 = false; // false - ещё ни разу не вызывалась функция OprosBD8Arr
    bFlag8BD_PSW = false;  // true - Один из 8-ми блоков ответил успешно (есть флаг готовности счёта)
    MinTimeBD = 0;
    
    for ( int i = 0; i < 8; i++ )
    {
      bFlagSetTimeInterval[i] = false; // false - не выполнялась функция SetTimeInterval(8) для БД
      bFlagGetSerialNum[i] = false; // false - не выполнялась функция ReadFlashInvert(10, &SerialNumArr[i]) для БД
      ErrorCodBD[i] = 0; // Код ошибки БД
      KolErrors[i] = 0; // Количество ошибок обмена с БД
      PrizNesnChet[i] = 0; // Количество признаков неснятого счёта
      Chet[i] = 0; // Текущий счёт
      ChetZaSekundu[i] = 0; // Счёт за секунду
      ChetNakapl[i] = 0; // Сумарный счёт за секунду формируется при помощи этого накапливаемого счёта
      KolVoChet[i] = 0; // Количество полученных с БД счетов (сколько раз получали счет с БД)
      SpinEdit_AddrBDArr[i]->Enabled = false;
      CheckBox_AddrBDArr[i]->Enabled = false;
      dTBD[i] = 0;
      dTmaxBD[i] = 0;
      Panel_Display_Arr[i]->Caption = "";
      Edit_ArrSerNum[i]->Text = "";
      bFlagDisplaySN[i] = false;
      handle[i] = 0; // Дескрипторы файлов
      TimeBD[i] = 0;
      Edit_ArrSerNum[i]->Enabled = false;
      Edit_ArrSerNum[i]->Text = "";
      indexSM[i] = 0;
      this->UpdateGraph(i);

      Edit_SchetSekArr[i]->Text = "";
      Edit_PNSchArr[i]->Text = "";
      Edit_KvoIspArr[i]->Text = "";
    }
    Panel_Info->Caption = "";
    bFlagWork = true; // Идёт опрос блоков
  }
  else
  {
    Panel_Info->Caption = "Ошибка открытия ком-порта";
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPuasson8BD::Button_StopClick(TObject *Sender)
{
  Cprw->flagSostoyaniya = 8;
  Button_Stop->Enabled = false;
  Button_Start->Enabled = true;
  SpinEdit_Time->Enabled = true;
  CheckBox_AllBD->Enabled = true;
  Button_Exit->Enabled = true;
  bFlagWork = false;
  for ( int i = 0; i < 8; i++ )
  {
    SpinEdit_AddrBDArr[i]->Enabled = true;
    CheckBox_AddrBDArr[i]->Enabled = true;
    Edit_ArrSerNum[i]->Enabled = true;
    if ( (handle[i] != -1) && (handle[i] != 0) )
    {
      close( handle[i] );
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPuasson8BD::Display( void )
{
  char Str[220];

  for ( int ind = 0, i; ind < maxInd; ind++ )
  {
    i = FormPuasson8BD->IndexArr[ ind ];
    if ( ErrorCodBD[i] != 0 )
    {
      Panel_Display_Arr[i]->Caption = "";
      ErrorCodBD[i] = 0;
    }
  }
  MinTimeBD = MinSchet( TimeBD );
  for ( int ind = 0, i; ind < maxInd; ind++ )
  {
    i = FormPuasson8BD->IndexArr[ ind ];
    if ( bFlagDisplay == true )
    {
      //sprintf(
      //    Str,
      //    "счёт за сек.: %d; призн. несн. счёта: %d; Код ошибки: %d; кол-во испытаний: %d; ошибок обмена: %d",
      //    ChetZaSekundu[i],
      //    PrizNesnChet[i] - 1,
      //    ErrorCodBD[i],
      //    TimeBD[i],
      //    KolErrors[i]);
      //Panel_Display_Arr[i]->Caption = Str;
      sprintf( Str, "%d", ChetZaSekundu[i] );
      Edit_SchetSekArr[i]->Text = Str;
      sprintf( Str, "%d", PrizNesnChet[i] - 1 );
      Edit_PNSchArr[i]->Text = Str;
      sprintf( Str, "%d", TimeBD[i] );
      Edit_KvoIspArr[i]->Text = Str;
    }
    if ( bFlagDisplaySN[i] == false ) // Серийный номер не отображался
    {
      if ( bFlagGetSerialNum[i] == true ) // Серийный номер был прочитан
      {
        bFlagDisplaySN[i] = true; // Серийный номер больше не выводить
        sprintf( Str, "%.06d", SerialNumArr[i] );
        Edit_ArrSerNum[i]->Text = Str;
      }
    }
  }
  if ( bFlagDisplay == true )
  {
    sprintf
        (
        Str,
        "dTSum: %d; dTmaxSum: %d; dTPeriod: %d; dTmaxPeriod: %d; миним. кол-во испытаний: %d",
        dTSum,
        dTmaxSum,
        dTPeriod,
        dTmaxPeriod,
        MinTimeBD
        );
    Panel_Info->Caption = Str;
  }
  bFlagDisplay = false;
  if ( SpinEdit_Time->Value * 1000 <= MinTimeBD )
  {
    Button_StopClick( 0 );
  }
}
//---------------------------------------------------------------------------
int TFormPuasson8BD::MinSchet(int * ArrSchet)
{
  int MaxVar, MinVar;
  int j;
  MaxVar = 0;
  MinVar = 0;
  for ( int i = 0; i < maxInd; i++ )
  {
    j = IndexArr[i];
    if ( MaxVar < ArrSchet[j] )
    {
      MaxVar = ArrSchet[j];
    }
  }
  MinVar = MaxVar;
  for ( int i = 0; i < maxInd; i++ )
  {
    j = IndexArr[i];
    if ( MinVar > ArrSchet[j] )
    {
      MinVar = ArrSchet[j];
    }
  }
  return MinVar;
}
//---------------------------------------------------------------------------
void __fastcall TFormPuasson8BD::TimerOn( void )
{
  Form_82_Start->Timer1->Interval = DIA_Interval;
  Form_82_Start->Timer1->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormPuasson8BD::TimerOff( void )
{
  Form_82_Start->Timer1->Enabled = false;
  Form_82_Start->Timer1->Interval = 150;
}
//---------------------------------------------------------------------------
void __fastcall TFormPuasson8BD::Button_detailClick(TObject *Sender)
{
  FormPuasson8BDPepErr->Show();        
}
//---------------------------------------------------------------------------
void __fastcall TFormPuasson8BD::CheckBox_AllBDClick(TObject *Sender)
{
  for ( int i = 0; i < 8; i++ )
  {
    CheckBox_AddrBDArr[i]->Checked = CheckBox_AllBD->Checked;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPuasson8BD::FileArrayInit( int IndexArr )
{
  sprintf( chLogFileName[ IndexArr ],
      "SN_%.06d_Addr_%.02d.txt",
      SerialNumArr[ IndexArr ],
      AddrBDArr[ IndexArr ] );
  handle[ IndexArr ] =
  open( chLogFileName[ IndexArr ],
      O_CREAT | O_APPEND | O_BINARY | O_WRONLY,
      S_IREAD | S_IWRITE );
  // close(handle); - нужна такая функция
}
//---------------------------------------------------------------------------
void __fastcall TFormPuasson8BD::FileWriteData( int IndexArr )
{
  sprintf
      ( shFileString,
      "%d\t%d\x0d\x0a",
      PSW[ IndexArr ],
      Chet[ IndexArr ] ); // \x0d\x0a - для перевода на новую строку
  write ( handle[ IndexArr ], shFileString, strlen( shFileString ) );
  SredMas[ IndexArr ][indexSM[ IndexArr ]] = Chet[ IndexArr ];
  indexSM[ IndexArr ]++;
}
//---------------------------------------------------------------------------
void __fastcall TFormPuasson8BD::FileWriteError( int IndexArr )
{
  sprintf
      ( shFileString,
      "%d\t%d\x0d\x0a",
      -1,
      -1 ); // \x0d\x0a - для перевода на новую строку
  write ( handle[ IndexArr ], shFileString, strlen( shFileString ) );
  SredMas[ IndexArr ][indexSM[ IndexArr ]] = -1;
  indexSM[ IndexArr ]++;
}
//---------------------------------------------------------------------------
void __fastcall TFormPuasson8BD::Button_ExitClick(TObject *Sender)
{
  Close();
  for ( int i = 0; i < 8; i++ )
  {
    Panel_Display_Arr[i]->Caption = "";
    //Edit_ArrSerNum[i]->Text = "";
    if ( Form_Graph_Arr[i] != 0 )
    {
      Form_Graph_Arr[i]->Close();
      delete Form_Graph_Arr[i];
      Form_Graph_Arr[i] = 0;
    }
  }
  Panel_Info->Caption = "";
  // Вызвать обработчик события хотябы 1 раз
  CheckBox_AllBD->Checked = true;
  CheckBox_AllBD->Checked = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormPuasson8BD::Button_Graph_01Click(TObject *Sender)
{
  siFlagGraph = 1;
  PostroitGrafik();
}
//---------------------------------------------------------------------------
void __fastcall TFormPuasson8BD::Button_Graph_02Click(TObject *Sender)
{
  siFlagGraph = 2;
  PostroitGrafik();
}
//---------------------------------------------------------------------------
void __fastcall TFormPuasson8BD::Button_Graph_03Click(TObject *Sender)
{
  siFlagGraph = 3;
  PostroitGrafik();
}
//---------------------------------------------------------------------------
void __fastcall TFormPuasson8BD::Button_Graph_04Click(TObject *Sender)
{
  siFlagGraph = 4;
  PostroitGrafik();
}
//---------------------------------------------------------------------------
void __fastcall TFormPuasson8BD::Button_Graph_05Click(TObject *Sender)
{
  siFlagGraph = 5;
  PostroitGrafik();
}
//---------------------------------------------------------------------------
void __fastcall TFormPuasson8BD::Button_Graph_06Click(TObject *Sender)
{
  siFlagGraph = 6;
  PostroitGrafik();
}
//---------------------------------------------------------------------------
void __fastcall TFormPuasson8BD::Button_Graph_07Click(TObject *Sender)
{
  siFlagGraph = 7;
  PostroitGrafik();
}
//---------------------------------------------------------------------------
void __fastcall TFormPuasson8BD::Button_Graph_08Click(TObject *Sender)
{
  siFlagGraph = 8;
  PostroitGrafik();
}
//---------------------------------------------------------------------------
void TFormPuasson8BD::PostroitGrafik(void)
{
  if ( (siFlagGraph > 0) && (siFlagGraph <= 8) )
  {
    if ( Form_Graph_Arr[siFlagGraph-1] == 0 )
    {
      Form_Graph_Arr[siFlagGraph-1] = new TForm_Graph (Application);
    }
  }
  if ( Form_Graph_Arr[siFlagGraph-1] == 0 )
  {
    return;
  }
  // Операторы настройки, если они нужны
  Form_Graph_Arr[siFlagGraph-1]->ptrForm8BD = this;
  Form_Graph_Arr[siFlagGraph-1]->siFlagGraph = siFlagGraph;
  Form_Graph_Arr[siFlagGraph-1]->Name = "Form_Graph_0" + IntToStr(siFlagGraph); // Имена не должны повторяться, иначе ошибка выполнения
  Form_Graph_Arr[siFlagGraph-1]->Caption = "График для БД №  " + IntToStr(siFlagGraph);
  Form_Graph_Arr[siFlagGraph-1]->PostrGrafAll();
  Form_Graph_Arr[siFlagGraph-1]->Show();
}
//---------------------------------------------------------------------------
void __fastcall TFormPuasson8BD::Button_GraphClick(TObject *Sender)
{
  /* Функция-заглушка */;
  //  Kisp = StrToInt( SpinEdit_kolichestvo->Text );
  //if ( FlagWork == false )
  //{
  //  Graph(); // График из файла
  //}
  //else
  //{
  //  GraphWork(); // График из буфера
  //}
}
//---------------------------------------------------------------------------
void TFormPuasson8BD::UpdateGraph( int NomerBD ) // Обновлять графики (0 <= NomerBD < 8)
{
  if ( Form_Graph_Arr[NomerBD] != 0 ) // Создана форма с графиком
  {
    if ( Form_Graph_Arr[NomerBD]->bFlagOtkrytoyFormy == true )
    {
      //Form_Graph_Arr[NomerBD]->PostrGrafAll();
      Form_Graph_Arr[NomerBD]->Timer_ForGraphUpdate->Enabled = true;    
    }
  }
}
//---------------------------------------------------------------------------


