//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"
//#include "untHanja.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SHDocVw_OCX"
#pragma resource "*.dfm"
TfrmHanja *frmHanja;
//---------------------------------------------------------------------------
__fastcall TfrmHanja::TfrmHanja(TComponent* Owner)
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
		//pnlWaitT->Color//
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmHanja::FormShow(TObject *Sender)
{
	//181217//this->WebBrowser->Silent = true;//Silent : 웹브라우저에서 대화 상자를 표시할 수 있는지 여부를 지정.
	//if (this->WebBrowser->Left != -506)
	//{
		wchar_t szWC[256]   = {0, };
		AnsiString URL;
		URL    = "https://hanja.dict.naver.com/";
		URL.WideChar(szWC, 256);
		/*this->WebBrowser->Left   = -520;
		this->WebBrowser->Top    = -198;
		this->WebBrowser->Width  = 1011;
		this->WebBrowser->Height  = 500;*/
		this->WebBrowser->Navigate(szWC,NULL,NULL,NULL,NULL);
	//}
}
//---------------------------------------------------------------------------

void __fastcall TfrmHanja::btnCloseTypeBClick(TObject *Sender)
{
	this->WebBrowser->Refresh();
	this->WebBrowser->Quit();

//	frmMain->IMGTOOLBTN31->Tag = 0;
//	frmMain->IMGTOOLBTN31->Picture->Bitmap->Handle = NULL;
//	frmMain->IMGTOOLBTN31->Picture->Bitmap->Assign(frmMain->TOOLBTN2_BITMAP1[0]);

	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmHanja::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(frmHanja->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmHanja::FormDeactivate(TObject *Sender)
{
//200803//	Close();
}
//---------------------------------------------------------------------------

