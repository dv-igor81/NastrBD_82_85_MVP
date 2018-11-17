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

  ActionSelf<>* as_startNotSynhro;
  ActionSelf<>* as_startSynhro;
protected:
  void __fastcall Execute();
public:
  __fastcall SuperThread(bool CreateSuspended);
  void StartNotSynhro(ActionSelf<>* action);
  void StartSynhro(ActionSelf<>* action);

  //template<class P> void StartNotSynhroParam(ActionSelf<P>* action, P arg);
};
//---------------------------------------------------------------------------
#endif
