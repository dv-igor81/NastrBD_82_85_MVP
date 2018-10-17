//---------------------------------------------------------------------------
#ifndef HelperNumberTextBtnH
#define HelperNumberTextBtnH
//---------------------------------------------------------------------------
#include "ActionEvent.h"
using namespace smartevents;
//---------------------------------------------------------------------------
class HelperNumberTextBtn{
public:
    HelperNumberTextBtn(
        ActionSelf<const char*>* as_tbxNum_SetText, // Изменяю текст программно
        ActionEvent<const char*>* ev_tbxNum_TextChanged, // Текст изменился из ГИП
        //------------------------------------
        ActionEvent<>* ev_btnDec_Click,
        //------------------------------------
        ActionEvent<>* ev_btnInc_Click,
        int defVal,
        //------------------------------------
        int minVal,
        //------------------------------------
        int maxVal);
private:
    ActionSelf<const char*>* _as_tbxNum_SetText;
    ActionEvent<const char*>* _ev_tbxNum_TextChanged;
    ActionEvent<>* _ev_btnDec_Click;
    ActionEvent<>* _ev_btnInc_Click;
    int _defVal;
    int _minVal;
    int _maxVal;
};
//---------------------------------------------------------------------------
#endif
