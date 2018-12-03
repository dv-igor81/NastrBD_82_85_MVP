//---------------------------------------------------------------------------
#ifndef ModelSaveParamBd85H
#define ModelSaveParamBd85H
//---------------------------------------------------------------------------
#include "ViewModelSaveParamBd85.h"
#include "IAllProtokolS.h"
#include "ConnectBdProt.h"
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
//class
class ModelSaveParamBd85
{
public:
    ModelSaveParamBd85(
        IAllProtokolS * allProtokol,
        ViewModelSaveParamBd85 * vmSaveParam,
        ConnectBdProt * connectBdProt );
        
    ~ModelSaveParamBd85();

    AnsiString FileName;
    AnsiString FileHeader;
    
    int m_nT; // ����� ���������, (�)
    int m_nN; // ���������� ���������
    int m_nZ; // �������� (���)

    bool StartStopWork();
    int GetSummTime();

private:
    IAllProtokolS * _allProtokol;
    ViewModelSaveParamBd85 * _vmSaveParam;
    ConnectBdProt * _connectBdProt;

    void CreateActions(); // ������� ��������
    void DestroyActions(); // ���������� ������, �� ���������

    bool _isWork;

    //===>> ��������
    ActionSelf<> * as_OprosIter;
    void OprosIter();
    ActionSelf<const char*> * as_DisplayErrors;
    void DisplayErrors(const char * text);
    //<<===

    void StartWork();
    void StopWork();
    void ClearParam();
    void Calculate();

    unsigned char _ssp;

    unsigned short _scaling; // ���� �� ����������� (200 �� ��� 9-�������, 250 ��� ModBus)
    unsigned int _intervalQuantity; // ������� ���������� �������������, ��� ��������� (�������)
    unsigned int _intervalCounter;  // ������� ������������� (0,1,2,3 ��� 0,1,2,3,4) 
    unsigned int _scalingCounterTmp; // ��� ���������� �����
    unsigned int _scalingCounter; // ��� ���������� �����
    unsigned int _currTimeScaling; // ������� �����

};
//---------------------------------------------------------------------------
#endif
