//---------------------------------------------------------------------------
#pragma hdrstop
#include "ViewModelSaveParamBd85.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
ViewModelSaveParamBd85::ViewModelSaveParamBd85(
    IViewSaveParamBd85 * view,
    IFormDispetView * viewDispet,
    IPresenterWindowMainBd85 * mainPres
)
{
    _view = view;
    _viewDispet = viewDispet;
    _mainPres = mainPres;
    //===
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
    as_EditFileNameChange = new ActionSelf<const char*>(this, &ViewModelSaveParamBd85::EditFileNameChange);
    as_EditFileHeaderChange = new ActionSelf<const char*>(this, &ViewModelSaveParamBd85::EditFileHeaderChange);
    as_EditTimeChange = new ActionSelf<const char*>(this, &ViewModelSaveParamBd85::EditTimeChange);
    as_EditNumberChange = new ActionSelf<const char*>(this, &ViewModelSaveParamBd85::EditNumberChange);
    as_EditDelayChange = new ActionSelf<const char*>(this, &ViewModelSaveParamBd85::EditDelayChange);
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::ViewSubscribe() // Подписаться на события вид'а
{
    _view->EventFormClose() += as_FormClose;
    _view->EventEditFileNameChange() += as_EditFileNameChange;
    _view->EventEditFileHeaderChange() += as_EditFileHeaderChange;
    _view->EventEditTimeChange() += as_EditTimeChange;
    _view->EventEditNumberChange() += as_EditNumberChange;
    _view->EventEditDelayChange() += as_EditDelayChange;
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::DestroyActions()
{
    delete as_FormClose;
    delete as_EditFileNameChange;
    delete as_EditFileHeaderChange;
    delete as_EditTimeChange;
    delete as_EditNumberChange;
    delete as_EditDelayChange;
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::FormClose()
{
    _mainPres->ViewSaveParamBd85Close();
    delete this;
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::EditFileNameChange(const char * text)
{
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::EditFileHeaderChange(const char * text)
{
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::EditTimeChange(const char * text)
{
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::EditNumberChange(const char * text)
{
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::EditDelayChange(const char * text)
{
}
//---------------------------------------------------------------------------
