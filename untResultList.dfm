object frmResultList: TfrmResultList
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #44396#45824#51109' '#49548#50976#51088'/'#50672#54785' '#51221#48372
  ClientHeight = 921
  ClientWidth = 1342
  Color = clBtnFace
  Font.Charset = HANGEUL_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #44404#47548#52404
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  Scaled = False
  OnActivate = FormActivate
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 12
  object shpBG: TShape
    Left = 0
    Top = 0
    Width = 1342
    Height = 921
    Align = alClient
    Brush.Style = bsClear
    Pen.Color = 16750131
    ExplicitLeft = -32
    ExplicitTop = 176
    ExplicitWidth = 1362
    ExplicitHeight = 977
  end
  object pnlMain: TPanel
    Left = 0
    Top = 0
    Width = 1342
    Height = 921
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    object pnlHistory: TPanel
      Left = 0
      Top = 70
      Width = 1342
      Height = 481
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 0
      object pnlHistoryD: TPanel
        Left = 0
        Top = 14
        Width = 1342
        Height = 467
        Align = alClient
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Color = clWhite
        ParentBackground = False
        TabOrder = 1
        object sgHistory: TAdvStringGrid
          Left = 0
          Top = 0
          Width = 1342
          Height = 467
          Cursor = crDefault
          Align = alClient
          BevelEdges = [beRight]
          BevelInner = bvNone
          BevelOuter = bvNone
          ColCount = 14
          Ctl3D = False
          DefaultColWidth = 100
          DefaultRowHeight = 40
          DrawingStyle = gdsClassic
          FixedColor = 16705757
          FixedCols = 0
          RowCount = 5
          FixedRows = 0
          Font.Charset = HANGEUL_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = #44404#47548#52404
          Font.Style = []
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goEditing, goTabs]
          ParentCtl3D = False
          ParentFont = False
          ScrollBars = ssVertical
          TabOrder = 0
          OnEnter = edtHangeulEnter
          OnExit = sgHistoryExit
          OnKeyDown = sgHistoryKeyDown
          OnKeyPress = sgHistoryKeyPress
          OnMouseLeave = sgHistoryMouseLeave
          HoverRowCells = [hcNormal, hcSelected]
          OnClickCell = sgHistoryClickCell
          ActiveCellFont.Charset = HANGEUL_CHARSET
          ActiveCellFont.Color = clRed
          ActiveCellFont.Height = -13
          ActiveCellFont.Name = #44404#47548#52404
          ActiveCellFont.Style = []
          BorderColor = clWhite
          ControlLook.FixedGradientHoverFrom = clGray
          ControlLook.FixedGradientHoverTo = clWhite
          ControlLook.FixedGradientDownFrom = clGray
          ControlLook.FixedGradientDownTo = clSilver
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
          FixedColWidth = 100
          FixedRowHeight = 20
          FixedFont.Charset = HANGEUL_CHARSET
          FixedFont.Color = clWindowText
          FixedFont.Height = -13
          FixedFont.Name = #44404#47548#52404
          FixedFont.Style = []
          Flat = True
          FloatFormat = '%.2f'
          HoverButtons.Buttons = <>
          HoverButtons.Position = hbLeftFromColumnLeft
          HTMLSettings.ImageFolder = 'images'
          HTMLSettings.ImageBaseName = 'img'
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
          SelectionColor = clInfoBk
          SortSettings.DefaultFormat = ssAutomatic
          Version = '7.8.4.0'
          RowHeights = (
            20
            40
            40
            40
            40)
          object Shape1: TShape
            Left = 698
            Top = 0
            Width = 2
            Height = 469
            Brush.Color = clRed
            Pen.Color = clRed
            Pen.Style = psDot
            Shape = stRoundRect
          end
        end
      end
      object pnlHistoryT: TPanel
        Left = 0
        Top = 0
        Width = 1342
        Height = 14
        Align = alTop
        Alignment = taRightJustify
        BevelOuter = bvNone
        Caption = '['#50672#54785' '#51221#48372'] '
        Color = clGray
        Font.Charset = ANSI_CHARSET
        Font.Color = clWhite
        Font.Height = -12
        Font.Name = #44404#47548#52404
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 0
        object lblPosHistory: TLabel
          Left = 693
          Top = 2
          Width = 13
          Height = 12
          Caption = #9660
          Font.Charset = ANSI_CHARSET
          Font.Color = clWhite
          Font.Height = -12
          Font.Name = #44404#47548#52404
          Font.Style = [fsBold]
          ParentFont = False
        end
        object lblNoHistory: TLabel
          Left = 0
          Top = 0
          Width = 1246
          Height = 12
          Align = alClient
          Caption = 
            '      13            12            11            10              ' +
            '9             8             7              6             5      ' +
            '       4             3             2             1'
          Font.Charset = ANSI_CHARSET
          Font.Color = clYellow
          Font.Height = -12
          Font.Name = #44404#47548#52404
          Font.Style = [fsBold]
          ParentFont = False
        end
      end
    end
    object pnlOwnInfo: TPanel
      Left = 0
      Top = 551
      Width = 1342
      Height = 370
      Align = alBottom
      BevelOuter = bvNone
      Caption = 'pnlOwnInfo'
      TabOrder = 1
      object pnlOwnInfoD: TPanel
        Left = 0
        Top = 28
        Width = 1342
        Height = 342
        Align = alClient
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Color = clWhite
        ParentBackground = False
        TabOrder = 1
        object sgOwnInfo: TAdvStringGrid
          Left = 0
          Top = 0
          Width = 1342
          Height = 342
          Cursor = crDefault
          Align = alClient
          BevelEdges = [beRight]
          BevelInner = bvNone
          BevelOuter = bvNone
          ColCount = 25
          Ctl3D = False
          DefaultColWidth = 54
          DefaultRowHeight = 40
          DrawingStyle = gdsClassic
          FixedColor = 16705757
          FixedCols = 0
          RowCount = 4
          FixedRows = 0
          Font.Charset = HANGEUL_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = #44404#47548#52404
          Font.Style = []
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goEditing]
          ParentCtl3D = False
          ParentFont = False
          ScrollBars = ssVertical
          TabOrder = 0
          OnExit = sgOwnInfoExit
          OnKeyDown = sgOwnInfoKeyDown
          OnKeyPress = sgOwnInfoKeyPress
          OnMouseLeave = sgOwnInfoMouseLeave
          HoverRowCells = [hcNormal, hcSelected]
          OnClickCell = sgOwnInfoClickCell
          ActiveCellFont.Charset = HANGEUL_CHARSET
          ActiveCellFont.Color = clRed
          ActiveCellFont.Height = -13
          ActiveCellFont.Name = #44404#47548#52404
          ActiveCellFont.Style = []
          BorderColor = clWhite
          ControlLook.FixedGradientHoverFrom = clGray
          ControlLook.FixedGradientHoverTo = clWhite
          ControlLook.FixedGradientDownFrom = clGray
          ControlLook.FixedGradientDownTo = clSilver
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
          FixedColWidth = 54
          FixedRowHeight = 20
          FixedFont.Charset = HANGEUL_CHARSET
          FixedFont.Color = clWindowText
          FixedFont.Height = -13
          FixedFont.Name = #44404#47548#52404
          FixedFont.Style = []
          Flat = True
          FloatFormat = '%.2f'
          HoverButtons.Buttons = <>
          HoverButtons.Position = hbLeftFromColumnLeft
          HTMLSettings.ImageFolder = 'images'
          HTMLSettings.ImageBaseName = 'img'
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
          SelectionColor = clInfoBk
          SortSettings.DefaultFormat = ssAutomatic
          Version = '7.8.4.0'
          RowHeights = (
            20
            40
            40
            40)
          object Shape2: TShape
            Left = 700
            Top = 0
            Width = 2
            Height = 344
            Brush.Color = clRed
            Pen.Color = clRed
            Pen.Style = psDot
            Shape = stRoundRect
          end
        end
      end
      object pnlOwnInfoT: TPanel
        Left = 0
        Top = 0
        Width = 1342
        Height = 14
        Align = alTop
        Alignment = taRightJustify
        BevelOuter = bvNone
        Caption = '['#49548#50976#51088' '#51221#48372'] '
        Color = clGray
        Font.Charset = ANSI_CHARSET
        Font.Color = clWhite
        Font.Height = -12
        Font.Name = #44404#47548#52404
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 0
        object lblEra: TLabel
          Left = 891
          Top = 1
          Width = 298
          Height = 12
          Caption = '1('#45800#44592'), 2('#47749#52824'), 3('#45824#51221'), 4('#49548#54868'), 5('#49436#44592') '
          Font.Charset = ANSI_CHARSET
          Font.Color = clWhite
          Font.Height = -12
          Font.Name = #44404#47548#52404
          Font.Style = [fsBold]
          ParentFont = False
        end
      end
      object pnlOwnInfoT1: TPanel
        Left = 0
        Top = 14
        Width = 1342
        Height = 14
        Align = alTop
        Alignment = taRightJustify
        BevelOuter = bvNone
        Color = clGray
        Font.Charset = ANSI_CHARSET
        Font.Color = clWhite
        Font.Height = -12
        Font.Name = #44404#47548#52404
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 2
        object lblPosOwnInfo: TLabel
          Left = 695
          Top = 2
          Width = 13
          Height = 12
          Caption = #9660
          Font.Charset = ANSI_CHARSET
          Font.Color = clWhite
          Font.Height = -12
          Font.Name = #44404#47548#52404
          Font.Style = [fsBold]
          ParentFont = False
        end
        object lblNoOwnInfo: TLabel
          Left = 0
          Top = 0
          Width = 1274
          Height = 12
          Align = alClient
          Caption = 
            '   24      23      22     21      20      19     18      17     ' +
            ' 16     15      14      13     12      11      10      9       8' +
            '       7      6       5       4       3      2       1'
          Font.Charset = ANSI_CHARSET
          Font.Color = clYellow
          Font.Height = -12
          Font.Name = #44404#47548#52404
          Font.Style = [fsBold]
          ParentFont = False
        end
      end
    end
    object pnlTitle: TPanel
      Left = 0
      Top = 0
      Width = 1342
      Height = 70
      Align = alTop
      Alignment = taLeftJustify
      BevelEdges = [beBottom]
      BevelKind = bkFlat
      BevelOuter = bvNone
      Color = clWhite
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -19
      Font.Name = #44404#47548#52404
      Font.Style = [fsBold]
      ParentBackground = False
      ParentFont = False
      TabOrder = 2
      object pnlJibunT: TPanel
        Left = 0
        Top = 0
        Width = 1342
        Height = 68
        Align = alClient
        BevelOuter = bvNone
        Color = clSilver
        ParentBackground = False
        TabOrder = 0
        object pnlJibun1: TPanel
          Left = 0
          Top = 0
          Width = 120
          Height = 68
          Align = alLeft
          BevelOuter = bvNone
          Color = 6553600
          ParentBackground = False
          TabOrder = 0
          object lblJibun1: TLabel
            Left = 29
            Top = 24
            Width = 64
            Height = 19
            Caption = #51648'  '#48264
            Color = clWhite
            Font.Charset = ANSI_CHARSET
            Font.Color = clWhite
            Font.Height = -19
            Font.Name = #44404#47548#52404
            Font.Style = [fsBold]
            ParentColor = False
            ParentFont = False
          end
        end
        object pnlJibun: TPanel
          Left = 120
          Top = 0
          Width = 574
          Height = 68
          Align = alClient
          Alignment = taRightJustify
          BevelOuter = bvNone
          Color = clWhite
          ParentBackground = False
          TabOrder = 1
          object btnHistory: TImage
            Left = 556
            Top = 0
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
            OnClick = btnHistoryClick
          end
          object lblWrite: TLabel
            Left = 568
            Top = 54
            Width = 6
            Height = 12
            Alignment = taRightJustify
            Font.Charset = ANSI_CHARSET
            Font.Color = clNavy
            Font.Height = -12
            Font.Name = #44404#47548#52404
            Font.Style = []
            ParentFont = False
          end
          object chkAreaChange: TCheckBox
            Left = 6
            Top = 26
            Width = 163
            Height = 17
            Caption = #51648#51201#45800#50948#48320#54872'('#13217')'
            Font.Charset = ANSI_CHARSET
            Font.Color = clNavy
            Font.Height = -12
            Font.Name = #44404#47548#52404
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
            Visible = False
          end
        end
        object Panel3: TPanel
          Left = 694
          Top = 0
          Width = 8
          Height = 68
          Align = alRight
          BevelOuter = bvNone
          Color = clWhite
          ParentBackground = False
          TabOrder = 2
        end
        object pnlPnuInfoT: TPanel
          Left = 702
          Top = 0
          Width = 504
          Height = 68
          Align = alRight
          Alignment = taLeftJustify
          BevelOuter = bvNone
          Color = clWhite
          Font.Charset = ANSI_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = #44404#47548#52404
          Font.Style = [fsBold]
          ParentBackground = False
          ParentFont = False
          TabOrder = 3
          OnMouseLeave = pnlPnuInfoTMouseLeave
          object lblJibunOK: TLabel
            Left = 94
            Top = 5
            Width = 52
            Height = 12
            Caption = #51648#48264#51068#52824
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = #44404#47548#52404
            Font.Style = [fsBold]
            ParentFont = False
            OnClick = lblJibunOKClick
          end
          object lblJibun: TLabel
            Left = 237
            Top = 6
            Width = 26
            Height = 12
            Caption = #51648#48264
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = #44404#47548#52404
            Font.Style = [fsBold]
            ParentFont = False
          end
          object lblMemo: TLabel
            Left = 76
            Top = 49
            Width = 26
            Height = 12
            Caption = #51201#50836
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = #44404#47548#52404
            Font.Style = [fsBold]
            ParentFont = False
          end
          object lblMemo1: TLabel
            Left = 264
            Top = 49
            Width = 59
            Height = 12
            Caption = '('#51648#51201#46020#51228
          end
          object lblMemo2: TLabel
            Left = 410
            Top = 49
            Width = 20
            Height = 12
            Caption = #54840')'
          end
          object lblLevel: TLabel
            Left = 76
            Top = 27
            Width = 26
            Height = 12
            Caption = #46321#44553
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = #44404#47548#52404
            Font.Style = [fsBold]
            ParentFont = False
          end
          object Shape4: TShape
            Left = 500
            Top = 0
            Width = 4
            Height = 70
            Brush.Color = clGray
            Pen.Color = clGray
          end
          object chkJibunOK: TCheckBox
            Left = 77
            Top = 2
            Width = 17
            Height = 17
            Checked = True
            Font.Charset = ANSI_CHARSET
            Font.Color = clWhite
            Font.Height = -13
            Font.Name = #44404#47548#52404
            Font.Style = [fsBold]
            ParentFont = False
            State = cbChecked
            TabOrder = 0
            OnKeyPress = edtKeyPress
          end
          object Panel2: TPanel
            Left = 146
            Top = 1
            Width = 72
            Height = 20
            BevelOuter = bvNone
            Caption = '(SpaceBar)'
            Color = clInfoBk
            Font.Charset = HANGEUL_CHARSET
            Font.Color = clRed
            Font.Height = -12
            Font.Name = #44404#47548#52404
            Font.Style = [fsBold]
            ParentBackground = False
            ParentFont = False
            TabOrder = 4
          end
          object Panel5: TPanel
            Left = 0
            Top = 0
            Width = 68
            Height = 68
            Align = alLeft
            BevelOuter = bvNone
            Caption = #51648#48264#51221#48372
            Color = 2192371
            Font.Charset = ANSI_CHARSET
            Font.Color = clWhite
            Font.Height = -12
            Font.Name = #44404#47548#52404
            Font.Style = [fsBold]
            ParentBackground = False
            ParentFont = False
            TabOrder = 5
          end
          object edtPnu: TEdit
            Left = 264
            Top = 2
            Width = 136
            Height = 20
            Alignment = taCenter
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = #44404#47548#52404
            Font.Style = []
            MaxLength = 20
            ParentFont = False
            TabOrder = 1
            OnEnter = edtHangeulEnter
            OnKeyDown = edtKeyDown
            OnKeyPress = edtKeyPress
          end
          object pnlJubinHelp: TPanel
            Left = 400
            Top = 2
            Width = 98
            Height = 20
            BevelOuter = bvNone
            Caption = '('#48520#51068#52824' '#49884' '#51077#47141')'
            Color = clInfoBk
            Font.Charset = HANGEUL_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = #44404#47548#52404
            Font.Style = []
            ParentBackground = False
            ParentFont = False
            TabOrder = 6
          end
          object edtMemo: TEdit
            Left = 104
            Top = 45
            Width = 160
            Height = 20
            Alignment = taCenter
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = #44404#47548#52404
            Font.Style = []
            MaxLength = 74
            ParentFont = False
            TabOrder = 2
            OnEnter = edtHangeulEnter
            OnKeyDown = edtKeyDown
            OnKeyPress = edtKeyPress
          end
          object edtDoho: TEdit
            Left = 329
            Top = 45
            Width = 80
            Height = 20
            Alignment = taCenter
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = #44404#47548#52404
            Font.Style = []
            MaxLength = 10
            ParentFont = False
            TabOrder = 3
            OnKeyDown = edtKeyDown
            OnKeyPress = edtKeyPress
          end
          object edtLevel: TEdit
            Left = 104
            Top = 24
            Width = 160
            Height = 20
            Alignment = taCenter
            Font.Charset = ANSI_CHARSET
            Font.Color = clBlack
            Font.Height = -12
            Font.Name = #44404#47548#52404
            Font.Style = []
            MaxLength = 20
            ParentFont = False
            TabOrder = 7
            OnEnter = edtHangeulEnter
            OnKeyDown = edtKeyDown
            OnKeyPress = edtKeyPress
          end
        end
        object pnlButton: TPanel
          Left = 1206
          Top = 0
          Width = 136
          Height = 68
          Align = alRight
          BevelOuter = bvNone
          Color = clWhite
          ParentBackground = False
          TabOrder = 4
          object btnSave: TbsSkinButton
            Tag = 1
            Left = 8
            Top = 10
            Width = 120
            Height = 52
            HintImageIndex = 0
            TabOrder = 0
            SkinData = frmMain.bsSkinData1
            SkinDataName = 'button'
            OnMouseEnter = btnSaveMouseEnter
            DefaultFont.Charset = ANSI_CHARSET
            DefaultFont.Color = clNavy
            DefaultFont.Height = -12
            DefaultFont.Name = #44404#47548#52404
            DefaultFont.Style = [fsBold]
            DefaultWidth = 0
            DefaultHeight = 0
            UseSkinFont = False
            Transparent = False
            CheckedMode = False
            ImageIndex = -1
            AlwaysShowLayeredFrame = False
            UseSkinSize = False
            UseSkinFontColor = False
            RepeatMode = False
            RepeatInterval = 100
            AllowAllUp = False
            TabStop = True
            CanFocused = True
            Down = False
            GroupIndex = 0
            Caption = #51200#51109
            NumGlyphs = 1
            Spacing = 1
            OnClick = btnSaveClick
          end
        end
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 921
    Width = 1342
    Height = 0
    Align = alBottom
    BevelOuter = bvNone
    Color = clWhite
    ParentBackground = False
    TabOrder = 1
    object Memo1: TMemo
      Left = 8
      Top = 20
      Width = 153
      Height = 73
      BevelInner = bvNone
      BevelOuter = bvNone
      ImeName = 'Microsoft Office IME 2007'
      Lines.Strings = (
        'Memo1')
      TabOrder = 0
      Visible = False
    end
  end
  object IdDecoderMIME1: TIdDecoderMIME
    FillChar = '='
    Left = 368
    Top = 192
  end
  object ActionList1: TActionList
    Left = 312
    Top = 192
    object ActionSave: TAction
      Caption = #51200#51109
      ShortCut = 16467
      OnExecute = ActionSaveExecute
    end
    object ActionSaveTemp: TAction
      Caption = #51076#49884#51200#51109
      ShortCut = 16468
    end
    object ActionSaveText: TAction
      Caption = 'ActionSaveText'
      ShortCut = 49242
    end
    object ActionLoadText: TAction
      Caption = 'ActionLoadText'
      ShortCut = 49241
    end
    object ActionLoadHistory: TAction
      Caption = 'ActionLoadHistory'
      ShortCut = 49238
    end
    object ActionLoadOwnInfo: TAction
      Caption = 'ActionLoadOwnInfo'
      ShortCut = 49240
    end
    object ActionShort1: TAction
      Caption = #53664#51648#46321#44553
      ShortCut = 116
      OnExecute = ActionShortExecute
    end
    object ActionShort2: TAction
      Caption = #44592#51456#49688#54869#47049
      ShortCut = 117
      OnExecute = ActionShortExecute
    end
    object ActionShort3: TAction
      Caption = #51076#45824#44032#44201
      ShortCut = 118
      OnExecute = ActionShortExecute
    end
    object ActionShort4: TAction
      Caption = #51648#47785#48320#44221
      ShortCut = 119
      OnExecute = ActionShortExecute
    end
    object ActionShort5: TAction
      Caption = #47532#53552
      ShortCut = 120
      OnExecute = ActionShortExecute
    end
    object ActionShort6: TAction
      Caption = #49437
      ShortCut = 121
      OnExecute = ActionShortExecute
    end
    object ActionShort7: TAction
      Caption = #54872
      ShortCut = 122
      OnExecute = ActionShortExecute
    end
    object ActionHistory1: TAction
      Caption = 'ActionHistory1'
      ShortCut = 8304
    end
    object ActionHistory2: TAction
      Caption = 'ActionHistory2'
      ShortCut = 8305
    end
    object ActionHistory3: TAction
      Caption = 'ActionHistory3'
      ShortCut = 8306
    end
    object ActionHistory4: TAction
      Caption = 'ActionHistory4'
      ShortCut = 8307
    end
    object ActionHistory5: TAction
      Caption = 'ActionHistory5'
      ShortCut = 8308
    end
    object ActionHistory6: TAction
      Caption = 'ActionHistory6'
      ShortCut = 8309
    end
    object ActionHistory7: TAction
      Caption = 'ActionHistory7'
      ShortCut = 8310
    end
    object ActionHistory8: TAction
      Caption = 'ActionHistory8'
      ShortCut = 8311
    end
    object ActionHistory9: TAction
      Caption = 'ActionHistory9'
      ShortCut = 8312
    end
    object ActionHistory10: TAction
      Caption = 'ActionHistory10'
      ShortCut = 8313
    end
    object ActionHistory11: TAction
      Caption = 'ActionHistory11'
      ShortCut = 8314
    end
    object ActionHistory12: TAction
      Caption = 'ActionHistory12'
      ShortCut = 8315
    end
    object ActionHistory13: TAction
      Caption = 'ActionHistory13'
      ShortCut = 49217
    end
    object ActionHistory14: TAction
      Caption = 'ActionHistory14'
      ShortCut = 49218
    end
    object ActionHistory15: TAction
      Caption = 'ActionHistory15'
      ShortCut = 49223
    end
    object ActionHistory16: TAction
      Caption = 'ActionHistory16'
      ShortCut = 49224
    end
    object ActionHistory17: TAction
      Caption = 'ActionHistory17'
      ShortCut = 49225
    end
    object ActionHistory18: TAction
      Caption = 'ActionHistory18'
      ShortCut = 49226
    end
    object ActionEra1: TAction
      Caption = #45800#44592
      ShortCut = 16496
    end
    object ActionEra2: TAction
      Caption = #47749#52824
      ShortCut = 16497
    end
    object ActionEra3: TAction
      Caption = #45824#51221
      ShortCut = 16498
    end
    object ActionEra4: TAction
      Caption = #49548#54868
      ShortCut = 16499
    end
    object ActionReason1: TAction
      Caption = #49324#51221
      ShortCut = 16500
    end
    object ActionReason2: TAction
      Caption = #49548#50976#44428#48372#51316
      ShortCut = 16501
    end
    object ActionReason3: TAction
      Caption = #49548#50976#44428#51060#51204
      ShortCut = 16502
    end
    object ActionReason4: TAction
      Caption = #50472#49444#51221
      ShortCut = 16503
    end
    object ActionReason5: TAction
      Caption = #51452#49548#48320#44221
      ShortCut = 16504
    end
    object ActionReason6: TAction
      Caption = #49457#47749#48373#44396
      ShortCut = 16505
    end
    object ActionReason7: TAction
      Caption = 'ActionReason7'
      ShortCut = 16506
    end
    object ActionReason8: TAction
      Caption = 'ActionReason8'
      ShortCut = 16507
    end
    object ActionPrev: TAction
      Caption = #51060#51204#51060#48120#51648
      ShortCut = 16464
    end
    object ActionNext: TAction
      Caption = #45796#51020#51060#48120#51648
      ShortCut = 16462
    end
    object ActionZoomIn: TAction
      Caption = #54869#45824
      ShortCut = 16457
    end
    object ActionZoomOut: TAction
      Caption = #52629#49548
      ShortCut = 16463
    end
    object ActionDate1: TAction
      Caption = 'ActionDate1'
      ShortCut = 24688
    end
    object ActionDate2: TAction
      Caption = 'ActionDate2'
      ShortCut = 24689
    end
    object ActionDate3: TAction
      Caption = 'ActionDate3'
      ShortCut = 24690
    end
    object ActionDate4: TAction
      Caption = 'ActionDate4'
      ShortCut = 24691
    end
    object ActionDate5: TAction
      Caption = 'ActionDate5'
      ShortCut = 24692
    end
    object ActionDate6: TAction
      Caption = 'ActionDate6'
      ShortCut = 24693
    end
    object ActionDate7: TAction
      Caption = 'ActionDate7'
      ShortCut = 24694
    end
    object ActionDate8: TAction
      Caption = 'ActionDate8'
      ShortCut = 24695
    end
    object ActionDate9: TAction
      Caption = 'ActionDate9'
      ShortCut = 24696
    end
    object ActionDate10: TAction
      Caption = 'ActionDate10'
      ShortCut = 24697
    end
    object ActionDate11: TAction
      Caption = 'ActionDate11'
      ShortCut = 24698
    end
    object ActionDate12: TAction
      Caption = 'ActionDate12'
      ShortCut = 24699
    end
    object ActionSaveHistory: TAction
      Caption = 'ActionSaveHistory'
      ShortCut = 16459
    end
    object ActionSaveOwnInfo: TAction
      Caption = 'ActionSaveOwnInfo'
      ShortCut = 16460
    end
  end
  object AdvGridExcelIO1: TAdvGridExcelIO
    AdvStringGrid = sgHistory
    Options.ExportOverwriteMessage = 'File %s already exists'#13'Ok to overwrite ?'
    Options.ExportRawRTF = False
    Options.ExportHardBorders = True
    UseUnicode = False
    GridStartRow = 0
    GridStartCol = 0
    Version = '3.13'
    Left = 486
    Top = 191
  end
  object AdvGridExcelIO2: TAdvGridExcelIO
    AdvStringGrid = sgOwnInfo
    Options.ExportOverwriteMessage = 'File %s already exists'#13'Ok to overwrite ?'
    Options.ExportRawRTF = False
    Options.ExportHardBorders = True
    UseUnicode = False
    GridStartRow = 0
    GridStartCol = 0
    Version = '3.13'
    Left = 550
    Top = 191
  end
  object SaveDialog1: TSaveDialog
    Filter = #50641#49472#54028#51068'|*.xls'
    Title = #50641#49472' '#54028#51068' '#51200#51109#54616#44592
    Left = 615
    Top = 191
  end
end
