//---------------------------------------------------------------------------
#pragma hdrstop
#include "ModelSaveParamBd85.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
ModelSaveParamBd85::ModelSaveParamBd85(
    IAllProtokolS * allProtokol,
    ViewModelSaveParamBd85 * vmSaveParam,
    ConnectBdProt * connectBdProt)
{
    _allProtokol = allProtokol;
    _vmSaveParam = vmSaveParam;
    _connectBdProt = connectBdProt;
    _isWork = false;
    m_nT = 0;
    m_nN = 0;
    m_nZ = 0;
    ClearParam();
    CreateActions(); // ������� ��������
    *_allProtokol->GetEventErrorCountIncrement() += as_DisplayErrors;
}
//---------------------------------------------------------------------------
ModelSaveParamBd85::~ModelSaveParamBd85()
{
    DestroyActions(); // ���������� ������, �� ���������
}
//---------------------------------------------------------------------------
bool ModelSaveParamBd85::StartStopWork()
{
    if ( _isWork == false )
    {
        StartWork();
    }
    else
    {
        StopWork();    
    }
    return _isWork;
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::CreateActions() // ������� ��������
{
    as_OprosIter = new ActionSelf<>(this, &ModelSaveParamBd85::OprosIter);
    as_DisplayErrors = new ActionSelf<const char*>(this, &ModelSaveParamBd85::DisplayErrors);
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::DestroyActions() // ���������� ������, �� ���������
{
    delete as_OprosIter;
    delete as_DisplayErrors;
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::OprosIter()
{
    Sleep(5);
    if ( _allProtokol->GetSsp( & _ssp ) == false )
    {
        return;
    }
    if ( (_ssp & 0x01) != 0x01 ) // ���� ���������� ����� �� �������
    {
        return;
    }
    if ( _allProtokol->GetScaling( & _scaling ) == false )
    {
        return;
    }
    Calculate();
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::DisplayErrors(const char * text)
{
    _vmSaveParam->DisplayErrors( text );
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::StartWork()
{
    if ( GetSummTime() <= 0 )
    {
        return;
    }
    ClearParam();
    _vmSaveParam->DisplayCurrTime( _currTimeScaling );       
    _connectBdProt->SetActionOprosIter( as_OprosIter );
    switch ( _allProtokol->GetProtokolName() )
    {
    case ProtokolName_t::NineBit: // 9-�� ������
        _intervalQuantity = 5; // ���������� ������������� � �������
        break;
    case ProtokolName_t::ModBus_RTU: // ModBus RTU
    case ProtokolName_t::ModBus_TCP: // ModBus TCP
    case ProtokolName_t::ModBus_RTU_IP: // ModBus RTU (TCP/IP)
        _intervalQuantity = 4; // ���������� ������������� � �������
        break;
    }

    _isWork = true;
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::StopWork()
{
    _connectBdProt->SetActionOprosIter( 0 );
    _isWork = false;    
}
//---------------------------------------------------------------------------
int ModelSaveParamBd85::GetSummTime()
{
    int summTime = m_nT * m_nN + m_nZ * 60 * (m_nN - 1);
    return summTime;
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::ClearParam()
{
    _scaling = 0; // ���� �� ����������� (200 �� ��� 9-�������, 250 ��� ModBus)
    _intervalQuantity = 0; // ���������� �������������, ��� ��������� (�������) (4 ���� 5)
    _intervalCounter = 0; // ������� ������������� (0,1,2,3 ��� 0,1,2,3,4)
    _scalingCounterTmp = 0; // ��� ���������� �����
    _scalingCounter = 0; // ��� ���������� �����
    _currTimeScaling = 0; // ������� �����
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::Calculate()
{
    _intervalCounter++; // ������� �������������
    _scalingCounterTmp += _scaling; // _scalingCounter - ������� ���������� �����
    if ( _intervalCounter % _intervalQuantity == 0 )
    { // ������ 1 �������
        _currTimeScaling++;

        _vmSaveParam->DisplayCurrTime( _currTimeScaling );
        _scalingCounter = _scalingCounterTmp;
        _scalingCounterTmp = 0;
        _intervalCounter = 0; // ������� �������������
        if ( _currTimeScaling >= GetSummTime() )
        {
            _vmSaveParam->ButtonOkClick();
        }
    }
}


