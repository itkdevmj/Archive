//---------------------------------------------------------------------------

#ifndef untReleaseListH
#define untReleaseListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
#include <pngimage.hpp>
//---------------------------------------------------------------------------
class TfrmReleaseList : public TForm
{
__published:	// IDE-managed Components
	TPanel *panWindowsMove;
	TListView *lvResult;
	TImage *btnCloseTypeB;
	TImage *Image2;
	TPanel *panCenter;
	TLabel *lblFormTitle;
	TShape *shpBG;
	TCheckBox *chkShow;
	TLabel *lblShow;
	TImage *IMGVIEW;
	TPanel *Panel1;
	TImage *IMGPREV;
	TImage *IMGNEXT;
	TPanel *Panel3;
	TPanel *Panel4;
	TImage *IMGNOIMAGE;
	TLabel *lblCount;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnCloseTypeBClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall chkShowClick(TObject *Sender);
	void __fastcall lvResultClick(TObject *Sender);
	void __fastcall IMGPREVClick(TObject *Sender);
	void __fastcall IMGPREVMouseEnter(TObject *Sender);
	void __fastcall IMGPREVMouseLeave(TObject *Sender);
	void __fastcall IMGNEXTClick(TObject *Sender);
	void __fastcall IMGNEXTMouseEnter(TObject *Sender);
	void __fastcall IMGNEXTMouseLeave(TObject *Sender);


private:	// User declarations

	TIniFile 	*_iniList;

public:		// User declarations

	vector<RELEASELIST_STRUCT>		m_vRELEASELIST;
	vector<RELEASEPATHLIST_STRUCT>  m_vRELEASEPATHLIST;
	int								m_nReleasePathCount;
	int								m_nReleasePathIndex;

	Graphics::TBitmap 			*BITMAP_BTN_PREV[2];
	Graphics::TBitmap 			*BITMAP_BTN_NEXT[2];
	void 		__fastcall  funcLoadButtonImage();
	void 		__fastcall  funcDeleteButtonImage();

	void __fastcall funcGetReleaseList();
	int __fastcall 	funcLoadImage(AnsiString _asVersion);

	void __fastcall funcGetImageList(AnsiString Dir);
	void __fastcall funcGetFileList(AnsiString Dir);


	__fastcall TfrmReleaseList(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmReleaseList *frmReleaseList;
//---------------------------------------------------------------------------
#endif
