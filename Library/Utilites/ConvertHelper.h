//---------------------------------------------------------------------------
#ifndef ConvertHelperH
#define ConvertHelperH
//---------------------------------------------------------------------------
class ConvertHelper
{
public:
    static double CodeToValue(unsigned short code);
    static unsigned short ValueToCode(double value);
    static double VoltageHiCodeToValue(unsigned short code);
    static unsigned short VoltageHiValueToCode(double value);
    static double TemperatureCodeToValue(unsigned short code);
};
//---------------------------------------------------------------------------
#endif
