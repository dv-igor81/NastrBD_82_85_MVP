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
        int maxVal) :
        as_tbxNum_TextChanged(this, &HelperNumberTextBtn::TbxNumTextChanged)
        , as_btnDec_Click(this, &HelperNumberTextBtn::BtnDecClick)
        , as_btnInc_Click(this, &HelperNumberTextBtn::BtnIncClick)
{
    _as_tbxNum_SetText = as_tbxNum_SetText;
    _ev_tbxNum_TextChanged = ev_tbxNum_TextChanged;
    _ev_btnDec_Click = ev_btnDec_Click;
    _ev_btnInc_Click = ev_btnInc_Click;

    _defVal = defVal;
    _curVal = _defVal;
    _minVal = minVal;
    _maxVal = maxVal;
    _flagIgnor = false;

    ev_tbxNum_SetText += _as_tbxNum_SetText;
    *_ev_tbxNum_TextChanged += as_tbxNum_TextChanged;
    *_ev_btnDec_Click += as_btnDec_Click;
    *_ev_btnInc_Click += as_btnInc_Click;
}
//---------------------------------------------------------------------------
int HelperNumberTextBtn::GetNumber()
{
    return _curVal;
}
//---------------------------------------------------------------------------
void HelperNumberTextBtn::SetNumber(int number)
{
    _curVal = number;
    AnsiString str = IntToStr(_curVal);
    TbxNum_SetText( str.c_str() );
}
//---------------------------------------------------------------------------
void HelperNumberTextBtn::SetNumber()
{
    SetNumber(_curVal);
}
//---------------------------------------------------------------------------
void HelperNumberTextBtn::NumberIncrement()
{
    if ( _curVal < _maxVal )
    {
        _curVal++;
    }
    else
    {
        _curVal = _minVal;
    }
    SetNumber();
    //AnsiString str = IntToStr(_curVal);
    //TbxNum_SetText( str.c_str() );
}
//---------------------------------------------------------------------------
void HelperNumberTextBtn::NubmerDecrement()
{
    if ( _curVal > _minVal )
    {
        _curVal--;
    }
    else
    {
        _curVal = _maxVal;
    }
    SetNumber();
    //AnsiString str = IntToStr(_curVal);
    //TbxNum_SetText( str.c_str() );
}
//---------------------------------------------------------------------------
void HelperNumberTextBtn::NumberValueChanged(const char* text)
{
    if ( _flagIgnor == false ) // ===>> Предотвратить "бесконечную" рекурсию
    {
        if ( IsNullOrEmpty(text) )
        {
            _curVal = _defVal;
        }
        else
        {
            ConvertTextToNumber(text, _curVal);
        }
    } // <<=== Предотвратить "бесконечную" рекурсию
}
//---------------------------------------------------------------------------
void HelperNumberTextBtn::TbxNumTextChanged(const char* text)
{
    NumberValueChanged(text);
}
//---------------------------------------------------------------------------
void HelperNumberTextBtn::BtnDecClick()
{
    NubmerDecrement();
}
//---------------------------------------------------------------------------
void HelperNumberTextBtn::BtnIncClick()
{
    NumberIncrement();
}
//---------------------------------------------------------------------------
bool HelperNumberTextBtn::IsNullOrEmpty(const char* text)
{
    return (GetLengText(text) <= 0);
}
//---------------------------------------------------------------------------
int HelperNumberTextBtn::GetLengText(const char* text)
{
    if (text == 0)
    {
        return 0;
    }
    int maxLength = 20;
    int retVal = -1;
    for (int i = 0; i <= maxLength; i++)
    {
        if (text[i] == 0)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}
//---------------------------------------------------------------------------
void HelperNumberTextBtn::ConvertTextToNumber(const char* text, int curVal)
{
    AnsiString str = text;
    int retValue;
    try
    {
        retValue = StrToInt( str );
        if ( retValue > _maxVal || retValue < _minVal )
        {
            retValue = curVal;
        }
    }
    catch (...)
    {
        retValue = curVal;
    }
    SetNumber(retValue);
}
//---------------------------------------------------------------------------
void HelperNumberTextBtn::TbxNum_SetText(const char* text)
{
    _flagIgnor = true; // ===>> Предотвратить "бесконечную" рекурсию
    ev_tbxNum_SetText( text );
    _flagIgnor = false; // <<=== Предотвратить "бесконечную" рекурсию
}
