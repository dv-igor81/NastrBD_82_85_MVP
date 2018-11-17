//---------------------------------------------------------------------------
#ifndef ArgTaskWithParamH
#define ArgTaskWithParamH
//---------------------------------------------------------------------------
#include "IArgTaskWithParam.h"
//---------------------------------------------------------------------------
template<class T1>
class ArgTaskWithParam : public IArgTaskWithParam
{
public:
    ArgTaskWithParam(ActionSelf<T1>* action, T1 arg1)
        :    as_StartAction( this, &ArgTaskWithParam::StartAction )
    {
        _action = action;
        _arg1 = arg1;
    }
    ActionSelf<>* StartSelf()
    {
        return & as_StartAction;
    }
private:
    ActionSelf<T1>* _action;
    T1 _arg1;
    ActionSelf<> as_StartAction;
    void StartAction()
    {
        (*_action)(_arg1);
        delete this;
    }
};
//---------------------------------------------------------------------------
// "суфикс" A2 - 2 параметра
#endif
