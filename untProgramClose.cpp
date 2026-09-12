//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmProgramClose *frmProgramClose;
//---------------------------------------------------------------------------
__fastcall TfrmProgramClose::TfrmProgramClose(TComponent* Owner)
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

void __fastcall TfrmProgramClose::FormShow(TObject *Sender)
{
	frmProgramClose->Caption = "Saving program informaion";
}
//---------------------------------------------------------------------------
void __fastcall TfrmProgramClose::FormClose(TObject *Sender, TCloseAction &Action)
{
	for( int i=0;i<12; i++)
	{
		Application->ProcessMessages();
		::Sleep(100);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmProgramClose::tmr_ProgramCloseTimer(TObject *Sender)
{
	lbl_State->Caption = "Saving program informaion...";

	this->tmr_ProgramClose->Enabled = false;

	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmProgramClose::btnCloseClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmProgramClose::btnCloseTypeBClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmProgramClose::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(frmProgramClose->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------

