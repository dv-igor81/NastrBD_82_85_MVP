//---------------------------------------------------------------------------
#ifndef TextHelperH
#define TextHelperH
//---------------------------------------------------------------------------
class TextHelper
{
public:
    static int AddText(
        char * ptrTo,
        const char * ptrFrom,
        int lenTo,
        int maxLength);

    static void SetCharInText(
        char * ptrText,
        char simbol,
        int maxLength);

    static int GetLengText(
        const char * ptrText,
        int maxLength);
        
    static void CopyText(
        char * ptrTo,
        const char * ptrFrom,
        int maxLength);

    static int ConvertTextToNumber(
        const char* text,
        int curVal);

    static int ConvertTextToNumber(
        const char* text,
        int curVal,
        int min,
        int max);
};
#endif
