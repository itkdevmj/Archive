//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "bsPngImageList"
#pragma resource "*.dfm"


#include "common.h"

#pragma warn -8004

TfrmPreview *frmPreview;
//---------------------------------------------------------------------------
__fastcall TfrmPreview::TfrmPreview(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmPreview::FormCreate(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TfrmPreview::FormShow(TObject *Sender)
{
	this->Left	= frmMain->pnlSearchBar->Width + 4;
	this->Top	= 4;

	Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmPreview::FormClose(TObject *Sender, TCloseAction &Action)
{
	funcDeleteComponentsThumb();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPreview::btnCloseTypeBClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPreview::funcSetWaitWindows(bool bSetValue)
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

void __fastcall TfrmPreview::funcProcessThumb()
{
	if (!DirectoryExists(frmMain->THUMBPATH))
		CreateDir(frmMain->THUMBPATH);

	funcGotoPageThumb();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPreview::funcGotoPageThumb()
{
	funcDeleteComponentsThumb();
	funcCreateListThumb();

	//=============================================================
	int	nRet  	= 0;
	int	nSize	= (int)frmMain->m_vThumbPathList.size();
	int	nIndex	= -1;

	lblWait2->Caption  = "미리보기 이미지를 구성중입니다.";
	funcSetWaitWindows(true);

	//화면크기 조정//
	if(nSize > 50)
	{
		pnlMain->Width	= 1200 + 21;
		pnlMain->Height	= (frmMain->THUMBNAILSIZE + 20) * 5;
	}
	else
	{
		pnlMain->Height	= ((nSize+9)/10) * (frmMain->THUMBNAILSIZE + 20);
		pnlMain->Width	= 1200;
	}
	this->Width		= pnlMain->Width + 4;
	Shape1->Width	= this->Width;

    //썸네일 다운로드//
	try{
		nRet = frmFtpControl->FuncFtpGetFileThumb(true);
	}
	__finally{
		if(nRet == true)
		{
			for(int i = 0; i < nSize; i++)
			{
				if(cboPreviewDocKind->ItemIndex > 0)
				{
					AnsiString  asKindCode  = (char *)frmMain->m_vThumbPathList[i].KIND_CODE;//ThumbList
					AnsiString  asKindCode2	= cboPreviewDocKind2->Items->Strings[cboPreviewDocKind->ItemIndex];//Filter
					if(asKindCode != asKindCode2)
					{
						continue;
					}
				}

				nIndex++;
				funcMakeDynamicThumbnail(nIndex, i);
			}
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
void __fastcall TfrmPreview::funcCreateListThumb()
{
	if( pnlThumbList == NULL)
		pnlThumbList  = new TList();
	if( imgThumbList == NULL)
		imgThumbList  = new TList();
	if( lblThumbList == NULL)
		lblThumbList  = new TList();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPreview::funcDeleteComponentsThumb()
{
	//btnCreate4
	if(pnlThumbList != NULL)
	{
		for(int i = 0; i < pnlThumbList->Count; i++)
		{
			TPanel *pnlDC = (TPanel *)pnlThumbList->Items[i];
			if(pnlDC != NULL)
			{
				TImage *imgDocDC	= (TImage *)imgThumbList->Items[i];
				if(imgDocDC != NULL)
				{
					imgThumbList->Items[i] = NULL;
					delete imgDocDC;
					imgDocDC	= NULL;
				}

				TLabel *lblDocDC	= (TLabel *)lblThumbList->Items[i];
				if(lblDocDC != NULL)
				{
					lblThumbList->Items[i] = NULL;
					delete lblDocDC;
					lblDocDC	= NULL;
				}

				pnlThumbList->Items[i] = NULL;
				delete pnlDC;
				pnlDC	= NULL;
			}
		}

		imgThumbList->Clear();
		delete imgThumbList;
		imgThumbList = NULL;

		lblThumbList->Clear();
		delete lblThumbList;
		lblThumbList = NULL;

		pnlThumbList->Clear();
		delete pnlThumbList;
		pnlThumbList = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPreview::funcMakeDynamicThumbnail(int _nIndex, int _nVectorIdx)
{
	AnsiString 	asPageNo	= "";
	AnsiString 	asStr		= "";
	AnsiString 	asPathName 	= "";
	AnsiString 	asThumbFile = "";
	//download 받은 thumbnail경로//
	//200603//#11
	AnsiString 	asFileExt 	= "";
	int         nLeft		= 0;
	int         nTop		= 0;
	int         nWidth		= frmMain->THUMBNAILSIZE;
	int         nHeight		= frmMain->THUMBNAILSIZE;


	if(frmMain->INI_AS_THUMBEXT	== "JPG")
		asFileExt 	= ".jpg";
	else
		asFileExt 	= ".bmp";

	asThumbFile = (char *)frmMain->m_vThumbPathList[_nVectorIdx].PATH_NAME;
	asPathName	= asThumbFile;//FTP원본이미지경로//

	asThumbFile = ExtractFileName(asThumbFile);
	asThumbFile	= asThumbFile.SubString(1, asThumbFile.Pos(".")-1) + asFileExt;
	asThumbFile = frmMain->THUMBPATH + asThumbFile;

	//201202//썸네일 미 존재 시, NoImage표시//
//	if(!FileExists(asThumbFile))
//		return;

	//---
	TPanel *pnlDC 			= new TPanel(ScrollBox1);
	TImage *imgDocDC 		= new TImage(pnlDC);
	imgDocDC->Width			= frmMain->THUMBNAILSIZE;
	imgDocDC->Height		= frmMain->THUMBNAILSIZE;

	//201202//썸네일 미 존재 시, NoImage표시//
	if(!FileExists(asThumbFile) || asThumbFile.IsEmpty())
		imgDocDC->Picture->Bitmap->Assign(frmMain->BITMAP_BTN_ETC[frmMain->NoImage120]);
	else
		imgDocDC->Picture->LoadFromFile(asThumbFile);

	//=====================================================
	//Scale
	//=====================================================
	nLeft	= nWidth * (_nIndex % 10);
	nTop	= (nWidth + 20) * (_nIndex / 10);

	//=====================================================
	//Panel
	//=====================================================
	pnlDC->Align			= alNone;
	pnlDC->Tag 				= _nVectorIdx;
	//200623//pnlDC->Hint				= IntToStr(m_nViewDocNo);//문서번호(이동결의서:1)
	pnlDC->Caption			= "pnlDC" + IntToStr(_nIndex + 1);
	pnlDC->BevelKind    	= Controls::bkNone;
//	pnlDC->BevelKind		= bkFlat;
//	pnlDC->BevelEdges   	>> beLeft;
//	pnlDC->BevelEdges   	>> beTop;
//	pnlDC->BevelEdges   	>> beRight;
//	pnlDC->BevelEdges   	<< beBottom;
	pnlDC->BevelOuter 		= Controls::bvNone;
	pnlDC->SetBounds(nLeft, nTop, nWidth, nHeight + 20);
	pnlDC->ParentFont		= true;
	pnlDC->ParentBackground = false;
	pnlDC->Parent 			= ScrollBox1;
//??//	pnlDC->Hint				= frmMain->THUMBNAILSIZE;

	//=====================================================
	//Label
	//=====================================================
	TLabel *lblDocDC 		= new TLabel(pnlDC);//200623//(ScrollBox1);
	lblDocDC->Parent 		= pnlDC;
	lblDocDC->Tag 			= _nVectorIdx;
	if(frmMain->m_nViewDocNo == 2 || frmMain->m_nViewDocNo == 7)
	{
		asPageNo	= (char*)frmMain->m_vThumbPathList[_nVectorIdx].DOHO;
		//220315//DOC02.DOHO에 2개의 도호정보가 있는 경우에 오류발생//44710.31021.2.651.3, 4, 5//
		if(asPageNo.IsEmpty())	asPageNo	= "-";//220315//
		//220315//if(!asPageNo.IsEmpty())	asPageNo	= IntToStr(asPageNo.ToInt());
		asStr	= eFunc->funcGetKindCodeToKindName(frmMain->m_nViewDocNo, frmMain->m_vThumbPathList[_nVectorIdx].KIND_CODE);
		asStr	= asStr + "(도호:" + asPageNo + ")";
	}
	else
	{
		asPageNo	= (char*)frmMain->m_vThumbPathList[_nVectorIdx].PAGE_NO;
		if(!asPageNo.IsEmpty())
		{
			//201015//asPageNo	= IntToStr(asPageNo.ToInt());//201015//
			asPageNo	= eFunc->funcGetPageNoName(frmMain->m_nViewDocNo, asPageNo.c_str());//201015//
		}

		//201218//좌표계산부 첫페이지 표시 때문에 문서구분  '좌표계산부'를 00010으로 표시했으므로 관련하여 처리//
		if(frmMain->m_nViewDocNo == 18 && asPageNo == "00010")
		{
			asStr	= eFunc->funcGetKindCodeToKindName(frmMain->m_nViewDocNo, "01");
			asStr	= asStr + "(P:" + asPageNo + ")";
		}
		else
		{
			asStr	= eFunc->funcGetKindCodeToKindName(frmMain->m_nViewDocNo, frmMain->m_vThumbPathList[_nVectorIdx].KIND_CODE);
			asStr	= asStr + "(P:" + asPageNo + ")";
		}
	}

	lblDocDC->Caption 		= asStr;
	lblDocDC->Alignment		= taCenter;
	lblDocDC->SetBounds(4, 4, nWidth-8, 16);

	lblDocDC->ParentFont	= true;
	lblDocDC->Transparent   = true;
	if(_nVectorIdx == frmMain->m_nThumbCurrIndex && frmMain->m_nThumbCurrIndex != frmMain->m_nThumbPathIndex)
	{
		lblDocDC->Font->Style   = TFontStyles() << fsBold;
		lblDocDC->Font->Color	= clWhite;//clBlue;
		pnlDC->Color	  		= (TColor)RGB(51, 150, 255);
	}
	else if(_nVectorIdx == frmMain->m_nThumbPathIndex)
	{
		lblDocDC->Font->Style   = TFontStyles() << fsBold;
		lblDocDC->Font->Color	= clWhite;
		pnlDC->Color	  		= (TColor)RGB(243, 115, 33);//201020//(TColor)RGB(130, 192, 255);
	}
	else
	{
		lblDocDC->Font->Color	= clBlack;
		pnlDC->Color			= clCream;//200429
	}

	//=====================================================
	//IMAGE
	//=====================================================
	//---
	imgDocDC->Parent 		= pnlDC;
	imgDocDC->Tag 			= _nVectorIdx;
	imgDocDC->Hint          = IntToStr(frmMain->m_nViewDocNo);//문서번호(이동결의서:1);//200623//asPathName;//FTP원본이미지경로//
	imgDocDC->SetBounds((frmMain->THUMBNAILSIZE-imgDocDC->Picture->Width)/2+1, 20, imgDocDC->Picture->Width-2, imgDocDC->Picture->Height-2);
	imgDocDC->OnClick 		= imgThumbDC_onClick;
//
//	pnlDC->OnMouseEnter		= ScrollBox1MouseEnter;
//	lblDocDC->OnMouseEnter	= ScrollBox1MouseEnter;
//	imgDocDC->OnMouseEnter	= ScrollBox1MouseEnter;


	imgThumbList->Add(imgDocDC);
	lblThumbList->Add(lblDocDC);
	pnlThumbList->Add(pnlDC);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPreview::funcShowCurrentThumbLabel()
{
	if(pnlThumbList != NULL)
	{
		if(frmMain->m_nThumbCurrIndex < 0)
		{
			return;
		}

		//======================================================================
		//241015//#전주#중앙정보테크//
		//======================================================================
		int nSkinColor	= frmMain->SIDOINI->ReadInteger(L"FUNCTIONS", L"VALUE", (TColor)RGB(243, 115, 33));//16750131
		int nSkinColor2	= frmMain->SIDOINI->ReadInteger(L"FUNCTIONS", L"VALUE2", (TColor)RGB(51, 150, 255));//16760962
		for(int i = 0; i < pnlThumbList->Count; i++)
		{
			TPanel *pnlDC = (TPanel *)pnlThumbList->Items[i];
			if(pnlDC != NULL)
			{
				TLabel *lblDocDC 		= (TLabel *)lblThumbList->Items[i];
				if(lblDocDC != NULL)
				{
					if(pnlDC->Tag == frmMain->m_nThumbCurrIndex && frmMain->m_nThumbCurrIndex != frmMain->m_nThumbPathIndex)
					{
						lblDocDC->Font->Style   = TFontStyles() << fsBold;
						lblDocDC->Font->Color	= clWhite;//clBlue;
						pnlDC->Color	  		= (TColor)nSkinColor2;
						//pnlDC->BevelOuter 	= Controls::bvLowered;//200429
					}
					//201020//
					else if(pnlDC->Tag == frmMain->m_nThumbPathIndex)
					{
						lblDocDC->Font->Style   = TFontStyles() << fsBold;
						lblDocDC->Font->Color	= clWhite;
						pnlDC->Color	  		= (TColor)nSkinColor;
					}
					else
					{
						lblDocDC->Font->Style   = TFontStyles() >> fsBold;
						lblDocDC->Font->Color	= clBlack;
						pnlDC->Color	  		= clCream;//200429
						pnlDC->BevelOuter 		= Controls::bvNone;//200429
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

AnsiString __fastcall TfrmPreview::funcLoadImageThumb(AnsiString _asFilename)
{
	GetImageInfo		getImageInfo;

	memset(&getImageInfo, 0x00, sizeof(GetImageInfo));

	Graphics::TBitmap  	*bmpThumb;
	bmpThumb = NULL;

	Application->ProcessMessages();

	AnsiString asThumbFile	= "";

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
			bmpThumb->Width 	= frmMain->THUMBNAILSIZE;
			bmpThumb->Height 	= (int)((double)getImageInfo.nImageHeight * (double)dShortenRate);
		}
		else
		{
			dShortenRate = (double)frmMain->THUMBNAILSIZE / (double)getImageInfo.nImageHeight;
			bmpThumb->Width 	= (int)((double)getImageInfo.nImageWidth * (double)dShortenRate);
			bmpThumb->Height 	= frmMain->THUMBNAILSIZE;
		}

		::SetStretchBltMode(bmpThumb->Canvas->Handle, HALFTONE);
		::StretchDIBits(bmpThumb->Canvas->Handle,
					0, 0, bmpThumb->Width, bmpThumb->Height,
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
		asThumbFile = ExtractFileName(_asFilename);
		AnsiString asExt = ".bmp";
		int pos = asThumbFile.Pos(".");
		if (pos > 0) {
			asThumbFile = asThumbFile.SubString(1, pos-1);
		}
		asThumbFile = frmMain->THUMBPATH + asThumbFile + asExt;
		if(FileExists(asThumbFile))
			DeleteFile(asThumbFile);
		bmpThumb->SaveToFile(asThumbFile);
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

	return asThumbFile;
}
//---------------------------------------------------------------------------

/*
void __fastcall TfrmMain::imgThumbDC_onClick(TObject *Sender)
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

	m_nThumbCurrIndex = nTag;//200105

	AnsiString asPathName = "";//FTP원본이미지경로//
	asPathName = (char *)m_vThumbPathList[nTag].PATH_NAME;

	if( funcGetImage(asPathName, nSelDoc, 1) )
	{
		m_nFTPPathIndex 	= eFunc->funcGetDocFTPPathListIndex(asPathName);
		if(frmMain->m_nFTPPathIndex > -1)
			frmMain->funcSetFTPbtnPrevNext();//

		m_nThumbCurrIndex 	= eFunc->funcGetDocThumbPathListIndex(asPathName);
		if(m_nThumbCurrIndex > -1)
		{
			//funcProcessThumb();
			funcShowCurrentThumbLabel();
		}

		if(_CURRENT_WORKMODE != "DOCUMENT")
			IMGMODECHANGEClick(IMGMODECHANGEDOC);

		for(int i = 0; i < pnlThumbList->Count; i++)
		{

			TPanel *pnlDC1 = (TPanel *)pnlThumbList->Items[i];
			if(m_nThumbCurrIndex == pnlDC1->Tag)
			{
				nPnlIndex = i;
				break;
			}
		}

		if(nPnlIndex > -1)
		{
			//200623//TPanel *pnlDC = (TPanel *)pnlThumbList->Items[nPnlIndex];
			TImage *imgDC = (TImage *)imgThumbList->Items[nPnlIndex];
			if(imgDC != NULL)
			{
				nSelDoc = imgDC->Hint.ToInt();
				AnsiString asKwon 		= m_vThumbPathList[nTag].KWON_NO;
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
				palMainView->SetFocus();
		}
		//200805//palClient->SetFocus();
	}
}
//---------------------------------------------------------------------------
*/
void __fastcall TfrmPreview::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(this->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPreview::Timer1Timer(TObject *Sender)
{
	Timer1->Enabled = false;

	funcProcessThumb();

}
//---------------------------------------------------------------------------

void __fastcall TfrmPreview::imgThumbDC_onClick(TObject *Sender)
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
//	if(frmMain->m_nViewDocNo == 8)
//		frmMain->funcInitDoc08Bar(false);//#DOC08_INFO_ICON
	//==================================================

	frmMain->m_nThumbCurrIndex = nTag;//200105

	AnsiString asPathName = "";//FTP원본이미지경로//
	asPathName = (char *)frmMain->m_vThumbPathList[nTag].PATH_NAME;

	if( frmMain->funcGetImage(asPathName, nSelDoc, 1) )
	{
		frmMain->m_nFTPPathIndex 	= eFunc->funcGetDocFTPPathListIndex(asPathName);
		if(frmMain->m_nFTPPathIndex > -1)
			frmMain->funcSetPrevNextBar();//

		frmMain->m_nThumbCurrIndex 	= eFunc->funcGetDocThumbPathListIndex(asPathName);
		if(frmMain->m_nThumbCurrIndex > -1)
		{
			//funcProcessThumb();
			funcShowCurrentThumbLabel();
			frmMain->funcShowCurrentThumbLabel();
		}

		if(frmMain->_CURRENT_WORKMODE != "DOCUMENT")
			frmMain->IMGMODECHANGEClick(frmMain->IMGMODECHANGEDOC);

		for(int i = 0; i < pnlThumbList->Count; i++)
		{

			TPanel *pnlDC1 = (TPanel *)pnlThumbList->Items[i];
			if(frmMain->m_nThumbCurrIndex == pnlDC1->Tag)
			{
				nPnlIndex = i;
				break;
			}
		}

		if(nPnlIndex > -1)
		{
			//200623//TPanel *pnlDC = (TPanel *)pnlThumbList->Items[nPnlIndex];
			TImage *imgDC = (TImage *)imgThumbList->Items[nPnlIndex];
			if(imgDC != NULL)
			{
				nSelDoc = imgDC->Hint.ToInt();
				AnsiString asKwon 		= frmMain->m_vThumbPathList[nTag].KWON_NO;
				if(asKwon == "") asKwon = "0";
				frmSql->funcReadDocDBInfo(nSelDoc, asKwon, asPathName);
				//_nType : 1 => treSystemDblClick
				//_nType : 2 => FTP Prev/Next File Path DB Info Display //FTP 앞뒤이미지 DB속성정보//
				//_nType : 3 => PoiPopup>문서심볼클릭
				eMainSub->funcSetDBInfo(2);//231212//frmResultList->funcSetComponent3();

				//200407
				//#OWNNAMES#
				if(nSelDoc == 8 /*260616//NotUsed//&& frmMain->INI_B_OWNINFO*/)
				{
					frmMain->funcProcessDoc8OwnNames(asPathName);//#OWNINFO#
				}
			}
			//asPathName으로 ftpprevnext에서의 index 찾기//

			if(frmMain->IMGSCREEN2->Picture->Bitmap != NULL && frmMain->IMGSCREEN2->Picture->Bitmap->Width > 0)//220227
				frmMain->palMainView->SetFocus();
		}
		//200805//palClient->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmPreview::funcInitThumb()
{
	funcDeleteComponentsThumb();
	funcCreateListThumb();

//	frmMain->m_vThumbPathList.clear();
//	m_nThumbCount		= 0;
//	m_nThumbPathIndex 	= -1;
//	m_nThumbCurrIndex   = -1;
//	m_nPerThumbCnt		= 20;//201228//10->20//44270//Req//
//	m_bThumbChecked		= false;//201126//
//
//	funcDeleteComponentsThumb();
//	funcCreateListThumb();
//
//	//=======================================================
//	//201130//각 페이지당 전체체크여부//
//	pnlAllThumb->Visible	= false;
//	btnPreviewAct->Caption 	= "";
//	lblDownloadCnt->Caption	= "";
//	m_nDownloadCnt			= 0;
//	//=======================================================
}
//---------------------------------------------------------------------------


void __fastcall TfrmPreview::cboPreviewDocKindClick(TObject *Sender)
{
	funcGotoPageThumb();
}
//---------------------------------------------------------------------------

