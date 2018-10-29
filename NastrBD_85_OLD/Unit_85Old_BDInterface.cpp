//---------------------------------------------------------------------------
#pragma hdrstop

#include "Unit_85Old_BDInterface.h"
#include "Unit_85Old_RS232.h"
#include "Unit_85Old_main.h"
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <string.h>;
#include <Buttons.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)

Port232 com232;
extern unsigned char buf_write[16],*pbuf_write=buf_write;   //Буфер для записи
extern unsigned char buf_read[16],*pbuf_read=buf_read;      //Буфер для чтения
//int CodeRet;
int CodeRet_85Old;
DWORD err=0;
unsigned char ch,*adrbuf;
long int time1,time2;
unsigned char UniAdr;// универсальный адрес (на него откликаются все БД)
//------------------------------------------------------------------------------
int OpenRS(int nPort)
{  int i;
   adrbuf=&ch;
   unsigned char ArrIndAdr[7];

   if(com232.OpenA(nPort))
     { if(com232.PortInit()==1)
         CloseHandle(com232.hCOM);
     }
   else
     return 0;
   if(com232.OpenA(nPort))
     { if(com232.PortInit()!=1)
         return 0;
       //порт открылся удачно
       com232.PurgeBufs();//Чистим буфера чтения-записи
     }

   com232.dcb.Parity=SPACEPARITY;
   SetCommState(com232.hCOM,&com232.dcb);
   for(i=0;i<=7;i++)
     { if(ArrIndAdr[i]==i)
         { ch=ArrIndAdr[i];
           break;
         }
     }
   return 0;
}
//------------------------------------------------------------------------------
int CloseRS()
{ com232.ClosePort();
  return 0;
}
//------------------------------------------------------------------------------
int CommandExec(unsigned char kOutByte,unsigned char kInByte)
{ if(!Form_85Old_Main->bFlagWork)return 1;
  if(Form_85Old_Main->FlagZapis){Form_85Old_Main->FlagZapis=false;return 1;}
  
//ch=UniAdr;
ch=StrToInt(Form_85Old_Main->NewConnectionAdr->Text);
for(int cykl=0;cykl<5;cykl++)
{  com232.dcb.fParity=true;
   com232.dcb.Parity=MARKPARITY;SetCommState(com232.hCOM,&com232.dcb);
   // Первый этап обмена - шлем адрес целевого БД
for(int cykl2=0;cykl2<5;cykl2++)//делаем 5 попыток связи и если нет - выдаём сообщение
{
   if(!Form_85Old_Main->bFlagWork)return 1;com232.PurgeBufs();//Чистим буфера чтения-записи
   if(!Form_85Old_Main->bFlagWork)return 1;com232.WriteA(&ch,1);
       time1=GetCurrentTime();
   do{ if(!Form_85Old_Main->bFlagWork)return 1;err=com232.ReadA(pbuf_read,1); Application->ProcessMessages();}
   while((err!=1)&&((GetCurrentTime()-time1)<500));
    if(Form_85Old_Main->FlagZapis){Form_85Old_Main->FlagZapis=false;for(int i=0;i<8;i++)buf_read[i]=0;return 1;}
   if (err!=1)continue; else break;
}//for(cykl2)
   if (err!=1){Application->MessageBox(" Отклик на адрес не получен","Таймаут", MB_OK|MB_ICONHAND);
               Application->ProcessMessages();
               return 0;
               }
//*****************************************
       
       if(!Form_85Old_Main->bFlagWork)return 1;com232.PurgeBufs();//Чистим буфера чтения-записи
   com232.dcb.Parity=SPACEPARITY;SetCommState(com232.hCOM,&com232.dcb);
   if(!Form_85Old_Main->bFlagWork)return 1;com232.WriteA(pbuf_write,kOutByte+1);
        time1=GetCurrentTime();
   do {if(!Form_85Old_Main->bFlagWork)return 1; err=com232.ReadA(pbuf_read,kInByte); Application->ProcessMessages();
      }while((err!=kInByte)&&(GetCurrentTime()-time1)<500);
      if(Form_85Old_Main->FlagZapis){Form_85Old_Main->FlagZapis=false;for(int i=0;i<8;i++)buf_read[i]=0;return 1;}
    if (err==kInByte) return 1; else continue;
}//for(cykl)
  if (err!=kInByte){Application->MessageBox(" Данные с БД на пришли","Таймаут", MB_OK|MB_ICONHAND);
                    Application->ProcessMessages();
                    return 0;
                    }
}
//------------------------------------------------------------------------------
// установить индивидуальный адрес БД
int SetIndAdr(unsigned char Adr)
{  buf_write[0]=0x13;
   buf_write[1]=184;
   buf_write[2]=112;
   buf_write[3]=235;
   buf_write[4]=Adr;
   CodeRet_85Old = CommandExec(1+3,1);
   if(buf_read[0]==0xAA)Application->MessageBox("Команда не понятна БД","индивидуальный адрес", MB_OK|MB_ICONHAND);
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
// считать индивидуальный адрес БД
int GetIndAdr(unsigned char *Adr)
{  *pbuf_write=0x14;
   CodeRet_85Old = CommandExec(0,1);
   *Adr=buf_read[0];
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
// установить групповой адрес БД
int SetGrpAdr(unsigned char Adr)
{  buf_write[0]=0x15;
   buf_write[1]=184;
   buf_write[2]=112;
   buf_write[3]=235;
   buf_write[4]=Adr;
   CodeRet_85Old = CommandExec(1+3,1);
   if(buf_read[0]==0xAA)Application->MessageBox("Команда не понятна БД","групповой адрес", MB_OK|MB_ICONHAND);
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
// считать групповой адрес БД
int GetGrpAdr(unsigned char *Adr)
{  *buf_write=0x16;
   CodeRet_85Old = CommandExec(0,1);
   *Adr=buf_read[0];
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
// считать текущую температуру процессора БД
int GetTemp(unsigned int *Temper)
{  *buf_write=0x08;
   CodeRet_85Old = CommandExec(0,2);
   *Temper=buf_read[1]*256+buf_read[0];
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
// считать значение высокого напряжения
int GetUhi(unsigned int *Temp)
{  *buf_write=0x07;
   CodeRet_85Old = CommandExec(0,2);
   *Temp=buf_read[1]*256+buf_read[0];
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
// установить значение высокого напряжения
int SetUhi(unsigned int Uhi)
{  buf_write[0]=0x19;
   buf_write[1]=184;
   buf_write[2]=112;
   buf_write[3]=235;
   buf_write[4]=Uhi;
   buf_write[5]=(Uhi>>8)&0x0F;
   CodeRet_85Old = CommandExec(2+3,1);
   if(buf_read[0]==0xAA)Application->MessageBox("Команда не понятна БД","значение высокого напряжения", MB_OK|MB_ICONHAND);
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
// управление системой АРЧ 0-включить, 1-отключить
int ARCHCon(unsigned char State)
{  buf_write[0]=0x12;
   buf_write[1]=184;
   buf_write[2]=112;
   buf_write[3]=235;
   buf_write[4]=State;
   CodeRet_85Old = CommandExec(1+3,1);
   if(buf_read[0]==0xAA)Application->MessageBox("Команда не понятна БД","управление системой АРЧ", MB_OK|MB_ICONHAND);
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
// управление снятием спектра импульса 1-включить, 0-отключить
int SpectrCon(unsigned char State)
{  buf_write[0]=0x0F;
   buf_write[1]=184;
   buf_write[2]=112;
   buf_write[3]=235;
   buf_write[4]=State;
   CodeRet_85Old = CommandExec(1+3,1);
   if(buf_read[0]==0xAA)Application->MessageBox("Команда не понятна БД","управление снятием спектра", MB_OK|MB_ICONHAND);
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
// увеличение частоты импульсов от светодиода
int IncFreqLEDImp(unsigned char State)
{  buf_write[0]=0x11;
   buf_write[1]=184;
   buf_write[2]=112;
   buf_write[3]=235;
   buf_write[4]=State;
   CodeRet_85Old = CommandExec(1+3,1);
   if(buf_read[0]==0xAA)Application->MessageBox("Команда не понятна БД","увеличение частоты импульсов от светодиода", MB_OK|MB_ICONHAND);
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
// получить амплитуду импульса от светодиода
int GetLEDAmp(unsigned int *Ampl)
{  unsigned int data;
   *buf_write=0x10;
   CodeRet_85Old = CommandExec(0,2);
   data=buf_read[1]&0x00;
   *Ampl=data*256+buf_read[0];
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
// задать амплитуду импульса светодиода
int SetLEDAmp(unsigned int Amp)
{  buf_write[0]=0x1A;
   buf_write[1]=184;
   buf_write[2]=112;
   buf_write[3]=235;
   buf_write[4]=Amp;
   buf_write[5]=(Amp>>8);
   CodeRet_85Old = CommandExec(2+3,1);
   if(buf_read[0]==0xAA)Application->MessageBox("Команда не понятна БД","задать амплитуду импульса светодиода", MB_OK|MB_ICONHAND);
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
// получить счет за 0,2 сек
int GetCountImp(unsigned int *CImp)
{  unsigned int data;
   buf_write[0]=0x05;
   CodeRet_85Old = CommandExec(0,2);
   data=buf_read[1]&0x0F;
   *CImp=data*256+buf_read[0];
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
// получить спектр импульса
int GetSpectr(unsigned int *Spectr)
{  unsigned int data;
   *pbuf_write=0x06;
   CodeRet_85Old = CommandExec(0,2);
   data=buf_read[1]&0x0F;
   *Spectr=data*256+buf_read[0];
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
// получить слово состояния программы БД
int GetPSWBD(unsigned char *PSWBD)
{  *pbuf_write=0x06;
   CodeRet_85Old = CommandExec(0,1);
   *PSWBD=buf_read[0];
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
// измерить напряжение на выходе дискриминатора нижнего уровня
int GetDNU(unsigned int *DNU)
{  unsigned int data;
   *pbuf_write=0x17;
   CodeRet_85Old = CommandExec(0,2);
   data=buf_read[1]&0x0F;
   *DNU=data*256+buf_read[0];
   Application->ProcessMessages();
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
// установить порог дискриминации нижнего уровня
int SetDNU(unsigned int DNU)
{  buf_write[0]=0x0B;
   buf_write[1]=184;
   buf_write[2]=112;
   buf_write[3]=235;
   buf_write[4]=(DNU);
   buf_write[5]=(DNU>>8)&0x0F;
   CodeRet_85Old = CommandExec(2+3,1);
   if(buf_read[0]==0xAA)Application->MessageBox("Команда не понятна БД","установить порог дискриминации нижнего уровня", MB_OK|MB_ICONHAND);
   return CodeRet_85Old;
}//-----------------------------------------------------------------------------
// измерить напряжение на выходе дискриминатора верхнего уровня
int GetDVU(unsigned int *DVU)
{  unsigned int data;
   *pbuf_write=0x18;
   CodeRet_85Old = CommandExec(0,2);
   data=buf_read[1]&0x0F;
   *DVU=data*256+buf_read[0];
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
// установить порог дискриминации верхнего уровня
int SetDVU(unsigned int DVU)
{  buf_write[0]=0x0C;
   buf_write[1]=184;
   buf_write[2]=112;
   buf_write[3]=235;
   buf_write[4]=DVU;
   buf_write[5]=(DVU>>8)&0x0F;
   CodeRet_85Old = CommandExec(2+3,1);
   if(buf_read[0]==0xAA)Application->MessageBox("Команда не понятна БД","установить порог дискриминации верхнего уровня", MB_OK|MB_ICONHAND);
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
// запись байта данных в FLASH/EE DATA MEMORY процессора
int WriteFlash(unsigned int Adr,unsigned long Data)
{  union {  unsigned long tData;
            unsigned char mDATA[4];
         } outdata;
   outdata.tData=Data;
    buf_write[0]=0x01;
   buf_write[1]=184;
   buf_write[2]=112;
   buf_write[3]=235;
   buf_write[4]=Adr&0x00FF;
   buf_write[5]=(Adr>>8)&0x0003;
   buf_write[6]=(~outdata.mDATA[0]);
   buf_write[7]=(~outdata.mDATA[1]);
   buf_write[8]=(~outdata.mDATA[2]);
   buf_write[9]=(~outdata.mDATA[3]);
   CodeRet_85Old = CommandExec(6+3,1);
   if(buf_read[0]==0xAA)Application->MessageBox("Команда не понятна БД","запись байта данных в FLASH/EE DATA", MB_OK|MB_ICONHAND);
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
// считывание байта данных из FLASH/EE DATA MEMORY процессора
int ReadFlash(unsigned int Adr, unsigned long *Data)
{  union {  unsigned long tData;
            unsigned char eMas[4];
         } indata;
   buf_write[0]=0x02;
   buf_write[1]=Adr&0x00FF;
   buf_write[2]=(Adr>>8)&0x0003;
   CodeRet_85Old = CommandExec(2,4);
   indata.eMas[0]=(~buf_read[0]);//&0xFF;
   indata.eMas[1]=(~buf_read[1]);//&0x00;
   indata.eMas[2]=(~buf_read[2]);//&0x00;
   indata.eMas[3]=(~buf_read[3]);//&0x00;
   *Data=indata.tData;
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
// запись байта данных во внутреннюю память данных процессора (256 байт) процессора
int WriteRAM(unsigned char Adr, unsigned char Data)
{  buf_write[0]=0x03;
   buf_write[1]=Adr;
   buf_write[2]=Data;
   CodeRet_85Old = CommandExec(2,1);
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
int ReadRAM(unsigned char Adr,unsigned char *Data)        // чтение байта данных из внутренней памяти данных процессора
{ buf_write[0]=0x04;
  buf_write[1]=Adr;
   CodeRet_85Old = CommandExec(1,1);
   *Data=buf_read[0];
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
// получить слово состояния программы БД
int GetSSP(unsigned char *SSP)
{  buf_write[0]=0x09;
   CodeRet_85Old = CommandExec(0,1);
   *SSP=buf_read[0];
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
int SetTimeInterval(unsigned char TimeInt)
{  buf_write[0]=0x0D;
   buf_write[1]=TimeInt;
   CodeRet_85Old = CommandExec(1,1);
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
int GetSIM3(unsigned int *SIM3)
{
   buf_write[0]=0x1c;
   buf_write[1]=3;
   CodeRet_85Old = CommandExec(1,2);
   *SIM3=buf_read[1]*256+buf_read[0];
   return CodeRet_85Old;
}
 //-----------------------------------------------------------------------------
int GetVersia(unsigned char *Versia)
{
   buf_write[0]=0x1f;
   CodeRet_85Old = CommandExec(0,4);
   for(int i=0;i<4;i++)Versia[i]=buf_read[i];
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int SetARH(unsigned char KodRS) //с записью в EEPROM       0-есть обратная связь  1-нет
{  buf_write[0]=0x12;
   buf_write[1]=184;
   buf_write[2]=112;
   buf_write[3]=235;
   buf_write[4]=KodRS;
   CodeRet_85Old = CommandExec(1+3,1);
   if(buf_read[0]==0xAA)Application->MessageBox("Команда не понятна БД","управление системой АРЧ", MB_OK|MB_ICONHAND);
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
int GetARH(unsigned char *KodRS) //0-есть  1-нет
{
   buf_write[0]=0x09; //4-тый бит SSP БД
   CodeRet_85Old = CommandExec(0,1);
   *KodRS=buf_read[0];
   *KodRS=*KodRS&0x10;
   if(*KodRS==0x10)*KodRS=1; else *KodRS=0;
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------

int GetSIM4(unsigned int *SIM4)
{
   buf_write[0]=0x1c;
   buf_write[1]=4;
   CodeRet_85Old = CommandExec(1,2);
   *SIM4=buf_read[1]*256+buf_read[0];
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
int GetTimeInterval(unsigned char *TimeInt)
{
   buf_write[0]=0x0e;
   CodeRet_85Old = CommandExec(0,1);
   *TimeInt=buf_read[0];
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
int SetSIM3(unsigned int PWMzn) //длительность
{  buf_write[0]=0x1e;
   buf_write[1]=184;
   buf_write[2]=112;
   buf_write[3]=235;
   buf_write[4]=PWMzn;
   buf_write[5]=(PWMzn>>8)&0x0F;
   CodeRet_85Old = CommandExec(5,1);
   if(buf_read[0]==0xAA)Application->MessageBox("Команда не понятна БД","установить новое значение ШИМ", MB_OK|MB_ICONHAND);
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
int SetSIM4(unsigned int PWMzn) //период
{  buf_write[0]=0x1b;
   buf_write[1]=184;
   buf_write[2]=112;
   buf_write[3]=235;
   buf_write[4]=PWMzn;
   buf_write[5]=(PWMzn>>8)&0x0F;
   CodeRet_85Old = CommandExec(5,1);
   if(buf_read[0]==0xAA)Application->MessageBox("Команда не понятна БД","установить новое значение ШИМ", MB_OK|MB_ICONHAND);
   return CodeRet_85Old;
}
//------------------------------------------------------------------------------
