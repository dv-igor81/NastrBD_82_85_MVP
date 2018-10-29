object Form_85Old_Main: TForm_85Old_Main
  Left = 264
  Top = 101
  Width = 824
  Height = 698
  BorderWidth = 1
  Caption = '--- '#1085#1072#1076#1087#1080#1089#1100' '#1092#1086#1088#1084#1080#1088#1091#1077#1090#1089#1103' '#1085#1072' '#1101#1090#1072#1087#1077' '#1074#1099#1087#1086#1083#1085#1077#1085#1080#1103' ---'
  Color = clSilver
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clBlack
  Font.Height = -12
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010001002020100000000000E80200001600000028000000200000004000
    0000010004000000000080020000000000000000000000000000000000000000
    0000000080000080000000808000800000008000800080800000C0C0C0008080
    80000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000011011111110101000000000000000000110
    1111111010110000000000000000011011111110101111000000000000000111
    1111111110111110000000000000011111111111101111110000000000000111
    1111111110111111110000000000011111111111101111111110000000000000
    0000000000111111111100000000011111111111110011111111100000000011
    1111111111110111111111100000000011111111111110011111111100000000
    0111111111111110111111111000000000111111111111110011111111000000
    0000111111111111110111111110000000000111111111111110011111100000
    0000001111111111111110111110000000000000111111111111110011100000
    0000000001111111111111110110000000000000001111111111111110000000
    000000000000111111111111111000000000000000000000000000000000FFF7
    FBFFFFE7F3FFFFCFF7FFFF9FC7FFFFBF9FFFFE7FBFFFF8FF7FFFF3F8FFFFE7E3
    FFFFEFEFFFFF0001FFFF0000FFFF00003FFF00001FFF00000FFF000003FF0000
    01FF000000FF0000007F0000001F8000000FC0000007F0000003F8000001FC00
    0000FF000000FF800000FFC00000FFF00000FFF80000FFFC0000FFFF0000}
  OldCreateOrder = False
  Position = poScreenCenter
  PrintScale = poNone
  Scaled = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label4: TLabel
    Left = 600
    Top = 576
    Width = 49
    Height = 16
    Caption = #1042#1045#1056#1057#1048#1071' '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -12
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label1: TLabel
    Left = 515
    Top = 547
    Width = 98
    Height = 16
    Caption = #1054#1073#1088#1072#1090#1085#1072#1103' '#1089#1074#1103#1079#1100
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -12
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label18: TLabel
    Left = 584
    Top = 504
    Width = 104
    Height = 16
    Caption = #1057#1086#1089#1090#1086#1103#1085#1080#1077' '#1041#1044':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = [fsBold, fsUnderline]
    ParentFont = False
  end
  object GroupBox1: TGroupBox
    Left = 496
    Top = 216
    Width = 273
    Height = 121
    Caption = #1055#1086#1076#1082#1083#1102#1095#1077#1085#1080#1077
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    object COMLabel: TLabel
      Left = 172
      Top = 27
      Width = 24
      Height = 16
      Caption = 'COM'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label2: TLabel
      Left = 27
      Top = 56
      Width = 168
      Height = 16
      Caption = #1048#1085#1076#1080#1074#1080#1076#1091#1072#1083#1100#1085'.'#1072#1076#1088#1077#1089' '#1041#1044
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object OpenPortButton: TButton
      Left = 88
      Top = 85
      Width = 89
      Height = 25
      Cursor = crHandPoint
      Caption = #1054#1058#1050#1056#1067#1058#1068
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnClick = OpenPortButtonClick
    end
    object Edit5: TEdit
      Left = 200
      Top = 24
      Width = 33
      Height = 24
      Color = clCream
      TabOrder = 1
      Text = '1'
    end
    object UpDown1: TUpDown
      Left = 233
      Top = 24
      Width = 15
      Height = 24
      Associate = Edit5
      Min = 1
      Max = 255
      Position = 1
      TabOrder = 2
      Wrap = False
    end
    object NewConnectionAdr: TEdit
      Left = 200
      Top = 52
      Width = 33
      Height = 24
      Color = clCream
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      Text = '63'
    end
    object UpDown3: TUpDown
      Left = 233
      Top = 52
      Width = 15
      Height = 24
      Associate = NewConnectionAdr
      Min = 0
      Max = 63
      Position = 63
      TabOrder = 4
      Wrap = False
    end
  end
  object DataFromDetGroupBox: TGroupBox
    Left = 14
    Top = 8
    Width = 447
    Height = 233
    Caption = #1048#1085#1092#1086#1088#1084#1072#1094#1080#1103' '#1089' '#1041#1044
    Ctl3D = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -12
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 1
    object IndAdrEdit: TEdit
      Left = 318
      Top = 39
      Width = 75
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 0
    end
    object IndAdrPanel: TPanel
      Left = 8
      Top = 39
      Width = 241
      Height = 20
      Alignment = taLeftJustify
      BorderWidth = 1
      Caption = ' '#1048#1085#1076#1080#1074#1080#1076#1091#1072#1083#1100#1085#1099#1081' '#1072#1076#1088#1077#1089
      Color = clSilver
      Ctl3D = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 1
    end
    object ParamColPanel: TPanel
      Left = 8
      Top = 16
      Width = 241
      Height = 20
      Alignment = taLeftJustify
      BorderWidth = 1
      Caption = '                     '#1055#1040#1056#1040#1052#1045#1058#1056
      Color = clSilver
      Ctl3D = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Pitch = fpFixed
      Font.Style = [fsBold]
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 2
    end
    object GrpAdrPanel: TPanel
      Left = 8
      Top = 62
      Width = 241
      Height = 20
      Alignment = taLeftJustify
      BorderWidth = 1
      Caption = ' '#1043#1088#1091#1087#1087#1086#1074#1086#1081' '#1072#1076#1088#1077#1089
      Color = clSilver
      Ctl3D = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 3
    end
    object CodeColPanel: TPanel
      Left = 249
      Top = 16
      Width = 68
      Height = 20
      Alignment = taLeftJustify
      Caption = '     '#1050#1054#1044
      Color = clSilver
      Ctl3D = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 4
    end
    object GrpAdrEdit: TEdit
      Left = 318
      Top = 62
      Width = 75
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 5
    end
    object TprPanel: TPanel
      Left = 8
      Top = 85
      Width = 241
      Height = 20
      Alignment = taLeftJustify
      BorderWidth = 1
      Caption = ' '#1058#1077#1084#1087#1077#1088#1072#1090#1091#1088#1072' '#1087#1088#1086#1094#1077#1089#1089#1086#1088#1072' '
      Color = clSilver
      Ctl3D = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 6
    end
    object UhiIPanel: TPanel
      Left = 8
      Top = 133
      Width = 241
      Height = 20
      Alignment = taLeftJustify
      BorderWidth = 1
      Caption = ' '#1053#1072#1087#1088#1103#1078#1077#1085#1080#1077' '#1042#1067#1057#1054#1050#1054#1045' '#1080#1079#1084#1077#1088#1077#1085#1085#1086#1077' '
      Color = clSilver
      Ctl3D = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 7
    end
    object DNUIPanel: TPanel
      Left = 8
      Top = 109
      Width = 241
      Height = 20
      Alignment = taLeftJustify
      BorderWidth = 1
      Caption = ' '#1047#1085#1072#1095#1077#1085#1080#1077' '#1044#1053#1059' '#1080#1079#1084#1077#1088#1077#1085#1085#1086#1077' '
      Color = clSilver
      Ctl3D = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 8
    end
    object TprCodeEdit: TEdit
      Left = 250
      Top = 85
      Width = 67
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 9
    end
    object UhiICodeEdit: TEdit
      Left = 250
      Top = 133
      Width = 67
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 10
    end
    object DNUICodeEdit: TEdit
      Left = 250
      Top = 109
      Width = 67
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 11
    end
    object ValueCodePanel: TPanel
      Left = 317
      Top = 16
      Width = 76
      Height = 20
      Alignment = taLeftJustify
      Caption = ' '#1047#1053#1040#1063#1045#1053#1048#1045
      Color = clSilver
      Ctl3D = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 12
    end
    object TprEdit: TEdit
      Left = 318
      Top = 85
      Width = 75
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 13
    end
    object UhiIEdit: TEdit
      Left = 318
      Top = 133
      Width = 75
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 14
    end
    object DNUIEdit: TEdit
      Left = 318
      Top = 109
      Width = 75
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 15
    end
    object UnitPanel: TPanel
      Left = 393
      Top = 16
      Width = 44
      Height = 20
      Alignment = taLeftJustify
      Caption = '   '#1045#1048
      Color = clSilver
      Ctl3D = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 16
    end
    object TprUnitEdit: TEdit
      Left = 394
      Top = 85
      Width = 43
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 17
      Text = '  '#176'C'
    end
    object UhiIUnitEdit: TEdit
      Left = 394
      Top = 133
      Width = 43
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 18
      Text = '   '#1042
    end
    object DNUIUnitEdit: TEdit
      Left = 394
      Top = 109
      Width = 43
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 19
      Text = '   '#1042
    end
    object EmptyPanel01: TPanel
      Left = 249
      Top = 39
      Width = 68
      Height = 20
      Color = clSilver
      TabOrder = 20
    end
    object EmptyPanel02: TPanel
      Left = 249
      Top = 62
      Width = 68
      Height = 20
      Color = clSilver
      TabOrder = 21
    end
    object EmptyPanel07: TPanel
      Left = 394
      Top = 39
      Width = 43
      Height = 20
      Color = clSilver
      TabOrder = 22
    end
    object EmptyPanel08: TPanel
      Left = 394
      Top = 62
      Width = 43
      Height = 20
      Color = clSilver
      TabOrder = 23
    end
    object Panel1: TPanel
      Left = 8
      Top = 158
      Width = 241
      Height = 20
      Alignment = taLeftJustify
      BorderWidth = 1
      Caption = ' '#1044#1083#1080#1090#1077#1083#1100#1085#1086#1089#1090#1100' '#1064#1048#1052
      Color = clSilver
      Ctl3D = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 24
    end
    object EditSIMd: TEdit
      Left = 250
      Top = 158
      Width = 67
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 25
    end
    object Edit2: TEdit
      Left = 394
      Top = 158
      Width = 43
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 26
      Text = '  '#1084#1082#1089
    end
    object Panel15: TPanel
      Left = 8
      Top = 181
      Width = 241
      Height = 20
      Alignment = taLeftJustify
      BorderWidth = 1
      Caption = ' '#1055#1077#1088#1080#1086#1076' '#1064#1048#1052' '
      Color = clSilver
      Ctl3D = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 27
    end
    object EditSIMp: TEdit
      Left = 250
      Top = 180
      Width = 67
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 28
    end
    object EditSIM3zn: TEdit
      Left = 318
      Top = 180
      Width = 75
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 29
    end
    object Edit9: TEdit
      Left = 394
      Top = 180
      Width = 43
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 30
      Text = '  '#1084#1082#1089
    end
    object Edit4: TEdit
      Left = 318
      Top = 158
      Width = 75
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 31
    end
    object Panel16: TPanel
      Left = 8
      Top = 205
      Width = 241
      Height = 20
      Alignment = taLeftJustify
      BorderWidth = 1
      Caption = ' '#1057#1095#1077#1090' '#1089' '#1041#1044' '#1079#1072' 1 '#1089#1077#1082' '
      Color = clSilver
      Ctl3D = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 32
    end
    object Panel18: TPanel
      Left = 249
      Top = 205
      Width = 68
      Height = 20
      Color = clSilver
      TabOrder = 33
    end
    object Edit14: TEdit
      Left = 318
      Top = 204
      Width = 75
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 34
    end
    object Edit15: TEdit
      Left = 394
      Top = 204
      Width = 43
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 35
      Text = #1080#1084#1087'/'#1089
    end
  end
  object DataForDetBox: TGroupBox
    Left = 16
    Top = 400
    Width = 447
    Height = 233
    Caption = #1059#1089#1090#1072#1085#1086#1074#1082#1072' '#1087#1072#1088#1072#1084#1077#1090#1088#1086#1074' '#1041#1044
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -12
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    object SetDNUEdit: TMaskEdit
      Left = 318
      Top = 79
      Width = 79
      Height = 20
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 0
    end
    object SetIndAdrPanel: TPanel
      Left = 8
      Top = 37
      Width = 241
      Height = 20
      Alignment = taLeftJustify
      BorderWidth = 1
      Caption = ' '#1048#1085#1076#1080#1074#1080#1076#1091#1072#1083#1100#1085#1099#1081' '#1072#1076#1088#1077#1089
      Color = clSilver
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 1
    end
    object SetGrpAdrPanel: TPanel
      Left = 8
      Top = 58
      Width = 241
      Height = 20
      Alignment = taLeftJustify
      BorderWidth = 1
      Caption = ' '#1043#1088#1091#1087#1087#1086#1074#1086#1081' '#1072#1076#1088#1077#1089' '
      Color = clSilver
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
    object SetDNUPanel: TPanel
      Left = 8
      Top = 79
      Width = 241
      Height = 22
      Alignment = taLeftJustify
      BorderWidth = 1
      Caption = ' '#1047#1085#1072#1095#1077#1085#1080#1077' '#1044#1053#1059' '#1079#1072#1076#1072#1085#1085#1086#1077' '
      Color = clSilver
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object SetUhiPanel: TPanel
      Left = 8
      Top = 102
      Width = 241
      Height = 20
      Alignment = taLeftJustify
      BorderWidth = 1
      Caption = ' '#1053#1072#1087#1088#1103#1078#1077#1085#1080#1077' '#1042#1067#1057#1054#1050#1054#1045' '#1079#1072#1076#1072#1085#1085#1086#1077' '
      Color = clSilver
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
    end
    object SetParamColPanel: TPanel
      Left = 8
      Top = 16
      Width = 241
      Height = 20
      BorderWidth = 1
      Caption = #1055#1040#1056#1040#1052#1045#1058#1056
      Color = clSilver
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 5
    end
    object SetCodeColPanel: TPanel
      Left = 250
      Top = 16
      Width = 67
      Height = 20
      BorderWidth = 1
      Caption = #1050#1054#1044
      Color = clSilver
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 6
    end
    object SetValueColPanel: TPanel
      Left = 318
      Top = 16
      Width = 79
      Height = 20
      BorderWidth = 1
      Caption = #1047#1053#1040#1063#1045#1053#1048#1045
      Color = clSilver
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 7
    end
    object SetUhiEdit: TMaskEdit
      Left = 318
      Top = 102
      Width = 79
      Height = 20
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 8
    end
    object SetIndAdrEdit: TEdit
      Left = 318
      Top = 37
      Width = 79
      Height = 20
      Color = clCream
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 9
    end
    object SetGrpAdrEdit: TEdit
      Left = 318
      Top = 58
      Width = 79
      Height = 20
      Color = clCream
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 10
    end
    object SetDNUCodeEdit: TEdit
      Left = 250
      Top = 79
      Width = 67
      Height = 20
      Color = clCream
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 11
    end
    object SetUhiCodeEdit: TEdit
      Left = 250
      Top = 102
      Width = 67
      Height = 20
      Color = clCream
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 12
    end
    object EmptyPanel09: TPanel
      Left = 250
      Top = 37
      Width = 67
      Height = 20
      Color = clSilver
      TabOrder = 13
    end
    object EmptyPanel10: TPanel
      Left = 250
      Top = 58
      Width = 67
      Height = 20
      Color = clSilver
      TabOrder = 14
    end
    object Panel3: TPanel
      Left = 398
      Top = 16
      Width = 44
      Height = 20
      Alignment = taLeftJustify
      Caption = '   '#1045#1048
      Color = clSilver
      Ctl3D = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 15
    end
    object Panel4: TPanel
      Left = 398
      Top = 37
      Width = 43
      Height = 20
      Color = clSilver
      TabOrder = 16
    end
    object Panel5: TPanel
      Left = 398
      Top = 58
      Width = 43
      Height = 20
      Color = clSilver
      TabOrder = 17
    end
    object Edit1: TEdit
      Left = 398
      Top = 80
      Width = 43
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 18
      Text = '   '#1042
    end
    object Edit3: TEdit
      Left = 398
      Top = 102
      Width = 43
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 19
      Text = '   '#1042
    end
    object Panel12: TPanel
      Left = 8
      Top = 124
      Width = 241
      Height = 20
      Alignment = taLeftJustify
      BorderWidth = 1
      Caption = ' '#1044#1083#1080#1090#1077#1083#1100#1085#1086#1089#1090#1100' '#1064#1048#1052' - '#1085#1072#1095#1072#1083#1100#1085'.'#1090#1086#1095#1082#1072
      Color = clSilver
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      TabOrder = 20
    end
    object Panel28: TPanel
      Left = 8
      Top = 146
      Width = 241
      Height = 20
      Alignment = taLeftJustify
      BorderWidth = 1
      Caption = ' '#1044#1083#1080#1090#1077#1083#1100#1085#1086#1089#1090#1100' '#1064#1048#1052' - '#1084#1072#1082#1089#1080#1084'.'#1090#1086#1095#1082#1072
      Color = clSilver
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      TabOrder = 21
    end
    object Edit6: TEdit
      Left = 250
      Top = 124
      Width = 67
      Height = 20
      Color = clCream
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 22
    end
    object Edit18: TEdit
      Left = 250
      Top = 146
      Width = 67
      Height = 20
      Color = clCream
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 23
    end
    object Panel14: TPanel
      Left = 318
      Top = 124
      Width = 78
      Height = 20
      Color = clSilver
      TabOrder = 24
    end
    object Panel29: TPanel
      Left = 318
      Top = 146
      Width = 78
      Height = 20
      Color = clSilver
      TabOrder = 25
    end
    object Edit8: TEdit
      Left = 398
      Top = 124
      Width = 43
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 26
      Text = ' '#1077#1076'.'
    end
    object Edit19: TEdit
      Left = 398
      Top = 146
      Width = 43
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 27
      Text = ' '#1077#1076'.'
    end
    object GroupBox7: TGroupBox
      Left = 8
      Top = 184
      Width = 170
      Height = 43
      Caption = #1054#1073#1088#1072#1090#1085#1072#1103' '#1089#1074#1103#1079#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 28
      object RS1: TRadioButton
        Left = 8
        Top = 12
        Width = 89
        Height = 17
        Cursor = crHandPoint
        Caption = #1042#1082#1083#1102#1095#1077#1085#1072
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
      end
      object RS3: TRadioButton
        Left = 8
        Top = 25
        Width = 97
        Height = 17
        Cursor = crHandPoint
        Caption = #1042#1099#1082#1083#1102#1095#1077#1085#1072
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
      end
    end
    object Panel19: TPanel
      Left = 8
      Top = 167
      Width = 241
      Height = 20
      Alignment = taLeftJustify
      BorderWidth = 1
      Caption = ' '#1055#1077#1088#1080#1086#1076' '#1064#1048#1052
      Color = clSilver
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      TabOrder = 29
    end
    object Edit16: TEdit
      Left = 250
      Top = 167
      Width = 67
      Height = 20
      Color = clCream
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 30
    end
    object Panel20: TPanel
      Left = 318
      Top = 167
      Width = 78
      Height = 20
      Color = clSilver
      TabOrder = 31
    end
    object Edit17: TEdit
      Left = 396
      Top = 167
      Width = 43
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 32
      Text = ' '#1077#1076'.'
    end
  end
  object SetParamButton: TButton
    Left = 209
    Top = 597
    Width = 240
    Height = 30
    Cursor = crHandPoint
    Caption = #1047#1072#1087#1080#1089#1100' '#1087#1072#1088#1072#1084#1077#1090#1088#1086#1074
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    OnClick = SetParamButtonClick
  end
  object GroupBox2: TGroupBox
    Left = 16
    Top = 248
    Width = 447
    Height = 137
    Caption = #1055#1086#1083#1091#1095#1077#1085#1080#1077' '#1089#1095#1105#1090#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -12
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
    object Label3: TLabel
      Left = 112
      Top = 16
      Width = 126
      Height = 15
      Caption = #1042#1088#1077#1084#1103' '#1080#1079#1084#1077#1088#1077#1085#1080#1103','#1089'='
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
    end
    object SumCountPanel: TPanel
      Left = 8
      Top = 61
      Width = 241
      Height = 20
      Alignment = taLeftJustify
      BorderWidth = 1
      Caption = ' '#1057#1091#1084#1084#1072#1088#1085#1099#1081' '#1089#1095#1077#1090' '#1079#1072' '#1074#1088#1077#1084#1103' '#1080#1079#1084#1077#1088#1077#1085#1080#1103' '
      Color = clSilver
      Ctl3D = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 0
    end
    object TCountPanel: TPanel
      Left = 8
      Top = 85
      Width = 241
      Height = 20
      Alignment = taLeftJustify
      BorderWidth = 1
      Caption = ' '#1058#1077#1082#1091#1097#1077#1077' '#1074#1088#1077#1084#1103' '#1089#1095#1077#1090#1072' '#1080#1084#1087#1091#1083#1100#1089#1086#1074' '
      Color = clSilver
      Ctl3D = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 1
    end
    object EmptyPanel05: TPanel
      Left = 249
      Top = 61
      Width = 68
      Height = 20
      Color = clSilver
      TabOrder = 2
    end
    object EmptyPanel06: TPanel
      Left = 249
      Top = 85
      Width = 68
      Height = 20
      Color = clSilver
      TabOrder = 3
    end
    object SumCountEdit: TEdit
      Left = 318
      Top = 62
      Width = 75
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 4
    end
    object TCountEdit: TEdit
      Left = 318
      Top = 86
      Width = 75
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 5
    end
    object SumCountUnitEdit: TEdit
      Left = 394
      Top = 62
      Width = 43
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 6
      Text = ' '#1080#1084#1087
    end
    object TCountUnitEdit: TEdit
      Left = 394
      Top = 86
      Width = 43
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 7
      Text = '  '#1089
    end
    object T_LimitEdit: TEdit
      Left = 248
      Top = 12
      Width = 68
      Height = 23
      Color = clCream
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      TabOrder = 8
      Text = '200'
    end
    object SetResetButton: TButton
      Left = 8
      Top = 108
      Width = 57
      Height = 25
      Cursor = crHandPoint
      Caption = #1057#1073#1088#1086#1089
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 9
      OnClick = SetResetButtonClick
    end
    object StartCountButton: TButton
      Left = 64
      Top = 108
      Width = 57
      Height = 25
      Cursor = crHandPoint
      Caption = #1057#1058#1040#1056#1058
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 10
      OnClick = StartCountButtonClick
    end
    object Count1Panel: TPanel
      Left = 8
      Top = 37
      Width = 241
      Height = 20
      Alignment = taLeftJustify
      BorderWidth = 1
      Caption = ' '#1057#1095#1077#1090' '#1089' '#1041#1044' '#1079#1072' 1 '#1089#1077#1082' '
      Color = clSilver
      Ctl3D = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 11
    end
    object EmptyPanel04: TPanel
      Left = 249
      Top = 37
      Width = 68
      Height = 20
      Color = clSilver
      TabOrder = 12
    end
    object Count1Edit: TEdit
      Left = 318
      Top = 38
      Width = 75
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 13
    end
    object Count1UnitEdit: TEdit
      Left = 394
      Top = 38
      Width = 43
      Height = 21
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 14
      Text = #1080#1084#1087'/'#1089
    end
  end
  object Button5: TButton
    Left = 560
    Top = 392
    Width = 129
    Height = 33
    Caption = #1055#1059#1040#1057#1057#1054#1053
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 5
    OnClick = Button5Click
  end
  object Panel13: TPanel
    Left = -43
    Top = 0
    Width = 836
    Height = 9
    BevelInner = bvLowered
    Color = clGray
    TabOrder = 6
  end
  object Panel33: TPanel
    Left = 470
    Top = -140
    Width = 9
    Height = 781
    BevelInner = bvLowered
    Color = clGray
    TabOrder = 7
  end
  object Panel6: TPanel
    Left = 0
    Top = -140
    Width = 9
    Height = 781
    BevelInner = bvLowered
    Color = clGray
    TabOrder = 8
  end
  object Panel8: TPanel
    Left = -27
    Top = 632
    Width = 828
    Height = 9
    BevelInner = bvLowered
    Color = clGray
    TabOrder = 9
  end
  object Panel9: TPanel
    Left = -3
    Top = 240
    Width = 484
    Height = 9
    BevelInner = bvLowered
    Color = clGray
    TabOrder = 10
  end
  object Panel10: TPanel
    Left = -3
    Top = 392
    Width = 484
    Height = 9
    BevelInner = bvLowered
    Color = clGray
    TabOrder = 11
  end
  object Edit7: TEdit
    Left = 584
    Top = 600
    Width = 25
    Height = 24
    Color = clMoneyGreen
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -12
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 12
  end
  object Edit11: TEdit
    Left = 608
    Top = 600
    Width = 25
    Height = 24
    Color = clMoneyGreen
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -12
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 13
  end
  object Edit12: TEdit
    Left = 632
    Top = 600
    Width = 25
    Height = 24
    Color = clMoneyGreen
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -12
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 14
  end
  object Edit13: TEdit
    Left = 656
    Top = 600
    Width = 25
    Height = 24
    Color = clMoneyGreen
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -12
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 15
  end
  object Panel11: TPanel
    Left = 472
    Top = 488
    Width = 328
    Height = 9
    BevelInner = bvLowered
    Color = clGray
    TabOrder = 16
  end
  object Panel7: TPanel
    Left = 791
    Top = -140
    Width = 9
    Height = 781
    BevelInner = bvLowered
    Color = clGray
    TabOrder = 17
  end
  object Panel17: TPanel
    Left = 482
    Top = 16
    Width = 305
    Height = 145
    BevelInner = bvLowered
    Color = clSilver
    TabOrder = 18
    object Label5: TLabel
      Left = 2
      Top = 20
      Width = 117
      Height = 13
      Caption = '6'#1073#1080#1090' - '#1087#1088#1080#1079#1085#1072#1082' SSP'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label9: TLabel
      Left = 2
      Top = 44
      Width = 267
      Height = 13
      Caption = '4'#1073#1080#1090' - '#1092#1083#1072#1075' '#1091#1087#1088#1072#1074#1083#1077#1085'.'#1086#1073#1088#1072#1090#1085'.'#1089#1074#1103#1079#1100#1102'(0-'#1077#1089#1090#1100')'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label10: TLabel
      Left = 2
      Top = 84
      Width = 241
      Height = 13
      Caption = '1'#1073#1080#1090' - '#1087#1088#1080#1079#1085#1072#1082' '#1085#1077' '#1089#1085#1103#1090#1086#1075#1086' '#1089#1095#1105#1090#1072'(1-'#1077#1089#1090#1100')'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label11: TLabel
      Left = 2
      Top = 98
      Width = 243
      Height = 13
      Caption = '0'#1073#1080#1090' - '#1087#1088#1080#1079#1085#1072#1082' '#1075#1086#1090#1086#1074#1085#1086#1089#1090#1080' '#1089#1095#1105#1090#1072'(1-'#1077#1089#1090#1100')'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label8: TLabel
      Left = 2
      Top = 70
      Width = 140
      Height = 13
      Caption = '2'#1073#1080#1090' - '#1085#1077' '#1080#1089#1087#1086#1083#1100#1079#1091#1077#1090#1089#1103
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label12: TLabel
      Left = 2
      Top = 56
      Width = 140
      Height = 13
      Caption = '3'#1073#1080#1090' - '#1085#1077' '#1080#1089#1087#1086#1083#1100#1079#1091#1077#1090#1089#1103
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label13: TLabel
      Left = 2
      Top = 32
      Width = 140
      Height = 13
      Caption = '5'#1073#1080#1090' - '#1085#1077' '#1080#1089#1087#1086#1083#1100#1079#1091#1077#1090#1089#1103
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label14: TLabel
      Left = 2
      Top = 8
      Width = 140
      Height = 13
      Caption = '7'#1073#1080#1090' - '#1085#1077' '#1080#1089#1087#1086#1083#1100#1079#1091#1077#1090#1089#1103
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label15: TLabel
      Left = 8
      Top = 114
      Width = 33
      Height = 22
      Caption = 'SSP'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -19
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label16: TLabel
      Left = 46
      Top = 115
      Width = 11
      Height = 22
      Caption = '='
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label17: TLabel
      Left = 102
      Top = 115
      Width = 11
      Height = 22
      Caption = '='
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Edit23: TEdit
      Left = 58
      Top = 116
      Width = 39
      Height = 22
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 0
    end
    object Edit10: TEdit
      Left = 120
      Top = 116
      Width = 79
      Height = 22
      Color = clMoneyGreen
      Ctl3D = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 1
    end
  end
  object Panel2: TPanel
    Left = 470
    Top = 168
    Width = 327
    Height = 9
    BevelInner = bvLowered
    Color = clGray
    TabOrder = 19
  end
  object ARCH_Con: TBitBtn
    Left = 624
    Top = 535
    Width = 121
    Height = 28
    Caption = #1054#1090#1082#1083#1102#1095#1077#1085#1086
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -12
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 20
    Kind = bkNo
  end
end
