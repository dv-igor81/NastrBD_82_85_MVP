#pragma hdrstop
#include <stdio.h>
//---------------------------------------------------------------------------
#include "RSProtokol.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
int iDiaDebug;
modbus_t * ctx;
extern unsigned char ModBus_kInByte;
//---------------------------------------------------------------------------
#define MAX_MESSAGE_LENGTH 260

//::    ---------- Request     Indication ----------
//::    | Client | ---------------------->| Server |
//::    ---------- Confirmation  Response ----------
typedef enum {
    // Request message on the server side
    MSG_INDICATION,
    // Request message on the client side
    MSG_CONFIRMATION
} msg_type_t;
//static int receive_msg(modbus_t *ctx, uint8_t *msg, msg_type_t msg_type)
int receive_msg(
    modbus_t * ctx,
    uint8_t * msg,
    msg_type_t msg_type );
int ReadFlashInvert( unsigned int Adr, unsigned long * Data );
int GetSerialNumber( unsigned long * SerNum );
// Builds a TCP request header
int _modbus_tcp_build_request_basis(
    modbus_t * ctx,
    int function,
    int addr,
    int nb,
    uint8_t * req );
//---------------------------------------------------------------------------
int _modbus_tcp_send_msg_pre(
    uint8_t * req,
    int req_length );
//---------------------------------------------------------------------------
ssize_t _modbus_tcp_send(
    modbus_t * ctx,
    const uint8_t * req,
    int req_length );
// DIA <<===
//---------------------------------------------------------------------------
double fabs(double x) // � xe2 ��� ������� ���� (������� � ����� math.h)
{
  if ( x < 0)
  {
    x *= -1;
  }
  return x;
}
//---------------------------------------------------------------------------
RSProtokol_t::RSProtokol_t() :
  // ������ ��� ����������
  m_nPwmCycleTimeMin(3200),
  m_nPwmCycleTimeMax(4095),
  // ������������ ��������� ���
  m_nPwmPulseLengthMin(40),
  m_nPwmPulseLengthMax(120),
  // ����������
  m_nPwmCycleTimeOffset(1),
  m_nPwmPulseLengOffset(1),
  flagARCH_Off(false)
  , P_Gain1(12.0)
  , I_Gain1(2.0)
  , I_Error1(0.0)
  , I_State(0.0)
  , I_State1(0.0)
  , I_Min1(-25.0)
  , I_Max1(25.0)
  , DRIVE1_MIN(-25.0)
  , DRIVE1_MAX(25.0)
{
  this->AddrBD = 63;
  this->FlagDebug = 0;
  this->ErrorCode = 0;
  this->COMPort = 0;
  this->pbuf_read = this->buf_read;
  this->pbuf_write = this->buf_write;
  sprintf(Str_err, "%s", "������ ������ RSProtokol_t �� ����������");

  flagARCH = 0;
  flagUchSv = 0;
  flagTCP = false;
  auto_State_Flag = 0; // ��� ����-������� ���������� �����������
  ReadTimeout = 100;
  WriteTimeout = 100;
  ClearBDSpectr();

  ptr_Edit_3_01__14[0] = & Edit_3_01;
  ptr_Edit_3_01__14[1] = & Edit_3_02;
  ptr_Edit_3_01__14[2] = & Edit_3_03;
  ptr_Edit_3_01__14[3] = & Edit_3_04;
  ptr_Edit_3_01__14[4] = & Edit_3_05;
  ptr_Edit_3_01__14[5] = & Edit_3_06;
  ptr_Edit_3_01__14[6] = & Edit_3_07;
  ptr_Edit_3_01__14[7] = & Edit_3_08;
  ptr_Edit_3_01__14[8] = & Edit_3_09;
  ptr_Edit_3_01__14[9] = & Edit_3_10;
  ptr_Edit_3_01__14[10] = & Edit_3_11;
  ptr_Edit_3_01__14[11] = & Edit_3_12;
  ptr_Edit_3_01__14[12] = & Edit_3_13;
  ptr_Edit_3_01__14[13] = & Edit_3_14;
  ptr_Edit_3_01__14[14] = & Edit_3_15;
  //----------------------------------
  AddrRegModBus_BD82[0] = 10; // ����� �����
  AddrRegModBus_BD82[1] = 0x300+2; // ����������
  AddrRegModBus_BD82[2] = 0x300+3; // ����������� ����
  AddrRegModBus_BD82[3] = 0x300+4; // ������������ ����
  AddrRegModBus_BD82[4] = 0x300+5; // ������� ����������
  AddrRegModBus_BD82[5] = 0x300+6; // ���-�� ����������
  AddrRegModBus_BD82[6] = 0x300+7; // ���-�� ������� �����
  AddrRegModBus_BD82[7] = 0x300+8; // ������� ������� 1
  AddrRegModBus_BD82[8] = 0x300+9; // ������� ������� 2
  AddrRegModBus_BD82[9] = 0x300+10; // ������� ������� 3
  AddrRegModBus_BD82[10] = 0x300+11; // ���, ��
  AddrRegModBus_BD82[11] = 8; // ����. ������������ ����, [��]
  AddrRegModBus_BD82[12] = 0x300 + 12; // ����. ������� �������, �
  AddrRegModBus_BD82[13] = 0x300 + 13; // ����. ������� �����, �
  AddrRegModBus_BD82[14] = 19; // ���������� ���, ���. / �  
  //----------------------------------
  AddrRegModBus_BD85_New[0] = 10; // ����� �����
  AddrRegModBus_BD85_New[1] = 0x300+2; // ����������
  AddrRegModBus_BD85_New[2] = 0x300+3; // ����������� ����
  AddrRegModBus_BD85_New[3] = 0x300+4; // ������������ ����
  AddrRegModBus_BD85_New[4] = 0x300+5; // ������� ����������
  AddrRegModBus_BD85_New[5] = 0x300+6; // ���-�� ����������
  AddrRegModBus_BD85_New[6] = 0x300+7; // ���-�� ������� �����
  AddrRegModBus_BD85_New[7] = 0x300+8; // ������� ������� 1
  AddrRegModBus_BD85_New[8] = 0x300+9; // ������� ������� 2
  AddrRegModBus_BD85_New[9] = 0x300+10; // ������� ������� 3
  AddrRegModBus_BD85_New[10] = 0x300+11; // ���, ��
  AddrRegModBus_BD85_New[11] = 18; // ����. ������������ ����, [��]
  AddrRegModBus_BD85_New[12] = 0x300 + 12; // ����. ������� �������, �
  AddrRegModBus_BD85_New[13] = 0x300 + 13; // ����. ������� �����, �
  //----------------------------------
  //==\\this->Data.FlagReadKolTikSpektr = false;
  this->Data.FlagWriteKolTikSpektr = false;
  this->Data.bf_SpectrStart = false;
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
int RSProtokol_t::strlcpy(char * dest, const char * src, int dest_size)
{
  char * d;
  const char * s;
  d = dest;
  s = src;
  int n = dest_size;

  if (n != 0 && --n != 0)
  {
    do
    {
      if ((*d++ = *s++) == 0)
      {
    	break;
      }
    } while (--n != 0);
  }

  if (n == 0)
  {
    if (dest_size != 0)
    {
      *d = '\0';
    }
    while (*s++)
    {
      ;
    }
  }
  return (s - src - 1);
}
//---------------------------------------------------------------------------
void RSProtokol_t::SetComPortHahdle( HANDLE hCOM )
{
  if ( hCOM == 0 )
  {
    return;
  }
  if ( hCOM == INVALID_HANDLE_VALUE )
  {
    return;
  }
  this->COMPort = hCOM;
  //flagPort = true; // ��������� ����� ������ (true)/������ (false)
}
//---------------------------------------------------------------------------
void RSProtokol_t::FreeComPortHahdle( void )
{
  this->COMPort = 0;
  //flagPort = false; // ��������� ����� ������ (true)/������ (false)
}
//---------------------------------------------------------------------------
int RSProtokol_t::RSConnect(const char * device)
{
  int speed;
  if ( flagModbusProtokol == 0 ) // ������ ��������: "9-�� ������"
  {
    this->ErrorCode = RSConnect(
	device, // device
	115200, // baud
	MARKPARITY, // parity
	8, // data_bit
	ONESTOPBIT); // stop_bit
  }
  else if ( flagModbusProtokol == 1 ) // ������ ��������: "ModBus RTU"
  {
    this->parity = NOPARITY;
    this->stop_bit = TWOSTOPBITS;
    if (newProsivka == true) // �� 84 (�������� 230 400)
    {
      this->ErrorCode = RSConnect(
        device, // device
        230400, // baud
        this->parity, // parity // (SPACEPARITY, NOPARITY)
         8, // data_bit
        this->stop_bit); // stop_bit // (ONESTOPBIT, TWOSTOPBITS)
    }
    else
    {
      this->ErrorCode = RSConnect(
        device, // device
        57600, // baud
        this->parity, // parity // (SPACEPARITY, NOPARITY)
         8, // data_bit
        this->stop_bit); // stop_bit // (ONESTOPBIT, TWOSTOPBITS)
    }
  }
  //! else if ( flagTCP == true )
  else if ( flagModbusProtokol == 2 || // ModBus TCP
            flagModbusProtokol == 3 )  // ModBus RTU (TCP/IP)
  {
    if ( flagModbusProtokol == 2 ) // ModBus TCP
    {
      ctx = modbus_new_tcp( Data.IP_Addr, Data.IP_Port );
    }
    if ( flagModbusProtokol == 3 ) // ModBus RTU (TCP/IP)
    {
      ctx = modbus_new_rtu_tcp_ip( Data.IP_Addr, Data.IP_Port );
    }
    modbus_set_slave( ctx, Data.Addr_BD_TCP );
    if ( modbus_connect( ctx ) == -1 )
    {
      // sprintf( Str, "����� ����������": %s\n, modbus_strerror( errno ) );
      // Memo_Display->Lines->Add( Str );
      modbus_free( ctx );
      Data.bFlag_TCP_Connect = false;
      return -1;
    }
    Data.bFlag_TCP_Connect = true;
    return 0; // ErrorCode
  }
  //=== //=== //===
  //if ( COMPort == 0 )
  //{
  //  flagPort = false; // ��������� ����� ������ (true)/������ (false)
  //}
  //else
  //{
  //  flagPort = true; // ��������� ����� ������ (true)/������ (false)
  //}
  return this->ErrorCode;
}
//---------------------------------------------------------------------------
void RSProtokol_t::Reset(void)
{
  // ===
  this->Data.flagGetVersion = false; // ���� ������������, ���� ����� ���������� ��������� � ������� ���� ���
  this->Data.flagSetTimeInterval = false; // ���� ������������, ���� ����� ���������� ��������� � ������� ���� ���
  this->Data.flagGetTimeInterval = false; // ���� ������������, ���� ����� ���������� ��������� � ������� ���� ���
  this->Data.flagGetIndAdr = false; // ���� ������������, ���� ����� ���������� ��������� � ������� ���� ���
  this->Data.flagGetGrpAdr = false; // ���� ������������, ���� ����� ���������� ��������� � ������� ���� ���
  this->Data.bfSetTimeSpektr = false; // �������� ��� ������� �� ��������������
  // ===
  this->Data.ptrUhiI = 0;
  this->Data.ptrLEDAmp = 0;
  this->Data.kodUhiI = 0;
  this->Data.kodLEDAmp = 0;
  // ===
  this->Data.TSchet = 0;
  this->Data.TSchetTemp = 0;
  this->Data.bFlagCount = false;  
  this->Data.SumSchet = 0;
  this->Data.T_Limit = 0;  
  // ===
  this->Data.flagFirst = -1;
  this->Data.flagSecond = -1;
  this->Data.count = 0;
  this->Data.count2 = 0;
  // ===
  this->testErr = 0; // ��� �������� ��� ����� ����������� ���� ���������� �����
  this->indexArrTime = 0;
  this->MaxIndexArrTime = 0;
  this->N0 = 0;
  this->N1 = 0;
  this->Data.Temper = 0;
  this->Data.flTemper = 0.0f;
  this->Data.DNU = 0;
  this->Data.dbDNU = 0.0;
  this->Data.DVU = 0;
  this->Data.dbDVU = 0.0;
  this->Data.UhiI = 0;
  this->Data.UhiIsr = 0;

  for ( int i = 0; i < 50; i++ )
  {
    this->Data.sumUhiI[i] = 0;
    this->Data.LEDAmp[i] = 0;
  }

  this->Data.kodUhiI = 0;
  this->Data.ptrUhiI = 0;
  this->Data.dbUhiIsr = 0.0;
  this->Data.SIM3 = 0;
  this->Data.dbSIM3 = 0.0;
  this->Data.SIM4 = 0;
  this->Data.dbSIM4 = 0.0;
  // ===
  this->Data.sim3 = 0;
  this->Data.sim4 = 0;
  // ===
  this->Data.SIM2 = 0;
  this->Data.Ampl = 0;
  this->Data.dbAmpl = 0.0;
  this->Data.LEDAmpI = 0;
  this->Data.LEDAmpR = 0;
  this->Data.LEDAmpRcp = 0;

  this->Data.kodLEDAmp = 0;
  this->Data.ptrLEDAmp = 0;
  this->Data.dbLEDAmpRcp = 0.0;
  //
  this->Data.PSW = 0;
  this->ReturnVar = -1;
  // ������� flagFirstAddr 23.10.2014
  // ������ flagFirstAddr � ������� flagSpeed 16.01.2015
  this->flagFirstAddr = true; // true - ��� ������ ��������� � �� ��� ��� ���� ��������
  this->NullsToStr_err(); // �������� ������ ��������� �� �������

  CheckBox_auto_Checked = false; // = true, ���� ������ CheckBox_auto ����������
  CheckBox_DAuto_Checked = false; // = true, ���� ������ CheckBox_DAuto ����������
  //
  P_Gain0 = 12.0;
  I_Gain0 = 2.0;
  I_Error0 = 0.0;
  I_State0 = 0.0;
  DRIVE0_MIN = -25.0;
  DRIVE0_MAX = 25.0;
  I_Min0 = DRIVE0_MIN;
  I_Max0 = DRIVE0_MAX;
  //
  this->Data.Ver_HEX = 0;
  this->Data.iSpektrZaprosCount = 0; // ���������� ������� ������� ���������
  this->Data.TimeNaboraSpectr = 0; // ����� ������ �������
  this->Data.TimeGotovSpectr = 0; // ����� ���������� �������

  if ( this->COMPort != 0 )
  {
    // ������ ����� ������/������
    if( PurgeComm( this->COMPort, PURGE_TXCLEAR | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_RXABORT) == 0 )
    {
      ;
    }
  }
}
//---------------------------------------------------------------------------
void RSProtokol_t::NullsToStr_err(void)
{
  for (int k = 0; k < sizeof(Str_err); k++) // 250 - ����� ������
  {
    Str_err[k] = '\0';
  }
}
//---------------------------------------------------------------------------
int RSProtokol_t::RSConnect(const char * COMNum, int baud, int parity, int data_bit, int stop_bit)
{
  int dest_size;
  dest_size = sizeof(this->DEVID) / sizeof(this->DEVID[0]);
  this->ret_size = strlcpy( &this->DEVID[0], "\\\\.\\", dest_size );
  this->ret_size = strlcpy( &this->DEVID[4], COMNum, dest_size ); // ������ ������ ����� ��� \\.\COM10 ��� ������������ ������ ���-�����
  this->baud = baud;
  this->parity = parity;
  this->data_bit = data_bit;
  this->stop_bit = stop_bit;
  this->ErrorCode = 0;
  this->err = 0;

  Reset();

  if ( this->COMPort == 0 ) // �� ���� ���-���� ��� �� ������, ��� �������� ���-���� ��� ������
  {
    this->COMPort = CreateFile
        ( this->DEVID, // lpFileName ("LPT1")
        GENERIC_READ | GENERIC_WRITE, // dwDesiredAccess (GENERIC_WRITE)
        0, // dwShareMode (0)
        NULL, // lpSecurityAttributes (IntPtr.Zero)
        OPEN_EXISTING,  // dwCreationDisposition (OPEN_EXISTING)
        NULL, // dwFlagsAndAttributes (0)
        0 ); // hTemplateFile (IntPtr.Zero)
  }
  else
  {
    if (FlagDebug > 0)
    {
      sprintf(Str_err, "%s", "������: ���� ��� ������ (RSConnect)");
    }
    ErrorCode = 1; // ��� ������ 1 - ���� ��� ������
    return -1;
  }
  // ===
  if (this->COMPort == INVALID_HANDLE_VALUE)
  {
    this->COMPort = NULL;
    if (FlagDebug > 0)
    {
      sprintf(Str_err, "%s", "������: ���� �� �������� (RSConnect)");
    }
    ErrorCode = 2; // ��� ������ 2 - ���� �� ��������
    return -1;
  }
  if(GetCommState(this->COMPort, &this->forSave.lpDCB) == false)
  {
    if (FlagDebug > 0)
    {
      sprintf(Str_err, "%s", "������: �� ������� ������� TDCB (RSConnect)");
    }
    ErrorCode = 3; // ��� ������ 3 - �� ������� ������� TDCB
    return -1;
  }
  if (GetCommTimeouts(this->COMPort, &this->forSave.lpCommTimeouts) == false)
  {
    if (FlagDebug > 0)
    {
      sprintf(Str_err, "%s", "������: �� ������� ������� TCommTimeouts (RSConnect)");
    }
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

  // No software handshaking
  this->forUse.lpDCB.fTXContinueOnXoff = TRUE;
  this->forUse.lpDCB.fOutX = FALSE;
  this->forUse.lpDCB.fInX = FALSE;
  // Binary mode (it's the only supported on Windows anyway)
  this->forUse.lpDCB.fBinary = TRUE;
  // Don't want errors to be blocking (�� ��������� ��������� ���� �������� ������/������ ��� ������)
  this->forUse.lpDCB.fAbortOnError = FALSE;

  this->forUse.lpDCB.fNull = false;  // ������� ����� �� �������������
  // ===
  this->forUse.lpDCB.fAbortOnError = /*TRUE*/FALSE;  // ������� ���������� ��� �������� � ������ ������
  // true - �������� �������� ModBus �������� �� ������ ���-������

  this->forUse.lpDCB.fErrorChar = false;
  //\\this->forUse.lpDCB.fDsrSensitivity = FALSE; // ��������� ��������������� �������� � ��������� ����� DSR
  // ������ �������� � ��������� ��������� �� ������ ���������� ErrorChar
  this->forUse.lpDCB.ErrorChar = 0;
  this->forUse.lpDCB.fDtrControl = DTR_CONTROL_DISABLE;
  this->forUse.lpDCB.fRtsControl = RTS_CONTROL_DISABLE;

  this->forUse.lpCommTimeouts.ReadIntervalTimeout = 0; // ����������� ���������� �������� ����� �������� ���� ��������
  this->forUse.lpCommTimeouts.ReadTotalTimeoutMultiplier = 0; // ����. ��� ������� ����������� ����������� ������� ������ �������
  //this->forUse.lpCommTimeouts.ReadTotalTimeoutConstant = 100; // ����. ��� ������� ����������� ����������� ������� ������ �������
  this->forUse.lpCommTimeouts.ReadTotalTimeoutConstant = ReadTimeout;
  this->forUse.lpCommTimeouts.WriteTotalTimeoutMultiplier = 0; // ����. ��� ������� ����������� ����������� ������� ������ �������
  //this->forUse.lpCommTimeouts.WriteTotalTimeoutConstant = 100; // ����. ��� ������� ����������� ����������� ������� ������ �������
  this->forUse.lpCommTimeouts.WriteTotalTimeoutConstant = WriteTimeout;

  if( SetCommState(this->COMPort, &this->forUse.lpDCB) == false )
  {
    if (FlagDebug > 0)
    {
      sprintf(Str_err, "%s", "������: �� ������� ���������� TDCB (RSConnect)");
    }
    ErrorCode = 5; // ��� ������ 5 - �� ������� ���������� TDCB
    return -1;
  }
  if ( SetCommTimeouts(this->COMPort, &this->forUse.lpCommTimeouts) == false )
  {
    if (FlagDebug > 0)
    {
      sprintf(Str_err, "%s", "������: �� ������� ���������� TCommTimeouts (RSConnect)");
    }
    ErrorCode = 6; // ��� ������ 6 - �� ������� ���������� TCommTimeouts
    return -1;
  }
  // ������ ����� ������/������
  if( PurgeComm( this->COMPort, PURGE_TXCLEAR | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_RXABORT) == 0 )
  {
    if (FlagDebug > 0)
    {
      sprintf(Str_err, "%s", "������: ������� �����/�������� (RSConnect)");
    }
    ErrorCode = 16;  // ��� ������ 16 - ������� �����/�������� (RSConnect)
    return -1;
  }
  return 0;
}
//---------------------------------------------------------------------------
int RSProtokol_t::RSDisConnect(void)
{
  if ( flagTCP == true )
  {
    if ( Data.bFlag_TCP_Connect == true )
    {
      modbus_close( ctx );
      modbus_free( ctx );
      Data.bFlag_TCP_Connect = false;
    }    
    return 0;
  }
  //===
  if (this->COMPort == 0)
  {
    if (FlagDebug > 0)
    {
      sprintf(Str_err, "%s", "������: ���� ��� ������ (RSDisConnect)");
    }
    //flagPort = false;
    ErrorCode = 7; // ��� ������ 7 - ���� ��� ������
    return -1;
  }
  if(SetCommState(this->COMPort, &this->forSave.lpDCB) == false)
  {
    CloseHandle(this->COMPort);
    this->COMPort = 0;
    if (FlagDebug > 0)
    {
      sprintf(Str_err, "%s", "������: �� ������� ���������� TDCB ��� �������� ����� (RSDisConnect)");
    }
    //flagPort = false;
    ErrorCode = 8; // ��� ������ 8 - �� ������� ���������� TDCB ��� �������� �����
    return -1;
  }
  if (SetCommTimeouts(this->COMPort, &forSave.lpCommTimeouts) == false)
  {
    CloseHandle(this->COMPort);
    this->COMPort = 0;
    if (FlagDebug > 0)
    {
      sprintf(Str_err, "%s", "������: �� ������� ���������� TCommTimeouts ��� �������� ����� (RSDisConnect)");
    }
    //flagPort = false;
    ErrorCode = 9; // ��� ������ 9 - �� ������� ���������� TCommTimeouts ��� �������� �����
    return -1;
  }
  CloseHandle(this->COMPort);
  this->COMPort = 0;
  //flagPort = false;
  return 0;
}
//---------------------------------------------------------------------------
int RSProtokol_t::WriteToPort( unsigned char * buf, int count, int parity )
{
  DWORD wb;
  if ( this->COMPort == 0 )
  {
    if ( FlagDebug > 1 )
    {
      int len = strlen( Str_err );
      if ( len != 0 )
      {
        sprintf(&Str_err[len], "%s", " => ������: ���������������� ���� ������ (WriteToPort)");
      }
      else
      {
        sprintf(Str_err, "%s", "������: ���������������� ���� ������ (WriteToPort)");
      }
    }
    ErrorCode = 10; // ��� ������ 10 - ���� ������ (WriteToPort)
    return -1;
  }
  if ( this->parity != parity )
  {
    this->parity = parity;
    this->forUse.lpDCB.Parity = this->parity;
    if( SetCommState( this->COMPort, &this->forUse.lpDCB ) == false )
    {
      if ( FlagDebug > 0 )
      {
        int len = strlen( Str_err );
        if (len != 0)
        {
          sprintf(&Str_err[len], "%s", " => ������: �� ������� ���������� TDCB (WriteToPort)");
        }
        else
        {
          sprintf(Str_err, "%s", "������: �� ������� ���������� TDCB (WriteToPort)");
        }
      }
      ErrorCode = 11; // ��� ������ 11 - �� ������� ���������� TDCB
      return -1;
    }
  }
  if ( WriteFile( this->COMPort, buf, count, &wb, NULL ) == false )
  {
    if ( FlagDebug > 0 )
    {
      int len = strlen(Str_err);
      if ( len != 0 )
      {
        sprintf(&Str_err[len], "%s", " => ������: �� ������� ����������� ������ � ���� (WriteToPort)");
      }
      else
      {
        sprintf(Str_err, "%s", "������: �� ������� ���������� TDCB (WriteToPort)");
      }
    }
    ErrorCode = 12;  // ��� ������ 12 - �� ������� ����������� ������ � ����
    return -1;
  }
  return (int)wb;
}
//---------------------------------------------------------------------------
int RSProtokol_t::ReadFromPort(unsigned char * buf, int count, int parity)
{
  DWORD rb, n;
  if (this->COMPort == 0)
  {
    if (FlagDebug > 0)
    {
      int len = strlen(Str_err);
      if (len != 0)
      {
        sprintf(&Str_err[len], "%s", " => ������: ���������������� ���� ������ (ReadFromPort)");
      }
      else
      {
        sprintf(Str_err, "%s", "������: ���������������� ���� ������ (ReadFromPort)");
      }
    }
    ErrorCode = 13; // ��� ������ 13 - ���� ������ (ReadFromPort)
    return -1;
  }
  if (this->parity != parity)
  {
    this->parity = parity;
    this->forUse.lpDCB.Parity = this->parity;
    if(SetCommState(this->COMPort, &this->forUse.lpDCB) == false)
    {
      if (FlagDebug > 0)
      {
        int len = strlen(Str_err);
        if (len != 0)
        {
          sprintf(&Str_err[len], "%s", " => ������: �� ������� ���������� TDCB (ReadFromPort)");
        }
        else
        {
          sprintf(Str_err, "%s", "������: �� ������� ���������� TDCB (ReadFromPort)");
        }
      }
      ErrorCode = 14; // ��� ������ 14 - �� ������� ���������� TDCB
      return -1;
    }
  }
  if ( ReadFile(this->COMPort, buf, count, &rb, NULL) == false)
  {
    if (FlagDebug > 0)
    {
      int len = strlen(Str_err);
      if (len != 0)
      {
        sprintf(&Str_err[len], "%s", " => ������: �� ������� ����������� ������ �� ���� (ReadFromPort)");
      }
      else
      {
        sprintf(Str_err, "%s", "������: �� ������� ����������� ������ �� ���� (ReadFromPort)");
      }
    }
    ErrorCode = 15;  // ��� ������ 15 - �� ������� ����������� ������ �� ����
    return -1;
  }
  return (int)rb;
}
//---------------------------------------------------------------------------
void RSProtokol_t::ClearReqRsp( uint8_t * Arr, int Length ) // �������� ������
{
  for ( int i = 0; i < Length; i++ ) // ���������
  {
    Arr[i] = 0;
  }
}
//---------------------------------------------------------------------------
int RSProtokol_t::CommandExec( unsigned char kOutByte, unsigned char kInByte )
{
  unsigned char Addr;
  Addr = this->AddrBD; // ����� �� (63 - ��� ��������� "������" �� ���������)

  ModBus_kInByte = kInByte + 1;
    
  // ===>> 18.02.2015
  if ( flagModbusProtokol == 2 ) // ��������: "ModBus TCP"  
  {
    int req_length;
    int msg_length;
    int addr; // ����������-��������
    int nb; // ����������-��������
    int rc;

    if ( Data.bFlag_TCP_Connect == false )
    {
      return -1;
    }

    addr = 0; // ����� ��������
    nb = 0;

    uint8_t req[MAX_MESSAGE_LENGTH]; // ������ // #define MAX_MESSAGE_LENGTH 260
    uint8_t rsp[MAX_MESSAGE_LENGTH]; // �����

    ClearReqRsp( req, MAX_MESSAGE_LENGTH ); // �������� ������ �������
    ClearReqRsp( rsp, MAX_MESSAGE_LENGTH ); // �������� ������ ������

    req_length = _modbus_tcp_build_request_basis( // ��������� ��������� TCP-�������
      ctx,
      65, // ��� �������
      addr, // ����� ��������
      nb, // ���������� ���������
      req ); // ������ (�����)

    req_length -= 4; // req[7] = function;

    for ( int i = 0; i <= kOutByte; i++ )
    {
      req[req_length++] = buf_write[i];
    }
    msg_length = _modbus_tcp_send_msg_pre( // ������ ��� ModBus TCP
        req, // ������ (�����)
        req_length ); // ����� ������

    // In recovery mode, the write command will be issued until to be
    //   successful! Disabled by default.
    do
    {
      rc = _modbus_tcp_send( ctx, req, req_length );
      if ( rc == -1 )
      {
        ; // ������
      }
    }
    while ( ( ctx->error_recovery & MODBUS_ERROR_RECOVERY_LINK ) && ( rc == -1 ) );
    if ( ( rc > 0 ) && ( rc != msg_length ) )
    {
      errno = EMBBADDATA;
      return -1;
    }
    if ( rc > 0 )
    {
      rc = receive_msg( ctx, // ����������� ���������� ���� modbus_t
      rsp, MSG_CONFIRMATION ); // CONFIRMATION - �������������
      if (rc == -1)
      {
        return -1;
      }
      // rc = check_confirmation( ctx, req, rsp, rc );
    }
    for ( int i = 0; i <= kInByte; i++ )
    {
      buf_read[i] = rsp[9+i];
    }
    if (
          (req[6] == rsp[6] ) && // ����� ��
          (req[7] == rsp[7] ) && // ��� �������
          (req[8] == rsp[8] ) // ��� ��� �������
       )
    {
      return 0; // ErrorCode
    }
    else
    {
      return -1; // ErrorCode    
    }
  } // ����� �����: if ( flagModbusProtokol == 2 )
  else
  // <<=== 18.02.2015
  if ( this->flagModbusProtokol == 0 ) // ��������: "9-�� ������"
  {
    if ( (this->flagFirstAddr == true) || (this->flagSpeed == false) )
    { // (flagSpeed == true - ���� �������� ������)
      this->flagFirstAddr = false;
      WriteToPort( &Addr, 1, MARKPARITY );
      this->err = ReadFromPort( &this->SSP_Value, 1, MARKPARITY );
      if ( this->err != 1 )
      {
        if (FlagDebug > 0)
        {
          int len = strlen(Str_err);
          if (len != 0)
          {
            sprintf(&Str_err[len], "%s", " => ������: ����� �������� ���� �� ����� 1 (CommandExec)");
          }
          else
          {
            sprintf(Str_err, "%s", "������: ����� �������� ���� �� ����� 1 (CommandExec)");
          }
        }
        ErrorCode = 16;  // ��� ������ 16 - ����� �������� ���� �� ������������� ���������� (CommandExec)
        this->flagFirstAddr = true; // ����� ���� ��� ��������� ������
        return -1;
      }
    } // if ( (this->flagFirstAddr == true) || (this->flagSpeed == false) )
    WriteToPort(this->pbuf_write, kOutByte + 1, SPACEPARITY);
    this->err = ReadFromPort(this->pbuf_read, kInByte, SPACEPARITY);
    if ( this->err != kInByte )
    {
      if (FlagDebug > 0)
      {
        int len = strlen(Str_err);
        if (len != 0)
        {
          sprintf(&Str_err[len], "%s", " => ������: ����� �������� ���� �� ������������� ���������� (CommandExec)");
        }
        else
        {
          sprintf(Str_err, "%s", "������: ����� �������� ���� �� ������������� ���������� (CommandExec)");
        }
      }
      ErrorCode = 17;  // ��� ������ 17 - ����� �������� ���� �� ������������� ���������� (CommandExec)
      // ===
      this->flagFirstAddr = true;
      // ===
      return -1;
    }
  }
  else if ( flagModbusProtokol == 1 ) // ��������: "ModBus RTU"
  {
    int Index = 0;
    buf_write_modbus[Index++] = this->AddrBD;
    buf_write_modbus[Index++] = 65; // ��� �������
    for ( int i = 0; i <= kOutByte; i++ )
    {
      buf_write_modbus[Index++] = pbuf_write[i];
    }
    CRC = crc16( &buf_write_modbus[0], Index );
    buf_write_modbus[Index++] = CRC >> 8;
    buf_write_modbus[Index++] = CRC;

    //=== //=== //===
    WriteToPort( this->buf_write_modbus, Index, this->parity );
    this->err = ReadFromPort( this->buf_read_modbus, 3, this->parity );
    //=== //=== //===

    if ( this->err != 3 )
    {
      if (FlagDebug > 0)
      {
        int len = strlen(Str_err);
        if (len != 0)
        {
          sprintf(&Str_err[len], "%s", " => ������: ����� �������� ���� �� ������������� ���������� (CommandExec)");
        }
        else
        {
          sprintf(Str_err, "%s", "������: ����� �������� ���� �� ������������� ���������� (CommandExec)");
        }
      }
      ErrorCode = 18;  // ��� ������ 18 - ����� �������� ���� �� ������������� ���������� (CommandExec)
      return -1; // ������: �� ��������� ������ ��� �����
    }


    if (buf_read_modbus[1-1] != this->AddrBD)
    {
      if (FlagDebug > 0)
      {
        int len = strlen(Str_err);
        if (len != 0)
        {
          sprintf(&Str_err[len], "%s", " => ������: �������� ���� �� �������� ������� ��  (CommandExec)");
        }
        else
        {
          sprintf(Str_err, "%s", "������: �������� ���� �� �������� ������� ��  (CommandExec)");
        }
      }
      ErrorCode = 19;  // ��� ������ 19 - �������� ���� �� �������� ������� �� (CommandExec)
      return -1;
    }
    if (buf_read_modbus[2-1] != 65)
    {
      if (FlagDebug > 0)
      {
        int len = strlen(Str_err);
        if (len != 0)
        {
          sprintf(&Str_err[len], "%s", " => ������: �������� ���� �� �������� ����� ������� 65 (CommandExec)");
        }
        else
        {
          sprintf(Str_err, "%s", "������: �������� ���� �� �������� ����� ������� 65 (CommandExec)");
        }
      }
      ErrorCode = 20;  // ��� ������ 20 -  �������� ���� �� �������� ����� ������� 65 (CommandExec)
      return -1;
    }
    //=== //=== //===
    this->err = ReadFromPort(&this->buf_read_modbus[3], kInByte + 2, this->parity);
    //=== //=== //===
    if (this->err != kInByte + 2)
    {
      if (FlagDebug > 0)
      {
        int len = strlen(Str_err);
        if (len != 0)
        {
          sprintf(&Str_err[len], "%s", " => ������: �� ��������� ��������� ����� ������� (CommandExec)");
        }
        else
        {
          sprintf(Str_err, "%s", "������: �� ��������� ��������� ����� ������� (CommandExec)");
        }
      }
      ErrorCode = 21;  // ��� ������ 21 - �� ��������� ��������� ����� ������� (CommandExec)
      return -1;
    }
    CRC = crc16( &buf_read_modbus[0], 3 + kInByte + 2);
    if (CRC != 0)
    {
      if (FlagDebug > 0)
      {
        int len = strlen(Str_err);
        if (len != 0)
        {
          sprintf(&Str_err[len], "%s", " => ������: CRC �� �������� ������� �� ����� ���� (CommandExec)");
        }
        else
        {
          sprintf(Str_err, "%s", "������: CRC �� �������� ������� �� ����� ���� (CommandExec)");
        }
      }
      ErrorCode = 22;  // ��� ������ 22 - CRC �� �������� ������� �� ����� ���� (CommandExec)
      return -1;
    }
    for ( int i = 0; i < kInByte; i++ )
    {
      pbuf_read[i] = buf_read_modbus[3+i];
    }
  }
  // ===>> 17.07.2017
  else if ( flagModbusProtokol == 3 ) // ��������: "ModBus RTU (TCP/IP)"
  {
    int rc;
    int Index = 0;

    buf_write_modbus[Index++] = this->AddrBD;
    buf_write_modbus[Index++] = 65; // ��� �������
    for ( int i = 0; i <= kOutByte; i++ )
    {
      buf_write_modbus[Index++] = pbuf_write[i];
    }
    CRC = crc16( &buf_write_modbus[0], Index );
    buf_write_modbus[Index++] = CRC >> 8;
    buf_write_modbus[Index++] = CRC;

    // In recovery mode, the write command will be issued until to be
    //   successful! Disabled by default.
    do
    {
      rc = _modbus_tcp_send( ctx, buf_write_modbus, Index );
      if ( rc == -1 )
      {
        ; // ������
      }
    } while ( ( ctx->error_recovery & MODBUS_ERROR_RECOVERY_LINK ) && ( rc == -1 ) );

    if ( ( rc > 0 ) && ( rc != Index ) )
    {
      errno = EMBBADDATA;
      return -1;
    }

    if ( rc > 0 )
    {
      rc = receive_msg(
          ctx, // ����������� ���������� ���� modbus_t
          buf_read_modbus,
          MSG_CONFIRMATION ); // CONFIRMATION - �������������
      if (rc == -1)
      {
        return -1;
      }
      // rc = check_confirmation( ctx, req, rsp, rc );
    }
    if (buf_read_modbus[1-1] != this->AddrBD)
    {
      if (FlagDebug > 0)
      {
        int len = strlen(Str_err);
        if (len != 0)
        {
          sprintf(&Str_err[len], "%s", " => ������: �������� ���� �� �������� ������� ��  (CommandExec)");
        }
        else
        {
          sprintf(Str_err, "%s", "������: �������� ���� �� �������� ������� ��  (CommandExec)");
        }
      }
      ErrorCode = 19;  // ��� ������ 19 - �������� ���� �� �������� ������� �� (CommandExec)
      return -1;
    }
    if (buf_read_modbus[2-1] != 65)
    {
      if (FlagDebug > 0)
      {
        int len = strlen(Str_err);
        if (len != 0)
        {
          sprintf(&Str_err[len], "%s", " => ������: �������� ���� �� �������� ����� ������� 65 (CommandExec)");
        }
        else
        {
          sprintf(Str_err, "%s", "������: �������� ���� �� �������� ����� ������� 65 (CommandExec)");
        }
      }
      ErrorCode = 20;  // ��� ������ 20 -  �������� ���� �� �������� ����� ������� 65 (CommandExec)
      return -1;
    }
    CRC = crc16( &buf_read_modbus[0], 3 + kInByte + 2);
    if (CRC != 0)
    {
      if (FlagDebug > 0)
      {
        int len = strlen(Str_err);
        if (len != 0)
        {
          sprintf(&Str_err[len], "%s", " => ������: CRC �� �������� ������� �� ����� ���� (CommandExec)");
        }
        else
        {
          sprintf(Str_err, "%s", "������: CRC �� �������� ������� �� ����� ���� (CommandExec)");
        }
      }
      ErrorCode = 22;  // ��� ������ 22 - CRC �� �������� ������� �� ����� ���� (CommandExec)
      return -1;
    }
    for ( int i = 0; i < kInByte; i++ )
    {
      pbuf_read[i] = buf_read_modbus[3+i];
    }
  }
  // <<=== 17.07.2017
  return 0;
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
int RSProtokol_t::GetGrpAdr(unsigned char * Adr/*, RSProtokol_t * Prot*/)
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
// ������� ������� ����������� ����������
int RSProtokol_t::GetTemp(unsigned int * Temper)
{
  this->buf_write[0] = 0x08;
  this->CodeRet = CommandExec(0, 2);
  if (this->CodeRet == 0) // ��� ������ ������
  {
    *Temper = this->buf_read[1] * 256 + this->buf_read[0];
  }
  else // ������ ������
  {
    *Temper = 0;
  }
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
// ������� ������������ �������� ���
int RSProtokol_t::GetSIM3(unsigned int * SIM)
{
  this->buf_write[0] = 0x1c;
  this->buf_write[1] = 3;
  this->CodeRet = CommandExec(1, 2);
  if (this->CodeRet == 0) // ��� ������ ������
  {
    *SIM = this->buf_read[1] * 256 + this->buf_read[0];
  }
  else // ������ ������
  {
    *SIM = 0;
  }
  return this->CodeRet;
}
//---------------------------------------------------------------------------
// ������� ������ ��� ����������
int RSProtokol_t::GetSIM4(unsigned int * SIM)
{
  this->buf_write[0] = 0x1c;
  this->buf_write[1] = 4;
  this->CodeRet = CommandExec(1, 2);
  if (this->CodeRet == 0) // ��� ������ ������
  {
    *SIM = this->buf_read[1] * 256 + this->buf_read[0];
  }
  else // ������ ������
  {
    *SIM = 0;
  }
  return this->CodeRet;
}
//---------------------------------------------------------------------------
// ������� ��� ���������� ������������
int RSProtokol_t::GetSIM2(unsigned int * SIM)
{
  this->buf_write[0] = 0x1c;
  this->buf_write[1] = 2;
  this->CodeRet = CommandExec(1, 2);
  if (this->CodeRet == 0) // ��� ������ ������
  {
    *SIM = this->buf_read[1] * 256 + this->buf_read[0];
  }
  else // ������ ������
  {
    *SIM = 0;
  }
  return this->CodeRet;
}
//---------------------------------------------------------------------------
// ������� ������ ����������
int RSProtokol_t::GetLEDAmp(unsigned int * Ampl)
{
  //unsigned int data;
  this->buf_write[0] = 0x10;
  this->CodeRet = CommandExec(0, 2);
  if (this->CodeRet == 0) // ��� ������ ������
  {
    *Ampl = this->buf_read[0];
  }
  else // ������ ������
  {
    *Ampl = 0;
  }
  return this->CodeRet;
}
//---------------------------------------------------------------------------
// ������� ��������� �������� �� ���������� ��������
int RSProtokol_t::GetLEDAmpR(int * AmplR)
{
  //unsigned int data;
  this->buf_write[0] = 0x1d;
  this->CodeRet = CommandExec(0, 2);
  if (this->CodeRet == 0) // ��� ������ ������
  {
    *AmplR = this->buf_read[0];
  }
  else // ������ ������
  {
    *AmplR = 0;
  }
  return this->CodeRet;
}
//---------------------------------------------------------------------------
// ������� ���� �� ����������� (��������� �������������) ��������� ��������, �������� �� 0,2 ���
int RSProtokol_t::GetCountImp(unsigned int * CImp)
{
  unsigned int data;
  this->buf_write[0] = 0x05;
  this->CodeRet = CommandExec(0, 2);
  if (this->CodeRet == 0) // ��� ������ ������
  {
    data = this->buf_read[1];
    *CImp = data * 256 + this->buf_read[0];
  }
  else // ������ ������
  {
    *CImp = 0;
  }
  return this->CodeRet;
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
// ���������� ����� ����� ��. ��� TimeInt = 255 (���������� �� ���������)
// �� �� ������������ ����������� ��������� ��������� ����� (������ �� UART)
// ��� TimeInt �������� �� 255 �� �������������� ������������ ��������� �����
// (����� �������������� ���: TimeInt * 25 = XXX ����.)
int RSProtokol_t::SetTimeInterval(unsigned char TimeInt)
{
  this->buf_write[0] = 0x0D;
  this->buf_write[1] = TimeInt;
  this->CodeRet = CommandExec(1, 1);
  return this->CodeRet;
}
//---------------------------------------------------------------------------
int RSProtokol_t::GetTimeInterval(unsigned char * TimeInt)
{
  this->buf_write[0] = 0x0E;
  this->CodeRet = CommandExec(0, 1);
  *TimeInt = buf_read[0];
  return this->CodeRet;
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
// ��������� ����������
int RSProtokol_t::GetStickyNote(char * strStickyNote)
{
  int i, addr;
  //!for (i = 0; i < 33; i++)
  for (i = 0; i < 25; i++)
  {
    strStickyNote[i] = '\0'; // 0 ... 24 + '\0'
  }

  if (NULL == strStickyNote)
  {
    return -1; // ��������� ������ ��������� �� ����
  }
  //for (i = 0, addr = 0x0d; i < 32; i += 4, addr++)
  for (i = 0, addr = 0x0d; i < 24; i += 4, addr++)
  {
    unsigned long ulStickyNote = 0;
    if(ReadFlashInvert(addr, &ulStickyNote) != 0)
    {
      return -1;
    }
    strStickyNote[i + 0] = LOBYTE(LOWORD(ulStickyNote));
    strStickyNote[i + 1] = HIBYTE(LOWORD(ulStickyNote));
    strStickyNote[i + 2] = LOBYTE(HIWORD(ulStickyNote));
    strStickyNote[i + 3] = HIBYTE(HIWORD(ulStickyNote));
  }
  return 0;
}
//---------------------------------------------------------------------------
// ���������� P3.7 (������ �������� ��� ��������� ��������)
int RSProtokol_t::Set_P37(void)
{
  this->buf_write[0] = 0x30;
  this->CodeRet = CommandExec(0, 1);
  return this->CodeRet;
}
//---------------------------------------------------------------------------
// �������� P3.7 (������ �������� ��� ��������� ��������)
int RSProtokol_t::Reset_P37(void)
{
  this->buf_write[0] = 0x31;
  this->CodeRet = CommandExec(0, 1);
  return this->CodeRet;
}
//---------------------------------------------------------------------------
int RSProtokol_t::SpectrClear(void)
{
  this->buf_write[0] = 0x20;
  this->CodeRet = CommandExec(0, 1);
  return this->CodeRet;
}
//---------------------------------------------------------------------------
int RSProtokol_t::SpectrStart(void)
{
  this->buf_write[0] = 0x21;
  this->CodeRet = CommandExec(0, 1);
  return this->CodeRet;
}
//---------------------------------------------------------------------------
int RSProtokol_t::SpectrStop(void)
{
  this->buf_write[0] = 0x22;
  this->CodeRet = CommandExec(0, 1);
  return this->CodeRet;
}
//---------------------------------------------------------------------------
int RSProtokol_t::SpectrReadBuf(unsigned char Block, unsigned char Mas[16])
{
  this->buf_write[0] = 0x23;
  this->buf_write[1] = Block;
  this->CodeRet = CommandExec(1, 16);  
  if (this->CodeRet == 0)
  {
    for (int i = 0; i < 16; i++)
    {
      Mas[i] = this->buf_read[i];
    }
  }
  return this->CodeRet;
}
//---------------------------------------------------------------------------
int RSProtokol_t::SetTimeSpectr(unsigned char TimeInt)
{
  this->buf_write[0] = 0x24;
  this->buf_write[1] = TimeInt;
  this->CodeRet = CommandExec(1, 1);
  return this->CodeRet;
}
//---------------------------------------------------------------------------
int RSProtokol_t::GetTimeSpectr(unsigned char * TimeInt)
{
  this->buf_write[0] = 0x25;
  this->CodeRet = CommandExec(0,1);
  *TimeInt = this->buf_read[0];
  return this->CodeRet;
}
//---------------------------------------------------------------------------
void RSProtokol_t::FlagAvtoSnyat() // ����� ������� "����"
{
  // ����� ������
  if (AutoPodbor_1_Un_2_U81 == 1)
  {
    //===>> 29.10.2018
    //Form_82_Start->CheckBox_auto->Checked = false;
    ev_CheckBoxAutoCheckedFalse();
    //<<=== 29.10.2018
  }
  if (AutoPodbor_1_Un_2_U81 == 2)
  {
    //===>> 29.10.2018
    //Form_82_Start->CheckBox_auto_0_81->Checked = false;
    ev_CheckBox081CheckedFalse();
    //<<=== 29.10.2018
  }
}
//---------------------------------------------------------------------------
void RSProtokol_t::FlagAvtoSnyatDiskr()
{
  //===>> 29.10.2018
  //Form_82_Start->CheckBox_DAuto_Standart->Checked = false;
  //Form_82_Start->CheckBox_DAuto_Shirokie->Checked = false;
  //Form_82_Start->CheckBox_DAuto_Rengen->Checked = false;
  //Form_82_Start->CheckBox_DAuto->Checked = false;
  ev_FlagAvtoSnyatDiskr();
  //<<=== 29.10.2018
}
//---------------------------------------------------------------------------
// ��������� ��������� ��� --> (U0 + Un == Uhi)
// ��� ��� --> (U0 * 0,81 + Un == Uhi)
void RSProtokol_t::AvtoPodborUhiIter() // ���������� Uhi
{
  // ==== ===== ===== 12.01.2016 <<===
  if ( CheckBox_auto_Checked == true )
  {
    typedef enum { ZnacheniyNebylo = 0,
                   ZnaceniePlus = 1,
                   ZnacenieMinus = 2,
                   ZnacenieNulevoe = 3 } PlusMinus_t;
    // Data.SIM3 - ������������ ��������� ���
    // Data.SIM4 - ������ ��� ����������
    static int Sekunda3 = 0;
    static PlusMinus_t bFlag_1 = ZnacheniyNebylo; // ������� �������� (������)
    static PlusMinus_t bFlag_2 = ZnacheniyNebylo; // ��������, ������� ���� ����� ��������� bFlag_1
    static PlusMinus_t bFlag_3 = ZnacheniyNebylo; // ��������, ������� ���� ����� ��������� bFlag_2
    static PlusMinus_t bFlag_4 = ZnacheniyNebylo; // ��������, ������� ���� ����� ��������� bFlag_3
    static PlusMinus_t bFlag_5 = ZnacheniyNebylo; // ��������, ������� ���� ����� ��������� bFlag_4
    static PlusMinus_t bFlag_6 = ZnacheniyNebylo; // ��������, ������� ���� ����� ��������� bFlag_5

    if ( auto_State_Flag == 50 ) // ����� �������������
    {
      auto_State_Flag = 1; // ����� ������� ��������� "���������� �������" � ������� "������������ �������� ���".
      bFlag_1 = ZnacheniyNebylo; // ������� �������� (������)
      bFlag_2 = ZnacheniyNebylo; // ��������, ������� ���� ����� ��������� bFlag_1
      bFlag_3 = ZnacheniyNebylo; // ��������, ������� ���� ����� ��������� bFlag_2
      bFlag_4 = ZnacheniyNebylo; // ��������, ������� ���� ����� ��������� bFlag_3
      bFlag_5 = ZnacheniyNebylo; // ��������, ������� ���� ����� ��������� bFlag_4
      bFlag_6 = ZnacheniyNebylo; // ��������, ������� ���� ����� ��������� bFlag_5

      Data.ptrUhiI = 0;
      Data.kodUhiI = 0;
      Data.KolAuto = 0; // ������� �������� ����������
    }

    //==\\bool bfExitFromPart1_6; // true - ����� �� ������ ����� ���������, ������� �� ������
    //==\\bool bfExitFromPart1_4; // true - ����� �� ������ ����� ���������, ������� �� ������
    bool bfExitFromPart1_2; // true - ����� �� ������ ����� ���������, ������� �� ������

    Sekunda3++;
    //!Sekunda3 = Sekunda3 % (KolVoPodinterval * 3); // KolVoPodinterval - 5 ��� 4 � ����������� �� ���������� ���������
    Sekunda3 = Sekunda3 % (KolVoPodinterval * 2); // KolVoPodinterval - 5 ��� 4 � ����������� �� ���������� ���������

    unsigned int UhiEtalon;

    if (AutoPodbor_1_Un_2_U81 == 1)
    {
      UhiEtalon = Data.m_iU + Data.m_iU0;
    }
    if (AutoPodbor_1_Un_2_U81 == 2)
    {
      UhiEtalon = (Data.m_iU * 81 + 50)/100 + Data.m_iU0; // 50 / 100 = 0.5 - ���������� �� ������
      //==// UhiEtalon = Data.m_iU * 0.81 + 0.5 + Data.m_iU0;
    }

    // <<=== 28.02.2015
    if ( Sekunda3 == 0 )
    {
      // ===>> 28.02.2015
      if ( auto_State_Flag == 1 ) // ����� ������� ��������� "���������� �������" � ������� "������������ �������� ���".
      {
        Data.delta = abs( Data.UhiI - UhiEtalon );
        if ( Data.delta == 0 )
        {
          Data.shag = 0; // ����� �� ��������� ����-�������
        }
        if ( Data.delta > 0 )
        {
          Data.shag = 1;
        }
        if ( Data.delta > 100 )
        {
          //!Data.shag = 5;
          Data.shag = 3;
        }
        if ( Data.delta > 300 )
        {
          //!Data.shag = 10;
          Data.shag = 6;
        }

        if ( Data.UhiI >= UhiEtalon )
        {
          bFlag_1 = ZnaceniePlus;
          Data.dlitelnost -= Data.shag;
          if ( Data.dlitelnost < 5 ) // ������������ ���� ������� �������
          {
            Data.dlitelnost = 5;
            auto_State_Flag = 2; // ������� � ������� ���
          }
        }
        if ( Data.UhiI < UhiEtalon )
        {
          bFlag_1 = ZnacenieMinus;
          Data.dlitelnost += Data.shag;
          if ( Data.dlitelnost > 100 ) // ������������ ���� �������� �������
          {
            Data.dlitelnost = 100;
            auto_State_Flag = 2; // ������� � ������� ���
          }
        }
        // ������ ������ �� ������ ����� ���������
        // ������� ��� ������ � ����� ������, ����� ��� ������ � ������ ������
        // ���� ��������� 6 ������� ����� ����.
        //==\\bfExitFromPart1_6 =
        //==\\  (bFlag_6 == bFlag_5) && (bFlag_5 == bFlag_4) &&
        //==\\  (bFlag_3 == bFlag_2) && (bFlag_2 == bFlag_1) &&
        //==\\  (
        //==\\    (bFlag_4 == ZnaceniePlus) && (bFlag_1 == ZnacenieMinus) ||
        //==\\    (bFlag_4 == ZnacenieMinus) && (bFlag_1 == ZnaceniePlus)
        //==\\  );
        // ������ ������ �� ������ ����� ���������
        // ������� ��� ������ � ����� ������, ����� ��� ������ � ������ ������
        // ���� ��������� 4 ������� ����� ����.
        //==\\bfExitFromPart1_4 =
        //==\\  (bFlag_4 == bFlag_3) &&
        //==\\  (bFlag_2 == bFlag_1) &&
        //==\\  (
        //==\\    (bFlag_3 == ZnaceniePlus) && (bFlag_1 == ZnacenieMinus) ||
        //==\\    (bFlag_3 == ZnacenieMinus) && (bFlag_1 == ZnaceniePlus)
        //==\\  );
        // ������ ������ �� ������ ����� ���������
        // ������� ���� ����� � ����� ������, ����� ���� ����� � ������ ������
        // ���� ��������� 2 ������ ����� ����. ���� ������� ����.
        bfExitFromPart1_2 =
          (
            (bFlag_2 == ZnaceniePlus) && (bFlag_1 == ZnacenieMinus) ||
            (bFlag_2 == ZnacenieMinus) && (bFlag_1 == ZnaceniePlus) ||
            (Data.delta < 2)
          );
        if ( bfExitFromPart1_2 == true )
        {
          auto_State_Flag = 2; // ������� � ������� ���
          Data.KolAuto = 0;  // ���������� ��������, � ������ Avto = 20 - Data.KolAuto
        }
        else
        {
          SetUhi( Data.dlitelnost );
        }

        bFlag_6 = bFlag_5;
        bFlag_5 = bFlag_4;
        bFlag_4 = bFlag_3;
        bFlag_3 = bFlag_2;
        bFlag_2 = bFlag_1;
      }
      else if ( auto_State_Flag == 2 ) // ��������� (������ ���)
      {
        //!Data.KolAuto++;  // ���������� ��������, � ������ Avto
        Data.delta = abs( Data.UhiI - UhiEtalon );

        if ( Data.delta == 0 )
        {
          Data.shag = 0;
        }
        if ( Data.delta > 0 )
        {
          //!Data.shag = 5;
          Data.shag = 3;
        }
        if ( Data.delta > 2 )
        {
          //!Data.shag = 10;
          Data.shag = 6;
        }
        if ( Data.delta > 7 )
        {
          //!Data.shag = 50;
          Data.shag = 20;
        }
        if ( Data.delta > 14 )
        {
          //!Data.shag = 100;
          Data.shag = 40;
        }
        if ( Data.delta > 27 )
        {
          //!Data.shag = 200;
          Data.shag = 80;
        }
        if ( Data.delta > 39 )
        {
          //!Data.shag = 300;
          Data.shag = 150;
        }
        if ( Data.delta > 51 )
        {
          //!Data.shag = 400;
          Data.shag = 200;
        }
        if ( Data.delta > 63 )
        {
          //!Data.shag = 500;
          Data.shag = 250;
        }
        if ( Data.delta > 75 )
        {
          //!Data.shag = 600;
          Data.shag = 300;
        }

        if ( Data.delta > 0 )
        {
          if ( Data.UhiI > UhiEtalon )
          {
            Data.period += Data.shag;
            if ( Data.period > 4095 )
            {
              Data.period = 4095;
              Data.KolPopytok++;
              auto_State_Flag = 50; // ����� ������������� (������ �������)
              if( Data.KolPopytok < 8 ) // ���������� ������� 29.09.2015)
              {
                auto_State_Flag = 50; // ����� ������������� (������ �������)
              }
              else
              {
                FlagAvtoSnyat(); // ����� ������
                auto_State_Flag = 100; // ���������� ������� ���������!!!
              }
            }
          }
          else
          {
            Data.period = Data.period - Data.shag;
            if ( Data.period < 2000 )
            {
              Data.period = 2000;
              Data.KolPopytok++;
              auto_State_Flag = 50; // ����� ������������� (������ �������)
              if( Data.KolPopytok < 8 ) // ���������� ������� 29.09.2015)
              {
                auto_State_Flag = 50; // ����� ������������� (������ �������)
              }
              else
              {
                FlagAvtoSnyat(); // ����� ������
                auto_State_Flag = 100; // ���������� ������� ���������!!!
              }
            }
          }
          SetUhi2( Data.period );
        }

        //!if ( abs( Data.UhiIsr - UhiEtalon ) < 2 ) // UhiI
        if ( Data.delta < 2 )
        {
          Data.KolAuto++;  // ���������� ��������, � ������ Avto, ����� ���������� � �����
        }

        //!if ( Data.KolAuto > 20 )
        if ( Data.KolAuto > 5 )
        {
          //if ( abs( Data.UhiIsr - UhiEtalon ) < 2 )
          if ( Data.delta < 2 )
          {
            FlagAvtoSnyat(); // ����� ������
            auto_State_Flag = -1; // ���������� ���������� �������
          }
          else
          {
            Data.KolPopytok++;
            if( Data.KolPopytok < 8 ) // ���������� ������� 29.09.2015
            {
              auto_State_Flag = 50; // ����� ������������� (������ �������)
            }
            else
            {
              FlagAvtoSnyat(); // ����� ������
              auto_State_Flag = 100; // ���������� ������� ���������!!!
            }
          }
        }
      } // end if ( auto_State_Flag == 1 )
    } // end if ( Sekunda == 0 )
  } //
}
//---------------------------------------------------------------------------
int RSProtokol_t::OprosBDParam( void )  // -1 - ������ �����, 0 - ����� ��������
{
  if ( bFlagWork == true )
  {
    if ( FlagDebug > 0 )
    {
      sprintf( Str_err, "%s", "������: ������� OprosBD ��� ��������" );
    }
    return -1;
  }
  // ===>>
  bFlagWork = true;
  this->ErrorCode = 0; // ���� ��� ��� ������
  // <<===
  Data.count2++;
  Data.flagSecond = Data.count2 % 15;
  if (Data.flagSecond == 0)
  {
    Data.count2 = 0;
  }

  NullsToStr_err(); // ������� ������ ��������� �� �������

  if( Data.flagSetTimeInterval == false )
  {
    //==\\ if ( Form_82_Start->flagModbusProtokol == 0 ) // ������ ��������: "9-�� ������"
    {
      if ( SetTimeInterval( 8 ) != 0 )
      {
	int len = strlen(Str_err);
	if (len != 0)
	{
	  sprintf(&Str_err[len], "%s", " => ������: �� (OprosBD, SetTimeInterval)");
        }
	else
	{
	  sprintf(Str_err, "%s", "������: �� (OprosBD, SetTimeInterval)");
        }
        ErrorCode = 23; // ������: �� (OprosBD, GetTimeInterval())
        bFlagWork = false;
        return -1;
      }
    }
    //===
    Data.flagSetTimeInterval = true;
    //Form_82_Start->bFlagChengeKolTik = true;  // ����������� ������� ��� �����
    //bFlagChengeKolTik = true;
  }
  if( Data.flagGetTimeInterval == false )
  {
    if ( GetTimeInterval( &Data.KolTik ) != 0 )
    {
      if (FlagDebug > 0)
      {
        int len = strlen(Str_err);
        if (len != 0)
        {
          sprintf(&Str_err[len], "%s", " => ������: �� (OprosBD, GetTimeInterval())");
        }
        else
        {
          sprintf(Str_err, "%s", "������: �� (OprosBD, GetTimeInterval())");
        }
      }
      ErrorCode = 24; // ������: �� (OprosBD, GetTimeInterval())
      bFlagWork = false;
      return -1;
    }
    Data.flagGetTimeInterval = true;
  }
  // ===
  if ( GetSSP( &Data.PSW ) != 0 ) // ����� ��������� � ����
  {
    if (FlagDebug > 0)
    {
      int len = strlen(Str_err);
      if (len != 0)
      {
        sprintf(&Str_err[len], "%s", " => ������: �� (OprosBD, GetSSP)");
      }
      else
      {
        sprintf(Str_err, "%s", "������: �� (OprosBD, GetSSP)");
      }
    }
    ErrorCode = 36; // ������: �� (OprosBD, GetSSP)
    bFlagWork = false;
    return -1; // ������ �����
  } // ����������� ��������� ��������� ��
  else
  {
    if ( ( Data.PSW & 0x01 ) == 0x01 ) // ���� ���������� ����� �������
    {
      testErr = 0;
      if ( GetCountImp(&Data.CountImp) == 0 )
      {
        Data.count++; // ���������� ���������� � �� ������ (������� ��� �������� ���� � ��)
        Data.flagFirst = Data.count % KolVoPodinterval;
        Data.TSchetTemp += Data.CountImp; // TSchetTemp - ���� �� 1 ���., CountImp - ���� �� ����������� 0,2 ��� 0,25 ���
        if ( Data.flagFirst == 0 )
        {
          Data.TSchet = Data.TSchetTemp; // TSchet - ���� �� 1 ���.
          Data.TSchetTemp = 0;
          if ( ( ( Data.count / KolVoPodinterval ) <= Data.T_Limit ) && ( Data.bFlagCount == true ) ) // ��������� ��������� ������� ����� ���������
          {
            Data.SumSchet += Data.TSchet;
            // TimeTSchet - ������� ����� ������ (� ��������) �� ������ ��������� �����
            // (����������� �� "����� ���������" ������)
            Data.TimeTSchet = Data.count / KolVoPodinterval;
            Data.TimeTSchet_dia = Data.TimeTSchet; // ��� ��������� ����: "������� ����� �����" ��� ����� ������
            if ( Data.TimeTSchet != 0 )
            {
              Data.Sred = static_cast<float>(Data.SumSchet) / static_cast<float>(Data.TimeTSchet);
            }
            else if (Data.TimeTSchet == 0)
            {
              Data.Sred = 0;
            }
          }
          else // if ( Data.count % KolVoPodinterval == 0 ) // !!!!!!!!!!!
          {
            Data.count = 0;
            Data.bFlagCount = false;
          } // end if ( ( ( Data.count / 5 or 4 ) <= Data.T_Limit ) && (Data.bFlagCount == true) )
        }
      }
      else // if ( GetCountImp(&Data.Count) != 0 )
      {
        if ( FlagDebug > 0 )
        {
          int len = strlen(Str_err);
          if ( len != 0 )
          {
            sprintf(&Str_err[len], "%s", " => ������: �� (OprosBD, GetCountImp)");
          }
	  else
	  {
	    sprintf(Str_err, "%s", "������: �� (OprosBD, GetCountImp)");
          }
        }
        ErrorCode = 37; // ������: �� (OprosBD, GetCountImp)
        bFlagWork = false;
        return -1;
      }
    }
    else
    {
      if ( FlagDebug > 0 )
      {
        // �� ����� ���� �����
        int len = strlen( Str_err );
        if ( len != 0 )
        {
	  sprintf(&Str_err[len], "%s", " => ������: �� ����� ���� ����� (OprosBD)");
        }
        else
        {
	  sprintf(Str_err, "%s", "������: �� ����� ���� ����� (OprosBD)");
        }
        //\\ErrorCode = 38; // ������: �� (OprosBD, GetCountImp)
      }
      if ( testErr > 1 )
      {
        int len = strlen( Str_err );
        if ( len != 0 )
        {
	  sprintf( &Str_err[len], "%s", " => ������: �����. ���� ���. ����� ����� 1-�� ������ ������ (OprosBD)" );
        }
        else
        {
	  sprintf( Str_err, "%s", "������: �����. ���� ���. ����� ����� 1-�� ������ ������ (OprosBD)" );
        }
        //\\ErrorCode = 39; // ������: �� (OprosBD, GetCountImp)
      }
      // ����� ��� ��������� ������, ������� �� ��������� ��������� ��������� -1
    }
  }
  // ===


  // \\if( ( Data.flagGetGrpAdr == false ) && ( Data.flagSecond == 3 ) )
  {
    if ( GetGrpAdr( &Data.GrAdr ) != 0 )
    {
      if ( FlagDebug > 0 )
      {
	int len = strlen( Str_err );
	if (len != 0)
	{
	  sprintf( &Str_err[len], "%s", " => ������: �� (OprosBD, GrAdr)" );
        }
	else
	{
	  sprintf( Str_err, "%s", "������: �� (OprosBD, GrAdr)" );
        }
      }
      ErrorCode = 26; // ������: �� (OprosBD, GrAdr)
      bFlagWork = false;
      return -1;
    }
    Data.flagGetGrpAdr = true;
  }
  // \\if ( ( Data.flagGetIndAdr == false ) && (Data.flagSecond == 4) )
  {
    if ( GetIndAdr( &Data.IndAdr ) != 0 )
    {
      if ( FlagDebug > 0 )
      {
	int len = strlen( Str_err );
	if (len != 0)
	{
	  sprintf( &Str_err[len], "%s", " => ������: �� (OprosBD, GetIndAdr)" );
        }
	else
	{
	  sprintf( Str_err, "%s", "������: �� (OprosBD, GetIndAdr)" );
        }
      }
      ErrorCode = 25; // ������: �� (OprosBD, GetIndAdr)
      bFlagWork = false;
      return -1;
    }
    Data.flagGetIndAdr = true;
  }

  // \\if ( Data.flagSecond == 5 )
  {
    if ( GetTemp( &Data.Temper ) != 0 )
    {
      if ( FlagDebug > 0 )
      {
	int len = strlen( Str_err );
	if (len != 0)
	{
	  sprintf( &Str_err[len], "%s", " => ������: �� (OprosBD, GetTemp)" );
        }
	else
	{
	  sprintf( Str_err, "%s", "������: �� (OprosBD, GetTemp)" );
        }
      }
      ErrorCode = 27; // ������: �� (OprosBD, GetTemp)
      bFlagWork = false;
      return -1;
    }
    Data.flTemper = TConvert( Data.Temper );
  }
  // \\if ( (Data.flagSecond == 6) || (CheckBox_DAuto_Checked == true) )
  {
    if ( GetDNU( &Data.DNU ) != 0 )
    {
      if ( FlagDebug > 0 )
      {
	int len = strlen( Str_err );
	if ( len != 0 )
	{
	  sprintf( &Str_err[len], "%s", " => ������: �� (OprosBD, GetDNU)" );
        }
	else
	{
	  sprintf( Str_err, "%s", "������: �� (OprosBD, GetDNU)" );
        }
      }
      ErrorCode = 28; // ������: �� (OprosBD, GetDNU)
      bFlagWork = false;
      return -1;
    }
    Data.dbDNU = Code2DAC( Data.DNU );
  }
  // \\if ( (Data.flagSecond == 7) || (CheckBox_DAuto_Checked == true) )
  {
    if ( GetDVU( &Data.DVU ) != 0 )
    {
      if ( FlagDebug > 0 )
      {
	int len = strlen( Str_err );
	if (len != 0)
	{
	  sprintf( &Str_err[len], "%s", " => ������: �� (OprosBD, GetDVU)" );
        }
	else
	{
	  sprintf( Str_err, "%s", "������: �� (OprosBD, GetDVU)" );
        }
      }
      ErrorCode = 29; // ������: �� (OprosBD, GetDVU)
      bFlagWork = false;
      return -1;
    }
    Data.dbDVU = Code2DAC( Data.DVU );
  }
  // \\if ( (Data.flagSecond == 8) || (CheckBox_auto_Checked == true) )
  {
    if ( GetUhi( &Data.UhiI ) != 0 )
    {
      if (FlagDebug > 0)
      {
	int len = strlen(Str_err);
	if (len != 0)
	{
	  sprintf(&Str_err[len], "%s", " => ������: �� (OprosBD, GetUhi)");
        }
	else
	{
	  sprintf(Str_err, "%s", "������: �� (OprosBD, GetUhi)");
        }
      }
      ErrorCode = 30; // ������: �� (OprosBD, GetUhi)
      bFlagWork = false;
      return -1;
    }

    Data.sumUhiI[Data.ptrUhiI] = Data.UhiI;
    if( Data.kodUhiI < 50 )
    {
      Data.kodUhiI++;
    }
    Data.UhiIsr = 0;
    for( unsigned int i = 0; i < Data.kodUhiI; i++ )
    {
      Data.UhiIsr = Data.UhiIsr + Data.sumUhiI[i];
    }
    Data.UhiIsr = (int)((float)Data.UhiIsr / (float)Data.kodUhiI); // ���������� �������
    Data.ptrUhiI++;
    if ( Data.ptrUhiI == 50 )
    {
      Data.ptrUhiI = 0;
    }
    Data.dbUhiIsr = Code2U( Data.UhiIsr );
  }
  // \\if ( Data.flagSecond == 9 )
  {
    if ( GetSIM3( &Data.SIM3 ) != 0 )
    {
      if ( FlagDebug > 0 )
      {
	int len = strlen( Str_err );
	if (len != 0)
	{
	  sprintf( &Str_err[len], "%s", " => ������: �� (OprosBD, GetSIM3)" );
        }
	else
	{
	  sprintf( Str_err, "%s", "������: �� (OprosBD, GetSIM3)" );
        }
      }
      ErrorCode = 31; // ������: �� (OprosBD, GetSIM3)
      bFlagWork = false;
      return -1;
    }
    Data.dbSIM3 = Data.SIM3 * 0.0596;
  }
  // \\if ( Data.flagSecond == 10 )
  {
    if ( GetSIM4( &Data.SIM4 ) != 0 )
    {
      if ( FlagDebug > 0 )
      {
	int len = strlen(Str_err);
	if ( len != 0 )
        {
	  sprintf(&Str_err[len], "%s", " => ������: �� (OprosBD, GetSIM4)");
        }
	else
	{
	  sprintf(Str_err, "%s", "������: �� (OprosBD, GetSIM4)");
        }
      }
      ErrorCode = 32; // ������: �� (OprosBD, GetSIM4)
      bFlagWork = false;
      return -1;
    }
    Data.dbSIM4 = Data.SIM4 * 0.0596;
  }
  // \\if ( Data.flagSecond == 11 )
  {
    if ( GetSIM2(&Data.SIM2) != 0 )
    {
      if ( FlagDebug > 0 )
      {
	int len = strlen(Str_err);
	if ( len != 0 )
        {
	  sprintf(&Str_err[len], "%s", " => ������: �� (OprosBD, GetSIM2)");
        }
	else
	{
	  sprintf(Str_err, "%s", "������: �� (OprosBD, GetSIM2)");
        }
      }
      ErrorCode = 33; // ������: �� (OprosBD, GetSIM2)
      bFlagWork = false;
      return -1;
    }
  }
  // \\if ( Data.flagSecond == 12 )
  {
    if ( GetLEDAmp( &Data.Ampl ) != 0 )
    {
      if ( FlagDebug > 0 )
      {
	int len = strlen(Str_err);
	if ( len != 0 )
        {
	  sprintf(&Str_err[len], "%s", " => ������: �� (OprosBD, GetLEDAmp)");
        }
	else
	{
	  sprintf(Str_err, "%s", "������: �� (OprosBD, GetLEDAmp)");
        }
      }
      ErrorCode = 34; // ������: �� (OprosBD, GetLEDAmp)
      bFlagWork = false;
      return -1;
    }
    if( Data.Ver_HEX != 0 )
    {
      if ( Data.Ver_HEX != 400 )
      {
        Data.dbAmpl = Data.Ampl * 2.5 / 255;
      }
      else
      {
        Data.dbAmpl = Data.Ampl * 4.5 / 255;
      }
    }
  }
  // \\if ( Data.flagSecond == 13 )
  {
    if ( GetLEDAmpR( &Data.LEDAmpR ) != 0 )
    {
      if ( FlagDebug > 0 )
      {
	int len = strlen( Str_err );
	if ( len != 0 )
        {
	  sprintf( &Str_err[len], "%s", " => ������: �� (OprosBD, GetLEDAmpR)" );
        }
	else
	{
	  sprintf( Str_err, "%s", "������: �� (OprosBD, GetLEDAmpR)" );
        }
      }
      ErrorCode = 35; // ������: �� (OprosBD, GetLEDAmpR)
      bFlagWork = false;
      return -1;
    }
    Data.LEDAmp[Data.ptrLEDAmp] = Data.LEDAmpR;
    if ( Data.kodLEDAmp < 150 )
    {
      Data.kodLEDAmp++;
    }
    Data.LEDAmpRcp = 0;
    for ( int i = 0; i < Data.kodLEDAmp; i++ )
    {
      Data.LEDAmpRcp += Data.LEDAmp[i];
    }
    Data.LEDAmpRcp /= (float)Data.kodLEDAmp;
    Data.ptrLEDAmp++;
    if ( Data.ptrLEDAmp == 150 )
    {
      Data.ptrLEDAmp = 0;
    }
    if( Data.Ver_HEX != 0 )
    {
      if ( Data.Ver_HEX != 400 )
      {
        Data.dbLEDAmpRcp = Data.LEDAmpRcp * 2.5 / 255;
      }
      else
      {
        Data.dbLEDAmpRcp = Data.LEDAmpRcp * 4.5 / 255;
      }
    }
  }
  // ==== ===== ===== 12.01.2016 ===>>
  if ( flagModbusProtokol != 0 ) // ������ ��������: �� "9-�� ������"
  {
    uint16_t Dest[2];
    int ReadCount = read_registers(AddrBD, 100, 2, Dest);
    if (ReadCount == 2)
    {
      Data.TimeZapuskBD = (unsigned int)((Dest[1] << 16) | Dest[0]);
    }
  }
  // ==== ===== ===== 12.01.2016 <<===

  AvtoPodborUhiIter();

  //bool AvtoDnu = false;
  //bool AvtoDvu = false;

  if ( CheckBox_DAuto_Checked == true )
  {

    if ( AvtoDnu() == false )
    {
      double dDnu = Code2DAC( Data.DNU );
      double dAbsDnu = fabs( Data.m_fltDac0 - dDnu );
      if ( 0.001 < dAbsDnu )
      {
        Data.m_iDac0 = Clamp(Data.m_iDac0 + UpdatePID0(Data.m_fltDac0 - Code2DAC(Data.DNU)), 0, 0x0fff);
        SetDNU( Data.m_iDac0 );
      }
      else
      {
        ResetPID0();
      }
    }
    // ���������� �� ������ �������������� �������� ������ ���
    if ( AvtoDvu() == false )
    {
      double dDvu = Code2DAC( Data.DVU );
      double dAbsDvu = fabs( Data.m_fltDac1 - dDvu );
      if ( 0.001 < dAbsDvu )
      {
        Data.m_iDac1 = Clamp(Data.m_iDac1 + UpdatePID1(Data.m_fltDac1 - Code2DAC(Data.DVU)), 0, 0x0fff);
        SetDVU( Data.m_iDac1 );
      }
      else
      {
        ResetPID1();
      }
    }
    if ( IsPidSResetted() )
    {
      CheckBox_DAuto_Checked = false;
      FlagAvtoSnyatDiskr(); // ����� ������; // �������� ������
    }
  }
  // ==== ===== =====
  testErr++;
  // ������� ���� �� 0.2 ���
  ///////////
  //extern PACKAGE System::TDateTime __fastcall Date(void);
  //extern PACKAGE System::TDateTime __fastcall Time(void);
  //extern PACKAGE System::TDateTime __fastcall Now(void);
  DecodeTime(Time(), ArrTimeTek.Hour, ArrTimeTek.Min, ArrTimeTek.Sec, ArrTimeTek.MSec);
  //DecodeDate(const System::TDateTime DateTime, Word &Year, Word &Month, Word &Day);
  //EncodeDate(Word Year, Word Month, Word Day);

  ArrTime[indexArrTime].Hour = ArrTimeTek.Hour;
  ArrTime[indexArrTime].Min = ArrTimeTek.Min;
  ArrTime[indexArrTime].Sec = ArrTimeTek.Sec;
  ArrTime[indexArrTime].MSec = ArrTimeTek.MSec;
  ArrTime[indexArrTime].PSW_b0 = ArrTimeTek.PSW_b0;
  ArrTime[indexArrTime].PSW_b1 = ArrTimeTek.PSW_b1;
  ///////////////////////////////////////////////////////////////////
  ArrTime[indexArrTime].flagFirst = Data.flagFirst;
  ArrTime[indexArrTime].flagSecond = Data.flagSecond;
  ArrTime[indexArrTime].count = Data.count;
  if ( (Data.PSW & 0x01) == 0x01 )
  {
    ArrTime[indexArrTime].PSW_b0 = 1;
    N0++; // ���������� ��������� ���������� ����� (PSW_b0 == 1)
  }
  else
  {
    ArrTime[indexArrTime].PSW_b0 = 0;
  }
  //
  if ( (Data.PSW & 0x02) == 0x02 )
  {
    ArrTime[indexArrTime].PSW_b1 = 1;
    N1++; // ���������� ��������� ��������� ����� (PSW_b1 == 1)
  }
  else
  {
    ArrTime[indexArrTime].PSW_b1 = 0;
  }
  if (MaxIndexArrTime < 100)
  {
    MaxIndexArrTime++;
  }
  indexArrTime++;
  if (indexArrTime == 100)
  {
    indexArrTime = 0;
  }

  //===>>
  ev_OprosBDParam();
  //if (Form_82_Start->bfZvukOn == true)
  //{
  //  Form_82_Start->bfZvukOn = false;
  //  Form_82_Start->ZvukOn();
  //}
  //if (Form_82_Start->bfZvukOff == true)
  //{
  //  Form_82_Start->bfZvukOff = false;
  //  Form_82_Start->ZvukOff();
  //}
  //<<===
  return 0; // ������� ����������
}
//---------------------------------------------------------------------------
/// ����� ���������� ������ ��� ����������� ���������������
bool RSProtokol_t::IsPidSResetted()
{
  bool flag = true;
  flag &= (I_State0 == 0);
  flag &= (I_State1 == 0);
  flag &= (I_Error0 == 0);
  flag &= (I_Error1 == 0);
  return flag;
}
//---------------------------------------------------------------------------
int RSProtokol_t::OprosBD( void ) // -1 - ������ �����, 0 - ����� ��������
{
  int iRetValue;
  iRetValue = OprosBDParam(); // 0 - �����

  if ( iRetValue != 0 )
  {
    bFlagWork = false;
    return iRetValue;
  }

  if ( bfOprosSpectra == true )
  {
    bfOprosSpectra = bfOprosSpectra;
    iRetValue = OprosBDSpektr( true, & Data.TimeNaboraSpectr, & Data.TimeGotovSpectr ); // false - �� �������� �����
  }
  bFlagWork = false;
  if ( iRetValue != 0 )
  {
    return iRetValue;
  }
  return 0;
}
//---------------------------------------------------------------------------
void RSProtokol_t::OprosSpectra(bool bf) // bf = true - ��������� ����� ������� � ������� OprosBD()
{
  bfOprosSpectra = bf;
  if ( bf == true )
  {
    bfPervVhod = true; // ������ ���� � �������
  }
}
//---------------------------------------------------------------------------
int RSProtokol_t::DiaGetTime(void) // ������� ����� � ������������
{
  int iTime;
  int iTime2;
  unsigned short Hour;
  unsigned short Min;
  unsigned short Sec;
  unsigned short MSec;
  DecodeTime(Time(), Hour, Min, Sec, MSec);
  //==\\iTime = 60 * 60 * 1000 * Hour + 60 * 1000 * Min + 1000 * Sec + MSec;
  iTime =  (((Hour * 60) + Min) * 60 + Sec) * 1000 + MSec;
  return iTime;
}
//---------------------------------------------------------------------------
void RSProtokol_t::ClearBDSpectr(void)
{
  ObnulenieArr(Data.ArrSpectrSumm, 512, 0); //==\\
  Data.iSpektrZaprosCount = 0; // ���������� ������� ������� ���������
  Data.TimeNaboraSpectr = 0; // ����� ������ �������
  Data.TimeGotovSpectr = 0; // ����� ���������� �������
}
//---------------------------------------------------------------------------
int RSProtokol_t::OprosBDSpektr(bool bfTime, int * iTimeRead, int * iTimeGotov ) // -1 - ������ �����, 0 - ����� ��������
{
  // iTimeRead - ����� ������ �������
  // iTimeGotovh - ����� ���������� �������
  int iRet;
  unsigned char Interval;
  int iTime_read_0;
  int iTime_read_1;

  static int iTimeDeltaRead_0;
  static int iTimeDeltaRead_1;

  static int iTime_got_0;
  static int iTime_got_1;


  int iNeUdachnyiObmen;
  int iNeGotovSpektr;
  int iTimeGotov_Tmp;

  if ( this->Data.bfSetTimeSpektr == false ) // ������ ������ ������ �������
  {
    //Data.KolTikSpectr = Form_82_Spectr_BD84->SpinEdit_TimeSpektr->Value;
    iRet = SetTimeSpectr( Data.KolTikSpectr ); // KolTikSpectr
    if (iRet != 0)
    {
      return -1;
    }
    iRet = GetTimeSpectr(&Interval);
    if (iRet != 0)
    {
      return -1;
    }
    if(Interval != Data.KolTikSpectr)
    {
      return -1;
    }
    this->Data.bfSetTimeSpektr = true;
  }
  if ( this->Data.FlagWriteKolTikSpektr == true ) // ������ ������ "������"
  {
    //Data.KolTikSpectr = Form_82_Spectr_BD84->SpinEdit_TimeSpektr->Value;
    iRet = SetTimeSpectr( Data.KolTikSpectr ); // KolTikSpectr
    if (iRet != 0)
    {
      return -1;
    }
    iRet = GetTimeSpectr(&Interval);
    if (iRet != 0)
    {
      return -1;
    }
    if(Interval != Data.KolTikSpectr)
    {
      return -1;
    }
    this->Data.FlagWriteKolTikSpektr = false;
  }
  if( this->Data.bf_SpectrStart == true )
  {
    iRet = SpectrStart();
    if (iRet != 0)
    {
      return -1;
    }
    this->Data.bf_SpectrStart = false;
  }
  ObnulenieArr(Data.ArrSpectr, 512, 0);
  iNeUdachnyiObmen = 0;
  iNeGotovSpektr = 0;
  while ( true )
  {
    int iVar;
    iVar = GetSSP( &Data.PSW );
    if ( iVar == 0 ) // ������� �����
    {
      if ( ( Data.PSW & 0x04) == 0x04 ) // ������ �����
      {
        break; // �����
      }
      else
      {
        iNeGotovSpektr++;
      }
    }
    else
    {
      iNeUdachnyiObmen++;
    }
    if ( iNeGotovSpektr >= 100000 ) // ��� ���������� ������� 100 000 ��� ������
    {
      break; // ������ ���������� �������
    }
    if ( iNeUdachnyiObmen >= 3 )
    {
      return -1; // ������ ������
    }
  }

  if ( ( Data.PSW & 0x04) == 0x04 )
  {
    if ( bfTime == true ) // ��������� ���������� ��������� ���������
    {
      iTime_got_1 = DiaGetTime(); // ����� ���������� �������� ���������� [��]
      iTime_read_0 = iTime_got_1; // ����� ������ ������ ������� [��]
      if ( bfPervVhod == false ) // ������ � ����������� ������ � ��� ����� ������� (����� ���������)
      {
        iTimeGotov_Tmp = iTime_got_1 - iTime_got_0; // �������� �������� ����������
      }
      iTime_got_0 = iTime_got_1; // ����� ������ �������� ���������� = ����� ���������� �������� ���������� [��]
    }
    for (int nomBlock = 0; nomBlock < 32; nomBlock++) //==\\
    {
      ObnulenieArr(Data.ArrSpectrBlock, 16);
      iRet = SpectrReadBuf( nomBlock, &Data.ArrSpectrBlock[0] );
      if ( iRet != 0 )
      {
        return -1;
      }
      for (int i = 0; i < 16; i++)
      {
        this->Data.ArrSpectr[nomBlock*16+i] = this->Data.ArrSpectrBlock[i];
      }
    }
  }
  else
  {
    this->Data.iSpektrZaprosErr++; // ���������� ������ ������ �������� (������)
  }

  if ( this->Data.iSpektrZaprosErr >= 3 )
  {
    iRet = SpectrStart(); // �������� ������ ����� �������
    this->Data.iSpektrZaprosErr = 0;
  }

  if ( bfTime == true ) // ��������� ���������� ��������� ���������
  {
    if ( ( Data.PSW & 0x04 ) == 0x04 )
    {
      iTime_read_1 = DiaGetTime(); // ����� ���������� ������ ������� [��]
      iTimeDeltaRead_1 = iTime_read_1 - iTime_read_0; // ������� �������� ������ �������
      // ===>>
      for (int i = 0; i < 512; i++)
      {
        this->Data.ArrSpectrSumm[i] += (int)this->Data.ArrSpectr[i];
      }
      this->Data.iSpektrZaprosCount++; // ���������� ������� ������� ��������
      this->Data.iSpektrZaprosErr = 0; // ���������� ������ ������ �������� (������)
      iRet = SpectrStart(); // �������� ������ ����� �������
      // <<===
      if ( bfPervVhod == true ) // ������ ����� � �������, ����� ���������
      {
        * iTimeRead = 0;
        * iTimeGotov = 0;
        bfPervVhod = false;
      }
      else // ������ � ����������� ������ � ��� ����� ������� (����� ���������)
      {
        * iTimeRead = iTimeDeltaRead_0; // ���������� �������� ������ ������� [��]
        * iTimeGotov = iTimeGotov_Tmp - iTimeDeltaRead_0; // �������� �������� ���������� - ���������� �������� ������ ������� [��]
      }
      iTimeDeltaRead_0 = iTimeDeltaRead_1; // ���������� �������� ������ ������� [��] = ������� �������� ������ ������� [��]
    }
  } 
  return 0;
}
//---------------------------------------------------------------------------
void RSProtokol_t::ObnulenieArr(unsigned char Arr[], int N, unsigned char uchVal)
{
  for (int i = 0; i < N; i++)
  {
    Arr[i] = uchVal;
  }
}
//---------------------------------------------------------------------------
void RSProtokol_t::ObnulenieArr(int Arr[], int N, unsigned char uchVal)
{
  for (int i = 0; i < N; i++)
  {
    Arr[i] = uchVal;
  }
}
//---------------------------------------------------------------------------
// �������������� ���������� �� ������ �������������� (�������/��������) ������ �� ���� � ������
double RSProtokol_t::Code2DAC(int var)
{
  if ( Data.Ver_HEX != 400 )
  {
    return (var * 2.5 / 4096) * 1.1;
  }
  else
  {
    return (var * 4.5 / 4096) * 1.1;  
  }
}
//---------------------------------------------------------------------------
// �������������� �������� ����������� �� ���� � ������� �������
float RSProtokol_t::TConvert(int Temper)
{
  //==\\float g_fltTSlope = -0.3389;
  //==\\float g_fltTOffset = 378.95;
  //==\\return g_fltTSlope * (float)var + g_fltTOffset;
  float g_fltTSlope;
  float g_fltTOffset;
  float g_Temper;

  if (Data.Ver_HEX != 0)
  {
    if (Data.Ver_HEX != 400)
    {
      g_fltTSlope = -0.3389;
      g_fltTOffset = 378.95;
    }
    else
    {
      //===>> 05.04.2018
      // ������������ �� ��������

      //g_fltTSlope = -0.714;
      //g_fltTOffset = 486.4;

      //g_fltTSlope = -0.704;
      //g_fltTOffset = 476.1;

      g_fltTSlope = -0.6875;
      g_fltTOffset = 463.78;

      // ������������ �� ��������
      //<<===
    }
    g_Temper = g_fltTSlope * Temper + g_fltTOffset;
  }
  else
  {
    g_Temper = 0;
  }
  return g_Temper;
}
//---------------------------------------------------------------------------
// �������������� ���������� (����������� �� 50-�� ���������) �� ���� � ������
double RSProtokol_t::Code2U( int var )
{
  if ( Data.Ver_HEX != 400 )
  {
    return var * 2.5 / 4096 * 1000;
  }
  else
  {
    return var * 4.5 / 4096 * 1000;
  }
}
//---------------------------------------------------------------------------
int RSProtokol_t::OprosBD_2(void) // -1 - ������ �����, 0 - ����� ��������
{
  if (bFlagWork == true)
  {
    if ( FlagDebug > 0 )
    {
      sprintf( Str_err, "%s", "������: ������� OprosBD_2 ��� ��������" );
    }
    return -1;
  }
  // ===>>
  bFlagWork = true;
  // <<===
  Data.flagSecond = 0; // ��������� ������
  // ===>>
  if ( Data.flagGetVersion == false )
  {
    if ( GetVersia( Data.Ver ) != 0 )
    {
      if ( FlagDebug > 0 )
      {
	int len = strlen( Str_err );
	if (len != 0)
	{
	  sprintf( &Str_err[len], "%s", " => ������: �� (OprosBD, GetVersia)" );
        }
	else
	{
	  sprintf( Str_err, "%s", "������: �� (OprosBD, GetVersia)" );
        }
      }
      ErrorCode = 23; // ������: �� �� �������� (OprosBD, GetVersia)
      bFlagWork = false;
      return -1;
    }
    Data.Ver_HEX = (Data.Ver[0] - '0')*100;
    if ( Data.Ver[0] == '4' ) //
    {
      flagSpeed = false; // � ������ ������� ���� ������ ������ ����
    }
    Data.flagGetVersion = true;
  }
  // <<===
  if ( Data.flagSecond == 0 )
  {
    if ( ReadFlashInvert( 0, &Data.DNUZ ) != 0 )
    {
      if (FlagDebug > 0)
      {
        sprintf( Str_err, "������: �� (OprosBD_2, DNUZ)" );
      }
      ErrorCode = 40; // ������: �� (OprosBD_2, DNUZ)
      bFlagWork = false;
      return -1;
    }
    Data.DNUZ &= 0x0000FFFF;
  }
  if ( Data.flagSecond == 0 )
  {
    if ( ReadFlashInvert( 0x01, &Data.DVUZ ) != 0 )
    {
      if (FlagDebug > 0)
      {
        sprintf(Str_err, "������: �� (OprosBD_2, DVUZ)");
      }
      ErrorCode = 41; // ������: �� (OprosBD_2, DVUZ)
      bFlagWork = false;
      return -1;
    }
    Data.DVUZ &= 0x0000FFFF;
  }
  if ( Data.flagSecond == 0 )
  {
    if ( ReadFlashInvert( 0x02, &Data.LEDAmpZ ) != 0 )
    {
      if (FlagDebug > 0)
      {
        sprintf( Str_err, "������: �� (OprosBD_2, LEDAmpZ)" );
      }
      ErrorCode = 42; // ������: �� (OprosBD_2, LEDAmpZ)
      bFlagWork = false;
      return -1;
    }
    Data.LEDAmpZ &= 0x0000FFFF;
  }
  if ( Data.flagSecond == 0 )
  {
    if ( ReadFlashInvert( 0x03, &Data.UhiZ ) != 0 )
    {
      if ( FlagDebug > 0 )
      {
        sprintf( Str_err, "������: �� (OprosBD_2, UhiZ)" );
      }
      ErrorCode = 43; // ������: �� (OprosBD_2, UhiZ)
      bFlagWork = false;
      return -1;
    }
    Data.UhiZ &= 0x0000FFFF;
  }
  if ( Data.flagSecond == 0 )
  {
    int errSvyaz;
    if ( flagModbusProtokol == 0 ) // 9-������
    {
      errSvyaz = ReadFlashInvert( 0x04, &Data.IndAdrZ );
    }
    if ( flagModbusProtokol != 0 ) // ModBus RTU, ModBus TCP, ModBus RTU (TCP/IP)
    {
      errSvyaz = ReadFlash2( 0x300+1, &Data.IndAdrZ );
    }
    if ( errSvyaz != 0 )
    {
      if (FlagDebug > 0)
      {
        sprintf( Str_err, "������: �� (OprosBD_2, IndAdrZ)" );
      }
      ErrorCode = 44; // ������: �� (OprosBD_2, IndAdrZ)
      bFlagWork = false;
      return -1;
    }
    Data.IndAdrZ &= 0x000000FF;
  }
  if ( Data.flagSecond == 0 )
  {
    if ( ReadFlashInvert( 5, &Data.GrpAdrZ ) != 0 )
    {
      if (FlagDebug > 0)
      {
    	sprintf( Str_err, "������: �� (OprosBD_2, GrpAdrZ)" );
      }
      ErrorCode = 45; // ������: �� (OprosBD_2, GrpAdrZ)
      bFlagWork = false;
      return -1;
    }
    Data.GrpAdrZ &= 0x000000FF;
  }
  if ( Data.flagSecond == 0 )
  {
    if ( ReadFlashInvert( 0x07, &Data.SIMstartZ ) != 0 )
    {
      if (FlagDebug > 0)
      {
    	sprintf( Str_err, "������: �� (OprosBD_2, SIMstartZ)" );
      }
      ErrorCode = 46; // ������: �� (OprosBD_2, SIMstartZ)
      bFlagWork = false;
      return -1;
    }
    Data.SIMstartZ &= 0x0000FFFF;
  }
  if ( Data.flagSecond == 0 )
  {
    if ( ReadFlashInvert( 0x09, &Data.SIMminZ ) != 0 )
    {
      if (FlagDebug > 1)
      {
    	sprintf( Str_err, "������: �� (OprosBD_2, SIMstartZ)" );
      }
      ErrorCode = 47; // ������: �� (OprosBD_2, SIMstartZ)
      bFlagWork = false;
      return -1;
    }
    Data.SIMminZ &= 0x0000FFFF;
  }
  if ( Data.flagSecond == 0 )
  {
    if ( ReadFlash( 0x2B, &Data.LedZadZ ) != 0 )
    {
      if (FlagDebug > 0)
      {
    	sprintf( Str_err, "������: �� (OprosBD_2, LedZadZ)" );
      }
      ErrorCode = 48; // ������: �� (OprosBD_2, LedZadZ)
      bFlagWork = false;
      return -1;
    }
    Data.LedZadZ &= 0x000000FF;
  }
  if ( Data.flagSecond == 0 )
  {
    if ( ReadFlashInvert( 10, &Data.m_ulSerialNumberZ ) != 0 )
    {
      if (FlagDebug > 0)
      {
    	sprintf(Str_err, "������: �� (OprosBD_2, m_ulSerialNumberZ)");
      }
      ErrorCode = 49; // ������: �� (OprosBD_2, m_ulSerialNumberZ)
      bFlagWork = false;
      return -1;
    }
  }
  if ( Data.flagSecond == 0 )
  {
    if ( ReadFlashInvert( 11, &Data.m_ulU0Z ) != 0 )
    {
      if ( FlagDebug > 0 )
      {
    	sprintf( Str_err, "������: �� (OprosBD_2, m_ulU0Z)" );
      }
      ErrorCode = 50; // ������: �� (OprosBD_2, m_ulU0Z)
      bFlagWork = false;
      return -1;
    }
  }
  if ( Data.flagSecond == 0 )
  {
    if ( ReadFlashInvert( 12, &Data.m_ulUZ ) != 0 )
    {
      if ( FlagDebug > 0 )
      {
        sprintf( Str_err, "������: �� (OprosBD_2, m_ulUZ)" );
      }
      ErrorCode = 51; // ������: �� (OprosBD_2, m_ulUZ)
      bFlagWork = false;
      return -1;
    }
  }
  if ( Data.flagSecond == 0 )
  {
    if ( GetStickyNote( (char*)&Data.m_strStickyNote[0] ) != 0 )
    {
      if ( FlagDebug > 0 )
      {
        sprintf(Str_err, "������: �� (OprosBD_2, m_strStickyNote)");
      }
      ErrorCode = 52; // ������: �� (OprosBD_2, m_strStickyNote)
      bFlagWork = false;
      return -1;
    }
  }
  if ( Data.flagSecond == 0 )
  {
    if ( ReadFlashInvert( 8, &Data.DlInterPhon ) != 0 )
    {
      if ( FlagDebug > 0 )
      {
        sprintf( Str_err, "������: �� (OprosBD_2, DlInterPhon)" );
      }
      ErrorCode = 53; // ������: �� (OprosBD_2, DlInterPhon)
      bFlagWork = false;
      return -1;
    }
  }
  if ( Data.flagSecond == 0 )
  {
    if ( GetSSP( &Data.PSW ) != 0 ) // ����� ��������� � ����
    {
      bFlagWork = false;
      flagARCH = -1;
      flagUchSv = -1;
      return -1;
    }
    else
    {
      if ( ( Data.PSW & 0x10 ) == 0x10 )
      { // ��������� ��� (���/����)
        flagARCH = 1; // ��� ���������
      }
      else
      { // ��� ��������
        if ( ( Data.PSW & 0x20 ) == 0x20 )
        { // ��������� ��� (���/����)
          flagARCH = 2; // ������
        }
        else
        {
          flagARCH = 3; // �����������
        }
      } //===
      if ( ( Data.PSW & 0x08 ) == 0x08  )
      {
        flagUchSv = 1; // �������� �������� ����������
      }
      else
      {
        flagUchSv = 2; // ��������� �������� ����������
      }
    }
  }
  bFlagWork = false;
  return 0;
}
//---------------------------------------------------------------------------
// ���������� �������������� ����� ��
int RSProtokol_t::SetIndAdr(unsigned char Adr)
{
  this->buf_write[0] = 0x13;
  this->buf_write[1] = 184;
  this->buf_write[2] = 112;
  this->buf_write[3] = 235;
  this->buf_write[4] = Adr;
  CodeRet = this->CommandExec(4, 1);
  return this->CodeRet;
}
//---------------------------------------------------------------------------
// ���������� ��������� ����� ��
int RSProtokol_t::SetGrpAdr(unsigned char Adr)
{
  this->buf_write[0] = 0x15;
  this->buf_write[1] = 184;
  this->buf_write[2] = 112;
  this->buf_write[3] = 235;
  this->buf_write[4] = Adr;
  CodeRet = this->CommandExec(4, 1);
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
// ������ ��� ����������
int RSProtokol_t::SetLEDAmp(unsigned int Amp)
{
  this->buf_write[0] = 0x1A;
  this->buf_write[1] = 184;
  this->buf_write[2] = 112;
  this->buf_write[3] = 235;
  this->buf_write[4] = Amp;
  this->buf_write[5] = Amp >> 8;
  this->CodeRet = CommandExec(5, 1);
  return this->CodeRet;
}
//---------------------------------------------------------------------------
// ���������� �������� �������� ����������
int RSProtokol_t::SetUhi(unsigned int Uhi)
{
  this->buf_write[0] = 0x19;
  this->buf_write[1] = 184; // B8
  this->buf_write[2] = 112; // 70
  this->buf_write[3] = 235; // EB
  this->buf_write[4] = Uhi;
  this->buf_write[5] = (Uhi >> 8) & 0xff;
  this->CodeRet = CommandExec(5, 1);
  return this->CodeRet;
}
//---------------------------------------------------------------------------
// ������� �������� �������� ����������
int RSProtokol_t::GetUhi(unsigned int * UhiI)
{
  this->buf_write[0] = 0x07;
  this->CodeRet = CommandExec(0, 2);
  if (this->CodeRet == 0) // ��� ������ ������
  {
    *UhiI = this->buf_read[1] * 256 + this->buf_read[0];
  }
  else // ������ ������
  {
    *UhiI = 0;
  }
  return this->CodeRet;
}
//---------------------------------------------------------------------------
// ���������� ������ ���
int RSProtokol_t::SetUhi2(unsigned int Uhi)
{
  this->buf_write[0] = 0x1B;
  this->buf_write[1] = 184;
  this->buf_write[2] = 112;
  this->buf_write[3] = 235;
  this->buf_write[4] = Uhi;
  this->buf_write[5] = (Uhi >> 8) & 0xff;
  this->CodeRet = CommandExec(5, 1);
  return this->CodeRet;
}
//------------------------------------------------------------------------------
// �������� ����� ��������� ��������� ��   (��� ���������� �����)(��� ����, �� � ������ ��������)
int RSProtokol_t::SetSSP(unsigned char SSP)
{
  unsigned long Data = SSP;
  this->CodeRet = WriteFlash(0x06, Data);
  return this->CodeRet;
}
//---------------------------------------------------------------------------
// ������ ��� ����������
int RSProtokol_t::SetLEDOtkl(unsigned int Amp)
{
  this->buf_write[0] = 0x1E;
  this->buf_write[1] = 184;
  this->buf_write[2] = 112;
  this->buf_write[3] = 235;
  this->buf_write[4] = Amp;
  this->buf_write[5] = Amp >> 8;
  this->CodeRet = CommandExec(5, 1);
  return this->CodeRet;
}
//---------------------------------------------------------------------------
int RSProtokol_t::SetSerialNumber(unsigned int uiSerialNumber)
{
  return WriteFlashInvert(10, uiSerialNumber);
}
//---------------------------------------------------------------------------
int RSProtokol_t::SetU0(unsigned int uiU0)
{
  return WriteFlashInvert(11, uiU0);
}
//---------------------------------------------------------------------------
int RSProtokol_t::SetU(unsigned int uiU)
{
  return WriteFlashInvert(12, uiU);
}
//---------------------------------------------------------------------------
// ������ 4-� ���� ������ �� FLASH/EE DATA MEMORY ����������
int RSProtokol_t::WriteFlashInvert(unsigned int Adr, unsigned long Data)
{
  union {
    unsigned long tData;
    unsigned char mDATA[4];
  } outdata;
  outdata.tData = Data;
  this->buf_write[0] = 0x01;
  this->buf_write[1] = 184;
  this->buf_write[2] = 112;
  this->buf_write[3] = 235;
  this->buf_write[4] = Adr & 0x00FF;
  this->buf_write[5] = (Adr >> 8) & 0x0003;
  this->buf_write[6] = ~outdata.mDATA[0];
  this->buf_write[7] = ~outdata.mDATA[1];
  this->buf_write[8] = ~outdata.mDATA[2];
  this->buf_write[9] = ~outdata.mDATA[3];
  this->CodeRet = CommandExec(9, 1);
  return this->CodeRet;
}
//---------------------------------------------------------------------------
// ������ 4-� ���� ������ �� FLASH/EE DATA MEMORY ����������
int RSProtokol_t::WriteFlash(unsigned int Adr, unsigned long Data)
{
  union {
    unsigned long tData;
    unsigned char mDATA[4];
  } outdata;
  outdata.tData = Data;
  buf_write[0] = 0x01;
  buf_write[1] = 184;
  buf_write[2] = 112;
  buf_write[3] = 235;
  buf_write[4] = Adr & 0x00FF;
  buf_write[5] = (Adr >> 8) & 0x0003;
  buf_write[6] = outdata.mDATA[0];
  buf_write[7] = outdata.mDATA[1];
  buf_write[8] = outdata.mDATA[2];
  buf_write[9] = outdata.mDATA[3];
  CodeRet = CommandExec(9, 1);
  return CodeRet;
}
//---------------------------------------------------------------------------
// ������ 4-� ���� ������ �� FLASH/EE DATA MEMORY ����������
int RSProtokol_t::WriteFlash2(unsigned int Adr, unsigned long Data)
{
  union {
    unsigned long tData;
    unsigned char mDATA[4];
  } outdata;
  outdata.tData = Data;
  buf_write[0] = 0x01;
  buf_write[1] = 184;
  buf_write[2] = 112;
  buf_write[3] = 235;
  buf_write[4] = Adr & 0x00FF;
  buf_write[5] = (Adr >> 8) & 0x0003;
  buf_write[6] = outdata.mDATA[3];
  buf_write[7] = outdata.mDATA[2];
  buf_write[8] = outdata.mDATA[1];
  buf_write[9] = outdata.mDATA[0];
  CodeRet = CommandExec(9, 1);
  return CodeRet;
}
//---------------------------------------------------------------------------
// �������� �����������
int RSProtokol_t::SetStickyNote(char * strStickyNote)
{
  //!for (int i = 0, addr = 0x0d; i < 32; i += 4, addr++)
  for (int i = 0, addr = 0x0d; i < 24; i += 4, addr++)//! 09.02.2018
  {
    WORD lo = MAKEWORD(strStickyNote[i + 0], strStickyNote[i + 1]);
    WORD hi = MAKEWORD(strStickyNote[i + 2], strStickyNote[i + 3]);
    if ( WriteFlashInvert(addr, MAKELONG(lo, hi)) != 0 )
    {
      return -1;
    }
  }
  return 0;
}
//---------------------------------------------------------------------------
float RSProtokol_t::Clamp(float fltValue, float fltMin, float fltMax)
{
  if (fltValue > fltMax)
  {
    return fltMax;
  }
  if (fltValue < fltMin)
  {
    return fltMin;
  }
  return fltValue;
}
//---------------------------------------------------------------------------
double RSProtokol_t::UpdatePID0(double error)
{
  DOUBLE pTerm, iTerm;
  // Calculate the proportional term.
  pTerm = P_Gain0 * error;
  // Calculate the integral state with appropriate limiting.
  if ((I_Error0 > 0 && error < 0) || (I_Error0 < 0 && error > 0))
  {
	I_State0 = 0;
	I_Error0 = 0;
  }
  I_State0 = Clamp(I_State0 + error, I_Min0, I_Max0);
  I_Error0 = error;
  // Calculate the integral term.
  iTerm = I_Gain0 * I_State0;
  return Clamp(pTerm + iTerm, DRIVE0_MIN, DRIVE0_MAX);
}
//---------------------------------------------------------------------------
double RSProtokol_t::UpdatePID1(double error)
{
  double pTerm, iTerm;
  // Calculate the proportional term.
  pTerm = P_Gain1 * error;

  // Calculate the integral state with appropriate limiting.
  if ((I_Error1 > 0 && error < 0) || (I_Error1 < 0 && error > 0))
  {
    I_State1 = 0;
    I_Error1 = 0;
  }
  I_State1 = Clamp(I_State1 + error, I_Min1, I_Max1);
  I_Error1 = error;
  // Calculate the integral term.
  iTerm = I_Gain1 * I_State1;
  return Clamp(pTerm + iTerm, DRIVE1_MIN, DRIVE1_MAX);
}
//---------------------------------------------------------------------------
/*double RSProtokol_t::UpdatePID(double error, double position)
{
  double pTerm, iTerm;
  // Calculate the proportional term.
  pTerm = P_Gain * error;
  // Calculate the integral state with appropriate limiting.
  if ((I_Error > 0 && error < 0) || (I_Error < 0 && error > 0))
  {
    I_State = 0;
    I_Error = 0;
  }
  I_State = Clamp(I_State + error, I_Min, I_Max);
  I_Error = error;
  // Calculate the integral term.
  iTerm = I_Gain * I_State;
  return Clamp(pTerm + iTerm, DRIVE_MIN, DRIVE_MAX);
}*/
//---------------------------------------------------------------------------
void RSProtokol_t::ResetPID(void)
{
  I_State1 = 0;
  I_Error1 = 0;
}
//---------------------------------------------------------------------------
void RSProtokol_t::ResetPID0(void)
{
  I_State0 = 0;
  I_Error0 = 0;
  bf_AvtoDnu = true;
}
//---------------------------------------------------------------------------
bool RSProtokol_t::AvtoDnu()
{
  return bf_AvtoDnu;
}
//---------------------------------------------------------------------------
void RSProtokol_t::ResetPID1(void)
{
  I_State1 = 0;
  I_Error1 = 0;
  bf_AvtoDvu = true;
}
//---------------------------------------------------------------------------
bool RSProtokol_t::AvtoDvu()
{
  if (bf_WriteDef_DVU == true)
  {
    bf_WriteDef_DVU = false;
    SetDVU(4095);
  }
  return bf_AvtoDvu;
}
//---------------------------------------------------------------------------
void RSProtokol_t::Set_CheckBox_DAuto_Checked(bool dNu, bool dVu) // 2018.03.19
{
  bf_WriteDef_DVU = false;
  if (dNu == false && dVu == true)
  {
    bf_WriteDef_DVU = true;
  }
  bf_AvtoDnu = dNu;
  bf_AvtoDvu = dVu;
}
//---------------------------------------------------------------------------
// ������ holding �������� � �������� ������ � ������ dest
int RSProtokol_t::read_registers(
    int BDAddr, // ����� ��
    int REGAddr, // ����� ��������
    int nb, // ����� ���������
    uint16_t * dest) // ������
{
  typedef enum
  {
    _STEP_META,
    _STEP_DATA
  } _step_t;

  //const int MODBUS_MAX_READ_REGISTERS = 125;
  //const int _MIN_REQ_LENGTH = 12;
  //const int MAX_MESSAGE_LENGTH = 260;

  //! if ( flagTCP == true ) //! 18.07.2017
  if ( flagModbusProtokol == 2 )  //! ModBus TCP 18.07.2017
  {
    if ( Data.bFlag_TCP_Connect == true )
    {
      modbus_set_slave( ctx, BDAddr );
      return modbus_read_registers( ctx, REGAddr, nb, dest );
    }
    else
    {
      return -1;
    }
  }

  uint8_t req[_MIN_REQ_LENGTH];
  uint8_t rsp[MAX_MESSAGE_LENGTH];

  uint16_t crc;
  int req_length;
  int msg_length;
  int length_to_read;
  _step_t step;
  int req_nb_value;
  int rsp_nb_value;
  uint16_t crc_calculated;
  uint16_t crc_received;

  // ���������������� ��������� ��� �� �����
  step = _STEP_META;
  length_to_read = 3; // ����� ����, ��� �������, ���-�� ���� ������ (����� ��������� � CRC)
  msg_length = 0; // ����� ���� ��� ���������

  if (nb > MODBUS_MAX_READ_REGISTERS)
  {
    return -1;
  }

  // ��������� ������� RTU
  this->AddrBD = BDAddr;
  req[0] = this->AddrBD; // ����� ������������ ����������
  req[1] = 3; // ����� ������� ModBus
  req[2] = REGAddr >> 8; // ����� ��������
  req[3] = REGAddr & 0x00ff; // ����� ��������
  req[4] = nb >> 8; // ����� ���������
  req[5] = nb & 0x00ff; // ����� ���������
  req_length = 6;
  crc = crc16(req, req_length);
  req[req_length++] = crc >> 8;
  req[req_length++] = crc & 0x00FF;

  if ( flagModbusProtokol == 1 )  //! ModBus RTU 18.07.2017
  {
    WriteToPort(req, req_length, this->parity);
  }
  else if ( flagModbusProtokol == 3 ) //! ModBus RTU (TCP/IP) (18.07.2017)
  {
    // In recovery mode, the write command will be issued until to be
    //   successful! Disabled by default.
    do
    {
      this->err = _modbus_tcp_send( ctx, req, req_length );
      if ( this->err == -1 )
      {
        ; // ������
      }
    } while ( ( ctx->error_recovery & MODBUS_ERROR_RECOVERY_LINK ) && ( this->err == -1 ) );
    if ( ( this->err > 0 ) && ( this->err != req_length ) )
    {
      errno = EMBBADDATA;
      return -1;
    }
  }

  if ( flagModbusProtokol == 1 ) //! ModBus RTU (18.07.2017)
  {
    while (length_to_read != 0)
    {
      this->err = ReadFromPort(rsp + msg_length, length_to_read, this->parity);

      if (this->err != length_to_read)
      {
        return -2;
      }
      // ����� ��������� ����
      msg_length += this->err;
      // ���������� ���������� ����
      length_to_read -= this->err;
      if (length_to_read == 0)
      {
        switch (step)
        {
        case _STEP_META:
          length_to_read = rsp[2] + 2; // ����� ���� + (��� ����� ����������� �����)
          if (msg_length + length_to_read > MODBUS_MAX_READ_REGISTERS)
          {
            return -3;
          }
          step = _STEP_DATA;
          break;
        default:
          break;
        }
      }
    } // end while (length_to_read != 0)
  }
  else if ( flagModbusProtokol == 3 ) //! ModBus RTU (TCP/IP) (18.07.2017)
  {
    if ( this->err > 0 )
    {
      this->err = receive_msg(
        ctx, // ����������� ���������� ���� modbus_t
        rsp,
        MSG_CONFIRMATION ); // CONFIRMATION - �������������
      if ( this->err == -1 )
      {
        return -1;
      }
    }
    msg_length = this->err;
  }

  // ===

  crc_calculated = crc16(rsp, msg_length - 2);
  crc_received = (rsp[msg_length - 2] << 8) | rsp[msg_length - 1];

  if ( crc_calculated == crc_received )
  {
    req_nb_value = (req[4] << 8) + req[5]; // ����� ��������� (nb)
    rsp_nb_value = (rsp[2] / 2); // ����� �������� ���� ������ / 2 (��������� � CRC �� ������ � ��� �����)

    if ( req_nb_value == rsp_nb_value )
    {
      this->err = rsp_nb_value;
    }
    else
    {
      this->err = -4;
    }
  }
  else
  {
    return -5;
  }
  if ( this->err == -1 )
  {
    return -6;
  }
  // ===
  for ( int i = 0; i < this->err; i++ )
  {
    dest[i] = (rsp[3 + (i << 1)] << 8) |
        rsp[4 + (i << 1)];
  }
  return this->err;
}
//---------------------------------------------------------------------------
// ������ nb ��������� ������� � ������ REGAddr
int RSProtokol_t::write_registers(
    int BDAddr, // ����� ��
    int REGAddr, // ����� ��������
    int nb, // ����� ���������
    uint16_t * src) // ������
{
  typedef enum
  {
    _STEP_META,
    _STEP_DATA
  } _step_t;

  //const int MAX_MESSAGE_LENGTH = 260;
  //const int MODBUS_MAX_WRITE_REGISTERS = 123;

  //! if ( flagTCP == true ) //! 18.07.2017
  if ( flagModbusProtokol == 2 )  //! ModBus TCP 18.07.2017
  {
    if ( Data.bFlag_TCP_Connect == true )
    {
      modbus_set_slave( ctx, BDAddr );
      return modbus_write_registers( ctx, REGAddr, nb, src );
    }
    else
    {
      return -1;
    }
  }

  int rc;
  int i;

  uint16_t crc;
  int byte_count;
  int req_length;
  int msg_length;
  int length_to_read;
  _step_t step;
  int req_nb_value;
  int rsp_nb_value;
  uint16_t crc_calculated;
  uint16_t crc_received;

  uint8_t req[MAX_MESSAGE_LENGTH];
  uint8_t rsp[MAX_MESSAGE_LENGTH];

  // ���������������� ��������� ��� �� �����
  step = _STEP_META;
  length_to_read = 6; // ����� ����, ��� �������, ���-�� ���� ������ (����� ��������� � CRC)
  msg_length = 0; // ����� ���� ��� ���������

  if (nb > MODBUS_MAX_WRITE_REGISTERS)
  {
    return -1;
  }

  // ��������� ������� RTU
  this->AddrBD = BDAddr;
  req[0] = this->AddrBD; // ����� ������������ ����������
  req[1] = 16; // ����� ������� ModBus
  req[2] = REGAddr >> 8; // ����� ��������
  req[3] = REGAddr & 0x00ff; // ����� ��������
  req[4] = nb >> 8; // ����� ���������
  req[5] = nb & 0x00ff; // ����� ���������
  req_length = 6;

  byte_count = nb * 2;
  req[req_length++] = byte_count;

  for (i = 0; i < nb; i++)
  {
    req[req_length++] = src[i] >> 8;
    req[req_length++] = src[i] & 0x00FF;
  }

  crc = crc16(req, req_length);
  req[req_length++] = crc >> 8;
  req[req_length++] = crc & 0x00FF;

  if ( flagModbusProtokol == 1 ) //! ModBus RTU (18.07.2017)
  {
    WriteToPort(req, req_length, this->parity);
  }
  else if ( flagModbusProtokol == 3 ) //! ModBus RTU (TCP/IP) (18.07.2017)
  {
    // In recovery mode, the write command will be issued until to be
    //   successful! Disabled by default.
    do
    {
      this->err = _modbus_tcp_send( ctx, req, req_length );
      if ( this->err == -1 )
      {
        ; // ������
      }
    } while ( ( ctx->error_recovery & MODBUS_ERROR_RECOVERY_LINK ) && ( this->err == -1 ) );
    if ( ( this->err > 0 ) && ( this->err != req_length ) )
    {
      errno = EMBBADDATA;
      return -1;
    }
  }

  if ( flagModbusProtokol == 1 ) //! ModBus RTU (18.07.2017)
  {
    while ( length_to_read != 0 )
    {
      this->err = ReadFromPort(rsp + msg_length, length_to_read, this->parity);
      if ( this->err != length_to_read )
      {
        this->MB_length_to_read = length_to_read; // ����� ���������
        return -2;
      }
      // ����� ��������� ����
      msg_length += this->err;
      // ���������� ���������� ����
      length_to_read -= this->err;
      if (length_to_read == 0)
      {
        switch (step)
        {
        case _STEP_META:
          length_to_read = 2; // ��� ����� ����������� �����
           if (msg_length + length_to_read > MODBUS_MAX_WRITE_REGISTERS)
           {
             return -3;
           }
           step = _STEP_DATA;
           break;
        default:
          break;
        }
      }
    } // end while (length_to_read != 0)
  }
  else if ( flagModbusProtokol == 3 ) //! ModBus RTU (TCP/IP) (18.07.2017)
  {
    if ( this->err <= 0 )
    {
      return -1;
    }
    this->err = receive_msg(
      ctx, // ����������� ���������� ���� modbus_t
      rsp,
      MSG_CONFIRMATION ); // CONFIRMATION - �������������
    if ( this->err == -1 )
    {
      return -1;
    }
    msg_length = this->err;
  }

  // ===

  crc_calculated = crc16(rsp, msg_length - 2);
  crc_received = (rsp[msg_length - 2] << 8) | rsp[msg_length - 1];

  if (crc_calculated == crc_received)
  {
    if (rsp[1] != 16)
    {
      return -4;
    }
    req_nb_value = (req[4] << 8) + req[5];
    rsp_nb_value = (rsp[4] << 8) | rsp[5];
    if (req_nb_value == rsp_nb_value)
    {
      this->err = rsp_nb_value;
    }
    else
    {
      this->err = -5;
    }
  }
  else
  {
    return -6;
  }
  return this->err;
}
//---------------------------------------------------------------------------
// ���������� ������� ��������� �� ���������� (1 - ��������, � - ���������)
int RSProtokol_t::IncFreqLEDImp(unsigned char State)
{
  this->buf_write[0] = 0x11;
  this->buf_write[1] = 184;
  this->buf_write[2] = 112;
  this->buf_write[3] = 235;
  this->buf_write[4] = State;
  this->CodeRet = CommandExec(4, 1);
  return this->CodeRet;
}
//---------------------------------------------------------------------------
// ���������� ������� ������� �������� 1-������, 0-�����������
int RSProtokol_t::SpectrCon(unsigned char State)
{
  this->buf_write[0] = 0x0F;
  this->buf_write[1] = 184;
  this->buf_write[2] = 112;
  this->buf_write[3] = 235;
  this->buf_write[4] = State;
  this->CodeRet = CommandExec(4, 1);
  return this->CodeRet;
}
//---------------------------------------------------------------------------
// ���������� �������� ��� 0-��������, 1-���������
int RSProtokol_t::ARCHCon(unsigned char State)
{
  this->buf_write[0] = 0x12;
  this->buf_write[1] = 184;
  this->buf_write[2] = 112;
  this->buf_write[3] = 235;
  this->buf_write[4] = State;
  this->CodeRet = CommandExec(4, 1);
  return this->CodeRet;
}
//---------------------------------------------------------------------------
int RSProtokol_t::ReadFromBDModbus( unsigned short * AddrRegModBus )
{
  int ReturnVar;
  ReturnVar = 0;
  int i;
  for ( i = 0; i < 15; i++ ) // 15 ������ ��������
  {
    ReturnVar = ExRead( i, AddrRegModBus[i], ptr_Edit_3_01__14[i] );
    if ( ReturnVar == -1 )
    {
      return ReturnVar;
    }
  }
  return ReturnVar;
}
//---------------------------------------------------------------------------
int RSProtokol_t::ExRead( int Index, unsigned short AddrRegModBus, unsigned long * ptr_Edit_3_01__14 )
{
  int RetVal;
  switch( Index )
  {
  case 0 :
  case 11 :
  case 14 :
    RetVal = ReadFlashInvert( AddrRegModBus, ptr_Edit_3_01__14 );
    break;
  case 1 :
  case 2 :
  case 3 :
  case 4 :
  case 5 :
  case 6 :
  case 7 :
  case 8 :
  case 9 :
  case 10 :
  case 12 :
  case 13 :
    ReturnVar = ReadFlash2( AddrRegModBus, ptr_Edit_3_01__14 );
    break;
  default :
    RetVal = -1;
  }
  return RetVal;
}
//---------------------------------------------------------------------------
int RSProtokol_t::ReadFromBDModbus_BD82( void )
{
  return ReadFromBDModbus( this->AddrRegModBus_BD82 );
}
//---------------------------------------------------------------------------
int RSProtokol_t::ReadFromBDModbus_BD85_New( void )
{
  return ReadFromBDModbus( this->AddrRegModBus_BD85_New );
}
//---------------------------------------------------------------------------
int RSProtokol_t::WriteToBDModBus( unsigned short * AddrEEPROM )
{
  int ReturnVar;
  ReturnVar = 0;
  int i;
  for ( i = 0; i < 15; i++ ) // 15 ������ ��������
  {
    ReturnVar = ExWrite( i, AddrEEPROM[i], ptr_Edit_3_01__14[i] );
    if ( ReturnVar == -1 )
    {
      return ReturnVar;
    }
  }
  return ReturnVar;
}
//---------------------------------------------------------------------------
int RSProtokol_t::ExWrite( int Index, unsigned short AddrRegModBus, unsigned long * ptr_Edit_3_01__14 )
{
  int RetVal;
  switch( Index )
  {
  case 0 :
  case 11 :
  case 14 :  
    RetVal = WriteFlashInvert( AddrRegModBus, * ptr_Edit_3_01__14 );
    break;
  case 1 :
  case 2 :
  case 3 :
  case 4 :
  case 5 :
  case 6 :
  case 7 :
  case 8 :
  case 9 :
  case 10 :
  case 12 :
  case 13 :
    ReturnVar = WriteFlash2( AddrRegModBus, * ptr_Edit_3_01__14 );
    break;
  default :
    RetVal = -1;
  }
  return RetVal;
}
//---------------------------------------------------------------------------
int RSProtokol_t::WriteToBDModBus_BD82( void )
{
  return WriteToBDModBus( this->AddrRegModBus_BD82 );
}
//---------------------------------------------------------------------------
int RSProtokol_t::WriteToBDModBus_BD85_New( void )
{
  return WriteToBDModBus( this->AddrRegModBus_BD85_New );
}
//---------------------------------------------------------------------------
void RSProtokol_t::ReadKoef(
    float * k1,
    unsigned long * Longk1,
    float * A1,
    unsigned long * LongA1,
    float * k2,
    unsigned long * Longk2,
    float * A2,
    unsigned long * LongA2,
    int MasSveto[256]
    )
{ // ������ ������������
  union
  {
    float Flo;
    unsigned char Ch[4];
  } uu;
  union
  {
    unsigned long Lon;
    unsigned char Ch[4];
  } uuFL;

  for ( int i = 0; i < 4; i++ )
  {
    buf_write[0] = 0x02;
    buf_write[1] = 0x2C + i; // ����� ����� (0x2C === 44) 44-45-46-47
    buf_write[2] = 0;


    if ( CommandExec(2, 4) == -1 )
    {
      return;
    }

    uu.Ch[0] = buf_read[0];
    uu.Ch[1] = buf_read[1];
    uu.Ch[2] = buf_read[2];
    uu.Ch[3] = buf_read[3];

    if ( (uu.Ch[0] == 255) && (uu.Ch[1] == 255)
        && (uu.Ch[2] == 255) && (uu.Ch[3] == 255) )
    {
      uu.Flo = 0;
    }

    uuFL.Ch[0] = buf_read[0];
    uuFL.Ch[1] = buf_read[1];
    uuFL.Ch[2] = buf_read[2];
    uuFL.Ch[3] = buf_read[3];
    
    if ( (uuFL.Ch[0] == 255) && (uuFL.Ch[1] == 255)
        && (uuFL.Ch[2] == 255) && (uuFL.Ch[3] == 255) )
    {
      uuFL.Lon = 0;
    }
    if ( i == 0 )
    {
      *k1 = uu.Flo;
      *Longk1 = uuFL.Lon;
    }
    if ( i == 1 )
    {
      *A1 = uu.Flo;
      *LongA1 = uuFL.Lon;
    }
    if ( i == 2 )
    {
      *k2 = uu.Flo;
      *Longk2 = uuFL.Lon;
    }
    if ( i == 3 )
    {
      *A2 = uu.Flo;
      *LongA2 = uuFL.Lon;
    }
  } // end for ( int i = 0; i < 4; i++ )

  // ������ ������������� �������� 0-255
  int j = 0;

  for ( int i = 0; i < 64; i++ )
  {
    buf_write[1] = 48 + i; // ����� ����� �� 48 �� 111
    buf_write[2] = 0;
    if ( CommandExec(2, 4) == -1 )
    {
      return;
    }

    MasSveto[j++] = buf_read[0];
    MasSveto[j++] = buf_read[1];
    MasSveto[j++] = buf_read[2];
    MasSveto[j++] = buf_read[3];
  }
}
//---------------------------------------------------------------------------
void RSProtokol_t::WriteKoef(
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
    )
{
  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //unsigned long temp = 0;
  //unsigned char temp2 = 0;
  AnsiString str;

  union
  {
    float Flo;
    unsigned char Ch[4];
  } uu;
  union
  {
    unsigned long Lon;
    unsigned char Ch[4];
  } uuFL;

  for ( int i = 0; i < 4; i++ )
  {
    // ���������� ������������ � EEPROM
    if ( FlagGrafik )
    {
      if ( i == 0 )
      {
        uu.Flo = *k1; // �������������� = ������������������ * k1 + �1 - ��� ����������
        for ( int i = 0; i < 4; i++ )
        {
          uuFL.Ch[i] = uu.Ch[i];
        }
        *Longk1 = uuFL.Lon;
      }
      if ( i == 1 )
      {
        uu.Flo = *A1; // �������������� = ������������������ * k1 - �1 - ��� BUILDER
        for ( int i = 0; i < 4; i++ )
        {
          uuFL.Ch[i] = uu.Ch[i];
        }
        *LongA1 = uuFL.Lon;
      }
      if ( i == 2 )
      {
        uu.Flo = *k2; // ��������������������� = ������������� * (1 / �2) + �2 / �2 - ��� ����������
        for ( int i = 0; i < 4; i++ )
        {
          uuFL.Ch[i] = uu.Ch[i];
        }
        *Longk2 = uuFL.Lon;
      }
      if ( i == 3 )
      {
        uu.Flo = *A2; // ������������� = ��������������������� * �2 - �2 - ��� BUILDER
        for ( int i = 0; i < 4; i++ )
        {
          uuFL.Ch[i] = uu.Ch[i];
        }
        *LongA2 = uuFL.Lon;
      }
      buf_write[0] = 0x01; // PWrRom-������ � EEPROM
      buf_write[1] = 184;
      buf_write[2] = 112;
      buf_write[3] = 235;
      buf_write[4] = 0x2C + i; // ����� ����� (44-����������) 44-45-46-47
      buf_write[5] = 0;
      // 4 ����� ������
      buf_write[6] = uu.Ch[0];
      buf_write[7] = uu.Ch[1];
      buf_write[8] = uu.Ch[2];
      buf_write[9] = uu.Ch[3];
      if ( CommandExec(9, 1) == -1 )
      {
        return;
      }
      if ( buf_read[0] == 0xAA )
      {
        Application->MessageBox("������ ������ � EEPROM!", "��������!", MB_ICONSTOP);
        return;
      }
    }
    else // ��������� ������ �� ����� ��� EEPROM�
    {
      if ( i == 0 )
      {
        WriteFlash(0x2c, *Longk1);
      }
      if ( i == 1 )
      {
        WriteFlash(0x2d, *LongA1);
      }
      if ( i == 2 )
      {
        WriteFlash(0x2e, *Longk2);
      }
      if ( i == 3 )
      {
        WriteFlash(0x2f, *LongA2);
      }
    }
  }

  for ( int i = 0; i <256; i++ )
  {
    if ( MasSveto[i] < 0 )
    {
      MasSveto[i] = 0;
    }
    if ( MasSveto[i] > 255 )
    {
      MasSveto[i] = 255;
    }
  }

  // ������ � EEPROM 256 �������� �������������������
  int j = 0;
  for ( int i = 0; i < 64; i++ )
  {
    buf_write[0] = 0x01; // PWrRom-������ � EEPROM
    buf_write[1] = 184;
    buf_write[2] = 112;
    buf_write[3] = 235;
    buf_write[4] = 48 + i; // ����� ����� 48 - 111
    buf_write[5] = 0;
    // 4����� ������
    buf_write[6] = MasSveto[j++];
    buf_write[7] = MasSveto[j++] ;
    buf_write[8] = MasSveto[j++] ;
    buf_write[9] = MasSveto[j++] ;
    if ( CommandExec(9, 1) == -1 )
    {
      return;
    }
    if ( buf_read[0] == 0xAA )
    {
      Application->MessageBox("������ ������ � EEPROM!", "��������!", MB_ICONSTOP);
      return;
    }
  }

  // if ( !Form1->Privet(AdresBD) ) return;
  k1PR = A1PR = k2PR = A2PR = 0;
  for ( int i = 0; i < 4; i++ )
  { // ������ ������������
    buf_write[0] = 0x02; //
    buf_write[1] = 0x2C + i; // ����� �����(0x2C --- 44-����������) 44-45-46-47
    buf_write[2] = 0;
    // 4 ����� ������
    if ( CommandExec(2, 4) == -1 )
    {
      return;
    }
    uu.Ch[0] = buf_read[0];
    uu.Ch[1] = buf_read[1];
    uu.Ch[2] = buf_read[2];
    uu.Ch[3] = buf_read[3];
    if ( uu.Ch[0] == 255 && uu.Ch[1] == 255
        && uu.Ch[2] == 255 && uu.Ch[3] == 255 )
    {
      uu.Flo = 0;
    }
    uuFL.Ch[0] = buf_read[0];
    uuFL.Ch[1] = buf_read[1];
    uuFL.Ch[2] = buf_read[2];
    uuFL.Ch[3] = buf_read[3];
    if( uuFL.Ch[0] == 255 && uuFL.Ch[1] == 255
        && uuFL.Ch[2] == 255 && uuFL.Ch[3] == 255 )
    {
      uuFL.Lon = 0;
    }
    if ( i == 0 )
    {
      k1PR = uu.Flo;
      Longk1PR = uuFL.Lon;
    }
    if ( i == 1 )
    {
      A1PR = uu.Flo;
      LongA1PR = uuFL.Lon;
    }
    if ( i == 2 )
    {
      k2PR = uu.Flo;
      Longk2PR = uuFL.Lon;
    }
    if ( i == 3 )
    {
      A2PR = uu.Flo;
      LongA2PR = uuFL.Lon;
    }
  }
  // ������ ������������� �������� 0-255
  j = 0;
  for ( int i = 0; i < 64; i++ )
  {
    buf_write[1] = 48 + i; // ����� ����� 48 - 111
    buf_write[2] = 0;
    // 4 ����� ������
    if ( CommandExec(2, 4) == -1 )
    {
      return;
    }
    MasSvetoPR[j++] = buf_read[0];
    MasSvetoPR[j++] = buf_read[1];
    MasSvetoPR[j++] = buf_read[2];
    MasSvetoPR[j++] = buf_read[3];
  }

  if ( Longk1PR != *Longk1 )
  {
    Application->MessageBox("�������� �� ���������� � EEPROM", "Longk1", MB_ICONINFORMATION);
  }
  if ( LongA1PR != *LongA1 )
  {
    Application->MessageBox("�������� �� ���������� � EEPROM", "LongA1", MB_ICONINFORMATION);
  }
  if ( Longk2PR != *Longk2 )
  {
    Application->MessageBox("�������� �� ���������� � EEPROM", "Longk2", MB_ICONINFORMATION );
  }
  if ( LongA2PR != *LongA2 )
  {
    Application->MessageBox("�������� �� ���������� � EEPROM", "LongA2", MB_ICONINFORMATION);
  }
  for ( int i = 0; i < 256; i++ )
  {
    str = "�������� �� ���������� � EEPROM\n ����� ������ = " + IntToStr(i);
    if ( MasSvetoPR[i] != MasSveto[i] )
    {
      Application->MessageBox(str.c_str(), "���", MB_ICONINFORMATION);
    }
  }
}
//---------------------------------------------------------------------------

