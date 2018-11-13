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
// �������� ���������� ������
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
  char Ver[5]; // ��� ������ ������
  int Ver_HEX; // ������ ��������
  unsigned char IndAdr; // �������������� ����� ����-��
  unsigned char GrAdr; // ��������� ����� ����-��
  unsigned int Temper; // ����������� ���
  float flTemper; // �����������, ������� �������
  unsigned int DNU; // ���������� �� ������ �������������� ������� ������ ���
  double dbDNU; // ���������� �� ������ �������������� ������� ������ [�]
  unsigned int DVU; // ���������� �� ������ �������������� �������� ������ ���
  double dbDVU; // ���������� �� ������ �������������� �������� ������ [�]
  unsigned int UhiI, UhiIsr, sumUhiI[50], kodUhiI, ptrUhiI; // UhiI - ���������� ������� �����. (��50) ���
  double dbUhiIsr; // ���������� ������� �����. (��50) [�]
  unsigned int SIM3; // ������������ �������� ��� (���)
  double dbSIM3; // ������������ �������� ��� [���.]
  unsigned int SIM4; // ������ ��� ���������� (���)
  double dbSIM4; // ������ ��� ���������� [���.]
  // ===
  unsigned int sim3;
  unsigned int sim4;
  // ===
  unsigned int SIM2; // ��� ���������� ������������ (���)
  unsigned int Ampl; // ������ ���������� (������ = 5) (���)
  double dbAmpl; // ������ ���������� (������ = 5) [�]
  int LEDAmpI, LEDAmpR, LEDAmpRcp, LEDAmp[200], kodLEDAmp, ptrLEDAmp;
  double dbLEDAmpRcp;
  unsigned int flagFirst;  // ���� ���������� ������ (�������� ������� 1)
  unsigned int flagSecond; // ���� ���������� ������ (�������� ������� 1)
  unsigned char MasRez[8]; // = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
  unsigned char PSW; // ����� ��������� ��������� ��
  unsigned int CountImp; // ���� � �� �� ������������� �������� (0,2 ������� ��� 0,25 ������� � ����������� �� ���������)
  unsigned int Sred02; // ������� � �� �� 0,2 �������
  unsigned int TSchet; // ������� ����� ����� ���������
  // ===
  unsigned int TSchetTemp;
  unsigned int TimeTSchet; // ������� ����� ������ (� ��������) �� ������ ��������� ����� (����������� �� "����� ���������" ������)
  unsigned int TimeTSchet_dia; // ��� ��������� ����: "������� ����� �����" ��� ����� ������
  bool bFlagCount; // ���� ���/���� ������ ����� ���������
  float Sred; // ������� � �� �� 0,2 �������
  // ===
  unsigned int SumSchet; // ��������� ����� ����� ���������
  unsigned int T_Limit; // ����� ����� ���������  

  unsigned int count; // ������� 200 ���. ����������
  unsigned int count2; // ������� 200 ���. ����������

  String Str_hex;
  char Str_err[250]; // ���� ���������� ��������������� ��������� �� ������

  bool flagGetVersion; // false - �� ���� �������� � ������� �����, true - �������� � ������� �����
  bool flagSetTimeInterval; // ---
  bool flagGetTimeInterval; // ---

  bool flagSetSpectrInterval;
  bool flagGetSpectrInterval;

  bool flagGetIndAdr; // ---
  bool flagGetGrpAdr; // ---
  bool bfSetTimeSpektr;

  unsigned long IndAdrZ; // �������������� ����� ��������
  unsigned long GrpAdrZ; // ��������� ����� ��������
  unsigned long DNUZ; // �������� �������������� ������� ������
  double dbDNUZ;
  unsigned long DVUZ; // �������� �������������� �������� ������
  double dbDVUZ;
  unsigned long LEDAmpZ; // ��� ���������� ��������
  unsigned long UhiZ; // ������������ ���� ��������
  unsigned long SIMstartZ; // ������ ��� ���������
  unsigned long SIMminZ; // ������ ��� �����������
  unsigned long LedZadZ; // �������� ������ ����������
  unsigned long m_ulSerialNumberZ; // �������� �����
  unsigned long m_ulUZ; // ���������� �����������
  unsigned long m_ulU0Z; // ��������� ���������� (��� ������� ������������ ���)
  // ===
  float m_fltU;
  unsigned int m_iU;
  float m_fltU0;
  unsigned int m_iU0;
  int period; // ������ (������������ � ������ ������� Avto)
  int dlitelnost; // ������������ ��������� ���

  int KolAuto; // ���������� �������� (������������ � ������ ������� Avto)
  int KolPopytok; // ���������� ������� (������������ � ������ ������� Avto)

  int shag; // ��� (������������ � ������ ������� Avto)
  int delta; // ������ (������������ � ������ ������� Avto)
  // ===
  double dbm_ulU0Z;
  double dbm_ulUZ;
  char m_strStickyNote[24+1]; // ���������� (��������� ������ ��� ������������ ����)
  char m_strStickyNote_temp[24+1]; // ���������� (��������� ������ ��� ������������ ����)
  // ===
  float m_fltDac0;
  unsigned int m_iDac0;
  float m_fltDac1;
  unsigned int m_iDac1;
  unsigned long DlInterPhon; // ������������ ��������� ����
  unsigned char KolTik;
  unsigned char KolTikSpectr;
  // ===

  int IP_Port;
  int Addr_BD_TCP; // ����� �� ��� ��������� ModBus TCP
  char IP_Addr[18]; // "192.168.3.4"
  bool bFlag_TCP_Connect;
  // 20.08.2015
  unsigned char ArrSpectrBlock[16];
  unsigned char ArrSpectr[512];
  int ArrSpectrSumm[512];
  int iSpektrZaprosCount; // ���������� ������� ������� ��������
  int TimeNaboraSpectr; // ����� ������ �������
  int TimeGotovSpectr; // ����� ���������� �������
  int iSpektrZaprosErr; // ���������� ������ ������ �������� (������)
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
  WORD Hour; // ���
  WORD Min; // ������
  WORD Sec; // �������
  WORD MSec; // �����������
  short PSW_b0;
  short PSW_b1;
  /////////////////////////////////////////////////////////////////////
  unsigned int flagFirst;  // ���� ���������� ������ (�������� ������� 1)
  unsigned int flagSecond; // ���� ���������� ������ (�������� ������� 1)
  int count;
  //int N0; // ���������� ��������� �������� ����� (PSW_b0 == 1)
  //int N1; // ���������� ��������� ��������� ����� (PSW_b1 == 1)
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
  int CodeRet; // ��� ���������� ������������ ���������

  //!unsigned char buf_write[16]; // ����� ��� ������
  //!unsigned char buf_read[16]; // ����� ��� ������
  unsigned char buf_write[32]; // ����� ��� ������
  unsigned char buf_read[32]; // ����� ��� ������

  unsigned char * pbuf_write; // ��������� �� ����� ������
  unsigned char * pbuf_read; // ��������� �� ����� ������

  //!unsigned char buf_write_modbus[16]; // ����� ��� ������ NastrBD
  //!unsigned char buf_read_modbus[16]; // ����� ��� ������ NastrBD
  unsigned char buf_write_modbus[32]; // ����� ��� ������ NastrBD
  unsigned char buf_read_modbus[32]; // ����� ��� ������ NastrBD
  unsigned short CRC;
  // ===
  bool FlagOpros; // ���� ��� ��������� ��������� ������ (������� �������/�������)
  bool FlagAutoOpros; // ���� ��� ��������� ��������� ������ (������� start/stop)

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
  bool bfPervVhod; // true - ������ ���� � ������� int OprosBDSpektr()
  void FlagAvtoSnyat(); // ����� ������� "����" (����������)
  void FlagAvtoSnyatDiskr(); // ����� ������� "����" (������ �������������)
//---------------------------------------------------------------------------
// ��������� ��������� ��� --> (U0 + Un == Uhi)
// ��� ��� --> (U0 * 0,81 + Un == Uhi)
  void AvtoPodborUhiIter(); // ���������� Uhi 
public:
  int AutoPodbor_1_Un_2_U81;
  int DiaGetTime(void); // ����� � ������������
  void ClearBDSpectr(void);
  void OprosSpectra(bool bf); // bf = true - ��������� ����� ������� � ������� OprosBD()
  int GetSSP(unsigned char * SSP);
  int GetCountImp(unsigned int * CImp);
  int GetVersia(unsigned char * Versia);
  int GetGrpAdr(unsigned char * Adr);
  int GetTemp(unsigned int * Temper);
  int GetDNU(unsigned int * DNU);
  int GetDVU(unsigned int * DVU);
  int GetUhi(unsigned int * UhiI);
  int GetSIM3(unsigned int * SIM); // ������� ������������ �������� ���
  int GetSIM4(unsigned int * SIM);
  int GetSIM2(unsigned int * SIM);
  int GetLEDAmp(unsigned int * Ampl);
  int GetLEDAmpR(int * AmplR);
  int GetTimeInterval(unsigned char * TimeInt);
  int GetStickyNote(char * strStickyNote);
  
  double Code2DAC( int var );
  double Code2U( int var );


  int Set_P37(void); // ���������� P3.7 (��������� ��������)
  int Reset_P37(void); // �������� P3.7 (������ ��������)

  int SpectrClear(void);
  int SpectrStart(void);
  int SpectrStop(void);
  int SpectrReadBuf(unsigned char Block, unsigned char Mas[16]);
  int SetTimeSpectr(unsigned char TimeInt);  // ��������� ������� ������ ������� KolTikSpectr
  int GetTimeSpectr(unsigned char * TimeInt); // ������ ������� ������ ������� KolTikSpectr
  int GetSpectrZaprosCount( void )
  {
    return this->Data.iSpektrZaprosCount; // ���������� ������� ������� ���������
  }
  int GetTimeNaboraSpectr( void )
  {
    return this->Data.TimeNaboraSpectr; // ����� ������ �������
  }
  int GetTimeGotovSpectr( void )
  {
    return this->Data.TimeGotovSpectr; // ����� ���������� �������
  }

    
  unsigned char SSP_Value; // ���������� ��� ��������� "������"

  /*unsigned*/ char err; // ������� ������� ReadFile ����������� � err
  unsigned char MB_length_to_read;
  
  int FlagDebug; // ���� �������

  // ===>> 17.07.2017
  //!bool flagModbusProtokol; // ���� ��������� false - "������", true - ModBusRTU (���� � ������ RSProtokol_t)
  int flagModbusProtokol; //! // ���� ��������� (���� � ������ RSProtokol_t)
  // 0 - "9-�� ������"
  // 1 - ModBus RTU
  // 2 - ModBus TCP
  // 3 - ModBus RTU (TCP/IP)
  // <<=== 17.07.2017

  // ������� flagFirstAddr 23.10.2014
  bool flagFirstAddr; // true - ��� ������ ��������� � �� ��� ��� ���� ��������
  bool flagSpeed; // ���� �������� ������, ��� ��������� "������" (true - ���� �������� ������)
  bool flagTCP;

  int testErr;
  unsigned char AddrBD;
  RSProtokol_t(); // �����������
  uint16_t crc16(uint8_t * buffer, uint16_t buffer_length);
  Time_t ArrTime[100], ArrTimeTek;
  unsigned short N0;
  unsigned short N1;
  int indexArrTime;
  int MaxIndexArrTime;
  // ===
  int OprosBD(void); // -1 - ������ �����, 0 - ����� ��������
  int OprosBDParam( void ); // -1 - ������ �����, 0 - ����� ��������


  // ������������ ��������: -1 - ������ �����, 0 - ����� ��������
  // ���������: iTimeRead - ����� ������ �������, iTimeGotovh - ����� ���������� �������
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
  int SetUhi(unsigned int Uhi); // ���������� ������������ ���
  int SetUhi2(unsigned int Uhi); // ���������� ������ ���
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

  void ClearReqRsp( uint8_t * Arr, int Length ); // �������� ������ (������� ��� ������)
  int CommandExec(unsigned char kOutByte, unsigned char kInByte);

  void NullsToStr_err(void); // ������� ������ ��������� �� �������
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

  /// ����� ���������� ������ ��� ����������� ���������������
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
      (int BDAddr, // ����� ��
      int REGAddr, // ����� ��������
      int nb, // ���������� ���������
      uint16_t * dest // ������
  );
  int write_registers
      (int BDAddr, // ����� ��
      int REGAddr, // ����� ��������
      int nb, // ���������� ���������
      uint16_t * src // ������ 
  );
  int IncFreqLEDImp(unsigned char State); // ���������� ������� ��������� �� ����������
  int SpectrCon(unsigned char State); // ���������� ������� ������� �������� 1-������, 0-�����������
  int ARCHCon(unsigned char State); // ���������� �������� ��� 0-��������, 1-���������

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

  // ������ ��� ����������
  const unsigned int m_nPwmCycleTimeMin;
  const unsigned int m_nPwmCycleTimeMax;
  // ������������ ��������� ���
  const unsigned int m_nPwmPulseLengthMin;
  const unsigned int m_nPwmPulseLengthMax;

  const unsigned int m_nPwmCycleTimeOffset;
  const unsigned int m_nPwmPulseLengOffset;

  bool CheckBox_auto_Checked; // = true, ���� ������ CheckBox_auto ����������
  bool CheckBox_DAuto_Checked; // = true, ���� ������ CheckBox_DAuto ����������
  void Set_CheckBox_DAuto_Checked(bool dNu, bool dVu); // 2018.03.19
  int auto_State_Flag;

  Data_t Data; // ������ ��� ������ �� �����
  int ErrorCode;
  int ReturnVar; // ��� OprosBD ������� �����
  char Str_err[250 * 2]; // ���� ���������� ��������������� ��������� �� ������

  int flagARCH; // ���� ��� (�������������� ����������� ����������������)
  int flagUchSv; // ���� �������� ����������
  //bool bf_ARH_UchSv;

  bool newProsivka; // = true - ��� �������� ����, ��� �������� ��������
  // ����� - ���� �������� ���, �������� �������� SPACEPARITY

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

  // ��� ��������  ������ � EEPROM
  float k1PR;
  float A1PR;
  float k2PR;
  float A2PR;
  unsigned long Longk1PR;
  unsigned long LongA1PR;
  unsigned long Longk2PR;
  unsigned long LongA2PR;
  int MasSvetoPR[256];

  bool bFlagWork; // ���� ������ ��������� �������/��������

  // ���������� ������������� (������ �� ����������� �������),
  // ������� ����� �������, ����� �������� ���� �� �������
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
