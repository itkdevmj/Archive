#pragma link "bsSkinBoxCtrls"
#pragma link "bsSkinCtrls"
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
TfrmStat *frmStat;
//---------------------------------------------------------------------------
__fastcall TfrmStat::TfrmStat(TComponent* Owner)
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
		this->shpBG->Pen->Color		= (TColor)RGB(R, G, B);
		//shpWait->Pen->Color//
		this->shpWait->Pen->Color	= (TColor)RGB(R, G, B);
		//panWindowsMove->Color//
		this->panWindowsMove->Color	= (TColor)RGB(R, G, B);
		//pnlWaitT->Color//
		this->pnlWaitT->Color		= (TColor)RGB(R, G, B);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::FormCreate(TObject *Sender)
{
	funcCreateStatDoc8();

	//250710//[기능개선]사용자별 문서열람 현황
	funcCreateStatUserDoc();

	//250711//[기능개선]읍면동별 구축통계
	funcCreateStatDoc();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::FormShow(TObject *Sender)
{
	//=======================================================================
	// SET LOADED IMAGE
	//=======================================================================
	funcLoadButtonImage();

	btnCloseTypeB->Picture->Bitmap->Assign(frmMain->BITMAP_BTN_SYSTEM[frmMain->Close22]);

	funcReadUmdData();//220204//#STAT_DOC8//

	if(frmMain->INI_B_OWNNAMES)
	{
		TabSheet3->TabVisible	= true;
	}
	else
	{
		TabSheet3->TabVisible	= false;
	}

	PageControl1->ActivePage = TabSheet1;

	if(PageControl1->ActivePage == TabSheet1)
	{
		funcSetComboDoc();

		m_vStatDoc01.clear();
		m_vStatDoc02.clear();
		m_vStatDoc03.clear();
		m_vStatDoc04.clear();
		m_vStatDoc06.clear();
		m_vStatDoc07.clear();
		m_vStatDoc08.clear();
		m_vStatDoc09.clear();
		m_vStatDoc11.clear();
		m_vStatDoc15.clear();
		m_vStatDoc17.clear();
		m_vStatDoc18.clear();

		funcInitStat();
	}
	else if(PageControl1->ActivePage == TabSheet3)//구대장(한글화) 열람 통계//
	{
		funcInitTabStatDoc8();
	}

	//220207//FormShow 시에 자동 조회하지 말자//Timer1->Enabled  = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmStat::funcSetWaitWindows(bool bSetValue)
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
			if(m_nTargetDoc > 0)
			{
				lblCnt->Caption = "(0 / " + IntToStr(m_nTargetDoc) + ")";
				lblCnt->Visible = true;
			}
           	palWait->BringToFront();
        }
	}

	Application->ProcessMessages();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcLoadButtonImage()
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
	IMGFIND2->Picture->Bitmap->Assign(BITMAP_BTN_FIND[0]);//250710//
	IMGFIND3->Picture->Bitmap->Assign(BITMAP_BTN_FIND[0]);//220207//
	IMGFIND4->Picture->Bitmap->Assign(BITMAP_BTN_FIND[0]);//250711//
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcDeleteButtonImage()
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

void __fastcall TfrmStat::IMGSAVELOGMouseEnter(TObject *Sender)
{
	IMGSAVELOG->Picture->Bitmap->Handle  = NULL;
	IMGSAVELOG->Picture                  = NULL;
	IMGSAVELOG->Picture->Bitmap->Assign(BITMAP_BTN_SAVELOG[1]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::IMGSAVELOGMouseLeave(TObject *Sender)
{
	IMGSAVELOG->Picture->Bitmap->Handle  = NULL;
	IMGSAVELOG->Picture                  = NULL;
	IMGSAVELOG->Picture->Bitmap->Assign(BITMAP_BTN_SAVELOG[0]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::IMGSAVELOGClick(TObject *Sender)
{
	//=========================================================================================
	if(PageControl1->ActivePage == TabSheet1)//지적문서 구축통계//
	{
		if(m_nStatRowCount == 0)
		{
			frmMsg->funcMessageDlg("데이터부재 알림:", "저장할 데이터가 존재하지 않습니다.", 3);
			return;
		}

		UnicodeString sSheetName;

		//읍면동+리
		AnsiString 	asNow		= Now().FormatString("YYYYMMDD");
		AnsiString  asMsg		= "";

		sSheetName	= "지적문서_";
		if(chkYearLand->Checked)
			sSheetName	= sSheetName + "년도별&지역별_";
		if(chkDocKind->Checked)
			sSheetName	= sSheetName + "문서별건수_";

		if(frmMain->m_asSaveFileDir.IsEmpty())
			SaveDialog1->InitialDir = frmMain->DOWNLOADPATH;
		else
			SaveDialog1->InitialDir = frmMain->m_asSaveFileDir;

		SaveDialog1->FileName = sSheetName + asNow;
		if(SaveDialog1->Execute()){
			AnsiString 	asFileName = SaveDialog1->FileName;// + ".xls";
			if(FileExists(asFileName))
			{
				//=================================================
				//240307//파일 존재 시 다른이름으로 저장 처리//
				int z = 1;
				AnsiString  asDir	= ExtractFilePath(asFileName);
				while(FileExists(asFileName))
				{
					asFileName.sprintf("%s%s(%s) (%d).xls", asDir, (AnsiString)sSheetName, asNow, z++);
				}
				SaveDialog1->FileName	= asFileName;
				//=================================================
//				asMsg	= "파일이 존재합니다. 덮어쓰시겠습니까?";
//				frmMsg->funcMessageDlg("파일 중복 알림:", asMsg, 1);
//				if(frmMsg->m_bClick == 1)//Yes
//				{
//					DeleteFile(SaveDialog1->FileName);
//				}
//				else
//				{
//					IMGSAVELOGClick(NULL);
//					return;
//				}
			}

			frmMain->m_asSaveFileDir = ExtractFilePath(SaveDialog1->FileName);

			AnsiString asSaveFileName = ExtractFileName(asFileName);

			AdvGridExcelIO1->XLSExport((UnicodeString)asFileName, sSheetName, 1, 1, false);

			asMsg.sprintf("'%s' 엑셀파일 저장을 완료하였습니다.", asSaveFileName.c_str() );
			frmMsg->funcMessageDlg("저장 완료:", asMsg, 3);
		}
	}
	//=========================================================================================
	else if(PageControl1->ActivePage == TabSheet2)//사용자별 문서열람 현황//
	{
		if(m_nStatUserDocRowCount == 0)
		{
			frmMsg->funcMessageDlg("데이터부재 알림:", "저장할 데이터가 존재하지 않습니다.", 3);
			return;
		}

		UnicodeString sSheetName;

		//읍면동+리
		AnsiString 	asNow	= Now().FormatString("YYYYMMDD");
		AnsiString  asSttDt	= edtSttDt2->Date.FormatString("YYYYMMDD");
		AnsiString  asEndDt	= edtEndDt2->Date.FormatString("YYYYMMDD");
		AnsiString  asMsg	= "";

		sSheetName	= "사용자별 문서열람 현황";

		if(frmMain->m_asSaveFileDir.IsEmpty())
			SaveDialog1->InitialDir = frmMain->DOWNLOADPATH;
		else
			SaveDialog1->InitialDir = frmMain->m_asSaveFileDir;

		SaveDialog1->FileName = sSheetName + "_" + asNow + "(" + asSttDt + "_" + asEndDt + ")";
		if(SaveDialog1->Execute()){
			AnsiString 	asFileName = SaveDialog1->FileName;// + ".xls";
			if(FileExists(asFileName))
			{
				//=================================================
				//240307//파일 존재 시 다른이름으로 저장 처리//
				int z = 1;
				AnsiString  asDir	= ExtractFilePath(asFileName);
				while(FileExists(asFileName))
				{
					asFileName.sprintf("%s%s(%s) (%d).xls", asDir, (AnsiString)sSheetName, asNow, z++);
				}
				SaveDialog1->FileName	= asFileName;
				//=================================================
//				asMsg	= "파일이 존재합니다. 덮어쓰시겠습니까?";
//				frmMsg->funcMessageDlg("파일 중복 알림:", asMsg, 1);
//				if(frmMsg->m_bClick == 1)//Yes
//				{
//					DeleteFile(SaveDialog1->FileName);
//				}
//				else
//				{
//					IMGSAVELOGClick(NULL);
//					return;
//				}
			}

			frmMain->m_asSaveFileDir = ExtractFilePath(SaveDialog1->FileName);

			AnsiString asSaveFileName = ExtractFileName(asFileName);

			AdvGridExcelIO3->XLSExport((UnicodeString)asFileName, sSheetName, 1, 1, false);

			asMsg.sprintf("'%s' 엑셀파일 저장을 완료하였습니다.", asSaveFileName.c_str() );
			frmMsg->funcMessageDlg("저장 완료:", asMsg, 3);
		}
	}
	//=========================================================================================
	else if(PageControl1->ActivePage == TabSheet3)//구대장(한글화) 열람 통계//
	{
		if(m_nStatDoc8RowCount == 0)
		{
			frmMsg->funcMessageDlg("데이터부재 알림:", "저장할 데이터가 존재하지 않습니다.", 3);
			return;
		}

		UnicodeString sSheetName;

		//읍면동+리
		AnsiString 	asNow		= Now().FormatString("YYYYMMDD");
		AnsiString  asMsg		= "";

		sSheetName	= "구대장(한글화)_";
		//250708//[기능개선]구대장한글화 통계(+사용자별)
		if(rbUser->Checked)
			sSheetName	= sSheetName + "사용자별_";
		if(rbUmd->Checked)
			sSheetName	= sSheetName + "읍면동별_";
//		if(rbView->Checked)
//			sSheetName	= sSheetName + "열람_";
//		if(rbPrint->Checked)
//			sSheetName	= sSheetName + "인쇄_";

		if(frmMain->m_asSaveFileDir.IsEmpty())
			SaveDialog1->InitialDir = frmMain->DOWNLOADPATH;
		else
			SaveDialog1->InitialDir = frmMain->m_asSaveFileDir;

		SaveDialog1->FileName = sSheetName + asNow;
		if(SaveDialog1->Execute()){
			AnsiString 	asFileName = SaveDialog1->FileName;// + ".xls";
			if(FileExists(asFileName))
			{
				//=================================================
				//240307//파일 존재 시 다른이름으로 저장 처리//
				int z = 1;
				AnsiString  asDir	= ExtractFilePath(asFileName);
				while(FileExists(asFileName))
				{
					asFileName.sprintf("%s%s(%s) (%d).xls", asDir, (AnsiString)sSheetName, asNow, z++);
				}
				SaveDialog1->FileName	= asFileName;
				//=================================================
//				asMsg	= "파일이 존재합니다. 덮어쓰시겠습니까?";
//				frmMsg->funcMessageDlg("파일 중복 알림:", asMsg, 1);
//				if(frmMsg->m_bClick == 1)//Yes
//				{
//					DeleteFile(SaveDialog1->FileName);
//				}
//				else
//				{
//					IMGSAVELOGClick(NULL);
//					return;
//				}
			}

			frmMain->m_asSaveFileDir = ExtractFilePath(SaveDialog1->FileName);

			AnsiString asSaveFileName = ExtractFileName(asFileName);

			AdvGridExcelIO2->XLSExport((UnicodeString)asFileName, sSheetName, 1, 1, false);

			asMsg.sprintf("'%s' 엑셀파일 저장을 완료하였습니다.", asSaveFileName.c_str() );
			frmMsg->funcMessageDlg("저장 완료:", asMsg, 3);
		}
	}
	//=========================================================================================
	else if(PageControl1->ActivePage == TabSheet4)//읍면동별 구축통계//
	{
		if(m_nStatDocRowCount == 0)
		{
			frmMsg->funcMessageDlg("데이터부재 알림:", "저장할 데이터가 존재하지 않습니다.", 3);
			return;
		}

		UnicodeString sSheetName;

		//읍면동+리
		AnsiString 	asNow	= Now().FormatString("YYYYMMDD");
		AnsiString  asMsg	= "";

		sSheetName	= "읍면동별 구축통계 현황";
		if(rbUmdPath->Checked)
			sSheetName	+= "(문서 면수 기준)";
		else
			sSheetName	+= "(데이터 건수 기준)";

		if(frmMain->m_asSaveFileDir.IsEmpty())
			SaveDialog1->InitialDir = frmMain->DOWNLOADPATH;
		else
			SaveDialog1->InitialDir = frmMain->m_asSaveFileDir;

		SaveDialog1->FileName = sSheetName + "_" + asNow;
		if(SaveDialog1->Execute()){
			AnsiString 	asFileName = SaveDialog1->FileName;// + ".xls";
			if(FileExists(asFileName))
			{
				//=================================================
				//240307//파일 존재 시 다른이름으로 저장 처리//
				int z = 1;
				AnsiString  asDir	= ExtractFilePath(asFileName);
				//=====================================================================
				while(FileExists(asFileName))
				{
					asFileName.sprintf("%s%s(%s) (%d).xls", asDir, (AnsiString)sSheetName, asNow, z++);
				}
				SaveDialog1->FileName	= asFileName;
				//=================================================
//				asMsg	= "파일이 존재합니다. 덮어쓰시겠습니까?";
//				frmMsg->funcMessageDlg("파일 중복 알림:", asMsg, 1);
//				if(frmMsg->m_bClick == 1)//Yes
//				{
//					DeleteFile(SaveDialog1->FileName);
//				}
//				else
//				{
//					IMGSAVELOGClick(NULL);
//					return;
//				}
			}

			frmMain->m_asSaveFileDir = ExtractFilePath(SaveDialog1->FileName);

			AnsiString asSaveFileName = ExtractFileName(asFileName);

			AdvGridExcelIO4->XLSExport((UnicodeString)asFileName, sSheetName, 1, 1, false);

			asMsg.sprintf("'%s' 엑셀파일 저장을 완료하였습니다.", asSaveFileName.c_str() );
			frmMsg->funcMessageDlg("저장 완료:", asMsg, 3);
		}
	}
	//=========================================================================================
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::IMGEXITMouseEnter(TObject *Sender)
{
	IMGEXIT->Picture->Bitmap->Handle  = NULL;
	IMGEXIT->Picture                  = NULL;
	IMGEXIT->Picture->Bitmap->Assign(BITMAP_BTN_EXIT[1]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::IMGEXITMouseLeave(TObject *Sender)
{
	IMGEXIT->Picture->Bitmap->Handle  = NULL;
	IMGEXIT->Picture                  = NULL;
	IMGEXIT->Picture->Bitmap->Assign(BITMAP_BTN_EXIT[0]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::IMGEXITClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(PageControl1->ActivePage == TabSheet1)
	{
		m_vStatDoc01.clear();
		m_vStatDoc02.clear();
		m_vStatDoc03.clear();
		m_vStatDoc04.clear();
		m_vStatDoc06.clear();
		m_vStatDoc07.clear();
		m_vStatDoc08.clear();
		m_vStatDoc09.clear();
		m_vStatDoc11.clear();
		m_vStatDoc15.clear();
		m_vStatDoc17.clear();
		m_vStatDoc18.clear();

		funcInitStat();
	}
	else if(PageControl1->ActivePage == TabSheet3)//구대장(한글화) 열람 통계//
	{
		funcInitTabStatDoc8();
	}

	//읍면동별 구축통계 - 리스트 해제//
	funcInitStringList(false);

	funcDeleteButtonImage();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::btnCloseTypeBClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::IMGFINDMouseEnter(TObject *Sender)
{
	if(Sender == IMGFIND)
	{
		IMGFIND->Picture->Bitmap->Handle  = NULL;
		IMGFIND->Picture                  = NULL;
		IMGFIND->Picture->Bitmap->Assign(BITMAP_BTN_FIND[1]);
	}
	else if(Sender == IMGFIND2)
	{
		IMGFIND2->Picture->Bitmap->Handle  = NULL;
		IMGFIND2->Picture                  = NULL;
		IMGFIND2->Picture->Bitmap->Assign(BITMAP_BTN_FIND[1]);
	}
	else if(Sender == IMGFIND3)
	{
		IMGFIND3->Picture->Bitmap->Handle  = NULL;
		IMGFIND3->Picture                  = NULL;
		IMGFIND3->Picture->Bitmap->Assign(BITMAP_BTN_FIND[1]);
	}
	else if(Sender == IMGFIND4)
	{
		IMGFIND4->Picture->Bitmap->Handle  = NULL;
		IMGFIND4->Picture                  = NULL;
		IMGFIND4->Picture->Bitmap->Assign(BITMAP_BTN_FIND[1]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::IMGFINDMouseLeave(TObject *Sender)
{
	if(Sender == IMGFIND)
	{
		IMGFIND->Picture->Bitmap->Handle  = NULL;
		IMGFIND->Picture                  = NULL;
		IMGFIND->Picture->Bitmap->Assign(BITMAP_BTN_FIND[0]);
	}
	else if(Sender == IMGFIND2)
	{
		IMGFIND2->Picture->Bitmap->Handle  = NULL;
		IMGFIND2->Picture                  = NULL;
		IMGFIND2->Picture->Bitmap->Assign(BITMAP_BTN_FIND[0]);
	}
	else if(Sender == IMGFIND3)
	{
		IMGFIND3->Picture->Bitmap->Handle  = NULL;
		IMGFIND3->Picture                  = NULL;
		IMGFIND3->Picture->Bitmap->Assign(BITMAP_BTN_FIND[0]);
	}
	else if(Sender == IMGFIND4)
	{
		IMGFIND4->Picture->Bitmap->Handle  = NULL;
		IMGFIND4->Picture                  = NULL;
		IMGFIND4->Picture->Bitmap->Assign(BITMAP_BTN_FIND[0]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::IMGFINDClick(TObject *Sender)
{
	//=====================================================
	if(Sender == IMGFIND)//지적문서 구축통계//
	{
		if( frmAlphaDoc8->Showing )//220118//
			frmAlphaDoc8->Close();
		if( frmDoc8View->Showing )//221208//#PRINT_IMPROVE//
			frmDoc8View->Close();

		if( !chkYearLand->Checked && !chkDocKind->Checked)
		{
			frmMsg->funcMessageDlg("선택 확인:", "년도별/지역별 또는 문서구분별 중 한 개 이상 체크해주세요.", 3);
			return;
		}

		funcSetWaitWindows(true);
		//
		for (int i = 0; i < sgStat->RowCount; i++) {
			sgStat->Rows[i]->Clear();
		}
		m_nStatRowCount	= 0;
		//
		funcReadStat();

		funcDispStat();

		funcSetWaitWindows(false);
	}
	//=====================================================
	else if(Sender == IMGFIND2)//사용자별 문서열람 현황//
	{
//		//250708//[기능개선]구대장한글화 통계(+사용자별)
//		if( !chkView->Checked && !chkPrint->Checked && !chkDirect->Checked )
//		{
//			frmMsg->funcMessageDlg("선택 확인:", "[업무 유형]을 선택해 주세요.", 3);
//			return;
//		}


		funcSetWaitWindows(true);

		funcReadStatUserDoc();

		funcSetWaitWindows(false);
	}
	//=====================================================
	else if(Sender == IMGFIND3)//구대장(한글화) 열람 통계//
	{
		//250708//[기능개선]구대장한글화 통계(+사용자별)
		if( !chkView->Checked && !chkPrint->Checked && !chkDirect->Checked )
		{
			frmMsg->funcMessageDlg("선택 확인:", "[업무 유형]을 선택해 주세요.", 3);
			return;
		}


		funcSetWaitWindows(true);

		//250708//[기능개선]구대장한글화 통계(+사용자별)
		if(rbUser->Checked)//사용자별//
			funcReadStatDoc8_User();
		else//if(rbUmd->Checked)//읍면동별//
			funcReadStatDoc8();

		funcSetWaitWindows(false);
	}
	//=====================================================
	else if(Sender == IMGFIND4)//읍면동별 구축통계//
	{
		//읍면동별 구축통계 - 리스트 초기화//
		funcInitStringList(false);
		funcInitStringList(true);

		m_nTargetDoc = 0;
		for(int i = 1; i < DF_DOC_CNT; i++)
		{
			if( (i <= 4) || (i >= 6 && i <= 9) || (i >= 17 && i <= 18) )
			{
				if( frmMain->INIINFO.B_DOCKIND[i] )
					m_nTargetDoc++;
			}
		}

		funcSetWaitWindows(true);

		int nCnt = 0;
		for(int i = 1; i < DF_DOC_CNT; i++)
		{
			if( (i <= 4) || (i >= 6 && i <= 9) || (i >= 17 && i <= 18) )
			{
				if( frmMain->INIINFO.B_DOCKIND[i] )
				{
					funcReadStatDoc(i);
					nCnt++;
					lblCnt->Caption = "(" + IntToStr(nCnt) + " / " + IntToStr(m_nTargetDoc) + ")";
					Application->ProcessMessages();
				}
			}
		}

		funcDispStatDoc();

		funcSetWaitWindows(false);
	}
	//=====================================================
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(frmStat->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::sgStatGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign, TVAlignment &VAlign)
{
	HAlign = taCenter;
	VAlign = vtaCenter;
}
//---------------------------------------------------------------------------




//####################################################
//
// 통계보기//
//
//####################################################
//Init UI
void __fastcall TfrmStat::funcInitStat()
{
	int nCol 	= 0;
	int nKind 	= 3;

	sgStat->DefaultColWidth     = 120;

	if( !chkYearLand->Checked )
		nKind	= 2;
	if( !chkDocKind->Checked )
		nKind	= 2;

	if(m_nDocCount * nKind == 12)
	{
		sgStat->ColCount = 13;//12이상은 Dummy.[Caution]Builder2010_Bug. AdvStringGrid.ColCount 12으로 설정하면 MemoryOverFlow or Invalid Pointer Operatioin 발생//		sgStat->ColWidths[12]	= 0;
		sgStat->ColWidths[12]	= 0;
	}
	else
	{
		sgStat->ColCount    = m_nDocCount * nKind;
	}
	sgStat->RowCount    = m_nStatRowCount + 3;
	sgStat->FixedRows   = 2;
	sgStat->FixedCols   = 0;
	//---
	if(chkDoc01->Checked)
	{
		sgStat->MergeCells(nCol, 0, nKind, 1);
		sgStat->Cells[nCol][0]     	= chkDoc01->Caption;
		if( chkYearLand->Checked )
			sgStat->Cells[nCol++][1]  	= "구축년도";
		if( chkDocKind->Checked )
			sgStat->Cells[nCol++][1]	= "문서구분";
		sgStat->Cells[nCol++][1]		= "건수(매수)";
	}
	//---
	if(chkDoc02->Checked)
	{
		sgStat->MergeCells(nCol, 0, nKind, 1);
		sgStat->Cells[nCol][0]		= chkDoc02->Caption;
		if( chkYearLand->Checked )
			sgStat->Cells[nCol++][1]  	= "구축년도";
		if( chkDocKind->Checked )
			sgStat->Cells[nCol++][1]	= "문서구분";
		sgStat->Cells[nCol++][1]		= "건수(매수)";
	}
	//---
	if(chkDoc03->Checked)
	{
		sgStat->MergeCells(nCol, 0, nKind, 1);
		sgStat->Cells[nCol][0]     	= chkDoc03->Caption;
		if( chkYearLand->Checked )
			sgStat->Cells[nCol++][1]  	= "구축년도";
		if( chkDocKind->Checked )
			sgStat->Cells[nCol++][1]	= "문서구분";
		sgStat->Cells[nCol++][1]		= "건수(매수)";
	}
	//---
	if(chkDoc04->Checked)
	{
		sgStat->MergeCells(nCol, 0, nKind, 1);
		sgStat->Cells[nCol][0]     	= chkDoc04->Caption;
		if( chkYearLand->Checked )
			sgStat->Cells[nCol++][1]  	= "구축년도";
		if( chkDocKind->Checked )
			sgStat->Cells[nCol++][1]	= "문서구분";
		sgStat->Cells[nCol++][1]		= "건수(매수)";
	}
	//---
	if(chkDoc06->Checked)
	{
		sgStat->MergeCells(nCol, 0, nKind, 1);
		sgStat->Cells[nCol][0]     	= chkDoc06->Caption;
		if( chkYearLand->Checked )
			sgStat->Cells[nCol++][1]  	= "구축년도";
		if( chkDocKind->Checked )
			sgStat->Cells[nCol++][1]	= "문서구분";
		sgStat->Cells[nCol++][1]		= "건수(매수)";
	}
	//---
	if(chkDoc09->Checked)
	{
		sgStat->MergeCells(nCol, 0, nKind, 1);
		sgStat->Cells[nCol][0]     	= chkDoc09->Caption;
		if( chkYearLand->Checked )
			sgStat->Cells[nCol++][1]  	= "구축년도";
		if( chkDocKind->Checked )
			sgStat->Cells[nCol++][1]	= "문서구분";
		sgStat->Cells[nCol++][1]		= "건수(매수)";
	}
	//---
	if(chkDoc11->Checked)
	{
		sgStat->MergeCells(nCol, 0, nKind, 1);
		sgStat->Cells[nCol][0]     	= chkDoc11->Caption;
		if( chkYearLand->Checked )
			sgStat->Cells[nCol++][1]  	= "구축년도";
		if( chkDocKind->Checked )
			sgStat->Cells[nCol++][1]	= "문서구분";
		sgStat->Cells[nCol++][1]		= "건수(매수)";
	}
	//---
	if(chkDoc15->Checked)
	{
		sgStat->MergeCells(nCol, 0, nKind, 1);
		sgStat->Cells[nCol][0]     	= chkDoc15->Caption;
		if( chkYearLand->Checked )
			sgStat->Cells[nCol++][1]  	= "구축년도";
		if( chkDocKind->Checked )
			sgStat->Cells[nCol++][1]	= "문서구분";
		sgStat->Cells[nCol++][1]		= "건수(매수)";
	}
	//---
	if(chkDoc17->Checked)
	{
		sgStat->MergeCells(nCol, 0, nKind, 1);
		sgStat->Cells[nCol][0]     	= chkDoc17->Caption;
		if( chkYearLand->Checked )
			sgStat->Cells[nCol++][1]  	= "구축년도";
		if( chkDocKind->Checked )
			sgStat->Cells[nCol++][1]	= "문서구분";
		sgStat->Cells[nCol++][1]		= "건수(매수)";
	}
	//---
	if(chkDoc18->Checked)
	{
		sgStat->MergeCells(nCol, 0, nKind, 1);
		sgStat->Cells[nCol][0]     	= chkDoc18->Caption;
		if( chkYearLand->Checked )
			sgStat->Cells[nCol++][1]  	= "구축년도";
		if( chkDocKind->Checked )
			sgStat->Cells[nCol++][1]	= "문서구분";
		sgStat->Cells[nCol++][1]		= "건수(매수)";
	}
	//---
	if(chkDoc07->Checked)
	{
		sgStat->MergeCells(nCol, 0, nKind, 1);
		sgStat->Cells[nCol][0]     	= chkDoc07->Caption;
		if( chkYearLand->Checked )
			sgStat->Cells[nCol++][1]  	= "지역별";
		if( chkDocKind->Checked )
			sgStat->Cells[nCol++][1]	= "문서구분";
		sgStat->Cells[nCol++][1]		= "건수(매수)";
	}
	//---
	if(chkDoc08->Checked)
	{
		sgStat->MergeCells(nCol, 0, nKind, 1);
		sgStat->Cells[nCol][0]     	= chkDoc08->Caption;
		if( chkYearLand->Checked )
			sgStat->Cells[nCol++][1]  	= "지역별";
		if( chkDocKind->Checked )
			sgStat->Cells[nCol++][1]	= "문서구분";
		sgStat->Cells[nCol++][1]		= "건수(매수)";
	}

	for(int i = 0; i < sgStat->ColCount; i++)
	{
		sgStat->FontStyles[i][0]	= TFontStyles() << fsBold;
		sgStat->Colors[i][0]		= (TColor)RGB( 219, 238, 243);
		sgStat->FontStyles[i][1]	= TFontStyles() << fsBold;
		sgStat->Colors[i][1]		= (TColor)RGB( 219, 238, 243);
	}

	::UpdateWindow(sgStat->Handle);

}
// ---------------------------------------------------------------------------

void __fastcall TfrmStat::funcDispStat()
{
	funcInitStat();

	int 		nCol 	= 0;
	int 		nCurCol = 0;//다음 문서 첫번째 컬럼 기억//
	AnsiString 	asStr   = "";
	int	 		nGrade	= 0;
	int         nSize	= 0;
	int			nIndex	= 3;
	int 		nKind 	= 3;
	int			n1ColBgColor	= 210;
	int			n1ColFgColor	= 255;
	TColor		cKindCodeColor	= (TColor)RGB( 221, 240, 255 );//(TColor)RGB( 114, 155, 228 );
	int 		*nSumCount 	= new int[m_nDocCount];
	int			nDocIndex	= 0;//nSumCount.index//

	for (int i = 0; i < m_nDocCount; i++)
		nSumCount[i]	= 0;

	if( !chkYearLand->Checked )
		nKind	= 2;
	if( !chkDocKind->Checked )
		nKind	= 2;

	sgStat->RowCount	= m_nStatRowCount;

	//---토지이동결의서---//
	nSize	= (int)m_vStatDoc01.size();
	nIndex	= 3;
	for (int i = 0; i < nSize; i++)
	{
		nCol	= 0;
		asStr	= "";
		//color//		sgStat->RowColor[nIndex] = clWhite;

		//구축년도//
		if(chkYearLand->Checked)
		{
			sgStat->Colors[nCol][nIndex]   	= (TColor)RGB( n1ColBgColor, n1ColBgColor, n1ColBgColor );
			//sgStat->FontColors[nCol][nRow]	= (TColor)RGB( n1ColFgColor, n1ColFgColor, n1ColFgColor );
			asStr	= (char*)m_vStatDoc01[i].YEAR;
			sgStat->Cells[nCol++][nIndex]  = asStr;
		}
		//문서구분//
		if(chkDocKind->Checked)
		{
			sgStat->Colors[nCol][nIndex] 	= cKindCodeColor;
			asStr	= (char*)m_vStatDoc01[i].KIND_CODE;
			sgStat->Cells[nCol++][nIndex]	= eFunc->funcGetKindCodeToKindName(1, asStr.c_str());
		}
		//개수//
		sgStat->Cells[nCol++][nIndex]  	= FormatFloat("#,##0", m_vStatDoc01[i].COUNT);
		nSumCount[nDocIndex]	+= m_vStatDoc01[i].COUNT;//220107//
		nIndex++;
	}
	if(nSize > 0)
	{
		//합계
		sgStat->FontStyles[nCurCol][1]		= TFontStyles() << fsBold;
		sgStat->Cells[nCurCol][2]			= "합계";
		sgStat->FontColors[nCurCol][2]		= (TColor)RGB( 255, 0, 0);
		sgStat->FontStyles[nCurCol+1][1]	= TFontStyles() << fsBold;
		sgStat->Cells[nCurCol+1][2]			= FormatFloat("#,##0", nSumCount[nDocIndex]);
		sgStat->FontColors[nCurCol+1][2]	= (TColor)RGB( 255, 0, 0);

		nCurCol	= nCol;
		nDocIndex++;//220107//
	}
	else
	{
		nCurCol	+= nKind;
	}

	//---측량결과도---//
	nSize	= (int)m_vStatDoc02.size();
	nIndex	= 3;
	for (int i = 0; i < nSize; i++)
	{
		nCol	= nCurCol;
		asStr	= "";
		//color//		sgStat->RowColor[nIndex] = clWhite;

		//구축년도//
		if(chkYearLand->Checked)
		{
			sgStat->Colors[nCol][nIndex]   	= (TColor)RGB( n1ColBgColor, n1ColBgColor, n1ColBgColor );
			//sgStat->FontColors[nCol][nRow]	= (TColor)RGB( n1ColFgColor, n1ColFgColor, n1ColFgColor );
			asStr	= (char*)m_vStatDoc02[i].YEAR;
			sgStat->Cells[nCol++][nIndex]	= asStr;
		}
		//문서구분//
		if(chkDocKind->Checked)
		{
			sgStat->Colors[nCol][nIndex] 	= cKindCodeColor;
			asStr	= (char*)m_vStatDoc02[i].KIND_CODE;
			sgStat->Cells[nCol++][nIndex]  	= eFunc->funcGetKindCodeToKindName(2, asStr.c_str());
		}
		//개수//
		sgStat->Cells[nCol++][nIndex]  	= FormatFloat("#,##0", m_vStatDoc02[i].COUNT);
		nSumCount[nDocIndex]	+= m_vStatDoc02[i].COUNT;//220107//
		nIndex++;
	}
	if(nSize > 0)
	{
		//합계
		sgStat->FontStyles[nCurCol][1]		= TFontStyles() << fsBold;
		sgStat->Cells[nCurCol][2]			= "합계";
		sgStat->FontColors[nCurCol][2]		= (TColor)RGB( 255, 0, 0);
		sgStat->FontStyles[nCurCol+1][1]	= TFontStyles() << fsBold;
		sgStat->Cells[nCurCol+1][2]			= FormatFloat("#,##0", nSumCount[nDocIndex]);
		sgStat->FontColors[nCurCol+1][2]	= (TColor)RGB( 255, 0, 0);

		nCurCol	= nCol;
		nDocIndex++;//220107//
	}
	else
	{
		nCurCol	+= nKind;
	}

	//---면적측정부---//
	nSize	= (int)m_vStatDoc03.size();
	nIndex	= 3;
	for (int i = 0; i < nSize; i++)
	{
		nCol	= nCurCol;
		asStr	= "";
		//color//		sgStat->RowColor[nIndex] = clWhite;

		//구축년도//
		if(chkYearLand->Checked)
		{
			sgStat->Colors[nCol][nIndex]   	= (TColor)RGB( n1ColBgColor, n1ColBgColor, n1ColBgColor );
			//sgStat->FontColors[nCol][nRow]	= (TColor)RGB( n1ColFgColor, n1ColFgColor, n1ColFgColor );
			asStr	= (char*)m_vStatDoc03[i].YEAR;
			sgStat->Cells[nCol++][nIndex]   = asStr;
		}
		//문서구분//
		if(chkDocKind->Checked)
		{
			sgStat->Colors[nCol][nIndex] 	= cKindCodeColor;
			asStr	= (char*)m_vStatDoc03[i].KIND_CODE;
			sgStat->Cells[nCol++][nIndex]   = eFunc->funcGetKindCodeToKindName(3, asStr.c_str());
		}
		//개수//
		sgStat->Cells[nCol++][nIndex]   = FormatFloat("#,##0", m_vStatDoc03[i].COUNT);
		nSumCount[nDocIndex]	+= m_vStatDoc03[i].COUNT;//220107//
		nIndex++;
	}
	if(nSize > 0)
	{
		//합계
		sgStat->FontStyles[nCurCol][1]		= TFontStyles() << fsBold;
		sgStat->Cells[nCurCol][2]			= "합계";
		sgStat->FontColors[nCurCol][2]		= (TColor)RGB( 255, 0, 0);
		sgStat->FontStyles[nCurCol+1][1]	= TFontStyles() << fsBold;
		sgStat->Cells[nCurCol+1][2]			= FormatFloat("#,##0", nSumCount[nDocIndex]);
		sgStat->FontColors[nCurCol+1][2]	= (TColor)RGB( 255, 0, 0);

		nCurCol	= nCol;
		nDocIndex++;//220107//
	}
	else
	{
		nCurCol	+= nKind;
	}

	//---부동산특조법---//
	nSize	= (int)m_vStatDoc04.size();
	nIndex	= 3;
	for (int i = 0; i < nSize; i++)
	{
		nCol	= nCurCol;
		asStr	= "";
		//color//		sgStat->RowColor[nIndex] = clWhite;

		//구축년도//
		if(chkYearLand->Checked)
		{
			sgStat->Colors[nCol][nIndex]   	= (TColor)RGB( n1ColBgColor, n1ColBgColor, n1ColBgColor );
			//sgStat->FontColors[nCol][nRow]	= (TColor)RGB( n1ColFgColor, n1ColFgColor, n1ColFgColor );
			asStr	= (char*)m_vStatDoc04[i].YEAR;
			sgStat->Cells[nCol++][nIndex]   = asStr;
		}
		//문서구분//
		if(chkDocKind->Checked)
		{
			sgStat->Colors[nCol][nIndex] 	= cKindCodeColor;
			asStr	= (char*)m_vStatDoc04[i].KIND_CODE;
			sgStat->Cells[nCol++][nIndex]   = eFunc->funcGetKindCodeToKindName(4, asStr.c_str());
		}
		//개수//
		sgStat->Cells[nCol++][nIndex]   = FormatFloat("#,##0", m_vStatDoc04[i].COUNT);
		nSumCount[nDocIndex]	+= m_vStatDoc04[i].COUNT;//220107//
		nIndex++;
	}
	if(nSize > 0)
	{
		//합계
		sgStat->FontStyles[nCurCol][1]		= TFontStyles() << fsBold;
		sgStat->Cells[nCurCol][2]			= "합계";
		sgStat->FontColors[nCurCol][2]		= (TColor)RGB( 255, 0, 0);
		sgStat->FontStyles[nCurCol+1][1]	= TFontStyles() << fsBold;
		sgStat->Cells[nCurCol+1][2]			= FormatFloat("#,##0", nSumCount[nDocIndex]);
		sgStat->FontColors[nCurCol+1][2]	= (TColor)RGB( 255, 0, 0);

		nCurCol	= nCol;
		nDocIndex++;//220107//
	}
	else
	{
		nCurCol	+= nKind;
	}

	//---환지계획서---//
	nSize	= (int)m_vStatDoc06.size();
	nIndex	= 3;
	for (int i = 0; i < nSize; i++)
	{
		nCol	= nCurCol;
		asStr	= "";
		//color//		sgStat->RowColor[nIndex] = clWhite;

		//구축년도//
		if(chkYearLand->Checked)
		{
			sgStat->Colors[nCol][nIndex]   	= (TColor)RGB( n1ColBgColor, n1ColBgColor, n1ColBgColor );
			//sgStat->FontColors[nCol][nRow]	= (TColor)RGB( n1ColFgColor, n1ColFgColor, n1ColFgColor );
			asStr	= (char*)m_vStatDoc06[i].YEAR;
			sgStat->Cells[nCol++][nIndex]   = asStr;
		}
		//문서구분//
		if(chkDocKind->Checked)
		{
			sgStat->Colors[nCol][nIndex] 	= cKindCodeColor;
			asStr	= (char*)m_vStatDoc06[i].KIND_CODE;
			sgStat->Cells[nCol++][nIndex]   = eFunc->funcGetKindCodeToKindName(6, asStr.c_str());
		}
		//개수//
		sgStat->Cells[nCol++][nIndex]   = FormatFloat("#,##0", m_vStatDoc06[i].COUNT);
		nSumCount[nDocIndex]	+= m_vStatDoc06[i].COUNT;//220107//
		nIndex++;
	}
	if(nSize > 0)
	{
		//합계
		sgStat->FontStyles[nCurCol][1]		= TFontStyles() << fsBold;
		sgStat->Cells[nCurCol][2]			= "합계";
		sgStat->FontColors[nCurCol][2]		= (TColor)RGB( 255, 0, 0);
		sgStat->FontStyles[nCurCol+1][1]	= TFontStyles() << fsBold;
		sgStat->Cells[nCurCol+1][2]			= FormatFloat("#,##0", nSumCount[nDocIndex]);
		sgStat->FontColors[nCurCol+1][2]	= (TColor)RGB( 255, 0, 0);

		nCurCol	= nCol;
		nDocIndex++;//220107//
	}
	else
	{
		nCurCol	+= nKind;
	}

	//---공시지가---//
	nSize	= (int)m_vStatDoc09.size();
	nIndex	= 3;
	for (int i = 0; i < nSize; i++)
	{
		nCol	= nCurCol;
		asStr	= "";
		//color//		sgStat->RowColor[nIndex] = clWhite;

		//구축년도//
		if(chkYearLand->Checked)
		{
			sgStat->Colors[nCol][nIndex]   	= (TColor)RGB( n1ColBgColor, n1ColBgColor, n1ColBgColor );
			//sgStat->FontColors[nCol][nRow]	= (TColor)RGB( n1ColFgColor, n1ColFgColor, n1ColFgColor );
			asStr	= (char*)m_vStatDoc09[i].YEAR;
			sgStat->Cells[nCol++][nIndex]   = asStr;
		}
		//문서구분//
		if(chkDocKind->Checked)
		{
			sgStat->Colors[nCol][nIndex] 	= cKindCodeColor;
			asStr	= (char*)m_vStatDoc09[i].KIND_CODE;
			sgStat->Cells[nCol++][nIndex]   = eFunc->funcGetKindCodeToKindName(9, asStr.c_str());
		}
		//개수//
		sgStat->Cells[nCol++][nIndex]   = FormatFloat("#,##0", m_vStatDoc09[i].COUNT);
		nSumCount[nDocIndex]	+= m_vStatDoc09[i].COUNT;//220107//
		nIndex++;
	}
	if(nSize > 0)
	{
		//합계
		sgStat->FontStyles[nCurCol][1]		= TFontStyles() << fsBold;
		sgStat->Cells[nCurCol][2]			= "합계";
		sgStat->FontColors[nCurCol][2]		= (TColor)RGB( 255, 0, 0);
		sgStat->FontStyles[nCurCol+1][1]	= TFontStyles() << fsBold;
		sgStat->Cells[nCurCol+1][2]			= FormatFloat("#,##0", nSumCount[nDocIndex]);
		sgStat->FontColors[nCurCol+1][2]	= (TColor)RGB( 255, 0, 0);

		nCurCol	= nCol;
		nDocIndex++;//220107//
	}
	else
	{
		nCurCol	+= nKind;
	}

	//---지적경계정비---//
	nSize	= (int)m_vStatDoc11.size();
	nIndex	= 3;
	for (int i = 0; i < nSize; i++)
	{
		nCol	= nCurCol;
		asStr	= "";
		//color//		sgStat->RowColor[nIndex] = clWhite;

		//구축년도//
		if(chkYearLand->Checked)
		{
			sgStat->Colors[nCol][nIndex]   	= (TColor)RGB( n1ColBgColor, n1ColBgColor, n1ColBgColor );
			//sgStat->FontColors[nCol][nRow]	= (TColor)RGB( n1ColFgColor, n1ColFgColor, n1ColFgColor );
			asStr	= (char*)m_vStatDoc11[i].YEAR;
			sgStat->Cells[nCol++][nIndex]   = asStr;
		}
		//문서구분//
		if(chkDocKind->Checked)
		{
			sgStat->Colors[nCol][nIndex] 	= cKindCodeColor;
			asStr	= (char*)m_vStatDoc11[i].KIND_CODE;
			sgStat->Cells[nCol++][nIndex]   = eFunc->funcGetKindCodeToKindName(11, asStr.c_str());
		}
		//개수//
		sgStat->Cells[nCol++][nIndex]   = FormatFloat("#,##0", m_vStatDoc11[i].COUNT);
		nSumCount[nDocIndex]	+= m_vStatDoc11[i].COUNT;//220107//
		nIndex++;
	}
	if(nSize > 0)
	{
		//합계
		sgStat->FontStyles[nCurCol][1]		= TFontStyles() << fsBold;
		sgStat->Cells[nCurCol][2]			= "합계";
		sgStat->FontColors[nCurCol][2]		= (TColor)RGB( 255, 0, 0);
		sgStat->FontStyles[nCurCol+1][1]	= TFontStyles() << fsBold;
		sgStat->Cells[nCurCol+1][2]			= FormatFloat("#,##0", nSumCount[nDocIndex]);
		sgStat->FontColors[nCurCol+1][2]	= (TColor)RGB( 255, 0, 0);

		nCurCol	= nCol;
		nDocIndex++;//220107//
	}
	else
	{
		nCurCol	+= nKind;
	}

	//---비법인등록대장---//
	nSize	= (int)m_vStatDoc15.size();
	nIndex	= 3;
	for (int i = 0; i < nSize; i++)
	{
		nCol	= nCurCol;
		asStr	= "";
		//color//		sgStat->RowColor[nIndex] = clWhite;

		//구축년도//
		if(chkYearLand->Checked)
		{
			sgStat->Colors[nCol][nIndex]   	= (TColor)RGB( n1ColBgColor, n1ColBgColor, n1ColBgColor );
			//sgStat->FontColors[nCol][nRow]	= (TColor)RGB( n1ColFgColor, n1ColFgColor, n1ColFgColor );
			asStr	= (char*)m_vStatDoc15[i].YEAR;
			sgStat->Cells[nCol++][nIndex]   = asStr;
		}
		//문서구분//
		if(chkDocKind->Checked)
		{
			sgStat->Colors[nCol][nIndex] 	= cKindCodeColor;
			asStr	= (char*)m_vStatDoc15[i].KIND_CODE;
			sgStat->Cells[nCol++][nIndex]   = eFunc->funcGetKindCodeToKindName(15, asStr.c_str());
		}
		//개수//
		sgStat->Cells[nCol++][nIndex]   = FormatFloat("#,##0", m_vStatDoc15[i].COUNT);
		nSumCount[nDocIndex]	+= m_vStatDoc15[i].COUNT;//220107//
		nIndex++;
	}
	if(nSize > 0)
	{
		//합계
		sgStat->FontStyles[nCurCol][1]		= TFontStyles() << fsBold;
		sgStat->Cells[nCurCol][2]			= "합계";
		sgStat->FontColors[nCurCol][2]		= (TColor)RGB( 255, 0, 0);
		sgStat->FontStyles[nCurCol+1][1]	= TFontStyles() << fsBold;
		sgStat->Cells[nCurCol+1][2]			= FormatFloat("#,##0", nSumCount[nDocIndex]);
		sgStat->FontColors[nCurCol+1][2]	= (TColor)RGB( 255, 0, 0);

		nCurCol	= nCol;
		nDocIndex++;//220107//
	}
	else
	{
		nCurCol	+= nKind;
	}

	//---기타문서---//
	nSize	= (int)m_vStatDoc17.size();
	nIndex	= 3;
	for (int i = 0; i < nSize; i++)
	{
		nCol	= nCurCol;
		asStr	= "";
		//color//		sgStat->RowColor[nIndex] = clWhite;

		//구축년도//
		if(chkYearLand->Checked)
		{
			sgStat->Colors[nCol][nIndex]   	= (TColor)RGB( n1ColBgColor, n1ColBgColor, n1ColBgColor );
			//sgStat->FontColors[nCol][nRow]	= (TColor)RGB( n1ColFgColor, n1ColFgColor, n1ColFgColor );
			asStr	= (char*)m_vStatDoc17[i].YEAR;
			sgStat->Cells[nCol++][nIndex]   = asStr;
		}
		//문서구분//
		if(chkDocKind->Checked)
		{
			sgStat->Colors[nCol][nIndex] 	= cKindCodeColor;
			asStr	= (char*)m_vStatDoc17[i].KIND_CODE;
			sgStat->Cells[nCol++][nIndex]   = eFunc->funcGetKindCodeToKindName(17, asStr.c_str());
		}
		//개수//
		sgStat->Cells[nCol++][nIndex]   = FormatFloat("#,##0", m_vStatDoc17[i].COUNT);
		nSumCount[nDocIndex]	+= m_vStatDoc17[i].COUNT;//220107//
		nIndex++;
	}
	if(nSize > 0)
	{
		//합계
		sgStat->FontStyles[nCurCol][1]		= TFontStyles() << fsBold;
		sgStat->Cells[nCurCol][2]			= "합계";
		sgStat->FontColors[nCurCol][2]		= (TColor)RGB( 255, 0, 0);
		sgStat->FontStyles[nCurCol+1][1]	= TFontStyles() << fsBold;
		sgStat->Cells[nCurCol+1][2]			= FormatFloat("#,##0", nSumCount[nDocIndex]);
		sgStat->FontColors[nCurCol+1][2]	= (TColor)RGB( 255, 0, 0);

		nCurCol	= nCol;
		nDocIndex++;//220107//
	}
	else
	{
		nCurCol	+= nKind;
	}

	//---좌표계산부---//
	nSize	= (int)m_vStatDoc18.size();
	nIndex	= 3;
	for (int i = 0; i < nSize; i++)
	{
		nCol	= nCurCol;
		asStr	= "";
		//color//		sgStat->RowColor[nIndex] = clWhite;

		//구축년도//
		if(chkYearLand->Checked)
		{
			sgStat->Colors[nCol][nIndex]   	= (TColor)RGB( n1ColBgColor, n1ColBgColor, n1ColBgColor );
			//sgStat->FontColors[nCol][nRow]	= (TColor)RGB( n1ColFgColor, n1ColFgColor, n1ColFgColor );
			asStr	= (char*)m_vStatDoc18[i].YEAR;
			sgStat->Cells[nCol++][nIndex]   = asStr;
		}
		//문서구분//
		if(chkDocKind->Checked)
		{
			sgStat->Colors[nCol][nIndex] 	= cKindCodeColor;
			asStr	= (char*)m_vStatDoc18[i].KIND_CODE;
			sgStat->Cells[nCol++][nIndex]   = eFunc->funcGetKindCodeToKindName(18, asStr.c_str());
		}
		//개수//
		sgStat->Cells[nCol++][nIndex]   = FormatFloat("#,##0", m_vStatDoc18[i].COUNT);
		nSumCount[nDocIndex]	+= m_vStatDoc18[i].COUNT;//220107//
		nIndex++;
	}
	if(nSize > 0)
	{
		//합계
		sgStat->FontStyles[nCurCol][1]		= TFontStyles() << fsBold;
		sgStat->Cells[nCurCol][2]			= "합계";
		sgStat->FontColors[nCurCol][2]		= (TColor)RGB( 255, 0, 0);
		sgStat->FontStyles[nCurCol+1][1]	= TFontStyles() << fsBold;
		sgStat->Cells[nCurCol+1][2]			= FormatFloat("#,##0", nSumCount[nDocIndex]);
		sgStat->FontColors[nCurCol+1][2]	= (TColor)RGB( 255, 0, 0);

		nCurCol	= nCol;
		nDocIndex++;//220107//
	}
	else
	{
		nCurCol	+= nKind;
	}

	//---종이지적도---//
	nSize	= (int)m_vStatDoc07.size();
	nIndex	= 3;
	for (int i = 0; i < nSize; i++)
	{
		nCol	= nCurCol;
		asStr	= "";
		//color//		sgStat->RowColor[nIndex] = clWhite;

		//읍면동//
		if(chkYearLand->Checked)
		{
			sgStat->Colors[nCol][nIndex]   	= (TColor)RGB( n1ColBgColor, n1ColBgColor, n1ColBgColor );
			//sgStat->FontColors[nCol][nRow]	= (TColor)RGB( n1ColFgColor, n1ColFgColor, n1ColFgColor );
			asStr	= (char*)m_vStatDoc07[i].LAND;
			sgStat->Cells[nCol++][nIndex]   = eFunc->funcUMDCdToNm(asStr);
		}
		//문서구분//
		if(chkDocKind->Checked)
		{
			sgStat->Colors[nCol][nIndex] 	= cKindCodeColor;
			asStr	= (char*)m_vStatDoc07[i].KIND_CODE;
			if(asStr == "00000000")
				sgStat->Cells[nCol++][nIndex]   = "기타";
			else
				sgStat->Cells[nCol++][nIndex]   = eFunc->funcGetKindCodeToKindName(7, asStr.c_str());
		}
		//개수//
		sgStat->Cells[nCol++][nIndex]   = FormatFloat("#,##0", m_vStatDoc07[i].COUNT);
		nSumCount[nDocIndex]	+= m_vStatDoc07[i].COUNT;//220107//
		nIndex++;
	}
	if(nSize > 0)
	{
		//합계
		sgStat->FontStyles[nCurCol][1]		= TFontStyles() << fsBold;
		sgStat->Cells[nCurCol][2]			= "합계";
		sgStat->FontColors[nCurCol][2]		= (TColor)RGB( 255, 0, 0);
		sgStat->FontStyles[nCurCol+1][1]	= TFontStyles() << fsBold;
		sgStat->Cells[nCurCol+1][2]			= FormatFloat("#,##0", nSumCount[nDocIndex]);
		sgStat->FontColors[nCurCol+1][2]	= (TColor)RGB( 255, 0, 0);

		nCurCol	= nCol;
		nDocIndex++;//220107//
	}
	else
	{
		nCurCol	+= nKind;
	}

	//---구대장---//
	nSize	= (int)m_vStatDoc08.size();
	nIndex	= 3;
	for (int i = 0; i < nSize; i++)
	{
		nCol	= nCurCol;
		asStr	= "";
		//color//		sgStat->RowColor[nIndex] = clWhite;

		//읍면동//
		if(chkYearLand->Checked)
		{
			sgStat->Colors[nCol][nIndex]   	= (TColor)RGB( n1ColBgColor, n1ColBgColor, n1ColBgColor );
			//sgStat->FontColors[nCol][nRow]	= (TColor)RGB( n1ColFgColor, n1ColFgColor, n1ColFgColor );
			asStr	= (char*)m_vStatDoc08[i].LAND;
			if(asStr == "00000000")
				sgStat->Cells[nCol++][nIndex]   = "기타";
			else
			sgStat->Cells[nCol++][nIndex]   = eFunc->funcUMDCdToNm(asStr);
		}
		//문서구분//
		if(chkDocKind->Checked)
		{
			sgStat->Colors[nCol][nIndex] 	= cKindCodeColor;
			asStr	= (char*)m_vStatDoc08[i].KIND_CODE;
			sgStat->Cells[nCol++][nIndex]   = eFunc->funcGetKindCodeToKindName(8, asStr.c_str());
		}
		//개수//
		sgStat->Cells[nCol++][nIndex]   = FormatFloat("#,##0", m_vStatDoc08[i].COUNT);
		nSumCount[nDocIndex]	+= m_vStatDoc08[i].COUNT;//220107//
		nIndex++;
	}
	if(nSize > 0)
	{
		//합계
		sgStat->FontStyles[nCurCol][1]		= TFontStyles() << fsBold;
		sgStat->Cells[nCurCol][2]			= "합계";
		sgStat->FontColors[nCurCol][2]		= (TColor)RGB( 255, 0, 0);
		sgStat->FontStyles[nCurCol+1][1]	= TFontStyles() << fsBold;
		sgStat->Cells[nCurCol+1][2]			= FormatFloat("#,##0", nSumCount[nDocIndex]);
		sgStat->FontColors[nCurCol+1][2]	= (TColor)RGB( 255, 0, 0);

		nCurCol	= nCol;
		nDocIndex++;//220107//
	}
	else
	{
		nCurCol	+= nKind;
	}

//	if(m_nStatRowCount > 0)
//	{
//		sgStat->Row = 2;
//	}
}
// ---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStat()
{
	if(chkYearLand->Checked && chkDocKind->Checked)
	{
		if(chkDoc01->Checked)
			funcReadStatDoc01();
		if(chkDoc02->Checked)
			funcReadStatDoc02();
		if(chkDoc03->Checked)
			funcReadStatDoc03();
		if(chkDoc04->Checked)
			funcReadStatDoc04();
		if(chkDoc06->Checked)
			funcReadStatDoc06();
		if(chkDoc07->Checked)
			funcReadStatDoc07();
		if(chkDoc08->Checked)
			funcReadStatDoc08();
		if(chkDoc09->Checked)
			funcReadStatDoc09();
		if(chkDoc11->Checked)
			funcReadStatDoc11();
		if(chkDoc15->Checked)
			funcReadStatDoc15();
		if(chkDoc17->Checked)
			funcReadStatDoc17();
		if(chkDoc18->Checked)
			funcReadStatDoc18();
	}
	else if(!chkYearLand->Checked && chkDocKind->Checked)
	{
		if(chkDoc01->Checked)
			funcReadStatDoc01_2();
		if(chkDoc02->Checked)
			funcReadStatDoc02_2();
		if(chkDoc03->Checked)
			funcReadStatDoc03_2();
		if(chkDoc04->Checked)
			funcReadStatDoc04_2();
		if(chkDoc06->Checked)
			funcReadStatDoc06_2();
		if(chkDoc07->Checked)
			funcReadStatDoc07_2();
		if(chkDoc08->Checked)
			funcReadStatDoc08_2();
		if(chkDoc09->Checked)
			funcReadStatDoc09_2();
		if(chkDoc11->Checked)
			funcReadStatDoc11_2();
		if(chkDoc15->Checked)
			funcReadStatDoc15_2();
		if(chkDoc17->Checked)
			funcReadStatDoc17_2();
		if(chkDoc18->Checked)
			funcReadStatDoc18_2();
	}
	else if(chkYearLand->Checked && !chkDocKind->Checked)
	{
		if(chkDoc01->Checked)
			funcReadStatDoc01_3();
		if(chkDoc02->Checked)
			funcReadStatDoc02_3();
		if(chkDoc03->Checked)
			funcReadStatDoc03_3();
		if(chkDoc04->Checked)
			funcReadStatDoc04_3();
		if(chkDoc06->Checked)
			funcReadStatDoc06_3();
		if(chkDoc07->Checked)
			funcReadStatDoc07_3();
		if(chkDoc08->Checked)
			funcReadStatDoc08_3();
		if(chkDoc09->Checked)
			funcReadStatDoc09_3();
		if(chkDoc11->Checked)
			funcReadStatDoc11_3();
		if(chkDoc15->Checked)
			funcReadStatDoc15_3();
		if(chkDoc17->Checked)
			funcReadStatDoc17_3();
		if(chkDoc18->Checked)
			funcReadStatDoc18_3();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc01()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT01";
	AnsiString  asColumn  	= "DISTINCT SUBSTR(PRCS_DATE, 1, 4) AS YEAR, KIND_CODE, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY YEAR, KIND_CODE";
	AnsiString  asOrderBy  	= " ORDER BY YEAR, KIND_CODE";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[3];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.YEAR, 		sizeof(tempDoc.YEAR), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 	sizeof(tempDoc.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc01.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc01.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc01.size())
		m_nStatRowCount = (int)m_vStatDoc01.size();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc02()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT02";
	AnsiString  asColumn  	= "DISTINCT SUBSTR(SURV_YEAR, 1, 4) AS YEAR, KIND_CODE, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY YEAR, KIND_CODE";
	AnsiString  asOrderBy  	= " ORDER BY YEAR, KIND_CODE";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[3];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.YEAR, 		sizeof(tempDoc.YEAR), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 	sizeof(tempDoc.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc02.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc02.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc02.size())
		m_nStatRowCount = (int)m_vStatDoc02.size();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc03()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT03";
	AnsiString  asColumn  	= "DISTINCT SUBSTR(SURV_YEAR, 1, 4) AS YEAR, KIND_CODE, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY YEAR, KIND_CODE";
	AnsiString  asOrderBy  	= " ORDER BY YEAR, KIND_CODE";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[3];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.YEAR, 		sizeof(tempDoc.YEAR), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 	sizeof(tempDoc.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc03.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc03.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc03.size())
		m_nStatRowCount = (int)m_vStatDoc03.size();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc04()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT04";
	AnsiString  asColumn  	= "DISTINCT SUBSTR(REQ_YEAR, 1, 4) AS YEAR, KIND_CODE, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY YEAR, KIND_CODE";
	AnsiString  asOrderBy  	= " ORDER BY YEAR, KIND_CODE";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[3];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.YEAR, 		sizeof(tempDoc.YEAR), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 	sizeof(tempDoc.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc04.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc04.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc04.size())
		m_nStatRowCount = (int)m_vStatDoc04.size();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc06()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT06";
	AnsiString  asColumn  	= "DISTINCT SUBSTR(COMP_YEAR, 1, 4) AS YEAR, KIND_CODE, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY YEAR, KIND_CODE";
	AnsiString  asOrderBy  	= " ORDER BY YEAR, KIND_CODE";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[3];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.YEAR, 		sizeof(tempDoc.YEAR), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 	sizeof(tempDoc.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc06.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc06.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc06.size())
		m_nStatRowCount = (int)m_vStatDoc06.size();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc07()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT07";
	AnsiString  asColumn  	= "DISTINCT CONCAT(SIDOSGG, UMD) AS LAND, KIND_CODE, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY LAND, KIND_CODE";
	AnsiString  asOrderBy  	= " ORDER BY LAND, KIND_CODE";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[3];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.LAND, 		sizeof(tempDoc.LAND), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 	sizeof(tempDoc.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc07.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc07.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc07.size())
		m_nStatRowCount = (int)m_vStatDoc07.size();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc08()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT08";
	AnsiString  asColumn  	= "DISTINCT SUBSTR(PNU, 1, 8) AS LAND, KIND_CODE, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY LAND, KIND_CODE";
	AnsiString  asOrderBy  	= " ORDER BY LAND, KIND_CODE";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[3];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.LAND, 		sizeof(tempDoc.LAND), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 	sizeof(tempDoc.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc08.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc08.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc08.size())
		m_nStatRowCount = (int)m_vStatDoc08.size();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc09()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT09";
	AnsiString  asColumn  	= "DISTINCT SUBSTR(BASE_YEAR, 1, 4) AS YEAR, KIND_CODE, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY YEAR, KIND_CODE";
	AnsiString  asOrderBy  	= " ORDER BY YEAR, KIND_CODE";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[3];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.YEAR, 		sizeof(tempDoc.YEAR), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 	sizeof(tempDoc.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc09.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc09.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc09.size())
		m_nStatRowCount = (int)m_vStatDoc09.size();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc11()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT11";
	AnsiString  asColumn  	= "DISTINCT SUBSTR(REQ_YEAR, 1, 4) AS YEAR, KIND_CODE, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY YEAR, KIND_CODE";
	AnsiString  asOrderBy  	= " ORDER BY YEAR, KIND_CODE";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[3];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.YEAR, 		sizeof(tempDoc.YEAR), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 	sizeof(tempDoc.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc11.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc11.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc11.size())
		m_nStatRowCount = (int)m_vStatDoc11.size();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc15()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT15";
	AnsiString  asColumn  	= "DISTINCT SUBSTR(PRCS_DATE, 1, 4) AS YEAR, KIND_CODE, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY YEAR, KIND_CODE";
	AnsiString  asOrderBy  	= " ORDER BY YEAR, KIND_CODE";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[3];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.YEAR, 		sizeof(tempDoc.YEAR), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 	sizeof(tempDoc.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc15.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc15.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc15.size())
		m_nStatRowCount = (int)m_vStatDoc15.size();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc17()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT17";
	AnsiString  asColumn  	= "DISTINCT SUBSTR(DOC_DATE, 1, 4) AS YEAR, KIND_CODE, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY YEAR, KIND_CODE";
	AnsiString  asOrderBy  	= " ORDER BY YEAR, KIND_CODE";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[3];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.YEAR, 		sizeof(tempDoc.YEAR), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 	sizeof(tempDoc.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc17.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc17.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc17.size())
		m_nStatRowCount = (int)m_vStatDoc17.size();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc18()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT18";
	AnsiString  asColumn  	= "DISTINCT SUBSTR(JIGU_YEAR, 1, 4) AS YEAR, KIND_CODE, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY YEAR, KIND_CODE";
	AnsiString  asOrderBy  	= " ORDER BY YEAR, KIND_CODE";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[3];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.YEAR, 		sizeof(tempDoc.YEAR), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 	sizeof(tempDoc.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 		sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc18.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc18.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc18.size())
		m_nStatRowCount = (int)m_vStatDoc18.size();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcSetComboDoc()
{
	m_nDocCount = 0;
	if(frmMain->INIINFO.B_DOCKIND[1])
	{
		chkDoc01->Visible	= true;
		chkDoc01->Left  = 8 + (m_nDocCount % 4) * 120;
		chkDoc01->Top   = 12 + (m_nDocCount / 4) * 20;
		m_nDocCount++;
	}
	else
		chkDoc01->Visible	= false;

	if(frmMain->INIINFO.B_DOCKIND[2])
	{
		chkDoc02->Visible	= true;
		chkDoc02->Left  = 8 + (m_nDocCount % 4) * 120;
		chkDoc02->Top   = 12 + (m_nDocCount / 4) * 20;
		m_nDocCount++;
	}
	else
		chkDoc02->Visible	= false;

	if(frmMain->INIINFO.B_DOCKIND[3])
	{
		chkDoc03->Visible	= true;
		chkDoc03->Left  = 8 + (m_nDocCount % 4) * 120;
		chkDoc03->Top   = 12 + (m_nDocCount / 4) * 20;
		m_nDocCount++;
	}
	else
		chkDoc03->Visible	= false;

	if(frmMain->INIINFO.B_DOCKIND[4])
	{
		chkDoc04->Visible	= true;
		chkDoc04->Left  = 8 + (m_nDocCount % 4) * 120;
		chkDoc04->Top   = 12 + (m_nDocCount / 4) * 20;
		m_nDocCount++;
	}
	else
		chkDoc04->Visible	= false;

	if(frmMain->INIINFO.B_DOCKIND[6])
	{
		chkDoc06->Visible	= true;
		chkDoc06->Left  = 8 + (m_nDocCount % 4) * 120;
		chkDoc06->Top   = 12 + (m_nDocCount / 4) * 20;
		m_nDocCount++;
	}
	else
		chkDoc06->Visible	= false;

	if(frmMain->INIINFO.B_DOCKIND[7])
	{
		chkDoc07->Visible	= true;
		chkDoc07->Left  = 8 + (m_nDocCount % 4) * 120;
		chkDoc07->Top   = 12 + (m_nDocCount / 4) * 20;
		m_nDocCount++;
	}
	else
		chkDoc07->Visible	= false;

	if(frmMain->INIINFO.B_DOCKIND[8])
	{
		chkDoc08->Visible	= true;
		chkDoc08->Left  = 8 + (m_nDocCount % 4) * 120;
		chkDoc08->Top   = 12 + (m_nDocCount / 4) * 20;
		m_nDocCount++;
	}
	else
		chkDoc08->Visible	= false;

	if(frmMain->INIINFO.B_DOCKIND[9])
	{
		chkDoc09->Visible	= true;
		chkDoc09->Left  = 8 + (m_nDocCount % 4) * 120;
		chkDoc09->Top   = 12 + (m_nDocCount / 4) * 20;
		m_nDocCount++;
	}
	else
		chkDoc09->Visible	= false;

	if(frmMain->INIINFO.B_DOCKIND[11])
	{
		chkDoc11->Visible	= true;
		chkDoc11->Left  = 8 + (m_nDocCount % 4) * 120;
		chkDoc11->Top   = 12 + (m_nDocCount / 4) * 20;
		m_nDocCount++;
	}
	else
		chkDoc11->Visible	= false;

	if(frmMain->INIINFO.B_DOCKIND[15])
	{
		chkDoc15->Visible	= true;
		chkDoc15->Left  = 8 + (m_nDocCount % 4) * 120;
		chkDoc15->Top   = 12 + (m_nDocCount / 4) * 20;
		m_nDocCount++;
	}
	else
		chkDoc15->Visible	= false;

	if(frmMain->INIINFO.B_DOCKIND[17])
	{
		chkDoc17->Visible	= true;
		chkDoc17->Left  = 8 + (m_nDocCount % 4) * 120;
		chkDoc17->Top   = 12 + (m_nDocCount / 4) * 20;
		m_nDocCount++;
	}
	else
		chkDoc17->Visible	= false;

	if(frmMain->INIINFO.B_DOCKIND[18])
	{
		chkDoc18->Visible	= true;
		chkDoc18->Left  = 8 + (m_nDocCount % 4) * 120;
		chkDoc18->Top   = 8 + (m_nDocCount / 3) * 24;
		m_nDocCount++;
	}
	else
		chkDoc18->Visible	= false;

}
//---------------------------------------------------------------------------




void __fastcall TfrmStat::funcReadStatDoc01_2()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT01";
	AnsiString  asColumn  	= "DISTINCT KIND_CODE, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY KIND_CODE";
	AnsiString  asOrderBy  	= " ORDER BY KIND_CODE";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[2];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 	sizeof(tempDoc.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc01.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc01.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc01.size())
		m_nStatRowCount = (int)m_vStatDoc01.size();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc02_2()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT02";
	AnsiString  asColumn  	= "DISTINCT KIND_CODE, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY KIND_CODE";
	AnsiString  asOrderBy  	= " ORDER BY KIND_CODE";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[2];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 	sizeof(tempDoc.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc02.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc02.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc02.size())
		m_nStatRowCount = (int)m_vStatDoc02.size();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc03_2()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT03";
	AnsiString  asColumn  	= "DISTINCT KIND_CODE, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY KIND_CODE";
	AnsiString  asOrderBy  	= " ORDER BY KIND_CODE";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[2];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 	sizeof(tempDoc.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc03.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc03.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc03.size())
		m_nStatRowCount = (int)m_vStatDoc03.size();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc04_2()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT04";
	AnsiString  asColumn  	= "DISTINCT KIND_CODE, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY KIND_CODE";
	AnsiString  asOrderBy  	= " ORDER BY KIND_CODE";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[2];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 	sizeof(tempDoc.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc04.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc04.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc04.size())
		m_nStatRowCount = (int)m_vStatDoc04.size();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc06_2()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT06";
	AnsiString  asColumn  	= "DISTINCT KIND_CODE, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY KIND_CODE";
	AnsiString  asOrderBy  	= " ORDER BY KIND_CODE";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[2];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 	sizeof(tempDoc.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc06.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc06.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc06.size())
		m_nStatRowCount = (int)m_vStatDoc06.size();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc07_2()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT07";
	AnsiString  asColumn  	= "DISTINCT KIND_CODE, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY KIND_CODE";
	AnsiString  asOrderBy  	= " ORDER BY KIND_CODE";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[2];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 	sizeof(tempDoc.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc07.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc07.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc07.size())
		m_nStatRowCount = (int)m_vStatDoc07.size();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc08_2()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT08";
	AnsiString  asColumn  	= "DISTINCT KIND_CODE, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY KIND_CODE";
	AnsiString  asOrderBy  	= " ORDER BY KIND_CODE";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[2];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 	sizeof(tempDoc.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc08.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc08.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc08.size())
		m_nStatRowCount = (int)m_vStatDoc08.size();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc09_2()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT09";
	AnsiString  asColumn  	= "DISTINCT KIND_CODE, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY KIND_CODE";
	AnsiString  asOrderBy  	= " ORDER BY KIND_CODE";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[2];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 	sizeof(tempDoc.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc09.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc09.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc09.size())
		m_nStatRowCount = (int)m_vStatDoc09.size();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc11_2()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT11";
	AnsiString  asColumn  	= "DISTINCT KIND_CODE, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY KIND_CODE";
	AnsiString  asOrderBy  	= " ORDER BY KIND_CODE";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[2];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 	sizeof(tempDoc.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc11.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc11.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc11.size())
		m_nStatRowCount = (int)m_vStatDoc11.size();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc15_2()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT15";
	AnsiString  asColumn  	= "DISTINCT KIND_CODE, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY KIND_CODE";
	AnsiString  asOrderBy  	= " ORDER BY KIND_CODE";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[2];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 	sizeof(tempDoc.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc15.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc15.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc15.size())
		m_nStatRowCount = (int)m_vStatDoc15.size();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc17_2()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT17";
	AnsiString  asColumn  	= "DISTINCT KIND_CODE, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY KIND_CODE";
	AnsiString  asOrderBy  	= " ORDER BY KIND_CODE";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[2];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 	sizeof(tempDoc.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc17.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc17.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc17.size())
		m_nStatRowCount = (int)m_vStatDoc17.size();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc18_2()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT18";
	AnsiString  asColumn  	= "DISTINCT KIND_CODE, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY KIND_CODE";
	AnsiString  asOrderBy  	= " ORDER BY KIND_CODE";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[2];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.KIND_CODE, 	sizeof(tempDoc.KIND_CODE), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 		sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc18.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc18.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc18.size())
		m_nStatRowCount = (int)m_vStatDoc18.size();
}
//---------------------------------------------------------------------------



bool __fastcall TfrmStat::funcCheckCountComboDoc()
{
	if(chkDoc01->Checked)
		return true;
	if(chkDoc02->Checked)
		return true;
	if(chkDoc03->Checked)
		return true;
	if(chkDoc04->Checked)
		return true;
	if(chkDoc06->Checked)
		return true;
	if(chkDoc07->Checked)
		return true;
	if(chkDoc08->Checked)
		return true;
	if(chkDoc09->Checked)
		return true;
	if(chkDoc11->Checked)
		return true;
	if(chkDoc15->Checked)
		return true;
	if(chkDoc17->Checked)
		return true;
	if(chkDoc18->Checked)
		return true;

	return false;
}
//---------------------------------------------------------------------------







void __fastcall TfrmStat::funcReadStatDoc01_3()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT01";
	AnsiString  asColumn  	= "PRCS_DATE";
	AnsiString  asTargetCol	= "";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY YEAR";
	//AnsiString  asOrderBy  	= " ORDER BY YEAR='0000' DESC, YEAR DESC";
	AnsiString  asOrderBy  	= " ORDER BY YEAR DESC";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[2];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	asTargetCol	= "DISTINCT CASE LENGTH(" + asColumn + ") WHEN 8 THEN (";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1960' AND SUBSTR(" + asColumn + ", 1, 4) < '1970', '1960~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1950' AND SUBSTR(" + asColumn + ", 1, 4) < '1960', '1950~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1940' AND SUBSTR(" + asColumn + ", 1, 4) < '1950', '1940~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1930' AND SUBSTR(" + asColumn + ", 1, 4) < '1940', '1930~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) != '0000' AND SUBSTR(" + asColumn + ", 1, 4) < '1930', '1900~', SUBSTR(" + asColumn + ", 1, 4)))))))";
	asTargetCol	= asTargetCol + "ELSE '0000' END ";
	asTargetCol	= asTargetCol + "AS YEAR, COUNT(DISTINCT PATH_NAME) AS COUNT";

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.YEAR, 	    sizeof(tempDoc.YEAR), 	    &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asTargetCol + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc01.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc01.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc01.size())
		m_nStatRowCount = (int)m_vStatDoc01.size();

	//==================================
	//260617//[REG][DEBUG]
	//==================================
	if(frmMain->m_bDEBUG)
		frmMain->qryLog->Add(asSqlQry);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc02_3()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT02";
	AnsiString  asColumn1  	= "SUBMIT_DATE";
	AnsiString  asColumn2  	= "INSPCT_DAY";
	AnsiString  asColumn3  	= "SURV_DAY";
	AnsiString  asTargetCol	= "";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY YEAR";
	//AnsiString  asOrderBy  	= " ORDER BY YEAR='0000' DESC, YEAR DESC";
	AnsiString  asOrderBy  	= " ORDER BY YEAR DESC";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[2];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	asTargetCol	= "DISTINCT CASE LENGTH(" + asColumn1 + ") WHEN 8 THEN (";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn1 + ", 1, 4) >= '1960' AND SUBSTR(" + asColumn1 + ", 1, 4) < '1970', '1960~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn1 + ", 1, 4) >= '1950' AND SUBSTR(" + asColumn1 + ", 1, 4) < '1960', '1950~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn1 + ", 1, 4) >= '1940' AND SUBSTR(" + asColumn1 + ", 1, 4) < '1950', '1940~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn1 + ", 1, 4) >= '1930' AND SUBSTR(" + asColumn1 + ", 1, 4) < '1940', '1930~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn1 + ", 1, 4) != '0000' AND SUBSTR(" + asColumn1 + ", 1, 4) < '1930', '1900~', SUBSTR(" + asColumn1 + ", 1, 4)))))))";

	asTargetCol	= asTargetCol + "ELSE ( CASE LENGTH(" + asColumn2 + ") WHEN 8 THEN (";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn2 + ", 1, 4) >= '1960' AND SUBSTR(" + asColumn2 + ", 1, 4) < '1970', '1960~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn2 + ", 1, 4) >= '1950' AND SUBSTR(" + asColumn2 + ", 1, 4) < '1960', '1950~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn2 + ", 1, 4) >= '1940' AND SUBSTR(" + asColumn2 + ", 1, 4) < '1950', '1940~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn2 + ", 1, 4) >= '1930' AND SUBSTR(" + asColumn2 + ", 1, 4) < '1940', '1930~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn2 + ", 1, 4) != '0000' AND SUBSTR(" + asColumn2 + ", 1, 4) < '1930', '1900~', SUBSTR(" + asColumn2 + ", 1, 4)))))))";

	asTargetCol	= asTargetCol + "ELSE ( CASE LENGTH(" + asColumn3 + ") WHEN 8 THEN (";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn3 + ", 1, 4) >= '1960' AND SUBSTR(" + asColumn3 + ", 1, 4) < '1970', '1960~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn3 + ", 1, 4) >= '1950' AND SUBSTR(" + asColumn3 + ", 1, 4) < '1960', '1950~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn3 + ", 1, 4) >= '1940' AND SUBSTR(" + asColumn3 + ", 1, 4) < '1950', '1940~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn3 + ", 1, 4) >= '1930' AND SUBSTR(" + asColumn3 + ", 1, 4) < '1940', '1930~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn3 + ", 1, 4) != '0000' AND SUBSTR(" + asColumn3 + ", 1, 4) < '1930', '1900~', SUBSTR(" + asColumn3 + ", 1, 4)))))))";

	asTargetCol	= asTargetCol + "ELSE '0000' END ";
	asTargetCol	= asTargetCol + ") END ";
	asTargetCol	= asTargetCol + ") END ";
	asTargetCol	= asTargetCol + "AS YEAR, COUNT(DISTINCT PATH_NAME) AS COUNT";

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.YEAR, 	    sizeof(tempDoc.YEAR), 	    &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asTargetCol + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc02.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc02.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc02.size())
		m_nStatRowCount = (int)m_vStatDoc02.size();

	//==================================
	//260617//[REG][DEBUG]
	//==================================
	if(frmMain->m_bDEBUG)
		frmMain->qryLog->Add(asSqlQry);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc03_3()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT03";
	AnsiString  asColumn  	= "SURV_YEAR";
	AnsiString  asTargetCol	= "";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY YEAR";
	//AnsiString  asOrderBy  	= " ORDER BY YEAR='0000' DESC, YEAR DESC";
	AnsiString  asOrderBy  	= " ORDER BY YEAR DESC";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[2];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	asTargetCol	= "DISTINCT CASE LENGTH(" + asColumn + ") WHEN 4 THEN (";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1960' AND SUBSTR(" + asColumn + ", 1, 4) < '1970', '1960~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1950' AND SUBSTR(" + asColumn + ", 1, 4) < '1960', '1950~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1940' AND SUBSTR(" + asColumn + ", 1, 4) < '1950', '1940~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1930' AND SUBSTR(" + asColumn + ", 1, 4) < '1940', '1930~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) != '0000' AND SUBSTR(" + asColumn + ", 1, 4) < '1930', '1900~', SUBSTR(" + asColumn + ", 1, 4)))))))";
	asTargetCol	= asTargetCol + "ELSE '0000' END ";
	asTargetCol	= asTargetCol + "AS YEAR, COUNT(DISTINCT PATH_NAME) AS COUNT";

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.YEAR, 	    sizeof(tempDoc.YEAR), 	    &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asTargetCol + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc03.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc03.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc03.size())
		m_nStatRowCount = (int)m_vStatDoc03.size();

	//==================================
	//260617//[REG][DEBUG]
	//==================================
	if(frmMain->m_bDEBUG)
		frmMain->qryLog->Add(asSqlQry);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc04_3()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT04";
	AnsiString  asColumn  	= "REQ_YEAR";
	AnsiString  asTargetCol	= "";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY YEAR";
	//AnsiString  asOrderBy  	= " ORDER BY YEAR='0000' DESC, YEAR DESC";
	AnsiString  asOrderBy  	= " ORDER BY YEAR DESC";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[2];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	asTargetCol	= "DISTINCT CASE LENGTH(" + asColumn + ") WHEN 4 THEN (";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1960' AND SUBSTR(" + asColumn + ", 1, 4) < '1970', '1960~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1950' AND SUBSTR(" + asColumn + ", 1, 4) < '1960', '1950~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1940' AND SUBSTR(" + asColumn + ", 1, 4) < '1950', '1940~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1930' AND SUBSTR(" + asColumn + ", 1, 4) < '1940', '1930~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) != '0000' AND SUBSTR(" + asColumn + ", 1, 4) < '1930', '1900~', SUBSTR(" + asColumn + ", 1, 4)))))))";
	asTargetCol	= asTargetCol + "ELSE '0000' END ";
	asTargetCol	= asTargetCol + "AS YEAR, COUNT(DISTINCT PATH_NAME) AS COUNT";

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.YEAR, 	    sizeof(tempDoc.YEAR), 	    &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asTargetCol + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc04.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc04.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc04.size())
		m_nStatRowCount = (int)m_vStatDoc04.size();

	//==================================
	//260617//[REG][DEBUG]
	//==================================
	if(frmMain->m_bDEBUG)
		frmMain->qryLog->Add(asSqlQry);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc06_3()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT06";
	AnsiString  asColumn  	= "COMP_YEAR";
	AnsiString  asTargetCol	= "";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY YEAR";
	//AnsiString  asOrderBy  	= " ORDER BY YEAR='0000' DESC, YEAR DESC";
	AnsiString  asOrderBy  	= " ORDER BY YEAR DESC";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[2];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	asTargetCol	= "DISTINCT CASE LENGTH(" + asColumn + ") WHEN 4 THEN (";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1960' AND SUBSTR(" + asColumn + ", 1, 4) < '1970', '1960~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1950' AND SUBSTR(" + asColumn + ", 1, 4) < '1960', '1950~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1940' AND SUBSTR(" + asColumn + ", 1, 4) < '1950', '1940~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1930' AND SUBSTR(" + asColumn + ", 1, 4) < '1940', '1930~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) != '0000' AND SUBSTR(" + asColumn + ", 1, 4) < '1930', '1900~', SUBSTR(" + asColumn + ", 1, 4)))))))";
	asTargetCol	= asTargetCol + "ELSE '0000' END ";
	asTargetCol	= asTargetCol + "AS YEAR, COUNT(DISTINCT PATH_NAME) AS COUNT";

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.YEAR, 	    sizeof(tempDoc.YEAR), 	    &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asTargetCol + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc06.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc06.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc06.size())
		m_nStatRowCount = (int)m_vStatDoc06.size();

	//==================================
	//260617//[REG][DEBUG]
	//==================================
	if(frmMain->m_bDEBUG)
		frmMain->qryLog->Add(asSqlQry);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc07_3()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT07";
	AnsiString  asColumn  	= "DISTINCT CASE LENGTH(CONCAT(SIDOSGG, UMD)) WHEN 8 THEN CONCAT(SIDOSGG, UMD) ELSE '00000000' END AS LAND, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY LAND";
	AnsiString  asOrderBy  	= " ORDER BY SUBSTR(LAND, 1, 5) != '" + frmMain->_SIDOCODE + "' DESC, LAND ASC";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[2];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.LAND, 	    sizeof(tempDoc.LAND), 	    &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc07.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc07.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc07.size())
		m_nStatRowCount = (int)m_vStatDoc07.size();

	//==================================
	//260617//[REG][DEBUG]
	//==================================
	if(frmMain->m_bDEBUG)
		frmMain->qryLog->Add(asSqlQry);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc08_3()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT08";
	AnsiString  asColumn  	= "DISTINCT CASE LENGTH(PNU) WHEN 19 THEN SUBSTR(PNU, 1, 8) ELSE '00000000' END AS LAND, COUNT(DISTINCT PATH_NAME) AS COUNT";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY LAND";
	AnsiString  asOrderBy  	= " ORDER BY SUBSTR(LAND, 1, 5) != '" + frmMain->_SIDOCODE + "' DESC, LAND ASC";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[2];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.LAND, 	    sizeof(tempDoc.LAND), 	    &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asColumn + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc08.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc08.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc08.size())
		m_nStatRowCount = (int)m_vStatDoc08.size();

	//==================================
	//260617//[REG][DEBUG]
	//==================================
	if(frmMain->m_bDEBUG)
		frmMain->qryLog->Add(asSqlQry);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc09_3()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT09";
	AnsiString  asColumn  	= "BASE_YEAR";
	AnsiString  asTargetCol	= "";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY YEAR";
	//AnsiString  asOrderBy  	= " ORDER BY YEAR='0000' DESC, YEAR DESC";
	AnsiString  asOrderBy  	= " ORDER BY YEAR DESC";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[2];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	asTargetCol	= "DISTINCT CASE LENGTH(" + asColumn + ") WHEN 4 THEN (";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1960' AND SUBSTR(" + asColumn + ", 1, 4) < '1970', '1960~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1950' AND SUBSTR(" + asColumn + ", 1, 4) < '1960', '1950~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1940' AND SUBSTR(" + asColumn + ", 1, 4) < '1950', '1940~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1930' AND SUBSTR(" + asColumn + ", 1, 4) < '1940', '1930~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) != '0000' AND SUBSTR(" + asColumn + ", 1, 4) < '1930', '1900~', SUBSTR(" + asColumn + ", 1, 4)))))))";
	asTargetCol	= asTargetCol + "ELSE '0000' END ";
	asTargetCol	= asTargetCol + "AS YEAR, COUNT(DISTINCT PATH_NAME) AS COUNT";

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.YEAR, 	    sizeof(tempDoc.YEAR), 	    &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asTargetCol + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc09.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc09.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc09.size())
		m_nStatRowCount = (int)m_vStatDoc09.size();

	//==================================
	//260617//[REG][DEBUG]
	//==================================
	if(frmMain->m_bDEBUG)
		frmMain->qryLog->Add(asSqlQry);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc11_3()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT11";
	AnsiString  asColumn  	= "DOC_DATE";
	AnsiString  asTargetCol	= "";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY YEAR";
	//AnsiString  asOrderBy  	= " ORDER BY YEAR='0000' DESC, YEAR DESC";
	AnsiString  asOrderBy  	= " ORDER BY YEAR DESC";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[2];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	asTargetCol	= "DISTINCT CASE LENGTH(" + asColumn + ") WHEN 8 THEN (";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1960' AND SUBSTR(" + asColumn + ", 1, 4) < '1970', '1960~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1950' AND SUBSTR(" + asColumn + ", 1, 4) < '1960', '1950~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1940' AND SUBSTR(" + asColumn + ", 1, 4) < '1950', '1940~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1930' AND SUBSTR(" + asColumn + ", 1, 4) < '1940', '1930~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) != '0000' AND SUBSTR(" + asColumn + ", 1, 4) < '1930', '1900~', SUBSTR(" + asColumn + ", 1, 4)))))))";
	asTargetCol	= asTargetCol + "ELSE '0000' END ";
	asTargetCol	= asTargetCol + "AS YEAR, COUNT(DISTINCT PATH_NAME) AS COUNT";

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.YEAR, 	    sizeof(tempDoc.YEAR), 	    &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asTargetCol + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc11.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc11.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc11.size())
		m_nStatRowCount = (int)m_vStatDoc11.size();

	//==================================
	//260617//[REG][DEBUG]
	//==================================
	if(frmMain->m_bDEBUG)
		frmMain->qryLog->Add(asSqlQry);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc15_3()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT15";
	AnsiString  asColumn  	= "PRCS_DATE";
	AnsiString  asTargetCol	= "";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY YEAR";
	//AnsiString  asOrderBy  	= " ORDER BY YEAR='0000' DESC, YEAR DESC";
	AnsiString  asOrderBy  	= " ORDER BY YEAR DESC";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[2];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	asTargetCol	= "DISTINCT CASE LENGTH(" + asColumn + ") WHEN 8 THEN (";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1960' AND SUBSTR(" + asColumn + ", 1, 4) < '1970', '1960~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1950' AND SUBSTR(" + asColumn + ", 1, 4) < '1960', '1950~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1940' AND SUBSTR(" + asColumn + ", 1, 4) < '1950', '1940~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1930' AND SUBSTR(" + asColumn + ", 1, 4) < '1940', '1930~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) != '0000' AND SUBSTR(" + asColumn + ", 1, 4) < '1930', '1900~', SUBSTR(" + asColumn + ", 1, 4)))))))";
	asTargetCol	= asTargetCol + "ELSE '0000' END ";
	asTargetCol	= asTargetCol + "AS YEAR, COUNT(DISTINCT PATH_NAME) AS COUNT";

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.YEAR, 	    sizeof(tempDoc.YEAR), 	    &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asTargetCol + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc15.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc15.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc15.size())
		m_nStatRowCount = (int)m_vStatDoc15.size();

	//==================================
	//260617//[REG][DEBUG]
	//==================================
	if(frmMain->m_bDEBUG)
		frmMain->qryLog->Add(asSqlQry);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc17_3()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT17";
	AnsiString  asColumn  	= "DOC_DATE";
	AnsiString  asTargetCol	= "";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY YEAR";
	//AnsiString  asOrderBy  	= " ORDER BY YEAR='0000' DESC, YEAR DESC";
	AnsiString  asOrderBy  	= " ORDER BY YEAR DESC";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[2];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	asTargetCol	= "DISTINCT CASE LENGTH(" + asColumn + ") WHEN 8 THEN (";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1960' AND SUBSTR(" + asColumn + ", 1, 4) < '1970', '1960~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1950' AND SUBSTR(" + asColumn + ", 1, 4) < '1960', '1950~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1940' AND SUBSTR(" + asColumn + ", 1, 4) < '1950', '1940~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1930' AND SUBSTR(" + asColumn + ", 1, 4) < '1940', '1930~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) != '0000' AND SUBSTR(" + asColumn + ", 1, 4) < '1930', '1900~', SUBSTR(" + asColumn + ", 1, 4)))))))";
	asTargetCol	= asTargetCol + "ELSE '0000' END ";
	asTargetCol	= asTargetCol + "AS YEAR, COUNT(DISTINCT PATH_NAME) AS COUNT";

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.YEAR, 	    sizeof(tempDoc.YEAR), 	    &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asTargetCol + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc17.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc17.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc17.size())
		m_nStatRowCount = (int)m_vStatDoc17.size();

	//==================================
	//260617//[REG][DEBUG]
	//==================================
	if(frmMain->m_bDEBUG)
		frmMain->qryLog->Add(asSqlQry);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc18_3()
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry  	= "";
	AnsiString  asTable  	= "TB_DOCUMENT18";
	AnsiString  asColumn  	= "JIGU_YEAR";
	AnsiString  asTargetCol	= "";
	AnsiString  asWhere   	= "";
	AnsiString  asGroupBy  	= " GROUP BY YEAR";
	//AnsiString  asOrderBy  	= " ORDER BY YEAR='0000' DESC, YEAR DESC";
	AnsiString  asOrderBy  	= " ORDER BY YEAR DESC";
	AnsiString  asStr  		= "";
	SQLRETURN ret;
	SQLINTEGER m_nVal[2];
	int nIndex = 1;
	STAT_STRUCT	tempDoc;

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));

	asTargetCol	= "DISTINCT CASE LENGTH(" + asColumn + ") WHEN 4 THEN (";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1960' AND SUBSTR(" + asColumn + ", 1, 4) < '1970', '1960~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1950' AND SUBSTR(" + asColumn + ", 1, 4) < '1960', '1950~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1940' AND SUBSTR(" + asColumn + ", 1, 4) < '1950', '1940~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) >= '1930' AND SUBSTR(" + asColumn + ", 1, 4) < '1940', '1930~', ";
	asTargetCol	= asTargetCol + "IF(SUBSTR(" + asColumn + ", 1, 4) != '0000' AND SUBSTR(" + asColumn + ", 1, 4) < '1930', '1900~', SUBSTR(" + asColumn + ", 1, 4)))))))";
	asTargetCol	= asTargetCol + "ELSE '0000' END ";
	asTargetCol	= asTargetCol + "AS YEAR, COUNT(DISTINCT PATH_NAME) AS COUNT";

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempDoc.YEAR, 	    sizeof(tempDoc.YEAR), 	    &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempDoc.COUNT, 	sizeof(tempDoc.COUNT), 		&m_nVal[nIndex-1]); nIndex++;

	//asWhere//
	asSqlQry = "SELECT " + asTargetCol + " FROM " + asTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatDoc18.clear();

	memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	while (SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vStatDoc18.push_back(tempDoc);
		memset(&tempDoc, 0x00, sizeof(STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_nStatRowCount < (int)m_vStatDoc18.size())
		m_nStatRowCount = (int)m_vStatDoc18.size();

	//==================================
	//260617//[REG][DEBUG]
	//==================================
	if(frmMain->m_bDEBUG)
		frmMain->qryLog->Add(asSqlQry);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::Timer1Timer(TObject *Sender)
{
	Timer1->Enabled	= false;

	IMGFINDClick(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::PageControl1Change(TObject *Sender)
{
	if(PageControl1->ActivePage == TabSheet1)
	{
		funcSetComboDoc();

		m_vStatDoc01.clear();
		m_vStatDoc02.clear();
		m_vStatDoc03.clear();
		m_vStatDoc04.clear();
		m_vStatDoc06.clear();
		m_vStatDoc07.clear();
		m_vStatDoc08.clear();
		m_vStatDoc09.clear();
		m_vStatDoc11.clear();
		m_vStatDoc15.clear();
		m_vStatDoc17.clear();
		m_vStatDoc18.clear();

		funcInitStat();
	}
	else if(PageControl1->ActivePage == TabSheet2)//사용자별 문서열람 현황//
	{
		funcInitTabStatUserDoc();
	}
	else if(PageControl1->ActivePage == TabSheet3)//구대장(한글화) 열람 통계//
	{
		funcInitTabStatDoc8();
	}
	else if(PageControl1->ActivePage == TabSheet4)//읍면동별 구축통계//
	{
		//
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcInitTabStatUserDoc()
{
	edtSttDt2->Date 	= Now().FormatString("YYYY-01-01");
	edtEndDt2->Date 	= Now().FormatString("YYYY-MM-DD");
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcInitTabStatDoc8()
{
	AnsiString  asNow	= Now().FormatString("YYYY-MM-DD");
	TDateTime	dtNow	= Now();
	rbView->Checked		= true;
	rbPrint->Checked	= false;
	edtSEndDt->Date 	= Now();
	edtSSttDt->Date 	= IncMonth(Now(), -1);
	cboSUmd->ItemIndex	= 0;
	cboSUmdChange(cboSUmd);
}
//---------------------------------------------------------------------------

//읍면동별 구축통계 - 리스트 초기화, 해제//
void __fastcall TfrmStat::funcInitStringList(bool _bSet)
{
	if(_bSet)
	{
		for(int i = 1; i < DF_DOC_CNT; i++)
		{
			m_slUmdCode[i] = new TStringList();
			m_slUmdCode[i]->Clear();
			m_slUmdCode[i]->Text = "";

			m_slUmdCnt[i] = new TStringList();
			m_slUmdCnt[i]->Clear();
			m_slUmdCnt[i]->Text = "";
		}
	}
	else
	{
		for(int i = 1; i < DF_DOC_CNT; i++)
		{
			if(m_slUmdCode[i] != NULL)
			{
				delete m_slUmdCode[i];
				m_slUmdCode[i]	= NULL;

				delete m_slUmdCnt[i];
				m_slUmdCnt[i]	= NULL;
			}
		}
	}
}
//---------------------------------------------------------------------------


//Create
void __fastcall TfrmStat::funcCreateStatDoc8()
{
	int nCol = 0;

	sgStatDoc8->DefaultColWidth	= 150;

	sgStatDoc8->ColCount  = 4;//
	sgStatDoc8->RowCount  = 2;
	sgStatDoc8->FixedRows = 1;
	sgStatDoc8->FixedCols = 1;

	sgStatDoc8->Cells[nCol++][0]    = "토지소재지";
	sgStatDoc8->Cells[nCol++][0]    = "토지대장(건수)";
	sgStatDoc8->Cells[nCol++][0]    = "임야대장(건수)";
	sgStatDoc8->Cells[nCol++][0]    = "지역별합계";

	::UpdateWindow(sgStatDoc8->Handle);

//	for (int i = 0; i < 2; i++) {
//		for (int j = 0; j < sgStatDoc8->ColCount; j++) {
//			sgStatDoc8->Colors[j][i] = (TColor)RGB(221,232,254);//clInfoBk;
//		}
//	}
}
// ---------------------------------------------------------------------------

void __fastcall TfrmStat::funcInitStatDoc8()
{
	funcCreateStatDoc8();

	for (int i = 1; i < sgStatDoc8->RowCount; i++) {
		sgStatDoc8->Rows[i]->Clear();
	}

	sgStatDoc8->RowCount = 2;

//	for (int i = 0; i < 1; i++)
//		for (int j = 0; j < sgStatDoc8->ColCount; j++)
//			sgStatDoc8->Colors[j][i] = (TColor)RGB(221,232,254);//clInfoBk;
}
// ---------------------------------------------------------------------------

void __fastcall TfrmStat::funcDispStatDoc8()
{
	int index = 2;
	int nCol = 0;
	int nUmdRiSize 		= (int)m_vUMDRICODE.size();
	int	nDocKindSize	= 2;
	int nSize = (int)m_vStat.size();
	AnsiString  asUmdRiCdLabel  = "";
	AnsiString  asUmdRiCdData   = "";
	AnsiString  asSelectUmdRiCd = "";
	AnsiString  asStateCdData   = "";
	AnsiString  asPnu   		= "";
	AnsiString  asDocKindName	= "";
	int			nLandCol		= 1;
	int			nForestCol		= 2;
	int			nSumCol			= 3;

	//
	int *nSumByUmdRi 	= new int[nUmdRiSize];
	int *nSumByDocKind 	= new int[nDocKindSize];

	for (int i = 0; i < nUmdRiSize; i++)
		nSumByUmdRi[i]	= 0;
	for (int j = 0; j < nDocKindSize; j++)
		nSumByDocKind[j]	= 0;

	for (int i = 0; i < nUmdRiSize + 1; i++)
		for (int j = 0; j < nDocKindSize; j++)
			sgStatDoc8->Cells[j+1][i+1] = "0";

	asSelectUmdRiCd	= edtSUmdCd->Text;

//	//================================================
//	sgStatDoc8->LockUpdate	= true;
//	//================================================

	for (int i = 0; i < nUmdRiSize; i++)
	{
		nCol 		= 0;

		if(cboSUmd->ItemIndex > 1)//전체 & 대상지역 제외//220207//
		{
			asUmdRiCdLabel   = m_vUMDRICODE[i].CD;
			if(asUmdRiCdLabel.SubString(1, 3) != (AnsiString)edtSUmdCd->Text)
				continue;
		}
		else
		{
			asUmdRiCdLabel   = m_vUMDRICODE[i].CD;
		}

		for(int j = 0; j < nSize; j++)
		{
			asUmdRiCdData	= (char*)m_vStat[j].UMDRI_CD;
			if(asUmdRiCdLabel != asUmdRiCdData)
				continue;

			asDocKindName		= (char*)m_vStat[j].DOC_KIND;
			if(asDocKindName == "1")//토지대장//
			{
				sgStatDoc8->FontStyles[nLandCol][index] = TFontStyles() << fsBold;
				sgStatDoc8->FontColors[nLandCol][index] = (TColor)RGB(0,0,255);
				sgStatDoc8->Cells[nLandCol][index] = FormatFloat("###,##0", m_vStat[j].COUNT);
				nSumByDocKind[nLandCol-1]	+= m_vStat[j].COUNT;
			}
			else if(asDocKindName == "2")//임야대장//
			{
				sgStatDoc8->FontStyles[nForestCol][index] = TFontStyles() << fsBold;
				sgStatDoc8->FontColors[nForestCol][index] = (TColor)RGB(0,0,255);
				sgStatDoc8->Cells[nForestCol][index] = FormatFloat("###,##0", m_vStat[j].COUNT);
				nSumByDocKind[nForestCol-1]	+= m_vStat[j].COUNT;
			}

			nSumByUmdRi[i]	+= m_vStat[j].COUNT;
		}

		if(cboSUmd->ItemIndex == 1 && nSumByUmdRi[i] == 0)//대상지역 제외//220207//
			continue;

		index++;
	}

//	//================================================
//	sgStatDoc8->AutoSizeColumns(true);
//	sgStatDoc8->LockUpdate	= false;
//	//================================================

	AnsiString 	asStr 	= "";
	int			nCount 	= 0;

	sgStatDoc8->RowColor[1] 	 = clInfoBk;//(TColor)RGB(210,210,210);//(224,243,254);
	sgStatDoc8->FontStyles[0][1] = TFontStyles() << fsBold;
	sgStatDoc8->FontColors[0][1] = (TColor)RGB(255,0,255);

	//SUM : Row 1
	for(int i = 0; i < nDocKindSize; i++)
		nCount += nSumByDocKind[i];

	asStr	= IntToStr(nCount);
	sgStatDoc8->FontStyles[0][1] = TFontStyles() << fsBold;
	sgStatDoc8->FontColors[0][1] = (TColor)RGB(255,0,255);
	sgStatDoc8->Cells[0][1]	= "합계";
	sgStatDoc8->FontStyles[nSumCol][1] = TFontStyles() << fsBold;
	sgStatDoc8->FontColors[nSumCol][1] = (TColor)RGB(255,0,255);
	sgStatDoc8->Cells[nSumCol][1] = FormatFloat("###,##0", asStr.ToInt());
	for (int j = 0; j < nDocKindSize; j++)
	{
		sgStat->FontStyles[j+1][1] = TFontStyles() << fsBold;
		sgStat->FontColors[j+1][1] = (TColor)RGB(255,0,255);
		sgStat->Cells[j+1][1] = FormatFloat("###,##0", nSumByDocKind[j]);
	}

	//SUM : Col 3
	int nRow	= 2;
	for (int i = 0; i < nUmdRiSize; i++)
	{
		if(cboSUmd->ItemIndex > 1)//전체 & 대상지역 제외//220207//
		{
			asUmdRiCdLabel   = m_vUMDRICODE[i].CD;
			if(asUmdRiCdLabel.SubString(1, 3) != (AnsiString)edtSUmdCd->Text)
				continue;
		}
		else
		{
			asUmdRiCdLabel   = m_vUMDRICODE[i].CD;
		}

		if(cboSUmd->ItemIndex == 1 && nSumByUmdRi[i] == 0)//대상지역 제외//220207//
			continue;

		//col 3
		asStr	= IntToStr(nSumByUmdRi[i]);
		if(nSumByUmdRi[i] > 0)
		{
			sgStatDoc8->FontStyles[nSumCol][nRow] = TFontStyles() << fsBold;
			sgStatDoc8->FontColors[nSumCol][nRow] = (TColor)RGB(255,0,255);
			sgStatDoc8->FontStyles[0][nRow] = TFontStyles() << fsBold;
			sgStatDoc8->FontColors[0][nRow] = (TColor)RGB(0,0,255);
		}
		sgStatDoc8->Cells[nSumCol][nRow]	= FormatFloat("###,##0", asStr.ToInt());
		//col 0
		asStr	= (char*)m_vUMDRICODE[i].NM;
		sgStatDoc8->Cells[0][nRow]	= asStr;

		nRow++;
	}

	if(index > 2)   sgStatDoc8->RowCount = nRow;
	else    		sgStatDoc8->RowCount = 2;

	m_nStatDoc8RowCount	= nRow - 2;

	delete nSumByUmdRi;
	delete nSumByDocKind;

	AnsiString temp = FormatFloat("###,##0",index-2);
	lblStatCnt->Caption = "조회건수 : " + temp;
	Application->ProcessMessages();
}
//---------------------------------------------------------------------------


//===========================================================================
//250708//[기능개선]구대장한글화 통계(+사용자별)
//===========================================================================
//Create
void __fastcall TfrmStat::funcCreateStatDoc8_User()
{
	int nCol = 0;

	sgStatDoc8->DefaultColWidth	= 150;

	sgStatDoc8->ColCount  = 7;//
	sgStatDoc8->RowCount  = 2;
	sgStatDoc8->FixedRows = 1;
	sgStatDoc8->FixedCols = 0;

	sgStatDoc8->Cells[nCol++][0]    = "사용자";
	sgStatDoc8->ColWidths[nCol]		= 0;
	sgStatDoc8->Cells[nCol++][0]    = "팀명(업무구분)";
	sgStatDoc8->Cells[nCol++][0]    = "사용일자";
	sgStatDoc8->Cells[nCol++][0]    = "지번";
	sgStatDoc8->ColWidths[nCol]		= 0;
	sgStatDoc8->Cells[nCol++][0]    = "PNU";
	sgStatDoc8->Cells[nCol++][0]    = "업무유형";
	sgStatDoc8->ColWidths[nCol]		= 0;
	sgStatDoc8->Cells[nCol++][0]    = "파일경로";

	::UpdateWindow(sgStatDoc8->Handle);

	//For Save
	nCol = 0;
	sgStatDoc8Save->DefaultColWidth	= 150;

	sgStatDoc8Save->ColCount  = 7;//
	sgStatDoc8Save->RowCount  = 2;
	sgStatDoc8Save->FixedRows = 1;
	sgStatDoc8Save->FixedCols = 0;

	sgStatDoc8Save->Cells[nCol++][0]    = "사용자";
	sgStatDoc8Save->Cells[nCol++][0]    = "팀명(업무구분)";
	sgStatDoc8Save->Cells[nCol++][0]    = "사용일자";
	sgStatDoc8Save->ColWidths[nCol]		= 200;
	sgStatDoc8Save->Cells[nCol++][0]    = "지번";
	sgStatDoc8Save->Cells[nCol++][0]    = "PNU";
	sgStatDoc8Save->Cells[nCol++][0]    = "업무유형";
	sgStatDoc8Save->ColWidths[nCol]		= 300;
	sgStatDoc8Save->Cells[nCol++][0]    = "파일경로";

	::UpdateWindow(sgStatDoc8Save->Handle);
}
// ---------------------------------------------------------------------------

//===========================================================================
//250708//[기능개선]구대장한글화 통계(+사용자별)
//===========================================================================
void __fastcall TfrmStat::funcInitStatDoc8_User()
{
	funcCreateStatDoc8_User();

	for (int i = 1; i < sgStatDoc8->RowCount; i++) {
		sgStatDoc8->Rows[i]->Clear();
	}
	sgStatDoc8->RowCount = 2;

	for (int i = 1; i < sgStatDoc8Save->RowCount; i++) {
		sgStatDoc8Save->Rows[i]->Clear();
	}
	sgStatDoc8Save->RowCount = 2;
}
// ---------------------------------------------------------------------------

//===========================================================================
//250708//[기능개선]구대장한글화 통계(+사용자별)
//===========================================================================
void __fastcall TfrmStat::funcDispStatDoc8_User()
{
	int nRow 	= 1;
	int nCol 	= 0;
	int nSize = (int)m_vStatUser.size();
	AnsiString  asUserName 		= "";
	AnsiString  asActionDt 		= "";
	AnsiString  asLandCd   		= "";
	AnsiString  asLandNm   		= "";
	AnsiString  asPathName 		= "";
	AnsiString  asType			= "";//업무유형//
	int nIndex 	= 1;

	for(int i = 0; i < nSize; i++)
	{
		asType	= (char*)m_vStatUser[i].TYPE;//업무유형//
		if( (asType == "1" && !chkView->Checked)
		 ||	(asType == "2" && !chkPrint->Checked)
		 ||	(asType == "3" && !chkDirect->Checked) )
			continue;

		asUserName  = (char*)m_vStatUser[i].USERNAME;
		asActionDt  = (char*)m_vStatUser[i].ACTION_DT;
		asLandCd 	= (char*)m_vStatUser[i].PNU;
		asLandNm 	= frmMain->func_ConvertLandcdToAddress(asLandCd);
		asPathName 	= m_vStatUser[i].PATH_NAME;

		//
		nCol	= 0;
		sgStatDoc8->Cells[nCol++][nRow]	= asUserName;
		sgStatDoc8->Cells[nCol++][nRow]	= "";
		sgStatDoc8->Cells[nCol++][nRow]	= asActionDt;
		sgStatDoc8->Cells[nCol++][nRow]	= asLandNm;
		sgStatDoc8->Cells[nCol++][nRow]	= asLandCd;
		//
		if(asType == "1")		sgStatDoc8->Cells[nCol++][nRow]	= "열람";
		else if(asType == "2")	sgStatDoc8->Cells[nCol++][nRow]	= "인쇄";
		else if(asType == "3")	sgStatDoc8->Cells[nCol++][nRow]	= "자료보정";
		//
		sgStatDoc8->Cells[nCol++][nRow]	= asPathName;

		//For Save
		nCol	= 0;
		sgStatDoc8Save->Cells[nCol++][nRow]	= asUserName;
		sgStatDoc8Save->Cells[nCol++][nRow]	= "";
		sgStatDoc8Save->Cells[nCol++][nRow]	= asActionDt;
		sgStatDoc8Save->Cells[nCol++][nRow]	= asLandNm;
		sgStatDoc8Save->Cells[nCol++][nRow]	= asLandCd;
		//
		if(asType == "1")		sgStatDoc8Save->Cells[nCol++][nRow]	= "열람";
		else if(asType == "2")	sgStatDoc8Save->Cells[nCol++][nRow]	= "인쇄";
		else if(asType == "3")	sgStatDoc8Save->Cells[nCol++][nRow]	= "자료보정";
		//
		sgStatDoc8Save->Cells[nCol++][nRow]	= asPathName;

		//
		nRow++;
	}

	sgStatDoc8->RowCount 	= nRow;
	sgStatDoc8->Row 		= 1;

	//
	sgStatDoc8Save->RowCount 	= nRow;
	sgStatDoc8Save->Row 		= 1;

	m_nStatDoc8RowCount		= (nRow > 1 ? nRow : 0);

	AnsiString temp = FormatFloat("###,##0",nRow-1);
	lblStatCnt->Caption = "조회건수 : " + temp;
	Application->ProcessMessages();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::cboSUmdChange(TObject *Sender)
{
	funcChangeSUmd();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcChangeSUmd()
{
	AnsiString asUmdNm	= "";
	AnsiString asUmdCd	= "";

	asUmdNm = cboSUmd->Text;
	if(cboSUmd->Text == "::전체" || cboSUmd->Text == "::대상지역")//220207//
	{
		edtSUmdCd->Text = "";
	}
	else
	{
		edtSUmdCd->Text = asUmdNm.SubString(2, 3);
		asUmdCd = asUmdNm.SubString(2, 3);
	}

	cboSUmd->Refresh();

	//자동조회하지 말것 - '검색'버튼 동작시에만 조회//funcReadStatDoc8();//211214//
}
// ---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadUmdData()
{
	cboSUmd->Items->Clear();
	cboSUmd->Items->Add("::전체");
	cboSUmd->Items->Add("::대상지역");//220207//

	SQLCHAR     m_cVal[2][30];
	SQLINTEGER  m_nVal[2];
	SQLRETURN   ret;
	int			nIndex = 1;
	UMDDATA_STRUCT          tempUMD;
	memset(&tempUMD, 0x00, sizeof(UMDDATA_STRUCT));

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, tempUMD.UMD_CD  , sizeof(tempUMD.UMD_CD)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, tempUMD.UMD_NM  , sizeof(tempUMD.UMD_NM)   	, &m_nVal[nIndex-1]); nIndex++;

	AnsiString  asSqlQry;
	asSqlQry = "SELECT DISTINCT UMD_CD, UMD_NM FROM SIDO_CODE WHERE SIDOSGG_CD ='" + frmMain->_SIDOCODE.Trim() + "' ORDER BY UMD_CD ASC";
	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	m_vUMD.clear();

	AnsiString result[2];
	char temp[30];

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
	}
	else{
		for(int i=0; i<2; i++) result[i] = "";

		while(SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {

			result[0] = tempUMD.UMD_CD;
			result[1] = tempUMD.UMD_NM;

			if(result[0] != "000" && result[1] != ""){
				cboSUmd->Items->Add("(" + result[0] + ")" + result[1]);

				m_vUMD.push_back(tempUMD);
			}

			memset(&tempUMD, 0x00, sizeof(UMDDATA_STRUCT));

		};
		if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);
	}

	cboSUmd->ItemIndex      = -1;
	if(cboSUmd->Items->Count > 0)
		cboSUmd->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::funcReadStatDoc8()
{
	//==========================================================
	//Only TB_ROAD_REGISTJIBUN + TB_ROAD_LANDLIST COUNT
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry		 = "";
	AnsiString  asSqlTable		 = "TB_COPY_DOC08";
	AnsiString  asSqlCol		 = "";
	AnsiString  asWhere			 = "";
	AnsiString  asGroupBy		 = "";
	AnsiString  asOrderBy		 = "";
	AnsiString 	asUmdRiCol 		= "SUBSTR(PNU, 6, 5)";
	AnsiString 	asWhereUmdRi 	= "";
	AnsiString 	asUmdRiCd		= "";
	AnsiString 	asStr			= "";
	bool		bRiCd			= false;
	SQLRETURN ret;
	AnsiString temp, result;
	DOC8_STAT_STRUCT 				tempStat;

	SQLINTEGER m_nVal[3];

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempStat, 0x00, sizeof(DOC8_STAT_STRUCT));
	int nIndex = 1;

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, tempStat.UMDRI_CD  , sizeof(tempStat.UMDRI_CD)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, tempStat.DOC_KIND  , sizeof(tempStat.DOC_KIND)   	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, &tempStat.COUNT    , sizeof(tempStat.COUNT)     	, &m_nVal[nIndex-1]); nIndex++;

	if(rbView->Checked)
		asWhere	= " WHERE TYPE='1'";
	else if(rbPrint->Checked)
		asWhere	= " WHERE TYPE='2'";
	//==========================================================================
	//241107//#한글화편집#DirectTable//
	//==========================================================================
	else if(rbDirect->Checked)
		asWhere	= " WHERE TYPE='3'";

	//DATE
	AnsiString  asSttDt	= DateToStr(edtSSttDt->Date);
	AnsiString  asEndDt	= DateToStr(edtSEndDt->Date);
	asWhere	= asWhere + " AND SUBSTR(ACTION_DT, 1, 10) >= '" + asSttDt + "' AND SUBSTR(ACTION_DT, 1, 10) <= '" + asEndDt + "'";

	if(cboSUmd->ItemIndex > 1)//전체 & 대상지역 제외//220207//
	{
		asUmdRiCd	= edtSUmdCd->Text;
		asWhereUmdRi	= "SUBSTR(PNU, 6, 3)";

		if( !asUmdRiCd.IsEmpty() )
		{
			if( !asWhere.IsEmpty() )
				asWhere	= asWhere + " AND ";
			else
				asWhere	= " WHERE ";

			asWhere	= asWhere + asWhereUmdRi + " = '" + asUmdRiCd + "'";
		}
	}

	asSqlCol       = asUmdRiCol + " AS UMDRI_CD, SUBSTR(PNU, 11, 1) AS DOC_KIND, COUNT(DISTINCT PATH_NAME) AS COUNT";

	asGroupBy   = " GROUP BY UMDRI_CD, DOC_KIND";
	asOrderBy   = " ORDER BY UMDRI_CD, DOC_KIND ASC";
	asSqlQry	= "SELECT DISTINCT " + asSqlCol + " FROM " +  asSqlTable + asWhere + asGroupBy + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}


	m_vStat.clear();
	funcInitStatDoc8();


	memset(&tempStat, 0x00, sizeof(DOC8_STAT_STRUCT));
	while(SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA)
	{
		m_vStat.push_back(tempStat);
		memset(&tempStat, 0x00, sizeof(DOC8_STAT_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_vStat.size() > 0)
		funcDispStatDoc8();
}
//---------------------------------------------------------------------------


//===========================================================================
//250708//[기능개선]구대장한글화 통계(+사용자별)
//===========================================================================
void __fastcall TfrmStat::funcReadStatDoc8_User()
{
	//==========================================================
	//Only TB_ROAD_REGISTJIBUN + TB_ROAD_LANDLIST COUNT
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry		 = "";
	AnsiString  asSqlTable		 = "TB_COPY_DOC08 A, TB_OLDLANDDOC_PATHLIST B";
	AnsiString  asSqlCol		 = "A.*, B.PATH_NAME";
	AnsiString  asWhere			 = "";
	AnsiString  asGroupBy		 = "";
	AnsiString  asOrderBy		 = "";
	AnsiString 	asStr			= "";
	SQLRETURN ret;
	AnsiString temp, result;
	DOC8_STAT_USER_STRUCT 				tempStat;

	SQLINTEGER m_nVal[7];

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempStat, 0x00, sizeof(DOC8_STAT_USER_STRUCT));
	int nIndex = 1;

/*
typedef struct {
	//from TB_COPY_DOC08.*, TB_OLDLANDDOC_PATHLIST.PATH_NAME
	int		SEQNO;
	int		TYPE;//1.열람, 2:인쇄, 3:편집//
	char 	ACTION_DT[19+1];//2025-07-08 12:34:56//
	char 	USERNAME[64+1];
	char 	PNU[19+1];
	int		PATHLIST_SEQNO;
	char 	PATH_NAME[255+1];
}DOC8_STAT_USER_STRUCT;
*/
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, &tempStat.SEQNO			, sizeof(tempStat.SEQNO)     		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, tempStat.TYPE    			, sizeof(tempStat.TYPE)     		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, tempStat.ACTION_DT  		, sizeof(tempStat.ACTION_DT)   		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, tempStat.USERNAME  		, sizeof(tempStat.USERNAME)   		, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, tempStat.PNU  				, sizeof(tempStat.PNU)   			, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, &tempStat.PATHLIST_SEQNO   , sizeof(tempStat.PATHLIST_SEQNO)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, tempStat.PATH_NAME  		, sizeof(tempStat.PATH_NAME)   		, &m_nVal[nIndex-1]); nIndex++;

	//TYPE
	if(chkView->Checked)
	{
		asWhere = " (TYPE='1'";
	}
	if(chkPrint->Checked)
	{
		if( asWhere.IsEmpty() )
			asWhere = " (TYPE='2'";
		else
			asWhere = asWhere + " OR TYPE='2'";
	}
	if(chkDirect->Checked)
	{
		if( asWhere.IsEmpty() )
			asWhere = " (TYPE='3'";
		else
			asWhere = asWhere + " OR TYPE='3')";
	}
	asWhere = " WHERE " + asWhere + ")";

	//DATE
	AnsiString  asSttDt	= DateToStr(edtSSttDt->Date);
	AnsiString  asEndDt	= DateToStr(edtSEndDt->Date);
	asWhere	= asWhere + " AND SUBSTR(ACTION_DT, 1, 10) >= '" + asSttDt + "' AND SUBSTR(ACTION_DT, 1, 10) <= '" + asEndDt + "'";

	asWhere = asWhere + " AND A.PNU != ''";//260212//

	asWhere	= asWhere + " AND A.PATHLIST_SEQNO=B.SEQNO";

	asOrderBy   = " ORDER BY SEQNO ASC";
	asSqlQry	= "SELECT " + asSqlCol + " FROM " +  asSqlTable + asWhere + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatUser.clear();
	funcInitStatDoc8_User();

	memset(&tempStat, 0x00, sizeof(DOC8_STAT_USER_STRUCT));
	while(SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA)
	{
		m_vStatUser.push_back(tempStat);
		memset(&tempStat, 0x00, sizeof(DOC8_STAT_USER_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_vStatUser.size() > 0)
		funcDispStatDoc8_User();
}
//---------------------------------------------------------------------------

//===========================================================================
//250708//[기능개선]구대장한글화 통계(+사용자별)
//===========================================================================
//SELECT B.FT_NAME, A.FT_DOC, A.CNT
//FROM (SELECT DISTINCT FT_ID, FT_DOC, COUNT(*) AS CNT FROM tb_user4 WHERE (FT_ACTION=4 OR FT_ACTION=5 OR FT_ACTION=7) GROUP BY FT_ID, FT_DOC) A,
//(SELECT FT_ID, FT_NAME FROM tb_user1) B
//WHERE A.FT_ID=B.FT_ID
//ORDER BY B.FT_NAME, A.FT_DOC
void __fastcall TfrmStat::funcReadStatUserDoc()
{
	//==========================================================
	//Only TB_ROAD_REGISTJIBUN + TB_ROAD_LANDLIST COUNT
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry		 = "";
	AnsiString  asSqlTableA		 = "";
	AnsiString  asSqlTableB		 = "";
	AnsiString  asSqlCol		 = "B.FT_NAME, A.FT_ID, A.FT_DOC, A.CNT ";
	AnsiString  asWhere			 = "A.FT_ID=B.FT_ID ";
	AnsiString  asWhereA		 = "";
	AnsiString  asGroupBy		 = "";
	AnsiString  asOrderBy		 = "ORDER BY B.FT_NAME, A.FT_DOC";
	AnsiString 	asFtId			 = "";
	AnsiString 	asFtIdBck		 = "";
	SQLRETURN ret;
	AnsiString temp, result;
	STAT_USERDOC_STRUCT 				tempStat;
	STAT_USERDOC_STRUCT 				tempStatSum;

	SQLINTEGER m_nVal[4];

	memset(m_nVal, 0x00, sizeof(m_nVal));
	memset(&tempStat, 0x00, sizeof(STAT_USERDOC_STRUCT));
	memset(&tempStatSum, 0x00, sizeof(STAT_USERDOC_STRUCT));
	int nIndex = 1;

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, tempStat.USERNAME	, sizeof(tempStat.USERNAME)	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, tempStat.FT_ID		, sizeof(tempStat.FT_ID)	, &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, &tempStat.FT_DOC	, sizeof(tempStat.FT_DOC)   , &m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, &tempStat.COUNT    , sizeof(tempStat.COUNT)    , &m_nVal[nIndex-1]); nIndex++;

	//DATE
	AnsiString  asSttDt	= DateToStr(edtSttDt2->Date);
	AnsiString  asEndDt	= DateToStr(edtEndDt2->Date);
	asWhereA	= asWhereA + " AND SUBSTR(FT_ACTIONDATE, 1, 10) >= '" + asSttDt + "' AND SUBSTR(FT_ACTIONDATE, 1, 10) <= '" + asEndDt + "'";
	asSqlTableA	= "(SELECT DISTINCT FT_ID, FT_DOC, COUNT(*) AS CNT FROM tb_user4 WHERE (FT_ACTION=4 OR FT_ACTION=5 OR FT_ACTION=7)" + asWhereA + " GROUP BY FT_ID, FT_DOC) A, ";
	asSqlTableB	= "(SELECT FT_ID, FT_NAME FROM tb_user1) B ";

	asSqlQry	= "SELECT " + asSqlCol + "FROM " +  asSqlTableA + asSqlTableB + "WHERE " + asWhere + asOrderBy;

	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return;
	}

	m_vStatUserDoc.clear();
	funcInitStatUserDoc();

	memset(&tempStat, 0x00, sizeof(STAT_USERDOC_STRUCT));
	memset(&tempStatSum, 0x00, sizeof(STAT_USERDOC_STRUCT));
	while(SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA)
	{
		asFtId	= (char*)tempStat.FT_ID;
		if(!asFtIdBck.IsEmpty() && asFtId != asFtIdBck)
		{
			for(int j = 0; j < 5; j++)
				tempStatSum.COUNT += tempStatSum.DOC_NO[j];
			m_vStatUserDoc.push_back(tempStatSum);
			memset(&tempStatSum, 0x00, sizeof(STAT_USERDOC_STRUCT));
		}

		//
		asFtIdBck = asFtId;
		strcpy(tempStatSum.USERNAME, tempStat.USERNAME);
		strcpy(tempStatSum.FT_ID, tempStat.FT_ID);
		if(tempStat.FT_DOC == 8)		tempStatSum.DOC_NO[0] = tempStat.COUNT;
		else if(tempStat.FT_DOC == 7)	tempStatSum.DOC_NO[1] = tempStat.COUNT;
		else if(tempStat.FT_DOC == 1)	tempStatSum.DOC_NO[2] = tempStat.COUNT;
		else if(tempStat.FT_DOC == 2)	tempStatSum.DOC_NO[3] = tempStat.COUNT;
		else							tempStatSum.DOC_NO[4] = tempStat.COUNT;

		memset(&tempStat, 0x00, sizeof(STAT_USERDOC_STRUCT));
	};

	//Last User
	if(!asFtIdBck.IsEmpty() && asFtId != asFtIdBck)
	{
		m_vStatUserDoc.push_back(tempStatSum);
		memset(&tempStatSum, 0x00, sizeof(STAT_USERDOC_STRUCT));
	}

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	if(m_vStatUserDoc.size() > 0)
		funcDispStatUserDoc();
}
//---------------------------------------------------------------------------


//===========================================================================
//250708//[기능개선]구대장한글화 통계(+사용자별)
//===========================================================================
//Create
void __fastcall TfrmStat::funcCreateStatUserDoc()
{
	int nCol = 0;

	sgStatUserDoc->DefaultColWidth	= 100;

	sgStatUserDoc->ColCount  = 7;//
	sgStatUserDoc->RowCount  = 2;
	sgStatUserDoc->FixedRows = 1;
	sgStatUserDoc->FixedCols = 0;

	sgStatUserDoc->Cells[nCol++][0]    = "사용자";
	sgStatUserDoc->Cells[nCol++][0]    = "구대장";
	sgStatUserDoc->Cells[nCol++][0]    = "지적도";
	sgStatUserDoc->Cells[nCol++][0]    = "이동결의서";
	sgStatUserDoc->Cells[nCol++][0]    = "측량결과도";
	sgStatUserDoc->Cells[nCol++][0]    = "기타문서";
	sgStatUserDoc->Cells[nCol++][0]    = "소계";

	::UpdateWindow(sgStatUserDoc->Handle);
}
// ---------------------------------------------------------------------------

//===========================================================================
//250708//[기능개선]구대장한글화 통계(+사용자별)
//===========================================================================
void __fastcall TfrmStat::funcInitStatUserDoc()
{
	for (int i = 1; i < sgStatUserDoc->RowCount; i++) {
		sgStatUserDoc->Rows[i]->Clear();
		sgStatUserDoc->RowColor[i] = clWhite;

		for (int j = 0; j < sgStatUserDoc->ColCount; j++) {
			sgStatUserDoc->FontSizes[j][i] 	= sgStatUserDoc->Font->Size;
			sgStatUserDoc->FontStyles[j][i] = TFontStyles() >> fsBold;
		}
	}
	sgStatUserDoc->RowCount = 2;
}
// ---------------------------------------------------------------------------

//===========================================================================
//250708//[기능개선]구대장한글화 통계(+사용자별)
//===========================================================================
void __fastcall TfrmStat::funcDispStatUserDoc()
{
	int nRow 	= 1;
	int nCol 	= 0;
	int nSize 	= (int)m_vStatUserDoc.size();
	int nSum[6] = {0,};
	int nIndex 	= 1;

	for(int i = 0; i < nSize; i++)
	{
		//
		nCol	= 0;
		sgStatUserDoc->Cells[nCol++][nRow]	= (char*)m_vStatUserDoc[i].USERNAME;
		sgStatUserDoc->Cells[nCol++][nRow]	= FormatFloat("#,##0", m_vStatUserDoc[i].DOC_NO[0]);
		sgStatUserDoc->Cells[nCol++][nRow]	= FormatFloat("#,##0", m_vStatUserDoc[i].DOC_NO[1]);
		sgStatUserDoc->Cells[nCol++][nRow]	= FormatFloat("#,##0", m_vStatUserDoc[i].DOC_NO[2]);
		sgStatUserDoc->Cells[nCol++][nRow]	= FormatFloat("#,##0", m_vStatUserDoc[i].DOC_NO[3]);
		sgStatUserDoc->Cells[nCol++][nRow]	= FormatFloat("#,##0", m_vStatUserDoc[i].DOC_NO[4]);
		sgStatUserDoc->FontSizes[nCol][nRow] 	= sgStatUserDoc->FixedFont->Size;
		sgStatUserDoc->FontStyles[nCol][nRow] 	= TFontStyles() << fsBold;
		sgStatUserDoc->Cells[nCol++][nRow]	= FormatFloat("#,##0", m_vStatUserDoc[i].COUNT);

		for(int j = 0; j < 5; j++)
		{
			nSum[j] += m_vStatUserDoc[i].DOC_NO[j];
		}

		//
		nRow++;
	}

	nCol = 0;
	sgStatUserDoc->RowColor[nRow] = clBtnFace;
	sgStatUserDoc->FontSizes[nCol][nRow] 	= sgStatUserDoc->FixedFont->Size;
	sgStatUserDoc->FontStyles[nCol][nRow] 	= TFontStyles() << fsBold;
	sgStatUserDoc->Cells[nCol++][nRow]	= "합계";
	for(int j = 0; j < 5; j++)
	{
		sgStatUserDoc->FontSizes[nCol][nRow] 	= sgStatUserDoc->FixedFont->Size;
		sgStatUserDoc->FontStyles[nCol][nRow] 	= TFontStyles() << fsBold;
		sgStatUserDoc->Cells[nCol++][nRow] = FormatFloat("#,##0", nSum[j]);
		nSum[5] += nSum[j];
	}
	sgStatUserDoc->FontSizes[nCol][nRow] 	= sgStatUserDoc->FixedFont->Size;
	sgStatUserDoc->FontStyles[nCol][nRow] 	= TFontStyles() << fsBold;
	sgStatUserDoc->Cells[nCol++][nRow] = FormatFloat("#,##0", nSum[5]);
	nRow++;

	sgStatUserDoc->RowCount = nRow;
	sgStatUserDoc->Row 		= 1;

	sgStatUserDoc->Refresh();

	m_nStatUserDocRowCount		= (nRow > 1 ? nRow : 0);

	AnsiString temp = FormatFloat("###,##0",nRow-2);
	lblStatCnt2->Caption = "사용자 수 : " + temp;
	Application->ProcessMessages();
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::sgStatUserDocGetAlignment(TObject *Sender, int ARow, int ACol,
		  TAlignment &HAlign, TVAlignment &VAlign)
{
	if(ARow > 0 && ACol != 0)
		HAlign = taRightJustify;
	else
		HAlign = taCenter;
	//
	VAlign = vtaCenter;
}
//---------------------------------------------------------------------------

void __fastcall TfrmStat::sgStatDocGetAlignment(TObject *Sender, int ARow, int ACol,
          TAlignment &HAlign, TVAlignment &VAlign)
{
	if(ARow > 0 && ACol == 0)
		HAlign = taLeftJustify;
	else if(ARow > 0 && ACol != 0)
		HAlign = taRightJustify;
	else
		HAlign = taCenter;
	//
	VAlign = vtaCenter;
}
//---------------------------------------------------------------------------



//===========================================================================
//250708//[기능개선]구대장한글화 통계(+사용자별)
//===========================================================================
//Create
void __fastcall TfrmStat::funcCreateStatDoc()
{
	int nCol = 0;

	sgStatDoc->DefaultColWidth	= 100;

	sgStatDoc->ColCount  = 7;//
	sgStatDoc->RowCount  = 2;
	sgStatDoc->FixedRows = 1;
	sgStatDoc->FixedCols = 0;

	sgStatDoc->Cells[nCol++][0]    = "읍면동";
	sgStatDoc->Cells[nCol++][0]    = "구대장";
	sgStatDoc->Cells[nCol++][0]    = "지적도";
	sgStatDoc->Cells[nCol++][0]    = "이동결의서";
	sgStatDoc->Cells[nCol++][0]    = "측량결과도";
	sgStatDoc->Cells[nCol++][0]    = "기타문서";
	sgStatDoc->Cells[nCol++][0]    = "소계";

	::UpdateWindow(sgStatDoc->Handle);
}
// ---------------------------------------------------------------------------

//===========================================================================
//250708//[기능개선]구대장한글화 통계(+사용자별)
//===========================================================================
void __fastcall TfrmStat::funcInitStatDoc()
{
	for (int i = 1; i < sgStatDoc->RowCount; i++) {
		sgStatDoc->Rows[i]->Clear();
		sgStatDoc->RowColor[i] = clWhite;

		for (int j = 0; j < sgStatDoc->ColCount; j++) {
			sgStatDoc->FontSizes[j][i] 	= sgStatDoc->Font->Size;
			sgStatDoc->FontStyles[j][i] = TFontStyles() >> fsBold;
		}
	}
	sgStatDoc->RowCount = 2;
}
// ---------------------------------------------------------------------------

//===========================================================================
//250708//[기능개선]구대장한글화 통계(+사용자별)
//===========================================================================
void __fastcall TfrmStat::funcDispStatDoc()
{
	int nRow 	= 1;
	int nCol	= 0;
	int nSize 	= (int)m_vUMD.size();
	int nSum[7] = {0,};
	int nIndex 	= 1;

	for(int i = 0; i < nSize; i++)
	{
		AnsiString  asUmdCd = (char*)m_vUMD[i].UMD_CD;
		AnsiString  asUmdNm = (char*)m_vUMD[i].UMD_NM;
		int nSubSum		= 0;
		int nListIdx 	= -1;

		for (int j = 1; j < sgStatDoc->ColCount; j++)
			sgStatDoc->Cells[j][nRow] = "0";

		sgStatDoc->Cells[0][nRow] = "(" + asUmdCd + ")" + asUmdNm;
		//
		for(int z = 1; z < DF_DOC_CNT; z++)
		{
			if(z == 8)		nCol = 1;
			else if(z == 7)	nCol = 2;
			else if(z == 1)	nCol = 3;
			else if(z == 2)	nCol = 4;
			else 			nCol = 5;

			if( frmMain->INIINFO.B_DOCKIND[z] && m_slUmdCode[z]->Count > 0)
			{
				int nCount 	= 0;
				nListIdx = m_slUmdCode[z]->IndexOf(asUmdCd);
				if(nListIdx > -1)
					nCount = StrToInt(m_slUmdCnt[z]->Strings[nListIdx]);

				if(nCol != 5)
				{
					sgStatDoc->Cells[nCol][nRow]	= FormatFloat("#,##0", nCount);
				}
				else
				{
					AnsiString asCnt = sgStatDoc->Cells[nCol][nRow];
					asCnt = StringReplace(asCnt, ",", "", TReplaceFlags() << rfReplaceAll);
					if(asCnt == "")	asCnt = "0";
					nCount += StrToInt(asCnt);
					sgStatDoc->Cells[nCol][nRow]	= FormatFloat("#,##0", nCount);
				}

				nSubSum	+= nCount;
				nSum[nCol-1] += nCount;
			}
		}

		//소계//
		sgStatDoc->Cells[sgStatDoc->ColCount-1][nRow]	= FormatFloat("#,##0", nSubSum);
		//
		nRow++;
	}

	nCol = 0;
	sgStatDoc->RowColor[nRow] = clBtnFace;
	sgStatDoc->FontSizes[nCol][nRow] 	= sgStatDoc->FixedFont->Size;
	sgStatDoc->FontStyles[nCol][nRow] 	= TFontStyles() << fsBold;
	sgStatDoc->Cells[nCol++][nRow]	= "합계";
	for(int j = 0; j < 5; j++)
	{
		sgStatDoc->FontSizes[nCol][nRow] 	= sgStatDoc->FixedFont->Size;
		sgStatDoc->FontStyles[nCol][nRow] 	= TFontStyles() << fsBold;
		sgStatDoc->Cells[nCol++][nRow] = FormatFloat("#,##0", nSum[j]);
		nSum[5] += nSum[j];
	}
	sgStatDoc->FontSizes[nCol][nRow] 	= sgStatDoc->FixedFont->Size;
	sgStatDoc->FontStyles[nCol][nRow] 	= TFontStyles() << fsBold;
	sgStatDoc->Cells[nCol++][nRow] = FormatFloat("#,##0", nSum[5]);
	nRow++;

	sgStatDoc->RowCount = nRow;
	sgStatDoc->Row 		= 1;

	sgStatDoc->Refresh();

	m_nStatDocRowCount		= (nRow > 1 ? nRow : 0);

	if(rbUmdPath->Checked)	lblUnit->Caption = "(단위: 면)";
	else					lblUnit->Caption = "(단위: 건)";

	AnsiString temp = FormatFloat("###,##0",nRow-2);
	lblStatCnt4->Caption = "사용자 수 : " + temp;
	Application->ProcessMessages();
}
//---------------------------------------------------------------------------


//===========================================================================
//250711//[기능개선]읍면동별 구축통계
//===========================================================================
//# 면수
//SELECT DISTINCT SUBSTRING(AF_PNU, 1, 8) AS UMD, COUNT(DISTINCT PATH_NAME) AS PATH_CNT FROM tb_document01 WHERE (AF_PNU LIKE '44150%') GROUP BY UMD;
//SELECT DISTINCT SUBSTRING(AF_PNU, 1, 8) AS UMD, COUNT(DISTINCT PATH_NAME) AS PATH_CNT FROM tb_document02 WHERE (AF_PNU! LIKE '44150%') GROUP BY UMD;
//SELECT DISTINCT UMD, COUNT(DISTINCT PATH_NAME) AS PATH_CNT FROM tb_document07 WHERE (UMD LIKE '44150%') GROUP BY UMD;
//SELECT DISTINCT SUBSTRING(PNU, 1, 8) AS UMD, COUNT(DISTINCT PATH_NAME) AS PATH_CNT FROM tb_document08 WHERE (PNU LIKE '44150%') GROUP BY UMD;
//
//# 건수
//SELECT DISTINCT SUBSTRING(AF_PNU, 1, 8) AS UMD, COUNT(*) AS RECORD_CNT FROM tb_document01 WHERE (AF_PNU LIKE '44150%') GROUP BY UMD;
//SELECT DISTINCT SUBSTRING(AF_PNU, 1, 8) AS UMD, COUNT(*) AS RECORD_CNT FROM tb_document02 WHERE ( LIKE '44150%') GROUP BY UMD;
//SELECT DISTINCT UMD, COUNT(*) AS RECORD_CNT FROM tb_document07 WHERE (UMD LIKE '44150%') GROUP BY UMD;
//SELECT DISTINCT SUBSTRING(PNU, 1, 8) AS UMD, COUNT(*) AS RECORD_CNT FROM tb_document08 WHERE (PNU LIKE '44150%') GROUP BY UMD;
void __fastcall TfrmStat::funcReadStatDoc(int _nDocNo)
{
	//==========================================================
	//Only TB_ROAD_REGISTJIBUN + TB_ROAD_LANDLIST COUNT
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString  asSqlQry	= "";
	AnsiString  asSqlTable	= "";
	AnsiString  asSqlCol	= "";
	AnsiString  asColumn1	= "";
	AnsiString  asColumn2	= "";
	AnsiString  asColumn3	= "";
	AnsiString  asWhere		= "";
	AnsiString  asGroupBy	= " GROUP BY UMD";
	AnsiString 	sConnStr 	= "";
	int			nArrayIndex = 0;

	//Init//
	funcInitStatDoc();

	sConnStr = (char*)frmSql->m_InCon;

	ADOConnection1->Connected = false;
	ADOConnection1->ConnectionString = sConnStr;

	ADOQuery1->ConnectionString = sConnStr;
	//
	ADOQuery1->DisableControls();
	ADOQuery1->Close();
	ADOQuery1->Connection = ADOConnection1;

	//===============================
	//읍면동(코드), 읍면동(명)
	//===============================
	if(_nDocNo == 1 || _nDocNo == 2 || _nDocNo == 3 || _nDocNo == 6)	asColumn1 = "AF_PNU";
	else if(_nDocNo == 7)												asColumn1 = "UMD";
	else                                            					asColumn1 = "PNU";

	if(rbUmdPath->Checked)	asColumn2 = "DISTINCT PATH_NAME";
	else                    asColumn2 = "*";

	if(_nDocNo == 7)        asSqlCol = "DISTINCT UMD";
	else                    asSqlCol = "DISTINCT SUBSTRING(" + asColumn1 + ", 6, 3) as UMD";
	asSqlCol += ", COUNT(" + asColumn2 + ") as CNT";

	if(_nDocNo == 7)	asColumn3 = "SIDOSGG";
	else                asColumn3 = asColumn1;

	asSqlTable.sprintf("TB_DOCUMENT%02d", _nDocNo);

	asSqlQry.sprintf("SELECT %s FROM %s WHERE (%s LIKE '%s%') GROUP BY UMD", asSqlCol, asSqlTable.Trim(), asColumn3, frmMain->_SIDOCODE);

	//
	ADOQuery1->SQL->Text = asSqlQry;
	ADOQuery1->Open();

//	if(_nDocNo == 8)		nArrayIndex = 0;
//	else if(_nDocNo == 7)	nArrayIndex = 1;
//	else if(_nDocNo == 1)	nArrayIndex = 2;
//	else if(_nDocNo == 2)	nArrayIndex = 3;
//	else					nArrayIndex = 4;

	while(!ADOQuery1->Eof)
	{
		AnsiString  asData = "";

		for(int i = 0; i < ADOQuery1->Fields->Count; i++)
		{
			asData = ADOQuery1->Fields->Fields[i]->AsString;
			if(i == 0)	m_slUmdCode[_nDocNo]->Add(asData);
			else        m_slUmdCnt[_nDocNo]->Add(asData);
		}

		ADOQuery1->Next();
	}
	ADOQuery1->Close();

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);
}
//---------------------------------------------------------------------------


//[이동결의서]필지정보 없는 문서 중 필지정보 있는 문서에 1개의 읍면동만 존재하는 경우 AF_PNU를 해당 읍면동 코드를 채우는 Query//
//UPDATE
//tb_document01 Z,
//(SELECT KWON_NO, PRCS_DATE, MEASURE_TYPE, SUBSTRING(AF_PNU, 1, 8) AS UMD FROM tb_document01 WHERE PATH_NAME IN (SELECT A.PATH_NAME FROM (SELECT DISTINCT PATH_NAME, COUNT(DISTINCT SUBSTRING(AF_PNU, 6, 3)) AS CNT FROM tb_document01 WHERE AF_PNU!='' GROUP BY PATH_NAME HAVING CNT = 1) A)) Y
//SET Z.AF_PNU=Y.UMD
//WHERE (Z.BF_PNU='' AND Z.AF_PNU='') AND Z.KWON_NO=Y.KWON_NO AND Z.PRCS_DATE=Y.PRCS_DATE AND Z.MEASURE_TYPE=Y.MEASURE_TYPE
//
//SELECT DISTINCT SUBSTRING(AF_PNU, 1, 8) AS UMD, COUNT(DISTINCT PATH_NAME) AS PATH_CNT FROM tb_document01 WHERE (AF_PNU LIKE '44150%') GROUP BY UMD;
//SELECT DISTINCT SUBSTRING(AF_PNU, 1, 8) AS UMD, COUNT(*) AS RECORD_CNT FROM tb_document01 WHERE (AF_PNU LIKE '44150%') GROUP BY UMD;
//SELECT DISTINCT SUBSTRING(AF_PNU, 1, 8) AS UMD, COUNT(DISTINCT PATH_NAME) AS PATH_CNT FROM tb_document02 WHERE (AF_PNU! LIKE '44150%') GROUP BY UMD;
//SELECT DISTINCT SUBSTRING(AF_PNU, 1, 8) AS UMD, COUNT(*) AS RECORD_CNT FROM tb_document02 WHERE ( LIKE '44150%') GROUP BY UMD;
//SELECT DISTINCT UMD, COUNT(DISTINCT PATH_NAME) AS PATH_CNT FROM tb_document07 WHERE (UMD LIKE '44150%') GROUP BY UMD;
//SELECT DISTINCT UMD, COUNT(*) AS RECORD_CNT FROM tb_document07 WHERE (UMD LIKE '44150%') GROUP BY UMD;
//SELECT DISTINCT SUBSTRING(PNU, 1, 8) AS UMD, COUNT(DISTINCT PATH_NAME) AS PATH_CNT FROM tb_document08 WHERE (PNU LIKE '44150%') GROUP BY UMD;
//SELECT DISTINCT SUBSTRING(PNU, 1, 8) AS UMD, COUNT(*) AS RECORD_CNT FROM tb_document08 WHERE (PNU LIKE '44150%') GROUP BY UMD;

//CREATE INDEX IDX_STAT ON TB_DOCUMENT01 (AF_PNU);
//CREATE INDEX IDX_STAT ON TB_DOCUMENT02 (AF_PNU);
//CREATE INDEX IDX_STAT ON TB_DOCUMENT07 (UMD);
//CREATE INDEX IDX_STAT ON TB_DOCUMENT08 (PNU);
//
//CREATE INDEX IDX_STAT ON TB_DOCUMENT04 (PNU);
//CREATE INDEX IDX_STAT ON TB_DOCUMENT06 (AF_PNU);
//CREATE INDEX IDX_STAT ON TB_DOCUMENT09 (PNU);
//CREATE INDEX IDX_STAT ON TB_DOCUMENT17 (PNU);
//
//CREATE INDEX IDX_QRY ON TB_DOCUMENT01 (BF_PNU);
//CREATE INDEX IDX_QRY ON TB_DOCUMENT02 (BF_PNU);
//CREATE INDEX IDX_QRY ON TB_DOCUMENT06 (BF_PNU);

