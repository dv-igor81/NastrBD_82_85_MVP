//---------------------------------------------------------------------------

#ifndef Unit_Form_VersionInfoH
#define Unit_Form_VersionInfoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm_VersionInfo : public TForm
{
__published:	// IDE-managed Components
        TRichEdit *RichEdit;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
        __fastcall TForm_VersionInfo(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_VersionInfo *Form_VersionInfo;
//---------------------------------------------------------------------------
#endif
