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
    WindowLoader(TForm * Owner);
    ~WindowLoader();
    void LoadWindowBd85Main();
private:
    TForm * _owner;
    PresenterWindowMainBd85 * _presenter;
    IAllProtokolS * _allProtokol;
    ITask * _task;
    //===
    ActionSelf<> as_ShowDispetWindow;
    void ShowDispetWindow();
};
//---------------------------------------------------------------------------
#endif
