//---------------------------------------------------------------------------
#ifndef ViewModelBd85PoissonH
#define ViewModelBd85PoissonH
//---------------------------------------------------------------------------
#include "IViewBd85Poisson.h"
#include "IFormDispetView.h"
#include "IPresenterWindowMainBd85.h"
#include "ConnectBdProt.h"
#include "IViewModelBd85Poisson.h"
//---------------------------------------------------------------------------
class ViewModelBd85Poisson : public IViewModelBd85Poisson
{
public:
    ViewModelBd85Poisson(
        IViewBd85Poisson * view,
        IFormDispetView * viewDispet,
        IPresenterWindowMainBd85 * mainPres,
        IAllProtokolS * allProtokol,
        TaskWithParam * task,
        ConnectBdProt * connectBdProt);
        
    ~ViewModelBd85Poisson();

    bool IsViewLoaded(); // Используется в загрузчике
    //===>> Реализует IViewModelBd85Poisson
    void FormClose();
    //<<=== Реализует IViewModelBd85Poisson
private:
    bool _isViewLoaded;

    IViewBd85Poisson * _view;
    IFormDispetView * _viewDispet;
    IPresenterWindowMainBd85 * _mainPres;
    TaskWithParam * _task;
    //ModelBd85Poisson * _model;

    void SetViewParam(); // Начальная настройка
};
//---------------------------------------------------------------------------
#endif
