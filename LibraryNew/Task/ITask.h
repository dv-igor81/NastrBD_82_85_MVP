//---------------------------------------------------------------------------
#ifndef ITaskH
#define ITaskH
//---------------------------------------------------------------------------
#include "ActionEvent.h"
using namespace smarteventsMin;
//---------------------------------------------------------------------------
class ITask
{
public:
    virtual ~ITask(){};

    virtual void RunAsynk(ActionSelf<>* action) = 0;
    //virtual void RunAsynk(ActionSelf<>& action) = 0; // new
    //virtual void RunAsynk(ActionEvent<>* action) = 0; // new
    //virtual void RunAsynk(ActionEvent<>& action) = 0; // new

    virtual void BeginInvoke(ActionSelf<>* action) = 0;
    //virtual void BeginInvoke(ActionSelf<>& action) = 0; // new
    //virtual void BeginInvoke(ActionEvent<>* action) = 0; // new
    //virtual void BeginInvoke(ActionEvent<>& action) = 0; // new
};
//---------------------------------------------------------------------------
#endif
