//---------------------------------------------------------------------------
#ifndef WindowSaveParamNastrBd85H
#define WindowSaveParamNastrBd85H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
#include "IViewSaveParamBd85.h"
//---------------------------------------------------------------------------
class TWindowSaveParamBd85 : public TForm, public IViewSaveParamBd85
{
__published:	// IDE-managed Components
        TScrollBox *ScrollBox;
        TLabel *Label_FileName;
        TEdit *Edit_FileName;
        TLabel *Label_FileHeader;
        TEdit *Edit_FileHeader;
        TLabel *Label_Time;
        TEdit *Edit_Time;
        TLabel *Label_Number;
        TEdit *Edit_Number;
        TLabel *Label_Delay;
        TEdit *Edit_Delay;
        TButton *Button_Ok;
        TButton *Button_Cancel;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
    BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER( WM_SYSCOMMAND, TMessage, OnWMSysCommand );
    END_MESSAGE_MAP( TComponent )
    void __fastcall OnWMSysCommand( TMessage& Message );

    ActionEvent<> ev_FormClose;
public:		// User declarations
        __fastcall TWindowSaveParamBd85(TComponent* Owner);
    void SetVerPoText(const char * text);        
    void SetFileName(const char * fileName);
    void SetFileNameEnabled(bool enabled);
    void SetFileHeader(const char * fileHeader);
    void SetFileHeaderEnabled(bool enabled);
    void SetTimeText(const char * text);
    void SetTimeEnabled(bool enabled);
    void SetNumberText(const char * text);
    void SetNumberEnabled(bool enabled);
    void SetDelayText(const char * text);
    void SetDelayEnabled(bool enabled);
    void WrapShow();

    void Destroy();

    ActionEvent<>& EventFormClose();
};
//---------------------------------------------------------------------------
#endif
