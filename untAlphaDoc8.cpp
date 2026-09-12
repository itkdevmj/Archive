/*###############################################################################

- 설명 : 구대장 한글화 번역본을 위해 A3 이미지 파일(평,㎡ 각각)을 생성하기 위한 파일//
		 화면에 표시되는 폼은 아님에 주의
- Modified : 2022.12.21
- History
[221221] Init.

###############################################################################*/



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

TfrmAlphaDoc8 *frmAlphaDoc8;
//---------------------------------------------------------------------------
__fastcall TfrmAlphaDoc8::TfrmAlphaDoc8(TComponent* Owner)
	: TForm(Owner)
{
	m_dDocFitFactor = 1;//221208//#PRINT_IMPROVE
	m_bPaintCompleted	= false;//231103//
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaDoc8::FormCreate(TObject *Sender)
{
	eData = new classDOC08Data();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaDoc8::FormDestroy(TObject *Sender)
{
	delete eData;
	eData = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaDoc8::FormShow(TObject *Sender)
{
	m_bPaintCompleted	= false;//260528//
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaDoc8::funcRefreshShow()
{
	//======================================
	//221208//#PRINT_IMPROVE//
	//1. LoadImage Background
	//2. Draw Text in IMGSCREEN2
	//3. SaveJpg(4960*3908) - A (평)
	//4. SaveJpg(4960*3908) - B (㎡)
	//5. LoadImage A
	//=================================

	//============================================
	//확대축소를 위한 이미지 보관 폴더 삭제//
	AnsiString  asTempDir	= frmMain->ROOTPATH + "tmp2\\";
	if (!DirectoryExists(asTempDir))
		CreateDir(asTempDir);
	eFunc->funcDeleteDir(false, asTempDir);
	//============================================

//=============================================================================
//231118//#SHAREOWN//
//=============================================================================
	//=================================================================
	//부책//
	//=================================================================
	if(frmMain->m_bSUBBOOK)
	{
		if(m_nDOCKIND == 0)//231117//
			m_asBGFilePath	= frmMain->ROOTPATH + "FORMAT\\토지대장A.jpg";
		else
			m_asBGFilePath	= frmMain->ROOTPATH + "FORMAT\\임야대장A.jpg";

		if( !FileExists(m_asBGFilePath) )
		{
			frmMain->chkOwnNames->Enabled = false;
			Application->MessageBoxA(L"지정서식이 존재하지않아 기본서식으로 표시합니다.", L"알림:", 0);
			m_asBGFilePath	= frmMain->ROOTPATH + "FORMAT\\토지대장A.jpg";
		}
		else
		{
			frmMain->chkOwnNames->Enabled = true;
		}

		try{
			funcMakeViewImageA3();
		}
		__finally{
			funcImageViewClear();
			funcFreeImage();
		}
	}
	//=================================================================
	//공유지연명부//
	//=================================================================
	else
	{
		m_asBGFilePath	= frmMain->ROOTPATH + "FORMAT\\공유지연명부" + frmMain->m_asFormatType + ".jpg";

		if( !FileExists(m_asBGFilePath) || (frmMain->m_asFormatType != "A" && frmMain->m_asFormatType != "B") )
		{
			frmMain->chkOwnNames->Enabled = false;
			return;
		}
		else
		{
			frmMain->chkOwnNames->Enabled = true;
		}

		try{
			funcMakeViewImageA3Share();
		}
		__finally{
			funcImageViewClear();
			funcFreeImage();
			m_bPaintCompleted	= false;
		}
	}
//ORG//
//	//======================================
//	if(m_nDOCKIND == 0)//211205//
//		m_asBGFilePath	= frmMain->ROOTPATH + "FORMAT\\토지대장A.jpg";
//	else
//		m_asBGFilePath	= frmMain->ROOTPATH + "FORMAT\\임야대장A.jpg";
//
//	if( !FileExists(m_asBGFilePath) )
//	{
//		Application->MessageBoxA(L"지정서식이 존재하지않아 기본서식으로 표시합니다.", L"알림:", 0);
//		m_asBGFilePath	= frmMain->ROOTPATH + "FORMAT\\토지대장A.jpg";
//	}
//
//	//=================================
//	//221208//#PRINT_IMPROVE//
//	try{
//		funcMakeViewImageA3();
//	//======================================
//	}
//	__finally{
//		funcImageViewClear();
//		funcFreeImage();
//	}
	//=================================================================
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaDoc8::FormClose(TObject *Sender, TCloseAction &Action)
{
	//241018//frmResultList, frmResultList2 에서 처리하면 FormClose시 소멸되므로, 설정하는 Form에서 초기화 하는 것이 맞다.//
	frmMain->m_asLandCd	= "";
	frmMain->m_asLandNm	= "";

	funcImageViewClear();
	funcFreeImage();
}
//---------------------------------------------------------------------------

double __fastcall TfrmAlphaDoc8::funcSetImageBaseScale()
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

void __fastcall TfrmAlphaDoc8::funcFreeImage()
{
	if (m_DIB != NULL){
		FreeImage_Unload(m_DIB);
		m_DIB = NULL;
		mBitMapInfo = NULL;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlphaDoc8::funcImageViewClear()
{
	this->IMGSCREEN2->Picture->Bitmap->Assign(NULL);
	this->panMain->Left = 0;
	this->panMain->Top  = 0;

	nImageWidth 	= 0;
	nImageHeight 	= 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlphaDoc8::funcLoadImage(AnsiString _asFilename)
{
	funcImageViewClear();
	funcFreeImage();

	Application->ProcessMessages();

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
			IMGSCREEN2->Width 	= nImageWidth;
			IMGSCREEN2->Height 	= nImageHeight;
		}
		else
		{
			IMGSCREEN2->Width 	= panMain->Width;
			IMGSCREEN2->Height 	= panMain->Height;
		}
		//==============================

		mBitMapInfo 	= FreeImage_GetInfo(m_DIB);

		//################################################################
		if(FreeImage_GetFileType(_asFilename.c_str(), 16) == FIF_TIFF)
		{
			mBitMapInfo->bmiHeader.biCompression	= BI_RGB;
		}

		//200731//new
		//################################################################
		readImageWidth      = nImageWidth;
		readImageHeight     = nImageHeight;
		IMGSCREEN2->Left    = 0;
		IMGSCREEN2->Top     = 0;
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

void __fastcall TfrmAlphaDoc8::funcFullView()
{
	//################################################################
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
	m_nSrcWidth   	= (int)((double)IMGSCREEN2->Width/m_dDocFactor);
	m_nSrcHeight  	= (int)((double)IMGSCREEN2->Height/m_dDocFactor);
	realLeft     	= (int)(m_nSrcCenterX + (double)m_nSrcWidth/2);
	realTop      	= (int)(m_nSrcCenterY - (double)m_nSrcHeight/2);
	//===================================================

	func_DrawImage();
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlphaDoc8::func_DrawImage()
{
	IMGSCREEN2->Canvas->Lock();
	if(m_DIB != NULL)
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

		::StretchDIBits(pDCDoc, 0, 0, IMGSCREEN2->Width, IMGSCREEN2->Height, realPosX, realPosY, m_nSrcWidth, m_nSrcHeight, FreeImage_GetBits(m_DIB), FreeImage_GetInfo(m_DIB), DIB_RGB_COLORS, SRCCOPY);

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
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaDoc8::funcRedrawOwnInfo()
{
	int fontwidth		= m_nFontSize;
	int fontheight 		= fontwidth;
	int nMiddleWidth	= m_nMiddleWidth;
	SHARP_POSITION_STRUCT	tempData;
	TPoint	tPoint;
	TScale  tScale;

	//if(pbRect2->Visible)
	if(!m_bPaintCompleted)//230925//1번째가 정상인지 2번째가 정상인지 확인 후 처리할 것//
	{
    	//##########################################################################################
		// 공통 사용 변수(PaintBox)
    	//##########################################################################################
		HDC 	hdc 			= IMGSCREEN2->Canvas->Handle;
		HPEN 	pen, penSharp;
		HFONT   m_font, hOldFont;
		HFONT 	m_fontL, hOldFontL;//지번폰트//
		TColor	cPenColorC		= (TColor)RGB(255, 0, 0);//Caution
		TColor	cPenColor		= panMain->Font->Color;
		TColor	cPenColorSharp	= (TColor)RGB(255, 0, 0);//부분삭제선//

    	//##########################################################################################
    	// 공통 사용 변수(String, Position)
    	//##########################################################################################
		AnsiString 	asData		= "";//한 셀 포함 문자//
		AnsiString 	asCaption 	= "";//TextOut에 표기할 문자//
		AnsiString 	asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
		int 		nTxtLen 	= 0;
		bool		bPartSharp		= false;
		bool		bAllSharp		= false;//#1016//전체삭제-취소선//
		bool		bEven			= true;//241203//취소선 % 개수 체크(open-close) 확인용//
		int 		nTextW			= 0;
		int 		nTextH			= 0;
		int			nStartW			= 0;
		int			nStartH			= 0;
		int			nSumH			= 0;
		int			nPartSharp1		= 0;
		int			nPartSharp2		= 0;
		int			nAllSharp1		= 0;
		int			nAllSharp2		= 0;
		int			nAllSharpLeft	= 0;
		//==============================================================

		//부분삭제선//여기에서만 초기화한다//
		m_vSharpPos.clear();

		//==============================================================
		//일반폰트//
		m_font	= ::CreateFont(fontwidth, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
		hOldFont  = (HFONT)::SelectObject(hdc, m_font);
		//==============================================================

		//##########################################################################################
		//#
		//# CAUTION
		//#
    	//##########################################################################################
        {
			//==============================================================
			pen   = ::CreatePen(PS_SOLID, 1, cPenColorC);
			::SelectObject(hdc, pen);
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
			::SetBkMode(hdc, TRANSPARENT);
			::SetTextColor(hdc, cPenColorC);
			IMGSCREEN2->Canvas->Brush->Color	= clWhite;
			//==============================================================

			//==========================================================================================
			tPoint	= m_bsAlphaDoc8[12].tPoint;
			nTextW	= IMGSCREEN2->Canvas->TextWidth(eData->m_vCAUTION[0].DATA)+1;//Caution.Text.Width는 독립적//
			nTextH	= IMGSCREEN2->Canvas->TextHeight(eData->m_vCAUTION[0].DATA)+1;//Caution.Text.Width는 독립적//
			//==========================================================================================

    		//======================================================
    		// 좌측하단 문구표시//
    		IMGSCREEN2->Canvas->TextOutA(tPoint.x, tPoint.y, eData->m_vCAUTION[0].DATA);
			//======================================================

			::SetROP2 (hdc, oldro);
			::DeleteObject( pen );
		}

		//##########################################################################################
    	//#
		//# LAND, JIBUN, LEVEL, MEMO
    	//#
    	//##########################################################################################
		//==============================================================
		//지번폰트//
		m_fontL	= ::CreateFont(fontwidth+2, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
		hOldFontL  = (HFONT)::SelectObject(hdc, m_fontL);
		//==============================================================
		{

			//==============================================================
			pen   = ::CreatePen(PS_SOLID, 1, cPenColor);
			::SelectObject(hdc, pen);
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
			::SetBkMode(hdc, TRANSPARENT);
			::SetTextColor(hdc, cPenColor);
			IMGSCREEN2->Canvas->Brush->Color	= clWhite;
			//==============================================================

			//==============================================================
			asData			= "";//한 셀 포함 문자//
			asCaption 		= "";//TextOut에 표기할 문자//
			asTemp 			= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen 		= 0;
			nTextW			= 0;
			nTextH			= 0;
			nStartW			= 0;
			nStartH			= 0;
			nSumH			= 0;
			nPartSharp1		= 0;
			nPartSharp2		= 0;
			nAllSharp1		= 0;
			nAllSharp2		= 0;
			nAllSharpLeft	= 0;
			//==============================================================



			//*****************************************************************
			//
			// 동리 //LAND//읍면동명, 리명 구분하여 두 줄 처리//
			//
			//*****************************************************************
			bAllSharp	= false;
			bPartSharp	= false;

			//==========================================================================================
			tPoint	= m_bsAlphaDoc8[0].tPoint;
			tScale	= m_bsAlphaDoc8[0].tScale;
			nTextW	= IMGSCREEN2->Canvas->TextWidth("동")+1;//임의글자로 체크//
			nTextH	= IMGSCREEN2->Canvas->TextHeight("동")+1;//임의글자로 체크//
    		//=========================================================

			if(eData->m_asLand.Length() > 0)
			{
				eData->m_asLand	= StringReplace(eData->m_asLand, " ", "_", TReplaceFlags() << rfReplaceAll);
                asData = eData->m_asLand;
				//---
                nTxtLen = asData.Length();
                nSumH	= 0;

                //=================================================
                //211206//읍면동명, 리명 구분하여 두 줄 처리//
				TStringList *slData 		= new TStringList;
                slData	= new TStringList();
                int nPos	= asData.Pos("_");
                while(nPos > 0)
                {
                    asTemp 	= asData.SubString(1, nPos-1);
                    slData->Add(asTemp);
                    asData  = asData.Delete(1, nPos);
                    nPos	= asData.Pos("_");
                }
                slData->Add(asData);

    			//==========================================================================================
				//실제표시//
				nStartW	= tPoint.x + tScale.w - ((tScale.w - slData->Count*nTextW) / 2);
    			//==========================================================================================

                for(int z = 0; z < slData->Count; z++)
				{
					asData	= slData->Strings[z];
	//				asData	= StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
    //				asData	= StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
    //				asData	= StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);

                    nTxtLen = asData.Length();
                    nSumH	= 0;
                    //라인별 높이 체크//
					for(int j = 0; j < nTxtLen; j++)
                    {
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
                            asTemp = asData.SubString(j+1, 2);
                            nSumH	+= IMGSCREEN2->Canvas->TextHeight(asTemp);
                            j++;
                        }
                        else
                        {
                            if(asData.c_str()[j] == '%')//부분삭제//
                                continue;
                            if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
                            {
                                if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
                                {
                                    asCaption = asData.SubString(j+1, 2);
                                    nSumH	+= IMGSCREEN2->Canvas->TextHeight(asCaption);
                                    j++;
                                    continue;
                                }
                            }
                            asCaption = asData.SubString(j+1, 1);
                            nSumH	+= IMGSCREEN2->Canvas->TextHeight(asCaption);
                        }
                    }

					//=========================================================
					nStartW	-= nTextW;
                    nStartH	= tPoint.y + (tScale.h - nSumH) / 2;
                    //=========================================================

                    //=========================================================
					for(int j = 0; j < nTxtLen; j++)
                    {
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asCaption = asData.SubString(j+1, 2);
                            IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
                            j++;
                        }
                        else
                        {
                            if(!bPartSharp && asData.c_str()[j] =='%')
    	                    {
                                bPartSharp	= true;
                                nPartSharp1	= nStartH;
                                continue;
                            }
                            else if(bPartSharp && asData.c_str()[j] =='%')
    	                    {
                                nPartSharp2	= nStartH-1;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                                tempData.tpSTT.x	= nStartW + nTextW/2;
                                tempData.tpSTT.y	= nPartSharp1;
                                tempData.tpEND.x	= nStartW + nTextW/2;
                                tempData.tpEND.y	= nPartSharp2;
								m_vSharpPos.push_back(tempData);
								bPartSharp	= false;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                continue;
							}

                            if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
                            {
                                if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
    	                        {
                                    asCaption = asData.SubString(j+1, 2);
									IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
                                    j++;
                                    nStartH	+= nTextH;
                                    continue;
                                }
                            }
                            //숫자 1자리//
                            asCaption = asData.SubString(j+1, 1);
                            IMGSCREEN2->Canvas->TextOutA(nStartW+m_nNumberL, nStartH, asCaption);
                        }

                        nStartH	+= nTextH;
                    }
                }

                delete slData;
                slData    = NULL;
			}


			//*****************************************************************
			//
			// 지번 //
			//
			//*****************************************************************
			bAllSharp	= false;
			bPartSharp	= false;

			//==========================================================================================
			tPoint  = m_bsAlphaDoc8[1].tPoint;
			tScale  = m_bsAlphaDoc8[1].tScale;
			nTextW	= IMGSCREEN2->Canvas->TextWidth("번")+1;//임의글자로 체크//
			nTextH  = IMGSCREEN2->Canvas->TextHeight("번");//임의글자로 체크//
            //==========================================================================================

			if(eData->m_asJibun.Length() > 0)
            {
                asData     = eData->m_asJibun;
                if(frmMain->m_nBonbuType == 1)
                    asData    = StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
                else if(frmMain->m_nBonbuType == 2)
                    asData    = StringReplace(asData, "-", ".", TReplaceFlags() << rfReplaceAll);
                else if(frmMain->m_nBonbuType == 3)
                    asData    = StringReplace(asData, "-", "/", TReplaceFlags() << rfReplaceAll);
                else if(frmMain->m_nBonbuType == 4)
                    asData    = StringReplace(asData, "-", " - ", TReplaceFlags() << rfReplaceAll);
                else if(frmMain->m_nBonbuType == 5)
                    asData    = StringReplace(asData, "-", " | ", TReplaceFlags() << rfReplaceAll);
                else if(frmMain->m_nBonbuType == 6)
                    asData    = StringReplace(asData, "-", "의", TReplaceFlags() << rfReplaceAll);
                //---
                nTxtLen = asData.Length();
                nSumH    = 0;

				for(int j = 0; j < nTxtLen; j++)
                {
                    if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                    {
                        asTemp = asData.SubString(j+1, 2);
                        nSumH    += IMGSCREEN2->Canvas->TextHeight(asTemp);
						j++;
                    }
					else
                    {
                        asCaption = asData.SubString(j+1, 1);
                        nSumH    += IMGSCREEN2->Canvas->TextHeight(asCaption);
					}
                }

				//=========================================================
				//실제표시//
				nStartW    = tPoint.x + (tScale.w - nTextW) / 2;
                nStartH    = tPoint.y + (tScale.h - nSumH) / 2;
                //=========================================================

				for(int j = 0; j < nTxtLen; j++)
                {
                    if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                    {
                        asCaption = asData.SubString(j+1, 2);
                        IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
                        j++;
                    }
                    else
					{
                        asCaption = asData.SubString(j+1, 1);
                        IMGSCREEN2->Canvas->TextOutA(nStartW+m_nNumberL, nStartH, asCaption);
                    }
                    nStartH    += nTextH+1;
                }
            }

            ::SetROP2 (hdc, oldro);
			::DeleteObject( pen );



			//==============================================================
			//일반폰트//
			m_font	= ::CreateFont(fontwidth, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
			hOldFont  = (HFONT)::SelectObject(hdc, m_font);
			//==============================================================

			//===================================
			//241203//#등급#추가//
			//===================================
			//*****************************************************************
			//
			// 등급 //
			//
			//*****************************************************************
			bAllSharp	= false;
			bPartSharp	= false;
			bEven		= true;//close상태//

			//==========================================================================================
			tPoint  = m_bsAlphaDoc8[13].tPoint;
			tScale  = m_bsAlphaDoc8[13].tScale;
			nTextW	= IMGSCREEN2->Canvas->TextWidth("등")+1;//임의글자로 체크//
			nTextH  = IMGSCREEN2->Canvas->TextHeight("등")+1;//임의글자로 체크//
			//=========================================================

			if(eData->m_asLevel.Length() > 0)
			{
				asData = eData->m_asLevel;
				//---
                nTxtLen = asData.Length();
				nSumH    = 0;

                TStringList *slData         = new TStringList;
                slData    = new TStringList();
    //220826//적요 : 사용자 줄바꿈(_)에서 자동개행으로 변경
    //            int nPos    = asData.Pos("_");
    //            while(nPos > 0)
    //            {
    //                asTemp     = asData.SubString(1, nPos-1);
    //                slData->Add(asTemp);
	//                asData  = asData.Delete(1, nPos);
    //                nPos    = asData.Pos("_");
    //            }
    //            if( !asData.IsEmpty() )
    //                slData->Add(asData);

				//=========================================================
				//실제표시//
				nStartW    = tPoint.x + (tScale.w - nTextW) / 2;
				nStartH    = tPoint.y + (tScale.h - nSumH) / 2;
				//=========================================================

				//개행없는 데이터 처리//
				int nLineTxtLen    = 0;//Cell 높이와 nTextH로 한줄 글자 수 계산//
				int nLineTxtCnt    = 0;//한글과 숫자 Length()가 다르게 나오기 때문에 정확한 개행 길이만큼 계산이 안되서 사용//
				if(slData->Count == 0 && nTextW > 0)
				{
					nLineTxtLen    = tScale.h/nTextW;
					asTemp    = "";

					for(int j = 0; j < nTxtLen; j++)
                    {
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asTemp = asTemp    + asData.SubString(j+1, 2);
                            if(nLineTxtCnt >= nLineTxtLen-1)
                            {
                                slData->Add(asTemp);
                                asTemp    = "";
                                nLineTxtCnt    = 0;

                                //+++++++++++++++++++++++++++++++++++++++++++++++++++
                                if(asData.c_str()[j+2] == '_')
                                    j++;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++
                            }
                            else
                            {
								nLineTxtCnt++;//231215//ReturnCode//세로쓰기는한글2글자로체킹할필요없다.//231117//++ -> += 2
                            }
                            j++;
						}
                        else
                        {
                            //========================================================
                            if(asData.c_str()[j] == '_')
                            {
                                if( !asTemp.IsEmpty() )//211208//31025.2.20.2//주소개행과 길이자동개행이 복합//
								{
                                    slData->Add(asTemp);
                                    asTemp    = "";
                                    nLineTxtCnt    = 0;

                                    //+++++++++++++++++++++++++++++++++++++++++++++++++++
									//220427//소유자명 8글자이면 자동개행인데 '_'를 붙여서 한줄을 더 띄우는 문제 발생//
                                    if(asData.c_str()[j+1] == '_')
                                        j++;
                                    //+++++++++++++++++++++++++++++++++++++++++++++++++++
                                }
                            }
                            else
                            {
                                //========================================================
                                //211201//#8//이름 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
								if(asData.c_str()[j] == '%')
								{
									bEven	= !bEven;//241203//
									nLineTxtLen    = nLineTxtLen + 1;
                                }
								//========================================================
                                asTemp = asTemp + asData.SubString(j+1, 1);
								if(nLineTxtCnt >= nLineTxtLen-1)//open//241203//
                                {
                                    //========================================================
									//211201//#8//이름 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
									if( !bEven )//241203//
									{
										if(asData.c_str()[j+1] == '%')
										{
											bEven	= !bEven;//close//241203//
											nLineTxtLen    = nLineTxtLen + 1;
											asTemp = asTemp + asData.SubString(j+2, 1);
											j++;
										}
									}
                                    //========================================================
									slData->Add(asTemp);
                                    asTemp    = "";
                                    nLineTxtCnt    = 0;

                                    //+++++++++++++++++++++++++++++++++++++++++++++++++++
                                    //220427//소유자명 8글자이면 자동개행인데 '_'를 붙여서 한줄을 더 띄우는 문제 발생//
                                    if(asData.c_str()[j+1] == '_')
                                        j++;
                                    //+++++++++++++++++++++++++++++++++++++++++++++++++++
                                }
                                else
                                {
									nLineTxtCnt++;
                                }
                            }
                        }
                    }
                    if( !asTemp.IsEmpty() )
                    {
                        slData->Add(asTemp);
                        asTemp    = "";
					}
                }
                //=========================================================

				//=========================================================
				//Width 시작위치 계산//220826//적요 : 사용자 줄바꿈(_)에서 자동개행으로 변경//
				nStartW    = tPoint.x + tScale.w - ((tScale.w - slData->Count*nTextW)/2);//세로쓰기-중간//
				//=========================================================

				for(int z = 0; z < slData->Count; z++)
                {
                    asData    = slData->Strings[z];
                    asData    = StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
                    asData    = StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
                    asData    = StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);
                    asData    = StringReplace(asData, ".", ",", TReplaceFlags() << rfReplaceAll);//211207//

                    nTxtLen = asData.Length();
                    nSumH    = 0;
                    //라인별 높이 체크//
					for(int j = 0; j < nTxtLen; j++)
                    {
                        if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asTemp = asData.SubString(j+1, 2);
                            nSumH    += IMGSCREEN2->Canvas->TextHeight(asTemp);
                            j++;
                        }
                        else
                        {
                            if(asData.c_str()[j] == '%')//부분삭제//
                                continue;
                            if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
                            {
								if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
                                {
									asCaption = asData.SubString(j+1, 2);
                                    nSumH    += IMGSCREEN2->Canvas->TextHeight(asCaption);
                                    j++;
                                    continue;
                                }
							}
							asCaption = asData.SubString(j+1, 1);
							nSumH    += IMGSCREEN2->Canvas->TextHeight(asCaption);
						}
					}

					//=========================================================
					//실제표시//
					nStartW    -= nTextW;
					nStartH    = tPoint.y + (tScale.h - nSumH) / 2;
					//=========================================================

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(시작)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp1    = nStartH;
					}
					//=========================================================

					for(int j = 0; j < nTxtLen; j++)
					{
                        if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asCaption = asData.SubString(j+1, 2);
                            IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
                            j++;
                        }
                        else
						{
							if(!bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(시작)//
							{
                                bPartSharp    = true;
                                nPartSharp1    = nStartH;
								continue;
                            }
							else if(bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(종료)//
							{
                                nPartSharp2    = nStartH-1;
                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                                tempData.tpSTT.x    = nStartW + nTextW/2;
								tempData.tpSTT.y    = nPartSharp1;
                                tempData.tpEND.x    = nStartW + nTextW/2;
                                tempData.tpEND.y    = nPartSharp2;
								m_vSharpPos.push_back(tempData);
                                bPartSharp    = false;
                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                continue;
                            }

                            if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
                            {
                                if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
                                {
                                    asCaption = asData.SubString(j+1, 2);
                                    IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
                                    j++;
                                    nStartH    += nTextH;
                                    continue;
                                }
                            }
                            //숫자 1자리//
                            asCaption = asData.SubString(j+1, 1);
							IMGSCREEN2->Canvas->TextOutA(nStartW+m_nNumberL, nStartH, asCaption);
                        }

                        nStartH    += nTextH;
					}

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(종료)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x    = nStartW + nTextW/2;
						tempData.tpSTT.y    = nPartSharp1;
						tempData.tpEND.x    = nStartW + nTextW/2;
						tempData.tpEND.y    = nPartSharp2;
						m_vSharpPos.push_back(tempData);
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
					//=========================================================

				}
				delete slData;
                slData    = NULL;
            }



			//*****************************************************************
			//
			// 적요 //
			//
			//*****************************************************************
			bAllSharp	= false;
			bPartSharp	= false;
			bEven		= true;//close상태//

			//==========================================================================================
			tPoint  = m_bsAlphaDoc8[2].tPoint;
			tScale  = m_bsAlphaDoc8[2].tScale;
			nTextW	= IMGSCREEN2->Canvas->TextWidth("메")+1;//임의글자로 체크//
			nTextH  = IMGSCREEN2->Canvas->TextHeight("메")+1;//임의글자로 체크//
			//=========================================================

			if(eData->m_asMemo.Length() > 0)
			{
                asData = eData->m_asMemo;
				//---
                nTxtLen = asData.Length();
                nSumH    = 0;

                TStringList *slData         = new TStringList;
                slData    = new TStringList();
    //220826//적요 : 사용자 줄바꿈(_)에서 자동개행으로 변경
    //            int nPos    = asData.Pos("_");
    //            while(nPos > 0)
    //            {
    //                asTemp     = asData.SubString(1, nPos-1);
    //                slData->Add(asTemp);
	//                asData  = asData.Delete(1, nPos);
    //                nPos    = asData.Pos("_");
    //            }
    //            if( !asData.IsEmpty() )
    //                slData->Add(asData);

				//=========================================================
				//실제표시//
				nStartW    = tPoint.x + (tScale.w - nTextW) / 2;
				nStartH    = tPoint.y + (tScale.h - nSumH) / 2;
				//=========================================================

				//개행없는 데이터 처리//
				int nLineTxtLen    = 0;//Cell 높이와 nTextH로 한줄 글자 수 계산//
				int nLineTxtCnt    = 0;//한글과 숫자 Length()가 다르게 나오기 때문에 정확한 개행 길이만큼 계산이 안되서 사용//
				if(slData->Count == 0 && nTextW > 0)
				{
                    nLineTxtLen    = tScale.h/nTextW;
					asTemp    = "";

                    for(int j = 0; j < nTxtLen; j++)
                    {
                        if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asTemp = asTemp    + asData.SubString(j+1, 2);
                            if(nLineTxtCnt >= nLineTxtLen-1)
                            {
                                slData->Add(asTemp);
                                asTemp    = "";
                                nLineTxtCnt    = 0;

                                //+++++++++++++++++++++++++++++++++++++++++++++++++++
                                if(asData.c_str()[j+2] == '_')
                                    j++;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++
                            }
                            else
                            {
								nLineTxtCnt++;//231215//ReturnCode//세로쓰기는한글2글자로체킹할필요없다.//231117//++ -> += 2
                            }
                            j++;
						}
                        else
                        {
                            //========================================================
                            if(asData.c_str()[j] == '_')
                            {
                                if( !asTemp.IsEmpty() )//211208//31025.2.20.2//주소개행과 길이자동개행이 복합//
								{
                                    slData->Add(asTemp);
                                    asTemp    = "";
                                    nLineTxtCnt    = 0;

                                    //+++++++++++++++++++++++++++++++++++++++++++++++++++
									//220427//소유자명 8글자이면 자동개행인데 '_'를 붙여서 한줄을 더 띄우는 문제 발생//
                                    if(asData.c_str()[j+1] == '_')
                                        j++;
                                    //+++++++++++++++++++++++++++++++++++++++++++++++++++
                                }
                            }
                            else
                            {
                                //========================================================
                                //211201//#8//이름 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
                                if(asData.c_str()[j] == '%')
                                {
									bEven	= !bEven;//241203//
									nLineTxtLen    = nLineTxtLen + 1;
                                }
								//========================================================
                                asTemp = asTemp + asData.SubString(j+1, 1);
                                if(nLineTxtCnt >= nLineTxtLen-1)
                                {
                                    //========================================================
                                    //211201//#8//이름 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
									if( !bEven )//241203//
									{
										if(asData.c_str()[j+1] == '%')
										{
											bEven	= !bEven;//241203//
											nLineTxtLen    = nLineTxtLen + 1;
											asTemp = asTemp + asData.SubString(j+2, 1);
											j++;
										}
									}
									//========================================================
                                    slData->Add(asTemp);
                                    asTemp    = "";
                                    nLineTxtCnt    = 0;

                                    //+++++++++++++++++++++++++++++++++++++++++++++++++++
                                    //220427//소유자명 8글자이면 자동개행인데 '_'를 붙여서 한줄을 더 띄우는 문제 발생//
                                    if(asData.c_str()[j+1] == '_')
                                        j++;
                                    //+++++++++++++++++++++++++++++++++++++++++++++++++++
                                }
                                else
                                {
									nLineTxtCnt++;
                                }
                            }
                        }
                    }
                    if( !asTemp.IsEmpty() )
                    {
                        slData->Add(asTemp);
                        asTemp    = "";
					}
                }
                //=========================================================

				//=========================================================
				//Width 시작위치 계산//220826//적요 : 사용자 줄바꿈(_)에서 자동개행으로 변경//
				nStartW    = tPoint.x + tScale.w - ((tScale.w - slData->Count*nTextW)/2);//세로쓰기-중간//
				//=========================================================

				for(int z = 0; z < slData->Count; z++)
                {
                    asData    = slData->Strings[z];
                    asData    = StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
                    asData    = StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
                    asData    = StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);
                    asData    = StringReplace(asData, ".", ",", TReplaceFlags() << rfReplaceAll);//211207//

                    nTxtLen = asData.Length();
                    nSumH    = 0;
                    //라인별 높이 체크//
					for(int j = 0; j < nTxtLen; j++)
                    {
                        if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asTemp = asData.SubString(j+1, 2);
                            nSumH    += IMGSCREEN2->Canvas->TextHeight(asTemp);
                            j++;
                        }
                        else
                        {
							if(asData.c_str()[j] == '%')//부분삭제//
                                continue;
                            if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
                            {
								if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
                                {
									asCaption = asData.SubString(j+1, 2);
                                    nSumH    += IMGSCREEN2->Canvas->TextHeight(asCaption);
                                    j++;
                                    continue;
                                }
							}
							asCaption = asData.SubString(j+1, 1);
							nSumH    += IMGSCREEN2->Canvas->TextHeight(asCaption);
						}
					}

					//=========================================================
					//실제표시//
					nStartW    -= nTextW;
					nStartH    = tPoint.y + (tScale.h - nSumH) / 2;
					//=========================================================

					//=========================================================
					//241203//취소선 처리 중 개행(시작시점)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp1    = nStartH;
					}
					//=========================================================

					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asCaption = asData.SubString(j+1, 2);
                            IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
                            j++;
                        }
                        else
                        {
							if(!bPartSharp && asData.c_str()[j] =='%')//세로쓰기 부분삭제(시작지점)//
							{
								bPartSharp    = true;
								nPartSharp1    = nStartH;
								continue;
							}
							else if(bPartSharp && asData.c_str()[j] =='%')
							{
								nPartSharp2    = nStartH-1;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
								tempData.tpSTT.x    = nStartW + nTextW/2;
								tempData.tpSTT.y    = nPartSharp1;
								tempData.tpEND.x    = nStartW + nTextW/2;
								tempData.tpEND.y    = nPartSharp2;
								m_vSharpPos.push_back(tempData);
								bPartSharp    = false;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
								continue;
							}

                            if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
                            {
                                if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
                                {
                                    asCaption = asData.SubString(j+1, 2);
                                    IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
                                    j++;
                                    nStartH    += nTextH;
                                    continue;
                                }
                            }
                            //숫자 1자리//
                            asCaption = asData.SubString(j+1, 1);
							IMGSCREEN2->Canvas->TextOutA(nStartW+m_nNumberL, nStartH, asCaption);
                        }

                        nStartH    += nTextH;
					}

					//=========================================================
					//241203//취소선 처리 중 개행(종료시점)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x    = nStartW + nTextW/2;
						tempData.tpSTT.y    = nPartSharp1;
						tempData.tpEND.x    = nStartW + nTextW/2;
						tempData.tpEND.y    = nPartSharp2;
						m_vSharpPos.push_back(tempData);
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
					//=========================================================
				}
				delete slData;
				slData    = NULL;
			}

            ::SetROP2 (hdc, oldro);
            ::DeleteObject( pen );
		}



		//==============================================================
		//일반폰트//
		m_font	= ::CreateFont(fontwidth, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
		hOldFont  = (HFONT)::SelectObject(hdc, m_font);
		//==============================================================

		//##########################################################################################
		//#
		//# JIMOK
		//#
		//##########################################################################################
		{
			//==============================================================
			//일반폰트//
			pen   = ::CreatePen(PS_SOLID, 1, cPenColor);
			::SelectObject(hdc, pen);
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
			::SetBkMode(hdc, TRANSPARENT);
			::SetTextColor(hdc, cPenColor);
			IMGSCREEN2->Canvas->Brush->Color    = clWhite;
			//==============================================================

			//==============================================================
			asData			= "";//한 셀 포함 문자//
			asCaption   	= "";//TextOut에 표기할 문자//
			asTemp         	= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen     	= 0;
			nTextW        	= 0;
			nTextH        	= 0;
			nStartW        	= 0;
			nStartH        	= 0;

			nSumH        	= 0;
			nPartSharp1    	= 0;
			nPartSharp2    	= 0;
			nAllSharp1      = 0;
			nAllSharp2      = 0;
			nAllSharpLeft	= 0;
			//위에서 한번 초기화//m_vSharpPos.clear();
			//==============================================================

			bAllSharp	= false;
			bPartSharp  = false;

			//==========================================================================================
			tPoint  = m_bsAlphaDoc8[3].tPoint;
			tScale  = m_bsAlphaDoc8[3].tScale;
			nTextW	= IMGSCREEN2->Canvas->TextWidth("지")+1;//임의글자로 체크//
			nTextH  = IMGSCREEN2->Canvas->TextHeight("지")+1;//임의글자로 체크//
			//==========================================================================================

			for( int i = 0; i < (int)eData->m_vJIMOK.size(); i++)
            {
				asData = eData->m_vJIMOK[i].DATA;

                if(asData == "-")//NoData
                    continue;

				asData = eFunc->funcStringReplaceDoc08(asData);//260518//
				//=====================================================
                if(asData.SubString(1, 1) == "#")//전체삭제//
                {
					bAllSharp    = true;
                    asData    = asData.Delete(1, 1);
                }
                else
                {
                    bAllSharp    = false;
                }
                //=====================================================


                //=========================================
                TStringList *slData         = new TStringList;
                slData    = new TStringList();
                int nPos    = asData.Pos("_");
                while(nPos > 0)
                {
                    asTemp     = asData.SubString(1, nPos-1);
                    slData->Add(asTemp);
                    asData         = asData.Delete(1, nPos);
                    nPos        = asData.Pos("_");
                }
                if( !asData.IsEmpty() )
                    slData->Add(asData);

                //==========================================================================================
				//실제표시//
                nStartH    = tPoint.y + (tScale.h - slData->Count * nTextH) / 2;
                //==========================================================================================


                for(int z = 0; z < slData->Count; z++)
				{
					asData		= slData->Strings[z];

					asTemp		= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);//부분삭제처리전 '%'없는 TextWidth 위한 임시처리//
					int nTxtW   = IMGSCREEN2->Canvas->TextWidth(asTemp);//231117//nTextW -> nTxtW//
					nStartW    	= tPoint.x - i*tScale.w + (tScale.w - nTxtW) / 2;//가로쓰기-중간//231117//nTextW -> nTxtW//
                    if(i >= 6)
                        nStartW    -= nMiddleWidth;

                    nTxtLen = asData.Length();
                    for(int j = 0; j < nTxtLen; j++)
                    {
                        if(!bPartSharp && asData.c_str()[j] =='%')//가로쓰기 부분삭제 시작지점//
                        {
                            bPartSharp    = true;
                            nPartSharp1    = nStartW;
                            continue;
                        }
						else if(bPartSharp && asData.c_str()[j] =='%')//가로쓰기 부분삭제 종료지점//
                        {
							nPartSharp2    = nStartW + nTxtW-1;//231117//nTextW -> nTxtW//
                            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                            tempData.tpSTT.x    = nPartSharp1;
                            tempData.tpSTT.y    = nStartH + nTextH/2;
                            tempData.tpEND.x    = nPartSharp2;
                            tempData.tpEND.y    = nStartH + nTextH/2;
							eData->m_vSharpPos.push_back(tempData);
                            bPartSharp    = false;
                            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            continue;
                        }
                        else if(bPartSharp && j == 0)//가로쓰기 부분삭제 중 개행 후 시작지점//
                        {
                            nPartSharp1    = nStartW;
                            continue;
                        }
						else if(bPartSharp && j == nTxtLen-1)//가로쓰기 부분삭제 중 개행 전 종료지점//
                        {
                            nPartSharp2    = nStartW-1;
                            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                            tempData.tpSTT.x    = nPartSharp1;
                            tempData.tpSTT.y    = nStartH + nTextH/2;
                            tempData.tpEND.x    = nPartSharp2;
                            tempData.tpEND.y    = nStartH + nTextH/2;
                            eData->m_vSharpPos.push_back(tempData);
                            //여기선 flag해제하면 안됨//
                            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            continue;
                        }
                    }

                    asData        = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
                    asCaption     = asData;
                    IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);

                    nStartH    += nTextH;
                }

                delete slData;
                slData    = NULL;

                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				//전체삭제-TGA이미지//
                if(bAllSharp)
                {
                    nAllSharpLeft    = tPoint.x    - i*tScale.w;
                    if(i >= 6)
                        nAllSharpLeft    -= nMiddleWidth;
                    ::AlphaBlend(IMGSCREEN2->Canvas->Handle, nAllSharpLeft, tPoint.y, frmMain->BITMAP_BTN_TGA[frmMain->TgaDoc8Jimok]->Width, frmMain->BITMAP_BTN_TGA[frmMain->TgaDoc8Jimok]->Height,frmMain->BITMAP_BTN_TGA[frmMain->TgaDoc8Jimok]->Canvas->Handle,0,0,frmMain->BITMAP_BTN_TGA[frmMain->TgaDoc8Jimok]->Width,frmMain->BITMAP_BTN_TGA[frmMain->TgaDoc8Jimok]->Height,frmMain->flagbf);
					bAllSharp    = false;
                }
                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            }

            ::SetROP2 (hdc, oldro);
            ::DeleteObject( pen );
        }



		//==============================================================
		//일반폰트//
		m_font	= ::CreateFont(fontwidth, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
		hOldFont  = (HFONT)::SelectObject(hdc, m_font);
		//==============================================================

		//##########################################################################################
        //#
		//# AREA
        //#
        //##########################################################################################
        {
            //==============================================================
            //일반폰트//
			pen   = ::CreatePen(PS_SOLID, 1, cPenColor);
            ::SelectObject(hdc, pen);
            int oldro = ::SetROP2(hdc, R2_COPYPEN);
            ::SetBkMode(hdc, TRANSPARENT);
            ::SetTextColor(hdc, cPenColor);
            IMGSCREEN2->Canvas->Brush->Color    = clWhite;
            //==============================================================

			//==============================================================
			asData			= "";//한 셀 포함 문자//
			asCaption   	= "";//TextOut에 표기할 문자//
			asTemp         	= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen     	= 0;
			nTextW        	= 0;
			nTextH        	= 0;
			nStartW        	= 0;
			nStartH        	= 0;
			nSumH        	= 0;
			nPartSharp1    	= 0;
			nPartSharp2    	= 0;
			nAllSharp1      = 0;
			nAllSharp2      = 0;
			nAllSharpLeft	= 0;
			//위에서 한번 초기화//eData->m_vSharpPos.clear();
			//==============================================================

			bAllSharp    = false;
            bPartSharp    = false;

			//==========================================================================================
			tPoint  = m_bsAlphaDoc8[4].tPoint;
			tScale  = m_bsAlphaDoc8[4].tScale;
			nTextW	= IMGSCREEN2->Canvas->TextWidth("면")+1;//임의글자로 체크//
			nTextH  = IMGSCREEN2->Canvas->TextHeight("면")+1;//임의글자로 체크//
			//==========================================================================================

            //==============================================================
            AnsiString  asUnit        = "";
            AnsiString  asUnitNew    = "";
            //임야는 단위를 ㎡ 변환시에만 표시하는데, 단위를 별도 체킹하지 않으므로 한번만 표시하므로 플래그 해제//
            bool        bForestUnitDisp    = false;
            //==============================================================

            for( int i = 0; i < (int)eData->m_vAREA.size(); i++)
            {
                asData = eData->m_vAREA[i].DATA;
                if(asData == "-")//NoData
                    continue;

				//230203//임야대장에도 ㎡ 가 있을 수 있다//
				if(asData.AnsiPos("㎡") > 0 || asData.AnsiPos("평방미터") > 0 || asData.AnsiPos("평") > 0)
                {
                    //No Action//
                }
                else//있는 그대로? 확인하고 주석 기재할 것//
                {
                    asData = eFunc->funcChangeAreaFormatStr(3, asData);//220119//#21//임야대장 지적 -> 정단무보 변경없이 입력그대로두기//
                }

				asData = eFunc->funcStringReplaceDoc08(asData);//260518//
				//=====================================================
                if(asData.SubString(1, 1) == "#")//전체삭제//
                {
                    bAllSharp    = true;
                    asData    = asData.Delete(1, 1);
                }
                else
                {
                    bAllSharp    = false;
                }
                //=====================================================

                //=========================================
                // 단위확인//
                int nPos    = 0;
                AnsiString  asTempUnit    = "";
                bool        bUnit    = false;
                if(m_nDOCKIND == 0)//토지대장//
				{
					for(int u = 0; u < (int)frmMain->m_vAREAUNIT.size(); u++)
                    {
                        asTempUnit    = frmMain->m_vAREAUNIT[u].DATA;

                        nPos    = asData.AnsiPos(asTempUnit);
                        if(nPos > 0)
                        {
                            bUnit    = true;
                            asUnit    = asData.SubString(nPos, asTempUnit.Length());
                            asData    = StringReplace(asData, asUnit, "", TReplaceFlags() << rfReplaceAll);
                        }

                        if(bUnit)
                        {
                            if(asUnit == "평방미터")//220120
                                asUnit    = "㎡";
                            break;
                        }
                    }
                }

                //=========================================
                TStringList *slData         = new TStringList;
                slData    = new TStringList();
                nPos    = asData.Pos("_");
                while(nPos > 0)
                {
                    asTemp     = asData.SubString(1, nPos-1);
                    slData->Add(asTemp);
                    asData         = asData.Delete(1, nPos);
                    nPos        = asData.Pos("_");
                }
                if( !asData.IsEmpty() )
                    slData->Add(asData);

                //==========================================================================================
				//실제표시//
                nStartH    = tPoint.y + (tScale.h - slData->Count * nTextH) / 2;
                //==========================================================================================

                for(int z = 0; z < slData->Count; z++)
                {
                    asData    = slData->Strings[z];

                    //211206//
                    int nSharpPos1    = 0;
                    int nSharpPos2    = 0;
                    if(m_bAreaChange)
                    {
                        if(m_nDOCKIND == 0)//토지대장//
                        {
                            if(asUnit == "평" || asUnit == "홉" || asUnit == "작")
                            {
                                //211206//=============
                                nSharpPos1    = asData.Pos("%");
                                if(nSharpPos1 > 0)
                                    asData    = asData.Delete(nSharpPos1, 1);
                                nSharpPos2    = asData.Pos("%");
                                if(nSharpPos2 > 0)
                                    asData    = asData.Delete(nSharpPos2, 1);
                                //=====================

                                asData    = eFunc->funcChangeAreaFormatStr(1, asData + asUnit);//평->㎡//

                                //211206//=============
                                if(nSharpPos1 > 0)
                                    asData    = "%" + asData;
                                if(nSharpPos2 > 0)
									asData    = asData + "%";
                                //=====================

                                asUnitNew    = "㎡";

                                //==========================================
                                //230213//㎡일때는 맨처음에만 단위 표시한다//
                                if(i > 0)
                                {
                                    bUnit = false;
                                }
                                //==========================================
                            }
                            else
                            {
                                asUnitNew    = asUnit;
                            }
                        }
                        else if(m_nDOCKIND == 1)//임야대장//
                        {
                            //211206//=============
                            nSharpPos1    = asData.Pos("%");
                            if(nSharpPos1 > 0)
                                asData    = asData.Delete(nSharpPos1, 1);
                            nSharpPos2    = asData.Pos("%");
                            if(nSharpPos2 > 0)
                                asData    = asData.Delete(nSharpPos2, 1);
                            //=====================

                            asData    = eFunc->funcChangeAreaFormatStr(1, asData);//정단무보->㎡

                            //211206//=============
                            if(nSharpPos1 > 0)
                                asData    = "%" + asData;
							if(nSharpPos2 > 0)
                                asData    = asData + "%";
                            //=====================

                            if( !bForestUnitDisp )
                            {
                                asUnitNew    = "㎡";
                                bUnit    = true;
                                bForestUnitDisp    = true;
                            }
                        }
					}

					asTemp		= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);//부분삭제처리전 '%'없는 TextWidth 위한 임시처리//
					int nTxtW  	= IMGSCREEN2->Canvas->TextWidth(asTemp);//231117//nTextW -> nTxtW//
					nStartW    	= tPoint.x - i*tScale.w + (tScale.w - nTxtW) / 2;//가로쓰기-중간//231117//nTextW -> nTxtW//
                    if(i >= 6)
                        nStartW    -= nMiddleWidth;

                    nTxtLen = asData.Length();
                    for(int j = 0; j < nTxtLen; j++)
                    {
                        if(!bPartSharp && asData.c_str()[j] =='%')//가로쓰기 부분삭제 시작지점//
                        {
                            bPartSharp    = true;
                            nPartSharp1   = nStartW;
                            continue;
                        }
                        else if(bPartSharp && asData.c_str()[j] =='%')//가로쓰기 부분삭제 종료지점//
                        {
							nPartSharp2    = nStartW + nTxtW-1;//231117//nTextW -> nTxtW//
                            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                            tempData.tpSTT.x    = nPartSharp1;
							tempData.tpSTT.y    = nStartH + nTextH/2;
                            tempData.tpEND.x    = nPartSharp2;
                            tempData.tpEND.y    = nStartH + nTextH/2;
                            eData->m_vSharpPos.push_back(tempData);
                            bPartSharp    = false;
                            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            continue;
                        }
                        else if(bPartSharp && j == 0)//가로쓰기 부분삭제 중 개행 후 시작지점//
                        {
							nPartSharp1    = nStartW;
                            continue;
                        }
                        else if(bPartSharp && j == nTxtLen-1)//가로쓰기 부분삭제 중 개행 전 종료지점//
                        {
                            if(asData.c_str()[j] =='%')//종료//211201//
                                bPartSharp    = false;
							nPartSharp2    = nStartW + nTxtW-1;//231117//nTextW -> nTxtW//
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                            tempData.tpSTT.x    = nPartSharp1;
                            tempData.tpSTT.y    = nStartH + nTextH/2;
                            tempData.tpEND.x    = nPartSharp2;
                            tempData.tpEND.y    = nStartH + nTextH/2;
                            eData->m_vSharpPos.push_back(tempData);
                            //여기선 flag해제하면 안됨//
                            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            continue;
                        }
                    }

                    asData        = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
                    asCaption     = asData;
                    IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);

                    nStartH    += nTextH;
                }

                //=========================================
                //단위표시//
                if(bUnit)
                {
					if(m_bAreaChange)
					{
						int nTxtW    = IMGSCREEN2->Canvas->TextWidth(asUnitNew)+1;
                        nStartW    = tPoint.x - (i-1)*tScale.w;//가로쓰기-우측//단위//
                        if(i >= 6)
                            nStartW    -= nMiddleWidth;

						IMGSCREEN2->Canvas->TextOutA(nStartW-nTxtW, tPoint.y+tScale.h-nTextH, asUnitNew);
                    }
                    else
                    {
                        int nTxtW    = IMGSCREEN2->Canvas->TextWidth(asUnit)+1;
                        nStartW    = tPoint.x - (i-1)*tScale.w;//가로쓰기-우측//단위//
                        if(i >= 6)
                            nStartW    -= nMiddleWidth;
                        IMGSCREEN2->Canvas->TextOutA(nStartW-nTxtW, tPoint.y+tScale.h-nTextH, asUnit);
                    }
                }
                //=========================================

                delete slData;
                slData    = NULL;

                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				//전체삭제-TGA이미지//
                if(bAllSharp)
				{
					nAllSharpLeft    = tPoint.x    - i*tScale.w;
                    if(i >= 6)
                        nAllSharpLeft    -= nMiddleWidth;
					::AlphaBlend(IMGSCREEN2->Canvas->Handle, nAllSharpLeft, tPoint.y, frmMain->BITMAP_BTN_TGA[frmMain->TgaDoc8Jimok]->Width, frmMain->BITMAP_BTN_TGA[frmMain->TgaDoc8Jimok]->Height,frmMain->BITMAP_BTN_TGA[frmMain->TgaDoc8Jimok]->Canvas->Handle,0,0,frmMain->BITMAP_BTN_TGA[frmMain->TgaDoc8Jimok]->Width,frmMain->BITMAP_BTN_TGA[frmMain->TgaDoc8Jimok]->Height,frmMain->flagbf);
                    bAllSharp    = false;
                }
                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            }

            ::SetROP2 (hdc, oldro);
            ::DeleteObject( pen );
        }



		//==============================================================
		//일반폰트//
		m_font	= ::CreateFont(fontwidth, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
		hOldFont  = (HFONT)::SelectObject(hdc, m_font);
		//==============================================================


        //##########################################################################################
        //#
		//# VALUE1
        //#
        //##########################################################################################
        {
            //==============================================================
			//일반폰트//
            pen   = ::CreatePen(PS_SOLID, 1, cPenColor);
            ::SelectObject(hdc, pen);
            int oldro = ::SetROP2(hdc, R2_COPYPEN);
            ::SetBkMode(hdc, TRANSPARENT);
            ::SetTextColor(hdc, cPenColor);
            IMGSCREEN2->Canvas->Brush->Color    = clWhite;
            //==============================================================

			//==============================================================
			asData			= "";//한 셀 포함 문자//
			asCaption   	= "";//TextOut에 표기할 문자//
			asTemp         	= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen     	= 0;
			nTextW        	= 0;
			nTextH        	= 0;
			nStartW        	= 0;
			nStartH        	= 0;
			nSumH        	= 0;
			nPartSharp1    	= 0;
			nPartSharp2    	= 0;
			nAllSharp1      = 0;
			nAllSharp2      = 0;
			nAllSharpLeft	= 0;
			//위에서 한번 초기화//eData->m_vSharpPos.clear();
			//==============================================================

            bAllSharp    = false;
            bPartSharp    = false;

            //==========================================================================================
			tPoint  = m_bsAlphaDoc8[5].tPoint;
			tScale  = m_bsAlphaDoc8[5].tScale;
			nTextW	= IMGSCREEN2->Canvas->TextWidth("과")+1;//임의글자로 체크//
			nTextH  = IMGSCREEN2->Canvas->TextHeight("과")+1;//임의글자로 체크//
            //==========================================================================================

            for( int i = 0; i < (int)eData->m_vVALUE1.size(); i++)
            {
                asData = eData->m_vVALUE1[i].DATA;

                if(asData == "-")//NoData
                    continue;

				asData = eFunc->funcStringReplaceDoc08(asData);//260518//
				//221108//DB에는 기준수확량, 임대가격, 토지등급 텍스트에 []처리 되어 있으므로 삭제( <> 로 표현되어야 하기에 아래코드에서 처리)
                asData    = StringReplace(asData, "[", "", TReplaceFlags() << rfReplaceAll);
                asData    = StringReplace(asData, "]", "", TReplaceFlags() << rfReplaceAll);

                //=====================================================
                if(asData.SubString(1, 1) == "#")//전체삭제//
                {
                    bAllSharp    = true;
                    asData    = asData.Delete(1, 1);
                }
                else
                {
                    bAllSharp    = false;
                }
                //=====================================================


                //=========================================
                // 단위확인//
                int nPos    = 0;
                AnsiString  asUnit    = "";
                bool        bUnit    = false;
                for(int u = 0; u < (int)frmMain->m_vVALUEUNIT.size(); u++)
                {
                    asUnit    = frmMain->m_vVALUEUNIT[u].DATA;

                    nPos    = asData.AnsiPos(asUnit);
                    if(nPos > 0)
                    {
                        bUnit    = true;
                        asUnit    = asData.SubString(nPos, asUnit.Length());
						asData    = StringReplace(asData, asUnit, "", TReplaceFlags() << rfReplaceAll);
                    }

                    if(bUnit)
                        break;
                }
                //=========================================

                //=========================================
                TStringList *slData         = new TStringList;
                slData    = new TStringList();
                int nPos1    = asData.AnsiPos("기준수확량");
                int nPos2    = asData.AnsiPos("임대가격");
                int nPos3    = asData.AnsiPos("토지등급");

                nPos    = 1;
                while(nPos1 > 0 || nPos2 > 0 || nPos3 > 0 || nPos > 0)
                {
                    if(nPos1 > 0)
                        asTemp     = "기준수확량";
                    if(nPos2 > 0)
                        asTemp     = "임대가격";
                    if(nPos3 > 0)
                        asTemp     = "토지등급";

                    if(nPos1 > 0 || nPos2 > 0 || nPos3 > 0)
                    {
                        if(nPos2 > nPos1)        nPos    = nPos2;
                        else if(nPos3 > nPos1)    nPos    = nPos3;
                        else if(nPos3 > nPos2)    nPos    = nPos3;
                        else if(nPos1 > 0)        nPos    = nPos1;
                        else if(nPos2 > 0)    nPos    = nPos2;
                        else if(nPos3 > 0)    nPos    = nPos3;

						//=====================================
                        //211201//#2
                        int nEndPos    = asTemp.Length() + nPos - 1;
                        if(asData.c_str()[nEndPos] =='%')
                            nEndPos++;
                        asTemp     = asData.SubString(1, nEndPos);
                        asData  = asData.Delete(1, nEndPos);
                        //220127//TEST//if(nPos1 > 0 || nPos2 > 0)
                        if(asTemp.Pos("기준수확량") > 0 || asTemp.Pos("임대가격") > 0)
                        {
                            //=======================================
                            //211208//31025.254.1    //OLD//asTemp     = "<" + asTemp + ">";
                            if(asTemp.SubString(1, 1) == "%" && asTemp.SubString(asTemp.Length(), 1) != "%")
                            {
                                asTemp     = "<" + asTemp + "%>";
                                if(!asData.IsEmpty() && asData.SubString(asData.Length(), 1) =='%' && asData.SubString(1, 1) != "%")
                                {
                                    asData    = "%" + asData;
                                }
                            }
                            else
                            {
                                asTemp     = "<" + asTemp + ">";
                            }
                            //=======================================
                        }
                        slData->Add(asTemp);
                        //=====================================

                        nPos1    = 0;
                        nPos2    = 0;
                        nPos3    = 0;
                    }
    //                else if(nPos >= 1)//맨처음에는 그냥 들어오게 하려고 1로 설정한 것임//원래는 데이터가 있어야 하므로 1이상을 체크//
	//                {
    //                    asTemp     = asData.SubString(1, nPos-1);
    //                    asData  = asData.Delete(1, nPos);
    //                    if( !asTemp.IsEmpty() )
    //                        slData->Add(asTemp);
    //                }
                    nPos    = asData.Pos("_");
                    //==================================
                    //211201//#1
                    if(nPos > 0)
                    {
                        asTemp     = asData.SubString(1, nPos-1);
                        asData    = asData.Delete(1, nPos);
                        if( !asTemp.IsEmpty() )
                            slData->Add(asTemp);
                    }
                    nPos1    = asData.AnsiPos("기준수확량");
                    nPos2    = asData.AnsiPos("임대가격");
                    nPos3    = asData.AnsiPos("토지등급");
                    //==================================
                }
                if( !asData.IsEmpty() )
                    slData->Add(asData);

                //==========================================================================================
				//실제표시//
				nStartH    = tPoint.y + (tScale.h - slData->Count * nTextH) / 2;
                //==========================================================================================

                for(int z = 0; z < slData->Count; z++)
                {
					asData		= slData->Strings[z];

					asTemp    	= StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);//부분삭제처리전 '%'없는 TextWidth 위한 임시처리//
					int	nTxtW   = IMGSCREEN2->Canvas->TextWidth(asTemp);//231117//nTextW -> nTxtW//
					nStartW    	= tPoint.x - i*tScale.w + (tScale.w - nTxtW) / 2;//가로쓰기-중간//231117//nTextW -> nTxtW//
                    if(i >= 6)
                        nStartW    -= nMiddleWidth;

                    int nPartTextWidth    = 0;//211229//25031.181.2//
                    nTxtLen = asData.Length();
                    for(int j = 0; j < nTxtLen; j++)
                    {
                        if(!bPartSharp && asData.c_str()[j] =='%')//가로쓰기 부분삭제 시작지점//
                        {
                            bPartSharp    = true;
                            nPartSharp1    = nStartW + nPartTextWidth;//211229//25031.181.2//nPartSharp1    = nStartW;
                            continue;
                        }
                        else if(bPartSharp && asData.c_str()[j] =='%')//가로쓰기 부분삭제 종료지점//
                        {
                            nPartSharp2    = nStartW + nPartTextWidth-1;//211229//25031.181.2//nPartSharp2    = nStartW + nTextW-1;
                            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                            tempData.tpSTT.x    = nPartSharp1;
                            tempData.tpSTT.y    = nStartH + nTextH/2;
                            tempData.tpEND.x    = nPartSharp2;
                            tempData.tpEND.y    = nStartH + nTextH/2;
                            eData->m_vSharpPos.push_back(tempData);
                            bPartSharp    = false;
                            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            continue;
                        }
                        else if(bPartSharp && j == 0)//가로쓰기 부분삭제 중 개행 후 시작지점//
                        {
                            nPartSharp1    = nStartW;
                            continue;
                        }
						else if(bPartSharp && j == nTxtLen-1)//가로쓰기 부분삭제 중 개행 전 종료지점//
                        {
                            nPartSharp2    = nStartW-1;
                            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                            tempData.tpSTT.x    = nPartSharp1;
                            tempData.tpSTT.y    = nStartH + nTextH/2;
                            tempData.tpEND.x    = nPartSharp2;
                            tempData.tpEND.y    = nStartH + nTextH/2;
                            eData->m_vSharpPos.push_back(tempData);
                            //여기선 flag해제하면 안됨//
                            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            continue;
                        }
                        else//211229//25031.181.2//
                        {
                            asTemp    = asData.SubString(j, 1);
                            nPartTextWidth    += IMGSCREEN2->Canvas->TextWidth(asTemp);
                        }
                    }

                    asData        = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
                    asCaption     = asData;
                    IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);

                    nStartH    += nTextH;
                }

                //=========================================
                //단위표시//
                if(bUnit)
                {
                    int nTxtW    = IMGSCREEN2->Canvas->TextWidth(asUnit)+1;
                    nStartW    = tPoint.x - (i-1)*tScale.w;//가로쓰기-우측//단위//
					if(i >= 6)
                        nStartW    -= nMiddleWidth;
                    IMGSCREEN2->Canvas->TextOutA(nStartW-nTxtW, tPoint.y+tScale.h-nTextH, asUnit);
                }
                //=========================================

                delete slData;
                slData    = NULL;

                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				//전체삭제-TGA이미지//
                if(bAllSharp)
                {
                    nAllSharpLeft    = tPoint.x    - i*tScale.w;
                    if(i >= 6)
                        nAllSharpLeft    -= nMiddleWidth;
                    ::AlphaBlend(IMGSCREEN2->Canvas->Handle, nAllSharpLeft, tPoint.y, frmMain->BITMAP_BTN_TGA[frmMain->TgaDoc8Value]->Width, frmMain->BITMAP_BTN_TGA[frmMain->TgaDoc8Value]->Height,frmMain->BITMAP_BTN_TGA[frmMain->TgaDoc8Value]->Canvas->Handle,0,0,frmMain->BITMAP_BTN_TGA[frmMain->TgaDoc8Value]->Width,frmMain->BITMAP_BTN_TGA[frmMain->TgaDoc8Value]->Height,frmMain->flagbf);
                    bAllSharp    = false;
                }
                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            }
            ::SetROP2 (hdc, oldro);
            ::DeleteObject( pen );
        }



        //##########################################################################################
        //#
        //# VALUE2
        //#
        //##########################################################################################
        {
            //==============================================================
			//일반폰트//
            pen   = ::CreatePen(PS_SOLID, 1, cPenColor);
            ::SelectObject(hdc, pen);
            int oldro = ::SetROP2(hdc, R2_COPYPEN);
            ::SetBkMode(hdc, TRANSPARENT);
            ::SetTextColor(hdc, cPenColor);
            IMGSCREEN2->Canvas->Brush->Color    = clWhite;
            //==============================================================

			//==============================================================
			asData			= "";//한 셀 포함 문자//
			asCaption   	= "";//TextOut에 표기할 문자//
			asTemp         	= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen     	= 0;
			nTextW        	= 0;
			nTextH        	= 0;
			nStartW        	= 0;
			nStartH        	= 0;
			nSumH        	= 0;
			nPartSharp1    	= 0;
			nPartSharp2    	= 0;
			nAllSharp1      = 0;
			nAllSharp2      = 0;
			nAllSharpLeft	= 0;
			//위에서 한번 초기화//eData->m_vSharpPos.clear();
			//==============================================================

            bAllSharp    = false;
            bPartSharp    = false;

            //==========================================================================================
			tPoint  = m_bsAlphaDoc8[6].tPoint;
			tScale  = m_bsAlphaDoc8[6].tScale;
			nTextW	= IMGSCREEN2->Canvas->TextWidth("과")+1;//임의글자로 체크//
			nTextH  = IMGSCREEN2->Canvas->TextHeight("과")+1;//임의글자로 체크//가로쓰기//
            //==========================================================================================

            for( int i = 0; i < (int)eData->m_vVALUE2.size(); i++)
            {
                asData = eData->m_vVALUE2[i].DATA;

                if(asData == "-")//NoData
                    continue;

				asData = eFunc->funcStringReplaceDoc08(asData);//260518//
				//=====================================================
				if(asData.SubString(1, 1) == "#")//전체삭제//
                {
                    bAllSharp    = true;
                    asData    = asData.Delete(1, 1);
                }
                else
                {
                    bAllSharp    = false;
                }
                //=====================================================


                //=========================================
                // 단위확인//
                int nPos    = 0;
                AnsiString  asUnit    = "";
                bool        bUnit    = false;
                for(int u = 0; u < (int)frmMain->m_vVALUE2UNIT.size(); u++)
				{
                    asUnit    = frmMain->m_vVALUE2UNIT[u].DATA;

                    nPos    = asData.AnsiPos(asUnit);
                    if(nPos > 0)
                    {
                        bUnit    = true;
                        asUnit    = asData.SubString(nPos, asUnit.Length());
                        asData    = StringReplace(asData, asUnit, "", TReplaceFlags() << rfReplaceAll);
                    }

                    if(bUnit)
                        break;
                }
                //=========================================


                //=========================================
                TStringList *slData         = new TStringList;
                slData    = new TStringList();
                nPos    = asData.Pos("_");
                while(nPos > 0)
                {
                    asTemp     = asData.SubString(1, nPos-1);
                    slData->Add(asTemp);
                    asData         = asData.Delete(1, nPos);
                    nPos        = asData.Pos("_");
                }
                if( !asData.IsEmpty() )
                    slData->Add(asData);

                //==========================================================================================
                nStartH    = tPoint.y + (tScale.h - slData->Count * nTextH) / 2;
                //==========================================================================================

                for(int z = 0; z < slData->Count; z++)
                {
                    asData    = slData->Strings[z];

                    asTemp    = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);//부분삭제처리전 '%'없는 TextWidth 위한 임시처리//
					int nTxtW    = IMGSCREEN2->Canvas->TextWidth(asTemp);//231117//nTextW -> nTxtW//
					nStartW    = tPoint.x - i*tScale.w + (tScale.w - nTxtW) / 2;//가로쓰기-중간//231117//nTextW -> nTxtW//
                    if(i >= 6)
                        nStartW    -= nMiddleWidth;

                    nTxtLen = asData.Length();
                    for(int j = 0; j < nTxtLen; j++)
                    {
                        if(!bPartSharp && asData.c_str()[j] =='%')//가로쓰기 부분삭제 시작지점//
                        {
                            bPartSharp    = true;
                            nPartSharp1    = nStartW;
                            continue;
                        }
                        else if(bPartSharp && asData.c_str()[j] =='%')//가로쓰기 부분삭제 종료지점//
                        {
                            nPartSharp2    = nStartW + nTxtW-1;//231117//nTextW -> nTxtW//
                            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                            tempData.tpSTT.x    = nPartSharp1;
                            tempData.tpSTT.y    = nStartH + nTextH/2;
                            tempData.tpEND.x    = nPartSharp2;
                            tempData.tpEND.y    = nStartH + nTextH/2;
                            eData->m_vSharpPos.push_back(tempData);
                            bPartSharp    = false;
                            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            continue;
                        }
						else if(bPartSharp && j == 0)//가로쓰기 부분삭제 중 개행 후 시작지점//
                        {
                            nPartSharp1    = nStartW;
                            continue;
                        }
                        else if(bPartSharp && j == nTxtLen-1)//가로쓰기 부분삭제 중 개행 전 종료지점//
                        {
                            nPartSharp2    = nStartW-1;
                            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                            tempData.tpSTT.x    = nPartSharp1;
                            tempData.tpSTT.y    = nStartH + nTextH/2;
                            tempData.tpEND.x    = nPartSharp2;
                            tempData.tpEND.y    = nStartH + nTextH/2;
                            eData->m_vSharpPos.push_back(tempData);
                            //여기선 flag해제하면 안됨//
                            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            continue;
                        }
                    }

                    asData        = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
                    asCaption     = asData;
                    IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);

                    nStartH    += nTextH;
                }

                //=========================================
                //단위표시//
                if(bUnit)
                {
                    int nTxtW  = IMGSCREEN2->Canvas->TextWidth(asUnit)+1;
                    nStartW    = tPoint.x - (i-1)*tScale.w;//가로쓰기-우측//단위//
					if(i >= 6)
                        nStartW    -= nMiddleWidth;
                    IMGSCREEN2->Canvas->TextOutA(nStartW-nTxtW, tPoint.y+tScale.h-nTextH, asUnit);
                }
                //=========================================

                delete slData;
                slData    = NULL;
            }

            ::SetROP2 (hdc, oldro);
            ::DeleteObject( pen );
        }



        //##########################################################################################
        //#
		//# HISTORY
        //#
        //##########################################################################################
        {
            //==============================================================
            //일반폰트//
            pen   = ::CreatePen(PS_SOLID, 1, cPenColor);
            ::SelectObject(hdc, pen);
            int oldro = ::SetROP2(hdc, R2_COPYPEN);
            ::SetBkMode(hdc, TRANSPARENT);
            ::SetTextColor(hdc, cPenColor);
            IMGSCREEN2->Canvas->Brush->Color    = clWhite;
            //==============================================================

			//==============================================================
			asData			= "";//한 셀 포함 문자//
			asCaption   	= "";//TextOut에 표기할 문자//
			asTemp         	= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen     	= 0;
			nTextW        	= 0;
			nTextH        	= 0;
			nStartW        	= 0;
			nStartH        	= 0;
			nSumH        	= 0;
			nPartSharp1    	= 0;
			nPartSharp2    	= 0;
			nAllSharp1      = 0;
			nAllSharp2      = 0;
			nAllSharpLeft	= 0;
			//위에서 한번 초기화//eData->m_vSharpPos.clear();
			//==============================================================

            bAllSharp    = false;
            bPartSharp    = false;

            //==========================================================================================
			tPoint  = m_bsAlphaDoc8[7].tPoint;
			tScale  = m_bsAlphaDoc8[7].tScale;
			nTextW	= IMGSCREEN2->Canvas->TextWidth("연")+1;//임의글자로 체크//
			nTextH  = IMGSCREEN2->Canvas->TextHeight("연")+1;//임의글자로 체크//
            //==========================================================================================

            //==========================================================================================
            bool    bOverCell        = false;//#OVERCELL//
            int     nOverCellW        = 0;//#OVERCELL//

            for( int i = 0; i < (int)eData->m_vHISTORY.size(); i++)
            {
                asData = eData->m_vHISTORY[i].DATA;

                if(asData == "-")//NoData
                    continue;

				asData = eFunc->funcStringReplaceDoc08(asData);//260518//
				//221020//[REQ]연혁개행처리//            asData    = StringReplace(asData, "_", "", TReplaceFlags() << rfReplaceAll);//211208//금란차장Req//연혁은 개행문자('_') 제거//
				//=====================================================
                if(asData.SubString(1, 1) == "#")//전체삭제//
                {
                    bAllSharp    = true;
                    asData    = asData.Delete(1, 1);
                }
                else
                {
                    bAllSharp    = false;
                }
                //=====================================================

                //---
                nTxtLen = asData.Length();
                nSumH    = 0;

                TStringList *slData         = new TStringList;
                slData    = new TStringList();
                //연혁에는 개행하지 않음//
    //            int nPos    = asData.Pos("_");
    //            while(nPos > 0)
    //            {
    //                asTemp     = asData.SubString(1, nPos-1);
    //                slData->Add(asTemp);
	//                asData  = asData.Delete(1, nPos);
    //                nPos    = asData.Pos("_");
    //            }
    //            slData->Add(asData);

                //개행없는 데이터 처리//
                int nLineTxtLen    = 0;//Cell 높이와 nTextH로 한줄 글자 수 계산//
                int nLineTxtCnt    = 0;//한글과 숫자 Length()가 다르게 나오기 때문에 정확한 개행 길이만큼 계산이 안되서 사용//
                if(slData->Count == 0 && nTextW > 0)
                {
                    //연혁 셀 넘치는 경우 처리//#OVERCELL//
                    int nMaxTxtLen       = 0;
                    int nMaxWLineLen       = 0;
                    int nMaxHLineLen    = 0;
                    int nCountTxtLen    = 0;
                    nMaxWLineLen    = tScale.w/nTextW;
                    nMaxHLineLen    = tScale.h/nTextH;
                    nMaxTxtLen        = nMaxWLineLen * nMaxHLineLen;

                    nLineTxtLen    = tScale.h/nTextH;
                    asTemp    = "";

                    for(int j = 0; j < nTxtLen; j++)
                    {
                        if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asTemp = asTemp    + asData.SubString(j+1, 2);
                            if(nLineTxtCnt >= nLineTxtLen-1)
                            {
                                slData->Add(asTemp);
                                asTemp    = "";
                                nCountTxtLen    += nLineTxtCnt+1;
                                nLineTxtCnt    = 0;
                            }
							else
                            {
								nLineTxtCnt++;//231215//ReturnCode//세로쓰기는한글2글자로체킹할필요없다.//231117//++ -> += 2
                            }
                            j++;
                        }
                        else
                        {
                            //=====================================
							//221020//[REQ]연혁 개행처리 & 자동개행//
                            if(asData.SubString(j+1, 1) == "_")
                            {
                                if( !asTemp.IsEmpty())
                                {
                                    slData->Add(asTemp);
                                    asTemp    = "";
                                    nCountTxtLen    += nLineTxtCnt+1;
                                    nLineTxtCnt    = 0;
                                }
                            }
                            else
                            //=====================================
                            {
                                asTemp = asTemp + asData.SubString(j+1, 1);
                                if(nLineTxtCnt >= nLineTxtLen-1)
                                {
									slData->Add(asTemp);
                                    asTemp    = "";
                                    nCountTxtLen    += nLineTxtCnt+1;
                                    nLineTxtCnt    = 0;
                                }
                                else
                                {
									if(asData.c_str()[j] == '%')//부분삭제//데이터에는 저장, 길이에는 포함하지 않는다. 추후 제거할 것이므로//
										continue;
									nLineTxtCnt++;
                                }
                            }
                        }
                    }
                    if( !asTemp.IsEmpty() )
                    {
                        slData->Add(asTemp);
                        asTemp    = "";
                        nCountTxtLen    += nLineTxtCnt;
                    }

                    //연혁 셀 넘치는 경우 처리//#OVERCELL//
                    if(nCountTxtLen > nMaxTxtLen)
                    {
                        bOverCell    = true;
                    }
                    else
                    {
                        bOverCell    = false;
                    }
                }
                //=========================================================

				//==========================================================================================
				//실제표시//
				if(bOverCell)
                {
                    if(nOverCellW == 0)//맨처음데이터//
                        nOverCellW    = tPoint.x - (i-1)*tScale.w;//가로쓰기-우측//
                    nStartW    = nOverCellW;
                }
                else
                {
                    nStartW    = tPoint.x - (i-1)*tScale.w;//가로쓰기-우측//
				}
                if(i >= 6)
                    nStartW    -= nMiddleWidth;
				//==========================================================================================


                bool    bRevise    = false;//셀당 Width 보정 1회만 하기 위한 플래그//

                for(int z = 0; z < slData->Count; z++)
                {
                    asData    = slData->Strings[z];

                    nTxtLen = asData.Length();

					//==========================================================================================
					//실제표시//
					nStartW    -= nTextW;
                    if( !bRevise && nStartW < tPoint.x - i*tScale.w)//맨처음에만 보정해준다//
					{
                        nStartW     -= 4;/*Gap*/
                        bRevise    = true;
                    }
                    nStartH    = tPoint.y;//세로쓰기-상단//
	                //==========================================================================================

                    if(bAllSharp)//전체삭제//
						nAllSharp2    = nStartH-1;

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(시작)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp1    = nStartH;
					}
					//=========================================================

					//=========================================================
					for(int j = 0; j < nTxtLen; j++)
                    {
                        if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
                            asCaption = asData.SubString(j+1, 2);
                            IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
							j++;

//241204//PlanToDelete//세로쓰기 취소선 처리//
//							if(bPartSharp && j == 1)//세로쓰기 부분삭제 중 개행 후 시작지점//211201//#9//한글이라 2byte이므로 j==1로 체크//
//							{
//								nPartSharp1    = nStartH;
//								nStartH    += nTextH;//211208
//								continue;
//							}
//							else if(bPartSharp && j == nTxtLen-1)//세로쓰기 부분삭제 중 개행 전 종료지점//
//							{
//								nPartSharp2    = nStartH+nTextH-1;
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
//								tempData.tpSTT.x    = nStartW + nTextW/2;
//								tempData.tpSTT.y    = nPartSharp1;
//								tempData.tpEND.x    = nStartW + nTextW/2;
//								tempData.tpEND.y    = nPartSharp2;
//								eData->m_vSharpPos.push_back(tempData);
//								//여기선 flag해제하면 안됨//
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								continue;
//							}
						}
                        else
                        {
							if(!bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(시작)//
							{
                                bPartSharp    = true;
                                nPartSharp1    = nStartH;
                                continue;
                            }
							else if(bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(종료)//
							{
                                nPartSharp2    = nStartH-1;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                                tempData.tpSTT.x    = nStartW + nTextW/2;
								tempData.tpSTT.y    = nPartSharp1;
                                tempData.tpEND.x    = nStartW + nTextW/2;
                                tempData.tpEND.y    = nPartSharp2;
                                eData->m_vSharpPos.push_back(tempData);
                                bPartSharp    = false;
                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                continue;
                            }
//241204//PlanToDelete//세로쓰기 취소선 처리//
//							else if(bPartSharp && j == 0)//세로쓰기 부분삭제 중 개행 후 시작지점//
//                            {
//                                asCaption = asData.SubString(j+1, 1);
//                                IMGSCREEN2->Canvas->TextOutA(nStartW+m_nNumberL, nStartH, asCaption);
//                                nPartSharp1    = nStartH-1;//211201//#10//아래코드랑 순서 변경//41021.303.1//
//                                nStartH    += nTextH;
//                                continue;
//                            }
//                            else if(bPartSharp && j == nTxtLen-1)//세로쓰기 부분삭제 중 개행 전 종료지점//
//                            {
//                                asCaption = asData.SubString(j+1, 1);
//                                IMGSCREEN2->Canvas->TextOutA(nStartW+m_nNumberL, nStartH, asCaption);
//                                nStartH    += nTextH;
//                                nPartSharp2    = nStartH-1;
//                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
//                                tempData.tpSTT.x    = nStartW + nTextW/2;
//                                tempData.tpSTT.y    = nPartSharp1;
//                                tempData.tpEND.x    = nStartW + nTextW/2;
//                                tempData.tpEND.y    = nPartSharp2;
//                                eData->m_vSharpPos.push_back(tempData);
//                                //여기선 flag해제하면 안됨//
//                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								continue;
//							}

                            asCaption = asData.SubString(j+1, 1);
                            IMGSCREEN2->Canvas->TextOutA(nStartW+m_nNumberL, nStartH, asCaption);
                        }

                        nStartH    += nTextH;
					}

					//=========================================================
					//241203//취소선 처리 중 개행(종료시점)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x    = nStartW + nTextW/2;
						tempData.tpSTT.y    = nPartSharp1;
						tempData.tpEND.x    = nStartW + nTextW/2;
						tempData.tpEND.y    = nPartSharp2;
						eData->m_vSharpPos.push_back(tempData);
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
					//=========================================================

					//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					//전체삭제-취소선//
                    if(bAllSharp)
                    {
                        memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                        tempData.tpSTT.x    = nStartW + nTextW/2;
                        tempData.tpSTT.y    = nAllSharp1;
                        tempData.tpEND.x    = nStartW + nTextW/2;
                        tempData.tpEND.y    = nAllSharp2;
                        eData->m_vSharpPos.push_back(tempData);
                        bAllSharp    = false;
                    }
                    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				}

                delete slData;
                slData    = NULL;

                if(bOverCell)
                {
                    nOverCellW    = nStartW - nTextW;
                }
                else
                {
					nOverCellW    = 0;
                }
            }

            ::SetROP2 (hdc, oldro);
            ::DeleteObject( pen );
		}



        //##########################################################################################
        //#
        //# DATE
        //#
        //##########################################################################################
		{
            //==============================================================
            //일반폰트//
            pen   = ::CreatePen(PS_SOLID, 1, cPenColor);
            ::SelectObject(hdc, pen);
            int oldro = ::SetROP2(hdc, R2_COPYPEN);
            ::SetBkMode(hdc, TRANSPARENT);
            ::SetTextColor(hdc, cPenColor);
            IMGSCREEN2->Canvas->Brush->Color    = clWhite;
            //==============================================================

			//==============================================================
			asData			= "";//한 셀 포함 문자//
			asCaption   	= "";//TextOut에 표기할 문자//
			asTemp         	= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen     	= 0;
			nTextW        	= 0;
			nTextH        	= 0;
			nStartW        	= 0;
			nStartH        	= 0;
			nSumH        	= 0;
			nPartSharp1    	= 0;
			nPartSharp2    	= 0;
			nAllSharp1      = 0;
			nAllSharp2      = 0;
			nAllSharpLeft	= 0;
			//위에서 한번 초기화//eData->m_vSharpPos.clear();
			//==============================================================

			bAllSharp    = false;
            bPartSharp    = false;

            //==========================================================================================
			tPoint  = m_bsAlphaDoc8[8].tPoint;
			tScale  = m_bsAlphaDoc8[8].tScale;
			nTextW	= IMGSCREEN2->Canvas->TextWidth("일")+1;//임의글자로 체크//
			nTextH  = IMGSCREEN2->Canvas->TextHeight("일")+1;//임의글자로 체크//
            //==========================================================================================

            for( int i = 0; i < (int)eData->m_vOWNINFODATE.size(); i++)
            {
                asData = eData->m_vOWNINFODATE[i].DATA;

                if(asData == "-")//NoData
                    continue;

                //=====================================================
                //211201//#7//월, 일 등이 비어 있는 경우 존재//410.26.1.195.8
    //            asData    = StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);
				//=====================================================
                asData    = StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
                asData    = StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
                asData    = StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);

                //=====================================================
                if(asData.SubString(1, 1) == "#")//전체삭제//
                {
                    bAllSharp    = true;
                    asData    = asData.Delete(1, 1);
                }
                else
                {
                    bAllSharp    = false;
                }
                //=====================================================

                if(asData.SubString(1, 1) == "%" && asData.SubString(asData.Length(), 1) == "%")//전체삭제를 부분삭제로 입력//
                {
                    bAllSharp    = true;
                    asData    = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
                }
                else
                {
                    bAllSharp    = false;
                }

                //=====================================================
                //230208//#REQ//내용이 있지만 식별이 불가한 경우 처리//
                if(asData != "판독불가")
                //=====================================================
                {
                    asData    = eFunc->funcChangeDateStrFormatDate(asData.c_str());
                    asData    = eFunc->funcChangeDateFormatString(3, asData.c_str());
				}

                //---
                nTxtLen = asData.Length();
                nSumH    = 0;

                TStringList *slData         = new TStringList;
                slData    = new TStringList();
                //일자에는 개행하지 않음//
                if(nTxtLen > 0)
                {
                    //=====================================================
                    //230208//#REQ//내용이 있지만 식별이 불가한 경우 처리//
                    if(asData != "판독불가")
                    //=====================================================
                    {
                        //년도//
                        int nPos     = asData.AnsiPos("년");
                        asTemp     = asData.SubString(1, nPos+1);
                        slData->Add(asTemp);
                        asData  = asData.Delete(1, nPos+1);
                        //월일//
                        asTemp     = asData;
                        //211216//도청김훈곤주무관Req//Date에 5줄로 맞춰달라//
                        asTemp    = StringReplace(asTemp, "월", "월 ", TReplaceFlags() << rfReplaceAll);
                        //====================================================
                        //211201//#7//월, 일 등이 비어 있는 경우 존재//410.26.1.195.8
                        if(asTemp.AnsiPos("월") == 0)
                            asTemp    = " 월" + asTemp;
                        if(asTemp.AnsiPos("일") == 0)
                            asTemp    = asTemp + " 일";
                        //====================================================
                        slData->Add(asTemp);
                    }
					//=====================================================
                    //230208//#REQ//내용이 있지만 식별이 불가한 경우 처리//
                    else
                    {
                        slData->Add("판 독");
                        slData->Add("불 가");
                    }
                    //=====================================================
                }
                //=========================================================

				//======================================
				//실제표시//
				//211228//보정//32028.230//31039.18.1
                if(i == 10)
                    nStartW    = tPoint.x - (i-1)*tScale.w - 20 - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
                else if(i == 23)
                    nStartW    = tPoint.x - (i-1)*tScale.w - 12 - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
                else
                nStartW    = tPoint.x - (i-1)*tScale.w - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
                if(i%2)//95/2를 보정하기 위함//
                    nStartW    -= 1;
                //======================================
                if(i >= 11)
                    nStartW    -= (nMiddleWidth + 31);//HERE!!!
                //======================================

                for(int z = 0; z < slData->Count; z++)
                {
                    asData    = slData->Strings[z];

                    nTxtLen = asData.Length();

                    //=========================================================
                    //Height 계산//
					int nSumHeight    = 0;
                    asTemp    = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
                    for(int j = 0; j < asTemp.Length(); j++)
                    {
                        if( (asTemp.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asCaption = asTemp.SubString(j+1, 2);
                            nSumHeight    += IMGSCREEN2->Canvas->TextHeight(asCaption);
                            j++;
                        }
                        else
                        {
                            if( z == 1 && j + 1 < asTemp.Length() && (asTemp.c_str()[j] >= '0' && asTemp.c_str()[j] <= '9'))
                            {
                                if(asTemp.c_str()[j+1] >= '0' && asTemp.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
                                {
                                    asCaption = asTemp.SubString(j+1, 2);
                                    nSumHeight    += IMGSCREEN2->Canvas->TextHeight(asCaption);
                                    j++;
                                    continue;
                                }
                            }
                            asCaption = asTemp.SubString(j+1, 1);
                            nSumHeight    += IMGSCREEN2->Canvas->TextHeight(asCaption);
                        }
                    }
                    //=========================================================

					//=========================================================
					nStartW    -= nTextW;
                    nStartH    = tPoint.y + (tScale.h - nSumHeight) / 2;//세로쓰기-중간//
                    //=========================================================

					if(bAllSharp)//전체삭제//
                        nAllSharp1    = nStartH;

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(시작)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp1    = nStartH;
					}
					//=========================================================

					//=========================================================
                    for(int j = 0; j < nTxtLen; j++)
                    {
                        if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asCaption = asData.SubString(j+1, 2);
                            IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
                            j++;
						}
						else
						{
							if(!bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(시작)//
							{
                                bPartSharp    = true;
                                nPartSharp1    = nStartH;
                                continue;
                            }
							else if(bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(종료)//
                            {
                                nPartSharp2    = nStartH-1;
                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                                tempData.tpSTT.x    = nStartW + nTextW/2;
								tempData.tpSTT.y    = nPartSharp1;
                                tempData.tpEND.x    = nStartW + nTextW/2;
                                tempData.tpEND.y    = nPartSharp2;
                                eData->m_vSharpPos.push_back(tempData);
                                bPartSharp    = false;
                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                continue;
							}
//241204//PlanToDelete//세로쓰기 취소선 처리//
//							else if(bPartSharp && j == 0)//세로쓰기 부분삭제 중 개행 후 시작지점//
//							{
//								nPartSharp1    = nStartH;
//								continue;
//							}
//                            else if(bPartSharp && j == nTxtLen-1)//세로쓰기 부분삭제 중 개행 전 종료지점//
//							{
//								nPartSharp2    = nStartH-1;
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
//								tempData.tpSTT.x    = nStartW + nTextW/2;
//								tempData.tpSTT.y    = nPartSharp1;
//								tempData.tpEND.x    = nStartW + nTextW/2;
//								tempData.tpEND.y    = nPartSharp2;
//								eData->m_vSharpPos.push_back(tempData);
//								//여기선 flag해제하면 안됨//
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								continue;
//							}

                            if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
                            {
                                if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
                                {
                                    asCaption = asData.SubString(j+1, 2);
                                    IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
                                    j++;
                                    nStartH    += nTextH;
                                    continue;
                                }
                            }
                            //숫자 1자리//
                            asCaption = asData.SubString(j+1, 1);
                            IMGSCREEN2->Canvas->TextOutA(nStartW+m_nNumberL, nStartH, asCaption);
						}

                        nStartH    += nTextH;
                    }

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(종료)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x    = nStartW + nTextW/2;
						tempData.tpSTT.y    = nPartSharp1;
						tempData.tpEND.x    = nStartW + nTextW/2;
						tempData.tpEND.y    = nPartSharp2;
						eData->m_vSharpPos.push_back(tempData);
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
					//=========================================================

					//전체삭제-취소선//
                    if(bAllSharp)
					{
						nAllSharp2    = nStartH-1;
                        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                        memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                        tempData.tpSTT.x    = nStartW + nTextW/2;
                        tempData.tpSTT.y    = nAllSharp1;
                        tempData.tpEND.x    = nStartW + nTextW/2;
                        tempData.tpEND.y    = nAllSharp2;
                        eData->m_vSharpPos.push_back(tempData);
                        //bAllSharp    = false;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
				}

                delete slData;
                slData    = NULL;
            }

            ::SetROP2 (hdc, oldro);
            ::DeleteObject( pen );
        }



		//##########################################################################################
        //#
        //# REASON
        //#
        //##########################################################################################
        {
            //==============================================================
            //일반폰트//
            pen   = ::CreatePen(PS_SOLID, 1, cPenColor);
            ::SelectObject(hdc, pen);
            int oldro = ::SetROP2(hdc, R2_COPYPEN);
            ::SetBkMode(hdc, TRANSPARENT);
            ::SetTextColor(hdc, cPenColor);
            IMGSCREEN2->Canvas->Brush->Color    = clWhite;
            //==============================================================

			//==============================================================
			asData			= "";//한 셀 포함 문자//
			asCaption   	= "";//TextOut에 표기할 문자//
			asTemp         	= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen     	= 0;
			nTextW        	= 0;
			nTextH        	= 0;
			nStartW        	= 0;
			nStartH        	= 0;
			nSumH        	= 0;
			nPartSharp1    	= 0;
			nPartSharp2    	= 0;
			nAllSharp1      = 0;
			nAllSharp2      = 0;
			nAllSharpLeft	= 0;
			//위에서 한번 초기화//eData->m_vSharpPos.clear();
			//==============================================================

			bAllSharp    = false;
            bPartSharp    = false;

               //==============================================================
            int        nComment        = 0;
			bool    bComment        = 0;
            TStringList *slComment         = new TStringList;
            slComment    = new TStringList();
            slComment->Text = "";
            slComment->Clear();
            //==============================================================

            //==========================================================================================
			tPoint  = m_bsAlphaDoc8[9].tPoint;
			tScale  = m_bsAlphaDoc8[9].tScale;
			nTextW	= IMGSCREEN2->Canvas->TextWidth("사")/*+1*/;//임의글자로 체크//
			nTextH  = IMGSCREEN2->Canvas->TextHeight("사")+1;//임의글자로 체크//
            //==========================================================================================

            for( int i = 0; i < (int)eData->m_vOWNINFOREASON.size(); i++)
            {
                asData = eData->m_vOWNINFOREASON[i].DATA;

                if(asData == "-")//NoData
                    continue;

				asData    = StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);
                asData    = StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
                //asData    = StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
                //asData    = StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);


				//=====================================================
				//소유권이전, 소유권보존 자동개행처리//
                AnsiString  asTmp1    = "";
				AnsiString  asTmp2    = "";
                for(int r = 0; r < (int)frmMain->m_vREASONDATA.size(); r++)
                {
                    asTmp1    = frmMain->m_vREASONDATA[r].DATA;
                    asTmp2    = StringReplace(asTmp1, "_", "", TReplaceFlags() << rfReplaceAll);
                    asTmp2    = StringReplace(asTmp2, " ", "", TReplaceFlags() << rfReplaceAll);//2112080//사고란에는 특정데이터(eData->m_vREASONDATA)를 제외하고는 공백처리하지 않음//
                    if(asData.AnsiPos(asTmp2))
                    {
                        asData    = StringReplace(asData, asTmp2, asTmp1, TReplaceFlags() << rfReplaceAll);
                    }
                }
                //=====================================================


                //=====================================================
                if(asData.SubString(1, 1) == "#")//전체삭제//
                {
                    bAllSharp    = true;
                    asData    = asData.Delete(1, 1);
                }
                else
                {
                    bAllSharp    = false;
                }

                if(asData.SubString(1, 1) == "%" && asData.SubString(asData.Length(), 1) == "%")//전체삭제를 부분삭제로 입력//
                {
                    //=================================================================================
                    //211229//
                    asTemp    = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
                    if(asTemp.Length() < 20)
                    {
                    	bAllSharp    = true;
                    	asData    = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					}
                    //=================================================================================
                }
                else
                {
                    bAllSharp    = false;
                }
                //=====================================================



				//---
                nTxtLen = asData.Length();
                nSumH    = 0;

                TStringList *slData         = new TStringList;
                slData    = new TStringList();

                //개행없는 데이터 처리//
                int nLineTxtLen    = 0;//Cell 높이와 nTextH로 한줄 글자 수 계산//
                int nLineTxtCnt    = 0;//한글과 숫자 Length()가 다르게 나오기 때문에 정확한 개행 길이만큼 계산이 안되서 사용//
				if(slData->Count == 0 && nTextW > 0)
                {
                    nLineTxtLen    = tScale.h/nTextW;
                    asTemp    = "";

                    //=================================================================================
                    //주석처리//
                    //211229//
                    asTemp    = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
                    if(asTemp.Length() >= 20)
                    //211229//if(asData.Length() >= 20)//asData.Pos("법률") > 0 || asData.Pos("분배농지") > 0)
                    {
                        asTemp    = "";//211229//

                        bComment    = true;
                        if(nComment == 0)
							asTemp     = "⑴";
						else if(nComment == 1)
							asTemp     = "⑵";
						else if(nComment == 2)
							asTemp     = "⑶";
						else if(nComment == 3)
							asTemp     = "⑷";
                        else if(nComment == 4)
                            asTemp     = "⑸";
                        asData     = asTemp + asData;
                        slData->Add("하단기재");//211216//도청김훈곤주무관Req//주석:하단기재//41023.628
                        //211201//#11//주석 취소선 적용//asData    = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
                        asData    = StringReplace(asData, "_", "", TReplaceFlags() << rfReplaceAll);
						asData    = StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);//2112080//사고란에는 특정데이터(eData->m_vREASONDATA)를 제외하고는 공백처리하지 않음//
                        slComment->Add(asData);
                        slData->Add(asTemp);
                        nComment++;
                    }
                    //=================================================================================
                    else//일반적인 데이터//
                    {
                        //개행 문자에 따른 줄바꿈기능//
                        int nPos    = asData.Pos("_");
                        while(nPos > 0)
                        {
                            asTemp     = asData.SubString(1, nPos-1);
                            slData->Add(asTemp);
                            asData  = asData.Delete(1, nPos);
                            nPos    = asData.Pos("_");
                        }
                        if( !asData.IsEmpty() )
							slData->Add(asData);

                        //길이에 따른 자동줄바꿈기능//
    //                    for(int j = 0; j < nTxtLen; j++)
    //                    {
    //                        if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
    //                        {
    //                            asTemp = asTemp    + asData.SubString(j+1, 2);
    //                            if(nLineTxtCnt >= nLineTxtLen-1)
    //                            {
    //                                slData->Add(asTemp);
	//                                asTemp    = "";
    //                                nLineTxtCnt    = 0;
    //                            }
    //                            else
    //                            {
    //                                nLineTxtCnt++;
    //                            }
    //                            j++;
    //                        }
    //                        else
    //                        {
	//                            if(asData.c_str()[j] == '%')//부분삭제//
    //                                continue;
    //                            asTemp = asTemp + asData.SubString(j+1, 1);
    //                            if(nLineTxtCnt >= nLineTxtLen-1)
    //                            {
    //                                slData->Add(asTemp);
    //                                asTemp    = "";
    //                                nLineTxtCnt    = 0;
    //                            }
    //                            else
    //                            {
    //                                nLineTxtCnt++;
	//                            }
    //                        }
    //                    }
    //                    if( !asTemp.IsEmpty() )
    //                    {
    //                        slData->Add(asTemp);
	//                        asTemp    = "";
	//                    }
                    }
                }
                //=========================================================

                //======================================
				//실제표시//
				//211228//보정//32028.230//31039.18.1
                if(i == 10)
                    nStartW    = tPoint.x - (i-1)*tScale.w - 20 - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
                else if(i == 23)
					nStartW    = tPoint.x - (i-1)*tScale.w - 12 - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
                else
                nStartW    = tPoint.x - (i-1)*tScale.w - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
                if(i%2)//95/2를 보정하기 위함//
                    nStartW    -= 1;
                //======================================
                if(i >= 11)
                    nStartW    -= (nMiddleWidth + 31);//HERE!!!
                //======================================


                for(int z = 0; z < slData->Count; z++)
                {
                    asData    = slData->Strings[z];

                    nTxtLen = asData.Length();

					//=========================================================
                    //Height 계산//
                    int nSumHeight    = 0;
                    asTemp    = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
                    for(int j = 0; j < asTemp.Length(); j++)
                    {
                        if( (asTemp.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asCaption = asTemp.SubString(j+1, 2);
                            nSumHeight    += IMGSCREEN2->Canvas->TextHeight(asCaption);
                            j++;
                        }
                        else
                        {
                            asCaption = asTemp.SubString(j+1, 1);
                            nSumHeight    += IMGSCREEN2->Canvas->TextHeight(asCaption);
                        }
                    }
                    //=========================================================

					//=========================================================
					nStartW    -= nTextW;
                    nStartH    = tPoint.y + (tScale.h - nSumHeight) / 2;//세로쓰기-중간//
                    //=========================================================

                    if(bAllSharp)//전체삭제//
                        nAllSharp1    = nStartH;

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(시작)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp1    = nStartH;
					}
					//=========================================================

					//=========================================================
                    for(int j = 0; j < nTxtLen; j++)
					{
                        if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asCaption = asData.SubString(j+1, 2);
							IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
                            j++;

//241204//PlanToDelete//세로쓰기 취소선 처리//
//							//=========================================================
//							//minji@230201//[해결]%소유권이전%_성변경 => 처리 시 '이전'에만 취소선이 표시되는 문제 수정//
//							if(bPartSharp && j == nTxtLen-1)//세로쓰기 취소선 처리(종료)//
//							{
//								nPartSharp2    = nStartH-1;
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
//								tempData.tpSTT.x    = nStartW + nTextW/2;
//								tempData.tpSTT.y    = nPartSharp1;
//								tempData.tpEND.x    = nStartW + nTextW/2;
//								tempData.tpEND.y    = nPartSharp2 + nTextH;
//								eData->m_vSharpPos.push_back(tempData);
//								//여기선 flag해제하면 안됨//
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							}
//							//=========================================================
						}
                        else
                        {
							if(!bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(시작)//
							{
                                bPartSharp    = true;
								nPartSharp1    = nStartH;
                                continue;
                            }
							else if(bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(종료)//
							{
                                nPartSharp2    = nStartH-1;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                                tempData.tpSTT.x    = nStartW + nTextW/2;
								tempData.tpSTT.y    = nPartSharp1;
                                tempData.tpEND.x    = nStartW + nTextW/2;
                                tempData.tpEND.y    = nPartSharp2;
                                eData->m_vSharpPos.push_back(tempData);
                                bPartSharp    = false;
                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                continue;
                            }
//241204//PlanToDelete//세로쓰기 취소선 처리//
//							else if(bPartSharp && j == 0)//세로쓰기 부분삭제 중 개행 후 시작지점//
//                            {
//                                nPartSharp1    = nStartH;
//                                continue;
//                            }
//                            else if(bPartSharp && j == nTxtLen-1)//세로쓰기 부분삭제 중 개행 전 종료지점//
//                            {
//                                nPartSharp2    = nStartH-1;
//                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
//                                tempData.tpSTT.x    = nStartW + nTextW/2;
//                                tempData.tpSTT.y    = nPartSharp1;
//								tempData.tpEND.x    = nStartW + nTextW/2;
//                                tempData.tpEND.y    = nPartSharp2;
//                                eData->m_vSharpPos.push_back(tempData);
//                                //여기선 flag해제하면 안됨//
//                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                continue;
//                            }

                            asCaption = asData.SubString(j+1, 1);
                            IMGSCREEN2->Canvas->TextOutA(nStartW+m_nNumberL, nStartH, asCaption);
                        }

                        nStartH    += nTextH;
                    }

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(종료)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x    = nStartW + nTextW/2;
						tempData.tpSTT.y    = nPartSharp1;
						tempData.tpEND.x    = nStartW + nTextW/2;
						tempData.tpEND.y    = nPartSharp2;
						eData->m_vSharpPos.push_back(tempData);
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
					//=========================================================

					//220126//TEST//if(slComment->Count == 0)//211229//25031.36//%소유권이전_성명경정%
                    {
						//전체삭제//
                        if(bAllSharp)
						{
							nAllSharp2    = nStartH-1;
                            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                            tempData.tpSTT.x    = nStartW + nTextW/2;
                            tempData.tpSTT.y    = nAllSharp1;
                            tempData.tpEND.x    = nStartW + nTextW/2;
                            tempData.tpEND.y    = nAllSharp2;
							eData->m_vSharpPos.push_back(tempData);
                            //bAllSharp    = false;
                            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                        }
                    }
                }

                delete slData;
                slData    = NULL;
            }

            //======================================================
            // 주석표시//
            int nCommentTextH    = 0;
            bool    bCommentAllSharp    = false;
            bool    bCommentPartSharp    = false;
            for(int m = 0; m < slComment->Count; m++)
            {
                asCaption        = slComment->Strings[m];

                if(asCaption.SubString(1, 1) == "#")//전체삭제//
                {
                    bCommentAllSharp    = true;
                    asData    = asCaption.Delete(1, 1);
                }
                else
                {
                    bCommentAllSharp    = false;
                }

                //211229//25031.36//%소유권이전_성명경정%
                if(asData.SubString(1, 1) == "%" && asData.SubString(asData.Length(), 1) == "%")//전체삭제를 부분삭제로 입력//
                {
                    bCommentAllSharp    = true;
                    asData    = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
                }
                else
                {
                    bCommentAllSharp    = false;
                }
                //======================================================
                //211201//#11//주석 취소선 적용//하단 표시로 위치가 REASON가 달라서 [11]로 표시하니 지우면 안 됨//
                int nCommentTextLen    = asCaption.Length();
				TPoint tempPoint    = m_bsAlphaDoc8[11].tPoint;
                TScale tempScale    = m_bsAlphaDoc8[11].tScale;
                int nCommentW    = tempPoint.x-10*tempScale.w;
                int nCommentH    = tempPoint.y+tempScale.h+14+m*nCommentTextH;
                int nPosSharp1    = 0;
                int nPosSharp2    = 0;
                bCommentPartSharp    = false;
                for(int n = 0; n < nCommentTextLen; n++)
                {
                    if(!bCommentPartSharp && asCaption.c_str()[n] =='%')//가로쓰기 부분삭제 시작지점//
					{
                        nPosSharp1    = n+1;
                        bCommentPartSharp    = true;
                        nPartSharp1    = nCommentW + nTextW-1;
                        continue;
					}
                    else if(bCommentPartSharp && asCaption.c_str()[n] =='%')//가로쓰기 부분삭제 종료지점//
                    {
                        nPosSharp2    = n;

                        AnsiString  asTemp    = asCaption.SubString(nPosSharp1+1, nPosSharp2-nPosSharp1);
                        nPartSharp2        = nCommentW + IMGSCREEN2->Canvas->TextWidth(asTemp) + asTemp.Length();
                        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                        memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                        tempData.tpSTT.x    = nPartSharp1;
                        tempData.tpSTT.y    = nCommentH + nTextH/2;
                        tempData.tpEND.x    = nPartSharp2;
                        tempData.tpEND.y    = nCommentH + nTextH/2;
                        eData->m_vSharpPos.push_back(tempData);
                        bCommentPartSharp    = false;
                        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                        continue;
                    }
                }
                //comment---
                if(bCommentAllSharp)//211208//
                {
                    memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                    tempData.tpSTT.x    = nStartW + nTextW/2;
                    tempData.tpSTT.y    = nAllSharp1;
                    tempData.tpEND.x    = nStartW + nTextW/2;
                    tempData.tpEND.y    = nAllSharp2;
                    eData->m_vSharpPos.push_back(tempData);
                    //bAllSharp    = false;
				}
                //======================================================

                asCaption    = StringReplace(asCaption, "%", "", TReplaceFlags() << rfReplaceAll);
                nCommentTextH    = IMGSCREEN2->Canvas->TextHeight(asCaption)+1;
                IMGSCREEN2->Canvas->TextOutA(tempPoint.x-10*tempScale.w, tempPoint.y+tempScale.h+14+m*nCommentTextH, asCaption);
            }
            delete slComment;
            slComment    = NULL;
            //======================================================

            ::SetROP2 (hdc, oldro);
            ::DeleteObject( pen );
        }



        //##########################################################################################
        //#
        //# ADDRESS
        //#
        //##########################################################################################
        {
            //==============================================================
            //일반폰트//
            pen   = ::CreatePen(PS_SOLID, 1, cPenColor);
            ::SelectObject(hdc, pen);
            int oldro = ::SetROP2(hdc, R2_COPYPEN);
            ::SetBkMode(hdc, TRANSPARENT);
			::SetTextColor(hdc, cPenColor);
            IMGSCREEN2->Canvas->Brush->Color    = clWhite;
            //==============================================================

			//==============================================================
			asData			= "";//한 셀 포함 문자//
			asCaption   	= "";//TextOut에 표기할 문자//
			asTemp         	= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen     	= 0;
			nTextW        	= 0;
			nTextH        	= 0;
			nStartW        	= 0;
			nStartH        	= 0;
			nSumH        	= 0;
			nPartSharp1    	= 0;
			nPartSharp2    	= 0;
			nAllSharp1      = 0;
			nAllSharp2      = 0;
			nAllSharpLeft	= 0;
			//위에서 한번 초기화//eData->m_vSharpPos.clear();
			//==============================================================

			bAllSharp	= false;
			bPartSharp  = false;
			bEven		= true;//close상태//

            //==========================================================================================
			tPoint  = m_bsAlphaDoc8[10].tPoint;
			tScale  = m_bsAlphaDoc8[10].tScale;
			nTextW	= IMGSCREEN2->Canvas->TextWidth("주")/*+1*/;//임의글자로 체크//
			nTextH  = IMGSCREEN2->Canvas->TextHeight("주")+1;//임의글자로 체크//
            //==========================================================================================

            for( int i = 0; i < (int)eData->m_vOWNINFOADDRESS.size(); i++)
            {
                asData = eData->m_vOWNINFOADDRESS[i].DATA;

                if(asData == "-")//NoData
                    continue;

				asData    = StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);
				asData    = StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
                //=========================================================
                //211201//#6//주소에서 괄호삭제 기능 제거//41026.1.186.2
    //            asData    = StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
    //            asData    = StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);
                //=========================================================


                //=====================================================
                if(asData.SubString(1, 1) == "#")//전체삭제//
                {
                    bAllSharp    = true;
                    asData    = asData.Delete(1, 1);
                }
                else
                {
                    bAllSharp    = false;
                }

                if(asData.SubString(1, 1) == "%" && asData.SubString(asData.Length(), 1) == "%")//전체삭제를 부분삭제로 입력//
                {
                    bAllSharp    = true;
                    asData    = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
                }
                else
                {
                    bAllSharp    = false;
                }
                //=====================================================

                //---
                nTxtLen = asData.Length();
                nSumH    = 0;

				TStringList *slData         = new TStringList;
				slData    = new TStringList();

                //개행없는 데이터 처리//
                int nLineTxtLen    = 0;//Cell 높이와 nTextH로 한줄 글자 수 계산//
                int nLineTxtCnt    = 0;//한글과 숫자 Length()가 다르게 나오기 때문에 정확한 개행 길이만큼 계산이 안되서 사용//
                if(slData->Count == 0 && nTextW > 0)
                {
                    nLineTxtLen    = tScale.h/nTextW;
                    asTemp    = "";

                    for(int j = 0; j < nTxtLen; j++)
                    {
                        if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asTemp = asTemp    + asData.SubString(j+1, 2);
                            if(nLineTxtCnt >= nLineTxtLen-1)
                            {
                                slData->Add(asTemp);
                                asTemp    = "";
                                nLineTxtCnt    = 0;
                            }
                            else
                            {
								nLineTxtCnt++;//231215//ReturnCode//세로쓰기는한글2글자로체킹할필요없다.//231117//++ -> += 2
                            }
                            j++;
                        }
                        else
                        {
							//========================================================
                            //211201//#4//주소 개행('_')
                            if(asData.c_str()[j] == '_')
                            {
								if( !asTemp.IsEmpty() )//211208//31025.2.20.2//주소개행과 길이자동개행이 복합//
                                {
                                    slData->Add(asTemp);
                                    asTemp    = "";
                                    nLineTxtCnt    = 0;
                                }
                            }
                            else
                            {
                                //========================================================
                                //211201//#8//주소 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
								if(asData.c_str()[j] == '%')
                                {
									bEven	= !bEven;//241203//
									nLineTxtLen    = nLineTxtLen + 1;
                                }
                                //========================================================
                                asTemp = asTemp + asData.SubString(j+1, 1);
                                if(nLineTxtCnt >= nLineTxtLen-1)
                                {
                                    //========================================================
                                    //211201//#8//주소 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
									if( !bEven )//241203//
									{
										if(asData.c_str()[j+1] == '%')
										{
											bEven	= !bEven;//241203//
											nLineTxtLen    = nLineTxtLen + 1;
											asTemp = asTemp + asData.SubString(j+2, 1);
											j++;
										}
									}
                                    //========================================================
                                    slData->Add(asTemp);
                                    asTemp    = "";
                                    nLineTxtCnt    = 0;
                                }
                                else
                                {
									nLineTxtCnt++;
                                }
                            }
                        }
                    }
                    if( !asTemp.IsEmpty() )
                    {
                        slData->Add(asTemp);
                        asTemp    = "";
                    }
                }
                //=========================================================

                //======================================
				//실제표시//
				//211228//보정//32028.230//31039.18.1
                if(i == 10)
                    nStartW    = tPoint.x - (i-1)*tScale.w - 20 - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
                else if(i == 23)
                    nStartW    = tPoint.x - (i-1)*tScale.w - 12 - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
				else
                nStartW    = tPoint.x - (i-1)*tScale.w - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
                if(i%2)//95/2를 보정하기 위함//
                    nStartW    -= 1;
                //======================================
                if(i >= 11)
                    nStartW    -= (nMiddleWidth + 31);//HERE!!!
                //=========================================================
                //220112//31039.18.1(부여두리)
                if(slData->Count == 4)
                    nStartW -= 2;

                for(int z = 0; z < slData->Count; z++)
                {
                    asData    = slData->Strings[z];

                    nTxtLen = asData.Length();

					//=========================================================
					nStartW    -= nTextW;
                    nStartH    = tPoint.y;//세로쓰기-상단//
					//=========================================================

                    if(bAllSharp)//전체삭제//
                        nAllSharp1    = nStartH;

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(시작)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp1    = nStartH;
					}
					//=========================================================

					//=========================================================
                    for(int j = 0; j < nTxtLen; j++)
                    {
                        if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
                            asCaption = asData.SubString(j+1, 2);
                            IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
                            j++;

//241204//PlanToDelete//세로쓰기 취소선 처리//
//							if(bPartSharp && j == 1)//세로쓰기 부분삭제 중 개행 후 시작지점//211201//#9//한글이라 2byte이므로 j==1로 체크//
//                            {
//                                nPartSharp1    = nStartH;
//                                nStartH    += nTextH;//211208
//                                continue;
//                            }
//                            else if(bPartSharp && j == nTxtLen-1)//세로쓰기 부분삭제 중 개행 전 종료지점//
//                            {
//                                nPartSharp2    = nStartH+nTextH-1;
//                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
//                                tempData.tpSTT.x    = nStartW + nTextW/2;
//								tempData.tpSTT.y    = nPartSharp1;
//                                tempData.tpEND.x    = nStartW + nTextW/2;
//								tempData.tpEND.y    = nPartSharp2;
//                                eData->m_vSharpPos.push_back(tempData);
//                                //여기선 flag해제하면 안됨//
//                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                continue;
//                            }
                        }
                        else
                        {
							if(!bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(시작)//
							{
                                bPartSharp    = true;
                                nPartSharp1    = nStartH;
                                continue;
                            }
							else if(bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(종료)//
                            {
                                nPartSharp2    = nStartH-1;
                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                                tempData.tpSTT.x    = nStartW + nTextW/2;
								tempData.tpSTT.y    = nPartSharp1;
                                tempData.tpEND.x    = nStartW + nTextW/2;
                                tempData.tpEND.y    = nPartSharp2;
                                eData->m_vSharpPos.push_back(tempData);
                                bPartSharp    = false;
                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                continue;
                            }
//241204//PlanToDelete//세로쓰기 취소선 처리//
//							else if(bPartSharp && j == 0)//세로쓰기 부분삭제 중 개행 후 시작지점//
//                            {
//                                nPartSharp1    = nStartH;
//                                //시작지점에 문자는 출력해야죠.//continue;
//                            }
//							else if(bPartSharp && j == nTxtLen-1)//세로쓰기 부분삭제 중 개행 전 종료지점//
//                            {
//                                nPartSharp2    = nStartH-1;
//                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
//								tempData.tpSTT.x    = nStartW + nTextW/2;
//                                tempData.tpSTT.y    = nPartSharp1;
//                                tempData.tpEND.x    = nStartW + nTextW/2;
//                                tempData.tpEND.y    = nPartSharp2;
//                                eData->m_vSharpPos.push_back(tempData);
//                                //여기선 flag해제하면 안됨//
//                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                continue;
//                            }

                            asCaption = asData.SubString(j+1, 1);
                            IMGSCREEN2->Canvas->TextOutA(nStartW+m_nNumberL, nStartH, asCaption);
                        }

                        nStartH    += nTextH;
                    }

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(종료)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x    = nStartW + nTextW/2;
						tempData.tpSTT.y    = nPartSharp1;
						tempData.tpEND.x    = nStartW + nTextW/2;
						tempData.tpEND.y    = nPartSharp2;
						eData->m_vSharpPos.push_back(tempData);
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
					//=========================================================

					//전체삭제-취소선//
                    if(bAllSharp)
                    {
						nAllSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                        tempData.tpSTT.x    = nStartW + nTextW/2;
                        tempData.tpSTT.y    = nAllSharp1;
                        tempData.tpEND.x    = nStartW + nTextW/2;
                        tempData.tpEND.y    = nAllSharp2;
						eData->m_vSharpPos.push_back(tempData);
						//bAllSharp    = false;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
				}

                delete slData;
                slData    = NULL;
            }

            ::SetROP2 (hdc, oldro);
            ::DeleteObject( pen );
        }



        //##########################################################################################
        //#
        //# NAME
        //#
        //##########################################################################################
        {
            //==============================================================
            //일반폰트//
            pen   = ::CreatePen(PS_SOLID, 1, cPenColor);
            ::SelectObject(hdc, pen);
            int oldro = ::SetROP2(hdc, R2_COPYPEN);
            ::SetBkMode(hdc, TRANSPARENT);
            ::SetTextColor(hdc, cPenColor);
			IMGSCREEN2->Canvas->Brush->Color    = clWhite;
            //==============================================================

			//==============================================================
			asData			= "";//한 셀 포함 문자//
			asCaption   	= "";//TextOut에 표기할 문자//
			asTemp         	= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen     	= 0;
			nTextW        	= 0;
			nTextH        	= 0;
			nStartW        	= 0;
			nStartH        	= 0;
			nSumH        	= 0;
			nPartSharp1    	= 0;
			nPartSharp2    	= 0;
			nAllSharp1      = 0;
			nAllSharp2      = 0;
			nAllSharpLeft	= 0;
			//위에서 한번 초기화//eData->m_vSharpPos.clear();
			//==============================================================

			bAllSharp	= false;
            bPartSharp  = false;
			bEven		= true;//close상태//

            //==========================================================================================
			tPoint  = m_bsAlphaDoc8[11].tPoint;
			tScale  = m_bsAlphaDoc8[11].tScale;
			nTextW	= IMGSCREEN2->Canvas->TextWidth("이")/*+1*/;//임의글자로 체크//
			nTextH  = IMGSCREEN2->Canvas->TextHeight("이")+1;//임의글자로 체크//
            //==========================================================================================

            for( int i = 0; i < (int)eData->m_vOWNINFONAME.size(); i++)
            {
                asData = eData->m_vOWNINFONAME[i].DATA;

                if(asData == "-")//NoData
                    continue;

				asData = eFunc->funcStringReplaceDoc08(asData);//260518//
				//=====================================================
                if(asData.SubString(1, 1) == "#")//전체삭제//
                {
					bAllSharp	= true;
                    asData    	= asData.Delete(1, 1);
                }
                else
                {
					bAllSharp    = false;
                }
                //=====================================================

                //---
                nTxtLen = asData.Length();
                nSumH    = 0;

                TStringList *slData         = new TStringList;
                slData    = new TStringList();

                //개행없는 데이터 처리//
                int nLineTxtLen    = 0;//Cell 높이와 nTextH로 한줄 글자 수 계산//
                int nLineTxtCnt    = 0;//한글과 숫자 Length()가 다르게 나오기 때문에 정확한 개행 길이만큼 계산이 안되서 사용//
                if(slData->Count == 0 && nTextW > 0)
                {
                    nLineTxtLen    = tScale.h/nTextW;
                    asTemp    = "";

                    for(int j = 0; j < nTxtLen; j++)
					{
                        if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asTemp = asTemp    + asData.SubString(j+1, 2);
                            if(nLineTxtCnt >= nLineTxtLen-1)
                            {
                                slData->Add(asTemp);
                                asTemp    = "";
                                nLineTxtCnt    = 0;
                            }
                            else
                            {
								nLineTxtCnt++;//231215//ReturnCode//세로쓰기는한글2글자로체킹할필요없다.//231117//++ -> += 2
                            }
                            j++;
                        }
                        else
                        {
                            //================================================
                            //211201//#14//
                            //개행 문자에 따른 줄바꿈기능//
                            //========================================================
                            //211201//#4//주소 개행('_')
                            if(asData.c_str()[j] == '_')
                            {
                                slData->Add(asTemp);
                                asTemp    = "";
                                nLineTxtCnt    = 0;
                            }
                            else
                            //========================================================
                            {
                                //========================================================
                                //211201//#8//이름 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
								if(asData.c_str()[j] == '%')
                                {
									bEven	= !bEven;//241203//
									nLineTxtLen    = nLineTxtLen + 1;
                                }
                                //========================================================

                                //211101//
        //                        if(asData.c_str()[j] == '%')//부분삭제//
        //                            continue;
                                asTemp = asTemp + asData.SubString(j+1, 1);
                                if(nLineTxtCnt >= nLineTxtLen-1)
                                {
                                    //========================================================
                                    //211201//#8//이름 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
									if( !bEven )//241203//
									{
										if(asData.c_str()[j+1] == '%')
										{
											bEven	= !bEven;//241203//
											nLineTxtLen    = nLineTxtLen + 1;
											asTemp = asTemp + asData.SubString(j+2, 1);
											j++;
										}
									}
									//========================================================
                                    slData->Add(asTemp);
                                    asTemp    = "";
                                    nLineTxtCnt    = 0;
                                }
                                else
                                {
									nLineTxtCnt++;
                                }
                            }
                            //================================================
    //                        //길이에 따른 자동줄바꿈기능//
    //                        //211101//
    ////                        if(asData.c_str()[j] == '%')//부분삭제//
	////                            continue;
    //                        asTemp = asTemp + asData.SubString(j+1, 1);
    //                        if(nLineTxtCnt >= nLineTxtLen-1)
    //                        {
    //                            slData->Add(asTemp);
    //                            asTemp    = "";
    //                            nLineTxtCnt    = 0;
    //                        }
    //                        else
    //                        {
    //                            nLineTxtCnt++;
    //                        }
                        }
                    }
                    if( !asTemp.IsEmpty() )
                    {
                        slData->Add(asTemp);
                        asTemp    = "";
                    }
                }
                //=========================================================

				//======================================
				//실제 표시//
				//211228//보정//32028.230//31039.18.1
				if(i == 10)
                    nStartW    = tPoint.x - (i-1)*tScale.w - 20 - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
                else if(i == 23)
                    nStartW    = tPoint.x - (i-1)*tScale.w - 12 - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
                else
                nStartW    = tPoint.x - (i-1)*tScale.w - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
                if(i%2)//95/2를 보정하기 위함//
                    nStartW    -= 1;
                //======================================
                if(i >= 11)
					nStartW    -= (nMiddleWidth + 31);
                //=========================================================

                for(int z = 0; z < slData->Count; z++)
                {
                    asData    = slData->Strings[z];

                    nTxtLen = asData.Length();

                    //=========================================================
                    //Height 계산//
                    int nSumHeight    = 0;
                    asTemp    = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
                    for(int j = 0; j < asTemp.Length(); j++)
                    {
                        if( (asTemp.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asCaption = asTemp.SubString(j+1, 2);
                            nSumHeight    += IMGSCREEN2->Canvas->TextHeight(asCaption);
                            j++;
                        }
                        else
                        {
                            asCaption = asTemp.SubString(j+1, 1);
                            nSumHeight    += IMGSCREEN2->Canvas->TextHeight(asCaption);
                        }
                    }
					//=========================================================

					//=========================================================
					nStartW    -= nTextW;
                    nStartH    = tPoint.y + (tScale.h - nSumHeight) / 2;//세로쓰기-중간//
                    //=========================================================

					if(bAllSharp)//전체삭제//
                        nAllSharp1    = nStartH;

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(시작)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp1    = nStartH;
					}
					//=========================================================

					//=========================================================
                    for(int j = 0; j < nTxtLen; j++)
                    {
                        if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asCaption = asData.SubString(j+1, 2);
                            IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
                            j++;

//241204//PlanToDelete//세로쓰기 취소선 처리//
//							if(bPartSharp && j == 1)//세로쓰기 부분삭제 중 개행 후 시작지점//211201//#9//41026.1.75//한글이라 2byte이므로 j==1로 체크//
//                            {
//                                nPartSharp1    = nStartH;
//                                nStartH    += nTextH;//211208
//                                continue;
//                            }
//                            else if(bPartSharp && j == nTxtLen-1)//세로쓰기 부분삭제 중 개행 전 종료지점//
//                            {
//                                nPartSharp2    = nStartH+nTextH-1;
//                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
//                                tempData.tpSTT.x    = nStartW + nTextW/2;
//								tempData.tpSTT.y    = nPartSharp1;
//                                tempData.tpEND.x    = nStartW + nTextW/2;
//                                tempData.tpEND.y    = nPartSharp2;
//                                eData->m_vSharpPos.push_back(tempData);
//                                //여기선 flag해제하면 안됨//
//                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                continue;
//                            }
                        }
                        else
						{
							if(!bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(시작)//
							{
                                bPartSharp    = true;
                                nPartSharp1    = nStartH;
                                continue;
                            }
							else if(bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(종료)//
                            {
                                nPartSharp2    = nStartH-1;
                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                                tempData.tpSTT.x    = nStartW + nTextW/2;
								tempData.tpSTT.y    = nPartSharp1;
                                tempData.tpEND.x    = nStartW + nTextW/2;
                                tempData.tpEND.y    = nPartSharp2;
                                eData->m_vSharpPos.push_back(tempData);
                                bPartSharp    = false;
                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                continue;
                            }
//241204//PlanToDelete//세로쓰기 취소선 처리//
//							else if(bPartSharp && j == 0)//세로쓰기 부분삭제 중 개행 후 시작지점//
//							{
//								nPartSharp1    = nStartH;
//								continue;
//							}
//							else if(bPartSharp && j == nTxtLen-1)//세로쓰기 부분삭제 중 개행 후 종료지점//
//							{
//								nPartSharp2    = nStartH-1;
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
//								tempData.tpSTT.x    = nStartW + nTextW/2;
//								tempData.tpSTT.y    = nPartSharp1;
//								tempData.tpEND.x    = nStartW + nTextW/2;
//								tempData.tpEND.y    = nPartSharp2;
//								eData->m_vSharpPos.push_back(tempData);
//								//여기선 flag해제하면 안됨//
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								continue;
//							}

							asCaption = asData.SubString(j+1, 1);
							IMGSCREEN2->Canvas->TextOutA(nStartW+m_nNumberL, nStartH, asCaption);
						}

                        nStartH    += nTextH;
                    }

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(종료)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x    = nStartW + nTextW/2;
						tempData.tpSTT.y    = nPartSharp1;
						tempData.tpEND.x    = nStartW + nTextW/2;
						tempData.tpEND.y    = nPartSharp2;
						eData->m_vSharpPos.push_back(tempData);
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
					//=========================================================

					//전체삭제-취소선//
					if(bAllSharp)
                    {
						nAllSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                        tempData.tpSTT.x    = nStartW + nTextW/2;
                        tempData.tpSTT.y    = nAllSharp1;
                        tempData.tpEND.x    = nStartW + nTextW/2;
                        tempData.tpEND.y    = nAllSharp2;
                        eData->m_vSharpPos.push_back(tempData);
						//bAllSharp    = false;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
				}

                delete slData;
				slData    = NULL;
			}

            ::SetROP2 (hdc, oldro);
			::DeleteObject( pen );
		}



        //####################################################################################
        //Sharp
        //####################################################################################
        {
		    //------------------
            //일반폰트//
			penSharp   = ::CreatePen(PS_SOLID, frmMain->m_nSharpWidthPrint, cPenColorSharp);//HERE!!!
			::SelectObject(hdc, penSharp);
            int oldro1 = ::SetROP2(hdc, R2_COPYPEN);
            ::SetBkMode(hdc, TRANSPARENT);
            ::SetTextColor(hdc, cPenColorSharp);
			IMGSCREEN2->Canvas->Brush->Color    = clWhite;
            //------------------
            TPoint tpStt, tpEnd;
            for(int i = 0; i < (int)eData->m_vSharpPos.size(); i++)
            {
                tpStt    = eData->m_vSharpPos[i].tpSTT;
                tpEnd    = eData->m_vSharpPos[i].tpEND;
				::MoveToEx(hdc, tpStt.x, tpStt.y, NULL);
				::LineTo(hdc, tpEnd.x, tpEnd.y);
            }

			::SetROP2 (hdc, oldro1);
            ::DeleteObject( penSharp );
        }

		::SelectObject(hdc, hOldFont);
        ::DeleteObject(m_font);
        //####################################################################################
    }
}
//---------------------------------------------------------------------------







//=================================================================
//부책:구대장 [인쇄화면] 항목별 위치//
//=================================================================
void __fastcall TfrmAlphaDoc8::funcGetPrintViewBoundary()
{
	AnsiString  asINIHeader = "HANGEUL_FORM_SUBBOOK";

	m_nHLeft		= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"H_LEFT", 4163);
	m_nOLeft		= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"O_LEFT", 4316);
	m_nHTop			= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"H_TOP", 344);
	m_nOTop			= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"O_TOP", 1986);
	m_nHWidth		= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"H_WIDTH", 319);
	m_nOWidth		= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"O_WIDTH", 171);

	//동리//
	m_bsAlphaDoc8[0].tPoint.x	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"0_L", 4635);
	m_bsAlphaDoc8[0].tPoint.y	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"0_T", 580);
	m_bsAlphaDoc8[0].tScale.w	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"0_W", 153);
	m_bsAlphaDoc8[0].tScale.h	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"0_H", 236);
	//지번//
	m_bsAlphaDoc8[1].tPoint.x	= m_bsAlphaDoc8[0].tPoint.x;
	m_bsAlphaDoc8[1].tPoint.y	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"1_T", 1029);
	m_bsAlphaDoc8[1].tScale.w	= m_bsAlphaDoc8[0].tScale.w;
	m_bsAlphaDoc8[1].tScale.h	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"1_H", 564);
	//적요//
	m_bsAlphaDoc8[2].tPoint.x	= m_bsAlphaDoc8[0].tPoint.x;
	m_bsAlphaDoc8[2].tPoint.y	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"2_T", 2494);
	m_bsAlphaDoc8[2].tScale.w	= m_bsAlphaDoc8[0].tScale.w;
	m_bsAlphaDoc8[2].tScale.h	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"2_H", 764);
	//HISTORY
	m_bsAlphaDoc8[3].tPoint.x	= m_nHLeft;
	m_bsAlphaDoc8[3].tPoint.y	= m_nHTop;
	m_bsAlphaDoc8[3].tScale.w	= m_nHWidth;
	m_bsAlphaDoc8[3].tScale.h	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"3_H", 236);
	m_bsAlphaDoc8[4].tPoint.x	= m_nHLeft;
	m_bsAlphaDoc8[4].tPoint.y	= m_bsAlphaDoc8[3].tPoint.y + m_bsAlphaDoc8[3].tScale.h;
	m_bsAlphaDoc8[4].tScale.w	= m_nHWidth;
	m_bsAlphaDoc8[4].tScale.h	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"4_H", 236);
	m_bsAlphaDoc8[5].tPoint.x	= m_nHLeft;
	m_bsAlphaDoc8[5].tPoint.y	= m_bsAlphaDoc8[4].tPoint.y + m_bsAlphaDoc8[4].tScale.h;
	m_bsAlphaDoc8[5].tScale.w	= m_nHWidth;
	m_bsAlphaDoc8[5].tScale.h	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"5_H", 214);
	m_bsAlphaDoc8[6].tPoint.x	= m_nHLeft;
	m_bsAlphaDoc8[6].tPoint.y	= m_bsAlphaDoc8[5].tPoint.y + m_bsAlphaDoc8[5].tScale.h;
	m_bsAlphaDoc8[6].tScale.w	= m_nHWidth;
	m_bsAlphaDoc8[6].tScale.h	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"6_H", 140);
	m_bsAlphaDoc8[7].tPoint.x	= m_nHLeft;
	m_bsAlphaDoc8[7].tPoint.y	= m_bsAlphaDoc8[6].tPoint.y + m_bsAlphaDoc8[6].tScale.h + 2;
	m_bsAlphaDoc8[7].tScale.w	= m_nHWidth;
	m_bsAlphaDoc8[7].tScale.h	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"7_H", 800);
	//OWNINFO
	m_bsAlphaDoc8[8].tPoint.x	= m_nOLeft;
	m_bsAlphaDoc8[8].tPoint.y	= m_nOTop;
	m_bsAlphaDoc8[8].tScale.w	= m_nOWidth;
	m_bsAlphaDoc8[8].tScale.h	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"8_H", 236);
	m_bsAlphaDoc8[9].tPoint.x	= m_nOLeft;
	m_bsAlphaDoc8[9].tPoint.y	= m_bsAlphaDoc8[8].tPoint.y + m_bsAlphaDoc8[8].tScale.h;
	m_bsAlphaDoc8[9].tScale.w	= m_nOWidth;
	m_bsAlphaDoc8[9].tScale.h	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"9_H", 236);
	m_bsAlphaDoc8[10].tPoint.x	= m_nOLeft;
	m_bsAlphaDoc8[10].tPoint.y	= m_bsAlphaDoc8[9].tPoint.y + m_bsAlphaDoc8[9].tScale.h + 3;
	m_bsAlphaDoc8[10].tScale.w	= m_nOWidth;
	m_bsAlphaDoc8[10].tScale.h	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"10_H", 425);
	m_bsAlphaDoc8[11].tPoint.x	= m_nOLeft;
	m_bsAlphaDoc8[11].tPoint.y	= m_bsAlphaDoc8[10].tPoint.y + m_bsAlphaDoc8[10].tScale.h + 1;
	m_bsAlphaDoc8[11].tScale.w	= m_nOWidth;
	m_bsAlphaDoc8[11].tScale.h	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"11_H", 375);
	//CAUTION
	m_bsAlphaDoc8[12].tPoint.x	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"12_L", 180);
	m_bsAlphaDoc8[12].tPoint.y	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"12_T", 3280);
	m_bsAlphaDoc8[12].tScale.w	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"12_W", 1000);
	m_bsAlphaDoc8[12].tScale.h	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"12_H", 30);

	//LEVEL//241203//#등급#추가//
	m_bsAlphaDoc8[13].tPoint.x	= m_bsAlphaDoc8[0].tPoint.x;
	m_bsAlphaDoc8[13].tPoint.y	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"13_T", 1806);
	m_bsAlphaDoc8[13].tScale.w	= m_bsAlphaDoc8[0].tScale.w;
	m_bsAlphaDoc8[13].tScale.h	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"13_H", 470);

	m_nMiddleWidth	= 154;//A3 이미지에서 사용할 중간-간격(172)//공유지연명부A.jpg참고//
	m_nNumberL		= 12;//221208//#PRINT_IMPROVE//
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaDoc8::funcMakeViewImageA3()
{
//221220//잘 동작하는 코드임//
//	//=================================
//	Graphics::TBitmap *printBmp = new Graphics::TBitmap();
//	printBmp->PixelFormat = pf32bit;
//	printBmp->Width 	= IMGSCREEN2->Width;
//	printBmp->Height 	= IMGSCREEN2->Height;
//	SetStretchBltMode(printBmp->Canvas->Handle, HALFTONE);
//	StretchBlt(printBmp->Canvas->Handle, 0, 0, printBmp->Width, printBmp->Height, IMGSCREEN2->Canvas->Handle, 0, 0, IMGSCREEN2->Width, IMGSCREEN2->Height, SRCCOPY);
//	::BitBlt(printBmp->Canvas->Handle, 0, 0, printBmp->Width, printBmp->Height, IMGSCREEN2->Canvas->Handle, 0, 0, SRCCOPY);
//
//	TJPEGImage	*saveJpg = new TJPEGImage();
//	saveJpg->CompressionQuality = 100;
//	saveJpg->Compress();
//	saveJpg->Assign(printBmp);
//	saveJpg->SaveToFile(frmMain->ROOTPATH + "test\\test.jpg");
//	delete saveJpg;
//	saveJpg = NULL;
//
//	delete printBmp;
//	printBmp	= NULL;
//	//=================================

	AnsiString  asPathName	= "";

	frmAlphaDoc8->m_asSavedFileName	= "";
	frmAlphaDoc8->m_asSavedFileName1	= "";
	frmAlphaDoc8->m_asSavedFileName2	= "";

	//============================================
	//확대축소를 위한 이미지 보관 폴더 삭제//
	AnsiString  asTempDir	= frmMain->ROOTPATH + "tmp2\\";
	if (!DirectoryExists(asTempDir))
		CreateDir(asTempDir);
	//============================================

	try{
		pbRect2->Invalidate();

		//---------------------------------
		// Image First (평)
		m_bAreaChange = false;
		funcLoadImage(frmAlphaDoc8->m_asBGFilePath);
		funcRedrawOwnInfo();
		asPathName	= asTempDir + "[부책]" + frmMain->m_asLandNm + "_열람1.jpg";
		frmAlphaDoc8->m_asSavedFileName1	= asPathName;
		if(FileExists(asPathName))
			DeleteFile(asPathName);
		IMGSCREEN2->Picture->SaveToFile(asPathName);
		//---------------------------------
		// Image Second (㎡)
		m_bAreaChange = true;
		funcLoadImage(frmAlphaDoc8->m_asBGFilePath);
		funcRedrawOwnInfo();
		asPathName	= asTempDir + "[부책]" + frmMain->m_asLandNm + "_열람2.jpg";
		frmAlphaDoc8->m_asSavedFileName2	= asPathName;
		IMGSCREEN2->Picture->SaveToFile(asPathName);
		m_bAreaChange = false;
		//---------------------------------
		//기본 (평)으로 표시//
		frmAlphaDoc8->m_asSavedFileName	= frmAlphaDoc8->m_asSavedFileName1;
	}
	__finally{
		pbRect2->Invalidate();
	}
}
//---------------------------------------------------------------------------

//=================================================================
//부책:공유지연명부 [인쇄화면] 항목별 위치//
//=================================================================
void __fastcall TfrmAlphaDoc8::funcGetPrintViewBoundaryShare()
{
	AnsiString  asINIHeader = "";

	if(frmMain->m_asFormatType == "A")
	{
		asINIHeader = "HANGEUL_FORM_SHAREOWN_A";
		//231116//부책, 공유지연명부A,B 에 따라 다르므로 funcSetBoundary, funcSetBoundaryShare()에서 설정//
		m_nMiddleWidth	= 173;//A3 이미지에서 사용할 중간-간격(172)//공유지연명부A.jpg참고//
		m_nOWidth		= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"WIDTH", m_nMiddleWidth);
	}
	else if(frmMain->m_asFormatType == "B")
	{
		asINIHeader = "HANGEUL_FORM_SHAREOWN_B";
		//231116//부책, 공유지연명부A,B 에 따라 다르므로 funcSetBoundary, funcSetBoundaryShare()에서 설정//
		m_nMiddleWidth	= 166;//A3 이미지에서 사용할 중간-간격(166)//공유지연명부B.jpg참고//
		m_nOWidth		= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"WIDTH", 165);
	}


//	m_nHLeft		= 4163;
	m_nOLeft		= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"LEFT", 4635);
//	m_nHTop			= 344;
	m_nOTop			= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"TOP", 344);
//	m_nHWidth		= 319;
//231116//FORMAT별로 상이하여 위에서 처리//	m_nOWidth		= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"WIDTH", 172);

	//동리//
	m_bsAlphaDoc8Share[0].tPoint.x	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"0_L", 4635);
	m_bsAlphaDoc8Share[0].tPoint.y	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"0_T", 580);
	m_bsAlphaDoc8Share[0].tScale.w	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"0_W", 152);
	m_bsAlphaDoc8Share[0].tScale.h	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"0_H", 236);
	//지번//
	m_bsAlphaDoc8Share[1].tPoint.x	= m_bsAlphaDoc8Share[0].tPoint.x;
	m_bsAlphaDoc8Share[1].tPoint.y	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"1_T", 1030);
	m_bsAlphaDoc8Share[1].tScale.w	= m_bsAlphaDoc8Share[0].tScale.w;
	m_bsAlphaDoc8Share[1].tScale.h	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"1_H", 564);
	//적요//
	m_bsAlphaDoc8Share[2].tPoint.x	= m_bsAlphaDoc8Share[0].tPoint.x;
	m_bsAlphaDoc8Share[2].tPoint.y	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"2_T", 2494);
	m_bsAlphaDoc8Share[2].tScale.w	= m_bsAlphaDoc8Share[0].tScale.w;
	m_bsAlphaDoc8Share[2].tScale.h	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"2_H", 764);
	//SHARE
	m_bsAlphaDoc8Share[3].tPoint.x	= m_nOLeft;
	m_bsAlphaDoc8Share[3].tPoint.y	= m_nOTop;
	m_bsAlphaDoc8Share[3].tScale.w	= m_nOWidth;
	m_bsAlphaDoc8Share[3].tScale.h	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"3_H", 236);
	m_bsAlphaDoc8Share[4].tPoint.x	= m_nOLeft;
	m_bsAlphaDoc8Share[4].tPoint.y	= m_bsAlphaDoc8Share[3].tPoint.y + m_bsAlphaDoc8Share[3].tScale.h;
	m_bsAlphaDoc8Share[4].tScale.w	= m_nOWidth;
	m_bsAlphaDoc8Share[4].tScale.h	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"4_H", 236);
	m_bsAlphaDoc8Share[5].tPoint.x	= m_nOLeft;
	m_bsAlphaDoc8Share[5].tPoint.y	= m_bsAlphaDoc8Share[4].tPoint.y + m_bsAlphaDoc8Share[4].tScale.h;
	m_bsAlphaDoc8Share[5].tScale.w	= m_nOWidth;
	m_bsAlphaDoc8Share[5].tScale.h	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"5_H", 176);
	m_bsAlphaDoc8Share[6].tPoint.x	= m_nOLeft;
	m_bsAlphaDoc8Share[6].tPoint.y	= m_bsAlphaDoc8Share[5].tPoint.y + m_bsAlphaDoc8Share[5].tScale.h;
	m_bsAlphaDoc8Share[6].tScale.w	= m_nOWidth;
	m_bsAlphaDoc8Share[6].tScale.h	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"6_H", 426);
	m_bsAlphaDoc8Share[7].tPoint.x	= m_nOLeft;
	m_bsAlphaDoc8Share[7].tPoint.y	= m_bsAlphaDoc8Share[6].tPoint.y + m_bsAlphaDoc8Share[6].tScale.h;
	m_bsAlphaDoc8Share[7].tScale.w	= m_nOWidth;
	m_bsAlphaDoc8Share[7].tScale.h	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"7_H", 378);

	m_bsAlphaDoc8Share[8].tPoint.x	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"8_L", 180);
	m_bsAlphaDoc8Share[8].tPoint.y	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"8_T", 3280);//3296//
	m_bsAlphaDoc8Share[8].tScale.w	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"8_W", 1000);
	m_bsAlphaDoc8Share[8].tScale.h	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"8_H", 30);

	//등급//LEVEL//241203//#등급#추가//
	m_bsAlphaDoc8Share[9].tPoint.x	= m_bsAlphaDoc8Share[0].tPoint.x;
	m_bsAlphaDoc8Share[9].tPoint.y	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"10_T", 1810);
	m_bsAlphaDoc8Share[9].tScale.w	= m_bsAlphaDoc8Share[0].tScale.w;
	m_bsAlphaDoc8Share[9].tScale.h	= frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"10_H", 470);

	m_nNumberL		= 12;//221208//#PRINT_IMPROVE//

	//공유지연명부 Grid1, Grid2 높이 차이//
	m_nTopBottomGap = frmMain->CONFIGDOC8INI->ReadInteger(asINIHeader, L"TB_GAP", 1466);
}
//---------------------------------------------------------------------------

//231101//#SHAREOWN_PRINT
void __fastcall TfrmAlphaDoc8::funcMakeViewImageA3Share()
{
	AnsiString  asPathName	= "";

	frmAlphaDoc8->m_asSavedFileName1	= "";
	frmAlphaDoc8->m_asSavedFileName2	= "";

	//============================================
	//확대축소를 위한 이미지 보관 폴더 삭제//
	AnsiString  asTempDir	= frmMain->ROOTPATH + "tmp2\\";
	if (!DirectoryExists(asTempDir))
		CreateDir(asTempDir);
	//============================================

	try{
		pbRect2->Invalidate();

		//---------------------------------
		funcLoadImage(frmAlphaDoc8->m_asBGFilePath);
		funcRedrawShareOwn();
		asPathName	= asTempDir + "[공유지연명부]" + frmMain->m_asLandNm + ".jpg";
		frmAlphaDoc8->m_asSavedFileName1	= asPathName;
		if(FileExists(asPathName))
			DeleteFile(asPathName);
		IMGSCREEN2->Picture->SaveToFile(asPathName);

		//---------------------------------
		frmAlphaDoc8->m_asSavedFileName	= frmAlphaDoc8->m_asSavedFileName1;



//=============================================================================
//231123//TEST
//		funcLoadImage(frmMain->ROOTPATH + "FORMAT\\테스트용1.png");
//		funcRedrawOwnInfo();
//		asPathName	= asTempDir + "[공유지연명부]" + frmMain->m_asLandNm + "_TEST.png";
//		eData->m_asSavedFileName2	= asPathName;
//		IMGSCREEN2->Picture->SaveToFile(asPathName);
//=============================================================================



		m_bPaintCompleted	= true;//230925//
	}
	__finally{
//230925//TEST//		pbRect2->Invalidate();
	}
}
//---------------------------------------------------------------------------

//231101//#SHAREOWN_PRINT
void __fastcall TfrmAlphaDoc8::funcRedrawShareOwn()
{
	int fontwidth		= m_nFontSize;
	int fontheight 		= fontwidth;
	int nMiddleWidth	= m_nMiddleWidth;
	SHARP_POSITION_STRUCT	tempData;
	TPoint	tPoint;
	TScale  tScale;

	//230908//DEBUG//
//	IMGSCREEN2->Canvas->Font->Name = frmMain->m_asFontName;
//	IMGSCREEN2->Canvas->Font->Size = 12;

	//if(pbRect2->Visible)
	if(!m_bPaintCompleted)//230925//1번째가 정상인지 2번째가 정상인지 확인 후 처리할 것//
	{
    	//##########################################################################################
		// 공통 사용 변수(PaintBox)
    	//##########################################################################################
		HDC 	hdc 			= IMGSCREEN2->Canvas->Handle;
		HPEN 	pen, penSharp;
		HFONT   m_font, hOldFont;
		HFONT 	m_fontL, hOldFontL;//지번폰트//
		HFONT 	m_fontRatio, hOldFontRatio;//소유권보합폰트//231114//
		TColor	cPenColorC		= (TColor)RGB(255, 0, 0);//Caution
		TColor	cPenColor		= panMain->Font->Color;
		TColor	cPenColorSharp	= (TColor)RGB(255, 0, 0);//부분삭제선//

    	//##########################################################################################
    	// 공통 사용 변수(String, Position)
    	//##########################################################################################
		AnsiString 	asData		= "";//한 셀 포함 문자//
		AnsiString 	asCaption 	= "";//TextOut에 표기할 문자//
		AnsiString 	asTemp 		= "";//SubString, 길이체크 용으로 사용할 문자//
		int 		nTxtLen 	= 0;
		bool		bPartSharp		= false;
		bool		bAllSharp		= false;//#1016//전체삭제-취소선//
		bool		bEven			= true;//241203//취소선 % 개수 체크(open-close) 확인용//
		int 		nTextW			= 0;
		int 		nTextH			= 0;
		int			nStartW			= 0;
		int			nStartH			= 0;
		int			nSumH			= 0;
		int			nPartSharp1		= 0;
		int			nPartSharp2		= 0;
		int			nAllSharp1		= 0;
		int			nAllSharp2		= 0;
		//==============================================================

		//부분삭제선//여기에서만 초기화한다//
		eData->m_vSharpPos.clear();



		//==============================================================
		//일반폰트//
		m_font	= ::CreateFont(fontwidth, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
		hOldFont  = (HFONT)::SelectObject(hdc, m_font);
		//==============================================================



		//##########################################################################################
		//#
		//# CAUTION
    	//#
    	//##########################################################################################
        {
			//==============================================================
			pen   = ::CreatePen(PS_SOLID, 1, cPenColorC);
			::SelectObject(hdc, pen);
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
			::SetBkMode(hdc, TRANSPARENT);
			::SetTextColor(hdc, cPenColorC);
			IMGSCREEN2->Canvas->Brush->Color	= clWhite;
			//==============================================================

			//==========================================================================================
			tPoint	= m_bsAlphaDoc8Share[8].tPoint;
			nTextW	= IMGSCREEN2->Canvas->TextWidth(eData->m_vCAUTION[0].DATA)+1;//Caution.Text.Width는 독립적//
			nTextH	= IMGSCREEN2->Canvas->TextHeight(eData->m_vCAUTION[0].DATA)+1;//Caution.Text.Width는 독립적//
			//==========================================================================================

    		//======================================================
    		// 좌측하단 문구표시//
    		IMGSCREEN2->Canvas->TextOutA(tPoint.x, tPoint.y, eData->m_vCAUTION[0].DATA);
			//======================================================

			::SetROP2 (hdc, oldro);
			::DeleteObject( pen );
		}


		//##########################################################################################
    	//#
		//# LAND, JIBUN, LEVEL, MEMO
    	//#
    	//##########################################################################################
		//==============================================================
		//지번폰트//
		m_fontL	= ::CreateFont(fontwidth+2, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
		hOldFontL  = (HFONT)::SelectObject(hdc, m_fontL);
		//==============================================================
		{
			//==============================================================
			pen   = ::CreatePen(PS_SOLID, 1, cPenColor);
			::SelectObject(hdc, pen);
			int oldro = ::SetROP2(hdc, R2_COPYPEN);
			::SetBkMode(hdc, TRANSPARENT);
			::SetTextColor(hdc, cPenColor);
			IMGSCREEN2->Canvas->Brush->Color	= clWhite;
			//==============================================================

			//==============================================================
			asData			= "";//한 셀 포함 문자//
			asCaption 		= "";//TextOut에 표기할 문자//
			asTemp 			= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen 		= 0;
			nTextW			= 0;
			nTextH			= 0;
			nStartW			= 0;
			nStartH			= 0;
			nSumH			= 0;
			nPartSharp1		= 0;
			nPartSharp2		= 0;
			nAllSharp1		= 0;
			nAllSharp2		= 0;
			//==============================================================



			//*****************************************************************
			//
			// 동리 //LAND//읍면동명, 리명 구분하여 두 줄 처리//
			//
			//*****************************************************************
			bAllSharp	= false;
			bPartSharp	= false;

			//==========================================================================================
			tPoint	= m_bsAlphaDoc8Share[0].tPoint;
			tScale	= m_bsAlphaDoc8Share[0].tScale;
			nTextW	= IMGSCREEN2->Canvas->TextWidth("동")+1;//임의글자로 체크//
			nTextH	= IMGSCREEN2->Canvas->TextHeight("동")+1;//임의글자로 체크//
    		//=========================================================

			if(eData->m_asLand.Length() > 0)
			{
                eData->m_asLand	= StringReplace(eData->m_asLand, " ", "_", TReplaceFlags() << rfReplaceAll);
                asData = eData->m_asLand;
				//---
                nTxtLen = asData.Length();
                nSumH	= 0;

                //=================================================
                //211206//읍면동명, 리명 구분하여 두 줄 처리//
                TStringList *slData 		= new TStringList;
                slData	= new TStringList();
                int nPos	= asData.Pos("_");
                while(nPos > 0)
                {
                    asTemp 	= asData.SubString(1, nPos-1);
                    slData->Add(asTemp);
                    asData  = asData.Delete(1, nPos);
                    nPos	= asData.Pos("_");
                }
                slData->Add(asData);

    			//==========================================================================================
				//실제표시//
//231103//
				nStartW = funcGetStartW(0, 0, slData->Count, nTextW);
//OLD//
//				nStartW	= tPoint.x + tScale.w - ((tScale.w - slData->Count*nTextW) / 2);
    			//==========================================================================================

                for(int z = 0; z < slData->Count; z++)
				{
					asData	= slData->Strings[z];
	//				asData	= StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
    //				asData	= StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
    //				asData	= StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);

                    nTxtLen = asData.Length();
                    nSumH	= 0;
                    //라인별 높이 체크//
                    for(int j = 0; j < nTxtLen; j++)
                    {
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asTemp = asData.SubString(j+1, 2);
                            nSumH	+= IMGSCREEN2->Canvas->TextHeight(asTemp);
                            j++;
                        }
                        else
                        {
                            if(asData.c_str()[j] == '%')//부분삭제//
                                continue;
                            if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
                            {
                                if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
                                {
                                    asCaption = asData.SubString(j+1, 2);
                                    nSumH	+= IMGSCREEN2->Canvas->TextHeight(asCaption);
                                    j++;
                                    continue;
                                }
                            }
                            asCaption = asData.SubString(j+1, 1);
                            nSumH	+= IMGSCREEN2->Canvas->TextHeight(asCaption);
                        }
                    }

					//=========================================================
					nStartW	-= nTextW;
//231103//
					nStartH = funcGetStartH(0, 0, 0, nSumH);
//OLD//
//                    nStartH	= tPoint.y + (tScale.h - nSumH) / 2;
					//=========================================================

                    //=========================================================
                    for(int j = 0; j < nTxtLen; j++)
                    {
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asCaption = asData.SubString(j+1, 2);
                            IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
                            j++;
                        }
                        else
                        {
                            if(!bPartSharp && asData.c_str()[j] =='%')
    	                    {
                                bPartSharp	= true;
                                nPartSharp1	= nStartH;
                                continue;
                            }
                            else if(bPartSharp && asData.c_str()[j] =='%')
    	                    {
                                nPartSharp2	= nStartH-1;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                                tempData.tpSTT.x	= nStartW + nTextW/2;
                                tempData.tpSTT.y	= nPartSharp1;
                                tempData.tpEND.x	= nStartW + nTextW/2;
                                tempData.tpEND.y	= nPartSharp2;
                                eData->m_vSharpPos.push_back(tempData);
								bPartSharp	= false;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                continue;
							}

                            if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
                            {
                                if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
    	                        {
                                    asCaption = asData.SubString(j+1, 2);
									IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
                                    j++;
                                    nStartH	+= nTextH;
                                    continue;
                                }
                            }
                            //숫자 1자리//
                            asCaption = asData.SubString(j+1, 1);
                            IMGSCREEN2->Canvas->TextOutA(nStartW+m_nNumberL, nStartH, asCaption);
                        }

                        nStartH	+= nTextH;
                    }
                }

                delete slData;
                slData    = NULL;
			}


			//*****************************************************************
			//
			// 지번 //
			//
			//*****************************************************************
			bAllSharp	= false;
			bPartSharp	= false;

			//==========================================================================================
			tPoint  = m_bsAlphaDoc8Share[1].tPoint;
			tScale  = m_bsAlphaDoc8Share[1].tScale;
			nTextW	= IMGSCREEN2->Canvas->TextWidth("번")+1;//임의글자로 체크//
			nTextH  = IMGSCREEN2->Canvas->TextHeight("번");//임의글자로 체크//
            //==========================================================================================

			if(eData->m_asJibun.Length() > 0)
            {
                asData     = eData->m_asJibun;
                if(frmMain->m_nBonbuType == 1)
                    asData    = StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
                else if(frmMain->m_nBonbuType == 2)
                    asData    = StringReplace(asData, "-", ".", TReplaceFlags() << rfReplaceAll);
                else if(frmMain->m_nBonbuType == 3)
                    asData    = StringReplace(asData, "-", "/", TReplaceFlags() << rfReplaceAll);
                else if(frmMain->m_nBonbuType == 4)
                    asData    = StringReplace(asData, "-", " - ", TReplaceFlags() << rfReplaceAll);
                else if(frmMain->m_nBonbuType == 5)
                    asData    = StringReplace(asData, "-", " | ", TReplaceFlags() << rfReplaceAll);
                else if(frmMain->m_nBonbuType == 6)
                    asData    = StringReplace(asData, "-", "의", TReplaceFlags() << rfReplaceAll);
                //---
                nTxtLen = asData.Length();
                nSumH    = 0;

                for(int j = 0; j < nTxtLen; j++)
                {
                    if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                    {
                        asTemp = asData.SubString(j+1, 2);
                        nSumH    += IMGSCREEN2->Canvas->TextHeight(asTemp);
						j++;
                    }
					else
                    {
                        asCaption = asData.SubString(j+1, 1);
                        nSumH    += IMGSCREEN2->Canvas->TextHeight(asCaption);
					}
                }

				//=========================================================
				//실제표시//
//231103//
				nStartW = funcGetStartW(1, 0, 1, nTextW);
				nStartW    -= nTextW;
				nStartH = funcGetStartH(1, 0, 1, nSumH);
//OLD//
//				nStartW    = tPoint.x + (tScale.w - nTextW) / 2;
//				nStartH    = tPoint.y + (tScale.h - nSumH) / 2;
                //=========================================================

				for(int j = 0; j < nTxtLen; j++)
				{
					if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                    {
                        asCaption = asData.SubString(j+1, 2);
                        IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
                        j++;
                    }
                    else
					{
                        asCaption = asData.SubString(j+1, 1);
						IMGSCREEN2->Canvas->TextOutA(nStartW+m_nNumberL, nStartH, asCaption);
					}
					nStartH    += nTextH+1;
                }
            }

            ::SetROP2 (hdc, oldro);
            ::DeleteObject( pen );


			//===================================
			//241203//#등급#추가//
			//===================================
			//*****************************************************************
			//
			// 등급 //
			//
			//*****************************************************************
			bAllSharp	= false;
			bPartSharp	= false;
			bEven		= true;//close상태//

			//==========================================================================================
			tPoint  = m_bsAlphaDoc8Share[9].tPoint;
			tScale  = m_bsAlphaDoc8Share[9].tScale;
			nTextW	= IMGSCREEN2->Canvas->TextWidth("등")+1;//임의글자로 체크//
			nTextH  = IMGSCREEN2->Canvas->TextHeight("등")+1;//임의글자로 체크//
			//=========================================================

			if(eData->m_asLevel.Length() > 0)
			{
                asData = eData->m_asLevel;
                //---
                nTxtLen = asData.Length();
                nSumH    = 0;

                TStringList *slData         = new TStringList;
                slData    = new TStringList();
    //220826//적요 : 사용자 줄바꿈(_)에서 자동개행으로 변경
    //            int nPos    = asData.Pos("_");
    //            while(nPos > 0)
    //            {
    //                asTemp     = asData.SubString(1, nPos-1);
    //                slData->Add(asTemp);
	//                asData  = asData.Delete(1, nPos);
    //                nPos    = asData.Pos("_");
    //            }
    //            if( !asData.IsEmpty() )
    //                slData->Add(asData);

				//개행없는 데이터 처리//
				int nLineTxtLen    = 0;//Cell 높이와 nTextH로 한줄 글자 수 계산//
				int nLineTxtCnt    = 0;//한글과 숫자 Length()가 다르게 나오기 때문에 정확한 개행 길이만큼 계산이 안되서 사용//
				if(slData->Count == 0 && nTextW > 0)
				{
                    nLineTxtLen    = tScale.h/nTextW;
                    asTemp    = "";

                    for(int j = 0; j < nTxtLen; j++)
                    {
                        if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
                            asTemp = asTemp    + asData.SubString(j+1, 2);
                            if(nLineTxtCnt >= nLineTxtLen-1)
                            {
                                slData->Add(asTemp);
                                asTemp    = "";
                                nLineTxtCnt    = 0;

                                //+++++++++++++++++++++++++++++++++++++++++++++++++++
                                if(asData.c_str()[j+2] == '_')
                                    j++;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++
                            }
                            else
                            {
								nLineTxtCnt++;//231215//ReturnCode//세로쓰기는한글2글자로체킹할필요없다.//231117//++ -> += 2
                            }
                            j++;
						}
                        else
                        {
                            //========================================================
                            if(asData.c_str()[j] == '_')
                            {
                                if( !asTemp.IsEmpty() )//211208//31025.2.20.2//주소개행과 길이자동개행이 복합//
                                {
                                    slData->Add(asTemp);
                                    asTemp    = "";
                                    nLineTxtCnt    = 0;

                                    //+++++++++++++++++++++++++++++++++++++++++++++++++++
                                    //220427//소유자명 8글자이면 자동개행인데 '_'를 붙여서 한줄을 더 띄우는 문제 발생//
                                    if(asData.c_str()[j+1] == '_')
                                        j++;
                                    //+++++++++++++++++++++++++++++++++++++++++++++++++++
                                }
                            }
                            else
                            {
                                //========================================================
                                //211201//#8//이름 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
								if(asData.c_str()[j] == '%')
                                {
									bEven	= !bEven;//241203//
									nLineTxtLen    = nLineTxtLen + 1;
                                }
								//========================================================
                                asTemp = asTemp + asData.SubString(j+1, 1);
                                if(nLineTxtCnt >= nLineTxtLen-1)
                                {
                                    //========================================================
                                    //211201//#8//이름 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
									if( !bEven )//241203//
									{
										if(asData.c_str()[j+1] == '%')
										{
											bEven	= !bEven;//241203//
											nLineTxtLen    = nLineTxtLen + 1;
											asTemp = asTemp + asData.SubString(j+2, 1);
											j++;
										}
									}
                                    //========================================================
                                    slData->Add(asTemp);
                                    asTemp    = "";
                                    nLineTxtCnt    = 0;

                                    //+++++++++++++++++++++++++++++++++++++++++++++++++++
                                    //220427//소유자명 8글자이면 자동개행인데 '_'를 붙여서 한줄을 더 띄우는 문제 발생//
                                    if(asData.c_str()[j+1] == '_')
                                        j++;
                                    //+++++++++++++++++++++++++++++++++++++++++++++++++++
                                }
                                else
                                {
									nLineTxtCnt++;
                                }
                            }
                        }
                    }
                    if( !asTemp.IsEmpty() )
                    {
                        slData->Add(asTemp);
                        asTemp    = "";
					}
                }
                //=========================================================

				//=========================================================
				//실제표시//
                //Width 시작위치 계산//220826//적요 : 사용자 줄바꿈(_)에서 자동개행으로 변경//
//231103//
				nStartW = funcGetStartW(2, 0, slData->Count, nTextW);
//OLD//
//				nStartW    = tPoint.x + tScale.w - ((tScale.w - slData->Count*nTextW)/2);//세로쓰기-중간//
				//=========================================================

				for(int z = 0; z < slData->Count; z++)
                {
					asData    = slData->Strings[z];
                    asData    = StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
                    asData    = StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
                    asData    = StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);
                    asData    = StringReplace(asData, ".", ",", TReplaceFlags() << rfReplaceAll);//211207//

                    nTxtLen = asData.Length();
                    nSumH    = 0;
					//라인별 높이 체크//
					for(int j = 0; j < nTxtLen; j++)
                    {
                        if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asTemp = asData.SubString(j+1, 2);
                            nSumH    += IMGSCREEN2->Canvas->TextHeight(asTemp);
                            j++;
                        }
                        else
                        {
							if(asData.c_str()[j] == '%')//부분삭제//
                                continue;
                            if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
                            {
								if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
                                {
                                    asCaption = asData.SubString(j+1, 2);
                                    nSumH    += IMGSCREEN2->Canvas->TextHeight(asCaption);
                                    j++;
                                    continue;
                                }
							}
							asCaption = asData.SubString(j+1, 1);
							nSumH    += IMGSCREEN2->Canvas->TextHeight(asCaption);
						}
					}

					//=========================================================
					//실제표시//
					nStartW    -= nTextW;
//231103//
					nStartH = funcGetStartH(2, 0, 0, nSumH);
//OLD//
//					nStartH    = tPoint.y + (tScale.h - nSumH) / 2;

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(시작)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp1    = nStartH;
					}
					//=========================================================

					//=========================================================
                    for(int j = 0; j < nTxtLen; j++)
                    {
                        if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asCaption = asData.SubString(j+1, 2);
                            IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
                            j++;
                        }
                        else
                        {
                            if(!bPartSharp && asData.c_str()[j] =='%')
                            {
                                bPartSharp    = true;
                                nPartSharp1    = nStartH;
                                continue;
                            }
							else if(bPartSharp && asData.c_str()[j] =='%')
                            {
                                nPartSharp2    = nStartH-1;
                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                                tempData.tpSTT.x    = nStartW + nTextW/2;
								tempData.tpSTT.y    = nPartSharp1;
                                tempData.tpEND.x    = nStartW + nTextW/2;
                                tempData.tpEND.y    = nPartSharp2;
                                eData->m_vSharpPos.push_back(tempData);
                                bPartSharp    = false;
                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                continue;
                            }

                            if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
                            {
                                if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
                                {
                                    asCaption = asData.SubString(j+1, 2);
                                    IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
                                    j++;
                                    nStartH    += nTextH;
                                    continue;
                                }
                            }
                            //숫자 1자리//
                            asCaption = asData.SubString(j+1, 1);
                            IMGSCREEN2->Canvas->TextOutA(nStartW+m_nNumberL, nStartH, asCaption);
                        }

                        nStartH    += nTextH;
					}

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(종료)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x    = nStartW + nTextW/2;
						tempData.tpSTT.y    = nPartSharp1;
						tempData.tpEND.x    = nStartW + nTextW/2;
						tempData.tpEND.y    = nPartSharp2;
						eData->m_vSharpPos.push_back(tempData);
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
					//=========================================================

				}
				delete slData;
                slData    = NULL;
			}



			//*****************************************************************
			//
			// 적요 //
			//
			//*****************************************************************
			bAllSharp	= false;
			bPartSharp	= false;
			bEven		= true;//close상태//

			//==========================================================================================
			tPoint  = m_bsAlphaDoc8Share[2].tPoint;
			tScale  = m_bsAlphaDoc8Share[2].tScale;
			nTextW	= IMGSCREEN2->Canvas->TextWidth("메")+1;//임의글자로 체크//
			nTextH  = IMGSCREEN2->Canvas->TextHeight("메")+1;//임의글자로 체크//
			//=========================================================

			if(eData->m_asMemo.Length() > 0)
			{
                asData = eData->m_asMemo;
                //---
                nTxtLen = asData.Length();
                nSumH    = 0;

                TStringList *slData         = new TStringList;
                slData    = new TStringList();
    //220826//적요 : 사용자 줄바꿈(_)에서 자동개행으로 변경
    //            int nPos    = asData.Pos("_");
    //            while(nPos > 0)
    //            {
    //                asTemp     = asData.SubString(1, nPos-1);
    //                slData->Add(asTemp);
	//                asData  = asData.Delete(1, nPos);
    //                nPos    = asData.Pos("_");
    //            }
    //            if( !asData.IsEmpty() )
    //                slData->Add(asData);

				//개행없는 데이터 처리//
				int nLineTxtLen    = 0;//Cell 높이와 nTextH로 한줄 글자 수 계산//
				int nLineTxtCnt    = 0;//한글과 숫자 Length()가 다르게 나오기 때문에 정확한 개행 길이만큼 계산이 안되서 사용//
				if(slData->Count == 0 && nTextW > 0)
				{
                    nLineTxtLen    = tScale.h/nTextW;
                    asTemp    = "";

                    for(int j = 0; j < nTxtLen; j++)
                    {
                        if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
                            asTemp = asTemp    + asData.SubString(j+1, 2);
                            if(nLineTxtCnt >= nLineTxtLen-1)
                            {
                                slData->Add(asTemp);
                                asTemp    = "";
                                nLineTxtCnt    = 0;

                                //+++++++++++++++++++++++++++++++++++++++++++++++++++
                                if(asData.c_str()[j+2] == '_')
                                    j++;
								//+++++++++++++++++++++++++++++++++++++++++++++++++++
                            }
                            else
                            {
								nLineTxtCnt++;//231215//ReturnCode//세로쓰기는한글2글자로체킹할필요없다.//231117//++ -> += 2
                            }
                            j++;
						}
                        else
                        {
                            //========================================================
                            if(asData.c_str()[j] == '_')
                            {
                                if( !asTemp.IsEmpty() )//211208//31025.2.20.2//주소개행과 길이자동개행이 복합//
                                {
                                    slData->Add(asTemp);
                                    asTemp    = "";
                                    nLineTxtCnt    = 0;

                                    //+++++++++++++++++++++++++++++++++++++++++++++++++++
                                    //220427//소유자명 8글자이면 자동개행인데 '_'를 붙여서 한줄을 더 띄우는 문제 발생//
                                    if(asData.c_str()[j+1] == '_')
                                        j++;
                                    //+++++++++++++++++++++++++++++++++++++++++++++++++++
                                }
                            }
                            else
                            {
                                //========================================================
                                //211201//#8//이름 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
								if(asData.c_str()[j] == '%')
                                {
									bEven	= !bEven;//241203//
									nLineTxtLen    = nLineTxtLen + 1;
                                }
								//========================================================
                                asTemp = asTemp + asData.SubString(j+1, 1);
                                if(nLineTxtCnt >= nLineTxtLen-1)
                                {
                                    //========================================================
                                    //211201//#8//이름 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
									if( !bEven )//241203//
									{
										if(asData.c_str()[j+1] == '%')
										{
											bEven	= !bEven;//241203//
											nLineTxtLen    = nLineTxtLen + 1;
											asTemp = asTemp + asData.SubString(j+2, 1);
											j++;
										}
									}
									//========================================================
                                    slData->Add(asTemp);
                                    asTemp    = "";
                                    nLineTxtCnt    = 0;

                                    //+++++++++++++++++++++++++++++++++++++++++++++++++++
                                    //220427//소유자명 8글자이면 자동개행인데 '_'를 붙여서 한줄을 더 띄우는 문제 발생//
                                    if(asData.c_str()[j+1] == '_')
                                        j++;
                                    //+++++++++++++++++++++++++++++++++++++++++++++++++++
                                }
                                else
                                {
									nLineTxtCnt++;
                                }
                            }
                        }
                    }
                    if( !asTemp.IsEmpty() )
                    {
                        slData->Add(asTemp);
                        asTemp    = "";
					}
                }
                //=========================================================

				//=========================================================
				//실제표시//
                //Width 시작위치 계산//220826//적요 : 사용자 줄바꿈(_)에서 자동개행으로 변경//
//231103//
				nStartW = funcGetStartW(2, 0, slData->Count, nTextW);
//OLD//
//				nStartW    = tPoint.x + tScale.w - ((tScale.w - slData->Count*nTextW)/2);//세로쓰기-중간//
				//=========================================================

				for(int z = 0; z < slData->Count; z++)
                {
					asData    = slData->Strings[z];
                    asData    = StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
                    asData    = StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
                    asData    = StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);
                    asData    = StringReplace(asData, ".", ",", TReplaceFlags() << rfReplaceAll);//211207//

                    nTxtLen = asData.Length();
                    nSumH    = 0;
                    //라인별 높이 체크//
                    for(int j = 0; j < nTxtLen; j++)
                    {
                        if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asTemp = asData.SubString(j+1, 2);
                            nSumH    += IMGSCREEN2->Canvas->TextHeight(asTemp);
                            j++;
                        }
                        else
                        {
							if(asData.c_str()[j] == '%')//부분삭제//
                                continue;
                            if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
                            {
								if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
                                {
                                    asCaption = asData.SubString(j+1, 2);
                                    nSumH    += IMGSCREEN2->Canvas->TextHeight(asCaption);
                                    j++;
                                    continue;
                                }
							}
							asCaption = asData.SubString(j+1, 1);
							nSumH    += IMGSCREEN2->Canvas->TextHeight(asCaption);
						}
					}

					//=========================================================
					//실제표시//
					nStartW    -= nTextW;
//231103//
					nStartH = funcGetStartH(2, 0, 0, nSumH);
//OLD//
//					nStartH    = tPoint.y + (tScale.h - nSumH) / 2;

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(시작)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp1    = nStartH;
					}
					//=========================================================

					//=========================================================
                    for(int j = 0; j < nTxtLen; j++)
                    {
                        if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asCaption = asData.SubString(j+1, 2);
                            IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
                            j++;
                        }
                        else
                        {
                            if(!bPartSharp && asData.c_str()[j] =='%')
                            {
                                bPartSharp    = true;
                                nPartSharp1    = nStartH;
                                continue;
                            }
							else if(bPartSharp && asData.c_str()[j] =='%')
                            {
                                nPartSharp2    = nStartH-1;
                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                                tempData.tpSTT.x    = nStartW + nTextW/2;
								tempData.tpSTT.y    = nPartSharp1;
                                tempData.tpEND.x    = nStartW + nTextW/2;
                                tempData.tpEND.y    = nPartSharp2;
                                eData->m_vSharpPos.push_back(tempData);
                                bPartSharp    = false;
                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                continue;
                            }

                            if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
                            {
                                if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
                                {
                                    asCaption = asData.SubString(j+1, 2);
                                    IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
                                    j++;
                                    nStartH    += nTextH;
                                    continue;
                                }
                            }
                            //숫자 1자리//
                            asCaption = asData.SubString(j+1, 1);
                            IMGSCREEN2->Canvas->TextOutA(nStartW+m_nNumberL, nStartH, asCaption);
                        }

                        nStartH    += nTextH;
					}

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(종료)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x    = nStartW + nTextW/2;
						tempData.tpSTT.y    = nPartSharp1;
						tempData.tpEND.x    = nStartW + nTextW/2;
						tempData.tpEND.y    = nPartSharp2;
						eData->m_vSharpPos.push_back(tempData);
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
					//=========================================================
				}
				delete slData;
                slData    = NULL;
            }

            ::SetROP2 (hdc, oldro);
            ::DeleteObject( pen );
        }


		//==============================================================
		//일반폰트//
		m_font	= ::CreateFont(fontwidth, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
		hOldFont  = (HFONT)::SelectObject(hdc, m_font);
		//==============================================================



        //##########################################################################################
        //#
		//# DATE
        //#
        //##########################################################################################
		{
            //==============================================================
            //일반폰트//
            pen   = ::CreatePen(PS_SOLID, 1, cPenColor);
            ::SelectObject(hdc, pen);
            int oldro = ::SetROP2(hdc, R2_COPYPEN);
            ::SetBkMode(hdc, TRANSPARENT);
            ::SetTextColor(hdc, cPenColor);
            IMGSCREEN2->Canvas->Brush->Color    = clWhite;
            //==============================================================

			//==============================================================
			asData			= "";//한 셀 포함 문자//
			asCaption   	= "";//TextOut에 표기할 문자//
			asTemp         	= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen     	= 0;
			nTextW        	= 0;
			nTextH        	= 0;
			nStartW        	= 0;
			nStartH        	= 0;
			nSumH        	= 0;
			nPartSharp1    	= 0;
			nPartSharp2    	= 0;
			nAllSharp1      = 0;
			nAllSharp2      = 0;
			//위에서 한번 초기화//eData->m_vSharpPos.clear();
			//==============================================================

			bAllSharp    = false;
            bPartSharp    = false;

            //==========================================================================================
			tPoint  = m_bsAlphaDoc8Share[3].tPoint;
			tScale  = m_bsAlphaDoc8Share[3].tScale;
			nTextW	= IMGSCREEN2->Canvas->TextWidth("일")+1;//임의글자로 체크//
			nTextH  = IMGSCREEN2->Canvas->TextHeight("일")+1;//임의글자로 체크//
            //==========================================================================================

			for( int i = 0; i < (int)eData->m_vSHAREOWNDATE.size(); i++)
            {
                asData = eData->m_vSHAREOWNDATE[i].DATA;

                if(asData == "-")//NoData
                    continue;

                //=====================================================
                //211201//#7//월, 일 등이 비어 있는 경우 존재//410.26.1.195.8
    //            asData    = StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);
				//=====================================================
                asData    = StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
                asData    = StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
                asData    = StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);

                //=====================================================
                if(asData.SubString(1, 1) == "#")//전체삭제//
                {
                    bAllSharp    = true;
                    asData    = asData.Delete(1, 1);
                }
                else
                {
                    bAllSharp    = false;
                }
                //=====================================================

                if(asData.SubString(1, 1) == "%" && asData.SubString(asData.Length(), 1) == "%")//전체삭제를 부분삭제로 입력//
                {
                    bAllSharp    = true;
                    asData    = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
                }
                else
                {
                    bAllSharp    = false;
                }

                //=====================================================
                //230208//#REQ//내용이 있지만 식별이 불가한 경우 처리//
				if(asData != "판독불가")
                //=====================================================
				{
					if( !frmMain->m_bAIOCR )//기구축 DB 번역본//
					{
						asData    = eFunc->funcChangeDateStrFormatDate(asData.c_str());
						asData    = eFunc->funcChangeDateFormatString(3, asData.c_str());
					}
					else//AIOCR 번역본//
					{
						AnsiString  _asData = asData;
						asData	= eFunc->funcChangeDateStrFormatDate(asData.c_str());
						if(asData == "Error")
							asData = _asData;
						else
							asData	= eFunc->funcChangeDateFormatString(3, asData.c_str());
					}
				}

				//---
				nTxtLen = asData.Length();
				nSumH    = 0;

                TStringList *slData         = new TStringList;
                slData    = new TStringList();
                //일자에는 개행하지 않음//
                if(nTxtLen > 0)
                {
                    //=====================================================
                    //230208//#REQ//내용이 있지만 식별이 불가한 경우 처리//
                    if(asData != "판독불가")
                    //=====================================================
                    {
                        //년도//
                        int nPos     = asData.AnsiPos("년");
                        asTemp     = asData.SubString(1, nPos+1);
                        slData->Add(asTemp);
                        asData  = asData.Delete(1, nPos+1);
                        //월일//
                        asTemp     = asData;
                        //211216//도청김훈곤주무관Req//Date에 5줄로 맞춰달라//
                        asTemp    = StringReplace(asTemp, "월", "월 ", TReplaceFlags() << rfReplaceAll);
                        //====================================================
                        //211201//#7//월, 일 등이 비어 있는 경우 존재//410.26.1.195.8
                        if(asTemp.AnsiPos("월") == 0)
                            asTemp    = " 월" + asTemp;
                        if(asTemp.AnsiPos("일") == 0)
                            asTemp    = asTemp + " 일";
                        //====================================================
                        slData->Add(asTemp);
                    }
					//=====================================================
                    //230208//#REQ//내용이 있지만 식별이 불가한 경우 처리//
                    else
                    {
                        slData->Add("판 독");
                        slData->Add("불 가");
                    }
                    //=====================================================
                }
                //=========================================================

				//======================================
				//실제표시//
//231103//
				nStartW = funcGetStartW(3, i, slData->Count, nTextW);
//OLD//
//				//211228//보정//32028.230//31039.18.1
//				if(i == 10)
//					nStartW    = tPoint.x - (i-1)*tScale.w - 20 - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
//                else if(i == 23)
//					nStartW    = tPoint.x - (i-1)*tScale.w - 12 - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
//                else
//					nStartW    = tPoint.x - (i-1)*tScale.w - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
//				if(i%2)//95/2를 보정하기 위함//
//                    nStartW    -= 1;
//				//======================================
//				if(i >= 11)
//					nStartW    -= (nMiddleWidth + 31);//HERE!!!
//                //======================================

				for(int z = 0; z < slData->Count; z++)
                {
                    asData    = slData->Strings[z];

                    nTxtLen = asData.Length();

                    //=========================================================
                    //Height 계산//
					int nSumHeight    = 0;
                    asTemp    = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
                    for(int j = 0; j < asTemp.Length(); j++)
                    {
                        if( (asTemp.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asCaption = asTemp.SubString(j+1, 2);
                            nSumHeight    += IMGSCREEN2->Canvas->TextHeight(asCaption);
                            j++;
                        }
                        else
                        {
                            if( z == 1 && j + 1 < asTemp.Length() && (asTemp.c_str()[j] >= '0' && asTemp.c_str()[j] <= '9'))
                            {
                                if(asTemp.c_str()[j+1] >= '0' && asTemp.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
                                {
                                    asCaption = asTemp.SubString(j+1, 2);
                                    nSumHeight    += IMGSCREEN2->Canvas->TextHeight(asCaption);
                                    j++;
                                    continue;
                                }
                            }
                            asCaption = asTemp.SubString(j+1, 1);
                            nSumHeight    += IMGSCREEN2->Canvas->TextHeight(asCaption);
                        }
                    }
                    //=========================================================

					//=========================================================
					nStartW    -= nTextW;
//231103//
					nStartH = funcGetStartH(3, i, 0, nSumHeight);
//OLD//
//					nStartH    = tPoint.y + (tScale.h - nSumHeight) / 2;//세로쓰기-중간//
					//=========================================================

					if(bAllSharp)//전체삭제//
                        nAllSharp1    = nStartH;

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(시작)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp1    = nStartH;
					}
					//=========================================================

					//=========================================================
                    for(int j = 0; j < nTxtLen; j++)
                    {
                        if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asCaption = asData.SubString(j+1, 2);
                            IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
                            j++;
						}
                        else
                        {
							if(!bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(시작)//
                            {
                                bPartSharp    = true;
                                nPartSharp1    = nStartH;
                                continue;
							}
							else if(bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(종료)//
							{
                                nPartSharp2    = nStartH-1;
                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                                tempData.tpSTT.x    = nStartW + nTextW/2;
								tempData.tpSTT.y    = nPartSharp1;
                                tempData.tpEND.x    = nStartW + nTextW/2;
                                tempData.tpEND.y    = nPartSharp2;
                                eData->m_vSharpPos.push_back(tempData);
                                bPartSharp    = false;
                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                continue;
                            }
//241204//PlanToDelete//세로쓰기 취소선 처리//
//							else if(bPartSharp && j == 0)//세로쓰기 부분삭제 중 개행 후 시작지점//
//                            {
//                                nPartSharp1    = nStartH;
//                                continue;
//                            }
//                            else if(bPartSharp && j == nTxtLen-1)//세로쓰기 부분삭제 중 개행 전 종료지점//
//                            {
//                                nPartSharp2    = nStartH-1;
//                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
//                                tempData.tpSTT.x    = nStartW + nTextW/2;
//                                tempData.tpSTT.y    = nPartSharp1;
//                                tempData.tpEND.x    = nStartW + nTextW/2;
//                                tempData.tpEND.y    = nPartSharp2;
//                                eData->m_vSharpPos.push_back(tempData);
//                                //여기선 flag해제하면 안됨//
//                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                continue;
//                            }

                            if( z == 1 && j + 1 < asData.Length() && (asData.c_str()[j] >= '0' && asData.c_str()[j] <= '9'))
                            {
                                if(asData.c_str()[j+1] >= '0' && asData.c_str()[j+1] <= '9')//월, 일 숫자 2자리//
                                {
                                    asCaption = asData.SubString(j+1, 2);
                                    IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
                                    j++;
                                    nStartH    += nTextH;
                                    continue;
                                }
                            }
                            //숫자 1자리//
                            asCaption = asData.SubString(j+1, 1);
                            IMGSCREEN2->Canvas->TextOutA(nStartW+m_nNumberL, nStartH, asCaption);
						}

                        nStartH    += nTextH;
                    }

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(종료)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x    = nStartW + nTextW/2;
						tempData.tpSTT.y    = nPartSharp1;
						tempData.tpEND.x    = nStartW + nTextW/2;
						tempData.tpEND.y    = nPartSharp2;
						eData->m_vSharpPos.push_back(tempData);
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
					//=========================================================

					//전체삭제-취소선//
                    if(bAllSharp)
                    {
                        nAllSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                        memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                        tempData.tpSTT.x    = nStartW + nTextW/2;
                        tempData.tpSTT.y    = nAllSharp1;
                        tempData.tpEND.x    = nStartW + nTextW/2;
                        tempData.tpEND.y    = nAllSharp2;
                        eData->m_vSharpPos.push_back(tempData);
                        //bAllSharp    = false;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
				}

                delete slData;
                slData    = NULL;
            }

            ::SetROP2 (hdc, oldro);
            ::DeleteObject( pen );
        }



		//##########################################################################################
        //#
        //# REASON
        //#
        //##########################################################################################
        {
            //==============================================================
            //일반폰트//
			pen   = ::CreatePen(PS_SOLID, 1, cPenColor);
            ::SelectObject(hdc, pen);
            int oldro = ::SetROP2(hdc, R2_COPYPEN);
            ::SetBkMode(hdc, TRANSPARENT);
            ::SetTextColor(hdc, cPenColor);
            IMGSCREEN2->Canvas->Brush->Color    = clWhite;
            //==============================================================

			//==============================================================
			asData			= "";//한 셀 포함 문자//
			asCaption   	= "";//TextOut에 표기할 문자//
			asTemp         	= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen     	= 0;
			nTextW        	= 0;
			nTextH        	= 0;
			nStartW        	= 0;
			nStartH        	= 0;
			nSumH        	= 0;
			nPartSharp1    	= 0;
			nPartSharp2    	= 0;
			nAllSharp1      = 0;
			nAllSharp2      = 0;
			//위에서 한번 초기화//eData->m_vSharpPos.clear();
			//==============================================================

			//231110//하단 주석처리(중복제거 후 표시)//
//			AnsiString  asSymbol[15] = {"⑴", "⑵", "⑶", "⑷", "⑸", "⑹", "⑺", "⑻", "⑼", "⑽", "⑾", "⑿", "⒀", "⒁", "⒂"};
			AnsiString  asSymbol[10] = {"⑴", "⑵", "⑶", "⑷", "⑸", "⑹", "⑺", "⑻", "⑼", "⑽"};

			bAllSharp   = false;
			bPartSharp  = false;
			bEven		= true;//241203//

			//==============================================================
			TStringList *slComment         = new TStringList;
            slComment    = new TStringList();
            slComment->Text = "";
            slComment->Clear();
            //==============================================================

            //==========================================================================================
			tPoint  = m_bsAlphaDoc8Share[4].tPoint;
			tScale  = m_bsAlphaDoc8Share[4].tScale;
			nTextW	= IMGSCREEN2->Canvas->TextWidth("사")/*+1*/;//임의글자로 체크//
			nTextH  = IMGSCREEN2->Canvas->TextHeight("사")+1;//임의글자로 체크//
            //==========================================================================================

            for( int i = 0; i < (int)eData->m_vSHAREOWNREASON.size(); i++)
            {
                asData = eData->m_vSHAREOWNREASON[i].DATA;

                if(asData == "-")//NoData
                    continue;

				asData    = StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);
                asData    = StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
                //asData    = StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
                //asData    = StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);


//231121//공유지는 '소유권_이 전" 등의 자동개행 처리하지 않음//
//[TODO]추후 필요할 때 아래 코드를 원복한다//
//241114//아래코드를 원복
				//=====================================================
				//소유권이전, 소유권보존 자동개행처리//
				AnsiString  asTmp1  = "";
				AnsiString  asTmp2  = "";
				bool		bFound	= false;
				for(int r = 0; r < (int)frmMain->m_vREASONDATA.size(); r++)
				{
					int nPosition = 0;
					asTmp1	= frmMain->m_vREASONDATA[r].DATA;
					asTmp2  = StringReplace(asTmp1, "_", "", TReplaceFlags() << rfReplaceAll);
					asTmp2  = StringReplace(asTmp2, " ", "", TReplaceFlags() << rfReplaceAll);//2112080//사고란에는 특정데이터(eData->m_vREASONDATA)를 제외하고는 공백처리하지 않음//
					nPosition	= asData.AnsiPos(asTmp2);
					if(nPosition > 1)//eData->m_vREASONDATA 데이터가 본 데이터의 시작이 아니라면 앞에 다른 데이터가 존재한다는 뜻//
					{
						asData    = StringReplace(asData, asTmp2, "_" + asTmp1, TReplaceFlags() << rfReplaceAll);
						bFound	= true;
						break;//231116//
					}
					else if(nPosition == 1)
					{
						asData    = StringReplace(asData, asTmp2, asTmp1, TReplaceFlags() << rfReplaceAll);
						bFound	= true;
						break;//231116//
					}
				}
				//=====================================================

				//=====================================================
				if(asData.SubString(1, 1) == "#")//전체삭제//
				{
					bAllSharp    = true;
					asData    = asData.Delete(1, 1);
				}
				else
				{
					bAllSharp    = false;
				}

				if(asData.SubString(1, 1) == "%" && asData.SubString(asData.Length(), 1) == "%")//전체삭제를 부분삭제로 입력//
				{
                    //=================================================================================
                    //211229//
                    asTemp    = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
                    if(asTemp.Length() < 20)
                    {
                    	bAllSharp    = true;
                    	asData    = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					}
                    //=================================================================================
                }
                else
                {
					bAllSharp    = false;
                }
                //=====================================================



                //---
                nTxtLen = asData.Length();
                nSumH    = 0;

                TStringList *slData         = new TStringList;
                slData    = new TStringList();

				//개행없는 데이터 처리//
                int nLineTxtLen    = 0;//Cell 높이와 nTextH로 한줄 글자 수 계산//
                int nLineTxtCnt    = 0;//한글과 숫자 Length()가 다르게 나오기 때문에 정확한 개행 길이만큼 계산이 안되서 사용//
				if(slData->Count == 0 && nTextW > 0)
                {
                    nLineTxtLen    = tScale.h/nTextW;
					asTemp    = "";

                    //=================================================================================
                    //주석처리//
                    //211229//
                    asTemp    = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
					if(asTemp.Length() >= 20)//231116//20->40
					//211229//if(asData.Length() >= 20)//asData.Pos("법률") > 0 || asData.Pos("분배농지") > 0)
					{
						asTemp    = "";//211229//

						bool bFound	= false;
						for(int k = 0; k < slComment->Count; k++)
						{
							AnsiString  asCmt1 = "";
							AnsiString  asCmt2 = "";
							asCmt1 = slComment->Strings[k];
							asCmt1 = asCmt1.SubString(3, asCmt1.Length()-1);
							asCmt2 = asData;
							asCmt2	= StringReplace(asCmt2, "_", "", TReplaceFlags() << rfReplaceAll);
							asCmt2  = StringReplace(asCmt2, " ", "", TReplaceFlags() << rfReplaceAll);//2112080//사고란에는 특정데이터(eData->m_vREASONDATA)를 제외하고는 공백처리하지 않음//

							if(asCmt1 == asCmt2)
							{
								bFound = true;
								slData->Add("하단기재");//211216//도청김훈곤주무관Req//주석:하단기재//41023.628
								slData->Add(asSymbol[k]);
								break;
							}
						}

						if( !bFound )//기존 주석 유형과 다른 경우 새로 추가//
						{
							slData->Add("하단기재");//211216//도청김훈곤주무관Req//주석:하단기재//41023.628
							slData->Add(asSymbol[slComment->Count]);

							asData	= StringReplace(asData, "_", "", TReplaceFlags() << rfReplaceAll);
							asData  = StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);//2112080//사고란에는 특정데이터(eData->m_vREASONDATA)를 제외하고는 공백처리하지 않음//
							asData  = asSymbol[slComment->Count] + asData;
							slComment->Add(asData);
						}
					}
					//=================================================================================
					else//일반적인 데이터//
					{
						//개행 문자에 따른 줄바꿈기능//
						int nPos    = asData.Pos("_");
						if(nPos > 0)
						{
							while(nPos > 0)
							{
								asTemp     = asData.SubString(1, nPos-1);
								slData->Add(asTemp);
								asData  = asData.Delete(1, nPos);
								nPos    = asData.Pos("_");
							}
							if( !asData.IsEmpty() )
								slData->Add(asData);
						}
//=============================================================================
//231116//개행없는 데이터 처리//
						else
						{
							asTemp = "";
							for(int j = 0; j < nTxtLen; j++)
							{
								if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
								{
									asTemp = asTemp    + asData.SubString(j+1, 2);
									if(nLineTxtCnt >= nLineTxtLen-1)
									{
										slData->Add(asTemp);
										asTemp    = "";
										nLineTxtCnt    = 0;
									}
									else
									{
										nLineTxtCnt++;//231215//ReturnCode//세로쓰기는한글2글자로체킹할필요없다.//231117//++ -> += 2
									}
									j++;
								}
								else
								{
									//================================================
									//개행 문자에 따른 줄바꿈기능//
									//========================================================
									if(asData.c_str()[j] == '_')
									{
										slData->Add(asTemp);
										asTemp    = "";
										nLineTxtCnt    = 0;
									}
									else
									//========================================================
									{
										//========================================================
										//211201//#8//이름 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
										if(asData.c_str()[j] == '%')
										{
											bEven	= !bEven;//241203//
											nLineTxtLen    = nLineTxtLen + 1;
										}
										//========================================================

										asTemp = asTemp + asData.SubString(j+1, 1);
										if(nLineTxtCnt >= nLineTxtLen-1)
										{
											//========================================================
											//211201//#8//이름 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
											if( !bEven )//241203//
											{
												if(asData.c_str()[j+1] == '%')
												{
													bEven	= !bEven;//241203//
													nLineTxtLen    = nLineTxtLen + 1;
													asTemp = asTemp + asData.SubString(j+2, 1);
													j++;
												}
											}
											//========================================================
											slData->Add(asTemp);
											asTemp    = "";
											nLineTxtCnt    = 0;
										}
										else
										{
											nLineTxtCnt++;
										}
									}
								}
							}
							if( !asTemp.IsEmpty() )
							{
								slData->Add(asTemp);
								asTemp    = "";
							}
						}
//231116//ORG//TEST후 결정//
//						//개행 문자에 따른 줄바꿈기능//
//						int nPos    = asData.Pos("_");
//						while(nPos > 0)
//						{
//							asTemp     = asData.SubString(1, nPos-1);
//							slData->Add(asTemp);
//							asData  = asData.Delete(1, nPos);
//							nPos    = asData.Pos("_");
//						}
//						if( !asData.IsEmpty() )
//							slData->Add(asData);
//=============================================================================

					}
                }
				//=========================================================

                //======================================
				//실제표시//
//231103//
				nStartW = funcGetStartW(4, i, slData->Count, nTextW);
//OLD//
//				//211228//보정//32028.230//31039.18.1
//				if(i == 10)
//					nStartW    = tPoint.x - (i-1)*tScale.w - 20 - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
//                else if(i == 23)
//					nStartW    = tPoint.x - (i-1)*tScale.w - 12 - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
//                else
//				nStartW    = tPoint.x - (i-1)*tScale.w - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
//				if(i%2)//95/2를 보정하기 위함//
//					nStartW    -= 1;
//				//======================================
//                if(i >= 11)
//                    nStartW    -= (nMiddleWidth + 31);//HERE!!!
//				//======================================


				for(int z = 0; z < slData->Count; z++)
				{
                    asData    = slData->Strings[z];

                    nTxtLen = asData.Length();

					//=========================================================
                    //Height 계산//
                    int nSumHeight    = 0;
                    asTemp    = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
                    for(int j = 0; j < asTemp.Length(); j++)
                    {
                        if( (asTemp.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asCaption = asTemp.SubString(j+1, 2);
                            nSumHeight    += IMGSCREEN2->Canvas->TextHeight(asCaption);
                            j++;
                        }
                        else
                        {
                            asCaption = asTemp.SubString(j+1, 1);
                            nSumHeight    += IMGSCREEN2->Canvas->TextHeight(asCaption);
                        }
                    }
                    //=========================================================

					//=========================================================
					nStartW    -= nTextW;
//231103//
					nStartH = funcGetStartH(4, i, 0, nSumHeight);
//OLD//
//                    nStartH    = tPoint.y + (tScale.h - nSumHeight) / 2;//세로쓰기-중간//
					//=========================================================

                    if(bAllSharp)//전체삭제//
                        nAllSharp1    = nStartH;

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(시작)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp1    = nStartH;
					}
					//=========================================================

					//=========================================================
					for(int j = 0; j < nTxtLen; j++)
					{
                        if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asCaption = asData.SubString(j+1, 2);
							IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
                            j++;

                            //=========================================================
                            //minji@230201//[해결]%소유권이전%_성변경 => 처리 시 '이전'에만 취소선이 표시되는 문제 수정//
                            if(bPartSharp && j == nTxtLen-1)//세로쓰기 부분삭제 중 개행 전 종료지점//
                            {
                                nPartSharp2    = nStartH-1;
                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                                tempData.tpSTT.x    = nStartW + nTextW/2;
                                tempData.tpSTT.y    = nPartSharp1;
                                tempData.tpEND.x    = nStartW + nTextW/2;
                                tempData.tpEND.y    = nPartSharp2 + nTextH;
                                eData->m_vSharpPos.push_back(tempData);
                                //여기선 flag해제하면 안됨//
                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            }
                            //=========================================================
                        }
                        else
						{
							if(!bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(시작)//
                            {
                                bPartSharp    = true;
								nPartSharp1    = nStartH;
                                continue;
                            }
							else if(bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(종료)//
							{
                                nPartSharp2    = nStartH-1;
                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                                tempData.tpSTT.x    = nStartW + nTextW/2;
								tempData.tpSTT.y    = nPartSharp1;
                                tempData.tpEND.x    = nStartW + nTextW/2;
                                tempData.tpEND.y    = nPartSharp2;
                                eData->m_vSharpPos.push_back(tempData);
                                bPartSharp    = false;
                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                continue;
                            }
//241204//PlanToDelete//세로쓰기 취소선 처리//
//							else if(bPartSharp && j == 0)//세로쓰기 부분삭제 중 개행 후 시작지점//
//							{
//								nPartSharp1    = nStartH;
//								continue;
//							}
//							else if(bPartSharp && j == nTxtLen-1)//세로쓰기 부분삭제 중 개행 전 종료지점//
//							{
//								nPartSharp2    = nStartH-1;
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
//								tempData.tpSTT.x    = nStartW + nTextW/2;
//								tempData.tpSTT.y    = nPartSharp1;
//								tempData.tpEND.x    = nStartW + nTextW/2;
//								tempData.tpEND.y    = nPartSharp2;
//								eData->m_vSharpPos.push_back(tempData);
//								//여기선 flag해제하면 안됨//
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								continue;
//							}

                            asCaption = asData.SubString(j+1, 1);
                            IMGSCREEN2->Canvas->TextOutA(nStartW+m_nNumberL, nStartH, asCaption);
                        }

                        nStartH    += nTextH;
                    }

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(종료)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x    = nStartW + nTextW/2;
						tempData.tpSTT.y    = nPartSharp1;
						tempData.tpEND.x    = nStartW + nTextW/2;
						tempData.tpEND.y    = nPartSharp2;
						eData->m_vSharpPos.push_back(tempData);
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
					//=========================================================

					//220126//TEST//if(slComment->Count == 0)//211229//25031.36//%소유권이전_성명경정%
                    {
						//전체삭제//
                        if(bAllSharp)
                        {
							nAllSharp2    = nStartH-1;
							//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                            tempData.tpSTT.x    = nStartW + nTextW/2;
                            tempData.tpSTT.y    = nAllSharp1;
                            tempData.tpEND.x    = nStartW + nTextW/2;
                            tempData.tpEND.y    = nAllSharp2;
							eData->m_vSharpPos.push_back(tempData);
                            //bAllSharp    = false;
                            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                        }
                    }
                }

                delete slData;
                slData    = NULL;
            }

            //======================================================
            // 주석표시//
            int nCommentTextH    = 0;
			bool    bCommentAllSharp    = false;
            bool    bCommentPartSharp    = false;
            for(int m = 0; m < slComment->Count; m++)
            {
                asCaption        = slComment->Strings[m];

                if(asCaption.SubString(1, 1) == "#")//전체삭제//
                {
                    bCommentAllSharp    = true;
                    asData    = asCaption.Delete(1, 1);
                }
                else
                {
                    bCommentAllSharp    = false;
                }

                //211229//25031.36//%소유권이전_성명경정%
                if(asData.SubString(1, 1) == "%" && asData.SubString(asData.Length(), 1) == "%")//전체삭제를 부분삭제로 입력//
                {
                    bCommentAllSharp    = true;
                    asData    = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
                }
                else
                {
                    bCommentAllSharp    = false;
				}
                //======================================================
                //211201//#11//주석 취소선 적용//하단 표시로 위치가 REASON가 달라서 [11]로 표시하니 지우면 안 됨//
				int nCommentTextLen = asCaption.Length();
				TPoint tempPoint    = m_bsAlphaDoc8Share[7].tPoint;//231106//
				TScale tempScale    = m_bsAlphaDoc8Share[7].tScale;//231106//
				int nCommentW    	= tempPoint.x - 18 * tempScale.w;
				int nCommentH    	= tempPoint.y + tempScale.h + 14 + m * nCommentTextH + m_nTopBottomGap/*231106*/;
				int nPosSharp1    	= 0;
				int nPosSharp2    	= 0;
				bCommentPartSharp   = false;

				//-------------------------------------------------------------
				//231106//공유지연명부는 위, 아래폼이 동일하게 반복되므로 아래폼 위치를 보정해줘야 함//
				if(m >= 5 && m < 10)
				{
					nCommentW 	= tempPoint.x - 9 * tempScale.w + 20/*gap*/;//231111//12->9
					nCommentH   = tempPoint.y + tempScale.h + 14 + (m-5) * nCommentTextH + m_nTopBottomGap/*231106*/;
				}
//231111//주석 10개까지만 처리//
//				else if(m >= 10 && m < 15)
//				{
//					nCommentW 	= tempPoint.x - 6 * tempScale.w + 20/*gap*/;
//					nCommentH   = tempPoint.y + tempScale.h + 14 + (m-5) * nCommentTextH + m_nTopBottomGap/*231106*/;
//				}
				//-------------------------------------------------------------

                for(int n = 0; n < nCommentTextLen; n++)
                {
                    if(!bCommentPartSharp && asCaption.c_str()[n] =='%')//가로쓰기 부분삭제 시작지점//
					{
                        nPosSharp1    = n+1;
                        bCommentPartSharp    = true;
						nPartSharp1    = nCommentW + nTextW-1;
                        continue;
					}
                    else if(bCommentPartSharp && asCaption.c_str()[n] =='%')//가로쓰기 부분삭제 종료지점//
                    {
                        nPosSharp2    = n;

                        AnsiString  asTemp    = asCaption.SubString(nPosSharp1+1, nPosSharp2-nPosSharp1);
                        nPartSharp2        = nCommentW + IMGSCREEN2->Canvas->TextWidth(asTemp) + asTemp.Length();
                        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                        memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x    = nPartSharp1;
                        tempData.tpSTT.y    = nCommentH + nTextH/2;
                        tempData.tpEND.x    = nPartSharp2;
                        tempData.tpEND.y    = nCommentH + nTextH/2;
                        eData->m_vSharpPos.push_back(tempData);
                        bCommentPartSharp    = false;
                        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                        continue;
                    }
                }
                //comment---
                if(bCommentAllSharp)//211208//
                {
                    memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                    tempData.tpSTT.x    = nStartW + nTextW/2;
                    tempData.tpSTT.y    = nAllSharp1;
                    tempData.tpEND.x    = nStartW + nTextW/2;
                    tempData.tpEND.y    = nAllSharp2;
                    eData->m_vSharpPos.push_back(tempData);
                    //bAllSharp    = false;
				}
                //======================================================

				asCaption    = StringReplace(asCaption, "%", "", TReplaceFlags() << rfReplaceAll);
				nCommentTextH    = IMGSCREEN2->Canvas->TextHeight(asCaption)+1;
				//231106//IMGSCREEN2->Canvas->TextOutA(tempPoint.x-10*tempScale.w, tempPoint.y+tempScale.h+14+m*nCommentTextH, asCaption);
				IMGSCREEN2->Canvas->TextOutA(nCommentW, nCommentH, asCaption);//231106//
			}
			delete slComment;
            slComment    = NULL;
            //======================================================

            ::SetROP2 (hdc, oldro);
            ::DeleteObject( pen );
        }



//231114//
		//==============================================================
		//소유권보합폰트//
		m_fontRatio	= ::CreateFont(fontwidth/2 + 8, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
		hOldFontRatio  = (HFONT)::SelectObject(hdc, m_fontRatio);
		//==============================================================



		//##########################################################################################
        //#
		//# RATIO
        //#
        //##########################################################################################
        {
            //==============================================================
			//일반폰트//
            pen   = ::CreatePen(PS_SOLID, 1, cPenColor);
            ::SelectObject(hdc, pen);
            int oldro = ::SetROP2(hdc, R2_COPYPEN);
            ::SetBkMode(hdc, TRANSPARENT);
            ::SetTextColor(hdc, cPenColor);
            IMGSCREEN2->Canvas->Brush->Color    = clWhite;
            //==============================================================

			//==============================================================
			asData			= "";//한 셀 포함 문자//
			asCaption   	= "";//TextOut에 표기할 문자//
			asTemp         	= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen     	= 0;
			nTextW        	= 0;
			nTextH        	= 0;
			nStartW        	= 0;
			nStartH        	= 0;
			nSumH        	= 0;
			nPartSharp1    	= 0;
			nPartSharp2    	= 0;
			nAllSharp1      = 0;
			nAllSharp2      = 0;
			//위에서 한번 초기화//eData->m_vSharpPos.clear();
			//==============================================================

            bAllSharp    = false;
            bPartSharp    = false;

            //==========================================================================================
			tPoint  = m_bsAlphaDoc8Share[5].tPoint;
			tScale  = m_bsAlphaDoc8Share[5].tScale;
//231114//위치이동//가로쓰기-자동개행은 처음이라//
//데이터 작업 전 한번 체크하고 가로쓰기 가운데정렬 맞추려고//
//for-loop 안에서 IMGSCREEN2->Canvas->TextWidth를 다시해서 값이 틀어지므로//
//for-loop 안에서 체크하도록 위치 수정//
//			nTextW	= IMGSCREEN2->Canvas->TextWidth("분")+1;//임의글자로 체크//
//			nTextH  = IMGSCREEN2->Canvas->TextHeight("분")+1;//임의글자로 체크//
//=============================================================================

			//==========================================================================================

            for( int i = 0; i < (int)eData->m_vSHAREOWNRATIO.size(); i++)
            {
//=============================================================================
//231114//위치이동//가로쓰기-자동개행은 처음이라//
//데이터 작업 전 한번 체크하고 가로쓰기 가운데정렬 맞추려고//
//for-loop 안에서 IMGSCREEN2->Canvas->TextWidth를 다시해서 값이 틀어지므로//
//for-loop 안에서 체크하도록 위치 수정//
				nTextW	= IMGSCREEN2->Canvas->TextWidth("분")+1;//임의글자로 체크//
				nTextH  = IMGSCREEN2->Canvas->TextHeight("분")+1;//임의글자로 체크//
				nTextW = nTextW/2;
//=============================================================================

				asData = eData->m_vSHAREOWNRATIO[i].DATA;

                if(asData == "-")//NoData
                    continue;

				asData    = StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);
//				asData    = StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
                //=====================================================
                if(asData.SubString(1, 1) == "#")//전체삭제//
                {
                    bAllSharp    = true;
                    asData    = asData.Delete(1, 1);
                }
                else
                {
                    bAllSharp    = false;
                }
                //=====================================================

				//=========================================
				TStringList *slData         = new TStringList;
				slData    = new TStringList();

//231111//가로쓰기-중간-개행//==========================================================================================
				nTxtLen = asData.Length();
				nSumH    = 0;

				//=============================================================
				//231116//
				//개행 문자에 따른 줄바꿈기능//
				int nPos    = asData.Pos("_");
				if(nPos > 0)
				{
					while(nPos > 0)
					{
						asTemp     = asData.SubString(1, nPos-1);
						slData->Add(asTemp);
						asData  = asData.Delete(1, nPos);
						nPos    = asData.Pos("_");
					}
					if( !asData.IsEmpty() )
						slData->Add(asData);
				}
				//=============================================================

				//개행없는 데이터 처리//
				int nLineTxtLen    = 0;//Cell 높이와 nTextH로 한줄 글자 수 계산//
                int nLineTxtCnt    = 0;//한글과 숫자 Length()가 다르게 나오기 때문에 정확한 개행 길이만큼 계산이 안되서 사용//
				if(slData->Count == 0 && nTextW > 0)
				{
					nLineTxtLen    = tScale.w/nTextW;
					asTemp    = "";

					//길이에 따른 자동줄바꿈기능//
					for(int j = 0; j < nTxtLen; j++)
					{
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
//=============================================================================
//231117//
							AnsiString  asPartStr = asData.SubString(j+1, 4);
							if(asPartStr == "분지" || asPartStr == "분의" || asPartStr == "지분")
							{
								asTemp = asTemp    + asPartStr;
								if(asTemp.Length() >= 8)
								{
									slData->Add(asTemp);
									asTemp    = "";
									nLineTxtCnt    = 0;
								}
								else
								{
									nLineTxtCnt += 4;
								}
								j += 3;
							}
							else
//=============================================================================
							{
								asTemp = asTemp    + asData.SubString(j+1, 2);
								if(nLineTxtCnt >= nLineTxtLen-1)
								{
									slData->Add(asTemp);
									asTemp    = "";
									nLineTxtCnt    = 0;
								}
								else
								{
									nLineTxtCnt++;//231215//ReturnCode//세로쓰기는한글2글자로체킹할필요없다.//231117//++ -> +=2
								}
								j++;
							}
						}
						else
						{
							if(asData.c_str()[j] == '%')//부분삭제//
								continue;
							asTemp = asTemp + asData.SubString(j+1, 1);
							if(nLineTxtCnt >= nLineTxtLen-1)
							{
								slData->Add(asTemp);
								asTemp    = "";
								nLineTxtCnt    = 0;
							}
							else
							{
								nLineTxtCnt++;
							}
						}
					}
					if( !asTemp.IsEmpty() )
					{
						slData->Add(asTemp);
						asTemp    = "";
					}
				}
//231111//가로쓰기-중간-개행//==========================================================================================



				//==========================================================================================
				//실제표시//
//231103//
					nStartH = funcGetStartH(5, i, slData->Count, nTextH);
//OLD//
//                nStartH    = tPoint.y + (tScale.h - slData->Count * nTextH) / 2;
				//==========================================================================================

                for(int z = 0; z < slData->Count; z++)
				{
                    asData    = slData->Strings[z];

					asTemp    = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);//부분삭제처리전 '%'없는 TextWidth 위한 임시처리//
					nTextW    = IMGSCREEN2->Canvas->TextWidth(asTemp);
//231103//
					nStartW = funcGetStartW(5, i, slData->Count, nTextW);
//OLD//
//					nStartW    = tPoint.x - i*tScale.w + (tScale.w - nTextW) / 2;//가로쓰기-중간//
//					if(i >= 6)
//						nStartW    -= nMiddleWidth;

                    int nPartTextWidth    = 0;
                    nTxtLen = asData.Length();
                    for(int j = 0; j < nTxtLen; j++)
                    {
						if(!bPartSharp && asData.c_str()[j] =='%')//가로쓰기 부분삭제 시작지점//
                        {
                            bPartSharp    = true;
                            nPartSharp1    = nStartW + nPartTextWidth;//211229//25031.181.2//nPartSharp1    = nStartW;
                            continue;
                        }
                        else if(bPartSharp && asData.c_str()[j] =='%')//가로쓰기 부분삭제 종료지점//
                        {
                            nPartSharp2    = nStartW + nPartTextWidth-1;//211229//25031.181.2//nPartSharp2    = nStartW + nTextW-1;
                            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                            tempData.tpSTT.x    = nPartSharp1;
                            tempData.tpSTT.y    = nStartH + nTextH/2;
                            tempData.tpEND.x    = nPartSharp2;
                            tempData.tpEND.y    = nStartH + nTextH/2;
                            eData->m_vSharpPos.push_back(tempData);
                            bPartSharp    = false;
                            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            continue;
                        }
                        else if(bPartSharp && j == 0)//가로쓰기 부분삭제 중 개행 후 시작지점//
                        {
                            nPartSharp1    = nStartW;
                            continue;
                        }
						else if(bPartSharp && j == nTxtLen-1)//가로쓰기 부분삭제 중 개행 전 종료지점//
                        {
                            nPartSharp2    = nStartW-1;
                            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                            tempData.tpSTT.x    = nPartSharp1;
                            tempData.tpSTT.y    = nStartH + nTextH/2;
                            tempData.tpEND.x    = nPartSharp2;
                            tempData.tpEND.y    = nStartH + nTextH/2;
                            eData->m_vSharpPos.push_back(tempData);
                            //여기선 flag해제하면 안됨//
                            //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            continue;
                        }
                        else
                        {
                            asTemp    = asData.SubString(j, 1);
                            nPartTextWidth    += IMGSCREEN2->Canvas->TextWidth(asTemp);
                        }
                    }

                    asData        = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
                    asCaption     = asData;
                    IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);

                    nStartH    += nTextH;
                }

                delete slData;
                slData    = NULL;
            }
            ::SetROP2 (hdc, oldro);
            ::DeleteObject( pen );
        }



		//==============================================================
		//일반폰트//
		m_font	= ::CreateFont(fontwidth, 0, 0, 0, 900/*FALSE*/, FALSE, FALSE, 0, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, frmMain->m_asFontName.c_str() );
		hOldFont  = (HFONT)::SelectObject(hdc, m_font);
		//==============================================================



        //##########################################################################################
        //#
        //# ADDRESS
        //#
        //##########################################################################################
        {
            //==============================================================
            //일반폰트//
            pen   = ::CreatePen(PS_SOLID, 1, cPenColor);
            ::SelectObject(hdc, pen);
            int oldro = ::SetROP2(hdc, R2_COPYPEN);
            ::SetBkMode(hdc, TRANSPARENT);
			::SetTextColor(hdc, cPenColor);
            IMGSCREEN2->Canvas->Brush->Color    = clWhite;
            //==============================================================

			//==============================================================
			asData			= "";//한 셀 포함 문자//
			asCaption   	= "";//TextOut에 표기할 문자//
			asTemp         	= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen     	= 0;
			nTextW        	= 0;
			nTextH        	= 0;
			nStartW        	= 0;
			nStartH        	= 0;
			nSumH        	= 0;
			nPartSharp1    	= 0;
			nPartSharp2    	= 0;
			nAllSharp1      = 0;
			nAllSharp2      = 0;
			//위에서 한번 초기화//eData->m_vSharpPos.clear();
			//==============================================================

			bAllSharp   = false;
			bPartSharp  = false;
			bEven		= true;//close상태//

            //==========================================================================================
			tPoint  = m_bsAlphaDoc8Share[6].tPoint;
			tScale  = m_bsAlphaDoc8Share[6].tScale;
			nTextW	= IMGSCREEN2->Canvas->TextWidth("주")/*+1*/;//임의글자로 체크//
			nTextH  = IMGSCREEN2->Canvas->TextHeight("주")+1;//임의글자로 체크//
            //==========================================================================================

            for( int i = 0; i < (int)eData->m_vSHAREOWNADDRESS.size(); i++)
			{
				//231116//DEBUG//
				if(i >= 40)
				{
                    int a = 1;
                }


                asData = eData->m_vSHAREOWNADDRESS[i].DATA;

                if(asData == "-")//NoData
                    continue;

				asData    = StringReplace(asData, " ", "", TReplaceFlags() << rfReplaceAll);
				asData    = StringReplace(asData, "-", "|", TReplaceFlags() << rfReplaceAll);
                //=========================================================
                //211201//#6//주소에서 괄호삭제 기능 제거//41026.1.186.2
    //            asData    = StringReplace(asData, "(", "", TReplaceFlags() << rfReplaceAll);
    //            asData    = StringReplace(asData, ")", "", TReplaceFlags() << rfReplaceAll);
                //=========================================================


                //=====================================================
                if(asData.SubString(1, 1) == "#")//전체삭제//
                {
                    bAllSharp    = true;
                    asData    = asData.Delete(1, 1);
                }
                else
                {
                    bAllSharp    = false;
                }

                if(asData.SubString(1, 1) == "%" && asData.SubString(asData.Length(), 1) == "%")//전체삭제를 부분삭제로 입력//
                {
                    bAllSharp    = true;
                    asData    = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
                }
                else
                {
                    bAllSharp    = false;
                }
                //=====================================================

                //---
                nTxtLen = asData.Length();
                nSumH    = 0;

				TStringList *slData         = new TStringList;
				slData    = new TStringList();

                //개행없는 데이터 처리//
                int nLineTxtLen    = 0;//Cell 높이와 nTextH로 한줄 글자 수 계산//
                int nLineTxtCnt    = 0;//한글과 숫자 Length()가 다르게 나오기 때문에 정확한 개행 길이만큼 계산이 안되서 사용//
                if(slData->Count == 0 && nTextW > 0)
                {
                    nLineTxtLen    = tScale.h/nTextW;
                    asTemp    = "";

                    for(int j = 0; j < nTxtLen; j++)
                    {
						if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asTemp = asTemp    + asData.SubString(j+1, 2);
                            if(nLineTxtCnt >= nLineTxtLen-1)
                            {
                                slData->Add(asTemp);
                                asTemp    = "";
                                nLineTxtCnt    = 0;
                            }
                            else
                            {
								nLineTxtCnt++;//231215//ReturnCode//세로쓰기는한글2글자로체킹할필요없다.//231117//++ -> += 2
                            }
                            j++;
                        }
                        else
                        {
							//========================================================
                            //211201//#4//주소 개행('_')
                            if(asData.c_str()[j] == '_')
                            {
								if( !asTemp.IsEmpty() )//211208//31025.2.20.2//주소개행과 길이자동개행이 복합//
                                {
                                    slData->Add(asTemp);
                                    asTemp    = "";
                                    nLineTxtCnt    = 0;
                                }
                            }
                            else
                            {
                                //========================================================
                                //211201//#8//주소 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
								if(asData.c_str()[j] == '%')
                                {
									bEven	= !bEven;//241203//
									nLineTxtLen    = nLineTxtLen + 1;
                                }
                                //========================================================
                                asTemp = asTemp + asData.SubString(j+1, 1);
                                if(nLineTxtCnt >= nLineTxtLen-1)
                                {
                                    //========================================================
                                    //211201//#8//주소 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
									if( !bEven )//241203//
									{
										if(asData.c_str()[j+1] == '%')
										{
											bEven	= !bEven;//241203//
											nLineTxtLen    = nLineTxtLen + 1;
											asTemp = asTemp + asData.SubString(j+2, 1);
											j++;
										}
									}
									//========================================================
                                    slData->Add(asTemp);
                                    asTemp    = "";
                                    nLineTxtCnt    = 0;
                                }
                                else
                                {
									nLineTxtCnt++;
                                }
                            }
                        }
                    }
                    if( !asTemp.IsEmpty() )
                    {
                        slData->Add(asTemp);
                        asTemp    = "";
                    }
                }
                //=========================================================

                //======================================
				//실제표시//
//231103//
				nStartW = funcGetStartW(6, i, slData->Count, nTextW);
//OLD//
//				//211228//보정//32028.230//31039.18.1
//				if(i == 10)
//					nStartW    = tPoint.x - (i-1)*tScale.w - 20 - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
//				else if(i == 23)
//					nStartW    = tPoint.x - (i-1)*tScale.w - 12 - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
//				else
//				nStartW    = tPoint.x - (i-1)*tScale.w - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
//				if(i%2)//95/2를 보정하기 위함//
//					nStartW    -= 1;
//				//======================================
//				if(i >= 11)
//					nStartW    -= (nMiddleWidth + 31);//HERE!!!
//				//=========================================================
//				//220112//31039.18.1(부여두리)
//				if(slData->Count == 4)
//					nStartW -= 2;

                for(int z = 0; z < slData->Count; z++)
                {
                    asData    = slData->Strings[z];

                    nTxtLen = asData.Length();

					//=========================================================
					nStartW    -= nTextW;
//231103//
					nStartH    = funcGetStartH(6, i, 0, 0);//세로쓰기-상단//
//OLD//					nStartH    = tPoint.y;//세로쓰기-상단//
					//=========================================================

                    if(bAllSharp)//전체삭제//
                        nAllSharp1    = nStartH;

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(시작)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp1    = nStartH;
					}
					//=========================================================

					//=========================================================
                    for(int j = 0; j < nTxtLen; j++)
                    {
                        if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
						{
                            asCaption = asData.SubString(j+1, 2);
                            IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
                            j++;

//241204//PlanToDelete//세로쓰기 취소선 처리//
//							if(bPartSharp && j == 1)//세로쓰기 부분삭제 중 개행 후 시작지점//211201//#9//한글이라 2byte이므로 j==1로 체크//
//							{
//								nPartSharp1    = nStartH;
//								nStartH    += nTextH;//211208
//								continue;
//							}
//							else if(bPartSharp && j == nTxtLen-1)//세로쓰기 부분삭제 중 개행 전 종료지점//
//							{
//								nPartSharp2    = nStartH+nTextH-1;
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
//								tempData.tpSTT.x    = nStartW + nTextW/2;
//								tempData.tpSTT.y    = nPartSharp1;
//								tempData.tpEND.x    = nStartW + nTextW/2;
//								tempData.tpEND.y    = nPartSharp2;
//								eData->m_vSharpPos.push_back(tempData);
//								//여기선 flag해제하면 안됨//
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								continue;
//							}
						}
                        else
                        {
							if(!bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(시작)//
							{
                                bPartSharp    = true;
                                nPartSharp1    = nStartH;
                                continue;
                            }
							else if(bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(종료)//
							{
                                nPartSharp2    = nStartH-1;
                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                                tempData.tpSTT.x    = nStartW + nTextW/2;
                                tempData.tpSTT.y    = nPartSharp1;
                                tempData.tpEND.x    = nStartW + nTextW/2;
                                tempData.tpEND.y    = nPartSharp2;
                                eData->m_vSharpPos.push_back(tempData);
                                bPartSharp    = false;
                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                continue;
                            }
//241204//PlanToDelete//세로쓰기 취소선 처리//
//							else if(bPartSharp && j == 0)//세로쓰기 부분삭제 중 개행 후 시작지점//
//                            {
//                                nPartSharp1    = nStartH;
//                                //시작지점에 문자는 출력해야죠.//continue;
//                            }
//							else if(bPartSharp && j == nTxtLen-1)//세로쓰기 부분삭제 중 개행 전 종료지점//
//                            {
//                                nPartSharp2    = nStartH-1;
//                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
//								tempData.tpSTT.x    = nStartW + nTextW/2;
//                                tempData.tpSTT.y    = nPartSharp1;
//                                tempData.tpEND.x    = nStartW + nTextW/2;
//                                tempData.tpEND.y    = nPartSharp2;
//                                eData->m_vSharpPos.push_back(tempData);
//                                //여기선 flag해제하면 안됨//
//                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                continue;
//                            }

                            asCaption = asData.SubString(j+1, 1);
                            IMGSCREEN2->Canvas->TextOutA(nStartW+m_nNumberL, nStartH, asCaption);
                        }

                        nStartH    += nTextH;
                    }

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(종료)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x    = nStartW + nTextW/2;
						tempData.tpSTT.y    = nPartSharp1;
						tempData.tpEND.x    = nStartW + nTextW/2;
						tempData.tpEND.y    = nPartSharp2;
						eData->m_vSharpPos.push_back(tempData);
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
					//=========================================================

					//전체삭제-취소선//
                    if(bAllSharp)
                    {
						nAllSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                        tempData.tpSTT.x    = nStartW + nTextW/2;
                        tempData.tpSTT.y    = nAllSharp1;
                        tempData.tpEND.x    = nStartW + nTextW/2;
                        tempData.tpEND.y    = nAllSharp2;
						eData->m_vSharpPos.push_back(tempData);
                        //bAllSharp    = false;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
				}

                delete slData;
                slData    = NULL;
            }

            ::SetROP2 (hdc, oldro);
            ::DeleteObject( pen );
        }



        //##########################################################################################
        //#
        //# NAME
        //#
        //##########################################################################################
        {
            //==============================================================
            //일반폰트//
            pen   = ::CreatePen(PS_SOLID, 1, cPenColor);
            ::SelectObject(hdc, pen);
            int oldro = ::SetROP2(hdc, R2_COPYPEN);
            ::SetBkMode(hdc, TRANSPARENT);
            ::SetTextColor(hdc, cPenColor);
			IMGSCREEN2->Canvas->Brush->Color    = clWhite;
            //==============================================================

			//==============================================================
			asData			= "";//한 셀 포함 문자//
			asCaption   	= "";//TextOut에 표기할 문자//
			asTemp         	= "";//SubString, 길이체크 용으로 사용할 문자//
			nTxtLen     	= 0;
			nTextW        	= 0;
			nTextH        	= 0;
			nStartW        	= 0;
			nStartH        	= 0;
			nSumH        	= 0;
			nPartSharp1    	= 0;
			nPartSharp2    	= 0;
			nAllSharp1      = 0;
			nAllSharp2      = 0;
			//위에서 한번 초기화//eData->m_vSharpPos.clear();
			//==============================================================

			bAllSharp	= false;
            bPartSharp  = false;
			bEven		= true;//close상태//

            //==========================================================================================
			tPoint  = m_bsAlphaDoc8Share[7].tPoint;
			tScale  = m_bsAlphaDoc8Share[7].tScale;
			nTextW	= IMGSCREEN2->Canvas->TextWidth("이")/*+1*/;//임의글자로 체크//
			nTextH  = IMGSCREEN2->Canvas->TextHeight("이")+1;//임의글자로 체크//
            //==========================================================================================

            for( int i = 0; i < (int)eData->m_vSHAREOWNNAME.size(); i++)
            {
                asData = eData->m_vSHAREOWNNAME[i].DATA;

                if(asData == "-")//NoData
                    continue;

				asData = eFunc->funcStringReplaceDoc08(asData);//260518//
                //=====================================================
                if(asData.SubString(1, 1) == "#")//전체삭제//
                {
					bAllSharp	= true;
                    asData    	= asData.Delete(1, 1);
                }
                else
                {
					bAllSharp    = false;
                }
                //=====================================================

                //---
                nTxtLen = asData.Length();
                nSumH    = 0;

                TStringList *slData         = new TStringList;
                slData    = new TStringList();

                //개행없는 데이터 처리//
                int nLineTxtLen    = 0;//Cell 높이와 nTextH로 한줄 글자 수 계산//
                int nLineTxtCnt    = 0;//한글과 숫자 Length()가 다르게 나오기 때문에 정확한 개행 길이만큼 계산이 안되서 사용//
                if(slData->Count == 0 && nTextW > 0)
                {
                    nLineTxtLen    = tScale.h/nTextW;
                    asTemp    = "";

                    for(int j = 0; j < nTxtLen; j++)
					{
                        if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asTemp = asTemp    + asData.SubString(j+1, 2);
                            if(nLineTxtCnt >= nLineTxtLen-1)
                            {
                                slData->Add(asTemp);
                                asTemp    = "";
                                nLineTxtCnt    = 0;
                            }
                            else
                            {
								nLineTxtCnt++;//231215//ReturnCode//세로쓰기는한글2글자로체킹할필요없다.//231117//++ -> += 2
                            }
                            j++;
                        }
                        else
                        {
                            //================================================
                            //211201//#14//
                            //개행 문자에 따른 줄바꿈기능//
                            //========================================================
                            //211201//#4//주소 개행('_')
                            if(asData.c_str()[j] == '_')
                            {
                                slData->Add(asTemp);
                                asTemp    = "";
                                nLineTxtCnt    = 0;
                            }
                            else
                            //========================================================
                            {
                                //========================================================
                                //211201//#8//이름 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
								if(asData.c_str()[j] == '%')
                                {
									bEven	= !bEven;//241203//
									nLineTxtLen    = nLineTxtLen + 1;
                                }
                                //========================================================

                                //211101//
        //                        if(asData.c_str()[j] == '%')//부분삭제//
        //                            continue;
                                asTemp = asTemp + asData.SubString(j+1, 1);
                                if(nLineTxtCnt >= nLineTxtLen-1)
                                {
                                    //========================================================
									//211201//#8//이름 부분삭제 시 길이체크에 ('%')이 영향을 받기에 처리//
									if( !bEven )//241203//
									{
										if(asData.c_str()[j+1] == '%')
										{
											bEven	= !bEven;//241203//
											nLineTxtLen    = nLineTxtLen + 1;
											asTemp = asTemp + asData.SubString(j+2, 1);
											j++;
										}
									}
									//========================================================
                                    slData->Add(asTemp);
                                    asTemp    = "";
                                    nLineTxtCnt    = 0;
                                }
                                else
                                {
									nLineTxtCnt++;
                                }
                            }
                            //================================================
    //                        //길이에 따른 자동줄바꿈기능//
    //                        //211101//
    ////                        if(asData.c_str()[j] == '%')//부분삭제//
	////                            continue;
    //                        asTemp = asTemp + asData.SubString(j+1, 1);
    //                        if(nLineTxtCnt >= nLineTxtLen-1)
    //                        {
    //                            slData->Add(asTemp);
    //                            asTemp    = "";
    //                            nLineTxtCnt    = 0;
    //                        }
    //                        else
    //                        {
    //                            nLineTxtCnt++;
    //                        }
                        }
                    }
                    if( !asTemp.IsEmpty() )
                    {
                        slData->Add(asTemp);
                        asTemp    = "";
                    }
                }
                //=========================================================

				//======================================
				//실제 표시//
//231103//
				nStartW = funcGetStartW(7, i, slData->Count, nTextW);
//OLD//
//				//211228//보정//32028.230//31039.18.1
//                if(i == 10)
//					nStartW    = tPoint.x - (i-1)*tScale.w - 20 - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
//                else if(i == 23)
//					nStartW    = tPoint.x - (i-1)*tScale.w - 12 - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
//                else
//                nStartW    = tPoint.x - (i-1)*tScale.w - (tScale.w - slData->Count*nTextW)/2;//세로쓰기-중간//
//				if(i%2)//95/2를 보정하기 위함//
//                    nStartW    -= 1;
//                //======================================
//				if(i >= 11)
//					nStartW    -= (nMiddleWidth + 31);
//				//=========================================================

				for(int z = 0; z < slData->Count; z++)
				{
                    asData    = slData->Strings[z];

                    nTxtLen = asData.Length();

                    //=========================================================
                    //Height 계산//
                    int nSumHeight    = 0;
                    asTemp    = StringReplace(asData, "%", "", TReplaceFlags() << rfReplaceAll);
                    for(int j = 0; j < asTemp.Length(); j++)
                    {
                        if( (asTemp.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asCaption = asTemp.SubString(j+1, 2);
                            nSumHeight    += IMGSCREEN2->Canvas->TextHeight(asCaption);
                            j++;
                        }
                        else
                        {
                            asCaption = asTemp.SubString(j+1, 1);
                            nSumHeight    += IMGSCREEN2->Canvas->TextHeight(asCaption);
                        }
                    }
					//=========================================================

					//=========================================================
					nStartW    -= nTextW;
//231103//
					nStartH = funcGetStartH(7, i, 0, nSumHeight);
//OLD//
//                    nStartH    = tPoint.y + (tScale.h - nSumHeight) / 2;//세로쓰기-중간//
					//=========================================================

					if(bAllSharp)//전체삭제//
                        nAllSharp1    = nStartH;

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(시작)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp1    = nStartH;
					}
					//=========================================================

					//=========================================================
                    for(int j = 0; j < nTxtLen; j++)
                    {
                        if( (asData.c_str()[j] & 0x80) == 0x80 )// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
                        {
                            asCaption = asData.SubString(j+1, 2);
                            IMGSCREEN2->Canvas->TextOutA(nStartW, nStartH, asCaption);
                            j++;

//241204//PlanToDelete//세로쓰기 취소선 처리//
//							if(bPartSharp && j == 1)//세로쓰기 부분삭제 중 개행 후 시작지점//211201//#9//41026.1.75//한글이라 2byte이므로 j==1로 체크//
//							{
//								nPartSharp1    = nStartH;
//								nStartH    += nTextH;//211208
//								continue;
//							}
//							else if(bPartSharp && j == nTxtLen-1)//세로쓰기 부분삭제 중 개행 전 종료지점//
//							{
//								nPartSharp2    = nStartH+nTextH-1;
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
//								tempData.tpSTT.x    = nStartW + nTextW/2;
//								tempData.tpSTT.y    = nPartSharp1;
//								tempData.tpEND.x    = nStartW + nTextW/2;
//								tempData.tpEND.y    = nPartSharp2;
//								eData->m_vSharpPos.push_back(tempData);
//								//여기선 flag해제하면 안됨//
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								continue;
//							}
                        }
                        else
						{
							if(!bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(시작)//
                            {
                                bPartSharp    = true;
                                nPartSharp1    = nStartH;
                                continue;
							}
							else if(bPartSharp && asData.c_str()[j] =='%')//세로쓰기 취소선 처리(종료)//
                            {
                                nPartSharp2    = nStartH-1;
                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
                                tempData.tpSTT.x    = nStartW + nTextW/2;
                                tempData.tpSTT.y    = nPartSharp1;
                                tempData.tpEND.x    = nStartW + nTextW/2;
                                tempData.tpEND.y    = nPartSharp2;
                                eData->m_vSharpPos.push_back(tempData);
                                bPartSharp    = false;
                                //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                continue;
                            }
//241204//PlanToDelete//세로쓰기 취소선 처리//
//							else if(bPartSharp && j == 0)//세로쓰기 부분삭제 중 개행 후 시작지점//
//							{
//								nPartSharp1    = nStartH;
//								continue;
//							}
//							else if(bPartSharp && j == nTxtLen-1)//세로쓰기 부분삭제 중 개행 전 종료지점//
//							{
//								nPartSharp2    = nStartH-1;
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
//								tempData.tpSTT.x    = nStartW + nTextW/2;
//								tempData.tpSTT.y    = nPartSharp1;
//								tempData.tpEND.x    = nStartW + nTextW/2;
//								tempData.tpEND.y    = nPartSharp2;
//								eData->m_vSharpPos.push_back(tempData);
//								//여기선 flag해제하면 안됨//
//								//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								continue;
//							}

                            asCaption = asData.SubString(j+1, 1);
							IMGSCREEN2->Canvas->TextOutA(nStartW+m_nNumberL, nStartH, asCaption);
                        }

                        nStartH    += nTextH;
                    }

					//=========================================================
					//241203//세로쓰기 취소선 처리 중 개행(종료)//
					//=========================================================
					if(bPartSharp)
					{
						nPartSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x    = nStartW + nTextW/2;
						tempData.tpSTT.y    = nPartSharp1;
						tempData.tpEND.x    = nStartW + nTextW/2;
						tempData.tpEND.y    = nPartSharp2;
						eData->m_vSharpPos.push_back(tempData);
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
					//=========================================================

					//전체삭제-취소선//
					if(bAllSharp)
                    {
						nAllSharp2    = nStartH-1;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
						memset(&tempData, 0x00, sizeof(SHARP_POSITION_STRUCT));
						tempData.tpSTT.x    = nStartW + nTextW/2;
                        tempData.tpSTT.y    = nAllSharp1;
                        tempData.tpEND.x    = nStartW + nTextW/2;
                        tempData.tpEND.y    = nAllSharp2;
                        eData->m_vSharpPos.push_back(tempData);
                        //bAllSharp    = false;
						//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					}
				}

                delete slData;
				slData    = NULL;
			}

            ::SetROP2 (hdc, oldro);
			::DeleteObject( pen );
		}



        //####################################################################################
        //Sharp
        //####################################################################################
        {
		    //------------------
            //일반폰트//
			penSharp   = ::CreatePen(PS_SOLID, frmMain->m_nSharpWidthPrint, cPenColorSharp);//HERE!!!
			::SelectObject(hdc, penSharp);
            int oldro1 = ::SetROP2(hdc, R2_COPYPEN);
            ::SetBkMode(hdc, TRANSPARENT);
            ::SetTextColor(hdc, cPenColorSharp);
			IMGSCREEN2->Canvas->Brush->Color    = clWhite;
            //------------------
            TPoint tpStt, tpEnd;
            for(int i = 0; i < (int)eData->m_vSharpPos.size(); i++)
            {
				tpStt    = eData->m_vSharpPos[i].tpSTT;
				tpEnd    = eData->m_vSharpPos[i].tpEND;
				::MoveToEx(hdc, tpStt.x, tpStt.y, NULL);
				::LineTo(hdc, tpEnd.x, tpEnd.y);
            }

			::SetROP2 (hdc, oldro1);
            ::DeleteObject( penSharp );
        }

		::SelectObject(hdc, hOldFont);
        ::DeleteObject(m_font);
        //####################################################################################
    }
}
//---------------------------------------------------------------------------

int __fastcall TfrmAlphaDoc8::funcGetStartW(int _nType, int _nIndex, int _nCount, int _nTextW)
{
	TPoint	tPoint;
	TScale  tScale;
	int nMiddleWidth	= m_nMiddleWidth;
	int nStartW    = 0;

	//==========================================================================================
	tPoint  = m_bsAlphaDoc8Share[_nType].tPoint;
	tScale  = m_bsAlphaDoc8Share[_nType].tScale;
	//==========================================================================================

	if(_nType <= 2)//동리, 지번//
	{
		nStartW    = tPoint.x + tScale.w - ((tScale.w - _nCount * _nTextW)/2);//세로쓰기-중간//
	}
	else if(_nType == 2 && _nCount > 0)//적요(괄호내용)//
	{
		nStartW    = tPoint.x + (tScale.w - _nTextW) / 2;//세로쓰기-중간//
	}
	else
	{
		if(frmMain->m_asFormatType == "A")
		{
			if(_nType != 5)//RATIO 외 항목//
			{
				if(_nIndex < 11)//[11 CELL]//index 11, 12은 입력화면서식맞춤용으로 '공란'//
					nStartW = tPoint.x - (_nIndex-1) * tScale.w - (tScale.w - _nCount * _nTextW) / 2;//세로쓰기-중간//
				else if(_nIndex >= 13 && _nIndex < 24)//[11 CELL]//index 24, 25은 입력화면서식맞춤용으로 '공란'//
					nStartW = tPoint.x - ((_nIndex-1) - 13) * tScale.w - (tScale.w - _nCount * _nTextW) / 2;//세로쓰기-중간//
				else if(_nIndex >= 26 && _nIndex < 39)//[13 CELL]//
					nStartW = tPoint.x - ((_nIndex-1) - 15) * tScale.w - (tScale.w - _nCount * _nTextW) / 2;//세로쓰기-중간//
				else if(_nIndex >= 39 && _nIndex < 52)//[13 CELL]//
					nStartW = tPoint.x - ((_nIndex-1) - 28) * tScale.w - (tScale.w - _nCount * _nTextW) / 2;//세로쓰기-중간//
			}
			else//RATIO//
			{
				if(_nIndex < 11)//[11 CELL]//index 11, 12은 입력화면서식맞춤용으로 '공란'//
					nStartW = tPoint.x - _nIndex * tScale.w + (tScale.w - _nTextW) / 2;//가로쓰기-중간//
				else if(_nIndex >= 13 && _nIndex < 24)//[11 CELL]//index 24, 25은 입력화면서식맞춤용으로 '공란'//
					nStartW = tPoint.x - (_nIndex - 13) * tScale.w + (tScale.w - _nTextW) / 2;//가로쓰기-중간//
				else if(_nIndex >= 26 && _nIndex < 39)//[13 CELL]//
					nStartW = tPoint.x - (_nIndex - 15) * tScale.w + (tScale.w - _nTextW) / 2;//가로쓰기-중간//
				else if(_nIndex >= 39 && _nIndex < 52)//[13 CELL]//
					nStartW = tPoint.x - (_nIndex - 28) * tScale.w + (tScale.w - _nTextW) / 2;//가로쓰기-중간//
			}

			if(_nIndex >= 26)
				nStartW    -= nMiddleWidth;
		}
		else if(frmMain->m_asFormatType == "B")
		{
			if(_nType != 5)//RATIO 외 항목//
			{
				if(_nIndex < 13)
					nStartW = tPoint.x - (_nIndex-1) * tScale.w - (tScale.w - _nCount * _nTextW) / 2;//세로쓰기-중간//
				else if(_nIndex >= 13 && _nIndex < 38)
					nStartW = tPoint.x - ((_nIndex-1) - 13) * tScale.w - (tScale.w - _nCount * _nTextW) / 2;//세로쓰기-중간//
				else if(_nIndex >= 39 && _nIndex < 51)
					nStartW = tPoint.x - ((_nIndex-1) - 26) * tScale.w - (tScale.w - _nCount * _nTextW) / 2;//세로쓰기-중간//
			}
			else
			{
				if(_nIndex < 13)
					nStartW = tPoint.x - _nIndex * tScale.w + (tScale.w - _nTextW) / 2;//가로쓰기-중간//
				else if(_nIndex >= 13 && _nIndex < 38)
					nStartW = tPoint.x - (_nIndex - 13) * tScale.w + (tScale.w - _nTextW) / 2;//가로쓰기-중간//
				else if(_nIndex >= 39 && _nIndex < 51)
					nStartW = tPoint.x - (_nIndex - 26) * tScale.w + (tScale.w - _nTextW) / 2;//가로쓰기-중간//
			}

			if(_nIndex >= 26)
				nStartW    -= nMiddleWidth;

			if(_nIndex % 2)//공유지연명부B Width=165.4로 애매하므로 두 개의 Cell 마다 1 pixcel 보정//
			{
				nStartW -= 1;
			}
		}
	}

	return nStartW;
}
//---------------------------------------------------------------------------

int __fastcall TfrmAlphaDoc8::funcGetStartH(int _nType, int _nIndex, int _nCount, int _nTextH)
{
	TPoint	tPoint;
	TScale  tScale;
	int nStartH    = 0;

	//==========================================================================================
	tPoint  = m_bsAlphaDoc8Share[_nType].tPoint;
	tScale  = m_bsAlphaDoc8Share[_nType].tScale;
	//==========================================================================================

	if(_nType == 0 || _nType == 1)//동리, 지번//
	{
		nStartH    = tPoint.y + (tScale.h - _nTextH) / 2;//중간
	}
	else if(_nType == 2)//적요//
	{
		nStartH    = tPoint.x + (tScale.h - _nTextH) / 2;//중간//
	}
	else
	{
		if(frmMain->m_asFormatType == "A")
		{
			if(_nType == 5)//RATIO//
			{
				if(_nIndex < 11 || (_nIndex >= 26 && _nIndex < 39))
					nStartH = tPoint.y + (tScale.h - _nCount * _nTextH) / 2;//Grid1
				else
					nStartH = tPoint.y + (tScale.h - _nCount * _nTextH) / 2 + m_nTopBottomGap;//Grid2
			}
			else if(_nType == 6)//ADDRESS//
			{
				if(_nIndex < 11 || (_nIndex >= 26 && _nIndex < 39))
					nStartH = tPoint.y;//Grid1
				else
					nStartH = tPoint.y + m_nTopBottomGap;//Grid2
			}
			else//RATIO, ADDRESS 외 항목//
			{
				if(_nIndex < 11 || (_nIndex >= 26 && _nIndex < 39))
					nStartH = tPoint.y + (tScale.h - _nTextH) / 2;//Grid1
				else
					nStartH = tPoint.y + (tScale.h - _nTextH) / 2 + m_nTopBottomGap;//Grid2
			}
		}
		else if(frmMain->m_asFormatType == "B")
		{
			if(_nType == 5)//RATIO//
			{
				if(_nIndex < 13 || (_nIndex >= 26 && _nIndex < 38))
					nStartH = tPoint.y + (tScale.h - _nCount * _nTextH) / 2;//Grid1
				else
					nStartH = tPoint.y + (tScale.h - _nCount * _nTextH) / 2 + m_nTopBottomGap;//Grid2
            }
			else if(_nType == 6)//ADDRESS//
			{
				if(_nIndex < 13 || (_nIndex >= 26 && _nIndex < 38))
					nStartH = tPoint.y;//Grid1
				else
					nStartH = tPoint.y + m_nTopBottomGap;//Grid2
			}
			else//RATIO, ADDRESS 외 항목//
			{
				if(_nIndex < 13 || (_nIndex >= 26 && _nIndex < 38))
					nStartH = tPoint.y + (tScale.h - _nTextH) / 2;//Grid1
				else
					nStartH = tPoint.y + (tScale.h - _nTextH) / 2 + m_nTopBottomGap;//Grid2
			}
		}
	}

	return nStartH;
}
//---------------------------------------------------------------------------

