object WindowMainBd85: TWindowMainBd85
  Left = 793
  Top = 171
  AutoScroll = False
  BorderIcons = [biSystemMenu, biMinimize]
  BorderWidth = 1
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1041#1044' 85'
  ClientHeight = 625
  ClientWidth = 662
  Color = clBtnFace
  Constraints.MaxHeight = 665
  Constraints.MaxWidth = 680
  Constraints.MinHeight = 350
  Constraints.MinWidth = 385
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl_WindowBd85: TPageControl
    Left = 0
    Top = 0
    Width = 662
    Height = 625
    ActivePage = TabSheet_MainParam
    Align = alClient
    Style = tsFlatButtons
    TabIndex = 0
    TabOrder = 0
    OnChange = PageControl_WindowBd85Change
    object TabSheet_MainParam: TTabSheet
      Caption = #1054#1089#1085#1086#1074#1085#1099#1077' '#1087#1072#1088#1072#1084#1077#1090#1088#1099
      object ScrollBox_MainParam: TScrollBox
        Left = 0
        Top = 0
        Width = 654
        Height = 594
        Align = alClient
        TabOrder = 0
        object Label_ChangeEEPROM: TLabel
          Left = 454
          Top = 569
          Width = 190
          Height = 19
          Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1077' '#1080#1079#1084#1077#1085#1077#1085#1080#1103
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clRed
          Font.Height = -16
          Font.Name = 'Courier New'
          Font.Style = [fsItalic]
          ParentFont = False
          Visible = False
        end
        object panel_Connect: TPanel
          Left = 448
          Top = 5
          Width = 201
          Height = 263
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
            Top = 148
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
            Top = 45
            Width = 187
            Height = 101
            BevelOuter = bvNone
            TabOrder = 2
            object groupBox_ComPort: TGroupBox
              Left = 0
              Top = 0
              Width = 187
              Height = 101
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
              Height = 101
              Align = alClient
              Caption = ' TCP/IP '
              TabOrder = 1
              object label_IP_Addr: TLabel
                Left = 11
                Top = 13
                Width = 44
                Height = 13
                Caption = 'IP '#1040#1076#1088#1077#1089
              end
              object label_TCP_Port: TLabel
                Left = 10
                Top = 55
                Width = 49
                Height = 13
                Caption = 'TCP '#1055#1086#1088#1090
              end
              object textBox_IP_Addr: TEdit
                Left = 9
                Top = 29
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
                Top = 71
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
            Top = 204
            Width = 121
            Height = 23
            Caption = #1053#1072#1095#1072#1090#1100
            TabOrder = 3
            OnClick = button_StartStopClick
          end
          object label_Hint: TPanel
            Left = 8
            Top = 230
            Width = 189
            Height = 29
            BevelInner = bvRaised
            BevelOuter = bvLowered
            Caption = 'label_Hint'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlue
            Font.Height = -13
            Font.Name = 'Courier New'
            Font.Style = [fsItalic]
            ParentFont = False
            TabOrder = 4
          end
        end
        object GroupBox_Scaling: TGroupBox
          Left = 1
          Top = 221
          Width = 446
          Height = 141
          Caption = ' '#1055#1086#1083#1091#1095#1077#1085#1080#1077' '#1089#1095#1105#1090#1072' '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
          object Label_TimeMetering: TLabel
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
          object Edit_TimeMeteringLimit: TEdit
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
            TabOrder = 0
            Text = '60'
          end
          object Panel_MiddleSecondScaling_0: TPanel
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
            TabOrder = 1
          end
          object Panel_MiddleSecondScaling_1: TPanel
            Left = 249
            Top = 38
            Width = 68
            Height = 20
            TabOrder = 2
          end
          object Edit_MiddleSecondScaling: TEdit
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
            TabOrder = 3
          end
          object Edit_MiddleSecondScaling_3: TEdit
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
            TabOrder = 4
            Text = #1080#1084#1087'/'#1089
          end
          object Panel_TotalScaling_0: TPanel
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
            TabOrder = 5
          end
          object Panel_TotalScaling_1: TPanel
            Left = 249
            Top = 60
            Width = 68
            Height = 20
            TabOrder = 6
          end
          object Edit_TotalScaling: TEdit
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
            TabOrder = 7
          end
          object Edit_TotalScaling_3: TEdit
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
            TabOrder = 8
            Text = ' '#1080#1084#1087
          end
          object Panel_TimeScaling_0: TPanel
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
            TabOrder = 9
          end
          object Panel_TimeScaling_1: TPanel
            Left = 249
            Top = 82
            Width = 68
            Height = 20
            TabOrder = 10
          end
          object Edit_TimeScaling: TEdit
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
            TabOrder = 11
          end
          object Edit_TimeScaling_3: TEdit
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
            TabOrder = 12
            Text = '  '#1089
          end
          object button_ClearScaling: TButton
            Left = 8
            Top = 108
            Width = 120
            Height = 25
            Caption = #1057#1073#1088#1086#1089
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = 'Courier New'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 13
            OnClick = button_ClearScalingClick
          end
          object button_StartStopScaling: TButton
            Left = 128
            Top = 108
            Width = 120
            Height = 25
            Caption = #1057#1090#1072#1088#1090
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = 'Courier New'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 14
            OnClick = button_StartStopScalingClick
          end
          object button_SaveToFile: TButton
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
        object GroupBox_VerPo: TGroupBox
          Left = 448
          Top = 268
          Width = 202
          Height = 177
          Caption = ' '#1048#1085#1092#1086' '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -13
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
          object Label_VerPo: TLabel
            Left = 35
            Top = 130
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
          object Edit_VerPo3: TEdit
            Left = 93
            Top = 148
            Width = 25
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
            TabOrder = 0
          end
          object Edit_VerPo0: TEdit
            Left = 12
            Top = 148
            Width = 25
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
            Left = 39
            Top = 148
            Width = 25
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
            Left = 66
            Top = 148
            Width = 25
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
          object Panel_ErrorConnectCount: TPanel
            Left = 6
            Top = 19
            Width = 131
            Height = 20
            BevelInner = bvLowered
            BorderWidth = 1
            Caption = ' '#1054#1096#1080#1073#1086#1082' '#1089#1074#1103#1079#1080' '
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'Courier New'
            Font.Style = []
            ParentFont = False
            TabOrder = 4
          end
          object Edit_ErrorConnectCount: TEdit
            Left = 141
            Top = 19
            Width = 54
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
            TabOrder = 5
          end
          object GroupBox_ReverseLink: TGroupBox
            Left = 6
            Top = 40
            Width = 146
            Height = 59
            Caption = ' '#1054#1073#1088#1072#1090#1085#1072#1103' '#1089#1074#1103#1079#1100' '
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -13
            Font.Name = 'Courier New'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 6
            object radioButton_ArchOn: TRadioButton
              Left = 24
              Top = 16
              Width = 89
              Height = 17
              Caption = #1042#1082#1083#1102#1095#1077#1085#1072
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -13
              Font.Name = 'Courier New'
              Font.Style = []
              ParentFont = False
              TabOrder = 0
              OnClick = radioButton_ArchOnClick
            end
            object radioButton_ArchOff: TRadioButton
              Left = 24
              Top = 35
              Width = 97
              Height = 17
              Caption = #1042#1099#1082#1083#1102#1095#1077#1085#1072
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -13
              Font.Name = 'Courier New'
              Font.Style = []
              ParentFont = False
              TabOrder = 1
              OnClick = radioButton_ArchOffClick
            end
          end
          object BitBtn_ArchOnOffDisplay: TBitBtn
            Left = 8
            Top = 102
            Width = 145
            Height = 28
            Cancel = True
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -13
            Font.Name = 'Courier New'
            Font.Style = [fsBold]
            ModalResult = 7
            ParentFont = False
            TabOrder = 7
            NumGlyphs = 2
          end
        end
        object GroupBox_Rate: TGroupBox
          Left = 1
          Top = -1
          Width = 446
          Height = 219
          Caption = ' '#1048#1085#1092#1086#1088#1084#1072#1094#1080#1103' '#1089' '#1041#1044' '
          Ctl3D = True
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentCtl3D = False
          ParentFont = False
          TabOrder = 3
          object Panel_rate_Description: TPanel
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
            TabOrder = 0
          end
          object Panel_rate_Code: TPanel
            Left = 250
            Top = 16
            Width = 67
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
            TabOrder = 1
          end
          object Panel_rate_Value: TPanel
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
            TabOrder = 2
          end
          object Panel_rate_Unit: TPanel
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
            TabOrder = 3
          end
          object Panel_IndAddr_0: TPanel
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
            TabOrder = 4
          end
          object Panel_IndAddr_1: TPanel
            Left = 250
            Top = 38
            Width = 67
            Height = 20
            TabOrder = 5
          end
          object Edit_IndAddr: TEdit
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
            TabOrder = 6
          end
          object Panel_IndAddr_3: TPanel
            Left = 394
            Top = 38
            Width = 43
            Height = 20
            TabOrder = 7
          end
          object Panel_GroupAdr_0: TPanel
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
            TabOrder = 8
          end
          object Panel_GroupAdr_1: TPanel
            Left = 250
            Top = 60
            Width = 67
            Height = 20
            TabOrder = 9
          end
          object Edit_GroupAdr: TEdit
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
            TabOrder = 10
          end
          object Panel_GroupAdr_3: TPanel
            Left = 394
            Top = 60
            Width = 43
            Height = 20
            TabOrder = 11
          end
          object Panel_Temperature_0: TPanel
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
            TabOrder = 12
          end
          object Edit_Temperature_Code: TEdit
            Left = 251
            Top = 82
            Width = 66
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
          object Edit_Temperature_Value: TEdit
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
            TabOrder = 14
          end
          object Edit_Temperature_3: TEdit
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
          object Panel_DNU_0: TPanel
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
            TabOrder = 16
          end
          object Edit_DNU_Code: TEdit
            Left = 251
            Top = 104
            Width = 66
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
          end
          object Edit_DNU_Value: TEdit
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
            TabOrder = 18
          end
          object Edit_DNU_3: TEdit
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
            TabOrder = 19
            Text = '   '#1042
          end
          object Panel_VoltageHi_0: TPanel
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
            TabOrder = 20
          end
          object Edit_VoltageHi_Code: TEdit
            Left = 251
            Top = 126
            Width = 66
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
          end
          object Edit_VoltageHi_Value: TEdit
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
            TabOrder = 22
          end
          object Edit_VoltageHi_3: TEdit
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
            TabOrder = 23
            Text = '   '#1042
          end
          object Panel_WidthPwm_0: TPanel
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
            TabOrder = 24
          end
          object Edit_WidthPwm_Code: TEdit
            Left = 251
            Top = 148
            Width = 66
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
            TabOrder = 25
          end
          object Edit_WidthPwm_Value: TEdit
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
            TabOrder = 26
          end
          object Edit_WidthPwm_3: TEdit
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
            Text = '  '#1084#1082#1089
          end
          object Panel_PeriodPwm_0: TPanel
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
            TabOrder = 28
          end
          object Edit_PeriodPwm_Code: TEdit
            Left = 251
            Top = 170
            Width = 66
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
          object Edit_PeriodPwm_Value: TEdit
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
            TabOrder = 30
          end
          object Edit_PeriodPwm_3: TEdit
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
            TabOrder = 31
            Text = '  '#1084#1082#1089
          end
          object Panel_Scaling_0: TPanel
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
            TabOrder = 32
          end
          object Panel_Scaling_1: TPanel
            Left = 250
            Top = 192
            Width = 67
            Height = 20
            TabOrder = 33
          end
          object Edit_Scaling: TEdit
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
            TabOrder = 34
          end
          object Edit_Scaling_3: TEdit
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
            TabOrder = 35
            Text = ' '#1080#1084#1087
          end
        end
        object GroupBox_EEPROM: TGroupBox
          Left = 1
          Top = 365
          Width = 446
          Height = 224
          Caption = ' '#1059#1089#1090#1072#1085#1086#1074#1082#1072' '#1087#1072#1088#1072#1084#1077#1090#1088#1086#1074' '#1041#1044' '
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 4
          object Panel_EEPROM_Description: TPanel
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
            TabOrder = 0
          end
          object Panel_EEPROM_Code: TPanel
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
            TabOrder = 1
          end
          object Panel_EEPROM_Value: TPanel
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
            TabOrder = 2
          end
          object Panel_EEPROM_Unit: TPanel
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
            TabOrder = 3
          end
          object Panel_IndAddrZad_0: TPanel
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
            TabOrder = 4
          end
          object Panel_IndAddrZad_1: TPanel
            Left = 250
            Top = 38
            Width = 67
            Height = 20
            TabOrder = 5
          end
          object Edit_IndAddrZad: TEdit
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
            TabOrder = 6
            OnChange = Edit_IndAddrZadChange
          end
          object Panel_indAddrZad_3: TPanel
            Left = 394
            Top = 38
            Width = 43
            Height = 20
            TabOrder = 7
          end
          object Panel_GroupAdrZad_0: TPanel
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
            TabOrder = 8
          end
          object Panel_GroupAdrZad_1: TPanel
            Left = 250
            Top = 60
            Width = 67
            Height = 20
            TabOrder = 9
          end
          object Edit_GroupAdrZad: TEdit
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
            TabOrder = 10
            OnChange = Edit_GroupAdrZadChange
          end
          object Panel_GroupAdrZad_3: TPanel
            Left = 394
            Top = 60
            Width = 43
            Height = 20
            TabOrder = 11
          end
          object Panel_DnuZad_0: TPanel
            Left = 8
            Top = 82
            Width = 241
            Height = 20
            Alignment = taLeftJustify
            BorderWidth = 1
            Caption = ' '#1047#1085#1072#1095#1077#1085#1080#1077' '#1044#1053#1059' '#1079#1072#1076#1072#1085#1085#1086#1077' '
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Courier New'
            Font.Style = []
            ParentFont = False
            TabOrder = 12
          end
          object Edit_DnuZad_Code: TEdit
            Left = 250
            Top = 82
            Width = 67
            Height = 20
            Color = clCream
            Ctl3D = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'Courier New'
            Font.Style = [fsBold]
            ParentCtl3D = False
            ParentFont = False
            TabOrder = 13
            OnChange = Edit_DnuZad_CodeChange
          end
          object Edit_DnuZad_Value: TMaskEdit
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
            TabOrder = 14
          end
          object Edit_DnuZad_3: TEdit
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
            Text = '   '#1042
          end
          object Panel_VoltageHiZad_0: TPanel
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
            TabOrder = 16
          end
          object Edit_VoltageHiZad_Code: TEdit
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
            TabOrder = 17
          end
          object comboBox_VoltageHiZad_Value: TComboBox
            Left = 320
            Top = 104
            Width = 73
            Height = 22
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'Courier New'
            Font.Style = [fsBold]
            ItemHeight = 14
            ParentFont = False
            TabOrder = 18
            OnChange = comboBox_VoltageHiZad_ValueChange
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
          object Edit_VoltageHiZad_3: TEdit
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
            TabOrder = 19
            Text = '   '#1042
          end
          object Panel_WidthPwmZad_0: TPanel
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
            TabOrder = 20
          end
          object Edit_WidthPwmZad: TEdit
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
            TabOrder = 21
            OnChange = Edit_WidthPwmZadChange
          end
          object Panel_WidthPwmZad_2: TPanel
            Left = 318
            Top = 126
            Width = 75
            Height = 20
            TabOrder = 22
          end
          object Edit_WidthPwmZad_3: TEdit
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
            TabOrder = 23
            Text = ' '#1077#1076'.'
          end
          object Panel_OffsetPwmZad_0: TPanel
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
            TabOrder = 24
          end
          object Edit_OffsetPwmZad: TEdit
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
            TabOrder = 25
            OnChange = Edit_OffsetPwmZadChange
          end
          object Panel_OffsetPwmZad_2: TPanel
            Left = 318
            Top = 148
            Width = 75
            Height = 20
            TabOrder = 26
          end
          object Edit_OffsetPwmZad_3: TEdit
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
          object Panel_PeriodPwmZad_0: TPanel
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
            TabOrder = 28
          end
          object Edit_PeriodPwmZad: TEdit
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
            TabOrder = 29
            OnChange = Edit_PeriodPwmZadChange
          end
          object Panel_PeriodPwmZad_2: TPanel
            Left = 318
            Top = 170
            Width = 75
            Height = 20
            TabOrder = 30
          end
          object Edit_PeriodPwmZad_3: TEdit
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
          object button_WriteToEeprom: TButton
            Left = 9
            Top = 193
            Width = 152
            Height = 25
            Caption = #1047#1072#1087#1080#1089#1100' '#1087#1072#1088#1072#1084#1077#1090#1088#1086#1074
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = 'Courier New'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 32
            OnClick = button_WriteToEepromClick
          end
          object button_FromFile: TButton
            Left = 177
            Top = 193
            Width = 131
            Height = 25
            Caption = #1048#1079' '#1092#1072#1081#1083#1072
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = 'Courier New'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 33
          end
          object btnPwmAuto: TButton
            Left = 321
            Top = 193
            Width = 116
            Height = 25
            Caption = #1064#1048#1052' '#1072#1074#1090#1086
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = 'Courier New'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 34
          end
        end
      end
    end
    object TabSheet_ModBusParam: TTabSheet
      Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' ModBus'
      ImageIndex = 1
      object ScrollBox_SettingsForModBus: TScrollBox
        Left = 0
        Top = 0
        Width = 654
        Height = 594
        Align = alClient
        TabOrder = 0
        object Label_ChangeModBusEEPROM: TLabel
          Left = 454
          Top = 567
          Width = 190
          Height = 19
          Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1077' '#1080#1079#1084#1077#1085#1077#1085#1080#1103
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clRed
          Font.Height = -16
          Font.Name = 'Courier New'
          Font.Style = [fsItalic]
          ParentFont = False
          Visible = False
        end
        object GroupBox_SettingsForModbus: TGroupBox
          Left = 3
          Top = 2
          Width = 543
          Height = 274
          Caption = '   '#1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1076#1083#1103' '#1041#1044' ModBus   '
          TabOrder = 0
          object Label_NumberOfBd: TLabel
            Left = 24
            Top = 24
            Width = 67
            Height = 13
            Caption = #1053#1086#1084#1077#1088' '#1073#1083#1086#1082#1072
          end
          object Label_Exposition: TLabel
            Left = 24
            Top = 73
            Width = 81
            Height = 13
            Caption = #1069#1082#1089#1087#1086#1079#1080#1094#1080#1103', '#1084#1089
          end
          object Label_MinimumCount: TLabel
            Left = 23
            Top = 123
            Width = 98
            Height = 13
            Caption = #1052#1080#1085#1080#1084#1072#1083#1100#1085#1099#1081' '#1089#1095#1105#1090
          end
          object Label_MaximumCount: TLabel
            Left = 24
            Top = 173
            Width = 104
            Height = 13
            Caption = #1052#1072#1082#1089#1080#1084#1072#1083#1100#1085#1099#1081' '#1089#1095#1105#1090
          end
          object Label_LevelOfOverload: TLabel
            Left = 24
            Top = 223
            Width = 105
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100' '#1087#1077#1088#1077#1075#1088#1091#1079#1082#1080
          end
          object Label_QuantityOfInterval: TLabel
            Left = 197
            Top = 26
            Width = 96
            Height = 13
            Caption = #1050#1086#1083'-'#1074#1086' '#1080#1085#1090#1077#1088#1074#1072#1083#1086#1074
          end
          object Label_QuantityOfLook: TLabel
            Left = 197
            Top = 73
            Width = 111
            Height = 13
            Caption = #1050#1086#1083'-'#1074#1086' '#1074#1079#1075#1083#1103#1076#1072' '#1087#1086#1089#1083#1077
          end
          object Label_LevelOfAlarm_1: TLabel
            Left = 197
            Top = 124
            Width = 118
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100' '#1090#1088#1077#1074#1086#1075#1080' 1 * 10'
          end
          object Label_LevelOfAlarm_2: TLabel
            Left = 197
            Top = 174
            Width = 118
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100' '#1090#1088#1077#1074#1086#1075#1080' 2 * 10'
          end
          object Label_LevelOfAlarm_3: TLabel
            Left = 197
            Top = 225
            Width = 118
            Height = 13
            Caption = #1059#1088#1086#1074#1077#1085#1100' '#1090#1088#1077#1074#1086#1075#1080' 3 * 10'
          end
          object Label_Phon: TLabel
            Left = 372
            Top = 25
            Width = 35
            Height = 13
            Caption = #1060#1086#1085', '#1089
          end
          object Label_DurationOfPhon: TLabel
            Left = 371
            Top = 74
            Width = 152
            Height = 13
            Caption = #1044#1083#1080#1090'. '#1087#1086#1076#1080#1085#1090#1077#1088#1074#1072#1083#1072' '#1092#1086#1085#1072', '#1084#1089
          end
          object Label_DurationOfAlarm: TLabel
            Left = 373
            Top = 124
            Width = 128
            Height = 13
            Caption = #1044#1083#1080#1090'. '#1089#1080#1075#1085#1072#1083#1072' '#1090#1088#1077#1074#1086#1075#1080', '#1089
          end
          object Label_DurationOfVideo: TLabel
            Left = 373
            Top = 176
            Width = 118
            Height = 13
            Caption = #1044#1083#1080#1090'. '#1089#1080#1075#1085#1072#1083#1072' '#1074#1080#1076#1077#1086', '#1089
          end
          object Edit_NumberOfBd: TEdit
            Left = 23
            Top = 39
            Width = 140
            Height = 21
            TabOrder = 0
            OnChange = Edit_NumberOfBdChange
          end
          object Edit_Exposition: TEdit
            Left = 23
            Top = 87
            Width = 140
            Height = 21
            TabOrder = 1
            OnChange = Edit_ExpositionChange
          end
          object Edit_MinimumCount: TEdit
            Left = 23
            Top = 138
            Width = 140
            Height = 21
            TabOrder = 2
            OnChange = Edit_MinimumCountChange
          end
          object Edit_MaximumCount: TEdit
            Left = 23
            Top = 189
            Width = 140
            Height = 21
            TabOrder = 3
            OnChange = Edit_MaximumCountChange
          end
          object Edit_LevelOfOverload: TEdit
            Left = 23
            Top = 240
            Width = 140
            Height = 21
            TabOrder = 4
            OnChange = Edit_LevelOfOverloadChange
          end
          object Edit_QuantityOfInterval: TEdit
            Left = 197
            Top = 39
            Width = 143
            Height = 21
            TabOrder = 5
            OnChange = Edit_QuantityOfIntervalChange
          end
          object Edit_QuantityOfLook: TEdit
            Left = 197
            Top = 87
            Width = 143
            Height = 21
            TabOrder = 6
            OnChange = Edit_QuantityOfLookChange
          end
          object Edit_LevelOfAlarm_1: TEdit
            Left = 197
            Top = 138
            Width = 143
            Height = 21
            TabOrder = 7
            OnChange = Edit_LevelOfAlarm_1Change
          end
          object Edit_LevelOfAlarm_2: TEdit
            Left = 197
            Top = 189
            Width = 143
            Height = 21
            TabOrder = 8
            OnChange = Edit_LevelOfAlarm_2Change
          end
          object Edit_LevelOfAlarm_3: TEdit
            Left = 197
            Top = 241
            Width = 142
            Height = 21
            TabOrder = 9
            OnChange = Edit_LevelOfAlarm_3Change
          end
          object Edit_Phon: TEdit
            Left = 372
            Top = 39
            Width = 152
            Height = 21
            TabOrder = 10
            OnChange = Edit_PhonChange
          end
          object Edit_DurationOfPhon: TEdit
            Left = 372
            Top = 87
            Width = 152
            Height = 21
            TabOrder = 11
            OnChange = Edit_DurationOfPhonChange
          end
          object Edit_DurationOfAlarm: TEdit
            Left = 373
            Top = 138
            Width = 152
            Height = 21
            TabOrder = 12
            OnChange = Edit_DurationOfAlarmChange
          end
          object Edit_DurationOfVideo: TEdit
            Left = 374
            Top = 190
            Width = 152
            Height = 21
            TabOrder = 13
            OnChange = Edit_DurationOfVideoChange
          end
          object Button_ModBus_Write: TButton
            Left = 449
            Top = 240
            Width = 78
            Height = 25
            Caption = #1047#1072#1087#1080#1089#1100
            TabOrder = 14
            OnClick = Button_ModBus_WriteClick
          end
          object Button_ModBus_SetDef: TButton
            Left = 352
            Top = 240
            Width = 86
            Height = 25
            Caption = #1055#1086' '#1091#1084#1086#1083#1095#1072#1085#1080#1102
            TabOrder = 15
            OnClick = Button_ModBus_SetDefClick
          end
        end
      end
    end
  end
end
