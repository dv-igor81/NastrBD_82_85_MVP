//---------------------------------------------------------------------------
#ifndef ScalingDataNewBd85H
#define ScalingDataNewBd85H
//---------------------------------------------------------------------------
class ScalingDataNewBd85
{
public:
    ScalingDataNewBd85( int timeLimitScaling );
    
    ScalingDataNewBd85(
        int timeLimitScaling
        , int currTimeScaling
        , double scalingCounterSumm
    );

    bool GetWorkScalingSumm(); // false - ��������� ������
    bool GetStartWorkScalingSumm(); // true - ������ ������
    const char* GetTimeMeteringLimit();
    const char* GetTimeScaling();
    const char* GetTotalScaling();
    const char* GetMiddleScaling();
private:
    enum { indAddrSize = 4
        , uShortTextSize = 7 // 6 ���� (�����������-��������� ����: 5 * 0xFFFF = 327675) � ����������� ����
        , floatTextSize = 10
        };
    bool _isWorkScalingSumm;
    bool _isStartWork;

    char _timeLimitScaling[uShortTextSize];
    char _currTimeScaling[uShortTextSize];
    char _scalingCounterSumm[floatTextSize];
    char _middleScaling[floatTextSize];

    void ClearText();
};
//---------------------------------------------------------------------------
#endif
