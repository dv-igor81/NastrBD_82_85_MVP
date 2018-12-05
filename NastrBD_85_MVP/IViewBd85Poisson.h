//---------------------------------------------------------------------------
#ifndef IViewBd85PoissonH
#define IViewBd85PoissonH
//---------------------------------------------------------------------------
//#include "ActionEvent.h"
//using namespace smartevents;
//---------------------------------------------------------------------------
#include "IViewModelBd85Poisson.h"
//---------------------------------------------------------------------------
class IViewBd85Poisson
{
public:
    virtual void SetViewModel( IViewModelBd85Poisson * viewModel ) = 0;
    virtual void SetVerPoText(const char * text) = 0;
    virtual void WrapShow() = 0;
    virtual void WrapClose() = 0;    
    virtual void Destroy() = 0;    
};
//---------------------------------------------------------------------------
#endif
