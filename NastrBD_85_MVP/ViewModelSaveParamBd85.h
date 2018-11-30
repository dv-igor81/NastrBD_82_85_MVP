//---------------------------------------------------------------------------
#ifndef ViewModelSaveParamBd85H
#define ViewModelSaveParamBd85H
//---------------------------------------------------------------------------
#include "IViewSaveParamBd85.h"
#include "IWindowMainBd85.h"
#include "IFormDispetView.h"
//---------------------------------------------------------------------------
class ViewModelSaveParamBd85
{
public:
    ViewModelSaveParamBd85(
        IViewSaveParamBd85 * view,
        IFormDispetView * viewDispet,
        IWindowMainBd85 * viewMain
    );
    ~ViewModelSaveParamBd85();
private:
    IViewSaveParamBd85 * _view;
    IFormDispetView * _viewDispet;
    IWindowMainBd85 * _viewMain;

    //===>> Делегаты
    ActionSelf<> * as_FormClose;
    //<<=== Делегаты
    
    void SetViewParam(); // Начальная настройка
    void CreateActions(); // Создать делегаты
    void ViewSubscribe(); // Подписаться на события вид'а
    void DestroyActions(); // Освободить память, от делегатов

    //===>> Делегаты
    void FormClose();
    //<<=== Делегаты
};
//---------------------------------------------------------------------------
#endif
