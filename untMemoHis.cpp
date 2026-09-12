//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"

#pragma warn -8004

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMemoHis *frmMemoHis;
//---------------------------------------------------------------------------
__fastcall TfrmMemoHis::TfrmMemoHis(TComponent* Owner)
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
void __fastcall TfrmMemoHis::FormCreate(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoHis::FormShow(TObject *Sender)
{
	this->Left = frmMain->Left + frmMemo->Left + frmMemo->Width;
	this->Top  = frmMain->Top + frmMain->Height / 2 - this->Height / 2 - 20;

	funcClearForm();

	DisplayDBGrid();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoHis::funcClearForm()
{
//	//MemoInfoHis
//	m_vMEMOINFOHIS.clear();

    InitDBGrid();

	lblPoiName->Caption     = "";
	lblMemoTitle->Caption	= "";
	lblCount->Caption		= "";
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoHis::FormClose(TObject *Sender, TCloseAction &Action)
{
	funcClearForm();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoHis::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(frmMemoHis->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMemoHis::btnCloseTypeBClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMemoHis::InitDBGrid()
{
	int nCol = 0;

	this->sgMemoHis->RowCount = 2;
	this->sgMemoHis->ColCount = 6;//201109//3->6

	this->sgMemoHis->RowHeights[0] = 22;
	this->sgMemoHis->ColWidths[nCol++] = 80; // 작성일
	this->sgMemoHis->ColWidths[nCol++] = 80; // 작성자
	this->sgMemoHis->ColWidths[nCol++] = 300; // 메모내용
	this->sgMemoHis->ColWidths[nCol++] = 40; // LINECOLOR
	this->sgMemoHis->ColWidths[nCol++] = 70; // GAGAM_X
	this->sgMemoHis->ColWidths[nCol++] = 70; // GAGAM_Y

	// Cells[col][row]
	nCol = 0;
	this->sgMemoHis->Cells[nCol++][0] = L"작성일";
	this->sgMemoHis->Cells[nCol++][0] = L"작성자";
	this->sgMemoHis->Cells[nCol++][0] = L"메모내용";
	this->sgMemoHis->Cells[nCol++][0] = L"컬러";
	this->sgMemoHis->Cells[nCol++][0] = L"가감값(X)";
	this->sgMemoHis->Cells[nCol++][0] = L"가감값(Y)";

	for (int i = 1; i < this->sgMemoHis->RowCount; i++){
		for (int j = 0; j < this->sgMemoHis->ColCount; j++){
			this->sgMemoHis->Cells[j][i] = L"";
		}
	}

	this->sgMemoHis->RowCount = 2;
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMemoHis::DisplayDBGrid()
{
	AnsiString asStr 	= "";
	int nCol 			= 0;
	int nSize 			= (int)frmMemo->m_vMEMOINFOHIS.size();

	if(nSize > 0)
	{
		lblPoiName->Caption 	= "[위치:" + AnsiString(frmMemo->m_vMEMOINFO[0].POI_NAME) + "]";
		lblMemoTitle->Caption 	= "[제목:" + AnsiString(frmMemo->m_vMEMOINFO[0].TITLE) + "]";
	}
	for (int i = 0; i < nSize; i++)
	{
		nCol = 0;
		asStr = frmMemo->m_vMEMOINFOHIS[i].WRITE_DT;
		if(asStr.Length() == 14)
		{
			asStr 	= asStr.SubString(1, 4) + "-" + asStr.SubString(5, 2) + "-" + asStr.SubString(7, 2) + " " + asStr.SubString(9, 2) + ":" + asStr.SubString(11, 2) + ":" + asStr.SubString(13, 2);
		}
		this->sgMemoHis->Cells[nCol++][i + 1] = asStr;
		this->sgMemoHis->Cells[nCol++][i + 1] = frmUserManagement->funcReadUserName(AnsiString((char*)frmMemo->m_vMEMOINFOHIS[i].WRITE_ID));
		this->sgMemoHis->Cells[nCol++][i + 1] = frmMemo->m_vMEMOINFOHIS[i].MEMO;
		//201109//
		this->sgMemoHis->Cells[nCol++][i + 1] = "";
		this->sgMemoHis->Cells[nCol++][i + 1] = (char*)frmMemo->m_vMEMOINFOHIS[i].GAGAM_X;
		this->sgMemoHis->Cells[nCol++][i + 1] = (char*)frmMemo->m_vMEMOINFOHIS[i].GAGAM_Y;
		//---
		this->sgMemoHis->RowCount++;
	}

	this->sgMemoHis->RowCount--;

	if (this->sgMemoHis->RowCount > 1) {
		sgMemoHis->SetFocus();
		sgMemoHis->Row = 1;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TfrmMemoHis::sgMemoHisDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
	TStringGrid  *pDBGrid   = (TStringGrid *)Sender;
	TCanvas  *pCanvas   = pDBGrid->Canvas;

	//--------------------------------------------------------------------------
	AnsiString strValue = "";

	strValue = pDBGrid->Cells[ACol][ARow];

	int X = 0;
	int Y = 0;

	/*if( ARow == 0){
		::SetTextAlign( pCanvas->Handle, TA_CENTER );
		X = Rect.Left + ((Rect.Right - Rect.Left)/2);
	}
	else{
		::SetTextAlign( pCanvas->Handle, TA_LEFT );
		X = Rect.Left + 5;
	}*/

	::SetTextAlign( pCanvas->Handle, TA_CENTER );
	X = Rect.Left + ((Rect.Right - Rect.Left)/2);
	//Y = Rect.Top  + ((Rect.Bottom - Rect.Top - text height)/2);
	//--------------------------------------------------------------------------
	TColor crOldBrushColor = pCanvas->Brush->Color;
	TColor crOldPenColor   = pCanvas->Pen->Color;
 	//--------------------------------------------------------------------------

	if(ARow == 0 ){
		pCanvas->Brush->Color = clActiveCaption;//(TColor)RGB( 17, 136, 255 );
		pCanvas->Pen->Color   = (TColor)RGB( 255, 255, 255 );
		pCanvas->Font->Color  = (TColor)RGB( 255, 255, 255 );
	}
	else
	{
		if(ACol == 3)
		{
			int linecolor	= frmMemo->m_vMEMOINFOHIS[ARow-1].LINECOLOR;

			if(linecolor > 0)
			{
				int lineR 	= GetRValue(linecolor);
				int lineG 	= GetGValue(linecolor);
				int lineB 	= GetBValue(linecolor);

				pCanvas->Brush->Color	=	(TColor)RGB( lineR, lineG, lineB );
				//pCanvas->FillRect(Rect);
			}
		}
		else
		{
			//org//
			if( State.Contains(Grids::gdSelected) )
			{
				pCanvas->Brush->Color = (TColor)RGB( 221, 238, 255 );
				pCanvas->Pen->Color   = (TColor)RGB( 255, 255, 255 );
				pCanvas->Font->Color  = (TColor)RGB( 0, 0, 0 );
			}
			else
			{
				pCanvas->Brush->Color = (TColor)RGB( 255, 255, 255 );
				pCanvas->Pen->Color   = (TColor)RGB( 255, 255, 255 );
			}
		}
	}


	pCanvas->FillRect( Rect );

	pCanvas->Brush->Color = crOldBrushColor;
	pCanvas->Pen->Color   = crOldPenColor;
	//--------------------------------------------------------------------------

	TBrushStyle nOldBrushStyle = pCanvas->Brush->Style;
	int OldBkMode = ::SetBkMode( pCanvas->Handle, TRANSPARENT );
	pCanvas->Brush->Style = bsClear;
	//--------------------------------------------------------------------------

	if(ARow == 0)
	{
		pCanvas->TextOut( X, Rect.Top + 4,  strValue );
	}
	else
	{
		if( ACol == 0 && strValue.Length() >= 10)
		{
			AnsiString asStrPrev;
			AnsiString asStrNext;
			int nLength = strValue.Length();
			if(nLength >= 10)
			{
				asStrPrev = strValue.SubString(1, 10);
				asStrNext = strValue.SubString(11, nLength - 10);
				pCanvas->Font->Size = 8;
				pCanvas->TextOut( X, Rect.Top + 8, asStrPrev );
				pCanvas->TextOut( X, Rect.Top + 20, asStrNext );
			}
		}
		else if(ACol == 1)
		{
			pCanvas->TextOut( X, Rect.Top + 14, strValue );
        }
		else if(ACol == 2 && strValue.Length() > 80)
		{
			AnsiString asStr1;
			AnsiString asStr2;
			AnsiString asStr3;
			int nLength = strValue.Length();
			int nMidIndex = 78;//nLength / 2;
			if( (strValue.c_str()[nMidIndex] & 0x80) == 0x80 ) {// - nIndex~nIndex+1까지 2바이트가 한글// - 한글 일 때 처리
				nMidIndex += 2; // 한글문자 다음 바이트로 넘김
			}

			pCanvas->Font->Size = 8;
			asStr1 = strValue.SubString(1, nMidIndex);
			if(nLength < 160)
			{
				asStr2 = strValue.SubString(nMidIndex + 1, nLength - nMidIndex);
				pCanvas->TextOut( X, Rect.Top + 1,  asStr1 );
				pCanvas->TextOut( X, Rect.Top + 13, asStr2 );
			}
			else
			{
				asStr2 = strValue.SubString(nMidIndex + 1, nMidIndex);
				asStr3 = strValue.SubString(nMidIndex*2 + 1, nLength - nMidIndex*2);
				pCanvas->TextOut( X, Rect.Top + 1,  asStr1 );
				pCanvas->TextOut( X, Rect.Top + 13, asStr2 );
				pCanvas->TextOut( X, Rect.Top + 25, asStr3 );
			}
		}
		else
		{
			pCanvas->TextOut( X, Rect.Top + 14, strValue );
		}
	}

	//--------------------------------------------------------------------------
	pCanvas->Brush->Style = nOldBrushStyle;
	::SetBkMode( pCanvas->Handle, OldBkMode );
}
//---------------------------------------------------------------------------

