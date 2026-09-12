object frmMemoViewer: TfrmMemoViewer
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = 'frmMemoViewer'
  ClientHeight = 676
  ClientWidth = 702
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #45208#45588#44256#46357
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  Scaled = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnMouseWheel = FormMouseWheel
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 14
  object shpBG: TShape
    Left = 0
    Top = 0
    Width = 702
    Height = 676
    Align = alClient
    Brush.Style = bsClear
    Pen.Color = 16750131
    ExplicitLeft = -45
    ExplicitTop = 32
    ExplicitWidth = 747
    ExplicitHeight = 413
  end
  object panMain: TPanel
    Left = 1
    Top = 1
    Width = 700
    Height = 674
    BevelOuter = bvNone
    Color = clWhite
    ParentBackground = False
    TabOrder = 0
    object panCenter: TPanel
      Left = 0
      Top = 32
      Width = 700
      Height = 642
      Align = alClient
      BevelOuter = bvNone
      Color = clWhite
      ParentBackground = False
      TabOrder = 0
      object IMGNOIMAGE: TImage
        Left = 220
        Top = 160
        Width = 270
        Height = 258
        Visible = False
      end
      object IMGPREV: TImage
        Left = 0
        Top = 250
        Width = 29
        Height = 76
        OnClick = IMGPREVClick
        OnMouseEnter = IMGPREVMouseEnter
        OnMouseLeave = IMGPREVMouseLeave
      end
      object IMGNEXT: TImage
        Left = 669
        Top = 250
        Width = 29
        Height = 76
        OnClick = IMGNEXTClick
        OnMouseEnter = IMGNEXTMouseEnter
        OnMouseLeave = IMGNEXTMouseLeave
      end
      object palMainView: TPanel
        Left = 29
        Top = 0
        Width = 640
        Height = 640
        BevelOuter = bvNone
        Color = clWhite
        ParentBackground = False
        TabOrder = 0
        object pnlIMGVIEW: TPanel
          Left = 0
          Top = 0
          Width = 640
          Height = 640
          BevelOuter = bvNone
          TabOrder = 0
          object IMGVIEW: TImage
            Left = 0
            Top = 0
            Width = 640
            Height = 640
            Align = alClient
            OnMouseDown = IMGVIEWMouseDown
            OnMouseMove = IMGVIEWMouseMove
            OnMouseUp = IMGVIEWMouseUp
            ExplicitLeft = -5
            ExplicitTop = 1
          end
        end
      end
    end
    object panWindowsMove: TPanel
      Left = 0
      Top = 0
      Width = 700
      Height = 32
      Align = alTop
      BevelOuter = bvNone
      Color = 16750131
      ParentBackground = False
      TabOrder = 1
      OnMouseDown = panWindowsMoveMouseDown
      object imgIconTitle: TImage
        Left = 8
        Top = 8
        Width = 18
        Height = 17
        Cursor = crHandPoint
        Picture.Data = {
          0954506E67496D61676589504E470D0A1A0A0000000D49484452000000120000
          00110806000000D05AFCF90000001974455874536F6674776172650041646F62
          6520496D616765526561647971C9653C0000036669545874584D4C3A636F6D2E
          61646F62652E786D7000000000003C3F787061636B657420626567696E3D22EF
          BBBF222069643D2257354D304D7043656869487A7265537A4E54637A6B633964
          223F3E203C783A786D706D65746120786D6C6E733A783D2261646F62653A6E73
          3A6D6574612F2220783A786D70746B3D2241646F626520584D5020436F726520
          352E332D633031312036362E3134353636312C20323031322F30322F30362D31
          343A35363A32372020202020202020223E203C7264663A52444620786D6C6E73
          3A7264663D22687474703A2F2F7777772E77332E6F72672F313939392F30322F
          32322D7264662D73796E7461782D6E7323223E203C7264663A44657363726970
          74696F6E207264663A61626F75743D222220786D6C6E733A786D704D4D3D2268
          7474703A2F2F6E732E61646F62652E636F6D2F7861702F312E302F6D6D2F2220
          786D6C6E733A73745265663D22687474703A2F2F6E732E61646F62652E636F6D
          2F7861702F312E302F73547970652F5265736F75726365526566232220786D6C
          6E733A786D703D22687474703A2F2F6E732E61646F62652E636F6D2F7861702F
          312E302F2220786D704D4D3A4F726967696E616C446F63756D656E7449443D22
          786D702E6469643A323334463543313444443938453631314131414143354335
          34303245363031322220786D704D4D3A446F63756D656E7449443D22786D702E
          6469643A37394430344537433034353831314541393035374635313037313543
          413831352220786D704D4D3A496E7374616E636549443D22786D702E6969643A
          3739443034453742303435383131454139303537463531303731354341383135
          2220786D703A43726561746F72546F6F6C3D2241646F62652050686F746F7368
          6F7020435336202857696E646F777329223E203C786D704D4D3A446572697665
          6446726F6D2073745265663A696E7374616E636549443D22786D702E6969643A
          3944313035464641443435424537313141414441464532303033443135373636
          222073745265663A646F63756D656E7449443D22786D702E6469643A32333446
          35433134444439384536313141314141433543353430324536303132222F3E20
          3C2F7264663A4465736372697074696F6E3E203C2F7264663A5244463E203C2F
          783A786D706D6574613E203C3F787061636B657420656E643D2272223F3EA28C
          E3E4000000724944415478DA63EC5A7690811A801187410F81581E871EAC7230
          838E00B1354C0C88FF23D128EAB1C881F4DAC20C42D6C002C4F7805815887FA2
          19844B8E119B41D5403C1188F381B815CD205C72580D222BAC8786418C446AFE
          4FC8A051AFD1D16B1419849C6949054781D886915AE511000BA94113F2B6FADD
          0000000049454E44AE426082}
        Visible = False
      end
      object lblFormTitle: TLabel
        Left = 14
        Top = 9
        Width = 97
        Height = 14
        Caption = #47700#47784' '#52392#48512' '#54028#51068' '#48372#44592
        Font.Charset = ANSI_CHARSET
        Font.Color = clWhite
        Font.Height = -12
        Font.Name = #45208#45588#44256#46357
        Font.Style = [fsBold]
        ParentFont = False
        OnMouseDown = panWindowsMoveMouseDown
      end
      object btnCloseTypeB: TImage
        Left = 670
        Top = 5
        Width = 22
        Height = 22
        Cursor = crHandPoint
        OnClick = btnCloseTypeBClick
      end
      object lblCount: TLabel
        Left = 620
        Top = 9
        Width = 4
        Height = 15
        Alignment = taCenter
        Font.Charset = ANSI_CHARSET
        Font.Color = clWhite
        Font.Height = -13
        Font.Name = #45208#45588#44256#46357' ExtraBold'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object lblMemoTitle: TLabel
        Left = 140
        Top = 9
        Width = 4
        Height = 15
        Font.Charset = ANSI_CHARSET
        Font.Color = clWhite
        Font.Height = -13
        Font.Name = #45208#45588#44256#46357' ExtraBold'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
  end
end
