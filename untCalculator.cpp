//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"
//#include "untCalculator.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SHDocVw_OCX"
#pragma resource "*.dfm"
TfrmCalculator *frmCalculator;
//---------------------------------------------------------------------------
__fastcall TfrmCalculator::TfrmCalculator(TComponent* Owner)
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
void __fastcall TfrmCalculator::FormShow(TObject *Sender)
{
		wchar_t szWC[256]   = {0, };
		AnsiString URL;
		URL    = "https://search.naver.com/search.naver?sm=top_hty&fbm=1&ie=utf8&query=%EA%B3%B5%ED%95%99%EC%9A%A9%EA%B3%84%EC%82%B0%EA%B8%B0";
		URL.WideChar(szWC, 256);
		//this->WebBrowser->Left   = -27;
		//this->WebBrowser->Top    = -320;
		//this->WebBrowser->Width  = 639;
		//this->WebBrowser->Height = 633;
		this->WebBrowser2->Navigate(szWC,NULL,NULL,NULL,NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmCalculator::MyMessageHandler(TMsg &Msg, bool &Handled)
{
	Handled = IsDialogMessage(WebBrowser2->Handle, &Msg) == true;

	if(!Handled || WebBrowser2->Busy)
	{
		return;
	}

	if( (Msg.message == WM_KEYDOWN || Msg.message == WM_KEYUP) && (Msg.wParam == VK_RETURN || Msg.wParam == VK_TAB) )
	{
		if(FOleInPlaceActiveObject != NULL)
		{
			FOleInPlaceActiveObject->TranslateAccelerator(&Msg);
		}
		else
		{
			IDispatch *Dispatch = WebBrowser2->Application;
			if(Dispatch != NULL)
			{
				IOleInPlaceActiveObject *iOIPAO;
				Dispatch->QueryInterface(IID_IOleInPlaceActiveObject, (LPVOID *)&iOIPAO);

				if( iOIPAO != NULL )
				{
					FOleInPlaceActiveObject = iOIPAO;
					FOleInPlaceActiveObject->TranslateAccelerator(&Msg);
                }
            }
        }
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmCalculator::btnCloseTypeBClick(TObject *Sender)
{
	this->WebBrowser2->Refresh();
	this->WebBrowser2->Quit();

//	frmMain->IMGTOOLBTN34->Tag = 0;
//	frmMain->IMGTOOLBTN34->Picture->Bitmap->Handle = NULL;
//	frmMain->IMGTOOLBTN34->Picture->Bitmap->Assign(frmMain->TOOLBTN2_BITMAP1[3]);

	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalculator::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(frmCalculator->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalculator::FormCreate(TObject *Sender)
{
	OleInitialize(NULL);
	Application->OnMessage = MyMessageHandler;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalculator::FormDestroy(TObject *Sender)
{
	OleUninitialize();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalculator::FormDeactivate(TObject *Sender)
{
//	Close();
}
//---------------------------------------------------------------------------

