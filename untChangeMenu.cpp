//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#pragma warn -8004

TfrmChangeMenu *frmChangeMenu;
//---------------------------------------------------------------------------
__fastcall TfrmChangeMenu::TfrmChangeMenu(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmChangeMenu::FormShow(TObject *Sender)
{
	this->Left	= frmMain->Left + frmMain->palMainSearchBar->Left + frmMain->palMainSearchBar->Width + 8;
	this->Top	= frmMain->Top + 80;//200313//panWindowsMove삭제//사장님Req//frmMain->panWindowsMove->Height + 80;//100

	m_nChkQryCnt 			= 0;
	m_nChkFavCnt 			= 0;
	m_nChkPoiCnt 			= 0;//241120//#DOCPOI#//PNU정보 존재 문서인지 체크할 것//
	m_bDetailSearching 		= false;
	m_nDetailSearchingIndex = 0;
	m_bMaxQryCheckMent		= false;

	funcLoadButtonImage();

	funcSettngMenu();
}
//---------------------------------------------------------------------------

void __fastcall TfrmChangeMenu::funcLoadButtonImage()
{
	AnsiString filename = "";
	TPngImage *imgPng;
	wchar_t wBufChk[64];
	TImage *tcmpChk;

	for(int i = 0; i < 2; i++)
	{
		imgPng = new TPngImage();
		filename.sprintf("%simgChkBox%d.png", frmMain->IMAGEMENUPATH, i+1);
		imgPng->LoadFromFile(filename);
		BITMAP_BTN_CHKBOX[i] 	= new Graphics::TBitmap();
		BITMAP_BTN_CHKBOX[i]->Assign(imgPng);
		delete imgPng;
		imgPng = NULL;
		//
		imgPng = new TPngImage();
		filename.sprintf("%simgFind%d.png", frmMain->IMAGEMENUPATH, i+1);
		imgPng->LoadFromFile(filename);
		BITMAP_BTN_FIND[i] 	= new Graphics::TBitmap();
		BITMAP_BTN_FIND[i]->Assign(imgPng);
		delete imgPng;
		imgPng = NULL;
	}

	for(int i = 1; i < DF_DOC_CNT; i++)
	{
		memset(wBufChk, 0, sizeof(wBufChk));
		swprintf(wBufChk, L"chkQry%02d", i);
		tcmpChk = (TImage*)this->FindComponent(wBufChk);
		if(tcmpChk != NULL)
		{
			tcmpChk->Picture->Bitmap->Handle	= NULL;
			tcmpChk->Picture					= NULL;
			tcmpChk->Picture->Bitmap->Assign(BITMAP_BTN_CHKBOX[0]);
		}
		//
		memset(wBufChk, 0, sizeof(wBufChk));
		swprintf(wBufChk, L"chkFav%02d", i);
		tcmpChk = (TImage*)this->FindComponent(wBufChk);
		if(tcmpChk != NULL)
		{
			tcmpChk->Picture->Bitmap->Handle	= NULL;
			tcmpChk->Picture					= NULL;
			tcmpChk->Picture->Bitmap->Assign(BITMAP_BTN_CHKBOX[0]);
		}
		//
		memset(wBufChk, 0, sizeof(wBufChk));
		swprintf(wBufChk, L"btnFnd%02d", i);
		tcmpChk = (TImage*)this->FindComponent(wBufChk);
		if(tcmpChk != NULL)
		{
			tcmpChk->Picture->Bitmap->Handle	= NULL;
			tcmpChk->Picture					= NULL;
			tcmpChk->Picture->Bitmap->Assign(BITMAP_BTN_FIND[0]);
		}
		//=====================================================================
		//241120//#DOCPOI#//울진군팀장님[REQ]//문서POI-사용자별 설정으로 표시//처음에는 설정정보 없으므로 Default는 QRYCHECK Value//
		//=====================================================================
		if(i < DF_DOC_CNT)//241211//[DOC20_YN]-1/*가감대장 제외*/)
		{
			memset(wBufChk, 0, sizeof(wBufChk));
			swprintf(wBufChk, L"chkPoi%02d", i);
			tcmpChk = (TImage*)this->FindComponent(wBufChk);
			if(tcmpChk != NULL)
			{
				tcmpChk->Picture->Bitmap->Handle	= NULL;
				tcmpChk->Picture					= NULL;
				tcmpChk->Picture->Bitmap->Assign(BITMAP_BTN_CHKBOX[0]);
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmChangeMenu::funcDeleteButtonImage()
{
	for(int i = 0; i < 2; i++)
	{
		delete BITMAP_BTN_CHKBOX[i];
		BITMAP_BTN_CHKBOX[i] = NULL;
		delete BITMAP_BTN_FIND[i];
		BITMAP_BTN_FIND[i] = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmChangeMenu::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(frmChangeMenu->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmChangeMenu::btnCloseTypeBClick(TObject *Sender)
{
	if(m_bDetailSearching)
	{
		if(frmMain->treSystem->Items->Count > 0)//메뉴변경에서 상세검색중 이미지 로딩하면 현재 form 종료하면서 띄운다//
		{
			frmMsg->funcMessageDlg("검색중 알림:", "상세검색 진행중입니다. 통합검색화면으로 이동할까요?", 1);
			if( frmMsg->m_bClick )
			{
				m_bDetailSearching	= false;
				frmMain->IMGTABClick(frmMain->IMGTAB00);
				Close();
			}
		}
		else
		{
			frmMsg->funcMessageDlg("검색중 알림:", "상세검색 진행중입니다. 종료할까요?", 1);
			if( frmMsg->m_bClick )
			{
				m_bDetailSearching	= false;
				frmMain->IMGTABClick(frmMain->IMGTAB00);
				Close();
			}
		}
	}
	else
	{
		if(frmMain->treSystem->Items->Count == 0)
		{
			frmMain->IMGTABClick(frmMain->IMGTAB00);
		}
		Close();
	}
}
//---------------------------------------------------------------------------

//int __fastcall TfrmChangeMenu::funcGetDocumentIndex(AnsiString _asDocName)
//{
//	int nIndex = -1;
//
//	if( _asDocName.IsEmpty() )
//		return nIndex;
//
//	for(int i = 1; i < DF_DOC_CNT; i++)
//	{
//		if(frmMain->INIINFO.DOCKINDNAME[i] == _asDocName)
//		{
//			nIndex = i;
//			break;
//		}
//	}
//
//	return nIndex;
//}
//---------------------------------------------------------------------------
//
//int __fastcall TfrmChangeMenu::funcGetDocPriorityIndex(AnsiString _asDocName)
//{
//	int nIndex = -1;
//
//	if( _asDocName.IsEmpty() )
//    	return nIndex;
//
//	for(int i = 1; i < DF_DOC_CNT; i++)
//	{
//		if(frmMain->INIINFO.DOCPRIORITY[i] == _asDocName)
//		{
//			nIndex = i;
//			break;
//        }
//	}
//
//	return nIndex;
//}
////---------------------------------------------------------------------------

void __fastcall TfrmChangeMenu::FormClose(TObject *Sender, TCloseAction &Action)
{
	frmMain->funcFreeEachButtonImage(frmMain->IMGTABSET);
	frmMain->IMGTABSET->Picture->Bitmap->Assign(frmMain->BITMAP_BTN_TAB[0][frmMain->TabNext]);

	m_nChkQryCnt 			= 0;
	m_nChkFavCnt 			= 0;
	m_nChkPoiCnt 			= 0;//241120//#DOCPOI#//PNU정보 존재 문서인지 체크할 것//
	m_nChkPoiDocNo			= -1;
	m_bDetailSearching 		= false;
	m_nDetailSearchingIndex = 0;
	m_bMaxQryCheckMent 		= false;

	funcDeleteButtonImage();

	for(int i = 1; i < DF_DOC_CNT; i++)
	{
		if( !frmMain->INIINFO.DOCKINDNAME[i].IsEmpty() )
		{
			frmMain->USERINI->WriteInteger("QUERY_CHECK", frmMain->INIINFO.DOCKINDNAME[i], frmMain->INIINFO.B_QRYCHECK[i]);
			frmMain->USERINI->WriteInteger("DOCFAVORITE", frmMain->INIINFO.DOCKINDNAME[i], frmMain->INIINFO.B_DOCFAVOR[i]);
			if(i < DF_DOC_CNT)//241211//[DOC20_YN]-1/*가감대장 제외*/)
			{
				frmMain->USERINI->WriteInteger("DOCPOI", frmMain->INIINFO.DOCKINDNAME[i], frmMain->INIINFO.B_DOCPOI[i]);//241120//#DOCPOI#//

				//241120//#DOCPOI#//문서심볼 선택한 문서가 1개인 경우, 폴더심볼(iconDocCnt##) 아닌 해당 문서 심볼(iconPoiDoc##)로 표기//
				if(frmMain->INIINFO.B_DOCPOI[i])
				{
					m_nChkPoiCnt++;
					if(m_nChkPoiCnt == 1)
						m_nChkPoiDocNo	= i;
					else
						m_nChkPoiDocNo	= -1;
				}
			}
		}
	}

	frmMain->funcSetTabButtons();

    frmMain->func_DrawImagePaint();//241125//설정 변경 후 지적도 갱신//
}
//---------------------------------------------------------------------------


void __fastcall TfrmChangeMenu::IMGHEADERMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(frmChangeMenu->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------
//
//
//void __fastcall TfrmChangeMenu::funcLoadButtonImage()
//{
//	AnsiString path = frmMain->ROOTPATH + "RES\\MENU\\";
//	AnsiString filename = "";
//	TPngImage *imgPng;
//	wchar_t wBufMnu[64];
//	TImage *tcmpMnu;
//	wchar_t wBufDn[64];
//	TImage *tcmpDn;
//	wchar_t wBufUp[64];
//	TImage *tcmpUp;
//	int		nTag;
//
//	//
//	imgPng = new TPngImage();
//	filename.sprintf("%sIMGDN.png", path);
//	imgPng->LoadFromFile(filename);
//	BITMAP_BTN_TABDN 	= new Graphics::TBitmap();
//	BITMAP_BTN_TABDN->Assign(imgPng);
//	delete imgPng;
//	imgPng = NULL;
//    //
//	imgPng = new TPngImage();
//	filename.sprintf("%sIMGUP.png", path);
//	imgPng->LoadFromFile(filename);
//	BITMAP_BTN_TABUP 	= new Graphics::TBitmap();
//	BITMAP_BTN_TABUP->Assign(imgPng);
//	delete imgPng;
//	imgPng = NULL;
//
//	for(int i = 1; i < 9/*DF_DOC_CNT*/; i++)
//	{
//		//
//		for(int j = 0; j < 2; j++)
//		{
//			imgPng = new TPngImage();
//			filename.sprintf("%sMenu%02d_%d.png", path, i, j+1);
//			imgPng->LoadFromFile(filename);
//			BITMAP_BTN_TABDOC[i][j] 	= new Graphics::TBitmap();
//			BITMAP_BTN_TABDOC[i][j]->Assign(imgPng);
//			delete imgPng;
//			imgPng = NULL;
//		}
//		//
//		memset(wBufDn, 0, sizeof(wBufDn));
//		swprintf(wBufDn, L"IMGDN%02d", i);
//		tcmpDn = (TImage*)this->FindComponent(wBufDn);
//		if(tcmpDn != NULL)
//		{
//			tcmpDn->Picture->Bitmap->Handle	= NULL;
//			tcmpDn->Picture					= NULL;
//			tcmpDn->Picture->Bitmap->Assign(BITMAP_BTN_TABDN);
//		}
//		//
//		memset(wBufUp, 0, sizeof(wBufUp));
//		swprintf(wBufUp, L"IMGUP%02d", i);
//		tcmpUp = (TImage*)this->FindComponent(wBufUp);
//		if(tcmpUp != NULL)
//		{
//			tcmpUp->Picture->Bitmap->Handle	= NULL;
//			tcmpUp->Picture					= NULL;
//			tcmpUp->Picture->Bitmap->Assign(BITMAP_BTN_TABUP);
//		}
//	}
//
//	for(int i = 1; i < 9/*DF_DOC_CNT*/; i++)
//	{
//		if(frmMain->INIINFO.DOCPRIORITY[i] == "")
//			break;
//
//		nTag = funcGetDocumentIndex(frmMain->INIINFO.DOCPRIORITY[i]);
//		if(nTag <= 0)
//			continue;
//
//		memset(wBufMnu, 0, sizeof(wBufMnu));
//		swprintf(wBufMnu, L"IMGMENU%02d", i);
//		tcmpMnu = (TImage*)this->FindComponent(wBufMnu);
//		if(tcmpMnu != NULL)
//		{
//			tcmpMnu->Picture->Bitmap->Handle	= NULL;
//			tcmpMnu->Picture					= NULL;
//			if( frmMain->INIINFO.B_DOCKIND[nTag] )//활성화문서이미지//
//				tcmpMnu->Picture->Bitmap->Assign(BITMAP_BTN_TABDOC[nTag][0]);
//			else//비활성화문서이미지//
//				tcmpMnu->Picture->Bitmap->Assign(BITMAP_BTN_TABDOC[nTag][1]);
//			tcmpMnu->Hint = frmMain->INIINFO.DOCKINDNAME[nTag];
//		}
//	}
//}
////---------------------------------------------------------------------------
//
//void __fastcall TfrmChangeMenu::funcDeleteButtonImage()
//{
//	for(int i = 0; i < 9/*DF_DOC_CNT*/; i++)
//	{
//		for(int j = 0; j < 2; j++)
//		{
//			delete BITMAP_BTN_TABDOC[i][j];
//			BITMAP_BTN_TABDOC[i][j] = NULL;
//		}
//	}
//
//	delete BITMAP_BTN_TABUP;
//	BITMAP_BTN_TABUP = NULL;
//	delete BITMAP_BTN_TABDN;
//	BITMAP_BTN_TABDN = NULL;
//}
////---------------------------------------------------------------------------


//void __fastcall TfrmChangeMenu::BTNUPClick(TObject *Sender)
//{
//	wchar_t wBufImg[64];
//	TImage *tcmpImg;
//	int nTag 				= dynamic_cast<TImage*>(Sender)->Tag;
//	int nSelTag = -1;//선택메뉴
//	int nBefTag = -1;//변경되어야 할 메뉴
//
//	memset(wBufImg, 0, sizeof(wBufImg));
//	swprintf(wBufImg, L"IMGMENU%02d", nTag);
//	tcmpImg = (TImage*)this->FindComponent(wBufImg);
//	if(tcmpImg != NULL)
//	{
//		nBefTag = tcmpImg->Tag;//윗 이미지 태그(몇번문서이미지가 있느냐)
//	}
//
//	if(nTag + 1 < 9/*DF_DOC_CNT*/)
//	{
//		memset(wBufImg, 0, sizeof(wBufImg));
//		swprintf(wBufImg, L"IMGMENU%02d", nTag+1);
//		tcmpImg = (TImage*)this->FindComponent(wBufImg);
//		if(tcmpImg != NULL)
//		{
//			nSelTag = tcmpImg->Tag;
//		}
//	}
//
//	if(nBefTag > -1 && nSelTag > -1)
//	{
//		memset(wBufImg, 0, sizeof(wBufImg));
//		swprintf(wBufImg, L"IMGMENU%02d", nTag);
//		tcmpImg = (TImage*)this->FindComponent(wBufImg);
//		if(tcmpImg != NULL)
//		{
//			tcmpImg->Picture->Bitmap->Handle	= NULL;
//			tcmpImg->Picture					= NULL;
//			tcmpImg->Picture->Bitmap->Assign(BITMAP_BTN_TABDOC[nSelTag][0]);
//			tcmpImg->Tag = nSelTag;
//			frmMain->INIINFO.DOCPRIORITY[nSelTag]	= frmMain->INIINFO.DOCKINDNAME[nTag];
//			tcmpImg->Hint = frmMain->INIINFO.DOCPRIORITY[nSelTag];
//		}
//		memset(wBufImg, 0, sizeof(wBufImg));
//		swprintf(wBufImg, L"IMGMENU%02d", nTag+1);
//		tcmpImg = (TImage*)this->FindComponent(wBufImg);
//		if(tcmpImg != NULL)
//		{
//			tcmpImg->Picture->Bitmap->Handle	= NULL;
//			tcmpImg->Picture					= NULL;
//			tcmpImg->Picture->Bitmap->Assign(BITMAP_BTN_TABDOC[nBefTag][0]);
//			tcmpImg->Tag = nBefTag;
//			frmMain->INIINFO.DOCPRIORITY[nBefTag]	= frmMain->INIINFO.DOCKINDNAME[nTag];
//			tcmpImg->Hint = frmMain->INIINFO.DOCPRIORITY[nBefTag];
//		}
//	}
//}
////---------------------------------------------------------------------------
//void __fastcall TfrmChangeMenu::BTNDNClick(TObject *Sender)
//{
//	wchar_t wBufImg[64];
//	TImage *tcmpImg;
//	int nTag 				= dynamic_cast<TImage*>(Sender)->Tag;
//	int nSelTag = -1;//선택메뉴
//	int nNxtTag = -1;//변경되어야 할 메뉴
//
//	memset(wBufImg, 0, sizeof(wBufImg));
//	swprintf(wBufImg, L"IMGMENU%02d", nTag);
//	tcmpImg = (TImage*)this->FindComponent(wBufImg);
//	if(tcmpImg != NULL)
//	{
//		nSelTag = tcmpImg->Tag;//현재 이미지 태그(몇번문서이미지가 있느냐)
//	}
//
//	if(nTag + 1 < 9/*DF_DOC_CNT*/)
//	{
//	    memset(wBufImg, 0, sizeof(wBufImg));
//	    swprintf(wBufImg, L"IMGMENU%02d", nTag+1);
//	    tcmpImg = (TImage*)this->FindComponent(wBufImg);
//	    if(tcmpImg != NULL)
//	    {
//		    nNxtTag = tcmpImg->Tag;
//	    }
//	}
//
//	if(nNxtTag > -1 && nSelTag > -1)
//	{
//		memset(wBufImg, 0, sizeof(wBufImg));
//		swprintf(wBufImg, L"IMGMENU%02d", nTag);
//		tcmpImg = (TImage*)this->FindComponent(wBufImg);
//		if(tcmpImg != NULL)
//		{
//			tcmpImg->Picture->Bitmap->Handle	= NULL;
//			tcmpImg->Picture					= NULL;
//			tcmpImg->Picture->Bitmap->Assign(BITMAP_BTN_TABDOC[nNxtTag][0]);
//			tcmpImg->Tag = nNxtTag;
//			frmMain->INIINFO.DOCPRIORITY[nNxtTag]	= frmMain->INIINFO.DOCKINDNAME[nTag];
//			tcmpImg->Hint = frmMain->INIINFO.DOCPRIORITY[nNxtTag];
//		}
//		memset(wBufImg, 0, sizeof(wBufImg));
//		swprintf(wBufImg, L"IMGMENU%02d", nTag+1);
//		tcmpImg = (TImage*)this->FindComponent(wBufImg);
//		if(tcmpImg != NULL)
//		{
//			tcmpImg->Picture->Bitmap->Handle	= NULL;
//			tcmpImg->Picture					= NULL;
//			tcmpImg->Picture->Bitmap->Assign(BITMAP_BTN_TABDOC[nSelTag][0]);
//			tcmpImg->Tag = nSelTag;
//			frmMain->INIINFO.DOCPRIORITY[nSelTag]	= frmMain->INIINFO.DOCKINDNAME[nTag];
//			tcmpImg->Hint = frmMain->INIINFO.DOCPRIORITY[nSelTag];
//		}
//	}
//}
//---------------------------------------------------------------------------

void __fastcall TfrmChangeMenu::btnFndClick(TObject *Sender)
{
	wchar_t wBufLbl[64];
	TLabel *tcmpLbl;
	wchar_t wBufFnd[64];
	TImage *tcmpFnd;
	wchar_t wBufTab[64];
	TImage *tcmpTab;
	int nTag 				= dynamic_cast<TImage*>(Sender)->Tag;

	if(nTag == m_nDetailSearchingIndex)
	{
		dynamic_cast<TImage*>(Sender)->Picture->Bitmap->Handle	= NULL;
		dynamic_cast<TImage*>(Sender)->Picture					= NULL;
		dynamic_cast<TImage*>(Sender)->Picture->Bitmap->Assign(BITMAP_BTN_FIND[0]);

		memset(wBufLbl, 0, sizeof(wBufLbl));
		swprintf(wBufLbl, L"lblDoc%02d", nTag);
		tcmpLbl = (TLabel*)this->FindComponent(wBufLbl);
		tcmpLbl->Font->Color = clBlack;
		tcmpLbl->Font->Style = TFontStyles() << fsBold;

		m_bDetailSearching = false;
		m_nDetailSearchingIndex = 0;
		return;
    }

	for(int i = 1; i < DF_DOC_CNT; i++)
	{
		memset(wBufFnd, 0, sizeof(wBufFnd));
		swprintf(wBufFnd, L"btnFnd%02d", i);
		tcmpFnd = (TImage*)this->FindComponent(wBufFnd);
		//
		memset(wBufLbl, 0, sizeof(wBufLbl));
		swprintf(wBufLbl, L"lblDoc%02d", i);
		tcmpLbl = (TLabel*)this->FindComponent(wBufLbl);
		//
		if(tcmpFnd != NULL)
		{
			tcmpFnd->Picture->Bitmap->Handle	= NULL;
			tcmpFnd->Picture					= NULL;
			if(i == nTag)
			{
				tcmpFnd->Picture->Bitmap->Assign(BITMAP_BTN_FIND[1]);
				//
				if(tcmpLbl != NULL)
				{
					if(tcmpLbl->Enabled)
					{
						tcmpLbl->Font->Color = clBlue;
						tcmpLbl->Font->Style = TFontStyles() << fsBold;
					}
				}
				//상세검색화면 띄운다//
				m_bDetailSearching = true;
				m_nDetailSearchingIndex = nTag;
				//
				memset(wBufTab, 0, sizeof(wBufTab));
				swprintf(wBufTab, L"IMGTAB%02d", i);
				tcmpTab = (TImage*)frmMain->FindComponent(wBufTab);
				frmMain->IMGTABClick(tcmpTab);
			}
			else
			{
				tcmpFnd->Picture->Bitmap->Assign(BITMAP_BTN_FIND[0]);
				//
				if(tcmpLbl != NULL)
				{
					if(tcmpLbl->Enabled)
					{
						tcmpLbl->Font->Color = clBlack;
						tcmpLbl->Font->Style = TFontStyles() << fsBold;
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmChangeMenu::chkQryClick(TObject *Sender)
{
	wchar_t wBufChkQry[64];
	TImage *tcmpChkQry;
	wchar_t wBufChkFav[64];
	TImage *tcmpChkFav;
	int nTag 				= dynamic_cast<TImage*>(Sender)->Tag;

	memset(wBufChkQry, 0, sizeof(wBufChkQry));
	swprintf(wBufChkQry, L"chkQry%02d", nTag);
	tcmpChkQry = (TImage*)this->FindComponent(wBufChkQry);
	if(tcmpChkQry != NULL)
	{
		if(frmMain->INIINFO.B_QRYCHECK[nTag])
		{
			m_nChkQryCnt--;
			frmMain->INIINFO.B_QRYCHECK[nTag] = false;
			tcmpChkQry->Picture->Bitmap->Handle	= NULL;
			tcmpChkQry->Picture					= NULL;
			tcmpChkQry->Picture->Bitmap->Assign(BITMAP_BTN_CHKBOX[0]);
			//210201//#IMGTAB2ROW
//			//통합검색 해제하면 즐겨찾기도 해제//
//			memset(wBufChkFav, 0, sizeof(wBufChkFav));
//			swprintf(wBufChkFav, L"chkFav%02d", nTag);
//			tcmpChkFav = (TImage*)this->FindComponent(wBufChkFav);
//			if(tcmpChkFav != NULL)
//			{
//				if(frmMain->INIINFO.B_DOCFAVOR[nTag])
//				{
//					m_nChkFavCnt--;
//					frmMain->INIINFO.B_DOCFAVOR[nTag] 	= false;
//					tcmpChkFav->Picture->Bitmap->Handle	= NULL;
//					tcmpChkFav->Picture					= NULL;
//					tcmpChkFav->Picture->Bitmap->Assign(BITMAP_BTN_CHKBOX[0]);
//				}
//			}
		}
		else
		{
			//통합검색 체크해도 즐겨찾기도 체크하지 않음//
			if(m_nChkQryCnt >= 5)
			{
				if( !m_bMaxQryCheckMent )
				{
					m_bMaxQryCheckMent = true;
					frmMsg->funcMessageDlg("통합검색 제한: " , "문서통합검색 선택은 속도에 영향을 주기에 5개까지만 권장합니다.", 3);
				}
			}
			m_nChkQryCnt++;
			frmMain->INIINFO.B_QRYCHECK[nTag] = true;
			tcmpChkQry->Picture->Bitmap->Handle	= NULL;
			tcmpChkQry->Picture					= NULL;
			tcmpChkQry->Picture->Bitmap->Assign(BITMAP_BTN_CHKBOX[1]);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmChangeMenu::chkFavClick(TObject *Sender)
{
	wchar_t wBufChkFav[64];
	TImage *tcmpChkFav;
//NotUsed//	wchar_t wBufChkQry[64];
//NotUsed//	TImage *tcmpChkQry;
	int nTag 				= dynamic_cast<TImage*>(Sender)->Tag;

	memset(wBufChkFav, 0, sizeof(wBufChkFav));
	swprintf(wBufChkFav, L"chkFav%02d", nTag);
	tcmpChkFav = (TImage*)this->FindComponent(wBufChkFav);
	if(tcmpChkFav != NULL)
	{
		if(frmMain->INIINFO.B_DOCFAVOR[nTag])//즐겨찾기 기설정->해제//
		{
			//210201//#IMGTAB2ROW//m_nChkFavCnt--;
			frmMain->INIINFO.B_DOCFAVOR[nTag] 	= false;
			tcmpChkFav->Picture->Bitmap->Handle	= NULL;
			tcmpChkFav->Picture					= NULL;
			tcmpChkFav->Picture->Bitmap->Assign(BITMAP_BTN_CHKBOX[0]);
			//즐겨찾기 해제해도 통합검색 해지하지 않음//
		}
		else//즐겨찾기 기해제->설정//
		{
			//210201//#IMGTAB2ROW//
//			if(m_nChkFavCnt >= 5)
//			{
//				frmMsg->funcMessageDlg("즐겨찾기 제한: " , "즐겨찾기는 최대 5개까지만 설정 가능합니다.", 3);
//				return;
//			}
//			if(m_nChkQryCnt >= 5)
//			{
//				if( !m_bMaxQryCheckMent )
//				{
//					m_bMaxQryCheckMent = true;
//					frmMsg->funcMessageDlg("통합검색 제한: " , "문서통합검색 선택은 속도에 영향을 주기에 5개까지만 권장합니다.", 3);
//				}
//			}

			//210201//#IMGTAB2ROW//m_nChkFavCnt++;
			frmMain->INIINFO.B_DOCFAVOR[nTag] 	= true;
			tcmpChkFav->Picture->Bitmap->Handle	= NULL;
			tcmpChkFav->Picture					= NULL;
			tcmpChkFav->Picture->Bitmap->Assign(BITMAP_BTN_CHKBOX[1]);

			//210201//#IMGTAB2ROW//
//			//즐겨찾기 체크하면 통합검색도 체크//
//			memset(wBufChkQry, 0, sizeof(wBufChkQry));
//			swprintf(wBufChkQry, L"chkQry%02d", nTag);
//			tcmpChkQry = (TImage*)this->FindComponent(wBufChkQry);
//			if(tcmpChkQry != NULL)
//			{
//				if(!frmMain->INIINFO.B_QRYCHECK[nTag])
//				{
//					m_nChkQryCnt++;
//					frmMain->INIINFO.B_QRYCHECK[nTag] 	= true;
//					tcmpChkQry->Picture->Bitmap->Handle	= NULL;
//					tcmpChkQry->Picture					= NULL;
//					tcmpChkQry->Picture->Bitmap->Assign(BITMAP_BTN_CHKBOX[1]);
//				}
//			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmChangeMenu::funcSettngMenu()
{
	wchar_t wBufLbl[64];
	TLabel *tcmpLbl;
	wchar_t wBufFnd[64];
	TImage *tcmpFnd;
	wchar_t wBufChkQry[64];
	TImage *tcmpChkQry;
	wchar_t wBufChkFav[64];
	TImage *tcmpChkFav;
	wchar_t wBufChkPoi[64];
	TImage *tcmpChkPoi;

	for(int i = 1; i < DF_DOC_CNT; i++)
	{
		//
		memset(wBufLbl, 0, sizeof(wBufLbl));
		swprintf(wBufLbl, L"lblDoc%02d", i);
		tcmpLbl = (TLabel*)this->FindComponent(wBufLbl);
		if(tcmpLbl != NULL)
		{
			tcmpLbl->Caption = frmMain->INIINFO.DOCKINDNAME[i];//201118//INI에 등록된 문서명 사용하기//
			tcmpLbl->Font->Color = clBlack;
			tcmpLbl->Font->Style = TFontStyles() << fsBold;

			memset(wBufFnd, 0, sizeof(wBufFnd));
			swprintf(wBufFnd, L"btnFnd%02d", i);
			tcmpFnd = (TImage*)this->FindComponent(wBufFnd);

			if(frmMain->INIINFO.B_DOCKIND[i])
			{
				tcmpLbl->Enabled = true;
				if(tcmpFnd != NULL)
					tcmpFnd->Enabled = true;
			}
			else
			{
				tcmpLbl->Enabled = false;
				if(tcmpFnd != NULL)
					tcmpFnd->Enabled = false;
			}
		}
		//
		memset(wBufChkQry, 0, sizeof(wBufChkQry));
		swprintf(wBufChkQry, L"chkQry%02d", i);
		tcmpChkQry = (TImage*)this->FindComponent(wBufChkQry);
		if(tcmpChkQry != NULL)
		{
			tcmpChkQry->Picture->Bitmap->Handle	= NULL;
			tcmpChkQry->Picture					= NULL;
			if(frmMain->INIINFO.B_QRYCHECK[i])
			{
				m_nChkQryCnt++;
				tcmpChkQry->Picture->Bitmap->Assign(BITMAP_BTN_CHKBOX[1]);
			}
			else
			{
				tcmpChkQry->Picture->Bitmap->Assign(BITMAP_BTN_CHKBOX[0]);
			}

			if(frmMain->INIINFO.B_DOCKIND[i])
				tcmpChkQry->Enabled = true;
			else
				tcmpChkQry->Enabled = false;
		}
		//
		memset(wBufChkFav, 0, sizeof(wBufChkFav));
		swprintf(wBufChkFav, L"chkFav%02d", i);
		tcmpChkFav = (TImage*)this->FindComponent(wBufChkFav);
		if(tcmpChkFav != NULL)
		{
			tcmpChkFav->Picture->Bitmap->Handle	= NULL;
			tcmpChkFav->Picture					= NULL;
			if(/*frmMain->INIINFO.B_QRYCHECK[i] &&*/ frmMain->INIINFO.B_DOCFAVOR[i])
			{
				//210201//#IMGTAB2ROW//m_nChkFavCnt++;
				tcmpChkFav->Picture->Bitmap->Assign(BITMAP_BTN_CHKBOX[1]);
			}
			else
			{
				tcmpChkFav->Picture->Bitmap->Assign(BITMAP_BTN_CHKBOX[0]);
			}

			if(frmMain->INIINFO.B_DOCKIND[i])
				tcmpChkFav->Enabled = true;
			else
				tcmpChkFav->Enabled = false;
		}
		//=====================================================================
		//241120//#DOCPOI#//울진군팀장님[REQ]//문서POI-사용자별 설정으로 표시//처음에는 설정정보 없으므로 Default는 QRYCHECK Value//
		//=====================================================================
		if(i < DF_DOC_CNT)//241211//[DOC20_YN]-1)/*가감대장 제외*/)
		{
			memset(wBufChkPoi, 0, sizeof(wBufChkPoi));
			swprintf(wBufChkPoi, L"chkPoi%02d", i);
			tcmpChkPoi = (TImage*)this->FindComponent(wBufChkPoi);
			if(tcmpChkPoi != NULL)
			{
				tcmpChkPoi->Picture->Bitmap->Handle	= NULL;
				tcmpChkPoi->Picture					= NULL;
				if(i != 11 && i != 15 && i != 18)//PNU 컬럼 없는 문서 제외(TB_KINDOFSYMBOL 참고)//
				{
					if(frmMain->INIINFO.B_DOCPOI[i])
					{
						tcmpChkPoi->Picture->Bitmap->Assign(BITMAP_BTN_CHKBOX[1]);
					}
					else
					{
						tcmpChkPoi->Picture->Bitmap->Assign(BITMAP_BTN_CHKBOX[0]);
					}
				}

				if(frmMain->INIINFO.B_DOCKIND[i])
					tcmpChkPoi->Enabled = true;
				else
					tcmpChkPoi->Enabled = false;
			}
		}
	}
}
//---------------------------------------------------------------------------

//241120//#DOCPOI#//
void __fastcall TfrmChangeMenu::chkPoiClick(TObject *Sender)
{
	wchar_t wBufChkPoi[64];
	TImage *tcmpChkPoi;
	wchar_t wBufChkQry[64];
	TImage *tcmpChkQry;
	int nTag 				= dynamic_cast<TImage*>(Sender)->Tag;

	if(nTag < DF_DOC_CNT)//241211//[DOC20_YN]-1/*가감대장 제외*/)
	{
		memset(wBufChkPoi, 0, sizeof(wBufChkPoi));
		swprintf(wBufChkPoi, L"chkPoi%02d", nTag);
		tcmpChkPoi = (TImage*)this->FindComponent(wBufChkPoi);
		if(tcmpChkPoi != NULL)
		{
			if(frmMain->INIINFO.B_DOCPOI[nTag])//문서심볼 기설정->해제//
			{
				frmMain->INIINFO.B_DOCPOI[nTag] 	= false;
				tcmpChkPoi->Picture->Bitmap->Handle	= NULL;
				tcmpChkPoi->Picture					= NULL;
				tcmpChkPoi->Picture->Bitmap->Assign(BITMAP_BTN_CHKBOX[0]);
			}
			else//문서심볼 기해제->설정//
			{
				frmMain->INIINFO.B_DOCPOI[nTag] 	= true;
				tcmpChkPoi->Picture->Bitmap->Handle	= NULL;
				tcmpChkPoi->Picture					= NULL;
				tcmpChkPoi->Picture->Bitmap->Assign(BITMAP_BTN_CHKBOX[1]);
			}
		}
	}
}
//---------------------------------------------------------------------------

