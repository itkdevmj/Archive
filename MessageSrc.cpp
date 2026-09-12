//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "common.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "bsMessages"
#pragma link "bsSkinCtrls"
#pragma link "bsSkinData"
#pragma link "AdvMemo"
#pragma link "bsSkinBoxCtrls"
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "BaseGrid"
#pragma resource "*.dfm"

//#pragma warn -8004

TfrmMsg *frmMsg;
//---------------------------------------------------------------------------
__fastcall TfrmMsg::TfrmMsg(TComponent* Owner)
	: TForm(Owner)
{
	m_sBoxPath = frmMain->RESPATH + "MESSAGE\\";

	if(FileExists(m_sBoxPath + "선택.jpg")){
		IMGWARRING->Picture->LoadFromFile(m_sBoxPath + "선택.jpg");
	}
	if(FileExists(m_sBoxPath + "예_1.jpg")){
		IMGWARRINGYES->Picture->LoadFromFile(m_sBoxPath + "예_1.jpg");
	}
	if(FileExists(m_sBoxPath + "아니오_1.jpg")){
		IMGWARRINGNO->Picture->LoadFromFile(m_sBoxPath + "아니오_1.jpg");
	}

	if(FileExists(m_sBoxPath + "에러.jpg")){
		IMGERROR->Picture->LoadFromFile(m_sBoxPath + "에러.jpg");
	}
	if(FileExists(m_sBoxPath + "확인_1.jpg")){
		IMGERRORYES->Picture->LoadFromFile(m_sBoxPath + "확인_1.jpg");
	}

	if(FileExists(m_sBoxPath + "정보.jpg")){
		IMGINFORMATION->Picture->LoadFromFile(m_sBoxPath + "정보.jpg");
	}
	if(FileExists(m_sBoxPath + "확인_1.jpg")){
		IMGINFORYES->Picture->LoadFromFile(m_sBoxPath + "확인_1.jpg");
	}

	exPanelWarring->Visible     = false;
	exPanelError->Visible       = false;
	exPanelInformation->Visible = false;

	ClientWidth  = IMGWARRING->Picture->Width;
	ClientHeight = IMGWARRING->Picture->Height;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsg::CreateParams(TCreateParams &Params)
{
	// 반드시 부모를 먼저 호출해야 한다.
	TForm::CreateParams(Params);

	Params.Style = (Params.Style | WS_POPUP) & ~WS_DLGFRAME;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMsg::IMGWARRINGYESMouseEnter(TObject *Sender)
{
	IMGWARRINGYES->Picture = NULL;
	IMGWARRINGYES->Picture->Bitmap->Handle = NULL;

	Application->ProcessMessages();

	if(FileExists(m_sBoxPath + "예_2.jpg")){
		IMGWARRINGYES->Picture->LoadFromFile(m_sBoxPath + "예_2.jpg");
	}
	Application->ProcessMessages();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsg::IMGWARRINGYESMouseLeave(TObject *Sender)
{
	IMGWARRINGYES->Picture = NULL;
	IMGWARRINGYES->Picture->Bitmap->Handle = NULL;

	Application->ProcessMessages();

	if(FileExists(m_sBoxPath + "예_1.jpg")){
		IMGWARRINGYES->Picture->LoadFromFile(m_sBoxPath + "예_1.jpg");
	}
	Application->ProcessMessages();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsg::IMGWARRINGYESMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	funcProcessIMGWARRINGYES();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsg::funcProcessIMGWARRINGYES()
{
	m_bClick = 1;
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsg::IMGWARRINGNOMouseEnter(TObject *Sender)
{
	IMGWARRINGNO->Picture = NULL;
	IMGWARRINGNO->Picture->Bitmap->Handle = NULL;

	Application->ProcessMessages();

	if(FileExists(m_sBoxPath + "아니오_2.jpg")){
		IMGWARRINGNO->Picture->LoadFromFile(m_sBoxPath + "아니오_2.jpg");
	}
	Application->ProcessMessages();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsg::IMGWARRINGNOMouseLeave(TObject *Sender)
{
	IMGWARRINGNO->Picture = NULL;
	IMGWARRINGNO->Picture->Bitmap->Handle = NULL;

	Application->ProcessMessages();

	if(FileExists(m_sBoxPath + "아니오_1.jpg")){
		IMGWARRINGNO->Picture->LoadFromFile(m_sBoxPath + "아니오_1.jpg");
	}
	Application->ProcessMessages();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsg::IMGWARRINGMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	if(Y > 0 && Y < 30){
		ReleaseCapture();
		SendMessage(Handle, WM_SYSCOMMAND, 0xf012, 0);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsg::IMGERRORMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	if(Y > 0 && Y < 30){
		ReleaseCapture();
		SendMessage(Handle, WM_SYSCOMMAND, 0xf012, 0);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsg::IMGINFORMATIONMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	if(Y > 0 && Y < 30){
		ReleaseCapture();
		SendMessage(Handle, WM_SYSCOMMAND, 0xf012, 0);
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsg::IMGERRORYESMouseEnter(TObject *Sender)
{
	IMGERRORYES->Picture = NULL;
	IMGERRORYES->Picture->Bitmap->Handle = NULL;

	Application->ProcessMessages();

	if(FileExists(m_sBoxPath + "확인_2.jpg")){
		IMGERRORYES->Picture->LoadFromFile(m_sBoxPath + "확인_2.jpg");
	}
	Application->ProcessMessages();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsg::IMGERRORYESMouseLeave(TObject *Sender)
{
	IMGERRORYES->Picture = NULL;
	IMGERRORYES->Picture->Bitmap->Handle = NULL;

	Application->ProcessMessages();

	if(FileExists(m_sBoxPath + "확인_1.jpg")){
		IMGERRORYES->Picture->LoadFromFile(m_sBoxPath + "확인_1.jpg");
	}
	Application->ProcessMessages();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsg::IMGERRORYESMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	funcProcessIMGERRORYES();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsg::funcProcessIMGERRORYES()
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsg::IMGINFORYESMouseEnter(TObject *Sender)
{
	IMGINFORYES->Picture = NULL;
	IMGINFORYES->Picture->Bitmap->Handle = NULL;

	Application->ProcessMessages();

	if(FileExists(m_sBoxPath + "확인_2.jpg")){
		IMGINFORYES->Picture->LoadFromFile(m_sBoxPath + "확인_2.jpg");
	}
	Application->ProcessMessages();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsg::IMGINFORYESMouseLeave(TObject *Sender)
{
	IMGINFORYES->Picture = NULL;
	IMGINFORYES->Picture->Bitmap->Handle = NULL;

	Application->ProcessMessages();

	if(FileExists(m_sBoxPath + "확인_1.jpg")){
		IMGINFORYES->Picture->LoadFromFile(m_sBoxPath + "확인_1.jpg");
	}
	Application->ProcessMessages();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsg::IMGINFORYESMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	funcProcessIMGINFORYES();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsg::funcProcessIMGINFORYES()
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsg::IMGWARRINGNOMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	m_bClick = 0;
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMsg::FormShow(TObject *Sender)
{
	m_bClick = 0;

	// 글자 입력길이 제한
	nMemoMaxLen = 200;
	bMaxLength  = false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMsg::IMGOBJECTIONSAVEdeEnabled()
{
}
//---------------------------------------------------------------------------

void __fastcall TfrmMsg::FormKeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN)
	{
		if(exPanelWarring->Visible)//선택
		{
			IMGWARRINGYESMouseEnter(NULL);
			funcProcessIMGWARRINGYES();
			IMGWARRINGYESMouseLeave(NULL);
		}
		else if(exPanelError->Visible)//에러
		{
			IMGERRORYESMouseEnter(NULL);
			funcProcessIMGERRORYES();
			IMGERRORYESMouseLeave(NULL);
		}
		else if(exPanelInformation->Visible)//정보
		{
			IMGINFORYESMouseEnter(NULL);
			funcProcessIMGINFORYES();
			IMGINFORYESMouseLeave(NULL);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMsg::funcMessageDlg(AnsiString Title, AnsiString Msg, int HelpCtx)
{
	exPanelWarring->Visible     = false;
	exPanelError->Visible       = false;
	exPanelInformation->Visible = false;
	m_bClick                    = 0;
	m_nCallMode                 = 0;

	if(HelpCtx == 1){//선택
		exPanelWarring->Visible    = true;
		this->Width  = exPanelWarring->Width;
		this->Height = exPanelWarring->Height;
		exPanelWarring->Top        = 0;
		exPanelWarring->Left       = 0;
		lblWarringTitle->Caption   = Title;
		lblWarringComment->Caption = Msg;

		IMGWARRINGYESMouseEnter(NULL);

		IMGWARRINGNOMouseLeave(NULL);

		this->ClientWidth  = exPanelWarring->Width;
		this->ClientHeight = exPanelWarring->Height;
		Application->ProcessMessages();
	}
	else if(HelpCtx == 2){//에러
		exPanelError->Visible    = true;
		this->Width  = exPanelError->Width;
		this->Height = exPanelError->Height;
		exPanelError->Top        = 0;
		exPanelError->Left       = 0;
		lblErrorTitle->Caption   = Title;
		lblErrorComment->Caption = Msg;

		IMGERRORYESMouseEnter(NULL);

		ClientWidth  = exPanelError->Width;
		ClientHeight = exPanelError->Height;
		Application->ProcessMessages();
	}
	else if(HelpCtx == 3){//정보
		exPanelInformation->Visible = true;
		this->Width  = exPanelInformation->Width;
		this->Height = exPanelInformation->Height;
		exPanelInformation->Top     = 0;
		exPanelInformation->Left    = 0;
		lblInforTitle->Caption      = Title;
		lblInforComment->Caption    = Msg;

		IMGINFORYESMouseEnter(NULL);

		this->ClientWidth  = exPanelInformation->Width;
		this->ClientHeight = exPanelInformation->Height;
		Application->ProcessMessages();
	}

	this->Left = Left + ClientWidth/2 - this->Width/2;
	this->Top  = Top + ClientHeight/2 - this->Height/2;
	this->ShowModal();
}
//---------------------------------------------------------------------------

