//---------------------------------------------------------------------------

#ifndef untChangeMenuH
#define untChangeMenuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <pngimage.hpp>
#include <stdio.h>
#include <stdlib.h>
//---------------------------------------------------------------------------
class TfrmChangeMenu : public TForm
{
__published:	// IDE-managed Components
	TImage *IMGBG;
	TImage *IMGHEADER;
	TImage *btnCloseTypeB;
	TImage *chkQry01;
	TImage *chkFav01;
	TImage *chkQry02;
	TImage *chkFav02;
	TImage *chkQry03;
	TImage *chkQry04;
	TImage *chkFav04;
	TImage *chkFav03;
	TImage *chkQry06;
	TImage *chkFav06;
	TImage *chkQry07;
	TImage *chkFav07;
	TImage *chkQry08;
	TImage *chkFav08;
	TImage *chkQry09;
	TImage *chkFav09;
	TImage *chkQry11;
	TImage *chkFav11;
	TImage *chkQry15;
	TImage *chkFav15;
	TImage *chkFav17;
	TImage *chkQry17;
	TImage *chkQry18;
	TImage *chkFav18;
	TLabel *lblDoc01;
	TLabel *lblDoc02;
	TLabel *lblDoc03;
	TLabel *lblDoc04;
	TLabel *lblDoc06;
	TLabel *lblDoc07;
	TLabel *lblDoc08;
	TLabel *lblDoc09;
	TLabel *lblDoc11;
	TLabel *lblDoc15;
	TLabel *lblDoc17;
	TLabel *lblDoc18;
	TImage *btnFnd01;
	TImage *btnFnd02;
	TImage *btnFnd03;
	TImage *btnFnd04;
	TImage *btnFnd06;
	TImage *btnFnd07;
	TImage *btnFnd08;
	TImage *btnFnd09;
	TImage *btnFnd11;
	TImage *btnFnd15;
	TImage *btnFnd17;
	TImage *btnFnd18;
	TImage *chkQry20;
	TImage *chkFav20;
	TLabel *lblDoc20;
	TImage *btnFnd20;
	TImage *chkPoi01;
	TImage *chkPoi02;
	TImage *chkPoi04;
	TImage *chkPoi03;
	TImage *chkPoi06;
	TImage *chkPoi07;
	TImage *chkPoi08;
	TImage *chkPoi09;
	TImage *chkPoi11;
	TImage *chkPoi15;
	TImage *chkPoi17;
	TImage *chkPoi18;
	TImage *chkPoi20;
//	void __fastcall BTNUPClick(TObject *Sender);
//	void __fastcall BTNDNClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall btnCloseTypeBClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall IMGHEADERMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnFndClick(TObject *Sender);
	void __fastcall chkQryClick(TObject *Sender);
	void __fastcall chkFavClick(TObject *Sender);
	void __fastcall chkPoiClick(TObject *Sender);
private:	// User declarations
public:		// User declarations

	int				m_nChkQryCnt;
	int				m_nChkFavCnt;//최대5개//
	int				m_nChkPoiCnt;//241120//#DOCPOI#//PNU정보 존재 문서인지 체크할 것//
	int				m_nChkPoiDocNo;//241120//#DOCPOI#//문서심볼 선택한 문서가 1개인 경우, 폴더심볼(iconDocCnt##) 아닌 해당 문서 심볼(iconPoiDoc##)로 표기//
	bool			m_bDetailSearching;//상세검색중//종료 시 멘트해줘야 함//
	int				m_nDetailSearchingIndex;//상세검색중인 메뉴인덱스//종료 시 해제//
	bool			m_bMaxQryCheckMent;//"통합검색 권장 5개까지" 멘트 한번만 처리하자.

//	Graphics::TBitmap *BITMAP_BTN_TABDOC[9][2];
//	Graphics::TBitmap *BITMAP_BTN_TABDN;
//	Graphics::TBitmap *BITMAP_BTN_TABUP;
	Graphics::TBitmap *BITMAP_BTN_CHKBOX[2];
	Graphics::TBitmap *BITMAP_BTN_FIND[2];

	void __fastcall funcLoadButtonImage();
	void __fastcall funcDeleteButtonImage();

//	int  __fastcall funcGetDocumentIndex(AnsiString _asDocName);
//	int  __fastcall funcGetDocPriorityIndex(AnsiString _asDocName);


	void __fastcall funcSettngMenu();


	__fastcall TfrmChangeMenu(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmChangeMenu *frmChangeMenu;
//---------------------------------------------------------------------------
#endif
