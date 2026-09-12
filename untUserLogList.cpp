#pragma link "bsPngImageList"
#pragma link "tmsAdvGridExcel"
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "BaseGrid"
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"

#pragma warn -8004
#pragma warn -8006

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmUserLogList *frmUserLogList;
//---------------------------------------------------------------------------
__fastcall TfrmUserLogList::TfrmUserLogList(TComponent* Owner)
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
		this->shpWait->Pen->Color		= (TColor)RGB(R, G, B);
		//panWindowsMove->Color//
		this->panWindowsMove->Color		= (TColor)RGB(R, G, B);
		//pnlWaitT->Color//
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::FormCreate(TObject *Sender)
{
	funcCreateLog();
	funcCreateHist();
	funcCreateDownload();//210305//#TB_COPY_DNLD//
	funcCreateGrade();//210331//#GRADELIST
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::FormShow(TObject *Sender)
{
	//210331//#GRADELIST
	if(frmMain->m_asParamStr2 == "SYSTEM_OK_ADMIN")
	{
		TabSheet4->Visible	= true;
	}
	else
	{
		TabSheet4->Visible	= false;
    }

	PageControl1->ActivePage	= TabSheet1;

	//---
	if(this->Tag == 1)
	{
		this->Left = frmUserManagement->Left + (frmUserManagement->Width - this->Width)/2;
		this->Top  = frmUserManagement->Top + (frmUserManagement->Height - this->Height)/2;
	}
	else if(this->Tag == 2)
	{
		this->Left = frmMain->Left + (frmMain->Width - this->Width)/2;
		this->Top  = frmMain->Top + (frmMain->Height - this->Height)/2;
	}

	funcLoadButtonImage();

	mvUserLogInfo.clear();
	mvUserHistInfo.clear();
	mvUserDownloadInfo.clear();
	mvUserGradeInfo.clear();//210331//#GRADELIST

	funListClear();

	if( m_nLogCount > 0)
		PageControl1->ActivePage	= TabSheet1;
	else if( m_nHistCount > 0)
		PageControl1->ActivePage	= TabSheet2;
	else if( m_nDownloadCount > 0)
		PageControl1->ActivePage	= TabSheet3;
	else if( m_nGradeCount > 0)//210331//#GRADELIST
		PageControl1->ActivePage	= TabSheet4;

	if(this->Tag == 2)//200421//관리자 로그인 시 메인화면에서 보여주기//
	{
		AnsiString asSttDt = (Now() - 90).FormatString("YYYY-MM");
		AnsiString asEndDt = Now().FormatString("YYYY-MM");
		dtSttMon->Text = asSttDt;
		dtEndMon->Text = asEndDt;
		chkDayOff->Checked = true;
		//220107//[DUP]chkDayOff->Checked시에 검색한다//IMGFINDClick(IMGFIND);
	}
	//=========================================================================
	//231014//사용자관리>로그인기록 : chkDayOff->Checked에 변함이 없어 IMGFINDClick동작하지 않아 기록 갱신 하지 않아서 기능추가//
	else
	{
		IMGFINDClick(NULL);
	}
	//=========================================================================
	//220107//로그기록 창 닫을 때, 오래 걸리는 이유가 종료할 때 아래 설정으로 재검색해서 문제발생//
//	else
//	{
//		chkDayOff->Checked	= false;
//		dtSttMon->Text	= "";
//		dtEndMon->Text	= "";
//		cboLog->ItemIndex	= 0;
//		if(cboAct->Items->Count > 0)
//			cboAct->ItemIndex = 0;
//		if(cboGrade->Items->Count > 0)
//			cboGrade->ItemIndex = 0;
//	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmUserLogList::funcSetWaitWindows(bool bSetValue)
{
	palWait->Left = (panCenter->Width - palWait->Width) / 2;
	palWait->Top  = (panCenter->Height - palWait->Height) / 2;

	if (this->palWait->Visible == !bSetValue)
	{
		palWait->Visible = bSetValue;

		if (bSetValue)		Screen->Cursor     = crHourGlass;
		else            	Screen->Cursor     = crDefault;

		if(!bSetValue)
		{
			lblWait1->Caption  = "잠시만 기다려 주세요.";
			lblWait2->Caption  = "선택 작업을 적용중입니다.";
		}
		else
		{
           	palWait->BringToFront();
        }
	}

	Application->ProcessMessages();
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::funListClear()
{
	//201105//
	funcInitLog();
	funcInitHist();
	funcInitDownload();//210305//#TB_COPY_DNLD//
	funcInitGrade();//210331//#GRADELIST
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::funcListDisplay()
{
	if(PageControl1->ActivePage	== TabSheet1)
	{
		funcDispHist();
		funcDispDownload();
		funcDispGrade();
		funcDispLog();
	}
	else if(PageControl1->ActivePage	== TabSheet2)
	{
		funcDispLog();
		funcDispDownload();
		funcDispGrade();
		funcDispHist();
	}
	else if(PageControl1->ActivePage	== TabSheet3)
	{
		funcDispLog();
		funcDispHist();
		funcDispGrade();
		funcDispDownload();
	}
	else if(PageControl1->ActivePage	== TabSheet4)
	{
		funcDispLog();
		funcDispHist();
		funcDispDownload();
		funcDispGrade();
	}
}
//---------------------------------------------------------------------------

//void __fastcall TfrmUserLogList::funcReadUserInformation()
//{
//	SQLCHAR 		m_cVal[4][255];
//	SQLINTEGER 		m_nVal[4];
//	UserLogInfo 	mUserLogInfo;
//
//	SQLHSTMT 		*phStmtSQL = NULL;
//	phStmtSQL = &frmSql->m_hStmt;
//
//	char		cSqlQry[QRY_ARRANGE_SIZE];
//
//	for (int i=0; i<4; i++) {
//		memset(&m_cVal[i][0], 0x00, sizeof(m_cVal[i]));
//		SQLBindCol(*phStmtSQL, i+1, SQL_C_CHAR, &m_cVal[i][0], sizeof(m_cVal[i]), &m_nVal[i]);
//	}
//
//	memset(cSqlQry, 0, sizeof(cSqlQry));
//	wsprintf(cSqlQry, "SELECT * FROM TB_USER2 WHERE FT_ID='%s'", frmUserManagement->func_base64Encode(asSelectId).c_str());
//
//	if (frmSql->func_QryProcess(phStmtSQL, cSqlQry) < 0){
//		return;
//	}
//	else {
//		for (int i=0; i<4; i++) {
//			memset(&m_cVal[i][0], 0x00, sizeof(m_cVal[i]));
//		}
//
//		mvUserLogInfo.clear();
//		while (SQLFetch(*phStmtSQL)!=SQL_NO_DATA)
//		{
//			memset(&mUserLogInfo, 0, sizeof(mUserLogInfo));
//
//			memcpy(mUserLogInfo.cId, m_cVal[0], sizeof(mUserLogInfo.cId));
//			wsprintf(mUserLogInfo.cIdDec, "%s", frmMain->func_Decoder(mUserLogInfo.cId));
//			memcpy(mUserLogInfo.cLoginDate, m_cVal[2], sizeof(mUserLogInfo.cLoginDate));
//			memcpy(mUserLogInfo.cLogoutDate, m_cVal[3], sizeof(mUserLogInfo.cLogoutDate));
//			mvUserLogInfo.push_back(mUserLogInfo);
//
//			for (int i=0; i<4; i++) {
//				memset(&m_cVal[i][0], 0x00, sizeof(m_cVal[i]));
//			}
//		};
//
//		if (frmSql->m_hStmt)
//			SQLCloseCursor(frmSql->m_hStmt);
//
//	}
//}
////---------------------------------------------------------------------------
//
//void __fastcall TfrmUserLogList::funcReadUserCmdInformation()
//{
//	SQLCHAR 		m_cVal[4][255];
//	SQLINTEGER 		m_nVal[4];
//	UserCmdInfo 	mUserCmdInfo;
//
//	SQLHSTMT 		*phStmtSQL = NULL;
//	phStmtSQL = &frmSql->m_hStmt;
//
//	char		cSqlQry[QRY_ARRANGE_SIZE];
//
//	for (int i=0; i<4; i++) {
//		memset(&m_cVal[i][0], 0x00, sizeof(m_cVal[i]));
//		SQLBindCol(*phStmtSQL, i+1, SQL_C_CHAR, &m_cVal[i][0], sizeof(m_cVal[i]), &m_nVal[i]);
//	}
//
//	memset(cSqlQry, 0, sizeof(cSqlQry));
//	wsprintf(cSqlQry, "SELECT * FROM TB_USER3 WHERE FT_ID='%s'", frmUserManagement->func_base64Encode(asSelectId).c_str());
//
//	if (frmSql->func_QryProcess(phStmtSQL, cSqlQry) < 0){
//		return;
//	}
//	else {
//		for (int i=0; i<4; i++) {
//			memset(&m_cVal[i][0], 0x00, sizeof(m_cVal[i]));
//		}
//
//		mvUserCmdInfo.clear();
//		while (SQLFetch(*phStmtSQL)!=SQL_NO_DATA)
//		{
//			memset(&mUserCmdInfo, 0, sizeof(mUserCmdInfo));
//
//			memcpy(mUserCmdInfo.cId, m_cVal[0], sizeof(mUserCmdInfo.cId));
//			wsprintf(mUserCmdInfo.cIdDec, "%s", frmMain->func_Decoder(mUserCmdInfo.cId));
//			memcpy(mUserCmdInfo.cPnu, m_cVal[2], sizeof(mUserCmdInfo.cPnu ));
//			memcpy(mUserCmdInfo.cDate, m_cVal[3], sizeof(mUserCmdInfo.cDate));
//			mvUserCmdInfo.push_back(mUserCmdInfo);
//
//			for (int i=0; i<4; i++) {
//				memset(&m_cVal[i][0], 0x00, sizeof(m_cVal[i]));
//			}
//		};
//
//		if (frmSql->m_hStmt)
//			SQLCloseCursor(frmSql->m_hStmt);
//
//	}
//}
////---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::funcReadUserLogInformation()
{
	if (frmSql->m_hStmt)		SQLCloseCursor(frmSql->m_hStmt);

	SQLCHAR 		m_cVal[5][255];//210104//IP추가//
	SQLINTEGER 		m_nVal[5];//210104//IP추가//
	UserLogInfo 	mUserLogInfo;
	AnsiString      mSqlCol 	= "";
	AnsiString      mSqlQryA 	= "";
	AnsiString      mSqlQryB 	= "";
	AnsiString      mSqlQryC 	= "";
	AnsiString      asSqlQry 	= "";
	AnsiString      asOrderBy 	= "ORDER BY FT_LOGIN";//210326//#503

	for (int i=0; i<5; i++) {//210104//IP추가//
		memset(&m_cVal[i][0], 0x00, sizeof(m_cVal[i]));
		SQLBindCol(frmSql->m_hStmt, i+1, SQL_C_CHAR, &m_cVal[i][0], sizeof(m_cVal[i]), &m_nVal[i]);
	}

	//선택한 사용자만//
//	memset(cSqlQry, 0, sizeof(cSqlQry));
//	wsprintf(cSqlQry, "SELECT FT_ID, FT_LOGIN, FT_LOGOUT  FROM TB_USER4 WHERE FT_ID='%s' AND (FT_ACTION=0 OR FT_ACTION=9)", asSelectId.c_str());

	//모든 사용자기록//
	mSqlQryA = "AND SUBSTR(FT_LOGIN, 1, 7) >= '" + dtSttMon->Text.Trim() + "' AND SUBSTR(FT_LOGIN, 1, 7)  <= '" + dtEndMon->Text.Trim() + "' ";
	mSqlQryB = "AND FT_ID != '" + frmMain->func_Encoder("admin") + "'";//'admin'제외//
	if(chkDayOff->Checked)
		mSqlQryC = "AND (SUBSTR(FT_LOGIN, 12, 2) < '09' or SUBSTR(FT_LOGIN, 12, 2) > '18') ";

	//---
	mSqlCol		= "FT_ID, FT_NAME, FT_IP, FT_LOGIN, FT_LOGOUT ";
	//---
	//220207//! 제거//asSqlQry	= "SELECT " + mSqlCol + "FROM TB_USER4 WHERE !(FT_ACTION=0 OR FT_ACTION=9) " + mSqlQryA + mSqlQryB + mSqlQryC + asOrderBy;
	asSqlQry	= "SELECT " + mSqlCol + "FROM TB_USER4 WHERE (FT_ACTION=0 OR FT_ACTION=9) " + mSqlQryA + mSqlQryB + mSqlQryC + asOrderBy;

	if (frmSql->func_QryProcess(asSqlQry.c_str()) < 0){
		return;
	}
	else {
		for (int i=0; i<4; i++) {
			memset(&m_cVal[i][0], 0x00, sizeof(m_cVal[i]));
		}

		mvUserLogInfo.clear();
		while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA)
		{
			memset(&mUserLogInfo, 0, sizeof(mUserLogInfo));

			memcpy(mUserLogInfo.cId, m_cVal[0], sizeof(mUserLogInfo.cId));
			wsprintf(mUserLogInfo.cIdDec, "%s", frmMain->func_Decoder(mUserLogInfo.cId));
			memcpy(mUserLogInfo.cName, m_cVal[1], sizeof(mUserLogInfo.cName));
			memcpy(mUserLogInfo.cIp, m_cVal[2], sizeof(mUserLogInfo.cIp));//210104//IP추가//
			wsprintf(mUserLogInfo.cIpDec, "%s", frmMain->func_Decoder(mUserLogInfo.cIp));
			memcpy(mUserLogInfo.cLoginDate, m_cVal[3], sizeof(mUserLogInfo.cLoginDate));
			memcpy(mUserLogInfo.cLogoutDate, m_cVal[4], sizeof(mUserLogInfo.cLogoutDate));
			mvUserLogInfo.push_back(mUserLogInfo);

			for (int i=0; i<5; i++) {//210104//IP추가//
				memset(&m_cVal[i][0], 0x00, sizeof(m_cVal[i]));
			}
		};

		if (frmSql->m_hStmt)		SQLCloseCursor(frmSql->m_hStmt);

	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::funcReadUserHistInformation()
{
	if (frmSql->m_hStmt)		SQLCloseCursor(frmSql->m_hStmt);

	SQLCHAR 		m_cVal[6][255];//210104//IP추가//
	SQLINTEGER 		m_nVal[6];//210104//IP추가//
	UserHistInfo 	mUserHistInfo;
	AnsiString      mSqlCol 	= "";
	AnsiString      mSqlQryA 	= "";
	AnsiString      mSqlQryB 	= "";
	AnsiString      mSqlQryC 	= "";
	AnsiString      mSqlQryD 	= "";
	AnsiString		asStr 		= "";
	AnsiString      asSqlQry 	= "";
	AnsiString      asOrderBy 	= "ORDER BY FT_ACTIONDATE";//210326//#503
	AnsiString		asTypeNm	= "";//210305//#44710//

	for (int i=0; i<6; i++) {//210104//IP추가//
		memset(&m_cVal[i][0], 0x00, sizeof(m_cVal[i]));
		SQLBindCol(frmSql->m_hStmt, i+1, SQL_C_CHAR, &m_cVal[i][0], sizeof(m_cVal[i]), &m_nVal[i]);
	}

	//선택한 사용자만//
//	memset(cSqlQry, 0, sizeof(cSqlQry));
//	wsprintf(cSqlQry, "SELECT FT_ID, FT_PNU, FT_ACTIONDATE FROM TB_USER4 WHERE FT_ID='%s' AND FT_ACTION=1", asSelectId.c_str());
	//모든 사용자기록//
	mSqlQryA = "AND SUBSTR(FT_ACTIONDATE, 1, 7) >= '" + dtSttMon->Text.Trim() + "' AND SUBSTR(FT_ACTIONDATE, 1, 7) <= '" + dtEndMon->Text.Trim() + "' ";
	mSqlQryB = "AND FT_ID != '" + frmMain->func_Encoder("admin") + "' ";//'admin'제외//
	if(chkDayOff->Checked)
	{
		mSqlQryC = "AND (SUBSTR(FT_ACTIONDATE, 12, 2) < '09' or SUBSTR(FT_ACTIONDATE, 12, 2) > '18') ";
	}
	mSqlQryD = "AND FT_ACTION != '7' AND FT_ACTION != '11' AND FT_ACTION != '12' AND FT_ACTION != '14' ";//파일저장, 권한변경, 휴면계정, 삭제계정 제외//

	//---
	mSqlCol		= "FT_ID, FT_NAME, FT_IP, FT_ACTION, FT_PNU, FT_ACTIONDATE ";
	//---
	asSqlQry	= "SELECT " + mSqlCol + "FROM TB_USER4 WHERE !(FT_ACTION=0 OR FT_ACTION=9) " + mSqlQryA + mSqlQryB + mSqlQryC + mSqlQryD + asOrderBy;

	if (frmSql->func_QryProcess(asSqlQry.c_str()) < 0){
		return;
	}
	else {
		for (int i=0; i<6; i++) {//210104//IP추가//
			memset(&m_cVal[i][0], 0x00, sizeof(m_cVal[i]));
		}

		mvUserHistInfo.clear();
		while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA)
		{
			asStr = "";
			memset(&mUserHistInfo, 0, sizeof(mUserHistInfo));

			memcpy(mUserHistInfo.cId, m_cVal[0], sizeof(mUserHistInfo.cId));
			wsprintf(mUserHistInfo.cIdDec, "%s", frmMain->func_Decoder(mUserHistInfo.cId));
			memcpy(mUserHistInfo.cName, m_cVal[1], sizeof(mUserHistInfo.cName ));
			memcpy(mUserHistInfo.cIp, m_cVal[2], sizeof(mUserHistInfo.cIp));//210104//IP추가//
			wsprintf(mUserHistInfo.cIpDec, "%s", frmMain->func_Decoder(mUserHistInfo.cIp));
			asStr = (char*)m_cVal[3];
			//===================================================================================
			//240923//관련해서 수정한 기록이 없는데 어째서 몇년동안 동작하지 않았음을 몰랐을까?//
			//===================================================================================
			if( !asStr.IsEmpty() )
				asStr.sprintf("%02d", asStr.ToInt());
			//===================================================================================

			//210305//#44710//
			asTypeNm	= eFunc->funcGetKindCodeToKindName(503, asStr.c_str());
			memcpy(mUserHistInfo.cActionName, asTypeNm.c_str(), sizeof(mUserHistInfo.cActionName));
			//210305//#44710//
//			mUserHistInfo.nAction = asStr.ToInt();
//			switch(mUserHistInfo.nAction)
//			{
//				case 1:		memcpy(mUserHistInfo.cActionName, "검색", 			sizeof(mUserHistInfo.cActionName));			break;
//				case 2:		memcpy(mUserHistInfo.cActionName, "수정", 			sizeof(mUserHistInfo.cActionName));			break;
//				case 3:		memcpy(mUserHistInfo.cActionName, "삭제", 			sizeof(mUserHistInfo.cActionName));			break;
//				case 4:		memcpy(mUserHistInfo.cActionName, "인쇄", 			sizeof(mUserHistInfo.cActionName));			break;
//				case 5:		memcpy(mUserHistInfo.cActionName, "문서열람", 		sizeof(mUserHistInfo.cActionName));			break;
//				case 6:		memcpy(mUserHistInfo.cActionName, "등록", 			sizeof(mUserHistInfo.cActionName));			break;
//				case 7:		memcpy(mUserHistInfo.cActionName, "파일저장", 		sizeof(mUserHistInfo.cActionName));			break;
//				case 8:		memcpy(mUserHistInfo.cActionName, "통계", 			sizeof(mUserHistInfo.cActionName));			break;
//				case 11:	memcpy(mUserHistInfo.cActionName, "권한변경", 		sizeof(mUserHistInfo.cActionName));			break;
//				case 12:	memcpy(mUserHistInfo.cActionName, "휴면계정", 		sizeof(mUserHistInfo.cActionName));			break;
//				case 13:	memcpy(mUserHistInfo.cActionName, "비밀번호변경", 	sizeof(mUserHistInfo.cActionName));			break;
//			}
			memcpy(mUserHistInfo.cPnu, m_cVal[4], sizeof(mUserHistInfo.cPnu ));
			memcpy(mUserHistInfo.cActionDate, m_cVal[5], sizeof(mUserHistInfo.cActionDate));
			mvUserHistInfo.push_back(mUserHistInfo);

			for (int i=0; i<6; i++) {
				memset(&m_cVal[i][0], 0x00, sizeof(m_cVal[i]));
			}
		};

		if (frmSql->m_hStmt)
			SQLCloseCursor(frmSql->m_hStmt);
	}
}
//---------------------------------------------------------------------------

//210305//#TB_COPY_DNLD//
void __fastcall TfrmUserLogList::funcReadUserDownloadInformation()
{
	if (frmSql->m_hStmt)		SQLCloseCursor(frmSql->m_hStmt);

	SQLCHAR 		m_cVal[6][255];
	SQLINTEGER 		m_nVal[6];
	UserDownloadInfo 	mUserDownloadInfo;
	AnsiString      mSqlCol 	= "";
	AnsiString      mSqlQryA 	= "";
	AnsiString      mSqlQryB 	= "";
	AnsiString      mSqlQryC 	= "";
	AnsiString		asStr 		= "";
	AnsiString      asSqlQry 	= "";
	AnsiString      asOrderBy 	= "ORDER BY FT_ACTIONDATE";
	AnsiString		asTypeNm	= "";//210305//#44710//

	for (int i=0; i<6; i++) {
		memset(&m_cVal[i][0], 0x00, sizeof(m_cVal[i]));
		SQLBindCol(frmSql->m_hStmt, i+1, SQL_C_CHAR, &m_cVal[i][0], sizeof(m_cVal[i]), &m_nVal[i]);
	}

	//모든 사용자기록//
	mSqlQryA = "SUBSTR(FT_ACTIONDATE, 1, 7) >= '" + dtSttMon->Text.Trim() + "' AND SUBSTR(FT_ACTIONDATE, 1, 7) <= '" + dtEndMon->Text.Trim() + "' ";
	mSqlQryB = "AND FT_ID != '" + frmMain->func_Encoder("admin") + "' ";//'admin'제외//
	if(chkDayOff->Checked)
		mSqlQryC = " AND (SUBSTR(FT_ACTIONDATE, 12, 2) < '09' or SUBSTR(FT_ACTIONDATE, 12, 2) > '18') ";

	//---
	mSqlCol		= "FT_ID, FT_NAME, FT_DOC, FT_KINDNAME, FT_REASON, FT_ACTIONDATE ";
	//---
	asSqlQry	= "SELECT " + mSqlCol + "FROM TB_COPY_DNLD WHERE " + mSqlQryA + mSqlQryB + asOrderBy;//210104//IP추가//
	if(chkDayOff->Checked)
		asSqlQry = asSqlQry + mSqlQryC;

	if (frmSql->func_QryProcess(asSqlQry.c_str()) < 0){
		return;
	}
	else {
		for (int i=0; i<6; i++) {//210104//IP추가//
			memset(&m_cVal[i][0], 0x00, sizeof(m_cVal[i]));
		}

		mvUserDownloadInfo.clear();
		while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA)
		{
			asStr = "";
			memset(&mUserDownloadInfo, 0, sizeof(mUserDownloadInfo));

			memcpy(mUserDownloadInfo.cId, m_cVal[0], sizeof(mUserDownloadInfo.cId));
			wsprintf(mUserDownloadInfo.cId, "%s", frmMain->func_Decoder(mUserDownloadInfo.cId));
			memcpy(mUserDownloadInfo.cName, m_cVal[1], sizeof(mUserDownloadInfo.cName ));
			asStr = (char*)m_cVal[2];
			if( !asStr.IsEmpty() )
				memcpy(mUserDownloadInfo.cDocName, frmMain->INIINFO.DOCKINDNAME[asStr.ToInt()].c_str(), sizeof(mUserDownloadInfo.cDocName));
			memcpy(mUserDownloadInfo.cKindName, m_cVal[3], sizeof(mUserDownloadInfo.cKindName));
			memcpy(mUserDownloadInfo.cReason, m_cVal[4], sizeof(mUserDownloadInfo.cReason));
			memcpy(mUserDownloadInfo.cActionDate, m_cVal[5], sizeof(mUserDownloadInfo.cActionDate));
			mvUserDownloadInfo.push_back(mUserDownloadInfo);

			for (int i=0; i<6; i++) {
				memset(&m_cVal[i][0], 0x00, sizeof(m_cVal[i]));
			}
		};

		if (frmSql->m_hStmt)
			SQLCloseCursor(frmSql->m_hStmt);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::funcReadUserGradeInformation()
{
	if (frmSql->m_hStmt)		SQLCloseCursor(frmSql->m_hStmt);

	SQLCHAR 		m_cVal[7][255];
	SQLINTEGER 		m_nVal[7];
	UserHistInfo 	mUserGradeInfo;
	AnsiString      mSqlCol 	= "";
	AnsiString      mSqlQryA 	= "";
	AnsiString      mSqlQryB 	= "";
	AnsiString      mSqlQryC 	= "";
	AnsiString      mSqlQryD 	= "";
	AnsiString		asStr 		= "";
	AnsiString      asSqlQry 	= "";
	AnsiString      asOrderBy 	= "ORDER BY FT_ACTIONDATE";
	AnsiString		asTypeNm	= "";//210305//#44710//

	for (int i=0; i<7; i++) {
		memset(&m_cVal[i][0], 0x00, sizeof(m_cVal[i]));
		SQLBindCol(frmSql->m_hStmt, i+1, SQL_C_CHAR, &m_cVal[i][0], sizeof(m_cVal[i]), &m_nVal[i]);
	}

	//모든 사용자기록//
	mSqlQryA = "AND SUBSTR(FT_ACTIONDATE, 1, 7) >= '" + dtSttMon->Text.Trim() + "' AND SUBSTR(FT_ACTIONDATE, 1, 7) <= '" + dtEndMon->Text.Trim() + "' ";
	mSqlQryB = "AND FT_ID != '" + frmMain->func_Encoder("admin") + "' ";//'admin'제외//
	if(chkDayOff->Checked)
	{
		mSqlQryC = "AND (SUBSTR(FT_ACTIONDATE, 12, 2) < '09' or SUBSTR(FT_ACTIONDATE, 12, 2) > '18') ";
	}
	mSqlQryD = "AND (FT_ACTION = '11' OR FT_ACTION = '12' OR FT_ACTION = '14') ";//권한변경, 휴면계정, 삭제계정//

	//---
	mSqlCol		= "FT_ID, FT_NAME, FT_IP, FT_ACTION, FT_PNU, FT_ACTIONDATE, FT_PATHNAME ";
	//---
	asSqlQry	= "SELECT " + mSqlCol + "FROM TB_USER4 WHERE !(FT_ACTION=0 OR FT_ACTION=9) " + mSqlQryA + mSqlQryB + mSqlQryC + mSqlQryD + asOrderBy;

	if (frmSql->func_QryProcess(asSqlQry.c_str()) < 0){
		return;
	}
	else {
		for (int i=0; i<7; i++) {//210104//IP추가//
			memset(&m_cVal[i][0], 0x00, sizeof(m_cVal[i]));
		}

		mvUserGradeInfo.clear();
		while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA)
		{
			asStr = "";
			memset(&mUserGradeInfo, 0, sizeof(mUserGradeInfo));

			memcpy(mUserGradeInfo.cId, m_cVal[0], sizeof(mUserGradeInfo.cId));
			wsprintf(mUserGradeInfo.cIdDec, "%s", frmMain->func_Decoder(mUserGradeInfo.cId));
			memcpy(mUserGradeInfo.cName, m_cVal[1], sizeof(mUserGradeInfo.cName ));
			memcpy(mUserGradeInfo.cIp, m_cVal[2], sizeof(mUserGradeInfo.cIp));//210104//IP추가//
			wsprintf(mUserGradeInfo.cIpDec, "%s", frmMain->func_Decoder(mUserGradeInfo.cIp));
			asStr = (char*)m_cVal[3];
			//210305//#44710//
			asTypeNm	= eFunc->funcGetKindCodeToKindName(503, asStr.c_str());
			memcpy(mUserGradeInfo.cActionName, asTypeNm.c_str(), sizeof(mUserGradeInfo.cActionName));
			//210305//#44710//
//			mUserGradeInfo.nAction = asStr.ToInt();
//			switch(mUserGradeInfo.nAction)
//			{
//				case 1:		memcpy(mUserGradeInfo.cActionName, "검색", 			sizeof(mUserGradeInfo.cActionName));			break;
//				case 2:		memcpy(mUserGradeInfo.cActionName, "수정", 			sizeof(mUserGradeInfo.cActionName));			break;
//				case 3:		memcpy(mUserGradeInfo.cActionName, "삭제", 			sizeof(mUserGradeInfo.cActionName));			break;
//				case 4:		memcpy(mUserGradeInfo.cActionName, "인쇄", 			sizeof(mUserGradeInfo.cActionName));			break;
//				case 5:		memcpy(mUserGradeInfo.cActionName, "문서열람", 		sizeof(mUserGradeInfo.cActionName));			break;
//				case 6:		memcpy(mUserGradeInfo.cActionName, "등록", 			sizeof(mUserGradeInfo.cActionName));			break;
//				case 7:		memcpy(mUserGradeInfo.cActionName, "파일저장", 		sizeof(mUserGradeInfo.cActionName));			break;
//				case 8:		memcpy(mUserGradeInfo.cActionName, "통계", 			sizeof(mUserGradeInfo.cActionName));			break;
//				case 11:	memcpy(mUserGradeInfo.cActionName, "권한변경", 		sizeof(mUserGradeInfo.cActionName));			break;
//				case 12:	memcpy(mUserGradeInfo.cActionName, "휴면계정", 		sizeof(mUserGradeInfo.cActionName));			break;
//				case 13:	memcpy(mUserGradeInfo.cActionName, "비밀번호변경", 	sizeof(mUserGradeInfo.cActionName));			break;
//			}
			memcpy(mUserGradeInfo.cPnu, m_cVal[4], sizeof(mUserGradeInfo.cPnu ));
			memcpy(mUserGradeInfo.cActionDate, m_cVal[5], sizeof(mUserGradeInfo.cActionDate));
			memcpy(mUserGradeInfo.cPathName, m_cVal[6], sizeof(mUserGradeInfo.cPathName));
			mvUserGradeInfo.push_back(mUserGradeInfo);

			for (int i=0; i<7; i++) {
				memset(&m_cVal[i][0], 0x00, sizeof(m_cVal[i]));
			}
		};

		if (frmSql->m_hStmt)
			SQLCloseCursor(frmSql->m_hStmt);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::funcSaveLogList()
{
//	UnicodeString sSheetName;
//
//	sSheetName = cbHowtoStat->Text + "_" + cbConditionStat->Text;
//	AnsiString sDate = DateToStr(StartDate->Date);
//	AnsiString eDate = DateToStr(EndDate->Date);
//	AnsiString sTemp = "";
//	AnsiString sSttT = "";
//	AnsiString sEndT = "";
//
////M
////	sDate = sDate.SubString(1,7);
////	eDate = eDate.SubString(1,7);
////
////	sDate = StringReplace(sDate, "-", "년 ", TReplaceFlags() << rfReplaceAll);
////	sDate = sDate + "월";
////
////	eDate = StringReplace(eDate, "-", "년 ", TReplaceFlags() << rfReplaceAll);
////	eDate = eDate + "월";
////
////	if(bsCbDateStat->Checked == true){
////		sSheetName = sSheetName + "_" + sDate + "~" + eDate;
////	}
//
//	//M
//	sTemp = sDate.SubString(1,4);
//	sSttT = sTemp + "년 ";
//	sTemp = sDate.SubString(6,2);
//	sSttT = sSttT + sTemp + "월 ";
//	sTemp = sDate.SubString(9,2);
//	sSttT = sSttT + sTemp + "일 ";
//
//	sTemp = eDate.SubString(1,4);
//	sEndT = sTemp + "년 ";
//	sTemp = eDate.SubString(6,2);
//	sEndT = sEndT + sTemp + "월 ";
//	sTemp = eDate.SubString(9,2);
//	sEndT = sEndT + sTemp + "일 ";
//
//	if(bsCbDateStat->Checked == true){
//		sSheetName = sSheetName + "_" + sSttT + "~" + sEndT;
//	}
//	//
//
//	SaveDialog1->FileName = "[지적행정ONESTOP]통계관리_" + sSheetName;
//	if(SaveDialog1->Execute()){
//		UnicodeString sFileName = SaveDialog1->FileName + ".xls";
//		AdvGridExcelIO2->XLSExport(sFileName,sSheetName,1,1,false);
//
//		AnsiString strMessage = "";
//		AnsiString lpszSaveFileName = ExtractFileName(sFileName);
//		//strMessage.sprintf( "저장 완료:\n\n'%s' 엑셀 파일 저장을 완료 하였습니다.\t\t\n", lpszSaveFileName.c_str() );
//		//func_MessageDlg( strMessage.c_str(), mtInformation, TMsgDlgButtons() << mbOK, 0);
//		strMessage.sprintf("'%s' 엑셀파일 저장을 완료하였습니다.", lpszSaveFileName.c_str() );
//		func_MessageDlg("저장 완료:", strMessage, 3);
//	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmUserLogList::funcLoadButtonImage()
{
	AnsiString asPath = frmMain->ROOTPATH + "RES\\MAIN\\";
	AnsiString filename = "";

	//Button Image
	for(int i = 0; i < 2; i++)
	{
		TPngImage *imgPng = new TPngImage();
		filename = asPath + "btnSave" + IntToStr(i) + ".png";
		imgPng->LoadFromFile(filename);
		BITMAP_BTN_SAVELOG[i] = new Graphics::TBitmap();
		BITMAP_BTN_SAVELOG[i]->Assign(imgPng);
		delete imgPng;
		imgPng = NULL;
		//
		imgPng = new TPngImage();
		filename = asPath + "btnExit" + IntToStr(i) + ".png";
		imgPng->LoadFromFile(filename);
		BITMAP_BTN_EXIT[i] = new Graphics::TBitmap();
		BITMAP_BTN_EXIT[i]->Assign(imgPng);
		delete imgPng;
		imgPng = NULL;
		//
		imgPng = new TPngImage();
		filename = asPath + "QbtnDetailFind" + IntToStr(i+1) + ".png";
		imgPng->LoadFromFile(filename);
		BITMAP_BTN_FIND[i] = new Graphics::TBitmap();
		BITMAP_BTN_FIND[i]->Assign(imgPng);
		delete imgPng;
		imgPng = NULL;
	}

	IMGSAVELOG->Picture->Bitmap->Assign(BITMAP_BTN_SAVELOG[0]);
	IMGEXIT->Picture->Bitmap->Assign(BITMAP_BTN_EXIT[0]);
	IMGFIND->Picture->Bitmap->Assign(BITMAP_BTN_FIND[0]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::funcDeleteButtonImage()
{
	for(int i = 0; i < 2; i++)
	{
		delete BITMAP_BTN_SAVELOG[i];
		BITMAP_BTN_SAVELOG[i] = NULL;
		delete BITMAP_BTN_EXIT[i];
		BITMAP_BTN_EXIT[i] = NULL;
		delete BITMAP_BTN_FIND[i];
		BITMAP_BTN_FIND[i] = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::IMGSAVELOGMouseEnter(TObject *Sender)
{
	IMGSAVELOG->Picture->Bitmap->Handle  = NULL;
	IMGSAVELOG->Picture                  = NULL;
	IMGSAVELOG->Picture->Bitmap->Assign(BITMAP_BTN_SAVELOG[1]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::IMGSAVELOGMouseLeave(TObject *Sender)
{
	IMGSAVELOG->Picture->Bitmap->Handle  = NULL;
	IMGSAVELOG->Picture                  = NULL;
	IMGSAVELOG->Picture->Bitmap->Assign(BITMAP_BTN_SAVELOG[0]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::IMGSAVELOGClick(TObject *Sender)
{
	bool	bStorable	= true;

	if(PageControl1->ActivePage == TabSheet1 && m_nLogCount == 0)
		bStorable	= false;
	else if(PageControl1->ActivePage == TabSheet2 && m_nHistCount == 0)
		bStorable	= false;
	else if(PageControl1->ActivePage == TabSheet3 && m_nDownloadCount == 0)
		bStorable	= false;
	else if(PageControl1->ActivePage == TabSheet4 && m_nGradeCount == 0)
		bStorable	= false;

	if( !bStorable )
	{
		frmMsg->funcMessageDlg("데이터부재 알림:", "저장할 데이터가 존재하지 않습니다.", 3);
		return;
	}

	//201105//
	UnicodeString sSheetName;

	//읍면동+리
	AnsiString 	asNow		= Now().FormatString("YYYYMMDD");
	AnsiString  asMsg		= "";

	sSheetName	= asNow;

	if(frmMain->m_asSaveFileDir.IsEmpty())
		SaveDialog1->InitialDir = frmMain->DOWNLOADPATH;
	else
		SaveDialog1->InitialDir = frmMain->m_asSaveFileDir;

	if(PageControl1->ActivePage == TabSheet1)
	{
		SaveDialog1->FileName = "로그인기록_" + sSheetName;
		if(SaveDialog1->Execute()){
			UnicodeString sFileName = SaveDialog1->FileName;// + ".xls";
			if(FileExists(sFileName))
			{
				asMsg	= "파일이 존재합니다. 덮어쓰시겠습니까?";
				frmMsg->funcMessageDlg("파일 중복 알림:", asMsg, 1);
				if(frmMsg->m_bClick == 1)//Yes
				{
					DeleteFile(SaveDialog1->FileName);
				}
				else
				{
					IMGSAVELOGClick(NULL);
					return;
				}
			}

			frmMain->m_asSaveFileDir = ExtractFilePath(SaveDialog1->FileName);

			AnsiString asSaveFileName = ExtractFileName(sFileName);

			AdvGridExcelIO1->XLSExport(sFileName, "로그인기록", 1, 1, false);

			asMsg.sprintf("'%s' 엑셀파일 저장을 완료하였습니다.", asSaveFileName.c_str() );
			frmMsg->funcMessageDlg("저장 완료:", asMsg, 3);
		}
	}
	else if(PageControl1->ActivePage == TabSheet2)
	{
		SaveDialog1->FileName = "작업기록_" + sSheetName;
		if(SaveDialog1->Execute()){
			UnicodeString sFileName = SaveDialog1->FileName;// + ".xls";
			if(FileExists(sFileName))
			{
				asMsg	= "파일이 존재합니다. 덮어쓰시겠습니까?";
				frmMsg->funcMessageDlg("파일 중복 알림:", asMsg, 1);
				if(frmMsg->m_bClick == 1)//Yes
				{
					DeleteFile(SaveDialog1->FileName);
				}
				else
				{
					IMGSAVELOGClick(NULL);
					return;
				}
			}

			frmMain->m_asSaveFileDir = ExtractFilePath(SaveDialog1->FileName);

			AnsiString asSaveFileName = ExtractFileName(sFileName);

			AdvGridExcelIO2->XLSExport(sFileName, "작업기록", 1, 1, false);

			asMsg.sprintf("'%s' 엑셀파일 저장을 완료하였습니다.", asSaveFileName.c_str() );
			frmMsg->funcMessageDlg("저장 완료:", asMsg, 3);
		}
	}
	else if(PageControl1->ActivePage == TabSheet3)//210305//#TB_COPY_DNLD//
	{
		SaveDialog1->FileName = "파일저장기록_" + sSheetName;
		if(SaveDialog1->Execute()){
			UnicodeString sFileName = SaveDialog1->FileName;// + ".xls";
			if(FileExists(sFileName))
			{
				asMsg	= "파일이 존재합니다. 덮어쓰시겠습니까?";
				frmMsg->funcMessageDlg("파일 중복 알림:", asMsg, 1);
				if(frmMsg->m_bClick == 1)//Yes
				{
					DeleteFile(SaveDialog1->FileName);
				}
				else
				{
					IMGSAVELOGClick(NULL);
					return;
				}
			}

			frmMain->m_asSaveFileDir = ExtractFilePath(SaveDialog1->FileName);

			AnsiString asSaveFileName = ExtractFileName(sFileName);

			AdvGridExcelIO3->XLSExport(sFileName, "파일저장기록", 1, 1, false);

			asMsg.sprintf("'%s' 엑셀파일 저장을 완료하였습니다.", asSaveFileName.c_str() );
			frmMsg->funcMessageDlg("저장 완료:", asMsg, 3);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::IMGEXITMouseEnter(TObject *Sender)
{
	IMGEXIT->Picture->Bitmap->Handle  = NULL;
	IMGEXIT->Picture                  = NULL;
	IMGEXIT->Picture->Bitmap->Assign(BITMAP_BTN_EXIT[1]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::IMGEXITMouseLeave(TObject *Sender)
{
	IMGEXIT->Picture->Bitmap->Handle  = NULL;
	IMGEXIT->Picture                  = NULL;
	IMGEXIT->Picture->Bitmap->Assign(BITMAP_BTN_EXIT[0]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::IMGEXITClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::FormClose(TObject *Sender, TCloseAction &Action)
{
	//220107//로그기록 창 닫을 때, 오래 걸리는 이유가 종료할 때 아래 설정으로 재검색해서 문제발생//
//	chkDayOff->Checked	= false;
//	dtSttMon->Text	= "";
//	dtEndMon->Text	= "";
//	cboLog->ItemIndex	= 0;
//	if(cboAct->Items->Count > 0)
//		cboAct->ItemIndex = 0;
//	if(cboGrade->Items->Count > 0)
//		cboGrade->ItemIndex = 0;

	funcDeleteButtonImage();
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::btnCloseTypeBClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::edtDate_OnKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if ((Key > 47 && Key < 58) || (Key > 95 && Key < 106) || Key == 8 || Key == 46);// 0~9, backspace, deletekey 예외
	else
		Key = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::edtDate_OnKeyPress(TObject *Sender, wchar_t &Key)

{
	if(Key == VK_RETURN)
	{
		if(Sender == dtSttMon)
			dtEndMon->SetFocus();
		else if(Sender == dtEndMon)
			IMGFINDClick(IMGFIND);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::edtDate_OnEnter(TObject *Sender)
{
	unsigned long Conversion, Sentence;
	HIMC Mode = ImmGetContext(Application->Handle);
	ImmGetConversionStatus(Mode, &Conversion, &Sentence);
	if (Conversion == IME_CMODE_ALPHANUMERIC) // 현재모드가 한글 아니면 패스
	;
	else // 현재모드가 한글이면 한/영키 누른 효과를준다.
		ImmSetConversionStatus(Mode, IME_CMODE_ALPHANUMERIC, IME_CMODE_ALPHANUMERIC);
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::edtDate_OnExit(TObject *Sender)
{
//	funcCheckDateKeyword(Sender);
}
//---------------------------------------------------------------------------

bool __fastcall TfrmUserLogList::funcCheckDateKeyword(TObject *Sender)
{
	if(Sender == dtSttMon)
	{
		if(dtSttMon->Text.Trim().Length() != 7 && !eFunc->funcCheckDate(dtSttMon->Text.Trim()) )
		{
			frmMsg->funcMessageDlg("입력값확인:", "시작월을 확인해주세요.", 3);
			dtSttMon->SetFocus();
			return false;
		}
	}
	else if(Sender == dtEndMon)
	{
		if(dtEndMon->Text.Trim().Length() != 7 && !eFunc->funcCheckDate(dtEndMon->Text.Trim()) )
		{
			frmMsg->funcMessageDlg("입력값확인:", "종료월을 확인해주세요.", 3);
			dtEndMon->SetFocus();
			return false;
		}
	}

	return true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::IMGFINDMouseEnter(TObject *Sender)
{
	IMGFIND->Picture->Bitmap->Handle  = NULL;
	IMGFIND->Picture                  = NULL;
	IMGFIND->Picture->Bitmap->Assign(BITMAP_BTN_FIND[1]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::IMGFINDMouseLeave(TObject *Sender)
{
	IMGFIND->Picture->Bitmap->Handle  = NULL;
	IMGFIND->Picture                  = NULL;
	IMGFIND->Picture->Bitmap->Assign(BITMAP_BTN_FIND[0]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::IMGFINDClick(TObject *Sender)
{
//
	if( !funcCheckDateKeyword(dtSttMon) )
		return;

	if( !funcCheckDateKeyword(dtEndMon) )
		return;

	if(dtSttMon->Text.Trim() > dtEndMon->Text.Trim())
	{
		frmMsg->funcMessageDlg("입력값확인:", "시작월을 종료월보다 작게 입력해주세요.", 3);
		return;
	}

	funcSetWaitWindows(true);//210326//#PERSON_INFO
	//
	funListClear();

	funcReadUserLogInformation();
	funcReadUserHistInformation();
	funcReadUserDownloadInformation();//210305//#TB_COPY_DNLD//
	funcReadUserGradeInformation();//210331//#GRADELIST

	funcListDisplay();

	funcSetWaitWindows(false);//210326//#PERSON_INFO
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(frmUserLogList->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::sgLogGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign, TVAlignment &VAlign)
{
	HAlign = taCenter;
	VAlign = vtaCenter;
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::sgHistGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign, TVAlignment &VAlign)
{
	HAlign = taCenter;
	VAlign = vtaCenter;
}
//---------------------------------------------------------------------------



//####################################################
//
// 로그인기록//
//
//####################################################
//Create UI
void __fastcall TfrmUserLogList::funcCreateLog()
{
	int nCol = 0; // M

	sgLog->DefaultColWidth     = 80;

	sgLog->ColCount    = 6;//210104//IP추가//5->6
	sgLog->RowCount    = 2;
	sgLog->FixedRows   = 1;
	sgLog->FixedCols   = 0;

	sgLog->Cells[nCol][0]      = "No";
	sgLog->ColWidths[nCol++]   = 0;//210111//44770//Req//텍스트가 짤려도 좋으니 수평스크롤 없이 한 화면에 캡처할 수 있게 요청//
	sgLog->Cells[nCol][0]      = "사용자ID";
	sgLog->ColWidths[nCol++]   = 120;
	sgLog->Cells[nCol][0]      = "사용자명";
	sgLog->ColWidths[nCol++]   = 120;

	//210104//IP추가//
	sgLog->Cells[nCol][0]      = "IP";
	sgLog->ColWidths[nCol++]   = 120;

	sgLog->Cells[nCol][0]      = "로그인시각";
	sgLog->ColWidths[nCol++]   = 150;
	sgLog->Cells[nCol][0]      = "로그아웃시각";
	sgLog->ColWidths[nCol++]   = 150;

	::UpdateWindow(sgLog->Handle);

}
// ---------------------------------------------------------------------------
//Init Data
void __fastcall TfrmUserLogList::funcInitLog()
{
	for (int i = 1; i < sgLog->RowCount; i++) {
		sgLog->Rows[i]->Clear();
	}

	sgLog->RowCount = 2;
}
// ---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::funcDispLog()
{
	funcInitLog();

	int nCol = 0;
	int nSize = (int)mvUserLogInfo.size();
	AnsiString asStr    = "";
	int nGrade	= 0;
	int			nIndex			= 1;//210326//#503//

//	//================================================
//	sgLog->LockUpdate	= true;
//	//================================================

	for (int i = 0; i < nSize; i++)
	{
		//==========================================================
		//210326//#503//조회조건 체크//
		if(cboLog->ItemIndex == 1)//관리자//
		{
			nGrade	= funcGetGradeFromUserId((char*)mvUserLogInfo[i].cIdDec);
			if(nGrade != 2)
				continue;
		}

		//==========================================================
		nCol	= 0;
		asStr	= "";
		//color
		sgLog->RowColor[nIndex] = clWhite;

        //NO//
		sgLog->Cells[nCol++][nIndex]  = nIndex;
		//사용자ID//
		sgLog->Cells[nCol++][nIndex]  = (char*)mvUserLogInfo[i].cIdDec;
		//사용자명//
		sgLog->Cells[nCol++][nIndex]  = (char*)mvUserLogInfo[i].cName;

		//210104//IP추가//
		//사용자IP//
		sgLog->Cells[nCol++][nIndex]  = (char*)mvUserLogInfo[i].cIpDec;

		//로그인시각//
//		sgLog->FontStyles[nCol][nIndex] = TFontStyles() << fsBold;
//		sgLog->FontColors[nCol][nIndex] = (TColor)RGB(0,0,255);
		sgLog->Cells[nCol++][nIndex]  = (char*)mvUserLogInfo[i].cLoginDate;
		//로그아웃시각//
//		sgLog->FontStyles[nCol][nIndex] = TFontStyles() << fsBold;
//		sgLog->FontColors[nCol][nIndex] = (TColor)RGB(0,0,255);
		sgLog->Cells[nCol++][nIndex] = (char*)mvUserLogInfo[i].cLogoutDate;
		nIndex++;

	}

//	//================================================
//	sgLog->AutoSizeColumns(true);
//	sgLog->LockUpdate	= false;
//	//================================================

	m_nLogCount	= nIndex - 1;

	if(nIndex > 1)
	{
		sgLog->Row = 1;
		sgLog->RowCount = nIndex;
	}

	//210326//#PERSON_INFO
	asStr	= FormatFloat("#,##0", m_nLogCount);
	pnlLogT->Caption    = " ▶ 로그인기록(" + asStr + "건)";
}
// ---------------------------------------------------------------------------


//####################################################
//
// 작업기록//
//
//####################################################
//Create UI
void __fastcall TfrmUserLogList::funcCreateHist()
{
	int nCol = 0; // M

	sgHist->DefaultColWidth     = 80;

	sgHist->ColCount    = 8;//210326//#503//7->8
	sgHist->RowCount    = 2;
	sgHist->FixedRows   = 1;
	sgHist->FixedCols   = 0;

	sgHist->Cells[nCol][0]      = "No";
	sgHist->ColWidths[nCol++]   = 0;//210111//44770//Req//텍스트가 짤려도 좋으니 수평스크롤 없이 한 화면에 캡처할 수 있게 요청//
	sgHist->Cells[nCol][0]      = "사용자ID";
	sgHist->ColWidths[nCol++]   = 100;//210104//120->100
	sgHist->Cells[nCol][0]      = "사용자명";
	sgHist->ColWidths[nCol++]   = 100;//210104//120->100
	sgHist->Cells[nCol][0]      = "IP";//210104//추가//44770//Req//
	sgHist->ColWidths[nCol++]   = 100;
	sgHist->Cells[nCol][0]      = "처리내용";
	sgHist->ColWidths[nCol++]   = 100;//210104//120->100
	sgHist->Cells[nCol][0]      = "토지소재지";
	sgHist->ColWidths[nCol++]   = 160;//210104//200->160
	sgHist->Cells[nCol][0]      = "처리일자";
	sgHist->ColWidths[nCol++]   = 130;//210104//200->160
	sgHist->Cells[nCol][0]      = "INDEX";//210326//#503//
	sgHist->ColWidths[nCol++]   = 0;//210326//#503//

	::UpdateWindow(sgHist->Handle);

}
// ---------------------------------------------------------------------------
//Init Data
void __fastcall TfrmUserLogList::funcInitHist()
{
	for (int i = 1; i < sgHist->RowCount; i++) {
		sgHist->Rows[i]->Clear();
	}

	sgHist->RowCount = 2;

	//200915//m_nMultiAIndex	= -1;
}
// ---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::funcDispHist()
{
	funcInitHist();

	int nCol = 0;
	int nSize = (int)mvUserHistInfo.size();
	AnsiString  asActionName	= "";//210326//#503//
	AnsiString 	asStr    		= "";
	int			nIndex			= 1;//210326//#503//

//	//================================================
	sgHist->LockUpdate	= true;
//	//================================================

	for (int i = 0; i < nSize; i++)
	{
		asActionName	= (char*)mvUserHistInfo[i].cActionName;

		//==========================================================
		//210326//#503//조회조건 체크//
		if(cboAct->ItemIndex > 0)
		{
			if(cboAct->Text != asActionName)
				continue;
		}
		else//조회조건이 '전체'이더라도 '권한변경', '휴면계정', '삭제계정'은 처리안함 //
		{
			if(asActionName == "권한변경" || asActionName == "휴면계정" || asActionName == "삭제계정")
            	continue;
		}

		//==========================================================
		nCol	= 0;
		asStr	= "";
		//color
		sgHist->RowColor[nIndex] = clWhite;

		//NO//
		sgHist->Cells[nCol++][nIndex]  	= nIndex;
		//사용자ID//
		sgHist->Cells[nCol++][nIndex]  	= (char*)mvUserHistInfo[i].cIdDec;
		//사용자명//
		sgHist->Cells[nCol++][nIndex]  	= (char*)mvUserHistInfo[i].cName;
		//IP//210104//IP추가//44770//Req//
		sgHist->Cells[nCol++][nIndex]  	= (char*)mvUserHistInfo[i].cIpDec;
		//처리내용//
		sgHist->FontStyles[nCol][nIndex] = TFontStyles() << fsBold;
		sgHist->FontColors[nCol][nIndex] = (TColor)RGB(0,0,255);
		sgHist->Cells[nCol++][nIndex]  	= asActionName;
		//토지소재지//
		sgHist->Cells[nCol++][nIndex] 	= eFunc->funcPnuToBonbuName2((char*)mvUserHistInfo[i].cPnu, 0);
		//처리일자//
		sgHist->Cells[nCol++][nIndex]  	= (char*)mvUserHistInfo[i].cActionDate;
		//INDEX
		sgHist->Cells[nCol++][nIndex]  	= i;
		nIndex++;
	}

//	//================================================
//	sgHist->AutoSizeColumns(true);
	sgHist->LockUpdate	= false;
//	//================================================

//	m_nHistCount	= nSize;
//
//	if(nSize > 0)
//	{
//		sgHist->Row = 1;
//		sgHist->RowCount = nSize + 1;
//	}

	m_nHistCount	= nIndex - 1;

	if(nIndex > 1)
	{
		sgHist->Row = 1;
		sgHist->RowCount = nIndex;
	}

	//210326//#PERSON_INFO
	asStr	= FormatFloat("#,##0", m_nHistCount);
	pnlHistT->Caption    = " ▶ 작업기록(" + asStr + "건)";
	//210326//#PERSON_INFO//pnlHistT->Caption    = " ▶ 작업기록(" + IntToStr(nSize) + "건)";
}
// ---------------------------------------------------------------------------


void __fastcall TfrmUserLogList::sgLogClickCell(TObject *Sender, int ARow, int ACol)
{
	if(ARow > 0)
	{
		//
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::sgHistClickCell(TObject *Sender, int ARow, int ACol)
{
	if(ARow > 0)
	{
		//
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::chkDayOffClick(TObject *Sender)
{
	if(this->Tag != 2)//240927//
		IMGFINDClick(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::sgDownloadClickCell(TObject *Sender, int ARow, int ACol)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::sgDownloadGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign, TVAlignment &VAlign)
{
	HAlign = taCenter;
	VAlign = vtaCenter;
}
//---------------------------------------------------------------------------
//####################################################
//
// 로그인기록//
//
//####################################################
//Create UI
void __fastcall TfrmUserLogList::funcCreateDownload()
{
	int nCol = 0; // M

	sgDownload->DefaultColWidth     = 80;

	sgDownload->ColCount    = 6;
	sgDownload->RowCount    = 2;
	sgDownload->FixedRows   = 1;
	sgDownload->FixedCols   = 0;

	sgDownload->Cells[nCol][0]      = "사용자ID";
	sgDownload->ColWidths[nCol++]   = 80;
	sgDownload->Cells[nCol][0]      = "사용자명";
	sgDownload->ColWidths[nCol++]   = 80;

	sgDownload->Cells[nCol][0]      = "문서명";
	sgDownload->ColWidths[nCol++]   = 110;
	sgDownload->Cells[nCol][0]      = "문서구분명";
	sgDownload->ColWidths[nCol++]   = 130;

	sgDownload->Cells[nCol][0]      = "다운로드사유";
	sgDownload->ColWidths[nCol++]   = 180;
	sgDownload->Cells[nCol][0]      = "처리일자";
	sgDownload->ColWidths[nCol++]   = 120;

	::UpdateWindow(sgDownload->Handle);

}
// ---------------------------------------------------------------------------
//Init Data
void __fastcall TfrmUserLogList::funcInitDownload()
{
	for (int i = 1; i < sgDownload->RowCount; i++) {
		sgDownload->Rows[i]->Clear();
	}

	sgDownload->RowCount = 2;
}
// ---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::funcDispDownload()
{
	funcInitDownload();

	int nCol = 0;
	int nSize = (int)mvUserDownloadInfo.size();
	AnsiString asStr    = "";

//	//================================================
//	sgDownload->LockUpdate	= true;
//	//================================================

	for (int i = 0; i < nSize; i++)
	{
		nCol	= 0;
		asStr	= "";
		//color
		sgDownload->RowColor[i+1] = clWhite;

		//사용자ID//
		sgDownload->Cells[nCol++][i+1]  = (char*)mvUserDownloadInfo[i].cId;
		//사용자명//
		sgDownload->Cells[nCol++][i+1]  = (char*)mvUserDownloadInfo[i].cName;

		//문서명//
		sgDownload->Cells[nCol++][i+1]  = (char*)mvUserDownloadInfo[i].cDocName;
		//문서구분명//
		sgDownload->Cells[nCol++][i+1]  = (char*)mvUserDownloadInfo[i].cKindName;

		//다운로드사유//
		sgDownload->FontStyles[nCol][i+1] = TFontStyles() << fsBold;
		sgDownload->FontColors[nCol][i+1] = (TColor)RGB(0,0,255);
		sgDownload->Cells[nCol++][i+1]  = (char*)mvUserDownloadInfo[i].cReason;
		//처리일자//
		sgDownload->Cells[nCol++][i+1] 	= (char*)mvUserDownloadInfo[i].cActionDate;
	}

//	//================================================
//	sgDownload->AutoSizeColumns(true);
//	sgDownload->LockUpdate	= false;
//	//================================================

	m_nDownloadCount	= nSize;

	if(nSize > 0)
	{
		sgDownload->Row = 1;
		sgDownload->RowCount = nSize + 1;
	}

	//210326//#PERSON_INFO
	asStr	= FormatFloat("#,##0", nSize);
	pnlDownloadT->Caption    = " ▶ 다운로드기록(" + asStr + "건)";
	//210326//#PERSON_INFO//pnlDownloadT->Caption    = " ▶ 다운로드기록(" + IntToStr(nSize) + "건)";
}
// ---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::cboActClick(TObject *Sender)
{
	funcSetWaitWindows(true);

	funcDispHist();

	funcSetWaitWindows(false);
}
//---------------------------------------------------------------------------



//####################################################
//
// 권한변경기록//
//
//####################################################
//Create UI
void __fastcall TfrmUserLogList::funcCreateGrade()
{
	int nCol = 0; // M

	sgGrade->DefaultColWidth     = 80;

	sgGrade->ColCount    = 9;
	sgGrade->RowCount    = 2;
	sgGrade->FixedRows   = 1;
	sgGrade->FixedCols   = 0;

	sgGrade->Cells[nCol][0]      = "No";
	sgGrade->ColWidths[nCol++]   = 0;
	sgGrade->Cells[nCol][0]      = "사용자ID";
	sgGrade->ColWidths[nCol++]   = 90;
	sgGrade->Cells[nCol][0]      = "사용자명";
	sgGrade->ColWidths[nCol++]   = 90;
	sgGrade->Cells[nCol][0]      = "IP";
	sgGrade->ColWidths[nCol++]   = 90;
	sgGrade->Cells[nCol][0]      = "처리내용";
	sgGrade->ColWidths[nCol++]   = 70;
	sgGrade->Cells[nCol][0]      = "승인자ID";
	sgGrade->ColWidths[nCol++]   = 90;
	sgGrade->Cells[nCol][0]      = "처리일자";
	sgGrade->ColWidths[nCol++]   = 120;
	sgGrade->Cells[nCol][0]      = "사유";
	sgGrade->ColWidths[nCol++]   = 140;//220208//100;
	sgGrade->Cells[nCol][0]      = "INDEX";
	sgGrade->ColWidths[nCol++]   = 0;

	::UpdateWindow(sgGrade->Handle);

}
// ---------------------------------------------------------------------------
//Init Data
void __fastcall TfrmUserLogList::funcInitGrade()
{
	for (int i = 1; i < sgGrade->RowCount; i++) {
		sgGrade->Rows[i]->Clear();
	}

	sgGrade->RowCount = 2;

	//200915//m_nMultiAIndex	= -1;
}
// ---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::funcDispGrade()
{
	funcInitGrade();

	int nCol = 0;
	int nSize = (int)mvUserGradeInfo.size();
	AnsiString  asActionName	= "";
	AnsiString 	asStr    		= "";
	int			nIndex			= 1;

//	//================================================
//	sgGrade->LockUpdate	= true;
//	//================================================

	for (int i = 0; i < nSize; i++)
	{
		asActionName	= (char*)mvUserGradeInfo[i].cActionName;

		//==========================================================
		//210326//#503//조회조건 체크//
		if(cboGrade->ItemIndex > 0)
		{
			if(cboGrade->Text != asActionName)
				continue;
		}
		else//조회조건이 '전체'이더라도 '권한변경', '휴면계정', '삭제계정'은 처리안함 //
		{
			if(asActionName != "권한변경" && asActionName != "휴면계정" && asActionName != "삭제계정")
            	continue;
		}

		//==========================================================
		nCol	= 0;
		asStr	= "";
		//color
		sgGrade->RowColor[nIndex] = clWhite;

		//NO//
		sgGrade->Cells[nCol++][nIndex]  = nIndex;
		//사용자ID//-권한변경대상ID
		asStr  = (char*)mvUserGradeInfo[i].cPnu;//220208//
		sgGrade->Cells[nCol++][nIndex]  = frmMain->func_Decoder(asStr);
		//사용자명//-권한변경대상 사용자명
		sgGrade->Cells[nCol++][nIndex]  = frmUserManagement->funcReadUserName(asStr);//220208//
		//IP//210104//IP추가//44770//Req//
		sgGrade->Cells[nCol++][nIndex]  = (char*)mvUserGradeInfo[i].cIpDec;
		//처리내용//
		sgGrade->Cells[nCol++][nIndex]  = asActionName;
		//승인자ID//
		sgGrade->Cells[nCol++][nIndex] 	= (char*)mvUserGradeInfo[i].cIdDec;
		//처리일자//
		sgGrade->Cells[nCol++][nIndex]  = (char*)mvUserGradeInfo[i].cActionDate;
		//승인사유//
		sgGrade->FontStyles[nCol][nIndex] = TFontStyles() << fsBold;
		sgGrade->FontColors[nCol][nIndex] = (TColor)RGB(0,0,255);
		sgGrade->Cells[nCol++][nIndex]  = (char*)mvUserGradeInfo[i].cPathName;
		//INDEX
		sgGrade->Cells[nCol++][nIndex]  = i;
		nIndex++;
	}

	m_nGradeCount	= nIndex - 1;

	if(nIndex > 1)
	{
		sgGrade->Row = 1;
		sgGrade->RowCount = nIndex;
	}

	//210326//#PERSON_INFO
	asStr	= FormatFloat("#,##0", m_nGradeCount);
	pnlGradeT->Caption    = " ▶ 권한변경기록(" + asStr + "건)";
}
// ---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::sgGradeGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign, TVAlignment &VAlign)
{
	HAlign = taCenter;
	VAlign = vtaCenter;
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::cboGradeClick(TObject *Sender)
{
	funcSetWaitWindows(true);

	funcDispGrade();

	funcSetWaitWindows(false);
}
//---------------------------------------------------------------------------

int __fastcall TfrmUserLogList::funcGetGradeFromUserId(AnsiString _asUserId)
{
	AnsiString  asStr	= "";
	int nGrade	= 0;
	int nSize	= (int)frmUserManagement->mvUserInfoList.size();

	if( _asUserId.IsEmpty() )
	{
		return 0;
    }

	if( _asUserId == "admin" )//210415//admin 관리자로 접근하도록//
	{
		nGrade	= 2;
		return nGrade;
    }

	for(int i = 0; i < nSize; i++)
	{
		if( strcmp(_asUserId.c_str(), frmUserManagement->mvUserInfoList[i].cIdDec) )
			continue;

		asStr	= frmUserManagement->mvUserInfoList[i].cGrade;
		if( !asStr.IsEmpty() && eFunc->IsNumberString(asStr))
			nGrade	= asStr.ToInt();
	}

	return nGrade;
}
//---------------------------------------------------------------------------
void __fastcall TfrmUserLogList::cboLogClick(TObject *Sender)
{
	funcSetWaitWindows(true);

	funcDispLog();

	funcSetWaitWindows(false);
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::PageControl1Changing(TObject *Sender, bool &AllowChange)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserLogList::PageControl1Change(TObject *Sender)
{
//	if(PageControl1->ActivePage	== TabSheet1)
//		funcDispLog();
//	else if(PageControl1->ActivePage	== TabSheet2)
//		funcDispHist();
//	else if(PageControl1->ActivePage	== TabSheet3)
//		funcDispDownload();
//	else if(PageControl1->ActivePage	== TabSheet4)
//		funcDispGrade();
}
//---------------------------------------------------------------------------

