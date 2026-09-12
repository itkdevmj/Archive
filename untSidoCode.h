//---------------------------------------------------------------------------

#ifndef untSidoCodeH
#define untSidoCodeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <jpeg.hpp>
#include <Buttons.hpp>
#include <Graphics.hpp>
#include <pngimage.hpp>
//---------------------------------------------------------------------------
class TfrmSidoCode : public TForm
{
__published:	// IDE-managed Components
	TEdit *edtInputStr;
	TImage *imgBG;
	TImage *btnCloseTypeB;
	TPanel *panCenter;
	TPanel *panWindowsMove;
	TImage *imgIconTitle;
	TLabel *lblFormTitle;
	TListView *lvResult;
	TLabel *Label2;
	TLabel *Label3;
	TComboBox *cboGbn;
	TEdit *edtBobn;
	TEdit *edtBubn;
	TImage *btnAccept;
	TImage *btnSidoCodeSearch;
	TPanel *pnlBlank;
	TShape *shpBG;
	void __fastcall btnSidoCodeSearchClick(TObject *Sender);
	void __fastcall edtInputStrKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall lvResultDblClick(TObject *Sender);
	void __fastcall panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnCloseTypeBClick(TObject *Sender);
	void __fastcall edtInputStr_OnEnter(TObject *Sender);
	void __fastcall lvResult_OnKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall edtBonBuKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall btnSidoCodeSearchMouseEnter(TObject *Sender);
	void __fastcall btnSidoCodeSearchMouseLeave(TObject *Sender);
	void __fastcall btnAcceptMouseEnter(TObject *Sender);
	void __fastcall btnAcceptMouseLeave(TObject *Sender);
	void __fastcall btnAcceptClick(TObject *Sender);
	void __fastcall FormDeactivate(TObject *Sender);
	void __fastcall cboGbnKeyPress(TObject *Sender, wchar_t &Key);

private:	// User declarations

	AnsiString m_asCode;
	AnsiString m_asName;

    Graphics::TBitmap *BITMAP_BTN_FIND[2];
	Graphics::TBitmap *BITMAP_BTN_ACCEPT[2];

	void __fastcall funcLoadButtonImage();
	void __fastcall funcDeleteButtonImage();

	void __fastcall funcAllUmdRiCode();

public:		// User declarations

	__fastcall TfrmSidoCode(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSidoCode *frmSidoCode;
//---------------------------------------------------------------------------
#endif
