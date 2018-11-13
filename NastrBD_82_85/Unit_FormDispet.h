//---------------------------------------------------------------------------
#ifndef Unit_FormDispetH
#define Unit_FormDispetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#define WM_BASE_App    (WM_USER + 0)
// Идентификатор сообщения-запроса
#define WM_DIA_ZAPROS  (WM_BASE_App + 0)
// Идентификатор сообщения-ответа
#define WM_DIA_OTVET   (WM_BASE_App + 1)
//---------------------------------------------------------------------------
#include "WindowLoader.h" // 29.10.2018
//---------------------------------------------------------------------------
class TFormDispet : public TForm, public IFormDispetView
{
__published:	// IDE-managed Components
        TRadioButton *RadioButton_BD82;
        TButton *Button_Initiate;
        TRadioButton *RadioButton_BD85New;
        TRadioButton *RadioButton_BD85Old;
        TTimer *Timer_Dispet;
        TButton *Button_Izmeneniya;
        TPanel *Panel_MessageBox;
        TRadioButton *RadioButton_BD84;
        void __fastcall Button_InitiateClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Timer_DispetTimer(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Button_IzmeneniyaClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
  int iFlagTimer;
  int iPanelLeft;
  int iPanelTop;
  int iPanelWidth;
  int iPanelHeight;
  int iFlagVyborFormy; // Флаг выбора формы

  unsigned int uiFlagApp; // Флаг приложения ( == 0 - Запущен единственный экземпляр приложения )
  HWND hWndFirst; // Описатель окна, для получения фокуса ввода (полученный через указатель "this")
  HWND hWndSecond; // Описатель окна, полученный через параметр "wParam"
  void __fastcall funkZapros( TMessage & Message ); // Функция обработки сообщения-запроса
  void __fastcall funkOtvet( TMessage & Message ); // Функция обработки сообщения-ответа
  //void __fastcall OnWMSysCommand( TMessage& Message ); // Функция обработки ...

  WindowLoader viewLoader; // 29.10.2018
  AnsiString ProgrammVersion;
  AnsiString FormCaption;
public:		// User declarations
  __fastcall TFormDispet(TComponent* Owner);
  int __fastcall DiaGetWinHandle( HWND hWnd ); // Изменяет описатель окна
  const char * GetProgrammVersion();
  void WrapShow(); 

  ATOM aApp;
  char * szAppName;
  char szCaptionMess[40];
  char szTextMess[100];

  BEGIN_MESSAGE_MAP
    MESSAGE_HANDLER( WM_DIA_ZAPROS, TMessage, funkZapros )
    MESSAGE_HANDLER( WM_DIA_OTVET, TMessage, funkOtvet )
    //MESSAGE_HANDLER( WM_SYSCOMMAND, TMessage, OnWMSysCommand );
  END_MESSAGE_MAP( TComponent )
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDispet *FormDispet;
//---------------------------------------------------------------------------
#endif
