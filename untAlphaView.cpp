#pragma link "GR32_RangeBars"
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#pragma warn -8004



#define IsCTRLpressed()  ( (GetKeyState(VK_CONTROL) & (1 << (sizeof(SHORT)*8-1))) != 0 )


TfrmAlphaView *frmAlphaView;
//---------------------------------------------------------------------------
__fastcall TfrmAlphaView::TfrmAlphaView(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlphaView::FormCreate(TObject *Sender)
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
void __fastcall TfrmAlphaView::func_Trans()
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

void __fastcall TfrmAlphaView::WMMOVING(TMessage & msg)
{
	frmAlphaSub->Left   = this->Left + (this->Width - this->ClientWidth) / 2;
	frmAlphaSub->Top    = this->Top + panWindowsMove->Height + pnlTool->Height + 8;
}
//---------------------------------------------------------------------------


void __fastcall TfrmAlphaView::FormResize(TObject *Sender)
{
	lblAlphaT->Left		= (this->Width - lblAlphaT->Width) / 2;

	frmAlphaSub->Left   = this->Left + (this->Width - this->ClientWidth) / 2;
	frmAlphaSub->Top    = this->Top + panWindowsMove->Height + pnlTool->Height + 8;
	frmAlphaSub->Width  = this->pnlView->Width;
	frmAlphaSub->Height = this->pnlView->Height;// + 20;//24;

	//---
	if(frmAlphaSub->bFormShowed)
	{
		frmAlphaSub->IMGSCREEN2->Width	= frmAlphaSub->Width;
		frmAlphaSub->IMGSCREEN2->Height	= frmAlphaSub->Height;

		frmAlphaSub->m_dDocFactor	= frmAlphaSub->funcSetImageBaseScale();

		//===================================================
		//화면 중앙
		frmAlphaSub->m_nSrcCenterX   = (-frmAlphaSub->readImageWidth/2);
		frmAlphaSub->m_nSrcCenterY   = (frmAlphaSub->readImageHeight/2);
		frmAlphaSub->m_nSrcWidth   	= (int)((double)frmAlphaSub->IMGSCREEN2->Width/frmAlphaSub->m_dDocFactor);
		frmAlphaSub->m_nSrcHeight  	= (int)((double)frmAlphaSub->IMGSCREEN2->Height/frmAlphaSub->m_dDocFactor);
		frmAlphaSub->realLeft     	= (int)(frmAlphaSub->m_nSrcCenterX + (double)frmAlphaSub->m_nSrcWidth/2);
		frmAlphaSub->realTop      	= (int)(frmAlphaSub->m_nSrcCenterY - (double)frmAlphaSub->m_nSrcHeight/2);
		//===================================================


		frmAlphaSub->func_DrawImage();
		frmAlphaSub->mToolButtonState = DF_PANNING;
		frmAlphaSub->panMain->SetFocus();
	}
	//---

	func_Trans();
}
//---------------------------------------------------------------------------
void __fastcall TfrmAlphaView::FormShow(TObject *Sender)
{
	//-------------------------------------------------------------------
	int style = GetWindowLong(this->Handle, GWL_STYLE);
	style = style & ~WS_CAPTION;
	//style = style | WS_BORDER;
	//style = style & ~WS_BORDER;

	style = SetWindowLong(frmAlphaView->Handle, GWL_STYLE, (int)style);

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
	lblAlphaT->Caption = "지적문서통합관리시스템(도면 겹쳐보기 화면 1) - " + m_asTitleName;
	lblAlphaT->Left		= (this->Width - lblAlphaT->Width) / 2;

	if( !frmAlphaSub->Showing )
	{
		lblGammaV->Caption = "("+ IntToStr(gbGamma->Position) + ")";

		frmAlphaSub->Show();
		frmAlphaSub->panMain->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView::funcProcessAlpha()
{
	frmAlphaSub->m_nAlphaFactor = 6;
	frmAlphaSub->AlphaBlendValue = frmAlphaSub->dAlphaRate[frmAlphaSub->m_nAlphaFactor];
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView::funcProcessGamma()
{
	int nValue = gbGamma->Position;//CurrValue
	int nDiff = nValue - m_nGammaValue;
	if(nDiff == 0)
		return;

	m_nGammaValue = nValue;
	int nCalcValue = (nValue - gbGamma->Max / 2) * (10);

	frmAlphaSub->funcGammaImage(nCalcValue);
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView::FormClose(TObject *Sender, TCloseAction &Action)
{
	frmAlphaSub->bFormShowed = false;
	frmAlphaSub->bAdjusting  = false;
	gbGamma->Enabled 	= true;

	if(frmMain->mGetImageInfo1.m_DIB != NULL){
		FreeImage_Unload(frmMain->mGetImageInfo1.m_DIB);
		frmMain->mGetImageInfo1.m_DIB = NULL;
		memset(&frmMain->mGetImageInfo1, 0x00, sizeof(GetImageInfo));
    }

	if( frmAlphaSub->Showing )
		frmAlphaSub->Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView::gbGammaMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if(frmAlphaSub->bAdjusting)	 return;

	lblGammaV->Caption = "("+ IntToStr(gbGamma->Position) + ")";

	gbGamma->Enabled = false;

	frmAlphaSub->bAdjusting = true;

	frmAlphaSub->panMain->SetFocus();

	try{
//		frmMain->funcSetWaitWindows(true);
//		Application->ProcessMessages();
		//백남수
		frmAlphaSub->funcSetWaitWindows(true);
		/////////////////////////

		int nValue = gbGamma->Position;//CurrValue
		int nDiff = nValue - m_nGammaValue;
		if(nDiff == 0)
			return;

		//double dTemp = (double)1 + (double)(nValue - gbGamma->Max/2) * (double)0.1;
		double dTemp = (double)1 + (double)nDiff * (double)0.1;
		frmAlphaSub->funcGammaImage(dTemp);

		m_nGammaValue = nValue;
	}
	__finally{
		//Application->ProcessMessages();
		//frmMain->funcSetWaitWindows(false);
		//백남수
		frmAlphaSub->funcSetWaitWindows(false);
		/////////////////////////////

		frmAlphaSub->bAdjusting = false;

		gbGamma->Enabled = true;

	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmAlphaView::gbAlphaMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
//	int nValue = gbAlpha->Position;//CurrValue
//	int nDiff = nValue - m_nAlphaValue;
//	if(nDiff == 0)
//		return;
//
//	m_nAlphaValue = nValue;
//	int nCalcValue = nValue * 16;
//	if(nCalcValue == 256)
//		nCalcValue -= 1;
//
//	int nPercent = (int)((double)((double)(255 - nCalcValue) / (double)255 ) * (double)100);
//	lblAlphaV->Caption = "(" + IntToStr(nPercent) + "%)";
//	frmAlphaSub->AlphaBlendValue = nCalcValue;

	frmAlphaSub->m_nAlphaFactor = gbAlpha->Position;
	frmAlphaSub->AlphaBlendValue = frmAlphaSub->dAlphaRate[frmAlphaSub->m_nAlphaFactor];
	lblAlphaV->Caption = "(" + IntToStr((10 - frmAlphaSub->m_nAlphaFactor) * 10) + "%)";
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView::btnOrgClick(TObject *Sender)
{
	funcSetOrg();
}
//---------------------------------------------------------------------------
//1:1 크기로//
void __fastcall TfrmAlphaView::funcSetOrg()
{
	frmAlphaSub->m_dDocFactor   = 1;
	frmAlphaSub->funcRefreshView();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView::btnCloseTypeBClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	ReleaseCapture();

	SendMessage(frmAlphaView->Handle, WM_SYSCOMMAND, 0xf012, 0);

	frmAlphaSub->Left   = this->Left + (this->Width - this->ClientWidth) / 2;
	frmAlphaSub->Top    = this->Top + panWindowsMove->Height + pnlTool->Height + 8;
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView::imgResizeClick(TObject *Sender)
{
	FormResize(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView::btnZoomInClick(TObject *Sender)
{
	frmAlphaSub->funcZoomInView();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView::btnZoomOutClick(TObject *Sender)
{
	frmAlphaSub->funcZoomOutView();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView::btnRotateClick(TObject *Sender)
{
	if(Sender == btnRotate0)
		frmAlphaSub->funcRotateView(0);
	else if(Sender == btnRotateL)
		frmAlphaSub->funcRotateView(1);
	else if(Sender == btnRotateR)
		frmAlphaSub->funcRotateView(-1);
}
//---------------------------------------------------------------------------


void __fastcall TfrmAlphaView::edtAngleKeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN)
	{
		btnRotateSetClick(NULL);
	}
	else if(Key == '-')//특정기호 변경//250818//
	{
		if(_bMinusFlag)
			Key	= NULL;
		else
			_bMinusFlag	= true;
	}
	//else if(Key == 8 || Key == VK_DELETE)//backspace, delete
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView::edtAngleChange(TObject *Sender)
{
	if(edtAngle->Text.Pos("-") == 0)
		_bMinusFlag = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmAlphaView::btnRotateSetClick(TObject *Sender)
{
	//[TODO] Width, Height 값 조절에 대한 이슈가 생김//
	double dAngle = edtAngle->Text.ToDouble();
	frmAlphaSub->funcRotateView(dAngle);
}
//---------------------------------------------------------------------------

