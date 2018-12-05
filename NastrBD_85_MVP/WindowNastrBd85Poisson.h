//---------------------------------------------------------------------------
#ifndef WindowNastrBd85PoissonH
#define WindowNastrBd85PoissonH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
#include "IViewBd85Poisson.h"
//---------------------------------------------------------------------------
class TWindowBd85Poisson : public TForm, public IViewBd85Poisson
{
__published:	// IDE-managed Components
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
    BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER( WM_SYSCOMMAND, TMessage, OnWMSysCommand );
    END_MESSAGE_MAP( TComponent )
    void __fastcall OnWMSysCommand( TMessage& Message );
    
    IViewModelBd85Poisson * _viewModel;
    void Initialization();
public:		// User declarations
        __fastcall TWindowBd85Poisson(TComponent* Owner);
    //===>> Реализация IViewBd85Poisson
    void SetViewModel( IViewModelBd85Poisson * viewModel );
    void SetVerPoText(const char * text);
    void WrapShow();
    void WrapClose();
    void Destroy();
    //<<=== Реализация IViewBd85Poisson
};
#endif
