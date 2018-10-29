//---------------------------------------------------------------------------
#pragma hdrstop
#include "Unit_82_ClassFunction.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)

void Function_t::DIAcopy(char * S, unsigned char var)
{
  for (int i = 0; (i < razmer) && (S != 0) ; i++)
  {
	String[var-1][i] = S[i];
  }
}
//----------------------------------------------------------------------------
void Function_t::DIAcopy2(char * S1, char * S2, unsigned char var1,  unsigned char var2)
{
  int i;
  for (i = 0; (i < razmer) && (i < var1) && (S1 != 0) ; i++)
  {
	massaIstochnika[i] = S1[i];
  }
  massaIstochnika[i] = '\0';
  for (i = 0; (i < razmer) && (i < var2) && (S2 != 0) ; i++)
  {
	tipIctochnika[i] = S2[i];
  }
  tipIctochnika[i] = '\0';
}
//---------------------------------------------------------------------------
char * Function_t::Display(int var)
{
  if (ProgrammState == -1)
  {
    if (7 == var) // ��� ���� �������
    {
      ProgrammState = 0;
    }
    return String[var];
  }
  if (ProgrammState == 0)
  {
    DIAcopy("", var); // �������� ������ � ������� var
  }
  if ( ProgrammState == 0 )
  {
    sprintf(this->arr, "");
    sprintf(this->arr2, " ������� ������ \"�����\" ��� ������ ���������� ����");
  }
  if ( ProgrammState == 1 )
  {
    sprintf(this->arr2, " ��� ����� ���������� ���� Nf1");
  }
  if ( ProgrammState == 3 )
  {
    sprintf(this->arr, "");
    sprintf(this->arr2, " ������� ����� � ��� ���������");
  }
  if ( ProgrammState == 4 )
  {
    sprintf(this->arr, "");
    sprintf(this->arr2, " ��� ����� ���� �� ���������");
  }
  if ( ProgrammState == 7 )
  {
    sprintf(this->arr, "");
    sprintf(this->arr2, " ��� ����� ��������� ���� Nf2");
  }
  if ( ProgrammState == 8 )
  {
    sprintf(this->arr, "");
    sprintf(this->arr2, " ��� ����� ��������� ���� Nf2");
  }
  //===
  if ( ProgrammState == 1 || ProgrammState == 4 )
  {
    for (int i = 0; i < 8; i++)
    {
      if (this->bAddrBDArr[i] == true)
      {
      	if ( this->Cprw->bFlagOprosa[i+1] == 0 )
      	{
      	  sprintf(this->String[i],
              "��: %0.1d, t: %05.01f ���, ���. ����: %.05d, ����. ����: %06.2f, �����. ������. ��: %.02d, Err1: %.02d, Err2: %.02d",
	      i+1,
	      double(this->Cprw->t)/1000.0,
	      this->Cprw->Data.SumSchet[i],
	      this->Cprw->Data.SredSchet[i],
	      this->Cprw->N1[i],
	      this->Cprw->N2[i],
	      this->Cprw->N3[i]
          );
        }
	else
	{
	  sprintf(this->String[i],
              "��: %0.1d, t: %05.01f ���, ��� ������ �����: %d",
	      i+1,
	      double(this->Cprw->t)/1000.0,
	      this->Cprw->ErrorCode[i]
          );
        }
      }
      else
      {
      	sprintf(this->String[i], "");
      }
    }
    sprintf(this->arr, "dT = %.3d ����, dTmax = %.4d ����", this->Cprw->dT, this->Cprw->dTmax);
  }
  if (ProgrammState == 2 || ProgrammState == 5 || ProgrammState == 6 || ProgrammState == 7 || ProgrammState == 8 )
  {
    if ( ProgrammState == 2 )
    {
      ProgrammState = 3; // ������ �������� ���� ���������
    }
    if ( ProgrammState == 5 )
    {
      ProgrammState = 3; // ������ �� � ������
    }
    if ( ProgrammState == 8 )
    {
      ProgrammState = 0; // ������ �� � ������
    }


    for ( int i = 0; i < 8; i++ )
    {
      if ( this->bAddrBDArr[i] == true )
      {
	if ( this->Cprw->bFlagOprosa[i+1] == 0 )
	{
	  sprintf(this->String[i],
	      "��: %0.1d, t: %05.01f ���, ���. ����: %.05d, ����. ����: %06.2f, �����. ������. ��: %.02d, Err1: %.02d, Err2: %.02d",
	      i+1,
	      double(this->Cprw->t)/1000.0,
	      this->Cprw->Data.SumSchet[i],
	      this->Cprw->Data.SredSchet[i],
	      this->Cprw->N1[i],
	      this->Cprw->N2[i],
	      this->Cprw->N3[i] );
        }
	else
	{
	  sprintf(this->String[i],
	      "��: %0.1d, t: %05.01f ���, ��� ������ �����: %d",
	      i+1,
	      double(this->Cprw->t)/1000.0,
	      this->Cprw->ErrorCode[i] );
        }
      }
      else
      {
	sprintf(this->String[i], "");
      }
    }
    sprintf(this->arr, "dT = %.3d ����, dTmax = %.4d ����", this->Cprw->dT, this->Cprw->dTmax);
  }
  if ( var >= 0 )
  {
    return this->String[var];
  }
  else if ( var == -1 )
  {
    return this->arr;
  }
  else if ( var == -2 )
  {
    return this->arr2;
  }
}
//---------------------------------------------------------------------------
unsigned int Function_t::Next(void)
{
  WORD Year, Month, Day; // ���������� ��� �������� ����
  WORD Hour, Min, Sec, MSec; // ���������� ��� �������� �����
  int length; // ��� ������� sprintf (������)

  this->Cprw->AddrBD = this->AddrBD; // ����������
  if ( ProgrammState == -1 )
  {
    upravlenie &= ~(1 << 0); // �� �������� ��� ����� ���� "����� ���������"
    upravlenie &= ~(1 << 1); // �� �������� ��� ����� ���� "��� ���������"
    upravlenie |= (1 << 2); // �������� ��� ����� ���� "����� ��"
    upravlenie |= (1 << 3); // �������� ��� ����� ���� "����� COM-�����"
    upravlenie &= ~(1 << 4); // ���������� ������
    upravlenie |= (1 << 5); // �������� ������ "Next"
    upravlenie &= ~(1 << 6); // �� �������� ������ "End" ��������� ������ � ����������� � ������� � ������ ��������� ����
    upravlenie |= (1 << 7); // �������� ������ ������ ��
    return upravlenie;
  }
  if ( ProgrammState == 0 )
  {
    char id[10];
    sprintf(id, "COM%d", ComPortNum);
    for (int i = 0; i < 10; i++)
    {
      this->Cprw->DEVID[i] = (wchar_t)id[i];
    }
    if ( this->Cprw->RSConnect(this->Cprw->DEVID) == 0 ) // ���� ��� ������ �������� ���-�����
    {
      upravlenie &= ~(1 << 0); // �� �������� ��� ����� ���� "����� ���������"
      upravlenie &= ~(1 << 1); // �� �������� ��� ����� ���� "��� ���������"
      upravlenie &= ~(1 << 2); // �� �������� ��� ����� ���� "����� ��"
      upravlenie &= ~(1 << 3); // �� �������� ��� ����� ���� "����� COM-�����"
      upravlenie |= (1 << 4); // �������� ������
      upravlenie &= ~(1 << 5); // �� �������� ������ "Next"
      upravlenie &= ~(1 << 7); // �� �������� ������ ������ ��
      ProgrammState = 1;
      this->Cprw->NomIstoch = 0;
      for (int i = 0; i < 8; i++)
      {
      	this->Cprw->Data.flagGetSerialNum[i] = false;
      	this->Cprw->Data.flagSetTimeInterval[i] = false;
      }
    }
    else
    {
      upravlenie &= ~(1 << 0); // �� �������� ��� ����� ���� "����� ���������"
      upravlenie &= ~(1 << 1); // �� �������� ��� ����� ���� "��� ���������"
      upravlenie |= (1 << 2); // �������� ��� ����� ���� "����� ��"
      upravlenie |= (1 << 3); // �������� ��� ����� ���� "����� COM-�����"
      upravlenie &= ~(1 << 4); // ���������� ������
      upravlenie |= (1 << 5); // �������� ������ "Next"
      this->Cprw->RSDisConnect();
      sprintf(this->String[0],
    	  "������ ��� ������� ������� COM-���� "
      );
    }
    return upravlenie;
  }
  if ( ProgrammState == 1 ) // ���� ����� ���� ����� ����������
  {
    if ( bFlagPotoka == true )
    {
      this->Cprw->Resume(); // ������ 200 ��. ������ ������
      FormErrorReport->Memo1->Lines->Add(this->Cprw->Str_err);
    }
    else
    {
      this->Cprw->OprosBD_Arr(); // ������ 200 ��. ������ ������
    }
    if ( this->Cprw->t == this->intervZad ) // ���� ����� ���� ����������
    { // � �-��� Reset ���������� ��������� t, ������� t ������ �� ������ ComPortReadWrite_t
      upravlenie |= (1 << 0); // �������� ��� ����� ���� "����� ���������"
      upravlenie |= (1 << 1); // �������� ��� ����� ���� "��� ���������"
      upravlenie |= (1 << 2); // �������� ��� ����� ���� "����� ��"
      upravlenie |= (1 << 3); // �������� ��� ����� ���� "����� COM-�����"
      upravlenie &= ~(1 << 4); // ���������� ������
      upravlenie |= (1 << 5); // �������� ������ "Next"
      this->Cprw->RSDisConnect();
      ProgrammState = 2;
      for (int i = 0; i < 8; i++)
      {
        if (this->bAddrBDArr[i] == true)
	{
	  this->Cprw->DataI.SumSchet[i] = this->Cprw->Data.SumSchet[i];
	  this->Cprw->DataI.SredSchet[i] = this->Cprw->Data.SredSchet[i];
        }
      }
    }
    return upravlenie;
  }
  if ( ProgrammState == 3 ) // ���� ����� ���� �� ���������
  {
    char id[10];
    sprintf(id, "COM%d", ComPortNum);
    for ( int i = 0; i < 10; i++ )
    {
      this->Cprw->DEVID[i] = (wchar_t)id[i];
    }
    if ( FlagMassyItipa == false ) // = true ���� ���� ����� �� �����, ����� false
    {
      sprintf(this->arr2, "������� ����� � ��� ���������");
      return upravlenie;
    }
    if ( this->Cprw->RSConnect(this->Cprw->DEVID) == 0 ) // ���� ��� ������ �������� ���-�����
    {
      upravlenie &= ~(1 << 0); // �� �������� ��� ����� ���� "����� ���������"
      upravlenie &= ~(1 << 1); // �� �������� ��� ����� ���� "��� ���������"
      upravlenie &= ~(1 << 2); // �� �������� ��� ����� ���� "����� ��"
      upravlenie &= ~(1 << 3); // �� �������� ��� ����� ���� "����� COM-�����"
      upravlenie |= (1 << 4); // �������� ������
      upravlenie &= ~(1 << 5); // �� �������� ������ "Next"
      upravlenie &= ~(1 << 6); // �� �������� ������ "End" ��������� ������ � ����������� � ������� � ������ ��������� ����
      ProgrammState = 4;
      this->Cprw->NomIstoch++; //
    }
    else
    {
      upravlenie &= ~(1 << 0); // �� �������� ��� ����� ���� "����� ���������"
      upravlenie &= ~(1 << 1); // �� �������� ��� ����� ���� "��� ���������"
      upravlenie |= (1 << 2); // �������� ��� ����� ���� "����� ��"
      upravlenie |= (1 << 3); // �������� ��� ����� ���� "����� COM-�����"
      upravlenie &= ~(1 << 4); // ���������� ������
      upravlenie |= (1 << 5); // �������� ������ "Next"
      upravlenie |= (1 << 6); // �������� ������ "End" ��������� ������ � ����������� � ������� � ������ ��������� ����
      this->Cprw->RSDisConnect();
      sprintf(this->String[0],
	  "������ ��� ������� ������� COM-���� "
      );
      ProgrammState = 0;
    }
    return upravlenie;
  }
  if ( ProgrammState == 4 )
  {
    if ( bFlagPotoka == true )
    {
      this->Cprw->Resume(); // ������ 200 ��. ������ ������
    }
    else
    {
      this->Cprw->OprosBD_Arr(); // ������ 200 ��. ������ ������
    }
    if ( this->Cprw->t == this->intervZad ) // ���� ����� ���� ����������
    { // � �-��� Reset ���������� ��������� t, ������� t ������ �� ������ ComPortReadWrite_t
      upravlenie |= (1 << 0); // �������� ��� ����� ���� "����� ���������"
      upravlenie |= (1 << 1); // �������� ��� ����� ���� "��� ���������"
      //upravlenie |= (1 << 2); // �������� ��� ����� ���� "����� ��"
      upravlenie |= (1 << 3); // �������� ��� ����� ���� "����� COM-�����"
      upravlenie &= ~(1 << 4); // ���������� ������
      upravlenie |= (1 << 5); // �������� ������ "Next"
      upravlenie |= (1 << 6); // �������� ������ "End" ��������� ������ � ����������� � ������� � ������ ��������� ����

      this->Cprw->RSDisConnect();
      ProgrammState = 5;
    }
  }
///////////////////////////////////////////////
  if (ProgrammState == 6) // ���� �������� ����� ���� (��� ���������)
  {
    char id[10];
    sprintf(id, "COM%d", ComPortNum);
    for (int i = 0; i < 10; i++)
    {
      this->Cprw->DEVID[i] = (wchar_t)id[i];
    }
    if ( /*this->Cprw->RSConnect(this->Cprw->DEVID) == 0*/true ) // ���� ��� ������ �������� ���-�����
    {
      upravlenie &= ~(1 << 0); // �� �������� ��� ����� ���� "����� ���������"
      upravlenie &= ~(1 << 1); // �� �������� ��� ����� ���� "��� ���������"
      upravlenie &= ~(1 << 2); // �� �������� ��� ����� ���� "����� ��"
      upravlenie &= ~(1 << 3); // �� �������� ��� ����� ���� "����� COM-�����"
      upravlenie |= (1 << 4); // �������� ������
      upravlenie &= ~(1 << 5); // �� �������� ������ "Next"
      ProgrammState = 7;
    }
    else
    {
      upravlenie &= ~(1 << 0); // �� �������� ��� ����� ���� "����� ���������"
      upravlenie &= ~(1 << 1); // �� �������� ��� ����� ���� "��� ���������"
      upravlenie |= (1 << 2); // �������� ��� ����� ���� "����� ��"
      upravlenie |= (1 << 3); // �������� ��� ����� ���� "����� COM-�����"
      upravlenie &= ~(1 << 4); // ���������� ������
      upravlenie |= (1 << 5); // �������� ������ "Next"
      this->Cprw->RSDisConnect();
      sprintf(this->String[0],
          "������ ��� ������� ������� COM-���� "
      );
      upravlenie |= (1 << 7); // �������� ������ ������ ��
      ProgrammState = 0;
    }
    return upravlenie;
  }
	//{ // � �-��� Reset ���������� ��������� t, ������� t ������ �� ������ ComPortReadWrite_t
  upravlenie &= ~(1 << 0); // �� �������� ��� ����� ���� "����� ���������"
  upravlenie &= ~(1 << 1); // �� �������� ��� ����� ���� "��� ���������"
  //upravlenie |= (1 << 2); // �������� ��� ����� ���� "����� ��"
  upravlenie |= (1 << 3); // �������� ��� ����� ���� "����� COM-�����"
  upravlenie &= ~(1 << 4); // ���������� ������
  upravlenie |= (1 << 5); // �������� ������ "Next"
  upravlenie &= ~(1 << 6); // �� �������� ������ "End" ��������� ������ � ����������� � ������� � ������ ��������� ����
  upravlenie |= (1 << 7); // �������� ������ ������ ��
  //this->Cprw->RSDisConnect();
  ProgrammState = 8;

  DecodeDate(Date(), Year, Month, Day);
  sprintf(forReport, "���� ����������:%.02d.%.02d.%.04d", Day, Month, Year);
  Form_Report->Memo_Log->Lines->Add(forReport);
  sprintf(forReport, "�������� ���������������� �� (����� ��������� %d�)", (this->intervZad/1000));
  Form_Report->Memo_Log->Lines->Add(forReport);

  DecodeTime(Time(), Hour, Min, Sec, MSec);
  sprintf(forReport, "����� ����������:%.02d.%.02d.%.02d", Hour, Min, Sec);
  Form_Report->Memo_Log->Lines->Add(forReport);

  if (this->Cprw->Data.AllSerialNum == true) // = true, ���� ��� �������� ������ ��������
  {
    sprintf(forReport, "��� ����� ��� ���������� �����: %s", this->Cprw->Str_FileNameSerialNum, "");
    Form_Report->Memo_Log->Lines->Add(forReport);
  }
  else
  {
    sprintf(forReport, "��� ����� ��� ���������� ����� ���������� �������������: �������� ������ �� ���������");
    Form_Report->Memo_Log->Lines->Add(forReport);
  }

  length = sprintf(forReport, "� �������� �����������:");
  int length2 = length;
  for ( int i = 0; i < 8; i++ )
  {
    if (this->bAddrBDArr[i] == true)
    {
      if ( length2 == length )
      {
        length2 += sprintf( &forReport[length2], "BD%d", AddrBDArr[i] );
      }
      else
      {
        length2 += sprintf( &forReport[length2], ", BD%d", AddrBDArr[i] );
      }
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  // ===
  Form_Report->Memo_Log->Lines->Add("   ���� ��������� �� ����� ��������� ����");
  length = sprintf(forReport, "   Nf1:   ");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      length += sprintf(&forReport[length], "%d    ", this->Cprw->DataI.SumSchet[i]);
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  // ===
  Form_Report->Memo_Log->Lines->Add("   ��������� �������� ����� ���� (���/�)");
  length = sprintf(forReport, "   nf1:  ");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      length += sprintf(&forReport[length], "%.2f   ", this->Cprw->DataI.SredSchet[i]);
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  // ===
  Form_Report->Memo_Log->Lines->Add("   ���-�� ��������� ���� �� ����������� � �������.����");
  length = sprintf(forReport, "     :    ");
  for (int i = 0; i < 8; i++)
  {
    if (this->bAddrBDArr[i] == true)
    {
      length += sprintf(&forReport[length], "%d      ", this->Arr_Naf[i]);
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  // ===
  Form_Report->Memo_Log->Lines->Add("   ��������� �������� ����� ���� �� ����������� (���/�)");
  length = sprintf(forReport, "     :    ");
  for (int i = 0; i < 8; i++)
  {
    if (this->bAddrBDArr[i] == true)
    {
      length += sprintf(&forReport[length], "%d      ", this->Arr_Naf[i]/(this->intervZad/1000));
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  // ===
  Form_Report->Memo_Log->Lines->Add("---------------------------------------------------------------------------------------");

  sprintf(forReport, " �������� �:%d", this->Cprw->NomIstoch);
  Form_Report->Memo_Log->Lines->Add(forReport);
  sprintf(forReport, "   ����� ���������,�(���������):%s", this->massaIstochnika);
  Form_Report->Memo_Log->Lines->Add(forReport);
  sprintf(forReport, "   ��� ���������:%s", this->tipIctochnika);
  Form_Report->Memo_Log->Lines->Add(forReport);
  //===
  Form_Report->Memo_Log->Lines->Add("   \"���� �� ���������\" Ns( ��� )");
  length = sprintf(forReport, "     :  ");
  for (int i = 0; i < 8; i++)
  {
    if (this->bAddrBDArr[i] == true)
    {
      length += sprintf(&forReport[length],
          "%d   ",
	  this->Cprw->Data.SumSchet[i]
      );
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  //===
  Form_Report->Memo_Log->Lines->Add("   \"C������� ����� �� ���������\" ns( ���/�)");
  length = sprintf(forReport, "     :  ");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      length += sprintf(&forReport[length],
	  "%.02f   ",
	  this->Cprw->Data.SredSchet[i]
      );
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  // ===
  Form_Report->Memo_Log->Lines->Add("   \"���� �� ��������� �� �����������\"  Ns ( ��� )");
  length = sprintf(forReport, "     :    ");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      length += sprintf(&forReport[length], "%d      ", this->Arr_Nai[i]);
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  // ===
  Form_Report->Memo_Log->Lines->Add("   \"C������� ����� �� ��������� �� �����������\" ns( ���/� )");
  length = sprintf(forReport, "     :    ");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      length += sprintf(&forReport[length], "%d      ", this->Arr_Nai[i]/(this->intervZad/1000));
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  //===
  Form_Report->Memo_Log->Lines->Add("   \"������ �������� �����\" ns-nf( ���/�)");
  length = sprintf(forReport, "     :  ");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      length += sprintf(&forReport[length],
         "%.02f   ",
	 ( this->Cprw->Data.SredSchet[i] - this->Cprw->DataI.SredSchet[i] )
      );
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  // ===
  Form_Report->Memo_Log->Lines->Add("   �������� ������ �� �����");
  length = sprintf(forReport, "     :    ");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      length += sprintf(&forReport[length], "%d      ", this->Arr_Tceziya[i]);
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  // ===
  Form_Report->Memo_Log->Lines->Add("   �������� ������ �� ����������");
  length = sprintf(forReport, "     :    ");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      length += sprintf(&forReport[length], "%d      ", this->Arr_Svetodiod[i]);
    }
  }
  Form_Report->Memo_Log->Lines->Add( forReport );
  // ===
  Form_Report->Memo_Log->Lines->Add("   ����������� ������� �������������,%  ");
  length = sprintf(forReport, "   � :    ");
  int modul;
  double rezult;
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      modul = this->Cprw->DataI.SumSchet[i] - this->Arr_Naf[i];
      if ( modul < 0 )
      {
	modul = modul * -1;
      }
      rezult = (double)modul * 100.0 / this->Cprw->DataI.SumSchet[i];
      length += sprintf(&forReport[length], "%.01f      ", rezult);
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  // ===
  length = sprintf(forReport, "   � :    ");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      modul = this->Cprw->Data.SumSchet[i] - this->Arr_Nai[i];
      if ( modul < 0 )
      {
	modul = modul * -1;
      }
      rezult = (double)modul * 100.0 / this->Cprw->Data.SumSchet[i];
      length += sprintf(&forReport[length], "%.01f      ", rezult);
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  //===
  Form_Report->Memo_Log->Lines->Add("   ���������������� (���/(�*�) ��� (���/(�*���)) )");
  if ( m != 0 )
  {
    length = sprintf(forReport, "   S :");
    for ( int i = 0; i < 8; i++ )
    {
      if ( this->bAddrBDArr[i] == true )
      {
	length += sprintf(&forReport[length],
	    "%.1f   ",
	    ( ( this->Cprw->Data.SredSchet[i] - this->Cprw->DataI.SredSchet[i]) / m )
        );
      }
    }
  }
  else
  {
    Form_Report->Memo_Log->Lines->Add("   S :");
    sprintf(forReport, "      ������: m == 0   ");
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  Form_Report->Memo_Log->Lines->Add("   ����������� ���������������� (���)");
  length = sprintf(forReport, "     :");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      if ( (this->Cprw->Data.SredSchet[i] - this->Cprw->DataI.SredSchet[i]) != 0 )
      {
	length += sprintf(&forReport[length],
	    "%.3f   ",
	    ( sqrt( (this->Cprw->Data.SredSchet[i] + this->Cprw->DataI.SredSchet[i]) * (this->intervZad/1000) ) /
	    ( (this->Cprw->Data.SredSchet[i] - this->Cprw->DataI.SredSchet[i]) * (this->intervZad/1000) ) )
        );
      }
      else
      {
	length += sprintf(&forReport[length], "������: ������� �� ����    ");
      }
    }
  }
  Form_Report->Memo_Log->Lines->Add( forReport );
  //===
  Form_Report->Memo_Log->Lines->Add("   ���������� ������ �����:"); // N3
  length = sprintf(forReport, "     :    ");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      length += sprintf(&forReport[length], "%d      ", this->Cprw->N3[i]);
    }
  }
  Form_Report->Memo_Log->Lines->Add( forReport );
  // ===
  Form_Report->Memo_Log->Lines->Add("   ���������� ��������� ��������� �����:"); // N1
  length = sprintf(forReport, "     :    ");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      length += sprintf(&forReport[length], "%d      ", this->Cprw->N1[i]);
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  Form_Report->Memo_Log->Lines->Add("   ���������� ����������� ����������:"); // N2
  length = sprintf(forReport, "     :    ");
  for ( int i = 0; i < 8; i++ )
  {
    if ( this->bAddrBDArr[i] == true )
    {
      length += sprintf(&forReport[length], "%d      ", this->Cprw->N2[i]);
    }
  }
  Form_Report->Memo_Log->Lines->Add(forReport);
  Form_Report->Memo_Log->Lines->Add("---------------------------------------------------------------------------------------");
  }
  return upravlenie;
  }
  return upravlenie;
}
//---------------------------------------------------------------------------
Function_t::Function_t( void ) // �����������
{
  bFlagPotoka = /*true*/ false; // true - ������������ �����, false - �� ������������ �����
  Cprw = new ComPortReadWrite_t(true, bFlagPotoka); // true - �� ��������� ����� ��� ��������� ������
  Cprw->FreeOnTerminate = true; // false - �� ������������ ����� ����������
  ProgrammState = -1; // ������� ��������� ��������� (-1 - ��� ������)
  this->upravlenie = 0x0F;

  DIAcopy(" �������� ����� COM-����� � ���������� �� ", 1);
  DIAcopy("", 2);
  DIAcopy("", 3);
  DIAcopy("", 4);
  DIAcopy("", 5);
  DIAcopy("", 6);
  DIAcopy("", 7);
  DIAcopy("", 8);
}
//---------------------------------------------------------------------------
void Function_t::GetParam(char * s, double var)
{
  if ( DIAcpy("t", s) == 0 )
  {
    /*t = var*/;
  }
  else if ( DIAcpy("Ns", s) == 0 )
  {
    Ns = var;
  }
  else if ( DIAcpy("Nf", s) == 0 )
  {
    Nf = var;
  }
  else if ( DIAcpy("Nf1", s) == 0 )
  {
    Nf1 = var;
  }
  else if ( DIAcpy("Nf2", s) == 0 )
  {
    Nf2 = var;
  }
  else if ( DIAcpy("m", s) == 0 )
  {
    m = var;
  }
  else if ( DIAcpy("S", s) == 0 )
  {
    S = var;
  }
}
//---------------------------------------------------------------------------
int Function_t::DIAcpy(char * var1, char * var2)
{
  int i;
  for (i = 0; (i < razmer) && (var2[i] != 0) ; i++)
  {
    if ( var1[i] != var2[i] )
    {
      return -1; // ������ �� �����
    }
  }
  return 0;
}
//---------------------------------------------------------------------------
int Function_t::Stop(void)
{
  for ( int i = 0; i < 8; i++ )
  {
    sprintf(this->String[i], "");
  }
  sprintf(this->arr, "");

  ProgrammState = 0;
  upravlenie &= ~(1 << 0); // �� �������� ��� ����� ���� "����� ���������"
  upravlenie &= ~(1 << 1); // �� �������� ��� ����� ���� "��� ���������"
  upravlenie |= (1 << 3); // �������� ��� ����� ���� "����� COM-�����"
  upravlenie &= ~(1 << 4); // ���������� ������
  upravlenie |= (1 << 5); // �������� ������ "Next"
  upravlenie |= (1 << 7); // �������� ������ ������ ��
  this->Cprw->RSDisConnect();	// ������� COM-����
  this->Cprw->Reset();

  return upravlenie;
}
//---------------------------------------------------------------------------
int Function_t::EndIstochnik(void)
{
  for ( int i = 0; i < 8; i++ )
  {
    sprintf(this->String[i], "\0\0\0\0\0\0\0\0\0\0\0\0\0");
  }
  upravlenie |= (1 << 4); // ��������� ������
  upravlenie &= ~(1 << 6); // �� �������� ������ "End" ��������� ������ � ����������� � ������� � ������ ��������� ����
  ProgrammState = 6; // ������� � ��������������� ����� - ����� ��������� ����
  return upravlenie;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

