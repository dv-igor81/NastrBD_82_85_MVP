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
class TWindowStart : public TForm, public IFormDispetView
{
__published:	// IDE-managed Components
        TButton *Button_Start;
        void __fastcall Button_StartClick(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// User declarations
    AnsiString ProgrammVersion;
    WindowLoader viewLoader;
    void SetVerPoText(const char * text);    
public:		// User declarations
        __fastcall TWindowStart(TComponent* Owner);
  const char * GetProgrammVersion();
  void WrapShow();         
};
//---------------------------------------------------------------------------
extern PACKAGE TWindowStart *WindowStart;
//---------------------------------------------------------------------------
#endif
