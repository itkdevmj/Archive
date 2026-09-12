//---------------------------------------------------------------------------

#ifndef untResultListH
#define untResultListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Grids.hpp>
#include <jpeg.hpp>
#include "IdBaseComponent.hpp"
#include "IdCoder.hpp"
#include "IdCoder3to4.hpp"
#include "IdCoderMIME.hpp"
#include <msxmldom.hpp>
#include <XMLDoc.hpp>
#include <xmldom.hpp>
#include <XMLIntf.hpp>
#include <pngimage.hpp>
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "BaseGrid.hpp"
#include <ActnList.hpp>
#include "tmsAdvGridExcel.hpp"
#include <Dialogs.hpp>
#include "bsSkinCtrls.hpp"

class classDOC08Data;  // ← 전방 선언 (포인터만 사용 시 OK)
//---------------------------------------------------------------------------
class TfrmResultList : public TForm
{
__published:	// IDE-managed Components
	TIdDecoderMIME *IdDecoderMIME1;
	TShape *shpBG;
	TPanel *pnlMain;
	TPanel *pnlOwnInfoT;
	TPanel *pnlHistoryT;
	TPanel *pnlHistoryD;
	TAdvStringGrid *sgHistory;
	TPanel *pnlOwnInfoD;
	TAdvStringGrid *sgOwnInfo;
	TPanel *pnlHistory;
	TPanel *pnlOwnInfo;
	TLabel *lblPosHistory;
	TLabel *lblPosOwnInfo;
	TActionList *ActionList1;
	TAction *ActionSave;
	TAction *ActionShort1;
	TAction *ActionShort2;
	TAction *ActionShort3;
	TAction *ActionShort4;
	TAction *ActionShort5;
	TAction *ActionShort6;
	TAction *ActionHistory1;
	TAction *ActionHistory2;
	TAction *ActionHistory3;
	TAction *ActionHistory4;
	TAction *ActionHistory5;
	TAction *ActionHistory6;
	TAction *ActionEra1;
	TAction *ActionEra2;
	TAction *ActionEra3;
	TAction *ActionEra4;
	TAction *ActionReason1;
	TAction *ActionReason2;
	TAction *ActionReason3;
	TAction *ActionReason4;
	TAction *ActionReason5;
	TAction *ActionReason6;
	TAction *ActionHistory7;
	TAction *ActionHistory8;
	TAction *ActionHistory9;
	TAction *ActionHistory10;
	TAction *ActionHistory11;
	TAction *ActionSaveText;
	TAdvGridExcelIO *AdvGridExcelIO1;
	TAdvGridExcelIO *AdvGridExcelIO2;
	TSaveDialog *SaveDialog1;
	TAction *ActionReason7;
	TAction *ActionReason8;
	TAction *ActionPrev;
	TAction *ActionNext;
	TAction *ActionZoomIn;
	TAction *ActionZoomOut;
	TAction *ActionHistory12;
	TShape *Shape1;
	TShape *Shape2;
	TAction *ActionLoadText;
	TAction *ActionHistory13;
	TAction *ActionHistory14;
	TAction *ActionHistory15;
	TAction *ActionHistory16;
	TAction *ActionHistory17;
	TAction *ActionHistory18;
	TAction *ActionSaveTemp;
	TLabel *lblEra;
	TAction *ActionDate1;
	TAction *ActionDate2;
	TAction *ActionDate3;
	TAction *ActionDate4;
	TAction *ActionDate5;
	TAction *ActionDate6;
	TAction *ActionDate7;
	TAction *ActionDate8;
	TAction *ActionDate9;
	TAction *ActionDate10;
	TAction *ActionLoadOwnInfo;
	TAction *ActionLoadHistory;
	TAction *ActionSaveHistory;
	TAction *ActionSaveOwnInfo;
	TAction *ActionShort7;
	TLabel *lblNoHistory;
	TPanel *pnlOwnInfoT1;
	TLabel *lblNoOwnInfo;
	TAction *ActionDate11;
	TAction *ActionDate12;
	TPanel *Panel1;
	TMemo *Memo1;
	TPanel *pnlTitle;
	TPanel *pnlJibunT;
	TPanel *pnlJibun1;
	TLabel *lblJibun1;
	TPanel *pnlJibun;
	TCheckBox *chkAreaChange;
	TPanel *Panel3;
	TPanel *pnlPnuInfoT;
	TLabel *lblJibunOK;
	TLabel *lblJibun;
	TLabel *lblMemo;
	TLabel *lblMemo1;
	TLabel *lblMemo2;
	TLabel *lblLevel;
	TShape *Shape4;
	TCheckBox *chkJibunOK;
	TPanel *Panel2;
	TPanel *Panel5;
	TEdit *edtPnu;
	TPanel *pnlJubinHelp;
	TEdit *edtMemo;
	TEdit *edtDoho;
	TEdit *edtLevel;
	TPanel *pnlButton;
	TbsSkinButton *btnSave;
	TImage *btnHistory;
	TLabel *lblWrite;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btnSaveClick(TObject *Sender);
	void __fastcall edtHangeulEnter(TObject *Sender);
	void __fastcall sgHistoryClickCell(TObject *Sender, int ARow, int ACol);
	void __fastcall sgOwnInfoClickCell(TObject *Sender, int ARow, int ACol);
	void __fastcall sgHistoryKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall sgOwnInfoKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall lblJibunOKClick(TObject *Sender);
	void __fastcall ActionSaveExecute(TObject *Sender);
	void __fastcall sgHistoryKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall sgOwnInfoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cboEraKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall ActionShortExecute(TObject *Sender);
	void __fastcall chkToModifyClick(TObject *Sender);
	void __fastcall sgHistoryExit(TObject *Sender);
	void __fastcall sgOwnInfoExit(TObject *Sender);
	void __fastcall edtKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall chkAreaChangeClick(TObject *Sender);
	void __fastcall btnSaveMouseEnter(TObject *Sender);
	void __fastcall sgHistoryMouseLeave(TObject *Sender);
	void __fastcall sgOwnInfoMouseLeave(TObject *Sender);
	void __fastcall pnlPnuInfoTMouseLeave(TObject *Sender);
	void __fastcall btnHistoryClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);

private:	// User declarations

public:		// User declarations

	//==================================================================
	classDOC08Data			*eData;

	//==================================================================

	//==================================================================
	// 구대장 연혁 & 소유자정보//
	//==================================================================
	GPoint  				m_gPoiJimok;
	GPoint  				m_gPoiArea;
	GPoint  				m_gPoiValue1;
	GPoint  				m_gPoiValue2;
	GPoint  				m_gPoiHistory;
	TPoint  				m_tpPoiJimok;
	TPoint  				m_tpPoiArea;
	TPoint  				m_tpPoiValue1;
	TPoint  			   	m_tpPoiValue2;
	TPoint  			   	m_tpPoiHistory;
	double					m_dImageMoveGap;
	int						m_nHistoryInputCount;
    int                     m_nOwnInfoInputCount;
	TColor					COLOR_INPUT_BG;//입력화면 교대로 표시되는 배경화면//
	TColor					COLOR_HEADER_BG;
	bool					m_INI_EMPTY;// '빈칸' 텍스트 및 배경색 표시 여부(1:표시, 0:미표시<Default>//

	//======================================================================
	void __fastcall 		    funcMoveImage(WORD &Key);

	//구대장>연혁, 소유자정보//
	void _fastcall 				funcInitResultList();
	void _fastcall 				funcDispResultList();
	bool __fastcall 			funcCheckInputData();
	bool __fastcall 			funcExistsToSave();

	//======================================================================
	//콤보리스트//
	//======================================================================
	TRect 								cboRect;//문서종류 선택 콤보박스//

	//======================================================================
	bool						m_bHistoryEditing;
	bool						m_bOwnInfoEditing;
	bool						m_bSaved;
	//======================================================================

	//Qry Error 시 SQL Query 저장//
	AnsiString					m_asQryToSave;
	void __fastcall 			funcSaveQry(AnsiString  _asType);

	bool						m_bSaving;//저장중//

	//=========================================================================
	//241111//#구대장한글편집#DirectTable//
	//=========================================================================
	void __fastcall 			funcDisplayDirectWriteInfo();


	//=========================================================================
	//260611//AIOCR결과 DB저장(자동)//
	//_bAlert (true: 버튼클릭 수동 저장, false: 자동 저장)
	//=========================================================================
	void __fastcall 			funcSaveDBData(bool _bAlert);


	__fastcall TfrmResultList(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmResultList *frmResultList;
//---------------------------------------------------------------------------
#endif
