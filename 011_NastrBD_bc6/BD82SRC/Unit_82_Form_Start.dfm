object Form_82_Start: TForm_82_Start
  Left = 904
  Top = 302
  AutoScroll = False
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1041#1044' 82 / '#1041#1044' 84 vX.XX'
  ClientHeight = 739
  ClientWidth = 889
  Color = clBtnFace
  Constraints.MinHeight = 240
  Constraints.MinWidth = 306
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl_ModBus_Settings: TPageControl
    Left = 0
    Top = 0
    Width = 889
    Height = 720
    ActivePage = TabSheet_Main
    Align = alClient
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    Style = tsButtons
    TabIndex = 0
    TabOrder = 0
    OnChange = PageControl_ModBus_SettingsChange
    object TabSheet_Main: TTabSheet
      Caption = '  '#1048#1085#1092#1086#1088#1084#1072#1094#1080#1103' '#1089' '#1041#1044'  '
      object ScrollBox_Tab1_Scrolling: TScrollBox
        Left = 0
        Top = 0
        Width = 881
        Height = 689
        Align = alClient
        TabOrder = 0
        object Label_bit7: TLabel
          Left = 608
          Top = 314
          Width = 38
          Height = 13
          Caption = #1044#1072#1090#1095#1080#1082
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object Label_bit7_2: TLabel
          Left = 595
          Top = 325
          Width = 64
          Height = 13
          Caption = #1087#1088#1080#1089#1091#1090#1089#1090#1074#1080#1103
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
        end
        object GroupBox_InfoFromBD_Display: TGroupBox
          Left = 4
          Top = 4
          Width = 449
          Height = 313
          Caption = '  '#1048#1085#1092#1086#1088#1084#1072#1094#1080#1103' '#1089' '#1041#1044'  '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
          object Panel_Col1_Row1: TPanel
            Left = 3
            Top = 15
            Width = 206
            Height = 20
            BevelInner = bvLowered
            Caption = #1055#1072#1088#1072#1084#1077#1090#1088
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
          end
          object Panel_Col2_Row1: TPanel
            Left = 211
            Top = 15
            Width = 77
            Height = 20
            BevelInner = bvLowered
            Caption = #1050#1054#1044
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 1
          end
          object Panel_Col3_Row1: TPanel
            Left = 290
            Top = 15
            Width = 80
            Height = 20
            BevelInner = bvLowered
            Caption = #1047#1085#1072#1095#1077#1085#1080#1077
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 2
          end
          object Panel_Col4_Row1: TPanel
            Left = 371
            Top = 15
            Width = 72
            Height = 20
            BevelInner = bvLowered
            Caption = #1045#1048
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 3
          end
          object Panel_Col4_Row2: TPanel
            Left = 371
            Top = 36
            Width = 72
            Height = 20
            BevelInner = bvLowered
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 4
          end
          object Panel_Col1_Row2: TPanel
            Left = 3
            Top = 36
            Width = 206
            Height = 20
            BevelInner = bvLowered
            Caption = #1048#1085#1076#1080#1074#1080#1076#1091#1072#1083#1100#1085#1099#1081' '#1072#1076#1088#1077#1089' '#1041#1044
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 5
          end
          object Panel_Col4_Row3: TPanel
            Left = 371
            Top = 57
            Width = 72
            Height = 20
            BevelInner = bvLowered
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 6
          end
          object Panel_Col2_Row3: TPanel
            Left = 211
            Top = 57
            Width = 77
            Height = 20
            BevelInner = bvLowered
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 7
          end
          object Panel_Col1_Row3: TPanel
            Left = 3
            Top = 57
            Width = 206
            Height = 20
            BevelInner = bvLowered
            Caption = #1043#1088#1091#1087#1087#1086#1074#1086#1081' '#1072#1076#1088#1077#1089' '#1041#1044
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 8
          end
          object Panel_Col1_Row4: TPanel
            Left = 3
            Top = 78
            Width = 206
            Height = 20
            BevelInner = bvLowered
            Caption = #1058#1077#1084#1087#1077#1088#1072#1090#1091#1088#1072' '#1087#1088#1086#1094#1077#1089#1089#1086#1088#1072
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 9
          end
          object Panel_Col1_Row5: TPanel
            Left = 3
            Top = 99
            Width = 206
            Height = 20
            BevelInner = bvLowered
            Caption = #1047#1085#1072#1095#1077#1085#1080#1077' '#1044#1053#1059' '#1080#1079#1084#1077#1088#1077#1085#1085#1086#1077
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 10
          end
          object Panel_Col1_Row6: TPanel
            Left = 3
            Top = 120
            Width = 206
            Height = 20
            BevelInner = bvLowered
            Caption = #1047#1085#1072#1095#1077#1085#1080#1077' '#1044#1042#1059' '#1080#1079#1084#1077#1088#1077#1085#1085#1086#1077
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 11
          end
          object Panel_Col1_Row7: TPanel
            Left = 3
            Top = 141
            Width = 206
            Height = 20
            BevelInner = bvLowered
            Caption = #1053#1072#1087#1088#1103#1078#1077#1085#1080#1077' '#1042#1067#1057#1054#1050#1054#1045' '#1080#1079#1084#1077#1088#1077#1085' ('#1087#1086' 50)'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 12
          end
          object Panel_Col1_Row9: TPanel
            Left = 3
            Top = 183
            Width = 206
            Height = 20
            BevelInner = bvLowered
            Caption = #1055#1077#1088#1080#1086#1076' '#1064#1048#1052' '#1080#1079#1084#1077#1088#1077#1085#1085#1099#1081
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 13
          end
          object Panel_Col3_Row10: TPanel
            Left = 290
            Top = 204
            Width = 80
            Height = 20
            BevelInner = bvLowered
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 14
          end
          object Panel_Col1_Row10: TPanel
            Left = 3
            Top = 204
            Width = 206
            Height = 20
            BevelInner = bvLowered
            Caption = #1058#1086#1082' '#1089#1074#1077#1090#1086#1076#1080#1086#1076#1072' '#1088#1072#1089#1089#1095#1080#1090#1072#1085#1085#1099#1081
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 15
          end
          object Panel_Col1_Row11: TPanel
            Left = 3
            Top = 225
            Width = 206
            Height = 20
            BevelInner = bvLowered
            Caption = #1054#1090#1082#1083#1080#1082' '#1089#1074#1077#1090#1086#1076#1080#1086#1076#1072' ('#1074#1086#1088#1086#1090#1072' = 5)'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 16
          end
          object Panel_Col1_Row12: TPanel
            Left = 3
            Top = 246
            Width = 206
            Height = 20
            BevelInner = bvLowered
            Caption = #1048#1079#1084#1077#1088#1077#1085'. '#1086#1090#1082#1083#1080#1082' '#1089#1074#1077#1090#1086#1076#1080#1086#1076#1072' ('#1087#1086' 150)'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 17
          end
          object Panel_Col2_Row13: TPanel
            Left = 211
            Top = 267
            Width = 77
            Height = 20
            BevelInner = bvLowered
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 18
          end
          object Panel_Col1_Row13: TPanel
            Left = 3
            Top = 267
            Width = 206
            Height = 20
            BevelInner = bvLowered
            Caption = #1057#1095#1105#1090' '#1089' '#1041#1044' '#1079#1072' 1 '#1089#1077#1082'.'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 19
          end
          object Panel_Col1_Row8: TPanel
            Left = 3
            Top = 162
            Width = 206
            Height = 20
            BevelInner = bvLowered
            Caption = #1044#1083#1080#1090#1077#1083#1100#1085#1086#1089#1090#1100' '#1080#1084#1087#1091#1083#1100#1089#1072' '#1064#1048#1052
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 20
          end
          object Edit_Col2_Row4: TEdit
            Left = 211
            Top = 78
            Width = 77
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 21
          end
          object Edit_Col2_Row5: TEdit
            Left = 211
            Top = 99
            Width = 77
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 22
          end
          object Edit_Col2_Row6: TEdit
            Left = 211
            Top = 120
            Width = 77
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 23
          end
          object Edit_Col2_Row7: TEdit
            Left = 211
            Top = 141
            Width = 77
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 24
          end
          object Edit_Col2_Row8: TEdit
            Left = 211
            Top = 162
            Width = 77
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 25
          end
          object Edit_Col2_Row9: TEdit
            Left = 211
            Top = 183
            Width = 77
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 26
          end
          object Edit_Col2_Row10: TEdit
            Left = 211
            Top = 204
            Width = 77
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 27
          end
          object Edit_Col2_Row11: TEdit
            Left = 211
            Top = 225
            Width = 77
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 28
          end
          object Edit_Col2_Row12: TEdit
            Left = 211
            Top = 246
            Width = 77
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 29
          end
          object Edit_Col3_Row2: TEdit
            Left = 290
            Top = 36
            Width = 80
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 30
          end
          object Edit_Col3_Row4: TEdit
            Left = 290
            Top = 78
            Width = 80
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 31
          end
          object Edit_Col3_Row5: TEdit
            Left = 290
            Top = 99
            Width = 80
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 32
          end
          object Edit_Col3_Row6: TEdit
            Left = 290
            Top = 120
            Width = 80
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 33
          end
          object Edit_Col3_Row7: TEdit
            Left = 290
            Top = 141
            Width = 80
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 34
          end
          object Edit_Col3_Row8: TEdit
            Left = 290
            Top = 162
            Width = 80
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 35
          end
          object Edit_Col3_Row9: TEdit
            Left = 290
            Top = 183
            Width = 80
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 36
          end
          object Edit_Col3_Row11: TEdit
            Left = 290
            Top = 225
            Width = 80
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 37
          end
          object Edit_Col3_Row12: TEdit
            Left = 290
            Top = 246
            Width = 80
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 38
          end
          object Edit_Col3_Row13: TEdit
            Left = 290
            Top = 267
            Width = 80
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 39
          end
          object Edit_Col4_Row4: TEdit
            Left = 371
            Top = 78
            Width = 72
            Height = 21
            Color = clMoneyGreen
            ReadOnly = True
            TabOrder = 40
            Text = '        '#176'C'
          end
          object Edit_Col4_Row5: TEdit
            Left = 371
            Top = 99
            Width = 72
            Height = 21
            Color = clMoneyGreen
            ReadOnly = True
            TabOrder = 41
            Text = '          '#1042'.'
          end
          object Edit_Col4_Row6: TEdit
            Left = 371
            Top = 120
            Width = 72
            Height = 21
            Color = clMoneyGreen
            ReadOnly = True
            TabOrder = 42
            Text = '          '#1042'.'
          end
          object Edit_Col4_Row7: TEdit
            Left = 371
            Top = 141
            Width = 72
            Height = 21
            Color = clMoneyGreen
            ReadOnly = True
            TabOrder = 43
            Text = '          '#1042'.'
          end
          object Edit_Col4_Row8: TEdit
            Left = 371
            Top = 162
            Width = 72
            Height = 21
            Color = clMoneyGreen
            ReadOnly = True
            TabOrder = 44
            Text = '        '#1084#1082#1089'.'
          end
          object Edit_Col4_Row9: TEdit
            Left = 371
            Top = 183
            Width = 72
            Height = 21
            Color = clMoneyGreen
            ReadOnly = True
            TabOrder = 45
            Text = '        '#1084#1082#1089'.'
          end
          object Edit_Col4_Row10: TEdit
            Left = 371
            Top = 204
            Width = 72
            Height = 21
            Color = clMoneyGreen
            ReadOnly = True
            TabOrder = 46
            Text = '         '#1077#1076'.'
          end
          object Edit_Col4_Row11: TEdit
            Left = 371
            Top = 225
            Width = 72
            Height = 21
            Color = clMoneyGreen
            ReadOnly = True
            TabOrder = 47
            Text = '          '#1042'.'
          end
          object Edit_Col4_Row12: TEdit
            Left = 371
            Top = 246
            Width = 72
            Height = 21
            Color = clMoneyGreen
            ReadOnly = True
            TabOrder = 48
            Text = '          '#1042'.'
          end
          object Edit_Col4_Row13: TEdit
            Left = 371
            Top = 267
            Width = 72
            Height = 21
            Color = clMoneyGreen
            ReadOnly = True
            TabOrder = 49
            Text = '   '#1080#1084#1087'./'#1089#1077#1082'.'
          end
          object Panel_Col2_Row2: TPanel
            Left = 211
            Top = 36
            Width = 77
            Height = 20
            BevelInner = bvLowered
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 50
          end
          object Edit_Col3_Row3: TEdit
            Left = 290
            Top = 57
            Width = 80
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 51
          end
          object Panel_Col1_Row14: TPanel
            Left = 3
            Top = 288
            Width = 206
            Height = 20
            BevelInner = bvLowered
            Caption = #1044#1086#1079#1072
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 52
          end
          object Panel_Col2_Row14: TPanel
            Left = 211
            Top = 288
            Width = 77
            Height = 20
            BevelInner = bvLowered
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 53
          end
          object Edit_Col3_Row14: TEdit
            Left = 290
            Top = 288
            Width = 80
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 54
          end
          object Edit_Col4_Row14: TEdit
            Left = 371
            Top = 288
            Width = 72
            Height = 21
            Color = clMoneyGreen
            ReadOnly = True
            TabOrder = 55
            Text = '     '#1084#1082#1047#1074'/'#1095
          end
        end
        object GroupBox_WriteSettings: TGroupBox
          Left = 4
          Top = 322
          Width = 448
          Height = 358
          Caption = '  '#1059#1089#1090#1072#1085#1086#1074#1082#1072' '#1087#1072#1088#1072#1084#1077#1090#1088#1086#1074' '#1041#1044'  '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
          object Label_SSP: TLabel
            Left = 40
            Top = 319
            Width = 98
            Height = 13
            Caption = #1057#1083#1086#1074#1086' '#1089#1086#1089#1090#1086#1103#1085#1080#1103
          end
          object Panel_2_Col1_Row1: TPanel
            Left = 3
            Top = 15
            Width = 205
            Height = 20
            BevelInner = bvLowered
            Caption = #1055#1072#1088#1072#1084#1077#1090#1088
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
          end
          object Panel_2_Col2_Row1: TPanel
            Left = 210
            Top = 15
            Width = 67
            Height = 20
            BevelInner = bvLowered
            Caption = #1050#1054#1044
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 1
          end
          object Panel_2_Col3_Row1: TPanel
            Left = 279
            Top = 15
            Width = 70
            Height = 20
            BevelInner = bvLowered
            Caption = #1047#1085#1072#1095#1077#1085#1080#1077
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 2
          end
          object Panel_2_Col4_Row1: TPanel
            Left = 350
            Top = 15
            Width = 92
            Height = 20
            BevelInner = bvLowered
            Caption = #1045#1048
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 3
          end
          object Panel_2_Col4_Row2: TPanel
            Left = 350
            Top = 36
            Width = 92
            Height = 20
            BevelInner = bvLowered
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 4
          end
          object Panel_2_Col1_Row2: TPanel
            Left = 3
            Top = 36
            Width = 205
            Height = 20
            BevelInner = bvLowered
            Caption = #1048#1085#1076#1080#1074#1080#1076#1091#1072#1083#1100#1085#1099#1081' '#1072#1076#1088#1077#1089' '#1041#1044
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 5
          end
          object Panel_2_Col4_Row3: TPanel
            Left = 350
            Top = 57
            Width = 92
            Height = 20
            BevelInner = bvLowered
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 6
          end
          object Panel_2_Col2_Row3: TPanel
            Left = 210
            Top = 57
            Width = 67
            Height = 20
            BevelInner = bvLowered
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 7
          end
          object Panel_2_Col1_Row3: TPanel
            Left = 3
            Top = 57
            Width = 205
            Height = 20
            BevelInner = bvLowered
            Caption = #1043#1088#1091#1087#1087#1086#1074#1086#1081' '#1072#1076#1088#1077#1089' '#1041#1044
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 8
          end
          object Panel_2_Col1_Row4: TPanel
            Left = 3
            Top = 78
            Width = 205
            Height = 20
            BevelInner = bvLowered
            Caption = #1047#1085#1072#1095#1077#1085#1080#1077' '#1044#1053#1059' '#1079#1072#1076#1072#1085#1085#1086#1077'*'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 9
          end
          object Panel_2_Col1_Row5: TPanel
            Left = 3
            Top = 99
            Width = 205
            Height = 20
            BevelInner = bvLowered
            Caption = #1047#1085#1072#1095#1077#1085#1080#1077' '#1044#1042#1059' '#1079#1072#1076#1072#1085#1085#1086#1077'*'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 10
          end
          object Panel_2_Col1_Row6: TPanel
            Left = 3
            Top = 120
            Width = 205
            Height = 20
            BevelInner = bvLowered
            Caption = #1058#1086#1082' '#1089#1074#1077#1090#1086#1076#1080#1086#1076#1072' '#1079#1072#1076#1072#1085#1085#1099#1081
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 11
          end
          object Panel_2_Col1_Row7: TPanel
            Left = 3
            Top = 141
            Width = 205
            Height = 20
            BevelInner = bvLowered
            Caption = #1044#1083#1080#1090#1077#1083#1100#1085#1086#1089#1090#1100' '#1064#1048#1052#1072' '#1079#1072#1076#1072#1085#1085#1072#1103
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 12
          end
          object Panel_2_Col1_Row9: TPanel
            Left = 3
            Top = 183
            Width = 205
            Height = 20
            BevelInner = bvLowered
            Caption = #1055#1045#1056#1048#1054#1044' '#1064#1048#1052' '#1084#1080#1085#1080#1084#1072#1083#1100#1085#1099#1081
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 13
          end
          object Panel_2_Col3_Row10: TPanel
            Left = 279
            Top = 204
            Width = 70
            Height = 20
            BevelInner = bvLowered
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 14
          end
          object Panel_2_Col1_Row10: TPanel
            Left = 3
            Top = 204
            Width = 205
            Height = 20
            BevelInner = bvLowered
            Caption = #1047#1072#1076#1072#1085#1085#1099#1081' '#1054#1058#1050#1051#1048#1050' '#1089#1074#1077#1090#1086#1076#1080#1086#1076#1072
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 15
          end
          object Panel_2_Col1_Row11: TPanel
            Left = 3
            Top = 225
            Width = 205
            Height = 20
            BevelInner = bvLowered
            Caption = #1057#1077#1088#1080#1081#1085#1099#1081' '#1085#1086#1084#1077#1088
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 16
          end
          object Panel_2_Col1_Row12: TPanel
            Left = 3
            Top = 246
            Width = 205
            Height = 20
            BevelInner = bvLowered
            Caption = #1053#1072#1087#1088'. '#1087#1088#1080' '#1085#1091#1083#1077#1074#1086#1081' '#1076#1083#1080#1090'. '#1064#1048#1052
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 17
          end
          object Panel_2_Col1_Row13: TPanel
            Left = 3
            Top = 267
            Width = 205
            Height = 20
            BevelInner = bvLowered
            Caption = #1053#1072#1087#1088'. '#1085#1086#1084'.*'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 18
          end
          object Panel_2_Col1_Row8: TPanel
            Left = 3
            Top = 162
            Width = 205
            Height = 20
            BevelInner = bvLowered
            Caption = #1055#1045#1056#1048#1054#1044' '#1064#1048#1052' '#1085#1072#1095#1072#1083#1100#1085#1099#1081
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 19
          end
          object Edit_2_Col2_Row4: TEdit
            Left = 210
            Top = 78
            Width = 67
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 20
            OnChange = Edit_2_Col2_Row4Change
          end
          object Edit_2_Col2_Row5: TEdit
            Left = 210
            Top = 99
            Width = 67
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 21
            OnChange = Edit_2_Col2_Row5Change
          end
          object Edit_2_Col2_Row6: TEdit
            Left = 210
            Top = 120
            Width = 67
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 22
          end
          object Edit_2_Col2_Row7: TEdit
            Left = 210
            Top = 141
            Width = 67
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 23
            OnChange = Edit_2_Col2_Row7Change
          end
          object Edit_2_Col2_Row8: TEdit
            Left = 210
            Top = 162
            Width = 67
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 24
          end
          object Edit_2_Col2_Row9: TEdit
            Left = 210
            Top = 183
            Width = 67
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 25
          end
          object Edit_2_Col2_Row10: TEdit
            Left = 210
            Top = 204
            Width = 67
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 26
          end
          object Edit_2_Col3_Row2: TEdit
            Left = 279
            Top = 36
            Width = 70
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 27
          end
          object Edit_2_Col3_Row3: TEdit
            Left = 279
            Top = 57
            Width = 70
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 28
          end
          object Edit_2_Col3_Row4: TEdit
            Left = 279
            Top = 78
            Width = 70
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 29
            OnChange = Edit_2_Col3_Row4Change
          end
          object Edit_2_Col3_Row5: TEdit
            Left = 279
            Top = 99
            Width = 70
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 30
            OnChange = Edit_2_Col3_Row5Change
          end
          object Edit_2_Col3_Row11: TEdit
            Left = 279
            Top = 225
            Width = 70
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 31
          end
          object Edit_2_Col3_Row12: TEdit
            Left = 279
            Top = 246
            Width = 70
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 32
          end
          object Edit_2_Col3_Row13: TEdit
            Left = 279
            Top = 267
            Width = 70
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 33
          end
          object Edit_2_Col4_Row6: TEdit
            Left = 405
            Top = 120
            Width = 37
            Height = 21
            Color = clMoneyGreen
            ReadOnly = True
            TabOrder = 34
            Text = '   '#1077#1076'.'
          end
          object Edit_2_Col4_Row7: TEdit
            Left = 405
            Top = 141
            Width = 37
            Height = 21
            Color = clMoneyGreen
            ReadOnly = True
            TabOrder = 35
            Text = '   '#1077#1076'.'
          end
          object Edit_2_Col4_Row8: TEdit
            Left = 405
            Top = 162
            Width = 37
            Height = 21
            Color = clMoneyGreen
            ReadOnly = True
            TabOrder = 36
            Text = '   '#1077#1076'.'
          end
          object Edit_2_Col4_Row9: TEdit
            Left = 405
            Top = 183
            Width = 37
            Height = 21
            Color = clMoneyGreen
            ReadOnly = True
            TabOrder = 37
            Text = '   '#1077#1076'.'
          end
          object Edit_2_Col4_Row10: TEdit
            Left = 405
            Top = 204
            Width = 37
            Height = 21
            Color = clMoneyGreen
            ReadOnly = True
            TabOrder = 38
            Text = '   '#1077#1076'.'
          end
          object Edit_2_Col4_Row12: TEdit
            Left = 350
            Top = 246
            Width = 92
            Height = 21
            Color = clMoneyGreen
            ReadOnly = True
            TabOrder = 39
            Text = '             '#1042'.'
          end
          object Edit_2_Col4_Row13: TEdit
            Left = 350
            Top = 267
            Width = 92
            Height = 21
            Color = clMoneyGreen
            ReadOnly = True
            TabOrder = 40
            Text = '             '#1042'.'
          end
          object Panel_2_Col2_Row2: TPanel
            Left = 210
            Top = 36
            Width = 67
            Height = 20
            BevelInner = bvLowered
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 41
          end
          object Edit_2_Col2_4_Row_14: TEdit
            Left = 210
            Top = 289
            Width = 232
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 42
            OnChange = Edit_2_Col2_4_Row_14Change
          end
          object Panel_2_Col1_Row14: TPanel
            Left = 3
            Top = 289
            Width = 205
            Height = 20
            BevelInner = bvLowered
            Caption = #1050#1086#1084#1084#1077#1085#1090'. '#1085#1072#1082#1083#1077#1081#1082#1072' (0 ... 23)'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 43
          end
          object Panel_2_Col3_Row9: TPanel
            Left = 279
            Top = 183
            Width = 70
            Height = 20
            BevelInner = bvLowered
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 44
          end
          object Panel_2_Col3_Row8: TPanel
            Left = 279
            Top = 162
            Width = 70
            Height = 20
            BevelInner = bvLowered
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 45
          end
          object Panel_2_Col3_Row7: TPanel
            Left = 279
            Top = 141
            Width = 70
            Height = 20
            BevelInner = bvLowered
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 46
          end
          object Panel_2_Col3_Row6: TPanel
            Left = 279
            Top = 120
            Width = 70
            Height = 20
            BevelInner = bvLowered
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 47
          end
          object Panel_2_Col4_Row11: TPanel
            Left = 350
            Top = 225
            Width = 92
            Height = 20
            BevelInner = bvLowered
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 48
          end
          object Panel_2_Col2_Row11: TPanel
            Left = 210
            Top = 225
            Width = 67
            Height = 20
            BevelInner = bvLowered
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 49
          end
          object Button_2_Col4_Row6_10: TButton
            Left = 351
            Top = 121
            Width = 53
            Height = 82
            Caption = '<---'
            Enabled = False
            TabOrder = 50
            OnClick = Button_2_Col4_Row6_10Click
          end
          object RadioGroup_KOD: TRadioGroup
            Left = 202
            Top = 322
            Width = 179
            Height = 31
            Caption = '   '#1055#1086#1083#1103' '#1074#1074#1086#1076#1072'   '
            Columns = 2
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ItemIndex = 0
            Items.Strings = (
              #1050#1086#1076
              #1047#1085#1072#1095#1077#1085#1080#1077)
            ParentFont = False
            TabOrder = 51
            OnClick = RadioGroup_KODClick
          end
          object Edit_SSP_bin: TEdit
            Left = 38
            Top = 332
            Width = 74
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            ReadOnly = True
            TabOrder = 52
          end
          object Edit_SSP_hex: TEdit
            Left = 109
            Top = 332
            Width = 40
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            ReadOnly = True
            TabOrder = 53
          end
        end
        object GroupBox_ReadSettings: TGroupBox
          Left = 457
          Top = 4
          Width = 418
          Height = 228
          Caption = '  '#1055#1086#1080#1089#1082' '#1041#1044'  '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
          object LabelAddtFrom: TLabel
            Left = 36
            Top = 16
            Width = 65
            Height = 13
            Caption = #1055#1077#1088#1074#1099#1081' '#1041#1044
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object LabelAddrTo: TLabel
            Left = 221
            Top = 16
            Width = 83
            Height = 13
            Caption = #1055#1086#1089#1083#1077#1076#1085#1080#1081' '#1041#1044
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object ButtonSearch: TButton
            Left = 160
            Top = 196
            Width = 85
            Height = 25
            Caption = #1053#1072#1095#1072#1090#1100
            TabOrder = 0
            OnClick = ButtonSearchClick
          end
          object Memo_SkanBD: TMemo
            Left = 3
            Top = 40
            Width = 406
            Height = 147
            ReadOnly = True
            ScrollBars = ssBoth
            TabOrder = 1
          end
          object Button_Clear_Memo_Scan: TButton
            Left = 93
            Top = 196
            Width = 66
            Height = 25
            Caption = #1057#1090#1077#1088#1077#1090#1100
            TabOrder = 2
            OnClick = Button_Clear_Memo_ScanClick
          end
          object Button_SaveAddr: TButton
            Left = 246
            Top = 196
            Width = 111
            Height = 25
            Caption = #1048#1079#1084#1077#1085#1080#1090#1100' '#1040#1076#1088#1077#1089
            TabOrder = 3
            OnClick = Button_SaveAddrClick
          end
          object SpinEdit_Begin: TCSpinEdit
            Left = 105
            Top = 13
            Width = 81
            Height = 22
            MaxValue = 247
            MinValue = 1
            TabOrder = 4
            Value = 1
          end
          object SpinEdit_End: TCSpinEdit
            Left = 313
            Top = 13
            Width = 81
            Height = 22
            MaxValue = 247
            MinValue = 1
            TabOrder = 5
            Value = 247
          end
        end
        object GroupBox_ARCH: TGroupBox
          Left = 457
          Top = 376
          Width = 160
          Height = 109
          Caption = '   '#1040#1056#1063'   '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 4
          object RadioButton_ARCH1: TRadioButton
            Left = 5
            Top = 15
            Width = 100
            Height = 17
            Caption = #1055#1088#1086#1075#1088#1072#1084#1084#1085#1086#1077
            Checked = True
            Color = clLime
            ParentColor = False
            TabOrder = 0
            TabStop = True
            OnClick = RadioButton_ARCH1Click
          end
          object RadioButton_ARCH2: TRadioButton
            Left = 5
            Top = 38
            Width = 100
            Height = 17
            Caption = #1056#1091#1095#1085#1086#1077
            Color = clBtnFace
            ParentColor = False
            TabOrder = 1
            OnClick = RadioButton_ARCH2Click
          end
          object RadioButton_ARCH3: TRadioButton
            Left = 5
            Top = 61
            Width = 100
            Height = 17
            Caption = #1054#1090#1082#1083#1102#1095#1077#1085#1086
            Color = clBtnFace
            ParentColor = False
            TabOrder = 2
            OnClick = RadioButton_ARCH3Click
          end
          object CheckBox_Diod: TCheckBox
            Left = 5
            Top = 88
            Width = 140
            Height = 17
            Caption = #1059#1095#1072#1097'. '#1089#1074#1077#1090#1086#1076#1080#1086#1076#1072
            Color = clBtnFace
            ParentColor = False
            TabOrder = 3
            OnClick = CheckBox_DiodClick
          end
        end
        object GroupBox_InfoFromBD_Ver: TGroupBox
          Left = 457
          Top = 310
          Width = 133
          Height = 66
          Caption = '   '#1057#1086#1089#1090#1086#1103#1085#1080#1077' '#1041#1044'   '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 5
          object Label_VerProshivki: TLabel
            Left = 10
            Top = 28
            Width = 40
            Height = 13
            Caption = #1042#1077#1088#1089#1080#1103
          end
          object Edit_Ver04: TEdit
            Left = 59
            Top = 25
            Width = 16
            Height = 22
            TabStop = False
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -12
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            ReadOnly = True
            TabOrder = 0
          end
          object Edit_Ver03: TEdit
            Left = 75
            Top = 25
            Width = 17
            Height = 22
            TabStop = False
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -12
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            ReadOnly = True
            TabOrder = 1
          end
          object Edit_Ver02: TEdit
            Left = 92
            Top = 25
            Width = 17
            Height = 22
            TabStop = False
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -12
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            ReadOnly = True
            TabOrder = 2
          end
          object Edit_Ver01: TEdit
            Left = 109
            Top = 25
            Width = 17
            Height = 22
            TabStop = False
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -12
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            ReadOnly = True
            TabOrder = 3
          end
        end
        object GroupBox_InfoFromBD_SetParam: TGroupBox
          Left = 456
          Top = 232
          Width = 419
          Height = 79
          Caption = '   '#1055#1086#1076#1082#1083#1102#1095#1077#1085#1080#1077'    '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          object Label_AddrBD: TLabel
            Left = 329
            Top = 15
            Width = 37
            Height = 13
            Caption = #1040#1076#1088#1077#1089
          end
          object Label_NomBD: TLabel
            Left = 114
            Top = 20
            Width = 67
            Height = 13
            Caption = #8470' '#1041#1044' (LPT)'
          end
          object CheckBox_Diskr: TCheckBox
            Left = 332
            Top = 58
            Width = 16
            Height = 18
            Caption = #1056#1072#1089#1096#1080#1088'. '#1087#1086#1088#1086#1075#1080' '#1076#1080#1089#1082#1088'.'
            Checked = True
            Enabled = False
            State = cbChecked
            TabOrder = 4
            Visible = False
            OnClick = CheckBox_DiskrClick
          end
          object SpinEdit_AddrBD: TCSpinEdit
            Left = 329
            Top = 30
            Width = 49
            Height = 22
            MaxValue = 247
            TabOrder = 1
            Value = 247
          end
          object Button_OpenBD: TButton
            Left = 195
            Top = 42
            Width = 125
            Height = 23
            Caption = #1054#1058#1050#1056#1067#1058#1068
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlue
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
            OnClick = Button_OpenBDClick
          end
          object CheckBox_auto: TCheckBox
            Left = 12
            Top = 15
            Width = 58
            Height = 17
            Caption = 'U'#1085
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 5
            OnClick = CheckBox_autoClick
          end
          object CheckBox_DAuto: TCheckBox
            Left = 12
            Top = 52
            Width = 97
            Height = 17
            Caption = #1044#1080#1089#1082#1088'. '#1072#1074#1090#1086
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 6
            Visible = False
            OnClick = CheckBox_DAutoClick
          end
          object Button_WriteToBD: TButton
            Left = 195
            Top = 14
            Width = 124
            Height = 23
            Caption = #1047#1072#1087#1080#1089#1100' '#1087#1072#1088#1072#1084#1077#1090#1088#1086#1074
            Enabled = False
            TabOrder = 2
            OnClick = Button_WriteToBDClick
          end
          object ComboBox_NomBD: TComboBox
            Left = 112
            Top = 34
            Width = 74
            Height = 21
            Style = csDropDownList
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ItemHeight = 13
            ItemIndex = 0
            ParentFont = False
            TabOrder = 3
            Text = #1054#1090#1082#1083'.'
            OnChange = ComboBox_NomBDChange
            Items.Strings = (
              #1054#1090#1082#1083'.'
              #1041#1044'1'
              #1041#1044'2'
              #1041#1044'3'
              #1041#1044'4'
              #1041#1044'5'
              #1041#1044'6'
              #1041#1044'7'
              #1041#1044'8')
          end
          object CheckBox_auto_0_81: TCheckBox
            Left = 12
            Top = 33
            Width = 58
            Height = 17
            Caption = 'U0,81'
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 7
            OnClick = CheckBox_auto_0_81Click
          end
        end
        object SpinEdit_ForSaveAddr: TCSpinEdit
          Left = 816
          Top = 201
          Width = 54
          Height = 22
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          MaxValue = 247
          MinValue = 1
          ParentFont = False
          TabOrder = 6
          Value = 1
        end
        object Button_ARCH: TButton
          Left = 663
          Top = 316
          Width = 91
          Height = 25
          Caption = #1040#1056#1063
          TabOrder = 7
          OnClick = Button_ARCHClick
        end
        object Button_Puason: TButton
          Left = 663
          Top = 345
          Width = 91
          Height = 25
          Caption = #1055#1059#1040#1057#1057#1054#1053
          TabOrder = 8
          OnClick = Button_PuasonClick
        end
        object Panel_bit7: TPanel
          Left = 613
          Top = 340
          Width = 32
          Height = 31
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Color = clRed
          TabOrder = 9
        end
        object RadioGroup_VyborProtokola: TRadioGroup
          Left = 456
          Top = 486
          Width = 161
          Height = 97
          Caption = '   '#1055#1088#1086#1090#1086#1082#1086#1083'   '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ItemIndex = 0
          Items.Strings = (
            '9-'#1090#1080' '#1073#1080#1090#1085#1099#1081
            'ModBus RTU'
            'ModBus TCP'
            'ModBus RTU (TCP/IP)')
          ParentFont = False
          TabOrder = 10
          OnClick = RadioGroup_VyborProtokolaClick
        end
        object GroupBox_ComPort: TGroupBox
          Left = 758
          Top = 311
          Width = 117
          Height = 117
          Caption = ' '#1042#1099#1073#1086#1088' '#1087#1086#1088#1090#1072' '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 11
          object Label_NomComPort: TLabel
            Left = 7
            Top = 17
            Width = 82
            Height = 13
            Caption = #8470' COM-'#1087#1086#1088#1090#1072
          end
          object Label_UpdateComPorts: TLabel
            Left = 6
            Top = 67
            Width = 68
            Height = 13
            Caption = 'COM-'#1087#1086#1088#1090#1099
          end
          object Button_UpdateComPortsList: TButton
            Left = 7
            Top = 82
            Width = 74
            Height = 24
            Caption = #1054#1073#1085#1086#1074#1080#1090#1100
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
            OnClick = Button_UpdateComPortsListClick
          end
          object ComboBox_NomComPort: TComboBox
            Left = 6
            Top = 33
            Width = 81
            Height = 21
            Style = csDropDownList
            ItemHeight = 13
            TabOrder = 1
          end
          object Edit_IPAddr: TEdit
            Left = 5
            Top = 32
            Width = 108
            Height = 21
            TabOrder = 2
            Text = '192.168.3.4'
          end
          object Edit_IPPort: TEdit
            Left = 7
            Top = 83
            Width = 47
            Height = 21
            TabOrder = 3
            Text = '502'
          end
        end
        object Button_Spectr: TButton
          Left = 663
          Top = 375
          Width = 91
          Height = 25
          Caption = #1057#1087#1077#1082#1090#1088' ('#1041#1044'84)'
          TabOrder = 12
          OnClick = Button_SpectrClick
        end
        object Button_SaveToFile: TButton
          Left = 774
          Top = 458
          Width = 86
          Height = 23
          Caption = #1042' '#1092#1072#1081#1083
          Enabled = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 13
          OnClick = Button_SaveToFileClick
        end
        object BitBtn_P37SetReset: TBitBtn
          Left = 461
          Top = 200
          Width = 88
          Height = 25
          Caption = #1047#1074#1091#1082' On / Off'
          Enabled = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 14
          OnMouseDown = BitBtn_P37SetResetMouseDown
          OnMouseUp = BitBtn_P37SetResetMouseUp
        end
        object Button_Plus: TButton
          Left = 843
          Top = 242
          Width = 29
          Height = 28
          Caption = '+'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -24
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 15
          OnClick = Button_PlusClick
        end
        object Button_Minus: TButton
          Left = 843
          Top = 279
          Width = 29
          Height = 28
          Caption = '-'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -24
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 16
          OnClick = Button_MinusClick
        end
        object Panel_2_Col2_Row12: TPanel
          Left = 214
          Top = 568
          Width = 67
          Height = 20
          BevelInner = bvLowered
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 17
        end
        object Panel_2_Col2_Row13: TPanel
          Left = 214
          Top = 589
          Width = 67
          Height = 20
          BevelInner = bvLowered
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 18
        end
        object Panel_MoxaSettingsDisplay: TPanel
          Left = 455
          Top = 587
          Width = 418
          Height = 30
          BevelInner = bvLowered
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlue
          Font.Height = -13
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 19
        end
        object CheckBox_DAuto_Standart: TCheckBox
          Left = 357
          Top = 401
          Width = 82
          Height = 14
          Caption = #1057#1090#1072#1085#1076#1072#1088#1090
          Color = clInfoBk
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          TabOrder = 20
          OnClick = CheckBox_DAuto_StandartClick
        end
        object CheckBox_DAuto_Shirokie: TCheckBox
          Left = 357
          Top = 414
          Width = 82
          Height = 13
          Caption = #1064#1080#1088#1086#1082#1080#1077
          Color = clInfoBk
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          TabOrder = 21
          OnClick = CheckBox_DAuto_ShirokieClick
        end
        object CheckBox_DAuto_Rengen: TCheckBox
          Left = 357
          Top = 427
          Width = 82
          Height = 14
          Caption = #1056#1077#1085#1075#1077#1085
          Color = clInfoBk
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          TabOrder = 22
          OnClick = CheckBox_DAuto_RengenClick
        end
      end
    end
    object TabSheet_Modbus: TTabSheet
      Caption = '  '#1053#1072#1089#1090#1088#1086#1081#1082#1080' ModBus  '
      ImageIndex = 3
      object ScrollBox_Tab3_Scrolling: TScrollBox
        Left = 0
        Top = 0
        Width = 881
        Height = 689
        Align = alClient
        TabOrder = 0
        object GroupBox_SettingsForModbus: TGroupBox
          Left = 9
          Top = 15
          Width = 568
          Height = 330
          Caption = '   '#1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1076#1083#1103' '#1041#1044' ModBus   '
          Enabled = False
          TabOrder = 0
          object Label_3_01: TLabel
            Left = 24
            Top = 24
            Width = 64
            Height = 13
            Caption = #1053#1086#1084#1077#1088' '#1073#1083#1086#1082#1072
          end
          object Label_3_02: TLabel
            Left = 24
            Top = 73
            Width = 77
            Height = 13
            Caption = #1069#1082#1089#1087#1086#1079#1080#1094#1080#1103', '#1084#1089
          end
          object Label_3_03: TLabel
            Left = 23
            Top = 123
            Width = 96
            Height = 13
            Caption = #1052#1080#1085#1080#1084#1072#1083#1100#1085#1099#1081' '#1089#1095#1105#1090
          end
          object Label_3_04: TLabel
            Left = 24
            Top = 173
            Width = 101
            Height = 13
            Caption = #1052#1072#1082#1089#1080#1084#1072#1083#1100#1085#1099#1081' '#1089#1095#1105#1090
          end
          object Label_3_05: TLabel
            Left = 24
            Top = 223
            Width = 104
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100' '#1087#1077#1088#1077#1075#1088#1091#1079#1082#1080
          end
          object Label_3_06: TLabel
            Left = 197
            Top = 26
            Width = 98
            Height = 13
            Caption = #1050#1086#1083'-'#1074#1086' '#1080#1085#1090#1077#1088#1074#1072#1083#1086#1074
          end
          object Label_3_07: TLabel
            Left = 197
            Top = 73
            Width = 111
            Height = 13
            Caption = #1050#1086#1083'-'#1074#1086' '#1074#1079#1075#1083#1103#1076#1072' '#1087#1086#1089#1083#1077
          end
          object Label_3_08: TLabel
            Left = 197
            Top = 124
            Width = 120
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100' '#1090#1088#1077#1074#1086#1075#1080' 1 * 10'
          end
          object Label_3_09: TLabel
            Left = 197
            Top = 174
            Width = 120
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100' '#1090#1088#1077#1074#1086#1075#1080' 2 * 10'
          end
          object Label_3_10: TLabel
            Left = 197
            Top = 225
            Width = 120
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100' '#1090#1088#1077#1074#1086#1075#1080' 3 * 10'
          end
          object Label_3_11: TLabel
            Left = 372
            Top = 25
            Width = 32
            Height = 13
            Caption = #1060#1086#1085', '#1089
          end
          object Label_3_12: TLabel
            Left = 371
            Top = 74
            Width = 153
            Height = 13
            Caption = #1044#1083#1080#1090'. '#1087#1086#1076#1080#1085#1090#1077#1088#1074#1072#1083#1072' '#1092#1086#1085#1072', '#1084#1089
          end
          object Label_3_13: TLabel
            Left = 373
            Top = 124
            Width = 129
            Height = 13
            Caption = #1044#1083#1080#1090'. '#1089#1080#1075#1085#1072#1083#1072' '#1090#1088#1077#1074#1086#1075#1080', '#1089
          end
          object Label_3_14: TLabel
            Left = 373
            Top = 176
            Width = 119
            Height = 13
            Caption = #1044#1083#1080#1090'. '#1089#1080#1075#1085#1072#1083#1072' '#1074#1080#1076#1077#1086', '#1089
          end
          object Label_3_15: TLabel
            Left = 375
            Top = 227
            Width = 148
            Height = 13
            Caption = #1040#1073#1089#1086#1083#1102#1090#1085#1099#1081' '#1092#1086#1085', '#1080#1084#1087'. / '#1089#1077#1082'.'
          end
          object Edit_3_01: TEdit
            Left = 23
            Top = 39
            Width = 140
            Height = 21
            TabOrder = 0
          end
          object Edit_3_02: TEdit
            Left = 23
            Top = 87
            Width = 140
            Height = 21
            TabOrder = 1
          end
          object Edit_3_03: TEdit
            Left = 23
            Top = 138
            Width = 140
            Height = 21
            TabOrder = 2
          end
          object Edit_3_04: TEdit
            Left = 23
            Top = 189
            Width = 140
            Height = 21
            TabOrder = 3
          end
          object Edit_3_05: TEdit
            Left = 23
            Top = 240
            Width = 140
            Height = 21
            TabOrder = 4
          end
          object Edit_3_06: TEdit
            Left = 197
            Top = 39
            Width = 143
            Height = 21
            TabOrder = 5
          end
          object Edit_3_07: TEdit
            Left = 197
            Top = 87
            Width = 143
            Height = 21
            TabOrder = 6
          end
          object Edit_3_08: TEdit
            Left = 197
            Top = 138
            Width = 143
            Height = 21
            TabOrder = 7
          end
          object Edit_3_09: TEdit
            Left = 197
            Top = 189
            Width = 143
            Height = 21
            TabOrder = 8
          end
          object Edit_3_10: TEdit
            Left = 197
            Top = 241
            Width = 142
            Height = 21
            TabOrder = 9
          end
          object Edit_3_11: TEdit
            Left = 372
            Top = 39
            Width = 152
            Height = 21
            TabOrder = 10
          end
          object Edit_3_12: TEdit
            Left = 372
            Top = 87
            Width = 152
            Height = 21
            TabOrder = 11
          end
          object Edit_3_13: TEdit
            Left = 373
            Top = 138
            Width = 152
            Height = 21
            TabOrder = 12
          end
          object Edit_3_14: TEdit
            Left = 374
            Top = 190
            Width = 152
            Height = 21
            TabOrder = 13
          end
          object Button_ModBus_Write: TButton
            Left = 456
            Top = 288
            Width = 89
            Height = 25
            Caption = #1047#1072#1087#1080#1089#1100
            Enabled = False
            TabOrder = 14
            OnClick = Button_ModBus_WriteClick
          end
          object Button_ModBus_SetDef: TButton
            Left = 352
            Top = 288
            Width = 86
            Height = 25
            Caption = #1055#1086' '#1091#1084#1086#1083#1095#1072#1085#1080#1102
            Enabled = False
            TabOrder = 15
            OnClick = Button_ModBus_SetDefClick
          end
          object Edit_3_15: TEdit
            Left = 375
            Top = 241
            Width = 152
            Height = 21
            TabOrder = 16
          end
        end
      end
    end
    object TabSheet_Reports: TTabSheet
      Caption = '  '#1054#1090#1095#1105#1090' '#1086' '#1088#1072#1073#1086#1090#1077' '#1087#1088#1086#1075#1088#1072#1084#1084#1099'  '
      ImageIndex = 2
      object ScrollBox_Tab4_Scrolling: TScrollBox
        Left = 0
        Top = 0
        Width = 881
        Height = 689
        Align = alClient
        TabOrder = 0
        object Button_Clear_Memo_Err: TButton
          Left = 15
          Top = 16
          Width = 82
          Height = 25
          Caption = #1054#1095#1080#1089#1090#1080#1090#1100
          TabOrder = 0
          OnClick = Button_Clear_Memo_ErrClick
        end
        object GroupBox_For_Prints_Errors: TGroupBox
          Left = 3
          Top = 57
          Width = 877
          Height = 587
          Caption = '   '#1054#1090#1095#1077#1090' '#1086' '#1088#1072#1073#1086#1090#1077' '#1087#1088#1086#1075#1088#1072#1084#1084#1099'   '
          TabOrder = 1
          object Memo_For_Print_Errors: TMemo
            Left = 2
            Top = 15
            Width = 873
            Height = 570
            Align = alClient
            ReadOnly = True
            ScrollBars = ssBoth
            TabOrder = 0
          end
        end
      end
    end
    object TabSheet_SetSettings: TTabSheet
      Caption = '  LPT && COM, ModBus TCP  '
      ImageIndex = 1
      object ScrollBox_Tab2_Scrolling: TScrollBox
        Left = 0
        Top = 0
        Width = 881
        Height = 689
        Align = alClient
        TabOrder = 0
        object Label_sek: TLabel
          Left = 641
          Top = 130
          Width = 21
          Height = 13
          Caption = #1089#1077#1082'.'
          Visible = False
        end
        object LabelLptAddr: TLabel
          Left = 245
          Top = 169
          Width = 182
          Height = 13
          Caption = #1040#1076#1088#1077#1089' LPT-'#1087#1086#1088#1090#1072' (888 - '#1095#1072#1097#1077' '#1074#1089#1077#1075#1086')'
        end
        object Label_arch: TLabel
          Left = 680
          Top = 23
          Width = 20
          Height = 13
          Caption = #1040#1056#1063
          Visible = False
        end
        object Label_uch_sv: TLabel
          Left = 667
          Top = 50
          Width = 35
          Height = 13
          Caption = #1059#1095'. '#1089#1074'.'
          Visible = False
        end
        object StringGrid1: TStringGrid
          Left = 9
          Top = 117
          Width = 217
          Height = 236
          ColCount = 3
          RowCount = 9
          TabOrder = 0
          RowHeights = (
            24
            24
            24
            24
            24
            24
            24
            24
            24)
        end
        object CheckBox_Proshivka: TCheckBox
          Left = 237
          Top = 117
          Width = 193
          Height = 17
          Caption = #1053#1086#1074#1072#1103' '#1087#1088#1086#1096#1080#1074#1082#1072' '#1041#1044'? ('#1076#1072' / '#1085#1077#1090')'
          TabOrder = 1
          Visible = False
        end
        object GroupBox_InfoFromBD_AutoTesting: TGroupBox
          Left = 9
          Top = 7
          Width = 632
          Height = 105
          Caption = '   '#1074#1099#1073#1086#1088' '#1041#1044' '#1076#1083#1103' '#1087#1088#1086#1074#1077#1088#1082#1080'   '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
          object Label_BD01: TLabel
            Left = 22
            Top = 32
            Width = 7
            Height = 13
            Caption = '1'
          end
          object Label_BD02: TLabel
            Left = 40
            Top = 32
            Width = 7
            Height = 13
            Caption = '2'
          end
          object Label_BD03: TLabel
            Left = 56
            Top = 32
            Width = 7
            Height = 13
            Caption = '3'
          end
          object Label_BD04: TLabel
            Left = 74
            Top = 32
            Width = 7
            Height = 13
            Caption = '4'
          end
          object Label_BD05: TLabel
            Left = 90
            Top = 32
            Width = 7
            Height = 13
            Caption = '5'
          end
          object Label_BD06: TLabel
            Left = 107
            Top = 33
            Width = 7
            Height = 13
            Caption = '6'
          end
          object Label_BD07: TLabel
            Left = 124
            Top = 33
            Width = 7
            Height = 13
            Caption = '7'
          end
          object Label_BD08: TLabel
            Left = 141
            Top = 33
            Width = 7
            Height = 13
            Caption = '8'
          end
          object Label_Imp2sek: TLabel
            Left = 248
            Top = 88
            Width = 310
            Height = 13
            Caption = #1059#1089#1090#1072#1085#1072#1074#1083#1080#1074#1072#1077#1090' 4-'#1099#1081' '#1074#1099#1074#1086#1076' LPT-'#1087#1086#1088#1090#1072' '#1085#1072' 2 '#1089#1077#1082#1091#1085#1076#1099
          end
          object Label_Start: TLabel
            Left = 250
            Top = 40
            Width = 365
            Height = 13
            Caption = #1057#1090#1072#1088#1090#1091#1077#1090' '#1090#1077#1089#1090#1080#1088#1086#1074#1072#1085#1080#1077' '#1074#1099#1073#1088#1072#1085#1085#1099#1093' '#1041#1044' '#1086#1076#1080#1085' '#1088#1072#1079' '#1083#1080#1073#1086' '#1074' '#1094#1080#1082#1083#1077
          end
          object Button_Start: TButton
            Left = 324
            Top = 15
            Width = 82
            Height = 25
            Caption = 'Start'
            TabOrder = 0
            OnClick = Button_StartClick
          end
          object CheckBox_Vybor_BD01: TCheckBox
            Left = 20
            Top = 45
            Width = 11
            Height = 17
            TabOrder = 1
          end
          object CheckBox_Vybor_BD02: TCheckBox
            Left = 37
            Top = 45
            Width = 11
            Height = 17
            TabOrder = 2
          end
          object CheckBox_Vybor_BD03: TCheckBox
            Left = 54
            Top = 45
            Width = 11
            Height = 17
            TabOrder = 3
          end
          object CheckBox_Vybor_BD04: TCheckBox
            Left = 71
            Top = 45
            Width = 11
            Height = 17
            TabOrder = 4
          end
          object CheckBox_Vybor_BD08: TCheckBox
            Left = 139
            Top = 45
            Width = 11
            Height = 17
            TabOrder = 5
          end
          object CheckBox_Vybor_BD07: TCheckBox
            Left = 122
            Top = 45
            Width = 11
            Height = 17
            TabOrder = 6
          end
          object CheckBox_Vybor_BD06: TCheckBox
            Left = 105
            Top = 45
            Width = 11
            Height = 17
            TabOrder = 7
          end
          object CheckBox_Vybor_BD05: TCheckBox
            Left = 88
            Top = 45
            Width = 11
            Height = 17
            TabOrder = 8
          end
          object RadioGroup_Povtor: TRadioGroup
            Left = 165
            Top = 11
            Width = 78
            Height = 80
            Caption = '   '#1055#1086#1074#1090#1086#1088'   '
            Items.Strings = (
              '1 '#1088#1072#1079
              #1094#1080#1082#1083)
            TabOrder = 9
            OnClick = RadioGroup_PovtorClick
          end
          object CheckBox_All: TCheckBox
            Left = 5
            Top = 74
            Width = 73
            Height = 17
            Caption = #1042#1089#1077' '#1041#1044
            TabOrder = 10
            OnClick = CheckBox_AllClick
          end
          object Button_Imp2sek: TButton
            Left = 323
            Top = 64
            Width = 82
            Height = 25
            Caption = #1048#1084#1087'. (2 '#1089#1077#1082'.)'
            TabOrder = 11
            OnClick = Button_Imp2sekClick
          end
          object Panel_bit7_2: TPanel
            Left = 413
            Top = 63
            Width = 24
            Height = 23
            BevelInner = bvRaised
            BevelOuter = bvLowered
            Color = clRed
            TabOrder = 12
          end
        end
        object Button_OpenBD_msek: TButton
          Left = 428
          Top = 124
          Width = 123
          Height = 23
          Caption = #1054#1058#1050#1056#1067#1058#1068' '#1053#1040
          Enabled = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlue
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 3
          Visible = False
          OnClick = Button_OpenBD_msekClick
        end
        object SpinEdit_Sek: TCSpinEdit
          Left = 557
          Top = 125
          Width = 81
          Height = 22
          Enabled = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          MaxValue = 247
          MinValue = 1
          ParentFont = False
          TabOrder = 4
          Value = 1
          Visible = False
        end
        object SpinEditLptAddr: TCSpinEdit
          Left = 243
          Top = 186
          Width = 102
          Height = 22
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          MaxValue = 100000
          MinValue = 1
          ParentFont = False
          TabOrder = 5
          Value = 888
        end
        object ButtonSetLptAddr: TButton
          Left = 243
          Top = 214
          Width = 123
          Height = 25
          Caption = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1072#1076#1077#1089' LPT'
          TabOrder = 6
          OnClick = ButtonSetLptAddrClick
        end
        object Button_Out32: TButton
          Left = 736
          Top = 184
          Width = 75
          Height = 25
          Caption = ' Out32'
          Enabled = False
          TabOrder = 7
          Visible = False
          OnClick = Button_Out32Click
        end
        object Button_Inp32: TButton
          Left = 736
          Top = 216
          Width = 75
          Height = 25
          Caption = 'Inp32'
          Enabled = False
          TabOrder = 8
          Visible = False
        end
        object GroupBox_For_Metro: TGroupBox
          Left = 8
          Top = 360
          Width = 257
          Height = 313
          Caption = '   '#1055#1072#1088#1072#1084#1077#1090#1088#1099' ModBus TCP ('#1076#1083#1103' '#1084#1077#1090#1088#1086')   '
          TabOrder = 9
          object Label_StantsiyaMetro: TLabel
            Left = 21
            Top = 133
            Width = 173
            Height = 13
            Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1089#1090#1072#1085#1094#1080#1080' '#1084#1077#1090#1088#1086#1087#1086#1083#1080#1090#1077#1085#1072
          end
          object CheckBox_Enabled_Write_TCP: TCheckBox
            Left = 16
            Top = 27
            Width = 233
            Height = 17
            Caption = #1056#1072#1079#1088#1077#1096#1080#1090#1100' '#1079#1072#1087#1080#1089#1100' '#1074' '#1041#1044' ('#1044#1072'/'#1053#1077#1090')'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
            OnClick = CheckBox_Enabled_Write_TCPClick
          end
          object CheckBox_Image: TCheckBox
            Left = 21
            Top = 110
            Width = 185
            Height = 17
            Caption = #1062#1074#1077#1090#1085#1086#1081' screenshot  ('#1044#1072' / '#1053#1077#1090')? '
            Checked = True
            State = cbChecked
            TabOrder = 1
          end
          object Button_Image: TButton
            Left = 16
            Top = 80
            Width = 193
            Height = 25
            Caption = 'Screenshot "'#1048#1085#1092#1086#1088#1084#1072#1094#1080#1103' '#1089' '#1041#1044'"'
            TabOrder = 2
            OnClick = Button_ImageClick
          end
          object Edit_StantsiyaMetro: TEdit
            Left = 15
            Top = 149
            Width = 209
            Height = 21
            TabOrder = 3
          end
          object Button_ToComment: TButton
            Left = 29
            Top = 173
            Width = 177
            Height = 25
            Caption = '<--- '#1047#1072#1087#1086#1083#1085#1080#1090#1100' "'#1050#1086#1084#1084#1077#1085#1090#1072#1088#1080#1081'"'
            TabOrder = 4
            OnClick = Button_ToCommentClick
          end
        end
        object RichEdit_SaveLogToFile: TRichEdit
          Left = 608
          Top = 520
          Width = 273
          Height = 145
          Enabled = False
          ScrollBars = ssBoth
          TabOrder = 10
          Visible = False
        end
        object Memo_SaveLogToFile: TMemo
          Left = 608
          Top = 368
          Width = 273
          Height = 145
          Enabled = False
          ScrollBars = ssBoth
          TabOrder = 11
          Visible = False
        end
        object BitBtn_ARCH: TBitBtn
          Left = 710
          Top = 17
          Width = 107
          Height = 25
          Caption = #1054#1090#1082#1083#1102#1095#1077#1085#1086
          Enabled = False
          TabOrder = 12
          Visible = False
          Glyph.Data = {
            DE010000424DDE01000000000000760000002800000024000000120000000100
            0400000000006801000000000000000000001000000000000000000000000000
            80000080000000808000800000008000800080800000C0C0C000808080000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
            3333333333333FFFFF333333000033333388888833333333333F888888FFF333
            000033338811111188333333338833FFF388FF33000033381119999111833333
            38F338888F338FF30000339119933331111833338F388333383338F300003391
            13333381111833338F8F3333833F38F3000039118333381119118338F38F3338
            33F8F38F000039183333811193918338F8F333833F838F8F0000391833381119
            33918338F8F33833F8338F8F000039183381119333918338F8F3833F83338F8F
            000039183811193333918338F8F833F83333838F000039118111933339118338
            F3833F83333833830000339111193333391833338F33F8333FF838F300003391
            11833338111833338F338FFFF883F83300003339111888811183333338FF3888
            83FF83330000333399111111993333333388FFFFFF8833330000333333999999
            3333333333338888883333330000333333333333333333333333333333333333
            0000}
          NumGlyphs = 2
        end
        object BitBtn_Uch_sv: TBitBtn
          Left = 710
          Top = 48
          Width = 107
          Height = 25
          Caption = #1054#1090#1082#1083#1102#1095#1077#1085#1086
          Enabled = False
          TabOrder = 13
          Visible = False
          Glyph.Data = {
            DE010000424DDE01000000000000760000002800000024000000120000000100
            0400000000006801000000000000000000001000000000000000000000000000
            80000080000000808000800000008000800080800000C0C0C000808080000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
            3333333333333FFFFF333333000033333388888833333333333F888888FFF333
            000033338811111188333333338833FFF388FF33000033381119999111833333
            38F338888F338FF30000339119933331111833338F388333383338F300003391
            13333381111833338F8F3333833F38F3000039118333381119118338F38F3338
            33F8F38F000039183333811193918338F8F333833F838F8F0000391833381119
            33918338F8F33833F8338F8F000039183381119333918338F8F3833F83338F8F
            000039183811193333918338F8F833F83333838F000039118111933339118338
            F3833F83333833830000339111193333391833338F33F8333FF838F300003391
            11833338111833338F338FFFF883F83300003339111888811183333338FF3888
            83FF83330000333399111111993333333388FFFFFF8833330000333333999999
            3333333333338888883333330000333333333333333333333333333333333333
            0000}
          NumGlyphs = 2
        end
        object Button_P3_7_Set: TButton
          Left = 392
          Top = 202
          Width = 72
          Height = 25
          Caption = #1047#1074#1091#1082' On'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 14
          OnClick = Button_P3_7_SetClick
        end
        object Button_P3_7_Reset: TButton
          Left = 471
          Top = 202
          Width = 74
          Height = 25
          Caption = #1047#1074#1091#1082' Off'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 15
          OnClick = Button_P3_7_ResetClick
        end
        object GroupBox_TCP: TGroupBox
          Left = 268
          Top = 360
          Width = 247
          Height = 313
          TabOrder = 16
          object Label_KolTik: TLabel
            Left = 6
            Top = 37
            Width = 64
            Height = 13
            Caption = 'KolTik, '#1096#1090'.'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object CheckBox_speed: TCheckBox
            Left = 6
            Top = 13
            Width = 235
            Height = 17
            Caption = 'Speed ('#1041#1072#1081#1090' '#1072#1076#1088#1077#1089#1072' '#1090#1086#1083#1100#1082#1086' 1 '#1088#1072#1079')'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
            OnClick = CheckBox_speedClick
          end
          object Edit_KolTik: TEdit
            Left = 4
            Top = 52
            Width = 60
            Height = 21
            TabOrder = 1
          end
        end
        object GroupBox_UsredSchet: TGroupBox
          Left = 231
          Top = 247
          Width = 418
          Height = 105
          Caption = '   '#1055#1086#1083#1091#1095#1077#1085#1080#1077' '#1089#1095#1105#1090#1072'   '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 17
          object Label_time_izm: TLabel
            Left = 47
            Top = 16
            Width = 123
            Height = 13
            Caption = #1042#1088#1077#1084#1103' '#1080#1079#1084#1077#1088#1077#1085#1080#1103' = '
          end
          object Label_time_izm_2: TLabel
            Left = 241
            Top = 16
            Width = 8
            Height = 13
            Caption = #1089
          end
          object Button_Set_Reset: TButton
            Left = 261
            Top = 10
            Width = 68
            Height = 20
            Caption = #1057#1073#1088#1086#1089
            TabOrder = 0
            OnClick = Button_Set_ResetClick
          end
          object Panel_3_Col1_Row1: TPanel
            Left = 7
            Top = 33
            Width = 166
            Height = 20
            BevelInner = bvLowered
            Caption = #1059#1089#1088#1077#1076#1085#1105#1085#1085#1099#1081' '#1089#1095#1105#1090' '#1089' '#1041#1044
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
          end
          object Panel_3_Col2_Row3: TPanel
            Left = 174
            Top = 73
            Width = 45
            Height = 20
            BevelInner = bvLowered
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 2
          end
          object Edit_3_Col3_Row2: TEdit
            Left = 220
            Top = 53
            Width = 80
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 3
          end
          object Edit_3_Col4_Row1: TEdit
            Left = 300
            Top = 32
            Width = 67
            Height = 21
            Color = clMoneyGreen
            ReadOnly = True
            TabOrder = 4
            Text = '  '#1080#1084#1087' / '#1089
          end
          object Panel_3_Col1_Row2: TPanel
            Left = 7
            Top = 53
            Width = 166
            Height = 20
            BevelInner = bvLowered
            Caption = #1057#1095#1105#1090' '#1089' '#1041#1044' '#1079#1072' '#1074#1088#1077#1084#1103' '#1080#1079#1084'.'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 5
          end
          object Panel_3_Col2_Row2: TPanel
            Left = 173
            Top = 53
            Width = 45
            Height = 20
            BevelInner = bvLowered
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 6
          end
          object Edit_3_Col3_Row1: TEdit
            Left = 220
            Top = 32
            Width = 80
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 7
          end
          object Edit_3_Col4_Row2: TEdit
            Left = 300
            Top = 52
            Width = 67
            Height = 21
            Color = clMoneyGreen
            ReadOnly = True
            TabOrder = 8
            Text = '    '#1080#1084#1087'.'
          end
          object Panel_3_Col1_Row3: TPanel
            Left = 7
            Top = 73
            Width = 166
            Height = 20
            BevelInner = bvLowered
            Caption = #1058#1077#1082#1091#1097#1077#1077' '#1074#1088#1077#1084#1103' '#1089#1095#1105#1090#1072' '#1080#1084#1087'.'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 9
          end
          object Panel_3_Col2_Row1: TPanel
            Left = 173
            Top = 33
            Width = 45
            Height = 20
            BevelInner = bvLowered
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 10
          end
          object Edit_3_Col3_Row3: TEdit
            Left = 220
            Top = 73
            Width = 80
            Height = 21
            Color = clMoneyGreen
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 11
          end
          object Edit_3_Col4_Row3: TEdit
            Left = 300
            Top = 73
            Width = 67
            Height = 21
            Color = clMoneyGreen
            ReadOnly = True
            TabOrder = 12
            Text = '       '#1089
          end
          object Button_Sum_Schet: TButton
            Left = 333
            Top = 10
            Width = 68
            Height = 20
            Caption = #1057#1090#1072#1088#1090
            TabOrder = 13
            OnClick = Button_Sum_SchetClick
          end
          object CSpinEdit_time_izm: TCSpinEdit
            Left = 172
            Top = 10
            Width = 64
            Height = 22
            MaxValue = 1000
            MinValue = 1
            TabOrder = 14
            Value = 100
          end
        end
        object Button_P37SetReset: TButton
          Left = 735
          Top = 250
          Width = 89
          Height = 25
          Caption = #1047#1074#1091#1082' On / Off'
          Enabled = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGradientActiveCaption
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 18
          Visible = False
          OnMouseDown = Button_P37SetResetMouseDown
          OnMouseUp = Button_P37SetResetMouseUp
        end
      end
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 720
    Width = 889
    Height = 19
    Panels = <
      item
        Width = 300
      end
      item
        Width = 300
      end
      item
        Width = 50
      end>
    SimplePanel = False
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 672
    Top = 65528
  end
  object Timer2: TTimer
    Enabled = False
    OnTimer = Timer2Timer
    Left = 616
    Top = 65528
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'txt'
    FileName = 'NastrBD.txt'
    Filter = #1090#1077#1082#1089#1090#1086#1074#1099#1077' (*.txt)|*.txt|'#1074#1089#1077' '#1092#1072#1081#1083#1099'|*.*'
    Title = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1087#1072#1088#1072#1084#1077#1090#1088#1099' '#1041#1044'82 '#1074' '#1092#1072#1081#1083
    Left = 840
    Top = 65528
  end
  object Timer3: TTimer
    Enabled = False
    OnTimer = Timer3Timer
    Left = 720
    Top = 65528
  end
end
