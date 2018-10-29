//---------------------------------------------------------------------------
#pragma hdrstop
#include "Unit_Funktion.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

// ���������� ���������� ��������� ���-������
// � ������� ComPorts �������� ������ ��������� ���-������
// ���� ��������������� ������� ������� ����� "true"
// ����� ����� ���� � ������ ComPorts[0] --- COM1, ... ComPorts[31] --- COM32
//---------------------------------------------------------------------------
int DIA_UpdateCom(bool ComPorts[32])
{
  int i;
  int j;
  AnsiString AnsiStr = "";
  HANDLE port;

  for ( i = 0; i < 32; i++ )
  {
    ComPorts[i] = false;
  }
  j = 0;
  for ( i = 1; i < 33; i++ )
  {
    SetLastError(0);
    AnsiStr = "\\\\.\\COM" + IntToStr(i);
    port = CreateFileA(
        AnsiStr.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0, NULL, OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
    if ( port != INVALID_HANDLE_VALUE )
    {
      j++;
      ComPorts[i - 1] = true;
      CloseHandle( port );
    }
  }
  return j;
}
//---------------------------------------------------------------------------
// ������� CRC ��� ������� ��������
static const uint8_t table_crc_hi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
};
//---------------------------------------------------------------------------
// ������� CRC ��� ������� ��������
static const uint8_t table_crc_lo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
    0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
    0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
    0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
    0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
    0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
    0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
    0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
    0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
    0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
    0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
    0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
    0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
    0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
    0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
    0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
    0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
    0x43, 0x83, 0x41, 0x81, 0x80, 0x40
};
//---------------------------------------------------------------------------
RSProtokol_t::RSProtokol_t()
    : flagModbusProtokol( true ), // ����� ���������
    flagFirstAddr ( true ), // ��� ����� ������ � ��������� "������"
    pbuf_read ( & buf_read [0] ), // ��������� ����������������
    pbuf_write ( & buf_write [0] ), // ��������� ����������������
    pcDR_Wr ( & cDisplayReportc_Write [0] ), // ��������� ����������������
    pcDR_Rd ( & cDisplayReportc_Read [0] ) // ��������� ����������������
{
  this->flagPort = false;
  this->ReadIntervalTimeout = 0; // ����������� ���������� �������� ����� �������� ���� ��������
  this->ReadTotalTimeoutMultiplier = 0; // ����. ��� ������� ����������� ����������� ������� ������ �������
  this->ReadTotalTimeoutConstant = 100; // ����. ��� ������� ����������� ����������� ������� ������ �������
  this->WriteTotalTimeoutMultiplier = 0; // ����. ��� ������� ����������� ����������� ������� ������ �������
  this->WriteTotalTimeoutConstant = 100; // ����. ��� ������� ����������� ����������� ������� ������ �������
}
//---------------------------------------------------------------------------
int RSProtokol_t::RSDisConnect(void)
{
  int Ret = 0;
  if ( this->COMPort == 0 )
  {
    ErrorCode = 7; // ��� ������ 7 - ���� ��� ������
    Ret = -1;
  }
  if( SetCommState(this->COMPort, &this->forSave.lpDCB) == false )
  {
    CloseHandle( this->COMPort );
    this->COMPort = 0;
    ErrorCode = 8; // ��� ������ 8 - �� ������� ���������� TDCB ��� �������� �����
    Ret = -1;
  }
  if ( SetCommTimeouts(this->COMPort, &forSave.lpCommTimeouts) == false )
  {
    CloseHandle(this->COMPort);
    this->COMPort = 0;
    ErrorCode = 9; // ��� ������ 9 - �� ������� ���������� TCommTimeouts ��� �������� �����
    Ret = -1;
  }
  CloseHandle( this->COMPort );
  this->COMPort = 0;
  return Ret;
}
//---------------------------------------------------------------------------
int RSProtokol_t::RSConnect(const char * device)
{
  if ( flagModbusProtokol == false ) // ������ �������� "9-�� ������"
  {
    this->ErrorCode = RSConnect(
	device, // device
	115200, // baud
	MARKPARITY, // parity
	8, // data_bit
	ONESTOPBIT); // stop_bit
  }
  else // ������ �������� "ModBus RTU"
  {
    this->parity = NOPARITY;
    this->stop_bit = TWOSTOPBITS;
    this->ErrorCode = RSConnect(
        device, // device
	57600, // baud
	this->parity, // parity (SPACEPARITY; NOPARITY)
	8, // data_bit
	this->stop_bit); // stop_bit (ONESTOPBIT; TWOSTOPBITS)
  }
  if ( COMPort == 0 )
  {
    flagPort = false; // ��������� ����� ������ (true)/������ (false)
  }
  else
  {
    flagPort = true; // ��������� ����� ������ (true)/������ (false)
  }
  return this->ErrorCode;
}
//---------------------------------------------------------------------------
int RSProtokol_t::RSConnect(const char * COMNum, int baud, int parity, int data_bit, int stop_bit)
{
  int dest_size;
  dest_size = sizeof(this->DEVID) / sizeof(this->DEVID[0]);
  this->ret_size = strlcpy(this->DEVID, COMNum, dest_size);
  this->baud = baud;
  this->parity = parity;
  this->data_bit = data_bit;
  this->stop_bit = stop_bit;
  this->ErrorCode = 0;
  this->pbuf_read = this->buf_read;
  this->pbuf_write = this->buf_write;
  this->Count = 0;

  Reset();

  if (this->COMPort == 0) // �� ���� ���-���� ��� �� ������, ��� �������� ���-���� ��� ������
  {
    this->COMPort = CreateFile
        (this->DEVID, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, NULL, 0);
  }
  else
  {
    ErrorCode = 1; // ��� ������ 1 - ���� ��� ������
    return -1;
  }
  // ===
  if ( this->COMPort == INVALID_HANDLE_VALUE )
  {
    ErrorCode = 2; // ��� ������ 2 - ���� �� ��������
    this->COMPort = 0;
    return -1;
  }
  if( GetCommState(this->COMPort, &this->forSave.lpDCB) == false )
  {
    ErrorCode = 3; // ��� ������ 3 - �� ������� ������� TDCB
    return -1;
  }
  if ( GetCommTimeouts(this->COMPort, &this->forSave.lpCommTimeouts) == false )
  {
    ErrorCode = 4; // ��� ������ 4 - �� ������� ������� TCommTimeouts
    return -1;
  }
  this->forUse = this->forSave;
  //
  this->forUse.lpDCB.BaudRate = this->baud;
  this->forUse.lpDCB.ByteSize = this->data_bit;
  this->forUse.lpDCB.Parity = this->parity;
  this->forUse.lpDCB.StopBits = this->stop_bit;
  this->forUse.lpDCB.DCBlength = sizeof(TDCB);
  //
  if (this->forUse.lpDCB.Parity == NOPARITY)
  {
    this->forUse.lpDCB.fParity = FALSE;
  }
  else
  {
    this->forUse.lpDCB.fParity = TRUE;
  }

  this->forUse.lpDCB.fTXContinueOnXoff = TRUE;
  this->forUse.lpDCB.fOutX = FALSE;
  this->forUse.lpDCB.fInX = FALSE;
  // �������� �����
  this->forUse.lpDCB.fBinary = TRUE;
  // �� ��������� ��������� ���� �������� ������/������ ��� ������
  this->forUse.lpDCB.fAbortOnError = FALSE;

  this->forUse.lpDCB.fNull = false; // ������� ����� �� �������������
  // ===
  this->forUse.lpDCB.fAbortOnError = FALSE;  // TRUE - ������� ���������� ��� �������� � ������ ������
  // true - �������� �������� ModBus �������� �� ������ ���-������

  this->forUse.lpDCB.fErrorChar = false;
  //==\\this->forUse.lpDCB.fDsrSensitivity = FALSE; // ��������� ��������������� �������� � ��������� ����� DSR
  // ������ �������� � ��������� ��������� �� ������ ���������� ErrorChar
  this->forUse.lpDCB.ErrorChar = 0;
  this->forUse.lpDCB.fDtrControl = DTR_CONTROL_DISABLE;
  this->forUse.lpDCB.fRtsControl = RTS_CONTROL_DISABLE;

  // ����������� ���������� �������� ����� �������� ���� ��������
  this->forUse.lpCommTimeouts.ReadIntervalTimeout = this->ReadIntervalTimeout;
  // ����. ��� ������� ����������� ����������� ������� ������ �������
  this->forUse.lpCommTimeouts.ReadTotalTimeoutMultiplier = this->ReadTotalTimeoutMultiplier;
  // ����. ��� ������� ����������� ����������� ������� ������ �������
  this->forUse.lpCommTimeouts.ReadTotalTimeoutConstant = this->ReadTotalTimeoutConstant;
   // ����. ��� ������� ����������� ����������� ������� ������ �������
  this->forUse.lpCommTimeouts.WriteTotalTimeoutMultiplier = this->WriteTotalTimeoutMultiplier;
  // ����. ��� ������� ����������� ����������� ������� ������ �������
  this->forUse.lpCommTimeouts.WriteTotalTimeoutConstant = this->WriteTotalTimeoutConstant;

  if(SetCommState(this->COMPort, &this->forUse.lpDCB) == false)
  {
    ErrorCode = 5; // ��� ������ 5 - �� ������� ���������� TDCB
    return -1;
  }
  if (SetCommTimeouts(this->COMPort, &this->forUse.lpCommTimeouts) == false)
  {
    ErrorCode = 6; // ��� ������ 6 - �� ������� ���������� TCommTimeouts
    return -1;
  }
  // ������ ����� ������/������
  if( PurgeComm( this->COMPort, PURGE_TXCLEAR | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_RXABORT) == 0 )
  {
    ErrorCode = 16;  // ��� ������ 16 - ������� �����/�������� (RSConnect)
    return -1;
  }
  return 0;
}
//---------------------------------------------------------------------------
int RSProtokol_t::strlcpy(char * dest, const char * src, int dest_size)
{
  char * d;
  const char * s;
  d = dest;
  s = src;
  int n = dest_size;

  if ( n != 0 && --n != 0)
  {
    do
    {
      if ( (*d++ = *s++) == 0 )
      {
    	break;
      }
    } while ( --n != 0 );
  }

  if (n == 0)
  {
    if (dest_size != 0)
    {
      *d = '\0';
    }
    while ( *s++ )
    {
      ;
    }
  }
  return (s - src - 1);
}
//---------------------------------------------------------------------------
void RSProtokol_t::Reset(void)
{
  ;
}
//---------------------------------------------------------------------------
int RSProtokol_t::CommandExec(unsigned char kOutByte, unsigned char kInByte)
{
  unsigned char Addr;
  Addr = this->AddrBD; // ����� �� (63 - ��� ��������� "������" �� ���������)
  // ===
  if (this->flagModbusProtokol == false)
  {
    if ( this->flagFirstAddr == true )
    {
      this->flagFirstAddr = false;
      WriteToPort( &Addr, 1, MARKPARITY );
      this->Count = ReadFromPort( this->pbuf_read, 1, MARKPARITY );
      if ( this->Count != 1 )
      {
        ErrorCode = 16;  // ��� ������ 16 - ����� �������� ���� �� ������������� ���������� (CommandExec)
        this->flagFirstAddr = true;
        return -1;
      }
    }
    WriteToPort(this->pbuf_write, kOutByte + 1, SPACEPARITY);
    this->Count = ReadFromPort( this->pbuf_read, kInByte, SPACEPARITY );
    if ( this->Count != kInByte )
    {
      ErrorCode = 17;  // ��� ������ 17 - ����� �������� ���� �� ������������� ���������� (CommandExec)
      // ===
      this->flagFirstAddr = true;
      // ===
      return -1;
    }
  }
  else // if (flagModbusProtokol == true)
  {
    for ( int i = 0; i < 255; i++ )
    {
      cDisplayReportc_Write[0] = 0;
      cDisplayReportc_Read[0] = 0;
    }
    int Index = 0;
    buf_write_modbus[Index++] = this->AddrBD;
    buf_write_modbus[Index++] = 65; // ��� �������
    for (int i = 0; i <= kOutByte; i++)
    {
      buf_write_modbus[Index++] = pbuf_write[i];
    }
    CRC = crc16( &buf_write_modbus[0], Index);
    buf_write_modbus[Index++] = CRC >> 8;
    buf_write_modbus[Index++] = CRC;
    //===>> 26.09.2014
    //pcDR_Wr = &cDisplayReportc_Write[0];
    //for ( int i = 0, len = 0; i < Index; i++ )
    //{
    //  len = sprintf( pcDR_Wr, "%.02X ", buf_write_modbus[i] );
    //  pcDR_Wr += len;
    //}
    //<<=== 26.09.2014
    WriteToPort(this->buf_write_modbus, Index, this->parity);
    this->Count = ReadFromPort(this->buf_read_modbus, 3, this->parity);
    //===>> 26.09.2014
    //pcDR_Rd = &cDisplayReportc_Read[0];
    //for ( int i = 0, len = 0; i < this->Count; i++ )
    //{
    //  len = sprintf( pcDR_Rd, "%.02X ", buf_read_modbus[i] );
    //  pcDR_Rd += len;
    //}
    //<<=== 26.09.2014
    if (this->Count != 3)
    {
      ErrorCode = 18;  // ��� ������ 18 - ����� �������� ���� �� ������������� ���������� (CommandExec)
      return -1; // ������: �� ��������� ������ ��� �����
    }
    if (buf_read_modbus[1-1] != this->AddrBD)
    {
      ErrorCode = 19;  // ��� ������ 19 - �������� ���� �� �������� ������� �� (CommandExec)
      return -1;
    }
    if (buf_read_modbus[2-1] != 65)
    {
      ErrorCode = 20;  // ��� ������ 20 -  �������� ���� �� �������� ����� ������� 65 (CommandExec)
      return -1;
    }
    this->Count = ReadFromPort(&this->buf_read_modbus[3], kInByte + 2, this->parity);
    //===>> 26.09.2014
    //for ( int i = 0, len = 0; i < this->Count; i++ )
    //{
    //  len = sprintf( pcDR_Rd, "%.02X ", buf_read_modbus[3+i] );
    //  pcDR_Rd += len;
    //}
    //<<=== 26.09.2014
    if (this->Count != kInByte + 2)
    {
      ErrorCode = 21;  // ��� ������ 21 - �� ��������� ��������� ����� ������� (CommandExec)
      return -1;
    }
    CRC = crc16( &buf_read_modbus[0], 3 + kInByte + 2 );
    if (CRC != 0)
    {
      ErrorCode = 22;  // ��� ������ 22 - CRC �� �������� ������� �� ����� ���� (CommandExec)
      return -1;
    }
    for ( int i = 0; i < kInByte; i++ )
    {
      pbuf_read[i] = buf_read_modbus[3+i];
    }
  }
  return 0;
}
//---------------------------------------------------------------------------
// ���������� ����� ������ �� FLASH/EE DATA MEMORY ����������
int RSProtokol_t::ReadFlashInvert(unsigned int Adr, unsigned long * Data)
{
  // ===>>
  union {
   unsigned long tData;
   unsigned char eMas[4];
  } indata;
  // <<===
  buf_write[0] = 0x02;
  buf_write[1] = Adr & 0x00FF;
  buf_write[2] = (Adr >> 8) & 0x0003;
  this->CodeRet = CommandExec(2, 4);
  indata.eMas[0] = (~buf_read[0]);
  indata.eMas[1] = (~buf_read[1]);
  indata.eMas[2] = (~buf_read[2]);
  indata.eMas[3] = (~buf_read[3]);
  *Data = indata.tData;
  return CodeRet;
}
//---------------------------------------------------------------------------
// ���������� ����� ������ �� FLASH/EE DATA MEMORY ����������
int RSProtokol_t::ReadFlash(unsigned int Adr, unsigned long * Data)
{
  // ===>>
  union {
    unsigned long tData;
    unsigned char eMas[4];
  } indata;
  // ===>>
  buf_write[0] = 0x02;
  buf_write[1] = Adr & 0x00FF;
  buf_write[2] = (Adr >> 8) & 0x0003;
  CodeRet = CommandExec(2, 4);
  indata.eMas[0] = (buf_read[0]);
  indata.eMas[1] = (buf_read[1]);
  indata.eMas[2] = (buf_read[2]);
  indata.eMas[3] = (buf_read[3]);
  *Data = indata.tData;
  return CodeRet;
}
//---------------------------------------------------------------------------
int RSProtokol_t::ReadFlash2(unsigned int Adr, unsigned long * Data)
{
  // ===>>
  union {
    unsigned long tData;
    unsigned char eMas[4];
  } indata;
  // ===>>
  buf_write[0] = 0x02;
  buf_write[1] = Adr & 0x00FF;
  buf_write[2] = (Adr >> 8) & 0x0003;
  CodeRet = CommandExec(2, 4);
  indata.eMas[0] = (buf_read[3]);
  indata.eMas[1] = (buf_read[2]);
  indata.eMas[2] = (buf_read[1]);
  indata.eMas[3] = (buf_read[0]);
  *Data = indata.tData;
  return CodeRet;
}
//---------------------------------------------------------------------------
// ������� ����� ��������� ��������� ��
int RSProtokol_t::GetSSP(unsigned char * SSP)
{
  this->buf_write[0] = 0x09;
  this->CodeRet = CommandExec(0, 1);
  if (this->CodeRet == 0) // ��� ������ ������
  {
    *SSP = this->buf_read[0];
  }
  else // ������ ������
  {
    *SSP = 0;
  }
  return this->CodeRet;
}
//---------------------------------------------------------------------------
int RSProtokol_t::WriteToPort(const unsigned char * buf, int count, int parity)
{
  DWORD wb;
  if (this->COMPort == 0)
  {
    ErrorCode = 10; // ��� ������ 10 - ���� ������ (WriteToPort)
    return -1;
  }
  if (this->parity != parity)
  {
    this->parity = parity;
    this->forUse.lpDCB.Parity = this->parity;
    if(SetCommState(this->COMPort, &this->forUse.lpDCB) == false)
    {
      ErrorCode = 11; // ��� ������ 11 - �� ������� ���������� TDCB
      return -1;
    }
  }
  if ( WriteFile(this->COMPort, buf, count, &wb, NULL ) == false)
  {
    ErrorCode = 12;  // ��� ������ 12 - �� ������� ����������� ������ � ����
    return -1;
  }
  return (int)wb;
}
//---------------------------------------------------------------------------
int RSProtokol_t::ReadFromPort(unsigned char * buf, int count, int parity)
{
  DWORD rb;
  if (this->COMPort == 0)
  {
    ErrorCode = 13; // ��� ������ 13 - ���� ������ (ReadFromPort)
    return -1;
  }
  if (this->parity != parity)
  {
    this->parity = parity;
    this->forUse.lpDCB.Parity = this->parity;
    if(SetCommState(this->COMPort, &this->forUse.lpDCB) == false)
    {
      ErrorCode = 14; // ��� ������ 14 - �� ������� ���������� TDCB
      return -1;
    }
  }
  if ( ReadFile(this->COMPort, buf, count, &rb, NULL) == false)
  {
    ErrorCode = 15;  // ��� ������ 15 - �� ������� ����������� ������ �� ����
    return -1;
  }
  return (int)rb;
}
//---------------------------------------------------------------------------
uint16_t RSProtokol_t::crc16(uint8_t * buffer, uint16_t buffer_length)
{
  uint8_t crc_hi = 0xFF; // ������� ����/������ CRC
  uint8_t crc_lo = 0xFF; // ������� ����/������ CRC
  unsigned int i;
  while (buffer_length--)
  {
    i = crc_hi ^ *buffer++;
    crc_hi = crc_lo ^ table_crc_hi[i];
    crc_lo = table_crc_lo[i];
  }
  return (crc_hi << 8 | crc_lo);
}
//---------------------------------------------------------------------------
// ������� ������ �� �� ��
int RSProtokol_t::GetVersia(unsigned char * Versia)
{
  int i;
  this->buf_write[0] = 0x1f;
  this->CodeRet = CommandExec(0, 4);
  if (this->CodeRet == 0) // ��� ������ ������
  {
    for( i = 0; i < 4; i++ )
    {
      Versia[i] = this->buf_read[i];
    }
  }
  else // ������ ������
  {
    for( i = 0; i < 4; i++ )
    {
      Versia[i] = '-';
    }
  }
  Versia[i] = '\0';
  return this->CodeRet;
}
//---------------------------------------------------------------------------
// ������� ���������� �� ������ �������������� ������� ������
int RSProtokol_t::GetDNU(unsigned int * DNU)
{
  unsigned int data;
  this->buf_write[0] = 0x17;
  this->CodeRet = CommandExec(0, 2);
  if (this->CodeRet == 0) // ��� ������ ������
  {
    data = this->buf_read[1]&0x0F;
    *DNU = data * 256 + this->buf_read[0];
  }
  else // ������ ������
  {
    *DNU = 0;
  }
  return this->CodeRet;
}
//---------------------------------------------------------------------------
// ������� ���������� �� ������ �������������� �������� ������
int RSProtokol_t::GetDVU(unsigned int * DVU)
{
  unsigned int data;
  this->buf_write[0] = 0x18;
  this->CodeRet = CommandExec(0, 2);
  if (this->CodeRet == 0) // ��� ������ ������
  {
    data = this->buf_read[1] & 0x0F;
    *DVU = data * 256 + this->buf_read[0];
  }
  else // ������ ������
  {
    *DVU = 0;
  }
  return this->CodeRet;
}
//---------------------------------------------------------------------------
// ������� �������������� ����� ��
int RSProtokol_t::GetIndAdr(unsigned char * Adr)
{
  this->buf_write[0] = 0x14;
  this->CodeRet = CommandExec(0, 1);
  if (this->CodeRet == 0) // ��� ������ ������
  {
    *Adr = this->buf_read[0];
  }
  else // ������ ������
  {
    *Adr = '\0';
  }
  return this->CodeRet;
}
//---------------------------------------------------------------------------
// ������� ��������� ����� ��
int RSProtokol_t::GetGrpAdr(unsigned char * Adr)
{
  this->buf_write[0] = 0x16;
  this->CodeRet = CommandExec(0, 1);
  if (this->CodeRet == 0) // ��� ������ ������
  {
    *Adr = this->buf_read[0];
  }
  else // ������ ������
  {
    *Adr = '\0';
  }
  return this->CodeRet;
}
//---------------------------------------------------------------------------
// ���������� ����� ������������� ������� ������
int RSProtokol_t::SetDNU(unsigned int DNUZ)
{
  this->buf_write[0] = 0x0B;
  this->buf_write[1] = 184;
  this->buf_write[2] = 112;
  this->buf_write[3] = 235;
  this->buf_write[4] = DNUZ;
  this->buf_write[5] = (DNUZ >> 8) & 0x0F;
  this->CodeRet = CommandExec(5, 1);
  return this->CodeRet;
}
//---------------------------------------------------------------------------
// ���������� ����� ������������� �������� ������
int RSProtokol_t::SetDVU(unsigned int DVUZ)
{
  this->buf_write[0] = 0x0C;
  this->buf_write[1] = 184;
  this->buf_write[2] = 112;
  this->buf_write[3] = 235;
  this->buf_write[4] = DVUZ;
  this->buf_write[5] = (DVUZ >> 8) & 0x0F;
  this->CodeRet = CommandExec(5, 1);
  return this->CodeRet;
}
//---------------------------------------------------------------------------
int RSProtokol_t::ReadBD( DataBD9Bit_t * Data )
{
  int RetVal;
  int Count = 0;
  for ( int i = 0; i < Data->Length; i++ )
  {
    Count++;
    RetVal = ExRead( i, Data->ptr_Param[i] );
    Data->Uspeh[i] = false;
    if ( RetVal == 0 )
    {
      Data->Uspeh[i] = true;
    }
  }
  if ( Count < 28 )
  {
    return -1;
  }
  return 0;
}
//---------------------------------------------------------------------------
int RSProtokol_t::ExRead( int NomerParametra, void * Value )
{
  int RetVal = 0;
  unsigned long tmp;
  switch( NomerParametra )
  {
  case 0 : // 1) ������ ��������
    RetVal = GetVersia( (unsigned char *)Value );
    break;
  case 1 : // 2) ����� ��������� ��������� ��
    RetVal = GetSSP( (unsigned char *)Value );
    break;
  case 2 : // 3) �������������� ����� ��������
    if ( flagModbusProtokol == false )
    {
      RetVal = ReadFlashInvert( 0x04, (unsigned long *)Value );
    }
    else
    {
      RetVal = ReadFlash2( 0x300 + 1, (unsigned long *)Value );
    }
    break;
  case 3 : // 4) ��������� ����� ��������
    RetVal = ReadFlashInvert( 0x05, (unsigned long *)Value );
    break;
  case 4 : // 5) �������� �������������� ������� ������ ��������
    RetVal = ReadFlashInvert( 0, (unsigned long *)Value );
    break;
  case 5 : // 6) �������� �������������� �������� ������ ��������
    RetVal = ReadFlashInvert( 1, (unsigned long *)Value );
    break;
  case 6 : // 7) ��� ���������� ��������
    RetVal = ReadFlashInvert( 0x02, (unsigned long *)Value );
    break;
  case 7 : // 8) ������������ ��������� ���� ��������
    RetVal = ReadFlashInvert( 0x03, (unsigned long *)Value );
    break;
  case 8 : // 9) ������ ��� ��������� ��������
    RetVal = ReadFlashInvert( 0x07, (unsigned long *)Value );
    break;
  case 9 : // 10) ������ ��� ����������� ��������
    RetVal = ReadFlashInvert( 0x09, (unsigned long *)Value );
    break;
  case 10 : // 11) ������ ���������� ��������
    RetVal = ReadFlash( 0x2B, (unsigned long *)Value );
    (*(unsigned long *)Value) &= 0x000000FF;
    //tmp = *(unsigned long *)Value;
    //tmp &= 0x000000FF;
    //(*(unsigned long *)Value) = tmp;
    break;
  case 11 : // 12) �������� �����
    RetVal = ReadFlashInvert( 0x0A, (unsigned long *)Value );
    break;
  case 12 : // 13) ���������� ��� ������� ������������ ��� ��������
    break;
  case 13 : // 14) ���������� ����������� ��������
    break;
  case 14 : // 15) ����������
    break;
  //==//==//==//==
  case 15 : // 16) KolTik
  case 16 : // 17) �������������� ����� ����-��
  case 17 : // 18) ��������� ����� ����-��
  case 18 : // 19) ����������� ���
  case 19 : // 20) ���������� �� ������ �������������� ������� ������ ���
  case 20 : // 21) ���������� �� ������ �������������� �������� ������ ���
  case 21 : // 22) ���������� ������� �����. (��50) ���
  case 22 : // 23) ������������ �������� ��� (���)
  case 23 : // 24) ������ ��� ���������� (���)
  case 24 : // 25) ��� ���������� ������������ (���)
  case 25 : // 26) ������ ���������� (������ = 5) (���)
  case 26 : // 27) ���������� ������ ���������� (�� 150)
  case 27 : // 28) ���� � �� �� 1 �������
    break;
  default :
    RetVal = -1;
  }
  return RetVal;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
