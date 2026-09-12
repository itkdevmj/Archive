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

TfrmMemoRegist *frmMemoRegist;
//---------------------------------------------------------------------------
__fastcall TfrmMemoRegist::TfrmMemoRegist(TComponent* Owner)
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
		//panWindowsMove->Color//
		this->panWindowsMove->Color		= (TColor)RGB(R, G, B);
		//pnlWaitT->Color//
	}



	colorError = clRed;

	int nCol = 0; // M

	sgResult->FixedFont->Color = (TColor)RGB(111, 111, 111);
	sgResult->FixedColor       = (TColor)RGB(221,232,254);//clInfoBk;
	sgResult->DefaultColWidth = 80;

	sgResult->ColCount = 6;
	sgResult->RowCount = 2;
	sgResult->FixedRows = 1;
	sgResult->FixedCols = 0;

	sgResult->ColWidths[nCol]	= 40;
	sgResult->Cells[nCol++][0] = "No";
	sgResult->ColWidths[nCol]	= 80;
	sgResult->Cells[nCol++][0] = "읍면동";
	sgResult->ColWidths[nCol]	= 80;
	sgResult->Cells[nCol++][0] = "리";
	sgResult->ColWidths[nCol]	= 100;
	sgResult->Cells[nCol++][0] = "지번";
	sgResult->ColWidths[nCol]	= 200;
	sgResult->Cells[nCol++][0] = "소유자";
	sgResult->ColWidths[nCol]	= 240;
	sgResult->Cells[nCol][0] = "사업명";

	::UpdateWindow(sgResult->Handle);

//	for (int i = 0; i < 1; i++)
//		for (int j = 0; j < sgResult->ColCount; j++)
//			sgResult->Colors[j][i] = (TColor)RGB(221,232,254);//clInfoBk;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoRegist::FormShow(TObject *Sender)
{
	sgResult->FontColors[0][10] = clRed;;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoRegist::btnCloseTypeBMouseEnter(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoRegist::btnCloseTypeBMouseLeave(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoRegist::btnCloseTypeBMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoRegist::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(this->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoRegist::funcInitStringGrid()
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

void __fastcall TfrmMemoRegist::funcDispStringGrid()
{
	int nCol = 0;
	AnsiString strTemp = "";

	int nSize = (int)frmMemoBatch->m_vRAWEXCELDATA.size();
	for(int i = 1; i < nSize + 1; i++)
	{
		nCol = 0;
		sgResult->Cells[nCol++][i] = frmMemoBatch->m_vRAWEXCELDATA[i-1].NO;
		sgResult->Cells[nCol++][i] = frmMemoBatch->m_vRAWEXCELDATA[i-1].UMD_NAME;
		sgResult->Cells[nCol++][i] = frmMemoBatch->m_vRAWEXCELDATA[i-1].RI_NAME;
		sgResult->Cells[nCol++][i] = frmMemoBatch->m_vRAWEXCELDATA[i-1].JIBUN_NAME;
		sgResult->Cells[nCol++][i] = frmMemoBatch->m_vRAWEXCELDATA[i-1].OWN_NAME;
		sgResult->Cells[nCol++][i] = frmMemoBatch->m_vRAWEXCELDATA[i-1].TITLE;
	}

	sgResult->RowCount = nSize + 1;
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMemoRegist::sgResultGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign, TVAlignment &VAlign)
{
	HAlign = taCenter;
	VAlign = vtaCenter;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoRegist::btnCloseTypeBClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

