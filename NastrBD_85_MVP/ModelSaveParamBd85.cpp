//---------------------------------------------------------------------------
#pragma hdrstop
#include "ModelSaveParamBd85.h"
#include "ConvertHelper.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
ModelSaveParamBd85::ModelSaveParamBd85(
    IAllProtokolS * allProtokol,
    ViewModelSaveParamBd85 * vmSaveParam,
    ConnectBdProt * connectBdProt) : _omissionMax(100)
{
    _allProtokol = allProtokol;
    _vmSaveParam = vmSaveParam;
    _connectBdProt = connectBdProt;
    _isWork = false;
    m_nT = 0;
    m_nN = 0;
    m_nZ = 0;
    ClearParam();
    CreateActions(); // ??????? ????????
    *_allProtokol->GetEventErrorCountIncrement() += as_DisplayErrors;
}
//---------------------------------------------------------------------------
ModelSaveParamBd85::~ModelSaveParamBd85()
{
    DestroyActions(); // ?????????? ??????, ?? ?????????
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
void ModelSaveParamBd85::CreateActions() // ??????? ????????
{
    as_OprosIter = new ActionSelf<>(this, &ModelSaveParamBd85::OprosIter);
    as_DisplayErrors = new ActionSelf<const char*>(this, &ModelSaveParamBd85::DisplayErrors);
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::DestroyActions() // ?????????? ??????, ?? ?????????
{
    delete as_OprosIter;
    delete as_DisplayErrors;
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::OprosIter()
{
    Sleep(5);
    bool flag = _allProtokol->GetSsp( & _ssp );
    if ( flag == true )
    {
        if ( (_ssp & 0x01) == 0x01 ) // ???? ?????????? ????? ???????
        {
            _omission = 0;
            flag = _allProtokol->GetScaling( & _scaling );
            if ( flag == true )
            {
                Calculate();
            }
        }
        else
        {
            _omission++;
            if ( _omission > _omissionMax )
            {
                if ( _allProtokol->InitMkInBd() == true )
                {
                    _omission = 0;
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::DisplayErrors(const char * text)
{
    _vmSaveParam->DisplayErrorsInvoke( text );
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::StartWork()
{
    if ( GetSummTime() <= 0 )
    {
        return;
    }
    ClearParam();
    _vmSaveParam->DisplayCurrTimeInvoke( _currTimeScaling );       
    _connectBdProt->SetActionOprosIter( as_OprosIter );
    switch ( _allProtokol->GetProtokolName() )
    {
    case ProtokolName_t::NineBit: // 9-?? ??????
        _intervalQuantity = 5; // ?????????? ????????????? ? ???????
        break;
    case ProtokolName_t::ModBus_RTU: // ModBus RTU
    case ProtokolName_t::ModBus_TCP: // ModBus TCP
    case ProtokolName_t::ModBus_RTU_IP: // ModBus RTU (TCP/IP)
        _intervalQuantity = 4; // ?????????? ????????????? ? ???????
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
unsigned int ModelSaveParamBd85::GetSummTime()
{
    unsigned int summTime = m_nT * m_nN + m_nZ * 60 * (m_nN - 1);
    return summTime;
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::ClearParam()
{
    _scaling = 0; // ???? ?? ??????????? (200 ?? ??? 9-???????, 250 ??? ModBus)
    _intervalQuantity = 0; // ?????????? ?????????????, ??? ????????? (???????) (4 ???? 5)
    _intervalCounter = 0; // ??????? ????????????? (0,1,2,3 ??? 0,1,2,3,4)
    _scalingCounterTmp = 0; // ??? ?????????? ?????
    _scalingCounter = 0; // ??? ?????????? ?????
    _currTimeScaling = 0; // ??????? ?????
    _scalingSumm = 0; // ???? ?? ????? ?????????
    _bFlagCommentWritten = false;
    _temperature = 0;
    _voltageHi = 0;
    _widthPwm = 0;
    _periodPwm = 0;
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::Calculate()
{
    _intervalCounter++; // ??????? ?????????????
    _scalingCounterTmp += _scaling; // _scalingCounter - ??????? ?????????? ?????
    if ( _intervalCounter % _intervalQuantity == 0 )
    { // ?????? ??? 1 ???????
        _scalingCounter = _scalingCounterTmp;
        _scalingCounterTmp = 0;
        _intervalCounter = 0; // ??????? ?????????????
        if ( IsDelayTime() == false )
        {
            _scalingSumm += _scalingCounter;
        }
        _currTimeScaling++;
        _vmSaveParam->DisplayCurrTimeInvoke( _currTimeScaling );
        if ( _currTimeScaling >= GetSummTime() )
        {
            _vmSaveParam->ButtonOkClickInvoke(); // ???????? ?????????
            _vmSaveParam->DisplayInfoInvoke(""); // ???????? ???? ? ???????????
            _vmSaveParam->DisplayMiddleScalingInvoke(""); // ???????? ???? "??. ???? ? ?? ?? 1 ???."
            _vmSaveParam->DisplayTotalScalingInvoke(""); // ???????? ???? "????????? ???? ?? ????? ?????????"
            WriteToFile();
            _scalingSumm = 0;
            return;
        }
        DisplayInfo();
        if ( EndOfMetering() == true )
        {
            WriteToFile();
            _scalingSumm = 0;
        }
    }
}
//---------------------------------------------------------------------------
bool ModelSaveParamBd85::IsDelayTime() // ????? ???????? ???????
{
    unsigned int remainder = _currTimeScaling % ( m_nT + 60 * m_nZ );
    if ( remainder >= m_nT )
    { // ???? ?????, ? ?? ?????????
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
unsigned int ModelSaveParamBd85::NumberOfMetering()
{
    unsigned int quotient = _currTimeScaling / ( m_nT + 60 * m_nZ );
    return quotient + 1;
}
//---------------------------------------------------------------------------
unsigned int ModelSaveParamBd85::TimeOfMetering()
{ // ????? ??? ???????? ????????? (??? ????????)
    unsigned int time;
    unsigned int remainder = _currTimeScaling % ( m_nT + 60 * m_nZ );
    if ( remainder >= m_nT )
    {  // ???? ?????, ? ?? ?????????
        time = remainder - m_nT;
    }
    else
    { // ???? ?????????, ? ?? ?????
        time = remainder;
    }
    return time;
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::WriteToFile()
{
    int nFile1;
    //int nFile2;
    if ( FileExists( FileName ) )
    {
        nFile1 = FileOpen( FileName , fmOpenWrite );
    }
    else
    {
        nFile1 = FileCreate( FileName );
    }
    if ( nFile1 != -1 )
    {
        FileSeek( nFile1, 0, 2 ); // ??????????? "????????? - ??????" ? ????? ?????
        if ( _bFlagCommentWritten == false )
        {
            TDateTime Td(Now() );
            AnsiString sdate = Td.DateString();
            double Vremq = (float)GetSummTime();
            Vremq /= 60.0;
            char acBuffer[1024] = { 0 };
            sprintf(acBuffer, "\r\n????:%s  ???????????:%s\r\n?????????: %d ?? %d? (????? ?????????????????:%6.2f???) c ????????? %d ??? ????? ???????????\r\n",
                sdate,
                FileHeader.c_str(),
                m_nN,
                m_nT,
                Vremq,
                m_nZ);
            FileWrite( nFile1, (void*)acBuffer, strlen(acBuffer) );
            sprintf(acBuffer, " ?????      ??????.  ???????,?   ?????    ??????      ????\r\n");
            FileWrite( nFile1, (void*)acBuffer, strlen(acBuffer) );
            _bFlagCommentWritten = true;            
        }
        char acBuffer[1024] = { 0 };
        //===>>
        TDateTime T( Now() );
        //AnsiString sdate = T.DateString();
        AnsiString stime = T.TimeString();
        int n = stime.AnsiPos(':');
        if (n == 2)
        {
            stime.Insert(' ', 1);
        }
        bool flagGood = true;
        flagGood &= _allProtokol->GetTemperature( & _temperature );
        double temperVal = ConvertHelper::TemperatureCodeToValue( _temperature );
        flagGood &= _allProtokol->GetVoltageHi( & _voltageHi );
        double voltageHiVal = ConvertHelper::VoltageHiCodeToValue( _voltageHi );
        flagGood &= _allProtokol->GetWidthPwm( & _widthPwm );
        flagGood &= _allProtokol->GetPeriodPwm( & _periodPwm );

        if ( flagGood == true )
        {
            sprintf(acBuffer, "%s  %8.1f  %8.1f  %8d  %8d  %8d\r\n",
                stime.c_str(), // ?????
                temperVal, // ???????????
                voltageHiVal, // ??????? ??????????
                _widthPwm, // ???????????? ??? (???)
                _periodPwm, // ?????? ??? (???)
                _scalingSumm); // ???? ?? ???????? ?????
            FileWrite( nFile1, (void*)acBuffer, strlen(acBuffer) );
        }
        //<<===
        FileClose( nFile1 );
    }
    else
    {
        //ShowMessage( "?????? ??????? ? ?????: " + FileName );
    }
}
//---------------------------------------------------------------------------
void ModelSaveParamBd85::DisplayInfo()
{
    char * str;
    char text1[50];
    char text2[12];
    char text3[12];
    if ( IsDelayTime() )
    {
        str = "?????";
    }
    else
    {
        str = "?????.";
    }
    int q = NumberOfMetering(); // ????? ?????????
    int t = TimeOfMetering(); // ????? ??? ???????? ????????? ??? ????? 
    sprintf( text1, "%s ? %d (%d ???.)", str, q, t );
    _vmSaveParam->DisplayInfoInvoke( text1 );


    double dblScalingSumm = _scalingSumm;
    if ( EndOfMetering() == true )
    {
        dblScalingSumm /= m_nT;
        sprintf( text2, "%0.2f", dblScalingSumm ); // ??????? ???? ?? 1 ???.
        sprintf( text3, "%d", _scalingSumm ); // ????????? ???? ?? ????? ?????????
        _vmSaveParam->DisplayMiddleScalingInvoke( text2 );
        _vmSaveParam->DisplayTotalScalingInvoke( text3 );
    }
    if ( IsDelayTime() == false ) // ????? ????????? (? ?? ?????)
    {
        unsigned int timeMet = TimeOfMetering();
        if ( timeMet != 0 )
        {
            dblScalingSumm /= timeMet;
            sprintf( text2, "%0.2f", dblScalingSumm ); // ??????? ???? ?? 1 ???.
            sprintf( text3, "%d", _scalingSumm ); // ????????? ???? ?? ????? ?????????
            _vmSaveParam->DisplayMiddleScalingInvoke( text2 );
            _vmSaveParam->DisplayTotalScalingInvoke( text3 );
        }
    }
}
//---------------------------------------------------------------------------
bool ModelSaveParamBd85::EndOfMetering()
{
    unsigned int remainder = _currTimeScaling % ( m_nT + 60 * m_nZ );
    if ( ( remainder == 0 && m_nZ == 0 ) || ( remainder == m_nT && m_nZ != 0 ) )
    { // ??????????? ?????????
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------




