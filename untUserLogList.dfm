object frmUserLogList: TfrmUserLogList
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsNone
  Caption = #49324#50857#51088' '#47196#44536' '#44592#47197
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
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 14
  object shpBG: TShape
    Left = 0
    Top = 0
    Width = 747
    Height = 445
    Align = alClient
    Brush.Style = bsClear
    Pen.Color = 16750131
    ExplicitWidth = 700
    ExplicitHeight = 394
  end
  object panCenter: TPanel
    Left = 1
    Top = 32
    Width = 745
    Height = 412
    BevelOuter = bvNone
    Color = clWhite
    ParentBackground = False
    TabOrder = 0
    object Panel2: TPanel
      Left = 0
      Top = 40
      Width = 745
      Height = 6
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 0
    end
    object Panel3: TPanel
      Left = 0
      Top = 371
      Width = 745
      Height = 41
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 1
      object IMGSAVELOG: TImage
        Left = 530
        Top = 8
        Width = 100
        Height = 28
        OnClick = IMGSAVELOGClick
        OnMouseEnter = IMGSAVELOGMouseEnter
        OnMouseLeave = IMGSAVELOGMouseLeave
      end
      object IMGEXIT: TImage
        Left = 634
        Top = 8
        Width = 100
        Height = 28
        OnClick = IMGEXITClick
        OnMouseEnter = IMGEXITMouseEnter
        OnMouseLeave = IMGEXITMouseLeave
      end
    end
    object Panel4: TPanel
      Left = 0
      Top = 46
      Width = 6
      Height = 325
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 2
    end
    object Panel5: TPanel
      Left = 739
      Top = 46
      Width = 6
      Height = 325
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 3
    end
    object PageControl1: TPageControl
      Left = 6
      Top = 46
      Width = 733
      Height = 325
      ActivePage = TabSheet2
      Align = alClient
      TabOrder = 4
      OnChange = PageControl1Change
      OnChanging = PageControl1Changing
      object TabSheet1: TTabSheet
        Caption = ' '#47196#44536#51064' '#44592#47197' '
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object pnlLog: TPanel
          Left = 0
          Top = 0
          Width = 725
          Height = 296
          Align = alClient
          BevelOuter = bvNone
          Color = clBtnShadow
          ParentBackground = False
          TabOrder = 0
          object sgLog: TAdvStringGrid
            Left = 0
            Top = 24
            Width = 725
            Height = 272
            Cursor = crDefault
            Align = alClient
            DefaultRowHeight = 20
            DrawingStyle = gdsClassic
            RowCount = 16
            Font.Charset = HANGEUL_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = #44404#47548#52404
            Font.Style = []
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSelect]
            ParentFont = False
            ScrollBars = ssBoth
            TabOrder = 0
            GridFixedLineColor = clSilver
            HoverRowCells = [hcNormal, hcSelected]
            OnGetAlignment = sgLogGetAlignment
            OnClickCell = sgLogClickCell
            ActiveCellFont.Charset = HANGEUL_CHARSET
            ActiveCellFont.Color = clWindowText
            ActiveCellFont.Height = -12
            ActiveCellFont.Name = #44404#47548#52404
            ActiveCellFont.Style = []
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
            FixedRowHeight = 20
            FixedFont.Charset = HANGEUL_CHARSET
            FixedFont.Color = clWindowText
            FixedFont.Height = -12
            FixedFont.Name = #44404#47548#52404
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HoverButtons.Position = hbLeftFromColumnLeft
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glStandard
            MouseActions.WheelIncrement = 1
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
            SelectionColor = clYellow
            SortSettings.DefaultFormat = ssAutomatic
            Version = '7.8.4.0'
          end
          object pnlLogT: TPanel
            Left = 0
            Top = 0
            Width = 725
            Height = 24
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = ' '#9654' '#47196#44536#51064#44592#47197
            Color = clActiveBorder
            Font.Charset = HANGEUL_CHARSET
            Font.Color = clWhite
            Font.Height = -12
            Font.Name = #44404#47548#52404
            Font.Style = [fsBold]
            ParentBackground = False
            ParentFont = False
            TabOrder = 1
            object lblLog: TLabel
              Left = 504
              Top = 5
              Width = 33
              Height = 14
              Caption = #49324#50857#51088
              Font.Charset = ANSI_CHARSET
              Font.Color = clWhite
              Font.Height = -12
              Font.Name = #45208#45588#44256#46357
              Font.Style = [fsBold]
              ParentFont = False
            end
            object cboLog: TComboBox
              Left = 556
              Top = 2
              Width = 120
              Height = 20
              Style = csDropDownList
              Font.Charset = HANGEUL_CHARSET
              Font.Color = clNavy
              Font.Height = -12
              Font.Name = #44404#47548#52404
              Font.Style = [fsBold]
              ItemIndex = 0
              ParentFont = False
              TabOrder = 0
              Text = #51204#52404
              OnClick = cboLogClick
              Items.Strings = (
                #51204#52404
                #44288#47532#51088)
            end
          end
        end
      end
      object TabSheet2: TTabSheet
        Caption = '   '#51089#50629' '#44592#47197'   '
        ImageIndex = 1
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object pnlHist: TPanel
          Left = 0
          Top = 0
          Width = 725
          Height = 296
          Align = alClient
          BevelOuter = bvNone
          Color = clBtnShadow
          ParentBackground = False
          TabOrder = 0
          object sgHist: TAdvStringGrid
            Left = 0
            Top = 24
            Width = 725
            Height = 272
            Cursor = crDefault
            Align = alClient
            ColCount = 6
            DefaultRowHeight = 20
            DrawingStyle = gdsClassic
            RowCount = 16
            Font.Charset = HANGEUL_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = #44404#47548#52404
            Font.Style = []
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSelect]
            ParentFont = False
            ScrollBars = ssBoth
            TabOrder = 0
            GridFixedLineColor = clSilver
            HoverRowCells = [hcNormal, hcSelected]
            OnGetAlignment = sgHistGetAlignment
            OnClickCell = sgHistClickCell
            ActiveCellFont.Charset = HANGEUL_CHARSET
            ActiveCellFont.Color = clWindowText
            ActiveCellFont.Height = -12
            ActiveCellFont.Name = #44404#47548#52404
            ActiveCellFont.Style = []
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
            FixedRowHeight = 20
            FixedFont.Charset = HANGEUL_CHARSET
            FixedFont.Color = clWindowText
            FixedFont.Height = -12
            FixedFont.Name = #44404#47548#52404
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HoverButtons.Position = hbLeftFromColumnLeft
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glStandard
            MouseActions.WheelIncrement = 1
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
            SelectionColor = clYellow
            SortSettings.DefaultFormat = ssAutomatic
            Version = '7.8.4.0'
          end
          object pnlHistT: TPanel
            Left = 0
            Top = 0
            Width = 725
            Height = 24
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = ' '#9654' '#51089#50629#44592#47197
            Color = clActiveBorder
            Font.Charset = HANGEUL_CHARSET
            Font.Color = clWhite
            Font.Height = -12
            Font.Name = #44404#47548#52404
            Font.Style = [fsBold]
            ParentBackground = False
            ParentFont = False
            TabOrder = 1
            object lblAct: TLabel
              Left = 504
              Top = 5
              Width = 44
              Height = 14
              Caption = #51089#50629#51333#47448
              Font.Charset = ANSI_CHARSET
              Font.Color = clWhite
              Font.Height = -12
              Font.Name = #45208#45588#44256#46357
              Font.Style = [fsBold]
              ParentFont = False
            end
            object cboAct: TComboBox
              Left = 556
              Top = 2
              Width = 120
              Height = 20
              Style = csDropDownList
              Font.Charset = HANGEUL_CHARSET
              Font.Color = clNavy
              Font.Height = -12
              Font.Name = #44404#47548#52404
              Font.Style = [fsBold]
              ParentFont = False
              TabOrder = 0
              OnClick = cboActClick
              Items.Strings = (
                #51204#52404
                #44160#49353
                #48320#44221
                #49325#51228
                #51064#49604
                #47928#49436#50676#46988
                #51648#51201#48520#48512#54633#51648#46321#47197
                #54028#51068#51200#51109
                #51648#51201#48520#48512#54633#51648#53685#44228
                #44428#54620#48320#44221
                #55092#47732#44228#51221#48320#44221)
            end
          end
        end
      end
      object TabSheet3: TTabSheet
        Caption = #54028#51068#51200#51109' '#44592#47197
        ImageIndex = 2
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object pnlDownload: TPanel
          Left = 0
          Top = 0
          Width = 725
          Height = 296
          Align = alClient
          BevelOuter = bvNone
          Color = clBtnShadow
          ParentBackground = False
          TabOrder = 0
          object sgDownload: TAdvStringGrid
            Left = 0
            Top = 24
            Width = 725
            Height = 272
            Cursor = crDefault
            Align = alClient
            DefaultRowHeight = 20
            DrawingStyle = gdsClassic
            RowCount = 16
            Font.Charset = HANGEUL_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = #44404#47548#52404
            Font.Style = []
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSelect]
            ParentFont = False
            ScrollBars = ssBoth
            TabOrder = 0
            GridFixedLineColor = clSilver
            HoverRowCells = [hcNormal, hcSelected]
            OnGetAlignment = sgDownloadGetAlignment
            OnClickCell = sgDownloadClickCell
            ActiveCellFont.Charset = HANGEUL_CHARSET
            ActiveCellFont.Color = clWindowText
            ActiveCellFont.Height = -12
            ActiveCellFont.Name = #44404#47548#52404
            ActiveCellFont.Style = []
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
            FixedRowHeight = 20
            FixedFont.Charset = HANGEUL_CHARSET
            FixedFont.Color = clWindowText
            FixedFont.Height = -12
            FixedFont.Name = #44404#47548#52404
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HoverButtons.Position = hbLeftFromColumnLeft
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glStandard
            MouseActions.WheelIncrement = 1
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
            SelectionColor = clYellow
            SortSettings.DefaultFormat = ssAutomatic
            Version = '7.8.4.0'
          end
          object pnlDownloadT: TPanel
            Left = 0
            Top = 0
            Width = 725
            Height = 24
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = ' '#9654' '#54028#51068' '#51200#51109' '#44592#47197
            Color = clActiveBorder
            Font.Charset = HANGEUL_CHARSET
            Font.Color = clWhite
            Font.Height = -12
            Font.Name = #44404#47548#52404
            Font.Style = [fsBold]
            ParentBackground = False
            ParentFont = False
            TabOrder = 1
          end
        end
      end
      object TabSheet4: TTabSheet
        Caption = ' '#44428#54620' '#48320#44221' '#44592#47197' '
        ImageIndex = 3
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object pnlGrade: TPanel
          Left = 0
          Top = 0
          Width = 725
          Height = 296
          Align = alClient
          BevelOuter = bvNone
          Color = clBtnShadow
          ParentBackground = False
          TabOrder = 0
          object sgGrade: TAdvStringGrid
            Left = 0
            Top = 24
            Width = 725
            Height = 272
            Cursor = crDefault
            Align = alClient
            ColCount = 9
            DefaultRowHeight = 20
            DrawingStyle = gdsClassic
            RowCount = 16
            Font.Charset = HANGEUL_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = #44404#47548#52404
            Font.Style = []
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSelect]
            ParentFont = False
            ScrollBars = ssBoth
            TabOrder = 0
            GridFixedLineColor = clSilver
            HoverRowCells = [hcNormal, hcSelected]
            OnGetAlignment = sgGradeGetAlignment
            OnClickCell = sgHistClickCell
            ActiveCellFont.Charset = HANGEUL_CHARSET
            ActiveCellFont.Color = clWindowText
            ActiveCellFont.Height = -12
            ActiveCellFont.Name = #44404#47548#52404
            ActiveCellFont.Style = []
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
            FixedRowHeight = 20
            FixedFont.Charset = HANGEUL_CHARSET
            FixedFont.Color = clWindowText
            FixedFont.Height = -12
            FixedFont.Name = #44404#47548#52404
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HoverButtons.Position = hbLeftFromColumnLeft
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glStandard
            MouseActions.WheelIncrement = 1
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
            SelectionColor = clYellow
            SortSettings.DefaultFormat = ssAutomatic
            Version = '7.8.4.0'
          end
          object pnlGradeT: TPanel
            Left = 0
            Top = 0
            Width = 725
            Height = 24
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = ' '#9654' '#44428#54620#48320#44221#44592#47197
            Color = clActiveBorder
            Font.Charset = HANGEUL_CHARSET
            Font.Color = clWhite
            Font.Height = -12
            Font.Name = #44404#47548#52404
            Font.Style = [fsBold]
            ParentBackground = False
            ParentFont = False
            TabOrder = 1
            object lblGrade: TLabel
              Left = 504
              Top = 5
              Width = 44
              Height = 14
              Caption = #51089#50629#51333#47448
              Font.Charset = ANSI_CHARSET
              Font.Color = clWhite
              Font.Height = -12
              Font.Name = #45208#45588#44256#46357
              Font.Style = [fsBold]
              ParentFont = False
            end
            object cboGrade: TComboBox
              Left = 556
              Top = 2
              Width = 120
              Height = 20
              Style = csDropDownList
              Font.Charset = HANGEUL_CHARSET
              Font.Color = clNavy
              Font.Height = -12
              Font.Name = #44404#47548#52404
              Font.Style = [fsBold]
              ParentFont = False
              TabOrder = 0
              OnClick = cboGradeClick
              Items.Strings = (
                #51204#52404
                #44160#49353
                #48320#44221
                #49325#51228
                #51064#49604
                #47928#49436#50676#46988
                #51648#51201#48520#48512#54633#51648#46321#47197
                #54028#51068#51200#51109
                #51648#51201#48520#48512#54633#51648#53685#44228
                #44428#54620#48320#44221
                #55092#47732#44228#51221#48320#44221)
            end
          end
        end
      end
    end
    object pnlFind: TPanel
      Left = 0
      Top = 0
      Width = 745
      Height = 40
      Align = alTop
      BevelEdges = [beBottom]
      BevelKind = bkFlat
      BevelOuter = bvNone
      TabOrder = 5
      object lblFind: TLabel
        Left = 122
        Top = 12
        Width = 63
        Height = 14
        Caption = #51312#54924#44592#44036'('#50900')'
      end
      object lblMid: TLabel
        Left = 280
        Top = 12
        Width = 8
        Height = 14
        Caption = '~'
      end
      object IMGFIND: TImage
        Left = 380
        Top = 8
        Width = 71
        Height = 22
        OnClick = IMGFINDClick
        OnMouseEnter = IMGFINDMouseEnter
        OnMouseLeave = IMGFINDMouseLeave
      end
      object dtEndMon: TMaskEdit
        Tag = 1
        Left = 294
        Top = 8
        Width = 71
        Height = 22
        Alignment = taCenter
        Color = clWhite
        EditMask = '####-##;1;_'
        ImeName = 'Microsoft Office IME 2007'
        MaxLength = 7
        TabOrder = 0
        Text = '    -  '
        OnEnter = edtDate_OnEnter
        OnExit = edtDate_OnExit
        OnKeyDown = edtDate_OnKeyDown
        OnKeyPress = edtDate_OnKeyPress
      end
      object dtSttMon: TMaskEdit
        Tag = 1
        Left = 200
        Top = 8
        Width = 71
        Height = 22
        Alignment = taCenter
        Color = clWhite
        EditMask = '####-##;1;_'
        ImeName = 'Microsoft Office IME 2007'
        MaxLength = 7
        TabOrder = 1
        Text = '    -  '
        OnEnter = edtDate_OnEnter
        OnExit = edtDate_OnExit
        OnKeyDown = edtDate_OnKeyDown
        OnKeyPress = edtDate_OnKeyPress
      end
      object chkDayOff: TCheckBox
        Left = 12
        Top = 8
        Width = 80
        Height = 24
        Alignment = taLeftJustify
        Caption = #50629#47924' '#50808' '#49884#44036
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlue
        Font.Height = -12
        Font.Name = #45208#45588#44256#46357
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        OnClick = chkDayOffClick
      end
    end
  end
  object panWindowsMove: TPanel
    Left = 1
    Top = 0
    Width = 747
    Height = 32
    BevelEdges = [beLeft, beTop, beRight]
    BevelOuter = bvNone
    Color = 16750131
    ParentBackground = False
    TabOrder = 1
    OnMouseDown = panWindowsMoveMouseDown
    object Image3: TImage
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
      Width = 83
      Height = 14
      Caption = #49324#50857#51088' '#47196#44536' '#44592#47197
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = #45208#45588#44256#46357
      Font.Style = [fsBold]
      ParentFont = False
      OnMouseDown = panWindowsMoveMouseDown
    end
    object btnCloseTypeB: TImage
      Left = 721
      Top = 5
      Width = 22
      Height = 22
      Cursor = crHandPoint
      OnClick = btnCloseTypeBClick
    end
  end
  object palWait: TPanel
    Left = 220
    Top = 150
    Width = 264
    Height = 80
    BevelOuter = bvNone
    Color = clWhite
    ParentBackground = False
    TabOrder = 2
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
      Left = 67
      Top = 37
      Width = 109
      Height = 14
      Caption = #51104#49884#47564' '#44592#45796#47140' '#51452#49464#50836'.'
    end
    object lblWait2: TLabel
      Left = 67
      Top = 55
      Width = 131
      Height = 14
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
  object SaveDialog1: TSaveDialog
    DefaultExt = '.xls'
    Filter = 'Excel Files(*.xls)|*.xls'
    Title = #47196#44536#44592#47197' '#51200#51109#54616#44592
    Left = 544
    Top = 32
  end
  object AdvGridExcelIO1: TAdvGridExcelIO
    AdvStringGrid = sgLog
    Options.ExportOverwriteMessage = 'File %s already exists'#13'Ok to overwrite ?'
    Options.ExportCellFormats = False
    Options.ExportRawRTF = False
    Options.ExportHardBorders = True
    UseUnicode = False
    GridStartRow = 0
    GridStartCol = 0
    Version = '3.13'
    Left = 1304
    Top = 528
  end
  object AdvGridExcelIO2: TAdvGridExcelIO
    AdvStringGrid = sgHist
    Options.ExportOverwriteMessage = 'File %s already exists'#13'Ok to overwrite ?'
    Options.ExportCellFormats = False
    Options.ExportRawRTF = False
    Options.ExportHardBorders = True
    UseUnicode = False
    GridStartRow = 0
    GridStartCol = 0
    Version = '3.13'
    Left = 120
    Top = 841
  end
  object AdvGridExcelIO3: TAdvGridExcelIO
    AdvStringGrid = sgDownload
    Options.ExportOverwriteMessage = 'File %s already exists'#13'Ok to overwrite ?'
    Options.ExportCellFormats = False
    Options.ExportRawRTF = False
    Options.ExportHardBorders = True
    UseUnicode = False
    GridStartRow = 0
    GridStartCol = 0
    Version = '3.13'
    Left = 120
    Top = 841
  end
end
