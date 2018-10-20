//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "SuperThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall SuperThread::SuperThread(bool CreateSuspended)
        : TThread(CreateSuspended)
{
  work = false;
  change = true;
  flagNotSynchro = false;
  flagSynchro = false;
}
//---------------------------------------------------------------------------
void __fastcall SuperThread::Execute()
{
  while ( Terminated == false )
  {
    if (flagNotSynchro)
    {
      flagNotSynchro = false;
      start_not_synhro();
    }
    if (flagSynchro)
    {
      flagSynchro = false;
      Synchronize( & start_synhro );
    }
    Suspend(); // Приостановить поток
  }
}
//---------------------------------------------------------------------------
void __fastcall SuperThread::start_not_synhro()
{
    if ( as_startNotSynhro != 0 )
    {
        (*as_startNotSynhro)();
        as_startNotSynhro = 0;
    }
}
//---------------------------------------------------------------------------
void __fastcall SuperThread::start_synhro()
{
    if ( as_startSynhro != 0 )
    {
        (*as_startSynhro)();
        as_startSynhro = 0;
    }
}
//---------------------------------------------------------------------------
void SuperThread::GetEventStartNotSynhro(ActionSelf<>* action)
{
    as_startNotSynhro = action;
}
//---------------------------------------------------------------------------
void SuperThread::GetEventStartSynhro(ActionSelf<>* action)
{
    as_startSynhro = action;
}
//---------------------------------------------------------------------------
void SuperThread::SetFlagNotSynchro()
{
    flagNotSynchro = true;
}
//---------------------------------------------------------------------------
void SuperThread::SetFlagSynchro()
{
    flagSynchro = true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
