//---------------------------------------------------------------------------

#ifndef Unit_Form_LoadParamH
#define Unit_Form_LoadParamH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include <list.h>
#include <stdio.h>
//---------------------------------------------------------------------------
struct Param
{
public:
  int m_nN;
  TDateTime m_dtDateTime;
  int m_nTCode;
  float m_fltTValue;
  int m_nPwmPulseLengthCode;
  int m_nPwmCycleTimeCode; // pwmCycleTimeCode, // U (Код) ----------- Вносить в строку "ПЕРИОД ШИМ минимальный"
  int m_nVValue;
  int m_nLedCode;
  AnsiString m_strComment;
  bool m_xChecked;

  Param(int nN,
      TDateTime dtDateTime,
      int nTCode,
      float fltTValue,
      int nPwmPulseLengthCode,
      int nPwmCycleTimeCode, // pwmCycleTimeCode, // U (Код) ----------- Вносить в строку "ПЕРИОД ШИМ минимальный"
      int nVValue,
      int nLedCode,
      AnsiString strComment,
      bool xChecked = true) :
  m_nN(nN),
  m_dtDateTime(dtDateTime),
  m_nTCode(nTCode),
  m_fltTValue(fltTValue),
  m_nPwmPulseLengthCode(nPwmPulseLengthCode),
  m_nPwmCycleTimeCode(nPwmCycleTimeCode),
  m_nVValue(nVValue),
  m_nLedCode(nLedCode),
  m_strComment(strComment),
  m_xChecked(xChecked)
  {
    ;
  }
  Param()
  {
    ;
  }
};
bool operator < (const Param& param1, const Param& param2)
{
  return param1.m_nTCode < param2.m_nTCode;
}
//---------------------------------------------------------------------------
class TForm_LoadParam : public TForm
{
__published:	// IDE-managed Components
        TEdit *Edit_LogFileName;
        TButton *Button_Browse;
        TButton *Button_Read;
        TListView *ListView_DetectionUnits2;
        TListView *ListView_DetectionUnits1;
        TButton *Button_Ok;
        TButton *Button_Cancel;
        TOpenDialog *OpenDialog;
        void __fastcall Button_BrowseClick(TObject *Sender);
        void __fastcall Button_ReadClick(TObject *Sender);
        void __fastcall ListView_DetectionUnits1Click(TObject *Sender);
        void __fastcall ListView_DetectionUnits2Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
  // Param list.
  std::list< std::list< Param > > * m_pParams;
  // Selected detection unit;
  int m_nN;
public:		// User declarations
  __fastcall TForm_LoadParam(TComponent* Owner);
  void GetParams(std::list<Param> & params);
  int ProcessLine(AnsiString strLine);
  // ДИА 04.09.2015 ===>>
  int DiaShim; //m_nPwmCycleTimeCode
  int DiaShim_Min;
  // ДИА 04.09.2015 <<===   
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_LoadParam *Form_LoadParam;
//---------------------------------------------------------------------------
#endif
