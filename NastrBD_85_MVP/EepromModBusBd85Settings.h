//---------------------------------------------------------------------------
#ifndef EepromModBusBd85SettingsH
#define EepromModBusBd85SettingsH
//---------------------------------------------------------------------------
class EepromModBusBd85Settings
{
public:
    unsigned short NumberOfBd; // 1) ����� ��
    unsigned short Exposition; // 2) ����������, ��
    unsigned short MinimumCount; // 3) ����������� ����
    unsigned short MaximumCount; // 4) ������������ ����
    unsigned short LevelOfOverload; // 5) ������� ����������
    unsigned short QuantityOfInterval; // 6) ���-�� ����������
    unsigned short QuantityOfLook;// 7) ���-�� ������� �����
    unsigned short LevelOfAlarm1; // 8) ������� ������� 1 * 10
    unsigned short LevelOfAlarm2; // 9) ������� ������� 2 * 10
    unsigned short LevelOfAlarm3; // 10) ������� ������� 3 * 10
    unsigned short Phon; // 11) ���, �
    unsigned short DurationOfPhon; // 12) ����. ������������ ����, ��
    unsigned short DurationOfAlarm; // 13) ����. ������� �������, �
    unsigned short DurationOfVideo; // 14) ����. ������� �����

    void Copy( EepromModBusBd85Settings & data );
    bool NotEqual( EepromModBusBd85Settings & data );
    
private:
    static const unsigned short ExpositionDefault; // 2) ����������, ��
    static const unsigned short MinimumCountDefault; // 3) ����������� ����
    static const unsigned short MaximumCountDefault; // 4) ������������ ����
    static const unsigned short LevelOfOverloadDefault; // 5) ������� ����������
    static const unsigned short QuantityOfIntervalDefault; // 6) ���-�� ����������
    static const unsigned short QuantityOfLookDefault;// 7) ���-�� ������� �����
    static const unsigned short LevelOfAlarm1Default; // 8) ������� ������� 1 * 10
    static const unsigned short LevelOfAlarm2Default; // 9) ������� ������� 2 * 10
    static const unsigned short LevelOfAlarm3Default; // 10) ������� ������� 3 * 10
    static const unsigned short PhonDefault; // 11) ���, �
    static const unsigned short DurationOfPhonDefault; // 12) ����. ������������ ����, ��
    static const unsigned short DurationOfAlarmDefault; // 13) ����. ������� �������, �
    static const unsigned short DurationOfVideoDefault; // 14) ����. ������� �����

    void MarkIfNotEqual( bool & flagEqual, int arg1, int arg2  );
};
//---------------------------------------------------------------------------
#endif
