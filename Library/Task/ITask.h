//---------------------------------------------------------------------------
#ifndef ITaskH
#define ITaskH
//---------------------------------------------------------------------------
#include "ActionEvent.h"
using namespace smartevents;
//---------------------------------------------------------------------------
class ITask
{
public:
    virtual void RunAsynk(ActionSelf<>* action) = 0;
    virtual void BeginInvoke(ActionSelf<>* action) = 0;
};
//---------------------------------------------------------------------------
#endif
