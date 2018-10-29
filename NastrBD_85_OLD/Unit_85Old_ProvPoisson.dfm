object Form_85Old_Poisson: TForm_85Old_Poisson
  Left = 600
  Top = 181
  Width = 545
  Height = 215
  BorderIcons = []
  Caption = #1055#1059#1040#1057#1057#1054#1053' ('#1057#1095#1105#1090' '#1079#1072' '#1091#1089#1090#1072#1085#1086#1074#1083#1077#1085#1085#1099#1081' '#1074' '#1041#1044' '#1080#1085#1090#1077#1088#1074#1072#1083' '#1074#1088#1077#1084#1077#1085#1080')'
  Color = clSilver
  DragKind = dkDock
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010001002020100000000000E80200001600000028000000200000004000
    0000010004000000000080020000000000000000000000000000000000000000
    0000000080000080000000808000800000008000800080800000C0C0C0008080
    80000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF009000
    0000000000000000000000000000099900000000000000000000000000990009
    9900000000000000000000009900000009000000000000000000000990000000
    0990000000000000000000090000000000900000000000000000009900000000
    0009000000000000000000900000000000090000000000000000009000000000
    0009000000000000000000900000000000009000000000000000099000000000
    0000900000000000000009000000000000009000000000000000090000000000
    0000990000000000000009000000000000000900000000000000990000000000
    0000090000000000000090000000000000000900000000000000900000000000
    0000090000000000000090000000000000000900000000000000900000000000
    0000090000000000000090000000000000000990000000000000900000000000
    0000009000000000000090000000000000000090000000000009900000000000
    0000009900000000000900000000000000000009000000000009000000000000
    0000000990000000000900000000000000000000990000000099000000000000
    0000000009000000099000000000000000000000099000000900000000000000
    0000000000990000990000000000000000000000000990999000000000000000
    0000000000000000000000000000000000000000000000000000000000002AAA
    AAAA8AAAAAA8E2AAAAA3FAAAAAA7F8AAAAAFFCAAAA8FFEAAAA9FFEAAAA9FFEAA
    AA9FFF2AAA9FFF2AAABFFF2AAABFFF2AAABFFFAAAA3FFFAAAA7FFFAAAA7FFFAA
    AA7FFFAAAA7FFFAAAA7FFF8AAA7FFFCAAA7FFFCAAA7FFFCAAAFFFFEAAAFFFFE2
    AAFFFFF2A8FFFFFAA9FFFFF8ABFFFFFCA3FFFFFE07FFFFFFFFFFFFFFFFFF}
  OldCreateOrder = False
  Position = poScreenCenter
  PrintScale = poNone
  OnClose = ClosePoisson
  OnHide = FormHide
  OnShow = ShowPoisson
  PixelsPerInch = 96
  TextHeight = 13
  object Label54: TLabel
    Left = 61
    Top = 80
    Width = 379
    Height = 13
    Caption = 
      #1050#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090'=('#1044#1080#1089#1087#1077#1088#1089#1080#1103' - '#1057#1088#1077#1076#1085#1077#1077' '#1079#1085'.'#1089#1095#1105#1090#1072')/'#1057#1088#1077#1076#1085#1077#1077' '#1079#1085'.'#1080#1085#1090#1077#1085#1089#1080#1074#1085#1086 +
      #1089#1090#1080
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label34: TLabel
    Left = 104
    Top = 104
    Width = 117
    Height = 13
    Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1080#1089#1087#1099#1090#1072#1085#1080#1081
  end
  object Label36: TLabel
    Left = 16
    Top = 132
    Width = 218
    Height = 13
    Caption = #1060#1072#1081#1083' '#1089' '#1088#1077#1079#1091#1083#1100#1090#1072#1090#1072#1084#1080'(C:\'#1058#1057#1056#1052'\BD85\*.txt)'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 169
    Width = 530
    Height = 19
    Color = clSilver
    Panels = <
      item
        Width = 400
      end
      item
        Width = 50
      end>
    SimplePanel = False
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 24
    Width = 97
    Height = 49
    Caption = #1047#1085#1072#1095#1077#1085#1080#1077
    TabOrder = 1
    object Edit1: TEdit
      Left = 8
      Top = 16
      Width = 65
      Height = 21
      Color = clCream
      TabOrder = 0
    end
  end
  object Button1: TButton
    Left = 448
    Top = 112
    Width = 72
    Height = 25
    Caption = #1053#1040#1063#1040#1051#1048
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 448
    Top = 136
    Width = 72
    Height = 25
    Caption = #1057#1058#1054#1055
    TabOrder = 3
    OnClick = Button2Click
  end
  object GroupBox3: TGroupBox
    Left = 240
    Top = 24
    Width = 97
    Height = 49
    Caption = #1044#1080#1089#1087#1077#1088#1089#1080#1103
    TabOrder = 4
    object Edit17: TEdit
      Left = 8
      Top = 16
      Width = 65
      Height = 21
      Color = clCream
      TabOrder = 0
    end
  end
  object Button3: TButton
    Left = 448
    Top = 40
    Width = 75
    Height = 25
    Caption = #1043#1088#1072#1092#1080#1082' '
    DragKind = dkDock
    TabOrder = 5
    OnClick = Button3Click
  end
  object Edit0: TEdit
    Left = 224
    Top = 96
    Width = 89
    Height = 21
    Color = clCream
    TabOrder = 6
    Text = '10000'
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 521
    Height = 9
    BevelInner = bvLowered
    Color = clMedGray
    DragKind = dkDock
    TabOrder = 7
  end
  object Panel2: TPanel
    Left = 9
    Top = 160
    Width = 521
    Height = 9
    BevelInner = bvLowered
    Color = clMedGray
    DragKind = dkDock
    TabOrder = 8
  end
  object Panel3: TPanel
    Left = 0
    Top = 0
    Width = 9
    Height = 169
    BevelInner = bvLowered
    Color = clMedGray
    DragKind = dkDock
    TabOrder = 9
  end
  object Panel4: TPanel
    Left = 520
    Top = 0
    Width = 9
    Height = 169
    BevelInner = bvLowered
    Color = clMedGray
    DragKind = dkDock
    TabOrder = 10
  end
  object Button11: TButton
    Left = 448
    Top = 8
    Width = 75
    Height = 17
    Caption = #1042#1099#1093#1086#1076
    TabOrder = 11
    OnClick = Button11Click
  end
  object Edit33: TEdit
    Left = 248
    Top = 128
    Width = 177
    Height = 21
    TabOrder = 12
    Text = 'poissonBD85.txt'
  end
  object GroupBox4: TGroupBox
    Left = 344
    Top = 24
    Width = 97
    Height = 49
    Caption = #1050#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090
    TabOrder = 13
    object Edit25: TEdit
      Left = 8
      Top = 16
      Width = 65
      Height = 21
      Color = clCream
      TabOrder = 0
    end
  end
  object GroupBox2: TGroupBox
    Left = 128
    Top = 24
    Width = 105
    Height = 49
    Caption = #1057#1088#1077#1076#1085#1077#1077' '#1079#1085'.'
    TabOrder = 14
    object Edit9: TEdit
      Left = 8
      Top = 16
      Width = 65
      Height = 21
      Color = clCream
      TabOrder = 0
    end
  end
end
