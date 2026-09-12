object frmUserAdd: TfrmUserAdd
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsNone
  Caption = #49324#50857#51088' '#44288#47532
  ClientHeight = 195
  ClientWidth = 742
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #45208#45588#44256#46357
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  Scaled = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 14
  object shpBG: TShape
    Left = 0
    Top = 0
    Width = 742
    Height = 195
    Align = alClient
    Brush.Style = bsClear
    Pen.Color = 16750131
    ExplicitLeft = -5
    ExplicitTop = -218
    ExplicitWidth = 747
    ExplicitHeight = 413
  end
  object panCenter: TPanel
    Left = 1
    Top = 32
    Width = 740
    Height = 162
    BevelOuter = bvNone
    Color = clWhite
    ParentBackground = False
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 9
      Top = 3
      Width = 720
      Height = 150
      Caption = ' '#49324#50857#51088' '#46321#47197' / '#48320#44221' '
      TabOrder = 0
      object IMGREGIST: TImage
        Left = 388
        Top = 110
        Width = 100
        Height = 28
        OnClick = IMGREGISTClick
        OnMouseEnter = IMGREGISTMouseEnter
        OnMouseLeave = IMGREGISTMouseLeave
      end
      object IMGMODIFY: TImage
        Left = 498
        Top = 110
        Width = 100
        Height = 28
        OnClick = IMGMODIFYClick
        OnMouseEnter = IMGMODIFYMouseEnter
        OnMouseLeave = IMGMODIFYMouseLeave
      end
      object IMGEXIT: TImage
        Left = 608
        Top = 110
        Width = 100
        Height = 28
        OnClick = IMGEXITClick
        OnMouseEnter = IMGEXITMouseEnter
        OnMouseLeave = IMGEXITMouseLeave
      end
      object pnlTitle1: TPanel
        Left = 11
        Top = 27
        Width = 89
        Height = 22
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #49324#50857#51088#47749
        ParentBackground = False
        TabOrder = 9
      end
      object edtUserInfo1: TEdit
        Left = 100
        Top = 27
        Width = 130
        Height = 20
        Alignment = taCenter
        Ctl3D = False
        ImeName = 'Microsoft Office IME 2007'
        MaxLength = 20
        ParentCtl3D = False
        TabOrder = 0
        Text = #54861#44600#46041
        OnEnter = edtHangul_OnEnter
        OnKeyPress = edtUserInfoKeyPress
      end
      object pnlTitle2: TPanel
        Left = 238
        Top = 27
        Width = 110
        Height = 22
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #49324#50857#51088' IP'
        ParentBackground = False
        TabOrder = 10
      end
      object edtUserInfo2: TEdit
        Left = 348
        Top = 27
        Width = 120
        Height = 20
        Alignment = taCenter
        Ctl3D = False
        ImeName = 'Microsoft Office IME 2007'
        MaxLength = 15
        ParentCtl3D = False
        TabOrder = 1
        Text = '0.0.0.0'
        OnKeyPress = edtUserInfoKeyPress
      end
      object pnlGrade: TPanel
        Left = 476
        Top = 27
        Width = 110
        Height = 22
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #49324#50857#44428#54620
        ParentBackground = False
        TabOrder = 11
      end
      object cboGrade: TComboBox
        Left = 586
        Top = 27
        Width = 120
        Height = 22
        Style = csDropDownList
        ImeName = 'Microsoft IME 2010'
        TabOrder = 2
        OnClick = cboGradeClick
        OnKeyPress = edtUserInfoKeyPress
        Items.Strings = (
          #49849#51064#45824#44592
          #51068#48152#49324#50857#51088
          #44288#47532#51088
          #52572#49548#49324#50857#51088
          #55092#47732#49324#50857#51088
          #49325#51228#49324#50857#51088)
      end
      object pnlTitle3: TPanel
        Left = 11
        Top = 50
        Width = 89
        Height = 22
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #49324#50857#51088' ID'
        ParentBackground = False
        TabOrder = 12
      end
      object edtUserInfo3: TEdit
        Left = 100
        Top = 50
        Width = 130
        Height = 21
        Alignment = taCenter
        AutoSize = False
        Ctl3D = False
        ImeMode = imDisable
        ImeName = 'Microsoft Office IME 2007'
        MaxLength = 20
        ParentCtl3D = False
        TabOrder = 3
        Text = 'abcd'
        OnEnter = edtAlphaNumeric_OnEnter
        OnKeyPress = edtUserInfoKeyPress
      end
      object pnlTitle4: TPanel
        Left = 238
        Top = 50
        Width = 110
        Height = 22
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #49324#50857#51088' '#48708#48128#48264#54840
        ParentBackground = False
        TabOrder = 13
      end
      object edtUserInfo4: TEdit
        Left = 348
        Top = 50
        Width = 120
        Height = 20
        Alignment = taCenter
        Ctl3D = False
        ImeName = 'Microsoft Office IME 2007'
        MaxLength = 20
        ParentCtl3D = False
        PasswordChar = '*'
        TabOrder = 4
        Text = '1234'
        OnEnter = edtAlphaNumeric_OnEnter
        OnKeyPress = edtUserInfoKeyPress
      end
      object pnlTitle5: TPanel
        Left = 476
        Top = 50
        Width = 110
        Height = 22
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #50672#46973#52376
        ParentBackground = False
        TabOrder = 14
      end
      object edtUserInfo5: TEdit
        Left = 586
        Top = 50
        Width = 120
        Height = 20
        Alignment = taCenter
        Ctl3D = False
        ImeName = 'Microsoft Office IME 2007'
        MaxLength = 13
        ParentCtl3D = False
        TabOrder = 5
        Text = '010-1234-5678'
        OnKeyPress = edtUserInfoKeyPress
      end
      object pnlTitle7: TPanel
        Left = 238
        Top = 73
        Width = 110
        Height = 22
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #48708#48128#48264#54840' '#54869#51064
        ParentBackground = False
        TabOrder = 15
      end
      object edtUserInfo7: TEdit
        Left = 348
        Top = 73
        Width = 120
        Height = 20
        Alignment = taCenter
        Ctl3D = False
        ImeName = 'Microsoft Office IME 2007'
        MaxLength = 20
        ParentCtl3D = False
        PasswordChar = '*'
        TabOrder = 7
        Text = '1234'
        OnEnter = edtAlphaNumeric_OnEnter
        OnKeyPress = edtUserInfoKeyPress
      end
      object pnlTitle6: TPanel
        Left = 11
        Top = 73
        Width = 89
        Height = 22
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #48512#49436#47749
        ParentBackground = False
        TabOrder = 16
      end
      object edtUserInfo6: TEdit
        Left = 100
        Top = 73
        Width = 130
        Height = 21
        Alignment = taCenter
        AutoSize = False
        Ctl3D = False
        ImeName = 'Microsoft Office IME 2007'
        MaxLength = 20
        ParentCtl3D = False
        TabOrder = 6
        OnEnter = edtHangul_OnEnter
        OnKeyPress = edtUserInfoKeyPress
      end
      object pnlTitle8: TPanel
        Left = 476
        Top = 73
        Width = 110
        Height = 22
        BevelInner = bvRaised
        BevelOuter = bvLowered
        Caption = #48708#48128#48264#54840#50724#47448#54943#49688
        ParentBackground = False
        TabOrder = 17
      end
      object edtUserInfo8: TEdit
        Left = 586
        Top = 73
        Width = 23
        Height = 20
        Alignment = taCenter
        Ctl3D = False
        Enabled = False
        ImeName = 'Microsoft Office IME 2007'
        MaxLength = 1
        NumbersOnly = True
        ParentCtl3D = False
        TabOrder = 8
        Text = '0'
        OnKeyPress = edtUserInfoKeyPress
      end
      object btnInitFailCut: TButton
        Left = 610
        Top = 73
        Width = 96
        Height = 22
        Caption = #48708#48128#48264#54840' '#52488#44592#54868
        TabOrder = 18
        OnClick = btnInitFailCutClick
      end
    end
  end
  object panWindowsMove: TPanel
    Left = 1
    Top = 0
    Width = 742
    Height = 32
    BevelEdges = [beLeft, beTop, beRight]
    BevelOuter = bvNone
    Color = 16750131
    ParentBackground = False
    TabOrder = 1
    OnMouseDown = panWindowsMoveMouseDown
    object btnCloseTypeB: TImage
      Left = 716
      Top = 5
      Width = 22
      Height = 22
      Cursor = crHandPoint
      OnClick = btnCloseTypeBClick
    end
    object lblFormTitle: TLabel
      Left = 14
      Top = 9
      Width = 58
      Height = 14
      Caption = #49324#50857#51088' '#44288#47532
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
  object pnlGradeReason: TPanel
    Left = 21
    Top = 132
    Width = 185
    Height = 48
    BevelOuter = bvNone
    Color = clSilver
    ParentBackground = False
    TabOrder = 2
    Visible = False
    object lblName: TLabel
      Left = 19
      Top = 6
      Width = 69
      Height = 14
      Caption = #44428#54620#48320#44221' '#49324#50976
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -12
      Font.Name = #45208#45588#44256#46357
      Font.Style = [fsBold]
      ParentFont = False
    end
    object edtReason: TEdit
      Left = 19
      Top = 23
      Width = 140
      Height = 20
      Alignment = taCenter
      Ctl3D = False
      ImeName = 'Microsoft Office IME 2007'
      ParentCtl3D = False
      TabOrder = 0
      OnEnter = edtHangul_OnEnter
      OnKeyPress = edtReasonKeyPress
    end
  end
end
