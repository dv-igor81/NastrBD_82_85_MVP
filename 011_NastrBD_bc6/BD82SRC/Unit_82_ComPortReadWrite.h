//---------------------------------------------------------------------------

#ifndef Unit_82_ComPortReadWriteH
#define Unit_82_ComPortReadWriteH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//#include "Unit_82_RSProtokol.h"
#include "RSProtokol.h"
//---------------------------------------------------------------------------
class ComPortReadWrite_t : public TThread
{
private:
  void __fastcall Printing();
  // ===
  void __fastcall PrintingNoConnect();
  void __fastcall PrintingNot();
  void __fastcall PrintingYes();
  void __fastcall PrintingEnd();
  bool bflag_tek_err; // флаг текущего состояния опроса - (ложь - нет ошибкок связи)
  bool bflag_pred_err; // флаг предыдущего состояния опроса - (ложь - нет ошибкок связи)

  void swap(int & varTo, int & varFrom);
  void FindBdByNom(int nom);
protected:
  void __fastcall Execute();
public:
  __fastcall ComPortReadWrite_t(bool CreateSuspended);
  //void __fastcall SetTcpFlag( bool );
  //bool __fastcall GetTcpFlag( void );
  RSProtokol_t * Prot;
  int flagSostoyaniya;
  // ===
  int varFrom;
  int varTo;
  char CArr[200];
  int N;
  int AddrBD;
};
//---------------------------------------------------------------------------
#endif
