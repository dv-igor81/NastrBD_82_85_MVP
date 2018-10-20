//---------------------------------------------------------------------------
#ifndef TaskH
#define TaskH
//---------------------------------------------------------------------------
#include "ITask.h"
//---------------------------------------------------------------------------
class Task : public ITask
{
public:
    void RunAsynk(ActionSelf<>* action);
    void BeginInvoke(ActionSelf<>* action);
private:
    //ActionEvent<> _event;
};
//---------------------------------------------------------------------------
#endif
