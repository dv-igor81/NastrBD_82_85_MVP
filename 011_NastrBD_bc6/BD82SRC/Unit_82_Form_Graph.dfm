object Form_Graph: TForm_Graph
  Left = 563
  Top = 447
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1043#1088#1072#1092#1080#1082
  ClientHeight = 417
  ClientWidth = 584
  Color = clBtnFace
  Constraints.MaxHeight = 455
  Constraints.MaxWidth = 600
  Constraints.MinHeight = 455
  Constraints.MinWidth = 600
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object CheckBox_logariphm: TCheckBox
    Left = 8
    Top = 392
    Width = 225
    Height = 17
    Caption = #1051#1086#1075#1072#1088#1080#1092#1084#1080#1095#1077#1089#1082#1080#1081' '#1084#1072#1089#1096#1090#1072#1073' '#1075#1088#1072#1092#1080#1082#1072
    Checked = True
    State = cbChecked
    TabOrder = 0
    OnClick = CheckBox_logariphmClick
  end
  object Chart_Puasson_lin: TChart
    Left = 0
    Top = 0
    Width = 585
    Height = 313
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      #1056#1072#1089#1087#1088#1077#1076#1077#1083#1077#1085#1080#1077' '#1087#1086' '#1055#1091#1072#1089#1089#1086#1085#1091)
    BottomAxis.Automatic = False
    BottomAxis.AutomaticMaximum = False
    BottomAxis.AutomaticMinimum = False
    BottomAxis.Maximum = 25
    View3D = False
    BevelInner = bvLowered
    BorderWidth = 2
    TabOrder = 1
    object Chart_Puasson_log: TChart
      Left = 5
      Top = 5
      Width = 576
      Height = 303
      AnimatedZoom = True
      BackWall.Brush.Color = clWhite
      BackWall.Brush.Style = bsClear
      Title.Text.Strings = (
        #1056#1072#1089#1087#1088#1077#1076#1077#1083#1077#1085#1080#1077' '#1087#1086' '#1055#1091#1072#1089#1089#1086#1085#1091)
      BottomAxis.Automatic = False
      BottomAxis.AutomaticMaximum = False
      BottomAxis.AutomaticMinimum = False
      BottomAxis.Maximum = 100
      LeftAxis.Automatic = False
      LeftAxis.AutomaticMaximum = False
      LeftAxis.AutomaticMinimum = False
      LeftAxis.Logarithmic = True
      LeftAxis.Maximum = 100
      Legend.Visible = False
      View3D = False
      View3DWalls = False
      BevelInner = bvLowered
      BorderWidth = 2
      TabOrder = 0
      object Series4: TLineSeries
        Marks.ArrowLength = 8
        Marks.Visible = False
        SeriesColor = clRed
        Pointer.InflateMargins = True
        Pointer.Style = psRectangle
        Pointer.Visible = False
        XValues.DateTime = False
        XValues.Name = 'X'
        XValues.Multiplier = 1
        XValues.Order = loAscending
        YValues.DateTime = False
        YValues.Name = 'Y'
        YValues.Multiplier = 1
        YValues.Order = loNone
      end
      object Series5: TBarSeries
        Marks.ArrowLength = 20
        Marks.Visible = False
        SeriesColor = clRed
        BarWidthPercent = 10
        XValues.DateTime = False
        XValues.Name = 'X'
        XValues.Multiplier = 1
        XValues.Order = loAscending
        YValues.DateTime = False
        YValues.Name = 'Bar'
        YValues.Multiplier = 1
        YValues.Order = loNone
      end
      object Series6: TLineSeries
        Marks.ArrowLength = 8
        Marks.Visible = False
        SeriesColor = clGreen
        Pointer.InflateMargins = True
        Pointer.Style = psRectangle
        Pointer.Visible = False
        XValues.DateTime = False
        XValues.Name = 'X'
        XValues.Multiplier = 1
        XValues.Order = loAscending
        YValues.DateTime = False
        YValues.Name = 'Y'
        YValues.Multiplier = 1
        YValues.Order = loNone
      end
    end
    object Series1: TLineSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clGreen
      ShowInLegend = False
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
    object Series2: TBarSeries
      Marks.ArrowLength = 20
      Marks.Visible = False
      SeriesColor = clRed
      ShowInLegend = False
      BarWidthPercent = 5
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Bar'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
    object Series3: TLineSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clYellow
      ShowInLegend = False
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object Panel_InfoMain: TPanel
    Left = 2
    Top = 316
    Width = 220
    Height = 70
    BevelInner = bvLowered
    BevelOuter = bvSpace
    TabOrder = 2
    object Label_srednee: TLabel
      Left = 66
      Top = 28
      Width = 105
      Height = 13
      Caption = #1057#1088#1077#1076#1085#1077#1077' '#1079#1085#1072#1095#1077#1085#1080#1077' = '
    end
    object Label_verLoSrab: TLabel
      Left = 10
      Top = 45
      Width = 160
      Height = 13
      Caption = #1042#1077#1088#1086#1103#1090'. '#1083#1086#1078#1085#1099#1093' '#1089#1088#1072#1073#1072#1090'. * E-3 = '
    end
    object Label_Error_Svyazi: TLabel
      Left = 86
      Top = 10
      Width = 85
      Height = 13
      Caption = #1054#1096#1080#1073#1086#1082' '#1089#1074#1103#1079#1080' = '
    end
  end
  object Panel_Vybora: TPanel
    Left = 225
    Top = 316
    Width = 135
    Height = 70
    BevelInner = bvLowered
    BevelOuter = bvSpace
    TabOrder = 3
    object RadioButton_Puasson: TRadioButton
      Left = 7
      Top = 7
      Width = 77
      Height = 17
      Caption = #1055#1091#1072#1089#1089#1086#1085
      Checked = True
      TabOrder = 0
      TabStop = True
      OnClick = RadioButton_PuassonClick
    end
    object RadioButton_inTime: TRadioButton
      Left = 7
      Top = 27
      Width = 125
      Height = 17
      Caption = #1043#1088#1072#1092#1080#1082' '#1074#1086' '#1074#1088#1077#1084#1077#1085#1080
      TabOrder = 1
      OnClick = RadioButton_inTimeClick
    end
    object RadioButton_Gays: TRadioButton
      Left = 7
      Top = 46
      Width = 61
      Height = 17
      Caption = #1043#1072#1091#1089#1089
      TabOrder = 2
      OnClick = RadioButton_GaysClick
    end
  end
  object Panel_InfoDop: TPanel
    Left = 363
    Top = 316
    Width = 217
    Height = 98
    BevelInner = bvLowered
    BevelOuter = bvSpace
    TabOrder = 4
    object Label_koefMorozova: TLabel
      Left = 71
      Top = 41
      Width = 96
      Height = 13
      Caption = #1050#1086#1101#1092'. '#1052#1086#1088#1086#1079#1086#1074#1072' = '
    end
    object Label_znachPoroga: TLabel
      Left = 69
      Top = 7
      Width = 98
      Height = 13
      Caption = #1047#1085#1072#1095#1077#1085#1080#1077' '#1087#1086#1088#1086#1075#1072' = '
    end
    object Label_kolichIzmereniy: TLabel
      Left = 2
      Top = 24
      Width = 168
      Height = 13
      Caption = #1050#1086#1083'-'#1074#1086' '#1089#1090#1088#1086#1082' ('#1089#1095#1077#1090#1086#1074') '#1074' '#1092#1072#1081#1083#1077' =  '
    end
    object Label_Dispersiya: TLabel
      Left = 98
      Top = 58
      Width = 69
      Height = 13
      Caption = #1044#1080#1089#1087#1077#1088#1089#1080#1103' = '
    end
    object Label_FileName: TLabel
      Left = 2
      Top = 75
      Width = 69
      Height = 13
      Caption = #1048#1084#1103' '#1092#1072#1081#1083#1072' = '
    end
  end
  object Timer_ForGraphUpdate: TTimer
    OnTimer = Timer_ForGraphUpdateTimer
    Left = 544
    Top = 320
  end
end
