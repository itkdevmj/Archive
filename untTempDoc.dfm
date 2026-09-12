object frmTempDoc: TfrmTempDoc
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = 'frmTempDoc'
  ClientHeight = 896
  ClientWidth = 1084
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
  object Shape2: TShape
    Left = 0
    Top = 32
    Width = 1084
    Height = 864
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
    Width = 1084
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
      Width = 72
      Height = 14
      Caption = ' '#51076#49884#54028#51068#48372#44592' '
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
      Left = 100
      Top = 8
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
      Left = 633
      Top = 9
      Width = 420
      Height = 14
      Alignment = taRightJustify
      AutoSize = False
      Caption = #50676#46988#54616#44256#51088' '#54616#45716'  '#47928#49436#47484' '#53364#47533#54616#49464#50836'.'
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
      Left = 1052
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
  object pnlTempDoc: TPanel
    Left = 1
    Top = 32
    Width = 1082
    Height = 860
    BevelOuter = bvNone
    Caption = 'pnlTempDoc'
    TabOrder = 2
    object Shape1: TShape
      Left = 0
      Top = 140
      Width = 1082
      Height = 1
      Align = alTop
      Brush.Style = bsClear
      Pen.Color = 16750131
      Pen.Width = 2
      ExplicitTop = 141
    end
    object pnlMain: TPanel
      Left = 29
      Top = 141
      Width = 1024
      Height = 719
      Align = alClient
      BevelOuter = bvNone
      Color = clWhite
      ParentBackground = False
      TabOrder = 0
      object IMGSCREEN1: TImage
        Left = 0
        Top = 0
        Width = 1024
        Height = 720
        Stretch = True
      end
      object IMGNOIMAGE: TImage
        Left = 377
        Top = 231
        Width = 270
        Height = 258
        Visible = False
      end
    end
    object pnlPreview: TPanel
      Left = 0
      Top = 0
      Width = 1082
      Height = 140
      Align = alTop
      BevelOuter = bvNone
      Color = clWhite
      ParentBackground = False
      TabOrder = 1
      object ScrollBox1: TScrollBox
        Left = 0
        Top = 0
        Width = 1082
        Height = 140
        VertScrollBar.Visible = False
        Align = alClient
        BevelInner = bvNone
        BevelOuter = bvNone
        BorderStyle = bsNone
        TabOrder = 0
      end
    end
    object pnlPrev: TPanel
      Left = 0
      Top = 141
      Width = 29
      Height = 719
      Align = alLeft
      BevelOuter = bvNone
      Color = clWhite
      ParentBackground = False
      TabOrder = 2
      object IMGPREV: TImage
        Left = 0
        Top = 252
        Width = 29
        Height = 76
        OnClick = IMGPREVClick
        OnMouseEnter = IMGPREVMouseEnter
        OnMouseLeave = IMGPREVMouseLeave
      end
    end
    object pnlNext: TPanel
      Left = 1053
      Top = 141
      Width = 29
      Height = 719
      Align = alRight
      BevelOuter = bvNone
      Color = clWhite
      ParentBackground = False
      TabOrder = 3
      object IMGNEXT: TImage
        Left = 0
        Top = 252
        Width = 29
        Height = 76
        OnClick = IMGNEXTClick
        OnMouseEnter = IMGNEXTMouseEnter
        OnMouseLeave = IMGNEXTMouseLeave
      end
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
