//---------------------------------------------------------------------------

#ifndef untUserLogListH
#define untUserLogListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <pngimage.hpp>
#include <Mask.hpp>
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "BaseGrid.hpp"
#include <Grids.hpp>
#include <Dialogs.hpp>
#include "tmsAdvGridExcel.hpp"
#include "bsPngImageList.hpp"
//---------------------------------------------------------------------------
class TfrmUserLogList : public TForm
{
__published:	// IDE-managed Components
	TPanel *panCenter;
	TPanel *Panel2;
	TPanel *Panel3;
	TPanel *Panel4;
	TPanel *Panel5;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TPanel *panWindowsMove;
	TImage *Image3;
	TLabel *lblFormTitle;
	TImage *btnCloseTypeB;
	TImage *IMGSAVELOG;
	TImage *IMGEXIT;
	TPanel *pnlFind;
	TMaskEdit *dtEndMon;
	TMaskEdit *dtSttMon;
	TLabel *lblFind;
	TLabel *lblMid;
	TImage *IMGFIND;
	TShape *shpBG;
	TCheckBox *chkDayOff;
	TPanel *pnlHist;
	TAdvStringGrid *sgHist;
	TPanel *pnlHistT;
	TLabel *lblAct;
	TComboBox *cboAct;
	TPanel *pnlLog;
	TAdvStringGrid *sgLog;
	TPanel *pnlLogT;
	TSaveDialog *SaveDialog1;
	TAdvGridExcelIO *AdvGridExcelIO1;
	TAdvGridExcelIO *AdvGridExcelIO2;
	TTabSheet *TabSheet3;
	TPanel *pnlDownload;
	TAdvStringGrid *sgDownload;
	TPanel *pnlDownloadT;
	TAdvGridExcelIO *AdvGridExcelIO3;
	TTabSheet *TabSheet4;
	TPanel *pnlGrade;
	TAdvStringGrid *sgGrade;
	TPanel *pnlGradeT;
	TLabel *lblGrade;
	TComboBox *cboGrade;
	TComboBox *cboLog;
	TLabel *lblLog;
	TPanel *palWait;
	TShape *shpWait;
	TbsPngImageView *bsPngImageView1;
	TLabel *lblWait1;
	TLabel *lblWait2;
	TPanel *pnlWaitT;
	TLabel *lblDownloadCnt;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall IMGSAVELOGMouseEnter(TObject *Sender);
	void __fastcall IMGSAVELOGMouseLeave(TObject *Sender);
	void __fastcall IMGSAVELOGClick(TObject *Sender);
	void __fastcall IMGEXITMouseEnter(TObject *Sender);
	void __fastcall IMGEXITMouseLeave(TObject *Sender);
	void __fastcall IMGEXITClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btnCloseTypeBClick(TObject *Sender);
	void __fastcall edtDate_OnKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall edtDate_OnKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtDate_OnEnter(TObject *Sender);
	void __fastcall edtDate_OnExit(TObject *Sender);
	void __fastcall IMGFINDMouseEnter(TObject *Sender);
	void __fastcall IMGFINDMouseLeave(TObject *Sender);
	void __fastcall IMGFINDClick(TObject *Sender);
	void __fastcall panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall sgLogGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign, TVAlignment &VAlign);
	void __fastcall sgHistGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign, TVAlignment &VAlign);
	void __fastcall sgLogClickCell(TObject *Sender, int ARow, int ACol);
	void __fastcall sgHistClickCell(TObject *Sender, int ARow, int ACol);
	void __fastcall chkDayOffClick(TObject *Sender);
	void __fastcall sgDownloadClickCell(TObject *Sender, int ARow, int ACol);
	void __fastcall sgDownloadGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign, TVAlignment &VAlign);
	void __fastcall cboActClick(TObject *Sender);
	void __fastcall sgGradeGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign, TVAlignment &VAlign);
	void __fastcall cboGradeClick(TObject *Sender);
	void __fastcall cboLogClick(TObject *Sender);
	void __fastcall PageControl1Changing(TObject *Sender, bool &AllowChange);
	void __fastcall PageControl1Change(TObject *Sender);


private:	// User declarations
	vector<UserLogInfo> 		mvUserLogInfo;
	vector<UserHistInfo> 		mvUserHistInfo;
	vector<UserDownloadInfo> 	mvUserDownloadInfo;
	vector<UserHistInfo> 		mvUserGradeInfo;//210331//#GRADELIST

	void __fastcall funListClear();
	void __fastcall funcListDisplay();

public:		// User declarations
	AnsiString	asSelectId;

	void __fastcall 	funcSetWaitWindows(bool bSetValue);

	void __fastcall funcSaveLogList();

	//IMAGES
	Graphics::TBitmap *BITMAP_BTN_SAVELOG[2];
	Graphics::TBitmap *BITMAP_BTN_EXIT[2];
	Graphics::TBitmap *BITMAP_BTN_FIND[2];

	void __fastcall funcLoadButtonImage();
	void __fastcall funcDeleteButtonImage();

	bool __fastcall funcCheckDateKeyword(TObject *Sender);


	//201105//
	//####################################################
	// 로그인기록//
	//####################################################
	int				m_nLogCount;
	void __fastcall funcCreateLog();
	void __fastcall funcInitLog();
	void __fastcall funcDispLog();
	void __fastcall funcReadUserLogInformation();

	//####################################################
	// 작업기록//
	//####################################################
	int				m_nHistCount;
	void __fastcall funcCreateHist();
	void __fastcall funcInitHist();
	void __fastcall funcDispHist();
	void __fastcall funcReadUserHistInformation();

    //210305//#TB_COPY_DNLD//
	//####################################################
	// 파일저장기록//
	//####################################################
	int				m_nDownloadCount;
	void __fastcall funcCreateDownload();
	void __fastcall funcInitDownload();
	void __fastcall funcDispDownload();
	void __fastcall funcReadUserDownloadInformation();

	//####################################################
	// 권한변경기록//
	//####################################################
	int				m_nGradeCount;
	void __fastcall funcCreateGrade();
	void __fastcall funcInitGrade();
	void __fastcall funcDispGrade();
	void __fastcall funcReadUserGradeInformation();


	//----------------------------------------------------------
	int __fastcall funcGetGradeFromUserId(AnsiString _asUserId);

	__fastcall TfrmUserLogList(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmUserLogList *frmUserLogList;
//---------------------------------------------------------------------------
#endif
