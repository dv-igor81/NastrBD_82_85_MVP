//---------------------------------------------------------------------------
#pragma hdrstop
#include "EepromModBusBd85Settings.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
 // 2) ����������, ��
const unsigned short EepromModBusBd85Settings::ExpositionDefault = 250;
 // 3) ����������� ����
const unsigned short EepromModBusBd85Settings::MinimumCountDefault = 10;
// 4) ������������ ����                                                                                               1
const unsigned short EepromModBusBd85Settings::MaximumCountDefault = 1000;
 // 5) ������� ����������
const unsigned short EepromModBusBd85Settings::LevelOfOverloadDefault = 10000;
// 6) ���-�� ����������
const unsigned short EepromModBusBd85Settings::QuantityOfIntervalDefault = 8;
// 7) ���-�� ������� �����
const unsigned short EepromModBusBd85Settings::QuantityOfLookDefault = 4;
// 8) ������� ������� 1 * 10
const unsigned short EepromModBusBd85Settings::LevelOfAlarm1Default = 80;
// 9) ������� ������� 2 * 10
const unsigned short EepromModBusBd85Settings::LevelOfAlarm2Default = 800;
 // 10) ������� ������� 3 * 30
const unsigned short EepromModBusBd85Settings::LevelOfAlarm3Default = 8000;
// 11) ���, �
const unsigned short EepromModBusBd85Settings::PhonDefault = 100;
 // 12) ����. ������������ ����, ��
const unsigned short EepromModBusBd85Settings::DurationOfPhonDefault = 1000;
// 13) ����. ������� �������, �
const unsigned short EepromModBusBd85Settings::DurationOfAlarmDefault = 7;
 // 14) ����. ������� �����
const unsigned short EepromModBusBd85Settings::DurationOfVideoDefault = 7;
//---------------------------------------------------------------------------
void EepromModBusBd85Settings::Copy( EepromModBusBd85Settings & data )
{
    NumberOfBd = data.NumberOfBd; // 1) ����� ��
    Exposition = data.Exposition; // 2) ����������, ��
    MinimumCount = data.MinimumCount; // 3) ����������� ����
    MaximumCount = data.MaximumCount; // 4) ������������ ����
    LevelOfOverload = data.LevelOfOverload; // 5) ������� ����������
    QuantityOfInterval = data.QuantityOfInterval; // 6) ���-�� ����������
    QuantityOfLook = data.QuantityOfLook; // 7) ���-�� ������� �����
    LevelOfAlarm1 = data.LevelOfAlarm1; // 8) ������� ������� 1 * 10
    LevelOfAlarm2 = data.LevelOfAlarm2; // 9) ������� ������� 2 * 10
    LevelOfAlarm3 = data.LevelOfAlarm3; // 10) ������� ������� 3 * 10
    Phon = data.Phon; // 11) ���, �
    DurationOfPhon = data.DurationOfPhon; // 12) ����. ������������ ����, ��
    DurationOfAlarm = data.DurationOfAlarm; // 13) ����. ������� �������, �
    DurationOfVideo = data.DurationOfVideo; // 14) ����. ������� �����, �
}
//---------------------------------------------------------------------------
bool EepromModBusBd85Settings::NotEqual( EepromModBusBd85Settings & data )
{
    bool flagEqual = true;
    // ��������, ���� ��� ���� �� ������������
    MarkIfNotEqual( flagEqual, NumberOfBd, data.NumberOfBd ); // 1) ����� ��
    MarkIfNotEqual( flagEqual, Exposition, data.Exposition ); // 2) ����������, ��
    MarkIfNotEqual( flagEqual, MinimumCount, data.MinimumCount ); // 3) ����������� ����
    MarkIfNotEqual( flagEqual, MaximumCount, data.MaximumCount ); // 4) ������������ ����
    MarkIfNotEqual( flagEqual, LevelOfOverload, data.LevelOfOverload ); // 5) ������� ����������
    MarkIfNotEqual( flagEqual, QuantityOfInterval, data.QuantityOfInterval ); // 6) ���-�� ����������
    MarkIfNotEqual( flagEqual, QuantityOfLook, data.QuantityOfLook ); // 7) ���-�� ������� �����
    MarkIfNotEqual( flagEqual, LevelOfAlarm1, data.LevelOfAlarm1 ); // 8) ������� ������� 1 * 10
    MarkIfNotEqual( flagEqual, LevelOfAlarm2, data.LevelOfAlarm2 ); // 9) ������� ������� 2 * 10
    MarkIfNotEqual( flagEqual, LevelOfAlarm3, data.LevelOfAlarm3 ); // 10) ������� ������� 3 * 10
    MarkIfNotEqual( flagEqual, Phon, data.Phon ); // 11) ���, �
    MarkIfNotEqual( flagEqual, DurationOfPhon, data.DurationOfPhon ); // 12) ����. ������������ ����, ��
    MarkIfNotEqual( flagEqual, DurationOfAlarm, data.DurationOfAlarm ); // 13) ����. ������� �������, �
    MarkIfNotEqual( flagEqual, DurationOfVideo, data.DurationOfVideo ); // 14) ����. ������� �����, �
    return !flagEqual;
}
//---------------------------------------------------------------------------
void EepromModBusBd85Settings::MarkIfNotEqual( bool & flagEqual, int arg1, int arg2  )
{
    flagEqual = flagEqual && ( arg1 == arg2 );
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
