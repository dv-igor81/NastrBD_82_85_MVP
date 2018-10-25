//---------------------------------------------------------------------------
#pragma hdrstop
#include "TextHelper.h"
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
