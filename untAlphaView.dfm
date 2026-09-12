object frmAlphaView: TfrmAlphaView
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  ClientHeight = 774
  ClientWidth = 1024
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #45208#45588#44256#46357
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 14
  object pnlTool: TPanel
    Left = 0
    Top = 22
    Width = 1024
    Height = 24
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    object pnlAlpha: TPanel
      Left = 0
      Top = 0
      Width = 280
      Height = 24
      Align = alLeft
      BevelEdges = [beTop, beRight, beBottom]
      BevelKind = bkFlat
      BevelOuter = bvNone
      Color = clWhite
      ParentBackground = False
      TabOrder = 0
      object Label1: TLabel
        Left = 8
        Top = 3
        Width = 33
        Height = 14
        Caption = #53804#47749#46020
      end
      object Label2: TLabel
        Left = 88
        Top = 3
        Width = 34
        Height = 14
        Caption = '100%'
      end
      object Label3: TLabel
        Left = 228
        Top = 3
        Width = 20
        Height = 14
        Caption = '0%'
      end
      object lblAlphaV: TLabel
        Left = 44
        Top = 3
        Width = 34
        Height = 13
        Alignment = taCenter
        Caption = '(40%)'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlue
        Font.Height = -11
        Font.Name = #45208#45588#44256#46357' ExtraBold'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object gbAlpha: TGaugeBar
        Left = 124
        Top = 0
        Width = 100
        Height = 20
        Backgnd = bgPattern
        BorderStyle = bsNone
        HighLightColor = clBtnFace
        Max = 10
        ShowHandleGrip = True
        Style = rbsMac
        Position = 10
        OnMouseUp = gbAlphaMouseUp
      end
    end
    object pnlInfo: TPanel
      Left = 560
      Top = 0
      Width = 464
      Height = 24
      Align = alClient
      BevelEdges = [beTop, beBottom]
      BevelKind = bkFlat
      BevelOuter = bvNone
      Color = clWhite
      ParentBackground = False
      TabOrder = 1
      ExplicitLeft = 640
      ExplicitWidth = 384
      object btnZoomIn: TButton
        Left = 68
        Top = -1
        Width = 36
        Height = 22
        Caption = '+'
        TabOrder = 0
        OnClick = btnZoomInClick
      end
      object btnZoomOut: TButton
        Left = 104
        Top = -1
        Width = 36
        Height = 22
        Caption = '-'
        TabOrder = 1
        OnClick = btnZoomOutClick
      end
      object btnOrg: TButton
        Left = 12
        Top = -1
        Width = 56
        Height = 22
        Caption = #50896#48376#53356#44592
        TabOrder = 2
        OnClick = btnOrgClick
      end
      object btnRotateL: TButton
        Left = 212
        Top = -1
        Width = 36
        Height = 22
        Hint = #48120#49464#51312#51221#51004#47196' '#45796#49548' '#49884#44036#51060' '#49548#50836#46112' '#49688' '#51080#49845#45768#45796'.'
        Caption = '-1'#176
        TabOrder = 3
        OnClick = btnRotateClick
      end
      object btnRotateR: TButton
        Left = 248
        Top = -1
        Width = 36
        Height = 22
        Hint = #48120#49464#51312#51221#51004#47196' '#45796#49548' '#49884#44036#51060' '#49548#50836#46112' '#49688' '#51080#49845#45768#45796'.'
        Caption = '+1'#176
        TabOrder = 4
        OnClick = btnRotateClick
      end
      object btnRotate0: TButton
        Left = 156
        Top = -1
        Width = 56
        Height = 22
        Hint = #48120#49464#51312#51221#51004#47196' '#45796#49548' '#49884#44036#51060' '#49548#50836#46112' '#49688' '#51080#49845#45768#45796'.'
        Caption = #50896#48376#44033#46020
        TabOrder = 5
        OnClick = btnRotateClick
      end
      object edtAngle: TEdit
        Left = 286
        Top = 0
        Width = 40
        Height = 22
        Alignment = taCenter
        TabOrder = 6
        OnChange = edtAngleChange
        OnKeyPress = edtAngleKeyPress
      end
      object btnRotateSet: TButton
        Left = 326
        Top = -1
        Width = 56
        Height = 22
        Hint = #54924#51204
        Caption = #54924#51204
        TabOrder = 7
        OnClick = btnRotateSetClick
      end
    end
    object pnlGamma: TPanel
      Left = 280
      Top = 0
      Width = 280
      Height = 24
      Align = alLeft
      BevelEdges = [beTop, beRight, beBottom]
      BevelKind = bkFlat
      BevelOuter = bvNone
      Color = clWhite
      ParentBackground = False
      TabOrder = 2
      ExplicitLeft = 260
      object Label4: TLabel
        Left = 57
        Top = 3
        Width = 48
        Height = 14
        Caption = #51652#54616#44172'(1)'
      end
      object Label5: TLabel
        Left = 211
        Top = 3
        Width = 55
        Height = 14
        Caption = #55120#47532#44172'(10)'
      end
      object Label6: TLabel
        Left = 8
        Top = 3
        Width = 22
        Height = 14
        Caption = #48157#44592
      end
      object lblGammaV: TLabel
        Left = 32
        Top = 3
        Width = 15
        Height = 13
        Alignment = taCenter
        Caption = '(5)'
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlue
        Font.Height = -11
        Font.Name = #45208#45588#44256#46357' ExtraBold'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object gbGamma: TGaugeBar
        Tag = 3
        Left = 108
        Top = 0
        Width = 100
        Height = 20
        Backgnd = bgPattern
        BorderStyle = bsNone
        HighLightColor = clBtnFace
        LargeChange = 2
        Max = 20
        Min = 1
        ShowHandleGrip = True
        Style = rbsMac
        Position = 10
        OnMouseUp = gbGammaMouseUp
      end
    end
  end
  object pnlView: TPanel
    Left = 0
    Top = 46
    Width = 1024
    Height = 728
    Align = alClient
    BevelOuter = bvNone
    BorderStyle = bsSingle
    TabOrder = 1
  end
  object panWindowsMove: TPanel
    Left = 0
    Top = 0
    Width = 1024
    Height = 22
    Align = alTop
    BevelOuter = bvNone
    Color = 9855019
    ParentBackground = False
    TabOrder = 2
    OnMouseDown = panWindowsMoveMouseDown
    object btnCloseTypeB: TImage
      Left = 1002
      Top = 0
      Width = 22
      Height = 22
      Cursor = crHandPoint
      Align = alRight
      Picture.Data = {
        0954506E67496D61676589504E470D0A1A0A0000000D49484452000000160000
        00160806000000C4B46C3B0000001974455874536F6674776172650041646F62
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
        786D702E6469643A373630313139463041424641453931313946354142343438
        41444237343737422220786D704D4D3A446F63756D656E7449443D22786D702E
        6469643A46463544313335304641423431314539414635334133383146384237
        353335302220786D704D4D3A496E7374616E636549443D22786D702E6969643A
        4646354431333446464142343131453941463533413338314638423735333530
        2220786D703A43726561746F72546F6F6C3D2241646F62652050686F746F7368
        6F7020435336202857696E646F777329223E203C786D704D4D3A446572697665
        6446726F6D2073745265663A696E7374616E636549443D22786D702E6969643A
        3737303131394630414246414539313139463541423434384144423734373742
        222073745265663A646F63756D656E7449443D22786D702E6469643A37363031
        31394630414246414539313139463541423434384144423734373742222F3E20
        3C2F7264663A4465736372697074696F6E3E203C2F7264663A5244463E203C2F
        783A786D706D6574613E203C3F787061636B657420656E643D2272223F3E81B1
        A417000000FF4944415478DA63FCFFFF3F032D00E3A8C1780DEE5E76D00C48CD
        06E298D228FBCBD83402D5E802A925409C0A54738AA0C1400D4E406A0310F302
        F10720F6046A3C81A6C61C48ED00620120FE0CC4014035FB08197C1048D92109
        7D07627FA0C6DD50795720B511883991D41C02CADB1332980B48AD07623724E1
        DF401C05652F03625624B95D401C0834F81B3161CC060DBF5024E17F509A0949
        6C35341E7E11157950C39981D47450E4306007A0C8CD041AFA179B24DEE40634
        1CE43A50C499A2499D06620BA0A1FF70E9A5AF8B6912C6D054014AC7AE48C294
        A70A5AA663F49CE701D474124D0D28E76D0762410662731E5423F5CB0A6A8151
        83696F3000F157B3D5ED3DB96D0000000049454E44AE426082}
      OnClick = btnCloseTypeBClick
      ExplicitLeft = 558
      ExplicitTop = 2
    end
    object lblAlphaT: TLabel
      Left = 330
      Top = 3
      Width = 262
      Height = 15
      Alignment = taCenter
      Caption = #51648#51201#47928#49436#53685#54633#44288#47532#49884#49828#53596'('#46020#47732' '#44217#52432#48372#44592' '#54868#47732' 1) '
      Color = clHotLight
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -13
      Font.Name = #45208#45588#44256#46357
      Font.Style = []
      ParentColor = False
      ParentFont = False
      OnMouseDown = panWindowsMoveMouseDown
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 24
    Top = 72
  end
end
