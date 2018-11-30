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

    //===>> ��������
    ActionSelf<> * as_FormClose;
    ActionSelf<const char*> * as_EditFileNameChange;
    ActionSelf<const char*> * as_EditFileHeaderChange;
    ActionSelf<const char*> * as_EditTimeChange;
    ActionSelf<const char*> * as_EditNumberChange;
    ActionSelf<const char*> * as_EditDelayChange;
    //<<=== ��������
    
    void SetViewParam(); // ��������� ���������
    void CreateActions(); // ������� ��������
    void ViewSubscribe(); // ����������� �� ������� ���'�
    void DestroyActions(); // ���������� ������, �� ���������

    //===>> ��������
    void FormClose();
    void EditFileNameChange(const char * text);
    void EditFileHeaderChange(const char * text);
    void EditTimeChange(const char * text);
    void EditNumberChange(const char * text);
    void EditDelayChange(const char * text);
    //<<=== ��������
};
//---------------------------------------------------------------------------
#endif
