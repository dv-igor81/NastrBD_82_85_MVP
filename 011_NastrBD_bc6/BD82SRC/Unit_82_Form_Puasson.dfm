object Form_Puasson: TForm_Puasson
  Left = 614
  Top = 634
  Width = 492
  Height = 336
  BorderIcons = [biMinimize, biMaximize]
  Caption = #1055#1059#1040#1057#1057#1054#1053' ('#1057#1095#1105#1090' '#1079#1072' '#1091#1089#1090#1072#1085#1086#1074#1083#1077#1085#1085#1099#1081' '#1074' '#1041#1044' '#1080#1085#1090#1077#1088#1074#1072#1083' '#1074#1088#1077#1084#1077#1085#1080')'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  OnHide = FormHide
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object ScrollBox1: TScrollBox
    Left = 0
    Top = 0
    Width = 476
    Height = 298
    Align = alClient
    TabOrder = 0
    object Label_kolichestvo: TLabel
      Left = 8
      Top = 134
      Width = 138
      Height = 13
      Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1080#1089#1087#1099#1090#1072#1085#1080#1081
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_fileName: TLabel
      Left = 3
      Top = 174
      Width = 258
      Height = 13
      Caption = #1060#1072#1081#1083' '#1089' '#1088#1077#1079#1091#1083#1100#1090#1072#1090#1072#1084#1080'(C:\'#1058#1057#1056#1052'\BD82\*.txt)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_kolichestvo_interval: TLabel
      Left = 155
      Top = 153
      Width = 93
      Height = 13
      Caption = #1086#1090' 1 '#1076#1086' 300 000'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_Chislo_Izmereniy: TLabel
      Left = 8
      Top = 106
      Width = 206
      Height = 13
      Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1080#1079#1084#1077#1088#1077#1085#1080#1081' '#1074' '#1092#1072#1081#1083#1077' = '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object GroupBox_Znachenie: TGroupBox
      Left = 9
      Top = 8
      Width = 108
      Height = 49
      Caption = '   '#1047#1085#1072#1095#1077#1085#1080#1077'   '
      TabOrder = 0
      object Edit_Znachenie: TEdit
        Left = 8
        Top = 16
        Width = 65
        Height = 21
        Color = clCream
        TabOrder = 0
      end
    end
    object GroupBox_Srednee: TGroupBox
      Left = 122
      Top = 8
      Width = 108
      Height = 49
      Caption = '   '#1057#1088#1077#1076#1085#1077#1077' '#1079#1085'.   '
      TabOrder = 1
      object Edit_Srednee: TEdit
        Left = 8
        Top = 16
        Width = 65
        Height = 21
        Color = clCream
        TabOrder = 0
      end
    end
    object GroupBox_Dispersiya: TGroupBox
      Left = 235
      Top = 8
      Width = 108
      Height = 49
      Caption = '   '#1044#1080#1089#1087#1077#1088#1089#1080#1103'   '
      TabOrder = 2
      object Edit_dispersiya: TEdit
        Left = 8
        Top = 16
        Width = 65
        Height = 21
        Color = clCream
        TabOrder = 0
      end
    end
    object GroupBox_Koeph: TGroupBox
      Left = 349
      Top = 8
      Width = 108
      Height = 49
      Caption = '   '#1050#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090'   '
      TabOrder = 3
      object Edit_koeph: TEdit
        Left = 8
        Top = 16
        Width = 65
        Height = 21
        Color = clCream
        TabOrder = 0
      end
    end
    object Button_exit: TButton
      Left = 26
      Top = 66
      Width = 75
      Height = 25
      Caption = #1042#1099#1093#1086#1076
      TabOrder = 4
      OnClick = Button_exitClick
    end
    object Button_graph: TButton
      Left = 136
      Top = 66
      Width = 75
      Height = 25
      Caption = #1043#1088#1072#1092#1080#1082' '
      DragKind = dkDock
      TabOrder = 5
      OnClick = Button_graphClick
    end
    object Button_start: TButton
      Left = 246
      Top = 66
      Width = 75
      Height = 25
      Caption = #1053#1040#1063#1040#1051#1048
      TabOrder = 6
      OnClick = Button_startClick
    end
    object Button_stop: TButton
      Left = 357
      Top = 66
      Width = 75
      Height = 25
      Caption = #1057#1058#1054#1055
      Enabled = False
      TabOrder = 7
      OnClick = Button_stopClick
    end
    object SpinEdit_kolichestvo: TCSpinEdit
      Left = 151
      Top = 132
      Width = 121
      Height = 22
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      MaxValue = 300000
      MinValue = 1
      ParentFont = False
      TabOrder = 8
      Value = 300000
    end
    object Edit_fileName: TEdit
      Left = 266
      Top = 170
      Width = 199
      Height = 21
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 9
      Text = 'poissonBD82.txt'
    end
    object GroupBox_kontroliruem: TGroupBox
      Left = 8
      Top = 208
      Width = 457
      Height = 57
      Caption = '   '#1050#1086#1085#1090#1088#1086#1083#1100' '#1089#1095#1080#1090#1072#1085#1085#1099#1093' '#1079#1085#1072#1095#1077#1085#1080#1081'   '
      TabOrder = 10
      object Label_nomer_elem: TLabel
        Left = 8
        Top = 28
        Width = 64
        Height = 13
        Caption = #8470' '#1069#1083#1077#1084#1077#1085#1090#1072
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label_znach_elem: TLabel
        Left = 254
        Top = 28
        Width = 51
        Height = 13
        Caption = #1047#1085#1072#1095#1077#1085#1080#1077' '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object SpinEdit_nomer_elem: TCSpinEdit
        Left = 77
        Top = 24
        Width = 121
        Height = 22
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        MaxValue = 300000
        MinValue = 1
        ParentFont = False
        TabOrder = 0
        Value = 1
      end
      object Edit_znach_elem: TEdit
        Left = 317
        Top = 24
        Width = 105
        Height = 21
        Color = clCream
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        ReadOnly = True
        TabOrder = 1
      end
    end
    object StatusBar: TStatusBar
      Left = 0
      Top = 275
      Width = 472
      Height = 19
      Panels = <
        item
          Width = 400
        end
        item
          Width = 50
        end>
      SimplePanel = False
    end
  end
end
