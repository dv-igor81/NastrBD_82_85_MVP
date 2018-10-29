//---------------------------------------------------------------------------
#ifndef BDInterfaceH
#define BDInterfaceH
//---------------------------------------------------------------------------
int OpenRS(int n); // ���������� ���������� � ��
int CloseRS();     // ������� ����
int SetIndAdr(unsigned char Adr);      // ���������� �������������� ����� ��
int GetIndAdr(unsigned char *Adr);     // ������� �������������� ����� ��
int SetGrpAdr(unsigned char Adr);      // ���������� ��������� ����� ��
int GetGrpAdr(unsigned char *Adr);     // ������� ��������� ����� ��
int GetTemp(unsigned int *Temp);       // ������� ������� ����������� ���������� ��
int GetUhi(unsigned int *Temp);        // ������� �������� �������� ����������
int SetUhi(unsigned int Temp);        // ���������� �������� �������� ����������
int ARCHCon(unsigned char State);      // ���������� �������� ��� 1-��������, 0-���������
int SpectrCon(unsigned char State);    // ���������� ������� ������� �������� 1-��������, 0-���������
int GetLEDAmp(unsigned int *Ampl);      // �������� ��������� �������� �� ����������
int SetLEDAmp(unsigned int Ampl);       // ������ ��������� �������� ����������
int IncFreqLEDImp(unsigned char State); // ���������� ������� ��������� �� ����������
int GetCountImp(unsigned int *CImp);   // �������� ���� �� 0,2 ���
int GetSpectr(unsigned int *Spectr);   // �������� ������ ��������
int GetPSWBD(unsigned char *PSWBD);    // �������� ����� ��������� ��������� ��
int WriteFlash(unsigned int Adr,unsigned long Data);  // ������ ����� ������ � FLASH/EE DATA MEMORY ����������
int ReadFlash(unsigned int Adr, unsigned long *Data); // ���������� ����� ������ �� FLASH/EE DATA MEMORY ����������
int WriteRAM(unsigned char Adr, unsigned char Data);  // ������ ����� ������ �� ���������� ������ ������ ����������
                                                      // (256 ����) ����������
int ReadRAM(unsigned char Adr,unsigned char *Data);        // ������ ����� ������ �� ���������� ������ ������ ���������� (256 ����) ����������
int GetDNU(unsigned int *DNU);         // �������� ���������� �� ������ �������������� ������� ������
int GetDVU(unsigned int *DVU);         // �������� ���������� �� ������ �������������� �������� ������
int SetDNU(unsigned int DNU);          // ���������� ����� ������������� ������� ������
int SetDVU(unsigned int DVU);          // ���������� ����� ������������� �������� ������
int GetSSP(unsigned char *SSP);        // �������� ����� ��������� ��������� ��
int SetTimeInterval(unsigned char TimeInt); // ���������� ����� ����� �� ��� TimeInt=255(���������� � �� �� ���������)
                                            // �� �� ������������ ����������� ��������� ��������� ����� (������ �� UART)
                                            // ��� TimeInt �������� �� 255 �� �������� �������������� ������������
                                            // ��������� ����� (����� ��������� ��� TimeInt*25=��� ����)
int GetSIM3(unsigned int *SIM3);//��������� �������� ������� ���
int GetVersia(unsigned char *Versia);
int SetARH(unsigned char KodRS);//1-�������� ����� ��������    0-���
int GetARH(unsigned char *KodRS);

int GetSIM4(unsigned int *SIM4);//��������� ������������ ���
int GetTimeInterval(unsigned char *TimeInt);

int SetSIM3(unsigned int PWMzn);
int SetSIM4(unsigned int PWMzn);
#endif
