//---------------------------------------------------------------------------
#ifndef IWindowMainBd85H
#define IWindowMainBd85H
//---------------------------------------------------------------------------
#include "ActionEvent.h"
using namespace smartevents;
//---------------------------------------------------------------------------
#include "HelperConnectFourBdProt.h"
//---------------------------------------------------------------------------
class IWindowMainBd85
{
public:
    virtual ActionSelf<>* GetSelfShow() = 0;
    virtual ActionEvent<>* GetEventFormShow() = 0;
    virtual ActionEvent<>* GetEventFormClose() = 0;

    virtual HelperConnectFourBdProt* GetConnectFourBdProt() = 0;
};
//---------------------------------------------------------------------------
#endif
