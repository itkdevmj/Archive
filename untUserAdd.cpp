//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"

#pragma warn -8004

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmUserAdd *frmUserAdd;
//---------------------------------------------------------------------------
__fastcall TfrmUserAdd::TfrmUserAdd(TComponent* Owner)
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

void __fastcall TfrmUserAdd::FormShow(TObject *Sender)
{
	funcLoadButtonImage();

	b_Content_Change_flag = false;

	if (this->Tag == FORM_SHOW_MODE_RECORD) {
		//btnUserAdd->Enabled = true;
		IMGREGIST->Picture->Bitmap->Handle  = NULL;
		IMGREGIST->Picture                  = NULL;
		IMGREGIST->Picture->Bitmap->Assign(BITMAP_BTN_REGIST[0]);
		//btnUserModify->Enabled = false;
		IMGMODIFY->Enabled 					= false;//231014//버튼 비활성화 이미지면 상태로 변경해줘야지//
		IMGMODIFY->Picture->Bitmap->Handle  = NULL;
		IMGMODIFY->Picture                  = NULL;
		IMGMODIFY->Picture->Bitmap->Assign(BITMAP_BTN_MODIFY[2]);

		edtUserInfo3->Enabled = true;
		cboGrade->ItemIndex = 0;
		edtUserInfo1->Text = L"";
		edtUserInfo2->Text = func_GetLocalIP();
		edtUserInfo3->Text = L"";
		edtUserInfo4->Text = L"";
		edtUserInfo5->Text = L"";
		//210104//유지안함//'민원토지과'유지//
		edtUserInfo6->Text = L"";//210104//유지안함//
		edtUserInfo7->Text = L"";
		edtUserInfo8->Text = L"0";
		pnlTitle8->Visible 		= false;//사용자등록일때는 안보임//
		edtUserInfo8->Visible   = false;//사용자등록일때는 안보임//
		btnInitFailCut->Visible = false;//사용자등록일때는 안보임//
	}

	if (this->Tag == FORM_SHOW_MODE_MODIFY) {
		edtUserInfo3->Enabled 				= false;
		//btnUserAdd->Enabled = false;
		IMGREGIST->Enabled 					= false;
		IMGREGIST->Picture->Bitmap->Handle  = NULL;
		IMGREGIST->Picture                  = NULL;
		IMGREGIST->Picture->Bitmap->Assign(BITMAP_BTN_REGIST[2]);
		//btnUserModify->Enabled = true;
		IMGMODIFY->Enabled 					= true;
		IMGMODIFY->Picture->Bitmap->Handle  = NULL;
		IMGMODIFY->Picture                  = NULL;
		IMGMODIFY->Picture->Bitmap->Assign(BITMAP_BTN_MODIFY[0]);
		pnlTitle8->Visible 		= true;//사용자등록일때는 보임//
		edtUserInfo8->Visible 	= true;//사용자변경일때는 보임//
		btnInitFailCut->Visible = true;//사용자변경일때는 보임//
		int nGrade = StrToInt(frmUserManagement->mCurrentUser.cGrade);
		if(nGrade == 2)
			btnInitFailCut->Enabled = true;//관리자만 활성화//
		else
			btnInitFailCut->Enabled = false;//그외 비활성화//
	}

	pnlTitle6->Visible = true;
	edtUserInfo6->Visible = true;
}
//---------------------------------------------------------------------------



bool __fastcall TfrmUserAdd::funQueryUserId(AnsiString _asUserID)
{
	if (frmSql->m_hStmt)		SQLCloseCursor(frmSql->m_hStmt);

	bool bReturn = false;

	SQLCHAR 	m_cVal[255];
	SQLINTEGER 	m_nVal;
	SQLRETURN 	ret;
	char 		min_cValue[255];

	SQLBindCol(frmSql->m_hStmt, 1,  SQL_C_CHAR, m_cVal, sizeof(m_cVal) , &m_nVal);

	char cSql[2048];
	memset(cSql, 0, sizeof(cSql));
	sprintf(cSql, "SELECT FT_ID FROM TB_USER1 WHERE FT_ID = '%s'", _asUserID.c_str());//_cUserId);

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
			if(asValue.Length())
				bReturn = true;
		};
		if(frmSql->m_hStmt)
			SQLCloseCursor(frmSql->m_hStmt);
	}

	return bReturn;
}
//---------------------------------------------------------------------------

bool TfrmUserAdd::funCheckEditBox(int nType)
{
	switch(nType)
	{
		case 1:
			if (this->edtUserInfo1->Text.IsEmpty())
			{
				AnsiString strMsg = "사용자 이름정보가 존재하지 않습니다.";
				frmMsg->funcMessageDlg("입력 확인:", strMsg, 3);
				return false;
			}
			if (this->edtUserInfo2->Text.IsEmpty())
			{
				AnsiString strMsg = "사용자 IP정보가 존재하지 않습니다.";
				frmMsg->funcMessageDlg("입력 확인:", strMsg, 3);
				return false;
			}
			if (this->edtUserInfo3->Text.IsEmpty())
			{
				AnsiString strMsg = "사용자 ID정보가 존재하지 않습니다.";
				frmMsg->funcMessageDlg("입력 확인:", strMsg, 3);
				return false;
			}
			if (this->edtUserInfo4->Text.IsEmpty())
			{
				AnsiString strMsg = "사용자 비밀번호 정보가 존재하지 않습니다.";
				frmMsg->funcMessageDlg("입력 확인:", strMsg, 3);
				return false;
			}
			break;
		default:
			break;
	}
	return true;
}
//---------------------------------------------------------------------------

bool TfrmUserAdd::funCheckRePassWord()
{
	bool bReturnValue = false;
	if (edtUserInfo4->Text == edtUserInfo7->Text) bReturnValue = true;
	return bReturnValue;
}
//---------------------------------------------------------------------------

bool __fastcall TfrmUserAdd::func_checkPassWord()
{
	bool engcheck  = false;
	bool numcheck  = false;
	bool signcheck = false;
	bool result    = false;

	edtUserInfo4->Text = StringReplace(edtUserInfo4->Text, " ", "", TReplaceFlags()<<rfReplaceAll );
	if (edtUserInfo4->Text.Length() >= 9){
		AnsiString temp;
		for(int i=1; i<=edtUserInfo4->Text.Length(); i++){
			temp = edtUserInfo4->Text.SubString(i,1).UpperCase();
			if(engcheck == false){
				if(temp >= "A" && temp <= "Z") engcheck = true;
			}
			if(numcheck == false){
				if(temp >= "0" && temp <= "9") numcheck = true;
			}
			if(signcheck == false){
				if(temp >= "!" && temp <= "/") signcheck = true;
				else if(temp >= ":" && temp <= "@") signcheck = true;
				else if(temp >= "[" && temp <= "`") signcheck = true;
				else if(temp >= "{" && temp <= "~") signcheck = true;
			}
		}

		if(engcheck == true && numcheck == true && signcheck == true) result = true;
	}
	return result;
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserAdd::edtHangul_OnEnter(TObject *Sender)
{
	unsigned long Conversion, Sentence;
	HIMC Mode = ImmGetContext(Application->Handle);
	ImmGetConversionStatus(Mode, &Conversion, &Sentence);
	if (Conversion == IME_CMODE_HANGEUL) // 현재모드가 한글이면 패스
	;
	else // 현재모드가 한글이 아니면 한/영키 누른 효과를준다.
		ImmSetConversionStatus(Mode, IME_CMODE_HANGEUL, IME_CMODE_HANGEUL);
}
// ---------------------------------------------------------------------------

void __fastcall TfrmUserAdd::edtAlphaNumeric_OnEnter(TObject *Sender)
{
	unsigned long Conversion, Sentence;
	HIMC Mode = ImmGetContext(Application->Handle);
	ImmGetConversionStatus(Mode, &Conversion, &Sentence);
	if (Conversion == IME_CMODE_ALPHANUMERIC) // 현재모드가 영문/숫자이면 패스
	;
	else // 현재모드가 영문/숫자가 아니면 한/영키 누른 효과를준다.
		ImmSetConversionStatus(Mode, IME_CMODE_ALPHANUMERIC, IME_CMODE_ALPHANUMERIC);
}
//---------------------------------------------------------------------------

AnsiString __fastcall TfrmUserAdd::func_GetLocalIP()
{
	WSAData 	wsaData;
	char 		cSLocal[256];

	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
		return "";

	memset(cSLocal, 0, sizeof(cSLocal));
	if (gethostname(cSLocal, 256) == SOCKET_ERROR)
		return "";

	hostent *hos = gethostbyname(cSLocal);

	if (hos == NULL) return "";

	char *addr = *(hos->h_addr_list);

	AnsiString asLocalIP = AnsiString((unsigned char)addr[0]) + '.'
						 + AnsiString((unsigned char)addr[1]) + '.'
						 + AnsiString((unsigned char)addr[2]) + '.'
						 + AnsiString((unsigned char)addr[3]);
	WSACleanup();

	return asLocalIP;
}
//---------------------------------------------------------------------------
//200220//notused//
//int __fastcall TfrmUserAdd::funcGetUseLayerValue()
//{
//	int nValue = 0;
//	for (int i = 1; i < DF_DOC_CNT; i++)
//	{
//		if (frmIniControl->mIniStruct.bButtonLayer[i]) {
//			nValue = (nValue | (0x00000001 << i));
//		}
//	}
//
//	return nValue;
//}
////---------------------------------------------------------------------------


void __fastcall TfrmUserAdd::btnCloseTypeBClick(TObject *Sender)
{
	edtReason->Text	= "";//210323//#PERSON_INFO
	pnlGradeReason->Visible	= false;//210323//#PERSON_INFO
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserAdd::funcLoadButtonImage()
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
		if(i < 2)
		{
			imgPng = new TPngImage();
			filename = asPath + "btnExit" + IntToStr(i) + ".png";
			imgPng->LoadFromFile(filename);
			BITMAP_BTN_EXIT[i] = new Graphics::TBitmap();
			BITMAP_BTN_EXIT[i]->Assign(imgPng);
			delete imgPng;
			imgPng = NULL;
		}
	}

	IMGREGIST->Picture->Bitmap->Assign(BITMAP_BTN_REGIST[0]);
	IMGMODIFY->Picture->Bitmap->Assign(BITMAP_BTN_MODIFY[0]);
	IMGEXIT->Picture->Bitmap->Assign(BITMAP_BTN_EXIT[0]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserAdd::funcDeleteButtonImage()
{
	for(int i = 0; i < 3; i++)
	{
		delete BITMAP_BTN_REGIST[i];
		BITMAP_BTN_REGIST[i] = NULL;
		delete BITMAP_BTN_MODIFY[i];
		BITMAP_BTN_MODIFY[i] = NULL;
		if(i < 2)
		{
			delete BITMAP_BTN_EXIT[i];
			BITMAP_BTN_EXIT[i] = NULL;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserAdd::IMGREGISTMouseEnter(TObject *Sender)
{
	if(IMGREGIST->Enabled)
	{
		IMGREGIST->Picture->Bitmap->Handle  = NULL;
		IMGREGIST->Picture                  = NULL;
		IMGREGIST->Picture->Bitmap->Assign(BITMAP_BTN_REGIST[1]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserAdd::IMGREGISTMouseLeave(TObject *Sender)
{
	if(IMGREGIST->Enabled)
	{
		IMGREGIST->Picture->Bitmap->Handle  = NULL;
		IMGREGIST->Picture                  = NULL;
		IMGREGIST->Picture->Bitmap->Assign(BITMAP_BTN_REGIST[0]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserAdd::IMGREGISTClick(TObject *Sender)
{
	if(IMGREGIST->Enabled)
	{
		if(funQueryUserId(frmMain->func_Encoder(edtUserInfo3->Text)))
		{
			AnsiString strMsg = "사용중인 아이디입니다.";
			frmMsg->funcMessageDlg("아이디 중복 알림:", strMsg, 3);
			edtUserInfo3->SetFocus();
			return;
		}

		if(pnlGradeReason->Visible && edtReason->Text.Trim().IsEmpty())//210323//#PERSON_INFO
		{
			frmMsg->funcMessageDlg("입력 알림:", "권한변경 사유를 입력해주세요.", 3);
			return;
        }

		if (!funCheckEditBox(1)) { return; }

		if (!funCheckRePassWord()) {
			AnsiString strMsg = "암호정보가 잘못되었습니다.";
			frmMsg->funcMessageDlg("비밀번호 재입력 확인:", strMsg, 3);
			return;
		}

		if (func_checkPassWord() != true) {
			AnsiString strMsg = "암호는 숫자와 영문자, 특수기호등을 혼합하여 9자리 이상으로 권장합니다.";
			frmMsg->funcMessageDlg("비밀번호 권장 알림:", strMsg, 3);
			//권장사항//return;
		}

		AnsiString asColumnStr = "";
		AnsiString asValuesStr = "";
		SQLRETURN 	usRet;
		char		cSqlQry[QRY_ARRANGE_SIZE];
		SQLCHAR     SqlState[9], SQLStmt[100], Msg[SQL_MAX_MESSAGE_LENGTH];
		SQLINTEGER  NativeError;
		//SQLSMALLINT	i = 0;
		//SQLSMALLINT MsgLen = 0;
		memset(SqlState, 0, sizeof(SqlState));
		memset(SQLStmt, 0, sizeof(SQLStmt));
		memset(Msg, 0, sizeof(Msg));

		//Column
		asColumnStr = asColumnStr + "FT_NAME";
		asColumnStr = asColumnStr + ", FT_IP";
		asColumnStr = asColumnStr + ", FT_DEPART";
		asColumnStr = asColumnStr + ", FT_GRADE";
		asColumnStr = asColumnStr + ", FT_ID";
		asColumnStr = asColumnStr + ", FT_PW";
		asColumnStr = asColumnStr + ", FT_TEL";
		asColumnStr = asColumnStr + ", FT_MEMO";
		asColumnStr = asColumnStr + ", FT_FAILCUT";

		//Values
		asValuesStr = asValuesStr + "'" + edtUserInfo1->Text + "'";//NAME
		asValuesStr = asValuesStr + ", '" + frmMain->func_Encoder(AnsiString(edtUserInfo2->Text)) + "'";//IP
		asValuesStr = asValuesStr + ", '" + edtUserInfo6->Text.c_str() + "'";//DEPART
		asValuesStr = asValuesStr + ", " + IntToStr(cboGrade->ItemIndex);//GRADE
		asValuesStr = asValuesStr + ", '" + frmMain->func_Encoder(AnsiString(edtUserInfo3->Text)) + "'";//ID
		asValuesStr = asValuesStr + ", SHA2('" + frmMain->func_Encoder(AnsiString(edtUserInfo4->Text)) + "', 256)";//210303//#USER1_PW//PW
		asValuesStr = asValuesStr + ", '" + edtUserInfo5->Text.c_str() + "'";//TEL
		asValuesStr = asValuesStr + ", '262'";//1,2,8//IntToStr(funcGetUseLayerValue()) + "'";//"262";//Minji_#02_SetGrant//"A"//SETGRANT
		asValuesStr = asValuesStr + ", '" +
		asValuesStr = asValuesStr + ", '" + edtUserInfo8->Text.c_str() + "'";//FT_FAILCUT

		memset(cSqlQry, 0, QRY_ARRANGE_SIZE);
		wsprintf(cSqlQry, "INSERT INTO TB_USER1 (%s) values(%s)", asColumnStr, asValuesStr);

		usRet = SQLExecDirect(frmSql->m_hStmt, (SQLCHAR *) cSqlQry, SQL_NTS);
		if ((usRet != SQL_SUCCESS) &&(usRet != SQL_SUCCESS_WITH_INFO)  && (usRet != SQL_NO_DATA))
		{
			SQLCloseCursor(frmSql->m_hStmt);
			return;
		}

		memset(cSqlQry, 0, QRY_ARRANGE_SIZE);
		wsprintf(cSqlQry, "commit");
		usRet = SQLExecDirect(frmSql->m_hStmt, (SQLCHAR *) cSqlQry, SQL_NTS);

		if ((usRet != SQL_SUCCESS) &&(usRet != SQL_SUCCESS_WITH_INFO)  && (usRet != SQL_NO_DATA) )
		{
			SQLCloseCursor(frmSql->m_hStmt);
			return;
		}

		SQLCloseCursor(frmSql->m_hStmt);
		AnsiString strMsg = "사용자 정보의 추가를 완료 하였습니다.";
		frmMsg->funcMessageDlg("계정 추가 알림:", strMsg, 3);

        //210323//#PERSON_INFO
		if(cboGrade->ItemIndex > 0)
		{
//230207//funcSetUserHistState()Param변경//
//			AnsiString asKindCode = eFunc->funcGetKindNameToKindCode(503, "사용승인");
//			if( !asKindCode.IsEmpty() )
//				frmUserManagement->funcSetUserHistState(&frmUserManagement->mCurrentUser, asKindCode.ToInt(), 0);
			frmUserManagement->funcSetUserHistState(&frmUserManagement->mCurrentUser, "사용승인", 0);
		}

		frmUserManagement->mvUserInfoList.clear();
		frmUserManagement->funListClear();
		frmUserManagement->funcReadUserInformation();
		frmUserManagement->funcListDisplay();
		Close();
		return;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserAdd::IMGMODIFYMouseEnter(TObject *Sender)
{
	if(IMGMODIFY->Enabled)
	{
		IMGMODIFY->Picture->Bitmap->Handle  = NULL;
		IMGMODIFY->Picture                  = NULL;
		IMGMODIFY->Picture->Bitmap->Assign(BITMAP_BTN_MODIFY[1]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserAdd::IMGMODIFYMouseLeave(TObject *Sender)
{
	if(IMGMODIFY->Enabled)
	{
		IMGMODIFY->Picture->Bitmap->Handle  = NULL;
		IMGMODIFY->Picture                  = NULL;
		IMGMODIFY->Picture->Bitmap->Assign(BITMAP_BTN_MODIFY[0]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserAdd::IMGMODIFYClick(TObject *Sender)
{
	if(IMGMODIFY->Enabled)
	{
		if (!funCheckRePassWord()) {
			String sText    = L"암호정보가 잘못되었습니다.";
			String sCaption = L"페스워드 재입력 오류";
			Application->MessageBoxA(sText.w_str(), sCaption.c_str() ,0);
			return;
		}

		if(pnlGradeReason->Visible && edtReason->Text.Trim().IsEmpty())//210323//#PERSON_INFO
		{
			frmMsg->funcMessageDlg("입력 알림:", "권한변경 사유를 입력해주세요.", 3);
			return;
        }

		if (func_checkPassWord() != true) {
			String sText    = "암호는 숫자와 영문자, 특수기호등을 혼합하여 9자리 이상으로 권장합니다.";
			String sCaption = "사용자 정보 추가";
			Application->MessageBoxA(sText.w_str(), sCaption.c_str() ,0);
			//권장사항//return;
		}

		SQLRETURN 	usRet;
		char		cSqlQry[QRY_ARRANGE_SIZE];

		AnsiString	asUserInfo1 = edtUserInfo1->Text.c_str();//NAME
		AnsiString	asUserInfo2 = frmMain->func_Encoder(AnsiString(edtUserInfo2->Text));//IP
		AnsiString	asUserInfo3	= "";//220208//GRADE
		AnsiString	asUserInfo4 = frmMain->func_Encoder(AnsiString(edtUserInfo3->Text));//ID
		AnsiString	asUserInfo5 = frmMain->func_Encoder(AnsiString(edtUserInfo4->Text));//PW
		AnsiString	asUserInfo6	= edtUserInfo5->Text.c_str();//TEL
		AnsiString	asUserInfo7	= edtUserInfo6->Text.c_str();//DEPART
		AnsiString	asUserInfo8	= edtUserInfo8->Text.c_str();//FT_FAILCUT

		//GRADE
		if(cboGrade->ItemIndex > -1)
		{
			asUserInfo3	= IntToStr(cboGrade->ItemIndex);//GRADE
			//=====================================================
			//210326//#PERSON_INFO//비밀번호초기화(GRADE=9) 상태에서 이전 권한 백업을 cFailCut에 해둔다//
			if(m_bInitPassword)
			{
				asUserInfo8	= asUserInfo3;//220208//(char*)frmUserManagement->mCurrentUser.cGrade;//로그인사용자//
				asUserInfo3	= "9";
			}
			//=====================================================
		}

		//190906//사용자정보변경 후 문서권한 초기화되는 문제 수정//
		memset(cSqlQry, 0, QRY_ARRANGE_SIZE);
		//210303//#USER1_PW//

		if(asUserInfo5.IsEmpty())//210323//#PERSON_INFO
		{
			wsprintf(cSqlQry, "UPDATE TB_USER1 SET FT_NAME='%s', FT_IP='%s', FT_DEPART='%s', FT_GRADE='%s', FT_TEL='%s', FT_FAILCUT='%s' WHERE FT_ID='%s'",
								asUserInfo1.c_str(),
								asUserInfo2.c_str(),
								asUserInfo7.c_str(),
								asUserInfo3.c_str(),
								asUserInfo6.c_str(),
								asUserInfo8.c_str(),
								asUserInfo4.c_str());
		}
		else
		{
			wsprintf(cSqlQry, "UPDATE TB_USER1 SET FT_NAME='%s', FT_IP='%s', FT_DEPART='%s', FT_GRADE='%s', FT_PW=SHA2('%s', 256), FT_TEL='%s', FT_FAILCUT='%s' WHERE FT_ID='%s'",
								asUserInfo1.c_str(),
								asUserInfo2.c_str(),
								asUserInfo7.c_str(),
								asUserInfo3.c_str(),
								asUserInfo5.c_str(),
								asUserInfo6.c_str(),
								asUserInfo8.c_str(),
								asUserInfo4.c_str());
		}
		usRet = SQLExecDirect(frmSql->m_hStmt, (SQLCHAR *)cSqlQry, SQL_NTS);  // Return Value 100 : Non Search data.
		memset(cSqlQry, 0, QRY_ARRANGE_SIZE);
		if ((usRet != SQL_SUCCESS) &&(usRet != SQL_SUCCESS_WITH_INFO)  && (usRet != SQL_NO_DATA) ) {
			SQLCloseCursor(frmSql->m_hStmt);
			AnsiString strMsg = "데이터베이스 확인이 필요합니다. 제조사에 문의 바랍니다.";
			frmMsg->funcMessageDlg("DB 확인 요청:", strMsg, 3);
			return;
		}

		wsprintf(cSqlQry, "COMMIT");
		usRet = SQLExecDirect(frmSql->m_hStmt, (SQLCHAR *) cSqlQry, SQL_NTS);

		if ((usRet != SQL_SUCCESS) &&(usRet != SQL_SUCCESS_WITH_INFO)  && (usRet != SQL_NO_DATA))
		{
			SQLCloseCursor(frmSql->m_hStmt);
			return;
		}

		if (frmSql->m_hStmt)
			SQLCloseCursor(frmSql->m_hStmt);

		AnsiString strMsg = "정보 변경이 완료 되었습니다.";
		frmMsg->funcMessageDlg("정보변경 알림:", strMsg, 3);
		if(frmUserManagement->funUserGradeStrToInt(frmUserManagement->edtUserInfo6->Text) == 0 && cboGrade->ItemIndex > 0)//승인대기->변경
		{
//230207//funcSetUserHistState()Param변경//
//			AnsiString asKindCode = eFunc->funcGetKindNameToKindCode(503, "사용승인");
//			if( !asKindCode.IsEmpty() )
//				frmUserManagement->funcSetUserHistState(&frmUserManagement->mCurrentUser, asKindCode.ToInt(), 0);
			frmUserManagement->funcSetUserHistState(&frmUserManagement->mCurrentUser, "사용승인", 0);
		}
		else if(frmUserManagement->funUserGradeStrToInt(frmUserManagement->edtUserInfo6->Text) != cboGrade->ItemIndex)//승인대기->변경
		{
//230207//funcSetUserHistState()Param변경//
//			AnsiString asKindCode = eFunc->funcGetKindNameToKindCode(503, "권한변경");//210305//#44710//11
//			if( !asKindCode.IsEmpty() )
//				frmUserManagement->funcSetUserHistState(&frmUserManagement->mCurrentUser, asKindCode.ToInt(), 0);//권한변경//190712
			frmUserManagement->funcSetUserHistState(&frmUserManagement->mCurrentUser, "권한변경", 0);//권한변경//190712
		}
		frmUserManagement->funListClear();
		//Application->ProcessMessages();
		frmUserManagement->funcReadUserInformation();
		frmUserManagement->funcListDisplay();
		Close();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserAdd::IMGEXITMouseEnter(TObject *Sender)
{
	if(IMGEXIT->Enabled)
	{
		IMGEXIT->Picture->Bitmap->Handle  = NULL;
		IMGEXIT->Picture                  = NULL;
		IMGEXIT->Picture->Bitmap->Assign(BITMAP_BTN_EXIT[1]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserAdd::IMGEXITMouseLeave(TObject *Sender)
{
	if(IMGEXIT->Enabled)
	{
		IMGEXIT->Picture->Bitmap->Handle  = NULL;
		IMGEXIT->Picture                  = NULL;
		IMGEXIT->Picture->Bitmap->Assign(BITMAP_BTN_EXIT[0]);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserAdd::IMGEXITClick(TObject *Sender)
{
	edtReason->Text	= "";//210323//#PERSON_INFO
	pnlGradeReason->Visible	= false;//210323//#PERSON_INFO
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserAdd::FormClose(TObject *Sender, TCloseAction &Action)
{
	funcDeleteButtonImage();
}
//---------------------------------------------------------------------------


void __fastcall TfrmUserAdd::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(frmUserAdd->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserAdd::edtUserInfoKeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN)
	{
		if(Sender == edtUserInfo1)
		{
			edtUserInfo2->SetFocus();
		}
		else if(Sender == edtUserInfo2)
		{
			cboGrade->SetFocus();
		}
		else if(Sender == cboGrade)
		{
			edtUserInfo3->SetFocus();
		}
		else if(Sender == edtUserInfo3)
		{
			edtUserInfo4->SetFocus();
		}
		else if(Sender == edtUserInfo4)
		{
			edtUserInfo5->SetFocus();
		}
		else if(Sender == edtUserInfo5)
		{
			edtUserInfo6->SetFocus();
		}
		else if(Sender == edtUserInfo6)
		{
			edtUserInfo7->SetFocus();
		}
		else if(Sender == edtUserInfo7)
		{
			btnInitFailCutClick(btnInitFailCut);
		}
		else if(Sender == btnInitFailCut)
		{
			IMGREGISTClick(IMGREGIST);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserAdd::btnInitFailCutClick(TObject *Sender)
{
	edtUserInfo8->Text  = "0";
	strcpy(frmUserManagement->mCurrentUser.cFailCut, (char*)IntToStr(cboGrade->ItemIndex).c_str());
	//220208//cboGrade->ItemIndex	= 5;//비밀번호초기화//
	cboGrade->Enabled	= false;//220208//
	//=====================================================
	//210326//#PERSON_INFO
	m_bInitPassword	= true;
	edtUserInfo4->Text	= frmMain->_SIDOCODE;
	edtUserInfo7->Text	= frmMain->_SIDOCODE;
	//=====================================================
}
//---------------------------------------------------------------------------
//210323//#PERSON_INFO
void __fastcall TfrmUserAdd::cboGradeClick(TObject *Sender)
{
	int nGrade = frmUserManagement->funUserGradeStrToInt(frmUserManagement->edtUserInfo6->Text);// GRADE//231012//frmUserManagement-> 추가[component.mistake]
	if(/*cboGrade->Text != "휴면사용자" && */nGrade != cboGrade->ItemIndex)//사유입력//
	{
		pnlGradeReason->Visible	= true;
		edtReason->SetFocus();
	}
	else
	{
		pnlGradeReason->Visible	= false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserAdd::edtReasonKeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN)
	{
		if(edtReason->Text.Trim().IsEmpty())
		{
            frmMsg->funcMessageDlg("입력 요청:", "권한변경 사유를 입력해주세요.", 3);
			return;
		}

		if(edtUserInfo3->Enabled)
			edtUserInfo3->SetFocus();
		else
			edtUserInfo5->SetFocus();
	}
}
//---------------------------------------------------------------------------

