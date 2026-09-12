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

TfrmRegist *frmRegist;
//---------------------------------------------------------------------------
__fastcall TfrmRegist::TfrmRegist(TComponent* Owner)
	: TForm(Owner)
{
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
	sgResult->ColWidths[nCol]	= 160;
	sgResult->Cells[nCol++][0] = "소유자";
	sgResult->ColWidths[nCol]	= 300;
	sgResult->Cells[nCol][0] = "사업명";

	::UpdateWindow(sgResult->Handle);

//	for (int i = 0; i < 1; i++)
//		for (int j = 0; j < sgResult->ColCount; j++)
//			sgResult->Colors[j][i] = (TColor)RGB(221,232,254);//clInfoBk;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRegist::FormShow(TObject *Sender)
{
//	this->Left = frmMain->Left + frmMain->Width;
//	this->Top  = frmMain->Top;

//	IMGCLOSEMouseLeave(NULL);

//	funcInitStringGrid();
//	funcDispStringGrid();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRegist::btnCloseTypeBMouseEnter(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TfrmRegist::btnCloseTypeBMouseLeave(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TfrmRegist::btnCloseTypeBMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmRegist::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(frmRegist->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmRegist::funcInitStringGrid()
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

void __fastcall TfrmRegist::funcDispStringGrid()
{
	int nCol = 0;
	AnsiString strTemp = "";

	int nSize = (int)frmMemoBatch->m_vRAWEXCELDATA.size();
	for(int i = 1; i < nSize + 1; i++)
	{
		nCol = 0;
		sgResult->Cells[nCol++][i] = frmMemoBatch->m_vRAWEXCELDATA[i].NO;
		sgResult->Cells[nCol++][i] = frmMemoBatch->m_vRAWEXCELDATA[i].UMD_NAME;
		sgResult->Cells[nCol++][i] = frmMemoBatch->m_vRAWEXCELDATA[i].RI_NAME;
		sgResult->Cells[nCol++][i] = frmMemoBatch->m_vRAWEXCELDATA[i].JIBUN_NAME;
		sgResult->Cells[nCol++][i] = frmMemoBatch->m_vRAWEXCELDATA[i].OWN_NAME;
		sgResult->Cells[nCol++][i] = frmMemoBatch->m_vRAWEXCELDATA[i].TITLE;
	}

	sgResult->RowCount = nSize + 1;
}
// ---------------------------------------------------------------------------

void __fastcall TfrmRegist::sgResultGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign, TVAlignment &VAlign)
{
	HAlign = taCenter;
	VAlign = vtaCenter;
}
//---------------------------------------------------------------------------

void __fastcall TfrmRegist::btnCloseTypeBClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

