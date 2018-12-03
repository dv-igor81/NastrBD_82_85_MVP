//---------------------------------------------------------------------------
#pragma hdrstop
#include "WindowLoader.h"
#include "AllProtokolS.h"
#include "Task.h"
//---------------------------------------------------------------------------
#include "WindowMainNastrBd85.h"
#include "WindowSaveParamNastrBd85.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
WindowLoader::WindowLoader(
    TForm * Owner,
    IFormDispetView * view) :
    _presenter(0),
    _vmSaveParam(0),
    _allProtokol(0),
    _task(0)
{
    _owner = Owner;
    //_view = (IFormDispetView *)_owner; Так не работает... ошибка выполнения
    _viewDispet = view;
    _allProtokol = new AllProtokolS();
    //_task = new Task();
    _task = new TaskWithParam( new Task() );
}
//---------------------------------------------------------------------------
WindowLoader::~WindowLoader()
{
    if ( _presenter != 0 )
    {
        delete _presenter;
    }
    delete _allProtokol;
    delete _task;
}
//---------------------------------------------------------------------------
void WindowLoader::LoadWindowBd85Main()
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
        TWindowMainBd85 * view = new TWindowMainBd85(
            _owner
        );
        _presenter = new PresenterWindowMainBd85(
            view,
            _viewDispet,
            _allProtokol,
            _task, this);
    }
}
//---------------------------------------------------------------------------
void WindowLoader::LoadWindowBd85SaveParam(
    IPresenterWindowMainBd85 * mainPres,
    ConnectBdProt * connectBdProt)
{
    bool viewIsLoaded = true;
    if ( _vmSaveParam == 0 )
    {
        viewIsLoaded = false;
    }
    else if ( _vmSaveParam->IsViewLoaded() == false )
    {
        viewIsLoaded = false;
        delete _vmSaveParam;
    }
    if (  viewIsLoaded == false  )
    {
        TWindowSaveParamBd85 * _view = new TWindowSaveParamBd85(
            _owner
        );
        _vmSaveParam = new ViewModelSaveParamBd85(
            _view, _viewDispet, mainPres,
            _allProtokol, _task, connectBdProt
        );
    }
}
//---------------------------------------------------------------------------
