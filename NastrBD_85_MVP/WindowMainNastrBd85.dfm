object WindowMainBd85: TWindowMainBd85
  Left = 597
  Top = 105
  Width = 770
  Height = 700
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1041#1044' 85'
  Color = clBtnFace
  Constraints.MaxHeight = 700
  Constraints.MaxWidth = 770
  Constraints.MinHeight = 350
  Constraints.MinWidth = 385
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
  object PageControl_WindowBd85: TPageControl
    Left = 0
    Top = 0
    Width = 754
    Height = 662
    ActivePage = TabSheet_Main
    Align = alClient
    TabIndex = 0
    TabOrder = 0
    object TabSheet_Main: TTabSheet
      Caption = #1054#1089#1085#1086#1074#1085#1099#1077' '#1087#1072#1088#1072#1084#1077#1090#1088#1099
      object panel_Connect: TPanel
        Left = 450
        Top = 8
        Width = 201
        Height = 289
        BevelInner = bvLowered
        TabOrder = 0
        object label_Protocol: TLabel
          Left = 8
          Top = 4
          Width = 90
          Height = 13
          Caption = #1055#1088#1086#1090#1086#1082#1086#1083' '#1086#1073#1084#1077#1085#1072
        end
        object comboBox_Protocol: TComboBox
          Left = 8
          Top = 20
          Width = 145
          Height = 21
          ItemHeight = 13
          TabOrder = 0
          OnChange = comboBox_ProtocolChange
        end
        object panel_helperNumTxtBtn: TPanel
          Left = 8
          Top = 160
          Width = 121
          Height = 53
          BevelInner = bvLowered
          TabOrder = 1
          object label_AddrBd: TLabel
            Left = 9
            Top = 5
            Width = 98
            Height = 13
            Caption = #1040#1076#1088#1077#1089' '#1041#1044' [1 ... 247]'
          end
          object textBox_AddrBd: TEdit
            Left = 6
            Top = 23
            Width = 41
            Height = 24
            BiDiMode = bdRightToLeftReadingOnly
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentBiDiMode = False
            ParentFont = False
            TabOrder = 0
            Text = '1'
            OnChange = textBox_AddrBdChange
          end
          object button_AddrBd_Dec: TButton
            Left = 48
            Top = 22
            Width = 33
            Height = 25
            Caption = '-'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = 24
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
            OnClick = button_AddrBd_DecClick
          end
          object button_AddrBd_Inc: TButton
            Left = 82
            Top = 22
            Width = 33
            Height = 25
            Caption = '+'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = 24
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 2
            OnClick = button_AddrBd_IncClick
          end
        end
        object panel_comPort_TcpIp: TPanel
          Left = 8
          Top = 48
          Width = 187
          Height = 109
          BevelOuter = bvNone
          TabOrder = 2
          object groupBox_ComPort: TGroupBox
            Left = 0
            Top = 0
            Width = 187
            Height = 109
            Align = alClient
            Caption = ' '#1042#1099#1073#1086#1088' '#1050#1054#1052' '#1087#1086#1088#1090#1072' '
            TabOrder = 0
            object label_ComPortS: TLabel
              Left = 13
              Top = 55
              Width = 102
              Height = 13
              Caption = #1057#1087#1080#1089#1086#1082' '#1050#1054#1052'-'#1087#1086#1088#1090#1086#1074
            end
            object comboBox_ComPorts: TComboBox
              Left = 12
              Top = 24
              Width = 117
              Height = 21
              ItemHeight = 13
              TabOrder = 0
              OnChange = comboBox_ComPortsChange
            end
            object button_UpdateNumberOfComPortS: TButton
              Left = 13
              Top = 72
              Width = 116
              Height = 25
              Caption = #1054#1073#1085#1086#1074#1080#1090#1100
              TabOrder = 1
              OnClick = button_UpdateNumberOfComPortSClick
            end
            object label_ComPortsCount: TEdit
              Left = 132
              Top = 22
              Width = 41
              Height = 24
              BiDiMode = bdRightToLeftReadingOnly
              Color = cl3DLight
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentBiDiMode = False
              ParentFont = False
              ReadOnly = True
              TabOrder = 2
            end
          end
          object groupBox_TcpIp: TGroupBox
            Left = 0
            Top = 0
            Width = 187
            Height = 109
            Align = alClient
            Caption = ' TCP/IP '
            TabOrder = 1
            object label_IP_Addr: TLabel
              Left = 11
              Top = 15
              Width = 44
              Height = 13
              Caption = 'IP '#1040#1076#1088#1077#1089
            end
            object label_TCP_Port: TLabel
              Left = 10
              Top = 62
              Width = 49
              Height = 13
              Caption = 'TCP '#1055#1086#1088#1090
            end
            object textBox_IP_Addr: TEdit
              Left = 9
              Top = 31
              Width = 128
              Height = 24
              BiDiMode = bdRightToLeftReadingOnly
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentBiDiMode = False
              ParentFont = False
              TabOrder = 0
              Text = '192.168.3.4'
              OnChange = textBox_IP_AddrChange
            end
            object textBox_TCP_Port: TEdit
              Left = 8
              Top = 78
              Width = 81
              Height = 24
              BiDiMode = bdRightToLeftReadingOnly
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentBiDiMode = False
              ParentFont = False
              TabOrder = 1
              Text = '502'
              OnChange = textBox_TCP_PortChange
            end
          end
        end
        object button_StartStop: TButton
          Left = 8
          Top = 217
          Width = 137
          Height = 25
          Caption = #1053#1072#1095#1072#1090#1100
          TabOrder = 3
          OnClick = button_StartStopClick
        end
        object label_Hint: TPanel
          Left = 8
          Top = 248
          Width = 185
          Height = 33
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Caption = 'label_Hint'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlue
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
        end
      end
      object DataFromDetGroupBox: TGroupBox
        Left = -1
        Top = 2
        Width = 446
        Height = 217
        Caption = ' '#1048#1085#1092#1086#1088#1084#1072#1094#1080#1103' '#1089' '#1041#1044' '
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
          Top = 38
          Width = 75
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 0
        end
        object IndAdrPanel: TPanel
          Left = 8
          Top = 38
          Width = 241
          Height = 20
          Alignment = taLeftJustify
          BorderWidth = 1
          Caption = ' '#1048#1085#1076#1080#1074#1080#1076#1091#1072#1083#1100#1085#1099#1081' '#1072#1076#1088#1077#1089
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
          Top = 60
          Width = 241
          Height = 20
          Alignment = taLeftJustify
          BorderWidth = 1
          Caption = ' '#1043#1088#1091#1087#1087#1086#1074#1086#1081' '#1072#1076#1088#1077#1089
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
          Top = 60
          Width = 75
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 5
        end
        object TprPanel: TPanel
          Left = 8
          Top = 82
          Width = 241
          Height = 20
          Alignment = taLeftJustify
          BorderWidth = 1
          Caption = ' '#1058#1077#1084#1087#1077#1088#1072#1090#1091#1088#1072' '#1087#1088#1086#1094#1077#1089#1089#1086#1088#1072' '
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
          Top = 126
          Width = 241
          Height = 20
          Alignment = taLeftJustify
          BorderWidth = 1
          Caption = ' '#1053#1072#1087#1088#1103#1078#1077#1085#1080#1077' '#1042#1067#1057#1054#1050#1054#1045' '#1080#1079#1084#1077#1088#1077#1085#1085#1086#1077' '
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
          Top = 104
          Width = 241
          Height = 20
          Alignment = taLeftJustify
          BorderWidth = 1
          Caption = ' '#1047#1085#1072#1095#1077#1085#1080#1077' '#1044#1053#1059' '#1080#1079#1084#1077#1088#1077#1085#1085#1086#1077' '
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
          Top = 82
          Width = 67
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 9
        end
        object UhiICodeEdit: TEdit
          Left = 250
          Top = 126
          Width = 67
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 10
        end
        object DNUICodeEdit: TEdit
          Left = 250
          Top = 104
          Width = 67
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 11
        end
        object ValueCodePanel: TPanel
          Left = 317
          Top = 16
          Width = 76
          Height = 20
          Alignment = taLeftJustify
          Caption = ' '#1047#1053#1040#1063#1045#1053#1048#1045
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
          Top = 82
          Width = 75
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 13
        end
        object UnitPanel: TPanel
          Left = 393
          Top = 16
          Width = 44
          Height = 20
          Alignment = taLeftJustify
          Caption = '   '#1045#1048
          Ctl3D = True
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentCtl3D = False
          ParentFont = False
          TabOrder = 14
        end
        object TprUnitEdit: TEdit
          Left = 394
          Top = 82
          Width = 43
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 15
          Text = '  '#176'C'
        end
        object UhiIUnitEdit: TEdit
          Left = 394
          Top = 126
          Width = 43
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 16
          Text = '   '#1042
        end
        object DNUIUnitEdit: TEdit
          Left = 394
          Top = 104
          Width = 43
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 17
          Text = '   '#1042
        end
        object EmptyPanel01: TPanel
          Left = 249
          Top = 38
          Width = 68
          Height = 20
          TabOrder = 18
        end
        object EmptyPanel02: TPanel
          Left = 249
          Top = 60
          Width = 68
          Height = 20
          TabOrder = 19
        end
        object EmptyPanel07: TPanel
          Left = 394
          Top = 38
          Width = 43
          Height = 20
          TabOrder = 20
        end
        object EmptyPanel08: TPanel
          Left = 394
          Top = 60
          Width = 43
          Height = 20
          TabOrder = 21
        end
        object Panel1: TPanel
          Left = 8
          Top = 148
          Width = 241
          Height = 20
          Alignment = taLeftJustify
          BorderWidth = 1
          Caption = ' '#1044#1083#1080#1090#1077#1083#1100#1085#1086#1089#1090#1100' '#1064#1048#1052
          Ctl3D = True
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          TabOrder = 22
        end
        object Edit2: TEdit
          Left = 394
          Top = 148
          Width = 43
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 23
          Text = '  '#1084#1082#1089
        end
        object Panel15: TPanel
          Left = 8
          Top = 170
          Width = 241
          Height = 20
          Alignment = taLeftJustify
          BorderWidth = 1
          Caption = ' '#1055#1077#1088#1080#1086#1076' '#1064#1048#1052' '
          Ctl3D = True
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          TabOrder = 24
        end
        object Edit9: TEdit
          Left = 394
          Top = 170
          Width = 43
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 25
          Text = '  '#1084#1082#1089
        end
        object Panel16: TPanel
          Left = 8
          Top = 192
          Width = 241
          Height = 20
          Alignment = taLeftJustify
          BorderWidth = 1
          Caption = ' '#1057#1095#1077#1090' '#1089' '#1041#1044' '#1079#1072' 1 '#1089#1077#1082' '
          Ctl3D = True
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          TabOrder = 26
        end
        object Panel18: TPanel
          Left = 249
          Top = 192
          Width = 68
          Height = 20
          TabOrder = 27
        end
        object Edit15: TEdit
          Left = 394
          Top = 192
          Width = 43
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 28
          Text = ' '#1080#1084#1087
        end
        object Edit5: TEdit
          Left = 250
          Top = 148
          Width = 67
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 29
        end
        object Edit10: TEdit
          Left = 250
          Top = 170
          Width = 67
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 30
        end
        object Edit4: TEdit
          Left = 318
          Top = 104
          Width = 75
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 31
        end
        object Edit14: TEdit
          Left = 318
          Top = 126
          Width = 75
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 32
        end
        object Edit20: TEdit
          Left = 318
          Top = 148
          Width = 75
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 33
        end
        object Edit21: TEdit
          Left = 318
          Top = 170
          Width = 75
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 34
        end
        object Edit22: TEdit
          Left = 318
          Top = 192
          Width = 75
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 35
        end
      end
      object GroupBox2: TGroupBox
        Left = -1
        Top = 226
        Width = 446
        Height = 145
        Caption = ' '#1055#1086#1083#1091#1095#1077#1085#1080#1077' '#1089#1095#1105#1090#1072' '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -12
        Font.Name = 'Courier New'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 2
        object Label3: TLabel
          Left = 112
          Top = 16
          Width = 119
          Height = 15
          Caption = #1042#1088#1077#1084#1103' '#1080#1079#1084#1077#1088#1077#1085#1080#1103','#1089
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentFont = False
        end
        object SumCountPanel: TPanel
          Left = 8
          Top = 60
          Width = 241
          Height = 20
          Alignment = taLeftJustify
          BorderWidth = 1
          Caption = ' '#1057#1091#1084#1084#1072#1088#1085#1099#1081' '#1089#1095#1077#1090' '#1079#1072' '#1074#1088#1077#1084#1103' '#1080#1079#1084#1077#1088#1077#1085#1080#1103' '
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
          Top = 82
          Width = 241
          Height = 20
          Alignment = taLeftJustify
          BorderWidth = 1
          Caption = ' '#1058#1077#1082#1091#1097#1077#1077' '#1074#1088#1077#1084#1103' '#1089#1095#1077#1090#1072' '#1080#1084#1087#1091#1083#1100#1089#1086#1074' '
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
          Top = 60
          Width = 68
          Height = 20
          TabOrder = 2
        end
        object EmptyPanel06: TPanel
          Left = 249
          Top = 82
          Width = 68
          Height = 20
          TabOrder = 3
        end
        object SumCountEdit: TEdit
          Left = 318
          Top = 60
          Width = 75
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 4
        end
        object TCountEdit: TEdit
          Left = 318
          Top = 82
          Width = 75
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 5
        end
        object SumCountUnitEdit: TEdit
          Left = 394
          Top = 60
          Width = 43
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 6
          Text = ' '#1080#1084#1087
        end
        object TCountUnitEdit: TEdit
          Left = 394
          Top = 82
          Width = 43
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 7
          Text = '  '#1089
        end
        object T_LimitEdit: TEdit
          Left = 248
          Top = 16
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
          Width = 120
          Height = 25
          Cursor = crHandPoint
          Caption = #1057#1073#1088#1086#1089
          Enabled = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 9
        end
        object StartCountButton: TButton
          Left = 128
          Top = 108
          Width = 120
          Height = 25
          Cursor = crHandPoint
          Caption = #1057#1090#1072#1088#1090
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 10
        end
        object Count1Panel: TPanel
          Left = 8
          Top = 38
          Width = 241
          Height = 20
          Alignment = taLeftJustify
          BorderWidth = 1
          Caption = ' '#1057#1088'. '#1057#1095#1077#1090' '#1089' '#1041#1044' '#1079#1072' 1 '#1089#1077#1082' '
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
          Top = 38
          Width = 68
          Height = 20
          TabOrder = 12
        end
        object Count1Edit: TEdit
          Left = 318
          Top = 38
          Width = 75
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 13
        end
        object Count1UnitEdit: TEdit
          Left = 394
          Top = 38
          Width = 43
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 14
          Text = #1080#1084#1087'/'#1089
        end
        object btnSaveParam: TButton
          Left = 318
          Top = 108
          Width = 120
          Height = 25
          Caption = '-> '#1042' '#1092#1072#1081#1083
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 15
        end
      end
      object DataForDetBox: TGroupBox
        Left = -1
        Top = 376
        Width = 446
        Height = 254
        Caption = ' '#1059#1089#1090#1072#1085#1086#1074#1082#1072' '#1087#1072#1088#1072#1084#1077#1090#1088#1086#1074' '#1041#1044' '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -12
        Font.Name = 'Courier New'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
        object SetDNUEdit: TMaskEdit
          Left = 318
          Top = 82
          Width = 75
          Height = 20
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 0
        end
        object SetIndAdrPanel: TPanel
          Left = 8
          Top = 38
          Width = 241
          Height = 20
          Alignment = taLeftJustify
          BorderWidth = 1
          Caption = ' '#1048#1085#1076#1080#1074#1080#1076#1091#1072#1083#1100#1085#1099#1081' '#1072#1076#1088#1077#1089
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
          Top = 60
          Width = 241
          Height = 20
          Alignment = taLeftJustify
          BorderWidth = 1
          Caption = ' '#1043#1088#1091#1087#1087#1086#1074#1086#1081' '#1072#1076#1088#1077#1089' '
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
          Top = 82
          Width = 241
          Height = 22
          Alignment = taLeftJustify
          BorderWidth = 1
          Caption = ' '#1047#1085#1072#1095#1077#1085#1080#1077' '#1044#1053#1059' '#1079#1072#1076#1072#1085#1085#1086#1077' '
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
          Top = 104
          Width = 241
          Height = 20
          Alignment = taLeftJustify
          BorderWidth = 1
          Caption = ' '#1053#1072#1087#1088#1103#1078#1077#1085#1080#1077' '#1042#1067#1057#1054#1050#1054#1045' '#1079#1072#1076#1072#1085#1085#1086#1077' '
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
          Width = 75
          Height = 20
          BorderWidth = 1
          Caption = #1047#1053#1040#1063#1045#1053#1048#1045
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 7
        end
        object SetIndAdrEdit: TEdit
          Left = 318
          Top = 38
          Width = 75
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
          TabOrder = 8
        end
        object SetGrpAdrEdit: TEdit
          Left = 318
          Top = 60
          Width = 75
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
        object SetDNUCodeEdit: TEdit
          Left = 250
          Top = 82
          Width = 67
          Height = 20
          Color = clCream
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGreen
          Font.Height = -11
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentCtl3D = False
          ParentFont = False
          TabOrder = 10
        end
        object SetUhiCodeEdit: TEdit
          Left = 250
          Top = 104
          Width = 67
          Height = 20
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 15
        end
        object EmptyPanel09: TPanel
          Left = 250
          Top = 38
          Width = 67
          Height = 20
          TabOrder = 14
        end
        object EmptyPanel10: TPanel
          Left = 250
          Top = 60
          Width = 67
          Height = 20
          TabOrder = 16
        end
        object Panel3: TPanel
          Left = 394
          Top = 16
          Width = 44
          Height = 20
          Alignment = taLeftJustify
          Caption = '   '#1045#1048
          Ctl3D = True
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentCtl3D = False
          ParentFont = False
          TabOrder = 17
        end
        object Panel4: TPanel
          Left = 394
          Top = 38
          Width = 43
          Height = 20
          TabOrder = 18
        end
        object Panel5: TPanel
          Left = 394
          Top = 60
          Width = 43
          Height = 20
          TabOrder = 19
        end
        object Edit1: TEdit
          Left = 394
          Top = 82
          Width = 43
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 20
          Text = '   '#1042
        end
        object Edit3: TEdit
          Left = 394
          Top = 104
          Width = 43
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 21
          Text = '   '#1042
        end
        object Panel12: TPanel
          Left = 8
          Top = 126
          Width = 241
          Height = 20
          Alignment = taLeftJustify
          BorderWidth = 1
          Caption = ' '#1044#1083#1080#1090#1080#1090#1077#1083#1100#1085#1086#1089#1090#1100' '#1064#1048#1052' (0...200)'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Courier New'
          Font.Style = []
          ParentFont = False
          TabOrder = 22
        end
        object Panel28: TPanel
          Left = 8
          Top = 148
          Width = 241
          Height = 20
          Alignment = taLeftJustify
          BorderWidth = 1
          Caption = ' '#1057#1084#1077#1097#1077#1085#1080#1077' '#1064#1048#1052' (0...2000)'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Courier New'
          Font.Style = []
          ParentFont = False
          TabOrder = 23
        end
        object Edit6: TEdit
          Left = 250
          Top = 126
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
        object Edit18: TEdit
          Left = 250
          Top = 148
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
        object Panel14: TPanel
          Left = 318
          Top = 126
          Width = 75
          Height = 20
          TabOrder = 24
        end
        object Panel29: TPanel
          Left = 318
          Top = 148
          Width = 75
          Height = 20
          TabOrder = 25
        end
        object Edit8: TEdit
          Left = 394
          Top = 126
          Width = 43
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 26
          Text = ' '#1077#1076'.'
        end
        object Edit19: TEdit
          Left = 394
          Top = 148
          Width = 43
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 27
          Text = ' '#1077#1076'.'
        end
        object GroupBox_ReverseLink: TGroupBox
          Left = 8
          Top = 192
          Width = 168
          Height = 57
          Caption = ' '#1054#1073#1088#1072#1090#1085#1072#1103' '#1089#1074#1103#1079#1100' '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 28
          object RS1: TRadioButton
            Left = 8
            Top = 16
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
            Top = 32
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
        object Panel2: TPanel
          Left = 8
          Top = 170
          Width = 241
          Height = 20
          Alignment = taLeftJustify
          BorderWidth = 1
          Caption = ' '#1055#1077#1088#1080#1086#1076' '#1064#1048#1052' (2000..3000)'
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
          Top = 170
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
          TabOrder = 13
        end
        object Panel6: TPanel
          Left = 318
          Top = 170
          Width = 75
          Height = 20
          TabOrder = 30
        end
        object Edit17: TEdit
          Left = 394
          Top = 170
          Width = 43
          Height = 21
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 31
          Text = ' '#1077#1076'.'
        end
        object btnDefaults: TButton
          Left = 317
          Top = 200
          Width = 120
          Height = 25
          Caption = #1048#1079' '#1092#1072#1081#1083#1072
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 32
        end
        object SetUhiEdit: TComboBox
          Left = 320
          Top = 104
          Width = 73
          Height = 24
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGreen
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ItemHeight = 16
          ParentFont = False
          TabOrder = 33
          Items.Strings = (
            '1100'
            '1110'
            '1120'
            '1130'
            '1140'
            '1100'
            '1160'
            '1170'
            '1180'
            '1190'
            '1200'
            '1210'
            '1220'
            '1230'
            '1240'
            '1250'
            '1260'
            '1270'
            '1280'
            '1290'
            '1300')
        end
      end
      object GroupBox_VerPo: TGroupBox
        Left = 450
        Top = 298
        Width = 269
        Height = 151
        Caption = ' '#1048#1085#1092#1086' '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 4
        object Label6: TLabel
          Left = 86
          Top = 59
          Width = 48
          Height = 16
          Caption = #1042#1077#1088#1089#1080#1103
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label4: TLabel
          Left = 18
          Top = 23
          Width = 112
          Height = 16
          Caption = #1054#1073#1088#1072#1090#1085#1072#1103' '#1089#1074#1103#1079#1100
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object ARCH_Con: TBitBtn
          Left = 138
          Top = 20
          Width = 120
          Height = 28
          Caption = #1042#1099#1082#1083#1102#1095#1077#1085#1072
          Enabled = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          Kind = bkNo
        end
        object Edit_VerPo0: TEdit
          Left = 138
          Top = 57
          Width = 28
          Height = 24
          TabStop = False
          Color = clMoneyGreen
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentFont = False
          ReadOnly = True
          TabOrder = 1
        end
        object Edit_VerPo1: TEdit
          Left = 168
          Top = 57
          Width = 28
          Height = 24
          TabStop = False
          Color = clMoneyGreen
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentFont = False
          ReadOnly = True
          TabOrder = 2
        end
        object Edit_VerPo2: TEdit
          Left = 198
          Top = 57
          Width = 28
          Height = 24
          TabStop = False
          Color = clMoneyGreen
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentFont = False
          ReadOnly = True
          TabOrder = 3
        end
        object Edit_VerPo3: TEdit
          Left = 228
          Top = 57
          Width = 28
          Height = 24
          TabStop = False
          Color = clMoneyGreen
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentFont = False
          ReadOnly = True
          TabOrder = 4
        end
        object Button5: TButton
          Left = 8
          Top = 88
          Width = 120
          Height = 25
          Caption = #1057#1090#1072#1090'. '#1072#1085#1072#1083#1080#1079
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 5
        end
        object btnPwmAuto: TButton
          Left = 192
          Top = 216
          Width = 120
          Height = 26
          Caption = #1064#1048#1052' '#1072#1074#1090#1086
          Enabled = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 6
        end
        object Panel_ErrorConnectCount: TPanel
          Left = 8
          Top = 120
          Width = 105
          Height = 20
          Alignment = taLeftJustify
          BorderWidth = 1
          Caption = ' '#1054#1096#1080#1073#1086#1082' '#1089#1074#1103#1079#1080' '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Courier New'
          Font.Style = []
          ParentFont = False
          TabOrder = 7
        end
        object Edit_ErrorConnectCount: TEdit
          Left = 114
          Top = 120
          Width = 67
          Height = 20
          TabStop = False
          Color = clMoneyGreen
          Ctl3D = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Courier New'
          Font.Style = []
          ParentCtl3D = False
          ParentFont = False
          ReadOnly = True
          TabOrder = 8
        end
      end
    end
    object TabSheet_ModBusParam: TTabSheet
      Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' ModBus'
      ImageIndex = 1
      object GroupBox_SettingsForModbus: TGroupBox
        Left = 2
        Top = 7
        Width = 543
        Height = 274
        Caption = '   '#1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1076#1083#1103' '#1041#1044' ModBus   '
        Enabled = False
        TabOrder = 0
        object Label_3_01: TLabel
          Left = 24
          Top = 24
          Width = 67
          Height = 13
          Caption = #1053#1086#1084#1077#1088' '#1073#1083#1086#1082#1072
        end
        object Label_3_02: TLabel
          Left = 24
          Top = 73
          Width = 81
          Height = 13
          Caption = #1069#1082#1089#1087#1086#1079#1080#1094#1080#1103', '#1084#1089
        end
        object Label_3_03: TLabel
          Left = 23
          Top = 123
          Width = 98
          Height = 13
          Caption = #1052#1080#1085#1080#1084#1072#1083#1100#1085#1099#1081' '#1089#1095#1105#1090
        end
        object Label_3_04: TLabel
          Left = 24
          Top = 173
          Width = 104
          Height = 13
          Caption = #1052#1072#1082#1089#1080#1084#1072#1083#1100#1085#1099#1081' '#1089#1095#1105#1090
        end
        object Label_3_05: TLabel
          Left = 24
          Top = 223
          Width = 105
          Height = 13
          Caption = #1059#1088#1086#1074#1077#1085#1100' '#1087#1077#1088#1077#1075#1088#1091#1079#1082#1080
        end
        object Label_3_06: TLabel
          Left = 197
          Top = 26
          Width = 96
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
          Width = 118
          Height = 13
          Caption = #1059#1088#1086#1074#1077#1085#1100' '#1090#1088#1077#1074#1086#1075#1080' 1 * 10'
        end
        object Label_3_09: TLabel
          Left = 197
          Top = 174
          Width = 118
          Height = 13
          Caption = #1059#1088#1086#1074#1077#1085#1100' '#1090#1088#1077#1074#1086#1075#1080' 2 * 10'
        end
        object Label_3_10: TLabel
          Left = 197
          Top = 225
          Width = 118
          Height = 13
          Caption = #1059#1088#1086#1074#1077#1085#1100' '#1090#1088#1077#1074#1086#1075#1080' 3 * 10'
        end
        object Label_3_11: TLabel
          Left = 372
          Top = 25
          Width = 35
          Height = 13
          Caption = #1060#1086#1085', '#1089
        end
        object Label_3_12: TLabel
          Left = 371
          Top = 74
          Width = 152
          Height = 13
          Caption = #1044#1083#1080#1090'. '#1087#1086#1076#1080#1085#1090#1077#1088#1074#1072#1083#1072' '#1092#1086#1085#1072', '#1084#1089
        end
        object Label_3_13: TLabel
          Left = 373
          Top = 124
          Width = 128
          Height = 13
          Caption = #1044#1083#1080#1090'. '#1089#1080#1075#1085#1072#1083#1072' '#1090#1088#1077#1074#1086#1075#1080', '#1089
        end
        object Label_3_14: TLabel
          Left = 373
          Top = 176
          Width = 118
          Height = 13
          Caption = #1044#1083#1080#1090'. '#1089#1080#1075#1085#1072#1083#1072' '#1074#1080#1076#1077#1086', '#1089
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
          Left = 449
          Top = 240
          Width = 78
          Height = 25
          Caption = #1047#1072#1087#1080#1089#1100
          Enabled = False
          TabOrder = 14
        end
        object Button_ModBus_SetDef: TButton
          Left = 352
          Top = 240
          Width = 86
          Height = 25
          Caption = #1055#1086' '#1091#1084#1086#1083#1095#1072#1085#1080#1102
          Enabled = False
          TabOrder = 15
        end
      end
    end
  end
end
