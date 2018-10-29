//---------------------------------------------------------------------------
#ifndef Unit_85Old_mainH
#define Unit_85Old_mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <ExtCtrls.hpp>
#include <DBGrids.hpp>
#include <DBCtrls.hpp>
#include <dbcgrids.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------
class TForm_85Old_Main : public TForm
{
  private:
    void __fastcall OnWMSysCommand( TMessage& aMsg );
  public:
    BEGIN_MESSAGE_MAP
      MESSAGE_HANDLER( WM_SYSCOMMAND, TMessage, OnWMSysCommand );
    END_MESSAGE_MAP( TComponent )
    
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TButton *OpenPortButton;
        TEdit *IndAdrEdit;
        TGroupBox *DataFromDetGroupBox;
        TPanel *IndAdrPanel;
        TPanel *ParamColPanel;
        TPanel *GrpAdrPanel;
        TPanel *CodeColPanel;
        TEdit *GrpAdrEdit;
        TPanel *TprPanel;
        TPanel *UhiIPanel;
        TPanel *DNUIPanel;
        TEdit *TprCodeEdit;
        TEdit *UhiICodeEdit;
        TEdit *DNUICodeEdit;
        TPanel *ValueCodePanel;
        TEdit *TprEdit;
        TEdit *UhiIEdit;
        TEdit *DNUIEdit;
        TPanel *UnitPanel;
        TEdit *TprUnitEdit;
        TEdit *UhiIUnitEdit;
        TEdit *DNUIUnitEdit;
        TPanel *EmptyPanel01;
        TPanel *EmptyPanel02;
        TPanel *EmptyPanel07;
        TPanel *EmptyPanel08;
        TGroupBox *DataForDetBox;
        TMaskEdit *SetDNUEdit;
        TPanel *SetIndAdrPanel;
        TPanel *SetGrpAdrPanel;
        TPanel *SetDNUPanel;
        TPanel *SetUhiPanel;
        TPanel *SetParamColPanel;
        TPanel *SetCodeColPanel;
        TPanel *SetValueColPanel;
        TMaskEdit *SetUhiEdit;
        TEdit *SetIndAdrEdit;
        TEdit *SetGrpAdrEdit;
        TEdit *SetDNUCodeEdit;
        TEdit *SetUhiCodeEdit;
        TPanel *EmptyPanel09;
        TPanel *EmptyPanel10;
        TLabel *COMLabel;
        TButton *SetParamButton;
        TGroupBox *GroupBox2;
        TPanel *SumCountPanel;
        TPanel *TCountPanel;
        TPanel *EmptyPanel05;
        TPanel *EmptyPanel06;
        TEdit *SumCountEdit;
        TEdit *TCountEdit;
        TEdit *SumCountUnitEdit;
        TEdit *TCountUnitEdit;
        TEdit *T_LimitEdit;
        TButton *SetResetButton;
        TButton *StartCountButton;
        TLabel *Label3;
        TPanel *Panel1;
        TEdit *EditSIMd;
        TEdit *Edit2;
        TPanel *Panel3;
        TPanel *Panel4;
        TPanel *Panel5;
        TEdit *Edit1;
        TEdit *Edit3;
        TPanel *Count1Panel;
        TPanel *EmptyPanel04;
        TEdit *Count1Edit;
        TEdit *Count1UnitEdit;
        TButton *Button5;
        TPanel *Panel13;
        TPanel *Panel33;
        TPanel *Panel6;
        TPanel *Panel8;
        TPanel *Panel9;
        TPanel *Panel10;
        TLabel *Label4;
        TEdit *Edit7;
        TEdit *Edit11;
        TEdit *Edit12;
        TEdit *Edit13;
        TPanel *Panel11;
        TEdit *Edit5;
        TUpDown *UpDown1;
        TPanel *Panel12;
        TPanel *Panel28;
        TEdit *Edit6;
        TEdit *Edit18;
        TPanel *Panel14;
        TPanel *Panel29;
        TEdit *Edit8;
        TEdit *Edit19;
        TGroupBox *GroupBox7;
        TRadioButton *RS1;
        TRadioButton *RS3;
        TPanel *Panel7;
        TPanel *Panel15;
        TEdit *EditSIMp;
        TEdit *EditSIM3zn;
        TEdit *Edit9;
        TEdit *NewConnectionAdr;
        TLabel *Label2;
        TUpDown *UpDown3;
        TPanel *Panel17;
        TLabel *Label5;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label8;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TEdit *Edit4;
        TLabel *Label15;
        TLabel *Label16;
        TEdit *Edit23;
        TLabel *Label17;
        TEdit *Edit10;
        TPanel *Panel2;
        TBitBtn *ARCH_Con;
        TLabel *Label1;
        TLabel *Label18;
        TPanel *Panel16;
        TPanel *Panel18;
        TEdit *Edit14;
        TEdit *Edit15;
        TPanel *Panel19;
        TEdit *Edit16;
        TPanel *Panel20;
        TEdit *Edit17;
        void __fastcall OpenPortButtonClick(TObject *Sender);
        void __fastcall MainCycle(void);
        void __fastcall SetParamButtonClick(TObject *Sender);
        float __fastcall TConvert(int Temper);
        void __fastcall Init(void);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall StartCountButtonClick(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall SetResetButtonClick(TObject *Sender);

private:	// User declarations
        void  ClearForm(void);
        void /*Form_85Old_Main::*/ZapEEPROM(void);
        bool FlagZap;
public:		// User declarations
      unsigned char Versia[4];
        unsigned long IndAdrZ;   // Индивидуальный адрес заданный
        unsigned long GrpAdrZ;   // Групповой адрес заданный
        unsigned long DNUZ;      // Значение дискриминатора нижнего уровня заданное
        unsigned long UhiZ;      // Напряжение высокое заданное
        unsigned char IndAdr;    // Индивидуальный адрес полученный
        unsigned char GrpAdr;    // Групповой адрес полученный
        unsigned int Tpr;        // Температура процессора измеренная
        unsigned int TprSred;        // Температура процессора измеренная
        unsigned int UhiI;       // Напряжение высокое измеренное
        unsigned int DNUI;       // Значение дискриминатора нижнего уровня измеренное
        float DNUZZnach;
        unsigned int SIM3,SIM4;        //Значение ШИМ из БД
        unsigned long SIMstart,SIMmax;
        unsigned int AmpSpectr;  // Амплитуда импульса спектра
        unsigned int Schet02,Count02;    // Счет с БД за 0,2 сек
        unsigned int Sred02;     // Среднее с БД за 0,2 сек
        unsigned int TSchet;     // Текущее время счета импульсов
        unsigned int SumSchet;   // Суммарное время счета импульсов
        unsigned char PSW;       // Слово состояния программы БД
        unsigned char TimeInt,Date; 

        unsigned int count;       // Счетчик 200 мсек интервалов
        unsigned int T_Limit; // Время счета импульсов
        unsigned int flagFirst;   // Флаг обновления данных (делитель времени 1)
        unsigned int flagSecond;  // Флаг обновления данных (делитель времени 2)
        unsigned int flagThird;   // Флаг обновления данных (делитель времени 3)
        bool flagRefresh;    // Флаг необходимости обновить данные

        bool bFlagCount;    // Флаг вкл/откл режима счета импульсов
        bool bFlgEnd;
        bool bRecordEn;
        unsigned int uiRecNum;
        unsigned long ulRecCount;
        bool bFlagWork;      // Флаг режима измерения включен/отключен
        bool FlagZapis;
        unsigned char KodRS,KodRSzap;
        bool KodVxod;
        __fastcall TForm_85Old_Main(TComponent* Owner);
private:
    bool CreateFormFlag_BD85_Old;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_85Old_Main *Form_85Old_Main;
     
//---------------------------------------------------------------------------
#endif
