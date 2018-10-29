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
  // Конструктор
  TWriteSelf();
  // Деструктор
  ~TWriteSelf();
  // Кто я: 1 - НП, 2 - ПП, 3 - ОП, 4 - ключ не найден (первый запуск)
  // НП - Начальная программа, запускается пользователем, создаёт и запускает Промежуточную программу
  // ПП - Промежуточная программа, запускается Начальной программой, создаёт и запускает Окончательную программу
  // ОП - Окончательная программа, запускается Промежуточной программой, ничего не создаёт и не запускает
  int WhoAmI();

  int TWriteSelf::WhoAmFile(
    AnsiString fileNameLocal,
    TFileBuffer & fileBufLocal);

  void MyWriteFile();
  void UpdatedWriteFile();   
  void MyWriteFile(TFileBuffer & fileBufLocal);// Записать файл
  void MyWinExec(); // Запустить файл
  void SetReady(); // Установить флаг готовности (для сброса счётчика)
  bool Reset(); // Дать команду на сброс счётчика
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
  // Старт программы
  int StartProgramm();    
private:
  void Mess( char * text, int Level );


  AnsiString fileName;  // Имя файла текущей программы
  AnsiString InfofillName; // Имя файла окончательной программы

  TFileBuffer _fileBufSelf; // Файловый буфер
  TFileBuffer _fileBufUpdate; // Файловый буфер

  char msfFormated[256];


  int _flagDeystviya; //
  int _bfDebuf;
  bool _bfReady;
};
//---------------------------------------------------------------------------
#endif
