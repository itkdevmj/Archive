//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"

#pragma warn -8004

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMemoViewer *frmMemoViewer;
//---------------------------------------------------------------------------
__fastcall TfrmMemoViewer::TfrmMemoViewer(TComponent* Owner)
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
		this->shpBG->Pen->Color			= (TColor)RGB(R, G, B);
		//shpWait->Pen->Color//
		//panWindowsMove->Color//
		this->panWindowsMove->Color		= (TColor)RGB(R, G, B);
		//pnlWaitT->Color//
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoViewer::FormCreate(TObject *Sender)
{
	VIEWERWIDTH		= IMGVIEW->Width;
	VIEWERHEIGHT	= IMGVIEW->Height;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoViewer::FormShow(TObject *Sender)
{
	if (!DirectoryExists(frmMemo->ADDFILEPATH))
		CreateDir(frmMemo->ADDFILEPATH);

	if (!DirectoryExists(frmMemo->ADDTHUMBPATH))
		CreateDir(frmMemo->ADDTHUMBPATH);

	if(m_bFromMemo)
	{
		if(frmMemo->Showing)
		{
			this->Left = frmMemo->Left + frmMemo->Width;
			this->Top  = frmMemo->Top + (frmMemo->Height - this->Height) / 2 - 20;
		}
		else
		{
			this->Left = (frmMain->Left + frmMain->Width - this->Width) / 2;
			this->Top  = frmMain->Top + frmMain->Height / 2 - this->Height / 2 - 20;
        }

		lblMemoTitle->Caption = "[제목:" + frmMemo->edtMemoTitle->Text + "]";
		lblCount->Caption = "(" + IntToStr(frmMemo->m_nThumbIndex+1) + "/" + IntToStr(frmMemo->m_nThumbCount) + ")";

		AnsiString asPathName	= "";
		if(frmMemo->pnlThumbList != NULL)
		{
			TPanel *pnlDocDC 		= (TPanel *)frmMemo->pnlThumbList->Items[frmMemo->m_nThumbIndex];
			if(pnlDocDC != NULL)
			{
				asPathName = pnlDocDC->Hint;
				if(asPathName != NULL)
				{
					if(FileExists(asPathName))
					{
						if( IMGNOIMAGE->Visible )		IMGNOIMAGE->Visible = false;
						if( !palMainView->Visible )		palMainView->Visible = true;
						funcLoadImage(asPathName);
					}
					else
					{
						if( !IMGNOIMAGE->Visible )		IMGNOIMAGE->Visible = true;
						if( palMainView->Visible )		palMainView->Visible = false;
					}
				}
			}
		}
	}
	else//포토아이콘 클릭 > 메모뷰어
	{
		this->Left = (frmMain->Left + frmMain->Width - this->Width) / 2;
		this->Top  = (frmMain->Top + frmMain->Height - this->Height) / 2;

		funcViewForm();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoViewer::funcClearForm()
{
	funcImageViewClear();

	frmMemo->m_nVectorCount	= 0;
	frmMemo->m_nVectorIndex = -1;

	//=========================================================
	//MemoInfo
	frmMemo->m_vMEMOINFO.clear();
	//MemoFile
	frmMemo->m_vMEMOFILE.clear();


	AnsiString asStr 		= "";
	lblMemoTitle->Caption	= "";
	lblCount->Caption		= "";
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoViewer::funcViewForm()
{
	AnsiString asPathName	= "";

	funcClearForm();

	if( !frmMemo->m_asSelectPoiKey.IsEmpty() )
	{
		frmMemo->funcReadMemoInfo(frmMemo->m_asSelectPoiKey);
		frmMemo->funcReadMemoFile(frmMemo->m_asSelectPoiKey);

		AnsiString asStr = (char*)frmMemo->m_vMEMOINFO[0].TITLE;
		lblMemoTitle->Caption	= "[제목:" + asStr + "]";
		frmMemo->m_nThumbCount  = frmMemo->m_vMEMOINFO[0].FILE_CNT;

		if(frmMemo->m_nThumbCount == 0)//여기 들어올 일이 없어야겠지?//
		{
			frmMsg->funcMessageDlg("사진 파일 부재:", "사진 파일이 없어 뷰어를 종료합니다.", 3);
			return;
		}


		for(int i = 0; i < (int)frmMemo->m_vMEMOFILE.size(); i++)
		{
			asPathName = frmMemo->funcDownloadFile(i);
			if(asPathName != NULL)
				strcpy(frmMemo->m_vMEMOFILE[i].LOCAL_PATH_NAME, asPathName.c_str());
		}
		frmMemo->m_nThumbIndex	= 0;
		lblCount->Caption = "(" + IntToStr(frmMemo->m_nThumbIndex+1) + "/" + IntToStr(frmMemo->m_nThumbCount) + ")";
	}

	asPathName	= frmMemo->m_vMEMOFILE[frmMemo->m_nThumbIndex].LOCAL_PATH_NAME;
	if(asPathName != NULL)
	{
		if(FileExists(asPathName))
		{
			if( IMGNOIMAGE->Visible )		IMGNOIMAGE->Visible = false;
			if( !palMainView->Visible )		palMainView->Visible = true;
			funcLoadImage(asPathName);
		}
		else
		{
			if( !IMGNOIMAGE->Visible )		IMGNOIMAGE->Visible = true;
			if( palMainView->Visible )		palMainView->Visible = false;
		}
	}
}
//---------------------------------------------------------------------------

////MemoViewer Open 상태에서 FTP에서 받지 않아도 되는 로컬파일 추가//
//void __fastcall TfrmMemoViewer::funcRefreshForm()
//{
//	lblCount->Caption = "(" + IntToStr(frmMemo->m_nThumbIndex+1) + "/" + IntToStr(frmMemo->m_nThumbCount) + ")";
//}
////---------------------------------------------------------------------------

void __fastcall TfrmMemoViewer::FormClose(TObject *Sender, TCloseAction &Action)
{
	m_bFromMemo	= false;

	funcImageViewClear();

	IMGVIEW->Picture->Bitmap	= NULL;
	IMGVIEW->Picture			= NULL;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoViewer::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(frmMemoViewer->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoViewer::btnCloseTypeBClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoViewer::funcFreeImage()
{
	if (mGetViewerImageInfo.m_DIB != NULL){
		FreeImage_Unload(mGetViewerImageInfo.m_DIB);
		mGetViewerImageInfo.m_DIB = NULL;
		memset(&mGetViewerImageInfo, 0x00, sizeof(mGetViewerImageInfo));
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoViewer::funcImageViewClear()
{
	if (mGetViewerImageInfo.m_DIB != NULL){
		FreeImage_Unload(mGetViewerImageInfo.m_DIB);
		mGetViewerImageInfo.m_DIB = NULL;
	}

	this->IMGVIEW->Picture->Bitmap->Assign(NULL);

	mGetViewerImageInfo.asPathName		= "";
	mGetViewerImageInfo.nImageWidth 	= 0;
	mGetViewerImageInfo.nImageHeight 	= 0;
	mGetViewerImageInfo.nBPP = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoViewer::funcLoadImage(AnsiString _asFilename)
{
	funcImageViewClear();
	funcFreeImage();

	if (mGetViewerImageInfo.m_DIB != NULL){
		FreeImage_Unload(mGetViewerImageInfo.m_DIB);
		mGetViewerImageInfo.m_DIB = NULL;
	}

	Graphics::TBitmap  	*bmpLoad;
	bmpLoad = NULL;

	Application->ProcessMessages();

	bmpLoad = new Graphics::TBitmap();
	mGetViewerImageInfo.bmpSource32 = new Graphics::TBitmap();

	Application->ProcessMessages();

	mGetViewerImageInfo.asPathName	= _asFilename;

	try {
		mGetViewerImageInfo.m_DIB = FreeImage_Load(FreeImage_GetFileType(mGetViewerImageInfo.asPathName.c_str(), 16), mGetViewerImageInfo.asPathName.c_str());
	}
	catch (Exception &exception) {
		AnsiString strMsg = "Exception is broken up to load mGetViewerImageInfo.m_DIB";
		frmMsg->funcMessageDlg("이미지 DIB 확인:", strMsg, 2);
		return;
	}

	if (!mGetViewerImageInfo.m_DIB) {
		AnsiString strMsg = "getImageInfo.m_DIB is NULL";
		frmMsg->funcMessageDlg("이미지 DIB 확인:", strMsg, 2);
		return;
	}

	try {
		frmMain->m_dDocFactor = 1;

		mGetViewerImageInfo.nBPP = FreeImage_GetBPP(mGetViewerImageInfo.m_DIB);
		mGetViewerImageInfo.nImageWidth  = FreeImage_GetWidth(mGetViewerImageInfo.m_DIB);
		mGetViewerImageInfo.nImageHeight = FreeImage_GetHeight(mGetViewerImageInfo.m_DIB);

		mGetViewerImageInfo.mBitMapInfo = FreeImage_GetInfo(mGetViewerImageInfo.m_DIB);
		memcpy(&mGetViewerImageInfo.mBitMapHeadInfo, &mGetViewerImageInfo.mBitMapInfo->bmiHeader, sizeof(_mBitmapHeader));

		if(FreeImage_GetFileType(mGetViewerImageInfo.asPathName.c_str(), 16) == FIF_TIFF)
		{
			bmpLoad->PixelFormat = pf24bit;
		}
		else
		{
			if (mGetViewerImageInfo.nBPP == 1)
				bmpLoad->PixelFormat = pf1bit;
			else if (mGetViewerImageInfo.nBPP == 8)
				bmpLoad->PixelFormat = pf8bit;
			else if (mGetViewerImageInfo.nBPP == 16)
				bmpLoad->PixelFormat = pf16bit;
			else if (mGetViewerImageInfo.nBPP == 24)
				bmpLoad->PixelFormat = pf24bit;
			else if (mGetViewerImageInfo.nBPP == 32)
				bmpLoad->PixelFormat = pf32bit;
			else
				bmpLoad->PixelFormat = pf24bit;
		}

		double dMaxImageLen = 0;
		if (frmMain->INIUSERSETINFO.MEMORYSIZE < 1)
			frmMain->INIUSERSETINFO.MEMORYSIZE = 4000;

		if (mGetViewerImageInfo.nImageWidth > frmMain->INIUSERSETINFO.MEMORYSIZE || mGetViewerImageInfo.nImageHeight > frmMain->INIUSERSETINFO.MEMORYSIZE)
		{
			(mGetViewerImageInfo.nImageWidth > mGetViewerImageInfo.nImageHeight) ? (dMaxImageLen = mGetViewerImageInfo.nImageWidth) : (dMaxImageLen = mGetViewerImageInfo.nImageHeight);

			frmMain->m_dDocFactor = frmMain->INIUSERSETINFO.MEMORYSIZE / dMaxImageLen;

			//////////////
			bmpLoad->Width  = mGetViewerImageInfo.nImageWidth;
			bmpLoad->Height = mGetViewerImageInfo.nImageHeight;

			//200108//31110.10100.1.6.0 은 정상//31110.10100.1.178.0 은 300dpi인데, 2835로 들어온다//
			if(mGetViewerImageInfo.mBitMapHeadInfo.biXPelsPerMeter == 2835 && mGetViewerImageInfo.mBitMapHeadInfo.biYPelsPerMeter == 2835)
			{
				mGetViewerImageInfo.mBitMapHeadInfo.biXPelsPerMeter = 11811;
				mGetViewerImageInfo.mBitMapHeadInfo.biYPelsPerMeter = 11811;
			}

			bmpLoad->Width = mGetViewerImageInfo.nImageWidth;
			bmpLoad->Height = mGetViewerImageInfo.nImageHeight;
	        ::SetStretchBltMode(bmpLoad->Canvas->Handle, HALFTONE);
	        ::StretchDIBits(bmpLoad->Canvas->Handle,
				        0, 0, bmpLoad->Width, bmpLoad->Height,
						0, 0, mGetViewerImageInfo.nImageWidth, mGetViewerImageInfo.nImageHeight,
				        FreeImage_GetBits(mGetViewerImageInfo.m_DIB),
				        mGetViewerImageInfo.mBitMapInfo,
				        DIB_RGB_COLORS,
				        SRCCOPY);
		}
		else
		{
			mGetViewerImageInfo.nImageWidth  = (int)((double)mGetViewerImageInfo.nImageWidth  * (double)frmMain->m_dDocFactor);
			mGetViewerImageInfo.nImageHeight = (int)((double)mGetViewerImageInfo.nImageHeight * (double)frmMain->m_dDocFactor);

			bmpLoad->Width = mGetViewerImageInfo.nImageWidth;
			bmpLoad->Height = mGetViewerImageInfo.nImageHeight;

			::SetDIBitsToDevice(bmpLoad->Canvas->Handle ,
								0, 0, mGetViewerImageInfo.nImageWidth, mGetViewerImageInfo.nImageHeight,
								0, 0, 0, mGetViewerImageInfo.nImageHeight,
								FreeImage_GetBits(mGetViewerImageInfo.m_DIB),
								mGetViewerImageInfo.mBitMapInfo,
								DIB_RGB_COLORS);    //DIB_PAL_COLORS
		}

		AnsiString asDestFile0 = frmMain->ROOTPATH + "tmp\\viewer_loadimage.bmp";
		if(FileExists(asDestFile0))
			DeleteFile(asDestFile0);
		FreeImage_Save(FIF_BMP, mGetViewerImageInfo.m_DIB, asDestFile0.c_str(), BMP_DEFAULT);

		if(mGetViewerImageInfo.m_DIB == NULL)
		{
			AnsiString strMsg = "1getImageInfo.m_DIB is NULL before calling SetDIBitsToDevice";
			frmMsg->funcMessageDlg("이미지 DIB 확인:", strMsg, 2);
		}
	}
	__finally {
		mGetViewerImageInfo.bmpSource32->Assign(bmpLoad);

		this->funcFullView();

		mCurrScrImageInfo.nImageWidth = mGetViewerImageInfo.nImageWidth;
		mCurrScrImageInfo.nImageHeight = mGetViewerImageInfo.nImageHeight;
		mCurrScrImageInfo.nImageWidth = mGetViewerImageInfo.nImageWidth;
		mCurrScrImageInfo.nImageHeight = mGetViewerImageInfo.nImageHeight;
	}

	delete bmpLoad;
	bmpLoad->Handle = NULL;
	bmpLoad = NULL;

	pnlIMGVIEW->SetFocus();
}
//---------------------------------------------------------------------------

double __fastcall TfrmMemoViewer::funcSetImageBaseScale(int _nScreenW, int _nScreenH, int _nImageW, int _nImageH)
{
	if (_nImageW == 0 || _nImageH == 0) {
		AnsiString strMsg = "이미지의 길이가 0입니다. 명령어 수행이 중지 됩니다.";
		frmMsg->funcMessageDlg("이미지 크기 확인:", strMsg, 2);
		return 0;
	}

	if (_nImageW > _nScreenW || _nImageH > _nScreenH)
	{
		double dRateW = (double)_nScreenW / (double)_nImageW;
		double dRateH = (double)_nScreenH / (double)_nImageH;

		frmMain->m_dDocFactor = ( dRateW > dRateH ) ? (dRateH) : (dRateW);
	}

	dDocZoomRate[0] = frmMain->m_dDocFactor;
	dDocZoomRate[1] = frmMain->m_dDocFactor * 1.2;
	dDocZoomRate[2] = frmMain->m_dDocFactor * 1.3;
	dDocZoomRate[3] = frmMain->m_dDocFactor * 1.5;
	dDocZoomRate[4] = frmMain->m_dDocFactor * 2;
	dDocZoomRate[5] = frmMain->m_dDocFactor * 3;
	dDocZoomRate[6] = frmMain->m_dDocFactor * 4;
	dDocZoomRate[7] = frmMain->m_dDocFactor * 5;
	dDocZoomRate[8] = frmMain->m_dDocFactor * 6;
	dDocZoomRate[9] = frmMain->m_dDocFactor * 7;
	m_nDocZoomFactor = 1;
	//funcSetZoomBarPos(true);
	//btnZoomTrackBar->Value = m_nDocZoomFactor;
	return dDocZoomRate[m_nDocZoomFactor - 1];
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoViewer::funcFullView()
{
	//화면 크기에 따라 다시 배율 조정//
	mCurrScrImageInfo.dImgBaseScale = funcSetImageBaseScale(VIEWERWIDTH, VIEWERHEIGHT, this->mGetViewerImageInfo.nImageWidth, this->mGetViewerImageInfo.nImageHeight);
	if (mCurrScrImageInfo.dImgBaseScale == 0) {
		AnsiString strMsg = "mCurrScrImageInfo.dImgBaseScale == 0";
		frmMsg->funcMessageDlg("이미지 DIB 확인:", strMsg, 2);
		return;
	}

	//현재 IMGVIEW에 보여지는 위치가 원본이미지의 Left, Top 어디인지 표시//
	nOriginL = 0;
	nOriginT = 0;

	//M//191110//m_nScreenW, m_nScreenH는 크기 고정//resize하기 전까지는 변경되지 않음//
	m_nScreenW = (int)((double)mGetViewerImageInfo.nImageWidth * (double)frmMain->m_dDocFactor);
	m_nScreenH = (int)((double)mGetViewerImageInfo.nImageHeight * (double)frmMain->m_dDocFactor);

	frmMemo->funcSetWaitWindows(true);

	//IMGVIEW->Picture->Bitmap = NULL;
	IMGVIEW->Picture = NULL;

	try
	{
		m_nImageW = (int)((double)this->mGetViewerImageInfo.nImageWidth * (double)this->mCurrScrImageInfo.dImgBaseScale);
		m_nImageH = (int)((double)this->mGetViewerImageInfo.nImageHeight * (double)this->mCurrScrImageInfo.dImgBaseScale);

		m_nImageL	= 0;
		m_nImageT	= 0;

		this->pnlIMGVIEW->Width 	= m_nImageW;
		this->pnlIMGVIEW->Height = m_nImageH;
		this->IMGVIEW->Picture->Bitmap->Width  = m_nImageW;
		this->IMGVIEW->Picture->Bitmap->Height = m_nImageH;

		this->pnlIMGVIEW->Left = (palMainView->Width  - m_nImageW)  / 2;
		this->pnlIMGVIEW->Top  = (palMainView->Height - m_nImageH) / 2;

//		//gamma 조절 - 스캔 이미지가 흐리다//사장님Req//
//		img32DocViewBck->Bitmap = NULL;
//		img32DocViewBck->Bitmap->Assign(mGetViewerImageInfo.bmpSource32);
//		m_nAdjustValue3 = 3;//항상 3으로 시작//
//		int nDiff	= m_nAdjustValue3 - 10;
//		double dTemp = (double)1 + (double)nDiff * (double)0.1;
//		this->funcGammaImage(dTemp);

		HDC hdcSrcHd			= mGetViewerImageInfo.bmpSource32->Canvas->Handle;
		HDC hdcTgtHd			= IMGVIEW->Canvas->Handle;
		HDC tmBmHd	= mGetViewerImageInfo.bmpSource32->Canvas->Handle;
		::SetStretchBltMode(hdcTgtHd, HALFTONE);
		::StretchBlt(hdcTgtHd, 0, 0, m_nImageW, m_nImageH, hdcSrcHd, 0, 0, this->mGetViewerImageInfo.nImageWidth, this->mGetViewerImageInfo.nImageHeight, SRCCOPY);
	}
	catch (Exception &exception)
	{
		frmMemo->funcSetWaitWindows(false);
		throw Exception(L"funcFullView32.");  // 상위 함수로 에러메세지을 전송합니다.
	}

	//----
	AnsiString asDestFile = frmMain->ROOTPATH + "tmp\\bmpFullView.bmp";
	if(FileExists(asDestFile))
		DeleteFile(asDestFile);
	IMGVIEW->Picture->Bitmap->SaveToFile(asDestFile);
	//----

	frmMemo->funcSetWaitWindows(false);

	mCurrScrImageInfo.dScaleRateWidth   = (double)mGetViewerImageInfo.nImageWidth / (double)m_nImageW;
	mCurrScrImageInfo.dScaleRateHeight  = (double)mGetViewerImageInfo.nImageHeight / (double)m_nImageH;
}
//---------------------------------------------------------------------------

// 배율없이 다시보기
void __fastcall TfrmMemoViewer::funcRefreshView()
{
	if(IMGVIEW->Picture->Bitmap->Width == 0)
		return;

	mCurrScrImageInfo.dImgBaseScale = dDocZoomRate[m_nDocZoomFactor-1];

	if (mCurrScrImageInfo.dImgBaseScale == 0) {
		AnsiString strMsg = "mCurrScrImageInfo.dImgBaseScale == 0";
		frmMsg->funcMessageDlg("이미지 Scale 확인:", strMsg, 2);
		return;
	}

	int nOrgL = 0;
	int nOrgT = 0;
	int nImgL = 0;
	int nImgT = 0;
	int nDstW = 0;
	int nDstH = 0;
	int nSrcW = 0;
	int nSrcH = 0;

//	frmMemo->funcSetWaitWindows(true);

	IMGVIEW->Picture->Bitmap = NULL;
	IMGVIEW->Picture = NULL;

	try
	{
		m_nImageW = (this->mGetViewerImageInfo.nImageWidth * this->mCurrScrImageInfo.dImgBaseScale);
		m_nImageH = (this->mGetViewerImageInfo.nImageHeight * this->mCurrScrImageInfo.dImgBaseScale);

		pnlIMGVIEW->Width 					= m_nImageW;
		pnlIMGVIEW->Height 					= m_nImageH;
		IMGVIEW->Picture->Bitmap->Width 		= m_nImageW;
		IMGVIEW->Picture->Bitmap->Height 	= m_nImageH;

		HDC hdcSrcHd			= mGetViewerImageInfo.bmpSource32->Canvas->Handle;
		HDC hdcTgtHd			= IMGVIEW->Canvas->Handle;
		::SetStretchBltMode(IMGVIEW->Canvas->Handle, HALFTONE);
		::StretchBlt(hdcTgtHd, 0, 0, m_nImageW, m_nImageH, hdcSrcHd, 0, 0, this->mGetViewerImageInfo.nImageWidth, this->mGetViewerImageInfo.nImageHeight, SRCCOPY);
	}
	catch (Exception &exception)
	{
		throw Exception(L"funcRefreshView.");  // 상위 함수로 에러메세지을 전송합니다.
	}

	//----
	AnsiString asDestFile = frmMain->ROOTPATH + "tmp\\bmpRefreshView.bmp";
	if(FileExists(asDestFile))
		DeleteFile(asDestFile);
	IMGVIEW->Picture->Bitmap->SaveToFile(asDestFile);
	//----

	mCurrScrImageInfo.dScaleRateWidth   = (double)mGetViewerImageInfo.nImageWidth / (double)m_nImageW;
	mCurrScrImageInfo.dScaleRateHeight  = (double)mGetViewerImageInfo.nImageHeight / (double)m_nImageH;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoViewer::funcZoomInView()
{
	if(IMGVIEW->Picture->Bitmap->Width == 0)
		return;

	double dOldZoom	= mCurrScrImageInfo.dImgBaseScale;

	mCurrScrImageInfo.dImgBaseScale = dDocZoomRate[m_nDocZoomFactor-1];

	if (mCurrScrImageInfo.dImgBaseScale == 0) {
		AnsiString strMsg = "mCurrScrImageInfo.dImgBaseScale == 0";
		frmMsg->funcMessageDlg("이미지 Scale 확인:", strMsg, 2);
		return;
	}

	frmMemo->funcSetWaitWindows(true);

	IMGVIEW->Picture->Bitmap = NULL;
	IMGVIEW->Picture = NULL;

	try
	{
		int nCenterX = m_nImageW;
		int nCenterY = m_nImageH;

		m_nImageW 	= (this->mGetViewerImageInfo.nImageWidth * this->mCurrScrImageInfo.dImgBaseScale);
		m_nImageH 	= (this->mGetViewerImageInfo.nImageHeight * this->mCurrScrImageInfo.dImgBaseScale);

		pnlIMGVIEW->Width 					= m_nImageW;//palMainView->Width;
		pnlIMGVIEW->Height 					= m_nImageH;//palMainView->Height;
		IMGVIEW->Picture->Bitmap->Width 	= m_nImageW;//palMainView->Width;
		IMGVIEW->Picture->Bitmap->Height 	= m_nImageH;//palMainView->Height;

		if( m_bWheelZoom )//Wheel//Center중심//
		{
			if(pWheelMousePos.x > 0 && pWheelMousePos.y > 0)//There is pos in image
			{
				m_nImageL = pnlIMGVIEW->Left;
				m_nImageT = pnlIMGVIEW->Top;
				double dPointX = (double)pWheelMousePos.x / (double)nCenterX;
				double dPointY = (double)pWheelMousePos.y / (double)nCenterY;
				int nGapX = (int)((double)(m_nImageW - nCenterX) * (double)dPointX);
				int nGapY = (int)((double)(m_nImageH - nCenterY) * (double)dPointY);
				m_nImageL -= nGapX;
				m_nImageT -= nGapY;
				pnlIMGVIEW->Left = m_nImageL;
				pnlIMGVIEW->Top  = m_nImageT;

				//---------------------------
				HDC hdcSrcHd			= mGetViewerImageInfo.bmpSource32->Canvas->Handle;
				HDC hdcTgtHd			= IMGVIEW->Canvas->Handle;
				SetStretchBltMode(hdcTgtHd, HALFTONE);
				StretchBlt(hdcTgtHd, 0, 0, m_nImageW, m_nImageH, hdcSrcHd, 0, 0, mGetViewerImageInfo.nImageWidth, mGetViewerImageInfo.nImageHeight, SRCCOPY);
			}
		}
		else//ToolBtn
		{
			if(m_nImageL == 0 && m_nImageT == 0)
			{
				m_nImageL = (palMainView->Width - m_nImageW) / 2;
				m_nImageT = (palMainView->Height - m_nImageH) / 2;
			}
			else
			{
				m_nImageL -= (mGetViewerImageInfo.nImageWidth * (mCurrScrImageInfo.dImgBaseScale - dOldZoom)) / 2;
				m_nImageT -= (mGetViewerImageInfo.nImageHeight * (mCurrScrImageInfo.dImgBaseScale - dOldZoom)) / 2;
			}

			pnlIMGVIEW->Left = m_nImageL;
			pnlIMGVIEW->Top  = m_nImageT;

			//---------------------------
			HDC hdcSrcHd			= mGetViewerImageInfo.bmpSource32->Canvas->Handle;
			HDC hdcTgtHd			= IMGVIEW->Canvas->Handle;
			SetStretchBltMode(hdcTgtHd, HALFTONE);
			StretchBlt(hdcTgtHd, 0, 0, m_nImageW, m_nImageH, hdcSrcHd, 0, 0, mGetViewerImageInfo.nImageWidth, mGetViewerImageInfo.nImageHeight, SRCCOPY);
		}
	}
	catch (Exception &exception)
	{
		frmMemo->funcSetWaitWindows(false);
		throw Exception(L"funcZoomInView.");  // 상위 함수로 에러메세지을 전송합니다.
	}

	//----
	AnsiString asDestFile = frmMain->ROOTPATH + "tmp\\bmpZoomIn.bmp";
	if(FileExists(asDestFile))
		DeleteFile(asDestFile);
	IMGVIEW->Picture->Bitmap->SaveToFile(asDestFile);
	//----

	pWheelMousePos.x = 0;
	pWheelMousePos.y = 0;
	m_bWheelZoom = false;

	frmMemo->funcSetWaitWindows(false);

	mCurrScrImageInfo.dScaleRateWidth   = (double)mGetViewerImageInfo.nImageWidth / (double)m_nImageW;
	mCurrScrImageInfo.dScaleRateHeight  = (double)mGetViewerImageInfo.nImageHeight / (double)m_nImageH;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoViewer::funcZoomOutView()
{
	if(IMGVIEW->Picture->Bitmap->Width == 0)
		return;

	double dOldZoom	= mCurrScrImageInfo.dImgBaseScale;

	mCurrScrImageInfo.dImgBaseScale = dDocZoomRate[m_nDocZoomFactor-1];

	if (mCurrScrImageInfo.dImgBaseScale == 0) {
		AnsiString strMsg = "mCurrScrImageInfo.dImgBaseScale == 0";
		frmMsg->funcMessageDlg("이미지 Scale 확인:", strMsg, 2);
		return;
	}

	frmMemo->funcSetWaitWindows(true);

	IMGVIEW->Picture->Bitmap = NULL;
	IMGVIEW->Picture = NULL;

	try
	{
		int nCenterX = m_nImageW;
		int nCenterY = m_nImageH;

		m_nImageW 	= (this->mGetViewerImageInfo.nImageWidth * this->mCurrScrImageInfo.dImgBaseScale);
		m_nImageH 	= (this->mGetViewerImageInfo.nImageHeight * this->mCurrScrImageInfo.dImgBaseScale);

		pnlIMGVIEW->Width 					= m_nImageW;
		pnlIMGVIEW->Height 					= m_nImageH;
		IMGVIEW->Picture->Bitmap->Width 	= m_nImageW;
		IMGVIEW->Picture->Bitmap->Height 	= m_nImageH;

		if( m_bWheelZoom )//Wheel//Center중심//
		{
			if(pWheelMousePos.x > 0 && pWheelMousePos.y > 0)//There is pos in image
			{
				m_nImageL = pnlIMGVIEW->Left;
				m_nImageT = pnlIMGVIEW->Top;
				double dPointX = (double)pWheelMousePos.x / (double)nCenterX;
				double dPointY = (double)pWheelMousePos.y / (double)nCenterY;
				int nGapX = (int)((double)(m_nImageW - nCenterX) * (double)dPointX);
				int nGapY = (int)((double)(m_nImageH - nCenterY) * (double)dPointY);
				m_nImageL -= nGapX;
				m_nImageT -= nGapY;
				pnlIMGVIEW->Left = m_nImageL;
				pnlIMGVIEW->Top  = m_nImageT;

				//---------------------------
				HDC hdcSrcHd			= mGetViewerImageInfo.bmpSource32->Canvas->Handle;
				HDC hdcTgtHd			= IMGVIEW->Canvas->Handle;
				SetStretchBltMode(hdcTgtHd, HALFTONE);
				StretchBlt(hdcTgtHd, 0, 0, m_nImageW, m_nImageH, hdcSrcHd, 0, 0, mGetViewerImageInfo.nImageWidth, mGetViewerImageInfo.nImageHeight, SRCCOPY);
			}
		}
		else//ToolBtn
		{
			if(m_nImageL == 0 && m_nImageT == 0)
			{
				m_nImageL = (palMainView->Width - m_nImageW) / 2;
				m_nImageT = (palMainView->Height - m_nImageH) / 2;
			}
			else
			{
				m_nImageL -= (mGetViewerImageInfo.nImageWidth * (mCurrScrImageInfo.dImgBaseScale - dOldZoom)) / 2;
				m_nImageT -= (mGetViewerImageInfo.nImageHeight * (mCurrScrImageInfo.dImgBaseScale - dOldZoom)) / 2;
			}

			pnlIMGVIEW->Left = m_nImageL;
			pnlIMGVIEW->Top  = m_nImageT;

			//---------------------------
			HDC hdcSrcHd			= mGetViewerImageInfo.bmpSource32->Canvas->Handle;
			HDC hdcTgtHd			= IMGVIEW->Canvas->Handle;
			SetStretchBltMode(hdcTgtHd, HALFTONE);
			StretchBlt(hdcTgtHd, 0, 0, m_nImageW, m_nImageH, hdcSrcHd, 0, 0, mGetViewerImageInfo.nImageWidth, mGetViewerImageInfo.nImageHeight, SRCCOPY);
		}
	}
	catch (Exception &exception)
	{
		frmMemo->funcSetWaitWindows(false);
		throw Exception(L"funcZoomOut");  // 상위 함수로 에러메세지을 전송합니다.
	}

	//----
	AnsiString asDestFile = frmMain->ROOTPATH + "tmp\\bmpZoomOut.bmp";
	if(FileExists(asDestFile))
		DeleteFile(asDestFile);
	IMGVIEW->Picture->Bitmap->SaveToFile(asDestFile);
	//----

	pWheelMousePos.x = 0;
	pWheelMousePos.y = 0;
	m_bWheelZoom = false;

	frmMemo->funcSetWaitWindows(false);

	mCurrScrImageInfo.dScaleRateWidth   = (double)mGetViewerImageInfo.nImageWidth / (double)m_nImageW;
	mCurrScrImageInfo.dScaleRateHeight  = (double)mGetViewerImageInfo.nImageHeight / (double)m_nImageH;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoViewer::IMGPREVMouseEnter(TObject *Sender)
{
	if(frmMemo->m_nThumbIndex > 0)
	{
		frmMain->funcFreeEachButtonImage(IMGPREV);
		IMGPREV->Picture->Bitmap->Assign(frmMain->BITMAP_BTN_BUTTONS[1][frmMain->BtnPrev]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoViewer::IMGPREVMouseLeave(TObject *Sender)
{
	frmMain->funcFreeEachButtonImage(IMGPREV);
	IMGPREV->Picture->Bitmap->Assign(frmMain->BITMAP_BTN_BUTTONS[0][frmMain->BtnPrev]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoViewer::IMGPREVClick(TObject *Sender)
{
	if(frmMemo->m_nThumbIndex > 0)
	{
		frmMemo->m_nThumbIndex--;
		lblCount->Caption = "(" + IntToStr(frmMemo->m_nThumbIndex+1) + "/" + IntToStr(frmMemo->m_nThumbCount) + ")";
		funcProcessViewImage();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoViewer::IMGNEXTMouseEnter(TObject *Sender)
{
	if(frmMemo->m_nThumbIndex < frmMemo->m_nThumbCount - 1)
	{
		frmMain->funcFreeEachButtonImage(IMGNEXT);
		IMGNEXT->Picture->Bitmap->Assign(frmMain->BITMAP_BTN_BUTTONS[1][frmMain->BtnNext]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoViewer::IMGNEXTMouseLeave(TObject *Sender)
{
	frmMain->funcFreeEachButtonImage(IMGNEXT);
	IMGNEXT->Picture->Bitmap->Assign(frmMain->BITMAP_BTN_BUTTONS[0][frmMain->BtnNext]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoViewer::IMGNEXTClick(TObject *Sender)
{
	if(frmMemo->m_nThumbIndex < frmMemo->m_nThumbCount - 1)
	{
		frmMemo->m_nThumbIndex++;
		lblCount->Caption = "(" + IntToStr(frmMemo->m_nThumbIndex+1) + "/" + IntToStr(frmMemo->m_nThumbCount) + ")";
		funcProcessViewImage();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoViewer::funcProcessViewImage()
{
	AnsiString asPathName	= "";

	if(m_bFromMemo)//메모폼에서 왔을때//
	{
		if(frmMemo->pnlThumbList != NULL)
		{
			TPanel *pnlDocDC 		= (TPanel *)frmMemo->pnlThumbList->Items[frmMemo->m_nThumbIndex];
			if(pnlDocDC != NULL)
			{
				asPathName = pnlDocDC->Hint;
				//DB등록 전 데이터인지 등록 후 데이터인지 확인하기//
				//우선 테스트로 등록전 데이터를 확인//
				if( frmMemo->m_vMEMOFILE[frmMemo->m_nThumbIndex].B_NEW )//local file
				{
					if(FileExists(asPathName))
					{
						if( IMGNOIMAGE->Visible )		IMGNOIMAGE->Visible = false;
						if( !palMainView->Visible )		palMainView->Visible = true;
						funcLoadImage(asPathName);
					}
					else
					{
						if( !IMGNOIMAGE->Visible )		IMGNOIMAGE->Visible = true;
						if( palMainView->Visible )		palMainView->Visible = false;
					}
//					if(FileExists(asPathName))
//					{
//						frmMemo->m_nThumbIndex = frmMemo->m_nThumbIndex;
//						funcLoadImage(asPathName);
//					}
//					else
//					{
//						frmMsg->funcMessageDlg("파일 부재 알림:", "해당 경로에 파일이 없습니다.", 3);
//					}
				}
				else//remote file
				{
					asPathName	= frmMemo->m_vMEMOFILE[frmMemo->m_nThumbIndex].LOCAL_PATH_NAME;//frmMemo->funcDownloadFile(frmMemo->m_nThumbIndex);
					if(FileExists(asPathName))
					{
						if( IMGNOIMAGE->Visible )		IMGNOIMAGE->Visible = false;
						if( !palMainView->Visible )		palMainView->Visible = true;
						funcLoadImage(asPathName);
					}
					else
					{
						if( !IMGNOIMAGE->Visible )		IMGNOIMAGE->Visible = true;
						if( palMainView->Visible )		palMainView->Visible = false;
					}
//					if(FileExists(asPathName))
//					{
//						//frmMemo->m_nThumbIndex = nTag;
//						funcLoadImage(asPathName);
//					}
				}
			}
		}
	}
	else//포토-뷰
	{
		asPathName	= frmMemo->m_vMEMOFILE[frmMemo->m_nThumbIndex].LOCAL_PATH_NAME;
		if(asPathName != NULL)
		{
			if(FileExists(asPathName))
			{
				if( IMGNOIMAGE->Visible )		IMGNOIMAGE->Visible = false;
				if( !palMainView->Visible )		palMainView->Visible = true;
				funcLoadImage(asPathName);
			}
			else
			{
				if( !IMGNOIMAGE->Visible )		IMGNOIMAGE->Visible = true;
				if( palMainView->Visible )		palMainView->Visible = false;
			}
		}
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoViewer::IMGVIEWMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if(IMGVIEW->Picture->Bitmap->Width == 0)
		return;

	pnlIMGVIEW->SetFocus();

	if (Button == mbLeft)
	{
		if(bLeftDownFlag == false)
		{
			tpStartPoint.x = X;
			tpStartPoint.y = Y;
			bLeftDownFlag  = true;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoViewer::IMGVIEWMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	if(IMGVIEW->Picture->Bitmap->Width == 0)
		return;

	tpMovePoint.x = X;
	tpMovePoint.y = Y;

	if(bLeftDownFlag)
	{
		m_nGapX = tpMovePoint.x - tpStartPoint.x;
		m_nGapY = tpMovePoint.y - tpStartPoint.y;

		int nLeft = pnlIMGVIEW->Left + m_nGapX;
		int nTop  = pnlIMGVIEW->Top + m_nGapY;

		int nMargin = 200;
		//left, right
		if(nLeft + m_nImageW < nMargin)
			nLeft = nMargin - m_nImageW;
		else if(nLeft > palMainView->Width)
			nLeft = palMainView->Width - nMargin;
		//top, bottom
		if(nTop + m_nImageH < nMargin)
			nTop = nMargin - m_nImageH;
		else if(nTop > palMainView->Height)
			nTop = palMainView->Height - nMargin;

		pnlIMGVIEW->Left = nLeft;
		pnlIMGVIEW->Top  = nTop;

		m_nImageL = nLeft;
		m_nImageT = nTop;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoViewer::IMGVIEWMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if(IMGVIEW->Picture->Bitmap->Width == 0)
		return;

	if(bLeftDownFlag)
	{
		tpEndPoint.x = X;
		tpEndPoint.y = Y;
		funcRefreshView();

		bLeftDownFlag = false;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMemoViewer::FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
	if (Handled == true)
		return;
	if (m_bWheelZoom == true)
		return;
	if(pnlIMGVIEW->Focused() == false)
		return;

	pWheelMousePos = tpMovePoint;//IMGVIEWMouseMove에서 확인한 pt

	if (WheelDelta >= 0 )//ZoomIn
	{
		if(m_nDocZoomFactor == 10)	return;

		if((pWheelMousePos.x <= 0 || pWheelMousePos.x > IMGVIEW->Width)
		&& (pWheelMousePos.y <= 0 || pWheelMousePos.y > IMGVIEW->Height))//mousepos in panMain
		{
			return;
		}

		m_bWheelZoom = true;

		m_nDocZoomFactor++;
		//funcSetZoomBarPos(true);
		//btnZoomTrackBar->Value = m_nDocZoomFactor;
		mCurrScrImageInfo.dImgBaseScale	= dDocZoomRate[m_nDocZoomFactor-1];

		funcZoomInView();
	}
	else//ZoomOut
	{
		if(m_nDocZoomFactor == 1)	return;

		if((pWheelMousePos.x < 0 || pWheelMousePos.x > IMGVIEW->Width)
		&& (pWheelMousePos.y < 0 || pWheelMousePos.y > IMGVIEW->Height))//mousepos in panMain
		{
			return;
		}

		m_bWheelZoom = true;

		m_nDocZoomFactor--;
		//funcSetZoomBarPos(true);
		//btnZoomTrackBar->Value = m_nDocZoomFactor;
		mCurrScrImageInfo.dImgBaseScale	= dDocZoomRate[m_nDocZoomFactor-1];

		funcZoomOutView();
	}

	Handled = true;
}
//---------------------------------------------------------------------------


