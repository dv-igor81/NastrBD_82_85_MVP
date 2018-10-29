//-------------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Unit_85Old_RS232.h"
#include "Unit_85Old_main.h"
#include "Unit_85Old_BDInterface.h"
#include "Unit_85Old_ProvPoisson.h"
#include <Inifiles.hpp>
#include "Unit_FormDispet.h"
#include "Unit_82_Log.h"
//-------------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm_85Old_Main *Form_85Old_Main;
unsigned char buf_write[16],*pbuf_write=buf_write;   //Буфер для записи
unsigned char buf_read[16],*pbuf_read=buf_read;      //Буфер для чтения
unsigned int PortNum;     // Номер COM порта
bool flagPort_85Old = false;      // Состояние порта Открыт/закрыт

extern const char * IniFileName; // = "BD85.ini";
extern unsigned char UniAdr;
extern DWORD err;
extern Port232 com232;
//-------------------------------------------------------------------------------
extern AnsiString ProgrammVersion;
AnsiString FormCaption = "Настройка БД 85 (старый)";
//-------------------------------------------------------------------------------
__fastcall TForm_85Old_Main::TForm_85Old_Main(TComponent* Owner)
        : TForm(Owner)
{
  this->Caption = FormCaption;
  this->Caption = this->Caption + ProgrammVersion;
  T_Limit = 200;
  flagRefresh = true;
  bFlagCount = false;
  bRecordEn = false;
  uiRecNum = 0;
  ulRecCount = 0;
  bFlagWork = false;      // Флаг режима измерения включен/отключен
  FlagZapis = false;
  FlagZap = false;
  this->CreateFormFlag_BD85_Old = false; // false - форма не отображалась ещё
}
//-------------------------------------------------------------------------------
void __fastcall TForm_85Old_Main::OnWMSysCommand( TMessage& Message )
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
//-------------------------------------------------------------------------------
// Обработчик нажатия кнопки ОТКРЫТЬ
void __fastcall TForm_85Old_Main::OpenPortButtonClick(TObject *Sender)
            {
                int i;
                if (!flagPort_85Old)
                {
                    ClearForm();
                    OpenRS(UpDown1->Position); // инициализация выбранного порта
                    flagPort_85Old = true;
                    bFlagWork = true;
                    UniAdr = StrToInt(NewConnectionAdr->Text);
                    OpenPortButton->Caption = "ЗАКРЫТЬ";
                    Application->ProcessMessages();
                    SetParamButton->Enabled = true;
                    Application->ProcessMessages();
                    SetResetButton->Enabled = true;
                    Application->ProcessMessages();
                    ARCH_Con->Enabled = true;
                    Application->ProcessMessages();
                    Init();
                    MainCycle();
                }
                else
                {
                    bFlagWork = false;
                    SetResetButton->Enabled = false;
                    Application->ProcessMessages();
                    SetParamButton->Enabled = false;
                    Application->ProcessMessages();
                    com232.FlushBufs();
                    CloseRS();
                    OpenPortButton->Caption = "ОТКРЫТЬ";
                    Application->ProcessMessages();
                    ARCH_Con->Enabled = false;
                    Application->ProcessMessages();
                    flagPort_85Old = false;

                }
            }
//-------------------------------------------------------------------------------
//
#define STOP  {bFlagWork=false;SetResetButton->Enabled=false;CloseRS();OpenPortButton->Caption="ОТКРЫТЬ";flagPort_85Old = false;return;}
void __fastcall TForm_85Old_Main::Init(void)
        {

            if (flagPort_85Old)
                err = GetSSP(&PSW);
            if (!err)
                STOP;   // определение состояния программы БД
            if (flagPort_85Old)
                err = SetTimeInterval(8);
            if (!err)
                STOP; // устаналиваем режим вырабатывания временных интервалов Блоком детектирования
                      // с временем счета 0.2 сек
            if (flagPort_85Old)
                err = GetTimeInterval(&TimeInt);
            if (!err)
                STOP;
            if (TimeInt != 8)
            {
                Application->MessageBox("Значение не записалось в БД", "SetTimeInterval", MB_ICONINFORMATION);
                STOP
             }

            if (flagPort_85Old)
                err = GetTemp(&TprSred);
            if (!err)
                STOP;

            T_Limit = StrToInt(T_LimitEdit->Text);
            Application->ProcessMessages();

            if (!GetVersia(&Versia[0]))
                ShowMessage("Версия не читается!");
            Edit7->Text = (char)Versia[0];
            Application->ProcessMessages();
            Edit11->Text = (char)Versia[1];
            Application->ProcessMessages();
            Edit12->Text = (char)Versia[2];
            Application->ProcessMessages();
            Edit13->Text = (char)Versia[3];
            Application->ProcessMessages();

            if (flagPort_85Old)
            {
                err = ReadFlash(0, &DNUZ);
                if (!err)
                    STOP;
                DNUZ = DNUZ & 0x0000FFFF;
                err = ReadFlash(3, &UhiZ);
                if (!err)
                    STOP;
                UhiZ = UhiZ & 0x0000FFFF;

                err = ReadFlash(4, &IndAdrZ);
                if (!err)
                    STOP;
                IndAdrZ = IndAdrZ & 0x000000FF;
                err = ReadFlash(5, &GrpAdrZ);
                if (!err)
                    STOP;
                GrpAdrZ = GrpAdrZ & 0x000000FF;

                err = ReadFlash(8, &SIMstart);
                if (!err)
                    STOP;
                SIMstart = SIMstart & 0x0000FFFF;
                err = ReadFlash(9, &SIMmax);
                if (!err)
                    STOP;
                SIMmax = SIMmax & 0x0000FFFF;


                GetARH(&KodRS);
                if (!err)
                    STOP;
                if (!KodRS)
                {
                    RS1->Checked = true;
                    Application->ProcessMessages();
                    RS3->Checked = false;
                    Application->ProcessMessages();
                    ARCH_Con->Kind = bkRetry;
                    Application->ProcessMessages();
                    ARCH_Con->Caption = "Включена";
                    Application->ProcessMessages();
                    ARCH_Con->ModalResult = mrNone;
                    Application->ProcessMessages();
                    ARCH_Con->Font->Color = clGreen;
                    Application->ProcessMessages();
                }
                else
                {
                    RS1->Checked = false;
                    Application->ProcessMessages();
                    RS3->Checked = true;
                    Application->ProcessMessages();
                    ARCH_Con->Kind = bkNo;
                    Application->ProcessMessages();
                    ARCH_Con->Caption = "Отключена  ";
                    Application->ProcessMessages();
                    ARCH_Con->ModalResult = mrNone;
                    Application->ProcessMessages();
                    ARCH_Con->Font->Color = clRed;
                    Application->ProcessMessages();
                }
                Application->ProcessMessages();

                SetDNUCodeEdit->Text = IntToStr(DNUZ);
                Application->ProcessMessages();
                SetDNUEdit->Text = FloatToStrF(2.5 * StrToInt(SetDNUCodeEdit->Text) / 4095, ffGeneral, 4, 8);
                Application->ProcessMessages();
                DNUZZnach = StrToFloat(SetDNUEdit->Text);
                SetUhiCodeEdit->Text = IntToStr(UhiZ);
                Application->ProcessMessages();
                SetUhiEdit->Text = FloatToStrF((UhiZ * 2.5 / 4096 * 1000 * 0.978), ffGeneral, 4, 8);
                Application->ProcessMessages(); // значение напряжения высокого измеренного - на экран
                SetIndAdrEdit->Text = IntToStr(IndAdrZ);
                Application->ProcessMessages(); // Индивидуальный адрес заданный
                SetGrpAdrEdit->Text = GrpAdrZ;
                Application->ProcessMessages(); // Групповой адрес заданный

                Edit6->Text = IntToStr(SIMstart);
                Application->ProcessMessages();
                Edit18->Text = IntToStr(SIMmax);
                Application->ProcessMessages();

                GetSIM4(&SIM4);
                Edit16->Text = IntToStr(SIM4);
                Application->ProcessMessages();

            }
            TSchet = 0;
            count = 0;
            SumSchet = 0;
            SumCountEdit->Text = 0; // суммарный счет за время измерения
            TCountEdit->Text = 0;
        }
//-------------------------------------------------------------------------------------------

void __fastcall TForm_85Old_Main::MainCycle(void)
{  unsigned char i;
      unsigned char const MasRez[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
      AnsiString str="";
      int one=0;
   do
   {
      do // до тех пор пока не будет установлен флаг ГОТОВНОСТИ СЧЕТА
      {  if (bFlagWork)err=GetSSP(&PSW);if(!err)STOP;
         if(!one)
          {one++;if(one==6)one=0;//чтоб увидеть зависание
         str="";
         for(int k=0;k<8;k++){if(PSW&MasRez[7-k])str=str+"1"; else str=str+"0";Application->ProcessMessages();}
         if (bFlagWork)Edit10->Text=str; Application->ProcessMessages();
         if (bFlagWork)Edit23->Text="0x"+IntToHex(PSW,2); Application->ProcessMessages();
           }
      } while(((PSW & 0x01)!=0x01)&&bFlagWork);

      str="";
      for(int k=0;k<8;k++){if(PSW&MasRez[7-k])str=str+"1"; else str=str+"0";Application->ProcessMessages();}
       if (bFlagWork)Edit10->Text=str; Application->ProcessMessages();
       if (bFlagWork)Edit23->Text="0x"+IntToHex(PSW,2); Application->ProcessMessages();

      if (bFlagWork)err=GetCountImp(&Count02); if(!err) STOP;
      count++;               // счетчик 0.2 интервалов тикает
      flagFirst=count % 5;   // Обновление данных каждую 1 сек
      TSchet=TSchet+Count02; // счет за 1 сек

      if ((flagFirst==0))    // каждую секунду на экране обновляется .....
      {  Count1Edit->Text=FormatFloat("0.00",(float)SumSchet/((float)count/5.0));                 // реальный счет за 1 сек на экран
         if(((count/5)<=T_Limit)&&bFlagCount)      // проверяем окончание времени счета импульсов
         {  SumSchet=SumSchet+TSchet;
            SumCountEdit->Text=SumSchet;           // суммарный счет за время измерения - на экран
            TCountEdit->Text=count/5;              // время измерения в секундах - на экран
            if (bFlagWork)Count1Edit->Text=FormatFloat("0.00",(float)SumSchet/((float)count/5.0)); Application->ProcessMessages();
         }

         if (bFlagWork)Edit14->Text=FormatFloat("0.00",(float)TSchet); Application->ProcessMessages();
         TSchet=0;
      }
         if((count/5)==T_Limit)
         {  bFlagCount=false;
            StartCountButton->Caption="СТАРТ";Application->ProcessMessages();
         }

         if (bFlagWork)err=GetUhi(&UhiI);if(!err) STOP;                           // получаем код напряжения высокого измеренного
         if (bFlagWork)UhiICodeEdit->Text=IntToStr(UhiI); Application->ProcessMessages();      // код напряжения высокого измеренного - на экран
         if (bFlagWork)
         {//===>>
           UhiIEdit->Text = FormatFloat("0.0",(UhiI * 2.5 / 4096*1000*0.978));
           //UhiIEdit->Text = FormatFloat("0.0",( 150 ));
           Application->ProcessMessages(); // значение напряжения высокого измеренного - на экран
         }//<<===
         if (bFlagWork)err=GetTemp(&Tpr);if(!err) STOP;                          // получаем код температуры контроллера
         if (bFlagWork)TprCodeEdit->Text=IntToStr(Tpr); Application->ProcessMessages();       // код температуры контроллера - на экран
         if (bFlagWork)TprEdit->Text=FormatFloat("0.00",TConvert(Tpr));Application->ProcessMessages(); // значение температуры контроллера - на экран

      
         if (bFlagWork)err=GetDNU(&DNUI); if(!err) STOP;              // Значение дискриминатора нижнего уровня измеренное
         if (bFlagWork)DNUICodeEdit->Text=IntToStr(DNUI); Application->ProcessMessages();
         if (bFlagWork)DNUIEdit->Text=FormatFloat("0.000",(DNUI*2.5/4095));Application->ProcessMessages();


         if (bFlagWork)err=GetSIM3(&SIM3);if(!err) STOP;
         if (bFlagWork)EditSIMd->Text=IntToStr(SIM3);Application->ProcessMessages();  //значение ШИМа  длительность
         if (bFlagWork)Edit4->Text=FormatFloat("0.00",(float)SIM3/16.777216);Application->ProcessMessages();
         if (bFlagWork)GetSIM4(&SIM4);
         if (bFlagWork)EditSIMp->Text=IntToStr(SIM4);Application->ProcessMessages();  //значение ШИМа  период
         if (bFlagWork)EditSIM3zn->Text=FormatFloat("0.00",(float)SIM4/16.777216);Application->ProcessMessages();


         if (bFlagWork)err=GetIndAdr(&IndAdr);if(!err) STOP;        // Индивидуальный адрес
             if (bFlagWork)IndAdrEdit->Text=IntToStr(IndAdr);Application->ProcessMessages();
         if (bFlagWork)err=GetGrpAdr(&GrpAdr);Application->ProcessMessages();                       // Групповой адрес
             if (bFlagWork)GrpAdrEdit->Text=IntToStr(GrpAdr);if(!err) STOP; Application->ProcessMessages();



   if(FlagZap)
   {
     FlagZap = false;
     ZapEEPROM();}
   }
   while(bFlagWork);
}
//----------------------------------------------------------------------------------
// преобразования значения температуры в из кодов в градусы Цельсия
float __fastcall TForm_85Old_Main::TConvert(int Temper)
{  float TemperC,tmp;
  tmp=float(Temper);
   if(tmp>1114)
     TemperC=-50*(tmp-1114)/(1252-1114);
   else
     TemperC=50*(1114-tmp)/(1114-969);
   return TemperC;

}
//---------------------------------------------------------------------------
void __fastcall TForm_85Old_Main::SetParamButtonClick(TObject *Sender)
{
    if (!flagPort_85Old)
   { Application->MessageBox("Вы не открыли порт","ВНИМАНИЕ",MB_ICONSTOP);return;}
FlagZap=true;
}
//------------------------------------------------------------------------------
void TForm_85Old_Main::ZapEEPROM(void)
{

SetParamButton->Enabled=false;

  if (StrToInt(SetDNUCodeEdit->Text)!=DNUZ)
    { err=SetDNU(StrToInt(SetDNUCodeEdit->Text));
      SetDNUEdit->Text=FloatToStrF(2.5*StrToInt(SetDNUCodeEdit->Text)/4095,ffGeneral,4,8);
      DNUZZnach=StrToFloat(SetDNUEdit->Text);
    }
  if (StrToInt(SetUhiCodeEdit->Text)!=UhiZ) err=SetUhi(StrToInt(SetUhiCodeEdit->Text));

  if (StrToInt(SetIndAdrEdit->Text)!=IndAdrZ)  err=SetIndAdr(StrToInt(SetIndAdrEdit->Text));
  if (StrToInt(SetGrpAdrEdit->Text)!=GrpAdrZ)  err=SetGrpAdr(StrToInt(SetGrpAdrEdit->Text));

   err=SetSIM3(StrToInt(Edit6->Text));
  if (StrToInt(Edit18->Text)!=SIMmax)  err=WriteFlash(9,StrToInt(Edit18->Text));

   err=SetSIM4(StrToInt(Edit16->Text));

  if(RS1->Checked)KodRS=0;else KodRS=1;
  SetARH(KodRS);


  err=ReadFlash(0,&DNUZ);        DNUZ=DNUZ&0x0000FFFF;
if(StrToInt(SetDNUCodeEdit->Text)!= DNUZ)Application->MessageBox("Значение не записалось в EEPROM","ДНУ",MB_ICONINFORMATION);
  err=ReadFlash(3,&UhiZ);        UhiZ=UhiZ&0x0000FFFF;
if(StrToInt(SetUhiCodeEdit->Text)!= UhiZ)Application->MessageBox("Значение не записалось в EEPROM","UhiZ",MB_ICONINFORMATION);

 err=ReadFlash(4,&IndAdrZ);       IndAdrZ=IndAdrZ&0x000000FF;
if(StrToInt(SetIndAdrEdit->Text)!= IndAdrZ)Application->MessageBox("Значение не записалось в EEPROM","IndAdrZ",MB_ICONINFORMATION);
  err=ReadFlash(5,&GrpAdrZ);     GrpAdrZ=GrpAdrZ&0x000000FF;
if(StrToInt(SetGrpAdrEdit->Text)!= GrpAdrZ)Application->MessageBox("Значение не записалось в EEPROM","GrpAdrZ",MB_ICONINFORMATION);

  err=ReadFlash(8,&SIMstart);    SIMstart=SIMstart&0x0000FFFF;
if(StrToInt(Edit6->Text)!= SIMstart)Application->MessageBox("Значение не записалось в EEPROM","ШИМ начальный",MB_ICONINFORMATION);
  err=ReadFlash(9,&SIMmax);     SIMmax=SIMmax&0x0000FFFF;
if(StrToInt(Edit18->Text)!= SIMmax) Application->MessageBox("Значение не записалось в EEPROM","ШИМ максимальный",MB_ICONINFORMATION);
unsigned char KodRSzap;

  err=GetARH(&KodRSzap);

  if(!KodRSzap){RS1->Checked=true;    Application->ProcessMessages();
             RS3->Checked=false;      Application->ProcessMessages();
             ARCH_Con->Kind = bkRetry ;Application->ProcessMessages();
             ARCH_Con->Caption="Включена";Application->ProcessMessages();
             ARCH_Con->ModalResult = mrNone;Application->ProcessMessages();
             ARCH_Con->Font->Color=clGreen;Application->ProcessMessages();
             }
      else  {RS1->Checked=false;Application->ProcessMessages();
             RS3->Checked=true; Application->ProcessMessages();
             ARCH_Con->Kind = bkNo ; Application->ProcessMessages();
             ARCH_Con->Caption="Отключена  ";Application->ProcessMessages();
             ARCH_Con->ModalResult = mrNone; Application->ProcessMessages();
             ARCH_Con->Font->Color=clRed;   Application->ProcessMessages();
             }
if(KodRS!= KodRSzap)Application->MessageBox("Значение не записалось в EEPROM","Обратная связь",MB_ICONINFORMATION);



  SetDNUCodeEdit->Text=IntToStr(DNUZ);Application->ProcessMessages();
  SetUhiCodeEdit->Text=IntToStr(UhiZ);Application->ProcessMessages();
  SetUhiEdit->Text=FloatToStrF((UhiZ*2.5/4096*1000*0.978),ffGeneral,4,8);Application->ProcessMessages(); // значение напряжения высокого измеренного - на экран
  SetIndAdrEdit->Text=IntToStr(IndAdrZ);Application->ProcessMessages();   // Индивидуальный адрес заданный
    SetGrpAdrEdit->Text=IntToStr(GrpAdrZ);Application->ProcessMessages();             // Групповой адрес заданный
  Edit6->Text= IntToStr(SIMstart);Application->ProcessMessages();//ШИМ начальный
  Edit18->Text= IntToStr(SIMmax); Application->ProcessMessages();//ШИМ максимальный

Application->MessageBox("Закончена запись в EEPROM!","Внимание!",MB_ICONINFORMATION);
FlagZapis=true;



SetParamButton->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm_85Old_Main::FormClose(TObject *Sender, TCloseAction &Action)
{
  bFlagWork = false;
  if ( flagPort_85Old )
  {
    CloseRS();
  }
  // Получим размер формы из INI-файла
  TIniFile * IniFile = new TIniFile( IniFileName );
  try
  {
    IniFile->WriteInteger( "Form_85Old_Main", "MainFormWidth", Form_85Old_Main->Width );
    IniFile->WriteInteger( "Form_85Old_Main", "MainFormHeight", Form_85Old_Main->Height );
    IniFile->WriteString( "Form_85Old_Main", "T_LimitEdit", T_LimitEdit->Text );
    IniFile->WriteInteger( "Form_85Old_Main", "UpDown1", UpDown1->Position );
    delete IniFile;
  }
  catch(...)
  {
    delete IniFile;
  }
#ifdef _DIA_OBEDINENIE_
  CreateFormFlag_BD85_Old = false;
#endif
  FormDispet->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm_85Old_Main::StartCountButtonClick(TObject *Sender)
{
  if ( !flagPort_85Old )
  {
    Application->MessageBox( "Вы не открыли порт", "ВНИМАНИЕ", MB_ICONSTOP );
    return;
  }
  if ( bFlagCount )
  {
    bFlagCount = false;
    StartCountButton->Caption = "СТАРТ";
  }
  else
  {
    bFlagCount = true;
    StartCountButton->Caption = "СТОП";
    count = 0;
    SumSchet = 0;
    TSchet = 0;
    T_Limit = StrToInt( T_LimitEdit->Text );
  }
}
//---------------------------------------------------------------------------
void  TForm_85Old_Main::ClearForm(void)
{
  SetDNUCodeEdit->Text = "";
  SetDNUEdit->Text = "";
  UhiICodeEdit->Text = ""; // код напряжения высокого измеренного - на экран
  UhiIEdit->Text = "";
  TprCodeEdit->Text = ""; // код температуры контроллера - на экран
  TprEdit->Text = "";
  DNUICodeEdit->Text = "";
  DNUIEdit->Text = "";
  IndAdrEdit->Text = "";
  GrpAdrEdit->Text = "";
  Edit7->Text = "";
  Edit11->Text = "";
  Edit12->Text = "";
  Edit13->Text = "";
  SetUhiCodeEdit->Text = "";
  SetUhiEdit->Text = ""; // значение напряжения высокого измеренного - на экран
  SetIndAdrEdit->Text = ""; // Индивидуальный адрес заданный
  SetGrpAdrEdit->Text = ""; // Групповой адрес заданный
  Edit6->Text = "";
  Edit18->Text = "";
  Count1Edit->Text = "0.0"; // реальный счет за 1 сек на экран
  SumCountEdit->Text = "0"; // суммарный счет за время измерения на экран
  TCountEdit->Text = "0"; // время на экран
  EditSIMd->Text = ""; //значение ШИМа - длительности
  EditSIMp->Text = ""; //значение ШИМа - периода
}
//---------------------------------------------------------------------------
void __fastcall TForm_85Old_Main::Button5Click(TObject *Sender)
{
  Form_85Old_Poisson->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm_85Old_Main::FormShow(TObject *Sender)
{
  if( FormDispet != 0 )
  {
    FormDispet->DiaGetWinHandle( this->Handle );  
  }
  if ( CreateFormFlag_BD85_Old == false )
  {
    CreateFormFlag_BD85_Old = true;
    AnsiString asFullFileName;
    AnsiString asInfo;
    asFullFileName = ParamStr(0); // Нулевой параметр командной строки (имя файла)
    asInfo = this->Caption.c_str();
    asInfo += "; ";
    asInfo += "<" + asFullFileName + ">";

    WriteLog_DIA( asInfo.c_str() );
  }
  // Получим размер формы из INI-файла
  TIniFile * IniFile = new TIniFile( IniFileName );
  try
  {
    Form_85Old_Main->Width = IniFile->ReadInteger( "Form_85Old_Main", "MainFormWidth", 810 );
    Form_85Old_Main->Height = IniFile->ReadInteger( "Form_85Old_Main", "MainFormHeight", 672 );
    T_LimitEdit->Text = IniFile->ReadString( "Form_85Old_Main", "T_LimitEdit", "200" );
    UpDown1->Position = IniFile->ReadInteger( "Form_85Old_Main", "UpDown1", 1 );
    delete IniFile;
  }
  catch(...)
  {
    delete IniFile;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_85Old_Main::SetResetButtonClick(TObject *Sender)
{
  TSchet = 0;
  count = 0;
  SumSchet = 0;
  SumCountEdit->Text = 0; // суммарный счет за время измерения
  TCountEdit->Text = 0;
}
//---------------------------------------------------------------------------


