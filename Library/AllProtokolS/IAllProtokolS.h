//---------------------------------------------------------------------------
#ifndef IAllProtokolSH
#define IAllProtokolSH
//---------------------------------------------------------------------------
class IAllProtokolS
{
public:
    virtual ~IAllProtokolS(){};
    virtual void UpdateComPotrs() = 0;
    virtual bool NextComPortIndex(int * comPortIndex) = 0;
};
//---------------------------------------------------------------------------
#endif
