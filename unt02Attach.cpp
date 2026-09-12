//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#pragma warn -8004
#pragma warn -8055

Tfrm02Attach *frm02Attach;
//---------------------------------------------------------------------------
__fastcall Tfrm02Attach::Tfrm02Attach(TComponent* Owner)
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
		//panWindowsMove->Color//
		this->panWindowsMove->Color			= (TColor)RGB(R, G, B);
		//pnlWaitT->Color//
	}


	PageControl1->ActivePage = tabQuery;
	bRegistMode = true;//등록
	m_asOpenFileDir = "";//190911//44760//req
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::FormCreate(TObject *Sender)
{
	clndSurvDtR->Left 		= 625;
	clndSurvDtR->Top  		= 200;
	clndInspctDtR->Left 	= 150;
	clndInspctDtR->Top  	= 200;
	clndSurvDt01->Left 		= 150;
	clndSurvDt01->Top  		= 170;
	clndSurvDt02->Left 		= 285;
	clndSurvDt02->Top  		= 170;
	clndInspctDt01->Left 	= 150;
	clndInspctDt01->Top  	= 200;
	clndInspctDt02->Left 	= 285;
	clndInspctDt02->Top  	= 200;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::FormShow(TObject *Sender)
{
	frmSql->funcSQLCreateTableInfoDoc02();
	frmSql->funcSQLCreateTableFileDoc02();
	frmSql->funcSQLCreateTableInfoDelDoc02();
	frmSql->funcSQLCreateTableFileDelDoc02();


	frmFileSave->m_asSelectedFullFileName = "";
	frmFileSave->m_nFileSize = 0;

	funcLoadButtonImage();

	frmMsg->Position = poScreenCenter;//200212

	m_nDocNameMaxLen = 60;//maxlength : 60
	m_nPathMaxLen  = 255;//maxlength : 255
	m_bMaxLength   = false;

	edtSidoCdQ->Text = frmMain->_SIDOCODE + " " + frmMain->_SIDONAME;//190910

	funcInitVariables();
	funcInitVariablesQuery();
	funcInitVariablesDetail();

	if(PageControl1->ActivePage == tabRegist)
	{
		if(bRegistMode) //등록
			funcInitVariables();
		else//수정
			funcLoadData();
	}
	else if(PageControl1->ActivePage == tabQuery)
	{
		funcInitVariablesQuery();
		InitDBGrid();
		funcInitVariablesDetail();
	}

	edtSidoCd->Text = frmMain->_SIDOCODE + " " + frmMain->_SIDONAME;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm02Attach::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(frmFileSave->Showing)
		frmFileSave->Close();

	funcInitPanelFileNm();

	funcInitVariables();
	funcInitVariablesQuery();
	funcInitVariablesDetail();

	pnlView->Height 	= 160;
	pnlList04->Height 	= 32;
	pnlFileNmD->Height 	= 32;
	ScrollBox1->Height	= 32;

	PageControl1->ActivePage = tabQuery;
	bRegistMode = true;//등록
	m_asOpenFileDir = "";//190911//44760//req

	funcDeleteButtonImage();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::funcLoadButtonImage()
{
	wchar_t wBufBtnDwnImg[64];
	TImage *tcmpBtnDwnImg;
	wchar_t wBufBtnAddImg[64];
	TImage *tcmpBtnAddImg;
	wchar_t wBufBtnAttImg[64];
	TImage *tcmpBtnAttImg;

	AnsiString filename = "";

	for(int i = 0; i < 2; i++)
	{
		filename = frmMain->IMAGEUIPATH + "02Attach_btnFind" + IntToStr(i) + ".bmp";
		BITMAP_02ATTACH_BTN_FIND[i] 	= new Graphics::TBitmap();
		BITMAP_02ATTACH_BTN_FIND[i]->LoadFromFile(filename);

		filename = frmMain->IMAGEUIPATH + "02Attach_btnQuery" + IntToStr(i) + ".bmp";
		BITMAP_02ATTACH_BTN_QUERY[i] 	= new Graphics::TBitmap();
		BITMAP_02ATTACH_BTN_QUERY[i]->LoadFromFile(filename);

		filename = frmMain->IMAGEUIPATH + "02Attach_btnInit" + IntToStr(i) + ".bmp";
		BITMAP_02ATTACH_BTN_INIT[i] 	= new Graphics::TBitmap();
		BITMAP_02ATTACH_BTN_INIT[i]->LoadFromFile(filename);

		filename = frmMain->IMAGEUIPATH + "02Attach_btnDownload" + IntToStr(i) + ".bmp";
		BITMAP_02ATTACH_BTN_DOWNLOAD[i] 	= new Graphics::TBitmap();
		BITMAP_02ATTACH_BTN_DOWNLOAD[i]->LoadFromFile(filename);

		//
		filename = frmMain->IMAGEUIPATH + "02Attach_btnList" + IntToStr(i) + ".bmp";
		BITMAP_02ATTACH_BTN_LIST[i] 	= new Graphics::TBitmap();
		BITMAP_02ATTACH_BTN_LIST[i]->LoadFromFile(filename);

		filename = frmMain->IMAGEUIPATH + "02Attach_btnRegist" + IntToStr(i) + ".bmp";
		BITMAP_02ATTACH_BTN_REGIST[i] 	= new Graphics::TBitmap();
		BITMAP_02ATTACH_BTN_REGIST[i]->LoadFromFile(filename);
	}

	for(int i = 0; i < 3; i++)
	{
		filename = frmMain->IMAGEUIPATH + "02Attach_btnModify" + IntToStr(i) + ".bmp";
		BITMAP_02ATTACH_BTN_MODIFY[i] 	= new Graphics::TBitmap();
		BITMAP_02ATTACH_BTN_MODIFY[i]->LoadFromFile(filename);

		filename = frmMain->IMAGEUIPATH + "02Attach_btnDelete" + IntToStr(i) + ".bmp";
		BITMAP_02ATTACH_BTN_DELETE[i] 	= new Graphics::TBitmap();
		BITMAP_02ATTACH_BTN_DELETE[i]->LoadFromFile(filename);

		//
		filename = frmMain->IMAGEUIPATH + "02Attach_btnAttach" + IntToStr(i) + ".bmp";
		BITMAP_02ATTACH_BTN_ATTACH[i] 	= new Graphics::TBitmap();
		BITMAP_02ATTACH_BTN_ATTACH[i]->LoadFromFile(filename);

		filename = frmMain->IMAGEUIPATH + "02Attach_btnAdd" + IntToStr(i) + ".bmp";
		BITMAP_02ATTACH_BTN_ADD[i] 	= new Graphics::TBitmap();
		BITMAP_02ATTACH_BTN_ADD[i]->LoadFromFile(filename);
	}

	for(int i = 0; i < 10; i++)
	{
		swprintf(wBufBtnDwnImg, L"btnDownload%02d", i+1);
		tcmpBtnDwnImg = (TImage*)this->FindComponent(wBufBtnDwnImg);
		tcmpBtnDwnImg->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_DOWNLOAD[0]);

		//
		swprintf(wBufBtnAttImg, L"btnAttach%02d", i+1);
		tcmpBtnAttImg = (TImage*)this->FindComponent(wBufBtnAttImg);
		tcmpBtnAttImg->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_ATTACH[0]);

		swprintf(wBufBtnAddImg, L"btnAttachAdd%02d", i+1);
		tcmpBtnAddImg = (TImage*)this->FindComponent(wBufBtnAddImg);
		tcmpBtnAddImg->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_ADD[0]);
	}

	//---
	TPngImage *imgPng = new TPngImage();
	filename = frmMain->IMAGEMAINPATH + "btnClose.png";
	imgPng->LoadFromFile(filename);
	BITMAP_BTN_CLOSE22 	= new Graphics::TBitmap();
	BITMAP_BTN_CLOSE22->Assign(imgPng);
	delete imgPng;
	imgPng = NULL;
	btnCloseTypeB->Picture->Bitmap->Assign(BITMAP_BTN_CLOSE22);

	//---
	btnFindQ->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_FIND[0]);
	btnQuery->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_QUERY[0]);
	btnInit->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_INIT[0]);
	btnWrite->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_REGIST[0]);
	btnMod->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_MODIFY[2]);
	btnDel->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_DELETE[2]);
	//
	btnFind->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_FIND[0]);
	btnList->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_LIST[0]);
	btnRegist->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_REGIST[0]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::funcDeleteButtonImage()
{
	for(int i = 0; i < 2; i++)
	{
		delete BITMAP_02ATTACH_BTN_FIND[i];
		BITMAP_02ATTACH_BTN_FIND[i] = NULL;
		delete BITMAP_02ATTACH_BTN_QUERY[i];
		BITMAP_02ATTACH_BTN_QUERY[i] = NULL;
		delete BITMAP_02ATTACH_BTN_INIT[i];
		BITMAP_02ATTACH_BTN_INIT[i] = NULL;
		delete BITMAP_02ATTACH_BTN_REGIST[i];
		BITMAP_02ATTACH_BTN_REGIST[i] = NULL;
		delete BITMAP_02ATTACH_BTN_DOWNLOAD[i];
		BITMAP_02ATTACH_BTN_DOWNLOAD[i] = NULL;
		//
		delete BITMAP_02ATTACH_BTN_LIST[i];
		BITMAP_02ATTACH_BTN_LIST[i] = NULL;
		delete BITMAP_02ATTACH_BTN_REGIST[i];
		BITMAP_02ATTACH_BTN_REGIST[i] = NULL;
	}

	for(int i = 0; i < 3; i++)
	{
		delete BITMAP_02ATTACH_BTN_MODIFY[i];
		BITMAP_02ATTACH_BTN_MODIFY[i] = NULL;
		delete BITMAP_02ATTACH_BTN_DELETE[i];
		BITMAP_02ATTACH_BTN_DELETE[i] = NULL;
		//
		delete BITMAP_02ATTACH_BTN_ATTACH[i];
		BITMAP_02ATTACH_BTN_ATTACH[i] = NULL;
		delete BITMAP_02ATTACH_BTN_ADD[i];
		BITMAP_02ATTACH_BTN_ADD[i] = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnQueryClick(TObject *Sender)
{
	funcSetWaitWindows(true);//210310//#ATTACH02_ETC_DEL//

	funcCheckDate();

	InitDBGrid();
	funcInitVariablesDetail();

	frmSql->funcSQLSelectSurveyAddQuery();

	lblQryCntT->Visible = true;
	lblQryCnt->Visible = true;
	lblQryCnt->Caption = m_vSurveyAddInfo.size();

	if(m_vSurveyAddInfo.size() > 0)
	{
		DisplayDBGrid();
	}

	funcSetWaitWindows(false);//210310//#ATTACH02_ETC_DEL//
}
//---------------------------------------------------------------------------
void __fastcall Tfrm02Attach::btnInitClick(TObject *Sender)
{
	funcInitVariablesQuery();
	InitDBGrid();
	funcInitVariablesDetail();
}
//---------------------------------------------------------------------------
//void __fastcall Tfrm02Attach::sgListDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, Grids::TGridDrawState State)
//{
//	TStringGrid  *pDBGrid   = (TStringGrid *)Sender;
//	TCanvas  *pCanvas   = pDBGrid->Canvas;
//	//--------------------------------------------------------------------------
//	AnsiString strValue = "";
//	TRect realRect;
//
//	realRect.left   = Rect.left;//   + 1;
//	realRect.top    = Rect.top;//    + 1;
//	realRect.right  = Rect.right  - 1;
//	realRect.bottom = Rect.bottom - 1;
//
//	strValue = pDBGrid->Cells[ACol][ARow];
//
//	int X = 0;
//	//--------------------------------------------------------------------------
//	if( ACol == 0 || ARow ==  0){
//		::SetTextAlign( pCanvas->Handle, TA_CENTER );
//		X = realRect.Left + ((realRect.Right - realRect.Left)/2);
//	}
//	else {
//		::SetTextAlign( pCanvas->Handle, TA_CENTER ); // TA_LEFT );
//		X = realRect.Left + ((realRect.Right - realRect.Left)/2);
//	}
//
//	//--------------------------------------------------------------------------
//	TColor crOldBrushColor = pCanvas->Brush->Color;
//	TColor crOldPenColor   = pCanvas->Pen->Color;
//
//	pCanvas->Pen->Color   = (TColor)RGB( 180, 180, 180 );
//	pCanvas->Rectangle(Rect);
//
//	//--------------------------------------------------------------------------
//	if(State.Contains(Grids::gdSelected)){
//		pCanvas->Brush->Color = (TColor)RGB( 253, 234, 166 );
//		pCanvas->Pen->Color   = (TColor)RGB( 241, 202,  88 );
//
//		TPenStyle OldPenStyle = pCanvas->Pen->Style;
//		pCanvas->Pen->Style   = psSolid;
//		pCanvas->Rectangle(realRect);
//		pCanvas->Pen->Style = OldPenStyle;
//	}
//	else {
//		if(ARow == 0 ){
//			pCanvas->Brush->Color = (TColor)RGB( 227, 230, 232 );
//			pCanvas->Font->Color  = (TColor)RGB( 0, 0, 0 );//
//			//pCanvas->Pen->Color   = (TColor)RGB( 0, 0, 0 );//(TColor)RGB( 255, 255, 255 );
//			pCanvas->Pen->Color   = (TColor)RGB( 255, 255, 255 );
//		}
//		else{
//			pCanvas->Brush->Color = (TColor)RGB( 251, 255, 255 );
//			pCanvas->Pen->Color   = (TColor)RGB( 251, 255, 255 );
//			pCanvas->Font->Color  = (TColor)RGB( 0, 0, 0 );//
//		}
//
//		pCanvas->FillRect(realRect);
//	}
//
//	pCanvas->Brush->Color = crOldBrushColor;
//	pCanvas->Pen->Color   = crOldPenColor;
//	//--------------------------------------------------------------------------
//
//	TBrushStyle nOldBrushStyle = pCanvas->Brush->Style;
//	int OldBkMode = ::SetBkMode( pCanvas->Handle, TRANSPARENT );
//	pCanvas->Brush->Style = bsClear;
//
//
//	//--------------------------------------------------------------------------
//	//190916
//	if(ARow != 0 && ACol == 2 && strValue.Length() > 28)//190215
//	{
//		AnsiString asStrPrev;
//		AnsiString asStrNext;
//		int nLength = strValue.Length();
//		int nMidIndex = nLength / 2;
//		if( (strValue.c_str()[nMidIndex] & 0x80) == 0x80 ) {// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
//			nMidIndex += 2; // 한글문자 다음 바이트로 넘김
//		}
//
//		pCanvas->Font->Size = 7;
//		asStrPrev = strValue.SubString(1, nMidIndex);
//		asStrNext = strValue.SubString(nMidIndex + 1, nLength - 1);
//		pCanvas->TextOut( X, realRect.Top + 1,  asStrPrev );
//		pCanvas->TextOut( X, realRect.Top + 10, asStrNext );
//	}
//	else
//	{
//		pCanvas->TextOut( X, realRect.Top + 5, strValue );
//	}
//
//	//--------------------------------------------------------------------------
//	pCanvas->Brush->Style = nOldBrushStyle;
//	::SetBkMode( pCanvas->Handle, OldBkMode );
//	//--------------------------------------------------------------------------
//}
////---------------------------------------------------------------------------
void __fastcall Tfrm02Attach::InitDBGrid()
{
	int nCol = 0;

	this->sgList->RowCount = 2;

	this->sgList->ColWidths[nCol++] =  40; // No
	this->sgList->ColWidths[nCol++] = 200; // 토지소재
	this->sgList->ColWidths[nCol++] = 280; // 결과도명
	this->sgList->ColWidths[nCol++] =  80; // 축척
	this->sgList->ColWidths[nCol++] =  90; // 측량일자
	this->sgList->ColWidths[nCol++] =  90; // 측량검사일자
	//210310//#ATTACH02_ETC_DEL//this->sgList->ColWidths[nCol++] =  80; // 비고

	// Cells[col][row]
	nCol = 0;
	this->sgList->Cells[nCol++][0] = L"No";
	this->sgList->Cells[nCol++][0] = L"토지소재";
	this->sgList->Cells[nCol++][0] = L"결과도명";
	this->sgList->Cells[nCol++][0] = L"축척";
	this->sgList->Cells[nCol++][0] = L"측량일자";
	this->sgList->Cells[nCol++][0] = L"측량검사일자";
	//210310//#ATTACH02_ETC_DEL//this->sgList->Cells[nCol++][0] = L"비고";

	for (int i = 1; i < this->sgList->RowCount; i++)
	{
		for (int j = 0; j < this->sgList->ColCount; j++)
		{
			this->sgList->Cells[j][i] = L"";
		}
	}

	this->sgList->RowCount = 2;
}
// ---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::DisplayDBGrid()
{
	AnsiString asGbn;
	AnsiString asStr;
	int nRow = 0;
	int nCol = 0;

	//================================================
	sgList->Invalidate();//210310//#ATTACH02_ETC_DEL//
	//================================================

	for (int i = 0; i < (int)m_vSurveyAddInfo.size(); i++) {
		nCol = 0;
		nRow = i + 1;

		asGbn = m_vSurveyAddInfo[i].REGIST_GBN;
		this->sgList->Cells[nCol++][nRow] = nRow;
		this->sgList->Cells[nCol++][nRow] = eFunc->funcPnuToBonbuName2(m_vSurveyAddInfo[i].PNU, 3);
		this->sgList->Cells[nCol++][nRow] = m_vSurveyAddInfo[i].DOC_NAME;
		this->sgList->Cells[nCol++][nRow] = eFunc->funcGetKindCodeToKindName(502, m_vSurveyAddInfo[i].SCALE_CD);
		asStr = (char*)m_vSurveyAddInfo[i].SURVEY_DATE;
		if( !asStr.IsEmpty() )
			asStr = asStr.SubString(1, 4) + "-" + asStr.SubString(5, 2) + "-" + asStr.SubString(7, 2);
		this->sgList->Cells[nCol++][nRow] = asStr;
		asStr = (char*)m_vSurveyAddInfo[i].INSPCT_DATE;
		if( !asStr.IsEmpty() )
			asStr = asStr.SubString(1, 4) + "-" + asStr.SubString(5, 2) + "-" + asStr.SubString(7, 2);
		this->sgList->Cells[nCol++][nRow] = asStr;
		this->sgList->Cells[nCol++][nRow] = m_vSurveyAddInfo[i].ETC_MEMO;//(asGbn == "1") ? "토지이동" : "기타";
		this->sgList->RowCount++;
	}

	//================================================
	sgList->Invalidate();//210310//#ATTACH02_ETC_DEL//
	//================================================

	this->sgList->RowCount--;

	if (this->sgList->RowCount > 1) {
		sgList->SetFocus();
		sgList->Row = 1;

		sgListClick(NULL);
		//funcLoadDataDetail();
	}
}
// ---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::sgListDblClick(TObject *Sender)
{
//	if((int)m_vSurveyAddInfo.size() > 0)
//	{
//		m_asRegistCdKey = m_vSurveyAddInfo[sgList->Row - 1].REGIST_CDKEY;
//
//		funcLoadDataDetail();
//	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::funcInitVariablesQuery()
{
	edtUmdRiCdQ->Text = "";
	edtUmdRiNmQ->Text = "";
	cboGbnQ->ItemIndex = 0;
	edtBonbunQ->Text = "";
	edtBoobunQ->Text = "";
	edtSurvDt01->Text = "";
	edtSurvDt02->Text = "";
	edtInspctDt01->Text = "";
	edtInspctDt02->Text = "";
	edtResultQ->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::edtMaxChange(TObject *Sender)
{
	AnsiString asSenderName = dynamic_cast<TComponent*>(Sender)->Name;
	int	nTag = dynamic_cast<TComponent*>(Sender)->Tag;

	if(m_bMaxLength == false)
	{
		TEdit *tcmpEdt;
		tcmpEdt = (TEdit*)this->FindComponent(asSenderName.c_str());

		AnsiString asTxt = tcmpEdt->Text;
		int nLength = asTxt.Length();

		if(nLength % 2)	nLength += 1;

		if (asSenderName == "edtResult" || asSenderName == "edtResultQ" || asSenderName == "edtEtc" || asSenderName.SubString(1, 11) == "edtAttachNm")//MaxLength : 60
		{
			if( nLength >= m_nDocNameMaxLen )
				m_bMaxLength = true;
		}
		else if (asSenderName.SubString(1, 13) == "edtAttachPath")//MaxLength : 255
		{
			if( nLength >= m_nPathMaxLen )
			    m_bMaxLength = true;
		}
    }
	else//delete text using VK_DELETE key
	{
		TEdit *tcmpEdt;
		tcmpEdt = (TEdit*)this->FindComponent(asSenderName.c_str());
		AnsiString asTxt = tcmpEdt->Text;
		int nLength = asTxt.Length();

		if(nLength == 0)
			m_bMaxLength = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::edtMaxKeyPress(TObject *Sender, wchar_t &Key)
{
	if( m_bMaxLength )
	{
		if(Key != 8 && Key != VK_DELETE && Key != VK_LEFT && Key != VK_RIGHT)
			Key = NULL;
		else
			m_bMaxLength = false;
	}
	else
	{
		if(Key == VK_RETURN)
		{
			if(Sender == edtResult)//maskedit가 enabled=false 상태라 setfocus가 안됨//부번 입력 후 파일 선택(btnInspct는 이미지라 focus 안됨)
				btnAttachClick(btnAttach01);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::edtBox_OnExit(TObject *Sender)
{
	m_bMaxLength = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::edtBox_OnEnter(TObject *Sender)
{
	m_bMaxLength = false;

	unsigned long Conversion, Sentence;
	HIMC Mode = ImmGetContext(Application->Handle);
	ImmGetConversionStatus(Mode, &Conversion, &Sentence);
	if (Conversion == IME_CMODE_HANGEUL) { 							// 현재모드가 한글이면 패스
	}
	else                                                         	// 현재모드가 한글이 아니면 한/영키 누른 효과를준다.
		ImmSetConversionStatus(Mode, IME_CMODE_HANGEUL, IME_CMODE_HANGEUL);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::edtUmdRiCdExit(TObject *Sender)
{
	AnsiString asResult = eFunc->funcPnuToUMDRIName(AnsiString(edtUmdRiCd->Text.Trim()).c_str(), false);
	if(asResult.IsEmpty())
	{
		edtUmdRiCd->Text	= "";
		edtUmdRiNm->Text	= "";
	}
	else
	{
		edtUmdRiNm->Text 	= asResult;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnSurvDt01Click(TObject *Sender)
{
	clndSurvDt01->Date = Now();
	clndSurvDt01->Visible   = true;
	clndSurvDt02->Visible   = false;
	clndInspctDt01->Visible = false;
	clndInspctDt02->Visible = false;

	clndSurvDt01->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnSurvDt02Click(TObject *Sender)
{
	clndSurvDt01->Visible   = false;
	clndSurvDt02->Date = Now();
	clndSurvDt02->Visible   = true;
	clndInspctDt01->Visible = false;
	clndInspctDt02->Visible = false;

	clndSurvDt02->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnInspctDt01Click(TObject *Sender)
{
	clndSurvDt01->Visible   = false;
	clndSurvDt02->Visible   = false;
	clndInspctDt01->Date 	= Now();
	clndInspctDt01->Visible = true;
	clndInspctDt02->Visible = false;

	clndInspctDt01->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnInspctDt02Click(TObject *Sender)
{
	clndSurvDt01->Visible   = false;
	clndSurvDt02->Visible   = false;
	clndInspctDt01->Visible = false;
	clndInspctDt02->Date = Now();
	clndInspctDt02->Visible = true;

	clndInspctDt02->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::clndSurvDt01DblClick(TObject *Sender)
{
	edtSurvDt01->Text = clndSurvDt01->Date.FormatString("YYYY.MM.DD");
	clndSurvDt01->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::clndSurvDt02DblClick(TObject *Sender)
{
	AnsiString asSurvDateStt = "";
	AnsiString asSurvDateEnd = "";

	edtSurvDt02->Text = clndSurvDt02->Date.FormatString("YYYY.MM.DD");

	asSurvDateStt = edtSurvDt01->Text.Trim();
	asSurvDateStt = StringReplace(asSurvDateStt, ".", "", TReplaceFlags()<<rfReplaceAll);
	asSurvDateEnd = edtSurvDt02->Text.Trim();
	asSurvDateEnd = StringReplace(asSurvDateEnd, ".", "", TReplaceFlags()<<rfReplaceAll);

	if( asSurvDateEnd < asSurvDateStt )
	{
		frmMsg->funcMessageDlg("알림:", "측량일자 종료일이 시작일보다 빠릅니다.", 3);
		edtSurvDt02->Text = "";
		clndSurvDt02->Visible = true;
		clndSurvDt02->BringToFront();
		return;
	}

	clndSurvDt02->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::clndInspctDt01DblClick(TObject *Sender)
{
	edtInspctDt01->Text = clndInspctDt01->Date.FormatString("YYYY.MM.DD");
	clndInspctDt01->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::clndInspctDt02DblClick(TObject *Sender)
{
	AnsiString asInspctDateStt = "";
	AnsiString asInspctDateEnd = "";

	edtInspctDt02->Text = clndInspctDt02->Date.FormatString("YYYY.MM.DD");

	asInspctDateStt = edtInspctDt01->Text.Trim();
	asInspctDateStt = StringReplace(asInspctDateStt, ".", "", TReplaceFlags()<<rfReplaceAll);
	asInspctDateEnd = edtInspctDt02->Text.Trim();
	asInspctDateEnd = StringReplace(asInspctDateEnd, ".", "", TReplaceFlags()<<rfReplaceAll);

	if( asInspctDateEnd < asInspctDateStt )
	{
		frmMsg->funcMessageDlg("알림:", "측량검사일자 종료일이 시작일보다 빠릅니다.", 3);
		edtInspctDt02->Text = "";
		clndInspctDt02->Visible = true;
		clndInspctDt02->BringToFront();
		return;
	}

	clndInspctDt02->Visible = false;
}
//---------------------------------------------------------------------------


void __fastcall Tfrm02Attach::clndMouseLeave(TObject *Sender)
{
	if (clndSurvDt01->Showing)
		clndSurvDt01->Visible = false;
	if (clndSurvDt02->Showing)
		clndSurvDt02->Visible = false;
	if (clndInspctDt01->Showing)
		clndInspctDt01->Visible = false;
	if (clndInspctDt02->Showing)
		clndInspctDt02->Visible = false;
	//
	if (clndSurvDtR->Showing)
		clndSurvDtR->Visible = false;
	if (clndInspctDtR->Showing)
		clndInspctDtR->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::edtBoobunQExit(TObject *Sender)
{
	if(edtBonbun->Text.Trim().Length() == 0)
	{
		frmMsg->funcMessageDlg("알림:", "본번을 입력해주세요.", 3);
		return;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::edtUmdRiCdQExit(TObject *Sender)
{
	AnsiString asResult = eFunc->funcPnuToUMDRIName(AnsiString(edtUmdRiCdQ->Text.Trim()).c_str(), false);
	if(asResult.IsEmpty())
	{
		edtUmdRiCdQ->Text	= "";
		edtUmdRiNmQ->Text	= "";
	}
	else
	{
		edtUmdRiNmQ->Text 	= asResult;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrm02Attach::btnModClick(TObject *Sender)
{
	bRegistMode = false;//수정
	funcInitVariables();
	PageControl1->ActivePage = tabRegist;
	PageControl1Change(NULL);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm02Attach::btnDelClick(TObject *Sender)
{
	AnsiString asCdkeySub = "";

	frmSql->funcSQLInsertSurveyAddInfo(DF_DELETE_RECORD);

	for(int i = 0; i < (int)m_vSurveyAddFile.size(); i++)
	{
		//asCdkeySub.sprintf("%03d", i+1);
		asCdkeySub = m_vSurveyAddFile[i].CDKEY_SUB;
		frmSql->funcSQLInsertSurveyAddFile(DF_DELETE_RECORD, asCdkeySub, 0, "");
	}

	btnQueryClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm02Attach::funcInitVariablesDetail()
{
	lblSidoSgg->Caption = "";
	lblLand->Caption = "";
	lblPnu->Caption = "";
	lblResult->Caption = "";
	lblScale->Caption = "";
	lblSurv->Caption = "";
	lblFileNm01->Caption = "";


	TLabel *tcmpLblPath;
	wchar_t wBufLblPath[30];
	TImage *tcmpBtnDwn;
	wchar_t wBufBtnDwn[30];
	TImage *tcmpImgDel;
	wchar_t wBufImgDel[30];

	funcInitPanelFileNm();

	btnMod->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_MODIFY[2]);
	btnDel->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_DELETE[2]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::funcLoadDataDetail()
{
	AnsiString asPnu = m_vSurveyAddInfo[sgList->Row - 1].PNU;

	lblSidoSgg->Caption = asPnu.SubString(1, 5);
	lblLand->Caption = asPnu.SubString(6, 5) + " " + eFunc->funcPnuToUMDRIName(asPnu.c_str(), false);
	lblPnu->Caption = eFunc->funcPnuToBonbuName2(asPnu.c_str(), 4);
	lblResult->Caption = m_vSurveyAddInfo[sgList->Row - 1].DOC_NAME;
	lblScale->Caption = eFunc->funcGetKindCodeToKindName(502, m_vSurveyAddInfo[sgList->Row - 1].SCALE_CD);
	lblSurv->Caption = m_vSurveyAddInfo[sgList->Row - 1].SURVEY_DATE;

	funcInitPanelFileNm();
	funcRedrawPanelFileNm();

	btnMod->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_MODIFY[0]);
	btnDel->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_DELETE[0]);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm02Attach::funcInitPanelFileNm()
{
	TLabel *tcmpLblPath;
	wchar_t wBufLblPath[30];
	TImage *tcmpBtnDwn;
	wchar_t wBufBtnDwn[30];
	TImage *tcmpImgDel;
	wchar_t wBufImgDel[30];
	int nIndex = 0;
	int nCount = 0;
	int nLabelGap = 24;
	AnsiString asFileName = "";

	for(int i = 0; i < 10; i++)
	{
		swprintf(wBufLblPath, L"lblFileNm%02d", i+1);
		tcmpLblPath = (TLabel*)this->FindComponent(wBufLblPath);
		tcmpLblPath->Caption = "";
		tcmpLblPath->Visible = false;

		swprintf(wBufBtnDwn, L"btnDownload%02d", i+1);
		tcmpBtnDwn = (TImage*)this->FindComponent(wBufBtnDwn);
		tcmpBtnDwn->Visible = false;

		swprintf(wBufImgDel, L"btnFileDel%02d", i+1);
		tcmpImgDel = (TImage*)this->FindComponent(wBufImgDel);
		tcmpImgDel->Visible = false;
	}

	//pnlMainQ->Height 	= 604;
	pnlView->Height 	= 160;
	pnlList04->Height 	= 32;
	pnlFileNmD->Height 	= 32;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm02Attach::funcRedrawPanelFileNm()
{
	TLabel *tcmpLblPath;
	wchar_t wBufLblPath[30];
	TImage *tcmpBtnDwn;
	wchar_t wBufBtnDwn[30];
	TImage *tcmpImgDel;
	wchar_t wBufImgDel[30];
	int nCount = 0;
	int nLabelGap = 24;
	AnsiString asFileName = "";

	if(sgList->Row > 1)
		m_nSgListIndex = sgList->Row - 1;

	frmSql->funcSQLSelectSurveyAddFile();

	nCount = m_vSurveyAddFile.size();

	if(nCount == 0)
	{
//		frm02Attach->Height 	= 630;
		pnlView->Height 		= 160;
		pnlList04->Height 		= 32;
		pnlFileNmD->Height 		= 32;
    }

	if(nCount > 1)
	{
//		frm02Attach->Height 	= 630 + nLabelGap * (nCount - 1);
//		pnlMainQ->Height 		= pnlMainQ->Height + nLabelGap * (nCount - 1);
//		pnlDetail->Height 		= pnlDetail->Height + nLabelGap * (nCount - 1);
		pnlView->Height 		= 160 + nLabelGap * (nCount - 1);
		pnlList04->Height 		= 32 + nLabelGap * (nCount - 1);
		pnlFileNmD->Height 		= 32 + nLabelGap * (nCount - 1);
	}

	for(int i = 0; i < nCount; i++)
	{
		swprintf(wBufLblPath, L"lblFileNm%02d", i+1);
		tcmpLblPath = (TLabel*)this->FindComponent(wBufLblPath);
		tcmpLblPath->Visible = true;

		swprintf(wBufBtnDwn, L"btnDownload%02d", i+1);
		tcmpBtnDwn = (TImage*)this->FindComponent(wBufBtnDwn);
		tcmpBtnDwn->Visible = true;

		swprintf(wBufImgDel, L"btnFileDel%02d", i+1);
		tcmpImgDel = (TImage*)this->FindComponent(wBufImgDel);
		tcmpImgDel->Visible = true;

		asFileName = m_vSurveyAddFile[i].PATH_NAME;
		asFileName = ExtractFileName(StringReplace(asFileName, "/", "\\", TReplaceFlags()<<rfReplaceAll));
		tcmpLblPath->Caption = asFileName;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnDownloadClick(TObject *Sender)
{
	int nTag = dynamic_cast<TImage*>(Sender)->Tag;

	if(frmFileSave->Showing == false)
	{
		frmFileSave->m_asSelectedFullFileName = m_vSurveyAddFile[nTag - 1].PATH_NAME;
		frmFileSave->m_asSelectedFullFileName = StringReplace(frmFileSave->m_asSelectedFullFileName, "/", "\\", TReplaceFlags()<<rfReplaceAll);
		frmFileSave->m_nFileSize = m_vSurveyAddFile[nTag - 1].FILE_SIZE;
		frmFileSave->Tag = nTag;
		frmFileSave->Show();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnFileDelClick(TObject *Sender)
{
	if (Application->MessageBox(L"선택한 파일을 삭제하시겠습니까?", L"확 인", MB_YESNO) == IDYES)
	{
		int	nTag = dynamic_cast<TComponent*>(Sender)->Tag;
		AnsiString asCdkeySub = m_vSurveyAddFile[nTag-1].CDKEY_SUB;

		lblLoading->Caption = "파일 삭제중입니다.";
		funcSetWaitWindows(true);

		if( funcDeleteFile(nTag) )
		{
			frmSql->funcSQLInsertSurveyAddFile(DF_DELETE_RECORD, asCdkeySub, 0, "");
			m_vSurveyAddFile.erase(m_vSurveyAddFile.begin() + nTag - 1);
			m_nFileCnt--;
			frmSql->funcSQLInsertSurveyAddInfo(DF_UPDATE_CNT);

			funcSetWaitWindows(false);

			funcInitPanelFileNm();
			funcRedrawPanelFileNm();
			frmMsg->funcMessageDlg("알림:", "파일을 삭제하였습니다.", 3);
		}
	}
	else//No
	{
		return;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::sgListClick(TObject *Sender)
{
	if((int)m_vSurveyAddInfo.size() > 0)
	{
		m_asRegistCdKey = m_vSurveyAddInfo[sgList->Row - 1].REGIST_CDKEY;

		funcInitVariablesDetail();

		funcLoadDataDetail();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnClndDelClick(TObject *Sender)
{
	if(Sender == btnSurvDel01)
		edtSurvDt01->Text = "";
	else if(Sender == btnSurvDel02)
		edtSurvDt02->Text = "";
	else if(Sender == btnInspctDel01)
		edtInspctDt01->Text = "";
	else if(Sender == btnInspctDel02)
		edtInspctDt02->Text = "";
	//
	else if(Sender == btnInspctDel)
		edtInspctDt->Text = "";
	else if(Sender == btnSurvDel)
		edtSurvDt->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnCloseTypeBClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------


void __fastcall Tfrm02Attach::btnModMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	btnMod->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_MODIFY[1]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnModMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	btnMod->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_MODIFY[0]);
	btnModClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnDelMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	btnDel->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_DELETE[1]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnDelMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	btnDel->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_DELETE[0]);
	btnDelClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnDownloadMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	wchar_t wBufBtnDwnImg[64];
	TImage *tcmpBtnDwnImg;
	int nTag = dynamic_cast<TImage*>(Sender)->Tag;

	swprintf(wBufBtnDwnImg, L"btnDownload%02d", nTag);
	tcmpBtnDwnImg = (TImage*)this->FindComponent(wBufBtnDwnImg);
	tcmpBtnDwnImg->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_DOWNLOAD[1]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnDownloadMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	wchar_t wBufBtnDwnImg[64];
	TImage *tcmpBtnDwnImg;
	int nTag = dynamic_cast<TImage*>(Sender)->Tag;

	swprintf(wBufBtnDwnImg, L"btnDownload%02d", nTag);
	tcmpBtnDwnImg = (TImage*)this->FindComponent(wBufBtnDwnImg);
	tcmpBtnDwnImg->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_DOWNLOAD[0]);

	btnDownloadClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnFindQMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	btnFindQ->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_FIND[1]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnFindQMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	btnFindQ->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_FIND[0]);
	btnFindQClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnQueryMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	btnQuery->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_QUERY[1]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnQueryMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	btnQuery->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_QUERY[0]);
	btnQueryClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnInitMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	btnInit->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_INIT[1]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnInitMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	btnInit->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_INIT[0]);
	btnInitClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnFileDelMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
//
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnFileDelMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	btnFileDelClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnListClick(TObject *Sender)
{
	PageControl1Change(NULL);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnRegistClick(TObject *Sender)
{
	TPanel *tcmpPnlPath;
	wchar_t wBufPnlPath[30];
	TEdit *tcmpEdtPath;
	wchar_t wBufEdtPath[30];

	AnsiString asCdkeySub = "";
	AnsiString asRemotePathName = "";
	AnsiString asLocalPathName = "";

	if(nAttachCnt == 0)
	{
		frmMsg->funcMessageDlg("알림:", "첨부 파일을 1건 이상 등록해주세요.", 3);
		return;
	}

	if(funcCheckEditText())
	{
		if(nAttachCnt > 0)
		{
			lblLoading->Caption = "파일 업로드중입니다.";
			funcSetWaitWindows(true);
		}

		if( bRegistMode )
		{
			if(frmSql->funcSQLInsertSurveyAddInfo(DF_NEW_RECORD) > 0)
			{
				m_asCurrDay = Now().FormatString("yyyymmdd");

				for(int i = 0; i < nAttachCnt; i++)
				{
					asCdkeySub = "";
					asRemotePathName = "";

					swprintf(wBufPnlPath, L"pnlAttach%02d", i+1);
					tcmpPnlPath = (TPanel*)this->FindComponent(wBufPnlPath);
					if (tcmpPnlPath->Visible)
					{
						swprintf(wBufEdtPath, L"edtAttachPath%02d", i+1);
						tcmpEdtPath = (TEdit*)this->FindComponent(wBufEdtPath);
						if(tcmpEdtPath->Text.Trim().Length() > 0)
						{
							DWORD dwFileSize = 0;

							asRemotePathName = funcUploadAttach(i+1);
							if(asRemotePathName.IsEmpty())
							{
								continue;
							}

							asLocalPathName = tcmpEdtPath->Text;
							dwFileSize = GetLocalFileSize(asLocalPathName);

							nMaxCdkeySub = i + 1;
							asCdkeySub.sprintf("%03d", nMaxCdkeySub);
							if(frmSql->funcSQLInsertSurveyAddFile(DF_NEW_RECORD, asCdkeySub, dwFileSize, asRemotePathName) > 0)
								m_nFileCnt++;
						}
						else
						{
							if(nAttachCnt == 1 && edtAttachPath01->Text.IsEmpty() )
							{
								frmMsg->funcMessageDlg("알림:", "첨부 파일을 1건 이상 등록해주세요.", 3);
								return;
							}
						}
					}
				}
			}
		}
		else
		{
			int nType = DF_UPDATE_RECORD;

			//get MAX CdkeySub
			if(m_vSurveyAddFile.size() > 0)
			{
				asCdkeySub = m_vSurveyAddFile[m_vSurveyAddFile.size()-1].CDKEY_SUB;
				nMaxCdkeySub = StrToInt(asCdkeySub);
			}
			else
			{
				nMaxCdkeySub = 0;
			}

			m_asRegistNo = m_asRegistCdKey.SubString(9, 5);

			if(frmSql->funcSQLInsertSurveyAddInfo(nType) > 0)
			{
				m_asCurrDay = m_asRegistCdKey.SubString(1, 8);

				for(int i = 0; i < nAttachCnt; i++)
				{
					asCdkeySub = "";
					asRemotePathName = "";

					swprintf(wBufPnlPath, L"pnlAttach%02d", i+1);
					tcmpPnlPath = (TPanel*)this->FindComponent(wBufPnlPath);
					if (tcmpPnlPath->Visible)
					{
						swprintf(wBufEdtPath, L"edtAttachPath%02d", i+1);
						tcmpEdtPath = (TEdit*)this->FindComponent(wBufEdtPath);
						if(tcmpEdtPath->Text.Trim().Length() > 0)
						{
							DWORD dwFileSize = 0;

							if(i < m_nFileCnt)//수정일 때, 기존 DB등록된 파일경로명과 선택한 파일경로명이 다른경우, 기존 DB 저장된 file_cnt 이하 index만 체크한다.
							{
								if(tcmpEdtPath->Text != m_vSurveyAddFile[i].PATH_NAME)//파일변경됨
								{
									//FTP old-file delete
									funcDeleteFile(i+1);
									nType = DF_UPDATE_RECORD;//수정상태, 파일도 수정

									//get Current CdkeySub
									asCdkeySub = m_vSurveyAddFile[i].CDKEY_SUB;

									//FTP new-file upload
									asRemotePathName = funcUploadAttach(i+1);
									if(asRemotePathName.IsEmpty())
									{
										continue;
									}
									//Get filesize
									asLocalPathName = tcmpEdtPath->Text;
									dwFileSize = GetLocalFileSize(asLocalPathName);
									//Update DB fileinfo
									frmSql->funcSQLInsertSurveyAddFile(nType, asCdkeySub, dwFileSize, asRemotePathName);
								}
								else
									continue;
							}
							else//수정상태이지만 파일은 추가
							{
								nType = DF_NEW_RECORD;//수정상태, 파일은 추가

								nMaxCdkeySub++;
								asCdkeySub.sprintf("%03d", nMaxCdkeySub);

								//FTP new-file upload
								asRemotePathName = funcUploadAttach(i+1);
								if(asRemotePathName.IsEmpty())
								{
									continue;
								}
								//Get filesize
								asLocalPathName = tcmpEdtPath->Text;
								dwFileSize = GetLocalFileSize(asLocalPathName);
								//Update DB fileinfo
								if(frmSql->funcSQLInsertSurveyAddFile(nType, asCdkeySub, dwFileSize, asRemotePathName) > 0)
									m_nFileCnt++;
							}
						}
						else
						{
							if(nAttachCnt == 1 && edtAttachPath01->Text.IsEmpty() )
							{
								frmMsg->funcMessageDlg("알림:", "첨부 파일을 1건 이상 등록해주세요.", 3);
								return;
							}

							if(i < m_nFileCnt)
								funcDeleteFile(i+1);
						}
					}
				}
			}
		}

		funcSetWaitWindows(false);

		if(nAttachCnt >= 1 && m_nFileCnt == 0 && !edtAttachPath01->Text.IsEmpty() )//1건이면서 경로명이 비어있지 않은데...m_nFileCnt가 0이면...에러
		{
			frmMsg->funcMessageDlg("알림:", "파일이 업로드 되지 못했습니다.", 3);
			return;
		}
		else//m_nFileCnt > 0
		{
			if(frmSql->funcSQLInsertSurveyAddInfo(DF_UPDATE_CNT) > 0)
			{
				if(bRegistMode)//등록
					frmMsg->funcMessageDlg("확인:", "<결과도> 등록 되었습니다.", 3);
				else//수정
					frmMsg->funcMessageDlg("확인:", "<결과도> 수정 되었습니다.", 3);
				funcInitVariables();
				PageControl1->ActivePage = tabQuery;//등록->조회화면으로 이동//
				PageControl1Change(NULL);
			}
			else
			{
				frmMsg->funcMessageDlg("알림:", "데이타를 입력하는데 문제가 발생하였습니다.", 3);
				return;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnFindClick(TObject *Sender)
{
	frmSidoCode->lvResult->Tag = 7;
	if( frmSidoCode->Showing == false )
		frmSidoCode->Show();
	else
		frmSidoCode->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnAttachClick(TObject *Sender)
{
	TPanel *tcmpPnlPath;
	wchar_t wBufPnlPath[30];
	TPanel *tcmpPnlNo;
	wchar_t wBufPnlNo[30];
	TEdit *tcmpEdtPath;
	wchar_t wBufEdtPath[30];
	TEdit *tcmpEdtName;
	wchar_t wBufEdtName[30];
	AnsiString asFilePath = "";
	AnsiString asFileExt = "";
	int nTag = dynamic_cast<TImage*>(Sender)->Tag;

	if(m_asOpenFileDir.IsEmpty())//190911//44760//req
		OpenDialog1->InitialDir = ExtractFilePath(Application->ExeName);
	else
		OpenDialog1->InitialDir = m_asOpenFileDir;

	if(OpenDialog1->Execute())
	{
		m_asOpenFileDir = ExtractFilePath(OpenDialog1->FileName);//190911//44760//req

		if(OpenDialog1->Files->Count > 1)
		{
			frmMsg->funcMessageDlg("알림:", "1개의 파일만 선택해주세요.", 3);
			return;
		}

		asFilePath = OpenDialog1->FileName;
		asFileExt = ExtractFileExt(asFilePath);

		swprintf(wBufPnlPath, L"pnlAttach%02d", nTag);
		tcmpPnlPath = (TPanel*)this->FindComponent(wBufPnlPath);

		if(tcmpPnlPath->Visible)
		{
			swprintf(wBufPnlNo, L"pnlAttachNo%02d", nTag);
			tcmpPnlNo = (TPanel*)this->FindComponent(wBufPnlNo);
			tcmpPnlNo->Caption = nTag;

			swprintf(wBufEdtPath, L"edtAttachPath%02d", nTag);
			tcmpEdtPath = (TEdit*)this->FindComponent(wBufEdtPath);
			tcmpEdtPath->Text = asFilePath;

			swprintf(wBufEdtName, L"edtAttachNm%02d", nTag);
			tcmpEdtName = (TEdit*)this->FindComponent(wBufEdtName);
			tcmpEdtName->Text = ExtractFileName(tcmpEdtPath->Text);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnAttachDelClick(TObject *Sender)
{
	TPanel *tcmpPnlPath;
	wchar_t wBufPnlPath[30];
	TEdit *tcmpEdtPath;
	wchar_t wBufEdtPath[30];
	TEdit *tcmpEdtNm;
	wchar_t wBufEdtNm[30];
	int nTag = dynamic_cast<TImage*>(Sender)->Tag;

	swprintf(wBufPnlPath, L"pnlAttach%02d", nTag);
	tcmpPnlPath = (TPanel*)this->FindComponent(wBufPnlPath);

	if(tcmpPnlPath->Visible)
	{
		swprintf(wBufEdtPath, L"edtAttachPath%02d", nTag);
		tcmpEdtPath = (TEdit*)this->FindComponent(wBufEdtPath);
		tcmpEdtPath->Text = "";

		swprintf(wBufEdtNm, L"edtAttachNm%02d", nTag);
		tcmpEdtNm = (TEdit*)this->FindComponent(wBufEdtNm);
		tcmpEdtNm->Text = "";
	}
}
//---------------------------------------------------------------------------

//[TODO] 중간에 삭제해버리면 기존에 저장되었던 데이타들의 SEQSUB를 모두 변경해줘야 한다.

void __fastcall Tfrm02Attach::btnAttachAddClick(TObject *Sender)
{
	TPanel *tcmpPnlPath;
	wchar_t wBufPnlPath[30];
	TEdit *tcmpEdtPath;
	wchar_t wBufEdtPath[30];
	int nTag = dynamic_cast<TImage*>(Sender)->Tag;

	if(nAttachCnt == 10)
	{
		frmMsg->funcMessageDlg("알림:", "첨부파일은 최대 10개까지입니다.", 3);
		return;
	}

	nAttachCnt++;
	swprintf(wBufPnlPath, L"pnlAttach%02d", nAttachCnt);
	tcmpPnlPath = (TPanel*)this->FindComponent(wBufPnlPath);
	tcmpPnlPath->Visible = true;
	ScrollBox1->Height = nAttachCnt * pnlAttachT->Height;
}
//---------------------------------------------------------------------------


void __fastcall Tfrm02Attach::funcInitVariables()
{
	m_nFileCnt = 0;//실제 file 테이블에 저장된 파일 개수
	nAttachCnt = 1;//추가버튼으로 추가된 개수(실제 FTP upload 개수와 다를 수 있음)

	edtUmdRiCd->Text = "";
	edtUmdRiNm->Text = "";//190911//44760//req
	cboGbn->ItemIndex = 0;
	edtBonbun->Text = "";
	edtBoobun->Text = "";
	cboScale->ItemIndex = 3;//190911//44760//req
	clndInspctDtR->Date = Now();
	edtInspctDt->Text 	= clndInspctDtR->Date.FormatString("YYYY.MM.DD");
	edtSurvDt->Text = "";
//	edtInspctDt->Text = "";
	edtResult->Text = "";
	edtEtc->Text = "";

	TPanel *tcmpPnlPath;
	wchar_t wBufPnlPath[30];
	TEdit *tcmpEdtPath;
	wchar_t wBufEdtPath[30];
	TEdit *tcmpEdtName;
	wchar_t wBufEdtName[30];

	for(int i = 0; i < 10; i++)
	{
		swprintf(wBufPnlPath, L"pnlAttach%02d", i+1);
		tcmpPnlPath = (TPanel*)this->FindComponent(wBufPnlPath);

		swprintf(wBufEdtPath, L"edtAttachPath%02d", i+1);
		tcmpEdtPath = (TEdit*)this->FindComponent(wBufEdtPath);
		tcmpEdtPath->Text = "";

		swprintf(wBufEdtName, L"edtAttachNm%02d", i+1);
		tcmpEdtName = (TEdit*)this->FindComponent(wBufEdtName);
		tcmpEdtName->Text = "";

		if(i == 0)
		{
			tcmpPnlPath->Visible = true;
		}
		else
		{
			tcmpPnlPath->Visible = false;
		}

		tcmpEdtPath->Text = "";
		tcmpEdtName->Text = "";
	}

	ScrollBox1->Height = nAttachCnt * pnlAttachT->Height;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::funcLoadData()
{
	SURVEY_ADDINFO_STRUCT tempDoc02Attach;
	AnsiString asPnu        = "";
	AnsiString asSidoCode   = "";
	AnsiString asSidoName   = "";
	AnsiString asUmdRiCode  = "";
	AnsiString asUmdRiName  = "";
	AnsiString asGbn        = "";
	AnsiString asBonbun     = "";
	AnsiString asBoobun     = "";
	AnsiString asSurvDate   = "";
	AnsiString asInspctDate = "";
//	nAttachCnt = 0;

	memset(&tempDoc02Attach, 0x00, sizeof(SURVEY_ADDINFO_STRUCT));
	memcpy(&tempDoc02Attach, &m_vSurveyAddInfo[sgList->Row - 1], sizeof(SURVEY_ADDINFO_STRUCT));

	//190916
	asGbn = (char*)tempDoc02Attach.REGIST_GBN;
	if(asGbn == "1")
		rbGbn1->Checked = true;
	else if(asGbn == "2")
		rbGbn2->Checked = true;
	else if(asGbn == "3")
		rbGbn3->Checked = true;
	//210304//#ATTACH_DOC02//현황/경계 하나로//
//	else if(asGbn == "4")
//		rbGbn4->Checked = true;

	asPnu       = tempDoc02Attach.PNU;
	if(asPnu.Length() == 19)
	{
		asSidoCode  = asPnu.SubString(1, 5);
		asUmdRiCode = asPnu.SubString(6, 5);
		asGbn       = asPnu.SubString(11, 1);
		asBonbun    = asPnu.SubString(12, 4);
		asBoobun    = asPnu.SubString(16, 4);

		asSidoName  = eFunc->funcPnuToSGGName(asPnu.c_str());
		asUmdRiName = eFunc->funcPnuToUMDRIName(asPnu.c_str(), false);

		//edtSidoCd->Text   = asSidoCode + " " + asSidoName;
		edtUmdRiCd->Text  = asUmdRiCode;//asUmdRiCode + " " + asUmdRiName;
		edtUmdRiNm->Text  = asUmdRiName;//190911//44760//req
		cboGbn->ItemIndex = StrToInt(asGbn)-1;
		edtBonbun->Text   = StrToInt(asBonbun);
		edtBoobun->Text   = StrToInt(asBoobun);
	}

	asSurvDate        = tempDoc02Attach.SURVEY_DATE;
	if( asSurvDate.Length() == 8)
		edtSurvDt->Text    = asSurvDate.SubString(1, 4) + "." + asSurvDate.SubString(5, 2) + "." + asSurvDate.SubString(7, 2);

	asInspctDate      = tempDoc02Attach.INSPCT_DATE;
	if( asInspctDate.Length() == 8)
		edtInspctDt->Text = asInspctDate.SubString(1, 4) + "." + asInspctDate.SubString(5, 2) + "." + asInspctDate.SubString(7, 2);

	edtResult->Text   = tempDoc02Attach.DOC_NAME;
	edtEtc->Text      = tempDoc02Attach.ETC_MEMO;



	//-----------------------------------------------
	TPanel *tcmpPnlPath;
	wchar_t wBufPnlPath[30];
	TPanel *tcmpPnlNo;
	wchar_t wBufPnlNo[30];
	TEdit *tcmpEdtPath;
	wchar_t wBufEdtPath[30];
	TEdit *tcmpEdtName;
	wchar_t wBufEdtName[30];
	AnsiString asFileName = "";

	if(sgList->Row > 1)
		m_nSgListIndex = sgList->Row - 1;

	nAttachCnt = tempDoc02Attach.FILE_CNT;
	m_nFileCnt = tempDoc02Attach.FILE_CNT;

	ScrollBox1->Height = nAttachCnt * pnlAttachT->Height;

	for(int i = 0; i < nAttachCnt; i++)
	{
		swprintf(wBufPnlPath, L"pnlAttach%02d", i+1);
		tcmpPnlPath = (TPanel*)this->FindComponent(wBufPnlPath);
		tcmpPnlPath->Visible = true;

		swprintf(wBufPnlNo, L"pnlAttachNo%02d", i+1);
		tcmpPnlNo = (TPanel*)this->FindComponent(wBufPnlNo);
		tcmpPnlNo->Caption = i+1;

		swprintf(wBufEdtPath, L"edtAttachPath%02d", i+1);
		tcmpEdtPath = (TEdit*)this->FindComponent(wBufEdtPath);
		tcmpEdtPath->Text = m_vSurveyAddFile[i].PATH_NAME;

		swprintf(wBufEdtName, L"edtAttachNm%02d", i+1);
		tcmpEdtName = (TEdit*)this->FindComponent(wBufEdtName);
		asFileName = m_vSurveyAddFile[i].PATH_NAME;
		asFileName = ExtractFileName(StringReplace(asFileName, "/", "\\", TReplaceFlags()<<rfReplaceAll));
		tcmpEdtName->Text = asFileName;
	}

	if(nAttachCnt == 0)//수정모드//첨부파일 한 개도 없었을 경우: 파일 첨부하기, 추가 1 row 보이기
	{
		nAttachCnt = 1;
		ScrollBox1->Height = nAttachCnt * pnlAttachT->Height;

		swprintf(wBufPnlPath, L"pnlAttach%02d", 1);
		tcmpPnlPath = (TPanel*)this->FindComponent(wBufPnlPath);
		tcmpPnlPath->Visible = true;

		swprintf(wBufEdtPath, L"edtAttachPath%02d", 1);
		tcmpEdtPath = (TEdit*)this->FindComponent(wBufEdtPath);
		tcmpEdtPath->Text = "";

		swprintf(wBufEdtName, L"edtAttachNm%02d", 1);
		tcmpEdtName = (TEdit*)this->FindComponent(wBufEdtName);
		tcmpEdtName->Text = "";
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnInspctDtClick(TObject *Sender)
{
	clndInspctDtR->Date = Now();
	clndInspctDtR->Visible = true;
	clndInspctDtR->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnSurvDtClick(TObject *Sender)
{
	clndSurvDtR->Date = Now();
	clndSurvDtR->Visible = true;
	clndSurvDtR->Date = Now();
	clndSurvDtR->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::clndInspctDtRDblClick(TObject *Sender)
{
	edtInspctDt->Text = clndInspctDtR->Date.FormatString("YYYY.MM.DD");
	clndInspctDtR->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::clndSurvDtRDblClick(TObject *Sender)
{
	edtSurvDt->Text = clndSurvDtR->Date.FormatString("YYYY.MM.DD");
	clndSurvDtR->Visible = false;
}
//---------------------------------------------------------------------------

AnsiString __fastcall Tfrm02Attach::funcUploadAttach(int _nIndex)
{
	FTP_FILE_STRUCT	mUploadFile;
	AnsiString asTarget = "DOCUMENT02_ATTACH";
	AnsiString asRemoteFilePath = "";
	AnsiString asRemoteFileName = "";
	AnsiString asLocalFilePath = "";
//	AnsiString asIndex = Now().FormatString("yyyymmdd");
	AnsiString asCdkeySub = "";
	TEdit *tcmpEdtPath;
	wchar_t wBufEdtPath[30];
	TEdit *tcmpEdtNm;
	wchar_t wBufEdtNm[30];

	swprintf(wBufEdtPath, L"edtAttachPath%02d", _nIndex);
	tcmpEdtPath = (TEdit*)this->FindComponent(wBufEdtPath);
	if(tcmpEdtPath->Text.Trim().Length() == 0)
		return "";

	swprintf(wBufEdtNm, L"edtAttachNm%02d", _nIndex);
	tcmpEdtNm = (TEdit*)this->FindComponent(wBufEdtNm);
	if(tcmpEdtNm->Text.Trim().Length() == 0)
		return "";

	asLocalFilePath = tcmpEdtPath->Text;
	asRemoteFileName = tcmpEdtNm->Text;
	memset(&mUploadFile, 0x00, sizeof(mUploadFile));
	wsprintf(mUploadFile.cTarget, "%s", asTarget.c_str());
	wsprintf(mUploadFile.cFileName, "%s", asRemoteFileName.c_str());
	wsprintf(mUploadFile.cLocalFilePath, "%s", asLocalFilePath.c_str());//Local File Path
	wsprintf(mUploadFile.cFileType, "%s", asLocalFilePath.SubString(asLocalFilePath.Length() - 2, 3));
//	wsprintf(mUploadFile.cIndexPolder, "%s/", asToday.c_str());//cIndexPolder
	asCdkeySub.sprintf("%03d", nMaxCdkeySub);
	wsprintf(mUploadFile.cIndexPolder, "%s/", (m_asCurrDay + m_asRegistNo + asCdkeySub).c_str());//cIndexPolder

	if (!frmFtpControl->FuncFtpFileUpload(0, &mUploadFile, 0))
	{
		return asRemoteFilePath;
	}

	//210226//asRemoteFilePath.sprintf("%s%s/%s%s", frmMain->INIINFO.FTPROOT, mUploadFile.cTarget, mUploadFile.cIndexPolder, mUploadFile.cFileName);
	asRemoteFilePath.sprintf("%s/%s%s", mUploadFile.cTarget, mUploadFile.cIndexPolder, mUploadFile.cFileName);//210226//
	return asRemoteFilePath;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::edtBoobunExit(TObject *Sender)
{
	if(edtBonbun->Text.Trim().Length() == 0)
	{
		frmMsg->funcMessageDlg("알림:", "본번을 입력해주세요.", 3);
		return;
	}
}
//---------------------------------------------------------------------------
__int64 __fastcall Tfrm02Attach::GetLocalFileSize(AnsiString _asFileName)
{
	DWORD   dwLow;
	DWORD   dwHigh  = 0;
	__int64     nFileSize = 0;
	HANDLE  hFile   = ::CreateFile( _asFileName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL );

	if( hFile != INVALID_HANDLE_VALUE )
	{
		dwLow = ::GetFileSize( hFile, &dwHigh );
		if( (dwLow != 0xFFFFFFFF)  ||  GetLastError() == NO_ERROR )
			nFileSize = (__int64)(dwHigh << 32  |  dwLow);

		CloseHandle( hFile );
	}
	return nFileSize;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnAttachAddMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	wchar_t wBufBtnAddImg[64];
	TImage *tcmpBtnAddImg;
	int nTag = dynamic_cast<TImage*>(Sender)->Tag;

	swprintf(wBufBtnAddImg, L"btnAttachAdd%02d", nTag);
	tcmpBtnAddImg = (TImage*)this->FindComponent(wBufBtnAddImg);
	tcmpBtnAddImg->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_ADD[1]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnAttachAddMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	wchar_t wBufBtnAddImg[64];
	TImage *tcmpBtnAddImg;
	int nTag = dynamic_cast<TImage*>(Sender)->Tag;

	swprintf(wBufBtnAddImg, L"btnAttachAdd%02d", nTag);
	tcmpBtnAddImg = (TImage*)this->FindComponent(wBufBtnAddImg);
	tcmpBtnAddImg->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_ADD[0]);

	btnAttachAddClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnFindMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	btnFind->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_FIND[1]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnFindMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	btnFind->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_FIND[0]);
	btnFindClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnListMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	btnList->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_LIST[1]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnListMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	btnList->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_LIST[0]);
	btnListClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnRegistMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	if(bRegistMode) //등록
		btnRegist->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_REGIST[1]);
	else//수정
		btnRegist->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_MODIFY[1]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnRegistMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if(bRegistMode) //등록
		btnRegist->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_REGIST[0]);
	else//수정
		btnRegist->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_MODIFY[0]);

	btnRegistClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnAttachMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	wchar_t wBufBtnAttImg[64];
	TImage *tcmpBtnAttImg;
	int nTag = dynamic_cast<TImage*>(Sender)->Tag;

	swprintf(wBufBtnAttImg, L"btnAttach%02d", nTag);
	tcmpBtnAttImg = (TImage*)this->FindComponent(wBufBtnAttImg);
	tcmpBtnAttImg->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_ATTACH[1]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnAttachMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	wchar_t wBufBtnAttImg[64];
	TImage *tcmpBtnAttImg;
	int nTag = dynamic_cast<TImage*>(Sender)->Tag;

	swprintf(wBufBtnAttImg, L"btnAttach%02d", nTag);
	tcmpBtnAttImg = (TImage*)this->FindComponent(wBufBtnAttImg);
	tcmpBtnAttImg->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_ATTACH[0]);

	btnAttachClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnWriteMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	btnWrite->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_REGIST[1]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::btnWriteMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	btnWrite->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_REGIST[0]);
	btnWriteClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm02Attach::btnWriteClick(TObject *Sender)
{
	m_asRegistCdKey = "";

	m_asRegistNo = frmSql->funcSQLSelectSurveyAddMaxRegistNo();

	bRegistMode = true;//등록
	funcInitVariables();
	PageControl1->ActivePage = tabRegist;
	PageControl1Change(NULL);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm02Attach::btnFindQClick(TObject *Sender)
{
	frmSidoCode->lvResult->Tag = 8;
	if( frmSidoCode->Showing == false )
		frmSidoCode->Show();
	else
		frmSidoCode->BringToFront();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm02Attach::PageControl1Change(TObject *Sender)
{
	if(PageControl1->ActivePage == tabRegist)
	{
		if(bRegistMode) //등록
		{
			m_asRegistCdKey = "";
			m_asRegistNo = frmSql->funcSQLSelectSurveyAddMaxRegistNo();
			funcInitVariables();
			edtUmdRiCd->SetFocus();
			btnRegist->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_REGIST[0]);
		}
		else//수정
		{
			funcLoadData();
			btnRegist->Picture->Bitmap->Assign(BITMAP_02ATTACH_BTN_MODIFY[0]);
		}
	}
	else if(PageControl1->ActivePage == tabQuery)
	{
		//[TODO] 작성 중 조회 화면으로 이동시 조회했던 내용 초기화 할지 여부//funcInitVariablesQuery();
		btnQueryClick(NULL);
	}

	//edtSidoCd->Text = frmMain->_SIDOCODE + " " + frmMain->_SIDONAME;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::PageControl1Changing(TObject *Sender, bool &AllowChange)
{
	if (PageControl1->ActivePage == tabRegist)//minji
	{
		if(bRegistMode && funcCheckWroteData())
		{
			if (Application->MessageBox(L"작성하던 내용이 있습니다. 지우시겠습니까?", L"확 인", MB_YESNO) == IDYES) { // 초기화
				funcInitVariables();
//				bRegistMode = false;//초기화
			}
			else
			{
            	AllowChange = false;
				return;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::funcCheckDate()
{
	AnsiString asSurvDateStt 	= "";
	AnsiString asSurvDateEnd 	= "";
	AnsiString asInspctDateStt 	= "";
	AnsiString asInspctDateEnd 	= "";

	//
	asSurvDateStt = frm02Attach->edtSurvDt01->Text.Trim();
	if( asSurvDateStt.IsEmpty() && !asSurvDateEnd.IsEmpty() )
	{
		frmMsg->funcMessageDlg("알림:", "측량일자의 시작일이 없어 검색조건에서 제외됩니다.", 3);
		return;
	}

	asSurvDateEnd = frm02Attach->edtSurvDt02->Text.Trim();
	if( !asSurvDateStt.IsEmpty() && asSurvDateEnd.IsEmpty() )
	{
		frmMsg->funcMessageDlg("알림:", "측량일자의 종료일이 없어 검색조건에서 제외됩니다.", 3);
		return;
	}

	m_bQrySurvDt = true;


	//
	asInspctDateStt = frm02Attach->edtInspctDt01->Text.Trim();
	if( asInspctDateStt.IsEmpty() && !asInspctDateEnd.IsEmpty() )
	{
		frmMsg->funcMessageDlg("알림:", "측량검사일자의 시작일이 없어 검색조건에서 제외됩니다.", 3);
		return;
	}

	asInspctDateEnd = frm02Attach->edtInspctDt02->Text.Trim();
	if( !asInspctDateStt.IsEmpty() && asInspctDateEnd.IsEmpty() )
	{
		frmMsg->funcMessageDlg("알림:", "측량검사일자의 종료일이 없어 검색조건에서 제외됩니다.", 3);
		return;
	}

	m_bQryInspctDt = true;
}
//---------------------------------------------------------------------------

bool __fastcall Tfrm02Attach::funcDeleteFile(int _nTag)
{
	FTP_FILE_STRUCT	mDeleteFile;
	AnsiString  asTarget = "DOCUMENT02_ATTACH";
	AnsiString	asRemoteFile;
	AnsiString	asRemoteDir;
	AnsiString  asRemoteFilePath;
	AnsiString	asRemoteFullFilePath;

	//---
	memset(&mDeleteFile, 0x00, sizeof(mDeleteFile));
	asRemoteFullFilePath    = frm02Attach->m_vSurveyAddFile[_nTag-1].PATH_NAME;
	asRemoteFullFilePath 	= StringReplace(asRemoteFullFilePath, "/", "\\", TReplaceFlags()<<rfReplaceAll);
	asRemoteFilePath 	    = StringReplace(asRemoteFullFilePath, (asTarget + "\\").c_str(), "", TReplaceFlags()<<rfReplaceAll);
	asRemoteDir		  		= StringReplace(ExtractFilePath(asRemoteFilePath), "\\", "", TReplaceFlags()<<rfReplaceAll);
	asRemoteFile      		= ExtractFileName(asRemoteFilePath);

	wsprintf(mDeleteFile.cTarget, "%s", asTarget.c_str());
	wsprintf(mDeleteFile.cFileName, "%s", asRemoteFile.c_str());
	wsprintf(mDeleteFile.cIndexPolder, "%s/", asRemoteDir.c_str());//cIndexPolder

	return frmFtpControl->FuncFtpFileDelete(0, &mDeleteFile);
}
//---------------------------------------------------------------------------

bool __fastcall Tfrm02Attach::funcCheckEditText()
{
	AnsiString asSidoCode 	= frm02Attach->edtSidoCd->Text.SubString(1, 5);
	AnsiString asUmdRiCode 	= frm02Attach->edtUmdRiCd->Text;
	AnsiString asBonbun 	= frm02Attach->edtBonbun->Text;
	AnsiString asBoobun 	= frm02Attach->edtBoobun->Text;
	AnsiString asResultName = frm02Attach->edtResult->Text;

	if(asSidoCode.IsEmpty())//여기에는 들어올 일이 없다.
	{
		frmMsg->funcMessageDlg("알림:", "시도코드를 입력해주세요.", 3);
		return false;
	}

	if(asUmdRiCode.IsEmpty())
	{
		frmMsg->funcMessageDlg("알림:", "토지소재를 입력해주세요.", 3);
		return false;
	}

	if(asBonbun.IsEmpty())
	{
		frmMsg->funcMessageDlg("알림:", "본번을 입력해주세요.", 3);
		return false;
	}

	if(asBoobun.IsEmpty())
	{
		frmMsg->funcMessageDlg("알림:", "부번을 입력해주세요.", 3);
		return false;
	}

	if(asResultName.IsEmpty())
	{
		frmMsg->funcMessageDlg("알림:", "결과도명을 입력해주세요.", 3);
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm02Attach::funcSetWaitWindows(bool bSetValue)
{
	this->panelWait->Left = (this->Width/2) - (this->panelWait->Width/2);
	this->panelWait->Top  = (this->Height/2) - (this->panelWait->Height/2) - 120;

	if (this->panelWait->Visible == !bSetValue)
	{
		panelWait->Visible = bSetValue;

		if (bSetValue) {
			Screen->Cursor     = crHourGlass;
		} else {
			Screen->Cursor     = crDefault;
			lblLoading->Caption = L"";
		}
	}
	Application->ProcessMessages();
}
//---------------------------------------------------------------------------

bool __fastcall Tfrm02Attach::funcCheckWroteData()
{
	if(edtUmdRiCd->Text != "")
		return true;
	if(edtBonbun->Text != "")
		return true;
	if(edtBoobun->Text != "")
		return true;
	if(edtSurvDt->Text != "")
		return true;
	if(edtInspctDt->Text != "")
		return true;
	if(edtResult->Text != "")
		return true;
	if(edtEtc->Text != "")
		return true;
	if(edtAttachNm01->Text != "")
		return true;
	if(edtAttachPath01->Text != "")
		return true;

	//-----------------------------------------------
	TPanel *tcmpPnlPath;
	wchar_t wBufPnlPath[30];
	TEdit *tcmpEdtPath;
	wchar_t wBufEdtPath[30];
	TEdit *tcmpEdtName;
	wchar_t wBufEdtName[30];
	AnsiString asFileName = "";

	for(int i = 0; i < 10; i++)
	{
		swprintf(wBufPnlPath, L"pnlAttach%02d", i+1);
		tcmpPnlPath = (TPanel*)this->FindComponent(wBufPnlPath);

		if(tcmpPnlPath->Visible)
		{
			swprintf(wBufEdtPath, L"edtAttachPath%02d", i+1);
			tcmpEdtPath = (TEdit*)this->FindComponent(wBufEdtPath);
			if(tcmpEdtPath->Text != "")
				return true;

			swprintf(wBufEdtName, L"edtAttachNm%02d", i+1);
			tcmpEdtName = (TEdit*)this->FindComponent(wBufEdtName);
			if(tcmpEdtName->Text != "")
				return true;
		}
	}

	return false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(frm02Attach->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::funcRegistKeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN)
	{
		if(Sender == edtUmdRiCd)
			edtUmdRiNm->SetFocus();
		if(Sender == edtUmdRiNm)
			edtBonbun->SetFocus();
		if(Sender == edtBonbun)
			edtBoobun->SetFocus();
		if(Sender == edtBoobun)//maskedit가 enabled=false 상태라 setfocus가 안됨//부번 입력 후 파일 선택(btnInspct는 이미지라 focus 안됨)
			cboScale->SetFocus();
		if(Sender == cboScale)//maskedit가 enabled=false 상태라 setfocus가 안됨//부번 입력 후 파일 선택(btnInspct는 이미지라 focus 안됨)
			edtResult->SetFocus();
//		if(Sender == edtBoobun)//maskedit가 enabled=false 상태라 setfocus가 안됨//부번 입력 후 파일 선택(btnInspct는 이미지라 focus 안됨)
//			btnAttachClick(btnAttach01);
//			btnInspctDtClick(NULL);
//		if(Sender == btnInspctDt)
//			btnSurvDtClick(NULL);
//		if(Sender == btnSurvDt)
//			btnAttachClick(btnAttach01);

		Sender = NULL;
		Key = NULL;
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::funcQueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN)
	{
		if(Sender == edtUmdRiCdQ)
			edtUmdRiNmQ->SetFocus();
		if(Sender == edtUmdRiNmQ)
			edtBonbunQ->SetFocus();
		if(Sender == edtBonbunQ)
			edtBoobunQ->SetFocus();
		if(Sender == edtBoobunQ)
			edtResultQ->SetFocus();
		if(Sender == edtResultQ)//maskedit가 enabled=false 상태라 setfocus가 안됨//부번 입력 후 파일 선택(btnInspct는 이미지라 focus 안됨)
			btnQueryClick(NULL);
//			edtSurvDt01->SetFocus();
//		if(Sender == edtSurvDt01)
//			edtSurvDt02->SetFocus();
//		if(Sender == edtSurvDt02)
//			edtInspctDt01->SetFocus();
//		if(Sender == edtInspctDt01)
//			edtInspctDt02->SetFocus();
//		if(Sender == edtInspctDt02)
//			btnQueryClick(NULL);

		Sender = NULL;
		Key = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::sgListDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State)
{
	TStringGrid  *pDBGrid   = (TStringGrid *)Sender;
	TCanvas  *pCanvas   = pDBGrid->Canvas;
	//--------------------------------------------------------------------------
	AnsiString strValue = "";
	TRect realRect;

	realRect.left   = Rect.left;//   + 1;
	realRect.top    = Rect.top;//    + 1;
	realRect.right  = Rect.right  - 1;
	realRect.bottom = Rect.bottom - 1;

	strValue = pDBGrid->Cells[ACol][ARow];

	int X = 0;
	//--------------------------------------------------------------------------
	if( ACol == 0 || ARow ==  0){
		::SetTextAlign( pCanvas->Handle, TA_CENTER );
		X = realRect.Left + ((realRect.Right - realRect.Left)/2);
	}
	else {
		::SetTextAlign( pCanvas->Handle, TA_CENTER ); // TA_LEFT );
		X = realRect.Left + ((realRect.Right - realRect.Left)/2);
	}

	//--------------------------------------------------------------------------
	TColor crOldBrushColor = pCanvas->Brush->Color;
	TColor crOldPenColor   = pCanvas->Pen->Color;

	pCanvas->Pen->Color   = (TColor)RGB( 180, 180, 180 );
	pCanvas->Rectangle(Rect);

	//--------------------------------------------------------------------------
	if(State.Contains(Grids::gdSelected)){
		pCanvas->Brush->Color = (TColor)RGB( 253, 234, 166 );
		pCanvas->Pen->Color   = (TColor)RGB( 241, 202,  88 );

		TPenStyle OldPenStyle = pCanvas->Pen->Style;
		pCanvas->Pen->Style   = psSolid;
		pCanvas->Rectangle(realRect);
		pCanvas->Pen->Style = OldPenStyle;
	}
	else {
		if(ARow == 0 ){
			pCanvas->Brush->Color = (TColor)RGB( 227, 230, 232 );
			pCanvas->Font->Color  = (TColor)RGB( 0, 0, 0 );//
			//pCanvas->Pen->Color   = (TColor)RGB( 0, 0, 0 );//(TColor)RGB( 255, 255, 255 );
			pCanvas->Pen->Color   = (TColor)RGB( 255, 255, 255 );
		}
		else{
			pCanvas->Brush->Color = (TColor)RGB( 251, 255, 255 );
			pCanvas->Pen->Color   = (TColor)RGB( 251, 255, 255 );
			pCanvas->Font->Color  = (TColor)RGB( 0, 0, 0 );//
		}

		pCanvas->FillRect(realRect);
	}

	pCanvas->Brush->Color = crOldBrushColor;
	pCanvas->Pen->Color   = crOldPenColor;
	//--------------------------------------------------------------------------

	TBrushStyle nOldBrushStyle = pCanvas->Brush->Style;
	int OldBkMode = ::SetBkMode( pCanvas->Handle, TRANSPARENT );
	pCanvas->Brush->Style = bsClear;


	//--------------------------------------------------------------------------
	//190916
	if(ARow != 0 && ACol == 2 && strValue.Length() > 56)//210310//#ATTACH02_ETC_DEL////190215
	{
		AnsiString asStrPrev;
		AnsiString asStrNext;
		int nLength = strValue.Length();
		int nMidIndex = nLength / 2;
		if( (strValue.c_str()[nMidIndex] & 0x80) == 0x80 ) {// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
			nMidIndex += 2; // 한글문자 다음 바이트로 넘김
		}

		pCanvas->Font->Size = 7;
		asStrPrev = strValue.SubString(1, nMidIndex);
		asStrNext = strValue.SubString(nMidIndex + 1, nLength - 1);
		pCanvas->TextOut( X, realRect.Top + 1,  asStrPrev );
		pCanvas->TextOut( X, realRect.Top + 10, asStrNext );
	}
	else
	{
		pCanvas->TextOut( X, realRect.Top + 5, strValue );
	}

	//--------------------------------------------------------------------------
	pCanvas->Brush->Style = nOldBrushStyle;
	::SetBkMode( pCanvas->Handle, OldBkMode );
	//--------------------------------------------------------------------------
}
//---------------------------------------------------------------------------

void __fastcall Tfrm02Attach::cboSortClick(TObject *Sender)
{
	btnQueryClick(btnQuery);
}
//---------------------------------------------------------------------------

