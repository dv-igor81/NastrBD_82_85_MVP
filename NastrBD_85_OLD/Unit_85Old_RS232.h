//---------------------------------------------------------------------------
// Port232.h
//---------------------------------------------------------------------------
#ifndef PORT232_H
#define PORT232_H
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
class Port232
{
private:

	DWORD wb,rb;
	bool err;
	DWORD mask;
	OVERLAPPED wov,rov;
	DWORD fParity,StopBits,ByteSize,Parity;
	//BaudRate-скорость передачи данных(бит/сек)(9600)
	//fParity-контроль чётности(0=false)
	//StopBits-количество стоповых бит(0-1бит,1-1.5бит,2-2бита)
	//ByteSize-число информационных бит(8)
public: DCB dcb;
        COMMTIMEOUTS ct;
      DWORD BaudRate;
	HANDLE hCOM;
	_fastcall Port232();
	bool _fastcall OpenA(int n);//открытие порта для асинхронной передачи данных
	bool _fastcall OpenS(int n);//открытие порта для синхронной передачи данных

	DWORD _fastcall PortInit();//n-номер СОМ-порта(инициализация порта)

	DWORD _fastcall WriteA(void *buf,int count);// запись в порт-возвращает кол-во символов
	DWORD _fastcall WriteS(void *buf,int count);

	DWORD _fastcall ReadA(void *buf,int count); // чтение из порта-возвращает кол-во символо
	DWORD _fastcall ReadS(void *buf,int count);

	DWORD _fastcall SetParamA(int n,DWORD BaudRate,DWORD fParity,DWORD StopBits,
	               DWORD ByteSize);//установка новых параметров передачи данных
	DWORD _fastcall SetParamS(int n,DWORD BaudRate,DWORD fParity,DWORD StopBits,
	               DWORD ByteSize);

	DWORD _fastcall PurgeBufs();//очистка буферов приёма/передачи
	DWORD  _fastcall ClearError();//восстановление связи после ошибки с возвратом кода ошибки
	bool  _fastcall FlushBufs();//передача остатков данных(перед PurgeBuf)
	bool  _fastcall Transmit(char cChar);//передача 1 внеочередного байта в линию
	//несмотря на наличие данных в очереди приёмника и перед этими данными
	//только при синхронной передаче
	bool  _fastcall EscapeComm(DWORD dwFunc);//тонкое управление потоком

	bool _fastcall WaitA();//ожидание события по маске
	bool _fastcall WaitS();
	//функция чтения вызывается после получения первого символа
         void _fastcall ClosePort();
	 _fastcall ~Port232();

};
#endif;




/*Пример синхронной передачи данных через COM2
  ( при асинхронной - ф-ции с "A")
Port com;
if(com.OpenS(2))  -открытие COM2
{
if(com.PortInit()==1)   - инициализация порта
{   DWORD err1,err2;
	com.PurgeBufs();    - очистка буферов
	char *buf_out="TESTtest";
	char buf_in[15];
	    err1=com.WriteS(buf_out,8); - запись в порт
	if(err1){
		com.WaitS();  - ожидание маски(символ принят и помещён в приёмный буфер)
	    err2=com.ReadS(buf_in,8); - чтение из порта
		if(!err1|!err2)com.ClearError(); -при ошибке восстановление связи
		                                  с возвратом ошибки
	}
ввод новых параметров:
if(com.SetParamS(2,9600,0,0,8)!=1)-ошибка установки новых параметров;
}
}*/
