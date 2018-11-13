//---------------------------------------------------------------------------
#ifndef ModBusParamH
#define ModBusParamH
//---------------------------------------------------------------------------
class ModBusParam {
public:
    void SetNumberOfBdChange(const char* text);
private:
    static const unsigned short _numberOfBd;
private:
    //unsigned short _numberOfBd;
};
//---------------------------------------------------------------------------
#endif
