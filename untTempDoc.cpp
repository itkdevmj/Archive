//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "bsPngImageList"
#pragma resource "*.dfm"

#pragma warn -8004

#include "common.h"


TfrmTempDoc *frmTempDoc;
//---------------------------------------------------------------------------
__fastcall TfrmTempDoc::TfrmTempDoc(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::FormCreate(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::FormShow(TObject *Sender)
{
	this->Left	= frmMain->pnlSearchBar->Width + 4;
	this->Top	= 4;

	m_nTmpDocIndex = 0;

	funcRefreshShow();
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::FormClose(TObject *Sender, TCloseAction &Action)
{
	funcDeleteListTempDoc();

	funcImageViewClear();
	funcFreeImage();
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::funcRefreshShow()
{
	Timer1->Enabled = true;

	funcSetWaitWindows(true);

	m_nTmpDocCount = (int)m_vTmpDocList.size();
	funcSetPrevNextImage();

	if(m_nTmpDocIndex > -1)
	{
		AnsiString asPathName = funcGetLocalFilePath((char*)m_vTmpDocList[m_nTmpDocIndex].PATH_NAME);
		if(FileExists(asPathName))
		{
			this->funcLoadImage(asPathName);
			if(IMGSCREEN1->Picture->Bitmap != NULL && IMGSCREEN1->Picture->Bitmap->Width > 0)
				pnlMain->SetFocus();
		}
	}

	funcSetWaitWindows(false);
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::btnCloseTypeBClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::funcSetWaitWindows(bool bSetValue)
{
	palWait->Left = (this->Width/2) - (palWait->Width/2);
	palWait->Top  = (this->Height/2) - (palWait->Height/2);
	//palWait->Top  = (palClient->Height/2) - (palWait->Height/2);//191126//

	if (this->palWait->Visible == !bSetValue)
	{
		palWait->Visible = bSetValue;

		if (bSetValue)		Screen->Cursor     = crHourGlass;
		else            	Screen->Cursor     = crDefault;

		if(!bSetValue)
		{
			lblDownloadCnt->Visible	= false;//201201//
			lblWait1->Caption  = "잠시만 기다려 주세요.";
			lblWait2->Caption  = "선택 작업을 적용중입니다.";
		}
		else
		{
           	palWait->BringToFront();
        }
	}

	//if(pnlImgDocView->Visible == false && IMGSCREEN2->Picture->Bitmap != NULL)
		Application->ProcessMessages();
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::funcProcessTempDoc()
{
	if (!DirectoryExists(frmMain->TMPTHUMBPATH))
		CreateDir(frmMain->TMPTHUMBPATH);

	funcGotoPageTempDoc();
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::funcGotoPageTempDoc()
{
	funcDeleteListTempDoc();
	funcCreateListTempDoc();

	//=============================================================
	int	nIndex	= -1;

	lblWait2->Caption  = "미리보기 이미지를 구성중입니다.";
	funcSetWaitWindows(true);

    //썸네일 다운로드//
	try{
		//이미 [임시보관] 버튼 클릭 시, m_vTmpDocList를 저장한다.//
	}
	__finally{
		for(int i = 0; i < m_nTmpDocCount; i++)
		{
			nIndex++;
			funcMakeDynamicTempDoc(nIndex, i);
		}

		lblCount->Caption = FormatFloat("#,##0", nIndex+1) + "건";
	}

	funcSetWaitWindows(false);
}
//---------------------------------------------------------------------------

//***************************************************************************
//
// 검색결과 문서와 같은 DOC_KIND 문서가 있는 경우,
// 해당 문서의 THUMBNAIL을 보여주는 기능 -  동적 생성
//
//***************************************************************************
void __fastcall TfrmTempDoc::funcCreateListTempDoc()
{
	if( pnlDocList == NULL)
		pnlDocList  = new TList();
	if( imgDocList == NULL)
		imgDocList  = new TList();
	if( lblDocList == NULL)
		lblDocList  = new TList();
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::funcDeleteListTempDoc()
{
	//btnCreate4
	if(pnlDocList != NULL)
	{
		for(int i = 0; i < pnlDocList->Count; i++)
		{
			TPanel *pnlDC = (TPanel *)pnlDocList->Items[i];
			if(pnlDC != NULL)
			{
				TImage *imgDocDC	= (TImage *)imgDocList->Items[i];
				if(imgDocDC != NULL)
				{
					imgDocList->Items[i] = NULL;
					delete imgDocDC;
					imgDocDC	= NULL;
				}

				TLabel *lblDocDC	= (TLabel *)lblDocList->Items[i];
				if(lblDocDC != NULL)
				{
					lblDocList->Items[i] = NULL;
					delete lblDocDC;
					lblDocDC	= NULL;
				}

				pnlDocList->Items[i] = NULL;
				delete pnlDC;
				pnlDC	= NULL;
			}
		}

		imgDocList->Clear();
		delete imgDocList;
		imgDocList = NULL;

		lblDocList->Clear();
		delete lblDocList;
		lblDocList = NULL;

		pnlDocList->Clear();
		delete pnlDocList;
		pnlDocList = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::funcMakeDynamicTempDoc(int _nIndex, int _nVectorIdx)
{
	AnsiString 	asPageNo	= "";
	AnsiString 	asStr		= "";
	AnsiString 	asPathName 	= "";
	AnsiString 	asFileName 	= "";
	AnsiString 	asTempDocFile = "";
	//download 받은 thumbnail경로//
	//200603//#11
	AnsiString 	asFileExt 	= "";
	int         nLeft		= 0;
	int         nTop		= 0;
	int         nWidth		= frmMain->THUMBNAILSIZE;
	int         nHeight		= frmMain->THUMBNAILSIZE;

	if(frmMain->INI_AS_THUMBEXT	== "JPG")	asFileExt 	= ".jpg";
	else                                 	asFileExt 	= ".bmp";

	asTempDocFile	= ExtractFileName((char *)m_vTmpDocList[_nVectorIdx].THUMB_NAME);
	asTempDocFile = frmMain->TMPTHUMBPATH + asTempDocFile;

	//---
	TPanel *pnlDC 			= new TPanel(ScrollBox1);
	TImage *imgDocDC 		= new TImage(pnlDC);
	imgDocDC->Width			= frmMain->THUMBNAILSIZE;
	imgDocDC->Height		= frmMain->THUMBNAILSIZE;

	//썸네일 미 존재 시, NoImage표시//
	if(!FileExists(asTempDocFile) || asTempDocFile.IsEmpty())
		imgDocDC->Picture->Bitmap->Assign(frmMain->BITMAP_BTN_ETC[frmMain->NoImage120]);
	else
		imgDocDC->Picture->LoadFromFile(asTempDocFile);

	//=====================================================
	//Scale
	//=====================================================
	nLeft	= nWidth * _nIndex;//(_nIndex % 10);
	nTop	= 0;//(nWidth + 20) * (_nIndex / 10);

	//=====================================================
	//Panel
	//=====================================================
	pnlDC->Align			= alNone;
	pnlDC->Tag 				= _nVectorIdx;
	pnlDC->Caption			= "pnlDC" + IntToStr(_nIndex + 1);
	pnlDC->BevelKind    	= Controls::bkNone;
	pnlDC->BevelOuter 		= Controls::bvNone;
	pnlDC->SetBounds(nLeft, nTop, nWidth, nHeight + 20);
	pnlDC->ParentFont		= true;
	pnlDC->ParentBackground = false;
	pnlDC->Parent 			= ScrollBox1;
	pnlDC->OnClick 			= imgTempDocDC_onClick;

	//=====================================================
	//Label
	//=====================================================
	TLabel *lblDocDC 		= new TLabel(pnlDC);
	lblDocDC->Parent 		= pnlDC;
	lblDocDC->Tag 			= _nVectorIdx;
	asPathName	= (char*)m_vTmpDocList[_nVectorIdx].PATH_NAME;
	asFileName	= ExtractFileName(asPathName);
	lblDocDC->Caption 		= frmMain->INIINFO.DOCKINDNAME[m_vTmpDocList[_nVectorIdx].DOC_NO];
	lblDocDC->Alignment		= taCenter;
	lblDocDC->SetBounds(4, 4, nWidth-8, 16);

	lblDocDC->ParentFont	= true;
	lblDocDC->Transparent   = true;
	if(_nVectorIdx == m_nTmpDocIndex)
	{
		lblDocDC->Font->Style   = TFontStyles() << fsBold;
		lblDocDC->Font->Color	= clWhite;
		pnlDC->Color	  		= (TColor)RGB(243, 115, 33);
	}
	else
	{
		lblDocDC->Font->Color	= clBlack;
		pnlDC->Color			= clCream;
	}

	//=====================================================
	//IMAGE
	//=====================================================
	//---
	if(imgDocDC->Picture != NULL)
	{
		imgDocDC->Parent 		= pnlDC;
		imgDocDC->Tag 			= _nVectorIdx;
		imgDocDC->Hint          = IntToStr(m_vTmpDocList[_nVectorIdx].DOC_NO);//문서번호(이동결의서:1);
		imgDocDC->SetBounds((frmMain->THUMBNAILSIZE-imgDocDC->Picture->Width)/2+1, 20, imgDocDC->Picture->Width-2, imgDocDC->Picture->Height-2);
		imgDocDC->OnClick 		= imgTempDocDC_onClick;
	}

	imgDocList->Add(imgDocDC);
	lblDocList->Add(lblDocDC);
	pnlDocList->Add(pnlDC);
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::funcShowCurrentLabel()
{
	if(pnlDocList != NULL)
	{
		if(m_nTmpDocIndex < 0)
		{
			return;
		}

		//======================================================================
		//241015//#전주#중앙정보테크//
		//======================================================================
		int nSkinColor	= frmMain->SIDOINI->ReadInteger(L"FUNCTIONS", L"VALUE", (TColor)RGB(243, 115, 33));//16750131
		int nSkinColor2	= frmMain->SIDOINI->ReadInteger(L"FUNCTIONS", L"VALUE2", (TColor)RGB(51, 150, 255));//16760962
		for(int i = 0; i < pnlDocList->Count; i++)
		{
			TPanel *pnlDC = (TPanel *)pnlDocList->Items[i];
			if(pnlDC != NULL)
			{
				TLabel *lblDocDC 		= (TLabel *)lblDocList->Items[i];
				if(lblDocDC != NULL)
				{
					if(pnlDC->Tag == m_nTmpDocIndex)
					{
						lblDocDC->Font->Style   = TFontStyles() << fsBold;
						lblDocDC->Font->Color	= clWhite;
						pnlDC->Color	  		= (TColor)nSkinColor;
					}
					else
					{
						lblDocDC->Font->Style   = TFontStyles() >> fsBold;
						lblDocDC->Font->Color	= clBlack;
						pnlDC->Color	  		= clCream;
						pnlDC->BevelOuter 		= Controls::bvNone;
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

AnsiString __fastcall TfrmTempDoc::funcLoadImageTempDoc(AnsiString _asFilename)
{
	GetImageInfo		getImageInfo;

	memset(&getImageInfo, 0x00, sizeof(GetImageInfo));

	Graphics::TBitmap  	*bmpTempDoc;
	bmpTempDoc = NULL;

	Application->ProcessMessages();

	AnsiString asTempDocFile	= "";

	getImageInfo.asPathName	= _asFilename;

	try {
		getImageInfo.m_DIB = FreeImage_Load(FreeImage_GetFileType(getImageInfo.asPathName.c_str(), 16), getImageInfo.asPathName.c_str());
	}
	catch (Exception &exception) {
		AnsiString strMsg = "Exception is broken up to load mGetImageInfo.m_DIB";
		frmMsg->funcMessageDlg("이미지 DIB 확인:", strMsg, 2);
		return "";
	}

	if (!getImageInfo.m_DIB) {
		AnsiString strMsg = "getImageInfo.m_DIB is NULL";
		frmMsg->funcMessageDlg("이미지 DIB 확인:", strMsg, 2);
		return "";
	}

	try {
		getImageInfo.nBPP = FreeImage_GetBPP(getImageInfo.m_DIB);
		getImageInfo.nImageWidth  = FreeImage_GetWidth(getImageInfo.m_DIB);
		getImageInfo.nImageHeight = FreeImage_GetHeight(getImageInfo.m_DIB);

		getImageInfo.mBitMapInfo = FreeImage_GetInfo(getImageInfo.m_DIB);
		memcpy(&getImageInfo.mBitMapHeadInfo, &getImageInfo.mBitMapInfo->bmiHeader, sizeof(_mBitmapHeader));

		if(mGetImageInfo.fiformat == FIF_TIFF)
		{
			mGetImageInfo.mBitMapInfo->bmiHeader.biCompression	= BI_RGB;
		}

		double dShortenRate = 0.0;
		if(getImageInfo.nImageWidth > getImageInfo.nImageHeight)
		{
			dShortenRate = (double)frmMain->THUMBNAILSIZE / (double)getImageInfo.nImageWidth;
			bmpTempDoc->Width 	= frmMain->THUMBNAILSIZE;
			bmpTempDoc->Height 	= (int)((double)getImageInfo.nImageHeight * (double)dShortenRate);
		}
		else
		{
			dShortenRate = (double)frmMain->THUMBNAILSIZE / (double)getImageInfo.nImageHeight;
			bmpTempDoc->Width 	= (int)((double)getImageInfo.nImageWidth * (double)dShortenRate);
			bmpTempDoc->Height 	= frmMain->THUMBNAILSIZE;
		}

		::SetStretchBltMode(bmpTempDoc->Canvas->Handle, HALFTONE);
		::StretchDIBits(bmpTempDoc->Canvas->Handle,
					0, 0, bmpTempDoc->Width, bmpTempDoc->Height,
					0, 0, getImageInfo.nImageWidth, getImageInfo.nImageHeight,
					FreeImage_GetBits(getImageInfo.m_DIB),
					getImageInfo.mBitMapInfo,
					DIB_RGB_COLORS,
					SRCCOPY);

		if(getImageInfo.m_DIB == NULL)
		{
			AnsiString strMsg = "1getImageInfo.m_DIB is NULL before calling SetDIBitsToDevice";
			frmMsg->funcMessageDlg("이미지 DIB 확인:", strMsg, 2);
		}
	}
	__finally {
		asTempDocFile = ExtractFileName(_asFilename);
		AnsiString asExt = ".bmp";
		int pos = asTempDocFile.Pos(".");
		if (pos > 0) {
			asTempDocFile = asTempDocFile.SubString(1, pos-1);
		}
		asTempDocFile = frmMain->THUMBPATH + asTempDocFile + asExt;
		if(FileExists(asTempDocFile))
			DeleteFile(asTempDocFile);
		bmpTempDoc->SaveToFile(asTempDocFile);
	}

	if (getImageInfo.m_DIB != NULL){
		FreeImage_Unload(getImageInfo.m_DIB);
		getImageInfo.m_DIB = NULL;
	}

	/*//201015//
	delete bmpLoad;
	bmpLoad->Handle = NULL;
	bmpLoad = NULL;
	*/

	return asTempDocFile;
}
//---------------------------------------------------------------------------

/*
void __fastcall TfrmMain::imgTempDocDC_onClick(TObject *Sender)
{
	if(palWait->Visible)
		return;

	int nSelDoc				= dynamic_cast<TImage*>(Sender)->Hint.ToInt();
	int nTag 				= dynamic_cast<TImage*>(Sender)->Tag;
	int nPnlIndex			= -1;

	if(nTag < 0)
	{
		//200123//여기는 들어오면 안됨//
		frmMsg->funcMessageDlg("파일확인:", "미리보기파일(Tag)에 문제가 있습니다. 개발사에 문의해주세요.", 2);
		return;
	}

	//==================================================
	//231212//#DOC8_OVERLAP//
	if(m_nViewDocNo == 8)
		funcInitDoc08Bar(false);//#DOC08_INFO_ICON
	//==================================================

	m_nTempDocCurrIndex = nTag;//200105

	AnsiString asPathName = "";//FTP원본이미지경로//
	asPathName = (char *)m_vTmpDocList[nTag].PATH_NAME;

	if( funcGetImage(asPathName, nSelDoc, 1) )
	{
		m_nFTPPathIndex 	= eFunc->funcGetDocFTPPathListIndex(asPathName);
		if(frmMain->m_nFTPPathIndex > -1)
			frmMain->funcSetFTPbtnPrevNext();//

		m_nTempDocCurrIndex 	= eFunc->funcGetDocTempDocPathListIndex(asPathName);
		if(m_nTempDocCurrIndex > -1)
		{
			//funcProcessTempDoc();
			funcShowCurrentTempDocLabel();
		}

		if(_CURRENT_WORKMODE != "DOCUMENT")
			IMGMODECHANGEClick(IMGMODECHANGEDOC);

		for(int i = 0; i < pnlDocList->Count; i++)
		{

			TPanel *pnlDC1 = (TPanel *)pnlDocList->Items[i];
			if(m_nTempDocCurrIndex == pnlDC1->Tag)
			{
				nPnlIndex = i;
				break;
			}
		}

		if(nPnlIndex > -1)
		{
			//200623//TPanel *pnlDC = (TPanel *)pnlDocList->Items[nPnlIndex];
			TImage *imgDC = (TImage *)imgDocList->Items[nPnlIndex];
			if(imgDC != NULL)
			{
				nSelDoc = imgDC->Hint.ToInt();
				AnsiString asKwon 		= m_vTmpDocList[nTag].KWON_NO;
				if(asKwon == "") asKwon = "0";
				frmSql->funcReadDocDBInfo(nSelDoc, asKwon, asPathName);
				//_nType : 1 => treSystemDblClick
				//_nType : 2 => FTP Prev/Next File Path DB Info Display //FTP 앞뒤이미지 DB속성정보//
				//_nType : 3 => PoiPopup>문서심볼클릭
				eMainSub->funcSetDBInfo(2);//231212//frmResultList->funcSetComponent3();

				//200407
				//#OWNNAMES#
				if(nSelDoc == 8 && INI_B_OWNINFO)
				{
					funcProcessDoc8OwnNames(asPathName);//#OWNINFO#
				}
			}
			//asPathName으로 ftpprevnext에서의 index 찾기//

			if(IMGSCREEN2->Picture->Bitmap != NULL && IMGSCREEN2->Picture->Bitmap->Width > 0)//220227
				pnlMain->SetFocus();
		}
		//200805//palClient->SetFocus();
	}
}
//---------------------------------------------------------------------------
*/
void __fastcall TfrmTempDoc::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(this->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::Timer1Timer(TObject *Sender)
{
	Timer1->Enabled = false;

	funcProcessTempDoc();

}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::imgTempDocDC_onClick(TObject *Sender)
{
	if(palWait->Visible)
		return;

	int nSelDoc				= dynamic_cast<TImage*>(Sender)->Hint.ToInt();
	int nTag 				= dynamic_cast<TImage*>(Sender)->Tag;
	if(nTag < 0)
	{
		//200123//여기는 들어오면 안됨//
		frmMsg->funcMessageDlg("파일확인:", "미리보기파일(Tag)에 문제가 있습니다. 개발사에 문의해주세요.", 2);
		return;
	}

	m_nTmpDocIndex = nTag;
	funcProcessViewImage();
//[Caution]Tag에 Index 정보를 담고 있어서 삭제하면 안됨//
//	else//'임시보관' 했으나, 어쩌다가 파일이 없는 경우는 Vector에서 삭제함//
//	{
//		m_vTmpDocList.erase(m_vTmpDocList.begin() + nTag);
//	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::funcInitTempDoc()
{
	funcDeleteListTempDoc();
	funcCreateListTempDoc();

//	m_vTmpDocList.clear();
//	m_nTempDocCount		= 0;
//	m_nTempDocPathIndex 	= -1;
//	m_nTempDocCurrIndex   = -1;
//	m_nPerTempDocCnt		= 20;//201228//10->20//44270//Req//
//	m_bTempDocChecked		= false;//201126//
//
//	funcDeleteListTempDoc();
//	funcCreateListTempDoc();
//
//	//=======================================================
//	//201130//각 페이지당 전체체크여부//
//	pnlAllTempDoc->Visible	= false;
//	btnPreviewAct->Caption 	= "";
//	lblDownloadCnt->Caption	= "";
//	m_nDownloadCnt			= 0;
//	//=======================================================
}
//---------------------------------------------------------------------------

int __fastcall TfrmTempDoc::funcGetIndexList(AnsiString _asFilePath)
{
	AnsiString  asPathName = "";
	int nIndex = -1;

	for(int i = 0; i < (int)m_vTmpDocList.size(); i++)
	{
		asPathName = (char*)m_vTmpDocList[i].PATH_NAME;
		if( _asFilePath == asPathName )
		{
			nIndex = i;
			break;
		}
	}

	return nIndex;
}
//---------------------------------------------------------------------------


double __fastcall TfrmTempDoc::funcSetImageBaseScale()
{
	if (readImageWidth == 0 || readImageHeight == 0) {
		AnsiString strMsg = "이미지의 길이가 0입니다. 명령어 수행이 중지 됩니다.";
		ShowMessage(strMsg);
		return 0;
	}

	if (readImageWidth > pnlMain->Width || readImageHeight > pnlMain->Height)
	{
		double dRateW = (double)pnlMain->Width / (double)readImageWidth;
		double dRateH = (double)pnlMain->Height / (double)readImageHeight;

		m_dDocFitFactor = ( dRateW > dRateH ) ? (dRateH) : (dRateW);
	}

	return m_dDocFitFactor;
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::funcFreeImage()
{
	if (m_DIB != NULL){
		FreeImage_Unload(m_DIB);
		m_DIB = NULL;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmTempDoc::funcImageViewClear()
{
	this->IMGSCREEN1->Picture->Bitmap->Assign(NULL);
	this->pnlMain->Left = 0;
	this->pnlMain->Top  = 0;

	asPathName	= "";
	nImageWidth 	= 0;
	nImageHeight 	= 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::funcLoadImage(AnsiString _asFilename)
{
	funcImageViewClear();
	funcFreeImage();

	if (m_DIB != NULL){
		FreeImage_Unload(m_DIB);
		m_DIB 		= NULL;
		mBitMapInfo = NULL;
	}

	Application->ProcessMessages();

	asPathName  = _asFilename;
	fiformat	= FreeImage_GetFileType(_asFilename.c_str(), 16);

	try {
		if(fiformat != FIF_UNKNOWN)
			m_DIB = FreeImage_Load(fiformat, _asFilename.c_str());
	}
	catch (Exception &exception) {
		AnsiString strMsg = "Exception is broken up to load m_DIB";
		ShowMessage(strMsg);

		if(m_DIB != NULL){
			FreeImage_Unload(m_DIB);
			m_DIB = NULL;
		}
		return;
	}

	if (!m_DIB) {
		AnsiString strMsg = "m_DIB is NULL";
		ShowMessage(strMsg);
		return;
	}

	try {
		//FreeImage_SetTransparent(m_DIB, true);//210812//TEST//

		nImageWidth  	= FreeImage_GetWidth(m_DIB);
		nImageHeight 	= FreeImage_GetHeight(m_DIB);

		//==============================
		//221208//#PRINT_IMPROVE
		if(pnlMain->Align == alNone)
		{
			pnlMain->Width		= nImageWidth;
			pnlMain->Height		= nImageHeight;
			IMGSCREEN1->Width 	= nImageWidth;
			IMGSCREEN1->Height 	= nImageHeight;
		}
		else
		{
			IMGSCREEN1->Width 	= pnlMain->Width;
			IMGSCREEN1->Height 	= pnlMain->Height;
		}
		//==============================

		mBitMapInfo 	= FreeImage_GetInfo(m_DIB);

		//################################################################
		if(FreeImage_GetFileType(asPathName.c_str(), 16) == FIF_TIFF)
		{
			mBitMapInfo->bmiHeader.biCompression	= BI_RGB;
		}

		//200731//new
		//################################################################
		readImageWidth      = nImageWidth;
		readImageHeight     = nImageHeight;
		IMGSCREEN1->Left    = 0;
		IMGSCREEN1->Top     = 0;
		//################################################################

		//minj@230309//테두리 컬러가 너무 진하다고 해서 아래 기능을 사용했으나//
		//이제는 배경서식 테두리를 흐리게 했으므로 아래 기능이 필요없어짐//
//		//FreeImage_AdjustBrightness(m_DIB, 10);
//		FreeImage_AdjustContrast(m_DIB, 40);

//		//================================================================
//		//211028//TEST
//		FreeImage_AdjustContrast(m_DIB, 100);
//		FreeImage_Save(FIF_JPEG, m_DIB, AnsiString(frmMain->PRINTPATH + "TEST.jpg").c_str());
//		//================================================================
	}
	__finally {
		if(m_DIB == NULL)
		{
			AnsiString strMsg = "m_DIB is NULL before calling SetDIBitsToDevice";
			ShowMessage(strMsg);
			return;
		}

		this->funcFullView();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::funcFullView()
{
	m_dDocFactor	= funcSetImageBaseScale();

	if (m_dDocFactor == 0) {
		AnsiString strMsg = "m_dDocFactor is 0";
		ShowMessage(strMsg);
		return;
	}

	dScaleGap	    = 0.1;

	//===================================================
	//화면 중앙
	m_nSrcCenterX   = (-readImageWidth/2);
	m_nSrcCenterY   = (readImageHeight/2);
	m_nSrcWidth   	= (int)((double)IMGSCREEN1->Width/m_dDocFactor);
	m_nSrcHeight  	= (int)((double)IMGSCREEN1->Height/m_dDocFactor);
	realLeft     	= (int)(m_nSrcCenterX + (double)m_nSrcWidth/2);
	realTop      	= (int)(m_nSrcCenterY - (double)m_nSrcHeight/2);
	//===================================================

	func_DrawImage();

	pnlMain->SetFocus();
}
//---------------------------------------------------------------------------

//201217//이미지 확대 범위가 조금 작았으면 좋겠다//
//44230Req//지적원도 1단계에서 2단계 갈때 너무 훅 커진다//
//그래서 알씨 줌 크기를 반영//10%,20%,30%,50%,70%,100%,150%,200%,300%,500%,700%,1000%,2000%,3000%,5000%
//우리는 제한이 없으니까 1000% 이후로는 500%씩 커지게 하자//
double __fastcall TfrmTempDoc::funcGetImageScale(bool _bZoomIn)
{
	if(_bZoomIn)//ZoomIn
	{
		if(m_dDocFactor < 0.1)//10%
			m_dDocFactor	= 0.1;
		else if(m_dDocFactor < 0.2)//20%
			m_dDocFactor	= 0.2;
		else if(m_dDocFactor < 0.3)//30%
			m_dDocFactor	= 0.3;
		else if(m_dDocFactor < 0.5)//50%
			m_dDocFactor	= 0.5;
		else if(m_dDocFactor < 0.7)//70%
			m_dDocFactor	= 0.7;
		else if(m_dDocFactor < 1.0)//100%
			m_dDocFactor	= 1.0;
		else if(m_dDocFactor < 1.5)//150%
			m_dDocFactor	= 1.5;
		else if(m_dDocFactor < 2.0)//200%
			m_dDocFactor	= 2.0;
		else if(m_dDocFactor < 3.0)//300%
			m_dDocFactor	= 3.0;
		else if(m_dDocFactor < 5.0)//500%
			m_dDocFactor	= 5.0;
		else if(m_dDocFactor < 7.0)//700%
			m_dDocFactor	= 7.0;
		else if(m_dDocFactor < 10.0)//1000%
			m_dDocFactor	= 10.0;
		else if(m_dDocFactor >= 10.0)//1000% 이상//
			m_dDocFactor	+= 5;
	}
	else//ZoomOut
	{
		if(m_dDocFactor - 5 >= 10.0)//1000% 이상//
			m_dDocFactor	-= 5;
		else if(m_dDocFactor > 10.0)//1000%
			m_dDocFactor	= 10.0;
		else if(m_dDocFactor > 7.0)//700%
			m_dDocFactor	= 7.0;
		else if(m_dDocFactor > 5.0)//500%
			m_dDocFactor	= 5.0;
		else if(m_dDocFactor > 3.0)//300%
			m_dDocFactor	= 3.0;
		else if(m_dDocFactor > 2.0)//200%
			m_dDocFactor	= 2.0;
		else if(m_dDocFactor > 1.5)//150%
			m_dDocFactor	= 1.5;
		else if(m_dDocFactor > 1.0)//100%
			m_dDocFactor	= 1.0;
		else if(m_dDocFactor > 0.7)//70%
			m_dDocFactor	= 0.7;
		else if(m_dDocFactor > 0.5)//50%
			m_dDocFactor	= 0.5;
		else if(m_dDocFactor > 0.3)//30%
			m_dDocFactor	= 0.3;
		else if(m_dDocFactor > 0.2)//20%
			m_dDocFactor	= 0.2;
		else if(m_dDocFactor > 0.1)//10%
			m_dDocFactor	= 0.1;

		if(m_dDocFactor < m_dDocFitFactor)
			m_dDocFactor	= m_dDocFitFactor;
	}

	return m_dDocFactor;
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::func_DrawImage()
{
	IMGSCREEN1->Canvas->Lock();
	if(m_DIB != NULL)
	{
		IMGSCREEN1->Left    = 0;
		IMGSCREEN1->Top     = 0;

		IMGSCREEN1->Picture->Bitmap->Width  = IMGSCREEN1->Width;
		IMGSCREEN1->Picture->Bitmap->Height	= IMGSCREEN1->Height;

		TRect rect;
		rect.Left   = IMGSCREEN1->Left;
		rect.Top    = IMGSCREEN1->Top;
		rect.Right  = IMGSCREEN1->Width;
		rect.Bottom = IMGSCREEN1->Height;

		pDCDoc   = IMGSCREEN1->Canvas->Handle; //복사본
		memDCDoc = ::CreateCompatibleDC(IMGSCREEN1->Canvas->Handle);

		if(memDCDoc){
			hMembitmapDoc = ::CreateCompatibleBitmap(IMGSCREEN1->Canvas->Handle, IMGSCREEN1->Width, IMGSCREEN1->Height);
			if(hMembitmapDoc){
				pDCDoc = memDCDoc;
				pObjDoc = ::SelectObject(memDCDoc,hMembitmapDoc);
			}
		}

		//221209//TEST//hbrDoc   = ::CreateSolidBrush( 0x00ffffff ); //브러쉬
		hbrDoc   = ::CreateSolidBrush( 0x00404040 ); //브러쉬
		::FillRect( pDCDoc, &rect, hbrDoc  );
		DeleteObject( hbrDoc );

		::SetStretchBltMode(pDCDoc,HALFTONE);

		realPosX	=  -(double)realLeft;
		realPosY	= readImageHeight - m_nSrcHeight - (double)realTop;

		::StretchDIBits(pDCDoc, 0, 0, IMGSCREEN1->Width, IMGSCREEN1->Height, realPosX, realPosY, m_nSrcWidth, m_nSrcHeight, FreeImage_GetBits(m_DIB), FreeImage_GetInfo(m_DIB), DIB_RGB_COLORS, SRCCOPY);

		if (pDCDoc != IMGSCREEN1->Canvas->Handle){
			::BitBlt(IMGSCREEN1->Canvas->Handle, 0,0,rect.Width() ,rect.Height(), memDCDoc ,0 ,0 , SRCCOPY);
		}

		::DeleteDC(memDCDoc);
		::DeleteObject(hMembitmapDoc);
		::DeleteObject(pObjDoc);


		//==================================================================
        //이미지 밖 검정색 부분 처리//
		//==================================================================
		IMGSCREEN1->Canvas->Brush->Color = clGray;
		pDCDoc   = IMGSCREEN1->Canvas->Handle; //복사본
		TRect _rctRect;
		//Left
		if(realPosX < 0)
		{
			_rctRect.Left   = 0;
			_rctRect.Top    = 0;
			_rctRect.Right  =  -(int)((double)realPosX * m_dDocFactor);
			_rctRect.Bottom = IMGSCREEN1->Height;
			hbrDoc   = ::CreateSolidBrush( 0x00ffffff ); //브러쉬
			::FillRect( pDCDoc, &_rctRect, hbrDoc  );
			::SelectObject(pDCDoc, hbrDoc);
		}
		//Top
		if((double)(readImageHeight - realPosY) * m_dDocFactor < IMGSCREEN1->Height)
		{
			_rctRect.Left   = 0;
			_rctRect.Top    = 0;
			_rctRect.Right  = IMGSCREEN1->Width;
			_rctRect.Bottom = IMGSCREEN1->Height - (int)((double)(readImageHeight - realPosY) * m_dDocFactor);
			hbrDoc   = ::CreateSolidBrush( 0x00ffffff ); //브러쉬
			::FillRect( pDCDoc, &_rctRect, hbrDoc  );
			::SelectObject(pDCDoc, hbrDoc);
		}
		//Right
		if((double)(readImageWidth - realPosX) * m_dDocFactor < IMGSCREEN1->Width)
		{
			_rctRect.Left   = (int)((double)(readImageWidth - realPosX) * m_dDocFactor);
			_rctRect.Top    = 0;
			_rctRect.Right  = IMGSCREEN1->Width;
			_rctRect.Bottom = IMGSCREEN1->Height;
			hbrDoc   = ::CreateSolidBrush( 0x00ffffff ); //브러쉬
			::FillRect( pDCDoc, &_rctRect, hbrDoc  );
			::SelectObject(pDCDoc, hbrDoc);
		}
		//Bottom
		if((double)(realPosY + m_nSrcHeight) * m_dDocFactor < IMGSCREEN1->Height)
		{
			_rctRect.Left   = 0;
			_rctRect.Top    = (int)((double)(realPosY + m_nSrcHeight) * m_dDocFactor);
			_rctRect.Right  = IMGSCREEN1->Width;
			_rctRect.Bottom = IMGSCREEN1->Height;
			hbrDoc   = ::CreateSolidBrush( 0x00ffffff ); //브러쉬
			::FillRect( pDCDoc, &_rctRect, hbrDoc  );
			::SelectObject(pDCDoc, hbrDoc);
		}
		DeleteObject( hbrDoc );
		//------
		//==================================================================

		IMGSCREEN1->Invalidate();
	}
	IMGSCREEN1->Canvas->Unlock();
}
//---------------------------------------------------------------------------

AnsiString __fastcall TfrmTempDoc::funcGetLocalFilePath(AnsiString _asDBFilePath)
{
	AnsiString asFileName 	= ExtractFileName(_asDBFilePath);
	asFileName 	= frmMain->TMPDOCPATH + asFileName;
	return asFileName;
}
//---------------------------------------------------------------------------

bool __fastcall TfrmTempDoc::funcExistTempList(AnsiString _asFilePath)
{
	int nIndex = funcGetIndexList(_asFilePath);
	return nIndex > -1 ? true : false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::funcSetPrevNextImage()
{
	frmMain->funcFreeEachButtonImage(IMGPREV);
	frmMain->funcFreeEachButtonImage(IMGNEXT);
	if(m_nTmpDocCount == 0)
	{
		IMGPREV->Picture->Bitmap->Assign(frmMain->BITMAP_BTN_BUTTONS[0][frmMain->BtnPrev]);
		IMGNEXT->Picture->Bitmap->Assign(frmMain->BITMAP_BTN_BUTTONS[0][frmMain->BtnNext]);
	}
	else
	{
		IMGPREV->Picture->Bitmap->Assign(frmMain->BITMAP_BTN_BUTTONS[(m_nTmpDocIndex == 0) ? 0:1][frmMain->BtnPrev]);
		IMGNEXT->Picture->Bitmap->Assign(frmMain->BITMAP_BTN_BUTTONS[(m_nTmpDocIndex == m_nTmpDocCount-1) ? 0:1][frmMain->BtnNext]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::IMGPREVClick(TObject *Sender)
{
	if(m_nTmpDocIndex > 0)
	{
		m_nTmpDocIndex--;
		lblCount->Caption = "(" + IntToStr(m_nTmpDocIndex+1) + "/" + IntToStr(m_nTmpDocCount) + ")";
		funcProcessViewImage();

		if(m_nTmpDocIndex == 0)
		{
			frmMain->funcFreeEachButtonImage(IMGPREV);
			IMGPREV->Picture->Bitmap->Assign(frmMain->BITMAP_BTN_BUTTONS[1][frmMain->BtnPrev]);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::IMGPREVMouseEnter(TObject *Sender)
{
/*	if(m_nTmpDocIndex > 0)
	{
		frmMain->funcFreeEachButtonImage(IMGPREV);
		IMGPREV->Picture->Bitmap->Assign(frmMain->BITMAP_BTN_BUTTONS[1][frmMain->BtnPrev]);
	}*/
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::IMGPREVMouseLeave(TObject *Sender)
{
//	frmMain->funcFreeEachButtonImage(IMGPREV);
//	IMGPREV->Picture->Bitmap->Assign(frmMain->BITMAP_BTN_BUTTONS[0][frmMain->BtnPrev]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::IMGNEXTClick(TObject *Sender)
{
	if(m_nTmpDocIndex < m_nTmpDocCount - 1)
	{
		m_nTmpDocIndex++;
		lblCount->Caption = "(" + IntToStr(m_nTmpDocIndex+1) + "/" + IntToStr(m_nTmpDocCount) + ")";
		funcProcessViewImage();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::IMGNEXTMouseEnter(TObject *Sender)
{
/*	if(m_nTmpDocIndex < m_nTmpDocCount - 1)
	{
		frmMain->funcFreeEachButtonImage(IMGNEXT);
		IMGNEXT->Picture->Bitmap->Assign(frmMain->BITMAP_BTN_BUTTONS[1][frmMain->BtnNext]);
	}*/
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::IMGNEXTMouseLeave(TObject *Sender)
{
//	frmMain->funcFreeEachButtonImage(IMGNEXT);
//	IMGNEXT->Picture->Bitmap->Assign(frmMain->BITMAP_BTN_BUTTONS[0][frmMain->BtnNext]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmTempDoc::funcProcessViewImage()
{
	AnsiString asPathName	= m_vTmpDocList[m_nTmpDocIndex].PATH_NAME;
	if(asPathName != NULL)
	{
		asPathName = funcGetLocalFilePath(asPathName);
		if(FileExists(asPathName))
		{
			if( IMGNOIMAGE->Visible )	IMGNOIMAGE->Visible = false;
			if( !pnlMain->Visible )		pnlMain->Visible = true;
			funcLoadImage(asPathName);
		}
		else
		{
			if( !IMGNOIMAGE->Visible )	IMGNOIMAGE->Visible = true;
			if( pnlMain->Visible )		pnlMain->Visible = false;
		}

		funcShowCurrentLabel();
	}
}
//---------------------------------------------------------------------------

