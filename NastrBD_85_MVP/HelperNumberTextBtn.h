//---------------------------------------------------------------------------
#ifndef HelperNumberTextBtnH
#define HelperNumberTextBtnH
//---------------------------------------------------------------------------
#include "ActionEvent.h"
using namespace smartevents;
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class HelperNumberTextBtn{
public:
    HelperNumberTextBtn(
        ActionSelf<const char*>* as_tbxNum_SetText, // Изменяю текст программно
        ActionEvent<const char*>* ev_tbxNum_TextChanged, // Текст изменился из ГИП
        ActionEvent<>* ev_btnDec_Click,
        ActionEvent<>* ev_btnInc_Click,
        int defVal,
        int minVal,
        int maxVal);
    int GetNumber();
    void SetNumber(int number);
    void SetNumber();
    ActionEvent<int>* GetEventSetNumber();
private:
    ActionSelf<const char*>* _as_tbxNum_SetText;
    ActionEvent<const char*>* _ev_tbxNum_TextChanged;
    ActionEvent<>* _ev_btnDec_Click;
    ActionEvent<>* _ev_btnInc_Click;
    //==============================================
    ActionEvent<const char*> ev_tbxNum_SetText;
    ActionEvent<int> ev_tbxNum_SetNumber;
    //==============================================
    ActionSelf<const char*> as_tbxNum_TextChanged;
    void TbxNumTextChanged(const char*);
    ActionSelf<> as_btnDec_Click;
    void BtnDecClick();
    ActionSelf<> as_btnInc_Click;
    void BtnIncClick();
    //==============================================
    int _defVal;
    int _minVal;
    int _maxVal;
    int _curVal;
    bool _flagIgnor;

    void NumberIncrement();
    void NubmerDecrement();
    void NumberValueChanged(const char* text);
    bool IsNullOrEmpty(const char* text);
    int GetLengText(const char* text); // Получить длинну строки (оканчивающююся нулевым символом)
    void ConvertTextToNumber(const char* text, int curVal);
    void TbxNum_SetText(const char* text);
};
//---------------------------------------------------------------------------
#endif
