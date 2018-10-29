//---------------------------------------------------------------------------
#ifndef Unit_FunktionH
#define Unit_FunktionH

#include <Classes.hpp>
#include "Unit_DataBD.h"

typedef unsigned char uint8_t; // �������� ���������� �����
typedef unsigned short uint16_t;

// ���������� ���������� ��������� ���-������
// � ������� ComPorts �������� ������ ��������� ���-������
// ���� ��������������� ������� ������� ����� "true"
// ����� ����� ���� � ������ ComPorts[0] --- COM1, ... ComPorts[31] --- COM32
//---------------------------------------------------------------------------
int DIA_UpdateCom(bool ComPorts[32]);

class NastrCom_t
{
public:
  TDCB lpDCB;
  TCommTimeouts lpCommTimeouts;
};

class RSProtokol_t
{
public:
  // ������
  unsigned char AddrBD;
  bool flagModbusProtokol; // ���� ��������� false - "9 ������", true - ModBus RTU
  bool flagFirstAddr; // true - ��� ������ ��������� � �� ��� ��� ���� ��������  

  // �������
  int GetIndAdr(unsigned char * Adr);
  int GetGrpAdr(unsigned char * Adr);
  int GetVersia(unsigned char * Versia);
  int GetDNU(unsigned int * DNU);
  int GetDVU(unsigned int * DVU);

  int SetDNU(unsigned int DNUZ);
  int SetDVU(unsigned int DVUZ);

  RSProtokol_t(); // ����������� 
  int RSConnect(const char * device, int baud, int parity, int data_bit, int stop_bit);
  int RSConnect(const char * device);
  int RSDisConnect(void);
  int CommandExec(unsigned char kOutByte, unsigned char kInByte);
  int WriteToPort(const unsigned char * buf, int count, int parity);
  int ReadFromPort(unsigned char * buf, int count, int parity);
  // ���������� ����� ������ �� FLASH/EE DATA MEMORY ����������
  int ReadFlashInvert(unsigned int Adr, unsigned long * Data);
  // ���������� ����� ������ �� FLASH/EE DATA MEMORY ����������
  int ReadFlash(unsigned int Adr, unsigned long * Data);
  // ���������� ����� ������ �� FLASH/EE DATA MEMORY ����������
  int ReadFlash2(unsigned int Adr, unsigned long * Data);
  // ������� ����� ��������� ��������� ��
  int GetSSP(unsigned char * SSP);

  int ReadBD( DataBD9Bit_t * Data );
  int ExRead( int NomerParametra, void * Value );

private:

  int Count;

  HANDLE COMPort;
  int ErrorCode; // ��� ������  

  
  NastrCom_t forUse;
  NastrCom_t forSave;

  bool flagPort; // ��������� ����� ������ (true)/������ (false)
  unsigned char buf_write[16]; // ����� ��� ������
  unsigned char buf_read[16]; // ����� ��� ������
  unsigned char * pbuf_write; // ��������� �� ����� ������
  unsigned char * pbuf_read; // ��������� �� ����� ������
  char cDisplayReportc_Write[255]; // ���������� � MemoMain ������������ �������
  char * pcDR_Wr;
  char cDisplayReportc_Read[255]; // ���������� � MemoMain �������� �������
  char * pcDR_Rd;
  unsigned char buf_write_modbus[16]; // ����� ��� ������ NastrBD
  unsigned char buf_read_modbus[16]; // ����� ��� ������ NastrBD
  uint16_t CRC;

  int CodeRet; // ��� ���������� ������������ ���������
  char DEVID[16];
  int ret_size;
    
  int baud; // �������� ������ ������� �� ���-�����
  int data_bit; // ��� � �����
  int stop_bit; // ���� ���
  int parity; // ��������

  int strlcpy(char * dest, const char * src, int dest_size);
  void Reset(void);

  int ReadIntervalTimeout; // ����������� ���������� �������� ����� �������� ���� ��������
  int ReadTotalTimeoutMultiplier; // ����. ��� ������� ����������� ����������� ������� ������ �������
  int ReadTotalTimeoutConstant; // ����. ��� ������� ����������� ����������� ������� ������ �������
  int WriteTotalTimeoutMultiplier; // ����. ��� ������� ����������� ����������� ������� ������ �������
  int WriteTotalTimeoutConstant; // ����. ��� ������� ����������� ����������� ������� ������ �������

  uint16_t crc16(uint8_t * buffer, uint16_t buffer_length);
};



//---------------------------------------------------------------------------
#endif
