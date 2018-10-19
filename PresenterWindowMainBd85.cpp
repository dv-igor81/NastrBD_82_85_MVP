//---------------------------------------------------------------------------
#pragma hdrstop
#include "PresenterWindowMainBd85.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
PresenterWindowMainBd85::PresenterWindowMainBd85(
    IWindowMainBd85 * view,
    IAllProtokolS * allProtokol,
    ITask * task) :
        as_FormClose(this, &PresenterWindowMainBd85::FormClose)
{
    _isViewLoaded = true;
    _view = view;
    _allProtokol = allProtokol;
    _task = task;

    ev_Show += _view->GetSelfShow();
    *_view->GetEventFormClose() += as_FormClose;
    _connectBdProt = new ConnectBdProt(
        _view->GetConnectFourBdProt(), _allProtokol, _task );
    ev_Show(); // Прказать форму
}
//---------------------------------------------------------------------------
PresenterWindowMainBd85::~PresenterWindowMainBd85()
{
    _view->Destroy();
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
