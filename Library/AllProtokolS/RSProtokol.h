//---------------------------------------------------------------------------
#ifndef RSProtokolH
#define RSProtokolH
//---------------------------------------------------------------------------
#include "modbus.h"
#include "unistd.h"
#include "modbus-private.h"
#include "config.h"
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include "ActionEvent.h"
using namespace smartevents;
//---------------------------------------------------------------------------
#include <Sockets.hpp>
//---------------------------------------------------------------------------
// создание псевдонима именам
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
//---------------------------------------------------------------------------
class NastrCom_t
{
public:
  TDCB lpDCB;
  TCommTimeouts lpCommTimeouts;
};
//---------------------------------------------------------------------------
class Data_t
{
public:
  char Ver[5]; // Для номера версии
  int Ver_HEX; // Версия прошивки
  unsigned char IndAdr; // Индивидуальный адрес устр-ва
  unsigned char GrAdr; // Групповой адрес устр-ва
  unsigned int Temper; // Темпетатура КОД
  float flTemper; // Температура, градусы Цельсия
  unsigned int DNU; // Напряжение на выходе дискриминатора нижнего уровня КОД
  double dbDNU; // Напряжение на выходе дискриминатора нижнего уровня [В]
  unsigned int DVU; // Напряжение на выходе дискриминатора верхнего уровня КОД
  double dbDVU; // Напряжение на выходе дискриминатора верхнего уровня [В]
  unsigned int UhiI, UhiIsr, sumUhiI[50], kodUhiI, ptrUhiI; // UhiI - Напряжение ВЫСОКОЕ измер. (по50) КОД
  double dbUhiIsr; // Напряжение ВЫСОКОЕ измер. (по50) [В]
  unsigned int SIM3; // Длительность импульса ШИМ (КОД)
  double dbSIM3; // Длительность импульса ШИМ [мкс.]
  unsigned int SIM4; // Период ШИМ измеренный (КОД)
  double dbSIM4; // Период ШИМ измеренный [мкс.]
  // ===
  unsigned int sim3;
  unsigned int sim4;
  // ===
  unsigned int SIM2; // Ток светодиода рассчитанный (КОД)
  unsigned int Ampl; // Отклик светодиода (ворота = 5) (КОД)
  double dbAmpl; // Отклик светодиода (ворота = 5) [В]
  int LEDAmpI, LEDAmpR, LEDAmpRcp, LEDAmp[200], kodLEDAmp, ptrLEDAmp;
  double dbLEDAmpRcp;
  unsigned int flagFirst;  // Флаг обновления данных (делитель времени 1)
  unsigned int flagSecond; // Флаг обновления данных (делитель времени 1)
  unsigned char MasRez[8]; // = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
  unsigned char PSW; // Слово состояния программы БД
  unsigned int CountImp; // Счёт с БД за установленный интервал (0,2 секунды или 0,25 секунды в зависимости от протокола)
  unsigned int Sred02; // Среднее с БД за 0,2 секунды
  unsigned int TSchet; // Текущее время счёта импульсов
  // ===
  unsigned int TSchetTemp;
  unsigned int TimeTSchet; // Сколько время прошло (в секундах) от начала получения счёта (усреднённого за "время измерения" секунд)
  unsigned int TimeTSchet_dia; // Для обнулении поля: "Текущее время счёта" при новом старте
  bool bFlagCount; // Флаг вкл/откл режима счета импульсов
  float Sred; // Среднее с БД за 0,2 секунды
  // ===
  unsigned int SumSchet; // Суммарное время счёта импульсов
  unsigned int T_Limit; // Время счета импульсов  

  unsigned int count; // Счётчик 200 мкс. интервалов
  unsigned int count2; // Счётчик 200 мкс. интервалов

  String Str_hex;
  char Str_err[250]; // Сюда копируется диагностическое сообщение об ошибке

  bool flagGetVersion; // false - не было получено в текущей сесии, true - получено в текущей сесии
  bool flagSetTimeInterval; // ---
  bool flagGetTimeInterval; // ---

  bool flagSetSpectrInterval;
  bool flagGetSpectrInterval;

  bool flagGetIndAdr; // ---
  bool flagGetGrpAdr; // ---
  bool bfSetTimeSpektr;

  unsigned long IndAdrZ; // Индивидуальный адрес заданный
  unsigned long GrpAdrZ; // Групповой адрес заданный
  unsigned long DNUZ; // Значение дискриминатора нижнего уровня
  double dbDNUZ;
  unsigned long DVUZ; // Значение дискриминатора верхнего уровня
  double dbDVUZ;
  unsigned long LEDAmpZ; // Ток светодиода заданный
  unsigned long UhiZ; // Длительность ШИМа заданная
  unsigned long SIMstartZ; // Период ШИМ начальный
  unsigned long SIMminZ; // Период ШИМ минимальный
  unsigned long LedZadZ; // Заданный отклик светодиода
  unsigned long m_ulSerialNumberZ; // Серийный номер
  unsigned long m_ulUZ; // Напряжение номинальное
  unsigned long m_ulU0Z; // Начальное напряжение (при нулевой длительности ШИМ)
  // ===
  float m_fltU;
  unsigned int m_iU;
  float m_fltU0;
  unsigned int m_iU0;
  int period; // Период (используется в режиме подбора Avto)
  int dlitelnost; // Длительность импульсов ШИМ

  int KolAuto; // Количество итераций (используется в режиме подбора Avto)
  int KolPopytok; // Количество попыток (используется в режиме подбора Avto)

  int shag; // Шаг (используется в режиме подбора Avto)
  int delta; // Дельта (используется в режиме подбора Avto)
  // ===
  double dbm_ulU0Z;
  double dbm_ulUZ;
  char m_strStickyNote[24+1]; // Коментарий (последний символ для завершающего нуля)
  char m_strStickyNote_temp[24+1]; // Коментарий (последний символ для завершающего нуля)
  // ===
  float m_fltDac0;
  unsigned int m_iDac0;
  float m_fltDac1;
  unsigned int m_iDac1;
  unsigned long DlInterPhon; // Длительность интервала фона
  unsigned char KolTik;
  unsigned char KolTikSpectr;
  // ===

  int IP_Port;
  int Addr_BD_TCP; // Адрес БД для протокола ModBus TCP
  char IP_Addr[18]; // "192.168.3.4"
  bool bFlag_TCP_Connect;
  // 20.08.2015
  unsigned char ArrSpectrBlock[16];
  unsigned char ArrSpectr[512];
  int ArrSpectrSumm[512];
  int iSpektrZaprosCount; // Количество удачных обменов спектром
  int TimeNaboraSpectr; // Время чтения спектра
  int TimeGotovSpectr; // Время готовности спектра
  int iSpektrZaprosErr; // Количество ошибок обмена спектром (подряд)
  //==\\
  //==\\bool FlagReadKolTikSpektr;
  bool FlagWriteKolTikSpektr;
  bool bf_SpectrStart;
  // ==== ===== ===== 12.01.2016 ===>>
  unsigned int TimeZapuskBD;
  // ==== ===== ===== 12.01.2016 <<===
};

class Time_t
{
public:
  WORD Hour; // час
  WORD Min; // минута
  WORD Sec; // секунда
  WORD MSec; // милисекунда
  short PSW_b0;
  short PSW_b1;
  /////////////////////////////////////////////////////////////////////
  unsigned int flagFirst;  // Флаг обновления данных (делитель времени 1)
  unsigned int flagSecond; // Флаг обновления данных (делитель времени 1)
  int count;
  //int N0; // Количество признаков готового счёта (PSW_b0 == 1)
  //int N1; // Количество признаков неснятого счета (PSW_b1 == 1)
};
//---------------------------------------------------------------------------
class RSProtokol_t
{
private:
  HINSTANCE dllInstanse;
  HANDLE COMPort;
  NastrCom_t forUse;
  NastrCom_t forSave;
  char DEVID[16];

  int ret_size;
  int CodeRet; // Эта переменная возвращается функциями

  //!unsigned char buf_write[16]; // Буфер для чтения
  //!unsigned char buf_read[16]; // Буфер для записи
  unsigned char buf_write[32]; // Буфер для чтения
  unsigned char buf_read[32]; // Буфер для записи

  unsigned char * pbuf_write; // Указатель на буфер чтения
  unsigned char * pbuf_read; // Указатель на буфер записи

  //!unsigned char buf_write_modbus[16]; // Буфер для чтения NastrBD
  //!unsigned char buf_read_modbus[16]; // Буфер для записи NastrBD
  unsigned char buf_write_modbus[32]; // Буфер для чтения NastrBD
  unsigned char buf_read_modbus[32]; // Буфер для записи NastrBD
  unsigned short CRC;
  // ===
  bool FlagOpros; // Флаг для изменения состояния кнопки (надпись ОТКРЫТЬ/ЗАКРЫТЬ)
  bool FlagAutoOpros; // Флаг для изменения состояния кнопки (надпись start/stop)

  // ===
  float TConvert( int Temper );
  // ===
  int strlcpy(char * dest, const char * src, int dest_size);
  int RSConnect(const char * device, int baud, int parity, int data_bit, int stop_bit);
  // ===
  int WriteToPort(/*const*/ unsigned char * buf, int count, int parity);
  int ReadFromPort(unsigned char * buf, int count, int parity);
  void ObnulenieArr(unsigned char Arr[], int N, unsigned char uchVal = 0);
  void ObnulenieArr(int Arr[], int N, unsigned char uchVal = 0);  

  bool bfOprosSpectra;
  bool bfPervVhod; // true - Первый вход в функцию int OprosBDSpektr()
  void FlagAvtoSnyat(); // Снять галочку "Авто" (напряжение)
  void FlagAvtoSnyatDiskr(); // Снять галочки "Авто" (пороги дискриминации)
//---------------------------------------------------------------------------
// стремимся выполнить это --> (U0 + Un == Uhi)
// или это --> (U0 * 0,81 + Un == Uhi)
  void AvtoPodborUhiIter(); // Автоподбот Uhi 
public:
  int AutoPodbor_1_Un_2_U81;
  int DiaGetTime(void); // Время в милисекундах
  void ClearBDSpectr(void);
  void OprosSpectra(bool bf); // bf = true - разрешить опрос спектра в функции OprosBD()
  int GetSSP(unsigned char * SSP);
  int GetCountImp(unsigned int * CImp);
  int GetVersia(unsigned char * Versia);
  int GetGrpAdr(unsigned char * Adr);
  int GetTemp(unsigned int * Temper);
  int GetDNU(unsigned int * DNU);
  int GetDVU(unsigned int * DVU);
  int GetUhi(unsigned int * UhiI);
  int GetSIM3(unsigned int * SIM); // Считать длительность импульса ШИМ
  int GetSIM4(unsigned int * SIM);
  int GetSIM2(unsigned int * SIM);
  int GetLEDAmp(unsigned int * Ampl);
  int GetLEDAmpR(int * AmplR);
  int GetTimeInterval(unsigned char * TimeInt);
  int GetStickyNote(char * strStickyNote);
  
  double Code2DAC( int var );
  double Code2U( int var );


  int Set_P37(void); // Установить P3.7 (отключить лампочку)
  int Reset_P37(void); // Сбросить P3.7 (зажечь лампочку)

  int SpectrClear(void);
  int SpectrStart(void);
  int SpectrStop(void);
  int SpectrReadBuf(unsigned char Block, unsigned char Mas[16]);
  int SetTimeSpectr(unsigned char TimeInt);  // Установка времени набора спектра KolTikSpectr
  int GetTimeSpectr(unsigned char * TimeInt); // Чтение времени набора спектра KolTikSpectr
  int GetSpectrZaprosCount( void )
  {
    return this->Data.iSpektrZaprosCount; // Количество удачных обменов спектрами
  }
  int GetTimeNaboraSpectr( void )
  {
    return this->Data.TimeNaboraSpectr; // Время чтения спектра
  }
  int GetTimeGotovSpectr( void )
  {
    return this->Data.TimeGotovSpectr; // Время готовности спектра
  }

    
  unsigned char SSP_Value; // Переменная для протокола "старый"

  /*unsigned*/ char err; // Возврат функции ReadFile сохраняется в err
  unsigned char MB_length_to_read;
  
  int FlagDebug; // Флаг отладки

  // ===>> 17.07.2017
  //!bool flagModbusProtokol; // Флаг протокола false - "Старый", true - ModBusRTU (есть в классе RSProtokol_t)
  int flagModbusProtokol; //! // Флаг протокола (есть в классе RSProtokol_t)
  // 0 - "9-ти битный"
  // 1 - ModBus RTU
  // 2 - ModBus TCP
  // 3 - ModBus RTU (TCP/IP)
  // <<=== 17.07.2017

  // Отменил flagFirstAddr 23.10.2014
  bool flagFirstAddr; // true - при первом обращении к БД или при сбое передачи
  bool flagSpeed; // Флаг скорости опроса, для протокола "Старый" (true - выше скорость опроса)
  bool flagTCP;

  int testErr;
  unsigned char AddrBD;
  RSProtokol_t(); // конструктор
  uint16_t crc16(uint8_t * buffer, uint16_t buffer_length);
  Time_t ArrTime[100], ArrTimeTek;
  unsigned short N0;
  unsigned short N1;
  int indexArrTime;
  int MaxIndexArrTime;
  // ===
  int OprosBD(void); // -1 - ошибка связи, 0 - звязь работает
  int OprosBDParam( void ); // -1 - ошибка связи, 0 - звязь работает


  // Возвращаемое значение: -1 - ошибка связи, 0 - звязь работает
  // Параметры: iTimeRead - время чтения спектра, iTimeGotovh - время готовности спектра
  int OprosBDSpektr(bool bfTime, int * iTimeRead, int * iTimeGotov );

  int OprosBD_2(void);
  void Reset(void);
  // ===
  int RSConnect(const char * device);
  int RSDisConnect(void);
  // ===
  int SetSSP(unsigned char SSP);  
  int SetIndAdr(unsigned char Adr);
  int SetGrpAdr(unsigned char Adr);
  int SetDNU(unsigned int DNUZ);
  int SetDVU(unsigned int DVUZ);
  int SetLEDAmp(unsigned int Amp);
  int SetUhi(unsigned int Uhi); // Установить длительность ШИМ
  int SetUhi2(unsigned int Uhi); // Установить период ШИМ
  int SetLEDOtkl(unsigned int Amp);
  int SetSerialNumber(unsigned int uiSerialNumber);
  int SetU0(unsigned int uiU0);
  int SetU(unsigned int uiU);
  int SetTimeInterval(unsigned char TimeInt);  

  int ReadFlashInvert(unsigned int Adr, unsigned long * Data);
  int ReadFlash(unsigned int Adr, unsigned long * Data);  
  int ReadFlash2(unsigned int Adr, unsigned long * Data);  
  
  int WriteFlashInvert(unsigned int Adr, unsigned long Data);
  int WriteFlash(unsigned int Adr, unsigned long Data);
  int WriteFlash2(unsigned int Adr, unsigned long Data);



  int ExRead( int Index, unsigned short AddrRegModBus, unsigned long * ptr_Edit_3_01__14 );
  int ReadFromBDModbus_BD82( void );
  int ReadFromBDModbus_BD85_New( void );
  int ReadFromBDModbus( unsigned short * AddrRegModBus );

  int ExWrite( int Index, unsigned short AddrRegModBus, unsigned long * ptr_Edit_3_01__14 );
  int WriteToBDModBus_BD82( void );
  int WriteToBDModBus_BD85_New( void );
  int WriteToBDModBus( unsigned short * AddrRegModBus );

  void ClearReqRsp( uint8_t * Arr, int Length ); // Очистить массив (запроса или ответа)
  int CommandExec(unsigned char kOutByte, unsigned char kInByte);

  void NullsToStr_err(void); // Очистка строки сообщений об ошибках
  int SetStickyNote(char * strStickyNote);
  //
  int GetIndAdr(unsigned char * Adr);
  float Clamp(float fltValue, float fltMin, float fltMax);
  //double UpdatePID(double error, double position);
  double UpdatePID0(double error);
  double UpdatePID1(double error);
  void ResetPID(void);

  void ResetPID0(void);
  bool AvtoDnu();

  void ResetPID1(void);
  bool AvtoDvu();

  bool bf_AvtoDnu;
  bool bf_AvtoDvu;
  bool bf_WriteDef_DVU;

  /// Можно сбрасывать флажки для автоподбора дискриминаторов
  bool IsPidSResetted();
  // ===
  void SetComPortHahdle( HANDLE hCOM );
  void FreeComPortHahdle( void );

  double P_Gain0;
  double I_Gain0;
  double I_Error0;
  double I_State0;

  double I_Min0;
  double I_Max0;
  double DRIVE0_MIN;
  double DRIVE0_MAX;
  //
  int read_registers
      (int BDAddr, // Адрес БД
      int REGAddr, // Адрес регистра
      int nb, // Количество регистров
      uint16_t * dest // Массив
  );
  int write_registers
      (int BDAddr, // Адрес БД
      int REGAddr, // Адрес регистра
      int nb, // Количество регистров
      uint16_t * src // Массив 
  );
  int IncFreqLEDImp(unsigned char State); // увеличение частоты импульсов от светодиода
  int SpectrCon(unsigned char State); // Управление снятием спектра импульса 1-ручное, 0-программное
  int ARCHCon(unsigned char State); // Управление системой АРЧ 0-включить, 1-отключить

  void ReadKoef(
      float * k1,
      unsigned long * Longk1,
      float * A1,
      unsigned long * LongA1,
      float * k2,
      unsigned long * Longk2,
      float * A2,
      unsigned long * LongA2,
      int MasSveto[256]      
      );
  void WriteKoef(
      float * k1,
      unsigned long * Longk1,
      float * A1,
      unsigned long * LongA1,
      float * k2,
      unsigned long * Longk2,
      float * A2,
      unsigned long * LongA2,
      int MasSveto[256],
      bool FlagGrafik
    );

  //void OprosBD8Arr( void );
  unsigned int dT;
  unsigned int dTmax;  

  // период ШИМ измеренный
  const unsigned int m_nPwmCycleTimeMin;
  const unsigned int m_nPwmCycleTimeMax;
  // длительность импульсов ШИМ
  const unsigned int m_nPwmPulseLengthMin;
  const unsigned int m_nPwmPulseLengthMax;

  const unsigned int m_nPwmCycleTimeOffset;
  const unsigned int m_nPwmPulseLengOffset;

  bool CheckBox_auto_Checked; // = true, если флажок CheckBox_auto установлен
  bool CheckBox_DAuto_Checked; // = true, если флажок CheckBox_DAuto установлен
  void Set_CheckBox_DAuto_Checked(bool dNu, bool dVu); // 2018.03.19
  int auto_State_Flag;

  Data_t Data; // Данные для вывода на форму
  int ErrorCode;
  int ReturnVar; // Для OprosBD главной формы
  char Str_err[250 * 2]; // Сюда копируется диагностическое сообщение об ошибке

  int flagARCH; // флаг АРЧ (автоматическая регулировка чувствительности)
  int flagUchSv; // флаг учащения светодиода
  //bool bf_ARH_UchSv;

  bool newProsivka; // = true - два стоповых бита, нет контроля четности
  // иначе - один стоповый бит, контроль чётности SPACEPARITY

  int baud;
  int parity;
  int data_bit;
  int stop_bit;

  unsigned long Edit_3_01;
  unsigned long Edit_3_02;
  unsigned long Edit_3_03;
  unsigned long Edit_3_04;
  unsigned long Edit_3_05;
  unsigned long Edit_3_06;
  unsigned long Edit_3_07;
  unsigned long Edit_3_08;
  unsigned long Edit_3_09;
  unsigned long Edit_3_10;
  unsigned long Edit_3_11;
  unsigned long Edit_3_12;
  unsigned long Edit_3_13;
  unsigned long Edit_3_14;
  unsigned long Edit_3_15;  

  unsigned long * ptr_Edit_3_01__14[15];
  unsigned short AddrRegModBus_BD82[15];
  
  unsigned short AddrRegModBus_BD85_New[14];  


  bool flagARCH_Off;

  // Для проверки  записи в EEPROM
  float k1PR;
  float A1PR;
  float k2PR;
  float A2PR;
  unsigned long Longk1PR;
  unsigned long LongA1PR;
  unsigned long Longk2PR;
  unsigned long LongA2PR;
  int MasSvetoPR[256];

  bool bFlagWork; // Флаг режима измерения включён/выключен

  // Количество подинтервалов (счетов за подинтервал времени),
  // которое нужно сложить, чтобы получить счет за секунду
  unsigned char KolVoPodinterval;

  DWORD ReadTimeout;
  DWORD WriteTimeout;

    double I_State;
    double I_Error1;
    double I_State1;

    double I_Min1;
    double I_Max1;

    const double P_Gain1;
    const double I_Gain1;
    const double DRIVE1_MIN;
    const double DRIVE1_MAX;

    //===>> 29.10.2018
    ActionEvent<> ev_FlagAvtoSnyatDiskr;
    ActionEvent<> ev_OprosBDParam;
    ActionEvent<> ev_CheckBoxAutoCheckedFalse;
    ActionEvent<> ev_CheckBox081CheckedFalse;
    //<<=== 29.10.2018
};
//---------------------------------------------------------------------------
//double I_Error = 0.0;
//double I_State = 0.0;

//double I_Error1 = 0.0;
//double I_State1 = 0.0;

//const double P_Gain1 = 12.0;
//const double I_Gain1 = 2.0;

//const double DRIVE1_MIN = -25.0;
//const double DRIVE1_MAX	= 25.0;

//const double DRIVE_MIN = -100.0;
//const double DRIVE_MAX = 100.0;

//const double P_Gain	= -0.036;
//const double I_Gain	= -0.42;

//double I_Min1 = DRIVE1_MIN;
//double I_Max1 = DRIVE1_MAX;

//double I_Min = DRIVE_MIN;
//double I_Max = DRIVE_MAX;


//---------------------------------------------------------------------------
#endif
