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

    static int GetLengText(
        const char * ptrText,
        int maxLength);
        
    static void CopyText(
        char * ptrTo,
        const char * ptrFrom,
        int maxLength);
};
#endif
