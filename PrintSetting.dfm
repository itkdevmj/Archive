object frmPrintSetting: TfrmPrintSetting
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsNone
  Caption = #54532#47536#53552' '#49444#51221
  ClientHeight = 410
  ClientWidth = 812
  Color = clWhite
  DoubleBuffered = True
  Font.Charset = HANGEUL_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #44404#47548#52404
  Font.Style = []
  FormStyle = fsMDIForm
  OldCreateOrder = False
  Position = poMainFormCenter
  Scaled = False
  OnClose = FormClose
  OnCreate = frmPrintSetting_OnCreate
  OnDeactivate = FormDeactivate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 12
  object shpBG: TShape
    Left = 0
    Top = 0
    Width = 812
    Height = 410
    Align = alClient
    Brush.Style = bsClear
    Pen.Color = 16750131
    ExplicitHeight = 378
  end
  object panCenter: TPanel
    Left = 1
    Top = 32
    Width = 810
    Height = 375
    BevelOuter = bvNone
    TabOrder = 0
    object imgPrint: TImage
      Left = 792
      Top = 360
      Width = 105
      Height = 105
    end
    object btnPreview: TButton
      Left = 583
      Top = 339
      Width = 100
      Height = 28
      Caption = #51064#49604'('#48120#47532#48372#44592')'
      Font.Charset = HANGEUL_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #44404#47548#52404
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      Visible = False
      OnClick = btnPrint0Click
    end
    object btnPrint0: TButton
      Left = 689
      Top = 339
      Width = 100
      Height = 28
      Caption = #51064' '#49604
      Font.Charset = HANGEUL_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #44404#47548#52404
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = btnPrint0Click
    end
    object btnSaveSetting: TButton
      Left = 495
      Top = 339
      Width = 82
      Height = 28
      Caption = #49444#51221' '#51200#51109
      Font.Charset = HANGEUL_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #44404#47548#52404
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      Visible = False
    end
    object gbCommon: TGroupBox
      Left = 22
      Top = 82
      Width = 211
      Height = 110
      Caption = #53356#44592' '
      TabOrder = 3
      object lblScale: TLabel
        Left = 17
        Top = 67
        Width = 48
        Height = 12
        Caption = #51064#49604#53356#44592
      end
      object lblWidth: TLabel
        Left = 81
        Top = 244
        Width = 30
        Height = 11
        Caption = #45331#51060':'
        Enabled = False
        Font.Charset = HANGEUL_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = #44404#47548#52404
        Font.Style = []
        ParentFont = False
        Visible = False
      end
      object lblHeight: TLabel
        Left = 81
        Top = 264
        Width = 30
        Height = 11
        Caption = #45458#51060':'
        Enabled = False
        Font.Charset = HANGEUL_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = #44404#47548#52404
        Font.Style = []
        ParentFont = False
        Visible = False
      end
      object lblInchW: TLabel
        Left = 178
        Top = 244
        Width = 12
        Height = 11
        Caption = 'cm'
        Enabled = False
        Font.Charset = HANGEUL_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = #44404#47548#52404
        Font.Style = []
        ParentFont = False
        Visible = False
      end
      object lblInchH: TLabel
        Left = 178
        Top = 264
        Width = 12
        Height = 11
        Caption = 'cm'
        Enabled = False
        Font.Charset = HANGEUL_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = #44404#47548#52404
        Font.Style = []
        ParentFont = False
        Visible = False
      end
      object lblPaperType: TLabel
        Left = 16
        Top = 30
        Width = 48
        Height = 12
        Caption = #50857#51648#49440#53469
      end
      object cboPrintScale: TComboBox
        Left = 71
        Top = 62
        Width = 120
        Height = 20
        Style = csDropDownList
        ImeName = 'Microsoft Office IME 2007'
        TabOrder = 0
        OnClick = cboPrintScaleClick
        Items.Strings = (
          #49892#51228' '#53356#44592
          #50857#51648#53356#44592#50640' '#47582#52644
          #51204#52404#48516#54624#52636#47141)
      end
      object edtWidth: TEdit
        Left = 132
        Top = 240
        Width = 40
        Height = 19
        Enabled = False
        Font.Charset = HANGEUL_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = #44404#47548#52404
        Font.Style = []
        ImeName = 'Microsoft Office IME 2007'
        ParentFont = False
        TabOrder = 1
        Text = '297'
        Visible = False
      end
      object edtHeight: TEdit
        Left = 132
        Top = 260
        Width = 40
        Height = 19
        Enabled = False
        Font.Charset = HANGEUL_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = #44404#47548#52404
        Font.Style = []
        ImeName = 'Microsoft Office IME 2007'
        ParentFont = False
        TabOrder = 2
        Text = '210'
        Visible = False
      end
      object cboPaperType: TComboBox
        Left = 70
        Top = 27
        Width = 120
        Height = 20
        Style = csDropDownList
        ImeName = 'Microsoft Office IME 2007'
        TabOrder = 3
        OnClick = cboPaperTypeClick
        Items.Strings = (
          'A4'
          'A3'
          'A2')
      end
    end
    object gbDoc7: TGroupBox
      Left = 239
      Top = 129
      Width = 211
      Height = 65
      Caption = ' '#54224#49604#51648#51201'('#51076#50556')'#46020' '#49436#49885' '#51201#50857' '
      TabOrder = 4
      object chkDoc7Form: TCheckBox
        Left = 27
        Top = 28
        Width = 140
        Height = 17
        Caption = #51648#51201#46020' '#46321#48376' '#52636#47141#50577#49885
        TabOrder = 0
        OnClick = chkDoc7FormClick
      end
    end
    object gbDoc8: TGroupBox
      Left = 239
      Top = 8
      Width = 211
      Height = 106
      Caption = ' '#44396' '#45824' '#51109' '
      TabOrder = 5
      object lblDoc8Page2_1: TLabel
        Left = 28
        Top = 37
        Width = 144
        Height = 12
        Caption = #44396#45824#51109' 2'#51109'(A4) '#48516#54624' '#52636#47141
        OnClick = chkDoc8Page2Click
      end
      object lblDoc8Page2_2: TLabel
        Left = 28
        Top = 50
        Width = 150
        Height = 12
        Caption = #52852#46300#45824#51109' '#50526#46263#47732' '#44057#51060' '#52636#47141
        OnClick = chkDoc8Page2Click
      end
      object chkDoc8Stamp: TCheckBox
        Left = 11
        Top = 77
        Width = 197
        Height = 17
        Caption = #54224#49604'('#53664#51648','#51076#50556')'#45824#51109' '#47928#44396' '#51201#50857
        Checked = True
        State = cbChecked
        TabOrder = 0
        OnClick = chkDoc8StampClick
      end
      object chkDoc8Page2: TCheckBox
        Left = 11
        Top = 41
        Width = 18
        Height = 17
        TabOrder = 1
        OnClick = chkDoc8Page2Click
      end
    end
    object gbPosition: TGroupBox
      Left = 22
      Top = 198
      Width = 211
      Height = 128
      Caption = #50948#52824
      TabOrder = 6
      object lblPositionMent: TLabel
        Left = 16
        Top = 26
        Width = 42
        Height = 12
        Caption = #51221' '#51473#50521
      end
      object pnlPosition: TPanel
        Left = 91
        Top = 21
        Width = 95
        Height = 95
        BevelOuter = bvNone
        TabOrder = 0
        object shpSel: TShape
          Left = 32
          Top = 32
          Width = 32
          Height = 32
          Pen.Color = clRed
        end
        object pnlPos1: TPanel
          Tag = 1
          Left = 2
          Top = 2
          Width = 30
          Height = 30
          BevelInner = bvRaised
          BevelOuter = bvLowered
          Font.Charset = HANGEUL_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = #44404#47548#52404
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          OnClick = pnlPos_OnClick
          object shpPos1: TShape
            Tag = 1
            Left = 1
            Top = 1
            Width = 15
            Height = 15
            Brush.Color = clBlue
            Pen.Color = clBlue
            OnMouseUp = shpPos1_OnMouseUp
          end
        end
        object pnlPos2: TPanel
          Tag = 2
          Left = 33
          Top = 2
          Width = 30
          Height = 30
          BevelInner = bvRaised
          BevelOuter = bvLowered
          TabOrder = 1
          OnClick = pnlPos_OnClick
          object shpPos2: TShape
            Tag = 2
            Left = 8
            Top = 1
            Width = 15
            Height = 15
            Brush.Color = clBlue
            Pen.Color = clBlue
            OnMouseUp = shpPos1_OnMouseUp
          end
        end
        object pnlPos8: TPanel
          Tag = 8
          Left = 33
          Top = 64
          Width = 30
          Height = 30
          BevelInner = bvRaised
          BevelOuter = bvLowered
          TabOrder = 7
          OnClick = pnlPos_OnClick
          object shpPos8: TShape
            Tag = 8
            Left = 8
            Top = 13
            Width = 15
            Height = 15
            Brush.Color = clBlue
            Pen.Color = clBlue
            OnMouseUp = shpPos1_OnMouseUp
          end
        end
        object pnlPos3: TPanel
          Tag = 3
          Left = 64
          Top = 2
          Width = 30
          Height = 30
          BevelInner = bvRaised
          BevelOuter = bvLowered
          TabOrder = 2
          OnClick = pnlPos_OnClick
          object shpPos3: TShape
            Tag = 3
            Left = 13
            Top = 1
            Width = 15
            Height = 15
            Brush.Color = clBlue
            Pen.Color = clBlue
            OnMouseUp = shpPos1_OnMouseUp
          end
        end
        object pnlPos9: TPanel
          Tag = 9
          Left = 64
          Top = 64
          Width = 30
          Height = 30
          BevelInner = bvRaised
          BevelOuter = bvLowered
          TabOrder = 8
          OnClick = pnlPos_OnClick
          object shpPos9: TShape
            Tag = 9
            Left = 13
            Top = 13
            Width = 15
            Height = 15
            Brush.Color = clBlue
            Pen.Color = clBlue
            OnMouseUp = shpPos1_OnMouseUp
          end
        end
        object pnlPos4: TPanel
          Tag = 4
          Left = 2
          Top = 33
          Width = 30
          Height = 30
          BevelInner = bvRaised
          BevelOuter = bvLowered
          TabOrder = 3
          OnClick = pnlPos_OnClick
          object shpPos4: TShape
            Tag = 4
            Left = 1
            Top = 8
            Width = 15
            Height = 15
            Brush.Color = clBlue
            Pen.Color = clBlue
            OnMouseUp = shpPos1_OnMouseUp
          end
        end
        object pnlPos5: TPanel
          Tag = 5
          Left = 33
          Top = 33
          Width = 30
          Height = 30
          BevelInner = bvRaised
          BevelOuter = bvLowered
          TabOrder = 4
          OnClick = pnlPos_OnClick
          object shpPos5: TShape
            Tag = 5
            Left = 8
            Top = 8
            Width = 15
            Height = 15
            Brush.Color = clBlue
            Pen.Color = clBlue
            OnMouseUp = shpPos1_OnMouseUp
          end
        end
        object pnlPos6: TPanel
          Tag = 6
          Left = 64
          Top = 33
          Width = 30
          Height = 30
          BevelInner = bvRaised
          BevelOuter = bvLowered
          TabOrder = 5
          OnClick = pnlPos_OnClick
          object shpPos6: TShape
            Tag = 6
            Left = 13
            Top = 8
            Width = 15
            Height = 15
            Brush.Color = clBlue
            Pen.Color = clBlue
            OnMouseUp = shpPos1_OnMouseUp
          end
        end
        object pnlPos7: TPanel
          Tag = 7
          Left = 2
          Top = 64
          Width = 30
          Height = 30
          BevelInner = bvRaised
          BevelOuter = bvLowered
          TabOrder = 6
          OnClick = pnlPos_OnClick
          object shpPos7: TShape
            Tag = 7
            Left = 1
            Top = 13
            Width = 15
            Height = 15
            Brush.Color = clBlue
            Pen.Color = clBlue
            OnMouseUp = shpPos1_OnMouseUp
          end
        end
      end
    end
    object gbPreview: TGroupBox
      Left = 239
      Top = 208
      Width = 211
      Height = 54
      Caption = ' '#52636#47141' '#54868#47732' '#48372#44592' '#49444#51221' '
      TabOrder = 7
      object chkPreview: TCheckBox
        Left = 27
        Top = 23
        Width = 140
        Height = 17
        Caption = #52636#47141' '#54868#47732' '#54869#51064#54616#44592
        TabOrder = 0
      end
    end
    object gbPrinters: TGroupBox
      Left = 22
      Top = 9
      Width = 211
      Height = 67
      Caption = #54532#47536#53552' '#49440#53469' '
      TabOrder = 8
      object Label2: TLabel
        Left = 81
        Top = 244
        Width = 30
        Height = 11
        Caption = #45331#51060':'
        Enabled = False
        Font.Charset = HANGEUL_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = #44404#47548#52404
        Font.Style = []
        ParentFont = False
        Visible = False
      end
      object Label3: TLabel
        Left = 81
        Top = 264
        Width = 30
        Height = 11
        Caption = #45458#51060':'
        Enabled = False
        Font.Charset = HANGEUL_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = #44404#47548#52404
        Font.Style = []
        ParentFont = False
        Visible = False
      end
      object Label4: TLabel
        Left = 178
        Top = 244
        Width = 12
        Height = 11
        Caption = 'cm'
        Enabled = False
        Font.Charset = HANGEUL_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = #44404#47548#52404
        Font.Style = []
        ParentFont = False
        Visible = False
      end
      object Label5: TLabel
        Left = 178
        Top = 264
        Width = 12
        Height = 11
        Caption = 'cm'
        Enabled = False
        Font.Charset = HANGEUL_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = #44404#47548#52404
        Font.Style = []
        ParentFont = False
        Visible = False
      end
      object Edit1: TEdit
        Left = 132
        Top = 240
        Width = 40
        Height = 19
        Enabled = False
        Font.Charset = HANGEUL_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = #44404#47548#52404
        Font.Style = []
        ImeName = 'Microsoft Office IME 2007'
        ParentFont = False
        TabOrder = 0
        Text = '297'
        Visible = False
      end
      object Edit2: TEdit
        Left = 132
        Top = 260
        Width = 40
        Height = 19
        Enabled = False
        Font.Charset = HANGEUL_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = #44404#47548#52404
        Font.Style = []
        ImeName = 'Microsoft Office IME 2007'
        ParentFont = False
        TabOrder = 1
        Text = '210'
        Visible = False
      end
      object GroupBox3: TGroupBox
        Left = 19
        Top = 150
        Width = 167
        Height = 79
        Caption = ' '#50668#48177'(mm) '
        TabOrder = 2
        object Label7: TLabel
          Left = 10
          Top = 27
          Width = 30
          Height = 12
          Caption = #50812#51901':'
        end
        object Label8: TLabel
          Left = 10
          Top = 53
          Width = 18
          Height = 12
          Caption = #50948':'
        end
        object Label9: TLabel
          Left = 88
          Top = 27
          Width = 42
          Height = 12
          Caption = #50724#47480#51901':'
        end
        object Label10: TLabel
          Left = 88
          Top = 53
          Width = 30
          Height = 12
          Caption = #48148#45797':'
        end
        object Edit3: TEdit
          Left = 46
          Top = 23
          Width = 27
          Height = 20
          ImeName = 'Microsoft Office IME 2007'
          TabOrder = 0
          Text = '0'
        end
        object Edit4: TEdit
          Left = 46
          Top = 49
          Width = 27
          Height = 20
          ImeName = 'Microsoft Office IME 2007'
          TabOrder = 1
          Text = '0'
        end
        object Edit5: TEdit
          Left = 133
          Top = 23
          Width = 24
          Height = 20
          ImeName = 'Microsoft Office IME 2007'
          TabOrder = 2
          Text = '0'
        end
        object Edit6: TEdit
          Left = 133
          Top = 49
          Width = 24
          Height = 20
          ImeName = 'Microsoft Office IME 2007'
          TabOrder = 3
          Text = '0'
        end
      end
      object cboPrinterList: TComboBox
        Left = 10
        Top = 29
        Width = 190
        Height = 20
        Style = csDropDownList
        ImeName = 'Microsoft Office IME 2007'
        TabOrder = 3
        OnChange = cboPrinterListChange
      end
    end
    object gbPrintPreview: TGroupBox
      Left = 478
      Top = 8
      Width = 310
      Height = 320
      Caption = #48120#47532#48372#44592
      Color = clWhite
      ParentBackground = False
      ParentColor = False
      TabOrder = 9
      object pnlPrintPreview: TPanel
        Left = 5
        Top = 15
        Width = 299
        Height = 299
        BevelOuter = bvNone
        Caption = #48120#47532#48372#44592
        TabOrder = 0
        object pnlPaper: TPanel
          Left = 0
          Top = 43
          Width = 299
          Height = 212
          BevelOuter = bvNone
          Color = clWhite
          ParentBackground = False
          TabOrder = 0
          object Shape16: TShape
            Left = 0
            Top = 0
            Width = 299
            Height = 212
            Align = alClient
            ExplicitLeft = 2
            ExplicitTop = 2
            ExplicitWidth = 295
          end
          object pnlPreviewImg: TPanel
            Left = 1
            Top = 1
            Width = 297
            Height = 210
            BevelOuter = bvNone
            Caption = #48120#47532#48372#44592
            TabOrder = 0
            object imgPrintPreview: TImage
              Left = 0
              Top = 0
              Width = 297
              Height = 210
              Align = alClient
              Center = True
              ExplicitHeight = 297
            end
          end
        end
        object pnlPaper2: TPanel
          Left = 43
          Top = 148
          Width = 212
          Height = 149
          BevelOuter = bvNone
          Color = clWhite
          ParentBackground = False
          TabOrder = 1
          Visible = False
          object Shape18: TShape
            Left = 0
            Top = 0
            Width = 212
            Height = 149
            Align = alClient
            ExplicitLeft = 2
            ExplicitTop = 2
            ExplicitWidth = 295
            ExplicitHeight = 212
          end
          object pnlPreviewImg2: TPanel
            Left = 1
            Top = 0
            Width = 210
            Height = 148
            BevelOuter = bvNone
            TabOrder = 0
            object imgPrintPreview2: TImage
              Left = 0
              Top = 0
              Width = 210
              Height = 148
              Align = alClient
              ExplicitLeft = -87
              ExplicitWidth = 297
              ExplicitHeight = 297
            end
          end
        end
        object pnlPaper1: TPanel
          Left = 43
          Top = 0
          Width = 212
          Height = 149
          BevelOuter = bvNone
          Color = clWhite
          ParentBackground = False
          TabOrder = 3
          Visible = False
          object Shape17: TShape
            Left = 0
            Top = 0
            Width = 212
            Height = 149
            Align = alClient
            ExplicitLeft = 2
            ExplicitTop = 2
            ExplicitWidth = 295
            ExplicitHeight = 212
          end
          object pnlPreviewImg1: TPanel
            Left = 1
            Top = 0
            Width = 210
            Height = 148
            BevelOuter = bvNone
            TabOrder = 0
            object imgPrintPreview1: TImage
              Left = 0
              Top = 0
              Width = 210
              Height = 148
              Align = alClient
              ExplicitLeft = -87
              ExplicitWidth = 297
              ExplicitHeight = 297
            end
          end
        end
        object pnlDoc7Form: TPanel
          Left = 45
          Top = 2
          Width = 208
          Height = 295
          BevelOuter = bvNone
          TabOrder = 2
          Visible = False
          object pnlDoc7Form1: TPanel
            Left = 10
            Top = 0
            Width = 192
            Height = 297
            BevelOuter = bvNone
            ParentBackground = False
            TabOrder = 0
            object pnlDoc7Top: TPanel
              Left = 0
              Top = 2
              Width = 192
              Height = 43
              Align = alTop
              BevelOuter = bvNone
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -8
              Font.Name = #48148#53461#52404
              Font.Style = [fsItalic]
              ParentFont = False
              TabOrder = 0
              object Shape1: TShape
                Left = 0
                Top = 0
                Width = 192
                Height = 26
                Align = alTop
              end
              object Shape4: TShape
                Left = 0
                Top = 25
                Width = 25
                Height = 12
              end
              object Shape5: TShape
                Left = 0
                Top = 35
                Width = 25
                Height = 14
              end
              object Shape6: TShape
                Left = 24
                Top = 25
                Width = 32
                Height = 12
              end
              object Shape7: TShape
                Left = 55
                Top = 25
                Width = 25
                Height = 12
              end
              object Shape8: TShape
                Left = 79
                Top = 25
                Width = 34
                Height = 12
              end
              object Shape10: TShape
                Left = 136
                Top = 25
                Width = 56
                Height = 12
              end
              object Shape9: TShape
                Left = 112
                Top = 25
                Width = 25
                Height = 12
              end
              object Shape11: TShape
                Left = 24
                Top = 35
                Width = 89
                Height = 14
              end
              object Shape12: TShape
                Left = 112
                Top = 35
                Width = 25
                Height = 14
              end
              object Shape13: TShape
                Left = 136
                Top = 35
                Width = 23
                Height = 14
              end
              object Shape14: TShape
                Left = 158
                Top = 35
                Width = 14
                Height = 14
              end
              object Shape15: TShape
                Left = 171
                Top = 35
                Width = 21
                Height = 14
              end
              object lblT1: TLabel
                Left = 3
                Top = 27
                Width = 20
                Height = 6
                Caption = #48156#44553#48264#54840
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -5
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object lblT2: TLabel
                Left = 58
                Top = 27
                Width = 20
                Height = 6
                Caption = #52376#47532#49884#44033
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -5
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object lblT3: TLabel
                Left = 115
                Top = 27
                Width = 19
                Height = 6
                Caption = #51089' '#49457' '#51088
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -5
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object lblT4: TLabel
                Left = 3
                Top = 37
                Width = 20
                Height = 6
                Caption = #53664#51648#49548#51116
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -5
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object lblT5: TLabel
                Left = 113
                Top = 37
                Width = 20
                Height = 6
                Caption = #46020#47732#48264#54840
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -5
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object lblT6: TLabel
                Left = 159
                Top = 37
                Width = 10
                Height = 6
                Caption = #52629#52377
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -5
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object lblText1: TLabel
                Left = 30
                Top = 27
                Width = 2
                Height = 6
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -5
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object lblText2: TLabel
                Left = 83
                Top = 27
                Width = 2
                Height = 6
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -5
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object lblText3: TLabel
                Left = 140
                Top = 27
                Width = 2
                Height = 6
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -5
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object lblText4: TLabel
                Left = 30
                Top = 37
                Width = 2
                Height = 6
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -5
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object lblText5: TLabel
                Left = 140
                Top = 37
                Width = 2
                Height = 6
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -5
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object lblText6: TLabel
                Left = 173
                Top = 37
                Width = 2
                Height = 6
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -5
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object lblT0: TLabel
                Left = 50
                Top = 8
                Width = 105
                Height = 11
                Alignment = taCenter
                Caption = #54224#49604' '#51648#51201#46020' '#46321#48376
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = #48148#53461#52404
                Font.Style = [fsBold]
                ParentFont = False
              end
            end
            object pnlDoc7Mid: TPanel
              Left = 0
              Top = 45
              Width = 192
              Height = 212
              Align = alClient
              BevelOuter = bvNone
              TabOrder = 1
              object Shape2: TShape
                Left = 0
                Top = 0
                Width = 192
                Height = 212
                Align = alClient
                ExplicitWidth = 190
                ExplicitHeight = 198
              end
              object pnlDoc7ImgPreview: TPanel
                Left = 1
                Top = 1
                Width = 190
                Height = 210
                BevelOuter = bvNone
                TabOrder = 0
                object imgDoc7Preview: TImage
                  Left = 0
                  Top = 0
                  Width = 190
                  Height = 210
                  Align = alClient
                  ExplicitTop = 1
                end
              end
            end
            object pnlDoc7Bottom: TPanel
              Left = 0
              Top = 257
              Width = 192
              Height = 37
              Align = alBottom
              BevelOuter = bvNone
              TabOrder = 2
              object Shape3: TShape
                Left = 0
                Top = 0
                Width = 192
                Height = 37
                Align = alClient
                ExplicitWidth = 190
                ExplicitHeight = 43
              end
              object lblB1: TLabel
                Left = 36
                Top = 3
                Width = 95
                Height = 8
                Alignment = taCenter
                Caption = #54224#49604' '#51648#51201#46020#50640' '#51032#54616#50668' '#51089#49457#54620' '#46321#48376#51077#45768#45796'.'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -7
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object lblDate: TLabel
                Left = 84
                Top = 11
                Width = 26
                Height = 5
                Caption = '2019'#45380' 4'#50900' 2'#51068
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -4
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
              object lblSidoName: TLabel
                Left = 8
                Top = 17
                Width = 178
                Height = 11
                Alignment = taCenter
                AutoSize = False
                Caption = #48512' '#50668' '#44400' '#49688
                Font.Charset = ANSI_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = #48148#53461#52404
                Font.Style = [fsBold]
                ParentFont = False
              end
              object lblB2: TLabel
                Left = 15
                Top = 27
                Width = 115
                Height = 8
                Alignment = taCenter
                Caption = '('#51060' '#46020#47732' '#46321#48376#51004#47196#45716' '#51648#51201#52769#47049#51012' '#54624' '#49688' '#50630#49845#45768#45796'.)'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -7
                Font.Name = 'Tahoma'
                Font.Style = []
                ParentFont = False
              end
            end
            object pnlDoc7MarginT: TPanel
              Left = 0
              Top = 0
              Width = 192
              Height = 2
              Align = alTop
              BevelOuter = bvNone
              Color = clWhite
              ParentBackground = False
              TabOrder = 3
            end
            object pnlDoc7MarginB: TPanel
              Left = 0
              Top = 294
              Width = 192
              Height = 3
              Align = alBottom
              BevelOuter = bvNone
              Color = clWhite
              ParentBackground = False
              TabOrder = 4
            end
          end
        end
        object palWait: TPanel
          Left = 48
          Top = 140
          Width = 210
          Height = 80
          BevelOuter = bvNone
          Color = clWhite
          ParentBackground = False
          TabOrder = 4
          Visible = False
          object shpWait: TShape
            Left = 0
            Top = 0
            Width = 210
            Height = 80
            Brush.Style = bsClear
            Pen.Color = 16750131
          end
          object lblWait1: TLabel
            Left = 20
            Top = 37
            Width = 126
            Height = 12
            Caption = #51104#49884#47564' '#44592#45796#47140' '#51452#49464#50836'.'
          end
          object lblWait2: TLabel
            Left = 20
            Top = 55
            Width = 150
            Height = 12
            Caption = #49440#53469' '#51089#50629#51012' '#51201#50857#51473#51077#45768#45796'.'
          end
          object pnlWaitT: TPanel
            Left = 1
            Top = 1
            Width = 208
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
          end
        end
      end
    end
    object gbSave: TGroupBox
      Left = 206
      Top = 365
      Width = 211
      Height = 49
      Caption = ' '#51200' '#51109' '
      TabOrder = 10
      Visible = False
      object rbAlways: TRadioButton
        Left = 106
        Top = 20
        Width = 82
        Height = 17
        Caption = #54637#49345' '#51201#50857
        TabOrder = 0
      end
      object rbTemp: TRadioButton
        Left = 14
        Top = 20
        Width = 60
        Height = 17
        Caption = #54620#48264#47564
        Checked = True
        TabOrder = 1
        TabStop = True
      end
    end
    object gbTitle: TGroupBox
      Left = 239
      Top = 272
      Width = 211
      Height = 54
      Caption = ' '#52636#47141' '#51228#47785' '
      TabOrder = 11
      Visible = False
      object edtPrintTitle: TEdit
        Left = 9
        Top = 22
        Width = 194
        Height = 20
        ImeName = 'Microsoft Office IME 2007'
        TabOrder = 0
        OnEnter = edtPrintTitleEnter
      end
    end
    object gbPaperDirect: TGroupBox
      Left = 22
      Top = 168
      Width = 211
      Height = 49
      Caption = ' '#48169#54693' '
      TabOrder = 12
      Visible = False
      object rbLandscape: TRadioButton
        Left = 106
        Top = 20
        Width = 82
        Height = 17
        Caption = #44032#47196
        TabOrder = 0
        OnClick = rbPaperDirectClick
      end
      object rbPortrait: TRadioButton
        Left = 14
        Top = 20
        Width = 60
        Height = 17
        Caption = #49464#47196
        Checked = True
        TabOrder = 1
        TabStop = True
        OnClick = rbPaperDirectClick
      end
    end
  end
  object panWindowsMove: TPanel
    Left = 0
    Top = 0
    Width = 812
    Height = 32
    BevelEdges = [beLeft, beTop, beRight]
    BevelOuter = bvNone
    Color = 16750131
    ParentBackground = False
    TabOrder = 1
    OnMouseDown = panWindowsMoveMouseDown
    object imgIconTitle: TImage
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
      Width = 58
      Height = 14
      Caption = #54532#47536#53552' '#49444#51221
      Font.Charset = ANSI_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = #45208#45588#44256#46357
      Font.Style = [fsBold]
      ParentFont = False
    end
    object btnCloseTypeB: TImage
      Left = 782
      Top = 4
      Width = 22
      Height = 22
      Cursor = crHandPoint
      OnClick = btnCloseTypeBClick
    end
  end
  object pnlPrint: TPanel
    Left = 424
    Top = 305
    Width = 105
    Height = 105
    BevelOuter = bvNone
    Caption = #51064#49604
    TabOrder = 2
    Visible = False
    object Image1: TImage
      Left = 0
      Top = 0
      Width = 105
      Height = 105
      Align = alClient
    end
  end
  object PrinterSetupDialog1: TPrinterSetupDialog
    Left = 312
  end
end
