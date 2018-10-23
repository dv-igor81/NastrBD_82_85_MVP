//---------------------------------------------------------------------------
#ifndef StartDataNewBd85H
#define StartDataNewBd85H
//---------------------------------------------------------------------------
class StartDataNewBd85
{
public:
    StartDataNewBd85(
        const char* verPo);
    const char* GetVerPo();
private:
    enum { verPoSize = 5 };
    char _verPo[verPoSize];
};
//---------------------------------------------------------------------------
#endif
