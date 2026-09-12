//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"

#pragma warn -8004

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmAreaCalculatorTypeA *frmAreaCalculatorTypeA;
//---------------------------------------------------------------------------
__fastcall TfrmAreaCalculatorTypeA::TfrmAreaCalculatorTypeA(TComponent* Owner)
	: TForm(Owner)
{
	//======================================================================
	//241204//#ÀüÁÖ#Áß¾ÓÁ¤º¸Å×Å©//
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

void __fastcall TfrmAreaCalculatorTypeA::FormShow(TObject *Sender)
{
	cboType->ItemIndex = 0;
	edtValue->Text = L"1";
	btnCalcAClick(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TfrmAreaCalculatorTypeA::cboTypeChange(TObject *Sender)
{
	//
}
//---------------------------------------------------------------------------

void __fastcall TfrmAreaCalculatorTypeA::btnCalcAClick(TObject *Sender)
{
	double dInputValue = 0;
	double dCalcValue0 = 0;
	double dCalcValue1 = 0;
	double dCalcValue2 = 0;
	double dCalcValue3 = 0;
	double dCalcValue4 = 0;
	double dCalcValue5 = 0;

	AnsiString strValue;

	try {
		dInputValue = edtValue->Text.ToDouble();
//		strValue = FormatFloat("###,##0.00", dInputValue);
//		dInputValue = strValue.ToDouble();

		switch(cboType->ItemIndex)
		{
			case 0:	dCalcValue0 = dInputValue;			break;
			case 1: dCalcValue0 = dInputValue * 0.3025; break; // 3.3057;	break;
			case 2: dCalcValue0 = dInputValue * 3000;	break;
			case 3: dCalcValue0 = dInputValue * 300;	break;
			case 4: dCalcValue0 = dInputValue * 30;		break;
			//210309//#AREACALC//case 5: dCalcValue0 = dInputValue * 3;		break;
			case 5: dCalcValue0 = dInputValue;			break;//210309//#AREACALC//
			default:
				break;
		}

		dCalcValue1 = dCalcValue0 * 3.3057851239669442148; //3.30578512396694421487603305785124 = 1 / 0.3025
		dCalcValue2 = dCalcValue0 / 3000;
		dCalcValue3 = dCalcValue0 / 300;
		dCalcValue4 = dCalcValue0 / 30;
		//210309//#AREACALC//dCalcValue5 = dCalcValue0 / 3;
		dCalcValue5 = dCalcValue0;//210309//#AREACALC//

		StaticText1->Caption = FormatFloat("###,##0.000000000", dCalcValue0);
		StaticText2->Caption = FormatFloat("###,##0.000000000", dCalcValue1);
		StaticText3->Caption = FormatFloat("###,##0.000000000", dCalcValue2);
		StaticText4->Caption = FormatFloat("###,##0.000000000", dCalcValue3);
		StaticText5->Caption = FormatFloat("###,##0.000000000", dCalcValue4);
		StaticText6->Caption = FormatFloat("###,##0.000000000", dCalcValue5);

//		if (cboType->ItemIndex == 2) {
//			StaticText1->Caption = FormatFloat("###,##0.0000", dCalcValue0); //FloatToStr(dCalcValue0);
//			StaticText2->Caption = FormatFloat("###,##0.0000", dCalcValue1);
//			StaticText3->Caption = FormatFloat("###,##0.000000", dCalcValue2);
//			StaticText4->Caption = FormatFloat("###,##0.000000", dCalcValue3);
//			StaticText5->Caption = FormatFloat("###,##0.000000", dCalcValue4);
//			StaticText6->Caption = FormatFloat("###,##0.0000", dCalcValue5);
//		} else {
//			StaticText1->Caption = FormatFloat("###,##0.0000", dCalcValue0); //FloatToStr(dCalcValue0);
//			StaticText2->Caption = FormatFloat("###,##0.0000", dCalcValue1);
//			StaticText3->Caption = FormatFloat("###,##0.0000", dCalcValue2);
//			StaticText4->Caption = FormatFloat("###,##0.0000", dCalcValue3);
//			StaticText5->Caption = FormatFloat("###,##0.0000", dCalcValue4);
//			StaticText6->Caption = FormatFloat("###,##0.0000", dCalcValue5);
//        }
	}
	catch (Exception &exception) {
		throw Exception("ÀÔ·Â ¿À·ùÀÔ´Ï´Ù.");
	}

}
//---------------------------------------------------------------------------

void __fastcall TfrmAreaCalculatorTypeA::edtValueKeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN)
	{
		if(Sender == edtValue)
			this->btnCalcAClick(NULL);
		else if(Sender == Edit1)
			Edit2->SetFocus();
		else if(Sender == Edit2)
			Edit3->SetFocus();
		else if(Sender == Edit3)
			Edit4->SetFocus();
		else if(Sender == Edit4)
			this->btnCalcBClick(NULL);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmAreaCalculatorTypeA::FormClose(TObject *Sender, TCloseAction &Action)
{
//	frmMain->IMGTOOLBTN33->Tag = 0;
//	frmMain->IMGTOOLBTN33->Picture->Bitmap->Handle = NULL;
//	frmMain->IMGTOOLBTN33->Picture->Bitmap->Assign(frmMain->TOOLBTN2_BITMAP1[2]);
}
//---------------------------------------------------------------------------

void __fastcall TfrmAreaCalculatorTypeA::btnCloseTypeBClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAreaCalculatorTypeA::panWindowsMoveMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	//SendMessage(panWindowsMove->Handle, WM_SYSCOMMAND, 0xf012, 0);
	SendMessage(frmAreaCalculatorTypeA->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmAreaCalculatorTypeA::btnCalcBClick(TObject *Sender)
{
	//
	double dCalcValueA1 = 0;
	double dCalcValueA2 = 0;
	double dCalcValueA3 = 0;
	double dCalcValueA4 = 0;
	double dCalcValueA9 = 0;
	double dCalcValueA8 = 0;
	double dCalcValueSum = 0;

	if (Edit1->Text.IsEmpty()) { Edit1->Text = L"0"; }
	if (Edit2->Text.IsEmpty()) { Edit2->Text = L"0"; }
	if (Edit3->Text.IsEmpty()) { Edit3->Text = L"0"; }
	if (Edit4->Text.IsEmpty()) { Edit4->Text = L"0"; }

	//210309//#AREACALC//
	//1Á¤(¹çµÎµÏ Á¤:ïë)	: 3,000Æò//
	//1´Ü(Ãþ°è ´Ü:Ó«)	: 300Æò//
	//1¹«(ÀÌ¶û ¹«:Ùï)	: 30Æò//
	//1º¸(°ÉÀ½ º¸:ÜÆ)	: 1Æò//

	dCalcValueA1 = Edit1->Text.ToDouble();
	dCalcValueA2 = Edit2->Text.ToDouble();
	dCalcValueA3 = Edit3->Text.ToDouble();
	dCalcValueA4 = Edit4->Text.ToDouble();
	//210309//#AREACALC//dCalcValueSum = dCalcValueA1 + dCalcValueA2 * 0.1 + dCalcValueA3 * 0.01 + dCalcValueA4 * 0.001;
	//210309//#AREACALC//dCalcValueA9 = dCalcValueSum * 3000;
	//210309//#AREACALC//dCalcValueA8 = dCalcValueSum * 9917.35537;
	//210309//#AREACALC//
	dCalcValueSum = dCalcValueA1 + dCalcValueA2 * 0.1 + dCalcValueA3 * 0.01;
	dCalcValueA9 = dCalcValueSum * 3000 + dCalcValueA4;
	dCalcValueA8 = dCalcValueA9 * 3.3057851239669442148;//9917.35537;
//	dCalcValueA9 = (dCalcValueA1 * 3000) + (dCalcValueA2 * 300) + (dCalcValueA3 * 30) + (dCalcValueA4 * 1);
//	dCalcValueA8 = dCalcValueA9 * 3.305785;

	Edit5->Text =  FormatFloat("###,##0.000000000", dCalcValueA9);
	Edit6->Text =  FormatFloat("###,##0.000000000", dCalcValueA8);
}
//---------------------------------------------------------------------------

void __fastcall TfrmAreaCalculatorTypeA::FormDeactivate(TObject *Sender)
{
//200803//	Close();
}
//---------------------------------------------------------------------------

