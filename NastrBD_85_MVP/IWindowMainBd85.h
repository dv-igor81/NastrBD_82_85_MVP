//---------------------------------------------------------------------------
#ifndef IWindowMainBd85H
#define IWindowMainBd85H
//---------------------------------------------------------------------------
#include "ActionEvent.h"
using namespace smartevents;
//---------------------------------------------------------------------------
#include "HelperConnectFourBdProt.h"
#include "StartDataNewBd85.h"
//---------------------------------------------------------------------------
class IWindowMainBd85
{
public:
    //virtual ~IWindowMainBd85(){};
    virtual void Destroy() = 0;
    virtual ActionSelf<>* GetSelfShow() = 0;
    virtual ActionEvent<>* GetEventFormShow() = 0;
    virtual ActionEvent<>* GetEventFormClose() = 0;

    virtual ActionSelf<StartDataNewBd85*>* GetSelfDisplayStartData() = 0;

    virtual HelperConnectFourBdProt* GetConnectFourBdProt() = 0;
};
//---------------------------------------------------------------------------
#endif
