//---------------------------------------------------------------------------

#ifndef Unit_82_Form_SpectrH
#define Unit_82_Form_SpectrH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------
class TForm_82_Spectr_BD84 : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer_Obnovleniya_Spectra;
        TPanel *Panel_Bottom;
        TPanel *Panel_Top;
        TPanel *Panel_Left;
        TPanel *Panel_Right;
        TEdit *Edit_Znachenie_MAX;
        TLabel *Label_Znachenie_MAX;
        TEdit *Edit_Kanal_MAX;
        TLabel *Label_Kanal_MAX;
        TEdit *Edit_Integral;
        TLabel *Label_Integral;
        TEdit *Edit_Intensivnost;
        TLabel *Label_Intensivnost;
        TEdit *Edit_TimeSumm;
        TPanel *Panel_Graph;
        TPaintBox *PaintBox_Graph;
        TImage *Image_Graph;
        TLabel *Label_TimeNaborSpektra;
        TButton *Button_Spectr;
        TButton *Button_ClearSpektr;
        TButton *Button_Mashtab;
        TEdit *Edit_TimeNaborSpektra;
        TGroupBox *GroupBox_SpektrGraph;
        TRadioButton *RadioButton_Graph;
        TRadioButton *RadioButton_Gistogramma;
        TGroupBox *GroupBox_SpektrKanal;
        TRadioButton *RadioButton_Kanal;
        TRadioButton *RadioButton_Volt;
        TLabel *Label_TimeSumm;
        TEdit *Edit_TimeSys;
        TLabel *Label_TimeSys;
        TEdit *Edit_TimeReadySpektra;
        TLabel *Label_TimeReadySpektra;
        TPanel *Panel_TimeSpektr;
        TLabel *Label_TimeSpektr;
        TCSpinEdit *SpinEdit_TimeSpektr;
        TLabel *Label_TimeSpektrSek;
        TButton *Button_WriteTimeSpektr;
        TEdit *Edit_Xm1;
        TLabel *Label_Xm1;
        TEdit *Edit_Max_Xm1;
        TLabel *Label_Max_Xm1;
        void __fastcall Timer_Obnovleniya_SpectraTimer(TObject *Sender);
        void __fastcall Button_SpectrClick(TObject *Sender);
        void __fastcall Button_ClearSpektrClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Button_MashtabClick(TObject *Sender);
        void __fastcall Image_GraphMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall RadioButton_GraphClick(TObject *Sender);
        void __fastcall RadioButton_GistogrammaClick(TObject *Sender);
        void __fastcall RadioButton_KanalClick(TObject *Sender);
        void __fastcall RadioButton_VoltClick(TObject *Sender);
        void __fastcall Button_WriteKolTikSpectrClick(TObject *Sender);
        void __fastcall SpinEdit_TimeSpektrChange(TObject *Sender);
        void __fastcall Button_WriteTimeSpektrClick(TObject *Sender);
private:	// User declarations
  // ���������������� ��� ������
  typedef class Point_t__
  {
  public:
    // �����������
    Point_t__(int _x, int _y) : X(_x), Y(_y)
    {
    }
    int X;
    int Y;
  } Point_t;
  
  // ������ ������

  enum DIA_CONST { DVU = 1023, DNU = 5, MaxLength = 50 };

  int NomerMarkera; // 0 - ���, 1 - ������1, 2 - ������2


  Graphics::TBitmap * BitMapMain;
  Graphics::TBitmap * BitMapMarker1;
  Graphics::TBitmap * BitMapMarker2;
  Graphics::TBitmap * BitMapMarkerMax;
  Graphics::TBitmap * CreateDefaultBitMap(void);

  // ����� ����� �������
  int Npoints;
  // �������� (� ��������) ��� ������������� ��������
  // ���� "X" � "Y" ����� ������� ��������� (�� ���������
  // �� ������ �������� � ������� ����� ����)
  float O_x_pix;
  float O_y_pix;
  // �������� �� ���� "X" � "Y" ��� �������� �� ��������������
  // �������� � ��������
  float M_x;
  float M_y;

  float x_max;
  float x_min;

  float step_x;
  float x_max_abs;
  float y_max_abs;


  HPEN GreenPen_2;
  HPEN RedPen_1;
  HPEN BlackPen_4;

  HPEN OsiKoordPen; // ���� ��� ���� ���������
  HPEN SetkaKoorPen; // ���� ��� ������������ �����
  HPEN GraphPen; // ���� ��� �������
  HPEN MarkerPen; // ���� ��� �������

  //==\\int ArrSpectr[1024];
  int ArrSpectr[512];
  bool bfUpdateSpector;
  bool bf_Button_Spectr; // true - ��� ����� �������
  bool bf_Button_Mashtab_Nazata;

  int Rekursiya;
  int Rekursiya_max;
  Point_t * point_1;
  Point_t * point_2;
  char msg[MaxLength];
  int X_MarkerArr[3];
  int X_MarkerArr_ToX[3];

  float y_point_end;
  float y_point_end_pix;
  float y_point_begin;
  float y_point_begin_pix;

  float x_point_end;
  float x_point_end_pix;
  float x_point_begin;
  float x_point_begin_pix;

  int iZnachenieMax;
  int iKanalMax;
  int iIntegral;
  int TimeNaboraSpektra; // ����� ������ (������) �������
  int TimeGotovSpectr; // ����� ���������� �������
  float iIntensivnost;
  int SpZapCount; // ���������� ��� ����������, �� ������� ��� ������� ������
  int SpZapCountOld; // ���������� ��� ����������, �� ������� ��� ������� ������

  bool bf_RadioButton_Graph;
  bool bf_RadioButton_Kanal;
  int iTime_0;
  int iTime_1;
  int iTimeSys; // ����� ���������

  // ������� ������
  void DrawBitMap( Graphics::TBitmap * BMP );
  void InitParam(void);
  float Math_Abs(float fVar);
  float Function_of_graph(float fVar);
  void DrawLine
  (
    Graphics::TBitmap * BitmapVar,
    Point_t * Pt1,
    Point_t * Pt2
  );
  void DrawString
  (
    Graphics::TBitmap * BitmapVar,
    char * chArrSimvols,
    Point_t * Pt
  );
  void DrawClear
  (
    Graphics::TBitmap * BitmapVar
  );
  void DrawPlus
  (
    Graphics::TBitmap * BitmapVar, // ������ ������������� BitmapConst
    Graphics::TBitmap * BitmapConst // �� ����������
  );
  void DrawVertLine(Graphics::TBitmap * BitmapVar);
  float f_Diapazon(float MinVal, float MaxVal, float NormVal, float ErrorVal);
  int i_Diapazon(int MinVal, int MaxVal, int NormVal, int ErrorVal);
  float Convert_Y_ToPix(float Y);
  float Convert_X_ToPix(float X);
  int Convert_Pix_ToX(float x_pix);
  bool bfFirctVhod; // false - ������ ����� � ������.
public:		// User declarations
  // �����������
  __fastcall TForm_82_Spectr_BD84(TComponent* Owner);
  // ����������
  __fastcall ~TForm_82_Spectr_BD84();
  // ���������� ������� �������������� �� -1 �� 1 �� ���� "X" � "Y"
  void PostroenieGraph(void);
  // ���������� ������� �������������� �� 0 �� 1 �� ���� "X" � "Y"
  void PostroenieGraphNormir(void);
  // ���������� ����� ������������ �������
  void ProrisovkaGraph(void);
  // �������� ������ �������
  
  // ������� ����������� ������
  void SetSpectr(int * SpArr);
  // ��������� ���������� ������ � ������������
  void SetSpectrSNakopleniem(unsigned char * SpArr_Data);
  // ����� ��������� �������
  int ArrSum(int iStart, int iBegin, int * iArr);
  bool GetStartStopSpectr( void ) // true - ��� ����� �������
  {
    return this->bf_Button_Spectr;
  }
  void SetStartStopSpectr( bool bf ) // true - ��� ����� �������
  {
    this->bf_Button_Spectr = bf;
  }
};
//---------------------------------------------------------------------------
//const int MaxLength = 50;
extern PACKAGE TForm_82_Spectr_BD84 *Form_82_Spectr_BD84;
//---------------------------------------------------------------------------
#endif


/*
void TMyWindow::Paint(TDC& PaintDC, bool erase, TRect& rect)

{
  HPEN PenHandle, OldPenHandle;
  HBRUSH BrushHandle, OldBrushHandle;
  PenHandle = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
  OldPenHandle = SelectObject(PaintDC, PenHandle);
  BrushHandle = CreateSolidBrush(RGB(255, 255, 0));
  OldBrushHandle = SelectObject(PaintDC, BrushHandle);
  Ellipse(10, 20, 50, 50);
  SelectObject(OldBrushHandle);
  DeleteObject(BrushHandle);
  SelectObject(OldPenHandle);
  DeleteObject(PenHandle);
)

This C++Builder code accomplishes the same thing:

void __fastcall TForm1::FormPaint(TObject *Sender)

{
  Canvas->Pen->Color = clBlue;
  Canvas->Brush->Color = clYellow;
  Canvas->Ellipse(10, 20, 50, 50);
}
*/

