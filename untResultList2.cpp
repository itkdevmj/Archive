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

//keybd_event(가상키코드, 하드웨어스캔코드, 동작지정Flag, 추가정보//

TfrmResultList2 *frmResultList2;
//---------------------------------------------------------------------------
__fastcall TfrmResultList2::TfrmResultList2(TComponent* Owner)
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

void __fastcall TfrmResultList2::FormCreate(TObject *Sender)
{
	eData = new classDOC08Data();

	//v1.0.0.3//230804//공유지뒷면//
//기존 대부분의 서식은 왼쪽13칸, 오른쪽11칸이나,//
//오른쪽13칸문서도 간헐적으로 존재하여 입력창 구조를 변경하기로 함//
//왼쪽, 오른쪽 모두 13칸을 유지하고//
//오른쪽에 11칸서식인 경우 12, 13셀은 비우고 입력하기로 결정//
	m_nRightCount 	= 13;//오른쪽면 Cell 개수//
	m_nPageCount	= 26;//윗쪽, 아랫쪽 각각 Cell 개수//
//	m_nRightCount 	= 11/오른쪽면 Cell 개수//
//	m_nPageCount	= 24//윗쪽, 아랫쪽 각각 Cell 개수//
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList2::FormDestroy(TObject *Sender)
{
	delete eData;
	eData = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList2::FormShow(TObject *Sender)
{
	this->Left	= frmMain->Left - Shape1->Left;
	this->Top	= frmMain->Top + 8;

	sgShareOwn1->Left	= 0;
	sgShareOwn2->Left	= 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList2::FormClose(TObject *Sender, TCloseAction &Action)
{
	delete eData;

	//241018//frmResultList, frmResultList2 에서 처리하면 FormClose시 소멸되므로, 설정하는 Form에서 초기화 하는 것이 맞다.//
//	frmMain->m_asLandCd	= "";
//	frmMain->m_asLandNm	= "";
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList2::edtHangeulEnter(TObject *Sender)
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
void _fastcall TfrmResultList2::funcInitResultList()
{
	for(int i = 0; i < sgShareOwn1->RowCount; i++)
	{
		sgShareOwn1->Rows[i]->Clear();
	}

	for (int i = 0; i < sgShareOwn1->RowCount; i++) {
		for (int j = 0; j < sgShareOwn1->ColCount - 1; j++) {
			if(j % 2)
				sgShareOwn1->Colors[j][i] = COLOR_INPUT_BG;
			else
				sgShareOwn1->Colors[j][i] = clWhite;
		}
	}

	for(int i = 0; i < sgShareOwn2->RowCount; i++)
	{
		sgShareOwn2->Rows[i]->Clear();
	}

	for (int i = 0; i < sgShareOwn2->RowCount; i++) {
		for (int j = 0; j < sgShareOwn2->ColCount - 1; j++) {
			if( !(j % 2) )
				sgShareOwn2->Colors[j][i] = COLOR_INPUT_BG;
			else
				sgShareOwn2->Colors[j][i] = clWhite;
		}
	}

	pnlOwnInfoT1->Color		= COLOR_HEADER_BG;
	pnlOwnInfoNo1->Color	= COLOR_HEADER_BG;
	pnlOwnInfoT2->Color		= COLOR_HEADER_BG;
	pnlOwnInfoNo2->Color	= COLOR_HEADER_BG;

	pnlJibun->Caption	= "";
	lblWrite->Caption   = "";
	lblWrite->Visible	= false;
	btnHistory->Visible	= false;
	chkJibunOK->Checked	= false;
	edtPnu->Text	= "";
	edtLevel->Text	= "";
	edtMemo->Text	= "";
	edtDoho->Text	= "";
//=============================================================================
//v1.0.0.3//230804//공유지뒷면//
	chkFormat->Checked = false;
//=============================================================================


	if(frmAlphaDoc8->m_nDOCKIND == 0)
		lblMemo1->Caption	= "(지적도제";
	else if(frmAlphaDoc8->m_nDOCKIND == 1)
		lblMemo1->Caption	= "(임야도제";

	m_bSaved	= false;
}
//---------------------------------------------------------------------------

///구대장>소유자정보//
void _fastcall TfrmResultList2::funcDispResultList()
{
	AnsiString 	asData		= "";
	int 		nPos		= 0;
	int			nSizeShareOwn	= eData->m_nShareOwnCount;
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
		if(frmAlphaDoc8->m_nDOCKIND == 0)
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
		else if(frmAlphaDoc8->m_nDOCKIND == 1)
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

//230614//
	TAdvStringGrid 	*sgShareOwn = new TAdvStringGrid(this);

	for(int i = 0; i < 2; i++)
	{
		if(i == 0)
			sgShareOwn = sgShareOwn1;
		else
			sgShareOwn = sgShareOwn2;

		sgShareOwn->FixedRows  	= 0;
		sgShareOwn->FixedCols  	= 0;
		sgShareOwn->RowCount 	= 5;
		nRow	= 0;
		sgShareOwn->RowHeights[nRow++]	= 60;
		sgShareOwn->RowHeights[nRow++]	= 65;
		sgShareOwn->RowHeights[nRow++]	= 65;//v1.0.0.1//#SHAREOWN#//소유권보합//
		sgShareOwn->RowHeights[nRow++]	= 110;
		sgShareOwn->RowHeights[nRow]		= 105;
		sgShareOwn->DefaultColWidth		= nDefaultColWidthOwnInfo;
		sgShareOwn->ColWidths[sgShareOwn->ColCount - 1]	= 44;
		nRow	= 0;
		for(nRow = 0; nRow < 5; nRow++)
			sgShareOwn->Colors[sgShareOwn->ColCount - 1][nRow] 	= clBtnFace;
		nRow	= 0;
		sgShareOwn->Cells[sgShareOwn->ColCount - 1][nRow++] 	= "년월일";
		sgShareOwn->Cells[sgShareOwn->ColCount - 1][nRow++] 	= "사고";
		sgShareOwn->Cells[sgShareOwn->ColCount - 1][nRow++] 	= "소유권보합";//v1.0.0.1//#SHAREOWN#//소유권보합//
		sgShareOwn->Cells[sgShareOwn->ColCount - 1][nRow++] 	= "주소";
		sgShareOwn->Cells[sgShareOwn->ColCount - 1][nRow] 		= "소유자";
	}

	//================================================
	// DB 데이터//
	//================================================
	for(int i = 0; i < eData->m_nShareOwnCount; i++)
	{
		//=============================================================================
		//---Grid1, 2 와 컬럼 지정//
		//Grid1.Right//[Grid1.idx:13~23][db.seq:11~1]
		if( i < m_nRightCount )
		{
			sgShareOwn = sgShareOwn1;
			nCol = (m_nPageCount-1) - i/*Vector.Idx*/;
		}
		//Grid2.Right//[Grid2.idx:13~23][db.seq:22~12]
		else if( i >= m_nRightCount && i < m_nRightCount*2)
		{
			sgShareOwn = sgShareOwn2;
			nCol = (m_nPageCount-1) + m_nRightCount - i/*Vector.Idx*/;
		}
		//Grid1.Left//[Grid1.idx:0~12][db.seq:35~23]
		else if( i >= m_nRightCount*2 && i < m_nRightCount + m_nPageCount )
		{
			sgShareOwn = sgShareOwn1;
			nCol = (m_nPageCount-1) + m_nRightCount - i/*Vector.Idx*/;
		}
		//Grid2.Left//[Grid2.idx:0~12][db.seq:48~36]
		else
		{
			sgShareOwn = sgShareOwn2;
			nCol = (m_nPageCount-1) + m_nPageCount - i/*Vector.Idx*/;
		}

		//=============================================================================
		for(nRow = 0; nRow < 5; nRow++)
		{
			//=============================================================================
			if(nRow == 0)			asData  = (char*)eData->m_vSHAREOWNDATE[i].DATA;
			else if(nRow == 1)		asData 	= (char*)eData->m_vSHAREOWNREASON[i].DATA;
			else if(nRow == 2)		asData 	= (char*)eData->m_vSHAREOWNRATIO[i].DATA;
			else if(nRow == 3)		asData 	= (char*)eData->m_vSHAREOWNADDRESS[i].DATA;
			else if(nRow == 4)		asData 	= (char*)eData->m_vSHAREOWNNAME[i].DATA;

			//=============================================================================
			//Data
			if(asData	== "-")
			{
				if( m_INI_EMPTY )	asData	= "빈칸";
				else      			asData	= "";
			}
			//=============================================================================
			//Data
			if(asData.Pos("@") > 0)			sgShareOwn->FontColors[nCol][nRow]	= clRed;
			else if(asData.Pos("$") > 0)	sgShareOwn->FontColors[nCol][nRow]	= clBlue;
			else if(asData.Pos("#") > 0)    sgShareOwn->FontColors[nCol][nRow]	= clGray;
			else
			{
				if(asData == "빈칸")
				{
					sgShareOwn->FontColors[nCol][nRow]	= clWhite;
					sgShareOwn->Colors[nCol][nRow] 	= (TColor)RGB( frmMain->m_nEmptyBgColor, frmMain->m_nEmptyBgColor, frmMain->m_nEmptyBgColor );
				}
				else
				{
					sgShareOwn->FontColors[nCol][nRow]	= clBlack;
				}
			}

			//---
			sgShareOwn->Cells[nCol][nRow] 	= asData;
		}
	}

	sgShareOwn1->Col	= sgShareOwn1->ColCount - 2;
	sgShareOwn1->Row	= 0;

//=============================================================================
//230905//다른 필지를 열람하면 이전 Grid 포커스가 남아 있어서 TEST//
	sgShareOwn2->Col	= sgShareOwn2->ColCount - 2;
	sgShareOwn2->Row	= 0;
//241012//왜 Focus해야 하는지 확인 후 디버깅//
//	if(frmAlphaDoc8->m_nShareOwnCount)
//		sgShareOwn1->SetFocus();
//=============================================================================


//v1.0.0.1//230614//#CARE#//
//NULL 부터 설정해야 sgShareOwn2와의 연결이 잘 끊긴다.
//delete 부터 하면 sgShareOwn2이 먼저 NULL 이 된다.
	sgShareOwn = NULL;
	delete sgShareOwn;
}
//---------------------------------------------------------------------------

bool __fastcall TfrmResultList2::funcCheckInputData()
{
	AnsiString  asStr   		= "";
	AnsiString  asOwnDate		= "";
	AnsiString  asOwnReason		= "";
	AnsiString  asOwnRatio		= "";
	AnsiString  asOwnAddress	= "";
	AnsiString  asOwnName		= "";
	int			nRow			= 0;
	int 		nCol			= 0;

	//초기화//
	m_nShareOwnInputCount	= 0;

//=============================================================================
//v1.0.0.4//230905//상단, 하단 분리해서 마지막 데이터 찾으려니 힘들어서 아래의 내용으로 알고리즘 변경//
	int nGrid		= 1;
	for(int i = m_nPageCount * 2 - 1; i >= 0; i--)
	{
		nRow	= 0;
		if(	i >= (m_nPageCount * 2 - m_nRightCount) )//[AllData-Idx:51~39][Grid2.Idx:0~12]
		{
			nGrid	= 2;
			nCol	= (m_nPageCount * 2) - (i+1);
		}
		else if( i < (m_nPageCount) && i >= (m_nPageCount - m_nRightCount) )//[AllData-Idx:25-13][Grid2.Idx:13~25]
		{
			nGrid	= 2;
			nCol	= (m_nPageCount + m_nRightCount) - (i+1);
		}
		else if( i < (m_nPageCount + m_nRightCount) && i >= (m_nPageCount) )//[AllData-Idx:38~26][Grid1.Idx:0~12]
		{
			nGrid	= 1;
			nCol	= (m_nPageCount + m_nRightCount) - (i+1);
		}
		else//[AllData-Idx:12~0][Grid1.Idx:13~25]
		{
			nGrid	= 1;
			nCol	= (m_nPageCount) - (i+1);
		}

		if(nGrid == 2)
		{
			asOwnDate		= sgShareOwn2->Cells[nCol][nRow++];
			asOwnReason		= sgShareOwn2->Cells[nCol][nRow++];
			asOwnRatio		= sgShareOwn2->Cells[nCol][nRow++];
			asOwnAddress	= sgShareOwn2->Cells[nCol][nRow++];
			asOwnName		= sgShareOwn2->Cells[nCol][nRow];
		}
		else if(nGrid == 1)
		{
			asOwnDate		= sgShareOwn1->Cells[nCol][nRow++];
			asOwnReason		= sgShareOwn1->Cells[nCol][nRow++];
			asOwnRatio		= sgShareOwn1->Cells[nCol][nRow++];
			asOwnAddress	= sgShareOwn1->Cells[nCol][nRow++];
			asOwnName		= sgShareOwn1->Cells[nCol][nRow];
		}

		//---
		if(asOwnDate == "빈칸")		asOwnDate		= "";
		if(asOwnReason == "빈칸")	asOwnReason		= "";
		if(asOwnRatio == "빈칸")	asOwnRatio		= "";
		if(asOwnAddress == "빈칸")	asOwnAddress	= "";
		if(asOwnName == "빈칸")		asOwnName		= "";

		//---
		if(asOwnDate.Trim().IsEmpty() && asOwnReason.Trim().IsEmpty() && asOwnRatio.Trim().IsEmpty()
		&& asOwnAddress.Trim().IsEmpty() && asOwnName.Trim().IsEmpty())
		{
			continue;
		}
		else
		{
			m_nShareOwnInputCount	= (i + 1);
			break;
		}
	}

	//=========================================================================
	//대상 데이터를 기준으로 날짜 오류 검사//
	//=========================================================================
	//소유자정보 년월일 오류체크//
	if( !frmMain->m_bAIOCR && eData == e08DataAlpha)//260615//m_bAIOCR 조건 추가//
	{
		TAdvStringGrid *sgShareOwn = new TAdvStringGrid(this);
		for(int i = 0; i < m_nShareOwnInputCount; i++)
		{
			//---Grid1, 2 와 컬럼 지정//
			//Grid1.Right//[Grid1.idx:13~23][db.seq:11~1]
			if( i < m_nRightCount )
			{
				sgShareOwn = sgShareOwn1;
				nCol = (m_nPageCount) - (i+1)/*Vector.Idx*/;
			}
			//Grid2.Right//[Grid2.idx:13~23][db.seq:22~12]
			else if( i >= m_nRightCount && i < m_nRightCount*2)
			{
				sgShareOwn = sgShareOwn2;
				nCol = (m_nPageCount + m_nRightCount) - (i+1)/*Vector.Idx*/;
			}
			//Grid1.Left//[Grid1.idx:0~12][db.seq:35~23]
			else if( i >= m_nRightCount*2 && i < m_nRightCount + m_nPageCount )
			{
				sgShareOwn = sgShareOwn1;
				nCol = (m_nPageCount + m_nRightCount) - (i+1)/*Vector.Idx*/;
			}
			//Grid2.Left//[Grid2.idx:0~12][db.seq:48~36]
			else
			{
				sgShareOwn = sgShareOwn2;
				nCol = (m_nPageCount * 2) - (i+1)/*Vector.Idx*/;
			}

			//
			asStr	= sgShareOwn->Cells[nCol][0];
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
					//230724//공유지연명부 입력 화면에서 OutOfResources 에러 발생으로 분리시켜봄//
					if(sgShareOwn == sgShareOwn1)
						sgShareOwn1ClickCell(sgShareOwn1, 0, nCol);
					else if(sgShareOwn == sgShareOwn2)
						sgShareOwn2ClickCell(sgShareOwn2, 0, nCol);
					return false;
				}
			}
		}
		sgShareOwn = NULL;
		delete sgShareOwn;

		//=========================================================================
		//지번 일치 여부 검사//
		//=========================================================================
		if( m_nShareOwnInputCount > 0)
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
//bool __fastcall TfrmResultList2::funcExistsToSave()
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
//	TAdvStringGrid 	*sgShareOwn = new TAdvStringGrid(this);
//	int 			nRow 	= 0;
//	int 			nCol 	= 0;
//
//	for(int i = 0; i < (int)eData->m_ResultDoc08ShareOwn.size(); i++)
//	{
//		//---Grid1, 2 와 컬럼 지정//
//		//Grid1.Right//[Grid1.idx:13~23][db.seq:11~1]
//		if( i < frmResultList2->m_nRightCount )
//		{
//			sgShareOwn = frmResultList2->sgShareOwn1;
//			nCol = (frmResultList2->m_nPageCount-1) - i/*Vector.Idx*/;
//		}
//		//Grid2.Right//[Grid2.idx:13~23][db.seq:22~12]
//		else if( i >= frmResultList2->m_nRightCount && i < frmResultList2->m_nRightCount*2)
//		{
//			sgShareOwn = frmResultList2->sgShareOwn2;
//			nCol = (frmResultList2->m_nPageCount-1) + frmResultList2->m_nRightCount - i/*Vector.Idx*/;
//		}
//		//Grid1.Left//[Grid1.idx:0~12][db.seq:35~23]
//		else if( i >= frmResultList2->m_nRightCount*2 && i < frmResultList2->m_nRightCount + frmResultList2->m_nPageCount )
//		{
//			sgShareOwn = frmResultList2->sgShareOwn1;
//			nCol = (frmResultList2->m_nPageCount-1) + frmResultList2->m_nRightCount - i/*Vector.Idx*/;
//		}
//		//Grid2.Left//[Grid2.idx:0~12][db.seq:48~36]
//		else
//		{
//			sgShareOwn = frmResultList2->sgShareOwn2;
//			nCol = (frmResultList2->m_nPageCount-1) + frmResultList2->m_nPageCount - i/*Vector.Idx*/;
//		}
//
//		//=============================================================================
//		for(nRow = 0; nRow < 5; nRow++)
//		{
//			//=============================================================================
//			if(nRow == 0)			asDBStr = (char*)eData->m_ResultDoc08ShareOwn[i].HIS_DATE;
//			else if(nRow == 1)		asDBStr = (char*)eData->m_ResultDoc08ShareOwn[i].REASON;
//			else if(nRow == 2)		asDBStr = (char*)eData->m_ResultDoc08ShareOwn[i].RATIO;
//			else if(nRow == 3)		asDBStr = (char*)eData->m_ResultDoc08ShareOwn[i].OWN_ADDRESS;
//			else if(nRow == 4)		asDBStr = (char*)eData->m_ResultDoc08ShareOwn[i].OWN_NAME;
//			//210705//연혁에서는 "서기"라는 문구를 삭제 후 표기하지 않고 입력 그대로 표기한다//asHistory	= StringReplace(asHistory, "서기", "", TReplaceFlags() << rfReplaceAll);
//
//			//=============================================================================
//			asSGStr	= sgShareOwn->Cells[nCol][nRow];
//			if(asSGStr == "빈칸")	asSGStr	= "";//220104//
//			//=============================================================================
//			if(asSGStr.Pos("'") > 0)//220204//저장오류원인// ' 제거 후 sgShareOwn에 저장//
//			{
//				asSGStr = StringReplace(asSGStr, "'", "", TReplaceFlags() << rfReplaceAll);
//				sgShareOwn->Cells[nCol][nRow]	= asSGStr;
//			}
//			if(asDBStr != asSGStr)
//			{
//				//=========================================================================
//				//241030//#구대장한글편집#DirectTable//
//				//=========================================================================
//				tempHistory.SEQ				= i+1;//셀 순번//
//				tempHistory.CONTENTS_SEQ	= nRow+1;//항목 순번[부책-연혁](1:지목,2:지적,3:과세1,4:과세2,5:연혁)//
//				strcpy( tempHistory.BEFORE_DATA, asDBStr.c_str() );
//				strcpy( tempHistory.AFTER_DATA, asDBStr.c_str() );
//				//
//				eData->m_ResultDoc08OwnInfoHistory.push_back(tempHistory);
//				//
//				memset(&tempHistory, 0x00, sizeof(DOCUMENT08_HISTORY_STRUCT));
//				//=========================================================================
//
//				sgShareOwn = NULL;
//				delete sgShareOwn;
//				return false;
//			}
//		}
//	}
//
//	sgShareOwn = NULL;
//	delete sgShareOwn;
//
//	return true;
//}
////---------------------------------------------------------------------------

//241107//DB, 입력 불일치가 발생하면 바로 False Return => 모든 데이터 체크하도록 기능 변경
//#한글화편집#DirectTable//
//DB와 입력테이블 개수가 같은 경우 - 입력데이터 모두 체크//
bool __fastcall TfrmResultList2::funcExistsToSave()
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

	TAdvStringGrid 	*sgShareOwn = new TAdvStringGrid(this);
	int 			nRow 	= 0;
	int 			nCol 	= 0;

	memset(&tempHistory, 0x00, sizeof(DOCUMENT08_HISTORY_STRUCT));

	for(int i = 0; i < (int)eData->m_ResultDoc08ShareOwn.size(); i++)
	{
		//---Grid1, 2 와 컬럼 지정//
		//Grid1.Right//[Grid1.idx:13~23][db.seq:11~1]
		if( i < frmResultList2->m_nRightCount )
		{
			sgShareOwn = frmResultList2->sgShareOwn1;
			nCol = (frmResultList2->m_nPageCount-1) - i/*Vector.Idx*/;
		}
		//Grid2.Right//[Grid2.idx:13~23][db.seq:22~12]
		else if( i >= frmResultList2->m_nRightCount && i < frmResultList2->m_nRightCount*2)
		{
			sgShareOwn = frmResultList2->sgShareOwn2;
			nCol = (frmResultList2->m_nPageCount-1) + frmResultList2->m_nRightCount - i/*Vector.Idx*/;
		}
		//Grid1.Left//[Grid1.idx:0~12][db.seq:35~23]
		else if( i >= frmResultList2->m_nRightCount*2 && i < frmResultList2->m_nRightCount + frmResultList2->m_nPageCount )
		{
			sgShareOwn = frmResultList2->sgShareOwn1;
			nCol = (frmResultList2->m_nPageCount-1) + frmResultList2->m_nRightCount - i/*Vector.Idx*/;
		}
		//Grid2.Left//[Grid2.idx:0~12][db.seq:48~36]
		else
		{
			sgShareOwn = frmResultList2->sgShareOwn2;
			nCol = (frmResultList2->m_nPageCount-1) + frmResultList2->m_nPageCount - i/*Vector.Idx*/;
		}

		//=============================================================================
		for(nRow = 0; nRow < 5; nRow++)
		{
			//=============================================================================
			if(nRow == 0)			asDBStr = (char*)eData->m_ResultDoc08ShareOwn[i].HIS_DATE;
			else if(nRow == 1)		asDBStr = (char*)eData->m_ResultDoc08ShareOwn[i].REASON;
			else if(nRow == 2)		asDBStr = (char*)eData->m_ResultDoc08ShareOwn[i].RATIO;
			else if(nRow == 3)		asDBStr = (char*)eData->m_ResultDoc08ShareOwn[i].OWN_ADDRESS;
			else if(nRow == 4)		asDBStr = (char*)eData->m_ResultDoc08ShareOwn[i].OWN_NAME;
			//210705//연혁에서는 "서기"라는 문구를 삭제 후 표기하지 않고 입력 그대로 표기한다//asHistory	= StringReplace(asHistory, "서기", "", TReplaceFlags() << rfReplaceAll);

			//=============================================================================
			asSGStr	= sgShareOwn->Cells[nCol][nRow];
			if(asSGStr == "빈칸")	asSGStr	= "";//220104//
			//=============================================================================
			if(asSGStr.Pos("'") > 0)//220204//저장오류원인// ' 제거 후 sgShareOwn에 저장//
			{
				asSGStr = StringReplace(asSGStr, "'", "", TReplaceFlags() << rfReplaceAll);
				sgShareOwn->Cells[nCol][nRow]	= asSGStr;
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
			}
		}

		//241114//한글화입력프로그램에서는 DB, 입력데이터 불일치가 발생하면 바로 종료하므로 if문 내에서 처리해도 되지만,//
		//LandArchive에서는 여기에서 처리해야 한다.//
		sgShareOwn = NULL;
		delete sgShareOwn;
		bReturn	= false;
	}

	sgShareOwn = NULL;
	delete sgShareOwn;

	return bReturn;
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList2::btnSaveClick(TObject *Sender)
{
	if( m_bSaving )//210701//
		return;

	if(frmMain->palWait->Visible)
		return;

	if( !funcCheckInputData() )
		return;

	//210617//
	if((int)eData->m_vOldLandDocInfo.size() == 0
	&& (chkJibunOK->Checked || !edtPnu->Text.Trim().IsEmpty() || !edtLevel->Text.Trim().IsEmpty() || !edtLevel->Text.Trim().IsEmpty()))
	{
		m_bSaved	= false;
	}
	//DB와 입력테이블 개수가 다른 경우//
	else if( m_nShareOwnInputCount != (int)eData->m_ResultDoc08ShareOwn.size() )
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
	if(m_nShareOwnInputCount == 0)
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
		funcSaveDBData(true);//260615//

/*
		m_bSaving	= true;//210701//

		frmMain->lblWait2->Caption  = "저장중입니다.";
		frmMain->funcSetWaitWindows(true);

		bool bReturn = false;

		try{
			//=====================================================
			//241101//#구대장한글화편집//#DirectTable//
			//=====================================================
			frmSql->funcSQLUpdateOldLandDocPathlist();
			//frmMain->m_ResultDocument08Pnu 다시 가져오기//
			frmSql->funcReadDocument08Pnu(frmMain->m_ResultDocument08Pnu[0].PATH_NAME);
			funcDisplayDirectWriteInfo();
			//=====================================================
			int nSEQNO	= frmSql->funcSQLWriteTbCopyDoc08(DF_NEW_RECORD, 3);
			frmSql->funcWriteDoc08_History(nSEQNO, 1, (nFrom == 2 ? true : false));
			//=====================================================


			//=====================================================
			// INFO 저장하기//
			//=====================================================
			if(frmSql->funcSQLReadCount("SELECT COUNT(*) FROM TB_OLDLANDDOC_INFO WHERE PATHLIST_SEQNO = " + IntToStr(frmMain->m_nPathListSeqNo)) == 0)//INFO테이블에 없다면//
				frmSql->funcSQLWriteOldLandDocInfo2(DF_NEW_RECORD);
			else
				frmSql->funcSQLWriteOldLandDocInfo2(DF_UPDATE_RECORD);
			//=====================================================

			//=====================================================
			// SHAREOWN 저장하기//
			//=====================================================
			//기존데이터 삭제//
			if(frmSql->funcSQLReadCount("SELECT COUNT(*) FROM TB_DOCUMENT08_SHAREOWN WHERE PATHLIST_SEQNO = " + IntToStr(frmMain->m_nPathListSeqNo)) > 0)//SHAREOWN테이블에 있다면//
			{
				bReturn = frmSql->funcWriteShareOwn(nFrom, DF_DELETE_RECORD_ALL, 0);
				Application->ProcessMessages();//v1.0.0.0//공유지48항목DELETE_ALL완료 전에 INSERT문을 수행하게 되어 본 함수 적용//
			}

			//=====================================================
			TAdvStringGrid 	*sgShareOwn = new TAdvStringGrid(this);
			//=====================================================
			//첫 번째 그리드//
			//=====================================================
			for(int i = 0; i < m_nShareOwnInputCount; i++) 
			{
				//=====================================================
				m_asQryToSave	= "";

				//=====================================================
				bReturn = frmSql->funcWriteShareOwn(nFrom, DF_NEW_RECORD, i);
				//=====================================================
			}

			sgShareOwn = NULL;
			delete sgShareOwn;
			
		}
		__finally{
			if(bReturn)
			{
				//241012/[한글화편집]기능에서는 불필요//frmSql->funcSQLWriteOldLandDocPathList(DF_UPDATE_RECORD);

				//=====================================================
				// OWNINFO 가져오기//
				eData->funcDeleteOwnInfo();//AlphaView 초기화//

				//공통정보//
				frmSql->funcSQLReadOldLandDocInfo();
				//공유지연명부//
				frmSql->funcReadDocument08ShareOwn();

				//===========================================
				//AlphaView 구성//210712//
				//===========================================
				if( (int)eData->m_ResultDoc08ShareOwn.size() > 0)//231118//#SHAREOWN#
				{
					if(nFrom == 1)//기구축 번역본//
						eData->funcProcessOwnNames(false);
					else//AIOCR 번역본//
						eData->funcProcessOwnNames(true);
				}

				if((int)eData->m_vOldLandDocInfo.size() > 0)
				{
					//221221//#DOC8_OVERLAP//
					if( eData == e08DataAlpha && frmAlphaDoc8->Showing )
					{
						frmAlphaDoc8->eData = eData;
						frmAlphaDoc8->funcRefreshShow();
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

void __fastcall TfrmResultList2::sgShareOwn1ClickCell(TObject *Sender, int ARow, int ACol)
{
	m_bShareOwnEditing1	= true;
	m_bShareOwnEditing2 = false;

	if(ACol == sgShareOwn1->ColCount - 1)
	{
		sgShareOwn1->Options >> goEditing;
	}
	else
	{
		sgShareOwn1->Options << goEditing;
		//220112
		AnsiString  asStr	= sgShareOwn1->Cells[ACol][ARow];
		if(asStr == "빈칸")
		{
			sgShareOwn1->FontColors[ACol][ARow]	= clBlack;
			sgShareOwn1->Colors[ACol][ARow] 	= clWhite;
			sgShareOwn1->Cells[ACol][ARow]		= "";
		}
		//---
		if( !IsCTRLpressed() )//220203//Ctrl + MouseClick하면 '명치'입력되는 문제해결//
			keybd_event(VK_F2, 5,0,0);//220211//INSERT적용하면CLICKCELL했을때전체블럭처리되어F2로변경//
		edtHangeulEnter(sgShareOwn1);
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmResultList2::sgShareOwn1KeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN)
	{
		if(sgShareOwn1->Row < sgShareOwn1->RowCount)
		{
			int nCol	= sgShareOwn1->Col;
			int nRow	= sgShareOwn1->Row;
			bool	bLast	= false;//210702

			if(nCol >= 0 && nCol < sgShareOwn1->ColCount-1)
			{
				//210624//
				AnsiString  asStr	= "";

				if(sgShareOwn1->Row == 0)
				{
					//=====================================================
					//210708//copy right cell data
					AnsiString  asCopyMsg	= sgShareOwn1->Cells[nCol][nRow];
					AnsiString  asOldMsg	= "";
					//=====================================================

					asStr	= sgShareOwn1->Cells[nCol][0];
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
						sgShareOwn1->Cells[nCol][0]	= asStr;
					//==========================================================================================
					//220119//#3//
					asStr	= sgShareOwn1->Cells[nCol][nRow];
					//==========================================================================================
				}

				//==============================================================================---
				//220104//#SHARP_CONCATE//
				asStr	= sgShareOwn1->Cells[nCol][nRow];
				if(asStr.IsEmpty() || asStr == "빈칸")
				{
					if( m_INI_EMPTY )
						sgShareOwn1->Cells[nCol][nRow] 		= "빈칸";
					sgShareOwn1->FontColors[nCol][nRow]	= clWhite;
					sgShareOwn1->Colors[nCol][nRow] 	= (TColor)RGB( frmMain->m_nEmptyBgColor, frmMain->m_nEmptyBgColor, frmMain->m_nEmptyBgColor );
				}
				else
				{
					sgShareOwn1->Colors[nCol][nRow] 	= clWhite;
				}
				//==============================================================================---

				//===============================================
				//210701//
				asStr	= sgShareOwn1->Cells[nCol][nRow];
				if(asStr.Pos("@") > 0)
					sgShareOwn1->FontColors[nCol][nRow]	= clRed;
				else if(asStr.Pos("$") > 0)
					sgShareOwn1->FontColors[nCol][nRow]	= clBlue;
				else if(asStr.Pos("#") > 0)
					sgShareOwn1->FontColors[nCol][nRow]	= clGray;
//				else
//					sgShareOwn1->FontColors[nCol][nRow]	= clBlack;
				//===============================================


				if(nCol == m_nPageCount - m_nRightCount)
				{
					if(sgShareOwn1->Row < sgShareOwn1->RowCount - 1)
					{
						sgShareOwn1->SetFocus();
						sgShareOwn1->Col = sgShareOwn1->ColCount - 2;
						sgShareOwn1->Row = nRow;
					}
					//v1.0.0.1//230803//Grid1 소유자 오른쪽 마지막 칸이면 Grid2 소유자 오른쪽 첫 번째로 이동//
					else
					{
						sgShareOwn2->SetFocus();
						sgShareOwn2->Col = sgShareOwn2->ColCount - 2;
						sgShareOwn2->Row = nRow;
                    }
				}
				else if(nCol == 0)
				{
					if(sgShareOwn1->Row < sgShareOwn1->RowCount - 1)
					{
						sgShareOwn1->SetFocus();
						sgShareOwn1->Col = sgShareOwn1->ColCount - 2;
						sgShareOwn1->Row = nRow + 1;
					}
					//v1.0.0.1//230803//Grid1 소유자 오른쪽 마지막 칸이면 Grid2 소유자 오른쪽 첫 번째로 이동//
					else
					{
						sgShareOwn2->SetFocus();
						sgShareOwn2->Col = sgShareOwn2->ColCount - (m_nPageCount - m_nRightCount);
						sgShareOwn2->Row = nRow;
                    }
//					else
//					{
//						bLast	= true;
//					}
				}
				else// if(nCol < m_nPageCount - m_nRightCount)
				{
					sgShareOwn1->Col--;
				}

				if(bLast)//LastOwnName
				{
					btnSave->SetFocus();
				}
				else
				{
					//230724//공유지연명부 입력 화면에서 OutOfResources 에러 발생으로 분리시켜봄//
					sgShareOwn1ClickCell(sgShareOwn1, sgShareOwn1->Row, sgShareOwn1->Col);
				}
			}
		}
		else//last row -> focus btnSave
		{
			btnSave->SetFocus();
		}
	}
	else if(Key == '\'' || Key == ',')//220124//요청에의해 괄호는 입력되도록// || Key == '(' || Key == ')')//220118//#1특정기호입력방지//210705//
	{
		Key	= NULL;
	}
	else if(Key == '#')//220120//#삭제기능변경//지목, 지적, 과세1에서만//
	{
		Key	= NULL;
	}
	else if(Key == '/')//220105//
	{
		Key	= '_';
	}
	else//220112//기 '빈칸'에 다른 데이터 입력하면 컬러변경//
	{
		if(sgShareOwn1->Row < sgShareOwn1->RowCount)
		{
			int nCol	= sgShareOwn1->Col;
			int nRow	= sgShareOwn1->Row;
			if(nCol >= 0 && nCol < sgShareOwn1->ColCount-1)
			{
				AnsiString  asStr	= sgShareOwn1->Cells[nCol][nRow];
				if(asStr == "빈칸")
				{
					sgShareOwn1->FontColors[nCol][nRow]	= clBlack;
					sgShareOwn1->Colors[nCol][nRow] 	= clWhite;
					sgShareOwn1->Cells[nCol][nRow]		= "";
				}
			}
		}
	}
//	else if(Key == VK_DELETE)
//	{
//		sgShareOwn1->Cells[sgShareOwn1->Col][sgShareOwn1->Row]	= "";
//	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList2::edtKeyPress(TObject *Sender, wchar_t &Key)
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
			sgShareOwn1->Col	= sgShareOwn1->ColCount-2;
			sgShareOwn1->Row	= 4;
			sgShareOwn1->SetFocus();
			m_bShareOwnEditing1 = true;
			m_bShareOwnEditing2 = false;
			keybd_event(VK_INSERT, 5,0,0);//220209//블럭글자처리//
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList2::lblJibunOKClick(TObject *Sender)
{
	chkJibunOK->Checked	= !chkJibunOK->Checked;
}
//---------------------------------------------------------------------------


void __fastcall TfrmResultList2::ActionSaveExecute(TObject *Sender)
{
	btnSaveClick(NULL);//자동저장//ROW 살펴라////
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList2::sgShareOwn1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
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


	AnsiString  asStr	= sgShareOwn1->Cells[sgShareOwn1->Col][sgShareOwn1->Row];
	if(Key == VK_DOWN)
	{
		if(IsSHIFTpressed())
		{
			//210614//TEST//Key = NULL;
			return;
		}

		if(sgShareOwn1->Row < sgShareOwn1->RowCount-1)
		{
			sgShareOwn1->Col	= sgShareOwn1->ColCount - 2;
		}
		else
		{
			if(sgShareOwn1 == sgShareOwn1)
			{
				sgShareOwn1->Col = sgShareOwn1->ColCount - 2;
				sgShareOwn1->Row = 0;
				sgShareOwn1->SetFocus();
			}
			else
			{
				btnSaveClick(NULL);//자동저장//ROW 살펴라////
			}
		}

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

		if(sgShareOwn1->Row == 0)
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

		if(sgShareOwn1->Col == sgShareOwn1->ColCount - 2)
			return;

		if(asStr.IsEmpty())
		{
			sgShareOwn1->Col++;
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

		if(sgShareOwn1->Col	== 0)
			return;

		if(asStr.IsEmpty())
		{
			sgShareOwn1->Col--;
			keybd_event(VK_INSERT, 5,0,0);//220209//블럭글자처리//
		}
	}
	else if(Key == '/')//220105//
	{
		Key	= '_';
	}
	else if(Key == VK_TAB)//241008//
	{
		if(sgShareOwn1->Col == sgShareOwn1->ColCount-2)
		{
			sgShareOwn1->Col	= -1;
			if(sgShareOwn1->Row < sgShareOwn1->RowCount-1)
				sgShareOwn1->Row++;
			else
				sgShareOwn1->Row	= 0;
		}
	}

	//===============================================
	//210701//
	asStr	= sgShareOwn1->Cells[sgShareOwn1->Col][sgShareOwn1->Row];
	if(asStr.Pos("@") > 0)
		sgShareOwn1->FontColors[sgShareOwn1->Col][sgShareOwn1->Row]	= clRed;
	else if(asStr.Pos("$") > 0)
		sgShareOwn1->FontColors[sgShareOwn1->Col][sgShareOwn1->Row]	= clBlue;
	else if(asStr.Pos("#") > 0)
		sgShareOwn1->FontColors[sgShareOwn1->Col][sgShareOwn1->Row]	= clGray;
//	else
//		sgShareOwn1->FontColors[sgShareOwn1->Col][sgShareOwn1->Row]	= clBlack;
	//===============================================
}
//---------------------------------------------------------------------------


void __fastcall TfrmResultList2::cboEraKeyPress(TObject *Sender, wchar_t &Key)
{
//	if (Key > 47 && Key < 57)
//	{
//		sgShareOwn2->Cells[sgShareOwn2->Col][0]	= cboEra->Text;
//	}
//
//	cboEra->Visible = false;
}
//---------------------------------------------------------------------------


void __fastcall TfrmResultList2::sgShareOwnExit(TObject *Sender)
{
	if(Sender == sgShareOwn1)
	{
		m_bShareOwnEditing1	= false;
		m_bShareOwnEditing2 = false;
	}
	else if(Sender == sgShareOwn2)
	{
		m_bShareOwnEditing1	= false;
		m_bShareOwnEditing2	= false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList2::ActionEraExecute(TObject *Sender)
{
	AnsiString  asStr	= "";
	AnsiString  asEra1	= "단기";
	//220210//NotUsed//F2때문에 다수 오류 발생//AnsiString  asEra2	= "명치";
	AnsiString  asEra3	= "대정";
	AnsiString  asEra4	= "소화";
	AnsiString  asEra	= "";

	if(IsCTRLpressed())
	{
		if(Sender == ActionEra1)
			asEra	= asEra1;
//220210//NotUsed//F2때문에 다수 오류 발생//
//		else if(Sender == ActionEra2)
//			asEra	= asEra2;
		else if(Sender == ActionEra3)
			asEra	= asEra3;
		else if(Sender == ActionEra4)
			asEra	= asEra4;

		//230712//sgShareOwn1조건분리//
		if(m_bShareOwnEditing1 && sgShareOwn2->Col != sgShareOwn2->ColCount -1)
		{
			asStr	= sgShareOwn2->Cells[sgShareOwn2->Col][sgShareOwn2->Row];
			if(asStr == "-")	asStr	= "";
			sgShareOwn2->Cells[sgShareOwn2->Col][sgShareOwn2->Row]	= asStr + asEra;
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			//220210//연대 단축키 입력 후 F2(입력모드-커서표시) 동작안하는 이유가 Ctrl이 눌린 상태에서 동작했기 때문에
			//VK_CONTROL을 해제한다//
			keybd_event(VK_CONTROL, 0x9c,KEYEVENTF_KEYUP,0);
			keybd_event(VK_F2, 5,0,0);
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		}
		else if(m_bShareOwnEditing2 && sgShareOwn2->Col != sgShareOwn2->ColCount -1)
		{
			asStr	= sgShareOwn2->Cells[sgShareOwn2->Col][sgShareOwn2->Row];
			if(asStr == "-")	asStr	= "";
			sgShareOwn2->Cells[sgShareOwn2->Col][sgShareOwn2->Row]	= asStr + asEra;
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			//220210//연대 단축키 입력 후 F2(입력모드-커서표시) 동작안하는 이유가 Ctrl이 눌린 상태에서 동작했기 때문에
			//VK_CONTROL을 해제한다//
			keybd_event(VK_CONTROL, 0x9c,KEYEVENTF_KEYUP,0);
			keybd_event(VK_F2, 5,0,0);
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList2::ActionReasonExecute(TObject *Sender)
{
	if(sgShareOwn1->Row != 1 && sgShareOwn2->Row != 1)//230712//sgShareOwn1조건추가//사고단축키이므로 사고칸에서만 동작//
		return;

	AnsiString  asStr	= "";
	AnsiString  asReason1	= "사정";
	AnsiString  asReason2	= "소유권보존";
	AnsiString  asReason3	= "소유권이전";
	AnsiString  asReason4	= "씨설정";
	AnsiString  asReason5	= "주소변경";
	AnsiString  asReason6	= "성명복구";
	AnsiString  asReason7	= "주소개칭";
	AnsiString  asReason8	= "소유권이전(분배농지)";
	AnsiString  asReason	= "";

	if(Sender == ActionReason1)
		asReason	= asReason1;
	else if(Sender == ActionReason2)
		asReason	= asReason2;
	else if(Sender == ActionReason3)
		asReason	= asReason3;
	else if(Sender == ActionReason4)
		asReason	= asReason4;
	else if(Sender == ActionReason5)
		asReason	= asReason5;
	else if(Sender == ActionReason6)
		asReason	= asReason6;
	else if(Sender == ActionReason7)
		asReason	= asReason7;
	else if(Sender == ActionReason8)
		asReason	= asReason8;

	//230712//sgShareOwn1조건분리//
	if(m_bShareOwnEditing1 && sgShareOwn1->Col != sgShareOwn1->ColCount -1)
	{
		sgShareOwn1->Cells[sgShareOwn1->Col][sgShareOwn1->Row]	= asStr + asReason;
	}
	else if(m_bShareOwnEditing2 && sgShareOwn2->Col != sgShareOwn2->ColCount -1)
	{
		sgShareOwn2->Cells[sgShareOwn2->Col][sgShareOwn2->Row]	= asStr + asReason;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList2::funcMoveImage(WORD &Key)
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

void __fastcall TfrmResultList2::edtKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
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

void __fastcall TfrmResultList2::FormCloseQuery(TObject *Sender, bool &CanClose)
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

void __fastcall TfrmResultList2::funcSaveQry(AnsiString  _asType)
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

void __fastcall TfrmResultList2::ActionDateExecute(TObject *Sender)
{
//	if(frmMain->m_bMine)
//	{
//		AnsiString  asStr		= "";
//		AnsiString  asDate1		= "대정2년3월3일";
//		AnsiString  asDate2		= "대정2년9월20일";
//		AnsiString  asDate3		= "대정2년9월30일";
//		AnsiString  asDate4		= "대정3년6월13일";
//		AnsiString  asDate5		= "소화17년2월27일";
//		AnsiString  asDate6		= "소화18년1월22일";
//		AnsiString  asDate7		= "단기4282년8월10일";
//		AnsiString  asDate8		= "1973년11월30일";
//		AnsiString  asDate9		= "1974년11월22일";
//		AnsiString  asDate10	= "1975년9월1일";
//		AnsiString  asDate11	= "1977년3월22일";
//		AnsiString  asDate12	= "1977년4월8일";
//		AnsiString  asDate		= "";
//		AnsiString  asStrGrid	= "";
//
//		if(Sender == ActionDate1)
//		{
//			asStrGrid	= frmTranslate->sgShortcut->Cells[1][1];
//			if( !asStrGrid.IsEmpty() )
//				asDate	= asStrGrid;
//			else
//				asDate	= asDate1;
//		}
//		else if(Sender == ActionDate2)
//		{
//			asStrGrid	= frmTranslate->sgShortcut->Cells[1][2];
//			if( !asStrGrid.IsEmpty() )
//				asDate	= asStrGrid;
//			else
//				asDate	= asDate2;
//		}
//		else if(Sender == ActionDate3)
//		{
//			asStrGrid	= frmTranslate->sgShortcut->Cells[1][3];
//			if( !asStrGrid.IsEmpty() )
//				asDate	= asStrGrid;
//			else
//				asDate	= asDate3;
//		}
//		else if(Sender == ActionDate4)
//		{
//			asStrGrid	= frmTranslate->sgShortcut->Cells[1][4];
//			if( !asStrGrid.IsEmpty() )
//				asDate	= asStrGrid;
//			else
//				asDate	= asDate4;
//		}
//		else if(Sender == ActionDate5)
//		{
//			asStrGrid	= frmTranslate->sgShortcut->Cells[1][5];
//			if( !asStrGrid.IsEmpty() )
//				asDate	= asStrGrid;
//			else
//				asDate	= asDate5;
//		}
//		else if(Sender == ActionDate6)
//		{
//			asStrGrid	= frmTranslate->sgShortcut->Cells[1][6];
//			if( !asStrGrid.IsEmpty() )
//				asDate	= asStrGrid;
//			else
//				asDate	= asDate6;
//		}
//		else if(Sender == ActionDate7)
//		{
//			asStrGrid	= frmTranslate->sgShortcut->Cells[1][7];
//			if( !asStrGrid.IsEmpty() )
//				asDate	= asStrGrid;
//			else
//				asDate	= asDate7;
//		}
//		else if(Sender == ActionDate8)
//		{
//			asStrGrid	= frmTranslate->sgShortcut->Cells[1][8];
//			if( !asStrGrid.IsEmpty() )
//				asDate	= asStrGrid;
//			else
//				asDate	= asDate8;
//		}
//		else if(Sender == ActionDate9)
//		{
//			asStrGrid	= frmTranslate->sgShortcut->Cells[1][9];
//			if( !asStrGrid.IsEmpty() )
//				asDate	= asStrGrid;
//			else
//				asDate	= asDate9;
//		}
//		else if(Sender == ActionDate10)
//		{
//			asStrGrid	= frmTranslate->sgShortcut->Cells[1][10];
//			if( !asStrGrid.IsEmpty() )
//				asDate	= asStrGrid;
//			else
//				asDate	= asDate10;
//		}
//		else if(Sender == ActionDate11)
//		{
//			asStrGrid	= frmTranslate->sgShortcut->Cells[1][11];
//			if( !asStrGrid.IsEmpty() )
//				asDate	= asStrGrid;
//			else
//				asDate	= asDate11;
//		}
//		else if(Sender == ActionDate12)
//		{
//			asStrGrid	= frmTranslate->sgShortcut->Cells[1][12];
//			if( !asStrGrid.IsEmpty() )
//				asDate	= asStrGrid;
//			else
//				asDate	= asDate12;
//		}
//
//		//230712//sgShareOwn1조건분리//
//		if(m_bShareOwnEditing1 && sgShareOwn1->Row == 0 && sgShareOwn1->Col != sgShareOwn1->ColCount -1)
//		{
//			asStr	= sgShareOwn1->Cells[sgShareOwn1->Col][sgShareOwn1->Row];
//			sgShareOwn1->Cells[sgShareOwn1->Col][sgShareOwn1->Row]	= asStr + asDate;
//		}
//		else if(m_bShareOwnEditing2 && sgShareOwn2->Row == 0 && sgShareOwn2->Col != sgShareOwn2->ColCount -1)
//		{
//			asStr	= sgShareOwn2->Cells[sgShareOwn2->Col][sgShareOwn2->Row];
//			sgShareOwn2->Cells[sgShareOwn2->Col][sgShareOwn2->Row]	= asStr + asDate;
//		}
//	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmResultList2::ActionLoadShareOwnExecute(TObject *Sender)
{
//	if(frmMain->m_bMine)
//	{
//		if(frmMain->m_asLandCd.Length() != 19)
//			return;
//		if(frmMain->m_asOldLandCd.Length() != 19 )
//			return;
//
//		AnsiString asSrcFileName	= frmMain->TODAYPATH + frmMain->m_asOldLandCd + "_소유자정보.txt";
//		AnsiString asTgtFileName	= frmMain->TODAYPATH + frmMain->m_asLandCd + "_소유자정보.txt";
//
//		if( FileExists(asSrcFileName) )
//		{
//			CopyFile(asSrcFileName.c_str(), asTgtFileName.c_str(), false);
//			funcLoadShareOwnTextFile();
//		}
//	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList2::FormActivate(TObject *Sender)
{
//230908//TEST//확인 후 처리할 것!!!
//	if( !frmAlphaDoc8->Showing )
//		frmMain->chkOwnNames->Checked	= false;
}
//---------------------------------------------------------------------------

//void __fastcall TfrmResultList::funcCheckRegStr()
//{
//	String s = "123";
//	Regex number("[0-9]+");
//
//	if(std::regex_match(s, number))
//	{
//		ShowMessage("number");
//	}
//	else
//	{
//		ShowMessage("not number");
//	}
//
//	return 0;
//}
////---------------------------------------------------------------------------

void __fastcall TfrmResultList2::btnSave1MouseEnter(TObject *Sender)
{
	keybd_event(VK_INSERT, 5,0,0);//220119//#15//블럭된 글자 짤림 현상 해결//
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList2::sgShareOwnMouseLeave(TObject *Sender)
{
	if( !IsCTRLpressed() )//220204//AppDeactivate시 블럭글자 사라지는 문제 수정//220203//Ctrl + MouseClick하면 '명치'입력되는 문제해결//
		keybd_event(VK_INSERT, 5,0,0);//220209//블럭글자처리//
}
//---------------------------------------------------------------------------



void __fastcall TfrmResultList2::ActionEmptyExecute(TObject *Sender)
{
	if(IsCTRLpressed())//Ctrl + M이 시스템 기본 단축키로 개행
	{
//    	ShowMessage("OMG!!!");
		return;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList2::pnlPnuInfoTMouseLeave(TObject *Sender)
{
	if( !IsCTRLpressed() )//220204//AppDeactivate시 블럭글자 사라지는 문제 수정//220203//Ctrl + MouseClick하면 '명치'입력되는 문제해결//
		keybd_event(VK_INSERT, 5,0,0);//220209//블럭글자처리//
}
//---------------------------------------------------------------------------

//v1.0.0.1//#SHAREOWN#//
void __fastcall TfrmResultList2::funcCheckResultListClick()
{
//231004//#MOVED//공유지연명부는 입력자 구분이 없으므로 맨처음입력시와 변경시 포커스 다르게 설정한다//	chkJibunOK->SetFocus();

//=============================================================================
//v1.0.0.3//230804//공유지뒷면//
	chkFormat->Checked = false;
//=============================================================================

	chkJibunOK->Checked	= false;
	sgShareOwn1->Col	= sgShareOwn1->ColCount-2;
	sgShareOwn1->Row	= 1;

	//231004//공유지연명부는 입력자 구분이 없으므로 맨처음입력시와 변경시 포커스 다르게 설정한다//
	if(eData->m_nShareOwnCount == 0)//맨처음입력시//
		chkJibunOK->SetFocus();
	else
		sgShareOwn1->SetFocus();

	m_bShareOwnEditing1 	= true;
	m_bShareOwnEditing2 	= true;//230712//
	keybd_event(VK_INSERT, 5,0,0);//220209//블럭글자처리//
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList2::ActionShortExecute(TObject *Sender)
{
	AnsiString  asStr	= "";
	AnsiString  asShort8	= "%";
	AnsiString  asShort		= "";

	if(Sender == ActionShort8)
		asShort	= asShort8;

	//230712//sgShareOwn1조건분리//
	//220406//금란차장REQ//220216//F5~F12 단축키는 연혁에서만 적용//
	if(m_bShareOwnEditing1 && sgShareOwn1->Col != sgShareOwn1->ColCount -1)
	{
		asStr	= sgShareOwn1->Cells[sgShareOwn1->Col][sgShareOwn1->Row];
		if(Sender != ActionShort8)
			return;

		sgShareOwn1->Cells[sgShareOwn1->Col][sgShareOwn1->Row]	= asShort + asStr + asShort;
		keybd_event(VK_F2, 5,0,0);//220210//단축키는 블럭글자 없으므로 입력모드로 전환//
	}
	else if(m_bShareOwnEditing2 && sgShareOwn2->Col != sgShareOwn2->ColCount -1)
	{
		asStr	= sgShareOwn2->Cells[sgShareOwn2->Col][sgShareOwn2->Row];
		if(Sender != ActionShort8)
			return;

		sgShareOwn2->Cells[sgShareOwn2->Col][sgShareOwn2->Row]	= asShort + asStr + asShort;
		keybd_event(VK_F2, 5,0,0);//220210//단축키는 블럭글자 없으므로 입력모드로 전환//
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList2::sgShareOwn2ClickCell(TObject *Sender, int ARow, int ACol)
{
	m_bShareOwnEditing1	= false;
	m_bShareOwnEditing2	= true;

	if(ACol == sgShareOwn2->ColCount - 1)
	{
		sgShareOwn2->Options >> goEditing;
	}
	else
	{
		sgShareOwn2->Options << goEditing;
		//220112
		AnsiString  asStr	= sgShareOwn2->Cells[ACol][ARow];
		if(asStr == "빈칸")
		{
			sgShareOwn2->FontColors[ACol][ARow]	= clBlack;
			sgShareOwn2->Colors[ACol][ARow] 	= clWhite;
			sgShareOwn2->Cells[ACol][ARow]		= "";
		}
		//---
		if( !IsCTRLpressed() )//220203//Ctrl + MouseClick하면 '명치'입력되는 문제해결//
			keybd_event(VK_F2, 5,0,0);//220211//INSERT적용하면CLICKCELL했을때전체블럭처리되어F2로변경//
		edtHangeulEnter(sgShareOwn2);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList2::sgShareOwn2KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
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

	AnsiString  asStr	= sgShareOwn2->Cells[sgShareOwn2->Col][sgShareOwn2->Row];
	if(Key == VK_DOWN)
	{
		if(IsSHIFTpressed())
		{
			//210614//TEST//Key = NULL;
			return;
		}

		if(sgShareOwn2->Row < sgShareOwn2->RowCount-1)
		{
			sgShareOwn2->Col	= sgShareOwn2->ColCount - 2;
		}
		else
		{
			if(sgShareOwn2 == sgShareOwn2)
			{
				sgShareOwn2->Col = sgShareOwn2->ColCount - 2;
				sgShareOwn2->Row = 0;
				sgShareOwn2->SetFocus();
			}
			else
			{
				btnSaveClick(NULL);//자동저장//ROW 살펴라////
			}
		}

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

		if(sgShareOwn2->Row == 0)
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

		if(sgShareOwn2->Col == sgShareOwn2->ColCount - 2)
			return;

		if(asStr.IsEmpty())
		{
			sgShareOwn2->Col++;
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

		if(sgShareOwn2->Col	== 0)
			return;

		if(asStr.IsEmpty())
		{
			sgShareOwn2->Col--;
			keybd_event(VK_INSERT, 5,0,0);//220209//블럭글자처리//
		}
	}
	else if(Key == '/')//220105//
	{
		Key	= '_';
	}
	else if(Key == VK_TAB)//241008//
	{
		if(sgShareOwn2->Col == sgShareOwn2->ColCount-2)
		{
			sgShareOwn2->Col	= -1;
			if(sgShareOwn2->Row < sgShareOwn2->RowCount-1)
				sgShareOwn2->Row++;
			else
				sgShareOwn2->Row	= 0;
		}
	}

	//===============================================
	//210701//
	asStr	= sgShareOwn2->Cells[sgShareOwn2->Col][sgShareOwn2->Row];
	if(asStr.Pos("@") > 0)
		sgShareOwn2->FontColors[sgShareOwn2->Col][sgShareOwn2->Row]	= clRed;
	else if(asStr.Pos("$") > 0)
		sgShareOwn2->FontColors[sgShareOwn2->Col][sgShareOwn2->Row]	= clBlue;
	else if(asStr.Pos("#") > 0)
		sgShareOwn2->FontColors[sgShareOwn2->Col][sgShareOwn2->Row]	= clGray;
//	else
//		sgShareOwn2->FontColors[sgShareOwn2->Col][sgShareOwn2->Row]	= clBlack;
	//===============================================
}
//---------------------------------------------------------------------------


void __fastcall TfrmResultList2::sgShareOwn2KeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN)
	{
		if(sgShareOwn2->Row < sgShareOwn2->RowCount)
		{
			int nCol	= sgShareOwn2->Col;
			int nRow	= sgShareOwn2->Row;
			bool	bLast	= false;//210702

			if(nCol >= 0 && nCol < sgShareOwn2->ColCount-1)
			{
				//210624//
				AnsiString  asStr	= "";

				if(sgShareOwn2->Row == 0)
				{
					//=====================================================
					//210708//copy right cell data
					AnsiString  asCopyMsg	= sgShareOwn2->Cells[nCol][nRow];
					AnsiString  asOldMsg	= "";
//					if(frmMain->m_bMine)//[TODO]
//					{
//						if(nCol < sgShareOwn2->ColCount-2 && asCopyMsg == ".")
//						{
//							asOldMsg	= sgShareOwn2->Cells[nCol+1][nRow];
//							sgShareOwn2->Cells[nCol][nRow]	= asOldMsg;
//						}
//					}
					//=====================================================

					asStr	= sgShareOwn2->Cells[nCol][0];
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
						sgShareOwn2->Cells[nCol][0]	= asStr;
				}

				//==============================================================================---
				//220104//#SHARP_CONCATE//
				asStr	= sgShareOwn2->Cells[nCol][nRow];
				if(asStr.IsEmpty() || asStr == "빈칸")
				{
					if( m_INI_EMPTY )
						sgShareOwn2->Cells[nCol][nRow] 		= "빈칸";
					sgShareOwn2->FontColors[nCol][nRow]	= clWhite;
					sgShareOwn2->Colors[nCol][nRow] 		= (TColor)RGB( frmMain->m_nEmptyBgColor, frmMain->m_nEmptyBgColor, frmMain->m_nEmptyBgColor );
				}
				else
				{
					sgShareOwn2->Colors[nCol][nRow] 		= clWhite;
				}
				//==============================================================================---

				//===============================================
				//210701//
				asStr	= sgShareOwn2->Cells[nCol][nRow];
				if(asStr.Pos("@") > 0)
					sgShareOwn2->FontColors[nCol][nRow]	= clRed;
				else if(asStr.Pos("$") > 0)
					sgShareOwn2->FontColors[nCol][nRow]	= clBlue;
				else if(asStr.Pos("#") > 0)
					sgShareOwn2->FontColors[nCol][nRow]	= clGray;
//				else
//					sgShareOwn2->FontColors[nCol][nRow]	= clBlack;
				//===============================================


				if(nCol == m_nPageCount - m_nRightCount)
				{
					//v1.0.0.1//230803//Grid1 소유자 오른쪽 마지막 칸이면 Grid2 소유자 오른쪽 첫 번째로 이동//
					if(sgShareOwn2->Row < sgShareOwn2->RowCount - 1)
					{
						sgShareOwn2->SetFocus();
						sgShareOwn2->Col = sgShareOwn2->ColCount - 2;
						sgShareOwn2->Row = nRow;
					}
					else
					{
						sgShareOwn1->SetFocus();
						sgShareOwn1->Col = sgShareOwn1->ColCount - nCol;
						sgShareOwn1->Row = nRow;
                    }
				}
				else if(nCol == 0)
				{
					if(sgShareOwn2->Row < sgShareOwn2->RowCount - 1)
					{
						sgShareOwn2->SetFocus();
						sgShareOwn2->Col	= sgShareOwn2->ColCount - 2;
						sgShareOwn2->Row = nRow + 1;
					}
					else
					{
						bLast	= true;
					}
				}
				else// if(nCol < m_nPageCount - m_nRightCount)
				{
					sgShareOwn2->Col--;
				}

				if(bLast)//LastOwnName
				{
					btnSave->SetFocus();
				}
				else
				{
					//230724//공유지연명부 입력 화면에서 OutOfResources 에러 발생으로 분리시켜봄//
					sgShareOwn2ClickCell(sgShareOwn2, sgShareOwn2->Row, sgShareOwn2->Col);
				}
			}
		}
		else//last row -> focus btnSave
		{
			btnSave->SetFocus();
		}
	}
	else if(Key == '\'' || Key == ',')//220124//요청에의해 괄호는 입력되도록// || Key == '(' || Key == ')')//220118//#1특정기호입력방지//210705//
	{
		Key	= NULL;
	}
	else if(Key == '#')//220120//#삭제기능변경//지목, 지적, 과세1에서만//
	{
		Key	= NULL;
	}
	else if(Key == '/')//220105//
	{
		Key	= '_';
	}
	else//220112//기 '빈칸'에 다른 데이터 입력하면 컬러변경//
	{
		if(sgShareOwn2->Row < sgShareOwn2->RowCount)
		{
			int nCol	= sgShareOwn2->Col;
			int nRow	= sgShareOwn2->Row;
			if(nCol >= 0 && nCol < sgShareOwn2->ColCount-1)
			{
				AnsiString  asStr	= sgShareOwn2->Cells[nCol][nRow];
				if(asStr == "빈칸")
				{
					sgShareOwn2->FontColors[nCol][nRow]	= clBlack;
					sgShareOwn2->Colors[nCol][nRow] 	= clWhite;
					sgShareOwn2->Cells[nCol][nRow]		= "";
				}
			}
		}
	}
//	else if(Key == VK_DELETE)
//	{
//		sgShareOwn2->Cells[sgShareOwn2->Col][sgShareOwn2->Row]	= "";
//	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList2::chkFormatClick(TObject *Sender)
{
//Checked 설정할 때마다 표시되어 주석처리//
//	if(chkFormat->Checked)
//	{
//		Application->MessageBox(L"공유지연명부 뒷면을 선택했습니다.", L"알림", 0);
//	}
//	else
//	{
//		Application->MessageBox(L"공유지연명부 뒷면을 해제했습니다.", L"알림", 0);
//	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList2::lblFormatClick(TObject *Sender)
{
	chkFormat->Checked	= !chkFormat->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TfrmResultList2::btnHistoryClick(TObject *Sender)
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
void __fastcall TfrmResultList2::funcDisplayDirectWriteInfo()
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
void __fastcall TfrmResultList2::funcSaveDBData(bool _bAlert)
{
	int 	nType	= DF_NEW_RECORD;
	bool 	bReturn 	= false;
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
		//=====================================================
		int nSEQNO	= frmSql->funcSQLWriteTbCopyDoc08(DF_NEW_RECORD, 3);
		frmSql->funcWriteDoc08_History(nSEQNO, 1, (eData == e08DataAlpha ? false : true));
		//=====================================================

		//=====================================================
		// INFO 저장하기//
		//=====================================================
		if(frmSql->funcSQLReadCount("SELECT COUNT(*) FROM TB_OLDLANDDOC_INFO WHERE PATHLIST_SEQNO = " + IntToStr(frmMain->m_nPathListSeqNo)) == 0)//INFO테이블에 없다면//
			frmSql->funcSQLWriteOldLandDocInfo2(DF_NEW_RECORD);
		else
			frmSql->funcSQLWriteOldLandDocInfo2(DF_UPDATE_RECORD);
		//=====================================================

		//=====================================================
		// SHAREOWN 저장하기//
		//=====================================================
		//기존데이터 삭제//
		asTable = (eData != e08DataAIOCR ? "TB_DOCUMENT08_SHAREOWN" : "TB_DOCUMENT08_AIOCR_SHAREOWN");

		if(frmSql->funcSQLReadCount("SELECT COUNT(*) FROM TB_DOCUMENT08_SHAREOWN WHERE PATHLIST_SEQNO = " + IntToStr(frmMain->m_nPathListSeqNo)) > 0)//SHAREOWN테이블에 있다면//
		{
			bReturn = frmSql->funcWriteShareOwn(DF_DELETE_RECORD_ALL, 0);
			Application->ProcessMessages();//v1.0.0.0//공유지48항목DELETE_ALL완료 전에 INSERT문을 수행하게 되어 본 함수 적용//
		}

		for(int i = 0; i < m_nShareOwnInputCount; i++)
		{
			//=====================================================
			bReturn = frmSql->funcWriteShareOwn(DF_NEW_RECORD, i);
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
			    // OWNINFO 가져오기//
			    eData->funcDeleteOwnInfo();//AlphaView 초기화//

			    //공통정보//
			    frmSql->funcSQLReadOldLandDocInfo();
			    //공유지연명부//
			    frmSql->funcReadDocument08ShareOwn();

			    //===========================================
			    //AlphaView 구성//210712//
			    //===========================================
			    if( (int)eData->m_ResultDoc08ShareOwn.size() > 0)
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

