//---------------------------------------------------------------------------
// ������ � ���� - ���� ������� �������
//---------------------------------------------------------------------------

#ifndef Unit_FileDirectH
#define Unit_FileDirectH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
class FileDirect
{
  private:

  public:
  FileDirect();//�����������
//---------------------------------------------------------------------------
  int ReadCount(const AnsiString FileName); // ���������� ����� � ������������� ������ �����
  int ReadStr(const AnsiString FileName, AnsiString * MasStr); // ������ �� ����� ����� ������ �����
//---------------------------------------------------------------------------
  AnsiString ReadString(const AnsiString FileName, // ������ �� ����� �������� �� Name (Name = ��������) - ���������� ��������
      AnsiString Name ,
      AnsiString Default
      );
//---------------------------------------------------------------------------
  void WriteString(const AnsiString FileName, // ������ � ���� �������� �� Name (Name = ��������)
      AnsiString Name,
      AnsiString Value
      );
//---------------------------------------------------------------------------
  bool ReadBool(const AnsiString FileName,
      AnsiString Name,
      bool Default
      );
//---------------------------------------------------------------------------
  void WriteBool(const AnsiString FileName,
      AnsiString Name,
      bool boolValue
      );
//---------------------------------------------------------------------------
  int ReadInteger(const AnsiString FileName,
      AnsiString Name,
      int Default
      );
//---------------------------------------------------------------------------
  void WriteInteger(const AnsiString FileName,
      AnsiString Name,
      int Value
      );
//---------------------------------------------------------------------------
  unsigned long ReadUnsignedLong(const AnsiString FileName,
      AnsiString Name,
      unsigned long Default
      );
//---------------------------------------------------------------------------
  void WriteUnsignedLong(const AnsiString FileName,
      AnsiString Name,
      unsigned long Value
      );
//---------------------------------------------------------------------------
  float ReadFloat(const AnsiString FileName,
      AnsiString Name,
      float Default
      );
//---------------------------------------------------------------------------
  void WriteFloat(const AnsiString FileName,
      AnsiString Name,
      float Value
      );
//---------------------------------------------------------------------------
  void ClearFile(const AnsiString FileName); // �������� ����  - ������� ��� ������
  void ClearString(const AnsiString FileName, AnsiString Name); // ������ ������
//---------------------------------------------------------------------------
  ~FileDirect(); // ����������
//---------------------------------------------------------------------------
};

#endif
