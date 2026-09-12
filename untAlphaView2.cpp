#pragma link "GR32_RangeBars"
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#pragma warn -8004

TfrmAlphaView2 *frmAlphaView2;
//---------------------------------------------------------------------------
__fastcall TfrmAlphaView2::TfrmAlphaView2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlphaView2::FormCreate(TObject *Sender)
{
//	int style = GetWindowLong(this->Handle, GWL_STYLE);
//	style = style & ~WS_CAPTION;
//	//style = style | WS_BORDER;
//	//style = style & ~WS_BORDER;
//
//	style = SetWindowLong(this->Handle, GWL_STYLE, (int)style);
//
	func_Trans();
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlphaView2::func_Trans()
{
	//HRGN : 윈도우의 GDI Handle
	//CombineRgn : HRGN 핸들을 조합하는 것. 원하는 모양을 잘라냈을 때의 핸들.(실제로 적용은 하지 않습니다.)
	//SetWindowRgn : 잘라냈을때의 핸들을 윈도우에 적용시키는 것.
	HRGN hRegion,hRegion1;

	hRegion1 = CreateRectRgn(0, 0, Width, Height);
	//hRegion  = CreateRectRgn(4, 30 + pnlTool->Height, Width - 2, Height - 2);
	hRegion  = CreateRectRgn(8, 30 + pnlTool->Height, Width - 8, Height - 8);

	CombineRgn(hRegion, hRegion1, hRegion, RGN_DIFF);

	SetWindowRgn(Handle, hRegion, True);
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView2::WMMOVING(TMessage & msg)
{
	frmAlphaSub2->Left   = this->Left + (this->Width - this->ClientWidth) / 2;
	frmAlphaSub2->Top    = this->Top + panWindowsMove->Height + pnlTool->Height + 8;
}
//---------------------------------------------------------------------------


void __fastcall TfrmAlphaView2::FormResize(TObject *Sender)
{
	lblAlphaT->Left		 = (this->Width - lblAlphaT->Width) / 2;

	frmAlphaSub2->Left   = this->Left + (this->Width - this->ClientWidth) / 2;
	frmAlphaSub2->Top    = this->Top + panWindowsMove->Height + pnlTool->Height + 8;
	frmAlphaSub2->Width  = this->pnlView->Width;
	frmAlphaSub2->Height = this->pnlView->Height;// + 20;//24;

	//---
	if(frmAlphaSub2->bFormShowed)
	{
		frmAlphaSub2->IMGSCREEN2->Width		= frmAlphaSub2->Width;
		frmAlphaSub2->IMGSCREEN2->Height	= frmAlphaSub2->Height;

		frmAlphaSub2->m_dDocFactor	= frmAlphaSub2->funcSetImageBaseScale();

		//===================================================
		//화면 중앙
		frmAlphaSub2->m_nSrcCenterX   = (-frmAlphaSub2->readImageWidth/2);
		frmAlphaSub2->m_nSrcCenterY   = (frmAlphaSub2->readImageHeight/2);
		frmAlphaSub2->m_nSrcWidth   	= (int)((double)frmAlphaSub2->IMGSCREEN2->Width/frmAlphaSub2->m_dDocFactor);
		frmAlphaSub2->m_nSrcHeight  	= (int)((double)frmAlphaSub2->IMGSCREEN2->Height/frmAlphaSub2->m_dDocFactor);
		frmAlphaSub2->realLeft     	= (int)(frmAlphaSub2->m_nSrcCenterX + (double)frmAlphaSub2->m_nSrcWidth/2);
		frmAlphaSub2->realTop      	= (int)(frmAlphaSub2->m_nSrcCenterY - (double)frmAlphaSub2->m_nSrcHeight/2);
		//===================================================


		frmAlphaSub2->func_DrawImage();
		frmAlphaSub2->mToolButtonState = DF_PANNING;
		frmAlphaSub2->panMain->SetFocus();
	}
	//---

	func_Trans();
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlphaView2::FormShow(TObject *Sender)
{
	//-------------------------------------------------------------------
	int style = GetWindowLong(this->Handle, GWL_STYLE);
	style = style & ~WS_CAPTION;
	//style = style | WS_BORDER;
	//style = style & ~WS_BORDER;

	style = SetWindowLong(frmAlphaView2->Handle, GWL_STYLE, (int)style);

	func_Trans();
	//-------------------------------------------------------------------


	//	tagPOINT tpPosition;
	GetCursorPos(&tpPosition);

	MONITORINFOEXW MonitorInfoEx;
	MonitorInfoEx.cbSize = sizeof(MONITORINFOEXW);
	GetMonitorInfoW(Screen->Monitors[0]->Handle, &MonitorInfoEx);

	int nMonitorCount = Screen->MonitorCount;
	if(nMonitorCount == 1)
	{
		this->Left = 0;
	}
	else
	{
		MONITORINFOEXW MonitorInfoEx;
		MonitorInfoEx.cbSize = sizeof(MONITORINFOEXW);
		GetMonitorInfoW(Screen->Monitors[1]->Handle, &MonitorInfoEx);

		if(tpPosition.x < 0)
		{
			if(Screen->Monitors[0]->Left < 0)
				this->Left = Screen->Monitors[0]->Left;
			else if(Screen->Monitors[1]->Left < 0)
				this->Left = Screen->Monitors[1]->Left;
		}
		else if(tpPosition.x > 0)
		{
			if(tpPosition.x < Screen->Monitors[0]->Left)
				this->Left = Screen->Monitors[1]->Left;
			else if(tpPosition.x < Screen->Monitors[1]->Left)
				this->Left = Screen->Monitors[0]->Left;
			else if(tpPosition.x > Screen->Monitors[0]->Left + Screen->Monitors[0]->Width)
				this->Left = Screen->Monitors[1]->Left;
			else if(tpPosition.x > Screen->Monitors[1]->Left + Screen->Monitors[1]->Width)
				this->Left = Screen->Monitors[0]->Left;
		}
	}
	this->Top  = 0;


	//----------------------
	lblAlphaT->Caption = "지적문서통합관리시스템(도면 겹쳐보기 화면 2) - " + m_asTitleName;
	lblAlphaT->Left		= (this->Width - lblAlphaT->Width) / 2;

	if( !frmAlphaSub2->Showing )
	{
		lblGammaV->Caption = "("+ IntToStr(gbGamma->Position) + ")";

		frmAlphaSub2->Show();
		frmAlphaSub2->panMain->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView2::funcProcessAlpha()
{
	frmAlphaSub2->m_nAlphaFactor = 6;
	frmAlphaSub2->AlphaBlendValue = frmAlphaSub2->dAlphaRate[frmAlphaSub2->m_nAlphaFactor];
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView2::funcProcessGamma()
{
	int nValue = gbGamma->Position;//CurrValue
	int nDiff = nValue - m_nGammaValue;
	if(nDiff == 0)
		return;

	m_nGammaValue = nValue;
	int nCalcValue = (nValue - gbGamma->Max / 2) * (10);

	frmAlphaSub2->funcGammaImage(nCalcValue);
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView2::FormClose(TObject *Sender, TCloseAction &Action)
{
	frmAlphaSub2->bFormShowed = false;
	frmAlphaSub2->bAdjusting  = false;
	gbGamma->Enabled 	= true;

	if( frmAlphaSub2->Showing )
		frmAlphaSub2->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView2::gbGammaMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if(frmAlphaSub2->bAdjusting)	 return;

	lblGammaV->Caption = "("+ IntToStr(gbGamma->Position) + ")";

	gbGamma->Enabled = false;

	frmAlphaSub2->bAdjusting = true;

	frmAlphaSub2->panMain->SetFocus();

	try{
		//frmMain->funcSetWaitWindows(true);
		//Application->ProcessMessages();
		//백남수
		frmAlphaSub2->funcSetWaitWindows(true);
		//////////////////////////

		int nValue = gbGamma->Position;//CurrValue
		int nDiff = nValue - m_nGammaValue;
		if(nDiff == 0)
			return;

		//double dTemp = (double)1 + (double)(nValue - gbGamma->Max/2) * (double)0.1;
		double dTemp = (double)1 + (double)nDiff * (double)0.1;
		frmAlphaSub2->funcGammaImage(dTemp);

		m_nGammaValue = nValue;
	}
	__finally{
		//Application->ProcessMessages();
		//frmMain->funcSetWaitWindows(false);
		//백남수
		frmAlphaSub2->funcSetWaitWindows(false);
		////////////////////////////////

		frmAlphaSub2->bAdjusting = false;

		gbGamma->Enabled = true;

	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmAlphaView2::gbAlphaMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	frmAlphaSub2->m_nAlphaFactor = gbAlpha->Position;
	frmAlphaSub2->AlphaBlendValue = frmAlphaSub2->dAlphaRate[frmAlphaSub2->m_nAlphaFactor];
	lblAlphaV->Caption = "(" + IntToStr((10 - frmAlphaSub2->m_nAlphaFactor) * 10) + "%)";
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView2::btnOrgClick(TObject *Sender)
{
	funcSetOrg();
}
//---------------------------------------------------------------------------
//1:1 크기로//
void __fastcall TfrmAlphaView2::funcSetOrg()
{
	frmAlphaSub2->m_dDocFactor   = 1;
	frmAlphaSub2->funcRefreshView();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView2::btnCloseTypeBClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView2::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	ReleaseCapture();

	SendMessage(frmAlphaView2->Handle, WM_SYSCOMMAND, 0xf012, 0);

	frmAlphaSub2->Left   = this->Left + (this->Width - this->ClientWidth) / 2;
	frmAlphaSub2->Top    = this->Top + panWindowsMove->Height + pnlTool->Height + 8;
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView2::imgResizeClick(TObject *Sender)
{
	FormResize(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView2::btnZoomInClick(TObject *Sender)
{
	frmAlphaSub2->funcZoomInView();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView2::btnZoomOutClick(TObject *Sender)
{
	frmAlphaSub2->funcZoomOutView();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView2::btnRotateClick(TObject *Sender)
{
	if(Sender == btnRotate0)
		frmAlphaSub2->funcRotateView(0);
	else if(Sender == btnRotateL)
		frmAlphaSub2->funcRotateView(1);
	else if(Sender == btnRotateR)
		frmAlphaSub2->funcRotateView(-1);
}
//---------------------------------------------------------------------------

