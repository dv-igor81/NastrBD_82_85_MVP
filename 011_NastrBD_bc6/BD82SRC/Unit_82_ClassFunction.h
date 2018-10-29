//---------------------------------------------------------------------------
#ifndef Unit_82_ClassFunctionH
#define Unit_82_ClassFunctionH
#include "Unit_82_ComPortReadWrite.h"
//---------------------------------------------------------------------------
const unsigned char razmer = 200; //
class Function_t
{
public:
  Function_t(void); // �����������

  void GetParam(char *, double var);
  ComPortReadWrite_t * Cprw; // ������ ������
  unsigned int AddrBD; // ����� ��
  unsigned int ComPortNum; // ����� ���-�����

  char * Display(int var);
  void DIAcopy2(char * S1, char * S2, unsigned char var1,  unsigned char var2);
  unsigned int Next(void);

  int DIAcpy(char * var1, char * var2);
  void DIAcopy(char * S, unsigned char var);
  int Stop(void);
  int EndIstochnik(void);

  //unsigned int t; // ����� ����� ���� [����.]
  char arr[razmer];
  char arr2[razmer];

  char forReport[razmer];

  char massaIstochnika[razmer];
  char tipIctochnika[razmer];

  bool bAddrBDArr[8];
  unsigned short AddrBDArr[8];
  double m; // ����� ���������

  bool FlagMassyItipa; // = true ���� ���� ����� �� �����, ����� false
  unsigned int intervZad; // �������� �������� �������
  char ProgrammState; // ������� ��������� ���������

  unsigned int Arr_Naf[8]; // �������� �������
  unsigned int Arr_Nai[8]; // �������� �������
  unsigned int Arr_Svetodiod[8]; // �������� �������
  unsigned int Arr_Tceziya[8]; // �������� �������


private:
  char String[8][razmer];

  unsigned int upravlenie; // ��� ���������� ������������ ��������� �� �����
  bool bFlagPotoka;

  unsigned int Ns;
  double Nf; // ��������������� ����
  unsigned int Nf1;
  unsigned int Nf2;

  unsigned int S;
};

#endif
