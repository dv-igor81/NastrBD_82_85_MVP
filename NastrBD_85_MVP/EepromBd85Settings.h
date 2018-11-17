//---------------------------------------------------------------------------
#ifndef EepromBd85SettingsH
#define EepromBd85SettingsH
//---------------------------------------------------------------------------
class EepromBd85Settings
{
public:
    EepromBd85Settings();
    void Copy( EepromBd85Settings & data );
    bool NotEqual( EepromBd85Settings & data );

    static char VerPo[5];
    unsigned char IndAddrZad;
    unsigned char GroupAddrZad;
    unsigned short DnuZad;
    unsigned short VoltageHiZad;
    unsigned short WidthPwmZad;
    unsigned short OffsetPwmZad;
    unsigned short PeriodPwmZad;
    int FlagArch; // дыру Раз (1 --- true, -1 --- false)
private:
    void MarkIfNotEqual( bool & flagEqual, int arg1, int arg2 );
};
//---------------------------------------------------------------------------
#endif
