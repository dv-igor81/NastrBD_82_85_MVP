//---------------------------------------------------------------------------
#ifndef IWindowMainBd85H
#define IWindowMainBd85H
//---------------------------------------------------------------------------
#include "ActionEvent.h"
using namespace smartevents;
//---------------------------------------------------------------------------
#include "HelperConnectFourBdProt.h"
#include "StartDataNewBd85.h"
#include "IterDataNewBd85.h"
#include "ScalingDataNewBd85.h"
//---------------------------------------------------------------------------
class IWindowMainBd85
{
public:
    virtual void Destroy() = 0;
    virtual ActionSelf<>* GetSelfShow() = 0;
    virtual ActionEvent<>* GetEventFormShow() = 0;
    virtual ActionEvent<>* GetEventFormClose() = 0;
    virtual ActionSelf<StartDataNewBd85*>* GetSelfDisplayStartData() = 0;
    virtual ActionSelf<IterDataNewBd85*>& GetSelfDisplayIterData() = 0;
    virtual ActionSelf<const char*>* GetSelfDisplayErrors() = 0;
    virtual HelperConnectFourBdProt* GetConnectFourBdProt() = 0;
    virtual ActionEvent<const char*>* GetEventButtonStartStopScalingClick() = 0;
};
//---------------------------------------------------------------------------
#endif
