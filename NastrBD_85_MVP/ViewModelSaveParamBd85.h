//---------------------------------------------------------------------------
#ifndef ViewModelSaveParamBd85H
#define ViewModelSaveParamBd85H
//---------------------------------------------------------------------------
#include "IViewSaveParamBd85.h"
#include "IWindowMainBd85.h"
#include "IFormDispetView.h"
#include "IPresenterWindowMainBd85.h"
//---------------------------------------------------------------------------
class ViewModelSaveParamBd85
{
public:
    ViewModelSaveParamBd85(
        IViewSaveParamBd85 * view,
        IFormDispetView * viewDispet,
        IPresenterWindowMainBd85 * mainPres
    );
    ~ViewModelSaveParamBd85();
private:
    IViewSaveParamBd85 * _view;
    IFormDispetView * _viewDispet;
    IPresenterWindowMainBd85 * _mainPres;

    //===>> Делегаты
    ActionSelf<> * as_FormClose;
    ActionSelf<const char*> * as_EditFileNameChange;
    ActionSelf<const char*> * as_EditFileHeaderChange;
    ActionSelf<const char*> * as_EditTimeChange;
    ActionSelf<const char*> * as_EditNumberChange;
    ActionSelf<const char*> * as_EditDelayChange;
    //<<=== Делегаты
    
    void SetViewParam(); // Начальная настройка
    void CreateActions(); // Создать делегаты
    void ViewSubscribe(); // Подписаться на события вид'а
    void DestroyActions(); // Освободить память, от делегатов

    //===>> Делегаты
    void FormClose();
    void EditFileNameChange(const char * text);
    void EditFileHeaderChange(const char * text);
    void EditTimeChange(const char * text);
    void EditNumberChange(const char * text);
    void EditDelayChange(const char * text);
    //<<=== Делегаты
};
//---------------------------------------------------------------------------
#endif
