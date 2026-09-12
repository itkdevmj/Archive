//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "BaseGrid"
#pragma resource "*.dfm"


#pragma warn -8004


TfrmAttach *frmAttach;
//---------------------------------------------------------------------------
__fastcall TfrmAttach::TfrmAttach(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmAttach::FormCreate(TObject *Sender)
{
	funcCreateAttach();
}
//---------------------------------------------------------------------------
void __fastcall TfrmAttach::FormShow(TObject *Sender)
{
	this->Left = frmLMReq->Left + (frmLMReq->Width - this->Width) / 2;
	this->Top  = frmLMReq->Top + (frmLMReq->Height - this->Height) / 2;

	DragAcceptFiles(Handle,true); //drag&drop use
	ChangeWindowMessageFilterEx(Handle, WM_DROPFILES, MSGFLT_ALLOW, NULL); //drag&drop use when admin mode
	ChangeWindowMessageFilterEx(Handle, 0x0049, MSGFLT_ALLOW, NULL);

	m_nSelectGridIndex = 0;
	funcCreateAttach();

	funcLoadButtonImage();

	funcInitAttach();

	cboKindCode->Visible = false;
	cboKindCode->Clear();
	funcSetComboList();

	//<처리완료> 후에도 <파일첨부>를 하는 경우도 있어 기능 해제//
//	// setting button//RESULT = 0(삭제), 1(임시저장), 2(처리완료), 3(처리완료&ONESTOP이관)
//	if (frmLMReq->m_vLMBASICINFO[0].RESULT >= 2)//220218//COPY_LMREQ_TO_ONESTOP // 승인저장 상태에서는 <임시저장>, <저장완료> 버튼 비활성 처리한다.
//		btnUpload->Enabled	= false;
//	else
//    	btnUpload->Enabled	= false;

	//DB 데이터 가져오기//
	try{
		frmSql->funcDownloadAttach();
	}
	__finally{
		funcDispAttach();
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmAttach::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (DirectoryExists(frmMain->TEMPPATH))//temp 하위 파일들 삭제하기
		eFunc->funcDeleteDir(true, frmMain->TEMPPATH);

	cboKindCode->Visible = false;
	funcDeleteButtonImage();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAttach::funcRefreshShow()
{
	//<처리완료> 후에도 <파일첨부>를 하는 경우도 있어 기능 해제//
//	// setting button//RESULT = 0(삭제), 1(임시저장), 2(처리완료), 3(처리완료&ONESTOP이관)
//	if (frmLMReq->m_vLMBASICINFO[0].RESULT >= 2)//220218//COPY_LMREQ_TO_ONESTOP // 승인저장 상태에서는 <임시저장>, <저장완료> 버튼 비활성 처리한다.
//		btnUpload->Enabled	= false;
//	else
//		btnUpload->Enabled	= false;

	cboKindCode->Visible = false;
	//DB 데이터 가져오기//
	frmSql->funcDownloadAttach();

	funcDispAttach();
}
//---------------------------------------------------------------------------


void __fastcall TfrmAttach::funcLoadButtonImage()
{
	AnsiString filename = "";
	TPngImage *imgPng;

	try{
		//------------------------------------------------------
		//DELETE
		imgPng = new TPngImage();
		filename = frmMain->IMAGEMAINPATH + "btnDel.png";
		imgPng->LoadFromFile(filename);
		BITMAP_BTN_DEL 	= new Graphics::TBitmap();
		BITMAP_BTN_DEL->Assign(imgPng);
		delete imgPng;
		imgPng = NULL;
	}
	catch (Exception &exception)
	{
		Application->Terminate();
		return;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAttach::funcDeleteButtonImage()
{
	delete BITMAP_BTN_DEL;
	BITMAP_BTN_DEL = NULL;
}
//---------------------------------------------------------------------------

//=======================================================================================
//	파일첨부//
//=======================================================================================
//Create UI
void __fastcall TfrmAttach::funcCreateAttach()
{
	int nCol = 0; // M

	//sgAttach->FixedFont->Color   = (TColor)RGB(111, 111, 111);
	//sgAttach->FixedColor         = (TColor)RGB(221,232,254);//clInfoBk;
	sgAttach->DefaultColWidth    = 80;

	sgAttach->ColCount   = 7;
	sgAttach->RowCount   = 2;
	sgAttach->FixedRows  = 1;
	sgAttach->FixedCols  = 0;

	sgAttach->Cells[nCol][0]     = "삭제";
	sgAttach->ColWidths[nCol++]  = 30;
	sgAttach->Cells[nCol][0]     = "문서명";
	sgAttach->ColWidths[nCol++]  = 160;
	sgAttach->Cells[nCol][0]     = "파일명";
	sgAttach->ColWidths[nCol++]  = 400;
	sgAttach->Cells[nCol][0]     = "파일경로";
	sgAttach->ColWidths[nCol++]  = 0;
	sgAttach->Cells[nCol][0]     = "파일크기";
	sgAttach->ColWidths[nCol++]  = 0;
	sgAttach->Cells[nCol][0]     = "SEQNO";
	sgAttach->ColWidths[nCol++]  = 0;
	sgAttach->Cells[nCol][0]     = "KIND_CODE";
	sgAttach->ColWidths[nCol++]  = 0;

	::UpdateWindow(sgAttach->Handle);

	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < sgAttach->ColCount; j++) {
			sgAttach->Colors[j][i] = (TColor)RGB(229,241,251);//clInfoBk;
		}
	}
}
// ---------------------------------------------------------------------------
//Init Data
void __fastcall TfrmAttach::funcInitAttach()
{
	for (int i = 1; i < sgAttach->RowCount; i++) {
		sgAttach->Rows[i]->Clear();
	}

	sgAttach->RowCount = 2;

	pnlAttachT->Caption = "  첨부파일목록";

	for (int i = 0; i < 1; i++)
		for (int j = 0; j < sgAttach->ColCount; j++)
			sgAttach->Colors[j][i] = (TColor)RGB(229,241,251);//clInfoBk;
}
// ---------------------------------------------------------------------------
//Display Data
void __fastcall TfrmAttach::funcDispAttach()
{
	int nCount 	= 0;
	int index 	= 1;
	int nCol 	= 0;
	int nSize 	= (int)frmSql->m_vLMREQ_ATTACH.size();
	AnsiString 	asStr    = "";
	AnsiString 	asFileName = "";
	AnsiString 	asPathName = "";
	int			nSeqNo		= 0;

	if(nSize > 0)   sgAttach->RowCount = nSize + 1;
	else    		sgAttach->RowCount = 1;

	if(nSize > 0)
		frmLMReq->bWritingMode	= true;

	//================================================
	sgAttach->LockUpdate	= true;
	//================================================

	for (int i = 0; i < nSize; i++)
	{
		//
		nCol    = 0;
		asStr   = "";

//        //color
//		if(index % 2 == 0) sgAttach->RowColor[index] = (TColor)RGB(229,241,251);//(224,243,254);
//		else sgAttach->RowColor[index] = clWhite;

		//DELETE BUTTON
		sgAttach->AddBitmap(nCol++, index, BITMAP_BTN_DEL, false, haCenter, vaCenter);
		//KIND_CODE//문서구분//
		sgAttach->Cells[nCol++][index]  = eFunc->funcGetKindCodeToKindName(1, (char*)frmSql->m_vLMREQ_ATTACH[i].KIND_CODE);//201214//4->1
		//FILE_NAME
		asFileName	= frmSql->m_vLMREQ_ATTACH[i].FILE_NAME;
		sgAttach->Cells[2][index] = asFileName;
		//PATH_NAME
		nSeqNo       = frmSql->m_vLMREQ_ATTACH[i].SEQNO;
		asPathName = frmMain->TEMPPATH + IntToStr(nSeqNo) + "_" + asFileName;
		sgAttach->Cells[3][index] = asPathName;
		//FILE_SIZE
		sgAttach->Cells[4][index] = IntToStr(frmSql->m_vLMREQ_ATTACH[i].FILE_SIZE);
		//SEQNO
		sgAttach->Cells[5][index] = IntToStr(frmSql->m_vLMREQ_ATTACH[i].SEQNO);
		//SEQNO
		sgAttach->Cells[6][index] = (char*)frmSql->m_vLMREQ_ATTACH[i].KIND_CODE;

		index++;
	}

	//================================================
	sgAttach->AutoSizeColumns(true);
	sgAttach->LockUpdate	= false;
	sgAttach->ColWidths[0]  = 30;
	sgAttach->ColWidths[1]  = 160;
	if(nSize == 0)
		sgAttach->ColWidths[2]  = 400;
	sgAttach->ColWidths[3]  = 0;
	sgAttach->ColWidths[4]  = 0;
	sgAttach->ColWidths[5]  = 0;
	sgAttach->ColWidths[6]  = 0;
	//================================================

	m_nAttachCount	= nSize;

	funcUpdateAttachCount();
}
// ---------------------------------------------------------------------------

void __fastcall TfrmAttach::WMDropFiles(TWMDropFiles &message)
{
	char fullPath[MAX_PATH];
	UINT fileCount 			= DragQueryFile((HDROP)message.Drop,0xffffffff,NULL,0); //Count draged file
	AnsiString asFullPath 	= "";
	AnsiString asFilePath 	= "";
	AnsiString asFileName 	= "";
	AnsiString asDocName  	= "";
	int nOldCount 			= 0;

//	if(m_nAttachCount == 0)
//		nOldCount = sgAttach->RowCount - 2;
//	else
		nOldCount = sgAttach->RowCount - 1;

//	if(_SELECTROWINDEX < 2)
//	{
//		AnsiString strMessage = "첨부파일을 등록할 접수번호를 조회목록에서 선택해주세요.";
//		frmMsg->funcMessageDlg("파일등록 접수번호 선택 :", strMessage, 3);
//		return;
//    }

	//================================================
	sgAttach->LockUpdate	= true;
	//================================================

	//sgAttach->RowCount = 1 + nOldCount + fileCount;
	for(UINT i = nOldCount; i < nOldCount + fileCount; i++)
	{
		DragQueryFile((HDROP)message.Drop, i - nOldCount, fullPath, MAX_PATH);
		if(FileExists(fullPath))                          // if draged file is file
		{
			DWORD dwFileSize = 0;

			asFullPath = fullPath;
			dwFileSize = eFunc->func_GetLength(asFullPath);

			asFilePath = ExtractFilePath(asFullPath);
			asFileName = ExtractFileName(asFullPath);
			sgAttach->AddBitmap(0, i+1, BITMAP_BTN_DEL, false, haCenter, vaCenter);
			sgAttach->Cells[1][i+1] = asDocName;
			sgAttach->Cells[2][i+1] = asFileName;
			sgAttach->Cells[3][i+1] = fullPath;
			sgAttach->Cells[4][i+1] = dwFileSize;
			sgAttach->Cells[5][i+1] = "";//SEQNO
			sgAttach->Cells[6][i+1] = "";//DOC.KIND_CODE
		}
		else continue;
	}

	sgAttach->RowCount = nOldCount + fileCount + 1;

	funcUpdateAttachCount();

//	sgAttach->RowCount = nOldCount + fileCount + 2;
//	sgAttach->Cells[2][nOldCount + fileCount + 1] = "";
//	sgAttach->Cells[3][nOldCount + fileCount + 1] = "";
//	sgAttach->Cells[4][nOldCount + fileCount + 1] = "";
//	sgAttach->Cells[5][nOldCount + fileCount + 1] = "";
//	sgAttach->Cells[6][nOldCount + fileCount + 1] = "";
	DragFinish((HDROP)message.Drop);

	//================================================
	sgAttach->AutoSizeColumns(true);
	sgAttach->LockUpdate	= false;
	sgAttach->ColWidths[0]  = 30;
	sgAttach->ColWidths[1]  = 160;
	sgAttach->ColWidths[3]  = 0;
	sgAttach->ColWidths[4]  = 0;
	sgAttach->ColWidths[5]  = 0;
	sgAttach->ColWidths[6]  = 0;
	//================================================
}
// ---------------------------------------------------------------------------

void __fastcall TfrmAttach::sgAttachDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
	TAdvStringGrid  *pDBGrid   = (TAdvStringGrid *)Sender;
	TCanvas  *pCanvas   = pDBGrid->Canvas;

	if(ARow != 0 && ARow > m_nAttachCount && ARow == sgAttach->Row && ACol == 1)//New Line
	{
		cboRect = Rect;

		cboKindCode->Left = cboRect.Left;
		cboKindCode->Top  = ARow * sgAttach->DefaultRowHeight;
		//if(cboKindCode->Width != sgAttach->ColWidths[ACol])   cboKindCode->Width	= sgAttach->ColWidths[ACol];//210106//
		//if(cboKindCode->Height != sgAttach->DefaultRowHeight) cboKindCode->Height	= sgAttach->DefaultRowHeight;//210106//
		cboKindCode->Visible = true;
		sgAttach->Cells[6][ARow] = frmMain->m_BASECODE_001_DOC1[cboKindCode->ItemIndex].kind_code;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAttach::sgAttachGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign, TVAlignment &VAlign)
{
	if(ARow == 0)
	{
		HAlign = taCenter;
	}
	else
	{
		if(ACol == 4)
			HAlign = taRightJustify;
		else
			HAlign = taCenter;
	}

	VAlign = vtaCenter;
}
//---------------------------------------------------------------------------

void __fastcall TfrmAttach::btnUploadClick(TObject *Sender)
{
	if(	bUploading )//업로드 처리중입니다.
		return;

	AnsiString  asKindCode  = "";
	AnsiString  asFilePath  = "";
	AnsiString  asFileName  = "";
	AnsiString  asFileSize  = "";
	AnsiString  asBlob      = "";
	AnsiString  asStr       = "";
	int			nSeqNo		= 0;
	int			nType	    = DF_NEW_RECORD;
	DWORD       dwFileSize;
	int         nSize 		= sgAttach->RowCount - 1;
	int			nToUploadCount	= 0;
	int			nUploadedCount	= 0;

	bUploading	= true;//업로드 처리중입니다.

	frmMain->lblWait2->Caption	= "업로드중입니다.";
	frmMain->funcSetWaitWindows(true);
	Application->ProcessMessages();


//	if(sgAttach->Cells[2][nSize-1] == "")//처음 empty데이터
//		nSize = sgAttach->RowCount - 1;
//
	if(nSize == 0)
	{
		frmMsg->funcMessageDlg("파일 부재 알림:", "업로드할 데이터가 없습니다.", 3);
		return;
	}

//	pnlIng->Left = (pnlUploader->Width - pnlIng->Width) / 2;
//	pnlIng->Top  = (pnlUploader->Height - pnlIng->Height) / 2;
//	pnlIng->Visible = true;
//	pb->Max = nSize - 1;
//	pb->Position = 0;

	for(int i = 0; i < nSize; i++)
	{
		asStr		= sgAttach->Cells[5][i+1];
		if( !asStr.IsEmpty() )
			continue;

		nToUploadCount++;
		nType 	= DF_NEW_RECORD;
		nSeqNo	= 0;

		asFileName 	= sgAttach->Cells[2][i+1];
		asFileSize 	= sgAttach->Cells[4][i+1];
		if(asFileSize == "")	asFileSize = "0";
		dwFileSize 	= asFileSize.ToDouble();
		asFilePath 	= sgAttach->Cells[3][i+1];
//		asStr		= sgAttach->Cells[5][i+1];
//		if( asStr.IsEmpty() )//NEW
//		{
//			nType 	= DF_NEW_RECORD;
//			nSeqNo	= 0;
//		}
//		else//UPDATE
//		{
//			nType 	= DF_UPDATE_RECORD;
//			nSeqNo	= asStr.ToInt();
//		}
		asKindCode  = sgAttach->Cells[6][i+1];

		if(asKindCode.IsEmpty())
			asKindCode = eFunc->funcGetKindNameToKindCode(1, "구비서류");//201214//4->1

		if(i < m_nAttachCount - 1)//UPDATE
			nType 	= DF_UPDATE_RECORD;
		else//INSERT
			nType 	= DF_NEW_RECORD;

		if(funcAttachPutBinaryData(nType, nSeqNo, asKindCode, asFilePath, dwFileSize))
		{
			nUploadedCount++;
//			UPLODERLISTINI->WriteString("UPLOAD RESOURCE", asFileName, asUpdateTime);
//			pb->Position++;
		}
		else
		{
			sgAttach->FontColors[1][i+1] = (TColor)clRed;
			AnsiString asMsg = asFileName + "파일을 업로드하는데 문제가 발생하였습니다.";
			ShowMessage(asMsg);
//			pb->Max = 0;
//			pb->Position = 0;
//			pnlIng->Visible = false;
			return;
		}
	}

	if(nToUploadCount > 0 && nToUploadCount == nUploadedCount)
	{
		AnsiString asMsg = "첨부 파일을 업로드 하였습니다.";
		frmMsg->funcMessageDlg("업로드 완료:", asMsg, 3);

		frmSql->funcSQLReadTbAttach();
		funcRefreshShow();
	}

	frmMain->funcSetWaitWindows(false);
	Application->ProcessMessages();
	bUploading	= false;//업로드 처리완료//

	if(cboKindCode->Visible == true) cboKindCode->Visible = false;
}
//---------------------------------------------------------------------------
//==============================================
//파일 binary data upload
//==============================================
// binary data를 DB에 기록한다.
bool __fastcall TfrmAttach::funcAttachPutBinaryData(int _nType, int _nSeqNo, AnsiString _asKindCode, AnsiString _asFileName, LONG _lFileSize)
{
	SQLRETURN       ret;
	SQLTCHAR      * pWriteBuff;
	SQLINTEGER      ind = SQL_DATA_AT_EXEC;
	int             chunksize, dtsize;      // 데이터를 잘라서 보낼려고
	AnsiString      asSqlQry = "";
	AnsiString      asValues = "";
	AnsiString      asWhere = "";
	bool			bRet = false;
	SDWORD          cbFileName, cbFileSize, cbUpdateTime;

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);


	//==============================================
    //DELETE
	if(_nType == DF_DELETE_RECORD)
	{
		asWhere 	= "WHERE SIDO_CODE = '"+ frmMain->_SIDOCODE + "' AND ACCEPT_YEAR = '" + frmLMReq->m_asAcceptYear + "' AND ACCEPT_NO='" + frmLMReq->m_asAcceptNo + "'";
		asSqlQry 	= "DELETE FROM TB_LMREQ_ATTACH " + asWhere;
		return frmSql->func_QryProcess(asSqlQry);
	}

	//==============================================
    //INSERT or UPDATE
	if (_lFileSize > MAX_CHUNK_SIZE)        // 한번에 보낼수있는 최대 바이트
		chunksize = MAX_CHUNK_SIZE;         // 보다 크면 잘라서 보냄
	else
		chunksize = _lFileSize;

	if(FileExists(_asFileName))
	{
		FILE *fd;
		size_t nResult = 0;

		fd = fopen(_asFileName.c_str(),"rb");
		if (fd==NULL)
		{
			ShowMessage("fopen error");
			return false;
		}

		// obtain file size:
		fseek (fd , 0 , SEEK_END);
		_lFileSize = ftell (fd);
		rewind (fd);

		buffer = (char*)malloc (sizeof(char)*_lFileSize);
		if(buffer == NULL)
		{
			ShowMessage("메모리 할당 에러");
			return false;
		}
		memset(buffer, 0x00, _lFileSize);

		nResult = fread(buffer, sizeof(char), _lFileSize, fd);
		if((LONG)nResult != _lFileSize)
		{
			ShowMessage("파일 읽기 오류");
			return false;
		}

		fclose(fd);

		//-------------------------------------------------------------------
		_asFileName	= ExtractFileName(_asFileName);

		if(_nType == DF_NEW_RECORD)//insert
		{
			asValues	= "(" + frmMain->_SIDOCODE + ", '" + frmLMReq->m_asAcceptYear + "', '" + frmLMReq->m_asAcceptNo + "', " + IntToStr(frmLMReq->m_nReqGb) + ", '" + _asKindCode.Trim() + "', '" + _asFileName.Trim() + "', ? ," + _lFileSize + ")";
			asSqlQry	= "INSERT INTO TB_LMREQ_ATTACH (SIDO_CODE, ACCEPT_YEAR, ACCEPT_NO, REQGB, KIND_CODE, FILE_NAME, RESOURCE_DATA, FILE_SIZE) VALUES " + asValues;
		}
		else if(_nType == DF_UPDATE_RECORD)
		{
			asWhere 	= " WHERE SIDO_CODE = '"+ frmMain->_SIDOCODE + "' AND ACCEPT_YEAR = '" + frmLMReq->m_asAcceptYear + "' AND ACCEPT_NO=" + frmLMReq->m_asAcceptNo + "' AND REQGB=" + IntToStr(frmLMReq->m_nReqGb)+ " AND SEQNO=" + _nSeqNo;
			asSqlQry 	= "UPDATE TB_LMREQ_ATTACH SET KIND_CODE='" + _asKindCode.Trim() + ", FILE_NAME='" + _asFileName.Trim() + "', RESOURCE_DATA=?, FILE_SIZE=" + _lFileSize + asWhere;
		}

		// 쿼리를 준비합니다.SQLBindParameter를 사용하기위한 준비작업
		ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR*)asSqlQry.c_str(), SQL_NTS);
		if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		{
			// 파라메터 바인딩
			ret = SQLBindParameter(frmSql->m_hStmt, 1, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_LONGVARBINARY, 0, 0, (SQLPOINTER)buffer, _lFileSize, &ind);
			ret = SQLExecute(frmSql->m_hStmt);// 쿼리 실행
			while(ret == SQL_NEED_DATA)
			{
				// 데이터 보내기 시작
				ret = SQLParamData(frmSql->m_hStmt, (SQLPOINTER*)&pWriteBuff);  // 시작에 한번
				if(ret == SQL_NEED_DATA)
				{
					// 데이터가 클때 잘라서 모두 다 보내준다.
					for (dtsize=0, pWriteBuff = buffer; dtsize < _lFileSize;
							dtsize += chunksize, pWriteBuff += chunksize)
					{
						int len;

						if (dtsize+chunksize < _lFileSize)
							len = chunksize;
						else
							len = _lFileSize - dtsize;

						ret = SQLPutData(frmSql->m_hStmt, (SQLPOINTER)pWriteBuff, len );
						if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
							bRet = true;
						else
							ShowMessage("0:" + ret);
					}

					ret = SQLParamData(frmSql->m_hStmt, (SQLPOINTER*)&pWriteBuff);  // 끝에 한번 더

					//func_QryProcess(asSql.c_str());
					if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
						bRet = true;
					else
						ShowMessage("1:");// + ret);
				}
				else
				{
					ShowMessage("2:");// + ret);
				}
			}
		}
		else if(ret == SQL_INVALID_HANDLE)
			ShowMessage("SQL_INVALID_HANDLE");
		else if(ret == SQL_ERROR)
			ShowMessage("SQL_ERROR");

		free(buffer);
	}
	else// 에러가 발생했을때
	{
		_TUCHAR* szErrorMsg;
		_TUCHAR* pSqlState;
		SDWORD    NativeError;
		SWORD    svErrorMsg;

		szErrorMsg = new _TUCHAR[ SQL_MAX_MESSAGE_LENGTH-1];
		pSqlState = new _TUCHAR[SQL_MAX_MESSAGE_LENGTH-1];

		SQLError(frmSql->m_hEnv, frmSql->m_hDbc, frmSql->m_hStmt, pSqlState, &NativeError, szErrorMsg, SQL_MAX_MESSAGE_LENGTH-1, &svErrorMsg);

		ShowMessage((char*)szErrorMsg);

		// SQL 상태코드들이 들어 있습니다.
		delete pSqlState;
		delete szErrorMsg;
	}

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	return bRet;
}
//---------------------------------------------------------------------------

void __fastcall TfrmAttach::funcDeleteSelectFile(int _nRow)
{
	AnsiString  asMsg		= "";
	AnsiString 	asSeqNo 	= sgAttach->Cells[5][_nRow];
	AnsiString	asPathName	= sgAttach->Cells[3][_nRow];
	int			nSeqNo		= 0;

	if( asSeqNo.IsEmpty())
	{
		asMsg = "파일정보가 없습니다.";
		frmMsg->funcMessageDlg("파일정보 확인 :", asMsg, 3);
		return;
	}

	if( DeleteFile(asPathName) )
	{
		nSeqNo	= asSeqNo.ToInt();

		if(funcAttachPutBinaryData(DF_DELETE_RECORD, nSeqNo, "", "", 0))
		{
			asMsg = "파일을 삭제하였습니다.";
			frmMsg->funcMessageDlg("파일삭제 확인 :", asMsg, 3);
		}
	}

	//
	sgAttach->RemoveRows(_nRow, 1);
	pnlAttachT->Caption = "  첨부파일목록(총 " + FormatFloat("###,##0", sgAttach->RowCount - 1) + "건)";
	if(frmSql->m_vLMREQ_ATTACH.size() > 0)
	{
		m_nAttachCount--;
		sgAttach->RowCount = m_nAttachCount + 1;
		if(frmSql->m_vLMREQ_ATTACH.size() == 1)
		{
			frmSql->m_vLMREQ_ATTACH.clear();
			cboKindCode->Visible = false;
		}
		else
		{
			frmSql->m_vLMREQ_ATTACH.erase(frmSql->m_vLMREQ_ATTACH.begin() + _nRow-1);
		}
	}//
	else//size == 0
	{
		sgAttach->ColWidths[2]  = 400;
    }
}
// ---------------------------------------------------------------------------

void __fastcall TfrmAttach::funcDeleteAll()
{
	AnsiString  asMsg		= "";

	if(funcAttachPutBinaryData(DF_DELETE_RECORD, 0, "", "", 0))
	{
		m_nAttachCount	= 0;
		frmSql->m_vLMREQ_ATTACH.clear();

		int nSeqNo	= frmSql->funcSQLMaxSeqNoLMReqAttach();
		//SetSeqNo
		AnsiString 	asSqlQry	= "";
		asSqlQry = "ALTER TABLE TB_LMREQ_ATTACH AUTO_INCREMENT = " + IntToStr(nSeqNo);
		frmSql->func_SetSeqNoQryProcess(asSqlQry);
	}

	funcInitAttach();
}
// ---------------------------------------------------------------------------
void __fastcall TfrmAttach::funcUpdateAttachCount()
{
	pnlAttachT->Caption = "  첨부파일목록(총 " + FormatFloat("###,##0", sgAttach->RowCount - 1) + "건)";
}
// ---------------------------------------------------------------------------

void __fastcall TfrmAttach::funcOpenExplorer(AnsiString _asPathName)
{
	ShellExecute(NULL, "open", _asPathName.c_str(), NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TfrmAttach::funcSetComboList()
{
	for(int i = 0; i < (int)frmMain->m_BASECODE_001_DOC1.size(); i++)
	{
		cboKindCode->Items->Add(frmMain->m_BASECODE_001_DOC1[i].kind_name);
	}

	if((int)frmMain->m_BASECODE_001_DOC1.size() > 0)
		cboKindCode->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmAttach::cboKindCodeClick(TObject *Sender)
{
	if(m_nSelectGridIndex > 0){
		sgAttach->Cells[1][m_nSelectGridIndex] = frmMain->m_BASECODE_001_DOC1[cboKindCode->ItemIndex].kind_name;
		cboKindCode->Visible = false;
		sgAttach->Cells[6][m_nSelectGridIndex] = frmMain->m_BASECODE_001_DOC1[cboKindCode->ItemIndex].kind_code;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmAttach::sgAttachClickCell(TObject *Sender, int ARow, int ACol)
{
	m_nSelectGridIndex = ARow;
	if(ARow > 0)
	{
		//=======================================================
		if (ACol == 0)//삭제//
		{
			if (ARow > m_nAttachCount && sgAttach->Cells[5][ARow] == "")//삭제-신규추가파일//바로 삭제//
			{
				sgAttach->RemoveRows(ARow, 1);

				funcUpdateAttachCount();
			}
			else//삭제-기등록파일//DB DELETE QUERY
			{
				AnsiString 	asStr 		= "";
				AnsiString 	asPathName 	= "";
				AnsiString 	asFileName 	= sgAttach->Cells[2][ARow];
				int			nSeqNo      = 0;

				asStr	= sgAttach->Cells[5][ARow];
				if(!asStr.IsEmpty() && !asFileName.IsEmpty())
				{
					AnsiString strMessage = "선택한 파일을 삭제하시겠습니까?";
					frmMsg->funcMessageDlg("파일삭제 확인 :", strMessage, 1);

					if (frmMsg->m_bClick == 1) // Yes
					{
						funcDeleteSelectFile(ARow);
					}
					else // No
					{
						return;
					}
				}
			}
		}
		//=======================================================
		else if (ACol == 1)//문서구분//
		{
			//201214//
			cboKindCode->Visible = false;

			AnsiString asStr	= sgAttach->Cells[1][ARow];
			if( !asStr.IsEmpty() )
			{
				cboKindCode->ItemIndex	= eFunc->funcGetKindNameToKindIndex(1, asStr.c_str());
			}
			else
			{
                cboKindCode->ItemIndex	= 0;
            }
		}
		//=======================================================
		else if(ACol == 2)//파일 열기//
		{
			AnsiString asPathName	= sgAttach->Cells[3][ARow];

			if( FileExists(asPathName) )
			{
				funcOpenExplorer(asPathName);
			}
		}
		//=======================================================
	}
}
//---------------------------------------------------------------------------

