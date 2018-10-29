//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit_85Old_Grafik.h"
#include <Inifiles.hpp>
#include "Unit_85Old_ProvPoisson.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#define KolPoisson 20000
TForm_85Old_GrafPoisson *Form_85Old_GrafPoisson;
extern const char* IniFileName;
extern double y[KolPoisson];
extern double yy[KolPoisson];
extern int MaxPoisson;
extern int Spec[10000];
extern unsigned int MaxZn2,MinZn2;
extern unsigned int MaxZn;
extern int por2,por;//порядок числа
extern unsigned int KolIsp;
//---------------------------------------------------------------------------
__fastcall TForm_85Old_GrafPoisson::TForm_85Old_GrafPoisson(TComponent* Owner)
        : TForm(Owner)
{
  //  Получим размер формы из INI-файла
  TIniFile * IniFile = new TIniFile( IniFileName );
  try
  {
    Form_85Old_GrafPoisson->Width = IniFile->ReadInteger( "Form_85Old_Grafik", "GrafPoissonWidth", 0 );
    Form_85Old_GrafPoisson->Height = IniFile->ReadInteger( "Form_85Old_Grafik", "GrafPoissonHeight", 0 );
    delete IniFile;
  }
  catch(...)
  {
    delete IniFile;
  }
  if ( Form_85Old_GrafPoisson->Width <= 546 )
  {
    Form_85Old_GrafPoisson->Width = 546;
  }
  if ( Form_85Old_GrafPoisson->Height <= 424 )
  {
    Form_85Old_GrafPoisson->Height=424;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_85Old_GrafPoisson::CloseGraf(TObject *Sender,
      TCloseAction &Action)
{
  // Запишем размер формы в INI-файл
  TIniFile * IniFile = new TIniFile( IniFileName );
  try
  {
    IniFile->WriteInteger( "Form_85Old_Grafik", "GrafPoissonWidth", Form_85Old_GrafPoisson->Width );
    IniFile->WriteInteger( "Form_85Old_Grafik", "GrafPoissonHeight", Form_85Old_GrafPoisson->Height );
    delete IniFile;
  }
  catch(...)
  {
    delete IniFile;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_85Old_GrafPoisson::CheckLogClick(TObject *Sender)
{
 //Переключение кнопки ВЫБОРА МАСШТАБА

if(RadioButton2->Checked) //график счёта от времени
{

    if(!CheckLog->Checked)
       {//линейный масштаб
        Chart2->Visible=false;
        Chart1->Visible=true;
        Form_85Old_GrafPoisson->Chart1->Title->Text->Clear();
        Form_85Old_GrafPoisson->Chart1->Title->Text->Add("График счёта от времени");
        Series1->Clear(); Series2->Clear();  Series6->Clear();
        Form_85Old_GrafPoisson->Chart1->BottomAxis->Minimum=0;
        Form_85Old_GrafPoisson->Chart1->BottomAxis->Maximum=KolIsp;
        Form_85Old_GrafPoisson->Chart1->LeftAxis->Minimum=0;
        unsigned int MaxZn3=0; for(int i=0;i<KolIsp;i++)
                         {if(Form_85Old_Poisson->data[i]>MaxZn3)MaxZn3=Form_85Old_Poisson->data[i];}

        Form_85Old_GrafPoisson->Chart1->LeftAxis->Maximum=MaxZn3+10;
        for(int i=0;i<KolIsp;i++)Form_85Old_GrafPoisson->Series1->AddXY(i,Form_85Old_Poisson->data[i],clBlack);
        }
    else
        { //Логарифмический масштаб
         Chart2->Visible=true;
         Series3->Clear(); Series4->Clear();Series5->Clear();
           Form_85Old_GrafPoisson->Chart2->Title->Text->Clear();
           Form_85Old_GrafPoisson->Chart2->Title->Text->Add("График счёта от времени");
          Form_85Old_GrafPoisson->Chart2->BottomAxis->Minimum=0;
          Form_85Old_GrafPoisson->Chart2->BottomAxis->Maximum=KolIsp;
          Form_85Old_GrafPoisson->Chart2->LeftAxis->Minimum=0;
          unsigned int MaxZn3=0; for(int i=0;i<KolIsp;i++)
                         {if(Form_85Old_Poisson->data[i]>MaxZn3)MaxZn3=Form_85Old_Poisson->data[i];}
            if(MaxZn3<=100000)Form_85Old_GrafPoisson->Chart2->LeftAxis->Maximum=100000;
            if(MaxZn3<=10000)Form_85Old_GrafPoisson->Chart2->LeftAxis->Maximum=10000;
            if(MaxZn3<=1000)Form_85Old_GrafPoisson->Chart2->LeftAxis->Maximum=1000;
            if(MaxZn3<=100)Form_85Old_GrafPoisson->Chart2->LeftAxis->Maximum=100;
            if(MaxZn3<=10)Form_85Old_GrafPoisson->Chart2->LeftAxis->Maximum=10;
            
         for(int i=0;i<KolIsp;i++)Form_85Old_GrafPoisson->Series5->AddXY(i,Form_85Old_Poisson->data[i],clBlack);
        }

}
else  //Пуассон
{
      if(CheckLog->Checked)
        { //Логарифмический масштаб
           Chart2->Visible=true;
              Form_85Old_GrafPoisson->Chart2->Title->Text->Clear();
              Form_85Old_GrafPoisson->Chart2->Title->Text->Add("Распределение по Пуассону");
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

          Series3->Clear();
          Series4->Clear();
          Series5->Clear();
          for(int i=0;i<MaxPoisson;i++)Form_85Old_GrafPoisson->Series3->AddXY(i,y[i],clRed);//распределение Пуассона
          for(int i=0;i<MaxPoisson;i++)Form_85Old_GrafPoisson->Series5->AddXY(i,yy[i],clGreen);
          for(int i=0;i<=MaxZn2;i++)Form_85Old_GrafPoisson->Series4->AddXY(i,Spec[i],clBlack); //построим гистограмму
        }
       else
       { //Линейный масштаб
        Chart2->Visible=false;
        Chart1->Visible=true;
        Series1->Clear(); Series2->Clear(); Series6->Clear();
         Form_85Old_GrafPoisson->Chart1->Title->Text->Clear();
         Form_85Old_GrafPoisson->Chart1->Title->Text->Add("Распределение по Пуассону");
         //Линейный масштаб
          Form_85Old_GrafPoisson->Chart1->BottomAxis->Minimum=0;
          Form_85Old_GrafPoisson->Chart1->BottomAxis->Maximum=MaxZn2+pow(10,por2);
          Form_85Old_GrafPoisson->Chart1->BottomAxis->Minimum=MinZn2;
          
          Form_85Old_GrafPoisson->Chart1->LeftAxis->Minimum=0;
          Form_85Old_GrafPoisson->Chart1->LeftAxis->Maximum=MaxZn+pow(10,por);
        for(int i=0;i<MaxPoisson;i++)Form_85Old_GrafPoisson->Series1->AddXY(i,y[i],clRed);//распределение Пуассона
        for(int i=0;i<MaxPoisson;i++)Form_85Old_GrafPoisson->Series6->AddXY(i,yy[i],clGreen);
        for(int i=0;i<=MaxZn2;i++)Form_85Old_GrafPoisson->Series2->AddXY(i,Spec[i],clBlack); //построим гистограмму
       }

}

}
//---------------------------------------------------------------------------

void __fastcall TForm_85Old_GrafPoisson::RadioButton1Click(TObject *Sender)
{

//Пуассон
if(CheckLog->Checked)
{ //Логарифмический масштаб
Chart2->Visible=true;
Series3->Clear(); Series4->Clear();Series5->Clear();
Form_85Old_GrafPoisson->Chart2->Title->Text->Clear();
Form_85Old_GrafPoisson->Chart2->Title->Text->Add("Распределение по Пуассону");
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

for(int i=0;i<MaxPoisson;i++)Form_85Old_GrafPoisson->Series3->AddXY(i,y[i],clRed);//распределение Пуассона
for(int i=0;i<MaxPoisson;i++)Form_85Old_GrafPoisson->Series5->AddXY(i,yy[i],clGreen);
for(int i=0;i<=MaxZn2;i++)Form_85Old_GrafPoisson->Series4->AddXY(i,Spec[i],clBlack); //построим гистограмму
}
else
{ //Линейный масштаб
Chart2->Visible=false;
Chart1->Visible=true;
Series1->Clear(); Series2->Clear();Series6->Clear();
Form_85Old_GrafPoisson->Chart1->Title->Text->Clear();
Form_85Old_GrafPoisson->Chart1->Title->Text->Add("Распределение по Пуассону");
 //Линейный масштаб
Form_85Old_GrafPoisson->Chart1->BottomAxis->Minimum=0;
Form_85Old_GrafPoisson->Chart1->BottomAxis->Maximum=MaxZn2+pow(10,por2);
Form_85Old_GrafPoisson->Chart1->BottomAxis->Minimum=MinZn2;

Form_85Old_GrafPoisson->Chart1->LeftAxis->Minimum=0;
Form_85Old_GrafPoisson->Chart1->LeftAxis->Maximum=MaxZn+pow(10,por);
for(int i=0;i<MaxPoisson;i++)Form_85Old_GrafPoisson->Series1->AddXY(i,y[i],clRed);//распределение Пуассона
for(int i=0;i<MaxPoisson;i++)Form_85Old_GrafPoisson->Series6->AddXY(i,yy[i],clGreen);
for(int i=0;i<=MaxZn2;i++)Form_85Old_GrafPoisson->Series2->AddXY(i,Spec[i],clBlack); //построим гистограмму
}



}
//---------------------------------------------------------------------------

void __fastcall TForm_85Old_GrafPoisson::RadioButton2Click(TObject *Sender)
{
//График во времени
if(!CheckLog->Checked)
{//линейный масштаб
Chart2->Visible=false;
Chart1->Visible=true;
Series1->Clear(); Series2->Clear(); Series6->Clear();
    Form_85Old_GrafPoisson->Chart1->Title->Text->Clear();
    Form_85Old_GrafPoisson->Chart1->Title->Text->Add("График счёта от времени");
Form_85Old_GrafPoisson->Chart1->BottomAxis->Minimum=0;
Form_85Old_GrafPoisson->Chart1->BottomAxis->Maximum=KolIsp;
Form_85Old_GrafPoisson->Chart1->LeftAxis->Minimum=0;
unsigned int MaxZn3=0; for(int i=0;i<KolIsp;i++)
                         {if(Form_85Old_Poisson->data[i]>MaxZn3)MaxZn3 = Form_85Old_Poisson->data[i];}
Form_85Old_GrafPoisson->Chart1->LeftAxis->Maximum=MaxZn3+10;
for(int i=0;i<KolIsp;i++)Form_85Old_GrafPoisson->Series1->AddXY(i,Form_85Old_Poisson->data[i],clBlack);
}
else
{ //Логарифмический масштаб
Chart2->Visible=true;
Series3->Clear(); Series4->Clear();Series5->Clear();
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
//---------------------------------------------------------------------------

