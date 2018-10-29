//---------------------------------------------------------------------------

#ifndef ProvPoissonH
#define ProvPoissonH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "fstream.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#define NMAS 20000
//---------------------------------------------------------------------------
class TForm_85Old_Poisson : public TForm
{
__published:	// IDE-managed Components
        TStatusBar *StatusBar1;
        TGroupBox *GroupBox1;
        TEdit *Edit1;
        TButton *Button1;
        TButton *Button2;
        TLabel *Label54;
        TGroupBox *GroupBox3;
        TEdit *Edit17;
        TButton *Button3;
        TEdit *Edit0;
        TLabel *Label34;
        TPanel *Panel1;
        TPanel *Panel2;
        TPanel *Panel3;
        TPanel *Panel4;
        TButton *Button11;
        TLabel *Label36;
        TEdit *Edit33;
        TGroupBox *GroupBox4;
        TEdit *Edit25;
        TGroupBox *GroupBox2;
        TEdit *Edit9;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall ShowPoisson(TObject *Sender);
        void __fastcall Button11Click(TObject *Sender);
        void __fastcall ClosePoisson(TObject *Sender,
          TCloseAction &Action);
        void __fastcall FormHide(TObject *Sender);
private:	// User declarations
          bool KodVxod;
          float Sum,Disp,Krit;
          bool Port;
          DWORD err;
          long  time1;
          char SSP;
          int Kisp;
//          fstream fil,fil2;
          bool KodGrafika;
          void Zapis();
          double poisson(int i,float Srednee);//распределение Пуассона для i-точки
          double gausses(int x,float Srednee);//распределение Гаусса

           WORD RunningFlagCNT32;
           bool FlagStart;
           bool FlagWork;
public:		// User declarations
           int data[NMAS];//Счёт, полученный для данного БД
           int Nisp;
           void Graf(int nom);
           void GrafWork(int nom);
           void PostrGraf(void);
        __fastcall TForm_85Old_Poisson(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_85Old_Poisson *Form_85Old_Poisson;
//---------------------------------------------------------------------------
#endif
