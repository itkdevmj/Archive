//---------------------------------------------------------------------------

#ifndef untRegistH
#define untRegistH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <printers.hpp>
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "BaseGrid.hpp"
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TfrmRegist : public TForm
{
__published:	// IDE-managed Components
	TPanel *pnlData;
	TImage *Image1;
	TPanel *panWindowsMove;
	TImage *btnCloseTypeB;
	TPanel *pnlDataM;
	TPanel *Panel4;
	TPanel *pnlBlankL;
	TPanel *pnlBlankR;
	TPanel *pnlTitle;
	TAdvStringGrid *sgResult;
	TPanel *Panel1;
	TLabel *lblFormTitle;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnCloseTypeBMouseEnter(TObject *Sender);
	void __fastcall btnCloseTypeBMouseLeave(TObject *Sender);
	void __fastcall btnCloseTypeBMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall sgResultGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign, TVAlignment &VAlign);
	void __fastcall btnCloseTypeBClick(TObject *Sender);

private:	// User declarations
	TColor colorError;

public:		// User declarations

	void __fastcall funcInitStringGrid();
	void __fastcall funcDispStringGrid();

	__fastcall TfrmRegist(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRegist *frmRegist;
//---------------------------------------------------------------------------
#endif
