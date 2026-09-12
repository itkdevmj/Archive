//---------------------------------------------------------------------------

#ifndef PrintSettingH
#define PrintSettingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <JPEG.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
#include "GR32_RangeBars.hpp"
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <pngimage.hpp>
#include "bsPngImageList.hpp"
//---------------------------------------------------------------------------
class TfrmPrintSetting : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *gbDoc8;
	TCheckBox *chkDoc8Stamp;
	TCheckBox *chkDoc8Page2;
	TGroupBox *gbSave;
	TRadioButton *rbAlways;
	TRadioButton *rbTemp;
	TButton *btnSaveSetting;
	TGroupBox *gbCommon;
	TLabel *lblScale;
	TLabel *lblWidth;
	TLabel *lblHeight;
	TLabel *lblInchW;
	TLabel *lblInchH;
	TComboBox *cboPrintScale;
	TEdit *edtWidth;
	TEdit *edtHeight;
	TGroupBox *gbPosition;
	TPanel *pnlPosition;
	TPanel *pnlPos1;
	TShape *shpPos1;
	TPanel *pnlPos2;
	TShape *shpPos2;
	TPanel *pnlPos8;
	TShape *shpPos8;
	TPanel *pnlPos3;
	TShape *shpPos3;
	TPanel *pnlPos9;
	TShape *shpPos9;
	TPanel *pnlPos4;
	TShape *shpPos4;
	TPanel *pnlPos5;
	TShape *shpPos5;
	TPanel *pnlPos6;
	TShape *shpPos6;
	TPanel *pnlPos7;
	TShape *shpPos7;
	TShape *shpSel;
	TLabel *lblPositionMent;
	TGroupBox *gbDoc7;
	TCheckBox *chkDoc7Form;
	TLabel *lblDoc8Page2_1;
	TLabel *lblDoc8Page2_2;
	TButton *btnPrint0;
	TLabel *lblPaperType;
	TComboBox *cboPaperType;
	TGroupBox *gbPrintPreview;
	TImage *imgPrintPreview;
	TPanel *pnlPrintPreview;
	TPanel *pnlPaper;
	TImage *imgPrintPreview2;
	TPanel *pnlPaper2;
	TPanel *pnlDoc7Form;
	TPanel *pnlDoc7Form1;
	TPanel *pnlDoc7Top;
	TShape *Shape1;
	TShape *Shape4;
	TShape *Shape5;
	TShape *Shape6;
	TShape *Shape7;
	TShape *Shape8;
	TShape *Shape10;
	TShape *Shape9;
	TShape *Shape11;
	TShape *Shape12;
	TShape *Shape13;
	TShape *Shape14;
	TShape *Shape15;
	TLabel *lblT1;
	TLabel *lblT2;
	TLabel *lblT3;
	TLabel *lblT4;
	TLabel *lblT5;
	TLabel *lblT6;
	TLabel *lblText1;
	TLabel *lblText2;
	TLabel *lblText3;
	TLabel *lblText4;
	TLabel *lblText5;
	TLabel *lblText6;
	TLabel *lblT0;
	TPanel *pnlDoc7Mid;
	TShape *Shape2;
	TPanel *pnlDoc7ImgPreview;
	TImage *imgDoc7Preview;
	TPanel *pnlDoc7Bottom;
	TShape *Shape3;
	TLabel *lblB1;
	TLabel *lblDate;
	TLabel *lblSidoName;
	TLabel *lblB2;
	TPanel *pnlDoc7MarginT;
	TPanel *pnlDoc7MarginB;
	TPanel *pnlPaper1;
	TImage *imgPrintPreview1;
	TShape *Shape16;
	TShape *Shape17;
	TShape *Shape18;
	TPanel *pnlPreviewImg;
	TPanel *pnlPreviewImg1;
	TPanel *pnlPreviewImg2;
	TGroupBox *gbPreview;
	TCheckBox *chkPreview;
	TGroupBox *gbPrinters;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *Edit1;
	TEdit *Edit2;
	TGroupBox *GroupBox3;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TEdit *Edit3;
	TEdit *Edit4;
	TEdit *Edit5;
	TEdit *Edit6;
	TComboBox *cboPrinterList;
	TPrinterSetupDialog *PrinterSetupDialog1;
	TGroupBox *gbTitle;
	TEdit *edtPrintTitle;
	TButton *btnPreview;
	TPanel *panCenter;
	TPanel *panWindowsMove;
	TImage *imgIconTitle;
	TLabel *lblFormTitle;
	TImage *btnCloseTypeB;
	TShape *shpBG;
	TImage *imgPrint;
	TGroupBox *gbPaperDirect;
	TRadioButton *rbLandscape;
	TRadioButton *rbPortrait;
	TPanel *pnlPrint;
	TImage *Image1;
	TPanel *palWait;
	TShape *shpWait;
	TLabel *lblWait1;
	TLabel *lblWait2;
	TPanel *pnlWaitT;
	void __fastcall frmPrintSetting_OnCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btnPrint0Click(TObject *Sender);
	void __fastcall pnlPos_OnClick(TObject *Sender);
	void __fastcall shpPos1_OnMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall chkDoc7FormClick(TObject *Sender);
	void __fastcall cboPaperTypeClick(TObject *Sender);
	void __fastcall cboPrintScaleClick(TObject *Sender);
	void __fastcall chkDoc8Page2Click(TObject *Sender);
	void __fastcall chkDoc8StampClick(TObject *Sender);
	void __fastcall cboPrinterListChange(TObject *Sender);
	void __fastcall edtPrintTitleEnter(TObject *Sender);
	void __fastcall FormDeactivate(TObject *Sender);
	void __fastcall btnCloseTypeBClick(TObject *Sender);
	void __fastcall panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall rbPaperDirectClick(TObject *Sender);

private:	// User declarations

	//****************************************************************
	// FREE IMAGE
	//****************************************************************
	//################################################################
	HDC 				memDCDoc;
	HDC 				pDCDoc;
	HGDIOBJ 			pObjDoc;
	HBRUSH 				hbrDoc;
	HBITMAP 			hMembitmapDoc;
	HBITMAP 			hOldBitmapDoc;


	int	nPosition;
	int nFlag;
	TStringList *m_sPrinterList;
	TPrinter *m_pPrinter;
	TStringList *m_sPaperTypeList;
	PAPER_SIZE_STRUCT stPaperSize;


	void __fastcall funcSetPosPanelCaption(int _nPos);
	void __fastcall funcSetPosPanelShpSel(int _nPos);
public:		// User declarations

	vector<DOGAKLINE_STRUCT> m_vDOGAKLINE_Bck;


	vector<PRINT_SETTING_STRUCT> mSetPrint;//Minji_#02_B_Print

	bool clearCode;
	int printrate;

	bool bDBSetValue;//from db value?
	bool bFromShow;//FormShow 할때만 수행
	bool bDoc8Card;//구대장-카드(false이면 부책)

//	int nBmp32Width;
//	int nBmp32Height;

	Graphics::TBitmap  	*bmpLoad;

	int    nWidth;//원본 이미지 사이즈 //frmMain->mGetImageInfo.nImageWidth
	int    nHeight;//원본 이미지 사이즈//frmMain->mGetImageInfo.nImageHeight
	int    nPaperW;//용지크기//
	int    nPaperH;//용지크기//
	int    nImgmmW;//이미지를 mm 단위로 환산
	int    nImgmmH;//이미지를 mm 단위로 환산
	double dMMtoPixelW;
	double dMMtoPixelH;
	double dResolRate;//해상도 / 100 (72, 96, 100, 200, 300)
	double dRatio;

	AnsiString m_asPRINTDIR;

	AnsiString m_asOrientation;//"L", "P"

	int 	nDocNo;
	int 	nCurImagePaperType;//현재 선택된 이미지의 용지 사이즈//A4(0), A3(1), A2(2)


	Doc07CopyInfo mDoc07CopyInfo;


	void __fastcall funcSetWaitWindows(bool bSetValue);//201223//

	void __fastcall funcFastReportOpen(char *_cParameters, int _nType);
	void __fastcall funcCopyInfoToDb();
	int  __fastcall funcDbToCopyNoIndex(char *_cDate);
	void __fastcall funcAddSiGunTitle(char *_cBuff);

	void __fastcall funcPrintSettingFitAll();
	void __fastcall funcPrintSettingRealPart(bool _bAll);
	void __fastcall funcPrintSettingDoc0Group(AnsiString _asPrtFilePath);//181022
	void __fastcall funcWriteIniData();

	int  __fastcall funcQryInsertPrint(int _nType);
	bool __fastcall funcQrySelectPrint();
	void __fastcall funcSaveSetting();
	void __fastcall funcGetDBValue();
	void __fastcall funcSetDBValue();
	void __fastcall funcDeleteTempFile();


	//카드대장 앞면 혹은 뒷면 다운로드 후 이미지 편집 시 사용//
	FIBITMAP* 			i_DIB;
	BITMAPINFO*			mBitMapInfo;
	AnsiString __fastcall funcDownloadImage(bool _bPrint, AnsiString _asFullPath);
	void __fastcall funcResaveImage(AnsiString _asFilePath, int _nIndex, bool _bPreview);
	void __fastcall funcResizeDownloadImage(AnsiString _asFilePath, int _nIndex);
	//void __fastcall funcSaveTempFile();

	void __fastcall funcDogakLinePaint();

	Graphics::TBitmap *IMGMAPPOINT;//지번표시 텍스트 > 인쇄 적용
	void __fastcall funcMapPointPaint();//지번표시 텍스트 > 인쇄

	void __fastcall funcCreatePreviewImg();
	void __fastcall funcGetPrinterList();//프린터 목록 가져오기
	int  __fastcall funcGetPaperSize(void);//프린터 용지 목록//
	void __fastcall funcSetPaperSize(int pSize);
	void __fastcall funcGetPrintSetting();
	void __fastcall funcSetPrintSetting();
	int  __fastcall funcGetBasicPrinter(AnsiString _asPrinterName);
	AnsiString __fastcall funcSetBasicPrinter(int _nIndex);
	int  __fastcall funcGetPaperIndex(int _nPaperSize);
	int  __fastcall funcSetPaperIndex(int _nIndex);

	void __fastcall funcGetPrintPreview();
	void __fastcall funcPreviewPrintDoc8();
	void __fastcall funcFilePreview(AnsiString _asPrintFile);
	void __fastcall funcCopyInfoToDbPreview();
	void __fastcall funcRectanglePreview(AnsiString _asPrintFile);
	void __fastcall funcPreviewPrintDoc8Page2Card(AnsiString _asPrintFile, bool _bFirstPage, bool _bDownload);
	void __fastcall funcPreviewPrintDoc8Page2Etc(AnsiString _asPrintFile1, AnsiString _asPrintFile2);
	void __fastcall funcSetPreviewPage(bool _bLandscape);
	void __fastcall funcSetPreviewPageDoc8Page2(bool _bLandscape);

	//인쇄크기 설정//
	void __fastcall funcSetPrintScale();//200829//
	//전체분할인쇄//
	void __fastcall funcFileAllPart();//200829//


	//=======================================================================
	FIBITMAP* printDIB;
	void __fastcall funcDrawWaterMark();
	void __fastcall funcDrawDoc8Stamp(AnsiString _asPrintFile);
	//=======================================================================



	__fastcall TfrmPrintSetting(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmPrintSetting *frmPrintSetting;
//---------------------------------------------------------------------------
#endif
