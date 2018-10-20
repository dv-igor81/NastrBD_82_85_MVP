//---------------------------------------------------------------------------
#ifndef WindowLoaderH
#define WindowLoaderH
//---------------------------------------------------------------------------
#include <vcl.h>
//---------------------------------------------------------------------------
#include "PresenterWindowMainBd85.h"
#include "IAllProtokolS.h"
#include "ITask.h"
//---------------------------------------------------------------------------
class WindowLoader 
{
public:
    WindowLoader(TComponent* Owner);
    ~WindowLoader();
    void LoadWindowMain();
private:
    TComponent * _owner;
    PresenterWindowMainBd85 * _presenter;
    IAllProtokolS * _allProtokol;
    ITask * _task;
};
//---------------------------------------------------------------------------
#endif
