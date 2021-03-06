//---------------------------------------------------------------------------
#pragma hdrstop
#include "Task.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
Task::Task()
{
    _thread = new SuperThread(true); // true - ?? ????????? ????? ??? ????????? ??????
    _thread->FreeOnTerminate = false; // false - ?? ???????????? ????? ??????????
}
//---------------------------------------------------------------------------
Task::~Task()
{
    delete _thread;
}
//---------------------------------------------------------------------------
void Task::RunAsynk(ActionSelf<>* action)
{
    _thread->StartNotSynhro( action );
    _thread->Resume();
}
//---------------------------------------------------------------------------
void Task::BeginInvoke(ActionSelf<>* action)
{
    _thread->StartSynhro( action );
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
