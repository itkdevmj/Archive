//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCalcDate *frmCalcDate;
//---------------------------------------------------------------------------
__fastcall TfrmCalcDate::TfrmCalcDate(TComponent* Owner)
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
void __fastcall TfrmCalcDate::FormShow(TObject *Sender)
{

	String sNowDate = Now().FormatString("yyyy");
	unsigned short nCalYear = sNowDate.ToInt();
	unsigned short nCalM = Now().FormatString("mm").ToInt();
	unsigned short nCalD  = Now().FormatString("dd").ToInt();


	wchar_t wcDate[64];
	memset(wcDate, 0, sizeof(wcDate));
	swprintf(wcDate, L"%d년%d월%d일", nCalYear, nCalM,  nCalD);

	cboYearType->ItemIndex = 0;
	edtYear->Text = IntToStr(nCalYear);
	btnCalcClick(NULL);
}

//---------------------------------------------------------------------------

void __fastcall TfrmCalcDate::cboYearTypeChange(TObject *Sender)
{
	edtYear->Text = L"";
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalcDate::btnCalcClick(TObject *Sender)
{
	try {
		int nInputYear = edtYear->Text.ToInt();
		int nCalYear0;
		int nCalYear1;
		int nCalYear2;
		int nCalYear3;
		int nCalYear4;
		int nCalYear5;
		int nCalYear6;
		int nCalYear7;

		switch(cboYearType->ItemIndex)
		{
			case 0:	nCalYear0 = nInputYear;	break;
			case 1: nCalYear0 = nInputYear + 1896;	break;
			case 2: nCalYear0 = nInputYear + 1867;	break;
			case 3: nCalYear0 = nInputYear + 1911;	break;
			case 4: nCalYear0 = nInputYear + 1925;	break;
			case 5: nCalYear0 = nInputYear - 2333;	break;
			case 6: nCalYear0 = nInputYear - 544;	break;
			case 7: nCalYear0 = nInputYear - 7197;	break;
			default:
				break;
		}

		nCalYear1 = nCalYear0 - 1896;
		nCalYear2 = nCalYear0 - 1867;
		nCalYear3 = nCalYear0 - 1911;
		nCalYear4 = nCalYear0 - 1925;
		nCalYear5 = nCalYear0 + 2333;
		nCalYear6 = nCalYear0 + 544;
		nCalYear7 = nCalYear0 + 7197;

		StaticText1->Caption = IntToStr(nCalYear0);
		StaticText2->Caption = IntToStr(nCalYear1);
		StaticText3->Caption = IntToStr(nCalYear2);
		StaticText4->Caption = IntToStr(nCalYear3);
		StaticText5->Caption = IntToStr(nCalYear4);
		StaticText6->Caption = IntToStr(nCalYear5);
		StaticText7->Caption = IntToStr(nCalYear6);
		StaticText8->Caption = IntToStr(nCalYear7);


	}
	catch (Exception &exception) {
		throw Exception("입력오류");
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmCalcDate::FormClose(TObject *Sender, TCloseAction &Action)
{
//	if (frmCalcDate->Tag == 1) {
//		frmMain->IMGTOOLBTN32->Tag = 0;
//		frmMain->IMGTOOLBTN32->Picture->Bitmap->Handle = NULL;
//		frmMain->IMGTOOLBTN32->Picture->Bitmap->Assign(frmMain->TOOLBTN2_BITMAP1[1]);
//	}
//	else if (frmCalcDate->Tag == 2) {
//		frmMain->IMGTOOLBTN33->Tag = 0;
//		frmMain->IMGTOOLBTN33->Picture->Bitmap->Handle = NULL;
//		frmMain->IMGTOOLBTN33->Picture->Bitmap->Assign(frmMain->TOOLBTN2_BITMAP1[2]);
//	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalcDate::edtYearKeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN)
		this->btnCalcClick(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalcDate::btnCloseTypeBClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalcDate::panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(frmCalcDate->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmCalcDate::FormDeactivate(TObject *Sender)
{
//200803//	Close();
}
//---------------------------------------------------------------------------

