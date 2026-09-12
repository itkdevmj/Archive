#pragma link "bsPngImageList"
#pragma link "GR32_RangeBars"
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//해당 경고 없애기, W8057, W8004
#pragma warn -8057
#pragma warn -8004
#pragma warn -8018

TfrmPrintSetting *frmPrintSetting;
//---------------------------------------------------------------------------
//[Paper Sizes]
//https://docs.microsoft.com/en-us/windows/desktop/intl/paper-sizes
/*

[Type]	[Value]	 [Meaning]
DMPAPER_LETTER 1 US Letter 8 1/2 x 11 in
DMPAPER_LETTERSMALL 2 US Letter Small 8 1/2 x 11 in
DMPAPER_TABLOID 3 US Tabloid 11 x 17 in
DMPAPER_LEDGER 4 US Ledger 17 x 11 in
DMPAPER_LEGAL 5 US Legal 8 1/2 x 14 in
DMPAPER_STATEMENT 6 US Statement 5 1/2 x 8 1/2 in
DMPAPER_EXECUTIVE 7 US Executive 7 1/4 x 10 1/2 in
DMPAPER_A3 8 A3 297 x 420 mm
DMPAPER_A4 9 A4 210 x 297 mm
DMPAPER_A4SMALL 10 A4 Small 210 x 297 mm
DMPAPER_A5 11 A5 148 x 210 mm
DMPAPER_B4 12 B4 (JIS) 257 x 364 mm
DMPAPER_B5 13 B5 (JIS) 182 x 257 mm
DMPAPER_FOLIO 14 Folio 8 1/2 x 13 in
DMPAPER_QUARTO 15 Quarto 215 x 275 mm
DMPAPER_10X14 16 10 x 14 in
DMPAPER_11X17 17 11 x 17 in
DMPAPER_NOTE 18 US Note 8 1/2 x 11 in
DMPAPER_ENV_9 19 US Envelope #9 3 7/8 x 8 7/8
DMPAPER_ENV_10 20 US Envelope #10 4 1/8 x 9 1/2
DMPAPER_ENV_11 21 US Envelope #11 4 1/2 x 10 3/8
DMPAPER_ENV_12 22 US Envelope #12 4 3/4 x 11 in
DMPAPER_ENV_14 23 US Envelope #14 5 x 11 1/2
DMPAPER_CSHEET 24 C size sheet
DMPAPER_DSHEET 25 D size sheet
DMPAPER_ESHEET 26 E size sheet
DMPAPER_ENV_DL 27 Envelope DL 110 x 220mm
DMPAPER_ENV_C5 28 Envelope C5 162 x 229 mm
DMPAPER_ENV_C3 29 Envelope C3 324 x 458 mm
DMPAPER_ENV_C4 30 Envelope C4 229 x 324 mm
DMPAPER_ENV_C6 31 Envelope C6 114 x 162 mm
DMPAPER_ENV_C65 32 Envelope C65 114 x 229 mm
DMPAPER_ENV_B4 33 Envelope B4 250 x 353 mm
DMPAPER_ENV_B5 34 Envelope B5 176 x 250 mm
DMPAPER_ENV_B6 35 Envelope B6 176 x 125 mm
DMPAPER_ENV_ITALY 36 Envelope 110 x 230 mm
DMPAPER_ENV_MONARCH 37 US Envelope Monarch 3.875 x 7.5 in
DMPAPER_ENV_PERSONAL 38 6 3/4 US Envelope 3 5/8 x 6 1/2 in
DMPAPER_FANFOLD_US 39 US Std Fanfold 14 7/8 x 11 in
DMPAPER_FANFOLD_STD_GERMAN 40 German Std Fanfold 8 1/2 x 12 in
DMPAPER_FANFOLD_LGL_GERMAN 41 German Legal Fanfold 8 1/2 x 13 in
DMPAPER_ISO_B4 42 B4 (ISO) 250 x 353 mm
DMPAPER_JAPANESE_POSTCARD 43 Japanese Postcard 100 x 148 mm
DMPAPER_9X11 44 9 x 11 in
DMPAPER_10X11 45 10 x 11 in
DMPAPER_15X11 46 15 x 11 in
DMPAPER_ENV_INVITE 47 Envelope Invite 220 x 220 mm
DMPAPER_RESERVED_48 48 RESERVED--DO NOT USE
DMPAPER_RESERVED_49 49 RESERVED--DO NOT USE
DMPAPER_LETTER_EXTRA 50 US Letter Extra 9 1/2 x 12 in
DMPAPER_LEGAL_EXTRA 51 US Legal Extra 9 1/2 x 15 in
DMPAPER_TABLOID_EXTRA 52 US Tabloid Extra 11.69 x 18 in
DMPAPER_A4_EXTRA 53 A4 Extra 9.27 x 12.69 in
DMPAPER_LETTER_TRANSVERSE 54 Letter Transverse 8 1/2 x 11 in
DMPAPER_A4_TRANSVERSE 55 A4 Transverse 210 x 297 mm
DMPAPER_LETTER_EXTRA_TRANSVERSE 56 Letter Extra Transverse 9 1/2 x 12 in
DMPAPER_A_PLUS 57 SuperA/SuperA/A4 227 x 356 mm
DMPAPER_B_PLUS 58 SuperB/SuperB/A3 305 x 487 mm
DMPAPER_LETTER_PLUS 59 US Letter Plus 8.5 x 12.69 in
DMPAPER_A4_PLUS 60 A4 Plus 210 x 330 mm
DMPAPER_A5_TRANSVERSE 61 A5 Transverse 148 x 210 mm
DMPAPER_B5_TRANSVERSE 62 B5 (JIS) Transverse 182 x 257 mm
DMPAPER_A3_EXTRA 63 A3 Extra 322 x 445 mm
DMPAPER_A5_EXTRA 64 A5 Extra 174 x 235 mm
DMPAPER_B5_EXTRA 65 B5 (ISO) Extra 201 x 276 mm
DMPAPER_A2 66 A2 420 x 594 mm
DMPAPER_A3_TRANSVERSE 67 A3 Transverse 297 x 420 mm
DMPAPER_A3_EXTRA_TRANSVERSE 68 A3 Extra Transverse 322 x 445 mm
DMPAPER_DBL_JAPANESE_POSTCARD 69 Japanese Double Postcard 200 x 148 mm
DMPAPER_A6 70 A6 105 x 148 mm
DMPAPER_JENV_KAKU2 71 Japanese Envelope Kaku #2
DMPAPER_JENV_KAKU3 72 Japanese Envelope Kaku #3
DMPAPER_JENV_CHOU3 73 Japanese Envelope Chou #3
DMPAPER_JENV_CHOU4 74 Japanese Envelope Chou #4
DMPAPER_LETTER_ROTATED 75 Letter Rotated 11 x 8 1/2 11 in
DMPAPER_A3_ROTATED 76 A3 Rotated 420 x 297 mm
DMPAPER_A4_ROTATED 77 A4 Rotated 297 x 210 mm
DMPAPER_A5_ROTATED 78 A5 Rotated 210 x 148 mm
DMPAPER_B4_JIS_ROTATED 79 B4 (JIS) Rotated 364 x 257 mm
DMPAPER_B5_JIS_ROTATED 80 B5 (JIS) Rotated 257 x 182 mm
DMPAPER_JAPANESE_POSTCARD_ROTATED 81 Japanese Postcard Rotated 148 x 100 mm
DMPAPER_DBL_JAPANESE_POSTCARD_ROTATED 82 Double Japanese Postcard Rotated 148 x 200 mm
DMPAPER_A6_ROTATED 83 A6 Rotated 148 x 105 mm
DMPAPER_JENV_KAKU2_ROTATED 84 Japanese Envelope Kaku #2 Rotated
DMPAPER_JENV_KAKU3_ROTATED 85 Japanese Envelope Kaku #3 Rotated
DMPAPER_JENV_CHOU3_ROTATED 86 Japanese Envelope Chou #3 Rotated
DMPAPER_JENV_CHOU4_ROTATED 87 Japanese Envelope Chou #4 Rotated
DMPAPER_B6_JIS 88 B6 (JIS) 128 x 182 mm
DMPAPER_B6_JIS_ROTATED 89 B6 (JIS) Rotated 182 x 128 mm
DMPAPER_12X11 90 12 x 11 in
DMPAPER_JENV_YOU4 91 Japanese Envelope You #4
DMPAPER_JENV_YOU4_ROTATED 92 Japanese Envelope You #4 Rotated
DMPAPER_P16K 93 PRC 16K 146 x 215 mm
DMPAPER_P32K 94 PRC 32K 97 x 151 mm
DMPAPER_P32KBIG 95 PRC 32K(Big) 97 x 151 mm
DMPAPER_PENV_1 96 PRC Envelope #1 102 x 165 mm
DMPAPER_PENV_2 97 PRC Envelope #2 102 x 176 mm
DMPAPER_PENV_3 98 PRC Envelope #3 125 x 176 mm
DMPAPER_PENV_4 99 PRC Envelope #4 110 x 208 mm
DMPAPER_PENV_5 100 PRC Envelope #5 110 x 220 mm
DMPAPER_PENV_6 101 PRC Envelope #6 120 x 230 mm
DMPAPER_PENV_7 102 PRC Envelope #7 160 x 230 mm
DMPAPER_PENV_8 103 PRC Envelope #8 120 x 309 mm
DMPAPER_PENV_9 104 PRC Envelope #9 229 x 324 mm
DMPAPER_PENV_10 105 PRC Envelope #10 324 x 458 mm
DMPAPER_P16K_ROTATED 106 PRC 16K Rotated
DMPAPER_P32K_ROTATED 107 PRC 32K Rotated
DMPAPER_P32KBIG_ROTATED 108 PRC 32K(Big) Rotated
DMPAPER_PENV_1_ROTATED 109 PRC Envelope #1 Rotated 165 x 102 mm
DMPAPER_PENV_2_ROTATED 110 PRC Envelope #2 Rotated 176 x 102 mm
DMPAPER_PENV_3_ROTATED 111 PRC Envelope #3 Rotated 176 x 125 mm
DMPAPER_PENV_4_ROTATED 112 PRC Envelope #4 Rotated 208 x 110 mm
DMPAPER_PENV_5_ROTATED 113 PRC Envelope #5 Rotated 220 x 110 mm
DMPAPER_PENV_6_ROTATED 114 PRC Envelope #6 Rotated 230 x 120 mm
DMPAPER_PENV_7_ROTATED 115 PRC Envelope #7 Rotated 230 x 160 mm
DMPAPER_PENV_8_ROTATED 116 PRC Envelope #8 Rotated 309 x 120 mm
DMPAPER_PENV_9_ROTATED 117 PRC Envelope #9 Rotated 324 x 229 mm
DMPAPER_PENV_10_ROTATED 118 PRC Envelope #10 Rotated 458 x 324 mm

*/
/*
typedef struct _devicemodeA {
  BYTE  dmDeviceName[CCHDEVICENAME];
  WORD  dmSpecVersion;
  WORD  dmDriverVersion;
  WORD  dmSize;
  WORD  dmDriverExtra;
  DWORD dmFields;
  union {
    struct {
      short dmOrientation;
	  short dmPaperSize;
      short dmPaperLength;
      short dmPaperWidth;
      short dmScale;
      short dmCopies;
      short dmDefaultSource;
      short dmPrintQuality;
    } DUMMYSTRUCTNAME;
    POINTL dmPosition;
    struct {
      POINTL dmPosition;
      DWORD  dmDisplayOrientation;
      DWORD  dmDisplayFixedOutput;
    } DUMMYSTRUCTNAME2;
  } DUMMYUNIONNAME;
  short dmColor;
  short dmDuplex;
  short dmYResolution;
  short dmTTOption;
  short dmCollate;
  BYTE  dmFormName[CCHFORMNAME];
  WORD  dmLogPixels;
  DWORD dmBitsPerPel;
  DWORD dmPelsWidth;
  DWORD dmPelsHeight;
  union {
    DWORD dmDisplayFlags;
    DWORD dmNup;
  } DUMMYUNIONNAME2;
  DWORD dmDisplayFrequency;
  DWORD dmICMMethod;
  DWORD dmICMIntent;
  DWORD dmMediaType;
  DWORD dmDitherType;
  DWORD dmReserved1;
  DWORD dmReserved2;
  DWORD dmPanningWidth;
  DWORD dmPanningHeight;
} DEVMODEA, *PDEVMODEA, *NPDEVMODEA, *LPDEVMODEA;
*/


__fastcall TfrmPrintSetting::TfrmPrintSetting(TComponent* Owner)
	: TForm(Owner)
{
	//======================================================================
	//241204//#전주#중앙정보테크//
	//======================================================================
	if(frmMain->_SKINCOLOR_ > 0)
	{
		int R	= GetRValue(frmMain->_SKINCOLOR_);
		int G	= GetGValue(frmMain->_SKINCOLOR_);
		int B	= GetBValue(frmMain->_SKINCOLOR_);

		//shpBG->Pen->Color//
		this->shpBG->Pen->Color		= (TColor)RGB(R, G, B);
		//shpWait->Pen->Color//
		this->shpWait->Pen->Color	= (TColor)RGB(R, G, B);
		//panWindowsMove->Color//
		this->panWindowsMove->Color	= (TColor)RGB(R, G, B);
		//pnlWaitT->Color//
		this->pnlWaitT->Color		= (TColor)RGB(R, G, B);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintSetting::frmPrintSetting_OnCreate(TObject *Sender)
{
	nPosition = 5;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::FormShow(TObject *Sender)
{
	btnPrint0->Visible = true;
	btnSaveSetting->Left = 250;

	bFromShow = true;//설정변경할 때마다 funcGetPrintPreview()를 호출하게 되는데 그것을 방지하기 위함//
	bDoc8Card = false;//구대장-카드아님

	////////////////////////////////////////////////////////////////////////////
	if (DirectoryExists(frmMain->PRINTPATH))//print 하위 파일들 삭제하기
		eFunc->funcDeleteDir(true, frmMain->PRINTPATH);
	if (!DirectoryExists(frmMain->PRINTPATH))
		CreateDir(frmMain->PRINTPATH);


	/////////////////////////////////////
	nDocNo = frmMain->m_nViewDocNo;//funcClickNodeToDocNum(frmMain->mSearchNode.tSelectNode);

	//201222//이미지 회전 후 인쇄//
	nWidth  = FreeImage_GetWidth(frmMain->mGetImageInfo.m_DIB);
	nHeight = FreeImage_GetHeight(frmMain->mGetImageInfo.m_DIB);
//	nWidth  = frmMain->mGetImageInfo.nImageWidth;
//	nHeight = frmMain->mGetImageInfo.nImageHeight;

	//get resolution
	if(frmMain->bJGWExists)
	{
		dMMtoPixelW = ((double)frmMain->biXPelsPerMeterJGW / (double)100) / (double)10;
		dMMtoPixelH = ((double)frmMain->biYPelsPerMeterJGW / (double)100) / (double)10;
		dResolRate = (int)RoundTo((double)frmMain->biXPelsPerMeterJGW * (double)2.54 / (double)100 / (double)100, -3);//0.72, 0.96, 1, 2, 3
	}
	else
	{
		dMMtoPixelW = ((double)frmMain->mGetImageInfo.mBitMapHeadInfo.biXPelsPerMeter / (double)100) / (double)10;
		dMMtoPixelH = ((double)frmMain->mGetImageInfo.mBitMapHeadInfo.biYPelsPerMeter / (double)100) / (double)10;
		dResolRate = RoundTo((double)frmMain->mGetImageInfo.mBitMapHeadInfo.biXPelsPerMeter * (double)2.54 / (double)100 / (double)100, -3);//0.72, 0.96, 1, 2, 3

		if(dResolRate == 0.72)
		{
			dResolRate = 0.96;

			dRatio = 1.584;//1.57;
			dMMtoPixelW = (double)(dResolRate / (double)0.96)*(double)fr01cm * dRatio;//((double)frmMain->mGetImageInfo.mBitMapHeadInfo.biXPelsPerMeter / (double)100) / (double)10;
			dMMtoPixelH = (double)(dResolRate / (double)0.96)*(double)fr01cm * dRatio;//((double)frmMain->mGetImageInfo.mBitMapHeadInfo.biYPelsPerMeter / (double)100) / (double)10;
			dMMtoPixelW = (double)(dResolRate / (double)0.96)*(double)fr01cm * dRatio;//((double)frmMain->mGetImageInfo.mBitMapHeadInfo.biXPelsPerMeter / (double)100) / (double)10;
			dMMtoPixelH = (double)(dResolRate / (double)0.96)*(double)fr01cm * dRatio;//((double)frmMain->mGetImageInfo.mBitMapHeadInfo.biYPelsPerMeter / (double)100) / (double)10;
		}
	}

	nImgmmW = nWidth / dMMtoPixelW;//pixel -> mm
	nImgmmH = nHeight / dMMtoPixelH;//pixel -> mm

	if(nDocNo == 7)
	{
		gbDoc7->Enabled = true;
		chkDoc7Form->Enabled = true;
		edtPrintTitle->Text = "";//190928//44230//req
		gbTitle->Enabled = false;//190928//44230//req
	}
	else
	{
		gbDoc7->Enabled = false;
		chkDoc7Form->Enabled = false;
		gbTitle->Enabled = true;//190928//44230//req
		edtPrintTitle->Text = "";//190928//44230//req
	}

	if(nDocNo == 8)
	{
		gbDoc8->Enabled = true;
		chkDoc8Page2->Enabled = true;
		lblDoc8Page2_1->Enabled = true;
		lblDoc8Page2_2->Enabled = true;
		chkDoc8Stamp->Enabled = true;
	}
	else
	{
		gbDoc8->Enabled = false;
		chkDoc8Page2->Enabled = false;
		lblDoc8Page2_1->Enabled = false;
		lblDoc8Page2_2->Enabled = false;
		chkDoc8Stamp->Enabled = false;
	}

	funcSetPrintScale();//201214//moved//

	funcGetPrinterList();//프린터 목록 가져오기

	funcGetDBValue();

	funcSetPosPanelCaption(nPosition);

	chkDoc7FormClick(NULL);

	funcGetPrintPreview();//190401

	nFlag = 0;
	bFromShow = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(bmpLoad != NULL)
	{
		delete bmpLoad;
		bmpLoad = NULL;
	}

	frmPrintSetting->Tag = 0;
	cboPaperType->ItemIndex = 0;
	bDoc8Card = false;

	//인쇄 안 누르고 그냥 프린트 설정 창 종료시//
	if (frmMain->mRactState.bRactCalcFlag && frmMain->PBCONTROL2->Visible && nFlag == 0)
	{
		frmMain->mRactState.bRactCalcFlag = false;

		memset(&frmMain->mMouseStateLayer1, 0, sizeof(frmMain->mMouseStateLayer1));
		memset(&frmMain->mRactState, 0, sizeof(frmMain->mRactState));
		frmMain->PBCONTROL2->Invalidate();
		if(frmMain->PBCONTROL2->Visible)	frmMain->PBCONTROL2->Visible	= false;
	}

	//200323
	frmMain->IMGDOCPRINT->Picture->Bitmap->Handle     = NULL;
	frmMain->IMGDOCPRINT->Picture                     = NULL;
	if(frmMain->mToolButtonState == DF_RECTANGLE)
	{
		frmMain->IMGDOCRECTCLEAR->Picture->LoadFromFile(frmMain->IMAGEMAINPATH + "select_rectclear.png");
		frmMain->_CURRENT_DOCWORKMODE = "영역선택";
    }
}
//---------------------------------------------------------------------------

//201223//
void __fastcall TfrmPrintSetting::funcSetWaitWindows(bool bSetValue)
{
	palWait->Left = (pnlPrintPreview->Width/2) - (palWait->Width/2);
	palWait->Top  = (pnlPrintPreview->Height/2) - (palWait->Height/2);
	//palWait->Top  = (palClient->Height/2) - (palWait->Height/2);//191126//

	if (this->palWait->Visible == !bSetValue)
	{
		palWait->Visible = bSetValue;

		if (bSetValue)		Screen->Cursor     = crHourGlass;
		else            	Screen->Cursor     = crDefault;

		if(!bSetValue)
			lblWait2->Caption  = "선택 작업을 적용중입니다.";
	}

	Application->ProcessMessages();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::funcFastReportOpen(char *_cParameters, int _nType)
{
	AnsiString asExecFile;
	if (_nType == 7) {
		asExecFile = frmMain->ROOTPATH + "LandOfficePrint07.exe";
	}
	else if (_nType == 0) {
		asExecFile = frmMain->ROOTPATH + "LandOfficePrint.exe";
	}

	int nDoc = frmMain->m_nViewDocNo;//funcClickNodeToDocNum(frmMain->mSearchNode.tSelectNode);

//230207//funcSetUserHistState()Param변경//
//	//230207//int nType = eFunc->funcGetKindNameToKindIndex(503, "인쇄");//210305//#44710//4
//	AnsiString  asKindCode = eFunc->funcGetKindNameToKindCode(503, "인쇄");//230207//210305//#44710//4
//	if( !asKindCode.IsEmpty() )
//		frmUserManagement->funcSetUserHistState(&frmUserManagement->mCurrentUser, asKindCode.ToInt(), nDoc);//인쇄//
	frmUserManagement->funcSetUserHistState(&frmUserManagement->mCurrentUser, "인쇄", nDoc);//인쇄//

	SHELLEXECUTEINFO ExVal;
	ExVal.cbSize       = sizeof(SHELLEXECUTEINFO);
	ExVal.fMask        = NULL;
	ExVal.hwnd         = NULL;
	ExVal.lpVerb       = NULL;
	ExVal.lpFile       = asExecFile.c_str();

	ExVal.lpParameters = _cParameters;
	ExVal.lpDirectory  = "";
	ExVal.nShow        = SW_SHOW;
	ExVal.hInstApp     = NULL;
	ShellExecuteEx(&ExVal);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::funcCopyInfoToDb()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	SQLRETURN 	usRet;
	char		cSqlQry[QRY_ARRANGE_SIZE];

	SQLCHAR     SqlState[6], SQLStmt[100], Msg[SQL_MAX_MESSAGE_LENGTH];
	SQLINTEGER  NativeError;
	SQLSMALLINT	i = 0;
	SQLSMALLINT MsgLen = 0;

	memset(SqlState, 0, sizeof(SqlState));
	memset(SQLStmt, 0, sizeof(SQLStmt));
	memset(Msg, 0, sizeof(Msg));

	memset(&mDoc07CopyInfo, 0, sizeof(mDoc07CopyInfo));

	AnsiString asDateStr = Now().FormatString("yyyymmdd");
	AnsiString asTimeStr = Now().FormatString("hh:nn:ss");
	AnsiString asDateStrTypeA = Now().FormatString("yyyy년 mm월 dd일");

	wsprintf(mDoc07CopyInfo.cCopyDate, "%s", asDateStr.c_str());
	AnsiString	asCopyInfo1 = mDoc07CopyInfo.cCopyDate;

	mDoc07CopyInfo.nCopyNo = funcDbToCopyNoIndex(mDoc07CopyInfo.cCopyDate) + 1;
	AnsiString	asCopyInfo2 = IntToStr(mDoc07CopyInfo.nCopyNo);

	wsprintf(mDoc07CopyInfo.cCopyTime, "%s", asTimeStr.c_str());
	AnsiString	asCopyInfo3	= mDoc07CopyInfo.cCopyTime;

	char cUserId[64];
	memset(cUserId, 0, sizeof(cUserId));
	wsprintf(cUserId, "%s", AnsiString(frmMain->USERINI->ReadString("USER_CONFIG", "ID", " ")).c_str());
	AnsiString	asCopyInfo4 = frmMain->m_asCurrentNm;//200925//this->funcDbToUserName(cUserId);

	wchar_t			wcAddress[255];
	memset(wcAddress, 0, sizeof(wcAddress));

//190228//지번 1개만 검색하는 것이 아니므로 아래 코드는 사용할 수가 없다.
//	if (frmMain->funcGetSelectAddressStr(wcAddress) > 0) {
//		AnsiString asAddress = wcAddress;
//		sprintf(mDoc07CopyInfo.cCopyAddress, "%s", asAddress.c_str());
//	}

	AnsiString	asCopyInfo5 = "";
	TTreeNode		*TempNode = frmMain->mSearchNode.tSelectNode;
	int	nSelDoc = eTree->funcClickNodeToDocNum(TempNode);
	AnsiString 	asPrinterName 	= m_sPrinterList->Strings[cboPrinterList->ItemIndex];//201230//

	//Document Title
	AnsiString	asCopyInfo0 = "";//190423

	switch (nSelDoc) {
		case 2:
			DOCUMENT02_STRUCT	*mDoc2Struct;
			mDoc2Struct = (DOCUMENT02_STRUCT*)TempNode->Data;
			if (!mDoc2Struct) { break; }
			sprintf(mDoc07CopyInfo.cDoHoNo, "%s", mDoc2Struct->DOHO);
			sprintf(mDoc07CopyInfo.cScale, "%s", mDoc2Struct->RDSCALE_CODE);
			if( mDoc2Struct->AF_PNU != NULL )
				sprintf(mDoc07CopyInfo.cCopyAddress, "%s", eFunc->funcPnuToUMDRIName(mDoc2Struct->AF_PNU, false));
			else if( mDoc2Struct->BF_PNU != NULL )
				sprintf(mDoc07CopyInfo.cCopyAddress, "%s", eFunc->funcPnuToUMDRIName(mDoc2Struct->BF_PNU, false));
			else
				sprintf(mDoc07CopyInfo.cCopyAddress, "");

			asCopyInfo5 = mDoc07CopyInfo.cCopyAddress;
			break;

		case 7:
			//200401//
			if(frmSql->m_ResultDoc07DBInfo.size() == 0)
				break;

			AnsiString asStr = "";

			sprintf(mDoc07CopyInfo.cDoHoNo, "%s", frmSql->m_ResultDoc07DBInfo[0].DOHO_BON);
			asStr = (char*)frmSql->m_ResultDoc07DBInfo[0].SCALE;
			if( asStr.IsEmpty() )	asStr = "-";
			else					asStr.sprintf("%04d", asStr.ToInt()*100);
			//else					asStr.sprintf("%02d00", asStr.ToInt());
			sprintf(mDoc07CopyInfo.cScale, "%s", asStr);

			asStr = (char*)frmSql->m_ResultDoc07DBInfo[0].SIDOSGG;
			asStr = asStr + (char*)frmSql->m_ResultDoc07DBInfo[0].UMD;
			asStr = asStr + (char*)frmSql->m_ResultDoc07DBInfo[0].RI;
			asStr.sprintf("%s%s00000000", asStr, frmSql->m_ResultDoc07DBInfo[0].LAND_GBN);
			sprintf(mDoc07CopyInfo.cCopyAddress, "%s", eFunc->funcPnuToUMDRIName(asStr.c_str(), false));

			asCopyInfo5 = mDoc07CopyInfo.cCopyAddress;
			//원래는 KIND_CODE로 해야 함//1:6000일 때만 타이틀 "임야도"로...//190423
			//			asCopyInfo0.sprintf("%s %s", eFunc->funcGetKindCodeToKindName(7, mDoc7Struct->KIND_CODE), "등본");//190423
			if( !strcmp(mDoc07CopyInfo.cScale, "6000") )
				asCopyInfo0 = "임야도 등본";
			else
				asCopyInfo0 = "지적도 등본";
			break;
	}

	AnsiString	asCopyInfo6	= mDoc07CopyInfo.cDoHoNo;
	AnsiString	asCopyInfo7	= mDoc07CopyInfo.cScale;

	//
	wsprintf(mDoc07CopyInfo.cCopyDateTypeA, "%s", asDateStrTypeA.c_str());
	AnsiString	asCopyInfo8	= mDoc07CopyInfo.cCopyDateTypeA;

	funcAddSiGunTitle(mDoc07CopyInfo.cSiGunTitel);
	AnsiString	asCopyInfo9	= mDoc07CopyInfo.cSiGunTitel;

	AnsiString	asCopyInfo10 = "OK";

	//190128//moved from untIniControl.cpp
	AnsiString asIniFile = frmMain->ROOTPATH + "DATA\\CopyDoc.ini";
	if(FileExists(asIniFile))
		DeleteFile(asIniFile);
	frmMain->PRINTDOC07INI = new TIniFile(asIniFile);//

	// To Do
	frmMain->PRINTDOC07INI->WriteString(L"COPY_DOC07", L"TITLE", asCopyInfo0.c_str());//190423
	frmMain->PRINTDOC07INI->WriteString(L"COPY_DOC07", L"DATE", asCopyInfo1.c_str());
	frmMain->PRINTDOC07INI->WriteString(L"COPY_DOC07", L"NO", asCopyInfo2.c_str());
	frmMain->PRINTDOC07INI->WriteString(L"COPY_DOC07", L"TIME", asCopyInfo3.c_str());
	frmMain->PRINTDOC07INI->WriteString(L"COPY_DOC07", L"USER", asCopyInfo4.c_str());
	frmMain->PRINTDOC07INI->WriteString(L"COPY_DOC07", L"ADDRESS", asCopyInfo5.c_str());
	frmMain->PRINTDOC07INI->WriteString(L"COPY_DOC07", L"DOHO", asCopyInfo6.c_str());
	frmMain->PRINTDOC07INI->WriteString(L"COPY_DOC07", L"SCALE", asCopyInfo7.c_str());
	frmMain->PRINTDOC07INI->WriteString(L"COPY_DOC07", L"DATEA", asCopyInfo8.c_str());
	frmMain->PRINTDOC07INI->WriteString(L"COPY_DOC07", L"SIGUN", asCopyInfo9.c_str());
	frmMain->PRINTDOC07INI->WriteString(L"COPY_DOC07", L"ETC", asCopyInfo10.c_str());
	frmMain->PRINTDOC07INI->WriteString(L"COPY_DOC07", L"PREVIEW", (chkPreview->Checked == true) ? (1) : (0));
	frmMain->PRINTDOC07INI->WriteString(L"COPY_DOC07", L"PRINTER", 		asPrinterName);//201230//

	// To Do
	memset(cSqlQry, 0, QRY_ARRANGE_SIZE);
	wsprintf(cSqlQry, "INSERT INTO TB_COPY_DOC07 (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s) values('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
						"FT_DATE",
						"FN_NO",
						"FT_TIME",
						"FT_USER",
						"FT_ADDRESS",
						"FT_DOHO",
						"FT_SCALE",
						"FT_DATE2",
						"FT_SIGUN",
						"FT_ETC",
						asCopyInfo1.c_str(),
						asCopyInfo2.c_str(),
						asCopyInfo3.c_str(),
						asCopyInfo4.c_str(),
						asCopyInfo5.c_str(),
						asCopyInfo6.c_str(),
						asCopyInfo7.c_str(),
						asCopyInfo8.c_str(),
						asCopyInfo9.c_str(),
						asCopyInfo10.c_str());


	usRet = SQLExecDirect(frmSql->m_hStmt, (SQLCHAR *) cSqlQry, SQL_NTS);
	if ((usRet != SQL_SUCCESS) &&(usRet != SQL_SUCCESS_WITH_INFO)  && (usRet != SQL_NO_DATA))
	{
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	memset(cSqlQry, 0, QRY_ARRANGE_SIZE);
	wsprintf(cSqlQry, "commit");
	usRet = SQLExecDirect(frmSql->m_hStmt, (SQLCHAR *) cSqlQry, SQL_NTS);

	if ((usRet != SQL_SUCCESS) &&(usRet != SQL_SUCCESS_WITH_INFO)  && (usRet != SQL_NO_DATA) )
	{
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);
}
//---------------------------------------------------------------------------

int __fastcall TfrmPrintSetting::funcDbToCopyNoIndex(char *_cDate)
{
	if (frmSql->m_hStmt)		SQLCloseCursor(frmSql->m_hStmt);

	int nReturnValue = 0;

	char cDate[32];
	memset(cDate, 0, sizeof(cDate));
	int nCopyNo = 0;

	SQLINTEGER 		m_nVal[2];

	char		cSqlQry[QRY_ARRANGE_SIZE];

	int nIndex = 1;

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, cDate  	, sizeof(cDate)  	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, &nCopyNo  , sizeof(nCopyNo)    , &m_nVal[nIndex-1]); nIndex++;

	memset(cSqlQry, 0, sizeof(cSqlQry));
	wsprintf(cSqlQry, "SELECT FT_DATE, FN_NO FROM TB_COPY_DOC07 WHERE FT_DATE='%s' ORDER BY FT_DATE, FN_NO ASC", _cDate);

	SQLRETURN ret;
	ret = SQLPrepare(frmSql->m_hStmt, (SQLCHAR *)cSqlQry, SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if ((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO) && (ret != SQL_NO_DATA)) {
		if (frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);
	}
	else {
		memset(cDate, 0, sizeof(cDate));
		nCopyNo = 0;

		while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA)
		{
			nReturnValue = nCopyNo;

			memset(cDate, 0, sizeof(cDate));
			nCopyNo = 0;

		};
		if (frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);
	}

	return nReturnValue;
}
//---------------------------------------------------------------------------


void __fastcall TfrmPrintSetting::funcAddSiGunTitle(char *_cBuff)
{
//=============================================================================
//250611//SIDO_CODE.NAME 텍스트에 '청'이 누락되어 업데이트되어 '지적도등본' 출력 시 하단 문구가 나오지 않는 이슈 발생하여 아래와 같이 처리//
	AnsiString  asTemp	= "";
	if (frmMain->_SIDONAME.SubString(frmMain->_SIDONAME.Length()-3, 4) == "시청" || frmMain->_SIDONAME.SubString(frmMain->_SIDONAME.Length()-3, 2) == "시")
		asTemp	= frmMain->_SIDONAME.SubString(1, frmMain->_SIDONAME.Length()-4) + "시장";
	else if (frmMain->_SIDONAME.SubString(frmMain->_SIDONAME.Length()-3, 4) == "군청" || frmMain->_SIDONAME.SubString(frmMain->_SIDONAME.Length()-3, 2) == "군")
		asTemp	= frmMain->_SIDONAME.SubString(1, frmMain->_SIDONAME.Length()-4) + "군수";
	else if (frmMain->_SIDONAME.SubString(frmMain->_SIDONAME.Length()-3, 4) == "구청" || frmMain->_SIDONAME.SubString(frmMain->_SIDONAME.Length()-3, 2) == "구")
		asTemp	= frmMain->_SIDONAME.SubString(1, frmMain->_SIDONAME.Length()-4) + "구청장";
	wsprintf(_cBuff, asTemp.c_str());
//=============================================================================

}
//---------------------------------------------------------------------------
//Minji_#02_B_Print
void __fastcall TfrmPrintSetting::btnPrint0Click(TObject *Sender)
{
	if (frmMain->IMGSCREEN2->Picture->Bitmap == NULL || frmMain->IMGSCREEN2->Picture->Bitmap->Width == 0) {
		AnsiString strMsg = "지정된 이미지가 없습니다.";
		frmMsg->funcMessageDlg("이미지 부재 알림:", strMsg, 3);
		return;
	}

	funcSetPrintSetting();//200108//TEST

	funcSaveSetting();

	funcWriteIniData();

	//도곽선 그리기
	if(frmMain->m_vDOGAKLINE.size() > 0)//190329
	{
		m_vDOGAKLINE_Bck = frmMain->m_vDOGAKLINE;

		funcDogakLinePaint();
	}

	if(frmMain->lblMapPoint->Visible && frmMain->shpMapPoint->Visible)//190625//지번표시 텍스트 > 인쇄
		funcMapPointPaint();

	bool bZoomed = false;

	if((frmMain->IMGSCREEN2->Left < 0 || frmMain->IMGSCREEN2->Top < 0 || (frmMain->IMGSCREEN2->Left+frmMain->IMGSCREEN2->Width) > frmMain->palMainView->Width || (frmMain->IMGSCREEN2->Top+frmMain->IMGSCREEN2->Height) > frmMain->palMainView->Height)
	&& (frmMain->IMGSCREEN2->Width > frmMain->mGetImageInfo.nImageWidth || frmMain->IMGSCREEN2->Height > frmMain->mGetImageInfo.nImageHeight) )
	{
		bZoomed = true;
	}

	funcPrintSettingRealPart(true);

	frmMain->mToolButtonState = DF_PANNING;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::funcPrintSettingFitAll()
{
	char cParameters[255];
	char cPaper[255];

	memset(cParameters, 0, sizeof(cParameters));
	memset(cPaper, 0, sizeof(cPaper));
	if(cboPaperType->ItemIndex == 0)//A4
		wsprintf(cPaper, "%s", "A4");
	else if(cboPaperType->ItemIndex == 1)//A3
		wsprintf(cPaper, "%s", "A3");
	else if(cboPaperType->ItemIndex == 2)//A2
		wsprintf(cPaper, "%s", "A2");

	AnsiString asFilePath = frmMain->PRINTPATH;
	////////////////////////////////////////////////////////////////////////////
	if (DirectoryExists(frmMain->PRINTPATH))//print 하위 파일들 삭제하기
		eFunc->funcDeleteDir(true, frmMain->PRINTPATH);
	if (!DirectoryExists(frmMain->PRINTPATH))
		CreateDir(frmMain->PRINTPATH);

	asFilePath = asFilePath + "temp1.bmp";

	try
	{
		Graphics::TBitmap  	*bmpTemp = new Graphics::TBitmap();
		bmpTemp->PixelFormat = pf24bit;
		bmpTemp->Assign(bmpLoad);
		bmpTemp->SaveToFile(asFilePath);

		delete bmpTemp;
		bmpTemp = NULL;

		//===================
		//200925//[TODO]
//		if (rbPortrait->Checked) {
//			sprintf(cParameters, "%s%s", cPaper, "_P");
//		}
//		else if (rbLandscape->Checked){
//			sprintf(cParameters, "%s%s", cPaper, "_L");
//		}
		//200813//TEST//old
		if (nWidth > nHeight) {
			sprintf(cParameters, "%s%s", cPaper, "_L");
		}
		else{
			sprintf(cParameters, "%s%s", cPaper, "_P");
		}
	}
	__finally {
		this->funcFastReportOpen(cParameters, 0);
	}

	Close();
}
//---------------------------------------------------------------------------

//선택 영역을 실제 크기로 인쇄
void __fastcall TfrmPrintSetting::funcPrintSettingRealPart(bool _bAll)
{
	char cParameters[255];
	char cPaper[255];

	memset(cParameters, 0, sizeof(cParameters));
	memset(cPaper, 0, sizeof(cPaper));

	memset(cPaper, 0, sizeof(cPaper));
	if(cboPaperType->ItemIndex == 0)//A4
		wsprintf(cPaper, "%s", "A4");
	else if(cboPaperType->ItemIndex == 1)//A3
		wsprintf(cPaper, "%s", "A3");
	else if(cboPaperType->ItemIndex == 2)//A2
		wsprintf(cPaper, "%s", "A2");

	AnsiString asFilePath = frmMain->PRINTPATH;
	if (!DirectoryExists(frmMain->PRINTPATH))
		CreateDir(frmMain->PRINTPATH);

	asFilePath = asFilePath + "temp1.bmp";//jpg

	try {
		if( nDocNo == 7 && chkDoc7Form->Checked )//지적도//양식
			funcCopyInfoToDb();

		sprintf(cParameters, "%s%s", cPaper, m_asOrientation);//200320//

		frmMain->funcDeleteRectangle();//210428//#RECTCLEAR//frmMain->m_vRECT.clear();
	}

	__finally {
		if( nDocNo == 7 && chkDoc7Form->Checked )//지적도//양식
		{
			this->funcFastReportOpen(cParameters, nDocNo);
		}
		else
		{
			//200926////200914//
//			if(nDocNo == 8 && chkDoc8Page2->Checked)
//			{
//				sprintf(cParameters, "%s%s", cPaper, "_P");
//			}
//			else
//			{
//		        if (rbPortrait->Checked) {
//			        sprintf(cParameters, "%s%s", cPaper, "_P");
//		        }
//		        else if (rbLandscape->Checked){
//			        sprintf(cParameters, "%s%s", cPaper, "_L");
//		        }
//			}

			this->funcFastReportOpen(cParameters, 0);
		}
	}

	//부분인쇄할때//
	frmMain->funcInitPBControl2();

	Close();
}
//---------------------------------------------------------------------------


void __fastcall TfrmPrintSetting::funcWriteIniData()
{
	String sTemp;
	String sItemLabel;
	AnsiString asStr;
	AnsiString asSido;

	//220930//44770추가//220712//#44250//계룡만 임시로 인쇄 설정 파일 삭제 안함//
	AnsiString asIniFile = frmMain->ROOTPATH + "DATA\\PrintSetting.ini";
	try{
//231108//태안군에서도 이슈 발생하여 PrintSetting.ini 삭제하지 않고 유지//
//		if(frmMain->_SIDOCODE != "44250" && frmMain->_SIDOCODE != "44770")
//		{
//			if (FileExists(asIniFile))
//				DeleteFile(asIniFile);
//		}

		Sleep(100);//220712//44250//계룡주무관들 PC 노후로 인해 설정파일(PrintSetting.ini) 삭제하고 바로 쓰기가 안되서 문제발생//

		if((int)mSetPrint.size() == 0)
		{
			frmMsg->funcMessageDlg("알림:", "인쇄설정파일이 존재하지 않습니다.", 3);
			return;
		}
	}
	__finally{
		frmMain->_iniPrintSetting = new TIniFile(asIniFile);//

		// To Do SIDO CODE SETTING
	//	AnsiString 	asPrinterName 	= mSetPrint[0].cPrinterName;
	//	int 		nPaperSize		= mSetPrint[0].nPaperSize;
		AnsiString 	asPrinterName 	= m_sPrinterList->Strings[cboPrinterList->ItemIndex];
		int 		nPaperSize		= cboPaperType->ItemIndex;
		int 		nScale 			= mSetPrint[0].nScale;
		int 		nPosition 		= mSetPrint[0].nPosition;
		int 		nDoc8Page2 		= mSetPrint[0].nDoc8Page2;
		int 		nDoc8Stamp 		= mSetPrint[0].nDoc8Stamp;
		int 		nDoc7P 			= mSetPrint[0].nDoc7P;
		int 		nPreview    	= mSetPrint[0].nPreview;

		//frmMain->_iniPrintSetting->WriteString(L"PRINT_SETTING", L"PRINTER_NAME", asPrinterName);
		frmMain->_iniPrintSetting->WriteString(L"PRINT_SETTING", L"PRINTER", 	asPrinterName);//201230//
		frmMain->_iniPrintSetting->WriteString(L"PRINT_SETTING", L"PAPER_SIZE", nPaperSize);
		frmMain->_iniPrintSetting->WriteString(L"PRINT_SETTING", L"SCALE", 		nScale);
		frmMain->_iniPrintSetting->WriteString(L"PRINT_SETTING", L"POSITION", 	nPosition);
		frmMain->_iniPrintSetting->WriteString(L"PRINT_SETTING", L"DOC8PAGE2", 	nDoc8Page2);
		frmMain->_iniPrintSetting->WriteString(L"PRINT_SETTING", L"DOC8STAMP", 	nDoc8Stamp);
		frmMain->_iniPrintSetting->WriteString(L"PRINT_SETTING", L"DOC7P", 		nDoc7P);
		frmMain->_iniPrintSetting->WriteString(L"PRINT_SETTING", L"PREVIEW", 		nPreview);
		if(dResolRate == 0)
			frmMain->_iniPrintSetting->WriteString(L"PRINT_SETTING", L"RESOLUTION", 200);
		else if(dResolRate == 0.96)
			frmMain->_iniPrintSetting->WriteString(L"PRINT_SETTING", L"RESOLUTION", (dResolRate * 100) * dRatio);
		else
			frmMain->_iniPrintSetting->WriteString(L"PRINT_SETTING", L"RESOLUTION", dResolRate * 100);

		frmMain->_iniPrintSetting->WriteString(L"PRINT_SETTING", L"TITLE", 		edtPrintTitle->Text);//190928//44230//req
	}
}
//---------------------------------------------------------------------------

int __fastcall TfrmPrintSetting::funcQryInsertPrint(int _nType)
{
	AnsiString  asSqlQry		= "";
	AnsiString 	asSqlTbl 		= "TB_PRINT";
	AnsiString 	asSqlCol 		= "";
	AnsiString 	asSqlVal 		= "";
	AnsiString 	asSqlWhere 		= "";
	AnsiString 	asUserId 		= frmMain->m_asCurrentId;
//	AnsiString 	asPrinterName 	= cboPrinterList->Text;
//	int 	   	nPepersize		= cboPaperType->ItemIndex;
	int 	   	nScale   		= cboPrintScale->ItemIndex;
	int         nDoc8Page2 		= (chkDoc8Page2->Checked == true) ? (1) : (0);
	int         nDoc8Stamp 		= (chkDoc8Stamp->Checked == true) ? (1) : (0);
	int 	   	nDoc7P 			= (chkDoc7Form->Checked == true) ? (1) : (0);
	int 	   	nPreview		= (chkPreview->Checked == true) ? (1) : (0);

	int nColCount = 7;
	char cCol[7][20] = {"ID", "SCALE", "POSITION", "DOC8PAGE2", "DOC8STAMP", "DOC7P", "PREVIEW"};

	if (_nType == DF_NEW_RECORD)//====================================
	{
		//Insert Column
		for(int i = 0; i < nColCount; i++)
		{
			AnsiString asCol = cCol[i];
			asSqlCol = asSqlCol + asCol;
			if(i != nColCount-1)
				asSqlCol = asSqlCol + ", ";
		}

		//Insert Values
		asSqlVal = asSqlVal + "'" + asUserId	   + "', ";
//		asSqlVal = asSqlVal + "'" + asPrinterName  + "', ";
//		asSqlVal = asSqlVal 	  + nPepersize	   + ", ";
		asSqlVal = asSqlVal 	  + nScale		   + ", ";
		asSqlVal = asSqlVal 	  + nPosition	   + ", ";
		asSqlVal = asSqlVal 	  + nDoc8Page2 	   + ", ";
		asSqlVal = asSqlVal 	  + nDoc8Stamp	   + ", ";
		asSqlVal = asSqlVal 	  + nDoc7P		   + ", ";
		asSqlVal = asSqlVal 	  + nPreview;

		asSqlQry.sprintf("INSERT INTO %s (%s) values (%s)",	asSqlTbl, asSqlCol, asSqlVal);
	}
	else if (_nType == DF_UPDATE_RECORD)//====================================
	{
		//Query Column
//		asSqlCol = asSqlCol + cCol[1] + " = '" + asPrinterName 	+ "', ";
//		asSqlCol = asSqlCol + cCol[2] + " = "  + nPepersize 	+ ", ";
		asSqlCol = asSqlCol + cCol[1] + " = "  + nScale 		+ ", ";
		asSqlCol = asSqlCol + cCol[2] + " = "  + nPosition 		+ ", ";
		asSqlCol = asSqlCol + cCol[3] + " = "  + nDoc8Page2 	+ ", ";
		asSqlCol = asSqlCol + cCol[4] + " = "  + nDoc8Stamp 	+ ", ";
		asSqlCol = asSqlCol + cCol[5] + " = "  + nDoc7P 		+ ", ";
		asSqlCol = asSqlCol + cCol[6] + " = "  + nPreview;

		//Where condition
		asSqlWhere = asSqlWhere + cCol[0] + "= '" + asUserId + "'";

		asSqlQry.sprintf("UPDATE %s SET %s WHERE %s", asSqlTbl, asSqlCol, asSqlWhere);
	}
	else if (_nType == DF_DELETE_RECORD)//====================================
	{
		//Where condition
		asSqlWhere = asSqlWhere + cCol[0] 	= "'" + asUserId + "'";

		asSqlQry.sprintf("DELETE FROM %s WHERE %s", asSqlTbl, asSqlWhere);
	}

	return frmSql->func_QryProcess(asSqlQry.c_str());
}
//---------------------------------------------------------------------------
//
bool __fastcall TfrmPrintSetting::funcQrySelectPrint()
{
	if (frmSql->m_hStmt)		SQLCloseCursor(frmSql->m_hStmt);

	AnsiString asSqlTbl = "TB_PRINT";
	AnsiString asSqlWhere = "";
	char cSqlQry[QRY_ARRANGE_SIZE];
	SQLINTEGER m_nVal[7];//9
	SQLRETURN ret;
	PRINT_SETTING_STRUCT tempPrint;
	int nIndex = 1;

	memset(m_nVal, 0, sizeof(m_nVal));
	memset(&tempPrint, 0x00, sizeof(PRINT_SETTING_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex, SQL_C_CHAR, tempPrint.cID, 			sizeof(tempPrint.cID), 			&m_nVal[nIndex - 1]);	nIndex++;
//	SQLBindCol(frmSql->m_hStmt, nIndex, SQL_C_CHAR, tempPrint.cPrinterName, 	sizeof(tempPrint.cPrinterName), &m_nVal[nIndex - 1]);	nIndex++;
//	SQLBindCol(frmSql->m_hStmt, nIndex, SQL_C_LONG, &tempPrint.nPaperSize, 	sizeof(tempPrint.nPaperSize), 	&m_nVal[nIndex - 1]);	nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex, SQL_C_LONG, &tempPrint.nScale, 		sizeof(tempPrint.nScale), 		&m_nVal[nIndex - 1]);	nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex, SQL_C_LONG, &tempPrint.nPosition, 	sizeof(tempPrint.nPosition), 	&m_nVal[nIndex - 1]);	nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex, SQL_C_LONG, &tempPrint.nDoc8Page2, 	sizeof(tempPrint.nDoc8Page2), 	&m_nVal[nIndex - 1]); 	nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex, SQL_C_LONG, &tempPrint.nDoc8Stamp, 	sizeof(tempPrint.nDoc8Stamp), 	&m_nVal[nIndex - 1]);   nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex, SQL_C_LONG, &tempPrint.nDoc7P, 		sizeof(tempPrint.nDoc7P), 		&m_nVal[nIndex - 1]);   nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex, SQL_C_LONG, &tempPrint.nPreview, 		sizeof(tempPrint.nPreview), 	&m_nVal[nIndex - 1]);   nIndex++;

	asSqlWhere = "WHERE ID = '" + frmMain->m_asCurrentId +"'";
	memset(cSqlQry, 0, sizeof(cSqlQry));
	sprintf(cSqlQry, "SELECT * FROM %s %s", asSqlTbl.c_str(), asSqlWhere.c_str());

	ret = SQLPrepare(frmSql->m_hStmt, (SQLCHAR*)cSqlQry, SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if ((ret != SQL_SUCCESS) && (ret != SQL_SUCCESS_WITH_INFO) && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(frmSql->m_hStmt);
		AnsiString strMsg = "인쇄 관련 DB 정보 확인이 필요합니다. 개발사에 문의해주세요.";
		frmMsg->funcMessageDlg("DB정보 부재 알림:", strMsg, 2);
		return false;
	}
	else
	{
		mSetPrint.clear();
		while (SQLFetch(frmSql->m_hStmt) != SQL_NO_DATA)
		{
			mSetPrint.push_back(tempPrint);
			memset(&tempPrint, 0x00, sizeof(PRINT_SETTING_STRUCT));
		};

		if (frmSql->m_hStmt)
			SQLCloseCursor(frmSql->m_hStmt);
	}

	if(mSetPrint.size() == 0)
		return false;

	return true;

}//---------------------------------------------------------------------------
void __fastcall TfrmPrintSetting::funcSaveSetting()
{
	funcSetDBValue();

	funcQryInsertPrint((bDBSetValue == false) ? (DF_NEW_RECORD) : (DF_UPDATE_RECORD));
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintSetting::funcGetDBValue()
{
	edtPrintTitle->Text = "";//190928//44230//req

	if(funcQrySelectPrint())//설정정보가 DB에 존재할 때
	{
		funcWriteIniData();

		bDBSetValue 				= true;

//		cboPaperType->ItemIndex		= mSetPrint[0].nPaperSize;
		cboPrintScale->ItemIndex	= mSetPrint[0].nScale;
		nPosition 					= mSetPrint[0].nPosition;

		if(mSetPrint[0].nDoc8Page2)	chkDoc8Page2->Checked	= true;
		else                       	chkDoc8Page2->Checked	= false;

		if(mSetPrint[0].nDoc8Stamp)	chkDoc8Stamp->Checked	= true;
		else                       	chkDoc8Stamp->Checked	= false;

		if(mSetPrint[0].nDoc7P)		chkDoc7Form->Checked 	= true;
		else                   		chkDoc7Form->Checked 	= false;

		if(mSetPrint[0].nPreview) 	chkPreview->Checked 	= true;
		else                   		chkPreview->Checked 	= false;
	}
	else//설정정보가 DB에 없을 때
	{
		nPosition					= 5;
		cboPrintScale->ItemIndex 	= 1;//페이지맞춤(기본)//
		chkDoc8Page2->Checked		= false;
		chkDoc8Stamp->Checked		= false;
		chkDoc7Form->Checked 	 	= false;
		chkPreview->Checked 	 	= false;

		if(funcQryInsertPrint(DF_NEW_RECORD) != 1)
		{
			AnsiString strMsg = "인쇄 설정 정보 저장에 문제가 발생하였습니다.";
			frmMsg->funcMessageDlg("인쇄 설정정보 확인", strMsg, 3);
			return;
		}

		if(funcQrySelectPrint())
			funcWriteIniData();
		else
		{
			AnsiString strMsg = "인쇄 설정 정보 확인이 필요합니다.";
			frmMsg->funcMessageDlg("인쇄 설정정보 확인:", strMsg, 3);
			return;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintSetting::funcSetDBValue()
{
	PRINT_SETTING_STRUCT tempPrint;

	mSetPrint.clear();
	memset(&stPaperSize, 0x00, sizeof(PAPER_SIZE_STRUCT));
	memset(&tempPrint, 0x00, sizeof(PRINT_SETTING_STRUCT));

	bDBSetValue 			= true;

	wsprintf(tempPrint.cID, 			"%s", frmMain->m_asCurrentId.c_str());
//	wsprintf(tempPrint.cPrinterName, 	"%s", cboPrinterList->Text);
//	tempPrint.nPaperSize 	= cboPaperType->ItemIndex;
	tempPrint.nScale 		= cboPrintScale->ItemIndex;
	tempPrint.nPosition 	= nPosition;
	if(cboPaperType->ItemIndex == 0)
	{
		stPaperSize.nWidth 	= 297;
		stPaperSize.nHeight = 210;
	}
	else if(cboPaperType->ItemIndex == 1)
	{
		stPaperSize.nWidth 	= 420;
		stPaperSize.nHeight = 297;
	}
	else if(cboPaperType->ItemIndex == 2)
	{
		stPaperSize.nWidth 	= 594;
		stPaperSize.nHeight = 420;
	}
	tempPrint.nDoc8Page2 	= (chkDoc8Page2->Checked == true) ? (1) : (0);
	tempPrint.nDoc8Stamp 	= (chkDoc8Stamp->Checked == true) ? (1) : (0);
	tempPrint.nDoc7P   		= (chkDoc7Form->Checked == true) ? (1) : (0);
	tempPrint.nPreview 		= (chkPreview->Checked == true) ? (1) : (0);

	mSetPrint.push_back(tempPrint);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::pnlPos_OnClick(TObject *Sender)
{
	TPanel *tcmpPanel = dynamic_cast<TPanel *>(Sender);
	int nTag = dynamic_cast<TPanel*>(Sender)->Tag;

	funcSetPosPanelCaption(nTag);
	nPosition = nTag;

	if( !bFromShow )
		funcGetPrintPreview();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::funcSetPosPanelCaption(int _nPos)
{
	char cPosition[9][20] = {"왼쪽 위", "중앙 위", "오른쪽 위", "왼쪽 중앙", "정 중앙", "오른쪽 중앙", "왼쪽 아래", "중앙 아래", "오른쪽 아래"};

	lblPositionMent->Caption = cPosition[_nPos-1];
	funcSetPosPanelShpSel(_nPos);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintSetting::funcSetPosPanelShpSel(int _nPos)
{
	switch((_nPos - 1) % 3)
	{
		case 0:
			shpSel->Left = 1;
			break;
		case 1:
			shpSel->Left = 32;
			break;
		case 2:
			shpSel->Left = 63;
			break;
	}

	switch((_nPos - 1) / 3)
	{
		case 0:
			shpSel->Top = 1;
			break;
		case 1:
			shpSel->Top = 32;
			break;
		case 2:
			shpSel->Top = 63;
			break;
	}

	shpSel->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintSetting::shpPos1_OnMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	TShape *tcmpShape = dynamic_cast<TShape *>(Sender);
	int nTag = dynamic_cast<TShape*>(Sender)->Tag;

	funcSetPosPanelCaption(nTag);
	nPosition = nTag;

	if( !bFromShow )
		funcGetPrintPreview();//190401
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::chkDoc7FormClick(TObject *Sender)
{
	if(palWait->Visible)//210111//
		return;

	if(nDocNo == 7 && chkDoc7Form->Checked)
	{
		funcCopyInfoToDbPreview();
		nCurImagePaperType 			= 2;
		cboPaperType->Enabled 		= false;
		cboPrintScale->ItemIndex 	= 0;//지적도-실제크기//
		rbPortrait->Enabled			= false;//200813
		rbLandscape->Enabled		= false;//200813
		cboPrintScale->Enabled 		= false;
		pnlDoc7Form->Visible 		= true;
		pnlPaper->Visible 			= false;
		pnlPaper1->Visible 			= false;
		pnlPaper2->Visible 			= false;
	}
	else
	{
		if(nDocNo == 8 && chkDoc8Page2->Checked)
		{
			pnlPaper->Visible = false;
			pnlPaper1->Visible = true;
			pnlPaper2->Visible = true;
			rbPortrait->Enabled		= false;//200914//
			rbLandscape->Enabled	= false;//200914//
			cboPrintScale->Enabled 	= false;//200914//
		}
		else
		{
			pnlPaper->Visible = true;
			pnlPaper1->Visible = false;
			pnlPaper2->Visible = false;
			rbPortrait->Enabled		= true;//200914//
			rbLandscape->Enabled	= true;//200914//
			cboPrintScale->Enabled 	= true;//200914//
		}

		pnlDoc7Form->Visible 	= false;
		cboPaperType->Enabled 	= true;
		pnlPosition->Enabled 	= true;
	}

	cboPaperType->ItemIndex = 0;
	cboPaperTypeClick(NULL);
}
//---------------------------------------------------------------------------
AnsiString __fastcall TfrmPrintSetting::funcDownloadImage(bool _bPrint, AnsiString _asFullPath)
{
	FTP_FILE_STRUCT	mDownloadFile;
	AnsiString asRemoteDir = ExtractFilePath(_asFullPath);
	AnsiString asFileName  = ExtractFileName(_asFullPath);
	AnsiString asLocalDir  = frmMain->PRINTPATH;//"Print\\";

	if( !_bPrint && !frmMain->m_asSaveFileDir.IsEmpty() )//파일 그룹 저장 mnuLeftGroupSave//210106//
		asLocalDir = frmMain->m_asSaveFileDir + "\\";

	if(!DirectoryExists(asLocalDir))
		CreateDir(asLocalDir);

	asRemoteDir	= StringReplace(asRemoteDir, "\\", "/", TReplaceFlags() << rfReplaceAll);

	memset(&mDownloadFile, 0x00, sizeof(mDownloadFile));
	wsprintf(mDownloadFile.cFileName, "%s", asFileName.c_str());
	wsprintf(mDownloadFile.cRemoteFilePath, asRemoteDir.c_str());
	wsprintf(mDownloadFile.cLocalFilePath, "%s", asLocalDir.c_str());

	if (!frmFtpControl->FuncFtpFileDownload(19, &mDownloadFile, 0)) {
		return "";
	}

	asFileName.sprintf("%s%s", mDownloadFile.cLocalFilePath, mDownloadFile.cFileName);
	return asFileName;
}
// ---------------------------------------------------------------------------
void __fastcall TfrmPrintSetting::funcResaveImage(AnsiString _asFilePath, int _nIndex, bool _bPreview)
{
	double 	dRate = 0.0;
	double 	dRateW = 0.0;
	double 	dRateH = 0.0;
	int		nImageIncW = 0;
	int		nImageIncH = 0;
	int 	nExtType = 0;
	AnsiString asExt = ExtractFileExt(_asFilePath);
	AnsiString asTempFile = "";

//200928//
//	if(asExt.UpperCase() == ".TIF")
//		nExtType = 1;
//	else if(asExt.UpperCase() == ".JPG")
//		nExtType = 2;
//	else if(asExt.UpperCase() == ".BMP")
//		nExtType = 3;
//	else if(asExt.UpperCase() == ".PNG")
//		nExtType = 4;

	if( !_bPreview )
		asTempFile = frmMain->PRINTPATH + "Print" + IntToStr(_nIndex) + ".jpg";
	else
		asTempFile = frmMain->ROOTPATH + "tmp\\tmp" + IntToStr(_nIndex) + ".jpg";

//200928//	if(nExtType == 1)//Tif
	{
		int nImageW = 0;
		int nImageH = 0;

		if(i_DIB != NULL)
		{
			FreeImage_Unload(i_DIB);
			i_DIB = NULL;
		}

		try {
			i_DIB = FreeImage_Load(FreeImage_GetFileType(_asFilePath.c_str(), 16), _asFilePath.c_str());
			nImageW = FreeImage_GetWidth(i_DIB);
			nImageH = FreeImage_GetHeight(i_DIB);
		} catch (Exception &exception) {
			AnsiString strMsg = "Exception is broken up to load mGetImageInfo.m_DIB";
			frmMsg->funcMessageDlg("이미지 DIB 확인:", strMsg, 2);
			return;
		}

		if (!i_DIB) {
			AnsiString strMsg = "i_DIB is NULL";
			frmMsg->funcMessageDlg("이미지 DIB 확인:", strMsg, 2);
			return;
		}

		//################################################################
		Graphics::TBitmap *printBmp = new Graphics::TBitmap();
		printBmp->PixelFormat = pf24bit;

		printBmp->Width 	= nImageW;
		printBmp->Height 	= nImageH;

		::SetStretchBltMode(printBmp->Canvas->Handle, HALFTONE);
		::StretchDIBits(printBmp->Canvas->Handle, 0, 0, nImageW, nImageH, 0, 0, nImageW, nImageH, FreeImage_GetBits(i_DIB), FreeImage_GetInfo(i_DIB), DIB_RGB_COLORS, SRCCOPY);
		//################################################################

		TJPEGImage *saveJpg;
		//Save To Jpg
		saveJpg = new TJPEGImage();
		saveJpg->CompressionQuality = 70;
		saveJpg->Compress();
		//saveJpg->PixelFormat = pf24bit;
		saveJpg->Assign(printBmp);
		saveJpg->SaveToFile(asTempFile);
		delete saveJpg;
		saveJpg = NULL;
	}
//200928//
//	else if(nExtType == 2)//Jpg
//	{
//		Graphics::TBitmap *printBmp = new Graphics::TBitmap();
//		TJPEGImage *imgJpg = new TJPEGImage();
//		imgJpg->LoadFromFile(_asFilePath);
//		printBmp->Assign(imgJpg);
//		printBmp->PixelFormat = pf24bit;
//		printBmp->SaveToFile(asTempFile);
//		delete imgJpg;
//		imgJpg = NULL;
//		delete printBmp;
//		printBmp = NULL;
//	}
//	else if(nExtType == 3)//Bmp
//	{
//		RenameFile(_asFilePath.c_str(), asTempFile.c_str());
//	}
//	else if(nExtType == 4)//Png
//	{
//		Graphics::TBitmap *bmpTemp = new Graphics::TBitmap();
//		TPngImage *imgPng = new TPngImage();
//		imgPng->LoadFromFile(_asFilePath);
//		bmpTemp->Assign(imgPng);
//		bmpTemp->PixelFormat = pf24bit;
//		bmpTemp->SaveToFile(asTempFile);
//		delete imgPng;
//		imgPng = NULL;
//		delete bmpTemp;
//		bmpTemp = NULL;
//	}

	DeleteFile(_asFilePath);
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintSetting::funcResizeDownloadImage(AnsiString _asFilePath, int _nIndex)
{
	double 	dRate = 0.0;
	double 	dRateW = 0.0;
	double 	dRateH = 0.0;
	int		nImageIncW = 0;
	int		nImageIncH = 0;
	int 	nExtType = 0;
	AnsiString asExt = ExtractFileExt(_asFilePath);

//200928//
//	if(asExt.UpperCase() == ".TIF")
//		nExtType = 1;
//	else if(asExt.UpperCase() == ".JPG")
//		nExtType = 2;
//	else if(asExt.UpperCase() == ".BMP")
//		nExtType = 3;
//	else if(asExt.UpperCase() == ".PNG")
//		nExtType = 4;

	if(frmMain->PRINTPATH.IsEmpty())
    	frmMain->PRINTPATH       = frmMain->ROOTPATH + "Print\\";//M//191119

	AnsiString asTempFile = frmMain->PRINTPATH + "Print" + IntToStr(_nIndex) + ".jpg";
//200928//	if(nExtType == 1)//Tif
	{
		Graphics::TBitmap *bmpTemp = new Graphics::TBitmap();
		FIBITMAP* 			i_DIB;
		BITMAPINFO*			mBitMapInfo;
		int nImageW = 0;
		int nImageH = 0;

		try {
			i_DIB = FreeImage_Load(FreeImage_GetFileType(_asFilePath.c_str(), 16), _asFilePath.c_str());
			nImageW = FreeImage_GetWidth(i_DIB);
			nImageH	= FreeImage_GetHeight(i_DIB);
		} catch (Exception &exception) {
			AnsiString strMsg = "Exception is broken up to load mGetImageInfo.m_DIB";
			frmMsg->funcMessageDlg("이미지 DIB 확인:", strMsg, 2);
			return;
		}

		if (!i_DIB) {
			AnsiString strMsg = "i_DIB is NULL";
			frmMsg->funcMessageDlg("이미지 DIB 확인:", strMsg, 2);
			return;
		}

		//################################################################
		Graphics::TBitmap *printBmp = new Graphics::TBitmap();
		printBmp->PixelFormat = pf24bit;

		printBmp->Width 	= nImageW;
		printBmp->Height 	= nImageH;

		::SetStretchBltMode(printBmp->Canvas->Handle, HALFTONE);
		::StretchDIBits(printBmp->Canvas->Handle, 0, 0, nImageW, nImageH, 0, 0, nImageW, nImageH, FreeImage_GetBits(frmMain->mGetImageInfo.m_DIB), FreeImage_GetInfo(frmMain->mGetImageInfo.m_DIB), DIB_RGB_COLORS, SRCCOPY);
		//################################################################

		TJPEGImage *saveJpg;
		//Save To Jpg
		saveJpg = new TJPEGImage();
		saveJpg->CompressionQuality = 70;
		saveJpg->Compress();
		//saveJpg->PixelFormat = pf24bit;
		saveJpg->Assign(printBmp);
		saveJpg->SaveToFile(asTempFile);
		delete saveJpg;
		saveJpg = NULL;
	}
//200928//
//	else if(nExtType == 2)//Jpg
//	{
//		Graphics::TBitmap *printBmp = new Graphics::TBitmap();
//		TJPEGImage *imgJpg = new TJPEGImage();
//		imgJpg->LoadFromFile(_asFilePath);
//		printBmp->Assign(imgJpg);
//		printBmp->PixelFormat = pf24bit;
//		printBmp->SaveToFile(asTempFile);
//		delete imgJpg;
//		imgJpg = NULL;
//		delete printBmp;
//		printBmp = NULL;
//	}
//	else if(nExtType == 3)//Bmp
//	{
//	}
//	else if(nExtType == 4)//Png
//	{
//	}

	DeleteFile(_asFilePath);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::funcDogakLinePaint()
{
	HDC pDraw1    		= bmpLoad->Canvas->Handle;
	TCanvas  *pCanvas   = bmpLoad->Canvas;

	HPEN pen1, pen2;
	HFONT m_font, m_fontA;
	HFONT hOldFont, hOldFontA;
	TPoint start, end;
	double scaleW, scaleH;

	pen1   = ::CreatePen(PS_SOLID, 1, 0x000000ff);
	::SelectObject(pDraw1, pen1);
	int oldro1 = ::SetROP2(pDraw1, R2_COPYPEN);

	if(m_vDOGAKLINE_Bck.size() > 0)
	{
		for (int i=0; i<(int)m_vDOGAKLINE_Bck.size(); i++)
		{
			start 	= m_vDOGAKLINE_Bck[i].tpMapStt;
			end		= m_vDOGAKLINE_Bck[i].tpMapEnd;
			::MoveToEx(pDraw1, start.x, start.y, NULL);
			::LineTo(pDraw1, end.x, end.y);
			//::Rectangle(pbRect6->Canvas->Handle, (start.x-3), start.y-3, start.x+3, start.y+3);
			::SetROP2 (pDraw1, oldro1);
			//::DeleteObject( pen );
		}

		::SetROP2 (pDraw1, oldro1);
		::DeleteObject( pen1 );
	}

	if(m_vDOGAKLINE_Bck.size() > 0)
	{
		AnsiString asValueW = "500";
		AnsiString asValueH = "400";//"4\r\n0\r\n0";
		AnsiString asValueHelp = "<본 도각선은 1200 도각선으로 참고용입니다.>";
		TPoint tpText1, tpText2;
		int nTextWLen = asValueW.Length();
		int nTextHLen = asValueH.Length();

		//---
		tpText1	= m_vDOGAKLINE_Bck[0].tpMapStt;
		tpText2 = m_vDOGAKLINE_Bck[(m_vDOGAKLINE_Bck.size()/2)].tpMapStt;

		int fontwidth = 14;//[TODO]//frmIniControl->mUserSetIniInfo.nDoc0_V5;
		//---
		m_font    = ::CreateFont(fontwidth, 0, 0, 0, FW_HEAVY, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "나눔고딕" );
		hOldFont  = (HFONT)::SelectObject(pDraw1, m_font);
		::SetBkMode(pDraw1, TRANSPARENT);
		::SetTextColor(pDraw1, 0x000000ff);//200313//Color적용//frmIniControl->mUserSetIniInfo.ulDoc0_V5_1);
		pCanvas->TextOutA(tpText1.x + 8, tpText1.y + 1, asValueW);
		pCanvas->TextOutA(tpText1.x + 2, tpText1.y - 12, asValueHelp);
		::SelectObject(pDraw1, hOldFont);
		::DeleteObject(m_font);

		//---
		m_fontA   = ::CreateFont(fontwidth, 0, 2700, 2700, FW_HEAVY, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "나눔고딕" );
		hOldFontA = (HFONT)::SelectObject(pDraw1, m_fontA);
		::SetBkMode(pDraw1, TRANSPARENT);
		::SetTextColor(pDraw1, 0x000000ff);//200313//Color적용//frmIniControl->mUserSetIniInfo.ulDoc0_V5_1);
		pCanvas->TextOutA(tpText2.x + 12, tpText2.y + 8, asValueH);
		::SelectObject(pDraw1, hOldFontA);
		::DeleteObject(m_fontA);

		//---
		AnsiString asValueMove = "(원하는 위치로 도각선을 드래그하여 사용하세요.)";
		pen2   = ::CreatePen(PS_SOLID, 1, 0x00ff0000);//200313//color변경//0x0000f2ff->0x00ff0000
		::SelectObject(pDraw1, pen2);
		int oldro2 = ::SetROP2(pDraw1, R2_COPYPEN);
		::SetBkMode(pDraw1, TRANSPARENT);
		::SetTextColor(pDraw1, 0x00ff0000);//200313//color변경//0x0000f2ff->0x00ff0000
		pCanvas->TextOutA(tpText1.x + 2, tpText1.y - 24, asValueMove);
		::SelectObject(pDraw1, hOldFontA);
		::DeleteObject(m_fontA);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::funcMapPointPaint()
{
//	IMGMAPPOINT = new Graphics::TBitmap();
//	HDC pDraw    		= IMGMAPPOINT->Canvas->Handle;
//	TCanvas  *pCanvas   = IMGMAPPOINT->Canvas;
//
//	HPEN pen;
//	HFONT m_font;
//	HFONT hOldFont, hOldFontA;
//	TPoint start, end;
//	double scaleW, scaleH;
//
//	pen   = ::CreatePen(PS_SOLID, 1, 0x000000ff);
//	::SelectObject(pDraw, pen);
//	int oldro = ::SetROP2(pDraw, R2_COPYPEN);
//
//	start.x = 0;//frmMain->shpMapPoint->Left;
//	start.y = 0;//frmMain->shpMapPoint->Top;
//	end.x   = frmMain->shpMapPoint->Width;//frmMain->shpMapPoint->Left + frmMain->shpMapPoint->Width;
//	end.y   = frmMain->shpMapPoint->Height;//frmMain->shpMapPoint->Top + frmMain->shpMapPoint->Height;
//
//	::Rectangle(pDraw, start.x, start.y, end.x, end.y);
//	::SetROP2 (pDraw, oldro);
//	::DeleteObject( pen );
//
//
//	AnsiString asValue = frmMain->lblMapPoint->Caption;
//	int nTextX = 0;
//	int nTextY = 0;
//	TPoint tpText;
//	int nTextLen = asValue.Length();
//	int fontwidth = 9;
//
//	tpText.x = 4;//frmMain->lblMapPoint->Left;
//	tpText.y = 2;//frmMain->lblMapPoint->Top;
//
//	m_font    = ::CreateFont(fontwidth, 0, 0, 0, FW_HEAVY, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "나눔고딕" );
//	hOldFont  = (HFONT)::SelectObject(pDraw, m_font);
//
//	::SetBkMode(pDraw, TRANSPARENT);
//	if(frmMain->m_bOtherJibun)
//		::SetTextColor(pDraw, clBlue);
//	else
//  		::SetTextColor(pDraw, clRed);
//
//	pCanvas->TextOutA(tpText.x, tpText.y, asValue);
//
//	::SelectObject(pDraw, hOldFont);
//	::DeleteObject(m_font);
//
//	AnsiString asDestFile = frmMain->ROOTPATH + "tmp\\IMGMAPPOINT.bmp";
//	if(FileExists(asDestFile))
//		DeleteFile(asDestFile);
//
//	Graphics::TBitmap  	*bmpTemp = new Graphics::TBitmap();
//	bmpTemp->PixelFormat = 24;
//	bmpTemp->Assign(IMGMAPPOINT);
//	bmpTemp->SaveToFile(asDestFile);
//
//	::AlphaBlend(bmpLoad->Canvas->Handle, start.x, start.y, end.x - start.x, end.y - start.y, IMGMAPPOINT->Canvas->Handle, 0, 0, IMGMAPPOINT->Width, IMGMAPPOINT->Height, frmMain->flagbf);
//
//	delete bmpTemp;
//	bmpTemp = NULL;
}
//---------------------------------------------------------------------------

//preview 이미지 생성
void __fastcall TfrmPrintSetting::funcCreatePreviewImg()
{
//
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::funcGetPrinterList()
{
	TPrinter *printer = new TPrinter();
	m_sPrinterList    = new TStringList();
	m_sPaperTypeList  = new TStringList();

	m_pPrinter        = new TPrinter();

	cboPrinterList->Clear();

	m_sPrinterList = (TStringList *)printer->Printers;

	for(int i = 0; i < m_sPrinterList->Count; i++)
	{
		cboPrinterList->Items->Add(m_sPrinterList->Strings[i]);
	}

	//PaperType
	m_sPaperTypeList->Add("A4");
	m_sPaperTypeList->Add("A3");
	m_sPaperTypeList->Add("A2");

	if(cboPrinterList->Items->Count > 0)
	{
		funcGetPrintSetting();
	}

}
//---------------------------------------------------------------------------

//http://www.borlandforum.com/impboard/impboard.dll?action=read&db=del_tip&no=170
int __fastcall TfrmPrintSetting::funcGetPaperSize(void)
{
	wchar_t Device[256], Driver[256], Port[256];
    THandle hDMode;
    TDevMode *ADevMode;
	Printer()->GetPrinterA(Device, Driver, Port, hDMode);
    ADevMode = (TDevMode *)GlobalLock((void *)hDMode);
    GlobalUnlock((void *)hDMode);
    return ADevMode->dmPaperSize;
	//return 1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::funcSetPaperSize(int pSize)
{
//	char Device[256], Driver[256], Port[256];
//	THandle hDMode;
//
//	TDevMode *ADevMode;
//	Printer()->GetPrinter(Device, Driver, Port, hDMode);
//	ADevMode = (TDevMode *)GlobalLock((void *)hDMode);
//	ADevMode->dmPaperSize = pSize;
//	GlobalUnlock((void *)hDMode);
//	Printer()->SetPrinter(Device, Driver, Port, hDMode);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::funcGetPrintSetting()
{
	wchar_t Device[256], Driver[256], Port[256];
	THandle hDMode;
	TDevMode *ADevMode;
	m_pPrinter->GetPrinterA(Device, Driver, Port, hDMode);
	ADevMode = (TDevMode *)GlobalLock((void *)hDMode);
	GlobalUnlock((void *)hDMode);

	//PrinterName
	//190801//프로그램 종료시까지 선택한 프린터명을 기억하기//
	if(frmMain->m_asPrinterName.IsEmpty())
		cboPrinterList->ItemIndex = funcGetBasicPrinter(ADevMode->dmDeviceName);
	else
		cboPrinterList->ItemIndex = funcGetBasicPrinter(frmMain->m_asPrinterName);
	cboPrinterList->Text = m_sPrinterList->Strings[cboPrinterList->ItemIndex];

	ADevMode->dmPaperSize = funcGetPaperSize();
	//PaperSize
	cboPaperType->ItemIndex = funcGetPaperIndex(ADevMode->dmPaperSize);
	cboPaperType->Text = m_sPaperTypeList->Strings[cboPaperType->ItemIndex];
	cboPaperTypeClick(NULL);

	int nScale  = ADevMode->dmScale;
	//200424//프린터 정보가 상이 할때, ADevMode->dmScale가 1 초과여서 ItemIndex를 제대로 설정 못함//
	if(nScale <= 1)
		cboPrintScale->ItemIndex = nScale;
	else
		cboPrintScale->ItemIndex = 1;//페이지맞춤(기본)//

	int nCopies = ADevMode->dmCopies;
//	int nPos    = ADevMode->dmPosition
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintSetting::funcSetPrintSetting()
{
    wchar_t Device[256], Driver[256], Port[256];
    THandle hDMode;

	TDevMode *ADevMode;
	m_pPrinter->GetPrinterA(Device, Driver, Port, hDMode);
	ADevMode = (TDevMode *)GlobalLock((void *)hDMode);
	memset(ADevMode->dmDeviceName, 0x00, sizeof(ADevMode->dmDeviceName));
	swprintf(ADevMode->dmDeviceName, L"%s", funcSetBasicPrinter(cboPrinterList->ItemIndex));
	ADevMode->dmPaperSize = funcSetPaperIndex(cboPaperType->ItemIndex);
	ADevMode->dmScale = cboPrintScale->ItemIndex;
	GlobalUnlock((void *)hDMode);
	Printer()->SetPrinterA(Device, Driver, Port, hDMode);
}
//---------------------------------------------------------------------------

int __fastcall TfrmPrintSetting::funcGetBasicPrinter(AnsiString _asPrinterName)
{
	int nRet = 0;

	for(int i = 0; i < (int)m_sPrinterList->Count; i++)
	{
		if(m_sPrinterList->Strings[i] == _asPrinterName)
		{
			nRet = i;
			break;
		}
	}

	return nRet;
}
//---------------------------------------------------------------------------

AnsiString __fastcall TfrmPrintSetting::funcSetBasicPrinter(int _nIndex)
{
	return AnsiString(m_sPrinterList->Strings[_nIndex]);
}
//---------------------------------------------------------------------------

int __fastcall TfrmPrintSetting::funcGetPaperIndex(int _nPaperSize)
{
	int nIndex = 0;
	switch(_nPaperSize)
	{
		case 9://A4
			nIndex = 0;
			break;
		case 8://A3
			nIndex = 1;
			break;
		case 66://A2
			nIndex = 2;
			break;
		//기타 문서는 PrintSetting.cpp 맨 위를 참고//
	}

	return nIndex;
}
//---------------------------------------------------------------------------

int __fastcall TfrmPrintSetting::funcSetPaperIndex(int _nIndex)
{
	int nPaperSize = 9;
	switch(_nIndex)
	{
		case 0://A4
			nPaperSize = 9;
			break;
		case 1://A3
			nPaperSize = 8;
			break;
		case 2://A2
			nPaperSize = 66;
			break;
		//기타 문서는 PrintSetting.cpp 맨 위를 참고//
	}

	return nPaperSize;
}
//---------------------------------------------------------------------------

//int __fastcall TfrmPrintSetting::funcGetBasicPaperSize(AnsiString _asPrinterName)
//{
//	int nRet = 0;
//
//	for(int i = 0; i < (int)m_sPrinterList->Count; i++)
//	{
//		if(m_sPrinterList->Strings[i] == _asPrinterName)
//		{
//			nRet = i;
//			continue;
//        }
//	}
//
//	return nRet;
//}
////---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::cboPaperTypeClick(TObject *Sender)
{
	if(palWait->Visible)//210111//
		return;

	//폐쇄지적도 인쇄양식 세로이미지 기준
	if( nDocNo == 7 && chkDoc7Form->Checked )//지적도//양식
	{
		//Preview Panel
		nPaperW = 190;
		nPaperH = 210;
	}
	else
	{
		//200925//
		if(nWidth < nHeight)//Portrait
		{
			rbPortrait->Checked		= true;
			rbLandscape->Checked 	= false;
		}
		else//Landscape
		{
			rbPortrait->Checked		= false;
			rbLandscape->Checked 	= true;
        }

		//Preview Panel
		if(cboPaperType->ItemIndex == 0)
		{
			if(rbPortrait->Checked)
			{
				nPaperW 	= 210;
				nPaperH 	= 297;
			}
			else
			{
				nPaperW 	= 297;
				nPaperH 	= 210;
			}
		}
		else if(cboPaperType->ItemIndex == 1)
		{
			if(rbPortrait->Checked)
			{
				nPaperW 	= 297;
				nPaperH 	= 420;
			}
			else
			{
				nPaperW 	= 420;
				nPaperH 	= 297;
			}
		}
		else if(cboPaperType->ItemIndex == 2)
		{
			if(rbPortrait->Checked)
			{
				nPaperW 	= 420;
				nPaperH 	= 594;
			}
			else
			{
				nPaperW 	= 594;
				nPaperH 	= 420;
			}
		}

		//200925//[TODO]
		//200813//TEST//old
		if(nWidth < nHeight)//Portrait
		{
			if(nPaperW > nPaperH)//190807//44760//Doc15
			{
				int nTemp = nPaperW;
				nPaperW   = nPaperH;
				nPaperH   = nTemp;
			}
		}
		//200925//[TODO]
	}

	if( !bFromShow )
		funcGetPrintPreview();//190401
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::cboPrintScaleClick(TObject *Sender)
{
	if(palWait->Visible)//210111//
		return;

	if( !bFromShow )
	{
		if(cboPrintScale->ItemIndex != 2)
			funcGetPrintPreview();//190401
		else
			funcFileAllPart();

		if(cboPrintScale->ItemIndex == 0){//실제크기
			imgPrintPreview->Stretch = false;
		}
		else{
			imgPrintPreview->Stretch = true;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::chkDoc8Page2Click(TObject *Sender)
{
	if(palWait->Visible)//210111//
		return;

	if(Sender == lblDoc8Page2_1 || Sender == lblDoc8Page2_2)//210111
	{
    	chkDoc8Page2->Checked	= !chkDoc8Page2->Checked;
	}

	if (nDocNo == 8 && chkDoc8Page2->Checked)
	{
		pnlPaper2->Visible 			= true;
		cboPaperType->ItemIndex 	= 0;//A4
		cboPrintScale->ItemIndex 	= 1;//페이지맞춤(기본)//
		cboPaperType->Enabled 		= false;
		rbPortrait->Enabled			= false;//200914//
		rbLandscape->Enabled		= false;//200914//
		cboPrintScale->Enabled 		= false;
		pnlPosition->Enabled 		= false;
	}
	else
	{
		pnlPaper2->Visible 			= false;
		cboPaperType->Enabled 		= true;
		rbPortrait->Enabled			= true;//200914//
		rbLandscape->Enabled		= true;//200914//
		cboPrintScale->Enabled 		= true;
		pnlPosition->Enabled 		= true;
	}

	cboPaperTypeClick(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::chkDoc8StampClick(TObject *Sender)
{
	if(palWait->Visible)//210111//
		return;

	if( !bFromShow )
		funcGetPrintPreview();//190401
}
//---------------------------------------------------------------------------
//생성한 preview 이미지 보여주기
void __fastcall TfrmPrintSetting::funcGetPrintPreview()
{
	AnsiString asPrintFile = "";

	////////////////////////////////////////////////////////////////////////////
	if (DirectoryExists(frmMain->PRINTPATH))//print 하위 파일들 삭제하기
		eFunc->DeleteFileinDir(frmMain->PRINTPATH);
	if (!DirectoryExists(frmMain->PRINTPATH))
		CreateDir(frmMain->PRINTPATH);

	m_asOrientation = "_L";//200320

	//부분인쇄//===================================
	if(frmPrintSetting->Tag == 2)
	{
		if( !(nDocNo == 7 && chkDoc7Form->Checked) )
		{
			if(nWidth < nHeight)
				funcSetPreviewPage(false);
			else
				funcSetPreviewPage(true);
		}

		int nDogakLine = frmMain->m_vDOGAKLINE.size();
		if(frmMain->m_vDOGAKLINE.size() > 0)
		{
			m_vDOGAKLINE_Bck = frmMain->m_vDOGAKLINE;
			funcDogakLinePaint();
		}

		if(frmMain->lblMapPoint->Visible && frmMain->shpMapPoint->Visible)//190625//지번표시 텍스트 > 인쇄
			funcMapPointPaint();

		asPrintFile = frmMain->PRINTPATH + "PrintRect.jpg";
		if(FileExists(asPrintFile))
			DeleteFile(asPrintFile);

		funcRectanglePreview(asPrintFile);
	}
	//인쇄//===================================
	else if(nDocNo == 8 && chkDoc8Page2->Checked)
	{
		funcPreviewPrintDoc8();
	}
	else
	{
		if( !(nDocNo == 7 && chkDoc7Form->Checked) )
		{
			if(nWidth < nHeight)
			{
				m_asOrientation = "_P";//201214
				funcSetPreviewPage(false);
			}
			else
			{
				m_asOrientation = "_L";//201214
				funcSetPreviewPage(true);
			}
		}

		int nDogakLine = frmMain->m_vDOGAKLINE.size();
		if(frmMain->m_vDOGAKLINE.size() > 0)
		{
			m_vDOGAKLINE_Bck = frmMain->m_vDOGAKLINE;
			funcDogakLinePaint();
		}

		if(frmMain->lblMapPoint->Visible && frmMain->shpMapPoint->Visible)//190625//지번표시 텍스트 > 인쇄
			funcMapPointPaint();

//210111//
//		if(frmMain->mGetImageInfo.fiformat == FIF_JPEG)//210111//
//			asPrintFile = frmMain->PRINTPATH + "PrintPreview.jpg";
//		else if(frmMain->mGetImageInfo.fiformat == FIF_TIFF)
//			asPrintFile = frmMain->PRINTPATH + "PrintPreview.tif";

		asPrintFile = frmMain->PRINTPATH + "PrintPreview.jpg";
		if(FileExists(asPrintFile))
			DeleteFile(asPrintFile);

		funcFilePreview(asPrintFile);
	}//_nDoc !=7 && _nDoc !=8
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintSetting::funcPreviewPrintDoc8()
{
	frmMain->m_asSaveFileDir = "";//190829

	AnsiString asPrintFile = "";//print filename

	DOCUMENT08_STRUCT   *mDoc8Struct;
	mDoc8Struct = (DOCUMENT08_STRUCT*)frmMain->mSearchNode.tSelectNode->Data;
	if (!mDoc8Struct) return;

	//=================================
	funcSetWaitWindows(true);//210111//
	//=================================

	if(!strcmp(mDoc8Struct->SINGU_NAME, "카드"))//카드이면 앞뒤장 출력
	{
		bDoc8Card = true;

		if(nWidth < nHeight)
			funcSetPreviewPageDoc8Page2(false);
		else
			funcSetPreviewPageDoc8Page2(true);


		TTreeNode*	tGetNode;
		bool bBack  = false;
		int  nRet 	= -1;

		if(!strcmp(mDoc8Struct->ONOFF_CODE, "1"))//뒷면
			bBack = true;

		AnsiString asDownloadFileName = "";//download filename in FTP

		if(bBack)//현재 Loadimage : 뒷면
		{
			//앞면-다운로드
			tGetNode = frmMain->mSearchNode.tSelectNode->GetPrev();

			if(tGetNode != NULL && eTree->funcClickNodeToDocNum(tGetNode) == 8)//210128//뒷면 없는 카드대장인 경우, GetNext 하면 같은 폴더에 없어도 tree의 next를 가져오기에 문제 발생//
			{
				mDoc8Struct = (DOCUMENT08_STRUCT*)tGetNode->Data;

				try {
					nRet	= -1;//210128//

					asDownloadFileName = funcDownloadImage(true, mDoc8Struct->PATH_NAME);//210106//

				}
				__finally {
					if( !asDownloadFileName.IsEmpty() )
					{
						//210208//암호화설정되었지만 암호화 안된 이미지가 있더라도 처리되도록//
						if (frmMain->INIINFO.B_ENCRYPT)
						{
							nRet	= 1;
							FREE_IMAGE_FORMAT 	fiformat	= FreeImage_GetFileType(asDownloadFileName.c_str(), 16);

							if(fiformat	== FIF_TIFF || fiformat	== FIF_JPEG || fiformat	== FIF_BMP)
								nRet = 0;
						}
						//---

						//========================================================
						//210208//#IMGMODE//비암호화 문서를 암호화 후 FTP Upload//
						if(frmMain->INIINFO.B_ENCRYPT && frmMain->INI_B_IMGMODE)
						{
							if(nRet == 0)//비암호화 문서를 암호화 후 FTP Upload//
							{
								frmMain->m_asEncLocalPathName	= asDownloadFileName;
								frmMain->m_asEncDBPathName  = (char*)mDoc8Struct->PATH_NAME;
								nRet = frmMain->funcGetFileBuffer(true);
							}
							else
							{
								nRet	= eEncrypt->FuncEncryptFile(asDownloadFileName.c_str());

								//내부 모듈을 통해 암호화된 문서인지 체크해서 복호화하기//
								if(nRet != 0)
								{
									frmMain->m_asEncLocalPathName	= asDownloadFileName;
									nRet = frmMain->funcGetFileBuffer(false);
								}
								//---

								if(nRet == 0)
								{
									AnsiString asDownloadFileNameEnc = asDownloadFileName + "_enc";
									if(FileExists(asDownloadFileNameEnc))
										DeleteFile(asDownloadFileNameEnc);
								}
							}
						}
						else//ORG
						//========================================================
						{
							//210208//#IMGMODE//암호화설정(ON)&&IMGMODE(OFF)이면 열람불가//
							//태안에 암호화,비암호화문서 혼재되어 있어서 예외처리했었으나//
							//IMGMODE를 적용하면서 원래대로 기능 복원//
							//if(nRet != 0)
							if(nRet != 0)//210224//#44760_EXCEPT
								nRet	= eEncrypt->FuncEncryptFile(asDownloadFileName.c_str());

							if(nRet == 0)
							{
								AnsiString asDownloadFileNameEnc = asDownloadFileName + "_enc";
								if(FileExists(asDownloadFileNameEnc))
									DeleteFile(asDownloadFileNameEnc);
							}
                        }
					}
				}

				if(nRet == 0)
				{
					funcResaveImage(asDownloadFileName, 1, true);
					//
					asPrintFile = frmMain->PRINTPATH + "PrintPreview1.jpg";
					if(FileExists(asPrintFile))
						DeleteFile(asPrintFile);

					funcPreviewPrintDoc8Page2Card(asPrintFile, true, true);//----------
				}
				else
				{
					//=================================
					funcSetWaitWindows(false);//210111//
					//=================================
					frmMsg->funcMessageDlg("암호화모듈확인:", "문서 암호화 모듈을 확인해주세요.", 2);
					return;
				}

				//뒷면-현재 이미지
				asPrintFile = frmMain->PRINTPATH + "PrintPreview2.jpg";
				if(FileExists(asPrintFile))
					DeleteFile(asPrintFile);

				funcPreviewPrintDoc8Page2Card(asPrintFile, false, false);//----------
			}
		}
		else//현재 Loadimage : 앞면
		{
			//앞면-현재 이미지
	        //################################################################
			asPrintFile = frmMain->PRINTPATH + "PrintPreview1.jpg";
			if(FileExists(asPrintFile))
				DeleteFile(asPrintFile);

			funcPreviewPrintDoc8Page2Card(asPrintFile, true, false);//----------

			//뒷면-다운로드
			if(frmMain->mSelectNodeFolder == frmMain->mSearchNode.tSelectNode)//'카드'라는 폴더명 클릭으로 '앞면'이 오픈된 경우//
				tGetNode = frmMain->mSearchNode.tSelectNode->GetNextChild(frmMain->mSearchNode.tSelectNode->getFirstChild());
			else
				tGetNode = frmMain->mSearchNode.tSelectNode->GetNext();

			if(tGetNode != NULL && eTree->funcClickNodeToDocNum(tGetNode) == 8)//210128//뒷면 없는 카드대장인 경우, GetNext 하면 같은 폴더에 없어도 tree의 next를 가져오기에 문제 발생//
			{
				mDoc8Struct = (DOCUMENT08_STRUCT*)tGetNode->Data;

				try {
					nRet	= -1;//210128//

					asDownloadFileName = funcDownloadImage(true, mDoc8Struct->PATH_NAME);//210106//

				}
				__finally {
					if( !asDownloadFileName.IsEmpty() )
					{
						//210208//암호화설정되었지만 암호화 안된 이미지가 있더라도 처리되도록//
						if (frmMain->INIINFO.B_ENCRYPT)
						{
							nRet	= 1;
							FREE_IMAGE_FORMAT 	fiformat	= FreeImage_GetFileType(asDownloadFileName.c_str(), 16);

							if(fiformat	== FIF_TIFF || fiformat	== FIF_JPEG || fiformat	== FIF_BMP)
								nRet = 0;
						}
						//---

						//========================================================
						//210208//#IMGMODE//비암호화 문서를 암호화 후 FTP Upload//
						if(frmMain->INIINFO.B_ENCRYPT && frmMain->INI_B_IMGMODE)
						{
							if(nRet == 0)//비암호화 문서를 암호화 후 FTP Upload//
							{
								frmMain->m_asEncLocalPathName	= asDownloadFileName;
								frmMain->m_asEncDBPathName  = (char*)mDoc8Struct->PATH_NAME;
								nRet = frmMain->funcGetFileBuffer(true);
							}
							else
							{
								nRet	= eEncrypt->FuncEncryptFile(asDownloadFileName.c_str());

								//내부 모듈을 통해 암호화된 문서인지 체크해서 복호화하기//
								if(nRet != 0)
								{
									frmMain->m_asEncLocalPathName	= asDownloadFileName;
									nRet = frmMain->funcGetFileBuffer(false);
								}
								//---

								if(nRet == 0)
								{
									AnsiString asDownloadFileNameEnc = asDownloadFileName + "_enc";
									if(FileExists(asDownloadFileNameEnc))
										DeleteFile(asDownloadFileNameEnc);
								}
							}
						}
						else//ORG
						//========================================================
						{
							//210208//#IMGMODE//암호화설정(ON)&&IMGMODE(OFF)이면 열람불가//
							//태안에 암호화,비암호화문서 혼재되어 있어서 예외처리했었으나//
							//IMGMODE를 적용하면서 원래대로 기능 복원//
							//if(nRet != 0)
							if(nRet != 0)//210224//#44760_EXCEPT
								nRet	= eEncrypt->FuncEncryptFile(asDownloadFileName.c_str());

							if(nRet == 0)
							{
								AnsiString asDownloadFileNameEnc = asDownloadFileName + "_enc";
								if(FileExists(asDownloadFileNameEnc))
									DeleteFile(asDownloadFileNameEnc);
							}
                        }
					}
				}

				if(nRet == 0)
				{
					funcResaveImage(asDownloadFileName, 2, true);

					asPrintFile = frmMain->PRINTPATH + "PrintPreview2.jpg";
					if(FileExists(asPrintFile))
						DeleteFile(asPrintFile);

					funcPreviewPrintDoc8Page2Card(asPrintFile, false, true);//----------
				}
				else
				{
					//=================================
					funcSetWaitWindows(false);//210111//
					//=================================
					frmMsg->funcMessageDlg("암호화모듈확인:", "문서 암호화 모듈을 확인해주세요.", 2);
					return;
				}
			}
			else//210128//카드대장 앞면 혹은 뒷면 없음을 알림//
			{
				frmMsg->funcMessageDlg("파일부재 알림:", "카드대장 뒷면이 존재하지 않습니다.", 3);
            }
		}

		m_asOrientation	= "_L";

	}
	else//부책//카드 아닐 때 A4 한장을 분할해서 출력
	{
		bDoc8Card = false;

		if(nWidth < nHeight)
			funcSetPreviewPageDoc8Page2(true);
		else
			funcSetPreviewPageDoc8Page2(false);

		AnsiString asPrintFile1 = frmMain->PRINTPATH + "PrintPreview1.jpg";//preview filename
		AnsiString asPrintFile2 = frmMain->PRINTPATH + "PrintPreview2.jpg";//preview filename
		if(FileExists(asPrintFile1))
			DeleteFile(asPrintFile1);

		if(FileExists(asPrintFile2))
			DeleteFile(asPrintFile2);

		funcPreviewPrintDoc8Page2Etc(asPrintFile1, asPrintFile2);//----------

		m_asOrientation	= "_P";
	}

	//=================================
	funcSetWaitWindows(false);//210111//
	//=================================
}
//---------------------------------------------------------------------------
//201223//
//void __fastcall TfrmPrintSetting::funcFilePreview(AnsiString _asPrintFile)
//{
//	int nPnlW = pnlPaper->Width - 2;
//	int nPnlH = pnlPaper->Height - 2;
//	int nPrintW = 0;
//	int nPrintH = 0;
//
//	int nPreviewL	= 0;
//	int nPreviewT 	= 0;
//	int nPreviewW	= 0;
//	int nPreviewH	= 0;
//
//	Graphics::TBitmap *printBmp = new Graphics::TBitmap();
//	printBmp->PixelFormat = pf24bit;
//
//	////////////////////////////////
//	nPrintW	= nPaperW * dMMtoPixelW;
//	nPrintH	= nPaperH * dMMtoPixelH;
//	printBmp->Width 	= nPrintW;
//	printBmp->Height 	= nPrintH;
//
//	nPreviewW	= nPrintW / dMMtoPixelW;
//	nPreviewH	= nPrintH / dMMtoPixelH;
//
//	if(cboPrintScale->ItemIndex == 1)//페이지맞춤(기본)//
//	{
//		//################################################################
//		::SetStretchBltMode(printBmp->Canvas->Handle, HALFTONE);
//		::StretchDIBits(printBmp->Canvas->Handle, 0, 0, nPrintW, nPrintH, 0, 0, nWidth, nHeight, FreeImage_GetBits(frmMain->mGetImageInfo.m_DIB), FreeImage_GetInfo(frmMain->mGetImageInfo.m_DIB), DIB_RGB_COLORS, SRCCOPY);
//		//################################################################
//	}
//	else if(cboPrintScale->ItemIndex == 0)//실제크기//
//	{
//		int nLeft = 0;
//		int nTop = 0;
//		int nRow = (nPosition - 1) / 3;
//		int nCol = (nPosition - 1) % 3;
//
//		//Image to Save
//		switch(nRow)
//		{
//			case 0:		nTop  = nHeight - nPrintH;		break;
//			case 1:     nTop  = (nHeight - nPrintH) / 2;	break;
//			case 2:     nTop  = 0;		break;
//		}
//		switch(nCol)
//		{
//			case 0:		nLeft = 0;		break;
//			case 1:     nLeft = (nWidth - nPrintW) / 2;	break;
//			case 2:     nLeft = nWidth - nPrintW;         break;
//		}
//
//		//Preview
//		switch(nRow)
//		{
//			case 0:		nPreviewT  	= nPaperH - nPreviewH;		break;
//			case 1:     nPreviewT  	= (nPaperH - nPreviewH) / 2;	break;
//			case 2:     nPreviewT  	= 0;		break;
//		}
//
//		switch(nCol)
//		{
//			case 0:		nPreviewL 	= 0;		break;
//			case 1:     nPreviewL 	= (nPaperW - nPreviewW) / 2;	break;
//			case 2:     nPreviewL 	= nPaperW - nPreviewW;         break;
//		}
//
//		//201222//
//		if(nLeft < 0)	nLeft	= 0;
//		if(nTop < 0)	nTop	= 0;
//
//		//################################################################
//		::SetStretchBltMode(printBmp->Canvas->Handle, HALFTONE);
//		::StretchDIBits(printBmp->Canvas->Handle, 0, 0, nPrintW, nPrintH, nLeft, nTop, nPrintW, nPrintH, FreeImage_GetBits(frmMain->mGetImageInfo.m_DIB), FreeImage_GetInfo(frmMain->mGetImageInfo.m_DIB), DIB_RGB_COLORS, SRCCOPY);
//		//################################################################
//	}
//
//	//==========================================================================
//	//구대장_스탬프//
//	if(nDocNo == 8 && chkDoc8Stamp->Checked)
//	{
//		double dBmRate = (double)printBmp->Height / (double)printBmp->Width;
//		dBmRate = RoundTo(dBmRate, -2) * 100;
//		int nStampL = (printBmp->Width * 0.55);
//		int nStampT = (printBmp->Height * 0.88);
//		int nStampW = (frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Width)*dBmRate/100;
//		int nStampH = (frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Height)*dBmRate/100;
//		::AlphaBlend(printBmp->Canvas->Handle, nStampL, nStampT, nStampW, nStampH, frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Canvas->Handle, 0, 0, frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Width, frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Height, frmMain->flagbf);
//	}
//
//	//================================================================================
//	if(frmMain->INIUSERSETINFO.B_WATERMARK)//200421//44770//WaterMark
//	{
//		HDC 	pDraw		= printBmp->Canvas->Handle;
//		TCanvas *pCanvas   	= printBmp->Canvas;
//
//		HPEN pen;
//		HFONT m_font;
//		HFONT hOldFont, hOldFontA;
//
//		TPoint tpText;
//		int fontwidth = 24;//48;
//		AnsiString asLabel	= "";
//		AnsiString asDepart	= frmMain->USERINI->ReadString("USER_CONFIG", "DEPART", "");
//		AnsiString asDate	= Now().FormatString("yyyy.mm.dd hh:mm:ss");
//		if(asDepart.IsEmpty())
//			asLabel.sprintf("인쇄:%s(%s)", frmMain->m_asCurrentNm, asDate);
//		else
//			asLabel.sprintf("인쇄:%s/%s(%s)", frmMain->m_asCurrentNm, asDepart, asDate);
//
//		m_font    = ::CreateFont(fontwidth, 0, 0, 0, FW_HEAVY, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "나눔고딕" );
//		hOldFont  = (HFONT)::SelectObject(pDraw, m_font);
//		::SetBkMode(pDraw, TRANSPARENT);
//		::SetTextColor(pDraw, clBlue);
//		pCanvas->TextOutA(30, 30, asLabel);
//		::SelectObject(pDraw, hOldFont);
//		::DeleteObject(m_font);
//	}
//
//	//Save To Jpg
//	TJPEGImage *saveJpg = new TJPEGImage();
//	saveJpg->CompressionQuality = 70;
//	saveJpg->Compress();
//	//saveJpg->PixelFormat = pf24bit;
//	saveJpg->Assign(printBmp);
//	saveJpg->SaveToFile(_asPrintFile);
//
//
//	if(nDocNo == 7 && chkDoc7Form->Checked)
//	{
//		imgDoc7Preview->Picture->Bitmap->Handle	= NULL;
//		imgDoc7Preview->Picture					= NULL;
//		imgDoc7Preview->Picture->Bitmap->Width	= nPreviewW;
//		imgDoc7Preview->Picture->Bitmap->Height	= nPreviewH;
//
//		SetStretchBltMode(imgDoc7Preview->Canvas->Handle, HALFTONE);
//		HDC tmBmHd    = printBmp->Canvas->Handle;
//		StretchBlt(imgDoc7Preview->Canvas->Handle, 0, 0, nPreviewW, nPreviewH, tmBmHd, 0, 0, nPrintW, nPrintH, SRCCOPY);
//
//		pnlDoc7ImgPreview->Left					= 1;
//		pnlDoc7ImgPreview->Top					= 1;
//		pnlDoc7ImgPreview->Width				= nPreviewW;
//		pnlDoc7ImgPreview->Height				= nPreviewH;
////		imgDoc7Preview->Stretch					= true;
//	}
//	else
//	{
//		imgPrintPreview->Picture->Bitmap->Handle	= NULL;
//		imgPrintPreview->Picture					= NULL;
//		imgPrintPreview->Picture->Bitmap->Width		= nPreviewW;
//		imgPrintPreview->Picture->Bitmap->Height	= nPreviewH;
//
//		SetStretchBltMode(imgPrintPreview->Canvas->Handle, HALFTONE);
//		HDC tmBmHd    = printBmp->Canvas->Handle;
//		StretchBlt(imgPrintPreview->Canvas->Handle, 0, 0, nPreviewW, nPreviewH, tmBmHd, 0, 0, nPrintW, nPrintH, SRCCOPY);
//
//		pnlPreviewImg->Left							= nPreviewL+1;
//		pnlPreviewImg->Top							= nPreviewT+1;
//		pnlPreviewImg->Width						= nPreviewW;
//		pnlPreviewImg->Height						= nPreviewH;
////		imgPrintPreview->Stretch					= true;
//	}
//
//	delete saveJpg;
//	saveJpg = NULL;
//
//	delete printBmp;
//	printBmp = NULL;
//
//	if ( printDIB != NULL)
//	{
//		FreeImage_Unload(printDIB);
//		printDIB = NULL;
//	}
//}
////---------------------------------------------------------------------------
void __fastcall TfrmPrintSetting::funcFilePreview(AnsiString _asPrintFile)
{
	int nPnlW = pnlPaper->Width - 2;
	int nPnlH = pnlPaper->Height - 2;
	int nPrintW = 0;
	int nPrintH = 0;

	int nPreviewL	= 0;
	int nPreviewT 	= 0;
	int nPreviewW	= 0;
	int nPreviewH	= 0;

	Graphics::TBitmap *printBmp = new Graphics::TBitmap();
	printBmp->PixelFormat = pf24bit;

	//=================================
	funcSetWaitWindows(true);//210111//
	//=================================

	////////////////////////////////
	nPrintW	= nPaperW * dMMtoPixelW;
	nPrintH	= nPaperH * dMMtoPixelH;
//	printBmp->Width 	= nPrintW;
//	printBmp->Height 	= nPrintH;
//	nPreviewW	= nPrintW / dMMtoPixelW;
//	nPreviewH	= nPrintH / dMMtoPixelH;

	if(cboPrintScale->ItemIndex == 0 && nWidth < nPrintW && nHeight < nPrintH)//210111//
	{
		printBmp->Width 	= nWidth;
		printBmp->Height 	= nHeight;
	}
	else
	{
		printBmp->Width 	= nPrintW;
		printBmp->Height 	= nPrintH;
	}
	nPreviewW	= printBmp->Width / dMMtoPixelW;
	nPreviewH	= printBmp->Height / dMMtoPixelH;

	if ( printDIB != NULL)
	{
		FreeImage_Unload(printDIB);
		printDIB = NULL;
	}

	if(cboPrintScale->ItemIndex == 1)//페이지맞춤(기본)//
	{
		//################################################################
		//::SetStretchBltMode(printBmp->Canvas->Handle, HALFTONE);
		//::StretchDIBits(printBmp->Canvas->Handle, 0, 0, nPrintW, nPrintH, 0, 0, nWidth, nHeight, FreeImage_GetBits(frmMain->mGetImageInfo.m_DIB), FreeImage_GetInfo(frmMain->mGetImageInfo.m_DIB), DIB_RGB_COLORS, SRCCOPY);
		printDIB	= FreeImage_Rescale(frmMain->mGetImageInfo.m_DIB, nPrintW, nPrintH, FILTER_BILINEAR);
		//################################################################
	}
	else if(cboPrintScale->ItemIndex == 0)//실제크기//
	{
		int nLeft = 0;
		int nTop = 0;
		int nRow = (nPosition - 1) / 3;
		int nCol = (nPosition - 1) % 3;

		//Image to Save
		switch(nRow)
		{
			case 0:		nTop  = 0;		break;
			case 1:     nTop  = (nHeight - nPrintH) / 2;	break;
			case 2:     nTop  = nHeight - nPrintH;		break;
		}
		switch(nCol)
		{
			case 0:		nLeft = 0;		break;
			case 1:     nLeft = (nWidth - nPrintW) / 2;	break;
			case 2:     nLeft = nWidth - nPrintW;         break;
		}

		//Preview
		switch(nRow)
		{
			case 0:		nPreviewT  	= 0;		break;
			case 1:     nPreviewT  	= (nPaperH - nPreviewH) / 2;	break;
			case 2:     nPreviewT  	= nPaperH - nPreviewH;		break;
		}

		switch(nCol)
		{
			case 0:		nPreviewL 	= 0;		break;
			case 1:     nPreviewL 	= (nPaperW - nPreviewW) / 2;	break;
			case 2:     nPreviewL 	= nPaperW - nPreviewW;         break;
		}

		//201222//
		if(nLeft < 0)	nLeft	= 0;
		if(nTop < 0)	nTop	= 0;

//		//################################################################
//		::SetStretchBltMode(printBmp->Canvas->Handle, HALFTONE);
//		::StretchDIBits(printBmp->Canvas->Handle, 0, 0, nPrintW, nPrintH, nLeft, nTop, nPrintW, nPrintH, FreeImage_GetBits(frmMain->mGetImageInfo.m_DIB), FreeImage_GetInfo(frmMain->mGetImageInfo.m_DIB), DIB_RGB_COLORS, SRCCOPY);

		//210111//부책 용지에 맞춤 > 실제크기 변경 시 printDIB가 NULL이 된다. 3507 x 2480보다 원본이미지가 더 작아서 발생하는 현상으로 보임//
		int nRight		= nPrintW + nLeft;
		int nBottoom	= nPrintH + nTop;
		if(nRight > nWidth)
		{
			nRight		= nWidth;
			nPrintW		= nWidth;
		}
		if(nBottoom > nHeight)
		{
			nBottoom	= nHeight;
			nPrintH		= nHeight;
		}

		printDIB	= FreeImage_Copy(frmMain->mGetImageInfo.m_DIB, nLeft, nTop, nRight, nBottoom);
		//################################################################
	}

	if(printDIB == NULL)
	{
		delete printBmp;
		printBmp = NULL;

		//=================================
		funcSetWaitWindows(false);//210111//
		//=================================
		frmMsg->funcMessageDlg("이미지 확인:", "이미지 확인이 필요합니다. 개발사에 요청해주세요.", 3);
		return;
    }

	//================================================================================
	if(frmMain->INIUSERSETINFO.B_WATERMARK && !(nDocNo == 7 && chkDoc7Form->Checked))//201228//지적도(임야도) 등본일때는 WaterMark표시안함//200421//44770//WaterMark//
		funcDrawWaterMark();

	//210111
	//원본tif라고 tif포맷으로 저장하면 LandOffice07.exe에서 tif가 적용안되는 상태(적용하려면 이미지 로딩방식을 freeimage로 변경해야함)
	//원본tif여도 jpg파일의 jpg형식으로 변경하면 0kb로 저장이 제대로 안됨.
	//tif인 경우에는 위와 같이, bit수를 24로 변경해서 jpg로 저장한다//
	int readBpp = FreeImage_GetBPP(frmMain->mGetImageInfo.m_DIB);
	if(readBpp < 16){
		printDIB = FreeImage_ConvertTo24Bits(printDIB);
	}
	FreeImage_Save(FIF_JPEG, printDIB, _asPrintFile.c_str());
//210111//	FreeImage_Save(frmMain->mGetImageInfo.fiformat, printDIB, _asPrintFile.c_str());

	//??? 스탬프는 어찌하나//
	//==========================================================================
	//구대장_스탬프//
	if(nDocNo == 8 && chkDoc8Stamp->Checked)
		funcDrawDoc8Stamp(_asPrintFile);

	AnsiString  asPreviewPath	= frmMain->ROOTPATH + "tmp\\preview.jpg";
	if(FileExists(asPreviewPath))
		DeleteFile(asPreviewPath);

	if(nDocNo == 7 && chkDoc7Form->Checked)
	{
		imgDoc7Preview->Picture->Bitmap->Handle	= NULL;
		imgDoc7Preview->Picture					= NULL;
		imgDoc7Preview->Picture->Bitmap->Width	= nPreviewW;
		imgDoc7Preview->Picture->Bitmap->Height	= nPreviewH;

		::SetStretchBltMode(imgDoc7Preview->Canvas->Handle, HALFTONE);
		::StretchDIBits(imgDoc7Preview->Canvas->Handle, 0, 0, nPreviewW, nPreviewH, 0, 0, nPrintW, nPrintH, FreeImage_GetBits(printDIB), FreeImage_GetInfo(printDIB), DIB_RGB_COLORS, SRCCOPY);

		pnlDoc7ImgPreview->Left					= 1;
		pnlDoc7ImgPreview->Top					= 1;
		pnlDoc7ImgPreview->Width				= nPreviewW;
		pnlDoc7ImgPreview->Height				= nPreviewH;
//		imgDoc7Preview->Stretch					= true;
	}
	else
	{
		imgPrintPreview->Picture->Bitmap->Handle	= NULL;
		imgPrintPreview->Picture					= NULL;
		imgPrintPreview->Picture->Bitmap->Width		= nPreviewW;
		imgPrintPreview->Picture->Bitmap->Height	= nPreviewH;

		::SetStretchBltMode(imgPrintPreview->Canvas->Handle, HALFTONE);
		::StretchDIBits(imgPrintPreview->Canvas->Handle, 0, 0, nPreviewW, nPreviewH, 0, 0, nPrintW, nPrintH, FreeImage_GetBits(printDIB), FreeImage_GetInfo(printDIB), DIB_RGB_COLORS, SRCCOPY);

		pnlPreviewImg->Left							= nPreviewL+1;
		pnlPreviewImg->Top							= nPreviewT+1;
		pnlPreviewImg->Width						= nPreviewW;
		pnlPreviewImg->Height						= nPreviewH;
//		imgPrintPreview->Stretch					= true;
	}

	delete printBmp;
	printBmp = NULL;

	if ( printDIB != NULL)
	{
		FreeImage_Unload(printDIB);
		printDIB = NULL;
	}

	//=================================
	funcSetWaitWindows(false);//210111//
	//=================================
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::funcPreviewPrintDoc8Page2Card(AnsiString _asPrintFile, bool _bFirstPage, bool _bDownload)
{
	int nPnlW = pnlPaper1->Width - 2;
	int nPnlH = pnlPaper1->Height - 2;
	int nPrintW 	= nWidth;
	int nPrintH 	= nHeight;
	int nPreviewL	= 0;
	int nPreviewT 	= 0;
	int nPreviewW	= 0;
	int nPreviewH	= 0;


	Graphics::TBitmap *printBmp = new Graphics::TBitmap();
	printBmp->PixelFormat = pf24bit;

	printBmp->Width 	= nPrintW;
	printBmp->Height 	= nPrintH;

//	nPreviewW	= nPrintW / dMMtoPixelW;
//	nPreviewH	= nPrintH / dMMtoPixelH;
	//200928//
	nPreviewW   = nPnlW;
	nPreviewH	= nPnlH;

	//################################################################
	::SetStretchBltMode(printBmp->Canvas->Handle, HALFTONE);
	if(_bDownload)
		::StretchDIBits(printBmp->Canvas->Handle, 0, 0, nPrintW, nPrintH, 0, 0, nPrintW, nPrintH, FreeImage_GetBits(i_DIB), FreeImage_GetInfo(i_DIB), DIB_RGB_COLORS, SRCCOPY);
	else
		::StretchDIBits(printBmp->Canvas->Handle, 0, 0, nPrintW, nPrintH, 0, 0, nPrintW, nPrintH, FreeImage_GetBits(frmMain->mGetImageInfo.m_DIB), FreeImage_GetInfo(frmMain->mGetImageInfo.m_DIB), DIB_RGB_COLORS, SRCCOPY);
	//################################################################


	//==========================================================================
	double dRate = 0.0;
	double dRateW = (double)nPnlW / (double)nPrintW;
	double dRateH = (double)nPnlH / (double)nPrintH;
	if(dRateW < dRateH)		dRate = dRateW;
	else               		dRate = dRateH;

	if (chkDoc8Stamp->Checked)
	{
		double dBmRate = (double)nPrintH / (double)nPrintW;
		dBmRate = RoundTo(dBmRate, -2) * 100;
		int nStampLeft = (nPrintW * 0.55);
		int nStampTop = (nPrintH * 0.88);
		int nStampW = (frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Width)*dBmRate/100;
		int nStampH = (frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Height)*dBmRate/100;
		::AlphaBlend(printBmp->Canvas->Handle, nStampLeft, nStampTop, nStampW, nStampH, frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Canvas->Handle, 0, 0, frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Width, frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Height, frmMain->flagbf);
	}

	//================================================================================
	if(frmMain->INIUSERSETINFO.B_WATERMARK)//200421//44770//WaterMark
	{
		HDC pDraw    		= printBmp->Canvas->Handle;
		TCanvas  *pCanvas   = printBmp->Canvas;

		HPEN pen;
		HFONT m_font;
		HFONT hOldFont, hOldFontA;

		TPoint tpText;
		int fontwidth = 24;//48;
		AnsiString asLabel	= "";
		AnsiString asDepart	= frmMain->USERINI->ReadString("USER_CONFIG", "DEPART", "");
		AnsiString asDate	= Now().FormatString("yyyy.mm.dd hh:mm:ss");
		if(asDepart.IsEmpty())
			asLabel.sprintf("인쇄:%s(%s)", frmMain->m_asCurrentNm, asDate);
		else
			asLabel.sprintf("인쇄:%s/%s(%s)", frmMain->m_asCurrentNm, asDepart, asDate);

		m_font    = ::CreateFont(fontwidth, 0, 0, 0, FW_HEAVY, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "나눔고딕" );
		hOldFont  = (HFONT)::SelectObject(pDraw, m_font);
		::SetBkMode(pDraw, TRANSPARENT);
		::SetTextColor(pDraw, clBlue);
		pCanvas->TextOutA(30, 30, asLabel);
		::SelectObject(pDraw, hOldFont);
		::DeleteObject(m_font);
	}

	//Save To Jpg
	TJPEGImage *saveJpg = new TJPEGImage();
	saveJpg->CompressionQuality = 70;
	saveJpg->Compress();
	//saveJpg->PixelFormat = pf24bit;
	saveJpg->Assign(printBmp);
	saveJpg->SaveToFile(_asPrintFile);

	//---
	if (_bFirstPage)
	{
		imgPrintPreview1->Picture->Bitmap->Handle	= NULL;
		imgPrintPreview1->Picture					= NULL;

		SetStretchBltMode(imgPrintPreview1->Canvas->Handle, HALFTONE);
		HDC tmBmHd    = printBmp->Canvas->Handle;
		StretchBlt(imgPrintPreview1->Canvas->Handle, 0, 0, nPreviewW, nPreviewH, tmBmHd, 0, 0, nPrintW, nPrintH, SRCCOPY);

		pnlPreviewImg1->Left = 1;
		pnlPreviewImg1->Top = 1;
	}
	else//second page
	{
		imgPrintPreview2->Picture->Bitmap->Handle	= NULL;
		imgPrintPreview2->Picture					= NULL;

		SetStretchBltMode(imgPrintPreview2->Canvas->Handle, HALFTONE);
		HDC tmBmHd    = printBmp->Canvas->Handle;
		StretchBlt(imgPrintPreview2->Canvas->Handle, 0, 0, nPreviewW, nPreviewH, tmBmHd, 0, 0, nPrintW, nPrintH, SRCCOPY);

		pnlPreviewImg2->Left = 1;
		pnlPreviewImg2->Top = 1;
	}

	delete saveJpg;
	saveJpg = NULL;

	delete printBmp;
	printBmp = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintSetting::funcPreviewPrintDoc8Page2Etc(AnsiString _asPrintFile1, AnsiString _asPrintFile2)
{
	int nPnlW = pnlPaper1->Width - 2;
	int nPnlH = pnlPaper1->Height - 2;
	int nPreviewL	= 0;
	int nPreviewT 	= 0;
	int nPreviewW	= 0;
	int nPreviewH	= 0;
	int nPrintL = 0;
	int nPrintT = 0;
	int nPrintW = 0;
	int nPrintH = 0;


	////////////////////////////////
	Graphics::TBitmap *printBmp1 = new Graphics::TBitmap();
	Graphics::TBitmap *printBmp2 = new Graphics::TBitmap();

	//-------------------------------
	if(nWidth < nHeight)//Portrait//***
	{
		nPrintW 	= frmMain->readImageWidth;
		nPrintH 	= frmMain->readImageHeight / 2;
	}
	else//Landscape//***
	{
		nPrintW 	= frmMain->readImageWidth / 2;
		nPrintH 	= frmMain->readImageHeight;
	}

	printBmp1->PixelFormat 	= pf24bit;
	printBmp1->Width 		= nPrintW;
	printBmp1->Height 		= nPrintH;

	//################################################################
	::SetStretchBltMode(printBmp1->Canvas->Handle, HALFTONE);
	::StretchDIBits(printBmp1->Canvas->Handle, 0, 0, nPrintW, nPrintH, 0, 0, nPrintW, nPrintH, FreeImage_GetBits(frmMain->mGetImageInfo.m_DIB), FreeImage_GetInfo(frmMain->mGetImageInfo.m_DIB), DIB_RGB_COLORS, SRCCOPY);
	//################################################################


	//==========================================================================
	double dRate = 0.0;
	double dRateW = (double)nPnlW / (double)printBmp1->Width;
	double dRateH = (double)nPnlH / (double)printBmp1->Height;
	if(dRateW < dRateH)		dRate = dRateW;
	else               		dRate = dRateH;

	if (chkDoc8Stamp->Checked)
	{
		double dBmRate = (double)printBmp1->Width / (double)printBmp1->Height;
		dBmRate = RoundTo(dBmRate, -2) * 100;
		int nStampLeft = (printBmp1->Width * 0.45);
		int nStampTop = (printBmp1->Height * 0.88);
		int nStampW = (frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Width)*dBmRate/100;
		int nStampH = (frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Height)*dBmRate/100;
		::AlphaBlend(printBmp1->Canvas->Handle, nStampLeft, nStampTop, nStampW, nStampH, frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Canvas->Handle, 0, 0, frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Width, frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Height, frmMain->flagbf);
	}


	//================================================================================
	if(frmMain->INIUSERSETINFO.B_WATERMARK)//200421//44770//WaterMark
	{
		HDC 		pDraw      = printBmp1->Canvas->Handle;
		TCanvas  	*pCanvas   = printBmp1->Canvas;

		HPEN pen;
		HFONT m_font;
		HFONT hOldFont, hOldFontA;

		TPoint tpText;
		int fontwidth = 24;//48;
		AnsiString asLabel	= "";
		AnsiString asDepart	= frmMain->USERINI->ReadString("USER_CONFIG", "DEPART", "");
		AnsiString asDate	= Now().FormatString("yyyy.mm.dd hh:mm:ss");
		if(asDepart.IsEmpty())
			asLabel.sprintf("인쇄:%s(%s)", frmMain->m_asCurrentNm, asDate);
		else
			asLabel.sprintf("인쇄:%s/%s(%s)", frmMain->m_asCurrentNm, asDepart, asDate);

		m_font    = ::CreateFont(fontwidth, 0, 0, 0, FW_HEAVY, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "나눔고딕" );
		hOldFont  = (HFONT)::SelectObject(pDraw, m_font);
		::SetBkMode(pDraw, TRANSPARENT);
		::SetTextColor(pDraw, clBlue);
		pCanvas->TextOutA(30, 30, asLabel);
		::SelectObject(pDraw, hOldFont);
		::DeleteObject(m_font);
	}

	TJPEGImage *saveJpg;
	//Save To Jpg
	saveJpg = new TJPEGImage();
	saveJpg->CompressionQuality = 70;
	saveJpg->Compress();
	//saveJpg->PixelFormat = pf24bit;
	saveJpg->Assign(printBmp1);
	saveJpg->SaveToFile(_asPrintFile1);
	delete saveJpg;
	saveJpg = NULL;


	//-------------------------------
	if(nWidth < nHeight)//Portrait//***
	{
		nPrintT = nPrintH;
	}
	else//Landscape//***
	{
		nPrintL = nPrintW;
	}
	printBmp2->PixelFormat = pf24bit;
	printBmp2->Width 	= nPrintW;
	printBmp2->Height 	= nPrintH;

	//################################################################
	::SetStretchBltMode(printBmp2->Canvas->Handle, HALFTONE);
	::StretchDIBits(printBmp2->Canvas->Handle, 0, 0, nPrintW, nPrintH, nPrintL, nPrintT, nPrintW, nPrintH, FreeImage_GetBits(frmMain->mGetImageInfo.m_DIB), FreeImage_GetInfo(frmMain->mGetImageInfo.m_DIB), DIB_RGB_COLORS, SRCCOPY);
	//################################################################


	//==========================================================================
	if (chkDoc8Stamp->Checked)
	{
		double dBmRate = (double)printBmp2->Width / (double)printBmp2->Height;
		dBmRate = RoundTo(dBmRate, -2) * 100;
		int nStampLeft = (printBmp2->Width * 0.45);
		int nStampTop = (printBmp2->Height * 0.88);
		int nStampW = (frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Width)*dBmRate/100;
		int nStampH = (frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Height)*dBmRate/100;
		::AlphaBlend(printBmp2->Canvas->Handle, nStampLeft, nStampTop, nStampW, nStampH, frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Canvas->Handle, 0, 0, frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Width, frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Height, frmMain->flagbf);
	}

	//================================================================================
	if(frmMain->INIUSERSETINFO.B_WATERMARK)//200421//44770//WaterMark
	{
		HDC 		pDraw		= printBmp2->Canvas->Handle;
		TCanvas  	*pCanvas   	= printBmp2->Canvas;

		HPEN pen;
		HFONT m_font;
		HFONT hOldFont, hOldFontA;

		TPoint tpText;
		int fontwidth = 24;//48;
		AnsiString asLabel	= "";
		AnsiString asDepart	= frmMain->USERINI->ReadString("USER_CONFIG", "DEPART", "");
		AnsiString asDate	= Now().FormatString("yyyy.mm.dd hh:mm:ss");
		if(asDepart.IsEmpty())
			asLabel.sprintf("인쇄:%s(%s)", frmMain->m_asCurrentNm, asDate);
		else
			asLabel.sprintf("인쇄:%s/%s(%s)", frmMain->m_asCurrentNm, asDepart, asDate);

		m_font    = ::CreateFont(fontwidth, 0, 0, 0, FW_HEAVY, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "나눔고딕" );
		hOldFont  = (HFONT)::SelectObject(pDraw, m_font);

		::SetBkMode(pDraw, TRANSPARENT);
		::SetTextColor(pDraw, clBlue);

		pCanvas->TextOutA(30, 30, asLabel);

		::SelectObject(pDraw, hOldFont);
		::DeleteObject(m_font);
	}
	//Save To Jpg
	saveJpg = new TJPEGImage();
	saveJpg->CompressionQuality = 70;
	saveJpg->Compress();
	//saveJpg->PixelFormat = pf24bit;
	saveJpg->Assign(printBmp2);
	saveJpg->SaveToFile(_asPrintFile2);
	delete saveJpg;
	saveJpg = NULL;


	nPreviewW   = nPnlW;
	nPreviewH	= nPnlH;
	//---
	imgPrintPreview1->Picture->Bitmap->Handle	= NULL;
	imgPrintPreview1->Picture					= NULL;

	SetStretchBltMode(imgPrintPreview1->Canvas->Handle, HALFTONE);
	HDC tmBmHd    = printBmp1->Canvas->Handle;
	StretchBlt(imgPrintPreview1->Canvas->Handle, 0, 0, nPreviewW, nPreviewH, tmBmHd, 0, 0, nPrintW, nPrintH, SRCCOPY);

	pnlPreviewImg1->Left	= 1;
	pnlPreviewImg1->Top		= 1;

	//---
	imgPrintPreview2->Picture->Bitmap->Handle	= NULL;
	imgPrintPreview2->Picture					= NULL;

	SetStretchBltMode(imgPrintPreview2->Canvas->Handle, HALFTONE);
	HDC tmBmHd2    = printBmp2->Canvas->Handle;
	StretchBlt(imgPrintPreview2->Canvas->Handle, 0, 0, nPreviewW, nPreviewH, tmBmHd2, 0, 0, nPrintW, nPrintH, SRCCOPY);

	pnlPreviewImg2->Left	 = 1;
	pnlPreviewImg2->Top		 = 1;

	delete printBmp1;
	printBmp1 = NULL;
	delete printBmp2;
	printBmp2 = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::funcCopyInfoToDbPreview()
{
	AnsiString asStr			= "";
	AnsiString asDateStr 		= Now().FormatString("yyyymmdd");
	AnsiString asTimeStr 		= Now().FormatString("hh:nn:ss");
	AnsiString asDateStrTypeA 	= Now().FormatString("yyyy년 mm월 dd일");

	lblText1->Caption 		= asDateStr;
	lblText2->Caption 		= asTimeStr;
	lblText3->Caption 		= frmMain->USERINI->ReadString("USER_CONFIG", "NAME", " ").t_str();
	lblText4->Caption 		= "";
	lblText5->Caption 		= "";
	lblText6->Caption 		= "";
	lblDate->Caption 		= asDateStrTypeA;

	char cTemp[16];
	funcAddSiGunTitle(cTemp);
	lblSidoName->Caption 	= cTemp;

	int	nSelDoc = frmMain->m_nViewDocNo;
	if(frmSql->m_ResultDoc07DBInfo.size() == 0)
		return;

	asStr	= frmSql->m_ResultDoc07DBInfo[0].KWON_NO;
	asStr   = frmMain->INIINFO.SIDOCODE + asStr;
	asStr 	= frmSql->func_ConvertUmdCDtoNM(asStr.SubString(1,8));//210204//#LOADING_TEST//frmMain->func_ConvertEmdCDtoNM(asStr.SubString(1,8));
	lblText4->Caption 		= asStr;

	asStr	= frmSql->m_ResultDoc07DBInfo[0].DOHO_BON;
	if(asStr.IsEmpty()) 	asStr = "0";
	lblText5->Caption 		= asStr.ToInt();
	asStr	= frmSql->m_ResultDoc07DBInfo[0].SCALE;
	if( !asStr.IsEmpty() )
		lblText6->Caption 	= asStr + "00";

	if( asStr == "60" )
		lblT0->Caption = "임야도 등본";
	else
		lblT0->Caption = "지적도 등본";

	lblT0->Left = (pnlDoc7Top->Width - lblT0->Width) / 2;
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintSetting::funcRectanglePreview(AnsiString _asPrintFile)
{
	int nPnlW = 0;//pnlPaper->Width - 2;
	int nPnlH = 0;//pnlPaper->Height - 2;

	//=================================
	funcSetWaitWindows(true);//210111//
	//=================================

	if( nDocNo == 7 && chkDoc7Form->Checked )
	{
		nPnlW = pnlDoc7Mid->Width - 2;
		nPnlH = pnlDoc7Mid->Height - 2;
	}
	else
	{
		nPnlW = pnlPaper->Width - 2;
		nPnlH = pnlPaper->Height - 2;
	}

	AnsiString result;
	int left, top, right, bottom, centerX, centerY;

	if(cboPrintScale->ItemIndex == 0 && frmPrintSetting->Tag == 1)//실제크기로
	{
		if(frmMain->pnlImgDocView->Left < 0)
			left = abs(frmMain->pnlImgDocView->Left);
		if(frmMain->pnlImgDocView->Top < 0)
			top = abs(frmMain->pnlImgDocView->Top);
		if(frmMain->pnlImgDocView->Left + frmMain->pnlImgDocView->Width > frmMain->palMainView->Width)
			right = left + frmMain->palMainView->Width;
		if(frmMain->pnlImgDocView->Top + frmMain->pnlImgDocView->Height > frmMain->palMainView->Height)
			bottom = top + frmMain->palMainView->Height;
	}
	else
	{
		//Rectalge position
		////////////////////////////////////////////////////////////////////////////
		if(frmMain->mRactState.tpRactStartPoint.x < frmMain->mRactState.tpRactEndPoint.x)
		{
			left   = frmMain->mRactState.tpRactStartPoint.x;
			right  = frmMain->mRactState.tpRactEndPoint.x;
		}
		else
		{
			left   = frmMain->mRactState.tpRactEndPoint.x;
			right  = frmMain->mRactState.tpRactStartPoint.x;
		}
		if(frmMain->mRactState.tpRactStartPoint.y < frmMain->mRactState.tpRactEndPoint.y)
		{
			top    = frmMain->mRactState.tpRactStartPoint.y;
			bottom = frmMain->mRactState.tpRactEndPoint.y;
		}
		else
		{
			top    = frmMain->mRactState.tpRactEndPoint.y;
			bottom = frmMain->mRactState.tpRactStartPoint.y;
		}
	}

	//이미지 밖으로 나간 영역 조정
	if(left < 0)
		left = 0;
	if(top < 0)
		top = 0;
	if(right > (frmMain->realLeft + frmMain->readImageWidth) * frmMain->m_dDocFactor)
		right = (frmMain->realLeft + frmMain->readImageWidth) * frmMain->m_dDocFactor;
	if(bottom > (frmMain->readImageHeight - frmMain->realTop) * frmMain->m_dDocFactor)
		bottom = (frmMain->readImageHeight - frmMain->realTop) * frmMain->m_dDocFactor;

	//이미지 상에 선택된 영역의 화면좌표 중심
	centerX = left + (right - left) / 2;
	centerY = top + (bottom - top) / 2;

	if( !(nDocNo == 7 && chkDoc7Form->Checked) )
	{
		if( (right - left)  < (bottom - top) )//width < height//Portrait
		{
			if(nPaperW > nPaperH)
			{
				int nTemp = nPaperW;
				nPaperW   = nPaperH;
				nPaperH   = nTemp;
			}

			if(nPnlW > nPnlH)
			{
				int nTemp = nPnlW;
				nPnlW   = nPnlH;
				nPnlH   = nTemp;
			}

			pnlPaper->Width = 212;
			pnlPaper->Height = 299;
			pnlPaper->Left = 43;
			pnlPaper->Top = 0;

			m_asOrientation	= "_P";//200928//
		}
		else//width > height//Landscape//200515//#1
		{
			if(nPaperW < nPaperH)
			{
				int nTemp = nPaperW;
				nPaperW   = nPaperH;
				nPaperH   = nTemp;
			}

			if(nPnlW < nPnlH)
			{
				int nTemp = nPnlW;
				nPnlW   = nPnlH;
				nPnlH   = nTemp;
			}

			pnlPaper->Left 		= 0;
			pnlPaper->Top 		= 43;
			pnlPaper->Width 	= 299;
			pnlPaper->Height  	= 212;

			m_asOrientation	= "_L";//200928//
		}
		//200925//[TODO]
	}

	if(cboPrintScale->ItemIndex == 0)//실제크기로
	{
		//출력할 영역정보로 출력할 수 있는 화면 좌표 Width, Height 산정
		//get Point Center X, Y //by original size
		int  nScreenRectW, nScreenRectH, nScreenCenterX, nScreenCenterY = 0;
		nScreenRectW = (nPaperW * dMMtoPixelW) * frmMain->m_dDocFactor;
		nScreenRectH = (nPaperH * dMMtoPixelH) * frmMain->m_dDocFactor;

		//출력할 수 있는 화면 좌표 width, height를 기준으로 left, top, right, bottom 재조정
		if(left < (centerX - nScreenRectW / 2))
			left = centerX - nScreenRectW / 2;
		if(top < (centerY - nScreenRectH / 2))
			top = centerY - nScreenRectH / 2;
		if(right > (centerX + nScreenRectW / 2))
			right = centerX + nScreenRectW / 2;
		if(bottom > (centerY + nScreenRectH / 2))
			bottom = centerY + nScreenRectH / 2;
	}

	//################################################################
	TPoint	_tPoint;
	GPoint	_gStart, _gEnd;

	_tPoint.x	= left;
	_tPoint.y	= top;
	_gStart		= eFunc->funcDeviceToSurveyMap(_tPoint);
	_tPoint.x	= right;
	_tPoint.y	= bottom;
	_gEnd		= eFunc->funcDeviceToSurveyMap(_tPoint);

	int nPrintL = _gStart.x;
	//210127//영역선택 > 인쇄 시 Y좌표가 거꾸로 나옴//int nPrintT = frmMain->readImageHeight - _gEnd.y;
	int nPrintT = _gStart.y;
	int nPrintW = _gEnd.x - _gStart.x;
	int nPrintH = _gEnd.y - _gStart.y;
	int nPreviewL	= 0;
	int nPreviewT 	= 0;
	int nPreviewW	= 0;
	int nPreviewH	= 0;

	Graphics::TBitmap *printBmp = new Graphics::TBitmap();
	printBmp->PixelFormat = pf24bit;

	////////////////////////////////
	if(cboPrintScale->ItemIndex == 1)//페이지맞춤(기본)//
	{
		printBmp->Width 	= nPrintW;
		printBmp->Height 	= nPrintH;

		nPreviewL	= 0;
		nPreviewT	= 0;
		nPreviewW	= nPaperW;
		nPreviewH	= nPaperH;
	}
	else if(cboPrintScale->ItemIndex == 0)//실제크기//
	{
		nPreviewW	= nPrintW / dMMtoPixelW;
		nPreviewH	= nPrintH / dMMtoPixelH;


		int nRow = (nPosition - 1) / 3;
		int nCol = (nPosition - 1) % 3;

		switch(nRow)
		{
			case 0:		nPreviewT  	= 0;		break;
			case 1:     nPreviewT  	= (nPaperH - nPreviewH) / 2;	break;
			case 2:     nPreviewT  	= nPaperH - nPreviewH;		break;
		}

		switch(nCol)
		{
			case 0:		nPreviewL 	= 0;		break;
			case 1:     nPreviewL 	= (nPaperW - nPreviewW) / 2;	break;
			case 2:     nPreviewL 	= nPaperW - nPreviewW;         break;
		}

		printBmp->Width 	= nPrintW;//nPaperW * dMMtoPixelW;
		printBmp->Height 	= nPrintH;//nPaperH * dMMtoPixelH;
	}

	//210112//
//	::SetStretchBltMode(printBmp->Canvas->Handle, HALFTONE);
//	::StretchDIBits(printBmp->Canvas->Handle, 0, 0, printBmp->Width, printBmp->Height, nPrintL, nPrintT, nPrintW, nPrintH, FreeImage_GetBits(frmMain->mGetImageInfo.m_DIB), FreeImage_GetInfo(frmMain->mGetImageInfo.m_DIB), DIB_RGB_COLORS, SRCCOPY);
//	//================================================================================
//	if(frmMain->INIUSERSETINFO.B_WATERMARK && !(nDocNo == 7 && chkDoc7Form->Checked))//201228//지적도(임야도) 등본일때는 WaterMark표시안함)//200421//44770//WaterMark
//	{
//		HDC pDraw    		= printBmp->Canvas->Handle;
//		TCanvas  *pCanvas   = printBmp->Canvas;
//
//		HPEN pen;
//		HFONT m_font;
//		HFONT hOldFont, hOldFontA;
//
//		TPoint tpText;
//		int fontwidth = 24;//48;
//		AnsiString asLabel	= "";
//		AnsiString asDepart	= frmMain->USERINI->ReadString("USER_CONFIG", "DEPART", "");
//		AnsiString asDate	= Now().FormatString("yyyy.mm.dd hh:mm:ss");
//		if(asDepart.IsEmpty())
//			asLabel.sprintf("인쇄:%s(%s)", frmMain->m_asCurrentNm, asDate);
//		else
//			asLabel.sprintf("인쇄:%s/%s(%s)", frmMain->m_asCurrentNm, asDepart, asDate);
//
//		m_font    = ::CreateFont(fontwidth, 0, 0, 0, FW_HEAVY, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "나눔고딕" );
//		hOldFont  = (HFONT)::SelectObject(pDraw, m_font);
//		::SetBkMode(pDraw, TRANSPARENT);
//		::SetTextColor(pDraw, clBlue);
//		pCanvas->TextOutA(40, 40, asLabel);
//		::SelectObject(pDraw, hOldFont);
//		::DeleteObject(m_font);
//	}
//	//Save To Jpg
//	TJPEGImage *saveJpg = new TJPEGImage();
//	saveJpg->CompressionQuality = 70;
//	saveJpg->Compress();
//	//saveJpg->PixelFormat = pf24bit;
//	saveJpg->Assign(printBmp);
//	saveJpg->SaveToFile(_asPrintFile);

	//210112//
	//=================================================================================================
	int nRight		= nPrintW + nPrintL;
	int nBottoom	= nPrintH + nPrintT;
	printDIB	= FreeImage_Copy(frmMain->mGetImageInfo.m_DIB, nPrintL, nPrintT, nRight, nBottoom);
	if(printDIB == NULL)
	{
		delete printBmp;
		printBmp = NULL;

		//=================================
		funcSetWaitWindows(false);//210111//
		//=================================
		frmMsg->funcMessageDlg("이미지 확인:", "이미지 확인이 필요합니다. 개발사에 요청해주세요.", 3);
		return;
	}
	if(frmMain->INIUSERSETINFO.B_WATERMARK && !(nDocNo == 7 && chkDoc7Form->Checked))//201228//지적도(임야도) 등본일때는 WaterMark표시안함//200421//44770//WaterMark//
		funcDrawWaterMark();

	//210111
	//원본tif라고 tif포맷으로 저장하면 LandOffice07.exe에서 tif가 적용안되는 상태(적용하려면 이미지 로딩방식을 freeimage로 변경해야함)
	//원본tif여도 jpg파일의 jpg형식으로 변경하면 0kb로 저장이 제대로 안됨.
	//tif인 경우에는 위와 같이, bit수를 24로 변경해서 jpg로 저장한다//
	int readBpp = FreeImage_GetBPP(frmMain->mGetImageInfo.m_DIB);
	if(readBpp < 16){
		printDIB = FreeImage_ConvertTo24Bits(printDIB);
	}
	FreeImage_Save(FIF_JPEG, printDIB, _asPrintFile.c_str());
	//=================================================================================================

	if(nDocNo == 7 && chkDoc7Form->Checked)
	{
		imgDoc7Preview->Picture->Bitmap->Handle	= NULL;
		imgDoc7Preview->Picture					= NULL;
		imgDoc7Preview->Picture->Bitmap->Width	= nPreviewW;
		imgDoc7Preview->Picture->Bitmap->Height	= nPreviewH;

//		SetStretchBltMode(imgDoc7Preview->Canvas->Handle, HALFTONE);
//		HDC tmBmHd    = printBmp->Canvas->Handle;
//		StretchBlt(imgDoc7Preview->Canvas->Handle, 0, 0, nPreviewW, nPreviewH, tmBmHd, 0, 0, nPrintW, nPrintH, SRCCOPY);
		//210112//
		::SetStretchBltMode(imgDoc7Preview->Canvas->Handle, HALFTONE);
		::StretchDIBits(imgDoc7Preview->Canvas->Handle, 0, 0, nPreviewW, nPreviewH, 0, 0, nPrintW, nPrintH, FreeImage_GetBits(printDIB), FreeImage_GetInfo(printDIB), DIB_RGB_COLORS, SRCCOPY);

		pnlDoc7ImgPreview->Left					= nPreviewL+1;
		pnlDoc7ImgPreview->Top					= nPreviewT+1;
		pnlDoc7ImgPreview->Width				= nPreviewW;
		pnlDoc7ImgPreview->Height				= nPreviewH;
	}
	else
	{
		imgPrintPreview->Picture->Bitmap->Handle	= NULL;
		imgPrintPreview->Picture					= NULL;
		imgPrintPreview->Picture->Bitmap->Width		= nPreviewW;
		imgPrintPreview->Picture->Bitmap->Height	= nPreviewH;

//		SetStretchBltMode(imgPrintPreview->Canvas->Handle, HALFTONE);
//		HDC tmBmHd    = printBmp->Canvas->Handle;
//		StretchBlt(imgPrintPreview->Canvas->Handle, 0, 0, nPreviewW, nPreviewH, tmBmHd, 0, 0, nPrintW, nPrintH, SRCCOPY);
		//210112//
		::SetStretchBltMode(imgPrintPreview->Canvas->Handle, HALFTONE);
		::StretchDIBits(imgPrintPreview->Canvas->Handle, 0, 0, nPreviewW, nPreviewH, 0, 0, nPrintW, nPrintH, FreeImage_GetBits(printDIB), FreeImage_GetInfo(printDIB), DIB_RGB_COLORS, SRCCOPY);

		pnlPreviewImg->Left					= nPreviewL+1;
		pnlPreviewImg->Top					= nPreviewT+1;
		pnlPreviewImg->Width				= nPreviewW;
		pnlPreviewImg->Height				= nPreviewH;
	}

	//210112//
//	delete saveJpg;
//	saveJpg = NULL;

	delete printBmp;
	printBmp = NULL;

    //210112//
	if ( printDIB != NULL)
	{
		FreeImage_Unload(printDIB);
		printDIB = NULL;
	}

	//=================================
	funcSetWaitWindows(false);//210111//
	//=================================
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintSetting::funcSetPreviewPage(bool _bLandscape)
{
	pnlPaper->Visible = true;
	pnlPaper1->Visible = false;
	pnlPaper2->Visible = false;

	//200925//[TODO]
//	//200813//TEST
//	if(rbPortrait->Checked)
//	{
//		pnlPaper->Left 		= 43;
//		pnlPaper->Top 		= 0;
//		pnlPaper->Width 	= 212;
//		pnlPaper->Height  	= 299;
//	}
//	else if(rbLandscape->Checked)
//	{
//		pnlPaper->Left 		= 0;
//		pnlPaper->Top 		= 43;
//		pnlPaper->Width 	= 299;
//		pnlPaper->Height  	= 212;
//	}
	//200813//TEST//old
	if(_bLandscape)
	{
		pnlPaper->Left 		= 0;
		pnlPaper->Top 		= 43;
		pnlPaper->Width 	= 299;
		pnlPaper->Height  	= 212;
	}
	else
	{
		pnlPaper->Left 		= 43;
		pnlPaper->Top 		= 0;
		pnlPaper->Width 	= 212;
		pnlPaper->Height  	= 299;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintSetting::funcSetPreviewPageDoc8Page2(bool _bLandscape)
{
	pnlPaper->Visible 			= false;
	pnlPaper1->Visible 			= true;
	pnlPaper2->Visible 			= true;
	cboPaperType->Enabled 		= false;
	cboPrintScale->ItemIndex 	= 1;//페이지맞춤(기본)//
	rbPortrait->Enabled			= false;//200914//
	rbLandscape->Enabled		= false;//200914//
	cboPrintScale->Enabled 		= false;
	pnlPosition->Enabled 		= false;

	if(_bLandscape)
	{
		pnlPaper1->Left 	= 43;
		pnlPaper1->Top 		= 0;
		pnlPaper1->Width 	= 212;
		pnlPaper1->Height  	= 149;
		pnlPaper2->Left 	= pnlPaper1->Left;
		pnlPaper2->Top 		= pnlPaper1->Height;//
		pnlPaper2->Width 	= pnlPaper1->Width;
		pnlPaper2->Height  	= pnlPaper1->Height;
		pnlPreviewImg1->Width  = 210;
		pnlPreviewImg1->Height = 147;
		pnlPreviewImg2->Width  = 210;
		pnlPreviewImg2->Height = 147;
	}
	else
	{
		pnlPaper1->Left 	= 0;
		pnlPaper1->Top 		= 43;
		pnlPaper1->Width 	= 149;
		pnlPaper1->Height  	= 212;
		pnlPaper2->Left 	= pnlPaper1->Width;//
		pnlPaper2->Top 		= pnlPaper1->Top;
		pnlPaper2->Width 	= pnlPaper1->Width;
		pnlPaper2->Height  	= pnlPaper1->Height;
		pnlPreviewImg1->Width  = 147;
		pnlPreviewImg1->Height = 210;
		pnlPreviewImg2->Width  = 147;
		pnlPreviewImg2->Height = 210;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::cboPrinterListChange(TObject *Sender)
{
	cboPrinterList->Text = m_sPrinterList->Strings[cboPrinterList->ItemIndex];
	frmMain->m_asPrinterName = cboPrinterList->Text;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::edtPrintTitleEnter(TObject *Sender)
{
	unsigned long Conversion, Sentence;
	HIMC Mode = ImmGetContext(Application->Handle);
	ImmGetConversionStatus(Mode, &Conversion, &Sentence);
	if (Conversion == IME_CMODE_HANGEUL) { 							// 현재모드가 한글이면 패스
	}
	else                                                         	// 현재모드가 한글이 아니면 한/영키 누른 효과를준다.
		ImmSetConversionStatus(Mode, IME_CMODE_HANGEUL, IME_CMODE_HANGEUL);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::FormDeactivate(TObject *Sender)
{
	//Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::btnCloseTypeBClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(frmPrintSetting->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------

//
//void __fastcall TfrmMain::btnPrint2Click(TObject *Sender)
//{
//	//----------------------------------------------------------
//	double 	dMMtoPixelW;
//	double 	dMMtoPixelH;
//	double 	dDpiRate;
//	int    	nImgmmW;//이미지를 mm 단위로 환산
//	int   	nImgmmH;//이미지를 mm 단위로 환산
//	int     nPaperW = 297;
//	int		nPaperH	= 210;
//	int     nPrintW = 0;
//	int		nPrintH = 0;
//	int 	nWidthCount		= 0;
//	int 	nHeightCount	= 0;
//	int 	nWidthTemp		= 0;
//	int 	nHeightTemp		= 0;
//	int     nCount			= 0;
//	AnsiString asFileName  	= "";
//	int    	nImageL			= 0;
//	int   	nImageT			= 0;
//	int		nWidthRest		= 0;
//	int		nHeightRest		= 0;
//	int 	nXSrc			= 0;
//	int 	nYSrc			= 0;
//	int 	nSrcW			= 0;
//	int 	nSrcH			= 0;
//
//	dMMtoPixelW = ((double)mBitMapInfo->bmiHeader.biXPelsPerMeter / (double)100) / (double)10;
//	dMMtoPixelH = ((double)mBitMapInfo->bmiHeader.biYPelsPerMeter / (double)100) / (double)10;
//	nImgmmW	= readImageWidth / dMMtoPixelW;
//	nImgmmH = readImageHeight / dMMtoPixelH;
//
//	//A4 몇장 나오는지//
//	nWidthCount 	= nImgmmW/nPaperW;
//	nHeightCount    = nImgmmH/nPaperH;
//	nWidthTemp		= nImgmmW%nPaperW;
//	nHeightTemp     = nImgmmH%nPaperH;
//	//테두리 검정색 부분 제거 위함//
//	if(nWidthTemp > nPaperW * 0.1)
//	{
//		nWidthCount++;
//		nWidthTemp	 = 0;
//	}
//	else
//	{
//		nWidthRest	= nWidthTemp / 2;
//	}
//
//	if(nHeightTemp > nPaperH * 0.1)
//	{
//		nHeightCount++;
//		nHeightTemp	 = 0;
//	}
//	else
//	{
//		nHeightRest	= nHeightTemp / 2;
//	}
//
//	//----------------------------------------------------------
//	Image1->Canvas->Lock();
//	if(m_DIB != NULL)
//	{
//		//화면밖으로//
//		pnlPrint->Left		= palMainView->Left + palMainView->Width;
//		pnlPrint->Top		= palMainView->Top + palMainView->Height;
//		pnlPrint->Visible	= true;
//
//		nPrintW	= nPaperW * dMMtoPixelW;
//		nPrintH	= nPaperH * dMMtoPixelH;
//		pnlPrint->Width   = nPrintW;
//		pnlPrint->Height  = nPrintH;
//		Image1->Picture->Bitmap->Width	= Image1->Width;
//		Image1->Picture->Bitmap->Height	= Image1->Height;
//
//
//		TRect rect;
//		rect.Left   = Image1->Left;
//		rect.Top    = Image1->Top;
//		rect.Right  = Image1->Width;
//		rect.Bottom = Image1->Height;
//
//		pDC   = Image1->Canvas->Handle; //복사본
//		memDC = ::CreateCompatibleDC(Image1->Canvas->Handle);
//
//		if(memDC){
//			hMembitmap = ::CreateCompatibleBitmap(Image1->Canvas->Handle, Image1->Width, Image1->Height);
//			if(hMembitmap){
//				pDC = memDC;
//				pObj = ::SelectObject(memDC,hMembitmap);
//			}
//		}
//
//		hbr   = ::CreateSolidBrush( 0x00ffffff ); //브러쉬
//		::FillRect( pDC, &rect, hbr  );
//		DeleteObject( hbr );
//
//		::SetStretchBltMode(pDC,HALFTONE);
//
//		for(int i = 0; i < nHeightCount; i++)
//		{
//			for(int j = 0; j < nWidthCount; j++)
//			{
//				nSrcW   = Image1->Width;
//				nSrcH  	= Image1->Height;
//				nXSrc	= nImageL + nWidthRest;//nPaperW*dMMtoPixelW;
//				nYSrc	= readImageHeight - nSrcH - nImageT;//readImageHeight - nSrcHeight * (nHeightCount - i) + nHeightRest;//nPaperH*dMMtoPixelH;
//				::StretchDIBits(pDC, 0, 0, nPrintW, nPrintH, nXSrc, nYSrc, nSrcW, nSrcH, FreeImage_GetBits(m_DIB), FreeImage_GetInfo(m_DIB), DIB_RGB_COLORS, SRCCOPY);
//
//				if (pDC != Image1->Canvas->Handle){
//					::BitBlt(Image1->Canvas->Handle, 0,0,rect.Width() ,rect.Height(), memDC ,0 ,0 , SRCCOPY);
//				}
//
//				nCount++;
//				asFileName  = frmMain->ROOTPATH + "PRINT\\print" + IntToStr(nCount) + ".bmp";
//				Image1->Picture->SaveToFile(asFileName);
//
//				nImageL	+= nSrcW;
//				//nImageL	+= (nSrcWidth - 50);
//			}
//			nImageL	= 0;
//			nImageT	+= nSrcH;
//			//nImageT	+= (nSrcHeight - 50);
//		}
//		::DeleteDC(memDC);
//		::DeleteObject(hMembitmap);
//		::DeleteObject(pObj);
//
//		Image1->Invalidate();
//	}
//	Image1->Canvas->Unlock();
//
//
//	this->funcFastReportOpen("A4_L", 0);
//
//	Image1->Picture->Bitmap	= NULL;
//	pnlPrint->Visible	= false;
//}
//---------------------------------------------------------------------------
void __fastcall TfrmPrintSetting::rbPaperDirectClick(TObject *Sender)
{
	if( !bFromShow )
		funcGetPrintPreview();//190401
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::funcSetPrintScale()
{
	cboPrintScale->Items->Clear();

	cboPrintScale->Items->Add("실제 크기");
	cboPrintScale->Items->Add("용지크기에 맞춤");
	//200925//일단 막음//
//	if(frmPrintSetting->Tag == 2 || chkDoc8Page2->Enabled || chkDoc7Form->Enabled)
//	{
//		cboPrintScale->Items->Add("실제 크기");
//		cboPrintScale->Items->Add("용지크기에 맞춤");
//	}
//	else
//	{
//		cboPrintScale->Items->Add("실제 크기");
//		cboPrintScale->Items->Add("용지크기에 맞춤");
//		cboPrintScale->Items->Add("전체분할출력");
//	}

    //201214//설정값을 가져와야지//테스트였을뿐//cboPrintScale->ItemIndex = 0;//TEST
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrintSetting::funcFileAllPart()
{
	//----------------------------------------------------------
	double 	dMMtoPixelW;
	double 	dMMtoPixelH;
	double 	dDpiRate;
	int    	nImgmmW;//이미지를 mm 단위로 환산
	int   	nImgmmH;//이미지를 mm 단위로 환산
	int     nPaperW = 297;
	int		nPaperH	= 210;
	int     nPrintW = 0;
	int		nPrintH = 0;
	int 	nWidthCount		= 0;
	int 	nHeightCount	= 0;
	int 	nWidthTemp		= 0;
	int 	nHeightTemp		= 0;
	int     nCount			= 0;
	AnsiString asFileName  	= "";
	int    	nImageL			= 0;
	int   	nImageT			= 0;
	int		nWidthRest		= 0;
	int		nHeightRest		= 0;
	int 	nXSrc			= 0;
	int 	nYSrc			= 0;
	int 	nSrcW			= 0;
	int 	nSrcH			= 0;

	//=================================
	funcSetWaitWindows(true);//210111//
	//=================================

	dMMtoPixelW = ((double)frmMain->mGetImageInfo.mBitMapInfo->bmiHeader.biXPelsPerMeter / (double)100) / (double)10;
	dMMtoPixelH = ((double)frmMain->mGetImageInfo.mBitMapInfo->bmiHeader.biYPelsPerMeter / (double)100) / (double)10;
//	dDpiRate = RoundTo((double)mBitMapInfo->bmiHeader.biXPelsPerMeter * (double)2.54 / (double)100 / (double)100, -3);//0.72, 0.96, 1, 2, 3
//	dMMtoPixelW = dDpiRate * fr01cm * 1;
//	dMMtoPixelH	= dDpiRate * fr01cm * 1;
	nImgmmW	= frmMain->readImageWidth / dMMtoPixelW;
	nImgmmH = frmMain->readImageHeight / dMMtoPixelH;

	//A4 몇장 나오는지//
	nWidthCount 	= nImgmmW/nPaperW;
	nHeightCount    = nImgmmH/nPaperH;
	nWidthTemp		= nImgmmW%nPaperW;
	nHeightTemp     = nImgmmH%nPaperH;
//	if(nWidthTemp > 0)		nWidthCount++;
//	if(nHeightTemp > 0)		nHeightCount++;
	//테두리 검정색 부분 제거 위함//
	if(nWidthTemp > nPaperW * 0.1)
	{
		nWidthCount++;
		nWidthTemp	 = 0;
	}
	else
	{
		nWidthRest	= nWidthTemp / 2;
	}

	if(nHeightTemp > nPaperH * 0.1)
	{
		nHeightCount++;
		nHeightTemp	 = 0;
	}
	else
	{
		nHeightRest	= nHeightTemp / 2;
	}

	//----------------------------------------------------------
	Image1->Canvas->Lock();
	if(frmMain->mGetImageInfo.m_DIB != NULL)
	{
		//화면밖으로//
		pnlPrint->Left		= frmMain->palMainView->Left + frmMain->palMainView->Width;
		pnlPrint->Top		= frmMain->palMainView->Top + frmMain->palMainView->Height;
		pnlPrint->Visible	= true;

		nPrintW	= nPaperW * dMMtoPixelW;
		nPrintH	= nPaperH * dMMtoPixelH;
		pnlPrint->Width   = nPrintW;
		pnlPrint->Height  = nPrintH;
		Image1->Picture->Bitmap->Width	= Image1->Width;
		Image1->Picture->Bitmap->Height	= Image1->Height;


		TRect rect;
		rect.Left   = Image1->Left;
		rect.Top    = Image1->Top;
		rect.Right  = Image1->Width;
		rect.Bottom = Image1->Height;

		pDCDoc   = Image1->Canvas->Handle; //복사본
		memDCDoc = ::CreateCompatibleDC(Image1->Canvas->Handle);

		if(memDCDoc){
			hMembitmapDoc = ::CreateCompatibleBitmap(Image1->Canvas->Handle, Image1->Width, Image1->Height);
			if(hMembitmapDoc){
				pDCDoc = memDCDoc;
				pObjDoc = ::SelectObject(memDCDoc,hMembitmapDoc);
			}
		}

		hbrDoc   = ::CreateSolidBrush( 0x00ffffff ); //브러쉬
		::FillRect( pDCDoc, &rect, hbrDoc  );
		DeleteObject( hbrDoc );

		::SetStretchBltMode(pDCDoc,HALFTONE);

		for(int i = 0; i < nHeightCount; i++)
		{
			for(int j = 0; j < nWidthCount; j++)
			{
				nSrcW   = Image1->Width;
				nSrcH  	= Image1->Height;
				nXSrc	= nImageL + nWidthRest;//nPaperW*dMMtoPixelW;
				nYSrc	= frmMain->readImageHeight - nSrcH - nImageT;//readImageHeight - nSrcHeight * (nHeightCount - i) + nHeightRest;//nPaperH*dMMtoPixelH;
				::StretchDIBits(pDCDoc, 0, 0, nPrintW, nPrintH, nXSrc, nYSrc, nSrcW, nSrcH, FreeImage_GetBits(frmMain->mGetImageInfo.m_DIB), FreeImage_GetInfo(frmMain->mGetImageInfo.m_DIB), DIB_RGB_COLORS, SRCCOPY);

				if (pDCDoc != Image1->Canvas->Handle){
					::BitBlt(Image1->Canvas->Handle, 0,0,rect.Width() ,rect.Height(), memDCDoc ,0 ,0 , SRCCOPY);
				}

				nCount++;
				asFileName  = frmMain->ROOTPATH + "PRINT\\print" + IntToStr(nCount) + ".bmp";
				Image1->Picture->SaveToFile(asFileName);

				nImageL	+= nSrcW;
				//nImageL	+= (nSrcWidth - 50);
			}
			nImageL	= 0;
			nImageT	+= nSrcH;
			//nImageT	+= (nSrcHeight - 50);
		}
		::DeleteDC(memDCDoc);
		::DeleteObject(hMembitmapDoc);
		::DeleteObject(pObjDoc);

		Image1->Invalidate();
	}
	Image1->Canvas->Unlock();

	//=================================
	funcSetWaitWindows(false);//210111//
	//=================================

	this->funcFastReportOpen("A4_L", 0);

	Image1->Picture->Bitmap	= NULL;
	pnlPrint->Visible	= false;
}
//---------------------------------------------------------------------------
//201223//
void __fastcall TfrmPrintSetting::funcDrawWaterMark()
{
	AnsiString asLabel	= "";
	AnsiString asDepart	= frmMain->USERINI->ReadString("USER_CONFIG", "DEPART", "");
	AnsiString asDate	= Now().FormatString("yyyy.mm.dd hh:mm:ss");
	AnsiString asSaveWM	= frmMain->ROOTPATH + "tmp\\SaveWM.jpg";
	int	nFontHeight		= 100 * frmMain->m_dDocFactor;
	int nPrintWidth 	= 0;
	int nPrintHeight	= 0;

	if(printDIB != NULL)
	{
		nPrintWidth  	= FreeImage_GetWidth(printDIB);
		nPrintHeight 	= FreeImage_GetHeight(printDIB);
	}

	if( FileExists(asSaveWM) )//201223
		DeleteFile(asSaveWM);

	if(asDepart.IsEmpty() || asDepart == NULL)//210428//
		asLabel.sprintf("저장:%s(%s)", frmMain->m_asCurrentNm, asDate);
	else
		asLabel.sprintf("저장:%s/%s(%s)", frmMain->m_asCurrentNm, asDepart, asDate);


	Graphics::TBitmap  	*bmpWM;
	bmpWM = new Graphics::TBitmap();
	bmpWM->PixelFormat = pf24bit;
//	//고정//
////	bmpWM->Width  = asLabel.Length() * fontwidth / 2;//600;
////	bmpWM->Height = 48;
//	//비율//
//	bmpWM->Width  = (int)((double)nPrintWidth * 0.2);
//	bmpWM->Height = (int)((double)nPrintHeight * 0.02);
	//210428//
	//비율//
	if(frmPrintSetting->Tag == 2)
	{
		if(cboPrintScale->ItemIndex == 1)//페이지맞춤(기본)//
		{
			bmpWM->Width  = 240;//200;//(int)((double)nPrintWidth * 0.2);
			bmpWM->Height = 20;//(int)((double)nPrintHeight * 0.02);
		}
		else if(cboPrintScale->ItemIndex == 0)//실제크기//
		{
			bmpWM->Width  = 360;//300;//(int)((double)nPrintWidth * 0.2);
			bmpWM->Height = 30;//(int)((double)nPrintHeight * 0.02);
		}
	}
	else
	{
		if(cboPrintScale->ItemIndex == 1)//페이지맞춤(기본)//
		{
			bmpWM->Width  = asLabel.Length() * 12;
			bmpWM->Height = nFontHeight;
			//210628
//			if(nPrintWidth > nPrintHeight)//Landscape
//			{
//				bmpWM->Width  = (int)((double)nPrintWidth * 0.2);
//				bmpWM->Height = (int)((double)nPrintHeight * 0.02);
//			}
//			else//Portrait
//			{
//				bmpWM->Width  = (int)((double)nPrintWidth * 0.5);
//				bmpWM->Height = (int)((double)nPrintHeight * 0.02);
//			}
		}
		else if(cboPrintScale->ItemIndex == 0)//실제크기//
		{
			bmpWM->Width  = asLabel.Length() * 12;
			bmpWM->Height = nFontHeight;
			//210628
//			bmpWM->Width  = (int)((double)nPrintWidth * 0.2);
//			bmpWM->Height = (int)((double)nPrintHeight * 0.02);
		}
	}

	HDC pDraw    		= bmpWM->Canvas->Handle;
	TCanvas  *pCanvas   = bmpWM->Canvas;
	HPEN pen;
	HFONT m_font;
	HFONT hOldFont, hOldFontA;
	TPoint tpText;
	int fontwidth = (int)((double)bmpWM->Height * 0.7);//201015//24->32-> (bmpWM->Height - 8)

	m_font    = ::CreateFont(fontwidth, 0, 0, 0, FW_HEAVY, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "나눔고딕" );
	hOldFont  = (HFONT)::SelectObject(pDraw, m_font);

	::SetBkMode(pDraw, TRANSPARENT);
	::SetTextColor(pDraw, clBlue);

	pCanvas->TextOutA((bmpWM->Height - fontwidth) / 2, (bmpWM->Height - fontwidth) / 2, asLabel);

	::SelectObject(pDraw, hOldFont);
	::DeleteObject(m_font);

	//bmpWM->SaveToFile(asSaveWM);

	//Save JPG
	//asSaveWM	= ROOTPATH + "tmp\\SaveWM.jpg";
	TJPEGImage *jpgWM = new TJPEGImage();
	jpgWM->CompressionQuality = 70;
	jpgWM->Compress();
	//jpgWM->PixelFormat = pf24bit;
	jpgWM->Assign(bmpWM);
	jpgWM->SaveToFile(asSaveWM);

	delete jpgWM;
	jpgWM = NULL;

	delete bmpWM;
	bmpWM = NULL;

	//---
	FIBITMAP* dibOrg;
	FIBITMAP* dibWM;
	FREE_IMAGE_FORMAT 	fiformatWM;

	dibOrg	= FreeImage_Clone(printDIB);

	fiformatWM	= FreeImage_GetFileType(asSaveWM.c_str(), 16);
	dibWM		= FreeImage_Load(fiformatWM, asSaveWM.c_str());

	if(cboPrintScale->ItemIndex == 1)//페이지맞춤(기본)//
		FreeImage_Paste(dibOrg, dibWM, fontwidth, fontwidth, 110/*alpha*/);
	else if(cboPrintScale->ItemIndex == 0)//실제크기//
		FreeImage_Paste(dibOrg, dibWM, 0, 0, 110/*alpha*/);
//	//FreeImage_Paste(m_DIBClone, dibWM, fontwidth, fontwidth, 110/*alpha*/);
//	FreeImage_Save(FIF_JPEG, dibOrg, _asDstFile.c_str());

	if(printDIB != NULL)
	{
		FreeImage_Unload(printDIB);
		printDIB	= NULL;
	}
	printDIB	= FreeImage_Clone(dibOrg);

	FreeImage_Unload(dibOrg);
	dibOrg = NULL;

	FreeImage_Unload(dibWM);
	dibWM = NULL;

	if( FileExists(asSaveWM) )
		DeleteFile(asSaveWM);
}
//---------------------------------------------------------------------------
//201223//
void __fastcall TfrmPrintSetting::funcDrawDoc8Stamp(AnsiString _asPrintFile)
{
	if(frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp] != NULL)
	{
		int nPrintWidth 	= 0;
		int nPrintHeight	= 0;
		int nStampWidth 	= 0;
		int nStampHeight	= 0;

		if(printDIB != NULL)
		{
			nPrintWidth  	= FreeImage_GetWidth(printDIB);
			nPrintHeight 	= FreeImage_GetHeight(printDIB);

			//################################################################
			Graphics::TBitmap *printBmp = new Graphics::TBitmap();
			printBmp->PixelFormat = pf24bit;

			printBmp->Width 	= nPrintWidth;
			printBmp->Height 	= nPrintHeight;

			::SetStretchBltMode(printBmp->Canvas->Handle, HALFTONE);
			::StretchDIBits(printBmp->Canvas->Handle, 0, 0, nPrintWidth, nPrintHeight, 0, 0, nPrintWidth, nPrintHeight, FreeImage_GetBits(printDIB), FreeImage_GetInfo(printDIB), DIB_RGB_COLORS, SRCCOPY);
			//################################################################

			double dBmRate = (double)nPrintHeight / (double)nPrintWidth;
			dBmRate = RoundTo(dBmRate, -2) * 100;
			int nStampLeft = (nPrintWidth * 0.55);
			int nStampTop = (nPrintHeight * 0.88);
			int nStampW = (frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Width)*dBmRate/100;
			int nStampH = (frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Height)*dBmRate/100;
			::AlphaBlend(printBmp->Canvas->Handle, nStampLeft, nStampTop, nStampW, nStampH, frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Canvas->Handle, 0, 0, frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Width, frmMain->BITMAP_BTN_TGA[frmMain->TgaStamp]->Height, frmMain->flagbf);

			//---
			TJPEGImage *saveJpg;
			//Save To Jpg
			saveJpg = new TJPEGImage();
			saveJpg->CompressionQuality = 70;
			saveJpg->Compress();
			//saveJpg->PixelFormat = pf24bit;
			saveJpg->Assign(printBmp);
			saveJpg->SaveToFile(_asPrintFile);

			delete saveJpg;
			saveJpg = NULL;
			//---

			if(printDIB != NULL)
			{
				FreeImage_Unload(printDIB);
				printDIB	= NULL;

				printDIB		= FreeImage_Load(FreeImage_GetFileType(_asPrintFile.c_str(), 16), _asPrintFile.c_str());
			}
		}
	}
}
//---------------------------------------------------------------------------
