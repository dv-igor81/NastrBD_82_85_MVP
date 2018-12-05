//---------------------------------------------------------------------------
#ifndef IWindowLoaderH
#define IWindowLoaderH
//---------------------------------------------------------------------------
#include "IPresenterWindowMainBd85.h"
#include "ConnectBdProt.h"
//---------------------------------------------------------------------------
class IWindowLoader
{
public:
    virtual void LoadWindowBd85SaveParam(
        IPresenterWindowMainBd85 * mainPres,
        ConnectBdProt * connectBdProt ) = 0;

    virtual void LoadWindowBd85Poisson(
        IPresenterWindowMainBd85 * mainPres,
        ConnectBdProt * connectBdProt ) = 0;
};
//---------------------------------------------------------------------------
#endif
