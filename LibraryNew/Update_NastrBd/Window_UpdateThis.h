//---------------------------------------------------------------------------
#ifndef Window_UpdateThisH
#define Window_UpdateThisH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
// MessServise * _mess;
//#include "Model_Funk_MessServise.h"
//---------------------------------------------------------------------------
// IniFiles * _ini;
//#include "Model_IniFiles.h"
//---------------------------------------------------------------------------
// TWriteSelf 
#include "Unit_WriteSelf.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TWindow_Updater : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label_Display;
        TTimer *Timer;
        TLabel *Label_Count;
        TButton *Button_Reset;
        TLabel *Label_VersiyaPo;
        TPanel *Panel_Display;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall TimerTimer(TObject *Sender);
        void __fastcall Button_ResetClick(TObject *Sender);
private:	// User declarations
    TWriteSelf _writeSelf;
    bool _bfTimerFirst;
    void Mess( AnsiString text, int Level );
    void Step_01();
    void Step_02();
    void Step_03();
    int _step;    
    int _bfDebuf;

    // Программа запущена из файл-сервера?
    bool ProgramStartFromFileServer();
public:		// User declarations
        __fastcall TWindow_Updater(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TWindow_Updater *Window_Updater;
//---------------------------------------------------------------------------
#endif
