//---------------------------------------------------------------------------

#ifndef untCalcDateH
#define untCalcDateH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
#include <pngimage.hpp>
//---------------------------------------------------------------------------
class TfrmCalcDate : public TForm
{
__published:	// IDE-managed Components
	TPanel *panCenter;
	TSpeedButton *btnCalc;
	TEdit *edtYear;
	TComboBox *cboYearType;
	TStaticText *StaticText1;
	TStaticText *StaticText2;
	TStaticText *StaticText3;
	TStaticText *StaticText4;
	TStaticText *StaticText5;
	TStaticText *StaticText6;
	TStaticText *StaticText7;
	TStaticText *StaticText8;
	TImage *imgBG;
	TImage *Image3;
	TImage *btnCloseTypeB;
	TPanel *panWindowsMove;
	TImage *Image2;
	TLabel *lblFormTitle;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnCalcClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall edtYearKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall cboYearTypeChange(TObject *Sender);
	void __fastcall btnCloseTypeBClick(TObject *Sender);
	void __fastcall panWindowsMoveMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall FormDeactivate(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TfrmCalcDate(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCalcDate *frmCalcDate;
//---------------------------------------------------------------------------
#endif
