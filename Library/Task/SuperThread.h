//---------------------------------------------------------------------------
#ifndef SuperThreadH
#define SuperThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include "ActionEvent.h"
using namespace smartevents;
//---------------------------------------------------------------------------
class SuperThread : public TThread
{
private:
  void SetName();
  void __fastcall start_not_synhro();
  void __fastcall start_synhro();
  bool work;
  bool change;

  bool flagNotSynchro;
  bool flagSynchro;

  ActionSelf<>* as_startNotSynhro;
  ActionSelf<>* as_startSynhro;
protected:
  void __fastcall Execute();
public:
  __fastcall SuperThread(bool CreateSuspended);
  void GetEventStartNotSynhro(ActionSelf<>* action);
  void GetEventStartSynhro(ActionSelf<>* action);
  void SetFlagNotSynchro();
  void SetFlagSynchro();
};
//---------------------------------------------------------------------------
#endif
