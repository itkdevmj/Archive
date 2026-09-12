//---------------------------------------------------------------------------

#ifndef untUserManagementH
#define untUserManagementH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "IdBaseComponent.hpp"      	// IdEncoderMIME1 Add
#include "IdCoder.hpp"                  // IdEncoderMIME1 Add
#include "IdCoder3to4.hpp"              // IdEncoderMIME1 Add
#include "IdCoderMIME.hpp"
#include <pngimage.hpp>              // IdEncoderMIME1 Add
//---------------------------------------------------------------------------
class TfrmUserManagement : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TGroupBox *GroupBox1;
	TListView *lstvUserListInfo;
	TGroupBox *GroupBox2;
	TPanel *Panel5;
	TEdit *edtUserInfo5;
	TPanel *Panel6;
	TEdit *edtUserInfo3;
	TPanel *Panel7;
	TEdit *edtUserInfo4;
	TPanel *Panel8;
	TEdit *edtUserInfo1;
	TPanel *Panel9;
	TPanel *Panel10;
	TEdit *edtUserInfo2;
	TStatusBar *stbVectorInfo;
	TEdit *edtUserInfo6;
	TTabSheet *TabSheet2;
	TGroupBox *GroupBox3;
	TListView *lvUserBList;
	TCheckBox *cbxAll;
	TPanel *panWindowsMove;
	TImage *btnCloseTypeB;
	TLabel *lblFormTitle;
	TImage *Image2;
	TImage *IMGLOG;
	TImage *IMGREGIST;
	TImage *IMGMODIFY;
	TImage *IMGDELETE;
	TImage *IMGEXIT;
	TImage *IMGSAVESETTING;
	TImage *IMGEXIT2;
	TLabel *lblUserInfo8;
	TShape *shpBG;
	TEdit *edtUserInfo7;
	TEdit *edtName;
	TLabel *lblName;
	TButton *btnFind;
	TLabel *lblTotalGrade;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall lstvUserListInfoClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall PageControl1Change(TObject *Sender);
	void __fastcall cbxAll_OnClick(TObject *Sender);
	void __fastcall TabSheet1_OnShow(TObject *Sender);
	void __fastcall TabSheet2_OnShow(TObject *Sender);
	void __fastcall frmUserManagement_OnCreate(TObject *Sender);
	void __fastcall PageControl1Changing(TObject *Sender, bool &AllowChange);
	void __fastcall IMGREGISTMouseEnter(TObject *Sender);
	void __fastcall IMGREGISTMouseLeave(TObject *Sender);
	void __fastcall IMGREGISTClick(TObject *Sender);
	void __fastcall IMGMODIFYMouseEnter(TObject *Sender);
	void __fastcall IMGMODIFYMouseLeave(TObject *Sender);
	void __fastcall IMGMODIFYClick(TObject *Sender);
	void __fastcall IMGDELETEMouseEnter(TObject *Sender);
	void __fastcall IMGDELETEMouseLeave(TObject *Sender);
	void __fastcall IMGDELETEClick(TObject *Sender);
	void __fastcall IMGEXITMouseEnter(TObject *Sender);
	void __fastcall IMGEXITMouseLeave(TObject *Sender);
	void __fastcall IMGEXITClick(TObject *Sender);
	void __fastcall IMGLOGMouseEnter(TObject *Sender);
	void __fastcall IMGLOGMouseLeave(TObject *Sender);
	void __fastcall IMGLOGClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall IMGSAVESETTINGMouseEnter(TObject *Sender);
	void __fastcall IMGSAVESETTINGMouseLeave(TObject *Sender);
	void __fastcall IMGSAVESETTINGClick(TObject *Sender);
	void __fastcall IMGEXIT2MouseEnter(TObject *Sender);
	void __fastcall IMGEXIT2MouseLeave(TObject *Sender);
	void __fastcall IMGEXIT2Click(TObject *Sender);
	void __fastcall btnCloseTypeBClick(TObject *Sender);
	void __fastcall panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall btnFindClick(TObject *Sender);
	void __fastcall edtFindKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtHangul_OnEnter(TObject *Sender);

private:	// User declarations

	int TfrmUserManagement::funSearchUserVIndex(char *cName, char *cId);

public:		// User declarations

	UserInfo	mCurrentUser;
	vector<UserInfo> mvUserInfoList;
	vector<UserHistInfo> mvUserHistInfoList;
	int			lstvUserListInfoIndex;//리스트인덱스
	int			m_nUserListVectorIndex;//220208//mvUserInfoList 벡터인덱스//

	int	nUser4Count;

	void __fastcall funcReadUserInformation();
//	void __fastcall funcReadUserHistInformation1();
//	void __fastcall funcReadUserHistInformation2();
	int  __fastcall funcSQLSelectUserBInfo(AnsiString _asId);
	void __fastcall funcSQLUpdateUserBInfo(int _nValue, AnsiString _asId);

	int TfrmUserManagement::funUserInfoToBuffIndex(char* cUserName);

	void TfrmUserManagement::funListClear();
	void TfrmUserManagement::funcListDisplay();
	int TfrmUserManagement::funUserGradeStrToInt(String sGrade);
	String TfrmUserManagement::funUserGradeIntToStr(int nType);

	void __fastcall TfrmUserManagement::funcSetUserLoginState(UserInfo* _mUserInfo, int nType);
//230207//사용자작업기록에서 funcGetKindNameToKindIndex로 체크하여 문제가 발생//
//DB직접Query했을 때와 프로그램에서 동일 Query 수행 시 결과가 다르게 나오는 이슈발생//
//_nType을 _asTypeNm으로 변경한다//
//230207//void __fastcall TfrmUserManagement::funcSetUserHistState(UserInfo* _mUserInfo, int _nType, int _nDoc)
	void __fastcall TfrmUserManagement::funcSetUserHistState(UserInfo* _mUserInfo, AnsiString  _asTypeNm, int _nDoc);
	AnsiString __fastcall TfrmUserManagement::funcReadUserName(AnsiString _asId);

	//IMAGES
	Graphics::TBitmap *BITMAP_BTN_REGIST[3];
	Graphics::TBitmap *BITMAP_BTN_MODIFY[3];
	Graphics::TBitmap *BITMAP_BTN_DELETE[3];
	Graphics::TBitmap *BITMAP_BTN_EXIT[2];
	Graphics::TBitmap *BITMAP_BTN_LOG[2];
	Graphics::TBitmap *BITMAP_BTN_SAVESETTING[2];

	void __fastcall funcLoadButtonImage();
	void __fastcall funcDeleteButtonImage();


	//================================================================
	// 사용자별 문서권한설정//
	//================================================================
	void __fastcall funcUserBSetting();
	int  __fastcall funcGetUserBValue();
	void __fastcall funcSetUserBValue(int _nValue);


	__fastcall TfrmUserManagement(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmUserManagement *frmUserManagement;
//---------------------------------------------------------------------------
#endif
