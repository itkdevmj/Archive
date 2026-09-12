#pragma link "IdBaseComponent"
#pragma link "IdCoder"
#pragma link "IdCoder3to4"
#pragma link "IdCoderMIME"
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"

#pragma warn -8004

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


//-----------------------------------------------
#define		DF_TB_USER1_COL_COUNT			11
//-----------------------------------------------

TfrmUserManagement *frmUserManagement;
//---------------------------------------------------------------------------
__fastcall TfrmUserManagement::TfrmUserManagement(TComponent* Owner)
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
		this->shpBG->Pen->Color	= (TColor)RGB(R, G, B);
		//shpWait->Pen->Color//
		//panWindowsMove->Color//
		this->panWindowsMove->Color	= (TColor)RGB(R, G, B);
		//pnlWaitT->Color//
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::FormShow(TObject *Sender)
{
	//##################################################
	//[TTA][DEFECT_REPORT][221111]
	if(frmSidoCode->Showing)
		frmSidoCode->Close();
	if(frmChangeMenu->Showing)
		frmChangeMenu->Close();
	//##################################################


	if(frmMain->INIINFO.SIDOCODE == "31110")//울산 중구청
	{
		TabSheet2->TabVisible = false;
	}
	else
	{
		TabSheet2->TabVisible = true;
	}

	funcLoadButtonImage();

	PageControl1->TabIndex = 0;
	mvUserInfoList.clear();
	funListClear();
	funcReadUserInformation();
	funcListDisplay();

	if (PageControl1->TabIndex == 0)
	{
		this->Width = 747;
	}
	else if (PageControl1->TabIndex == 1)
	{
		this->Width = 350;
	}
	shpBG->Width = this->Width;

	btnCloseTypeB->Left = this->Width - (btnCloseTypeB->Picture->Bitmap->Width + 7);
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::FormDestroy(TObject *Sender)
{
	mvUserInfoList.clear();
}
//---------------------------------------------------------------------------






void __fastcall TfrmUserManagement::lstvUserListInfoClick(TObject *Sender)
{
	if (!lstvUserListInfo->Selected)
		return;

	TListItem *listitem;
	AnsiString asUserInfo1 = "";
	AnsiString asUserInfo2 = "";
	AnsiString asUserInfo3 = "";
	int	nVIndex = 0;

	listitem = lstvUserListInfo->Items->Item[lstvUserListInfo->Selected->Index];
	lstvUserListInfoIndex = lstvUserListInfo->Selected->Index;//181119
	asUserInfo1 = (AnsiString)listitem->SubItems->Strings[0];
	asUserInfo2 = (AnsiString)listitem->SubItems->Strings[1];
	asUserInfo3 = (AnsiString)listitem->SubItems->Strings[2];
	nVIndex = funSearchUserVIndex(asUserInfo1.c_str(), asUserInfo3.c_str());
	m_nUserListVectorIndex	= nVIndex;//220208

	if (nVIndex == -1) {
		frmMsg->funcMessageDlg("계정 확인:", "정보가 존재하지 않습니다.", 3);
		//btnUserModify->Enabled =  false;
		IMGREGIST->Enabled 					= false;
		IMGREGIST->Picture->Bitmap->Handle  = NULL;
		IMGREGIST->Picture                  = NULL;
		IMGREGIST->Picture->Bitmap->Assign(BITMAP_BTN_REGIST[2]);

		//btnUserDelete->Enabled =  false;
		IMGDELETE->Enabled 					= false;
		IMGDELETE->Picture->Bitmap->Handle  = NULL;
		IMGDELETE->Picture                  = NULL;
		IMGDELETE->Picture->Bitmap->Assign(BITMAP_BTN_DELETE[2]);
		return;
	}

	edtUserInfo1->Text = mvUserInfoList[nVIndex].cName;
	edtUserInfo2->Text = mvUserInfoList[nVIndex].cIpDec;
	edtUserInfo3->Text = mvUserInfoList[nVIndex].cIdDec;
	edtUserInfo4->Text = mvUserInfoList[nVIndex].cPwDec;
	edtUserInfo5->Text = mvUserInfoList[nVIndex].cTel;

	if( !strcmp(mvUserInfoList[nVIndex].cGrade, "9") )//210416//#PERSON_INFO
		edtUserInfo6->Text = "비밀번호 초기화";
	else
		edtUserInfo6->Text = funUserGradeIntToStr(StrToInt(mvUserInfoList[nVIndex].cGrade));
	edtUserInfo7->Text = mvUserInfoList[nVIndex].cDepart;//210303//#USER1_PW//HIDE
	if (StrToInt(mvUserInfoList[nVIndex].cGrade) == 0) edtUserInfo6->Color = TColor(0x008080FF);
	if (StrToInt(mvUserInfoList[nVIndex].cGrade) == 1) edtUserInfo6->Color = clWhite;
	if (StrToInt(mvUserInfoList[nVIndex].cGrade) == 2) edtUserInfo6->Color = clWhite;
	if (StrToInt(mvUserInfoList[nVIndex].cGrade) == 3) edtUserInfo6->Color = clWhite;
	lblUserInfo8->Caption	= mvUserInfoList[nVIndex].cFailCut;

	//[120][120][120][250]
	stbVectorInfo->Panels->Items[0]->Text = mvUserInfoList[nVIndex].cIpDec;
	stbVectorInfo->Panels->Items[1]->Text = mvUserInfoList[nVIndex].cName;
	stbVectorInfo->Panels->Items[2]->Text = mvUserInfoList[nVIndex].cIdDec;
	stbVectorInfo->Tag = nVIndex;


	//btnUserModify->Enabled =  true;
	IMGMODIFY->Enabled 				= true;
	IMGMODIFY->Picture->Bitmap->Handle  = NULL;
	IMGMODIFY->Picture                  = NULL;
	IMGMODIFY->Picture->Bitmap->Assign(BITMAP_BTN_MODIFY[0]);
	//btnUserDelete->Enabled =  true;
	IMGDELETE->Enabled 				= true;
	IMGDELETE->Picture->Bitmap->Handle  = NULL;
	IMGDELETE->Picture                  = NULL;
	IMGDELETE->Picture->Bitmap->Assign(BITMAP_BTN_DELETE[0]);
}
//---------------------------------------------------------------------------
void __fastcall TfrmUserManagement::funcReadUserInformation()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	SQLINTEGER m_nVal[DF_TB_USER1_COL_COUNT];
	SQLRETURN 	ret;
	AnsiString 	asSqlQry	= "";
	AnsiString 	asOrderBy	= "";
	UserInfo 	mUserInfo;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&mUserInfo, 0, sizeof(mUserInfo));

	int nIndex = 1;
	SQLBindCol(frmSql->m_hStmt, nIndex, SQL_C_CHAR, mUserInfo.cName, 		sizeof(mUserInfo.cName), 		&m_nVal[nIndex - 1]);		nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex, SQL_C_CHAR, mUserInfo.cIp, 			sizeof(mUserInfo.cIp), 			&m_nVal[nIndex - 1]);		nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex, SQL_C_CHAR, mUserInfo.cDepart, 		sizeof(mUserInfo.cDepart), 		&m_nVal[nIndex - 1]);		nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex, SQL_C_CHAR, mUserInfo.cGrade, 		sizeof(mUserInfo.cGrade), 		&m_nVal[nIndex - 1]);		nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex, SQL_C_CHAR, mUserInfo.cId, 			sizeof(mUserInfo.cId), 			&m_nVal[nIndex - 1]);		nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex, SQL_C_CHAR, mUserInfo.cPw, 			sizeof(mUserInfo.cPw), 			&m_nVal[nIndex - 1]);		nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex, SQL_C_CHAR, mUserInfo.cTel, 		sizeof(mUserInfo.cTel), 		&m_nVal[nIndex - 1]);		nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex, SQL_C_CHAR, mUserInfo.cMemo, 		sizeof(mUserInfo.cMemo), 		&m_nVal[nIndex - 1]);		nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex, SQL_C_CHAR, mUserInfo.cFailCut, 	sizeof(mUserInfo.cFailCut), 	&m_nVal[nIndex - 1]);		nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex, SQL_C_CHAR, mUserInfo.cLoginDate, 	sizeof(mUserInfo.cLoginDate), 	&m_nVal[nIndex - 1]);		nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex, SQL_C_CHAR, mUserInfo.cLogoutDate, 	sizeof(mUserInfo.cLogoutDate), 	&m_nVal[nIndex - 1]);		nIndex++;

	//cancel//asSqlQry = "SELECT * FROM TB_USER1 WHERE FT_GRADE!='4'";//200525//#3//44250//WHERE절 추가//
	asSqlQry = "SELECT * FROM TB_USER1 WHERE FT_GRADE!='5'";//220208//4(휴면)->5(삭제)//210331//삭제계정 제외//200525//return//
	//--------------------------------------------
	//251001//[REQ_25_SEP_Meeting]지적정보사업부//
	//--------------------------------------------
	asOrderBy = " ORDER BY CASE WHEN FT_GRADE='0' THEN 1 ELSE 0 END ASC, FT_GRADE ASC";//'1'이면 마지막에 오도록, '0' 먼저 오도록 정렬//
	asSqlQry += asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	mvUserInfoList.clear();

	memset(&mUserInfo, 0, sizeof(mUserInfo));
	while(SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA)
	{
		wsprintf(mUserInfo.cIpDec, "%s", frmMain->func_Decoder(mUserInfo.cIp));
		wsprintf(mUserInfo.cIdDec, "%s", frmMain->func_Decoder(mUserInfo.cId));
		//210303//#USER1_PW//wsprintf(mUserInfo.cPwDec, "%s", frmMain->func_Decoder(mUserInfo.cPw));
		mvUserInfoList.push_back(mUserInfo);
		memset(&mUserInfo, 0, sizeof(mUserInfo));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);
}
//---------------------------------------------------------------------------

//void __fastcall TfrmUserManagement::funcReadUserHistInformation1()
//{
//	SQLHSTMT 		*phStmtSQLA = NULL;
//	SQLCHAR 	    m_cVal[5][255];
//	SQLINTEGER 	    m_nVal[5];
//	UserHistInfo 	mUserHistInfo;
//	AnsiString		asTable1 = "TB_USER1";
//	AnsiString		asTable2 = "TB_USER2";
//	AnsiString		asTable3 = "TB_USER3";
//	AnsiString		asColumnStr;
//	AnsiString		asJoinStr;
//	AnsiString		asWhereStr;
//	AnsiString		asOrderStr;
//	int 			nColCount = 5;
//
//	phStmtSQLA = &frmSql->m_hStmt;
//
//
//	for (int i = 0; i < nColCount; i++) {
//		memset(&m_cVal[i][0], 0x00, sizeof(m_cVal[i]));
//		SQLBindCol(frmSql->m_hStmt, i+1, SQL_C_CHAR, &m_cVal[i][0], sizeof(m_cVal[i]), &m_nVal[i]);
//	}
//
//	asColumnStr = asColumnStr + asTable1 + ".FT_IP";
//	asColumnStr = asColumnStr + ", " + asTable1 + ".FT_ID";
//	asColumnStr = asColumnStr + ", " + asTable1 + ".FT_NAME";
//	asColumnStr = asColumnStr + ", " + asTable2 + ".FT_LOGIN";
//	asColumnStr = asColumnStr + ", " + asTable2 + ".FT_LOGOUT";
//
//	asWhereStr = asTable1 +  ".FT_ID = " + asTable2 + ".FT_ID";
//
//	asOrderStr = "ORDER BY " + asTable2 + ".FT_LOGOUT";
//
//	char cSqlQry[QRY_ARRANGE_SIZE];
//	memset(cSqlQry, 0x00, QRY_ARRANGE_SIZE);
//	sprintf(cSqlQry, "SELECT %s FROM %s INNER JOIN %s ON %s %s", asColumnStr, asTable1, asTable2, asWhereStr, asOrderStr);
//
//	if (frmMain->func_QryProcess(phStmtSQLA, cSqlQry) < 0)
//	{
//		return;
//	}
//
//	for (int i = 0; i < nColCount; i++)
//		memset(&m_cVal[i][0], 0x00, sizeof(m_cVal[i]));
//
//	while (SQLFetch(*phStmtSQLA) != SQL_NO_DATA)
//	{
//		memset(&mUserHistInfo, 0, sizeof(mUserHistInfo));
//
//		memcpy(mUserHistInfo.cIp, m_cVal[0], sizeof(mUserHistInfo.cIp));
//		wsprintf(mUserHistInfo.cIpDec, "%s", frmMain->func_Decoder(mUserHistInfo.cIp));
//		memcpy(mUserHistInfo.cId, m_cVal[1], sizeof(mUserHistInfo.cId));
//		wsprintf(mUserHistInfo.cIdDec, "%s", frmMain->func_Decoder(mUserHistInfo.cId));
//		memcpy(mUserHistInfo.cName, m_cVal[2], sizeof(mUserHistInfo.cName));
//		memcpy(mUserHistInfo.cLoginDate, m_cVal[3], sizeof(mUserHistInfo.cLoginDate));
//		memcpy(mUserHistInfo.cLogoutDate, m_cVal[4], sizeof(mUserHistInfo.cLogoutDate));
//		mUserHistInfo.nAction = 0;//Login
//
//		for (int i = 0; i < nColCount; i++) {
//			memset(&m_cVal[i][0], 0x00, sizeof(m_cVal[i]));
//		}
//
//		mvUserHistInfoList.push_back(mUserHistInfo);
//		nUser4Count++;
//	};
//	if (*phStmtSQLA)
//		SQLCloseCursor(*phStmtSQLA);
//}
////---------------------------------------------------------------------------
//void __fastcall TfrmUserManagement::funcReadUserHistInformation2()
//{
//	SQLHSTMT 		*phStmtSQLA = NULL;
//	SQLCHAR 	    m_cVal[5][255];
//	SQLINTEGER 	    m_nVal[5];
//	UserHistInfo 	mUserHistInfo;
//	AnsiString		asTable1 = "TB_USER1";
//	AnsiString		asTable2 = "TB_USER2";
//	AnsiString		asTable3 = "TB_USER3";
//	AnsiString		asColumnStr;
//	AnsiString		asJoinStr;
//	AnsiString		asWhereStr;
//	AnsiString		asOrderStr;
//	int 			nColCount = 5;
//
//	phStmtSQLA = &frmSql->m_hStmt;
//
//	for (int i = 0; i < nColCount; i++) {
//		memset(&m_cVal[i][0], 0x00, sizeof(m_cVal[i]));
//		SQLBindCol(frmSql->m_hStmt, i+1, SQL_C_CHAR, &m_cVal[i][0], sizeof(m_cVal[i]), &m_nVal[i]);
//	}
//
//	asColumnStr = asColumnStr + asTable1 + ".FT_IP";
//	asColumnStr = asColumnStr + ", " + asTable1 + ".FT_ID";
//	asColumnStr = asColumnStr + ", " + asTable1 + ".FT_NAME";
//	asColumnStr = asColumnStr + ", " + asTable3 + ".FT_PNU";
//	asColumnStr = asColumnStr + ", " + asTable3 + ".FT_DATE";
//
//	asWhereStr = asTable1 +  ".FT_ID = " + asTable3 + ".FT_ID";
//
//	asOrderStr = "ORDER BY " + asTable3 + ".FT_DATE";
//
//	char cSqlQry[QRY_ARRANGE_SIZE];
//	memset(cSqlQry, 0x00, QRY_ARRANGE_SIZE);
//	sprintf(cSqlQry, "SELECT %s FROM %s INNER JOIN %s ON %s %s", asColumnStr, asTable1, asTable3, asWhereStr, asOrderStr);
//
//	if (frmMain->func_QryProcess(phStmtSQLA, cSqlQry) < 0)
//	{
//		return;
//	}
//
//	for (int i = 0; i < nColCount; i++)
//		memset(&m_cVal[i][0], 0x00, sizeof(m_cVal[i]));
//
//	while (SQLFetch(*phStmtSQLA) != SQL_NO_DATA)
//	{
//		memset(&mUserHistInfo, 0, sizeof(mUserHistInfo));
//
//		memcpy(mUserHistInfo.cIp, m_cVal[0], sizeof(mUserHistInfo.cIp));
//		wsprintf(mUserHistInfo.cIpDec, "%s", frmMain->func_Decoder(mUserHistInfo.cIp));
//		memcpy(mUserHistInfo.cId, m_cVal[1], sizeof(mUserHistInfo.cId));
//		wsprintf(mUserHistInfo.cIdDec, "%s", frmMain->func_Decoder(mUserHistInfo.cId));
//		memcpy(mUserHistInfo.cName, m_cVal[2], sizeof(mUserHistInfo.cName));
//		memcpy(mUserHistInfo.cPnu, m_cVal[3], sizeof(mUserHistInfo.cPnu));
//		memcpy(mUserHistInfo.cActionDate, m_cVal[4], sizeof(mUserHistInfo.cActionDate));
//		mUserHistInfo.nAction = 1;//Query
//
//		for (int i = 0; i < nColCount; i++) {
//			memset(&m_cVal[i][0], 0x00, sizeof(m_cVal[i]));
//		}
//
//		mvUserHistInfoList.push_back(mUserHistInfo);
//		nUser4Count++;
//	};
//	if (*phStmtSQLA)
//		SQLCloseCursor(*phStmtSQLA);
//}
////---------------------------------------------------------------------------

int TfrmUserManagement::funUserInfoToBuffIndex(char* cUserName)
{
	int nReturnValue = -1;

	for (int i = 0; i < (int)this->mvUserInfoList.size(); i++)
	{
		if (!strcmp(this->mvUserInfoList[i].cName, cUserName))
		{
			nReturnValue = i;
			break;
		}
	}

	return nReturnValue;
}
//---------------------------------------------------------------------------

int TfrmUserManagement::funUserGradeStrToInt(String sGrade)
{
	int nReturnValue = -1;
	if (!sGrade.CompareIC(L"승인대기")) 		nReturnValue = 0;
	if (!sGrade.CompareIC(L"일반사용자")) 		nReturnValue = 1;
	if (!sGrade.CompareIC(L"관리자"))   		nReturnValue = 2;
	if (!sGrade.CompareIC(L"최소사용자")) 		nReturnValue = 3;
	if (!sGrade.CompareIC(L"휴면사용자"))   	nReturnValue = 4;
	if (!sGrade.CompareIC(L"삭제사용자"))   	nReturnValue = 5;
	if (!sGrade.CompareIC(L"비밀번호초기화"))   nReturnValue = -1;
	return nReturnValue;
}
//---------------------------------------------------------------------------

String TfrmUserManagement::funUserGradeIntToStr(int nType)
{
	String sReturnStr = L"";
	if (nType == 0 ) sReturnStr = L"승인대기";
	if (nType == 1 ) sReturnStr = L"일반사용자";
	if (nType == 2 ) sReturnStr = L"관리자";
	if (nType == 3 ) sReturnStr = L"최소사용자";
	if (nType == 4 ) sReturnStr = L"휴면사용자";
	if (nType == 5 ) sReturnStr = L"삭제사용자";//220208
	if (nType == 9 ) sReturnStr = L"비밀번호초기화";//220208//
	return sReturnStr;
}
//---------------------------------------------------------------------------

int TfrmUserManagement::funSearchUserVIndex(char *cName, char *cId)
{
	int nReturnValue = -1;

	for (int i=0; i < (int)mvUserInfoList.size(); i++) {
		if (strcmp(cName, mvUserInfoList[i].cName) == 0) {
			if (strcmp(cId, mvUserInfoList[i].cIdDec) == 0) {
				nReturnValue = i;
			}
		}
	}

	return nReturnValue;
}
//---------------------------------------------------------------------------

void TfrmUserManagement::funListClear()
{
	lstvUserListInfo->Items->BeginUpdate();
	lstvUserListInfo->Items->Clear();
	lstvUserListInfo->Items->EndUpdate();

	edtUserInfo1->Text = L"";
	edtUserInfo2->Text = L"";
	edtUserInfo3->Text = L"";
	edtUserInfo4->Text = L"";
	edtUserInfo5->Text = L"";
	edtUserInfo6->Text = L"";
	//btnUserModify->Enabled =  false;
	IMGMODIFY->Enabled 					= false;
	IMGMODIFY->Picture->Bitmap->Handle  = NULL;
	IMGMODIFY->Picture                  = NULL;
	IMGMODIFY->Picture->Bitmap->Assign(BITMAP_BTN_MODIFY[2]);
	//btnUserDelete->Enabled =  false;
	IMGDELETE->Enabled 					= false;
	IMGDELETE->Picture->Bitmap->Handle  = NULL;
	IMGDELETE->Picture                  = NULL;
	IMGDELETE->Picture->Bitmap->Assign(BITMAP_BTN_DELETE[2]);
}
//---------------------------------------------------------------------------

void TfrmUserManagement::funcListDisplay()
{
	TListItem   *ListItem;
	AnsiString  asKeyword	= edtName->Text;
	AnsiString  asName		= "";
	int 		nIndex		= 0;

	//--------------------------------------------
	//251001//[REQ_25_SEP_Meeting]지적정보사업부//
	//--------------------------------------------
	int			nGrade = -1;
	TStringList *slUserGrade	= new TStringList();
	TStringList *slUserGradeCnt = new TStringList();
	slUserGrade->Clear();
	slUserGrade->Text = "";
	slUserGradeCnt->Clear();
	slUserGradeCnt->Text = "";

	for (int i=0; i < (int)mvUserInfoList.size(); i++) {
		asName	= 	(char*)mvUserInfoList[i].cName;
		if(asKeyword.IsEmpty() || (!asKeyword.IsEmpty() && asName.Pos(asKeyword) > 0))
		{
			ListItem = lstvUserListInfo->Items->Add();
			ListItem->Caption = nIndex+1;//i+1;
			ListItem->SubItems->Add((AnsiString)mvUserInfoList[i].cName);
			ListItem->SubItems->Add((AnsiString)mvUserInfoList[i].cIpDec);
			ListItem->SubItems->Add((AnsiString)mvUserInfoList[i].cIdDec);
			//210303//#USER1_PW//ListItem->SubItems->Add((AnsiString)mvUserInfoList[i].cPw);
			//--------------------------------------------
			//251001//[REQ_25_SEP_Meeting]지적정보사업부//
			//--------------------------------------------
			if((char *)mvUserInfoList[i].cGrade == "")
				strcpy(mvUserInfoList[i].cGrade, "0");
//			if((char *)mvUserInfoList[i].cGrade == "")
//			{
//				frmMsg->funcMessageDlg("권한정보 확인:", "사용자 권한정보를 확인해주세요.", 3);
//				return;
//			}
			//--------------------------------------------
			ListItem->SubItems->Add(funUserGradeIntToStr(StrToInt(mvUserInfoList[i].cGrade)));
			ListItem->SubItems->Add((AnsiString)mvUserInfoList[i].cTel);
			ListItem->SubItems->Add(i);
			nIndex++;

			//--------------------------------------------
			//251001//[REQ_25_SEP_Meeting]지적정보사업부//
			//사용자 권한별 집계 표시//
			//--------------------------------------------
			nGrade = AnsiString(mvUserInfoList[i].cGrade).ToInt();
			int slidx = slUserGrade->IndexOf(nGrade);
			if(slidx > -1)
			{
				slUserGradeCnt->Strings[slidx] = slUserGradeCnt->Strings[slidx].ToInt()+1;
			}
			else
			{
				slUserGrade->Add(nGrade);
				slUserGradeCnt->Add(1);
            }
		}
	}

	//--------------------------------------------
	//251001//[REQ_25_SEP_Meeting]지적정보사업부//
	//사용자 권한별 집계 표시//
	//--------------------------------------------
	AnsiString  asTotalGrade = "";
	for(int z = 0; z < slUserGrade->Count; z++)
	{
		AnsiString  asGrade = slUserGrade->Strings[z];
		AnsiString  asCount = slUserGradeCnt->Strings[z];
		AnsiString  asMsg = "";

//승인대기
//일반사용자
//관리자
//최소사용자
//휴면사용자
//삭제사용자

		if(asGrade == "1")	asGrade = "일반사용자";
		else if(asGrade == "2")	asGrade = "관리자";
		else if(asGrade == "3")	asGrade = "최소사용자";
		else if(asGrade == "4")	asGrade = "휴면사용자";
		else if(asGrade == "5")	asGrade = "삭제사용자";
		else					asGrade = "승인대기";
		asMsg.sprintf("%s(%s)", asGrade, asCount);
		asTotalGrade += (z < slUserGrade->Count-1) ? (asMsg + ",") : (asMsg);
	}
	lblTotalGrade->Caption = asTotalGrade;

	if(mvUserInfoList.size() > 0)//181119_moved
	{
		if(nIndex >= 0)//if(lstvUserListInfoIndex >= 0)
		{
			lstvUserListInfoIndex	= 0;
			lstvUserListInfo->SetFocus();
			lstvUserListInfo->Selected = lstvUserListInfo->Items->Item[lstvUserListInfoIndex];
			lstvUserListInfoClick(lstvUserListInfo);
			//lstvUserListInfo->ItemFocused = lstvUserListInfo->Items->Item[0];
		}
//		else//No Data
//		{
//			lstvUserListInfo->SetFocus();
//			lstvUserListInfo->Selected = lstvUserListInfo->Items->Item[0];
//			lstvUserListInfoClick(lstvUserListInfo);
//			lstvUserListInfoIndex = 0;
//			//lstvUserListInfo->ItemFocused = lstvUserListInfo->Items->Item[0];
//		}
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::funcSetUserLoginState(UserInfo* _mUserInfo, int nType)
{
	char			cSqlQry[QRY_ARRANGE_SIZE];
	SQLRETURN 		ret;

	memset(cSqlQry, 0, QRY_ARRANGE_SIZE);

	if (nType == 2) {
		wsprintf(cSqlQry, "UPDATE TB_USER1 SET FT_LOGOUTDATE='%s' WHERE FT_ID='%s'", _mUserInfo->cLogoutDate, _mUserInfo->cId);
	}
	else if (nType == 12) {
		wsprintf(cSqlQry, "UPDATE TB_USER1 SET FT_LOGOUTDATE='%s' WHERE FT_ID='%s' AND FT_LOGINDATE='%s'", _mUserInfo->cLogoutDate, _mUserInfo->cId, _mUserInfo->cLoginDate);
	}
//190826//TO_CLEAN_USER_TABLES
//	else if (nType == 13) {
//		wsprintf(cSqlQry, "UPDATE TB_USER2 SET FT_LOGOUT='%s' WHERE FT_ID='%s' AND FT_LOGIN='%s'", _mUserInfo->cLogoutDate, _mUserInfo->cId, _mUserInfo->cLoginDate);
//	}
//	else if (nType == 14) {
//
//	}
	else {
		return;
	}
	frmSql->func_QryProcess(cSqlQry);
}
//---------------------------------------------------------------------------

//_nType 0:Login, 9:Logout(update), 1:Query, 2:Modify, 3:Delete, 4:Print, 5:View(Document), 6:New(JDM), 8:Statistics(JDM)
//7:파일저장, 11:권한변경, 12:휴면계정//
//230207//사용자작업기록에서 funcGetKindNameToKindIndex로 체크하여 문제가 발생//
//DB직접Query했을 때와 프로그램에서 동일 Query 수행 시 결과가 다르게 나오는 이슈발생//
//_nType을 _asTypeNm으로 변경한다//
//230207//void __fastcall TfrmUserManagement::funcSetUserHistState(UserInfo* _mUserInfo, int _nType, int _nDoc)
void __fastcall TfrmUserManagement::funcSetUserHistState(UserInfo* _mUserInfo, AnsiString  _asTypeNm, int _nDoc)
{
	AnsiString  asColumnStr 	= "";//for INSERT
	AnsiString  asValuesStr 	= "";//for INSERT
	AnsiString  asLogoutStr 	= "";//for UPDATE
	AnsiString  asTypeNm 		= "";//210305//#44710//
	AnsiString  asTypeCd		= eFunc->funcGetKindNameToKindCode(503, _asTypeNm.c_str());//230207//funcSetUserHistState()Param변경//
	AnsiString  asDateStr 		= Now().FormatString("yyyy-mm-dd hh:nn:ss");
	int         nType			= asTypeCd.ToInt();
	char		cSqlQry[QRY_ARRANGE_SIZE];
	SQLRETURN 	ret;

	//260909//"admin"(유지관리계정) 암호화가 잘못되어 변경//
	if( (char*)_mUserInfo->cId == frmMain->func_Encoder("admin") || (char*)_mUserInfo->cId == "")//231012//기타의 사유로 로그인정보 없는 계정정보 들어오면 무시//
		return;

	memset(cSqlQry, 0, QRY_ARRANGE_SIZE);

//230207//funcSetUserHistState()Param변경//
//	asTypeNm	= eFunc->funcGetKindCodeToKindName(503, AnsiString(IntToStr(_nType)).c_str());//210305//#44710//
	asTypeNm	= _asTypeNm;

	if(asTypeNm != "로그아웃시각")//210305//#44710//if(_nType != 9)//insert
	{
		//Column
		asColumnStr = asColumnStr + "FT_IP";
		asColumnStr = asColumnStr + ", FT_DEPART";
		asColumnStr = asColumnStr + ", FT_ID";
		asColumnStr = asColumnStr + ", FT_NAME";
		asColumnStr = asColumnStr + ", FT_LOGIN";
		asColumnStr = asColumnStr + ", FT_ACTION";
		if(asTypeNm != "로그인시각")//210305//#44710//if(_nType != 0)
		{
			asColumnStr = asColumnStr + ", FT_DOC";
			asColumnStr = asColumnStr + ", FT_PNU";
			asColumnStr = asColumnStr + ", FT_ACTIONDATE";
		}
		//210323//#PERSON_INFO//if(asTypeNm == "인쇄" || asTypeNm == "문서열람" || asTypeNm == "파일저장")//210305//#44710//if(_nType == 4 || _nType == 5 || _nType == 7)//Print//View//Save

		if(asTypeNm == "인쇄" || asTypeNm == "문서열람" || asTypeNm == "파일저장")//210305//#44710//if(_nType == 4 || _nType == 5 || _nType == 7)//Print//View//Save
		{
			asColumnStr = asColumnStr + ", FT_PATHNAME";
		}
		else if(asTypeNm == "권한변경" || asTypeNm == "사용승인")//210323//#PERSON_INFO//
		{
			asColumnStr = asColumnStr + ", FT_PATHNAME";
		}

		//Values
		asValuesStr = asValuesStr + "'" 	+ _mUserInfo->cIp + "'";
		asValuesStr = asValuesStr + ", '" 	+ _mUserInfo->cDepart + "'";
		asValuesStr = asValuesStr + ", '" 	+ _mUserInfo->cId + "'";
		asValuesStr = asValuesStr + ", '" 	+ _mUserInfo->cName + "'";
		asValuesStr = asValuesStr + ", '" 	+ _mUserInfo->cLoginDate + "'";
		asValuesStr = asValuesStr + ", "  	+ nType;//230207//funcSetUserHistState()Param변경//_nType->nType
		if(asTypeNm != "로그인시각")//210305//#44710//if(_nType != 0)
		{
			asValuesStr = asValuesStr + ", "  + _nDoc;//FT_DOC
			if(asTypeNm == "권한변경" || asTypeNm == "사용승인" || asTypeNm == "삭제계정")//220208//<삭제계정> 추가//210323//#PERSON_INFO
				asValuesStr = asValuesStr + ", '" + frmMain->func_Encoder(edtUserInfo3->Text) + "'";//220207//asValuesStr = asValuesStr + ", '" + _mUserInfo->cId + "'";//변경대상 ID//
			else
				asValuesStr = asValuesStr + ", '" + frmMain->m_asSearchPnu + "'";
			asValuesStr = asValuesStr + ", '" + asDateStr + "'";//FT_ACTIONDATE
		}
		if(asTypeNm == "인쇄" || asTypeNm == "문서열람" || asTypeNm == "파일저장")//210305//#44710//if(_nType == 4 || _nType == 5 || _nType == 7)//Print//View//Save
		{
			AnsiString asStr = frmMain->m_asCurrentFilePath;
			asStr = StringReplace(asStr, "\\", "/", TReplaceFlags() << rfReplaceAll);
			asValuesStr = asValuesStr + ", '" + asStr.Trim() + "'";
		}
		else if(asTypeNm == "권한변경" || asTypeNm == "사용승인")//210323//#PERSON_INFO//210305//#44710//else if(_nType == 11)//권한변경
		{
        	//210323//#PERSON_INFO
			AnsiString asStr = frmUserAdd->edtReason->Text;
			asValuesStr = asValuesStr + ", '" + asStr.Trim() + "'";//PATH_NAME=>권한변경일때만 REASON
		}
		wsprintf(cSqlQry, "INSERT INTO TB_USER4 (%s) values(%s)", asColumnStr, asValuesStr);
	}
	else//logout//update
	{
		//Column
		asLogoutStr = asLogoutStr + "FT_LOGOUT = '" + _mUserInfo->cLogoutDate + "'";
		wsprintf(cSqlQry, "UPDATE TB_USER4 SET %s WHERE FT_ID='%s' AND FT_LOGIN='%s'", asLogoutStr, _mUserInfo->cId, _mUserInfo->cLoginDate);
	}
	frmSql->func_QryProcess(cSqlQry);
}
//---------------------------------------------------------------------------


void __fastcall TfrmUserManagement::funcSQLUpdateUserBInfo(int _nValue, AnsiString _asId)
{
	SQLRETURN 	usRet;
	char		cSqlQry[QRY_ARRANGE_SIZE];

	AnsiString	asUserInfo2 = IntToStr(_nValue);

	memset(cSqlQry, 0, QRY_ARRANGE_SIZE);
	wsprintf(cSqlQry, "UPDATE TB_USER1 SET FT_MEMO='%s' WHERE FT_ID='%s'", asUserInfo2.c_str(), _asId);

	usRet = SQLExecDirect(frmSql->m_hStmt, (SQLCHAR *) cSqlQry, SQL_NTS);
	if ((usRet != SQL_SUCCESS) &&(usRet != SQL_SUCCESS_WITH_INFO)  && (usRet != SQL_NO_DATA) )
	{
		SQLCloseCursor(frmSql->m_hStmt);
		frmMsg->funcMessageDlg("DB 정보 확인:", "데이터베이스 정보 확인이 필요합니다. 제조사에 문의 바랍니다.", 3);
		return;
	}

	wsprintf(cSqlQry, "COMMIT");
	usRet = SQLExecDirect(frmSql->m_hStmt, (SQLCHAR *) cSqlQry, SQL_NTS);

	if ((usRet != SQL_SUCCESS) &&(usRet != SQL_SUCCESS_WITH_INFO)  && (usRet != SQL_NO_DATA))
	{
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	if (frmSql->m_hStmt)		SQLCloseCursor(frmSql->m_hStmt);
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::PageControl1Change(TObject *Sender)
{
	if (PageControl1->ActivePageIndex == 0)
	{
		this->Width 		 	= 747;
		stbVectorInfo->Width	= 741;
	}
	else if (PageControl1->ActivePageIndex == 1)
	{
		if (!lstvUserListInfo->Selected)
		{
			frmMsg->funcMessageDlg("사용자 선택:", "권한설정을 진행할 사용자를 선택해주세요.", 3);
			return;
		}

		lvUserBList->Items->Clear();

		this->Width 			= 350;
		stbVectorInfo->Width 	= 344;

		TListItem   *ListItem;
		int nIdx = 1;

		for (int i = 1; i < DF_DOC_CNT; i++)//#TAB00DEL#<검색>은 제외하기로//사장님Req//
		{
			if( frmMain->INIINFO.DOCKINDNAME[i].IsEmpty() )
				continue;

			if( frmMain->INIINFO.B_DOCKIND[i] == false)
				continue;

			ListItem = lvUserBList->Items->Add();
			ListItem->Caption = frmMain->INIINFO.DOCKINDNAME[i];
			ListItem->SubItems->Add(IntToStr(i));
			nIdx++;
		}

		int nValue = 0;
		int nBuffIndex = 0;
		int nGrade = StrToInt(frmUserManagement->mCurrentUser.cGrade);//frmUserManagement->mCurrentUser : 현재 접속 user

		if(nGrade == 2)//if admin, can select user in ListItem
		{
			nBuffIndex = lstvUserListInfo->Selected->Caption.ToInt();//SubItems->Strings[0].ToInt();
			nValue = this->funcSQLSelectUserBInfo(AnsiString(mvUserInfoList[nBuffIndex-1].cId));
		}
		else if(nGrade == 1)//myself
		{
			nValue = this->funcSQLSelectUserBInfo(frmMain->m_asCurrentId);
		}
		//=============================================================================
		//240321//[Add]결의서.개인정보.조서만검색.최소사용자 권한//
		//=============================================================================
		else if(nGrade == 3)//'최소사용자'
		{
			frmMsg->funcMessageDlg("최소사용자 알림:", "'최소사용자'의 문서권한설정을 제한하여 선택해주세요.", 1);
		}
		//=============================================================================

		int nListCut = 0;
		for (int i = 1; i < DF_DOC_CNT; i++)//#TAB00DEL#<검색>은 제외하기로//사장님Req//
		{
			if( frmMain->INIINFO.DOCKINDNAME[i].IsEmpty() )
				continue;

			if( frmMain->INIINFO.B_DOCKIND[i] == false )
				continue;

			lvUserBList->Items->Item[nListCut]->Checked = (nValue >> i) & 0x00000001;
			nListCut++;
		}
	}

	btnCloseTypeB->Left = this->Width - (btnCloseTypeB->Picture->Bitmap->Width + 7);

}
//---------------------------------------------------------------------------

int __fastcall TfrmUserManagement::funcSQLSelectUserBInfo(AnsiString _asId)
{
	if (frmSql->m_hStmt)		SQLCloseCursor(frmSql->m_hStmt);

	int nValue = 0;

	SQLCHAR 	m_cVal[255];
	SQLINTEGER m_nVal;
	SQLRETURN 	ret;
	char 		min_cValue[255];

	SQLBindCol(frmSql->m_hStmt, 1,  SQL_C_CHAR, m_cVal, sizeof(m_cVal) , &m_nVal);

	char cSql[2048];
	memset(cSql, 0, sizeof(cSql));
	sprintf(cSql, "SELECT FT_MEMO FROM TB_USER1 WHERE FT_ID = '%s'", _asId);

	ret = SQLPrepare(frmSql->m_hStmt, (SQLCHAR *)cSql, SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if ((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(frmSql->m_hStmt);
		return 0;
	}
	else {
		memset(m_cVal, 0x00, sizeof(m_cVal));

		while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA)
		{
			memset(min_cValue, 0x00, sizeof(min_cValue));
			memcpy(min_cValue, m_cVal, sizeof(min_cValue));
			AnsiString asValue = min_cValue;
			if(asValue == "A")
				nValue = 0;
			else
				nValue = StrToInt(asValue);
		};
		if(frmSql->m_hStmt)
			SQLCloseCursor(frmSql->m_hStmt);
	}

	return nValue;
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::cbxAll_OnClick(TObject *Sender)
{
	//210705//이 기능을 왜 막아놨었지?//
	int nListCut = 0;
	//231014//시군별 구축 문서만 표시하므로 전체를 다 돌리면 안됨//for(int i=1; i<DF_DOC_CNT; i++)//with Doc19
	for(int i=1; i<lvUserBList->Items->Count+1; i++)//with Doc19
	{
		lvUserBList->Items->Item[nListCut]->Checked = cbxAll->Checked;
		nListCut++;
	}
}
//---------------------------------------------------------------------------
//Minji_#02_F_SetGrant
void __fastcall TfrmUserManagement::TabSheet1_OnShow(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
//Minji_#02_F_SetGrant
void __fastcall TfrmUserManagement::TabSheet2_OnShow(TObject *Sender)
{
	//=============================================================================
	//240321//[Add]결의서.개인정보.조서만검색.최소사용자 권한//권한표시 추가//
	//=============================================================================
	GroupBox3->Caption = "사용자별 설정( " + lstvUserListInfo->Selected->SubItems->Strings[0] + " )(" + lstvUserListInfo->Selected->SubItems->Strings[3] + ")";
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::frmUserManagement_OnCreate(TObject *Sender)
{
	PageControl1->TabIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::PageControl1Changing(TObject *Sender, bool &AllowChange)
{
	if (PageControl1->ActivePageIndex == 0)//minji
	{
		if(mvUserInfoList.size() == 0)
		{
			frmMsg->funcMessageDlg("권한설정 알림:", "계정 정보가 존재할 때, 권한설정가능합니다.", 3);
			AllowChange = false;
		}

		//181226//관리자만 권한설정 가능
		int nGrade = StrToInt(frmUserManagement->mCurrentUser.cGrade);
		if(nGrade != 2)//if admin, ListItem Selected User
		{
			frmMsg->funcMessageDlg("권한설정 알림:", "관리자에게 권한설정을 요청하세요.", 3);
			AllowChange = false;
		}//
		else if(nGrade == 2)//Login Grade
		{
			AnsiString asId = frmUserManagement->mCurrentUser.cId;
			int nBuffIndex = lstvUserListInfo->Selected->Caption.ToInt();
			int nSelectedIdGrade = StrToInt(mvUserInfoList[nBuffIndex-1].cGrade);
			if((asId != frmMain->func_Encoder("admin")) && (nSelectedIdGrade == 2 && asId != AnsiString(mvUserInfoList[nBuffIndex-1].cId)))
			{
				frmMsg->funcMessageDlg("권한설정 알림:", "다른 관리자의 권한설정은 해당 관리자만 가능합니다.", 3);
				AllowChange = false;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::funcLoadButtonImage()
{
	AnsiString asPath = frmMain->ROOTPATH + "RES\\MAIN\\";
	AnsiString filename = "";

	//Button Image
	for(int i = 0; i < 3; i++)
	{
		TPngImage *imgPng = new TPngImage();
		filename = asPath + "btnUserAdd" + IntToStr(i) + ".png";
		imgPng->LoadFromFile(filename);
		BITMAP_BTN_REGIST[i] = new Graphics::TBitmap();
		BITMAP_BTN_REGIST[i]->Assign(imgPng);
		delete imgPng;
		imgPng = NULL;
		//
		imgPng = new TPngImage();
		filename = asPath + "btnUserModify" + IntToStr(i) + ".png";
		imgPng->LoadFromFile(filename);
		BITMAP_BTN_MODIFY[i] = new Graphics::TBitmap();
		BITMAP_BTN_MODIFY[i]->Assign(imgPng);
		delete imgPng;
		imgPng = NULL;
		//
		imgPng = new TPngImage();
		filename = asPath + "btnDelete" + IntToStr(i) + ".png";
		imgPng->LoadFromFile(filename);
		BITMAP_BTN_DELETE[i] = new Graphics::TBitmap();
		BITMAP_BTN_DELETE[i]->Assign(imgPng);
		delete imgPng;
		imgPng = NULL;
		//
		if(i < 2)
		{
			imgPng = new TPngImage();
			filename = asPath + "btnExit" + IntToStr(i) + ".png";
			imgPng->LoadFromFile(filename);
			BITMAP_BTN_EXIT[i] = new Graphics::TBitmap();
			BITMAP_BTN_EXIT[i]->Assign(imgPng);
			delete imgPng;
			imgPng = NULL;
			//
			imgPng = new TPngImage();
			filename = asPath + "btnLog" + IntToStr(i) + ".png";
			imgPng->LoadFromFile(filename);
			BITMAP_BTN_LOG[i] = new Graphics::TBitmap();
			BITMAP_BTN_LOG[i]->Assign(imgPng);
			delete imgPng;
			imgPng = NULL;
			//
			imgPng = new TPngImage();
			filename = asPath + "btnSaveSetting" + IntToStr(i) + ".png";
			imgPng->LoadFromFile(filename);
			BITMAP_BTN_SAVESETTING[i] = new Graphics::TBitmap();
			BITMAP_BTN_SAVESETTING[i]->Assign(imgPng);
			delete imgPng;
			imgPng = NULL;
		}
	}

	IMGREGIST->Picture->Bitmap->Assign(BITMAP_BTN_REGIST[0]);
	IMGMODIFY->Picture->Bitmap->Assign(BITMAP_BTN_MODIFY[0]);
	IMGDELETE->Picture->Bitmap->Assign(BITMAP_BTN_DELETE[0]);
	IMGEXIT->Picture->Bitmap->Assign(BITMAP_BTN_EXIT[0]);
	IMGLOG->Picture->Bitmap->Assign(BITMAP_BTN_LOG[0]);
	IMGSAVESETTING->Picture->Bitmap->Assign(BITMAP_BTN_SAVESETTING[0]);
	IMGEXIT2->Picture->Bitmap->Assign(BITMAP_BTN_EXIT[0]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::funcDeleteButtonImage()
{
	for(int i = 0; i < 3; i++)
	{
		delete BITMAP_BTN_REGIST[i];
		BITMAP_BTN_REGIST[i] = NULL;
		delete BITMAP_BTN_MODIFY[i];
		BITMAP_BTN_MODIFY[i] = NULL;
		delete BITMAP_BTN_DELETE[i];
		BITMAP_BTN_DELETE[i] = NULL;
		if(i < 2)
		{
			delete BITMAP_BTN_EXIT[i];
			BITMAP_BTN_EXIT[i] = NULL;
			delete BITMAP_BTN_LOG[i];
			BITMAP_BTN_LOG[i] = NULL;
			delete BITMAP_BTN_SAVESETTING[i];
			BITMAP_BTN_SAVESETTING[i] = NULL;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::IMGREGISTMouseEnter(TObject *Sender)
{
	if(IMGREGIST->Enabled)
	{
		IMGREGIST->Picture->Bitmap->Handle  = NULL;
		IMGREGIST->Picture                  = NULL;
		IMGREGIST->Picture->Bitmap->Assign(BITMAP_BTN_REGIST[1]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::IMGREGISTMouseLeave(TObject *Sender)
{
	if(IMGREGIST->Enabled)
	{
		IMGREGIST->Picture->Bitmap->Handle  = NULL;
		IMGREGIST->Picture                  = NULL;
		IMGREGIST->Picture->Bitmap->Assign(BITMAP_BTN_REGIST[0]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::IMGREGISTClick(TObject *Sender)
{
	if(IMGREGIST->Enabled)
	{
		frmUserAdd->Tag = FORM_SHOW_MODE_RECORD;
		frmUserAdd->ShowModal();
		if (frmUserAdd->b_Content_Change_flag == false)
			return;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::IMGMODIFYMouseEnter(TObject *Sender)
{
	if(IMGMODIFY->Enabled)
	{
		IMGMODIFY->Picture->Bitmap->Handle  = NULL;
		IMGMODIFY->Picture                  = NULL;
		IMGMODIFY->Picture->Bitmap->Assign(BITMAP_BTN_MODIFY[1]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::IMGMODIFYMouseLeave(TObject *Sender)
{
	if(IMGMODIFY->Enabled)
	{
		IMGMODIFY->Picture->Bitmap->Handle  = NULL;
		IMGMODIFY->Picture                  = NULL;
		IMGMODIFY->Picture->Bitmap->Assign(BITMAP_BTN_MODIFY[0]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::IMGMODIFYClick(TObject *Sender)
{
	if(IMGMODIFY->Enabled)
	{
		frmUserAdd->Tag = FORM_SHOW_MODE_MODIFY;

		frmUserAdd->edtUserInfo1->Text = edtUserInfo1->Text;      					//NAME
		frmUserAdd->edtUserInfo2->Text = edtUserInfo2->Text;						//IP
		//220208//
		int nGradeIndex = funUserGradeStrToInt(edtUserInfo6->Text); // GRADE
		if(nGradeIndex == -1)//220208//비밀번호초기화상태였다면, 원래 권한정보를 failcut에서 가져온다//
		{
			AnsiString asStr	= (char*)mvUserInfoList[m_nUserListVectorIndex].cFailCut;
			if(asStr.IsEmpty())	asStr	= "0";//비어있다면 어쩔 수 없이 '최소사용자'로//
			frmUserAdd->cboGrade->ItemIndex	= asStr.ToInt();
			frmUserAdd->cboGrade->Enabled	= false;// GRADE
		}
		//260909//[삭제]와 [권한변경-삭제사용자] 기능이 TB_USER4 에 기록이 달라서 아래와 같이 한 개의 ROOT로 변경//
		else if(Sender == IMGDELETE)
		{
			frmUserAdd->cboGrade->Enabled	= true;// GRADE
			frmUserAdd->cboGrade->ItemIndex = 5;//"삭제사용자"
		}
		else
		{
			frmUserAdd->cboGrade->Enabled	= true;// GRADE
			frmUserAdd->cboGrade->ItemIndex = nGradeIndex;//
		}
//		if(edtUserInfo6->Text == "비밀번호 초기화")//210416//#PERSON_INFO
//			frmUserAdd->cboGrade->ItemIndex = 5; // GRADE
//		else
//			frmUserAdd->cboGrade->ItemIndex = funUserGradeStrToInt(edtUserInfo6->Text); // GRADE
		frmUserAdd->edtUserInfo3->Text = edtUserInfo3->Text;						//ID
		frmUserAdd->edtUserInfo4->Text = edtUserInfo4->Text;						//PW
		frmUserAdd->edtUserInfo5->Text = edtUserInfo5->Text;                        //TEL
		frmUserAdd->edtUserInfo6->Text = edtUserInfo7->Text;           				//DEPART//210303//#USER1_PW//
		frmUserAdd->edtUserInfo7->Text = edtUserInfo4->Text;                        //RE PW
		AnsiString asStr = lblUserInfo8->Caption;
		if(asStr.IsEmpty())	asStr = "0";
		frmUserAdd->edtUserInfo8->Text = asStr;                        //RE PW
		frmUserAdd->ShowModal();
		if (frmUserAdd->b_Content_Change_flag == false)
			return;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::IMGDELETEMouseEnter(TObject *Sender)
{
	if(IMGMODIFY->Enabled)
	{
		IMGDELETE->Picture->Bitmap->Handle  = NULL;
		IMGDELETE->Picture                  = NULL;
		IMGDELETE->Picture->Bitmap->Assign(BITMAP_BTN_DELETE[1]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::IMGDELETEMouseLeave(TObject *Sender)
{
	if(IMGMODIFY->Enabled)
	{
		IMGDELETE->Picture->Bitmap->Handle  = NULL;
		IMGDELETE->Picture                  = NULL;
		IMGDELETE->Picture->Bitmap->Assign(BITMAP_BTN_DELETE[0]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::IMGDELETEClick(TObject *Sender)
{
	if(IMGMODIFY->Enabled)
	{
		//260909//[삭제]와 [권한변경-삭제사용자] 기능이 TB_USER4 에 기록이 달라서 아래와 같이 한 개의 ROOT로 변경//
		frmMsg->funcMessageDlg("메뉴 이동:", "[권한변경]으로 진행해주세요.", 3);
		IMGMODIFYClick(IMGDELETE);
/*
		frmMsg->funcMessageDlg("계정 삭제 확인:", "선택한 사용자를 삭제 하시겠습니까?", 1);
		if(frmMsg->m_bClick != 1)//Yes
			return;

		SQLRETURN 		usRet;
		AnsiString 		asSqlQry;
		char			cSqlQry[QRY_ARRANGE_SIZE];

		AnsiString	asUserInfo1 = edtUserInfo1->Text.c_str();       //NAME
		AnsiString	asUserInfo2 = frmMain->func_Encoder(edtUserInfo2->Text); 		//IP
		AnsiString	asUserInfo3 = frmMain->func_Encoder(edtUserInfo3->Text); 		//ID
		AnsiString	asNow		= Now().FormatString("yyyy-mm-dd hh:nn:ss");

		//---
		memset(cSqlQry, 0, QRY_ARRANGE_SIZE);
		//190712//사용자정보삭제 기능 : delete > update set ft_grade=4
	//	wsprintf(cSqlQry, "DELETE FROM TB_USER1 WHERE FT_NAME = '%s' AND FT_ID = '%s'", asUserInfo1, asUserInfo3);
		//삭제하는 사용자
		//FT_GRADE='5'
		//FT_MEMO='0'
		//FT_LOGINDATE=삭제시간
		wsprintf(cSqlQry, "UPDATE TB_USER1 SET FT_GRADE='5', FT_MEMO='0', FT_LOGINDATE='%s' WHERE FT_NAME = '%s' AND FT_ID = '%s'", asNow, asUserInfo1, asUserInfo3);

		usRet = SQLExecDirect(frmSql->m_hStmt, (SQLCHAR *) cSqlQry, SQL_NTS);

		if ((usRet != SQL_SUCCESS) &&(usRet != SQL_SUCCESS_WITH_INFO)  && (usRet != SQL_NO_DATA)) {
			SQLCloseCursor(frmSql->m_hStmt);
			return;
		}

		memset(cSqlQry, 0, QRY_ARRANGE_SIZE);
		wsprintf(cSqlQry, "COMMIT");
		usRet = SQLExecDirect(frmSql->m_hStmt, (SQLCHAR *) cSqlQry, SQL_NTS);

		if ((usRet != SQL_SUCCESS) &&(usRet != SQL_SUCCESS_WITH_INFO)  && (usRet != SQL_NO_DATA))
		{
			SQLCloseCursor(frmSql->m_hStmt);
			return;
		}

		frmMsg->funcMessageDlg("정보 삭제 확인:", "정보 삭제가 완료 되었습니다.", 3);
		mvUserInfoList.clear();
		funListClear();
		funcReadUserInformation();
		funcListDisplay();

//230207//funcSetUserHistState()Param변경//
//		//210323//#PERSON_INFO//AnsiString asKindCode = eFunc->funcGetKindNameToKindCode(503, "휴면계정");//210305//#44710//12
//		AnsiString asKindCode = eFunc->funcGetKindNameToKindCode(503, "삭제계정");//210305//#44710//12
//		if( !asKindCode.IsEmpty() )
//			funcSetUserHistState(&mCurrentUser, asKindCode.ToInt(), 0);//휴면계정//190712
		funcSetUserHistState(&mCurrentUser, "삭제계정", 0);//휴면계정//190712
*/
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::IMGEXITMouseEnter(TObject *Sender)
{
	if(IMGEXIT->Enabled)
	{
		IMGEXIT->Picture->Bitmap->Handle  = NULL;
		IMGEXIT->Picture                  = NULL;
		IMGEXIT->Picture->Bitmap->Assign(BITMAP_BTN_EXIT[1]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::IMGEXITMouseLeave(TObject *Sender)
{
	if(IMGEXIT->Enabled)
	{
		IMGEXIT->Picture->Bitmap->Handle  = NULL;
		IMGEXIT->Picture                  = NULL;
		IMGEXIT->Picture->Bitmap->Assign(BITMAP_BTN_EXIT[0]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::IMGEXITClick(TObject *Sender)
{
	if(IMGEXIT->Enabled)
		Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::IMGLOGMouseEnter(TObject *Sender)
{
	if(IMGLOG->Enabled)
	{
		IMGLOG->Picture->Bitmap->Handle  = NULL;
		IMGLOG->Picture                  = NULL;
		IMGLOG->Picture->Bitmap->Assign(BITMAP_BTN_LOG[1]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::IMGLOGMouseLeave(TObject *Sender)
{
	if(IMGLOG->Enabled)
	{
		IMGLOG->Picture->Bitmap->Handle  = NULL;
		IMGLOG->Picture                  = NULL;
		IMGLOG->Picture->Bitmap->Assign(BITMAP_BTN_LOG[0]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::IMGLOGClick(TObject *Sender)
{
	if(IMGLOG->Enabled)
	{
		frmUserLogList->asSelectId = AnsiString(edtUserInfo3->Text);
		frmUserLogList->Tag = 1;
		frmUserLogList->Show();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::FormClose(TObject *Sender, TCloseAction &Action)
{
	edtName->Text	= "";//210323//#PERSON_INFO
	funcDeleteButtonImage();
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::IMGSAVESETTINGMouseEnter(TObject *Sender)
{
	if(IMGSAVESETTING->Enabled)
	{
		IMGSAVESETTING->Picture->Bitmap->Handle  = NULL;
		IMGSAVESETTING->Picture                  = NULL;
		IMGSAVESETTING->Picture->Bitmap->Assign(BITMAP_BTN_SAVESETTING[1]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::IMGSAVESETTINGMouseLeave(TObject *Sender)
{
	if(IMGSAVESETTING->Enabled)
	{
		IMGSAVESETTING->Picture->Bitmap->Handle  = NULL;
		IMGSAVESETTING->Picture                  = NULL;
		IMGSAVESETTING->Picture->Bitmap->Assign(BITMAP_BTN_SAVESETTING[0]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::IMGSAVESETTINGClick(TObject *Sender)
{
	if(IMGSAVESETTING->Enabled)
	{
		funcUserBSetting();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::IMGEXIT2MouseEnter(TObject *Sender)
{
	if(IMGEXIT2->Enabled)
	{
		IMGEXIT2->Picture->Bitmap->Handle  = NULL;
		IMGEXIT2->Picture                  = NULL;
		IMGEXIT2->Picture->Bitmap->Assign(BITMAP_BTN_EXIT[1]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::IMGEXIT2MouseLeave(TObject *Sender)
{
	if(IMGEXIT2->Enabled)
	{
		IMGEXIT2->Picture->Bitmap->Handle  = NULL;
		IMGEXIT2->Picture                  = NULL;
		IMGEXIT2->Picture->Bitmap->Assign(BITMAP_BTN_EXIT[0]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::IMGEXIT2Click(TObject *Sender)
{
	if(IMGEXIT2->Enabled)
		Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::btnCloseTypeBClick(TObject *Sender)
{
	if(IMGEXIT2->Enabled)
		Close();
}
//---------------------------------------------------------------------------

AnsiString __fastcall TfrmUserManagement::funcReadUserName(AnsiString _asId)
{
	if (frmSql->m_hStmt)		SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asName = "";
	SQLCHAR 	m_cVal[32+1];
	SQLINTEGER m_nVal;
	SQLRETURN 	ret;
	char 		min_cValue[32+1];

	SQLBindCol(frmSql->m_hStmt, 1,  SQL_C_CHAR, m_cVal, sizeof(m_cVal) , &m_nVal);

	char cSql[2048];
	memset(cSql, 0, sizeof(cSql));
	sprintf(cSql, "SELECT FT_NAME FROM TB_USER1 WHERE FT_ID = '%s'", _asId);

	ret = SQLPrepare(frmSql->m_hStmt, (SQLCHAR *)cSql, SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if ((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA))
	{
		SQLCloseCursor(frmSql->m_hStmt);
		return 0;
	}
	else {
		memset(m_cVal, 0x00, sizeof(m_cVal));

		while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA)
		{
			memset(min_cValue, 0x00, sizeof(min_cValue));
			memcpy(min_cValue, m_cVal, sizeof(min_cValue));
			asName = min_cValue;
		};
		if(frmSql->m_hStmt)
			SQLCloseCursor(frmSql->m_hStmt);
	}

	return asName;
}
//---------------------------------------------------------------------------
void __fastcall TfrmUserManagement::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(frmUserManagement->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------




//================================================================
// 사용자별 문서권한설정//
//================================================================
void __fastcall TfrmUserManagement::funcUserBSetting()
{
	//DB TB_USER1.FT_MEMO 값.
	//<일반사용자>는 관리자가 프로그램 실행해서 권한설정을 해줘야 함.

	int nIndex = 0;
	int nValue = 0;
	int nGrade = 0;
	AnsiString asUserId = "";

	for (int i = 0; i < lvUserBList->Items->Count; i++)
	{
		if (lvUserBList->Items->Item[i]->Checked) {
			nIndex = lvUserBList->Items->Item[i]->SubItems->Strings[0].ToInt();
			nValue = (nValue | (0x00000001 << nIndex));
		}
	}

	asUserId = mvUserInfoList[lstvUserListInfo->Selected->Caption.ToInt()-1].cId;
	nGrade   = StrToInt(mvUserInfoList[lstvUserListInfo->Selected->Caption.ToInt()-1].cGrade);

	if(asUserId == "")
	{
		frmMsg->funcMessageDlg("알림:", "로그인 계정정보를 확인해주세요.", 3);//들어올 일이 없지만 예외처리//
		return;
	}
	//
	funcSQLUpdateUserBInfo(nValue, asUserId);//(B)set
	frmMsg->funcMessageDlg("정보변경 완료:", "정보 변경이 완료 되었습니다.", 3);
}
//---------------------------------------------------------------------------

//1. (A) LANDARCHIVE_%시군%.ini [USE LAYER]
//2. (B) DB : update DB TB_USER1.FT_MDMO Value
int __fastcall TfrmUserManagement::funcGetUserBValue()
{
	int nValue = 0;
	for (int i = 1; i < DF_DOC_CNT; i++)
	{
		if (frmMain->INIINFO.B_DOCKIND[i]) {
			nValue = (nValue | (0x00000001 << i));
		}
	}
	return nValue;
}
// ---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::funcSetUserBValue(int _nValue)
{
	for (int i = 1; i < DF_DOC_CNT; i++)
	{
		frmMain->INIINFO.B_DOCKIND[i] 	= (_nValue >> i) & 0x00000001;
		frmMain->INIINFO.B_QRYCHECK[i] 	= (_nValue >> i) & 0x00000001;
		//231014//[오류]시군별구축문서설정:프로그램에서직접하지 않는다//frmMain->SIDOINI->WriteInteger("DOCKIND", frmMain->INIINFO.DOCKINDNAME[i], frmMain->INIINFO.B_DOCKIND[i]);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::btnFindClick(TObject *Sender)
{
	AnsiString  asStr	= edtName->Text;
	//210331//검색어 없으면 모두 표시//
//	if(asStr.IsEmpty())
//	{
//		frmMsg->funcMessageDlg("입력요청:", "검색하고자 하는 사용자명을 입력해주세요.", 3);
//		return;
//	}

	funListClear();
//	funcReadUserInformation();
	funcListDisplay();
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::edtFindKeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN)
	{
		if(Sender == edtName)
		{
            btnFindClick(btnFind);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserManagement::edtHangul_OnEnter(TObject *Sender)
{
	unsigned long Conversion, Sentence;
	HIMC Mode = ImmGetContext(Application->Handle);
	ImmGetConversionStatus(Mode, &Conversion, &Sentence);
	if (Conversion == IME_CMODE_HANGEUL) // 현재모드가 한글이면 패스
	;
	else // 현재모드가 한글이 아니면 한/영키 누른 효과를준다.
		ImmSetConversionStatus(Mode, IME_CMODE_HANGEUL, IME_CMODE_HANGEUL);
}
//---------------------------------------------------------------------------

