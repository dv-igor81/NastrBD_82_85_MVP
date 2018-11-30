//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Unit_FormDispet.cpp", FormDispet);
USEFORM("..\NastrBD_85_MVP\WindowMainNastrBd85.cpp", WindowMainBd85);
USEFORM("..\NastrBD_85_MVP\WindowStartNastrBd85.cpp", WindowStart);
USEFORM("..\011_NastrBD_bc6\Unit_Form_VersionInfo.cpp", Form_VersionInfo);
USEFORM("..\Library\Update_NastrBd\Window_UpdateThis.cpp", Window_Updater);
USEFORM("..\011_NastrBD_bc6\BD82SRC\Unit_82_Form_Start.cpp", Form_82_Start);
USEFORM("..\NastrBD_85_OLD\Unit_85Old_main.cpp", Form_85Old_Main);
USEFORM("..\NastrBD_85_OLD\Unit_85Old_Grafik.cpp", Form_85Old_GrafPoisson);
USEFORM("..\NastrBD_85_OLD\Unit_85Old_ProvPoisson.cpp", Form_85Old_Poisson);
USEFORM("..\011_NastrBD_bc6\BD82SRC\Unit_82_Form_Spectr.cpp", Form_82_Spectr_BD84);
USEFORM("..\011_NastrBD_bc6\BD82SRC\Unit_82_Form_Puasson8BD.cpp", FormPuasson8BD);
USEFORM("..\011_NastrBD_bc6\BD82SRC\Unit_82_Form_ARCH.cpp", Form_ARCH);
USEFORM("..\011_NastrBD_bc6\BD82SRC\Unit_82_Form_Puasson8BD_RepErr.cpp", FormPuasson8BDPepErr);
USEFORM("..\011_NastrBD_bc6\BD82SRC\Unit_82_Form_Graph.cpp", Form_Graph);
USEFORM("..\011_NastrBD_bc6\BD82SRC\Unit_82_Form_RearFromEEPROM.cpp", Form_RearFromEEPROM);
USEFORM("..\011_NastrBD_bc6\BD82SRC\Unit_82_Form_LoadParam.cpp", Form_LoadParam);
USEFORM("..\NastrBD_85_MVP\WindowSaveParamNastrBd85.cpp", WindowSaveParamBd85);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TWindow_Updater), &Window_Updater);
                 Application->CreateForm(__classid(TFormDispet), &FormDispet);
                 Application->CreateForm(__classid(TWindowStart), &WindowStart);
                 Application->CreateForm(__classid(TForm_VersionInfo), &Form_VersionInfo);
                 Application->CreateForm(__classid(TForm_85Old_Main), &Form_85Old_Main);
                 Application->CreateForm(__classid(TForm_82_Start), &Form_82_Start);
                 Application->CreateForm(__classid(TForm_85Old_GrafPoisson), &Form_85Old_GrafPoisson);
                 Application->CreateForm(__classid(TForm_85Old_Poisson), &Form_85Old_Poisson);
                 Application->CreateForm(__classid(TForm_82_Spectr_BD84), &Form_82_Spectr_BD84);
                 Application->CreateForm(__classid(TFormPuasson8BD), &FormPuasson8BD);
                 Application->CreateForm(__classid(TFormPuasson8BDPepErr), &FormPuasson8BDPepErr);
                 Application->CreateForm(__classid(TForm_Graph), &Form_Graph);
                 Application->CreateForm(__classid(TForm_ARCH), &Form_ARCH);
                 Application->CreateForm(__classid(TForm_RearFromEEPROM), &Form_RearFromEEPROM);
                 Application->CreateForm(__classid(TForm_LoadParam), &Form_LoadParam);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
