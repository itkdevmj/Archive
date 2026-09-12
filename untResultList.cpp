#pragma link "bsSkinCtrls"
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "BaseGrid"
#pragma link "IdBaseComponent"
#pragma link "IdCoder"
#pragma link "IdCoder3to4"
#pragma link "IdCoderMIME"
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//#pragma warn -8012
#pragma warn -8004


#define IsCTRLpressed()  ( (GetKeyState(VK_CONTROL) & (1 << (sizeof(SHORT)*8-1))) != 0 )
#define IsSHIFTpressed()  ( (GetKeyState(VK_LSHIFT) & (1 << (sizeof(SHORT)*8-1))) != 0 )
#define IsSNAPSHOTpressed()  ( (GetKeyState(VK_SNAPSHOT) & (1 << (sizeof(SHORT)*8-1))) != 0 )


TfrmResultList *frmResultList;
//---------------------------------------------------------------------------
__fastcall TfrmResultList::TfrmResultList(TComponent* Owner)
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
		//pnlWaitT->Color//
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::FormCreate(TObject *Sender)
{
	eData = new classDOC08Data();
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::FormDestroy(TObject *Sender)
{
	delete eData;
	eData = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::FormShow(TObject *Sender)
{
	this->Left	= frmMain->Left - Shape1->Left;
	this->Top	= frmMain->Top + 8;

	sgHistory->Left	= 0;
	sgOwnInfo->Left	= 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::FormClose(TObject *Sender, TCloseAction &Action)
{
	eData = NULL;

	//241018//frmResultList, frmResultList2 에서 처리하면 FormClose시 소멸되므로, 설정하는 Form에서 초기화 하는 것이 맞다.//
//	frmMain->m_asLandCd	= "";
//	frmMain->m_asLandNm	= "";

	//201105//frmMain->chkResultList->Checked	= true;//201104//44760안수환Req//false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::edtHangeulEnter(TObject *Sender)
{
	unsigned long Conversion, Sentence;
	HIMC Mode = ImmGetContext(Application->Handle);
	ImmGetConversionStatus(Mode, &Conversion, &Sentence);
	if (Conversion == IME_CMODE_HANGEUL)// 현재모드가 한글이면 패스
	{
		;
	}
	else                                  // 현재모드가 한글이 아니면 한/영키 누른 효과를준다.
	{
		ImmSetConversionStatus(Mode, IME_CMODE_HANGEUL, IME_CMODE_HANGEUL);
	}
}
//---------------------------------------------------------------------------

//초기화//
void _fastcall TfrmResultList::funcInitResultList()
{
	for(int i = 0; i < sgHistory->RowCount; i++)
	{
		sgHistory->Rows[i]->Clear();
	}

	for (int i = 0; i < sgHistory->RowCount; i++) {
		for (int j = 0; j < sgHistory->ColCount - 1; j++) {
			if(j % 2)
				sgHistory->Colors[j][i] = COLOR_INPUT_BG;
			else
				sgHistory->Colors[j][i] = clWhite;
		}
	}

	for(int i = 0; i < sgOwnInfo->RowCount; i++)
	{
		sgOwnInfo->Rows[i]->Clear();
	}

	for (int i = 0; i < sgOwnInfo->RowCount; i++) {
		for (int j = 0; j < sgOwnInfo->ColCount - 1; j++) {
			if( !(j % 2) )
				sgOwnInfo->Colors[j][i] = COLOR_INPUT_BG;
			else
				sgOwnInfo->Colors[j][i] = clWhite;
		}
	}

	lblNoHistory->Color		= COLOR_HEADER_BG;
	pnlOwnInfoT->Color		= COLOR_HEADER_BG;
	lblNoOwnInfo->Color		= COLOR_HEADER_BG;

	pnlJibun->Caption	= "";
	lblWrite->Caption   = "";
	lblWrite->Visible	= false;
	btnHistory->Visible	= false;
	chkJibunOK->Checked	= false;
	edtPnu->Text	= "";
	edtLevel->Text	= "";
	edtMemo->Text	= "";
	edtDoho->Text	= "";

	if(e08DataAlpha->m_nDOCKIND == 0)
		lblMemo1->Caption	= "(지적도제";
	else if(e08DataAlpha->m_nDOCKIND == 1)
		lblMemo1->Caption	= "(임야도제";

	m_bSaved	= false;
}
//---------------------------------------------------------------------------

///구대장>연혁, 소유자정보//
void _fastcall TfrmResultList::funcDispResultList()
{
	AnsiString 	asData	 	= "";
	int 		nPos		= 0;
	int			nSizeHistory	= eData->m_nHistoryCount;
	int			nSizeOwnInfo	= eData->m_nOwnInfoCount;
	int			nDefaultColWidthHistory	= 100;//120;
	int			nDefaultColWidthOwnInfo	= 54;//65;
	int			nTxtLen		= 0;
	int			nRow		= 0;
	int			nCol		= 0;
	AnsiString  asStr		= "";

//=============================================================================
//v1.0.0.4//230905//Grid 초기화//
	funcInitResultList();
//=============================================================================

    //지번//
	pnlJibun->Caption	= frmMain->m_asLandNm;
	//=========================================================================
	//241030//#구대장한글편집#DirectTable//
	//=========================================================================
	funcDisplayDirectWriteInfo();
	//=========================================================================

	if((int)eData->m_vOldLandDocInfo.size() > 0)
	{
		//
		if(eData->m_vOldLandDocInfo[0].PNU_CHECK == 1)
			chkJibunOK->Checked	= true;
		//
		edtPnu->Text	= (char*)eData->m_vOldLandDocInfo[0].PNU_NAME;
		//
		edtLevel->Text	= (char*)eData->m_vOldLandDocInfo[0].LEVEL;
		//
		asStr	= (char*)eData->m_vOldLandDocInfo[0].MEMO;
		if(eData->m_nDOCKIND == 0)
		{
			int nPos	= asStr.AnsiPos("(지적도제");
			if(nPos > 0)
			{
				edtMemo->Text	= asStr.SubString(1, nPos-1);
				asStr	= asStr.Delete(1, nPos-1);
				asStr	= StringReplace(asStr, "(지적도제", "", TReplaceFlags() << rfReplaceAll);
				asStr	= StringReplace(asStr, "호)", "", TReplaceFlags() << rfReplaceAll);
				edtDoho->Text	= asStr;
			}
			else//210629//
			{
				edtMemo->Text	= asStr;
				edtDoho->Text	= "";//210718//
			}
		}
		else if(eData->m_nDOCKIND == 1)
		{
			int nPos	= asStr.AnsiPos("(임야도제");
			if(nPos > 0)
			{
				edtMemo->Text	= asStr.SubString(1, nPos-1);
				asStr	= asStr.Delete(1, nPos-1);
				asStr	= StringReplace(asStr, "(임야도제", "", TReplaceFlags() << rfReplaceAll);
				asStr	= StringReplace(asStr, "호)", "", TReplaceFlags() << rfReplaceAll);
				edtDoho->Text	= asStr;
			}
			else//210629//
			{
				edtMemo->Text	= asStr;
				edtDoho->Text	= "";//210718//
			}
		}
	}

	//================================================
	//연혁//
	//================================================
	sgHistory->FixedRows  	= 0;
	sgHistory->FixedCols  	= 0;
	sgHistory->RowCount 	= 5;
	nRow	= 0;
	sgHistory->RowHeights[nRow++]	= 50;//30;
	sgHistory->RowHeights[nRow++]	= 90;//80;//60;
	sgHistory->RowHeights[nRow++]	= 75;//55;
	sgHistory->RowHeights[nRow++]	= 40;//45;//25;
	sgHistory->RowHeights[nRow]		= 210;//160;//140;
	sgHistory->DefaultColWidth		= nDefaultColWidthHistory;
	sgHistory->ColWidths[sgHistory->ColCount - 1]	= 40;
	for(nRow = 0; nRow < 5; nRow++)
		sgHistory->Colors[sgHistory->ColCount - 1][nRow] 	= clBtnFace;
	nRow	= 0;
	sgHistory->Cells[sgHistory->ColCount - 1][nRow++] 	= "지목";
	sgHistory->Cells[sgHistory->ColCount - 1][nRow++] 	= "지적";
	sgHistory->MergeCells(sgHistory->ColCount - 1, nRow, 1, 2);
	sgHistory->Cells[sgHistory->ColCount - 1][nRow++] 	= "과세가격";
	sgHistory->Cells[sgHistory->ColCount - 1][nRow+1] 	= "연혁";

	//================================================
	// DB 데이터//
	//================================================
	for(int i = 0; i < eData->m_nHistoryCount; i++)
	{
		//=============================================================================
		nCol	= sgHistory->ColCount - 2 - i;

		//=============================================================================
		for(nRow = 0; nRow < 5; nRow++)
		{
			//=============================================================================
			if(nRow == 0)			asData = (char*)eData->m_vJIMOK[i].DATA;
			else if(nRow == 1)		asData = (char*)eData->m_vAREA[i].DATA;
			else if(nRow == 2)		asData = (char*)eData->m_vVALUE1[i].DATA;
			else if(nRow == 3)		asData = (char*)eData->m_vVALUE2[i].DATA;
			else if(nRow == 4)		asData = (char*)eData->m_vHISTORY[i].DATA;

			//=============================================================================
			//Data
			if(asData	== "-")
			{
				//[연혁]
				if(nRow == 4 && m_INI_EMPTY)	asData	= "빈칸";
				else      						asData	= "";
			}
			//=============================================================================
			//Data
			if(asData.Pos("@") > 0)			sgHistory->FontColors[nCol][nRow]	= clRed;
			else if(asData.Pos("$") > 0)	sgHistory->FontColors[nCol][nRow]	= clBlue;
			else if(asData.Pos("#") > 0)	sgHistory->FontColors[nCol][nRow]	= clGray;
			else
			{
				if(nRow == 4 && asData == "빈칸")
				{
					sgHistory->FontColors[nCol][nRow]	= clWhite;
					sgHistory->Colors[nCol][nRow] 		= (TColor)RGB( frmMain->m_nEmptyBgColor, frmMain->m_nEmptyBgColor, frmMain->m_nEmptyBgColor );
				}
				else
				{
					sgHistory->FontColors[nCol][nRow]	= clBlack;
				}
			}

			//---
			sgHistory->Cells[nCol][nRow] 	= asData;
		}
	}
	if(nSizeHistory > 0)
		sgHistory->Col	= sgHistory->ColCount - nSizeHistory - 1;
	else
		sgHistory->Col	= sgHistory->ColCount - 2;
	sgHistory->Row	= 0;


	//================================================
	//소유자정보//
	//================================================
	sgOwnInfo->FixedRows  	= 0;
	sgOwnInfo->FixedCols  	= 0;
	sgOwnInfo->RowCount 	= 4;
	nRow	= 0;
	sgOwnInfo->RowHeights[nRow++]	= 60;
	sgOwnInfo->RowHeights[nRow++]	= 65;
	sgOwnInfo->RowHeights[nRow++]	= 110;
	sgOwnInfo->RowHeights[nRow]		= 105;
	sgOwnInfo->DefaultColWidth		= nDefaultColWidthOwnInfo;
	sgOwnInfo->ColWidths[sgOwnInfo->ColCount - 1]	= 44;
	for(nRow = 0; nRow < 4; nRow++)
		sgOwnInfo->Colors[sgOwnInfo->ColCount - 1][nRow] 	= clBtnFace;
	nRow	= 0;
	sgOwnInfo->Cells[sgOwnInfo->ColCount - 1][nRow++] 	= "년월일";
	sgOwnInfo->Cells[sgOwnInfo->ColCount - 1][nRow++] 	= "사고";
	sgOwnInfo->Cells[sgOwnInfo->ColCount - 1][nRow++] 	= "주소";
	sgOwnInfo->Cells[sgOwnInfo->ColCount - 1][nRow] 	= "소유자";

	//=============================================================================
	for(int i = 0; i < eData->m_nOwnInfoCount; i++)
	{
		//=============================================================================
		nCol	= sgOwnInfo->ColCount - 2 - i;

		//=============================================================================
		for(nRow = 0; nRow < 4; nRow++)
		{
			//=============================================================================
			if(nRow == 0)			asData  = (char*)eData->m_vOWNINFODATE[i].DATA;
			else if(nRow == 1)		asData 	= (char*)eData->m_vOWNINFOREASON[i].DATA;
			else if(nRow == 2)		asData 	= (char*)eData->m_vOWNINFOADDRESS[i].DATA;
			else if(nRow == 3)		asData 	= (char*)eData->m_vOWNINFONAME[i].DATA;

			//=============================================================================
			//Data
			if(asData	== "-")
			{
				if(m_INI_EMPTY)
					asData	= "빈칸";
				else
					asData	= "";
			}
			//=============================================================================
			//Data
			if(asData.Pos("@") > 0)			sgOwnInfo->FontColors[nCol][nRow]	= clRed;
			else if(asData.Pos("$") > 0)	sgOwnInfo->FontColors[nCol][nRow]	= clBlue;
			else if(asData.Pos("#") > 0)    sgOwnInfo->FontColors[nCol][nRow]	= clGray;
			else
			{
				if(asData == "빈칸")
				{
					sgOwnInfo->FontColors[nCol][nRow]	= clWhite;
					sgOwnInfo->Colors[nCol][nRow] 		= (TColor)RGB( frmMain->m_nEmptyBgColor, frmMain->m_nEmptyBgColor, frmMain->m_nEmptyBgColor );
				}
				else
				{
					sgOwnInfo->FontColors[nCol][nRow]	= clBlack;
				}
			}

			//---
			sgOwnInfo->Cells[nCol][nRow] 	= asData;
		}
	}
	if(nSizeOwnInfo > 0)
		sgOwnInfo->Col	= sgOwnInfo->ColCount - nSizeOwnInfo - 1;
	else
		sgOwnInfo->Col	= sgOwnInfo->ColCount - 2;
	sgOwnInfo->Row	= 0;
}
//---------------------------------------------------------------------------

bool __fastcall TfrmResultList::funcCheckInputData()
{
	AnsiString  asStr   		= "";
	AnsiString  asJimok			= "";
	AnsiString  asArea			= "";
	AnsiString  asValue1		= "";
	AnsiString  asValue2		= "";
	AnsiString  asHistory		= "";
	AnsiString  asOwnDate		= "";
	AnsiString  asOwnReason		= "";
	AnsiString  asOwnAddress	= "";
	AnsiString  asOwnName		= "";
	int			nRow			= 0;

	m_nHistoryInputCount	= 0;
	m_nOwnInfoInputCount	= 0;

	//연혁 입력 개수 체크//
	for(int i = 0; i < sgHistory->ColCount - 1; i++)
	{
		nRow	= 0;
		asJimok		= sgHistory->Cells[i][nRow++];
		asArea		= sgHistory->Cells[i][nRow++];
		asValue1	= sgHistory->Cells[i][nRow++];
		asValue2	= sgHistory->Cells[i][nRow++];
		asHistory	= sgHistory->Cells[i][nRow];
		if(asHistory == "빈칸")//220104//
			asHistory	= "";

		if(asJimok.Trim().IsEmpty() && asArea.Trim().IsEmpty()
		&& asValue1.Trim().IsEmpty() && asValue2.Trim().IsEmpty() && asHistory.Trim().IsEmpty())
		{
			continue;
		}
		else//한 항목이라도 데이터가 있다면 거기부터 count//
		{
			m_nHistoryInputCount	= sgHistory->ColCount - 1 - i;

			if(eData->m_nDOCKIND == 1 && m_nHistoryInputCount == 1)//210713//"임야" for hardcoding
			{
				if(asJimok == "임야" && asArea.Trim().IsEmpty()
				&& asValue1.Trim().IsEmpty() && asValue2.Trim().IsEmpty() && asHistory.Trim().IsEmpty())
				{
					return false;
				}
            }
			break;
		}
	}
	//소유자정보 입력 개수 체크//
	for(int i = 0; i < sgOwnInfo->ColCount - 1; i++)
	{
		nRow	= 0;
		asOwnDate		= sgOwnInfo->Cells[i][nRow++];
		asOwnReason		= sgOwnInfo->Cells[i][nRow++];
		asOwnAddress	= sgOwnInfo->Cells[i][nRow++];
		asOwnName		= sgOwnInfo->Cells[i][nRow];
		//220104//
		if(asOwnDate == "빈칸")
			asOwnDate	= "";
		if(asOwnReason == "빈칸")
			asOwnReason	= "";
		if(asOwnAddress == "빈칸")
			asOwnAddress	= "";
		if(asOwnName == "빈칸")
			asOwnName	= "";
		//---
		if(asOwnDate.Trim().IsEmpty() && asOwnReason.Trim().IsEmpty()
		&& asOwnAddress.Trim().IsEmpty() && asOwnName.Trim().IsEmpty())
		{
			continue;
		}
		else//한 항목이라도 데이터가 있다면 거기부터 count//
		{
			m_nOwnInfoInputCount	= sgOwnInfo->ColCount - 1 - i;
			break;
		}
	}

	//소유자정보 년월일 오류체크//
	if( !frmMain->m_bAIOCR && eData == e08DataAlpha)//260615//m_bAIOCR 조건 추가//
	{
		for(int i = sgOwnInfo->ColCount - 1 - m_nOwnInfoInputCount; i < sgOwnInfo->ColCount - 1; i++)
		{
			asStr	= sgOwnInfo->Cells[i][0];
			asStr	= StringReplace(asStr, "ㅇ", "", TReplaceFlags() << rfReplaceAll);
			asStr	= StringReplace(asStr, "@", "", TReplaceFlags() << rfReplaceAll);//210614//
			asStr	= StringReplace(asStr, "$", "", TReplaceFlags() << rfReplaceAll);//210614//
			if( !asStr.IsEmpty() )//230622//
			{
				asStr = eFunc->funcChangeDateStrFormatDate(asStr);
				asStr	= StringReplace(asStr, "%", "", TReplaceFlags() << rfReplaceAll);//220826//년월일에 %(취소선 표시) 있는 경우에 날짜 체크 오류가 생겨 추가//

				if(asStr == "Error" || (asStr != "-" && !asStr.IsEmpty() && asStr.Length() != 8))
				{
					Application->MessageBoxA(L"소유자정보 <년월일>을 확인해주세요.", L"알림:", 0);
					sgOwnInfoClickCell(sgOwnInfo, 0, i);
					return false;
				}
			}
		}

		if( m_nHistoryInputCount > 0 || m_nOwnInfoInputCount > 0)
		{
			if(!chkJibunOK->Checked )
			{
				if (Application->MessageBox(L"지번이 일치하지 않습니다. 저장할까요?", L"확 인", MB_YESNO) == IDNO)
				{
					if(Showing)
						chkJibunOK->SetFocus();
					return false;
				}
			}
		}
	}

	return true;
}
//---------------------------------------------------------------------------

////DB와 입력테이블 개수가 같은 경우 - 입력데이터 모두 체크//
//bool __fastcall TfrmResultList::funcExistsToSave()
//{
//	AnsiString  asDBStr	= "";
//	AnsiString  asSGStr	= "";
//
//	if((int)eData->m_vOldLandDocInfo.size() > 0)
//	{
//		if(chkJibunOK->Checked != eData->m_vOldLandDocInfo[0].PNU_CHECK)
//		{
//			return false;
//		}
//		if( edtPnu->Text != (char*)eData->m_vOldLandDocInfo[0].PNU_NAME)
//		{
//			return false;
//		}
//		if( edtLevel->Text != (char*)eData->m_vOldLandDocInfo[0].LEVEL)
//		{
//			return false;
//		}
//		asDBStr	= (char*)eData->m_vOldLandDocInfo[0].MEMO;
//		if(edtDoho->Text.Length() > 0 )
//		{
//			asSGStr	=  edtMemo->Text + lblMemo1->Caption + edtDoho->Text + lblMemo2->Caption;
//			if(asDBStr != asSGStr)
//			{
//				return false;
//			}
//		}
//		else
//		{
//			asSGStr	=  edtMemo->Text;
//			if(asDBStr != asSGStr)
//			{
//				return false;
//			}
//		}
//	}
//
//	int nRow 	= 0;
//	int nCol	= 0;
//
//	for(int i = 0; i < (int)eData->m_ResultDoc08His.size(); i++)
//	{
//		//=============================================================================
//		nCol	= sgHistory->ColCount - 2 - i;
//
//		//=============================================================================
//		for(nRow = 0; nRow < 5; nRow++)
//		{
//			//=============================================================================
//			if(nRow == 0)			asDBStr = (char*)eData->m_ResultDoc08His[i].JIMOK;
//			else if(nRow == 1)		asDBStr = (char*)eData->m_ResultDoc08His[i].AREA;
//			else if(nRow == 2)		asDBStr = (char*)eData->m_ResultDoc08His[i].VALUE1;
//			else if(nRow == 3)		asDBStr = (char*)eData->m_ResultDoc08His[i].VALUE2;
//			else if(nRow == 4)		asDBStr = (char*)eData->m_ResultDoc08His[i].HISTORY;
//
//			//=============================================================================
//			asSGStr	= sgHistory->Cells[nCol][nRow];
//			if(asSGStr == "빈칸")	asSGStr	= "";//220104//
//			//=============================================================================
//			if(asSGStr.Pos("'") > 0)//220204//저장오류원인// ' 제거 후 sgHistory에 저장//
//			{
//				asSGStr = StringReplace(asSGStr, "'", "", TReplaceFlags() << rfReplaceAll);
//				sgHistory->Cells[nCol][nRow]	= asSGStr;
//			}
//			if(asDBStr != asSGStr)
//			{
//				return false;
//			}
//		}
//	}
//
//	nRow 	= 0;
//	nCol	= 0;
//
//	for(int i = 0; i < (int)eData->m_ResultDoc08OwnInfo.size(); i++)
//	{
//		//=============================================================================
//		nCol	= sgOwnInfo->ColCount - 2 - i;
//
//		//=============================================================================
//		for(nRow = 0; nRow < 4; nRow++)
//		{
//			//=============================================================================
//			if(nRow == 0)			asDBStr = (char*)eData->m_ResultDoc08OwnInfo[i].HIS_DATE;
//			else if(nRow == 1)		asDBStr = (char*)eData->m_ResultDoc08OwnInfo[i].REASON;
//			else if(nRow == 2)		asDBStr = (char*)eData->m_ResultDoc08OwnInfo[i].OWN_ADDRESS;
//			else if(nRow == 3)		asDBStr = (char*)eData->m_ResultDoc08OwnInfo[i].OWN_NAME;
//
//			//=============================================================================
//			asSGStr	= sgOwnInfo->Cells[nCol][nRow];
//			if(asSGStr == "빈칸")	asSGStr	= "";//220104//
//			//=============================================================================
//			if(asSGStr.Pos("'") > 0)//220204//저장오류원인// ' 제거 후 sgOwnInfo에 저장//
//			{
//				asSGStr = StringReplace(asSGStr, "'", "", TReplaceFlags() << rfReplaceAll);
//				sgOwnInfo->Cells[nCol][nRow]	= asSGStr;
//			}
//			if(asDBStr != asSGStr)
//			{
//				return false;
//			}
//		}
//	}
//
//	return true;
//}
////---------------------------------------------------------------------------

//241107//DB, 입력 불일치가 발생하면 바로 False Return => 모든 데이터 체크하도록 기능 변경
//#한글화편집#DirectTable//
//DB와 입력테이블 개수가 같은 경우 - 입력데이터 모두 체크//
bool __fastcall TfrmResultList::funcExistsToSave()
{
	AnsiString  asDBStr	= "";
	AnsiString  asSGStr	= "";
	bool		bReturn	= true;
	DOCUMENT08_HISTORY_STRUCT	tempHistory;//구대장 연혁(관리자편집_내역)//

	//#한글화편집#DirectTable//
	eData->m_ResultDoc08_History.clear();


	if((int)eData->m_vOldLandDocInfo.size() > 0)
	{
		if(chkJibunOK->Checked != eData->m_vOldLandDocInfo[0].PNU_CHECK)
		{
			bReturn	= false;
		}
		if( edtPnu->Text != (char*)eData->m_vOldLandDocInfo[0].PNU_NAME)
		{
			bReturn	= false;
		}
		if( edtLevel->Text != (char*)eData->m_vOldLandDocInfo[0].LEVEL)
		{
			bReturn	= false;
		}
		asDBStr	= (char*)eData->m_vOldLandDocInfo[0].MEMO;
		if(edtDoho->Text.Length() > 0 )
		{
			asSGStr	=  edtMemo->Text + lblMemo1->Caption + edtDoho->Text + lblMemo2->Caption;
			if(asDBStr != asSGStr)
			{
				bReturn	= false;
			}
		}
		else
		{
			asSGStr	=  edtMemo->Text;
			if(asDBStr != asSGStr)
			{
				bReturn	= false;
			}
		}
	}

	int nRow 	= 0;
	int nCol	= 0;

	memset(&tempHistory, 0x00, sizeof(DOCUMENT08_HISTORY_STRUCT));

	for(int i = 0; i < (int)eData->m_ResultDoc08His.size(); i++)
	{
		//=============================================================================
		nCol	= sgHistory->ColCount - 2 - i;

		//=============================================================================
		for(nRow = 0; nRow < 5; nRow++)
		{
			//=============================================================================
			if(nRow == 0)			asDBStr = (char*)eData->m_ResultDoc08His[i].JIMOK;
			else if(nRow == 1)		asDBStr = (char*)eData->m_ResultDoc08His[i].AREA;
			else if(nRow == 2)		asDBStr = (char*)eData->m_ResultDoc08His[i].VALUE1;
			else if(nRow == 3)		asDBStr = (char*)eData->m_ResultDoc08His[i].VALUE2;
			else if(nRow == 4)		asDBStr = (char*)eData->m_ResultDoc08His[i].HISTORY;

			//=============================================================================
			asSGStr	= sgHistory->Cells[nCol][nRow];
			if(asSGStr == "빈칸")	asSGStr	= "";//220104//
			//=============================================================================
			if(asSGStr.Pos("'") > 0)//220204//저장오류원인// ' 제거 후 sgHistory에 저장//
			{
				asSGStr = StringReplace(asSGStr, "'", "", TReplaceFlags() << rfReplaceAll);
				sgHistory->Cells[nCol][nRow]	= asSGStr;
			}
			if(asDBStr != asSGStr)
			{
				//=========================================================================
				//241030//#구대장한글편집#DirectTable//
				//=========================================================================
				tempHistory.CONTENTS_SEQ	= nRow + 1;//항목 순번[부책-연혁](1:지목,2:지적,3:과세1,4:과세2,5:연혁)//
				tempHistory.SEQ				= i + 1;//셀 순번//
				strcpy( tempHistory.BF_DATA, asDBStr.c_str() );
				strcpy( tempHistory.AF_DATA, asSGStr.c_str() );
				//
				eData->m_ResultDoc08_History.push_back(tempHistory);
				//
				memset(&tempHistory, 0x00, sizeof(DOCUMENT08_HISTORY_STRUCT));
				//=========================================================================

				bReturn	= false;
			}
		}
	}

	nRow 	= 0;
	nCol	= 0;

	memset(&tempHistory, 0x00, sizeof(DOCUMENT08_HISTORY_STRUCT));

	for(int i = 0; i < (int)eData->m_ResultDoc08OwnInfo.size(); i++)
	{
		//=============================================================================
		nCol	= sgOwnInfo->ColCount - 2 - i;

		//=============================================================================
		for(nRow = 0; nRow < 4; nRow++)
		{
			//=============================================================================
			if(nRow == 0)			asDBStr = (char*)eData->m_ResultDoc08OwnInfo[i].HIS_DATE;
			else if(nRow == 1)		asDBStr = (char*)eData->m_ResultDoc08OwnInfo[i].REASON;
			else if(nRow == 2)		asDBStr = (char*)eData->m_ResultDoc08OwnInfo[i].OWN_ADDRESS;
			else if(nRow == 3)		asDBStr = (char*)eData->m_ResultDoc08OwnInfo[i].OWN_NAME;

			//=============================================================================
			asSGStr	= sgOwnInfo->Cells[nCol][nRow];
			if(asSGStr == "빈칸")	asSGStr	= "";//220104//
			//=============================================================================
			if(asSGStr.Pos("'") > 0)//220204//저장오류원인// ' 제거 후 sgOwnInfo에 저장//
			{
				asSGStr = StringReplace(asSGStr, "'", "", TReplaceFlags() << rfReplaceAll);
				sgOwnInfo->Cells[nCol][nRow]	= asSGStr;
			}
			if(asDBStr != asSGStr)
			{
				//=========================================================================
				//241030//#구대장한글편집#DirectTable//
				//=========================================================================
				tempHistory.CONTENTS_SEQ	= 5/*연혁항목개수*/ + nRow + 1;//항목 순번[부책-연혁](1:지목,2:지적,3:과세1,4:과세2,5:연혁)//
				tempHistory.SEQ				= i + 1;//셀 순번//
				strcpy( tempHistory.BF_DATA, asDBStr.c_str() );
				strcpy( tempHistory.AF_DATA, asSGStr.c_str() );
				//
				eData->m_ResultDoc08_History.push_back(tempHistory);
				//
				memset(&tempHistory, 0x00, sizeof(DOCUMENT08_HISTORY_STRUCT));
				//=========================================================================

				bReturn	= false;
			}
		}
	}

	return bReturn;
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::btnSaveClick(TObject *Sender)
{
	if( m_bSaving )//210701//
		return;

	if(frmMain->palWait->Visible)
		return;

//220105//블럭된 글자 짤림 현상 해결//지목,지적,과세가격에 포커스있을 때 저장하면 자동'#'처리되어 주석처리//
//	//210629//
//	if(m_bHistoryEditing)
//	{
//		wchar_t pKey = VK_RETURN;
//		sgHistoryKeyPress(sgHistory, pKey);
//	}
//	else if(m_bOwnInfoEditing)
//	{
//		wchar_t pKey = VK_RETURN;
//		sgOwnInfoKeyPress(sgOwnInfo, pKey);
//	}

	if( !funcCheckInputData() )
		return;

	//210617//
	if((int)eData->m_vOldLandDocInfo.size() == 0
	&& (chkJibunOK->Checked || !edtPnu->Text.Trim().IsEmpty() || !edtLevel->Text.Trim().IsEmpty() || !edtLevel->Text.Trim().IsEmpty()))
	{
		m_bSaved	= false;
	}
	//DB와 입력테이블 개수가 다른 경우//
	else if( m_nHistoryInputCount != (int)eData->m_ResultDoc08His.size()
	 || m_nOwnInfoInputCount != (int)eData->m_ResultDoc08OwnInfo.size() )
	{
		m_bSaved	= false;
	}
	else//DB와 입력테이블 개수가 같은 경우 - 입력데이터 모두 체크//
	{
		m_bSaved	= funcExistsToSave();
	}

	String  sMsg;

	if(m_bSaved)//241018//저장할 필요 없음//
	{
		sMsg	= L"변경된 데이터가 없습니다.";
		Application->MessageBoxA(sMsg.c_str(), L"알림:", 0);
		return;
	}

	//저장할 데이터 없음//
	if(m_nHistoryInputCount == 0 && m_nOwnInfoInputCount == 0)
		return;

	//====================================================================
	//기구축번역본 or AIOCR번역본//
	//====================================================================
	int nFrom = 1;
	if(eData == e08DataAIOCR)
		nFrom = 2;
	//====================================================================

	//====================================================================
	int 	nType	= DF_NEW_RECORD;

//210617//
	sMsg	= L"지번 [" + frmMain->m_asLandNm + L"] 입력 정보를 <저장> 하시겠습니까?";

	if ( Application->MessageBox(sMsg.c_str(), L"확 인", MB_YESNO) == IDYES)
	{
		funcSaveDBData(true);

/*
		try{
			//=====================================================
			//241101//#구대장한글화편집//#DirectTable//
			//=====================================================
			frmSql->funcSQLUpdateOldLandDocPathlist();
			//frmMain->m_ResultDocument08Pnu 다시 가져오기//
			frmSql->funcReadDocument08Pnu(frmMain->m_ResultDocument08Pnu[0].PATH_NAME);
			funcDisplayDirectWriteInfo();
			//=========================================================================
			int nSEQNO	= frmSql->funcSQLWriteTbCopyDoc08(DF_NEW_RECORD, 3);
			frmSql->funcWriteDoc08_History(nSEQNO, 1, (nFrom == 2 ? true : false));
			//=====================================================



			//=====================================================
			// INFO 저장하기//
			//=====================================================
			if(frmSql->funcSQLReadCount("SELECT COUNT(*) FROM TB_OLDLANDDOC_INFO WHERE PATHLIST_SEQNO = " + IntToStr(frmMain->m_nPathListSeqNo)) == 0)//INFO테이블에 없다면//
				frmSql->funcSQLWriteOldLandDocInfo(DF_NEW_RECORD);
			else
				frmSql->funcSQLWriteOldLandDocInfo(DF_UPDATE_RECORD);
			//=====================================================

			//=====================================================
			// HISTORY 저장하기//
			//=====================================================
			//기존데이터 삭제//
			if(frmSql->funcSQLReadCount("SELECT COUNT(*) FROM TB_DOCUMENT08_HIS WHERE PATHLIST_SEQNO = " + IntToStr(frmMain->m_nPathListSeqNo)) > 0)//HISTORY테이블에 있다면//
				bReturn = frmSql->funcWriteHistory(nFrom, DF_DELETE_RECORD_ALL, 0);
			//=====================================================
			// HISTORY 삭제선 정보 저장하기//
			//=====================================================
			//기존데이터 삭제//
			if(frmSql->funcSQLReadCount("SELECT COUNT(*) FROM TB_DOCUMENT08_HIS_DEL WHERE PATHLIST_SEQNO = " + IntToStr(frmMain->m_nPathListSeqNo)) > 0)//HISTORY테이블에 있다면//
				bReturn = frmSql->funcWriteHistoryDel(DF_DELETE_RECORD_ALL, 0);

			for(int i = sgHistory->ColCount - 2; i >= 0; i--)
			{
				m_asQryToSave	= "";//210617//

				if(i > sgHistory->ColCount - 2 - m_nHistoryInputCount)
					nType	= DF_NEW_RECORD;
				else
					break;

				//=====================================================
				bReturn = frmSql->funcWriteHistory(nFrom, nType, i);
				//=====================================================
				bReturn = frmSql->funcWriteHistoryDel(DF_NEW_RECORD, i);
				//=====================================================
			}


			//=====================================================
			// OWNINFO 저장하기//
			//=====================================================
			//기존데이터 삭제//
			if(frmSql->funcSQLReadCount("SELECT COUNT(*) FROM TB_DOCUMENT08_OWNINFO WHERE PATHLIST_SEQNO = " + IntToStr(frmMain->m_nPathListSeqNo)) > 0)//OWNINFO테이블에 있다면//
				bReturn = frmSql->funcWriteOwnInfo(nFrom, DF_DELETE_RECORD_ALL, 0);

			for(int i = sgOwnInfo->ColCount - 2; i >= 0; i--)
			{
				m_asQryToSave	= "";//210617//

				if(i > sgOwnInfo->ColCount - 2 - m_nOwnInfoInputCount)
					nType	= DF_NEW_RECORD;
				else
					break;

				//=====================================================
				bReturn = frmSql->funcWriteOwnInfo(nFrom, nType, i);
				//=====================================================
			}

		}
		__finally{
			if(bReturn)
			{
				//241012/[한글화편집]기능에서는 불필요//frmSql->funcSQLWriteOldLandDocPathList(DF_UPDATE_RECORD);

				//=====================================================
				// HISTORY, OWNINFO 가져오기//
				eData->funcDeleteOwnInfo();//AlphaView 초기화//

				//공통정보//
				frmSql->funcSQLReadOldLandDocInfo();
				//부책//
				frmSql->funcReadDocument08His();
				frmSql->funcReadDocument08OwnInfo();

				//===========================================
				//AlphaView 구성//210712//
				//===========================================
				if( (int)eData->m_ResultDoc08His.size() > 0 || (int)eData->m_ResultDoc08OwnInfo.size() > 0)
				{
					eData->funcProcessOwnNames(false);
				}

				if((int)eData->m_vOldLandDocInfo.size() > 0)
				{
					frmAlphaDoc8->eData = eData;
					frmAlphaDoc8->funcRefreshShow();
					if( frmDoc8View->Showing )
					{
						frmDoc8View->funcRefreshShow();
					}
				}
				//===========================================

				frmMain->funcSetWaitWindows(false);

				//210622//순서변경//
				//=====================================================
				//=====================================================
				sMsg	= L"입력 정보를 <저장> 하였습니다.";
				Application->MessageBoxA(sMsg.c_str(), L"알림:", 0);

				m_bSaving	= false;//210701//
			}
			else
			{
            	frmMain->funcSetWaitWindows(false);
				m_bSaving	= false;//210701//
            }
		}
*/
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::sgHistoryClickCell(TObject *Sender, int ARow, int ACol)
{
	m_bHistoryEditing	= true;
	m_bOwnInfoEditing 	= false;

//	//201113//안수환J요청//관리자만 수정 권한//
//	AnsiString asDepart	= frmMain->USERINI->ReadString("USER_CONFIG", "ADMIN", "");
//	if(asDepart == "2")
	{
//		if(ARow == 0)
//		{
//			sgHistory->Options >> goEditing;
//			sgHistory->InsertCols(ACol-1, ARow);
//		}
//		else
		{
			if(ACol == sgHistory->ColCount - 1)
			{
				sgHistory->Options >> goEditing;
			}
			else
			{
				sgHistory->Options << goEditing;
				//220112
				AnsiString  asStr	= sgHistory->Cells[ACol][ARow];
				if(asStr == "빈칸")
				{
					asStr	= "";
					sgHistory->FontColors[ACol][ARow]	= clBlack;
					sgHistory->Colors[ACol][ARow] 		= clWhite;
					sgHistory->Cells[ACol][ARow]		= asStr;
				}
				keybd_event(VK_F2, 5,0,0);//220211//INSERT적용하면CLICKCELL했을때전체블럭처리되어F2로변경//
				edtHangeulEnter(sgHistory);
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::sgOwnInfoClickCell(TObject *Sender, int ARow, int ACol)
{
	m_bHistoryEditing	= false;
	m_bOwnInfoEditing	= true;

//	//201113//안수환J요청//관리자만 수정 권한//
//	AnsiString asDepart	= frmMain->USERINI->ReadString("USER_CONFIG", "ADMIN", "");
//	if(asDepart == "2")
	{
//		if(ARow == 0)
//		{
//			sgOwnInfo->Options >> goEditing;
////			sgOwnInfo->InsertCols(ACol-1, ARow);
////			sgOwnInfo->AddColumn();
//		}
//		else
		{
			if(ACol == sgOwnInfo->ColCount - 1)
			{
				sgOwnInfo->Options >> goEditing;
			}
			else
			{
				sgOwnInfo->Options << goEditing;
				//220112
				AnsiString  asStr	= sgOwnInfo->Cells[ACol][ARow];
				if(asStr == "빈칸")
				{
					sgOwnInfo->FontColors[ACol][ARow]	= clBlack;
					sgOwnInfo->Colors[ACol][ARow] 		= clWhite;
					sgOwnInfo->Cells[ACol][ARow]		= "";
				}
				keybd_event(VK_F2, 5,0,0);
 				edtHangeulEnter(sgOwnInfo);
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::sgHistoryKeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN)
	{
		if(sgHistory->Row < sgHistory->RowCount)
		{
			int nCol	= sgHistory->Col;
			int nRow	= sgHistory->Row;
			bool	bLast	= false;//210702

			if(nCol >= 0 && nCol < sgHistory->ColCount-1)
			{
				//210629//
				AnsiString  asStr	= "";
				if(sgHistory->Row == 0)//Jimok
				{
					if(nCol > 0)
					{
						sgHistory->Col--;
					}
					else
					{
						sgHistory->Row++;
						sgHistory->Col	= sgHistory->ColCount - 2;
					}
				}
				else if(sgHistory->Row == 1)//면적//
				{
					if(eData->m_nDOCKIND == 1)//임야대장//
					{
						asStr	= sgHistory->Cells[nCol][1];
						asStr	= StringReplace(asStr, "ㅇ", "", TReplaceFlags() << rfReplaceAll);
						asStr	= StringReplace(asStr, "@", "", TReplaceFlags() << rfReplaceAll);
						asStr	= StringReplace(asStr, "$", "", TReplaceFlags() << rfReplaceAll);
						asStr	= eFunc->funcChangeAreaFormatStr(3, asStr);
						if( asStr == "Error")
						{
							Application->MessageBoxA(L"연혁 <지적>을 확인해주세요.", L"알림:", 0);
							return;
						}
						else if( asStr == "format4")
						{
							Application->MessageBoxA(L"연혁 <지적>에 소수 이하 4자리를 입력해주세요.", L"알림:", 0);
							return;
						}

						if( asStr != "Error" && !asStr.IsEmpty() )
							sgHistory->Cells[nCol][1]	= asStr;
					}

					if(nCol > 0)
					{
						sgHistory->Col--;
					}
					else
					{
						sgHistory->Row++;
						sgHistory->Col	= sgHistory->ColCount - 2;
					}
				}
				else if(sgHistory->Row == 2)//Value1
				{
					//==============================================================================---
					//220104//#SHARP_CONCATE//
					if(nCol == sgHistory->ColCount - 2)//첫번째 데이터만 체크//
					{
						AnsiString  asTempUnit	= "";
						bool		bUnit		= false;

						asStr	= sgHistory->Cells[nCol][nRow];
						for(int u = 0; u < (int)frmMain->m_vVALUEUNIT.size(); u++)
						{
							asTempUnit	= (char*)frmMain->m_vVALUEUNIT[u].DATA;
							if(asStr.AnsiPos(asTempUnit) > 0)
							{
								bUnit	= true;
								break;
							}
						}
						if( !bUnit )
							sgHistory->Cells[nCol][nRow]	= asStr + "원";
					}
					//==============================================================================---
					sgHistory->Row++;
				}
				else if(sgHistory->Row == 3)//Value2
				{
					asStr	= sgHistory->Cells[nCol][3];
					if(nCol > 0)
					{
						sgHistory->Row--;
						sgHistory->Col--;
					}
					else
					{
						sgHistory->Row++;
						sgHistory->Col	= sgHistory->ColCount - 2;
					}
				}
				else if(sgHistory->Row == 4)//History
				{
					//==============================================================================---
					//220104//#SHARP_CONCATE//
					asStr	= sgHistory->Cells[nCol][nRow];
					if(asStr.IsEmpty() || asStr == "빈칸")
					{
						if( m_INI_EMPTY )
							sgHistory->Cells[nCol][nRow] 		= "빈칸";
						sgHistory->FontColors[nCol][nRow]	= clWhite;
						sgHistory->Colors[nCol][nRow] 		= (TColor)RGB( frmMain->m_nEmptyBgColor, frmMain->m_nEmptyBgColor, frmMain->m_nEmptyBgColor );
					}
					else
					{
						sgHistory->Colors[nCol][nRow] 		= clWhite;
					}
					//==============================================================================---
					if(nCol > 0)
					{
						sgHistory->Col--;
					}
					else
					{
						bLast	= true;
                    }
				}

				//===============================================
				//210701//
				asStr	= sgHistory->Cells[nCol][nRow];
				if(asStr.Pos("@") > 0)
					sgHistory->FontColors[nCol][nRow]	= clRed;
				else if(asStr.Pos("$") > 0)
					sgHistory->FontColors[nCol][nRow]	= clBlue;
				else if(asStr.Pos("#") > 0)
					sgHistory->FontColors[nCol][nRow]	= clGray;
//				else
//					sgHistory->FontColors[nCol][nRow]	= clBlack;
				//===============================================

				if(bLast)//LastHistory
					sgOwnInfo->SetFocus();
				else
					sgHistoryClickCell(sgHistory, sgHistory->Row, sgHistory->Col);
			}
		}
	}
	else if(Key == '\'' || Key == ',')//210705//
	{
		Key	= NULL;
	}
//	else if(Key == VK_DELETE)
//	{
//		sgHistory->Cells[sgHistory->Col][sgHistory->Row]	= "";
//	}
	else//220112//기 '빈칸'에 다른 데이터 입력하면 컬러변경//
	{
		if(sgHistory->Row < sgHistory->RowCount)
		{
			int nCol	= sgHistory->Col;
			int nRow	= sgHistory->Row;
			if(nCol >= 0 && nCol < sgHistory->ColCount-1)
			{
				AnsiString  asStr	= sgHistory->Cells[nCol][nRow];
				if(asStr == "빈칸")
				{
					sgHistory->FontColors[nCol][nRow]	= clBlack;
					sgHistory->Colors[nCol][nRow] 		= clWhite;
					sgHistory->Cells[nCol][nRow]		= "";
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::sgOwnInfoKeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN)
	{
		if(sgOwnInfo->Row < sgOwnInfo->RowCount)
		{
			int nCol	= sgOwnInfo->Col;
			int nRow	= sgOwnInfo->Row;
			bool	bLast	= false;//210702

			if(nCol >= 0 && nCol < sgOwnInfo->ColCount-1)
			{
				//210624//
				AnsiString  asStr	= "";

				if(sgOwnInfo->Row == 0)
				{
					asStr	= sgOwnInfo->Cells[nCol][0];
					asStr	= StringReplace(asStr, "ㅇ", "", TReplaceFlags() << rfReplaceAll);
					asStr	= StringReplace(asStr, "@", "", TReplaceFlags() << rfReplaceAll);
					asStr	= StringReplace(asStr, "$", "", TReplaceFlags() << rfReplaceAll);
					asStr	= eFunc->funcChangeDateNumberFormatDate(asStr);
					if( asStr == "Error")
					{
						Application->MessageBoxA(L"소유자 <년월일>을 확인해주세요.", L"알림:", 0);
						return;
					}
					if( asStr != "Error" && !asStr.IsEmpty() )
						sgOwnInfo->Cells[nCol][0]	= asStr;
				}

				//==============================================================================---
				//220104//#SHARP_CONCATE//
				asStr	= sgOwnInfo->Cells[nCol][nRow];
				if(asStr.IsEmpty() || asStr == "빈칸")
				{
					if( m_INI_EMPTY )
						sgOwnInfo->Cells[nCol][nRow] 		= "빈칸";
					sgOwnInfo->FontColors[nCol][nRow]	= clWhite;
					sgOwnInfo->Colors[nCol][nRow] 		= (TColor)RGB( frmMain->m_nEmptyBgColor, frmMain->m_nEmptyBgColor, frmMain->m_nEmptyBgColor );
				}
				else
				{
					sgOwnInfo->Colors[nCol][nRow] 		= clWhite;
				}
				//==============================================================================---

				if(nCol > 0)
				{
					sgOwnInfo->Col--;
				}
				else
				{
					if(sgOwnInfo->Row < sgOwnInfo->RowCount -1)
					{
						sgOwnInfo->Row++;
						sgOwnInfo->Col	= sgOwnInfo->ColCount - 2;
					}
					else
					{
						bLast	= true;
					}
				}

				//===============================================
				//210701//
				asStr	= sgOwnInfo->Cells[nCol][nRow];
				if(asStr.Pos("@") > 0)
					sgOwnInfo->FontColors[nCol][nRow]	= clRed;
				else if(asStr.Pos("$") > 0)
					sgOwnInfo->FontColors[nCol][nRow]	= clBlue;
				else if(asStr.Pos("#") > 0)
					sgOwnInfo->FontColors[nCol][nRow]	= clGray;
//				else
//					sgOwnInfo->FontColors[nCol][nRow]	= clBlack;
				//===============================================

				if(bLast)//LastOwnName
					btnSave->SetFocus();
				else
					sgOwnInfoClickCell(sgOwnInfo, sgOwnInfo->Row, sgOwnInfo->Col);
			}
		}
		else//last row -> focus btnSave
		{
			btnSave->SetFocus();
		}
	}
	else if(Key == '\'' || Key == ',')//210705//
	{
		Key	= NULL;
	}
//	else if(Key == VK_DELETE)
//	{
//		sgOwnInfo->Cells[sgOwnInfo->Col][sgOwnInfo->Row]	= "";
//	}
	else//220112//기 '빈칸'에 다른 데이터 입력하면 컬러변경//
	{
		if(sgOwnInfo->Row < sgOwnInfo->RowCount)
		{
			int nCol	= sgOwnInfo->Col;
			int nRow	= sgOwnInfo->Row;
			if(nCol >= 0 && nCol < sgOwnInfo->ColCount-1)
			{
				AnsiString  asStr	= sgOwnInfo->Cells[nCol][nRow];
				if(asStr == "빈칸")
				{
					sgOwnInfo->FontColors[nCol][nRow]	= clBlack;
					sgOwnInfo->Colors[nCol][nRow] 		= clWhite;
					sgOwnInfo->Cells[nCol][nRow]		= "";
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::edtKeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN)
	{
		if(Sender == chkJibunOK)
		{
			if(chkJibunOK->Checked)//220204//
			{
				if(edtLevel->Enabled)//241017//#[등급] 입력//
					edtLevel->SetFocus();
				else
					edtMemo->SetFocus();
			}
			else
			{
				edtPnu->SetFocus();
			}
		}
		else if(Sender == edtPnu)
		{
			if(edtLevel->Enabled)//241017//#[등급] 입력//
				edtLevel->SetFocus();
			else
				edtMemo->SetFocus();
		}
		else if(Sender == edtLevel)//241017//#[등급] 입력//
		{
			edtMemo->SetFocus();
		}
		else if(Sender == edtMemo)
		{
			edtDoho->SetFocus();
		}
		else if(Sender == edtDoho)
		{
			sgHistory->SetFocus();
			m_bHistoryEditing	= true;
			m_bOwnInfoEditing 	= false;
			keybd_event(VK_F2, 5,0,0);//210607//
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::lblJibunOKClick(TObject *Sender)
{
	chkJibunOK->Checked	= !chkJibunOK->Checked;
}
//---------------------------------------------------------------------------


void __fastcall TfrmResultList::ActionSaveExecute(TObject *Sender)
{
	btnSaveClick(NULL);//자동저장//ROW 살펴라////
}
//---------------------------------------------------------------------------



void __fastcall TfrmResultList::sgHistoryKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(IsCTRLpressed()
	&& (Key == VK_LEFT || Key == VK_RIGHT || Key == VK_UP || Key == VK_DOWN))
	{
		if(frmMain->IMGSCREEN2->Picture->Bitmap->Width == 0)
			return;

		funcMoveImage(Key);
		Key	= NULL;
		return;
	}

	AnsiString  asStr	= sgHistory->Cells[sgHistory->Col][sgHistory->Row];
	if(Key == VK_DOWN)
	{
		if(IsSHIFTpressed())
		{
			//210614//TEST//Key = NULL;
			return;
		}

		if(sgHistory->Row != 2)
		{
			if(sgHistory->Row < sgHistory->RowCount-1)
			{
				sgHistory->Col	= sgHistory->ColCount - 2;
			}
			else
			{
				sgOwnInfo->SetFocus();
				m_bHistoryEditing	= false;
				m_bOwnInfoEditing 	= true;
			}
		}

		//==============================================================================---
		//220104//#SHARP_CONCATE//
		asStr	= sgHistory->Cells[sgHistory->Col][sgHistory->Row];
		if(sgHistory->Row == 4)
		{
			if(asStr.IsEmpty())
			{
				if( m_INI_EMPTY )
					sgHistory->Cells[sgHistory->Col][sgHistory->Row] 		= "빈칸";
				sgHistory->FontColors[sgHistory->Col][sgHistory->Row]	= clWhite;
				sgHistory->Colors[sgHistory->Col][sgHistory->Row] 		= (TColor)RGB( frmMain->m_nEmptyBgColor, frmMain->m_nEmptyBgColor, frmMain->m_nEmptyBgColor );
			}
			else
			{
				sgHistory->Colors[sgHistory->Col][sgHistory->Row] 		= clWhite;
			}
		}
		//==============================================================================---

		if(asStr.IsEmpty())
			keybd_event(VK_INSERT, 5,0,0);//220209//블럭글자처리//
	}
	else if(Key == VK_UP)
	{
		if(IsSHIFTpressed())
		{
			//210614//TEST//Key = NULL;
			return;
		}

		if(sgHistory->Row == 0)
			return;

		if(asStr.IsEmpty())
			keybd_event(VK_INSERT, 5,0,0);//220209//블럭글자처리//
	}
	else if(Key == VK_RIGHT)
	{
		if(IsSHIFTpressed())
		{
			//210614//TEST//Key = NULL;
			return;
		}

		if(sgHistory->Col == sgHistory->ColCount - 2)
			return;

		if(asStr.IsEmpty())
		{
			sgHistory->Col++;
			keybd_event(VK_INSERT, 5,0,0);//220209//블럭글자처리//
		}
	}
	else if(Key == VK_LEFT)
	{
		if(IsSHIFTpressed())
		{
			//210614//TEST//Key = NULL;
			return;
		}

		if(sgHistory->Col == 0)
			return;

		if(asStr.IsEmpty())
		{
			sgHistory->Col--;
			keybd_event(VK_INSERT, 5,0,0);//220209//블럭글자처리//
		}
	}
	else if(Key == VK_TAB)//241008//
	{
		if(sgHistory->Col == sgHistory->ColCount-2)
		{
			sgHistory->Col	= -1;
			if(sgHistory->Row < sgHistory->RowCount-1)
				sgHistory->Row++;
			else
				sgHistory->Row	= 0;
		}
	}

	//===============================================
	//210701//
	asStr	= sgHistory->Cells[sgHistory->Col][sgHistory->Row];
	if(asStr.Pos("@") > 0)
		sgHistory->FontColors[sgHistory->Col][sgHistory->Row]	= clRed;
	else if(asStr.Pos("$") > 0)
		sgHistory->FontColors[sgHistory->Col][sgHistory->Row]	= clBlue;
	else if(asStr.Pos("#") > 0)
		sgHistory->FontColors[sgHistory->Col][sgHistory->Row]	= clGray;
//	else
//		sgHistory->FontColors[sgHistory->Col][sgHistory->Row]	= clBlack;
	//===============================================
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::sgOwnInfoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(IsCTRLpressed()
	&& (Key == VK_LEFT || Key == VK_RIGHT || Key == VK_UP || Key == VK_DOWN))
	{
		if(frmMain->IMGSCREEN2->Picture->Bitmap->Width == 0)
			return;

		funcMoveImage(Key);
		Key	= NULL;
		return;
	}

	AnsiString  asStr	= sgOwnInfo->Cells[sgOwnInfo->Col][sgOwnInfo->Row];
	if(Key == VK_DOWN)
	{
		if(IsSHIFTpressed())
		{
			//210614//TEST//Key = NULL;
			return;
		}

		if(sgOwnInfo->Row < sgOwnInfo->RowCount-1)
			sgOwnInfo->Col	= sgOwnInfo->ColCount - 2;
		else
			btnSaveClick(NULL);//자동저장//ROW 살펴라////

		if(asStr.IsEmpty())
			keybd_event(VK_INSERT, 5,0,0);//220209//블럭글자처리//
	}
	else if(Key == VK_UP)
	{
		if(IsSHIFTpressed())
		{
			//210614//TEST//Key = NULL;
			return;
		}

		if(sgOwnInfo->Row == 0)
			return;

		if(asStr.IsEmpty())
			keybd_event(VK_INSERT, 5,0,0);//220209//블럭글자처리//
	}
	else if(Key == VK_RIGHT)
	{
		if(IsSHIFTpressed())
		{
			//210614//TEST//Key = NULL;
			return;
		}

		if(sgOwnInfo->Col == sgOwnInfo->ColCount - 2)
			return;

		if(asStr.IsEmpty())
		{
			sgOwnInfo->Col++;
			keybd_event(VK_INSERT, 5,0,0);//220209//블럭글자처리//
		}
	}
	else if(Key == VK_LEFT)
	{
		if(IsSHIFTpressed())
		{
			//210614//TEST//Key = NULL;
			return;
		}

		if(sgOwnInfo->Col	== 0)
			return;

		if(asStr.IsEmpty())
		{
			sgOwnInfo->Col--;
			keybd_event(VK_INSERT, 5,0,0);//220209//블럭글자처리//
		}
	}
	else if(Key == VK_TAB)//241008//
	{
		if(sgOwnInfo->Col == sgOwnInfo->ColCount-2)
		{
			sgOwnInfo->Col	= -1;
			if(sgOwnInfo->Row < sgOwnInfo->RowCount-1)
				sgOwnInfo->Row++;
			else
				sgOwnInfo->Row	= 0;
		}
	}

	//===============================================
	//210701//
	asStr	= sgOwnInfo->Cells[sgOwnInfo->Col][sgOwnInfo->Row];
	if(asStr.Pos("@") > 0)
		sgOwnInfo->FontColors[sgOwnInfo->Col][sgOwnInfo->Row]	= clRed;
	else if(asStr.Pos("$") > 0)
		sgOwnInfo->FontColors[sgOwnInfo->Col][sgOwnInfo->Row]	= clBlue;
	else if(asStr.Pos("#") > 0)
		sgOwnInfo->FontColors[sgOwnInfo->Col][sgOwnInfo->Row]	= clGray;
//	else
//		sgOwnInfo->FontColors[sgOwnInfo->Col][sgOwnInfo->Row]	= clBlack;
	//===============================================
}
//---------------------------------------------------------------------------


void __fastcall TfrmResultList::cboEraKeyPress(TObject *Sender, wchar_t &Key)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::ActionShortExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::chkToModifyClick(TObject *Sender)
{
	//210617//
//	if(chkToModify->Checked)
//	{
//		pnlPnuInfo->Enabled	= true;
//		pnlHistory->Enabled	= true;
//		pnlOwnInfo->Enabled	= true;
//	}
//	else
//	{
//		pnlPnuInfo->Enabled	= false;
//		pnlHistory->Enabled	= false;
//		pnlOwnInfo->Enabled	= false;
//	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::sgHistoryExit(TObject *Sender)
{
	wchar_t pKey = VK_RETURN;
	sgHistoryKeyPress(sgHistory, pKey);

	m_bHistoryEditing	= false;
	m_bOwnInfoEditing	= false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::sgOwnInfoExit(TObject *Sender)
{
	wchar_t pKey = VK_RETURN;
	sgOwnInfoKeyPress(sgOwnInfo, pKey);

	m_bHistoryEditing	= false;
	m_bOwnInfoEditing	= false;
}
//---------------------------------------------------------------------------










void __fastcall TfrmResultList::funcMoveImage(WORD &Key)
{
	if(IsCTRLpressed())
	{
		if(Key == VK_LEFT)
		{
			frmMain->IMGSCREEN2->Tag = 2;
			int nX	= frmMain->pnlImgDocView->Width / 2;
			int nY	= frmMain->pnlImgDocView->Height / 2;
			frmMain->IMGSCREEN2MouseDown(frmMain->IMGSCREEN2, mbLeft, TShiftState() << ssLeft, nX, nY);
			frmMain->IMGSCREEN2MouseUp(frmMain->IMGSCREEN2, mbLeft, TShiftState() << ssLeft, nX-m_dImageMoveGap, nY);
		}
		else if(Key == VK_RIGHT)
		{
			frmMain->IMGSCREEN2->Tag = 2;
			int nX	= frmMain->pnlImgDocView->Width / 2;
			int nY	= frmMain->pnlImgDocView->Height / 2;
			frmMain->IMGSCREEN2MouseDown(frmMain->IMGSCREEN2, mbLeft, TShiftState() << ssLeft, nX, nY);
			frmMain->IMGSCREEN2MouseUp(frmMain->IMGSCREEN2, mbLeft, TShiftState() << ssLeft, nX+m_dImageMoveGap, nY);
		}
		else if(Key == VK_UP)
		{
			frmMain->IMGSCREEN2->Tag = 2;
			int nX	= frmMain->pnlImgDocView->Width / 2;
			int nY	= frmMain->pnlImgDocView->Height / 2;
			frmMain->IMGSCREEN2MouseDown(frmMain->IMGSCREEN2, mbLeft, TShiftState() << ssLeft, nX, nY);
			frmMain->IMGSCREEN2MouseUp(frmMain->IMGSCREEN2, mbLeft, TShiftState() << ssLeft, nX, nY-m_dImageMoveGap);
		}
		else if(Key == VK_DOWN)
		{
			frmMain->IMGSCREEN2->Tag = 2;
			int nX	= frmMain->pnlImgDocView->Width / 2;
			int nY	= frmMain->pnlImgDocView->Height / 2;
			frmMain->IMGSCREEN2MouseDown(frmMain->IMGSCREEN2, mbLeft, TShiftState() << ssLeft, nX, nY);
			frmMain->IMGSCREEN2MouseUp(frmMain->IMGSCREEN2, mbLeft, TShiftState() << ssLeft, nX, nY+m_dImageMoveGap);
		}

		frmMain->IMGSCREEN2->Tag	= 1;//210614//
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::edtKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(IsCTRLpressed()
	&& (Key == VK_LEFT || Key == VK_RIGHT || Key == VK_UP || Key == VK_DOWN))
	{
		if(frmMain->IMGSCREEN2->Picture->Bitmap->Width == 0)
			return;

		funcMoveImage(Key);
		Key	= NULL;
		return;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	if( frmMain->chkResultList->Checked )
	{
		if(this->Showing && !m_bSaved)
		{
			btnSaveClick(NULL);
		}
		m_bSaved	= false;
		frmMain->chkResultList->Checked	= false;
		frmMain->IMGDOC08EDIT->Picture->Bitmap->Assign(frmMain->BITMAP_BTN_DOC08[frmMain->Doc08Edit1]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::funcSaveQry(AnsiString  _asType)
{
	if(m_asQryToSave.IsEmpty())
		return;

	AnsiString  asNow	= Now().FormatString("YYYYMMDD_HHNNSS");
	AnsiString  asFileName = frmMain->DOWNLOADPATH + frmMain->m_asLandCd + "_" + _asType + "_" + asNow + ".txt";
	TStringList *qry = new TStringList();

	qry->Clear();
	qry->Text = "";
	qry->Add(m_asQryToSave);
	qry->SaveToFile(asFileName.c_str());
	if(qry != NULL)
	{
		delete qry;
		qry = NULL;
	}
}
//---------------------------------------------------------------------------



//Ctrl+K
//Ctrl+L

void __fastcall TfrmResultList::FormActivate(TObject *Sender)
{
	if( !frmAlphaDoc8->Showing )
		frmMain->chkOwnNames->Checked	= false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::chkAreaChangeClick(TObject *Sender)
{
	//221221//#DOC8_OVERLAP//
//	if( eData->Showing )
//	{
//		eData->funcRefreshShow();
//		//211201//[TODO]//eData->BringToFront();
//	}
	if( frmDoc8View->Showing )
	{
		frmDoc8View->funcRefreshShow();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::btnSaveMouseEnter(TObject *Sender)
{
	keybd_event(VK_INSERT, 5,0,0);//220119//#15//블럭된 글자 짤림 현상 해결//
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::sgHistoryMouseLeave(TObject *Sender)
{
	keybd_event(VK_INSERT, 5,0,0);//220209//블럭글자처리//
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::sgOwnInfoMouseLeave(TObject *Sender)
{
	keybd_event(VK_INSERT, 5,0,0);//220209//블럭글자처리//
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::pnlPnuInfoTMouseLeave(TObject *Sender)
{
	keybd_event(VK_INSERT, 5,0,0);//220209//블럭글자처리//
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList::btnHistoryClick(TObject *Sender)
{
	if(frmDoc8History->Showing)
	{
		frmDoc8History->funcRefreshShow();
	}
	else
	{
		frmDoc8History->Show();
	}
}
//---------------------------------------------------------------------------

//=========================================================================
//241111//#구대장한글편집#DirectTable//
//=========================================================================
void __fastcall TfrmResultList::funcDisplayDirectWriteInfo()
{
	if( !strcmp(frmMain->m_ResultDocument08Pnu[0].DIRECT_YN, "1") )
	{
		AnsiString  asDate	= (char*)frmMain->m_ResultDocument08Pnu[0].DIRECT_DT;
		AnsiString  asId	= (char*)frmMain->m_ResultDocument08Pnu[0].DIRECT_ID;
		lblWrite->Caption	= "(최종변경: " + frmMain->func_Decoder(asId) + ", " + eFunc->funcChangeDateFormatString(2, asDate.c_str()) + ")";
		lblWrite->Visible	= true;
		btnHistory->Visible	= true;
	}
	//=========================================================================
}
//---------------------------------------------------------------------------

//=========================================================================
//260611//AIOCR결과 DB저장(자동)//
//_bAlert (true: 버튼클릭 수동 저장, false: 자동 저장)
//=========================================================================
void __fastcall TfrmResultList::funcSaveDBData(bool _bAlert)
{
	int  nType		= DF_NEW_RECORD;
	bool bReturn 	= false;
	String  sMsg;
	AnsiString  asTable = "";

	try{
		//_bAlert (true: 버튼클릭 수동 저장, false: 자동 저장)
		if(_bAlert)
		{
			m_bSaving	= true;
			frmMain->lblWait2->Caption  = "저장중입니다.";
			frmMain->funcSetWaitWindows(true);
		}

		//=====================================================
		//241101//#구대장한글화편집//#DirectTable//
		//=====================================================
		frmSql->funcSQLUpdateOldLandDocPathlist();
		//frmMain->m_ResultDocument08Pnu 다시 가져오기//
		frmSql->funcReadDocument08Pnu(frmMain->m_ResultDocument08Pnu[0].PATH_NAME);
		funcDisplayDirectWriteInfo();
		//=========================================================================
		int nSEQNO	= frmSql->funcSQLWriteTbCopyDoc08(DF_NEW_RECORD, 3);
		frmSql->funcWriteDoc08_History(nSEQNO, 1, (eData == e08DataAlpha ? false : true));
		//=====================================================

		//=====================================================
		// INFO 저장하기//
		//=====================================================
		if(frmSql->funcSQLReadCount("SELECT COUNT(*) FROM TB_OLDLANDDOC_INFO WHERE PATHLIST_SEQNO = " + IntToStr(frmMain->m_nPathListSeqNo)) == 0)//INFO테이블에 없다면//
			frmSql->funcSQLWriteOldLandDocInfo(DF_NEW_RECORD);
		else
			frmSql->funcSQLWriteOldLandDocInfo(DF_UPDATE_RECORD);
		//=====================================================

		//=====================================================
		// HISTORY 저장하기//
		//=====================================================
		//기존데이터 삭제//
		asTable = (eData != e08DataAIOCR ? "TB_DOCUMENT08_HIS" : "TB_DOCUMENT08_AIOCR_HIS");

		if(frmSql->funcSQLReadCount("SELECT COUNT(*) FROM " + asTable + " WHERE PATHLIST_SEQNO = " + IntToStr(frmMain->m_nPathListSeqNo)) > 0)//HISTORY테이블에 있다면//
			bReturn = frmSql->funcWriteHistory(DF_DELETE_RECORD_ALL, 0);
		//=====================================================
		// HISTORY 삭제선 정보 저장하기//
		//=====================================================
		//기존데이터 삭제//
		if(eData == e08DataAlpha)
		{
			if(frmSql->funcSQLReadCount("SELECT COUNT(*) FROM TB_DOCUMENT08_HIS_DEL WHERE PATHLIST_SEQNO = " + IntToStr(frmMain->m_nPathListSeqNo)) > 0)//HISTORY테이블에 있다면//
				bReturn = frmSql->funcWriteHistoryDel(DF_DELETE_RECORD_ALL, 0);
		}

		for(int i = sgHistory->ColCount - 2; i >= 0; i--)
		{
			if(i > sgHistory->ColCount - 2 - m_nHistoryInputCount)
				nType	= DF_NEW_RECORD;
			else
				break;

			//=====================================================
			bReturn = frmSql->funcWriteHistory(nType, i);
			//=====================================================
			if( !frmMain->m_bAIOCR && eData == e08DataAlpha)//260615//m_bAIOCR 조건 추가//
				bReturn = frmSql->funcWriteHistoryDel(DF_NEW_RECORD, i);
			//=====================================================
		}


		//=====================================================
		// OWNINFO 저장하기//
		//=====================================================
		//기존데이터 삭제//
		asTable = (eData != e08DataAIOCR ? "TB_DOCUMENT08_OWNINFO" : "TB_DOCUMENT08_AIOCR_OWNINFO");

		if(frmSql->funcSQLReadCount("SELECT COUNT(*) FROM " + asTable + " WHERE PATHLIST_SEQNO = " + IntToStr(frmMain->m_nPathListSeqNo)) > 0)//OWNINFO테이블에 있다면//
			bReturn = frmSql->funcWriteOwnInfo(DF_DELETE_RECORD_ALL, 0);

		for(int i = sgOwnInfo->ColCount - 2; i >= 0; i--)
		{
			if(i > sgOwnInfo->ColCount - 2 - m_nOwnInfoInputCount)
				nType	= DF_NEW_RECORD;
			else
				break;

			//=====================================================
			bReturn = frmSql->funcWriteOwnInfo(nType, i);
			//=====================================================
		}

	}
	__finally{
		//_bAlert (true: 버튼클릭 수동 저장, false: 자동 저장)
		if(_bAlert)
		{
			if(bReturn)
			{
				//241012/[한글화편집]기능에서는 불필요//frmSql->funcSQLWriteOldLandDocPathList(DF_UPDATE_RECORD);

				//=====================================================
				// HISTORY, OWNINFO 가져오기//
				eData->funcDeleteOwnInfo();//AlphaView 초기화//

				//공통정보//
				frmSql->funcSQLReadOldLandDocInfo();
				//부책//
				frmSql->funcReadDocument08His();
				frmSql->funcReadDocument08OwnInfo();

				//===========================================
				//AlphaView 구성//210712//
				//===========================================
				if( (int)eData->m_ResultDoc08His.size() > 0 || (int)eData->m_ResultDoc08OwnInfo.size() > 0)
				{
					eData->funcProcessOwnNames(false);
				}

				//_bAlert (true: 버튼클릭 수동 저장, false: 자동 저장)
				if(_bAlert && (int)eData->m_vOldLandDocInfo.size() > 0)
				{
					frmAlphaDoc8->eData = eData;
					frmAlphaDoc8->funcRefreshShow();
					if( frmDoc8View->Showing )
					{
						frmDoc8View->funcRefreshShow();
					}
				}
			}

			frmMain->funcSetWaitWindows(false);
			m_bSaving	= false;
		}

		if(bReturn && _bAlert)
		{
			sMsg	= L"입력 정보를 <저장> 하였습니다.";
			Application->MessageBoxA(sMsg.c_str(), L"알림:", 0);
		}
	}
}
//---------------------------------------------------------------------------


