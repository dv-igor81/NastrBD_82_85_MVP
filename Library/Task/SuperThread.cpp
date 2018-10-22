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
}
//---------------------------------------------------------------------------
void __fastcall SuperThread::Execute()
{
    while ( Terminated == false )
    {
        start_not_synhro();
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
void SuperThread::StartNotSynhro(ActionSelf<>* action)
{
    as_startNotSynhro = action;
}
//---------------------------------------------------------------------------
void SuperThread::StartSynhro(ActionSelf<>* action)
{
    as_startSynhro = action;
    Synchronize( & start_synhro );
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
