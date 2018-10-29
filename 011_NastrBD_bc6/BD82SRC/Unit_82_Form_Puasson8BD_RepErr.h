//---------------------------------------------------------------------------

#ifndef Unit_Form_Puasson8BD_RepErrH
#define Unit_Form_Puasson8BD_RepErrH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFormPuasson8BDPepErr : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox_main;
        TButton *Button_Clear;
        TMemo *Memo_main;
        void __fastcall Button_ClearClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormPuasson8BDPepErr(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPuasson8BDPepErr * FormPuasson8BDPepErr;
//---------------------------------------------------------------------------
#endif
