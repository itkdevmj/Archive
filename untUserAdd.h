//---------------------------------------------------------------------------

#ifndef untUserAddH
#define untUserAddH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <pngimage.hpp>
//---------------------------------------------------------------------------
class TfrmUserAdd : public TForm
{
__published:	// IDE-managed Components
	TPanel *panCenter;
	TGroupBox *GroupBox1;
	TPanel *pnlTitle1;
	TEdit *edtUserInfo1;
	TPanel *pnlTitle2;
	TEdit *edtUserInfo2;
	TPanel *pnlGrade;
	TComboBox *cboGrade;
	TPanel *pnlTitle3;
	TEdit *edtUserInfo3;
	TPanel *pnlTitle4;
	TEdit *edtUserInfo4;
	TPanel *pnlTitle5;
	TEdit *edtUserInfo5;
	TPanel *pnlTitle7;
	TEdit *edtUserInfo7;
	TPanel *pnlTitle6;
	TEdit *edtUserInfo6;
	TPanel *panWindowsMove;
	TImage *btnCloseTypeB;
	TLabel *lblFormTitle;
	TImage *Image2;
	TImage *IMGREGIST;
	TImage *IMGMODIFY;
	TImage *IMGEXIT;
	TPanel *pnlTitle8;
	TEdit *edtUserInfo8;
	TButton *btnInitFailCut;
	TShape *shpBG;
	TPanel *pnlGradeReason;
	TEdit *edtReason;
	TLabel *lblName;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall edtHangul_OnEnter(TObject *Sender);
	void __fastcall edtAlphaNumeric_OnEnter(TObject *Sender);
	void __fastcall btnCloseTypeBClick(TObject *Sender);
	void __fastcall IMGREGISTMouseEnter(TObject *Sender);
	void __fastcall IMGREGISTMouseLeave(TObject *Sender);
	void __fastcall IMGREGISTClick(TObject *Sender);
	void __fastcall IMGMODIFYMouseEnter(TObject *Sender);
	void __fastcall IMGMODIFYMouseLeave(TObject *Sender);
	void __fastcall IMGMODIFYClick(TObject *Sender);
	void __fastcall IMGEXITMouseEnter(TObject *Sender);
	void __fastcall IMGEXITMouseLeave(TObject *Sender);
	void __fastcall IMGEXITClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall edtUserInfoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall btnInitFailCutClick(TObject *Sender);
	void __fastcall cboGradeClick(TObject *Sender);
	void __fastcall edtReasonKeyPress(TObject *Sender, wchar_t &Key);

private:	// User declarations
	bool TfrmUserAdd::funCheckEditBox(int nType);
	bool TfrmUserAdd::funCheckRePassWord();
	bool __fastcall TfrmUserAdd::func_checkPassWord();

public:		// User declarations
	bool    b_Content_Change_flag;
	bool	m_bInitPassword;//210326//#PERSON_INFO

	//200220//notused//int __fastcall funcGetUseLayerValue();//181115
	bool __fastcall funQueryUserId(AnsiString _asUserID);
	AnsiString __fastcall func_GetLocalIP();

	//IMAGES
	Graphics::TBitmap *BITMAP_BTN_REGIST[3];
	Graphics::TBitmap *BITMAP_BTN_MODIFY[3];
	Graphics::TBitmap *BITMAP_BTN_EXIT[2];

	void __fastcall funcLoadButtonImage();
	void __fastcall funcDeleteButtonImage();

	__fastcall TfrmUserAdd(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmUserAdd *frmUserAdd;
//---------------------------------------------------------------------------
#endif
