//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("WindowStartNastrBd85.cpp", WindowStart);
USEFORM("WindowMainNastrBd85.cpp", WindowMainBd85);
USEFORM("WindowSaveParamNastrBd85.cpp", WindowSaveParamBd85);
USEFORM("WindowNastrBd85Poisson.cpp", WindowBd85Poisson);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TWindowStart), &WindowStart);
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
