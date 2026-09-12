//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"
//#include "untSettingEnv.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmSettingEnv *frmSettingEnv;
//---------------------------------------------------------------------------
__fastcall TfrmSettingEnv::TfrmSettingEnv(TComponent* Owner)
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
		this->shpBG->Pen->Color		= (TColor)RGB(R, G, B);
		//shpWait->Pen->Color//
		//panWindowsMove->Color//
		//pnlWaitT->Color//
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmSettingEnv::FormCreate(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TfrmSettingEnv::imgSettingEnvCloseClick(TObject *Sender)
{
	AnsiString 	asTimer	 		= edtLogoutTime->Text;

	if( cboLogout->ItemIndex == 0)
	{
		if( asTimer.IsEmpty() )//자동로그아웃일 때 시간 설정//
		{
			AnsiString strMsg = "자동로그아웃 설정시간을 입력해주세요.";
			frmMsg->funcMessageDlg("설정값 확인:", strMsg, 3);
			return;
		}
		else if( asTimer < "10")
		{
			AnsiString strMsg = "자동로그아웃 시간은 최소 10분 이상으로 입력해주세요.";
			frmMsg->funcMessageDlg("설정값 확인:", strMsg, 3);
			return;
		}
		else if( asTimer > "60")
		{
			AnsiString strMsg = "자동로그아웃 시간은 최소 60분 이하로 입력해주세요.";
			frmMsg->funcMessageDlg("설정값 확인:", strMsg, 3);
			return;
		}
	}

	//==========================================
	//201119//측정(면적거리) Label Size, Color
	AnsiString 	asStr	= edtAreaFontSize->Text;
	if( asStr.IsEmpty() )
	{
		AnsiString strMsg = "폰트크기를 입력해주세요.";
		frmMsg->funcMessageDlg("설정값 확인:", strMsg, 3);
		edtAreaFontSize->SetFocus();
		return;
	}

	if(asStr.ToInt() < 7 || asStr.ToInt() > 20)
	{
		AnsiString strMsg = "폰트크기는 7이상 20이하로 입력해주세요.";
		frmMsg->funcMessageDlg("설정값 확인:", strMsg, 3);
		edtAreaFontSize->SetFocus();
		return;
	}
	//==========================================


	frmMain->funcSetIniUserSetInfo();
//	if(edtFontSize->Text == "")
//		edtFontSize->Text	= "12";
//	if(edtLineWidth->Text == "")
//		edtLineWidth->Text	= "38";//210205//"45";
//	frmMain->tcmpPaintBox[2]->Invalidate();//200915//#1
//	frmMain->chkOwnNamesClick(frmMain->chkOwnNames);

	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSettingEnv::lblUserManagementClick(TObject *Sender)
{
	//200421//관리자 로그인 시 메인화면에서 보여주기//
	if(frmUserLogList->funcGetGradeFromUserId(frmMain->func_Decoder(frmMain->m_asCurrentId)) != 2)
	{
		frmMsg->funcMessageDlg("제한 알림:", "<관리자>  접근가능 메뉴입니다.", 3);
		return;
	}

	if( !frmUserManagement->Showing )
		frmUserManagement->Show();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSettingEnv::lblReleaseListClick(TObject *Sender)
{
	if( !frmReleaseList->Showing )
		frmReleaseList->Show();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSettingEnv::FormShow(TObject *Sender)
{
	if(frmMain->INIINFO.B_DOCKIND[2])//측량결과도//
		frmSettingEnv->pnlDoc02Day->Visible = true;
	else
		frmSettingEnv->pnlDoc02Day->Visible = false;

//	//200610
//	if(frmMain->INI_B_OWNNAMES)//#OWNNAMES#
//		frmSettingEnv->pnlOwnLabel->Visible = true;
//	else
//		frmSettingEnv->pnlOwnLabel->Visible = false;


//	this->Left 		= frmMain->palMainSearchBar->Left;
//	this->Top		= frmMain->palMainSearchBar->Top;
	this->Left 		= frmMain->Left + frmMain->palMainSearchBar->Left + 6;
	this->Top		= frmMain->Top + frmMain->palMainSearchBar->Top + 6;
	//this->Top		= GetSystemMetrics(SM_CYCAPTION) + frmMain->palMainSearchBar->Top;
	this->Width		= 260;
	//200402//this->Height	= frmMain->palMainSearchBar->Height - frmMain->bsSkinStatusPanel->Height;
	this->Height	= frmMain->palMainSearchBar->Height - frmMain->StatusBar2->Height;//200402

//241122//NotUsed//
//	//지적도보기, 문서보기//
//	if(frmMain->INIUSERSETINFO.NVIEWMODE == 1)
//		rbViewMode1->Checked 	= true;
//	else
//		rbViewMode2->Checked	= true;
//
//	//항공뷰보기 설정//
//	if(frmMain->INIUSERSETINFO.B_VIEWAIR == 1)
//		rbViewAir1->Checked 	= true;
//	else
//		rbViewAir2->Checked		= true;
//
//	//검색창 크게, 작게//
//	if(frmMain->INIUSERSETINFO.NSEARCHBAR == 1)
//		rbSearchBar1->Checked 	= true;
//	else
//		rbSearchBar2->Checked	= true;

	//지번 자동변경//
	if(frmMain->INIUSERSETINFO.B_AUTOJIBUN)
		rbAutoJibun1->Checked 	= true;
	else
		rbAutoJibun2->Checked	= true;

	//워터마크 표시//
	if(frmMain->INIUSERSETINFO.B_WATERMARK)
		rbWaterMark1->Checked 	= true;
	else
		rbWaterMark2->Checked	= true;

	cboLogout->ItemIndex  	= (frmMain->INIUSERSETINFO.B_AUTOLOGOUT == true) ? (0) : (1);
	edtLogoutTime->Text  	= frmMain->INIUSERSETINFO.LOGOUTTIMER / 60;

	//==========================================
	//201119//측정(면적거리) Label Size, Color
	edtAreaFontSize->Text           = frmMain->INIUSERSETINFO.AREAFONTSIZE;
	lblAreaFontColor->Font->Color	= (TColor)frmMain->INIUSERSETINFO.AREAFONTCOLOR;
	//==========================================

	//==========================================
	//201221//이동결의서(그룹1만 처리(Default) / 그룹1,2 처리)
	if(frmMain->INIUSERSETINFO.DOC01GROUP == 1)
		rbDoc01Group1->Checked	= true;
	else
		rbDoc01Group2->Checked	= true;
	//==========================================

	//==========================================
	//201221//검색결과트리 설정(1:펼치기(Default), 2:닫기//
	if(frmMain->INIUSERSETINFO.B_EXPAND)
		rbExpand1->Checked	= true;
	else
		rbExpand2->Checked	= true;
	//==========================================

	//==========================================
	//220308//REQ//구대장(부책) 한글표시(자동)//
	if(frmMain->INIUSERSETINFO.B_OWNLABEL == 1)
		rbOwnLabel1->Checked 	= true;
	else
		rbOwnLabel2->Checked	= true;
	//==========================================

	wchar_t wszBuf[64];
	TCheckBox *tcmpChk;

	for(int i = 1; i < DF_DOC_CNT; i++)//191223//원복//#TAB00DEL#<검색>은 제외하기로//사장님Req//
	{
		memset(wszBuf, 0, sizeof(wszBuf));
		swprintf(wszBuf, L"chkQry%02d", i);
		tcmpChk = (TCheckBox *)this->FindComponent(wszBuf);
		if(tcmpChk != NULL)
		{
			if(frmMain->INIINFO.B_DOCKIND[i])
			{
				tcmpChk->Visible = true;
				tcmpChk->Checked = frmMain->INIINFO.B_QRYCHECK[i];
			}
			else
			{
				tcmpChk->Visible	= false;
            }
		}
	}

	//---DOC02
	if(pnlDoc02Day->Visible)
	{
		if(frmMain->INIUSERSETINFO.DOC02DAY == 1)
			rbDoc02Day1->Checked = true;
		else if(frmMain->INIUSERSETINFO.DOC02DAY == 2)
			rbDoc02Day2->Checked = true;
		else if(frmMain->INIUSERSETINFO.DOC02DAY == 3)
			rbDoc02Day3->Checked = true;
	}

	int nCount	= 0;
	if(pnlAreaFont->Visible)//201222//
		nCount++;
	if(pnlAutoJibun->Visible)
		nCount++;
	if(pnlDoc01Group->Visible)//201222//
		nCount++;
	if(pnlDoc02Day->Visible)
		nCount++;
	if(pnlExpand->Visible)//201222//
		nCount++;
	if(pnlLogout->Visible)
		nCount++;
	if(pnlOwnLabel->Visible)
		nCount++;
	if(pnlSearchBar->Visible)
		nCount++;
	if(pnlViewAir->Visible)
		nCount++;
	if(pnlViewMode->Visible)
		nCount++;
	if(pnlWaterMark->Visible)
		nCount++;

//231019//alClient 이므로 설정해도 동작하지 않아서 주석처리//
//	pnlSettingD->Height	= nCount * 54;
//	pnlSetting->Height	= pnlSettingD->Height + pnlSettingT->Height;
	ScrollBox1->Height  = pnlDirect->Height + (pnlSettingT->Height + nCount * 54);
	pnlMain->Height		= pnlDirect->Height + (pnlSettingT->Height + nCount * 54);
	int	nTitle	= pnlBlankB1->Height + pnlBlankT1->Height + pnlBlankT2->Height + pnlTitle->Height;

	if(pnlMain->Height + nTitle > this->Height)
	{
		pnlMain->Height		= this->Height - nTitle;
		ScrollBox1->VertScrollBar->Visible	= true;
	}
	else
	{
		ScrollBox1->VertScrollBar->Visible	= false;
	}

	pnlSettingEnv->Height = nTitle + pnlMain->Height - 2;
	//shpBG->Height 	= this->Height;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSettingEnv::FormClose(TObject *Sender, TCloseAction &Action)
{
	//pnlSettingEnvCloseClick(pnlSettingEnvClose);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSettingEnv::pnlBlankT1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	ReleaseCapture();
	SendMessage(frmSettingEnv->Handle, WM_SYSCOMMAND, 0xf012, 0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmSettingEnv::lblAboutClick(TObject *Sender)
{
	if( !frmAbout->Showing )
		frmAbout->Show();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSettingEnv::imgSwitchClick(TObject *Sender)
{
	wchar_t wBufImg[64];
	TImage *tcmpImg;
	int nTag 				= dynamic_cast<TImage*>(Sender)->Tag;
	int nHint 				= dynamic_cast<TImage*>(Sender)->Hint.ToInt();

	memset(wBufImg, 0, sizeof(wBufImg));
	swprintf(wBufImg, L"imgSwitch%d", nTag);
	tcmpImg = (TImage*)this->FindComponent(wBufImg);
	if(tcmpImg != NULL)
	{
		tcmpImg->Picture->Bitmap->Handle = NULL;
		tcmpImg->Picture                 = NULL;
		if(nHint == 0)
		{
			tcmpImg->Hint = "1";
			tcmpImg->Picture->Bitmap->Assign(frmMain->BITMAP_BTN_TAB[1][frmMain->Arrow]);
		}
		else
		{
			tcmpImg->Hint = "0";
			tcmpImg->Picture->Bitmap->Assign(frmMain->BITMAP_BTN_TAB[0][frmMain->Arrow]);
		}


		switch(nTag)
		{
			case 1:
				if(tcmpImg->Hint == "0")
				{
					pnlDirectD->Visible	= true;
					pnlDirect->Height	= pnlDirectT->Height + pnlDirectD->Height + 10;
				}
				else
				{
					pnlDirectD->Visible	= false;
					pnlDirect->Height	= pnlDirectT->Height + 10;
				}
				break;
			case 2:
				if(tcmpImg->Hint == "0")
				{
					pnlSettingD->Visible 	= true;
					pnlSetting->Height		= pnlSettingT->Height + pnlSettingD->Height + 10;
				}
				else
				{
					pnlSettingD->Visible	= false;
					pnlSetting->Height		= pnlSettingT->Height + 10;
				}
				break;
		}
	}
}
//---------------------------------------------------------------------------

//201119//측정(면적거리) Label Size, Color
void __fastcall TfrmSettingEnv::btnFontColorClick(TObject *Sender)
{
	if (ColorDialog1->Execute())
		lblAreaFontColor->Font->Color = ColorDialog1->Color;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSettingEnv::ScrollBox1MouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
	ScrollBox1->VertScrollBar->Position -= WheelDelta;
}
//---------------------------------------------------------------------------

void __fastcall TfrmSettingEnv::lblStatClick(TObject *Sender)
{
	if( !frmStat->Showing )
		frmStat->Show();
}
//---------------------------------------------------------------------------

