#pragma link "bsSkinCtrls"
#pragma link "bsPngImageList"
#pragma link "bsPngImageList"
#pragma link "GR32_Image"
#pragma link "GR32_RangeBars"
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"


//---------------------------------------------------------------------------
#pragma warn -8004
#pragma warn -8018


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmDoc8View *frmDoc8View;
//---------------------------------------------------------------------------
__fastcall TfrmDoc8View::TfrmDoc8View(TComponent* Owner)
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



	m_dDocFitFactor = 1;//221208//#PRINT_IMPROVE
}
//---------------------------------------------------------------------------

void __fastcall TfrmDoc8View::FormShow(TObject *Sender)
{
	funcLoadButtonImage();//230901//컴포넌트 => 이미지 버튼으로 변경//

	this->Left	= frmMain->palMainSearchBar->Left + frmMain->palMainSearchBar->Width + 8;

	//=================================================================
	//부책//
	//=================================================================
	if(frmMain->m_bSUBBOOK)
	{
		chkAreaChange->Visible	= true;
		IMGDOC08UNIT->Visible	= true;//231226//
	}
	//=================================================================
	//공유지연명부//
	//=================================================================
	else
	{
		chkAreaChange->Visible	= false;
		IMGDOC08UNIT->Visible	= false;//231226//
	}

//	funcSetWaitWindows(true);
//	Timer1->Enabled  = true;//201224//moved
	funcRefreshShow();}

//---------------------------------------------------------------------------

void __fastcall TfrmDoc8View::Timer1Timer(TObject *Sender)
{
//	Timer1->Enabled = false;
//
//	funcRefreshShow();
}
//---------------------------------------------------------------------------

void __fastcall TfrmDoc8View::funcLoadButtonImage()
{
	AnsiString filename = "";
	TPngImage *imgPng;

	try{
		for(int i = 0; i < 2; i++)
		{
			//------------------------------------------------------
			//UNIT
			imgPng = new TPngImage();
			filename = frmMain->IMAGEMAINPATH + "doc08view_unit_" + IntToStr(i+1) + ".png";
			imgPng->LoadFromFile(filename);
			BITMAP_BTN_UNIT[i] 	= new Graphics::TBitmap();
			BITMAP_BTN_UNIT[i]->Assign(imgPng);
			delete imgPng;
			imgPng = NULL;
			//------------------------------------------------------
			//PRINT1
			imgPng = new TPngImage();
			filename = frmMain->IMAGEMAINPATH + "doc08view_print1_" + IntToStr(i+1) + ".png";
			imgPng->LoadFromFile(filename);
			BITMAP_BTN_PRINT1[i] 	= new Graphics::TBitmap();
			BITMAP_BTN_PRINT1[i]->Assign(imgPng);
			delete imgPng;
			imgPng = NULL;
			//------------------------------------------------------
			//PRINT2
			imgPng = new TPngImage();
			filename = frmMain->IMAGEMAINPATH + "doc08view_print2_"  + IntToStr(i+1) + ".png";
			imgPng->LoadFromFile(filename);
			BITMAP_BTN_PRINT2[i] 	= new Graphics::TBitmap();
			BITMAP_BTN_PRINT2[i]->Assign(imgPng);
			delete imgPng;
			imgPng = NULL;
		}
	}
	catch (Exception &exception)
	{
		Application->Terminate();
		return;
	}

	//Unit : Toggle
	IMGDOC08UNIT->Tag	= 0;
	IMGDOC08UNIT->Picture->Bitmap->Assign(BITMAP_BTN_UNIT[0]);
	//Print : 클릭 시에만 포커스 이미지 표시//
	IMGDOC08PRINT1->Picture->Bitmap->Assign(BITMAP_BTN_PRINT1[0]);
	IMGDOC08PRINT2->Picture->Bitmap->Assign(BITMAP_BTN_PRINT2[0]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmDoc8View::funcDeleteButtonImage()
{
	for(int i = 0; i < 2; i++)
	{
		delete BITMAP_BTN_UNIT[i];
		BITMAP_BTN_UNIT[i] = NULL;
		delete BITMAP_BTN_PRINT1[i];
		BITMAP_BTN_PRINT1[i] = NULL;
		delete BITMAP_BTN_PRINT2[i];
		BITMAP_BTN_PRINT2[i] = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmDoc8View::funcRefreshShow()
{
	funcSetWaitWindows(true);

	//=================================================================
	//부책//
	//=================================================================
	if(frmMain->m_bSUBBOOK)
	{
		if(chkAreaChange->Checked)
			frmAlphaDoc8->m_asSavedFileName	= frmAlphaDoc8->m_asSavedFileName2;
		else
			frmAlphaDoc8->m_asSavedFileName	= frmAlphaDoc8->m_asSavedFileName1;
	}
	//=================================================================
	//공유지연명부//
	//=================================================================
	else
	{
		frmAlphaDoc8->m_asSavedFileName	= frmAlphaDoc8->m_asSavedFileName1;
	}
	funcLoadImage(frmAlphaDoc8->m_asSavedFileName);

	funcSetWaitWindows(false);

	pnlDoc08Print->Enabled	= true;//230904//UI변경//

	panMain->SetFocus();//230201//
}
//---------------------------------------------------------------------------

void __fastcall TfrmDoc8View::FormClose(TObject *Sender, TCloseAction &Action)
{
	funcDeleteButtonImage();//230901//컴포넌트 => 이미지 버튼으로 변경//

	funcImageViewClear();
	funcFreeImage();

	chkAreaChange->Checked	= false;
	chkPrintOrg->Checked	= false;

	m_bDoc8ViewClose		= true;//230328//
	frmMain->chkOwnNames->Checked	= false;//220118//
}
//---------------------------------------------------------------------------

void __fastcall TfrmDoc8View::FormResize(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

double __fastcall TfrmDoc8View::funcSetImageBaseScale()
{
	if (readImageWidth == 0 || readImageHeight == 0) {
		AnsiString strMsg = "이미지의 길이가 0입니다. 명령어 수행이 중지 됩니다.";
		ShowMessage(strMsg);
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

void __fastcall TfrmDoc8View::funcFreeImage()
{
	if (m_DIB != NULL){
		FreeImage_Unload(m_DIB);
		m_DIB = NULL;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmDoc8View::funcImageViewClear()
{
	this->IMGSCREEN1->Picture->Bitmap->Assign(NULL);
	this->panMain->Left = 0;
	this->panMain->Top  = 0;

	asPathName	= "";
	nImageWidth 	= 0;
	nImageHeight 	= 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDoc8View::funcLoadImage(AnsiString _asFilename)
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
		if(panMain->Align == alNone)
		{
			panMain->Width		= nImageWidth;
			panMain->Height		= nImageHeight;
			IMGSCREEN1->Width 	= nImageWidth;
			IMGSCREEN1->Height 	= nImageHeight;
		}
		else
		{
			IMGSCREEN1->Width 	= panMain->Width;
			IMGSCREEN1->Height 	= panMain->Height;
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

void __fastcall TfrmDoc8View::funcFullView()
{
	//################################################################
	if( !chkAreaChange->Checked )//221221//지적단위 "평"일 때 열람하던 m_dDocFactor 유지//
		m_dDocFactor	= funcSetImageBaseScale();

	if (m_dDocFactor == 0) {
		AnsiString strMsg = "m_dDocFactor is 0";
		ShowMessage(strMsg);
		return;
	}

	dScaleGap	    = 0.1;

	//===================================================
	//화면 중앙
	if( !chkAreaChange->Checked )//221221//지적단위 "평"일 때 열람하던 m_dDocFactor 유지//
	{
		m_nSrcCenterX   = (-readImageWidth/2);
		m_nSrcCenterY   = (readImageHeight/2);
		m_nSrcWidth   	= (int)((double)IMGSCREEN1->Width/m_dDocFactor);
		m_nSrcHeight  	= (int)((double)IMGSCREEN1->Height/m_dDocFactor);
		realLeft     	= (int)(m_nSrcCenterX + (double)m_nSrcWidth/2);
		realTop      	= (int)(m_nSrcCenterY - (double)m_nSrcHeight/2);
	}
	//===================================================

	func_DrawImage();
//NotUsed//	mToolButtonState = DF_PANNING;//221220//

	panMain->SetFocus();
}
//---------------------------------------------------------------------------

//201217//이미지 확대 범위가 조금 작았으면 좋겠다//
//44230Req//지적원도 1단계에서 2단계 갈때 너무 훅 커진다//
//그래서 알씨 줌 크기를 반영//10%,20%,30%,50%,70%,100%,150%,200%,300%,500%,700%,1000%,2000%,3000%,5000%
//우리는 제한이 없으니까 1000% 이후로는 500%씩 커지게 하자//
double __fastcall TfrmDoc8View::funcGetImageScale(bool _bZoomIn)
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

void __fastcall TfrmDoc8View::func_DrawImage()
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
		//------
		//221209//TEST//HBRUSH brush = ::CreateSolidBrush(RGB(255,255,255));
		HBRUSH brush = ::CreateSolidBrush(RGB(80,80,80));
		HDC pDraw1    = IMGSCREEN1->Canvas->Handle;
		//221209//TEST//IMGSCREEN1->Canvas->Brush->Color = clWhite;
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
			//221209//TEST//hbrDoc   = ::CreateSolidBrush( 0x00ffffff ); //브러쉬
			hbrDoc   = ::CreateSolidBrush( 0x00808080 ); //브러쉬
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
			//221209//TEST//hbrDoc   = ::CreateSolidBrush( 0x00ffffff ); //브러쉬
			hbrDoc   = ::CreateSolidBrush( 0x00808080 ); //브러쉬
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
			//221209//TEST//hbrDoc   = ::CreateSolidBrush( 0x00ffffff ); //브러쉬
			hbrDoc   = ::CreateSolidBrush( 0x00808080 ); //브러쉬
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
			//221209//TEST//hbrDoc   = ::CreateSolidBrush( 0x00ffffff ); //브러쉬
			hbrDoc   = ::CreateSolidBrush( 0x00808080 ); //브러쉬
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

void __fastcall TfrmDoc8View::funcSetWaitWindows(bool bSetValue)
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

TPoint __fastcall TfrmDoc8View::funcSurveyMapToDevice(const GPoint _gPoint)
{
	TPoint tPoint;

	tPoint.x = (double)(_gPoint.x + this->realLeft) * this->m_dDocFactor;
	tPoint.y = (double)(_gPoint.y - this->realTop) * this->m_dDocFactor;

	return tPoint;
}
//---------------------------------------------------------------------------

GPoint __fastcall TfrmDoc8View::funcDeviceToSurveyMap(const TPoint _scrPoint)
{
	GPoint gPoint;

	gPoint.x = (double)_scrPoint.x / this->m_dDocFactor - this->realLeft;
	gPoint.y = (double)_scrPoint.y / this->m_dDocFactor + this->realTop;

	return gPoint;
}
//---------------------------------------------------------------------------

void __fastcall TfrmDoc8View::FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
	TControl *pCtrl=FindDragTarget(MousePos,true);

	if (panMain->Focused())
	{
		if (Handled == true)
			return;
		if (m_bWheelZoom == true)
			return;

		if((pWheelMousePos.x <= 0 || pWheelMousePos.x > IMGSCREEN1->Width)
		&& (pWheelMousePos.y <= 0 || pWheelMousePos.y > IMGSCREEN1->Height))//mousepos in panMain
		{
			return;
		}

		if(WheelDelta > 0)//ZoomIn
		{
			Handled	= true;
			m_bWheelZoom	= true;

			try{
				double dPointX, dPointY;
				dPointX	= (double)pWheelMousePos.x / (double)IMGSCREEN1->Width;
				dPointY	= (double)pWheelMousePos.y / (double)IMGSCREEN1->Height;

				GPoint	_gPoint;
				_gPoint	= funcDeviceToSurveyMap(pWheelMousePos);
				m_nSrcCenterX = -_gPoint.x;
				m_nSrcCenterY = _gPoint.y;

				m_dDocFactor = funcGetImageScale(true);

				m_nSrcWidth   	= (int)((double)IMGSCREEN1->Width/m_dDocFactor);
				m_nSrcHeight  	= (int)((double)IMGSCREEN1->Height/m_dDocFactor);

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
				dPointX	= (double)pWheelMousePos.x / (double)IMGSCREEN1->Width;
				dPointY	= (double)pWheelMousePos.y / (double)IMGSCREEN1->Height;

				GPoint	_gPoint;
				_gPoint	= funcDeviceToSurveyMap(pWheelMousePos);
				m_nSrcCenterX = -_gPoint.x;
				m_nSrcCenterY = _gPoint.y;

				m_dDocFactor	= funcGetImageScale(false);
				if(m_dDocFactor <= m_dDocFitFactor)
					m_dDocFactor	= m_dDocFitFactor;

				m_nSrcWidth   	= (int)((double)IMGSCREEN1->Width/m_dDocFactor);
				m_nSrcHeight  	= (int)((double)IMGSCREEN1->Height/m_dDocFactor);

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
}
//---------------------------------------------------------------------------

void __fastcall TfrmDoc8View::IMGSCREEN1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if(IMGSCREEN1->Picture->Bitmap->Width == 0)
		return;

	if(Shift.Contains(ssLeft)){
		startPoint.x = IMGSCREEN1->Left;
		startPoint.y = IMGSCREEN1->Top;
		clickPoint.x = X;
		clickPoint.y = Y;

//NotUsed//		if(mToolButtonState == DF_PANNING)
		{//이동
			m_bFlags = true;
			GetCursorPos(&_movepoint);  //현재 마우스 좌표를 저장

			//200820
			GPoint	_gPoint;
			TPoint	_tPoint;
			_tPoint.x	= IMGSCREEN1->Width / 2;
			_tPoint.y	= IMGSCREEN1->Height / 2;
			_gPoint	= funcDeviceToSurveyMap(_tPoint);
			m_nSrcCenterX = -_gPoint.x;
			m_nSrcCenterY = _gPoint.y;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmDoc8View::IMGSCREEN1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	if(IMGSCREEN1->Picture->Bitmap->Width == 0)
		return;

	if(palWait->Visible == false){//minji@230201//조건오류로 휠 확대축소가 동작하지 않아서 변경//if(Shift.Contains(ssLeft)){
		TPoint _ptPoint;
		_ptPoint.x = X;
		_ptPoint.y = Y;
		pWheelMousePos = _ptPoint;

		GPoint	_gPoint;
		TPoint  _sPoint;

		_gPoint	= funcDeviceToSurveyMap(_ptPoint);
		_sPoint	= funcSurveyMapToDevice(_gPoint);

		//same code #1
		if(/*//NotUsed//mToolButtonState == DF_PANNING &&*/ m_bFlags){
			GetCursorPos(&_ptPoint); //마우스 움직인 후의 현재 마우스 가져옴
			int nMovedL = IMGSCREEN1->Left  + (_ptPoint.x - _movepoint.x);
			int nMovedT  = IMGSCREEN1->Top  + (_ptPoint.y - _movepoint.y);

			IMGSCREEN1->Left	= nMovedL;
			IMGSCREEN1->Top  	= nMovedT;

			_movepoint  = _ptPoint; // 현재 좌표를 이전좌표로 기억해둠

			if(IMGSCREEN1->Left < -(IMGSCREEN1->Width - panMain->Width + panMain->Width/2)) IMGSCREEN1->Left = -(IMGSCREEN1->Width - panMain->Width + panMain->Width/2);
			else if(IMGSCREEN1->Left > panMain->Width/2) IMGSCREEN1->Left = panMain->Width/2;

			if(IMGSCREEN1->Top < -(IMGSCREEN1->Height - panMain->Height + panMain->Height/2)) IMGSCREEN1->Top = -(IMGSCREEN1->Height - panMain->Height + panMain->Height/2);
			else if(IMGSCREEN1->Top > panMain->Height/2) IMGSCREEN1->Top = panMain->Height/2;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmDoc8View::IMGSCREEN1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if(IMGSCREEN1->Picture->Bitmap->Width == 0)
		return;

	if(Button == mbLeft)//왼쪽 버튼
	{
		if(/*//NotUsed//mToolButtonState == DF_PANNING &&*/ m_bFlags == true){
			endPoint.x    = IMGSCREEN1->Left;
			endPoint.y    = IMGSCREEN1->Top;

			m_bFlags  = false;

			m_nSrcCenterX = (int)(m_nSrcCenterX + IMGSCREEN1->Left / m_dDocFactor);
			m_nSrcCenterY = (int)(m_nSrcCenterY - IMGSCREEN1->Top / m_dDocFactor);

			m_nSrcWidth   = (int)((double)IMGSCREEN1->Width / m_dDocFactor);
			m_nSrcHeight  = (int)((double)IMGSCREEN1->Height / m_dDocFactor);

			realLeft      = (int)(m_nSrcCenterX + (double)m_nSrcWidth/2);
			realTop       = (int)(m_nSrcCenterY - (double)m_nSrcHeight/2);

			func_DrawImage();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmDoc8View::chkAreaChangeClick(TObject *Sender)
{
	if(IMGSCREEN1->Picture->Bitmap->Width == 0)
		return;

	if( this->Showing )
		funcRefreshShow();
}
//---------------------------------------------------------------------------

void __fastcall TfrmDoc8View::btnPrintClick(TObject *Sender)
{
	//============================================
	//221201//비정상종료됐다면 살아 있을 수도 있다.
	HWND hWnd = FindWindow(NULL, "지적문서 인쇄");
	if(hWnd)
	{
		SendMessage(hWnd,WM_CLOSE,0,0);
	}

	if (!DirectoryExists(frmMain->PRINTPATH))//221208//#PRINT_IMPROVE//
		CreateDir(frmMain->PRINTPATH);
	//Print 폴더 삭제//
	eFunc->funcDeleteDir(false, frmMain->PRINTPATH);
	//============================================

	funcWriteIniData();

	btnPrint->Visible		= false;
	chkPrintOrg->Visible	= false;
	chkAreaChange->Visible	= false;



	AnsiString  asFileNameHan   = "";
	AnsiString  asFileNameOrg   = "";

	Graphics::TBitmap *printBmp = new Graphics::TBitmap();

	if(chkPrintOrg->Checked)
	{
		//원본이미지 복사//
		if(FileExists(frmMain->m_asLoadImageFileName))
		{
			AnsiString  asFileName	= ExtractFileName(frmMain->m_asLoadImageFileName);
			AnsiString  asExt 	= ExtractFileExt(asFileName);
			if(asExt.UpperCase() != ".JPG")//원본:TIF, 변경:JPG
			{
				asExt	= ".jpg";
				asFileNameOrg	= frmMain->PRINTPATH + frmMain->m_asLandNm + "_원본" + asExt;
				asFileNameHan	= frmMain->PRINTPATH + frmMain->m_asLandNm + "_참고" + asExt;
				//원본 로드하여 jpg로 변환하기//
				//===================================================================================================
				FIBITMAP* 			i_DIB;
				FREE_IMAGE_FORMAT 	fiformat;
				int nPixelX 	= FreeImage_GetDotsPerMeterX(frmMain->mGetImageInfo.m_DIB);
				int nPixelY 	= FreeImage_GetDotsPerMeterY(frmMain->mGetImageInfo.m_DIB);
				int nPrintW		= 297 * nPixelX;
				int nPrintH		= 210 * nPixelY;

				i_DIB	= FreeImage_Rescale(frmMain->mGetImageInfo.m_DIB, nPrintW, nPrintH, FILTER_BILINEAR);

				int readBpp = FreeImage_GetBPP(frmMain->mGetImageInfo.m_DIB);
				if(readBpp < 16){
					i_DIB = FreeImage_ConvertTo24Bits(i_DIB);
				}

				FreeImage_Save(FIF_JPEG, i_DIB, asFileNameOrg.c_str());
				if ( i_DIB != NULL)
				{
					FreeImage_Unload(i_DIB);
					i_DIB = NULL;
				}
				//===================================================================================================
			}
			else
			{
				asFileNameOrg	= frmMain->PRINTPATH + frmMain->m_asLandNm + "_원본" + asExt;
				asFileNameHan	= frmMain->PRINTPATH + frmMain->m_asLandNm + "_참고" + asExt;

				if(FileExists(asFileNameOrg))
					DeleteFile(asFileNameOrg);
				CopyFile(frmMain->m_asLoadImageFileName.c_str(), asFileNameOrg.c_str(), false);
			}
		}
	}
	else//220322//원본인쇄추가 체크 안하면 오동작//
	{
		asFileNameHan	= frmMain->PRINTPATH + frmMain->m_asLandNm + "_참고.jpg";
	}


	//한글인쇄본 A3->A4 변경//
	try{
		printBmp->PixelFormat = pf32bit;
		printBmp->Width 	= 3508;
		printBmp->Height 	= 2480;
		::SetStretchBltMode(printBmp->Canvas->Handle, HALFTONE);
		::StretchDIBits(printBmp->Canvas->Handle, 0, 0, printBmp->Width, printBmp->Height, 0, 0, readImageWidth, readImageHeight, FreeImage_GetBits(m_DIB), FreeImage_GetInfo(m_DIB), DIB_RGB_COLORS, SRCCOPY);
	}
	__finally{
		TJPEGImage	*saveJpg = new TJPEGImage();
		saveJpg->CompressionQuality = 100;
		saveJpg->Compress();
		saveJpg->Assign(printBmp);
		saveJpg->SaveToFile(asFileNameHan);
		delete saveJpg;
		saveJpg = NULL;
	}

	delete printBmp;
	printBmp	= NULL;

	//인쇄 미리보기 화면//
	if(FileExists(asFileNameHan))
	{
		AnsiString asExecFile	= frmMain->ROOTPATH + "Print.exe";

		SHELLEXECUTEINFO ExVal;
		ExVal.cbSize       = sizeof(SHELLEXECUTEINFO);
		ExVal.fMask        = NULL;
		ExVal.hwnd         = NULL;
		ExVal.lpVerb       = NULL;
		ExVal.lpFile       = asExecFile.c_str();

		ExVal.lpParameters = "A4_L";
		ExVal.lpDirectory  = "";
		ExVal.nShow        = SW_SHOW;
		ExVal.hInstApp     = NULL;
		ShellExecuteEx(&ExVal);

		//220121//#TB_COPY_DOC08//구대장<한글표시> 체크 : DB 저장//
		if(frmMain->m_asCurrentId != frmMain->func_Encoder("admin"))//230210//테스트계정에 대해서 이력 저장 안함//
			frmSql->funcSQLWriteTbCopyDoc08(DF_NEW_RECORD, 2);
	}

	btnPrint->Visible		= true;
	chkPrintOrg->Visible	= true;
	chkAreaChange->Visible	= true;//221020//[REQ]부여안수환J//
}
//---------------------------------------------------------------------------

AnsiString __fastcall TfrmDoc8View::funcGetPrintSetting()
{
	TPrinter 	*pPrinter       = new TPrinter();
	wchar_t Device[256], Driver[256], Port[256];
	THandle hDMode;
	TDevMode *ADevMode;
	pPrinter->GetPrinterA(Device, Driver, Port, hDMode);
	ADevMode = (TDevMode *)GlobalLock((void *)hDMode);
	GlobalUnlock((void *)hDMode);

	//PrinterName
	//190801//프로그램 종료시까지 선택한 프린터명을 기억하기//
	return ADevMode->dmDeviceName;
}
//---------------------------------------------------------------------------

void __fastcall TfrmDoc8View::funcWriteIniData()
{
	TPrinter 	*printer 		= new TPrinter();
	TStringList *printerList    = new TStringList();
	AnsiString 	asPrinterName	= "";

	printerList = (TStringList *)printer->Printers;
	if(printerList->Count == 0)
	{
		frmMsg->funcMessageDlg("프린터기 확인 알림:", "프린터기 연결을 확인해주세요.", 3);
		return;
    }

	//220930//44770추가//220712//220712//#44250//계룡만 임시로 인쇄 설정 파일 삭제 안함//
	AnsiString asIniFile = frmMain->ROOTPATH + "DATA\\PrintSetting.ini";
	if(frmMain->_SIDOCODE != "44250" && frmMain->_SIDOCODE != "44770")
	{
		if (FileExists(asIniFile))
			DeleteFile(asIniFile);
	}

	frmMain->_iniPrintSetting = new TIniFile(asIniFile);//

	if(frmMain->m_asPrinterName.IsEmpty())
		frmMain->m_asPrinterName = funcGetPrintSetting();

	frmMain->_iniPrintSetting->WriteString(L"PRINT_SETTING", L"PRINTER", 		frmMain->m_asPrinterName);//201230//
	frmMain->_iniPrintSetting->WriteString(L"PRINT_SETTING", L"PAPER_SIZE", 	0);
	frmMain->_iniPrintSetting->WriteString(L"PRINT_SETTING", L"SCALE", 			1);
	frmMain->_iniPrintSetting->WriteString(L"PRINT_SETTING", L"POSITION", 		5);
	frmMain->_iniPrintSetting->WriteString(L"PRINT_SETTING", L"DOC8PAGE2", 		0);
	frmMain->_iniPrintSetting->WriteString(L"PRINT_SETTING", L"DOC8STAMP", 		0);
	frmMain->_iniPrintSetting->WriteString(L"PRINT_SETTING", L"DOC7P", 			0);
	frmMain->_iniPrintSetting->WriteString(L"PRINT_SETTING", L"PREVIEW", 		1);
	frmMain->_iniPrintSetting->WriteString(L"PRINT_SETTING", L"RESOLUTION", 	300);
	frmMain->_iniPrintSetting->WriteString(L"PRINT_SETTING", L"TITLE", 			"");

//v1.0.0.6//230627//
	delete frmMain->_iniPrintSetting;
	frmMain->_iniPrintSetting = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TfrmDoc8View::IMGSCREEN1MouseEnter(TObject *Sender)
{
	panMain->SetFocus();
}
//---------------------------------------------------------------------------



void __fastcall TfrmDoc8View::FormCreate(TObject *Sender)
{
	//둥근사각형 만들기
	HRGN hRegion;
	//
	hRegion  = CreateRoundRectRgn(0,0, pnlDoc08Print->Width, pnlDoc08Print->Height, 4,4);
	SetWindowRgn(pnlDoc08Print->Handle, hRegion, True);
}
//---------------------------------------------------------------------------





void __fastcall TfrmDoc8View::IMGDOC08PRINTMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	//선택방식//
	if(Sender == IMGDOC08PRINT1)//한글 번역본 인쇄//
	{
		IMGDOC08PRINT1->Picture->Bitmap->Handle	= NULL;
		IMGDOC08PRINT1->Picture                 = NULL;
		IMGDOC08PRINT1->Picture->Bitmap->Assign(BITMAP_BTN_PRINT1[1]);
		IMGDOC08PRINT2->Picture->Bitmap->Handle	= NULL;
		IMGDOC08PRINT2->Picture                 = NULL;
		IMGDOC08PRINT2->Picture->Bitmap->Assign(BITMAP_BTN_PRINT2[0]);
	}
	else if(Sender == IMGDOC08PRINT2)//번역본+원본 인쇄//
	{
		IMGDOC08PRINT1->Picture->Bitmap->Handle	= NULL;
		IMGDOC08PRINT1->Picture                 = NULL;
		IMGDOC08PRINT1->Picture->Bitmap->Assign(BITMAP_BTN_PRINT1[0]);
		IMGDOC08PRINT2->Picture->Bitmap->Handle	= NULL;
		IMGDOC08PRINT2->Picture                 = NULL;
		IMGDOC08PRINT2->Picture->Bitmap->Assign(BITMAP_BTN_PRINT2[1]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmDoc8View::IMGDOC08PRINTMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	//선택방식//
	if(Sender == IMGDOC08PRINT1)//한글 번역본 인쇄//
		chkPrintOrg->Checked	= false;
	else if(Sender == IMGDOC08PRINT2)//번역본+원본 인쇄//
		chkPrintOrg->Checked	= true;
	//
	btnPrintClick(NULL);


	//선택방식//
	if(Sender == IMGDOC08PRINT1)//한글 번역본 인쇄//
	{
		IMGDOC08PRINT1->Picture->Bitmap->Handle	= NULL;
		IMGDOC08PRINT1->Picture                 = NULL;
		IMGDOC08PRINT1->Picture->Bitmap->Assign(BITMAP_BTN_PRINT1[0]);
		IMGDOC08PRINT2->Picture->Bitmap->Handle	= NULL;
		IMGDOC08PRINT2->Picture                 = NULL;
		IMGDOC08PRINT2->Picture->Bitmap->Assign(BITMAP_BTN_PRINT2[0]);
	}
	else if(Sender == IMGDOC08PRINT2)//번역본+원본 인쇄//
	{
		IMGDOC08PRINT1->Picture->Bitmap->Handle	= NULL;
		IMGDOC08PRINT1->Picture                 = NULL;
		IMGDOC08PRINT1->Picture->Bitmap->Assign(BITMAP_BTN_PRINT1[0]);
		IMGDOC08PRINT2->Picture->Bitmap->Handle	= NULL;
		IMGDOC08PRINT2->Picture                 = NULL;
		IMGDOC08PRINT2->Picture->Bitmap->Assign(BITMAP_BTN_PRINT2[0]);
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmDoc8View::IMGDOC08UNITClick(TObject *Sender)
{
	IMGDOC08UNIT->Picture->Bitmap->Handle	= NULL;
	IMGDOC08UNIT->Picture                 	= NULL;
	//TOGGLE//
	if(IMGDOC08UNIT->Tag == 0)//원본 지적단위 -> ㎡ //
	{
		IMGDOC08UNIT->Picture->Bitmap->Assign(BITMAP_BTN_UNIT[1]);
		chkAreaChange->Checked	= true;
		IMGDOC08UNIT->Tag = 1;
	}
	else if(IMGDOC08UNIT->Tag == 1)//㎡ -> 원본 지적단위 //
	{
		IMGDOC08UNIT->Picture->Bitmap->Assign(BITMAP_BTN_UNIT[0]);
		chkAreaChange->Checked	= false;
		IMGDOC08UNIT->Tag = 0;
	}

	//포커스 상태에서 클릭 시 Hint 변경//
	IMGDOC08UNITMouseEnter(IMGDOC08UNIT);
}
//---------------------------------------------------------------------------

void __fastcall TfrmDoc8View::IMGDOC08UNITMouseEnter(TObject *Sender)
{
	if(IMGDOC08UNIT->Tag == 0)
		IMGDOC08UNIT->Hint = "지적단위를 ㎡로 환산하여 열람합니다.";
	else if(IMGDOC08UNIT->Tag == 1)
		IMGDOC08UNIT->Hint = "지적단위를 원본 그대로 표기하여 열람합니다.";
}
//---------------------------------------------------------------------------

