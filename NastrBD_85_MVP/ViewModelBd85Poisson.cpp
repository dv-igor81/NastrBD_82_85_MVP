//---------------------------------------------------------------------------
#pragma hdrstop
#include "ViewModelBd85Poisson.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
ViewModelBd85Poisson::ViewModelBd85Poisson(
    IViewBd85Poisson * view,
    IFormDispetView * viewDispet,
    IPresenterWindowMainBd85 * mainPres,
    IAllProtokolS * allProtokol,
    TaskWithParam * task,
    ConnectBdProt * connectBdProt)
{
    _isViewLoaded = true; // �������� ���� (���) ���������
    _view = view;
    _viewDispet = viewDispet;
    _mainPres = mainPres;
    _task = task;

    _view->SetViewModel( this );
    SetViewParam(); // ��������� ���������
}
//---------------------------------------------------------------------------
ViewModelBd85Poisson::~ViewModelBd85Poisson()
{
}
//---------------------------------------------------------------------------
bool ViewModelBd85Poisson::IsViewLoaded()
{
    return _isViewLoaded;
}
//---------------------------------------------------------------------------
void ViewModelBd85Poisson::SetViewParam() // ��������� ���������
{
    _view->SetVerPoText( _viewDispet->GetProgrammVersion() );
    _view->WrapShow();
}
//---------------------------------------------------------------------------
void ViewModelBd85Poisson::FormClose()
{
    _mainPres->ViewFilialClose(); // ��������� �������� �����
    _isViewLoaded = false;
}
//---------------------------------------------------------------------------
