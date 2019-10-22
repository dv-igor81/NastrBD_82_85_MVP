//---------------------------------------------------------------------------
#ifndef ICodeValueTextBoxNumberH
#define ICodeValueTextBoxNumberH
//---------------------------------------------------------------------------
#include "ActionEvent.h"
using namespace smarteventsMin;
//---------------------------------------------------------------------------
class ICodeValueTextBoxNumber
{
public: // �����-����������� ������
    // ������� ���������� �����, � ������� ������� ���� "���"
    virtual void TextBoxCodeChange(const char * text, int pos) = 0;
    // ������� ���������� �����, � ������� ������� ���� "��������"
    virtual void TextBoxValueChange(const char * text, int pos) = 0;
    // ���������� �������� "���", � ���������� "���" � "��������" � ��������� � �������� �����
    virtual void SetCode(int code) = 0;
    // ���������� �������� "����", ����� �������� "��������", � ���������� "���" �  "��������"
    virtual void SetValue(double value) = 0;
    // �������� ������������ �������� "���"
    virtual int GetCode() = 0;
    // �������� ������������ �������� "��������"
    virtual double GetValue() = 0;
    // ���������� Value �� ������ Code � ������������
    virtual void RecountVelue() = 0;
    // ������, ������������-�� ���������� �����
    virtual bool IsNumber() = 0;
    // ���������� ������, ���������� ����������� ������
    virtual void Destroy() = 0;
};
//---------------------------------------------------------------------------
ICodeValueTextBoxNumber * CreateTextBoxNumber( // ������� ��������� ������: ITextBoxNumber
    int minCode, // ����������-��������� �������� "����"
    int maxCode, // �����������-��������� �������� "����"
    int defCode, // �������� "����" �� ���������
    int digits, // ������ ��� ���-�� ������, ����� ������� � ���� "��������"
    double codeToValue, // ����������� ��������� "����" � "��������"
    ActionSelf<const char*> * setTextCode, // ������� ��������� ������ ���� "���"
    ActionSelf<const char*> * setTextValue, // ������� ��������� ������ ���� "��������"
    ActionSelf<int> * setCursorCode, // ������� ��������� ������� � ���� "���"
    ActionSelf<int> * setCursorValue // ������� ��������� ������� � ���� "��������"
);
//---------------------------------------------------------------------------
// ���������� ������, ���������� ����������� ������: ITextBoxNumber
void DestroyTextBoxNumber( ICodeValueTextBoxNumber * number );
   //DestroyTextBoxNumber
//---------------------------------------------------------------------------
#endif
