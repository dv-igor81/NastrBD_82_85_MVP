//---------------------------------------------------------------------------
#include <vcl.h>
//---------------------------------------------------------------------------
#include <stdio.h>
#pragma hdrstop

#include "Unit_82_Form_Spectr.h"
#include "Unit_DIA_Global_Funk.h"
#include "Unit_82_Form_Start.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm_82_Spectr_BD84 *Form_82_Spectr_BD84;
//---------------------------------------------------------------------------
__fastcall TForm_82_Spectr_BD84::TForm_82_Spectr_BD84(TComponent* Owner)
        : TForm(Owner)
{
  Button_Mashtab->Enabled = false;
  Edit_Znachenie_MAX->Text = "0";
  Edit_Kanal_MAX->Text = "0";
  Edit_Integral->Text = "0";
  Edit_Intensivnost->Text = "0.00";
  Edit_TimeSumm->Text = "0.000";
  Edit_TimeNaborSpektra->Text = "0";
  Edit_TimeReadySpektra->Text = "0";

    
  this->bf_Button_Mashtab_Nazata = false; // Кнопка в состоянии 1
  this->bf_RadioButton_Graph = this->RadioButton_Graph->Checked;
  this->bf_RadioButton_Kanal = this->RadioButton_Kanal->Checked;
  this->bf_Button_Spectr = false; // true - идёт набор спектра
  this->x_min = 0;

  this->x_max = 512; //==\\
  this->NomerMarkera = 0; // 0 - нет, 1 - маркер1, 2 - маркер2
  this->iZnachenieMax = 0;
  this->iKanalMax = 0;
  this->iIntegral = 0;
  this->iIntensivnost = 0;
  this->SpZapCount = 0;
  this->SpZapCountOld = 0;
  //this->bf_ImageArray = 0;
  this->iTime_0 = 0;
  this->iTime_1 = 0;
  this->bfFirctVhod = false;
  //

  BitMapMain = CreateDefaultBitMap();
  BitMapMarker1 = CreateDefaultBitMap();
  BitMapMarker2 = CreateDefaultBitMap();

  // ===>> ===>> ===>> ===>> 12.10.2019 ===>> ===>> ===>> ===>>
  BitMapMarkerMax = CreateDefaultBitMap();
  // <<=== <<=== <<=== <<=== 12.10.2019 <<=== <<=== <<=== <<===

  GreenPen_2 = CreatePen( PS_SOLID, 2, clGreen );
  RedPen_1 = CreatePen( PS_SOLID, 1, clRed );
  BlackPen_4 = CreatePen( PS_SOLID, 1, clBlack );
  //
  OsiKoordPen = CreatePen( PS_SOLID, 2, clRed ); // Перо для осей координат
  SetkaKoorPen = CreatePen( PS_SOLID, 1, clGreen ); // Перо для координатной сетки
  GraphPen = CreatePen( PS_SOLID, 2, clBlack ); // Перо для графика
  MarkerPen = CreatePen( PS_SOLID, 2, clBlue ); // Перо для маркера
  //
  DrawClear(BitMapMain);
  DrawClear(BitMapMarker1);
  DrawClear(BitMapMarker2);
  //
  InitParam();

  SpinEdit_TimeSpektrChange( NULL );
}
//---------------------------------------------------------------------------
__fastcall TForm_82_Spectr_BD84::~TForm_82_Spectr_BD84()
{
  delete BitMapMain;
  delete BitMapMarker1;
  delete BitMapMarker2;
  delete BitMapMarkerMax;
}
//---------------------------------------------------------------------------
Graphics::TBitmap * TForm_82_Spectr_BD84::CreateDefaultBitMap(void)
{
  Graphics::TBitmap * DefaultBitMap = new Graphics::TBitmap();
  DefaultBitMap->Height = Panel_Graph->Height;
  DefaultBitMap->Width = Panel_Graph->Width;
  return DefaultBitMap;
}
//---------------------------------------------------------------------------
void TForm_82_Spectr_BD84::InitParam(void)
{
  // Величины (в пикселах) для параллельного переноса
  // осей "X" и "Y" новой системы координат (по сравнению
  // со старой системой в верхнем левом углу)
  this->O_x_pix = 50;
  this->O_y_pix = 50;
  // Масштабы по осям "X" и "Y" для перехода от действительных
  // значений к пикселам  
  this->M_x = 450 * 2;
  this->M_y = 300 * 2;

  // Число точек графика
  this->Npoints = this->x_max - this->x_min; // 512 точек

  this->bfUpdateSpector = false;
  this->x_max_abs = this->x_max;
  this->Rekursiya = 0;
  this->Rekursiya_max = 1;

}
//---------------------------------------------------------------------------
void TForm_82_Spectr_BD84::PostroenieGraphNormir(void)
{
  // Шаг по оси абсцисс "X" между точками графика
  step_x = (x_max - x_min) / Npoints;
  // Промежуточные локальные переменные
  float x_0;
  float y_0;
  float x_1;
  float y_1;

  // Расчёт минимального y_min и максимального y_max
  // действительных значений функции
  float y_min;
  float y_max;
  // Присваиваем y_min, y_max значение y_0
  // для нулевой точки (i=0)
  x_0 = x_min;
  y_0 = Function_of_graph(x_0);
  y_min = y_0;
  y_max = y_0;
  int i;
  // Органицуем цикл по всем точкам, начиная с i=1
  for(i = 1; i <= (Npoints-1); i++)
  {
    x_1 = x_min + i * step_x;
    y_1 = Function_of_graph(x_1);
    // Расчёт минимального и максимального значений функции
    if (y_min > y_1)
    {
      y_min = y_1;
    }
    if (y_max < y_1)
    {
      y_max = y_1;
    }
  }
  // Т.к. в последней точке i = Npoints
  // значение x_1 = x_min + Npoints * step_x
  // может отличаться от заданного значения x_max
  // (из-за накапливания погрешности в цикле), то проверим,
  // может быть y_min или y_max находится в последней
  // точке при точном задании нами значения x_max
  x_1 = x_max;
  y_1 = Function_of_graph(x_1);
  if (y_min > y_1)
  {
    y_min = y_1;
  }
  if (y_max < y_1)
  {
    y_max = y_1;
  }
  if (y_max < 5)
  {
    y_max = 5;  
  }
  this->y_max_abs = y_max;
  // Строим сетку координат:
  // Сначала строим ось абсцисс "X" от x = 0 до x = 1
  // Задаём абсциссу последней точки оси абсцисс "X"
  // при x = 1

  x_point_end = 1;
  x_point_begin = 0;
  x_point_end_pix = x_point_end * M_x + O_x_pix;
  x_point_begin_pix = x_point_begin * M_x + O_x_pix;

  // Выбираем перо для оси координат
  SelectObject( BitMapMain->Canvas->Handle, OsiKoordPen );
  // Задаём координаты двух граничных точек оси "X"
  point_1 = new Point_t(x_point_begin_pix, O_y_pix);
  point_2 = new Point_t(x_point_end_pix, O_y_pix);
  // Строим линию через две заданные граничные точки
  DrawLine(BitMapMain, point_1, point_2);
  // Строим горизонтальные линии сетки координат (кроме оси "X")
  // Ширина (размах) графика по оси ординат "Y"

  //==\\float span_y = y_max - y_min;

  // Число шагов по всей высоте сетки
  int N_step_grid_y = 20;
  // Шаг сетки в направлении оси "Y"
  // (высота всей сетки равна 2 единицам)
  float step_grid_y;
  float step_grid_y_pix;
  // Преобразование типов переменных
  step_grid_y = (x_point_end - x_point_begin) / N_step_grid_y;
  step_grid_y_pix = step_grid_y * M_y;

  // Выбираем перо для координатной сетки
  SelectObject( BitMapMain->Canvas->Handle, SetkaKoorPen );
  // Строим сетку от нулевой линии в одну сторону (вниз)
  int j_y;
  //==\\float y1;
  float y1_pix;
  //==\\for(j_y = 1; j_y <= (N_step_grid_y / 2); j_y++)
  for(j_y = 1; j_y <= (N_step_grid_y / 1); j_y++)
  {
    //==\\y1 = j_y * step_grid_y;
    y1_pix = j_y * step_grid_y_pix + O_y_pix;
    // Задаём координаты двух граничных точек линии сетки
    point_1 = new Point_t(x_point_begin_pix, y1_pix);
    point_2 = new Point_t(x_point_end_pix, y1_pix);
    // Строим линию через 2 заданные граничные точки
    DrawLine(BitMapMain, point_1, point_2);
  }
  // Строим сетку от нулевой линии в другую сторону (вверх)
  //for(j_y = 1; j_y <= (N_step_grid_y / 2); j_y++)
  //{
  //  //==\\y1 = j_y * step_grid_y;
  //  y1_pix = -j_y * step_grid_y_pix + O_y_pix;
  //  // Задаём координаты двух граничных точек линии сетки
  //  point1 = new Point_t(x_point_begin_pix, y1_pix);
  //  point2 = new Point_t(x_point_end_pix, y1_pix);
  //  // Строим линию через 2 заданные граничные точки
  //  DrawLine(BitMapMain, point1, point2);
  //}
  // Строим ось ординат "Y" от y = 0 до y = 1
  // Задаём ординату последней точки оси ординат "Y" при y = 0

  y_point_end = 1;
  y_point_begin = 0;

  y_point_end_pix = y_point_end * M_y + O_y_pix;
  y_point_begin_pix = y_point_begin * M_y + O_y_pix;

  // Выбираем перо для оси координат
  SelectObject( BitMapMain->Canvas->Handle, OsiKoordPen );

  // Задаём координаты двух граничных точек оси
  point_1 = new Point_t(O_x_pix, y_point_begin_pix);
  point_2 = new Point_t(O_x_pix, y_point_end_pix);
  // Строим линию через две заданные граничные точки  
  DrawLine(BitMapMain, point_1, point_2);

  // Строим вертикальные линии сетки координат (кроме оси "Y")
  // Ширина (размах) графика по оси абсцисс "X"

  //==\\float span_x = x_max - x_min;

  // Число шагов по всей ширине сетки по обе стороны от оси "Y"
  int N_step_grid_x = 20;
  // Шаг сетки в направлении оси "X"
  // (Ширина всей сетки равна 2 единицам)
  float step_grid_x;
  float step_grid_x_pix;
  // Преобразование типов переменных
  step_grid_x = (float) (y_point_end - y_point_begin) / N_step_grid_x;
  step_grid_x_pix = step_grid_x * M_x;

  // Выбираем перо для координатной сетки
  SelectObject( BitMapMain->Canvas->Handle, SetkaKoorPen );
  // Строим сетку от нулевой линии в одну сторону (вправо)
  int j_x;
  //==\\float x1;
  float x1_pix;
  //for(j_x = 1; j_x <= (N_step_grid_x / 2); j_x++)
  for(j_x = 1; j_x <= (N_step_grid_x / 1); j_x++)
  {
    //==\\x1 = j_x * step_grid_x;
    x1_pix = j_x * step_grid_x_pix + O_x_pix;
    // Задаём координаты двух граничных точек линии сетки
    point_1 = new Point_t(x1_pix, y_point_begin_pix);
    point_2 = new Point_t(x1_pix, y_point_end_pix);
    // Строим линию через 2 заданные граничные точки
    DrawLine(BitMapMain, point_1, point_2);
  }

  // Записываем числа по осям координат
  // Объявляем локальные переменные
  int n;
  float p1;
  float p2;

  // Записываем числа по оси "O", "+Y"
  p1 = 0;
  //for (n = 1; n <= 10; n++)
  for (n = 0; n <= 20; n++)
  {
    int len;
    y1_pix = (20 - n) * step_grid_y_pix + O_y_pix;
    p2 = p1 + n * 0.05f;
    p2 *= y_max;
    sprintf(msg, "%0.1f", p2);
    // Вставить 7 - len пробелов
    len = GetLengthStr(msg);
    for (i = 0; i < (6 - len); i++)
    {
      SimvolInsert(msg, 0, ' '); // Строка, индекс, символ
      SimvolInsert(msg, 0, ' '); // Строка, индекс, символ
    }
    point_1 = new Point_t(x_point_begin_pix - 40, y1_pix - 7);
    DrawString(BitMapMain, msg, point_1);
  }

  p1 = 0;
  for (n = 0; n <= 20; n++)
  {
    p2 = p1 + n * 0.05f;
    p2 *= (x_max - x_min);
    p2 += x_min;
    if ( bf_RadioButton_Kanal == false ) // Отображать по оси абсцисс значения в вольтах
    {
      p2 *= 4.5; // 4.5 - Максимальное значение в вольтах
      //==\\p2 /= 1024; // 1024 - Максимальное значение в каналах
      p2 /= 512; //==\\ 512 - Максимальное значение в каналах
      sprintf(msg, "%0.03f", p2);
    }
    if ( bf_RadioButton_Kanal == true ) // Отображать по оси абсцисс значения в каналах
    {
      sprintf(msg, "%0.0f", p2);
    }
    point_1 = new Point_t(O_x_pix - 10 + n * step_grid_x_pix, y_point_end_pix + 5);
    DrawString(BitMapMain, msg, point_1);
  }

  float x_0_pix;
  float y_0_pix;
  float x_1_pix;
  float y_1_pix;


  // Построение графига функции y = f(x)
  // Координаты нулевой (i = 0) точки, с которой строится график
  x_0 = x_min;
  x_0_pix = Convert_X_ToPix(x_0);
  // Рассчитываем "y" и вводим знак минус, чтобы положительное
  // значение "y" отложилось вверх по оси "Y" (а не вниз)
  y_0 = this->y_max_abs - Function_of_graph(x_0);
  y_0_pix = Convert_Y_ToPix(y_0);

  if ( bf_RadioButton_Graph == false )
  {
    // Строим отрезок линии графика y = f(x) между двумя известными точками
    point_1 = new Point_t(x_0_pix, y_0_pix);
    point_2 = new Point_t(x_0_pix, y_point_end_pix);
    DrawLine(BitMapMain, point_1, point_2);
  } // END: if ( bf_RadioButton_Graph == false )  

  // Выбираем перо, для рисования графика GraphPen
  SelectObject( BitMapMain->Canvas->Handle, GraphPen );
  // Организовываем цикл по всем точкам, начиная с i = 1
  for(i = 1; i <= Npoints; i++)
  {
    // Рассчитываем абсциссу "x" для данной i-й точки
    x_1 = x_min + i * step_x;
    // Рассчитываем ординату "y" этой i-й точки и вводим знак минус,
    // чтобы положительные значения "y" откладывались вверх (а не вниз),
    // и чтобы строить график традиционно снизу-вверх по оси "Y"
    y_1 = this->y_max_abs - Function_of_graph(x_1);
    // Переходим к относительным величинам и пикселам
    x_1_pix = Convert_X_ToPix(x_1);
    y_1_pix = Convert_Y_ToPix(y_1);
    // Строим отрезок линии графика y = f(x) между двумя известными точками
    if ( bf_RadioButton_Graph == true )
    {
      point_1 = new Point_t(x_0_pix, y_0_pix);
      point_2 = new Point_t(x_1_pix, y_1_pix);
    } // END: if ( bf_RadioButton_Graph == true )
    if ( bf_RadioButton_Graph == false )
    {
      // Строим отрезок линии графика y = f(x) между двумя известными точками
      point_1 = new Point_t(x_1_pix, y_1_pix);
      point_2 = new Point_t(x_1_pix, y_point_end_pix);
    } // END: if ( bf_RadioButton_Graph == false )
    DrawLine(BitMapMain, point_1, point_2);
    // Присваиваем предидущей (i-1)-й точке координаты данной точки
    x_0_pix = x_1_pix;
    y_0_pix = y_1_pix;
    // Задаём следующую (i+1)-ю точку
  }
}
//---------------------------------------------------------------------------
void TForm_82_Spectr_BD84::PostroenieGraph(void)
{
  // Шаг по оси абсцисс "X" между точками графика
  step_x = (x_max - x_min) / Npoints;
  // Наибольшее абсолютное значение x_max_abs из двух концив
  // заданного нами числового интервала x_min и x_max
  x_max_abs = Math_Abs(x_max);
  if (x_max_abs < Math_Abs(x_min))
  {
    x_max_abs = Math_Abs(x_min);
  }
  // Промежуточные локальные переменные
  float x_0;
  float y_0;
  float x_1;
  float y_1;
  float x_0_pix;
  float y_0_pix;
  float x_1_pix;
  float y_1_pix;

  // Расчёт минимального y_min и максимального y_max
  // действительных значений функции
  float y_min;
  float y_max;
  // Присваиваем y_min, y_max значение y_0
  // для нулевой точки (i=0)
  x_0 = x_min;
  y_0 = Function_of_graph(x_0);
  y_min = y_0;
  y_max = y_0;
  int i;
  // Органицуем цикл по всем точкам, начиная с i=1
  for(i = 1; i <= (Npoints-1); i++)
  {
    x_1 = x_min + i * step_x;
    y_1 = Function_of_graph(x_1);
    // Расчёт минимального и максимального значений функции
    if (y_min > y_1)
    {
      y_min = y_1;
    }
    if (y_max < y_1)
    {
      y_max = y_1;
    }
  }
  // Т.к. в последней точке i = Npoints
  // значение x_1 = x_min + Npoints * step_x
  // может отличаться от заданного значения x_max
  // (из-за накапливания погрешности в цикле), то проверим,
  // может быть y_min или y_max находится в последней
  // точке при точном задании нами значения x_max
  x_1 = x_max;
  y_1 = Function_of_graph(x_1);
  if (y_min > y_1)
  {
    y_min = y_1;
  }
  if (y_max < y_1)
  {
    y_max = y_1;
  }
  // Наибольшее абсолютное значение функции y_max_abs
  // из двух значений y_min и y_max
  y_max_abs = Math_Abs(y_max);
  if (y_max_abs < Math_Abs(y_min))
  {
    y_max_abs = Math_Abs(y_min);
  }
  // Строим сетку координат:
  // Сначала строим ось абсцисс "X" от x = -1 до x = 1
  // Задаём абсциссу последней точки оси абсцисс "X"
  // при x = 1
  float x_point_end;
  float x_point_end_pix;
  float x_point_begin;
  float x_point_begin_pix;
  x_point_end = 1;
  x_point_begin = - 1;

  x_point_end_pix = x_point_end * M_x + O_x_pix;
  x_point_begin_pix = x_point_begin * M_x + O_x_pix;
  // Выбираем зелёное перо толщиной 2
  SelectObject( BitMapMain->Canvas->Handle, GreenPen_2 );
  // Задаём координаты двух граничных точек оси "X"
  Point_t * point1 = new Point_t(-1 * M_x + O_x_pix, O_y_pix);
  Point_t * point2 = new Point_t(x_point_end_pix, O_y_pix);
  // Строим линию через две заданные граничные точки
  DrawLine(BitMapMain, point1, point2);
  // Строим горизонтальные линии сетки координат (кроме оси "X")
  // Ширина (размах) графика по оси ординат "Y"
  //==\\float span_y = y_max - y_min;
  // Число шагов по всей высоте сетки
  int N_step_grid_y = 20;
  // Шаг сетки в направлении оси "Y"
  // (высота всей сетки равна 2 единицам)
  float step_grid_y;
  float step_grid_y_pix;
  // Преобразование типов переменных
  step_grid_y = (float) 2 / N_step_grid_y;
  step_grid_y_pix = step_grid_y * M_y;
  // Выбираем красное перо толщиной 1
  SelectObject( BitMapMain->Canvas->Handle, RedPen_1 );
  // Строим сетку от нулевой линии в одну сторону (вниз)
  int j_y;
  //==\\float y1;
  float y1_pix;
  for(j_y = 1; j_y <= (N_step_grid_y / 2); j_y++)
  {
    //==\\y1 = j_y * step_grid_y;
    y1_pix = j_y * step_grid_y_pix + O_y_pix;
    // Задаём координаты двух граничных точек линии сетки
    Point_t * point3 = new Point_t(-1 * M_x + O_x_pix, y1_pix);
    Point_t * point4 = new Point_t(x_point_end_pix, y1_pix);
    // Строим линию через 2 заданные граничные точки
    DrawLine(BitMapMain, point3, point4);
  }
  // Строим сетку от нулевой линии в другую сторону (вверх)
  for(j_y = 1; j_y <= (N_step_grid_y / 2); j_y++)
  {
    //==\\y1 = j_y * step_grid_y;
    y1_pix = -j_y * step_grid_y_pix + O_y_pix;
    // Задаём координаты двух граничных точек линии сетки
    Point_t * point5 = new Point_t(-1 * M_x + O_x_pix, y1_pix);
    Point_t * point6 = new Point_t(x_point_end_pix, y1_pix);
    // Строим линию через 2 заданные граничные точки
    DrawLine(BitMapMain, point5, point6);
  }
  // Строим ось ординат "Y" от y = -1 до y = 1
  // Задаём ординату последней точки оси ординат "Y" при y = 0
  float y_point_end;
  float y_point_end_pix;
  float y_point_begin;
  //==\\float y_point_begin_pix;
  y_point_end = 1;
  y_point_end_pix = y_point_end * M_y + O_y_pix;
  y_point_begin = -1;
  y_point_begin_pix = y_point_begin * M_y + O_y_pix;
  // Выбираем зелёное перо толщиной 2
  SelectObject( BitMapMain->Canvas->Handle, GreenPen_2 );
  // Задаём координаты двух граничных точек оси
  Point_t * point7 = new Point_t(O_x_pix, -1 * M_y + O_y_pix);
  Point_t * point8 = new Point_t(O_x_pix, y_point_end_pix);
  // Строим линию через две заданные граничные точки  
  DrawLine(BitMapMain, point7, point8);
  // Строим вертикальные линии сетки координат (кроме оси "Y")
  // Ширина (размах) графика по оси абсцисс "X"
  //==\\float span_x = x_max - x_min;
  // Число шагов по всей ширине сетки по обе стороны от оси "Y"
  int N_step_grid_x = 20;
  // Шаг сетки в направлении оси "X"
  // (Ширина всей сетки равна 2 единицам)
  float step_grid_x;
  float step_grid_x_pix;
  // Преобразование типов переменных
  step_grid_x = (float) 2 / N_step_grid_x;
  step_grid_x_pix = step_grid_x * M_x;
  // Выбираем красное перо толщиной 1
  SelectObject( BitMapMain->Canvas->Handle, RedPen_1 );
  // Строим сетку от нулевой линии в одну сторону (вправо)
  int j_x;
  //==\\float x1;
  float x1_pix;
  for(j_x = 1; j_x <= (N_step_grid_x / 2); j_x++)
  {
    //==\\x1 = j_x * step_grid_x;
    x1_pix = j_x * step_grid_x_pix + O_x_pix;
    // Задаём координаты двух граничных точек линии сетки
    Point_t * point9 = new Point_t(x1_pix, -1 * M_y + O_y_pix);
    Point_t * point10 = new Point_t(x1_pix, y_point_end_pix);
    // Строим линию через 2 заданные граничные точки
    DrawLine(BitMapMain, point9, point10);
  }
  // Строим сетку от нулевой линии в другую сторону (влево)
  for(j_x = 1; j_x <= (N_step_grid_x / 2); j_x++)
  {
    //==\\x1 = j_x * step_grid_x;
    x1_pix = -j_x * step_grid_x_pix + O_x_pix;
    // Задаём координаты двух граничных точек линии сетки
    Point_t * point11 = new Point_t(x1_pix, -1 * M_y + O_y_pix);
    Point_t * point12 = new Point_t(x1_pix, y_point_end_pix);
    // Строим линию через 2 заданные граничные точки
    DrawLine(BitMapMain, point11, point12);
  }

  // Записываем числа по осям координат
  // Объявляем локальные переменные
  int n;
  float p1;
  float p2;
  char msg[100];
  // Записываем числа по оси "O", "+Y"
  p1 = 0;
  for (n = 1; n <= 10; n++)
  {
    y1_pix = n * step_grid_y_pix + O_y_pix;
    p2 = p1 - n * 0.1f;
    sprintf(msg, "%0.2f", p2);
    Point_t * point13 = new Point_t(x_point_begin_pix - 35, y1_pix - 5);
    DrawString(BitMapMain, msg, point13);
  }
  // Записываем числа по оси "O", "-Y"
  p1 = 0;
  for (n = 0; n <= 10; n++)
  {
    y1_pix = -n * step_grid_y_pix + O_y_pix;
    p2 = p1 + n * 0.1f;
    sprintf(msg, "%0.2f", p2);
    Point_t * point14 = new Point_t(x_point_begin_pix - 30, y1_pix - 5);
    DrawString(BitMapMain, msg, point14);
  }
  // Записываем числа по оси "O", "+X"
  p1 = 0;
  for (n = 0; n <= 10; n++)
  {
    p2 = p1 + n * 0.1f;
    sprintf(msg, "%03.2f", p2);
    Point_t * point15 = new Point_t(O_x_pix - 10 + n * step_grid_x_pix, y_point_end_pix + 5);
    DrawString(BitMapMain, msg, point15);
  }
  // Записываем числа по оси "O", "-X"
  p1 = 0;
  for (n = 1; n <= 10; n++)
  {
    p2 = p1 - n * 0.1f;
    sprintf(msg, "%3.2f", p2);
    Point_t * point16 = new Point_t(O_x_pix - 10 - n * step_grid_x_pix, y_point_end_pix + 5);
    DrawString(BitMapMain, msg, point16);
  }
  // Записываем обозначение оси Y' = Y / | y_max |
  sprintf(msg, "Y' = Y / | y_max |");
  Point_t * point17 = new Point_t(O_x_pix - 5, O_y_pix - 333);
  DrawString(BitMapMain, msg, point17);
  // Записываем значение |y_max|
  sprintf(msg, "| y_max | = %.2f", y_max_abs);
  Point_t * point18 = new Point_t(O_x_pix + 170, O_y_pix - 333);
  DrawString(BitMapMain, msg, point18);
  // Записываем значение y_max
  sprintf(msg, "y_max = %.2f", y_max);
  Point_t * point19 = new Point_t(O_x_pix + 380, O_y_pix - 333);
  DrawString(BitMapMain, msg, point19);
  // Записываем значение y_min
  sprintf(msg, "y_min = %.2f", y_min);
  Point_t * point20 = new Point_t(O_x_pix + 455, O_y_pix - 300);
  DrawString(BitMapMain, msg, point20);
  // Записываем обозначение оси "X' = X / | x_max |"
  sprintf(msg, " X' = X / | x_max | ");
  Point_t * point21 = new Point_t(O_x_pix + 455, O_y_pix - 30);
  DrawString(BitMapMain, msg, point21);
  // Записываем значение x_max
  sprintf(msg, "x_max = %.2f", x_max);
  Point_t * point22 = new Point_t(O_x_pix + 455, O_y_pix + 90);
  DrawString(BitMapMain, msg, point22);
  // Записываем значение x_min
  sprintf(msg, "x_min = %.2f", x_min);
  Point_t * point23 = new Point_t(O_x_pix + 455, O_y_pix + 140);
  DrawString(BitMapMain, msg, point23);
  // Построение графига функции y = f(x)
  // Координаты нулевой (i = 0) точки, с которой строится график
  x_0 = x_min;
  x_0_pix = Convert_X_ToPix(x_0);
  // Рассчитываем "y" и вводим знак минус, чтобы положительное
  // значение "y" отложилось вверх по оси "Y" (а не вниз)
  y_0 = - (Function_of_graph(x_0));
  y_0_pix = Convert_Y_ToPix(y_0);

  // Выбираем чёрное перо, толщиной 4
  SelectObject( BitMapMain->Canvas->Handle, BlackPen_4 );
  // Организовываем цикл по всем точкам, начиная с i = 1
  for(i = 1; i <= Npoints; i++)
  {
    // Рассчитываем абсциссу "x" для данной i-й точки
    x_1 = x_min + i * step_x;
    // Рассчитываем ординату "y" этой i-й точки и вводим знак минус,
    // чтобы положительные значения "y" откладывались вверх (а не вниз),
    // и чтобы строить график традиционно снизу-вверх по оси "Y"
    y_1 = -(Function_of_graph(x_1));
    // Переходим к относительным величинам и пикселам
    x_1_pix = Convert_X_ToPix(x_1);
    y_1_pix = Convert_Y_ToPix(y_1);
    // Строим отрезок линии графика y = f(x) между двумя известными точками
    Point_t * point24 = new Point_t(x_0_pix, y_0_pix);
    Point_t * point25 = new Point_t(x_1_pix, y_1_pix);
    DrawLine(BitMapMain, point24, point25);
    // Присваиваем предидущей (i-1)-й точке координаты данной точки
    x_0_pix = x_1_pix;
    y_0_pix = y_1_pix;
    // Задаём следующую (i+1)-ю точку
  }
}
//---------------------------------------------------------------------------
float TForm_82_Spectr_BD84::Math_Abs(float fVar)
{
  if (fVar < 0)
  {
    fVar *= -1;
  }
  return fVar;
}
//---------------------------------------------------------------------------
float TForm_82_Spectr_BD84::Function_of_graph(float fVar)
{
  int iVar;
  int iVarPlus;
  iVar = (int)(fVar);
  iVarPlus = i_Diapazon(1, 512, iVar, -1); //==\\
  if (iVarPlus == -1)
  {
    return 0;
  }
  return (float)(ArrSpectr[iVarPlus-1]); // функция - спектр
}
//---------------------------------------------------------------------------
void TForm_82_Spectr_BD84::DrawLine
(
  Graphics::TBitmap * BitmapVar,
  Point_t * Pt1,
  Point_t * Pt2
)
{
  if (BitmapVar == NULL)
  {
    // Обработка ошибки может быть здесь!
    return;
  }
  if (Pt1 == NULL)
  {
    // Обработка ошибки может быть здесь!
    return;
  }
  if (Pt2 == NULL)
  {
    // Обработка ошибки может быть здесь!
    return;
  }
  MoveToEx( BitmapVar->Canvas->Handle, Pt1->X, Pt1->Y, NULL );
  LineTo( BitmapVar->Canvas->Handle, Pt2->X, Pt2->Y );
  delete Pt1;
  Pt1 = NULL;
  delete Pt2;
  Pt2 = NULL;
}
//---------------------------------------------------------------------------
void TForm_82_Spectr_BD84::DrawString
(
  Graphics::TBitmap * BitmapVar,
  char * chArrSimvols,
  Point_t * Pt
)
{
  int Length;
  if (BitmapVar == NULL)
  {
    // Обработка ошибки может быть здесь!
    return;
  }
  if (Pt == NULL)
  {
    // Обработка ошибки может быть здесь!
    return;
  }
  Length = GetLengthStr(chArrSimvols);
  TextOut( BitmapVar->Canvas->Handle, Pt->X, Pt->Y, chArrSimvols, Length );
  delete Pt;
  Pt = NULL;
}
//---------------------------------------------------------------------------
float TForm_82_Spectr_BD84::f_Diapazon(float MinVal, float MaxVal, float NormVal, float ErrorVal)
{
  if (NormVal < MinVal)
  {
    return ErrorVal;
  }
  if (NormVal > MaxVal)
  {
    return ErrorVal;
  }
  return NormVal;
}
//---------------------------------------------------------------------------
int TForm_82_Spectr_BD84::i_Diapazon(int MinVal, int MaxVal, int NormVal, int ErrorVal)
{
  if (NormVal < MinVal)
  {
    return ErrorVal;
  }
  if (NormVal > MaxVal)
  {
    return ErrorVal;
  }
  return NormVal;
}
//---------------------------------------------------------------------------
//==\\void TForm_82_Spectr_BD84::SetSpectr(int SpArr[1024])
void TForm_82_Spectr_BD84::SetSpectr(int * SpArr) //==\\
{
  // Пока не обновился спектр, не строить график
  bfUpdateSpector = true; // Спектор обновляется
  if (SpArr == 0)
  {
    return;
  }
  //==\\for (int i = 0; i < 1024; i++)
  for (int i = 0; i < 512; i++) //==\\
  {
    if ( ( DNU <= i ) && ( i <= DVU ) )
    {
      ArrSpectr[i] = (int)SpArr[i];
    }
    else
    {
      ArrSpectr[i] = 0;
    }
  }
  bfUpdateSpector = false; // Спектор обновился
}
//---------------------------------------------------------------------------
void TForm_82_Spectr_BD84::SetSpectrSNakopleniem(unsigned char * SpArr_Data)
{
  // Пока не обновился спектр, не строить график
  bfUpdateSpector = true; // Спектор обновляется
  if (SpArr_Data == 0)
  {
    return;
  }
  //==\\for (int i = 0; i < 1024; i++)
  for (int i = 0; i < 512; i++) //==\\
  {
    ArrSpectr[i] += (int)SpArr_Data[i];
  }
  bfUpdateSpector = false; // Спектор обновился
}
//---------------------------------------------------------------------------
float TForm_82_Spectr_BD84::Convert_Y_ToPix(float Y)
{
  float y_pix;
  if (y_max_abs != 0)
  {
    y_pix = Y / this->y_max_abs * this->M_y + this->O_y_pix;
  }
  else
  {
    y_pix = this->O_y_pix;
  }
  return y_pix;
}
//---------------------------------------------------------------------------
float TForm_82_Spectr_BD84::Convert_X_ToPix(float X)
{
  float x_pix;
  //if (x_max_abs != 0)
  if ((this->x_max - this->x_min) != 0)
  {
    //x_pix = X / this->x_max_abs * this->M_x + this->O_x_pix;
    x_pix = (X - this->x_min) / (this->x_max - this->x_min) * this->M_x + this->O_x_pix;
  }
  else
  {
    x_pix = this->O_x_pix;
  }
  return x_pix;
}
//---------------------------------------------------------------------------
int TForm_82_Spectr_BD84::Convert_Pix_ToX(float x_pix)
{
  float X;
  X = (x_pix - this->O_x_pix) * this->x_max_abs / this->M_x;
  return static_cast<int>(X + 0.5);
}
//---------------------------------------------------------------------------
void TForm_82_Spectr_BD84::ProrisovkaGraph(void)
{
  DrawClear(BitMapMain); // Очищает холст BitMapMain
  // Построение графика нормированного от 0 до 1 по осям "X" и "Y"
  PostroenieGraphNormir(); // Формирует график на холсте BitMapMain
  DrawPlus(BitMapMain, BitMapMarker1); // Добавляет на холст BitMapMain изображение холста BitMapMarker1
  DrawPlus(BitMapMain, BitMapMarker2); // Добавляет на холст BitMapMain изображение холста BitMapMarker2
  DrawPlus(BitMapMain, BitMapMarkerMax); // Добавляет на холст BitMapMain изображение холста BitMapMarkerMax  
  DrawBitMap( BitMapMain ); // Изображение холста BitMapMain переносит (рисует) на форме (на компоненте формы)
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Spectr_BD84::Timer_Obnovleniya_SpectraTimer(
      TObject *Sender)
{
  char chText[MaxLength];
  int iDeltaTime;

  Rekursiya++;
  if (Rekursiya_max < Rekursiya)
  {
    Rekursiya_max = Rekursiya;
  }

  // Form_82_Start->Prot->Data.ArrSpectrSumm - проблема одновременного доступа к объекту ...
  SetSpectr( Form_82_Start->Prot->Data.ArrSpectrSumm ); // Забрать спектр

  this->SpZapCount = Form_82_Start->Prot->GetSpectrZaprosCount(); // Количество тех интервалов, за которые был получен спектр
  this->iIntegral = ArrSum( 0, 512-1, this->ArrSpectr ); // iZnachenieMax, iKanalMax
  this->TimeNaboraSpektra = Form_82_Start->Prot->GetTimeNaboraSpectr();
  this->TimeGotovSpectr = Form_82_Start->Prot->GetTimeGotovSpectr();

  if ( SpZapCount == 0 ) // Количество тех интервалов, за которые был получен спектр равно нулю
  {
    if ( bfFirctVhod == false )
    {
      bfFirctVhod = true;
      Form_82_Start->Prot->ClearBDSpectr(); // Очистить спектр
      this->iIntensivnost = 0;
      this->iTimeSys = 0; // Время системное
      //iDeltaTime = 0;
      //sprintf( chText, "%0.3f", this->iTimeSys / 1000.0 ); // Время в милисекундах
      //Edit_TimeSys->Text = chText;
      ProrisovkaGraph(); // Нарисовать график
    }
  }

  if (SpZapCountOld != SpZapCount)
  {
    SpZapCountOld = SpZapCount;
    if ( SpZapCount == 0 )
    {
      bfFirctVhod = false;
    }
    else
    {
      double kNineBit = 0;
      double kModBus = 0;
      if ( Form_82_Start->Prot->flagModbusProtokol == 0 ) // Протокол: "9-ти битный"
      {
        // 8 ---> 0.2 (сек)
        kNineBit = 25 * Form_82_Start->Prot->Data.KolTikSpectr / 1000.0;
        // СУММАРНЫЙ_СЧЁТ / КОЛИЧЕСТВО_ИНТЕРВАЛОВ * ДЛИТЕЛЬНОСТЬ_ИНТЕРВАЛА
        this->iIntensivnost = (float)this->iIntegral / (SpZapCount * kNineBit);
      }
      else // Протокол: НЕ "9-ти битный"
      {
        // 8 ---> 0.25 (сек)
        kModBus = 31.25 * Form_82_Start->Prot->Data.KolTikSpectr / 1000.0;
        // СУММАРНЫЙ_СЧЁТ / КОЛИЧЕСТВО_ИНТЕРВАЛОВ * ДЛИТЕЛЬНОСТЬ_ИНТЕРВАЛА
        this->iIntensivnost = (float)this->iIntegral / (SpZapCount * kModBus);
      }

      ProrisovkaGraph(); // Нарисовать график
      iTime_1 = Form_82_Start->Prot->DiaGetTime();
      iDeltaTime = iTime_1 - iTime_0;
      this->iTimeSys += iDeltaTime;
      iTime_0 = iTime_1;

      sprintf( chText, "%0.3f", this->iTimeSys / 1000.0 ); // Время системное в милисекундах
      Edit_TimeSys->Text = chText;



      sprintf(chText, "%d", this->iZnachenieMax);
      Edit_Znachenie_MAX->Text = chText;
      sprintf(chText, "%d", this->iKanalMax);
      Edit_Kanal_MAX->Text = chText;
      sprintf(chText, "%d", this->iIntegral);
      Edit_Integral->Text = chText;

      // ===>> ===>> ===>> ===>> 12.10.2019 ===>> ===>> ===>> ===>>
      // Из БД удалена возможность изменять интервал набора спектра
      // поэтому код ниже будет закоментирован

      //if ( Form_82_Start->Prot->flagModbusProtokol == 0 ) // Протокол: НЕ "9-ти битный"
      //{
      //  // СУММАРНОЕ_ВРЕМЯ = КОЛИЧЕСТВО_ИНТЕРВАЛОВ * ДЛИТЕЛЬНОСТЬ_ИНТЕРВАЛА
      //  sprintf(chText, "%0.3f", SpZapCount * kNineBit);
      //}
      //else
      //{
      //  // СУММАРНОЕ_ВРЕМЯ = КОЛИЧЕСТВО_ИНТЕРВАЛОВ * ДЛИТЕЛЬНОСТЬ_ИНТЕРВАЛА
      //  sprintf(chText, "%0.3f", SpZapCount * kModBus);
      //}
      //Edit_TimeSumm->Text = chText; // Время суммарное

      // sprintf(chText, "%0.02f", this->iIntensivnost);
      // Edit_Intensivnost->Text = chText;

      // sprintf(chText, "%d", this->TimeNaboraSpektra);
      // Edit_TimeNaborSpektra->Text = chText;

      // sprintf(chText, "%d", this->TimeGotovSpectr);
      // Edit_TimeReadySpektra->Text = chText;
      // <<=== <<=== <<=== <<=== 12.10.2019 <<=== <<=== <<=== <<===
    }
  }

  if (Rekursiya_max < Rekursiya)
  {
    Rekursiya_max = Rekursiya;
  }  
  Rekursiya--;
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Spectr_BD84::Button_SpectrClick(TObject *Sender)
{
  if ( this->bf_Button_Spectr == false )
  {
    this->bf_Button_Spectr = true;
    this->Button_Spectr->Caption = "Остановить набор спектра"; // (On)";
    this->Timer_Obnovleniya_Spectra->Enabled = true;
    this->Button_WriteTimeSpektr->Enabled = true;
    this->Button_ClearSpektr->Enabled = false;
    Form_82_Start->Prot->OprosSpectra( true, SpinEdit_TimeSpektr->Value );

    // запустим заново набор спектра
    Form_82_Start->Prot->Data.bf_SpectrStart = true;
    iTime_0 = Form_82_Start->Prot->DiaGetTime();
  }
  else // if ( this->bf_Button_Spectr == true )
  {
    this->bf_Button_Spectr = false;
    this->Button_Spectr->Caption = "Начать набор спектра"; // (Off)";
    this->Timer_Obnovleniya_Spectra->Enabled = false;
    this->Button_WriteTimeSpektr->Enabled = false;
    this->Button_ClearSpektr->Enabled = true;
    Form_82_Start->Prot->OprosSpectra( false, SpinEdit_TimeSpektr->Value );
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Spectr_BD84::Button_ClearSpektrClick(
      TObject *Sender)
{
  Form_82_Start->Prot->ClearBDSpectr(); // Очистить спектр
  SetSpectr(Form_82_Start->Prot->Data.ArrSpectrSumm); // Забрать спектр

  ProrisovkaGraph(); // Пеперисовать график

  this->iZnachenieMax = 0;
  this->iKanalMax = 0;
  this->iIntegral = 0;
  this->iIntensivnost = 0;
  this->TimeNaboraSpektra = 0;

  Edit_Znachenie_MAX->Text = "0";
  Edit_Kanal_MAX->Text = "0";
  Edit_Integral->Text = "0";
  Edit_Intensivnost->Text = "0.00";

  Edit_TimeSumm->Text = "0.000";
  Edit_TimeSys->Text = "0.000";

  Edit_TimeNaborSpektra->Text = "0";
  Edit_TimeReadySpektra->Text = "0";

  iTime_0 = Form_82_Start->Prot->DiaGetTime();
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Spectr_BD84::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  if (Timer_Obnovleniya_Spectra->Enabled == true)
  {
    Timer_Obnovleniya_Spectra->Enabled = false;
  }
  Form_82_Start->RadioGroup_VyborProtokola->Enabled = true;
}
//---------------------------------------------------------------------------
//void __fastcall TForm_82_Spectr_BD84::Image_Graph_Spektr_1MouseDown(
//      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
//      int Y)
//{ // При нажатии на ПКМ
//  O_x_pix = O_x_pix;
//} /
//---------------------------------------------------------------------------
void TForm_82_Spectr_BD84::DrawClear
(
    Graphics::TBitmap * BitmapVar
)
{
  BitBlt
  (
    BitmapVar->Canvas->Handle,
    0, 0, Panel_Graph->Width,
    Panel_Graph->Height,
    NULL, 0, 0,
    WHITENESS
  ); // Очистить область графика
}
//---------------------------------------------------------------------------
void TForm_82_Spectr_BD84::DrawPlus
(
    Graphics::TBitmap * BitmapVar, // Поверх накладывается BitmapConst
    Graphics::TBitmap * BitmapConst // Не изменяется
)
{
  BitBlt
  (
    BitmapVar->Canvas->Handle,
    0, 0, Panel_Graph->Width,
    Panel_Graph->Height,
    BitmapConst->Canvas->Handle, 0, 0,
    SRCAND
  ); // Скопировать область графика
}
//---------------------------------------------------------------------------
void TForm_82_Spectr_BD84::DrawVertLine(Graphics::TBitmap * BitmapVar)
{
  int NM; // Номер маркера
  if (BitmapVar == BitMapMarker1)
  {
    NM = 1;
  }
  if (BitmapVar == BitMapMarker2)
  {
    NM = 2;
  }
  // ===>> ===>> ===>> ===>> 12.10.2019 ===>> ===>> ===>> ===>>
  if (BitmapVar == BitMapMarkerMax)
  {
    NM = 0;
  }
  // <<=== <<=== <<=== <<=== 12.10.2019 <<=== <<=== <<=== <<===
  // Выбираем перо для оси координат
  SelectObject( BitmapVar->Canvas->Handle, MarkerPen );
  // Задаём координаты двух граничных точек оси "X"
  point_1 = new Point_t(X_MarkerArr[NM], y_point_end_pix);
  point_2 = new Point_t(X_MarkerArr[NM], y_point_begin_pix);
  // Строим линию через две заданные граничные точки
  DrawLine(BitmapVar, point_1, point_2);
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Spectr_BD84::Button_MashtabClick(TObject *Sender)
{
  if (bf_Button_Mashtab_Nazata == false)
  {
    Button_Mashtab->Caption = "Сжать";
    this->x_min = X_MarkerArr_ToX[1]; //Convert_Pix_ToX(X_MarkerArr[1]);
    this->x_max = X_MarkerArr_ToX[2]; //Convert_Pix_ToX(X_MarkerArr[2]);
    if (this->x_min > this->x_max)
    {
      int temp;
      temp = this->x_min;
      this->x_min = this->x_max;
      this->x_max = temp;
    }
    // Стереть оба маркера
    DrawClear(BitMapMarker1);
    DrawClear(BitMapMarker2);
    bf_Button_Mashtab_Nazata = true;
  }
  else
  {
    Button_Mashtab->Caption = "Растянуть";
    this->x_min = 0;
    //==\\this->x_max = 1024;
    this->x_max = 512;
    // Нарисовать оба маркера
    DrawVertLine(BitMapMarker1);
    DrawVertLine(BitMapMarker2);
    bf_Button_Mashtab_Nazata = false;
  }
  InitParam();
  ProrisovkaGraph();
}
//---------------------------------------------------------------------------
int TForm_82_Spectr_BD84::ArrSum(int iStart, int iBegin, int * iArr)
{
  int i;
  int iSumm;
  int MaxSpectr;
  int MaxKanal;
  iSumm = 0;
  MaxSpectr = iArr[iStart];
  MaxKanal = iStart;

  for (i = iStart; i <= iBegin; i++)
  {
    iSumm += iArr[i];
    if(iArr[i] > MaxSpectr)
    {
      MaxSpectr = iArr[i];
      MaxKanal = i;
    }
  }
  this->iKanalMax = MaxKanal;
  this->iZnachenieMax = MaxSpectr;
  return iSumm;
}
//---------------------------------------------------------------------------
void TForm_82_Spectr_BD84::DrawBitMap( Graphics::TBitmap * BMP )
{
  int Left;
  int Top;
  int DeltaWidth;
  int DeltaHeight;

  Image_Graph->Picture->Assign( BMP );
  PaintBox_Graph->Canvas->Draw( 0, 0, BMP );

  //this->Image1->Canvas->Draw(0, 0, BMP);
  //this->Image1->Picture->Assign(BMP);

  //==\\if (bf_ImageArray == false)
  //==\\{
  //==\\  return;
  //==\\}

  //==\\DeltaWidth = Panel_Graph->Width / const_Delta;
  //==\\DeltaHeight = Panel_Graph->Height / const_Delta;
  //==\\Left = 0;
  //==\\Top = -DeltaHeight;

  //==\\for (int i = 0, j = 0; i < const_Delta * const_Delta; i++)
  //==\\{
  //==\\  if ( ( i % const_Delta ) == 0 )
  //==\\  {
  //==\\    Top += DeltaHeight;
  //==\\    Left = 0;
  //==\\    j++;
  //==\\  }
  //==\\  else
  //==\\  {
  //==\\    Left += DeltaWidth;
  //==\\  }
  //==\\  if ( ((i+j) % 2) == 1 )
  //==\\  {
  //==\\    ImageArray[i]->Canvas->Draw( -Left, -Top, BMP );
  //==\\  }
  //==\\}
  //==\\Left = 0;
  //==\\Top = -DeltaHeight;
  //==\\for (int i = 0, j = 0; i < const_Delta * const_Delta; i++)
  //==\\{
  //==\\  if ( ( i % const_Delta ) == 0 )
  //==\\  {
  //==\\    Top += DeltaHeight;
  //==\\    Left = 0;
  //==\\    j++;
  //==\\  }
  //==\\  else
  //==\\  {
  //==\\    Left += DeltaWidth;
  //==\\  }
  //==\\  if ( ((i+j) % 2) == 0 )
  //==\\  {
  //==\\    ImageArray[i]->Canvas->Draw( -Left, -Top, BMP );
  //==\\  }
  //==\\}
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Spectr_BD84::Image_GraphMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  char chText[MaxLength];

  if (Button == mbRight)
  {
    // ===>> ===>> ===>> ===>> 12.10.2019 ===>> ===>> ===>> ===>>
    //if(Button_Mashtab->Enabled == true)
    //{
    //  Button_Mashtab->OnClick(Sender);
    //}
    NomerMarkera = 0;
    DrawClear(BitMapMarker1);
    DrawClear(BitMapMarker2);
    Edit_Xm1->Text = "";
    Edit_Max_Xm1->Text = "";
    // <<=== <<=== <<=== <<=== 12.10.2019 <<=== <<=== <<=== <<===
  }

  if (Button == mbLeft)
  {
    if(bf_Button_Mashtab_Nazata == false) // Если кнопка не увеличила масштаб (находится в первом состоянии)
    {
      if ((x_point_begin_pix < X) && (X < x_point_end_pix))
      {
        // ===>> ===>> ===>> ===>> 12.10.2019 ===>> ===>> ===>> ===>>
        NomerMarkera = 1;
        // <<=== <<=== <<=== <<=== 12.10.2019 <<=== <<=== <<=== <<===
      }
      else
      {
        return;
      }
      X_MarkerArr[1] = X;
      X_MarkerArr_ToX[1] = Convert_Pix_ToX(X_MarkerArr[1]);

      sprintf(chText, "%d", X_MarkerArr_ToX[1]);
      Edit_Xm1->Text = chText;

      sprintf(chText, "%d", ArrSpectr[X_MarkerArr_ToX[1]]);
      Edit_Max_Xm1->Text = chText;

      DrawClear(BitMapMarker1);
      DrawVertLine(BitMapMarker1);
      Button_Mashtab->Enabled = false;
    }
  }
  ProrisovkaGraph();
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Spectr_BD84::FormShow(TObject *Sender)
{
  ProrisovkaGraph(); // Нарисовать график
  if ( this->bf_Button_Spectr == true )
  {
    Timer_Obnovleniya_Spectra->Enabled = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Spectr_BD84::RadioButton_GraphClick(
      TObject *Sender)
{
  bf_RadioButton_Graph = true;
  ProrisovkaGraph(); // Нарисовать график
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Spectr_BD84::RadioButton_GistogrammaClick(
      TObject *Sender)
{
  bf_RadioButton_Graph = false;
  ProrisovkaGraph(); // Нарисовать график
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Spectr_BD84::RadioButton_KanalClick(
      TObject *Sender)
{
  bf_RadioButton_Kanal = true;
  ProrisovkaGraph(); // Нарисовать график
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Spectr_BD84::RadioButton_VoltClick(
      TObject *Sender)
{
  bf_RadioButton_Kanal = false;
  ProrisovkaGraph(); // Нарисовать график
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Spectr_BD84::Button_WriteKolTikSpectrClick(
      TObject *Sender)
{
  Form_82_Start->Prot->Data.bfSetTimeSpektr = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Spectr_BD84::SpinEdit_TimeSpektrChange(
      TObject *Sender)
{
  char chCaption[50];
  int iValue;
  float fValue;
  if ( SpinEdit_TimeSpektr->Text == "" )
  {
    return;
  }
  iValue = SpinEdit_TimeSpektr->Value;
  if ( iValue > 254 )
  {
    iValue = 254;
    SpinEdit_TimeSpektr->Text = "254";
  }
  if ( iValue < 8 )
  {
    iValue = 8;
  }
  if ( Form_82_Start->Prot->flagModbusProtokol == 0 ) // Протокол: НЕ "9-ти битный"
  {
    fValue = iValue * 25 / 1000.0f;
  }
  else
  {
    fValue = iValue * 31.25 / 1000.0f;
  }
  sprintf( chCaption, "= %0.3f [с.]", fValue );
  Label_TimeSpektrSek->Caption = chCaption;
}
//---------------------------------------------------------------------------
void __fastcall TForm_82_Spectr_BD84::Button_WriteTimeSpektrClick(
      TObject *Sender)
{
  Form_82_Start->Prot->OprosSpectra( true, SpinEdit_TimeSpektr->Value );
  Form_82_Start->Prot->Data.FlagWriteKolTikSpektr = true;
}
//---------------------------------------------------------------------------


