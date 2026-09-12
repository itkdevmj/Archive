//---------------------------------------------------------------------------

#ifndef untResultList2H
#define untResultList2H
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
class TfrmResultList2 : public TForm
{
__published:	// IDE-managed Components
	TIdDecoderMIME *IdDecoderMIME1;
	TShape *shpBG;
	TPanel *pnlMain;
	TPanel *pnlOwnInfoT1;
	TPanel *pnlOwnInfoD1;
	TAdvStringGrid *sgShareOwn1;
	TPanel *pnlOwnInfo1;
	TLabel *lblPosOwnInfo1;
	TActionList *ActionList1;
	TAction *ActionSave;
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
	TShape *Shape1;
	TAction *ActionLoadText;
	TAction *ActionSaveTemp;
	TLabel *lblEra1;
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
	TAction *ActionLoadShareOwn;
	TAction *ActionSaveOwnInfo;
	TPanel *pnlOwnInfoNo1;
	TLabel *lblNoOwnInfo1;
	TAction *ActionDate11;
	TAction *ActionDate12;
	TAction *ActionEmpty;
	TPanel *pnlOwnInfo2;
	TPanel *pnlOwnInfoD2;
	TPanel *pnlOwnInfoT2;
	TLabel *lblEra2;
	TPanel *pnlOwnInfoNo2;
	TLabel *lblPosOwnInfo2;
	TLabel *lblNoOwnInfo2;
	TAdvStringGrid *sgShareOwn2;
	TShape *Shape2;
	TAction *ActionShort8;
	TPanel *pnlTitle;
	TPanel *pnlJibunT;
	TPanel *pnlJibun1;
	TLabel *lblJibun1;
	TPanel *pnlJibun;
	TPanel *Panel3;
	TPanel *pnlPnuInfoT;
	TLabel *lblFormat;
	TLabel *lblJibun;
	TLabel *lblJibunOK;
	TLabel *lblLevel;
	TLabel *lblMemo;
	TLabel *lblMemo1;
	TLabel *lblMemo2;
	TShape *Shape4;
	TCheckBox *chkFormat;
	TCheckBox *chkJibunOK;
	TEdit *edtDoho;
	TEdit *edtLevel;
	TEdit *edtMemo;
	TEdit *edtPnu;
	TPanel *Panel2;
	TPanel *Panel5;
	TPanel *pnlJubinHelp;
	TPanel *pnlButton;
	TbsSkinButton *btnSave;
	TImage *btnHistory;
	TLabel *lblWrite;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btnSaveClick(TObject *Sender);
	void __fastcall edtHangeulEnter(TObject *Sender);
	void __fastcall sgShareOwn1ClickCell(TObject *Sender, int ARow, int ACol);
	void __fastcall sgShareOwn1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall lblJibunOKClick(TObject *Sender);
	void __fastcall ActionSaveExecute(TObject *Sender);
	void __fastcall sgShareOwn1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall cboEraKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall sgShareOwnExit(TObject *Sender);
	void __fastcall ActionEraExecute(TObject *Sender);
	void __fastcall ActionReasonExecute(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall edtKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall ActionDateExecute(TObject *Sender);
	void __fastcall ActionLoadShareOwnExecute(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall btnSave1MouseEnter(TObject *Sender);
	void __fastcall ActionEmptyExecute(TObject *Sender);
	void __fastcall sgShareOwnMouseLeave(TObject *Sender);
	void __fastcall pnlPnuInfoTMouseLeave(TObject *Sender);
	void __fastcall ActionShortExecute(TObject *Sender);
	void __fastcall sgShareOwn2ClickCell(TObject *Sender, int ARow, int ACol);
	void __fastcall sgShareOwn2KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall sgShareOwn2KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall chkFormatClick(TObject *Sender);
	void __fastcall lblFormatClick(TObject *Sender);
	void __fastcall btnHistoryClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);

private:	// User declarations

public:		// User declarations

	//==================================================================
	classDOC08Data			*eData;

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
	TColor					COLOR_INPUT_BG;//입력화면 교대로 표시되는 배경화면//
	TColor					COLOR_HEADER_BG;
	bool					m_INI_EMPTY;// '빈칸' 텍스트 및 배경색 표시 여부(1:표시, 0:미표시<Default>//

	int                     m_nShareOwnInputCount;

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
	bool						m_bShareOwnEditing1;
	bool						m_bShareOwnEditing2;
	bool						m_bSaved;
	//======================================================================

	//-----------------------------------------------------------------------
	AnsiString					m_asSaveFileDir;//파일 저장시 디렉토리(기본:DOWNLOAD, 사용자변경DIR)

	//Qry Error 시 SQL Query 저장//
	AnsiString					m_asQryToSave;
	void __fastcall 			funcSaveQry(AnsiString  _asType);

	bool						m_bSaving;//저장중//

	void __fastcall 			funcCheckRegStr();


//=============================================================================
//v1.0.0.1//#SHAREOWN#//
	int							m_nRightCount;//오른쪽면 Cell 개수//
	int							m_nPageCount;//윗쪽, 아랫쪽 각각 Cell 개수//
	void __fastcall 			funcCheckResultListClick();
//=============================================================================


	//=========================================================================
	//241111//#구대장한글편집#DirectTable//
	//=========================================================================
	void __fastcall 			funcDisplayDirectWriteInfo();


	//=========================================================================
	//260611//AIOCR결과 DB저장(자동)//
	//_bAlert (true: 버튼클릭 수동 저장, false: 자동 저장)
	//=========================================================================
	void __fastcall 			funcSaveDBData(bool _bAlert);


	__fastcall TfrmResultList2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmResultList2 *frmResultList2;
//---------------------------------------------------------------------------
#endif
