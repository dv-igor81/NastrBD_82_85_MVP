//---------------------------------------------------------------------------
#ifndef Unit_Form_Puasson8BDH
#define Unit_Form_Puasson8BDH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
class TFormPuasson8BD : public TForm
{
__published:	// IDE-managed Components

  TCheckBox * CheckBox_AddrBD1;
  TCheckBox * CheckBox_AddrBD2;
  TCheckBox * CheckBox_AddrBD3;
  TCheckBox * CheckBox_AddrBD4;
  TCheckBox * CheckBox_AddrBD5;
  TCheckBox * CheckBox_AddrBD6;
  TCheckBox * CheckBox_AddrBD7;
  TCheckBox * CheckBox_AddrBD8;

  TEdit * Edit_SN1;
  TEdit * Edit_SN2;
  TEdit * Edit_SN3;
  TEdit * Edit_SN4;
  TEdit * Edit_SN5;
  TEdit * Edit_SN6;
  TEdit * Edit_SN7;
  TEdit * Edit_SN8;

  TPanel * Panel_Display_BD1;
  TPanel * Panel_Display_BD2;
  TPanel * Panel_Display_BD3;
  TPanel * Panel_Display_BD4;
  TPanel * Panel_Display_BD5;
  TPanel * Panel_Display_BD6;
  TPanel * Panel_Display_BD7;
  TPanel * Panel_Display_BD8;

  TCSpinEdit * SpinEdit_AddrBD1;
  TCSpinEdit * SpinEdit_AddrBD2;
  TCSpinEdit * SpinEdit_AddrBD3;
  TCSpinEdit * SpinEdit_AddrBD4;
  TCSpinEdit * SpinEdit_AddrBD5;
  TCSpinEdit * SpinEdit_AddrBD6;
  TCSpinEdit * SpinEdit_AddrBD7;
  TCSpinEdit * SpinEdit_AddrBD8;

  TCSpinEdit * SpinEdit_Time;

  TScrollBox * ScrollBoxMain;
  TGroupBox * GroupBoxMain;

  TLabel * Label_sernum;
  TLabel * Label_addr_BD;
  TLabel * Label_Time;
  TLabel * Label_info;
  TPanel * Panel_Info;

  TButton * Button_Start;
  TButton * Button_detail;
  TButton * Button_ReadLogs;
  TButton * Button_Stop;

  TCSpinEdit * SpinEdit_readTimeout;
  TLabel * Label_readTimeout;
  TCheckBox * CheckBox_Err;
  TCheckBox * CheckBox_AllBD;
  TLabel * Label_Time_Diapazon;
  TButton * Button_Exit;

  TButton * Button_Graph_01;
  TButton * Button_Graph_02;
  TButton * Button_Graph_03;
  TButton * Button_Graph_04;
  TButton * Button_Graph_05;
  TButton * Button_Graph_06;
  TButton * Button_Graph_07;
  TButton * Button_Graph_08;
  TButton * Button_Graph;

  TEdit * Edit_SchetSek01;
  TEdit * Edit_SchetSek02;
  TEdit * Edit_SchetSek03;
  TEdit * Edit_SchetSek04;
  TEdit * Edit_SchetSek05;
  TEdit * Edit_SchetSek06;
  TEdit * Edit_SchetSek07;
  TEdit * Edit_SchetSek08;

  TEdit * Edit_PNSch01;
  TEdit * Edit_PNSch02;
  TEdit * Edit_PNSch03;
  TEdit * Edit_PNSch04;
  TEdit * Edit_PNSch05;
  TEdit * Edit_PNSch06;
  TEdit * Edit_PNSch07;
  TEdit * Edit_PNSch08;

  TEdit * Edit_KvoIsp01;
  TEdit * Edit_KvoIsp02;
  TEdit * Edit_KvoIsp03;
  TEdit * Edit_KvoIsp04;
  TEdit * Edit_KvoIsp05;
  TEdit * Edit_KvoIsp06;
  TEdit * Edit_KvoIsp07;
  TEdit * Edit_KvoIsp08;

  TLabel * Label_KvoIsp01;
  TLabel * Label_KvoIsp02;
  TLabel * Label_KvoIsp03;
  TLabel * Label_KvoIsp04;
  TLabel * Label_KvoIsp05;
  TLabel * Label_KvoIsp06;
  TLabel * Label_KvoIsp07;
  TLabel * Label_KvoIsp08;

  TLabel * Label_SchetSek01;
  TLabel * Label_SchetSek02;
  TLabel * Label_SchetSek03;
  TLabel * Label_SchetSek04;
  TLabel * Label_SchetSek05;
  TLabel * Label_SchetSek06;
  TLabel * Label_SchetSek07;
  TLabel * Label_SchetSek08;


  TLabel * Label_PNSch01;
  TLabel * Label_PNSch02;
  TLabel * Label_PNSch03;
  TLabel * Label_PNSch04;
  TLabel * Label_PNSch05;
  TLabel * Label_PNSch06;
  TLabel * Label_PNSch07;
  TLabel * Label_PNSch08;

  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall Button_StartClick(TObject *Sender);
  void __fastcall Button_StopClick(TObject *Sender);
  void __fastcall Button_detailClick(TObject *Sender);
  void __fastcall CheckBox_AllBDClick(TObject *Sender);
  void __fastcall Button_ExitClick(TObject *Sender);
  void __fastcall Button_Graph_01Click(TObject *Sender);
  void __fastcall Button_Graph_02Click(TObject *Sender);
  void __fastcall Button_Graph_03Click(TObject *Sender);
  void __fastcall Button_Graph_04Click(TObject *Sender);
  void __fastcall Button_Graph_05Click(TObject *Sender);
  void __fastcall Button_Graph_06Click(TObject *Sender);
  void __fastcall Button_Graph_07Click(TObject *Sender);
  void __fastcall Button_Graph_08Click(TObject *Sender);
  void __fastcall Button_GraphClick(TObject *Sender);
        
private:	// User declarations

  char chLogFileName[8 /* количество строк */][/*16*/26 /* длина строки */]; // имена файлов-логов
  int handle [ 8 ]; // дескрипторы файлов (нужно подключить <io.h>)
  char shFileString[16]; // Строка для записи в файл

  void GetAddrBDArr( void );
  int MinSchet(int * ArrSchet);
  void PostroitGrafik(void);    

public:		// User declarations
  int DIA_Interval; // Интервал, для управления таймером
  unsigned char AddrBDArr[8]; // 248 - Блок детектирования не опрашивается, 1...247 - адрес БД
  //===>> (24.10.2014)
  unsigned char IndexArr[8]; // Множество тех блоков (индексов массива AddrBDArr, адресов БД), которые выбрал пользователь
  unsigned char pInd; // "указатель" (индекс) массива IndexArr (указывает на тот блок, слово состояние которого нам нужно считать)
  unsigned char maxInd; // Сколько БД выбрано пользователем.
  //<<=== (24.10.2014)
  unsigned long SerialNumArr[8]; // Серийные номера БД

  bool bFlag8BD_PSW; // true - Один из 8-ми блоков ответил успешно (есть флаг готовности счёта)
  bool bFlagSetTimeInterval[8]; // false - не выполнялась функция SetTimeInterval(8) для БД
  bool bFlagGetSerialNum[8]; // false - не выполнялась функция ReadFlashInvert(10, &SerialNumArr[i]) для БД
  bool bFlagDisplaySN[8]; // false - не отображались серийные номера
  bool bFlagOprosBD8; // false - ещё ни разу не вызывалась функция OprosBD8Arr
  bool bFlagDisplayArr[8]; // false = расчёт не проведён

  float SredMas[8][300000]; // Массив, для запоминания счетов до 8-ми БД
  int indexSM[8]; // Значения индексов, для заполнения счетами массива SredMas
  
  bool bFlagDisplay; // false = Не отображать результаты расчётов
  bool bFlagDisplay_temp;
  int siFlagGraph;
  bool bFlagWork;

  unsigned int ErrorCodBD[8]; // Код ошибки

  unsigned int KolErrors[8]; // Количество ошибок
  unsigned int KolErrorsPodryad; // Количество ошибок подряд

  unsigned int PrizNesnChet[8]; // Количество признаков неснятого счёта
  unsigned int Chet[8]; // Текущий счёт
  signed int PSW[8]; // Текущее слово состояния (-1 - ошибка)

  unsigned int ChetNakapl[8]; // Сумарный счёт за секунду формируется при помощи этого накапливаемого счёта
  unsigned int ChetZaSekundu[8]; // Сумарный счёт за секунду
  unsigned char KolVoChet[8]; // Количество полученных с БД счетов (сколько раз получали счет с БД)

  unsigned int dTSum; // Интервал времени, за который опрашиваются выбранные блоки
  unsigned int dTmaxSum; // Максимум dTSum

  unsigned int dTPeriod; // Интервал времени, через который опрашиваются выбранные блоки
  unsigned int dTmaxPeriod; // Максимум dTSum

  unsigned int dTBD[8];
  unsigned int dTmaxBD[8];

  int TimeBD[8];
  int MinTimeBD;

  TPanel * Panel_Display_Arr[8];
  TEdit * Edit_ArrSerNum[8];
  TCSpinEdit * SpinEdit_AddrBDArr[8];
  TCheckBox * CheckBox_AddrBDArr[8];
  TButton * Button_GraphArr[8];

  TEdit * Edit_SchetSekArr[8];
  TEdit * Edit_PNSchArr[8];
  TEdit * Edit_KvoIspArr[8];

  __fastcall TFormPuasson8BD(TComponent* Owner);
  void __fastcall Display( void );
  void __fastcall TimerOn( void );
  void __fastcall TimerOff( void );

  void __fastcall FileArrayInit( int IndexArr  );
  void __fastcall FileWriteData( int IndexArr );  
  void __fastcall FileWriteError( int IndexArr );
  void UpdateGraph( int NomerBD ); // Обновлять графики (0 <= NomerBD < 8) 

};
//---------------------------------------------------------------------------
extern PACKAGE TFormPuasson8BD * FormPuasson8BD;
//---------------------------------------------------------------------------
#endif
