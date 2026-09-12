//---------------------------------------------------------------------------

#ifndef unt01AttachH
#define unt01AttachH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "BaseGrid.hpp"
#include <Grids.hpp>
#include <pngimage.hpp>
//---------------------------------------------------------------------------
class Tfrm01Attach : public TForm
{
__published:	// IDE-managed Components
	TPanel *pnl01Attach;
	TPanel *panWindowsMove;
	TLabel *lblFormTitle;
	TPanel *pnlClose;
	TImage *btnCloseTypeB;
	TPageControl *PageControl1;
	TTabSheet *tabRegist;
	TTabSheet *tabQuery;
	TFileSaveDialog *FileSaveDialog1;
	TOpenDialog *OpenDialog1;
	TMonthCalendar *clndPrcsDtR;
	TPanel *pnlL;
	TPanel *pnlMainR;
	TPanel *pnlAttach;
	TPanel *pnlBottom;
	TImage *btnList;
	TImage *btnRegist;
	TPanel *pnlRegist;
	TPanel *pnlRegistR;
	TPanel *pnlEtc;
	TPanel *pnlEtcT;
	TPanel *pnlEtcD;
	TEdit *edtEtc;
	TPanel *pnlLand;
	TPanel *pnlLandT;
	TPanel *pnlLandD;
	TImage *btnFind;
	TEdit *edtUmdRiCd;
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
	TPanel *pnlPrcs;
	TPanel *pnlInspctT;
	TPanel *pnlPrcsD;
	TImage *btnPrcsDt;
	TImage *btnPrcsDel;
	TEdit *edtPrcsDt;
	TPanel *pnlGbn;
	TPanel *pnlGbnT;
	TPanel *pnlGbnD;
	TPanel *pnlR;
	TMonthCalendar *clndPrcsDt01;
	TMonthCalendar *clndPrcsDt02;
	TPanel *pnlLQ;
	TPanel *pnlMainQ;
	TPanel *pnlQuery;
	TPanel *pnlQList;
	TPanel *pnlMid;
	TPanel *pnlKeyword;
	TPanel *pnlKeywordR;
	TPanel *pnlMeasureTypeQ;
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
	TPanel *pnlPrcs1;
	TPanel *pnlPrcsTQ;
	TPanel *pnlPrcsDQ;
	TImage *btnPrcsDel01;
	TLabel *lblPrcsMid;
	TImage *btnPrcsDt01;
	TImage *btnPrcsDt02;
	TImage *btnPrcsDel02;
	TEdit *edtPrcsDt01;
	TEdit *edtPrcsDt02;
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
	TPanel *pnlMeasureTypeV;
	TPanel *pnlMeasureTypeTV;
	TPanel *pnlMeasureTypeDV;
	TLabel *lblMeasureType;
	TPanel *pnlPrcsDtV;
	TPanel *pnlPrcsDtTV;
	TPanel *pnlPrcsDtDV;
	TLabel *lblPrcs;
	TPanel *pnlList04;
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
	TPanel *pnlRegistD;
	TPanel *pnlMeasureTypeDQ;
	TPanel *pnlMeasureTypeTQ;
	TComboBox *cboMeasureType;
	TPanel *Panel1;
	TAdvStringGrid *sgAddFileList;
	TPanel *pnlBlankQ;
	TPanel *pnlBlankTQ;
	TPanel *pnlBlankDQ;
	TComboBox *cboMeasureTypeQ;
	TPanel *pnlResult;
	TPanel *pnlResultT;
	TPanel *pnlResultD;
	TEdit *edtResult;
	TComboBox *cboKindCode;
	TScrollBox *ScrollBox1;
	TPanel *pnlFileNm;
	TPanel *pnlFileNmT;
	TPanel *pnlFileNmD;
	TPanel *pnlFileNmDwn;
	TPanel *pnlFileName;
	TPanel *pnlFileNmDel;
	TPanel *pnlFileNmKind;
	TAdvStringGrid *sgList;
	TLabel *lblQryCntT;
	TLabel *lblQryCnt;
	TComboBox *cboSort;
	TLabel *lblSort;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btnQueryClick(TObject *Sender);
	void __fastcall btnInitClick(TObject *Sender);
	void __fastcall edtMaxKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtBox_OnExit(TObject *Sender);
	void __fastcall edtBox_OnEnter(TObject *Sender);
	void __fastcall edtMaxChange(TObject *Sender);
	void __fastcall edtUmdRiCdExit(TObject *Sender);
	void __fastcall btnPrcsDt01Click(TObject *Sender);
	void __fastcall btnPrcsDt02Click(TObject *Sender);
	void __fastcall clndPrcsDt01DblClick(TObject *Sender);
	void __fastcall clndPrcsDt02DblClick(TObject *Sender);
	void __fastcall clndMouseLeave(TObject *Sender);
	void __fastcall edtBoobunQExit(TObject *Sender);
	void __fastcall edtUmdRiCdQExit(TObject *Sender);
	void __fastcall btnModClick(TObject *Sender);
	void __fastcall btnDelClick(TObject *Sender);
	void __fastcall btnDownloadClick(TObject *Sender);
	void __fastcall btnFileDelClick(TObject *Sender);
	void __fastcall btnClndDelClick(TObject *Sender);
	void __fastcall btnCloseTypeBClick(TObject *Sender);
	//
	void __fastcall btnListClick(TObject *Sender);
	void __fastcall btnRegistClick(TObject *Sender);
	void __fastcall btnFindClick(TObject *Sender);
	void __fastcall btnAttachClick(TObject *Sender);
	void __fastcall btnAttachDelClick(TObject *Sender);
	void __fastcall btnPrcsDtClick(TObject *Sender);
	void __fastcall clndPrcsDtRDblClick(TObject *Sender);
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
	void __fastcall sgAddFileListClickCell(TObject *Sender, int ARow, int ACol);
	void __fastcall sgAddFileListDblClickCell(TObject *Sender, int ARow, int ACol);
	void __fastcall sgAddFileListGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign, TVAlignment &VAlign);
	void __fastcall sgAddFileListHasComboBox(TObject *Sender, int ACol, int ARow, bool &HasComboBox);
	void __fastcall sgAddFileListSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall sgAddFileListGetEditorType(TObject *Sender, int ACol, int ARow, TEditorType &AEditor);
	void __fastcall cboKindCodeClick(TObject *Sender);
	void __fastcall sgAddFileListDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State);
	void __fastcall sgListClick(TObject *Sender);
	void __fastcall sgListDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State);
	void __fastcall sgListDblClick(TObject *Sender);
	void __fastcall cboSortClick(TObject *Sender);

private:	// User declarations

	int         m_nDocNameMaxLen;//maxlength : 60
	int         m_nEtcMemoMaxLen;//maxlength : 100
	int         m_nPathMaxLen;//maxlength : 255
	bool		m_bMaxLength;//edit 글자수 제한에 사용.

	bool		bRegistMode;//등록중인지 체크하기 위함.
	int			nAttachCnt;
	bool 		m_bChanged;//파일 변경한 것이 있음.
	int  		m_nChangedIndex;//미등록 파일 index
	int 		nMaxCdkeySub;//파일 추가/삭제를 반복하면 Sub값이 증가하므로 수정상태>파일추가 시 필요.

	AnsiString  m_asOpenFileDir;//프로그램 종료시까지 선택한 파일오픈 폴더 갖고 있기////190911//44760//req


public:		// User declarations

	Graphics::TBitmap *btnAttach;
	Graphics::TBitmap *btnDownload;
	Graphics::TBitmap *btnDelete;


	vector<ATTACH_INFO_DOC01_STRUCT> m_vAttachInfoDoc01;
	vector<ATTACH_FILE_DOC01_STRUCT> m_vAttachFileDoc01;

	AnsiString m_asRegistCdKey;
	AnsiString m_asCurrDay;//현재 포커싱 된 regist_cdkey의 날짜//
	int        m_nFileCnt;


	AnsiString m_asRegistNo;
//	AnsiString m_asSelectedFullFileName;
	int        m_nSgListIndex;
	bool	   m_bQryPrcsDt;

	Graphics::TBitmap *BITMAP_BTN_CLOSE22;//22x22, btnClose.png
	Graphics::TBitmap *BITMAP_01ATTACH_BTN_FIND[2];
	Graphics::TBitmap *BITMAP_01ATTACH_BTN_QUERY[2];
	Graphics::TBitmap *BITMAP_01ATTACH_BTN_INIT[2];
	Graphics::TBitmap *BITMAP_01ATTACH_BTN_DOWNLOAD[2];
	Graphics::TBitmap *BITMAP_01ATTACH_BTN_LIST[2];
	Graphics::TBitmap *BITMAP_01ATTACH_BTN_REGIST[2];

	Graphics::TBitmap *BITMAP_01ATTACH_BTN_MODIFY[3];
	Graphics::TBitmap *BITMAP_01ATTACH_BTN_DELETE[3];
	Graphics::TBitmap *BITMAP_01ATTACH_BTN_ATTACH[3];
	Graphics::TBitmap *BITMAP_01ATTACH_BTN_ADD[3];

	void __fastcall funcLoadButtonImage();
	void __fastcall funcDeleteButtonImage();

	void __fastcall funcInitVariables();
	void __fastcall funcLoadData();

	void __fastcall funcInitVariablesQuery();
	void __fastcall funcInitVariablesDetail();
	void __fastcall funcLoadDataDetail();
	void __fastcall funcLoadDataAttach();
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

	//파일첨부//문서구분//콤보리스트//
	void __fastcall funcSetComboList();
	void __fastcall InitAttachDBGrid();
	void __fastcall DisplayAttachDBGrid();
	void __fastcall funcDeleteSelectFile(int _nIndex);

	TRect cboRect;//문서종류 선택 콤보박스//
	void __fastcall sgAddFileListCombobox_OnClick(TObject *Sender);

	TList 		*imgDownList;
	TList 		*imgDelList;
	TList 		*lblKindList;
	TList 		*lblFileList;
	int			m_nCompCnt;
    void __fastcall funcCreateComponents(AnsiString _asKindName, AnsiString _asFileName);


	__fastcall Tfrm01Attach(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm01Attach *frm01Attach;
//---------------------------------------------------------------------------
#endif
