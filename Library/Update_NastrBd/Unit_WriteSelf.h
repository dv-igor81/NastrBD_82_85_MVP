//---------------------------------------------------------------------------
#ifndef Unit_WriteSelfH
#define Unit_WriteSelfH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
#include "Unit_SharedTypes.h"
//---------------------------------------------------------------------------
class TWriteSelf
{
public:
  // �����������
  TWriteSelf();
  // ����������
  ~TWriteSelf();
  // ��� �: 1 - ��, 2 - ��, 3 - ��, 4 - ���� �� ������ (������ ������)
  // �� - ��������� ���������, ����������� �������������, ������ � ��������� ������������� ���������
  // �� - ������������� ���������, ����������� ��������� ����������, ������ � ��������� ������������� ���������
  // �� - ������������� ���������, ����������� ������������� ����������, ������ �� ������ � �� ���������
  int WhoAmI();

  int TWriteSelf::WhoAmFile(
    AnsiString fileNameLocal,
    TFileBuffer & fileBufLocal);

  void MyWriteFile();
  void UpdatedWriteFile();   
  void MyWriteFile(TFileBuffer & fileBufLocal);// �������� ����
  void MyWinExec(); // ��������� ����
  void SetReady(); // ���������� ���� ���������� (��� ������ ��������)
  bool Reset(); // ���� ������� �� ����� ��������
  bool Reset(TFileBuffer & fileBufLocal);  

  AnsiString AnalisFile();
  AnsiString AnalisFileVerPo();

  int ReadUpdatedProg(
    AnsiString locFileName,
    AnsiString remFileName,
    AnsiString remoteFileNameFake);

  int GetFlag()
  {
    return _flagDeystviya;
  }
  AnsiString GetNewFileName();
  // ����� ���������
  int StartProgramm();    
private:
  void Mess( char * text, int Level );


  AnsiString fileName;  // ��� ����� ������� ���������
  AnsiString InfofillName; // ��� ����� ������������� ���������

  TFileBuffer _fileBufSelf; // �������� �����
  TFileBuffer _fileBufUpdate; // �������� �����

  char msfFormated[256];


  int _flagDeystviya; //
  int _bfDebuf;
  bool _bfReady;
};
//---------------------------------------------------------------------------
#endif
