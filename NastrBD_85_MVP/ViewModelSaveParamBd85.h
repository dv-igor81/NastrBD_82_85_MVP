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

    //===>> ��������
    ActionSelf<> * as_FormClose;
    //<<=== ��������
    
    void SetViewParam(); // ��������� ���������
    void CreateActions(); // ������� ��������
    void ViewSubscribe(); // ����������� �� ������� ���'�
    void DestroyActions(); // ���������� ������, �� ���������

    //===>> ��������
    void FormClose();
    //<<=== ��������
};
//---------------------------------------------------------------------------
#endif
