//---------------------------------------------------------------------------

#ifndef GrafikH
#define GrafikH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
//---------------------------------------------------------------------------
class TForm_85Old_GrafPoisson : public TForm
{
__published:	// IDE-managed Components
        TChart *Chart1;
        TLineSeries *Series1;
        TBarSeries *Series2;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TCheckBox *CheckLog;
        TChart *Chart2;
        TLineSeries *Series3;
        TBarSeries *Series4;
        TPanel *Panel3;
        TPanel *Panel1;
        TPanel *Panel2;
        TPanel *Panel4;
        TPanel *Panel5;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TLineSeries *Series5;
        TLabel *Label5;
        TLabel *Label6;
        TLineSeries *Series6;
        void __fastcall CloseGraf(TObject *Sender, TCloseAction &Action);
        void __fastcall CheckLogClick(TObject *Sender);
        void __fastcall RadioButton1Click(TObject *Sender);
        void __fastcall RadioButton2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm_85Old_GrafPoisson(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_85Old_GrafPoisson *Form_85Old_GrafPoisson;
//---------------------------------------------------------------------------
#endif
