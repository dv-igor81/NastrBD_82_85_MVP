//---------------------------------------------------------------------------
#pragma hdrstop
#include "StartDataNewBd85.h"
#include "TextHelper.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
StartDataNewBd85::StartDataNewBd85(
    const char* verPo)
{
    TextHelper::CopyText(_verPo, verPo, verPoSize);
}
//---------------------------------------------------------------------------
StartDataNewBd85::StartDataNewBd85()
{
    TextHelper::SpaseText(_verPo, verPoSize);  // ��������� ��� ������� ������ ���������
}
//---------------------------------------------------------------------------
const char* StartDataNewBd85::GetVerPo()
{
    return _verPo;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------