object FormDispet: TFormDispet
  Left = 580
  Top = 350
  BorderStyle = bsDialog
  Caption = '--- '#1085#1072#1076#1087#1080#1089#1100' '#1092#1086#1088#1084#1080#1088#1091#1077#1090#1089#1103' '#1085#1072' '#1101#1090#1072#1087#1077' '#1074#1099#1087#1086#1083#1085#1077#1085#1080#1103' ---'
  ClientHeight = 123
  ClientWidth = 393
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object RadioButton_BD82: TRadioButton
    Left = 11
    Top = 11
    Width = 86
    Height = 17
    Caption = #1041#1044' 82'
    TabOrder = 0
  end
  object RadioButton_BD_82_85: TRadioButton
    Left = 11
    Top = 92
    Width = 270
    Height = 17
    Caption = #1041#1044' '#1089#1080#1089#1090#1077#1084' '#1058#1057#1056#1052' 82/'#1058#1057#1056#1052' 85/'#1058#1057#1056#1052' 84 '#1080' '#1052#1077#1090#1088#1086
    TabOrder = 1
  end
  object Button_Initiate: TButton
    Left = 291
    Top = 92
    Width = 83
    Height = 25
    Caption = #1053#1072#1095#1072#1090#1100
    TabOrder = 2
    OnClick = Button_InitiateClick
  end
  object RadioButton_BD85New: TRadioButton
    Left = 11
    Top = 37
    Width = 310
    Height = 17
    Caption = #1041#1044' 85 '#1053#1086#1074#1099#1081' ('#1088#1077#1075#1091#1083#1080#1088#1086#1074#1082#1072' '#1076#1083#1080#1090#1077#1083#1100#1085#1086#1089#1090#1100#1102' '#1080' '#1087#1077#1088#1080#1086#1076#1086#1084')'
    TabOrder = 3
  end
  object RadioButton_BD85Old: TRadioButton
    Left = 11
    Top = 65
    Width = 254
    Height = 17
    Caption = #1041#1044' 85 '#1057#1090#1072#1088#1099#1081' ('#1088#1077#1075#1091#1083#1080#1088#1086#1074#1082#1072' '#1076#1083#1080#1090#1077#1083#1100#1085#1086#1089#1090#1100#1102')'
    TabOrder = 4
  end
  object Button_Izmeneniya: TButton
    Left = 352
    Top = 0
    Width = 27
    Height = 25
    Caption = '?'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 5
    OnClick = Button_IzmeneniyaClick
  end
  object Panel_MessageBox: TPanel
    Left = 296
    Top = 0
    Width = 41
    Height = 41
    Caption = #1042#1099#1073#1077#1088#1080#1090#1077' '#1090#1080#1087' '#1087#1088#1086#1074#1077#1088#1082#1080
    Color = clGray
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -33
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 6
  end
  object RadioButton_BD84: TRadioButton
    Left = 131
    Top = 11
    Width = 78
    Height = 17
    Caption = #1041#1044' 84'
    TabOrder = 7
  end
  object Timer_Dispet: TTimer
    OnTimer = Timer_DispetTimer
    Left = 360
    Top = 48
  end
end
