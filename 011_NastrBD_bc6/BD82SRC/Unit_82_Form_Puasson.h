//---------------------------------------------------------------------------

#ifndef Unit_Form_PuassonH
#define Unit_Form_PuassonH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "CSPIN.h"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include "RSProtokol.h"
//---------------------------------------------------------------------------
// 11.11.2014 - Добавил строку: #include "Unit_82_Form_Graph.h"
#include "Unit_82_Form_Graph.h"
//---------------------------------------------------------------------------
class TForm_Puasson : public TForm
{
__published:	// IDE-managed Components
        TScrollBox *ScrollBox1;
        TGroupBox *GroupBox_Znachenie;
        TEdit *Edit_Znachenie;
        TGroupBox *GroupBox_Srednee;
        TEdit *Edit_Srednee;
        TGroupBox *GroupBox_Dispersiya;
        TEdit *Edit_dispersiya;
        TGroupBox *GroupBox_Koeph;
        TEdit *Edit_koeph;
        TButton *Button_exit;
        TButton *Button_graph;
        TButton *Button_start;
        TButton *Button_stop;
        TLabel *Label_kolichestvo;
        TCSpinEdit *SpinEdit_kolichestvo;
        TEdit *Edit_fileName;
        TLabel *Label_fileName;
        TLabel *Label_kolichestvo_interval;
        TGroupBox *GroupBox_kontroliruem;
        TCSpinEdit *SpinEdit_nomer_elem;
        TLabel *Label_nomer_elem;
        TLabel *Label_znach_elem;
        TEdit *Edit_znach_elem;
        TLabel *Label_Chislo_Izmereniy;
        TStatusBar *StatusBar;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormHide(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Button_startClick(TObject *Sender);
        void __fastcall Button_exitClick(TObject *Sender);
        void __fastcall Button_graphClick(TObject *Sender);
        void __fastcall Button_stopClick(TObject *Sender);
private:	// User declarations
  double poisson(int x, float Srednee);
  double Gays(int x, float Disper, float Srednee);
  //int * DataArray; // динамический массив точек
  //double * y;
  //double * yy;
  unsigned int DataArray[300000];
  double y[300000];
  double yy[300000]; 
  unsigned int Spec[10000]; // массив для спектра
  double Spec_Gays[300000];
  int MaxPoisson; // позиция максимального значения

  unsigned int MaxZn; // Максимальное значение
  unsigned int MinZn; // Минимальное значение  
  unsigned int MaxZn2; // Максимальное значение 2
  unsigned int MinZn2; // Минимальное значение 2

  int count; // счётчик
  int Err_Svyaz; // ошибка звязи (найдено в логе "-1")  


  unsigned char PSW; // слово состояние
  unsigned int Shet;

  float Sum;
  float Disp;
  float Krit;

  bool KodVxod;  

public:		// User declarations
  void Graph(void); // Набор динамического массива целых чисел из файла
  void GraphWork(void); // График из буфера
    
  AnsiString str;
  AnsiString put; // Путь для сохранения логов
  AnsiString name;
  AnsiString filename;
  bool FlagWork;
  Set<char, 0, 255> Dig;

  int Kisp; // Количество испытаний (берём значение из окна ввода SpinEdit_kolichestvo)
  int Nisp; // Количество испытаний (берём значение подсчетом строк в файле, или буфере)
  void PostrGraf(); // Построение граффика
  void Zapis(); // Запись в файл    
  __fastcall TForm_Puasson(TComponent* Owner);

  RSProtokol_t * Prot;
  //TForm_Graph * Form_Graph;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Puasson *Form_Puasson;
//---------------------------------------------------------------------------
#endif
