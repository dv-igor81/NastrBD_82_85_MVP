//---------------------------------------------------------------------------
#pragma hdrstop
#include "ViewModelSaveParamBd85.h"
#include "ModelSaveParamBd85.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
ViewModelSaveParamBd85::ViewModelSaveParamBd85(
    IViewSaveParamBd85 * view,
    IFormDispetView * viewDispet,
    IPresenterWindowMainBd85 * mainPres,
    IAllProtokolS * allProtokol,
    TaskWithParam * task,
    ConnectBdProt * connectBdProt
)
{
    _view = view;
    _viewDispet = viewDispet;
    _mainPres = mainPres;
    _isViewLoaded = true; // основное окно (вид) загружено
    _task = task;
    _model = new ModelSaveParamBd85( allProtokol, this, connectBdProt );
    //===
    CreateActions(); // Создать делегаты
    ViewSubscribe(); // Подписаться на события вид'а
    SetViewParam(); // Начальная настройка
}
//---------------------------------------------------------------------------
ViewModelSaveParamBd85::~ViewModelSaveParamBd85()
{
    DestroyActions();
    _view->Destroy();
    delete _model;
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::SetViewParam()
{ // Начальная настройка
    _view->SetSummTimeText("---");
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
    _view->SetButtonOkText( "Старт" );
    _view->SetErrorText("0");
    _view->SetCurrTimeText("0");
    _view->SetInfoText("");
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
    as_ButtonOkClick = new ActionSelf<>(this, &ViewModelSaveParamBd85::ButtonOkClick);
    as_ButtonCancelClick = new ActionSelf<>(this, &ViewModelSaveParamBd85::ButtonCancelClick);
    //=== Для работы в Invoke - функциях
    as_DisplayErrors = new ActionSelf<const char*>(this, &ViewModelSaveParamBd85::DisplayErrors);
    as_DisplayCurrTime = new ActionSelf<int>(this, &ViewModelSaveParamBd85::DisplayCurrTime);
    as_DisplayInfo = new ActionSelf<const char*>(this, &ViewModelSaveParamBd85::DisplayInfo);
    as_DisplayMiddleScaling = new ActionSelf<const char*>(this, &ViewModelSaveParamBd85::DisplayMiddleScaling);
    as_DisplayTotalScaling = new ActionSelf<const char*>(this, &ViewModelSaveParamBd85::DisplayTotalScaling);
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
    _view->EventButtonOkClick() += as_ButtonOkClick;
    _view->EventButtonCancelClick() += as_ButtonCancelClick;
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
    delete as_ButtonOkClick;
    delete as_ButtonCancelClick;
    //=== Для работы в Invoke - функциях
    delete as_DisplayErrors;
    delete as_DisplayCurrTime;
    delete as_DisplayInfo;
    delete as_DisplayMiddleScaling;
    delete as_DisplayTotalScaling;
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::FormClose()
{
    _mainPres->ViewFilialClose(); // Закрылась дочерняя форма
    _isViewLoaded = false;
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::EditFileNameChange(const char * text)
{
    _model->FileName = text;
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::EditFileHeaderChange(const char * text)
{
    _model->FileHeader = text;
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::EditTimeChange(const char * text)
{
    UpdateSummTimeText( & _model->m_nT, text ); // Время измерения, (с)
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::EditNumberChange(const char * text)
{
    UpdateSummTimeText( & _model->m_nN, text ); // Количество изменений
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::EditDelayChange(const char * text)
{
    UpdateSummTimeText( & _model->m_nZ, text ); // Задержка (мин)
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::ButtonOkClick()
{
    bool work = _model->StartStopWork();
    ControlsEnabled( !work );
    if ( work )
    {
        _view->SetButtonOkText( "Стоп" );
        _model->DisplayInfo();
    }
    else
    {
        _view->SetButtonOkText( "Старт" );
        _view->SetInfoText( "" );
        _view->SetMiddleScalingText( "" );
        _view->SetTotalScalingText( "" );
    }
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::ButtonOkClickInvoke()
{
    _task->BeginInvoke( as_ButtonOkClick );
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::ButtonCancelClick()
{
    _view->WrapClose();
}
//---------------------------------------------------------------------------
bool ViewModelSaveParamBd85::IsViewLoaded()
{
    return _isViewLoaded;
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::ControlsEnabled( bool enabled )
{
    _view->SetFileNameEnabled( enabled );
    _view->SetFileHeaderEnabled( enabled );
    _view->SetTimeEnabled( enabled );
    _view->SetNumberEnabled( enabled );
    _view->SetDelayEnabled( enabled );
    _view->SetButtonCancelEnabled( enabled );
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::UpdateSummTimeText(unsigned int * outVal, const char * inVal)
{
    if ( inVal != 0 )
    {
        if ( inVal[0] != 0 )
        {
            *outVal = StrToInt( inVal );
            int summTime = _model->GetSummTime();
            AnsiString text = IntToStr( summTime );
            _view->SetSummTimeText( text.c_str() );
        }
    }
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::DisplayErrorsInvoke(const char * text)
{
    _task->BeginInvoke<const char*>( as_DisplayErrors, text );
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::DisplayErrors(const char * text)
{
    _view->SetErrorText(text);
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::DisplayCurrTimeInvoke(int currTime)
{
    _task->BeginInvoke<int>( as_DisplayCurrTime, currTime );
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::DisplayCurrTime(int currTime)
{
    AnsiString text = IntToStr( currTime );
    _view->SetCurrTimeText( text.c_str() );
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::DisplayInfoInvoke(const char * text)
{
    _task->BeginInvoke<const char*>( as_DisplayInfo, text );
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::DisplayInfo(const char * text)
{
    _view->SetInfoText( text );
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::DisplayMiddleScalingInvoke(const char * text)
{
    _task->BeginInvoke<const char*>( as_DisplayMiddleScaling, text );
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::DisplayMiddleScaling(const char * text)
{
    _view->SetMiddleScalingText( text );
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::DisplayTotalScalingInvoke(const char * text)
{
    _task->BeginInvoke<const char*>( as_DisplayTotalScaling, text );
}
//---------------------------------------------------------------------------
void ViewModelSaveParamBd85::DisplayTotalScaling(const char * text)
{
    _view->SetTotalScalingText( text );
}
//---------------------------------------------------------------------------
