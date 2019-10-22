//---------------------------------------------------------------------------
#ifndef TaskH
#define TaskH
//---------------------------------------------------------------------------
#include "ITask.h"
#include "SuperThread.h"
//---------------------------------------------------------------------------
class Task : public ITask
{
public:
    Task();
    ~Task();
    void RunAsynk(ActionSelf<>* action);
    void BeginInvoke(ActionSelf<>* action);
private:
    SuperThread * _thread;
};
//---------------------------------------------------------------------------
#endif
