object frmPreview: TfrmPreview
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = 'frmPreview'
  ClientHeight = 735
  ClientWidth = 1204
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Shape1: TShape
    Left = 0
    Top = 32
    Width = 1204
    Height = 703
    Align = alClient
    Brush.Style = bsClear
    Pen.Color = 16750131
    Pen.Width = 2
    ExplicitLeft = 568
    ExplicitTop = 328
    ExplicitWidth = 65
    ExplicitHeight = 65
  end
  object panWindowsMove: TPanel
    Left = 0
    Top = 0
    Width = 1204
    Height = 32
    Align = alTop
    BevelEdges = [beLeft, beTop, beRight]
    BevelOuter = bvNone
    Color = 16750131
    ParentBackground = False
    TabOrder = 0
    OnMouseDown = panWindowsMoveMouseDown
    object lblFormTitle: TLabel
      Left = 8
      Top = 9
      Width = 80
      Height = 14
      Caption = ' '#48120#47532#48372#44592' ('#51204#52404')'
      Color = clWhite
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = #45208#45588#44256#46357
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
      OnMouseDown = panWindowsMoveMouseDown
    end
    object lblCount: TLabel
      Left = 293
      Top = 9
      Width = 120
      Height = 14
      AutoSize = False
      Caption = #51204#52404' '#44148#49688
      Color = clWhite
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = #45208#45588#44256#46357
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
      OnMouseDown = panWindowsMoveMouseDown
    end
    object Label1: TLabel
      Left = 740
      Top = 9
      Width = 420
      Height = 14
      Alignment = taRightJustify
      AutoSize = False
      Caption = #50676#46988#54616#44256#51088' '#54616#45716'  '#47928#49436#47484' '#53364#47533#54616#49464#50836'. ('#47928#49436#48372#44592#54868#47732#50640' '#54364#49884#46121#45768#45796'.)   '
      Color = clWhite
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = #45208#45588#44256#46357' ExtraBold'
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
      OnMouseDown = panWindowsMoveMouseDown
    end
    object pnlClose: TPanel
      Left = 1172
      Top = 0
      Width = 32
      Height = 32
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 0
      object btnCloseTypeB: TImage
        Left = 4
        Top = 4
        Width = 22
        Height = 22
        Cursor = crHandPoint
        OnClick = btnCloseTypeBClick
      end
    end
    object cboPreviewDocKind: TComboBox
      Left = 120
      Top = 6
      Width = 160
      Height = 22
      Style = csDropDownList
      Font.Charset = HANGEUL_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = #45208#45588#44256#46357
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = cboPreviewDocKindClick
    end
    object cboPreviewDocKind2: TComboBox
      Left = 260
      Top = 27
      Width = 118
      Height = 21
      Style = csDropDownList
      TabOrder = 2
      Visible = False
    end
  end
  object palWait: TPanel
    Left = 300
    Top = 250
    Width = 264
    Height = 80
    BevelOuter = bvNone
    Color = clWhite
    ParentBackground = False
    TabOrder = 1
    Visible = False
    object shpWait: TShape
      Left = 0
      Top = 0
      Width = 264
      Height = 80
      Brush.Style = bsClear
      Pen.Color = 16750131
    end
    object bsPngImageView1: TbsPngImageView
      Left = 12
      Top = 38
      Width = 30
      Height = 30
      DoubleBuffered = False
      ReflectionEffect = False
      ImageIndex = 0
    end
    object lblWait1: TLabel
      Left = 50
      Top = 37
      Width = 109
      Height = 13
      Caption = #51104#49884#47564' '#44592#45796#47140' '#51452#49464#50836'.'
    end
    object lblWait2: TLabel
      Left = 50
      Top = 55
      Width = 131
      Height = 13
      Caption = #49440#53469' '#51089#50629#51012' '#51201#50857#51473#51077#45768#45796'.'
    end
    object pnlWaitT: TPanel
      Left = 1
      Top = 1
      Width = 262
      Height = 22
      Alignment = taLeftJustify
      BevelOuter = bvNone
      Caption = ' Wait...'
      Color = 16750131
      Font.Charset = HANGEUL_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = #45208#45588#44256#46357
      Font.Style = [fsBold]
      ParentBackground = False
      ParentFont = False
      TabOrder = 0
      object lblDownloadCnt: TLabel
        Left = 205
        Top = 4
        Width = 27
        Height = 14
        Alignment = taRightJustify
        Caption = '(0/0)'
        Font.Charset = HANGEUL_CHARSET
        Font.Color = clWhite
        Font.Height = -12
        Font.Name = #45208#45588#44256#46357
        Font.Style = []
        ParentFont = False
        Visible = False
      end
    end
  end
  object pnlMain: TPanel
    Left = 2
    Top = 32
    Width = 1200
    Height = 700
    BevelOuter = bvNone
    Color = clWhite
    ParentBackground = False
    TabOrder = 2
    object ScrollBox1: TScrollBox
      Left = 0
      Top = 0
      Width = 1200
      Height = 700
      HorzScrollBar.Visible = False
      Align = alClient
      BevelInner = bvNone
      BevelOuter = bvNone
      BorderStyle = bsNone
      Color = clWhite
      ParentColor = False
      TabOrder = 0
    end
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 10
    OnTimer = Timer1Timer
    Left = 40
    Top = 80
  end
end
