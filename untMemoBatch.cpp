#pragma link "bsPngImageList"
#pragma link "bsSkinCtrls"
#pragma link "tmsAdvGridExcel"
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "BaseGrid"
#pragma link "bsSkinBoxCtrls"
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#pragma warn -8004

TfrmMemoBatch *frmMemoBatch;
//---------------------------------------------------------------------------
__fastcall TfrmMemoBatch::TfrmMemoBatch(TComponent* Owner)
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
		this->panWindowsMove->Color		= (TColor)RGB(R, G, B);
		//pnlWaitT->Color//
	}


	int nCol = 0;

	sgResult->FixedFont->Color 	= (TColor)RGB(111, 111, 111);
	sgResult->FixedColor       	= (TColor)RGB(221,232,254);//clInfoBk;
	sgResult->DefaultColWidth 	= 80;

	//200114
//	sgResult->ColCount = 7;
//	sgResult->RowCount = 2;
//	sgResult->FixedRows = 1;
//	sgResult->FixedCols = 0;
//
//	sgResult->ColWidths[nCol]	= 80;
//	sgResult->Cells[nCol++][0] 	= "POI_KEY";
//	sgResult->ColWidths[nCol]	= 160;
//	sgResult->Cells[nCol++][0] 	= "POI_NAME";
//	sgResult->ColWidths[nCol]	= 200;
//	sgResult->Cells[nCol++][0] 	= "사업명";
//	sgResult->ColWidths[nCol]	= 300;
//	sgResult->Cells[nCol++][0] 	= "MEMO";
//	sgResult->ColWidths[nCol]	= 100;
//	sgResult->Cells[nCol++][0] 	= "작성자";
//	sgResult->ColWidths[nCol]	= 100;
//	sgResult->Cells[nCol++][0] 	= "X";
//	sgResult->ColWidths[nCol]	= 100;
//	sgResult->Cells[nCol++][0] 	= "Y";

	sgResult->ColCount = 4;
	sgResult->RowCount = 2;
	sgResult->FixedRows = 1;
	sgResult->FixedCols = 0;

	sgResult->ColWidths[nCol]	= 40;
	sgResult->Cells[nCol++][0] 	= "선택";
	sgResult->ColWidths[nCol]	= 160;
	sgResult->Cells[nCol++][0] 	= "지번";
	sgResult->ColWidths[nCol]	= 350;
	sgResult->Cells[nCol++][0] 	= "사업명";
	sgResult->ColWidths[nCol]	= 200;
	sgResult->Cells[nCol++][0] 	= "소유자";

	::UpdateWindow(sgResult->Handle);

	for (int i = 0; i < 1; i++)
		for (int j = 0; j < sgResult->ColCount; j++)
			sgResult->Colors[j][i] = (TColor)RGB(221,232,254);//clInfoBk;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoBatch::FormCreate(TObject *Sender)
{
	int nStyle = GetWindowLong(this->Handle, GWL_STYLE);
	::SetWindowLong(this->Handle, GWL_STYLE, nStyle & (~WS_CAPTION ) | (WS_BORDER) & (~WS_DLGFRAME));
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoBatch::FormShow(TObject *Sender)
{
	funcLoadButtonImage();

	IMGDELETE->Enabled  = false;
	edtFind->Text		= "";
	m_nDelCount			= 0;

	//======================================================================
	//일괄 등록 데이터 모두 가져오기//
	IMGFINDClick(IMGFIND);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoBatch::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(this->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------


void __fastcall TfrmMemoBatch::btnCloseTypeBClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoBatch::FormClose(TObject *Sender, TCloseAction &Action)
{
	funcDeleteButtonImage();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoBatch::funcSetWaitWindows(bool bSetValue)
{
	palWait->Left = (this->Width/2) - (palWait->Width/2);
	//191126//palWait->Top  = (palClient->Height - bsSkinStatusBar1->Height)/2 - (palWait->Height/2);
	palWait->Top  = (this->Height/2) - (palWait->Height/2);//191126//

	if (this->palWait->Visible == !bSetValue)
	{
		palWait->Visible = bSetValue;

		if (bSetValue)		Screen->Cursor     = crHourGlass;
		else            	Screen->Cursor     = crDefault;
	}

	Application->ProcessMessages();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMemoBatch::funcLoadButtonImage()
{
	AnsiString filename = "";

	//Button Image
	for(int i = 0; i < 2; i++)
	{
		TPngImage *imgPng = new TPngImage();
		filename = frmMain->IMAGEMEMOPATH + "btnAllReg" + IntToStr(i+1) + ".png";
		imgPng->LoadFromFile(filename);
		BITMAP_BTN_REGIST[i] = new Graphics::TBitmap();
		BITMAP_BTN_REGIST[i]->Assign(imgPng);
		delete imgPng;
		imgPng = NULL;
		//
		imgPng = new TPngImage();
		filename = frmMain->IMAGEMEMOPATH + "btnFind" + IntToStr(i+1) + ".png";
		imgPng->LoadFromFile(filename);
		BITMAP_BTN_FIND[i] = new Graphics::TBitmap();
		BITMAP_BTN_FIND[i]->Assign(imgPng);
		delete imgPng;
		imgPng = NULL;
		//
		imgPng = new TPngImage();
		filename = frmMain->IMAGEMEMOPATH + "btnSelDel" + IntToStr(i+1) + ".png";
		imgPng->LoadFromFile(filename);
		BITMAP_BTN_DELETE[i] = new Graphics::TBitmap();
		BITMAP_BTN_DELETE[i]->Assign(imgPng);
		delete imgPng;
		imgPng = NULL;
	}

	IMGREGIST->Picture->Bitmap->Assign(BITMAP_BTN_REGIST[0]);
	IMGFIND->Picture->Bitmap->Assign(BITMAP_BTN_FIND[0]);
	IMGDELETE->Picture->Bitmap->Assign(BITMAP_BTN_DELETE[0]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoBatch::funcDeleteButtonImage()
{
	for(int i = 0; i < 2; i++)
	{
		delete BITMAP_BTN_REGIST[i];
		BITMAP_BTN_REGIST[i] = NULL;
		delete BITMAP_BTN_FIND[i];
		BITMAP_BTN_FIND[i] = NULL;
		delete BITMAP_BTN_DELETE[i];
		BITMAP_BTN_DELETE[i] = NULL;
	}
}
//---------------------------------------------------------------------------


//200120//지번마다의 shape을 개별 메모건으로 저장//
void __fastcall TfrmMemoBatch::func_readExcelToWriteDB(AnsiString sFileName)
{
	try{
		AdvGridExcelIO1->CleanupInstance();
		AdvGridExcelIO1->XLSImport(sFileName);
	}
	__finally{

		//일괄등록 데이터 - 사전검사
		if( funcCheckRawExcelData() )//RAWEXCEL//--------------------------------------------------
		{
			//Init//
			m_vTEMPMEMOINFO.clear();
			m_vTEMPMEMOVECTOR.clear();
			m_vRAWEXCELDATA.clear();

			int rowcount = frmMemoRegist->sgResult->RowCount;
			int colcount = frmMemoRegist->sgResult->ColCount;

			AnsiString  strline, strtemp;
			AnsiString  resultTemp[6];
			AnsiString  asPoiKey  = "";
			AnsiString  asPnu     = "";
			AnsiString  asPoiName = "";
			AnsiString  asNowDT   = "";
			AnsiString  asTitle	  = "";
			int 		nIndex    = -1;
			int			nJiguCnt  = 0;//사업명 단위 개수//
			int			nSeq      = 0;

			for(int i=1; i<rowcount; i++){
				for(int j=0; j<colcount; j++) resultTemp[j] = "";
				for(int j=0; j<colcount; j++){
					resultTemp[j] = frmMemoRegist->sgResult->Cells[j][i];
				}

				asTitle	= (char*)tTempMemoInfo.TITLE;

				//200210//중복자료가 있는지를 체크한다.//사업명이 다르면 nSeq = 1 초기화한다//
				if(asTitle != "" && resultTemp[5] == asTitle)
				{
					nSeq++;
				}
				else//사업명이 달라짐//
				{
					nJiguCnt++;
					nSeq = 0;
                }

				memset(&tempRawExcelData, 0x00, sizeof(BATCHMEMOINFO_STRUCT));
				memset(&tTempMemoInfo, 0x00, sizeof(MEMOINFO_STRUCT));

				asPnu     = "";
				asPoiName = "";
				asNowDT = Now().FormatString("yyyymmddhhmmss");

				//200210
//				if( (nSeq % 1000) == 0)
//					nSeq = 0;

				//200210//asPoiKey.sprintf("%s%03d", asNowDT, nSeq++);
				asPoiKey.sprintf("%s%03d%04d", asNowDT, nJiguCnt, nSeq);
				memcpy(tTempMemoInfo.POI_KEY, asPoiKey.c_str(), sizeof(tTempMemoInfo.POI_KEY));

				//POI_NAME
				strtemp = resultTemp[1];
				if( !resultTemp[2].IsEmpty() )
				  strtemp = strtemp + " " + resultTemp[2];
				strtemp = strtemp + " " + resultTemp[3];

				memcpy(tTempMemoInfo.POI_NAME        , strtemp.c_str(), sizeof(tTempMemoInfo.POI_NAME));
				asPnu = frmSql->func_ConvertAddressToLandcd(strtemp, true);

				if(asPnu.Length() != 19)
					continue;

				nIndex = frmMain->func_readJibunIndex(asPnu) - 1;
				if(nIndex > -1)
				{
					GPoint gPoint;
					gPoint.x = frmMain->m_vSHPPOLYCBND[nIndex].x;
					gPoint.y = frmMain->m_vSHPPOLYCBND[nIndex].y;
					tTempMemoInfo.X = gPoint.x;
					tTempMemoInfo.Y = gPoint.y;
					tTempMemoInfo.FILE_CNT = 0;
					tTempMemoInfo.DATA_CNT = frmMain->m_vSHPPOLYCBND[nIndex].m_nNumPoints;//[TODO]m_nNumParts는 어떻게 할거야?

					memset(&tTempMemoVector, 0x00, sizeof(MEMOVECTOR_STRUCT));
					memcpy(tTempMemoVector.POI_KEY, asPoiKey.c_str(), sizeof(tTempMemoVector.POI_KEY));
					//frmMain->m_vSHPPOLYCBND[nIndex].m_vPoints.size
					for(int j = 0; j < (int)frmMain->m_vSHPPOLYCBND[nIndex].m_vPoints.size(); j++)
					{
						tTempMemoVector.VECTOR.push_back(frmMain->m_vSHPPOLYCBND[nIndex].m_vPoints[j]);
					}
					tTempMemoVector.COUNT = tTempMemoVector.VECTOR.size();
					tTempMemoVector.SIZE = sizeof(tTempMemoVector.VECTOR);
					m_vTEMPMEMOVECTOR.push_back(tTempMemoVector);
				}
				else
				{
					//TITLE//다음 사업명과 같은지 확인하기 위해 필요//
					memcpy(tTempMemoInfo.TITLE, resultTemp[5].c_str(), sizeof(tTempMemoInfo.TITLE));
					continue;//pnu 없으면 등록안함//지번정보 업데이트 시점이 일치하지 않아서 없으면 어떻게 하지?//[TODO]
				}
				//--------------------------------------------------------------------------------------------------

				//TITLE
				memcpy(tTempMemoInfo.TITLE, resultTemp[5].c_str(), sizeof(tTempMemoInfo.TITLE));
				//메모
				memcpy(tTempMemoInfo.MEMO, "", sizeof(tTempMemoInfo.MEMO));
//				//소유자
				memcpy(tTempMemoInfo.OWN_NAME, resultTemp[4].c_str() , sizeof(tTempMemoInfo.OWN_NAME));
				//일괄등록여부
				memcpy(tTempMemoInfo.BATCH_YN, "Y" , sizeof(tTempMemoInfo.BATCH_YN));
				//공개여부
				memcpy(tTempMemoInfo.OPEN_YN, "Y" , sizeof(tTempMemoInfo.OPEN_YN));
				//사용자 암호화된 ID
				memcpy(tTempMemoInfo.WRITE_ID, frmMain->m_asCurrentId.c_str(), sizeof(tTempMemoInfo.WRITE_ID));
				//저장시각
				memcpy(tTempMemoInfo.WRITE_DT, asNowDT.c_str(), sizeof(tTempMemoInfo.WRITE_DT));

				m_vTEMPMEMOINFO.push_back(tTempMemoInfo);

				//Push Raw Excel Data==============================
				strcpy(tempRawExcelData.NO, resultTemp[0].c_str());
				strcpy(tempRawExcelData.UMD_NAME, resultTemp[1].c_str());
				strcpy(tempRawExcelData.RI_NAME, resultTemp[2].c_str());
				strcpy(tempRawExcelData.JIBUN_NAME, resultTemp[3].c_str());
				strcpy(tempRawExcelData.OWN_NAME, resultTemp[4].c_str());
				strcpy(tempRawExcelData.TITLE, resultTemp[5].c_str());
				m_vRAWEXCELDATA.push_back(tempRawExcelData);
				//=================================================

				Label1->Caption = "데이터확인 : " + IntToStr((int)m_vRAWEXCELDATA.size()) + "건";

				Application->ProcessMessages();
			}

			AnsiString asSqlQry;
			AnsiString asWhere;//기 등록 데이타 확인 Where 절

			int size = (int)m_vTEMPMEMOINFO.size();
			bool success = true;

			for(int i=0; i<size; i++){
				asWhere = "";

				asSqlQry = "INSERT INTO " + frmMain->TABLE_MEMOINFO + " VALUES(";

				if( !strcmp(m_vTEMPMEMOINFO[i].POI_NAME, "음봉면 송촌리 302-5"))
				{
                    int a = 1;
                }

				strtemp = (char*)m_vTEMPMEMOINFO[i].POI_KEY;
				asSqlQry = asSqlQry + "'" + strtemp.Trim() + "',";

				strtemp = (char*)m_vTEMPMEMOINFO[i].POI_NAME;
				asSqlQry = asSqlQry + "'" + strtemp.Trim() + "',";

				strtemp = (char*)m_vTEMPMEMOINFO[i].TITLE;
				asSqlQry = asSqlQry + "'" + strtemp.Trim() + "',";

				strtemp = (char*)m_vTEMPMEMOINFO[i].MEMO;
				asSqlQry = asSqlQry + "'" + strtemp.Trim() + "',";

				strtemp =  (char*)m_vTEMPMEMOINFO[i].OWN_NAME;
				asSqlQry = asSqlQry + "'" + strtemp.Trim() + "',";

				strtemp =  (char*)m_vTEMPMEMOINFO[i].BATCH_YN;
				asSqlQry = asSqlQry + "'" + strtemp.Trim() + "',";

				strtemp =  (char*)m_vTEMPMEMOINFO[i].OPEN_YN;
				asSqlQry = asSqlQry + "'" + strtemp.Trim() + "',";

				strtemp =  (char*)m_vTEMPMEMOINFO[i].WRITE_ID;
				asSqlQry = asSqlQry + "'" + strtemp.Trim() + "',";

				strtemp =  (char*)m_vTEMPMEMOINFO[i].WRITE_DT;
				asSqlQry = asSqlQry + "'" + strtemp.Trim() + "',";

				asSqlQry = asSqlQry + m_vTEMPMEMOINFO[i].FILE_CNT + ",";
				asSqlQry = asSqlQry + m_vTEMPMEMOINFO[i].DATA_CNT + ",";

				asSqlQry = asSqlQry + m_vTEMPMEMOINFO[i].X + ",";
				asSqlQry = asSqlQry + m_vTEMPMEMOINFO[i].Y + ");";

				if(frmSql->func_QryProcess(asSqlQry) == false){
					success = false;
					frmMsg->funcMessageDlg("일괄등록:", "일괄등록을 실패하였습니다.", 2);
					break;
				}

				Label1->Caption = "DB적용중 : " + IntToStr(i+1) + " 건";

				strtemp = "";
				Application->ProcessMessages();

				//지번 VECTOR 저장//
				frmMemo->m_asTempPoiKey = (char*)m_vTEMPMEMOVECTOR[i].POI_KEY;
				funcWriteFileVectorLog(i);
			}
			Application->ProcessMessages();

			asSqlQry = "COMMIT;";
			frmSql->func_QryProcess(asSqlQry);

			//======================================================================
			//일괄 등록 (검색어 포함) 데이터 가져오기//
			IMGFINDClick(IMGFIND);//funcReadKeywordMemoInfo(edtFind->Text.Trim());

			//======================================================================
			//메모 모든 데이터 가져오기//
			frmSql->funcReadDocumentMemoAll();
			//======================================================================
			//메모 영역 모든 데이터 가져오기//
			frmMemo->m_vMEMOVECTOR.clear();
			frmSql->m_vMEMOPOLY.clear();
			for(int i = 0; i < (int)frmSql->m_vALLMEMOINFO.size(); i++)
			{
				if(frmSql->m_vALLMEMOINFO[i].DATA_CNT >= 3)
				{
					frmMemo->funcReadFileVectorLog(frmSql->m_vALLMEMOINFO[i].POI_KEY);
					//200109//frmSql->funcReadDocumentMemoVector(frmSql->m_vALLMEMOINFO[i].POI_KEY);
				}
			}

			frmMain->func_DrawImagePaint();//200120
		}//funcCheckRawExcelData() return value is true
	}
}
////---------------------------------------------------------------------------

////200120//사업명이 같은 메모를 1건으로 등록//
//하려 했으나, 지번별 시작 좌표를 이전 좌표의 마지막에서 이어오기 때문에 그림이 이상함//
//void __fastcall TfrmMemoBatch::func_readExcelToWriteDB(AnsiString sFileName)
//{
//	try{
//		AdvGridExcelIO1->CleanupInstance();
//		AdvGridExcelIO1->XLSImport(sFileName);
//	}
//	__finally{
//
//		//일괄등록 데이터 - 사전검사
//		if( funcCheckRawExcelData() )//RAWEXCEL//--------------------------------------------------
//		{
//			m_vTEMPMEMOINFO.clear();
//			m_vTEMPMEMOVECTOR.clear();
//
//			int rowcount = frmMemoRegist->sgResult->RowCount;
//			int colcount = frmMemoRegist->sgResult->ColCount;
//
//			AnsiString  strline, strtemp;
//			AnsiString  resultTemp[6];
//			AnsiString  asPoiKey  = "";
//			AnsiString  asPnu     = "";
//			AnsiString  asPoiName = "";
//			AnsiString  asTitle   = "";
//			AnsiString  asNowDT   = "";
//			int 		nIndex = -1;
//			int 		nCount = 0;
//
//			for(int i=1; i<rowcount; i++){
//				for(int j=0; j<colcount; j++) resultTemp[j] = "";
//				for(int j=0; j<colcount; j++){
//					resultTemp[j] = frmMemoRegist->sgResult->Cells[j][i];
//				}
//
//				if(asTitle == resultTemp[5])//사업명이 같다면//
//				{
//					//POI_NAME
//					strtemp = resultTemp[1];
//					if( !resultTemp[2].IsEmpty() )
//					  strtemp = strtemp + " " + resultTemp[2];
//					strtemp = strtemp + " " + resultTemp[3];
//					asPnu = frmSql->func_ConvertAddressToLandcd(strtemp, true);
//
//					if(asPnu.Length() != 19)
//						continue;
//
//					nIndex = frmMain->func_readJibunIndex(asPnu) - 1;
//					if(nIndex > -1)
//					{
//						if(m_vTEMPMEMOVECTOR.size() == 0)
//						{
//							GPoint gPoint;
//							gPoint.x = frmMain->m_vSHPPOLYCBND[nIndex].x;
//							gPoint.y = frmMain->m_vSHPPOLYCBND[nIndex].y;
//							tTempMemoInfo.X = gPoint.x;
//							tTempMemoInfo.Y = gPoint.y;
//							tTempMemoInfo.FILE_CNT = 0;
//						}
//
//						//frmMain->m_vSHPPOLYCBND[nIndex].m_vPoints.size
//						for(int j = 0; j < (int)frmMain->m_vSHPPOLYCBND[nIndex].m_vPoints.size(); j++)
//						{
//							tTempMemoVector.VECTOR.push_back(frmMain->m_vSHPPOLYCBND[nIndex].m_vPoints[j]);
//						}
//					}
//					else
//					{
//						continue;//pnu 없으면 등록안함//지번정보 업데이트 시점이 일치하지 않아서 없으면 어떻게 하지?//[TODO]
//					}
//				}
//				else
//				{
//					if(tTempMemoVector.VECTOR.size() > 0)
//					{
//						m_vTEMPMEMOINFO[nCount-1].DATA_CNT = tTempMemoVector.VECTOR.size();//---
//						tTempMemoVector.COUNT 	= tTempMemoVector.VECTOR.size();
//						tTempMemoVector.SIZE 	= sizeof(tTempMemoVector.VECTOR);
//						m_vTEMPMEMOVECTOR.push_back(tTempMemoVector);
//                    }
//
//					memset(&tTempMemoInfo, 0x00, sizeof(MEMOINFO_STRUCT));
//					memset(&tTempMemoVector, 0x00, sizeof(MEMOVECTOR_STRUCT));
//
//					asPnu     = "";
//					asPoiName = "";
//					asNowDT = Now().FormatString("yyyymmddhhmmss");
//
//					asPoiKey.sprintf("%s%03d", asNowDT, nCount+1);
//					memcpy(tTempMemoInfo.POI_KEY, asPoiKey.c_str(), sizeof(tTempMemoInfo.POI_KEY));
//					//POI_NAME
//					strtemp = resultTemp[1];
//					if( !resultTemp[2].IsEmpty() )
//					  strtemp = strtemp + " " + resultTemp[2];
//					strtemp = strtemp + " " + resultTemp[3];
//
//					if(asTitle != resultTemp[5])//사업명이 같지 않다면//
//						memcpy(tTempMemoInfo.POI_NAME        , strtemp.c_str(), sizeof(tTempMemoInfo.POI_NAME));
//
//					asPnu = frmSql->func_ConvertAddressToLandcd(strtemp, true);
//
//					if(asPnu.Length() != 19)
//						continue;
//
//					nIndex = frmMain->func_readJibunIndex(asPnu) - 1;
//					if(nIndex > -1)
//					{
//						GPoint gPoint;
//						gPoint.x = frmMain->m_vSHPPOLYCBND[nIndex].x;
//						gPoint.y = frmMain->m_vSHPPOLYCBND[nIndex].y;
//						tTempMemoInfo.X = gPoint.x;
//						tTempMemoInfo.Y = gPoint.y;
//						tTempMemoInfo.FILE_CNT = 0;
//						tTempMemoInfo.DATA_CNT = frmMain->m_vSHPPOLYCBND[nIndex].m_nNumPoints;//[TODO]m_nNumParts는 어떻게 할거야?
//
//						memcpy(tTempMemoVector.POI_KEY, asPoiKey.c_str(), sizeof(tTempMemoVector.POI_KEY));
//						//frmMain->m_vSHPPOLYCBND[nIndex].m_vPoints.size
//						for(int j = 0; j < (int)frmMain->m_vSHPPOLYCBND[nIndex].m_vPoints.size(); j++)
//						{
//							tTempMemoVector.VECTOR.push_back(frmMain->m_vSHPPOLYCBND[nIndex].m_vPoints[j]);
//						}
//						nCount++;
//					}
//					else
//					{
//						continue;//pnu 없으면 등록안함//지번정보 업데이트 시점이 일치하지 않아서 없으면 어떻게 하지?//[TODO]
//					}
//					//--------------------------------------------------------------------------------------------------
//
//					asTitle 	= resultTemp[5];
//					memcpy(tTempMemoInfo.TITLE, asTitle.c_str(), sizeof(tTempMemoInfo.TITLE));
//					//메모
//					memcpy(tTempMemoInfo.MEMO, "", sizeof(tTempMemoInfo.MEMO));
//	//				//소유자
//					memcpy(tTempMemoInfo.OWN_NAME, resultTemp[4].c_str() , sizeof(tTempMemoInfo.OWN_NAME));
//					//일괄등록여부
//					memcpy(tTempMemoInfo.BATCH_YN, "Y" , sizeof(tTempMemoInfo.BATCH_YN));
//					//공개여부
//					memcpy(tTempMemoInfo.OPEN_YN, "Y" , sizeof(tTempMemoInfo.OPEN_YN));
//					//사용자 암호화된 ID
//					memcpy(tTempMemoInfo.WRITE_ID, frmMain->m_asCurrentId.c_str(), sizeof(tTempMemoInfo.WRITE_ID));
//					//저장시각
//					memcpy(tTempMemoInfo.WRITE_DT, asNowDT.c_str(), sizeof(tTempMemoInfo.WRITE_DT));
//
//					m_vTEMPMEMOINFO.push_back(tTempMemoInfo);
//				}
//				Application->ProcessMessages();
//			}
//
//			if(tTempMemoVector.VECTOR.size() > 0)//last data
//			{
//				m_vTEMPMEMOINFO[nCount-1].DATA_CNT = tTempMemoVector.VECTOR.size();//---
//				tTempMemoVector.COUNT 	= tTempMemoVector.VECTOR.size();
//				tTempMemoVector.SIZE 	= sizeof(GPoint) * tTempMemoVector.COUNT;
//				m_vTEMPMEMOVECTOR.push_back(tTempMemoVector);
//			}
//
//			AnsiString asSqlQry;
//			AnsiString asWhere;//기 등록 데이타 확인 Where 절
//
//			int size = (int)m_vTEMPMEMOINFO.size();
//			bool success = true;
//
//			for(int i=0; i<size; i++){
//				asWhere = "";
//
//				asSqlQry = "INSERT INTO " + frmMain->TABLE_MEMOINFO + " VALUES(";
//
//				strtemp = (char*)m_vTEMPMEMOINFO[i].POI_KEY;
//				asSqlQry = asSqlQry + "'" + strtemp.Trim() + "',";
//
//				strtemp = (char*)m_vTEMPMEMOINFO[i].POI_NAME;
//				asSqlQry = asSqlQry + "'" + strtemp.Trim() + "',";
//
//				strtemp = (char*)m_vTEMPMEMOINFO[i].TITLE;
//				asSqlQry = asSqlQry + "'" + strtemp.Trim() + "',";
//
//				strtemp = (char*)m_vTEMPMEMOINFO[i].MEMO;
//				asSqlQry = asSqlQry + "'" + strtemp.Trim() + "',";
//
//				strtemp =  (char*)m_vTEMPMEMOINFO[i].OWN_NAME;
//				asSqlQry = asSqlQry + "'" + strtemp.Trim() + "',";
//
//				strtemp =  (char*)m_vTEMPMEMOINFO[i].BATCH_YN;
//				asSqlQry = asSqlQry + "'" + strtemp.Trim() + "',";
//
//				strtemp =  (char*)m_vTEMPMEMOINFO[i].OPEN_YN;
//				asSqlQry = asSqlQry + "'" + strtemp.Trim() + "',";
//
//				strtemp =  (char*)m_vTEMPMEMOINFO[i].WRITE_ID;
//				asSqlQry = asSqlQry + "'" + strtemp.Trim() + "',";
//
//				strtemp =  (char*)m_vTEMPMEMOINFO[i].WRITE_DT;
//				asSqlQry = asSqlQry + "'" + strtemp.Trim() + "',";
//
//				asSqlQry = asSqlQry + m_vTEMPMEMOINFO[i].FILE_CNT + ",";
//				asSqlQry = asSqlQry + m_vTEMPMEMOINFO[i].DATA_CNT + ",";
//
//				asSqlQry = asSqlQry + m_vTEMPMEMOINFO[i].X + ",";
//				asSqlQry = asSqlQry + m_vTEMPMEMOINFO[i].Y + ");";
//
//				if(frmSql->func_QryProcess(asSqlQry) == false){
//					success = false;
//					frmMsg->funcMessageDlg("일괄등록:", "일괄등록을 실패하였습니다.", 2);
//					break;
//				}
//
//				strtemp = "";
//				Application->ProcessMessages();
//
//				//지번 VECTOR 저장//
//				frmMemo->m_asTempPoiKey = (char*)m_vTEMPMEMOVECTOR[i].POI_KEY;
//				funcWriteFileVectorLog(i);
//			}
//			Application->ProcessMessages();
//
//			asSqlQry = "COMMIT;";
//			frmSql->func_QryProcess(asSqlQry);
//
//			m_vTEMPMEMOINFO.clear();
//			m_vTEMPMEMOVECTOR.clear();
//
//			//======================================================================
//			//일괄 등록 (검색어 포함) 데이터 가져오기//
//			funcReadKeywordMemoInfo(edtFind->Text.Trim());
//
//			//======================================================================
//			//메모 모든 데이터 가져오기//
//			frmSql->funcReadDocumentMemoAll();
//			//======================================================================
//			//메모 영역 모든 데이터 가져오기//
//			frmMemo->m_vMEMOVECTOR.clear();
//			frmSql->m_vMEMOPOLY.clear();
//			for(int i = 0; i < (int)frmSql->m_vALLMEMOINFO.size(); i++)
//			{
//				if(frmSql->m_vALLMEMOINFO[i].DATA_CNT >= 3)
//				{
//					frmMemo->funcReadFileVectorLog(frmSql->m_vALLMEMOINFO[i].POI_KEY);
//					//200109//frmSql->funcReadDocumentMemoVector(frmSql->m_vALLMEMOINFO[i].POI_KEY);
//				}
//			}
//
//			frmMain->func_DrawImagePaint();//200120
//		}//funcCheckRawExcelData() return value is true
//	}
//}
////---------------------------------------------------------------------------

//일괄등록 데이터 - 사전검사//190724//RAWEXCEL//--------------------------------------------------
bool __fastcall TfrmMemoBatch::funcCheckRawExcelData()
{
	int rowcount = frmMemoRegist->sgResult->RowCount;
	int colcount = frmMemoRegist->sgResult->ColCount;

	int nCol = 0;
	bool bError = false;
	bool bDuple = false;
//	AnsiString asWhere = "";
	AnsiString 	asChkQry = "";
	AnsiString 	rTemp[6];
	AnsiString 	asPoiName = "";
	AnsiString 	asPnu = "";
	int			nIndex = -1;

	for(int i = 1; i < rowcount; i++){
		for(int j = 0; j < colcount; j++) rTemp[j] = "";//Init

		nCol = 0;
	    asPoiName = "";

		//NO
		rTemp[nCol] = frmMemoRegist->sgResult->Cells[nCol][i];
		if(rTemp[nCol].IsEmpty())
		{
			bError = true;
			frmMemoRegist->sgResult->FontColors[nCol][i] = clRed;
		}
		nCol++;

		//소재지-읍면동
		rTemp[nCol] = frmMemoRegist->sgResult->Cells[nCol][i];
		if(rTemp[nCol].IsEmpty())
		{
			bError = true;
			frmMemoRegist->sgResult->FontColors[nCol][i] = clRed;
		}
		asPoiName = asPoiName + rTemp[nCol];
		nCol++;

		//소재지-리
		rTemp[nCol] = frmMemoRegist->sgResult->Cells[nCol][i];
		if( !rTemp[nCol].IsEmpty() )
		    asPoiName = asPoiName + " " + rTemp[nCol];
		nCol++;

		//소재지-지번(산 포함)
		rTemp[nCol] = frmMemoRegist->sgResult->Cells[nCol][i];
		if(rTemp[nCol].IsEmpty())
		{
			bError = true;
			frmMemoRegist->sgResult->FontColors[nCol][i] = clRed;
		}
		asPoiName = asPoiName + " " + rTemp[nCol];
		nCol++;

//		//현 Shape에 지번정보 없으면 error로 보여준다//
//		asPnu = frmSql->func_ConvertAddressToLandcd(asPoiName, true);
//		if(asPnu.Length() != 19)
//		{
//			bError = true;
//			frmMemoRegist->sgResult->FontColors[nCol][i] = clRed;
//		}
//		nIndex = frmMain->func_readJibunIndex(asPnu) - 1;
//		if(nIndex <= -1)
//		{
//			bError = true;
//			frmMemoRegist->sgResult->FontColors[nCol][i] = clRed;
//		}

		//소유자-필수항목 아님//
		rTemp[nCol] = frmMemoRegist->sgResult->Cells[nCol][i];
		nCol++;

		//사업명
		rTemp[nCol] = frmMemoRegist->sgResult->Cells[nCol][i];
		if(rTemp[nCol].IsEmpty())
		{
			bError = true;
			frmMemoRegist->sgResult->FontColors[nCol][i] = clRed;
		}
		nCol++;

//   	//중복데이타 있는지 체크
//		asWhere = " WHERE POI_NAME = '" + asPoiName + "'";
//		asChkQry = "SELECT COUNT(*) FROM " + frmMain->TABLE_MEMOINFO + " + asWhere;
//
//		if(func_SQLRead_CheckAcceptCdkey(asChkQry))//데이타 존재//보여주기
//		{
//			bDuple = true;
//			frmMemoRegist->sgResult->FontColors[7][i] = clBlue;
//		}
	}

	if(bError)
	{
		frmMain->funcSetWaitWindows(false);
		Application->ProcessMessages();

		frmMsg->funcMessageDlg("데이타 오류 확인:", "오류 데이터(빨간색)를 확인하시고 일괄등록 엑셀 파일을 변경해주세요.", 2);

		if( !frmMemoRegist->Showing )
		{
			frmMemoRegist->Show();
		}
		else
		{
			frmMemoRegist->funcInitStringGrid();
			frmMemoRegist->funcDispStringGrid();
		}

		return false;
	}
	else if(bDuple)
	{
		frmMain->funcSetWaitWindows(false);
		Application->ProcessMessages();

		frmMsg->funcMessageDlg("데이타 중복 확인:", "중복 데이터(파란색)를 확인해주세요.", 2);

//		if( !frmMemoRegist->Showing )
//		{
//			frmMemoRegist->Show();
//		}
//		else
//		{
//			frmMemoRegist->funcInitStringGrid();
//			frmMemoRegist->funcDispStringGrid();
//		}

		return false;
	}

	return true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoBatch::IMGREGISTMouseEnter(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoBatch::IMGREGISTMouseLeave(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoBatch::IMGREGISTClick(TObject *Sender)
{
//
	if (FileOpenDialog1->Execute(Handle)) {
		UnicodeString sFileName = FileOpenDialog1->FileName;

		funcSetWaitWindows(true);
		Application->ProcessMessages();

		func_readExcelToWriteDB(sFileName);

		funcSetWaitWindows(false);
		Application->ProcessMessages();

		//query//func_ProcessList();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoBatch::funcInitStringGrid()
{
	for (int i = 1; i < sgResult->RowCount; i++) {
		sgResult->Rows[i]->Clear();
	}

	sgResult->RowCount = 2;

	for (int i = 0; i < 1; i++)
		for (int j = 0; j < sgResult->ColCount; j++)
			sgResult->Colors[j][i] = (TColor)RGB(221,232,254);//clInfoBk;
}
// ---------------------------------------------------------------------------
//
//void __fastcall TfrmMemoBatch::funcDispStringGrid()
//{
//	int nCol = 0;
//	AnsiString strTemp = "";
//
//	int nSize = (int)frmSql->m_vBATCHMEMOINFO.size();
//	if(nSize > 0)	sgResult->RowCount = nSize + 1;
//	else			sgResult->RowCount = 2;
//
//	for(int i = 1; i < nSize + 1; i++)
//	{
//		nCol = 0;
//		sgResult->Cells[nCol++][i] = frmSql->m_vBATCHMEMOINFO[i].POI_KEY;
//		sgResult->Cells[nCol++][i] = frmSql->m_vBATCHMEMOINFO[i].POI_NAME;
//		sgResult->Cells[nCol++][i] = frmSql->m_vBATCHMEMOINFO[i].TITLE;
//		sgResult->Cells[nCol++][i] = frmSql->m_vBATCHMEMOINFO[i].MEMO;
//		sgResult->Cells[nCol++][i] = frmUserManagement->funcReadUserName(AnsiString((char*)frmSql->m_vBATCHMEMOINFO[i].WRITE_ID));
//		sgResult->Cells[nCol++][i] = frmSql->m_vBATCHMEMOINFO[i].X;
//		sgResult->Cells[nCol++][i] = frmSql->m_vBATCHMEMOINFO[i].Y;
//	}
//}
//// ---------------------------------------------------------------------------
void __fastcall TfrmMemoBatch::funcDispStringGrid()
{
	int nCol = 0;
	AnsiString strTemp = "";

	int nSize = (int)frmSql->m_vBATCHMEMOINFO.size();
	if(nSize > 0)	sgResult->RowCount = nSize + 1;
	else			sgResult->RowCount = 2;

	for(int i = 1; i < nSize + 1; i++)
	{
		nCol = 0;
		sgResult->Cells[nCol++][i] = ""; // 선택
		sgResult->AddCheckBox(0, i, false, true);
		sgResult->Cells[nCol++][i] = frmSql->m_vBATCHMEMOINFO[i-1].POI_NAME;
		sgResult->Cells[nCol++][i] = frmSql->m_vBATCHMEMOINFO[i-1].TITLE;
		sgResult->Cells[nCol++][i] = "";//[TODO]//frmSql->m_vBATCHMEMOINFO[i].OWN_NAME;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMemoBatch::funcWriteFileVectorLog(int _nIndex)
{
	FILE 			*fd;
	AnsiString 		asFileName 	= frmMain->ROOTPATH + "vector" + frmMemo->m_asTempPoiKey + ".log";
	int         	nSize 		= (int)m_vTEMPMEMOVECTOR[_nIndex].VECTOR.size();
	GPoint			tempPoints;
	vector<GPoint>	vPoints;

	if(nSize == 0)
		return;

	vPoints.clear();
	for(int i = 0; i < nSize; i++)
	{
		memset(&tempPoints, 0x00, sizeof(GPoint));
		tempPoints.x	= m_vTEMPMEMOVECTOR[_nIndex].VECTOR[i].x;
		tempPoints.y	= m_vTEMPMEMOVECTOR[_nIndex].VECTOR[i].y;

		if(tempPoints.x <= 0 || tempPoints.y <= 0)
			continue;

		vPoints.push_back(tempPoints);
	}

	if(FileExists(asFileName))
		DeleteFile(asFileName);

	fd = fopen(asFileName.c_str(), "wb");//"w"로 했더니 2byte가 계속 붙어서 shape저장을 제대로 못했다//"wb"로 해야함.
	fseek(fd,0,SEEK_END);

	for(int i = 0; i < nSize; i++)
	{
		fwrite(&vPoints[i], sizeof(GPoint), 1, fd);
	}
	fclose(fd);


	DWORD dwFileSize = 0;
	//asFileName = StringReplace(asFullPath, asBasicPath, "", flags);
	dwFileSize = frmMemo->GetLocalFileSize(asFileName);

	if( (dwFileSize % sizeof(GPoint)) != 0)
	{
		frmMsg->funcMessageDlg("영역설정확인:", "영역데이터에 오류가 발견되었습니다. 다시 설정해주세요.", 3);
		return;
    }

	try{
		frmMemo->funcPutBinaryData(asFileName, nSize, dwFileSize);
	}
	__finally{
//		if(FileExists(asFileName))
//			DeleteFile(asFileName);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoBatch::edtHangeul_OnEnter(TObject *Sender)
{
	unsigned long Conversion, Sentence;
	HIMC Mode = ImmGetContext(Application->Handle);
	ImmGetConversionStatus(Mode, &Conversion, &Sentence);
	if (Conversion == IME_CMODE_HANGEUL){;}// 현재모드가 한글이면 패스
	else{                                  // 현재모드가 한글이 아니면 한/영키 누른 효과를준다.
		ImmSetConversionStatus(Mode, IME_CMODE_HANGEUL, IME_CMODE_HANGEUL);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoBatch::edtFindKeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN)
	{
		//200114//<검색어>없으면 <전체검색>
//		if(edtFind->Text.Trim().IsEmpty())
//		{
//			frmMsg->funcMessageDlg("검색어입력:", "사업명을 입력해주세요.", 3);
//			return;
//        }
		IMGFINDClick(IMGFIND);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoBatch::IMGFINDMouseEnter(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoBatch::IMGFINDMouseLeave(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoBatch::IMGFINDClick(TObject *Sender)
{
	try{
		funcReadKeywordMemoInfo(edtFind->Text.Trim());
	}
	__finally{
		int nSize = (int)frmSql->m_vBATCHMEMOINFO.size();
		lblCount->Caption = "조회건수: " + IntToStr(nSize) + " 건";
		lblCount->Visible = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoBatch::IMGDELETEMouseEnter(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoBatch::IMGDELETEMouseLeave(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoBatch::IMGDELETEClick(TObject *Sender)
{
	try{
		funcDeleteMemoInfo();
	}
	__finally{
    	IMGFINDClick(IMGFIND);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoBatch::sgResultGetAlignment(TObject *Sender, int ARow, int ACol,
          TAlignment &HAlign, TVAlignment &VAlign)
{
	HAlign = taCenter;
	VAlign = vtaCenter;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoBatch::sgResultClickCell(TObject *Sender, int ARow, int ACol)

{
	if(ARow > 0 && ACol == 0)
	{
		bool m_bCheck = false;
		sgResult->GetCheckBoxState(0, ARow, m_bCheck);
		m_bCheck = !m_bCheck;
		sgResult->SetCheckBoxState(0, ARow, m_bCheck);
		if(m_bCheck)
			m_nDelCount++;
		else
			m_nDelCount--;
	}

	if(m_nDelCount > 0)
		IMGDELETE->Enabled = true;
	else
		IMGDELETE->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoBatch::funcReadKeywordMemoInfo(AnsiString _asKeyword)
{
	frmSql->funcReadDocumentMemoBatch(_asKeyword);
	funcInitStringGrid();
	funcDispStringGrid();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoBatch::funcDeleteMemoInfo()
{
	bool m_bCheck;
	int index = 2;
	AnsiString asSqlQry;
	AnsiString asSqlWhere;
	AnsiString asPoiKey;
	AnsiString asSqlTbl = frmMain->TABLE_MEMOINFO;
	int size = sgResult->RowCount;

	for (int i = 1; i < size; i++) {
		m_bCheck = false;
		sgResult->GetCheckBoxState(0, i, m_bCheck);
		if (m_bCheck == true) {
			asPoiKey = (char*)frmSql->m_vBATCHMEMOINFO[i-1].POI_KEY;
			asSqlWhere 	= "POI_KEY = '" + asPoiKey.Trim() + "'";
			asSqlQry.sprintf("DELETE FROM %s WHERE %s", asSqlTbl, asSqlWhere);
			frmSql->func_QryProcess(asSqlQry);
		}
	}
}
//---------------------------------------------------------------------------

