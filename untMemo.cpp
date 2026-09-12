#pragma link "bsPngImageList"
#pragma link "bsSkinCtrls"
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"

#include <errno.h>//220429//44250//MEMORYLEAK//for strerror(errno)

#pragma warn -8004
#pragma warn -8055

const SELDIRHELP = 1000;//SelectDirectory

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMemo *frmMemo;
//---------------------------------------------------------------------------
__fastcall TfrmMemo::TfrmMemo(TComponent* Owner)
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
		//pnlWaitT->Color//
		this->pnlWaitT->Color			= (TColor)RGB(R, G, B);
	}



	// 글자 입력길이 제한
	nTitleMaxLen = 60;
	nMemoMaxLen = 200;
	bMaxLength  = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemo::FormCreate(TObject *Sender)
{
	ADDFILEPATH 	= frmMain->ROOTPATH + "_ADDFILE\\";
	ADDTHUMBPATH 	= frmMain->ROOTPATH + "_ADDTHUMB\\";

	THUMBNAILSIZE	= 76;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemo::FormShow(TObject *Sender)
{
	this->Left = frmMain->Left + frmMain->Width / 2 - this->Width - 20;
	this->Top  = frmMain->Top + frmMain->Height / 2 - this->Height / 2 - 20;

	if (!DirectoryExists(ADDFILEPATH))
		CreateDir(ADDFILEPATH);

	if (!DirectoryExists(ADDTHUMBPATH))
		CreateDir(ADDTHUMBPATH);

	funcLoadButtonImage();

	if(m_bMemoRegist)//Regist
	{
		funcClearForm();
	}
	else//Modify
	{
		funcViewForm();

		//
		funcReadMemoInfoHis(m_asPoiKey);//
		if(m_vMEMOINFOHIS.size() > 1)
			IMGMEMOHIS->Visible = true;
		else
			IMGMEMOHIS->Visible = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemo::funcClearForm()
{
	funcDeleteListThumb();
	funcCreateListThumb();

	m_nVectorCount	= 0;
	m_nVectorIndex 	= -1;

	//=========================================================
	//MemoInfo
	m_vMEMOINFO.clear();
	//MemoVector
	m_vMEMOVECTOR.clear();
	//MemoFile
	m_vMEMOFILE.clear();
	//MemoInfoHis
	m_vMEMOINFOHIS.clear();

	AnsiString asStr 		= "";
	if((int)frmMain->m_vMEMORECT.size() >= 3)//200622
	{
		lblMemoHeader->Caption	= "영역 등록";
		pnlColors->Visible		= true;//201118//
		pnlGagam->Top			= 420;//201118//
		pnlColors->Top			= 450;//201118//
	}
	else
	{
		lblMemoHeader->Caption	= "메모 등록";
		pnlColors->Visible		= false;//201118//
	}

	IMGMEMOSAVE->Visible	= true;
	IMGMEMOMODIFY->Visible	= false;
	IMGMEMODELETE->Visible	= false;
	IMGMEMOHIS->Visible 	= false;

	m_nFileSeq		= 0;
	btnDownload->Visible	= false;//201118//

	chkOpenYN->Checked = true;
	if((int)frmMain->m_vMEMORECT.size() >= 3)
		edtMemoPoi->Text	= "선택영역";
	else if( !m_asSelectLandCd.IsEmpty() )
		edtMemoPoi->Text = frmMain->func_ConvertLandcdToAddress(m_asSelectLandCd);
	else
		edtMemoPoi->Text = "선택좌표";
	edtMemoTitle->Text	= "";
	edtMemoMemo->Text	= "";
	edtGagamX->Text		= "";//201118//
	edtGagamY->Text		= "";//201118//
	asStr	= "(작성자:" + frmMain->m_asCurrentNm + ")";
	pnlMemoBottom2D->Caption	= asStr;
	edtMemoTitle->SetFocus();


	//201109//
	int configindex = frmMain->func_ConfigIndexAlloc(1,"메모", "");
	if(configindex < 0) return;

	int linecolor	= frmMain->m_vCONFIGLP[configindex].linecolor;
	edtRed->Text	= GetRValue(linecolor);
	edtGreen->Text	= GetGValue(linecolor);
	edtBlue->Text	= GetBValue(linecolor);

	pnlColor->Color	= (TColor)RGB( edtRed->Text.ToInt(), edtGreen->Text.ToInt(), edtBlue->Text.ToInt() );
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemo::funcViewForm()
{
	lblWait2->Caption  = "이미지를 다운받고 있습니다.";
	funcSetWaitWindows(true);

	funcDeleteListThumb();
	funcCreateListThumb();

	m_nVectorCount	= 0;
	m_nVectorIndex 	= -1;

	//=========================================================
	//MemoInfo
	m_vMEMOINFO.clear();
	//MemoVector
	m_vMEMOVECTOR.clear();
	//MemoFile
	m_vMEMOFILE.clear();
	//MemoInfoHis
	m_vMEMOINFOHIS.clear();


	AnsiString asStr = "";
	lblMemoHeader->Caption	= "메모 내용";
	IMGMEMOSAVE->Visible	= false;
	IMGMEMOMODIFY->Visible	= true;
	IMGMEMODELETE->Visible	= true;

	m_asPoiKey	= m_asSelectPoiKey;

	if( !m_asPoiKey.IsEmpty() )
	{
		funcReadMemoInfo(m_asPoiKey);
		//200110//funcReadFileVectorLog(m_asPoiKey);
		//funcReadMemoVector(m_asPoiKey);

		//201109//
		if(m_vMEMOINFO[0].FILE_CNT == 0)
		{
			btnDownload->Visible	= false;
		}
		else
		{
			btnDownload->Visible	= true;

			funcReadMemoFile(m_asPoiKey);

			m_nFileSeq		= funcReadMaxSeq(m_asPoiKey);
		}

		if( !strcmp(m_vMEMOINFO[0].OPEN_YN, "Y") )
			chkOpenYN->Checked = true;
		else
			chkOpenYN->Checked = false;
		edtMemoPoi->Text	= m_vMEMOINFO[0].POI_NAME;
		edtMemoTitle->Text	= m_vMEMOINFO[0].TITLE;
		edtMemoMemo->Text	= m_vMEMOINFO[0].MEMO;

		edtGagamX->Text		= m_vMEMOINFO[0].GAGAM_X;//201118//
		edtGagamY->Text		= m_vMEMOINFO[0].GAGAM_Y;//201118//

		//201118//
		if(m_vMEMOINFO[0].DATA_CNT < 3)//메모//
		{
			pnlColors->Visible	= false;//201118//
		}
		else//영역//
		{
			pnlColors->Visible	= true;//201118//
			pnlGagam->Top		= 420;//201118//
			pnlColors->Top		= 450;//201118//
			//201109//
			int linecolor 		= m_vMEMOINFO[0].LINECOLOR;
			edtRed->Text		= GetRValue(linecolor);
			edtGreen->Text		= GetGValue(linecolor);
			edtBlue->Text		= GetBValue(linecolor);
			pnlColor->Color		= (TColor)RGB( edtRed->Text.ToInt(), edtGreen->Text.ToInt(), edtBlue->Text.ToInt() );
		}
		//---

		asStr	= "(작성자:" + frmUserManagement->funcReadUserName(AnsiString((char*)m_vMEMOINFO[0].WRITE_ID)) + ")";
		AnsiString asTemp = (char*)m_vMEMOINFO[0].WRITE_DT;
		if(asTemp.Length() == 14)
			asTemp = asTemp.SubString(1, 4) + "-" + asTemp.SubString(5, 2) + "-" + asTemp.SubString(7, 2) + " " + asTemp.SubString(9, 2) + ":" + asTemp.SubString(11, 2) + ":" + asTemp.SubString(13, 2);
		else
			asTemp = "정보없음";
		asStr	= asStr + "(최종수정일:" + asTemp + ")";
		pnlMemoBottom2D->Caption	= asStr;

		if( !frmFtpControl->FuncFtpConnect(1/*FTP1*/) )//200829
		{
			AnsiString strMsg = "현재 이미지 서버에 연결할 수 없습니다.(Connect)";
			frmMsg->funcMessageDlg("이미지 연결 확인:", strMsg, 3);
			funcSetWaitWindows(false);
			return;
		}

		AnsiString asPathName	= "";
		for(int i = 0; i < (int)m_vMEMOFILE.size(); i++)
		{
			asPathName = funcDownloadFile(i);
			if( !asPathName.IsEmpty() )
			{
				strcpy(m_vMEMOFILE[i].LOCAL_PATH_NAME, asPathName.c_str());
				funcMakeDCThumb(asPathName);
			}
		}

		if(frmMemoViewer->Showing)
		{
			frmMemoViewer->funcViewForm();
		}

		edtMemoMemo->SetFocus();
	}

	funcSetWaitWindows(false);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemo::FormCloseQuery(TObject *Sender, bool &CanClose)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemo::FormClose(TObject *Sender, TCloseAction &Action)
{
	pnlColors->Visible		= true;//201118//
	pnlGagam->Top			= 420;//201118//
	pnlColors->Top			= 450;//201118//

	if(frmMemoViewer->Showing)
		frmMemoViewer->Close();

	if(frmMemoHis->Showing)
		frmMemoHis->Close();

	frmMain->pbControl1DblClick = false;//191227

	m_bMemoRegist 		= false;
	m_asSelectPoiKey 	= "";
	m_asPoiKey       	= "";
	m_nSelectMemoIndex 	= -1;

	funcClearForm();

	//=============================================
	//241205//[레이어] 이미지 표시 설정//
	//=============================================
	frmMain->funcSetImageLayer(frmMain->IMGMEMOPOINT, false, false);
	//=============================================

	//=============================================
	//241205//[레이어] 이미지 표시 설정//
	//=============================================
	frmMain->funcSetImageLayer(frmMain->IMGMEMOPOLY, false, false);
	//=============================================

	//
	frmMain->_CURRENT_COMWORKMODE	= "";
	frmMain->m_vMEMORECT.clear();
	frmMain->m_eManipulationMode    	= frmMain->Panning;
	frmMain->m_bControlFlags = false;
	if(frmMain->PBCONTROL1->Visible == true) frmMain->PBCONTROL1->Invalidate();
	frmMain->PBCONTROL1->Visible = false;
	frmMain->ICONMEMOPOINT->Visible = false;
	frmMain->ICONMEMOPOLY->Visible = false;
	frmMain->MEMOPOINTHELP->Visible = false;
	frmMain->MEMOPOLYHELP->Visible = false;

	if (DirectoryExists(ADDFILEPATH))//_ADDFILE 하위 파일들 삭제하기
		eFunc->funcDeleteDir(true, ADDFILEPATH);
	if (DirectoryExists(ADDTHUMBPATH))//_ADDTHUMB 하위 파일들 삭제하기
		eFunc->funcDeleteDir(true, ADDTHUMBPATH);

	funcDeleteButtonImage();

	funcFreeImage();
	funcImageViewClear();

	funcDeleteListThumb();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemo::funcSetWaitWindows(bool bSetValue)
{
	palWait->Left = (this->Width/2) - (palWait->Width/2);
	//191126//palWait->Top  = (palClient->Height - bsSkinStatusBar1->Height)/2 - (palWait->Height/2);
	palWait->Top  = (this->Height/2) - (palWait->Height/2);//191126//

	if (this->palWait->Visible == !bSetValue)
	{
		palWait->Visible = bSetValue;

		if (bSetValue)		Screen->Cursor     = crHourGlass;
		else            	Screen->Cursor     = crDefault;

		if(!bSetValue)		lblWait2->Caption  = "선택 작업을 적용중입니다.";
	}

	Application->ProcessMessages();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemo::funcLoadButtonImage()
{
	AnsiString filename = "";
	TPngImage *imgPng;

	//Button Image
	for(int i = 0; i < 2; i++)
	{
		imgPng = new TPngImage();
		filename = frmMain->IMAGEMEMOPATH + "btnAddFile" + IntToStr(i+1) + ".png";
		imgPng->LoadFromFile(filename);
		BITMAP_BTN_ADDFILE[i] = new Graphics::TBitmap();
		BITMAP_BTN_ADDFILE[i]->Assign(imgPng);
		delete imgPng;
		imgPng = NULL;
		//
		imgPng = new TPngImage();
		filename = frmMain->IMAGEMEMOPATH + "btnRegist" + IntToStr(i+1) + ".png";
		imgPng->LoadFromFile(filename);
		BITMAP_BTN_MEMOSAVE[i] = new Graphics::TBitmap();
		BITMAP_BTN_MEMOSAVE[i]->Assign(imgPng);
		delete imgPng;
		imgPng = NULL;
		//
		imgPng = new TPngImage();
		filename = frmMain->IMAGEMEMOPATH + "btnModify" + IntToStr(i+1) + ".png";
		imgPng->LoadFromFile(filename);
		BITMAP_BTN_MEMOMODIFY[i] = new Graphics::TBitmap();
		BITMAP_BTN_MEMOMODIFY[i]->Assign(imgPng);
		delete imgPng;
		imgPng = NULL;
		//
		imgPng = new TPngImage();
		filename = frmMain->IMAGEMEMOPATH + "btnDelete" + IntToStr(i+1) + ".png";
		imgPng->LoadFromFile(filename);
		BITMAP_BTN_MEMODELETE[i] = new Graphics::TBitmap();
		BITMAP_BTN_MEMODELETE[i]->Assign(imgPng);
		delete imgPng;
		imgPng = NULL;
		//
		imgPng = new TPngImage();
		filename = frmMain->IMAGEMEMOPATH + "memoClose" + IntToStr(i+1) + ".png";
		imgPng->LoadFromFile(filename);
		BITMAP_BTN_MEMOCLOSE[i] = new Graphics::TBitmap();
		BITMAP_BTN_MEMOCLOSE[i]->Assign(imgPng);
		delete imgPng;
		imgPng = NULL;
	}

	//
	imgPng = new TPngImage();
	filename = frmMain->IMAGEMEMOPATH + "btnMemoHis.png";
	imgPng->LoadFromFile(filename);
	BITMAP_BTN_MEMOHIS = new Graphics::TBitmap();
	BITMAP_BTN_MEMOHIS->Assign(imgPng);
	delete imgPng;
	imgPng = NULL;
	//
	imgPng = new TPngImage();
	filename = frmMain->IMAGEMEMOPATH + "delete.png";
	imgPng->LoadFromFile(filename);
	BITMAP_BTN_DELETE = new Graphics::TBitmap();
	BITMAP_BTN_DELETE->Assign(imgPng);
	delete imgPng;
	imgPng = NULL;
	//
	IMGADDFILE->Picture->Bitmap->Assign(BITMAP_BTN_ADDFILE[0]);
	IMGMEMOSAVE->Picture->Bitmap->Assign(BITMAP_BTN_MEMOSAVE[0]);
	IMGMEMOMODIFY->Picture->Bitmap->Assign(BITMAP_BTN_MEMOMODIFY[0]);
	IMGMEMODELETE->Picture->Bitmap->Assign(BITMAP_BTN_MEMODELETE[0]);
	IMGEXIT->Picture->Bitmap->Assign(BITMAP_BTN_MEMOCLOSE[0]);
	IMGMEMOHIS->Picture->Bitmap->Assign(BITMAP_BTN_MEMOHIS);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemo::funcDeleteButtonImage()
{
	for(int i = 0; i < 2; i++)
	{
		delete BITMAP_BTN_ADDFILE[i];
		BITMAP_BTN_ADDFILE[i] = NULL;
		delete BITMAP_BTN_MEMOSAVE[i];
		BITMAP_BTN_MEMOSAVE[i] = NULL;
		delete BITMAP_BTN_MEMOMODIFY[i];
		BITMAP_BTN_MEMOMODIFY[i] = NULL;
		delete BITMAP_BTN_MEMODELETE[i];
		BITMAP_BTN_MEMODELETE[i] = NULL;
		delete BITMAP_BTN_MEMOCLOSE[i];
		BITMAP_BTN_MEMOCLOSE[i] = NULL;
	}

	delete BITMAP_BTN_DELETE;
	BITMAP_BTN_DELETE = NULL;
}
//---------------------------------------------------------------------------


__int64 __fastcall TfrmMemo::funcGetLocalFileSize(AnsiString _asPathName)
{
	DWORD   dwLow;
	DWORD   dwHigh  = 0;
	__int64     nFileSize = 0;
	HANDLE  hFile   = ::CreateFile( _asPathName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL );

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

void __fastcall TfrmMemo::funcRefreshForm()
{
//	if(m_bMemoNew)//메모뷰상태에서 신규등록//
//	{
//		AnsiString strMsg = "작성하던 메모내용을 저장하고 등록화면을 띄울까요?";
//		frmMsg->funcMessageDlg("등록화면이동 확인:", strMsg, 1);
//
//		if(frmMsg->m_bClick)
//		{
//			if(m_bMemoRegist)
//				IMGMEMOSAVEClick(IMGMEMOSAVE);
//			else
//				IMGMEMOMODIFYClick(IMGMEMOMODIFY);
//			m_bMemoRegist = true;
//			funcClearForm();
//		}
//	}
//	else if( !m_bMemoSaved )//아직 저장전//
//	{
//		if(m_bMemoRegist)//신규등록일때 어떤 데이터를 입력해도//
//		{
//			if(edtMemoTitle->Text.Trim().IsEmpty() && edtMemoMemo->Text.Trim().IsEmpty() && m_nThumbCount == 0)
//			{
//				Close();
//				return;
//            }
//		}
//		else//뷰상태일때 기존 db 데이터와 비교//
//		{
//			if( funcCheckSameData() )
//			{
//				Close();
//				return;
//            }
//		}
//
//		AnsiString strMsg = "작성하던 메모내용을 취소하시겠습니까?";
//		frmMsg->funcMessageDlg("저장 취소 확인:", strMsg, 1);
//
//		if(frmMsg->m_bClick)//취소//
//		{
//			Close();
//		}
//	}
//	else
//	{
//		Close();
//	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemo::IMGEXITClick(TObject *Sender)
{
	if(m_bMemoChange)//메모상태에서 메모//
	{
		if( !frmMemo->funcCheckSameData() )
		{
			AnsiString strMsg = "작성하던 메모내용을 취소하시겠습니까?";
			frmMsg->funcMessageDlg("저장 취소 확인:", strMsg, 1);

			if(frmMsg->m_bClick)//취소//
			{
				if(m_bMemoRegist)
				{
					funcClearForm();
				}
				else
				{
					frmMain->funcSetStatusBarMsg(2, frmMain->m_asTempMemoPoiKey);
					m_asSelectPoiKey 							= frmMain->m_asTempMemoPoiKey;
					funcViewForm();
				}
			}
		}
		else
		{
			frmMain->funcSetStatusBarMsg(2, frmMain->m_asTempMemoPoiKey);
			m_asSelectPoiKey 							= frmMain->m_asTempMemoPoiKey;
			funcViewForm();
		}
		m_bMemoChange = false;
	}
	else
	{
		if(m_bMemoRegist)
		{
			AnsiString strMsg = "작성하던 메모내용을 취소하시겠습니까?";
			frmMsg->funcMessageDlg("저장 취소 확인:", strMsg, 1);
			if(frmMsg->m_bClick)//취소//
			{
				Close();
            }
		}
		else
		{
			if( !frmMemo->funcCheckSameData() )
			{
				AnsiString strMsg = "작성하던 메모내용을 취소하시겠습니까?";
				frmMsg->funcMessageDlg("저장 취소 확인:", strMsg, 1);

				if(frmMsg->m_bClick)//취소//
				{
					Close();
				}
			}
			else
				Close();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemo::IMGMEMOSAVEMouseEnter(TObject *Sender)
{
	IMGMEMOSAVE->Picture->Bitmap->Handle	= NULL;
	IMGMEMOSAVE->Picture					= NULL;
	IMGMEMOSAVE->Picture->Bitmap->Assign(BITMAP_BTN_MEMOSAVE[1]);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemo::IMGMEMOSAVEMouseLeave(TObject *Sender)
{
	IMGMEMOSAVE->Picture->Bitmap->Handle	= NULL;
	IMGMEMOSAVE->Picture					= NULL;
	IMGMEMOSAVE->Picture->Bitmap->Assign(BITMAP_BTN_MEMOSAVE[0]);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemo::IMGMEMOSAVEClick(TObject *Sender)
{
//DB저장//
	if(edtMemoTitle->Text.Trim().IsEmpty())
	{
		frmMsg->funcMessageDlg("필수입력사항:", "제목을 입력해주세요.", 3);
		return;
	}

	if(edtMemoMemo->Text.Trim().IsEmpty() && pnlThumbList->Count == 0)
	{
		frmMsg->funcMessageDlg("필수입력사항:", "메모를 입력하거나 혹은 이미지를 첨부해주세요.", 3);
		return;
	}

	funcSetWaitWindows(true);

	AnsiString 	asStr	= "";
	int			nDBType = DF_NEW_RECORD;
	double		X = 0.0;
	double		Y = 0.0;
	bool		bReturnFile;
	bool		bReturnVector;
	bool		bReturnInfo;

	m_nVectorCount	= 1;

	if( !m_bMemoRegist )
		nDBType = DF_UPDATE_RECORD;

	//=========================================================
	//Create PoiKey
	m_asPoiKey	= Now().FormatString("yyyymmddhhmmsszzz0000");

	//=========================================================
	//MemoVector
	if((int)frmMain->m_vMEMORECT.size() >= 3)//선택 영역이 있는지 확인한다//
	{
		m_asTempPoiKey = m_asPoiKey;
		funcWriteFileVectorLog();//200109

		m_nVectorCount = (int)frmMain->m_vMEMORECT.size();
		X = frmMain->m_vMEMORECT[frmMain->m_vMEMORECT.size()-1].labelx;
		Y = frmMain->m_vMEMORECT[frmMain->m_vMEMORECT.size()-1].labely;
	}
	else if( !m_asSelectLandCd.IsEmpty() )
	{
		GPoint gPoint;
		gPoint = m_gpMemoPoint;//frmMain->func_DeviceToWorld(frmMain->clickPoint);//지번이 선택되었더라도 pointing한 좌표를 저장//

		m_asTempPoiKey = m_asPoiKey;
		funcWriteFileVectorLog();//200109
		X = gPoint.x;
		Y = gPoint.y;
	}
	//=========================================================
	//MemoFile
	AnsiString	asPathName	= "";
	for(int i = 0; i < (int)m_vMEMOFILE.size(); i++)
	{
		strcpy(m_vMEMOFILE[i].POI_KEY, m_asPoiKey.c_str());
		asPathName 	= funcUploadFile(i);
		if( !asPathName.IsEmpty() )
		{
			strcpy(m_vMEMOFILE[i].REMOTE_PATH_NAME, asPathName.c_str());
			funcWriteMemoFile(nDBType, i);
		}
	}
	//=========================================================
	//MemoInfo
	memset(&tempMEMOINFO, 0x00, sizeof(MEMOINFO_STRUCT));
	strcpy(tempMEMOINFO.POI_KEY, m_asPoiKey.c_str());
	asStr	= edtMemoPoi->Text.Trim();
	strcpy(tempMEMOINFO.POI_NAME, asStr.c_str());
	asStr	= edtMemoTitle->Text.Trim();
	strcpy(tempMEMOINFO.TITLE, asStr.c_str());
	asStr	= edtMemoMemo->Text.Trim();
	strcpy(tempMEMOINFO.MEMO, asStr.c_str());
	strcpy(tempMEMOINFO.BATCH_YN, "N");//#BATCH_YN#
	if(chkOpenYN->Checked)//#OPEN_YN#
		strcpy(tempMEMOINFO.OPEN_YN, "Y");
	else
		strcpy(tempMEMOINFO.OPEN_YN, "N");
	strcpy(tempMEMOINFO.WRITE_ID, frmMain->m_asCurrentId.c_str());
	strcpy(tempMEMOINFO.WRITE_DT, "");
	tempMEMOINFO.FILE_CNT	= m_nThumbCount;
	tempMEMOINFO.DATA_CNT   = m_nVectorCount;
	tempMEMOINFO.X			= X;
	tempMEMOINFO.Y   		= Y;

	//201109//
	tempMEMOINFO.LINECOLOR	= pnlColor->Color;
	asStr	= edtGagamX->Text.Trim();
	strcpy(tempMEMOINFO.GAGAM_X, asStr.c_str());
	asStr	= edtGagamY->Text.Trim();
	strcpy(tempMEMOINFO.GAGAM_Y, asStr.c_str());
	//---

	m_vMEMOINFO.push_back(tempMEMOINFO);
	//200113//SAVE할때는 HISTORY저장필요없음//funcWriteMemoInfoHistory((int)m_vMEMOINFO.size()-1);//#MOMOHISTORY#
	bReturnInfo = funcWriteMemoInfo(nDBType, (int)m_vMEMOINFO.size()-1);

//	//=========================================================
//	if(tempMEMOINFO.FILE_CNT > 0)
//	{
//		frmSql->m_vALLPHOTOINFO.push_back(tempMEMOINFO);
//	}
//	asStr = (char*)tempMEMOINFO.MEMO;
//	if( !asStr.IsEmpty() )//메모//
//	{
//		frmSql->m_vALLMEMOINFO.push_back(tempMEMOINFO);
//	}
//	//=========================================================

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
			funcReadFileVectorLog(frmSql->m_vALLMEMOINFO[i].POI_KEY);
			//200109//frmSql->funcReadDocumentMemoVector(frmSql->m_vALLMEMOINFO[i].POI_KEY);
		}
	}
	//=========================================================

	funcSetWaitWindows(false);

	if(bReturnInfo)
	{
		if( m_bMemoRegist )
			frmMsg->funcMessageDlg("메모저장 알림:", "신규 메모가 등록되었습니다.", 3);
		else
			frmMsg->funcMessageDlg("메모수정 알림:", "수정된 사항이 저장되었습니다.", 3);
	}
	else
	{
		frmMsg->funcMessageDlg("저장오류 알림:", "메모를 저장하는데 문제가 발생하였습니다. 개발사에 문의해주세요.", 3);
	}

	if(bReturnInfo && frmMain->INIINFO.B_MEMO == false)
		frmMain->INIINFO.B_MEMO = true;
	if(m_nVectorCount >= 3 && frmMain->INIINFO.B_POLY == false)
		frmMain->INIINFO.B_POLY = true;
//	if(m_nThumbCount && frmMain->INIINFO.B_PHOTO == false)
//		frmMain->INIINFO.B_PHOTO = true;

	frmMain->func_DrawImagePaint();

	Close();//메모보기 > 신규등록이 아니라면 종료//
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemo::IMGMEMOMODIFYMouseEnter(TObject *Sender)
{
	IMGMEMOMODIFY->Picture->Bitmap->Handle	= NULL;
	IMGMEMOMODIFY->Picture					= NULL;
	IMGMEMOMODIFY->Picture->Bitmap->Assign(BITMAP_BTN_MEMOMODIFY[1]);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemo::IMGMEMOMODIFYMouseLeave(TObject *Sender)
{
	IMGMEMOMODIFY->Picture->Bitmap->Handle	= NULL;
	IMGMEMOMODIFY->Picture					= NULL;
	IMGMEMOMODIFY->Picture->Bitmap->Assign(BITMAP_BTN_MEMOMODIFY[0]);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemo::IMGMEMOMODIFYClick(TObject *Sender)
{
//DB저장//
	if(edtMemoTitle->Text.Trim().IsEmpty())
	{
		frmMsg->funcMessageDlg("필수입력사항:", "제목을 입력해주세요.", 3);
		return;
	}

	if(edtMemoMemo->Text.Trim().IsEmpty() && pnlThumbList->Count == 0)
	{
		frmMsg->funcMessageDlg("필수입력사항:", "메모를 입력하거나 혹은 이미지를 첨부해주세요.", 3);
		return;
	}

	funcSetWaitWindows(true);

	AnsiString 	asStr	= "";
	int 		nIndex 	= 0;
	int			nDBType = DF_UPDATE_RECORD;
	double		X = 0.0;
	double		Y = 0.0;
	bool		bReturnFile;
	bool		bReturnVector;
	bool		bReturnInfo;

	m_nVectorCount	= 1;

	//update일때 vector는 수정하지 않는다//
//	//=========================================================
//	//MemoVector
//	if( !m_asSelectLandCd.IsEmpty() )
//	{
//		int selectIndex = frmMain->func_readKindofDocSpatialData(m_asSelectLandCd);
//		GPoint gPoint;
//		gPoint.x = frmMain->m_vKINFOGDOCSPATIALDATA[selectIndex].x;
//		gPoint.y = frmMain->m_vKINFOGDOCSPATIALDATA[selectIndex].y;
//
//		for(int i = 0; i < m_nVectorCount; i++)
//		{
//			memset(&tempMEMOVECTOR, 0x00, sizeof(MEMOVECTOR_STRUCT));
//			strcpy(tempMEMOVECTOR.POI_KEY, m_asPoiKey.c_str());
//			tempMEMOVECTOR.SEQ	= i + 1;
//			tempMEMOVECTOR.X	= gPoint.x;
//			tempMEMOVECTOR.Y	= gPoint.y ;
//			m_vMEMOVECTOR.push_back(tempMEMOVECTOR);
//			nIndex = (int)m_vMEMOVECTOR.size()-1;
//			funcWriteMemoVector(nDBType, nIndex);
//		}
//		//중심점 구하는 알고리즘//[TODO]
//		//funcWriteMemoInfo(DF_UPDATE_RECORD, ---);
//		X = gPoint.x;
//		Y = gPoint.y;
//	}
	//=========================================================
	//MemoFile
	AnsiString	asPathName	= "";
	for(int i = 0; i < (int)m_vMEMOFILE.size(); i++)
	{
		if(m_vMEMOFILE[i].B_NEW)
			nDBType = DF_NEW_RECORD;
		else
			nDBType = DF_UPDATE_RECORD;

		asPathName 	= (char*)m_vMEMOFILE[i].LOCAL_PATH_NAME;//Local File Path//이 함수 반환값을 다시 여기에 넣는다.
		if( asPathName.Pos("/") > 0)//remote file
			continue;

		asPathName 	= funcUploadFile(i);
		if( !asPathName.IsEmpty() )
		{
			strcpy(m_vMEMOFILE[i].REMOTE_PATH_NAME, asPathName.c_str());
			funcWriteMemoFile(nDBType, i);
		}
	}
	//=========================================================
	//MemoInfo
	nDBType = DF_UPDATE_RECORD;
	asStr	= edtMemoPoi->Text.Trim();
	strcpy(m_vMEMOINFO[0].POI_NAME, asStr.c_str());
	asStr	= edtMemoTitle->Text.Trim();
	strcpy(m_vMEMOINFO[0].TITLE, asStr.c_str());
	asStr	= edtMemoMemo->Text.Trim();
	strcpy(m_vMEMOINFO[0].MEMO, asStr.c_str());
	strcpy(m_vMEMOINFO[0].BATCH_YN, "N");//#BATCH_YN#
	if(chkOpenYN->Checked)//#OPEN_YN#
		strcpy(m_vMEMOINFO[0].OPEN_YN, "Y");
	else
		strcpy(m_vMEMOINFO[0].OPEN_YN, "N");
	strcpy(m_vMEMOINFO[0].WRITE_ID, frmMain->m_asCurrentId.c_str());
	strcpy(m_vMEMOINFO[0].WRITE_DT, "");
	m_vMEMOINFO[0].FILE_CNT		= m_nThumbCount;

	//201109//
	m_vMEMOINFO[0].LINECOLOR	= pnlColor->Color;
	asStr	= edtGagamX->Text.Trim();
	strcpy(m_vMEMOINFO[0].GAGAM_X, asStr.c_str());
	asStr	= edtGagamY->Text.Trim();
	strcpy(m_vMEMOINFO[0].GAGAM_Y, asStr.c_str());
	//---

	funcWriteMemoInfoHistory(0);//#MOMOHISTORY#
	bReturnInfo = funcWriteMemoInfo(nDBType, 0);

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
			funcReadFileVectorLog(frmSql->m_vALLMEMOINFO[i].POI_KEY);
			//200109//frmSql->funcReadDocumentMemoVector(frmSql->m_vALLMEMOINFO[i].POI_KEY);
		}
	}
	//=========================================================

	funcSetWaitWindows(false);

	if(bReturnInfo)
	{
		if( m_bMemoRegist )
			frmMsg->funcMessageDlg("메모저장 알림:", "신규 메모가 등록되었습니다.", 3);
		else
			frmMsg->funcMessageDlg("메모수정 알림:", "수정된 사항이 저장되었습니다.", 3);
	}
	else
	{
		frmMsg->funcMessageDlg("저장오류 알림:", "메모를 저장하는데 문제가 발생하였습니다. 개발사에 문의해주세요.", 3);
	}

	frmMain->func_DrawImagePaint();

	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemo::IMGMEMODELETEMouseEnter(TObject *Sender)
{
	IMGMEMODELETE->Picture->Bitmap->Handle	= NULL;
	IMGMEMODELETE->Picture					= NULL;
	IMGMEMODELETE->Picture->Bitmap->Assign(BITMAP_BTN_MEMODELETE[1]);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemo::IMGMEMODELETEMouseLeave(TObject *Sender)
{
	IMGMEMODELETE->Picture->Bitmap->Handle	= NULL;
	IMGMEMODELETE->Picture					= NULL;
	IMGMEMODELETE->Picture->Bitmap->Assign(BITMAP_BTN_MEMODELETE[0]);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemo::IMGMEMODELETEClick(TObject *Sender)
{
	//VECTOR
	funcWriteMemoVector(DF_DELETE_RECORD, 0);

	//FILE
	for(int i = 0; i < (int)m_vMEMOFILE.size(); i++)
		funcWriteMemoFile(DF_DELETE_RECORD, i);

	//INFO
	//200113//DELETE는 HISTORY INSERT 필요있다//
	funcWriteMemoInfoHistory(0);//#MOMOHISTORY#
	bool bReturnInfo = funcWriteMemoInfo(DF_DELETE_RECORD, 0);

	if(bReturnInfo)
	{
		frmMsg->funcMessageDlg("메모삭제 알림:", "메모가 삭제되었습니다.", 3);
	}
	else
	{
		frmMsg->funcMessageDlg("저장오류 알림:", "메모를 저장하는데 문제가 발생하였습니다. 개발사에 문의해주세요.", 3);
	}

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
			funcReadFileVectorLog(frmSql->m_vALLMEMOINFO[i].POI_KEY);
			//200109//frmSql->funcReadDocumentMemoVector(frmSql->m_vALLMEMOINFO[i].POI_KEY);
		}
	}

	frmMain->func_DrawImagePaint();

	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemo::IMGADDFILEMouseEnter(TObject *Sender)
{
	IMGADDFILE->Picture->Bitmap->Handle	= NULL;
	IMGADDFILE->Picture					= NULL;
	IMGADDFILE->Picture->Bitmap->Assign(BITMAP_BTN_ADDFILE[1]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemo::IMGADDFILEMouseLeave(TObject *Sender)
{
	IMGADDFILE->Picture->Bitmap->Handle	= NULL;
	IMGADDFILE->Picture					= NULL;
	IMGADDFILE->Picture->Bitmap->Assign(BITMAP_BTN_ADDFILE[0]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemo::IMGADDFILEClick(TObject *Sender)
{
//	if (OpenPictureDialog1->Execute(Handle)) {
//		AnsiString asTgtPath	= "";
//		AnsiString asFileName = OpenPictureDialog1->FileName;
//
//		if(FileExists(asFileName))
//		{
//			AnsiString asExt 		= ExtractFileExt(asFileName);
//			AnsiString asSeq		= "";
//			asSeq.sprintf("%03d", m_nFileSeq+1);
//			AnsiString asStr		= ExtractFileName(asFileName);
//			AnsiString asTgtPath 	= ADDFILEPATH + asStr.SubString(1, asStr.Length() - asExt.Length()) + "_" + asSeq + asExt;
//			CopyFile(asFileName.c_str(), asTgtPath.c_str(), false);
//			funcMakeDCThumb(asTgtPath);
//			m_nFileSeq++;
//			if(frmMemoViewer->Showing)
//				frmMemoViewer->lblCount->Caption = "(" + IntToStr(m_nThumbIndex+1) + "/" + IntToStr(m_nThumbCount) + ")";
//		}
//	}

	//250910//[2025_08_REQ]다수 파일 일괄 업로드//
	if (OpenPictureDialog1->Execute(Handle))
	{
		for (int i = 0; i < OpenPictureDialog1->Files->Count; ++i)
		{
			AnsiString asTgtPath	= "";
			AnsiString asFileName = OpenPictureDialog1->Files->Strings[i];

			if(FileExists(asFileName))
			{
				AnsiString asExt 		= ExtractFileExt(asFileName);
				AnsiString asSeq		= "";
				asSeq.sprintf("%03d", m_nFileSeq+1);
				AnsiString asStr		= ExtractFileName(asFileName);
				AnsiString asTgtPath 	= ADDFILEPATH + asStr.SubString(1, asStr.Length() - asExt.Length()) + "_" + asSeq + asExt;
				CopyFile(asFileName.c_str(), asTgtPath.c_str(), false);
				funcMakeDCThumb(asTgtPath);
				m_nFileSeq++;
				if(frmMemoViewer->Showing)
					frmMemoViewer->lblCount->Caption = "(" + IntToStr(m_nThumbIndex+1) + "/" + IntToStr(m_nThumbCount) + ")";
			}
		}
	}
}
//---------------------------------------------------------------------------


//======================================================================
//
// 글자 길이 입력 제한//
//
//======================================================================
void __fastcall TfrmMemo::edtMaxChange(TObject *Sender)
{
	AnsiString asSenderName = dynamic_cast<TComponent*>(Sender)->Name;

	if(bMaxLength == false)
	{
		TEdit *tcmpEdt;
		tcmpEdt = (TEdit*)this->FindComponent(asSenderName.c_str());

		AnsiString asTxt = tcmpEdt->Text;
		int nLength = asTxt.Length();

		if(nLength % 2)	nLength += 1;

		if (asSenderName == "edtMemoTitle")
		{
			lblTitleLen->Caption = "(" + IntToStr(nLength) + "/60)";
			if(nLength > nTitleMaxLen)//MaxLength : 60
			{
				if( (asTxt.c_str()[nTitleMaxLen-1] & 0x80) == 0x80 ) {// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
					nLength = nTitleMaxLen - 2; // 한글문자 이전 바이트로 넘김
					tcmpEdt->Text = asTxt.SubString(1, nLength);
				}
				else
				{
					nLength = nTitleMaxLen - 1;
					tcmpEdt->Text = asTxt.SubString(1, nLength);
				}
				frmMsg->funcMessageDlg("입력길이 제한 :", "최대 입력길이를 확인해주세요.", 3);
				bMaxLength = true;
			}
		}
		else if (asSenderName == "edtMemoMemo")
		{
			lblMemoLen->Caption = "(" + IntToStr(nLength) + "/200)";
			if(nLength > nMemoMaxLen)//MaxLength : 200
			{
				if( (asTxt.c_str()[nMemoMaxLen-1] & 0x80) == 0x80 ) {// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
					nLength = nMemoMaxLen - 2; // 한글문자 이전 바이트로 넘김
					tcmpEdt->Text = asTxt.SubString(1, nLength);
				}
				else
				{
					nLength = nMemoMaxLen - 1;
					tcmpEdt->Text = asTxt.SubString(1, nLength);
				}
				frmMsg->funcMessageDlg("입력길이 제한 :", "최대 입력길이를 확인해주세요.", 3);
				bMaxLength = true;
			}
		}
	}
	else//delete text using VK_DELETE key
	{
		TEdit *tcmpEdt;
		tcmpEdt = (TEdit*)this->FindComponent(asSenderName.c_str());
		AnsiString asTxt = tcmpEdt->Text;
		int nLength = asTxt.Length();

		if(nLength == 0)
			bMaxLength = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemo::edtKeyPress(TObject *Sender, wchar_t &Key)
{
	if( bMaxLength )
	{
		if(Key != 8 && Key != VK_DELETE && Key != VK_LEFT && Key != VK_RIGHT)
			Key = NULL;
		else
			bMaxLength = false;
	}

	if(Key == VK_RETURN)
	{
		if(Sender == edtMemoTitle)
			edtMemoMemo->SetFocus();
		else if(Sender == edtGagamX)//201118//
			edtGagamY->SetFocus();
//메모에는 개행이 있어서///
//		else if(Sender == edtMemoMemo)
//			IMGADDFILEClick(IMGADDFILE);
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmMemo::edtEnter(TObject *Sender)
{
	bMaxLength = false;

	unsigned long Conversion, Sentence;
	HIMC Mode = ImmGetContext(Application->Handle);
	ImmGetConversionStatus(Mode, &Conversion, &Sentence);
	if (Conversion == IME_CMODE_HANGEUL){;}// 현재모드가 한글이면 패스
	else{                                  // 현재모드가 한글이 아니면 한/영키 누른 효과를준다.
		ImmSetConversionStatus(Mode, IME_CMODE_HANGEUL, IME_CMODE_HANGEUL);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemo::edtExit(TObject *Sender)
{
	bMaxLength = false;
}
//---------------------------------------------------------------------------


















//***************************************************************************
//
// 검색결과 문서와 같은 DOC_KIND 문서가 있는 경우,
// 해당 문서의 THUMBNAIL을 보여주는 기능 -  동적 생성
//
//***************************************************************************
void __fastcall TfrmMemo::funcCreateListThumb()
{
	//btnCreate4
	if( pnlThumbList == NULL)
		pnlThumbList  = new TList();
	if( imgThumbList == NULL)
		imgThumbList  = new TList();
	if( chkSelectList == NULL)//200829//
		chkSelectList  = new TList();
	if( imgDeleteList == NULL)
		imgDeleteList  = new TList();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemo::funcDeleteListThumb()
{
	//btnCreate4
	if(pnlThumbList != NULL)
	{
		for(int i = 0; i < pnlThumbList->Count; i++)
		{
			TPanel *pnlDC = (TPanel *)pnlThumbList->Items[i];
			if(pnlDC != NULL)
			{
				TImage *imgDocDC 		= (TImage *)imgThumbList->Items[i];
				if(imgDocDC != NULL)
				{
					imgThumbList->Items[i] = NULL;
					delete imgDocDC;
				}

				//200829//
				TCheckBox *chkSelectDC 		= (TCheckBox *)chkSelectList->Items[i];
				if(chkSelectDC != NULL)
				{
					chkSelectList->Items[i] = NULL;
					delete chkSelectDC;
				}

				TImage *imgDocDC2 		= (TImage *)imgDeleteList->Items[i];
				if(imgDocDC2 != NULL)
				{
					imgDeleteList->Items[i] = NULL;
					delete imgDocDC2;
				}
				pnlThumbList->Items[i] = NULL;
				delete pnlDC;
			}
		}

		delete pnlThumbList;
		pnlThumbList = NULL;
		delete imgThumbList;
		imgThumbList = NULL;
		delete chkSelectList;//200829//
		chkSelectList = NULL;//200829//
		delete imgDeleteList;
		imgDeleteList = NULL;
	}

	m_nThumbCount	= 0;
	m_nThumbIndex 	= -1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemo::funcMakeDCThumb(AnsiString _asFileName)
{
	AnsiString 	asStr				= "";
	AnsiString 	asLocalPathName 	= _asFileName;
	AnsiString 	asThumbFile 		= _asFileName;
	int			nFileSize			= 0;

	asThumbFile = funcLoadImageThumb(_asFileName);

	if(asThumbFile.IsEmpty())
		return;

	if(m_nThumbCount / 3 < 2)
	{
		ScrollBox1->VertScrollBar->Visible = false;
		//pnlMemoFileD2->Height	= 156;
	}
	else
	{
		ScrollBox1->VertScrollBar->Visible = true;
		//pnlMemoFileD2->Height	= 76 + 80 * (m_nThumbCount / 3);
    }
	//---
	TPanel *pnlDC 			= new TPanel(this);
	TImage *imgThumbDC 		= new TImage(pnlDC);
	TCheckBox *chkSelectDC	= new TCheckBox(pnlDC);//200829//
	TImage *imgDeleteDC		= new TImage(pnlDC);

	imgThumbDC->Width		= THUMBNAILSIZE;
	imgThumbDC->Height		= THUMBNAILSIZE;
	imgThumbDC->Picture->LoadFromFile(asThumbFile);
	//---

	//---
	pnlDC->Parent 			= ScrollBox1;//pnlMemoFileD2;
	//pnlDC->Align			= alLeft;
	pnlDC->Tag 				= m_nThumbCount;
	pnlDC->Hint				= asLocalPathName;//LOCAL 이미지경로//_ADDFILE//
//	pnlDC->BevelKind    	= Controls::bvNone;
	pnlDC->BevelKind		= bkFlat;
//	pnlDC->BevelEdges   	>> beLeft;
//	pnlDC->BevelEdges   	>> beTop;
//	pnlDC->BevelEdges   	>> beRight;
//	pnlDC->BevelEdges   	<< beBottom;
	pnlDC->BevelOuter 		= Controls::bvNone;
//	pnlDC->Color			= clWhite;
	pnlDC->SetBounds((m_nThumbCount % 3) * (THUMBNAILSIZE + 4), (m_nThumbCount / 3) * (THUMBNAILSIZE + 4), THUMBNAILSIZE+2, THUMBNAILSIZE+2);
	pnlDC->ParentFont		= true;

	//---
	imgThumbDC->Parent 		= pnlDC;
	imgThumbDC->Tag         = m_nThumbCount;
	if(m_nThumbCount >= (int)m_vMEMOFILE.size())
		imgThumbDC->Hint 	= 0;//추가된 파일//아직 DB, FTP 적용전//
	else
		imgThumbDC->Hint 	= 1;//DB, FTP 적용된 파일//
//	imgThumbDC->Hint        = asLocalPathName;//REMOTE THUMBNAIL 이미지경로//_THUMB//
	imgThumbDC->SetBounds(0, 0, THUMBNAILSIZE, THUMBNAILSIZE);
	imgThumbDC->OnClick 	= imgThumbDC_onClick;

	//200829//
	chkSelectDC->Parent 	= pnlDC;
	chkSelectDC->Tag 		= m_nThumbCount;
	chkSelectDC->SetBounds(0, 0, 16, 16);
	chkSelectDC->Checked	= false;
	//chkSelectDC->OnClick 	= chkSelectDC_onClick;

	imgDeleteDC->Parent 	= pnlDC;
	imgDeleteDC->Tag 		= m_nThumbCount;
	nFileSize               = funcGetLocalFileSize(asLocalPathName);//LOCAL 이미지 파일크기//
	imgDeleteDC->Hint 		= nFileSize;
	imgDeleteDC->SetBounds(THUMBNAILSIZE - BITMAP_BTN_DELETE->Width, 0, BITMAP_BTN_DELETE->Width, BITMAP_BTN_DELETE->Height);
	imgDeleteDC->Picture->Bitmap->Assign(BITMAP_BTN_DELETE);
	imgDeleteDC->OnClick 	= imgDeleteDC_onClick;

	imgDeleteList->Add(imgDeleteDC);
	chkSelectList->Add(chkSelectDC);//200829
	imgThumbList->Add(imgThumbDC);
	pnlThumbList->Add(pnlDC);
	m_nThumbCount++;

	//==============================================================
	//MemoFile vector.push_back
	if( m_bMemoRegist || (m_bMemoRegist == false && m_nThumbCount > (int)m_vMEMOFILE.size()) )
	{
		memset(&tempMEMOFILE, 0x00, sizeof(MEMOFILE_STRUCT));
		if(m_bMemoRegist == false)//수정//
			strcpy(tempMEMOFILE.POI_KEY, m_asPoiKey.c_str());
		else//신규
			strcpy(tempMEMOFILE.POI_KEY, "");
		tempMEMOFILE.SEQ		= m_nFileSeq + 1;
		tempMEMOFILE.FILE_SIZE	= nFileSize;
		strcpy(tempMEMOFILE.LOCAL_PATH_NAME, asLocalPathName.c_str());
		strcpy(tempMEMOFILE.REMOTE_PATH_NAME, "");
		tempMEMOFILE.B_NEW = true;
		m_vMEMOFILE.push_back(tempMEMOFILE);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemo::funcFreeImage()
{
	if (mGetImageInfo.m_DIB != NULL){
		FreeImage_Unload(mGetImageInfo.m_DIB);
		mGetImageInfo.m_DIB = NULL;
		memset(&mGetImageInfo, 0x00, sizeof(GetImageInfo));
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemo::funcImageViewClear()
{
	mGetImageInfo.asPathName	= "";
	mGetImageInfo.nImageWidth 	= 0;
	mGetImageInfo.nImageHeight 	= 0;
	mGetImageInfo.nBPP 			= 0;
	//mGetImageInfo.nDBScale = 0;
	//mGetImageInfo.nInputScale = 0;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TfrmMemo::funcLoadImageThumb(AnsiString _asFilename)
{
	GetImageInfo		getImageInfo;

	memset(&getImageInfo, 0x00, sizeof(GetImageInfo));

	Graphics::TBitmap  	*bmpThumb;
	bmpThumb = NULL;

	//200103//메모첨부 다운로드 받다가 에러발생//Application->ProcessMessages();

	AnsiString asThumbFile	= "";

	bmpThumb = new Graphics::TBitmap();

	//200103//메모첨부 다운로드 받다가 에러발생//Application->ProcessMessages();

	getImageInfo.asPathName	= _asFilename;

	try {
		getImageInfo.m_DIB = FreeImage_Load(FreeImage_GetFileType(getImageInfo.asPathName.c_str(), 16), getImageInfo.asPathName.c_str());
	} catch (Exception &exception) {
		AnsiString strMsg = "Exception is broken up to load mGetImageInfo.m_DIB";
		frmMsg->funcMessageDlg("이미지 DIB 확인:", strMsg, 2);
		return "";
	}

	if (!getImageInfo.m_DIB) {
		AnsiString strMsg = "getImageInfo.m_DIB is NULL";
		frmMsg->funcMessageDlg("이미지 DIB 확인:", strMsg, 2);
		return "";
	}

	try {
		getImageInfo.nBPP = FreeImage_GetBPP(getImageInfo.m_DIB);
		getImageInfo.nImageWidth  = FreeImage_GetWidth(getImageInfo.m_DIB);
		getImageInfo.nImageHeight = FreeImage_GetHeight(getImageInfo.m_DIB);

		getImageInfo.mBitMapInfo = FreeImage_GetInfo(getImageInfo.m_DIB);
		memcpy(&getImageInfo.mBitMapHeadInfo, &getImageInfo.mBitMapInfo->bmiHeader, sizeof(_mBitmapHeader));

		if(FreeImage_GetFileType(getImageInfo.asPathName.c_str(), 16) == FIF_TIFF)
		{
			bmpThumb->PixelFormat = pf24bit;
		}
		else
		{
			if (getImageInfo.nBPP == 1)
				bmpThumb->PixelFormat = pf1bit;
			else if (getImageInfo.nBPP == 8)
				bmpThumb->PixelFormat = pf8bit;
			else if (getImageInfo.nBPP == 16)
				bmpThumb->PixelFormat = pf16bit;
			else if (getImageInfo.nBPP == 24)
				bmpThumb->PixelFormat = pf24bit;
			else if (getImageInfo.nBPP == 32)
				bmpThumb->PixelFormat = pf32bit;
			else
				bmpThumb->PixelFormat = pf24bit;
		}

		bmpThumb->Width 	= THUMBNAILSIZE;
		bmpThumb->Height = THUMBNAILSIZE;

		::SetStretchBltMode(bmpThumb->Canvas->Handle, HALFTONE);
		::StretchDIBits(bmpThumb->Canvas->Handle,
					0, 0, bmpThumb->Width, bmpThumb->Height,
					0, 0, getImageInfo.nImageWidth, getImageInfo.nImageHeight,
					FreeImage_GetBits(getImageInfo.m_DIB),
					getImageInfo.mBitMapInfo,
					DIB_RGB_COLORS,
					SRCCOPY);

		if(getImageInfo.m_DIB == NULL)
		{
			AnsiString strMsg = "1getImageInfo.m_DIB is NULL before calling SetDIBitsToDevice";
			frmMsg->funcMessageDlg("이미지 DIB 확인:", strMsg, 2);
		}
	}
	__finally {
		asThumbFile = ExtractFileName(_asFilename);
		AnsiString asExt = ".bmp";
		int pos = asThumbFile.Pos(".");
		if (pos > 0) {
			asThumbFile = asThumbFile.SubString(1, pos-1);
		}
		asThumbFile = ADDTHUMBPATH + asThumbFile + asExt;
		if(FileExists(asThumbFile))
			DeleteFile(asThumbFile);
		bmpThumb->SaveToFile(asThumbFile);

		//getImageInfo.bmpSource32->Assign(bmpLoad);
	}

	if (getImageInfo.m_DIB != NULL){
		FreeImage_Unload(getImageInfo.m_DIB);
		getImageInfo.m_DIB = NULL;
	}

	delete bmpThumb;
	bmpThumb->Handle = NULL;
	bmpThumb = NULL;

	return asThumbFile;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemo::imgThumbDC_onClick(TObject *Sender)
{
	int nTag 				= dynamic_cast<TImage*>(Sender)->Tag;
	AnsiString asPathName	= "";

	if(pnlThumbList != NULL)
	{
		TPanel *pnlDocDC 		= (TPanel *)pnlThumbList->Items[nTag];
		if(pnlDocDC != NULL)
		{
			asPathName = pnlDocDC->Hint;
			//DB등록 전 데이터인지 등록 후 데이터인지 확인하기//
			//우선 테스트로 등록전 데이터를 확인//
			if(asPathName.Pos("\\"))//local file
			{
				if(FileExists(asPathName))
				{
					m_nThumbIndex = nTag;
					frmMemoViewer->m_bFromMemo	= true;
					if( !frmMemoViewer->Showing )
						frmMemoViewer->Show();
					else
					{
						if(frmMain->m_bMSG)
							frmMsg->funcMessageDlg("오류알림:", "already frmMemoViewer->Showing", 3);
					}
				}
				else
				{
					frmMsg->funcMessageDlg("파일 부재 알림:", "해당 경로에 파일이 없습니다.", 3);
				}
			}
			else//remote file
			{
				if( !frmFtpControl->FuncFtpConnect(1/*FTP1*/) )//200829
				{
					AnsiString strMsg = "현재 이미지 서버에 연결할 수 없습니다.(Connect)";
					frmMsg->funcMessageDlg("이미지 연결 확인:", strMsg, 3);
					funcSetWaitWindows(false);
					return;
				}

				asPathName	= funcDownloadFile(nTag);
				if( !asPathName.IsEmpty() )
				{
					strcpy(m_vMEMOFILE[nTag].LOCAL_PATH_NAME, asPathName.c_str());
				}

				if(FileExists(asPathName))
				{
					m_nThumbIndex = nTag;
					frmMemoViewer->m_bFromMemo	= true;
					if( !frmMemoViewer->Showing )
						frmMemoViewer->Show();
					else
					{
						if(frmMain->m_bMSG)
							frmMsg->funcMessageDlg("오류알림:", "already frmMemoViewer->Showing", 3);
					}
				}
				else
				{
					frmMsg->funcMessageDlg("파일 부재 알림:", "해당 경로에 파일이 없습니다.", 3);
				}
			}
		}
		else
		{
			if(frmMain->m_bMSG)
				frmMsg->funcMessageDlg("오류알림:", "pnlDocDC == NULL", 3);
		}
	}
	else
	{
		if(frmMain->m_bMSG)
			frmMsg->funcMessageDlg("오류알림:", "pnlThumbList == NULL", 3);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemo::imgDeleteDC_onClick(TObject *Sender)
{
	frmMsg->funcMessageDlg("첨부 삭제 확인:", "파일이 서버에서 삭제됩니다. 삭제하시겠습니까?", 1);

	if(frmMsg->m_bClick)
	{
		int nTag 				= dynamic_cast<TImage*>(Sender)->Tag;
		AnsiString asPathName	= "";
		AnsiString asRenameName	= "";
		AnsiString asExt        = "";
		AnsiString asSeq		= "";

		if(pnlThumbList != NULL)
		{
			for(int i = nTag; i < pnlThumbList->Count; i++)
			{
				if(i == nTag)//삭제
				{
					TPanel *pnlDC = (TPanel *)pnlThumbList->Items[i];
					if(pnlDC != NULL)
					{
						asPathName = pnlDC->Hint;
						if(FileExists(asPathName))//delete local file
							DeleteFile(asPathName);

						TImage *imgDocDC 		= (TImage *)imgThumbList->Items[i];
						if(imgDocDC != NULL)
						{
							if(imgDocDC->Hint == "1")//delete remote file
							{
								funcDeleteFile(nTag);//
								funcWriteMemoFile(DF_DELETE_RECORD, nTag);
							}
							imgThumbList->Items[i] = NULL;
							delete imgDocDC;
						}

						//200829
						TCheckBox *chkSelectDC 		= (TCheckBox *)chkSelectList->Items[i];
						if(chkSelectDC != NULL)
						{
							chkSelectList->Items[i] = NULL;
							delete chkSelectDC;
						}

						TImage *imgDocDC2 		= (TImage *)imgDeleteList->Items[i];
						if(imgDocDC2 != NULL)
						{
							imgDeleteList->Items[i] = NULL;
							delete imgDocDC2;
						}
						pnlThumbList->Items[i] = NULL;
						delete pnlDC;
					}
					m_nThumbCount--;
					m_vMEMOFILE.erase(m_vMEMOFILE.begin() + nTag);

					if(frmMemoViewer->Showing)
					{
						if(m_vMEMOFILE.size() == 0)
						{
							frmMemoViewer->Close();
						}
						else
						{
							if(m_nThumbIndex > 0)
							{
								m_nThumbIndex--;
							}
							frmMemoViewer->lblCount->Caption = "(" + IntToStr(m_nThumbIndex+1) + "/" + IntToStr(m_nThumbCount) + ")";
							if((nTag == 0 && nTag == m_nThumbIndex) || (nTag > 0 && nTag == m_nThumbIndex+1))//MemoViewer에 보고있는 이미지를 삭제했을때//
							{
								AnsiString asPathName = m_vMEMOFILE[m_nThumbIndex].LOCAL_PATH_NAME;
								if(asPathName != NULL)
								{
									frmMemoViewer->funcLoadImage(asPathName);
								}
							}
						}
					}
				}
				else//위치이동//
				{
					TPanel *pnlDC = (TPanel *)pnlThumbList->Items[i];
					if(pnlDC != NULL)
					{
						pnlDC->Tag	= i - 1;
						pnlDC->Left	= ((i-1) % 3) * (THUMBNAILSIZE + 4);
						pnlDC->Top 	= ((i-1) / 3) * (THUMBNAILSIZE + 4);

						TImage *imgDocDC 		= (TImage *)imgThumbList->Items[i];
						TImage *imgDelDC 		= (TImage *)imgDeleteList->Items[i];
						if(imgDocDC != NULL && imgDelDC != NULL)
						{
							imgDocDC->Tag	= i - 1;
							imgDelDC->Tag   = i - 1;
							asSeq.sprintf("%03d", i);
							asPathName  	= imgDelDC->Hint;
							asExt 			= ExtractFileExt(asPathName);
							asRenameName 	= asPathName.SubString(1, asPathName.Length() - 7);
							asRenameName 	= asRenameName + asSeq + asExt;
							if(!FileExists(asPathName))
								RenameFile(asPathName, asRenameName);
						}
					}
				}
			}

			imgThumbList->Delete(nTag);
			imgDeleteList->Delete(nTag);
			pnlThumbList->Delete(nTag);

			if(m_nThumbCount / 3 < 2)
			{
				ScrollBox1->VertScrollBar->Visible = false;
				//pnlMemoFileD2->Height	= 156;
			}
			else
			{
				ScrollBox1->VertScrollBar->Visible = true;
				//pnlMemoFileD2->Height	= 76 + 80 * (m_nThumbCount / 3);
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemo::IMGHEADMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(frmMemo->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------








//***************************************************************************
// SQL
//***************************************************************************
void __fastcall TfrmMemo::funcReadMemoInfo(AnsiString _asPoiKey)
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	SQLINTEGER m_nVal[16];//201109//13->16

	memset(&tempMEMOINFO, 0x00, sizeof(MEMOINFO_STRUCT));
	int nIndex = 1;

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempMEMOINFO.POI_KEY, 		sizeof(tempMEMOINFO.POI_KEY), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempMEMOINFO.POI_NAME, 		sizeof(tempMEMOINFO.POI_NAME), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempMEMOINFO.TITLE, 		sizeof(tempMEMOINFO.TITLE), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempMEMOINFO.MEMO, 			sizeof(tempMEMOINFO.MEMO), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempMEMOINFO.OWN_NAME, 		sizeof(tempMEMOINFO.OWN_NAME), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempMEMOINFO.BATCH_YN, 		sizeof(tempMEMOINFO.BATCH_YN), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempMEMOINFO.OPEN_YN, 		sizeof(tempMEMOINFO.OPEN_YN), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempMEMOINFO.WRITE_ID, 		sizeof(tempMEMOINFO.WRITE_ID), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempMEMOINFO.WRITE_DT, 		sizeof(tempMEMOINFO.WRITE_DT), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempMEMOINFO.FILE_CNT, 	sizeof(tempMEMOINFO.FILE_CNT), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempMEMOINFO.DATA_CNT, 	sizeof(tempMEMOINFO.DATA_CNT), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_DOUBLE,  &tempMEMOINFO.X, 			sizeof(tempMEMOINFO.X), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_DOUBLE,  &tempMEMOINFO.Y, 			sizeof(tempMEMOINFO.Y), 			&m_nVal[nIndex-1]); nIndex++;
	//201109//
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_DOUBLE,  &tempMEMOINFO.LINECOLOR, 	sizeof(tempMEMOINFO.LINECOLOR), 	&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempMEMOINFO.GAGAM_X, 		sizeof(tempMEMOINFO.GAGAM_X), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempMEMOINFO.GAGAM_Y, 		sizeof(tempMEMOINFO.GAGAM_Y), 		&m_nVal[nIndex-1]); nIndex++;
	//---


	AnsiString asSqlQry		= "";
	AnsiString asSqlWhere	= "";

	asSqlWhere = "POI_KEY = '" + _asPoiKey.Trim() + "'";
	asSqlQry = "SELECT * FROM " + frmMain->TABLE_MEMOINFO + " WHERE " + asSqlWhere + " ORDER BY POI_KEY ASC";

	SQLRETURN ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	m_vMEMOINFO.clear();

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		// 뒷정리
		SQLCloseCursor(frmSql->m_hStmt);
	}
	else{
		memset(&tempMEMOINFO, 0x00, sizeof(MEMOINFO_STRUCT));
		while(SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
			m_vMEMOINFO.push_back(tempMEMOINFO);
			memset(&tempMEMOINFO, 0x00, sizeof(MEMOINFO_STRUCT));
		};
		if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemo::funcReadMemoVector(AnsiString _asPoiKey)
{
//	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);
//
//	SQLINTEGER m_nVal[5];
//
//	memset(&tempMEMOVECTOR, 0x00, sizeof(MEMOVECTOR_STRUCT));
//	int nIndex = 1;
//
//	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 		tempMEMOVECTOR.POI_KEY, sizeof(tempMEMOVECTOR.POI_KEY), 	&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 		&tempMEMOVECTOR.COUNT, 	sizeof(tempMEMOVECTOR.COUNT), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 		&tempMEMOVECTOR.SIZE, 	sizeof(tempMEMOVECTOR.SIZE), 		&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_DOUBLE, 		&tempMEMOVECTOR.X, 		sizeof(tempMEMOVECTOR.X), 			&m_nVal[nIndex-1]); nIndex++;
//	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_DOUBLE, 		&tempMEMOVECTOR.Y, 		sizeof(tempMEMOVECTOR.Y), 			&m_nVal[nIndex-1]); nIndex++;
//
//	AnsiString asSqlQry		= "";
//	AnsiString asSqlWhere	= "";
//
//	asSqlWhere = "POI_KEY = '" + _asPoiKey.Trim() + "'";
//	asSqlQry = "SELECT * FROM " + frmMain->TABLE_MEMOVECTOR + " WHERE " + asSqlWhere + " ORDER BY POI_KEY, SEQ ASC";
//
//	SQLRETURN ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
//	ret = SQLExecute(frmSql->m_hStmt);
//
//	m_vMEMOVECTOR.clear();
//
//	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
//		// 뒷정리
//		SQLCloseCursor(frmSql->m_hStmt);
//	}
//	else{
//		memset(&tempMEMOVECTOR, 0x00, sizeof(MEMOVECTOR_STRUCT));
//		while(SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
//			m_vMEMOVECTOR.push_back(tempMEMOVECTOR);
//			memset(&tempMEMOVECTOR, 0x00, sizeof(MEMOVECTOR_STRUCT));
//		};
//		if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);
//	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemo::funcReadMemoFile(AnsiString _asPoiKey)
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	SQLINTEGER m_nVal[4];

	memset(&tempMEMOFILE, 0x00, sizeof(MEMOFILE_STRUCT));
	int nIndex = 1;

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempMEMOFILE.POI_KEY, 			sizeof(tempMEMOFILE.POI_KEY), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempMEMOFILE.SEQ, 				sizeof(tempMEMOFILE.SEQ), 				&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_LONG, 	&tempMEMOFILE.FILE_SIZE, 		sizeof(tempMEMOFILE.FILE_SIZE), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempMEMOFILE.REMOTE_PATH_NAME, 	sizeof(tempMEMOFILE.REMOTE_PATH_NAME), 	&m_nVal[nIndex-1]); nIndex++;

	AnsiString asSqlQry		= "";
	AnsiString asSqlWhere	= "";

	asSqlWhere = "POI_KEY = '" + _asPoiKey.Trim() + "'";
	asSqlQry = "SELECT * FROM " + frmMain->TABLE_MEMOFILE + " WHERE " + asSqlWhere + " ORDER BY POI_KEY, SEQ ASC";

	SQLRETURN ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	m_vMEMOFILE.clear();

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		// 뒷정리
		SQLCloseCursor(frmSql->m_hStmt);
	}
	else{
		memset(&tempMEMOFILE, 0x00, sizeof(MEMOFILE_STRUCT));
		while(SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
			tempMEMOFILE.B_NEW = false;
			strcpy(tempMEMOFILE.LOCAL_PATH_NAME, "");
			m_vMEMOFILE.push_back(tempMEMOFILE);
			memset(&tempMEMOFILE, 0x00, sizeof(MEMOFILE_STRUCT));
		};
		if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemo::funcReadMemoInfoHis(AnsiString _asPoiKey)
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString asSqlQry		= "";
	AnsiString asSqlWhere	= "";
	SQLINTEGER m_nVal[6];//201109//3->6
	int nIndex = 1;

	memset(&tempMEMOINFOHIS, 0x00, sizeof(MEMOINFOHIS_STRUCT));

	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempMEMOINFOHIS.MEMO, 			sizeof(tempMEMOINFOHIS.MEMO), 			&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempMEMOINFOHIS.WRITE_ID, 		sizeof(tempMEMOINFOHIS.WRITE_ID), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempMEMOINFOHIS.WRITE_DT, 		sizeof(tempMEMOINFOHIS.WRITE_DT), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_DOUBLE, 	&tempMEMOINFOHIS.LINECOLOR, 	sizeof(tempMEMOINFOHIS.LINECOLOR), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempMEMOINFOHIS.GAGAM_X, 		sizeof(tempMEMOINFOHIS.GAGAM_X), 		&m_nVal[nIndex-1]); nIndex++;
	SQLBindCol(frmSql->m_hStmt, nIndex,  SQL_C_CHAR, 	tempMEMOINFOHIS.GAGAM_Y, 		sizeof(tempMEMOINFOHIS.GAGAM_Y), 		&m_nVal[nIndex-1]); nIndex++;

	asSqlWhere = "POI_KEY = '" + _asPoiKey.Trim() + "'";
	asSqlQry = "SELECT MEMO, WRITE_ID, WRITE_DT, LINECOLOR, GAGAM_X, GAGAM_Y FROM " + frmMain->TABLE_MEMOINFOHIS + " WHERE " + asSqlWhere + " ORDER BY WRITE_DT DESC";

	//---
	SQLRETURN ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)asSqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	m_vMEMOINFOHIS.clear();

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		// 뒷정리
		SQLCloseCursor(frmSql->m_hStmt);
	}

	memset(&tempMEMOINFOHIS, 0x00, sizeof(MEMOINFOHIS_STRUCT));
	while(SQLFetch(frmSql->m_hStmt)!=SQL_NO_DATA) {
		m_vMEMOINFOHIS.push_back(tempMEMOINFOHIS);
		memset(&tempMEMOINFOHIS, 0x00, sizeof(MEMOINFOHIS_STRUCT));
	};

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);
}
//---------------------------------------------------------------------------

//#MOMOHISTORY#
bool __fastcall TfrmMemo::funcWriteMemoInfo(int _nType, int _nIndex)
{
	AnsiString 	asSqlQry	= "";
	AnsiString 	asSqlTbl 	= frmMain->TABLE_MEMOINFO;
	AnsiString 	asSqlCol 	= "";
	AnsiString 	asSqlVal 	= "";
	AnsiString 	asSqlWhere 	= "";
	//201109//char 		cCol[13][20] = {	"POI_KEY", "POI_NAME", "TITLE", "MEMO", "OWN_NAME", "BATCH_YN", "OPEN_YN", "WRITE_ID", "WRITE_DT", "FILE_CNT", "DATA_CNT", "X", "Y"};
	//201109//int		nColCount 	= 13;
	char 		cCol[16][20] = {	"POI_KEY", "POI_NAME", "TITLE", "MEMO", "OWN_NAME", "BATCH_YN", "OPEN_YN", "WRITE_ID", "WRITE_DT", "FILE_CNT", "DATA_CNT", "X", "Y", "LINECOLOR", "GAGAM_X", "GAGAM_Y"};//201109//
	int			nColCount 	= 16;
	AnsiString  asNowDT 	= Now().FormatString("yyyymmddhhmmss");
	AnsiString 	asStr	 	= "";
	int			nCnt		= 0;
	double		dPos		= 0.0;
	double		dLineColor	= 0;

	strcpy(m_vMEMOINFO[_nIndex].WRITE_DT, asNowDT.c_str());

	if (_nType == DF_NEW_RECORD)//====================================
	{
		//Insert Column
		for(int i = 0; i < nColCount; i++)
		{
			AnsiString asCol = cCol[i];
			asSqlCol = asSqlCol + asCol;
			if(i != nColCount-1)
				asSqlCol = asSqlCol + ", ";
		}

		//Insert Values
		asStr    	= (char*)m_vMEMOINFO[_nIndex].POI_KEY;
		asSqlVal 	= asSqlVal + "'" + asStr.Trim() + "', ";
		asStr    	= (char*)m_vMEMOINFO[_nIndex].POI_NAME;
		asSqlVal 	= asSqlVal + "'" + asStr.Trim() + "', ";
		asStr    	= (char*)m_vMEMOINFO[_nIndex].TITLE;
		asSqlVal 	= asSqlVal + "'" + asStr.Trim() + "', ";
		asStr    	= (char*)m_vMEMOINFO[_nIndex].MEMO;
		asSqlVal 	= asSqlVal + "'" + asStr.Trim() + "', ";
		asStr    	= (char*)m_vMEMOINFO[_nIndex].OWN_NAME;
		asSqlVal 	= asSqlVal + "'" + asStr.Trim() + "', ";
		asStr    	= (char*)m_vMEMOINFO[_nIndex].BATCH_YN;
		asSqlVal 	= asSqlVal + "'" + asStr.Trim() + "', ";
		asStr    	= (char*)m_vMEMOINFO[_nIndex].OPEN_YN;
		asSqlVal 	= asSqlVal + "'" + asStr.Trim() + "', ";
		asStr    	= (char*)m_vMEMOINFO[_nIndex].WRITE_ID;
		asSqlVal 	= asSqlVal + "'" + asStr.Trim() + "', ";
		asStr    	= (char*)m_vMEMOINFO[_nIndex].WRITE_DT;
		asSqlVal 	= asSqlVal + "'" + asStr.Trim() + "', ";
		nCnt   		= m_vMEMOINFO[_nIndex].FILE_CNT;
		asSqlVal 	= asSqlVal + nCnt + ", ";
		nCnt    	= m_vMEMOINFO[_nIndex].DATA_CNT;
		asSqlVal 	= asSqlVal + nCnt + ", ";
		dPos   		= m_vMEMOINFO[_nIndex].X;
		asSqlVal 	= asSqlVal + dPos + ", ";
//		dPos    	= m_vMEMOINFO[_nIndex].Y;
//		asSqlVal 	= asSqlVal + dPos;
		//201109//
		dPos    	= m_vMEMOINFO[_nIndex].Y;
		asSqlVal 	= asSqlVal + dPos + ", ";
		dLineColor 	= m_vMEMOINFO[_nIndex].LINECOLOR;
		asSqlVal 	= asSqlVal + dLineColor + ", ";
		asStr 		= (char*)m_vMEMOINFO[_nIndex].GAGAM_X;
		asSqlVal 	= asSqlVal + "'" + asStr + "', ";//201207//''누락//
		asStr 		= (char*)m_vMEMOINFO[_nIndex].GAGAM_Y;
		asSqlVal 	= asSqlVal + "'" + asStr + "'";//201207//''누락//
		//---

		asSqlQry.sprintf("INSERT INTO %s (%s) values (%s)",	asSqlTbl, asSqlCol, asSqlVal);

		return frmSql->func_QryProcess(asSqlQry);
	}
	else if (_nType == DF_UPDATE_RECORD)//====================================
	{
		//Update Column
		asStr  		= (char*)m_vMEMOINFO[_nIndex].TITLE;
		asSqlCol 	= asSqlCol + cCol[2] + " = '" + asStr.Trim() + "', ";
		asStr    	= (char*)m_vMEMOINFO[_nIndex].MEMO;
		asSqlCol 	= asSqlCol + cCol[3] + " = '" + asStr.Trim() + "', ";
//		asStr    	= (char*)m_vMEMOINFO[_nIndex].OWN_NAME;
//		asSqlCol 	= asSqlCol + cCol[4] + " = '" + asStr.Trim() + "', ";
//		asStr    	= (char*)m_vMEMOINFO[_nIndex].BATCH_YN;
//		asSqlCol 	= asSqlCol + cCol[5] + " = '" + asStr.Trim() + "', ";
		asStr    	= (char*)m_vMEMOINFO[_nIndex].OPEN_YN;
		asSqlCol 	= asSqlCol + cCol[6] + " = '" + asStr.Trim() + "', ";
		asStr    	= (char*)m_vMEMOINFO[_nIndex].WRITE_ID;
		asSqlCol 	= asSqlCol + cCol[7] + " = '" + asStr.Trim() + "', ";
		asStr    	= (char*)m_vMEMOINFO[_nIndex].WRITE_DT;
		asSqlCol 	= asSqlCol + cCol[8] + " = '" + asStr.Trim() + "', ";
//		nCnt		= m_vMEMOINFO[_nIndex].FILE_CNT;
//		asSqlCol 	= asSqlCol + cCol[9] + " = "  + nCnt;
		//201109//
		nCnt		= m_vMEMOINFO[_nIndex].FILE_CNT;
		asSqlCol 	= asSqlCol + cCol[9] + " = "  + nCnt + ", ";
		dLineColor 	= m_vMEMOINFO[_nIndex].LINECOLOR;
		asSqlCol 	= asSqlCol + cCol[13] + " = "  + dLineColor + ", ";
		asStr 		= (char*)m_vMEMOINFO[_nIndex].GAGAM_X;
		asSqlCol 	= asSqlCol + cCol[14] + " = '"  + asStr + "', ";
		asStr 		= (char*)m_vMEMOINFO[_nIndex].GAGAM_Y;
		asSqlCol 	= asSqlCol + cCol[15] + " = '"  + asStr + "'";
		//---

		//Where Condition
		asStr    	= (char*)m_vMEMOINFO[_nIndex].POI_KEY;
		asSqlWhere 	= asSqlWhere + cCol[0] 	+ " = '" + asStr.Trim() + "'";

		asSqlQry.sprintf("UPDATE %s SET %s WHERE %s", asSqlTbl, asSqlCol, asSqlWhere);

		return frmSql->func_QryProcess(asSqlQry);
	}
	else if (_nType == DF_DELETE_RECORD)//====================================
	{
		//Where Condition
		asStr    	= (char*)m_vMEMOINFO[_nIndex].POI_KEY;
		asSqlWhere 	= asSqlWhere + cCol[0] 	+ " = '" + asStr.Trim() + "'";

		asSqlQry.sprintf("DELETE FROM %s WHERE %s", asSqlTbl, asSqlWhere);

		return frmSql->func_QryProcess(asSqlQry);
	}

	return false;
}
//---------------------------------------------------------------------------

bool __fastcall TfrmMemo::funcWriteMemoVector(int _nType, int _nIndex)
{
	AnsiString 	asSqlQry	= "";
	AnsiString 	asSqlTbl 	= frmMain->TABLE_MEMOVECTOR;
	AnsiString 	asSqlCol 	= "";
	AnsiString 	asSqlVal 	= "";
	AnsiString 	asSqlWhere 	= "";
	char 		cCol[4][20] = {	"POI_KEY", "COUNT", "SIZE", "VECTOR"};
	int			nColCount 	= 4;
	AnsiString 	asStr	 	= "";
	int			nSeq	 	= 0;
	double		dPos 		= 0;
//
//	if (_nType == DF_NEW_RECORD)//====================================
//	{
//		//Insert Column
//		for(int i = 0; i < nColCount; i++)
//		{
//			AnsiString asCol = cCol[i];
//			asSqlCol = asSqlCol + asCol;
//			if(i != nColCount-1)
//				asSqlCol = asSqlCol + ", ";
//		}
//
//		//Insert Values
//		asStr    	= (char*)m_vMEMOVECTOR[_nIndex].POI_KEY;
//		asSqlVal 	= asSqlVal + "'" + asStr.Trim() + "', ";
//		nSeq     	= m_vMEMOVECTOR[_nIndex].COUNT;
//		asSqlVal 	= asSqlVal + nSeq + ", ";
//		nSeq     	= m_vMEMOVECTOR[_nIndex].SIZE;
//		asSqlVal 	= asSqlVal + nSeq + ", ";
//		dPos    	= m_vMEMOVECTOR[_nIndex].X;
//		asSqlVal 	= asSqlVal + dPos + ", ";
//		dPos    	= m_vMEMOVECTOR[_nIndex].Y;
//		asSqlVal 	= asSqlVal + dPos;
//
//		asSqlQry.sprintf("INSERT INTO %s (%s) values (%s)",	asSqlTbl, asSqlCol, asSqlVal);
//
//		return frmSql->func_QryProcess(asSqlQry);
//	}
//	else if (_nType == DF_UPDATE_RECORD)//====================================
//	{
//		//Update Column
//		dPos  		= m_vMEMOVECTOR[_nIndex].X;
//		asSqlCol 	= asSqlCol + cCol[2] + " = " + dPos + ", ";
//		dPos    	= m_vMEMOVECTOR[_nIndex].Y;
//		asSqlCol 	= asSqlCol + cCol[3] + " = " + dPos;
//
//		//Where Condition
//		asStr    	= (char*)m_vMEMOVECTOR[_nIndex].POI_KEY;
//		nSeq     	= m_vMEMOVECTOR[_nIndex].COUNT;
//		asSqlWhere 	= asSqlWhere + cCol[0] 	+ " = '" + asStr.Trim() + "'";
//		asSqlWhere 	= asSqlWhere + " AND " + cCol[1] + " = " + nSeq;
//
//		asSqlQry.sprintf("UPDATE %s SET %s WHERE %s", asSqlTbl, asSqlCol, asSqlWhere);
//
//		return frmSql->func_QryProcess(asSqlQry);
//	}
//	else if (_nType == DF_DELETE_RECORD)//====================================
//	{
//		//Where Condition
//		asStr    	= (char*)m_vMEMOVECTOR[_nIndex].POI_KEY;
//		nSeq     	= m_vMEMOVECTOR[_nIndex].COUNT;
//		asSqlCol 	= asSqlCol + cCol[0] 	+ " = '" + asStr.Trim() + "'";
//		asSqlCol 	= asSqlCol + " AND " + cCol[1] + " = " + nSeq;
//		asSqlWhere 	= asSqlWhere + asSqlCol;
//
//		asSqlQry.sprintf("DELETE FROM %s WHERE %s", asSqlTbl, asSqlWhere);
//
//		return frmSql->func_QryProcess(asSqlQry);
//	}

	if (_nType == DF_DELETE_RECORD)//====================================
	{
		//Where Condition
		asStr    	= (char*)m_vMEMOINFO[_nIndex].POI_KEY;
		//asSqlCol 	= asSqlCol + cCol[0] 	+ " LIKE '" + asStr.SubString(1, 17).Trim() + "%'";
		asSqlCol 	= asSqlCol + cCol[0] 	+ " = '" + asStr.Trim() + "'";
		asSqlWhere 	= asSqlWhere + asSqlCol;

		asSqlQry.sprintf("DELETE FROM %s WHERE %s", asSqlTbl, asSqlWhere);

		return frmSql->func_QryProcess(asSqlQry);
	}
	return false;
}
//---------------------------------------------------------------------------

bool __fastcall TfrmMemo::funcWriteMemoFile(int _nType, int _nIndex)
{
	AnsiString 	asSqlQry	= "";
	AnsiString 	asSqlTbl 	= frmMain->TABLE_MEMOFILE;
	AnsiString 	asSqlCol 	= "";
	AnsiString 	asSqlVal 	= "";
	AnsiString 	asSqlWhere 	= "";
	char 		cCol[4][20] = {	"POI_KEY", "SEQ", "FILE_SIZE", "PATH_NAME"};
	int			nColCount 	= 4;
	AnsiString 	asStr	 	= "";
	int			nSeq	 	= 0;
	int			nFileSize 	= 0;

	if (_nType == DF_NEW_RECORD)//====================================
	{
		//Insert Column
		for(int i = 0; i < nColCount; i++)
		{
			AnsiString asCol = cCol[i];
			asSqlCol = asSqlCol + asCol;
			if(i != nColCount-1)
				asSqlCol = asSqlCol + ", ";
		}

		//Insert Values
		asStr    	= (char*)m_vMEMOFILE[_nIndex].POI_KEY;
		asSqlVal 	= asSqlVal + "'" + asStr.Trim() + "', ";
		nSeq     	= m_vMEMOFILE[_nIndex].SEQ;
		asSqlVal 	= asSqlVal + nSeq + ", ";
		nFileSize    = m_vMEMOFILE[_nIndex].FILE_SIZE;
		asSqlVal 	= asSqlVal + nFileSize + ", ";
		asStr    	= (char*)m_vMEMOFILE[_nIndex].REMOTE_PATH_NAME;
		asSqlVal 	= asSqlVal + "'" + asStr.Trim() + "'";

		asSqlQry.sprintf("INSERT INTO %s (%s) values (%s)",	asSqlTbl, asSqlCol, asSqlVal);

		return frmSql->func_QryProcess(asSqlQry);
	}
	else if (_nType == DF_UPDATE_RECORD)//====================================
	{
		//Update Column
		nFileSize  	= m_vMEMOFILE[_nIndex].FILE_SIZE;
		asStr    	= (char*)m_vMEMOFILE[_nIndex].REMOTE_PATH_NAME;
		asSqlCol 	= asSqlCol + cCol[2] + " = "  + nFileSize    + ", ";
		asSqlCol 	= asSqlCol + cCol[3] + " = '" + asStr.Trim() + "'";

		//Where Condition
		asStr    	= (char*)m_vMEMOFILE[_nIndex].POI_KEY;
		nSeq     	= m_vMEMOFILE[_nIndex].SEQ;
		asSqlWhere 	= asSqlWhere + cCol[0] + " = '" + asStr.Trim() + "'";
		asSqlWhere 	= asSqlWhere + " AND " + cCol[1] + " = " + nSeq;

		asSqlQry.sprintf("UPDATE %s SET %s WHERE %s", asSqlTbl, asSqlCol, asSqlWhere);

		return frmSql->func_QryProcess(asSqlQry);
	}
	else if (_nType == DF_DELETE_RECORD)//====================================
	{
		//Where Condition
		asStr    	= (char*)m_vMEMOFILE[_nIndex].POI_KEY;
		nSeq     	= m_vMEMOFILE[_nIndex].SEQ;
		asSqlWhere 	= asSqlWhere + cCol[0] 	+ " = '" + asStr.Trim() + "'";
		asSqlWhere 	= asSqlWhere + " AND " + cCol[1] + " = " + nSeq;

		asSqlQry.sprintf("DELETE FROM %s WHERE %s", asSqlTbl, asSqlWhere);

		return frmSql->func_QryProcess(asSqlQry);
	}

	return false;
}
//---------------------------------------------------------------------------


bool __fastcall TfrmMemo::funcWriteMemoInfoHistory(int _nIndex)
{
	AnsiString 	asSqlQry	= "";
	AnsiString 	asSqlTbl 	= frmMain->TABLE_MEMOINFOHIS;
	AnsiString 	asSqlCol 	= "";
	AnsiString 	asSqlVal 	= "";
	AnsiString 	asSqlWhere 	= "";
//201109//	char 		cCol[10][20] = {	"POI_KEY", "POI_NAME", "TITLE", "MEMO", "WRITE_ID", "WRITE_DT", "FILE_CNT", "DATA_CNT", "X", "Y"};
//201109//	int			nColCount 	= 10;
	char 		cCol[13][20] = {	"POI_KEY", "POI_NAME", "TITLE", "MEMO", "WRITE_ID", "WRITE_DT", "FILE_CNT", "DATA_CNT", "X", "Y", "LINECOLOR", "GAGAM_X", "GAGAM_Y"};//201109//
	int			nColCount 	= 13;//201109//
	AnsiString  asNowDT 	= Now().FormatString("yyyymmddhhmmss");
	AnsiString 	asStr	 	= "";
	int			nCnt		= 0;
	double		dPos		= 0.0;
	double		dLineColor	= 0;//201109//

	strcpy(m_vMEMOINFO[_nIndex].WRITE_DT, asNowDT.c_str());

	//Insert Column
	for(int i = 0; i < nColCount; i++)
	{
		AnsiString asCol = cCol[i];
		asSqlCol = asSqlCol + asCol;
		if(i != nColCount-1)
			asSqlCol = asSqlCol + ", ";
	}

	//Insert Values
	asStr    	= (char*)m_vMEMOINFO[_nIndex].POI_KEY;
	asSqlVal 	= asSqlVal + "'" + asStr.Trim() + "', ";
	asStr    	= (char*)m_vMEMOINFO[_nIndex].POI_NAME;
	asSqlVal 	= asSqlVal + "'" + asStr.Trim() + "', ";
	asStr    	= (char*)m_vMEMOINFO[_nIndex].TITLE;
	asSqlVal 	= asSqlVal + "'" + asStr.Trim() + "', ";
	asStr    	= (char*)m_vMEMOINFO[_nIndex].MEMO;
	asSqlVal 	= asSqlVal + "'" + asStr.Trim() + "', ";
	asStr    	= (char*)m_vMEMOINFO[_nIndex].WRITE_ID;
	asSqlVal 	= asSqlVal + "'" + asStr.Trim() + "', ";
	asStr    	= (char*)m_vMEMOINFO[_nIndex].WRITE_DT;
	asSqlVal 	= asSqlVal + "'" + asStr.Trim() + "', ";
	nCnt   		= m_vMEMOINFO[_nIndex].FILE_CNT;
	asSqlVal 	= asSqlVal + nCnt + ", ";
	nCnt    	= m_vMEMOINFO[_nIndex].DATA_CNT;
	asSqlVal 	= asSqlVal + nCnt + ", ";
	dPos   		= m_vMEMOINFO[_nIndex].X;
	asSqlVal 	= asSqlVal + dPos + ", ";
//	dPos    	= m_vMEMOINFO[_nIndex].Y;
//	asSqlVal 	= asSqlVal + dPos;
	//201109//
	dPos    	= m_vMEMOINFO[_nIndex].Y;
	asSqlVal 	= asSqlVal + dPos + ", ";
	dLineColor 	= m_vMEMOINFO[_nIndex].LINECOLOR;
	asSqlVal 	= asSqlVal + dLineColor + ", ";
	asStr 		= (char*)m_vMEMOINFO[_nIndex].GAGAM_X;
	asSqlVal 	= asSqlVal + "'" + asStr + "', ";//201207//''누락//
	asStr 		= (char*)m_vMEMOINFO[_nIndex].GAGAM_Y;
	asSqlVal 	= asSqlVal + "'" + asStr + "'";//201207//''누락//
	//---

	asSqlQry.sprintf("INSERT INTO %s (%s) values (%s)",	asSqlTbl, asSqlCol, asSqlVal);

	return frmSql->func_QryProcess(asSqlQry);
}
//---------------------------------------------------------------------------

AnsiString __fastcall TfrmMemo::funcUploadFile(int _nIndex)
{
	FTP_FILE_STRUCT	mUploadFile;
	AnsiString asTarget 		= frmMain->FTP_DIR_MEMO;
	AnsiString asRemoteFilePath = "";//ftp upload되는 path
	AnsiString asLocalFilePath 	= (char*)m_vMEMOFILE[_nIndex].LOCAL_PATH_NAME;//Local File Path//이 함수 반환값을 다시 여기에 넣는다.
	AnsiString asFileName       = "";

	asFileName = ExtractFileName(asLocalFilePath);
	if(asFileName.Length() == 0)
		return "";

	memset(&mUploadFile, 0x00, sizeof(mUploadFile));
	wsprintf(mUploadFile.cTarget, "%s", asTarget.c_str());
	wsprintf(mUploadFile.cFileName, "%s", asFileName.c_str());
	wsprintf(mUploadFile.cLocalFilePath, "%s", asLocalFilePath.c_str());//Local File Path
	wsprintf(mUploadFile.cFileType, "%s", asLocalFilePath.SubString(asLocalFilePath.Length() - 2, 3));
	wsprintf(mUploadFile.cIndexPolder, "%s/", m_asPoiKey.c_str());

	if (!frmFtpControl->FuncFtpFileUpload(0, &mUploadFile, 0))
	{
		return asRemoteFilePath;
	}

	asRemoteFilePath.sprintf("%s/%s%s", mUploadFile.cTarget, mUploadFile.cIndexPolder, mUploadFile.cFileName);
	return asRemoteFilePath;
}
//---------------------------------------------------------------------------

AnsiString __fastcall TfrmMemo::funcDownloadFile(int _nIndex)
{
	FTP_FILE_STRUCT	mDownFile;
	AnsiString	asRemoteFilePath	= (char*)m_vMEMOFILE[_nIndex].REMOTE_PATH_NAME;
	AnsiString	asLocalFilePath		= ADDFILEPATH;
	AnsiString  asFileName       	= "";

	asRemoteFilePath = StringReplace(asRemoteFilePath, "/", "\\", TReplaceFlags() <<rfReplaceAll);
	asFileName = ExtractFileName(asRemoteFilePath);
	if(asFileName.Length() == 0)
		return "";

	asRemoteFilePath = ExtractFilePath(asRemoteFilePath);
	asRemoteFilePath = StringReplace(asRemoteFilePath, "\\", "/", TReplaceFlags() <<rfReplaceAll);
	//---
	memset(&mDownFile, 0x00, sizeof(mDownFile));
	wsprintf(mDownFile.cFileName, asFileName.c_str());
	wsprintf(mDownFile.cRemoteFilePath, asRemoteFilePath.c_str());
	wsprintf(mDownFile.cLocalFilePath, (asLocalFilePath+asFileName).c_str());

	if( frmFtpControl->FuncFtpFileDownload(0, &mDownFile, 0) )
		return asLocalFilePath+asFileName;
	else
		return "";
}
//---------------------------------------------------------------------------

bool __fastcall TfrmMemo::funcDeleteFile(int _nIndex)
{
	FTP_FILE_STRUCT	mDeleteFile;
	AnsiString  asTarget = frmMain->FTP_DIR_MEMO;
	AnsiString	asRemoteFile;
	AnsiString	asRemoteDir;
	AnsiString  asRemoteFilePath;
	AnsiString	asRemoteFullFilePath;

	//---
	memset(&mDeleteFile, 0x00, sizeof(mDeleteFile));
	asRemoteFullFilePath    = m_vMEMOFILE[_nIndex].REMOTE_PATH_NAME;
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

int __fastcall TfrmMemo::funcReadMaxSeq(AnsiString _asPoiKey)
{
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	SQLCHAR    	m_cVal[16+1];
	SQLINTEGER 	m_nVal;
	SQLRETURN 	ret;
	AnsiString 	asSqlTbl	= frmMain->TABLE_MEMOFILE;
	AnsiString  asSqlWhere 	= "";
	AnsiString 	asSqlQry 	= "";
	int			nSeq		= 0;
	AnsiString  result 		= "";
	char 		min_cValue[16+1];

	memset(m_cVal,0x00,sizeof(m_cVal));
	SQLBindCol(frmSql->m_hStmt, 1, SQL_C_CHAR, m_cVal, sizeof(m_cVal), &m_nVal);

	asSqlWhere = asSqlWhere + "POI_KEY = '" + _asPoiKey + "'";

	asSqlQry.sprintf("SELECT MAX(SEQ) FROM %s WHERE %s", asSqlTbl, asSqlWhere);

	ret = SQLPrepare(frmSql->m_hStmt, (SQLCHAR *)asSqlQry.c_str(), SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
		return -1;
	}

	while (SQLFetch(frmSql->m_hStmt) != SQL_NO_DATA)
	{
		memset(min_cValue, 0x00, sizeof(min_cValue));
		memcpy(min_cValue, m_cVal, sizeof( min_cValue));
		result = min_cValue;
		if( !result.IsEmpty() )
		{
			nSeq = StrToInt(result);
			break;
		}
		break;
	};
	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	return nSeq;
}
//---------------------------------------------------------------------------

bool __fastcall TfrmMemo::funcCheckSameData()
{
	AnsiString asStr = "";

	//TITLE
	asStr	= edtMemoTitle->Text.Trim();
	if( strcmp(m_vMEMOINFO[0].TITLE, asStr.c_str()) )
		return false;

	//MEMO
	asStr	= edtMemoMemo->Text.Trim();
	if( strcmp(m_vMEMOINFO[0].MEMO, asStr.c_str()) )
		return false;

	//OPEN_YN
	if(chkOpenYN->Checked)
		asStr = "Y";
	else
		asStr = "N";
	if( strcmp(m_vMEMOINFO[0].OPEN_YN, asStr.c_str()) )
		return false;

	//FILE_CNT
	if( m_vMEMOINFO[0].FILE_CNT != m_nThumbCount )
		return false;
	if(m_nThumbCount > 0 && m_nFileSeq != m_vMEMOFILE[m_nThumbCount-1].SEQ)
		return false;

	return true;//ALL SAME DATA
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemo::IMGMEMOHISClick(TObject *Sender)
{
	if( !frmMemoHis->Showing )
		frmMemoHis->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemo::funcWriteFileVectorLog()
{
	FILE 			*fd;
	AnsiString 		asFileName 	= frmMain->ROOTPATH + "vector" + m_asTempPoiKey + ".log";
	int         	nSize 		= (int)frmMain->m_vMEMORECT.size();
	GPoint			tempPoints;
	vector<GPoint>	vPoints;

	if(nSize == 0)
		return;

	vPoints.clear();
	for(int i = 0; i < nSize; i++)
	{
		memset(&tempPoints, 0x00, sizeof(GPoint));
		tempPoints.x	= frmMain->m_vMEMORECT[i].x;
		tempPoints.y	= frmMain->m_vMEMORECT[i].y;

		if(tempPoints.x <= 0 || tempPoints.y <= 0)
			continue;

		vPoints.push_back(tempPoints);
	}

	if(FileExists(asFileName))
		DeleteFile(asFileName);

	fd = fopen(asFileName.c_str(), "wb+");
	fseek(fd,0,SEEK_END);

	for(int i = 0; i < nSize; i++)
	{
		fwrite(&vPoints[i], sizeof(GPoint), 1, fd);
	}
	fclose(fd);


	DWORD dwFileSize = 0;
	//asFileName = StringReplace(asFullPath, asBasicPath, "", flags);
	dwFileSize = GetLocalFileSize(asFileName);

	if( (dwFileSize % sizeof(GPoint)) != 0)
	{
		frmMsg->funcMessageDlg("영역설정확인:", "영역데이터에 오류가 발견되었습니다. 다시 설정해주세요.", 3);
		return;
    }

	try{
		funcPutBinaryData(asFileName, nSize, dwFileSize);
	}
	__finally{
//		if(FileExists(asFileName))
//			DeleteFile(asFileName);
	}
}
//---------------------------------------------------------------------------

bool __fastcall TfrmMemo::funcPutBinaryData(AnsiString _asFileName, int _nCount, LONG _lFileSize)
{
	SQLRETURN       ret;
	SQLTCHAR      * pWriteBuff;
	SQLINTEGER      ind = SQL_DATA_AT_EXEC;
	int             chunksize, dtsize;      // 데이터를 잘라서 보낼려고
	AnsiString      asSql = "";
	bool			bRet = false;
	SDWORD          cbFileName, cbFileSize, cbUpdateTime;

	if (_lFileSize > MAX_CHUNK_SIZE)             // 한번에 보낼수있는 최대 바이트
		chunksize = MAX_CHUNK_SIZE;         // 보다 크면 잘라서 보냄
	else
		chunksize = _lFileSize;

	if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

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
			ShowMessage("메모리 할당 확인");
			return false;
		}
		memset(buffer, 0x00, _lFileSize);

		nResult = fread(buffer, sizeof(char), _lFileSize, fd);
		if(nResult != (size_t)_lFileSize)
		{
			ShowMessage("파일 읽기 확인");
			return false;
		}

//		if(frmMain->m_bMSG)
//		{
//			AnsiString asFileName = frmMain->ROOTPATH + "\\buffer.txt";
//			TStringList *qry = new TStringList();
//			qry->Clear();
//			qry->Text = "";
//			qry->Add(buffer);
//			qry->SaveToFile(asFileName.c_str());
//			if(qry != NULL)
//			{
//				delete qry;
//				qry = NULL;
//			}
//		}

		fclose(fd);

		//-------------------------------------------------------------------
		//POI_KEY, COUNT, SIZE, VECTOR
		asSql = "INSERT INTO " + frmMain->TABLE_MEMOVECTOR + " VALUES ('" + m_asTempPoiKey.Trim() + "', " + _nCount + ", " + _lFileSize + ", ? )";

		// 쿼리를 준비합니다.SQLBindParameter를 사용하기위한 준비작업
		ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR*)asSql.c_str(), SQL_NTS);
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
						ShowMessage("1:" + ret);
				}
				else
				{
					ShowMessage("2:" + ret);
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

__int64 __fastcall TfrmMemo::GetLocalFileSize(AnsiString _asFileName)
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

void __fastcall TfrmMemo::funcReadFileVectorLog(AnsiString _asPoiKey)
{
	FILE 			*fd;
	LONG 			_lFileSize;
	AnsiString 		asFileName 	= frmMain->ROOTPATH + "vector" + _asPoiKey + ".log";
	int				nSize = 0;
	GPoint			tempPoints;
	MEMOVECTOR_STRUCT				tempMEMOVECTOR;

	try{
		nSize = funcGetBinaryData(_asPoiKey);
	}
	__finally{
		if(FileExists(asFileName))
		{
			//220429//44250//MEMORYLEAK//fd = fopen(asFileName.c_str(), "rb+");
			fd = fopen(asFileName.c_str(), "rb");//220429//44250//MEMORYLEAK//

			if(fd != NULL)//220429//44250//MEMORYLEAK//
			{
				fseek (fd , 0 , SEEK_END);
				_lFileSize = ftell (fd);
				rewind (fd);

				//
				memset(&tempMEMOVECTOR, 0x00, sizeof(MEMOVECTOR_STRUCT));
				memcpy(&tempMEMOVECTOR.POI_KEY, _asPoiKey.c_str(), sizeof(tempMEMOVECTOR.POI_KEY));
				tempMEMOVECTOR.COUNT = nSize;
				tempMEMOVECTOR.SIZE = (int)_lFileSize;

				for(int i = 0; i < nSize; i++)
				{
					memset(&tempPoints, 0x00, sizeof(GPoint));
					fread(&tempPoints, sizeof(GPoint), 1, fd);
					//vPoints.push_back(tempPoints);
					tempMEMOVECTOR.VECTOR.push_back(tempPoints);
				}
				m_vMEMOVECTOR.push_back(tempMEMOVECTOR);

				fclose(fd);

				//220429//Move to here
				GPoint gPoint;
				MBR    mMBR;

				memset(&frmSql->tMemoPoly, 0x00, sizeof(polyObject));
				mMBR.xmin	= (double)999999;
				mMBR.ymin	= (double)999999;
				mMBR.xmax	= (double)0;
				mMBR.ymax	= (double)0;

				for(int i = 0; i < (int)tempMEMOVECTOR.VECTOR.size(); i++)
				{
					gPoint.x = (double)tempMEMOVECTOR.VECTOR[i].x;
					gPoint.y = (double)tempMEMOVECTOR.VECTOR[i].y;

					if(gPoint.x <= 0 || gPoint.y <= 0)
						continue;

					frmSql->tMemoPoly.m_vPoints.push_back(gPoint);

					if(gPoint.x < mMBR.xmin)	mMBR.xmin = (double)gPoint.x;
					if(gPoint.x > mMBR.xmax)	mMBR.xmax = (double)gPoint.x;
					if(gPoint.y < mMBR.ymin)	mMBR.ymin = (double)gPoint.y;
					if(gPoint.y > mMBR.ymax)	mMBR.ymax = (double)gPoint.y;
				}

				frmSql->tMemoPoly.m_nNumPoints 	= frmSql->tMemoPoly.m_vPoints.size();
				frmSql->tMemoPoly.m_MBR        	= mMBR;
				frmSql->tMemoPoly.m_nID         = frmSql->m_vMEMOPOLY.size();
				frmSql->tMemoPoly.m_nShow		= 1;
				frmSql->tMemoPoly.label			= _asPoiKey;//frmSql->m_vALLMEMOINFO[i].POI_KEY;
				frmSql->m_vMEMOPOLY.push_back(frmSql->tMemoPoly);

				if(FileExists(asFileName))
					DeleteFile(asFileName);
			}
			else//220429//44250//MEMORYLEAK//
			{
				try{//TRY AGAIN
					DeleteFile(asFileName);
				}
				__finally{
					funcReadFileVectorLog(_asPoiKey);
				}
			}
		}
		else//220429//44250//MEMORYLEAK//
		{

        }
	}
}
//---------------------------------------------------------------------------

int __fastcall TfrmMemo::funcGetBinaryData(AnsiString _asPoiKey)
{
	/*2018.02.22*/if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

	AnsiString SqlQry;
	SQLCHAR m_cVal[3][50];
	SQLINTEGER m_nVal[3];
	MEMOVECTOR_STRUCT 	tempVECTOR;

	memset(&tempVECTOR, 0x00, sizeof(MEMOVECTOR_STRUCT));
	SQLBindCol(frmSql->m_hStmt, 1, SQL_C_CHAR, tempVECTOR.POI_KEY  , sizeof(tempVECTOR.POI_KEY ) , &m_nVal[0]);
	SQLBindCol(frmSql->m_hStmt, 2, SQL_C_LONG, &tempVECTOR.COUNT   , sizeof(tempVECTOR.COUNT)    , &m_nVal[1]);
	SQLBindCol(frmSql->m_hStmt, 3, SQL_C_LONG, &tempVECTOR.SIZE    , sizeof(tempVECTOR.SIZE)     , &m_nVal[2]);

	SqlQry = "SELECT POI_KEY, COUNT, SIZE, VECTOR FROM " + frmMain->TABLE_MEMOVECTOR + " WHERE POI_KEY = '" + _asPoiKey.Trim() + "'";

	SQLRETURN ret;
	ret = SQLPrepare(frmSql->m_hStmt,(SQLCHAR *)SqlQry.c_str(),SQL_NTS);
	ret = SQLExecute(frmSql->m_hStmt);

	SQLRETURN retcode;

	AnsiString result[3];
	char strtemp[50];
	int  nVectorCount;

	AnsiString path, dir, asFileName;
	dir = frmMain->ROOTPATH;

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		SQLCloseCursor(frmSql->m_hStmt);
	}
	else{
		try{//220429//
			asFileName 	= frmMain->ROOTPATH + "vector" + _asPoiKey + ".log";
			if(FileExists(asFileName))
				DeleteFile(asFileName);
		}
		__finally{
			BYTE *binaryPtr	= NULL;
			SQLINTEGER lenbin;
			int nGet;
			binaryPtr = new BYTE[MAX_CHUNK_SIZE];//1024->chunksize
			int chunksize, pos;

			FILE *wdatafile;
			wdatafile  = fopen(asFileName.c_str(), "wb+");

			//++++++++++++++++++++++++++++++++++++++++++++++++
			//220429//44250//MEMORYLEAK
			if(wdatafile == NULL)
			{
				SQLCloseCursor(frmSql->m_hStmt);
			}
			else
			{
			//++++++++++++++++++++++++++++++++++++++++++++++++
				int filesize;

				while(SQLFetch(frmSql->m_hStmt) != SQL_NO_DATA) {
					filesize = tempVECTOR.SIZE;
					nVectorCount = tempVECTOR.COUNT;

					chunksize = MAX_CHUNK_SIZE;
					memset(binaryPtr, 0x00, chunksize );//1024->chunksize

					while((retcode = SQLGetData(frmSql->m_hStmt, 4, SQL_C_BINARY, binaryPtr, chunksize, &lenbin)) != SQL_NO_DATA){
						if(lenbin == SQL_NULL_DATA) break;
						if(retcode == SQL_SUCCESS) nGet = lenbin;
						else nGet = chunksize;

						fwrite(binaryPtr, nGet, 1, wdatafile);
						memset(binaryPtr, 0x00, chunksize );//1024->chunksize

						Application->ProcessMessages() ;
						filesize = filesize - nGet;
						if(filesize <= 0) break;
					}

					Application->ProcessMessages() ;
				};
			}//else
			fclose(wdatafile);

			if(frmSql->m_hStmt) SQLCloseCursor(frmSql->m_hStmt);

			if(binaryPtr != NULL)
			{
				delete[] binaryPtr;
				binaryPtr = NULL;
			}
		}//__finally
	}

	return nVectorCount;
}
//---------------------------------------------------------------------------
int __fastcall TfrmMemo::func_readDataLength(AnsiString _qry)
{
	AnsiString mQry;
	int result = 0;

	SQLCHAR m_cVal[20];
	SQLINTEGER m_nVal;

	if(m_hStmtDataSize) SQLCloseCursor(m_hStmtDataSize);
	SQLBindCol(m_hStmtDataSize, 1, SQL_C_CHAR, m_cVal, sizeof(m_cVal), &m_nVal);

	mQry = _qry;

	SQLRETURN ret = SQLPrepare(m_hStmtDataSize,(SQLCHAR *)mQry.c_str(),SQL_NTS);
	ret = SQLExecute(m_hStmtDataSize);

	AnsiString tempSValue;
	char tempCValue[20];

	if((ret != SQL_SUCCESS) &&(ret != SQL_SUCCESS_WITH_INFO)  && (ret != SQL_NO_DATA) ){
		// 뒷정리
		SQLCloseCursor(m_hStmtDataSize);
	}
	else{
		memset(m_cVal,0x00,sizeof(m_cVal));
		tempSValue = "";
		while(SQLFetch(m_hStmtDataSize)!=SQL_NO_DATA) {
			memset(tempCValue, 0x00, sizeof(tempCValue) );
			memcpy(tempCValue, m_cVal, sizeof(tempCValue));
			tempSValue = tempCValue;
			if(tempSValue == "") tempSValue = "0";
			result = tempSValue.ToInt();
			memset(m_cVal,0x00,sizeof(m_cVal));
		};
		if(m_hStmtDataSize) SQLCloseCursor(m_hStmtDataSize);
	}

	if(m_hStmtDataSize) SQLCloseCursor(m_hStmtDataSize);

	return result;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemo::btnDownloadClick(TObject *Sender)
{
	//--------------------------------------------
	//251001//[REQ_25_SEP_Meeting]지적정보사업부//
	//가감대장(20)=>나중에 구축된 문서로 컬럼을 늘릴 수가 없어 사용하지 않는 DOC05_YN 컬럼 사용하기로 함 //
	int nCheckedCnt = 0;
	for(int i = 0; i < chkSelectList->Count; i++)
	{
		TCheckBox *chkSelectDC 		= (TCheckBox *)chkSelectList->Items[i];
		if(chkSelectDC != NULL)
		{
			if(chkSelectDC->Checked)
				nCheckedCnt++;
		}
	}
	if(nCheckedCnt == 0)
	{
		AnsiString strMsg = "다운로드할 파일을 선택해 주세요.";
		frmMsg->funcMessageDlg("선택 확인:", strMsg, 3);
		return;
	}
	//--------------------------------------------
	//251001//[REQ_25_SEP_Meeting]지적정보사업부//
	//--------------------------------------------
	if(m_asSaveFileDir.IsEmpty())
		m_asSaveFileDir = frmMain->DOWNLOADPATH;

	String  sDir = m_asSaveFileDir;
	int     nDownlaodCnt = 0;
	AnsiString  asNow = Now().FormatString("YYYYMMDD");
	if(SelectDirectory(L"파일을 저장할 폴더를 선택하세요.", "", sDir))
//	if (SelectDirectory(sDir, TSelectDirOpts() << sdAllowCreate << sdPerformCreate << sdPrompt, SELDIRHELP))
	{
//251001//[REQ_25_SEP_Meeting]//	if (SaveDialog1->Execute(Handle)){
		AnsiString asFileName 	= "";
		AnsiString asSrcFile 	= "";
		AnsiString asDstFile 	= "";
		AnsiString asExt 		= "";

//251001//[REQ_25_SEP_Meeting]//		m_asSaveFileDir = ExtractFilePath(SaveDialog1->FileName);

		for(int i = 0; i < chkSelectList->Count; i++)
		{
			TCheckBox *chkSelectDC 		= (TCheckBox *)chkSelectList->Items[i];
			if(chkSelectDC != NULL)
			{
				if(chkSelectDC->Checked)
				{
					asSrcFile	= m_vMEMOFILE[i].LOCAL_PATH_NAME;
//251001//[REQ_25_SEP_Meeting]//					asFileName	= ExtractFileName(asSrcFile);
					asExt 	= ExtractFileExt(asSrcFile);
					//asFileName	= ExtractFileName(asSrcFile);
					asFileName.sprintf("%s_%s(%03d)%s", AnsiString(edtMemoTitle->Text), asNow, i+1, asExt);
					asDstFile	= m_asSaveFileDir + asFileName;
					CopyFile(asSrcFile.c_str(), asDstFile.c_str(), false);
					nDownlaodCnt++;
				}
			}
		}

		if(nDownlaodCnt == nCheckedCnt)
		{
			AnsiString strMsg = "선택한 파일을 다운로드 완료 하였습니다.";
			frmMsg->funcMessageDlg("알림:", strMsg, 3);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemo::btnColorClick(TObject *Sender)
{
	if( ColorDialog1->Execute() )
	{
        COLORREF Clr = ColorDialog1->Color;
		//btnSetColor->Color = TColor(Clr);
		edtRed->Text = GetRValue(Clr);
		edtGreen->Text = GetGValue(Clr);
		edtBlue->Text = GetBValue(Clr);

		pnlColor->Color	= (TColor)RGB( edtRed->Text.ToInt(), edtGreen->Text.ToInt(), edtBlue->Text.ToInt() );
	}
}
//---------------------------------------------------------------------------


/*
fopen() 함수는 filename이 지정한 파일을 엽니다. mode 매개변수는 파일에 대해 요청된 액세스 유형을 지정하는 문자 스트링입니다. mode 변수는 선택적 키워드 매개변수가 뒤에 오는 하나의 위치 매개변수를 포함합니다.

참고: 프로그램이 SYSIFCOPT(*IFSIO) 또는 SYSIFCOPT(*IFS64IO)로 컴파일되고 fopen()이 통합 파일 시스템에서 파일을 작성하면 파일 소유자, 소유자의 그룹, 공용에 파일 읽기, 쓰기, 실행 권한이 부여됩니다.
가능한 위치 매개변수 값은 다음과 같습니다.
모드
설명
r
읽기 위해 텍스트 파일을 엽니다. 파일이 있어야 합니다.
w
쓰기 위해 텍스트 파일을 작성합니다. 주어진 파일이 있으면 논리 파일이 아닌 경우 해당 컨텐츠가 영구 삭제됩니다.
a
파일의 끝에서 쓰기 위해 추가 모드에서 텍스트 파일을 엽니다. fopen() 함수는 파일이 없고 논리 파일이 아니면 파일을 작성합니다.
r+
읽고 쓰기 위해 텍스트 파일을 엽니다. 파일이 있어야 합니다.
w+
읽고 쓰기 위해 텍스트 파일을 작성합니다. 주어진 파일이 있으면 논리 파일이 아닌 경우 해당 컨텐츠를 지웁니다.
a+
파일의 끝에서 읽거나 갱신하기 위해 추가 모드에서 텍스트 파일을 엽니다. fopen() 함수는 파일이 없으면 파일을 작성합니다.
rb
읽기 위해 2진 파일을 엽니다. 파일이 있어야 합니다.
wb
쓰기 위해 비어 있는 2진 파일을 작성합니다. 파일이 있으면 논리 파일이 아닌 경우 해당 컨텐츠를 지웁니다.
ab
파일의 끝에서 쓰기 위해 추가 모드에서 2진 파일을 엽니다. fopen 함수는 파일이 없으면 파일을 작성합니다.
r+b 또는 rb+
읽고 쓰기 위해 2진 파일을 엽니다. 파일이 있어야 합니다.
w+b 또는 wb+
읽고 쓰기 위해 비어 있는 2진 파일을 작성합니다. 파일이 있으면 논리 파일이 아닌 경우 해당 컨텐츠를 지웁니다.
a+b 또는 ab+
파일의 끝에서 쓰기 위해 추가 모드에서 2진 파일을 엽니다. fopen() 함수는 파일이 없으면 파일을 작성합니다.

*/
