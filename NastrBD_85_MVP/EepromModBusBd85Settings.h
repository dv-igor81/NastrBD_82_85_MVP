//---------------------------------------------------------------------------
#ifndef EepromModBusBd85SettingsH
#define EepromModBusBd85SettingsH
//---------------------------------------------------------------------------
class EepromModBusBd85Settings
{
public:
    unsigned short NumberOfBd; // 1) Номер БД
    unsigned short Exposition; // 2) Экспозиция, мс
    unsigned short MinimumCount; // 3) Минимальный счёт
    unsigned short MaximumCount; // 4) Максимальный счёт
    unsigned short LevelOfOverload; // 5) Уровень перегрузки
    unsigned short QuantityOfInterval; // 6) Кол-во интервалов
    unsigned short QuantityOfLook;// 7) Кол-во взгляда после
    unsigned short LevelOfAlarm1; // 8) Уровень тревоги 1 * 10
    unsigned short LevelOfAlarm2; // 9) Уровень тревоги 2 * 10
    unsigned short LevelOfAlarm3; // 10) Уровень тревоги 3 * 10
    unsigned short Phon; // 11) Фон, с
    unsigned short DurationOfPhon; // 12) Длит. подинтервала фона, мс
    unsigned short DurationOfAlarm; // 13) Длит. сигнала тревоги, с
    unsigned short DurationOfVideo; // 14) Длит. сигнала видео

    void Copy( EepromModBusBd85Settings & data );
    bool NotEqual( EepromModBusBd85Settings & data );
    
private:
    static const unsigned short ExpositionDefault; // 2) Экспозиция, мс
    static const unsigned short MinimumCountDefault; // 3) Минимальный счёт
    static const unsigned short MaximumCountDefault; // 4) Максимальный счёт
    static const unsigned short LevelOfOverloadDefault; // 5) Уровень перегрузки
    static const unsigned short QuantityOfIntervalDefault; // 6) Кол-во интервалов
    static const unsigned short QuantityOfLookDefault;// 7) Кол-во взгляда после
    static const unsigned short LevelOfAlarm1Default; // 8) Уровень тревоги 1 * 10
    static const unsigned short LevelOfAlarm2Default; // 9) Уровень тревоги 2 * 10
    static const unsigned short LevelOfAlarm3Default; // 10) Уровень тревоги 3 * 10
    static const unsigned short PhonDefault; // 11) Фон, с
    static const unsigned short DurationOfPhonDefault; // 12) Длит. подинтервала фона, мс
    static const unsigned short DurationOfAlarmDefault; // 13) Длит. сигнала тревоги, с
    static const unsigned short DurationOfVideoDefault; // 14) Длит. сигнала видео

    void MarkIfNotEqual( bool & flagEqual, int arg1, int arg2  );
};
//---------------------------------------------------------------------------
#endif
