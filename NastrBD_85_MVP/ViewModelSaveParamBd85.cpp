//---------------------------------------------------------------------------
#pragma hdrstop
#include "ViewModelSaveParamBd85.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
ViewModelSaveParamBd85::ViewModelSaveParamBd85(
    IViewSaveParamBd85 * view,
    IFormDispetView * viewDispet,
    IWindowMainBd85 * viewMain
)
{
    _view = view;
    _viewDispet = viewDispet;
    _viewMain = viewMain;
    SetViewParam(); // Начальная настройка
    CreateActions(); // Создать делегаты
    ViewSubscribe(); // Подписаться на события вид'а
}
//---------------------------------------------------------------------------
ViewModelSaveParamBd85::~ViewModelSaveParamBd85()
{
    _view->Destroy();
    DestroyActions();
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::SetViewParam()
{ // Начальная настройка
    _view->SetVerPoText( _viewDispet->GetProgrammVersion() );
    _view->SetFileName( "bd85.log" );
    _view->SetFileNameEnabled(true);
    _view->SetFileHeader("");
    _view->SetFileHeaderEnabled(true);
    _view->SetTimeText("100");
    _view->SetTimeEnabled(true);
    _view->SetNumberText("10");
    _view->SetNumberEnabled(true);
    _view->SetDelayText("0");
    _view->SetDelayEnabled(true);
    _view->WrapShow();
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::CreateActions()
{
    as_FormClose = new ActionSelf<>(this, &ViewModelSaveParamBd85::FormClose);
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::ViewSubscribe() // Подписаться на события вид'а
{
    _view->EventFormClose() += as_FormClose;
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::DestroyActions()
{
    delete as_FormClose;
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::FormClose()
{
    _viewMain->WrapShow();
    delete this;
}
//---------------------------------------------------------------------------
