//---------------------------------------------------------------------------
#ifndef WindowLoaderH
#define WindowLoaderH
//---------------------------------------------------------------------------
#include <vcl.h>
//---------------------------------------------------------------------------
#include "PresenterWindowMainBd85.h"
//---------------------------------------------------------------------------
class WindowLoader 
{
public:
    WindowLoader(TComponent* Owner);
    void LoadWindowMain();
private:
    TComponent* _owner;
    PresenterWindowMainBd85 * _presenter;    
};
//---------------------------------------------------------------------------
#endif
