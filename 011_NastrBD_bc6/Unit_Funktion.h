//---------------------------------------------------------------------------
#ifndef Unit_FunktionH
#define Unit_FunktionH

#include <Classes.hpp>
#include "Unit_DataBD.h"

typedef unsigned char uint8_t; // создание псевдонима имени
typedef unsigned short uint16_t;

// Возвращает количество доступных КОМ-портов
// В массиве ComPorts хранятся номера доступных КОМ-портов
// Если соответствующий элемент массива равен "true"
// номер порта есть в списке ComPorts[0] --- COM1, ... ComPorts[31] --- COM32
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
  // Данные
  unsigned char AddrBD;
  bool flagModbusProtokol; // Флаг протокола false - "9 битный", true - ModBus RTU
  bool flagFirstAddr; // true - при первом обращении к БД или при сбое передачи  

  // Функции
  int GetIndAdr(unsigned char * Adr);
  int GetGrpAdr(unsigned char * Adr);
  int GetVersia(unsigned char * Versia);
  int GetDNU(unsigned int * DNU);
  int GetDVU(unsigned int * DVU);

  int SetDNU(unsigned int DNUZ);
  int SetDVU(unsigned int DVUZ);

  RSProtokol_t(); // Конструктор 
  int RSConnect(const char * device, int baud, int parity, int data_bit, int stop_bit);
  int RSConnect(const char * device);
  int RSDisConnect(void);
  int CommandExec(unsigned char kOutByte, unsigned char kInByte);
  int WriteToPort(const unsigned char * buf, int count, int parity);
  int ReadFromPort(unsigned char * buf, int count, int parity);
  // Считывание байта данных из FLASH/EE DATA MEMORY процессора
  int ReadFlashInvert(unsigned int Adr, unsigned long * Data);
  // Считывание байта данных из FLASH/EE DATA MEMORY процессора
  int ReadFlash(unsigned int Adr, unsigned long * Data);
  // Считывание байта данных из FLASH/EE DATA MEMORY процессора
  int ReadFlash2(unsigned int Adr, unsigned long * Data);
  // Считать слово состояния программы БД
  int GetSSP(unsigned char * SSP);

  int ReadBD( DataBD9Bit_t * Data );
  int ExRead( int NomerParametra, void * Value );

private:

  int Count;

  HANDLE COMPort;
  int ErrorCode; // Код ошибки  

  
  NastrCom_t forUse;
  NastrCom_t forSave;

  bool flagPort; // Состояние порта Открыт (true)/закрыт (false)
  unsigned char buf_write[16]; // Буфер для чтения
  unsigned char buf_read[16]; // Буфер для записи
  unsigned char * pbuf_write; // Указатель на буфер чтения
  unsigned char * pbuf_read; // Указатель на буфер записи
  char cDisplayReportc_Write[255]; // Отображать в MemoMain отправленную посылку
  char * pcDR_Wr;
  char cDisplayReportc_Read[255]; // Отображать в MemoMain принятую посылку
  char * pcDR_Rd;
  unsigned char buf_write_modbus[16]; // Буфер для чтения NastrBD
  unsigned char buf_read_modbus[16]; // Буфер для записи NastrBD
  uint16_t CRC;

  int CodeRet; // Эта переменная возвращается функциями
  char DEVID[16];
  int ret_size;
    
  int baud; // Скорость обмена данными по ком-порту
  int data_bit; // Бит в байте
  int stop_bit; // Стоп бит
  int parity; // Четность

  int strlcpy(char * dest, const char * src, int dest_size);
  void Reset(void);

  int ReadIntervalTimeout; // Максимально допустимый интервал между стартами двух символов
  int ReadTotalTimeoutMultiplier; // Коэф. для расчёта максимально допустимого времени чтения посылки
  int ReadTotalTimeoutConstant; // Коэф. для расчёта максимально допустимого времени чтения посылки
  int WriteTotalTimeoutMultiplier; // Коэф. для расчёта максимально допустимого времени записи посылки
  int WriteTotalTimeoutConstant; // Коэф. для расчёта максимально допустимого времени записи посылки

  uint16_t crc16(uint8_t * buffer, uint16_t buffer_length);
};



//---------------------------------------------------------------------------
#endif
