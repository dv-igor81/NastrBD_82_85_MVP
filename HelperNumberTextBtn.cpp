//---------------------------------------------------------------------------
#pragma hdrstop
#include "HelperNumberTextBtn.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
HelperNumberTextBtn::HelperNumberTextBtn(
        ActionSelf<const char*>* as_tbxNum_SetText, // Изменяю текст программно
        ActionEvent<const char*>* ev_tbxNum_TextChanged, // Текст изменился из ГИП
        ActionEvent<>* ev_btnDec_Click,
        ActionEvent<>* ev_btnInc_Click,
        int defVal,
        int minVal,
        int maxVal)
{
    _as_tbxNum_SetText = as_tbxNum_SetText;
    _ev_tbxNum_TextChanged = ev_tbxNum_TextChanged;
    _ev_btnDec_Click = ev_btnDec_Click;
    _ev_btnInc_Click = ev_btnInc_Click;
    _defVal = defVal;
    _minVal = minVal;
    _maxVal = maxVal;
}
