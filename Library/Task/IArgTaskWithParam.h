//---------------------------------------------------------------------------
#ifndef IArgTaskWithParamH
#define IArgTaskWithParamH
//---------------------------------------------------------------------------
#include "ActionEvent.h"
using namespace smartevents;
//---------------------------------------------------------------------------
class IArgTaskWithParam
{
public:
    // virtual ~IArgTaskWithParam() = 0; // ��� - ������ ��������
    virtual ~IArgTaskWithParam(){}
    virtual ActionSelf<>* StartSelf() = 0;
};


#endif
