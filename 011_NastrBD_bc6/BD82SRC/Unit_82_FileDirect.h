//---------------------------------------------------------------------------
// Запись в файл - типа прямого доступа
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
  FileDirect();//конструктор
//---------------------------------------------------------------------------
  int ReadCount(const AnsiString FileName); // Количество строк в запрашиваемом списке строк
  int ReadStr(const AnsiString FileName, AnsiString * MasStr); // Чтение из файла всего списка строк
//---------------------------------------------------------------------------
  AnsiString ReadString(const AnsiString FileName, // Чтение из файла значения по Name (Name = Значение) - возвращает значение
      AnsiString Name ,
      AnsiString Default
      );
//---------------------------------------------------------------------------
  void WriteString(const AnsiString FileName, // Запись в файл значения по Name (Name = Значение)
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
  void ClearFile(const AnsiString FileName); // Почистим файл  - сделаем его пустым
  void ClearString(const AnsiString FileName, AnsiString Name); // удалим строку
//---------------------------------------------------------------------------
  ~FileDirect(); // деструктор
//---------------------------------------------------------------------------
};

#endif
