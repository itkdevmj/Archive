object frmSettingEnv: TfrmSettingEnv
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = #54872#44221#49444#51221
  ClientHeight = 628
  ClientWidth = 260
  Color = clWhite
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
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 14
  object shpBG: TShape
    Left = 0
    Top = 0
    Width = 260
    Height = 628
    Align = alClient
    Brush.Style = bsClear
    Pen.Color = 16750131
    ExplicitLeft = -487
    ExplicitTop = 32
    ExplicitWidth = 747
    ExplicitHeight = 413
  end
  object pnlSettingEnv: TPanel
    Left = 1
    Top = 1
    Width = 258
    Height = 626
    BevelOuter = bvNone
    Color = clWhite
    ParentBackground = False
    TabOrder = 0
    object pnlBlankT1: TPanel
      Left = 0
      Top = 0
      Width = 258
      Height = 10
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 0
      OnMouseDown = pnlBlankT1MouseDown
    end
    object pnlTitle: TPanel
      Left = 0
      Top = 10
      Width = 258
      Height = 40
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 1
      object iconPoi: TImage
        Left = 13
        Top = 0
        Width = 26
        Height = 40
      end
      object imgSettingEnvClose: TImage
        Left = 210
        Top = 14
        Width = 12
        Height = 12
        OnClick = imgSettingEnvCloseClick
      end
      object lblTitle: TLabel
        Left = 45
        Top = 9
        Width = 109
        Height = 21
        Caption = 'LandArchive'
        Font.Charset = HANGEUL_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = #45208#45588#44256#46357
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
    object pnlBlankT2: TPanel
      Left = 0
      Top = 50
      Width = 258
      Height = 10
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 2
    end
    object pnlBlankB1: TPanel
      Left = 0
      Top = 616
      Width = 258
      Height = 10
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 3
    end
    object pnlMain: TPanel
      Left = 1
      Top = 60
      Width = 256
      Height = 556
      BevelEdges = []
      BevelOuter = bvNone
      TabOrder = 4
      object ScrollBox1: TScrollBox
        Left = 0
        Top = 0
        Width = 256
        Height = 556
        HorzScrollBar.Visible = False
        VertScrollBar.Visible = False
        Align = alClient
        BevelInner = bvNone
        BevelOuter = bvNone
        BorderStyle = bsNone
        Color = clWhite
        ParentColor = False
        TabOrder = 0
        OnMouseWheel = ScrollBox1MouseWheel
        object pnlDirect: TPanel
          Left = 0
          Top = 0
          Width = 256
          Height = 120
          Align = alTop
          BevelOuter = bvNone
          TabOrder = 0
          object pnlDirectT: TPanel
            Left = 0
            Top = 0
            Width = 256
            Height = 30
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = '  '#48148#47196#44032#44592
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = #45208#45588#44256#46357
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
            object imgSwitch1: TImage
              Tag = 1
              Left = 66
              Top = 11
              Width = 15
              Height = 10
              Hint = '0'
              OnClick = imgSwitchClick
            end
          end
          object pnlDirectD: TPanel
            Left = 0
            Top = 30
            Width = 256
            Height = 80
            Align = alClient
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = #45208#45588#44256#46357
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 1
            object pnlAbout: TPanel
              Left = 0
              Top = 0
              Width = 256
              Height = 20
              Align = alTop
              BevelOuter = bvNone
              TabOrder = 0
              object pnlAboutT: TPanel
                Left = 0
                Top = 0
                Width = 256
                Height = 20
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 0
                object iconCircle1: TImage
                  Left = 10
                  Top = 5
                  Width = 10
                  Height = 10
                end
                object lblAbout: TLabel
                  Left = 24
                  Top = 3
                  Width = 69
                  Height = 14
                  Cursor = crHandPoint
                  Caption = #54532#47196#44536#47016' '#51221#48372
                  Font.Charset = HANGEUL_CHARSET
                  Font.Color = clBlue
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = [fsUnderline]
                  ParentFont = False
                  OnClick = lblAboutClick
                end
              end
            end
            object pnlRelaseList: TPanel
              Left = 0
              Top = 20
              Width = 256
              Height = 20
              Align = alTop
              BevelOuter = bvNone
              TabOrder = 1
              object pnlRelaseListT: TPanel
                Left = 0
                Top = 0
                Width = 256
                Height = 20
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 0
                object iconCircle2: TImage
                  Left = 10
                  Top = 5
                  Width = 10
                  Height = 10
                end
                object lblReleaseList: TLabel
                  Left = 24
                  Top = 3
                  Width = 116
                  Height = 14
                  Cursor = crHandPoint
                  Caption = #54532#47196#44536#47016' '#50629#45936#51060#53944' '#47785#47197
                  Font.Charset = HANGEUL_CHARSET
                  Font.Color = clBlue
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = [fsUnderline]
                  ParentFont = False
                  OnClick = lblReleaseListClick
                end
              end
            end
            object pnlUserManagement: TPanel
              Left = 0
              Top = 40
              Width = 256
              Height = 20
              Align = alTop
              BevelOuter = bvNone
              TabOrder = 2
              object pnlUserManagementT: TPanel
                Left = 0
                Top = 0
                Width = 256
                Height = 20
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 0
                object iconCircle3: TImage
                  Left = 10
                  Top = 5
                  Width = 10
                  Height = 10
                end
                object lblUserManagement: TLabel
                  Left = 26
                  Top = 3
                  Width = 58
                  Height = 14
                  Cursor = crHandPoint
                  Caption = #49324#50857#51088' '#44288#47532
                  Font.Charset = HANGEUL_CHARSET
                  Font.Color = clBlue
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = [fsUnderline]
                  ParentFont = False
                  OnClick = lblUserManagementClick
                end
              end
            end
            object pnlStat: TPanel
              Left = 0
              Top = 60
              Width = 256
              Height = 54
              Align = alTop
              BevelOuter = bvNone
              TabOrder = 3
              object pnlStatT: TPanel
                Left = 0
                Top = 0
                Width = 256
                Height = 20
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 0
                object iconCircle15: TImage
                  Left = 10
                  Top = 5
                  Width = 10
                  Height = 10
                end
                object lblStat: TLabel
                  Left = 26
                  Top = 3
                  Width = 47
                  Height = 14
                  Cursor = crHandPoint
                  Caption = #53685#44228' '#44288#47532
                  Font.Charset = HANGEUL_CHARSET
                  Font.Color = clBlue
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = [fsUnderline]
                  ParentFont = False
                  OnClick = lblStatClick
                end
              end
            end
          end
          object pnlBlankD: TPanel
            Left = 0
            Top = 110
            Width = 256
            Height = 10
            Align = alBottom
            BevelOuter = bvNone
            Color = clWhite
            ParentBackground = False
            TabOrder = 2
          end
        end
        object pnlSetting: TPanel
          Left = 0
          Top = 120
          Width = 256
          Height = 436
          Align = alClient
          BevelOuter = bvNone
          TabOrder = 1
          object pnlSettingT: TPanel
            Left = 0
            Top = 0
            Width = 256
            Height = 30
            Align = alTop
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Caption = '  '#49444#51221
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = #45208#45588#44256#46357
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
            object imgSwitch2: TImage
              Tag = 2
              Left = 40
              Top = 11
              Width = 15
              Height = 10
              Hint = '0'
              OnClick = imgSwitchClick
            end
          end
          object pnlSettingD: TPanel
            Left = 0
            Top = 30
            Width = 256
            Height = 406
            Align = alClient
            Alignment = taLeftJustify
            BevelOuter = bvNone
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = #45208#45588#44256#46357
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 1
            object pnlDoc02Day: TPanel
              Left = 0
              Top = 540
              Width = 256
              Height = 54
              Align = alTop
              BevelOuter = bvNone
              TabOrder = 0
              Visible = False
              object pnlDoc02DayT: TPanel
                Left = 0
                Top = 0
                Width = 256
                Height = 20
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 0
                object iconCircle4: TImage
                  Left = 10
                  Top = 5
                  Width = 10
                  Height = 10
                end
                object lblDoc02Day: TLabel
                  Left = 24
                  Top = 3
                  Width = 154
                  Height = 14
                  Caption = #52769#47049#44208#44284#46020' '#44160#49353#54364#49884'('#44592#51456#51068#51088')'
                  Font.Charset = HANGEUL_CHARSET
                  Font.Color = clBlue
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = [fsUnderline]
                  ParentFont = False
                end
              end
              object pnlDoc02DayD: TPanel
                Left = 0
                Top = 20
                Width = 256
                Height = 30
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 1
                object pnlDoc02DayB: TPanel
                  Left = 0
                  Top = 0
                  Width = 24
                  Height = 30
                  Align = alLeft
                  BevelOuter = bvNone
                  TabOrder = 0
                end
                object rbDoc02Day1: TRadioButton
                  Tag = 1
                  Left = 24
                  Top = 0
                  Width = 68
                  Height = 30
                  Align = alLeft
                  Caption = #52769#47049#51068#51088
                  Checked = True
                  Font.Charset = ANSI_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  TabOrder = 1
                  TabStop = True
                end
                object rbDoc02Day3: TRadioButton
                  Tag = 3
                  Left = 160
                  Top = 0
                  Width = 68
                  Height = 30
                  Align = alLeft
                  Caption = #44208#51032#51068#51088
                  Font.Charset = ANSI_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  TabOrder = 2
                end
                object rbDoc02Day2: TRadioButton
                  Tag = 2
                  Left = 92
                  Top = 0
                  Width = 68
                  Height = 30
                  Align = alLeft
                  Caption = #44160#49324#51068#51088
                  Font.Charset = ANSI_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  TabOrder = 3
                end
              end
            end
            object pnlLogout: TPanel
              Left = 0
              Top = 0
              Width = 256
              Height = 54
              Align = alTop
              BevelOuter = bvNone
              TabOrder = 1
              object pnlLogoutT: TPanel
                Left = 0
                Top = 0
                Width = 256
                Height = 20
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 0
                object iconCircle5: TImage
                  Left = 10
                  Top = 5
                  Width = 10
                  Height = 10
                end
                object lblLogout: TLabel
                  Left = 24
                  Top = 3
                  Width = 69
                  Height = 14
                  Caption = #47196#44536#50500#50883' '#49444#51221
                  Font.Charset = HANGEUL_CHARSET
                  Font.Color = clBlue
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  OnClick = lblUserManagementClick
                end
              end
              object pnlLogoutD: TPanel
                Left = 0
                Top = 20
                Width = 256
                Height = 30
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 1
                object lblDoc0_V7_lbl1: TLabel
                  Left = 120
                  Top = 9
                  Width = 105
                  Height = 14
                  Caption = #49444#51221' '#49884#44036'             ('#48516')'
                  Font.Charset = ANSI_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                end
                object pnlLogoutB: TPanel
                  Left = 0
                  Top = 0
                  Width = 24
                  Height = 30
                  Align = alLeft
                  BevelOuter = bvNone
                  TabOrder = 0
                end
                object cboLogout: TComboBox
                  Left = 24
                  Top = 4
                  Width = 90
                  Height = 22
                  Cursor = crHandPoint
                  Style = csDropDownList
                  Font.Charset = ANSI_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ImeName = 'Microsoft Office IME 2007'
                  ParentFont = False
                  TabOrder = 1
                  Items.Strings = (
                    #49324#50857#54632
                    #49324#50857#50504#54632)
                end
                object edtLogoutTime: TEdit
                  Left = 171
                  Top = 6
                  Width = 36
                  Height = 22
                  Cursor = crHandPoint
                  Alignment = taCenter
                  Font.Charset = ANSI_CHARSET
                  Font.Color = clBlack
                  Font.Height = -12
                  Font.Name = 'Verdana'
                  Font.Style = []
                  ImeName = 'Microsoft Office IME 2007'
                  MaxLength = 3
                  NumbersOnly = True
                  ParentFont = False
                  TabOrder = 2
                  Text = '10'
                end
              end
            end
            object pnlSearchBar: TPanel
              Left = 0
              Top = 54
              Width = 256
              Height = 54
              Align = alTop
              BevelOuter = bvNone
              TabOrder = 2
              Visible = False
              object pnlSearchBarT: TPanel
                Left = 0
                Top = 0
                Width = 256
                Height = 20
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 0
                object iconCircle6: TImage
                  Left = 10
                  Top = 5
                  Width = 10
                  Height = 10
                end
                object lblSearchBar: TLabel
                  Left = 24
                  Top = 3
                  Width = 58
                  Height = 14
                  Caption = #44160#49353#52285' '#49444#51221
                  Font.Charset = HANGEUL_CHARSET
                  Font.Color = clBlue
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  OnClick = lblUserManagementClick
                end
              end
              object pnlSearchBarD: TPanel
                Left = 0
                Top = 20
                Width = 256
                Height = 30
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 1
                object rbSearchBar1: TRadioButton
                  Tag = 1
                  Left = 24
                  Top = 0
                  Width = 110
                  Height = 30
                  Align = alLeft
                  Caption = #44160#49353#52285' '#53356#44172
                  Checked = True
                  Font.Charset = ANSI_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  TabOrder = 0
                  TabStop = True
                end
                object rbSearchBar2: TRadioButton
                  Tag = 2
                  Left = 134
                  Top = 0
                  Width = 91
                  Height = 30
                  Align = alLeft
                  Caption = #44160#49353#52285' '#51089#44172
                  Font.Charset = ANSI_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  TabOrder = 1
                end
                object pnlSearchBarB: TPanel
                  Left = 0
                  Top = 0
                  Width = 24
                  Height = 30
                  Align = alLeft
                  BevelOuter = bvNone
                  TabOrder = 2
                end
              end
            end
            object pnlViewMode: TPanel
              Left = 0
              Top = 162
              Width = 256
              Height = 54
              Align = alTop
              BevelOuter = bvNone
              TabOrder = 3
              Visible = False
              object pnlViewModeT: TPanel
                Left = 0
                Top = 0
                Width = 256
                Height = 20
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 0
                object iconCircle7: TImage
                  Left = 10
                  Top = 5
                  Width = 10
                  Height = 10
                end
                object lblViewMode: TLabel
                  Left = 24
                  Top = 3
                  Width = 58
                  Height = 14
                  Caption = #44592#48376#48624' '#49444#51221
                  Font.Charset = HANGEUL_CHARSET
                  Font.Color = clBlue
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  OnClick = lblUserManagementClick
                end
              end
              object pnlViewModeD: TPanel
                Left = 0
                Top = 20
                Width = 256
                Height = 30
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 1
                object rbViewMode1: TRadioButton
                  Tag = 1
                  Left = 24
                  Top = 0
                  Width = 110
                  Height = 30
                  Cursor = crHandPoint
                  Align = alLeft
                  Caption = #54637#44277#48624#48372#44592
                  Font.Charset = ANSI_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  TabOrder = 0
                end
                object rbViewMode2: TRadioButton
                  Tag = 2
                  Left = 134
                  Top = 0
                  Width = 91
                  Height = 30
                  Cursor = crHandPoint
                  Align = alLeft
                  Caption = #47928#49436#48372#44592
                  Checked = True
                  Font.Charset = ANSI_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  TabOrder = 1
                  TabStop = True
                end
                object pnlViewModeB: TPanel
                  Left = 0
                  Top = 0
                  Width = 24
                  Height = 30
                  Align = alLeft
                  BevelOuter = bvNone
                  TabOrder = 2
                end
              end
            end
            object pnlAutoJibun: TPanel
              Left = 0
              Top = 216
              Width = 256
              Height = 54
              Align = alTop
              BevelOuter = bvNone
              TabOrder = 4
              object pnlAutoJibunT: TPanel
                Left = 0
                Top = 0
                Width = 256
                Height = 20
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 0
                object iconCircle8: TImage
                  Left = 10
                  Top = 5
                  Width = 10
                  Height = 10
                end
                object lbllAutoJibun: TLabel
                  Left = 24
                  Top = 3
                  Width = 94
                  Height = 14
                  Caption = #51648#48264' '#51088#46041#48320#44221' '#44592#45733
                  Font.Charset = HANGEUL_CHARSET
                  Font.Color = clBlue
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  OnClick = lblUserManagementClick
                end
              end
              object pnlAutoJibunD: TPanel
                Left = 0
                Top = 20
                Width = 256
                Height = 30
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 1
                object rbAutoJibun1: TRadioButton
                  Tag = 1
                  Left = 24
                  Top = 0
                  Width = 110
                  Height = 30
                  Cursor = crHandPoint
                  Align = alLeft
                  Caption = #49324#50857
                  Checked = True
                  Font.Charset = ANSI_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  TabOrder = 0
                  TabStop = True
                end
                object rbAutoJibun2: TRadioButton
                  Tag = 2
                  Left = 134
                  Top = 0
                  Width = 91
                  Height = 30
                  Cursor = crHandPoint
                  Align = alLeft
                  Caption = #49324#50857#50504#54632
                  Font.Charset = ANSI_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  TabOrder = 1
                end
                object pnlAutoJibunB: TPanel
                  Left = 0
                  Top = 0
                  Width = 24
                  Height = 30
                  Align = alLeft
                  BevelOuter = bvNone
                  TabOrder = 2
                end
              end
            end
            object pnlWaterMark: TPanel
              Left = 0
              Top = 486
              Width = 256
              Height = 54
              Align = alTop
              BevelOuter = bvNone
              TabOrder = 5
              object pnlWaterMarkT: TPanel
                Left = 0
                Top = 0
                Width = 256
                Height = 20
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 0
                object iconCircle9: TImage
                  Left = 10
                  Top = 5
                  Width = 10
                  Height = 10
                end
                object lblWaterMark: TLabel
                  Left = 24
                  Top = 3
                  Width = 126
                  Height = 14
                  Caption = #50892#53552#47560#53356' '#54364#49884'('#51200#51109'/'#51064#49604')'
                  Font.Charset = HANGEUL_CHARSET
                  Font.Color = clBlue
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  OnClick = lblUserManagementClick
                end
              end
              object pnlWaterMarkD: TPanel
                Left = 0
                Top = 20
                Width = 256
                Height = 30
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 1
                object rbWaterMark1: TRadioButton
                  Tag = 1
                  AlignWithMargins = True
                  Left = 27
                  Top = 3
                  Width = 110
                  Height = 24
                  Cursor = crHandPoint
                  Align = alLeft
                  Caption = #49324#50857
                  Checked = True
                  Font.Charset = ANSI_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  TabOrder = 0
                  TabStop = True
                end
                object rbWaterMark2: TRadioButton
                  Tag = 2
                  Left = 140
                  Top = 0
                  Width = 91
                  Height = 30
                  Cursor = crHandPoint
                  Align = alLeft
                  Caption = #49324#50857#50504#54632
                  Font.Charset = ANSI_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  TabOrder = 1
                end
                object pnlWaterMarkB: TPanel
                  Left = 0
                  Top = 0
                  Width = 24
                  Height = 30
                  Align = alLeft
                  BevelOuter = bvNone
                  TabOrder = 2
                end
              end
            end
            object pnlViewAir: TPanel
              Left = 0
              Top = 108
              Width = 256
              Height = 54
              Align = alTop
              BevelOuter = bvNone
              TabOrder = 6
              Visible = False
              object pnlViewAirT: TPanel
                Left = 0
                Top = 0
                Width = 256
                Height = 20
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 0
                object iconCircle10: TImage
                  Left = 10
                  Top = 5
                  Width = 10
                  Height = 10
                end
                object lblViewAir: TLabel
                  Left = 24
                  Top = 3
                  Width = 58
                  Height = 14
                  Caption = #54637#44277#48624' '#48372#44592
                  Font.Charset = HANGEUL_CHARSET
                  Font.Color = clBlue
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  OnClick = lblUserManagementClick
                end
              end
              object pnlViewAirD: TPanel
                Left = 0
                Top = 20
                Width = 256
                Height = 30
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 1
                object rbViewAir1: TRadioButton
                  Tag = 1
                  Left = 24
                  Top = 0
                  Width = 110
                  Height = 30
                  Cursor = crHandPoint
                  Align = alLeft
                  Caption = #49324#50857
                  Checked = True
                  Font.Charset = ANSI_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  TabOrder = 0
                  TabStop = True
                end
                object rbViewAir2: TRadioButton
                  Tag = 2
                  Left = 134
                  Top = 0
                  Width = 91
                  Height = 30
                  Cursor = crHandPoint
                  Align = alLeft
                  Caption = #49324#50857#50504#54632
                  Font.Charset = ANSI_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  TabOrder = 1
                end
                object pnlViewAirB: TPanel
                  Left = 0
                  Top = 0
                  Width = 24
                  Height = 30
                  Align = alLeft
                  BevelOuter = bvNone
                  TabOrder = 2
                end
              end
            end
            object pnlOwnLabel: TPanel
              Left = 0
              Top = 324
              Width = 256
              Height = 54
              Align = alTop
              BevelOuter = bvNone
              TabOrder = 7
              Visible = False
              object Panel3: TPanel
                Left = 0
                Top = 20
                Width = 256
                Height = 30
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 0
                object Panel4: TPanel
                  Left = 0
                  Top = 0
                  Width = 24
                  Height = 30
                  Align = alLeft
                  BevelOuter = bvNone
                  TabOrder = 0
                end
                object rbOwnLabel1: TRadioButton
                  Tag = 1
                  Left = 24
                  Top = 0
                  Width = 110
                  Height = 30
                  Cursor = crHandPoint
                  Align = alLeft
                  Caption = #49324#50857
                  Checked = True
                  Font.Charset = ANSI_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  TabOrder = 1
                  TabStop = True
                end
                object rbOwnLabel2: TRadioButton
                  Tag = 2
                  Left = 134
                  Top = 0
                  Width = 91
                  Height = 30
                  Cursor = crHandPoint
                  Align = alLeft
                  Caption = #49324#50857#50504#54632
                  Font.Charset = ANSI_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  TabOrder = 2
                end
              end
              object Panel2: TPanel
                Left = 0
                Top = 0
                Width = 256
                Height = 20
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 1
                object iconCircle11: TImage
                  Left = 10
                  Top = 5
                  Width = 10
                  Height = 10
                end
                object Label2: TLabel
                  Left = 24
                  Top = 3
                  Width = 140
                  Height = 14
                  Caption = #44396#45824#51109'('#48512#52293') '#54620#44544#54364#49884'('#51088#46041')'
                  Font.Charset = HANGEUL_CHARSET
                  Font.Color = clBlue
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  OnClick = lblUserManagementClick
                end
              end
            end
            object pnlAreaFont: TPanel
              Left = 0
              Top = 378
              Width = 256
              Height = 54
              Align = alTop
              BevelOuter = bvNone
              TabOrder = 8
              object pnlAreaFontT: TPanel
                Left = 0
                Top = 0
                Width = 256
                Height = 20
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 0
                object iconCircle12: TImage
                  Left = 10
                  Top = 5
                  Width = 10
                  Height = 10
                end
                object lblAreaFontT: TLabel
                  Left = 24
                  Top = 3
                  Width = 136
                  Height = 14
                  Caption = #52769#51221'('#47732#51201','#44144#47532') '#53581#49828#53944#54364#49884
                  Font.Charset = HANGEUL_CHARSET
                  Font.Color = clBlue
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                end
              end
              object pnlAreaFontD: TPanel
                Left = 0
                Top = 20
                Width = 256
                Height = 30
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 1
                object btnFontColor: TSpeedButton
                  Left = 131
                  Top = 6
                  Width = 55
                  Height = 22
                  Caption = #54256#53944#49353
                  OnClick = btnFontColorClick
                end
                object lblAreaFontColor: TLabel
                  Left = 192
                  Top = 10
                  Width = 33
                  Height = 14
                  Caption = #44032#45208#45796
                  Font.Charset = HANGEUL_CHARSET
                  Font.Color = clBlack
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = [fsBold]
                  ParentFont = False
                end
                object lblAreaFontSize: TLabel
                  Left = 21
                  Top = 10
                  Width = 44
                  Height = 14
                  Caption = #54256#53944#53356#44592
                end
                object lblAreaFont: TPanel
                  Left = 0
                  Top = 0
                  Width = 24
                  Height = 30
                  Align = alLeft
                  BevelOuter = bvNone
                  TabOrder = 0
                end
                object edtAreaFontSize: TEdit
                  Left = 75
                  Top = 6
                  Width = 42
                  Height = 22
                  Alignment = taCenter
                  Font.Charset = ANSI_CHARSET
                  Font.Color = clBlack
                  Font.Height = -12
                  Font.Name = 'Verdana'
                  Font.Style = []
                  ImeName = 'Microsoft Office IME 2007'
                  NumbersOnly = True
                  ParentFont = False
                  TabOrder = 1
                  Text = '14'
                end
              end
            end
            object pnlDoc01Group: TPanel
              Left = 0
              Top = 432
              Width = 256
              Height = 54
              Align = alTop
              BevelOuter = bvNone
              TabOrder = 9
              object pnlDoc01GroupT: TPanel
                Left = 0
                Top = 0
                Width = 256
                Height = 20
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 0
                object iconCircle13: TImage
                  Left = 10
                  Top = 5
                  Width = 10
                  Height = 10
                end
                object lblDoc01Group: TLabel
                  Left = 24
                  Top = 3
                  Width = 102
                  Height = 14
                  Caption = #51060#46041#44208#51032#49436' '#44536#47353#52376#47532
                  Font.Charset = HANGEUL_CHARSET
                  Font.Color = clBlue
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                end
              end
              object pnlDoc01GroupD: TPanel
                Left = 0
                Top = 20
                Width = 256
                Height = 30
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 1
                object pnlDoc01GroupB: TPanel
                  Left = 0
                  Top = 0
                  Width = 24
                  Height = 30
                  Align = alLeft
                  BevelOuter = bvNone
                  TabOrder = 0
                end
                object rbDoc01Group1: TRadioButton
                  Tag = 1
                  Left = 24
                  Top = 0
                  Width = 110
                  Height = 30
                  Cursor = crHandPoint
                  Align = alLeft
                  Caption = #44536#47353'1'#47564' '#52376#47532
                  Checked = True
                  Font.Charset = ANSI_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  TabOrder = 1
                  TabStop = True
                end
                object rbDoc01Group2: TRadioButton
                  Tag = 2
                  Left = 134
                  Top = 0
                  Width = 91
                  Height = 30
                  Cursor = crHandPoint
                  Align = alLeft
                  Caption = #44536#47353'1, 2 '#52376#47532
                  Font.Charset = ANSI_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  TabOrder = 2
                end
              end
            end
            object pnlExpand: TPanel
              Left = 0
              Top = 270
              Width = 256
              Height = 54
              Align = alTop
              BevelOuter = bvNone
              TabOrder = 10
              object pnlExpandT: TPanel
                Left = 0
                Top = 0
                Width = 256
                Height = 20
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 0
                object iconCircle14: TImage
                  Left = 10
                  Top = 5
                  Width = 10
                  Height = 10
                end
                object lblExpand: TLabel
                  Left = 24
                  Top = 3
                  Width = 91
                  Height = 14
                  Caption = #44160#49353#44208#44284#53944#47532' '#49444#51221
                  Font.Charset = HANGEUL_CHARSET
                  Font.Color = clBlue
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                end
              end
              object pnlExpandD: TPanel
                Left = 0
                Top = 20
                Width = 256
                Height = 30
                Align = alTop
                BevelOuter = bvNone
                TabOrder = 1
                object rbExpand1: TRadioButton
                  Tag = 1
                  Left = 24
                  Top = 0
                  Width = 110
                  Height = 30
                  Align = alLeft
                  Caption = #44160#49353#44208#44284' '#54204#52824#44592
                  Checked = True
                  Font.Charset = ANSI_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  TabOrder = 0
                  TabStop = True
                end
                object rbExpand2: TRadioButton
                  Tag = 2
                  Left = 134
                  Top = 0
                  Width = 91
                  Height = 30
                  Align = alLeft
                  Caption = #44160#49353#44208#44284' '#45803#44592
                  Font.Charset = ANSI_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -12
                  Font.Name = #45208#45588#44256#46357
                  Font.Style = []
                  ParentFont = False
                  TabOrder = 1
                end
                object pnlExpandB: TPanel
                  Left = 0
                  Top = 0
                  Width = 24
                  Height = 30
                  Align = alLeft
                  BevelOuter = bvNone
                  TabOrder = 2
                end
              end
            end
          end
        end
      end
    end
  end
  object ColorDialog1: TColorDialog
    Left = 168
    Top = 16
  end
end
