object frmStat: TfrmStat
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsNone
  Caption = #53685#44228#48372#44592
  ClientHeight = 454
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
    Top = 32
    Width = 747
    Height = 422
    Align = alClient
    Brush.Style = bsClear
    Pen.Color = 16750131
    ExplicitTop = 0
    ExplicitWidth = 700
    ExplicitHeight = 394
  end
  object panCenter: TPanel
    Left = 1
    Top = 32
    Width = 745
    Height = 420
    BevelOuter = bvNone
    Color = clWhite
    ParentBackground = False
    TabOrder = 0
    object PageControl1: TPageControl
      Left = 0
      Top = 0
      Width = 745
      Height = 379
      ActivePage = TabSheet3
      Align = alClient
      TabOrder = 0
      OnChange = PageControl1Change
      object TabSheet1: TTabSheet
        Caption = '  '#51648#51201#47928#49436' '#44396#52629#53685#44228'  '
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object pnlTab1: TPanel
          Left = 0
          Top = 0
          Width = 737
          Height = 350
          Align = alClient
          BevelOuter = bvNone
          TabOrder = 0
          object Panel4: TPanel
            Left = 0
            Top = 89
            Width = 6
            Height = 261
            Align = alLeft
            BevelOuter = bvNone
            TabOrder = 0
          end
          object Panel5: TPanel
            Left = 731
            Top = 89
            Width = 6
            Height = 261
            Align = alRight
            BevelOuter = bvNone
            TabOrder = 1
          end
          object pnlFind: TPanel
            Left = 0
            Top = 0
            Width = 737
            Height = 89
            Align = alTop
            BevelEdges = [beBottom]
            BevelOuter = bvNone
            TabOrder = 2
            object IMGFIND: TImage
              Left = 660
              Top = 12
              Width = 71
              Height = 22
              OnClick = IMGFINDClick
              OnMouseEnter = IMGFINDMouseEnter
              OnMouseLeave = IMGFINDMouseLeave
            end
            object gbDoc: TGroupBox
              Left = 8
              Top = 4
              Width = 505
              Height = 80
              Caption = '  '#47928#49436'  '
              TabOrder = 0
              object chkDoc01: TCheckBox
                Left = 12
                Top = 8
                Width = 110
                Height = 24
                Caption = #53664#51648#51060#46041#44208#51032#49436
                Checked = True
                Font.Charset = ANSI_CHARSET
                Font.Color = clBlue
                Font.Height = -12
                Font.Name = #45208#45588#44256#46357
                Font.Style = []
                ParentFont = False
                State = cbChecked
                TabOrder = 0
                Visible = False
              end
              object chkDoc02: TCheckBox
                Left = 20
                Top = 8
                Width = 110
                Height = 24
                Caption = #52769#47049#44208#44284#46020
                Checked = True
                Font.Charset = ANSI_CHARSET
                Font.Color = clBlue
                Font.Height = -12
                Font.Name = #45208#45588#44256#46357
                Font.Style = []
                ParentFont = False
                State = cbChecked
                TabOrder = 1
                Visible = False
              end
              object chkDoc03: TCheckBox
                Left = 28
                Top = 8
                Width = 110
                Height = 24
                Caption = #47732#51201#52769#51221#48512
                Checked = True
                Font.Charset = ANSI_CHARSET
                Font.Color = clBlue
                Font.Height = -12
                Font.Name = #45208#45588#44256#46357
                Font.Style = []
                ParentFont = False
                State = cbChecked
                TabOrder = 2
                Visible = False
              end
              object chkDoc04: TCheckBox
                Left = 36
                Top = 8
                Width = 110
                Height = 24
                Caption = #48512#46041#49328#53945#51312#48277
                Checked = True
                Font.Charset = ANSI_CHARSET
                Font.Color = clBlue
                Font.Height = -12
                Font.Name = #45208#45588#44256#46357
                Font.Style = []
                ParentFont = False
                State = cbChecked
                TabOrder = 3
                Visible = False
              end
              object chkDoc06: TCheckBox
                Left = 44
                Top = 8
                Width = 110
                Height = 24
                Caption = #54872#51648#44228#54925#49436
                Checked = True
                Font.Charset = ANSI_CHARSET
                Font.Color = clBlue
                Font.Height = -12
                Font.Name = #45208#45588#44256#46357
                Font.Style = []
                ParentFont = False
                State = cbChecked
                TabOrder = 4
                Visible = False
              end
              object chkDoc07: TCheckBox
                Left = 52
                Top = 8
                Width = 110
                Height = 24
                Caption = #51333#51060#51648#51201#46020
                Checked = True
                Font.Charset = ANSI_CHARSET
                Font.Color = clBlue
                Font.Height = -12
                Font.Name = #45208#45588#44256#46357
                Font.Style = []
                ParentFont = False
                State = cbChecked
                TabOrder = 5
                Visible = False
              end
              object chkDoc08: TCheckBox
                Left = 60
                Top = 8
                Width = 110
                Height = 24
                Caption = #44396#45824#51109
                Checked = True
                Font.Charset = ANSI_CHARSET
                Font.Color = clBlue
                Font.Height = -12
                Font.Name = #45208#45588#44256#46357
                Font.Style = []
                ParentFont = False
                State = cbChecked
                TabOrder = 6
                Visible = False
              end
              object chkDoc09: TCheckBox
                Left = 68
                Top = 8
                Width = 110
                Height = 24
                Caption = #44277#49884#51648#44032
                Checked = True
                Font.Charset = ANSI_CHARSET
                Font.Color = clBlue
                Font.Height = -12
                Font.Name = #45208#45588#44256#46357
                Font.Style = []
                ParentFont = False
                State = cbChecked
                TabOrder = 7
                Visible = False
              end
              object chkDoc11: TCheckBox
                Left = 100
                Top = 8
                Width = 110
                Height = 24
                Caption = #51648#51201#44221#44228#51221#48708#45824#49345
                Checked = True
                Font.Charset = ANSI_CHARSET
                Font.Color = clBlue
                Font.Height = -12
                Font.Name = #45208#45588#44256#46357
                Font.Style = []
                ParentFont = False
                State = cbChecked
                TabOrder = 8
                Visible = False
              end
              object chkDoc15: TCheckBox
                Left = 76
                Top = 8
                Width = 110
                Height = 24
                Caption = #48708#48277#51064#46321#47197#45824#51109
                Checked = True
                Font.Charset = ANSI_CHARSET
                Font.Color = clBlue
                Font.Height = -12
                Font.Name = #45208#45588#44256#46357
                Font.Style = []
                ParentFont = False
                State = cbChecked
                TabOrder = 9
                Visible = False
              end
              object chkDoc17: TCheckBox
                Left = 84
                Top = 8
                Width = 110
                Height = 24
                Caption = #44592#53440#47928#49436
                Checked = True
                Font.Charset = ANSI_CHARSET
                Font.Color = clBlue
                Font.Height = -12
                Font.Name = #45208#45588#44256#46357
                Font.Style = []
                ParentFont = False
                State = cbChecked
                TabOrder = 10
                Visible = False
              end
              object chkDoc18: TCheckBox
                Left = 92
                Top = 8
                Width = 110
                Height = 24
                Caption = #51340#54364#44228#49328#48512
                Checked = True
                Font.Charset = ANSI_CHARSET
                Font.Color = clBlue
                Font.Height = -12
                Font.Name = #45208#45588#44256#46357
                Font.Style = []
                ParentFont = False
                State = cbChecked
                TabOrder = 11
                Visible = False
              end
            end
            object gbKind: TGroupBox
              Left = 520
              Top = 4
              Width = 130
              Height = 80
              Caption = '  '#51665#44228' '#45824#49345'  '
              TabOrder = 1
              Visible = False
              object chkYearLand: TCheckBox
                Left = 16
                Top = 20
                Width = 110
                Height = 24
                Caption = #45380#46020#48324'/'#51648#50669#48324
                Checked = True
                Font.Charset = ANSI_CHARSET
                Font.Color = clBlue
                Font.Height = -12
                Font.Name = #45208#45588#44256#46357
                Font.Style = []
                ParentFont = False
                State = cbChecked
                TabOrder = 0
              end
              object chkDocKind: TCheckBox
                Left = 16
                Top = 45
                Width = 110
                Height = 24
                Caption = #47928#49436#44396#48516#48324
                Font.Charset = ANSI_CHARSET
                Font.Color = clBlue
                Font.Height = -12
                Font.Name = #45208#45588#44256#46357
                Font.Style = []
                ParentFont = False
                TabOrder = 1
              end
            end
          end
          object sgStat: TAdvStringGrid
            Left = 6
            Top = 89
            Width = 725
            Height = 261
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
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
            ParentFont = False
            ScrollBars = ssBoth
            TabOrder = 3
            GridFixedLineColor = clSilver
            HoverRowCells = [hcNormal, hcSelected]
            OnGetAlignment = sgStatGetAlignment
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
            EnhRowColMove = False
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
            SelectionColor = clWhite
            SortSettings.DefaultFormat = ssAutomatic
            Version = '7.8.4.0'
          end
        end
      end
      object TabSheet2: TTabSheet
        Caption = ' '#49324#50857#51088#48324' '#47928#49436#50676#46988' '#54788#54889
        ImageIndex = 1
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object pnlTab2: TPanel
          Left = 0
          Top = 0
          Width = 737
          Height = 350
          Align = alClient
          BevelOuter = bvNone
          TabOrder = 0
          object Panel10: TPanel
            Left = 0
            Top = 0
            Width = 6
            Height = 350
            Align = alLeft
            BevelOuter = bvNone
            TabOrder = 0
          end
          object Panel11: TPanel
            Left = 731
            Top = 0
            Width = 6
            Height = 350
            Align = alRight
            BevelOuter = bvNone
            TabOrder = 1
          end
          object Panel12: TPanel
            Left = 6
            Top = 0
            Width = 725
            Height = 350
            Align = alClient
            BevelOuter = bvNone
            TabOrder = 2
            object sgStatUserDoc: TAdvStringGrid
              Left = 0
              Top = 89
              Width = 725
              Height = 261
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
              Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect]
              ParentFont = False
              ScrollBars = ssBoth
              TabOrder = 0
              GridFixedLineColor = clSilver
              HoverRowCells = [hcNormal, hcSelected]
              OnGetAlignment = sgStatUserDocGetAlignment
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
              EnhRowColMove = False
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
              FixedFont.Height = -13
              FixedFont.Name = #44404#47548#52404
              FixedFont.Style = [fsBold]
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
              SelectionColor = clWhite
              SortSettings.DefaultFormat = ssAutomatic
              Version = '7.8.4.0'
            end
            object Panel13: TPanel
              Left = 0
              Top = 65
              Width = 725
              Height = 24
              Align = alTop
              BevelOuter = bvNone
              Color = clActiveBorder
              ParentBackground = False
              TabOrder = 1
              object lblStatCnt2: TLabel
                Left = 10
                Top = 6
                Width = 57
                Height = 14
                Caption = #49324#50857#51088' '#49688' : '
              end
              object Label2: TLabel
                Left = 669
                Top = 6
                Width = 51
                Height = 14
                Alignment = taRightJustify
                Caption = '('#45800#50948' : '#44148')'
              end
            end
            object Panel14: TPanel
              Left = 0
              Top = 0
              Width = 725
              Height = 65
              Align = alTop
              BevelEdges = [beBottom]
              BevelOuter = bvNone
              TabOrder = 2
              object IMGFIND2: TImage
                Left = 650
                Top = 20
                Width = 71
                Height = 22
                OnClick = IMGFINDClick
                OnMouseEnter = IMGFINDMouseEnter
                OnMouseLeave = IMGFINDMouseLeave
              end
              object GroupBox4: TGroupBox
                Left = 6
                Top = 4
                Width = 216
                Height = 50
                Caption = '  [ '#50629#47924' '#50976#54805' ]  '
                TabOrder = 0
                object RadioButton1: TRadioButton
                  Left = 18
                  Top = 22
                  Width = 47
                  Height = 17
                  Caption = #50676#46988
                  Checked = True
                  TabOrder = 0
                  TabStop = True
                  Visible = False
                end
                object RadioButton2: TRadioButton
                  Left = 72
                  Top = 22
                  Width = 47
                  Height = 17
                  Caption = #51064#49604
                  TabOrder = 1
                  Visible = False
                end
                object RadioButton3: TRadioButton
                  Left = 126
                  Top = 22
                  Width = 72
                  Height = 17
                  Hint = #54620#44544#54868#54200#51665
                  Caption = #51088#47308' '#48372#51221
                  TabOrder = 2
                  Visible = False
                end
                object CheckBox1: TCheckBox
                  Left = 18
                  Top = 22
                  Width = 47
                  Height = 17
                  Caption = #50676#46988
                  Checked = True
                  State = cbChecked
                  TabOrder = 3
                end
                object CheckBox2: TCheckBox
                  Left = 72
                  Top = 22
                  Width = 47
                  Height = 17
                  Caption = #51064#49604
                  Checked = True
                  State = cbChecked
                  TabOrder = 4
                end
                object CheckBox3: TCheckBox
                  Left = 126
                  Top = 22
                  Width = 70
                  Height = 17
                  Caption = #45796#50868#47196#46300
                  Checked = True
                  State = cbChecked
                  TabOrder = 5
                end
              end
              object GroupBox5: TGroupBox
                Left = 228
                Top = 4
                Width = 215
                Height = 50
                Caption = '  [ '#50676#46988' '#44592#44036' ]  '
                TabOrder = 1
                object Label3: TLabel
                  Left = 99
                  Top = 26
                  Width = 16
                  Height = 14
                  Caption = '  -  '
                end
                object edtEndDt2: TDateTimePicker
                  Left = 117
                  Top = 22
                  Width = 86
                  Height = 20
                  Date = 44013.595247893520000000
                  Time = 44013.595247893520000000
                  TabOrder = 0
                end
                object edtSttDt2: TDateTimePicker
                  Left = 11
                  Top = 22
                  Width = 86
                  Height = 20
                  Date = 44013.595247893520000000
                  Time = 44013.595247893520000000
                  TabOrder = 1
                end
              end
            end
          end
        end
      end
      object TabSheet3: TTabSheet
        Caption = ' '#44396#45824#51109'('#54620#44544#54868') '#50676#46988#53685#44228' '
        ImageIndex = 2
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object pnlTab3: TPanel
          Left = 0
          Top = 0
          Width = 737
          Height = 350
          Align = alClient
          BevelOuter = bvNone
          TabOrder = 0
          object Panel6: TPanel
            Left = 0
            Top = 0
            Width = 6
            Height = 350
            Align = alLeft
            BevelOuter = bvNone
            TabOrder = 0
          end
          object Panel7: TPanel
            Left = 731
            Top = 0
            Width = 6
            Height = 350
            Align = alRight
            BevelOuter = bvNone
            TabOrder = 1
          end
          object Panel1: TPanel
            Left = 6
            Top = 0
            Width = 725
            Height = 350
            Align = alClient
            BevelOuter = bvNone
            TabOrder = 2
            object sgStatDoc8: TAdvStringGrid
              Left = 0
              Top = 89
              Width = 725
              Height = 261
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
              Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect]
              ParentFont = False
              ScrollBars = ssBoth
              TabOrder = 0
              GridFixedLineColor = clSilver
              HoverRowCells = [hcNormal, hcSelected]
              OnGetAlignment = sgStatGetAlignment
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
              EnhRowColMove = False
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
              FixedFont.Height = -13
              FixedFont.Name = #44404#47548#52404
              FixedFont.Style = [fsBold]
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
              SelectionColor = clWhite
              SortSettings.DefaultFormat = ssAutomatic
              Version = '7.8.4.0'
            end
            object Panel9: TPanel
              Left = 0
              Top = 65
              Width = 725
              Height = 24
              Align = alTop
              BevelOuter = bvNone
              Color = clActiveBorder
              ParentBackground = False
              TabOrder = 1
              object lblStatCnt: TLabel
                Left = 10
                Top = 6
                Width = 48
                Height = 14
                Caption = #51312#54924#44148#49688':'
              end
            end
            object Panel8: TPanel
              Left = 0
              Top = 0
              Width = 725
              Height = 65
              Align = alTop
              BevelEdges = [beBottom]
              BevelOuter = bvNone
              TabOrder = 2
              object IMGFIND3: TImage
                Left = 650
                Top = 20
                Width = 71
                Height = 22
                OnClick = IMGFINDClick
                OnMouseEnter = IMGFINDMouseEnter
                OnMouseLeave = IMGFINDMouseLeave
              end
              object GroupBox1: TGroupBox
                Left = 6
                Top = 4
                Width = 216
                Height = 50
                Caption = '  [ '#50629#47924' '#50976#54805' ]  '
                TabOrder = 0
                object rbView: TRadioButton
                  Left = 18
                  Top = 22
                  Width = 47
                  Height = 17
                  Caption = #50676#46988
                  Checked = True
                  TabOrder = 0
                  TabStop = True
                  Visible = False
                end
                object rbPrint: TRadioButton
                  Left = 72
                  Top = 22
                  Width = 47
                  Height = 17
                  Caption = #51064#49604
                  TabOrder = 1
                  Visible = False
                end
                object rbDirect: TRadioButton
                  Left = 126
                  Top = 22
                  Width = 72
                  Height = 17
                  Hint = #54620#44544#54868#54200#51665
                  Caption = #51088#47308' '#48372#51221
                  TabOrder = 2
                  Visible = False
                end
                object chkView: TCheckBox
                  Left = 18
                  Top = 22
                  Width = 47
                  Height = 17
                  Caption = #50676#46988
                  Checked = True
                  State = cbChecked
                  TabOrder = 3
                end
                object chkPrint: TCheckBox
                  Left = 72
                  Top = 22
                  Width = 47
                  Height = 17
                  Caption = #51064#49604
                  Checked = True
                  State = cbChecked
                  TabOrder = 4
                end
                object chkDirect: TCheckBox
                  Left = 126
                  Top = 22
                  Width = 70
                  Height = 17
                  Caption = #51088#47308' '#48372#51221
                  TabOrder = 5
                end
              end
              object GroupBox2: TGroupBox
                Left = 228
                Top = 4
                Width = 215
                Height = 50
                Caption = '  [ '#50629#47924' '#44592#44036' ]  '
                TabOrder = 1
                object Label1: TLabel
                  Left = 99
                  Top = 26
                  Width = 16
                  Height = 14
                  Caption = '  -  '
                end
                object edtSEndDt: TDateTimePicker
                  Left = 117
                  Top = 22
                  Width = 86
                  Height = 20
                  Date = 44013.595247893520000000
                  Time = 44013.595247893520000000
                  TabOrder = 0
                end
                object edtSSttDt: TDateTimePicker
                  Left = 11
                  Top = 22
                  Width = 86
                  Height = 20
                  Date = 44013.595247893520000000
                  Time = 44013.595247893520000000
                  TabOrder = 1
                end
              end
              object GroupBox3: TGroupBox
                Left = 449
                Top = 4
                Width = 194
                Height = 50
                Caption = '  [ '#53685#44228' '#45824#49345' ]   '
                TabOrder = 2
                object cboSUmd: TbsSkinComboBox
                  Left = 43
                  Top = 33
                  Width = 113
                  Height = 20
                  HintImageIndex = 0
                  TabOrder = 0
                  Visible = False
                  SkinDataName = 'combobox'
                  DefaultFont.Charset = HANGEUL_CHARSET
                  DefaultFont.Color = clBlack
                  DefaultFont.Height = -13
                  DefaultFont.Name = #45208#45588#48148#47480#44256#46357
                  DefaultFont.Style = []
                  DefaultWidth = 0
                  DefaultHeight = 0
                  UseSkinFont = False
                  UseSkinSize = False
                  ToolButtonStyle = False
                  AlphaBlend = False
                  AlphaBlendValue = 0
                  AlphaBlendAnimation = False
                  ListBoxCaptionMode = False
                  ListBoxDefaultFont.Charset = HANGEUL_CHARSET
                  ListBoxDefaultFont.Color = clWindowText
                  ListBoxDefaultFont.Height = -12
                  ListBoxDefaultFont.Name = #44404#47548#52404#52404
                  ListBoxDefaultFont.Style = []
                  ListBoxDefaultCaptionFont.Charset = HANGEUL_CHARSET
                  ListBoxDefaultCaptionFont.Color = clWindowText
                  ListBoxDefaultCaptionFont.Height = -12
                  ListBoxDefaultCaptionFont.Name = #44404#47548#52404#52404
                  ListBoxDefaultCaptionFont.Style = []
                  ListBoxDefaultItemHeight = 20
                  ListBoxCaptionAlignment = taLeftJustify
                  ListBoxUseSkinFont = False
                  ListBoxUseSkinItemHeight = False
                  ListBoxWidth = 0
                  HideSelection = True
                  AutoComplete = True
                  ImageIndex = -1
                  CharCase = ecNormal
                  DefaultColor = clWindow
                  ItemIndex = -1
                  DropDownCount = 40
                  HorizontalExtent = False
                  Font.Charset = HANGEUL_CHARSET
                  Font.Color = clBlack
                  Font.Height = -12
                  Font.Name = #44404#47548#52404
                  Font.Style = []
                  Sorted = False
                  Style = bscbFixedStyle
                  OnChange = cboSUmdChange
                end
                object edtSUmdCd: TEdit
                  Left = 157
                  Top = 33
                  Width = 48
                  Height = 22
                  Alignment = taCenter
                  NumbersOnly = True
                  TabOrder = 1
                  Visible = False
                end
                object rbUser: TRadioButton
                  Left = 18
                  Top = 22
                  Width = 80
                  Height = 17
                  Caption = #49324#50857#51088#48324
                  Checked = True
                  TabOrder = 2
                  TabStop = True
                end
                object rbUmd: TRadioButton
                  Left = 100
                  Top = 22
                  Width = 80
                  Height = 17
                  Caption = #51021#47732#46041#48324
                  TabOrder = 3
                end
              end
            end
            object sgStatDoc8Save: TAdvStringGrid
              Left = 800
              Top = 0
              Width = 704
              Height = 257
              Cursor = crDefault
              DefaultRowHeight = 20
              DrawingStyle = gdsClassic
              RowCount = 16
              Font.Charset = HANGEUL_CHARSET
              Font.Color = clWindowText
              Font.Height = -12
              Font.Name = #44404#47548#52404
              Font.Style = []
              Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect]
              ParentFont = False
              ScrollBars = ssBoth
              TabOrder = 3
              GridFixedLineColor = clSilver
              HoverRowCells = [hcNormal, hcSelected]
              OnGetAlignment = sgStatGetAlignment
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
              EnhRowColMove = False
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
              FixedFont.Height = -13
              FixedFont.Name = #44404#47548#52404
              FixedFont.Style = [fsBold]
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
              SelectionColor = clWhite
              SortSettings.DefaultFormat = ssAutomatic
              Version = '7.8.4.0'
            end
          end
        end
      end
      object TabSheet4: TTabSheet
        Caption = '  '#51021#47732#46041#48324' '#44396#52629#53685#44228'  '
        ImageIndex = 3
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object Panel2: TPanel
          Left = 0
          Top = 0
          Width = 737
          Height = 350
          Align = alClient
          BevelOuter = bvNone
          TabOrder = 0
          object Panel15: TPanel
            Left = 0
            Top = 0
            Width = 6
            Height = 350
            Align = alLeft
            BevelOuter = bvNone
            TabOrder = 0
          end
          object Panel16: TPanel
            Left = 731
            Top = 0
            Width = 6
            Height = 350
            Align = alRight
            BevelOuter = bvNone
            TabOrder = 1
          end
          object Panel17: TPanel
            Left = 6
            Top = 0
            Width = 725
            Height = 350
            Align = alClient
            BevelOuter = bvNone
            TabOrder = 2
            object sgStatDoc: TAdvStringGrid
              Left = 0
              Top = 89
              Width = 725
              Height = 261
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
              Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect]
              ParentFont = False
              ScrollBars = ssBoth
              TabOrder = 0
              GridFixedLineColor = clSilver
              HoverRowCells = [hcNormal, hcSelected]
              OnGetAlignment = sgStatDocGetAlignment
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
              EnhRowColMove = False
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
              FixedFont.Height = -13
              FixedFont.Name = #44404#47548#52404
              FixedFont.Style = [fsBold]
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
              SelectionColor = clWhite
              SortSettings.DefaultFormat = ssAutomatic
              Version = '7.8.4.0'
            end
            object Panel18: TPanel
              Left = 0
              Top = 65
              Width = 725
              Height = 24
              Align = alTop
              BevelOuter = bvNone
              Color = clActiveBorder
              ParentBackground = False
              TabOrder = 1
              object lblStatCnt4: TLabel
                Left = 10
                Top = 6
                Width = 57
                Height = 14
                Caption = #51021#47732#46041' '#49688' : '
              end
              object lblUnit: TLabel
                Left = 669
                Top = 6
                Width = 51
                Height = 14
                Alignment = taRightJustify
                Caption = '('#45800#50948' : '#44148')'
              end
            end
            object Panel19: TPanel
              Left = 0
              Top = 0
              Width = 725
              Height = 65
              Align = alTop
              BevelEdges = [beBottom]
              BevelOuter = bvNone
              TabOrder = 2
              object IMGFIND4: TImage
                Left = 650
                Top = 20
                Width = 71
                Height = 22
                OnClick = IMGFINDClick
                OnMouseEnter = IMGFINDMouseEnter
                OnMouseLeave = IMGFINDMouseLeave
              end
              object GroupBox6: TGroupBox
                Left = 6
                Top = 4
                Width = 216
                Height = 50
                Caption = '  [ '#44396#52629' '#45936#51060#53552' '#50976#54805' ]  '
                TabOrder = 0
                object rbUmdPath: TRadioButton
                  Left = 18
                  Top = 22
                  Width = 80
                  Height = 17
                  Caption = #47928#49436' '#47732#49688
                  Checked = True
                  TabOrder = 0
                  TabStop = True
                end
                object rbUmdRecord: TRadioButton
                  Left = 120
                  Top = 22
                  Width = 80
                  Height = 17
                  Caption = #45936#51060#53552' '#44148#49688
                  TabOrder = 1
                end
              end
            end
          end
        end
      end
    end
    object Panel3: TPanel
      Left = 0
      Top = 379
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
    TabOrder = 1
    OnMouseDown = panWindowsMoveMouseDown
    object lblFormTitle: TLabel
      Left = 14
      Top = 9
      Width = 44
      Height = 14
      Caption = #53685#44228#48372#44592
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
      PngImageList = frmMain.bsPngImageList6
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
      Top = 0
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
      object lblCnt: TLabel
        Left = 210
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
    Left = 680
    Top = 64
  end
  object AdvGridExcelIO1: TAdvGridExcelIO
    AdvStringGrid = sgStat
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
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 344
    Top = 528
  end
  object AdvGridExcelIO2: TAdvGridExcelIO
    AdvStringGrid = sgStatDoc8Save
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
  object AdvGridExcelIO3: TAdvGridExcelIO
    AdvStringGrid = sgStatUserDoc
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
  object AdvGridExcelIO4: TAdvGridExcelIO
    AdvStringGrid = sgStatDoc
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
  object ADOConnection1: TADOConnection
    Left = 456
    Top = 560
  end
  object ADOQuery1: TADOQuery
    Connection = ADOConnection1
    Parameters = <>
    Left = 464
    Top = 568
  end
end
