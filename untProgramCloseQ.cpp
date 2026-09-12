//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"

#pragma warn -8004

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmProgramCloseQ *frmProgramCloseQ;
//---------------------------------------------------------------------------
__fastcall TfrmProgramCloseQ::TfrmProgramCloseQ(TComponent* Owner)
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
void __fastcall TfrmProgramCloseQ::btnCloseClick(TObject *Sender)
{
	IMGCANCELClick(IMGCANCEL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmProgramCloseQ::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(frmProgramCloseQ->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmProgramCloseQ::FormShow(TObject *Sender)
{
	funcLoadButtonImage();

	frmProgramCloseQ->Tag = 1;

	if(CountLabel->Visible)//210806//자동로그아웃//
	{
		imgBG->Picture->Bitmap->Assign(BITMAP_BG[1]);
	}
	else//선택에의한종료//
	{
		imgBG->Picture->Bitmap->Assign(BITMAP_BG[0]);
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmProgramCloseQ::Timer1Timer(TObject *Sender)
{
	CountLabel->Caption = "[" + IntToStr(m_bCount) + "]" ;
	if(m_bCount == 0){
		Timer1->Enabled = false;
		CountLabel->Visible = false;
		CountMessageLabel->Visible = false;
		Close();
	}
	m_bCount--;
}
//---------------------------------------------------------------------------

void __fastcall TfrmProgramCloseQ::funcLoadButtonImage()
{
	AnsiString asPath = frmMain->ROOTPATH + "RES\\MAIN\\";
	AnsiString filename = "";
	TPngImage *imgPng;
	TJPEGImage *imgJpg;

	//Button Image
	for(int i = 0; i < 2; i++)
	{
		imgPng = new TPngImage();
		filename = asPath + "btnYes" + IntToStr(i) + ".png";
		imgPng->LoadFromFile(filename);
		BITMAP_BTN_YES[i] = new Graphics::TBitmap();
		BITMAP_BTN_YES[i]->Assign(imgPng);
		delete imgPng;
		imgPng = NULL;
		//
		imgPng = new TPngImage();
		filename = asPath + "btnCancel" + IntToStr(i) + ".png";
		imgPng->LoadFromFile(filename);
		BITMAP_BTN_CANCEL[i] = new Graphics::TBitmap();
		BITMAP_BTN_CANCEL[i]->Assign(imgPng);
		delete imgPng;
		imgPng = NULL;
		//210806//
		imgJpg = new TJPEGImage();
		filename = asPath + "bg_programcloseQ" + IntToStr(i) + ".jpg";
		imgJpg->LoadFromFile(filename);
		BITMAP_BG[i] = new Graphics::TBitmap();
		BITMAP_BG[i]->Assign(imgJpg);
		delete imgJpg;
		imgJpg = NULL;
	}

	IMGYES->Picture->Bitmap->Assign(BITMAP_BTN_YES[0]);
	IMGCANCEL->Picture->Bitmap->Assign(BITMAP_BTN_CANCEL[0]);
	imgBG->Picture->Bitmap->Assign(BITMAP_BG[0]);//210806//
}
//---------------------------------------------------------------------------

void __fastcall TfrmProgramCloseQ::funcDeleteButtonImage()
{
	for(int i = 0; i < 2; i++)
	{
		delete BITMAP_BTN_YES[i];
		BITMAP_BTN_YES[i] = NULL;
		delete BITMAP_BTN_CANCEL[i];
		BITMAP_BTN_CANCEL[i] = NULL;
		delete BITMAP_BG[i];
		BITMAP_BG[i] = NULL;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmProgramCloseQ::IMGYESMouseEnter(TObject *Sender)
{
	IMGYES->Picture->Bitmap->Handle  = NULL;
	IMGYES->Picture                  = NULL;
	IMGYES->Picture->Bitmap->Assign(BITMAP_BTN_YES[1]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmProgramCloseQ::IMGYESMouseLeave(TObject *Sender)
{
	IMGYES->Picture->Bitmap->Handle  = NULL;
	IMGYES->Picture                  = NULL;
	IMGYES->Picture->Bitmap->Assign(BITMAP_BTN_YES[0]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmProgramCloseQ::IMGYESClick(TObject *Sender)
{
	frmProgramCloseQ->Tag = 1;
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmProgramCloseQ::IMGCANCELMouseEnter(TObject *Sender)
{
	IMGCANCEL->Picture->Bitmap->Handle  = NULL;
	IMGCANCEL->Picture                  = NULL;
	IMGCANCEL->Picture->Bitmap->Assign(BITMAP_BTN_CANCEL[1]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmProgramCloseQ::IMGCANCELMouseLeave(TObject *Sender)
{
	IMGCANCEL->Picture->Bitmap->Handle  = NULL;
	IMGCANCEL->Picture                  = NULL;
	IMGCANCEL->Picture->Bitmap->Assign(BITMAP_BTN_CANCEL[0]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmProgramCloseQ::IMGCANCELClick(TObject *Sender)
{
	frmProgramCloseQ->Tag = 0;
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmProgramCloseQ::FormClose(TObject *Sender, TCloseAction &Action)
{
	funcDeleteButtonImage();
}
//---------------------------------------------------------------------------

void __fastcall TfrmProgramCloseQ::FormKeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN)
	{
		IMGYESClick(IMGYES);
	}
}
//---------------------------------------------------------------------------

