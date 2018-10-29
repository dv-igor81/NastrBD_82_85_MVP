object Form_RearFromEEPROM: TForm_RearFromEEPROM
  Left = 545
  Top = 195
  AutoScroll = False
  Caption = #1047#1085#1072#1095#1077#1085#1080#1103', '#1089#1095#1080#1090#1072#1085#1085#1099#1077' '#1080#1079' EEPROM'
  ClientHeight = 676
  ClientWidth = 867
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object ScrollBox: TScrollBox
    Left = 0
    Top = 0
    Width = 867
    Height = 676
    Align = alClient
    Color = clSilver
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 0
    object Panel_for_Scrolling: TPanel
      Left = 0
      Top = 0
      Width = 851
      Height = 657
      BevelInner = bvLowered
      Color = clSilver
      TabOrder = 0
      object Label_string_01: TLabel
        Left = 13
        Top = 69
        Width = 763
        Height = 14
        Caption = 
          #1055#1086#1087#1091#1075#1072#1080'_'#1058#1077#1084#1087#1077#1088#1072#1090#1091#1088#1099' = '#1050#1086#1076'_'#1058#1077#1084#1087#1077#1088#1072#1090#1091#1088#1099' * K1 + A1 --> '#1050#1086#1076'_'#1058#1086#1082#1072'_'#1057#1074#1077 +
          #1090#1086#1076#1080#1086#1076#1072' = ('#1055#1086#1087#1091#1075#1072#1080'_'#1058#1086#1082#1072'_'#1057#1074#1077#1090#1086#1076#1080#1086#1076#1072' + A2) * K2'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
      end
      object Label_string_02: TLabel
        Left = 13
        Top = 85
        Width = 651
        Height = 14
        Caption = 
          #1041#1072#1085#1082' 0x30 (1) = '#1072#1076#1088#1077#1089' 0 ('#1055#1086#1087#1091#1075#1072#1080' '#1058#1077#1084#1087#1077#1088#1072#1090#1091#1088#1099' = 0) '#1085#1072#1093#1086#1076#1080#1090#1089#1103' '#1079#1085#1072#1095 +
          #1077#1085#1080#1077' '#1055#1086#1087#1091#1075#1072#1077#1074' '#1058#1086#1082#1072' '#1057#1074#1077#1090#1086#1076#1080#1086#1076#1072
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
      end
      object Label_string_03: TLabel
        Left = 13
        Top = 101
        Width = 658
        Height = 14
        Caption = 
          #1041#1072#1085#1082' 0x6F (4) = '#1072#1076#1088#1077#1089' 255 ('#1055#1086#1087#1091#1075#1072#1080' '#1058#1077#1084#1087#1077#1088#1072#1090#1091#1088#1099' = 255) '#1089#1086#1086#1090#1074'. '#1079#1085#1072 +
          #1095#1077#1085#1080#1077' '#1055#1086#1087#1091#1075#1072#1077#1074' '#1058#1086#1082#1072' '#1057#1074#1077#1090#1086#1076#1080#1086#1076#1072
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
      end
      object StringGrid_small: TStringGrid
        Left = 11
        Top = 17
        Width = 558
        Height = 42
        Color = clCream
        DefaultColWidth = 110
        DefaultRowHeight = 20
        FixedColor = clSilver
        RowCount = 2
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
        ParentFont = False
        TabOrder = 0
      end
      object Panel_attrBD: TPanel
        Left = 580
        Top = 121
        Width = 261
        Height = 265
        BevelInner = bvLowered
        Color = clSilver
        TabOrder = 1
        object Label_attr_01: TLabel
          Left = 10
          Top = 16
          Width = 154
          Height = 14
          Caption = #1048#1085#1076#1080#1074#1080#1076#1091#1072#1083#1100#1085#1099#1081' '#1072#1076#1088#1077#1089' ='
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'Courier New'
          Font.Style = []
          ParentFont = False
        end
        object Label_attr_02: TLabel
          Left = 10
          Top = 40
          Width = 154
          Height = 14
          Caption = '     '#1043#1088#1091#1087#1087#1086#1074#1086#1081' '#1072#1076#1088#1077#1089' ='
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'Courier New'
          Font.Style = []
          ParentFont = False
        end
        object Label_attr_03: TLabel
          Left = 10
          Top = 64
          Width = 154
          Height = 14
          Caption = '                 '#1044#1053#1059' ='
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'Courier New'
          Font.Style = []
          ParentFont = False
        end
        object Label_attr_04: TLabel
          Left = 10
          Top = 88
          Width = 154
          Height = 14
          Caption = '                 '#1044#1042#1059' ='
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'Courier New'
          Font.Style = []
          ParentFont = False
        end
        object Label_attr_05: TLabel
          Left = 10
          Top = 112
          Width = 154
          Height = 14
          Caption = '  '#1058#1086#1082' '#1089#1074#1077#1090'-'#1076#1072' '#1079#1072#1076#1072#1085'. ='
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'Courier New'
          Font.Style = []
          ParentFont = False
        end
        object Label_attr_06: TLabel
          Left = 10
          Top = 136
          Width = 154
          Height = 14
          Caption = '    '#1044#1083#1080#1090'. '#1064#1048#1052' '#1079#1072#1076#1072#1085'. ='
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'Courier New'
          Font.Style = []
          ParentFont = False
        end
        object Label_attr_07: TLabel
          Left = 10
          Top = 160
          Width = 154
          Height = 14
          Caption = #1055#1077#1088#1080#1086#1076' '#1064#1048#1052' '#1085#1072#1095#1072#1083#1100#1085#1099#1081' ='
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'Courier New'
          Font.Style = []
          ParentFont = False
        end
        object Label_attr_08: TLabel
          Left = 17
          Top = 184
          Width = 147
          Height = 14
          Caption = '    '#1055#1077#1088#1080#1086#1076' '#1064#1048#1052' '#1084#1080#1085'. ='
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'Courier New'
          Font.Style = []
          ParentFont = False
        end
        object Label_attr_09: TLabel
          Left = 10
          Top = 208
          Width = 154
          Height = 14
          Caption = #1047#1072#1076#1072#1085'. '#1086#1090#1082#1083'. '#1089#1074#1077#1090'-'#1076#1072' ='
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'Courier New'
          Font.Style = []
          ParentFont = False
        end
        object Label_attr_10: TLabel
          Left = 10
          Top = 232
          Width = 154
          Height = 14
          Caption = '                 SSP ='
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'Courier New'
          Font.Style = []
          ParentFont = False
        end
        object Edit_attr_01: TEdit
          Left = 172
          Top = 13
          Width = 78
          Height = 21
          Color = clCream
          TabOrder = 0
        end
        object Edit_attr_02: TEdit
          Left = 172
          Top = 37
          Width = 78
          Height = 21
          Color = clCream
          TabOrder = 1
        end
        object Edit_attr_03: TEdit
          Left = 172
          Top = 61
          Width = 78
          Height = 21
          Color = clCream
          TabOrder = 2
        end
        object Edit_attr_04: TEdit
          Left = 172
          Top = 85
          Width = 78
          Height = 21
          Color = clCream
          TabOrder = 3
        end
        object Edit_attr_05: TEdit
          Left = 172
          Top = 109
          Width = 78
          Height = 21
          Color = clCream
          TabOrder = 4
        end
        object Edit_attr_06: TEdit
          Left = 172
          Top = 133
          Width = 78
          Height = 21
          Color = clCream
          TabOrder = 5
        end
        object Edit_attr_07: TEdit
          Left = 172
          Top = 157
          Width = 78
          Height = 21
          Color = clCream
          TabOrder = 6
        end
        object Edit_attr_08: TEdit
          Left = 172
          Top = 181
          Width = 78
          Height = 21
          Color = clCream
          TabOrder = 7
        end
        object Edit_attr_09: TEdit
          Left = 172
          Top = 205
          Width = 78
          Height = 21
          Color = clCream
          TabOrder = 8
        end
        object Edit_attr_10: TEdit
          Left = 172
          Top = 229
          Width = 78
          Height = 21
          Color = clCream
          TabOrder = 9
        end
      end
      object StringGrid_large: TStringGrid
        Left = 12
        Top = 120
        Width = 559
        Height = 522
        Color = clCream
        DefaultColWidth = 105
        DefaultRowHeight = 16
        FixedColor = clSilver
        RowCount = 65
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
        ParentFont = False
        TabOrder = 2
      end
    end
  end
end
