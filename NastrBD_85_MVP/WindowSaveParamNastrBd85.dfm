object WindowSaveParamBd85: TWindowSaveParamBd85
  Left = 556
  Top = 233
  Width = 525
  Height = 205
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = #1047#1072#1087#1080#1089#1100' '#1085#1072#1089#1090#1088#1086#1077#1082' '#1041#1044' 85 '#1074' '#1092#1072#1081#1083
  Color = clBtnFace
  Constraints.MaxHeight = 205
  Constraints.MaxWidth = 525
  Constraints.MinHeight = 100
  Constraints.MinWidth = 210
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
    Height = 167
    Align = alClient
    TabOrder = 0
    object Label_FileName: TLabel
      Left = 2
      Top = 12
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
      Left = 2
      Top = 44
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
      Left = 2
      Top = 72
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
      Left = 2
      Top = 102
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
      Left = 3
      Top = 129
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
      Top = 36
      Width = 401
      Height = 21
      MaxLength = 512
      TabOrder = 1
      OnChange = Edit_FileHeaderChange
    end
    object Edit_Time: TEdit
      Left = 138
      Top = 64
      Width = 81
      Height = 21
      MaxLength = 512
      TabOrder = 2
      OnChange = Edit_TimeChange
    end
    object Edit_Number: TEdit
      Left = 138
      Top = 94
      Width = 81
      Height = 21
      MaxLength = 512
      TabOrder = 3
      OnChange = Edit_NumberChange
    end
    object Edit_Delay: TEdit
      Left = 138
      Top = 124
      Width = 81
      Height = 21
      MaxLength = 512
      TabOrder = 4
      OnChange = Edit_DelayChange
    end
    object Button_Ok: TButton
      Left = 242
      Top = 68
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
    end
    object Button_Cancel: TButton
      Left = 242
      Top = 116
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
    end
  end
end
