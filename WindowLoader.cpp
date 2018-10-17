//---------------------------------------------------------------------------
#pragma hdrstop
#include "WindowLoader.h"
#include "WindowMainNastrBd85.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
WindowLoader::WindowLoader(TComponent* Owner) : _presenter(0)
{
    _owner = Owner;
}
//---------------------------------------------------------------------------
void WindowLoader::LoadWindowMain()
{
    bool viewIsLoaded = true;
    if ( _presenter == 0 )
    {
        viewIsLoaded = false;
    }
    else if ( _presenter->IsViewLoaded() == false )
    {
        viewIsLoaded = false;
        delete _presenter;
    }
    if ( viewIsLoaded == false )
    {
        TWindowMainBd85 * view = new TWindowMainBd85(_owner);
        _presenter = new PresenterWindowMainBd85(view);
    }
}
//---------------------------------------------------------------------------
