object frmMemoBatch: TfrmMemoBatch
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsNone
  Caption = #44277#51648#49324#54637
  ClientHeight = 554
  ClientWidth = 800
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
    Width = 800
    Height = 554
    Align = alClient
    Brush.Style = bsClear
    Pen.Color = 16750131
    ExplicitLeft = 8
    ExplicitTop = 40
    ExplicitWidth = 747
    ExplicitHeight = 413
  end
  object panWindowsMove: TPanel
    Left = 0
    Top = 0
    Width = 800
    Height = 32
    BevelEdges = [beLeft, beTop, beRight]
    BevelOuter = bvNone
    Color = 16750131
    ParentBackground = False
    TabOrder = 0
    OnMouseDown = panWindowsMoveMouseDown
    object btnCloseTypeB: TImage
      Left = 768
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
      Width = 66
      Height = 14
      Caption = #47700#47784#51068#44292#46321#47197
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = #45208#45588#44256#46357
      Font.Style = [fsBold]
      ParentFont = False
      OnMouseDown = panWindowsMoveMouseDown
    end
  end
  object panCenter: TPanel
    Left = 1
    Top = 32
    Width = 798
    Height = 521
    BevelEdges = [beLeft, beRight, beBottom]
    BevelOuter = bvNone
    TabOrder = 1
    object lblCount: TLabel
      Left = 672
      Top = 64
      Width = 72
      Height = 14
      Caption = #51312#54924#44148#49688' : 0'#44148
      Visible = False
    end
    object Memo1: TMemo
      Left = 712
      Top = 315
      Width = 153
      Height = 73
      ImeName = 'Microsoft Office IME 2007'
      Lines.Strings = (
        'Memo1')
      TabOrder = 0
      Visible = False
    end
    object sgResult: TAdvStringGrid
      Left = 8
      Top = 79
      Width = 780
      Height = 432
      Cursor = crDefault
      ColCount = 4
      Ctl3D = True
      DefaultColWidth = 120
      DrawingStyle = gdsClassic
      RowCount = 3
      Font.Charset = HANGEUL_CHARSET
      Font.Color = clGray
      Font.Height = -12
      Font.Name = #44404#47548#52404
      Font.Style = []
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
      ParentCtl3D = False
      ParentFont = False
      ScrollBars = ssBoth
      TabOrder = 1
      GridFixedLineColor = clSilver
      HoverRowCells = [hcNormal, hcSelected]
      OnGetAlignment = sgResultGetAlignment
      OnClickCell = sgResultClickCell
      ActiveCellFont.Charset = HANGEUL_CHARSET
      ActiveCellFont.Color = clWindowText
      ActiveCellFont.Height = -12
      ActiveCellFont.Name = #44404#47548#52404
      ActiveCellFont.Style = []
      ActiveCellColor = clCream
      AutoHideSelection = True
      BackGround.Color = clSilver
      BackGround.ColorTo = clSilver
      ControlLook.FixedGradientHoverFrom = 16710648
      ControlLook.FixedGradientHoverTo = 16446189
      ControlLook.FixedGradientHoverMirrorFrom = 16049367
      ControlLook.FixedGradientHoverMirrorTo = 15258305
      ControlLook.FixedGradientDownFrom = 15853789
      ControlLook.FixedGradientDownTo = 15852760
      ControlLook.FixedGradientDownMirrorFrom = 15522767
      ControlLook.FixedGradientDownMirrorTo = 15588559
      ControlLook.FixedGradientDownBorder = 14007466
      ControlLook.DropDownHeader.Font.Charset = DEFAULT_CHARSET
      ControlLook.DropDownHeader.Font.Color = clWindowText
      ControlLook.DropDownHeader.Font.Height = -11
      ControlLook.DropDownHeader.Font.Name = 'Tahoma'
      ControlLook.DropDownHeader.Font.Style = []
      ControlLook.DropDownHeader.Visible = True
      ControlLook.DropDownHeader.Buttons = <>
      ControlLook.DropDownFooter.Font.Charset = DEFAULT_CHARSET
      ControlLook.DropDownFooter.Font.Color = clWindowText
      ControlLook.DropDownFooter.Font.Height = -11
      ControlLook.DropDownFooter.Font.Name = 'Tahoma'
      ControlLook.DropDownFooter.Font.Style = []
      ControlLook.DropDownFooter.Visible = True
      ControlLook.DropDownFooter.Buttons = <>
      Filter = <>
      FilterDropDown.Font.Charset = DEFAULT_CHARSET
      FilterDropDown.Font.Color = clWindowText
      FilterDropDown.Font.Height = -11
      FilterDropDown.Font.Name = 'Tahoma'
      FilterDropDown.Font.Style = []
      FilterDropDown.TextChecked = 'Checked'
      FilterDropDown.TextUnChecked = 'Unchecked'
      FilterDropDownClear = '(All)'
      FilterEdit.TypeNames.Strings = (
        'Starts with'
        'Ends with'
        'Contains'
        'Not contains'
        'Equal'
        'Not equal'
        'Larger than'
        'Smaller than'
        'Clear')
      FixedColWidth = 120
      FixedRowHeight = 22
      FixedFont.Charset = HANGEUL_CHARSET
      FixedFont.Color = clBlack
      FixedFont.Height = -12
      FixedFont.Name = #44404#47548#52404
      FixedFont.Style = []
      FloatFormat = '%.2f'
      HoverButtons.Buttons = <>
      HoverButtons.Position = hbLeftFromColumnLeft
      HTMLSettings.ImageFolder = 'images'
      HTMLSettings.ImageBaseName = 'img'
      Look = glStandard
      PrintSettings.DateFormat = 'dd/mm/yyyy'
      PrintSettings.Font.Charset = DEFAULT_CHARSET
      PrintSettings.Font.Color = clWindowText
      PrintSettings.Font.Height = -11
      PrintSettings.Font.Name = 'Tahoma'
      PrintSettings.Font.Style = []
      PrintSettings.FixedFont.Charset = DEFAULT_CHARSET
      PrintSettings.FixedFont.Color = clWindowText
      PrintSettings.FixedFont.Height = -11
      PrintSettings.FixedFont.Name = 'Tahoma'
      PrintSettings.FixedFont.Style = []
      PrintSettings.HeaderFont.Charset = DEFAULT_CHARSET
      PrintSettings.HeaderFont.Color = clWindowText
      PrintSettings.HeaderFont.Height = -11
      PrintSettings.HeaderFont.Name = 'Tahoma'
      PrintSettings.HeaderFont.Style = []
      PrintSettings.FooterFont.Charset = DEFAULT_CHARSET
      PrintSettings.FooterFont.Color = clWindowText
      PrintSettings.FooterFont.Height = -11
      PrintSettings.FooterFont.Name = 'Tahoma'
      PrintSettings.FooterFont.Style = []
      PrintSettings.PageNumSep = '/'
      ScrollProportional = True
      ScrollSynch = True
      SearchFooter.Color = clBtnFace
      SearchFooter.FindNextCaption = 'Find &next'
      SearchFooter.FindPrevCaption = 'Find &previous'
      SearchFooter.Font.Charset = DEFAULT_CHARSET
      SearchFooter.Font.Color = clWindowText
      SearchFooter.Font.Height = -11
      SearchFooter.Font.Name = 'Tahoma'
      SearchFooter.Font.Style = []
      SearchFooter.HighLightCaption = 'Highlight'
      SearchFooter.HintClose = 'Close'
      SearchFooter.HintFindNext = 'Find next occurrence'
      SearchFooter.HintFindPrev = 'Find previous occurrence'
      SearchFooter.HintHighlight = 'Highlight occurrences'
      SearchFooter.MatchCaseCaption = 'Match case'
      SelectionColor = clHighlight
      SelectionTextColor = clHighlightText
      ShowDesignHelper = False
      SortSettings.DefaultFormat = ssAutomatic
      SortSettings.HeaderColorTo = 16579058
      SortSettings.HeaderMirrorColor = 16380385
      SortSettings.HeaderMirrorColorTo = 16182488
      Version = '7.8.4.0'
      WordWrap = False
    end
    object GroupBox1: TGroupBox
      Left = 220
      Top = 4
      Width = 568
      Height = 52
      Caption = ' '#51312#54924' '
      TabOrder = 2
      object IMGDELETE: TImage
        Left = 426
        Top = 16
        Width = 100
        Height = 28
        AutoSize = True
        OnClick = IMGDELETEClick
        OnMouseEnter = IMGDELETEMouseEnter
        OnMouseLeave = IMGDELETEMouseLeave
      end
      object IMGFIND: TImage
        Left = 323
        Top = 16
        Width = 100
        Height = 28
        AutoSize = True
        OnClick = IMGFINDClick
        OnMouseEnter = IMGFINDMouseEnter
        OnMouseLeave = IMGFINDMouseLeave
      end
      object lblFind: TLabel
        Left = 37
        Top = 22
        Width = 45
        Height = 14
        Caption = #49324'  '#50629'  '#47749
      end
      object edtFind: TbsSkinEdit
        Tag = 200
        Left = 113
        Top = 21
        Width = 173
        Height = 18
        DefaultColor = clWindow
        DefaultFont.Charset = HANGEUL_CHARSET
        DefaultFont.Color = clBlack
        DefaultFont.Height = -12
        DefaultFont.Name = #44404#47548#52404
        DefaultFont.Style = []
        UseSkinFont = False
        DefaultWidth = 0
        DefaultHeight = 0
        ButtonMode = False
        SkinDataName = 'edit'
        Alignment = taCenter
        Font.Charset = HANGEUL_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = #44404#47548#52404
        Font.Style = []
        ImeName = 'Microsoft Office IME 2007'
        ParentFont = False
        TabOrder = 0
        ButtonImageIndex = -1
        LeftImageIndex = -1
        LeftImageHotIndex = -1
        LeftImageDownIndex = -1
        RightImageIndex = -1
        RightImageHotIndex = -1
        RightImageDownIndex = -1
        OnEnter = edtHangeul_OnEnter
        OnKeyPress = edtFindKeyPress
      end
    end
    object GroupBox2: TGroupBox
      Left = 8
      Top = 4
      Width = 200
      Height = 52
      Caption = ' '#46321#47197' '
      TabOrder = 3
      object IMGREGIST: TImage
        Left = 48
        Top = 16
        Width = 100
        Height = 28
        AutoSize = True
        OnClick = IMGREGISTClick
        OnMouseEnter = IMGREGISTMouseEnter
        OnMouseLeave = IMGREGISTMouseLeave
      end
    end
  end
  object palWait: TbsSkinExPanel
    Left = 258
    Top = 234
    Width = 271
    Height = 80
    HintImageIndex = 0
    TabOrder = 2
    Visible = False
    SkinDataName = 'expanel'
    DefaultFont.Charset = ANSI_CHARSET
    DefaultFont.Color = clWindowText
    DefaultFont.Height = -12
    DefaultFont.Name = #44404#47548#52404
    DefaultFont.Style = [fsBold]
    DefaultWidth = 0
    DefaultHeight = 0
    UseSkinFont = False
    UseSkinSize = False
    CaptionImageIndex = -1
    NumGlyphs = 1
    Spacing = 2
    RealWidth = 0
    RealHeight = 0
    ShowRollButton = False
    ShowCloseButton = False
    DefaultCaptionHeight = 21
    RollState = False
    RollKind = rkRollVertical
    Moveable = False
    Sizeable = False
    Caption = 'Wait...'
    object bsSkinStdLabel1: TbsSkinStdLabel
      Left = 67
      Top = 37
      Width = 124
      Height = 12
      EllipsType = bsetNone
      UseSkinFont = False
      UseSkinColor = True
      DefaultFont.Charset = HANGEUL_CHARSET
      DefaultFont.Color = clWindowText
      DefaultFont.Height = -12
      DefaultFont.Name = #44404#47548#52404
      DefaultFont.Style = []
      SkinDataName = 'stdlabel'
      Font.Charset = HANGEUL_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = #44404#47548
      Font.Style = []
      Alignment = taCenter
      Caption = #51104#49884#47564' '#44592#45796#47140' '#51452#49464#50836'..'
      Color = clBtnFace
      ParentColor = False
      ParentFont = False
      Layout = tlCenter
    end
    object bsSkinStdLabel2: TbsSkinStdLabel
      Left = 67
      Top = 55
      Width = 148
      Height = 12
      EllipsType = bsetNone
      UseSkinFont = False
      UseSkinColor = True
      DefaultFont.Charset = HANGEUL_CHARSET
      DefaultFont.Color = clWindowText
      DefaultFont.Height = -12
      DefaultFont.Name = #44404#47548#52404
      DefaultFont.Style = []
      SkinDataName = 'stdlabel'
      Font.Charset = HANGEUL_CHARSET
      Font.Color = clBtnText
      Font.Height = -12
      Font.Name = #44404#47548
      Font.Style = []
      Alignment = taCenter
      Caption = #49440#53469' '#51089#50629#51012' '#51201#50857#51473#51077#45768#45796'..'
      Color = clBtnFace
      ParentColor = False
      ParentFont = False
      Layout = tlCenter
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
    object Label1: TLabel
      Left = 109
      Top = 4
      Width = 37
      Height = 14
      Caption = 'Label1'
    end
  end
  object FileOpenDialog1: TFileOpenDialog
    DefaultExtension = '*.xls'
    FavoriteLinks = <>
    FileTypes = <>
    Options = []
    Left = 696
    Top = 280
  end
  object AdvGridExcelIO1: TAdvGridExcelIO
    AdvStringGrid = frmMemoRegist.sgResult
    Options.ExportOverwriteMessage = 'File %s already exists'#13'Ok to overwrite ?'
    Options.ExportRawRTF = False
    Options.ExportHardBorders = True
    UseUnicode = False
    GridStartRow = 0
    GridStartCol = 0
    Version = '3.13'
    Left = 1304
    Top = 528
  end
end
