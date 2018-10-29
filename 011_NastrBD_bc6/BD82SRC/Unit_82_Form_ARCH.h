//---------------------------------------------------------------------------

#ifndef Unit_Form_ARCHH
#define Unit_Form_ARCHH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <Chart.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Dialogs.hpp>
#include <Series.hpp>
//---------------------------------------------------------------------------
//#include "Unit_82_RSProtokol.h"
#include "RSProtokol.h"
//---------------------------------------------------------------------------
class TForm_ARCH : public TForm
{
__published:	// IDE-managed Components
        TOpenDialog *OpenDialog_forWrite;
        TOpenDialog *OpenDialog_forRead;
        TScrollBox *ScrollBox;
        TPanel *Panel_Main;
        TLabel *Label_Vnimanie1;
        TLabel *Label_Vnimanie2;
        TLabel *Label_Vnimanie3;
        TLabel *Label_Vnimanie4;
        TPanel *Panel_Dannyh;
        TLabel *Label_Dannye;
        TLabel *Label_str01;
        TLabel *Label_str02;
        TLabel *Label_str03;
        TLabel *Label_str04;
        TLabel *Label_str05;
        TLabel *Label_str06;
        TLabel *Label_str07;
        TLabel *Label_str08;
        TLabel *Label_str09;
        TLabel *Label_str10;
        TLabel *Label_str19;
        TLabel *Label_str18;
        TLabel *Label_str17;
        TLabel *Label_str16;
        TLabel *Label_str15;
        TLabel *Label_str14;
        TLabel *Label_str13;
        TLabel *Label_str12;
        TLabel *Label_str11;
        TLabel *Label_Nom;
        TLabel *Label_temperKam;
        TLabel *Label_kodTemper;
        TLabel *Label_kodSvd;
        TLabel *Labe_KolVoPoints_1;
        TLabel *Label_KolVoPoints_2;
        TGroupBox *GroupBox_Interp_Approks;
        TLabel *Label_Interp;
        TLabel *Label_Approks;
        TLabel *Label_tangens_01;
        TLabel *Label_tangens_02;
        TButton *Button_ProsmGrafika;
        TButton *Button_ParamIzFayla;
        TRadioButton *RadioButton_Interpol_01;
        TRadioButton *RadioButton_Interpol_02;
        TRadioButton *RadioButton_Interpol_03;
        TRadioButton *RadioButton_Interpol_04;
        TRadioButton *RadioButton_Interpol_05;
        TEdit *Edit_tangens;
        TUpDown *UpDown_tangens;
        TRadioButton *RadioButton_Approks_01;
        TRadioButton *RadioButton_Approks_02;
        TRadioButton *RadioButton_Approks_03;
        TRadioButton *RadioButton_Approks_04;
        TPanel *Panel_forTable;
        //
        TEdit *Edit_temperKam_01;
        TEdit *Edit_temperKam_02;
        TEdit *Edit_temperKam_03;
        TEdit *Edit_temperKam_04;
        TEdit *Edit_temperKam_05;
        TEdit *Edit_temperKam_06;
        TEdit *Edit_temperKam_07;
        TEdit *Edit_temperKam_08;
        TEdit *Edit_temperKam_09;
        TEdit *Edit_temperKam_10;
        TEdit *Edit_temperKam_11;
        TEdit *Edit_temperKam_12;
        TEdit *Edit_temperKam_13;
        TEdit *Edit_temperKam_14;
        TEdit *Edit_temperKam_15;
        TEdit *Edit_temperKam_16;
        TEdit *Edit_temperKam_17;
        TEdit *Edit_temperKam_18;
        TEdit *Edit_temperKam_19;
        //
        TEdit *Edit_kodTemper_01;
        TEdit *Edit_kodTemper_02;
        TEdit *Edit_kodTemper_03;
        TEdit *Edit_kodTemper_04;
        TEdit *Edit_kodTemper_05;
        TEdit *Edit_kodTemper_06;
        TEdit *Edit_kodTemper_07;
        TEdit *Edit_kodTemper_08;
        TEdit *Edit_kodTemper_09;
        TEdit *Edit_kodTemper_10;
        TEdit *Edit_kodTemper_11;
        TEdit *Edit_kodTemper_12;
        TEdit *Edit_kodTemper_13;
        TEdit *Edit_kodTemper_14;
        TEdit *Edit_kodTemper_15;
        TEdit *Edit_kodTemper_16;
        TEdit *Edit_kodTemper_17;
        TEdit *Edit_kodTemper_18;
        TEdit *Edit_kodTemper_19;
        //
        TEdit *Edit_kodSvd_01;
        TEdit *Edit_kodSvd_02;
        TEdit *Edit_kodSvd_03;
        TEdit *Edit_kodSvd_04;
        TEdit *Edit_kodSvd_05;
        TEdit *Edit_kodSvd_06;
        TEdit *Edit_kodSvd_07;
        TEdit *Edit_kodSvd_08;
        TEdit *Edit_kodSvd_09;
        TEdit *Edit_kodSvd_10;
        TEdit *Edit_kodSvd_11;
        TEdit *Edit_kodSvd_12;
        TEdit *Edit_kodSvd_13;
        TEdit *Edit_kodSvd_14;
        TEdit *Edit_kodSvd_15;
        TEdit *Edit_kodSvd_16;
        TEdit *Edit_kodSvd_17;
        TEdit *Edit_kodSvd_18;
        TEdit *Edit_kodSvd_19;
        //
        TEdit *Edit_KolVoPoints;
        TUpDown *UpDown_KolVoPoints;
        TGroupBox *GroupBox_Graphiks;
        TRadioButton *RadioButton_Grafik1;
        TRadioButton *RadioButton_Grafik2;
        TPanel *Panel_ReadWrireEEPROM;
        TSpeedButton *SpeedButton_WriteFileStr;
        TLabel *Label_FileForWrite;
        TGroupBox *GroupBox_WriteToEEPROM;
        TButton *Button_WriteToEEPROM;
        TGroupBox *GroupBox_ReadFromEEPROM;
        TButton *Button_ReadFromEEPROM;
        TButton *Button_WriteFileStr;
        TPanel *Panel_ReadFromFile;
        TSpeedButton *SpeedButton_ReadFileStr;
        TLabel *Label_FileForRead;
        TGroupBox *GroupBox_ReadFromFile;
        TButton *Button_ReadFromFile;

        TEdit *Edit_WriteFileStr;
        TEdit *Edit_ReadFileStr;

        TButton *Button_ReadFileStr;
        TChart *Chart_Main;
        TLineSeries *Series1;
        TPointSeries *Series2;
        TLineSeries *Series3;
        TLineSeries *Series4;
        void __fastcall FormHide(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall UpDown_KolVoPointsClick(TObject *Sender,
          TUDBtnType Button);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Button_WriteFileStrClick(TObject *Sender);
        void __fastcall Button_ReadFileStrClick(TObject *Sender);
        void __fastcall Button_ProsmGrafikaClick(TObject *Sender);
        void __fastcall RadioButton_Grafik2Click(TObject *Sender);
        void __fastcall RadioButton_Grafik1Click(TObject *Sender);
        void __fastcall RadioButton_Interpol_02Click(TObject *Sender);
        void __fastcall RadioButton_Interpol_03Click(TObject *Sender);
        void __fastcall RadioButton_Interpol_04Click(TObject *Sender);
        void __fastcall RadioButton_Interpol_05Click(TObject *Sender);
        void __fastcall RadioButton_Approks_01Click(TObject *Sender);
        void __fastcall RadioButton_Approks_02Click(TObject *Sender);
        void __fastcall RadioButton_Approks_03Click(TObject *Sender);
        void __fastcall RadioButton_Approks_04Click(TObject *Sender);
        void __fastcall UpDown_tangensClick(TObject *Sender,
          TUDBtnType Button);
        void __fastcall RadioButton_Interpol_01Click(TObject *Sender);
        void __fastcall Button_ReadFromFileClick(TObject *Sender);
        void __fastcall Button_ReadFromEEPROMClick(TObject *Sender);
        void __fastcall Button_WriteToEEPROMClick(TObject *Sender);
        void __fastcall Button_ParamIzFaylaClick(TObject *Sender);
private:	// User declarations
  void __fastcall VisEdit(void);
  bool FlagVxod;
  bool KodVxod;  
  AnsiString str;

  unsigned long Longk1;
  unsigned long LongA1;
  unsigned long Longk2;
  unsigned long LongA2;

  unsigned long IndAdrZ; // Индивидуальный адрес заданный
  unsigned long GrpAdrZ; // Групповой адрес заданный
  unsigned long DNUZ; // Значение дискриминатора нижнего уровня заданное
  unsigned long DVUZ; // Значение дискриминатора верхнего уровня заданное
  unsigned long LEDAmpZ; // Амплитуда импульса от светодиода
  unsigned long UhiZ; // Напряжение высокое заданное (Длительность ШИМ задан.)
  unsigned long SIMstart; // Период ШИМ нач.
  unsigned long SIMmax; // Период ШИМ max.
  unsigned long SSPP; // SSP
  unsigned int NSveto; // Заданный отклик светодиода
  int MasSveto[256];

  int ErrorCode;

  // для проверки  записи в EEPROM
  unsigned long IndAdrZPR;
  unsigned long GrpAdrZPR;
  unsigned long DNUZPR;
  unsigned long DVUZPR;
  unsigned long LEDAmpZPR;
  unsigned long UhiZPR;
  unsigned long SIMstartPR;
  unsigned long SIMmaxPR;
  unsigned long SSPPPR;
  unsigned int NSvetoPR;

  AnsiString m_strLogFileName; // Имя файла журнала.

public:		// User declarations
  __fastcall TForm_ARCH(TComponent* Owner); // конструктор
  void __fastcall IshDan(void);
  void __fastcall Interpol(void);
  void __fastcall Matr(int Nmatr); // решение системы линейных уравнений методом Гаусса
  void __fastcall Grafik(void);
  void __fastcall VyvEdit(void);
  void ZapisFile(AnsiString filename);
  void __fastcall ZapEEPROM(void);     

  int err;

  float Mas[72][72];
  float Xx[72];
  float B[72];
  float Koef[18][5];
  int Nmatr;

  float k1;
  float A1;
  float k2;
  float A2;  

  RSProtokol_t * Prot;

  bool FlagGrafik;
  bool FlagFile;
  bool FlagEEPROM;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_ARCH *Form_ARCH;
//---------------------------------------------------------------------------
#endif
