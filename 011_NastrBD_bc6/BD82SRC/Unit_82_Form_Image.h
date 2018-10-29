//---------------------------------------------------------------------------

#ifndef Unit_82_Form_ImageH
#define Unit_82_Form_ImageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
// DIA INC
#include <Clipbrd.hpp>
#include <axctrls.hpp>
#include <Jpeg.hpp>
//---------------------------------------------------------------------------
class TForm_Image : public TForm
{
__published:	// IDE-managed Components
        TImage *Image_Print;
private:	// User declarations
public:		// User declarations
        __fastcall TForm_Image(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Image *Form_Image;
//---------------------------------------------------------------------------
#endif
