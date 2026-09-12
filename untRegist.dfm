object frmRegist: TfrmRegist
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = #51648#51201#54665#51221
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
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 14
  object pnlData: TPanel
    Left = 0
    Top = 0
    Width = 800
    Height = 554
    Align = alClient
    BevelEdges = [beLeft, beTop, beRight]
    BevelKind = bkFlat
    BevelOuter = bvNone
    Caption = #51648#44032#52636#47141
    ParentBackground = False
    TabOrder = 0
    ExplicitWidth = 1920
    ExplicitHeight = 1040
    object Image1: TImage
      Left = 525
      Top = 403
      Width = 105
      Height = 105
    end
    object panWindowsMove: TPanel
      Left = 0
      Top = 0
      Width = 796
      Height = 32
      Align = alTop
      Alignment = taLeftJustify
      BevelOuter = bvNone
      Color = 16750131
      Font.Charset = HANGEUL_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = #45208#45588#44256#46357
      Font.Style = [fsBold]
      ParentBackground = False
      ParentFont = False
      TabOrder = 0
      OnMouseDown = panWindowsMoveMouseDown
      object btnCloseTypeB: TImage
        Left = 768
        Top = 5
        Width = 22
        Height = 22
        AutoSize = True
        ParentShowHint = False
        ShowHint = False
        OnClick = btnCloseTypeBClick
      end
      object lblFormTitle: TLabel
        Left = 14
        Top = 9
        Width = 100
        Height = 14
        Caption = #51068#44292#46321#47197' '#51088#47308#47785#47197
        Font.Charset = ANSI_CHARSET
        Font.Color = clWhite
        Font.Height = -12
        Font.Name = #45208#45588#44256#46357
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
    object pnlDataM: TPanel
      Left = 8
      Top = 32
      Width = 780
      Height = 520
      Align = alClient
      BevelEdges = [beTop, beBottom]
      BevelKind = bkFlat
      BevelOuter = bvNone
      ParentBackground = False
      TabOrder = 1
      ExplicitTop = 27
      ExplicitWidth = 1900
      ExplicitHeight = 1011
      object Panel4: TPanel
        Left = 0
        Top = 8
        Width = 780
        Height = 500
        Align = alClient
        BevelOuter = bvNone
        Color = clWhite
        ParentBackground = False
        TabOrder = 0
        ExplicitWidth = 1200
        ExplicitHeight = 991
        object sgResult: TAdvStringGrid
          Left = 0
          Top = 0
          Width = 780
          Height = 500
          Cursor = crDefault
          ColCount = 6
          Ctl3D = True
          DefaultColWidth = 120
          DrawingStyle = gdsClassic
          FixedCols = 0
          RowCount = 2
          Font.Charset = HANGEUL_CHARSET
          Font.Color = clGray
          Font.Height = -12
          Font.Name = #44404#47548#52404
          Font.Style = []
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
          ParentCtl3D = False
          ParentFont = False
          ScrollBars = ssBoth
          TabOrder = 0
          GridFixedLineColor = clSilver
          HoverRowCells = [hcNormal, hcSelected]
          OnGetAlignment = sgResultGetAlignment
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
      end
      object pnlTitle: TPanel
        Left = 0
        Top = 0
        Width = 780
        Height = 8
        Align = alTop
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Color = clWhite
        ParentBackground = False
        TabOrder = 1
        ExplicitWidth = 1900
      end
      object Panel1: TPanel
        Left = 0
        Top = 508
        Width = 780
        Height = 8
        Align = alBottom
        Alignment = taLeftJustify
        BevelOuter = bvNone
        Color = clWhite
        ParentBackground = False
        TabOrder = 2
        ExplicitTop = 999
        ExplicitWidth = 1900
      end
    end
    object pnlBlankL: TPanel
      Left = 0
      Top = 32
      Width = 8
      Height = 520
      Align = alLeft
      BevelEdges = [beTop, beBottom]
      BevelKind = bkFlat
      BevelOuter = bvNone
      Color = clWhite
      ParentBackground = False
      TabOrder = 2
      ExplicitTop = 27
      ExplicitHeight = 1011
    end
    object pnlBlankR: TPanel
      Left = 788
      Top = 32
      Width = 8
      Height = 520
      Align = alRight
      BevelEdges = [beTop, beBottom]
      BevelKind = bkFlat
      BevelOuter = bvNone
      Color = clWhite
      ParentBackground = False
      TabOrder = 3
      ExplicitLeft = 1908
      ExplicitTop = 27
      ExplicitHeight = 1011
    end
  end
end
