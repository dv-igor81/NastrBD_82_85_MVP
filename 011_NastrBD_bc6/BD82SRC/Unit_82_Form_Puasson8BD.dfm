object FormPuasson8BD: TFormPuasson8BD
  Left = 271
  Top = 289
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = #1055#1091#1072#1089#1089#1086#1085
  ClientHeight = 412
  ClientWidth = 824
  Color = clBtnFace
  Constraints.MaxHeight = 450
  Constraints.MaxWidth = 840
  Constraints.MinHeight = 450
  Constraints.MinWidth = 840
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object ScrollBoxMain: TScrollBox
    Left = 0
    Top = 0
    Width = 824
    Height = 412
    Align = alClient
    TabOrder = 0
    object GroupBoxMain: TGroupBox
      Left = 8
      Top = 8
      Width = 809
      Height = 393
      Caption = ' '#1055#1091#1072#1089#1089#1086#1085' '
      TabOrder = 0
      object Label_sernum: TLabel
        Left = 674
        Top = 76
        Width = 86
        Height = 13
        Caption = #1057#1077#1088#1080#1081#1085#1099#1081' '#1085#1086#1084#1077#1088
      end
      object Label_addr_BD: TLabel
        Left = 603
        Top = 76
        Width = 31
        Height = 13
        Caption = #1040#1076#1088#1077#1089
      end
      object Label_Time: TLabel
        Left = 17
        Top = 18
        Width = 142
        Height = 13
        Caption = #1050#1086#1083'-'#1074#1086' '#1080#1089#1087#1099#1090#1072#1085#1080#1081' ['#1090#1099#1089'. '#1096#1090'.]'
      end
      object Label_info: TLabel
        Left = 451
        Top = 316
        Width = 308
        Height = 13
        Caption = '(1) - '#1084#1072#1082#1089#1080#1084#1072#1083#1100#1085#1086#1077' '#1074#1088#1077#1084#1103' '#1086#1078#1080#1076#1072#1085#1080#1103' '#1087#1086#1089#1099#1083#1082#1080'-'#1086#1090#1074#1077#1090#1072' ['#1084#1057#1077#1082'.]'
      end
      object Label_readTimeout: TLabel
        Left = 194
        Top = 18
        Width = 58
        Height = 13
        Caption = #1058#1072#1081#1084#1072#1091#1090' (1)'
      end
      object Label_Time_Diapazon: TLabel
        Left = 17
        Top = 54
        Width = 39
        Height = 13
        Caption = '1 ... 300'
      end
      object Panel_Display_BD1: TPanel
        Left = 8
        Top = 91
        Width = 538
        Height = 25
        Alignment = taLeftJustify
        BevelInner = bvLowered
        TabOrder = 0
        object Label_SchetSek01: TLabel
          Left = 8
          Top = 6
          Width = 84
          Height = 13
          Caption = #1057#1095#1105#1090' '#1079#1072' '#1089#1077#1082#1091#1085#1076#1091':'
        end
        object Label_PNSch01: TLabel
          Left = 144
          Top = 6
          Width = 97
          Height = 13
          Caption = #1087#1088#1080#1079#1085'. '#1085#1077#1089#1085'. '#1089#1095#1105#1090#1072':'
        end
        object Label_KvoIsp01: TLabel
          Left = 299
          Top = 5
          Width = 94
          Height = 13
          Caption = #1082#1086#1083'-'#1074#1086' '#1080#1089#1087#1099#1090#1072#1085#1080#1081':'
        end
        object Edit_SchetSek01: TEdit
          Left = 97
          Top = 3
          Width = 43
          Height = 21
          Color = clInfoBk
          Enabled = False
          ReadOnly = True
          TabOrder = 0
        end
        object Edit_PNSch01: TEdit
          Left = 247
          Top = 3
          Width = 47
          Height = 21
          Color = clInfoBk
          Enabled = False
          ReadOnly = True
          TabOrder = 1
        end
        object Edit_KvoIsp01: TEdit
          Left = 399
          Top = 3
          Width = 50
          Height = 21
          Color = clInfoBk
          Enabled = False
          ReadOnly = True
          TabOrder = 2
        end
      end
      object Edit_SN8: TEdit
        Left = 674
        Top = 274
        Width = 81
        Height = 21
        ReadOnly = True
        TabOrder = 1
      end
      object Edit_SN7: TEdit
        Left = 674
        Top = 247
        Width = 81
        Height = 21
        ReadOnly = True
        TabOrder = 2
      end
      object CheckBox_AddrBD7: TCheckBox
        Left = 551
        Top = 249
        Width = 48
        Height = 17
        Caption = #1041#1044'7'
        TabOrder = 3
      end
      object Edit_SN6: TEdit
        Left = 674
        Top = 221
        Width = 81
        Height = 21
        ReadOnly = True
        TabOrder = 4
      end
      object CheckBox_AddrBD6: TCheckBox
        Left = 551
        Top = 223
        Width = 48
        Height = 17
        Caption = #1041#1044'6'
        TabOrder = 5
      end
      object Edit_SN5: TEdit
        Left = 674
        Top = 194
        Width = 81
        Height = 21
        ReadOnly = True
        TabOrder = 6
      end
      object CheckBox_AddrBD5: TCheckBox
        Left = 551
        Top = 197
        Width = 48
        Height = 17
        Caption = #1041#1044'5'
        TabOrder = 7
      end
      object Edit_SN4: TEdit
        Left = 674
        Top = 169
        Width = 81
        Height = 21
        ReadOnly = True
        TabOrder = 8
      end
      object CheckBox_AddrBD4: TCheckBox
        Left = 551
        Top = 171
        Width = 48
        Height = 17
        Caption = #1041#1044'4'
        TabOrder = 9
      end
      object Edit_SN3: TEdit
        Left = 674
        Top = 143
        Width = 81
        Height = 21
        ReadOnly = True
        TabOrder = 10
      end
      object CheckBox_AddrBD3: TCheckBox
        Left = 551
        Top = 145
        Width = 48
        Height = 17
        Caption = #1041#1044'3'
        TabOrder = 11
      end
      object Edit_SN2: TEdit
        Left = 674
        Top = 117
        Width = 81
        Height = 21
        ReadOnly = True
        TabOrder = 12
      end
      object CheckBox_AddrBD2: TCheckBox
        Left = 551
        Top = 119
        Width = 48
        Height = 17
        Caption = #1041#1044'2'
        TabOrder = 13
      end
      object Edit_SN1: TEdit
        Left = 674
        Top = 91
        Width = 81
        Height = 21
        ReadOnly = True
        TabOrder = 14
      end
      object CheckBox_AddrBD1: TCheckBox
        Left = 551
        Top = 93
        Width = 48
        Height = 17
        Caption = #1041#1044'1'
        TabOrder = 15
      end
      object Panel_Display_BD7: TPanel
        Left = 8
        Top = 247
        Width = 538
        Height = 25
        Alignment = taLeftJustify
        BevelInner = bvLowered
        TabOrder = 16
        object Label_SchetSek07: TLabel
          Left = 8
          Top = 6
          Width = 84
          Height = 13
          Caption = #1057#1095#1105#1090' '#1079#1072' '#1089#1077#1082#1091#1085#1076#1091':'
        end
        object Label_PNSch07: TLabel
          Left = 144
          Top = 6
          Width = 97
          Height = 13
          Caption = #1087#1088#1080#1079#1085'. '#1085#1077#1089#1085'. '#1089#1095#1105#1090#1072':'
        end
        object Label_KvoIsp07: TLabel
          Left = 299
          Top = 5
          Width = 94
          Height = 13
          Caption = #1082#1086#1083'-'#1074#1086' '#1080#1089#1087#1099#1090#1072#1085#1080#1081':'
        end
        object Edit_SchetSek07: TEdit
          Left = 97
          Top = 3
          Width = 43
          Height = 21
          Color = clInfoBk
          Enabled = False
          ReadOnly = True
          TabOrder = 0
        end
        object Edit_PNSch07: TEdit
          Left = 247
          Top = 3
          Width = 47
          Height = 21
          Color = clInfoBk
          Enabled = False
          ReadOnly = True
          TabOrder = 1
        end
        object Edit_KvoIsp07: TEdit
          Left = 399
          Top = 3
          Width = 50
          Height = 21
          Color = clInfoBk
          Enabled = False
          ReadOnly = True
          TabOrder = 2
        end
      end
      object Panel_Display_BD6: TPanel
        Left = 8
        Top = 221
        Width = 538
        Height = 25
        Alignment = taLeftJustify
        BevelInner = bvLowered
        TabOrder = 17
        object Label_SchetSek06: TLabel
          Left = 8
          Top = 6
          Width = 84
          Height = 13
          Caption = #1057#1095#1105#1090' '#1079#1072' '#1089#1077#1082#1091#1085#1076#1091':'
        end
        object Label_PNSch06: TLabel
          Left = 144
          Top = 6
          Width = 97
          Height = 13
          Caption = #1087#1088#1080#1079#1085'. '#1085#1077#1089#1085'. '#1089#1095#1105#1090#1072':'
        end
        object Label_KvoIsp06: TLabel
          Left = 299
          Top = 5
          Width = 94
          Height = 13
          Caption = #1082#1086#1083'-'#1074#1086' '#1080#1089#1087#1099#1090#1072#1085#1080#1081':'
        end
        object Edit_SchetSek06: TEdit
          Left = 97
          Top = 3
          Width = 43
          Height = 21
          Color = clInfoBk
          Enabled = False
          ReadOnly = True
          TabOrder = 0
        end
        object Edit_PNSch06: TEdit
          Left = 247
          Top = 3
          Width = 47
          Height = 21
          Color = clInfoBk
          Enabled = False
          ReadOnly = True
          TabOrder = 1
        end
        object Edit_KvoIsp06: TEdit
          Left = 399
          Top = 3
          Width = 50
          Height = 21
          Color = clInfoBk
          Enabled = False
          ReadOnly = True
          TabOrder = 2
        end
      end
      object Panel_Display_BD5: TPanel
        Left = 8
        Top = 195
        Width = 538
        Height = 25
        Alignment = taLeftJustify
        BevelInner = bvLowered
        TabOrder = 18
        object Label_SchetSek05: TLabel
          Left = 8
          Top = 6
          Width = 84
          Height = 13
          Caption = #1057#1095#1105#1090' '#1079#1072' '#1089#1077#1082#1091#1085#1076#1091':'
        end
        object Label_PNSch05: TLabel
          Left = 144
          Top = 6
          Width = 97
          Height = 13
          Caption = #1087#1088#1080#1079#1085'. '#1085#1077#1089#1085'. '#1089#1095#1105#1090#1072':'
        end
        object Label_KvoIsp05: TLabel
          Left = 299
          Top = 5
          Width = 94
          Height = 13
          Caption = #1082#1086#1083'-'#1074#1086' '#1080#1089#1087#1099#1090#1072#1085#1080#1081':'
        end
        object Edit_SchetSek05: TEdit
          Left = 97
          Top = 3
          Width = 43
          Height = 21
          Color = clInfoBk
          Enabled = False
          ReadOnly = True
          TabOrder = 0
        end
        object Edit_PNSch05: TEdit
          Left = 247
          Top = 3
          Width = 47
          Height = 21
          Color = clInfoBk
          Enabled = False
          ReadOnly = True
          TabOrder = 1
        end
        object Edit_KvoIsp05: TEdit
          Left = 399
          Top = 3
          Width = 50
          Height = 21
          Color = clInfoBk
          Enabled = False
          ReadOnly = True
          TabOrder = 2
        end
      end
      object Panel_Display_BD4: TPanel
        Left = 8
        Top = 169
        Width = 538
        Height = 25
        Alignment = taLeftJustify
        BevelInner = bvLowered
        TabOrder = 19
        object Label_SchetSek04: TLabel
          Left = 8
          Top = 6
          Width = 84
          Height = 13
          Caption = #1057#1095#1105#1090' '#1079#1072' '#1089#1077#1082#1091#1085#1076#1091':'
        end
        object Label_PNSch04: TLabel
          Left = 144
          Top = 6
          Width = 97
          Height = 13
          Caption = #1087#1088#1080#1079#1085'. '#1085#1077#1089#1085'. '#1089#1095#1105#1090#1072':'
        end
        object Label_KvoIsp04: TLabel
          Left = 299
          Top = 5
          Width = 94
          Height = 13
          Caption = #1082#1086#1083'-'#1074#1086' '#1080#1089#1087#1099#1090#1072#1085#1080#1081':'
        end
        object Edit_SchetSek04: TEdit
          Left = 97
          Top = 3
          Width = 43
          Height = 21
          Color = clInfoBk
          Enabled = False
          ReadOnly = True
          TabOrder = 0
        end
        object Edit_PNSch04: TEdit
          Left = 247
          Top = 3
          Width = 47
          Height = 21
          Color = clInfoBk
          Enabled = False
          ReadOnly = True
          TabOrder = 1
        end
        object Edit_KvoIsp04: TEdit
          Left = 399
          Top = 3
          Width = 50
          Height = 21
          Color = clInfoBk
          Enabled = False
          ReadOnly = True
          TabOrder = 2
        end
      end
      object Panel_Display_BD3: TPanel
        Left = 8
        Top = 143
        Width = 538
        Height = 25
        Alignment = taLeftJustify
        BevelInner = bvLowered
        TabOrder = 20
        object Label_SchetSek03: TLabel
          Left = 8
          Top = 6
          Width = 84
          Height = 13
          Caption = #1057#1095#1105#1090' '#1079#1072' '#1089#1077#1082#1091#1085#1076#1091':'
        end
        object Label_PNSch03: TLabel
          Left = 144
          Top = 6
          Width = 97
          Height = 13
          Caption = #1087#1088#1080#1079#1085'. '#1085#1077#1089#1085'. '#1089#1095#1105#1090#1072':'
        end
        object Label_KvoIsp03: TLabel
          Left = 299
          Top = 5
          Width = 94
          Height = 13
          Caption = #1082#1086#1083'-'#1074#1086' '#1080#1089#1087#1099#1090#1072#1085#1080#1081':'
        end
        object Edit_SchetSek03: TEdit
          Left = 97
          Top = 3
          Width = 43
          Height = 21
          Color = clInfoBk
          Enabled = False
          ReadOnly = True
          TabOrder = 0
        end
        object Edit_PNSch03: TEdit
          Left = 247
          Top = 3
          Width = 47
          Height = 21
          Color = clInfoBk
          Enabled = False
          ReadOnly = True
          TabOrder = 1
        end
        object Edit_KvoIsp03: TEdit
          Left = 399
          Top = 3
          Width = 50
          Height = 21
          Color = clInfoBk
          Enabled = False
          ReadOnly = True
          TabOrder = 2
        end
      end
      object Panel_Display_BD2: TPanel
        Left = 8
        Top = 117
        Width = 538
        Height = 25
        Alignment = taLeftJustify
        BevelInner = bvLowered
        TabOrder = 21
        object Label_SchetSek02: TLabel
          Left = 8
          Top = 6
          Width = 84
          Height = 13
          Caption = #1057#1095#1105#1090' '#1079#1072' '#1089#1077#1082#1091#1085#1076#1091':'
        end
        object Label_PNSch02: TLabel
          Left = 144
          Top = 6
          Width = 97
          Height = 13
          Caption = #1087#1088#1080#1079#1085'. '#1085#1077#1089#1085'. '#1089#1095#1105#1090#1072':'
        end
        object Label_KvoIsp02: TLabel
          Left = 299
          Top = 5
          Width = 94
          Height = 13
          Caption = #1082#1086#1083'-'#1074#1086' '#1080#1089#1087#1099#1090#1072#1085#1080#1081':'
        end
        object Edit_SchetSek02: TEdit
          Left = 97
          Top = 3
          Width = 43
          Height = 21
          Color = clInfoBk
          Enabled = False
          ReadOnly = True
          TabOrder = 0
        end
        object Edit_PNSch02: TEdit
          Left = 247
          Top = 3
          Width = 47
          Height = 21
          Color = clInfoBk
          Enabled = False
          ReadOnly = True
          TabOrder = 1
        end
        object Edit_KvoIsp02: TEdit
          Left = 399
          Top = 3
          Width = 50
          Height = 21
          Color = clInfoBk
          Enabled = False
          ReadOnly = True
          TabOrder = 2
        end
      end
      object CheckBox_AddrBD8: TCheckBox
        Left = 551
        Top = 275
        Width = 48
        Height = 17
        Caption = #1041#1044'8'
        TabOrder = 22
      end
      object SpinEdit_Time: TCSpinEdit
        Left = 18
        Top = 33
        Width = 95
        Height = 22
        MaxValue = 300
        MinValue = 1
        TabOrder = 23
        Value = 1
      end
      object Button_Start: TButton
        Left = 8
        Top = 321
        Width = 75
        Height = 25
        Caption = #1057#1090#1072#1088#1090
        TabOrder = 24
        OnClick = Button_StartClick
      end
      object Button_detail: TButton
        Left = 298
        Top = 30
        Width = 137
        Height = 25
        Caption = #1055#1086#1076#1088#1086#1073#1085#1086' '#1086#1073' '#1086#1096#1080#1073#1082#1072#1093
        TabOrder = 25
        OnClick = Button_detailClick
      end
      object Panel_Info: TPanel
        Left = 8
        Top = 354
        Width = 529
        Height = 25
        Alignment = taLeftJustify
        BevelInner = bvLowered
        TabOrder = 26
      end
      object Button_ReadLogs: TButton
        Left = 176
        Top = 321
        Width = 103
        Height = 25
        Caption = #1063#1090#1077#1085#1080#1077' '#1083#1086#1075#1086#1074
        TabOrder = 27
      end
      object Button_Stop: TButton
        Left = 91
        Top = 321
        Width = 75
        Height = 25
        Caption = #1057#1058#1054#1055
        TabOrder = 28
        OnClick = Button_StopClick
      end
      object Panel_Display_BD8: TPanel
        Left = 8
        Top = 273
        Width = 538
        Height = 25
        Alignment = taLeftJustify
        BevelInner = bvLowered
        TabOrder = 29
        object Label_SchetSek08: TLabel
          Left = 8
          Top = 6
          Width = 84
          Height = 13
          Caption = #1057#1095#1105#1090' '#1079#1072' '#1089#1077#1082#1091#1085#1076#1091':'
        end
        object Label_PNSch08: TLabel
          Left = 144
          Top = 6
          Width = 97
          Height = 13
          Caption = #1087#1088#1080#1079#1085'. '#1085#1077#1089#1085'. '#1089#1095#1105#1090#1072':'
        end
        object Label_KvoIsp08: TLabel
          Left = 299
          Top = 5
          Width = 94
          Height = 13
          Caption = #1082#1086#1083'-'#1074#1086' '#1080#1089#1087#1099#1090#1072#1085#1080#1081':'
        end
        object Edit_SchetSek08: TEdit
          Left = 97
          Top = 3
          Width = 43
          Height = 21
          Color = clInfoBk
          Enabled = False
          ReadOnly = True
          TabOrder = 0
        end
        object Edit_PNSch08: TEdit
          Left = 247
          Top = 3
          Width = 47
          Height = 21
          Color = clInfoBk
          Enabled = False
          ReadOnly = True
          TabOrder = 1
        end
        object Edit_KvoIsp08: TEdit
          Left = 399
          Top = 3
          Width = 50
          Height = 21
          Color = clInfoBk
          Enabled = False
          ReadOnly = True
          TabOrder = 2
        end
      end
      object SpinEdit_AddrBD1: TCSpinEdit
        Left = 603
        Top = 91
        Width = 66
        Height = 22
        MaxValue = 247
        TabOrder = 30
        Value = 1
      end
      object SpinEdit_AddrBD2: TCSpinEdit
        Left = 603
        Top = 117
        Width = 66
        Height = 22
        MaxValue = 247
        TabOrder = 31
        Value = 2
      end
      object SpinEdit_AddrBD3: TCSpinEdit
        Left = 603
        Top = 143
        Width = 67
        Height = 22
        MaxValue = 247
        TabOrder = 32
        Value = 3
      end
      object SpinEdit_AddrBD4: TCSpinEdit
        Left = 603
        Top = 169
        Width = 67
        Height = 22
        MaxValue = 247
        TabOrder = 33
        Value = 4
      end
      object SpinEdit_AddrBD5: TCSpinEdit
        Left = 603
        Top = 195
        Width = 68
        Height = 22
        MaxValue = 247
        TabOrder = 34
        Value = 5
      end
      object SpinEdit_AddrBD6: TCSpinEdit
        Left = 603
        Top = 221
        Width = 67
        Height = 22
        MaxValue = 247
        TabOrder = 35
        Value = 6
      end
      object SpinEdit_AddrBD7: TCSpinEdit
        Left = 603
        Top = 247
        Width = 66
        Height = 22
        MaxValue = 247
        TabOrder = 36
        Value = 7
      end
      object SpinEdit_AddrBD8: TCSpinEdit
        Left = 603
        Top = 274
        Width = 66
        Height = 22
        MaxValue = 247
        TabOrder = 37
        Value = 8
      end
      object SpinEdit_readTimeout: TCSpinEdit
        Left = 195
        Top = 33
        Width = 95
        Height = 22
        MaxValue = 500
        MinValue = 2
        TabOrder = 38
        Value = 11
      end
      object CheckBox_Err: TCheckBox
        Left = 301
        Top = 10
        Width = 172
        Height = 17
        Caption = #1042#1099#1074#1086#1076#1080#1090#1100' '#1086#1096#1080#1073#1082#1080' ('#1044#1072'/'#1053#1077#1090')'
        TabOrder = 39
      end
      object CheckBox_AllBD: TCheckBox
        Left = 551
        Top = 57
        Width = 66
        Height = 17
        Caption = #1042#1089#1077' '#1041#1044
        TabOrder = 40
        OnClick = CheckBox_AllBDClick
      end
      object Button_Exit: TButton
        Left = 291
        Top = 321
        Width = 94
        Height = 25
        Caption = #1047#1072#1082#1088#1099#1090#1100' '#1086#1082#1085#1086
        TabOrder = 41
        OnClick = Button_ExitClick
      end
      object Button_Graph_01: TButton
        Left = 762
        Top = 91
        Width = 25
        Height = 19
        Caption = '...'
        TabOrder = 42
        OnClick = Button_Graph_01Click
      end
      object Button_Graph_02: TButton
        Left = 762
        Top = 118
        Width = 25
        Height = 19
        Caption = '...'
        TabOrder = 43
        OnClick = Button_Graph_02Click
      end
      object Button_Graph_03: TButton
        Left = 762
        Top = 143
        Width = 25
        Height = 19
        Caption = '...'
        TabOrder = 44
        OnClick = Button_Graph_03Click
      end
      object Button_Graph_04: TButton
        Left = 762
        Top = 169
        Width = 25
        Height = 19
        Caption = '...'
        TabOrder = 45
        OnClick = Button_Graph_04Click
      end
      object Button_Graph_05: TButton
        Left = 762
        Top = 195
        Width = 25
        Height = 19
        Caption = '...'
        TabOrder = 46
        OnClick = Button_Graph_05Click
      end
      object Button_Graph_06: TButton
        Left = 762
        Top = 222
        Width = 25
        Height = 19
        Caption = '...'
        TabOrder = 47
        OnClick = Button_Graph_06Click
      end
      object Button_Graph_07: TButton
        Left = 762
        Top = 247
        Width = 25
        Height = 19
        Caption = '...'
        TabOrder = 48
        OnClick = Button_Graph_07Click
      end
      object Button_Graph_08: TButton
        Left = 762
        Top = 275
        Width = 25
        Height = 19
        Caption = '...'
        TabOrder = 49
        OnClick = Button_Graph_08Click
      end
      object Button_Graph: TButton
        Left = 592
        Top = 360
        Width = 75
        Height = 25
        Caption = #1043#1088#1072#1092#1080#1082
        TabOrder = 50
        OnClick = Button_GraphClick
      end
    end
  end
end
