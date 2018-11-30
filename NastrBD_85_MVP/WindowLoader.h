//---------------------------------------------------------------------------
#ifndef WindowLoaderH
#define WindowLoaderH
//---------------------------------------------------------------------------
#include <vcl.h>
//---------------------------------------------------------------------------
#include "PresenterWindowMainBd85.h"
#include "ViewModelSaveParamBd85.h"
//---------------------------------------------------------------------------
#include "IAllProtokolS.h"
#include "ITask.h"
#include "TaskWithParam.h"
#include "IFormDispetView.h"
#include "IWindowLoader.h"
//---------------------------------------------------------------------------
class WindowLoader : public IWindowLoader
{
public:
    WindowLoader(
        TForm * Owner,
        IFormDispetView * view);
    ~WindowLoader();
    void LoadWindowBd85Main();
    void LoadWindowBd85SaveParam(IPresenterWindowMainBd85 * mainPres);
private:
    IFormDispetView * _viewDispet;
    //IWindowMainBd85 * _viewMain;
    TForm * _owner;
    PresenterWindowMainBd85 * _presenter;
    IAllProtokolS * _allProtokol;
    //ITask * _task;
    TaskWithParam * _task;
    ViewModelSaveParamBd85 * _vmSaveParam;

};
//---------------------------------------------------------------------------
#endif
