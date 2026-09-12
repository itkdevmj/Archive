//---------------------------------------------------------------------------

#ifndef untDoc8HistoryH
#define untDoc8HistoryH
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
#include "bsSkinBoxCtrls.hpp"
#include "bsSkinCtrls.hpp"
#include <DateUtils.hpp>
//---------------------------------------------------------------------------
class TfrmDoc8History : public TForm
{
__published:	// IDE-managed Components
	TPanel *panCenter;
	TPanel *panWindowsMove;
	TLabel *lblFormTitle;
	TImage *btnCloseTypeB;
	TShape *shpBG;
	TAdvStringGrid *sgDoc8History;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnCloseTypeBClick(TObject *Sender);
	void __fastcall panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall sgDoc8HistoryGetAlignment(TObject *Sender, int ARow, int ACol, TAlignment &HAlign, TVAlignment &VAlign);

private:	// User declarations
public:		// User declarations

	void __fastcall funcRefreshShow();
	//####################################################
	// 구대장 한글본 편집 내역//
	//####################################################
	void __fastcall funcCreateDoc8History();
	void __fastcall funcInitDoc8History();
	void __fastcall funcDispDoc8History();


	__fastcall TfrmDoc8History(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDoc8History *frmDoc8History;
//---------------------------------------------------------------------------
#endif
