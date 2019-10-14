object Form_82_Spectr_BD84: TForm_82_Spectr_BD84
  Left = 179
  Top = 100
  BorderStyle = bsDialog
  Caption = #1057#1087#1077#1082#1090#1088' ('#1041#1044' 84) '
  ClientHeight = 804
  ClientWidth = 1173
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
  object Panel_Bottom: TPanel
    Left = 0
    Top = 721
    Width = 1173
    Height = 83
    Align = alBottom
    TabOrder = 0
    object Label_Znachenie_MAX: TLabel
      Left = 346
      Top = 4
      Width = 117
      Height = 13
      Caption = #1047#1085#1072#1095#1077#1085#1080#1077' MAX ['#1077#1076'.]'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_Kanal_MAX: TLabel
      Left = 348
      Top = 43
      Width = 97
      Height = 13
      Caption = #1050#1072#1085#1072#1083' MAX ['#1077#1076'.]'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_Integral: TLabel
      Left = 488
      Top = 4
      Width = 96
      Height = 13
      Caption = #1048#1085#1090#1077#1075#1088#1072#1083' ['#1080#1084#1087'.]'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_Intensivnost: TLabel
      Left = 486
      Top = 43
      Width = 166
      Height = 13
      Caption = #1048#1085#1090#1077#1085#1089#1080#1074#1085#1086#1089#1090#1100' ['#1080#1084#1087'./'#1089#1077#1082'.] '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_TimeNaborSpektra: TLabel
      Left = 131
      Top = 2
      Width = 181
      Height = 13
      Caption = #1042#1088#1077#1084#1103' '#1095#1090#1077#1085#1080#1103' '#1089#1087#1077#1082#1090#1088#1072' ['#1084#1089#1077#1082'.]'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_TimeSumm: TLabel
      Left = 667
      Top = 3
      Width = 136
      Height = 13
      Caption = #1042#1088#1077#1084#1103' '#1089#1091#1084#1084#1072#1088#1085#1086#1077' ['#1089'.] '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_TimeSys: TLabel
      Left = 667
      Top = 43
      Width = 134
      Height = 13
      Caption = #1042#1088#1077#1084#1103' '#1089#1080#1089#1090#1077#1084#1085#1086#1077' ['#1089'.] '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_TimeReadySpektra: TLabel
      Left = 132
      Top = 43
      Width = 208
      Height = 13
      Caption = #1042#1088#1077#1084#1103' '#1075#1086#1090#1086#1074#1085#1086#1089#1090#1080' '#1089#1087#1077#1082#1090#1088#1072' ['#1084#1089#1077#1082'.]'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Edit_Znachenie_MAX: TEdit
      Left = 348
      Top = 20
      Width = 113
      Height = 21
      ReadOnly = True
      TabOrder = 0
      Text = '0'
    end
    object Edit_Kanal_MAX: TEdit
      Left = 348
      Top = 59
      Width = 112
      Height = 21
      ReadOnly = True
      TabOrder = 1
      Text = '0'
    end
    object Edit_Integral: TEdit
      Left = 488
      Top = 19
      Width = 108
      Height = 21
      ReadOnly = True
      TabOrder = 2
      Text = '0'
    end
    object Edit_Intensivnost: TEdit
      Left = 488
      Top = 58
      Width = 107
      Height = 21
      ReadOnly = True
      TabOrder = 3
      Text = '0.00'
    end
    object Edit_TimeSumm: TEdit
      Left = 667
      Top = 17
      Width = 118
      Height = 21
      ReadOnly = True
      TabOrder = 4
      Text = '0.000'
    end
    object Edit_TimeNaborSpektra: TEdit
      Left = 132
      Top = 18
      Width = 126
      Height = 21
      ReadOnly = True
      TabOrder = 5
      Text = '0'
    end
    object GroupBox_SpektrGraph: TGroupBox
      Left = 5
      Top = 5
      Width = 102
      Height = 73
      Caption = '   '#1057#1087#1077#1082#1090#1088'   '
      TabOrder = 6
      object RadioButton_Graph: TRadioButton
        Left = 5
        Top = 19
        Width = 73
        Height = 17
        Caption = #1043#1088#1072#1092#1080#1082
        TabOrder = 0
        OnClick = RadioButton_GraphClick
      end
      object RadioButton_Gistogramma: TRadioButton
        Left = 5
        Top = 43
        Width = 91
        Height = 17
        Caption = #1043#1080#1089#1090#1086#1075#1088#1072#1084#1084#1072
        Checked = True
        TabOrder = 1
        TabStop = True
        OnClick = RadioButton_GistogrammaClick
      end
    end
    object GroupBox_SpektrKanal: TGroupBox
      Left = 1081
      Top = 5
      Width = 80
      Height = 73
      Caption = '   '#1057#1087#1077#1082#1090#1088'   '
      TabOrder = 7
      object RadioButton_Kanal: TRadioButton
        Left = 5
        Top = 19
        Width = 68
        Height = 17
        Caption = #1050#1072#1085#1072#1083#1099
        Checked = True
        TabOrder = 0
        TabStop = True
        OnClick = RadioButton_KanalClick
      end
      object RadioButton_Volt: TRadioButton
        Left = 5
        Top = 43
        Width = 68
        Height = 17
        Caption = #1042#1086#1083#1100#1090#1099
        TabOrder = 1
        OnClick = RadioButton_VoltClick
      end
    end
    object Edit_TimeSys: TEdit
      Left = 667
      Top = 57
      Width = 118
      Height = 21
      ReadOnly = True
      TabOrder = 8
      Text = '0.000'
    end
    object Edit_TimeReadySpektra: TEdit
      Left = 133
      Top = 59
      Width = 126
      Height = 21
      ReadOnly = True
      TabOrder = 9
      Text = '0'
    end
  end
  object Panel_Top: TPanel
    Left = 0
    Top = 0
    Width = 1173
    Height = 41
    Align = alTop
    TabOrder = 1
    object Button_Spectr: TButton
      Left = 256
      Top = 8
      Width = 177
      Height = 25
      Caption = #1053#1072#1095#1072#1090#1100' '#1085#1072#1073#1086#1088' '#1089#1087#1077#1082#1090#1088#1072
      Enabled = False
      TabOrder = 0
      OnClick = Button_SpectrClick
    end
    object Button_ClearSpektr: TButton
      Left = 477
      Top = 8
      Width = 105
      Height = 25
      Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1089#1087#1077#1082#1090#1088
      TabOrder = 1
      OnClick = Button_ClearSpektrClick
    end
    object Button_Mashtab: TButton
      Left = 602
      Top = 8
      Width = 75
      Height = 25
      Caption = #1056#1072#1089#1090#1103#1085#1091#1090#1100
      TabOrder = 2
      OnClick = Button_MashtabClick
    end
    object Panel_TimeSpektr: TPanel
      Left = 706
      Top = 3
      Width = 412
      Height = 34
      BevelInner = bvLowered
      Color = clMedGray
      TabOrder = 3
      object Label_TimeSpektr: TLabel
        Left = 10
        Top = 9
        Width = 140
        Height = 16
        Caption = #1042#1088#1077#1084#1103' '#1089#1085#1103#1090#1080#1103' '#1057#1055#1045#1050#1058#1056#1040
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = 'Courier New'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label_TimeSpektrSek: TLabel
        Left = 228
        Top = 8
        Width = 84
        Height = 16
        Caption = '= 0,200 ['#1089'.]'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Courier New'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object SpinEdit_TimeSpektr: TCSpinEdit
        Left = 157
        Top = 6
        Width = 66
        Height = 22
        Color = clMoneyGreen
        MaxValue = 254
        MinValue = 8
        TabOrder = 0
        Value = 8
        OnChange = SpinEdit_TimeSpektrChange
      end
      object Button_WriteTimeSpektr: TButton
        Left = 323
        Top = 5
        Width = 80
        Height = 25
        Cursor = crHandPoint
        Caption = #1047#1072#1087#1080#1089#1072#1090#1100
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = 'Courier New'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
        OnClick = Button_WriteTimeSpektrClick
      end
    end
  end
  object Panel_Left: TPanel
    Left = 0
    Top = 41
    Width = 97
    Height = 680
    Align = alLeft
    TabOrder = 2
    object Label_Xm1: TLabel
      Left = 8
      Top = 9
      Width = 48
      Height = 13
      Caption = #1050#1072#1085#1072#1083' 1'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_Max_Xm1: TLabel
      Left = 7
      Top = 48
      Width = 74
      Height = 13
      Caption = #1052#1072#1082#1089#1080#1084#1091#1084' 1'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Edit_Xm1: TEdit
      Left = 6
      Top = 23
      Width = 73
      Height = 21
      ReadOnly = True
      TabOrder = 0
    end
    object Edit_Max_Xm1: TEdit
      Left = 6
      Top = 63
      Width = 73
      Height = 21
      ReadOnly = True
      TabOrder = 1
    end
  end
  object Panel_Right: TPanel
    Left = 1070
    Top = 41
    Width = 103
    Height = 680
    Align = alRight
    TabOrder = 3
  end
  object Panel_Graph: TPanel
    Left = 97
    Top = 41
    Width = 973
    Height = 680
    Align = alClient
    Color = clWhite
    TabOrder = 4
    object PaintBox_Graph: TPaintBox
      Left = 1
      Top = 1
      Width = 971
      Height = 678
      Align = alClient
    end
    object Image_Graph: TImage
      Left = 1
      Top = 1
      Width = 971
      Height = 678
      Align = alClient
      OnMouseUp = Image_GraphMouseUp
    end
  end
  object Timer_Obnovleniya_Spectra: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer_Obnovleniya_SpectraTimer
    Left = 16
    Top = 8
  end
end
