object WindowMainBd85: TWindowMainBd85
  Left = 641
  Top = 287
  Width = 796
  Height = 669
  Caption = 'WindowMainBd85'
  Color = clBtnFace
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
  object panel_Connect: TPanel
    Left = 8
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
end
