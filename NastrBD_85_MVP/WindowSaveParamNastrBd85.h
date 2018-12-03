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
#include <ExtCtrls.hpp>
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
        TPanel *Panel_ErrorConnectCount;
        TEdit *Edit_ErrorConnectCount;
        TPanel *Panel_SummTime;
        TEdit *Edit_SummTime;
        TPanel *Panel_CurrTime;
        TEdit *Edit_CurrTime;
        TPanel *Panel_Info;
        TEdit *Edit_Info;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Edit_FileNameChange(TObject *Sender);
        void __fastcall Edit_FileHeaderChange(TObject *Sender);
        void __fastcall Edit_TimeChange(TObject *Sender);
        void __fastcall Edit_NumberChange(TObject *Sender);
        void __fastcall Edit_DelayChange(TObject *Sender);
        void __fastcall Button_OkClick(TObject *Sender);
        void __fastcall Button_CancelClick(TObject *Sender);
private:	// User declarations
    BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER( WM_SYSCOMMAND, TMessage, OnWMSysCommand );
    END_MESSAGE_MAP( TComponent )
    void __fastcall OnWMSysCommand( TMessage& Message );

    ActionEvent<> ev_FormClose;
    ActionEvent<const char*> ev_EditFileNameChange;
    ActionEvent<const char*> ev_EditFileHeaderChange;
    ActionEvent<const char*> ev_EditTimeChange;
    ActionEvent<const char*> ev_EditNumberChange;
    ActionEvent<const char*> ev_EditDelayChange;
    ActionEvent<> ev_ButtonOkClick;
    ActionEvent<> ev_ButtonCancelClick;
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
    void SetButtonOkText(const char * text);
    void SetButtonCancelEnabled(bool enabled);
    void SetErrorText(const char * text);
    void SetSummTimeText(const char * text);
    void SetCurrTimeText(const char * text);
    void SetInfoText(const char * text);
    void WrapShow();
    void WrapClose();
    void Destroy();

    ActionEvent<>& EventFormClose();
    ActionEvent<const char*>& EventEditFileNameChange();
    ActionEvent<const char*>& EventEditFileHeaderChange();
    ActionEvent<const char*>& EventEditTimeChange();
    ActionEvent<const char*>& EventEditNumberChange();
    ActionEvent<const char*>& EventEditDelayChange();
    ActionEvent<>& EventButtonOkClick();
    ActionEvent<>& EventButtonCancelClick();
};
//---------------------------------------------------------------------------
#endif
