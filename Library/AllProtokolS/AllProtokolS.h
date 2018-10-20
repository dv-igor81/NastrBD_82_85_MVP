//---------------------------------------------------------------------------
#ifndef AllProtokolSH
#define AllProtokolSH
//---------------------------------------------------------------------------
#include "IAllProtokolS.h"
#include "RSProtokol.h"
//---------------------------------------------------------------------------
class AllProtokolS : public IAllProtokolS
{
public:
    AllProtokolS();
    ~AllProtokolS();
    void UpdateComPotrs();
    bool NextComPortIndex(int * comPortIndex);
private:
    enum { comPortCount = 100 };
    bool findComPorts[comPortCount];
    RSProtokol_t * protokol;
    int comPortPtr;
};
//---------------------------------------------------------------------------
#endif
