//---------------------------------------------------------------------------
#ifndef Unit_SharedTypesH
#define Unit_SharedTypesH
//---------------------------------------------------------------------------
// ���� ������, ��������� �������
//---------------------------------------------------------------------------
#define __kei_length__ 8
#define __size_length__ 4
//---------------------------------------------------------------------------
void MyStrCopy(
    char * strTo,
    const char * strFrom,
    int maxLength
);
//---------------------------------------------------------------------------
void SetNull(
    char * strTo,
    int Count
);
//---------------------------------------------------------------------------
union TSsd {
  struct TInfo {
    long count; // ������� ��� ��������� ���� ��������
    long poVersiya;
    unsigned char flags[4];
    char fileName[256];
    union TSize {
      long Lint;
      char Char[4];
    } Size;
    char key[8]; // ����, ��� ������������� ����, ��� ���� ������� ��������� �����������
  } Info;
  unsigned char BtArr[sizeof(TInfo)];
};
//---------------------------------------------------------------------------
class TFileBuffer { // �������� �����
public:
  // �����������
  TFileBuffer(const char * key);
  // ����������
  ~TFileBuffer();
  // ��������� ���������� ����� � ����
  int ReadFileToSelf( char * fileName );
  // �������� ��� ���������� � ����
  void WriteFileFromSelf( char * fileName );
  // �������� ��� ���������� � ��� (����������� ��������� ������) � ����
  void WriteSelfSsd( char * fileName );


  // �������� �� ������
  void ErrorMess( char * text, int Level );


  // ��������� ���� ����������� ��������� ������ (���).
  bool CheckKey();
  // �������� �� ������� ��������� �������������
  bool Intermediate();
  
  char * GetInfofillName();

  // ��������� ������������� ����������� ��������� ������
  void StartSsdInit( char * fileName );

  // �������� ������� ������������� ��������: ��� �� ��
  void SsdNoPp();

  // �������� ������� ������������� ��������: ��� ��
  void SsdYesPp( char * fileName );

  // "����������������" ���, ���� ��������� �����, ���� �������� ��� ���������
  void SsdIncrement();

  int GetCount();

  long GetPoVersiya();
  void SetPoVersiya(long poVers);

  void SsdReset();  

  // ���� ���� ����������� ����� ������, �������� ��������� ������ ��
  // ����������� ��������� ������ � ����
  void CopyIsKeyFindRevers(
      int btArrLength );


private:
  // ���������� ���� ����������� ��������� ������ (���), � ��������� ������ ����������
  void SetKey();

  // ���� ���� ����������� ����� ������, �������� ��������� ������ ��
  // ����� � ����������� ��������� ������
  void CopyIsKeyFind(
    int btArrLength );

  const char * _key;
  unsigned char * _btArrPtr; // ��������� �� ������
  long _length; // ������ �������
  TSsd _ssd; // ����������� ��������� ������
  int _bfDebuf;
};
//---------------------------------------------------------------------------
#endif
