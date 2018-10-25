//---------------------------------------------------------------------------
#pragma hdrstop
#include "ConvertHelper.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
double ConvertHelper::CodeToValue(unsigned short code)
{
    double retVal = code;
    retVal *= 2.5;
    retVal /= 4095;
    return retVal;
}
//---------------------------------------------------------------------------
unsigned short ConvertHelper::ValueToCode(double value)
{
    return 0; // stub
}
//---------------------------------------------------------------------------
double ConvertHelper::VoltageHiCodeToValue(unsigned short code)
{
    double retVal = code;
    retVal *= (2.5 * 1000);
    retVal /= 4096;
    return retVal;
}
//---------------------------------------------------------------------------
unsigned short ConvertHelper::VoltageHiValueToCode(double value)
{
    return 0; // stub
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
