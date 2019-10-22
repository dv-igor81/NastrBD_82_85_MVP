object Window_Updater: TWindow_Updater
  Left = 583
  Top = 257
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsDialog
  Caption = #1054#1073#1085#1086#1074#1083#1077#1085#1080#1077
  ClientHeight = 202
  ClientWidth = 574
  Color = clBtnFace
  Constraints.MaxHeight = 240
  Constraints.MaxWidth = 590
  Constraints.MinHeight = 240
  Constraints.MinWidth = 590
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label_Display: TLabel
    Left = -3
    Top = 8
    Width = 500
    Height = 29
    Alignment = taCenter
    AutoSize = False
    Caption = 'Label_Display'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object Label_Count: TLabel
    Left = 189
    Top = 43
    Width = 105
    Height = 29
    Alignment = taCenter
    AutoSize = False
    Caption = '---'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object Label_VersiyaPo: TLabel
    Left = 158
    Top = 83
    Width = 169
    Height = 29
    Alignment = taCenter
    AutoSize = False
    Caption = '---'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object Button_Reset: TButton
    Left = 8
    Top = 72
    Width = 105
    Height = 25
    Caption = #1057#1073#1088#1086#1089' '#1089#1095#1105#1090#1095#1080#1082#1072
    Enabled = False
    TabOrder = 0
    OnClick = Button_ResetClick
  end
  object Panel_Display: TPanel
    Left = 0
    Top = 0
    Width = 574
    Height = 202
    Align = alClient
    AutoSize = True
    BevelInner = bvRaised
    BevelOuter = bvLowered
    Caption = '}==='#1054#1073#1085#1086#1074#1083#1077#1085#1080#1077'==={'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Times New Roman'
    Font.Style = [fsItalic]
    ParentFont = False
    TabOrder = 1
  end
  object Timer: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = TimerTimer
    Left = 16
    Top = 8
  end
end
