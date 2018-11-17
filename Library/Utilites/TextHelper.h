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

    static void CharReplace(
        char * ptrText,
        char oldSimbol,
        char newSimbol,
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

    static void CheckNumber(
        int * change, // [IN/OUT] ��������� �������� ���������
        int * prev, // [IN/OUT] ���������� �������� ���������
        bool * update, // [IN/OUT] true - �������� ��������� ����
        int min, int max);

    static void ConvertTextToNumber(
        const char * text, // ��������� ������������� ������ �����
        int * change, // [OUT] ��������� �������� ���������
        int * prev, // [IN/OUT] ���������� �������� ���������,
        bool * update, // [OUT] true - �������� ��������� ����
        int min, int max);

    static double ConvertTextToDouble(
        const char* text,
        double curVal,
        bool * flagError);

    static double ConvertTextToDouble(
        const char* text,
        double curVal,
        double min,
        double max,
        bool * flagError);

    static double Rounding(double var, int quantity);
};
#endif
