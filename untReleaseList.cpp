//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#pragma warn -8004

TfrmReleaseList *frmReleaseList;
//---------------------------------------------------------------------------
__fastcall TfrmReleaseList::TfrmReleaseList(TComponent* Owner)
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
}
//---------------------------------------------------------------------------

void __fastcall TfrmReleaseList::FormCreate(TObject *Sender)
{
	int nStyle = GetWindowLong(this->Handle, GWL_STYLE);
	::SetWindowLong(this->Handle, GWL_STYLE, nStyle & (~WS_CAPTION ) | (WS_BORDER) & (~WS_DLGFRAME));
}
//---------------------------------------------------------------------------

void __fastcall TfrmReleaseList::FormShow(TObject *Sender)
{
	funcLoadButtonImage();

	lvResult->Clear();
	funcGetReleaseList();
}
//---------------------------------------------------------------------------

void __fastcall TfrmReleaseList::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(this->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------


void __fastcall TfrmReleaseList::btnCloseTypeBClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmReleaseList::funcGetReleaseList()
{
	AnsiString 	asIniFile = frmMain->ROOTPATH + "DATA\\_RELEASELIST_.ini";
	RELEASELIST_STRUCT vTemp;
	AnsiString 	asLine 		= "";
	AnsiString 	asSidoCode 	= "";
	AnsiString 	asSidoName 	= "";
	AnsiString 	asStr		= "";
	AnsiString  asFileName	= "";
	int 		nCount 	= 0;
	int			nPathIndex	= -1;
	RELEASEPATHLIST_STRUCT  tempVector;

	memset(&tempVector, 0x00, sizeof(RELEASEPATHLIST_STRUCT));

	m_vRELEASELIST.clear();
	m_vRELEASEPATHLIST.clear();

	if (FileExists(asIniFile))
		_iniList = new TIniFile(asIniFile);
	else
	{
		AnsiString strMsg = "업데이트 목록 파일이 존재하지 않습니다.\r\n(DATA\\_RELEASELIST_.INI)";
		frmMsg->funcMessageDlg("업데이트 확인:", strMsg, 3);
		Close();//191122//Application->Terminate();
		Application->ProcessMessages();
		return;
	}

	nCount = _iniList->ReadInteger(L"DEFAULT", L"COUNT", 0);

	for(int i = nCount; i > 0; i--)
	{
		asLine = _iniList->ReadString(L"RELEASE_LIST", IntToStr(i), "");

		TStringList *strList = new TStringList;
		strList->Delimiter = ',';
		//strList->DelimitedText = asLine;
		strList->DelimitedText = StringReplace(asLine, " ", "`", TReplaceFlags() << rfReplaceAll);
		strList->StrictDelimiter = true;//231019//[REF]http://www.borlandforum.com/impboard/impboard.dll?action=read&db=bcb_tip&no=989
		if(strList->Count == 4)//4)
		{
			memset(&vTemp, 0x00, sizeof(RELEASELIST_STRUCT));
//			vTemp.SEQ 	= (strList->Strings[0]).ToInt();
//			asStr = strList->Strings[1];
			vTemp.SEQ 	= i;
			asStr = strList->Strings[0];
			memcpy(vTemp.DATE, asStr.c_str(), asStr.Length());
			asStr = StringReplace(strList->Strings[1], "`", " ", TReplaceFlags() << rfReplaceAll);
			memcpy(vTemp.VERSION, asStr.c_str(), asStr.Length());
			asStr = StringReplace(strList->Strings[2], "`", " ", TReplaceFlags() << rfReplaceAll);
			memcpy(vTemp.CATEGORY, asStr.c_str(), asStr.Length());
			asStr = StringReplace(strList->Strings[3], "`", " ", TReplaceFlags() << rfReplaceAll);
			memcpy(vTemp.COMMENT, asStr.c_str(), asStr.Length());
			asFileName = frmMain->ROOTPATH + "RES\\RELEASE\\" + (char*)vTemp.VERSION + ".png";
			if(FileExists(asFileName))
			{
				nPathIndex++;
				vTemp.PATH_INDEX = nPathIndex;
				tempVector.LIST_INDEX	= (int)m_vRELEASELIST.size();
				tempVector.PATH_NAME = asFileName;
				m_vRELEASEPATHLIST.push_back(tempVector);

				memset(&tempVector, 0x00, sizeof(m_vRELEASEPATHLIST));
			}
			else
			{
				vTemp.PATH_INDEX = -1;
            }

			m_vRELEASELIST.push_back(vTemp);
		}
		else
		{
			AnsiString strMsg = "_RELASELIST_.ini 파일을 확인해주세요.";
			frmMsg->funcMessageDlg("파일 확인:", strMsg, 3);
			return;
		}
	}

	for(int i = 0; i < nCount; i++)
	{
		TListItem *pListItem = lvResult->Items->Add();

		pListItem->Caption = m_vRELEASELIST[i].SEQ;
		asStr 	= m_vRELEASELIST[i].DATE;
		pListItem->SubItems->Add(asStr);
		asStr 	= m_vRELEASELIST[i].VERSION;
		pListItem->SubItems->Add(asStr);
		asStr 	= m_vRELEASELIST[i].CATEGORY;
		pListItem->SubItems->Add(asStr);
		asStr 	= m_vRELEASELIST[i].COMMENT;
		pListItem->SubItems->Add(asStr);
		if(m_vRELEASELIST[i].PATH_INDEX > -1)
		{
			asStr	= "참고";
		}
		else
		{
			asStr	= "";
		}
		pListItem->SubItems->Add(asStr);
		asStr	= m_vRELEASELIST[i].PATH_INDEX;
		pListItem->SubItems->Add(asStr);
	}

	//이미지 목록 가져오기//
	m_nReleasePathCount	= (int)m_vRELEASEPATHLIST.size();
	if(m_nReleasePathCount == 0)
	{
		panCenter->Height	= 126;
		this->Height		= 159;
	}
	else
	{
		panCenter->Height	= 767;
		this->Height		= 800;

		m_nReleasePathIndex	= 0;

		lvResult->Selected = lvResult->Items->Item[0];
		lvResultClick(NULL);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmReleaseList::FormClose(TObject *Sender, TCloseAction &Action)
{
	funcDeleteButtonImage();

	IMGVIEW->Picture->Bitmap	= NULL;
	IMGVIEW->Picture			= NULL;
}
//---------------------------------------------------------------------------

//v1.0.0.9//250114//#RELEASE_LIST.SHOW.사용자선택(USER.INI > LREASE > SHOW)//
void __fastcall TfrmReleaseList::chkShowClick(TObject *Sender)
{
	frmMain->USERINI->WriteInteger(L"RELEASE", L"SHOW", 0);

	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmReleaseList::lvResultClick(TObject *Sender)
{
	TListItem *listitem;
	AnsiString asPathName 	= "";
	AnsiString asPath		= "";
	AnsiString asPathIndex	= "";
	int 		nPathIndex	= -1;

//	listitem 	= lvResult->Items->Item[lvResult->Selected->Index];
//	asPathIndex = (AnsiString)listitem->SubItems->Strings[3];
	nPathIndex = lvResult->Selected->SubItems->Strings[5].ToInt();

	if( nPathIndex != -1 )
	{
		m_nReleasePathIndex = nPathIndex;
		asPathName	= m_vRELEASEPATHLIST[m_nReleasePathIndex].PATH_NAME;

		TPngImage *imgPng = new TPngImage();
		Graphics::TBitmap *BITMAP_IMAGE;

		imgPng->LoadFromFile(asPathName);
		BITMAP_IMAGE = new Graphics::TBitmap();
		BITMAP_IMAGE->Assign(imgPng);
		delete imgPng;
		imgPng = NULL;

		IMGVIEW->Picture->Bitmap	= NULL;
		IMGVIEW->Picture			= NULL;
		IMGVIEW->Picture->Bitmap->Assign(BITMAP_IMAGE);
		IMGNOIMAGE->Visible	= false;
		IMGVIEW->Visible 	= true;

		lblCount->Caption	= "< " + FormatFloat("#,##0", m_nReleasePathIndex+1) + " / " + FormatFloat("#,##0", m_nReleasePathCount) + " >";
	}
//	else
//	{
//		IMGVIEW->Visible 	= false;
//		IMGNOIMAGE->Visible	= true;
//	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmReleaseList::funcLoadButtonImage()
{
	AnsiString filename = "";
	TPngImage *imgPng;

	//Button Image
	for(int i = 0; i < 2; i++)
	{
		imgPng = new TPngImage();
		filename = frmMain->IMAGEMEMOPATH + "btnPrev" + IntToStr(i+1) + ".png";
		imgPng->LoadFromFile(filename);
		BITMAP_BTN_PREV[i] = new Graphics::TBitmap();
		BITMAP_BTN_PREV[i]->Assign(imgPng);
		delete imgPng;
		imgPng = NULL;
		//
		imgPng = new TPngImage();
		filename = frmMain->IMAGEMEMOPATH + "btnNext" + IntToStr(i+1) + ".png";
		imgPng->LoadFromFile(filename);
		BITMAP_BTN_NEXT[i] = new Graphics::TBitmap();
		BITMAP_BTN_NEXT[i]->Assign(imgPng);
		delete imgPng;
		imgPng = NULL;
	}

	IMGPREV->Picture->Bitmap->Assign(BITMAP_BTN_PREV[0]);
	IMGNEXT->Picture->Bitmap->Assign(BITMAP_BTN_NEXT[0]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmReleaseList::funcDeleteButtonImage()
{
	for(int i = 0; i < 2; i++)
	{
		delete BITMAP_BTN_PREV[i];
		BITMAP_BTN_PREV[i] = NULL;
		delete BITMAP_BTN_NEXT[i];
		BITMAP_BTN_NEXT[i] = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmReleaseList::IMGPREVClick(TObject *Sender)
{
	if(m_nReleasePathIndex == 0)//First -> Last
		m_nReleasePathIndex = m_nReleasePathCount-1;
	else
		m_nReleasePathIndex--;

	int nListIndex	= m_vRELEASEPATHLIST[m_nReleasePathIndex].LIST_INDEX;
	lvResult->Selected = lvResult->Items->Item[nListIndex];
	lvResultClick(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TfrmReleaseList::IMGPREVMouseEnter(TObject *Sender)
{
	IMGPREV->Picture->Bitmap	= NULL;
	IMGPREV->Picture			= NULL;
	IMGPREV->Picture->Bitmap->Assign(BITMAP_BTN_PREV[1]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmReleaseList::IMGPREVMouseLeave(TObject *Sender)
{
	IMGPREV->Picture->Bitmap	= NULL;
	IMGPREV->Picture			= NULL;
	IMGPREV->Picture->Bitmap->Assign(BITMAP_BTN_PREV[0]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmReleaseList::IMGNEXTClick(TObject *Sender)
{
	if(m_nReleasePathIndex == m_nReleasePathCount-1)//Last -> First
		m_nReleasePathIndex = 0;
	else
		m_nReleasePathIndex++;

	int nListIndex	= m_vRELEASEPATHLIST[m_nReleasePathIndex].LIST_INDEX;
	lvResult->Selected = lvResult->Items->Item[nListIndex];
	lvResultClick(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TfrmReleaseList::IMGNEXTMouseEnter(TObject *Sender)
{
	IMGNEXT->Picture->Bitmap	= NULL;
	IMGNEXT->Picture			= NULL;
	IMGNEXT->Picture->Bitmap->Assign(BITMAP_BTN_NEXT[1]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmReleaseList::IMGNEXTMouseLeave(TObject *Sender)
{
	IMGNEXT->Picture->Bitmap	= NULL;
	IMGNEXT->Picture			= NULL;
	IMGNEXT->Picture->Bitmap->Assign(BITMAP_BTN_NEXT[0]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmReleaseList::funcGetImageList(AnsiString Dir)
{
//	m_vRELEASEPATHLIST.clear();
//
//	funcGetFileList(Dir);
}
//---------------------------------------------------------------------------

void __fastcall TfrmReleaseList::funcGetFileList(AnsiString Dir)
{
//	TSearchRec sr;
//	AnsiString iDir; //GetDirView()내에서만 사용할 패스변수 선언
//	int iAttributes 	= 0;
//	int nIndex 			= 0;
//	DWORD dwFileSize 	= 0;
//	char cFileSize[255];
//	AnsiString asPathName = "";
//	m_vRELEASEPATHLIST	tempVector;
//
//	memset(&tempVector, 0x00, sizeof(m_vRELEASEPATHLIST));
//
//	iAttributes |= faReadOnly * 0; //파일 옵션
//	iAttributes |= faHidden * 0;
//	iAttributes |= faSysFile * 0;
////	iAttributes |= faVolumeID * 0;
//	iAttributes |= faDirectory * 0;
//	iAttributes |= faArchive * 0;
//	iAttributes |= faAnyFile * 1;
//
//	iDir = Dir; //인자로 받아온 패스를 iDir에 저장
//	int len=iDir.Length();
//	if(iDir[len]=='\\')   //iDir의 마지막 문자가 '\\'인지 아닌지
//		iDir += "*.*";
//	else
//		iDir += "\\*.*";
//
//	if (FindFirst(iDir, iAttributes, sr) == 0) //찾는 파일이 있으면..
//	{
//		do{
//			if ((sr.Attr & faDirectory) == 0)//찾은 파일이 디렉토리가 아니면..
//			{
//				asPathName = Dir + "\\" + sr.Name;
//				strcpy(tempVector.PATH_NAME, asPathName.c_str());
//				m_vRELEASEPATHLIST.push_back(tempVector);
//			}
//			else{
//				if (sr.Name != "." && sr.Name != ".."){ // ".", ".." 두 디렉토리는 출력에서 제외시킴
//					AnsiString subDir;
//					subDir = Dir;
//					subDir = subDir+"\\";
//					subDir += sr.Name;
//					funcGetFileList(subDir);
//				}
//			}
//		}while(FindNext(sr) == 0); //다음 파일찾기, 다음찾은 파일이 없을때까지 do-while문 반복
//	}
//	FindClose(sr);
}
//---------------------------------------------------------------------------


