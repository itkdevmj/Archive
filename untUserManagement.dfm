object frmUserManagement: TfrmUserManagement
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsNone
  Caption = #44228#51221#44288#47532
  ClientHeight = 445
  ClientWidth = 747
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #45208#45588#44256#46357
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  Scaled = False
  OnClose = FormClose
  OnCreate = frmUserManagement_OnCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 14
  object shpBG: TShape
    Left = 0
    Top = 32
    Width = 747
    Height = 413
    Align = alClient
    Brush.Style = bsClear
    Pen.Color = 16750131
    ExplicitLeft = -65
    ExplicitTop = 0
    ExplicitWidth = 812
    ExplicitHeight = 410
  end
  object PageControl1: TPageControl
    Left = 1
    Top = 33
    Width = 745
    Height = 394
    ActivePage = TabSheet1
    TabOrder = 0
    OnChange = PageControl1Change
    OnChanging = PageControl1Changing
    object TabSheet1: TTabSheet
      Caption = #44228#51221#44288#47532
      OnShow = TabSheet1_OnShow
      object GroupBox1: TGroupBox
        Left = 6
        Top = 2
        Width = 717
        Height = 250
        Caption = ' '#44228#51221' '#51221#48372' '#51312#54924' '
        TabOrder = 0
        object lblName: TLabel
          Left = 78
          Top = 21
          Width = 72
          Height = 14
          Caption = #49324#50857#51088#47749'  '#52286#44592
        end
        object lblTotalGrade: TLabel
          Left = 400
          Top = 21
          Width = 3
          Height = 14
        end
        object lstvUserListInfo: TListView
          Left = 10
          Top = 45
          Width = 697
          Height = 193
          Columns = <
            item
              Caption = 'NO'
              Width = 30
            end
            item
              Alignment = taCenter
              Caption = #49324#50857#51088#47749
              Width = 120
            end
            item
              Alignment = taCenter
              Caption = #49324#50857#51088' IP'
              Width = 140
            end
            item
              Alignment = taCenter
              Caption = #49324#50857#51088' ID'
              Width = 120
            end
            item
              Alignment = taCenter
              Caption = #49324#50857#44428#54620
              Width = 100
            end
            item
              Alignment = taCenter
              AutoSize = True
              Caption = #50672#46973#52376
            end
            item
              Caption = 'INDEX'
              Width = 0
            end>
          GridLines = True
          ReadOnly = True
          RowSelect = True
          TabOrder = 0
          ViewStyle = vsReport
          OnClick = lstvUserListInfoClick
        end
        object edtName: TEdit
          Left = 159
          Top = 17
          Width = 140
          Height = 20
          Alignment = taCenter
          Ctl3D = False
          ImeName = 'Microsoft Office IME 2007'
          ParentCtl3D = False
          TabOrder = 1
          OnEnter = edtHangul_OnEnter
          OnKeyPress = edtFindKeyPress
        end
        object btnFind: TButton
          Left = 302
          Top = 17
          Width = 92
          Height = 22
          Caption = #44160#49353
          TabOrder = 2
          OnClick = btnFindClick
        end
      end
      object GroupBox2: TGroupBox
        Left = 6
        Top = 256
        Width = 717
        Height = 104
        Caption = ' '#49440#53469' '#44228#51221' '#51221#48372'  '
        TabOrder = 1
        object IMGLOG: TImage
          Left = 11
          Top = 68
          Width = 100
          Height = 28
          OnClick = IMGLOGClick
          OnMouseEnter = IMGLOGMouseEnter
          OnMouseLeave = IMGLOGMouseLeave
        end
        object IMGREGIST: TImage
          Left = 277
          Top = 68
          Width = 100
          Height = 28
          OnClick = IMGREGISTClick
          OnMouseEnter = IMGREGISTMouseEnter
          OnMouseLeave = IMGREGISTMouseLeave
        end
        object IMGMODIFY: TImage
          Left = 387
          Top = 68
          Width = 100
          Height = 28
          OnClick = IMGMODIFYClick
          OnMouseEnter = IMGMODIFYMouseEnter
          OnMouseLeave = IMGMODIFYMouseLeave
        end
        object IMGDELETE: TImage
          Left = 497
          Top = 68
          Width = 100
          Height = 28
          OnClick = IMGDELETEClick
          OnMouseEnter = IMGDELETEMouseEnter
          OnMouseLeave = IMGDELETEMouseLeave
        end
        object IMGEXIT: TImage
          Left = 607
          Top = 68
          Width = 100
          Height = 28
          OnClick = IMGEXITClick
          OnMouseEnter = IMGEXITMouseEnter
          OnMouseLeave = IMGEXITMouseLeave
        end
        object lblUserInfo8: TLabel
          Left = 280
          Top = 44
          Width = 66
          Height = 14
          Caption = 'lblUserInfo8'
          Visible = False
        end
        object Panel5: TPanel
          Left = 496
          Top = 43
          Width = 89
          Height = 20
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Caption = #50672#46973#52376
          ParentBackground = False
          TabOrder = 0
        end
        object edtUserInfo5: TEdit
          Left = 587
          Top = 42
          Width = 121
          Height = 20
          Alignment = taCenter
          Ctl3D = False
          Enabled = False
          ImeName = 'Microsoft Office IME 2007'
          ParentCtl3D = False
          TabOrder = 1
        end
        object Panel6: TPanel
          Left = 11
          Top = 42
          Width = 89
          Height = 20
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Caption = #49324#50857#51088' ID'
          ParentBackground = False
          TabOrder = 2
        end
        object edtUserInfo3: TEdit
          Left = 102
          Top = 42
          Width = 130
          Height = 20
          Alignment = taCenter
          Ctl3D = False
          Enabled = False
          ImeName = 'Microsoft Office IME 2007'
          ParentCtl3D = False
          TabOrder = 3
        end
        object Panel7: TPanel
          Left = 238
          Top = 42
          Width = 120
          Height = 20
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Caption = #49324#50857#51088' '#48708#48128#48264#54840
          ParentBackground = False
          TabOrder = 4
        end
        object edtUserInfo4: TEdit
          Left = 360
          Top = 42
          Width = 130
          Height = 20
          Alignment = taCenter
          Ctl3D = False
          Enabled = False
          ImeName = 'Microsoft Office IME 2007'
          ParentCtl3D = False
          PasswordChar = '*'
          TabOrder = 5
        end
        object Panel8: TPanel
          Left = 11
          Top = 20
          Width = 89
          Height = 20
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Caption = #49324#50857#51088#47749
          ParentBackground = False
          TabOrder = 6
        end
        object edtUserInfo1: TEdit
          Left = 102
          Top = 20
          Width = 130
          Height = 20
          Alignment = taCenter
          Ctl3D = False
          Enabled = False
          ImeName = 'Microsoft Office IME 2007'
          ParentCtl3D = False
          TabOrder = 7
        end
        object Panel9: TPanel
          Left = 238
          Top = 20
          Width = 120
          Height = 20
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Caption = #49324#50857#51088' IP'
          ParentBackground = False
          TabOrder = 8
        end
        object Panel10: TPanel
          Left = 496
          Top = 20
          Width = 89
          Height = 20
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Caption = #49324#50857#44428#54620
          ParentBackground = False
          TabOrder = 9
        end
        object edtUserInfo2: TEdit
          Left = 360
          Top = 20
          Width = 130
          Height = 20
          Alignment = taCenter
          Ctl3D = False
          Enabled = False
          ImeName = 'Microsoft Office IME 2007'
          ParentCtl3D = False
          TabOrder = 10
        end
        object edtUserInfo6: TEdit
          Left = 587
          Top = 20
          Width = 121
          Height = 20
          Alignment = taCenter
          Color = clWhite
          Ctl3D = False
          Enabled = False
          ImeName = 'Microsoft Office IME 2007'
          ParentCtl3D = False
          TabOrder = 11
        end
        object edtUserInfo7: TEdit
          Left = 720
          Top = 50
          Width = 121
          Height = 20
          Alignment = taCenter
          Ctl3D = False
          ImeName = 'Microsoft Office IME 2007'
          ParentCtl3D = False
          ReadOnly = True
          TabOrder = 12
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = #47928#49436#44428#54620#49444#51221
      ImageIndex = 1
      OnShow = TabSheet2_OnShow
      object IMGEXIT2: TImage
        Left = 190
        Top = 325
        Width = 100
        Height = 28
        OnClick = IMGEXIT2Click
        OnMouseEnter = IMGEXIT2MouseEnter
        OnMouseLeave = IMGEXIT2MouseLeave
      end
      object IMGSAVESETTING: TImage
        Left = 80
        Top = 325
        Width = 100
        Height = 28
        OnClick = IMGSAVESETTINGClick
        OnMouseEnter = IMGSAVESETTINGMouseEnter
        OnMouseLeave = IMGSAVESETTINGMouseLeave
      end
      object GroupBox3: TGroupBox
        Left = 6
        Top = 3
        Width = 322
        Height = 313
        Caption = #49324#50857#51088#48324' '#49444#51221' '
        TabOrder = 0
        object lvUserBList: TListView
          Left = 24
          Top = 24
          Width = 270
          Height = 260
          Checkboxes = True
          Columns = <
            item
              Caption = #47928#49436#47749
              Width = 250
            end
            item
              Caption = 'INDEX'
              Width = 0
            end>
          GridLines = True
          TabOrder = 0
          ViewStyle = vsReport
        end
      end
      object cbxAll: TCheckBox
        Left = 96
        Top = 290
        Width = 97
        Height = 17
        Caption = #51204#52404#49440#53469'/'#54644#51228
        TabOrder = 1
        OnClick = cbxAll_OnClick
      end
    end
  end
  object stbVectorInfo: TStatusBar
    Left = 1
    Top = 425
    Width = 745
    Height = 19
    Align = alNone
    Panels = <
      item
        Width = 120
      end
      item
        Width = 120
      end
      item
        Width = 120
      end
      item
        Width = 250
      end>
    ParentFont = True
    UseSystemFont = False
  end
  object panWindowsMove: TPanel
    Left = 0
    Top = 0
    Width = 747
    Height = 32
    Align = alTop
    BevelEdges = [beLeft, beTop, beRight]
    BevelOuter = bvNone
    Color = 16750131
    ParentBackground = False
    TabOrder = 2
    OnMouseDown = panWindowsMoveMouseDown
    object btnCloseTypeB: TImage
      Left = 718
      Top = 5
      Width = 22
      Height = 22
      Cursor = crHandPoint
      OnClick = btnCloseTypeBClick
    end
    object lblFormTitle: TLabel
      Left = 14
      Top = 9
      Width = 44
      Height = 14
      Caption = #44228#51221#44288#47532
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = #45208#45588#44256#46357
      Font.Style = [fsBold]
      ParentFont = False
      OnMouseDown = panWindowsMoveMouseDown
    end
    object Image2: TImage
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
  end
end
