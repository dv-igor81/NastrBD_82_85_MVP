//---------------------------------------------------------------------------
#ifndef WindowStartNastrBd85H
#define WindowStartNastrBd85H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
#include "WindowLoader.h"
//---------------------------------------------------------------------------
class TWindowStart : public TForm
{
__published:	// IDE-managed Components
        TButton *Button_Start;
        void __fastcall Button_StartClick(TObject *Sender);
private:	// User declarations
WindowLoader viewLoader;
public:		// User declarations
        __fastcall TWindowStart(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TWindowStart *WindowStart;
//---------------------------------------------------------------------------
#endif
