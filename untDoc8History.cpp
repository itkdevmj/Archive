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
TfrmDoc8History *frmDoc8History;
//---------------------------------------------------------------------------
__fastcall TfrmDoc8History::TfrmDoc8History(TComponent* Owner)
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
		//shpWait->Pen->Color//
		//panWindowsMove->Color//
		this->panWindowsMove->Color			= (TColor)RGB(R, G, B);
		//pnlWaitT->Color//
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmDoc8History::FormCreate(TObject *Sender)
{
	funcCreateDoc8History();
}
//---------------------------------------------------------------------------

void __fastcall TfrmDoc8History::FormShow(TObject *Sender)
{
	funcRefreshShow();
}
//---------------------------------------------------------------------------

void __fastcall TfrmDoc8History::funcRefreshShow()
{
	frmSql->funcReadDocument08_History(frmResultList->eData == e08DataAIOCR ? true:false);
	funcInitDoc8History();
	funcDispDoc8History();
}
//---------------------------------------------------------------------------


void __fastcall TfrmDoc8History::btnCloseTypeBClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmDoc8History::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(frmUserLogList->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmDoc8History::sgDoc8HistoryGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign, TVAlignment &VAlign)
{
	HAlign = taCenter;
	VAlign = vtaCenter;
}
//---------------------------------------------------------------------------

//Create
void __fastcall TfrmDoc8History::funcCreateDoc8History()
{
	int nCol = 0;

	sgDoc8History->DefaultColWidth	= 150;

	sgDoc8History->ColCount  = 5;//
	sgDoc8History->RowCount  = 2;
	sgDoc8History->FixedRows = 1;
	sgDoc8History->FixedCols = 3;

//	sgDoc8History->Cells[nCol++][0]    = "부책/공유지";
//	sgDoc8History->Cells[nCol++][0]    = "항목";
//	sgDoc8History->Cells[nCol++][0]    = "셀 순번";
//	sgDoc8History->Cells[nCol++][0]    = "변경 전";
//	sgDoc8History->Cells[nCol++][0]    = "변경 후";

	sgDoc8History->ColWidths[nCol]	= 80;
	sgDoc8History->Cells[nCol++][0]	= "변경";
	sgDoc8History->ColWidths[nCol]	= 80;
	sgDoc8History->Cells[nCol++][0] = "항목";
	sgDoc8History->ColWidths[nCol]	= 50;
	sgDoc8History->Cells[nCol++][0] = "셀번호";
	sgDoc8History->Cells[nCol++][0] = "변경(전)";
	sgDoc8History->Cells[nCol++][0] = "변경(후)";

	::UpdateWindow(sgDoc8History->Handle);

//	for (int i = 0; i < 2; i++) {
//		for (int j = 0; j < sgDoc8History->ColCount; j++) {
//			sgDoc8History->Colors[j][i] = (TColor)RGB(221,232,254);//clInfoBk;
//		}
//	}
}
// ---------------------------------------------------------------------------

void __fastcall TfrmDoc8History::funcInitDoc8History()
{
	for (int i = 1; i < sgDoc8History->RowCount; i++) {
		sgDoc8History->Rows[i]->Clear();
	}

	sgDoc8History->RowCount = 2;

//	for (int i = 0; i < 1; i++)
//		for (int j = 0; j < sgDoc8History->ColCount; j++)
//			sgDoc8History->Colors[j][i] = (TColor)RGB(221,232,254);//clInfoBk;
}
// ---------------------------------------------------------------------------

void __fastcall TfrmDoc8History::funcDispDoc8History()
{
	AnsiString  asContents[14]	= {"지목", "지적", "과세1", "과세2", "연혁", "년월일", "사고", "주소", "성명", "년월일", "사고", "보합", "주소", "성명"};
	AnsiString  asStr	= "";
	AnsiString  asDate	= "";
	AnsiString  asName	= "";
	int nCol = 0;
	int nSize 		= (int)e08DataAlpha->m_ResultDoc08_HistoryStat.size();

//	//================================================
//	sgDoc8History->LockUpdate	= true;
//	//================================================

	sgDoc8History->RowCount	= nSize + 1;

	for (int i = 0; i < nSize; i++)
	{
		nCol 		= 0;

		asDate	= (char*)e08DataAlpha->m_ResultDoc08_HistoryStat[i].ACTION_DT;
		asName	= (char*)e08DataAlpha->m_ResultDoc08_HistoryStat[i].USERNAME;
		asStr	= asName + ", " + eFunc->funcChangeDateFormatString(2, asDate.c_str());
		sgDoc8History->Cells[nCol++][i+1] = asStr;

		if(e08DataAlpha->m_ResultDoc08_HistoryStat[i].KIND_TYPE == 1)//부책//
			sgDoc8History->Cells[nCol++][i+1] = asContents[e08DataAlpha->m_ResultDoc08_HistoryStat[i].CONTENTS_SEQ-1];
		else
			sgDoc8History->Cells[nCol++][i+1] = asContents[e08DataAlpha->m_ResultDoc08_HistoryStat[i].CONTENTS_SEQ+8];

		sgDoc8History->Cells[nCol++][i+1] = e08DataAlpha->m_ResultDoc08_HistoryStat[i].SEQ;
		sgDoc8History->Cells[nCol++][i+1] = (char*)e08DataAlpha->m_ResultDoc08_HistoryStat[i].BF_DATA;
		sgDoc8History->Cells[nCol++][i+1] = (char*)e08DataAlpha->m_ResultDoc08_HistoryStat[i].AF_DATA;
	}
}
//---------------------------------------------------------------------------

