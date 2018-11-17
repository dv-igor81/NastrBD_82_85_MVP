//---------------------------------------------------------------------------
#pragma hdrstop
#include "TextHelper.h"
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
int TextHelper::AddText(
    char * ptrTo,
    const char * ptrFrom,
    int lenTo,
    int maxLength)
{
    if (lenTo < 0)
    {
        return -1;
    }
    int lenFrom = GetLengText(ptrFrom, maxLength);
    if (lenFrom == 0)
    {
        return -1;
    }
    int lenSum = lenTo + lenFrom;
    if ( lenSum > maxLength )
    {
	return -1;
    }
    int i, j;
    for (i = lenTo, j = 0; i < lenSum; i++, j++)
    {
        ptrTo[i] = ptrFrom[j];
    }
    ptrTo[i] = 0;
    return lenSum;
}
//---------------------------------------------------------------------------
void TextHelper::SetCharInText(
    char * ptrText,
    char simbol,
    int maxLength)
{
    maxLength--;
    for (int i = 0; i < maxLength; i++)
    {
        ptrText[i] = simbol;
    }
    ptrText[maxLength] = 0;
}
//---------------------------------------------------------------------------
void TextHelper::CharReplace(
    char * ptrText,
    char oldSimbol,
    char newSimbol,
    int maxLength)
{
    maxLength--;
    for (int i = 0; i < maxLength; i++)
    {
        if ( ptrText[i] == oldSimbol )
        {
            ptrText[i] = newSimbol;
        }
    }
    ptrText[maxLength] = 0;
}
//---------------------------------------------------------------------------
int TextHelper::GetLengText(
    const char * ptrText,
    int maxLength)
{
    if ( ptrText == 0 )
    {
        return 0;
    }
    int retVal = -1;
    for (int i = 0; i <= maxLength; i++)
    {
        if (ptrText[i] == 0)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}
//---------------------------------------------------------------------------
void TextHelper::CopyText(
    char * ptrTo,
    const char * ptrFrom,
    int maxLength)
{
    AddText(ptrTo, ptrFrom, 0, maxLength);
}
//---------------------------------------------------------------------------
int TextHelper::ConvertTextToNumber(
    const char* text, int curVal)
{
    if ( text == 0 )
    {
        return curVal;
    }
    if ( *text == 0 )
    {
        return curVal;
    }
    AnsiString str = text;
    int retValue;    
    try
    {
        retValue = StrToInt( str );
    }
    catch (...)
    {
        retValue = curVal;
    }
    return retValue;
}
//---------------------------------------------------------------------------
void TextHelper::CheckNumber(
    int * change, // [IN/OUT] Изменённое значение параметра
    int * prev, // [IN/OUT] Предыдущее значение параметра
    bool * update, // [IN/OUT] true - обновить текстовое поле
    int min, int max)
{
    // 0 - нет ошибки
    // 1 - выход значения за минимум
    // 2 - превышен максимум
    int errorCode = 0; // 0 - нет ошибки
    int retValue = *change;
    if ( retValue < min )
    {
        errorCode = 1; // 1 - выход значения за минимум
    }
    else if ( retValue > max )
    {
        errorCode = 2; // 2 - превышен максимум
    }
    switch ( errorCode )
    {
    case 0: // 0 - нет ошибки
        //if (*change != *prev)
        //{
        //    *update = true; // Отобразить новое значение
        //}
        *prev = retValue; // Сохранить предыдущее значение
        break;
    case 1: // 1 - выход значения за минимум
        *change = min; // Сохранить изменённое значение
        *prev = min; // Сохранить предыдущее значение
        *update = true; // Исправить ошибку
        break;
    case 2: // 2 - превышен максимум
        *change = max; // Сохранить изменённое значение
        *prev = max; // Сохранить предыдущее значение
        *update = true; // Исправить ошибку
        break;
    }    
}
//---------------------------------------------------------------------------
void TextHelper::ConvertTextToNumber(
    const char * text, // Текстовое представление целого числа
    int * change, // [OUT] Изменённое значение параметра
    int * prev, // [IN/OUT] Предыдущее значение параметра
    bool * update, // [OUT] true - обновить текстовое поле
    int min, int max)
{
    // 0 - нет ошибки
    // 1 - ошибка формата строки
    // 2 - выход значения за минимум
    // 3 - превышен максимум
    *update = false; // Не перерисовывать текстовое поле
    if ( text == 0 )
    {
        return;
    }
    if ( *text == 0 )
    {
        return;
    }
    int errorCode = 0; // 0 - нет ошибки
    AnsiString str = text;
    int retValue;
    try
    {
        retValue = StrToInt( str );
        if ( retValue < min )
        {
            errorCode = 2; // 2 - выход значения за минимум
        }
        else if ( retValue > max )
        {
            errorCode = 3; // 3 - превышен максимум
        }
    }
    catch (...)
    {
        errorCode = 1; // 1 - ошибка формата строки
    }
    switch ( errorCode )
    {
    case 0: // 0 - нет ошибки
        *change = retValue; // Сохранить изменённое значение
        *prev = retValue; // Сохранить предыдущее значение
        break;
    case 1: // 1 - ошибка формата строки
        *change = *prev; // Отменить попытку изменения
        *update = true; // Исправить ошибку
        break;
    case 2: // 2 - выход значения за минимум
        *change = min; // Сохранить изменённое значение
        *prev = min; // Сохранить предыдущее значение
        *update = true; // Исправить ошибку
        break;
    case 3: // 3 - превышен максимум
        *change = max; // Сохранить изменённое значение
        *prev = max; // Сохранить предыдущее значение
        *update = true; // Исправить ошибку
        break;
    }
}
//---------------------------------------------------------------------------
double TextHelper::ConvertTextToDouble(
    const char* text,
    double curVal,
    bool * flagError)
{
    *flagError = false;
    if ( text == 0 )
    {
        return curVal;
    }
    if ( *text == 0 )
    {
        return curVal;
    }
    const int size = 50;
    char tmpText[size];
    double retValue;
    CopyText(tmpText, text, size);
    CharReplace(tmpText, '.', ',', size);
    AnsiString str = tmpText;
    try
    {
        retValue = StrToFloat( str );
    }
    catch (...)
    {
        retValue = curVal;
        *flagError = true;
    }
    return retValue;
}
//---------------------------------------------------------------------------
double TextHelper::ConvertTextToDouble(
    const char* text,
    double curVal,
    double min,
    double max,    
    bool * flagError)
{
    *flagError = false;
    if ( text == 0 )
    {
        return curVal;
    }
    if ( *text == 0 )
    {
        return curVal;
    }
    const int size = 50;
    char tmpText[size];
    double retValue;
    CopyText(tmpText, text, size);
    CharReplace(tmpText, '.', ',', size);
    AnsiString str = tmpText;
    try
    {
        retValue = StrToFloat( str );
        if ( retValue > max || retValue < min )
        {
            retValue = curVal;
            *flagError = true;
        }        
    }
    catch (...)
    {
        retValue = curVal;
        *flagError = true;        
    }
    return retValue;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
