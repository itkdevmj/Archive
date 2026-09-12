//---------------------------------------------------------------------------

#ifndef unt02AttachH
#define unt02AttachH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Grids.hpp>
#include <pngimage.hpp>
//---------------------------------------------------------------------------
class Tfrm02Attach : public TForm
{
__published:	// IDE-managed Components
	TPanel *pnl02Attach;
	TPanel *panWindowsMove;
	TLabel *lblFormTitle;
	TPanel *pnlClose;
	TPageControl *PageControl1;
	TTabSheet *tabRegist;
	TTabSheet *tabQuery;
	TFileSaveDialog *FileSaveDialog1;
	TOpenDialog *OpenDialog1;
	TMonthCalendar *clndInspctDtR;
	TMonthCalendar *clndSurvDtR;
	TPanel *pnlL;
	TPanel *pnlMainR;
	TPanel *pnlAttach;
	TPanel *pnlAttachM;
	TScrollBox *ScrollBox1;
	TPanel *pnlAttach01;
	TPanel *pnlAttachPath01;
	TImage *btnAttach01;
	TImage *btnAttachDel01;
	TEdit *edtAttachPath01;
	TPanel *pnlAttachAdd01;
	TImage *btnAttachAdd01;
	TPanel *pnlAttachNo01;
	TPanel *pnlAttachNm01;
	TEdit *edtAttachNm01;
	TPanel *pnlAttach02;
	TPanel *pnlAttachPath02;
	TImage *btnAttach02;
	TImage *btnAttachDel02;
	TEdit *edtAttachPath02;
	TPanel *pnlAttachAdd02;
	TImage *btnAttachAdd02;
	TPanel *pnlAttachNo02;
	TPanel *pnlAttachNm02;
	TEdit *edtAttachNm02;
	TPanel *pnlAttach03;
	TPanel *pnlAttachPath03;
	TImage *btnAttach03;
	TImage *btnAttachDel03;
	TEdit *edtAttachPath03;
	TPanel *pnlAttachAdd03;
	TImage *btnAttachAdd03;
	TPanel *pnlAttachNo03;
	TPanel *pnlAttachNm03;
	TEdit *edtAttachNm03;
	TPanel *pnlAttach04;
	TPanel *pnlAttachPath04;
	TImage *btnAttach04;
	TImage *btnAttachDel04;
	TEdit *edtAttachPath04;
	TPanel *pnlAttachAdd04;
	TImage *btnAttachAdd04;
	TPanel *pnlAttachNo04;
	TPanel *pnlAttachNm04;
	TEdit *edtAttachNm04;
	TPanel *pnlAttach05;
	TPanel *pnlAttachPath05;
	TImage *btnAttach05;
	TImage *btnAttachDel05;
	TEdit *edtAttachPath05;
	TPanel *pnlAttachAdd05;
	TImage *btnAttachAdd05;
	TPanel *pnlAttachNo05;
	TPanel *pnlAttachNm05;
	TEdit *edtAttachNm05;
	TPanel *pnlAttach06;
	TPanel *pnlAttachPath06;
	TImage *btnAttach06;
	TImage *btnAttachDel06;
	TEdit *edtAttachPath06;
	TPanel *pnlAttachAdd06;
	TImage *btnAttachAdd06;
	TPanel *pnlAttachNo06;
	TPanel *pnlAttachNm06;
	TEdit *edtAttachNm06;
	TPanel *pnlAttach07;
	TPanel *pnlAttachPath07;
	TImage *btnAttach07;
	TImage *btnAttachDel07;
	TEdit *edtAttachPath07;
	TPanel *pnlAttachAdd07;
	TImage *btnAttachAdd07;
	TPanel *pnlAttachNo07;
	TPanel *pnlAttachNm07;
	TEdit *edtAttachNm07;
	TPanel *pnlAttach08;
	TPanel *pnlAttachPath08;
	TImage *btnAttach08;
	TImage *btnAttachDel08;
	TEdit *edtAttachPath08;
	TPanel *pnlAttachAdd08;
	TImage *btnAttachAdd08;
	TPanel *pnlAttachNo08;
	TPanel *pnlAttachNm08;
	TEdit *edtAttachNm08;
	TPanel *pnlAttach09;
	TPanel *pnlAttachPath09;
	TImage *btnAttach09;
	TImage *btnAttachDel09;
	TEdit *edtAttachPath09;
	TPanel *pnlAttachAdd09;
	TImage *btnAttachAdd09;
	TPanel *pnlAttachNo09;
	TPanel *pnlAttachNm09;
	TEdit *edtAttachNm09;
	TPanel *pnlAttach10;
	TPanel *pnlAttachPath10;
	TImage *btnAttach10;
	TImage *btnAttachDel10;
	TEdit *edtAttachPath10;
	TPanel *pnlAttachAdd10;
	TImage *btnAttachAdd10;
	TPanel *pnlAttachNo10;
	TPanel *pnlAttachNm10;
	TEdit *edtAttachNm10;
	TPanel *pnlAttachT;
	TPanel *pnlAttchT0;
	TPanel *pnlAttchT2;
	TPanel *pnlAttchT3;
	TPanel *pnlAttchT4;
	TPanel *pnlAttchT1;
	TPanel *pnlBottom;
	TImage *btnList;
	TImage *btnRegist;
	TPanel *pnlRegist;
	TPanel *pnlRegistR;
	TPanel *pnlSurv;
	TPanel *pnlSurvT;
	TPanel *pnlSurvD;
	TImage *btnSurvDt;
	TImage *btnSurvDel;
	TEdit *edtSurvDt;
	TPanel *pnlScale;
	TPanel *pnlScaleT;
	TPanel *pnlScaleD;
	TComboBox *cboScale;
	TPanel *pnlEtc;
	TPanel *pnlEtcT;
	TPanel *pnlEtcD;
	TEdit *edtEtc;
	TPanel *pnlLand;
	TPanel *pnlLandT;
	TPanel *pnlLandD;
	TImage *btnFind;
	TEdit *edtUmdRiCd;
	TPanel *pnlBlank;
	TPanel *pnlBlankT;
	TPanel *pnlBlankD;
	TPanel *pnlRegistT;
	TPanel *pnlRegistL;
	TPanel *pnlSidoSgg;
	TPanel *pnlSidoSggT;
	TPanel *pnlSidoSggD;
	TEdit *edtSidoCd;
	TPanel *pnlPnu;
	TPanel *pnlPnuT;
	TPanel *pnlPnuD;
	TLabel *lblPnuMid;
	TComboBox *cboGbn;
	TEdit *edtBonbun;
	TEdit *edtBoobun;
	TPanel *pnlInspct;
	TPanel *pnlInspctT;
	TPanel *pnlInspctD;
	TImage *btnInspctDt;
	TImage *btnInspctDel;
	TEdit *edtInspctDt;
	TPanel *pnlResult;
	TPanel *pnlResultT;
	TPanel *pnlResultD;
	TEdit *edtResult;
	TPanel *pnlGbn;
	TPanel *pnlGbnT;
	TPanel *pnlGbnD;
	TRadioButton *rbGbn2;
	TRadioButton *rbGbn1;
	TPanel *pnlR;
	TMonthCalendar *clndInspctDt01;
	TMonthCalendar *clndInspctDt02;
	TMonthCalendar *clndSurvDt01;
	TMonthCalendar *clndSurvDt02;
	TPanel *pnlLQ;
	TPanel *pnlMainQ;
	TPanel *pnlQuery;
	TPanel *pnlQList;
	TStringGrid *sgList;
	TPanel *pnlMid;
	TLabel *lblQryCnt;
	TLabel *lblQryCntT;
	TPanel *pnlKeyword;
	TPanel *pnlKeywordR;
	TPanel *pnlGbnQ;
	TPanel *pnlBtn;
	TImage *btnInit;
	TPanel *pnlKeywordT;
	TPanel *pnlKeywordL;
	TPanel *pnlSidoSggQ;
	TPanel *pnlSidoSggTQ;
	TPanel *pnlSidoSggDQ;
	TEdit *edtSidoCdQ;
	TPanel *pnlPnuQ;
	TPanel *pnlPnuTQ;
	TPanel *pnlPnuDQ;
	TLabel *lblPnuMidQ;
	TComboBox *cboGbnQ;
	TEdit *edtBonbunQ;
	TEdit *edtBoobunQ;
	TPanel *pnlSurv1;
	TPanel *pnlSurvT1;
	TPanel *pnlSurvD1;
	TImage *btnSurvDel01;
	TLabel *lblSurvMid;
	TImage *btnSurvDt01;
	TImage *btnSurvDt02;
	TImage *btnSurvDel02;
	TEdit *edtSurvDt01;
	TEdit *edtSurvDt02;
	TPanel *pnlInspctQ;
	TPanel *pnlInspctTQ;
	TPanel *pnlInspctDQ;
	TLabel *lblInspctMid;
	TImage *btnInspctDt01;
	TImage *btnInspctDel01;
	TImage *btnInspctDt02;
	TImage *btnInspctDel02;
	TEdit *edtInspctDt01;
	TEdit *edtInspctDt02;
	TPanel *pnlDetail;
	TPanel *pnlView;
	TPanel *pnlTitleV;
	TPanel *pnlList01;
	TPanel *pnlSidoSggV;
	TPanel *pnlSidoSggTV;
	TPanel *pnlSidoSggDV;
	TLabel *lblSidoSgg;
	TPanel *pnlLandV;
	TPanel *pnlLandTV;
	TPanel *pnlLandDV;
	TLabel *lblLand;
	TPanel *pnlList02;
	TPanel *pnlPnuV;
	TPanel *pnlPnuTV;
	TPanel *pnlPnuDV;
	TLabel *lblPnu;
	TPanel *pnlResultV;
	TPanel *pnlResultTV;
	TPanel *pnlResultDV;
	TLabel *lblResult;
	TPanel *pnlList03;
	TPanel *pnlScaleV;
	TPanel *pnlScaleTV;
	TPanel *pnlScaleDV;
	TLabel *lblScale;
	TPanel *pnlSurvDtV;
	TPanel *pnlSurvDtTV;
	TPanel *pnlSurvDtDV;
	TLabel *lblSurv;
	TPanel *pnlList04;
	TPanel *pnlFileNm;
	TPanel *pnlFileNmT;
	TPanel *pnlFileNmD;
	TPanel *pnlFileNmDwn;
	TImage *btnDownload01;
	TImage *btnDownload06;
	TImage *btnDownload07;
	TImage *btnDownload08;
	TImage *btnDownload09;
	TImage *btnDownload10;
	TImage *btnDownload02;
	TImage *btnDownload03;
	TImage *btnDownload04;
	TImage *btnDownload05;
	TPanel *pnlFileName;
	TLabel *lblFileNm01;
	TLabel *lblFileNm02;
	TLabel *lblFileNm03;
	TLabel *lblFileNm04;
	TLabel *lblFileNm05;
	TLabel *lblFileNm06;
	TLabel *lblFileNm07;
	TLabel *lblFileNm08;
	TLabel *lblFileNm09;
	TLabel *lblFileNm10;
	TPanel *pnlFileNmDel;
	TImage *btnFileDel01;
	TImage *btnFileDel02;
	TImage *btnFileDel03;
	TImage *btnFileDel04;
	TImage *btnFileDel05;
	TImage *btnFileDel06;
	TImage *btnFileDel07;
	TImage *btnFileDel08;
	TImage *btnFileDel09;
	TImage *btnFileDel10;
	TPanel *pnlBottomQ;
	TImage *btnDel;
	TImage *btnMod;
	TPanel *pnlRQ;
	TImage *btnQuery;
	TPanel *pnlLandQ;
	TPanel *pnlLandTQ;
	TPanel *pnlLandDQ;
	TImage *btnFindQ;
	TEdit *edtUmdRiCdQ;
	TEdit *edtUmdRiNmQ;
	TPanel *pnlResultQ;
	TPanel *pnlResultTQ;
	TPanel *pnlResultDQ;
	TEdit *edtResultQ;
	TImage *btnWrite;
	TPanel *pnlBQ;
	TPanel *Panel2;
	TPanel *panelWait;
	TImage *imgWait;
	TLabel *lblLoading;
	TEdit *edtUmdRiNm;
	TRadioButton *rbGbn3;
	TPanel *pnlRegistD;
	TPanel *pnlGbnDQ;
	TPanel *pnlGbnTQ;
	TRadioButton *rbGbnQ3;
	TRadioButton *rbGbnQ1;
	TRadioButton *rbGbnQ2;
	TImage *btnCloseTypeB;
	TLabel *lblSort;
	TComboBox *cboSort;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btnQueryClick(TObject *Sender);
	void __fastcall btnInitClick(TObject *Sender);
	void __fastcall sgListDblClick(TObject *Sender);
	void __fastcall edtMaxKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtBox_OnExit(TObject *Sender);
	void __fastcall edtBox_OnEnter(TObject *Sender);
	void __fastcall edtMaxChange(TObject *Sender);
	void __fastcall edtUmdRiCdExit(TObject *Sender);
	void __fastcall btnSurvDt01Click(TObject *Sender);
	void __fastcall btnSurvDt02Click(TObject *Sender);
	void __fastcall btnInspctDt01Click(TObject *Sender);
	void __fastcall btnInspctDt02Click(TObject *Sender);
	void __fastcall clndSurvDt01DblClick(TObject *Sender);
	void __fastcall clndSurvDt02DblClick(TObject *Sender);
	void __fastcall clndInspctDt01DblClick(TObject *Sender);
	void __fastcall clndInspctDt02DblClick(TObject *Sender);
	void __fastcall clndMouseLeave(TObject *Sender);
	void __fastcall edtBoobunQExit(TObject *Sender);
	void __fastcall edtUmdRiCdQExit(TObject *Sender);
	void __fastcall btnModClick(TObject *Sender);
	void __fastcall btnDelClick(TObject *Sender);
	void __fastcall btnDownloadClick(TObject *Sender);
	void __fastcall btnFileDelClick(TObject *Sender);
	void __fastcall sgListClick(TObject *Sender);
	void __fastcall btnClndDelClick(TObject *Sender);
	void __fastcall btnCloseTypeBClick(TObject *Sender);
	//
	void __fastcall btnListClick(TObject *Sender);
	void __fastcall btnRegistClick(TObject *Sender);
	void __fastcall btnFindClick(TObject *Sender);
	void __fastcall btnAttachClick(TObject *Sender);
	void __fastcall btnAttachDelClick(TObject *Sender);
	void __fastcall btnAttachAddClick(TObject *Sender);
	void __fastcall btnInspctDtClick(TObject *Sender);
	void __fastcall btnSurvDtClick(TObject *Sender);
	void __fastcall clndInspctDtRDblClick(TObject *Sender);
	void __fastcall clndSurvDtRDblClick(TObject *Sender);
	void __fastcall edtBoobunExit(TObject *Sender);
	void __fastcall btnModMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall btnModMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall btnDelMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnDelMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnDownloadMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnDownloadMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnFindQMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnFindQMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnQueryMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnQueryMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnInitMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnInitMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnFileDelMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnFileDelMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	//
	void __fastcall btnAttachAddMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnAttachAddMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnFindMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnFindMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnListMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnListMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnRegistMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnRegistMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnAttachMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnAttachMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall btnWriteMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnWriteMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnWriteClick(TObject *Sender);
	void __fastcall btnFindQClick(TObject *Sender);
	void __fastcall PageControl1Change(TObject *Sender);
	void __fastcall PageControl1Changing(TObject *Sender, bool &AllowChange);
	void __fastcall panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall funcRegistKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall funcQueryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall sgListDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall cboSortClick(TObject *Sender);

private:	// User declarations

	int         m_nDocNameMaxLen;//maxlength : 60
	int         m_nEtcMemoMaxLen;//maxlength : 100
	int         m_nPathMaxLen;//maxlength : 255
	bool		m_bMaxLength;//edit 글자수 제한에 사용.

	bool		bRegistMode;//등록중인지 체크하기 위함.
	int			nAttachCnt;
	int 		nMaxCdkeySub;//파일 추가/삭제를 반복하면 Sub값이 증가하므로 수정상태>파일추가 시 필요.

	AnsiString  m_asOpenFileDir;//프로그램 종료시까지 선택한 파일오픈 폴더 갖고 있기////190911//44760//req


public:		// User declarations

	vector<SURVEY_ADDINFO_STRUCT> m_vSurveyAddInfo;
	vector<SURVEY_ADDFILE_STRUCT> m_vSurveyAddFile;

	AnsiString m_asRegistCdKey;
	AnsiString m_asCurrDay;//현재 포커싱 된 regist_cdkey의 날짜//
	int        m_nFileCnt;


	AnsiString m_asRegistNo;
//	AnsiString m_asSelectedFullFileName;
	int        m_nSgListIndex;
	bool	   m_bQrySurvDt;
	bool	   m_bQryInspctDt;

	Graphics::TBitmap *BITMAP_BTN_CLOSE22;//22x22, btnClose.png
	Graphics::TBitmap *BITMAP_02ATTACH_BTN_FIND[2];
	Graphics::TBitmap *BITMAP_02ATTACH_BTN_QUERY[2];
	Graphics::TBitmap *BITMAP_02ATTACH_BTN_INIT[2];
	Graphics::TBitmap *BITMAP_02ATTACH_BTN_DOWNLOAD[2];
	Graphics::TBitmap *BITMAP_02ATTACH_BTN_LIST[2];
	Graphics::TBitmap *BITMAP_02ATTACH_BTN_REGIST[2];

	Graphics::TBitmap *BITMAP_02ATTACH_BTN_MODIFY[3];
	Graphics::TBitmap *BITMAP_02ATTACH_BTN_DELETE[3];
	Graphics::TBitmap *BITMAP_02ATTACH_BTN_ATTACH[3];
	Graphics::TBitmap *BITMAP_02ATTACH_BTN_ADD[3];

	void __fastcall funcLoadButtonImage();
	void __fastcall funcDeleteButtonImage();

	void __fastcall funcInitVariables();
	void __fastcall funcLoadData();

	void __fastcall funcInitVariablesQuery();
	void __fastcall funcInitVariablesDetail();
	void __fastcall funcLoadDataDetail();
	void __fastcall funcInitPanelFileNm();
	void __fastcall funcRedrawPanelFileNm();

	void __fastcall InitDBGrid();
	void __fastcall DisplayDBGrid();

	AnsiString __fastcall funcUploadAttach(int _nIndex);

	//파일용량구하기
	__int64 __fastcall GetLocalFileSize(AnsiString _asFileName);
	void __fastcall funcCheckDate();
	bool __fastcall funcDeleteFile(int _nTag);
	bool __fastcall funcCheckEditText();

	//FTP upload/download/delete
	void __fastcall funcSetWaitWindows(bool bSetValue);

	//등록화면에 변경된 내용이 있는지 체크
	bool __fastcall funcCheckWroteData();

	__fastcall Tfrm02Attach(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm02Attach *frm02Attach;
//---------------------------------------------------------------------------
#endif
