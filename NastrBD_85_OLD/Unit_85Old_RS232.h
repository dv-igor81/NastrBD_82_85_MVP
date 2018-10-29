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
	//BaudRate-�������� �������� ������(���/���)(9600)
	//fParity-�������� ��������(0=false)
	//StopBits-���������� �������� ���(0-1���,1-1.5���,2-2����)
	//ByteSize-����� �������������� ���(8)
public: DCB dcb;
        COMMTIMEOUTS ct;
      DWORD BaudRate;
	HANDLE hCOM;
	_fastcall Port232();
	bool _fastcall OpenA(int n);//�������� ����� ��� ����������� �������� ������
	bool _fastcall OpenS(int n);//�������� ����� ��� ���������� �������� ������

	DWORD _fastcall PortInit();//n-����� ���-�����(������������� �����)

	DWORD _fastcall WriteA(void *buf,int count);// ������ � ����-���������� ���-�� ��������
	DWORD _fastcall WriteS(void *buf,int count);

	DWORD _fastcall ReadA(void *buf,int count); // ������ �� �����-���������� ���-�� �������
	DWORD _fastcall ReadS(void *buf,int count);

	DWORD _fastcall SetParamA(int n,DWORD BaudRate,DWORD fParity,DWORD StopBits,
	               DWORD ByteSize);//��������� ����� ���������� �������� ������
	DWORD _fastcall SetParamS(int n,DWORD BaudRate,DWORD fParity,DWORD StopBits,
	               DWORD ByteSize);

	DWORD _fastcall PurgeBufs();//������� ������� �����/��������
	DWORD  _fastcall ClearError();//�������������� ����� ����� ������ � ��������� ���� ������
	bool  _fastcall FlushBufs();//�������� �������� ������(����� PurgeBuf)
	bool  _fastcall Transmit(char cChar);//�������� 1 ������������� ����� � �����
	//�������� �� ������� ������ � ������� �������� � ����� ����� �������
	//������ ��� ���������� ��������
	bool  _fastcall EscapeComm(DWORD dwFunc);//������ ���������� �������

	bool _fastcall WaitA();//�������� ������� �� �����
	bool _fastcall WaitS();
	//������� ������ ���������� ����� ��������� ������� �������
         void _fastcall ClosePort();
	 _fastcall ~Port232();

};
#endif;




/*������ ���������� �������� ������ ����� COM2
  ( ��� ����������� - �-��� � "A")
Port com;
if(com.OpenS(2))  -�������� COM2
{
if(com.PortInit()==1)   - ������������� �����
{   DWORD err1,err2;
	com.PurgeBufs();    - ������� �������
	char *buf_out="TESTtest";
	char buf_in[15];
	    err1=com.WriteS(buf_out,8); - ������ � ����
	if(err1){
		com.WaitS();  - �������� �����(������ ������ � ������� � ������� �����)
	    err2=com.ReadS(buf_in,8); - ������ �� �����
		if(!err1|!err2)com.ClearError(); -��� ������ �������������� �����
		                                  � ��������� ������
	}
���� ����� ����������:
if(com.SetParamS(2,9600,0,0,8)!=1)-������ ��������� ����� ����������;
}
}*/
