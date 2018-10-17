//---------------------------------------------------------------------------
#ifndef PresenterWindowMainBd85H
#define PresenterWindowMainBd85H
//---------------------------------------------------------------------------
#include "IWindowMainBd85.h"
#include "ConnectBdProt.h"
//---------------------------------------------------------------------------
class PresenterWindowMainBd85
{
public:
    PresenterWindowMainBd85(IWindowMainBd85 * view);
    ~PresenterWindowMainBd85();
    bool IsViewLoaded();
private:
    IWindowMainBd85 * _view;
    ConnectBdProt* _connectBdProt;

    ActionSelf<> as_FormClose;
    void FormClose();

    ActionEvent<> ev_Show;
    bool _isViewLoaded;
};
//---------------------------------------------------------------------------
#endif
