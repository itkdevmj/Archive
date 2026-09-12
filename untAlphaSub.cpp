#pragma link "bsPngImageList"
#pragma link "GR32_Image"
#pragma link "GR32_RangeBars"
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"

#pragma warn -8004
#pragma warn -8018
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"



#define IsCTRLpressed()  ( (GetKeyState(VK_CONTROL) & (1 << (sizeof(SHORT)*8-1))) != 0 )


TfrmAlphaSub *frmAlphaSub;
//---------------------------------------------------------------------------
__fastcall TfrmAlphaSub::TfrmAlphaSub(TComponent* Owner)
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
		//shpWait->Pen->Color//
		this->shpWait->Pen->Color		= (TColor)RGB(R, G, B);
		//panWindowsMove->Color//
		//pnlWaitT->Color//
		this->pnlWaitT->Color		= (TColor)RGB(R, G, B);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaSub::FormCreate(TObject *Sender)
{
//	dAlphaRate[11] = {0, 25, 50, 76, 102, 128, 154, 180, 204, 230, 255};
	dAlphaRate[0] = 0;
	dAlphaRate[1] = 25;
	dAlphaRate[2] = 50;
	dAlphaRate[3] = 76;
	dAlphaRate[4] = 102;
	dAlphaRate[5] = 128;
	dAlphaRate[6] = 154;
	dAlphaRate[7] = 180;
	dAlphaRate[8] = 204;
	dAlphaRate[9] = 230;
	dAlphaRate[10] = 255;

	m_nAlphaFactor = 6;
	this->AlphaBlendValue = dAlphaRate[6];//128;//191015//255;

	bFormShowed = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlphaSub::FormShow(TObject *Sender)
{
	this->funcSetWaitWindows(true);
	///////////////////////////////////

	//241220//Init//
	m_dDegree	= 0.0;

	//191015
	frmAlphaView->gbAlpha->Position = m_nAlphaFactor;//8;
	frmAlphaView->funcProcessAlpha();

	//화면 크기 설정
//	this->Left   = frmAlphaView->Left + (frmAlphaView->Width - frmAlphaView->ClientWidth) / 2;
//	this->Top    = frmAlphaView->Top + frmAlphaView->panWindowsMove->Height + frmAlphaView->pnlTool->Height + 8;
	this->Left   = frmAlphaView->Left + 4;
	this->Top    = frmAlphaView->Top + frmAlphaView->panWindowsMove->Height + frmAlphaView->pnlTool->Height + 4;
	this->Width  = frmAlphaView->pnlView->Width;
	this->Height = frmAlphaView->pnlView->Height;

	funcGetImageInfo();

	AnsiString asExt 		= ExtractFileExt(frmMain->mGetImageInfo.asPathName);
	AnsiString asCopyPath 	= frmMain->TMPPATH + "tmp1" + asExt;
	CopyFile(frmMain->mGetImageInfo.asPathName.c_str(), asCopyPath.c_str(), false);

	funcLoadImage(asCopyPath);

//	if( !FileExists(frmMain->mGetImageInfo1.asPathName) )
//		Close();

	this->funcSetWaitWindows(false);
	////////////////////////////////
	panMain->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaSub::FormClose(TObject *Sender, TCloseAction &Action)
{
	funcImageViewClear();
	funcFreeImage();

	bFormShowed = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaSub::FormResize(TObject *Sender)
{
	if(bFormShowed)
	{
//		this->Left   = frmAlphaView->Left + (frmAlphaView->Width - frmAlphaView->ClientWidth) / 2;
//		this->Top    = frmAlphaView->Top + frmAlphaView->panWindowsMove->Height + frmAlphaView->pnlTool->Height + 8;
//		this->Width  = frmAlphaView->pnlView->Width;
//		this->Height = frmAlphaView->pnlView->Height;// + 20;//24;
//
//		IMGSCREEN2->Width	= this->Width;
//		IMGSCREEN2->Height	= this->Height;
//
//		m_dDocFactor	= funcSetImageBaseScale();
//
//		func_DrawImage();
//		mToolButtonState = DF_PANNING;
//		panMain->SetFocus();

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaSub::funcGetImageInfo()
{
	//191015
	m_nAlphaFactor = 6;
	frmAlphaView->gbAlpha->Position 	= m_nAlphaFactor;//Req//8;
	frmAlphaView->gbGamma->Position		= 10;
	frmAlphaView->m_nAlphaValue  		= this->AlphaBlendValue;
	frmAlphaView->m_nGammaValue 		= frmAlphaView->gbGamma->Position;

	m_bWheelZoom = false;

	bFormShowed = true;//SHOW할때, RESIZE에서 funcLoadImage 하지 않기 위함.
}
//---------------------------------------------------------------------------

double __fastcall TfrmAlphaSub::funcSetImageBaseScale()
{
	if (readImageWidth == 0 || readImageHeight == 0) {
		AnsiString strMsg = "이미지의 길이가 0입니다. 명령어 수행이 중지 됩니다.";
		frmMsg->funcMessageDlg("이미지 크기 확인:", strMsg, 2);
		return 0;
	}

	if (readImageWidth > panMain->Width || readImageHeight > panMain->Height)
	{
		double dRateW = (double)panMain->Width / (double)readImageWidth;
		double dRateH = (double)panMain->Height / (double)readImageHeight;

		m_dDocFitFactor = ( dRateW > dRateH ) ? (dRateH) : (dRateW);
	}

	return m_dDocFitFactor;
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaSub::funcFreeImage()
{
	if (frmMain->mGetImageInfo1.m_DIB != NULL){
		FreeImage_Unload(frmMain->mGetImageInfo1.m_DIB);
		frmMain->mGetImageInfo1.m_DIB = NULL;
		memset(&frmMain->mGetImageInfo1, 0x00, sizeof(GetImageInfo));
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlphaSub::funcImageViewClear()
{
	this->IMGSCREEN2->Picture->Bitmap->Assign(NULL);
	this->panMain->Left = 0;
	this->panMain->Top  = 0;

	frmMain->mGetImageInfo1.asPathName	= "";
	frmMain->mGetImageInfo1.nImageWidth 	= 0;
	frmMain->mGetImageInfo1.nImageHeight 	= 0;
	frmMain->mGetImageInfo1.nBPP 			= 0;
	frmMain->mGetImageInfo1.nDBScale 		= 0;
	frmMain->mGetImageInfo1.nInputScale 	= 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlphaSub::funcLoadImage(AnsiString _asFilename)
{
	funcImageViewClear();
	funcFreeImage();

	if (frmMain->mGetImageInfo1.m_DIB != NULL){
		FreeImage_Unload(frmMain->mGetImageInfo1.m_DIB);
		frmMain->mGetImageInfo1.m_DIB 		= NULL;
		frmMain->mGetImageInfo1.mBitMapInfo = NULL;
		memset(&frmMain->mGetImageInfo1, 0x00, sizeof(GetImageInfo));
	}

	Application->ProcessMessages();

	frmMain->funcOpenAlphaImage1();

	if (!frmMain->mGetImageInfo1.m_DIB) {
		AnsiString strMsg = "frmMain->mGetImageInfo1.m_DIB is NULL";
		frmMsg->funcMessageDlg("이미지 DIB 확인:", strMsg, 2);
		return;
	}

	try {
		frmMain->mGetImageInfo1.nBPP 	= FreeImage_GetBPP(frmMain->mGetImageInfo1.m_DIB);
		frmMain->mGetImageInfo1.nImageWidth  	= FreeImage_GetWidth(frmMain->mGetImageInfo1.m_DIB);
		frmMain->mGetImageInfo1.nImageHeight 	= FreeImage_GetHeight(frmMain->mGetImageInfo1.m_DIB);

		frmMain->mGetImageInfo1.mBitMapInfo 	= FreeImage_GetInfo(frmMain->mGetImageInfo1.m_DIB);
		memcpy(&frmMain->mGetImageInfo1.mBitMapHeadInfo, &frmMain->mGetImageInfo1.mBitMapInfo->bmiHeader, sizeof(_mBitmapHeader));

		//################################################################
		if(FreeImage_GetFileType(frmMain->mGetImageInfo1.asPathName.c_str(), 16) == FIF_TIFF)
		{
			frmMain->mGetImageInfo1.mBitMapInfo->bmiHeader.biCompression	= BI_RGB;
		}

		//200731//new
		//################################################################
		readImageWidth      = frmMain->mGetImageInfo1.nImageWidth;
		readImageHeight     = frmMain->mGetImageInfo1.nImageHeight;
		IMGSCREEN2->Left    = 0;
		IMGSCREEN2->Top     = 0;

		//################################################################
	}
	__finally {
		if(frmMain->mGetImageInfo1.m_DIB == NULL)
		{
			AnsiString strMsg = "mGetImageInfo1.m_DIB is NULL before calling SetDIBitsToDevice";
			frmMsg->funcMessageDlg("이미지 DIB 확인:", strMsg, 2);
			return;
		}

		this->funcFullView();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaSub::funcFullView()
{
	//################################################################
	m_dDocFactor	= funcSetImageBaseScale();
	if (m_dDocFactor == 0) {
		AnsiString strMsg = "m_dDocFactor is 0";
		frmMsg->funcMessageDlg("이미지 DIB 확인:", strMsg, 2);
		return;
	}

	dScaleGap	    = 0.1;

	//===================================================
	//화면 중앙
	m_nSrcCenterX   = (-readImageWidth/2);
	m_nSrcCenterY   = (readImageHeight/2);
	m_nSrcWidth   	= (int)((double)IMGSCREEN2->Width/m_dDocFactor);
	m_nSrcHeight  	= (int)((double)IMGSCREEN2->Height/m_dDocFactor);
	realLeft     	= (int)(m_nSrcCenterX + (double)m_nSrcWidth/2);
	realTop      	= (int)(m_nSrcCenterY - (double)m_nSrcHeight/2);
	//===================================================

	func_DrawImage();

	mToolButtonState	= DF_PANNING;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlphaSub::func_DrawImage()
{
	IMGSCREEN2->Canvas->Lock();
	if(frmMain->mGetImageInfo1.m_DIB != NULL)
	{
		IMGSCREEN2->Left    = 0;
		IMGSCREEN2->Top     = 0;
//		PBCONTROL2->Left    = 0;
//		PBCONTROL2->Top     = 0;

		IMGSCREEN2->Picture->Bitmap->Width  = IMGSCREEN2->Width;
		IMGSCREEN2->Picture->Bitmap->Height	= IMGSCREEN2->Height;

		TRect rect;
		rect.Left   = IMGSCREEN2->Left;
		rect.Top    = IMGSCREEN2->Top;
		rect.Right  = IMGSCREEN2->Width;
		rect.Bottom = IMGSCREEN2->Height;

		pDCDoc   = IMGSCREEN2->Canvas->Handle; //복사본
		memDCDoc = ::CreateCompatibleDC(IMGSCREEN2->Canvas->Handle);

		if(memDCDoc){
			hMembitmapDoc = ::CreateCompatibleBitmap(IMGSCREEN2->Canvas->Handle, IMGSCREEN2->Width, IMGSCREEN2->Height);
			if(hMembitmapDoc){
				pDCDoc = memDCDoc;
				pObjDoc = ::SelectObject(memDCDoc,hMembitmapDoc);
			}
		}

		hbrDoc   = ::CreateSolidBrush( 0x00ffffff ); //브러쉬
		::FillRect( pDCDoc, &rect, hbrDoc  );
		DeleteObject( hbrDoc );

		::SetStretchBltMode(pDCDoc,HALFTONE);

		realPosX	=  -(double)realLeft;
		realPosY	= readImageHeight - m_nSrcHeight - (double)realTop;

		::StretchDIBits(pDCDoc, 0, 0, IMGSCREEN2->Width, IMGSCREEN2->Height, realPosX, realPosY, m_nSrcWidth, m_nSrcHeight, FreeImage_GetBits(frmMain->mGetImageInfo1.m_DIB), FreeImage_GetInfo(frmMain->mGetImageInfo1.m_DIB), DIB_RGB_COLORS, SRCCOPY);

		if (pDCDoc != IMGSCREEN2->Canvas->Handle){
			::BitBlt(IMGSCREEN2->Canvas->Handle, 0,0,rect.Width() ,rect.Height(), memDCDoc ,0 ,0 , SRCCOPY);
		}

		::DeleteDC(memDCDoc);
		::DeleteObject(hMembitmapDoc);
		::DeleteObject(pObjDoc);


		//==================================================================
        //이미지 밖 검정색 부분 처리//
		//==================================================================
		//------
		HBRUSH brush = ::CreateSolidBrush(RGB(255,255,255));
		HDC pDraw1    = IMGSCREEN2->Canvas->Handle;
		IMGSCREEN2->Canvas->Brush->Color = clWhite;
		pDCDoc   = IMGSCREEN2->Canvas->Handle; //복사본
		TRect _rctRect;
		//Left
		if(realPosX < 0)
		{
			_rctRect.Left   = 0;
			_rctRect.Top    = 0;
			_rctRect.Right  =  -(int)((double)realPosX * m_dDocFactor);
			_rctRect.Bottom = IMGSCREEN2->Height;
			hbrDoc   = ::CreateSolidBrush( 0x00ffffff ); //브러쉬
			::FillRect( pDCDoc, &_rctRect, hbrDoc  );
			::SelectObject(pDCDoc, hbrDoc);
		}
		//Top
		if((double)(readImageHeight - realPosY) * m_dDocFactor < IMGSCREEN2->Height)
		{
			_rctRect.Left   = 0;
			_rctRect.Top    = 0;
			_rctRect.Right  = IMGSCREEN2->Width;
			_rctRect.Bottom = IMGSCREEN2->Height - (int)((double)(readImageHeight - realPosY) * m_dDocFactor);
			hbrDoc   = ::CreateSolidBrush( 0x00ffffff ); //브러쉬
			::FillRect( pDCDoc, &_rctRect, hbrDoc  );
			::SelectObject(pDCDoc, hbrDoc);
		}
		//Right
		if((double)(readImageWidth - realPosX) * m_dDocFactor < IMGSCREEN2->Width)
		{
			_rctRect.Left   = (int)((double)(readImageWidth - realPosX) * m_dDocFactor);
			_rctRect.Top    = 0;
			_rctRect.Right  = IMGSCREEN2->Width;
			_rctRect.Bottom = IMGSCREEN2->Height;
			hbrDoc   = ::CreateSolidBrush( 0x00ffffff ); //브러쉬
			::FillRect( pDCDoc, &_rctRect, hbrDoc  );
			::SelectObject(pDCDoc, hbrDoc);
		}
		//Bottom
		if((double)(realPosY + m_nSrcHeight) * m_dDocFactor < IMGSCREEN2->Height)
		{
			_rctRect.Left   = 0;
			_rctRect.Top    = (int)((double)(realPosY + m_nSrcHeight) * m_dDocFactor);
			_rctRect.Right  = IMGSCREEN2->Width;
			_rctRect.Bottom = IMGSCREEN2->Height;
			hbrDoc   = ::CreateSolidBrush( 0x00ffffff ); //브러쉬
			::FillRect( pDCDoc, &_rctRect, hbrDoc  );
			::SelectObject(pDCDoc, hbrDoc);
		}
		DeleteObject( hbrDoc );
		//------
		//==================================================================

		IMGSCREEN2->Invalidate();
	}
	IMGSCREEN2->Canvas->Unlock();

	if(m_bWheelZoom)
		m_bWheelZoom	= false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaSub::funcRefreshView()
{
	//===================================================
	//화면 중앙
	m_nSrcCenterX   = (-readImageWidth/2);
	m_nSrcCenterY   = (readImageHeight/2);
	m_nSrcWidth   	= (int)((double)IMGSCREEN2->Width/m_dDocFactor);
	m_nSrcHeight  	= (int)((double)IMGSCREEN2->Height/m_dDocFactor);
	realLeft     	= (int)(m_nSrcCenterX + (double)m_nSrcWidth/2);
	realTop      	= (int)(m_nSrcCenterY - (double)m_nSrcHeight/2);
	//===================================================

	func_DrawImage();
}
//---------------------------------------------------------------------------


int __fastcall TfrmAlphaSub::funcGammaImage(double _dValue)
{
	int nReturnValue = 0;

	nReturnValue = FreeImage_AdjustGamma(frmMain->mGetImageInfo1.m_DIB, _dValue);
	func_DrawImage();

	return nReturnValue;
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaSub::FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
	if (panMain->Focused() == false)
		return;

	if (Handled == true)
		return;
	if (m_bWheelZoom == true)
		return;

	if((pWheelMousePos.x <= 0 || pWheelMousePos.x > IMGSCREEN2->Width)
	&& (pWheelMousePos.y <= 0 || pWheelMousePos.y > IMGSCREEN2->Height))//mousepos in panMain
	{
		return;
	}

	if(WheelDelta > 0)//ZoomIn
	{
		Handled	= true;
		m_bWheelZoom	= true;

		try{
			double dPointX, dPointY;
			dPointX	= (double)pWheelMousePos.x / (double)IMGSCREEN2->Width;
			dPointY	= (double)pWheelMousePos.y / (double)IMGSCREEN2->Height;

			GPoint	_gPoint;
			_gPoint	= funcDeviceToSurveyMap(pWheelMousePos);
			m_nSrcCenterX = -_gPoint.x;
			m_nSrcCenterY = _gPoint.y;

			//201217//44230Req//m_dDocFactor = m_dDocFactor + dScaleGap;
			m_dDocFactor = funcGetImageScale(true);//201217//44230Req//

			m_nSrcWidth   	= (int)((double)IMGSCREEN2->Width/m_dDocFactor);
			m_nSrcHeight  	= (int)((double)IMGSCREEN2->Height/m_dDocFactor);

			realLeft		= (int)(m_nSrcCenterX + (double)m_nSrcWidth * dPointX);
			realTop      	= (int)(m_nSrcCenterY - (double)m_nSrcHeight * dPointY);

			func_DrawImage();
		}
		__finally{
			m_bWheelZoom	= false;
		}
		Application->ProcessMessages();
	}
	else if(WheelDelta < 0)//ZoomOut
	{
		if(m_dDocFactor == m_dDocFitFactor)
			return;

		Handled	= true;
		m_bWheelZoom	= true;

		try{
			double dPointX, dPointY;
			dPointX	= (double)pWheelMousePos.x / (double)IMGSCREEN2->Width;
			dPointY	= (double)pWheelMousePos.y / (double)IMGSCREEN2->Height;

			GPoint	_gPoint;
			_gPoint	= funcDeviceToSurveyMap(pWheelMousePos);
			m_nSrcCenterX = -_gPoint.x;
			m_nSrcCenterY = _gPoint.y;

			//201217//44230Req//m_dDocFitFactor
			m_dDocFactor	= funcGetImageScale(false);
			if(m_dDocFactor <= m_dDocFitFactor)
				m_dDocFactor	= m_dDocFitFactor;
			//201217//44230Req//m_dDocFitFactor
//			if(m_dDocFactor - dScaleGap <= dScaleGap){ m_dDocFactor = m_dDocFitFactor; }
//			else m_dDocFactor = m_dDocFactor - dScaleGap;

			m_nSrcWidth   	= (int)((double)IMGSCREEN2->Width/m_dDocFactor);
			m_nSrcHeight  	= (int)((double)IMGSCREEN2->Height/m_dDocFactor);

			realLeft     	= (int)(m_nSrcCenterX + (double)m_nSrcWidth * dPointX);
			realTop      	= (int)(m_nSrcCenterY - (double)m_nSrcHeight * dPointY);

			func_DrawImage();
		}
		__finally{
			m_bWheelZoom	= false;
		}
		Application->ProcessMessages();
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmAlphaSub::IMGSCREEN2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	panMain->SetFocus();

	if (Button == mbLeft)
	{
		startPoint.x = IMGSCREEN2->Left;
		startPoint.y = IMGSCREEN2->Top;
		clickPoint.x = X;
		clickPoint.y = Y;

		if (mToolButtonState == DF_PANNING)
		{
			m_bFlags = true;
			GetCursorPos(&_movepoint);  //현재 마우스 좌표를 저장

			//200820
			GPoint	_gPoint;
			TPoint	_tPoint;
			_tPoint.x	= IMGSCREEN2->Width / 2;
			_tPoint.y	= IMGSCREEN2->Height / 2;
			_gPoint	= funcDeviceToSurveyMap(_tPoint);
			m_nSrcCenterX = -_gPoint.x;
			m_nSrcCenterY = _gPoint.y;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaSub::IMGSCREEN2MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	if(IMGSCREEN2->Picture->Bitmap->Width == 0)
		return;

	TPoint _ptPoint;
	_ptPoint.x = X;
	_ptPoint.y = Y;
	pWheelMousePos = _ptPoint;

	if (mToolButtonState == DF_PANNING && m_bFlags)
	{
		GetCursorPos(&_ptPoint); //마우스 움직인 후의 현재 마우스 가져옴
/*
//		int nMovedL = IMGSCREEN2->Left  + (_ptPoint.x - _movepoint.x);
//		int nMovedT = IMGSCREEN2->Top  + (_ptPoint.y - _movepoint.y);
		int nMovedL = (_ptPoint.x - _movepoint.x);
		int nMovedT = (_ptPoint.y - _movepoint.y);

//		int nMargin = 200;
//		if((double)realPosX * m_dDocFactor + nMovedL > IMGSCREEN2->Width - nMargin)
//		{
//			nMovedL	= nMargin - realPosX * m_dDocFactor;
//		}
//		if((double)(readImageHeight - realPosY) * m_dDocFactor < nMargin)
//		{
//			nMovedT	= nMargin - (readImageHeight - realPosY) * m_dDocFactor;
//		}
//		if((double)(readImageWidth - realPosX) * m_dDocFactor + nMovedL  < nMargin)
//		{
//			nMovedL	= nMargin - (readImageWidth - realPosX) * m_dDocFactor;
//		}
//		if((double)(realPosY + m_nSrcHeight) * m_dDocFactor + nMovedT > IMGSCREEN2->Height - nMargin)
//		{
//			nMovedT	= nMargin - (realPosY + m_nSrcHeight) * m_dDocFactor;
//		}

		IMGSCREEN2->Left = IMGSCREEN2->Left  + nMovedL;
		IMGSCREEN2->Top  = IMGSCREEN2->Top  + nMovedT;
//		IMGSCREEN2->Left = IMGSCREEN2->Left  + (_ptPoint.x - _movepoint.x);
//		IMGSCREEN2->Top  = IMGSCREEN2->Top  + (_ptPoint.y - _movepoint.y);

		_movepoint  = _ptPoint; // 현재 좌표를 이전좌표로 기억해둠

		if(IMGSCREEN2->Left < -(IMGSCREEN2->Width - panMain->Width + panMain->Width/2))
			IMGSCREEN2->Left = -(IMGSCREEN2->Width - panMain->Width + panMain->Width/2);
		else if(IMGSCREEN2->Left > panMain->Width/2)
			IMGSCREEN2->Left = panMain->Width/2;

		if(IMGSCREEN2->Top < -(IMGSCREEN2->Height - panMain->Height + panMain->Height/2))
			IMGSCREEN2->Top = -(IMGSCREEN2->Height - panMain->Height + panMain->Height/2);
		else if(IMGSCREEN2->Top > panMain->Height/2)
			IMGSCREEN2->Top = panMain->Height/2;
*/
		TGraphicControl *GCtrl=(TGraphicControl *)IMGSCREEN2;

		GetCursorPos(&_ptPoint); //마우스 움직인 후의 현재 마우스 가져옴
		int nMovedL = (_ptPoint.x - _movepoint.x);
		int nMovedT = (_ptPoint.y - _movepoint.y);

		GCtrl->Left = GCtrl->Left  + nMovedL;
		GCtrl->Top  = GCtrl->Top  + nMovedT;

		_movepoint  = _ptPoint; // 현재 좌표를 이전좌표로 기억해둠

		if(GCtrl->Left < -(GCtrl->Width - panMain->Width + panMain->Width/2))
			GCtrl->Left = -(GCtrl->Width - panMain->Width + panMain->Width/2);
		else if(GCtrl->Left > panMain->Width/2)
			GCtrl->Left = panMain->Width/2;

		if(GCtrl->Top < -(GCtrl->Height - panMain->Height + panMain->Height/2))
			GCtrl->Top = -(GCtrl->Height - panMain->Height + panMain->Height/2);
		else if(GCtrl->Top > panMain->Height/2)
			GCtrl->Top = panMain->Height/2;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaSub::IMGSCREEN2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if (Button == mbLeft)
	{
		if (mToolButtonState == DF_PANNING && m_bFlags)
		{
			endPoint.x    = IMGSCREEN2->Left;
			endPoint.y    = IMGSCREEN2->Top;

			m_bFlags  = false;

			m_nSrcCenterX = (int)(m_nSrcCenterX + IMGSCREEN2->Left / m_dDocFactor);
			m_nSrcCenterY = (int)(m_nSrcCenterY - IMGSCREEN2->Top / m_dDocFactor);

			m_nSrcWidth   = (int)((double)IMGSCREEN2->Width / m_dDocFactor);
			m_nSrcHeight  = (int)((double)IMGSCREEN2->Height / m_dDocFactor);

			realLeft      = (int)(m_nSrcCenterX + (double)m_nSrcWidth/2);
			realTop       = (int)(m_nSrcCenterY - (double)m_nSrcHeight/2);

			func_DrawImage();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaSub::funcZoomInView()
{
	if(frmMain->mGetImageInfo1.m_DIB != NULL){//확대
		//201217//44230Req//m_dDocFactor = m_dDocFactor + dScaleGap;
		m_dDocFactor = funcGetImageScale(true);//201217//44230Req//

		m_nSrcWidth  = (int)((double)IMGSCREEN2->Width / m_dDocFactor);
		m_nSrcHeight = (int)((double)IMGSCREEN2->Height / m_dDocFactor);

		realLeft     = (int)(m_nSrcCenterX + (double)m_nSrcWidth/2);
		realTop      = (int)(m_nSrcCenterY - (double)m_nSrcHeight/2);

		func_DrawImage();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaSub::funcZoomOutView()
{
	if(frmMain->mGetImageInfo1.m_DIB != NULL){//축소
		if( m_dDocFactor == m_dDocFitFactor)	return;

		//201217//44230Req//m_dDocFitFactor
		m_dDocFactor	= funcGetImageScale(false);
		if(m_dDocFactor <= m_dDocFitFactor)
			m_dDocFactor	= m_dDocFitFactor;
		//201217//44230Req//m_dDocFitFactor
//		if(m_dDocFactor - dScaleGap <= m_dDocFitFactor){ m_dDocFactor = m_dDocFitFactor; }
//		else m_dDocFactor = m_dDocFactor - dScaleGap;

		m_nSrcWidth  = (int)((double)IMGSCREEN2->Width / m_dDocFactor);
		m_nSrcHeight = (int)((double)IMGSCREEN2->Height / m_dDocFactor);

		realLeft     = (int)(m_nSrcCenterX + (double)m_nSrcWidth/2);
		realTop      = (int)(m_nSrcCenterY - (double)m_nSrcHeight/2);

		func_DrawImage();
	}
}
//---------------------------------------------------------------------------

TPoint __fastcall TfrmAlphaSub::funcSurveyMapToDevice(const GPoint _gPoint)
{
	TPoint tPoint;

	tPoint.x = (double)(_gPoint.x + realLeft) * m_dDocFactor;
	tPoint.y = (double)(_gPoint.y - realTop) * m_dDocFactor;

	return tPoint;
}
//---------------------------------------------------------------------------

GPoint __fastcall TfrmAlphaSub::funcDeviceToSurveyMap(const TPoint _scrPoint)
{
	GPoint gPoint;

	gPoint.x = (double)_scrPoint.x / m_dDocFactor - realLeft;
	gPoint.y = (double)_scrPoint.y / m_dDocFactor + realTop;

	return gPoint;
}
//---------------------------------------------------------------------------
//백남수
void __fastcall TfrmAlphaSub::funcSetWaitWindows(bool bSetValue)
{
	palWait->Left = (panMain->Width/2) - (palWait->Width/2);
	palWait->Top  = (panMain->Height/2) - (palWait->Height/2);

	if (this->palWait->Visible == !bSetValue)
	{
		palWait->Visible = bSetValue;

		if (bSetValue) Screen->Cursor = crHourGlass;
		else Screen->Cursor     = crDefault;

		if(!bSetValue) lblWait2->Caption  = "선택 작업을 적용중입니다.";
	}

	Application->ProcessMessages();
}
//---------------------------------------------------------------------------

//201217//이미지 확대 범위가 조금 작았으면 좋겠다//
//44230Req//지적원도 1단계에서 2단계 갈때 너무 훅 커진다//
//그래서 알씨 줌 크기를 반영//10%,20%,30%,50%,70%,100%,150%,200%,300%,500%,700%,1000%,2000%,3000%,5000%
//우리는 제한이 없으니까 1000% 이후로는 500%씩 커지게 하자//
double __fastcall TfrmAlphaSub::funcGetImageScale(bool _bZoomIn)
{
	m_dDocFactor	= RoundTo(m_dDocFactor, -2);

	if(_bZoomIn)//ZoomIn
	{
		m_dDocFactor	+= 0.01;
//		if(m_dDocFactor < 0.1)//10%
//			m_dDocFactor	= 0.1;
//		else if(m_dDocFactor < 0.2)//20%
//			m_dDocFactor	= 0.2;
//		else if(m_dDocFactor < 0.3)//30%
//			m_dDocFactor	= 0.3;
//		else if(m_dDocFactor < 0.5)//50%
//			m_dDocFactor	= 0.5;
//		else if(m_dDocFactor < 0.7)//70%
//			m_dDocFactor	= 0.7;
//		else if(m_dDocFactor < 1.0)//100%
//			m_dDocFactor	= 1.0;
//		else if(m_dDocFactor < 1.5)//150%
//			m_dDocFactor	= 1.5;
//		else if(m_dDocFactor < 2.0)//200%
//			m_dDocFactor	= 2.0;
//		else if(m_dDocFactor < 3.0)//300%
//			m_dDocFactor	= 3.0;
//		else if(m_dDocFactor < 5.0)//500%
//			m_dDocFactor	= 5.0;
//		else if(m_dDocFactor < 7.0)//700%
//			m_dDocFactor	= 7.0;
//		else if(m_dDocFactor < 10.0)//1000%
//			m_dDocFactor	= 10.0;
//		else if(m_dDocFactor >= 10.0)//1000% 이상//
//			m_dDocFactor	+= 5;
	}
	else//ZoomOut
	{
		m_dDocFactor	-= 0.01;
//		if(m_dDocFactor - 5 >= 10.0)//1000% 이상//
//			m_dDocFactor	-= 5;
//		else if(m_dDocFactor > 10.0)//1000%
//			m_dDocFactor	= 10.0;
//		else if(m_dDocFactor > 7.0)//700%
//			m_dDocFactor	= 7.0;
//		else if(m_dDocFactor > 5.0)//500%
//			m_dDocFactor	= 5.0;
//		else if(m_dDocFactor > 3.0)//300%
//			m_dDocFactor	= 3.0;
//		else if(m_dDocFactor > 2.0)//200%
//			m_dDocFactor	= 2.0;
//		else if(m_dDocFactor > 1.5)//150%
//			m_dDocFactor	= 1.5;
//		else if(m_dDocFactor > 1.0)//100%
//			m_dDocFactor	= 1.0;
//		else if(m_dDocFactor > 0.7)//70%
//			m_dDocFactor	= 0.7;
//		else if(m_dDocFactor > 0.5)//50%
//			m_dDocFactor	= 0.5;
//		else if(m_dDocFactor > 0.3)//30%
//			m_dDocFactor	= 0.3;
//		else if(m_dDocFactor > 0.2)//20%
//			m_dDocFactor	= 0.2;
//		else if(m_dDocFactor > 0.1)//10%
//			m_dDocFactor	= 0.1;

		if(m_dDocFactor < m_dDocFitFactor)
			m_dDocFactor	= m_dDocFitFactor;
	}

	return m_dDocFactor;
}
//---------------------------------------------------------------------------

//원본 다시 호출//
void __fastcall TfrmAlphaSub::funcRotateView0()
{
	frmAlphaView->edtAngle->Text = "";//기 입력 각도가 있다면 초기화//

	this->funcSetWaitWindows(true);
	///////////////////////////////////

	//241220//Init//
	m_dDegree	= 0.0;

	funcGetImageInfo();

	AnsiString asExt 		= ExtractFileExt(frmMain->mGetImageInfo.asPathName);
	AnsiString asCopyPath 	= frmMain->TMPPATH + "tmp1" + asExt;
	CopyFile(frmMain->mGetImageInfo.asPathName.c_str(), asCopyPath.c_str(), false);

	funcLoadImage(asCopyPath);

	this->funcSetWaitWindows(false);
	////////////////////////////////
	panMain->SetFocus();
}
//---------------------------------------------------------------------------


//_nType(0) : 원본각도//
//_nType(1) : 왼쪽으로 1도씩//
//_nType(-1) : 오른쪽으로 1도씩//
void __fastcall TfrmAlphaSub::funcRotateView(int _nType)
{
	double dAngle = 0.0;

	if(_nType == 0 )//원본각도//
		dAngle	= (double)m_dDegree * (double)(-1);
	else
		dAngle	= (double)_nType;

	m_dDegree	+= (double)dAngle;

	double x_org  	= FreeImage_GetWidth(frmMain->mGetImageInfo1.m_DIB) / (double)2;
	double y_org 	= FreeImage_GetHeight(frmMain->mGetImageInfo1.m_DIB) / (double)2;

	///////////////////////////////////
	this->funcSetWaitWindows(true);
	///////////////////////////////////

//	FIBITMAP *rotatedDIB = FreeImage_RotateEx(frmMain->mGetImageInfo1.m_DIB, dAngle, 0, 0, x_org, y_org, false);
	FIBITMAP *rotatedDIB = FreeImage_Rotate(frmMain->mGetImageInfo1.m_DIB, dAngle);//일반적으로 검정색 배경//

	//===================================================
	//250911//
	FreeImage_Unload(frmMain->mGetImageInfo1.m_DIB);
	frmMain->mGetImageInfo1.m_DIB = NULL;
	frmMain->mGetImageInfo1.m_DIB = rotatedDIB;

//	//===================================================
//	// 회전된 이미지가 RGBA라면
//	readImageWidth  = FreeImage_GetWidth(frmMain->mGetImageInfo1.m_DIB);
//	readImageHeight = FreeImage_GetHeight(frmMain->mGetImageInfo1.m_DIB);
//	FIBITMAP* bgWhite = FreeImage_Allocate(readImageWidth, readImageHeight, 32); // 흰색 배경
//	RGBQUAD white;
//	white.rgbRed = 255;
//	white.rgbGreen = 255;
//	white.rgbBlue = 255;
//	white.rgbReserved = 0;
//	// 흰색으로 초기화
//	FreeImage_FillBackground(bgWhite, &white, 0);
//	// 알파 블렌딩 처리(픽셀 단위로 직접 작성 필요)
//	funcBlendWithAlpha(rotatedDIB, bgWhite, frmMain->mGetImageInfo1.m_DIB);


	//===================================================
	//회전으로 각도가 틀어졌으므로 이미지 크기에 변동이 발생//
	readImageWidth  = FreeImage_GetWidth(frmMain->mGetImageInfo1.m_DIB);
	readImageHeight = FreeImage_GetHeight(frmMain->mGetImageInfo1.m_DIB);


	//===================================================
	//이미지 크기가 변경되었으므로 배율 다시 확인//
	m_dDocFactor	= funcSetImageBaseScale();
	if (m_dDocFactor == 0) {
		AnsiString strMsg = "m_dDocFactor is 0";
		frmMsg->funcMessageDlg("이미지 DIB 확인:", strMsg, 2);
		return;
	}

	//===================================================
	//화면 중앙
	m_nSrcWidth   	= (int)((double)IMGSCREEN2->Width/m_dDocFactor);
	m_nSrcHeight  	= (int)((double)IMGSCREEN2->Height/m_dDocFactor);
	realLeft     	= (int)(m_nSrcCenterX + (double)m_nSrcWidth/2);
	realTop      	= (int)(m_nSrcCenterY - (double)m_nSrcHeight/2);
	//===================================================

	func_DrawImage();


	///////////////////////////////////
	this->funcSetWaitWindows(false);
	///////////////////////////////////
}
//---------------------------------------------------------------------------


/*
사용 순서
흰색 배경 이미지를 미리 생성
회전된 원본 이미지(알파 채널 있음)와 흰색 배경 이미지, 그리고 출력용 새 이미지를 준비
blendWithAlpha 함수 호출해 두 이미지를 합성하고 output 얻음
output 이미지 저장 또는 출력
*/
void __fastcall TfrmAlphaSub::funcBlendWithAlpha(FIBITMAP* fg, FIBITMAP* bg, FIBITMAP* out)
{
    int width = FreeImage_GetWidth(fg);
    int height = FreeImage_GetHeight(fg);

    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            RGBQUAD fgColor, bgColor, outColor;
            FreeImage_GetPixelColor(fg, x, y, &fgColor);
            FreeImage_GetPixelColor(bg, x, y, &bgColor);

            float alpha = fgColor.rgbReserved / 255.0f;  // 알파값 0~1로 변환

            // 알파 블렌딩 공식
            outColor.rgbRed   = (BYTE)(fgColor.rgbRed * alpha + bgColor.rgbRed * (1 - alpha));
            outColor.rgbGreen = (BYTE)(fgColor.rgbGreen * alpha + bgColor.rgbGreen * (1 - alpha));
            outColor.rgbBlue  = (BYTE)(fgColor.rgbBlue * alpha + bgColor.rgbBlue * (1 - alpha));
            outColor.rgbReserved = 255;  // 불투명으로 설정

            FreeImage_SetPixelColor(out, x, y, &outColor);
        }
    }
}
//---------------------------------------------------------------------------

