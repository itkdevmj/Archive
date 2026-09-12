//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#pragma warn -8004

TfrmSidoCode *frmSidoCode;
//---------------------------------------------------------------------------
__fastcall TfrmSidoCode::TfrmSidoCode(TComponent* Owner)
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
		this->panWindowsMove->Color			= (TColor)RGB(R, G, B);
		//pnlWaitT->Color//
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSidoCode::FormCreate(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TfrmSidoCode::FormShow(TObject *Sender)
{
	if(frmMain->m_nActiveDoc == 9)//220104//논산 공시지가(DOC09)에 블럭지번 포함//
		frmMain->funcSetComboGbn(2, 1);//상세검색 & 블록지번//
	else
		frmMain->funcSetComboGbn(2, 1);//상세검색 & 일반지번//

	if(frmMain->palMainSearchBar->Visible)
	{
		this->Left	= frmMain->Left + frmMain->palMainSearchBar->Left + frmMain->palMainSearchBar->Width + 8;
		this->Top	= frmMain->Top + 49 + 8;//200313//panWindowsMove삭제//사장님Req//frmMain->Top + frmMain->panWindowsMove->Height + 49 - panWindowsMove->Height + 8;
	}
	else
	{
		this->Left	= frmMain->Left + frmMain->palMiniSearchBar->Left;
		this->Top	= frmMain->Top + frmMain->palMiniSearchBar->Top	+ frmMain->palMiniSearchBar->Height + frmMain->EDGEGAP;
	}

	if(this->lvResult->Tag == 1 || this->lvResult->Tag == 3)//상세검색창//LMREQ_Write//
	{
		pnlBlank->Top		= 62;
		pnlBlank->Visible	= true;
	}
	else
	{
		pnlBlank->Visible	= false;
		cboGbn->ItemIndex	= 0;
		edtBobn->Text		= "";
		edtBubn->Text		= "";
		cboGbn->Enabled	    = false;
		edtBobn->Enabled	= false;
		//200926//edtBubn->Enabled	= false;
    }

	funcLoadButtonImage();

	btnSidoCodeSearch->BringToFront();
	edtInputStr->Clear();
	lvResult->Clear();
	edtInputStr->SetFocus();

	unsigned long Conversion, Sentence;
	HIMC Mode = ImmGetContext(Application->Handle);
	ImmGetConversionStatus(Mode, &Conversion, &Sentence);
	if (Conversion == IME_CMODE_HANGEUL){}
	else
		ImmSetConversionStatus(Mode, IME_CMODE_HANGEUL, IME_CMODE_HANGEUL);

	//MINJI
//	if (edtInputStr->Text.IsEmpty())
//		return;

	funcAllUmdRiCode();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSidoCode::funcAllUmdRiCode()
{
	AnsiString asStrSgg = "";
	AnsiString asStrUmd = "";
	AnsiString asStrRi 	= "";
	String sStrUmd = L"";
	String sStrRi = L"";
	AnsiString asStrC 	= "";

	char cCode[32];
	char cCodeName[64+32];//case (this->lvResult->Tag == 6)

	for (int i=0; i<(int)frmMain->m_vDATA_SIDOCODE.size(); i++)
	{
		asStrSgg = frmMain->m_vDATA_SIDOCODE[i].cSggNm;
		asStrUmd = frmMain->m_vDATA_SIDOCODE[i].cUmdNm;
		asStrRi = frmMain->m_vDATA_SIDOCODE[i].cRiNm;

		sStrUmd = asStrUmd;
		sStrRi = asStrRi;

		//201222//44760 000 00 제외//
		if(!strcmp((char*)frmMain->m_vDATA_SIDOCODE[i].cUmdCd, "000") && !strcmp((char*)frmMain->m_vDATA_SIDOCODE[i].cRiCd, "00"))
			continue;

		//201215//읍면 명칭은 제거//동지역은 나와야 하므로//
		if(strcmp((char*)frmMain->m_vDATA_SIDOCODE[i].cUmdCd, "200") > 0 && !strcmp((char*)frmMain->m_vDATA_SIDOCODE[i].cRiCd, "00"))
			continue;

		memset(&cCode, 0, sizeof(cCode));
		if( !strcmp((char*)frmMain->m_vDATA_SIDOCODE[i].cUmdCd, "000") && !strcmp((char*)frmMain->m_vDATA_SIDOCODE[i].cRiCd, "00"))
			wsprintf(cCode, "%s", frmMain->m_vDATA_SIDOCODE[i].cSggCd);
		else
			wsprintf(cCode, "%s %s%s", frmMain->m_vDATA_SIDOCODE[i].cSggCd, frmMain->m_vDATA_SIDOCODE[i].cUmdCd, frmMain->m_vDATA_SIDOCODE[i].cRiCd);
		asStrC = cCode;

		TListItem *pListItem = lvResult->Items->Add();
		pListItem->Caption = asStrC;

		memset(&cCodeName, 0, sizeof(cCodeName));
		if(this->lvResult->Tag == 6)//190123
		{
			wsprintf(cCodeName, "%s %s %s", asStrSgg, asStrUmd, asStrRi);
		}
		else
		{
			if(frmMain->_SIDOCODE == "36110" && (this->lvResult->Tag == 0 || this->lvResult->Tag == 1))//210111//
				wsprintf(cCodeName, "%s %s %s", asStrSgg, asStrUmd, asStrRi);
//=============================================================================
//v1.0.0.6//11305//강북구//
			else if(frmMain->INIINFO.SIDOCODE == "11305")
				wsprintf(cCodeName, "%s %s %s", asStrSgg, asStrUmd, asStrRi);
//=============================================================================
			else
				wsprintf(cCodeName, "%s %s", asStrUmd, asStrRi);
		}
		asStrC = cCodeName;

		pListItem->SubItems->Add(asStrC);
		pListItem->SubItems->Add(IntToStr(i));
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSidoCode::edtInputStrKeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN) {
		btnSidoCodeSearchClick(NULL);
	}
	else{
		 if(Key == '\b') { }
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSidoCode::btnSidoCodeSearchClick(TObject *Sender)
{
	lvResult->Clear();

	if (edtInputStr->Text.IsEmpty())
	{
		funcAllUmdRiCode();
		return;
	}

	AnsiString asStrSgg = "";
	AnsiString asSggCd 	= "";//v1.0.0.6//11305//강북구//
	AnsiString asStrUmd = "";
	AnsiString asStrRi 	= "";
	AnsiString asUmdCd 	= "";
	AnsiString asRiCd 	= "";
	String sStrUmd = L"";
	String sStrRi = L"";
	AnsiString asStrC 	= "";

	char cCode[32];
	char cCodeName[64+32];//case (this->lvResult->Tag == 6)

	for (int i=0; i<(int)frmMain->m_vDATA_SIDOCODE.size(); i++)
	{
		asStrSgg 	= frmMain->m_vDATA_SIDOCODE[i].cSggNm;
		asSggCd 	= frmMain->m_vDATA_SIDOCODE[i].cSggCd;//v1.0.0.6//11305//강북구//
		asStrUmd 	= frmMain->m_vDATA_SIDOCODE[i].cUmdNm;
		asStrRi 	= frmMain->m_vDATA_SIDOCODE[i].cRiNm;
		asUmdCd	 	= frmMain->m_vDATA_SIDOCODE[i].cUmdCd;
		asRiCd		= frmMain->m_vDATA_SIDOCODE[i].cRiCd;

		sStrUmd = asStrUmd;
		sStrRi = asStrRi;

		//201215//읍면 명칭은 제거//동지역은 나와야 하므로//
		if(strcmp((char*)frmMain->m_vDATA_SIDOCODE[i].cUmdCd, "200") > 0 && !strcmp((char*)frmMain->m_vDATA_SIDOCODE[i].cRiCd, "00"))
			continue;

		if (sStrUmd.Pos(edtInputStr->Text) || sStrRi.Pos(edtInputStr->Text))
		{
			memset(&cCode, 0, sizeof(cCode));
			wsprintf(cCode, "%s %s%s", frmMain->m_vDATA_SIDOCODE[i].cSggCd, frmMain->m_vDATA_SIDOCODE[i].cUmdCd, frmMain->m_vDATA_SIDOCODE[i].cRiCd);
			asStrC = cCode;

			TListItem *pListItem = lvResult->Items->Add();
			pListItem->Caption = asStrC;

			memset(&cCodeName, 0, sizeof(cCodeName));
			if(this->lvResult->Tag == 6)
			{
				wsprintf(cCodeName, "%s %s %s", asStrSgg, asStrUmd, asStrRi);
			}
			else
			{
				if(frmMain->_SIDOCODE == "36110" && (this->lvResult->Tag == 0 || this->lvResult->Tag == 1))//210111//
					wsprintf(cCodeName, "%s %s %s", asStrSgg, asStrUmd, asStrRi);
//=============================================================================
//v1.0.0.6//11305//강북구//
				else if(frmMain->_SIDOCODE == "11305" && (this->lvResult->Tag == 0 || this->lvResult->Tag == 1))
					wsprintf(cCodeName, "%s %s %s", asStrSgg, asStrUmd, asStrRi);
//=============================================================================
				else
					wsprintf(cCodeName, "%s %s", asStrUmd, asStrRi);
			}
			asStrC = cCodeName;

			pListItem->SubItems->Add(asStrC);
			pListItem->SubItems->Add(IntToStr(i));
		}
//=============================================================================
//v1.0.0.6//11305//강북구//
		else if (asSggCd.Pos(edtInputStr->Text) || asStrSgg.Pos(edtInputStr->Text))
		{
			memset(&cCode, 0, sizeof(cCode));
			wsprintf(cCode, "%s %s%s", frmMain->m_vDATA_SIDOCODE[i].cSggCd, frmMain->m_vDATA_SIDOCODE[i].cUmdCd, frmMain->m_vDATA_SIDOCODE[i].cRiCd);
			asStrC = cCode;

			TListItem *pListItem = lvResult->Items->Add();
			pListItem->Caption = asStrC;

			memset(&cCodeName, 0, sizeof(cCodeName));
			if(this->lvResult->Tag == 6)
			{
				wsprintf(cCodeName, "%s %s %s", asStrSgg, asStrUmd, asStrRi);
			}
			else
			{
				if(frmMain->_SIDOCODE == "36110" && (this->lvResult->Tag == 0 || this->lvResult->Tag == 1))//210111//
					wsprintf(cCodeName, "%s %s %s", asStrSgg, asStrUmd, asStrRi);
				//=============================================================================
				//v1.0.0.6//11305//강북구//
				else if(frmMain->_SIDOCODE == "11305" && (this->lvResult->Tag == 0 || this->lvResult->Tag == 1))
					wsprintf(cCodeName, "%s %s %s", asStrSgg, asStrUmd, asStrRi);
				//=============================================================================
				else
					wsprintf(cCodeName, "%s %s", asStrUmd, asStrRi);
			}
			asStrC = cCodeName;

			pListItem->SubItems->Add(asStrC);
			pListItem->SubItems->Add(IntToStr(i));
		}
//=============================================================================
		else if (asUmdCd.Pos(edtInputStr->Text) || asRiCd.Pos(edtInputStr->Text))//M//191111
		{
			memset(&cCode, 0, sizeof(cCode));
			wsprintf(cCode, "%s %s%s", frmMain->m_vDATA_SIDOCODE[i].cSggCd, frmMain->m_vDATA_SIDOCODE[i].cUmdCd, frmMain->m_vDATA_SIDOCODE[i].cRiCd);
			asStrC = cCode;

			TListItem *pListItem = lvResult->Items->Add();
			pListItem->Caption = asStrC;

			memset(&cCodeName, 0, sizeof(cCodeName));
			if(this->lvResult->Tag == 6)
			{
				wsprintf(cCodeName, "%s %s %s", asStrSgg, asStrUmd, asStrRi);
			}
			else
			{
				if(frmMain->_SIDOCODE == "36110" && (this->lvResult->Tag == 0 || this->lvResult->Tag == 1))//210111//
					wsprintf(cCodeName, "%s %s %s", asStrSgg, asStrUmd, asStrRi);
//=============================================================================
//v1.0.0.6//11305//강북구//
				else if(frmMain->_SIDOCODE == "11305" && (this->lvResult->Tag == 0 || this->lvResult->Tag == 1))
					wsprintf(cCodeName, "%s %s %s", asStrSgg, asStrUmd, asStrRi);
//=============================================================================
				else
					wsprintf(cCodeName, "%s %s", asStrUmd, asStrRi);
			}
			asStrC = cCodeName;

			pListItem->SubItems->Add(asStrC);
			pListItem->SubItems->Add(IntToStr(i));
		}
		else if ((asUmdCd+asRiCd).Pos(edtInputStr->Text))
		{
			memset(&cCode, 0, sizeof(cCode));
			wsprintf(cCode, "%s %s%s", frmMain->m_vDATA_SIDOCODE[i].cSggCd, frmMain->m_vDATA_SIDOCODE[i].cUmdCd, frmMain->m_vDATA_SIDOCODE[i].cRiCd);
			asStrC = cCode;

			TListItem *pListItem = lvResult->Items->Add();
			pListItem->Caption = asStrC;

			memset(&cCodeName, 0, sizeof(cCodeName));
			if(this->lvResult->Tag == 6)
			{
				wsprintf(cCodeName, "%s %s %s", asStrSgg, asStrUmd, asStrRi);
			}
			else
			{
				if(frmMain->_SIDOCODE == "36110" && (this->lvResult->Tag == 0 || this->lvResult->Tag == 1))//210111//
					wsprintf(cCodeName, "%s %s %s", asStrSgg, asStrUmd, asStrRi);
//=============================================================================
//v1.0.0.6//11305//강북구//
				else if(frmMain->_SIDOCODE == "11305" && (this->lvResult->Tag == 0 || this->lvResult->Tag == 1))
					wsprintf(cCodeName, "%s %s %s", asStrSgg, asStrUmd, asStrRi);
//=============================================================================
				else
					wsprintf(cCodeName, "%s %s", asStrUmd, asStrRi);
			}
			asStrC = cCodeName;

			pListItem->SubItems->Add(asStrC);
			pListItem->SubItems->Add(IntToStr(i));
		}
	}

	if(lvResult->Items->Count > 0)
	{
		lvResult->SetFocus();
		lvResult->Selected = lvResult->Items->Item[0];
		lvResult->ItemFocused = lvResult->Items->Item[0];
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSidoCode::lvResultDblClick(TObject *Sender)
{
	//191115//기존 읍면동+리코드만 검색창으로 가져가는 기능에서 본번+부번까지 입력하는 기능으로 변경함
	wchar_t Key	= VK_RETURN;

	m_asCode = "";
	m_asName = "";

	int nBuffIndex = 0;

	try {
		nBuffIndex = lvResult->Selected->SubItems->Strings[1].ToInt();
	}
	catch (Exception &exception) {
		return;
	}

	if(frmMain->_SIDOCODE == "36110")//210107//#SEJONGPNU
	{
		m_asCode.sprintf("%s%s%s", frmMain->m_vDATA_SIDOCODE[nBuffIndex].cSggCd, frmMain->m_vDATA_SIDOCODE[nBuffIndex].cUmdCd, frmMain->m_vDATA_SIDOCODE[nBuffIndex].cRiCd);
		if( !strcmp(frmMain->m_vDATA_SIDOCODE[nBuffIndex].cRiCd, "00") )
			m_asName.sprintf("%s %s", frmMain->m_vDATA_SIDOCODE[nBuffIndex].cSggNm, frmMain->m_vDATA_SIDOCODE[nBuffIndex].cUmdNm);
		else
			m_asName.sprintf("%s %s %s", frmMain->m_vDATA_SIDOCODE[nBuffIndex].cSggNm, frmMain->m_vDATA_SIDOCODE[nBuffIndex].cUmdNm, frmMain->m_vDATA_SIDOCODE[nBuffIndex].cRiNm);
	}
//=============================================================================
//v1.0.0.6//11305//강북구//
	else if(frmMain->_SIDOCODE == "11305")
	{
		m_asCode.sprintf("%s%s%s", frmMain->m_vDATA_SIDOCODE[nBuffIndex].cSggCd, frmMain->m_vDATA_SIDOCODE[nBuffIndex].cUmdCd, frmMain->m_vDATA_SIDOCODE[nBuffIndex].cRiCd);
		if( !strcmp(frmMain->m_vDATA_SIDOCODE[nBuffIndex].cRiCd, "00") )
			m_asName.sprintf("%s %s", frmMain->m_vDATA_SIDOCODE[nBuffIndex].cSggNm, frmMain->m_vDATA_SIDOCODE[nBuffIndex].cUmdNm);
		else
			m_asName.sprintf("%s %s %s", frmMain->m_vDATA_SIDOCODE[nBuffIndex].cSggNm, frmMain->m_vDATA_SIDOCODE[nBuffIndex].cUmdNm, frmMain->m_vDATA_SIDOCODE[nBuffIndex].cRiNm);
	}
//=============================================================================
	else
	{
		m_asCode.sprintf("%s%s", frmMain->m_vDATA_SIDOCODE[nBuffIndex].cUmdCd, frmMain->m_vDATA_SIDOCODE[nBuffIndex].cRiCd);
		if( !strcmp(frmMain->m_vDATA_SIDOCODE[nBuffIndex].cRiCd, "00") )
			m_asName.sprintf("%s", frmMain->m_vDATA_SIDOCODE[nBuffIndex].cUmdNm);
		else
			m_asName.sprintf("%s %s", frmMain->m_vDATA_SIDOCODE[nBuffIndex].cUmdNm, frmMain->m_vDATA_SIDOCODE[nBuffIndex].cRiNm);
	}

	if(m_asCode == "00000")
	{
		m_asCode = "";
		m_asName = "";
	}

	if (this->lvResult->Tag == 0 || this->lvResult->Tag == 2 || this->lvResult->Tag == 4 || this->lvResult->Tag == 5
	 || this->lvResult->Tag == 7 || this->lvResult->Tag == 8 || this->lvResult->Tag == 9 || this->lvResult->Tag == 10)//통합검색창//
	{
		edtInputStr->Text	= m_asCode + " " + m_asName;
		cboGbn->Enabled		= true;
		edtBobn->Enabled	= true;
		cboGbn->ItemIndex   = 0;
		cboGbn->SetFocus();//201222//edtBobn->SetFocus();
	}
	else if (this->lvResult->Tag == 1)//상세검색창//
	{
		if(frmMain->_SIDOCODE == "36110" && m_asCode.Length() == 10)
		{
			if(m_asCode.SubString(1, 5) != frmMain->_SIDOCODE)//210115//#SEJONG_PNU
			{
				frmMain->edtUmdRiCd->Text 	= m_asCode.SubString(1, 10);
				frmMain->edtUmdRiNm->Text 	= m_asName;
			}
			else
			{
				frmMain->edtUmdRiCd->Text 	= m_asCode.SubString(6, 5);
				frmMain->edtUmdRiNm->Text 	= m_asName;
			}
		}
//=============================================================================
//v1.0.0.6//11305//강북구//
		else if(frmMain->_SIDOCODE == "11305" && m_asCode.Length() == 10)
		{
			if(m_asCode.SubString(1, 5) != frmMain->_SIDOCODE)
			{
				frmMain->edtUmdRiCd->Text 	= m_asCode.SubString(1, 10);
				frmMain->edtUmdRiNm->Text 	= m_asName;
			}
			else
			{
				frmMain->edtUmdRiCd->Text 	= m_asCode.SubString(6, 5);
				frmMain->edtUmdRiNm->Text 	= m_asName;
			}
        }
//=============================================================================
		else
		{
			frmMain->edtUmdRiCd->Text 	= m_asCode.SubString(1, 5);
			frmMain->edtUmdRiNm->Text 	= m_asName;
		}
//		frmMain->edtUmdRiCd->Text 	= m_asCode;
//		frmMain->edtUmdRiNm->Text 	= m_asName;
		if( !m_asCode.IsEmpty() )
		{
			frmMain->cboGbn->Enabled	= true;
			frmMain->edtBobn->Enabled	= true;
			frmMain->cboGbn->ItemIndex   = 0;
			frmMain->cboGbn->SetFocus();//201222//frmMain->edtBobn->SetFocus();
		}

		Close();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSidoCode::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(frmSidoCode->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSidoCode::btnCloseTypeBClick(TObject *Sender)
{
	funcDeleteButtonImage();
	Close();
}
//---------------------------------------------------------------------------

//MINJI
void __fastcall TfrmSidoCode::edtInputStr_OnEnter(TObject *Sender)
{
	unsigned long Conversion, Sentence;
	HIMC Mode = ImmGetContext(Application->Handle);
	ImmGetConversionStatus(Mode, &Conversion, &Sentence);
	if (Conversion == IME_CMODE_HANGEUL)//현재모드가 한글이면 패스
		;
	else//현재모드가 한글이 아니면 한/영키 누른 효과를준다.
		ImmSetConversionStatus(Mode, IME_CMODE_HANGEUL, IME_CMODE_HANGEUL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSidoCode::lvResult_OnKeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN)
		lvResultDblClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSidoCode::funcLoadButtonImage()
{
	AnsiString asPath = frmMain->ROOTPATH + "RES\\MAIN\\";
	AnsiString filename = "";

	//Button Image
	for(int i = 0; i < 2; i++)
	{
		TPngImage *imgPng = new TPngImage();
		filename = asPath + "btnFindL" + IntToStr(i) + ".png";
		imgPng->LoadFromFile(filename);
		BITMAP_BTN_FIND[i] = new Graphics::TBitmap();
		BITMAP_BTN_FIND[i]->Assign(imgPng);
		delete imgPng;
		imgPng = NULL;
		//
		imgPng = new TPngImage();
		filename = asPath + "btnAccept" + IntToStr(i) + ".png";
		imgPng->LoadFromFile(filename);
		BITMAP_BTN_ACCEPT[i] = new Graphics::TBitmap();
		BITMAP_BTN_ACCEPT[i]->Assign(imgPng);
		delete imgPng;
		imgPng = NULL;
	}

	btnSidoCodeSearch->Picture->Bitmap->Assign(BITMAP_BTN_FIND[0]);
	btnAccept->Picture->Bitmap->Assign(BITMAP_BTN_ACCEPT[0]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSidoCode::funcDeleteButtonImage()
{
	for(int i = 0; i < 2; i++)
	{
		delete BITMAP_BTN_FIND[i];
		BITMAP_BTN_FIND[i] = NULL;
		delete BITMAP_BTN_ACCEPT[i];
		BITMAP_BTN_ACCEPT[i] = NULL;
	}
}
//---------------------------------------------------------------------------

//201222//
void __fastcall TfrmSidoCode::cboGbnKeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN)
	{
		if(edtBobn->Enabled)
			edtBobn->SetFocus();
	}
	else
	{
		if(Key == 49)//Number 1
			cboGbn->ItemIndex = 0;
		else if(Key == 50)//Number 2
			cboGbn->ItemIndex = 1;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSidoCode::edtBonBuKeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN)
	{
		if(Sender == edtBobn)
		{
			if(edtBobn->Text.Trim().IsEmpty())
			{
				//200204//본번 입력 안하고 Enter누르면  <지번적용>하자//
				btnAcceptClick(btnAccept);
			}
			else
			{
				edtBubn->Enabled	= true;
				edtBubn->SetFocus();
			}
		}
		else if(Sender == edtBubn)
		{
			btnAcceptClick(btnAccept);
		}
	}
	else
	{
		if(Sender == edtBobn && (Key > 47 && Key < 58))// 0~9, backspace 예외
		{
			edtBubn->Enabled	= true;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSidoCode::btnSidoCodeSearchMouseEnter(TObject *Sender)
{
	btnSidoCodeSearch->Picture->Bitmap	= NULL;
	btnSidoCodeSearch->Picture			= NULL;
	btnSidoCodeSearch->Picture->Bitmap->Assign(BITMAP_BTN_FIND[1]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSidoCode::btnSidoCodeSearchMouseLeave(TObject *Sender)
{
 	btnSidoCodeSearch->Picture->Bitmap	= NULL;
	btnSidoCodeSearch->Picture			= NULL;
	btnSidoCodeSearch->Picture->Bitmap->Assign(BITMAP_BTN_FIND[0]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSidoCode::btnAcceptMouseEnter(TObject *Sender)
{
	btnAccept->Picture->Bitmap	= NULL;
	btnAccept->Picture			= NULL;
	btnAccept->Picture->Bitmap->Assign(BITMAP_BTN_ACCEPT[1]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSidoCode::btnAcceptMouseLeave(TObject *Sender)
{
	btnAccept->Picture->Bitmap	= NULL;
	btnAccept->Picture			= NULL;
	btnAccept->Picture->Bitmap->Assign(BITMAP_BTN_ACCEPT[0]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSidoCode::btnAcceptClick(TObject *Sender)
{
	AnsiString asGbn	= "";
	AnsiString asBobn	= edtBobn->Text.Trim();
	AnsiString asBubn	= edtBubn->Text.Trim();
	AnsiString asStr	= "";
	wchar_t Key	= VK_RETURN;

	if( m_asCode.IsEmpty() )
	{
		AnsiString strMsg = "읍면동, 리코드를 검색해주세요.";
		frmMsg->funcMessageDlg("입력 확인:", strMsg, 3);
		edtInputStr->SetFocus();
		return;
	}

	if(cboGbn->ItemIndex == 1)
		asGbn = "산";

	if( !asBobn.IsEmpty() )
	{
		if( !asBubn.IsEmpty() )
		{
			if(asBubn == "0")
				asStr	= m_asName + " " + asGbn + asBobn;
			else
				asStr	= m_asName + " " + asGbn + asBobn + "-" + asBubn;
		}
		else
		{
			asStr	= m_asName + " " + asGbn + asBobn;
			asBubn	= "0";
		}

		//241202//[통합검색].시도코드 찾기 검색결과에 시군구코드 붙여준다.//
		if(this->lvResult->Tag == 0)
		{
			if(frmMain->_SIDOCODE == "36110")//250528//#SEJONGPNU
				frmMain->m_asSearchPnu.sprintf("%s%d%04d%04d", m_asCode, cboGbn->ItemIndex + 1, asBobn.ToInt(), asBubn.ToInt());
			else
				frmMain->m_asSearchPnu.sprintf("%s%s%d%04d%04d", frmMain->_SIDOCODE, m_asCode, cboGbn->ItemIndex + 1, asBobn.ToInt(), asBubn.ToInt());
		}
		else
			frmMain->m_asSearchPnu.sprintf("%s%d%04d%04d", m_asCode, cboGbn->ItemIndex + 1, asBobn.ToInt(), asBubn.ToInt());//210201//
	}
	else
		asStr	= m_asName;

	if( asBubn.IsEmpty() )
    	asBubn = "0";

	Close();//201214//지번적용 후 시도코드창 종료//

	if(this->lvResult->Tag == 0)
	{
		if( !frmMain->edtMainSearchText->Enabled )//231121//
			frmMain->edtMainSearchText->Enabled	= true;

		frmMain->edtMainSearchText->Font->Color = clBlack;//200227
		frmMain->edtMiniSearchText->Font->Color = clBlack;//200227
		frmMain->edtMainSearchText->Text = asStr;
		frmMain->edtMainSearchText->SetFocus();
		frmMain->edtMainSearchText->SelStart = asStr.Length();
		//===================================================
		//241202//시도코드 검색해서 구성한 경우는 frmMain->m_asSearchPnu 재구성할 필요 없다.//
		frmMain->IMGFINDClick(NULL);//241202//frmMain->IMGFINDClick(frmMain->edtMainSearchText);//200609
		//===================================================
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmSidoCode::FormDeactivate(TObject *Sender)
{
//201212//deactivate할때가 아니라 검색창 혹은 메인 창을 클릭할때 사라지게 하자//Close();
}
//---------------------------------------------------------------------------

