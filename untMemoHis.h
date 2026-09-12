//---------------------------------------------------------------------------

#ifndef untMemoHisH
#define untMemoHisH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>
#include <pngimage.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TfrmMemoHis : public TForm
{
__published:	// IDE-managed Components
	TPanel *panMain;
	TPanel *panCenter;
	TPanel *panWindowsMove;
	TImage *imgIconTitle;
	TLabel *lblFormTitle;
	TImage *btnCloseTypeB;
	TLabel *lblMemoTitle;
	TPanel *palMainView;
	TLabel *lblCount;
	TLabel *lblPoiName;
	TStringGrid *sgMemoHis;
	TShape *shpBG;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall btnCloseTypeBClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall sgMemoHisDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State);

private:	// User declarations
public:		// User declarations

	void 		__fastcall funcClearForm();

	void 		__fastcall InitDBGrid();
	void 		__fastcall DisplayDBGrid();

	__fastcall TfrmMemoHis(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMemoHis *frmMemoHis;
//---------------------------------------------------------------------------
#endif
