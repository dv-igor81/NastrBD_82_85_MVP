//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit_85Old_ProvPoisson.h"
#include <Inifiles.hpp>
#include <math.h>
#include "Unit_85Old_Grafik.h"
#include <fstream.h>
#include "Unit_85Old_main.h"
#include "Unit_85Old_BDInterface.h"
//---------------------------------------------------------------------------
#include <stdio.h>
#include "Unit_85Old_RS232.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define NMAS 20000
#define KolPoisson 20000
TForm_85Old_Poisson *Form_85Old_Poisson;
extern const char * IniFileName; //="poissonBD85.ini";

float SredMas[NMAS];
union
{
  unsigned int in;
  unsigned char ch[2];
} uu;
union
{
  float ff;
  unsigned char ch[4];
} uuf;
extern union
{
  unsigned long ll;
  unsigned char ch[4];
} uul;

AnsiString str;
AnsiString put = "C:\\TCPM\\BD85";
AnsiString name;
AnsiString filename;
Set< char, 0, 255 > Dig;
double y[KolPoisson];
double yy[KolPoisson];
int MaxPoisson;
int Spec[10000];

unsigned int MaxZn2, MinZn2;
unsigned int MaxZn, MinZn;
int por2 = 0; //порядок числа
int por = 0;
bool WorkCancel = false;
int LovErr = 0;
unsigned int KolIsp;
//------------------------------------------------------------------------------
bool Work;
extern bool flagPort_85Old;
extern int PortNum;
extern Port232 com232;
extern unsigned char buf_write[16];
extern unsigned char * pbuf_write; // Буфер для записи
extern unsigned char buf_read[16];
extern unsigned char * pbuf_read; // Буфер для чтения
union
{
  unsigned int ui;
  unsigned char uc[2];
} uu1, uu2;
union
{
  unsigned long Lrez;
  unsigned char Ch[4];
} uurez;

//------------------------------------------------------------------------------
__fastcall TForm_85Old_Poisson::TForm_85Old_Poisson(TComponent* Owner)
        : TForm(Owner)
{
  Dig << ' ' << ',' << '+' << '-' << '.' << '0' << '1' << '2'
      << '3' << '4' << '5' << '6' << '7' << '8' << '9' << 'E' << 'e'; // Заполнение множества
  // Получим размер формы из INI-файла
  TIniFile * IniFile = new TIniFile( IniFileName );
  try
  {
    Form_85Old_Poisson->Width = IniFile->ReadInteger( "Form_85Old_ProvPoisson", "PoissonWidth", 537 );
    Form_85Old_Poisson->Height = IniFile->ReadInteger( "Form_85Old_ProvPoisson", "PoissonHeight", 372 );
    Edit33->Text = IniFile->ReadString( "Form_85Old_ProvPoisson", "Edit33", "poisson.txt" );
    delete IniFile;
  }
  catch(...)
  {
    delete IniFile;
  }
  Button2->Enabled = false;
  FlagWork = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm_85Old_Poisson::Button1Click(TObject *Sender)
{
//НАЧАЛИ
    if (!flagPort_85Old)
   { Application->MessageBox("Вы не открыли порт",
                         "ВНИМАНИЕ",MB_ICONSTOP);Button2-> Enabled=false;return;
    }
Nisp=0;
Button2-> Enabled=true;
Form_85Old_GrafPoisson->CheckLog->Checked = false;//масштаб линейный
for(int j=1;j<=Edit0->Text.Length();j++){if(!Dig.Contains(Edit0->Text[j]))
{Application->MessageBox("Вы ввели не цифровые символы",
                         "Кол-во испытаний",MB_ICONSTOP);Button2-> Enabled=false;return;}}
str=Edit0->Text;
if(str.AnsiPos(".")||str.AnsiPos(",")||str.AnsiPos("E")||str.AnsiPos("e"))
{Application->MessageBox("Число должно быть целым",
                         "Кол-во испытаний",MB_ICONSTOP);Button2-> Enabled=false;return;}

Kisp=StrToInt(str);//Количество испытаний
if(Kisp>NMAS)
{Application->MessageBox("Число должно быть <=20000",
                         "Кол-во испытаний",MB_ICONSTOP);Button2-> Enabled=false;return;}

CreateDir(put);
filename=AnsiString(put)+AnsiString("\\")+AnsiString(Edit33->Text);
if(FileExists(filename))
{
AnsiString filename2= "Файл "+filename+ " уже существует";
if(Application->MessageBox(filename2.c_str(),"Перезаписать?",MB_YESNO)!=IDYES)
   {Button2-> Enabled=false;
    return;
   }
}


   Work=true;
   WorkCancel=true;
   FlagWork=true;
      com232.FlushBufs();

      
Form_85Old_Poisson->StatusBar1->Panels->Items[0]->Text="Номер испытания";
Application->ProcessMessages();
Button1-> Enabled=false;
//******************************************************************************

Nisp=1;
DWORD error;
AnsiString StrError;
long time1,time2;
unsigned char ShetGotov;
unsigned int Shet;

for(;;)
{
      do // до тех пор пока не будет установлен флаг ГОТОВНОСТИ СЧЕТА
      {  err=GetSSP(&Form_85Old_Main->PSW);   // опрашиваем слово состояние программы БД
         if(!err)break;
         Application->ProcessMessages();
      }
      while((Form_85Old_Main->PSW & 0x01)!=0x01);
      err=GetCountImp(&Shet);
      if(!err)break;

Form_85Old_Poisson->StatusBar1->Panels->Items[1]->Text=IntToStr(Nisp);
Application->ProcessMessages();

SredMas[Nisp-1]=Shet;

Edit1->Text=IntToStr((int)SredMas[Nisp-1]);Application->ProcessMessages();// интенсивность 1

if(Nisp>2)
{

Sum=0;
for(int k=0;k<Nisp;k++)
{
Sum=Sum+ SredMas[k];
}
Sum=Sum/Nisp;//среднее значение
Disp=0;
for(int k=0;k<Nisp;k++)
{
Disp=Disp+(SredMas[k]-Sum)* (SredMas[k]-Sum);
}
if(Nisp>1)Disp=Disp/(Nisp-1);else Disp=0;//Дисперсия
Krit=(Disp-Sum)/Sum;//Критерий Морозова


  Edit9->Text=FormatFloat("0.00",Sum) ;Application->ProcessMessages();
  Edit17->Text=FormatFloat("0.00",Disp);Application->ProcessMessages();
  Edit25->Text=FormatFloat("0.00",Krit);Application->ProcessMessages();


}//if(Nisp>2)

Nisp++;
if(Nisp==Kisp)break;
Application->ProcessMessages();
if(!WorkCancel)break;
}
//******************************************************************************
kon:
Work=false;


Application->ProcessMessages();
Zapis();//результаты испытания - в файл
Application->ProcessMessages();
Button1-> Enabled=true;Application->ProcessMessages();
Button2-> Enabled=false;Application->ProcessMessages();
Form_85Old_Poisson->StatusBar1->Panels->Items[0]->Text=" ";Application->ProcessMessages();
Form_85Old_Poisson->StatusBar1->Panels->Items[1]->Text=" ";Application->ProcessMessages();

Application->MessageBox("Испытание закончено",
                         "Внимание!",MB_ICONINFORMATION);

}
//---------------------------------------------------------------------------
void __fastcall TForm_85Old_Poisson::Button2Click(TObject *Sender)
{

WorkCancel=false;
Application->ProcessMessages();
 FlagWork=false;
Zapis();//результаты испытания - в файл
Application->ProcessMessages();

//СТОП
Button1-> Enabled=true;Application->ProcessMessages();
Button2-> Enabled=false;Application->ProcessMessages();
Form_85Old_Poisson->StatusBar1->Panels->Items[0]->Text=" ";Application->ProcessMessages();
Form_85Old_Poisson->StatusBar1->Panels->Items[1]->Text=" ";Application->ProcessMessages();
}
//---------------------------------------------------------------------------
void __fastcall TForm_85Old_Poisson::Button3Click(TObject *Sender)
{
//График БД1

if(!FlagWork)Graf(1);
else GrafWork(1);

}
//---------------------------------------------------------------------------
void  TForm_85Old_Poisson::Graf(int nom)
{
//Просмотр графика по окончании работы(данные из файла)
//filename=AnsiString(put)+AnsiString("\\")+AnsiString("poisson.txt");

filename=AnsiString(put)+AnsiString("\\")+AnsiString(Edit33->Text);

if(!FileExists(filename))
{
AnsiString filename2= "Файл "+filename+ " не существует";
Application->MessageBox(filename2.c_str(),"Внимание",MB_ICONSTOP);
return;
}
fstream fil2;
fil2.open(filename.c_str(),ios::in);
if(!fil2){ AnsiString filename2= "Файл "+filename+ " не открывается";
          Application->MessageBox(filename2.c_str(),"Внимание !",MB_ICONSTOP);
          return;
          }

//int data[NMAS];//Счёт, полученный для данного БД
for(int i=0;i<NMAS;i++)data[i]=0;

fil2>>Nisp;
for(int jj=0;jj<Nisp;jj++)
{
fil2>>data[jj];

}

fil2.close();
PostrGraf();

}
//______________________________________________________________________________
void __fastcall TForm_85Old_Poisson::ShowPoisson(TObject *Sender)
{
  Nisp = 0;
  KodGrafika = false;
  WorkCancel = true;
  KodVxod = false;
  Form_85Old_Poisson->Hide();
}
//---------------------------------------------------------------------------
void TForm_85Old_Poisson::Zapis()
{
if(!Nisp)return;
//filename=AnsiString(put)+AnsiString("\\")+AnsiString("poisson.txt");
filename=AnsiString(put)+AnsiString("\\")+AnsiString(Edit33->Text);

//if(FileExists(filename))DeleteFile( filename.c_str());
FILE *filW;//для чтения
filW=fopen(filename.c_str(),"wt");
       if(filW==NULL)
         {unsigned int err=GetLastError();
          AnsiString filename2= "Файл "+filename+ " не открылся благополучно";
          Application->MessageBox(filename2.c_str(),"Ошибка ",MB_ICONSTOP);
          return;
         }


fprintf(filW,"   %i\n",Nisp-1);
for(int j=0;j<Nisp-1;j++)
{
fprintf(filW,"%9.0f ",SredMas[j]);
fprintf(filW,"\n");
}

fclose(filW);
}
//_____________________________________________________________________________
double TForm_85Old_Poisson::poisson(int x,float Srednee)
{
/* //формула с факториалом
long double b,f=1;
b=pow(Srednee,x);
for(int i=1;i<=x;i++)f=f*i;
return b*exp(-Srednee)/f;
*/
long double b,f=0;
for(int i=1;i<=x;i++)f=f+log(i);//натуральный логарифм
//if(x==0)f=1;
if(x==0) exp(-1*Srednee);
b=exp(-1*Srednee+x*log(Srednee)-f);
return b;
}
//_____________________________________________________________________________
double TForm_85Old_Poisson::gausses(int X,float Sred)
{
long double f;
long double const Pi=3.1415926535897932384626433832795;
f=1/(sqrt(2*Pi*Sred))*exp(-pow(X-Sred,2)/(2*Sred));

return f;
}
//_____________________________________________________________________________
void __fastcall TForm_85Old_Poisson::Button11Click(TObject *Sender)
{
  // Выход
  // Закрытие формы
  Application->ProcessMessages();
  Form_85Old_Poisson->StatusBar1->Panels->Items[0]->Text = "";
  Form_85Old_Poisson->StatusBar1->Panels->Items[1]->Text = "";
  Button1->Enabled = true;

  // Запишем размер формы в INI-файл
  TIniFile * IniFile = new TIniFile( IniFileName );
  try
  {
    IniFile->WriteInteger( "Form_85Old_ProvPoisson", "PoissonWidth", Form_85Old_Poisson->Width );
    IniFile->WriteInteger( "Form_85Old_ProvPoisson", "PoissonHeight", Form_85Old_Poisson->Height );
    IniFile->WriteString( "Form_85Old_ProvPoisson", "Edit33", Edit33->Text );
    delete IniFile;
  }
  catch(...)
  {
    delete IniFile;
  }
  WorkCancel = false;
  if ( KodVxod )
  {
    Work = false;
    com232.FlushBufs();
    flagPort_85Old = false;
    com232.ClosePort();
  }
  Form_85Old_Poisson->Hide();
  Application->ProcessMessages();
}
//---------------------------------------------------------------------------
void  TForm_85Old_Poisson::GrafWork(int nom)
{
for(int jj=0;jj<Nisp;jj++)
{
data[jj]=SredMas[jj];
}
Nisp--;
PostrGraf();
}
//____________________________________________________________________________
void  TForm_85Old_Poisson::PostrGraf(void)
{
float Di,Kr;
if(Work)KolIsp=Nisp-1;else KolIsp=Nisp;
//Обработаем данные     KolIsp-количество снятых точек
unsigned long SumZn=0;for(int i=0;i<KolIsp;i++)SumZn=SumZn+data[i];//сумма полученного ряда
if(SumZn==0) {Application->MessageBox("Все значения нулевые",
                         "Внимание на файл",MB_ICONSTOP);return;}
float SredneeZn=(float)SumZn/(float)KolIsp;//среднее значение(середина распределения гистограммы)
//float sr=SredneeZn+10*sqrt(SredneeZn);
unsigned int KolIspZn=0,KolLog=0;
KolIspZn=KolIsp;
//Берём значения меньше sr
//int data2[NMAS];
//for(int i=0;i<KolIsp;i++)if(data[i]<sr)data2[KolIspZn++]=data[i];else KolLog++;
//SumZn=0;for(int i=0;i<KolIspZn;i++)SumZn=SumZn+data2[i];//сумма полученного нового ряда
//SredneeZn=(float)SumZn/(float)KolIspZn;//новое среднее значение(середина распределения гистограммы)

//Подготовим данные для вывода
for(int i=0;i<10000;i++)Spec[i]=0;
for(int i=0;i<KolIsp;i++)if((int)data[i]<10000)Spec[(int)data[i]]++;
MaxZn=0;for(int i=0;i<10000;i++)if(Spec[i]>MaxZn)MaxZn=Spec[i];//максимальное значение

//MaxPoisson=KolIspZn;
MaxPoisson=0;for(int i=0;i<10000;i++)if(Spec[i]>0)MaxPoisson=i;//максимальное значение
if( MaxPoisson<9800)MaxPoisson=MaxPoisson+200;

Di=0;
for(int k=0;k<KolIsp;k++)
Di=Di+(data[k]-SredneeZn)* (data[k]-SredneeZn);
if(KolIsp>1)Di=Di/(KolIsp-1);else Di=0;//Дисперсия
Kr=(Di-SredneeZn)/SredneeZn;//Критерий Морозова

//получим распределение Пуассона
for(int i=0;i<MaxPoisson;i++)
{y[i]=poisson(i,SredneeZn);
 yy[i]=poisson(i,SredneeZn+1.96*Di/sqrt(KolIspZn));
 y[i]=y[i]*KolIspZn;
 yy[i]=yy[i]*KolIspZn;
}

MaxZn=0;for(int i=0;i<MaxPoisson;i++)if(y[i]>MaxZn)MaxZn=y[i];
MaxZn2=0;for(int i=0;i<KolIsp;i++)if(data[i]>MaxZn2)MaxZn2=data[i];//максимальное значение
MinZn2=MaxZn2;for(int i=0;i<KolIsp;i++)if(data[i]<MinZn2)MinZn2=data[i];//минимальное значение
//Рассчитаем порог
float PorogZn=MaxZn2;
float SumKolLog=(float)KolIsp/1000.;//Количество допустимых ложных срабатываний
float Sum=0;
/*
//движемся от бесконечности к нулю
int i;
float  Ymin,Ymax;
for(i=MaxPoisson-1;i>0;i--)
{
Ymax=y[i];
Ymin=y[i-1];
Sum=Sum+(Ymax+0.5*(Ymin-Ymax));
if(Sum>=SumKolLog)break;
}
PorogZn=i;
*/
int i;
//движемся от нуля к бесконечности
SumKolLog=(float)KolIsp/1000.*999.;//Количество допустимых ложных срабатываний
float  Ymin,Ymax;
for(i=0;i<MaxPoisson;i++)
{
  if(i>=130)//Гаусс
  {Ymin=y[i-1];
   Ymax=y[i];
     if(Ymax>Ymin)Sum=Sum+(Ymin+0.5*(Ymax-Ymin));
     else         Sum=Sum+(Ymax+0.5*fabs(Ymin-Ymax));
   }
   else //Пуассон
   { Sum=Sum+y[i];
   }
   if(Sum>=SumKolLog)break;
}
PorogZn=i+1;

KolLog=0;
for(int i=0;i<KolIsp;i++)if(data[i]>PorogZn)KolLog++;

por=0;//порядок числа
float temp=MaxZn;
while(temp>=10)
{por++;temp=temp/10.;}
if(por>1)por--;

por2=0;//порядок максимального числа
temp=MaxZn2;
while(temp>=10)
{por2++;temp=temp/10.;}

int por3=0;//порядок минимального числа
temp=MinZn2;
while(temp>=10)
{por3++;temp=temp/10.;}
if(MinZn2>pow(10,por3))MinZn2=MinZn2-pow(10,por3);

//Выведем на график
Form_85Old_GrafPoisson->Show();
Form_85Old_GrafPoisson->Series1->Clear();//очистим график
Form_85Old_GrafPoisson->Series2->Clear();//очистим график
 //Линейный масштаб
Form_85Old_GrafPoisson->Chart1->BottomAxis->Minimum=0;
Form_85Old_GrafPoisson->Chart1->BottomAxis->Maximum=MaxZn2+pow(10,por2);
Form_85Old_GrafPoisson->Chart1->BottomAxis->Minimum=MinZn2;

Form_85Old_GrafPoisson->Chart1->LeftAxis->Minimum=0;
MaxZn=0;for(int i=0;i<10000;i++)if(Spec[i]>MaxZn)MaxZn=Spec[i];//максимальное значение
Form_85Old_GrafPoisson->Chart1->LeftAxis->Maximum=MaxZn+pow(10,por);
 //Логарифмический масштаб по оси Y
Form_85Old_GrafPoisson->Chart2->BottomAxis->Minimum=0;
Form_85Old_GrafPoisson->Chart2->BottomAxis->Maximum=MaxZn2+pow(10,por2);
Form_85Old_GrafPoisson->Chart2->BottomAxis->Minimum=MinZn2;

Form_85Old_GrafPoisson->Chart2->LeftAxis->Minimum=0;
if(MaxZn<=100000)Form_85Old_GrafPoisson->Chart2->LeftAxis->Maximum=100000;
if(MaxZn<=10000)Form_85Old_GrafPoisson->Chart2->LeftAxis->Maximum=10000;
if(MaxZn<=1000)Form_85Old_GrafPoisson->Chart2->LeftAxis->Maximum=1000;
if(MaxZn<=100)Form_85Old_GrafPoisson->Chart2->LeftAxis->Maximum=100;
if(MaxZn<=10)Form_85Old_GrafPoisson->Chart2->LeftAxis->Maximum=10;


if(Form_85Old_GrafPoisson->RadioButton1->Checked) //Пуассон
{

       if(Form_85Old_GrafPoisson->CheckLog->Checked)
          { //Логарифмический масштаб
           Form_85Old_GrafPoisson->Chart2->Visible=true;
           Form_85Old_GrafPoisson->Series3->Clear();
           Form_85Old_GrafPoisson->Series4->Clear();
           Form_85Old_GrafPoisson->Series5->Clear();
            Form_85Old_GrafPoisson->Chart2->Title->Text->Clear();
            Form_85Old_GrafPoisson->Chart2->Title->Text->Add("Распределение по Пуассону");
           for(int i=0;i<MaxPoisson;i++)Form_85Old_GrafPoisson->Series3->AddXY(i,y[i],clRed);//распределение Пуассона
           for(int i=0;i<MaxPoisson;i++)Form_85Old_GrafPoisson->Series5->AddXY(i,yy[i],clGreen);
           for(int i=0;i<=MaxZn2+1;i++)Form_85Old_GrafPoisson->Series4->AddXY(i,Spec[i],clBlack); //построим гистограмму
          }
      else
         { //Линейный масштаб
          Form_85Old_GrafPoisson->Chart2->Visible=false;
          Form_85Old_GrafPoisson->Chart1->Visible=true;
           Form_85Old_GrafPoisson->Chart1->Title->Text->Clear();
           Form_85Old_GrafPoisson->Chart1->Title->Text->Add("Распределение по Пуассону");
          Form_85Old_GrafPoisson->Series1->Clear();
          Form_85Old_GrafPoisson->Series2->Clear();
          Form_85Old_GrafPoisson->Series6->Clear();
          for(int i=0;i<MaxPoisson;i++)Form_85Old_GrafPoisson->Series1->AddXY(i,y[i],clRed);//распределение Пуассона
          for(int i=0;i<MaxPoisson;i++)Form_85Old_GrafPoisson->Series6->AddXY(i,yy[i],clGreen);
          for(int i=0;i<=MaxZn2+1;i++)Form_85Old_GrafPoisson->Series2->AddXY(i,Spec[i],clBlack); //построим гистограмму
         }
}
else //Посмотрим график - изменение от времени
{

    if(!Form_85Old_GrafPoisson->CheckLog->Checked)
       {//линейный масштаб
        Form_85Old_GrafPoisson->Chart2->Visible=false;
        Form_85Old_GrafPoisson->Chart1->Visible=true;
         Form_85Old_GrafPoisson->Chart1->Title->Text->Clear();
         Form_85Old_GrafPoisson->Chart1->Title->Text->Add("График счёта от времени");
        Form_85Old_GrafPoisson->Series1->Clear();
        Form_85Old_GrafPoisson->Series2->Clear();
        Form_85Old_GrafPoisson->Series6->Clear();
        Form_85Old_GrafPoisson->Chart1->BottomAxis->Minimum=0;
        Form_85Old_GrafPoisson->Chart1->BottomAxis->Maximum=KolIsp;
        Form_85Old_GrafPoisson->Chart1->LeftAxis->Minimum=0;
        unsigned int MaxZn3=0; for(int i=0;i<KolIsp;i++)
                         {if(Form_85Old_Poisson->data[i]>MaxZn3)MaxZn3 = Form_85Old_Poisson->data[i];}

        Form_85Old_GrafPoisson->Chart1->LeftAxis->Maximum=MaxZn3+10;
        for(int i=0;i<KolIsp;i++)Form_85Old_GrafPoisson->Series1->AddXY( i, Form_85Old_Poisson->data[i], clBlack );
        }
    else
        { //Логарифмический масштаб
         Form_85Old_GrafPoisson->Chart2->Visible = true;
         Form_85Old_GrafPoisson->Series3->Clear();
         Form_85Old_GrafPoisson->Series4->Clear();
         Form_85Old_GrafPoisson->Series5->Clear();
          Form_85Old_GrafPoisson->Chart2->Title->Text->Clear();
          Form_85Old_GrafPoisson->Chart2->Title->Text->Add("График счёта от времени");
          Form_85Old_GrafPoisson->Chart2->BottomAxis->Minimum=0;
          Form_85Old_GrafPoisson->Chart2->BottomAxis->Maximum=KolIsp;
          Form_85Old_GrafPoisson->Chart2->LeftAxis->Minimum=0;
          unsigned int MaxZn3=0; for(int i=0;i<KolIsp;i++)
                         {if(Form_85Old_Poisson->data[i]>MaxZn3)MaxZn3 = Form_85Old_Poisson->data[i];}
            if(MaxZn3<=100000)Form_85Old_GrafPoisson->Chart2->LeftAxis->Maximum=100000;
            if(MaxZn3<=10000)Form_85Old_GrafPoisson->Chart2->LeftAxis->Maximum=10000;
            if(MaxZn3<=1000)Form_85Old_GrafPoisson->Chart2->LeftAxis->Maximum=1000;
            if(MaxZn3<=100)Form_85Old_GrafPoisson->Chart2->LeftAxis->Maximum=100;
            if(MaxZn3<=10)Form_85Old_GrafPoisson->Chart2->LeftAxis->Maximum=10;

         for(int i=0;i<KolIsp;i++)Form_85Old_GrafPoisson->Series5->AddXY(i,Form_85Old_Poisson->data[i],clBlack);
        }


}

str=AnsiString("Среднее значение=")+FormatFloat("0.00",SredneeZn);
Form_85Old_GrafPoisson->Label1->Caption = str;
str = AnsiString("Значение порога=")+FormatFloat("0.00",PorogZn);
Form_85Old_GrafPoisson->Label2->Caption=str;
str=AnsiString("Вероятность ложных срабатываний*Е-3=")+FormatFloat("0.0000",(float)KolLog/(float)KolIsp*1000);
Form_85Old_GrafPoisson->Label3->Caption=str;
str=AnsiString("Количество измерений=")+IntToStr(KolIsp);
Form_85Old_GrafPoisson->Label4->Caption=str;



str=AnsiString("Дисперсия=")+FormatFloat("0.00",Di);
Form_85Old_GrafPoisson->Label5->Caption=str;

str=AnsiString("Коэф.Морозова=")+FormatFloat("0.0000",Kr);
Form_85Old_GrafPoisson->Label6->Caption=str;
}
//_______________________________________________________________________________
void __fastcall TForm_85Old_Poisson::ClosePoisson(TObject *Sender,
      TCloseAction &Action)
{
  Work = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm_85Old_Poisson::FormHide(TObject *Sender)
{
  Form_85Old_Main->Show();
}
//---------------------------------------------------------------------------

