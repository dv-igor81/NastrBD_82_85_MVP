//---------------------------------------------------------------------------
#ifndef ViewModelSaveParamBd85H
#define ViewModelSaveParamBd85H
//---------------------------------------------------------------------------
#include "IViewSaveParamBd85.h"
#include "IWindowMainBd85.h"
#include "IFormDispetView.h"
#include "IPresenterWindowMainBd85.h"
#include "ConnectBdProt.h"
//---------------------------------------------------------------------------
class ModelSaveParamBd85;
//---------------------------------------------------------------------------
class ViewModelSaveParamBd85
{
public:
    ViewModelSaveParamBd85(
        IViewSaveParamBd85 * view,
        IFormDispetView * viewDispet,
        IPresenterWindowMainBd85 * mainPres,
        IAllProtokolS * allProtokol,
        TaskWithParam * task,
        ConnectBdProt * connectBdProt );
    ~ViewModelSaveParamBd85();
    bool IsViewLoaded();
    //===>> Invoke - �������
    void DisplayErrorsInvoke(const char * text);
    void DisplayCurrTimeInvoke(int currTime);
    void ButtonOkClickInvoke();
    void DisplayInfoInvoke(const char * text);
    void DisplayMiddleScalingInvoke(const char * text);
    void DisplayTotalScalingInvoke(const char * text);
    //<<=== Invoke - �������
private:
    IViewSaveParamBd85 * _view;
    IFormDispetView * _viewDispet;
    IPresenterWindowMainBd85 * _mainPres;
    TaskWithParam * _task;
    bool _isViewLoaded;
    ModelSaveParamBd85 * _model;

    //===>> ��������
    ActionSelf<> * as_FormClose;
    ActionSelf<const char*> * as_EditFileNameChange;
    ActionSelf<const char*> * as_EditFileHeaderChange;
    ActionSelf<const char*> * as_EditTimeChange;
    ActionSelf<const char*> * as_EditNumberChange;
    ActionSelf<const char*> * as_EditDelayChange;
    ActionSelf<> * as_ButtonOkClick;
    ActionSelf<> * as_ButtonCancelClick;
    //=== ��� ������ � Invoke - ��������
    ActionSelf<const char*> * as_DisplayErrors;
    ActionSelf<int> * as_DisplayCurrTime;
    ActionSelf<const char*> * as_DisplayInfo;
    ActionSelf<const char*> * as_DisplayMiddleScaling;
    ActionSelf<const char*> * as_DisplayTotalScaling;
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
    void ButtonOkClick();
    void ButtonCancelClick();    
    //=== ��� ������ � Invoke - ��������
    void DisplayErrors(const char * text);
    void DisplayCurrTime(int currTime);
    void DisplayInfo(const char * text);
    void DisplayMiddleScaling(const char * text);
    void DisplayTotalScaling(const char * text);
    //<<=== ��������

    void ControlsEnabled( bool enabled );
    void UpdateSummTimeText(unsigned int * outVal, const char * inVal);
};
//---------------------------------------------------------------------------
#endif
