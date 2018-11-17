//---------------------------------------------------------------------------
#ifndef WindowLoaderH
#define WindowLoaderH
//---------------------------------------------------------------------------
#include <vcl.h>
//---------------------------------------------------------------------------
#include "PresenterWindowMainBd85.h"
#include "IAllProtokolS.h"
#include "ITask.h"
#include "TaskWithParam.h"
#include "IFormDispetView.h"
//---------------------------------------------------------------------------
class WindowLoader 
{
public:
    WindowLoader(
        TForm * Owner,
        IFormDispetView * view);
    ~WindowLoader();
    void LoadWindowBd85Main();
private:
    IFormDispetView * _viewDispet;
    TForm * _owner;
    PresenterWindowMainBd85 * _presenter;
    IAllProtokolS * _allProtokol;
    //ITask * _task;
    TaskWithParam * _task;
};
//---------------------------------------------------------------------------
#endif
