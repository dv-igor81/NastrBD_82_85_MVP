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
 _fastcall Port232::Port232()//�����������
{
BaudRate=115200;
fParity=false;//�������� �������� ��������
StopBits=ONESTOPBIT;
ByteSize=8;
memset(&wov,0,sizeof(wov)); //��������� ��������
memset(&rov,0,sizeof(rov));
memset(&dcb,0,sizeof(dcb));
wov.hEvent=rov.hEvent=0;
mask=EV_RXCHAR;
}
//------------------------------------------------------------------------------
bool _fastcall Port232::OpenA(int n)//�������� ����������� ��������
{
AnsiString imq;
imq=StrToInt(n);
imq="COM"+imq;
char *cha1=imq.c_str();
hCOM=CreateFile(cha1,GENERIC_WRITE|GENERIC_READ,0,NULL,
     OPEN_EXISTING,
     FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED,NULL);
if(hCOM==INVALID_HANDLE_VALUE)
  {ShowMessage("������ �������� �����");

  return 0;}

return 1;
}
//------------------------------------------------------------------------------
bool _fastcall  Port232::OpenS(int n)//�������� ���������� ��������
{
AnsiString imq;
imq=StrToInt(n);
imq="COM"+imq;
char *cha1=imq.c_str();
hCOM=CreateFile(cha1,GENERIC_WRITE|GENERIC_READ,0,NULL,
				OPEN_EXISTING,0,NULL);
if(hCOM==INVALID_HANDLE_VALUE)
 {ShowMessage("������ �������� �����");

      return 0;}
return 1;
}
//------------------------------------------------------------------------------
DWORD _fastcall Port232::PortInit()//�������� � ������������� ���-�����
{err=1;
     		   if(!GetCommState(hCOM,&dcb))err=3;
			   //��������� DCB ����������� � ��������� �����
		   else{
			   dcb.DCBlength=sizeof(dcb);//
			   dcb.BaudRate=BaudRate;//�������� �������� ������
			   dcb.fBinary=true;//�������� ����� ������
			   dcb.fParity=fParity;//���������� �������� ��������
                           dcb.Parity=Parity;//����� ����� �������� ��������
			   dcb.StopBits=StopBits;//���������� �������� ���(=0 ��� 1 ����-����)
			   dcb.ByteSize=ByteSize;//����� ��� � �����
			   dcb.fNull=false;//������� ����� �� ���������������� ��������
			   dcb.fAbortOnError=true;//������� ���������� �����������
                           dcb.fErrorChar=false;//��������� �� �������������
//������ �������� � ��������� ��������� �� ������ ���������� ����� ErrorChar
                           dcb.ErrorChar=0;
                           dcb.fDtrControl=DTR_CONTROL_DISABLE;
                           dcb.fRtsControl=RTS_CONTROL_DISABLE;
                           dcb.fTXContinueOnXoff=true;
//��������� ��������� ��������� - �������� � ����
//dcb.fOutCtsFlow,dcb.fOutDsrFlow,dcb.fDtrControl,dcb.DsrSensitivity,
//dcb.fTxContinueOnXoff,dcb.fOutX,dcb.fInX,dcb.fErrorChar,dcb.fRtsControl,
//dcb.fAboutOnError,dcb.fDummy,dcb.wReserved,dcb.XonLim,dcb.XoffLim,
//dcb.XonChar,dcb.XoffChar,dcb.ErrorChar,dcb.EofChar,dcb.EvtChar,dcb.wReservedl
dcb.fOutxCtsFlow=false ;//����� �������� �� �������� CTS
dcb.fOutxDsrFlow=false ;//����� �������� �� �������� DSR
dcb.fDsrSensitivity=false ;//���������������� �������� � ��������� ����� DSR
dcb.fTXContinueOnXoff=false ;//��� XON/XOFF
dcb.fOutX=false ;//��� XON/XOFF
dcb.fInX=false ;//��� XON/XOFF
dcb.fErrorChar=false ; //������ �������� � ������� ��������
dcb.fAbortOnError=false ;//������������� ���� �������� ������/������ ��� ������������� ������
dcb.fDummy2=0 ;//�� ������������
//dcb.wReserved=0;//�� ������������
dcb.XonLim=0 ;//����������� ����� �������� � ������� ������ ����� �������� ������� XON
dcb.XoffLim=0 ;//������������ ���������� ���� � ������� ������ ����� �������� ������� XOFF
dcb.XonChar=0;//������ XON
dcb.XoffChar=0;//������ XOFF
dcb.ErrorChar=0;//������ ������ �������� � ��������� ��������
dcb.EofChar=0;//������ ������������ � ����� ������
dcb.EvtChar=0;//������, �������������� ��� ������������ � �������
dcb.wReserved1=0 ;//�� ������������

                            //������/������ ��� ������
			   if(!SetCommState(hCOM,&dcb))err=4;
			   //���������������� �����
			   else{
//		    ct.ReadIntervalTimeout=100;//=0-������ ����-��� �� ������������
		    ct.ReadIntervalTimeout=0xffffffff;//=0-������ ����-��� �� ������������
//���� ��� ������ ������>MAXDWORD����-������ ������
//2048*10\9600=2200����-����� ���������� ������,2048���� -������ ������-�� SetupComm
//(���-�� ��������)*10���\db.BaudRate=����� ���������� ���� ��������
			ct.ReadTotalTimeoutConstant=10;
			ct.ReadTotalTimeoutMultiplier=2;
			ct.WriteTotalTimeoutConstant=100;
			ct.WriteTotalTimeoutMultiplier=100;

				   if(!SetCommTimeouts(hCOM,&ct)) err=5;
				   //��������� ��������� ����������
				   else{
					   if(!PurgeComm(hCOM,PURGE_TXCLEAR|PURGE_RXCLEAR|
						                  PURGE_TXABORT|PURGE_RXABORT))err=6;
					   //������� ������� �����/��������
					   else{
						   if(!SetupComm(hCOM,2048,2048))err=7;
                           //������ ������� �����-��������,������ ���� 
						   //������ ������������ ����� ���������
						   else{
							   if(!SetCommMask(hCOM,mask))err=8;
                               //��������� ����� ������������� �������
						   }
					   }
				   }
			   }

	 }
 if(err>2)
 {ShowMessage("������ ������������� �����");

 }
return err;
}
//------------------------------------------------------------------------------
DWORD _fastcall  Port232::WriteA(void *buf,int count)//������ � ���-����
{
DWORD errWait=0;
wov.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);//true-������ ���������
ResetEvent(wov.hEvent);//-���������� ������� � ������  //������� ��������� ��������� ����
WriteFile(hCOM,buf,count,&wb,&wov);
errWait=WaitForSingleObject(wov.hEvent,1000);
if(errWait==WAIT_OBJECT_0)//  -1000 ���������� - ����� ��������
{SetEvent(wov.hEvent);//-����� ������� //������� ����������� ��������� ����
 err=GetOverlappedResult(hCOM,&wov,&wb,FALSE);//-false-�� ��� ���������� ��/���
 if(!err)// - ������ ������
  {wb=0;
  Application->MessageBox("RS:������ ������","",MB_ICONSTOP);

  }
}else //������ ��� Wait
{ wb=0;//������ �� �������
  if(errWait==WAIT_TIMEOUT) //��������� �����
    { Application->MessageBox("RS:��������� �����","",MB_ICONSTOP);

    }
  if(errWait==WAIT_FAILED)//�������� ����� ����� �������
    {Application->MessageBox("������ ������ Wait","",MB_ICONSTOP);
              
    }
}
CloseHandle(wov.hEvent);


	return wb;
}

//------------------------------------------------------------------------------
DWORD _fastcall Port232::WriteS(void *buf,int count)//������ � ���-����
{
	if(!WriteFile(hCOM,buf,count,&wb,NULL))
 	   {ShowMessage("������ ������ � ����");

           return 0;}
	return wb;
}
//------------------------------------------------------------------------------
DWORD _fastcall Port232::ReadA(void *buf,int count)//������ �� ���-�����
{
DWORD errWait=0;
rov.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);//true-������ ���������
ResetEvent(rov.hEvent);//-���������� ������� � ������  //������� ��������� ��������� ����
ReadFile(hCOM,buf,count,&rb,&rov);
errWait=WaitForSingleObject(rov.hEvent,1000);
if(errWait==WAIT_OBJECT_0)//  -1000 ���������� - ����� ��������
{SetEvent(rov.hEvent);//-����� ������� //������� ����������� ��������� ����
 err=GetOverlappedResult(hCOM,&rov,&rb,FALSE);//-false-�� ��� ���������� ��/���
 if(!err)// - ������ ������
  {rb=0;
  Application->MessageBox("RS:������ ������","",MB_ICONSTOP);

  }
}else //������ ��� Wait
{ rb=0;//������ �� �������
  if(errWait==WAIT_TIMEOUT) //��������� �����
    {Application->MessageBox("RS:��������� �����","",MB_ICONSTOP);

    }
  if(errWait==WAIT_FAILED)//�������� ����� ����� �������
    {Application->MessageBox("������ ������ Wait","",MB_ICONSTOP);
              
    }
}
CloseHandle(rov.hEvent);
	return rb;
	 
}

//-------------------------------------------------------------------------------
DWORD _fastcall Port232::ReadS(void *buf,int count)//������ �� ���-�����
{
  if(!ReadFile(hCOM,buf,count,&rb,NULL))
  {ShowMessage("RS232:������ ������ �� �����");

	return 0;}
	return rb;
}
//------------------------------------------------------------------------------
DWORD _fastcall Port232::PurgeBufs()//������� ������� �����/��������
{
  if(!PurgeComm(hCOM,PURGE_TXCLEAR|PURGE_RXCLEAR|PURGE_TXABORT|PURGE_RXABORT))
{ShowMessage("������ ������� ������� �����/��������");
	return 0;}
  return 1;
}
//------------------------------------------------------------------------------
DWORD _fastcall Port232::ClearError()//�������������� ����� ����� ��������� ��������
						//� ������������ ���� ������
{
DWORD ierr=0;COMSTAT stcom;AnsiString str;
if(ClearCommError(hCOM,&ierr,&stcom))
{
   switch (ierr)
   {case CE_BREAK   :str="���������� ��������� ������� �����";break;
   case CE_FRAME   :str="������ ����������";break;
   case CE_IOE     :str="������ �����-������ ��� ������ � ������";break;
   case CE_MODE    :str="����������� ����� �� ��������������(��� �������� HANDLE)";
	                break;
   case CE_OVERRUN :str="������ ��������(��������� ������ �������)";break;
   case CE_RXOVER  :str="������������ �������� ������";break;
   case CE_RXPARITY:str="������ �������� ";break;
   case CE_TXFULL  :str="������������ ������ ��������";break;
   default         :str="������ ������ ����������������� �����";
   }
if(ierr!=0)ShowMessage(str);
}
	   return ierr;
}
//-------------------------------------------------------------------------------
DWORD _fastcall Port232::SetParamA(int n,DWORD BaudRate2,DWORD fParity2,DWORD StopBits2,
	               DWORD ByteSize2)//��������� ����� ���������� ��������
{DWORD ierr=1;
	if(StopBits2!=0&&StopBits2!=1&&StopBits2!=2)
 	{ShowMessage("���������� ����-��� ������ �������");ierr=0;}
	if(StopBits==1)StopBits=0;
	if(ByteSize2!=5&&ByteSize2!=6&&ByteSize2!=7&&ByteSize2!=8)
{ShowMessage("���������� �������������� ��� ������ �������");ierr=0;}
    if(fParity2!=true&&fParity2!=false&&fParity2!=0&&fParity2!=1)
 {ShowMessage("�������� �������� ����� �������");ierr=0;}
    if(BaudRate2!=50&&BaudRate2!=75&&BaudRate2!=110&&BaudRate2!=150&&
	   BaudRate2!=300&&BaudRate2!=600&&BaudRate2!=1200&&BaudRate2!=2400&&
	   BaudRate2!=4800&&BaudRate2!=9600&&BaudRate2!=19200&&BaudRate2
                    !=38400&&BaudRate2!=57600&&BaudRate2!=115200)
{ShowMessage("�������� �������� ������ ������ �������");ierr=0;}
dcb.DCBlength=sizeof(dcb);
 dcb.BaudRate=BaudRate2;//�������� �������� ������
 dcb.fBinary=true;//�������� ����� ������
 dcb.fParity=fParity2;//��������� �������� ��������
 dcb.StopBits=StopBits2;//���������� �������� ���(=0 ��� 1 ����-����)
 dcb.ByteSize=ByteSize2;//����� ��� � �����
 dcb.fNull=false;//������� ����� �� ���������������� ��������
 dcb.Parity=NOPARITY;//����� ����� �������� ��������
 if(!SetCommState(hCOM,&dcb))
 {err=0;
  ShowMessage("������ ������������� �����");

 }
 	return ierr;

}
//------------------------------------------------------------------------------
DWORD _fastcall Port232::SetParamS(int n,DWORD BaudRate2,DWORD fParity2,
                       DWORD StopBits2,
	               DWORD ByteSize2)//��������� ����� ���������� ��������
{DWORD ierr=1;
		if(StopBits2!=0&&StopBits2!=1&&StopBits2!=2)
 	{ShowMessage("���������� ����-��� ������ �������");ierr=0;}
	if(StopBits==1)StopBits=0;
	if(ByteSize2!=5&&ByteSize2!=6&&ByteSize2!=7&&ByteSize2!=8)
//	{MessageBox("���������� �������������� ��� ������ �������",
//	MB_OK|MB_ICONEXCLAMATION);ierr=0;}
{ShowMessage("���������� �������������� ��� ������ �������");ierr=0;}
    if(fParity2!=true&&fParity2!=false&&fParity2!=0&&fParity2!=1)

// {MessageBox("�������� �������� ����� �������",MB_OK|MB_ICONEXCLAMATION);ierr=0;}
{ShowMessage("�������� �������� ����� �������");ierr=0;}
    if(BaudRate2!=50&&BaudRate2!=75&&BaudRate2!=110&&BaudRate2!=150&&
	   BaudRate2!=300&&BaudRate2!=600&&BaudRate2!=1200&&BaudRate2!=2400&&
	   BaudRate2!=4800&&BaudRate2!=9600&&BaudRate2!=19200&&BaudRate2
           !=38400&&
	   BaudRate2!=57600&&BaudRate2!=115200)
//	{MessageBox("�������� �������� ������ ������ �������",
//	MB_OK|MB_ICONEXCLAMATION);ierr=0;}
	{ShowMessage("�������� �������� ������ ������ �������");ierr=0;}
dcb.DCBlength=sizeof(dcb);
 dcb.BaudRate=BaudRate2;//�������� �������� ������
 dcb.fBinary=true;//�������� ����� ������
 dcb.fParity=fParity2;//��������� �������� ��������
 dcb.StopBits=StopBits2;//���������� �������� ���(=0 ��� 1 ����-����)
 dcb.ByteSize=ByteSize2;//����� ��� � �����
 dcb.fNull=false;//������� ����� �� ���������������� ��������
 dcb.Parity=NOPARITY;//����� ����� �������� ��������
 if(!SetCommState(hCOM,&dcb))
 {err=0;
  ShowMessage("������ ������������� �����");
            
 }

	return ierr;
}
//------------------------------------------------------------------------------
bool _fastcall Port232::FlushBufs()//�������� ������� ������ �� ������
{
	return FlushFileBuffers(hCOM);
}
//------------------------------------------------------------------------------
bool _fastcall Port232::Transmit(char cChar)//�������� 1������������� ����� � �����
{
	return TransmitCommChar(hCOM,cChar);
}
//------------------------------------------------------------------------------
bool _fastcall Port232::EscapeComm(DWORD dwFunc)//������ ���������� �������
{
	return EscapeCommFunction(hCOM,dwFunc);
}
//------------------------------------------------------------------------------
bool _fastcall Port232::WaitA()//�������� ����� �������
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
  Form_85Old_Main->OpenPortButton->Caption="�������";
  flagPort_85Old = false;
}
//------------------------------------------------------------------------------
 _fastcall Port232::~Port232() // ����������
{
        
}
//------------------------------------------------------------------------------
