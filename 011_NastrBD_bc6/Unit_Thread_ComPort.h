//---------------------------------------------------------------------------

#ifndef Unit_Thread_ComPortH
#define Unit_Thread_ComPortH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "DiaTypes.h"
#include "Unit_Funktion.h"
#include "Unit_DataBD.h"
//---------------------------------------------------------------------------
class ComPortReadWrite_t : public TThread
{            
private:
  // Данные
  enum { Size_BD = 16, Size_ComPorts = 32 };


  RSProtokol_t * Prot;

  // Функции
  void __fastcall Printing();
  void Display (String Str);
  void SkanComPort();
  void ClearText();
  void SkanBD9Bit();
  int GetNextCom();
  int ReadBD9Bit();
protected:
  void __fastcall Execute();
public:
  int Length_BD;
  bool MasBD_ModBus[Size_BD];
  bool MasBD_9bit[Size_BD];
  DataBD9Bit_t Data9Bit[Size_BD];  

  ZD_t flagZadachi; // флаг задачи
  bool flagEnableResume; // флаг доступности Resume
  String ComPortName;

  int Count;
  bool KomPorts[Size_ComPorts];
  int Ptr_ComPort;
  String StrDisplay;
  bool ByloSkanirovanie; // false - не было сканирования доступных КОМ-портов 

  void __fastcall SetString(String Str);
  __fastcall ComPortReadWrite_t(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
