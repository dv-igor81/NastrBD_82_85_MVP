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
    int * change, // [IN/OUT] ��������� �������� ���������
    int * prev, // [IN/OUT] ���������� �������� ���������
    bool * update, // [IN/OUT] true - �������� ��������� ����
    int min, int max)
{
    // 0 - ��� ������
    // 1 - ����� �������� �� �������
    // 2 - �������� ��������
    int errorCode = 0; // 0 - ��� ������
    int retValue = *change;
    if ( retValue < min )
    {
        errorCode = 1; // 1 - ����� �������� �� �������
    }
    else if ( retValue > max )
    {
        errorCode = 2; // 2 - �������� ��������
    }
    switch ( errorCode )
    {
    case 0: // 0 - ��� ������
        //if (*change != *prev)
        //{
        //    *update = true; // ���������� ����� ��������
        //}
        *prev = retValue; // ��������� ���������� ��������
        break;
    case 1: // 1 - ����� �������� �� �������
        *change = min; // ��������� ��������� ��������
        *prev = min; // ��������� ���������� ��������
        *update = true; // ��������� ������
        break;
    case 2: // 2 - �������� ��������
        *change = max; // ��������� ��������� ��������
        *prev = max; // ��������� ���������� ��������
        *update = true; // ��������� ������
        break;
    }    
}
//---------------------------------------------------------------------------
void TextHelper::ConvertTextToNumber(
    const char * text, // ��������� ������������� ������ �����
    int * change, // [OUT] ��������� �������� ���������
    int * prev, // [IN/OUT] ���������� �������� ���������
    bool * update, // [OUT] true - �������� ��������� ����
    int min, int max)
{
    // 0 - ��� ������
    // 1 - ������ ������� ������
    // 2 - ����� �������� �� �������
    // 3 - �������� ��������
    *update = false; // �� �������������� ��������� ����
    if ( text == 0 )
    {
        return;
    }
    if ( *text == 0 )
    {
        return;
    }
    int errorCode = 0; // 0 - ��� ������
    AnsiString str = text;
    int retValue;
    try
    {
        retValue = StrToInt( str );
        if ( retValue < min )
        {
            errorCode = 2; // 2 - ����� �������� �� �������
        }
        else if ( retValue > max )
        {
            errorCode = 3; // 3 - �������� ��������
        }
    }
    catch (...)
    {
        errorCode = 1; // 1 - ������ ������� ������
    }
    switch ( errorCode )
    {
    case 0: // 0 - ��� ������
        *change = retValue; // ��������� ��������� ��������
        *prev = retValue; // ��������� ���������� ��������
        break;
    case 1: // 1 - ������ ������� ������
        *change = *prev; // �������� ������� ���������
        *update = true; // ��������� ������
        break;
    case 2: // 2 - ����� �������� �� �������
        *change = min; // ��������� ��������� ��������
        *prev = min; // ��������� ���������� ��������
        *update = true; // ��������� ������
        break;
    case 3: // 3 - �������� ��������
        *change = max; // ��������� ��������� ��������
        *prev = max; // ��������� ���������� ��������
        *update = true; // ��������� ������
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
