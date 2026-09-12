object frmReleaseList: TfrmReleaseList
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsNone
  Caption = #44277#51648#49324#54637
  ClientHeight = 800
  ClientWidth = 907
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #45208#45588#44256#46357
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  Scaled = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 14
  object shpBG: TShape
    Left = 0
    Top = 0
    Width = 907
    Height = 800
    Align = alClient
    Brush.Style = bsClear
    Pen.Color = 16750131
    ExplicitTop = -71
    ExplicitWidth = 747
    ExplicitHeight = 413
  end
  object panWindowsMove: TPanel
    Left = 1
    Top = 0
    Width = 907
    Height = 32
    BevelOuter = bvNone
    Color = 16750131
    ParentBackground = False
    TabOrder = 0
    OnMouseDown = panWindowsMoveMouseDown
    object btnCloseTypeB: TImage
      Left = 882
      Top = 5
      Width = 22
      Height = 22
      Cursor = crHandPoint
      OnClick = btnCloseTypeBClick
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
        6469643A43343636424143443035444131314541393742464146433939464343
        333939362220786D704D4D3A496E7374616E636549443D22786D702E6969643A
        4334363642414343303544413131454139374246414643393946434333393936
        2220786D703A43726561746F72546F6F6C3D2241646F62652050686F746F7368
        6F7020435336202857696E646F777329223E203C786D704D4D3A446572697665
        6446726F6D2073745265663A696E7374616E636549443D22786D702E6969643A
        3135323745374430443830354541313142464242393842374343463441334137
        222073745265663A646F63756D656E7449443D22786D702E6469643A32333446
        35433134444439384536313141314141433543353430324536303132222F3E20
        3C2F7264663A4465736372697074696F6E3E203C2F7264663A5244463E203C2F
        783A786D706D6574613E203C3F787061636B657420656E643D2272223F3E4A72
        F00D0000007B4944415478DA63BC74F70303254057891F4C33E230E82110CBE3
        D08B22876ED01120B686CA3102F17F241A1960933B0234CC166610B2061620BE
        07C4AA40FC13CD20AC72408318B119540DC41381381F885BD10CC22A87CB2072
        027C8818C448A4FEFF840C1AF51A1DBD469141C8999654701468900D23B5CA23
        00F6B952DFB86DC5070000000049454E44AE426082}
      OnClick = btnCloseTypeBClick
    end
    object lblFormTitle: TLabel
      Left = 30
      Top = 9
      Width = 355
      Height = 14
      Caption = #54532#47196#44536#47016' '#50629#45936#51060#53944' '#47785#47197' (['#52280#44256']'#47484' '#53364#47533#54616#47732' '#50672#44288' '#47928#49436#47484' '#48380' '#49688' '#51080#49845#45768#45796'.)'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = #45208#45588#44256#46357
      Font.Style = [fsBold]
      ParentFont = False
      OnMouseDown = panWindowsMoveMouseDown
    end
    object lblShow: TLabel
      Left = 662
      Top = 11
      Width = 220
      Height = 14
      AutoSize = False
      Caption = #45796#49884' '#54364#49884#54616#51648' '#50506#51020'. ('#52404#53356' '#49884' '#54868#47732' '#51333#47308')'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = #45208#45588#44256#46357
      Font.Style = []
      ParentFont = False
      OnClick = chkShowClick
      OnMouseDown = panWindowsMoveMouseDown
    end
    object chkShow: TCheckBox
      Left = 642
      Top = 9
      Width = 20
      Height = 17
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = #45208#45588#44256#46357
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = chkShowClick
    end
  end
  object panCenter: TPanel
    Left = 1
    Top = 32
    Width = 905
    Height = 767
    BevelEdges = [beLeft, beRight, beBottom]
    BevelOuter = bvNone
    Color = clWhite
    ParentBackground = False
    TabOrder = 1
    object lvResult: TListView
      Tag = 1
      AlignWithMargins = True
      Left = 4
      Top = 4
      Width = 897
      Height = 118
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Align = alTop
      BevelInner = bvNone
      BevelOuter = bvNone
      Color = clWhite
      Columns = <
        item
          Caption = 'INDEX'
          Width = 0
        end
        item
          Alignment = taCenter
          Caption = 'Date'
          Width = 100
        end
        item
          Alignment = taCenter
          Caption = #48260#51204
          Width = 80
        end
        item
          Alignment = taCenter
          Caption = #48516#47448
          Width = 160
        end
        item
          Alignment = taCenter
          Caption = #45236#50857
          Width = 480
        end
        item
          Alignment = taCenter
          Caption = #52280#44256
        end
        item
          Caption = 'PATH_INDEX'
          Width = 0
        end>
      ColumnClick = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #45208#45588#44256#46357
      Font.Style = []
      GridLines = True
      ReadOnly = True
      RowSelect = True
      ParentFont = False
      TabOrder = 0
      ViewStyle = vsReport
      OnClick = lvResultClick
    end
    object Panel1: TPanel
      Left = 0
      Top = 126
      Width = 905
      Height = 641
      Margins.Left = 10
      Margins.Top = 0
      Margins.Right = 10
      Margins.Bottom = 10
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 1
      object IMGVIEW: TImage
        Left = 29
        Top = 0
        Width = 847
        Height = 641
        Margins.Left = 0
        Margins.Top = 0
        Margins.Right = 0
        Margins.Bottom = 0
        Align = alClient
        Stretch = True
        ExplicitLeft = 26
        ExplicitWidth = 819
        ExplicitHeight = 635
      end
      object IMGNOIMAGE: TImage
        Left = 295
        Top = 160
        Width = 270
        Height = 258
        Visible = False
      end
      object lblCount: TLabel
        Left = 402
        Top = 10
        Width = 100
        Height = 14
        Alignment = taCenter
        AutoSize = False
        Caption = '/'
        Font.Charset = ANSI_CHARSET
        Font.Color = clNavy
        Font.Height = -12
        Font.Name = #45208#45588#44256#46357
        Font.Style = [fsBold]
        ParentFont = False
        OnClick = chkShowClick
        OnMouseDown = panWindowsMoveMouseDown
      end
      object Panel3: TPanel
        Left = 0
        Top = 0
        Width = 29
        Height = 641
        Align = alLeft
        BevelOuter = bvNone
        TabOrder = 0
        object IMGPREV: TImage
          Left = -1
          Top = 282
          Width = 29
          Height = 76
          Margins.Left = 10
          Margins.Top = 10
          Margins.Right = 10
          Margins.Bottom = 10
          OnClick = IMGPREVClick
          OnMouseEnter = IMGPREVMouseEnter
          OnMouseLeave = IMGPREVMouseLeave
        end
      end
      object Panel4: TPanel
        Left = 876
        Top = 0
        Width = 29
        Height = 641
        Align = alRight
        BevelOuter = bvNone
        TabOrder = 1
        object IMGNEXT: TImage
          Left = 0
          Top = 282
          Width = 29
          Height = 76
          Margins.Left = 10
          Margins.Top = 10
          Margins.Right = 10
          Margins.Bottom = 10
          OnClick = IMGNEXTClick
          OnMouseEnter = IMGNEXTMouseEnter
          OnMouseLeave = IMGNEXTMouseLeave
        end
      end
    end
  end
end
