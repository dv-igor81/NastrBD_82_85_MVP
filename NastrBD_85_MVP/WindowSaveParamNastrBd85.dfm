object WindowSaveParamBd85: TWindowSaveParamBd85
  Left = 556
  Top = 233
  Width = 525
  Height = 245
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = #1047#1072#1087#1080#1089#1100' '#1085#1072#1089#1090#1088#1086#1077#1082' '#1041#1044' 85 '#1074' '#1092#1072#1081#1083
  Color = clBtnFace
  Constraints.MaxHeight = 245
  Constraints.MaxWidth = 525
  Constraints.MinHeight = 170
  Constraints.MinWidth = 250
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object ScrollBox: TScrollBox
    Left = 0
    Top = 0
    Width = 509
    Height = 207
    Align = alClient
    TabOrder = 0
    object Label_FileName: TLabel
      Left = 5
      Top = 9
      Width = 71
      Height = 13
      Caption = #1048#1084#1103' '#1092#1072#1081#1083#1072':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_FileHeader: TLabel
      Left = 5
      Top = 33
      Width = 86
      Height = 13
      Caption = #1050#1086#1084#1084#1077#1085#1090#1072#1088#1080#1081':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_Time: TLabel
      Left = 5
      Top = 57
      Width = 127
      Height = 13
      Caption = #1042#1088#1077#1084#1103' '#1080#1079#1084#1077#1088#1077#1085#1080#1103'('#1089'):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_Number: TLabel
      Left = 5
      Top = 81
      Width = 114
      Height = 13
      Caption = #1050#1086#1083'-'#1074#1086' '#1080#1079#1084#1077#1088#1077#1085#1080#1081':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_Delay: TLabel
      Left = 6
      Top = 102
      Width = 99
      Height = 13
      Caption = #1047#1072#1076#1077#1088#1078#1082#1072' ('#1084#1080#1085'):'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Edit_FileName: TEdit
      Left = 98
      Top = 4
      Width = 401
      Height = 21
      MaxLength = 512
      TabOrder = 0
      OnChange = Edit_FileNameChange
    end
    object Edit_FileHeader: TEdit
      Left = 98
      Top = 28
      Width = 401
      Height = 21
      MaxLength = 512
      TabOrder = 1
      OnChange = Edit_FileHeaderChange
    end
    object Edit_Time: TEdit
      Left = 138
      Top = 52
      Width = 81
      Height = 21
      MaxLength = 512
      TabOrder = 2
      OnChange = Edit_TimeChange
    end
    object Edit_Number: TEdit
      Left = 138
      Top = 76
      Width = 81
      Height = 21
      MaxLength = 512
      TabOrder = 3
      OnChange = Edit_NumberChange
    end
    object Edit_Delay: TEdit
      Left = 138
      Top = 100
      Width = 81
      Height = 21
      MaxLength = 512
      TabOrder = 4
      OnChange = Edit_DelayChange
    end
    object Button_Ok: TButton
      Left = 225
      Top = 52
      Width = 75
      Height = 25
      Caption = #1054#1082
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ModalResult = 1
      ParentFont = False
      TabOrder = 5
      OnClick = Button_OkClick
    end
    object Button_Cancel: TButton
      Left = 306
      Top = 52
      Width = 75
      Height = 25
      Cancel = True
      Caption = #1054#1090#1084#1077#1085#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ModalResult = 2
      ParentFont = False
      TabOrder = 6
      OnClick = Button_CancelClick
    end
    object Panel_ErrorConnectCount: TPanel
      Left = 6
      Top = 133
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
      TabOrder = 7
    end
    object Edit_ErrorConnectCount: TEdit
      Left = 141
      Top = 133
      Width = 68
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
    object Panel_SummTime: TPanel
      Left = 221
      Top = 82
      Width = 184
      Height = 20
      BevelInner = bvLowered
      BorderWidth = 1
      Caption = ' '#1042#1088#1077#1084#1103' '#1080#1079#1084#1077#1088#1077#1085#1080#1103', ['#1089'.]'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      TabOrder = 9
    end
    object Edit_SummTime: TEdit
      Left = 408
      Top = 82
      Width = 95
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
      TabOrder = 10
    end
    object Panel_CurrTime: TPanel
      Left = 221
      Top = 105
      Width = 184
      Height = 20
      BevelInner = bvLowered
      BorderWidth = 1
      Caption = ' '#1042#1088#1077#1084#1103' '#1090#1077#1082#1091#1097#1077#1077', ['#1089'.] '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      TabOrder = 11
    end
    object Edit_CurrTime: TEdit
      Left = 408
      Top = 105
      Width = 95
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
      TabOrder = 12
    end
    object Panel_Info: TPanel
      Left = 221
      Top = 128
      Width = 121
      Height = 20
      BevelInner = bvLowered
      BorderWidth = 1
      Caption = ' '#1048#1085#1092#1086#1088#1084#1072#1094#1080#1103' '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      TabOrder = 13
    end
    object Edit_Info: TEdit
      Left = 345
      Top = 128
      Width = 158
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
    object Panel_TotalScaling: TPanel
      Left = 6
      Top = 179
      Width = 389
      Height = 20
      BevelInner = bvLowered
      BorderWidth = 1
      Caption = ' '#1057#1091#1084#1084#1072#1088#1085#1099#1081' '#1089#1095#1105#1090' '#1079#1072' '#1074#1088#1077#1084#1103' '#1080#1079#1084#1077#1088#1077#1085#1080#1103' ['#1080#1084#1087'.]'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      TabOrder = 15
    end
    object Edit_TotalScaling: TEdit
      Left = 403
      Top = 179
      Width = 100
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
      TabOrder = 16
    end
    object Edit_MiddleScaling: TEdit
      Left = 403
      Top = 156
      Width = 100
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
    object Panel_MiddleScaling: TPanel
      Left = 6
      Top = 156
      Width = 389
      Height = 20
      BevelInner = bvLowered
      BorderWidth = 1
      Caption = ' '#1057#1088'. '#1089#1095#1105#1090' '#1089' '#1041#1044' '#1079#1072' 1 '#1089#1077#1082'. ['#1080#1084#1087'./'#1089'.]'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      TabOrder = 18
    end
  end
end
