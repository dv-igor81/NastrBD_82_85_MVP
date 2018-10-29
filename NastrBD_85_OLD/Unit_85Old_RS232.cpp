//----------------------------------------------------------------------------
//Port232.cpp :(9600-1-8-false)
//----------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//----------------------------------------------------------------------------
#include "Unit_85Old_RS232.h"
#include "Unit_85Old_main.h"
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <string.h>
extern bool flagPort_85Old;

//-----------------------------------------------------------------------------
 _fastcall Port232::Port232()//конструктор
{
BaudRate=115200;
fParity=false;//выключён контроль чётности
StopBits=ONESTOPBIT;
ByteSize=8;
memset(&wov,0,sizeof(wov)); //обнуление структур
memset(&rov,0,sizeof(rov));
memset(&dcb,0,sizeof(dcb));
wov.hEvent=rov.hEvent=0;
mask=EV_RXCHAR;
}
//------------------------------------------------------------------------------
bool _fastcall Port232::OpenA(int n)//открытие асинхронной передачи
{
AnsiString imq;
imq=StrToInt(n);
imq="COM"+imq;
char *cha1=imq.c_str();
hCOM=CreateFile(cha1,GENERIC_WRITE|GENERIC_READ,0,NULL,
     OPEN_EXISTING,
     FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED,NULL);
if(hCOM==INVALID_HANDLE_VALUE)
  {ShowMessage("Ошибка открытия порта");

  return 0;}

return 1;
}
//------------------------------------------------------------------------------
bool _fastcall  Port232::OpenS(int n)//открытие синхронной передачи
{
AnsiString imq;
imq=StrToInt(n);
imq="COM"+imq;
char *cha1=imq.c_str();
hCOM=CreateFile(cha1,GENERIC_WRITE|GENERIC_READ,0,NULL,
				OPEN_EXISTING,0,NULL);
if(hCOM==INVALID_HANDLE_VALUE)
 {ShowMessage("Ошибка открытия порта");

      return 0;}
return 1;
}
//------------------------------------------------------------------------------
DWORD _fastcall Port232::PortInit()//открытие и инициализация СОМ-порта
{err=1;
     		   if(!GetCommState(hCOM,&dcb))err=3;
			   //заполняет DCB информацией о настройке порта
		   else{
			   dcb.DCBlength=sizeof(dcb);//
			   dcb.BaudRate=BaudRate;//скорость передачи данных
			   dcb.fBinary=true;//двоичный режим обмена
			   dcb.fParity=fParity;//подключаем контроль чётности
                           dcb.Parity=Parity;//выбор схемы контроля чётности
			   dcb.StopBits=StopBits;//количество стоповых бит(=0 для 1 стоп-бита)
			   dcb.ByteSize=ByteSize;//число бит в кадре
			   dcb.fNull=false;//нулевые байты не отбрасываютсяпри передаче
			   dcb.fAbortOnError=true;//драйвер прекращает всеоперации
                           dcb.fErrorChar=false;//Указывает на необходимость
//замены символов с ошибочной чётностью на символ задаваемый полем ErrorChar
                           dcb.ErrorChar=0;
                           dcb.fDtrControl=DTR_CONTROL_DISABLE;
                           dcb.fRtsControl=RTS_CONTROL_DISABLE;
                           dcb.fTXContinueOnXoff=true;
//Остальные параметры структуры - обращены в ноль
//dcb.fOutCtsFlow,dcb.fOutDsrFlow,dcb.fDtrControl,dcb.DsrSensitivity,
//dcb.fTxContinueOnXoff,dcb.fOutX,dcb.fInX,dcb.fErrorChar,dcb.fRtsControl,
//dcb.fAboutOnError,dcb.fDummy,dcb.wReserved,dcb.XonLim,dcb.XoffLim,
//dcb.XonChar,dcb.XoffChar,dcb.ErrorChar,dcb.EofChar,dcb.EvtChar,dcb.wReservedl
dcb.fOutxCtsFlow=false ;//режим слежения за сигналом CTS
dcb.fOutxDsrFlow=false ;//режим слежения за сигналом DSR
dcb.fDsrSensitivity=false ;//чувствительность драйвера к состоянию линии DSR
dcb.fTXContinueOnXoff=false ;//для XON/XOFF
dcb.fOutX=false ;//для XON/XOFF
dcb.fInX=false ;//для XON/XOFF
dcb.fErrorChar=false ; //замена символов с ошибкой чётности
dcb.fAbortOnError=false ;//игнорирование всех операций чтения/записи при возникновении ошибки
dcb.fDummy2=0 ;//не используется
//dcb.wReserved=0;//не используется
dcb.XonLim=0 ;//минимальное число символов в приёмном буфере перед посылкой символа XON
dcb.XoffLim=0 ;//максимальное количество байт в приёмном буфере перед посылкой символа XOFF
dcb.XonChar=0;//символ XON
dcb.XoffChar=0;//символ XOFF
dcb.ErrorChar=0;//символ замены символов с ошибочной чётности
dcb.EofChar=0;//символ сигнализации о конце данных
dcb.EvtChar=0;//символ, использующийся для сигнализации о событии
dcb.wReserved1=0 ;//не используется

                            //чтения/записи при ошибке
			   if(!SetCommState(hCOM,&dcb))err=4;
			   //конфигурирование порта
			   else{
//		    ct.ReadIntervalTimeout=100;//=0-данный тайм-аут не используется
		    ct.ReadIntervalTimeout=0xffffffff;//=0-данный тайм-аут не используется
//если при чтении прошло>MAXDWORDмсек-ошибка чтения
//2048*10\9600=2200мсек-время считывания буфера,2048байт -размер буфера-из SetupComm
//(кол-во символов)*10бит\db.BaudRate=время считывания этих символов
			ct.ReadTotalTimeoutConstant=10;
			ct.ReadTotalTimeoutMultiplier=2;
			ct.WriteTotalTimeoutConstant=100;
			ct.WriteTotalTimeoutMultiplier=100;

				   if(!SetCommTimeouts(hCOM,&ct)) err=5;
				   //установка временных интервалов
				   else{
					   if(!PurgeComm(hCOM,PURGE_TXCLEAR|PURGE_RXCLEAR|
						                  PURGE_TXABORT|PURGE_RXABORT))err=6;
					   //очистка буферов приёма/передачи
					   else{
						   if(!SetupComm(hCOM,2048,2048))err=7;
                           //размер буферов приёма-передачи,должно быть 
						   //больше максимальной длины сообщения
						   else{
							   if(!SetCommMask(hCOM,mask))err=8;
                               //установка маски отслеживаемых событий
						   }
					   }
				   }
			   }

	 }
 if(err>2)
 {ShowMessage("Ошибка инициализации порта");

 }
return err;
}
//------------------------------------------------------------------------------
DWORD _fastcall  Port232::WriteA(void *buf,int count)//запись в СОМ-порт
{
DWORD errWait=0;
wov.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);//true-ручная установка
ResetEvent(wov.hEvent);//-установили событие в ручную  //событие блокирует ожидающие нити
WriteFile(hCOM,buf,count,&wb,&wov);
errWait=WaitForSingleObject(wov.hEvent,1000);
if(errWait==WAIT_OBJECT_0)//  -1000 милисекунд - время ожидания
{SetEvent(wov.hEvent);//-сброс события //событие освобождает ожидающие нити
 err=GetOverlappedResult(hCOM,&wov,&wb,FALSE);//-false-не ждёт завершения вв/выв
 if(!err)// - ошибка чтения
  {wb=0;
  Application->MessageBox("RS:Ошибка записи","",MB_ICONSTOP);

  }
}else //ошибка при Wait
{ wb=0;//данные не приняты
  if(errWait==WAIT_TIMEOUT) //превышено время
    { Application->MessageBox("RS:Превышено время","",MB_ICONSTOP);

    }
  if(errWait==WAIT_FAILED)//неверный вызов самой функции
    {Application->MessageBox("Ошибка вызова Wait","",MB_ICONSTOP);
              
    }
}
CloseHandle(wov.hEvent);


	return wb;
}

//------------------------------------------------------------------------------
DWORD _fastcall Port232::WriteS(void *buf,int count)//запись в СОМ-порт
{
	if(!WriteFile(hCOM,buf,count,&wb,NULL))
 	   {ShowMessage("Ошибка записи в порт");

           return 0;}
	return wb;
}
//------------------------------------------------------------------------------
DWORD _fastcall Port232::ReadA(void *buf,int count)//чтение из СОМ-порта
{
DWORD errWait=0;
rov.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);//true-ручная установка
ResetEvent(rov.hEvent);//-установили событие в ручную  //событие блокирует ожидающие нити
ReadFile(hCOM,buf,count,&rb,&rov);
errWait=WaitForSingleObject(rov.hEvent,1000);
if(errWait==WAIT_OBJECT_0)//  -1000 милисекунд - время ожидания
{SetEvent(rov.hEvent);//-сброс события //событие освобождает ожидающие нити
 err=GetOverlappedResult(hCOM,&rov,&rb,FALSE);//-false-не ждёт завершения вв/выв
 if(!err)// - ошибка чтения
  {rb=0;
  Application->MessageBox("RS:Ошибка чтения","",MB_ICONSTOP);

  }
}else //ошибка при Wait
{ rb=0;//данные не приняты
  if(errWait==WAIT_TIMEOUT) //превышено время
    {Application->MessageBox("RS:Превышено время","",MB_ICONSTOP);

    }
  if(errWait==WAIT_FAILED)//неверный вызов самой функции
    {Application->MessageBox("Ошибка вызова Wait","",MB_ICONSTOP);
              
    }
}
CloseHandle(rov.hEvent);
	return rb;
	 
}

//-------------------------------------------------------------------------------
DWORD _fastcall Port232::ReadS(void *buf,int count)//чтение из СОМ-порта
{
  if(!ReadFile(hCOM,buf,count,&rb,NULL))
  {ShowMessage("RS232:Ошибка чтения из порта");

	return 0;}
	return rb;
}
//------------------------------------------------------------------------------
DWORD _fastcall Port232::PurgeBufs()//очистка буферов приёма/передачи
{
  if(!PurgeComm(hCOM,PURGE_TXCLEAR|PURGE_RXCLEAR|PURGE_TXABORT|PURGE_RXABORT))
{ShowMessage("Ошибка очистки буферов приёма/передачи");
	return 0;}
  return 1;
}
//------------------------------------------------------------------------------
DWORD _fastcall Port232::ClearError()//восстановление связи после ошибочной ситуации
						//с возвращением кода ошибки
{
DWORD ierr=0;COMSTAT stcom;AnsiString str;
if(ClearCommError(hCOM,&ierr,&stcom))
{
   switch (ierr)
   {case CE_BREAK   :str="Обнаружено состояние разрыва связи";break;
   case CE_FRAME   :str="Ошибка обрамления";break;
   case CE_IOE     :str="Ошибка ввода-вывода при работе с портом";break;
   case CE_MODE    :str="Запрошенный режим не поддерживается(или неверный HANDLE)";
	                break;
   case CE_OVERRUN :str="Ошибка перебега(следующий символ потерян)";break;
   case CE_RXOVER  :str="Переполнение приёмного буфера";break;
   case CE_RXPARITY:str="Ошибка чётности ";break;
   case CE_TXFULL  :str="Переполнение буфера передачи";break;
   default         :str="Ошибка работы коммуникационного порта";
   }
if(ierr!=0)ShowMessage(str);
}
	   return ierr;
}
//-------------------------------------------------------------------------------
DWORD _fastcall Port232::SetParamA(int n,DWORD BaudRate2,DWORD fParity2,DWORD StopBits2,
	               DWORD ByteSize2)//установка новых параметров передачи
{DWORD ierr=1;
	if(StopBits2!=0&&StopBits2!=1&&StopBits2!=2)
 	{ShowMessage("Количество стоп-бит задано неверно");ierr=0;}
	if(StopBits==1)StopBits=0;
	if(ByteSize2!=5&&ByteSize2!=6&&ByteSize2!=7&&ByteSize2!=8)
{ShowMessage("Количество информационных бит задано неверно");ierr=0;}
    if(fParity2!=true&&fParity2!=false&&fParity2!=0&&fParity2!=1)
 {ShowMessage("Контроль чётности задан неверно");ierr=0;}
    if(BaudRate2!=50&&BaudRate2!=75&&BaudRate2!=110&&BaudRate2!=150&&
	   BaudRate2!=300&&BaudRate2!=600&&BaudRate2!=1200&&BaudRate2!=2400&&
	   BaudRate2!=4800&&BaudRate2!=9600&&BaudRate2!=19200&&BaudRate2
                    !=38400&&BaudRate2!=57600&&BaudRate2!=115200)
{ShowMessage("Скорость передачи данных задана неверно");ierr=0;}
dcb.DCBlength=sizeof(dcb);
 dcb.BaudRate=BaudRate2;//скорость передачи данных
 dcb.fBinary=true;//двоичный режим обмена
 dcb.fParity=fParity2;//отключаем контроль чётности
 dcb.StopBits=StopBits2;//количество стоповых бит(=0 для 1 стоп-бита)
 dcb.ByteSize=ByteSize2;//число бит в кадре
 dcb.fNull=false;//нулевые байты не отбрасываютсяпри передаче
 dcb.Parity=NOPARITY;//выбор схемы контроля чётности
 if(!SetCommState(hCOM,&dcb))
 {err=0;
  ShowMessage("Ошибка инициализации порта");

 }
 	return ierr;

}
//------------------------------------------------------------------------------
DWORD _fastcall Port232::SetParamS(int n,DWORD BaudRate2,DWORD fParity2,
                       DWORD StopBits2,
	               DWORD ByteSize2)//установка новых параметров передачи
{DWORD ierr=1;
		if(StopBits2!=0&&StopBits2!=1&&StopBits2!=2)
 	{ShowMessage("Количество стоп-бит задано неверно");ierr=0;}
	if(StopBits==1)StopBits=0;
	if(ByteSize2!=5&&ByteSize2!=6&&ByteSize2!=7&&ByteSize2!=8)
//	{MessageBox("Количество информационных бит задано неверно",
//	MB_OK|MB_ICONEXCLAMATION);ierr=0;}
{ShowMessage("Количество информационных бит задано неверно");ierr=0;}
    if(fParity2!=true&&fParity2!=false&&fParity2!=0&&fParity2!=1)

// {MessageBox("Контроль чётности задан неверно",MB_OK|MB_ICONEXCLAMATION);ierr=0;}
{ShowMessage("Контроль чётности задан неверно");ierr=0;}
    if(BaudRate2!=50&&BaudRate2!=75&&BaudRate2!=110&&BaudRate2!=150&&
	   BaudRate2!=300&&BaudRate2!=600&&BaudRate2!=1200&&BaudRate2!=2400&&
	   BaudRate2!=4800&&BaudRate2!=9600&&BaudRate2!=19200&&BaudRate2
           !=38400&&
	   BaudRate2!=57600&&BaudRate2!=115200)
//	{MessageBox("Скорость передачи данных задана неверно",
//	MB_OK|MB_ICONEXCLAMATION);ierr=0;}
	{ShowMessage("Скорость передачи данных задана неверно");ierr=0;}
dcb.DCBlength=sizeof(dcb);
 dcb.BaudRate=BaudRate2;//скорость передачи данных
 dcb.fBinary=true;//двоичный режим обмена
 dcb.fParity=fParity2;//отключаем контроль чётности
 dcb.StopBits=StopBits2;//количество стоповых бит(=0 для 1 стоп-бита)
 dcb.ByteSize=ByteSize2;//число бит в кадре
 dcb.fNull=false;//нулевые байты не отбрасываютсяпри передаче
 dcb.Parity=NOPARITY;//выбор схемы контроля чётности
 if(!SetCommState(hCOM,&dcb))
 {err=0;
  ShowMessage("Ошибка инициализации порта");
            
 }

	return ierr;
}
//------------------------------------------------------------------------------
bool _fastcall Port232::FlushBufs()//передача остатка данных из буфера
{
	return FlushFileBuffers(hCOM);
}
//------------------------------------------------------------------------------
bool _fastcall Port232::Transmit(char cChar)//передача 1внеочередного байта в линию
{
	return TransmitCommChar(hCOM,cChar);
}
//------------------------------------------------------------------------------
bool _fastcall Port232::EscapeComm(DWORD dwFunc)//тонкое управление потоком
{
	return EscapeCommFunction(hCOM,dwFunc);
}
//------------------------------------------------------------------------------
bool _fastcall Port232::WaitA()//ожидание маски событий
{
	return WaitCommEvent(hCOM,&mask,&rov);

}
//------------------------------------------------------------------------------
bool _fastcall Port232::WaitS()
{
  return WaitCommEvent(hCOM,&mask,NULL);
}
//------------------------------------------------------------------------------
 void _fastcall Port232::ClosePort()
{
  if ( flagPort_85Old )
  {
    CloseHandle(hCOM);
  }
  Form_85Old_Main->OpenPortButton->Caption="ОТКРЫТЬ";
  flagPort_85Old = false;
}
//------------------------------------------------------------------------------
 _fastcall Port232::~Port232() // деструктор
{
        
}
//------------------------------------------------------------------------------
