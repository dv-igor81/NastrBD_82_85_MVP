//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("BD82SRC\Unit_82_Form_Graph.cpp", Form_Graph);
USEFORM("BD82SRC\Unit_82_Form_ARCH.cpp", Form_ARCH);
USEFORM("BD82SRC\Unit_82_Form_LoadParam.cpp", Form_LoadParam);
USEFORM("BD82SRC\Unit_82_Form_Puasson.cpp", Form_Puasson);
USEFORM("BD82SRC\Unit_82_Form_Puasson8BD.cpp", FormPuasson8BD);
USEFORM("BD82SRC\Unit_82_Form_Puasson8BD_RepErr.cpp", FormPuasson8BDPepErr);
USEFORM("BD82SRC\Unit_82_Form_RearFromEEPROM.cpp", Form_RearFromEEPROM);
USEFORM("BD82SRC\Unit_82_Form_Start.cpp", Form_82_Start);
USEFORM("BD82SRC\Unit_82_Form_Spectr.cpp", Form_82_Spectr_BD84);
USEFORM("BD82SRC\Unit_82_Form_Image.cpp", Form_Image);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->HelpFile = "";
                 Application->CreateForm(__classid(TForm_82_Start), &Form_82_Start);
                 Application->CreateForm(__classid(TForm_ARCH), &Form_ARCH);
                 Application->CreateForm(__classid(TForm_Graph), &Form_Graph);
                 Application->CreateForm(__classid(TForm_LoadParam), &Form_LoadParam);
                 Application->CreateForm(__classid(TForm_Puasson), &Form_Puasson);
                 Application->CreateForm(__classid(TFormPuasson8BD), &FormPuasson8BD);
                 Application->CreateForm(__classid(TFormPuasson8BDPepErr), &FormPuasson8BDPepErr);
                 Application->CreateForm(__classid(TForm_RearFromEEPROM), &Form_RearFromEEPROM);
                 Application->CreateForm(__classid(TForm_Image), &Form_Image);
                 Application->CreateForm(__classid(TForm_82_Spectr_BD84), &Form_82_Spectr_BD84);
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
