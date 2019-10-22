//---------------------------------------------------------------------------
#ifndef TaskWithParamH
#define TaskWithParamH
//---------------------------------------------------------------------------
#include "ActionEvent.h"
using namespace smarteventsMin;
//---------------------------------------------------------------------------
#include "ITask.h"
#include "ArgTaskWithParam.h"
//---------------------------------------------------------------------------
class TaskWithParam
{
public:
    TaskWithParam( ITask * task );
    void RunAsynk( ActionSelf<>* action );
    void BeginInvoke( ActionSelf<>* action );

    template<class T1>
    void BeginInvoke( ActionSelf<T1>* action, T1 arg1 )
    {
        IArgTaskWithParam * args =
            new ArgTaskWithParam<T1>( action, arg1 );
        _withoutParam->BeginInvoke( args->StartSelf() );
    }

private:
    ITask * _withoutParam;
    IArgTaskWithParam * _args;
};
//---------------------------------------------------------------------------
#endif
