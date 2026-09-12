#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "BaseGrid"
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#pragma warn -8004
#pragma warn -8055

Tfrm01Attach *frm01Attach;
//---------------------------------------------------------------------------
__fastcall Tfrm01Attach::Tfrm01Attach(TComponent* Owner)
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

void __fastcall Tfrm01Attach::FormCreate(TObject *Sender)
{
	clndPrcsDtR->Left 		= 150;
	clndPrcsDtR->Top  		= 200;
	clndPrcsDt01->Left 		= 150;
	clndPrcsDt01->Top  		= 170;
	clndPrcsDt02->Left 		= 285;
	clndPrcsDt02->Top  		= 170;

	for (int i = 0; i < sgAddFileList->ColCount; i++)
	{
		sgAddFileList->Colors[i][0] = (TColor)RGB(221,232,254);//clInfoBk;
		sgList->Colors[i][0] 		= (TColor)RGB(221,232,254);//clInfoBk;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::FormShow(TObject *Sender)
{
	frmSql->funcSQLCreateTableInfoDoc01();
	frmSql->funcSQLCreateTableFileDoc01();
	frmSql->funcSQLCreateTableInfoDelDoc01();
	frmSql->funcSQLCreateTableFileDelDoc01();

	frmFileSave->m_asSelectedFullFileName = "";
	frmFileSave->m_nFileSize = 0;

	funcLoadButtonImage();

	frmMsg->Position = poScreenCenter;//200212

	m_nDocNameMaxLen = 60;//maxlength : 60
	m_nPathMaxLen    = 255;//maxlength : 255
	m_bMaxLength     = false;

	edtSidoCdQ->Text = frmMain->_SIDOCODE + " " + frmMain->_SIDONAME;

	funcInitVariables();
	funcInitVariablesQuery();
	funcInitVariablesDetail();

	if(PageControl1->ActivePage == tabRegist)
	{
		if(bRegistMode) //등록
		{
			//funcInitVariables();
			edtSidoCd->Text = frmMain->_SIDOCODE + " " + frmMain->_SIDONAME;
		}
		else//수정
		{
			funcLoadData();
			edtSidoCd->Text = frmMain->_SIDOCODE + " - " + frmMain->_SIDONAME;
		}
	}
	else if(PageControl1->ActivePage == tabQuery)
	{
		//funcInitVariablesQuery();
		InitDBGrid();
		//funcInitVariablesDetail();

		edtSidoCd->Text = frmMain->_SIDOCODE + " " + frmMain->_SIDONAME;
	}
}
//---------------------------------------------------------------------------
void __fastcall Tfrm01Attach::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(frmFileSave->Showing)
		frmFileSave->Close();

	funcInitPanelFileNm();

	funcInitVariables();
	funcInitVariablesQuery();
	funcInitVariablesDetail();

	pnlView->Height 		= 154;//160;
	pnlList04->Height 		= 30;//32;
	pnlFileNm->Height 		= 30;//32;
	pnlFileNmD->Height 		= 30;//32;
	ScrollBox1->Height 		= 30;//32;

	PageControl1->ActivePage = tabQuery;
	bRegistMode = true;//등록
	m_asOpenFileDir = "";//190911//44760//req

	funcDeleteButtonImage();

	delete btnAttach;
	btnAttach = NULL;
	delete btnDownload;
	btnDownload = NULL;
	delete btnDelete;
	btnDelete = NULL;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::funcLoadButtonImage()
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
		//---
		filename = frmMain->IMAGEUIPATH + "02Attach_btnFind" + IntToStr(i) + ".bmp";
		BITMAP_01ATTACH_BTN_FIND[i] 	= new Graphics::TBitmap();
		BITMAP_01ATTACH_BTN_FIND[i]->LoadFromFile(filename);

		filename = frmMain->IMAGEUIPATH + "02Attach_btnQuery" + IntToStr(i) + ".bmp";
		BITMAP_01ATTACH_BTN_QUERY[i] 	= new Graphics::TBitmap();
		BITMAP_01ATTACH_BTN_QUERY[i]->LoadFromFile(filename);

		filename = frmMain->IMAGEUIPATH + "02Attach_btnInit" + IntToStr(i) + ".bmp";
		BITMAP_01ATTACH_BTN_INIT[i] 	= new Graphics::TBitmap();
		BITMAP_01ATTACH_BTN_INIT[i]->LoadFromFile(filename);

		filename = frmMain->IMAGEUIPATH + "02Attach_btnDownload" + IntToStr(i) + ".bmp";
		BITMAP_01ATTACH_BTN_DOWNLOAD[i] 	= new Graphics::TBitmap();
		BITMAP_01ATTACH_BTN_DOWNLOAD[i]->LoadFromFile(filename);

		//
		filename = frmMain->IMAGEUIPATH + "02Attach_btnList" + IntToStr(i) + ".bmp";
		BITMAP_01ATTACH_BTN_LIST[i] 	= new Graphics::TBitmap();
		BITMAP_01ATTACH_BTN_LIST[i]->LoadFromFile(filename);

		filename = frmMain->IMAGEUIPATH + "02Attach_btnRegist" + IntToStr(i) + ".bmp";
		BITMAP_01ATTACH_BTN_REGIST[i] 	= new Graphics::TBitmap();
		BITMAP_01ATTACH_BTN_REGIST[i]->LoadFromFile(filename);
	}

	for(int i = 0; i < 3; i++)
	{
		filename = frmMain->IMAGEUIPATH + "02Attach_btnModify" + IntToStr(i) + ".bmp";
		BITMAP_01ATTACH_BTN_MODIFY[i] 	= new Graphics::TBitmap();
		BITMAP_01ATTACH_BTN_MODIFY[i]->LoadFromFile(filename);

		filename = frmMain->IMAGEUIPATH + "02Attach_btnDelete" + IntToStr(i) + ".bmp";
		BITMAP_01ATTACH_BTN_DELETE[i] 	= new Graphics::TBitmap();
		BITMAP_01ATTACH_BTN_DELETE[i]->LoadFromFile(filename);

		//
		filename = frmMain->IMAGEUIPATH + "02Attach_btnAttach" + IntToStr(i) + ".bmp";
		BITMAP_01ATTACH_BTN_ATTACH[i] 	= new Graphics::TBitmap();
		BITMAP_01ATTACH_BTN_ATTACH[i]->LoadFromFile(filename);

		filename = frmMain->IMAGEUIPATH + "02Attach_btnAdd" + IntToStr(i) + ".bmp";
		BITMAP_01ATTACH_BTN_ADD[i] 	= new Graphics::TBitmap();
		BITMAP_01ATTACH_BTN_ADD[i]->LoadFromFile(filename);
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
	//move at create()
	btnAttach   = new Graphics::TBitmap();
	btnDownload = new Graphics::TBitmap();
	btnDelete 	= new Graphics::TBitmap();
	btnAttach->LoadFromFile(frmMain->IMAGEUIPATH + "02Attach_btnAttach0.bmp");
	btnDownload->LoadFromFile(frmMain->IMAGEUIPATH + "02Attach_btnDownload0.bmp");
	btnDelete->LoadFromFile(frmMain->IMAGEUIPATH + "btnDelete.bmp");


	btnFindQ->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_FIND[0]);
	btnQuery->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_QUERY[0]);
	btnInit->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_INIT[0]);
	btnWrite->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_REGIST[0]);
	btnMod->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_MODIFY[2]);
	btnDel->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_DELETE[2]);
	//
	btnFind->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_FIND[0]);
	btnList->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_LIST[0]);
	btnRegist->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_REGIST[0]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::funcDeleteButtonImage()
{
	for(int i = 0; i < 2; i++)
	{
		delete BITMAP_01ATTACH_BTN_FIND[i];
		BITMAP_01ATTACH_BTN_FIND[i] = NULL;
		delete BITMAP_01ATTACH_BTN_QUERY[i];
		BITMAP_01ATTACH_BTN_QUERY[i] = NULL;
		delete BITMAP_01ATTACH_BTN_INIT[i];
		BITMAP_01ATTACH_BTN_INIT[i] = NULL;
		delete BITMAP_01ATTACH_BTN_REGIST[i];
		BITMAP_01ATTACH_BTN_REGIST[i] = NULL;
		delete BITMAP_01ATTACH_BTN_DOWNLOAD[i];
		BITMAP_01ATTACH_BTN_DOWNLOAD[i] = NULL;
		//
		delete BITMAP_01ATTACH_BTN_LIST[i];
		BITMAP_01ATTACH_BTN_LIST[i] = NULL;
		delete BITMAP_01ATTACH_BTN_REGIST[i];
		BITMAP_01ATTACH_BTN_REGIST[i] = NULL;
	}

	for(int i = 0; i < 3; i++)
	{
		delete BITMAP_01ATTACH_BTN_MODIFY[i];
		BITMAP_01ATTACH_BTN_MODIFY[i] = NULL;
		delete BITMAP_01ATTACH_BTN_DELETE[i];
		BITMAP_01ATTACH_BTN_DELETE[i] = NULL;
		//
		delete BITMAP_01ATTACH_BTN_ATTACH[i];
		BITMAP_01ATTACH_BTN_ATTACH[i] = NULL;
		delete BITMAP_01ATTACH_BTN_ADD[i];
		BITMAP_01ATTACH_BTN_ADD[i] = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnQueryClick(TObject *Sender)
{
	funcSetWaitWindows(true);//210310//#ATTACH02_ETC_DEL//

	funcCheckDate();

	InitDBGrid();
	funcInitVariablesDetail();

	frmSql->funcSQLSelectAttachDoc01Query();

	lblQryCntT->Visible = true;
	lblQryCnt->Visible = true;
	lblQryCnt->Caption = m_vAttachInfoDoc01.size();

	if(m_vAttachInfoDoc01.size() > 0)
	{
		DisplayDBGrid();
	}

	funcSetWaitWindows(false);//210310//#ATTACH02_ETC_DEL//
}
//---------------------------------------------------------------------------
void __fastcall Tfrm01Attach::btnInitClick(TObject *Sender)
{
	funcInitVariablesQuery();
	InitDBGrid();
	funcInitVariablesDetail();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall Tfrm01Attach::InitDBGrid()
{
	int nCol = 0;

	this->sgList->RowCount = 2;

	this->sgList->ColWidths[nCol++] =  40; // No
	this->sgList->ColWidths[nCol++] = 250; // 토지소재
	this->sgList->ColWidths[nCol++] = 200; // 첨부문서명
	this->sgList->ColWidths[nCol++] = 120; // 결의일자
	this->sgList->ColWidths[nCol++] = 150; // 비고

	// Cells[col][row]
	nCol = 0;
	this->sgList->Cells[nCol++][0] = L"No";
	this->sgList->Cells[nCol++][0] = L"토지소재";
	this->sgList->Cells[nCol++][0] = L"첨부문서명";
	this->sgList->Cells[nCol++][0] = L"결의일자";
	this->sgList->Cells[nCol++][0] = L"비고";

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

void __fastcall Tfrm01Attach::DisplayDBGrid()
{
	AnsiString asMeasureType;
	AnsiString asStr;
	int nRow = 0;
	int nCol = 0;

	for (int i = 0; i < (int)m_vAttachInfoDoc01.size(); i++) {
		nCol = 0;
		nRow = i + 1;

		asMeasureType = m_vAttachInfoDoc01[i].MEASURE_TYPE;
		this->sgList->Cells[nCol++][nRow] = nRow;
		this->sgList->Cells[nCol++][nRow] = eFunc->funcPnuToBonbuName2(m_vAttachInfoDoc01[i].PNU, 3);
		this->sgList->Cells[nCol++][nRow] = m_vAttachInfoDoc01[i].DOC_NAME;
		asStr = (char*)m_vAttachInfoDoc01[i].PRCS_DATE;
		if( !asStr.IsEmpty() )
			asStr = asStr.SubString(1, 4) + "-" + asStr.SubString(5, 2) + "-" + asStr.SubString(7, 2);
		this->sgList->Cells[nCol++][nRow] = asStr;
		this->sgList->Cells[nCol++][nRow] = m_vAttachInfoDoc01[i].ETC_MEMO;
		this->sgList->RowCount++;
	}

	this->sgList->RowCount--;

	if (this->sgList->RowCount > 1) {
		sgList->SetFocus();
		sgList->Row = 1;

		sgListClick(NULL);
		//funcLoadDataDetail();
	}
}
// ---------------------------------------------------------------------------


void __fastcall Tfrm01Attach::funcInitVariablesQuery()
{
	edtUmdRiCdQ->Text = "";
	edtUmdRiNmQ->Text = "";
	cboGbnQ->ItemIndex = 0;
	edtBonbunQ->Text = "";
	edtBoobunQ->Text = "";
	edtPrcsDt01->Text = "";
	edtPrcsDt02->Text = "";
	edtResultQ->Text = "";

	m_vAttachInfoDoc01.clear();
	lblQryCntT->Visible = false;
	lblQryCnt->Visible = false;
	lblQryCnt->Caption = m_vAttachInfoDoc01.size();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::edtMaxChange(TObject *Sender)
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

		if (asSenderName == "edtResult" || asSenderName == "edtResultQ" || asSenderName == "edtEtc")//MaxLength : 60
		{
			if( nLength >= m_nDocNameMaxLen )
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

void __fastcall Tfrm01Attach::edtMaxKeyPress(TObject *Sender, wchar_t &Key)
{
	if( m_bMaxLength )
	{
		if(Key != 8 && Key != VK_DELETE && Key != VK_LEFT && Key != VK_RIGHT)
			Key = NULL;
		else
			m_bMaxLength = false;
	}

	if(Key == VK_RETURN)
	{
		if(Sender == edtResult)
			edtEtc->SetFocus();
//		if(Sender == edtEtc)
//			edtEtc->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::edtBox_OnExit(TObject *Sender)
{
	m_bMaxLength = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::edtBox_OnEnter(TObject *Sender)
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

void __fastcall Tfrm01Attach::edtUmdRiCdExit(TObject *Sender)
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

void __fastcall Tfrm01Attach::btnPrcsDt01Click(TObject *Sender)
{
	clndPrcsDt01->Date = Now();
	clndPrcsDt01->Visible   = true;
	clndPrcsDt02->Visible   = false;
	clndPrcsDt01->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnPrcsDt02Click(TObject *Sender)
{
	clndPrcsDt01->Visible   = false;
	clndPrcsDt02->Date = Now();
	clndPrcsDt02->Visible   = true;
	clndPrcsDt02->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::clndPrcsDt01DblClick(TObject *Sender)
{
	edtPrcsDt01->Text = clndPrcsDt01->Date.FormatString("YYYY.MM.DD");
	clndPrcsDt01->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::clndPrcsDt02DblClick(TObject *Sender)
{
	AnsiString asPrcsDateStt = "";
	AnsiString asPrcsDateEnd = "";

	edtPrcsDt02->Text = clndPrcsDt02->Date.FormatString("YYYY.MM.DD");

	asPrcsDateStt = edtPrcsDt01->Text.Trim();
	asPrcsDateStt = StringReplace(asPrcsDateStt, ".", "", TReplaceFlags()<<rfReplaceAll);
	asPrcsDateEnd = edtPrcsDt02->Text.Trim();
	asPrcsDateEnd = StringReplace(asPrcsDateEnd, ".", "", TReplaceFlags()<<rfReplaceAll);

	if( asPrcsDateEnd < asPrcsDateStt )
	{
		frmMsg->funcMessageDlg("알림:", "측량일자 종료일이 시작일보다 빠릅니다.", 3);
		edtPrcsDt02->Text = "";
		clndPrcsDt02->Visible = true;
		clndPrcsDt02->BringToFront();
		return;
	}

	clndPrcsDt02->Visible = false;
}
//---------------------------------------------------------------------------




void __fastcall Tfrm01Attach::clndMouseLeave(TObject *Sender)
{
	if (clndPrcsDt01->Showing)
		clndPrcsDt01->Visible = false;
	if (clndPrcsDt02->Showing)
		clndPrcsDt02->Visible = false;
	//
	if (clndPrcsDtR->Showing)
		clndPrcsDtR->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::edtBoobunQExit(TObject *Sender)
{
	if(edtBonbun->Text.Trim().Length() == 0)
	{
		frmMsg->funcMessageDlg("알림:", "본번을 입력해주세요.", 3);
		return;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::edtUmdRiCdQExit(TObject *Sender)
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
void __fastcall Tfrm01Attach::btnModClick(TObject *Sender)
{
	bRegistMode = false;//수정
	funcInitVariables();
	PageControl1->ActivePage = tabRegist;
	PageControl1Change(NULL);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm01Attach::btnDelClick(TObject *Sender)
{
	AnsiString asCdkeySub = "";

	frmSql->funcSQLInsertAttachInfoDoc01(DF_DELETE_RECORD);

	for(int i = 0; i < (int)m_vAttachFileDoc01.size(); i++)
	{
		//asCdkeySub.sprintf("%03d", i+1);
		asCdkeySub = m_vAttachFileDoc01[i].CDKEY_SUB;
		frmSql->funcSQLInsertAttachFileDoc01(DF_DELETE_RECORD, asCdkeySub, "", 0, "");
	}

	btnQueryClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm01Attach::funcInitVariablesDetail()
{
	lblSidoSgg->Caption 	= "";
	lblLand->Caption 		= "";
	lblPnu->Caption 		= "";
	lblResult->Caption 		= "";
	lblMeasureType->Caption = "";
	lblPrcs->Caption 		= "";

	funcInitPanelFileNm();

	btnMod->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_MODIFY[2]);
	btnDel->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_DELETE[2]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::funcLoadDataDetail()
{
	AnsiString asStr = "";
	AnsiString asPnu = m_vAttachInfoDoc01[sgList->Row - 1].PNU;

	lblSidoSgg->Caption = asPnu.SubString(1, 5);
	lblLand->Caption = asPnu.SubString(6, 5) + " " + eFunc->funcPnuToUMDRIName(asPnu.c_str(), false);
	lblPnu->Caption = eFunc->funcPnuToBonbuName2(asPnu.c_str(), 4);
	lblResult->Caption = m_vAttachInfoDoc01[sgList->Row - 1].DOC_NAME;
	//200216//cboMeasureType->ItemIndex = eFunc->funcGetKindCodeToKindIndex(101, m_vAttachInfoDoc01[sgList->Row - 1].MEASURE_TYPE);
	lblMeasureType->Caption = eFunc->funcGetKindCodeToKindName(101, m_vAttachInfoDoc01[sgList->Row - 1].MEASURE_TYPE);//200216//
	asStr = m_vAttachInfoDoc01[sgList->Row - 1].PRCS_DATE;
	if( !asStr.IsEmpty() )
		lblPrcs->Caption = asStr.SubString(1, 4) + "-" + asStr.SubString(5, 2) + "-" + asStr.SubString(7, 2);

	funcInitPanelFileNm();

	imgDownList = new TList();
	imgDelList	= new TList();
	lblKindList = new TList();
	lblFileList = new TList();

	funcRedrawPanelFileNm();

	btnMod->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_MODIFY[0]);
	btnDel->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_DELETE[0]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::funcLoadDataAttach()
{
	for(int i = 1; i < sgAddFileList->RowCount; i++)
	{
		AnsiString asFileName = sgAddFileList->Cells[2][i];
		AnsiString asFullPath = sgAddFileList->Cells[3][i];
		//strcpy(frmMain->m_vAttachFileDoc01[i].KIND_CODE, frmMain->func_readCommonTextToCode("10007", "기타").c_str());
	}
}

//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::funcInitPanelFileNm()
{
	for(int i = 0; i < m_nCompCnt; i++)
	{
		TImage *imgDown 	= (TImage *)imgDownList->Items[i];
		if(imgDown != NULL)
		{
			imgDownList->Items[i] = NULL;
			delete imgDown;
		}

		TImage *imgDel 		= (TImage *)imgDelList->Items[i];
		if(imgDel != NULL)
		{
			imgDelList->Items[i] = NULL;
			delete imgDel;
		}

		TLabel *lblKind		= (TLabel *)lblKindList->Items[i];
		if(lblKind != NULL)
		{
			lblKindList->Items[i] = NULL;
			delete lblKind;
		}

		TLabel *lblFile		= (TLabel *)lblFileList->Items[i];
		if(lblFile != NULL)
		{
			lblFileList->Items[i] = NULL;
			delete lblFile;
		}
	}

	delete imgDownList;
	delete imgDelList;
	delete lblKindList;
	delete lblFileList;
	imgDownList = NULL;
	imgDelList 	= NULL;
	lblKindList = NULL;
	lblFileList = NULL;
	m_nCompCnt = 0;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::funcRedrawPanelFileNm()
{
	int nCount = 0;
	int nLabelGap = 24;
	AnsiString asFileName = "";

	if(sgList->Row > 1)
		m_nSgListIndex = sgList->Row - 1;

	frmSql->funcSQLSelectAttachFileDoc01();

	nCount = m_vAttachFileDoc01.size();

	if(nCount <= 1)//if(nCount == 0)
	{
		pnlView->Height 		= 154;//160;
		pnlList04->Height 		= 30;//32;
		pnlFileNmD->Height 		= 30;//32;
		ScrollBox1->Height 		= 30;//32;
	}

	if(nCount > 1)
	{
		pnlList04->Height 		= 30 + nLabelGap * (nCount - 1);
		pnlFileNm->Height 		= 30 + nLabelGap * (nCount - 1);
		pnlFileNmD->Height 		= 30 + nLabelGap * (nCount - 1);

		if(nCount <= 12)
		{
			pnlView->Height 		= 154 + nLabelGap * (nCount - 1);
			pnlFileNmT->Height 		= 30 + nLabelGap * (nCount - 1);
			ScrollBox1->Height 		= 30 + nLabelGap * (nCount - 1);
		}
		else
		{
			pnlView->Height 		= 154 + nLabelGap * 11;
			pnlFileNmT->Height 		= 30 + nLabelGap * 11;
			ScrollBox1->Height 		= 30 + nLabelGap * 11;
		}
	}

	AnsiString asKind = "";
	AnsiString asFile = "";

	for(int i = 0; i < nCount; i++)
	{
		asKind = eFunc->funcGetKindCodeToKindName(1, m_vAttachFileDoc01[i].KIND_CODE);
		asKind = "[" + asKind + "]";
		asFile = (char*)m_vAttachFileDoc01[i].PATH_NAME;
		funcCreateComponents(asKind, asFile);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::funcCreateComponents(AnsiString _asKindName, AnsiString _asFileName)
{
	AnsiString asStr 	= "";

	TImage *imgDel 		= new TImage(pnlFileNmDel);
	imgDel->Parent 		= pnlFileNmDel;
	imgDel->Tag 		= m_nCompCnt;
	imgDel->SetBounds(8, 8 + m_nCompCnt * 24, 12, 12);
	imgDel->Picture->Bitmap->Assign(btnDelete);
	imgDel->OnClick 	= btnFileDelClick;
	TImage *imgDown 	= new TImage(pnlFileNmDwn);
	imgDown->Parent 	= pnlFileNmDwn;
	imgDown->Tag 		= m_nCompCnt;
	imgDown->SetBounds(4, 4 + m_nCompCnt * 24, 87, 20);
	imgDown->Picture->Bitmap->Assign(btnDownload);
	imgDown->OnClick 	= btnDownloadClick;
	TLabel *lblKind 	= new TLabel(pnlFileNmKind);
	lblKind->Parent 	= pnlFileNmKind;
	lblKind->Tag 		= m_nCompCnt;
	lblKind->Caption 	= _asKindName;
	lblKind->SetBounds(8, 8 + m_nCompCnt * 24, 80, 14);
	lblKind->Alignment  = taCenter;
	TLabel *lblFile 	= new TLabel(pnlFileName);
	lblFile->Parent 	= pnlFileName;
	lblFile->Tag 		= m_nCompCnt;
	asStr = _asFileName;
	asStr = StringReplace(_asFileName, "/", "\\", TReplaceFlags() << rfReplaceAll);
	lblFile->Caption 	= ExtractFileName(asStr);
	//lblFile->Caption 	= _asFileName;
	lblFile->SetBounds(8, 8 + m_nCompCnt * 24, 462, 14);

	imgDelList->Add(imgDel);
	imgDownList->Add(imgDown);
	lblKindList->Add(lblKind);
	lblFileList->Add(lblFile);

	m_nCompCnt++;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnDownloadClick(TObject *Sender)
{
	int nTag = dynamic_cast<TImage*>(Sender)->Tag;

	if(frmFileSave->Showing == false)
	{
		frmFileSave->m_asSelectedFullFileName = m_vAttachFileDoc01[nTag].PATH_NAME;
		frmFileSave->m_asSelectedFullFileName = StringReplace(frmFileSave->m_asSelectedFullFileName, "/", "\\", TReplaceFlags()<<rfReplaceAll);
		frmFileSave->m_nFileSize = m_vAttachFileDoc01[nTag].FILE_SIZE;
		frmFileSave->Tag = nTag;
		frmFileSave->Show();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnFileDelClick(TObject *Sender)
{
	if (Application->MessageBox(L"선택한 파일을 삭제하시겠습니까?", L"확 인", MB_YESNO) == IDYES)
	{
		int	nTag = dynamic_cast<TComponent*>(Sender)->Tag;
		AnsiString asCdkeySub = m_vAttachFileDoc01[nTag-1].CDKEY_SUB;

		lblLoading->Caption = "파일 삭제중입니다.";
		funcSetWaitWindows(true);

		if( funcDeleteFile(nTag) )
		{
			frmSql->funcSQLInsertAttachFileDoc01(DF_DELETE_RECORD, asCdkeySub, "", 0, "");
			m_vAttachFileDoc01.erase(m_vAttachFileDoc01.begin() + nTag - 1);
			m_nFileCnt--;
			frmSql->funcSQLInsertAttachInfoDoc01(DF_UPDATE_CNT);

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

void __fastcall Tfrm01Attach::btnClndDelClick(TObject *Sender)
{
	if(Sender == btnPrcsDel01)
		edtPrcsDt01->Text = "";
	else if(Sender == btnPrcsDel02)
		edtPrcsDt02->Text = "";
	//
	else if(Sender == btnPrcsDel)
		edtPrcsDt->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnCloseTypeBClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------


void __fastcall Tfrm01Attach::btnModMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	btnMod->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_MODIFY[1]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnModMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	btnMod->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_MODIFY[0]);
	btnModClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnDelMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	btnDel->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_DELETE[1]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnDelMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	btnDel->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_DELETE[0]);
	btnDelClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnDownloadMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	wchar_t wBufBtnDwnImg[64];
	TImage *tcmpBtnDwnImg;
	int nTag = dynamic_cast<TImage*>(Sender)->Tag;

	swprintf(wBufBtnDwnImg, L"btnDownload%02d", nTag);
	tcmpBtnDwnImg = (TImage*)this->FindComponent(wBufBtnDwnImg);
	tcmpBtnDwnImg->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_DOWNLOAD[1]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnDownloadMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	wchar_t wBufBtnDwnImg[64];
	TImage *tcmpBtnDwnImg;
	int nTag = dynamic_cast<TImage*>(Sender)->Tag;

	swprintf(wBufBtnDwnImg, L"btnDownload%02d", nTag);
	tcmpBtnDwnImg = (TImage*)this->FindComponent(wBufBtnDwnImg);
	tcmpBtnDwnImg->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_DOWNLOAD[0]);

	btnDownloadClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnFindQMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	btnFindQ->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_FIND[1]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnFindQMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	btnFindQ->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_FIND[0]);
	btnFindQClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnQueryMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	btnQuery->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_QUERY[1]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnQueryMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	btnQuery->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_QUERY[0]);
	btnQueryClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnInitMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	btnInit->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_INIT[1]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnInitMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	btnInit->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_INIT[0]);
	btnInitClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnFileDelMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
//
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnFileDelMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	btnFileDelClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnListClick(TObject *Sender)
{
	PageControl1Change(NULL);//[TODO]
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnRegistClick(TObject *Sender)
{
	AnsiString asCdkeySub = "";
	AnsiString asKindCode = "";
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
			if(frmSql->funcSQLInsertAttachInfoDoc01(DF_NEW_RECORD) > 0)
			{
				m_asCurrDay = Now().FormatString("yyyymmdd");

				for(int i = 0; i < nAttachCnt; i++)
				{
					asCdkeySub = "";
					asRemotePathName = "";

					asKindCode      = sgAddFileList->Cells[6][i+1];
					asLocalPathName = sgAddFileList->Cells[2][i+1];
					if(asLocalPathName.Length() > 0)
					{
						DWORD dwFileSize = 0;

						asRemotePathName = funcUploadAttach(i+1);
						if(asRemotePathName.IsEmpty())
						{
							continue;
						}

						dwFileSize = GetLocalFileSize(asLocalPathName);

						nMaxCdkeySub = i + 1;
						asCdkeySub.sprintf("%03d", nMaxCdkeySub);
						if(frmSql->funcSQLInsertAttachFileDoc01(DF_NEW_RECORD, asCdkeySub, asKindCode, dwFileSize, asRemotePathName) > 0)
							m_nFileCnt++;
					}
					else
					{
						if(nAttachCnt == 1 && asLocalPathName == "" )
						{
							frmMsg->funcMessageDlg("알림:", "첨부 파일을 1건 이상 등록해주세요.", 3);
							return;
						}
					}
				}
			}
		}
		else
		{
			int nType = DF_UPDATE_RECORD;

			//get MAX CdkeySub
			if(m_vAttachFileDoc01.size() > 0)
			{
				asCdkeySub = m_vAttachFileDoc01[m_vAttachFileDoc01.size()-1].CDKEY_SUB;
				nMaxCdkeySub = StrToInt(asCdkeySub);
			}
			else
			{
				nMaxCdkeySub = 0;
			}

			m_asRegistNo = m_asRegistCdKey.SubString(9, 5);

			if(frmSql->funcSQLInsertAttachInfoDoc01(nType) > 0)
			{
				m_asCurrDay = m_asRegistCdKey.SubString(1, 8);

				for(int i = 0; i < nAttachCnt; i++)
				{
					asCdkeySub = "";
					asRemotePathName = "";

					asLocalPathName = sgAddFileList->Cells[2][i+1];
					if(asLocalPathName.Length() > 0)
					{
						DWORD dwFileSize = 0;

						if(i < m_nFileCnt)//수정일 때, 기존 DB등록된 파일경로명과 선택한 파일경로명이 다른경우, 기존 DB 저장된 file_cnt 이하 index만 체크한다.
						{
							asKindCode      = sgAddFileList->Cells[6][i+1];

							if(asLocalPathName != m_vAttachFileDoc01[i].PATH_NAME)//파일변경됨
							{
								//FTP old-file delete
								funcDeleteFile(i+1);
								nType = DF_UPDATE_RECORD;//수정상태, 파일도 수정

								//get Current CdkeySub
								asCdkeySub = m_vAttachFileDoc01[i].CDKEY_SUB;

								asKindCode      = sgAddFileList->Cells[6][i+1];
								//FTP new-file upload
								asRemotePathName = funcUploadAttach(i+1);
								if(asRemotePathName.IsEmpty())
								{
									continue;
								}
								//Get filesize
								dwFileSize = GetLocalFileSize(asLocalPathName);
								//Update DB fileinfo
								frmSql->funcSQLInsertAttachFileDoc01(nType, asCdkeySub, asKindCode, dwFileSize, asRemotePathName);
							}
							else if(asKindCode != m_vAttachFileDoc01[i].KIND_CODE)
							{
								nType = DF_UPDATE_RECORD;//수정상태, 문서구분 수정
								//get Current CdkeySub
								asCdkeySub = m_vAttachFileDoc01[i].CDKEY_SUB;
								//Get filesize
								dwFileSize = m_vAttachFileDoc01[i].FILE_SIZE;
								asRemotePathName = m_vAttachFileDoc01[i].PATH_NAME;
								frmSql->funcSQLInsertAttachFileDoc01(nType, asCdkeySub, asKindCode, dwFileSize, asRemotePathName);
                            }
							else
								continue;
						}
						else//수정상태이지만 파일은 추가
						{
							nType = DF_NEW_RECORD;//수정상태, 파일은 추가

							nMaxCdkeySub++;
							asCdkeySub.sprintf("%03d", nMaxCdkeySub);

							asKindCode      = sgAddFileList->Cells[6][i+1];
							//FTP new-file upload
							asRemotePathName = funcUploadAttach(i+1);
							if(asRemotePathName.IsEmpty())
							{
								continue;
							}
							//Get filesize
							dwFileSize = GetLocalFileSize(asLocalPathName);
							//Update DB fileinfo
							if(frmSql->funcSQLInsertAttachFileDoc01(nType, asCdkeySub, asKindCode, dwFileSize, asRemotePathName) > 0)
								m_nFileCnt++;
						}
					}
					else
					{
						if(nAttachCnt == 1 && asLocalPathName == "" )
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

		funcSetWaitWindows(false);

		if(nAttachCnt >= 1 && m_nFileCnt == 0 && asLocalPathName != "" )//1건이면서 경로명이 비어있지 않은데...m_nFileCnt가 0이면...에러
		{
			frmMsg->funcMessageDlg("알림:", "파일이 업로드 되지 못했습니다.", 3);
			return;
		}
		else//m_nFileCnt > 0
		{
			if(frmSql->funcSQLInsertAttachInfoDoc01(DF_UPDATE_CNT) > 0)
			{
				if(bRegistMode)//등록
					frmMsg->funcMessageDlg("확인:", "<이동결의서> 등록 되었습니다.", 3);
				else//수정
					frmMsg->funcMessageDlg("확인:", "<이동결의서> 수정 되었습니다.", 3);
				funcInitVariables();
				PageControl1->ActivePage = tabQuery;//등록->조회화면으로 이동//
				PageControl1Change(NULL);
				btnQueryClick(NULL);
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

void __fastcall Tfrm01Attach::btnFindClick(TObject *Sender)
{
	frmSidoCode->lvResult->Tag = 9;
	if( frmSidoCode->Showing == false )
		frmSidoCode->Show();
	else
		frmSidoCode->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnAttachClick(TObject *Sender)
{
	if(m_asOpenFileDir.IsEmpty())
		OpenDialog1->InitialDir = ExtractFilePath(Application->ExeName);
	else
		OpenDialog1->InitialDir = m_asOpenFileDir;

	if(OpenDialog1->Execute())
	{
		m_asOpenFileDir = ExtractFilePath(OpenDialog1->FileName);

		if(OpenDialog1->Files->Count > 1)
		{
			frmMsg->funcMessageDlg("알림:", "1개의 파일만 선택해주세요.", 3);
			return;
		}

		AnsiString asFilePath = OpenDialog1->FileName;
		AnsiString asFileExt = ExtractFileExt(asFilePath);

		sgAddFileList->Cells[0][sgAddFileList->Row] = sgAddFileList->Row;
		sgAddFileList->Cells[2][sgAddFileList->Row] = asFilePath;
//		{
//			sgAddFileList->Cells[2][sgAddFileList->Row].
//			TAdvStringGrid  *pDBGrid   = (TAdvStringGrid *)sgAddFileList;
//			TCanvas  *pCanvas   = pDBGrid->Canvas;
//			pCanvas->TextOut( Rect.Left + 3, Rect.Top + 2, asFilePath );
//		}

		//sgAddFileList->Cells[5][ARow] = fullPath;
		nAttachCnt++;

		if(sgAddFileList->Row == sgAddFileList->RowCount - 1)
		{
			sgAddFileList->AddBitmap(3, sgAddFileList->RowCount, btnAttach, false, haCenter, vaTop);
			sgAddFileList->AddBitmap(4, sgAddFileList->RowCount, btnDelete, false, haCenter, vaCenter);
			sgAddFileList->RowCount++;
		}

		cboKindCode->Left = cboRect.Left;
		cboKindCode->Top  = sgAddFileList->Row * sgAddFileList->DefaultRowHeight;//cboRect.Top;
		cboKindCode->Visible = true;
		sgAddFileList->Cells[6][sgAddFileList->Row] = frmMain->m_BASECODE_001_DOC1[cboKindCode->ItemIndex].kind_code;

	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnAttachDelClick(TObject *Sender)
{
	if (sgAddFileList->Row >= nAttachCnt)//추가 건
	{
		sgAddFileList->RemoveRows(sgAddFileList->Row, 1);

		if(sgAddFileList->RowCount == nAttachCnt + 1)
		{
			m_bChanged = false;
			m_nChangedIndex = -1;
		}

//		sgAddFileList->AddBitmap(3, sgAddFileList->RowCount, btnAttach, false, haCenter, vaCenter);
//		sgAddFileList->AddBitmap(4, sgAddFileList->RowCount, btnDelete, false, haCenter, vaCenter);
//		sgAddFileList->RowCount++;

	}
	else//기등록 건
	{
		AnsiString asFtpFileName = m_vAttachFileDoc01[sgAddFileList->Row].PATH_NAME;
		AnsiString asTmpFileName = sgAddFileList->Cells[3][sgAddFileList->Row];
		if (!asTmpFileName.IsEmpty())
		{
			funcDeleteSelectFile(sgAddFileList->Row);

			sgAddFileList->Cells[1][sgAddFileList->RowCount-1] = "";
			sgAddFileList->Cells[2][sgAddFileList->RowCount-1] = "";
			sgAddFileList->Cells[3][sgAddFileList->RowCount-1] = "";

			if(sgAddFileList->RowCount == nAttachCnt + 1)
			{
				m_bChanged = false;
				m_nChangedIndex = -1;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::funcInitVariables()
{
	m_nFileCnt = 0;//실제 file 테이블에 저장된 파일 개수
	nAttachCnt = 1;//추가버튼으로 추가된 개수(실제 FTP upload 개수와 다를 수 있음)

	edtUmdRiCd->Text = "";
	edtUmdRiNm->Text = "";//190911//44760//req
	cboGbn->ItemIndex = 0;
	edtBonbun->Text = "";
	edtBoobun->Text = "";
	clndPrcsDtR->Date 	= Now();
	edtPrcsDt->Text 	= clndPrcsDtR->Date.FormatString("YYYY.MM.DD");
	//edtPrcsDt->Text = "";
	edtResult->Text = "";
	edtEtc->Text = "";

	cboKindCode->Clear();
	funcSetComboList();

	InitAttachDBGrid();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::funcLoadData()
{
	ATTACH_INFO_DOC01_STRUCT tempDoc01Attach;
	AnsiString asGbn            = "";
	AnsiString asPnu        	= "";
	AnsiString asSidoCode   	= "";
	AnsiString asSidoName   	= "";
	AnsiString asUmdRiCode  	= "";
	AnsiString asUmdRiName  	= "";
	AnsiString asBonbun     	= "";
	AnsiString asBoobun     	= "";
	AnsiString asPrcsDate   	= "";
//	nAttachCnt = 0;

	memset(&tempDoc01Attach, 0x00, sizeof(ATTACH_INFO_DOC01_STRUCT));
	memcpy(&tempDoc01Attach, &m_vAttachInfoDoc01[sgList->Row - 1], sizeof(ATTACH_INFO_DOC01_STRUCT));

	//190916
	cboMeasureType->ItemIndex = eFunc->funcGetKindCodeToKindIndex(101, tempDoc01Attach.MEASURE_TYPE);

	asPnu       = tempDoc01Attach.PNU;
	if(asPnu.Length() == 19)
	{
		asSidoCode  = asPnu.SubString(1, 5);
		asUmdRiCode = asPnu.SubString(6, 5);
		asGbn       = asPnu.SubString(11, 1);
		asBonbun    = asPnu.SubString(12, 4);
		asBoobun    = asPnu.SubString(16, 4);

		asSidoName  = eFunc->funcPnuToSGGName(asPnu.c_str());
		asUmdRiName = eFunc->funcPnuToUMDRIName(asPnu.c_str(), false);

		edtSidoCd->Text   = asSidoCode + " - " + asSidoName;
		edtUmdRiCd->Text  = asUmdRiCode;//asUmdRiCode + " " + asUmdRiName;
		edtUmdRiNm->Text  = asUmdRiName;//190911//44760//req
		cboGbn->ItemIndex = StrToInt(asGbn)-1;
		edtBonbun->Text   = StrToInt(asBonbun);
		edtBoobun->Text   = StrToInt(asBoobun);
	}

	asPrcsDate        = tempDoc01Attach.PRCS_DATE;
	if( asPrcsDate.Length() == 8)
		edtPrcsDt->Text    = asPrcsDate.SubString(1, 4) + "." + asPrcsDate.SubString(5, 2) + "." + asPrcsDate.SubString(7, 2);

	edtResult->Text   = tempDoc01Attach.DOC_NAME;
	edtEtc->Text      = tempDoc01Attach.ETC_MEMO;



	//-----------------------------------------------
	TPanel *tcmpPnlNo;
	wchar_t wBufPnlNo[30];
	TEdit *tcmpEdtPath;
	wchar_t wBufEdtPath[30];
	TEdit *tcmpEdtName;
	wchar_t wBufEdtName[30];
	AnsiString asFileName = "";

	if(sgList->Row > 1)
		m_nSgListIndex = sgList->Row - 1;

	nAttachCnt = tempDoc01Attach.FILE_CNT;
	m_nFileCnt = tempDoc01Attach.FILE_CNT;

	//-//ScrollBox1->Height = nAttachCnt * pnlAttachT->Height;

	for(int i = 0; i < nAttachCnt; i++)
	{
		sgAddFileList->Cells[0][i+1] = i+1;
		sgAddFileList->Cells[1][i+1] = eFunc->funcGetKindCodeToKindName(1, m_vAttachFileDoc01[i].KIND_CODE);
		sgAddFileList->Cells[2][i+1] = m_vAttachFileDoc01[i].PATH_NAME;
		sgAddFileList->Cells[0][i+1] = i+1;
		sgAddFileList->AddBitmap(3, i+1, btnAttach, false, haCenter, vaTop);
		sgAddFileList->AddBitmap(4, i+1, btnDelete, false, haCenter, vaCenter);
		sgAddFileList->Cells[6][i+1] = m_vAttachFileDoc01[i].KIND_CODE;
	}

	sgAddFileList->Cells[0][nAttachCnt+1] = "";
	sgAddFileList->Cells[1][nAttachCnt+1] = "";
	sgAddFileList->Cells[2][nAttachCnt+1] = "";
	sgAddFileList->AddBitmap(3, nAttachCnt+1, btnAttach, false, haCenter, vaTop);
	sgAddFileList->AddBitmap(4, nAttachCnt+1, btnDelete, false, haCenter, vaCenter);

	if(nAttachCnt == 0)//수정모드//첨부파일 한 개도 없었을 경우: 파일 첨부하기, 추가 1 row 보이기
	{
		nAttachCnt = 1;
	}

	sgAddFileList->RowCount	= nAttachCnt + 2;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnPrcsDtClick(TObject *Sender)
{
	clndPrcsDtR->Date = Now();
	clndPrcsDtR->Visible = true;
	clndPrcsDtR->Date = Now();
	clndPrcsDtR->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::clndPrcsDtRDblClick(TObject *Sender)
{
	edtPrcsDt->Text = clndPrcsDtR->Date.FormatString("YYYY.MM.DD");
	clndPrcsDtR->Visible = false;
}
//---------------------------------------------------------------------------

AnsiString __fastcall Tfrm01Attach::funcUploadAttach(int _nIndex)
{
	FTP_FILE_STRUCT	mUploadFile;
	AnsiString asTarget 		= "DOCUMENT01_ATTACH";
	AnsiString asRemoteFilePath = "";
	AnsiString asRemoteFileName = "";
	AnsiString asLocalFilePath 	= "";
//	AnsiString asIndex = Now().FormatString("yyyymmdd");
	AnsiString asCdkeySub 		= "";
	AnsiString asPathName       = "";
	AnsiString asFileName       = "";

	asPathName = sgAddFileList->Cells[2][_nIndex];
	if(asPathName.Length() == 0)
		return "";

	asFileName = ExtractFileName(asPathName);
	if(asFileName.Length() == 0)
		return "";

	asLocalFilePath = asPathName;
	asRemoteFileName = asFileName;
	memset(&mUploadFile, 0x00, sizeof(mUploadFile));
	wsprintf(mUploadFile.cTarget, "%s", asTarget.c_str());
	wsprintf(mUploadFile.cFileName, "%s", asRemoteFileName.c_str());
	wsprintf(mUploadFile.cLocalFilePath, "%s", asLocalFilePath.c_str());//Local File Path
	wsprintf(mUploadFile.cFileType, "%s", asLocalFilePath.SubString(asLocalFilePath.Length() - 2, 3));
	asCdkeySub.sprintf("%03d", nMaxCdkeySub);
	wsprintf(mUploadFile.cIndexPolder, "%s/", (m_asCurrDay + m_asRegistNo + asCdkeySub).c_str());//cIndexPolder

	if (!frmFtpControl->FuncFtpFileUpload(0, &mUploadFile, 0))
	{
		return asRemoteFilePath;
	}

	//210226//asRemoteFilePath.sprintf("%s%s/%s%s", frmMain->INIINFO.FTPROOT, mUploadFile.cTarget, mUploadFile.cIndexPolder, mUploadFile.cFileName);
	asRemoteFilePath.sprintf("%s/%s%s", mUploadFile.cTarget, mUploadFile.cIndexPolder, mUploadFile.cFileName);
	return asRemoteFilePath;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::edtBoobunExit(TObject *Sender)
{
	if(edtBonbun->Text.Trim().Length() == 0)
	{
		frmMsg->funcMessageDlg("알림:", "본번을 입력해주세요.", 3);
		return;
	}
}
//---------------------------------------------------------------------------
__int64 __fastcall Tfrm01Attach::GetLocalFileSize(AnsiString _asFileName)
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

void __fastcall Tfrm01Attach::btnAttachAddMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	wchar_t wBufBtnAddImg[64];
	TImage *tcmpBtnAddImg;
	int nTag = dynamic_cast<TImage*>(Sender)->Tag;

	swprintf(wBufBtnAddImg, L"btnAttachAdd%02d", nTag);
	tcmpBtnAddImg = (TImage*)this->FindComponent(wBufBtnAddImg);
	tcmpBtnAddImg->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_ADD[1]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnFindMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	btnFind->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_FIND[1]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnFindMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	btnFind->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_FIND[0]);
	btnFindClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnListMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	btnList->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_LIST[1]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnListMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	btnList->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_LIST[0]);
	btnListClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnRegistMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	if(bRegistMode) //등록
		btnRegist->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_REGIST[1]);
	else//수정
		btnRegist->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_MODIFY[1]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnRegistMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if(bRegistMode) //등록
		btnRegist->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_REGIST[0]);
	else//수정
		btnRegist->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_MODIFY[0]);

	btnRegistClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnAttachMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	wchar_t wBufBtnAttImg[64];
	TImage *tcmpBtnAttImg;
	int nTag = dynamic_cast<TImage*>(Sender)->Tag;

	swprintf(wBufBtnAttImg, L"btnAttach%02d", nTag);
	tcmpBtnAttImg = (TImage*)this->FindComponent(wBufBtnAttImg);
	tcmpBtnAttImg->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_ATTACH[1]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnWriteMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	btnWrite->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_REGIST[1]);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::btnWriteMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	btnWrite->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_REGIST[0]);
	btnWriteClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm01Attach::btnWriteClick(TObject *Sender)
{
	m_asRegistCdKey = "";

	m_asRegistNo = frmSql->funcSQLSelectAttachDoc01MaxRegistNo();

	bRegistMode = true;//등록
	funcInitVariables();
	PageControl1->ActivePage = tabRegist;
	PageControl1Change(NULL);
}
//---------------------------------------------------------------------------
void __fastcall Tfrm01Attach::btnFindQClick(TObject *Sender)
{
	frmSidoCode->lvResult->Tag = 10;
	if( frmSidoCode->Showing == false )
		frmSidoCode->Show();
	else
		frmSidoCode->BringToFront();
}
//---------------------------------------------------------------------------
void __fastcall Tfrm01Attach::PageControl1Change(TObject *Sender)
{
	if(PageControl1->ActivePage == tabRegist)
	{
		if(bRegistMode) //등록
		{
			m_asRegistCdKey = "";

			m_asRegistNo = frmSql->funcSQLSelectAttachDoc01MaxRegistNo();

			funcInitVariables();

			edtUmdRiCd->SetFocus();

			edtSidoCd->Text = frmMain->_SIDOCODE + " " + frmMain->_SIDONAME;
			btnRegist->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_REGIST[0]);
		}
		else//수정
		{
			funcLoadData();
			edtSidoCd->Text = frmMain->_SIDOCODE + " - " + frmMain->_SIDONAME;
			btnRegist->Picture->Bitmap->Assign(BITMAP_01ATTACH_BTN_MODIFY[0]);
		}
	}
	else if(PageControl1->ActivePage == tabQuery)
	{
		//[TODO] 작성 중 조회 화면으로 이동시 조회했던 내용 초기화 할지 여부//funcInitVariablesQuery();
		edtSidoCd->Text = frmMain->_SIDOCODE + " " + frmMain->_SIDONAME;
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::PageControl1Changing(TObject *Sender, bool &AllowChange)
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

void __fastcall Tfrm01Attach::funcCheckDate()
{
	AnsiString asPrcsDateStt 	= "";
	AnsiString asPrcsDateEnd 	= "";

	//
	asPrcsDateStt = frm01Attach->edtPrcsDt01->Text.Trim();
	if( asPrcsDateStt.IsEmpty() && !asPrcsDateEnd.IsEmpty() )
	{
		frmMsg->funcMessageDlg("알림:", "결의일자의 시작일이 없어 검색조건에서 제외됩니다.", 3);
		return;
	}

	asPrcsDateEnd = frm01Attach->edtPrcsDt02->Text.Trim();
	if( !asPrcsDateStt.IsEmpty() && asPrcsDateEnd.IsEmpty() )
	{
		frmMsg->funcMessageDlg("알림:", "결의일자의 종료일이 없어 검색조건에서 제외됩니다.", 3);
		return;
	}

	m_bQryPrcsDt = true;
}
//---------------------------------------------------------------------------

bool __fastcall Tfrm01Attach::funcDeleteFile(int _nTag)
{
	FTP_FILE_STRUCT	mDeleteFile;
	AnsiString  asTarget = "DOCUMENT01_ATTACH";
	AnsiString	asRemoteFile;
	AnsiString	asRemoteDir;
	AnsiString  asRemoteFilePath;
	AnsiString	asRemoteFullFilePath;

	//---
	memset(&mDeleteFile, 0x00, sizeof(mDeleteFile));
	asRemoteFullFilePath    = frm01Attach->m_vAttachFileDoc01[_nTag-1].PATH_NAME;
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

bool __fastcall Tfrm01Attach::funcCheckEditText()
{
	AnsiString asSidoCode 	= frm01Attach->edtSidoCd->Text.SubString(1, 5);
	AnsiString asUmdRiCode 	= frm01Attach->edtUmdRiCd->Text;
	AnsiString asBonbun 	= frm01Attach->edtBonbun->Text;
	AnsiString asBoobun 	= frm01Attach->edtBoobun->Text;
	AnsiString asResultName = frm01Attach->edtResult->Text;

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
		frmMsg->funcMessageDlg("알림:", "첨부문서명을 입력해주세요.", 3);
		return false;
	}

	if(cboMeasureType->ItemIndex < 0)
	{
		frmMsg->funcMessageDlg("알림:", "이동종목을 선택해주세요.", 3);
		return false;
    }

	return true;
}
//---------------------------------------------------------------------------
void __fastcall Tfrm01Attach::funcSetWaitWindows(bool bSetValue)
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

bool __fastcall Tfrm01Attach::funcCheckWroteData()
{
	if(edtUmdRiCd->Text != "")
		return true;
	if(edtBonbun->Text != "")
		return true;
	if(edtBoobun->Text != "")
		return true;
	if(edtPrcsDt->Text != "")
		return true;
	if(edtResult->Text != "")
		return true;
	if(edtEtc->Text != "")
		return true;

	return false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(frm01Attach->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::funcRegistKeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN)
	{
		if(Sender == edtUmdRiCd)
//			edtUmdRiNm->SetFocus();
//		if(Sender == edtUmdRiNm)
			cboGbn->SetFocus();
		if(Sender == cboGbn)
			edtBonbun->SetFocus();
		if(Sender == edtBonbun)
			edtBoobun->SetFocus();
		if(Sender == edtBoobun)
			edtResult->SetFocus();
//		if(Sender == edtResult)
//			edtEtc->SetFocus();
//		if(Sender == edtBoobun)//maskedit가 enabled=false 상태라 setfocus가 안됨//부번 입력 후 파일 선택(btnInspct는 이미지라 focus 안됨)
//			btnAttachClick(btnAttach01);
//			btnInspctDtClick(NULL);
//		if(Sender == btnInspctDt)
//			btnPrcsDtClick(NULL);
//		if(Sender == btnPrcsDt)
//			btnAttachClick(btnAttach01);

		Sender = NULL;
		Key = NULL;
    }

	if(Sender == cboGbn && (Key == '1' || Key == '2'))
	{
		cboGbn->ItemIndex = Key - '1';
		cboGbn->Refresh();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::funcQueryKeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN)
	{
		if(Sender == edtUmdRiCdQ)
//			edtUmdRiNmQ->SetFocus();
//		if(Sender == edtUmdRiNmQ)
			cboGbnQ->SetFocus();
		if(Sender == cboGbnQ)
			edtBonbunQ->SetFocus();
		if(Sender == edtBonbunQ)
			edtBoobunQ->SetFocus();
		if(Sender == edtBoobunQ)
			edtResultQ->SetFocus();
		if(Sender == edtResultQ)
//			cboKindCodeQ->SetFocus();
//		if(Sender == cboKindCodeQ)
			cboMeasureTypeQ->SetFocus();
		if(Sender == cboMeasureTypeQ)//maskedit가 enabled=false 상태라 setfocus가 안됨//부번 입력 후 파일 선택(btnInspct는 이미지라 focus 안됨)
			btnQueryClick(NULL);
//			edtPrcsDt01->SetFocus();
//		if(Sender == edtPrcsDt01)
//			edtPrcsDt02->SetFocus();
//		if(Sender == edtPrcsDt02)
//			btnQueryClick(NULL);

		Sender = NULL;
		Key = NULL;
	}

	if(Sender == cboGbnQ && (Key == '1' || Key == '2'))
	{
		cboGbnQ->ItemIndex == Key - 47;//'전체'도 있음.
		cboGbnQ->Refresh();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::InitAttachDBGrid()
{
	int nCol = 0;

	//sgAddFileList
	sgAddFileList->ColWidths[0] = 30;//NO
	sgAddFileList->ColWidths[1] = 100;//KIND_NAME
	sgAddFileList->ColWidths[2] = 500;//PATH_NAME
	sgAddFileList->ColWidths[3] = 90;//[BTN]파일찾기
	sgAddFileList->ColWidths[4] = 40;//[BTN]DELETE
	sgAddFileList->ColWidths[5] = 0;//FTP PATH
	sgAddFileList->ColWidths[6] = 0;//KIND_CODE

	sgAddFileList->Cells[0][0] = L"No";
	sgAddFileList->Cells[1][0] = L"문서구분";
	sgAddFileList->Cells[2][0] = L"파일경로";
	sgAddFileList->Cells[3][0] = L"파일찾기";
	sgAddFileList->Cells[4][0] = L"삭제";
	sgAddFileList->Cells[5][0] = L"FTP PATH";
	sgAddFileList->Cells[6][0] = L"KIND_CODE";
	::UpdateWindow(sgAddFileList->Handle);

	sgAddFileList->ControlLook->DropDownAlwaysVisible = true;//for ComboBox

	for (int i = 1; i < sgAddFileList->RowCount; i++) {
		sgAddFileList->Rows[i]->Clear();
	}

	sgAddFileList->AddBitmap(3, 1, btnAttach, false, haCenter, vaTop);
	sgAddFileList->AddBitmap(4, 1, btnDelete, false, haCenter, vaCenter);

	sgAddFileList->RowCount = 2;

	nAttachCnt = 0;
}
// ---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::DisplayAttachDBGrid()
{
	int nRow = 0;
	int nCol = 0;

	for (int i = 0; i < (int)m_vAttachInfoDoc01.size(); i++) {
		nCol = 0;
		nRow = i + 1;

		this->sgAddFileList->Cells[nCol++][nRow] = nRow;
		this->sgAddFileList->Cells[nCol++][nRow] = eFunc->funcPnuToBonbuName2(m_vAttachInfoDoc01[i].PNU, 3);
		this->sgAddFileList->Cells[nCol++][nRow] = m_vAttachInfoDoc01[i].DOC_NAME;
		this->sgAddFileList->Cells[nCol++][nRow] = eFunc->funcGetKindCodeToKindName(101, m_vAttachInfoDoc01[i].MEASURE_TYPE);
		this->sgAddFileList->Cells[nCol++][nRow] = m_vAttachInfoDoc01[i].PRCS_DATE;
		this->sgAddFileList->RowCount++;
	}

	this->sgAddFileList->RowCount--;

	if (this->sgAddFileList->RowCount > 1) {
		sgAddFileList->SetFocus();
		sgAddFileList->Row = 1;
	}
}
// ---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::sgAddFileListClickCell(TObject *Sender, int ARow, int ACol)
{
	bool m_bCheck = false;

	//=======================================================
	if (ACol == 1)//문서구분//
	{
		cboKindCode->Left = cboRect.Left;
		cboKindCode->Top  = ARow * sgAddFileList->DefaultRowHeight;//cboRect.Top;
		cboKindCode->Visible = true;
		AnsiString asStr = sgAddFileList->Cells[6][ARow];
		cboKindCode->ItemIndex = eFunc->funcGetKindCodeToKindIndex(1, asStr.c_str());
		//sgAddFileList->Cells[1][ARow] = frmSql->m_BASECODE_101_DOC1[sgAddFileList->Combobox->ItemIndex].kind_name;
	}
	//=======================================================
	else if (ACol == 3)//파일찾기//
	{
		cboKindCode->Visible = false;
		cboKindCode->ItemIndex = 0;
		sgAddFileList->Row = ARow;
		btnAttachClick(NULL);
	}
	//=======================================================
	else if (ACol == 4)//삭제
	{
		cboKindCode->Visible = false;
		cboKindCode->ItemIndex = 0;
		sgAddFileList->Row = ARow;
		btnAttachDelClick(NULL);
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::sgAddFileListDblClickCell(TObject *Sender, int ARow, int ACol)
{
	//파일 보기 클릭//
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::sgAddFileListGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign, TVAlignment &VAlign)
{
	if (ACol == 2) {
		HAlign = taLeftJustify;
	}
	else {
		HAlign = taCenter;
	}
	VAlign = vtaCenter;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::sgAddFileListHasComboBox(TObject *Sender, int ACol, int ARow, bool &HasComboBox)
{
//	AnsiString asStr = sgAddFileList->Cells[2][ARow];
//
//	if(ARow == sgAddFileList->Row && asStr.Length() > 0 && ACol == 1)
//		HasComboBox = true;
//	else
//		HasComboBox = false;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::sgAddFileListSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
//	if(ARow == sgAddFileList->Row && ACol == 1)
//	{
//		sgAddFileList->Options >> goEditing;
//		sgAddFileList->EditorMode = true;
//	}
//	else
//	{
//		sgAddFileList->Options << goEditing;
//		sgAddFileList->EditorMode = false;
//	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::sgAddFileListGetEditorType(TObject *Sender, int ACol, int ARow, TEditorType &AEditor)
{
//	AnsiString asStr = sgAddFileList->Cells[2][ARow];
//
//	if(ARow == sgAddFileList->Row && asStr.Length() > 0 && ACol == 1)
//	{
//		AEditor= edComboList;
//		sgAddFileList->Combobox->Items->Clear();
//		sgAddFileList->Combobox->OnClick = sgAddFileListCombobox_OnClick;
//		funcSetComboList();
//	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::funcSetComboList()
{
	for(int i = 0; i < (int)frmMain->m_BASECODE_001_DOC1.size(); i++)
	{
		cboKindCode->Items->Add(frmMain->m_BASECODE_001_DOC1[i].kind_name);
	}

	if((int)frmMain->m_BASECODE_001_DOC1.size() > 0)
		cboKindCode->ItemIndex = 0;

//	for(int i = 0; i < (int)frmSql->m_BASECODE_101_DOC1.size(); i++)
//	{
//		sgAddFileList->Combobox->Items->Add(frmSql->m_BASECODE_101_DOC1[i].kind_name);
//	}
//
//	if((int)frmSql->m_BASECODE_101_DOC1.size() > 0)
//		sgAddFileList->Combobox->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::funcDeleteSelectFile(int _nIndex)
{
	AnsiString strMessage = "선택한 파일을 삭제하시겠습니까?";
	frmMsg->funcMessageDlg("알림:", "선택한 파일을 삭제하시겠습니까?", 1);

//	if (frmMessage->m_bClick == 1) // Yes
//	{
//		AnsiString asRemotePathName = frmMain->m_vATTACHFILE[_nIndex].ATTACH_PATH;
//		AnsiString asSeqNo = frmMain->m_vATTACHFILE[_nIndex].SEQNO;
//
//		m_asAttachCdKey = m_sAcceptCdKey;
//
//		// 시연용--------------------------------------------------------->>>
//		if(frmMain->m_bATTACH)
//		{
//			frmMain->func_SQLWrite_AttachFile(DF_DELETE_RECORD, StrToInt(asSeqNo), "Y", asRemotePathName);
//			frmMsg->funcMessageDlg("알림:", "파일을 삭제하였습니다.", 3);
//		}
//		else
//		{
//			if( funcDeleteFile(asRemotePathName) )
//			{
//				frmMain->func_SQLWrite_AttachFile(DF_DELETE_RECORD, StrToInt(asSeqNo), "Y", asRemotePathName);
//				frmMsg->funcMessageDlg("알림:", "파일을 삭제하였습니다.", 3);
//			}
//		}
//
//		//
//		sgAddFileList->RemoveRows(_nIndex, 1);
//		if(frmMain->m_vATTACHFILE.size() > 0)
//		{
//			nAttachCnt--;
//			if(frmMain->m_vATTACHFILE.size() == 1)
//				frmMain->m_vATTACHFILE.clear();
//			else
//				frmMain->m_vATTACHFILE.erase(frmMain->m_vATTACHFILE.begin() + _nIndex);
//		}//
//	}
//	else // No
//	{
//		return;
//	}
}
// ---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::sgAddFileListCombobox_OnClick(TObject *Sender)
{
//	sgAddFileList->Cells[1][sgAddFileList->Row] = frmSql->m_BASECODE_101_DOC1[sgAddFileList->Combobox->ItemIndex].kind_name;
//	sgAddFileList->Combobox->Items->Clear();
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::cboKindCodeClick(TObject *Sender)
{
	sgAddFileList->Cells[1][sgAddFileList->Row] = frmMain->m_BASECODE_001_DOC1[cboKindCode->ItemIndex].kind_name;
	cboKindCode->Visible = false;
	sgAddFileList->Cells[6][sgAddFileList->Row] = frmMain->m_BASECODE_001_DOC1[cboKindCode->ItemIndex].kind_code;
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::sgAddFileListDrawCell(TObject *Sender, int ACol, int ARow,
		  TRect &Rect, TGridDrawState State)
{
	TAdvStringGrid  *pDBGrid   = (TAdvStringGrid *)Sender;
	TCanvas  *pCanvas   = pDBGrid->Canvas;

	//--------------------------------------------------------------------------
	//파일경로명에 공백이 있으면 개행이 되어 보이지 않는다.
	//아래와 같이 처리하면 개행되어 보여졌던 이전 데이터를 지우고 다시 그린다//
	//그런데 WordWrap=false로 설정하면 아래와 같이 할 필요 없다//
//	if(ACol == 2 && ARow > 0)
//	{
//		AnsiString strValue = pDBGrid->Cells[ACol][ARow];
//
//		TColor crOldBrushColor = pCanvas->Brush->Color;
//		TColor crOldPenColor   = pCanvas->Pen->Color;
//		pCanvas->Brush->Color = (TColor)RGB( 255, 255, 255 );
//		TBrushStyle nOldBrushStyle = pCanvas->Brush->Style;
//		int OldBkMode = ::SetBkMode( pCanvas->Handle, TRANSPARENT );
//		pCanvas->Brush->Style = bsClear;
//		pCanvas->TextOut( Rect.Left, Rect.Top + 1, "" );
//
//		pCanvas->Brush->Color = crOldBrushColor;
//		pCanvas->Pen->Color   = crOldPenColor;
//		pCanvas->Brush->Style = nOldBrushStyle;
//		pCanvas->TextOut( Rect.Left, Rect.Top + 3, strValue );
//		::SetBkMode( pCanvas->Handle, OldBkMode );
//	}

	//--------------------------------------------------------------------------
	if(ARow != 0 && ARow == sgAddFileList->Row && ACol == 1)//New Line
	{
		cboRect = Rect;
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::sgListClick(TObject *Sender)
{
	if((int)m_vAttachInfoDoc01.size() > 0)
	{
		m_asRegistCdKey = m_vAttachInfoDoc01[sgList->Row - 1].REGIST_CDKEY;

		funcInitVariablesDetail();

		funcLoadDataDetail();
	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::sgListDrawCell(TObject *Sender, int ACol, int ARow,
		  TRect &Rect, TGridDrawState State)
{
	TAdvStringGrid  *pDBGrid   = (TAdvStringGrid *)Sender;
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
	if(ARow != 0 && ACol == 2 && strValue.Length() > 28)//190215
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
		pCanvas->TextOut( X, realRect.Top + 4, asStrNext );
	}
	else
	{
		pCanvas->TextOut( X, realRect.Top + 2, strValue );
	}

	//--------------------------------------------------------------------------
	pCanvas->Brush->Style = nOldBrushStyle;
	::SetBkMode( pCanvas->Handle, OldBkMode );
	//--------------------------------------------------------------------------
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::sgListDblClick(TObject *Sender)
{
//	if((int)m_vAttachInfoDoc01.size() > 0)
//	{
//		m_asRegistCdKey = m_vAttachInfoDoc01[sgList->Row - 1].REGIST_CDKEY;
//
//		funcLoadDataDetail();
//	}
}
//---------------------------------------------------------------------------

void __fastcall Tfrm01Attach::cboSortClick(TObject *Sender)
{
	btnQueryClick(btnQuery);
}
//---------------------------------------------------------------------------

