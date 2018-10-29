object Form_LoadParam: TForm_LoadParam
  Left = 571
  Top = 217
  Width = 431
  Height = 332
  Caption = #1063#1090#1077#1085#1080#1077' '#1087#1072#1088#1072#1084#1077#1090#1088#1086#1074' '#1041#1044' '#1080#1079' '#1092#1072#1081#1083#1072
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Edit_LogFileName: TEdit
    Left = 8
    Top = 16
    Width = 361
    Height = 21
    TabOrder = 0
  end
  object Button_Browse: TButton
    Left = 371
    Top = 16
    Width = 21
    Height = 21
    Caption = '...'
    TabOrder = 1
    OnClick = Button_BrowseClick
  end
  object Button_Read: TButton
    Left = 320
    Top = 48
    Width = 75
    Height = 25
    Caption = #1063#1080#1090#1072#1090#1100
    TabOrder = 2
    OnClick = Button_ReadClick
  end
  object ListView_DetectionUnits2: TListView
    Left = 104
    Top = 88
    Width = 289
    Height = 161
    Checkboxes = True
    Columns = <
      item
        Caption = 'T ('#176'C)'
        Width = 70
      end
      item
        Caption = 'T ('#1082#1086#1076')'
        Width = 70
      end
      item
        Caption = #1057#1074' ('#1082#1086#1076')'
        Width = -2
        WidthType = (
          -2)
      end>
    ColumnClick = False
    GridLines = True
    TabOrder = 3
    ViewStyle = vsReport
    OnClick = ListView_DetectionUnits2Click
  end
  object ListView_DetectionUnits1: TListView
    Left = 8
    Top = 88
    Width = 89
    Height = 161
    Columns = <
      item
        Caption = #8470' '#1041#1044
        Width = -2
        WidthType = (
          -2)
      end>
    ColumnClick = False
    GridLines = True
    HideSelection = False
    TabOrder = 4
    ViewStyle = vsReport
    OnClick = ListView_DetectionUnits1Click
  end
  object Button_Ok: TButton
    Left = 240
    Top = 264
    Width = 75
    Height = 25
    Caption = #1054#1082
    Enabled = False
    ModalResult = 1
    TabOrder = 5
  end
  object Button_Cancel: TButton
    Left = 320
    Top = 264
    Width = 75
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 6
  end
  object OpenDialog: TOpenDialog
    Left = 8
    Top = 264
  end
end
