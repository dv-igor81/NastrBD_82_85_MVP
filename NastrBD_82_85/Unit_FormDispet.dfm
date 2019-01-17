object FormDispet: TFormDispet
  Left = 580
  Top = 350
  BorderStyle = bsDialog
  Caption = '--- '#1085#1072#1076#1087#1080#1089#1100' '#1092#1086#1088#1084#1080#1088#1091#1077#1090#1089#1103' '#1085#1072' '#1101#1090#1072#1087#1077' '#1074#1099#1087#1086#1083#1085#1077#1085#1080#1103' ---'
  ClientHeight = 67
  ClientWidth = 338
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
  object RadioButton_BD82_84: TRadioButton
    Left = 11
    Top = 11
    Width = 86
    Height = 17
    Caption = #1041#1044' 82/84'
    TabOrder = 0
  end
  object Button_Initiate: TButton
    Left = 219
    Top = 4
    Width = 83
    Height = 25
    Caption = #1053#1072#1095#1072#1090#1100
    TabOrder = 1
    OnClick = Button_InitiateClick
  end
  object RadioButton_BD85New: TRadioButton
    Left = 11
    Top = 37
    Width = 102
    Height = 17
    Caption = #1041#1044' 85 '#1053#1086#1074#1099#1081
    TabOrder = 2
  end
  object Button_Izmeneniya: TButton
    Left = 306
    Top = 4
    Width = 27
    Height = 25
    Caption = '?'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    OnClick = Button_IzmeneniyaClick
  end
  object Panel_MessageBox: TPanel
    Left = 168
    Top = 8
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
    TabOrder = 4
  end
  object Timer_Dispet: TTimer
    OnTimer = Timer_DispetTimer
    Left = 224
    Top = 32
  end
end
