//---------------------------------------------------------------------------
#pragma hdrstop
#include "PresenterWindowMainBd85.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
PresenterWindowMainBd85::PresenterWindowMainBd85(IWindowMainBd85 * view) :
    as_FormClose(this, &PresenterWindowMainBd85::FormClose)
{
    _isViewLoaded = true;
    _view = view;
    ev_Show += _view->GetSelfShow();
    *_view->GetEventFormClose() += as_FormClose;
    _connectBdProt = new ConnectBdProt( _view->GetConnectFourBdProt() );
    ev_Show(); // Прказать форму
}
//---------------------------------------------------------------------------
PresenterWindowMainBd85::~PresenterWindowMainBd85()
{
    //if (_view != 0)
    //{
    //    delete _view;
    //}
}
//---------------------------------------------------------------------------
void PresenterWindowMainBd85::FormClose()
{
    _isViewLoaded = false;
}
//---------------------------------------------------------------------------
bool PresenterWindowMainBd85::IsViewLoaded()
{
    return _isViewLoaded;
}
