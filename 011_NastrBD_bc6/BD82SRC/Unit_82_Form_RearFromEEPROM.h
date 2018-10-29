//---------------------------------------------------------------------------

#ifndef Unit_Form_RearFromEEPROMH
#define Unit_Form_RearFromEEPROMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TForm_RearFromEEPROM : public TForm
{
__published:	// IDE-managed Components
        TScrollBox *ScrollBox;
        TPanel *Panel_for_Scrolling;
        TStringGrid *StringGrid_small;
        TPanel *Panel_attrBD;
        TLabel *Label_attr_01;
        TLabel *Label_attr_02;
        TLabel *Label_attr_03;
        TLabel *Label_attr_04;
        TLabel *Label_attr_05;
        TLabel *Label_attr_06;
        TLabel *Label_attr_07;
        TLabel *Label_attr_08;
        TLabel *Label_attr_09;
        TLabel *Label_attr_10;
        TEdit *Edit_attr_01;
        TEdit *Edit_attr_02;
        TEdit *Edit_attr_03;
        TEdit *Edit_attr_04;
        TEdit *Edit_attr_05;
        TEdit *Edit_attr_06;
        TEdit *Edit_attr_07;
        TEdit *Edit_attr_08;
        TEdit *Edit_attr_09;
        TEdit *Edit_attr_10;
        TStringGrid *StringGrid_large;
        TLabel *Label_string_01;
        TLabel *Label_string_02;
        TLabel *Label_string_03;
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm_RearFromEEPROM(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_RearFromEEPROM *Form_RearFromEEPROM;
//---------------------------------------------------------------------------
#endif
