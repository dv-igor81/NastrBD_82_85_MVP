//---------------------------------------------------------------------------
#ifndef Unit_SharedTypesH
#define Unit_SharedTypesH
//---------------------------------------------------------------------------
// Типы данных, доступные проекту
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
    long count; // Сколько раз программа была запущена
    long poVersiya;
    unsigned char flags[4];
    char fileName[256];
    union TSize {
      long Lint;
      char Char[4];
    } Size;
    char key[8]; // Ключ, для удостоверения того, что файл дописан служебной информацией
  } Info;
  unsigned char BtArr[sizeof(TInfo)];
};
//---------------------------------------------------------------------------
class TFileBuffer { // Файловый буфер
public:
  // Конструктор
  TFileBuffer(const char * key);
  // Деструктор
  ~TFileBuffer();
  // Прочитать содержимое файла в себя
  int ReadFileToSelf( char * fileName );
  // Записать своё содержимое в файл
  void WriteFileFromSelf( char * fileName );
  // Записать своё содержимое и ССД (специальную структуру данных) в файл
  void WriteSelfSsd( char * fileName );


  // Сообщить об ошибке
  void ErrorMess( char * text, int Level );


  // Проверить ключ специальной структуры данных (ССД).
  bool CheckKey();
  // Является ли текущая программа промежуточной
  bool Intermediate();
  
  char * GetInfofillName();

  // Начальная инициализация специальной структуры данных
  void StartSsdInit( char * fileName );

  // Изменить признак промежуточной програмы: это НЕ ПП
  void SsdNoPp();

  // Изменить признак промежуточной програмы: это ПП
  void SsdYesPp( char * fileName );

  // "Инкрементировать" ССД, либо выполнить сброс, либо оставить без изменения
  void SsdIncrement();

  int GetCount();

  long GetPoVersiya();
  void SetPoVersiya(long poVers);

  void SsdReset();  

  // Если ключ модификации файла найден, копируем служебные данные из
  // специальной структуры данных в файл
  void CopyIsKeyFindRevers(
      int btArrLength );


private:
  // Установить ключ специальной структуры данных (ССД), и некоторую другую информацию
  void SetKey();

  // Если ключ модификации файла найден, копируем служебные данные из
  // файла в специальную структуру данных
  void CopyIsKeyFind(
    int btArrLength );

  const char * _key;
  unsigned char * _btArrPtr; // Указатель на массив
  long _length; // Размер массива
  TSsd _ssd; // Специальная структура данных
  int _bfDebuf;
};
//---------------------------------------------------------------------------
#endif
